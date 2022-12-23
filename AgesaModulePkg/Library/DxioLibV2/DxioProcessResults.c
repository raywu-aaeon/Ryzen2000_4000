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

#define FILECODE LIBRARY_DXIOLIBV2_DXIOPROCESSRESULTS_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

VOID
DxioSleep (
  IN     GNB_HANDLE     *GnbHandle,
  IN     UINT32         Milliseconds
  );

/*----------------------------------------------------------------------------------------*/
/*
 *  Routine to write all register spaces.
 *
 *
 * @param[in]  BusNumber         Bus number of D0F0 of the target die
 * @param[in]  Address           Register offset, but PortDevice
 * @param[in]  Value             The value to write
 * @param[in]  Flags             Flags - BIT0 indicates S3 save/restore
 * @retval     VOID
 */
STATIC
VOID
SmnRegisterWrite (
  IN       UINT32              BusNumber,
  IN       UINT32              Address,
  IN       VOID                *Value,
  IN       UINT32              Flags
  )
{

  ACCESS_WIDTH  Width;
  PCI_ADDR      GnbPciAddress;

  GnbPciAddress.AddressValue = 0;
  GnbPciAddress.Address.Bus = BusNumber;
  Width = (Flags == GNB_REG_ACC_FLAG_S3SAVE) ? AccessS3SaveWidth32 : AccessWidth32;

  GnbLibPciIndirectWrite (
    GnbPciAddress.AddressValue | D0F0xB8_ADDRESS,
    Address,
    Width,
    Value,
    NULL
  );
  return;
}

STATIC
VOID
writeSmnBuffer(UINT32 TargetBus, UINT32 addr, UINT32 value) {
  UINT32 WriteVal;
  WriteVal = value;
  SmnRegisterWrite (TargetBus, addr, &WriteVal, 0);
}

STATIC
VOID
reset_hack (
  UINT32     TargetBus
  )
{

  writeSmnBuffer (TargetBus, 0x2d02568, 0xc40000);
  writeSmnBuffer (TargetBus, 0x2d0256c, 0xc40000);
  writeSmnBuffer (TargetBus, 0x2d02228, 0xc40000);
  writeSmnBuffer (TargetBus, 0x2d0222c, 0xc40000);
  return;

}

AGESA_STATUS
DxioProcessResults (
  IN       GNB_HANDLE                      *GnbHandle,
  IN       DXIO_COMPLEX_DESCRIPTOR         *UserConfig,
  IN       DXIO_PLATFORM_DESCRIPTOR        *ThisNode,
  IN       UINT32                          ThisNodeSize,
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI   *SmuServicesPpi
  )
{
  AGESA_STATUS              AgesaStatus;
  UINT32                    SmuArg[6];
  UINT8                     DxioRetval;
  BOOLEAN                   DxioComplete;
  DXIO_RETURN_PARAMS        *ReturnArgs;
  LISM_RETURN_PARAMS        *LismRetParams;
  RESET_REQUEST_PARAMS      *ResetReqParams;
  GPIO_RESET_INFO           GpioResetInfo;
  PCI_ADDR                  EarlyTrainAddress;
  PCI_ADDR                  NbioAddress;
  DXIO_ENGINE_DESCRIPTOR    *EarlyTrainDesc;
  PCIe_ENGINE_CONFIG        *EarlyTrainEngine;
  BOOLEAN                   EarlyLinkMapped;
  BOOLEAN                   TrainingSuccess;

  // Process results
// Temporary workaround for no DXIO firmware
    DxioWorkaroundForNoDxioInitialize ();
//
  AgesaStatus = AGESA_SUCCESS;
  ReturnArgs = (DXIO_RETURN_PARAMS*) &SmuArg[0];
  EarlyLinkMapped = FALSE;
  DxioComplete = FALSE;
  EarlyTrainAddress.AddressValue = 0;
  EarlyTrainDesc = NULL;
  EarlyTrainEngine = NULL;
  do {
    LibAmdMemFill (SmuArg, 0x00, 24, (AMD_CONFIG_PARAMS *) NULL);
    SmuServicesPpi->SmuDxioServiceRequest (SmuServicesPpi, GnbHandle->SocketId, DXIO_MSG_LISM_COLLECTRESULTS, SmuArg, SmuArg);
// Temporary workaround for no DXIO firmware
    DxioWorkaroundForNoDxioGetStatus (SmuArg);
//

    DxioRetval = (UINT8) (SmuArg[0] & 0xFF);
    switch (DxioRetval) {
    case DXIO_MBOX_RETVAL_OK:
      switch (ReturnArgs->RetParams_Type) {
      case DXIO_MBOX_RETPARAMS_LISM:
        LismRetParams = (LISM_RETURN_PARAMS*) &SmuArg[2];
        IDS_HDT_CONSOLE (GNB_TRACE, "Current State = 0x%x\n", LismRetParams->CurrentState);
        switch (LismRetParams->CurrentState) {
        case DXIO_LinkInitState_done:
            DxioComplete = TRUE;
            break;
        case DXIO_LinkInitState_mapped:
          // Ports are mapped.  Allow pre-configuration options to be programmed.
          IDS_HDT_CONSOLE (GNB_TRACE, "PORTS ARE MAPPED\n");
          DxioLibServiceRequest (SmuServicesPpi, GnbHandle->SocketId, DXIO_MSG_INIT_DMAENGINECONIFGTODRAM, 0, (UINT32) ThisNode, ThisNodeSize, 0, 0);
          EarlyTrainDesc = NULL;
          DxioPortMapping (GnbHandle,
                           UserConfig,
                           ThisNode,
                           (DXIO_ENGINE_DESCRIPTOR**)&EarlyTrainDesc,
                           &EarlyTrainAddress.AddressValue,
                           (PCIe_ENGINE_CONFIG **) &EarlyTrainEngine
                           );
          DxioCfgBeforeReconfig (GnbHandle);
          break;
        case DXIO_LinkInitState_configured:
          // Configuration is done.  Allow post-configuration, pre-training options to be programmed.
          IDS_HDT_CONSOLE (GNB_TRACE, "RECONFIG IS COMPLETE\n");
          DxioCfgAfterReconfig (GnbHandle);
          DxioComplete = TRUE;
          break;
        case DXIO_LinkInitState_earlyTrained:
          // Read back training results
          IDS_HDT_CONSOLE (GNB_TRACE, "EarlyTrained state detected...\n");
          if (EarlyTrainDesc == NULL) {
            IDS_HDT_CONSOLE (GNB_TRACE, "EarlyTrainLink NOT FOUND\n");
          } else {
            IDS_HDT_CONSOLE (GNB_TRACE, "\nEarlyTrainLink found at 0x%x\n", EarlyTrainAddress);
            EarlyLinkMapped = TRUE;
            EarlyTrainAddress.AddressValue = EarlyTrainAddress.AddressValue << 12;
            NbioAddress = NbioGetHostPciAddress (GnbHandle);
            if (EarlyTrainEngine != NULL) {
              TrainingSuccess = TRUE;                   ///TODO: Check DXIO training status
              if (TRUE == TrainingSuccess) {
                EarlyTrainAddress.AddressValue |= NbioAddress.AddressValue;
                GnbLibPciRMW (EarlyTrainAddress.AddressValue | 0x18, AccessWidth32, 0xFF000FF, 0x020200, (AMD_CONFIG_PARAMS *) NULL);
                DxioLibServiceRequest (SmuServicesPpi, GnbHandle->SocketId, DXIO_MSG_INIT_DMAENGINECONIFGTODRAM, 0, (UINT32) ThisNode, ThisNodeSize, 0, 0);
                EarlyTrainDesc->LinkDesc.Pcie.DevFunNumber = 0x200;
                IDS_HDT_CONSOLE (GNB_TRACE, "Sending this Platform Descriptor back to SMU...\n");
                GnbLibDebugDumpBuffer ((VOID*) ThisNode, ThisNodeSize << 2, 1, 16);
                IDS_HDT_CONSOLE (GNB_TRACE, "\n");
                DxioLibServiceRequest (SmuServicesPpi, GnbHandle->SocketId, DXIO_MSG_INIT_LOADHEAP, 0, (UINT32) ThisNode, ThisNodeSize, 0, DXIO_HEAPTYPE_CFGPTR);
              }
            }
          }
          break;
        case DXIO_LinkInitState_vetting:
          IDS_HDT_CONSOLE (GNB_TRACE, "Vetting state detected...\n");
          break;
        default:
          break;
        }
        break;
      case DXIO_MBOX_RETPARAMS_REQ_RESET:
        // Issue reset request for specific PCIe Engine
        ResetReqParams = (RESET_REQUEST_PARAMS*) &SmuArg[2];
        GpioResetInfo.ResetId = ResetReqParams->GpioId;
        GpioResetInfo.ResetControl = ResetReqParams->resetAssertDeassert;
        if (ResetReqParams->resetAssertDeassert == 0) {
          AgesaGpioSlotResetControl ((UINTN) GnbHandle->Address.Address.Bus, &GpioResetInfo);
          IDS_HDT_CONSOLE (GNB_TRACE, "Reset Assert Request for GpioId 0x%x\n", ResetReqParams->GpioId);
        } else {
          //AgesaGpioSlotResetControl ((UINTN) GnbHandle->Address.Address.Bus, &GpioResetInfo);
          reset_hack((UINT32) GnbHandle->Address.Address.Bus);
          if (PcdGet16 (PcdAfterResetDelay) != 0) {
            IDS_HDT_CONSOLE (GNB_TRACE, "Reset delay %dmS\n", PcdGet16 (PcdAfterResetDelay));
            DxioSleep (GnbHandle, PcdGet16 (PcdAfterResetDelay));
            PcdSet16 (PcdAfterResetDelay, 0);
          }
          IDS_HDT_CONSOLE (GNB_TRACE, "Reset Deassert Request for GpioId 0x%x\n", ResetReqParams->GpioId);
        }
        break;
      case DXIO_MBOX_RETPARAMS_NONE:
        DxioComplete = TRUE;
        break;
      case DXIO_MBOX_RETPARAMS_GENERIC:
      default:
        IDS_HDT_CONSOLE (GNB_TRACE, "Invalid return parameter [0x%x]\n", DxioRetval);
        ASSERT (FALSE);
        break;
      }
      break;
    case DXIO_MBOX_RETVAL_ERROR:
      switch (ReturnArgs->RetParams_Type) {
      case DXIO_MBOX_RETPARAMS_LISM:
        LismRetParams = (LISM_RETURN_PARAMS*) &SmuArg[2];
        IDS_HDT_CONSOLE (GNB_TRACE, "Current State = 0x%x", LismRetParams->CurrentState);
        AgesaStatus = AGESA_CRITICAL;
        DxioComplete = TRUE;
        break;
      default:
        ASSERT (FALSE);
        break;
      }
      break;
    default:
      IDS_HDT_CONSOLE (GNB_TRACE, "DXIO Mailbox Request did not return OK [0x%x]\n", DxioRetval);
      ASSERT (FALSE);
      DxioComplete = TRUE;
      break;
    }
    if (FALSE == DxioComplete) {
      LibAmdMemFill (SmuArg, 0x00, 24, (AMD_CONFIG_PARAMS *) NULL);
      SmuServicesPpi->SmuDxioServiceRequest (SmuServicesPpi, GnbHandle->SocketId, DXIO_MSG_LISM_RESUME, SmuArg, SmuArg);
    }
  } while (FALSE == DxioComplete);
  if ((EarlyLinkMapped == TRUE) && (EarlyTrainDesc != NULL)) {
    GnbLibPciRMW (EarlyTrainAddress.AddressValue | 0x18, AccessWidth32, 0xFF000FF, 0x000000, (AMD_CONFIG_PARAMS *) NULL);
  }
  return  AgesaStatus;
}



