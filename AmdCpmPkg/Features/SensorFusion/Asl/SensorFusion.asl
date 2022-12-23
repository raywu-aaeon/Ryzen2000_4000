/*****************************************************************************
 *
 * Copyright (C) 2018-2022 Advanced Micro Devices, Inc. All rights reserved.
 *
 ******************************************************************************
 */

DefinitionBlock (
    "SensorFusion.aml",                                 // Output file
    "SSDT",                                             // Signature
    0x01,                                               // SSDT Revision
    "AMD",                                              // OEM ID
    "CPMSFAML",                                         // OEM Table ID
    0x1                                                 // OEM Revision
    )
{
  #define CPM_SENSORFUSION

  #include "CmnDef.asi"
  #include "CmnExt.asi"
  #include "PostCode.asi"

  External(\_SB.PCI0.PBC.MP2C, DeviceObj)

  Scope (\_SB) {
    Device (CIND) {
      Name (_HID, "AMDI0081")
      Name (_CID, "PNP0C60")
      Name (_UID, 0x0)

      Method (_STA, 0, Serialized) {
        if (LEqual (CpmReadTable (CpmMainTable, CpmSensorFusionEn), 1)) {
          Return (0x0F)
        } Else {
          Return (0x00)
        }
      }
    } // End of Device (CIND)

    Device (VGBI) {
      Name (_HID, "AMDI0080")
      Name (_UID, 0x1)

      Name (_DEP, Package(0x1) {
        \_SB.PCI0.PBC.MP2C
      })

      Method (_STA, 0, Serialized) {
        if (LEqual (CpmReadTable (CpmMainTable, CpmSensorFusionEn), 1)) {
          Return (0x0F)
        } Else {
          Return (0x00)
        }
      }
    } // End of Device (VGBI)
  } // End of Scope (\_SB)
} // End of DefinitionBlock()

