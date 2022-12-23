/* $NoKeywords:$ */
/**
 * @file
 *
 * AmdSmmCommunication.h
 *
 * Contains definition for AmdSmmCommunication
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
 **/

#ifndef _AMD_PSP_SMM_COMMUNICATION_H_
#define _AMD_PSP_SMM_COMMUNICATION_H_

extern EFI_GUID gPspSmmCommHandleGuid;

#define PSP_SMM_COMM_ID_GET_BLOCK_SIZE       0x1     ///< ID for S3 script
#define PSP_SMM_COMM_ID_READ_FLASH           0x2     ///< ID for Read Flash
#define PSP_SMM_COMM_ID_WRITE_FALSH          0x3     ///< ID for Write Flash
#define PSP_SMM_COMM_ID_ERASE_FALSH          0x4     ///< ID for Erase Flash
#define PSP_SMM_COMM_ID_CLOSE_INTERFACE      0x5     ///< ID for close SMM communication interface
#define PSP_SMM_COMM_ID_RPMC_INCMC           0x6     ///< ID for increment the Monotonic counter for SPI
#define PSP_SMM_COMM_ID_RPMC_REQMC           0x7     ///< ID for request the Monotonic counter for SPI


/// SMM communication common buffer
typedef struct _PSP_SMM_COMMUNICATION_CMN {
  UINT32                       id;         ///< ID of smm communication buffer
} PSP_SMM_COMMUNICATION_CMN;

#define PSP_SMM_COMM_GETBLKSIZE_BUFFER_SIZE (OFFSET_OF (EFI_SMM_COMMUNICATE_HEADER, Data)  + sizeof (PSP_SMM_COMM_GETBLKSIZE))
/// SMM communication common buffer
typedef struct _PSP_SMM_COMM_GETBLKSIZE {
  UINT32                       id;         ///< ID of smm communication buffer
  UINTN                        BlockSize;  ///< Block size of Flash Device
} PSP_SMM_COMM_GETBLKSIZE;

#define PSP_SMM_COMM_RWFLASH_BUFFER_SIZE (OFFSET_OF (EFI_SMM_COMMUNICATE_HEADER, Data)  + sizeof (PSP_SMM_COMM_RW_FLASH))

/// SMM communication common buffer
typedef struct _PSP_SMM_COMM_RW_FLASH {
  UINT32                       id;         ///< ID of smm communication buffer
  UINTN                        FlashAddress; ///< Flash device physical address
  UINTN                        NumBytes;     ///< Number of bytes to be access
  UINT8                        *Buffer;       ///< Buffer start
} PSP_SMM_COMM_RW_FLASH;

#define PSP_SMM_COMM_ERASEFLASH_BUFFER_SIZE (OFFSET_OF (EFI_SMM_COMMUNICATE_HEADER, Data)  + sizeof (PSP_SMM_COMM_ERASEFLASH))

/// SMM communication common buffer
typedef struct _PSP_SMM_COMM_ERASEFLASH {
  UINT32                       id;         ///< ID of smm communication buffer
  UINTN                        FlashAddress; ///< Flash device physical address
  UINTN                        NumBytes;  ///< Number of bytes to be access
} PSP_SMM_COMM_ERASEFLASH;

#define PSP_CMM_COMM_CLOSE_INTERFACE_BUFFER_SIZE (OFFSET_OF (EFI_SMM_COMMUNICATE_HEADER, Data)  + sizeof (PSP_SMM_COMMUNICATION_CMN))


#define PSP_SMM_COMM_RPMC_INCMC_BUFFER_SIZE (OFFSET_OF (EFI_SMM_COMMUNICATE_HEADER, Data)  + sizeof (PSP_SMM_COMM_RPMC_INCMC))
/// SMM communication common buffer
typedef struct _PSP_SMM_COMM_RPMC_INCMC {
  UINT32                       id;         ///< ID of smm communication buffer
  UINT8   CounterAddr;                      ///< Input, CounterAddr for the "Increment Monotonic Counter" SPI command
  UINT32  CounterData;                      ///< Input, CounterData for the "Increment Monotonic Counter" SPI command
  UINT8   *Signature;                    ///< Input, Signature for the "Increment Monotonic Counter" SPI command
} PSP_SMM_COMM_RPMC_INCMC;

#define PSP_SMM_COMM_RPMC_REQMC_BUFFER_SIZE (OFFSET_OF (EFI_SMM_COMMUNICATE_HEADER, Data)  + sizeof (PSP_SMM_COMM_RPMC_REQMC))
/// SMM communication common buffer
typedef struct _PSP_SMM_COMM_RPMC_REQMC {
  UINT32                       id;         ///< ID of smm communication buffer
  UINT8   CounterAddr;                      ///< Input, CounterAddr for the "Request Monotonic Counter" SPI command
  UINT8   *Tag;                          ///< Input, Tag for the "Request Monotonic Counter" SPI command
  UINT8   *Signature;                    ///< Input, Signature for the "Request Monotonic Counter" SPI command
  UINT32  *CounterData;                  ///< Output, CounterData for the "Request Monotonic Counter" SPI command
  UINT8   *OutputSignature;              ///< Output, Returned Signature for the "Request Monotonic Counter" SPI command
} PSP_SMM_COMM_RPMC_REQMC;

#endif // _AMD_PSP_SMM_COMMUNICATION_H_

