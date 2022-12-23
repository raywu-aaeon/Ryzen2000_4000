/*****************************************************************************
 *
 * Copyright (C) 2012-2022 Advanced Micro Devices, Inc. All rights reserved.
 *
 ******************************************************************************
 */

DefinitionBlock (
  "ExpressCard.aml",      // Output file
  "SSDT",                 // Signature
  0x01,                   // SSDT Revision
  "AMD",                  // OEM ID
  "CPMXPRES",             // OEM Table ID
  0x1                     // OEM Revision
  )
{
  #define CPM_PCIE_EXPRESS_CARD_ASL

  #include "CmnDef.asi"
  #include "CmnExt.asi"
  #include "PostCode.asi"

  Scope (\_GPE) {                                 // General-Purpose Event
    Method (CpmExpressCardEventMethod) {
      Store (CpmReadTable (CpmExpressCardTable, CpmExpressCardBridgeDevice), Local0)
      Store (CpmReadTable (CpmExpressCardTable, CpmExpressCardBridgeFunction), Local1)
      Store (CpmReadTable (CpmExpressCardTable, CpmExpressCardEventPin), Local2)
      Store (CpmReadTable (CpmExpressCardTable, CpmExpressCardDeviceId), Local3)

      If (CpmReadGevent (Local2)) {               // hot remove
        CpmWriteGeventTriggerType (Local2, 0)
        CpmSetPostCode (CpmTpExpressCardRemoveEventBegin)
        CpmPcieHotplug (Local0, Local1, 0, 0)
        CpmSetPostCode (CpmTpExpressCardRemoveEventEnd)
      } else {                                    // hot insert
        CpmWriteGeventTriggerType (Local2, 1)
        Store (CpmGetDeviceStatus (Local3), Local4)
        If (Local4) {
          CpmSetPostCode (CpmTpExpressCardInsertEventBegin)
          CpmPcieHotplug (Local0, Local1, 1, 0)
          CpmSetPostCode (CpmTpExpressCardInsertEventEnd)
        }
      }

      If (CondRefOf (\_SB.PCI0.CpmExpressCardBridge)) {
        Notify (\_SB.PCI0.CpmExpressCardBridge, 0x00)
      }
    }
  }
}
