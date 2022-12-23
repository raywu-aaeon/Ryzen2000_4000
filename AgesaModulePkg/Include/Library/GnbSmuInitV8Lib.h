/* $NoKeywords:$ */
/**
 * @file
 *
 * SMU services
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-25 21:00:43 -0600 (Wed, 25 Feb 2015) $
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
#ifndef _GNBNBINITV8LIB_H_
#define _GNBNBINITV8LIB_H_

#pragma pack (push, 1)
#include  <AMD.h>
#include  <GnbPcie.h>
#include  <Library/GnbUraServicesLib.h>

/// SMU service request contect
typedef struct {
  PCI_ADDR          GnbPciAddress;    ///< PCIe address of GNB
  UINT32            RequestId;        ///< Request/Msg ID
  UINT32            RequestArgument[6]; ///< Request/Msg Argument
} SMU_MSG_CONTEXT_V8;

#define SIZE_OF_APMWEIGHTS      (sizeof (UINT32))
/// SCS result struct
typedef struct {
  UINT64        EnergyCountConstant;  ///< copied from SCS table
  UINT64        BoostTimeConstant;    ///< copied from SCS table
  UINT32        CountApmWeights;      ///< length of APMWeights array
//  UINT32        ApmWeights[1];        ///< ApmWeights
} SMU_RAM_CPU_INFO;

/// SMU PCIe Phy/Core PG struct
typedef union {
  struct {                                                              ///<
    UINT32                                                       Rx:1 ; ///<
    UINT32                                                       Tx:1 ; ///<
    UINT32                                                     Core:1 ; ///<
    UINT32                                                  SkipPhy:1 ; ///<
    UINT32                                                 SkipCore:1 ; ///<
    UINT32                                            Reserved_15_5:11; ///<
    UINT32                                              LowerLaneID:8 ; ///<
    UINT32                                              UpperLaneID:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} SMU_PCIE_PHY_LN_STRUCT;
/// SMU TDP contect
typedef struct {
  UINT32            SmuTdp;        ///< TDP returned by SMU
  UINT32            cTdp;          ///< Config TDP
} SMU_TDP_INFO;

#pragma pack (pop)

#define SMU_SCS_SIGNATURE STRING_TO_UINT32 ('!', 'S', 'C', 'S')
#ifndef TYPE_D0F0xBC
  #define  TYPE_D0F0xBC               0x4
#endif

/// SMU V8 basic lib

VOID
GnbSmuServiceCommonInitArgumentsV8 (
  IN       GNB_HANDLE               *GnbHandle,
  IN       AMD_CONFIG_PARAMS        *StdHeader,
  IN OUT   DEV_OBJECT               *DevObject,
  IN OUT   UINT32                   *SmuArg
  );


VOID
GnbSmuServiceRequestV8 (
  IN       DEV_OBJECT               *DevObject,
  IN       UINT32                   RequestId,
  IN OUT   UINT32                   *RequestArgument,
  IN       UINT32                   AccessFlags
  );

AGESA_STATUS
GnbSmuLoadScsDataV8 (
  IN       GNB_HANDLE           *GnbHandle,
  IN       UINT8                *ScsDataPtr,
  IN       UINT32               RequestId,
  IN       AMD_CONFIG_PARAMS    *StdHeader
  );

VOID
GnbSmuServiceRequestV8S3Script (
  IN      AMD_CONFIG_PARAMS     *StdHeader,
  IN      UINT16                ContextLength,
  IN      VOID                  *Context
  );

AGESA_STATUS
GnbSmuGetScsResultV8 (
  IN       GNB_HANDLE           *GnbHandle,
  IN       AMD_CONFIG_PARAMS    *StdHeader
  );


/// SMU V8 message interface

AGESA_STATUS
GnbSmuFirmwareTestV8 (
  IN       GNB_HANDLE               *GnbHandle,
  IN       UINT32                   RequestId,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  );

AGESA_STATUS
GnbSmuRequestGpuPowerV8 (
  IN       GNB_HANDLE               *GnbHandle,
  IN       UINT32                   RequestId,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  );

AGESA_STATUS
GnbSmuAcpPowerGatingV8 (
  IN       GNB_HANDLE               *GnbHandle,
  IN       UINT32                   RequestId,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  );

#endif

