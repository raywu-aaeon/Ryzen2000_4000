/*****************************************************************************
 *
 * Copyright (C) 2012-2022 Advanced Micro Devices, Inc. All rights reserved.
 *
 ******************************************************************************
 */

DefinitionBlock (
    "DisplayConnectEvent.aml",      // Output file
    "SSDT",                         // Signature
    0x01,                           // SSDT Revision
    "AMD",                          // OEM ID
    "CPMDFDCE",                     // OEM Table ID
    0x1                             // OEM Revision
    )
{
    #include "CmnDef.asi"
    #include "CmnExt.asi"
    #include "PostCode.asi"

    External(AFN8, MethodObj)
    External(\_SB.PCI0.PB2.VGA, DeviceObj)
    External(\_SB.PCI0.PB2.SWUS.SWDS.VGA, DeviceObj)
    External(\_SB.PCI0.PB2.CpmDgpuD3ColdHpdSupport, IntObj)

    Scope(\_GPE)                                    // General-Purpose Event
    {
        Method(CpmDisplayConnectEventMethod)
        {
            Store(CpmReadTable(CpmDisplayFeatureTable, CpmDisplayFeatureDisplayConnectEvent), Local0)
            If (CpmReadGeventTriggerType(Local0))
            {
                If (CpmReadGevent(Local0))
                {
                    If (LEqual (\_SB.PCI0.PB2.CpmDgpuD3ColdHpdSupport, 1)) {
                        CpmSetPostCode (CpmTpMxmHpdEventIn)
                        AFN8()
                    }
                    CpmWriteGeventTriggerType(Local0, Xor(CpmReadGevent(Local0), 1))
                    If (LEqual (\_SB.PCI0.PB2.CpmDgpuD3ColdHpdSupport, 1)) {
                        // Move Notify(VGA, 0x81) from ATIF AFN8() to General-Purpose Event \_GPE._Lxx in DisplayConnectEvent.asl.
                        If(CondRefOf(\_SB.PCI0.PB2.VGA)) {
                            Notify(\_SB.PCI0.PB2.VGA, 0x81)
                        }
                        If(CondRefOf(\_SB.PCI0.PB2.SWUS.SWDS.VGA)) {
                            Notify(\_SB.PCI0.PB2.SWUS.SWDS.VGA, 0x81)
                        }
                    }
                }
            }
            Else
            {
                If(LNot(CpmReadGevent(Local0)))
                {
                    If (LEqual (\_SB.PCI0.PB2.CpmDgpuD3ColdHpdSupport, 1)) {
                        CpmSetPostCode (CpmTpMxmHpdEventOut)
                        AFN8()
                    }
                    CpmWriteGeventTriggerType(Local0, Xor(CpmReadGevent(Local0), 1))
                    If (LEqual (\_SB.PCI0.PB2.CpmDgpuD3ColdHpdSupport, 1)) {
                        // Move Notify(VGA, 0x81) from ATIF AFN8() to General-Purpose Event \_GPE._Lxx in DisplayConnectEvent.asl.
                        If(CondRefOf(\_SB.PCI0.PB2.VGA)) {
                            Notify(\_SB.PCI0.PB2.VGA, 0x81)
                        }
                        If(CondRefOf(\_SB.PCI0.PB2.SWUS.SWDS.VGA)) {
                            Notify(\_SB.PCI0.PB2.SWUS.SWDS.VGA, 0x81)
                        }
                    }
                }
            }
        }
    }
}