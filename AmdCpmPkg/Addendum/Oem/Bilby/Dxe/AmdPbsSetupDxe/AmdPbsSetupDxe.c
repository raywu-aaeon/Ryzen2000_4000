/*****************************************************************************
 *
 * Copyright 2015 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 ******************************************************************************
 */

/** @file
The functions export data to the HII protocol to be later utilized by the
Setup Protocol
Copyright (c) 2004 - 2017, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available
under the terms and conditions of the BSD License which accompanies this
distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php
THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS, WITHOUT
WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
**/
#include <AmdCpmDxe.h>
#include "AmdPbsConfig.h"
#include "AmdPbsSetupDxe.h"
#include <Library/AmdPbsConfigLib/AmdPbsConfigLib.h>
#include <Library/PciExpressLib.h>
#include <Library/PcdLib.h>
#include <Library/AmdPspCommonLib.h>
#include <cpuRegisters.h>
#include <Protocol/ComponentName2.h>
#include <Library/DxeServicesLib.h>

CONST EFI_GUID  gZeroGuid = {0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0}};

EFI_STATUS
EFIAPI
LoadAmdPbsDefault (
  OUT AMD_PBS_SETUP_OPTION      *AmdPbsConfiguration
  );

//
// This is the generated IFR binary data for each formset defined in VFR.
// This data array is ready to be used as input of PreparePackageList() to
// create a packagelist (which contains Form packages, String packages, etc).
//

extern UINT8 AmdPbsHiiBin[];

//
// This is the generated String package data for all Unicode files.
// This data array is ready to be used as input of PreparePackageList() to
// create a packagelist (which contains Form packages, String packages, etc).
//

extern UINT8 AmdPbsSetupDxeStrings[];

//
// Global Variables.
//

EFI_GUID mFormSetGuid = AMD_PBS_SETUP_FORMSET_GUID;
EFI_GUID mPbsSetupGuid = AMD_PBS_SETUP_GUID;

HII_VENDOR_DEVICE_PATH mHiiVendorDevicePath0 = {
  {
    {
      HARDWARE_DEVICE_PATH,
      HW_VENDOR_DP,
      {
        (UINT8) (sizeof (VENDOR_DEVICE_PATH)),
        (UINT8) ((sizeof (VENDOR_DEVICE_PATH)) >> 8)
      }
    },
    AMD_PBS_SETUP_FORMSET_GUID
  },
  {
    END_DEVICE_PATH_TYPE,
    END_ENTIRE_DEVICE_PATH_SUBTYPE,
    {
      (UINT8) (END_DEVICE_PATH_LENGTH),
      (UINT8) ((END_DEVICE_PATH_LENGTH) >> 8)
    }
  }
};


UINTN
AmdCpmGetVbiosImage (
  )
{
  EFI_STATUS                                  Status;
  UINTN                                       HandleCount;
  EFI_HANDLE                                  *HandleBuffer;
  UINTN                                       Index;
  EFI_PCI_IO_PROTOCOL                         *PciIo;
  BOOLEAN                                     Found;
  UINTN                                       Seg;
  UINTN                                       Bus;
  UINTN                                       Dev;
  UINTN                                       Fnc;
  EFI_HANDLE                                  VgaHandle;
  UINT16                                      dGpVid;
  AMD_CPM_DISPLAY_FEATURE_PROTOCOL            *CpmDisplayFeatureProtocolPtr;
  CPM_DISPLAY_FEATURE_PRIVATE                 *DisplayFeatureDataPtr;
  UINTN                                       VBiosImage;
  UINTN                                       VBiosImageSize;

  dGpVid = 0;
  Found = FALSE;
  PciIo = NULL;
  Seg = 0x00;
  Bus = 0x00;
  Dev = 0x00;
  Fnc = 0x00;
  VgaHandle = NULL;
  VBiosImage = 0;
  VBiosImageSize = 0;

  Status = gBS->LocateProtocol ( &gAmdCpmDisplayFeatureProtocolGuid,
                                 NULL,
                                 (VOID**)&CpmDisplayFeatureProtocolPtr );
  ASSERT_EFI_ERROR (Status);

  DisplayFeatureDataPtr   = &CpmDisplayFeatureProtocolPtr->DisplayFeatureData;

  //
  // A. Search Int or Ext GFX bridge and then get the SubBus information from this bridge
  //

  //  Step 01.
  //  Search handles that support the gEfiPciIoProtocolGuid protocol
  //  gBS->LocateHandleBuffer returns an array of handles.

  Status = gBS->LocateHandleBuffer ( ByProtocol,
                                     &gEfiPciIoProtocolGuid,
                                     NULL,
                                     &HandleCount,
                                     &HandleBuffer );
  ASSERT_EFI_ERROR (Status);

  //
  //B. Search iGPU / dGPU device under bridge
  //

  for (Index = 0; (Index < HandleCount) && (Found == FALSE); Index++) {
    Status = gBS->HandleProtocol ( HandleBuffer[Index],
                                   &gEfiPciIoProtocolGuid,
                                   (VOID**)&PciIo );
    if (EFI_ERROR (Status)) {
      continue;
    }

    //
    // Step 01.
    // See if this is a PCI Graphics Controller by looking at Class Code Register
    //
    PciIo->GetLocation ( PciIo, &Seg, &Bus, &Dev, &Fnc );

    if (((UINTN)Bus == DisplayFeatureDataPtr->GfxDevicePfa[0].Pfa.Bus) &&
        ((UINTN)Dev == DisplayFeatureDataPtr->GfxDevicePfa[0].Pfa.Device) &&
        ((UINTN)Fnc == DisplayFeatureDataPtr->GfxDevicePfa[0].Pfa.Function)) {

      Status = PciIo->Pci.Read ( PciIo,
                                 EfiPciIoWidthUint16,
                                 PCI_VENDOR_ID_OFFSET,        // Start offset: 0x00
                                 1,                           // Length of bytes
                                 &dGpVid );

      if (dGpVid != 0xFFFF) {
        VgaHandle      = HandleBuffer[Index];
        VBiosImage     = (UINTN) PciIo->RomImage;
        VBiosImageSize = (UINTN) PciIo->RomSize;
      }
      Found = TRUE;
    }
  }

  return VBiosImage;
}


CHAR16 *
AmdCpmGetGopDriverRev (
     OUT BOOLEAN                *Found
  )
{
  EFI_STATUS                    Status;
  EFI_HANDLE                    *HandleBuffer;
  EFI_COMPONENT_NAME2_PROTOCOL  *ComponentName;
  CHAR16                        *DriverName;
  UINTN                         HandleCount;
  UINTN                         Index;

  ComponentName = NULL;
  DriverName = NULL;
  HandleCount = 0;
  *Found = FALSE;

  Status = gBS->LocateHandleBuffer ( ByProtocol,
                                     &gEfiDriverBindingProtocolGuid,
                                     NULL,
                                     &HandleCount,
                                     &HandleBuffer );
  if (!EFI_ERROR (Status)) {
    for (Index = 0; Index < HandleCount; Index++) {
      Status = gBS->OpenProtocol ( HandleBuffer[Index],
                                   &gEfiComponentName2ProtocolGuid,
                                   (VOID **) &ComponentName,
                                   gImageHandle,
                                   NULL,
                                   EFI_OPEN_PROTOCOL_GET_PROTOCOL );
      if (!EFI_ERROR (Status)) {
        Status = ComponentName->GetDriverName ( ComponentName,
                                                ComponentName->SupportedLanguages,
                                                &DriverName );
        gBS->CloseProtocol ( HandleBuffer[Index],
                             &gEfiComponentName2ProtocolGuid,
                             gImageHandle,
                             HandleBuffer[Index] );
        if (!EFI_ERROR (Status) && !StrnCmp (DriverName, L"AMD GOP ", 8)) {
          *Found = TRUE;
          break;
        }
      }
    }
  }

  if (HandleCount) {
    gBS->FreePool (HandleBuffer);
  }

  return DriverName;
}


CHAR16 *
AmdCpmGetGopDriverRevFromFv (
  IN     EFI_GUID               *GopDriverFileGuid,
     OUT BOOLEAN                *Found
  )
{
  EFI_STATUS                    Status;
  CHAR16                        *DriverName;
  CHAR16                        *CodeData;
  UINTN                         Index;
  VOID                          *LocalRomImage;
  EFI_IMAGE_DOS_HEADER          *ImageDosHdr;
  EFI_IMAGE_NT_HEADERS64        *ImageNt64Hdr;
  UINT32                        CodeSize;

  DriverName = NULL;
  *Found = FALSE;
  LocalRomImage = NULL;
  ImageDosHdr = NULL;
  ImageNt64Hdr = NULL;

  Status = GetSectionFromFv (GopDriverFileGuid, EFI_SECTION_PE32, 0, &LocalRomImage, &Index);
  if (EFI_ERROR (Status)) {
    return DriverName;
  }
  ImageDosHdr = (EFI_IMAGE_DOS_HEADER *)LocalRomImage;

  if (ImageDosHdr->e_magic != EFI_IMAGE_DOS_SIGNATURE) {
    return DriverName;
  }

  ImageNt64Hdr = (EFI_IMAGE_NT_HEADERS64 *)(((CHAR8 *)ImageDosHdr) + ImageDosHdr->e_lfanew);

  CodeData = (CHAR16 *)(((CHAR8 *)ImageDosHdr) + ImageNt64Hdr->OptionalHeader.BaseOfCode);
  CodeSize = ImageNt64Hdr->OptionalHeader.AddressOfEntryPoint - ImageNt64Hdr->OptionalHeader.BaseOfCode;
  for (Index = 0; Index < CodeSize; Index += 0x10) {
    CodeData = (CHAR16 *)(((CHAR8 *)ImageDosHdr) + ImageNt64Hdr->OptionalHeader.BaseOfCode + Index);
    if (StrnCmp(L"AMD GOP ", CodeData, 8) == 0) {
      DriverName = CodeData;
      *Found = TRUE;
      break;
    }
  }

  return DriverName;
}


//
// Update all of AMD FW Version information in VFR.
//
VOID
UpdateAmdFwVersionInfo (
  IN  EFI_HII_HANDLE                    HiiHandle
  )
{
  EFI_STRING_ID                         VfrTokenToUpdate;
  CHAR16                                *FwVersionValue;
  CHAR16                                *TmpFwVersionValue;
  CHAR16                                *FwStringBuffer;
  UINTN                                 FwVersionStringOffset;
  UINT64                                mFwVersionRegionBase;
  UINT32                                mFwVersionRegionSize;
  UINT8                                 *FwVersionPtr;
 // UINT32                                Data32;
  UINT8                                 Data8;
  UINT8                                 Index;
  BOOLEAN                               Found;

  FwVersionValue = AllocateZeroPool (0x80);
  FwStringBuffer = AllocateZeroPool (0x20);

  // AGESA Version
  FwVersionPtr = (UINT8 *)PcdGetPtr (PcdAmdPackageString);
  FwVersionStringOffset = AsciiStrSize (FwVersionPtr);
  for (Index = 0; Index < AsciiStrSize (FwVersionPtr + FwVersionStringOffset); Index++) {
    Data8 = *(FwVersionPtr + FwVersionStringOffset + Index);
    FwStringBuffer[0] = (CHAR16)Data8;
    StrCat (FwVersionValue, FwStringBuffer);
  }
  VfrTokenToUpdate = STRING_TOKEN (STR_AMD_PBS_FWVER_AGESA_VALUE);
  HiiSetString (HiiHandle, VfrTokenToUpdate, FwVersionValue, NULL);

  // PSP BootLoader Version
  ZeroMem (FwVersionValue, 0x40);
  ZeroMem (FwStringBuffer, 0x20);
  Found = PSPEntryInfo (  PSP_FW_BOOT_LOADER,
                          &mFwVersionRegionBase,
                          &mFwVersionRegionSize );
  if (Found) {
    FwVersionStringOffset = 0x60;
    FwVersionPtr = (UINT8 *)(mFwVersionRegionBase + FwVersionStringOffset);
    UnicodeValueToString (FwStringBuffer, (PREFIX_ZERO + RADIX_HEX), *(FwVersionPtr + 3), 0);
    StrCat (FwVersionValue, FwStringBuffer);
    StrCat (FwVersionValue, L".");
    UnicodeValueToString (FwStringBuffer, (PREFIX_ZERO + RADIX_HEX), *(FwVersionPtr + 2), 0);
    StrCat (FwVersionValue, FwStringBuffer);
    StrCat (FwVersionValue, L".");
    UnicodeValueToString (FwStringBuffer, (PREFIX_ZERO + RADIX_HEX), *(FwVersionPtr + 1), 0);
    StrCat (FwVersionValue, FwStringBuffer);
    StrCat (FwVersionValue, L".");
    UnicodeValueToString (FwStringBuffer, (PREFIX_ZERO + RADIX_HEX), *(FwVersionPtr), 0);
    StrCat (FwVersionValue, FwStringBuffer);
    VfrTokenToUpdate = STRING_TOKEN (STR_AMD_PBS_FWVER_PSP_BOOT_LOADER_VALUE);
    HiiSetString (HiiHandle, VfrTokenToUpdate, FwVersionValue, NULL);
  }

  // PSP SecureOS Version
  ZeroMem (FwVersionValue, 0x40);
  ZeroMem (FwStringBuffer, 0x20);
  Found = PSPEntryInfo (  PSP_FW_TRUSTED_OS,
                          &mFwVersionRegionBase,
                          &mFwVersionRegionSize );
  if (Found) {
    FwVersionStringOffset = 0x60;
    FwVersionPtr = (UINT8 *)(mFwVersionRegionBase + FwVersionStringOffset);
    UnicodeValueToString (FwStringBuffer, (PREFIX_ZERO + RADIX_HEX), *(FwVersionPtr + 3), 0);
    StrCat (FwVersionValue, FwStringBuffer);
    StrCat (FwVersionValue, L".");
    UnicodeValueToString (FwStringBuffer, (PREFIX_ZERO + RADIX_HEX), *(FwVersionPtr + 2), 0);
    StrCat (FwVersionValue, FwStringBuffer);
    StrCat (FwVersionValue, L".");
    UnicodeValueToString (FwStringBuffer, (PREFIX_ZERO + RADIX_HEX), *(FwVersionPtr + 1), 0);
    StrCat (FwVersionValue, FwStringBuffer);
    StrCat (FwVersionValue, L".");
    UnicodeValueToString (FwStringBuffer, (PREFIX_ZERO + RADIX_HEX), *FwVersionPtr, 0);
    StrCat (FwVersionValue, FwStringBuffer);
    VfrTokenToUpdate = STRING_TOKEN (STR_AMD_PBS_FWVER_PSP_TRUSTED_OS_VALUE);
    HiiSetString (HiiHandle, VfrTokenToUpdate, FwVersionValue, NULL);
  }

  // ABL Version
  ZeroMem (FwVersionValue, 0x40);
  ZeroMem (FwStringBuffer, 0x20);
  Found = PSPEntryInfo (  AGESA_BOOT_LOADER_0,
                          &mFwVersionRegionBase,
                          &mFwVersionRegionSize );
  if (Found) {
    FwVersionStringOffset = 0x60;
    FwVersionPtr = (UINT8 *)(mFwVersionRegionBase + FwVersionStringOffset);
    UnicodeValueToString (FwStringBuffer, (PREFIX_ZERO + RADIX_HEX), *(FwVersionPtr + 3), 2);
    StrCat (FwVersionValue, FwStringBuffer);
    UnicodeValueToString (FwStringBuffer, (PREFIX_ZERO + RADIX_HEX), *(FwVersionPtr + 2), 2);
    StrCat (FwVersionValue, FwStringBuffer);
    UnicodeValueToString (FwStringBuffer, (PREFIX_ZERO + RADIX_HEX), *(FwVersionPtr + 1), 2);
    StrCat (FwVersionValue, FwStringBuffer);
    UnicodeValueToString (FwStringBuffer, (PREFIX_ZERO + RADIX_HEX), *FwVersionPtr, 2);
    StrCat (FwVersionValue, FwStringBuffer);
    VfrTokenToUpdate = STRING_TOKEN (STR_AMD_PBS_FWVER_ABL_VALUE);
    HiiSetString (HiiHandle, VfrTokenToUpdate, FwVersionValue, NULL);
  }

  // APCB Version
  ZeroMem (FwVersionValue, 0x40);
  ZeroMem (FwStringBuffer, 0x20);
  FwVersionStringOffset = 0xA0;
  FwVersionPtr = (UINT8 *)(mFwVersionRegionBase + FwVersionStringOffset);
  UnicodeValueToString (FwStringBuffer, (PREFIX_ZERO + RADIX_HEX), *(FwVersionPtr + 1), 2);
  StrCat (FwVersionValue, FwStringBuffer);
  UnicodeValueToString (FwStringBuffer, (PREFIX_ZERO + RADIX_HEX), *FwVersionPtr, 2);
  StrCat (FwVersionValue, FwStringBuffer);
  VfrTokenToUpdate = STRING_TOKEN (STR_AMD_PBS_FWVER_APCB_VALUE);
  HiiSetString (HiiHandle, VfrTokenToUpdate, FwVersionValue, NULL);

  // APOB Version
  ZeroMem (FwVersionValue, 0x40);
  ZeroMem (FwStringBuffer, 0x20);
  FwVersionStringOffset = 0xA4;
  FwVersionPtr = (UINT8 *)(mFwVersionRegionBase + FwVersionStringOffset);
  UnicodeValueToString (FwStringBuffer, (PREFIX_ZERO + RADIX_HEX), *(FwVersionPtr+1), 2);
  StrCat (FwVersionValue, FwStringBuffer);
  UnicodeValueToString (FwStringBuffer, (PREFIX_ZERO + RADIX_HEX), *FwVersionPtr, 2);
  StrCat (FwVersionValue, FwStringBuffer);
  VfrTokenToUpdate = STRING_TOKEN (STR_AMD_PBS_FWVER_APOB_VALUE);
  HiiSetString (HiiHandle, VfrTokenToUpdate, FwVersionValue, NULL);

  // UCODE Patch Version
  ZeroMem (FwVersionValue, 0x40);
  mFwVersionRegionBase = AsmReadMsr64(MSR_PATCH_LEVEL);
  UnicodeValueToString (FwVersionValue, (PREFIX_ZERO + RADIX_HEX), mFwVersionRegionBase, 0);
  VfrTokenToUpdate = STRING_TOKEN (STR_AMD_PBS_FWVER_UCODE_VALUE);
  HiiSetString (HiiHandle, VfrTokenToUpdate, FwVersionValue, NULL);

  // SMU FW Version
  ZeroMem (FwVersionValue, 0x40);
  ZeroMem (FwStringBuffer, 0x20);
  FwVersionStringOffset = 0x00;
  Found = PSPEntryInfo (  SMU_OFFCHIP_FW + 0x200,
                          &mFwVersionRegionBase,
                          &mFwVersionRegionSize );
  if (Found) {
    FwVersionPtr = (UINT8 *)(mFwVersionRegionBase + FwVersionStringOffset);
    UnicodeValueToString (FwStringBuffer, PREFIX_ZERO, *(FwVersionPtr + 3), 0);
    StrCat (FwVersionValue, FwStringBuffer);
    StrCat (FwVersionValue, L".");
    UnicodeValueToString (FwStringBuffer, PREFIX_ZERO, *(FwVersionPtr + 2), 0);
    StrCat (FwVersionValue, FwStringBuffer);
    StrCat (FwVersionValue, L".");
    UnicodeValueToString (FwStringBuffer, PREFIX_ZERO, *(FwVersionPtr + 1), 0);
    StrCat (FwVersionValue, FwStringBuffer);
    StrCat (FwVersionValue, L".");
    UnicodeValueToString (FwStringBuffer, PREFIX_ZERO, *FwVersionPtr, 0);
    StrCat (FwVersionValue, FwStringBuffer);
    VfrTokenToUpdate = STRING_TOKEN (STR_AMD_PBS_FWVER_SMU_VALUE);
    HiiSetString (HiiHandle, VfrTokenToUpdate, FwVersionValue, NULL);
  }
  
  // SMU RV2 FW Version
  ZeroMem (FwVersionValue, 0x40);
  ZeroMem (FwStringBuffer, 0x20);
  FwVersionStringOffset = 0x00;
  Found = PSPEntryInfo (  SMU_OFFCHIP_FW + 0x100,
                          &mFwVersionRegionBase,
                          &mFwVersionRegionSize );
  if (Found) {
    FwVersionPtr = (UINT8 *)(mFwVersionRegionBase + FwVersionStringOffset);
    UnicodeValueToString (FwStringBuffer, PREFIX_ZERO, *(FwVersionPtr + 3), 0);
    StrCat (FwVersionValue, FwStringBuffer);
    StrCat (FwVersionValue, L".");
    UnicodeValueToString (FwStringBuffer, PREFIX_ZERO, *(FwVersionPtr + 2), 0);
    StrCat (FwVersionValue, FwStringBuffer);
    StrCat (FwVersionValue, L".");
    UnicodeValueToString (FwStringBuffer, PREFIX_ZERO, *(FwVersionPtr + 1), 0);
    StrCat (FwVersionValue, FwStringBuffer);
    StrCat (FwVersionValue, L".");
    UnicodeValueToString (FwStringBuffer, PREFIX_ZERO, *FwVersionPtr, 0);
    StrCat (FwVersionValue, FwStringBuffer);
    VfrTokenToUpdate = STRING_TOKEN (STR_AMD_PBS_FWVER_SMU_RV2_VALUE);
    HiiSetString (HiiHandle, VfrTokenToUpdate, FwVersionValue, NULL);
  }

  // DXIO FW Version
  ZeroMem (FwVersionValue, 0x40);
  ZeroMem (FwStringBuffer, 0x20);
  mFwVersionRegionSize = PcdGet32 (PcdDxioMajorRevision);
  UnicodeValueToString (FwStringBuffer, (PREFIX_ZERO + RADIX_HEX), mFwVersionRegionSize, 4);
  StrCat (FwVersionValue, FwStringBuffer);
  StrCat (FwVersionValue, L".");
  mFwVersionRegionSize = PcdGet32 (PcdDxioMinorRevision);
  UnicodeValueToString (FwStringBuffer, (PREFIX_ZERO + RADIX_HEX), mFwVersionRegionSize, 4);
  StrCat (FwVersionValue, FwStringBuffer);
  VfrTokenToUpdate = STRING_TOKEN (STR_AMD_PBS_FWVER_DXIO_VALUE);
  HiiSetString (HiiHandle, VfrTokenToUpdate, FwVersionValue, NULL);
  
  // MP2 FW Version
  ZeroMem (FwVersionValue, 0x40);
  ZeroMem (FwStringBuffer, 0x20);
  FwVersionStringOffset = 0x60;
  Found = PSPEntryInfo (  0x225,
                          &mFwVersionRegionBase,
                          &mFwVersionRegionSize );
  if (Found) {
    FwVersionPtr = (UINT8 *)(mFwVersionRegionBase + FwVersionStringOffset);
    UnicodeValueToString (FwStringBuffer, PREFIX_ZERO, *(FwVersionPtr + 0), 0);
    StrCat (FwVersionValue, FwStringBuffer);
    StrCat (FwVersionValue, L".");
    UnicodeValueToString (FwStringBuffer, PREFIX_ZERO, *(FwVersionPtr + 1), 0);
    StrCat (FwVersionValue, FwStringBuffer);
    StrCat (FwVersionValue, L".");
    UnicodeValueToString (FwStringBuffer, PREFIX_ZERO, *(FwVersionPtr + 2), 0);
    StrCat (FwVersionValue, FwStringBuffer);
    StrCat (FwVersionValue, L".");
    UnicodeValueToString (FwStringBuffer, PREFIX_ZERO, *(FwVersionPtr + 3), 0);
    StrCat (FwVersionValue, FwStringBuffer);    
    VfrTokenToUpdate = STRING_TOKEN (STR_AMD_PBS_FWVER_MP2_VALUE);
    HiiSetString (HiiHandle, VfrTokenToUpdate, FwVersionValue, NULL);
  }

  // MP2 RV2 FW Version
  ZeroMem (FwVersionValue, 0x40);
  ZeroMem (FwStringBuffer, 0x20);
  FwVersionStringOffset = 0x60;
  Found = PSPEntryInfo (  0x125,
                          &mFwVersionRegionBase,
                          &mFwVersionRegionSize );
  if (Found) {
    FwVersionPtr = (UINT8 *)(mFwVersionRegionBase + FwVersionStringOffset);
    UnicodeValueToString (FwStringBuffer, PREFIX_ZERO, *(FwVersionPtr + 3), 0);
    StrCat (FwVersionValue, FwStringBuffer);
    StrCat (FwVersionValue, L".");
    UnicodeValueToString (FwStringBuffer, PREFIX_ZERO, *(FwVersionPtr + 2), 0);
    StrCat (FwVersionValue, FwStringBuffer);
    StrCat (FwVersionValue, L".");
    UnicodeValueToString (FwStringBuffer, PREFIX_ZERO, *(FwVersionPtr + 1), 0);
    StrCat (FwVersionValue, FwStringBuffer);
    StrCat (FwVersionValue, L".");
    UnicodeValueToString (FwStringBuffer, PREFIX_ZERO, *(FwVersionPtr), 0);
    StrCat (FwVersionValue, FwStringBuffer);
    VfrTokenToUpdate = STRING_TOKEN (STR_AMD_PBS_FWVER_MP2_RV2_VALUE);
    HiiSetString (HiiHandle, VfrTokenToUpdate, FwVersionValue, NULL);
  }      

  // XHCI FW Version
  ZeroMem (FwVersionValue, 0x40);
  ZeroMem (FwStringBuffer, 0x20);
  FwVersionStringOffset = 0x8000;
  mFwVersionRegionBase = (UINT64) (PcdGet32(PcdAmdXhciFwLocation) + FwVersionStringOffset);

  FwVersionStringOffset = 0x0E;
  FwVersionPtr = (UINT8 *)(mFwVersionRegionBase + FwVersionStringOffset);
  FwVersionPtr = (UINT8 *)(UINTN)(*(UINT16 *)FwVersionPtr + mFwVersionRegionBase);

  UnicodeValueToString (FwStringBuffer, (PREFIX_ZERO + RADIX_HEX), *FwVersionPtr, 0);
  StrCat (FwVersionValue, FwStringBuffer);
  StrCat (FwVersionValue, L".");
  UnicodeValueToString (FwStringBuffer, (PREFIX_ZERO + RADIX_HEX), *(FwVersionPtr + 1), 0);
  StrCat (FwVersionValue, FwStringBuffer);
  StrCat (FwVersionValue, L".");
  UnicodeValueToString (FwStringBuffer, (PREFIX_ZERO + RADIX_HEX), *(FwVersionPtr + 2), 0);
  StrCat (FwVersionValue, FwStringBuffer);
  StrCat (FwVersionValue, L".");
  UnicodeValueToString (FwStringBuffer, (PREFIX_ZERO + RADIX_HEX), *(FwVersionPtr + 3), 0);
  StrCat (FwVersionValue, FwStringBuffer);
  VfrTokenToUpdate = STRING_TOKEN (STR_AMD_PBS_FWVER_XHCI_VALUE);
  HiiSetString (HiiHandle, VfrTokenToUpdate, FwVersionValue, NULL);

  // VBIOS FW Version
  mFwVersionRegionBase = (UINT64)AmdCpmGetVbiosImage();
  if (mFwVersionRegionBase != 0) {
    if (*(UINT16 *)mFwVersionRegionBase == 0xAA55) {
      ZeroMem (FwVersionValue, 0x40);
      ZeroMem (FwStringBuffer, 0x20);
      FwVersionStringOffset = 0x70;
      mFwVersionRegionSize = 0;
      for (Index = 0; Index < 15; Index++) {
        Data8 = *(UINT8 *)((mFwVersionRegionBase + FwVersionStringOffset) + Index);
        if (((Data8 >= 0x30) && (Data8 <= 0x39)) || ((Data8 >= 0x41) && (Data8 <= 0x5A)) || (Data8 == 0x2D)) {
          FwStringBuffer[0] = (CHAR16)Data8;
          StrCat (FwVersionValue, FwStringBuffer);
        }
      }
      VfrTokenToUpdate = STRING_TOKEN (STR_AMD_PBS_FWVER_VBIOS_VALUE);
      HiiSetString (HiiHandle, VfrTokenToUpdate, FwVersionValue, NULL);
    }
  }

  // GOP Driver Version
  ZeroMem (FwVersionValue, 0x80);
  if ((EFI_GUID *)PcdGetPtr(PcdGopDriverFile) == NULL || CompareGuid ((EFI_GUID *)PcdGetPtr(PcdGopDriverFile), &gZeroGuid)) {
    TmpFwVersionValue = AmdCpmGetGopDriverRev(&Found);
  } else {
    TmpFwVersionValue = AmdCpmGetGopDriverRevFromFv((EFI_GUID *)PcdGetPtr(PcdGopDriverFile), &Found);
  }
  if (Found && (TmpFwVersionValue != NULL)) {
    StrCpy(FwVersionValue, TmpFwVersionValue);
    VfrTokenToUpdate = STRING_TOKEN (STR_AMD_PBS_FWVER_GOP_VALUE);
    HiiSetString (HiiHandle, VfrTokenToUpdate, FwVersionValue, NULL);
  }
#if 0
  // EC FW Version
  ZeroMem (FwVersionValue, 0x40);
  mFwVersionRegionSize = 0;
  Data32 = PcdGet32 (PcdECFwVersion);
  for (Index = 0; Index < 4; Index++) {
    Data8 = (UINT8)(Data32 >> ( 8 * ( 3 - Index )));
    if ( Data8 >= 0x30 ) {
      mFwVersionRegionSize |= (UINT32)( Data8 - 0x30 ) << ( 4 * (3 - Index));
    }
  }
  UnicodeValueToString (FwVersionValue, (PREFIX_ZERO + RADIX_HEX), mFwVersionRegionSize, 4);
  VfrTokenToUpdate = STRING_TOKEN (STR_AMD_PBS_FWVER_EC_VALUE);
  HiiSetString (HiiHandle, VfrTokenToUpdate, FwVersionValue, NULL);

  // USB PD 1 FW Version
  ZeroMem (FwVersionValue, 0x40);
  mFwVersionRegionSize = (UINT32) PcdGet16 (PcdUSBPDFwSection1Version);
  UnicodeValueToString (FwVersionValue, (PREFIX_ZERO + RADIX_HEX), mFwVersionRegionSize, 4);
  VfrTokenToUpdate = STRING_TOKEN (STR_AMD_PBS_FWVER_USB_PD1_VALUE);
  HiiSetString (HiiHandle, VfrTokenToUpdate, FwVersionValue, NULL);

  // USB PD 2 FW Version
  ZeroMem (FwVersionValue, 0x40);
  mFwVersionRegionSize = (UINT32) PcdGet16 (PcdUSBPDFwSection2Version);
  UnicodeValueToString (FwVersionValue, (PREFIX_ZERO + RADIX_HEX), mFwVersionRegionSize, 4);
  VfrTokenToUpdate = STRING_TOKEN (STR_AMD_PBS_FWVER_USB_PD2_VALUE);
  HiiSetString (HiiHandle, VfrTokenToUpdate, FwVersionValue, NULL);
#endif

  gBS->FreePool (FwVersionValue);
  gBS->FreePool (FwStringBuffer);
  return;
}


VOID
AmdPbsBrowserActionChangedByQuestionId (
  IN EFI_QUESTION_ID QuestionId
  )
{
  EFI_STATUS           Status;
  INTN                VarSize;
  AMD_PBS_SETUP_OPTION AmdPbsSetupConfig;
  

  switch (QuestionId) {
  
    case KEY_XGBE_PORT_PHY_SWITCH:
    VarSize = sizeof (AMD_PBS_SETUP_OPTION);
  
    Status = HiiGetBrowserData (
                 &gAmdPbsSystemConfigurationGuid,
                 (CHAR16 *) AMD_PBS_SETUP_VARIABLE_NAME,
                 VarSize,
                 (UINT8 *) &AmdPbsSetupConfig);
    if(AmdPbsSetupConfig.XgbePortPhySwitch == 2){
      AmdPbsSetupConfig.PxeBoot = 0;		
      Status = HiiSetBrowserData (
                 &gAmdPbsSystemConfigurationGuid,
                 (CHAR16 *) AMD_PBS_SETUP_VARIABLE_NAME,
                 VarSize,
                 (UINT8 *) &AmdPbsSetupConfig,
                 NULL);
    }
    break;
  
#if 0 // we have always have x4 only in Dibbler hence we don't need this check
    case KEY_REDUCE_HARDWARE_SETTING:
    VarSize = sizeof (AMD_PBS_SETUP_OPTION);
    Status = HiiGetBrowserData (
               &gAmdPbsSystemConfigurationGuid,
               (CHAR16 *) AMD_PBS_SETUP_VARIABLE_NAME,
               VarSize,
               (UINT8 *) &AmdPbsSetupConfig);
    if (AmdPbsSetupConfig.ReduceHardwareEn == 1) {
      if (AmdPbsSetupConfig.WakeOnPME != 0) {
	  	AmdPbsSetupConfig.WakeOnPME = 0;
        Status = HiiSetBrowserData (
                   &gAmdPbsSystemConfigurationGuid,
                   (CHAR16 *) AMD_PBS_SETUP_VARIABLE_NAME,
                   VarSize,
                   (UINT8 *) &AmdPbsSetupConfig,
                   NULL);
      }
    } else if (AmdPbsSetupConfig.ReduceHardwareEn == 0) {
      if (AmdPbsSetupConfig.WakeOnPME != 1) {
        AmdPbsSetupConfig.WakeOnPME = 1;
        Status = HiiSetBrowserData (
                   &gAmdPbsSystemConfigurationGuid,
                   (CHAR16 *) AMD_PBS_SETUP_VARIABLE_NAME,
                   VarSize,
                   (UINT8 *) &AmdPbsSetupConfig,
                   NULL);
      }
    }
    break;

    case KEY_SPECIAL_VGA_FEATURE_SETTING:
    VarSize = sizeof (AMD_PBS_SETUP_OPTION);
    Status = HiiGetBrowserData (
               &gAmdPbsSystemConfigurationGuid,
               (CHAR16 *) AMD_PBS_SETUP_VARIABLE_NAME,
               VarSize,
               (UINT8 *) &AmdPbsSetupConfig);
    if (AmdPbsSetupConfig.SpecialVgaFeature != 0) {
      AmdPbsSetupConfig.D3ColdSupport = 1;
      Status = HiiSetBrowserData (
                 &gAmdPbsSystemConfigurationGuid,
                 (CHAR16 *) AMD_PBS_SETUP_VARIABLE_NAME,
                 VarSize,
                 (UINT8 *) &AmdPbsSetupConfig,
                 NULL);
    }
    break;

    case KEY_DT_HOTPLUG_SETTING:
    VarSize = sizeof (AMD_PBS_SETUP_OPTION);
    Status = HiiGetBrowserData (
               &gAmdPbsSystemConfigurationGuid,
               (CHAR16 *) AMD_PBS_SETUP_VARIABLE_NAME,
               VarSize,
               (UINT8 *) &AmdPbsSetupConfig);
    if (AmdPbsSetupConfig.DtHotPlugEnable == 1) {
      AmdPbsSetupConfig.DtSlotPowerControl = 3;
      AmdPbsSetupConfig.WlanPowerControl = 0;
      Status = HiiSetBrowserData (
                 &gAmdPbsSystemConfigurationGuid,
                 (CHAR16 *) AMD_PBS_SETUP_VARIABLE_NAME,
                 VarSize,
                 (UINT8 *) &AmdPbsSetupConfig,
                 NULL);
    }
    break;

    case KEY_DT_SLOT_SETTING:
    VarSize = sizeof (AMD_PBS_SETUP_OPTION);
    Status = HiiGetBrowserData (
               &gAmdPbsSystemConfigurationGuid,
               (CHAR16 *) AMD_PBS_SETUP_VARIABLE_NAME,
               VarSize,
               (UINT8 *) &AmdPbsSetupConfig);
    //
    // Update WlanPowerControl, WwanPowerEn, LanPowerControl by DtSlotPowerControl vlaue and platformId.
    //
    if (AmdPbsSetupConfig.DtSlotPowerControl > 0) {
      AmdPbsSetupConfig.WlanPowerControl = 0;
      if ((AmdPbsSetupConfig.PlatformId == 0) && (AmdPbsSetupConfig.DtSlotPowerControl == 1)) {
        // PlatformId is Mandloin and DtSlotPowerControl is Enabled (x4)
        AmdPbsSetupConfig.WwanPowerEn = 0;
      }
      if (AmdPbsSetupConfig.DtSlotPowerControl != 3) {
        // DtSlotPowerControl is Enabled (x4) or Enabled (x2)
        AmdPbsSetupConfig.LanPowerControl = 0;
        AmdPbsSetupConfig.LanLowPowerMode = 0;
      } else {
        // DtSlotPowerControl is Enabled (x1)
        AmdPbsSetupConfig.LanPowerControl = 1;
      }
      Status = HiiSetBrowserData (
                 &gAmdPbsSystemConfigurationGuid,
                 (CHAR16 *) AMD_PBS_SETUP_VARIABLE_NAME,
                 VarSize,
                 (UINT8 *) &AmdPbsSetupConfig,
                 NULL);
    }
    break;

    case KEY_DGPU_MACO_SETTING:
    VarSize = sizeof (AMD_PBS_SETUP_OPTION);
    Status = HiiGetBrowserData (
               &gAmdPbsSystemConfigurationGuid,
               (CHAR16 *) AMD_PBS_SETUP_VARIABLE_NAME,
               VarSize,
               (UINT8 *) &AmdPbsSetupConfig);
    if (AmdPbsSetupConfig.DgpuMaco == 1) {
      AmdPbsSetupConfig.AmdBlinkLed = 2;
      Status = HiiSetBrowserData (
                 &gAmdPbsSystemConfigurationGuid,
                 (CHAR16 *) AMD_PBS_SETUP_VARIABLE_NAME,
                 VarSize,
                 (UINT8 *) &AmdPbsSetupConfig,
                 NULL);
    }
    break;

    case KEY_SATA_SSD_SETTING:
    VarSize = sizeof (AMD_PBS_SETUP_OPTION);
    Status = HiiGetBrowserData (
               &gAmdPbsSystemConfigurationGuid,
               (CHAR16 *) AMD_PBS_SETUP_VARIABLE_NAME,
               VarSize,
               (UINT8 *) &AmdPbsSetupConfig);
    if (AmdPbsSetupConfig.SataPortSsdPowerEn == 2) {
      AmdPbsSetupConfig.SataPort0HddPowerEn = 0;
      AmdPbsSetupConfig.SataPort1OddPowerEn = 0;
      AmdPbsSetupConfig.ZeroPowerOddEn = 0;
      Status = HiiSetBrowserData (
                 &gAmdPbsSystemConfigurationGuid,
                 (CHAR16 *) AMD_PBS_SETUP_VARIABLE_NAME,
                 VarSize,
                 (UINT8 *) &AmdPbsSetupConfig,
                 NULL);
    }
    break;

    case KEY_ODD_POWER_SETTING:
    VarSize = sizeof (AMD_PBS_SETUP_OPTION);
    Status = HiiGetBrowserData (
               &gAmdPbsSystemConfigurationGuid,
               (CHAR16 *) AMD_PBS_SETUP_VARIABLE_NAME,
               VarSize,
               (UINT8 *) &AmdPbsSetupConfig);
    if (AmdPbsSetupConfig.SataPort1OddPowerEn == 0) {
      AmdPbsSetupConfig.ZeroPowerOddEn = 0;
      Status = HiiSetBrowserData (
                 &gAmdPbsSystemConfigurationGuid,
                 (CHAR16 *) AMD_PBS_SETUP_VARIABLE_NAME,
                 VarSize,
                 (UINT8 *) &AmdPbsSetupConfig,
                 NULL);
    }
    break;
#endif
    default:
    break;
  }
}


EFI_STATUS
EFIAPI
AmdPbsExtractConfig (
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN CONST EFI_STRING Request,
  OUT EFI_STRING *Progress,
  OUT EFI_STRING *Results
  )
{
  EFI_STATUS                       Status;
  UINTN                            BufferSize;
  AMD_PBS_DXE_PRIVATE_DATA         *Private;
  EFI_HII_CONFIG_ROUTING_PROTOCOL  *HiiConfigRouting;
  EFI_STRING                       ConfigRequestHdr;
  EFI_STRING                       ConfigRequest;
  BOOLEAN                          AllocatedRequest;
  UINTN                            Size;
  CHAR16                           *StrPointer;

  if (This == NULL || Progress == NULL || Results == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Initialize the local variables.
  //
  ConfigRequestHdr = NULL;
  ConfigRequest    = NULL;
  Size             = 0;
  *Progress = Request;
  AllocatedRequest = FALSE;

  Private = AMD_PBS_DXE_PRIVATE_FROM_THIS (This);
  HiiConfigRouting = Private->HiiConfigRouting;

  //
  // Get Buffer Storage data from EFI variable.
  // Try to get the current setting from variable.
  //
  BufferSize = sizeof (AMD_PBS_SETUP_OPTION);
  Status = gRT->GetVariable (
            AMD_PBS_SETUP_VARIABLE_NAME,
            &gAmdPbsSystemConfigurationGuid,
            NULL,
            &BufferSize,
            Private->IfrData
            );
  if (EFI_ERROR (Status)) {
    // set all default value to &Private->IfrData
    LoadAmdPbsDefault ((AMD_PBS_SETUP_OPTION*) &Private->IfrData);
  }

  if (Request == NULL) {
    //
    // Request is set to NULL, construct full request string.
    // Allocate and fill a buffer large enough to hold the <ConfigHdr> template
    // followed by "&OFFSET=0&WIDTH=WWWWWWWWWWWWWWWW" followed by a Null-terminator
    //
    ConfigRequestHdr = HiiConstructConfigHdr (&gAmdPbsSystemConfigurationGuid, AMD_PBS_SETUP_VARIABLE_NAME, Private->DriverHandle);
    Size = (StrLen (ConfigRequestHdr) + 32 + 1) * sizeof (CHAR16);
    ConfigRequest = AllocateZeroPool (Size);
    if (ConfigRequest == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
    AllocatedRequest = TRUE;
    UnicodeSPrint (ConfigRequest, Size, L"%s&OFFSET=0&WIDTH=%016LX", ConfigRequestHdr, (UINT64)BufferSize);
    FreePool (ConfigRequestHdr);
    ConfigRequestHdr = NULL;
  } else {
    //
    // Check routing data in <ConfigHdr>.
    // Note: if only one Storage is used, then this checking could be skipped.
    //
    if (!HiiIsConfigHdrMatch (Request, &mPbsSetupGuid, AMD_PBS_SETUP_VARIABLE_NAME)) {
      return EFI_NOT_FOUND;
    }
    //
    // Set Request to the unified request string.
    //
    ConfigRequest = Request;
    //
    // Check whether Request includes Request Element.
    //
    if (StrStr (Request, L"OFFSET") == NULL) {
      //
      // Check Request Element does exist in Reques String
      //
      StrPointer = StrStr (Request, L"PATH");
      if (StrPointer == NULL) {
        return EFI_INVALID_PARAMETER;
      }
      if (StrStr (StrPointer, L"&") == NULL) {
        Size = (StrLen (Request) + 32 + 1) * sizeof (CHAR16);
        ConfigRequest = AllocateZeroPool (Size);
        ASSERT (ConfigRequest != NULL);
        AllocatedRequest = TRUE;
        UnicodeSPrint (ConfigRequest, Size, L"%s&OFFSET=0&WIDTH=%016LX", Request, (UINT64) BufferSize);
      }
    }
  }

  Status = HiiConfigRouting->BlockToConfig (
                                HiiConfigRouting,
                                ConfigRequest,
                                Private->IfrData,
                                BufferSize,
                                Results,
                                Progress
                                );

  //
  // Free the allocated config request string.
  //
  if (AllocatedRequest) {
    FreePool (ConfigRequest);
    ConfigRequest = NULL;
  }

  //
  // Set Progress string to the original request string.
  //
  if (Request == NULL) {
    *Progress = NULL;
  } else if (StrStr (Request, L"OFFSET") == NULL) {
    *Progress = Request + StrLen (Request);
  }

  return Status;
} // AmdPbsExtractConfig


EFI_STATUS
EFIAPI
AmdPbsRouteConfig (
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN CONST EFI_STRING Configuration,
  OUT EFI_STRING *Progress
  )
{
  EFI_STATUS                       Status;
  UINTN                            BufferSize;
  AMD_PBS_DXE_PRIVATE_DATA         *Private;
  EFI_HII_CONFIG_ROUTING_PROTOCOL  *HiiConfigRouting;

  if (Configuration == NULL || Progress == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Private = AMD_PBS_DXE_PRIVATE_FROM_THIS (This);
  HiiConfigRouting = Private->HiiConfigRouting;
  *Progress = Configuration;

  //
  // Check routing data in <ConfigHdr>.
  // Note: if only one Storage is used, then this checking could be skipped.
  //
  if (!HiiIsConfigHdrMatch (Configuration, &gAmdPbsSystemConfigurationGuid, AMD_PBS_SETUP_VARIABLE_NAME)) {
    return EFI_NOT_FOUND;
  }

  //
  // Convert <ConfigResp> to buffer data by helper function ConfigToBlock()
  //
  BufferSize = sizeof (AMD_PBS_SETUP_OPTION);
  Status = HiiConfigRouting->ConfigToBlock (
                               HiiConfigRouting,
                               Configuration,
                               Private->IfrData,
                               &BufferSize,
                               Progress
                               );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Store Buffer Storage back to EFI variable
  //
  BufferSize = sizeof (AMD_PBS_SETUP_OPTION);
  Status = gRT->SetVariable(
                  AMD_PBS_SETUP_VARIABLE_NAME,
                  &gAmdPbsSystemConfigurationGuid,
                  EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  BufferSize,
                  Private->IfrData
                  );
  return Status;
}


EFI_STATUS
EFIAPI
AmdPbsCallback (
  IN  CONST EFI_HII_CONFIG_ACCESS_PROTOCOL  *This,
  IN  EFI_BROWSER_ACTION                    Action,
  IN  EFI_QUESTION_ID                       QuestionId,
  IN  UINT8                                 Type,
  IN  EFI_IFR_TYPE_VALUE                    *Value,
  OUT EFI_BROWSER_ACTION_REQUEST            *ActionRequest
  )
{
  EFI_STATUS                  Status;
  AMD_PBS_DXE_PRIVATE_DATA    *Private;
  UINTN                       BufferSize;
  UINTN                       VarSize;
  AMD_PBS_SETUP_OPTION        AmdPbsSetupConfig;
  STATIC BOOLEAN              AmdPbsCallbackInvoked = FALSE;

  if ((Action == EFI_BROWSER_ACTION_FORM_OPEN) || (Action == EFI_BROWSER_ACTION_FORM_CLOSE)) {
    return EFI_SUCCESS;
  }

  if ((Value == NULL) || (ActionRequest == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  if ((Type == EFI_IFR_TYPE_STRING) && (Value->string == 0)) {
    return EFI_INVALID_PARAMETER;
  }

  Status = EFI_SUCCESS;
  Private = AMD_PBS_DXE_PRIVATE_FROM_THIS (This);

  //
  // Retrive data from Browser
  //
  BufferSize = sizeof (AMD_PBS_SETUP_OPTION);
  if (!HiiGetBrowserData(&gAmdPbsSystemConfigurationGuid,
                         (CHAR16 *) AMD_PBS_SETUP_VARIABLE_NAME,
                         BufferSize,
                         (UINT8*)Private->IfrData)){
    return EFI_NOT_FOUND;
  }

  switch (Action) {
    case EFI_BROWSER_ACTION_RETRIEVE:
      if (!AmdPbsCallbackInvoked) {
        UpdateAmdFwVersionInfo (Private->HiiHandle);
      }
      AmdPbsCallbackInvoked = TRUE;
      break;

    case EFI_BROWSER_ACTION_DEFAULT_STANDARD:
      Status = LoadAmdPbsDefault ((AMD_PBS_SETUP_OPTION *) Private->IfrData);
      // EMBSWDEV-6181: If Callback Question Id matches with last option Question Id, assign the default value.
      if(QuestionId == KEY_XGBE_PCIE){
           Value->u64 = ((AMD_PBS_SETUP_OPTION *)Private->IfrData)->XgbeVsPcieXn; // Loading default value of last option
      }
      break;

    case EFI_BROWSER_ACTION_CHANGING:
      VarSize = sizeof (AMD_PBS_SETUP_OPTION);
      Status = HiiGetBrowserData (
                 &gAmdPbsSystemConfigurationGuid,
                 (CHAR16 *) AMD_PBS_SETUP_VARIABLE_NAME,
                 VarSize,
                 (UINT8 *) &AmdPbsSetupConfig);

      Status = HiiSetBrowserData (
                 &gAmdPbsSystemConfigurationGuid,
                 (CHAR16 *) AMD_PBS_SETUP_VARIABLE_NAME,
                 VarSize,
                 (UINT8 *) &AmdPbsSetupConfig,
                 NULL);
      return EFI_SUCCESS;
      break;

    case EFI_BROWSER_ACTION_CHANGED:
      AmdPbsBrowserActionChangedByQuestionId (QuestionId);
      return EFI_SUCCESS;
      break;

    default:
      break;
  }

  if (!EFI_ERROR (Status)) {
    //
    // Pass changed uncommitted data back to Form Browser
    //
    HiiSetBrowserData(&gAmdPbsSystemConfigurationGuid,
                      (CHAR16 *) AMD_PBS_SETUP_VARIABLE_NAME,
                      BufferSize,
                      (UINT8 *)Private->IfrData,
                      NULL);
  }

  return Status;
}


/**
 *---------------------------------------------------------------------------------------
 *
 *  AmdPbsDxeEntry
 *
 *  Description:
 *     Entry point for the cpu driver.
 *
 *  Parameters:
 *    @param[in]     ImageHandle
 *    @param[in]     *SystemTable
 *
 *    @retval         PMODULE_STATUS
 *
 *---------------------------------------------------------------------------------------
 **/

EFI_STATUS
EFIAPI
AmdPbsSetupDxeEntry (
  IN       EFI_HANDLE             ImageHandle,
  IN       EFI_SYSTEM_TABLE       *SystemTable
  )
{
  EFI_STATUS                      Status;
  EFI_HII_DATABASE_PROTOCOL       *HiiDatabase;
  EFI_HII_STRING_PROTOCOL         *HiiString;
  EFI_HII_CONFIG_ROUTING_PROTOCOL *HiiConfigRouting;
  AMD_PBS_DXE_PRIVATE_DATA        *Private;
  AMD_PBS_SETUP_OPTION            AmdPbsConfiguration;
  UINT8                           ReflashFlag;
  AMD_PBS_SETUP_OPTION            AmdPbsTempConfiguration;
  UINT8                           Index;
  UINT8                           DefaultUsedPbsSize;
  EFI_HII_PACKAGE_LIST_HEADER     *HiiPackageList;

  ReflashFlag = 0;
  Index = 0;
  DefaultUsedPbsSize = 46;  // It's RV PI 1001 DefaultUsedPbsSize.

  Status = GetAmdPbsConfiguration (&AmdPbsConfiguration);
  if (EFI_ERROR (Status)) {
    ReflashFlag |= BIT4 + BIT0;
    DEBUG((DEBUG_INFO, "OEM-DXE-AmdPbsSetupDxeEntry-  Error:  Failed to get AMD PBS variables\n"));
  }

  DEBUG((DEBUG_INFO, "OEM-DXE-AmdPbsSetupDxeEntry-AmdPbsConfiguration.AmdCpmUsedPbsSize = 0x%X\n", AmdPbsConfiguration.AmdCpmUsedPbsSize));
  DEBUG((DEBUG_INFO, "OEM-DXE-AmdPbsSetupDxeEntry-AMD_CPM_USED_PBS_SIZE = 0x%X\n", AMD_CPM_USED_PBS_SIZE));
  if (AmdPbsConfiguration.AmdCpmUsedPbsSize > 0) {
    DefaultUsedPbsSize = AmdPbsConfiguration.AmdCpmUsedPbsSize;
  }

  if (DefaultUsedPbsSize < AMD_CPM_USED_PBS_SIZE) {
    ReflashFlag |= BIT4 + BIT1;
    DEBUG((DEBUG_INFO, "OEM-DXE-AmdPbsSetupDxeEntry-  Notice: Add new created AMD PBS variables in NVRAM\n"));
  }

  if (AmdPbsConfiguration.PlatformId != ((PcdGet16 (OriginalPlatformId) & BIT2) >> 2)) {
    ReflashFlag |= BIT4;
    AmdPbsConfiguration.PlatformId = ((PcdGet16 (OriginalPlatformId) & BIT2) >> 2);
    DEBUG((DEBUG_INFO, "OEM-DXE-AmdPbsSetupDxeEntry-  Notice: Update AMD PBS PlatformId = 0x%X in NVRAM\n", AmdPbsConfiguration.PlatformId));
  }

  if (AmdPbsConfiguration.CurrentId != ((PcdGet16 (CurrentPlatformId) < 0x0008) ? 0 : 1)) {
    ReflashFlag |= BIT4;
    AmdPbsConfiguration.CurrentId = ((PcdGet16 (CurrentPlatformId) < 0x0008) ? 0 : 1);
    DEBUG((DEBUG_INFO, "OEM-DXE-AmdPbsSetupDxeEntry-  Notice: Update AMD PBS CurrentId = 0x%X in NVRAM\n", AmdPbsConfiguration.CurrentId));
  }

  if (ReflashFlag & BIT0) {
    LoadAmdPbsDefault (&AmdPbsConfiguration);
  } else if (ReflashFlag & BIT1) {
    LoadAmdPbsDefault (&AmdPbsTempConfiguration);
    CopyMem (((UINT8 *) &AmdPbsConfiguration) + DefaultUsedPbsSize, ((UINT8 *) &AmdPbsTempConfiguration) + DefaultUsedPbsSize, AMD_CPM_USED_PBS_SIZE - DefaultUsedPbsSize);
    for (Index = DefaultUsedPbsSize; Index < AMD_CPM_USED_PBS_SIZE; Index ++) {
      DEBUG((DEBUG_INFO, "OEM-DXE-AmdPbsSetupDxeEntry-Update PBS Index[0x%X] = 0x%X to 0x%X\n", Index, ((UINT8 *) &AmdPbsConfiguration)[Index], ((UINT8 *) &AmdPbsConfiguration)[Index]));
    }
    if (AmdPbsConfiguration.AmdCpmUsedPbsSize != AMD_CPM_USED_PBS_SIZE) {
      AmdPbsConfiguration.AmdCpmUsedPbsSize = AMD_CPM_USED_PBS_SIZE;
      DEBUG((DEBUG_INFO, "OEM-DXE-AmdPbsSetupDxeEntry-Update AmdCpmUsedPbsSize to 0x%X\n", AmdPbsConfiguration.AmdCpmUsedPbsSize));
    }
  }

  if (ReflashFlag & BIT4) {
    DEBUG((DEBUG_INFO, "OEM-DXE-AmdPbsSetupDxeEntry-  Notice: Update AMD PBS variables\n"));
    Status = SetAmdPbsConfiguration (&AmdPbsConfiguration);
    if (EFI_ERROR (Status)) {
      DEBUG((DEBUG_INFO, "OEM-DXE-AmdPbsSetupDxeEntry-  Error:  Failed to Update AMD PBS variables to NVRAM\n"));
      return Status;
    }
  }

  Private = AllocateZeroPool (sizeof (AMD_PBS_DXE_PRIVATE_DATA));
  if (Private == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Private->Signature   = AMD_PBS_DXE_PRIVATE_SIGNATURE;

  Private->ConfigAccess.ExtractConfig = AmdPbsExtractConfig;
  Private->ConfigAccess.RouteConfig   = AmdPbsRouteConfig;
  Private->ConfigAccess.Callback      = AmdPbsCallback;

  Private->IfrData = AllocateZeroPool (sizeof (AMD_PBS_SETUP_OPTION));
  ASSERT (Private->IfrData != NULL);

  Status = gBS->LocateProtocol (&gEfiHiiDatabaseProtocolGuid, NULL, (VOID **) &HiiDatabase);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Private->HiiDatabase = HiiDatabase;

  //
  // Locate HiiString protocol
  //
  Status = gBS->LocateProtocol (&gEfiHiiStringProtocolGuid, NULL, (VOID **) &HiiString);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Private->HiiString = HiiString;

  //
  // Locate ConfigRouting protocol
  //
  Status = gBS->LocateProtocol (&gEfiHiiConfigRoutingProtocolGuid, NULL, (VOID **) &HiiConfigRouting);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Private->HiiConfigRouting = HiiConfigRouting;
  // Get the HiiPackageListProtocol from the Image's Handle
  Status = gBS->HandleProtocol(ImageHandle, &gEfiHiiPackageListProtocolGuid, (VOID**)&HiiPackageList);
  if(EFI_ERROR(Status)){
    return Status;
  }

  Private->DriverHandle = NULL;              // if NULL, handle will be assigned.

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Private->DriverHandle,
                  &gEfiDevicePathProtocolGuid,
                  &mHiiVendorDevicePath0,
                  &gEfiHiiConfigAccessProtocolGuid,
                  &Private->ConfigAccess,
                  NULL);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  
  Status = HiiDatabase->NewPackageList( 
                  HiiDatabase,
                  HiiPackageList,
                  Private->DriverHandle,
                  &Private->HiiHandle
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Publish the HII package list
  //
 /* Private->HiiHandle = HiiAddPackages (
                 &mFormSetGuid,
                 Private->DriverHandle,
                 AmdPbsSetupDxeStrings,
                 AmdPbsHiiBin,
                 NULL);
  */
  
  if (Private->HiiHandle == NULL) {
    gBS->UninstallMultipleProtocolInterfaces (
                  &Private->DriverHandle,
                  &gEfiDevicePathProtocolGuid,
                  &mHiiVendorDevicePath0,
                  &gEfiHiiConfigAccessProtocolGuid,
                  &Private->ConfigAccess,
                  NULL
                  );

    return EFI_OUT_OF_RESOURCES;
  }

  return Status;
}
