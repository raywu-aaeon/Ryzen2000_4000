/* $NoKeywords:$ */
/**
 * @file
 *
 * PSP TPM related functions in DXE
 *
 * Contains PSP TPM interface
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision: 310042 $   @e \$Date: 2014-12-25 16:09:57 +0800 (Thu, 25 Dec 2014) $
 */
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
 **/

#include <PiDxe.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdPspCommonLib.h>
#include <Library/AmdPspFtpmLib.h>
#include <Protocol/AmdPspFtpmProtocol.h>
#include <Filecode.h>

#define FILECODE PSP_AMDPSPFTPMDXE_AMDPSPFTPMDXE_FILECODE


EFI_STATUS
GetFtpmStatus (
  IN       PSP_FTPM_PROTOCOL    *This,
  IN OUT   UINTN                *FtpmStatus
  )
{

  return (FtpmGetInfo (FtpmStatus));
}

EFI_STATUS
SendFtpmCommand (
  IN     PSP_FTPM_PROTOCOL    *This,
  IN     VOID                 *CommandBuffer,
  IN     UINT32               CommandSize
  )
{
  return FtpmSendCommand (
      CommandBuffer,
      CommandSize);

}

EFI_STATUS
GetFtpmResponse (
  IN       PSP_FTPM_PROTOCOL     *This,
  IN OUT   VOID                  *ResponseBuffer,
  IN OUT   UINT32                *ResponseSize
  )
{
  EFI_STATUS Status;

  if (!ResponseBuffer) {
    return (EFI_NOT_FOUND);
  }

  Status =  FtpmGetResponse (
                            ResponseBuffer,
                            ResponseSize
                          );
  return (Status);
}

EFI_STATUS
ExecuteFtpmCommand (
  IN       PSP_FTPM_PROTOCOL    *This,
  IN       VOID                 *CommandBuffer,
  IN       UINT32                CommandSize,
  IN OUT   VOID                 *ResponseBuffer,
  IN OUT   UINT32               *ResponseSize
  )
{
  return FtpmExecuteCommand (
                                CommandBuffer,
                                CommandSize,
                                ResponseBuffer,
                                ResponseSize
                               );
}


PSP_FTPM_PROTOCOL mAmdPspFtpmProtocol = {
  ExecuteFtpmCommand,
  GetFtpmStatus,
  SendFtpmCommand,
  GetFtpmResponse,
};

EFI_STATUS
AmdPspFtpmDxeDriverEntry (
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )

{
  EFI_STATUS                  Status;
  EFI_HANDLE                  Handle;
  UINTN                       AllocateSize;
  UINTN                       CommandBuffer;
  UINTN                       ResponseBuffer;

  AGESA_TESTPOINT (TpPspfTpmDxeEntry, NULL);
  //If PSP feature turn off, exit the driver
  if ((CheckPspDevicePresent () == FALSE) ||
      (PcdGetBool (PcdAmdPspEnable) == 0) ||
      (PcdGet8 (PcdAmdPspSystemTpmConfig) != SYSTEM_TPM_CONFIG_PSP_FTPM)) {
    return EFI_SUCCESS;
  }

  CommandBuffer = 0;
  ResponseBuffer = 0;

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.Drv.FtpmDxe Enter\n");

  //
  // Allocate pages for TPM Control area (as well as command & response buffer)
  AllocateSize =  ( FTPM_COMMAND_BUFFER_SIZE  + FTPM_RESPONSE_BUFFER_SIZE );

  Status = gBS->AllocatePages (
                  AllocateAnyPages,
                  EfiReservedMemoryType,
                  EFI_SIZE_TO_PAGES (AllocateSize),
                  (EFI_PHYSICAL_ADDRESS *)&CommandBuffer);

  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  gBS->SetMem ((VOID *)CommandBuffer, AllocateSize, 0);
  ResponseBuffer = (UINTN)CommandBuffer + FTPM_COMMAND_BUFFER_SIZE;
  Status = FtpmAssignMemory (
    (UINTN)CommandBuffer,
    FTPM_COMMAND_BUFFER_SIZE,
    (UINTN)ResponseBuffer,
    FTPM_RESPONSE_BUFFER_SIZE
  );
  IDS_HDT_CONSOLE_PSP_TRACE ("\tAllocate CmdBuf:0x%x ResBuf:0x%x\n", CommandBuffer, ResponseBuffer);


  //
  // Install protocol to pass Ftpm info to rest of BIOS drivers
  //
  Handle = NULL;
  IDS_HDT_CONSOLE_PSP_TRACE ("\tInstall PspTis protocol\n");
  Status = gBS->InstallProtocolInterface (
                  &Handle,
                  &gAmdPspFtpmProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mAmdPspFtpmProtocol
                  );

  if (EFI_ERROR (Status)) {
    return (Status);
  }

  IDS_HDT_CONSOLE_PSP_TRACE ("FtpmDxe Exit\n");
  AGESA_TESTPOINT (TpPspfTpmDxeExit, NULL);
  return Status;
}

