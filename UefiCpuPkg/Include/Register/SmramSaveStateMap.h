/** @file
SMRAM Save State Map Definitions.

SMRAM Save State Map definitions based on contents of the
Intel(R) 64 and IA-32 Architectures Software Developer's Manual
  Volume 3C, Section 34.4 SMRAM
  Volume 3C, Section 34.5 SMI Handler Execution Environment
  Volume 3C, Section 34.7 Managing Synchronous and Asynchronous SMIs

Copyright (c) 2015, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __SMRAM_SAVE_STATE_MAP_H__
#define __SMRAM_SAVE_STATE_MAP_H__

///
/// Default SMBASE address
///
#define SMM_DEFAULT_SMBASE           0x30000

///
/// Offset of SMM handler from SMBASE
///
#define SMM_HANDLER_OFFSET           0x8000

///
/// Offset of SMRAM Save State Map from SMBASE
///
// (AMI AMD Porting)>> AMD's save area starts 0xFE00
//#define SMRAM_SAVE_STATE_MAP_OFFSET  0xfc00
#define SMRAM_SAVE_STATE_MAP_OFFSET  0xfe00
// (AMI AMD Porting)<<
#pragma pack (1)

// (AMI AMD Porting)>> The AMD SMRAM save state MAP is different from Intel SMRAM state map
///
/// 32-bit SMRAM Save State Map
///
typedef struct {
    UINT16  _ES;              // 0xfe00 EFI_SMM_SAVE_STATE_REGISTER_ES
    UINT8   Reserved[14];     //        Reserved(6) + Descriptor in memory format(8)
    UINT16  _CS;              // 0xfe10 EFI_SMM_SAVE_STATE_REGISTER_CS
    UINT8   Reserved1[14];    //        Reserved(6) + Descriptor in memory format(8)
    UINT16  _SS;              // 0xfe20 EFI_SMM_SAVE_STATE_REGISTER_SS
    UINT8   Reserved2[14];    //        Reserved(6) + Descriptor in memory format(8)
    UINT16  _DS;              // 0xfe30 EFI_SMM_SAVE_STATE_REGISTER_DS
    UINT8   Reserved3[14];    //        Reserved(6) + Descriptor in memory format(8)
    UINT16  _FS;              // 0xfe40 EFI_SMM_SAVE_STATE_REGISTER_FS
    UINT8   Reserved4[14];    //        Reserved(2) + FS Base(4) + Descriptor in memory format(8)
    UINT16  _GS;              // 0xfe50 EFI_SMM_SAVE_STATE_REGISTER_GS
    UINT8   Reserved5[14];    //        Reserved(2) + GS Base(4) + Descriptor in memory format(8)
    UINT8   Reserved6[16];    // 0xfe60 Reserved(4) + GDTR limit(2) + Reserved(2) + Descriptor in memory format(8)
    UINT16  _LDTR;            // 0xfe70 EFI_SMM_SAVE_STATE_REGISTER_LDTR_SEL
    UINT16  _LDTR_ATTRIBUTE;  // 0xfe72 
    UINT32  _LDTR_LIMIT;      // 0xfe74 
    UINT64  _LDTR_BASE;       // 0xfe78 
    UINT8   Reserved7[4];     // 0xfe80 IDTR Reserved
    UINT16  _IDTR_LIMIT;      // 0xfe84 IDTR Limit
    UINT8   Reserved8[2];     // 0xfe86 IDTR Reserved
    UINT64  _IDTR_BASE;       // 0xfe88 IDTR Base
    UINT16  _TR;              // 0xfe90 EFI_SMM_SAVE_STATE_REGISTER_TR_SEL
    UINT16  _TR_ATTRIBUTE;    // 0xfe92 TR Attribute
    UINT32  _TR_LIMIT;        // 0xfe94 TR LIMIT
    UINT64  _TR_BASE;         // 0xfe98 TR BASE
    UINT64  IoRestartRip;     // 0xfea0 IO_RESTART_RIP
    UINT64  IoRestartRcx;     // 0xfea8 IO_RESTART_RCX
    UINT64  IoRestartRsi;     // 0xfeb0 IO_RESTART_RSI
    UINT64  IoRestartRdi;     // 0xfeb8 IO_RESTART_RDI
    UINT32  IoTrapOffset;     // 0xfec0 Core::X86::Smm::TrapOffset [SMM IO Trap Offset]
    UINT32  LocalSmiStatus;   // 0xfec4 Local Smi Status
    UINT8   IORestart;        // 0xfec8 Io Restart
    UINT8   AutoHALTRestart;  // 0xfec9 Auto Halt Restart
    UINT8   NmiMask;          // 0xfeca Nmi Mask
    UINT8   Reserved9[5];     // 0xfecb
    UINT64  IA32_EFER;        // 0xfed0 EFER
    UINT64  SvmState;         // 0xfed8 Svm State
    UINT64  GVmcbPA;          // 0xfee0 Guest VMCB physical address
    UINT64  SvmVIC;           // 0xfee8 SVM Virtual Interrupt Control
    UINT8   Reserved10[12];   // 0xfef0
    UINT32  SMMRevId;         // 0xfefc Smm Rev ID
    UINT32  SMBASE;           // 0xff00 Smm Base address
    UINT8   Reserved11[28];   // 0xff04 
    UINT64  GPAT;             // 0xff20 Guest PAT
    UINT64  HEFER;            // 0xff28 Host EFER
    UINT64  HCR4;             // 0xff30 Host CR4
    UINT64  NCR3;             // 0xff38 Nested CR3
    UINT64  HCR0;             // 0xff40 Host CR0
    UINT64  _CR4;             // 0xff48 CR4 EFI_SMM_SAVE_STATE_REGISTER_CR4
    UINT64  _CR3;             // 0xff50 CR3 EFI_SMM_SAVE_STATE_REGISTER_CR3
    UINT64  _CR0;             // 0xff58 CR0 EFI_SMM_SAVE_STATE_REGISTER_CR0
    UINT64  _DR7;             // 0xff60 DR7 EFI_SMM_SAVE_STATE_REGISTER_DR7
    UINT64  _DR6;             // 0xff68 DR6 EFI_SMM_SAVE_STATE_REGISTER_DR6
    UINT64  _EFLAGS;          // 0xff70 EFLAGS EFI_SMM_SAVE_STATE_REGISTER_RFLAGS
    UINT64  _EIP;             // 0xff78 EIP EFI_SMM_SAVE_STATE_REGISTER_RIP
    UINT64  _R15;             // 0xff80 E15 EFI_SMM_SAVE_STATE_REGISTER_R15
    UINT64  _R14;             // 0xff88 E14 EFI_SMM_SAVE_STATE_REGISTER_R14
    UINT64  _R13;             // 0xff90 E13 EFI_SMM_SAVE_STATE_REGISTER_R13
    UINT64  _R12;             // 0xff98 E12 EFI_SMM_SAVE_STATE_REGISTER_R12
    UINT64  _R11;             // 0xffa0 E11 EFI_SMM_SAVE_STATE_REGISTER_R11
    UINT64  _R10;             // 0xffa8 E10 EFI_SMM_SAVE_STATE_REGISTER_R10
    UINT64  _R9;              // 0xffb0 E9  EFI_SMM_SAVE_STATE_REGISTER_R9
    UINT64  _R8;              // 0xffb8 E8  EFI_SMM_SAVE_STATE_REGISTER_R8
    UINT64  _EDI;             // 0xffc0 EDI EFI_SMM_SAVE_STATE_REGISTER_RDI
    UINT64  _ESI;             // 0xffc8 ESI EFI_SMM_SAVE_STATE_REGISTER_RSI
    UINT64  _EBP;             // 0xffd0 EBP EFI_SMM_SAVE_STATE_REGISTER_RBP
    UINT64  _ESP;             // 0xffd8 ESP EFI_SMM_SAVE_STATE_REGISTER_RSP
    UINT64  _EBX;             // 0xffe0 EBX EFI_SMM_SAVE_STATE_REGISTER_RBX
    UINT64  _EDX;             // 0xffe8 EDX EFI_SMM_SAVE_STATE_REGISTER_RDX
    UINT64  _ECX;             // 0xfff0 ECX EFI_SMM_SAVE_STATE_REGISTER_RCX
    UINT64  _EAX;             // 0xfff8 EAX EFI_SMM_SAVE_STATE_REGISTER_RAX
} SMRAM_SAVE_STATE_MAP32;

typedef struct {
    UINT16  _ES;              // 0xfe00 EFI_SMM_SAVE_STATE_REGISTER_ES
    UINT8   Reserved[14];     //        Reserved(6) + Descriptor in memory format(8)
    UINT16  _CS;              // 0xfe10 EFI_SMM_SAVE_STATE_REGISTER_CS
    UINT8   Reserved1[14];    //        Reserved(6) + Descriptor in memory format(8)
    UINT16  _SS;              // 0xfe20 EFI_SMM_SAVE_STATE_REGISTER_SS
    UINT8   Reserved2[14];    //        Reserved(6) + Descriptor in memory format(8)
    UINT16  _DS;              // 0xfe30 EFI_SMM_SAVE_STATE_REGISTER_DS
    UINT8   Reserved3[14];    //        Reserved(6) + Descriptor in memory format(8)
    UINT16  _FS;              // 0xfe40 EFI_SMM_SAVE_STATE_REGISTER_FS
    UINT8   Reserved4[14];    //        Reserved(2) + FS Base(4) + Descriptor in memory format(8)
    UINT16  _GS;              // 0xfe50 EFI_SMM_SAVE_STATE_REGISTER_GS
    UINT8   Reserved5[14];    //        Reserved(2) + GS Base(4) + Descriptor in memory format(8)
    UINT8   Reserved6[16];    // 0xfe60 Reserved(4) + GDTR limit(2) + Reserved(2) + Descriptor in memory format(8)
    UINT16  _LDTR;            // 0xfe70 EFI_SMM_SAVE_STATE_REGISTER_LDTR_SEL
    UINT16  _LDTR_ATTRIBUTE;  // 0xfe72 
    UINT32  _LDTR_LIMIT;      // 0xfe74 
    UINT64  _LDTR_BASE;       // 0xfe78 
    UINT8   Reserved7[4];     // 0xfe80 IDTR Reserved
    UINT16  _IDTR_LIMIT;      // 0xfe84 IDTR Limit
    UINT8   Reserved8[2];     // 0xfe86 IDTR Reserved
    UINT64  _IDTR_BASE;       // 0xfe88 IDTR Base
    UINT16  _TR;              // 0xfe90 EFI_SMM_SAVE_STATE_REGISTER_TR_SEL
    UINT16  _TR_ATTRIBUTE;    // 0xfe92 TR Attribute
    UINT32  _TR_LIMIT;        // 0xfe94 TR LIMIT
    UINT64  _TR_BASE;         // 0xfe98 TR BASE
    UINT64  IoRestartRip;     // 0xfea0 IO_RESTART_RIP
    UINT64  IoRestartRcx;     // 0xfea8 IO_RESTART_RCX
    UINT64  IoRestartRsi;     // 0xfeb0 IO_RESTART_RSI
    UINT64  IoRestartRdi;     // 0xfeb8 IO_RESTART_RDI
    UINT32  IoTrapOffset;     // 0xfec0 Core::X86::Smm::TrapOffset [SMM IO Trap Offset]
    UINT32  LocalSmiStatus;   // 0xfec4 Local Smi Status
    UINT8   IORestart;        // 0xfec8 Io Restart
    UINT8   AutoHALTRestart;  // 0xfec9 Auto Halt Restart
    UINT8   NmiMask;          // 0xfeca Nmi Mask
    UINT8   Reserved9[5];     // 0xfecb
    UINT64  IA32_EFER;        // 0xfed0 EFER
    UINT64  SvmState;         // 0xfed8 Svm State
    UINT64  GVmcbPA;          // 0xfee0 Guest VMCB physical address
    UINT64  SvmVIC;           // 0xfee8 SVM Virtual Interrupt Control
    UINT8   Reserved10[12];   // 0xfef0
    UINT32  SMMRevId;         // 0xfefc Smm Rev ID
    UINT32  SMBASE;           // 0xff00 Smm Base address
    UINT8   Reserved11[28];   // 0xff04 
    UINT64  GPAT;             // 0xff20 Guest PAT
    UINT64  HEFER;            // 0xff28 Host EFER
    UINT64  HCR4;             // 0xff30 Host CR4
    UINT64  NCR3;             // 0xff38 Nested CR3
    UINT64  HCR0;             // 0xff40 Host CR0
    UINT64  _CR4;             // 0xff48 CR4 EFI_SMM_SAVE_STATE_REGISTER_CR4
    UINT64  _CR3;             // 0xff50 CR3 EFI_SMM_SAVE_STATE_REGISTER_CR3
    UINT64  _CR0;             // 0xff58 CR0 EFI_SMM_SAVE_STATE_REGISTER_CR0
    UINT64  _DR7;             // 0xff60 DR7 EFI_SMM_SAVE_STATE_REGISTER_DR7
    UINT64  _DR6;             // 0xff68 DR6 EFI_SMM_SAVE_STATE_REGISTER_DR6
    UINT64  _RFLAGS;          // 0xff70 RFLAGS EFI_SMM_SAVE_STATE_REGISTER_RFLAGS
    UINT64  _RIP;             // 0xff78 RIP EFI_SMM_SAVE_STATE_REGISTER_RIP
    UINT64  _R15;             // 0xff80 R15 EFI_SMM_SAVE_STATE_REGISTER_R15
    UINT64  _R14;             // 0xff88 R14 EFI_SMM_SAVE_STATE_REGISTER_R14
    UINT64  _R13;             // 0xff90 R13 EFI_SMM_SAVE_STATE_REGISTER_R13
    UINT64  _R12;             // 0xff98 R12 EFI_SMM_SAVE_STATE_REGISTER_R12
    UINT64  _R11;             // 0xffa0 R11 EFI_SMM_SAVE_STATE_REGISTER_R11
    UINT64  _R10;             // 0xffa8 R10 EFI_SMM_SAVE_STATE_REGISTER_R10
    UINT64  _R9;              // 0xffb0 R9  EFI_SMM_SAVE_STATE_REGISTER_R9
    UINT64  _R8;              // 0xffb8 R8  EFI_SMM_SAVE_STATE_REGISTER_R8
    UINT64  _RDI;             // 0xffc0 RDI EFI_SMM_SAVE_STATE_REGISTER_RDI
    UINT64  _RSI;             // 0xffc8 RSI EFI_SMM_SAVE_STATE_REGISTER_RSI
    UINT64  _RBP;             // 0xffd0 RBP EFI_SMM_SAVE_STATE_REGISTER_RBP
    UINT64  _RSP;             // 0xffd8 RSP EFI_SMM_SAVE_STATE_REGISTER_RSP
    UINT64  _RBX;             // 0xffe0 RBX EFI_SMM_SAVE_STATE_REGISTER_RBX
    UINT64  _RDX;             // 0xffe8 RDX EFI_SMM_SAVE_STATE_REGISTER_RDX
    UINT64  _RCX;             // 0xfff0 RCX EFI_SMM_SAVE_STATE_REGISTER_RCX
    UINT64  _RAX;             // 0xfff8 RAX EFI_SMM_SAVE_STATE_REGISTER_RAX
}SMRAM_SAVE_STATE_MAP64;
/*
///
/// 32-bit SMRAM Save State Map
///
typedef struct {
  UINT8   Reserved[0x200];  // 7c00h
                            // Padded an extra 0x200 bytes so 32-bit and 64-bit
                            // SMRAM Save State Maps are the same size
  UINT8   Reserved1[0xf8];  // 7e00h
  UINT32  SMBASE;           // 7ef8h
  UINT32  SMMRevId;         // 7efch
  UINT16  IORestart;        // 7f00h
  UINT16  AutoHALTRestart;  // 7f02h
  UINT8   Reserved2[0x9C];  // 7f08h
  UINT32  IOMemAddr;        // 7fa0h
  UINT32  IOMisc;           // 7fa4h
  UINT32  _ES;              // 7fa8h
  UINT32  _CS;              // 7fach
  UINT32  _SS;              // 7fb0h
  UINT32  _DS;              // 7fb4h
  UINT32  _FS;              // 7fb8h
  UINT32  _GS;              // 7fbch
  UINT32  Reserved3;        // 7fc0h
  UINT32  _TR;              // 7fc4h
  UINT32  _DR7;             // 7fc8h
  UINT32  _DR6;             // 7fcch
  UINT32  _EAX;             // 7fd0h
  UINT32  _ECX;             // 7fd4h
  UINT32  _EDX;             // 7fd8h
  UINT32  _EBX;             // 7fdch
  UINT32  _ESP;             // 7fe0h
  UINT32  _EBP;             // 7fe4h
  UINT32  _ESI;             // 7fe8h
  UINT32  _EDI;             // 7fech
  UINT32  _EIP;             // 7ff0h
  UINT32  _EFLAGS;          // 7ff4h
  UINT32  _CR3;             // 7ff8h
  UINT32  _CR0;             // 7ffch
} SMRAM_SAVE_STATE_MAP32;

///
/// 64-bit SMRAM Save State Map
///
typedef struct {
  UINT8   Reserved1[0x1d0];  // 7c00h
  UINT32  GdtBaseHiDword;    // 7dd0h
  UINT32  LdtBaseHiDword;    // 7dd4h
  UINT32  IdtBaseHiDword;    // 7dd8h
  UINT8   Reserved2[0xc];    // 7ddch
  UINT64  IO_EIP;            // 7de8h
  UINT8   Reserved3[0x50];   // 7df0h
  UINT32  _CR4;              // 7e40h
  UINT8   Reserved4[0x48];   // 7e44h
  UINT32  GdtBaseLoDword;    // 7e8ch
  UINT32  Reserved5;         // 7e90h
  UINT32  IdtBaseLoDword;    // 7e94h
  UINT32  Reserved6;         // 7e98h
  UINT32  LdtBaseLoDword;    // 7e9ch
  UINT8   Reserved7[0x38];   // 7ea0h
  UINT64  EptVmxControl;     // 7ed8h
  UINT32  EnEptVmxControl;   // 7ee0h
  UINT8   Reserved8[0x14];   // 7ee4h
  UINT32  SMBASE;            // 7ef8h
  UINT32  SMMRevId;          // 7efch
  UINT16  IORestart;         // 7f00h
  UINT16  AutoHALTRestart;   // 7f02h
  UINT8   Reserved9[0x18];   // 7f04h
  UINT64  _R15;              // 7f1ch
  UINT64  _R14;
  UINT64  _R13;
  UINT64  _R12;
  UINT64  _R11;
  UINT64  _R10;
  UINT64  _R9;
  UINT64  _R8;
  UINT64  _RAX;              // 7f5ch
  UINT64  _RCX;
  UINT64  _RDX;
  UINT64  _RBX;
  UINT64  _RSP;
  UINT64  _RBP;
  UINT64  _RSI;
  UINT64  _RDI;
  UINT64  IOMemAddr;         // 7f9ch
  UINT32  IOMisc;            // 7fa4h
  UINT32  _ES;               // 7fa8h
  UINT32  _CS;
  UINT32  _SS;
  UINT32  _DS;
  UINT32  _FS;
  UINT32  _GS;
  UINT32  _LDTR;             // 7fc0h
  UINT32  _TR;
  UINT64  _DR7;              // 7fc8h
  UINT64  _DR6;
  UINT64  _RIP;              // 7fd8h
  UINT64  IA32_EFER;         // 7fe0h
  UINT64  _RFLAGS;           // 7fe8h
  UINT64  _CR3;              // 7ff0h
  UINT64  _CR0;              // 7ff8h
} SMRAM_SAVE_STATE_MAP64;
*/
// (AMI AMD Porting)<<

///
/// Union of 32-bit and 64-bit SMRAM Save State Maps
///
typedef union  {
  SMRAM_SAVE_STATE_MAP32  x86;
  SMRAM_SAVE_STATE_MAP64  x64;
} SMRAM_SAVE_STATE_MAP;

///
/// Minimum SMM Revision ID that supports IOMisc field in SMRAM Save State Map
///
#define SMRAM_SAVE_STATE_MIN_REV_ID_IOMISC  0x30004

///
/// SMRAM Save State Map IOMisc I/O Length Values
///
#define  SMM_IO_LENGTH_BYTE             0x01
#define  SMM_IO_LENGTH_WORD             0x02
#define  SMM_IO_LENGTH_DWORD            0x04

///
/// SMRAM Save State Map IOMisc I/O Instruction Type Values
///
#define  SMM_IO_TYPE_IN_IMMEDIATE       0x9
#define  SMM_IO_TYPE_IN_DX              0x1
#define  SMM_IO_TYPE_OUT_IMMEDIATE      0x8
#define  SMM_IO_TYPE_OUT_DX             0x0
#define  SMM_IO_TYPE_INS                0x3
#define  SMM_IO_TYPE_OUTS               0x2
#define  SMM_IO_TYPE_REP_INS            0x7
#define  SMM_IO_TYPE_REP_OUTS           0x6

///
/// SMRAM Save State Map IOMisc structure
///
typedef union {
  struct {
    UINT32  SmiFlag:1;
    UINT32  Length:3;
    UINT32  Type:4;
    UINT32  Reserved1:8;
    UINT32  Port:16;
  } Bits;
  UINT32  Uint32;
} SMRAM_SAVE_STATE_IOMISC;

#pragma pack ()

#endif
