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
* Copyright 2008 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
*
* AMD is granting You permission to use this software and documentation (if
* any) (collectively, the "Software") pursuant to the terms and conditions of
* the Software License Agreement included with the Software. If You do not have
* a copy of the Software License Agreement, contact Your AMD representative for
* a copy.
*
* You agree that You will not reverse engineer or decompile the Software, in
* whole or in part, except as allowed by applicable law.
*
* WARRANTY DISCLAIMER: THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND. AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
* BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, QUALITY,
* FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT AND WARRANTIES
* ARISING FROM CUSTOM OF TRADE OR COURSE OF USAGE WITH RESPECT TO THE SOFTWARE,
* INCLUDING WITHOUT LIMITATION, THAT THE SOFTWARE WILL RUN UNINTERRUPTED OR
* ERROR-FREE. THE ENTIRE RISK ASSOCIATED WITH THE USE OF THE SOFTWARE IS
* ASSUMED BY YOU. Some jurisdictions do not allow the exclusion of implied
* warranties, so the above exclusion may not apply to You, but only to the
* extent required by law.
*
* LIMITATION OF LIABILITY AND INDEMNIFICATION: TO THE EXTENT NOT PROHIBITED BY
* APPLICABLE LAW, AMD AND ITS LICENSORS WILL NOT, UNDER ANY CIRCUMSTANCES BE
* LIABLE TO YOU FOR ANY PUNITIVE, DIRECT, INCIDENTAL, INDIRECT, SPECIAL OR
* CONSEQUENTIAL DAMAGES ARISING FROM POSSESSION OR USE OF THE SOFTWARE OR
* OTHERWISE IN CONNECTION WITH ANY PROVISION OF THIS AGREEMENT EVEN IF AMD AND
* ITS LICENSORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. THIS
* INCLUDES, WITHOUT LIMITATION, DAMAGES DUE TO LOST OR MISAPPROPRIATED DATA,
* LOST PROFITS OR CONFIDENTIAL OR OTHER INFORMATION, FOR BUSINESS INTERRUPTION,
* FOR PERSONAL INJURY, FOR LOSS OF PRIVACY, FOR FAILURE TO MEET ANY DUTY
* INCLUDING OF GOOD FAITH OR REASONABLE CARE, FOR NEGLIGENCE AND FOR ANY OTHER
* PECUNIARY OR OTHER LOSS WHTSOEVER. In no event shall AMD's total liability to
* You for all damages, losses, and causes of action (whether in contract, tort
* (including negligence) or otherwise) exceed the amount of $50 USD. You agree
* to defend, indemnify and hold harmless AMD, its subsidiaries and affiliates
* and their respective licensors, directors, officers, employees, affiliates or
* agents from and against any and all loss, damage, liability and other
* expenses (including reasonable attorneys' fees), resulting from Your
* possession or use of the Software or violation of the terms and conditions of
* this Agreement.
*
* U.S. GOVERNMENT RESTRICTED RIGHTS: Notice to U.S. Government End Users. The
* Software and related documentation are "commercial items", as that term is
* defined at 48 C.F.R. Section 2.101, consisting of "commercial computer
* software" and "commercial computer software documentation", as such terms are
* used in 48 C.F.R. Section 12.212 and 48 C.F.R. Section 227.7202,
* respectively. Consistent with 48 C.F.R. Section 12.212 or 48 C.F.R. Sections
* 227.7202-1 through 227.7202-4, as applicable, the commercial computer
* software and commercial computer software documentation are being licensed to
* U.S. Government end users: (a) only as commercial items, and (b) with only
* those rights as are granted to all other end users pursuant to the terms and
* conditions set forth in this Agreement. Unpublished rights are reserved under
* the copyright laws of the United States.
*
* EXPORT RESTRICTIONS:  You shall adhere to all applicable U.S. import/export
* laws and regulations, as well as the import/export control laws and
* regulations of other countries as applicable. You further agree You will not
* export, re-export, or transfer, directly or indirectly, any product,
* technical data, software or source code received from AMD under this license,
* or the direct product of such technical data or software to any country for
* which the United States or any other applicable government requires an export
* license or other governmental approval without first obtaining such licenses
* or approvals, or in violation of any applicable laws or regulations of the
* United States or the country where the technical data or software was
* obtained. You acknowledges the technical data and software received will not,
* in the absence of authorization from U.S. or local law and regulations as
* applicable, be used by or exported, re-exported or transferred to: (i) any
* sanctioned or embargoed country, or to nationals or residents of such
* countries; (ii) any restricted end-user as identified on any applicable
* government end-user list; or (iii) any party where the end-use involves
* nuclear, chemical/biological weapons, rocket systems, or unmanned air
* vehicles.  For the most current Country Group listings, or for additional
* information about the EAR or Your obligations under those regulations, please
* refer to the website of the U.S. Bureau of Industry and Security at
* http://www.bis.doc.gov/.
*******************************************************************************
*
*/
#ifndef _NBIOSMUV10LIB_H_
#define _NBIOSMUV10LIB_H_

#include <NbioRegisterTypes.h>

#define VDDOFF_VID_FP5 0xF8   //0xB8
#define VDDOFF_VID_AM4 0xFF

// SMU Response Codes:
#define BIOSSMC_Result_OK                    0x1  // The operations was successful.
#define BIOSSMC_Result_Failed                0xFF
#define BIOSSMC_Result_UnknownCmd            0xFE
#define BIOSSMC_Result_CmdRejectedPrereq     0xFD
#define BIOSSMC_Result_CmdRejectedBusy       0xFC

// Message Definitions:
#define SMC_MSG_TestMessage                   0x1
#define SMC_MSG_GetSmuVersion                 0x2
#define SMC_MSG_GetBiosIfVersion              0x3
#define BIOSSMC_MSG_GetNameString             0x4
#define SMC_MSG_EnableSmuFeatures             0x5
#define SMC_MSG_DisableSmuFeatures            0x6
#define SMC_MSG_DramLogSetDramAddrHigh        0x7
#define SMC_MSG_DramLogSetDramAddrLow         0x8
#define SMC_MSG_DramLogSetDramSize            0x9
#define SMC_MSG_DxioTestMessage               0xA
#define SMC_MSG_ReadCoreCacWeightRegister     0xB
#define SMC_MSG_SleepEntry                    0xC
#define SMC_MSG_SetGbeStatus                  0xD
#define SMC_MSG_PowerUpGfx                    0xE
#define SMC_MSG_PowerUpSata                   0xF
#define SMC_MSG_PowerDownSata                 0x10
#define SMC_MSG_DisableSataController         0x11
#define SMC_MSG_SetBiosDramAddrHigh           0x12
#define SMC_MSG_SetBiosDramAddrLow            0x13
#define SMC_MSG_SetToolsDramAddrHigh          0x14
#define SMC_MSG_SetToolsDramAddrLow           0x15
#define SMC_MSG_TransferTableSmu2Dram         0x16 //! RS
#define SMC_MSG_TransferTableDram2Smu         0x17 //! RS
#define SMC_MSG_PowerSourceAC                 0x18
#define SMC_MSG_PowerSourceDC                 0x19
#define SMC_MSG_SetSustainedPowerLimit        0x1A
#define SMC_MSG_SetFastPPTLimit               0x1B
#define SMC_MSG_SetSlowPPTLimit               0x1C
#define SMC_MSG_SetSlowPPTTimeConstant        0x1D
#define SMC_MSG_SetStapmTimeConstant          0x1E
#define SMC_MSG_SetTctlMax                    0x1F
#define SMC_MSG_SetVrmCurrentLimit            0x20
#define SMC_MSG_SetVrmSocCurrentLimit         0x21
#define SMC_MSG_SetVrmMaximumCurrentLimit     0x22
#define SMC_MSG_SetVrmSocMaximumCurrentLimit  0x23
#define SMC_MSG_SetPSI0CurrentLimit           0x24
#define SMC_MSG_SetPSI0SocCurrentLimit        0x25
#define SMC_MSG_SetProchotDeassertionRampTime 0x26
#define SMC_MSG_UpdateSkinTempError           0x27
#define SMC_MSG_SetGpuApertureLow             0x28
#define SMC_MSG_SetGpuApertureHigh            0x29
#define SMC_MSG_StartGpuLink                  0x2A
#define SMC_MSG_StopGpuLink                   0x2B
#define SMC_MSG_UsbD3Entry                    0x2C
#define SMC_MSG_UsbD3Exit                     0x2D
#define SMC_MSG_UsbInit                       0x2E
#define SMC_MSG_AcBtcStartCal                 0x2F
#define SMC_MSG_AcBtcStopCal                  0x30
#define SMC_MSG_AcBtcEndCal                   0x31
#define SMC_MSG_DcBtc                         0x32
#define SMC_MSG_BtcRestoreOnS3Resume          0x33
#define SMC_MSG_SetGpuDeviceId                0x34
#define SMC_MSG_SetUlvVidOffset               0x35
#define SMC_MSG_DisablePSI                    0x36
#define SMC_MSG_EnablePostCode                0x37
#define SMC_MSG_UsbConfigUpdate               0x38
#define SMC_MSG_SetupUSB31ControllerTrap      0x39
#define SMC_MSG_SetVddOffVid                  0x3A
#define SMC_MSG_SetVminFrequency              0x3B
#define SMC_MSG_SetFrequencyMax               0x3C
#define SMC_MSG_SetGfxclkOverdriveByFreqVid   0x3D // AM4 only, check fuse, turn on OD and sets SoftMin GFXCLK, disables infra limits, prochot remains on, not limited by FMax set by fuses. Vid is limited by fused vid
#define SMC_MSG_PowerGateXgbe                 0x3E
#define SMC_MSG_OC_Disable                    0x3F
#define SMC_MSG_OC_VoltageMax                 0x40 //mV
#define SMC_MSG_OC_FrequencyMax               0x41 //MHz
#define SMC_MSG_EnableCC6Filter               0x42
#define SMC_MSG_GetSustainedPowerAndThmLimit  0x43
#define SMC_MSG_SetSoftMaxCCLK                0x44
#define SMC_MSG_SetSoftMinCCLK                0x45
#define SMC_MSG_SetSoftMaxGfxClk              0x46
#define SMC_MSG_SetSoftMinGfxClk              0x47
#define SMC_MSG_SetSoftMaxSocclkByFreq        0x48
#define SMC_MSG_SetSoftMinSocclkByFreq        0x49
#define SMC_MSG_SetSoftMaxFclkByFreq          0x4A
#define SMC_MSG_SetSoftMinFclkByFreq          0x4B
#define SMC_MSG_SetSoftMaxVcn                 0x4C
#define SMC_MSG_SetSoftMinVcn                 0x4D
#define SMC_MSG_SetSoftMaxLclk                0x4E
#define SMC_MSG_SetSoftMinLclk                0x4F
#define SMC_MSG_UsbXhciControllerDisabled     0x50
#define SMC_MSG_GetOpnSpareFuse               0x51
#define SMC_MSG_SetExternalPcieBuses          0x52
#define SMC_MSG_PowerDownGfx                  0x53
#define SMC_MSG_SetSlowPPTLimitApuOnly        0x54
#define SMC_MSG_GetCorePerfOrder              0x55
#define SMC_MSG_SetGenericPeRstGpioAddrOffset 0x56
#define SMC_MSG_SetFitLimitScalar             0x57
#define SMC_MSG_EnableOverclocking            0x58
#define SMC_MSG_SetOverclockCclkFreqAllCores  0x59
#define SMC_MSG_SetOverclockCclkFreqPerCore   0x5A
#define SMC_MSG_SetOverclockVID               0x5B
#define SMC_MSG_GetOverclockCap               0x5C
#define SMC_MSG_SetApmlHighTempThreshold      0x5D
#define SMC_MSG_SetupNvmeTrap                 0x5E
#define SMC_MSG_GetNumNvmeTrap                0x5F
#define SMC_MSG_Spared                        0x60
#define SMC_Message_Count                     0x61
#define INVALID_SMU_MSG                       0xFF

#define SMC_MSG_DXIO_SERVICE    SMC_MSG_DxioTestMessage
#define SMC_MSG_S3Entry         SMC_MSG_SleepEntry
typedef struct {
  UINT32 Function : 3;
  UINT32 Device : 5;
  UINT32 Bus : 8;
  UINT32 Spare : 16;
} BIOSSMC_MSG_SetupNvmeTrap_t;
typedef union {
  UINT32 val;
  BIOSSMC_MSG_SetupNvmeTrap_t f;
} BIOSSMC_MSG_SetupNvmeTrap_u;
typedef struct {
  UINT8 NvmeTrapsRemaining;
  UINT8 NvmeTrapsUsed;
  UINT8 NvmeTrapsTotal;
  UINT8 Spare;
} BIOSSMC_MSG_GetNumNvmeTrap_t;
typedef union {
  UINT32 val;
  BIOSSMC_MSG_GetNumNvmeTrap_t f;
} BIOSSMC_MSG_GetNumNvmeTrap_u;


// Address
#define MP1_C2PMSG_MESSAGE_ADDRESS                         0x3B10528UL

// Type
#define MP1_C2PMSG_MESSAGE_TYPE                            TYPE_SMN

#define MP1_C2PMSG_MESSAGE_CONTENT_OFFSET                  0
#define MP1_C2PMSG_MESSAGE_CONTENT_WIDTH                   32
#define MP1_C2PMSG_MESSAGE_CONTENT_MASK                    0xffffffffL

/// MP1_C2PMSG_MESSAGE
typedef union {
  struct {                                                             ///<
    UINT32                                                 CONTENT:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} MP1_C2PMSG_MESSAGE_STRUCT;

// Address
#define MP1_C2PMSG_RESPONSE_ADDRESS                        0x3B10564UL

// Type
#define MP1_C2PMSG_RESPONSE_TYPE                           TYPE_SMN

#define MP1_C2PMSG_RESPONSE_CONTENT_OFFSET                 0
#define MP1_C2PMSG_RESPONSE_CONTENT_WIDTH                  32
#define MP1_C2PMSG_RESPONSE_CONTENT_MASK                   0xffffffffL

/// MP1_C2PMSG_RESPONSE
typedef union {
  struct {                                                             ///<
    UINT32                                                 CONTENT:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} MP1_C2PMSG_RESPONSE_STRUCT;


// Address
#define MP1_C2PMSG_ARGUMENT_0_ADDRESS                      0x3B10998UL

// Type
#define MP1_C2PMSG_ARGUMENT_0_TYPE                         TYPE_SMN

#define MP1_C2PMSG_ARGUMENT_0_CONTENT_OFFSET               0
#define MP1_C2PMSG_ARGUMENT_0_CONTENT_WIDTH                32
#define MP1_C2PMSG_ARGUMENT_0_CONTENT_MASK                 0xffffffffL

/// MP1_C2PMSG_ARGUMENT_0
typedef union {
  struct {                                                             ///<
    UINT32                                                 CONTENT:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} MP1_C2PMSG_ARGUMENT_0_STRUCT;


// Address
#define MP1_C2PMSG_ARGUMENT_1_ADDRESS                      0x3B1099CUL

// Type
#define MP1_C2PMSG_ARGUMENT_1_TYPE                         TYPE_SMN

#define MP1_C2PMSG_ARGUMENT_1_CONTENT_OFFSET               0
#define MP1_C2PMSG_ARGUMENT_1_CONTENT_WIDTH                32
#define MP1_C2PMSG_ARGUMENT_1_CONTENT_MASK                 0xffffffffL

/// MP1_C2PMSG_ARGUMENT_1
typedef union {
  struct {                                                             ///<
    UINT32                                                 CONTENT:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} MP1_C2PMSG_ARGUMENT_1_STRUCT;


// Address
#define MP1_C2PMSG_ARGUMENT_2_ADDRESS                      0x3B109A0UL

// Type
#define MP1_C2PMSG_ARGUMENT_2_TYPE                         TYPE_SMN

#define MP1_C2PMSG_ARGUMENT_2_CONTENT_OFFSET               0
#define MP1_C2PMSG_ARGUMENT_2_CONTENT_WIDTH                32
#define MP1_C2PMSG_ARGUMENT_2_CONTENT_MASK                 0xffffffffL

/// MP1_C2PMSG_ARGUMENT_2
typedef union {
  struct {                                                             ///<
    UINT32                                                 CONTENT:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} MP1_C2PMSG_ARGUMENT_2_STRUCT;


// Address
#define MP1_C2PMSG_ARGUMENT_3_ADDRESS                      0x3B109A4UL

// Type
#define MP1_C2PMSG_ARGUMENT_3_TYPE                         TYPE_SMN

#define MP1_C2PMSG_ARGUMENT_3_CONTENT_OFFSET               0
#define MP1_C2PMSG_ARGUMENT_3_CONTENT_WIDTH                32
#define MP1_C2PMSG_ARGUMENT_3_CONTENT_MASK                 0xffffffffL

/// MP1_C2PMSG_ARGUMENT_3
typedef union {
  struct {                                                             ///<
    UINT32                                                 CONTENT:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} MP1_C2PMSG_ARGUMENT_3_STRUCT;


// Address
#define MP1_C2PMSG_ARGUMENT_4_ADDRESS                      0x3B109a8UL

// Type
#define MP1_C2PMSG_ARGUMENT_4_TYPE                         TYPE_SMN

#define MP1_C2PMSG_ARGUMENT_4_CONTENT_OFFSET               0
#define MP1_C2PMSG_ARGUMENT_4_CONTENT_WIDTH                32
#define MP1_C2PMSG_ARGUMENT_4_CONTENT_MASK                 0xffffffffL

/// MP1_C2PMSG_ARGUMENT_4
typedef union {
  struct {                                                             ///<
    UINT32                                                 CONTENT:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} MP1_C2PMSG_ARGUMENT_4_STRUCT;


// Address
#define MP1_C2PMSG_ARGUMENT_5_ADDRESS                      0x3B109ACUL

// Type
#define MP1_C2PMSG_ARGUMENT_5_TYPE                         TYPE_SMN

#define MP1_C2PMSG_ARGUMENT_5_CONTENT_OFFSET               0
#define MP1_C2PMSG_ARGUMENT_5_CONTENT_WIDTH                32
#define MP1_C2PMSG_ARGUMENT_5_CONTENT_MASK                 0xffffffffL

/// MP1_C2PMSG_ARGUMENT_5
typedef union {
  struct {                                                             ///<
    UINT32                                                 CONTENT:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} MP1_C2PMSG_ARGUMENT_5_STRUCT;


/// SMU V10 basic lib

VOID
NbioSmuServiceCommonInitArgumentsV10 (
  IN OUT   UINT32                   *SmuArg
  );

UINT32
NbioSmuServiceRequestV10 (
  IN       PCI_ADDR                 NbioPciAddress,
  IN       UINT32                   RequestId,
  IN OUT   UINT32                   *RequestArgument,
  IN       UINT32                   AccessFlags
  );

AGESA_STATUS
NbioSmuFirmwareTestV10 (
  IN       GNB_HANDLE               *NbioHandle
  );

UINT32
NbioDxioServiceRequestV10 (
  IN       GNB_HANDLE               *NbioHandle,
  IN       UINT32                   DxioMBoxRequest,
  IN  OUT  UINT32                   *DxioMBoxArg,
  IN       UINT32                   AccessFlags
  );

VOID
SmuNotifyS3Entry (
  );

#endif


