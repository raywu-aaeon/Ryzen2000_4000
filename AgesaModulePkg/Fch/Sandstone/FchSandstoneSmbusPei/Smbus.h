/* $NoKeywords:$ */
/**
 * @file
 *
 * FCH PEI driver.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  FCH PEIM
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 10:28:05 -0800 (Tue, 09 Dec 2014) $
 *
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
 */

#ifndef _FCH_SMBUS_H_
#define _FCH_SMBUS_H_

#include <Ppi/Smbus2.h>
#include "FchPlatform.h"
//
// EQUate Definitions
//
#define SMB_IOREG00         0x00        // SMBusStatus
#define SMB_IOREG01         0x01        // SMBusSlaveStatus
#define SMB_IOREG02         0x02        // SMBusControl
#define SMB_IOREG03         0x03        // SMBusHostCmd
#define SMB_IOREG04         0x04        // SMBusAddress
#define SMB_IOREG05         0x05        // SMBusData0
#define SMB_IOREG06         0x06        // SMBusData1
#define SMB_IOREG07         0x07        // SMBusBlockData
#define SMB_IOREG08         0x08        // SMBusSlaveControl

#define SMB_CMD_QUICK       0x00 << 2   // Quick Read or Write
#define SMB_CMD_BYTE        0x01 << 2   // Byte Read or Write
#define SMB_CMD_BYTE_DATA   0x02 << 2   // Byte Data Read or Write
#define SMB_CMD_WORD_DATA   0x03 << 2   // Word Data Read or Write
#define SMB_CMD_BLOCK       0x05 << 2   // Block Read or Write
#define SMB_ALL_HOST_STATUS 0x1f        // HostBusy+SMBInterrupt+DeviceErr+BusCollision+Failed

#define TRY_TIMES           0x03
#define SMBUS_READ_ENABLE   BIT0

typedef struct  _AMD_SMBUS_PPI_PRIVATE AMD_SMBUS_PPI_PRIVATE;

//
typedef
UINT8
(EFIAPI *SMBUS_IO_READ) (
  IN       AMD_SMBUS_PPI_PRIVATE  *Private,
  IN       UINTN                  Address
  );


typedef
VOID
(EFIAPI *SMBUS_IO_WRITE) (
  IN       AMD_SMBUS_PPI_PRIVATE  *Private,
  IN       UINTN                  Address,
  IN       UINT8                  Data
  );


typedef
EFI_STATUS
(EFIAPI *SMBUS_STALL) (
  IN       EFI_PEI_SERVICES   **PeiServices,
  IN       EFI_PEI_STALL_PPI      *This,
  IN       UINTN              Microseconds
  );


//
// Module data structure
//
/// Private SMBUS PPI Data Structures
typedef struct _AMD_SMBUS_PPI_PRIVATE {
  EFI_PEI_SMBUS2_PPI           SmbusPpi;           ///< SMBUS PPI
  EFI_PEI_SERVICES        **PeiServices;      ///< Pointer to PeiServices
  UINTN                   BaseAddress;        ///< SMBUS Base Address
  UINT8                   RegisterIndex;      ///< SMBUS Base Register Index
  SMBUS_IO_READ           IoRead8;            ///< Local Function Pointer
  SMBUS_IO_WRITE          IoWrite8;           ///< Local Function Pointer
} AMD_SMBUS_PPI_PRIVATE;


/// Private SMBUS Data Block Structure
typedef struct _AMD_PEI_FCH_SMBUS_PRIVATE {
  AMD_SMBUS_PPI_PRIVATE   SmbusPpi0;          ///< SMBUS0 Data Block
  AMD_SMBUS_PPI_PRIVATE   SmbusPpi1;          ///< SMBUS1 Data Block
} AMD_PEI_FCH_SMBUS_PRIVATE;

#endif // _FCH_SMBUS_H_

