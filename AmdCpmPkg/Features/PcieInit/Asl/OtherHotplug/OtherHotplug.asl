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
  "OtherHotplug.aml",     // Output file
  "SSDT",                 // Signature
  0x01,                   // SSDT Revision
  "AMD",                  // OEM ID
  "CPMOTHPG",             // OEM Table ID
  0x1                     // OEM Revision
  )
{
  #define CPM_PCIE_OTHER_HOTPLUG_ASL

  #include "CmnDef.asi"
  #include "CmnExt.asi"
  #include "PostCode.asi"

  External(\_SB.PCI0.LPC0.EC0, DeviceObj)

  Scope (\_GPE) {                                 // General-Purpose Event
    Method (CpmOtherHotplugCard0EventMethod) {
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard0BridgeDevice), Local0)
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard0BridgeFunction), Local1)
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard0EventPin), Local2)
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard0DeviceId), Local3)
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard0HotPlugMode), Local5)

      If (CpmReadGevent (Local2)) {               // hot remove
        CpmSetPostCode (CpmTpOtherHotplugCard0RemoveEventBegin)
        CpmWriteGeventTriggerType (Local2, 0)
        CpmSetDeviceReset (Local3, 0)             // Assert Reset
        Sleep (10)                                // Delay
        CpmSetDevicePower (Local3, 0)             // Power Off
        Sleep (10)                                // Delay
        CpmSetDeviceClock (Local3, 0)             // Clock Off

        CpmPcieHotplug (Local0, Local1, 0, Local5)
        CpmSetPostCode (CpmTpOtherHotplugCard0RemoveEventEnd)
      } else {                                    // hot insert
        CpmWriteGeventTriggerType (Local2, 1)
        Store (CpmGetDeviceStatus (Local3), Local4)
        If (Local4) {
          CpmSetPostCode (CpmTpOtherHotplugCard0InsertEventBegin)
          CpmSetDeviceClock (Local3, 1)           // Clock On
          CpmSetDeviceReset (Local3, 0)           // Assert Reset
          CpmSetDevicePower (Local3, 1)
          Sleep (10)                              // Delay
          CpmSetDeviceReset (Local3, 2)           // Delay for Reset
          CpmSetDeviceReset (Local3, 1)           // De-assert Reset
          Sleep (10)                              // Delay
          CpmPcieHotplug (Local0, Local1, 1, Local5)
          CpmSetDeviceClock (Local3, 2)           // Clock On
          CpmSetPostCode (CpmTpOtherHotplugCard0InsertEventEnd)
        }
      }
      If (CondRefOf (\_SB.PCI0.CpmOtherHotplugCard0Bridge)) {
        Notify (\_SB.PCI0.CpmOtherHotplugCard0Bridge, 0x00)
      }
    }

    Method (CpmOtherHotplugCard1EventMethod) {
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard1BridgeDevice), Local0)
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard1BridgeFunction), Local1)
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard1EventPin), Local2)
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard1DeviceId), Local3)
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard1HotPlugMode), Local5)

      If (CpmReadGevent (Local2)) {               // hot remove
        CpmSetPostCode (CpmTpOtherHotplugCard1RemoveEventBegin)
        CpmWriteGeventTriggerType (Local2, 0)
        CpmSetDeviceReset (Local3, 0)             // Assert Reset
        Sleep (10)                                // Delay
        CpmSetDevicePower (Local3, 0)             // Power Off
        Sleep (10)                                // Delay
        CpmSetDeviceClock (Local3, 0)             // Clock Off

        CpmPcieHotplug (Local0, Local1, 0, Local5)
        CpmSetPostCode (CpmTpOtherHotplugCard1RemoveEventEnd)
      } else {                                    // hot insert
        CpmWriteGeventTriggerType (Local2, 1)
        Store (CpmGetDeviceStatus (Local3), Local4)
        If (Local4) {
          CpmSetPostCode (CpmTpOtherHotplugCard1InsertEventBegin)
          CpmSetDeviceClock (Local3, 1)           // Clock On
          CpmSetDeviceReset (Local3, 0)           // Assert Reset
          CpmSetDevicePower (Local3, 1)
          Sleep (10)                              // Delay
          CpmSetDeviceReset (Local3, 2)           // Delay for Reset
          CpmSetDeviceReset (Local3, 1)           // De-assert Reset
          Sleep (10)                              // Delay
          CpmPcieHotplug (Local0, Local1, 1, Local5)
          CpmSetDeviceClock (Local3, 2)           // Clock On
          CpmSetPostCode (CpmTpOtherHotplugCard1InsertEventEnd)
        }
      }
      If (CondRefOf (\_SB.PCI0.CpmOtherHotplugCard1Bridge)) {
        Notify (\_SB.PCI0.CpmOtherHotplugCard1Bridge, 0x00)
      }
    }
  }

  //
  // EC QEvent
  //
  Scope(\_SB.PCI0.LPC0.EC0) {
    //
    // CpmOtherHotplugCard0ConnectMethod
    //
    Method(CpmOtherHotplugCard0ConnectMethod, 0x0, Serialized) {
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard0BridgeDevice), Local0)
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard0BridgeFunction), Local1)
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard0DeviceId), Local3)
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard0HotPlugMode), Local5)
      Store (CpmGetDeviceStatus (Local3), Local4)
      If (Local4) {
        CpmSetPostCode (CpmTpOtherHotplugCard0InsertEventBegin)
        CpmSetDeviceClock (Local3, 1)           // Clock On
        CpmSetDeviceReset (Local3, 0)           // Assert Reset
        CpmSetDevicePower (Local3, 1)
        Sleep (10)                              // Delay
        CpmSetDeviceReset (Local3, 2)           // Delay for Reset
        CpmSetDeviceReset (Local3, 1)           // De-assert Reset
        Sleep (10)                              // Delay
        CpmPcieHotplug (Local0, Local1, 1, Local5)
        CpmSetDeviceClock (Local3, 2)           // Clock On
        CpmSetPostCode (CpmTpOtherHotplugCard0InsertEventEnd)
      }
      If (CondRefOf (\_SB.PCI0.CpmOtherHotplugCard0Bridge)) {
        Notify (\_SB.PCI0.CpmOtherHotplugCard0Bridge, 0x00)
      }
    } // End of Method(CpmOtherHotplugCard0ConnectMethod, 0x0, Serialized)

    //
    // CpmOtherHotplugCard0DisconnectMethod
    //
    Method(CpmOtherHotplugCard0DisconnectMethod, 0x0, Serialized) {
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard0BridgeDevice), Local0)
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard0BridgeFunction), Local1)
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard0DeviceId), Local3)
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard0HotPlugMode), Local5)
      CpmSetPostCode (CpmTpOtherHotplugCard0RemoveEventBegin)
      CpmSetDeviceReset (Local3, 0)             // Assert Reset
      Sleep (10)                                // Delay
      CpmSetDevicePower (Local3, 0)             // Power Off
      Sleep (10)                                // Delay
      CpmSetDeviceClock (Local3, 0)             // Clock Off
      CpmPcieHotplug (Local0, Local1, 0, Local5)
      CpmSetPostCode (CpmTpOtherHotplugCard0RemoveEventEnd)
      If (CondRefOf (\_SB.PCI0.CpmOtherHotplugCard0Bridge)) {
        Notify (\_SB.PCI0.CpmOtherHotplugCard0Bridge, 0x00)
      }
    } // End of Method(CpmOtherHotplugCard0DisconnectMethod, 0x0, Serialized)

    //
    // CpmOtherHotplugCard1ConnectMethod
    //
    Method(CpmOtherHotplugCard1ConnectMethod, 0x0, Serialized) {
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard1BridgeDevice), Local0)
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard1BridgeFunction), Local1)
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard1DeviceId), Local3)
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard1HotPlugMode), Local5)
      Store (CpmGetDeviceStatus (Local3), Local4)
      If (Local4) {
        CpmSetPostCode (CpmTpOtherHotplugCard1InsertEventBegin)
        CpmSetDeviceClock (Local3, 1)           // Clock On
        CpmSetDeviceReset (Local3, 0)           // Assert Reset
        CpmSetDevicePower (Local3, 1)
        Sleep (10)                              // Delay
        CpmSetDeviceReset (Local3, 2)           // Delay for Reset
        CpmSetDeviceReset (Local3, 1)           // De-assert Reset
        Sleep (10)                              // Delay
        CpmPcieHotplug (Local0, Local1, 1, Local5)
        CpmSetDeviceClock (Local3, 2)           // Clock On
        CpmSetPostCode (CpmTpOtherHotplugCard1InsertEventEnd)
      }
      If (CondRefOf (\_SB.PCI0.CpmOtherHotplugCard1Bridge)) {
        Notify (\_SB.PCI0.CpmOtherHotplugCard1Bridge, 0x00)
      }
    } // End of Method(CpmOtherHotplugCard1ConnectMethod, 0x0, Serialized)

    //
    // CpmOtherHotplugCard1DisconnectMethod
    //
    Method(CpmOtherHotplugCard1DisconnectMethod, 0x0, Serialized) {
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard1BridgeDevice), Local0)
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard1BridgeFunction), Local1)
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard1DeviceId), Local3)
      Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard1HotPlugMode), Local5)
      CpmSetPostCode (CpmTpOtherHotplugCard1RemoveEventBegin)
      CpmSetDeviceReset (Local3, 0)             // Assert Reset
      Sleep (10)                                // Delay
      CpmSetDevicePower (Local3, 0)             // Power Off
      Sleep (10)                                // Delay
      CpmSetDeviceClock (Local3, 0)             // Clock Off
      CpmPcieHotplug (Local0, Local1, 0, Local5)
      CpmSetPostCode (CpmTpOtherHotplugCard1RemoveEventEnd)
      If (CondRefOf (\_SB.PCI0.CpmOtherHotplugCard1Bridge)) {
        Notify (\_SB.PCI0.CpmOtherHotplugCard1Bridge, 0x00)
      }
    } // End of Method(CpmOtherHotplugCard1DisconnectMethod, 0x0, Serialized)

  } // End of Scope(\_SB.PCI0.LPC0.EC0)

  Scope (\_SB) {
    Name (CpmOtherHotplugCard0Connect, 0)       // Device 0 Connect ?
    Name (CpmOtherHotplugCard1Connect, 0)       // Device 1 Connect ?
    Method (CpmOtherHotplugCard_PTS, 1, Serialized) {
      if (LOr (LEqual (Arg0, 3), LEqual (Arg0, 4))) {
        CpmSetPostCode (CpmTpOtherHotplugCardPTSStart)
        Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCardNumber), Local0)
        Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard0DeviceId), Local3)
        Store (CpmGetDeviceStatus (Local3), CpmOtherHotplugCard0Connect)
        If (LEqual (Local0, 2)) {
          Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard1DeviceId), Local3)
          Store (CpmGetDeviceStatus (Local3), CpmOtherHotplugCard1Connect)
        }
        CpmSetPostCode (CpmTpOtherHotplugCardPTSEnd)
      }
    } // End of Method (CpmOtherHotplugCard_PTS)

    Method (CpmOtherHotplugCard_WAK, 1, Serialized) {
      if (LOr (LEqual (Arg0, 3), LEqual (Arg0, 4))) {
        CpmSetPostCode (CpmTpOtherHotplugCardWAKStart)
        Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCardNumber), Local0)
        Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard0DeviceId), Local3)
        If (LNotEqual (CpmGetDeviceStatus (Local3), CpmOtherHotplugCard0Connect)) {
          If (CondRefOf (\_SB.PCI0.CpmOtherHotplugCard0Bridge)) {
            Notify (\_SB.PCI0.CpmOtherHotplugCard0Bridge, 0x00)
          }
        }
        If (LEqual (Local0, 2)) {
          Store (CpmReadTable (CpmOtherHotplugCardTable, CpmOtherHotplugCard1DeviceId), Local3)
          If (LNotEqual (CpmGetDeviceStatus (Local3), CpmOtherHotplugCard1Connect)) {
            If (CondRefOf (\_SB.PCI0.CpmOtherHotplugCard1Bridge)) {
              Notify (\_SB.PCI0.CpmOtherHotplugCard1Bridge, 0x00)
            }
          }
        }
        CpmSetPostCode (CpmTpOtherHotplugCardWAKEnd)
      }
    } // End of Method (CpmOtherHotplugCard_WAK)
  } // End of Scope(\_SB)
}

