/*
 * FreeRTOS V202212.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software. If you wish to use our Amazon
 * FreeRTOS name, please do so in a fair use way that does not cause confusion.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Demo includes. */
#include "IntQueueTimer.h"
#include "IntQueue.h"

/* Infineon iLLD includes. */
#include "IfxCpu_Irq.h"
#include "IfxEgtm_reg.h"
#include "Egtm/Std/IfxEgtm.h"
#include "Egtm/Std/IfxEgtm_Cmu.h"
#include "Egtm/Std/IfxEgtm_Tom.h"
#include "Src/Std/IfxSrc.h"

/*-----------------------------------------------------------*/

/*
 * Use FXCLK2 (GCLK / 256) so the period fits in the TOM 16-bit counter.
 * Example: 200 MHz module clock  -> FXCLK2 = 781 kHz  -> period ~783
 *          500 MHz module clock  -> FXCLK2 = 1.95 MHz -> period ~1959
 */
#define intqueueTIMER_FREQUENCY      997UL
#define intqueueTIMER_ISR_PRIORITY   31
#define intqueueTIMER_CLUSTER        0
#define intqueueTIMER_CHANNEL        IfxEgtm_Tom_Ch_0

/* Keep a pointer to the TOM so the ISR can access it without the
 * high-level IfxEgtm_Tom_Timer driver. */
static Ifx_EGTM_CLS_TOM *pxTom;

IFX_INTERRUPT( vIntQueueTimerIsr, 0, intqueueTIMER_ISR_PRIORITY );

void vInitialiseTimerForIntQueueTest( void )
{
	float32 fModuleFreq, fFxclk2Freq;
	uint16  usPeriod;
	volatile Ifx_SRC_SRCR *pxSrc;
	Ifx_EGTM_CLS_TOM_TGC *pxTgc;

	/* ---- Enable the EGTM module and clocks ---- */
	IfxEgtm_enable( &MODULE_EGTM );
	fModuleFreq = IfxEgtm_Cmu_getModuleFrequency( &MODULE_EGTM );
	IfxEgtm_Cmu_setGclkFrequency( &MODULE_EGTM, fModuleFreq );
	IfxEgtm_Cmu_enableClocks( &MODULE_EGTM, IFXEGTM_CMU_CLKEN_FXCLK );

	/* ---- Low-level TOM channel configuration ---- */
	pxTom = &MODULE_EGTM.CLS[ intqueueTIMER_CLUSTER ].TOM;

	/* Select FXCLK2 (GCLK / 256) as clock source. */
	IfxEgtm_Tom_Ch_setClockSource( pxTom, intqueueTIMER_CHANNEL,
								   IfxEgtm_Tom_Ch_ClkSrc_cmuFxclk2 );

	/* Calculate and set the period (CM0). */
	fFxclk2Freq = fModuleFreq / 256.0f;
	usPeriod    = ( uint16 )( fFxclk2Freq / ( float32 ) intqueueTIMER_FREQUENCY );
	configASSERT( usPeriod > 0U );

	IfxEgtm_Tom_Ch_setCompareZeroShadow( pxTom, intqueueTIMER_CHANNEL, usPeriod );

	/* Counter starts at 0. */
	IfxEgtm_Tom_Ch_setCounterValue( pxTom, intqueueTIMER_CHANNEL, 0U );

	/* Generate trigger at CM0 match so shadow-to-active transfer happens. */
	IfxEgtm_Tom_Ch_setTriggerOutput( pxTom, intqueueTIMER_CHANNEL,
									 IfxEgtm_Tom_Ch_OutputTrigger_generate );

	/* Enable CCU0 (zero-match) interrupt in pulse-notify mode. */
	IfxEgtm_Tom_Ch_setNotification( pxTom, intqueueTIMER_CHANNEL,
									IfxEgtm_IrqMode_pulseNotify, TRUE, FALSE );

	/* ---- Configure the Service Request Node (SRC) ---- */
	pxSrc = IfxEgtm_Tom_Ch_getSrcPointer( &MODULE_EGTM,
										   ( IfxEgtm_Cluster ) intqueueTIMER_CLUSTER,
										   intqueueTIMER_CHANNEL );
	IfxSrc_init( pxSrc, IfxSrc_Tos_cpu0,
				 ( Ifx_Priority ) intqueueTIMER_ISR_PRIORITY,
				 ( IfxSrc_VmId ) configVM_NR );
	IfxSrc_enable( pxSrc );

	/* ---- Transfer shadow registers and start the timer ---- */
	pxTgc = IfxEgtm_Tom_Ch_getTgcPointer( pxTom, 0 );

	/* Force-update shadow -> actual. */
	IfxEgtm_Tom_Tgc_setChannelsForceUpdate( pxTgc, 1U << 0, 0, 0, 0 );
	IfxEgtm_Tom_Tgc_trigger( pxTgc );
	IfxEgtm_Tom_Tgc_setChannelsForceUpdate( pxTgc, 0, 1U << 0, 0, 0 );

	/* Clear any spurious notification that arose during setup. */
	IfxEgtm_Tom_Ch_clearZeroNotification( pxTom, intqueueTIMER_CHANNEL );

	/* Enable the single channel on TGC0 only — bypasses
	 * IfxEgtm_Tom_Timer_run() which crashes accessing tgc[1]. */
	IfxEgtm_Tom_Tgc_enableChannels( pxTgc, 1U << 0, 0, TRUE );
}
/*-----------------------------------------------------------*/

void vIntQueueTimerIsr( void )
{
	if( IfxEgtm_Tom_Ch_isZeroNotification( pxTom, intqueueTIMER_CHANNEL ) )
	{
		IfxEgtm_Tom_Ch_clearZeroNotification( pxTom, intqueueTIMER_CHANNEL );

		/* Allow higher-priority interrupts to nest. */
		__enable();

		IntQueueTestTimerHandler();
	}
}
/*-----------------------------------------------------------*/

void IntQueueTestTimerHandler( void )
{
	portYIELD_FROM_ISR( xSecondTimerHandler() );
}
/*-----------------------------------------------------------*/
