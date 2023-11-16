/**
 * \file Ifx_Ssw_Tc2.c
 * \brief Startup Software for Core2
 *
 * \version iLLD_1_0_1_16_0_1
 * \copyright Copyright (c) 2018 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 * Use of this file is subject to the terms of use agreed between (i) you or
 * the company in which ordinary course of business you are acting and (ii)
 * Infineon Technologies AG or its licensees. If and as long as no such terms
 * of use are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Ifx_Cfg.h"
#include "Ifx_Ssw.h"
#include "Ifx_Ssw_Infra.h"

#include "IfxScu_reg.h"
#include "IfxStm_reg.h"

/******************************************************************************/
/*                          Macros                                            */
/******************************************************************************/
/** \brief Configuration for cache enable.
 *
 */
#ifndef IFX_CFG_SSW_ENABLE_TRICORE2_PCACHE
#   define IFX_CFG_SSW_ENABLE_TRICORE2_PCACHE (1U)  /**< Program Cache enabled by default*/
#endif
#ifndef IFX_CFG_SSW_ENABLE_TRICORE2_DCACHE
#   define IFX_CFG_SSW_ENABLE_TRICORE2_DCACHE (1U)  /**< Data Cache enabled by default*/
#endif
/*******************************************************************************
**                      Imported Function Declarations                        **
*******************************************************************************/
IFX_SSW_COMMON_LINKER_SYMBOLS();
IFX_SSW_CORE_LINKER_SYMBOLS(2);


/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*********************************************************************************
* - startup code
*********************************************************************************/
/*Add options to eliminate usage of stack pointers unnecessarily*/
#if defined(__HIGHTEC__)
#pragma GCC optimize "O2"
#endif

void __Core2_start(void)
{
    unsigned int   stmCount;
    unsigned int   stmCountBegin = STM0_TIM0.U;     /* it is necessary to get this value to have minimum 100uS delay in subsequent CPU start */
    unsigned short wdtPassword   = Ifx_Ssw_getCpuWatchdogPasswordInline(&MODULE_SCU.WDTCPU[2]);

    /* Load user stack pointer */
    Ifx_Ssw_setAddressReg(sp, __USTACK(2));
    Ifx_Ssw_DSYNC();

    /* Set the PSW to its reset value in case of a warm start,clear PSW.IS */
    Ifx_Ssw_MTCR(CPU_PSW, IFX_CFG_SSW_PSW_DEFAULT);

    /* Clear the ENDINIT bit in the WDT_CON0 register, inline function */
    Ifx_Ssw_clearCpuEndinitInline(&MODULE_SCU.WDTCPU[2], wdtPassword);

    {
        Ifx_CPU_PCON0 pcon0;
        pcon0.U       = 0;
        pcon0.B.PCBYP = IFX_CFG_SSW_ENABLE_TRICORE2_PCACHE ? 0 : 1; /*depending on the enable bypass bit is reset/set */
        Ifx_Ssw_MTCR(CPU_PCON0, pcon0.U);
        Ifx_Ssw_ISYNC();
    }

    {
        Ifx_CPU_DCON0 dcon0;
        dcon0.U       = 0;
        dcon0.B.DCBYP = IFX_CFG_SSW_ENABLE_TRICORE2_DCACHE ? 0 : 1; /*depending on the enable bypass bit is reset/set */
        Ifx_Ssw_MTCR(CPU_DCON0, dcon0.U);
        Ifx_Ssw_ISYNC();
    }

    /* Load Base Address of Trap Vector Table. */
    Ifx_Ssw_MTCR(CPU_BTV, (unsigned int)__TRAPTAB(2));

    /* Load Base Address of Interrupt Vector Table. we will do this later in the program */
    Ifx_Ssw_MTCR(CPU_BIV, (unsigned int)__INTTAB(2));

    /* Load interrupt stack pointer. */
    Ifx_Ssw_MTCR(CPU_ISP, (unsigned int)__ISTACK(2));

    Ifx_Ssw_setCpuEndinitInline(&MODULE_SCU.WDTCPU[2], wdtPassword);

    /* initialize SDA base pointers */
    Ifx_Ssw_setAddressReg(a0, __SDATA1(2));
    Ifx_Ssw_setAddressReg(a1, __SDATA2(2));
    Ifx_Ssw_setAddressReg(a8, __SDATA3(2));
    Ifx_Ssw_setAddressReg(a9, __SDATA4(2));

    Ifx_Ssw_initCSA((unsigned int *)__CSA(2), (unsigned int *)__CSA_END(2));

    /* Clears any instruction buffer */
    Ifx_Ssw_ISYNC();

    stmCount = (unsigned int)(Ifx_Ssw_getStmFrequency() * IFX_CFG_SSW_STARTCPU_WAIT_TIME_IN_SECONDS);

    while ((unsigned int)(STM0_TIM0.U - stmCountBegin) < stmCount)
    {
        /* There is no need to check overflow of the STM timer.
         * When counter after overflow subtracted with counter before overflow,
         * the subtraction result will be as expected, as long as both are unsigned 32 bits
         * eg: stmCountBegin= 0xFFFFFFFE (before overflow)
         *     stmCountNow = 0x00000002 (before overflow)
         *     diff= stmCountNow - stmCountBegin = 4 as expected.*/
    }

    /*Initialize CPU Private Global Variables*/
    //TODO : This implementation is done once all compilers support this
#if (IFX_CFG_SSW_ENABLE_INDIVIDUAL_C_INIT != 0)
    /* Hook functions to initialize application specific HW extensions */
    if(hardware_init_hook)
    {
    	hardware_init_hook();
    }

    /* Hook functions to initialize application specific SW extensions */
    if(software_init_hook)
    {
    	software_init_hook();
    }

    /* Initialization of C runtime variables and CPP constructors and destructors */
    Ifx_Ssw_doCppInit();
#endif

#ifdef IFX_CFG_SSW_RETURN_FROM_MAIN
    {
        extern int core2_main(void);
        int status= core2_main();        /* Call main function of CPU2 */
#if (IFX_CFG_SSW_ENABLE_INDIVIDUAL_C_INIT != 0)
        Ifx_Ssw_doCppExit(status);
#else /* (IFX_CFG_SSW_ENABLE_INDIVIDUAL_C_INIT != 0) */
        (void)status;
#endif /* (IFX_CFG_SSW_ENABLE_INDIVIDUAL_C_INIT != 0) */
    }
#else /* IFX_CFG_SSW_RETURN_FROM_MAIN */
    extern void core2_main(void);
    Ifx_Ssw_jumpToFunction(core2_main);  /* Jump to main function of CPU2 */
#endif /* IFX_CFG_SSW_RETURN_FROM_MAIN */

    /* Go into infinite loop, normally the code shall not reach here */
    Ifx_Ssw_infiniteLoop();
}

/******************************************************************************
 *                        reset vector address                                *
 *****************************************************************************/
#if defined(__HIGHTEC__)
#pragma section
#pragma section ".start_cpu2" x
#endif
#if defined(__TASKING__)
#pragma protect on
#pragma section code "start_cpu2"
#endif
#if defined(__DCC__)
#pragma section CODE ".start_cpu2" X
#endif
#if defined(__ghs__)
#pragma ghs section text=".start_cpu2"
#endif

void _START2(void)
{
    Ifx_Ssw_jumpToFunction(__Core2_start);
}

/* reset the sections defined above, to normal region */
#if defined(__HIGHTEC__)
#pragma section
#endif
#if defined(__TASKING__)
#pragma protect restore
#pragma section code restore
#endif
#if defined(__DCC__)
#pragma section CODE
#endif
#if defined(__ghs__)
#pragma ghs section text=default
#endif

/*Restore the options to command line provided ones*/
#if defined(__HIGHTEC__)
#pragma GCC reset_options
#endif
