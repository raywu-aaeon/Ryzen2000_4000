/*****************************************************************************
 *
 * Copyright (C) 2012-2022 Advanced Micro Devices, Inc. All rights reserved.
 *
 ******************************************************************************
 */

DefinitionBlock (
    "DisplayFeatureI.aml",          // Output file
    "SSDT",                         // Signature
    0x01,                           // SSDT Revision
    "AMD",                          // OEM ID
    "CPMDFIGP",                     // OEM Table ID
    0x1                             // OEM Revision
    )
{
    #define CPM_DISPLAY_FEATURE_ASL

    #include "CmnDef.asi"
    #include "CmnExt.asi"
    #include "PostCode.asi"

    External(\_SB.PCI0.VGA, DeviceObj)
    External(\_SB.ALIB, MethodObj)
    External(\_SB.LID._LID, MethodObj)

    External(\_SB.PCI0.VGA.AFN0, MethodObj)
    External(\_SB.PCI0.VGA.AFN1, MethodObj)
    External(\_SB.PCI0.VGA.AFN2, MethodObj)
    External(\_SB.PCI0.VGA.AFN3, MethodObj)
    External(\_SB.PCI0.VGA.AFN4, MethodObj)
    External(\_SB.PCI0.VGA.AFN5, MethodObj)
    External(\_SB.PCI0.VGA.AFN6, MethodObj)
    External(\_SB.PCI0.VGA.AFN7, MethodObj)
    External(\_SB.PCI0.VGA.AFN8, MethodObj)
    External(\_SB.PCI0.VGA.AFNC, MethodObj)

    External(\_SB.PCI0.PB2.VGA.AFN0, MethodObj)
    External(\_SB.PCI0.PB2.VGA.AFN1, MethodObj)
    External(\_SB.PCI0.PB2.VGA.AFN2, MethodObj)
    External(\_SB.PCI0.PB2.VGA.AFN3, MethodObj)
    External(\_SB.PCI0.PB2.VGA.AFN4, MethodObj)
    External(\_SB.PCI0.PB2.VGA.AFN5, MethodObj)
    External(\_SB.PCI0.PB2.VGA.AFN6, MethodObj)
    External(\_SB.PCI0.PB2.VGA.AFN7, MethodObj)
    External(\_SB.PCI0.PB2.VGA.AFN8, MethodObj)
    External(\_SB.PCI0.PB2.VGA.AFNC, MethodObj)

    External(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN0, MethodObj)
    External(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN1, MethodObj)
    External(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN2, MethodObj)
    External(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN3, MethodObj)
    External(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN4, MethodObj)
    External(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN5, MethodObj)
    External(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN6, MethodObj)
    External(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN7, MethodObj)
    External(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN8, MethodObj)
    External(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFNC, MethodObj)

    Scope(\_SB.PCI0.VGA)
    {
        #include "atcs.asi"
        #include "atrm.asi"
    }

    Method(AFN0, 0, Serialized)
    {
        If(LEqual(CpmIsDgpuPrimary, 0))
        {
            If(CondRefOf(\_SB.PCI0.VGA.AFN0)) {
                \_SB.PCI0.VGA.AFN0()
            }
        }
        If(LEqual(CpmIsDgpuPrimary, 1))
        {
            If(CondRefOf(\_SB.PCI0.PB2.VGA.AFN0)) {
                \_SB.PCI0.PB2.VGA.AFN0()
            }
            If(CondRefOf(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN0)) {
                \_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN0()
            }
        }
    }
    Method(AFN1, 1, Serialized)
    {
        If(LEqual(CpmIsDgpuPrimary, 0))
        {
            If(CondRefOf(\_SB.PCI0.VGA.AFN1)) {
                \_SB.PCI0.VGA.AFN1(Arg0)
            }
        }
        If(LEqual(CpmIsDgpuPrimary, 1))
        {
            If(CondRefOf(\_SB.PCI0.PB2.VGA.AFN1)) {
                \_SB.PCI0.PB2.VGA.AFN1(Arg0)
            }
            If(CondRefOf(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN1)) {
                \_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN1(Arg0)
            }
        }
    }
    Method(AFN2, 2, Serialized)
    {
        If(LEqual(CpmIsDgpuPrimary, 0))
        {
            If(CondRefOf(\_SB.PCI0.VGA.AFN2)) {
                \_SB.PCI0.VGA.AFN2(Arg0, Arg1)
            }
        }
        If(LEqual(CpmIsDgpuPrimary, 1))
        {
            If(CondRefOf(\_SB.PCI0.PB2.VGA.AFN2)) {
                \_SB.PCI0.PB2.VGA.AFN2(Arg0, Arg1)
            }
            If(CondRefOf(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN2)) {
                \_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN2(Arg0, Arg1)
            }
        }
    }
    Method(AFN3, 2, Serialized)
    {
        If(LEqual(CpmIsDgpuPrimary, 0))
        {
            If(CondRefOf(\_SB.PCI0.VGA.AFN3)) {
                \_SB.PCI0.VGA.AFN3(Arg0, Arg1)
            }
        }
        If(LEqual(CpmIsDgpuPrimary, 1))
        {
            If(CondRefOf(\_SB.PCI0.PB2.VGA.AFN3)) {
                \_SB.PCI0.PB2.VGA.AFN3(Arg0, Arg1)
            }
            If(CondRefOf(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN3)) {
                \_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN3(Arg0, Arg1)
            }
        }
    }
    Method(AFN4, 1, Serialized)
    {
        If(LEqual(CpmIsDgpuPrimary, 0))
        {
            If(CondRefOf(\_SB.PCI0.VGA.AFN4)) {
                \_SB.PCI0.VGA.AFN4(Arg0)
            }
        }
        If(LEqual(CpmIsDgpuPrimary, 1))
        {
            If(CondRefOf(\_SB.PCI0.PB2.VGA.AFN4)) {
                \_SB.PCI0.PB2.VGA.AFN4(Arg0)
            }
            If(CondRefOf(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN4)) {
                \_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN4(Arg0)
            }
        }
    }
    Method(AFN5, 0, Serialized)
    {
        If(LEqual(CpmIsDgpuPrimary, 0))
        {
            If(CondRefOf(\_SB.PCI0.VGA.AFN5)) {
                \_SB.PCI0.VGA.AFN5()
            }
        }
        If(LEqual(CpmIsDgpuPrimary, 1))
        {
            If(CondRefOf(\_SB.PCI0.PB2.VGA.AFN5)) {
                \_SB.PCI0.PB2.VGA.AFN5()
            }
            If(CondRefOf(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN5)) {
                \_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN5()
            }
        }
    }
    Method(AFN6, 0, Serialized)
    {
        If(LEqual(CpmIsDgpuPrimary, 0))
        {
            If(CondRefOf(\_SB.PCI0.VGA.AFN6)) {
                \_SB.PCI0.VGA.AFN6()
            }
        }
        If(LEqual(CpmIsDgpuPrimary, 1))
        {
            If(CondRefOf(\_SB.PCI0.PB2.VGA.AFN6)) {
                \_SB.PCI0.PB2.VGA.AFN6()
            }
            If(CondRefOf(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN6)) {
                \_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN6()
            }
        }
    }
    Method(AFN7, 1, Serialized)
    {
        If(LEqual(CpmIsDgpuPrimary, 0))
        {
            If(CondRefOf(\_SB.PCI0.VGA.AFN7)) {
                \_SB.PCI0.VGA.AFN7(Arg0)
            }
        }
        If(LEqual(CpmIsDgpuPrimary, 1))
        {
            If(CondRefOf(\_SB.PCI0.PB2.VGA.AFN7)) {
                \_SB.PCI0.PB2.VGA.AFN7(Arg0)
            }
            If(CondRefOf(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN7)) {
                \_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN7(Arg0)
            }
        }
    }
    Method(AFN8, 0, Serialized)
    {
        If(LEqual(CpmIsDgpuPrimary, 0))
        {
            If(CondRefOf(\_SB.PCI0.VGA.AFN8)) {
                \_SB.PCI0.VGA.AFN8()
            }
        }
        If(LEqual(CpmIsDgpuPrimary, 1))
        {
            If(CondRefOf(\_SB.PCI0.PB2.VGA.AFN8)) {
                \_SB.PCI0.PB2.VGA.AFN8()
            }
            If(CondRefOf(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN8)) {
                \_SB.PCI0.PB2.SWUS.SWDS.VGA.AFN8()
            }
        }
    }
    Method(AFNC, 2, Serialized)
    {
        If(LEqual(CpmIsDgpuPrimary, 0))
        {
            If(CondRefOf(\_SB.PCI0.VGA.AFNC)) {
                \_SB.PCI0.VGA.AFNC(Arg0, Arg1)
            }
        }
        If(LEqual(CpmIsDgpuPrimary, 1))
        {
            If(CondRefOf(\_SB.PCI0.PB2.VGA.AFNC)) {
                \_SB.PCI0.PB2.VGA.AFNC(Arg0, Arg1)
            }
            If(CondRefOf(\_SB.PCI0.PB2.SWUS.SWDS.VGA.AFNC)) {
                \_SB.PCI0.PB2.SWUS.SWDS.VGA.AFNC(Arg0, Arg1)
            }
        }
    }

}