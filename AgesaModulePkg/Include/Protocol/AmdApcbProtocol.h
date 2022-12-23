/* $NoKeywords:$ */
/**
 * @file
 *
 * APCB service PPI prototype definition
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  APCB
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
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
#include "ApcbCommon.h"

#ifndef _AMD_APCB_SERVICE_PROTOCOL_H_
#define _AMD_APCB_SERVICE_PROTOCOL_H_

/*----------------------------------------------------------------------------------------
 *                    T Y P E D E F S     A N D     S T R U C T U R E S
 *                            COMPONENT Locality Distance Information Table
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                 D E F I N I T I O N S     A N D     M A C R O S
 *----------------------------------------------------------------------------------------
 */

#define       APCB_PROTOCOL_VERSION_2_0          2
#define       APCB_PROTOCOL_VERSION_3_0          3

///
/// Forward declaration for the AMD_APCB_SERVICE_PROTOCOL.
///
typedef struct _AMD_APCB_SERVICE_PROTOCOL AMD_APCB_SERVICE_PROTOCOL;

///Function used to set active APCB instance
typedef
VOID
(EFIAPI *FP_SET_ACTIVE_APCB_INSTANCE) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT8             Instance
  );

///Function used to flush APCB data
typedef
EFI_STATUS
(EFIAPI *FP_FLUSH_APCB_DATA) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This
  );

///Function used to update CBS APCB data
typedef
EFI_STATUS
(*FP_UPDATE_CBS_APCB_DATA) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT8             *ApcbTypeData,
  IN       UINT32            SizeInByte,
  IN       BOOLEAN           Internal
  );

///Function used to get the value of an APCB config token
typedef
EFI_STATUS
(EFIAPI *FP_GET_CONFIG_PARAM) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT16            TokenId,
  IN OUT   UINT32            *SizeInByte,
  IN OUT   UINT64            *Value
  );

///Function used to set the value of an APCB config token
typedef
EFI_STATUS
(EFIAPI *FP_SET_CONFIG_PARAM) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT16            TokenId,
  IN OUT   UINT32            *SizeInByte,
  IN OUT   UINT64            *Value
  );

///Function used to get the value of an APCB CBS token
typedef
EFI_STATUS
(EFIAPI *FP_GET_CBS_PARAM) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT16            TokenId,
  IN OUT   UINT32            *SizeInByte,
  IN OUT   UINT64            *Value
  );

///Function used to set the value of an APCB CBS token
typedef
EFI_STATUS
(EFIAPI *FP_SET_CBS_PARAM) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT16            TokenId,
  IN OUT   UINT32            *SizeInByte,
  IN OUT   UINT64            *Value
  );

///Function used to get the DRAM POST Package repair entries
typedef
EFI_STATUS
(EFIAPI *FP_GET_DRAM_POSTPKG_REPAIR_ENTRY) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN OUT   DRRP_REPAIR_ENTRY *Entry,
  IN OUT   UINT32            *NumOfEntries
  );

///Function used to clear the DRAM POST Package repair entries
typedef
EFI_STATUS
(EFIAPI *FP_CLEAR_DRAM_POSTPKG_REPAIR_ENTRY) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This
  );

///Function used to add a DRAM POST Package repair entry
typedef
EFI_STATUS
(EFIAPI *FP_ADD_DRAM_POSTPKG_REPAIR_ENTRY) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       DRRP_REPAIR_ENTRY *Entry
  );

///Function used to remove a DRAM POST Package repair entry
typedef
EFI_STATUS
(EFIAPI *FP_REMOVE_DRAM_POSTPKG_REPAIR_ENTRY) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       DRRP_REPAIR_ENTRY *Entry
  );

///Function used to acquire the mutex for subsequent APCB operations
typedef
EFI_STATUS
(EFIAPI *FP_ACQUIRE_MUTEX) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This
  );

///Function used to release the mutex for previous APCB operations
typedef
EFI_STATUS
(EFIAPI *FP_RELEASE_MUTEX) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This
  );

///Function used to get the value of an APCB BOOL token
typedef
EFI_STATUS
(EFIAPI *FP_GET_TOKEN_BOOL) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
     OUT   UINT8                        *Purpose,
  IN       UINT32                       TokenId,
     OUT   BOOLEAN                      *bValue
  );

///Function used to set the value of an APCB BOOL token
typedef
EFI_STATUS
(EFIAPI *FP_SET_TOKEN_BOOL) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT8                        Purpose,
  IN       UINT32                       TokenId,
  IN       BOOLEAN                      bValue
  );

///Function used to get the value of an APCB UINT8 token
typedef
EFI_STATUS
(EFIAPI *FP_GET_TOKEN_8) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
     OUT   UINT8                        *Purpose,
  IN       UINT32                       TokenId,
     OUT   UINT8                        *Value8
  );

///Function used to set the value of an APCB UINT8 token
typedef
EFI_STATUS
(EFIAPI *FP_SET_TOKEN_8) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT8                        Purpose,
  IN       UINT32                       TokenId,
  IN       UINT8                        Value8
  );

///Function used to get the value of an APCB UINT16 token
typedef
EFI_STATUS
(EFIAPI *FP_GET_TOKEN_16) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
     OUT   UINT8                        *Purpose,
  IN       UINT32                       TokenId,
     OUT   UINT16                       *Value16
  );

///Function used to set the value of an APCB UINT16 token
typedef
EFI_STATUS
(EFIAPI *FP_SET_TOKEN_16) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT8                        Purpose,
  IN       UINT32                       TokenId,
  IN       UINT16                       Value16
  );

///Function used to get the value of an APCB UINT32 token
typedef
EFI_STATUS
(EFIAPI *FP_GET_TOKEN_32) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
     OUT   UINT8                        *Purpose,
  IN       UINT32                       TokenId,
     OUT   UINT32                       *Value32
  );

///Function used to set the value of an APCB UINT32 token
typedef
EFI_STATUS
(EFIAPI *FP_SET_TOKEN_32) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT8                        Purpose,
  IN       UINT32                       TokenId,
  IN       UINT32                       Value32
  );

///Function used to retrive the data of a specified type
typedef
EFI_STATUS
(EFIAPI *FP_GET_TYPE) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
      OUT  UINT8                        *Purpose,
  IN       UINT16                       GroupId,
  IN       UINT16                       TypeId,
      OUT  UINT8                        **DataBuf,
      OUT  UINT32                       *DataSize
  );

///Function used to set the data of a specified type
typedef
EFI_STATUS
(EFIAPI *FP_SET_TYPE) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT8                        Purpose,
  IN       UINT16                       GroupId,
  IN       UINT16                       TypeId,
      OUT  UINT8                        *DataBuf,
      OUT  UINT32                       DataSize
  );

///Function used to purge all APCB token/value pairs
typedef
EFI_STATUS
(EFIAPI *FP_PURGE_ALL_TOKENS) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT8                        Purpose
  );

///Function used to purge the data of all types
typedef
EFI_STATUS
(EFIAPI *FP_PURGE_ALL_TYPES) (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT8                        Purpose
  );

///
/// Protocol prototype
///
/// Defines AMD_APCB_SERVICE_PPI, which publish the APCB service across all programs
///
struct _AMD_APCB_SERVICE_PROTOCOL {
  //
  // Common APCB services
  //
  UINT32                                Version;                          ///< Version number of the protocol
  FP_SET_ACTIVE_APCB_INSTANCE           ApcbSetActiveInstance;            ///< Set the actove instance of APCB
  FP_FLUSH_APCB_DATA                    ApcbFlushData;                    ///< Flush APCB data back to the SPI ROM
  FP_GET_DRAM_POSTPKG_REPAIR_ENTRY      ApcbGetDramPostPkgRepairEntries;  ///< Retrieve DRAM Post Package Repair Entries
  FP_CLEAR_DRAM_POSTPKG_REPAIR_ENTRY    ApcbClearDramPostPkgRepairEntry;  ///< Clear DRAM Post Package Repair Entries
  FP_ADD_DRAM_POSTPKG_REPAIR_ENTRY      ApcbAddDramPostPkgRepairEntry;    ///< Add a DRAM Post Package Repair Entry
  FP_REMOVE_DRAM_POSTPKG_REPAIR_ENTRY   ApcbRemoveDramPostPkgRepairEntry; ///< Remove a DRAM Post Package Repair Entry
  //
  // APCB 2.0 services
  //
  FP_GET_CONFIG_PARAM                   ApcbGetConfigParameter;           ///< Get an APCB configuration parameter
  FP_SET_CONFIG_PARAM                   ApcbSetConfigParameter;           ///< Set an APCB configuration parameter
  FP_GET_CBS_PARAM                      ApcbGetCbsParameter;              ///< Get an APCB CBS parameter
  FP_SET_CBS_PARAM                      ApcbSetCbsParameter;              ///< Set an APCB CBS parameter
  FP_UPDATE_CBS_APCB_DATA               ApcbUpdateCbsData;                ///< Update CBS APCB data
  //
  // APCB 3.0 services
  //
  FP_ACQUIRE_MUTEX                      ApcbAcquireMutex;                 ///< Aquire Mutex
  FP_RELEASE_MUTEX                      ApcbReleaseMutex;                 ///< Release Mutex
  FP_GET_TOKEN_BOOL                     ApcbGetTokenBool;                 ///< Get an APCB BOOL token
  FP_SET_TOKEN_BOOL                     ApcbSetTokenBool;                 ///< Set an APCB BOOL token
  FP_GET_TOKEN_8                        ApcbGetToken8;                    ///< Get an APCB UINT8 token
  FP_SET_TOKEN_8                        ApcbSetToken8;                    ///< Set an APCB UINT8 token
  FP_GET_TOKEN_16                       ApcbGetToken16;                   ///< Get an APCB UINT16 token
  FP_SET_TOKEN_16                       ApcbSetToken16;                   ///< Set an APCB UINT16 token
  FP_GET_TOKEN_32                       ApcbGetToken32;                   ///< Get an APCB UINT32 token
  FP_SET_TOKEN_32                       ApcbSetToken32;                   ///< Set an APCB UINT32 token
  FP_GET_TYPE                           ApcbGetType;                      ///< Retrieve the data of a specified type
  FP_SET_TYPE                           ApcbSetType;                      ///< Set the data of a specified type
  FP_PURGE_ALL_TOKENS                   ApcbPurgeAllTokens;               ///< Purge all token/value pairs
  FP_PURGE_ALL_TYPES                    ApcbPurgeAllTypes;                ///< Purge the data of all types
};

extern EFI_GUID gAmdApcbDxeServiceProtocolGuid;
extern EFI_GUID gAmdApcbSmmServiceProtocolGuid;

#endif //_AMD_APCB_SERVICE_PROTOCOL_H_

