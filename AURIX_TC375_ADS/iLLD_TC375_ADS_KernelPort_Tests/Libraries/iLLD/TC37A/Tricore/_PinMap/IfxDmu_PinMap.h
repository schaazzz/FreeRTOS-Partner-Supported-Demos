/**
 * \file IfxDmu_PinMap.h
 * \brief DMU I/O map
 * \ingroup IfxLld_Dmu
 *
 * \version iLLD_1_0_1_16_0_1
 * \copyright Copyright (c) 2017 Infineon Technologies AG. All rights reserved.
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
 * \defgroup IfxLld_Dmu_pinmap DMU Pin Mapping
 * \ingroup IfxLld_Dmu
 */

#ifndef IFXDMU_PINMAP_H
#define IFXDMU_PINMAP_H

#include <IfxDmu_reg.h>
#include <Port/Std/IfxPort.h>

/** \addtogroup IfxLld_Dmu_pinmap
 * \{ */

/** \brief DMU FDEST pin mapping structure */
typedef const struct
{
    Ifx_DMU*         module;    /**< \brief Base address */
    IfxPort_Pin       pin;       /**< \brief Port pin */
    Ifx_RxSel         select;    /**< \brief Input multiplexer value */
} IfxDmu_Fdest_In;


IFX_EXTERN IfxDmu_Fdest_In IfxDmu_FDEST_P21_0_IN;  /**< \brief Enter destructive debug mode */

/** \brief Table dimensions */
#define IFXDMU_PINMAP_NUM_MODULES 1
#define IFXDMU_PINMAP_NUM_0S 1
#define IFXDMU_PINMAP_FDEST_IN_NUM_ITEMS 1


/** \brief IfxDmu_Fdest_In table */
IFX_EXTERN const IfxDmu_Fdest_In *IfxDmu_Fdest_In_pinTable[IFXDMU_PINMAP_NUM_MODULES][IFXDMU_PINMAP_NUM_0S][IFXDMU_PINMAP_FDEST_IN_NUM_ITEMS];

/** \} */

#endif /* IFXDMU_PINMAP_H */
