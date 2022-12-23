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

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include  <AGESA.h>
#include  <Gnb.h>
#include  <Filecode.h>
#include  <Library/GnbLib.h>
#include  <Library/IdsLib.h>
#include  <Library/AmdBaseLib.h>
#include  <Library/NbioHandleLib.h>
#include  <Library/NbioSmuV10Lib.h>
#include  <Library/CpuLib.h>
#include  <Library/AmdS3SaveLib.h>

#define FILECODE LIBRARY_NBIOSMUV10LIB_NBIOSMUV10LIB_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

#ifndef INVALID_SMU_MSG
  #define INVALID_SMU_MSG  0xFF
#endif
#ifndef BIOSSMC_Result_FATAL
#define BIOSSMC_Result_FATAL      ((UINT8)0xFC)     // i.e. -4
#endif
/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */
#ifndef D0F0xB8_ADDRESS
  // **** D0F0xB8 Register Definition ****
  // Address
  #define D0F0xB8_ADDRESS          0xB8
#endif

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------*/
/*
 *  Routine to write SMU register space
 *
 *
 * @param[in] GnbPciAddress      PCI_ADDR
 * @param[in] Address            Register offset, but PortDevice
 * @param[in] Value              The value to write
 * @retval    AGESA_STATUS
 */
VOID
STATIC
SmuRegisterWrite (
  IN       PCI_ADDR            GnbPciAddress,
  IN       UINT32              Address,
  IN       VOID                *Value,
  IN       UINT32              Flags
  )
{
  ACCESS_WIDTH    Width;

  Width = (Flags == GNB_REG_ACC_FLAG_S3SAVE) ? AccessS3SaveWidth32 : AccessWidth32;
  GnbLibPciIndirectWrite (
    GnbPciAddress.AddressValue | D0F0xB8_ADDRESS,
    Address,
    Width,
    Value,
    NULL
  );
  return;
}

/*----------------------------------------------------------------------------------------*/
/*
 *  Routine to read SMU register space
 *
 *
 *
 * @param[in]  GnbPciAddress      PCI_ADDR
 * @param[in]  Address            Register offset, but PortDevice
 * @param[out] Value              Return value
 * @retval     AGESA_STATUS
 */
VOID
STATIC
SmuRegisterRead (
  IN       PCI_ADDR            GnbPciAddress,
  IN       UINT32              Address,
     OUT   VOID                *Value,
  IN       UINT32              Flags
  )
{
  ACCESS_WIDTH  Width;

  Width = (Flags == GNB_REG_ACC_FLAG_S3SAVE) ? AccessS3SaveWidth32 : AccessWidth32;
  GnbLibPciIndirectRead (
    GnbPciAddress.AddressValue | D0F0xB8_ADDRESS,
    (Address & (~0x3ull)),
    Width,
    Value,
    NULL
  );
  return;
}

/*----------------------------------------------------------------------------------------*/
/*
 *  Routine to Init Arguments
 *
 *
 *
 * @param[in, out]  SmuArg Request Argument
 */
VOID
NbioSmuServiceCommonInitArgumentsV10 (
  IN OUT   UINT32                   *SmuArg
  )
{
  LibAmdMemFill (SmuArg, 0x00, 24, NULL);
}

/*----------------------------------------------------------------------------------------*/
/**
 * SMU service request
 *
 *
 * @param[in]      NbioPciAddress  PCI_ADDR of this NBIO
 * @param[in]      RequestId       Request ID
 * @param[in, out] RequestArgument Request Argument
 * @param[in]      AccessFlags     See GNB_ACCESS_FLAGS_* definitions
 */

UINT32
NbioSmuServiceRequestV10 (
  IN       PCI_ADDR                 NbioPciAddress,
  IN       UINT32                   RequestId,
  IN OUT   UINT32                   *RequestArgument,
  IN       UINT32                   AccessFlags
  )
{
  UINT32                      RxSmuMessageResponse;
  UINT32                      DataMask;
  UINT32                      Address;

  IDS_HDT_CONSOLE (GNB_TRACE, "NbioSmuServiceRequestV10 Enter\n");

  DataMask = 0xFFFFFFFF;

  if (RequestId == INVALID_SMU_MSG) {
    IDS_HDT_CONSOLE (GNB_TRACE, "NbioSmuServiceRequestV10 INVALID!!\n");
    return BIOSSMC_Result_OK;
  }

  IDS_HDT_CONSOLE (NB_MISC, "  Service Request 0x%x\n", RequestId);
  IDS_HDT_CONSOLE (NB_MISC, "  Service Request Argument 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n", RequestArgument[0], RequestArgument[1], RequestArgument[2], RequestArgument[3], RequestArgument[4], RequestArgument[5]);

  SmuRegisterRead (NbioPciAddress, MP1_C2PMSG_RESPONSE_ADDRESS, &RxSmuMessageResponse, 0);

  // 1 Clear Response
  RxSmuMessageResponse = 0;
  SmuRegisterWrite (NbioPciAddress, MP1_C2PMSG_RESPONSE_ADDRESS, &RxSmuMessageResponse, AccessFlags);

  // 2 Write message arguments
  SmuRegisterWrite (NbioPciAddress, MP1_C2PMSG_ARGUMENT_0_ADDRESS, &RequestArgument[0], AccessFlags);
  SmuRegisterWrite (NbioPciAddress, MP1_C2PMSG_ARGUMENT_1_ADDRESS, &RequestArgument[1], AccessFlags);
  SmuRegisterWrite (NbioPciAddress, MP1_C2PMSG_ARGUMENT_2_ADDRESS, &RequestArgument[2], AccessFlags);
  SmuRegisterWrite (NbioPciAddress, MP1_C2PMSG_ARGUMENT_3_ADDRESS, &RequestArgument[3], AccessFlags);
  SmuRegisterWrite (NbioPciAddress, MP1_C2PMSG_ARGUMENT_4_ADDRESS, &RequestArgument[4], AccessFlags);
  SmuRegisterWrite (NbioPciAddress, MP1_C2PMSG_ARGUMENT_5_ADDRESS, &RequestArgument[5], AccessFlags);

  // 3 Write message ID
  SmuRegisterWrite (NbioPciAddress, MP1_C2PMSG_MESSAGE_ADDRESS, &RequestId, AccessFlags);

  // 4 Poll Response until non-zero
  do {
    SmuRegisterRead (NbioPciAddress, MP1_C2PMSG_RESPONSE_ADDRESS, &RxSmuMessageResponse, 0);
  } while (RxSmuMessageResponse == 0x0);

///@todo - implement S3 save for resume
  if (AccessFlags) {
    Address = MP1_C2PMSG_RESPONSE_ADDRESS;
    AmdS3SaveScriptPciWrite (AccessWidth32, NbioPciAddress.AddressValue | 0xB8, &Address);
    RxSmuMessageResponse = 0x1;
    DataMask = 0xFFFFFFFF;
    AmdS3SaveScriptPciPoll (AccessWidth32, NbioPciAddress.AddressValue | 0xBC, &RxSmuMessageResponse, &DataMask, 0xffffffff);
  }

  while (RxSmuMessageResponse == BIOSSMC_Result_FATAL) {
    IDS_HDT_CONSOLE (GNB_TRACE, "SMU Assert AccessFlags\n");
    ASSERT (FALSE);   // ASSERT if asserts are enabled
  }

  // 5 Read updated SMU message arguments
  SmuRegisterRead (NbioPciAddress, MP1_C2PMSG_ARGUMENT_0_ADDRESS, &RequestArgument[0], 0);
  SmuRegisterRead (NbioPciAddress, MP1_C2PMSG_ARGUMENT_1_ADDRESS, &RequestArgument[1], 0);
  SmuRegisterRead (NbioPciAddress, MP1_C2PMSG_ARGUMENT_2_ADDRESS, &RequestArgument[2], 0);
  SmuRegisterRead (NbioPciAddress, MP1_C2PMSG_ARGUMENT_3_ADDRESS, &RequestArgument[3], 0);
  SmuRegisterRead (NbioPciAddress, MP1_C2PMSG_ARGUMENT_4_ADDRESS, &RequestArgument[4], 0);
  SmuRegisterRead (NbioPciAddress, MP1_C2PMSG_ARGUMENT_5_ADDRESS, &RequestArgument[5], 0);

  IDS_HDT_CONSOLE (GNB_TRACE, "NbioSmuServiceRequestV10 Exit\n");
  return (RxSmuMessageResponse);
}

/*----------------------------------------------------------------------------------------*/
/**
 * SMU firmware test
 *
 *
 * @param[in]  NbioHandle     Pointer to GNB_HANDLE
 */

AGESA_STATUS
NbioSmuFirmwareTestV10 (
  IN       GNB_HANDLE               *NbioHandle
  )
{
  UINT32                      SmuArg[6];
  UINT32                      RequestId;
  UINT32                      Response;

  IDS_HDT_CONSOLE (MAIN_FLOW, "NbioSmuFirmwareTestV10 Enter\n");

  NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
  SmuArg[0] = 0xAA55AA55;
  RequestId = SMC_MSG_TestMessage;

  Response = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), RequestId, SmuArg, 0);

  IDS_HDT_CONSOLE (MAIN_FLOW, "  Service Test Return %x\n", SmuArg[0]);
  IDS_HDT_CONSOLE (MAIN_FLOW, "NbioSmuFirmwareTestV10 Exit\n");

  if (SmuArg[0] == 0) {
    return AGESA_ERROR;
  }
  return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * DXIO firmware request - Common function
 *
 *
 * @param[in]      NbioHandle      Pointer to GNB_HANDLE
 * @param[in]      DxioMBoxRequest DXIO Mailbox Request ID
 * @param[in, out] DxioMBoxArg     SMU Argument structure - [0] entry reserved for DXIO Mailbox Request ID
 * @param[in]      AccessFlags     See GNB_ACCESS_FLAGS_* definitions
 */

UINT32
NbioDxioServiceRequestV10 (
  IN       GNB_HANDLE               *NbioHandle,
  IN       UINT32                   DxioMBoxRequest,
  IN OUT   UINT32                   *DxioMBoxArg,
  IN       UINT32                   AccessFlags
  )
{
  UINT32            RetVal;
  *DxioMBoxArg = DxioMBoxRequest;
  RetVal = NbioSmuServiceRequestV10 (
    NbioGetHostPciAddress (NbioHandle),
    SMC_MSG_DXIO_SERVICE,
    DxioMBoxArg,
    AccessFlags
    );
  IDS_HDT_CONSOLE (
    GNB_TRACE,
    "Return Args = 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, ",
    DxioMBoxArg[0],
    DxioMBoxArg[1],
    DxioMBoxArg[2],
    DxioMBoxArg[3],
    DxioMBoxArg[4],
    DxioMBoxArg[5]
    );

  return RetVal;
}


/*----------------------------------------------------------------------------------------*/
/**
 * SMU S3 Entry Notification
 *
 */

VOID
SmuNotifyS3Entry (
  )
{
  PCI_ADDR            NbioPciAddress;
  UINT32              RequestId;
  UINT32              RxSmuMessageResponse;

  NbioPciAddress.AddressValue = MAKE_SBDFO (0, 0, 0, 0, 0);

  SmuRegisterRead (NbioPciAddress, MP1_C2PMSG_RESPONSE_ADDRESS, &RxSmuMessageResponse, 0);

  // 1 Clear Response
  RxSmuMessageResponse = 0;
  SmuRegisterWrite (NbioPciAddress, MP1_C2PMSG_RESPONSE_ADDRESS, &RxSmuMessageResponse, 0);

  // 2 Clear Message Arguments
  SmuRegisterWrite (NbioPciAddress, MP1_C2PMSG_ARGUMENT_0_ADDRESS, &RxSmuMessageResponse, 0);
  SmuRegisterWrite (NbioPciAddress, MP1_C2PMSG_ARGUMENT_1_ADDRESS, &RxSmuMessageResponse, 0);
  SmuRegisterWrite (NbioPciAddress, MP1_C2PMSG_ARGUMENT_2_ADDRESS, &RxSmuMessageResponse, 0);
  SmuRegisterWrite (NbioPciAddress, MP1_C2PMSG_ARGUMENT_3_ADDRESS, &RxSmuMessageResponse, 0);
  SmuRegisterWrite (NbioPciAddress, MP1_C2PMSG_ARGUMENT_4_ADDRESS, &RxSmuMessageResponse, 0);
  SmuRegisterWrite (NbioPciAddress, MP1_C2PMSG_ARGUMENT_5_ADDRESS, &RxSmuMessageResponse, 0);

  // 3 Write message ID
  RequestId = SMC_MSG_S3Entry;
  SmuRegisterWrite (NbioPciAddress, MP1_C2PMSG_MESSAGE_ADDRESS, &RequestId, 0);

  // Halt execution
  CpuSleep ();

  return;
}


