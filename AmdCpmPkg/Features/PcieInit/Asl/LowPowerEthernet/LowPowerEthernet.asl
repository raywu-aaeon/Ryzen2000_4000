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
  "LowPowerEthernet.aml", // Output file
  "SSDT",                 // Signature
  0x01,                   // SSDT Revision
  "AMD",                  // OEM ID
  "CPMLPETH",             // OEM Table ID
  0x1                     // OEM Revision
  )
{
  #define CPM_PCIE_LOW_POWER_ETHERNET_ASL

  #include "CmnDef.asi"
  #include "CmnExt.asi"
  #include "PostCode.asi"

  External (\_SB.PCI0.LPC0.EC0, DeviceObj)
  External (\_SB.PCI0.CpmLowPowerEthernetBridgeAslName.BCM5, DeviceObj)

  //
  // EC QEvent
  //
  Scope(\_SB.PCI0.LPC0.EC0) {
    Mutex(QMUX, 0)
    //
    // CpmLowPowerEthernetCablePlugOutMethod
    //
    Method(CpmLowPowerEthernetCablePlugOutMethod, 0x0, Serialized) {
      Acquire (QMUX, 0xFFFF)
      CpmSetPostCode (CpmTpLowPowerEthernetCablePlugOutBegin)
      Store (CpmReadTable (CpmLowPowerEthernetTable, CpmLowPowerEthernetLanLowPowerPin), Local2)
      If (LEqual (CpmReadGpio (Add (Local2, 0x200)), 0x0)) {
        If (CondRefOf (\_SB.PCI0.CpmLowPowerEthernetBridgeAslName.BCM5)) {
          Notify (\_SB.PCI0.CpmLowPowerEthernetBridgeAslName.BCM5, 0x03)
        }
      }
      CpmSetPostCode (CpmTpLowPowerEthernetCablePlugOutEnd)
      Release (QMUX)
    } // End of Method(CpmLowPowerEthernetCablePlugOutMethod, 0x0, Serialized)

    //
    // CpmLowPowerEthernetCablePlugInMethod
    //
    Method(CpmLowPowerEthernetCablePlugInMethod, 0x0, Serialized) {
      Acquire (QMUX, 0xFFFF)
      CpmSetPostCode (CpmTpLowPowerEthernetCablePlugInBegin)
      Store (CpmReadTable (CpmLowPowerEthernetTable, CpmLowPowerEthernetBridgeDevice), Local0)
      Store (CpmReadTable (CpmLowPowerEthernetTable, CpmLowPowerEthernetBridgeFunction), Local1)
      Store (CpmReadTable (CpmLowPowerEthernetTable, CpmLowPowerEthernetLanLowPowerPin), Local2)
      Store (CpmReadTable (CpmLowPowerEthernetTable, CpmLowPowerEthernetDeviceId), Local3)
      If (LEqual (CpmReadGpio (Add (Local2, 0x200)), 0x1)) {
        CpmWriteGpio (Add (Local2, 0x200), 0x0)
        Sleep (300)
        CpmSetDeviceClock (Local3, 1)           // Clock On
        Sleep (100)
        CpmSetDeviceReset (Local3, 0)           // Assert Reset
        Sleep (200)
        CpmSetDeviceReset (Local3, 1)           // De-assert Reset
        CpmPcieHotplug (Local0, Local1, 1, 1)
        Sleep (200)
        CpmSetDeviceClock (Local3, 2)           // Clock On
        If (CondRefOf (\_SB.PCI0.CpmLowPowerEthernetBridgeAslName.BCM5)) {
          Notify (\_SB.PCI0.CpmLowPowerEthernetBridgeAslName.BCM5, 0x00)
        }
      }
      CpmSetPostCode (CpmTpLowPowerEthernetCablePlugInEnd)
      Release (QMUX)
    } // End of Method(CpmLowPowerEthernetCablePlugInMethod, 0x0, Serialized)

  } // End of Scope(\_SB.PCI0.LPC0.EC0)

  Scope (\_SB.PCI0.CpmLowPowerEthernetBridgeAslName.BCM5) {
    Method (_EJ0, 1) {
      Acquire (\_SB.PCI0.LPC0.EC0.QMUX, 0xFFFF)
      CpmSetPostCode (CpmTpLowPowerEthernetEJ0Begin)
      Store (CpmReadTable (CpmLowPowerEthernetTable, CpmLowPowerEthernetBridgeDevice), Local0)
      Store (CpmReadTable (CpmLowPowerEthernetTable, CpmLowPowerEthernetBridgeFunction), Local1)
      Store (CpmReadTable (CpmLowPowerEthernetTable, CpmLowPowerEthernetLanLowPowerPin), Local2)
      Store (CpmReadTable (CpmLowPowerEthernetTable, CpmLowPowerEthernetDeviceId), Local3)
      CpmPcieHotplug (Local0, Local1, 0, 1)
      Sleep (100)
      Sleep (200)
      CpmWriteGpio (Add (Local2, 0x200), 0x1)
      Sleep (1000)
      CpmSetDeviceClock (Local3, 0)             // Clock Off
      CpmSetPostCode (CpmTpLowPowerEthernetEJ0End)
      Release (\_SB.PCI0.LPC0.EC0.QMUX)
    } // End of Method (_EJ0)
  } // End of Scope(\_SB.PCI0.CpmLowPowerEthernetBridgeAslName.BCM5)

  Scope (\_SB) {
    Method (CpmLowPowerEthernet_WAK, 1, Serialized) {
      CpmSetPostCode (CpmTpLowPowerEthernetWAKStart)
      Notify (\_SB.PCI0.CpmLowPowerEthernetBridgeAslName.BCM5, 0x00)
      CpmSetPostCode (CpmTpLowPowerEthernetWAKEnd)
    } // End of Method (CpmLowPowerEthernet_WAK)
  } // End of Scope(\_SB)
}

