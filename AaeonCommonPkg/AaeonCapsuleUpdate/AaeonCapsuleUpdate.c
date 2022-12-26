#include <AmiLib.h>
#include <Capsule.h>
#include <Fid.h>
#include <AmiDxeLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>

#define FID_FFS_FILE_NAME_GUID \
    { 0x3fd1d3a2, 0x99f7, 0x420b, { 0xbc, 0x69, 0x8b, 0xb1, 0xd4, 0x92, 0xa3, 0x32 }}

#define FID_FFS_FILE_SECTION_GUID \
    { 0x2EBE0275, 0x6458, 0x4AF9, { 0x91, 0xED, 0xD3, 0xF4, 0xED, 0xB1, 0x00, 0xAA }}

static W8_IMAGE_CAPSULE *Image;

/**
  This function returns current FID descriptor
  
  @param Fid     Pointer where to store FID descriptor

  @retval EFI_SUCCESS Layout returned successfully
  @retval other       error occured during execution

**/
EFI_STATUS AaeonGetFidFromFv(
    OUT VOID *Fid
)
{
    static EFI_GUID FidFileName = FID_FFS_FILE_NAME_GUID;
    EFI_STATUS Status;
    EFI_HANDLE *FvHandle;
    UINTN FvCount;
    UINTN i;
    UINTN BufferSize;
    VOID *Buffer;

    Status = gBS->LocateHandleBuffer(ByProtocol, &gEfiFirmwareVolume2ProtocolGuid, NULL, &FvCount, &FvHandle);
    if (EFI_ERROR(Status)) 
        return Status;

    for(i = 0; i < FvCount; i++) {
        EFI_FIRMWARE_VOLUME_PROTOCOL *Fv;
        UINT32 AuthStatus;
        
        Status = gBS->HandleProtocol(FvHandle[i], &gEfiFirmwareVolume2ProtocolGuid, (VOID **)&Fv);
        if (EFI_ERROR(Status)) 
            continue;
            
        Buffer = 0;
        BufferSize = 0;
        Status = Fv->ReadSection(Fv, &FidFileName, EFI_SECTION_FREEFORM_SUBTYPE_GUID, 0, &Buffer, &BufferSize, &AuthStatus);
        if (!EFI_ERROR(Status)) {
            TRACE((-1, "extracted section with guid %g\n", (EFI_GUID *)Buffer));
            Buffer = (UINT8 *)Buffer + sizeof(EFI_GUID);
            CopyMem(Fid, Buffer, sizeof(FW_VERSION));
            Buffer = (UINT8 *)Buffer - sizeof(EFI_GUID);
            gBS->FreePool(Buffer);
            return EFI_SUCCESS;
        }
    }
    gBS->FreePool(FvHandle);
    return EFI_NOT_FOUND;
}

/**
  This function returns FID descriptor stored in provided buffer
  
  @param Fid     Pointer where to store FID descriptor
  @param Buffer  Pointer to the buffer to be searched

  @retval EFI_SUCCESS       Layout returned successfully
  @retval EFI_NOT_FOUND     There is no FID descriptor in buffer

**/
EFI_STATUS AaeonGetFidFromBuffer(
    IN VOID *Buffer,
    OUT VOID *Fid
)
{
    static EFI_GUID FidSectionGuid = FID_FFS_FILE_SECTION_GUID;
    UINT32 Signature;
    UINT32 *SearchPointer;

    SearchPointer = (UINT32 *)((UINT8 *)Buffer - sizeof(EFI_GUID) + FLASH_SIZE);
    Signature = FidSectionGuid.Data1;

    do {
        if(*SearchPointer == Signature) {
            if(CompareGuid(&FidSectionGuid, (EFI_GUID *)SearchPointer)) {
                SearchPointer = (UINT32 *)((UINT8 *)SearchPointer + sizeof(EFI_GUID));
                CopyMem(Fid, SearchPointer, sizeof(FW_VERSION));
                return EFI_SUCCESS;
            }
        }
    } while(SearchPointer-- >= (UINT32 *)Buffer);

    return EFI_NOT_FOUND;
}

UINT8 LocalHexValue(CHAR8 Char)
{
    if(Char >= 0x30 && Char <= 0x39)        //symbols 0...9
        return Char - 0x30;

    if(Char >= 0x41 && Char <= 0x46)        //symbols A...F
        return Char - 0x37;

    return Char - 0x57;                     //symbols a...f
}

UINT32 AaeonGetVersionFromFid(
    VOID *FvImage OPTIONAL
)
{
    FW_VERSION Fid;
    EFI_STATUS Status;
    UINT32 Data32 = 0;

    if(Image == NULL)
        Status = AaeonGetFidFromFv(&Fid);
    else
        Status = AaeonGetFidFromBuffer(FvImage, &Fid);

    if(EFI_ERROR(Status))
        return 0;

    Data32 |= LocalHexValue(Fid.ProjectMajorVersion[0]) << 12;
    Data32 |= LocalHexValue(Fid.ProjectMajorVersion[1]) << 8;
    Data32 |= LocalHexValue(Fid.ProjectMinorVersion[0]) << 4;
    Data32 |= LocalHexValue(Fid.ProjectMinorVersion[1]);
    return Data32 ;

}