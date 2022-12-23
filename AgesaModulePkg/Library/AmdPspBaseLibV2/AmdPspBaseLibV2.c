/*
 ******************************************************************************
 *
 * Copyright (C) 2008-2022 Advanced Micro Devices, Inc. All rights reserved.
 *
 *******************************************************************************
 **/
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
#include <Library/FchBaseLib.h>
#include <Library/FchSpiAccessLib.h>
//#include <FchBiosRamUsage.h>
#include <Library/AmdHeapLib.h>
#include <Library/SmnAccessLib.h>

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

#define BIOS_DIR_EFS_OFFSET_IGNORE  0xFFFFFFFFul   //Ignored
#define ISH_VERSION_1         1   //1: IMAGE_SLOT_HEADER version 1, IMAGE_SLOT_HEADER
#define ISH_VERSION_2         2   //1: IMAGE_SLOT_HEADER version 2, IMAGE_SLOT_HEADER_V2
#define ISH_VERSION_IGNORE    0xFFFFFFFFul   //Ignored

/// Structure to store Directory related information
typedef struct {
  UINT32                  FamilyRawId;          //CpuId.0x80000001.EAX_Reg & RAW_FAMILY_ID_MASK;
  UINT32                  PspId;                //Id defined by bootrom
  UINT32                  BiosDirEfsOffset;     //Used in the previous programs, when combo BIOS dir and A/B recovery is not supported, check BiosDirBase in FIRMWARE_ENTRY_TABLEV2
  BOOLEAN                 ComboBisoDirSupport;  //TRUE: Combo Dir supported, FALSE: Combo Dir not supported
  UINT32                  IshStructVersion;     //Version for ISH structure, 1: IMAGE_SLOT_HEADER, 2: IMAGE_SLOT_HEADER_V2, 0xFFFFFFF, ignored
  RECOVERY_REASON_VERSION RecoveryReasonVersion;//Version for Recovery Reason, 1: RECOVERY_REASON_VERSION_1, 2: RECOVERY_REASON_VERSION_2, 0xFFFFFFF, ignored
} DIR_INFO;


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
/// Table to store all supported program directory infomation
DIR_INFO mDirInfoTbl[] = {
  {F19_RMB_RAW_ID, RMB_PSP_CHIP_ID, BIOS_DIR_EFS_OFFSET_IGNORE,                        FALSE, ISH_VERSION_2,      RECOVERY_REASON_VERSION_2},
  {F19_VMR_RAW_ID, VMR_PSP_CHIP_ID, OFFSET_OF(FIRMWARE_ENTRY_TABLEV2, SspBiosDirBase), FALSE, ISH_VERSION_IGNORE, RECOVERY_REASON_VERSION_1},
  {F19_CZN_RAW_ID, CZN_PSP_CHIP_ID, OFFSET_OF(FIRMWARE_ENTRY_TABLEV2, NewBiosDirBase), TRUE,  ISH_VERSION_IGNORE, RECOVERY_REASON_VERSION_1},
  {F19_BA_RAW_ID,  BA_PSP_CHIP_ID,  OFFSET_OF(FIRMWARE_ENTRY_TABLEV2, SspBiosDirBase), FALSE, ISH_VERSION_IGNORE, RECOVERY_REASON_VERSION_IGNORE},
  {F19_GN_RAW_ID,  GN_PSP_CHIP_ID,  OFFSET_OF(FIRMWARE_ENTRY_TABLEV2, NewBiosDirBase), FALSE, ISH_VERSION_IGNORE, RECOVERY_REASON_VERSION_IGNORE},
  {F17_VN_RAW_ID,  VN_PSP_CHIP_ID,  BIOS_DIR_EFS_OFFSET_IGNORE,                        TRUE,  ISH_VERSION_1,      RECOVERY_REASON_VERSION_2},
  {F17_MR_RAW_ID,  MR_PSP_CHIP_ID,  BIOS_DIR_EFS_OFFSET_IGNORE,                        TRUE,  ISH_VERSION_1,      RECOVERY_REASON_VERSION_2},
  {F17_RN_RAW_ID,  RN_PSP_CHIP_ID,  OFFSET_OF(FIRMWARE_ENTRY_TABLEV2, NewBiosDirBase), TRUE,  ISH_VERSION_IGNORE, RECOVERY_REASON_VERSION_1},
  {F17_ZP_RAW_ID,  ZP_PSP_CHIP_ID,  OFFSET_OF(FIRMWARE_ENTRY_TABLEV2, ZpBiosDirBase),  FALSE, ISH_VERSION_IGNORE, RECOVERY_REASON_VERSION_IGNORE},
  {F17_RV_RAW_ID,  RV_PSP_CHIP_ID,  OFFSET_OF(FIRMWARE_ENTRY_TABLEV2, RvBiosDirBase),  FALSE, ISH_VERSION_IGNORE, RECOVERY_REASON_VERSION_IGNORE},
  {F17_PIC_RAW_ID, RV_PSP_CHIP_ID,  OFFSET_OF(FIRMWARE_ENTRY_TABLEV2, RvBiosDirBase),  FALSE, ISH_VERSION_IGNORE, RECOVERY_REASON_VERSION_IGNORE},
  {F17_RV2_RAW_ID, RV2_PSP_CHIP_ID, OFFSET_OF(FIRMWARE_ENTRY_TABLEV2, RvBiosDirBase),  FALSE, ISH_VERSION_IGNORE, RECOVERY_REASON_VERSION_IGNORE},
  {F17_MTS_RAW_ID, MTS_PSP_CHIP_ID, OFFSET_OF(FIRMWARE_ENTRY_TABLEV2, SspBiosDirBase), FALSE, ISH_VERSION_IGNORE, RECOVERY_REASON_VERSION_IGNORE},
  {F17_SSP_RAW_ID, SSP_PSP_CHIP_ID, OFFSET_OF(FIRMWARE_ENTRY_TABLEV2, SspBiosDirBase), FALSE, ISH_VERSION_IGNORE, RECOVERY_REASON_VERSION_IGNORE},
};
/**
  Get DIR_INFO information according RAW_FAMILY_ID from mDirInfoTbl, return NULL if not found

  @retval return NULL if not found

**/
DIR_INFO *
GetDirInfoEntry (
  VOID
  )
{
  UINT32 i;
  DIR_INFO *DirInfoTblEntry;

  DirInfoTblEntry = NULL;
  for (i = 0; i < (sizeof (mDirInfoTbl)/ sizeof (DIR_INFO)); i++) {
    if (SocFamilyIdentificationCheck (mDirInfoTbl[i].FamilyRawId)) {
      DirInfoTblEntry = &mDirInfoTbl[i];
      break;
    }
  }
  return DirInfoTblEntry;
}

/**
  This function is to calculate the crc checksum

  @param[in]  pointer to content
  @param[in]  length of content

  @retval CRC value

**/
UINT32
Fletcher32 (
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
GetHeapBufferByHandle (
  IN      UINT32  BufferHandle,                    ///< An unique ID of buffer.
  IN      UINT32  BufferSize,                      ///< Data buffer size.
  IN OUT  UINT8   **BufferPtr                       ///< Pointer to buffer.
  )
{
  ALLOCATE_HEAP_PARAMS        AllocHeapParams;
  LOCATE_HEAP_PTR             LocateHeapParams;
  AGESA_STATUS                AgesaStatus;
  //Get buffer allocated in heap
  LocateHeapParams.BufferHandle = BufferHandle;
  if (HeapLocateBuffer (&LocateHeapParams, NULL) == AGESA_SUCCESS) {
    *BufferPtr = LocateHeapParams.BufferPtr;
  } else {
    //Allocate Heap buffer for PSP directory
    AllocHeapParams.RequestedBufferSize = BufferSize;
    AllocHeapParams.BufferHandle        = BufferHandle;
    AllocHeapParams.Persist             = HEAP_BOOTTIME_SYSTEM_MEM;
    AgesaStatus = HeapAllocateBuffer (&AllocHeapParams, NULL);
    ASSERT (AgesaStatus == AGESA_SUCCESS);
    if (AgesaStatus != AGESA_SUCCESS) {
      return FALSE;
    }
    *BufferPtr = AllocHeapParams.BufferPtr;
  }
  return TRUE;
}

BOOLEAN
IsPspDirAddrRom2Decoded (
  IN      UINT64                      EntryLocation
  )
{
  if (PcdGetBool (PcdPspDirUsing16MAddress) == TRUE) {
      return TRUE;
  } else if (IsRom2Decoded (EntryLocation)) {
      return TRUE;
  } else {
      return FALSE;
  }
}

UINT64
TryToTranslateOffsetToPhysicalAddress (
  IN      UINT64                      EntryLocation
  )
{
 if (IS_SPI_OFFSET (EntryLocation)) {
      if (IsPspDirAddrRom2Decoded (EntryLocation)) {
         EntryLocation = FORCE_SPIADDR_BIT24 (EntryLocation);
      }
  }
  return EntryLocation;
}

UINT64
TranslateEntryLocation (
  IN       UINT64                      EntryLocation,
  IN       UINT64                      DirectoryHdrAddr,
  IN       UINT32                      ImageSlotAddr    //if no image slot header, just leave it as 0
  )
{
  //address mode 1, relative to BIOS image base
  if (IS_ADDRESS_MODE_1 (EntryLocation)) {
      EntryLocation = EntryLocation & ~BIT62;
  } else if (IS_ADDRESS_MODE_2 (EntryLocation)) { //address mode 2, relative to current directory header
      EntryLocation = EntryLocation & ~BIT63;
      //get the relative offset compare to directory header
      EntryLocation += DirectoryHdrAddr;
  } else if (IS_ADDRESS_MODE_3 (EntryLocation)) { //address mode 3, relative to current image slot
      EntryLocation = EntryLocation & ~(BIT63 | BIT62);
      //get the relative offset compare to L2
      EntryLocation += ImageSlotAddr;
  }
  return TryToTranslateOffsetToPhysicalAddress (EntryLocation);
}

/**
 *
 *  Map SPI data to the Buffer,
 *  if SPI offset is specified, call FchSpiRomRead to get data, otherwise, access directly
 *
 *  @param[in]     Address    where to get the data, it may be a SPI offset or physical address
 *  @param[in,out] Buffer     where the data save to, the buffer must be allocated by the caller
 *  @param[in]     Size       how big the data is
 *
 *  @retval TRUE   Success to get the content from Address
 *  @retval FALSE  Fail to get the content from Address
 *
 **/
BOOLEAN
MapSpiDataToBuffer (
  IN       UINT32                      Address,
  IN OUT   VOID                        *Buffer,
  IN       UINT32                      Size
  )
{
  ZeroMem(Buffer, Size);
  if (FchSpiRomReadEx (Address, Buffer, Size) != TRUE) {
    return FALSE;
  }
  return TRUE;
}

/**
  This function is to validate PSP directory address on signature and crc checksum

  @param[in]  pointer to PSP directory base
  @param[in]  value of the signaure

  @retval TRUE            the PSP directory base address is valid.
  @retval FALSE           the PSP directory base address is not valid.

**/
BOOLEAN
ValidatePspDir (
  IN       PSP_DIRECTORY     *PspDir,
  IN       UINT32            Signature
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
  if (PspComboDir->Header.PspCookie != PSP_COMBO_DIRECTORY_COOKIE) {
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

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function checks if the CPU/APU is Zen 2 or later (starting from Family 17 Model 30h)
 *
 *     @return          TRUE -  Zen 2 or later SOC.
 *     @return          FALSE - Zen 1 SOC or previous CPU/APU.
 */
BOOLEAN
IsZen2OrLater (
  VOID
  )
{
  CPUID_DATA    CpuId;
  UINT32        Family;
  UINT32        Model;
  AsmCpuid (
      AMD_CPUID_FMF,
      &(CpuId.EAX_Reg),
      &(CpuId.EBX_Reg),
      &(CpuId.ECX_Reg),
      &(CpuId.EDX_Reg)
      );

  Family = (((CpuId.EAX_Reg & CPUID_EXT_FAMILY_MASK) >> 20) + ((CpuId.EAX_Reg & CPUID_BASE_FAMILY_MASK) >> 8));
  Model = (((CpuId.EAX_Reg & CPUID_EXT_MODEL_MASK) >> 12) | ((CpuId.EAX_Reg & CPUID_BASE_MODEL_MASK) >> 4));

  if ((Family == 0x17 && Model >= 0x30) || (Family > 0x17)) {
      return TRUE;
  } else {
      return FALSE;
  }
}

BOOLEAN
ShouldFirstGenEfsBeIgnored (
  IN FIRMWARE_ENTRY_TABLEV2      *FirmwareTableBase
  )
{
  BOOLEAN    FirstGenFfsStructure;
  FirstGenFfsStructure = FALSE;
  //check if it's first generation of EFS structure
  if ((FirmwareTableBase->Config & 0xFF) == 0xFF) {
      FirstGenFfsStructure = TRUE;
  }

  if (FirstGenFfsStructure && IsZen2OrLater ()) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  This function is to get the PSP level 2 directory buffer.

  @param[out]  pointer to PSP level 2 directory base

  @retval TRUE            Successfully get the valid PSP level 2 directory.
  @retval FALSE           Valid PSP level 2 directory is not found.

**/
BOOLEAN
GetPspLv2DirBaseV2 (
  IN       UINT64             PspLevel2BaseAddress,
  IN OUT   PSP_DIRECTORY     **PspLv2Dir
  )
{
  BOOLEAN                  PspDirValid;
  PSP_DIRECTORY            *PspRegionDir;
  UINT8                    *PspDirBuffer;

  PspDirValid = FALSE;
  PspRegionDir = NULL;
  PspDirBuffer = NULL;
  if (PspLevel2BaseAddress != 0) {
    if (GetHeapBufferByHandle (AMD_PSP_L2_DIRECTORY_BUFFER_HANDLE, MaxPspDirSize, &PspDirBuffer) != TRUE) {
      return FALSE;
    }

    // Get the PSP Dir
    if (MapSpiDataToBuffer ((UINT32)PspLevel2BaseAddress, PspDirBuffer, MaxPspDirSize) != TRUE) {
      return FALSE;
    }
    PspRegionDir = (PSP_DIRECTORY*)PspDirBuffer;


    PspDirValid = ValidatePspDir (PspRegionDir, PSP_LV2_DIRECTORY_HEADER_SIGNATURE);
    if (PspDirValid) {
      *PspLv2Dir = PspRegionDir;
      return TRUE;
    }
  }
  return FALSE;
}

/**
  This function is to search EFS structure and get the valid PSP L1 directory base address.

  @param[out]  pointer to PSP directory base

  @retval TRUE            Successfully get the valid PSP directory base address.
  @retval FALSE           Valid PSP directory is not found.

**/
BOOLEAN
GetPspDirBaseV2 (
  IN OUT   PSP_DIRECTORY     **PspDir
  )
{
  UINT32                      i;
  UINT32                      j;
  FIRMWARE_ENTRY_TABLEV2      FirmwareTableBase;
  UINT32                      PspChipId;
  BOOLEAN                     PspDirSigValid;
  UINT8                       *PspDirBuffer;
  UINT32                      PspDirBase;
  DIR_INFO                    *DirInfo;

  CONST UINT32 RomSigOffsetTable[] =  {
    0x020000,  //  --> 16MB base
    0x820000,  //  --> 8MB base
    0xC20000,  //  --> 4MB base
    0xE20000,  //  --> 2MB base
    0xF20000,  //  --> 1MB base
    0xFA0000   //  --> 512KB base
  };
  PspChipId = 0;
  PspDirBuffer = NULL;
  PspDirBase = 0;

  DirInfo = GetDirInfoEntry ();
  if (DirInfo == NULL) {
    //Unsupported Family detected
    ASSERT (FALSE);
    return (FALSE);
  }
  PspChipId = DirInfo->PspId;

  //search beyond ROM2 to find ROMSIG
  for (i = 0; i < 4; i++) {
    for (j = 0; j < sizeof (RomSigOffsetTable) / sizeof (UINT32); j++) {
      //Get the ROM SIG from SPI ROM
      if (FchSpiRomRead ((RomSigOffsetTable[j] + 0x1000000 * i), (UINT8 *)&FirmwareTableBase, sizeof (FIRMWARE_ENTRY_TABLEV2)) != TRUE) {
        ASSERT (FALSE);
        return FALSE;
      }
      // Search flash for unique signature 0x55AA55AA
      if (FirmwareTableBase.Signature  == FIRMWARE_TABLE_SIGNATURE) {
        if (ShouldFirstGenEfsBeIgnored (&FirmwareTableBase) == TRUE) {
          continue;
        }
        if (GetHeapBufferByHandle (AMD_PSP_DIRECTORY_BUFFER_HANDLE, MaxPspDirSize, &PspDirBuffer) != TRUE) {
          return FALSE;
        }
        if (MapSpiDataToBuffer (FirmwareTableBase.PspDirBase, PspDirBuffer, MaxPspDirSize) != TRUE) {
          return FALSE;
        }
        //Check if PSP combo structure
        if (GetComboDir ((UINT32)(UINTN)PspDirBuffer, PspChipId, &PspDirBase) == TRUE) {
          if(MapSpiDataToBuffer(PspDirBase, PspDirBuffer, MaxPspDirSize) != TRUE) {
            return FALSE;
          }
        }
        PspDirSigValid = FALSE;
        PspDirSigValid = ValidatePspDir ((PSP_DIRECTORY *) (UINTN)PspDirBuffer, PSP_DIRECTORY_HEADER_SIGNATURE);
        if (PspDirSigValid) {
          *PspDir = (PSP_DIRECTORY *) (UINTN)PspDirBuffer;
          return TRUE;
        } else {
          if (DirInfo->IshStructVersion == ISH_VERSION_2) {
            //Start from ISH version 2, it start to support PspDirBackupBase
            if (MapSpiDataToBuffer (FirmwareTableBase.PspDirBackupBase, PspDirBuffer, MaxPspDirSize) != TRUE) {
              return FALSE;
            }
            PspDirSigValid = ValidatePspDir ((PSP_DIRECTORY *) (UINTN)PspDirBuffer, PSP_DIRECTORY_HEADER_SIGNATURE);
            if (PspDirSigValid) {
              *PspDir = (PSP_DIRECTORY *) (UINTN)PspDirBuffer;
              return TRUE;
            } else {
              return FALSE;
            }
          } else {
            return FALSE;
          }
        }
      }
    }
  }
  return (FALSE);
}

/**
  This function is to get the BIOS level 2 directory buffer.

  @param[out]  pointer to BIOS level 2 directory base

  @retval TRUE            Successfully get the valid BIOS directory base address.
  @retval FALSE           Valid BIOS directory is not found.

**/
BOOLEAN
GetBiosLv2DirBaseV2 (
  IN       UINT64             BiosLevel2BaseAddress,
  IN OUT   BIOS_DIRECTORY     **BiosLv2Dir
  )
{
  BOOLEAN               BiosDirValid;
  UINT8                 *BiosDirBuffer;
  BIOS_DIRECTORY        *BiosDir;

  BiosDirValid = FALSE;
  BiosDirBuffer = NULL;
  BiosDir = NULL;

  if (BiosLevel2BaseAddress != 0) {
    // get buffer
    if (GetHeapBufferByHandle (AMD_PSP_L2_DIRECTORY_BUFFER_HANDLE, MaxPspDirSize, &BiosDirBuffer) != TRUE) {
      return FALSE;
    }

    // Get the Level2 Dir
    if (MapSpiDataToBuffer ((UINT32)BiosLevel2BaseAddress, BiosDirBuffer, MaxPspDirSize) != TRUE) {
      return FALSE;
    }

    BiosDir = (BIOS_DIRECTORY*)BiosDirBuffer;
    BiosDirValid = ValidateBiosDir (BiosDir, BIOS_LV2_DIRECTORY_HEADER_SIGNATURE);

    if (BiosDirValid) {
      *BiosLv2Dir = BiosDir;
      return TRUE;
    }
  }
  return FALSE;
}

/**
  This function is to get the BIOS Level 1 directory.

  @param[out]  pointer to BIOS directory base

  @retval TRUE            Successfully get the valid BIOS directory base address.
  @retval FALSE           Valid BIOS directory is not found.

**/
BOOLEAN
GetBiosDirBaseV2 (
  IN OUT   BIOS_DIRECTORY     **BiosDir
  )
{
  UINT32                      i;
  UINT32                      j;
  FIRMWARE_ENTRY_TABLEV2      FirmwareTableBase;
  UINT32                      FamilyId;
  UINT32                      PspChipId;
  BOOLEAN                     BiosDirSigValid;
  BOOLEAN                     ComboBisoDirSupport;
  UINT8                      *BiosDirBuffer;
  UINT32                      BiosDirBase;
  UINT32                      BiosDirEfsOffset;
  DIR_INFO                    *DirInfo;

  CONST UINT32 RomSigOffsetTable[] =  {
    0x020000,  //  --> 16MB base
    0x820000,  //  --> 8MB base
    0xC20000,  //  --> 4MB base
    0xE20000,  //  --> 2MB base
    0xF20000,  //  --> 1MB base
    0xFA0000   //  --> 512KB base
  };

  FamilyId = 0;
  PspChipId = 0;
  ComboBisoDirSupport = FALSE;
  BiosDirBuffer = NULL;
  BiosDirBase = 0;
  BiosDirEfsOffset = 0;

  DirInfo = GetDirInfoEntry ();
  if (DirInfo == NULL) {
    //Unsupported Family detected
    ASSERT (FALSE);
    return (FALSE);
  }
  PspChipId = DirInfo->PspId;
  ComboBisoDirSupport = DirInfo->ComboBisoDirSupport;
  BiosDirEfsOffset = DirInfo->BiosDirEfsOffset;
  //search beyond ROM2 to find ROMSIG
  for (i = 0; i < 4; i++) {
    for (j = 0; j < sizeof (RomSigOffsetTable) / sizeof (UINT32); j++) {
      //Get the ROM SIG from SPI ROM
      if (FchSpiRomRead ((RomSigOffsetTable[j] + 0x1000000 * i), (UINT8 *)&FirmwareTableBase, sizeof (FIRMWARE_ENTRY_TABLEV2)) != TRUE) {
        return FALSE;
      }
      // Search flash for unique signature 0x55AA55AA
      if (FirmwareTableBase.Signature  == FIRMWARE_TABLE_SIGNATURE) {
        if (ShouldFirstGenEfsBeIgnored (&FirmwareTableBase) == TRUE) {
            continue;
         }

        BiosDirBase = *((UINT32 *) ((UINT8 *)&FirmwareTableBase + BiosDirEfsOffset));
        if (GetHeapBufferByHandle (AMD_PSP_DIRECTORY_BUFFER_HANDLE, MaxPspDirSize, &BiosDirBuffer) != TRUE) {
          return FALSE;
        }

        //If support Combo BIOS directory, try to get from combo 1st
        if (ComboBisoDirSupport) {
          //Get the BIOS COMBO Dir
          if (MapSpiDataToBuffer (FirmwareTableBase.NewBiosDirBase, BiosDirBuffer, MaxPspDirSize) != TRUE) {
            return FALSE;
          }
          GetComboDir ((UINT32)(UINTN)BiosDirBuffer, PspChipId, &BiosDirBase);
        }

        //Get the BIOS Dir
        if (MapSpiDataToBuffer (BiosDirBase, BiosDirBuffer, MaxPspDirSize) != TRUE) {
          return FALSE;
        }

        BiosDirSigValid = FALSE;
        BiosDirSigValid = ValidateBiosDir ((BIOS_DIRECTORY *) (UINTN)BiosDirBuffer, BIOS_DIRECTORY_HEADER_SIGNATURE);
        ASSERT (BiosDirSigValid);
        if (BiosDirSigValid) {
          *BiosDir = (BIOS_DIRECTORY *)(UINTN)BiosDirBuffer;
          return TRUE;
        } else {
          return FALSE;
        }
      }
    }
  }
  return (FALSE);
}

/**
  This function is to check if PSP AB recovery layout is supported or not

  @param[in]   pointer to PSP directory base
  @param[out]  pointer to PSP region A base
  @param[out]  pointer to PSP region B base

  @retval TRUE            PSP AB recovery is supported
  @retval FALSE           PSP AB recovery is not supported

**/
BOOLEAN
IsABrecovery (
  IN         PSP_DIRECTORY               *PspDir,
  IN OUT     UINT64                      *PspRegionAEntryAddress,
  IN OUT     UINT64                      *PspRegionBEntryAddress
)
{
  UINT64                  TempPspRegionAEntryAddress = 0;
  UINT64                  TempPspRegionBEntryAddress = 0;
  BOOLEAN                 PspRegionAEntryExist = FALSE;
  BOOLEAN                 PspRegionBEntryExist = FALSE;
  UINTN                   i;

  if (PspDir == NULL) {
    return FALSE;
  }

  //Check Entry 0x48, 0x4A
  for (i = 0; i < PspDir->Header.TotalEntries; i++) {
    if (PspDir->PspEntry[i].Type.Field.Type == PSP_REGION_A_DIR) {
      TempPspRegionAEntryAddress = PspDir->PspEntry[i].Location;
      PspRegionAEntryExist = TRUE;
    } else if (PspDir->PspEntry[i].Type.Field.Type == PSP_REGION_B_DIR) {
      TempPspRegionBEntryAddress = PspDir->PspEntry[i].Location;
      PspRegionBEntryExist = TRUE;
    }
    //AB recovery must have both type PSP_REGION_A_DIR and PSP_REGION_B_DIR
    if (PspRegionAEntryExist && PspRegionBEntryExist) {
      *PspRegionAEntryAddress = TempPspRegionAEntryAddress;
      *PspRegionBEntryAddress = TempPspRegionBEntryAddress;
      return TRUE;
    }
  }

  return FALSE;
}

/**
 *
 *  Get PSP Directory Entry 's properties from Level 2
 *
 *  @param[in]     EntryType        BIOS Directory Entry type
 *  @param[in]     PspLevel2BaseAddress  The PSP Level 2 Directory base address
 *  @param[in,out] EntrySize        Size of entry
 *  @param[in,out] EntryDest        Destination of entry
 *
 *  @retval TRUE   Success to get the Entry 's properties
 *  @retval FALSE  Fail to get the Entry 's properties
 *
 **/
BOOLEAN
GetLevel2PSPEntryInfo (
  IN       UINT32                      EntryType,
  IN       UINT64                      PspLevel2BaseAddress,
  IN OUT   UINT64                      *EntryAddress,
  IN OUT   UINT32                      *EntrySize
  )
{
  UINTN                    i;
  PSP_DIRECTORY_ENTRY_TYPE EntryTypeValue;
  PSP_DIRECTORY            *PspRegionDir;
  UINT8                    *PspDirBuffer;

  PspDirBuffer = NULL;
  EntryTypeValue.Value = EntryType;

  if (GetPspLv2DirBaseV2 (PspLevel2BaseAddress, &PspRegionDir) == TRUE) {
  // Loop and compare the EntryType
    for (i = 0; i < PspRegionDir->Header.TotalEntries; i++) {
      if ((PspRegionDir->PspEntry[i].Type.Field.Type == EntryTypeValue.Field.Type) &&
          (PspRegionDir->PspEntry[i].Type.Field.SubProgram == EntryTypeValue.Field.SubProgram)) {
            *EntryAddress = TranslateEntryLocation (PspRegionDir->PspEntry[i].Location, PspLevel2BaseAddress, (UINT32)(PspLevel2BaseAddress & 0xFFFFFFFF));
            *EntrySize = PspRegionDir->PspEntry[i].Size;
            return (TRUE);
      }
    }
  }
  return (FALSE);
}

/**
  This function is to get the PSP entry information for given PSP entry type.

  @param[in]   value of given PSP entry type
  @param[out]  pointer to PSP entry address
  @param[out]  pointer to PSP entry size

  @retval TRUE            The given entry type is found
  @retval FALSE           The given entry type is not found

**/
BOOLEAN
PSPEntryInfoV2 (
  IN       UINT32                      EntryType,
  IN OUT   UINT64                      *EntryAddress,
  IN OUT   UINT32                      *EntrySize
  )
{
  PSP_DIRECTORY               *PspDir;
  UINT64                      PspLevel2BaseAddress;
  UINTN                       i;
  BOOLEAN                     Lv2DirExist;
  BOOLEAN                     ABrecoveryEnable;
  UINT64                      Level2EntryAddress;
  UINT64                      PspRegionAEntryAddress;
  UINT64                      PspRegionBEntryAddress;
  UINT32                      IgnoredEntrySize;
  PSP_DIRECTORY_ENTRY_TYPE    EntryTypeValue;

  PspDir = NULL;
  PspLevel2BaseAddress = 0;
  Lv2DirExist = FALSE;
  ABrecoveryEnable = FALSE;
  Level2EntryAddress = 0;
  PspRegionAEntryAddress = 0;
  PspRegionBEntryAddress = 0;
  EntryTypeValue.Value = EntryType;

  if (GetPspDirBaseV2 (&PspDir) != TRUE) {
    return FALSE;
  }
  if (PspDir == NULL) {
    IDS_HDT_CONSOLE_PSP_TRACE (" PSPDir is NULL \n");
    return FALSE;
  }

  // Check if A/B recovery schema 1st, as A/B has different search logic
  if ((EntryType != PSP_REGION_A_DIR) && (EntryType != PSP_REGION_B_DIR)) {
    ABrecoveryEnable = IsABrecovery (PspDir, &PspRegionAEntryAddress, &PspRegionBEntryAddress);
  }

  if (ABrecoveryEnable) {
    // Check read from Partition A or B by reading recovery flag
    if (CheckPspRecoveryFlagV2 () == FALSE) {
      // Get L2A Dir
      PspLevel2BaseAddress = PspRegionAEntryAddress;
    } else {
      // Get L2B Dir
      PspLevel2BaseAddress = PspRegionBEntryAddress;
    }
  } else {
    // Check the existence of Level 2 DIR for non-AB recovery mode
    if (EntryType != PSP_DIR_LV2) {
      Lv2DirExist = PSPEntryInfoV2 (PSP_DIR_LV2, &Level2EntryAddress, &IgnoredEntrySize);
    }
    // Try to load entry from level2 if exist
    if (Lv2DirExist) {
      PspLevel2BaseAddress = Level2EntryAddress;
    }
  }

  if (PspLevel2BaseAddress != 0) {
    if (GetLevel2PSPEntryInfo (EntryType, PspLevel2BaseAddress, EntryAddress, EntrySize) == TRUE) {
      return (TRUE);
    }
  }

  // If level 2 not exists, or can't find the entry in level 2, try in Level 1
  if (PspDir != NULL) {
    for (i = 0; i < PspDir->Header.TotalEntries; i++) {
      if ((PspDir->PspEntry[i].Type.Field.Type == EntryTypeValue.Field.Type) &&
          (PspDir->PspEntry[i].Type.Field.SubProgram == EntryTypeValue.Field.SubProgram)) {
           *EntryAddress = TryToTranslateOffsetToPhysicalAddress (PspDir->PspEntry[i].Location);
           *EntrySize = PspDir->PspEntry[i].Size;
           return (TRUE);
      }
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
 *  Get BIOS Directory Entry 's properties from Level 2
 *
 *  @param[in]     EntryType        BIOS Directory Entry type
 *  @param[in]     EntryInstance    If input with INSTANCE_IGNORED, will return 1st Entry type matched
 *                                  If input with Non INSTANCE_IGNORED, will return the entry which both Type & Instance matched
 *  @param[in]     SubProgram       If input with SUBPROGRAM_IGNORED, will return 1st Entry type & Instance matched
 *                                  If input with Non SUBPROGRAM_IGNORED, will return the entry which all Type & Instance & SubProgram matched
 *  @param[in]     Level2BaseAddress  if DirectoryType=DIR_TYPE_PSP_LV2, please specify PSP L2 base address(only for VN/MR and beyond),
 *                                    if DirectoryType=DIR_TYPE_BIOS_LV2, please specify BIOS L2 base address(for programs before VN, such as RN/CZN/MTS)
 *  @param[in,out] TypeAttrib       TypeAttrib of entry
 *  @param[in,out] EntryAddress     Address of entry
 *  @param[in,out] EntrySize        Size of entry
 *  @param[in,out] EntryDest        Destination of entry
 *
 *  @retval TRUE   Success to get the Entry 's properties
 *  @retval FALSE  Fail to get the Entry 's properties
 *
 **/
BOOLEAN
GetLevel2BIOSEntryInfo (
  IN       UINT32                      EntryType,
  IN       UINT8                       EntryInstance,
  IN       UINT8                       SubProgram,
  IN       UINT64                      Level2BaseAddress,
  IN OUT   TYPE_ATTRIB                 *TypeAttrib,
  IN OUT   UINT64                      *EntryAddress,
  IN OUT   UINT32                      *EntrySize,
  IN OUT   UINT64                      *EntryDest
  )
{
  UINTN                 i;
  BOOLEAN               Found;
  BIOS_DIRECTORY        *BiosLevel2Dir;
  UINT8                 *BiosDirBuffer;
  UINT64                BIOSLevel2BaseAddress;
  UINT32                IgnoredEntrySize;

  Found = FALSE;
  BiosDirBuffer = NULL;
  BIOSLevel2BaseAddress = 0;
  IgnoredEntrySize = 0;

  // Get BIOS L2 base address
  BIOSLevel2BaseAddress = Level2BaseAddress;


  if (GetBiosLv2DirBaseV2 (BIOSLevel2BaseAddress, &BiosLevel2Dir) == TRUE) {
    for (i = 0; i < BiosLevel2Dir->Header.TotalEntries; i++) {
      if (BiosLevel2Dir->BiosEntry[i].TypeAttrib.Type == EntryType) {
        if (EntryInstance == INSTANCE_IGNORED) {
           if ((SubProgram == SUBPROGRAM_IGNORED) || (SubProgram == BiosLevel2Dir->BiosEntry[i].TypeAttrib.SubProgram)) {
               Found = TRUE;
           }
        } else if (BiosLevel2Dir->BiosEntry[i].TypeAttrib.Instance == EntryInstance) {
           if ((SubProgram == SUBPROGRAM_IGNORED) || (SubProgram == BiosLevel2Dir->BiosEntry[i].TypeAttrib.SubProgram)) {
               Found = TRUE;
           }
        }
        if (Found == TRUE) {
          *TypeAttrib = BiosLevel2Dir->BiosEntry[i].TypeAttrib;
          *EntrySize = BiosLevel2Dir->BiosEntry[i].Size;
          *EntryDest = BiosLevel2Dir->BiosEntry[i].Destination;
          *EntryAddress = TranslateEntryLocation (BiosLevel2Dir->BiosEntry[i].Location, BIOSLevel2BaseAddress, 0);
          return TRUE;
        }
      }
    }
  }
  return FALSE;
}

/**
 *
 *  Get BIOS Directory Entry 's properties by 3 Attributes: EntryType, EntryInstance, SubProgram.
 *
 *  @param[in]     EntryType        BIOS Directory Entry type
 *  @param[in]     EntryInstance    If input with INSTANCE_IGNORED, will return 1st Entry type matched
 *                                  If input with Non INSTANCE_IGNORED, will return the entry which both Type & Instance matched
 *  @param[in]     SubProgram       If input with SUBPROGRAM_IGNORED, will return 1st Entry type & Instance matched
 *                                  If input with Non SUBPROGRAM_IGNORED, will return the entry which all Type & Instance & SubProgram matched
 *  @param[in,out] TypeAttrib       TypeAttrib of entry
 *  @param[in,out] EntryAddress     Address of entry
 *  @param[in,out] EntrySize        Size of entry
 *  @param[in,out] EntryDest        Destination of entry
 *
 *  @retval TRUE   Success to get the Entry 's properties
 *  @retval FALSE  Fail to get the Entry 's properties
 *
 **/
BOOLEAN
BIOSEntryInfoByAttributes (
  IN       UINT8                       EntryType,
  IN       UINT8                       EntryInstance,
  IN       UINT8                       SubProgram,
  IN OUT   TYPE_ATTRIB                 *TypeAttrib,
  IN OUT   UINT64                      *EntryAddress,
  IN OUT   UINT32                      *EntrySize,
  IN OUT   UINT64                      *EntryDest
  )
{
  BIOS_DIRECTORY          *BiosDir;
  UINT64                  BiosLevel2BaseAddress;
  PSP_DIRECTORY           *PspDir;
  UINTN                   i;
  BOOLEAN                 Found;
  BOOLEAN                 ABrecoveryEnable;
  UINT64                  Level2EntryAddress;
  UINT64                  BiosRegionEntryAddress;
  UINT64                  PspRegionAEntryAddress;
  UINT64                  PspRegionBEntryAddress;
  TYPE_ATTRIB             IgnoredTypeAttrib;
  UINT32                  IgnoredEntrySize;
  UINT64                  IgnoredEntryDest;

  BiosDir = NULL;
  BiosLevel2BaseAddress = 0;
  PspDir = NULL;
  ABrecoveryEnable = FALSE;
  Level2EntryAddress = 0;
  BiosRegionEntryAddress = 0;
  PspRegionAEntryAddress = 0;
  PspRegionBEntryAddress = 0;
  Found = FALSE;


  if (GetPspDirBaseV2 (&PspDir) != TRUE) {
    return FALSE;
  }
  //Check if A/B recovery schema 1st, as A/B has different search logic
  ABrecoveryEnable = IsABrecovery (PspDir, &PspRegionAEntryAddress, &PspRegionBEntryAddress);
  if (ABrecoveryEnable) {
    // For legacy AB recovery like RN/CZN, we still need to find BIOS entry from BIOS directory L2,
    //and BIOS L2 base (0x49) is from Psp Directory instead of EFS (RomSig)
    if (PSPEntryInfoV2 (BIOS_REGION_DIR, &BiosRegionEntryAddress, &IgnoredEntrySize) == TRUE) {
      BiosLevel2BaseAddress = BiosRegionEntryAddress;
    }
  } else if (GetBiosDirBaseV2 (&BiosDir) == TRUE) {
    //Check the existence of Level 2 DIR
    if (EntryType != BIOS_DIR_LV2) {
      if (BIOSEntryInfo (BIOS_DIR_LV2, INSTANCE_IGNORED, &IgnoredTypeAttrib, &Level2EntryAddress, &IgnoredEntrySize, &IgnoredEntryDest) == TRUE) {
        BiosLevel2BaseAddress = Level2EntryAddress;
      }
    }
  }

  //find entry in level 2
  if (BiosLevel2BaseAddress != 0) {
    if (GetLevel2BIOSEntryInfo (EntryType, EntryInstance, SubProgram,
        BiosLevel2BaseAddress,
        TypeAttrib, EntryAddress, EntrySize, EntryDest) == TRUE) {
        return (TRUE);
    }
  }

  //If level 2 not exists, or can't find the entry in level 2, try in Level 1
  if (BiosDir != NULL) {
    for (i = 0; i < BiosDir->Header.TotalEntries; i++) {
      if (BiosDir->BiosEntry[i].TypeAttrib.Type == EntryType) {
        if (EntryInstance == INSTANCE_IGNORED) {
            if ((SubProgram == SUBPROGRAM_IGNORED) || (SubProgram == BiosDir->BiosEntry[i].TypeAttrib.SubProgram)) {
                Found = TRUE;
            }
        } else if (BiosDir->BiosEntry[i].TypeAttrib.Instance == EntryInstance) {
            if ((SubProgram == SUBPROGRAM_IGNORED) || (SubProgram == BiosDir->BiosEntry[i].TypeAttrib.SubProgram)) {
                Found = TRUE;
            }
        }
        if (Found == TRUE) {
          *TypeAttrib = BiosDir->BiosEntry[i].TypeAttrib;
          *EntryAddress = TryToTranslateOffsetToPhysicalAddress (BiosDir->BiosEntry[i].Location);
          *EntrySize = BiosDir->BiosEntry[i].Size;
          *EntryDest = BiosDir->BiosEntry[i].Destination;
          return (TRUE);
        }
      }
    }
  }
  return (FALSE);
}

/**
 *
 *  Get BIOS Directory Entry 's properties by EntryType and EntryInstance
 *  This function will ignore SubProgram, if you care about SubProgram, call BIOSEntryInfoByAttributes instead.
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
  return BIOSEntryInfoByAttributes (EntryType, EntryInstance, SUBPROGRAM_IGNORED, TypeAttrib, EntryAddress, EntrySize, EntryDest);
}

BOOLEAN
GetPspLv2BaseAddr (
  IN OUT UINT64                      *PspLv2BaseAddress
  )
{
  PSP_DIRECTORY               *PspDir;
  BOOLEAN                     ABrecoveryEnable;
  UINT64                      Level2EntryAddress;
  UINT64                      PspRegionAEntryAddress;
  UINT64                      PspRegionBEntryAddress;
  UINT32                      IgnoredEntrySize;

  PspDir = NULL;
  ABrecoveryEnable = FALSE;
  Level2EntryAddress = 0;
  PspRegionAEntryAddress = 0;
  PspRegionBEntryAddress = 0;


  if (GetPspDirBaseV2 (&PspDir) != TRUE) {
    IDS_HDT_CONSOLE_PSP_TRACE (" Cannot get PSPDir \n");
    return FALSE;
  }
  if (PspDir == NULL) {
    IDS_HDT_CONSOLE_PSP_TRACE (" PSPDir is NULL \n");
    return FALSE;
  }
  // Check if A/B recovery schema 1st, as A/B has different search logic
  ABrecoveryEnable = IsABrecovery (PspDir, &PspRegionAEntryAddress, &PspRegionBEntryAddress);
  if (ABrecoveryEnable) {
    // Check read from Partition A or B by reading recovery flag
    if (CheckPspRecoveryFlagV2 () == FALSE) {
      // Get L2A Dir
      *PspLv2BaseAddress = PspRegionAEntryAddress;
      return TRUE;
    } else {
      // Get L2B Dir
      *PspLv2BaseAddress = PspRegionBEntryAddress;
      return TRUE;
    }
  } else {
    // Check the existence of Level 2 DIR for non-AB recovery mode
    if (PSPEntryInfoV2 (PSP_DIR_LV2, &Level2EntryAddress, &IgnoredEntrySize) == TRUE) {
      *PspLv2BaseAddress = Level2EntryAddress;
      return TRUE;
    }
  }
  return FALSE;
}

BOOLEAN
GetPspBiosLv2BaseAddr (
  IN OUT UINT64                      *PspLv2BaseAddress,
  IN OUT UINT64                      *BiosLv2BaseAddress
  )
{
  PSP_DIRECTORY               *PspDir;
  BOOLEAN                     PspLv2BaseAddrFound;
  BOOLEAN                     BiosLv2BaseAddrFound;
  BOOLEAN                     ABrecoveryEnable;
  UINT64                      Level2EntryAddress;
  UINT64                      PspRegionAEntryAddress;
  UINT64                      PspRegionBEntryAddress;
  UINT32                      IgnoredEntrySize;

  UINT64                       BiosRegionEntryAddress;
  TYPE_ATTRIB                  IgnoredTypeAttrib;
  UINT64                       IgnoredEntryDest;

  PspDir = NULL;
  PspLv2BaseAddrFound = FALSE;
  BiosLv2BaseAddrFound = FALSE;
  ABrecoveryEnable = FALSE;
  Level2EntryAddress = 0;
  PspRegionAEntryAddress = 0;
  PspRegionBEntryAddress = 0;
  BiosRegionEntryAddress = 0;

  if (GetPspDirBaseV2 (&PspDir) != TRUE) {
    IDS_HDT_CONSOLE_PSP_TRACE (" Cannot get PSPDir \n");
    return FALSE;
  }
  if (PspDir == NULL) {
    IDS_HDT_CONSOLE_PSP_TRACE (" PSPDir is NULL \n");
    return FALSE;
  }
  // Check if A/B recovery schema 1st, as A/B has different search logic
  ABrecoveryEnable = IsABrecovery (PspDir, &PspRegionAEntryAddress, &PspRegionBEntryAddress);
  if (ABrecoveryEnable) {
    // Check read from Partition A or B by reading recovery flag
    if (CheckPspRecoveryFlagV2 () == FALSE) {
      // Get L2A Dir
      *PspLv2BaseAddress = PspRegionAEntryAddress;
      PspLv2BaseAddrFound = TRUE;
    } else {
      // Get L2B Dir
      *PspLv2BaseAddress = PspRegionBEntryAddress;
      PspLv2BaseAddrFound = TRUE;
    }

    // For legacy AB recovery like RN/CZN, we still need to find BIOS entry from BIOS directory L2,
    // and BIOS L2 base (0x49) is from Psp Directory
    if (PSPEntryInfoV2 (BIOS_REGION_DIR, &BiosRegionEntryAddress, &IgnoredEntrySize) == TRUE) {
      *BiosLv2BaseAddress = BiosRegionEntryAddress;
      BiosLv2BaseAddrFound = TRUE;
    }
  } else {
    // Check the existence of Level 2 DIR for non-AB recovery mode
    if (PSPEntryInfoV2 (PSP_DIR_LV2, &Level2EntryAddress, &IgnoredEntrySize) == TRUE) {
      *PspLv2BaseAddress = Level2EntryAddress;
      PspLv2BaseAddrFound = TRUE;
    }

    // Check the existence of Level 2 DIR
    if (BIOSEntryInfo (BIOS_DIR_LV2, INSTANCE_IGNORED, &IgnoredTypeAttrib, &Level2EntryAddress, &IgnoredEntrySize,
                        &IgnoredEntryDest) == TRUE) {
      *BiosLv2BaseAddress = Level2EntryAddress;
      BiosLv2BaseAddrFound = TRUE;
    }
  }
  return (PspLv2BaseAddrFound && BiosLv2BaseAddrFound);
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


/**
  Check PSP Recovery Flag using SMN to remove MMIO initial dependency
  Target will set Recovery flag if some PSP entry point by PSP directory has been corrupted.

  @retval BOOLEAN  0: Recovery Flag is cleared, 1: Recovery Flag has been set

**/
BOOLEAN
CheckPspRecoveryFlagSmn (
  VOID
  )
{
  PSP_MBOX_V2_CMD PspMboxCmd;

  SmnRegisterRead (0, MP0_C2PMSG_28_SMN_ADDR,  (VOID *) &PspMboxCmd.Value);
  IDS_HDT_CONSOLE_PSP_TRACE ("RecoveryFlag %x\n", PspMboxCmd.Value);

  return (BOOLEAN) (PspMboxCmd.Field.Recovery);
}

VOID
PspBarInitEarlyV2 (
  VOID
  )
{
  UINT32                 Value32;
  UINT64                 PspMmioBase;
  UINTN                  PciAddress;
  UINT64                 Length;
  FABRIC_TARGET          MmioTarget;
  EFI_STATUS             Status;
  FABRIC_MMIO_ATTRIBUTE  Attributes;
  UINT32                 SmnBase;
  //UINT8                  RbNumber;
  //UINT64                 TempPspMmioBase;

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

/**
  Return the PSP Entry Address of given PSP entry type and level

  @param[in]        EntryType             Value of given PSP entry type
  @param[in]        IsLevel2              The given entry is in PSP level 2 directory
  @param[in, out]   EntryAddress          Pointer to PSP entry address

  @retval TRUE      The given entry type is found
  @retval FALSE     The given entry type is not found
**/
BOOLEAN
GetPspEntryAddress (
  IN      UINT8     EntryType,
  IN      BOOLEAN   IsLevel2,
  IN OUT  UINT64    *EntryAddress
  )
{
  PSP_DIRECTORY               *PspDir = NULL;
  UINTN                       i;
  UINT64                      Level2EntryAddress = 0;
  UINT32                      IgnoredEntrySize = 0;
  UINT64                      PspLevel2BaseAddress = 0;
  BOOLEAN                     Lv2DirExist = FALSE;
  BOOLEAN                     ABrecoveryEnable = FALSE;
  UINT64                      PspRegionAEntryAddress = 0;
  UINT64                      PspRegionBEntryAddress = 0;

  if (GetPspDirBaseV2 (&PspDir) != TRUE) {
    return FALSE;
  }

  if (IsLevel2){
    //Check if A/B recovery schema 1st, as A/B has different search logic
    if ((EntryType != PSP_REGION_A_DIR) && (EntryType != PSP_REGION_B_DIR)) {
      ABrecoveryEnable = IsABrecovery (PspDir, &PspRegionAEntryAddress, &PspRegionBEntryAddress);
    }

    if (ABrecoveryEnable) {
      //Check read from Partition A or B by reading recovery flag
      if (CheckPspRecoveryFlagV2 () == FALSE) {
        //Get L2A Dir
        PspLevel2BaseAddress = PspRegionAEntryAddress;
      } else {
        //Get L2B Dir
        PspLevel2BaseAddress = PspRegionBEntryAddress;
      }
    } else {
      //Check the existence of Level 2 DIR for non-AB recovery mode
      if (EntryType != PSP_DIR_LV2) {
        Lv2DirExist = PSPEntryInfoV2 (PSP_DIR_LV2, &Level2EntryAddress, &IgnoredEntrySize);
      }
      //Try to load entry from level2 if exist
      if (Lv2DirExist) {
        PspLevel2BaseAddress = Level2EntryAddress;
      }
    }

    if (PspLevel2BaseAddress != 0) {
      if (GetLevel2PSPEntryInfo (EntryType, PspLevel2BaseAddress, EntryAddress, &IgnoredEntrySize) == TRUE) {
        return (TRUE);
      }
    }

  } else {
    for (i = 0; i < PspDir->Header.TotalEntries; i++) {
      if (PspDir->PspEntry[i].Type.Field.Type == EntryType){
        *EntryAddress = TryToTranslateOffsetToPhysicalAddress (PspDir->PspEntry[i].Location);
        return TRUE;
      }
    }
  }

  return FALSE;
}
