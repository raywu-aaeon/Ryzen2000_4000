/*****************************************************************************
 *
 * Copyright 2008 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting You permission to use this software and documentation (if
 * any) (collectively, the "Software") pursuant to the terms and conditions of
 * the Software License Agreement included with the Software. If You do not have
 * a copy of the Software License Agreement, contact Your AMD representative for
 * a copy.
 *
 * You agree that You will not reverse engineer or decompile the Software, in
 * whole or in part, except as allowed by applicable law.
 *
 * WARRANTY DISCLAIMER: THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND. AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
 * BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, QUALITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT AND WARRANTIES
 * ARISING FROM CUSTOM OF TRADE OR COURSE OF USAGE WITH RESPECT TO THE SOFTWARE,
 * INCLUDING WITHOUT LIMITATION, THAT THE SOFTWARE WILL RUN UNINTERRUPTED OR
 * ERROR-FREE. THE ENTIRE RISK ASSOCIATED WITH THE USE OF THE SOFTWARE IS
 * ASSUMED BY YOU. Some jurisdictions do not allow the exclusion of implied
 * warranties, so the above exclusion may not apply to You, but only to the
 * extent required by law.
 *
 * LIMITATION OF LIABILITY AND INDEMNIFICATION: TO THE EXTENT NOT PROHIBITED BY
 * APPLICABLE LAW, AMD AND ITS LICENSORS WILL NOT, UNDER ANY CIRCUMSTANCES BE
 * LIABLE TO YOU FOR ANY PUNITIVE, DIRECT, INCIDENTAL, INDIRECT, SPECIAL OR
 * CONSEQUENTIAL DAMAGES ARISING FROM POSSESSION OR USE OF THE SOFTWARE OR
 * OTHERWISE IN CONNECTION WITH ANY PROVISION OF THIS AGREEMENT EVEN IF AMD AND
 * ITS LICENSORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. THIS
 * INCLUDES, WITHOUT LIMITATION, DAMAGES DUE TO LOST OR MISAPPROPRIATED DATA,
 * LOST PROFITS OR CONFIDENTIAL OR OTHER INFORMATION, FOR BUSINESS INTERRUPTION,
 * FOR PERSONAL INJURY, FOR LOSS OF PRIVACY, FOR FAILURE TO MEET ANY DUTY
 * INCLUDING OF GOOD FAITH OR REASONABLE CARE, FOR NEGLIGENCE AND FOR ANY OTHER
 * PECUNIARY OR OTHER LOSS WHTSOEVER. In no event shall AMD's total liability to
 * You for all damages, losses, and causes of action (whether in contract, tort
 * (including negligence) or otherwise) exceed the amount of $50 USD. You agree
 * to defend, indemnify and hold harmless AMD, its subsidiaries and affiliates
 * and their respective licensors, directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your
 * possession or use of the Software or violation of the terms and conditions of
 * this Agreement.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS: Notice to U.S. Government End Users. The
 * Software and related documentation are "commercial items", as that term is
 * defined at 48 C.F.R. Section 2.101, consisting of "commercial computer
 * software" and "commercial computer software documentation", as such terms are
 * used in 48 C.F.R. Section 12.212 and 48 C.F.R. Section 227.7202,
 * respectively. Consistent with 48 C.F.R. Section 12.212 or 48 C.F.R. Sections
 * 227.7202-1 through 227.7202-4, as applicable, the commercial computer
 * software and commercial computer software documentation are being licensed to
 * U.S. Government end users: (a) only as commercial items, and (b) with only
 * those rights as are granted to all other end users pursuant to the terms and
 * conditions set forth in this Agreement. Unpublished rights are reserved under
 * the copyright laws of the United States.
 *
 * EXPORT RESTRICTIONS:  You shall adhere to all applicable U.S. import/export
 * laws and regulations, as well as the import/export control laws and
 * regulations of other countries as applicable. You further agree You will not
 * export, re-export, or transfer, directly or indirectly, any product,
 * technical data, software or source code received from AMD under this license,
 * or the direct product of such technical data or software to any country for
 * which the United States or any other applicable government requires an export
 * license or other governmental approval without first obtaining such licenses
 * or approvals, or in violation of any applicable laws or regulations of the
 * United States or the country where the technical data or software was
 * obtained. You acknowledges the technical data and software received will not,
 * in the absence of authorization from U.S. or local law and regulations as
 * applicable, be used by or exported, re-exported or transferred to: (i) any
 * sanctioned or embargoed country, or to nationals or residents of such
 * countries; (ii) any restricted end-user as identified on any applicable
 * government end-user list; or (iii) any party where the end-use involves
 * nuclear, chemical/biological weapons, rocket systems, or unmanned air
 * vehicles.  For the most current Country Group listings, or for additional
 * information about the EAR or Your obligations under those regulations, please
 * refer to the website of the U.S. Bureau of Industry and Security at
 * http://www.bis.doc.gov/.
 *******************************************************************************
 */
#include <PiPei.h>
#include <Ppi/AmdPspFtpmPpi.h>
#include <Ppi/MemoryDiscovered.h>
#include <Ppi/AmdPspRecoveryDetectPpi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdPspCommonLib.h>
#include <Library/AmdCapsuleLib.h>
#include <Library/AmdPspFtpmLib.h>
#include <Library/FchBaseLib.h>
#include <Filecode.h>

#define FILECODE PSP_AMDPSPFTPMPEI_AMDPSPFTPMPEI_FILECODE

EFI_STATUS
EFIAPI
FtpmMemoryDiscoveredPpiCallback (
  IN  EFI_PEI_SERVICES                **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
  IN  VOID                            *InvokePpi
  );

EFI_STATUS
GetFtpmStatus (
  IN       PSP_FTPM_PPI         *This,
  IN OUT   UINTN                *FtpmStatus
  )
{
  return (FtpmGetInfo (FtpmStatus));
}

EFI_STATUS
SendFtpmCommand (
  IN     PSP_FTPM_PPI         *This,
  IN     VOID                 *CommandBuffer,
  IN     UINTN                 CommandSize
  )
{
  return FtpmSendCommand (
      CommandBuffer,
      CommandSize);
}

EFI_STATUS
GetFtpmResponse (
  IN       PSP_FTPM_PPI          *This,
  IN OUT   VOID                  *ResponseBuffer,
  IN OUT   UINTN                 *ResponseSize
  )
{

  EFI_STATUS Status;
  Status = FtpmGetResponse (
                            ResponseBuffer,
                            ResponseSize
                          );
  return (Status);
}

EFI_STATUS
ExecuteFtpmCommand (
  IN       PSP_FTPM_PPI         *This,
  IN       VOID                 *CommandBuffer,
  IN       UINTN                CommandSize,
  IN OUT   VOID                 *ResponseBuffer,
  IN OUT   UINTN                *ResponseSize
  )
{
  return FtpmExecuteCommand (
                              CommandBuffer,
                              CommandSize,
                              ResponseBuffer,
                              ResponseSize
                             );
}


STATIC PSP_FTPM_PPI mAmdPspFtpmPpi = {
  ExecuteFtpmCommand,
  GetFtpmStatus,
  SendFtpmCommand,
  GetFtpmResponse,
};

STATIC PSP_FTPM_FACTORY_RESET_PPI mAmdPspFtpmFactoryResetPpi = {
  0x00000001ul
};

STATIC EFI_PEI_PPI_DESCRIPTOR mAmdPspFtpmPpiList =
{
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdPspFtpmPpiGuid,
  &mAmdPspFtpmPpi
};

STATIC EFI_PEI_PPI_DESCRIPTOR mAmdPspFtpmFactoryResetPpiList =
{
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdPspFtpmFactoryResetPpiGuid,
  &mAmdPspFtpmFactoryResetPpi
};

EFI_PEI_NOTIFY_DESCRIPTOR   mMemoryDicoverPpiCallback = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiMemoryDiscoveredPpiGuid,
  FtpmMemoryDiscoveredPpiCallback
};

STATIC AMD_PSP_RECOVERY_DETECT_PPI mPspRecoveryDetectPpi = {
  0x01
};

STATIC EFI_PEI_PPI_DESCRIPTOR mPspRecoveryDetectedPpiList =
{
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdPspRecoveryDetectPpiGuid,
  &mPspRecoveryDetectPpi
};

EFI_STATUS
EFIAPI
FtpmMemoryDiscoveredPpiCallback (
  IN  EFI_PEI_SERVICES                **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
  IN  VOID                            *InvokePpi
  )
{
  EFI_STATUS                  Status;
  EFI_PHYSICAL_ADDRESS        FtpmCommandBuffer;
  EFI_PHYSICAL_ADDRESS        FtpmResponseBuffer;
  UINT32                      Caps;
  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.FtpmPei.MemoryDiscoveredPpiCallback\n");

  //If PSP feature turn off, exit the callback to avoid hang when swap part
  if ((PcdGetBool (PcdAmdPspEnable) == 0) ||
      (PcdGet8 (PcdAmdPspSystemTpmConfig) != SYSTEM_TPM_CONFIG_PSP_FTPM)) {
    return EFI_SUCCESS;
  }

  AGESA_TESTPOINT (TpPspfTpmPeiMemCallbackEntry, NULL);
  //Send PSP mailbox command to ensure Ctrl Area have been initialed
  Status = CheckFtpmCaps (&Caps);
  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Get fTPM cap fail\n");
    return Status;
  }
  //Supported & factory reset can't be set at the same time
  ASSERT (Caps  != (PSP_CAP_TPM_SUPPORTED | PSP_CAP_TPM_REQ_FACTORY_RESET));

  if (Caps == PSP_CAP_TPM_SUPPORTED) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Allocate memory for FTPM\n");
    Status = (*PeiServices)->AllocatePages (
                                PeiServices,
                                EfiBootServicesData,
                                EFI_SIZE_TO_PAGES (FTPM_COMMAND_BUFFER_SIZE + \
                                                    FTPM_RESPONSE_BUFFER_SIZE),
                                &FtpmCommandBuffer
                                );

    if (EFI_ERROR (Status)) {
      IDS_HDT_CONSOLE_PSP_TRACE ("Allocate Memory fail\n");
      return Status;
    }

    FtpmResponseBuffer      = FtpmCommandBuffer + FTPM_COMMAND_BUFFER_SIZE;

    SetMem ((VOID *) (UINTN) FtpmCommandBuffer, FTPM_COMMAND_BUFFER_SIZE + FTPM_RESPONSE_BUFFER_SIZE, 0);

    IDS_HDT_CONSOLE_PSP_TRACE ("AssignMemory for FTPM\n");
    Status = FtpmAssignMemory (
      (UINTN)FtpmCommandBuffer,
      FTPM_COMMAND_BUFFER_SIZE,
      (UINTN)FtpmResponseBuffer,
      FTPM_RESPONSE_BUFFER_SIZE
    );

    if (EFI_ERROR (Status)) {
      IDS_HDT_CONSOLE_PSP_TRACE ("FtpmAssignMemory fail\n");
      return Status;
    }

    IDS_HDT_CONSOLE_PSP_TRACE ("\tAllocate CmdBuf:0x%lx ResBuf:0x%lx\n", FtpmCommandBuffer, FtpmResponseBuffer);

    IDS_HDT_CONSOLE_PSP_TRACE ("\tInstall PspTis PPI\n");
    Status = (**PeiServices).InstallPpi (PeiServices, &mAmdPspFtpmPpiList);
    if (EFI_ERROR (Status)) {
      IDS_HDT_CONSOLE_PSP_TRACE ("InstallPpi fail\n");
    }
  } else if (Caps == PSP_CAP_TPM_REQ_FACTORY_RESET) {
    IDS_HDT_CONSOLE_PSP_TRACE ("FTPM FACTORY_RESET detected\n");
    //Install a PPI to notify SBIOS
    IDS_HDT_CONSOLE_PSP_TRACE ("\tInstall fTPM factory reset PPI\n");
    Status = (**PeiServices).InstallPpi (PeiServices, &mAmdPspFtpmFactoryResetPpiList);
    if (EFI_ERROR (Status)) {
      IDS_HDT_CONSOLE_PSP_TRACE ("InstallPpi fail\n");
    }
  } else if (Caps == PSP_CAP_FTPM_NEED_RECOVERY) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Ftpm Recovery Flag Detected\n");
    Status = (**PeiServices).InstallPpi (PeiServices, &mPspRecoveryDetectedPpiList);
    ASSERT (Status == EFI_SUCCESS);
  }
  AGESA_TESTPOINT (TpPspfTpmPeiMemCallbackExit, NULL);
  return Status;
}


/*++

Routine Description:

  PSP Driver Entry. Initialize PSP device and report DRAM info to PSP once found

Arguments:

Returns:

  EFI_STATUS

--*/
EFI_STATUS
AmdPspFtpmPeiDriverEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS            Status = EFI_SUCCESS;
  AGESA_TESTPOINT (TpPspfTpmPeiEntry, NULL);
  //If PSP feature turn off, exit the driver
  if ((CheckPspDevicePresent () == FALSE) ||
      (PcdGetBool (PcdAmdPspEnable) == 0) ||
      (PcdGet8 (PcdAmdPspSystemTpmConfig) != SYSTEM_TPM_CONFIG_PSP_FTPM)) {
    return EFI_SUCCESS;
  }

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.Drv.FtpmPei Enter\n");
  //
  // Check if Boot mode is boot then hook for MemoryDiscovery protocol
  //
  if ((FchReadSleepType () != 3) && (AmdCapsuleGetStatus () == FALSE)) {
    Status = (**PeiServices).NotifyPpi (PeiServices, &mMemoryDicoverPpiCallback);
  }
  IDS_HDT_CONSOLE_PSP_TRACE ("FtpmPei Exit\n");
  AGESA_TESTPOINT (TpPspfTpmPeiExit, NULL);

  return Status;
}


