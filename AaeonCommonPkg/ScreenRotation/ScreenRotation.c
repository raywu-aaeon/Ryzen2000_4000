//***********************************************************************
//*                                                                     *
//*                  Copyright (c) 1985-2021, AMI.                      *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file ScreenRotation.c

    The module can rotate screen, we can use setup item to control direction.
*/

//============================================================================
// Includes
//============================================================================
#include <Token.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/GraphicsOutput.h>
#include <AmiDxeLib.h>
#include <ScreenRotation/ScreenRotation.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiLib.h>

//============================================================================
// Typedef
//============================================================================
typedef struct {
    DLINK                                    Link;
    EFI_HANDLE                               Handle;
    EFI_GRAPHICS_OUTPUT_PROTOCOL             *Gop;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE  OrgQueryMode;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE    OrgSetMode;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT         OrgBlt;
    BOOLEAN                                  VirtualResolution;
} GOP_INFO;

//============================================================================
// Define
//============================================================================
#define FOR_EACH_GOP_INFO(ListPtr, LinkPtr, GopInfo) \
	for(  LinkPtr=(ListPtr)->pHead\
        ;    LinkPtr!=NULL\
          && (GopInfo=OUTTER(LinkPtr,Link,GOP_INFO),LinkPtr=LinkPtr->pNext,TRUE)\
        ;\
    )

#define EXCHANGE_RESOLUTION(ModeInfo) \
            do {\
                UINT32 _TempResolutioin = (ModeInfo)->HorizontalResolution; \
                (ModeInfo)->HorizontalResolution = (ModeInfo)->VerticalResolution; \
                (ModeInfo)->VerticalResolution = _TempResolutioin; \
            } while(0)

//============================================================================
// External Global Variable Declaration
//============================================================================
//============================================================================
// Global Variable Declaration
//============================================================================
static VOID *Registration = NULL;
static SCREEN_ROTATION_POLICY Policy;
static DLIST gGopInfoList;

//============================================================================
// Function Definitions
//============================================================================
/**
    Capture Screen Buffer to show from Original Buffer,
    Output screen buffer might be a part of original buffer.

    @param  OrgBuffer
    @param  SourceX
    @param  SourceY
    @param  Width
    @param  Height
    @param  Delta

    @retval  EFI_GRAPHICS_OUTPUT_BLT_PIXEL*
**/
EFI_GRAPHICS_OUTPUT_BLT_PIXEL*
CaptureBuffer(
        IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL   *OrgBuffer,
        IN UINTN                           SourceX,
        IN UINTN                           SourceY,
        IN UINTN                           Width,
        IN UINTN                           Height,
        IN UINTN                           Delta        
)
{
    EFI_STATUS  Status;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Buff = NULL;
    UINTN       BufferWidth = Delta/sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
    
    if(OrgBuffer == NULL) 
        // EFI_INVALID_PARAMETER;
        return NULL;
    
    // If no delta means output whole buffer
    if(!Delta)
        return NULL;
    
    // Capture the part we want to show
    Status = pBS->AllocatePool( EfiBootServicesData, Width * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * Height, &Buff );
    if (!EFI_ERROR(Status)) 
    {
        UINTN   x, y;
        for(x = 0 ; x < Height ; x++)
        {
            for(y = 0 ; y < Width ; y++)
            {
                Buff[x*Width + y] = OrgBuffer[(x+SourceY)*BufferWidth + SourceX + y];
            }
        }
    }
    return Buff;
}

/**
    Rotation Screen Buffer

    @param  OrgBuffer
    @param  Width
    @param  Height

    @retval  EFI_GRAPHICS_OUTPUT_BLT_PIXEL*
**/
EFI_GRAPHICS_OUTPUT_BLT_PIXEL*
RotationBuffer(
    IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL   *OrgBuffer,
    IN UINTN                           Width,
    IN UINTN                           Height,
    IN UINT8                           Direction)
{
    EFI_STATUS  Status = EFI_SUCCESS;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Buff = NULL;
    
    if(OrgBuffer == NULL) 
    {
        // EFI_INVALID_PARAMETER;
        return NULL;
    }
    // Make a new buffer
    Status = pBS->AllocatePool( EfiBootServicesData, Width * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * Height, &Buff );
    if (!EFI_ERROR(Status)) 
    {
        UINT32 x, y ;

        if (Direction == REVERSION) 
        {
            for( x = 0; x < Width * Height; x++ ) 
            {
                Buff[x] = OrgBuffer[(Width*Height) - x - 1];
            }
        } else if (Direction == RIGHT_ROTATION) 
        {
            for (x = 0 ; x < Height ; x++) 
            {
                for (y = 0 ; y < Width ; y++) 
                {
                    Buff[y*Height + (Height-1-x)] = OrgBuffer[x*Width+y];
                }
            }
        } else if (Direction == LEFT_ROTATION) 
        {
            for (x = 0 ; x < Width*Height; x++) 
            {
                y = (UINT32)(((x*Width)+Width-1) % ((Width*Height)+1));
                Buff[x] = OrgBuffer[y] ;
            }
        }
    }
    return Buff;
}

/** 
    Get the pointer of GopInfo related to the Gop.

    @param  Gop  Used to find the GopInfo.

    @retval  GOP_INFO*  found
    @retval  NULL       Not found
**/
GOP_INFO* GetGopInfo(EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop)
{
    DLINK *Link;
    GOP_INFO *GopInfo;
    FOR_EACH_GOP_INFO(&gGopInfoList, Link, GopInfo)
    {
        if (GopInfo->Gop == Gop)
            return GopInfo;
    }
    return NULL;
}

/**
    Blt with normal resolution.

    It will also raise the TPL to avoid some drivers like the mouse to get
    the wrong HorizontalResolution and VerticalResolution.

    @param  This
    @param  BltBuffer
    @param  BltOperation
    @param  SourceX
    @param  SourceY
    @param  DestinationX
    @param  DestinationY
    @param  Width
    @param  Height

    @retval  EFI_UNSUPPORTED  Fail to get the GopInfo
    @retval  EFI_STATUS       From the original Blt call
**/
EFI_STATUS
EFIAPI
OrgBltWithNormalResolution(
    IN  EFI_GRAPHICS_OUTPUT_PROTOCOL            *This,
    IN  EFI_GRAPHICS_OUTPUT_BLT_PIXEL           *BltBuffer,   OPTIONAL
    IN  EFI_GRAPHICS_OUTPUT_BLT_OPERATION       BltOperation,
    IN  UINTN                                   SourceX,
    IN  UINTN                                   SourceY,
    IN  UINTN                                   DestinationX,
    IN  UINTN                                   DestinationY,
    IN  UINTN                                   Width,
    IN  UINTN                                   Height,
    IN  UINTN                                   Delta         OPTIONAL)
{ 
    EFI_STATUS    Status;
    EFI_TPL OldTpl;
    GOP_INFO *GopInfo;

    GopInfo = GetGopInfo(This);
    if (!GopInfo) return EFI_UNSUPPORTED;   

    OldTpl = pBS->RaiseTPL (TPL_NOTIFY);
    // Swap back to normal graphics resolution as needed for BLT to display.
    if ((Policy.Direction == RIGHT_ROTATION || Policy.Direction == LEFT_ROTATION)) 
    {
        if(GopInfo->VirtualResolution) 
        {
            EXCHANGE_RESOLUTION(This->Mode->Info);
        }
    }
    Status = GopInfo->OrgBlt(This,
                       BltBuffer,
                       BltOperation,
                       SourceX,
                       SourceY,
                       DestinationX,
                       DestinationY,
                       Width,
                       Height,
                       Delta);
    
    // Swap to virtual rotated graphics resolution again as needed.
    if ((Policy.Direction == RIGHT_ROTATION || Policy.Direction == LEFT_ROTATION)) 
    {
        if (GopInfo->VirtualResolution) 
            EXCHANGE_RESOLUTION(This->Mode->Info);
    }
    pBS->RestoreTPL (OldTpl);
    return Status;
}

/**
    Screen Rotation Blt function hook.

    @param  This
    @param  BltBuffer
    @param  BltOperation
    @param  SourceX
    @param  SourceY
    @param  DestinationX
    @param  DestinationY
    @param  Width
    @param  Height

    @retval  EFI_STATUS
**/
EFI_STATUS
EFIAPI
ScreenRotationBlt(
    IN  EFI_GRAPHICS_OUTPUT_PROTOCOL            *This,
    IN  EFI_GRAPHICS_OUTPUT_BLT_PIXEL           *BltBuffer,   OPTIONAL
    IN  EFI_GRAPHICS_OUTPUT_BLT_OPERATION       BltOperation,
    IN  UINTN                                   SourceX,
    IN  UINTN                                   SourceY,
    IN  UINTN                                   DestinationX,
    IN  UINTN                                   DestinationY,
    IN  UINTN                                   Width,
    IN  UINTN                                   Height,
    IN  UINTN                                   Delta         OPTIONAL)
{
    EFI_STATUS Status;
    UINTN n_w = 0, n_h = 0;
    UINTN n_d_x = 0, n_d_y = 0;
    UINTN n_s_x = 0, n_s_y = 0;
    UINTN HRes, VRes;
    GOP_INFO *GopInfo;
	BOOLEAN     NewBufferUsed = FALSE;

    GopInfo = GetGopInfo(This);
    if (!GopInfo) return EFI_UNSUPPORTED;   

    // Swap back to normal graphics resolution as needed for BLT to display.
    if ((Policy.Direction == RIGHT_ROTATION || Policy.Direction == LEFT_ROTATION)) 
    {
        HRes = This->Mode->Info->VerticalResolution;
        VRes = This->Mode->Info->HorizontalResolution;
    }
	else {
        HRes = This->Mode->Info->HorizontalResolution;
        VRes = This->Mode->Info->VerticalResolution;
	}
	
    if (Policy.Direction != NORMAL) 
    {
        EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Buff = NULL;
        UINT8 SecondRotation = 0;

        switch (BltOperation) 
        {
        case EfiBltVideoFill:
        case EfiBltBufferToVideo:
            if(BltBuffer == NULL) 
            {
                return EFI_INVALID_PARAMETER;
            }
            // Handle EfiBltBufferToVideo and EfiBltVideoFill operation.
            if (BltOperation != EfiBltVideoFill)
            {
                EFI_GRAPHICS_OUTPUT_BLT_PIXEL* NewBuff;
                NewBuff = CaptureBuffer(BltBuffer, SourceX, SourceY, Width, Height, Delta);
                if(NewBuff)
                {
                    Buff = RotationBuffer(NewBuff, Width, Height, Policy.Direction);
                    NewBufferUsed = TRUE;
                    pBS->FreePool(NewBuff);
                }else
                {
                    Buff = RotationBuffer(BltBuffer, Width, Height, Policy.Direction);
                }
            }
            if (Policy.Direction == REVERSION) 
            {
                n_w = Width;
                n_h = Height;
                n_d_x = HRes - DestinationX - Width;
                n_d_y = VRes - DestinationY - Height;
            } else if (Policy.Direction == RIGHT_ROTATION) 
            {
                n_w = Height;
                n_h = Width;
                n_d_x = HRes - DestinationY - Height;
                n_d_y = DestinationX;
                if (n_d_x > HRes) n_d_x = HRes;
                if (n_d_y > VRes) n_d_y = VRes;
                if ((n_w+n_d_x) > HRes) n_w = HRes - n_d_x;
                if ((n_h+n_d_y) > VRes) n_h = VRes - n_d_y;
                if (Delta) Delta = n_w * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
            } else if (Policy.Direction == LEFT_ROTATION) 
            {
                n_w = Height;
                n_h = Width;
                n_d_x = DestinationY;
                n_d_y = (VRes - DestinationX - Width);
                if (n_d_x > HRes) n_d_x = HRes;
                if (n_d_y > VRes) n_d_y = VRes;
                if ((n_w+n_d_x) > HRes) n_w = HRes - n_d_x;
                if ((n_h+n_d_y) > VRes) n_h = VRes - n_d_y;
                if (Delta) Delta = n_w * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
            }
            if(NewBufferUsed)
            {
                SourceX = 0;
                SourceY = 0;
				Delta = 0;
            }
            Status = OrgBltWithNormalResolution(This,
                               (Buff ? Buff : BltBuffer),
                               BltOperation,
                               SourceX,
                               SourceY,
                               n_d_x,
                               n_d_y,
                               n_w,
                               n_h,
                               Delta);
            if (Buff) pBS->FreePool(Buff);
            break;
        case EfiBltVideoToBltBuffer:
            // Handle EfiBltVideoToBltBuffer operation.
            if (Policy.Direction == REVERSION) 
            {
                if ((SourceX+Width) > HRes || (SourceY+Height) > VRes) 
                {
                    DEBUG((EFI_D_ERROR, "[ScreenRotation] Error: VideoToBlt (Sx Sy): (%d %d), (Dx Dy): (%d %d), (W H): (%d %d), (HRes VRes): (%d %d), Delta: %d.\n",
                           SourceX, SourceY, DestinationX, DestinationY, Width, Height, HRes, VRes, Delta));
                    return EFI_UNSUPPORTED;
                }
            } else 
            {
                if ((SourceX+Width) > VRes || (SourceY+Height) > HRes) 
                {
                    DEBUG((EFI_D_ERROR, "[ScreenRotation] Error: VideoToBlt (Sx Sy): (%d %d), (Dx Dy): (%d %d), (W H): (%d %d), (HRes VRes): (%d %d), Delta: %d.\n",
                           SourceX, SourceY, DestinationX, DestinationY, Width, Height, HRes, VRes, Delta));
                    return EFI_UNSUPPORTED;
                }
            }
            if (Policy.Direction == REVERSION) 
            {
                n_w = Width;
                n_h = Height;
                n_s_x = HRes - SourceX - Width;
                n_s_y = VRes - SourceY - Height;
                SecondRotation = REVERSION;
            } else if (Policy.Direction == RIGHT_ROTATION) 
            {
                n_w = Height;
                n_h = Width;
                n_s_x = HRes - SourceY - Height;
                n_s_y = SourceX;
                SecondRotation = LEFT_ROTATION;
                if (Delta) Delta = n_w * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
            } else if (Policy.Direction == LEFT_ROTATION) 
            {
                n_w = Height;
                n_h = Width;
                n_s_x = SourceY;
                n_s_y = VRes - SourceX - Width;
                SecondRotation = RIGHT_ROTATION;
                if (Delta) Delta = n_w * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
            }
            Status = OrgBltWithNormalResolution(This,
                               BltBuffer,
                               EfiBltVideoToBltBuffer,
                               n_s_x,
                               n_s_y,
                               DestinationX,
                               DestinationY,
                               n_w,
                               n_h,
                               Delta);
            if (EFI_ERROR(Status)) return Status;
            Buff = RotationBuffer(BltBuffer, n_w, n_h, SecondRotation);
            if (Buff) 
            {
                MemCpy(BltBuffer, Buff, n_w * n_h * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
                pBS->FreePool(Buff);
            }
            break;
        case EfiBltVideoToVideo:
            // Handle EfiBltVideoToVideo operation.
            if (Policy.Direction == REVERSION) 
            {
                n_w = Width;
                n_h = Height;
                n_s_x = HRes - SourceX - Width;
                n_s_y = VRes - SourceY - Height;
                n_d_x = HRes - DestinationX - Width;
                n_d_y = VRes - DestinationY - Height;
            } else if (Policy.Direction == RIGHT_ROTATION) 
            {
                n_w = Height;
                n_h = Width;
                n_s_x = HRes - SourceY - Height;
                n_s_y = SourceX;
                n_d_x = HRes - DestinationY - Height;
                n_d_y = DestinationX;
                if (Delta) Delta = n_w * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
            } else if (Policy.Direction == LEFT_ROTATION) 
            {
                n_w = Height;
                n_h = Width;
                n_s_x = SourceY;
                n_s_y = VRes - SourceX - Width;
                n_d_x = DestinationY;
                n_d_y = (VRes - DestinationX - Width);
                if (Delta) Delta = n_w * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
            }
            // When RIGHT_ROTATION and REVERSION, EfiBltVideoToBltBuffer BltOperation is too slow, so use BltBuffer to let it fast.
            if (Policy.Direction == RIGHT_ROTATION || Policy.Direction == REVERSION) 
            {
                Status = pBS->AllocatePool( EfiBootServicesData, n_w * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * n_h, &Buff);
                if (EFI_ERROR(Status)) return Status;
                Status = OrgBltWithNormalResolution(This,
                                   Buff,
                                   EfiBltVideoToBltBuffer,
                                   n_s_x,
                                   n_s_y,
                                   0,
                                   0,
                                   n_w,
                                   n_h,
                                   Delta);
                if (!EFI_ERROR(Status)) 
                {
                    Status = OrgBltWithNormalResolution(This,
                                       Buff,
                                       EfiBltBufferToVideo,
                                       0,
                                       0,
                                       n_d_x,
                                       n_d_y,
                                       n_w,
                                       n_h,
                                       Delta);
                }
                if (Buff != NULL) 
                {
                    pBS->FreePool(Buff);
                }
            } else 
            {
                Status = OrgBltWithNormalResolution(This,
                                   BltBuffer,
                                   BltOperation,
                                   n_s_x,
                                   n_s_y,
                                   n_d_x,
                                   n_d_y,
                                   n_w,
                                   n_h,
                                   Delta);
            }
            break;
        default:
            Status = EFI_INVALID_PARAMETER;
        } // switch (BltOperation)
    } else  // Policy.Direction != NORMAL
    {
        Status = OrgBltWithNormalResolution(This,
                           BltBuffer,
                           BltOperation,
                           SourceX,
                           SourceY,
                           DestinationX,
                           DestinationY,
                           Width,
                           Height,
                           Delta);
    }
    return Status;
}

/**
    Screen Rotation QueryMode function hook.

    @param  This
    @param  ModeNumber
    @param  SizeOfInfo
    @param  Info

    @retval  EFI_STATUS
**/
EFI_STATUS
EFIAPI
ScreenRotationQueryMode (
    IN  EFI_GRAPHICS_OUTPUT_PROTOCOL          *This,
    IN  UINT32                                ModeNumber,
    OUT UINTN                                 *SizeOfInfo,
    OUT EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  **Info)
{
    EFI_STATUS Status;
    GOP_INFO *GopInfo;
    EFI_TPL OldTpl;

    GopInfo = GetGopInfo(This);
    if (!GopInfo) return EFI_UNSUPPORTED;

    OldTpl = pBS->RaiseTPL (TPL_NOTIFY);
    //
    //  1) Check the VirtualResolution : assume a query before setmode may happen
    //  2) Rollback the resolution : assume the GOP may return the resolution by Gop->Mode->Info if the same mode
    //
    if (ModeNumber == This->Mode->Mode
            && GopInfo->VirtualResolution)
    {
        EXCHANGE_RESOLUTION(This->Mode->Info);
    }

    Status = GopInfo->OrgQueryMode(This, ModeNumber, SizeOfInfo, Info);
    if (EFI_ERROR(Status)) 
    {
        pBS->RestoreTPL (OldTpl);
        DEBUG((EFI_D_ERROR, "[ScreenRotation] Error: OrgQueryMode %r.\n", Status));
        return Status;
    }

    DEBUG((EFI_D_VERBOSE, "[ScreenRotation] QueryMode of origin info: ModeNumber(%X), HR(%X), VR(%X)\n", 
                ModeNumber, (*Info)->HorizontalResolution, (*Info)->VerticalResolution));

    // Swap to virtual rotated graphics resolution as needed.
    if (Policy.Direction == RIGHT_ROTATION || Policy.Direction == LEFT_ROTATION) 
    {
        if (ModeNumber == This->Mode->Mode
                && GopInfo->VirtualResolution)
        {
            This->Mode->Info->HorizontalResolution = (*Info)->VerticalResolution;
            This->Mode->Info->VerticalResolution = (*Info)->HorizontalResolution;
        }
        EXCHANGE_RESOLUTION(*Info);

        DEBUG((EFI_D_VERBOSE, "[ScreenRotation] QueryMode of return resolution: HR(%X), VR(%X)\n", 
                    (*Info)->HorizontalResolution, (*Info)->VerticalResolution));

    } // Policy.Direction == RIGHT_ROTATION || Policy.Direction == LEFT_ROTATION

    pBS->RestoreTPL (OldTpl);

    return Status;
}

/**
    Screen Rotation SetMode function hook.

    @param  This
    @param  ModeNumber

    @retval  EFI_STATUS
**/
EFI_STATUS
EFIAPI
ScreenRotationSetMode (
    IN  EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
    IN  UINT32                       ModeNumber)
{
    EFI_STATUS Status;
    GOP_INFO *GopInfo;
    UINTN SizeInfo;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *ModeInfo;
    EFI_TPL OldTpl;
    
    DEBUG((EFI_D_VERBOSE, "[ScreenRotation] SetMode: original mode(%X), set mode(%X)\n", 
                This->Mode->Mode, ModeNumber));

    if (ModeNumber == This->Mode->Mode) return EFI_SUCCESS;

    GopInfo = GetGopInfo(This);
    if (!GopInfo) return EFI_UNSUPPORTED;

    Status = GopInfo->OrgQueryMode(This, ModeNumber, &SizeInfo, &ModeInfo);
    if (EFI_ERROR(Status)) return Status;

    OldTpl = pBS->RaiseTPL (TPL_NOTIFY);

    //
    // Rollback the resolution before setting the mode
    //
    if (GopInfo->VirtualResolution)
        EXCHANGE_RESOLUTION(This->Mode->Info);

    Status = GopInfo->OrgSetMode(This, ModeNumber);
    if (EFI_ERROR(Status)) 
    {
        DEBUG((EFI_D_ERROR, "[ScreenRotation] Error: OrgSetMode %r.\n", Status));
        pBS->RestoreTPL (OldTpl);
        return Status;
    }

    if (Policy.Direction == RIGHT_ROTATION || Policy.Direction == LEFT_ROTATION) 
    {
        This->Mode->Info->HorizontalResolution = ModeInfo->VerticalResolution;
        This->Mode->Info->VerticalResolution = ModeInfo->HorizontalResolution;
    } // Policy.Direction == RIGHT_ROTATION || Policy.Direction == LEFT_ROTATION
    pBS->RestoreTPL (OldTpl);

    return Status;
}

/**
    Gop notification call back

    @param  Event
    @param  Context

    @retval  EFI_STATUS
**/
VOID
GopNotification (
    IN  EFI_EVENT   Event,
    IN  VOID        *Context)
{
    EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop;
    EFI_STATUS      Status;
    EFI_HANDLE      GopHandle;
    GOP_INFO        *GopInfo;
    EFI_HANDLE      *Handles;
    UINTN           HandleCount;
    EFI_TPL         OldTpl;

    if (Policy.Direction == NORMAL) return;

    // Locate the handle based on the registration
    Status = pBS->LocateHandleBuffer(
                     ByRegisterNotify,
                     NULL,
                     Registration,
                     &HandleCount,
                     &Handles);
    if (EFI_ERROR(Status)) return;

    GopHandle = Handles[0];
    pBS->FreePool(Handles);

#if GraphicsSplitter_SUPPORT
    {
        VOID *Dp;
        Status = pBS->HandleProtocol(
                        GopHandle,
                        &gEfiDevicePathProtocolGuid,
                        (VOID**)&Dp);
        if (!EFI_ERROR(Status)) return;
    }
#endif

    Status = pBS->HandleProtocol( GopHandle, &gEfiGraphicsOutputProtocolGuid, (VOID**)&Gop);
    if (EFI_ERROR(Status)) return;

    GopInfo = GetGopInfo(Gop);
    if (!GopInfo)
    {
        GopInfo = AllocateZeroPool(sizeof(GOP_INFO));
        if (!GopInfo)
        {
            DEBUG((EFI_D_ERROR, "[ScreenRotation]: Out of resources for GopInfo\n"));
            return;
        }
        DListAdd(&gGopInfoList, &GopInfo->Link);
    }

    if (Gop->Blt != ScreenRotationBlt)
    {
        GopInfo->OrgBlt = Gop->Blt;
        GopInfo->OrgQueryMode = Gop->QueryMode;
        GopInfo->OrgSetMode = Gop->SetMode;
    }
    GopInfo->Gop = Gop;
    GopInfo->Handle = GopHandle;
    GopInfo->VirtualResolution = TRUE;

    OldTpl = pBS->RaiseTPL (TPL_NOTIFY);
    Gop->Blt = ScreenRotationBlt;
    if (Policy.Direction != REVERSION) 
    {
        Gop->QueryMode = ScreenRotationQueryMode;
        Gop->SetMode = ScreenRotationSetMode;
        EXCHANGE_RESOLUTION(Gop->Mode->Info);
    }
    pBS->RestoreTPL (OldTpl);
}

/**
    Function to swap back to normal graphics resolution for OS.

    @param  Event
    @param  Context

    @retval VOID

**/
VOID
SwapBackGraphicResolution(
    IN EFI_EVENT    Event,
    IN VOID         *Context
)
{
    DLINK *Link;
    GOP_INFO *GopInfo;
    EFI_GUID ScreenRotationGuid = SCREEN_ROTATION_GUID;

    //
    //  Event to recalculate the BGRT according to the current resolution
    //
    EfiNamedEventSignal(&ScreenRotationGuid);

    if (Policy.Direction == NORMAL) return;
    FOR_EACH_GOP_INFO(&gGopInfoList, Link, GopInfo)
    {
        EFI_STATUS Status;
        EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop;

        Status = pBS->HandleProtocol (
                            GopInfo->Handle,
                            &gEfiGraphicsOutputProtocolGuid,
                            (VOID **)&Gop
                            );
        if (EFI_ERROR(Status)) {
            DListDelete(&gGopInfoList, &GopInfo->Link);
            pBS->FreePool(GopInfo);
            continue;
        }

        if(GopInfo->VirtualResolution) 
        {
            EFI_TPL OldTpl = pBS->RaiseTPL (TPL_NOTIFY);

            if (Policy.Direction != REVERSION)
                EXCHANGE_RESOLUTION(Gop->Mode->Info);

            Gop->Blt = GopInfo->OrgBlt;
            Gop->QueryMode = GopInfo->OrgQueryMode;
            Gop->SetMode = GopInfo->OrgSetMode;
            GopInfo->VirtualResolution = FALSE;

            pBS->RestoreTPL (OldTpl);
        }
        DEBUG((EFI_D_INFO, "[ScreenRotation] SwapBack for OS, mode %d/%d, Gop: (%d %d)\n",
                    Gop->Mode->Mode, Gop->Mode->MaxMode, Gop->Mode->Info->HorizontalResolution, Gop->Mode->Info->VerticalResolution));
    }
}

/**
    Function to swap to virtual graphics resolution for SHELL.

    @param  Event
    @param  Context

    @retval VOID

**/
VOID
SwapGraphicResolution(
    IN EFI_EVENT    Event,
    IN VOID         *Context
)
{
    DLINK *Link;
    GOP_INFO *GopInfo;

    if (Policy.Direction == NORMAL) return;

    FOR_EACH_GOP_INFO(&gGopInfoList, Link, GopInfo)
    {
        EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop;
        EFI_STATUS Status;

        Status = pBS->HandleProtocol (
                            GopInfo->Handle,
                            &gEfiGraphicsOutputProtocolGuid,
                            (VOID **)&Gop
                            );

        if (EFI_ERROR(Status)) {
            DListDelete(&gGopInfoList, &GopInfo->Link);
            pBS->FreePool(GopInfo);
            continue;
        }

        if (!GopInfo->VirtualResolution)
        {
            EFI_TPL OldTpl = pBS->RaiseTPL (TPL_NOTIFY);

            Gop->Blt = ScreenRotationBlt;
            if (Policy.Direction != REVERSION)
            {
                EXCHANGE_RESOLUTION(Gop->Mode->Info);
                Gop->QueryMode = ScreenRotationQueryMode;
                Gop->SetMode = ScreenRotationSetMode;
            }
            GopInfo->VirtualResolution = TRUE;

            pBS->RestoreTPL (OldTpl);
        }
        DEBUG((EFI_D_INFO, "[ScreenRotation] Swap for SHELL, mode %d/%d, Gop: (%d %d)\n",
                    Gop->Mode->Mode, Gop->Mode->MaxMode, Gop->Mode->Info->HorizontalResolution, Gop->Mode->Info->VerticalResolution));
                    
    }
}

#define AMITSE_EVENT_AFTER_BOOT_GUID \
  {0x8c12a959, 0x70bc, 0x4362, 0xb4, 0x37, 0xb8, 0x05, 0x14, 0xa1, 0x91, 0x6e}
/**
    Screen Rotation entry point

    @param  ImageHandle
    @param  SystemTable

    @retval  EFI_STATUS
**/
EFI_STATUS
ScreenRotationEntryPoint(
    IN  EFI_HANDLE ImageHandle,
    IN  EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS  Status = EFI_SUCCESS;
    EFI_EVENT   Event;
    EFI_EVENT   ProtocolCallbackEvent;
    VOID        *ProtocolNotifyRegistration;
    EFI_GUID    EfiShellInterfaceGuid = EFI_SHELL_PROTOCOL_GUID;
    EFI_GUID    EfiShell20InterfaceGuid = EFI_SHELL2_0_FILE_GUID;
    static BOOLEAN Guard = FALSE;
    EFI_GUID    AfterBootGuid = AMITSE_EVENT_AFTER_BOOT_GUID; 

    InitAmiLib(ImageHandle, SystemTable);
    DEBUG((EFI_D_INFO, "[ScreenRotation] Entry Point.\n"));
    if (!Guard) 
    {
        EFI_GUID ScreenRotationGuid = SCREEN_ROTATION_GUID;
        UINTN Size = sizeof(SCREEN_ROTATION_POLICY);

        Status = pRS->GetVariable(L"ScreenRotationPolicy",
                                  &ScreenRotationGuid,
                                  NULL,
                                  &Size,
                                  &Policy);
        if (!EFI_ERROR(Status)) Guard = TRUE;
    }
    if (Policy.Direction != NORMAL) 
    {
        // Create event
        Status = pBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                                  TPL_CALLBACK,
                                  GopNotification,
                                  NULL,
                                  &Event );
        if (EFI_ERROR(Status)) return Status;
        // Register a notification when the GOP is installed
        Status = pBS->RegisterProtocolNotify(&gEfiGraphicsOutputProtocolGuid,
                                             Event,
                                             &Registration);
        if (EFI_ERROR(Status)) 
        {
            DEBUG((EFI_D_ERROR, "[ScreenRotation] RegisterProtocolNotify status = %r.\n", Status));
            return Status;
        }
        // Create event
        Status = pBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                                  TPL_CALLBACK,
                                  SwapGraphicResolution,
                                  NULL,
                                  &ProtocolCallbackEvent );

        if (!EFI_ERROR(Status))
        {
            Status = pBS->RegisterProtocolNotify(&AfterBootGuid,
                                                ProtocolCallbackEvent,
                                                &ProtocolNotifyRegistration);
            if (EFI_ERROR(Status)) 
            {
                DEBUG((EFI_D_ERROR, "[ScreenRotation] RegisterProtocolCallback after boot status = %r.\n", Status));
                return Status;
            }
        }
        
        // Register a callback function before boot.
        Status = RegisterProtocolCallback(&gAmiTseEventBeforeBootGuid,
                                          SwapBackGraphicResolution,
                                          NULL,
                                          &ProtocolCallbackEvent,
                                          &ProtocolNotifyRegistration);
        if (EFI_ERROR(Status)) 
        {
            DEBUG((EFI_D_ERROR, "[ScreenRotation] RegisterProtocolCallback before boot status = %r.\n", Status));
            return Status;
        }
        // Register a callback function when entering SHELL 1.0.
        Status = RegisterProtocolCallback(&EfiShellInterfaceGuid,
                                          SwapGraphicResolution,
                                          NULL,
                                          &ProtocolCallbackEvent,
                                          &ProtocolNotifyRegistration);
        if (EFI_ERROR(Status)) 
        {
            DEBUG((EFI_D_ERROR, "[ScreenRotation] RegisterProtocolCallback for SHELL 1.0 status = %r.\n", Status));
            return Status;
        }

        // Register a callback function when entering SHELL 2.0.
        Status = RegisterProtocolCallback(&EfiShell20InterfaceGuid,
                                          SwapGraphicResolution,
                                          NULL,
                                          &ProtocolCallbackEvent,
                                          &ProtocolNotifyRegistration);
        if (EFI_ERROR(Status)) 
        {
            DEBUG((EFI_D_ERROR, "[ScreenRotation] RegisterProtocolCallback for SHELL 2.0 status = %r.\n", Status));
            return Status;
        }
    } // Policy.Direction != NORMAL
    DListInit(&gGopInfoList);

    return Status;
}
