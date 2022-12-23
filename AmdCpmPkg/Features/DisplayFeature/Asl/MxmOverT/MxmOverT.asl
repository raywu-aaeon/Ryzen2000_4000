/*****************************************************************************
 *
 * Copyright (C) 2012-2022 Advanced Micro Devices, Inc. All rights reserved.
 *
 ******************************************************************************
 */

DefinitionBlock (
    "MxmOverT.aml",                 // Output file
    "SSDT",                         // Signature
    0x01,                           // SSDT Revision
    "AMD",                          // OEM ID
    "CPMDFMOT",                     // OEM Table ID
    0x1                             // OEM Revision
    )
{
    #include "CmnDef.asi"
    #include "CmnExt.asi"

    External(AFN3, MethodObj)

    Scope(\_GPE)                                    // General-Purpose Event
    {
        Method(CpmMxmOverTempEventMethod)
        {
            Store(CpmReadTable(CpmDisplayFeatureTable, CpmDisplayFeatureMxmOverTempEvent), Local0)
            Store(CpmReadTable(CpmDisplayFeatureTable, CpmDisplayFeatureMxmOverTempStateId), Local1)
            If (CpmReadGeventTriggerType(Local0))
            {
               If (CpmReadGevent(Local0))
               {
                   AFN3(0, 2)
                   CpmWriteGeventTriggerType(Local0, Xor(CpmReadGevent(Local0), 1))
               }
            }
            Else
            {
               If(LNot(CpmReadGevent(Local0)))
               {
                   AFN3(Local1, 2)                  //the state ID need to confirm
                   CpmWriteGeventTriggerType (Local0, Xor(CpmReadGevent(Local0), 1))
               }
            }
        }
    }
}