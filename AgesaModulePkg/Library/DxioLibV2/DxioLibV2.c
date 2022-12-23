/* $NoKeywords:$ */
/**
 * @file
 *
 * DXIO initialization services
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-25 21:00:43 -0600 (Wed, 25 Feb 2015) $
 *
 */
/*
*****************************************************************************
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
*
*/

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include <Filecode.h>
#include <PiPei.h>
#include <AmdPcieComplex.h>
#include <GnbDxio.h>
#include <Ppi/NbioSmuServicesPpi.h>
#include <Library/BaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/GnbLib.h>
#include <Library/PcieConfigLib.h>
#include <Library/NbioHandleLib.h>
#include <Library/NbioRegisterAccLib.h>
#include <Library/DxioLibV2.h>
#include <Library/OemGpioResetControlLib.h>
#include "DxioLibLocal.h"

#define FILECODE LIBRARY_DXIOLIBV2_DXIOLIBV2_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

#define   ZP_PLATFORM_TYPE  0
#define   MAX_INSTANCE_ID   8

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------*/
/**
 * DXIO Early Initialization
 *
 *
 *
 * @param[in]  PeiServices     Pointer to EFI_PEI_SERVICES pointer
 * @param[in]  SmuServicesPpi  Pointer to SMU Services PPI or similar entry point structure
 * @param[in]  Pcie            Pointer to the AGESA platfom complex
 * @param[in]  UserConfig      Pointer to the platform BIOS supplied platform configuration
 * @retval     AGESA_STATUS
 */

AGESA_STATUS
DxioEarlyInitV2 (
  IN       CONST EFI_PEI_SERVICES          **PeiServices,
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI   *SmuServicesPpi,
  IN       PCIe_PLATFORM_CONFIG            *Pcie,
  IN       DXIO_COMPLEX_DESCRIPTOR         *UserConfig
  )
{
  AGESA_STATUS              AgesaStatus;
  AGESA_STATUS              Status;
  GNB_HANDLE                *GnbHandle;
  UINT32                    SmuArg[6];
  UINT8                     InstanceId;
  UINT8                     DxioRetval;
  DXIO_PLATFORM_DESCRIPTOR  *PlatformDesc[MAX_INSTANCE_ID];
  UINT32                    PlatformDescSize[MAX_INSTANCE_ID];
  UINT8                     *AncillaryData[MAX_INSTANCE_ID];
  UINT32                    AncillaryDataSize[MAX_INSTANCE_ID];

  IDS_HDT_CONSOLE (GNB_TRACE, "%a : Enter\n", __FUNCTION__);

  AgesaStatus = AGESA_SUCCESS;

  //Test/Debug implementation
  DxioRetval = DXIO_MBOX_RETVAL_NULL;
  GnbHandle = NbioGetHandle (Pcie);
  InstanceId = 0xFF;
  while (GnbHandle != NULL) {
    InstanceId = GnbHandle->SocketId;
    DxioParseUserConfig (PeiServices,
                         GnbHandle,
                         UserConfig,
                         Pcie,
                         &PlatformDesc[InstanceId],
                         &PlatformDescSize[InstanceId],
                         &AncillaryData[InstanceId],
                         &AncillaryDataSize[InstanceId]
                         );

    if (PlatformDesc[InstanceId] != NULL) {
      IDS_HDT_CONSOLE (GNB_TRACE, "Platform Descriptor for Die %d\n", InstanceId);
      DxioDebugDump (PlatformDesc[InstanceId],
                     PlatformDescSize[InstanceId],
                     AncillaryData[InstanceId],
                     AncillaryDataSize[InstanceId]);

      if (InstanceId == UserConfig->BmcLinkLocation) {
        DxioLibServiceRequest (SmuServicesPpi, InstanceId, DXIO_MSG_LISM_RELOAD, 0, 0, 0, 0, 0);
      }
      DxioWorkaroundSetSimNowStatus (FALSE);

      LibAmdMemFill (SmuArg, 0x00, 24, (AMD_CONFIG_PARAMS *) NULL);
      SmuServicesPpi->SmuDxioServiceRequest (SmuServicesPpi, InstanceId, DXIO_MSG_DBUG_GETVERSION, SmuArg, SmuArg);

      PcdSet32 (PcdDxioMajorRevision, SmuArg[2]);
      PcdSet32 (PcdDxioMinorRevision, SmuArg[3]);

      LibAmdMemFill (SmuArg, 0x00, 24, (AMD_CONFIG_PARAMS *) NULL);
      SmuServicesPpi->SmuDxioServiceRequest (SmuServicesPpi, InstanceId, DXIO_MSG_INIT_INIT, SmuArg, SmuArg);
      DxioRetval = (UINT8) (SmuArg[0] & 0xFF);
      if (0 == PcdGet32 (PcdDxioMinorRevision)) {
        DxioRetval = DXIO_MBOX_RETVAL_OK;
        DxioWorkaroundSetSimNowStatus (TRUE);
        IDS_HDT_CONSOLE (GNB_TRACE, "SMU simulation is not enabled%d\n", InstanceId);
      }
      if (DxioRetval == DXIO_MBOX_RETVAL_OK) {

        DxioLibServiceRequest (SmuServicesPpi, InstanceId, DXIO_MSG_DBUG_SETSCRATCH, DBUG_SETSCRATCHFLAG_SKIPPSPMESSAGES, 1, 0, 0, 0);
        DxioLibServiceRequest (SmuServicesPpi, InstanceId, DXIO_MSG_DBUG_SETSCRATCH, DBUG_SETSCRATCHFLAG_RETURNAFTERMAPPING, 1, 0, 0, 0);
        DxioLibServiceRequest (SmuServicesPpi, InstanceId, DXIO_MSG_DBUG_SETSCRATCH, DBUG_SETSCRATCHFLAG_RETURNAFTERCONFIG, 1, 0, 0, 0);
        DxioLibServiceRequest (SmuServicesPpi, InstanceId, DXIO_MSG_DBUG_SETSCRATCH, DBUG_SETSCRATCHFLAG_V1ANCILLARYDATA, 1, 0, 0, 0);
        DxioLibServiceRequest (SmuServicesPpi, InstanceId, DXIO_MSG_DBUG_SETSCRATCH, 0x14, PcdGet8 (PcdDxioPhyProgramming), 0, 0, 0);

        if (PcdGet8 (PcdCfgSkipPspMessage) == 0) {
          DxioLibServiceRequest (SmuServicesPpi, InstanceId, DXIO_MSG_DBUG_SETSCRATCH, DBUG_SETSCRATCHFLAG_SKIPPSPMESSAGES, 0, 0, 0, 0);
        }

        DxioLibServiceRequest (SmuServicesPpi, InstanceId, DXIO_MSG_INIT_LOADCAPABILITIES, 0, 0, 0, 0, 0);

        if (AncillaryDataSize[InstanceId] != 0) {
          ASSERT (DXIO_MBOX_RETVAL_OK == DxioLibServiceRequest (SmuServicesPpi, InstanceId, DXIO_MSG_INIT_LOADHEAP, 0, (UINT32) AncillaryData[InstanceId], AncillaryDataSize[InstanceId], 0, DXIO_HEAPTYPE_ANCDATA));
        }
        DxioLibServiceRequest (SmuServicesPpi, InstanceId, DXIO_MSG_INIT_LOADHEAP, 0, 0, 0, 1, DXIO_HEAPTYPE_MACPCS);
        DxioLibServiceRequest (SmuServicesPpi, InstanceId, DXIO_MSG_INIT_LOADHEAP, 0, 0, 0, 1, DXIO_HEAPTYPE_GPIOPTR);
        ASSERT (DXIO_MBOX_RETVAL_OK == DxioLibServiceRequest (SmuServicesPpi, InstanceId, DXIO_MSG_INIT_LOADHEAP, 0, (UINT32) PlatformDesc[InstanceId], PlatformDescSize[InstanceId], 0, DXIO_HEAPTYPE_CFGPTR));

        // Inititiate configuration
        ASSERT (DXIO_MBOX_RETVAL_OK == DxioLibServiceRequest (SmuServicesPpi, InstanceId, DXIO_MSG_LISM_GO, 0, 0, 0, 0, 0));

        // Process results
        Status = DxioProcessResults (GnbHandle, UserConfig, PlatformDesc[InstanceId], PlatformDescSize[InstanceId], SmuServicesPpi);
        AGESA_STATUS_UPDATE (Status, AgesaStatus);
      }
    }
    do {
      GnbHandle = GnbGetNextHandle(GnbHandle);
    } while ((GnbHandle != NULL) && (InstanceId == GnbHandle->SocketId));
  }

  if (DxioRetval == DXIO_MBOX_RETVAL_OK) {
    GnbHandle = NbioGetHandle (Pcie);
    InstanceId = 0xFF;
    while (GnbHandle != NULL) {
      InstanceId = GnbHandle->SocketId;
      DxioLibServiceRequest (SmuServicesPpi, InstanceId, DXIO_MSG_LISM_RESUME, 0, 0, 0, 0, 0);
      // Process results
      Status = DxioProcessResults (GnbHandle, UserConfig, PlatformDesc[InstanceId], PlatformDescSize[InstanceId], SmuServicesPpi);
      AGESA_STATUS_UPDATE (Status, AgesaStatus);

      // Read back training results
      if (0 != PcdGet32 (PcdDxioMinorRevision)) {
        LibAmdMemFill ((VOID *)(PlatformDesc[InstanceId]), 0x00, PlatformDescSize[InstanceId] << 2, (AMD_CONFIG_PARAMS *) NULL);
        DxioLibServiceRequest (SmuServicesPpi, InstanceId, DXIO_MSG_INIT_DMAENGINECONIFGTODRAM, 0, (UINT32) PlatformDesc[InstanceId], PlatformDescSize[InstanceId], 0, 0);
      }
      DxioUpdatePortTrainingStatus (GnbHandle, UserConfig, PlatformDesc[InstanceId]);

      do {
        GnbHandle = GnbGetNextHandle(GnbHandle);
      } while ((GnbHandle != NULL) && (InstanceId == GnbHandle->SocketId));
    }
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "%a : Exit [0x%x]\n", __FUNCTION__, AgesaStatus);
  return  AgesaStatus;
}


/*----------------------------------------------------------------------------------------*/
/**
 * PCIe Port Speed Update Request
 *
 *
 *
 * @param[in]  PeiServices     Pointer to EFI_PEI_SERVICES pointer
 * @param[in]  SmuServicesPpi  Pointer to SMU Services PPI or similar entry point structure
 * @param[in]  InstanceId      The unique identifier of the NBIO instance associated with this socket/die
 * @param[in]  EngineId        PCIe bridge ID
 * @param[in]  TargetSpeed     Desired speed of the target port (Gen1, Gen2, Gen3)
 */

VOID
DxioSetLinkSpeedV2 (
  IN       CONST EFI_PEI_SERVICES          **PeiServices,
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI   *SmuServicesPpi,
  IN       UINT32                          InstanceId,
  IN       UINT32                          EngineId,
  IN       UINT32                          TargetSpeed
  )
{
  DxioLibServiceRequest (SmuServicesPpi, InstanceId, DXIO_MSG_PHYS_TARGETFREQUPDATE | (DXIO_freqUpdType_single << 10), DxioPcieEngine, TargetSpeed, EngineId, 0, 0);
}


