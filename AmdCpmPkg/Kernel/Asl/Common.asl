/*****************************************************************************
 *
 * Copyright (C) 2012-2022 Advanced Micro Devices, Inc. All rights reserved.
 *
 ******************************************************************************
 */

DefinitionBlock (
    "Common.aml",                   // Output file
    "SSDT",                         // Signature
    0x01,                           // SSDT Revision
    "AMD",                          // OEM ID
    "CPMCMN",                       // OEM Table ID
    0x1                             // OEM Revision
    )
{
    #define CPM_COMMON_ASL

    External(\_SB.ALIB, MethodObj)

    #include "CmnDef.asi"
    #include "CmnExt.asi"
    #include "PostCode.asi"
    #include "NvData.asi"
    #include "Function.asi"
}