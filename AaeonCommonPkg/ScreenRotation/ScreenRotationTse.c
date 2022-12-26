//***********************************************************************
//*                                                                     *
//*                  Copyright (c) 1985-2021, AMI.                      *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file ScreenRotationTse.c

    Screen rotation TSE hook functions.
*/

//============================================================================
// Includes
//============================================================================
#include <Token.h>
#include <AmiDxeLib.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/AcpiTable.h> 
#include <Acpi.h> 
#include "ScreenRotation.h"

#include <Library/MemoryAllocationLib.h>
#include <Protocol/AMIPostMgr.h>
#include <LogoLib.h>
#include <Library/UefiLib.h>

VOID AddImageDetailToACPI (UINT8 *, INTN, INTN, BOOLEAN);
VOID InvalidateStatusInBgrtWrapper ();
VOID UninstallBgrtWrapper ();

#ifndef EFI_DEFAULT_BMP_LOGO_GUID
#define EFI_DEFAULT_BMP_LOGO_GUID \
  {0x7BB28B99,0x61BB,0x11d5,0x9A,0x5D,0x00,0x90,0x27,0x3F,0xC1,0x4D}
#endif

#define BGRT_STATUS_90_DEGREE  (BIT1)
#define BGRT_STATUS_180_DEGREE (BIT2)
#define BGRT_STATUS_270_DEGREE (BIT1 | BIT2)

//============================================================================
// Define
//============================================================================
#pragma pack (1)
typedef struct //Structure for forming BGRT Table
{
    UINT16  Version;
    UINT8   Status;
    UINT8   ImageType;
    UINT64  ImageAddress;
    UINT32  ImageOffsetX;
    UINT32  ImageOffsetY;
}BGRT_TABLE;
typedef struct {
  CHAR8         CharB;
  CHAR8         CharM;
  UINT32        Size;
  UINT16        Reserved[2];
  UINT32        ImageOffset;
  UINT32        HeaderSize;
  UINT32        PixelWidth;
  UINT32        PixelHeight;
  UINT16        Planes;          ///< Must be 1
  UINT16        BitPerPixel;     ///< 1, 4, 8, or 24
  UINT32        CompressionType;
  UINT32        ImageSize;       ///< Compressed image size in bytes
  UINT32        XPixelsPerMeter;
  UINT32        YPixelsPerMeter;
  UINT32        NumberOfColors;
  UINT32        ImportantColors;
} BMP_IMAGE_HEADER;
#pragma pack()
//============================================================================
// External Global Variable Declaration
//============================================================================
extern EFI_GRAPHICS_OUTPUT_PROTOCOL *gGOP;
extern UINTN gMaxRows;
extern UINTN gMaxCols;
extern UINTN gTableKey;
extern VOID  *gBgrtSafeBuffer;
extern EFI_STATUS ConvertBmpToUgaBltWrapper (IN VOID *BmpImage,
                                             IN UINTN BmpImageSize,
                                             IN OUT VOID **UgaBlt,
                                             IN OUT UINTN  *UgaBltSize,
                                             OUT UINTN *PixelHeight,
                                             OUT UINTN *PixelWidth);
//============================================================================
// Global Variable Declaration
//============================================================================
static SCREEN_ROTATION_POLICY Policy = {0};
static UINT8 gBgrtLogoPatch = BGRT_LOGO_PATCH;

//============================================================================
// Function Definitions
//============================================================================
/**
    Calculates the checksum for the given structure

    @param VOID => Table structure
        UINT8 => Table Size

    @retval UINT8 => Checksum for the table

**/
UINT8 CalculateChecksumBgrt (VOID *AcpiTable, UINT8 TableSize)
{
    UINT8   *TablePtr = (UINT8 *)AcpiTable;
    UINT8   iIndex = 0;
    UINT8   Checksum = 0;

    for (iIndex= 0; iIndex < TableSize; iIndex ++)
        Checksum += TablePtr [iIndex];        

    return (0 - Checksum);
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
    Calculate the coordinate for BGRT.

    @param Height Height of image
    @param Width  Width of image
    @param  CoordinateX  Get X-Coordinate of image
    @param  CoordinateY  Get Y-Coordinate of image
	@param  Rotate  FALSE for trying to rotate back the resolution and otherwise TRUE
    @retval VOID
**/
VOID GetCoordinate(
    UINTN Height,
    UINTN Width, 
    INTN* CoordinateX,
    INTN* CoordinateY,
    BOOLEAN Rotate
)
{
    UINTN SizeOfX;
    UINTN SizeOfY;
    GetScreenResolution(&SizeOfX,&SizeOfY);

    if (!Rotate)
    {
        if (Policy.Direction == RIGHT_ROTATION || Policy.Direction == LEFT_ROTATION) 
        {
            UINTN tmp = SizeOfX;
            SizeOfX = SizeOfY;
            SizeOfY = tmp;
        }
    }

    //
    //  Center
    //
    if ( ( Width <= (((UINTN)(40 *SizeOfX))/100) ) && ( Height <= (((UINTN)(40 *SizeOfY))/100) ))
    {
        *CoordinateX = ((INTN)(SizeOfX - Width))/2; //Exact center of x-axis
        *CoordinateY = (((INTN)(SizeOfY*382))/1000) - ((INTN)Height/2);//Center of logo is 38.2% from the top of screen
    }
    else 
    {
        *CoordinateX = ((INTN)(SizeOfX - Width))/2;
        *CoordinateY  = ((INTN)(SizeOfY - Height))/2;
    }
}

/**
    Install modified Bgrt.

    @param  BgrtTable   Bgrt to install  

    @retval VOID
**/
VOID InstallBgrt(BGRT_TABLE* BgrtTable)
{
    EFI_ACPI_TABLE_PROTOCOL *AcpiTableProtocol = NULL;
    EFI_STATUS Status;
    ACPI_HDR *AcpiHdr;
    UINT8 AcpiHdrSize = sizeof (ACPI_HDR);
    UINTN TableSize = AcpiHdrSize + sizeof(BGRT_TABLE);
    UINT8 Checksum;

    AcpiHdr = (ACPI_HDR*)((UINT8*)BgrtTable - sizeof(ACPI_HDR));
    Checksum = CalculateChecksumBgrt (AcpiHdr, AcpiHdrSize);
    Checksum += CalculateChecksumBgrt (BgrtTable, sizeof(BGRT_TABLE));
    AcpiHdr->Checksum = Checksum;

    Status = pBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **) &AcpiTableProtocol);

    if (EFI_ERROR(Status)) 
    {
        DEBUG ((EFI_D_ERROR,"[ScreenRotation] Error: LocateProtocol(ACPITableProtocol) failed, Status: %r.\n", Status));
        return;
    }

    Status = AcpiTableProtocol->UninstallAcpiTable (AcpiTableProtocol, gTableKey);
    if (EFI_ERROR(Status)) 
    {
        DEBUG ((EFI_D_ERROR,"[ScreenRotation] Error: Uninstall ACPI BGRT table failed, Status: %r.\n", Status));
        return;
    }

    gTableKey = 0; //If not set to 0 then ACPI table is not created again

    Status = AcpiTableProtocol->InstallAcpiTable (AcpiTableProtocol, gBgrtSafeBuffer, TableSize, &gTableKey);
    if (EFI_ERROR(Status)) 
    {
        DEBUG ((EFI_D_ERROR,"[ScreenRotation] Error: Install ACPI BGRT table failed, Status: %r.\n", Status));
        return;
    }
}

/**
    Disables the BGRT status field if any changes happened in screen other than the image display

    @param  Event    Event signaled
    @param  Context  Data passed in
**/
VOID
ScreenRotationBgrtHook (
  EFI_EVENT   Event,
  VOID        *Context
)
{
    if (gBgrtLogoPatch == 1)
    {
        EFI_STATUS  Status;
        BGRT_TABLE *BgrtTable;
        BMP_IMAGE_HEADER *BmpBuff = NULL;
        EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer = NULL;
        EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Buff = NULL;
        UINT8 AcpiHdrSize = sizeof (ACPI_HDR);
        UINTN BltSize = 0;
        UINTN Width = 0, Height = 0;
        UINTN HRes = gGOP->Mode->Info->HorizontalResolution;
        UINTN VRes = gGOP->Mode->Info->VerticalResolution;
        UINTN TempSize = 0;
        UINTN ImageXOffset = 0, ImageYOffset = 0;
        UINT32 i = 0, j = 0;
        UINT8 *Image = NULL;
        UINTN ImageIndex = 0;
        UINTN AllignWidth = 0;

        DEBUG ((EFI_D_INFO,"[ScreenRotation] In ScreenRotationBgrtHook.\n"));
        if (Policy.Direction == NORMAL) 
            return;

        if (gBgrtSafeBuffer == NULL) 
        {
            DEBUG ((EFI_D_ERROR,"[ScreenRotation] Error: gBgrtSafeBuffer is NULL.\n"));
            return;
        }
        
        if (gGOP == NULL) 
        {
            DEBUG ((EFI_D_ERROR,"[ScreenRotation] Error: gGOP is NULL.\n"));
            return;
        }
        BgrtTable = (BGRT_TABLE *)((UINT8 *)gBgrtSafeBuffer + AcpiHdrSize);
        BmpBuff = (BMP_IMAGE_HEADER*)BgrtTable->ImageAddress;

        // Converts bmp graphics image buffer to a UGA blt buffer.
        Status = ConvertBmpToUgaBltWrapper (
                                BmpBuff,
                                BmpBuff->Size,
                                (void**)&BltBuffer,
                                &BltSize,
                                &Height,
                                &Width);
        if (EFI_ERROR(Status)) 
        {
            DEBUG ((EFI_D_ERROR,"[ScreenRotation] Error: ConvertBmpToUgaBltWrapper failed, Status: %r.\n", Status));
            return;
        }
        // Rotate screen buffer for Windows who will not call the hooked Gop to display BGRT logo.
        Buff = RotationBuffer (BltBuffer, Width, Height, Policy.Direction);
        if (BltBuffer != NULL) 
        {
            pBS->FreePool(BltBuffer);
        }
        // Sets the BGRT logo coordinates according to the rotation policy.
        ImageXOffset = BgrtTable->ImageOffsetX;
        ImageYOffset = BgrtTable->ImageOffsetY;
        if (Policy.Direction == RIGHT_ROTATION || Policy.Direction == LEFT_ROTATION) 
        {
            HRes = gGOP->Mode->Info->VerticalResolution;
            VRes = gGOP->Mode->Info->HorizontalResolution;
        }
        
        if (Policy.Direction == REVERSION) 
        {
            ImageXOffset = HRes - ImageXOffset - Width;
            ImageYOffset = VRes - ImageYOffset - Height;
            BgrtTable->Status |= BGRT_STATUS_180_DEGREE;
        } else if (Policy.Direction == RIGHT_ROTATION) 
        {
            TempSize = ImageXOffset;
            ImageXOffset = HRes - ImageYOffset - Height;
            ImageYOffset = TempSize;
            TempSize = Width;
            Width = Height;
            Height = TempSize;
            BgrtTable->Status |= BGRT_STATUS_270_DEGREE;
        } else if (Policy.Direction == LEFT_ROTATION) 
        {
            TempSize = ImageXOffset;
            ImageXOffset = ImageYOffset;
            ImageYOffset = (VRes - TempSize - Width);
            TempSize = Width;
            Width = Height;
            Height = TempSize;
            BgrtTable->Status |= BGRT_STATUS_90_DEGREE;
        }
        DEBUG ((EFI_D_INFO,"[ScreenRotation] New coordinates (ImageXOffset,ImageYOffset): (%d,%d), (Width,Height): (%d,%d), Policy.Direction: %x, BgrtTable->Status: %x.\n", 
            ImageXOffset, ImageYOffset, Width, Height, Policy.Direction, BgrtTable->Status));
        // Converts the rotated blt buffer to bmp buffer
        AllignWidth = Width;
        if (Width%4 != 0)
            AllignWidth += Width%4; // Width should be 4 bytes alligned
        
        BmpBuff->ImageSize = (UINT32)(3*AllignWidth*Height);
        
        if(BmpBuff->Size < sizeof (BMP_IMAGE_HEADER)+ BmpBuff->ImageSize)
        {
            BMP_IMAGE_HEADER*  NewImageBuff = NULL;
            
            pBS->AllocatePool (EfiRuntimeServicesData, sizeof (BMP_IMAGE_HEADER) + BmpBuff->ImageSize, &NewImageBuff);
            pBS->CopyMem(NewImageBuff,&BmpBuff,BmpBuff->Size);

            pBS->FreePool(BmpBuff);
            BmpBuff = NewImageBuff;
            BgrtTable->ImageAddress = (UINT64)NewImageBuff;
        }
        
        BmpBuff->Size = sizeof (BMP_IMAGE_HEADER)+ BmpBuff->ImageSize;
        BmpBuff->PixelWidth = (UINT32)Width;
        BmpBuff->PixelHeight = (UINT32)Height;
        Image = (UINT8*)BmpBuff;
        
        Image += BmpBuff->ImageOffset;
        for(i=(UINT32)(Width*Height);i;i-=BmpBuff->PixelWidth)
        {
            for(j=BmpBuff->PixelWidth;j;j--)
            {
                *Image++ = Buff[i-j].Blue;
                *Image++ = Buff[i-j].Green;
                *Image++ = Buff[i-j].Red;
            }
            ImageIndex = (UINTN) (Image - BmpBuff->ImageOffset);
            if ((ImageIndex % 4) != 0) // Bmp Image starts each row on a 32-bit boundary!
                Image = Image + (4 - (ImageIndex % 4));
        }

        if (Buff != NULL) 
            pBS->FreePool(Buff);

        BgrtTable->ImageOffsetX = (UINT32)ImageXOffset;
        BgrtTable->ImageOffsetY = (UINT32)ImageYOffset;

        InstallBgrt(BgrtTable);
    }
    else
    {
        UINT8             AcpiHdrSize = sizeof (ACPI_HDR);
        BMP_IMAGE_HEADER *BmpHeader;
        BGRT_TABLE       *BgrtTable;

        INTN CoordinateX;
        INTN CoordinateY;

        if (gBgrtSafeBuffer == NULL) 
        {
            DEBUG ((EFI_D_ERROR,"[ScreenRotation] Error: gBgrtSafeBuffer is NULL.\n"));
            return;
        }

        if (gGOP == NULL) 
        {
            DEBUG ((EFI_D_ERROR,"[ScreenRotation] Error: gGOP is NULL.\n"));
            return;
        }

        BgrtTable = (BGRT_TABLE *)((UINT8 *)gBgrtSafeBuffer + AcpiHdrSize);
        BmpHeader = (BMP_IMAGE_HEADER*)BgrtTable->ImageAddress;

        if (gBgrtLogoPatch == 2)
        {
            GetCoordinate(BmpHeader->PixelHeight, BmpHeader->PixelWidth, &CoordinateX, &CoordinateY, FALSE);
            BgrtTable->Status &= BIT0;
        }
        else
        {
            if (Policy.Direction == REVERSION) 
            {
                GetCoordinate(BmpHeader->PixelHeight, BmpHeader->PixelWidth, &CoordinateX, &CoordinateY, FALSE);
                BgrtTable->Status |= BGRT_STATUS_180_DEGREE;
            } else if (Policy.Direction == RIGHT_ROTATION) 
            {
                BgrtTable->Status |= BGRT_STATUS_270_DEGREE;
                GetCoordinate(BmpHeader->PixelHeight, BmpHeader->PixelWidth, &CoordinateX, &CoordinateY, TRUE);
            } else if (Policy.Direction == LEFT_ROTATION) 
            {
                BgrtTable->Status |= BGRT_STATUS_90_DEGREE;
                GetCoordinate(BmpHeader->PixelHeight, BmpHeader->PixelWidth, &CoordinateX, &CoordinateY, TRUE);
            }
            else
            {
                GetCoordinate(BmpHeader->PixelHeight, BmpHeader->PixelWidth, &CoordinateX, &CoordinateY, FALSE);
            }
        }
        BgrtTable->ImageOffsetX = (UINT32)CoordinateX;
        BgrtTable->ImageOffsetY = (UINT32)CoordinateY;

        InstallBgrt(BgrtTable);
    }
}

/**
    Initial standard full TSE mode for POST screen.

    @param  NONE

    @retval NONE
**/
VOID ScreenRotationInitHook(VOID)
{
    // Post code will use Col/Row to calculate data.
    // If Col:Row is 74:42, the coordinate will be wrong at postmgmt.c
    // Set gMaxRows:gMaxCols to standard size for normal mode workaround
    static BOOLEAN  Guard = FALSE;

    if (!Guard) 
	{
        EFI_STATUS  Status;
        EFI_GUID    ScreenRotationGuid = SCREEN_ROTATION_GUID;
        UINTN       Size = sizeof(SCREEN_ROTATION_POLICY);

        Status = pRS->GetVariable(L"ScreenRotationPolicy",
                                  &ScreenRotationGuid,
                                  NULL,
                                  &Size,
                                  &Policy);
        if (EFI_ERROR(Status)) 
		{
            DEBUG((EFI_D_ERROR, "[ScreenRotation] Error: Get ScreenRotationPolicy %r.\n", Status));
            return;
        }
        Status = EfiNamedEventListen(&ScreenRotationGuid,
                                     TPL_NOTIFY,
                                     ScreenRotationBgrtHook,
                                     NULL,
                                     NULL);

        if (EFI_ERROR(Status))
		{
            DEBUG((EFI_D_ERROR, "[ScreenRotation] Error: Crerate BGRT event %r.\n", Status));
        }
        Guard = TRUE;
    }
}

#if !(defined(ESA_BINARY_SUPPORT) && (ESA_BINARY_SUPPORT == 1))

VOID StyleInit(VOID);
VOID MouseStop(VOID);
VOID MouseRefresh(VOID);
VOID ClearScreen(UINT8 Attrib);
extern UINTN gMaxBufX;
extern UINTN gMaxBufY;
/**
    Initialization for the the Setup screen.
**/
VOID ScreenRotationSetupScreenInit(VOID)
{

    if (Policy.Direction == NORMAL || Policy.Direction == REVERSION) 
    {
        gMaxBufX = gMaxRows = STYLE_FULL_MAX_ROWS;
        gMaxBufY = gMaxCols = STYLE_FULL_MAX_COLS;
    }
    else
    {
        gMaxBufX = gMaxRows = ROTATE_VERTICAL_RESOLURION/19;
        gMaxBufY = gMaxCols = ROTATE_HORIZONTAL_RESOLURION/8;
    }
	StyleInit();
	MouseStop();
	ClearScreen (STYLE_CLEAR_SCREEN_COLOR);
	MouseRefresh();
}
#endif
