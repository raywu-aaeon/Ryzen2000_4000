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
 * @e \$Revision: 327431 $   @e \$Date: 2015-09-21 23:18:33 +0800 (Mon, 21 Sep 2015) $
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

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include  "Gnb.h"
#include  "GnbLib.h"
#include  "GnbPcieConfig.h"
#include  "GnbCommonLib.h"
#include  "OptionGnb.h"
#include  "GnbPcieInitLib.h"
#include  "GnbSmuInitLibV8.h"
#include  "Library/AmdHeapLib.h"
#include  "GnbFamServices.h"
#include  <Library/AmdS3SaveLib.h>
#include  <Library/IoLib.h>

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBSMULIBV8_GNBSMUINITLIBV8_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

#ifndef INVALID_SMU_MSG
  #define INVALID_SMU_MSG  0xFF
#endif

#define BIOSSMC_Result_FATAL      ((UINT8)0xFC)     // i.e. -4

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */
/// OPN strcuture
typedef struct {
  CHAR8   Opn[13];
  UINT32  ConfigID;
} OPN_CZ_STRUCT;

// Needed for floating point support, linker expects this symbol to be defined.
CONST INT32 _fltused = 0;

// F15CzVidWorkaroundPstateAdjustmentTable copied from CcxXvPowerMgmt.c
F15CZ_VID_WA_PSTATE_ADJ  F15CzVidWorkaroundPstateAdjustmentTable[] = {
  {0, 8},
  {1, 4},
  {0xFF, 0xFF}
};
/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

VOID
GnbSmuServiceCommonInitArgumentsV8 (
  IN       GNB_HANDLE               *GnbHandle,
  IN       AMD_CONFIG_PARAMS        *StdHeader,
  IN OUT   DEV_OBJECT               *DevObject,
  IN OUT   UINT32                   *SmuArg
  )
{
  DevObject->GnbHandle = GnbHandle;
  DevObject->StdHeader = StdHeader;
  DevObject->DevPciAddress = GnbGetHostPciAddress (GnbHandle);
  LibAmdMemFill (SmuArg, 0x00, 24, StdHeader);
}

/*----------------------------------------------------------------------------------------*/
/**
 * SMU service request
 *
 *
 * @param[in]       DevObject       Pointer to Device object
 * @param[in]       RequestId       Request ID
 * @param[in, out]  RequestArgument Request Argument
 * @param[in]       AccessFlags     See GNB_ACCESS_FLAGS_* definitions
 */

VOID
GnbSmuServiceRequestV8 (
  IN       DEV_OBJECT               *DevObject,
  IN       UINT32                   RequestId,
  IN OUT   UINT32                   *RequestArgument,
  IN       UINT32                   AccessFlags
  )
{
  UINT32                      RxSmuMessageResponse;
  GNB_BUILD_OPTIONS_COMMON    *GnbCommonOptions;
  UINT32                      DataMask;
  UINT32                      Address;
  PCI_ADDR                    PciAddressValue;

  AGESA_TESTPOINT (TpGnbSmuServiceRequestV8Entry, NULL);
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbSmuServiceRequestV8 Enter\n");

  GnbCommonOptions = (GNB_BUILD_OPTIONS_COMMON*) GnbFmGnbBuildOptions (DevObject->StdHeader);

  DataMask = 0xFFFFFFFF;

  if (!GnbCommonOptions->CfgSmuMessageEnable) {
    IDS_HDT_CONSOLE (GNB_TRACE, "BIOS FORCE SKIP SMU SERVICE!!\n");
    return;
  }

  if (RequestId == INVALID_SMU_MSG) {
    IDS_HDT_CONSOLE (GNB_TRACE, "GnbSmuServiceRequestV8 INVALID!!\n");
    return;
  }

  IDS_HDT_CONSOLE (NB_MISC, "  Service Request 0x%x\n", RequestId);
  IDS_HDT_CONSOLE (NB_MISC, "  Service Request Argument 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n", RequestArgument[0], RequestArgument[1], RequestArgument[2], RequestArgument[3], RequestArgument[4], RequestArgument[5]);

  GnbLibPciIndirectRead (MAKE_SBDFO (0, 0, 0, 0, D0F0xB8_ADDRESS), D0F0xBC_x13000010_ADDRESS, AccessWidth32, &RxSmuMessageResponse, DevObject->StdHeader);

  // Log last time response status
  IoWrite8 (0x85, (UINT8) RxSmuMessageResponse);

  // 1 Clear Response
  RxSmuMessageResponse = 0;
  GnbLibPciIndirectWrite (MAKE_SBDFO (0, 0, 0, 0, D0F0xB8_ADDRESS), D0F0xBC_x13000010_ADDRESS, AccessWidth32 | (AccessFlags << 7), &RxSmuMessageResponse, DevObject->StdHeader);

  do {
  GnbLibPciIndirectRead (MAKE_SBDFO (0, 0, 0, 0, D0F0xB8_ADDRESS), D0F0xBC_x13000010_ADDRESS, AccessWidth32, &RxSmuMessageResponse, DevObject->StdHeader);
  } while (RxSmuMessageResponse != 0x0);

  // 2 Write message arguments
  GnbLibPciIndirectWrite (MAKE_SBDFO (0, 0, 0, 0, D0F0xB8_ADDRESS), D0F0xBC_x13000020_ADDRESS, AccessWidth32 | (AccessFlags << 7), &RequestArgument[0], DevObject->StdHeader);
  GnbLibPciIndirectWrite (MAKE_SBDFO (0, 0, 0, 0, D0F0xB8_ADDRESS), D0F0xBC_x13000024_ADDRESS, AccessWidth32 | (AccessFlags << 7), &RequestArgument[1], DevObject->StdHeader);
  GnbLibPciIndirectWrite (MAKE_SBDFO (0, 0, 0, 0, D0F0xB8_ADDRESS), D0F0xBC_x13000028_ADDRESS, AccessWidth32 | (AccessFlags << 7), &RequestArgument[2], DevObject->StdHeader);
  GnbLibPciIndirectWrite (MAKE_SBDFO (0, 0, 0, 0, D0F0xB8_ADDRESS), D0F0xBC_x1300002C_ADDRESS, AccessWidth32 | (AccessFlags << 7), &RequestArgument[3], DevObject->StdHeader);
  GnbLibPciIndirectWrite (MAKE_SBDFO (0, 0, 0, 0, D0F0xB8_ADDRESS), D0F0xBC_x13000030_ADDRESS, AccessWidth32 | (AccessFlags << 7), &RequestArgument[4], DevObject->StdHeader);
  GnbLibPciIndirectWrite (MAKE_SBDFO (0, 0, 0, 0, D0F0xB8_ADDRESS), D0F0xBC_x13000034_ADDRESS, AccessWidth32 | (AccessFlags << 7), &RequestArgument[5], DevObject->StdHeader);
  IoWrite32 (0x88, RequestArgument[0]);

  AGESA_TESTPOINT (((RequestId & 0xFF) | 0xE000), NULL);
  // 3 Write message ID
  GnbLibPciIndirectWrite (MAKE_SBDFO (0, 0, 0, 0, D0F0xB8_ADDRESS), D0F0xBC_x13000000_ADDRESS, AccessWidth32 | (AccessFlags << 7), &RequestId, DevObject->StdHeader);
  IoWrite8 (0x84, (UINT8) RequestId);

  // 4 Poll Response until non-zero
  IoWrite8 (0x87, 0xff);

  do {
  GnbLibPciIndirectRead (MAKE_SBDFO (0, 0, 0, 0, D0F0xB8_ADDRESS), D0F0xBC_x13000010_ADDRESS, AccessWidth32, &RxSmuMessageResponse, DevObject->StdHeader);
    IoWrite8 (0x86, (UINT8) RxSmuMessageResponse);
  } while (RxSmuMessageResponse == 0x0);

  if (AccessFlags) {
    RxSmuMessageResponse = 0x1;
    Address = D0F0xBC_x13000010_ADDRESS;
    PciAddressValue.AddressValue = MAKE_SBDFO (0, 0, 0, 0, D0F0xB8_ADDRESS);
    AmdS3SaveScriptPciWrite (AccessWidth32, PciAddressValue.AddressValue, &Address);
    PciAddressValue.AddressValue = MAKE_SBDFO (0, 0, 0, 0, (D0F0xB8_ADDRESS + 4));
    AmdS3SaveScriptPciPoll (AccessWidth32, PciAddressValue.AddressValue, &RxSmuMessageResponse, &DataMask, 0xffffffff);
  }

  IoWrite8 (0x87, 0);

  while (RxSmuMessageResponse == BIOSSMC_Result_FATAL) {
    AGESA_TESTPOINT (0xE0EE, NULL);
    ASSERT (FALSE);   // ASSERT if asserts are enabled
  }

  // 5 Read updated SMU message arguments
  GnbLibPciIndirectRead (MAKE_SBDFO (0, 0, 0, 0, D0F0xB8_ADDRESS), D0F0xBC_x13000020_ADDRESS, AccessWidth32, &RequestArgument[0], DevObject->StdHeader);
  GnbLibPciIndirectRead (MAKE_SBDFO (0, 0, 0, 0, D0F0xB8_ADDRESS), D0F0xBC_x13000024_ADDRESS, AccessWidth32, &RequestArgument[1], DevObject->StdHeader);
  GnbLibPciIndirectRead (MAKE_SBDFO (0, 0, 0, 0, D0F0xB8_ADDRESS), D0F0xBC_x13000028_ADDRESS, AccessWidth32, &RequestArgument[2], DevObject->StdHeader);
  GnbLibPciIndirectRead (MAKE_SBDFO (0, 0, 0, 0, D0F0xB8_ADDRESS), D0F0xBC_x1300002C_ADDRESS, AccessWidth32, &RequestArgument[3], DevObject->StdHeader);
  GnbLibPciIndirectRead (MAKE_SBDFO (0, 0, 0, 0, D0F0xB8_ADDRESS), D0F0xBC_x13000030_ADDRESS, AccessWidth32, &RequestArgument[4], DevObject->StdHeader);
  GnbLibPciIndirectRead (MAKE_SBDFO (0, 0, 0, 0, D0F0xB8_ADDRESS), D0F0xBC_x13000034_ADDRESS, AccessWidth32, &RequestArgument[5], DevObject->StdHeader);
  IoWrite32 (0x8c, RequestArgument[0]);

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbSmuServiceRequestV8 Exit\n");
  AGESA_TESTPOINT (TpGnbSmuServiceRequestV8Exit, NULL);

}

/*----------------------------------------------------------------------------------------*/
/**
 * SMU service request for S3 script
 *
 *
 * @param[in]  StdHeader       Standard configuration header
 * @param[in]  ContextLength   Context length
 * @param[in]  Context         Pointer to Context
 */

VOID
GnbSmuServiceRequestV8S3Script (
  IN      AMD_CONFIG_PARAMS     *StdHeader,
  IN      UINT16                ContextLength,
  IN      VOID                  *Context
  )
{
  SMU_MSG_CONTEXT_V8    *SmuMsgContext;
  DEV_OBJECT            DevObject;
  UINT32                SmuArg[6];
  SmuMsgContext =  (SMU_MSG_CONTEXT_V8 *) Context;

  DevObject.StdHeader = StdHeader;
  DevObject.DevPciAddress = SmuMsgContext->GnbPciAddress;
  DevObject.GnbHandle = GnbGetHandle (StdHeader);

  SmuArg[0] = SmuMsgContext->RequestArgument[0];
  SmuArg[1] = SmuMsgContext->RequestArgument[1];
  SmuArg[2] = SmuMsgContext->RequestArgument[2];
  SmuArg[3] = SmuMsgContext->RequestArgument[3];
  SmuArg[4] = SmuMsgContext->RequestArgument[4];
  SmuArg[5] = SmuMsgContext->RequestArgument[5];

  GnbSmuServiceRequestV8 (&DevObject, SmuMsgContext->RequestId, SmuArg, 0);
}


/*----------------------------------------------------------------------------------------*/
/**
 * SMU firmware test
 *
 *
 * @param[in]  GnbHandle       Pointer to GNB_HANDLE
 * @param[in]  RequestId       Request ID
 * @param[in]  StdHeader       Standard configuration header
 */

AGESA_STATUS
GnbSmuFirmwareTestV8 (
  IN       GNB_HANDLE               *GnbHandle,
  IN       UINT32                   RequestId,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  )
{
  DEV_OBJECT                  DevObject;
  UINT32                      SmuArg[6];

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbSmuFirmwareTestV8 Enter\n");

  GnbSmuServiceCommonInitArgumentsV8 (GnbHandle, StdHeader, &DevObject, SmuArg);
  SmuArg[0] = 0xAA55AA55;
  GnbSmuServiceRequestV8 (
    &DevObject,
    RequestId,
    SmuArg,
    0
    );

  IDS_HDT_CONSOLE (NB_MISC, "  Service Test Return %x\n", SmuArg[0]);
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbSmuFirmwareTestV8 Exit\n");

  if (SmuArg[0] == 0) {
    return AGESA_ERROR;
  }
  return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Power Up/Down iGPU
 *
 *
 *
 * @param[in]  GnbHandle       Pointer to GNB_HANDLE
 * @param[in]  RequestId       Request ID
 * @param[in]  StdHeader       Standard configuration header
 */
AGESA_STATUS
GnbSmuRequestGpuPowerV8 (
  IN       GNB_HANDLE               *GnbHandle,
  IN       UINT32                   RequestId,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  )
{
  DEV_OBJECT                DevObject;
  UINT32                    SmuArg[6];

  GnbSmuServiceCommonInitArgumentsV8 (GnbHandle, StdHeader, &DevObject, SmuArg);
  GnbSmuServiceRequestV8 (
    &DevObject,
    RequestId,
    SmuArg,
    0
    );

  return AGESA_SUCCESS;
}


AGESA_STATUS
GnbSmuLoadScsDataV8 (
  IN       GNB_HANDLE           *GnbHandle,
  IN       UINT8                *ScsDataPtr,
  IN       UINT32               RequestId,
  IN       AMD_CONFIG_PARAMS    *StdHeader
  )
{
  DEV_OBJECT                DevObject;
  AGESA_STATUS              Status;
  GNB_BUILD_OPTIONS_COMMON  *GnbCommonOptions;
  UINT32                    SmuArg[6];

  IDS_PERF_TIMESTAMP (TP_BEGINGNBLOADSCSDATA, StdHeader);

  Status = AGESA_SUCCESS;
  GnbCommonOptions = (GNB_BUILD_OPTIONS_COMMON*) GnbFmGnbBuildOptions (StdHeader);

  if ((!GnbCommonOptions->CfgSmuMessageEnable) || (RequestId == INVALID_SMU_MSG)) {
    IDS_HDT_CONSOLE (GNB_TRACE, "BIOS FORCE SKIP SMU SERVICE(Id = %x)!!\n", RequestId);
    return AGESA_SUCCESS;
  }

  LibAmdMemFill (SmuArg, 0x00, sizeof (SmuArg), StdHeader);

  if (GnbCommonOptions->CfgScsSupport == TRUE) {
    IDS_HDT_CONSOLE (GNB_TRACE, "GnbSmuLoadScsDataV8 Enter\n");
    //Check input parameters
    ASSERT ((ScsDataPtr != NULL) && (StdHeader != NULL));
    if ((ScsDataPtr == NULL) || (StdHeader == NULL)) {
      return AGESA_ERROR;
    }

    //Verify the SCS block signature
    ASSERT (*(UINT32 *)ScsDataPtr == SMU_SCS_SIGNATURE);
    if (*(UINT32 *)ScsDataPtr != SMU_SCS_SIGNATURE) {
      IDS_HDT_CONSOLE (GNB_TRACE, "Verify SCS Binary fail\n", ScsDataPtr);
      return AGESA_ERROR;
    }

    //Load SCS block
    IDS_HDT_CONSOLE (GNB_TRACE, "Load SCS @%08x\n", ScsDataPtr);
    DevObject.DevPciAddress.AddressValue = MAKE_SBDFO (0, 0, 0, 0, 0);
    DevObject.GnbHandle = GnbHandle;
    DevObject.StdHeader = StdHeader;
    SmuArg[0] = (UINT32) (UINTN) ScsDataPtr;
    GnbSmuServiceRequestV8 (&DevObject, RequestId, &SmuArg[0], 0);

    //Get SCS result and save to Heap
    Status = GnbSmuGetScsResultV8 (GnbHandle, StdHeader);
    IDS_HDT_CONSOLE (GNB_TRACE, "Get SCS Result %s\n", (Status == AGESA_SUCCESS) ? "Success" : "Fail");
  }

  IDS_PERF_TIMESTAMP (TP_ENDGNBLOADSCSDATA, StdHeader);
  return Status;
}

AGESA_STATUS
GnbSmuGetScsResultV8 (
  IN       GNB_HANDLE           *GnbHandle,
  IN       AMD_CONFIG_PARAMS    *StdHeader
  )
{
  UINT32                      ScsResultAddr;
  UINT32                      NumApmWeights;
  AGESA_STATUS                Status;
  DEV_OBJECT                  DevObject;
  GNB_REGISTER_SERVICE        *GnbRegisterAccessProtocol;
  UINT32 fooval;

  Status = AGESA_SUCCESS;
  DevObject.GnbHandle = GnbHandle;
  DevObject.StdHeader = StdHeader;
  DevObject.DevPciAddress = GnbGetHostPciAddress (GnbHandle);

  Status = GnbLibLocateService (GnbRegisterAccessService, GnbGetSocketId (GnbHandle), &GnbRegisterAccessProtocol, StdHeader);
  ASSERT (Status == AGESA_SUCCESS);
  if (Status != AGESA_SUCCESS) {
    return Status;
  }

  //Get the command result (A pointer to SMURAM)
  ScsResultAddr = 0;
  GnbLibPciIndirectRead (MAKE_SBDFO (0, 0, 0, 0, D0F0xB8_ADDRESS), D0F0xBC_x13000020_ADDRESS, AccessWidth32, &ScsResultAddr, DevObject.StdHeader);

  IDS_HDT_CONSOLE (GNB_TRACE, "SMURAMAddr %08x ", ScsResultAddr);

  if (ScsResultAddr == 0) {
    return Status;
  }

  Status = GnbRegisterAccessProtocol->Read (GnbHandle, TYPE_D0F0xBC,
      (ScsResultAddr | 0x10000000) + offsetof (SMU_RAM_CPU_INFO, CountApmWeights),
      &NumApmWeights, 0, StdHeader);
  IDS_HDT_CONSOLE (GNB_TRACE, "NumApmWeights %d\n", NumApmWeights);

  fooval = NumApmWeights | 0xab550000;
  IoWrite32 (0x8c, fooval);

  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * SMU firmware ACP Power Gating
 *
 *
 * @param[in]  GnbHandle       Pointer to GNB_HANDLE
 * @param[in]  RequestId       Request ID
 * @param[in]  StdHeader       Standard configuration header
 */

AGESA_STATUS
GnbSmuAcpPowerGatingV8 (
  IN       GNB_HANDLE               *GnbHandle,
  IN       UINT32                   RequestId,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  )
{
  DEV_OBJECT                  DevObject;
  UINT32                      SmuArg[6];

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbSmuAcpPowerGatingV8 Enter\n");

  GnbSmuServiceCommonInitArgumentsV8 (GnbHandle, StdHeader, &DevObject, SmuArg);
  GnbSmuServiceRequestV8 (
    &DevObject,
    RequestId,
    SmuArg,
    0
    );
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbSmuAcpPowerGatingV8 Exit\n");
  return AGESA_SUCCESS;
}

UINT32
LibAmdReadFuse (
  IN       UINT32 FuseChain,
  IN       UINT32 BitPositionHi,
  IN       UINT32 BitPositionLo,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT32 SmuIndex;
  UINT32 SmuData;
  UINT32 BytePosition;
  UINT32 BitOffset;
  UINT32 BitDone;
  UINT32 RetVal;

  RetVal = 0;
  BitDone = 0;

  // Only support UINT32
  ASSERT ((BitPositionHi - BitPositionLo) <= 31);

  while (BitPositionHi >= BitPositionLo) {
    // 1. Get Byte positon and Bit offset in a 32-bits value read from FUSE
    BytePosition  = BitPositionLo / 8;
    BitOffset     = (BytePosition & 0x3) * 8;
    BytePosition &= 0xFFFFFFFC;  // DWORD aligned
    if ((BitPositionLo % 8) != 0) {
      BitOffset += (BitPositionLo % 8);
    }

		// 2. Read value from FUSE
    SmuIndex = 0xC0010000 + ((FuseChain & 0xF) << 12) + (BytePosition & 0x0FFF);
    GnbLibPciIndirectRead (MAKE_SBDFO (0, 0, 0, 0, 0xB8), SmuIndex, AccessWidth32, &SmuData, StdHeader);

    // 3. Get the bits we want and put it into RetVal
    if ((BitPositionHi - BitPositionLo) <= (31 - BitOffset)) {
      // We got all bits from this reading
      if ((BitOffset != 0) || ((BitPositionHi - BitPositionLo) != 31)) {
        // we don't need all 32-bits
        SmuData >>= BitOffset;
        SmuData &= (1 << (BitPositionHi - BitPositionLo + 1)) - 1;
      }
      RetVal  |= SmuData << BitDone;
      BitDone += BitPositionHi - BitPositionLo + 1;
    } else {
      // Just got some bits from this reading
      SmuData >>= BitOffset;
      SmuData &= (1 << (31 - BitOffset + 1)) - 1;
      RetVal  |= SmuData << BitDone;
      BitDone += 31 - BitOffset + 1;
    }
    BitPositionLo += BitDone;
  };

  return RetVal;
}

BOOLEAN
IsF15CzVidAdjustmentRequired (
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT8          i;
  UINT8          CharIndex;
  UINT8          Opn[13];
  UINT32         ConfigID;
  BOOLEAN        ReturnValue;
  OPN_CZ_STRUCT  OpnRequiredWA [] = {
    {
      {'A', 'D', '9', '8', '0', '0', 'A', 'U', 'M', '4', '4', 'A', 'B'}, {0xA5}
    },
    {
      {'A', 'D', '9', '8', '0', 'B', 'A', 'U', 'M', '4', '4', 'A', 'B'}, {0x95}
    },
    {
      {'A', 'D', '8', '8', '7', 'B', 'A', 'U', 'M', '4', '4', 'A', 'B'}, {0xB7}
    },
    {
      {'A', 'D', '9', '8', '0', '0', 'A', 'H', 'M', '4', '4', 'A', 'B'}, {0xBD}
    },
    {
      {'A', 'D', '9', '8', '0', 'B', 'A', 'H', 'M', '4', '4', 'A', 'B'}, {0xBE}
    },
    {
      {'A', 'D', '8', '8', '7', 'B', 'A', 'H', 'M', '4', '4', 'A', 'B'}, {0xB8}
    },
    {
      {0x0}, {0}
    }
  };

  ReturnValue = FALSE;

  // Read OPN from FUSE
  for (i = 0; i < 13; i++) {
    Opn[i] = (UINT8) LibAmdReadFuse (6, 2357 + i * 7, 2351 + i * 7, StdHeader);
  }

  // Compare OPN with OpnRequiredWA
  i = 0;
  while (OpnRequiredWA[i].Opn[0] != 0) {
    for (CharIndex = 0; CharIndex < 13; CharIndex++) {
      if (OpnRequiredWA[i].Opn[CharIndex] != Opn[CharIndex]) {
        break;
      }
    }
    if (CharIndex == 13) {
      // OPN is matched!!!
      ConfigID = LibAmdReadFuse (6, 314, 303, StdHeader);
      if (ConfigID == OpnRequiredWA[i].ConfigID) {
        ReturnValue = TRUE;
        break;
      }
    }
    i++;
  }
  return ReturnValue;
}


