//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file SdioSmm.c
    Smm driver to handle the SDIO MMIO operations

**/

//----------------------------------------------------------------------

#include <SdioSmm.h>
#include <SdioController.h>
#include <Library/BaseMemoryLib.h>
#include <Library/AmiBufferValidationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/SmmEndOfDxe.h>
//----------------------------------------------------------------------

EFI_SMM_BASE2_PROTOCOL          *gSmmBase2;
EFI_SMM_SYSTEM_TABLE2           *pSmst2;

typedef VOID        (*API_FUNC)(SDIO_STRUC*);
SDIO_GLOBAL_DATA    *gSdioData = NULL;
BOOLEAN             gLegacyBootNotify = FALSE;
EFI_GUID            gAmiSdioCommunicationGuid = SDIO_PARAMETER_BASE_ADDRESS_GUID;
/**
 Type:        Function Dispatch Table

    This is the table of functions used by SDIO Storage API

**/

API_FUNC SdioApiTable[] = {
    SdMmcAPIRead,
    SdMmcAPIWrite,
    SdMmcApiDeviceGeometry,
    SdMmcApiReset,
    SdMmcNotSupported,  // Dummy
    SdMmcNotSupported,  // GetDeviceInfo
    SdMmcNotSupported   // VerifyDevice
};

/**
    Initialize Sdio SMM data area

    @param   DispatchHandle,
    @param   *Context         OPTIONAL,
    @param   *CommBuffer      OPTIONAL,
    @param   *CommBufferSize  OPTIONAL

    @retval  EFI_STATUS

**/

EFI_STATUS
EFIAPI
SdioInitSmmData (
    IN  EFI_HANDLE      DispatchHandle,
    IN  CONST   VOID    *Context        OPTIONAL,
    IN  OUT     VOID    *CommBuffer     OPTIONAL,
    IN  OUT     UINTN   *CommBufferSize OPTIONAL
  )
{

    EFI_STATUS          Status = EFI_SUCCESS;
    SDIO_GLOBAL_DATA    *OrgSdioData;
    UINT8               Index;
    UINT64              *SdioSwSmiSignature = NULL;
    UINT64              *LegacyBootNotifySignature = NULL;

    // If input is invalid, stop processing this SMI
    if (CommBuffer == NULL || CommBufferSize == NULL) {
        return EFI_SUCCESS;
    }
      
    //Validate if CommBuffer address is an non-SMRAM region to avoid SMRAM data 
    // corruption through SMI handlers
    Status = AmiValidateMemoryBuffer ((VOID*)CommBuffer, sizeof(UINT64));
    if (EFI_ERROR(Status)) {
        DEBUG((DEBUG_VERBOSE,"\n SdioInitSmmData()ComBuffer overlaps with SMRAM space" ));
        return EFI_SUCCESS;
    }
    
    SdioSwSmiSignature = (UINT64  *)CommBuffer;
           
    if (*SdioSwSmiSignature == SIGNATURE_64 ('S', 'D', 'E', 'F', 'I', 'N', 'F', 'Y')) {     
        Status = pSmst2->SmiHandlerUnRegister (DispatchHandle);        
        ASSERT_EFI_ERROR(Status);

        return Status;
    }
    LegacyBootNotifySignature = (UINT64  *)CommBuffer;
    if (*LegacyBootNotifySignature == SIGNATURE_64 ('S', 'D', 'L', 'E', 'G', 'N', 'F', 'Y')) {    
        Status = pSmst2->SmiHandlerUnRegister (DispatchHandle);  
        gLegacyBootNotify = TRUE;
        return Status;
    }
    
    OrgSdioData = (SDIO_GLOBAL_DATA *)CommBuffer;
    
    Status = AmiValidateMemoryBuffer ((VOID*)OrgSdioData, sizeof(SDIO_GLOBAL_DATA));
    if (EFI_ERROR(Status)) {
        DEBUG((DEBUG_VERBOSE,"\n SdioInitSmmData() SDIO_GLOBAL_DATA ComBuffer overlaps with SMRAM space" ));
        return EFI_SUCCESS;
    }
    
    if (gSdioData == NULL) {

        // Copy IDENTIFY_CONTROLLER_DATA
        Status = pSmst2->SmmAllocatePool ( 
                                    EfiRuntimeServicesData, 
                                    sizeof (SDIO_GLOBAL_DATA),
                                    (VOID**)&(gSdioData));
        if (EFI_ERROR(Status)) {		
            ASSERT_EFI_ERROR(Status); 
			return Status;       
        }
		
        ZeroMem ((void*)gSdioData, sizeof(SDIO_GLOBAL_DATA));

    }
    
    for (Index = 0;Index < MAX_SDIO_DEVICES;Index++) {
        if (OrgSdioData->SdioDev[Index].DevEntryUsed != FALSE) {
            if (gSdioData->SdioDev[Index].DevEntryUsed == FALSE) {
                Status = AmiValidateMemoryBuffer ((VOID*)&OrgSdioData->SdioDev[Index], sizeof(SDIO_DEVICE_INFO));
                if (EFI_ERROR(Status)) {
                    DEBUG((DEBUG_VERBOSE,"\n SdioInitSmmData() SDIO_DEVICE_INFO buffer overlaps with SMRAM space" ));
                    return EFI_SUCCESS;
                }
                CopyMem ((SDIO_DEVICE_INFO *)&(gSdioData->SdioDev[Index]), (SDIO_DEVICE_INFO *)&(OrgSdioData->SdioDev[Index]), \
                           sizeof (SDIO_DEVICE_INFO));
            }
        } else {
            break;
        }
    }
            
    return EFI_SUCCESS;
    
}

/** 
    This is the entry point of the SDIO Smm driver.

    @param ImageHandle
    @param SystemTable

    @retval EFI_STATUS

**/

EFI_STATUS
EFIAPI
SdioSmmDriverEntryPoint (
    IN  EFI_HANDLE       ImageHandle,
    IN  EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS       Status;
    EFI_HANDLE       DispatchHandle = NULL;
    VOID             *Registration;

    Status = gBS->LocateProtocol (&gEfiSmmBase2ProtocolGuid, NULL, (VOID **) &gSmmBase2);
    if (EFI_ERROR(Status))
        return EFI_SUCCESS;

    Status = gSmmBase2->GetSmstLocation (gSmmBase2, &pSmst2);
    if (EFI_ERROR(Status))
        return EFI_SUCCESS;

    //
    // Register SDIO handler to transfer data from DXE driver to SMM
    //
    Status = pSmst2->SmiHandlerRegister (
                                 SdioInitSmmData,
                                 &gAmiSdioCommunicationGuid,
                                 &DispatchHandle);    
    ASSERT_EFI_ERROR (Status);
	
	// Register a callback function for gEfiSmmEndOfDxeProtocolGuid
    // to register the SdioSwSmiHandler, only when CSM is enabled.
    Status = pSmst2->SmmRegisterProtocolNotify (
                                          &gEfiSmmEndOfDxeProtocolGuid, 
                                          InstallSwSmiHandlerForLegacy, 
                                          &Registration);
    ASSERT_EFI_ERROR (Status);

    return EFI_SUCCESS;
}

/**
    Invoked on reads from SW SMI port with value SDIO_SWSMI. This
    function dispatches the SDIO Request Packets (URP) to the
    appropriate functions.

    @param  DispatchHandle  - EFI Handle
    @param  DispatchContext - Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT
    @param  CommBuffer
    @param  CommBufferSize

    @retval  Zero on successful completion
    @retval  Non zero on error

**/

EFI_STATUS
EFIAPI
SdioSwSmiHandler (
    EFI_HANDLE      DispatchHandle,
    IN  CONST VOID  *DispatchContext OPTIONAL,
    IN  OUT VOID    *CommBuffer      OPTIONAL,
    IN  OUT UINTN   *CommBufferSize  OPTIONAL
)
{
    SDIO_STRUC  *SdioURP = NULL;
    UINT8        BFuncIndex;
    UINT8        BNumberOfFunctions;
    UINT16       EbdaSeg;
    EFI_STATUS   Status;
    
    //
    // Get the fpURP pointer from EBDA
    //
    EbdaSeg = *((UINT16*)0x40E);
    SdioURP = *(SDIO_STRUC**)(UINTN)(((UINT32)EbdaSeg << 4) + SDIO_DATA_EBDA_OFFSET);
    SdioURP = (SDIO_STRUC*)((UINTN)SdioURP & 0xFFFFFFFF);

    // Validate if URP address is an non-SMRAM region to avoid SMRAM data 
    // corruption through SMI handlers
    Status = AmiValidateMemoryBuffer((VOID*)SdioURP, sizeof(SDIO_STRUC));

    if (EFI_ERROR(Status)) {
        // return without modifying the SdioeUrp buffer as it's not belongs to the normal Memory Region.
        return EFI_SUCCESS;
    }
    
	
    if (gLegacyBootNotify == FALSE){
		SdioURP->bRetValue = (EFI_SECURITY_VIOLATION & 0xFF);
		return EFI_SECURITY_VIOLATION;
    }
    
    BFuncIndex = SdioURP->bFuncNumber;
    BNumberOfFunctions = sizeof SdioApiTable / sizeof (API_FUNC *);

    //
    // Make sure function number is valid; if function number is not zero
    // check for valid extended SDIO API function
    //
    if (BFuncIndex >= BNumberOfFunctions ) {
        SdioURP->bRetValue = SDIO_PARAMETER_FAILED;
        return EFI_SUCCESS;
    }

    //
    // Call the appropriate function
    //

    SdioApiTable[BFuncIndex](SdioURP);

    return EFI_SUCCESS;
}

/**@internal
 * 
    Install the SW SMI handler for the Legacy Sdio Function only when the 
    BIOS supports the Legacy BIOS Mode 
    
    @param CONST EFI_GUID  *Protocol  - Points to the protocol's unique identifier.
	@param VOID			   *Interface - Points to the interface instance.
    @param EFI_HANDLE 	   Handle	  - The handle on which the interface was installed.

    @retval   VOID
    
   @endinternal
**/

EFI_STATUS
EFIAPI
InstallSwSmiHandlerForLegacy (
      IN CONST EFI_GUID  *Protocol,
      IN VOID            *Interface,
      IN EFI_HANDLE      Handle
)
{ 
    EFI_STATUS                      Status;
    EFI_HANDLE                      SwHandle = NULL;
    EFI_SMM_SW_DISPATCH2_PROTOCOL   *SwDispatch = NULL;
    EFI_SMM_SW_REGISTER_CONTEXT     SwContext;
    EFI_LEGACY_BIOS_PROTOCOL        *LegacyBios;
    
    // Check if the CSM/Legacy Function supported in BIOS
    Status = gBS->LocateProtocol (&gEfiLegacyBiosProtocolGuid, NULL, (VOID**)&LegacyBios);
    if (EFI_ERROR(Status)) { 
       // Legacy Not supported. Doesn't need to register the SW SMI
       return Status;
    }
    Status = pSmst2->SmmLocateProtocol (
                                  &gEfiSmmSwDispatch2ProtocolGuid,
                                  NULL,
                                  (VOID**)&SwDispatch);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    // Register the SW SMI for the Legacy Function
    SwContext.SwSmiInputValue = SDIO_SWSMI;
    Status = SwDispatch->Register (
                               SwDispatch,
                               SdioSwSmiHandler,
                               &SwContext,
                               &SwHandle);    
    ASSERT_EFI_ERROR(Status);
    
    return Status;    
}

/**@internal
 * 
    Get the Index no for the DeviceAddress

    @param  DeviceAddress

    @retval DeviceIndex

   @endinternal
**/
UINT8
GetDevEntry (
    IN  UINT8   DeviceAddress
)
{
    UINT8   Index;
    
    if(gSdioData == NULL) {
        return 0xFF;
    }

    for (Index = 0; Index < MAX_SDIO_DEVICES; Index++) {
        if ((gSdioData->SdioDev[Index].DeviceAddress == DeviceAddress) && \
            (gSdioData->SdioDev[Index].DevEntryUsed == TRUE)) {
            return Index;
        }
    }

    return 0xFF;

}

/**@internal
 * 
    Read the Data from the Device

    @param Input details from caller

    @retval Output information stored in SDIO_STRUC

   @endinternal
**/
VOID
SdMmcAPIRead (
    SDIO_STRUC *SdioURP
)
{
    SDIO_DEVICE_INFO  *SdioDevInfo;
    EFI_STATUS        Status;
    UINT8             Port;
    UINT32            Lba;
    UINT32            NumBlks;
    UINT32            TempNumBlks = MAX_NUMBLOCK_16BIT;
    UINT32            BufferAddress;
    UINT8             DevEntry;

    DevEntry = GetDevEntry(SdioURP->ApiData.Read.DeviceAddress);
    if (DevEntry == 0xFF) {
        SdioURP->bRetValue = SDIO_PARAMETER_FAILED;
        return;
    }
    SdioDevInfo = &gSdioData->SdioDev[DevEntry];

    Port = SdioURP->ApiData.Read.Port;
    Lba = SdioURP->ApiData.Read.LBA;
    NumBlks = SdioURP->ApiData.Read.NumBlks;
    BufferAddress = SdioURP->ApiData.Read.BufferAddress;
    // Check "SDIO buffer crosses 4GB above memory", if yes, It is assumed that it is invalid
    if (((UINT64)BufferAddress + NumBlks * SdioDevInfo->wBlockSize) & UPPER_64_BITS ) {
        SdioURP->bRetValue = SDIO_PARAMETER_FAILED;
        return;
    }

    // Validate if Buffer address is an non-SMRAM region to avoid SMRAM data 
    // corruption through SMI handlers
    Status = AmiValidateMemoryBuffer (
                               (VOID*)(UINTN)BufferAddress, 
                                NumBlks * SdioDevInfo->wBlockSize);

    if (EFI_ERROR(Status)) {
        SdioURP->bRetValue = SDIO_PARAMETER_FAILED;
        return;
    }
    //
    // If "Forced FDD" option is selected that means the device has
    // to be emulated as a floppy drive even though it has a HDD emulated
    // image.  This is accomplished by hiding the first cylinder totally.
    // The partition table is in the first cylinder.  LBA value for all
    // the requests to the device will be offset with the number of sectors
    // in the cylinder.
    //

    //
    // Check for forced floppy emulated device and change LBA accordingly
    //
    if (SdioDevInfo->bEmuType == SDIO_EMU_FORCED_FDD) {
        //
        // Skip first track in case of floppy emulation
        //
        Lba += SdioDevInfo->bHiddenSectors;
    }

    //
    // If number of block are greater than 65535(16-bit) then divide the read into multiple read.
    //
    while (NumBlks > TempNumBlks) {
        Status = SdMmcRead (SdioDevInfo, Port, (EFI_LBA)Lba, TempNumBlks, (VOID*)(UINTN)BufferAddress);
        if (EFI_ERROR(Status)) {
            SdioURP->bRetValue = SDIO_GENERAL_FAILURE;
            return;
        }
        NumBlks = NumBlks - TempNumBlks;
        Lba += TempNumBlks;
        BufferAddress += ((SdioDevInfo->wBlockSize) * TempNumBlks);
    }
    Status = SdMmcRead (SdioDevInfo, Port, (EFI_LBA)Lba, NumBlks,(VOID*)(UINTN)BufferAddress);

    if (EFI_ERROR(Status)) {
        SdioURP->bRetValue = SDIO_GENERAL_FAILURE;
    } else {
        //
        // Check for forced floppy emulated device
        //
        if ((SdioDevInfo->bEmuType == SDIO_EMU_FORCED_FDD) &&
            (SdioURP->ApiData.Read.LBA == 0)) {
            //
            // This is a floppy emulated ZIP drive, with read to
            // first sector. Update the boot record so that floppy
            // emulation is okay.
            //
            // Force #of hidden sectors to 0
            //
            BufferAddress = SdioURP->ApiData.Read.BufferAddress;
            *(UINT32*)((UINTN)(BufferAddress + 0xB + 0x11)) = 0;

            //
            // FreeDOS workaround
            //
            if ((*(UINT32*)((UINTN)BufferAddress + 3) == 0x65657246) && // 'eerF'
                (*(UINT32*)((UINTN)BufferAddress + 7) == 0x20534F44) && // ' SOD'
                (*(UINT32*)((UINTN)BufferAddress + 0x3A) == 0x20202032)) {
                    *(UINT16*)((UINTN)BufferAddress + 0x42) =
                        *(UINT16*)((UINTN)BufferAddress + 0x42) - (UINT16)SdioDevInfo->bHiddenSectors;
                    *(UINT16*)((UINTN)BufferAddress + 0x46) =
                        *(UINT16*)((UINTN)BufferAddress + 0x46) - (UINT16)SdioDevInfo->bHiddenSectors;
                    *(UINT16*)((UINTN)BufferAddress + 0x4A) =
                        *(UINT16*)((UINTN)BufferAddress + 0x4A) - (UINT16)SdioDevInfo->bHiddenSectors;
            }
            //
            // Force physical drive# to 0
            // For FAT32, physical drive number is present in offset 40h
            //
            if ((*(UINT32*)((UINTN)BufferAddress + 0x52)) == 0x33544146) { // '3TAF' for FAT3
                *(UINT8*)((UINTN)BufferAddress + 0x40) = 0;
            } else {
                *(UINT8*)((UINTN)BufferAddress + 0x24) = 0;
            }
        }

        SdioURP->bRetValue = SDIO_SUCCESS;
    }

    return;
}

/**@internal
 * 
    Write the Data to the Device

    @param Input details from caller

    @retval Output information stored in SDIO_STRUC

   @endinternal
**/
VOID
SdMmcAPIWrite (
    SDIO_STRUC *SdioURP
)
{
    SDIO_DEVICE_INFO  *SdioDevInfo;
    EFI_STATUS        Status;
    UINT8             Port;
    UINT32            Lba;
    UINT32            NumBlks;
    UINT32            TempNumBlks = MAX_NUMBLOCK_16BIT;
    UINT32            BufferAddress;
    UINT8             DevEntry;
    #if SDIO_WriteProtect
    UINT32            Temp32;
    #endif

    DevEntry=GetDevEntry (SdioURP->ApiData.Read.DeviceAddress);
    if (DevEntry == 0xFF) {
        SdioURP->bRetValue = SDIO_PARAMETER_FAILED;
        return;
    }

    SdioDevInfo = &gSdioData->SdioDev[DevEntry];

    Port = SdioURP->ApiData.Read.Port;
    Lba = SdioURP->ApiData.Read.LBA;
    NumBlks = SdioURP->ApiData.Read.NumBlks;
    BufferAddress = SdioURP->ApiData.Read.BufferAddress;

    // Check "SDIO buffer crosses 4GB above memory", if yes, It is assumed that it is invalid
    if (((UINT64)BufferAddress + NumBlks * SdioDevInfo->wBlockSize) & UPPER_64_BITS) {
        SdioURP->bRetValue = SDIO_PARAMETER_FAILED;
        return;
    }

    // Validate if Buffer address is an non-SMRAM region to avoid SMRAM data 
    // corruption through SMI handlers
    Status = AmiValidateMemoryBuffer (
                                (VOID*)(UINTN)BufferAddress, 
                                 NumBlks * SdioDevInfo->wBlockSize);

    if (EFI_ERROR(Status)) {
        SdioURP->bRetValue = SDIO_PARAMETER_FAILED;
        return;
    }

    #if SDIO_WriteProtect        
    Temp32 = SDIO_REG32(SdioDevInfo->SdioBaseAddress, PSTATE);
    if (!(Temp32 & PSTATE_WP)) {
        SdioURP->bRetValue = SDIO_WRITE_PROTECT_ERR;
        return;
    }
    #endif

    //
    // If "Forced FDD" option is selected that means the device has
    // to be emulated as a floppy drive even though it has a HDD emulated
    // image.  This is accomplished by hiding the first cylinder totally.
    // The partition table is in the first cylinder.  LBA value for all
    // the requests to the device will be offset with the number of sectors
    // in the cylinder.
    //

    //
    // Check for forced floppy emulated device and change LBA accordingly
    //
    if (SdioDevInfo->bEmuType == SDIO_EMU_FORCED_FDD) {
        //
        // Skip first track in case of floppy emulation
        //
        Lba += SdioDevInfo->bHiddenSectors;
    }

    //
    // If number of block are greater than 65535(16-bit) then divide the write into multiple write.
    //
    while (NumBlks > TempNumBlks) {
        Status = SdMmcWrite (SdioDevInfo, Port, (EFI_LBA)Lba, (UINT32)TempNumBlks, (VOID*)(UINTN)BufferAddress);
        if (EFI_ERROR(Status)) {
            SdioURP->bRetValue = SDIO_GENERAL_FAILURE;
            return;
        }
        NumBlks = NumBlks - TempNumBlks;
        Lba += TempNumBlks;
        BufferAddress += ((SdioDevInfo->wBlockSize) * TempNumBlks);
    }
    Status = SdMmcWrite (SdioDevInfo, Port, (EFI_LBA)Lba, (UINT32)NumBlks, (VOID*)(UINTN)BufferAddress);
    
    if (EFI_ERROR(Status)) {
        SdioURP->bRetValue = SDIO_GENERAL_FAILURE;
    } else {
        SdioURP->bRetValue = SDIO_SUCCESS;
    }

    return;
}

/**@internal
    Get the Device Geometry

        
    @param ImageHandle 
    @param SystemTable 

    @retval EFI_STATUS

   @endinternal
**/
VOID SdMmcApiDeviceGeometry (
    SDIO_STRUC *SdioURP
)
{

    SDIO_DEVICE_INFO    *SdioDevInfo;
    UINT8               DevEntry;

    DevEntry = GetDevEntry(SdioURP->ApiData.Read.DeviceAddress);
    if (DevEntry == 0xFF) {
        SdioURP->bRetValue = SDIO_PARAMETER_FAILED;
        return;
    }
    SdioDevInfo = &gSdioData->SdioDev[DevEntry];

    SdioURP->ApiData.DeviceGeo.NumHeads = SdioDevInfo->NumHeads;
    SdioURP->ApiData.DeviceGeo.NumCylinders = SdioDevInfo->NumCylinders;
    SdioURP->ApiData.DeviceGeo.NumSectors = SdioDevInfo->NumSectors;
    SdioURP->ApiData.DeviceGeo.LBANumHeads = SdioDevInfo->LBANumHeads;
    SdioURP->ApiData.DeviceGeo.LBANumCyls = SdioDevInfo->LBANumCyls;
    SdioURP->ApiData.DeviceGeo.LBANumSectors = SdioDevInfo->LBANumSectors;
    SdioURP->ApiData.DeviceGeo.BlockSize = SdioDevInfo->wBlockSize;
    SdioURP->ApiData.DeviceGeo.MaxLBA = SdioDevInfo->dMaxLBA;

    SdioURP->bRetValue = SDIO_SUCCESS;

    return;

}

/**@internal
 * 
    Reset the Device

        
    @param ImageHandle 
    @param SystemTable 

    @retval EFI_STATUS
    
    @endinternal
**/
VOID
SdMmcApiReset (
    SDIO_STRUC *SdioURP
)
{

    SDIO_DEVICE_INFO    *SdioDevInfo;
    EFI_STATUS          Status;
    UINT8               DevEntry;

    DevEntry = GetDevEntry (SdioURP->ApiData.Read.DeviceAddress);
    if (DevEntry == 0xFF) {
        SdioURP->bRetValue = SDIO_PARAMETER_FAILED;
        return;
    }

    SdioDevInfo = &gSdioData->SdioDev[DevEntry];

    Status = SdMmcSoftwareReset( SdioDevInfo, RESETCMD + RESETDAT );

    if (EFI_ERROR(Status)) {
        SdioURP->bRetValue = SDIO_GENERAL_FAILURE;
    } else {
        SdioURP->bRetValue = SDIO_SUCCESS;
    }

    return;

}


/**@internal
 * 
    SdMMc SMI functions not supported and return EFI_SUCCESS

    @retval VOID
    
   @endinternal
**/

VOID SdMmcNotSupported (
    SDIO_STRUC *SdioURP
)
{
    SdioURP->bRetValue = SDIO_SUCCESS;
    return;
}
