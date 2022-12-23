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
 ******************************************************************************
 */

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>

#include <Protocol/AmdNbioSmuServicesProtocol.h>

#include <Dxe/AmdPbsSetupDxe/AmdPbsConfig.h>

#include "FanPolicy.h"

#define SMC_MSG_GetSustainedPowerAndThmLimit  0x43
  
/**
  SmuServices Protocol notification event handler.

  @param[in] Event    Event whose notification function is being invoked.
  @param[in] Context  Pointer to the notification function's context.
**/
VOID
EFIAPI
SmuServicesNotification (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  EFI_STATUS                           Status;
  FAN_POLICY_TABLE                     *FanPolicyTable;
  UINT32                               SmuArg[6];
  DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL   *NbioSmuServiceProtocolPtr;
  UINT32 PowerLimit = 0;
  
  // Read Tctl from SMU message
  Status = gBS->LocateProtocol (
               &gAmdNbioSmuServicesProtocolGuid,
               NULL,
               (VOID **)&NbioSmuServiceProtocolPtr
               );
  DEBUG((EFI_D_INFO," Locate Smu Services %r\n",Status));
  if (EFI_ERROR(Status)) {
    return;
  }

  SmuArg[0] = 0;
  SmuArg[1] = 0;
  SmuArg[2] = 0;
  SmuArg[3] = 0;
  SmuArg[4] = 0;
  SmuArg[5] = 0;

  NbioSmuServiceProtocolPtr->AmdSmuServiceRequest (NbioSmuServiceProtocolPtr, 0, SMC_MSG_GetSustainedPowerAndThmLimit, SmuArg, SmuArg);

  PowerLimit = ((SmuArg[0] & 0x00FF0000) >> 16);
  DEBUG ((DEBUG_INFO, " TDP/TJMAX = 0x%x  TDP After conversion = %d \n", SmuArg[0] , PowerLimit ));

  if(PowerLimit > 25){
    FanPolicyTable = (FAN_POLICY_TABLE *) &DefaultAM4FanTable[1];
  }else{
    FanPolicyTable = (FAN_POLICY_TABLE *) &DefaultAM4FanTable[0];
  }
    
  if (PcdGet8 (PcdFanTableOverride)) {
    // CBS is changed, use user defined values.
    DEBUG((EFI_D_INFO," Use User Fan Values\n"));
  } else {
    // read the TDP and TJMAX
    if (SmuArg[0] != 0) {
      //while (FanPolicyTable->TdpTjMax != 0) {
        //if (FanPolicyTable->TdpTjMax == SmuArg[0]) {
          DEBUG((EFI_D_INFO," Set Default Fan Table\n"));
          if (PcdGet8 (PcdForceFanPwmEn) == 0) {
            PcdSet8 (PcdForceFanPwmEn,     FanPolicyTable->FanPolicy.ForceFanPwmEn);
            PcdSet8 (PcdForceFanPwm,       FanPolicyTable->FanPolicy.ForceFanPwm);
          }
          PcdSet8 (PcdFanTableOverride,     FanPolicyTable->FanPolicy.FanTable_Override);
          PcdSet8 (PcdFanTableHysteresis,   FanPolicyTable->FanPolicy.FanTable_Hysteresis);
          PcdSet8 (PcdFanTableTempLow,      FanPolicyTable->FanPolicy.FanTable_TempLow);
          PcdSet8 (PcdFanTableTempMed,      FanPolicyTable->FanPolicy.FanTable_TempMed);
          PcdSet8 (PcdFanTableTempHigh,     FanPolicyTable->FanPolicy.FanTable_TempHigh);
          PcdSet8 (PcdFanTableTempCritical, FanPolicyTable->FanPolicy.FanTable_TempCritical);
          PcdSet8 (PcdFanTablePwmLow,       FanPolicyTable->FanPolicy.FanTable_PwmLow);
          PcdSet8 (PcdFanTablePwmMed,       FanPolicyTable->FanPolicy.FanTable_PwmMed);
          PcdSet8 (PcdFanTablePwmHigh,      FanPolicyTable->FanPolicy.FanTable_PwmHigh);
          PcdSet8 (PcdFanTablePwmFreq,      FanPolicyTable->FanPolicy.FanTable_PwmFreq);
          PcdSet8 (PcdFanTablePolarity,     FanPolicyTable->FanPolicy.FanTable_Polarity);
          //break;
        //}
        //FanPolicyTable ++;
      //}
    }
  }
  //
  // Close event, so it will not be invoked again.
  //
  gBS->CloseEvent (Event);

  return ;
}


/**
  Initialize Dummy Interrupt Handler for Unexpected exception #F

  @param ImageHandle     ImageHandle of the loaded driver
  @param SystemTable     Pointer to the System Table

  @retval EFI_SUCCESS            Successfully Initialized.
  @retval EFI_OUT_OF_RESOURCES   Not enough resources available to initialize driver.
  @retval EFI_DEVICE_ERROR       A device error occured attempting to initialize the driver.

**/
EFI_STATUS
EFIAPI
FanPolicyEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  VOID                 *Registration;
  //UINT32               RegEax;

  //AsmCpuid (0x80000001, &RegEax, NULL, NULL, NULL);
  // Only for Pinnacle
  //if ((RegEax & 0x00FF0FF0) != 0x00800F80) {
  //  return EFI_SUCCESS;
  //}

  //
  // Register event for ExitPmAuth, so that we can uninstall ACPI SDT protocol after ExitPmAuth.
  //
  EfiCreateProtocolNotifyEvent (
      &gAmdNbioSmuServicesProtocolGuid,
      TPL_CALLBACK,
      SmuServicesNotification,
      NULL,
      &Registration
      );
  DEBUG((EFI_D_INFO,"%a Create Protocol Notify On SmuServices\n",__FUNCTION__));
  return EFI_SUCCESS;
}
