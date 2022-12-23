/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD CPU AP related utility functions and structures
 *
 * Contains code that provides mechanism to invoke and control APIC communication.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  CPU
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

#ifndef _CPU_AP_COMM_H_
#define _CPU_AP_COMM_H_

#include "Library/ApCommunicationLib.h"
#pragma pack (push, 1)

/*---------------------------------------------------------------------------------------
 *          M I X E D   (Definitions And Macros / Typedefs, Structures, Enums)
 *---------------------------------------------------------------------------------------
 */


/*---------------------------------------------------------------------------------------
 *                 D E F I N I T I O N S     A N D     M A C R O S
 *---------------------------------------------------------------------------------------
 */
#define APIC_CTRL_DWORD 0xF
#define APIC_CTRL_REG (APIC_CTRL_DWORD << 4)
#define APIC_CTRL_MASK 0xFF
#define APIC_CTRL_SHIFT 0

#define APIC_DATA_DWORD 0x38
#define APIC_DATA_REG (APIC_DATA_DWORD << 4)

#define APIC_REMOTE_READ_REG 0xC0
#define APIC_CMD_LO_REG 0x300
#define APIC_CMD_HI_REG 0x310

// APIC_CMD_LO_REG bits
#define CMD_REG_DELIVERY_STATUS 0x1000
#define CMD_REG_TO_READ 0x300
#define CMD_REG_REMOTE_RD_STS_MSK 0x30000ul
#define CMD_REG_REMOTE_DELIVERY_PENDING 0x10000ul
#define CMD_REG_REMOTE_DELIVERY_DONE 0x20000ul
#define CMD_REG_TO_NMI 0x400

// Macro used to determine the number of dwords to transmit to the AP as input
#define SIZE_IN_DWORDS(sInput) ((UINT32) (((sizeof (sInput)) + 3) >> 2))

// IDT table
#define IDT_DESC_PRESENT     0x80

#define IDT_DESC_TYPE_LDT    0x02
#define IDT_DESC_TYPE_CALL16 0x04
#define IDT_DESC_TYPE_TASK   0x05
#define IDT_DESC_TYPE_INT16  0x06
#define IDT_DESC_TYPE_TRAP16 0x07
#define IDT_DESC_TYPE_CALL32 0x0C
#define IDT_DESC_TYPE_INT32  0x0E
#define IDT_DESC_TYPE_TRAP32 0x0F

// ApFlags bits
#define AP_TASK_HAS_INPUT    0x00000001ul
#define AP_TASK_HAS_OUTPUT   0x00000002ul
#define AP_RETURN_PARAMS     0x00000004ul
#define AP_END_AT_HLT        0x00000008ul

// CPUID related registers
#define LOCAL_APIC_ID               24
#define MSR_EXTENDED_FEATURE_EN     0xC0000080ul

/*---------------------------------------------------------------------------------------
 *               T Y P E D E F S,   S T R U C T U R E S,    E N U M S
 *---------------------------------------------------------------------------------------
 */

/// Interrupt Descriptor Table entry
typedef struct {
  UINT16 OffsetLo;     ///< Lower 16 bits of the interrupt handler routine's offset
  UINT16 Selector;     ///< Interrupt handler routine's selector
  UINT8  Rsvd;         ///< Reserved
  UINT8  Flags;        ///< Interrupt flags
  UINT16 OffsetHi;     ///< Upper 16 bits of the interrupt handler routine's offset
  UINT32 Offset64;     ///< High order 32 bits of the handler's offset needed when in 64 bit mode
  UINT32 Rsvd64;       ///< Reserved
} IDT_DESCRIPTOR;

/// Structure needed to load the IDTR using the lidt instruction
typedef struct {
  UINT16 Limit;        ///< Interrupt Descriptor Table size
  UINT64 Base;         ///< Interrupt Descriptor Table base address
} IDT_BASE_LIMIT;

/*---------------------------------------------------------------------------------------
 *                        F U N C T I O N    P R O T O T Y P E
 *---------------------------------------------------------------------------------------
 */
//                   These are   P U B L I C   functions, used by AGESA
VOID
NmiHandler (
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

UINT8
ApUtilCalculateUniqueId (
  IN      UINT8 Socket,
  IN      UINT8 Core,
  IN      AMD_CONFIG_PARAMS *StdHeader
  );

UINT32
ApUtilRemoteRead (
  IN       UINT32            TargetApicId,
  IN       UINT8             RegAddr,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

VOID
ApUtilLocalWrite (
  IN       UINT32 RegAddr,
  IN       UINT32 Value,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

UINT32
ApUtilLocalRead (
  IN       UINT32  RegAddr,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

VOID
ApUtilTransmitBuffer (
  IN     UINT8   Socket,
  IN     UINT8   Core,
  IN     AP_DATA_TRANSFER *BufferInfo,
  IN     AMD_CONFIG_PARAMS *StdHeader
  );

AGESA_STATUS
ApUtilReceiveBuffer (
  IN       UINT8   Socket,
  IN       UINT8   Core,
  IN OUT   AP_DATA_TRANSFER  *BufferInfo,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

VOID
GetLocalApicIdForCore (
  IN       UINT8             TargetSocket,
  IN       UINT8             TargetCore,
     OUT   UINT32            *LocalApicId,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

VOID
ApUtilSetupIdtForHlt (
  IN       IDT_DESCRIPTOR *NmiIdtDescPtr,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

VOID
GetCsSelector (
  IN       UINT16 *Selector,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

VOID
SetIdtr (
  IN       IDT_BASE_LIMIT *IdtInfo,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

VOID
ApUtilFireDirectedNmi (
  IN      UINT32 TargetApicId,
  IN      AMD_CONFIG_PARAMS *StdHeader
  );

VOID
ApUtilTransmitPointer (
  IN       UINT8   Socket,
  IN       UINT8   Core,
  IN       VOID  **Pointer,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

VOID
ApUtilReceivePointer (
  IN       UINT8   Socket,
  IN       UINT8   Core,
     OUT   VOID  **ReturnPointer,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

#pragma pack (pop)
#endif  /* _CPU_AP_COMM_H_ */


