//*************************************************************************
// $Header: $
//
// $Revision: $
//
// $Date: $
//*************************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  TcgDxe.c
//
// Description:
//  Abstracted functions for Tcg protocol are defined here
//
//<AMI_FHDR_END>
//*************************************************************************
#include <AmiTcg/sha.h>
#include <AmiTcg/Tpm20.h>
#include <AmiTcg/TrEEProtocol.h>
#include <Protocol/TcgService.h>
#include <Token.h>
#include<Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#if defined (RomLayout_SUPPORT) && (RomLayout_SUPPORT!=0)
#include <Library/AmiRomLayoutLib.h>
#endif
#include <Protocol/FirmwareVolumeBlock.h>

#include <AmiProtocol.h>
#include <OemTCGAuxList.h>
#include "../TcgCoreFvOverride/TcgCoreFvOverride.h"

#include <Protocol/FirmwareVolume2.h>

extern EFI_GUID gEfiTrEEProtocolGuid;
extern EFI_GUID gEfiTcgProtocolGuid;

EFI_GUID TcgSkipFfsGuidList[] = { TCG_SKIP_FFS_GUID_LIST };

EFI_STATUS HashAllFilesInFv(
    IN SHA1_CTX                         *Sha1Ctx,
    IN EFI_FIRMWARE_VOLUME2_PROTOCOL    *FwVol,
    IN EFI_FV_FILETYPE                  FileType
)
{
    EFI_STATUS                      Status;
    VOID                            *KeyBuffer = NULL;
    EFI_GUID                        FileName;
    EFI_FV_FILE_ATTRIBUTES          FileAttr;
    UINTN                           FileSize;
    VOID                            *FileBuffer;
    UINT32                          AuthStat;
    UINTN                           unIdx = 0;
    BOOLEAN                         FoundSkipFfs;

    Status = gBS->AllocatePool( EfiBootServicesData, FwVol->KeySize, &KeyBuffer );

    if ( KeyBuffer != NULL )
    {
        gBS->SetMem( KeyBuffer, FwVol->KeySize, 0 );
    }

    if ( KeyBuffer == NULL )
    {
        DEBUG(( -1, "[%d]: Err.\n", __LINE__));
        DEBUG(( -1, "  FwVol->KeySize[0x%x]\n", FwVol->KeySize));
        return EFI_OUT_OF_RESOURCES;
    }

    do
    {
        Status = FwVol->GetNextFile(
            FwVol,
            KeyBuffer,
            &FileType,
            &FileName,
            &FileAttr,
            &FileSize
            );
        if( EFI_ERROR(Status) )
        {
            DEBUG(( -1, "[%d]: GetNextFile - %r\n", __LINE__, Status ));
        }
        else // if ( !EFI_ERROR( Status ))
        {
            FileBuffer = NULL;
            Status     = FwVol->ReadFile(
                FwVol,
                &FileName,
                &FileBuffer,
                &FileSize,
                &FileType,
                &FileAttr,
                &AuthStat
                );
            DEBUG(( -1, "[%d]: ReadFile - %r\n", __LINE__, Status ));
            ASSERT_EFI_ERROR(Status);
            if( !EFI_ERROR(Status))
            {
                for( unIdx=0, FoundSkipFfs = FALSE; unIdx < sizeof(TcgSkipFfsGuidList)/sizeof(TcgSkipFfsGuidList[0]) ; ++unIdx)
                {
                    if( TRUE == CompareGuid( &TcgSkipFfsGuidList[unIdx], &FileName ) )
                    {
                        DEBUG(( -1, "[%d]: -- Found Skip Guid --\n", __LINE__));
                        FoundSkipFfs = TRUE;
                        break;
                    }
                }
                DEBUG(( -1, "[%d]: FileName[%g]\n", __LINE__, FileName ));
                if( FALSE == FoundSkipFfs)
                {
                    DEBUG(( -1, "[%d]: SHA1Update, Addr[%x], Length[%x]\n", __LINE__, FileBuffer, FileSize));
                    SHA1Update(Sha1Ctx, FileBuffer, (u32)FileSize );
                }
                gBS->FreePool( FileBuffer );
            }
        }
    } while ( !EFI_ERROR( Status ));

    gBS->FreePool( KeyBuffer );
    return EFI_SUCCESS;
}

EFI_STATUS  GetFvVolSha1Digest( unsigned char Sha1Digest[20] )
{
    EFI_STATUS                      Status = EFI_SUCCESS;

    UINTN                           NumHandles;
    EFI_HANDLE                      *HandleBuffer;
    EFI_FIRMWARE_VOLUME2_PROTOCOL   *Fv;
    UINTN                           unIdx1;
    SHA1_CTX                        Sha1Ctx;

    Status = gBS->LocateHandleBuffer(ByProtocol,&gEfiFirmwareVolume2ProtocolGuid,NULL,&NumHandles,&HandleBuffer);
    if (EFI_ERROR(Status)) {
        DEBUG((-1, "[%d]: Can not locate gEfiFVProtocolGuid - %r\n", __LINE__, Status));
        return Status;
    }

    SHA1Init(&Sha1Ctx );

    for (unIdx1 = 0; unIdx1 < NumHandles; ++unIdx1) {
        Status = gBS->HandleProtocol( HandleBuffer[unIdx1], &gEfiFirmwareVolume2ProtocolGuid, &Fv);
        if (EFI_ERROR(Status)) {
            continue;
        }

        Status = HashAllFilesInFv( &Sha1Ctx, Fv, EFI_FV_FILETYPE_DRIVER );
    }

    SHA1Final(Sha1Digest, &Sha1Ctx);

    return Status;
}

#pragma pack (1)

typedef struct
{
    EFI_PHYSICAL_ADDRESS PostCodeAddress;
#if x64_TCG
    UINT64               PostCodeLength;
#else
    UINTN                PostCodeLength;
#endif
} EFI_PLATFORM_FIRMWARE_BOLB;

#pragma pack()

VOID FvOrdCallbackOnTreeInstall(IN EFI_EVENT ev,
                           IN VOID      *ctx)
{
    UINT8                           Sha1Digest[20];
    EFI_STATUS                      Status = EFI_SUCCESS;
    EFI_TREE_PROTOCOL               *mTreeProtocol = NULL;
    UINT8                           u8Buf[0x100];
    TrEE_EVENT                      *TcgEvent;
    EFI_PLATFORM_FIRMWARE_BOLB      EventData;

    DEBUG(( -1, "[%d]: Enter FvOrdCallbackOnTreeInstall(...)\n", __LINE__));
//    SMDbgTimeStart(( "[%d]: Enter FvOrdCallbackOnTreeInstall(...)\n", __LINE__ ));

    Status = gBS->LocateProtocol (&gEfiTrEEProtocolGuid, NULL, (VOID **) &mTreeProtocol);
    ASSERT_EFI_ERROR(Status);

    Status = GetFvVolSha1Digest( Sha1Digest );
    ASSERT_EFI_ERROR(Status);
    if ( EFI_ERROR(Status) )
    {
        return;
    }

    TcgEvent = (TrEE_EVENT*)&u8Buf[0];

    EventData.PostCodeAddress   = FV_MAIN_BASE;
    EventData.PostCodeLength    = FV_MAIN_BLOCKS * FLASH_BLOCK_SIZE;

    TcgEvent->Header.PCRIndex   = 0;
    TcgEvent->Header.EventType  = 0x00000001;
    TcgEvent->Header.HeaderSize = sizeof(TcgEvent->Header);
    TcgEvent->Header.HeaderVersion  = 1;
    gBS->CopyMem( &TcgEvent->Event[0], &EventData, sizeof(EventData) );
    TcgEvent->Size  = sizeof(TrEE_EVENT_HEADER) + sizeof(UINT32) + sizeof(EventData);

    Status = mTreeProtocol->HashLogExtendEvent(
                                        mTreeProtocol,
                                        0,
                                        (EFI_PHYSICAL_ADDRESS)&Sha1Digest[0],
                                        sizeof(Sha1Digest),
                                        TcgEvent
                                        );
    ASSERT_EFI_ERROR(Status);

    gBS->CloseEvent(ev);
//    SMDbgTimeEnd;
}

VOID FvOrdCallbackOnTcgprotocolInstall(IN EFI_EVENT event,
                                  IN VOID      *ctx)
{
    EFI_STATUS                      Status = EFI_SUCCESS;
    UINT8                           Sha1Digest[20];
    EFI_TCG_PROTOCOL                *tcgProtocol = NULL;
    TCG_PCR_EVENT                   *TcgEvent = NULL;
    UINT8                           u8Buf[0x100];
    EFI_PHYSICAL_ADDRESS            Last;
    UINT32                          evNum;
    EFI_PLATFORM_FIRMWARE_BOLB      EventData;

//    SMDbgTimeStart(( "[%d]: Enter FvOrdCallbackOnTcgprotocolInstall(...)\n", __LINE__ ));

    Status = gBS->LocateProtocol(
                                 &gEfiTcgProtocolGuid,
                                 NULL,
                                 &tcgProtocol );
    ASSERT_EFI_ERROR(Status);

    Status = GetFvVolSha1Digest( Sha1Digest );
    ASSERT_EFI_ERROR(Status);
    if ( EFI_ERROR(Status) )
    {
        return;
    }

    EventData.PostCodeAddress   = FV_MAIN_BASE;
    EventData.PostCodeLength    = FV_MAIN_BLOCKS * FLASH_BLOCK_SIZE;

    TcgEvent = (TCG_PCR_EVENT*)&u8Buf[0];

    TcgEvent->EventSize     = sizeof(EventData);
    TcgEvent->PCRIndex      = 0;
    TcgEvent->EventType     = 0x00000001;

    gBS->CopyMem( &TcgEvent->Event[0], &EventData, sizeof(EventData) );

    Status = tcgProtocol->HashLogExtendEvent(
                                    tcgProtocol,
                                    (EFI_PHYSICAL_ADDRESS)&Sha1Digest[0],
                                    sizeof(Sha1Digest),
                                    TCG_ALG_SHA,
                                    TcgEvent,
                                    &evNum,
                                    &Last );
    ASSERT_EFI_ERROR(Status);
    gBS->CloseEvent(event);
//    SMDbgTimeEnd;
}

EFI_EVENT                   Event;
VOID                        *reg;
EFI_EVENT                   Event2;
VOID                        *reg2;

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TcgCoreFvOverride
//
// Description: Hashes FVMain Volume
//
//
// Input:
//
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
void TcgCoreFvOverride(IN EFI_HANDLE        ImageHandle,
                     IN EFI_SYSTEM_TABLE  *SystemTable)
{
    EFI_STATUS Status = EFI_SUCCESS;

    DEBUG ((-1, "[%d]: Enter TcgCoreFvOverride(...).\n", __LINE__));

    // Register the gEfiTcgProtocolGuid Callback.
    Status = gBS->CreateEvent(  EFI_EVENT_NOTIFY_SIGNAL,
                                TPL_CALLBACK, FvOrdCallbackOnTcgprotocolInstall, &reg2, &Event2);
    if(EFI_ERROR(Status))
    {
        DEBUG((-1, "[%d]: Err. \n", __LINE__));
        return;
    }

    Status = gBS->RegisterProtocolNotify( &gEfiTcgProtocolGuid, Event2, &reg2);
    DEBUG ((-1, "TcgCoreFvOverride::RegisterProtocolNotify Status - %r\n", Status));

    // Register the gEfiTrEEProtocolGuid Callback.
    Status = gBS->CreateEvent(  EFI_EVENT_NOTIFY_SIGNAL,
                                TPL_CALLBACK, FvOrdCallbackOnTreeInstall, &reg, &Event );
    if(EFI_ERROR(Status))
    {
        DEBUG((-1, "[%d]: Err. \n", __LINE__));
        return;
    }

    Status = gBS->RegisterProtocolNotify( &gEfiTrEEProtocolGuid, Event, &reg );
    DEBUG ((-1, "TcgCoreFvOverride::RegisterProtocolNotify Status - %r\n", Status));

    return;
}
