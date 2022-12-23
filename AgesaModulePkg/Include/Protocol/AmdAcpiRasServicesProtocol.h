/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD RAS Services Protocol prototype definition
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Library
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-25 21:00:43 -0600 (Wed, 25 Feb 2015) $
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
#ifndef _AMD_ACPI_RAS_SERVICES_PROTOCOL_H_
#define _AMD_ACPI_RAS_SERVICES_PROTOCOL_H_
#pragma pack (push, 1)

/*----------------------------------------------------------------------------------------
 *                    T Y P E D E F S     A N D     S T R U C T U R E S
 *                            System Resource Affinity Table
 *----------------------------------------------------------------------------------------
 */
/// Initial data of AMD_MC_BANK
typedef struct _AMD_MC_BANK_INIT_DATA {
  UINT64 CtrlInitData;            ///< Initial data of CtrlInitDataLSD
  UINT32 CtrlRegMSRAddr;          ///< Initial data of CtrlRegMSRAddr
  UINT32 StatRegMSRAddr;          ///< Initial data of StatRegMSRAddr
  UINT32 AddrRegMSRAddr;          ///< Initial data of AddrRegMSRAddr
  UINT32 MiscRegMSRAddr;          ///< Initial data of MiscRegMSRAddr
} AMD_MC_BANK_INIT_DATA;

/// Initial data of Machine Check
typedef struct _AMD_MC_INIT_DATA {
  UINT64 GlobCapInitData;         ///< Check global capability register
  UINT64 GlobCtrlInitData;        ///< Check global control register
  UINT8  ClrStatusOnInit;         ///< Indicates if the status information in this machine check
                                  ///< bank is to be cleared during system initialization
  UINT8  StatusDataFormat;        ///< Indicates the format of the data in the status register
  UINT8  ConfWriteEn;             ///< This field indicates whether configuration parameters may be
                                  ///< modified by the OS. If the bit for the associated parameter is
                                  ///< set, the parameter is writable by the OS.
  UINT8  McBankNum;               ///< Number of MCA Bank
  AMD_MC_BANK_INIT_DATA *McBankInitData;  ///< Pointer to Initial data of Mc Bank
} AMD_MC_INIT_DATA;

/*----------------------------------------------------------------------------------------
 *                 D E F I N I T I O N S     A N D     M A C R O S
 *----------------------------------------------------------------------------------------
 */
///
/// Forward declaration for the AMD_FABRIC_ACPI_SRAT_SERVICES_PROTOCOL.
///
typedef struct _AMD_CCX_ACPI_RAS_SERVICES_PROTOCOL AMD_CCX_ACPI_RAS_SERVICES_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *AMD_RAS_SERVICES_GET_MC_BANK_INFO) (
  IN       AMD_CCX_ACPI_RAS_SERVICES_PROTOCOL         *This,
     OUT   AMD_MC_INIT_DATA                          **McBankInfo
  );

///
/// When installed, the SRAT Services Protocol produces a collection of
/// services that return various information to generate SRAT
///
struct _AMD_CCX_ACPI_RAS_SERVICES_PROTOCOL {
  UINTN                                Revision;       ///< Revision Number
  AMD_RAS_SERVICES_GET_MC_BANK_INFO    GetMcBankInfo;  ///< Get Machine Check bank infomation
};

extern EFI_GUID gAmdCcxAcpiRasServicesProtocolGuid;

#pragma pack (pop)
#endif // _AMD_ACPI_RAS_SERVICES_PROTOCOL_H_
