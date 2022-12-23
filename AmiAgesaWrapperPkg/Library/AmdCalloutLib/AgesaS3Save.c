/* $NoKeywords:$ */
/**
 * @file
 *
 * AgesaS3Save.c
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project:
 * @e \$Revision: 309090 $ @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 *
 **/
/*****************************************************************************
  *
  * Copyright 2008 - 2018 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
  *
  * AMD is granting you permission to use this software (the Materials)
  * pursuant to the terms and conditions of your Software License Agreement
  * with AMD.  This header does *NOT* give you permission to use the Materials
  * or any rights under AMD's intellectual property.  Your use of any portion
  * of these Materials shall constitute your acceptance of those terms and
  * conditions.  If you do not agree to the terms and conditions of the Software
  * License Agreement, please do not use any portion of these Materials.
  *
  * CONFIDENTIALITY:  The Materials and all other information, identified as
  * confidential and provided to you by AMD shall be kept confidential in
  * accordance with the terms and conditions of the Software License Agreement.
  *
  * LIMITATION OF LIABILITY: THE MATERIALS AND ANY OTHER RELATED INFORMATION
  * PROVIDED TO YOU BY AMD ARE PROVIDED "AS IS" WITHOUT ANY EXPRESS OR IMPLIED
  * WARRANTY OF ANY KIND, INCLUDING BUT NOT LIMITED TO WARRANTIES OF
  * MERCHANTABILITY, NONINFRINGEMENT, TITLE, FITNESS FOR ANY PARTICULAR PURPOSE,
  * OR WARRANTIES ARISING FROM CONDUCT, COURSE OF DEALING, OR USAGE OF TRADE.
  * IN NO EVENT SHALL AMD OR ITS LICENSORS BE LIABLE FOR ANY DAMAGES WHATSOEVER
  * (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF PROFITS, BUSINESS
  * INTERRUPTION, OR LOSS OF INFORMATION) ARISING OUT OF AMD'S NEGLIGENCE,
  * GROSS NEGLIGENCE, THE USE OF OR INABILITY TO USE THE MATERIALS OR ANY OTHER
  * RELATED INFORMATION PROVIDED TO YOU BY AMD, EVEN IF AMD HAS BEEN ADVISED OF
  * THE POSSIBILITY OF SUCH DAMAGES.  BECAUSE SOME JURISDICTIONS PROHIBIT THE
  * EXCLUSION OR LIMITATION OF LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES,
  * THE ABOVE LIMITATION MAY NOT APPLY TO YOU.
  *
  * AMD does not assume any responsibility for any errors which may appear in
  * the Materials or any other related information provided to you by AMD, or
  * result from use of the Materials or any related information.
  *
  * You agree that you will not reverse engineer or decompile the Materials.
  *
  * NO SUPPORT OBLIGATION: AMD is not obligated to furnish, support, or make any
  * further information, software, technical information, know-how, or show-how
  * available to you.  Additionally, AMD retains the right to modify the
  * Materials at any time, without notice, and is not obligated to provide such
  * modified Materials to you.
  *
  * U.S. GOVERNMENT RESTRICTED RIGHTS: The Materials are provided with
  * "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
  * subject to the restrictions as set forth in FAR 52.227-14 and
  * DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
  * Government constitutes acknowledgement of AMD's proprietary rights in them.
  *
  * EXPORT ASSURANCE:  You agree and certify that neither the Materials, nor any
  * direct product thereof will be exported directly or indirectly, into any
  * country prohibited by the United States Export Administration Act and the
  * regulations thereunder, without the required authorization from the U.S.
  * government nor will be used for any purpose prohibited by the same.
  * ***************************************************************************
  *
 */
#include "PiDxe.h"
#include "AGESA.h"
#include "Library/AmdCalloutLib.h"
#include <Library/DebugLib.h>
#include "Token.h"
#include <Protocol/SmmCommunication.h>
#include "Library/AmdPspMboxLibV1.h"
#include "AmiAgesaWrapper.h"
#include "Guid/AmiPsp.h"

extern EFI_RUNTIME_SERVICES     *gRT;
extern EFI_BOOT_SERVICES        *gBS;


// Size of SMM communicate header, without including the Data.
#define SMM_COMMUNICATE_HEADER_SIZE  (OFFSET_OF (EFI_SMM_COMMUNICATE_HEADER, Data))

// Size of BR PSP S3 nvram
#define PSP_S3_NVRAM_SIZE   0x3000  //Type 0x1A

EFI_SMM_COMMUNICATION_PROTOCOL  *SmmCommunication = NULL;
UINT8                           *CommunicateBuffer = NULL;
UINTN CONST                     MessageLength = PSP_S3_NVRAM_SIZE; // Reserve S3 DataSize 
UINTN                           CommunicateBufferSize = SMM_COMMUNICATE_HEADER_SIZE + PSP_S3_NVRAM_SIZE;// Header size (without data) + Reserve S3 DataSize

/*---------------------------------------------------------------------------------------*/
/**
 * OemHook to save the nonvolatile context
 *
 * @param[in]         DataSize
 * @param[in]         *Data
 *
 * @retval
 *
 */
AGESA_STATUS
AgesaSaveNonVolatileS3Info (
  IN       UINTN                        DataSize,
  IN       VOID                         *Data
  )
{
    EFI_STATUS                  Status;
    UINTN                       S3DataSize = DataSize;
    VOID                        *S3Data = Data;
    VOID                        *S3DataWithHmac;
    UINT8                       Hmac[32];
    EFI_SMM_COMMUNICATE_HEADER  *SmmCommunicateHeader;
    
    //Get the HMAC value of S3 Data
    PspMboxBiosCmdS3Info ((UINT64)Data, DataSize, Hmac);
    DEBUG((DEBUG_INFO, "Raw S3 data size  = %lx\n", DataSize));
    //Append the Hmac to end of S3 Data
    gBS->AllocatePool (
        EfiBootServicesData,
        DataSize + sizeof (Hmac),
        &S3DataWithHmac);

    DEBUG((DEBUG_INFO, "S3DataWithHmac pointer  = %lx\n", S3DataWithHmac));

    gBS->SetMem (S3DataWithHmac, DataSize + sizeof (Hmac), 0);
    gBS->CopyMem ((VOID *) ((UINT8*)S3DataWithHmac), Data, DataSize);
    gBS->CopyMem ((VOID *) ((UINT8*)S3DataWithHmac + DataSize), &Hmac[0], sizeof (Hmac));

    S3Data = S3DataWithHmac;
    S3DataSize = DataSize + sizeof (Hmac);

    DEBUG((DEBUG_INFO, "\n S3 Data with Hmac pointer = %lx\n", S3Data));
    DEBUG((DEBUG_INFO, "S3 Data size(include Hmac) = %lx\n", S3DataSize));

    //
    // Copy Smm Communicate Header Here
    //
    SmmCommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *)CommunicateBuffer;
    gBS->CopyMem(&SmmCommunicateHeader->HeaderGuid, &gAmiPspS3SmmCommunicationGuid, sizeof(EFI_GUID));

    SmmCommunicateHeader->MessageLength = MessageLength;
    //
    // Copy PSP S3 Data Here
    //
    gBS->CopyMem(&SmmCommunicateHeader->Data, S3Data, MessageLength);

    //
    // Send data to SMM.
    //
    Status = gBS->LocateProtocol(&gEfiSmmCommunicationProtocolGuid, NULL, (VOID **) &SmmCommunication);
    DEBUG((DEBUG_INFO, "LocateProtocol SmmCommunication = %x\n", Status));
    if (EFI_ERROR(Status)) {
        SmmCommunication = NULL;
    }

    if (SmmCommunication != NULL)
    {
        Status = SmmCommunication->Communicate(SmmCommunication, CommunicateBuffer, &CommunicateBufferSize);
        if (EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            return Status;
        }
    }
    
    // Free the Memory Allocated for S3Data Buffer.
    Status = gBS->FreePool(S3Data);
    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;  
    }
    
    Status = gRT->SetVariable(  // Save PCI Information in NVRAM
        MEM_S3_SAVE_VARIABLE_NV, &gAmiAgesaS3NonvolatileDataGuid,
        EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
        DataSize, Data);
    if (Status != EFI_SUCCESS)
        return Status;
    
    return  EFI_SUCCESS;
}

/*---------------------------------------------------------------------------------------*/
/**
 * OemHook to save the nonvolatile context
 *
 * @param[in]         DataSize
 * @param[in]         *Data
 *
 * @retval
 *
 */
AGESA_STATUS
AgesaSaveVolatileS3Info (
  IN       UINTN                        DataSize,
  IN       VOID                         *Data
  )
{
    EFI_STATUS                  Status;
    UINT8                       *AgesaBufferPtr = NULL;
    UINTN                       VariableSize = 0;
    UINT16                      *BufferPtr = NULL;

    // Allocate required buffer
    AgesaBufferPtr = (UINT8*)0xFFFFFFFF;
    Status = gBS->AllocatePages(AllocateMaxAddress, EfiACPIMemoryNVS, EFI_SIZE_TO_PAGES(DataSize),
                (EFI_PHYSICAL_ADDRESS*)&AgesaBufferPtr);
    if (EFI_ERROR(Status))
        return Status;

    // Copy all non-Volatile data to memory
    gBS->CopyMem(AgesaBufferPtr, Data, DataSize);

    // Save buffer pointer into NVRAM
    VariableSize = sizeof(UINT64);
    Status = gRT->SetVariable(
        MEM_S3_SAVE_VARIABLE_VOL, &gAmiAgesaS3VolatileDataGuid,
        EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
        VariableSize, &AgesaBufferPtr);
    if (Status != EFI_SUCCESS)
        return EFI_UNSUPPORTED;

    // Save buffer length into NVRAM
    VariableSize = sizeof(UINT64);
    BufferPtr = (UINT16 *)DataSize;

    Status = gRT->SetVariable(
        MEM_S3_SAVE_VARIABLE_VOL_LENGTH, &gAmiAgesaS3VolatileDataGuid,
        EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
        VariableSize, &BufferPtr);
    if (Status != EFI_SUCCESS)
        return EFI_UNSUPPORTED;

    return  EFI_SUCCESS;
}

/**
 * Initial Smm communication buffer before EndOfDxe event for gAmiPspS3SmmCommunicationGuid
 *
 *
 *
 * @retval EFI_SUCCESS    Initial success
 * @retval Others         Error happens during initialize
 */
RETURN_STATUS
EFIAPI
AmdCalloutConstructor (
  VOID
  )
{
    EFI_STATUS  Status = EFI_SUCCESS;

    if (CommunicateBuffer != NULL)
        return  Status;

    Status = gBS->AllocatePool( EfiRuntimeServicesData,
                                CommunicateBufferSize,
                                (VOID**)&CommunicateBuffer );
    DEBUG((DEBUG_INFO, "Allocate S3 Save Buffer() status = %r\n", Status));
    if ( EFI_ERROR( Status ))
    {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }
    return Status;
}

