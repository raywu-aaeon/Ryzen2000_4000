/*****************************************************************************
 *
 * Copyright 2015 - 2017 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 ******************************************************************************
 */
/*++
Module Name:

  GfxInitPei.c
  Allocate proper resource for GFX.

Abstract:
--*/
#include "Token.h"
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BaseLib.h>
#include <Library/PciLib.h>
#include <Library/PcdLib.h>
#include <Library/HobLib.h>
#include <Library/FabricResourceManagerLib.h>
#include <Ppi/Graphics.h>
#include <Library/PeiServicesLib.h>  
#include <Guid/AmdMemoryInfoHob.h>
#include "AmdGfxInitPei.h"
#include "AmdPeiGopPolicy.h"
#include <Library/PciExpressLib.h>
// AMI porting start
#define  FixBus NBIO_FIXED_ONCHIP_BUS_A 
// AMI porting end

//7CE1ED80-F762-4218-8270-F7133706EB36
#define AMD_LOGO_FFS_GUID \
  { 0x7CE1ED80, 0xF762, 0x4218, 0x82, 0x70, 0xF7, 0x13, 0x37, 0x06, 0xEB, 0x36 }
  
//98E145D7-1BDC-4636-ABCF-7CBCEF7B668D
#define AMD_PEI_VBIOS_FFS_GUID\
  { 0x98E145D7, 0x1BDC, 0x4636, 0xAB, 0xCF, 0x7C, 0xBC, 0xEF, 0x7B, 0x66, 0x8D }  

//A9CA9175-47AB-4F81-8505-5D96FE46153C
#define AMD_PEI_VBIOS_FFS_GUID_RAVEN2\
  { 0xA9CA9175, 0x47AB, 0x4F81, 0x85, 0x05, 0x5D, 0x96, 0xFE, 0x46, 0x15, 0x3C }  

//#define GNB_PCI_CFG_ADDRESS(bus,dev,func,reg)    \
//    (UINT64) ((((UINT8)bus << 24)+((UINT8)dev << 16)+((UINT8)func << 8)+((UINT8)(reg))) & 0xffffffff)

STATIC EFI_PEI_NOTIFY_DESCRIPTOR mGraphicsPpiNotify = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiGraphicsPpiGuid,
  GraphicsPpiNotifyCallback
};

#pragma pack (1)
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
#pragma pack ()


/*++

Routine Description:

  DrawAmdLogo
  Print the AMD logo through PEI GOP interface for test purpose. 

Arguments:
  N/A

Returns:
  N/A

--*/
VOID
DrawAmdLogo (
  IN  CONST    EFI_PEI_SERVICES             **PeiServices
  )
{
  EFI_STATUS              Status;
  EFI_PEI_GRAPHICS_PPI    *GraphicsPpi;
  EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE Mode;
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;  
  UINTN                                Instance;
  EFI_PEI_FV_HANDLE                    VolumeHandle;
  EFI_PEI_FILE_HANDLE                  FileHandle;    
  BMP_IMAGE_HEADER                     *LogoImage;
  UINT8                                *ImageBuffer;
  UINT8                                *ImageHeader;  
  UINT8                                *Framebuffer;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL        *Blt;
  UINT32                               Index;
  UINT32                               Index2;    
  UINTN                                ImageIndex;  
  EFI_GUID                LogoGuids = AMD_LOGO_FFS_GUID;
  
  DEBUG((EFI_D_INFO, "DrawAmdLogo.\n"));
  Status = (*PeiServices)->LocatePpi (
                               PeiServices,
                               &gEfiPeiGraphicsPpiGuid,
                               0,
                               NULL,
                               (VOID**)&GraphicsPpi
                               ); 
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "  gEfiPeiGraphicsPpiGuid locate failed. Create Notify\n"));
    return;  
  }
  
  Status = GraphicsPpi->GraphicsPpiGetMode(&Mode);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "  GraphicsPpiGetMode failed.\n"));
    return;  
  }
  Info = Mode.Info; 
  DEBUG((EFI_D_INFO, "GOP Mode:\n"));
  DEBUG((EFI_D_INFO, "  MaxMode: 0x%x\n", Mode.MaxMode));
  DEBUG((EFI_D_INFO, "  Mode: 0x%x\n", Mode.Mode));
  DEBUG((EFI_D_INFO, "  SizeOfInfo: 0x%x\n", Mode.SizeOfInfo));
  DEBUG((EFI_D_INFO, "  FrameBufferBase: 0x%x\n", Mode.FrameBufferBase));
  DEBUG((EFI_D_INFO, "  FrameBufferSize: 0x%x\n", Mode.FrameBufferSize));
  DEBUG((EFI_D_INFO, "  Info Version: 0x%x\n", Info->Version));
  DEBUG((EFI_D_INFO, "  Info HorizontalResolution: %d\n", Info->HorizontalResolution));
  DEBUG((EFI_D_INFO, "  Info VerticalResolution: %d\n", Info->VerticalResolution));
  DEBUG((EFI_D_INFO, "  Info PixelFormat RedMask: 0x%x\n", Info->PixelInformation.RedMask));
  DEBUG((EFI_D_INFO, "  Info PixelFormat GreenMask: 0x%x\n", Info->PixelInformation.GreenMask));
  DEBUG((EFI_D_INFO, "  Info PixelFormat BlueMask: 0x%x\n", Info->PixelInformation.BlueMask));    
  DEBUG((EFI_D_INFO, "  Info PixelInformation: 0x%x\n", Info->PixelInformation));
  DEBUG((EFI_D_INFO, "  Info PixelsPerScanLine: 0x%x\n", Info->PixelsPerScanLine));   
  Framebuffer = (UINT8 *)Mode.FrameBufferBase;
  Instance = 0;                                                                                       
  while (TRUE) {
    Status = PeiServicesFfsFindNextVolume (Instance++, &VolumeHandle);
    if (EFI_ERROR (Status)) {
      break;
    }
    Status = PeiServicesFfsFindFileByName (&LogoGuids, VolumeHandle, &FileHandle);
    if (!EFI_ERROR (Status)) {
      Status = PeiServicesFfsFindSectionData (EFI_SECTION_RAW, FileHandle, &LogoImage);
      if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_INFO, "Unable to find LOGO file section ffs %r!\n", Status));
        return;
      }
      DEBUG ((EFI_D_INFO, "  Found Logo, signature %c%c", LogoImage->CharB, LogoImage->CharM));
      ImageBuffer = (UINT8*)LogoImage;  
      ImageBuffer += LogoImage->ImageOffset;
      ImageHeader = ImageBuffer;      
      for (Index = 0; Index < LogoImage->PixelHeight; Index++) {
        Blt = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)(Framebuffer + (sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * Info->HorizontalResolution) * (((Info->VerticalResolution - LogoImage->PixelHeight - 1)/2) - Index )  + \
              sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * ((Info->HorizontalResolution - LogoImage->PixelWidth)/2));
        for (Index2 = 0; Index2 < LogoImage->PixelWidth; Index2++, ImageBuffer++, Blt++) {
          if (LogoImage->BitPerPixel == 24) {
            Blt->Blue   = *ImageBuffer++;
            Blt->Green  = *ImageBuffer++;
            Blt->Red    = *ImageBuffer;
            Blt->Reserved = 0;          
          }
        }   
        ImageIndex = (UINTN) (ImageBuffer - ImageHeader);
        if ((ImageIndex % 4) != 0) {
          ImageBuffer = ImageBuffer + (4 - (ImageIndex % 4));
        }                   
      }            
      break;
    } else {
      continue;
    }
  }                                                                                       
}  

/*
 * Check Picasso or RV2
 *
 * @retval    TRUE    This is Picasso
 *            FALSE   This is RV2
 *
 */

BOOLEAN
CheckRvOpnB4 (
 
  )
{ 
  //UINT32        OpnIndex32;
  UINT32        TempData32;
  UINT32        RegisterData;
  //EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL     *PciRootBridgeIo;
  //UINT64        Address;
  //EFI_STATUS    Status;
  
  //Status = pBS->LocateProtocol(
  //                        &gEfiPciRootBridgeIoProtocolGuid,
  //                        NULL,
  //                        &PciRootBridgeIo);
  //ASSERT_EFI_ERROR(Status);

  TempData32 = PciExpressRead32 (PCI_EXPRESS_LIB_ADDRESS (0,0,0,0xB8));
  //Address = GNB_PCI_CFG_ADDRESS(0x0,0x0,0x0,0xB8);
  //PciRootBridgeIo->Pci.Read(
  //                PciRootBridgeIo,
  //                EfiPciIoWidthUint32,
  //                Address,
  //                1,
  //                &TempData32);

  PciExpressWrite32 (PCI_EXPRESS_LIB_ADDRESS (0, 0, 0, 0xB8), 0x0005D5C0);
  //OpnIndex32 = 0x0005D5C0;
  //PciRootBridgeIo->Pci.Write(
  //               PciRootBridgeIo,
  //                EfiPciIoWidthUint32,
  //                Address,
  //                1,
  //                &OpnIndex32);
  
  RegisterData = PciExpressRead32 (PCI_EXPRESS_LIB_ADDRESS (0,0,0,0xBC));
  //Address = GNB_PCI_CFG_ADDRESS(0x0,0x0,0x0,0xBC);
  //PciRootBridgeIo->Pci.Read(
  //                PciRootBridgeIo,
  //                EfiPciIoWidthUint32,
  //                Address,
  //                1,
  //                &RegisterData);

  PciExpressWrite32 (PCI_EXPRESS_LIB_ADDRESS (0, 0, 0, 0xB8), TempData32);
  //Address = GNB_PCI_CFG_ADDRESS(0x0,0x0,0x0,0xB8);
  //PciRootBridgeIo->Pci.Write(
  //                PciRootBridgeIo,
  //                EfiPciIoWidthUint32,
  //                Address,
  //                1,
  //                &TempData32);

  TempData32 =  (RegisterData >> 30) & 0x3;

  if (TempData32 == 1) {
    return FALSE;
  } else if (TempData32 == 3) {
    return FALSE;
  }

  return TRUE;  
}

/*++

Routine Description:

  PreaprePeiGopPolicyData 

Arguments:
  N/A

Returns:

  Not NULL: PeiGopPolicyPtr
  NULL: failure

--*/
VOID *
PreaprePeiGopPolicyData (VOID)
{
  EFI_STATUS              Status;
  BOOLEAN                 IsRavenOpn;
  EFI_GUID                VbiosGuids = AMD_PEI_VBIOS_FFS_GUID;
  EFI_GUID                VbiosGuidsRv2 = AMD_PEI_VBIOS_FFS_GUID_RAVEN2;
  UINT8                   NextBridgeNum;
  VOID                    *VbiosImage;  
  UINTN                   Instance;
  EFI_PEI_FV_HANDLE       VolumeHandle;
  EFI_PEI_FILE_HANDLE     FileHandle;    
  AMD_PEI_GOP_POLICY_V1_1 *AmdPeiGopPolicyPtr;  
  
  Status = PeiServicesAllocatePool(sizeof(AMD_PEI_GOP_POLICY_V1_1), (VOID **)&AmdPeiGopPolicyPtr);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Unable to allocate space for AmdPeiGopPolicyPtr %r!\n", Status));
    return NULL;
  } 
  
  ZeroMem (AmdPeiGopPolicyPtr, sizeof(AMD_PEI_GOP_POLICY_V1_1));   
  Instance = 0;                                                                                       
  while (TRUE) {
    Status = PeiServicesFfsFindNextVolume (Instance++, &VolumeHandle);
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "Unable to find next FV, %r!\n", Status));    
      return NULL;
    }
    
    IsRavenOpn = CheckRvOpnB4(); // Check for Picosso
    if(IsRavenOpn) Status = PeiServicesFfsFindFileByName (&VbiosGuids, VolumeHandle, &FileHandle);
    else Status = PeiServicesFfsFindFileByName (&VbiosGuidsRv2, VolumeHandle, &FileHandle);

    if (!EFI_ERROR (Status)) {
      Status = PeiServicesFfsFindSectionData (EFI_SECTION_RAW, FileHandle, &VbiosImage);
      if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "Unable to find VBIOS file section ffs %r!\n", Status));
        return NULL;
      } 
      AmdPeiGopPolicyPtr->VbiosImage = VbiosImage;     
      break;
    }
  } 

  AmdPeiGopPolicyPtr->Header.TableSize = sizeof(AMD_PEI_GOP_POLICY_V1_1);
  AmdPeiGopPolicyPtr->Header.FormatRevision = AMD_PEI_GOP_FORMAT_REVISION;  
  AmdPeiGopPolicyPtr->Header.ContentRevision = AMD_PEI_GOP_CONTENT_REVISION;
  NextBridgeNum = PciRead8(PCI_LIB_ADDRESS (0, 8, 1, 0x19));
  AmdPeiGopPolicyPtr->GfxBar0 = PciRead32(PCI_LIB_ADDRESS (NextBridgeNum, 0, 0, 0x10));
  AmdPeiGopPolicyPtr->GfxBar1 = PciRead32(PCI_LIB_ADDRESS (NextBridgeNum, 0, 0, 0x14));
  AmdPeiGopPolicyPtr->GfxBar2 = PciRead32(PCI_LIB_ADDRESS (NextBridgeNum, 0, 0, 0x18));
  AmdPeiGopPolicyPtr->GfxBar3 = PciRead32(PCI_LIB_ADDRESS (NextBridgeNum, 0, 0, 0x1C));
  AmdPeiGopPolicyPtr->GfxBar4 = PciRead32(PCI_LIB_ADDRESS (NextBridgeNum, 0, 0, 0x20));
  AmdPeiGopPolicyPtr->GfxBar5 = PciRead32(PCI_LIB_ADDRESS (NextBridgeNum, 0, 0, 0x24)); 
  AmdPeiGopPolicyPtr->LidStatus = TRUE;
  AmdPeiGopPolicyPtr->HorizontalResolution = 1366; 
  AmdPeiGopPolicyPtr->VerticalResolution = 768;
  
  return (VOID *)AmdPeiGopPolicyPtr;          
}

/*++

Routine Description:

  GraphicsPpiNotifyCallback 

Arguments:

Returns:

  EFI_STATUS

--*/
EFI_STATUS
GraphicsPpiNotifyCallback (
  IN       EFI_PEI_SERVICES             **PeiServices,
  IN       EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN       VOID                         *Ppi
  )
{
  EFI_STATUS              Status;
  EFI_PEI_GRAPHICS_PPI    *GraphicsPpi;  
  AMD_PEI_GOP_POLICY_V1_1 *AmdPeiGopPolicyPtr;     
  
  DEBUG((EFI_D_INFO, "GraphicsPpiNotifyCallback.\n"));
  Status = (*PeiServices)->LocatePpi (
                               PeiServices,
                               &gEfiPeiGraphicsPpiGuid,
                               0,
                               NULL,
                               (VOID**)&GraphicsPpi
                               ); 
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "  gEfiPeiGraphicsPpiGuid locate failed.\n"));
    return Status;  
  }
  
  AmdPeiGopPolicyPtr = (AMD_PEI_GOP_POLICY_V1_1 *)PreaprePeiGopPolicyData();
  if (AmdPeiGopPolicyPtr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
                                               
  Status = GraphicsPpi->GraphicsPpiInit((VOID *)AmdPeiGopPolicyPtr);
  if (!EFI_ERROR(Status)) {
    DrawAmdLogo(PeiServices);
  }
  return Status;
}

/*++

Routine Description:

  GfxInit 

Arguments:

Returns:

  EFI_STATUS

--*/
EFI_STATUS
GfxInit (
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS              Status;
  EFI_PEI_GRAPHICS_PPI    *GraphicsPpi;
  AMD_PEI_GOP_POLICY_V1_1 *AmdPeiGopPolicyPtr;
  
  DEBUG((EFI_D_INFO, "GfxInit.\n"));
  Status = (**PeiServices).LocatePpi (
                               PeiServices,
                               &gEfiPeiGraphicsPpiGuid,
                               0,
                               NULL,
                               (VOID**)&GraphicsPpi
                               );
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "  gEfiPeiGraphicsPpiGuid locate failed. Create Notify\n"));
    Status = (**PeiServices).NotifyPpi (PeiServices, &mGraphicsPpiNotify);
    return Status;         
  }
  
  AmdPeiGopPolicyPtr = (AMD_PEI_GOP_POLICY_V1_1 *)PreaprePeiGopPolicyData();
  if (AmdPeiGopPolicyPtr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }                 

  Status = GraphicsPpi->GraphicsPpiInit((VOID *)AmdPeiGopPolicyPtr);;
  if (!EFI_ERROR(Status)) {
    DrawAmdLogo(PeiServices);
  }
  return Status;  
}

/*++

Routine Description:

  AllocateGfxResource
  Allocate proper resource for Gfx and the upper bridge.

Arguments:

Returns:

  EFI_STATUS

--*/
EFI_STATUS
AllocateGfxResource (
  IN CONST EFI_PEI_SERVICES     **PeiServices
)
{
  EFI_STATUS                     Status = EFI_SUCCESS;
  UINT32                         Index;
  UINT32                         VidDid;
  UINT16                         Data16;
  UINT32                         Data32;
  UINT32                         Length = 0;
  UINT64                         TotalPrefetchableSize = 0;
  UINT64                         ConsumedPrefetchableMem;
  UINT64                         TotalNonPrefetchableSize = 0;
  UINT64                         ConsumedNonPrefetchableMem;  
  UINT64                         TotalIOSize = 0;
  UINT64                         ConsumedIo;    
  BOOLEAN                        IsMemResource, IsPrefetchableMem, Is64BitBar;  
  UINT64                         AllocatedPrefetchableBase = 0;
  UINT64                         AllocatedNonPrefetchableBase = 0;
  UINT64                         AllocatedIoBase = 0;      
  UINT64                         AllocatedPrefetchableSize = 0;
  UINT64                         AllocatedNonPrefetchableSize = 0;
  UINT64                         AllocatedIoSize = 0;
  //---FABRIC_RESOURCE_FOR_EACH_DIE   MmioForEachDie;
  FABRIC_RESOURCE_FOR_EACH_RB   MmioForEachDie;
  #if 0  
  FABRIC_TARGET                  Target;
  #endif 

  DEBUG((EFI_D_INFO, "AllocateGfxResource Entry.\n"));
  // AMI porting start
  //PciWrite32(PCI_LIB_ADDRESS (0, 8, 1, 0x18), 0x40400); //Assign the sencondary bus and sub bus num.
  PciWrite8(PCI_LIB_ADDRESS (0, 8, 1, 0x19), FixBus); //Assign the sencondary bus and sub bus num.
  PciWrite8(PCI_LIB_ADDRESS (0, 8, 1, 0x1A), FixBus); //Assign the sencondary bus and sub bus num.
  // AMI porting end
  VidDid = PciRead32(PCI_LIB_ADDRESS (FixBus, 0, 0, 00));
  if (VidDid == 0xFFFFFFFF) {
    DEBUG((EFI_D_ERROR, "iGfx not found.\n"));
    return EFI_DEVICE_ERROR;  
  } 
  DEBUG((EFI_D_INFO, "  iGfx Vendor ID and Device ID: 0x%x.\n", VidDid));
  
  // Query the iGFX required resources.
  for (Index = 0; Index < AMD_GFX_NUM_OF_BAR; Index++) {
    PciWrite32 (PCI_LIB_ADDRESS (FixBus, 0, 0, 0x10 + (Index * 4)), ALL_ONE_32_BITS);
    Data32 = PciRead32(PCI_LIB_ADDRESS (FixBus, 0, 0, 0x10 + (Index * 4)));
    DEBUG((EFI_D_INFO, "-------------------------------------\n"));    
    DEBUG((EFI_D_INFO, "    BarIndex[0x%x]: 0x%x.\n", Index, Data32));    
    if (Data32 == ALL_ONE_32_BITS) {
      continue;
    }
    
    Length = ~(Data32 & 0xFFFFFFF0) + 1;
    DEBUG((EFI_D_INFO, "      BarRes[0x%x]: Length: 0x%x\n", Index, Length));
           
    IsMemResource = (Data32 & BIT0)? FALSE : TRUE;    
    if( IsMemResource) {
      DEBUG((EFI_D_INFO, "    Bar[0x%x] Resource Type: MEM", Index));
      IsPrefetchableMem = (Data32 & BIT3)? TRUE : FALSE;
      if(IsPrefetchableMem) {
        DEBUG((EFI_D_INFO, " Prefetchable.\n"));
        TotalPrefetchableSize += Length;
      } else {
        DEBUG((EFI_D_INFO, " Non-Prefetchable.\n"));
        TotalNonPrefetchableSize += Length;
      }
    } else {
      DEBUG((EFI_D_INFO, "    Bar[0x%x] Resource Type: IO\n", Index));
      TotalIOSize += Length; 
    }
    DEBUG((EFI_D_INFO, "-------------------------------------\n"));
    DEBUG((EFI_D_INFO, "  Prefetchable Required: 0x%x.\n", TotalPrefetchableSize));
    DEBUG((EFI_D_INFO, "  Non-Prefetchable Required: 0x%x.\n", TotalNonPrefetchableSize));
    DEBUG((EFI_D_INFO, "  IO Required: 0x%x.\n", TotalIOSize));        
  }     

  Status = FabricGetAvailableResource (&MmioForEachDie);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "  NonPrefetchableMmioSizeBelow4G.Base                = 0x%016LX\n", MmioForEachDie.NonPrefetchableMmioSizeBelow4G[0][0].Base));
  DEBUG ((DEBUG_INFO, "  NonPrefetchableMmioSizeBelow4G.Size                = 0x%08X\n", MmioForEachDie.NonPrefetchableMmioSizeBelow4G[0][0].Size));
  DEBUG ((DEBUG_INFO, "  PrefetchableMmioSizeBelow4G.Base                   = 0x%016LX\n", MmioForEachDie.PrefetchableMmioSizeBelow4G[0][0].Base));
  DEBUG ((DEBUG_INFO, "  PrefetchableMmioSizeBelow4G.Size                   = 0x%08X\n", MmioForEachDie.PrefetchableMmioSizeBelow4G[0][0].Size));  
  DEBUG ((DEBUG_INFO, "  PrimaryRbSecondNonPrefetchableMmioSizeBelow4G.Base      = 0x%016LX\n", MmioForEachDie.PrimaryRbSecondNonPrefetchableMmioSizeBelow4G.Base));
  DEBUG ((DEBUG_INFO, "  PrimaryRbSecondNonPrefetchableMmioSizeBelow4G.Size      = 0x%08X\n", MmioForEachDie.PrimaryRbSecondNonPrefetchableMmioSizeBelow4G.Size));
  DEBUG ((DEBUG_INFO, "  PrimaryRbSecondPrefetchableMmioSizeBelow4G.Base         = 0x%016LX\n", MmioForEachDie.PrimaryRbSecondPrefetchableMmioSizeBelow4G.Base));
  DEBUG ((DEBUG_INFO, "  PrimaryRbSecondPrefetchableMmioSizeBelow4G.Size         = 0x%08X\n", MmioForEachDie.PrimaryRbSecondPrefetchableMmioSizeBelow4G.Size));
  DEBUG ((DEBUG_INFO, "  IO.Base                                            = 0x%016LX\n", MmioForEachDie.IO[0][0].Base));
  DEBUG ((DEBUG_INFO, "  IO.Size                                            = 0x%08X\n", MmioForEachDie.IO[0][0].Size));      
  // cppcheck-suppress knownConditionTrueFalse  
  if (MmioForEachDie.PrefetchableMmioSizeBelow4G[0][0].Size >= TotalPrefetchableSize && AllocatedPrefetchableBase == 0) {
    AllocatedPrefetchableBase = MmioForEachDie.PrefetchableMmioSizeBelow4G[0][0].Base;
    AllocatedPrefetchableSize = MmioForEachDie.PrefetchableMmioSizeBelow4G[0][0].Size;  
  }

  if (MmioForEachDie.PrimaryRbSecondPrefetchableMmioSizeBelow4G.Size >= TotalPrefetchableSize && AllocatedPrefetchableBase == 0) {
    AllocatedPrefetchableBase = MmioForEachDie.PrimaryRbSecondPrefetchableMmioSizeBelow4G.Base;
    AllocatedPrefetchableSize = MmioForEachDie.PrimaryRbSecondPrefetchableMmioSizeBelow4G.Size; 
  }  
  
  if (MmioForEachDie.NonPrefetchableMmioSizeBelow4G[0][0].Size >= TotalPrefetchableSize && AllocatedPrefetchableBase == 0) {
    AllocatedPrefetchableBase = MmioForEachDie.NonPrefetchableMmioSizeBelow4G[0][0].Base;
    AllocatedPrefetchableSize = TotalPrefetchableSize;
    MmioForEachDie.NonPrefetchableMmioSizeBelow4G[0][0].Base += TotalPrefetchableSize; 
    MmioForEachDie.NonPrefetchableMmioSizeBelow4G[0][0].Size -= TotalPrefetchableSize;
  }
  
  if (MmioForEachDie.PrimaryRbSecondNonPrefetchableMmioSizeBelow4G.Size >= TotalPrefetchableSize && AllocatedPrefetchableBase == 0) {
    AllocatedPrefetchableBase = MmioForEachDie.PrimaryRbSecondNonPrefetchableMmioSizeBelow4G.Base;
    AllocatedPrefetchableSize = TotalPrefetchableSize;
    MmioForEachDie.PrimaryRbSecondNonPrefetchableMmioSizeBelow4G.Base += TotalPrefetchableSize; 
    MmioForEachDie.PrimaryRbSecondNonPrefetchableMmioSizeBelow4G.Size -= TotalPrefetchableSize;
  }     
  DEBUG((EFI_D_INFO, "AllocatedPrefetchableBase: 0x%016LX, AllocatedPrefetchableSize: 0x%08X.\n", AllocatedPrefetchableBase, AllocatedPrefetchableSize));
  // cppcheck-suppress knownConditionTrueFalse      
  if (MmioForEachDie.NonPrefetchableMmioSizeBelow4G[0][0].Size >= TotalNonPrefetchableSize && AllocatedNonPrefetchableBase == 0) {
    AllocatedNonPrefetchableBase = MmioForEachDie.NonPrefetchableMmioSizeBelow4G[0][0].Base;
    AllocatedNonPrefetchableSize = MmioForEachDie.NonPrefetchableMmioSizeBelow4G[0][0].Size;
  }
  
  if (MmioForEachDie.PrimaryRbSecondNonPrefetchableMmioSizeBelow4G.Size >= TotalNonPrefetchableSize && AllocatedNonPrefetchableBase == 0) {
    AllocatedNonPrefetchableBase = MmioForEachDie.PrimaryRbSecondNonPrefetchableMmioSizeBelow4G.Base;
    AllocatedNonPrefetchableSize = MmioForEachDie.PrimaryRbSecondNonPrefetchableMmioSizeBelow4G.Size;
  }     
  
  DEBUG((EFI_D_INFO, "AllocatedNonPrefetchableBase: 0x%016LX, AllocatedNonPrefetchableSize: 0x%08X.\n", AllocatedNonPrefetchableBase, AllocatedNonPrefetchableSize));  
  
  //#define RES_IO_BASE        0x2000
  //#define RES_IO_LIMIT       0x10000
  //IO.Base                                            = 0x0000000000001000
  //IO.Size                                            = 0x0000F000
  if ((MmioForEachDie.IO[0][0].Base <= RES_IO_BASE) && ((MmioForEachDie.IO[0][0].Base + MmioForEachDie.IO[0][0].Size) >= (RES_IO_BASE + RES_IO_LIMIT))) {
    AllocatedIoBase = RES_IO_BASE;
    AllocatedIoSize = RES_IO_LIMIT - RES_IO_BASE;
    DEBUG((EFI_D_ERROR, "DFx0C0 - IO Space Base Address: 0x%08x.\n", PciRead32(PCI_LIB_ADDRESS (0, 0x18, 0, 0xC0))));
    DEBUG((EFI_D_ERROR, "DFx0C4 - IO Space Limit Address: 0x%08x.\n", PciRead32(PCI_LIB_ADDRESS (0, 0x18, 0, 0xC4))));    
  } else {
    AllocatedIoBase =  MmioForEachDie.IO[0][0].Base;
    AllocatedIoSize =  MmioForEachDie.IO[0][0].Size;
  }
    
  DEBUG((EFI_D_INFO, "AllocatedIoBase: 0x%016LX, AllocatedIoSize: 0x%08X.\n", AllocatedIoBase, AllocatedIoSize));  
     
  //             0x80000               0x00800000                      0x1020 0000                0x1800 0000                   0x100        0
  if ((TotalNonPrefetchableSize > AllocatedNonPrefetchableSize) || (TotalPrefetchableSize > AllocatedPrefetchableSize) || (TotalIOSize > AllocatedIoSize)) {
    DEBUG((EFI_D_ERROR, "Out of resource.\n"));  
    return EFI_OUT_OF_RESOURCES;    
  } 
    
  // Assign Non-Prefetchable MMIO resource to bridge.
  if (AllocatedNonPrefetchableBase != 0) {  
    // AMI porting start
    //  Data32 = ((AllocatedNonPrefetchableBase & 0xFFF00000) >> 16) + \
    //           ((AllocatedNonPrefetchableBase + TotalNonPrefetchableSize - 1) & 0xFFF00000);
    Data32 = 0;
    if ( AllocatedNonPrefetchableBase < (PEI_BRIDGE_MMIO_MIN << 16) ){
        Data32 = ((AllocatedNonPrefetchableBase & 0xFFF00000) >> 16);
    } else {
        Data32 = PEI_BRIDGE_MMIO_MIN;   
    }
    if ( ((AllocatedNonPrefetchableBase + TotalNonPrefetchableSize - 1) & 0xFFF00000) < (PEI_BRIDGE_MMIO_MAX << 16) ){
        Data32 |= (PEI_BRIDGE_MMIO_MAX << 16 );
    } else {
        Data32 |= ((AllocatedNonPrefetchableBase + TotalNonPrefetchableSize - 1) & 0xFFF00000);   
    }        
    // AMI porting end
    DEBUG((EFI_D_INFO, "MEM_BASE_LIMIT: 0x%x.\n", Data32));             
    PciWrite32(PCI_LIB_ADDRESS (0, 8, 1, 0x20), Data32);              
  }
  
  // Assign Non-Prefetchable MMIO resource to bridge.
  if (AllocatedPrefetchableBase != 0) {  
    Data32 = ((AllocatedPrefetchableBase & 0xFFF00000) >> 16) + \
             ((AllocatedPrefetchableBase + TotalPrefetchableSize - 1) & 0xFFF00000);
    DEBUG((EFI_D_INFO, "PREF_BASE_LIMIT: 0x%x.\n", Data32));             
    PciWrite32(PCI_LIB_ADDRESS (0, 8, 1, 0x24), Data32);
    
    Data32 = (AllocatedPrefetchableBase >> 32) & ALL_ONE_32_BITS;
    DEBUG((EFI_D_INFO, "PREF_BASE_UPPER: 0x%x.\n", Data32));
    PciWrite32(PCI_LIB_ADDRESS (0, 8, 1, 0x28), Data32);

    Data32 = ((AllocatedPrefetchableBase + TotalPrefetchableSize - 1) >> 32) & ALL_ONE_32_BITS;
    DEBUG((EFI_D_INFO, "PREF_LIMIT_UPPER: 0x%x.\n", Data32));
    PciWrite32(PCI_LIB_ADDRESS (0, 8, 1, 0x2C), Data32);                           
  }

  // Assign IO resource to bridge.
  if (AllocatedIoBase != 0) {
    Data16 =  ((AllocatedIoBase & 0xF000) >> 8) + BIT0 + \
              ((AllocatedIoBase + TotalIOSize - 1) & 0xF000) + BIT8;
    DEBUG((EFI_D_INFO, "IO_BASE_LIMIT: 0x%x.\n", Data16));               
    PciWrite16(PCI_LIB_ADDRESS (0, 8, 1, 0x1C), Data16);
    
    Data32 = ((AllocatedIoBase & 0xFFFF0000) >> 16) + \
             ((AllocatedIoBase + TotalIOSize - 1) & 0xFFFF0000);
    DEBUG((EFI_D_INFO, "IO_BASE_LIMIT_HI: 0x%x.\n", Data32));
    PciWrite32(PCI_LIB_ADDRESS (0, 8, 1, 0x30), Data32);    
  }  
    
  // Assign resources to iGFX.
  ConsumedNonPrefetchableMem = 0;
  ConsumedPrefetchableMem = 0;
  ConsumedIo = 0;
  // cppcheck-suppress unreadVariable  
  Is64BitBar = FALSE;   
  for (Index = 0; Index < AMD_GFX_NUM_OF_BAR; Index++) {
    PciWrite32 (PCI_LIB_ADDRESS (FixBus, 0, 0, 0x10 + (Index * 4)), ALL_ONE_32_BITS);  
    Data32 = PciRead32(PCI_LIB_ADDRESS (FixBus, 0, 0, 0x10 + (Index * 4)));
    DEBUG((EFI_D_INFO, "-------------------------------------\n"));    
    DEBUG((EFI_D_INFO, "    BarIndex[0x%x]: 0x%x.\n", Index, Data32));
    
    Length = ~(Data32 & 0xFFFFFFF0) + 1;
    DEBUG((EFI_D_INFO, "      BarRes[0x%x]: Length: 0x%x\n", Index, Length));

    IsMemResource = (Data32 & BIT0)? FALSE : TRUE;
    if( IsMemResource) {
      DEBUG((EFI_D_INFO, "    Bar[0x%x] Resource Type: MEM", Index));
      IsPrefetchableMem = (Data32 & BIT3)? TRUE : FALSE;
      Is64BitBar = (Data32 & BIT2)? TRUE : FALSE;       
      if(IsPrefetchableMem && (AllocatedPrefetchableBase != 0)) {
        DEBUG((EFI_D_INFO, " Prefetchable.\n"));
        Data32 = ((AllocatedPrefetchableBase + ConsumedPrefetchableMem) & 0xFFFFFFF0) + (Data32 & 0xF) ;
        DEBUG((EFI_D_INFO, "    Bar[0x%x] value: 0x%x \n", Index, Data32));
        PciWrite32 (PCI_LIB_ADDRESS (FixBus, 0, 0, 0x10 + (Index * 4)), Data32);        
        if (Is64BitBar) {
          DEBUG((EFI_D_INFO, "    Is 64 bits bar, program the next bar for upper address.\n"));        
          Index++;
          Data32 = (AllocatedPrefetchableBase + ConsumedPrefetchableMem) >> 32;          
          DEBUG((EFI_D_INFO, "    Bar[0x%x] value: 0x%x\n", Index, Data32));          
          PciWrite32 (PCI_LIB_ADDRESS (FixBus, 0, 0, 0x10 + (Index * 4)), Data32);                  
        }
        ConsumedPrefetchableMem += Length;   
        DEBUG((EFI_D_INFO, "    ConsumedPrefetchableMem: 0x%x \n", ConsumedPrefetchableMem));
        
      } else if (!IsPrefetchableMem && (AllocatedNonPrefetchableBase != 0)) {      
        DEBUG((EFI_D_INFO, " Non-Prefetchable.\n"));
        
        Data32 = ((AllocatedNonPrefetchableBase + ConsumedNonPrefetchableMem) & 0xFFFFFFF0) + (Data32 & 0xF) ;
        DEBUG((EFI_D_INFO, "    Bar[0x%x] value:  0x%x\n", Index, Data32));
        PciWrite32 (PCI_LIB_ADDRESS (FixBus, 0, 0, 0x10 + (Index * 4)), Data32);        
        ConsumedNonPrefetchableMem += Length;
        DEBUG((EFI_D_INFO, "    ConsumedNonPrefetchableMem: 0x%x  \n", ConsumedNonPrefetchableMem));                        
      }      
    } else {
      DEBUG((EFI_D_INFO, "    Bar[0x%x] Resource Type: IO\n", Index));
      if (AllocatedIoBase != 0) {
        Data32 = ((AllocatedIoBase + ConsumedIo) & 0xFFFFFFF0) + (Data32 & 0xF);
        DEBUG((EFI_D_INFO, "    Bar[0x%x] value:  0x%x\n", Index, Data32));        
        PciWrite32 (PCI_LIB_ADDRESS (FixBus, 0, 0, 0x10 + (Index * 4)), Data32);
        ConsumedIo += Length;
        DEBUG((EFI_D_INFO, "    ConsumedIo: 0x%x  \n", ConsumedIo));                        
      }
    }               
    DEBUG((EFI_D_INFO, "-------------------------------------\n"));                  
  }

  #if 0
  // VGA Enable register for VGA compatibility space
  Target.TgtType = TARGET_DIE;
  Target.SocketNum = 0;
  Target.DieNum = 0;
  FabricEnableVgaMmio (Target);
  #endif
  
  // Enable GFX and bridge access.
  PciOr8 (PCI_LIB_ADDRESS (0, 8, 1, 0x3E), BIT2 + BIT3); //ISA_EN and VGA_EN
  PciOr8 (PCI_LIB_ADDRESS (0, 8, 1, 0x04), BIT0 + BIT1 + BIT2); //APC: Enable Bus Master, Enable memory/io decoding
  PciOr8 (PCI_LIB_ADDRESS (FixBus, 0, 0, 0x04), BIT0 + BIT1 + BIT2); //iGFX: Enable Bus Master, Enable memory/io decoding

  DEBUG((EFI_D_INFO, "AllocateGfxResource Exit.\n"));  
  return EFI_SUCCESS;  
}

/*++

Routine Description:

  Gfx Pei Init Entry. 

Arguments:

Returns:

  EFI_STATUS

--*/
EFI_STATUS
EFIAPI
GfxInitPeiEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS                     Status = EFI_SUCCESS;
  EFI_BOOT_MODE                  BootMode;  

  DEBUG((EFI_D_INFO, "GfxInitPeiEntry.\n"));

  Status = PeiServicesGetBootMode (&BootMode);
  if (BootMode != BOOT_IN_RECOVERY_MODE) {
    DEBUG((EFI_D_ERROR, "Not in recovery mode.\n"));  
     return EFI_SUCCESS;
  }

  //
  // The RV Gfx is integrated with other IPs under the same bridge.
  // If you have allocated the resource in other place.
  // Just allocate the Gfx resource there, don't need to allocate the resource here again.
  //
//#if 0
  // Allocate PCIE resource for Gfx.
  Status = AllocateGfxResource (PeiServices);
  if (EFI_ERROR(Status)) {
    return Status;  
  }
//#endif  
  
  // Locate Graphics Ppi and call initial function...
  Status = GfxInit(PeiServices);
  return Status;
}
