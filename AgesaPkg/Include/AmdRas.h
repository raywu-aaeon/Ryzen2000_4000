/*****************************************************************************
 *
 * Copyright 2016 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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

#ifndef _AMD_RAS_H_
#define _AMD_RAS_H_

/// ACPI define
#define BERT_SIG SIGNATURE_32('B', 'E', 'R', 'T')

#define ERROR_TYPE_RAW          (1)
#define ERROR_TYPE_GENERIC      (2)

/// BERT Block Status Bits
#define ERROR_UNCORR_VALID      (1 << 0)
#define ERROR_CORR_VALID        (1 << 1)
#define MULT_UNCORR_ERROR_VALID (1 << 2)
#define MULT_CORR_ERROR_VALID   (1 << 3)

/// ACPI 6.1 Table 18-343 Generic Error Data Entry
#define ERROR_RECOVERABLE           (0)
#define ERROR_SEVERITY_FATAL        (1)
#define ERROR_SEVERITY_CORRECTED    (2)
#define ERROR_NONE                  (3)

/// Validation bits UEFI spec2.6
#define FRU_ID_VALID                        (1 << 0)
#define FRU_STRING_VALID                    (1 << 1)

//
//AMD vendor specific error section GUID
//

/// NBIO Error Section GUID
#define NBIO_ERROR_SECT_GUID \
  { 0x911CAC2E, 0xA256, 0x4F84, 0xA3, 0xD3, 0xDD, 0xAE, 0x89, 0x9B, 0x27, 0x28 }
  //911CAC2E-A256-4F84-A3D3DDAE899B2728

/// SMU-SMN Error Section GUID
#define SMN_ERROR_SECT_GUID \
  { 0xA2860CC1, 0x8987, 0x4B7C, 0xB8, 0x6A, 0xD5, 0x08, 0xB1, 0x76, 0xBA, 0x70 }
  // A2860CC1-8987-4B7C-B86A-D508B176BA70

/// Serial-ATA (SATA) Parity and ECC Error Section GUID
#define SATA_ERROR_SECT_GUID \
  { 0x7C27AAD8, 0x06D4, 0x4ABA, 0xB2, 0x0D, 0x42, 0xA8, 0x79, 0x50, 0xD0, 0xE4 }
  //7C27AAD8-06D4-4ABA-B20D-42A87950D0E4

/// Fusion Controller Hub (FCH) A-Link Parity Error Section GUID
#define FCH_ALINK_ERROR_SECT_GUID \
  { 0x896798ED, 0x2514, 0x4E2B, 0xB4, 0x5A, 0x15, 0x27, 0x3F, 0x30, 0x2B, 0x94 }
  //896798ED-2514-4E2B-B45A-15273F302B94

/// Universal Serial Bus (USB) Parity and ECC Error Section GUID
#define USB_ERROR_SECT_GUID \
  { 0xCC366EE9, 0x1EC5, 0x4140, 0x89, 0xBF, 0xE1, 0x28, 0xAC, 0xED, 0x27, 0xAB }
  //CC366EE9-1EC5-4140-89BF-E128ACED27AB


//NBIO

//Structure

typedef struct _SMM_SAVE_STATE {
   UINT64   ES[2];                           //FE00
   UINT64   CS[2];                           //FE10
   UINT64   SS[2];                           //FE20
   UINT64   DS[2];                           //FE30
   UINT64   FS[2];                           //FE40
   UINT64   GS[2];                           //FE50
   UINT64   GDTR[2];                         //FE60
   UINT64   LDTR[2];                         //FE70
   UINT64   IDTR[2];                         //FE80
   UINT64   TR[2];                           //FE90
   UINT64   IO_RESTAERT_RIP;                 //FEA0
   UINT64   IO_RESTAERT_RCX;                 //FEA8
   UINT64   IO_RESTAERT_RSI;                 //FEB0
   UINT64   IO_RESTAERT_RDI;                 //FEB8
   UINT32   TrapoFFSET;                      //FEC0
   UINT32   LocalSmiStatus;                  //FEC4
   UINT8    IoRestart;                       //FEC8
   UINT8    AutoHalt;                        //FEC9
   UINT8    NmiMask;                         //FECA
   UINT8    Reserved1[5];                    //FECB
   UINT64   EFER;                            //FED0
   UINT64   SvmState;                        //FED8
   UINT64   GuestVMCBPyysicalAddress;        //FEE0
   UINT64   SVMVirtualInterruptControl;      //FEE8
   UINT8    Reserved2[12];                   //FEF0
   UINT32   SMMRevId;                        //FEFC
   UINT32   SMBASE;                          //FF00
   UINT8    Reserved3[28];                   //FF04
   UINT64   GuestPAT;                        //FF20
   UINT64   HostEFER;                        //FF28
   UINT64   HostCR4;                         //FF30
   UINT64   NestedCR3;                       //FF38
   UINT64   HostCR0;                         //FF40
   UINT64   CR4;                             //FF48
   UINT64   CR3;                             //FF50
   UINT64   CR0;                             //FF58
   UINT64   DR7;                             //FF60
   UINT64   DR6;                             //FF68
   UINT64   RFLAGS;                          //FF70
   UINT64   RIP;                             //FF78
   UINT64   R15;                             //FF80
   UINT64   R14;                             //FF88
   UINT64   R13;                             //FF90
   UINT64   R12;                             //FF98
   UINT64   R11;                             //FFA0
   UINT64   R10;                             //FFA8
   UINT64   R9;                              //FFB0
   UINT64   R8;                              //FFB8
   UINT64   RDI;                             //FFC0
   UINT64   RSI;                             //FFC8
   UINT64   RBP;                             //FFD0
   UINT64   RSP;                             //FFD8
   UINT64   RBX;                             //FFE0
   UINT64   RDX;                             //FFE8
   UINT64   RCX;                             //FFF0
   UINT64   RAX;                             //FFF8
} SMM_SAVE_STATE;

/// RAS NBIO Group Type enumerate
typedef enum _NBIO_GRP_TYPE_NUM {
  NBIO_GRP_UNCORR = 0,      ///< / 0  = Uncorrectable Parity Group
  NBIO_GRP_CORR = 1,        ///< / 1  = Correctable Parity Group
  NBIO_GRP_UCP = 3,         ///< / 3  = Uncorrectable converts to poison data parity group
} NBIO_GRP_TYPE_NUM;

/// RAS MCA Bank enumerate
typedef enum _MCA_INT_TYPE_NUM {
//CORE MCA Banks, access through each thread.
  MCA_NO_INTERRUPT = 0,      ///< / 0  = No Interrupt
  MCA_APIC,                  ///< / 1  = APIC based interrupt (LVT)
  MCA_SMI,                   ///< / 2  = SMI trigger event
  MCA_RESERVED,              ///< / 3  = Reserved
} MCA_INT_TYPE_NUM;

/// RAS SMN Category enumerate
typedef enum _SMN_CATEGORY_NUM {
  SMN_CATEGORY_UNCORR = 0,         ///< / 0  = Uncorrectable Category
  SMN_CATEGORY_CORR = 1,           ///< / 1  = Correctable Category
  SMN_CATEGORY_FATAL = 2,          ///< / 2  = Fatal Category
  SMN_CATEGORY_UCP = 3,            ///< / 3  = Uncorrectable converts to poison data Category
} SMN_CATEGORY_NUM;

/// DRAM Limit Address Register
typedef union {
  struct {
     UINT64       IoTrapSts:4;              ///< [3:0] IO Trap Status
     UINT64       :4;                       ///< [7:4] Reserved
     UINT64       MceRedirSts:1;            ///< [8] Machine check exception redirection status
     UINT64       :2;                       ///< [10:9] Reserved
     UINT64       WrMsr:1;                  ///< [11] SMM due to a WRMSR of an MCE_STATUS
     UINT64       :4;                       ///< [15:12] Reserved
     UINT64       SmiSrcLvtLgcy:1;          ///< [16] SMI source is legacy LVT APIC entry
     UINT64       SmiSrcLvtExt:1;           ///< [17] SMI source is APIC[530:500] LVT
     UINT64       SmiSrcMca:1;              ///< [18] SMI source is MCA
     UINT64       :54;                      ///< [63:19] Reserved
  } Field;
  UINT64  Value;
} LOCAL_SMI_STATUS;

///UMC CH registers
typedef union {
  struct {
     UINT32       RegchClkGateEn:1;         ///< Enable configuration register clock gating
     UINT32       DisDebugBusSel:1;         ///< Specific UMC debug bus configuration writes.
     UINT32       DisErrInj:1;              ///< Specific UMC error injection configuration writes.
     UINT32       AutoRefReorderArb:1;      ///<
     UINT32       AutoRefReorderRec:1;      ///<
     UINT32       AutoRefNoTimingQualRec:1; ///<
     UINT32       :26;                      ///< Reserved
  } Field;
  UINT32  Value;
} UMC_MISCCFG_REG;

typedef union {
  struct {
     UINT32       WrEccEn:1;                ///< Enables ECC generation for DRAM data.
     UINT32       :3;                       ///< Reserved
     UINT32       EccBadDramSymEn:1;        ///< Enables the software managed ECC history mechanism for x8 symbol size.
     UINT32       EccHardwareHistoryEn:1;   ///< Enables the hardware managed ECC history mechanism for x8 symbol size.
     UINT32       EccBitInterleaving:1;     ///<
     UINT32       EccSymbolSize:1;          ///< 0=x4 symbol. 1=x8 symbol.
     UINT32       UCFatalEn:1;              ///< Promote uncorrectable errors from deferred to fatal.
     UINT32       EccSymbolSize16:1;        ///< 1=x16 symbol. 0=use EccSymbolSize
     UINT32       RdEccEn:1;                ///< Enable DRAM data ECC checking and correction.
     UINT32       :21;                      ///< Reserved
  } Field;
  UINT32  Value;
} UMC_ECCCTRL_REG;

typedef union {
  struct {
     UINT32       EccErrPersistentEn:1;     ///< Enable continuous error injection.
     UINT32       EccErrOneShotEn:1;        ///< Enable a single error injection.
     UINT32       EccErrAddrEn:1;           ///< Allow address-based injection from the DF CS.
     UINT32       :29;                      ///< Reserved
  } Field;
  UINT32  Value;
} UMC_ECCERRINJCTRL_REG;

/// RAS UMC EXT_ERROR_CODE enumerate
typedef enum _UMC_EXT_ERROR_CODE_NUM {
  UMC_DRAMECCERR = 0,                       ///< DRAM ECC error.
  UMC_WRITEDATAPOISONERR,                   ///< Data poison error.
  UMC_SDPPARITYERR,                         ///< SDP parity error.
  UMC_APBERR,                               ///< Advanced peripheral bus error.
  UMC_ADDRCMDPARITYERR,                     ///< Address/command parity error.
  UMC_WRITEDATACRCERR,                      ///< Write data CRC error.
} UMC_EXT_ERROR_CODE_NUM;

typedef union {
  struct {
     UINT32       EccInjVector:16;          ///<
     UINT32       EccInjEn:9;               ///<
     UINT32       :7;                       ///< Reserved
  } Field;
  UINT32  Value;
} UMC_ECCERRINJ_REG;

///DF
/// DRAM Scrubber Base Address Register
typedef union {
  /// Bitfields of DRAM Scrubber Base Address Register
  struct {
    UINT32 DramScrubEn:1;              ///< DRAM Scrub Enable
    UINT32 :3;                         ///< Reserved
    UINT32 DramScrubBaseAddr:28;       ///< DRAM Scrub Base Address
  } Fields;
  UINT32  Value;
} DRAM_SCRUB_BASEADDR_REG;

/// DRAM Scrubber Error Address Lo Register
typedef union {
  /// Bitfields of DRAM Scrubber Error Address Lo Register
  struct {
    UINT32 ErrInjEn:1;                      ///< A new command to inject error is triggered by writing a 1
    UINT32 ErrInjDone:1;                    ///< Set by hardware once the write is sent to CS
    UINT32 LockAndDisErrInj:1;              ///< Lock error injection widget
    UINT32 :3;                              ///< Reserved
    UINT32 ErrInjAddrLo:26;                 ///< Error injection address low
  } Fields;
  UINT32  Value;
} DRAM_SCRUB_ERRORADDR_LO_REG;

/// DRAM Scrubber Error Address Hi Register
typedef union {
  /// Bitfields of DRAM Scrubber Error Address Hi Register
  struct {
    UINT32 ErrInjAddrHi:16;                 ///< Error injection address high
    UINT32 :16;                             ///< Reserved
  } Fields;
  UINT32  Value;
} DRAM_SCRUB_ERRORADDR_HI_REG;

/// DRAM Scrubber Address Lo Register
typedef union {
  /// Bitfields of DRAM Scrubber Address Lo Register
  struct {
    UINT32 MemInitEnable :1;  ///< Enables memory initialization
    UINT32 MemInitDone   :1;  ///< This bit is set by hardware once it has cleared the memory
    UINT32 DisMemInit    :1;  ///< BIOS or PSP should set the bit when it wants to protect any other malicious software from clearing memory
    UINT32               :3;  ///< Reserved
    UINT32 SeqScrubAddrLo:26; ///< Scrubber Address Low
  } Fields;
  UINT32  Value;
} DRAM_SCRUB_ADDR_LO_REG;

/// DRAM Scrubber Address Hi Register
typedef union {
  /// Bitfields of DRAM Scrubber Address Hi Register
  struct {
    UINT32 SeqScrubAddrHi:16;  ///< Scrubber Address High
    UINT32               :16;  ///< Reserved
  } Fields;
  UINT32  Value;
} DRAM_SCRUB_ADDR_HI_REG;

///MCA
typedef union {
  struct {
     UINT64       ErrorCode:16;             ///<
     UINT64       ErrorCodeExt:6;           ///<
     UINT64       :10;                      ///< Reserved
     UINT64       ErrorCodeId:6;            ///<
     UINT64       :2;                       ///< Reserved
     UINT64       Scrub:1;                  ///< 1 = The error was the result of a scrub operation.
     UINT64       :2;                       ///< Reserved
     UINT64       Poison:1;                 ///< 1 = The error was the result of attempting to consume poisoned data.
     UINT64       Deferred:1;               ///< 1 = A deferred error was created.
     UINT64       UECC:1;                   ///< 1 = The error was an uncorrectable ECC error
     UINT64       CECC:1;                   ///< 1 = The error was a correctable ECC error
     UINT64       :5;                       ///< Reserved
     UINT64       Transparent:1;            ///< 1 = This error is a transparent error.
     UINT64       SyndV:1;                  ///< 1 = This error logged information in MCA_SYND
     UINT64       :1;                       ///< Reserved
     UINT64       TCC:1;                    ///< 1 = The thread which consumed the error is not restartable and must be terminated.
     UINT64       ErrCoreIdVal:1;           ///< 1 = The ErrCoreId field is valid
     UINT64       PCC:1;                    ///< 1 = Hardware context held by the processor may have been corrupted
     UINT64       AddrV:1;                  ///< 1 = MCA_ADDR contains adderss information
     UINT64       MiscV:1;                  ///< 1 = Valid thresholding in MCA_MISC0
     UINT64       En:1;                     ///< 1 = MCA error reporting is enabled for this error.
     UINT64       UC:1;                     ///< 1 = The error was not corrected by hardware
     UINT64       Overflow:1;               ///< 1 = An error was detected while the valid bit was set
     UINT64       Val:1;                    ///< 1 = A valid error has been detected
  } Field;
  UINT64  Value;
} MCA_STATUS_MSR;

typedef union {
  struct {
     UINT64       :44;                      ///< Reserved
     UINT64       Deferred:1;               ///< 1 = A deferred error was created.
     UINT64       :8;                       ///< Reserved
     UINT64       SyndV:1;                  ///< 1 = This error logged information in MCA_SYND
     UINT64       :4;                       ///< Reserved
     UINT64       AddrV:1;                  ///< 1 = MCA_ADDR contains adderss information
     UINT64       :3;                       ///< Reserved
     UINT64       Overflow:1;               ///< 1 = An error was detected while the valid bit was set
     UINT64       Val:1;                    ///< 1 = A valid error has been detected
  } Field;
  UINT64  Value;
} MCA_DESTAT_MSR;

typedef union {
  struct {
     UINT64       ErrorAddr:56;             ///< Error Address
     UINT64       LSB:6;                    ///< Least significant valid bit
     UINT64       :2;                       ///< Reserved
  } Field;
  UINT64  Value;
} MCA_ADDR_MSR;

typedef union {
  struct {
     UINT64       :24;                       ///< Reserved
     UINT64       BlkPtr:8;                  ///< 01h=Extended MSR block is valid.
     UINT64       ErrCnt:12;                 ///< Error Counter
     UINT64       :4;                        ///< Reserved
     UINT64       Ovrflw:1;                  ///< Set by hardware when ErrCnt transitions from FFEh to FFFh.
     UINT64       ThresholdIntType:2;        ///< Type of interrupt signal
     UINT64       CntEn:1;                   ///< 1=Count thresholding errors.
     UINT64       LvtOffset:4;               ///< Error thresholding interrupt LVT address
     UINT64       :4;                        ///< Reserved
     UINT64       IntP:1;                    ///< 1=ThresholdIntType can be used to generate interrupts.
     UINT64       Locked:1;                  ///< 1=Writes to this register are ignored
     UINT64       CntP:1;                    ///< 1=A valid threshold counter is present
     UINT64       Valid:1;                   ///< 1=A valid CntP field is present in this register.
  } Field;
  UINT64  Value;
} MCA_MISC0_MSR;

typedef union {
  struct {
     UINT64       :24;                       ///< Reserved
     UINT64       BlkPtr:8;                  ///< 01h=Extended MSR block is valid.
     UINT64       ErrCnt:12;                 ///< Error Counter
     UINT64       :4;                        ///< Reserved
     UINT64       Ovrflw:1;                  ///< Set by hardware when ErrCnt transitions from FFEh to FFFh.
     UINT64       ThresholdIntType:2;        ///< Type of interrupt signal
     UINT64       CntEn:1;                   ///< 1=Count thresholding errors.
     UINT64       :8;                        ///< Reserved
     UINT64       IntP:1;                    ///< 1=ThresholdIntType can be used to generate interrupts.
     UINT64       Locked:1;                  ///< 1=Writes to this register are ignored
     UINT64       CntP:1;                    ///< 1=A valid threshold counter is present
     UINT64       Valid:1;                   ///< 1=A valid CntP field is present in this register.
  } Field;
  UINT64  Value;
} MCA_MISC1_MSR;

typedef union {
  struct {
     UINT64       McaX:1;                               ///< Reserved
     UINT64       TransparentErrorLoggingSupported:1;   ///< 01h=Extended MSR block is valid.
     UINT64       DeferredErrorLoggingSupported:1;      ///< Error Counter
     UINT64       :2;                                   ///< Reserved
     UINT64       DeferredIntTypeSupported:1;           ///< Set by hardware when ErrCnt transitions from FFEh to FFFh.
     UINT64       :26;                                  ///< Reserved
     UINT64       McaXEnable:1;                         ///< Type of interrupt signal
     UINT64       TransparentErrorLoggingEnable:1;      ///< 1=Count thresholding errors.
     UINT64       LogDeferredInMcaStat:1;               ///< Log Deferred error in MCA_STATUS
     UINT64       :2;                                   ///< Reserved
     UINT64       DeferredIntType:2;                    ///< Type of Deferred error interrupt.
     UINT64       :25;                                  ///< Reserved
  } Field;
  UINT64  Value;
} MCA_CONFIG_MSR;

// Syndrome Error Priority
#define MCA_SYND_ERROR_PRIORITY_NO_ERROR    0x00
#define MCA_SYND_ERROR_PRIORITY_RESERVED    0x01
#define MCA_SYND_ERROR_PRIORITY_CORRECTED   0x02
#define MCA_SYND_ERROR_PRIORITY_DEFERRED    0x03
#define MCA_SYND_ERROR_PRIORITY_UNCORRECTED 0x04
#define MCA_SYND_ERROR_PRIORITY_FATAL       0x05

// Syndrome Types
#define MCA_SYND_TYPE_DRAM_ERR 0x00
#define MCA_SYND_TYPE_CACHE_ERR 0x01
#define MCA_SYND_TYPE_INTERNAL_ERR 0x02

typedef union {
  struct {
     UINT64       ErrorInformation:18;      ///< Contains error-specific information about the location of the error.
     UINT64       Length:6;                 ///< Specifies the length in bits of the syndrome.
     UINT64       ErrorPriority:3;          ///< Encodes the priority of the error logged.
     UINT64       :1;                       ///< Reserved
     UINT64       Type:4;                   ///< Type
     UINT64       Syndrome:32;              ///< Contains the syndrome, if any, associated with the error.
  } Field;
  UINT64  Value;
} MCA_SYND_MSR;

typedef union {
  struct {
     UINT64       InstanceId:32;            ///< The instance ID of this IP.
     UINT64       HardwareID:12;            ///< The Hardware ID of the IP associated with this MCA bank.
     UINT64       :4;                       ///< Reserved
     UINT64       McaType:16;               ///< The McaType of the MCA bank within this IP.
  } Field;
  UINT64  Value;
} MCA_IPID_MSR;

typedef struct _CPU_INFO {
  UINTN        ProcessorNumber;
  UINT8        SocketId;
  UINT8        CcxId;
  UINT8        DieId;
  UINT8        CoreId;
  UINT8        ThreadID;
} CPU_INFO;

#define MCA_BANK_ERROR_INFO_REG_NUM     (9)
#define MAX_SEC_PROC_CONTEXT_INFO_ARRY_NUM  (2)

typedef struct _MCA_BANK_ERROR_INFO {
  UINTN                 McaBankNumber;
  MCA_STATUS_MSR        McaStatusMsr;
  MCA_ADDR_MSR          McaAddrMsr;
  MCA_MISC0_MSR         McaMisc0Msr;
  MCA_CONFIG_MSR        McaConfigMsr;
  MCA_IPID_MSR          McaIpidMsr;
  MCA_SYND_MSR          McaSyndMsr;
  MCA_DESTAT_MSR        McaDeStatMsr;
  MCA_ADDR_MSR          McaDeAddrMsr;
  MCA_MISC1_MSR         McaMisc1Msr;
} MCA_BANK_ERROR_INFO;

#define ZP_MCA_MAX_BANK_COUNT (23)
#define SSP_MCA_MAX_BANK_COUNT (28)

typedef struct _RAS_MCA_ERROR_INFO {
  CPU_INFO              CpuInfo;
  MCA_BANK_ERROR_INFO   McaBankErrorInfo[ZP_MCA_MAX_BANK_COUNT];
} RAS_MCA_ERROR_INFO;

typedef struct _RAS_MCA_ERROR_INFO_V2 {
  CPU_INFO              CpuInfo;
  UINTN                 McaBankCount;
  MCA_BANK_ERROR_INFO   McaBankErrorInfo[SSP_MCA_MAX_BANK_COUNT];
} RAS_MCA_ERROR_INFO_V2;

typedef struct _RAS_NBIO_ERROR_INFO {
  UINT8                 Die;
  UINT8                 DieBusNumber;
  NBIO_GRP_TYPE_NUM     TypeId;
  UINT8                 GroupId;
  UINT32                NbioGlobalStatusLo;
  UINT32                NbioGlobalStatusHi;
  UINT32                NbioParityErrorStsAddr;
  UINT32                NbioParityErrorSts;
} RAS_NBIO_ERROR_INFO;

/// Request the identity of dimm from system address
typedef struct {
  UINT64  normalizedAddr;               ///< Error Address that needs to be translated to dimm identification.
  UINT8   normalizedSocketId;           ///< The socket on which the targeted address locates.
  UINT8   normalizedDieId;              ///< The die on which the targeted address locates.
  UINT8   normalizedChannelId;          ///< The die on which the targeted address locates.
  UINT8   reserved;                     ///< Reserved
} NORMALIZED_ADDRESS;

typedef struct _DIMM_INFO {
  UINT8     ChipSelect;                 ///< The chip select on which the targeted address locates.
  UINT8     Bank;                       ///< The Bank for which the error address resides
  UINT32    Row;                        ///< The Row for which the error address resides
  UINT16    Column;                     ///< The Column for which the error address resides
  UINT8     rankmul;                    ///< The Rank Multiplex for which the error address resides
  UINT8     DimmId;                     ///< Reserved
} DIMM_INFO;

typedef struct _RAS_THRESHOLD_CONFIG {
  BOOLEAN  ThresholdControl;
  UINT16   ThresholdCount;
  UINT8    ThresholdIntType;
} RAS_THRESHOLD_CONFIG;

//
//AMD vendor specific error section structure
//

#define DXIO_PHYTYPE_PCIE     (0)
#define DXIO_PHYTYPE_SATA     (1)
#define DXIO_PHYTYPE_XGBE     (2)
#define DXIO_PHYTYPE_XGMI     (3)
#define DXIO_PHYTYPE_WAFL     (4)
#define DXIO_PHYTYPE_WAFLPCIE (5)

typedef union {
  struct {
    UINT8        Pcs:2;                 ///< [1:0] Pcs Intance
    UINT8        Id:3;                  ///< [4:2] The ID of the Type
    UINT8        PhyType:3;             ///< [7:5] Error Source Phy Type
  } Field;
  UINT8  Value;
} DXIO_ERR_ID;

typedef union {
  struct {
    UINT32       BusId:1;               ///< [0] Bus ID
    UINT32       ErrorSource:1;         ///< [1] Error Source
    UINT32       ErrorType:1;           ///< [2] Error Type
    UINT32       GroupType:1;           ///< [3] Group Type
    UINT32       GroupId:1;             ///< [4] Group ID
    UINT32       NbifId:1;              ///< [5] Leaf ID
    UINT32       LeafId:1;              ///< [6] Leaf ID
    UINT32       ParityErrSts:1;        ///< [7] Parity Error Status
    UINT32       :24;                   ///< [31:8] Reserved
  } Field;
  UINT32  Value;
} NBIO_ERR_VALID_BIT;

typedef union {
  struct {
    UINT8       Nbio:1;                ///< [0] NBIO
    UINT8       NbifMm:1;              ///< [1] NBIFMM
    UINT8       SyshubMm:1;            ///< [2] SYSHUBMM
    UINT8       Dxio:1;                ///< [3] DXIO
    UINT8       :4;                    ///< [7:4] Reserved
  } Field;
  UINT8  Value;
} NBIO_ERR_SRC;

typedef union {
  struct {
    UINT8       ParityErrCorr:1;       ///< [0] ParityErrCorr (NBIO) or PHY Controller ECC
    UINT8       ParityErrNonFatal:1;   ///< [1] ParityErrNonFatal (NBIO)
    UINT8       ParityErrFatal:1;      ///< [2] ParityErrFatal (NBIO or NBIF)
    UINT8       ParityErrSerr:1;       ///< [3] ParityErrSerr (NBIO)
    UINT8       PoisonError:1;         ///< [4] Poisoned Error (NBIF)
    UINT8       WatchdogTimeOut:1;     ///< [5] Watchdog timeout (NBIF)
    UINT8       :2;                    ///< [7:6] Reserved
  } Field;
  UINT8  Value;
} NBIO_ERR_TYPE;

typedef union {
  struct {
    UINT32       BusId:1;               ///< [0] Bus ID
    UINT32       ErrorType:1;           ///< [1] Error Type
    UINT32       ErrorSource:1;         ///< [2] Error Source
    UINT32       :29;                   ///< [31:3] Reserved
  } Field;
  UINT32  Value;
} SMN_ERROR_VALID_BIT;

typedef union {
  struct {
    UINT8      SmnParitySmnPspTimeoutSmuParityEcc:1;    ///< [0] SMN Parity
                                                        ///      SMN Timeouts:PSP
                                                        ///      SMU Parity and ECC
    UINT8      :1;                                      ///< [1] Reserved
    UINT8      PspParityEcc:1;                          ///< [2] Psp Parity and ECC
    UINT8      SmnTimeoutSmu:1;                         ///< [3] SMN Timeouts: SMU
    UINT8      SmnLinkPacketCrcWithRetry:1;             ///< [4] SMN Link Packet CRC with Retry
    UINT8      :3;                                      ///< [7:5] Reserved
  } Field;
  UINT8  Value;
} SMN_ERROR_SOURCE;

typedef union {
  struct {
    UINT32       BusId:1;               ///< [0] Bus ID
    UINT32       Port:1;                ///< [1] Port
    UINT32       ErrorSource:1;         ///< [2] Error Source
    UINT32       ErrorType:1;           ///< [3] Error Type
    UINT32       :28;                   ///< [31:4] Reserved
  } Field;
  UINT32  Value;
} SATA_ERROR_VALID_BIT;

typedef union {
  struct {
    UINT8      Sata:1;              ///< [0] SATA
    UINT8      :7;                  ///< [7:1] Reserved
  } Field;
  UINT8  Value;
} SATA_ERROR_SOURCE;

typedef union {
  struct {
    UINT32       ErrorType:1;           ///< [0] Error Type
    UINT32       ErrorSource:1;         ///< [1] Error Source
    UINT32       ErrorStatus:1;         ///< [2] Error Status
    UINT32       :29;                   ///< [31:3] Reserved
  } Field;
  UINT32  Value;
} ALINK_ERROR_VALID_BIT;

typedef union {
  struct {
    UINT16       DetectedParityError:1;     ///< [0] DetectedParityError (SMBus or LPC Bridge)
    UINT16       DataParityErrorDetected:1; ///< [1] DataParityErrorDetected (SMBus)
    UINT16       MasterDataParityError:1;   ///< [2] MasterDataParityError (LPC Bridge)
    UINT16       :13;                       ///< [15:3] Reserved
  } Field;
  UINT16  Value;
} ALINK_ERROR_STATUS;

typedef union {
  struct {
    UINT32       ErrorType:1;           ///< [0] Error Type
    UINT32       ErrorSource:1;         ///< [1] Error Source
    UINT32       ErrorStatus:1;         ///< [2] Error Status
    UINT32       :29;                   ///< [31:3] Reserved
  } Field;
  UINT32  Value;
} USB_ERROR_VALID_BIT;

typedef union {
  struct {
    UINT32       SEC_Ram0:1;        ///< [0] SEC_Ram0
    UINT32       DED_Ram0:1;        ///< [1] DED_Ram0
    UINT32       FED_Ram0:1;        ///< [2] FED_Ram0
    UINT32       SEC_Ram1:1;        ///< [3] SEC_Ram1
    UINT32       DED_Ram1:1;        ///< [4] DED_Ram1
    UINT32       FED_Ram1:1;        ///< [5] FED_Ram1
    UINT32       SEC_Ram2:1;        ///< [6] SEC_Ram2
    UINT32       DED_Ram2:1;        ///< [7] DED_Ram2
    UINT32       FED_Ram2:1;        ///< [8] FED_Ram2
    UINT32               :23;       ///< [31:9] Reserved
  } Field;
  UINT32 Value;
} USB_ERROR_STATUS;

typedef union {
  struct {
    UINT8      UsbParityAndEcc:1;   ///< [0] SATA
    UINT8      :7;                  ///< [7:1] Reserved
  } Field;
  UINT8  Value;
} USB_ERROR_TYPE;

#pragma pack (push, 1)

///
/// NBIO Error Record structure
///
typedef struct {
    NBIO_ERR_VALID_BIT      ValidationBits;
    UINT8                   BusId;
    NBIO_ERR_SRC            ErrorSource;
    NBIO_ERR_TYPE           ErrorType;
    UINT8                   GroupType;
    UINT16                  GroupId;
    UINT8                   NbifId;
    UINT8                   LeafId;
    UINT32                  ParityErrSts;
} AMD_NBIO_ERROR_RECORD;

///
/// SMU Error Record structure
///
typedef struct {
    SMN_ERROR_VALID_BIT     ValidationBits;
    UINT8                   BusId;
    UINT8                   Category;
    SMN_ERROR_SOURCE        ErrorSource;
    UINT8                   Reserved1;
} AMD_SMN_ERROR_RECORD;

///
/// SATA Error Record structure
///

///SATA Error Type definition
#define SATA_D2H_FIFO_PARITY_ERROR          (0)
#define SATA_H2D_FIFO_PARITY_ERROR          (1)
#define SATA_CONTEXT_MEMORY_PARITY_ERROR    (2)

typedef struct {
    SATA_ERROR_VALID_BIT    ValidationBits;
    UINT8                   BusId;
    UINT8                   Port;
    SATA_ERROR_SOURCE       ErrorSource;
    UINT8                   ErrorType;
} AMD_SATA_ERROR_RECORD;

///
/// FCH A-Link Error Record structure
///

///A-Link Error Type definition
#define FCH_ALINK_PARITY_ERROR              (0)

///A-Link Error Source definition
#define ALINK_SMBUS_PARITY_ERROR            (0)
#define ALINK_LPCBRIDGE_PARITY_ERROR        (1)

typedef struct {
    ALINK_ERROR_VALID_BIT   ValidationBits;
    UINT8                   ErrorType;
    UINT8                   ErrorSource;
    ALINK_ERROR_STATUS      ErrorStatus;
} AMD_ALINK_ERROR_RECORD;

///
/// USB Error Record structure
///

///A-Link Error Source definition
#define USB_USBCONTAINER0_ERROR             (0)
#define USB_USBCONTAINER1_ERROR             (1)

typedef struct {
    USB_ERROR_VALID_BIT     ValidationBits;
    USB_ERROR_TYPE          ErrorType;
    UINT8                   ErrorSource;
    USB_ERROR_STATUS        ErrorStatus;
} AMD_USB_ERROR_RECORD;

#pragma pack (pop)

#endif  // _AMD_RAS_H_

