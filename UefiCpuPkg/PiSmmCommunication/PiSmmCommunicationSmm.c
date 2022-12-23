/** @file
PiSmmCommunication SMM Driver.

Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <PiSmm.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/SmmMemLib.h>
#include <Protocol/SmmSwDispatch2.h>
#include <Protocol/SmmCommunication.h>
#include <Ppi/SmmCommunication.h>

#include "PiSmmCommunicationPrivate.h"
//(AMI AMD porting) For InitSmmS3ResumeState >>
#include <Library/HobLib.h>
#include <Guid/AcpiS3Context.h>
#include <Guid/SmramMemoryReserve.h>
#include <Protocol/SmmAccess2.h>
//(AMI AMD porting) For InitSmmS3ResumeState <<

EFI_SMM_COMMUNICATION_CONTEXT  mSmmCommunicationContext = {
  SMM_COMMUNICATION_SIGNATURE
};

/**
  Set SMM communication context.
**/
VOID
SetCommunicationContext (
  VOID
  )
{
  EFI_STATUS  Status;

  Status = gSmst->SmmInstallConfigurationTable (
                    gSmst,
                    &gEfiPeiSmmCommunicationPpiGuid,
                    &mSmmCommunicationContext,
                    sizeof(mSmmCommunicationContext)
                    );
  ASSERT_EFI_ERROR (Status);
}

/**
  Dispatch function for a Software SMI handler.

  @param DispatchHandle  The unique handle assigned to this handler by SmiHandlerRegister().
  @param Context         Points to an optional handler context which was specified when the
                         handler was registered.
  @param CommBuffer      A pointer to a collection of data in memory that will
                         be conveyed from a non-SMM environment into an SMM environment.
  @param CommBufferSize  The size of the CommBuffer.

  @retval EFI_SUCCESS Command is handled successfully.

**/
EFI_STATUS
EFIAPI
PiSmmCommunicationHandler (
  IN EFI_HANDLE  DispatchHandle,
  IN CONST VOID  *Context         OPTIONAL,
  IN OUT VOID    *CommBuffer      OPTIONAL,
  IN OUT UINTN   *CommBufferSize  OPTIONAL
  )
{
  UINTN                            CommSize;
  EFI_STATUS                       Status;
  EFI_SMM_COMMUNICATE_HEADER       *CommunicateHeader;
  EFI_PHYSICAL_ADDRESS             *BufferPtrAddress;

  DEBUG ((EFI_D_INFO, "PiSmmCommunicationHandler Enter\n"));

  BufferPtrAddress = (EFI_PHYSICAL_ADDRESS *)(UINTN)mSmmCommunicationContext.BufferPtrAddress;
  CommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *)(UINTN)*BufferPtrAddress;
  DEBUG ((EFI_D_INFO, "PiSmmCommunicationHandler CommunicateHeader - %x\n", CommunicateHeader));
  if (CommunicateHeader == NULL) {
    DEBUG ((EFI_D_INFO, "PiSmmCommunicationHandler is NULL, needn't to call dispatch function\n"));
    Status = EFI_SUCCESS;
  } else {
    if (!SmmIsBufferOutsideSmmValid ((UINTN)CommunicateHeader, OFFSET_OF (EFI_SMM_COMMUNICATE_HEADER, Data))) {
      DEBUG ((EFI_D_INFO, "PiSmmCommunicationHandler CommunicateHeader invalid - 0x%x\n", CommunicateHeader));
      Status = EFI_SUCCESS;
      goto Done;
    }

    CommSize = (UINTN)CommunicateHeader->MessageLength;
    if (!SmmIsBufferOutsideSmmValid ((UINTN)&CommunicateHeader->Data[0], CommSize)) {
      DEBUG ((EFI_D_INFO, "PiSmmCommunicationHandler CommunicateData invalid - 0x%x\n", &CommunicateHeader->Data[0]));
      Status = EFI_SUCCESS;
      goto Done;
    }

    //
    // Call dispatch function
    //
    DEBUG ((EFI_D_INFO, "PiSmmCommunicationHandler Data - %x\n", &CommunicateHeader->Data[0]));
    Status = gSmst->SmiManage (
                      &CommunicateHeader->HeaderGuid,
                      NULL,
                      &CommunicateHeader->Data[0],
                      &CommSize
                      );
  }

Done:
  DEBUG ((EFI_D_INFO, "PiSmmCommunicationHandler %r\n", Status));
  DEBUG ((EFI_D_INFO, "PiSmmCommunicationHandler Exit\n"));

  return (Status == EFI_SUCCESS) ? EFI_SUCCESS : EFI_INTERRUPT_PENDING;
}

/**
  Allocate EfiACPIMemoryNVS below 4G memory address.

  This function allocates EfiACPIMemoryNVS below 4G memory address.

  @param  Size         Size of memory to allocate.

  @return Allocated address for output.

**/
VOID*
AllocateAcpiNvsMemoryBelow4G (
  IN   UINTN   Size
  )
{
  UINTN                 Pages;
  EFI_PHYSICAL_ADDRESS  Address;
  EFI_STATUS            Status;
  VOID*                 Buffer;

  Pages = EFI_SIZE_TO_PAGES (Size);
  Address = 0xffffffff;

  Status  = gBS->AllocatePages (
                   AllocateMaxAddress,
                   EfiACPIMemoryNVS,
                   Pages,
                   &Address
                   );
  ASSERT_EFI_ERROR (Status);

  Buffer = (VOID *) (UINTN) Address;
  ZeroMem (Buffer, Size);

  return Buffer;
}

//(AMI AMD porting) AMD CPU needs to save gSmst only for S3 >>
/**
  Get SMRAM information form HOB(gEfiSmmPeiSmramMemoryReserveGuid).

  @param[in] SmmS3ResumeState  The information which is saved for SMM S3

  @retval EFI_SUCEESS     
  @return Others          Some error occurs.
**/
EFI_STATUS
EFIAPI
GetSmramInfoByHob (
  IN OUT EFI_PHYSICAL_ADDRESS    *ReservedAddress
  )
{
    EFI_HOB_GUID_TYPE               *GuidHob;
    EFI_SMRAM_HOB_DESCRIPTOR_BLOCK  *SmramDescriptorBlock;
    UINTN                           Index;
    UINTN                           NumberOfRegions;
    BOOLEAN                         FoundReservedArea;

    //
    // Get SMRAM information
    //
    GuidHob = GetFirstGuidHob (&gEfiSmmPeiSmramMemoryReserveGuid);

    if (GuidHob == NULL) {
        return EFI_NOT_FOUND;
    }

    SmramDescriptorBlock = (EFI_SMRAM_HOB_DESCRIPTOR_BLOCK *) GET_GUID_HOB_DATA (GuidHob);

    if (SmramDescriptorBlock == NULL) {
        return EFI_NOT_FOUND;
    }

    NumberOfRegions = SmramDescriptorBlock->NumberOfSmmReservedRegions;

    FoundReservedArea = FALSE;
    for (Index = 0; Index < NumberOfRegions; Index++)
    {
        if (SmramDescriptorBlock->Descriptor[Index].PhysicalSize == EFI_PAGE_SIZE)
        {
            if (SmramDescriptorBlock->Descriptor[Index].PhysicalSize < sizeof(SMM_S3_RESUME_STATE))
            {
                DEBUG ((DEBUG_INFO, "The SMM S3 reserved area size is not enough to save S3 data. \n"));
                DEBUG ((DEBUG_INFO, "The SMM S3 reserved size is  %x. \n", SmramDescriptorBlock->Descriptor[Index].PhysicalSize));
                DEBUG ((DEBUG_INFO, "The SMM S3 data size is  %x. \n", sizeof(SMM_S3_RESUME_STATE)));
                return EFI_BUFFER_TOO_SMALL;
            }
            FoundReservedArea = TRUE;
            break;
        }
    }

    if (FoundReservedArea == TRUE)
    {
        *ReservedAddress = SmramDescriptorBlock->Descriptor[Index].CpuStart;
        return EFI_SUCCESS;
    }
    else
    {
        return EFI_NOT_FOUND;
    }

}

/**
  Get SMRAM information form protocol(gEfiSmmAccess2ProtocolGuid).

  @param[in] SmmS3ResumeState  The information which is saved for SMM S3

  @retval EFI_SUCEESS     
  @return Others          Some error occurs.
**/
EFI_STATUS
EFIAPI
GetSmramInfoByProtocol (
  IN OUT EFI_PHYSICAL_ADDRESS    *ReservedAddress
  )
{
    UINTN                           Index;
    EFI_SMM_ACCESS2_PROTOCOL        *SmmAccess;
    UINTN                           Size;
    EFI_SMRAM_DESCRIPTOR            *SmramRanges;
    UINTN                           SmramRangeCount;
    EFI_STATUS                      Status;
    BOOLEAN                         FoundReservedArea;

    Status = gBS->LocateProtocol (&gEfiSmmAccess2ProtocolGuid, NULL, (VOID **)&SmmAccess);
    if (EFI_ERROR(Status))
    {
        return Status;
    }

    Size = 0;
    Status = SmmAccess->GetCapabilities (SmmAccess, &Size, NULL);
    if (Status != EFI_BUFFER_TOO_SMALL)
    {
        return Status;
    }

    Status = gBS->AllocatePool (EfiBootServicesData, Size, (VOID **)&SmramRanges);
    if (EFI_ERROR(Status))
    {
        return Status;
    }

    Status = SmmAccess->GetCapabilities (SmmAccess, &Size, SmramRanges);
    if (EFI_ERROR(Status))
    {
        gBS->FreePool(SmramRanges);
        return Status;
    }

    SmramRangeCount = Size / sizeof (EFI_SMRAM_DESCRIPTOR);

    FoundReservedArea = FALSE;
    for (Index = 0; Index < SmramRangeCount; Index++)
    {
        if (SmramRanges[Index].PhysicalSize == EFI_PAGE_SIZE)
        {
            if (SmramRanges[Index].PhysicalSize < sizeof(SMM_S3_RESUME_STATE))
            {
                DEBUG ((DEBUG_INFO, "The SMM S3 reserved area size is not enough to save S3 data. \n"));
                DEBUG ((DEBUG_INFO, "The SMM S3 reserved size is  %x. \n", SmramRanges[Index].PhysicalSize));
                DEBUG ((DEBUG_INFO, "The SMM S3 data size is  %x. \n", sizeof(SMM_S3_RESUME_STATE)));
                gBS->FreePool(SmramRanges);
                return EFI_BUFFER_TOO_SMALL;
            }
            FoundReservedArea = TRUE;
            break;
        }
    }

    if (FoundReservedArea == TRUE)
    {
        *ReservedAddress = (UINTN)SmramRanges[Index].CpuStart;
        gBS->FreePool(SmramRanges);
        return EFI_SUCCESS;
    }
    else
    {
        gBS->FreePool(SmramRanges);
        return EFI_NOT_FOUND;
    }
}

/**
  Initialize SMM S3 resume state structure used during S3 Resume.

**/
VOID
InitSmmS3ResumeState (
    VOID
  )
{
    EFI_STATUS                      Status;
    EFI_PHYSICAL_ADDRESS            ReservedAddr;
    SMM_S3_RESUME_STATE             *SmmS3ResumeState;

    //
    // Get SMRAM information
    //
    Status = GetSmramInfoByHob(&ReservedAddr);
    if (EFI_ERROR(Status))
    {
        Status = GetSmramInfoByProtocol(&ReservedAddr);
    }
    DEBUG ((DEBUG_INFO, "Get SMRAM information Status = %r\n", Status));

    if (EFI_ERROR(Status))
    {
        DEBUG ((DEBUG_INFO, "No SMM S3 reserved area to save S3 data. \n"));
        return;
    }

    SmmS3ResumeState = (SMM_S3_RESUME_STATE *)ReservedAddr;
    DEBUG ((DEBUG_INFO, "SMM S3 Structure = %x\n", SmmS3ResumeState));

    ZeroMem (SmmS3ResumeState, sizeof (SMM_S3_RESUME_STATE));

    SmmS3ResumeState->Smst = (EFI_PHYSICAL_ADDRESS)(UINTN)gSmst;

    if (sizeof (UINTN) == sizeof (UINT64)) {
      SmmS3ResumeState->Signature = SMM_S3_RESUME_SMM_64;
    }
    if (sizeof (UINTN) == sizeof (UINT32)) {
      SmmS3ResumeState->Signature = SMM_S3_RESUME_SMM_32;
    }

}
//(AMI AMD porting) AMD CPU needs to save gSmst only for S3 <<

/**
  Entry Point for PI SMM communication SMM driver.

  @param[in] ImageHandle  Image handle of this driver.
  @param[in] SystemTable  A Pointer to the EFI System Table.

  @retval EFI_SUCEESS
  @return Others          Some error occurs.
**/
EFI_STATUS
EFIAPI
PiSmmCommunicationSmmEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                    Status;
  EFI_SMM_SW_DISPATCH2_PROTOCOL *SmmSwDispatch2;
  EFI_SMM_SW_REGISTER_CONTEXT   SmmSwDispatchContext;
  EFI_HANDLE                    DispatchHandle;
  EFI_PHYSICAL_ADDRESS          *BufferPtrAddress;

  //
  // Register software SMI handler
  //
  Status = gSmst->SmmLocateProtocol (
                    &gEfiSmmSwDispatch2ProtocolGuid,
                    NULL,
                    (VOID **)&SmmSwDispatch2
                    );
  ASSERT_EFI_ERROR (Status);

  SmmSwDispatchContext.SwSmiInputValue = (UINTN)-1;
  Status = SmmSwDispatch2->Register (
                             SmmSwDispatch2,
                             PiSmmCommunicationHandler,
                             &SmmSwDispatchContext,
                             &DispatchHandle
                             );
  ASSERT_EFI_ERROR (Status);

  DEBUG ((EFI_D_INFO, "SmmCommunication SwSmi: %x\n", (UINTN)SmmSwDispatchContext.SwSmiInputValue));

  BufferPtrAddress = AllocateAcpiNvsMemoryBelow4G (sizeof(EFI_PHYSICAL_ADDRESS));
  ASSERT (BufferPtrAddress != NULL);
  DEBUG ((EFI_D_INFO, "SmmCommunication BufferPtrAddress: 0x%016lx, BufferPtr: 0x%016lx\n", (EFI_PHYSICAL_ADDRESS)(UINTN)BufferPtrAddress, *BufferPtrAddress));

  //
  // Save context
  //
  mSmmCommunicationContext.SwSmiNumber = (UINT32)SmmSwDispatchContext.SwSmiInputValue;
  mSmmCommunicationContext.BufferPtrAddress = (EFI_PHYSICAL_ADDRESS)(UINTN)BufferPtrAddress;
  SetCommunicationContext ();

  //(AMI AMD Porting) Saving gSmst for S3
  InitSmmS3ResumeState();
  //(AMI AMD Porting) Saving gSmst for S3

  return Status;
}
