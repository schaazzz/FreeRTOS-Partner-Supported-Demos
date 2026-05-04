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
 * copies or substantial portions of the Software.
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

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

/* Interface include files. */
#include "RegTests.h"

/*-----------------------------------------------------------*/

#define regtestREGISTER_COUNT    16U

#define portREGTEST_STRINGIFY_IMPL( x )    #x
#define portREGTEST_STRINGIFY( x )         portREGTEST_STRINGIFY_IMPL( x )

#define portREGTEST_YIELD_ASM \
    "syscall " portREGTEST_STRINGIFY( configYIELD_SYSCALL_ID ) " \n\t"

/* Tasks that implement register tests. */
static void prvRegisterTest1Task( void * pvParameters );
static void prvRegisterTest2Task( void * pvParameters );
static void prvRegisterTest3Task( void * pvParameters );
static void prvRegisterTest4Task( void * pvParameters );

/* Helpers. */
static BaseType_t prvRunRegisterTestIteration( const uint32_t * pulExpected,
                                               uint32_t * pulReadBack ) __attribute__( ( noinline, noclone ) );

static BaseType_t prvCheckRegisterValues( const uint32_t * pulExpected,
                                          const uint32_t * pulReadBack );

/* Flag that will be latched to pdTRUE should any unexpected behaviour be
detected in any of the tasks. */
static volatile BaseType_t xErrorDetected = pdFALSE;

/* Counters that are incremented on each cycle of a test. This is used to
detect a stalled task - a test that is no longer running. */
static volatile uint32_t ulRegisterTest1Counter = 0;
static volatile uint32_t ulRegisterTest2Counter = 0;
static volatile uint32_t ulRegisterTest3Counter = 0;
static volatile uint32_t ulRegisterTest4Counter = 0;

/*-----------------------------------------------------------*/

static BaseType_t prvRunRegisterTestIteration( const uint32_t * pulExpected,
                                               uint32_t * pulReadBack )
{
    __asm__ volatile
    (
        /* Load known values into D0-D15. */
        "ld.w %%d0,  [%0]0   \n\t"
        "ld.w %%d1,  [%0]4   \n\t"
        "ld.w %%d2,  [%0]8   \n\t"
        "ld.w %%d3,  [%0]12  \n\t"
        "ld.w %%d4,  [%0]16  \n\t"
        "ld.w %%d5,  [%0]20  \n\t"
        "ld.w %%d6,  [%0]24  \n\t"
        "ld.w %%d7,  [%0]28  \n\t"
        "ld.w %%d8,  [%0]32  \n\t"
        "ld.w %%d9,  [%0]36  \n\t"
        "ld.w %%d10, [%0]40  \n\t"
        "ld.w %%d11, [%0]44  \n\t"
        "ld.w %%d12, [%0]48  \n\t"
        "ld.w %%d13, [%0]52  \n\t"
        "ld.w %%d14, [%0]56  \n\t"
        "ld.w %%d15, [%0]60  \n\t"

        /* Force a context switch using the same syscall path as taskYIELD(). */
        /* The yield is emitted directly in this asm sequence instead of calling
         * taskYIELD() from C so GCC cannot clobber lower-context data registers
         * between register setup and readback. */
        portREGTEST_YIELD_ASM

        /* Read back D0-D15 after the context switch. */
        "st.w [%1]0,  %%d0   \n\t"
        "st.w [%1]4,  %%d1   \n\t"
        "st.w [%1]8,  %%d2   \n\t"
        "st.w [%1]12, %%d3   \n\t"
        "st.w [%1]16, %%d4   \n\t"
        "st.w [%1]20, %%d5   \n\t"
        "st.w [%1]24, %%d6   \n\t"
        "st.w [%1]28, %%d7   \n\t"
        "st.w [%1]32, %%d8   \n\t"
        "st.w [%1]36, %%d9   \n\t"
        "st.w [%1]40, %%d10  \n\t"
        "st.w [%1]44, %%d11  \n\t"
        "st.w [%1]48, %%d12  \n\t"
        "st.w [%1]52, %%d13  \n\t"
        "st.w [%1]56, %%d14  \n\t"
        "st.w [%1]60, %%d15  \n\t"
        :
        : "a"( pulExpected ), "a"( pulReadBack )
        : "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7",
          "d8", "d9", "d10", "d11", "d12", "d13", "d14", "d15",
          "memory"
    );

    return prvCheckRegisterValues( pulExpected, pulReadBack );
}

/*-----------------------------------------------------------*/

static BaseType_t prvCheckRegisterValues( const uint32_t * pulExpected,
                                          const uint32_t * pulReadBack )
{
    uint32_t uxIndex;

    for( uxIndex = 0; uxIndex < regtestREGISTER_COUNT; uxIndex++ )
    {
        if( pulExpected[ uxIndex ] != pulReadBack[ uxIndex ] )
        {
            return pdFALSE;
        }
    }

    return pdTRUE;
}

/*-----------------------------------------------------------*/

static void prvRegisterTest1Task( void * pvParameters )
{
    static const uint32_t ulExpected[ regtestREGISTER_COUNT ] =
    {
        0x01010101UL, 0x12121212UL, 0x23232323UL, 0x34343434UL,
        0x45454545UL, 0x56565656UL, 0x67676767UL, 0x78787878UL,
        0x11111111UL, 0x22222222UL, 0x33333333UL, 0x44444444UL,
        0x55555555UL, 0x66666666UL, 0x77777777UL, 0x88888888UL
    };

    uint32_t ulReadBack[ regtestREGISTER_COUNT ];

    ( void ) pvParameters;

    for( ; ; )
    {
        if( prvRunRegisterTestIteration( ulExpected, ulReadBack ) == pdFALSE )
        {
            xErrorDetected = pdTRUE;

            for( ; ; )
            {
                taskYIELD();
            }
        }

        ulRegisterTest1Counter++;
    }
}

/*-----------------------------------------------------------*/

static void prvRegisterTest2Task( void * pvParameters )
{
    static const uint32_t ulExpected[ regtestREGISTER_COUNT ] =
    {
        0x89ABCDEFUL, 0x01234567UL, 0xA5A5A5A5UL, 0x5A5A5A5AUL,
        0x13579BDFUL, 0x2468ACE0UL, 0x0F0F0F0FUL, 0xF0F0F0F0UL,
        0xFEDCBA98UL, 0x76543210UL, 0xAA55AA55UL, 0x55AA55AAUL,
        0x0A0B0C0DUL, 0x10203040UL, 0x89ABC001UL, 0x7F7F7F7FUL
    };

    uint32_t ulReadBack[ regtestREGISTER_COUNT ];

    ( void ) pvParameters;

    for( ; ; )
    {
        if( prvRunRegisterTestIteration( ulExpected, ulReadBack ) == pdFALSE )
        {
            xErrorDetected = pdTRUE;

            for( ; ; )
            {
                taskYIELD();
            }
        }

        ulRegisterTest2Counter++;
    }
}

/*-----------------------------------------------------------*/

static void prvRegisterTest3Task( void * pvParameters )
{
    static const uint32_t ulExpected[ regtestREGISTER_COUNT ] =
    {
        0x01020304UL, 0x11121314UL, 0x21222324UL, 0x31323334UL,
        0x41424344UL, 0x51525354UL, 0x61626364UL, 0x71727374UL,
        0x01010101UL, 0x02020202UL, 0x04040404UL, 0x08080808UL,
        0x10101010UL, 0x20202020UL, 0x40404040UL, 0x80808080UL
    };

    uint32_t ulReadBack[ regtestREGISTER_COUNT ];

    ( void ) pvParameters;

    for( ; ; )
    {
        if( prvRunRegisterTestIteration( ulExpected, ulReadBack ) == pdFALSE )
        {
            xErrorDetected = pdTRUE;

            for( ; ; )
            {
                taskYIELD();
            }
        }

        ulRegisterTest3Counter++;
    }
}

/*-----------------------------------------------------------*/

static void prvRegisterTest4Task( void * pvParameters )
{
    static const uint32_t ulExpected[ regtestREGISTER_COUNT ] =
    {
        0xDEADBEEFUL, 0xC001D00DUL, 0xFEEDFACEUL, 0xCAFEBABEUL,
        0x55AA55AAUL, 0xAA55AA55UL, 0x12345678UL, 0x87654321UL,
        0x0BADB002UL, 0x600DCAFEUL, 0xFACEB00CUL, 0x0FF1CE00UL,
        0x11223344UL, 0x99AABBCCUL, 0xA1B2C3D4UL, 0x5E6F7788UL
    };

    uint32_t ulReadBack[ regtestREGISTER_COUNT ];

    ( void ) pvParameters;

    for( ; ; )
    {
        if( prvRunRegisterTestIteration( ulExpected, ulReadBack ) == pdFALSE )
        {
            xErrorDetected = pdTRUE;

            for( ; ; )
            {
                taskYIELD();
            }
        }

        ulRegisterTest4Counter++;
    }
}

/*-----------------------------------------------------------*/

void vStartRegisterTasks( UBaseType_t uxPriority )
{
    BaseType_t ret;

    ret = xTaskCreate( prvRegisterTest1Task, "RegTest1", configMINIMAL_STACK_SIZE, NULL, uxPriority, NULL );
    configASSERT( ret == pdPASS );

    ret = xTaskCreate( prvRegisterTest2Task, "RegTest2", configMINIMAL_STACK_SIZE, NULL, uxPriority, NULL );
    configASSERT( ret == pdPASS );

    ret = xTaskCreate( prvRegisterTest3Task, "RegTest3", configMINIMAL_STACK_SIZE, NULL, uxPriority, NULL );
    configASSERT( ret == pdPASS );

    ret = xTaskCreate( prvRegisterTest4Task, "RegTest4", configMINIMAL_STACK_SIZE, NULL, uxPriority, NULL );
    configASSERT( ret == pdPASS );
}

/*-----------------------------------------------------------*/

BaseType_t xAreRegisterTasksStillRunning( void )
{
    static uint32_t ulLastRegisterTest1Counter = 0;
    static uint32_t ulLastRegisterTest2Counter = 0;
    static uint32_t ulLastRegisterTest3Counter = 0;
    static uint32_t ulLastRegisterTest4Counter = 0;

    if( ulLastRegisterTest1Counter == ulRegisterTest1Counter )
    {
        xErrorDetected = pdTRUE;
    }

    if( ulLastRegisterTest2Counter == ulRegisterTest2Counter )
    {
        xErrorDetected = pdTRUE;
    }

    if( ulLastRegisterTest3Counter == ulRegisterTest3Counter )
    {
        xErrorDetected = pdTRUE;
    }

    if( ulLastRegisterTest4Counter == ulRegisterTest4Counter )
    {
        xErrorDetected = pdTRUE;
    }

    ulLastRegisterTest1Counter = ulRegisterTest1Counter;
    ulLastRegisterTest2Counter = ulRegisterTest2Counter;
    ulLastRegisterTest3Counter = ulRegisterTest3Counter;
    ulLastRegisterTest4Counter = ulRegisterTest4Counter;

    return ( BaseType_t ) !xErrorDetected;
}

/*-----------------------------------------------------------*/
