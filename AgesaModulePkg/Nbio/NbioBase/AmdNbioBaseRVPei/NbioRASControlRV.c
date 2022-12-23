/* $NoKeywords:$ */
/**
 * @file
 *
 * NbioRASControlRV - NBIO RAS Control
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  AmdNbioBaseRVPei
 * @e \$Revision: 312065 $   @e \$Date: 2015-01-30 04:23:05 -0600 (Fri, 30 Jan 2015) $
 *
 */
/*****************************************************************************
 *
 * Copyright 2008 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 *******************************************************************************
 */
#include <AMD.h>
#include <PiPei.h>
#include <Filecode.h>
#include <GnbDxio.h>
#include <GnbRegistersRV.h>
#include <Library/PeiServicesLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/GnbLib.h>
#include <Library/GnbPciLib.h>
#include <Library/GnbPciAccLib.h>
#include <Library/NbioRegisterAccLib.h>
#include <Library/NbioHandleLib.h>

#define FILECODE        NBIO_NBIOBASE_AMDNBIOBASERVPEI_NBIORASCONTROLRV_FILECODE

/*----------------------------------------------------------------------------------------
 *                         E X T E R N   D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define UNCORRECTABLE_GROUP_TYPE  0
#define CORRECTABLE_GROUP_TYPE    1
#define ECC_UCP_GROUP_TYPE        3
#define DDP_UCP_GROUP_TYPE        4

// 1h - enable ECC correction and reporting
#define ECC_correction_and_reporting                0x01
// 5h - enable error reporting
#define Error_Reporting                             0x05
// Ch - enable UCP reporting
#define UCP_Reporting                               0x0C

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */

typedef struct {
  IN      UINT32        GroupType;       ///< Parity Group ID
  IN      UINT32        GroupID;         ///< Group Type
  IN      UINT32        StructureID;     ///< Structure ID
  IN      UINT32        ErrGenCmd;       ///< Error command
} NBIO_PARITY_TABLE;

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

NBIO_PARITY_TABLE NbioParityTableZP[] = {
    // NBIO Correctable Parity
    { CORRECTABLE_GROUP_TYPE,12, 0,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,12, 1,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,13, 0,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,13, 1,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,14, 0,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,14, 1,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,15, 0,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,15, 1,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,16, 0,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,16, 1,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,16, 2,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,16, 3,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,16, 4,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,16, 5,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,16, 6,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,16, 7,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,16, 8,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,16, 9,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,16,10,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,16,11,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,16,12,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,16,13,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,16,14,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,16,15,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,16,16,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,16,17,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,16,18,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,16,19,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,17, 0,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,17, 1,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,17, 2,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,17, 3,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,17, 4,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,17, 5,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,17, 6,Error_Reporting },
    { CORRECTABLE_GROUP_TYPE,17, 7,Error_Reporting },
    // NBIO Uncorrectable Parity
    { UNCORRECTABLE_GROUP_TYPE,12, 0,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,12, 1,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,12, 2,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,13, 0,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,13, 1,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,13, 2,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,13, 3,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,13, 4,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,13, 5,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,13, 6,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,13, 7,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,13, 8,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,13, 9,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,13,10,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,13,11,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,13,12,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,13,13,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,14, 0,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,14, 1,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,14, 2,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,15, 0,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,15, 1,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,15, 2,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,15, 3,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,15, 4,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,15, 5,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,15, 6,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,15, 7,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,15, 8,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,15, 9,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,15,10,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,15,11,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,15,12,Error_Reporting },
    { UNCORRECTABLE_GROUP_TYPE,15,13,Error_Reporting },
    // NBIO ECC
    { CORRECTABLE_GROUP_TYPE,0,0,ECC_correction_and_reporting },
    { CORRECTABLE_GROUP_TYPE,0,1,ECC_correction_and_reporting },
    { CORRECTABLE_GROUP_TYPE,0,2,ECC_correction_and_reporting },
    { CORRECTABLE_GROUP_TYPE,0,3,ECC_correction_and_reporting },
    { CORRECTABLE_GROUP_TYPE,0,4,ECC_correction_and_reporting },
    { CORRECTABLE_GROUP_TYPE,0,5,ECC_correction_and_reporting },
    { CORRECTABLE_GROUP_TYPE,1,0,ECC_correction_and_reporting },
    { CORRECTABLE_GROUP_TYPE,1,1,ECC_correction_and_reporting },
    { CORRECTABLE_GROUP_TYPE,1,2,ECC_correction_and_reporting },
    { CORRECTABLE_GROUP_TYPE,1,3,ECC_correction_and_reporting },
    { CORRECTABLE_GROUP_TYPE,1,4,ECC_correction_and_reporting },
    { CORRECTABLE_GROUP_TYPE,1,5,ECC_correction_and_reporting },
    { CORRECTABLE_GROUP_TYPE,2,0,ECC_correction_and_reporting },
    { CORRECTABLE_GROUP_TYPE,3,0,ECC_correction_and_reporting },
    { CORRECTABLE_GROUP_TYPE,4,0,ECC_correction_and_reporting },
    { CORRECTABLE_GROUP_TYPE,5,0,ECC_correction_and_reporting },
    { CORRECTABLE_GROUP_TYPE,6,0,ECC_correction_and_reporting },
    { CORRECTABLE_GROUP_TYPE,6,1,ECC_correction_and_reporting },
    { CORRECTABLE_GROUP_TYPE,7,0,ECC_correction_and_reporting },
    { CORRECTABLE_GROUP_TYPE,7,1,ECC_correction_and_reporting },
    { CORRECTABLE_GROUP_TYPE,8,1,ECC_correction_and_reporting },
    // NBIO ECC+UCP
    { ECC_UCP_GROUP_TYPE,2,1,ECC_correction_and_reporting },
    { ECC_UCP_GROUP_TYPE,3,1,ECC_correction_and_reporting },
    { ECC_UCP_GROUP_TYPE,4,1,ECC_correction_and_reporting },
    { ECC_UCP_GROUP_TYPE,5,1,ECC_correction_and_reporting },
    // NBIO DDP+UCP
    { DDP_UCP_GROUP_TYPE, 2,2,UCP_Reporting },
    { DDP_UCP_GROUP_TYPE, 3,2,UCP_Reporting },
    { DDP_UCP_GROUP_TYPE, 4,2,UCP_Reporting },
    { DDP_UCP_GROUP_TYPE, 5,2,UCP_Reporting },
    { DDP_UCP_GROUP_TYPE, 6,2,UCP_Reporting },
    { DDP_UCP_GROUP_TYPE, 7,2,UCP_Reporting },
    { DDP_UCP_GROUP_TYPE, 7,3,UCP_Reporting },
    { DDP_UCP_GROUP_TYPE, 7,4,UCP_Reporting },
    { DDP_UCP_GROUP_TYPE, 8,2,UCP_Reporting },
    { DDP_UCP_GROUP_TYPE, 8,3,UCP_Reporting },
    { DDP_UCP_GROUP_TYPE, 8,4,UCP_Reporting },
    { DDP_UCP_GROUP_TYPE, 9,0,UCP_Reporting },
    { DDP_UCP_GROUP_TYPE, 9,1,UCP_Reporting },
    { DDP_UCP_GROUP_TYPE,10,0,UCP_Reporting },
    { DDP_UCP_GROUP_TYPE,10,1,UCP_Reporting },
    { DDP_UCP_GROUP_TYPE,11,0,UCP_Reporting },
    { DDP_UCP_GROUP_TYPE,11,1,UCP_Reporting },
    { DDP_UCP_GROUP_TYPE,11,2,UCP_Reporting },
};

/*----------------------------------------------------------------------------------------
 *                    P P I   N O T I F Y   D E S C R I P T O R S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------*/
/**
 * Enable NBIO RAS Control
 *
 *
 *
 * @param[in]  GnbHandle      GNB Handle
 */

VOID
NbioRASControlRV (
  IN GNB_HANDLE                 *GnbHandle
  )
{
  UINTN                     i;
  UINT32                    Value;
  NBRASCFG_0004_STRUCT      NBRASCFG_0004;
  PCI_ADDR                  IommuPciAddress;

  IDS_HDT_CONSOLE (GNB_TRACE, "NbioRASControlRV Enter\n");

  // IOHCRASx00000000 (PARITY_CONTROL_0): 0x0001_xxxx
  NbioRegisterRead ( GnbHandle, TYPE_D0F0xBC, PARITY_CONTROL_0_ADDRESS, &Value, 0);
  Value = (Value & 0xFFFF) | 0x00010000;
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, PARITY_CONTROL_0_ADDRESS, &Value, 0);
  // IOHCRASx00000008 (PARITY_SEVERITY_CONTROL_UNCORR_0): 0xAAAA_AAAA
  Value = 0xAAAAAAAA;
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, PARITY_SEVERITY_CONTROL_UNCORR_0_ADDRESS, &Value, 0);
  // IOHCRASx00000010 (PARITY_SEVERITY_CONTROL_CORR_0): 0x0000_0000
  // IOHCRASx00000014 (PARITY_SEVERITY_CONTROL_CORR_1): 0x0000_0000
  // IOHCRASx00000018 (PARITY_SEVERITY_CONTROL_UCP_0): 0x0000_0000
  // IOHCRASx00000158 (MISC_SEVERITY_CONTROL): 0x0000_0000
  Value = 0;
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, PARITY_SEVERITY_CONTROL_CORR_0_ADDRESS, &Value, 0);
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, PARITY_SEVERITY_CONTROL_CORR_1_ADDRESS, &Value, 0);
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, PARITY_SEVERITY_CONTROL_UCP_0_ADDRESS, &Value, 0);
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, MISC_SEVERITY_CONTROL_ADDRESS, &Value, 0);

  // IOHCRASx00000168 (ErrEvent_ACTION_CONTROL): 0x0000_0018
  // IOHCRASx0000016C (ParitySerr_ACTION_CONTROL): 0x0000_001F
  // IOHCRASx00000170 (ParityFatal_ACTION_CONTROL): 0x0000_001F
  // IOHCRASx00000174 (ParityNonFatal_ACTION_CONTROL): 0x0000_0006
  // IOHCRASx00000178 (ParityCorr_ACTION_CONTROL): 0x0000_0006

  Value = 0x0000001F;
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, ParitySerr_ACTION_CONTROL_ADDRESS, &Value, 0);
  Value = 0x0000001F;
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, ParityFatal_ACTION_CONTROL_ADDRESS, &Value, 0);
  Value = 0x00000006;
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, ParityNonFatal_ACTION_CONTROL_ADDRESS, &Value, 0);
  Value = 0x00000006;
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, ParityCorr_ACTION_CONTROL_ADDRESS, &Value, 0);

  // IOMMUL1:
  // L1_CNTRL_1: 10 L1CacheParityEn.
  NbioRegisterRead ( GnbHandle, TYPE_D0F0xBC, L1_CNTRL_1_PCIE0_ADDRESS, &Value, 0);
  Value |= BIT10;
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, L1_CNTRL_1_PCIE0_ADDRESS, &Value, 0);
  NbioRegisterRead ( GnbHandle, TYPE_D0F0xBC, L1_CNTRL_1_IOAGR_ADDRESS, &Value, 0);
  Value |= BIT10;
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, L1_CNTRL_1_IOAGR_ADDRESS, &Value, 0);

  // L1_CNTRL_2: 3 L1ATSDataErrorSignalEn.
  NbioRegisterRead ( GnbHandle, TYPE_D0F0xBC, L1_CNTRL_2_PCIE0_ADDRESS, &Value, 0);
  Value |= BIT3;
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, L1_CNTRL_2_PCIE0_ADDRESS, &Value, 0);
  NbioRegisterRead ( GnbHandle, TYPE_D0F0xBC, L1_CNTRL_2_IOAGR_ADDRESS, &Value, 0);
  Value |= BIT3;
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, L1_CNTRL_2_IOAGR_ADDRESS, &Value, 0);

  // IOMMUL2:
  // IOMMU_COMMAND: 6 PARITY_ERROR_EN.
  IommuPciAddress = NbioGetHostPciAddress (GnbHandle);
  IommuPciAddress.Address.Function = 0x2;
  GnbLibPciRead (IommuPciAddress.AddressValue | 0x4 , AccessWidth32, &Value, NULL);
  Value |= BIT6;
  GnbLibPciWrite (IommuPciAddress.AddressValue | 0x4, AccessWidth32, &Value, NULL);

  // L2_DTC_CONTROL: 4 DTCParityEn.
  NbioRegisterRead ( GnbHandle, TYPE_D0F0xBC, 0x15700040, &Value, 0);
  Value |= BIT4;
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, 0x15700040, &Value, 0);
  // L2_ITC_CONTROL: 4 ITCParityEn.
  NbioRegisterRead ( GnbHandle, TYPE_D0F0xBC, 0x15700050, &Value, 0);
  Value |= BIT4;
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, 0x15700050, &Value, 0);
  // L2_PTC_A_CONTROL: 4 PTCAParityEn.
  NbioRegisterRead ( GnbHandle, TYPE_D0F0xBC, 0x15700060, &Value, 0);
  Value |= BIT4;
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, 0x15700060, &Value, 0);
  // L2_PDC_CONTROL: 4 PDCParityEn.
  NbioRegisterRead ( GnbHandle, TYPE_D0F0xBC, 0x13F01140, &Value, 0);
  Value |= BIT4;
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, 0x13F01140, &Value, 0);
  // L2B_SDP_PARITY_ERROR_EN: 2 TWW_PARITY_ERROR_EN.
  // L2B_SDP_PARITY_ERROR_EN: 1 CP_PARITY_ERROR_EN.
  NbioRegisterRead ( GnbHandle, TYPE_D0F0xBC, 0x13F01288, &Value, 0);
  Value |= (BIT1 | BIT2);
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, 0x13F01288, &Value, 0);

  // execute the programming sequence given in PPR section 9.1.7.1 NBIO Internal Error Reporting Configuration.
  for ( i = 0; i < sizeof (NbioParityTableZP) / sizeof (NBIO_PARITY_TABLE); i++) {
    NBRASCFG_0004.Value = 0x0;
    NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, PARITY_CONTROL_1_ADDRESS, &NBRASCFG_0004.Value, 0);
    do {
      NbioRegisterRead ( GnbHandle, TYPE_D0F0xBC, PARITY_CONTROL_1_ADDRESS, &NBRASCFG_0004.Value, 0);
    } while (NBRASCFG_0004.Field.ParityErrGenInjectAllow != 0x1);

    NBRASCFG_0004.Field.ParityErrGenGroupSel = NbioParityTableZP[i].GroupID;
    NBRASCFG_0004.Field.ParityErrGenIdSel = NbioParityTableZP[i].StructureID;
    NBRASCFG_0004.Field.ParityErrGenCmd = NbioParityTableZP[i].ErrGenCmd;
    NBRASCFG_0004.Field.ParityErrGenTrigger = 1;

    switch (NbioParityTableZP[i].GroupType) {
    case UNCORRECTABLE_GROUP_TYPE:
      NBRASCFG_0004.Field.ParityErrGenGroupTypeSel = 0;
      break;
    case CORRECTABLE_GROUP_TYPE:
    case ECC_UCP_GROUP_TYPE:
    case DDP_UCP_GROUP_TYPE:
      NBRASCFG_0004.Field.ParityErrGenGroupTypeSel = 1;
      break;
    }
    NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, PARITY_CONTROL_1_ADDRESS, &NBRASCFG_0004.Value, 0);

    if (NbioParityTableZP[i].GroupType == ECC_UCP_GROUP_TYPE) {
      do {
        NbioRegisterRead ( GnbHandle, TYPE_D0F0xBC, PARITY_CONTROL_1_ADDRESS, &NBRASCFG_0004.Value, 0);
      } while (NBRASCFG_0004.Field.ParityErrGenInjectAllow != 0x1);
      NBRASCFG_0004.Field.ParityErrGenCmd = UCP_Reporting;
      NBRASCFG_0004.Field.ParityErrGenTrigger = 1;
      NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, PARITY_CONTROL_1_ADDRESS, &NBRASCFG_0004.Value, 0);
    }
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "NbioRASControlRV Exit\n");
}

/*----------------------------------------------------------------------------------------*/
/**
 * set nbif parity check report workaround
 *
 *
 *
 * @param[in]  GnbHandle      GNB Handle
 */

VOID
NbioNBIFParityCheckWorkaroundRV (
  IN GNB_HANDLE                 *GnbHandle
  )
{
  UINT32 Value;

  IDS_HDT_CONSOLE (GNB_TRACE, "NbioNBIFParityCheckWorkaroundRV Enter\n");

  NbioRegisterRead ( GnbHandle, TYPE_D0F0xBC, 0x10139000, &Value, 0);
  Value |= (BIT0 | BIT1 | BIT2 | BIT4 | BIT5 | BIT6);
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, 0x10139000, &Value, 0);

  NbioRegisterRead ( GnbHandle, TYPE_D0F0xBC, 0x10139000, &Value, 0);
  Value |= (BIT18 | BIT19 | BIT20);
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, 0x10139000, &Value, 0);
  NbioRegisterRead ( GnbHandle, TYPE_D0F0xBC, 0x10139004, &Value, 0);
  Value |= (BIT18 | BIT19 | BIT20);
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, 0x10139004, &Value, 0);
  NbioRegisterRead ( GnbHandle, TYPE_D0F0xBC, 0x10139008, &Value, 0);
  Value |= (BIT18 | BIT19 | BIT20);
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, 0x10139008, &Value, 0);

  IDS_HDT_CONSOLE (GNB_TRACE, "NbioNBIFParityCheckWorkaroundRV Exit\n");
}

