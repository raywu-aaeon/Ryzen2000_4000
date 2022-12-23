/* $NoKeywords:$ */
/**
 * @file
 *
 * PSP Mailbox related functions Prototype definition
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision: 321051 $   @e \$Date: 2015-06-18 12:28:55 +0800 (Thu, 18 Jun 2015) $
 */
/*****************************************************************************
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
 **/
#ifndef _AMD_PSPMBOX_V1_LIB_H_
#define _AMD_PSPMBOX_V1_LIB_H_
#pragma pack (push, 1)

#include <Library/AmdPspBaseLibV1.h>

typedef union _MBOX_BUFFER MBOX_BUFFER;

#define PSP_NOTIFY_SMM        0xdd    ///< @todo Move it out to other file

#define PSP_MAILBOX_BASE      0x70    ///< Mailbox base offset on PCIe BAR

#define PSP_WAITSTS_MAX_COUNT 10000 ///< @todo Need check this value's correctness
//======================================================================================
//
// Define Mailbox Command
//
//======================================================================================
//
/// Mbox command list. Only one command can be send till target process it; the only exception is Abort command that BIOS may send in case of timeout etc.
///
typedef enum {
  MboxCmdRsvd               = 0x00,   ///< Unused

  MboxBiosCmdDramInfo       = 0x01,   ///< Bios -> PSP: Memory DRAM information (ie. PspBuffer address etc)
  MboxBiosCmdSmmInfo        = 0x02,   ///< Bios -> PSP: Bios will provide SMM inf - SmmBase, PspSmmDataRegion,PspSmmDataRegionLength, SoftSmiValue, SoftSmiPort
  MboxBiosCmdSxInfo         = 0x03,   ///< Bios -> PSP: Sx transition info (S3, S5)
  MboxBiosCmdRsmInfo        = 0x04,   ///< Bios -> PSP: Resume transition info (BiosResume Vector, Size of resume code)
  MboxBiosCmdPspQuery       = 0x05,   ///< Bios -> PSP: Bios Find supported feature
  MboxBiosCmdBootDone       = 0x06,   ///< Bios -> PSP: Bios is done with BIOS POST
  MboxBiosCmdClearS3Sts     = 0x07,   ///< Bios -> PSP: Inform PSP clear S3ExitReset
  MboxBiosS3DataInfo        = 0x08,   ///< Bios -> PSP: Bios will send this command to inform PSP to save the data needed to restore memory during resume from S3
  MboxBiosCmdNop            = 0x09,   ///< Bios -> PSP: Bios will send this NOP command to indicate to PSP that is is done servicing PSP SMM request
  MboxBiosCmdHSTIQuery      = 0x14,   ///< Bios -> PSP: Command to get HSTI bit field representing the security state of the SoC from the PSP
  MboxBiosCmdClrSmmLock     = 0x17,   ///< Bios -> PSP: Command to clear SMMLock Register in C6 private memory region
  MboxBiosCmdPcieInfo       = 0x18,   ///< Bios -> PSP: PCIE Device information
  MboxBiosCmdTa             = 0x40,   ///< Bios -> PSP: Send command to TA


  MboxPspCmdSpiGetAttrib    = 0x81,   ///< PSP -> BIOS: Get location of PSP NVRam region
  MboxPspCmdSpiSetAttrib    = 0x82,   ///< PSP -> BIOS: Get location of PSP NVRam region
  MboxPspCmdSpiGetBlockSize = 0x83,   ///< PSP -> BIOS: Get Block size info
  MboxPspCmdSpiReadFV       = 0x84,   ///< PSP -> BIOS: Read PSP NVRAM firmware volume
  MboxPspCmdSpiWriteFV      = 0x85,   ///< PSP -> BIOS: Write PSP NVRAM firmware volume
  MboxPspCmdSpiEraseFV      = 0x86,   ///< PSP -> BIOS: Erase PSP NVRAM firmware volume

  MboxCmdAbort              = 0xfe,   ///< Abort the last command (BIOS to PSP in case of timeout etc)
} MBOX_COMMAND;


///
///
/// standard header structure for additional parameter
///
typedef struct {
  UINT32    TotalSize;                      ///< Total Size of MBOX_BUFFER (including this field)
  UINT32    Status;                         ///< Status value if any:e
  //UINT8   ReqBuffer[x];                   ///< X byte long Request buffer for additional parameter.
} MBOX_BUFFER_HEADER;


//======================================================================================
//
// Below define Request buffer for various commands. This structure is based on Command
//
//======================================================================================
#define S3_RESTORE_BUFFER_HMAC_SIZE 32
///
/// structure of ReqBuffer for MboxBiosS3DataInfo mailbox command
///
typedef struct {
  UINT64 S3RestoreBufferBase;               ///< PSP reserve memory near TOM
  UINT64 S3RestoreBufferSize;               ///< Size of PSP memory
  UINT8  Hmac[S3_RESTORE_BUFFER_HMAC_SIZE];                          ///< HMAC of S3 Data
} S3DATA_REQ_BUFFER;

/// MBOX buffer for S3Info data to bring memory out of self refresh info
typedef struct {
  MBOX_BUFFER_HEADER  Header;               ///< Header
  S3DATA_REQ_BUFFER   Req;                  ///< Req
} MBOX_S3DATA_BUFFER;

#define SMM_TRIGGER_IO                      0
#define SMM_TRIGGER_MEM                     1

#define SMM_TRIGGER_BYTE                    0
#define SMM_TRIGGER_WORD                    1
#define SMM_TRIGGER_DWORD                   2

/// Define structure of SMM_TRIGGER_INFO
typedef struct {
  UINT64  Address;                          ///< Memory or IO address (Memory will be qword, IO will be word)
  UINT32  AddressType;                      ///< SMM trigger typr - Perform write to IO/Memory
  UINT32  ValueWidth;                       ///< Width of value to write (byte write, word write,..)
  UINT32  ValueAndMask;                     ///< AND mask of value after reading from the address
  UINT32  ValueOrMask;                      ///< OR Mask of value to write to this address.
} SMM_TRIGGER_INFO;

///
/// structure of ReqBuffer for MboxBiosCmdSmmInfo mailbox command
///
typedef struct {
  UINT64            SMMBase;                ///< SMM TSeg Base
  UINT64            SMMLength;              ///< Length of SMM area
  UINT64            PSPSmmDataRegion;       ///< PSP region base in Smm space
  UINT64            PspSmmDataLength;       ///< Psp region length in smm space
  SMM_TRIGGER_INFO  SmmTrigInfo;            ///< Information to generate SMM
  UINT64            PspMboxSmmBufferAddress;  ///< Address of MBOX_BUFFER structure used for BIOS-to-PSP commands sent from SMM mode
  UINT64            PspMboxSmmFlagAddress;    ///< Address of 32-bit flag indicating the CPU is in SMM mode
} SMM_REQ_BUFFER;

/// MBOX buffer for SMM info
typedef struct {
  MBOX_BUFFER_HEADER  Header;               ///< Header
  SMM_REQ_BUFFER      Req;                  ///< Reques buffer
} MBOX_SMM_BUFFER;


///
/// structure of ReqBuffer for MboxBiosCmdSxInfo mailbox command
///
typedef struct {
  UINT8  SleepType;                         ///< Inform which sleep state the system is going to
} SX_REQ_BUFFER;

/// MBOX buffer for Sx info
typedef struct {
  MBOX_BUFFER_HEADER  Header;               ///< Header
  SX_REQ_BUFFER       Req;                  ///< Request buffer
} MBOX_SX_BUFFER;


///
/// structure of ReqBuffer for MboxBiosCmdRsmInfo mailbox command
///
typedef struct {
  UINT64  ResumeVecorAddress;               ///< Address of BIOS resume vector
  UINT64  ResumeVecorLength;                ///< Length of BIOS resume vector
} RSM_REQ_BUFFER;

/// MBOX buffer for RSM info
typedef struct {
  MBOX_BUFFER_HEADER  Header;               ///< Header
  RSM_REQ_BUFFER      Req;                  ///< Req
} MBOX_RSM_BUFFER;

/// CAPS_REQ_BUFFER structure
typedef struct {
  UINT32 Capabilities;                      ///< PSP Writes capabilities into this field when it returns.
} CAPS_REQ_BUFFER;

// Bitmap defining capabilities
#ifndef PSP_CAP_TPM_SUPPORTED
  #define PSP_CAP_TPM_SUPPORTED (1 << 0)      ///< TPM supported
#endif

#ifndef PSP_CAP_TPM_REQ_FACTORY_RESET
  #define PSP_CAP_TPM_REQ_FACTORY_RESET (1 << 1)   ///< TPM requires a factory reset
#endif

#ifndef PSP_CAP_FTPM_NEED_RECOVERY
  #define PSP_CAP_FTPM_NEED_RECOVERY           (1 << 2)   ///< TPM binary authentication fail, trigger recovery mode
#endif

/// MBOX buffer for Capabilities Query
typedef struct {
  MBOX_BUFFER_HEADER  Header;               ///< Header
  CAPS_REQ_BUFFER     Req;                  ///< Req
} MBOX_CAPS_BUFFER;

// Bitmap defining HSTI bitfield
#define HSTISTATE_PSP_SECURE_EN             BIT0
#define HSTISTATE_PSP_PLATFORM_SECURE_EN    BIT1
#define HSTISTATE_PSP_DEBUG_LOCK_ON         BIT2

/// MBOX buffer for HSTI
typedef struct {
  MBOX_BUFFER_HEADER  Header;               ///< Header
  UINT32              HSTIState;            ///< HSTIState
} MBOX_HSTI_STATE;

/// MBOX buffer for MboxBiosCmdPcieInfo
#define PCIE_INFO_DEVID_PROMONTORY          0x01

/// Structure to describe PCIE Device Information
typedef struct {
  UINT32              DevId;                ///< Device ID, unique ID used to identify the device
  PCI_ADDR            Address;              ///< Pcie Device Address
} DEV_INFO;

/// MBOX buffer structure for MboxBiosCmdPcieInfo
typedef struct {
  MBOX_BUFFER_HEADER  Header;               ///< Header
  DEV_INFO            Info;                 ///< PCIE device information
} MBOX_PCIE_INFO_BUFFER;

/// MBOX buffer for Exit BIOS info
typedef struct {
  MBOX_BUFFER_HEADER  Header;               ///< Header
} MBOX_DEFAULT_BUFFER;

typedef UINT32 TEE_STATUS;                  ///< Status of TEE command
#define TEE_OK                                  0x000     ///< TEE command success
#define TEE_ERR_SOC_ADDRESS_MAPPING             0x10C     ///< TEE command error of SOC address mapping
#define TEE_ERR_NWD_INVALID_SESSION             0x10E     ///< TEE command error of invalid session
#define TEE_ERR_NWD_TOO_MANY_MAPPED_BUFFERS     0x10F     ///< TEE command error of too many mapped buffers
#define TEE_ERR_NWD_INVALID_WSM_LEN             0x110     ///< TEE command error of invalid length

/// MBOX buffer for MboxBiosCmdTa
typedef struct {
  MBOX_BUFFER_HEADER  Header;               ///< Header
  UINT64              TaCmdBufferAddress;      ///<Address of TA command buffer
  UINT64              TaCmdBufferSize;         ///< Size of TA command
} MBOX_TA;

//
//
// Define Malbox buffer comming from PSP->BIOS
//

///
/// structure of ReqBuffer for MboxPspCmdSpiGetAddress/MboxPspCmdSpiGetAddress  mailbox command
///
typedef struct {
  UINT64    Attribute;                      ///< Inform attribute of SPI part
} SPI_ATTRIB_REQ;

/// MBOX buffer for Spi Get/Set attribute info
typedef struct {
  MBOX_BUFFER_HEADER      Header;           ///< Header
  SPI_ATTRIB_REQ          Req;              ///< Req
} MBOX_SPI_ATTRIB_BUFFER;


///
/// structure of ReqBuffer for MboxPspCmdSpiGetBlockSize mailbox command
///
typedef struct {
  UINT64  Lba;                              ///< starting LBA
  UINT64  BlockSize;                        ///< Block size of each Lba
  UINT64  NumberOfBlocks;                   ///< Total number of blocks
} SPI_INFO_REQ;

/// MBOX buffer for Spi read block attribute
typedef struct {
  MBOX_BUFFER_HEADER    Header;             ///< Header
  SPI_INFO_REQ          Req;                ///< Req
} MBOX_SPI_INFO_BUFFER;


///
/// structure of ReqBuffer for MboxPspCmdSpiRead/Write mailbox command
///
typedef struct {
  UINT64  Lba;                              ///< starting LBA
  UINT64  Offset;                           ///< Offset in LBA
  UINT64  NumByte;                          ///< Total byte to read
  UINT8   Buffer[1];                        ///< Buffer to read the data
} SPI_RW_REQ;

/// MBOX buffer for Spi read block attribute
typedef struct {
  MBOX_BUFFER_HEADER    Header;             ///< Header
  SPI_RW_REQ            Req;                ///< Req
} MBOX_SPI_RW_BUFFER;


///
/// structure of ReqBuffer for MboxPspCmdSpiErase mailbox command
///
typedef struct {
  UINT64  Lba;                              ///< starting LBA
  UINT64  NumberOfBlocks;                   ///< Total number of blocks
} SPI_ERASE_REQ;

/// MBOX buffer for Spi read block attribute
typedef struct {
  MBOX_BUFFER_HEADER    Header;             ///< Header
  SPI_ERASE_REQ         Req;                ///< Req
} MBOX_SPI_ERASE_BUFFER;

/// Union of various structure
typedef union _MBOX_BUFFER {
  MBOX_DEFAULT_BUFFER       Dflt;           ///< Default

  MBOX_SMM_BUFFER           Smm;            ///< Smm
  MBOX_SX_BUFFER            Sx;             ///< Sx
  MBOX_RSM_BUFFER           Rsm;            ///< Rsm
  MBOX_CAPS_BUFFER          Cap;            ///< Cap
  MBOX_HSTI_STATE           Hsti;           ///< Hsti
  MBOX_PCIE_INFO_BUFFER     PcieInfo;       ///< Pcie info

  MBOX_SPI_ATTRIB_BUFFER    SpiAttrib;      ///< SpiAttrib
  MBOX_SPI_INFO_BUFFER      SpiInfo;        ///< SpiInfo
  MBOX_SPI_RW_BUFFER        SpiRw;          ///< SpiRw
  MBOX_SPI_ERASE_BUFFER     SpiErase;       ///< SpiErase
  UINT8                     Rsvd[32];       ///< To Keep the minimal size 32 bytes
} MBOX_BUFFER;

///
/// X86 to PSP Buffer
/// Each MMIO Block will have Command, Status and Buffer pointer entries.
/// The 8 dword wide MMIO mailbox will be part of PSP-CPU MMIO space
///
typedef struct {
  volatile MBOX_COMMAND     MboxCmd;        ///< Mbox Command 32 bit wide
  volatile MBOX_STATUS      MboxSts;        ///< Mbox status  32 bit wide
  MBOX_BUFFER               *Buffer;        ///< 64 bit Ponter to memory with additional parameter.
} PSP_MBOX;

/// 2x Sized Mailbox Buffer for alignment
typedef struct {
  MBOX_BUFFER   Chunk[2];                   ///< Add additional one for alignment
} UNALIGNED_MBOX_BUFFER;

///
/// Buffer is 2X size of aligned structure of size at least 32 bytes long
/// To align in go to next offset past the buffer size & from there back
/// to 32 byte aligned address
#define BALIGN32(p)  ((VOID *) (((UINTN)(VOID*)(p) + 32) & ~0x1F))


///
/// PSP to X86 Buffer exist in SMMRAM
///
typedef struct {
  volatile MBOX_COMMAND     MboxCmd;        ///< Mbox Command 32 bit wide
  volatile MBOX_STATUS      MboxSts;        ///< Mbox status  32 bit wide
  MBOX_BUFFER               Buffer;         ///< Mailbox buffer right after
} BIOS_MBOX;



#pragma pack (pop)
//======================================================================================
//
// Define Mailbox function prototype
//
//======================================================================================
//
//

EFI_STATUS
CheckFtpmCapsV1 (
  IN OUT   UINT32 *Caps
  );

EFI_STATUS
GetPspMboxLocation (
  IN OUT   PSP_MBOX **PspMbox
  );

EFI_STATUS
PspMboxBiosCmdDramInfo ();

EFI_STATUS
PspMboxBiosCmdS3Info (
  IN UINT64 S3RestoreBufferBase,
  IN UINT64 S3RestoreBufferSize,
  IN OUT   UINT8 *Hmac
   );

EFI_STATUS
PspMboxBiosCmdSmmInfo (
  IN UINT64            SMMBase,
  IN UINT64            SMMLength,
  IN UINT64            PSPSmmDataRegion,
  IN UINT64            PspSmmDataLength,
  IN SMM_TRIGGER_INFO  *SmmTrigInfo,
  IN UINT64            PspMboxSmmBufferAddress,
  IN UINT64            PspMboxSmmFlagAddress

  );

EFI_STATUS
PspMboxBiosCmdSxInfo (
  IN UINT8 SleepType,
  IN UINT8     *SmmBuffer,
  IN BOOLEAN   *SmmFlag
  );

EFI_STATUS
PspMboxBiosCmdResumeInfo (
  IN UINT64 S3ResumeAddress,
  IN UINT64 S3ResumeCodeSize
  );

EFI_STATUS
PspMboxBiosCmdExitBootServices ();

EFI_STATUS
PspMboxBiosCmdNop ();

EFI_STATUS
PspMboxBiosClearS3Status (
  IN UINT8     *SmmBuffer,
  IN BOOLEAN   *SmmFlag
  );

EFI_STATUS
PspMboxBiosQueryHSTIState (
  IN OUT   UINT32 *HSTIState
  );

EFI_STATUS
PspMboxBiosClearSmmLock (
  );

EFI_STATUS
PspMboxBiosPcieInfo (
  UINT32              DevId,
  PCI_ADDR            Address
  );

#endif //_PSP_MBOX_H_

