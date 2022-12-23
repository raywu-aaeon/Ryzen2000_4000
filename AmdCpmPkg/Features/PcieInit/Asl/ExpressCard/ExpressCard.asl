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
