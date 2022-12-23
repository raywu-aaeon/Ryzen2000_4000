/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD CCX BASE Library
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      CCX
 * @e sub-project:  Lib
 * @e \$Revision$   @e \$Date$
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


/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */

#include "Uefi.h"
#include <Library/BaseLib.h>
#include "AMD.h"
#include "Filecode.h"
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/CcxBaseX86Lib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/CcxBaseServicesProtocol.h>
#include "CcxBaseX86ServicesDxe.h"

#define FILECODE LIBRARY_DXECCXBASEX86SERVICESLIB_CCXBASEX86SERVICESDXE_FILECODE

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                           G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */
STATIC CCX_BASE_SERVICES_PROTOCOL mCcxBaseServices = {
  0x1,
  CcxGetMaxPhysAddr,
  CcxGetMaxProcCap
};



/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
EFI_STATUS
EFIAPI
CcxBaseServicesProtocolInstall (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  return (gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gAmdCcxBaseServicesProtocolGuid,
                  &mCcxBaseServices,
                  NULL
                  ));
}

/**
 *---------------------------------------------------------------------------------------
 *
 *  Returns the maximum physical address size
 *
 *  Parameters:
 *    @param[in]       This    Pointer to the CCX_BASE_SERVICES_PROTOCOL instance.
 *
 *    @return          UINT8   Maximum physical address size
 *
 *---------------------------------------------------------------------------------------
 */
UINT8
EFIAPI
CcxGetMaxPhysAddr (
  IN       CCX_BASE_SERVICES_PROTOCOL *This
  )
{
  UINT8       MemEncryptPhysAddWidth;
  UINT32      LFuncExt;
  CPUID_DATA  CpuId;


  MemEncryptPhysAddWidth = 0;

  LFuncExt = CcxGetLFuncExt ();

  if (LFuncExt >= 0x8000001F) {
    // Get value of CPUID_Fn8000001F_EBX[MemEncryptPhysAddWidth]
    AsmCpuid (
        0x8000001F,
        &(CpuId.EAX_Reg),
        &(CpuId.EBX_Reg),
        &(CpuId.ECX_Reg),
        &(CpuId.EDX_Reg)
      );
    MemEncryptPhysAddWidth = (UINT8) ((CpuId.EBX_Reg >> 6) & 0x3F);
  }

  return CcxGetPhysAddrSize () - MemEncryptPhysAddWidth;
}

/**
 *---------------------------------------------------------------------------------------
 *
 *  Returns the maximum processor capacity in the system
 *
 *  Parameters:
 *    @param[in]       This    Pointer to the CCX_BASE_SERVICES_PROTOCOL instance.
 *
 *    @return          UINT8   Maximum processor capacity
 *
 *---------------------------------------------------------------------------------------
 */
UINT8
EFIAPI
CcxGetMaxProcCap (
  IN       CCX_BASE_SERVICES_PROTOCOL *This
  )
{
  return ((1 << CcxGetApicIdCoreIdSize ()) * PcdGet8 (PcdAmdNumberOfPhysicalSocket));
}

