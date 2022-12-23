/* $NoKeywords:$ */
/**
 * @file
 *
 * PSP Base Library
 *
 * Contains interface to the PSP library
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 *
 */
/*
 ******************************************************************************
 *
 * Copyright 2008 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting you permission to use this software and documentation (if
 * any) (collectively, the "Materials") pursuant to the terms and conditions of
 * the Software License Agreement included with the Materials.  If you do not
 * have a copy of the Software License Agreement, contact your AMD
 * representative for a copy.
 *
 * You agree that you will not reverse engineer or decompile the Materials, in
 * whole or in part, except as allowed by applicable law.
 *
 * WARRANTY DISCLAIMER:  THE MATERIALS ARE PROVIDED "AS IS" WITHOUT WARRANTY OF
 * ANY KIND.  AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY,
 * INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT, THAT THE
 * MATERIALS WILL RUN UNINTERRUPTED OR ERROR-FREE OR WARRANTIES ARISING FROM
 * CUSTOM OF TRADE OR COURSE OF USAGE.  THE ENTIRE RISK ASSOCIATED WITH THE USE
 * OF THE MATERIAL IS ASSUMED BY YOU.  Some jurisdictions do not allow the
 * exclusion of implied warranties, so the above exclusion may not apply to
 * You.
 *
 * LIMITATION OF LIABILITY AND INDEMNIFICATION:  AMD AND ITS LICENSORS WILL
 * NOT, UNDER ANY CIRCUMSTANCES BE LIABLE TO YOU FOR ANY PUNITIVE, DIRECT,
 * INCIDENTAL, INDIRECT, SPECIAL OR CONSEQUENTIAL DAMAGES ARISING FROM USE OF
 * THE MATERIALS OR THIS AGREEMENT EVEN IF AMD AND ITS LICENSORS HAVE BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  In no event shall AMD's total
 * liability to You for all damages, losses, and causes of action (whether in
 * contract, tort (including negligence) or otherwise) exceed the amount of
 * $100 USD. You agree to defend, indemnify and hold harmless AMD and its
 * licensors, and any of their directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your use of
 * the Materials or violation of the terms and conditions of this Agreement.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS:  The Materials are provided with
 * "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
 * subject to the restrictions as set forth in FAR 52.227-14 and
 * DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
 * Government constitutes acknowledgment of AMD's proprietary rights in them.
 *
 * EXPORT RESTRICTIONS: The Materials may be subject to export restrictions as
 * stated in the Software License Agreement.
 *******************************************************************************
 */


/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include <Uefi.h>
#include "AGESA.h"
#include "Filecode.h"
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/AmdSocBaseLib.h>
#include <Library/AmdPspBaseLibV2.h>
#include <Library/AmdPspCommonLib.h>
#include <Library/CcxRolesLib.h>
#include <Library/FabricResourceManagerLib.h>
#include <Library/PciLib.h>

#define FILECODE LIBRARY_AMDPSPBASELIBV2_AMDPSPBASELIBV2_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define NBMSIC_SMN_BASE                     0x13B10000ul           ///< Define the SMN Base address for NB MISC register
#define MTS_NBMISC_SMN_BASE                 0x13E10000ul           ///< Define the SMN Base address for MTS NB MISC register
#define NBMSIC_PSP_BASE_ADDR_LO_OFFSET      0x2E0                  ///< Define the offset of PSP_BASE_ADDR_LO in NB MISC block
#define NBMSIC_PSP_BASE_ADDR_HI_OFFSET      0x2E4                  ///< Define the offset of PSP_BASE_ADDR_HI in NB MISC block
#define PSP_BAR_SIZE                        0x100000ul             ///< Size of PSP BAR
#define C2P_REG_OFFSET                      0x10500ul              ///< BIOS to PSP mailbox Register SMN offset
#define BIOS_MAILBOX_BASE                   (28 * 4)               ///< BIOS to PSP Mailbox base offset on PCIe BAR

#define DF_MMIOBASEADDRESS_0_PCI_ADDR    (MAKE_SBDFO (0, 0, 0x18, 0, 0x200))  ///< MmioBaseAddress
#define DF_MMIOLIMITADDRESS_0_PCI_ADDR   (MAKE_SBDFO (0, 0, 0x18, 0, 0x204))  ///< MmioLimitAddress
#define DF_MMIOADDRESSCONTROL_0_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, 0, 0x208))  ///< MmioAddressControl
#define NB_SMN_INDEX_2_PCI_ADDR (MAKE_SBDFO (0, 0, 0, 0, 0xB8))  ///< PCI Addr of NB_SMN_INDEX_2
#define NB_SMN_DATA_2_PCI_ADDR (MAKE_SBDFO (0, 0, 0, 0, 0xBC))  ///< PCI Addr of NB_SMN_DATA_2
#define BIOS_MUTEX_OFFSET    (23 * 4)       ///< BIOS mutex: BIOS sets this to non-zero requesting the mutex; clears this register when releases the mutex;
#define PSP_MUTEX_OFFSET     (24 * 4)       ///< PSP sets this to non-zero requesting the mutex; clears this register when releases the mutex;
#define MUTEX_TURN_OFFSET    (25 * 4)       ///< Turn registers as it is: BIOS sets this to 1 when requests the mutes; PSP sets it to 0 when PSP requests the mutex

#define FORCE_SPIADDR_BIT24(SpiAddress) (SpiAddress | 0xFF000000)

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
UINT32 Fletcher32 (
  IN OUT   UINT16  *data,
  IN       UINTN   words
  )
{
  UINT32 sum1;
  UINT32 sum2;
  UINTN tlen;

  sum1 = 0xffff;
  sum2 = 0xffff;

  while (words) {
    tlen = words >= 359 ? 359 : words;
    words -= tlen;
    do {
      sum2 += sum1 += *data++;
    } while (--tlen);
    sum1 = (sum1 & 0xffff) + (sum1 >> 16);
    sum2 = (sum2 & 0xffff) + (sum2 >> 16);
  }
  // Second reduction step to reduce sums to 16 bits
  sum1 = (sum1 & 0xffff) + (sum1 >> 16);
  sum2 = (sum2 & 0xffff) + (sum2 >> 16);
  return sum2 << 16 | sum1;
}


BOOLEAN
ValidatePspDir (
  IN       PSP_DIRECTORY     *PspDir,
  IN       UINT32     Signature
  )
{
  //Validate Signature
  if (PspDir->Header.PspCookie != Signature) {
    return FALSE;
  }
  //Do the checksum
  if (PspDir->Header.Checksum != Fletcher32 ((UINT16 *) &PspDir->Header.TotalEntries, \
      (sizeof (PSP_DIRECTORY_HEADER) - OFFSET_OF (PSP_DIRECTORY_HEADER, TotalEntries) + PspDir->Header.TotalEntries * sizeof (PSP_DIRECTORY_ENTRY)) / 2)) {
    return FALSE;
  }
  return TRUE;
}

BOOLEAN
ValidateBiosDir (
  IN       BIOS_DIRECTORY     *BiosDir,
  IN       UINT32     Signature
  )
{
  //Validate Signature
  if (BiosDir->Header.PspCookie != Signature) {
    return FALSE;
  }
  //Do the checksum
  if (BiosDir->Header.Checksum != Fletcher32 ((UINT16 *) &BiosDir->Header.TotalEntries, \
      (sizeof (PSP_DIRECTORY_HEADER) - OFFSET_OF (PSP_DIRECTORY_HEADER, TotalEntries) + BiosDir->Header.TotalEntries * sizeof (BIOS_DIRECTORY_ENTRY)) / 2)) {
    return FALSE;
  }
  return TRUE;
}


BOOLEAN
GetComboDir (
  IN       UINT32     PspComboDirBase,
  IN       UINT32     PspChipId,
  IN OUT   UINT32     *PspDirBase
  )
{
  PSP_COMBO_DIRECTORY *PspComboDir;
  PSP_COMBO_DIRECTORY_ENTRY *PspComboEntry;
  UINT32 i;


  PspComboDir = (PSP_COMBO_DIRECTORY *) (UINTN) PspComboDirBase;
  PspComboEntry = &PspComboDir->ComboEntry[0];
  //Check the signature
  if (PspComboDir->Header.PspCookie != PSP_COMBO_DIRECTORY_HEADER_SIGNATURE) {
    return FALSE;
  }
  //Loop to found matched entry
  for (i = 0; i < PspComboDir->Header.TotalEntries; i++) {
    if (PspComboEntry[i].Id == PspChipId) {
      *PspDirBase = FORCE_SPIADDR_BIT24 ((UINT32) PspComboEntry[i].PspDirTableAddr);
      return TRUE;
    }
  }
  return FALSE;
}

BOOLEAN
GetDirBase (
  IN OUT   UINT32     *PspDirBase,
  IN OUT   UINT32     *BiosDirBase
  )
{
  UINTN                     i;
  FIRMWARE_ENTRY_TABLEV2      *FirmwareTableBase;
  UINT32  FamilyId;
  UINT32  PspChipId;
  BOOLEAN PspDirSigValid;
  BOOLEAN BiosDirSigValid;

  CONST UINT32 RomSigAddrTable[] =
  {
    0xFFFA0000, //  --> 512KB base
    0xFFF20000, //  --> 1MB base
    0xFFE20000, //  --> 2MB base
    0xFFC20000, //  --> 4MB base
    0xFF820000, //  --> 8MB base
    0xFF020000  //  --> 16MB base
  };

  FamilyId = 0;
  PspChipId = 0;

  if (SocFamilyIdentificationCheck (F17_ZP_RAW_ID)) {
    FamilyId = F17_ZP_RAW_ID;
  } else if (SocFamilyIdentificationCheck (F17_RV_RAW_ID)) {
    FamilyId = F17_RV_RAW_ID;
  } else if (SocFamilyIdentificationCheck (F17_RV2_RAW_ID)) {
    FamilyId = F17_RV2_RAW_ID;
  } else if (SocFamilyIdentificationCheck (F17_SSP_RAW_ID)) {
    FamilyId = F17_SSP_RAW_ID;
  } else if (SocFamilyIdentificationCheck (F17_PIC_RAW_ID)) {
    FamilyId = F17_PIC_RAW_ID;
  } else if (SocFamilyIdentificationCheck (F17_MTS_RAW_ID)) {
    FamilyId = F17_MTS_RAW_ID;
  } else {
    //Unsupported Family detected
    return (FALSE);
  }


  for (i = 0; i < sizeof (RomSigAddrTable) / sizeof (UINT32); i++) {
    FirmwareTableBase  = (FIRMWARE_ENTRY_TABLEV2 *) (UINTN) RomSigAddrTable[i];
    // Search flash for unique signature 0x55AA55AA
    if (FirmwareTableBase->Signature  == FIRMWARE_TABLE_SIGNATURE) {
      switch (FamilyId) {
      case F17_ZP_RAW_ID:
        *BiosDirBase = FirmwareTableBase->ZpBiosDirBase;
        PspChipId = ZP_PSP_CHIP_ID;
        break;
      case F17_RV_RAW_ID:
      case F17_PIC_RAW_ID:
        *BiosDirBase = FirmwareTableBase->RvBiosDirBase;
        PspChipId = RV_PSP_CHIP_ID;
        break;
      case F17_RV2_RAW_ID:
        *BiosDirBase = FirmwareTableBase->RvBiosDirBase;
        PspChipId = RV2_PSP_CHIP_ID;
        break;
      case F17_MTS_RAW_ID:
        *BiosDirBase = FirmwareTableBase->SspBiosDirBase;
        PspChipId = MTS_PSP_CHIP_ID;
        break;
      case F17_SSP_RAW_ID:
        *BiosDirBase = FirmwareTableBase->SspBiosDirBase;
        PspChipId = SSP_PSP_CHIP_ID;
        break;
      default:
        //Unsupported Family detected
        break;
      }
      *BiosDirBase = FORCE_SPIADDR_BIT24 (*BiosDirBase);
      //Check if combo structure
      if (GetComboDir (FORCE_SPIADDR_BIT24 (FirmwareTableBase->PspDirBase), PspChipId, PspDirBase) == FALSE) {
        //Using the address Get from ROMSIG directly if not combo DIR
        *PspDirBase = FORCE_SPIADDR_BIT24 (FirmwareTableBase->PspDirBase);
      }
      PspDirSigValid = FALSE;
      BiosDirSigValid = FALSE;
      PspDirSigValid = ValidatePspDir ((PSP_DIRECTORY *) (UINTN) *PspDirBase, PSP_DIRECTORY_HEADER_SIGNATURE);
      BiosDirSigValid = ValidateBiosDir ((BIOS_DIRECTORY *) (UINTN) *BiosDirBase, BIOS_DIRECTORY_HEADER_SIGNATURE);

      ASSERT (PspDirSigValid);
      ASSERT (BiosDirSigValid);
      if (PspDirSigValid && BiosDirSigValid) {
        return TRUE;
      } else {
        return FALSE;
      }
    }
  }

  return (FALSE);
}


BOOLEAN
PSPEntryInfoV2 (
  IN       UINT32                      EntryType,
  IN OUT   UINT64                      *EntryAddress,
  IN       UINT32                      *EntrySize
  )
{
  PSP_DIRECTORY         *PspDir;
  PSP_DIRECTORY         *PspLv2Dir;
  UINT32                Ignored;
  UINTN                 i;
  BOOLEAN               Lv2DirExist;
  BOOLEAN               Lv2DirValid;
  UINT64                Level2EntryAddress;
  UINT32                IgnoredEntrySize;
  PSP_DIRECTORY_ENTRY_TYPE EntryTypeValue;

  PspDir = NULL;
  PspLv2Dir = NULL;
  Lv2DirExist = FALSE;
  Lv2DirValid = FALSE;
  Level2EntryAddress = 0;
  EntryTypeValue.Value= EntryType;

  if (GetDirBase ((UINT32 *)&PspDir, &Ignored) != TRUE) {
    return FALSE;
  }
  //Check the existence of Level 2 DIR
  if (EntryType != PSP_DIR_LV2) {
    Lv2DirExist = PSPEntryInfoV2 (PSP_DIR_LV2, &Level2EntryAddress, &IgnoredEntrySize);
  }
  //Try to load entry from level2 if exist
  if (Lv2DirExist) {
    PspLv2Dir = (PSP_DIRECTORY *) (UINTN) Level2EntryAddress;
    Lv2DirValid = ValidatePspDir (PspLv2Dir, PSP_LV2_DIRECTORY_HEADER_SIGNATURE);
    if (Lv2DirValid) {
      for (i = 0; i < PspLv2Dir->Header.TotalEntries; i++) {
        if ((PspLv2Dir->PspEntry[i].Type.Field.Type == EntryTypeValue.Field.Type) && 
            (PspLv2Dir->PspEntry[i].Type.Field.SubProgram == EntryTypeValue.Field.SubProgram)) {
          *EntryAddress = FORCE_SPIADDR_BIT24 (PspLv2Dir->PspEntry[i].Location);
          *EntrySize = PspLv2Dir->PspEntry[i].Size;
          return (TRUE);
        }
      }
    }
  }

  // If level 2 not exist, or can't find according entry in level 2, try in Level 1
  for (i = 0; i < PspDir->Header.TotalEntries; i++) {
  if ((PspDir->PspEntry[i].Type.Field.Type == EntryTypeValue.Field.Type) && 
            (PspDir->PspEntry[i].Type.Field.SubProgram == EntryTypeValue.Field.SubProgram)) {
    *EntryAddress = FORCE_SPIADDR_BIT24 (PspDir->PspEntry[i].Location);
    *EntrySize = PspDir->PspEntry[i].Size;
    return (TRUE);
  }
}

  return (FALSE);
}

/**
 * Get PSP Entry SCS binary information
 *
 *
 *
 * @param[in,out] EntryAddress        Address of SCS binary
 * @param[in,out] EntrySize           Size of the SCS binary
 */
BOOLEAN
GetPspEntryScsBinaryV2 (
  IN OUT   UINT64                      *EntryAddress,
  IN       UINT32                      *EntrySize
  )
{
  return PSPEntryInfoV2 (AMD_SCS_BINARY, EntryAddress, EntrySize);
}

/**
 * Get PSP Entry PSP NV data information
 *
 *
 *
 * @param[in,out] EntryAddress        Address of PSP NV data
 * @param[in,out] EntrySize           Size of the PSP NV data
 */
BOOLEAN
GetPspEntryPspNvDataV2 (
  IN OUT   UINT64                      *EntryAddress,
  IN       UINT32                      *EntrySize
  )
{
  return PSPEntryInfoV2 (PSP_NV_DATA, EntryAddress, EntrySize);
}


/**
 *
 *  Get BIOS Directory Entry 's properties
 *
 *  @param[in]     EntryType    BIOS Directory Entry type
 *  @param[in]     EntryInstance    If input with INSTANCE_IGNORED, will return 1st Entry type matched
 *                                  If input with Non INSTANCE_IGNORED, will return the entry which both Type & Instance matched
 *  @param[in,out] TypeAttrib   TypeAttrib of entry
 *  @param[in,out] EntryAddress Address of entry
 *  @param[in,out] EntrySize    Size of entry
 *  @param[in,out] EntryDest    Destination of entry
 *
 *  @retval TRUE   Success to get the Entry 's properties
 *  @retval FALSE  Fail to get the Entry 's properties
 *
 **/
BOOLEAN
BIOSEntryInfo (
  IN       UINT8                       EntryType,
  IN       UINT8                       EntryInstance,
  IN OUT   TYPE_ATTRIB                 *TypeAttrib,
  IN OUT   UINT64                      *EntryAddress,
  IN OUT   UINT32                      *EntrySize,
  IN OUT   UINT64                      *EntryDest
  )
{
  BIOS_DIRECTORY        *BiosDir;
  BIOS_DIRECTORY        *BiosLv2Dir;
  UINT32                Ignored;
  UINTN                 i;
  BOOLEAN               Found;
  BOOLEAN               Lv2DirExist;
  BOOLEAN               Lv2DirValid;
  UINT64                Level2EntryAddress;
  TYPE_ATTRIB           IgnoredTypeAttrib;
  UINT32                IgnoredEntrySize;
  UINT64                IgnoredEntryDest;

  BiosDir = NULL;
  BiosLv2Dir = NULL;
  Lv2DirExist = FALSE;
  Lv2DirValid = FALSE;
  Level2EntryAddress = 0;
  Found = FALSE;

  if (GetDirBase (&Ignored, (UINT32 *)&BiosDir) != TRUE) {
    return FALSE;
  }

  //Check the existence of Level 2 DIR
  if (EntryType != BIOS_DIR_LV2) {
    Lv2DirExist = BIOSEntryInfo (BIOS_DIR_LV2, INSTANCE_IGNORED, &IgnoredTypeAttrib, &Level2EntryAddress, &IgnoredEntrySize, &IgnoredEntryDest);
  }

  //Try to load entry from level2 if exist
  if (Lv2DirExist) {
    BiosLv2Dir = (BIOS_DIRECTORY *) (UINTN) Level2EntryAddress;
    Lv2DirValid = ValidateBiosDir (BiosLv2Dir, BIOS_LV2_DIRECTORY_HEADER_SIGNATURE);
    if (Lv2DirValid) {
      for (i = 0; i < BiosLv2Dir->Header.TotalEntries; i++) {
        if (BiosLv2Dir->BiosEntry[i].TypeAttrib.Type == EntryType) {
          if (EntryInstance == INSTANCE_IGNORED) {
            Found = TRUE;
          } else if (BiosLv2Dir->BiosEntry[i].TypeAttrib.Instance == EntryInstance) {
            Found = TRUE;
          }
          if (Found == TRUE) {
            *TypeAttrib = BiosLv2Dir->BiosEntry[i].TypeAttrib;
            *EntryAddress = FORCE_SPIADDR_BIT24 (BiosLv2Dir->BiosEntry[i].Location);
            *EntrySize = BiosLv2Dir->BiosEntry[i].Size;
            *EntryDest = BiosLv2Dir->BiosEntry[i].Destination;
            return (TRUE);
          }
        }
      }
    }
    Found = FALSE;
  }
  // If level 2 not exist, or can't find according entry in level 2, try in Level 1
  Found = FALSE;
  for (i = 0; i < BiosDir->Header.TotalEntries; i++) {
    if (BiosDir->BiosEntry[i].TypeAttrib.Type == EntryType) {
      if (EntryInstance == INSTANCE_IGNORED) {
        Found = TRUE;
      } else if (BiosDir->BiosEntry[i].TypeAttrib.Instance == EntryInstance) {
        Found = TRUE;
      }
      if (Found == TRUE) {
        *TypeAttrib = BiosDir->BiosEntry[i].TypeAttrib;
        *EntryAddress = FORCE_SPIADDR_BIT24 (BiosDir->BiosEntry[i].Location);
        *EntrySize = BiosDir->BiosEntry[i].Size;
        *EntryDest = BiosDir->BiosEntry[i].Destination;
        return (TRUE);
      }
    }
  }

  return (FALSE);
}
/**
  Check if PSP device is present

  @retval BOOLEAN  0: PSP Disabled, 1: PSP Enabled

**/
BOOLEAN
CheckPspDevicePresentV2 (
  VOID
  )
{
  ///@todo Add code to read SMU FUSE shadow register
  return (TRUE);
}

/**
  Check PSP Platform Seucre Enable State
  HVB & Secure S3 (Resume vector set to Dram, & core content will restore by uCode)
  will be applied if Psp Plaform Secure is enabled

  @retval BOOLEAN  0: PSP Platform Secure Disabled, 1: PSP Platform Secure  Enabled

**/
BOOLEAN
CheckPspPlatformSecureEnableV2 (
  VOID
  )
{
  ///@todo Add code to read SMU FUSE shadow register
  return (TRUE);
}

/**
  Return the PspMbox MMIO location


  @retval EFI_STATUS  0: Success, NonZero Error

**/
BOOLEAN
GetPspMboxLocation (
  IN OUT   PSP_MBOX_V2 **PspMbox
  )
{
  UINT32               PspMmioBase;

  if (GetPspMmioBase (&PspMmioBase) == FALSE) {
    return FALSE;
  }

  *PspMbox = (PSP_MBOX_V2 *) (UINTN) (PspMmioBase + C2P_REG_OFFSET + BIOS_MAILBOX_BASE);
  return TRUE;
}

/**
  Check PSP Recovery Flag
  Target will set Recovery flag if some PSP entry point by PSP directory has been corrupted.

  @retval BOOLEAN  0: Recovery Flag is cleared, 1: Recovery Flag has been set

**/
BOOLEAN
CheckPspRecoveryFlagV2 (
  VOID
  )
{
  PSP_MBOX_V2 *PspMbox;

  PspMbox = NULL;

  if (PcdGetBool (PcdAmdPspRecoveryFlagDetectEnable) == FALSE) {
    return FALSE;
  }
  //Init PSP MMIO
  PspBarInitEarlyV2 ();
  //NOTE, GetPspMboxLocation is reading the address from index will have the potential multiple core racinng issue
  GetPspMboxLocation (&PspMbox);

  return (BOOLEAN) (PspMbox->Cmd.Field.Recovery);
}

VOID
PspBarInitEarlyV2 (
  VOID
  )
{
  UINT32 Value32;
  UINT64 PspMmioBase;
  UINTN  PciAddress;
  UINT64 Length;
  FABRIC_TARGET MmioTarget;
  EFI_STATUS Status;
  FABRIC_MMIO_ATTRIBUTE Attributes;
  UINT32 SmnBase;

  SmnBase = 0;
  if ((CcxIsBsp (NULL) == FALSE)) {
    return;
  }
  //Check if PSP BAR has been assigned, if not do the PSP BAR initialation
  if (GetPspMmioBase (&Value32) == FALSE) {
    //Allocate MMIO Region from MMIO manager
    Length = PSP_BAR_SIZE;
    MmioTarget.TgtType = TARGET_RB;
    MmioTarget.SocketNum = 0;
    MmioTarget.RbNum = 0;
    Attributes.ReadEnable = 1;
    Attributes.WriteEnable = 1;
    Attributes.NonPosted = 0;
    Attributes.MmioType = NON_PCI_DEVICE_BELOW_4G;
    PspMmioBase  = 0;
    Status = FabricAllocateMmio (&PspMmioBase, &Length, ALIGN_1M, MmioTarget, &Attributes);
    ASSERT (Status == EFI_SUCCESS );
    if (EFI_ERROR (Status)) {
      IDS_HDT_CONSOLE_PSP_TRACE ("PspBarInitEarlyV2 Allocate MMIO Fail\n");
    } else {
      IDS_HDT_CONSOLE_PSP_TRACE ("PspBarInitEarlyV2 Allocate MMIO @0x%lx\n", PspMmioBase);
    }
    SmnBase = NBMSIC_SMN_BASE;
    if (SocFamilyIdentificationCheck (F17_MTS_RAW_ID)) {
      SmnBase = MTS_NBMISC_SMN_BASE;
    }
    //Set PSP BASE Address in NBMISC, and enable lock the MMIO
    PciAddress = NB_SMN_INDEX_2_PCI_ADDR;
    Value32 = SmnBase + NBMSIC_PSP_BASE_ADDR_LO_OFFSET;
    PciWrite32 (PciAddress, Value32);
    PciAddress = NB_SMN_DATA_2_PCI_ADDR;
    Value32 = (UINT32) (PspMmioBase | (BIT0 + BIT8));
    PciWrite32 (PciAddress, Value32);

    PciAddress = NB_SMN_INDEX_2_PCI_ADDR;
    Value32 = SmnBase + NBMSIC_PSP_BASE_ADDR_HI_OFFSET;
    PciWrite32 (PciAddress, Value32);
    PciAddress = NB_SMN_DATA_2_PCI_ADDR;
    Value32 = (UINT32) RShiftU64 (PspMmioBase, 32);
    PciWrite32 (PciAddress, Value32);
  }
}

/**
  Return the PspMMIO MMIO location

  @param[in] PspMmioBase Pointer to Psp MMIO address

  @retval BOOLEAN  0: Error, 1 Success
**/
BOOLEAN
GetPspMmioBase (
  IN OUT   UINT32 *PspMmioBase
  )
{
  UINT32    Value32;
  UINTN     PciAddress;
  UINT32    SmnBase;

  *PspMmioBase = 0;

  SmnBase = NBMSIC_SMN_BASE;
  if (SocFamilyIdentificationCheck (F17_MTS_RAW_ID)) {
    SmnBase = MTS_NBMISC_SMN_BASE;
  }

  PciAddress = NB_SMN_INDEX_2_PCI_ADDR;
  Value32 = SmnBase + NBMSIC_PSP_BASE_ADDR_LO_OFFSET;
  PciWrite32 (PciAddress, Value32);
  PciAddress = NB_SMN_DATA_2_PCI_ADDR;
  Value32 = PciRead32 (PciAddress);
  //Mask out the lower bits
  Value32 &= 0xFFF00000;

  if (Value32 == 0) {
    return (FALSE);
  }

  *PspMmioBase = Value32;
  return (TRUE);
}

///@todo remove below FCH definition when it has been declared by FCH module
#define ACPI_MMIO_BASE  0xFED80000ul
#define PMIO_BASE       0x300   // DWORD
#define FCH_PMIOA_REG64          0x64         // AcpiPmTmrBlk
/**
 * PSP Time out function with conditioner
 * The routine will exit in two conditions:
 * 1. Time out of input uSec
 * 2. Conditioner function return TRUE
 *
 * @param[in] uSec         Timer in microseconds
 * @param[in] Conditioner  Function for check condition of exit the timeout routine
 * @param[in] Context      Conditioner function context
 *
 * @retval BOOLEAN  FALSE: Timer exceed, TRUE: condition match
 */
BOOLEAN
PspLibTimeOutV2 (
  IN       UINT64              uSec,
  IN       FP_CONDITIONER      Conditioner,
  IN       VOID                *Context
  )
{
  UINT16 timerAddr;
  UINT32 startTime;
  UINT64 elapsedTime;

  // Return immediately if condition already match
  if (Conditioner (Context) == TRUE) {
    return TRUE;
  }

  //Check if infinitely flag set
  if (uSec == PSPLIB_WAIT_INFINITELY) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Wait infinitely ..\n");
    while (Conditioner (Context) == FALSE) {
      ;
    }
    return TRUE;
  }

  //Check availibitly of ACPI timer
  LibAmdMemRead (AccessWidth16, (UINT64) (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG64), &timerAddr, NULL);
  //Using IO delay, if ACPI timer is not available, it is not accurate, since the conditioner function will take time
  if ( timerAddr == 0 ) {
    uSec = DivU64x32 (uSec, 2);
    while ( uSec != 0) {
      if (Conditioner (Context) == TRUE) {
        return TRUE;
      }
      LibAmdIoRead (AccessWidth8, 0xEB, (UINT8*)&elapsedTime, NULL);
      uSec--;
    }
  } else {
    LibAmdIoRead (AccessWidth32, timerAddr, &startTime, NULL);
    elapsedTime = 0;
    for ( ;; ) {
      LibAmdIoRead (AccessWidth32, timerAddr, &elapsedTime, NULL);
      if ( elapsedTime <= startTime ) {
        elapsedTime = elapsedTime + 0xFFFFFFFFul - startTime;
      } else {
        elapsedTime = elapsedTime - startTime;
      }

      if (Conditioner (Context) == TRUE) {
        return TRUE;
      }

      if (DivU64x32 ( MultU64x32 (elapsedTime, 28), 100 ) > uSec ) {
        break;
      }
    }
  }
  return FALSE;
}

BOOLEAN
GetFtpmControlAreaV2 (
  IN OUT   VOID **FtpmControlArea
  )
{
  UINT32               PspMmioBase;

  if (GetPspMmioBase (&PspMmioBase) == FALSE) {
    return FALSE;
  }

  *FtpmControlArea = (VOID *) (UINTN) (PspMmioBase + C2P_REG_OFFSET);
  return TRUE;
}

VOID
SwitchPspMmioDecodeV2 (
  IN       BOOLEAN SwitchFlag,
  IN OUT   UINT32 *RegisterCopy
  )
{
}


/**
 * Acquire the Mutex for access PSP,X86 co-accessed register
 * Call this routine before access SMIx98 & SMIxA8
 *
 */
VOID
AcquirePspSmiRegMutexV2 (
  VOID
  )
{
  UINT32 PspMmioBase;
  UINT32 BiosMutex;
  UINT32 PspMutex;
  UINT32 Turn;

  PspMmioBase = 0;
  if (GetPspMmioBase (&PspMmioBase)) {
    BiosMutex = PspMmioBase + C2P_REG_OFFSET + BIOS_MUTEX_OFFSET;
    PspMutex = PspMmioBase + C2P_REG_OFFSET + PSP_MUTEX_OFFSET;
    Turn = PspMmioBase + C2P_REG_OFFSET + MUTEX_TURN_OFFSET;
    *(volatile UINT32*)(UINTN)(BiosMutex) = 1;
    *(volatile UINT32*)(UINTN)(Turn) = 1;
    //Wait till PSP FW release the mutex
    while ((*(volatile UINT32*)(UINTN)(PspMutex) == 1) && (*(volatile UINT32*)(UINTN)(Turn) == 1)) {
      ;
    }
  }
}
/**
 * Release the Mutex for access PSP,X86 co-accessed register
 * Call this routine after access SMIx98 & SMIxA8
 *
 */
VOID
ReleasePspSmiRegMutexV2 (
  VOID
  )
{
  UINT32 PspMmioBase;
  UINT32 BiosMutex;


  PspMmioBase = 0;
  if (GetPspMmioBase (&PspMmioBase)) {
    BiosMutex = PspMmioBase + C2P_REG_OFFSET + BIOS_MUTEX_OFFSET;
    *(volatile UINT32*)(UINTN)(BiosMutex) = 0;
  }
}

/**
 * Get PsbHstiStatus from C2P register
 *
 */
BOOLEAN
GetPsbStatus2 (
  PSB_STATUS_2 *PsbStatus2
  )
{
  PSB_STATUS_2 *C2pReg37;
  UINT32            PspMmioBase;

  PspMmioBase = 0;
  if (GetPspMmioBase (&PspMmioBase) == FALSE) {
    return FALSE;
  }
  // MP0_C2PMSG_37 register address is different between family
  if (SocFamilyIdentificationCheck (F17_ZP_RAW_ID)) {
    C2pReg37 = (PSB_STATUS_2 *) (UINTN) (PspMmioBase + 0x10594);
  } else {
    C2pReg37 = (PSB_STATUS_2 *) (UINTN) (PspMmioBase + 0x10994);
  }

  CopyMem (PsbStatus2, C2pReg37, sizeof (PSB_STATUS_2));
  return TRUE;
}

/**
 * Get PsbHstiStatus from C2P register
 *
 */
BOOLEAN
GetPsbHstiStatus1 (
  PSB_HSTI_STATUS_1 *PsbHstiStatus1
  )
{
  PSB_HSTI_STATUS_1 *C2pReg38;
  UINT32            PspMmioBase;

  PspMmioBase = 0;
  if (GetPspMmioBase (&PspMmioBase) == FALSE) {
    return FALSE;
  }
  // MP0_C2PMSG_38 register address is different between family
  if (SocFamilyIdentificationCheck (F17_ZP_RAW_ID)) {
    C2pReg38 = (PSB_HSTI_STATUS_1 *) (UINTN) (PspMmioBase + 0x10598);
  } else {
    C2pReg38 = (PSB_HSTI_STATUS_1 *) (UINTN) (PspMmioBase + 0x10998);
  }

  CopyMem (PsbHstiStatus1, C2pReg38, sizeof (PSB_HSTI_STATUS_1));
  return TRUE;
}