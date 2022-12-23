//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file SbSetup.c
    South Bridge Setup Routines

**/

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Setup.h>
#include <Protocol/PciIo.h>
#include <Protocol/DevicePath.h>
#include <Protocol/BlockIo.h>
#include <Protocol/DiskInfo.h>
#include <Protocol/PIDEController.h>
#if CSM_SUPPORT
#include <Protocol/LegacyBios.h>
#endif

#include <IndustryStandard/AmiAtaAtapi.h>
#include "AmiCspLib.h"
#include "Sb.h"
#include <Token.h>

#include <Library/PcdLib.h>
#include <Library/DevicePathLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PrintLib.h>
#include <Guid/AmdCbsConfig.h>

// The device path refer to CbsSetupDxe.c
//	to identify if AMD-CBS-SETUP exist.
struct {
	VENDOR_DEVICE_PATH           VendorDevicePath;
	EFI_DEVICE_PATH_PROTOCOL     End;
} gCbsVendorDp = {
  {
    {
      HARDWARE_DEVICE_PATH,
      HW_VENDOR_DP,
      {
        (UINT8) (sizeof (VENDOR_DEVICE_PATH)),
        (UINT8) ((sizeof (VENDOR_DEVICE_PATH)) >> 8)
      }
    },
    CBS_SYSTEM_CONFIGURATION_GUID
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

//
// Length of temp string buffer to store value string.
//
#define CHARACTER_NUMBER_FOR_VALUE              30
#define _48_BIT_ADDRESS_FEATURE_SET_SUPPORTED   0x0400
#define ATAPI_DEVICE                            0x8000

#if SHOW_IDE_MODE_SETUP
STRING_REF gPATA[2][2] = {
    // SATA port4,5 DID=IDE DID
    {STRING_TOKEN(STR_SATA4_FORM), STRING_TOKEN(STR_SATA5_FORM)},
    {STRING_TOKEN(STR_PATA_MASTER_FORM), STRING_TOKEN(STR_PATA_SLAVE_FORM)}
};

STRING_REF gSATA[3][2] = {
    {STRING_TOKEN(STR_SATA0_FORM), STRING_TOKEN(STR_SATA2_FORM)},
    {STRING_TOKEN(STR_SATA1_FORM), STRING_TOKEN(STR_SATA3_FORM)},
    {STRING_TOKEN(STR_SATA4_FORM), STRING_TOKEN(STR_SATA5_FORM)}
};

STRING_REF gAHCI[6] = {
    STRING_TOKEN(STR_SATA0_FORM), STRING_TOKEN(STR_SATA1_FORM),
    STRING_TOKEN(STR_SATA2_FORM), STRING_TOKEN(STR_SATA3_FORM),
    STRING_TOKEN(STR_SATA4_FORM), STRING_TOKEN(STR_SATA5_FORM)
};
#else
STRING_REF gPATA[2][2] = {
    // SATA port4,5 DID=IDE DID
    {STRING_TOKEN(STR_SATA_4_NAME), STRING_TOKEN(STR_SATA_5_NAME)},
    {STRING_TOKEN(STR_SATA_5_NAME), STRING_TOKEN(STR_SATA_4_NAME)}
};

STRING_REF gSATA[3][2] = {
    {STRING_TOKEN(STR_SATA_0_NAME), STRING_TOKEN(STR_SATA_2_NAME)},
    {STRING_TOKEN(STR_SATA_1_NAME), STRING_TOKEN(STR_SATA_3_NAME)},
    {STRING_TOKEN(STR_SATA_4_NAME), STRING_TOKEN(STR_SATA_5_NAME)}
};

STRING_REF gAHCI[6] = {
    STRING_TOKEN(STR_SATA_0_NAME), STRING_TOKEN(STR_SATA_1_NAME),
    STRING_TOKEN(STR_SATA_2_NAME), STRING_TOKEN(STR_SATA_3_NAME),
    STRING_TOKEN(STR_SATA_4_NAME), STRING_TOKEN(STR_SATA_5_NAME)
};
#endif

UINT32 GetNumTenthsOfGB (IN UINT32 RemainderBytesOfGB);
VOID SwapEntries (IN CHAR8 *Data, IN UINT16 Size);

EFI_STATUS SBUpdateIdeSetupInfo (
    IN EFI_HII_HANDLE   HiiHandle,
    IN STRING_REF       Token,
    IN IDENTIFY_DATA    *IdentifyDriveInfo
  );

struct {
    CHAR16*     FchTypeStr;
    CHAR16*     SataPciDpText;
} CONST gFchSataDps[] = {
        {L"Sandstone",      L"PciRoot(0x0)/Pci(0x8,0x2)/Pci(0x0,0x0)"},
        {L"Taishan",        L"PciRoot(0x0)/Pci(0x8,0x1)/Pci(0x0,0x2)"},
        {L"Kern",           L"PciRoot(0x0)/Pci(0x11,0x0)"},
        {L"Kern",           L"PciRoot(0x0)/Pci(0x14,0x1)"}, // Kern legacy PATA-IDE.
        // Porting required for new chip
        // Append Promontory here maybe....
        {NULL, NULL}
};

/**
    Init South Bridge strings

    @param HiiHandle
    @param Class

    @retval VOID

**/
VOID InitSBStrings(IN EFI_HII_HANDLE HiiHandle, IN UINT16 Class)
{
    if (Class == ADVANCED_FORM_SET_CLASS) {
        UINT8                        CONST SataClass = PcdGet8(PcdSataClass);
        BOOLEAN                      CONST SataSata6AhciCap = PcdGetBool(PcdSataSata6AhciCap);

        STRING_REF                  Token;
        EFI_STATUS                  Status;
        UINT8                       Index;
        UINTN                       HandleCount;
        EFI_HANDLE                  *HandleBuffer;
        EFI_DEVICE_PATH_PROTOCOL    *DevicePath;
        EFI_DISK_INFO_PROTOCOL      *DiskInfo;
        UINT32                      IdeChannel;
        UINT32                      IdeDevice;
        IDENTIFY_DATA               *IdentifyDriveInfo = NULL;
        UINT32                      BufferSize = 0;

		UINT8 						Var;
		EFI_DEVICE_PATH_PROTOCOL	*Dp;
		EFI_HANDLE					Handle;

		//
		// To identify if AMD-CBS-SETUP exist.
		//
		Dp = DuplicateDevicePath (&gCbsVendorDp.VendorDevicePath.Header);
		Status = gBS->LocateDevicePath(
						&gEfiHiiConfigAccessProtocolGuid,
						&Dp,
						&Handle);
		if (EFI_ERROR(Status)) Var = 0;
		else Var = 1;
		// disable AMI setup if CBS exist.
		Status = gRT->SetVariable (
					L"AmiAmdSbSuppressIfSetupData",
					&gAmiAmdCspVarstoreGuid,
					EFI_VARIABLE_BOOTSERVICE_ACCESS,
					sizeof(UINT8),
					&Var
					);
		ASSERT_EFI_ERROR(Status);

        //
        // Fill IDE Infomation
        //
        Status = gBS->LocateHandleBuffer (
                        ByProtocol,
                        &gEfiDiskInfoProtocolGuid,
                        NULL,
                        &HandleCount,
                        &HandleBuffer);

        if (EFI_ERROR(Status)) HandleCount = 0;

        for (Index = 0; Index < HandleCount; Index++) {
        	BOOLEAN			IsOnChipSata = FALSE;
        	CHAR16			*GetFchTypeStr = (CHAR16*)PcdGetPtr(AmiPcdSbFchTypeString);
        	CHAR16			*GetSataPciDpText = NULL;
        	CHAR16			*DpStr = NULL;
        	UINT32			i;

            DevicePath = DevicePathFromHandle(HandleBuffer[Index]);
            DpStr = ConvertDevicePathToText(DevicePath, FALSE, FALSE);

            // Find onChip device.
			i = 0;
			while(gFchSataDps[i].FchTypeStr != NULL) {
				// Find FCH type.
				if (StrCmp(gFchSataDps[i].FchTypeStr, GetFchTypeStr) == 0) {
					// Find correct depice path.
				    GetSataPciDpText = gFchSataDps[i].SataPciDpText;
					if (StrnCmp(GetSataPciDpText, DpStr, StrLen(GetSataPciDpText)) == 0) {
						DEBUG ((DEBUG_INFO|DEBUG_CHIPSET,"    <SbSetup>.InitSBStrings : %s-SATA %s\n",GetFchTypeStr, GetSataPciDpText));
						IsOnChipSata = TRUE;
						break;
					}
				}
				i++;
			}
			if (DpStr != NULL) FreePool(DpStr);

            //
            // Check for OnChip IDE
            //
            if (IsOnChipSata && GetSataPciDpText != NULL) {
                Status = gBS->HandleProtocol (
                            HandleBuffer[Index],
                            &gEfiDiskInfoProtocolGuid,
                            &DiskInfo);
                ASSERT_EFI_ERROR (Status);

                Status = DiskInfo->WhichIde (
                            DiskInfo,
                            &IdeChannel,
                            &IdeDevice);
                ASSERT_EFI_ERROR (Status);
                // primary,secondary-master,slave,
                // AHCI mode >> IdeChannel = 0~5, IdeDevice=0
                if (IdeChannel > MAX_AHCI_CHANNEL || IdeDevice > 1) continue;

                BufferSize = sizeof (IDENTIFY_DATA);
                IdentifyDriveInfo = AllocateZeroPool(BufferSize);
                ASSERT(IdentifyDriveInfo);

                Status = DiskInfo->Identify (
                            DiskInfo,
                            IdentifyDriveInfo,
                            &BufferSize);
                ASSERT_EFI_ERROR (Status);

                // Is Pata or Sata controller ?
                if (StrCmp(GetSataPciDpText, L"PciRoot(0x0)/Pci(0x14,0x1)") == 0) {
                	// This is Legacy-PATA-IDE.
                    if (SataSata6AhciCap == 0) {
                        // SATA as primary
                        Token = gPATA[IdeChannel][IdeDevice];
                    }else{
                        // SATA as secondary
                        Token = gPATA[IdeChannel ^ 1][IdeDevice];
                    }
                } else  {
                	// This is SATA devices.
                    if (SataClass == 1 || SataClass == 2 || SataClass == 5) {
                        // RAID / AHCI / AHCI as 7804
                        Token = gAHCI[IdeChannel];
                    } else {
                        // others
                        Token = gSATA[IdeChannel][IdeDevice];
                    }
                }

            } else {
                //
                // non-FCH
                //
                continue;
            }

            // (CSP_090609a_BL+) >
            Status = SBUpdateIdeSetupInfo(HiiHandle, Token, IdentifyDriveInfo);
            // (CSP_090609a_BL+) <

            if (IdentifyDriveInfo) {
                FreePool (IdentifyDriveInfo);
                IdentifyDriveInfo = NULL;
            }
        }
    #if CSM_SUPPORT
        // if RAID mode
        if (SataClass == 1) {
            UINT8                       MaxDriveCount;
            UINT8                       DriverNum, SataPort;
            BOOLEAN                     CarryFlag;
            EFI_IA32_REGISTER_SET       Regs;
            EFI_LEGACY_BIOS_PROTOCOL    *LegacyBios;
            EFI_PHYSICAL_ADDRESS        TheRealModeBuffer;
            VOID*                       Int13Buffer = NULL;
            CHAR8                       AMDString[] = "_DMA";

            Status = gBS->LocateProtocol(&gEfiLegacyBiosProtocolGuid, NULL, &LegacyBios);
            //ASSERT_EFI_ERROR(Status);
            if(EFI_ERROR(Status)) return;

            // allocate conventional memory for int code
            TheRealModeBuffer = 0x00000000000FFFFF;
            Status = gBS->AllocatePages(
                        AllocateMaxAddress,
                        EfiBootServicesData,
                        1, // Number of 4k pages
                        &TheRealModeBuffer);
            ASSERT_EFI_ERROR(Status);

            Int13Buffer = (VOID*)TheRealModeBuffer;
            // clear 4K page
            ZeroMem(Int13Buffer, 1024*4);

            // get driver count from BDA.
            MaxDriveCount = *(UINT8*)0x475;
            for(Index = 0; Index < MaxDriveCount; Index++) {
                DriverNum = Index + 0x80;

                for (SataPort = 0; SataPort < 6; SataPort++) {
                    // Get physical hard disk information by ATA identify command
                    // use AMD provide INT13 function code
                    CopyMem (&Regs.E.ECX, AMDString, 4);
                    Regs.H.AH = 0x25;
                    Regs.H.DL = DriverNum;
                    Regs.H.DH = SataPort;
                    Regs.X.BX = EFI_OFFSET(Int13Buffer);
                    Regs.X.ES = EFI_SEGMENT(Int13Buffer);
                    LegacyBios->Int86 (LegacyBios, 0x13, &Regs);
                    CarryFlag = (BOOLEAN)Regs.X.Flags.CF;
                    if (!CarryFlag) {
                        IdentifyDriveInfo = (IDENTIFY_DATA*)Int13Buffer;
                        Token = gAHCI[SataPort];
                        Status = SBUpdateIdeSetupInfo(HiiHandle, Token, IdentifyDriveInfo);
                        ASSERT_EFI_ERROR(Status);
                    }
                }
            }
            if (Int13Buffer) FreePages ((VOID*)TheRealModeBuffer, 1);
        }
    #endif
        if (HandleBuffer) FreePool (HandleBuffer);
    }

    if (Class == CHIPSET_FORM_SET_CLASS) {
    	UINTN	  HeaderSize = AsciiStrSize(PcdGetPtr(PcdAmdPackageString));
    	CHAR8	  *AsciiString = PcdGetPtr(PcdAmdPackageString);
        CHAR16    String[64]; // AVA9 : I think 64 characters is enough to contain the string. Dynamic allocate "PcdGetSize" if needed.

        AsciiString = AsciiString + HeaderSize; // Skip "AGESA!V9\0" header.

        AsciiStrToUnicodeStrS(AsciiString, String, sizeof(String) / sizeof(CHAR16));
        InitString(HiiHandle, STRING_TOKEN(STR_AMD_REF_VER),
                 L"%s",
                 String
                 );
    }
}

/*
  GetNumTenthsOfGB:

  x   x/16    num tenths
  -   ----    ----------
  0   0       0
  1   .0625   1
  2   .125    1
  3   .1875   2
  4   .25     2
  5   .3125   3
  6   .375    4
  7   .4375   4
  8   .5      5
  9   .5625   6
  10  .625    6
  11  .6875   7
  12  .75     7
  13  .8125   8
  14  .875    9
  15  .9375   9
*/

/**

    @param RemainderBytesOfGB

    @retval UINT32 Tenths

**/

UINT32
GetNumTenthsOfGB (
    IN UINT32 RemainderBytesOfGB
    )
{
    UINT32          Tenths = 0; //num tenths of of a GB
    UINT32          Sixteenths = RemainderBytesOfGB / (1 << 26); //num sixteenths of a GB

    switch (Sixteenths) {
        case 0:
            Tenths = 0; break;
        case 1:
        case 2:
            Tenths = 1; break;
        case 3:
        case 4:
            Tenths = 2; break;
        case 5:
            Tenths = 3; break;
        case 6:
        case 7:
            Tenths = 4; break;
        case 8:
            Tenths = 5; break;
        case 9:
        case 10:
            Tenths = 6; break;
        case 11:
        case 12:
            Tenths = 7; break;
        case 13:
            Tenths = 8; break;
        case 14:
        case 15:
            Tenths = 9; break;
        default:
            Tenths = 0; break;
    }

    return Tenths;
}

/**

    Please use MdePkg-BaseLib-AsciiStrToUnicodeStr to instead AsciiToUnicode.

**/

/**

    Please use MdePkg-BaseLib-AsciiStrHexToUintn to instead EfiValueToString.

**/


/**
    Swap Entries


    @param Data
    @param Size
    @retval VOID

**/

VOID SwapEntries (
    IN CHAR8        *Data,
    IN UINT16       Size
    )
{
    UINT16          Index;
    CHAR8           Temp8;

    for (Index = 0; (Index + 1) < Size; Index += 2) {
        Temp8           = Data[Index];
        Data[Index]     = Data[Index + 1];
        Data[Index + 1] = Temp8;
    }
}

/**
    SB Update Ide Setup Info


    @param HiiHandle
    @param Token
    @param IdentifyDriveInfo
    @retval EFI_STATUS return

**/

EFI_STATUS SBUpdateIdeSetupInfo (
    IN EFI_HII_HANDLE   HiiHandle,
    IN STRING_REF       Token,
    IN IDENTIFY_DATA    *IdentifyDriveInfo
  )
{
    CHAR8               NewString[0x100];
    CHAR8               ModelNumber[42];
    UINT64              NumSectors;
    UINT64              DriveSizeInBytes;
    UINT32              RemainderInBytes;

    if(IdentifyDriveInfo == NULL) return EFI_INVALID_PARAMETER;

    gBS->SetMem(ModelNumber, 42, 0);
    gBS->CopyMem (ModelNumber, IdentifyDriveInfo->Model_Number_27, 40);
    SwapEntries (ModelNumber, 40);
    ModelNumber[DEVICE_NAME_LENGTH] = '\0';     // Truncate it at 14 characters

    //
    // For HardDisk append the size. Otherwise display atapi
    //
    if (!(IdentifyDriveInfo->General_Config_0 & ATAPI_DEVICE)) {

        UINT32              DriveSizeInGB = 0;
        UINT32              NumTenthsOfGB = 0;
        UINT32              SectorSize = 512; // Default Sector Size

        if (IdentifyDriveInfo->Command_Set_Supported_83 & _48_BIT_ADDRESS_FEATURE_SET_SUPPORTED) {
            NumSectors = IdentifyDriveInfo->LBA_48;
              // WORD 106 valid? - BIT 14 - 1
              if ((IdentifyDriveInfo->Reserved_104_126[2] & 0x4000) && \
                  // WORD 106 valid? - BIT 15 - 0
                  (!(IdentifyDriveInfo->Reserved_104_126[2] & 0x8000)) &&
                  // WORD 106 bit 12 - Sectorsize > 256 words
                  (IdentifyDriveInfo->Reserved_104_126[2] & 0x1000)) {
                      // The sector size is in words 117-118.
                      SectorSize = (UINT32)\
                        (IdentifyDriveInfo->Reserved_104_126[13] + \
                        (IdentifyDriveInfo->Reserved_104_126[14] << 16)) * 2;
              }
        } else {
              NumSectors = IdentifyDriveInfo->Addressable_Sector_60;
        }

        DriveSizeInBytes = Mul64(NumSectors, SectorSize);

        //DriveSizeInGB is DriveSizeInBytes / 1 GB
        //####DriveSizeInGB = (UINT32) Div64(DriveSizeInBytes, (1 << 30), &RemainderInBytes);
        DriveSizeInGB = \
            (UINT32) Div64(DriveSizeInBytes, (1000 * 1000 * 1000), (UINTN*)&RemainderInBytes);

        //Convert the Remainder, which is in bytes, to number of tenths of a GB.
        NumTenthsOfGB = GetNumTenthsOfGB(RemainderInBytes);

        AsciiSPrint(NewString, sizeof(NewString),"%a (%d.%dGB)", ModelNumber, DriveSizeInGB, NumTenthsOfGB);
    } else {
        AsciiSPrint(NewString, sizeof(NewString),"%a ATAPI", ModelNumber);
    }

    InitString(
        HiiHandle,
        Token,
        L"%a",
        NewString);

    return EFI_SUCCESS;
}


