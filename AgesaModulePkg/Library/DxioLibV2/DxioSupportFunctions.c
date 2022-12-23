/* $NoKeywords:$ */
/**
 * @file
 *
 * DXIO Support Functions
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
#include <Library/SmnAccessLib.h>
#include "DxioLibLocal.h"

#define FILECODE LIBRARY_DXIOLIBV2_DXIOSUPPORTFUNCTIONS_FILECODE
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

#define SMN_NBIO0PCIE0_RSMU_BIOS_TIMER_CMD_ADDRESS             0x11180488UL
#define SMN_NBIO1PCIE1_RSMU_BIOS_TIMER_CMD_ADDRESS             0x11680488UL

/*----------------------------------------------------------------------------------------*/
/**
 * DXIO MAC Reset Workaround
 *
 *
 *
 * @param[in]  PeiServices     Pointer to EFI_PEI_SERVICES pointer
 * @param[in]  SmuServicesPpi  Pointer to SMU Services PPI or similar entry point structure
 * @param[in]  Pcie            Pointer to the AGESA platfom complex
 * @param[in]  UserConfig      Pointer to the platform BIOS supplied platform configuration
 * @retval     AGESA_STATUS
 */

VOID
DxioSleep (
  IN     GNB_HANDLE     *GnbHandle,
  IN     UINT32         Milliseconds
  )
{
  UINT32  ValueA1;
  UINT32  ValueA2;
  UINT32  ValueB1;
  UINT32  ValueB2;
  UINT32  ValueDiffA;
  UINT32  ValueDiffB;

  SmnRegisterRead (GnbHandle->Address.Address.Bus, SMN_NBIO0PCIE0_RSMU_BIOS_TIMER_CMD_ADDRESS, &ValueA1);
  SmnRegisterRead (GnbHandle->Address.Address.Bus, SMN_NBIO1PCIE1_RSMU_BIOS_TIMER_CMD_ADDRESS, &ValueB1);
  do {
    SmnRegisterRead (GnbHandle->Address.Address.Bus, SMN_NBIO0PCIE0_RSMU_BIOS_TIMER_CMD_ADDRESS, &ValueA2);
    SmnRegisterRead (GnbHandle->Address.Address.Bus, SMN_NBIO1PCIE1_RSMU_BIOS_TIMER_CMD_ADDRESS, &ValueB2);
    ValueDiffA = (ValueA2 - ValueA1) >> 10;  // Approximate Milliseconds
    ValueDiffB = (ValueB2 - ValueB1) >> 10;  // Approximate Milliseconds
  } while ((Milliseconds > ValueDiffA) && (Milliseconds > ValueDiffB));
}

/*----------------------------------------------------------------------------------------*/

/**
  Shortcut function to call SmuDxioServiceRequest with just function parameters (no array of arguments)


  @param SmuServicesPpi   Instance of PPI
  @param InstanceId       The unique identifier of the SMU instance associated with this socket (for SSP, the socket number)
  @param ServiceRequest   The service request identifie
  @param DxioArg1         Arg 1
  @param DxioArg2         Arg 2
  @param DxioArg3         Arg 3
  @param DxioArg4         Arg 4
  @param DxioArg5         Arg 5

  @return UINT8           Returns DXIO status
**/
UINT8
DxioLibServiceRequest (
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI   *SmuServicesPpi,
  IN       UINT32                          InstanceId,
  IN       UINT32                          ServiceRequest,
  IN       UINT32                          DxioArg1,
  IN       UINT32                          DxioArg2,
  IN       UINT32                          DxioArg3,
  IN       UINT32                          DxioArg4,
  IN       UINT32                          DxioArg5
  )
{
  UINT32                    SmuArg[6];

  LibAmdMemFill (SmuArg, 0x00, 24, (AMD_CONFIG_PARAMS *) NULL);
  SmuArg[1] = DxioArg1;
  SmuArg[2] = DxioArg2;
  SmuArg[3] = DxioArg3;
  SmuArg[4] = DxioArg4;
  SmuArg[5] = DxioArg5;

  SmuServicesPpi->SmuDxioServiceRequest (SmuServicesPpi, InstanceId, ServiceRequest, SmuArg, SmuArg);

  // Check for any errors returned and notify caller
  if (SmuArg[0] != DXIO_MBOX_RETVAL_OK) {
    IDS_HDT_CONSOLE (GNB_TRACE, "%a : Request %d returned status %d which != DXIO_MBOX_RETVAL_OK\n",
                       __FUNCTION__,
                       ServiceRequest,
                       SmuArg[0]
                       );
  }

  return (UINT8)SmuArg[0];
}

/*----------------------------------------------------------------------------------------*/
/*
 *  Function to find the topology structure for a specific socket
 *
 *
 *
 * @param[in]     SocketNumber    Socket number to look for
 * @param[in]     UserComplex     Pointer to the top of the topology complex
 * @param[in]     PortList        Pointer to address of port list (for return)
 */
AGESA_STATUS
DxioGetUserCfgForSocket (
  IN      UINT8                     SocketNumber,
  IN      DXIO_COMPLEX_DESCRIPTOR   *UserComplex,
  IN OUT  DXIO_PORT_DESCRIPTOR      **PortList
  )
{
  AGESA_STATUS               AgesaStatus;
  DXIO_COMPLEX_DESCRIPTOR    *UserCfg;

  AgesaStatus = AGESA_ERROR;
  UserCfg = UserComplex;

  while (UserCfg != NULL) {
    if (UserCfg->SocketId == SocketNumber) {
      *PortList = UserCfg->PciePortList;
      AgesaStatus = AGESA_SUCCESS;
      break;
    }
    UserCfg = PcieConfigGetNextDataDescriptor(UserCfg);
  }
  ASSERT (AgesaStatus == AGESA_SUCCESS);
  return AgesaStatus;
}

/*----------------------------------------------------------------------------------------*/
/*
 *  Function to find the topology structure for a specific socket
 *
 *
 *
 * @param[in]     SocketNumber    Socket number to look for
 * @param[in]     UserComplex     Pointer to the top of the topology complex
 * @param[in]     PortList        Pointer to address of port list (for return)
 */

UINT32    DxioStatus;
BOOLEAN   IsSimNowRunning;

VOID
DxioWorkaroundSetSimNowStatus (
  IN      BOOLEAN   IsSimNow
  )
{
  IsSimNowRunning = IsSimNow;
}
VOID
DxioWorkaroundForNoDxioInitialize (
  )
{
  if (TRUE == IsSimNowRunning) {
    DxioStatus = 0;
  }
}
VOID
DxioWorkaroundForNoDxioGetStatus (
  IN OUT  UINT32            *SmuArg
  )
{
  DXIO_RETURN_PARAMS        *ReturnArgs;
  LISM_RETURN_PARAMS        *LismRetParams;

  if (TRUE == IsSimNowRunning) {
    ReturnArgs = (DXIO_RETURN_PARAMS *) SmuArg;
    LismRetParams = (LISM_RETURN_PARAMS*) &SmuArg[2];
    ReturnArgs->MP1Mbox_RetVal = DXIO_MBOX_RETVAL_OK;

    switch (DxioStatus) {
    case 0:
      ReturnArgs->RetParams_Type = DXIO_MBOX_RETPARAMS_LISM;
      LismRetParams->CurrentState = DXIO_LinkInitState_mapped;
      DxioStatus++;
      break;
    case 1:
      ReturnArgs->RetParams_Type = DXIO_MBOX_RETPARAMS_LISM;
      LismRetParams->CurrentState = DXIO_LinkInitState_configured;
      DxioStatus++;
      break;
    case 2:
      ReturnArgs->RetParams_Type = DXIO_MBOX_RETPARAMS_LISM;
      LismRetParams->CurrentState = DXIO_LinkInitState_earlyTrained;
      DxioStatus++;
      break;
    case 3:
      ReturnArgs->RetParams_Type = DXIO_MBOX_RETPARAMS_LISM;
      LismRetParams->CurrentState = DXIO_LinkInitState_vetting;
      DxioStatus++;
      break;
    case 4:
    default:
      ReturnArgs->RetParams_Type = DXIO_MBOX_RETPARAMS_LISM;
      LismRetParams->CurrentState = DXIO_LinkInitState_done;
      break;
    }
    return;
  }
}



