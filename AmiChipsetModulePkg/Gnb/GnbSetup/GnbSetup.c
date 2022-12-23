//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************



/** @file GnbSetup.c
    GNB Setup Routines

**/

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/PrintLib.h>
#include <Setup.h>
#include "AmiCspLib.h"
#include "Token.h"

#include <Protocol/ComponentName.h>
#include <Protocol/DevicePath.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/DriverBinding.h>

#include <AmiChipsetModulePkg/Include/Gnb.h>
#if PCI_BUS_REVISION > 16
#include <PciBus.h>
#endif

#if CSM_SUPPORT
#include "AmiModulePkg/CSM/Csm.h"
#include <Protocol/LegacyBios.h>
#include "AmiModulePkg/CSM/CsmVideo/VesaBiosExtensions.h"


#define EFI_SIGNATURE_16(A,B)             ((A) | (B<<8))
#define EFI_SIGNATURE_32(A,B,C,D)         (EFI_SIGNATURE_16(A,B)     | (EFI_SIGNATURE_16(C,D)     << 16))

//
// Super VGA Information Block
//
#pragma pack (push, 1)
typedef struct {
  UINT32  VESASignature;      // 'VESA' 4 byte signature
  UINT16  VESAVersion;        // VBE version number
  UINT32  OEMStringPtr;       // Pointer to OEM string
  UINT32  Capabilities;       // Capabilities of video card
  UINT32  VideoModePtr;       // Pointer to an array of 16-bit supported modes values terminated by 0xFFFF
  UINT16  TotalMemory;        // Number of 64kb memory blocks
  union {
       struct  {
                UINT8   MinorRev;
                UINT8   MajorRev;
       }SoftwareRev;
       UINT16  OemSoftwareRev;   // VBE implementation Software revision
    };
  union {
    struct {
            UINT16   VendorNameOffset;
            UINT16   VendorNameSeg;
    }VendorName;
    UINT32  OemVendorNamePtr;   // VbeFarPtr to Vendor Name String
  };

  union {
    struct {
        UINT16   ProductNameOffset;
        UINT16   ProductNameSeg;
    }ProductName;
    UINT32  OemProductNamePtr;   // // VbeFarPtr to Product Name String
  };

  union {
    struct {
        UINT16   ProductRevOffset;
        UINT16   ProductRevSeg;
    }ProductRev;
    UINT32  OemProductRevPtr;   // VbeFarPtr to Product Revision String
  };
  UINT8   Reserved[222];      // Reserved for VBE implementation scratch area
  UINT8   OemData[256];       // Data area for OEM strings.  Pad to 512 byte block size
} GNB_VESA_BIOS_EXTENSIONS_INFORMATION_BLOCK;
#pragma pack (pop)
#endif

CHAR8                       gGopVersionString[0x40];

/**
    This function transfer Ascii To Unicode. 

    @param CHAR8   *AsciiString   
    @param CHAR16  *UnicodeString

    @retval VOID

**/

VOID
GnbAsciiToUnicode (
    IN  CHAR8       *AsciiString,
    OUT CHAR16      *UnicodeString
)
{
    UINT8           Index = 0;

    while (AsciiString[Index] != 0) {
        if (AsciiString[Index] == 0x20 && AsciiString[Index+1] ==0x20) break;
        UnicodeString[Index] = (CHAR16) AsciiString[Index];
        Index++;
    }
}

/**
    This function is  GetDriverName. 

    @param EFI_HANDLE   DriverBindingHandle   
    @param CHAR8  *String

    @retval TRUE - Get driver name Success.
    @retval FALSE - Get driver name fail.

**/

BOOLEAN
GnbGetDriverName (
  IN  EFI_HANDLE  DriverBindingHandle,
  OUT CHAR8       *String )
{
    EFI_STATUS                      Status;
    CHAR16                          *DriverName;
    EFI_COMPONENT_NAME_PROTOCOL     *ComponentName;
    CHAR8                           *Lang = NULL;

    //
    // Get driver name from UEFI 2.0 Component Name 2 protocol interface.
    //
    Status = gBS->OpenProtocol(
                  DriverBindingHandle,
                  &gEfiComponentName2ProtocolGuid,
                  (VOID**)&ComponentName,
                  NULL,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (!EFI_ERROR(Status)) {

        Status = ComponentName->GetDriverName(ComponentName, LANGUAGE_CODE_ENGLISH, &DriverName);
        if (EFI_ERROR(Status)) {

            //
            // Driver does not support "en-us", try to get SupportedLanguages
            //
            gBS->AllocatePool(EfiBootServicesData, Strlen(ComponentName->SupportedLanguages)+1, &Lang);
            if (Lang != NULL) {
                CHAR8                           *TempChar;

                AsciiStrCpyS(Lang, Strlen(ComponentName->SupportedLanguages)+1, ComponentName->SupportedLanguages);
                TempChar = Strstr(Lang, ";");
                if (TempChar != NULL) *TempChar = 0x0000;
                Status = ComponentName->GetDriverName(ComponentName, Lang, &DriverName);
                gBS->FreePool(Lang);
                Lang = NULL;
            }
        }

        if (!EFI_ERROR(Status)) {
            AsciiSPrint(String, Strlen(String),"%S", DriverName);
            return TRUE;
        }

    }

    //
    // If it fails to get the driver name from Component Name protocol interface, we should fall back on
    // EFI 1.1 Component Name protocol interface.
    //
    Status = gBS->OpenProtocol(
                  DriverBindingHandle,
                  &gEfiComponentNameProtocolGuid,
                  (VOID**)&ComponentName,
                  NULL,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (!EFI_ERROR(Status)) {
        Status = ComponentName->GetDriverName(ComponentName, "eng", &DriverName);
        if (!EFI_ERROR(Status)) {
            AsciiSPrint(String, Strlen(String),"%S", DriverName);
            return TRUE;
        }
    }

    return FALSE;
}


/**
    Get DriverBinding Handle by input device handle.

    @param ControllerHandle - the device controller handle be opened by its child device.
    @param *DriverBindingHandle - the handle of a driver which contains the binding protocol.

    @retval EFI_SUCCESS - DriverBinding handle found.

    @note  None.

**/

EFI_STATUS
GnbGetDriverBindingHandle (
  IN  EFI_HANDLE  ControllerHandle,
  OUT EFI_HANDLE  *DriverBindingHandle )
{
    EFI_STATUS                          Status;
    UINTN                               HandleCount;
    EFI_HANDLE                          *HandleBuffer;
    UINTN                               HandleIndex;
    EFI_GUID                            **ProtocolGuidArray;
    UINTN                               ArrayCount;
    UINTN                               ProtocolIndex;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *OpenInfo;
    UINTN                               OpenInfoCount;
    UINTN                               OpenInfoIndex;
    UINTN                               Index;

    Status = gBS->LocateHandleBuffer(
                  AllHandles,   
                  NULL,
                  NULL,
                  &HandleCount, 
                  &HandleBuffer);
    if (EFI_ERROR(Status)) return EFI_NOT_FOUND;

    for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
        ProtocolGuidArray = NULL;
        Status = gBS->ProtocolsPerHandle(
                      HandleBuffer[HandleIndex], 
                      &ProtocolGuidArray, 
                      &ArrayCount);
        if (EFI_ERROR(Status)) continue;

        for (ProtocolIndex = 0; ProtocolIndex < ArrayCount; ProtocolIndex++) {
            Status = gBS->OpenProtocolInformation(
                          HandleBuffer[HandleIndex], 
                          ProtocolGuidArray[ProtocolIndex],
                          &OpenInfo,
                          &OpenInfoCount);
            if (EFI_ERROR(Status)) continue;

            for (OpenInfoIndex = 0; OpenInfoIndex < OpenInfoCount; OpenInfoIndex++) {
                if (OpenInfo[OpenInfoIndex].ControllerHandle == ControllerHandle) {
                    if ((OpenInfo[OpenInfoIndex].Attributes & EFI_OPEN_PROTOCOL_BY_DRIVER) == EFI_OPEN_PROTOCOL_BY_DRIVER) {
                        for(Index = 0; Index < HandleCount; Index++) {
                            if(HandleBuffer[Index] == OpenInfo[OpenInfoIndex].AgentHandle) {
                                *DriverBindingHandle=HandleBuffer[Index];
                                gBS->FreePool(OpenInfo);
                                gBS->FreePool(ProtocolGuidArray);
                                gBS->FreePool(HandleBuffer);
                                return EFI_SUCCESS;
                            }
                        }
                    }
                }
            }
            if (OpenInfo != NULL) gBS->FreePool(OpenInfo);
        }
         if (ProtocolGuidArray != NULL) gBS->FreePool(ProtocolGuidArray);
    }
    if (HandleBuffer != NULL) gBS->FreePool(HandleBuffer);
    return EFI_NOT_FOUND;
}

/**
    Update IGD Gop Version in Setup String

    @param HiiHandle - Handle to HII database
    @retval VOID

    @note  None.

**/

VOID UpdateIGDGopVersion(IN EFI_HII_HANDLE HiiHandle) 
{
    /*
    EFI_STATUS                  Status;
    UINTN                       ControllerHandleCount = 0;
    EFI_HANDLE                  *ControllerHandleBuffer = NULL;
    EFI_HANDLE                  ControllerHandle;
    UINTN                       ControllerHandleIndex;
    EFI_HANDLE                  DriverBindingHandle;
    EFI_PCI_IO_PROTOCOL         *pciio;

    PCI_DEV_INFO                *dev;

    Status = gBS->LocateHandleBuffer(
                  ByProtocol,
                  &gEfiPciIoProtocolGuid,
                  NULL,
                  &ControllerHandleCount,
                  &ControllerHandleBuffer);
    if (EFI_ERROR(Status)) return;

    for (ControllerHandleIndex = 0; ControllerHandleIndex < ControllerHandleCount; ControllerHandleIndex++) {
        ControllerHandle = ControllerHandleBuffer[ControllerHandleIndex];
        Status = gBS->HandleProtocol (ControllerHandle, &gEfiPciIoProtocolGuid, &pciio);
        if (EFI_ERROR(Status)) continue;

        Status = GnbGetDriverBindingHandle (ControllerHandle, &DriverBindingHandle);
        if (EFI_ERROR(Status)) continue;

        //IGD GOP Driver check
         dev = (PCI_DEV_INFO*)pciio;
        if(!((dev->ParentBrg->Address.Addr.Bus == 0)
             && (dev->ParentBrg->Address.Addr.Device == 8)
             && (dev->ParentBrg->Address.Addr.Function == 1)
             && (dev->Address.Addr.Device == 0)
             && (dev->Address.Addr.Function == 0)))
        continue;

        if (GnbGetDriverName(DriverBindingHandle, gGopVersionString)) {
            InitString(HiiHandle, STRING_TOKEN(STR_VBIOS_VERSION), L"%a", gGopVersionString);
            break;
        }
    }
    */
}

/**
    InitGnbStrings Setup String

    @param HiiHandle - Handle to HII database
    @param Class - Indicates the setup class

    @retval VOID

    @note  None.

**/

VOID InitGnbStrings(IN EFI_HII_HANDLE HiiHandle, IN UINT16 Class)
{

  if (Class == CHIPSET_FORM_SET_CLASS) {
/*
//It is a sample code.
//CPM has shown GOP/VBIOS information, we needn't show this information in GNB part.

#if CSM_SUPPORT
        EFI_STATUS                 Status;
        EFI_LEGACY_BIOS_PROTOCOL  *LegacyBios;
        CHAR16               VersionString[30];
        CHAR16               VersionString2[20];
        CHAR16               StringBuffer[30];
        CHAR16               StringBuffer2[20];
        UINT32                IGDVersionOffsetPtr;
        CHAR8                *RomProductNamePtr=NULL;
        CHAR8                *IGDProductNamePtr=NULL;
        CHAR8                *IGDVersionNumberPtr=NULL;
        UINT8                Index = 0;
        UINT16                i = 0;


        EFI_LEGACY_BIOS_PLATFORM_PROTOCOL   *ELBPptr;
        EFI_HANDLE VgaHandle = NULL;
        EFI_HANDLE          *VgaHandlePtr = &VgaHandle;
        UINTN VgaHandleCount;

        EFI_PCI_IO_PROTOCOL *pciio;
        PCI_DEV_INFO        *dev;
        EFI_IA32_REGISTER_SET       Regs;
        GNB_VESA_BIOS_EXTENSIONS_INFORMATION_BLOCK  *VbeInformationBlock;     // 0x200 bytes.  Must be allocated below 1MB
        UINTN                                       NumberOfPagesBelow1MB;    // Number of 4KB pages in PagesBelow1MB
        EFI_PHYSICAL_ADDRESS                        PagesBelow1MB;            // Buffer for all VBE Information Blocks

        Status = gBS->LocateProtocol (&gEfiLegacyBiosProtocolGuid, NULL, (VOID **) &LegacyBios);
        if (!EFI_ERROR (Status)) {
          Status = gBS->LocateProtocol(&gEfiLegacyBiosPlatformProtocolGuid, NULL, &ELBPptr);
          if (EFI_ERROR (Status)) goto GopDriver;

          Status = ELBPptr->GetPlatformHandle(
                              ELBPptr,
                              EfiGetPlatformVgaHandle,
                              0,
                              &VgaHandlePtr,
                              &VgaHandleCount,
                              NULL);

          if (EFI_ERROR (Status))  goto GopDriver ;
          

           Status = gBS->HandleProtocol(*VgaHandlePtr, &gEfiPciIoProtocolGuid, &pciio);
           if (EFI_ERROR(Status))  goto GopDriver ;

           dev = (PCI_DEV_INFO*)pciio;

            if ( !((dev->Address.Addr.Device == IGD_DEV)
                          && (dev->Address.Addr.Function == IGD_FUN)))
             goto GopDriver ;  //Not IGD Vbios ,Skip

          //
          // Allocate buffer under 1MB for VBE data structures
          //
          NumberOfPagesBelow1MB = EFI_SIZE_TO_PAGES (
                                                      sizeof (GNB_VESA_BIOS_EXTENSIONS_INFORMATION_BLOCK) +
                                                      sizeof (VESA_BIOS_EXTENSIONS_MODE_INFORMATION_BLOCK) +
                                                      sizeof (VESA_BIOS_EXTENSIONS_EDID_DATA_BLOCK) +
                                                      sizeof (VESA_BIOS_EXTENSIONS_CRTC_INFORMATION_BLOCK)
                                                      );

          PagesBelow1MB = 0x00100000 - 1;

          Status = gBS->AllocatePages (
                          AllocateMaxAddress,
                          EfiBootServicesData,
                          NumberOfPagesBelow1MB,
                          &PagesBelow1MB
                          );
          if (EFI_ERROR (Status))  goto GopDriver ;

          VbeInformationBlock = (GNB_VESA_BIOS_EXTENSIONS_INFORMATION_BLOCK *) (UINTN) (PagesBelow1MB);

          //----------------------------------------------------------------------------
          //Function 00h - Return VBE Controller Information
          //Input: AX = 4F00h Return VBE Controller Information
          //ES:DI = Pointer to buffer in which to place VbeInfoBlock structure
          //                   (VbeSignature should be set to 'VBE2' when function is 
          //                   called to indicate VBE 3.0 information is desired and the 
          //                   information block is 512 bytes in size.)
          //                   
          //Output: AX = VBE Return Status
          //----------------------------------------------------------------------------

          gBS->SetMem (&Regs, sizeof (Regs), 0);
          Regs.X.AX = VESA_BIOS_EXTENSIONS_RETURN_CONTROLLER_INFORMATION;
          gBS->SetMem (VbeInformationBlock, sizeof (GNB_VESA_BIOS_EXTENSIONS_INFORMATION_BLOCK), 0);
          VbeInformationBlock->VESASignature  = VESA_BIOS_EXTENSIONS_VBE2_SIGNATURE;
          Regs.X.ES = EFI_SEGMENT (VbeInformationBlock);
          Regs.X.DI = EFI_OFFSET (VbeInformationBlock);

          LegacyBios->Int86 (LegacyBios, 0x10, &Regs);   //Call Int 10 (Function 00h - Return VBE Controller Information)

          if (Regs.X.AX == VESA_BIOS_EXTENSIONS_STATUS_SUCCESS) {

              RomProductNamePtr = (CHAR8 *) (((UINT32) (VbeInformationBlock->ProductName.ProductNameSeg) <<4) + \
                                                          (UINT32) (VbeInformationBlock->ProductName.ProductNameOffset));
              //
              // VBIOS info is at offset 0x6E , in 2 byte.
              // Format: 113-XXXXXX(Board SKU)-XXX(version) 
              //
              IGDVersionOffsetPtr =   *(UINT16*)(((UINT32)(VbeInformationBlock->ProductName.ProductNameSeg) <<4) + 0x6E);          
#if GNB_SHOW_FULL_VERSION
              IGDVersionNumberPtr = (CHAR8*)(((UINT32)(VbeInformationBlock->ProductName.ProductNameSeg) <<4) + IGDVersionOffsetPtr); 
#else
              // version name is at offset 11 byte
              IGDVersionNumberPtr = (CHAR8*)(((UINT32)(VbeInformationBlock->ProductName.ProductNameSeg) <<4) + IGDVersionOffsetPtr + 11);
#endif
              GnbAsciiToUnicode (IGDVersionNumberPtr,StringBuffer2);

              Swprintf(VersionString2, L"%s", StringBuffer2);

              // Try to find "Stoney generic VBIOS" name string.
              //
              // 1st name : STONEY
              // 2st name : PCI_EXPRESS
              // 3st name : DDR3
              // 4st name : STONEY GENERIC VBIOS
              
              for ( i=0 ; i<3 ; i++ ){
                  while ( RomProductNamePtr[Index] != 0) Index++; 
                  Index++; 
                  //Skip ASCII code 0x0D carriage return and 0x0A NL line feed, new line 
                  if ( RomProductNamePtr[Index] == 0x0D ) Index++;
                  if ( RomProductNamePtr[Index] == 0x0A ) Index++; 
              }
              
              IGDProductNamePtr = (CHAR8*)(&RomProductNamePtr[Index]); // IGD version name string

              GnbAsciiToUnicode (IGDProductNamePtr,StringBuffer);

              Swprintf(VersionString, L"%s", StringBuffer);

              InitString(HiiHandle, STRING_TOKEN(STR_VBIOS_VERSION), L"VBios Ver: %s %s",VersionString,VersionString2);
              return;
          } 
      }

GopDriver:
#endif //CSM_SUPPORT
       UpdateIGDGopVersion(HiiHandle);  //update Igd Gop version
*/
  } // end of CHIPSET_FORM_SET_CLASS
}


