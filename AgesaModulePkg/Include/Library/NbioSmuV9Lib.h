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
#ifndef _NBIOSMUV9LIB_H_
#define _NBIOSMUV9LIB_H_

#include <NbioRegisterTypes.h>

#define BIOSSMC_Result_OK             0x1                 // The operations was successful.

#define SMC_MSG_TestMessage                0x1
#define SMC_MSG_GetSmuVersion              0x2
#define SMC_MSG_GetBiosIfVersion           0x3
#define SMC_MSG_DfPstateChng               0x4 // DO NOT CHANGE, USED IN DV
#define SMC_MSG_CpuPstateChng              0x5
#define SMC_MSG_ConfigureWaflLinks         0x6
#define SMC_MSG_QueryReadyDramTraining     0x7
#define SMC_MSG_SetSharedDramAddress       0x8
#define SMC_MSG_EnableSmuFeatures          0x9
#define SMC_MSG_PmLogSetDramAddrHigh       0xB
#define SMC_MSG_PmLogSetDramAddrLow        0xC
#define SMC_MSG_DramLogSetDramAddrHigh     0xD
#define SMC_MSG_DramLogSetDramAddrLow      0xE
#define SMC_MSG_DXIO_SERVICE               0xF
#define SMC_MSG_ReadCoreCacWeightRegister  0x10
#define SMC_MSG_DfPerfMonCfg               0x11
#define SMC_MSG_GetThrottlerThresholds     0x12
#define SMC_MSG_S3Entry                    0x13
#define SMC_MSG_EnableHotPlug              0x14
#define SMC_MSG_DisableHotPlug             0x15
#define SMC_MSG_GPIOService                0x16
#define SMC_MSG_SetI2CBusSwitchBaseAddress 0x17
#define SMC_MSG_ConfigureNTBUsageMode      0x18
#define SMC_MSG_EnableNTBOptions           0x19
#define SMC_MSG_DisableNTBOptions          0x1A
#define SMC_MSG_EnableLnkWdthMgt           0x1B
#define SMC_MSG_DisableLnkWdthMgt          0x1C
#define SMC_MSG_SetBiosDramAddrHigh        0x1D
#define SMC_MSG_SetBiosDramAddrLow         0x1E
#define SMC_MSG_SetToolsDramAddrHigh       0x1F
#define SMC_MSG_SetToolsDramAddrLow        0x20
#define SMC_MSG_TransferTableSmu2Dram      0x21
#define SMC_MSG_TransferTableDram2Smu      0x22
#define SMC_MSG_AcBtcStartCal              0x23
#define SMC_MSG_AcBtcStopCal               0x24
#define SMC_MSG_AcBtcEndCal                0x25
#define SMC_MSG_DcBtc                      0x26
#define SMC_MSG_BtcRestoreOnS3Resume       0x27
#define BIOSSMC_MSG_GetNameString          0x28
#define SMC_MSG_CheckTdcCompatibility      0x29
#define SMC_MSG_CheckEdcCompatibility      0x2A
#define SMC_MSG_DramLogSetDramSize         0x2B
#define SMC_MSG_ReadPerfmonBaseAddress     0x2C
#define SMC_MSG_SetPerfmonDramAddressHigh  0x2D
#define SMC_MSG_SetPerfmonDramAddressLow   0x2E
#define SMC_MSG_SetGPIOInterruptCommand    0x2F
#define SMC_MSG_GetGPIOInterruptStatus     0x30
#define SMC_MSG_SetPPTLimit                0x31
#define SMC_MSG_SetEMBlinkInterval         0x32
#define SMC_MSG_OptimizeCakeDataLatency    0x33
#define SMC_MSG_IommuInterruptRemap        0x34
#define SMC_MSG_DisablePSI                 0x35
#define SMC_MSG_TDP_TJMAX                  0x36
#define SMC_MSG_OC_DISABLE                 0x37
#define SMC_MSG_OC_VOLTAGEMAX              0x38     //mV
#define SMC_MSG_OC_FREQMAX                 0x39     //Mhz
#define SMC_MSG_TCTL_OFFSET                0x3A
#define SMC_MSG_PCIeInterruptRemap         0x3B
#define SMC_MSG_DisableScrubberWA          0x3C
#define SMC_MSG_PCIeAERlogRemap            0x3D
#define SMC_MSG_SetHotplugPollInterval     0x3E
#define SMC_MSG_SATA_RESET                 0x3F
#define SMC_MSG_TJFMAXADJST                0x40
#define SMC_MSG_VMIN_LIMITING              0x41
#define SMC_MSG_APCB_DEBUG                 0x42
#define SMC_MSG_SetTDCLimit                0x43
#define SMC_MSG_SetEDCLimit                0x44
#define SMC_MSG_SetFITLimit                0x45
#define SMC_MSG_SetTjMax                   0x46
#define SMC_MSG_GetCorePerfOrder           0x47
#define SMC_MSG_SetFITLimitScalar          0x48
#define SP3_SMC_MSG_spare2                 0x43
#define SP3_SMC_MSG_DIS_1003               0x44
#define SP3_SMC_MSG_SetHotplugDebugFlags   0x45
#define SP3_SMC_MSG_EnableGpio89Polling    0x46
#define SP3_SMC_MSG_Frange_PSMOffset       0x47
#define SP3_SMC_MSG_EnableI2cConfig        0x48
#define CF_SMC_MSG_GetCorePerfOrder        0x49
#define CF_SMC_MSG_SetTDCLimit             0x4A
#define CF_SMC_MSG_SetEDCLimit             0x4B
#define CF_SMC_MSG_SetFITLimit             0x4C
#define CF_SMC_MSG_SetTjMax                0x4D
#define CF_SMC_MSG_SetFITLimitScalar       0x4E
#define SMC_Message_Count                  0x4F

#define SMC_DXIO_MSG_XGMI_READAPTATION     0x34

// Address
#define MP1_C2PMSG_MESSAGE_ADDRESS                         0x3B10528ul

// Type
#define MP1_C2PMSG_MESSAGE_TYPE                            TYPE_SMN

#define MP1_C2PMSG_MESSAGE_CONTENT_OFFSET                  0
#define MP1_C2PMSG_MESSAGE_CONTENT_WIDTH                   32
#define MP1_C2PMSG_MESSAGE_CONTENT_MASK                    0xffffffffUL

/// MP1_C2PMSG_MESSAGE
typedef union {
  struct {                                                             ///<
    UINT32                                                 CONTENT:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} MP1_C2PMSG_MESSAGE_STRUCT;

// Address
#define MP1_C2PMSG_RESPONSE_ADDRESS                        0x3B10564ul

// Type
#define MP1_C2PMSG_RESPONSE_TYPE                           TYPE_SMN

#define MP1_C2PMSG_RESPONSE_CONTENT_OFFSET                 0
#define MP1_C2PMSG_RESPONSE_CONTENT_WIDTH                  32
#define MP1_C2PMSG_RESPONSE_CONTENT_MASK                   0xffffffffUL

/// MP1_C2PMSG_RESPONSE
typedef union {
  struct {                                                             ///<
    UINT32                                                 CONTENT:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} MP1_C2PMSG_RESPONSE_STRUCT;


// Address
#define MP1_C2PMSG_ARGUMENT_0_ADDRESS                      0x3B10598ul

// Type
#define MP1_C2PMSG_ARGUMENT_0_TYPE                         TYPE_SMN

#define MP1_C2PMSG_ARGUMENT_0_CONTENT_OFFSET               0
#define MP1_C2PMSG_ARGUMENT_0_CONTENT_WIDTH                32
#define MP1_C2PMSG_ARGUMENT_0_CONTENT_MASK                 0xffffffffUL

/// MP1_C2PMSG_ARGUMENT_0
typedef union {
  struct {                                                             ///<
    UINT32                                                 CONTENT:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} MP1_C2PMSG_ARGUMENT_0_STRUCT;


// Address
#define MP1_C2PMSG_ARGUMENT_1_ADDRESS                      0x3B1059cul

// Type
#define MP1_C2PMSG_ARGUMENT_1_TYPE                         TYPE_SMN

#define MP1_C2PMSG_ARGUMENT_1_CONTENT_OFFSET               0
#define MP1_C2PMSG_ARGUMENT_1_CONTENT_WIDTH                32
#define MP1_C2PMSG_ARGUMENT_1_CONTENT_MASK                 0xffffffffUL

/// MP1_C2PMSG_ARGUMENT_1
typedef union {
  struct {                                                             ///<
    UINT32                                                 CONTENT:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} MP1_C2PMSG_ARGUMENT_1_STRUCT;


// Address
#define MP1_C2PMSG_ARGUMENT_2_ADDRESS                      0x3B105a0UL

// Type
#define MP1_C2PMSG_ARGUMENT_2_TYPE                         TYPE_SMN

#define MP1_C2PMSG_ARGUMENT_2_CONTENT_OFFSET               0
#define MP1_C2PMSG_ARGUMENT_2_CONTENT_WIDTH                32
#define MP1_C2PMSG_ARGUMENT_2_CONTENT_MASK                 0xffffffff

/// MP1_C2PMSG_ARGUMENT_2
typedef union {
  struct {                                                             ///<
    UINT32                                                 CONTENT:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} MP1_C2PMSG_ARGUMENT_2_STRUCT;


// Address
#define MP1_C2PMSG_ARGUMENT_3_ADDRESS                      0x3B105a4UL

// Type
#define MP1_C2PMSG_ARGUMENT_3_TYPE                         TYPE_SMN

#define MP1_C2PMSG_ARGUMENT_3_CONTENT_OFFSET               0
#define MP1_C2PMSG_ARGUMENT_3_CONTENT_WIDTH                32
#define MP1_C2PMSG_ARGUMENT_3_CONTENT_MASK                 0xffffffffUL

/// MP1_C2PMSG_ARGUMENT_3
typedef union {
  struct {                                                             ///<
    UINT32                                                 CONTENT:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} MP1_C2PMSG_ARGUMENT_3_STRUCT;


// Address
#define MP1_C2PMSG_ARGUMENT_4_ADDRESS                      0x3B105a8ul

// Type
#define MP1_C2PMSG_ARGUMENT_4_TYPE                         TYPE_SMN

#define MP1_C2PMSG_ARGUMENT_4_CONTENT_OFFSET               0
#define MP1_C2PMSG_ARGUMENT_4_CONTENT_WIDTH                32
#define MP1_C2PMSG_ARGUMENT_4_CONTENT_MASK                 0xffffffffUL

/// MP1_C2PMSG_ARGUMENT_4
typedef union {
  struct {                                                             ///<
    UINT32                                                 CONTENT:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} MP1_C2PMSG_ARGUMENT_4_STRUCT;


// Address
#define MP1_C2PMSG_ARGUMENT_5_ADDRESS                      0x3B105acul

// Type
#define MP1_C2PMSG_ARGUMENT_5_TYPE                         TYPE_SMN

#define MP1_C2PMSG_ARGUMENT_5_CONTENT_OFFSET               0
#define MP1_C2PMSG_ARGUMENT_5_CONTENT_WIDTH                32
#define MP1_C2PMSG_ARGUMENT_5_CONTENT_MASK                 0xffffffffUL

/// MP1_C2PMSG_ARGUMENT_5
typedef union {
  struct {                                                             ///<
    UINT32                                                 CONTENT:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} MP1_C2PMSG_ARGUMENT_5_STRUCT;

/// SMU hot plug controller flags
#define HP_DISABLE_SIDEBAND            0x01
#define HP_DISABLE_L1_WA               0x02
#define HP_DISABLE_BRIDGE_DIS          0x04
#define HP_DISABLE_IRQ_POLL            0x08
#define HP_DISABLE_IRQ_SET_BRIDGE_DIS  0x10

/// SMU V9 basic lib

VOID
NbioSmuServiceCommonInitArgumentsV9 (
  IN OUT   UINT32                   *SmuArg
  );

UINT32
NbioSmuServiceRequestV9 (
  IN       PCI_ADDR                 NbioPciAddress,
  IN       UINT32                   RequestId,
  IN OUT   UINT32                   *RequestArgument,
  IN       UINT32                   AccessFlags
  );

AGESA_STATUS
NbioSmuFirmwareTestV9 (
  IN       GNB_HANDLE               *NbioHandle
  );

AGESA_STATUS
NbioDxioServiceRequestV9 (
  IN       GNB_HANDLE               *NbioHandle,
  IN       UINT32                   RequestId,
  IN OUT   UINT32                   *RequestArgument,
  IN       UINT32                   AccessFlags
  );

VOID
SmuNotifyS3Entry (
  );

#endif

