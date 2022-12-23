/* $NoKeywords:$ */
/**
 * @file
 *
 * APOB driver for ZP and RV SCM system
 *
 * Contains code that public APOB service
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision: 317842 $   @e \$Date: 2015-04-29 15:06:52 +0800 (Wed, 29 Apr 2015) $
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

#include <PiPei.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BaseLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/ApobZpRvLib.h>
#include <Ppi/ApobCommonServicePpi.h>
#include <Filecode.h>

#define FILECODE PSP_APOBDRV_APOBZPRVPEI_APOBZPRVPEI_FILECODE

STATIC APOB_COMMON_SERVICE_PPI mApobCommonServicePpi = {
  ApobGetApcbInstanceZpRv,
  ApobGetApcbRecoveryFlagZpRv,
  ApobGetDimmCfgUpdatedFlagZpRv,
  NULL,
  ApobGetPhysComplexNumberZpRv,
  ApobGetPhysCoreNumberZpRv,
  ApobGetIsThreadEnabledZpRv,
  ApobGetEccEnableZpRv,
  ApobGetNvdimmPresentInSystemZpRv,
  ApobGetNvdimmInfoZpRv,
  ApobGetMaxDimmsPerChannelZpRv,
  ApobGetMaxChannelsPerDieZpRv,
  ApobGetMaxChannelsPerSocketZpRv,
  ApobGetDimmSmbusInfoZpRv,
  ApobGetMemClkFreqZpRv,
  ApobGetDdrMaxRateZpRv,
  ApobGetMemGenInfoElementZpRv,
  ApobGetNumberOfValidThresholdsZpRv,
  ApobGetThresholdsZpRv
};


STATIC EFI_PEI_PPI_DESCRIPTOR mApobCommonServicePpiList =
{
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gApobCommonServicePpiGuid,
  &mApobCommonServicePpi
};


EFI_STATUS
EFIAPI
ApobZpRvPeiDriverEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS Status;

  IDS_HDT_CONSOLE_PSP_TRACE ("ApobZpRvPeiDriverEntry >>\n");

  // Public APOB PPI
  IDS_HDT_CONSOLE_PSP_TRACE ("\tInstall PPI\n");
  Status = (**PeiServices).InstallPpi (PeiServices, &mApobCommonServicePpiList);
  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("InstallPpi fail\n");
    ASSERT (FALSE);
  }


  IDS_HDT_CONSOLE_PSP_TRACE ("ApobZpRvPeiDriverEntry <<\n");

  return EFI_SUCCESS;
}


