/*****************************************************************************
 *
 * Copyright 2015 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting you permission to use this software and documentation (if
 * any) (collectively, the "Materials") pursuant to the terms and conditions of
 * the Software License Agreement included with the Materials.  If you do not
 * have a copy of the Software License Agreement, contact your AMD
 * representative for a copy.
 * 
 * You agree that you will not reverse engineer or decompile the Materials, in
 * whole or in part, except as allowed by applicable law.
 * 
 * WARRANTY DISCLAIMER:  THE MATERIALS ARE PROVIDED "AS IS" WITHOUT WARRANTY OF
 * ANY KIND.  AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY,
 * INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT, THAT THE
 * MATERIALS WILL RUN UNINTERRUPTED OR ERROR-FREE OR WARRANTIES ARISING FROM
 * CUSTOM OF TRADE OR COURSE OF USAGE.  THE ENTIRE RISK ASSOCIATED WITH THE USE
 * OF THE MATERIAL IS ASSUMED BY YOU.  Some jurisdictions do not allow the
 * exclusion of implied warranties, so the above exclusion may not apply to
 * You.
 * 
 * LIMITATION OF LIABILITY AND INDEMNIFICATION:  AMD AND ITS LICENSORS WILL
 * NOT, UNDER ANY CIRCUMSTANCES BE LIABLE TO YOU FOR ANY PUNITIVE, DIRECT,
 * INCIDENTAL, INDIRECT, SPECIAL OR CONSEQUENTIAL DAMAGES ARISING FROM USE OF
 * THE MATERIALS OR THIS AGREEMENT EVEN IF AMD AND ITS LICENSORS HAVE BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  In no event shall AMD's total
 * liability to You for all damages, losses, and causes of action (whether in
 * contract, tort (including negligence) or otherwise) exceed the amount of
 * $100 USD. You agree to defend, indemnify and hold harmless AMD and its
 * licensors, and any of their directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your use of
 * the Materials or violation of the terms and conditions of this Agreement.
 * 
 * U.S. GOVERNMENT RESTRICTED RIGHTS:  The Materials are provided with
 * "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
 * subject to the restrictions as set forth in FAR 52.227-14 and
 * DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
 * Government constitutes acknowledgment of AMD's proprietary rights in them.
 * 
 * EXPORT RESTRICTIONS: The Materials may be subject to export restrictions as
 * stated in the Software License Agreement.
 ******************************************************************************
 */

DefinitionBlock (
    "DGpuD3Cold.aml",               // Output file
    "SSDT",                         // Signature
    0x01,                           // SSDT Revision
    "AMD",                          // OEM ID
    "CPMD3CLD",                     // OEM Table ID
    0x1                             // OEM Revision
    )
{
    #define CPM_DISPLAY_FEATURE_ASL
    #define CPM_DGPU_D3_COLD  1

    #include "CmnDef.asi"
    #include "CmnExt.asi"
    #include "PostCode.asi"

    External(\_SB.PCI0.PB2, DeviceObj)
    External(\_SB.PCI0.PB2.SWUS, DeviceObj)
    External(\_SB.PCI0.PB2.SWUS.SWDS, DeviceObj)
    External(\_SB.ALIB, MethodObj)
    External(\_SB.MACO, BuffFieldObj)

    Scope(\_SB.PCI0.PB2) {
        Name (CpmDgpuPowerResourceBuffer, Buffer (12) {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0})
        Name (CpmDgpuD3ColdMacoGpio, 0)                                         // MACO_EN GPIO pin number for Discrete GPU BxMACO Support          // FCH GPIO 11
        Name (CpmDgpuD3ColdMxmPwrEnGpio, 0)                                     // MXM_POWER_ENABLE GPIO pin number for Discrete GPU BOMACO Support // FCH GPIO 141
        Name (CpmDgpuD3ColdTimeMacoUpPwrDn, 0)                                  // MACO Entry (us): MACO_EN assert to PWR_EN deassert     // Min: 10us
        Name (CpmDgpuD3ColdTimePwrDnRstDn, 0)                                   // MACO Entry (ms): PWR_EN deassert to PERSTb assert      // Min: 20ms
        Name (CpmDgpuD3ColdTimePwrUpRstUp, 0)                                   // MACO Exit  (ms): PWR_EN assert to PERSTb deassert      // Min: 20ms
        Name (CpmDgpuD3ColdTimeRstUpMacoDn, 0)                                  // MACO Exit  (ms): PERSTb deassert to MACO_EN deassert   // Min: 1ms
        Name (CpmDgpuD3ColdHpdSupport, 1)                                       // DgpuD3ColdHpdSupport - DGPU D3Cold HPD Support

        Name (CpmdGpuBridgePMemPostBuffer, Buffer (24) {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0})
        Name (CpmdGpuBridgeUpStPostBuffer, Buffer (24) {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0})
        Name (CpmdGpuBridgeDnStPostBuffer, Buffer (24) {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0})
        Name (CpmdGpuDevicePMemPostBuffer, Buffer (24) {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0})

        Name (CpmdGpuBridgePMemSaveBuffer, Buffer (24) {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0})
        Name (CpmdGpuBridgeUpStSaveBuffer, Buffer (24) {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0})
        Name (CpmdGpuBridgeDnStSaveBuffer, Buffer (24) {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0})
        Name (CpmdGpuDevicePMemSaveBuffer, Buffer (24) {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0})

        Name (CpmdGpuZeroBuffer, Buffer (24) {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0})

        // Program DGPU Bridge/Device MMIO Register
        //  Arg0 - Bus Num of Gfx Bridge
        //  Arg1 - Device Num of Gfx Bridge
        //  Arg2 - Function Num of Gfx Bridge
        //  Arg3 - PostBuffer of Gfx Bridge
        //  Arg4 - Save Bridge = 0
        //         Save Device = 1
        //         Program Bridge = 2
        //         Program Device = 3
        //         Restore Bridge = 4
        //         Restore Device = 5
        Method (CpmProgramRegister, 5) {
            CreateDwordField (Arg3, 0,  CpmBridgeCommand)
            CreateDwordField (Arg3, 4,  CpmBridgeBusNumberReg)
            CreateDwordField (Arg3, 8,  CpmBridgeNonPrefetchable)
            CreateDwordField (Arg3, 12, CpmBridgeLimitBaseLowReg)
            CreateDwordField (Arg3, 16, CpmBridgeBaseHighReg)
            CreateDwordField (Arg3, 20, CpmBridgeLimitHighReg)
            If (LLess (Arg4, 2)) {
                If (LEqual (Arg4, 0)) {
                    // Save Bridge
                    Store (CpmReadPci32 (Arg0, Arg1, Arg2, 0x04), CpmBridgeCommand)
                    Store (CpmReadPci32 (Arg0, Arg1, Arg2, 0x18), CpmBridgeBusNumberReg)
                    Store (CpmReadPci32 (Arg0, Arg1, Arg2, 0x20), CpmBridgeNonPrefetchable)
                    Store (CpmReadPci32 (Arg0, Arg1, Arg2, 0x24), CpmBridgeLimitBaseLowReg)
                    Store (CpmReadPci32 (Arg0, Arg1, Arg2, 0x28), CpmBridgeBaseHighReg)
                    Store (CpmReadPci32 (Arg0, Arg1, Arg2, 0x2C), CpmBridgeLimitHighReg)
                } Else {
                    // Save Device
                    Store (CpmReadPci32 (Arg0, Arg1, Arg2, 0x04), CpmBridgeCommand)
                    Store (CpmReadPci32 (Arg0, Arg1, Arg2, 0x18), CpmBridgeBusNumberReg)
                    Store (CpmReadPci32 (Arg0, Arg1, Arg2, 0x1C), CpmBridgeNonPrefetchable)
                    Store (CpmReadPci32 (Arg0, Arg1, Arg2, 0x24), CpmBridgeLimitBaseLowReg)
                    Store (CpmReadPci32 (Arg0, Arg1, Arg2, 0x00), CpmBridgeBaseHighReg)
                    Store (Arg0, CpmBridgeLimitHighReg)
                }
            } Else {
                If (LEqual (And (Arg4, 1), 0)) {
                    // Program or Restore Bridge
                    CpmWritePci32 (Arg0, Arg1, Arg2, 0x18, CpmBridgeBusNumberReg)
                    CpmWritePci32 (Arg0, Arg1, Arg2, 0x20, CpmBridgeNonPrefetchable)
                    CpmWritePci32 (Arg0, Arg1, Arg2, 0x24, CpmBridgeLimitBaseLowReg)
                    CpmWritePci32 (Arg0, Arg1, Arg2, 0x28, CpmBridgeBaseHighReg)
                    CpmWritePci32 (Arg0, Arg1, Arg2, 0x2C, CpmBridgeLimitHighReg)
                } Else {
                    // Program or Restore Device
                    CpmWritePci32 (Arg0, Arg1, Arg2, 0x18, CpmBridgeBusNumberReg)
                    CpmWritePci32 (Arg0, Arg1, Arg2, 0x1C, CpmBridgeNonPrefetchable)
                    CpmWritePci32 (Arg0, Arg1, Arg2, 0x24, CpmBridgeLimitBaseLowReg)
                }
                If (LEqual (And (Arg4, 4), 4)) {
                    // Restore Bridge or Device
                    CpmWritePci32 (Arg0, Arg1, Arg2, 0x04, And (CpmBridgeCommand, 0x06FFFFFF))
                } Else {
                    // Program Bridge or Device
                    Store (CpmReadPci32 (Arg0, Arg1, Arg2, 0x04), Local0)
                    CpmWritePci32 (Arg0, Arg1, Arg2, 0x04, Or (And (Local0, 0x06FFFFF8), 0x2))
                }
            }
        }

        // Check DGPU Vendor/Device ID
        // Return 0x10 - AMD Ellesmere
        //        0x11 - AMD Baffin
        //        0x12 - AMD Iceland(Weston), Tonga, Polaris22
        //        0x13 - AMD Lexa
        //        0x20 - AMD Greenland
        //        0x21 - AMD Vega12
        //        0x22 - AMD Navi10
        //        0x23 - AMD Navi14
        //        0x00 - AMD Old GPU
        //        0xC0 - NVIDIA GPU
        Method (CpmCheckDgpuVidDid, 0) {
            CreateDwordField (CpmdGpuDevicePMemPostBuffer, 16, CpmDevicePMemPostDeviceId)
            Store (0x00, Local0)
            If (LEqual (And (CpmDevicePMemPostDeviceId, 0xFFDF), 0x1002)) {
                ShiftRight (CpmDevicePMemPostDeviceId, 16, Local1)
                And (Local1, 0xFFFF, Local1)
                If (LAnd (LGreaterEqual (Local1, 0x67C0), LLessEqual (Local1, 0x67DF))) {
                    // 0x10 - AMD Ellesmere
                    Store (0x10, Local0)
                } ElseIf (LAnd (LGreaterEqual (Local1, 0x67E0), LLessEqual (Local1, 0x67FF))) {
                    // 0x11 - AMD Baffin
                    Store (0x11, Local0)
                } ElseIf (LAnd (LGreaterEqual (Local1, 0x6900), LLessEqual (Local1, 0x695F))) {
                    // 0x12 - AMD Iceland(Weston), Tonga, Polaris22
                    Store (0x12, Local0)
                } ElseIf (LAnd (LGreaterEqual (Local1, 0x6980), LLessEqual (Local1, 0x699F))) {
                    // 0x13 - AMD Lexa
                    Store (0x13, Local0)
                } ElseIf (LAnd (LGreaterEqual (Local1, 0x6860), LLessEqual (Local1, 0x687F))) {
                    // 0x20 - AMD Greenland
                    Store (0x20, Local0)
                } ElseIf (LAnd (LGreaterEqual (Local1, 0x69A0), LLessEqual (Local1, 0x69BF))) {
                    // 0x21 - AMD Vega12
                    Store (0x21, Local0)
                } ElseIf (LAnd (LGreaterEqual (Local1, 0x7310), LLessEqual (Local1, 0x731F))) {
                    // 0x22 - AMD Navi10
                    Store (0x22, Local0)
                } ElseIf (LEqual (Local1, 0x7330)) {
                    // 0x22 - AMD Navi10
                    Store (0x22, Local0)
                } ElseIf (LAnd (LGreaterEqual (Local1, 0x7340), LLessEqual (Local1, 0x734F))) {
                    // 0x23 - AMD Navi14
                    Store (0x23, Local0)
                } Else {
                    // 0x00 - AMD Old GPU
                    Store (0x00, Local0)
                }
            } Else {
                If (LEqual (And (CpmDevicePMemPostDeviceId, 0xFFFF), 0x10DE)) {
                    // 0xC0 - NVIDIA GPU
                    Store (0xC0, Local0)
                }
            }
            Return (Local0)
        }

        // Save DGPU Bridge/Device MMIO Register
        //  Arg0 - Bus Num of Gfx Bridge
        //  Arg1 - Device Num of Gfx Bridge
        //  Arg2 - Function Num of Gfx Bridge
        Method (CpmSaveGfxResource, 3) {
            CreateDwordField (CpmdGpuBridgePMemPostBuffer, 4,  CpmBridgePMemPostBusNumberReg)
            CreateDwordField (CpmdGpuBridgeUpStPostBuffer, 4,  CpmBridgeUpStPostBusNumberReg)
            CreateDwordField (CpmdGpuBridgeDnStPostBuffer, 4,  CpmBridgeDnStPostBusNumberReg)

            Store (CpmdGpuZeroBuffer, CpmdGpuBridgePMemSaveBuffer)
            Store (CpmdGpuZeroBuffer, CpmdGpuBridgeUpStSaveBuffer)
            Store (CpmdGpuZeroBuffer, CpmdGpuBridgeDnStSaveBuffer)
            Store (CpmdGpuZeroBuffer, CpmdGpuDevicePMemSaveBuffer)

            CpmProgramRegister (Arg0, Arg1, Arg2, CpmdGpuBridgePMemSaveBuffer, 0)
            CpmWritePci32 (Arg0, Arg1, Arg2, 0x18, CpmBridgePMemPostBusNumberReg)
            ShiftRight (CpmBridgePMemPostBusNumberReg, 8, Local0)
            And (Local0, 0xFF, Local0)
            If (LNotEqual (CpmBridgeUpStPostBusNumberReg, 0)) {
                CpmProgramRegister (Local0, 0, 0, CpmdGpuBridgeUpStSaveBuffer, 0)
                CpmWritePci32 (Local0, 0, 0, 0x18, CpmBridgeUpStPostBusNumberReg)
                ShiftRight (CpmBridgeUpStPostBusNumberReg, 8, Local0)
                And (Local0, 0xFF, Local0)
            }
            If (LAnd (LNotEqual (CpmBridgeUpStPostBusNumberReg, 0), LNotEqual (CpmBridgeDnStPostBusNumberReg, 0))) {
                CpmProgramRegister (Local0, 0, 0, CpmdGpuBridgeDnStSaveBuffer, 0)
                CpmWritePci32 (Local0, 0, 0, 0x18, CpmBridgeDnStPostBusNumberReg)
                ShiftRight (CpmBridgeDnStPostBusNumberReg, 8, Local0)
                And (Local0, 0xFF, Local0)
            }
            CpmProgramRegister (Local0, 0, 0, CpmdGpuDevicePMemSaveBuffer, 1)
        }

        // Init DGPU Bridge/Device MMIO Register
        //  Arg0 - Bus Num of Gfx Bridge
        //  Arg1 - Device Num of Gfx Bridge
        //  Arg2 - Function Num of Gfx Bridge
        Method (CpmProgramGfxResource, 3) {
            CreateDwordField (CpmdGpuBridgePMemPostBuffer, 4,  CpmBridgePMemPostBusNumberReg)
            CreateDwordField (CpmdGpuBridgeUpStPostBuffer, 4,  CpmBridgeUpStPostBusNumberReg)
            CreateDwordField (CpmdGpuBridgeDnStPostBuffer, 4,  CpmBridgeDnStPostBusNumberReg)

            CpmProgramRegister (Arg0, Arg1, Arg2, CpmdGpuBridgePMemPostBuffer, 2)
            ShiftRight (CpmBridgePMemPostBusNumberReg, 8, Local0)
            And (Local0, 0xFF, Local0)
            If (LNotEqual (CpmBridgeUpStPostBusNumberReg, 0)) {
                CpmProgramRegister (Local0, 0, 0, CpmdGpuBridgeUpStPostBuffer, 2)
                ShiftRight (CpmBridgeUpStPostBusNumberReg, 8, Local0)
                And (Local0, 0xFF, Local0)
            }
            If (LAnd (LNotEqual (CpmBridgeUpStPostBusNumberReg, 0), LNotEqual (CpmBridgeDnStPostBusNumberReg, 0))) {
                CpmProgramRegister (Local0, 0, 0, CpmdGpuBridgeDnStPostBuffer, 2)
                ShiftRight (CpmBridgeDnStPostBusNumberReg, 8, Local0)
                And (Local0, 0xFF, Local0)
            }
            CpmProgramRegister (Local0, 0, 0, CpmdGpuDevicePMemPostBuffer, 3)
        }

        // Disable AMD DGPU's Audio
        Method (CpmDisableDgpuAudio, 0, Serialized) {
            CreateQwordField (CpmdGpuDevicePMemPostBuffer,  4, CpmDevicePMemPostBar2)
            CreateDwordField (CpmdGpuDevicePMemPostBuffer, 12, CpmDevicePMemPostBar5)

            Store (CpmCheckDgpuVidDid (), Local0)
            If (LAnd (LGreaterEqual (Local0, 0x00), LLessEqual (Local0, 0x0F))) {
                // Trigger a SW SMI to Disable DGPU Audio
                CpmTriggerSmi (CpmdGpuAudioDisable, 0x00, 0x10)
            } ElseIf (LAnd (LGreaterEqual (Local0, 0x10), LLessEqual (Local0, 0x1F))) {
                // BAR5 - AMD Ellesmere, AMD Baffin, AMD Iceland(Weston), Tonga, Polaris22, AMD Lexa
                // Bit1 for STRAP_BIF_AUDIO_EN in RomStrapOffset 0x5418
                Store (CpmReadMem32 (And (CpmDevicePMemPostBar5, 0xFFFFFFF0), 0x5418, 0, 32), Local2)
                CpmWriteMem32 (And (CpmDevicePMemPostBar5, 0xFFFFFFF0), 0x5418, 0, 32, And (Local2, 0xFFFFFFFD))
            } ElseIf (LAnd (LGreaterEqual (Local0, 0x20), LLessEqual (Local0, 0xBF))) {
                // BAR5 - AMD Greenland, AMD Vega12
                // Bit28 for STRAP_FUNC_EN_DEV0_F1 in RomStrapOffset 0x34E0
                Store (CpmReadMem32 (And (CpmDevicePMemPostBar5, 0xFFFFFFF0), 0x34E0, 0, 32), Local2)
                CpmWriteMem32 (And (CpmDevicePMemPostBar5, 0xFFFFFFF0), 0x34E0, 0, 32, And (Local2, 0xEFFFFFFF))
            }
        }

        // Program DGPU & its Audio SVID/SDID
        Method (CpmProgramDgpuSsid, 0, Serialized) {
            CreateByteField (CpmDgpuPowerResourceBuffer, 3, CpmDgpuBus)
            CreateDwordField (CpmDgpuPowerResourceBuffer, 4, CpmDgpuSsidVid0)
            CreateDwordField (CpmDgpuPowerResourceBuffer, 8, CpmDgpuSsidVid1)

            Store (CpmCheckDgpuVidDid (), Local0)
            If (LAnd (LGreaterEqual (Local0, 0x00), LLessEqual (Local0, 0xBF))) {
                // All of AMD DGPU
                Store (0x7FFFFFFF, Local2)
                Or (Local2, 0x80000000, Local2)
                CpmWritePci32 (CpmDgpuBus, 0, 0, 0x4C, CpmDgpuSsidVid0)
                Store (CpmReadPci32 (CpmDgpuBus, 0, 1, 0), Local1)
                If (LAnd (LNotEqual (Local1, Local2), LNotEqual (CpmDgpuSsidVid1, Local2))) {
                    // Get saved dGPU HD_Audio subsystem vendor ID and subsystem ID and write it to the mirror register
                    CpmWritePci32 (CpmDgpuBus, 0, 1, 0x4C, CpmDgpuSsidVid1)
                }
            }
        }

        // Restore DGPU Bridge/Device MMIO Register
        //  Arg0 - Bus Num of Gfx Bridge
        //  Arg1 - Device Num of Gfx Bridge
        //  Arg2 - Function Num of Gfx Bridge
        Method (CpmRestoreGfxResource, 3) {
            CreateByteField (CpmDgpuPowerResourceBuffer, 3, CpmDgpuBus)
            CreateDwordField (CpmdGpuBridgePMemPostBuffer, 4,  CpmBridgePMemPostBusNumberReg)
            CreateDwordField (CpmdGpuBridgeUpStPostBuffer, 4,  CpmBridgeUpStPostBusNumberReg)
            CreateDwordField (CpmdGpuBridgeDnStPostBuffer, 4,  CpmBridgeDnStPostBusNumberReg)

            CpmProgramRegister (CpmDgpuBus, 0, 0, CpmdGpuDevicePMemSaveBuffer, 5)
            If (LAnd (LNotEqual (CpmBridgeUpStPostBusNumberReg, 0), LNotEqual (CpmBridgeDnStPostBusNumberReg, 0))) {
                ShiftRight (CpmBridgeUpStPostBusNumberReg, 8, Local0)
                And (Local0, 0xFF, Local0)
                CpmProgramRegister (Local0, 0, 0, CpmdGpuBridgeDnStSaveBuffer, 4)
            }
            If (LNotEqual (CpmBridgeUpStPostBusNumberReg, 0)) {
                ShiftRight (CpmBridgePMemPostBusNumberReg, 8, Local0)
                And (Local0, 0xFF, Local0)
                CpmProgramRegister (Local0, 0, 0, CpmdGpuBridgeUpStSaveBuffer, 4)
            }
            CpmProgramRegister (Arg0, Arg1, Arg2, CpmdGpuBridgePMemSaveBuffer, 4)
        }

        Mutex (EEBC, 0)

        Method (CpmDgpuSetPower, 1) {
            Acquire (EEBC, 0xFFFF)
            CreateByteField (CpmDgpuPowerResourceBuffer, 0, CpmDgpuPowerResourceDeviceId)
            CreateByteField (CpmDgpuPowerResourceBuffer, 1, CpmBridgeDevice)
            CreateByteField (CpmDgpuPowerResourceBuffer, 2, CpmBridgeFunction)
            CreateByteField (CpmDgpuPowerResourceBuffer, 3, CpmDgpuBus)
            CreateDwordField (CpmDgpuPowerResourceBuffer, 4, CpmDgpuSsidVid0)
            CreateDwordField (CpmDgpuPowerResourceBuffer, 8, CpmDgpuSsidVid1)

            Name (CpmDgpuD3ColdHotPlugOK, 0)
            Name (CpmDgpuD3ColdHotPlugMode, 0)
            Name (CpmNonEvalDgpuSupport, 0)
            Name (CpmDgpuPmeTurnOffSupport, 0)
            If (LGreaterEqual (CpmSbChipId, CPM_FCH_REVISION_ID_ZP)) {
                And (ShiftRight (CpmReadTable (CpmMainTable, Add (CpmDisplayFeature, 3)), 0), 1, CpmDgpuPmeTurnOffSupport)  // BIT24: PmeTurnOffSupport
            }
            And (ShiftRight (CpmReadTable (CpmMainTable, Add (CpmDisplayFeature, 2)), 5), 1, CpmDgpuD3ColdHotPlugMode)      // BIT21: DgpuHotPlugMode DGPU HotPlug Mode - 0: Basic Mode, 1: Enhanced Mode
            And (ShiftRight (CpmReadTable (CpmMainTable, Add (CpmDisplayFeature, 2)), 6), 1, CpmNonEvalDgpuSupport)     // BIT22: NonEvalDgpuSupport

            If (LNotEqual (CpmDgpuD3ColdHotPlugMode, 1)) {
                // Only for HotPlugBasic
                Store (Buffer (5) {}, Local7)
                CreateWordField (Local7, 0, CpmStructureSize2)                  // Structure size field
                CreateField (Local7, 16, 3, CpmFunctionNumber)                  // func field
                CreateField (Local7, 19, 5, CpmDeviceNumber)                    // dev field
                CreateByteField (Local7, 3, CpmBusNumber)                       // bus field
                CreateByteField (Local7, 4, CpmHotplugStatus)                   // hotplug field
                Store (5, CpmStructureSize2)                                    // size
                Store (0, CpmBusNumber)                                         // bus 0
                Store (CpmBridgeDevice, Local0)
                Store (Local0, CpmDeviceNumber)                                 // device
                Store (CpmBridgeFunction, Local0)
                Store (Local0, CpmFunctionNumber)                               // function
            }

            If (LOr (LEqual (CpmSbChipId, CPM_FCH_REVISION_ID_RN), LOr (LEqual (CpmSbChipId, CPM_FCH_REVISION_ID_RV), LEqual (CpmSbChipId, CPM_FCH_REVISION_ID_RV2)))) {
                // Only for RV, RV2 & RN
                Store (Buffer (8) {}, Local3)
                CreateWordField (Local3, 0, CpmAlibStructureSize)               // Buffer Size
                CreateByteField (Local3, 2, CpmAlibSubFunction)                 // DPTCi Sub Function
                CreateDwordField (Local3, 3, CpmAlibControlValue)               // DPTCi Control Value
                Store (7, CpmAlibStructureSize)                                 // Size of Buffer
                Store (0x10, CpmAlibSubFunction)                                // START/STOP DGPU CONTROL
            }

            Store (CpmReadTable (CpmDisplayFeatureTable, CpmDisplayFeatureMacoGpio), CpmDgpuD3ColdMacoGpio)
            Store (CpmReadTable (CpmDisplayFeatureTable, CpmDisplayFeatureMxmPwrEnGpio), CpmDgpuD3ColdMxmPwrEnGpio)
            Store (CpmReadTable (CpmDisplayFeatureTable, CpmDisplayFeatureTimeMacoUpPwrDn), CpmDgpuD3ColdTimeMacoUpPwrDn)
            Store (CpmReadTable (CpmDisplayFeatureTable, CpmDisplayFeatureTimePwrDnRstDn), CpmDgpuD3ColdTimePwrDnRstDn)
            Store (CpmReadTable (CpmDisplayFeatureTable, CpmDisplayFeatureTimePwrUpRstUp), CpmDgpuD3ColdTimePwrUpRstUp)
            Store (CpmReadTable (CpmDisplayFeatureTable, CpmDisplayFeatureTimeRstUpMacoDn), CpmDgpuD3ColdTimeRstUpMacoDn)

            Add (Add (CpmAcpiMmioBaseAddr, 0x1502), Multiply (And (CpmDgpuD3ColdMacoGpio, 0xFF), 4), Local0)
            OperationRegion(vaMM, SystemMemory, Local0, 0x1)
            Field(vaMM, ByteAcc, NoLock, Preserve) {
                P011, 8,
            }
            Add (Add (CpmAcpiMmioBaseAddr, 0x1502), Multiply (And (CpmDgpuD3ColdMxmPwrEnGpio, 0xFF), 4), Local0)
            OperationRegion(vaNN, SystemMemory, Local0, 0x1)
            Field(vaNN, ByteAcc, NoLock, Preserve) {
                P141, 8,
            }

            If (LEqual (CpmNonEvalDgpuSupport, 1)) {
                Store (1, Local6)
            } Else {
                Store (CpmGetDeviceStatus (CpmDgpuPowerResourceDeviceId), Local6)
            }

            CpmClearPresenceDetectChangeBit (0, CpmBridgeDevice, CpmBridgeFunction) // Clear presence detect change bit. Set Reg0x70 Bit3 = 0 and Reg0x70 Bit19 = 1.

            IF (LEqual (CpmCheckDeviceResetState (CpmDgpuPowerResourceDeviceId, Arg0), 0)) {
                IF (LAnd (Arg0, Local6)) {
                    // Power on discrete graphics
                    CpmSetPostCode (CpmTpDgpuPowerOnBegin)

                    If (LEqual (\_SB.MACO, 1)) {
                        If (LLess (CpmDgpuD3ColdMxmPwrEnGpio, 0x100)) {
                            Store (0xC4, P141)                                      // Put MXM_POWER_ENABLE to high
                        } Else {
                            CpmWriteGpio (CpmDgpuD3ColdMxmPwrEnGpio, 1)             // Put MXM_POWER_ENABLE to high
                        }
                        Sleep (CpmDgpuD3ColdTimePwrUpRstUp)                         // MACO Exit  (ms): PWR_EN assert to PERSTb deassert      // Min: 20ms
                        CpmSetDeviceReset (CpmDgpuPowerResourceDeviceId, 1)         // De-assert MXM Reset
                        Sleep (CpmDgpuD3ColdTimeRstUpMacoDn)                        // MACO Exit  (ms): PERSTb deassert to MACO_EN deassert   // Min: 1ms
                        If (LLess (CpmDgpuD3ColdMacoGpio, 0x100)) {
                            Store (0x84, P011)                                      // Put MACO_EN to low
                        } Else {
                            CpmWriteGpio (CpmDgpuD3ColdMacoGpio, 0)                 // Put MACO_EN to low
                        }
                        Store (0, \_SB.MACO)
                    } Else {
                        CpmSetDeviceReset (CpmDgpuPowerResourceDeviceId, 0)         // Assert MXM Reset
                        CpmSetDevicePower (CpmDgpuPowerResourceDeviceId, 1)         // Power on MXM
                        Sleep (32)                                                  // Delay 32 ms
                        CpmSetDeviceReset (CpmDgpuPowerResourceDeviceId, 2)         // Delay for MXM Reset
                        CpmSetDeviceReset (CpmDgpuPowerResourceDeviceId, 1)         // De-assert MXM Reset
                        Sleep (100)                                                 // Delay 100 ms
                    }

                    If (LEqual (CpmDgpuPmeTurnOffSupport, 1)) {
                        CpmWakeLink (CpmBridgeDevice, CpmBridgeFunction, 1)
                    }
                    CpmSetPostCode (CpmTpDgpuPowerOnBeforePcieTraining)

                    Store (1, CpmDgpuD3ColdHotPlugOK)

                    If (LEqual (CpmDgpuD3ColdHotPlugMode, 1)) {
                        // Only for HotPlugEnhanced
                        If (LEqual (CpmDgpuPmeTurnOffSupport, 0)) {
                            // Enable Link
                            Store (CpmReadPci (0, CpmBridgeDevice, CpmBridgeFunction, 0x68, 0, 8), Local1)
                            CpmWritePci (0, CpmBridgeDevice, CpmBridgeFunction, 0x68, 0, 8, And (Local1, 0xEF))
                            Sleep (24)                                              // Delay 24 ms
                            Store (CpmRetrainPcieLink (0, CpmBridgeDevice, CpmBridgeFunction), Local1)
                        }

                        // Check DL_ACTIVE = 1 and LINK_TRAINING = 0
                        Store (0, Local1)
                        Store (5051, Local2)
                        While ( LAnd ( LNotEqual (And (Local1, 0x28), 0x20), LGreater (Local2, 0) ) ) {
                            CpmSetPostCode (CpmTpDgpuPowerOnUnderPcieTraining)
                            Store (CpmReadPci (0, CpmBridgeDevice, CpmBridgeFunction, 0x6B, 0, 8), Local1)
                            Store (Subtract (Local2, 1), Local2)
                            Stall (99)                                              // 99us * 5051 = Max 500ms time out
                        } // End of While (LNotEqual (And (Local1, 0x28), 0x20))

                    } Else { // End of If (LEqual (CpmDgpuD3ColdHotPlugMode, 1))
                        // Only for HotPlugBasic
                        // Pcie link training-retraining check sequence
                        Sleep (20)                                                  // spec needs up to 20ms delay after lane power up
                                                                                    // allow for system interrupts by splitting the 200ms delay
                                                                                    // Wait for PCIE Bridge stability as per spec
                        // Enable training
                        Store (1, CpmHotplugStatus)                                 // plug in
                        Store (\_SB.ALIB (6, Local7), Local6)                       // notify plug event

                        If (LLess (CpmSbChipId, CPM_FCH_REVISION_ID_ZP)) {
                            Store (0, CpmDgpuD3ColdHotPlugOK)                       // Assume card not working
                            Store (0, Local2)                                       // master loop counter
                            While (LLess (Local2, 15)) {
                                CpmClearPresenceDetectChangeBit (0, CpmBridgeDevice, CpmBridgeFunction) // Clear presence detect change bit. Set Reg0x70 Bit3 = 0 and Reg0x70 Bit19 = 1.
                                Store (1, Local4)                                   // Check Training State == 0x10 for up to 1 second
                                Store (200, Local5)
                                While (LAnd (Local4, Local5)) {
                                    Store (CpmReadPcieRegister (0, CpmBridgeDevice, CpmBridgeFunction, 0xA5), Local0)
                                    And (Local0, 0x7F, Local0)
                                    If (LAnd (LGreaterEqual (Local0, 0x10), LNotEqual (Local0, 0x7F))) {
                                        Store (0, Local4)
                                    } Else {
                                        Sleep (5)
                                        Decrement (Local5)
                                    }
                                } // End of While (LAnd (Local4, Local5))

                                If (LNot (Local4)) {                                // Timeout checking Training State?
                                    // Check if Data Link Negotiation is done(Bit1=0)
                                    Store (CpmCheckVirtualChannelNegotiationPending (0, CpmBridgeDevice, CpmBridgeFunction), Local5)

                                    If (Local5) {
                                        CpmReconfigPcieLink (0, CpmBridgeDevice, CpmBridgeFunction) // dGPU behind bridge 2
                                        Sleep (5)                                   // Delay 5ms after re-train
                                        Increment (Local2)                          // Increment master loop counter
                                    } Else {
                                        // Device training OK
                                        Store (0, Local0)                           // Do Common Clock re-train
                                        If (LEqual (CpmRetrainPcieLink (0, CpmBridgeDevice, CpmBridgeFunction), Ones)) {
                                            Store (1, Local0)
                                        }
                                        If (Local0) {
                                            Store (1, CpmDgpuD3ColdHotPlugOK)
                                            Store (16, Local2)
                                        } Else {
                                            Store (0, CpmDgpuD3ColdHotPlugOK)
                                            Store (16, Local2)
                                        }
                                    }
                                } Else {
                                    Store (16, Local2)
                                }
                            } // End of While (LLess (Local2, 15))

                            If (LNot (CpmDgpuD3ColdHotPlugOK)) {                    // Failure
                                CpmSetPostCode (CpmTpDgpuPowerOnPcieTrainingFailed)

                                // Do dummy PCI CFG read of device behind bridge to get State machine back to detect mode
                                Store (CpmReadPci32 (CpmDgpuBus, 0, 0, 0), Local1)
                                Sleep (10)
                                Store (1, Local4)
                                Store (5, Local5)
                                While (LAnd (Local4, Local5)) {
                                    Store (CpmReadPcieRegister (0, CpmBridgeDevice, CpmBridgeFunction, 0xA5), Local0)
                                    And (Local0, 0x7F, Local0)
                                    If (LOr (LLessEqual (Local0, 0x04), LEqual (Local0, 0x1F))) {
                                        Store (0, Local4)
                                    } Else {
                                        Store (CpmReadPci32 (CpmDgpuBus, 0, 0, 0), Local0)
                                        Sleep (5)
                                        Decrement (Local5)
                                    }
                                } // End of While (LAnd (Local4, Local5))
                                Store (0, CpmHotplugStatus)                         // plug out
                                \_SB.ALIB (6, Local7)                               // notify plug event
                            } // End of If (LNot (CpmDgpuD3ColdHotPlugOK))
                        } // End of If (LLess (CpmSbChipId, CPM_FCH_REVISION_ID_ZP))
                    } // End of If (LNotEqual (CpmDgpuD3ColdHotPlugMode, 1))

                    If (LEqual (CpmDgpuPmeTurnOffSupport, 1)) {
                        CpmWakeLink (CpmBridgeDevice, CpmBridgeFunction, 0)
                    }
                    CpmSetPostCode (CpmTpDgpuPowerOnAfterPcieTraining)
                    If (LEqual (CpmDgpuD3ColdHotPlugOK, 1)) {
                        Store (0x7FFFFFFF, Local6)
                        Or (Local6, 0x80000000, Local6)
                        Store (CpmReadPci32 (0, CpmBridgeDevice, CpmBridgeFunction, 0x54), Local1)
                        CpmWritePci32 (0, CpmBridgeDevice, CpmBridgeFunction, 0x54, And (Local1, 0xFFFF7FFC)) // Set to D0 state
                        Store (CpmReadPci (0, CpmBridgeDevice, CpmBridgeFunction, 0x19, 0, 8), Local2)
                        Store (1, Local4)
                        Store (40, Local5)                                          // 25ms * 40 = wait max 1000ms
                        While (LAnd (Local4, Local5)) {
                            Store (CpmReadPci32 (Local2, 0, 0, 0), Local0)
                            If (LNotEqual (Local0, Local6)) {
                                Store (CpmCheckDgpuVidDid (), Local0)
                                If (LAnd (LGreaterEqual (Local0, 0x00), LLessEqual (Local0, 0xBF))) {
                                    // All of AMD DGPU
                                    CpmSaveGfxResource (0, CpmBridgeDevice, CpmBridgeFunction)
                                    CpmProgramGfxResource (0, CpmBridgeDevice, CpmBridgeFunction)
                                    If (LNotEqual (CpmdGpuAudioDisable, 0)) {
                                        CpmDisableDgpuAudio ()
                                    }
                                    CpmProgramDgpuSsid ()
                                    CpmRestoreGfxResource (0, CpmBridgeDevice, CpmBridgeFunction)
                                }
                                Store (0, Local4)
                            } Else {
                                Sleep (25)                                          // 25ms * 40 = wait max 1000ms
                                Decrement (Local5)
                            }
                        } // End of While (LAnd (Local4, Local5))
                        CpmWritePci32 (0, CpmBridgeDevice, CpmBridgeFunction, 0x54, And (Local1, 0xFFFF7FFF)) // Restore to original state
                    } // End of If (LEqual (CpmDgpuD3ColdHotPlugOK, 1))

                    If (LOr (LEqual (CpmSbChipId, CPM_FCH_REVISION_ID_RV), LEqual (CpmSbChipId, CPM_FCH_REVISION_ID_RV2))) {
                        Store (CpmCheckDgpuVidDid (), Local0)
                        If (LAnd (LGreaterEqual (Local0, 0x00), LLessEqual (Local0, 0xBF))) {
                            // All of AMD DGPU
                            // Only for RV
                            Store (1, CpmAlibControlValue)                              // 1 to START
                            \_SB.ALIB (0x0C, Local3)
                        }
                    } Else {
                        If (LEqual (CpmSbChipId, CPM_FCH_REVISION_ID_RN)) {
                            Store (CpmCheckDgpuVidDid (), Local0)
                            If (LAnd (LGreaterEqual (Local0, 0x00), LLessEqual (Local0, 0xBF))) {
                                // All of AMD DGPU
                                // Only for RN
                                Store (1, CpmAlibControlValue)                      // 1 to START
                                \_SB.ALIB (0x0C, Local3)
                            }
                        }
                    }

                    Store (1, \_SB.PCI0.PB2.CpmDgpuD3ColdHpdSupport)
                    CpmSetPostCode (CpmTpDgpuPowerOnEnd)
                    // End of Power On dGPU

                } Else {
                    // Power Off dGPU
                    CpmSetPostCode (CpmTpDgpuPowerOffBegin)
                    // BIT23: DgpuD3ColdHpdSupport - DGPU D3Cold HPD Support
                    And (ShiftRight (CpmReadTable (CpmMainTable, Add (CpmDisplayFeature, 2)), 7), 1, \_SB.PCI0.PB2.CpmDgpuD3ColdHpdSupport)

                    If (LOr (LEqual (CpmSbChipId, CPM_FCH_REVISION_ID_RV), LEqual (CpmSbChipId, CPM_FCH_REVISION_ID_RV2))) {
                        Store (CpmCheckDgpuVidDid (), Local0)
                        If (LAnd (LGreaterEqual (Local0, 0x00), LLessEqual (Local0, 0xBF))) {
                            // All of AMD DGPU
                            // Only for RV
                            Store (0, CpmAlibControlValue)                              // 0 to STOP
                            \_SB.ALIB (0x0C, Local3)
                        }
                    } Else {
                        If (LEqual (CpmSbChipId, CPM_FCH_REVISION_ID_RN)) {
                            Store (CpmCheckDgpuVidDid (), Local0)
                            If (LAnd (LGreaterEqual (Local0, 0x00), LLessEqual (Local0, 0xBF))) {
                                // All of AMD DGPU
                                // Only for RN
                                Store (0, CpmAlibControlValue)                      // 0 to STOP
                                \_SB.ALIB (0x0C, Local3)
                            }
                        }
                    }

                    If (LEqual (CpmDgpuD3ColdHotPlugMode, 1)) {
                        // Only for HotPlugEnhanced
                        // Set endpoint device PM_CONTROL to Disabled (0)
                        Store (CpmReadPci32 (0, CpmBridgeDevice, CpmBridgeFunction, 0x54), Local1)
                        CpmWritePci32 (0, CpmBridgeDevice, CpmBridgeFunction, 0x54, And (Local1, 0xFFFF7FFC)) // Set to D0 state
                        Sleep (1)                                                   // Delay 1 ms
                        Store (CpmReadPci (0, CpmBridgeDevice, CpmBridgeFunction, 0x19, 0, 8), Local2)
                        CpmSetPcieAspm (Local2, 0, 0, 0)
                        Store (CpmGetPcieAspm (Local2, 0, 0), Local3)               // Read PM_CONTROL back once
                        CpmWritePci32 (0, CpmBridgeDevice, CpmBridgeFunction, 0x54, And (Local1, 0xFFFF7FFF)) // Restore to original state

                        If (LEqual (CpmDgpuPmeTurnOffSupport, 0)) {
                            // Disable Link
                            Store (CpmReadPci (0, CpmBridgeDevice, CpmBridgeFunction, 0x68, 0, 8), Local1)
                            CpmWritePci (0, CpmBridgeDevice, CpmBridgeFunction, 0x68, 0, 8, Or (Local1, 0x10))
                            Sleep (24)                                              // Delay 24 ms
                        }
                    } Else { // End of If (LEqual (CpmDgpuD3ColdHotPlugMode, 1))
                        // Only for HotPlugBasic
                        Store (CpmReadPci32 (0, CpmBridgeDevice, CpmBridgeFunction, 0x54), Local1)
                        CpmWritePci32 (0, CpmBridgeDevice, CpmBridgeFunction, 0x54, And (Local1, 0xFFFF7FFC)) // Set to D0 state

                        Store (0, CpmHotplugStatus)                                 // plug out
                        \_SB.ALIB (6, Local7)                                       // notify plug event
                        CpmWritePci32 (0, CpmBridgeDevice, CpmBridgeFunction, 0x54, And (Local1, 0xFFFF7FFF)) // Restore to original state
                    }

                    If (LEqual (CpmDgpuPmeTurnOffSupport, 1)) {
                        CpmSendPmeTurnOff (CpmBridgeDevice, CpmBridgeFunction)
                    }
                    CpmSetPostCode (CpmTpDgpuPowerOffBeforePowerOff)

                    If (LEqual (\_SB.MACO, 1)) {
                        If (LLess (CpmDgpuD3ColdMacoGpio, 0x100)) {
                            Store (0xC4, P011)                                      // Put MACO_EN to high
                        } Else {
                            CpmWriteGpio (CpmDgpuD3ColdMacoGpio, 1)                 // Put MACO_EN to high
                        }
                        Stall (CpmDgpuD3ColdTimeMacoUpPwrDn)                        // MACO Entry (us): MACO_EN assert to PWR_EN deassert     // Min: 10us
                        If (LLess (CpmDgpuD3ColdMxmPwrEnGpio, 0x100)) {
                            Store (0x84, P141)                                      // Put MXM_POWER_ENABLE to low
                        } Else {
                            CpmWriteGpio (CpmDgpuD3ColdMxmPwrEnGpio, 0)             // Put MXM_POWER_ENABLE to low
                        }
                        Sleep (CpmDgpuD3ColdTimePwrDnRstDn)                         // MACO Entry (ms): PWR_EN deassert to PERSTb assert      // Min: 20ms
                        CpmSetDeviceReset (CpmDgpuPowerResourceDeviceId, 0)         // Assert MXM Reset
                    } Else {
                        CpmSetDeviceReset (CpmDgpuPowerResourceDeviceId, 0)         // Assert MXM Reset
                        Sleep (10)                                                  // Delay 10 ms
                        CpmSetDevicePower (CpmDgpuPowerResourceDeviceId, 0)         // Power off MXM
                    }

                    // The link training-retraining check sequence goes here
                    // Note: Powering down the discrete graphics will result in a change-detection
                    // of the Plug and Play resources and trigger an OS PNP Scan.  This scan
                    // may have adverse effects (eg system timing) from the Vista RTM OS and various
                    // hot-fixes (Vista SP1) or updated drivers may be needed.
                    CpmClearPresenceDetectChangeBit (0, CpmBridgeDevice, CpmBridgeFunction) // Clear presence detect change bit. Set Reg0x70 Bit3 = 0 and Reg0x70 Bit19 = 1.
                    If (LEqual (CpmDgpuPmeTurnOffSupport, 0)) {
                    Store (CpmReadPci32 (CpmDgpuBus, 0, 0, 0), Local1)              // Do dummy PCI CFG read of device behind bridge
                    Sleep (10)
                    }
                    If (LLess (CpmSbChipId, CPM_FCH_REVISION_ID_ZP)) {
                        Store (1, Local4)
                        Store (5, Local5)
                        While (LAnd (Local4, Local5)) {
                            Store (CpmReadPcieRegister (0, CpmBridgeDevice, CpmBridgeFunction, 0xA5), Local0)
                            And (Local0, 0x7F, Local0)
                            If (LOr (LLessEqual (Local0, 0x04), LEqual (Local0, 0x1F))) {
                                Store (0, Local4)
                            } Else {
                                Store (CpmReadPci32 (CpmDgpuBus, 0, 0, 0), Local1)
                                Sleep (5)
                                Decrement (Local5)
                            }
                        } // End of While (LAnd (Local4, Local5))
                    } // End of If (LLess (CpmSbChipId, CPM_FCH_REVISION_ID_ZP))
                    CpmSetPostCode (CpmTpDgpuPowerOffEnd)
                    Store (2, CpmDgpuD3ColdHotPlugOK)
                } // End of Power Off dGPU
            } // End of IF (LEqual (CpmCheckDeviceResetState (CpmDgpuPowerResourceDeviceId, Arg0), 0))
            Release (EEBC)
        } // End of Method (CpmDgpuSetPower, 1)

        PowerResource (CpmDgpuPowerResourceVcc, 0, 0) {
            Name (CpmDgpuPowerResourceVccFlag, 1)
            Method (_STA) {
                Return (CpmDgpuPowerResourceVccFlag)
            }
            Method (_ON) {
                if (LEqual (CpmDgpuPowerResourceVccFlag, 0)) {
                    CpmDgpuSetPower (CPM_POWER_ON)
                }
                Store (0x01, CpmDgpuPowerResourceVccFlag)
            }
            Method (_OFF) {
                if (LEqual (CpmDgpuPowerResourceVccFlag, 1)) {
                    CpmDgpuSetPower (CPM_POWER_OFF)
                }
                Store (0x00, CpmDgpuPowerResourceVccFlag)
            }
        }

        Name (XPR0, Package() {CpmDgpuPowerResourceVcc})                        // Power resources required for D0
        Name (XPR2, Package() {CpmDgpuPowerResourceVcc})                        // Power resources required for D2
        Name (XPR3, Package() {CpmDgpuPowerResourceVcc})                        // Power resources required for D3
        Name (XS0W, 4)
    } // End of Scope(\_SB.PCI0.PB2)

    Scope(\_SB.PCI0.PB2.SWUS) {
        PowerResource (CpmDgpuPowerResourceVcc, 0, 0) {
            Name (CpmDgpuPowerResourceVccFlag, 1)
            Method (_STA) {
                Return (CpmDgpuPowerResourceVccFlag)
            }
            Method (_ON) {
                Store (0x01, CpmDgpuPowerResourceVccFlag)
            }
            Method (_OFF) {
                Store (0x00, CpmDgpuPowerResourceVccFlag)
            }
        }

        Name (XPR0, Package() {CpmDgpuPowerResourceVcc})                        // Power resources required for D0
        Name (XPR2, Package() {CpmDgpuPowerResourceVcc})                        // Power resources required for D2
        Name (XPR3, Package() {CpmDgpuPowerResourceVcc})                        // Power resources required for D3
        Name (XS0W, 4)
    } // End of Scope(\_SB.PCI0.PB2.SWUS)

    Scope(\_SB.PCI0.PB2.SWUS.SWDS) {
        PowerResource (CpmDgpuPowerResourceVcc, 0, 0) {
            Name (CpmDgpuPowerResourceVccFlag, 1)
            Method (_STA) {
                Return (CpmDgpuPowerResourceVccFlag)
            }
            Method (_ON) {
                Store (0x01, CpmDgpuPowerResourceVccFlag)
            }
            Method (_OFF) {
                Store (0x00, CpmDgpuPowerResourceVccFlag)
            }
        }

        Name (XPR0, Package() {CpmDgpuPowerResourceVcc})                        // Power resources required for D0
        Name (XPR2, Package() {CpmDgpuPowerResourceVcc})                        // Power resources required for D2
        Name (XPR3, Package() {CpmDgpuPowerResourceVcc})                        // Power resources required for D3
        Name (XS0W, 4)
    } // End of Scope(\_SB.PCI0.PB2.SWUS.SWDS)
}