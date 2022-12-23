/*****************************************************************************
 *
 * Copyright (C) 2012-2022 Advanced Micro Devices, Inc. All rights reserved.
 *
 ******************************************************************************
 */

/*****************************************************************************
 *
 * This software package can be used to enable the Overclocking of certain
 * AMD processors and its use is subject to the terms and conditions of the
 * AMD Overclocking Waiver. Enabling overclocking through use of the low-level
 * routines included in this package and operating an AMD processor outside of
 * the applicable AMD product specifications will void any AMD warranty and can
 * result in damage to the processor or the system into which the processor has
 * been integrated. The user of this software assumes, and AMD disclaims, all
 * risk, liability, costs and damages relating to or arising from the overclocking
 * of AMD processors.
 *
 ******************************************************************************
 */

DefinitionBlock (
    "AodSsdt.aml",     // Output file
    "SSDT",                         // Signature
    0x01,                           // SSDT Revision
    "AMD",                          // OEM ID
    "AOD",                          // OEM Table ID
    0x1                             // OEM Revision
    )
{
  #include "WmiDev.asi"
}

