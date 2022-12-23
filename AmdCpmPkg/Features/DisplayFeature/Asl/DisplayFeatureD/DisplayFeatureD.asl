/*****************************************************************************
 *
 * Copyright (C) 2012-2022 Advanced Micro Devices, Inc. All rights reserved.
 *
 ******************************************************************************
 */

DefinitionBlock (
    "DisplayFeatureD.aml",          // Output file
    "SSDT",                         // Signature
    0x01,                           // SSDT Revision
    "AMD",                          // OEM ID
    "CPMDFDGP",                     // OEM Table ID
    0x1                             // OEM Revision
    )
{
    #define CPM_DISPLAY_FEATURE_ASL

    #include "CmnDef.asi"
    #include "CmnExt.asi"

    External(\_SB.PCI0.PB2, DeviceObj)

    Scope(\_SB.PCI0.PB2)
    {
        Device (VGA)
        {
            Name (_ADR, 0x00)

            Method (_RMV, 0, NotSerialized)
            {
                Return (0)
            }
        } // End of Device(VGA)

        Device (HDAU)
        {
            Name (_ADR, 0x01)

            Method (_RMV, 0, NotSerialized)
            {
                Return (0)
            }

            Method(_STA, 0)
            {
                If (LNotEqual(CpmdGpuAudioDisable, 0))  // PX enabled
                {
                    Return(0x0)                         // Disable Audio device
                }
                Else
                {
                    Return(0xF)                         // Enable Audio device
                }
            }
        } // End of Device (HDAU)
    } // End of Scope(\_SB.PCI0.PB2)
}