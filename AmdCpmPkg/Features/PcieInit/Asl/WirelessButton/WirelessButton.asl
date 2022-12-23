/*****************************************************************************
 *
 * Copyright (C) 2012-2022 Advanced Micro Devices, Inc. All rights reserved.
 *
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
