/* $NoKeywords:$ */
/**
 * @file
 *
 * NBIO Config Codec verb table.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-26 11:00:43 +0800 (Thu, 26 Feb 2015) $
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
#include  <Library/BaseLib.h>
#include  <AGESA.h>
#include  <Gnb.h>
#include  <Library/IdsLib.h>
#include  <Library/AmdBaseLib.h>
#include  <Library/GnbLib.h>
#include  <Library/GnbMemAccLib.h>
#include  <Filecode.h>

#define FILECODE LIBRARY_NBIOAZALIALIB_NBIOAZALIALIB_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define HDA_MAX_SDIN_NUM                 0x0F
#define TIMEOUT_LOOP_TIMES               0x10
#define TIMEOUT_STALL_10                 10
#define TIMEOUT_STALL_100                100

#define HDAx0008_ADDRESS                 0x8
#define HDAx000C_ADDRESS                 0xc
#define HDAx0060_ADDRESS                 0x60
#define HDAx0064_ADDRESS                 0x64
#define HDAx0068_ADDRESS                 0x68

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */
VOID
TimeOutStall (
  IN       UINTN              Microseconds
  )
{
  UINTN               uSec;
  UINT8               Data;

  //Simplified implementation
  uSec = Microseconds / 2;
  while (uSec != 0) {
    LibAmdIoRead (AccessS3SaveWidth8, 0x80, &Data, NULL);
    uSec--;
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Audio controller reset
 *
 *
 * @param[in]  HdaBaseAddress      BAR0 Address Map
 * @param[in]  StdHeader           Standard configuration header
 *
 */
AGESA_STATUS
ControllerReset (
  IN      UINT32            HdaBaseAddress,
  IN      AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT32        Value32;
  UINT32        Loops;

  GnbLibMemRead (HdaBaseAddress + HDAx0008_ADDRESS, AccessWidth32, &Value32, StdHeader);
  Value32 |= BIT0;
  GnbLibMemWrite (HdaBaseAddress + HDAx0008_ADDRESS, AccessWidth32, &Value32, StdHeader);

  for (Loops = 0; Loops < TIMEOUT_LOOP_TIMES; Loops++) {
    Value32 = 0;
    GnbLibMemRead (HdaBaseAddress + HDAx0008_ADDRESS, AccessWidth32, &Value32, StdHeader);
    if ((Value32 & BIT0) == BIT0) {
      return AGESA_SUCCESS;
    }
    TimeOutStall (TIMEOUT_STALL_10);
  }
  return AGESA_ERROR;
}

/*----------------------------------------------------------------------------------------*/
/**
 * wait for Immediate Status result valid
 *
 *
 * @param[in]  HdaBaseAddress      BAR0 Address Map
 * @param[in]  StdHeader           Standard configuration header
 *
 */
AGESA_STATUS
WaitImmediateStatus (
  IN      UINT32            HdaBaseAddress,
  IN      AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT32        BitValue;
  UINT32        Loops;

  for (Loops = 0; Loops < TIMEOUT_LOOP_TIMES; Loops++) {
    BitValue = 0;
    GnbLibMemRead (HdaBaseAddress + HDAx0068_ADDRESS, AccessWidth32, &BitValue, StdHeader);
    if ((BitValue & BIT1) == BIT1) {
      return AGESA_SUCCESS;
    }
    TimeOutStall (TIMEOUT_STALL_10);
  }
  return AGESA_ERROR;
}

/*----------------------------------------------------------------------------------------*/
/**
 * send HD Audio Codec Command
 *
 *
 * @param[in]       HdaBaseAddress      BAR0 Address Map
 * @param[in]       StdHeader           Standard configuration header
 * @param[in, out]  CodecCommandData    Command data
 * @param[in]       ReadBack            Retrieve the response
 *
 */
AGESA_STATUS
SendCodecCommand (
  IN       UINT32            HdaBaseAddress,
  IN       AMD_CONFIG_PARAMS *StdHeader,
  IN OUT   UINT32            *CodecCommandData,
  IN       BOOLEAN           ReadBack
  )
{
  AGESA_STATUS  Status;
  UINT32 BitValue;
  UINT32 Loops;

  Status = AGESA_ERROR;
  if (CodecCommandData == NULL) {
    return Status;
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "    ::SendCodecCommand Data = %x\n", (UINT32)*CodecCommandData);

  //
  // Clear Immediate Command Status
  //
  GnbLibMemRead (HdaBaseAddress + HDAx0068_ADDRESS, AccessWidth32, &BitValue, StdHeader);
  BitValue |= BIT0;
  GnbLibMemWrite (HdaBaseAddress + HDAx0068_ADDRESS, AccessWidth32, &BitValue, StdHeader);

  for (Loops = 0; Loops < TIMEOUT_LOOP_TIMES; Loops++) {
    BitValue = 0;
    GnbLibMemRead (HdaBaseAddress + HDAx0068_ADDRESS, AccessWidth32, &BitValue, StdHeader);
    if ((BitValue & (BIT0 | BIT1)) == 0) {
      Status = AGESA_SUCCESS;
      break;
    }
    TimeOutStall (TIMEOUT_STALL_10);
  }

  if (Status == AGESA_SUCCESS) {
    GnbLibMemWrite (HdaBaseAddress + HDAx0060_ADDRESS, AccessWidth32, CodecCommandData, StdHeader);
    Status = WaitImmediateStatus (HdaBaseAddress, StdHeader);
    if (Status == AGESA_SUCCESS) {
      if (ReadBack == TRUE) {
        GnbLibMemRead (HdaBaseAddress + HDAx0064_ADDRESS, AccessWidth32, CodecCommandData, StdHeader);
      }
    }
  }
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Config Codec verb table
 *
 *
 * @param[in]       HdaBaseAddress      BAR0 Address Map
 * @param[in]       VerbTable           Codec Verbtable address
 *
 */
AGESA_STATUS
NbioConfigureVerbTable (
  IN      UINT32            HdaBaseAddress,
  IN      UINT64            VerbTable
  )
{
  AGESA_STATUS     Status;
  UINT16           ChannelNum;
  UINT32           CodecStateMap;
  UINT32           CodecMask;
  UINT32           VendorDeviceId;
  UINT8            ParameterId;
  UINT32           VerbTableData;
  CODEC_VERB_TABLE_LIST   *VerbTableList;
  CODEC_VERB_TABLE_LIST   *VerbTableAddress;

  VerbTableAddress = (CODEC_VERB_TABLE_LIST *)VerbTable;
  VerbTableData = 0;

  IDS_HDT_CONSOLE (GNB_TRACE, "NbioConfigureVerbTable: HdaBaseAddress = %x, CodecVerbTable = %x\n", HdaBaseAddress, VerbTable);

  if (HdaBaseAddress == 0 || VerbTableAddress == NULL) {
    IDS_HDT_CONSOLE (GNB_TRACE, "    ERROR::HdaBaseAddress == 0 || VerbTableAddress == NULL\n");
    return AGESA_ERROR;
  }
  //
  // Perform CRST causes the controller to exit its Reset state and de-assert the link RESET# signal.
  //
  Status = ControllerReset (HdaBaseAddress, NULL);
  if (Status == AGESA_ERROR) {
    IDS_HDT_CONSOLE (GNB_TRACE, "    ERROR::Active Controller fail! \n");
    return Status;
  }

  //
  // To find out all codec through identification of the state change status
  // "STATESTS" bits.
  //
  TimeOutStall (TIMEOUT_STALL_100);
  GnbLibMemRead (HdaBaseAddress + HDAx000C_ADDRESS, AccessWidth32, &CodecStateMap, NULL);
  CodecStateMap = (CodecStateMap & 0xf0000) >> 16;
  IDS_HDT_CONSOLE (GNB_TRACE, "    ::CodecStateMap = %x\n", CodecStateMap);

  //
  // To confirm every SDIN if there is a codec on link.
  //
  for (ChannelNum = 0; ChannelNum < HDA_MAX_SDIN_NUM; ChannelNum++) {
    CodecMask = (1 << ChannelNum);
    if (CodecStateMap & CodecMask) {
      //
      // To read the Codec's vendor and device ID.
      //
      ParameterId = 0x00;
      VendorDeviceId = 0xF0000;
      VendorDeviceId |= (ChannelNum << 28);
      Status = SendCodecCommand (HdaBaseAddress, NULL, &VendorDeviceId, TRUE);
      IDS_HDT_CONSOLE (GNB_TRACE, "    ::Read the Codec's VendorDeviceId = %x\n", VendorDeviceId);
      if (Status == AGESA_SUCCESS) {
        VerbTableList = VerbTableAddress;
        while (VerbTableList->CodecId != 0xFFFFFFFF) {
          IDS_HDT_CONSOLE (GNB_TRACE, "    ::CodecId = %x, VendorDeviceId = %x\n", VerbTableList->CodecId, VendorDeviceId);
          if (VendorDeviceId == VerbTableList->CodecId) {
            //
            // Deliver Verb Entry
            //
            VerbTableList++;
            while (VerbTableList->CodecId != 0xFFFFFFFF) {
              VerbTableData = VerbTableList->CodecId;
              VerbTableData |= (ChannelNum << 28);
              Status = SendCodecCommand (HdaBaseAddress, NULL, &VerbTableData, FALSE);
              if (Status == AGESA_ERROR) {
                IDS_HDT_CONSOLE (GNB_TRACE, "    ERROR::CodecId = %x, Deliver Verb Data = %x fail! \n", VendorDeviceId, VerbTableData);
                break;
              }
              VerbTableList++;
            }
          } else {
            while (VerbTableList->CodecId != 0xFFFFFFFF) {
              VerbTableList++;
            }
          }
          //
          // Finished, break to search the next SDIN to detect Codec.
          //
          VerbTableList++;
          if (Status == AGESA_ERROR) {
            IDS_HDT_CONSOLE (GNB_TRACE, "    ERROR::CodecId = %x, Deliver Verb Data = %x fail! \n", VendorDeviceId, VerbTableData);
            break;
          }
          if (VerbTableList->CodecId == 0xFFFFFFFF) {
            IDS_HDT_CONSOLE (GNB_TRACE, "NbioConfigureVerbTable: End\n");
            break;
          }
        }
      } else {
        IDS_HDT_CONSOLE (GNB_TRACE, "    ERROR::Read the Codec's Failed.\n");
      }
    }
  }
  return Status;
}

