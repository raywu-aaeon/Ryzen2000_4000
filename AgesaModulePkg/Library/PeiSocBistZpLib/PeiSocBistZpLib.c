/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD SOC BIST Library
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Lib
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 *
 */
/*
 ******************************************************************************
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
#include "Uefi.h"
#include <Library/BaseLib.h>
#include "AMD.h"
#include "Filecode.h"
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Ppi/NbioSmuServicesPpi.h>

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#define FILECODE LIBRARY_PEISOCBISTZPLIB_PEISOCBISTZPLIB_FILECODE

 /*---------------------------------------------------------------------------------------*/
 /**
  *
  * Reads the status of CCX BIST
  *
  * @param[in]      CcxNumber              Ccx number to read BIST data from
  * @param[in]      SystemDieCount         System based die number
  * @param[in]      PeiServices            Pointer to PEI services
  *
  *
  * @retval         AGESA_ALERT            A BIST error has occurred
  * @retval         AGESA_SUCCESS          No BIST errors have occured
  */
AGESA_STATUS
ReadCcxBistData (
  IN       UINTN            CcxNumber,
  IN       UINTN            SystemDieCount,
  IN CONST EFI_PEI_SERVICES **PeiServices
  )
{
  UINT8                         BistEn;
  UINT8                         ColdResetMBistEn;
  UINT8                         BistDone;
  UINT8                         BistPF;
  UINT32                        BistStatus;
  UINT32                        BistEnFuse;
  UINT32                        ColdResetMBistEnFuse;
  EFI_STATUS                    CalledStatus;
  PEI_AMD_NBIO_SMU_SERVICES_PPI *NbioSmuServices;


  CalledStatus = (**PeiServices).LocatePpi (
                                 PeiServices,
                                 &gAmdNbioSmuServicesPpiGuid,
                                 0,
                                 NULL,
                                 &NbioSmuServices
                                 );

  ASSERT (CalledStatus == EFI_SUCCESS);

  NbioSmuServices->SmuRegisterRead (NbioSmuServices, SystemDieCount, 0x5D0CC, &BistEnFuse);
  BistEn = (BistEnFuse >> 4) & 0x1;

  NbioSmuServices->SmuRegisterRead (NbioSmuServices, SystemDieCount, 0x5D0DC, &ColdResetMBistEnFuse);
  ColdResetMBistEn = (ColdResetMBistEnFuse >> 25) & 0x1;

  // Check BIST status only if BIST is fuse enabled
  if ((BistEn == 0x1) || (ColdResetMBistEn == 0x1)){
    NbioSmuServices->SmuRegisterRead (NbioSmuServices, SystemDieCount, 0x18080064 | (CcxNumber << 22), &BistStatus);

    BistDone = (BistStatus >> 9) & 0x1;
    if (BistDone == 0x1) {
      BistPF = (BistStatus >> 8) & 0x1;
      if (BistPF == 0) {
        return AGESA_ALERT;
      }
    }
  }
  return AGESA_SUCCESS;
}

/*---------------------------------------------------------------------------------------*/
 /**
  *
  * Reads the status of non-CCX BIST
  *
  * @param[in]      DieNumber              Die number to read data from
  * @param[out]     BistData               Value of BIST status register
  * @param[in]      PeiServices            Pointer to PEI services
  *
  * @retval         AGESA_ALERT            A BIST error has occurred
  * @retval         AGESA_SUCCESS          No BIST errors have occured
  */
AGESA_STATUS
ReadNonCcxBistData (
  IN       UINTN            DieNumber,
       OUT UINTN            *BistData,
  IN CONST EFI_PEI_SERVICES **PeiServices
  )
{
  UINT8                         RunMBist;
  UINT32                        RunMBistFuse;
  EFI_STATUS                    CalledStatus;
  PEI_AMD_NBIO_SMU_SERVICES_PPI *NbioSmuServices;

  CalledStatus = (**PeiServices).LocatePpi (
                                 PeiServices,
                                 &gAmdNbioSmuServicesPpiGuid,
                                 0,
                                 NULL,
                                 &NbioSmuServices
                                 );

  ASSERT (CalledStatus == EFI_SUCCESS);

  NbioSmuServices->SmuRegisterRead (NbioSmuServices, DieNumber, 0x5D258, &RunMBistFuse);
  RunMBist = (RunMBistFuse >> 6) & 0x1;

  if (RunMBist == 0x1) {
    NbioSmuServices->SmuRegisterRead (NbioSmuServices, DieNumber, 0x03810038, BistData);

    if (*BistData != 0) {
      return AGESA_ALERT;
    }
  }

  return AGESA_SUCCESS;
}
