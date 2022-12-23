/*****************************************************************************
 *
 * Copyright 2018 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
    "AcpPowerGatingAsl.aml",        // Output file
    "SSDT",                         // Signature
    0x01,                           // SSDT Revision
    "AMD",                          // OEM ID
    "CPMACPPG",                     // OEM Table ID
    0x1                             // OEM Revision
    )
{
    #define CPM_ACP_POWER_GATING  1

    #include "CmnDef.asi"
    #include "CmnExt.asi"
    #include "PostCode.asi"

    External(\_SB.PCI0.PBC.ACP, DeviceObj)
    External(\_SB.PCI0.PBC.AZAL, DeviceObj)

    Name (CpmAcpPresentState, 1)    // ACP  present state
    Name (CpmAzaliaPresentState, 1) // AZALIA present state
    Name (CpmAcpController, 1)      // ACP Controller Enable/Disable

    Method (CpmPowerGateOn, 0) {
      If (LEqual (CpmAcpController, 0)) {                             // ACP Controller is disable
        Store (0, CpmAcpPresentState)
      }
      If (LOr (LEqual (CpmAcpPresentState, 1), LEqual (CpmAzaliaPresentState, 1) ) ) {
        // Power on ACP
        Store (CpmReadPci (0, 8, 1, 0x19, 0, 8), Local0)              // Local0 = ACP Bus number
        Store (CpmReadPci32 (Local0, 0, 5, 0), Local1)                // Local1 = ACP DID
        If (LEqual (CpmAcpController, 0)) {                           // ACP Controller is disable
          Store (0x15E21022, Local1)
        }

        If (LAnd (LNotEqual (Local0, 0x00), LNotEqual (Local0, 0xFF) ) ) {
          If (LNotEqual (Local1, 0xFFFFFFFF)) {
            CpmSetPostCode (CpmTpAcpAzaliaPowerGateOnStart)

            // For ACLK Clock Start
            CpmWriteSmnRegister (0, 0, 0, 0x00058A74, 0x0)                // MP1_SMN_C2PMSG_93 = 0x0,   Clear responce register
            CpmWriteSmnRegister (0, 0, 0, 0x00058A54, 0xC8)               // MP1_SMN_C2PMSG_85 = 0xC8,  Write Clock Value
            CpmWriteSmnRegister (0, 0, 0, 0x00058A14, 0x3)                // MP1_SMN_C2PMSG_69 = 0x3,   Write Clock Type
            Store (CpmReadSmnRegister (0, 0, 0, 0x00058A74), Local4)      // Read MP1_SMN_C2PMSG_93,    Check Read Responce
            While (LEqual (Local4, 0)) {
              Store (CpmReadSmnRegister (0, 0, 0, 0x00058A74), Local4)
              if (LNotEqual (Local4, 0)) {
                break
              }
            }

            // For Power Gating
            // RSMU_PGFSM_CONTROL_ACP.RSMU_PGFSM_SW_CONTROL = 1
            // RSMU_PGFSM_CONTROL_ACP.RSMU_PGFSM_CMD = 1                  // 0:PD, 1:PU, 2:WR, 3:RD
            // RSMU_PGFSM_CONTROL_ACP.RSMU_PGFSM_SELECT = 1
            CpmWriteSmnRegister (0, 0, 0, 0x00048720, 0x103)

            // Polling PGFSM (internal register) power status register
            Store (1, Local4)
            Store (100, Local5)
            While (LAnd (LNotEqual (Local4, 0), Local5)) {
              Store (CpmReadSmnRegister (0, 0, 0, 0x00048720), Local4)    // Read RSMU_PGFSM_CONTROL_ACP
              Or (Local4, 0x00000006, Local4)                             // RSMU_PGFSM_CONTROL_ACP.RSMU_PGFSM_CMD = 3
              And (Local4, 0xFFFFFF0F, Local4)                            // RSMU_PGFSM_CONTROL_ACP.RSMU_PGFSM_ADDR = 0
              CpmWriteSmnRegister (0, 0, 0, 0x00048720, Local4)           // Write to RSMU_PGFSM_CONTROL_ACP
              Store (CpmReadSmnRegister (0, 0, 0, 0x00048728), Local4)    // Read RSMU_PGFSM_RD_DATA_ACP
              And (Local4, 3, Local4)
              Decrement (Local5)
              Stall (99)                                                  // 99us * 100 = 10ms
            }
            CpmWriteSmnRegister (0, 0, 0, 0x00048720, 0)                  // Write to RSMU_PGFSM_CONTROL_ACP = 0

            // Power off ACP
            CpmSetPostCode (CpmTpAcpAzaliaPowerGateOnEnd)
          }
        }
      }
    }

    Method (CpmPowerGateOff, 0) {
      If (LEqual (CpmAcpController, 0)) {                             // ACP Controller is disable
        Store (0, CpmAcpPresentState)
      }
      If (LAnd (LEqual (CpmAcpPresentState, 0), LEqual (CpmAzaliaPresentState, 0) ) ) {
        // Power on ACP
        Store (CpmReadPci (0, 8, 1, 0x19, 0, 8), Local0)              // Local0 = ACP Bus number
        Store (CpmReadPci32 (Local0, 0, 5, 0), Local1)                // Local1 = ACP DID
        If (LEqual (CpmAcpController, 0)) {                           // ACP Controller is disable
          Store (0x15E21022, Local1)
        }

        If (LAnd (LNotEqual (Local0, 0x00), LNotEqual (Local0, 0xFF) ) ) {
          If (LNotEqual (Local1, 0xFFFFFFFF)) {
            CpmSetPostCode (CpmTpAcpAzaliaPowerGateOffStart)

            // For ACLK Clock Stop
            CpmWriteSmnRegister (0, 0, 0, 0x00058A74, 0x0)                // MP1_SMN_C2PMSG_93 = 0x0,   Clear responce register
            CpmWriteSmnRegister (0, 0, 0, 0x00058A54, 0x0)                // MP1_SMN_C2PMSG_85 = 0x0,   Write Clock Value
            CpmWriteSmnRegister (0, 0, 0, 0x00058A14, 0x3)                // MP1_SMN_C2PMSG_69 = 0x3,   Write Clock Type
            Store (CpmReadSmnRegister (0, 0, 0, 0x00058A74), Local4)      // Read MP1_SMN_C2PMSG_93,    Check Read Responce
            While (LEqual (Local4, 0)) {
              Store (CpmReadSmnRegister (0, 0, 0, 0x00058A74), Local4)
              if (LNotEqual (Local4, 0)) {
                break
              }
            }

            // For Power Gating
            // RSMU_PGFSM_CONTROL_ACP.RSMU_PGFSM_SW_CONTROL = 1
            // RSMU_PGFSM_CONTROL_ACP.RSMU_PGFSM_CMD = 0                  // 0:PD, 1:PU, 2:WR, 3:RD
            // RSMU_PGFSM_CONTROL_ACP.RSMU_PGFSM_SELECT = 1
            CpmWriteSmnRegister (0, 0, 0, 0x00048720, 0x101)

            // Polling PGFSM (internal register) power status register
            Store (1, Local4)
            Store (100, Local5)
            While (LAnd (LNotEqual (Local4, 2), Local5)) {
              Store (CpmReadSmnRegister (0, 0, 0, 0x00048720), Local4)    // Read RSMU_PGFSM_CONTROL_ACP
              Or (Local4, 0x00000006, Local4)                             // RSMU_PGFSM_CONTROL_ACP.RSMU_PGFSM_CMD = 3
              And (Local4, 0xFFFFFF0F, Local4)                            // RSMU_PGFSM_CONTROL_ACP.RSMU_PGFSM_ADDR = 0
              CpmWriteSmnRegister (0, 0, 0, 0x00048720, Local4)           // Write to RSMU_PGFSM_CONTROL_ACP
              Store (CpmReadSmnRegister (0, 0, 0, 0x00048728), Local4)    // Read RSMU_PGFSM_RD_DATA_ACP
              And (Local4, 3, Local4)
              Decrement (Local5)
              Stall (99)                                                  // 99us * 100 = 10ms
            }
            CpmWriteSmnRegister (0, 0, 0, 0x00048720, 0)                  // Write to RSMU_PGFSM_CONTROL_ACP = 0

            // Power off ACP
            CpmSetPostCode (CpmTpAcpAzaliaPowerGateOffEnd)
          }
        }
      }
    }

    Scope (\_SB.PCI0.PBC.ACP) {
      Method (_PS0, 0) {
        Store (1, CpmAcpPresentState)
        CpmPowerGateOn ()
      }
      Method (_PS3, 0) {
        Store (0, CpmAcpPresentState)
        CpmPowerGateOff ()
      }
    }

    Scope (\_SB.PCI0.PBC.AZAL) {
      Method (_PS0, 0) {
        Store (1, CpmAzaliaPresentState)
        CpmPowerGateOn ()
      }
      Method (_PS3, 0) {
        Store (0, CpmAzaliaPresentState)
        CpmPowerGateOff ()
      }
    }

}