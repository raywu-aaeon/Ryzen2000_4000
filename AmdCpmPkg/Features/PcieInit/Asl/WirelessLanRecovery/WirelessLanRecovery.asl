/*****************************************************************************
 *
 * Copyright (C) 2018-2022 Advanced Micro Devices, Inc. All rights reserved.
 *
 ******************************************************************************
 */

DefinitionBlock (
  "WirelessLanRecovery.aml", // Output file
  "SSDT",                    // Signature
  0x01,                      // SSDT Revision
  "AMD",                     // OEM ID
  "CPMWLRC",                 // OEM Table ID
  0x1                        // OEM Revision
  )
{

  #include "CmnDef.asi"
  #include "CmnExt.asi"
  #include "PostCode.asi"

  External (\_SB.PCI0.CpmWirelessLanBridgeAslName.DEV0, DeviceObj)

  Scope (\_SB.PCI0.CpmWirelessLanBridgeAslName.DEV0) {
    Name(_PRR, Package() { \_SB_.PRWL })
  } // End of Scope(\_SB.PCI0.CpmWirelessLanBridgeAslName.DEV0)

  Scope (\_SB) {
    Name(WLPS, 1)
    PowerResource(PRWL, 0, 0) {
      Method(_RST, 0x0, NotSerialized)
      {
        CpmSetPostCode(CpmTpWirelessLanRecoveryResetStart)
        Store (CpmReadTable (CpmWirelessLanRecoveryTable, CpmWirelessLanRecoveryDeviceId), Local0)
        CpmSetDeviceReset (Local0, 0)           // Assert Reset
        Sleep (200)
        CpmSetDeviceReset (Local0, 1)           // De-assert Reset
        CpmSetPostCode(CpmTpWirelessLanRecoveryResetEnd)
      }

      Method(_STA, 0x0, NotSerialized)
      {
        Return(WLPS)
      }

      Method(_ON_, 0x0, NotSerialized)
      {
        Store (1, WLPS)
      }

      Method(_OFF, 0x0, NotSerialized)
      {
        Store (0, WLPS)
      }
    }
  } // End of Scope(\_SB)
}

