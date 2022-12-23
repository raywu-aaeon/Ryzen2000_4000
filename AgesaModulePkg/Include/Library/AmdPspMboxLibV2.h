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
 * @e \$Revision: 312133 $   @e \$Date: 2015-02-03 02:47:45 +0800 (Tue, 03 Feb 2015) $
 */
/*****************************************************************************
 *
 * Copyright 2008 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 *******************************************************************************
 **/
#ifndef _PSP_MBOX_H_
#define _PSP_MBOX_H_
#pragma pack (push, 1)

#include <Protocol/GraphicsOutput.h>

typedef union _MBOX_BUFFER MBOX_BUFFER;

#define PSP_NOTIFY_SMM        0xdd    ///< @todo Move it out to other file

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
  MboxBiosCmdGetVersion     = 0x19,   ///< Bios -> PSP: Bios will send this command to get PSP FW image version
  MboxBiosCmdLockDFReg      = 0x1B,   ///< Bios -> PSP: Bios will send this command to lock DF registers
  MboxBiosCmdClrSmmLock     = 0x1C,   ///< Bios -> PSP: Command to clear SMMLock Register in C6 private memory region
  MboxBiosCmdSetApCsBase    = 0x1D,   ///< Bios -> PSP: Bios will send the CS BASE value for AP threads
  MboxBiosCmdKvmInfo        = 0x1E,   ///< Bios -> PSP: KVM required information
  MboxBiosCmdLockSpi        = 0x1F,   ///< BIOS -> PSP: BIOS will send this command to lock SPI, X86 need in SMM mode when send this command
  MboxBiosCmdScreenOnGpio   = 0x20,   ///< BIOS -> PSP: Report the FCH GPIOs for early turn on eDP panel in S0i3 
  MboxBiosCmdSpiOpWhiteList = 0x21,   ///< BIOS -> PSP: BIOS send SPI operation whitelist to lock SPI, X86 need in SMM mode when send this command
  MboxBiosCmdRasEinj        = 0x22,    ///< BIOS -> PSP: BIOS send RAS Error Injection action
  MboxBiosCmdPspCapsQuery   = 0x27,   ///< Bios -> PSP: Bios check PSP NVRAM health
  MboxBiosCmdSetRpmcAddress = 0x39,   ///< BIOS -> PSP: Bios send this command to PSP to decide which RPMC address to use. Only used in product line.
  MboxBiosCmdTa             = 0x40,   ///< Bios -> PSP: Send command to TA

  MboxPspCmdSpiGetAttrib    = 0x81,   ///< PSP -> BIOS: Get location of PSP NVRam region
  MboxPspCmdSpiSetAttrib    = 0x82,   ///< PSP -> BIOS: Get location of PSP NVRam region
  MboxPspCmdSpiGetBlockSize = 0x83,   ///< PSP -> BIOS: Get Block size info
  MboxPspCmdSpiReadFV       = 0x84,   ///< PSP -> BIOS: Read PSP NVRAM firmware volume
  MboxPspCmdSpiWriteFV      = 0x85,   ///< PSP -> BIOS: Write PSP NVRAM firmware volume
  MboxPspCmdSpiEraseFV      = 0x86,   ///< PSP -> BIOS: Erase PSP NVRAM firmware volume
  MboxPspCmdRpmcIncMc       = 0x88,   ///< PSP -> BIOS: Increment Monotonic Counter
  MboxPspCmdRpmcReqMc       = 0x89,   ///< PSP -> BIOS: Request Monotonic Counter
  MboxPspCmdRpmcIncMcWrite  = 0x8A,   ///< PSP -> BIOS: Increment Monotonic Counter then write the PSP NVRAM

  MboxCmdAbort              = 0xfe,   ///< Abort the last command (BIOS to PSP in case of timeout etc)
} MBOX_COMMAND;
#define MboxBiosCmdPsbAutoFusing  0x21

#define PSP_MBOX_SUCCESS                  0x00        ///< Mail box success
#define PSP_MBOX_INVALID_PARAMETER        0x01        ///< Invalid Parameter
#define PSP_MBOX_CRC_ERROR                0x02        ///< CRC error
#define PSP_MBOX_COMMAND_PROCESS_ERROR    0x04        ///< Command process error
#define PSP_MBOX_UNSUPPORTED              0x08        ///< Unsupported
#define PSP_MBOX_SPI_BUSY_ASYNC           0x0A        ///< SPI Bus is busy due Async SPI implementation 
#define PSP_MBOX_SPI_BUSY_FPR_OWNED       0x0B        ///< SPI Bus is busy due SPI finger print take the ownership

typedef UINT32  P2C_MBOX_STATUS;
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
/// SMM register information
typedef struct {
  UINT64  Address;                          ///< Memory or IO address (Memory will be qword, IO will be word)
  UINT32  AddressType;                      ///< SMM trigger typr - Perform write to IO/Memory
  UINT32  ValueWidth;                       ///< Width of value to write (byte write, word write,..)
  UINT32  RegBitMask;                       ///< AND mask of value after reading from the address
  UINT32  ExpectValue;                      ///< OR Mask of value to write to this address.
} SMM_REGISTER;
/// All SMM register report via SMMINFO command
typedef struct {
  SMM_REGISTER SmiEnb;                      ///< Register information for SmiEnb
  SMM_REGISTER Eos;                         ///< Register information for EOS
  SMM_REGISTER FakeSmiEn;                   ///< Register information for FakeSmiEn
  SMM_REGISTER Reserved[5];                 ///< Reserved
} SMM_REGISTER_INFO;
///
/// structure of ReqBuffer for MboxBiosCmdSmmInfo mailbox command
///
typedef struct {
  UINT64            SMMBase;                  ///< SMM TSeg Base
  UINT64            SMMMask;                  ///< Mask of SMM SMM TSeg
  UINT64            PSPSmmDataRegion;         ///< PSP region base in Smm space
  UINT64            PspSmmDataLength;         ///< Psp region length in smm space
  SMM_TRIGGER_INFO  SmmTrigInfo;              ///< Information to generate SMM
  SMM_REGISTER_INFO SmmRegInfo;               ///< Information describe the SMM register information
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

// Bitmap defining Psp Capabilities
#define PSP_NVRAM_HEALTH                  BIT0    ///0 - not healthy, resert needed; 1 - healthy,don't need reset
#define PSP_RPMC_ENABLE                   BIT1    ///0 - Disabled or fail; 1 - Enabled

/// MBOX buffer for PSP Capabilities
typedef struct {
  MBOX_BUFFER_HEADER  Header;               ///< Header
  UINT32              PspCapabilities;       ///< PspNvramStatus
} MBOX_PSP_CAPS_BUFFER;
// Bitmap defining HSTI bitfield
#define HSTISTATE_PSP_SECURE_EN                   BIT0
#define HSTISTATE_PSP_PLATFORM_SECURE_EN          BIT1
#define HSTISTATE_PSP_DEBUG_LOCK_ON               BIT2
#define HSTISTATE_PSP_CUSTOMER_KEY_LOCK_ON        BIT3

/// MBOX buffer for HSTI
typedef struct {
  MBOX_BUFFER_HEADER  Header;               ///< Header
  UINT32              HSTIState;            ///< HSTIState
} MBOX_HSTI_STATE;

/// MBOX buffer for Exit BIOS info
typedef struct {
  MBOX_BUFFER_HEADER  Header;               ///< Header
} MBOX_DEFAULT_BUFFER;


/// CS Base Buffer
typedef struct {
  UINT32  Value;
} AP_CS_BASE_BUFFER;

/// MBOX buffer for ApCsBase
typedef struct {
  MBOX_BUFFER_HEADER      Header;                 ///< Header
  AP_CS_BASE_BUFFER       Req;                    ///< Req
} MBOX_AP_CS_BASE_BUFFER;


/// Version Buffer
typedef struct {
  UINT32              PspFwVersion;       // PSP FW Version
  UINT32              AgesaFwVersion;     // AGESA FW Version
  UINT32              APPBVersion;        // AGESA APPB FW Version
  UINT32              APCBVersion;        // AGESA APCB FW Version
  UINT32              APOBVersion;        // AGESA APOB FW Version
  UINT32              SmuVersion;         // SMU FW Version
} VERSION_BUFFER;

/// MBOX buffer for MboxBiosCmdSetRpmcAddress
typedef struct {
  MBOX_BUFFER_HEADER    Header;                 ///< Header
  UINT32                RpmcAddressToUse;       ///< tell PSP which RPMC address to program, value range 0 to 3
} MBOX_SET_RPMC_ADDRESS_BUFFER;
#define PSP_RPMC_PRODUCTION_ENABLED               BIT8  // fuse bit was set for RPMC Root Key Provision done at Manufacturing
#define PSP_RPMC_COUNTERS                         4    // 4 MC Counters.

/// MBOX buffer for GetVersion
typedef struct {
  MBOX_BUFFER_HEADER  Header;               ///< Header
  VERSION_BUFFER      VersionBuffer;        ///< Buffer composed of multiple FW version
} MBOX_GET_VERSION_BUFFER;

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

#define KVM_DMA_SIZE    (16 * 1024* 1024)
#define KVM_NIC_COHERENCY_SIZE  (256 * 1024)

/// BIOS to KVM mailbox
typedef struct {
  MBOX_BUFFER_HEADER                        Header;               ///< Header
  UINT32                                    KvmDmaAddrLo;               ///< KVM DMA Addr
  UINT32                                    KvmDmaAddrHi;               ///< KVM DMA Addr
  UINT32                                    KvmDmaSize;                 ///< KVM DMA size
} MBOX_KVM;

#define MAX_NUM_WAKEUP_GPIO                 30
typedef struct {
  UINT32                                    NumOfGpio;                  ///< KVM DMA Addr
  UINT32                                    Gpio[MAX_NUM_WAKEUP_GPIO];  ///< Gpio List, filled with GPIO pin number, e.g. Gpio[0]= 3, Gpio[1]=5, denote GPIO Pin #3 (AGPIO3) & #5 (AGPIO5_DEVSLP0)
} SCREENON_GPIO_LIST;

/// MboxBiosCmdScreenOnGpio
typedef struct {
  MBOX_BUFFER_HEADER                        Header;                     ///< Header
  SCREENON_GPIO_LIST                        List;                       ///< Gpio List
} MBOX_SCREENON_GPIO;


//MboxBiosCmdSpiOpWhiteList
// OpCode[7:0]   - this is simply the "whitelist" Opcode
// Options[1:0]  -
//               0              0              This OpCode does not require additional check
//               0              1              This is WRITE command, firmware should make sure the address does not cross cacheline.
//                                               We will rely on hw to enforce the address checking
//               1              0              This is READ command, firmware should make sure the address does not cross cacheline.
//                                               We will rely on hw to enforce the address checking
//               1              1              This Opcode is a ERASE command with address.  This Option will require a
//                                               SIZE field.  Firmware will check the address in index FIFO:
//                                             a)  Does not cross write protection range
//                                             b)  Aligns with SIZE definition accordingly.  For example, if the SIZE is 256B, lower
//                                                 8 bit address must be all 0s.
// Size[2:0]     - This field defines the size of ERASE:
//                  000b == 256B,
//                  001b == 512B,
//                  010b == 1KB,
//                  011b == 2KB,
//                  100b == 4KB,
//                  101b == 8KB,
//                  110b == 16KB,
//                  111b == 32KB
typedef struct {
  UINT8                                    OpCode;      ///< SPI OpCodes
  UINT8                                    Options;     ///< Option of SPI OpCodes
  UINT8                                    Size;        ///< Defines the size of ERASE
  UINT8                                    Frequency;   ///< Reserved
} SPI_OP;

#define MAX_NUM_SPI_OP                      32
typedef struct {
  UINT32                                    NumOfOp;                    ///< Number of SPI Operation
  SPI_OP                                    Ops[MAX_NUM_SPI_OP];        ///< SPI opreations
} SPI_OP_LIST;

typedef struct {
  MBOX_BUFFER_HEADER                        Header;                     ///< Header
  SPI_OP_LIST                               List;                       ///< SPI OP List
  UINT32                                    ROMAddrRng2;                ///< ROMAddrRng2 of LPC PCI 0x6C
  UINT32                                    RomProtect[4];                ///< RomProtect of LPC PCI 0x50-0x5C
} MBOX_SPI_OP_WHITELIST;

//MboxBiosCmdRasEinj
#define RAS_EINJ_ENABLE_INJECTION                0x1
#define RAS_EINJ_BEGIN_INJECTION_OPERATION       0x2
#define RAS_EINJ_END_OPERATION                   0x3
#define RAS_EINJ_EXECUTE_OPERATION               0x4

typedef struct {
  MBOX_BUFFER_HEADER                        Header;                     ///< Header
  UINT32                                    Action;                   ///< Action of EINJ interface, will have structure following by depend on the action ID.
} MBOX_RAS_EINJ;

typedef struct {
  UINT64 SysMemAddr;
  UINT32 UmcRegBase;
  UINT16 EccInjVector;
  UINT8  ChipSelect;
} RAS_EINJ_EXECUTE_OPERATION_STRUCT;

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
  UINT64  TargetNvId;                       ///< Target NV ID
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
  UINT64  TargetNvId;                       ///< Target NV ID
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
  UINT64  TargetNvId;                       ///< Target NV ID
  UINT64  Lba;                              ///< starting LBA
  UINT64  NumberOfBlocks;                   ///< Total number of blocks
} SPI_ERASE_REQ;

/// MBOX buffer for Spi read block attribute
typedef struct {
  MBOX_BUFFER_HEADER    Header;             ///< Header
  SPI_ERASE_REQ         Req;                ///< Req
} MBOX_SPI_ERASE_BUFFER;


///
/// structure of MboxPspCmdRpmcIncMc
///
typedef struct {
  UINT32   CounterAddr;                      ///< Input, CounterAddr for the "Increment Monotonic Counter" SPI command
  UINT32  CounterData;                      ///< Input, CounterData for the "Increment Monotonic Counter" SPI command
  UINT8   Signature[32];                    ///< Input, Signature for the "Increment Monotonic Counter" SPI command
} SPI_RPMC_INC_MC_REQ;

/// MBOX buffer for MboxPspCmdRpmcIncMc
typedef struct {
  MBOX_BUFFER_HEADER    Header;             ///< Header
  SPI_RPMC_INC_MC_REQ   Req;                ///< Req
} MBOX_SPI_RPMC_INC_MC_BUFFER;

///
/// structure of MboxPspCmdRpmcReqMc
///
typedef struct {
  UINT32   CounterAddr;                      ///< Input, CounterAddr for the "Request Monotonic Counter" SPI command
  UINT8   Tag[12];                          ///< Input, Tag for the "Request Monotonic Counter" SPI command
  UINT8   Signature[32];                    ///< Input, Signature for the "Request Monotonic Counter" SPI command
  UINT32  CounterData;                      ///< Output, CounterData for the "Request Monotonic Counter" SPI command
  UINT8   OutputSignature[32];              ///< Output, Returned Signature for the "Request Monotonic Counter" SPI command
} SPI_RPMC_REQ_MC;

/// MBOX buffer for MboxPspCmdRpmcReqMc
typedef struct {
  MBOX_BUFFER_HEADER    Header;             ///< Header
  SPI_RPMC_REQ_MC       Req;                ///< Req
} MBOX_SPI_RPMC_REQ_MC_REQ_BUFFER;

///
/// structure of MboxPspCmdRpmcIncMcWrite
///

/// MBOX buffer for MboxPspCmdRpmcIncMcWrite
/// Command with batch command
/// 1st execute multiple "Increment Monotonic Counter" command to increase MC
/// 2nd write the SPI as denoted in SPI_RW_REQ structure
typedef struct {
  MBOX_BUFFER_HEADER    Header;             ///< Header
  SPI_RPMC_INC_MC_REQ   McIncReq;           ///< Req for increase the MC
  SPI_RW_REQ            WriteReq;           ///< Req for Write
} MBOX_SPI_RPMC_INC_MC_WRITE_BUFFER;



/// Union of various structure
typedef union _MBOX_BUFFER {
  MBOX_DEFAULT_BUFFER       Dflt;           ///< Default

  MBOX_SMM_BUFFER           Smm;            ///< Smm
  MBOX_SX_BUFFER            Sx;             ///< Sx
  MBOX_RSM_BUFFER           Rsm;            ///< Rsm
  MBOX_CAPS_BUFFER          Cap;            ///< Cap
  MBOX_GET_VERSION_BUFFER   Ver;            ///< Version
  MBOX_AP_CS_BASE_BUFFER    CsBase;         ///< CS base
  MBOX_SCREENON_GPIO        Gpio;           ///< GPIO
  MBOX_SPI_OP_WHITELIST     WhiteList;      ///< WhiteList
  MBOX_SPI_ATTRIB_BUFFER    SpiAttrib;      ///< SpiAttrib
  MBOX_SPI_INFO_BUFFER      SpiInfo;        ///< SpiInfo
  MBOX_SPI_RW_BUFFER        SpiRw;          ///< SpiRw
  MBOX_SPI_ERASE_BUFFER     SpiErase;       ///< SpiErase
  UINT8                     Rsvd[32];       ///< To Keep the minimal size 32 bytes
} MBOX_BUFFER;

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
  UINT32 CheckSumValue:8;   ///< 8bits Checksum Value of MBOX_BUFFER
  UINT32 CheckSumEn:1;      ///< Switch for Enable/Disable Checksum
  UINT32 Reserved:22;          ///< Reserved
  UINT32 CommandReady:1; ///< Flag used specify P2C SMI command is ready to handle a new command
} SMI_MBOX_STATUS;

/// PSP to BIOS SMI mailbox structure
typedef struct {
  volatile MBOX_COMMAND     MboxCmd;        ///< Mbox Command 32 bit wide
  volatile SMI_MBOX_STATUS  MboxSts;        ///< Mbox status  32 bit wide
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
CheckPspCapsV2 (
  IN OUT   UINT32 *PspCaps
  );

EFI_STATUS
CheckFtpmCapsV2 (
  IN OUT   UINT32 *Caps
  );


EFI_STATUS
PspMboxBiosCmdS3Info (
  IN UINT64 S3RestoreBufferBase,
  IN UINT64 S3RestoreBufferSize,
  IN OUT   UINT8 *Hmac
   );

EFI_STATUS
PspMboxBiosCmdSmmInfo (
  IN SMM_REQ_BUFFER      *SmmInfoReq
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
PspMboxBiosQueryHSTIState (
  IN OUT   UINT32 *HSTIState
  );

EFI_STATUS
PspMboxBiosSendApCsBase (
  IN       UINT32 ApCsBase
  );

EFI_STATUS
PspMboxBiosGetFwVersions (
  IN OUT   VERSION_BUFFER *FwVersions
  );

EFI_STATUS
PspMboxBiosCmdKvmInfo (
  MBOX_KVM *KvmMboxMemBuffer
  );

EFI_STATUS
PspMboxBiosClearSmmLock (
  IN UINT8     *SmmBuffer,
  IN BOOLEAN   *SmmFlag
  );

EFI_STATUS
PspMboxBiosLockDFReg (
  );

EFI_STATUS
PspMboxBiosLockSpi (
  );

EFI_STATUS
PspMboxBiosScreenOnGpio (
  SCREENON_GPIO_LIST *GpioList
  );

EFI_STATUS
PspMboxBiosSpiOpWhiteList (
  SPI_OP_LIST *WhiteList,
  IN UINT8     *SmmBuffer,
  IN BOOLEAN   *SmmFlag
  );

EFI_STATUS
PspMboxBiosRasEinj (
  UINT32  Action,
  VOID    *ActionStruct
  );

EFI_STATUS
PspMboxBiosPsbAutoFusing (
  );
  
EFI_STATUS
PspMboxPspCapsQuery (
  IN OUT   UINT32 *PspCapabilities
  );
  /**
  * Bios send this command to PSP to decide which RPMC address to use.
  * A warm reset should be issued after receiving BIOS_MBOX_OK (0) from PSP tOS, otherwise BIOS do nothing.
  * It's caller's responsbility to issue the warm reset.
  *
  * @param[in]  RpmcAddressToUse           which RPMC address to program. Value 1 to 3
  *
  @retval EFI_STATUS              0: Success, NonZero Error
  * for example: 0x14 means the PSP report RPMC not available
**/
EFI_STATUS
PspMboxBiosCmdSetRpmcAddress (
  UINT32                RpmcAddressToUse
  );
#endif //_PSP_MBOX_H_

