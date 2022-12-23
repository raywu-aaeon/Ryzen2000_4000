/* $NoKeywords:$ */
/**
 * @file
 *
 * PSP V1 Base Library
 *
 * Contains interface to the PSP library
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision: 317842 $   @e \$Date: 2015-04-29 15:06:52 +0800 (Wed, 29 Apr 2015) $
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
#include <Library/BaseLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdPspBaseLibV1.h>
#include <Library/AmdPspCommonLib.h>
#include <Library/PciLib.h>
#include <Filecode.h>

#define FILECODE LIBRARY_AMDPSPBASELIBV1_AMDPSPBASELIBV1_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define PSP_BAR_TMP_BASE 0xFEA00000ul

#define GET_PCI_BUS(Reg) (((UINT32) Reg >> 16) & 0xFF)
#define GET_PCI_DEV(Reg) (((UINT32) Reg >> 11) & 0x1F)
#define GET_PCI_FUNC(Reg) (((UINT32) Reg >> 8) & 0x7)
#define GET_PCI_OFFSET(Reg) ((UINT32)Reg & 0xFF)

#define PCI_CONFIG_SMU_INDIRECT_INDEX   0xB8          ///<  Gnb Offset index for SMU mbox
#define PCI_CONFIG_SMU_INDIRECT_DATA    0xBC          ///<  Gnb Offset data for SMU mbox

#define SMU_CC_PSP_FUSES_STATUS         0xC0018000ul  ///< offset in GNB to find PSP fusing
#define SMU_CC_PSP_FUSES_SECURE         BIT0          ///< BIT0
#define SMU_CC_PSP_FUSES_FRA_ENABLE     BIT1          ///< BIT1
#define SMU_CC_PSP_FUSES_PROTO          BIT2          ///< BIT2
#define PLATFORM_SECURE_BOOT_EN         BIT4          ///< BIT4


#define PSP_BLANK_PART                  0   ///< Blank part
#define PSP_PROTO_PART                  SMU_CC_PSP_FUSES_PROTO    ///< Proto Part
#define PSP_NON_SECURE_PART             (SMU_CC_PSP_FUSES_PROTO + SMU_CC_PSP_FUSES_PCPU_DIS)    ///< Non Secure Part
#define PSP_SECURE_PART                 (SMU_CC_PSP_FUSES_PROTO + SMU_CC_PSP_FUSES_SECURE)      ///< Secure Part
#define PSP_FRA_MODE                    (SMU_CC_PSP_FUSES_FRA_ENABLE + SMU_CC_PSP_FUSES_PROTO + SMU_CC_PSP_FUSES_SECURE)  ///< FRA Part


#define PSP_MUTEX_REG0_OFFSET     (24 * 4)       ///< PSP Mutex0 register offset
#define PSP_MUTEX_REG1_OFFSET     (25 * 4)       ///< PSP Mutex1 register offset

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

UINT32
PspLibPciReadPspConfig (
  IN UINT16 Offset
  )
{
  UINT32 Value;
  UINTN  PciAddr;
  AMD_CONFIG_PARAMS  *StdHeader;

  StdHeader = NULL;
  PciAddr = MAKE_SBDFO (PSP_PCI_SEG, PSP_PCI_BUS, PSP_PCI_DEV, PSP_PCI_FUNC, Offset);

  Value = PciRead32 (PciAddr);
  return Value;
}

VOID
PspLibPciWritePspConfig (
  IN UINT16 Offset,
  IN  UINT32 Value
  )
{
  UINTN PciAddr;
  AMD_CONFIG_PARAMS  *StdHeader;

  StdHeader = NULL;
  PciAddr = MAKE_SBDFO (0, PSP_PCI_BUS, PSP_PCI_DEV, PSP_PCI_FUNC, Offset);

  PciWrite32 (PciAddr, Value);
}

/// Structure for Program ID
typedef enum {
  CZ_PROGRAM = 0x00,            ///< Program ID for CZ
  BR_PROGRAM = 0x01,            ///< Program ID for BR
  ST_PROGRAM = 0x02,            ///< Program ID for ST
  UNSUPPORTED_PROGRAM = 0xFF,   ///< Program ID for unsupported
} PROGRAM_ID;

PROGRAM_ID
PspGetProgarmId (
  VOID
  )
{
  CPUID_DATA          Cpuid;

  AsmCpuid (
      0x00000001,
      &(Cpuid.EAX_Reg),
      &(Cpuid.EBX_Reg),
      &(Cpuid.ECX_Reg),
      &(Cpuid.EDX_Reg)
      );
  //Stoney CPUID 0x00670F00 or 0x00670F01
  if ((Cpuid.EAX_Reg >> 16) == 0x67) {
    return ST_PROGRAM;
  } else if ((Cpuid.EAX_Reg >> 16) == 0x66) {
    if ((Cpuid.EAX_Reg & 0xF0) == 0x50) {
      //Bristol CPUID 0x00660F51
      return BR_PROGRAM;
    } else if ((Cpuid.EAX_Reg & 0xF0) == 0x00) {
      //Carrizo CPUID 0x00660F00 or 0x00660F01
      return CZ_PROGRAM;
    }
  }
  return UNSUPPORTED_PROGRAM;
}
BOOLEAN
GetPspDirBase (
  IN OUT   UINT32     *Address
  )
{
  UINTN                     i;
  FIRMWARE_ENTRY_TABLE      *FirmwareTableBase;
  PROGRAM_ID                ProgramId;
  CONST UINT32 RomSigAddrTable[] =
  {
    0xFFFA0000, //  --> 512KB base
    0xFFF20000, //  --> 1MB base
    0xFFE20000, //  --> 2MB base
    0xFFC20000, //  --> 4MB base
    0xFF820000, //  --> 8MB base
    0xFF020000  //  --> 16MB base
  };

  ProgramId = PspGetProgarmId ();

  for (i = 0; i < sizeof (RomSigAddrTable) / sizeof (UINT32); i++) {
    FirmwareTableBase  = (FIRMWARE_ENTRY_TABLE *) (UINTN) RomSigAddrTable[i];
    // Search flash for unique signature 0x55AA55AA
    if (FirmwareTableBase->Signature  == FIRMWARE_TABLE_SIGNATURE) {
      switch (ProgramId) {
      case BR_PROGRAM:
      case CZ_PROGRAM:
        *Address = FirmwareTableBase->PspDirBase;
        break;
      case ST_PROGRAM:
        *Address = FirmwareTableBase->NewPspDirBase;
        break;
      default:
        *Address = FirmwareTableBase->PspDirBase;
        break;
      }
      return TRUE;
    }
  }
  return (FALSE);
}

/**
 * Get specific PSP Entry information, this routine will auto detect the processor for loading
 * correct PSP Directory
 *
 *
 *
 * @param[in] EntryType               PSP DIR Entry Type
 * @param[in,out] EntryAddress        Address of the specific PSP Entry
 * @param[in,out] EntrySize           Size of the specific PSP Entry
 */

BOOLEAN
PSPEntryInfoV1 (
  IN       UINT32                      EntryType,
  IN OUT   UINT64                      *EntryAddress,
  IN       UINT32                      *EntrySize
  )
{
  PSP_DIRECTORY         *PspDir;
  UINTN                 i;
  PROGRAM_ID                ProgramId;

  PspDir = NULL;
  if (GetPspDirBase ((UINT32 *)&PspDir ) != TRUE) {
    return FALSE;
  }

  ProgramId = PspGetProgarmId ();
  //Append BR Program ID
  if ((ProgramId == BR_PROGRAM) &&
      ((EntryType == SMU_OFFCHIP_FW) ||
       (EntryType == SMU_OFF_CHIP_FW_2) ||
       (EntryType == AMD_SCS_BINARY))) {
    EntryType |= (PSP_ENTRY_BR_PROGRAM_ID << 8);
  }

  for (i = 0; i < PspDir->Header.TotalEntries; i++) {
    if (PspDir->PspEntry[i].Type.Value == EntryType) {
      *EntryAddress = PspDir->PspEntry[i].Location;
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
GetPspEntryScsBinaryV1 (
  IN OUT   UINT64                      *EntryAddress,
  IN       UINT32                      *EntrySize
  )
{
  return PSPEntryInfoV1 (AMD_SCS_BINARY, EntryAddress, EntrySize);
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
GetPspEntryPspNvDataV1 (
  IN OUT   UINT64                      *EntryAddress,
  IN       UINT32                      *EntrySize
  )
{
  return PSPEntryInfoV1 (PSP_NV_DATA, EntryAddress, EntrySize);
}


UINT32
ReadPspFuseValue (
  VOID
  )
{
  UINT32 Value;
  UINTN  PciAddr;
  AMD_CONFIG_PARAMS  *StdHeader;

  StdHeader = NULL;
  PciAddr = MAKE_SBDFO (0, 0, 0, 0, PCI_CONFIG_SMU_INDIRECT_INDEX);

  Value = SMU_CC_PSP_FUSES_STATUS;
  PciWrite32 (PciAddr, Value);

  PciAddr = MAKE_SBDFO (0, 0, 0, 0, PCI_CONFIG_SMU_INDIRECT_DATA);
  Value = PciRead32 (PciAddr);

  return Value;
}
/**
  Check if PSP device is present

  @retval BOOLEAN  0: PSP Disabled, 1: PSP Enabled

**/
BOOLEAN
CheckPspDevicePresentV1 (
  VOID
  )
{
  UINT32 FuseValue;
  FuseValue = ReadPspFuseValue ();

  if (FuseValue &= SMU_CC_PSP_FUSES_PROTO) {
    return (TRUE);
  }
  return (FALSE);
}

/**
  Check PSP Platform Seucre Enable State
  HVB & Secure S3 (Resume vector set to Dram, & core content will restore by uCode)
  will be applied if Psp Plaform Secure is enabled

  @retval BOOLEAN  0: PSP Platform Secure Disabled, 1: PSP Platform Secure  Enabled

**/
BOOLEAN
CheckPspPlatformSecureEnableV1 (
  VOID
  )
{
  UINT32 FuseValue;
  FuseValue = ReadPspFuseValue ();

  if (FuseValue &= PLATFORM_SECURE_BOOT_EN) {
    return (TRUE);
  }
  return (FALSE);
}

/**
  Check PSP Recovery Flag
  Target will set Recovery flag if some PSP entry point by PSP directory has been corrupted.

  @retval BOOLEAN  0: Recovery Flag is cleared, 1: Recovery Flag has been set

**/
BOOLEAN
CheckPspRecoveryFlagV1 (
  VOID
  )
{
  MBOX_STATUS *MboxStatus;

  MboxStatus = NULL;
  //Init PSP MMIO
  PspBarInitEarly ();

  GetPspMboxStatus (&MboxStatus);

  return (BOOLEAN) (MboxStatus->Recovery);
}

/**
  Return the PspMbox MMIO location


  @retval BOOLEAN  FALSE: ERROR, TRUE: SUCCEED

**/
BOOLEAN
GetPspMboxStatus (
  IN OUT   MBOX_STATUS **MboxStatus
  )
{
  UINT32 PspMmio;

  if (GetPspBar3Addr (&PspMmio) == FALSE) {
    return (FALSE);
  }

  *MboxStatus = (MBOX_STATUS *)( (UINTN)PspMmio + PSP_MAILBOX_BASE + PSP_MAILBOX_STATUS_OFFSET);   // PSPMbox base is at offset CP2MSG_28 ie. offset 28*4 = 0x70

  return (TRUE);
}

BOOLEAN
PspBarInitEarly ()
{
  UINT32 PspMmioSize;
  UINT32 Value32;
  UINTN  PciAddr;
  AMD_CONFIG_PARAMS  *StdHeader;

  if (PspLibPciReadPspConfig  (PSP_PCI_DEVID_REG) == 0xffffffff) {
    return (FALSE);
  }

  //Check if PSP BAR has been assigned, if not do the PSP BAR initialation
  if (PspLibPciReadPspConfig (PSP_PCI_BAR3_REG) == 0) {
    /// Get PSP BAR1 Size
    PspLibPciWritePspConfig (PSP_PCI_BAR3_REG, 0xFFFFFFFF);
    PspMmioSize = PspLibPciReadPspConfig (PSP_PCI_BAR3_REG);
    PspMmioSize = ~PspMmioSize + 1;
    /// Assign BAR3 Temporary Address
    PspLibPciWritePspConfig (PSP_PCI_BAR3_REG, PSP_BAR_TMP_BASE);
    PspLibPciWritePspConfig ( PSP_PCI_CMD_REG, 0x06);

    /// Enable MMIO Decoder
    StdHeader  = NULL;
    Value32 = ((PSP_BAR_TMP_BASE + PspMmioSize -1) >> 8) & ~0xFF;
    PciAddr = MAKE_SBDFO (0, 0, 0x18, 0x1, 0xBC);
    PciWrite32 (PciAddr, Value32);

    PciAddr = MAKE_SBDFO (0, 0, 0x18, 0x1, 0xB8);
    Value32 = (PSP_BAR_TMP_BASE >> 8) | 3;
    PciWrite32 (PciAddr, Value32);

    /// Enable MsixBarEn, Bar1En, Bar3En
    PspLibPciWritePspConfig ( PSP_PCI_EXTRAPCIHDR_REG, 0x34);
    /// Capability chain update
    Value32 = PspLibPciReadPspConfig (PSP_PCI_MIRRORCTRL1_REG);
    Value32 &= ~D8F0x44_PmNxtPtrW_MASK;
    Value32 |= 0xA4;
    PspLibPciWritePspConfig (PSP_PCI_MIRRORCTRL1_REG, Value32);
  }

  return (TRUE);
}


/**
  Return the PspMMIO MMIO location

  @param[in] PspMmio Pointer to Psp MMIO address

  @retval BOOLEAN  0: Error, 1 Success
**/
BOOLEAN
GetPspBar3Addr (
  IN OUT   UINT32 *PspMmio
  )
{
  UINT32 PciReg48;
  UINT64 MsrPspAddr;

  if (CheckPspDevicePresentV1 () == FALSE) {
    return (FALSE);
  }

  PciReg48 = PspLibPciReadPspConfig (PSP_PCI_EXTRAPCIHDR_REG);
  if (PciReg48 & BIT12) {
  // D8F0x48[12] Bar3Hide
    MsrPspAddr = AsmReadMsr64 (PSP_MSR_PRIVATE_BLOCK_BAR);
    *PspMmio = (UINT32)MsrPspAddr;
  } else {
    *PspMmio = PspLibPciReadPspConfig (PSP_PCI_BAR3_REG) & 0xFFF00000;
  }

  if ((*PspMmio) == 0xffffffff) {
    return (FALSE);
  }

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
PspLibTimeOutV1 (
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
GetFtpmControlAreaV1 (
  IN OUT   VOID **FtpmControlArea
  )
{
  *FtpmControlArea = NULL;
  return GetPspBar3Addr ((UINT32 *) FtpmControlArea);
}

VOID
SwitchPspMmioDecodeV1 (
  IN       BOOLEAN SwitchFlag,
  IN OUT   UINT32 *RegisterCopy
  )
{
  //Turn on decode
  if (SwitchFlag == TRUE) {
    *RegisterCopy = PspLibPciReadPspConfig (PSP_PCI_CMD_REG);
    //Enable BusMaster & MemAccess
    PspLibPciWritePspConfig (PSP_PCI_CMD_REG, *RegisterCopy | 0x6);
  } else {
  //Restore decode register
    PspLibPciWritePspConfig (PSP_PCI_CMD_REG, *RegisterCopy);
  }
}


/**
 * Acquire the Mutex for access PSP,X86 co-accessed register
 * Call this routine before access SMIx98 & SMIxA8 
 *
 */
VOID
AcquirePspSmiRegMutexV1 (
  VOID
  )
{
  UINT32 PspBarAddr;
  UINT32 MutexReg0;
  UINT32 MutexReg1;

  PspBarAddr = 0;
  if (GetPspBar3Addr (&PspBarAddr)) {
    MutexReg0 = PspBarAddr + PSP_MUTEX_REG0_OFFSET;
    MutexReg1 = PspBarAddr + PSP_MUTEX_REG1_OFFSET;
    *(volatile UINT32*)(UINTN)(MutexReg0) |= BIT0;
    *(volatile UINT32*)(UINTN)(MutexReg1) |= BIT0;
    //Wait till PSP FW release the mutex
    while ((*(volatile UINT32*)(UINTN)(MutexReg0)& BIT1) && (*(volatile UINT32*)(UINTN)(MutexReg1) & BIT0)) {
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
ReleasePspSmiRegMutexV1 (
  VOID
  )
{
  UINT32 PspBarAddr;
  UINT32 MutexReg0;

  PspBarAddr = 0;
  if (GetPspBar3Addr (&PspBarAddr)) {
    MutexReg0 = PspBarAddr + PSP_MUTEX_REG0_OFFSET;
    *(volatile UINT32*)(UINTN)(MutexReg0) &= ~BIT0;
  } 
}

