/*****************************************************************************
 *
 * Copyright 2012 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
  "WirelessButton.aml",   // Output file
  "SSDT",                 // Signature
  0x01,                   // SSDT Revision
  "AMD",                  // OEM ID
  "CPMWLBTN",             // OEM Table ID
  0x1                     // OEM Revision
  )
{
  #define CPM_PCIE_WIRELESS_BUTTON_ASL

  #include "CmnDef.asi"
  #include "CmnExt.asi"
  #include "PostCode.asi"

  Scope (\_GPE) {                                 // General-Purpose Event
    Name (CpmWirelessButtonCurrentStatus, 0)      // Radio SW ON-OFF status

    Method (CpmWirelessButtonEventMethod) {
      Store (0, Local7)
      Store (CpmSaveContextTable, Local0)
      If (Local0) {
        Store (CpmReadTable (CpmSaveContextTable, CpmSaveContextBufferType), Local0)
        Store (CpmReadTable (CpmSaveContextTable, CpmSaveContextBufferOffset), Local1)
        Add (CpmAcpiMmioBaseAddr, Add (Multiply (Local0, 0x100), Local1), Local1)
        CpmWriteMem8 (Local1, CpmWirelessButtonStatus, 0, 8, CpmWirelessButtonCurrentStatus)
      }
      Xor (CpmWirelessButtonCurrentStatus, 0x01, CpmWirelessButtonCurrentStatus)
      Store (CpmWirelessButtonTable, Local1)
      Store (CpmReadTable (CpmMainTable, CpmWirelessButtonEn), Local2)
      If (LAnd (Local1, Local2)) {
        If (CpmWirelessButtonCurrentStatus) {     // OFF, on boot up, at least one wireless device is on.
          CpmSetPostCode (CpmTpWirelessButtonEventPowerOffBegin)

          // Power off Antenna
          CpmSetDevicePower (CpmReadMem32 (CpmWirelessButtonTable, CpmWirelessButtonDeviceIdRadio, 0, 8), 0)
          CpmSetDevicePower (CpmReadMem32 (CpmWirelessButtonTable, CpmWirelessButtonDeviceIdOther, 0, 8), 0)

          If (LEqual (Local2, 2)) {               // Power Control Enabled, Power Off devices
            Store (CpmReadMem8 (CpmWirelessButtonTable, CpmWirelessButtonBridge, 0, 5), Local0)
            Store (CpmReadMem8 (CpmWirelessButtonTable, CpmWirelessButtonBridge, 5, 3), Local1)
            If (LOr (Local0, Local1)) {
              CpmPcieHotplug (Local0, Local1, 0, 0)
              Or (Local7, 1, Local7)
            }

            Store (CpmReadMem8 (CpmWirelessButtonTable, Add (CpmWirelessButtonBridge, 1), 0, 5), Local0)
            Store (CpmReadMem8 (CpmWirelessButtonTable, Add (CpmWirelessButtonBridge, 1), 5, 3), Local1)
            If (LOr (Local0, Local1)) {
              CpmPcieHotplug (Local0, Local1, 0, 0)
              Or (Local7, 2, Local7)
            }

            Store (CpmReadMem8(CpmWirelessButtonTable, Add (CpmWirelessButtonBridge, 2), 0, 5), Local0)
            Store (CpmReadMem8(CpmWirelessButtonTable, Add (CpmWirelessButtonBridge, 2), 5, 3), Local1)
            If (LOr (Local0, Local1)) {
              CpmPcieHotplug (Local0, Local1, 0, 0)
              Or (Local7, 4, Local7)
            }

            Store (CpmReadMem8 (CpmWirelessButtonTable, Add (CpmWirelessButtonBridge, 3), 0, 5), Local0)
            Store (CpmReadMem8 (CpmWirelessButtonTable, Add (CpmWirelessButtonBridge, 3), 5, 3), Local1)
            If (LOr (Local0, Local1)) {
              CpmPcieHotplug (Local0, Local1, 0, 0)
              Or (Local7, 8, Local7)
            }

            CpmSetDevicePower (CpmReadMem32 (CpmWirelessButtonTable, CpmWirelessButtonDeviceIdPower, 0, 8), 0)
            CpmSetPostCode (CpmTpWirelessButtonEventPowerOffDevice)
          }
        } Else {                                  // ON
          CpmSetPostCode (CpmTpWirelessButtonEventPowerOnBegin)

          If (LEqual (Local2, 2)) {               // Power Control Enabled, Power Off devices
            CpmSetDevicePower (CpmReadMem32 (CpmWirelessButtonTable, CpmWirelessButtonDeviceIdPower, 0, 8), 1)
            Sleep (200)

            Store (CpmReadMem8 (CpmWirelessButtonTable, CpmWirelessButtonBridge, 0, 5), Local0)
            Store (CpmReadMem8 (CpmWirelessButtonTable, CpmWirelessButtonBridge, 5, 3), Local1)
            If (LOr (Local0, Local1)) {
              CpmPcieHotplug (Local0, Local1, 1, 0)
              Or (Local7, 1, Local7)
            }

            Store (CpmReadMem8 (CpmWirelessButtonTable, Add (CpmWirelessButtonBridge, 1), 0, 5), Local0)
            Store (CpmReadMem8 (CpmWirelessButtonTable, Add (CpmWirelessButtonBridge, 1), 5, 3), Local1)
            If (LOr (Local0, Local1)) {
              CpmPcieHotplug (Local0, Local1, 1, 0)
              Or (Local7, 2, Local7)
            }

            Store (CpmReadMem8 (CpmWirelessButtonTable, Add (CpmWirelessButtonBridge, 2), 0, 5), Local0)
            Store (CpmReadMem8 (CpmWirelessButtonTable, Add (CpmWirelessButtonBridge, 2), 5, 3), Local1)
            If (LOr (Local0, Local1)) {
              CpmPcieHotplug (Local0, Local1, 1, 0)
              Or (Local7, 4, Local7)
            }

            Store (CpmReadMem8 (CpmWirelessButtonTable, Add (CpmWirelessButtonBridge, 3), 0, 5), Local0)
            Store (CpmReadMem8 (CpmWirelessButtonTable, Add (CpmWirelessButtonBridge, 3), 5, 3), Local1)
            If (LOr (Local0, Local1)) {
              CpmPcieHotplug (Local0, Local1, 1, 0)
              Or (Local7, 8, Local7)
            }

            CpmSetPostCode (CpmTpWirelessButtonEventPowerOnDevice)
          }

          // antenna on
          CpmSetDevicePower (CpmReadMem32 (CpmWirelessButtonTable, CpmWirelessButtonDeviceIdRadio, 0, 8), 1)
          CpmSetDevicePower (CpmReadMem32 (CpmWirelessButtonTable, CpmWirelessButtonDeviceIdOther, 0, 8), 1)
        }
        If (And (Local7, 1)) {
          If (CondRefOf (\_SB.PCI0.CpmWirelessBridge0)) {
            Notify (\_SB.PCI0.CpmWirelessBridge0, 0x00)
          }
        }
        If (And (Local7, 2)) {
          If (CondRefOf (\_SB.PCI0.CpmWirelessBridge1)) {
            Notify (\_SB.PCI0.CpmWirelessBridge1, 0x00)
          }
        }
        If (And (Local7, 4)) {
          If (CondRefOf (\_SB.PCI0.CpmWirelessBridge2)) {
            Notify (\_SB.PCI0.CpmWirelessBridge2, 0x00)
          }
        }
        If (And (Local7, 8)) {
          If (CondRefOf (\_SB.PCI0.CpmWirelessBridge3)) {
            Notify (\_SB.PCI0.CpmWirelessBridge3, 0x00)
          }
        }
      }
    }
  }
}
