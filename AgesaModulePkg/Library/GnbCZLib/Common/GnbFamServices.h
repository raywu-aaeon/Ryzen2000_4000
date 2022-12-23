/* $NoKeywords:$ */
/**
 * @file
 *
 * PCIe family specific services.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 312448 $   @e \$Date: 2015-02-06 10:57:34 +0800 (Fri, 06 Feb 2015) $
 *
 */
/*
*****************************************************************************
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
*
*/
#ifndef _GNBFAMSERVICES_H_
#define _GNBFAMSERVICES_H_

#include "Gnb.h"
#include "GnbPcie.h"
#include "GnbIommu.h"

typedef AGESA_STATUS (F_GNB_REGISTER_ACCESS) (
  IN       GNB_HANDLE                 *GnbHandle,
  IN       UINT8                      RegisterSpaceType,
  IN       UINT32                     Address,
  IN       VOID                       *Value,
  IN       UINT32                     Flags,
  IN       AMD_CONFIG_PARAMS          *StdHeader
);

/// Register Read/Write protocol
typedef struct {
  F_GNB_REGISTER_ACCESS               *Read;    ///< Read Register
  F_GNB_REGISTER_ACCESS               *Write;   ///< Write Register
} GNB_REGISTER_SERVICE;

AGESA_STATUS
GnbFmCreateIvrsEntry (
  IN       GNB_HANDLE                 *GnbHandle,
  IN       IVRS_BLOCK_TYPE            Type,
  IN       VOID                       *Ivrs,
  IN       AMD_CONFIG_PARAMS          *StdHeader
  );

typedef AGESA_STATUS F_GNBFMCREATEIVRSENTRY (
  IN       GNB_HANDLE                 *GnbHandle,
  IN       IVRS_BLOCK_TYPE            Type,
  IN       VOID                       *Ivrs,
  IN       AMD_CONFIG_PARAMS          *StdHeader
  );

BOOLEAN
GnbFmCheckIommuPresent (
  IN       GNB_HANDLE                 *GnbHandle,
  IN       AMD_CONFIG_PARAMS          *StdHeader
  );

typedef BOOLEAN F_GNBFMCHECKIOMMUPRESENT (
  IN       GNB_HANDLE                 *GnbHandle,
  IN       AMD_CONFIG_PARAMS          *StdHeader
  );

/// GNB IOMMU services
typedef struct {
  F_GNBFMCHECKIOMMUPRESENT             *GnbFmCheckIommuPresent;       ///< GnbFmCheckIommuPresent
  F_GNBFMCREATEIVRSENTRY               *GnbFmCreateIvrsEntry;         ///< GnbFmCreateIvrsEntry
} GNB_FAM_IOMMU_SERVICES;


typedef UINT8 (F_PCIE_MAXPAYLOAD_SETTING) (
  IN       PCIe_ENGINE_CONFIG    *Engine
);

/// MaxPayload service protocol
typedef struct {
  F_PCIE_MAXPAYLOAD_SETTING           *SetMaxPayload;   ///< Write Register
} PCIE_MAXPAYLOAD_SERVICE;



PCI_ADDR
GnbFmGetPciAddress (
  IN       GNB_HANDLE                 *GnbHandle,
  IN       AMD_CONFIG_PARAMS          *StdHeader
  );

AGESA_STATUS
GnbFmGetBusDecodeRange (
  IN       GNB_HANDLE                 *GnbHandle,
     OUT   UINT8                      *StartBusNumber,
     OUT   UINT8                      *EndBusNumber,
  IN       AMD_CONFIG_PARAMS          *StdHeader
  );

AGESA_STATUS
GnbFmGetLinkId (
  IN       GNB_HANDLE                 *GnbHandle,
     OUT   UINT8                      *LinkId,
  IN       AMD_CONFIG_PARAMS          *StdHeader
  );

typedef UINT32 F_GNBTIMESTAMP (
  IN       AMD_CONFIG_PARAMS          *StdHeader
  );

/// GNB Timestamp services
typedef struct {
  F_GNBTIMESTAMP                      *GnbFmTimeStamp;         ///< GnbFmTimeStamp
} GNB_FAM_TS_SERVICES;

VOID *
GnbFmAlibGetBaseTable (
  IN       AMD_CONFIG_PARAMS             *StdHeader
  );

typedef VOID * (F_GNBFMALIBGETBASETABLE) (
  IN       AMD_CONFIG_PARAMS          *StdHeader
  );

/// GNB Alib services
typedef struct {
  F_GNBFMALIBGETBASETABLE             *GnbFmAlibGetBaseTable;         ///< GnbFmAlibGetBaseTable
} GNB_FAM_ALIB_SERVICES;

VOID *
GnbFmGnbBuildOptions (
  IN       AMD_CONFIG_PARAMS             *StdHeader
  );

typedef VOID * (F_GNBFMALIBGETBUILDOPTIONS) (
  IN       AMD_CONFIG_PARAMS          *StdHeader
  );

/// GNB Build Options services
typedef struct {
  F_GNBFMALIBGETBUILDOPTIONS          *GnbFmGetBuildOptions;            ///< GnbFmBuildOptionsPtr
} GNB_FAM_BUILDOPTIONS_POINTERS;

#endif

