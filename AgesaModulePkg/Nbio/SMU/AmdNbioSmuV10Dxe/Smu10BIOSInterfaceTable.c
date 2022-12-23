/* $NoKeywords:$ */
/**
 * @file
 *
 * Family specific SMU 10 Bios Interface Table
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 312288 $   @e \$Date: 2016-12-22 00:39:01 -0600 (Thu, 22 Dec 2016) $
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
#include <smu10_bios_if.h>
#include <smu10.h>

#define FILECODE  NBIO_SMU_AMDNBIOSMUV10DXE_SMU10BIOSINTERFACETABLE_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
PPTable_t PPTableDefault = {
                             0, //  UINT32 Version;
                             0, //  UINT32 SUSTAINED_POWER_LIMIT;           //Power [mWatts] (STAPM)
                             0, //  UINT32 FAST_PPT_LIMIT;                  //Power [mWatts] (fPPT)
                             0, //  UINT32 SLOW_PPT_LIMIT;                  //Power [mWatts] (sPPT)
                             0, //  UINT32 SLOW_PPT_TIME_CONSTANT;          //Time constant (seconds)
                             0, //  UINT8  SYSTEM_TEMPERATURE_TRACKING;     //Tskin feedback from EC; 1 = enabled; 0 = disabled
                             0, //  UINT8  STAPM_BOOST_OVERRIDE;            //1 = use value in STAPM_BOOST; 0 = use SMU FW default
                             0, //  UINT8  STAPM_BOOST;                     //1 = enabled; 0 = disabled
                             0, //  UINT8  AA_MODE_EN;                      //A+A power/thermal sharing algorithm; 1 = enable; 0 = disable
                             0, //  UINT32 STAPM_TIME_CONSTANT;             //Time constant (seconds)
                             0, //  UINT32 THERMCTL_LIMIT;                  //Tctrl (THM)
                             0, //  UINT32 VRM_CURRENT_LIMIT;               //Current [mA] (VDDCR_VDD TDC)
                             0, //  UINT32 VRM_MAXIMUM_CURRENT_LIMIT;       //Current [mA] (VDDCR_VDD EDC)
                             0, //  UINT32 VRM_SOC_CURRENT_LIMIT;           //Current [mA] (VDDCR_SOC TDC)
                             0, //  UINT32 VRM_SOC_MAXIMUM_CURRENT_LIMIT;   //Current [mA] (VDDCR_SOC EDC)
                             0, //  UINT32 PSI0_CURRENT_LIMIT;              //Current [mA] (VDDCR_VDD PSI0)
                             0, //  UINT32 PSI0_SOC_CURRENT_LIMIT;          //Current [mA] (VDDCR_SOC PSI0)
                             0, //  UINT32 PROCHOT_L_DEASSERTION_RAMP_TIME; //Time [ms] (PROCHOT)
                             0, //  UINT8  SYSTEM_CONFIG;                   //0 = use fused default; >0 = user specified value
                             0, //  UINT8  itemp
                             0, //  uint8_t  Voltage_SlewRate;                //Only used in conjunction with WaitVidCompDis = 1
                             0,//  UINT8  spare;
                             0,//  UINT8 FanTable_Override;     //[1 means use the full set of data specified below; 0 means use default fan table]
                             0,//  UINT8 FanTable_Hysteresis;
                             0,//  UINT8 FanTable_TempLow;
                             0,//  UINT8 FanTable_TempMed;
                             0,//  UINT8 FanTable_TempHigh;
                             0,//  UINT8 FanTable_TempCritical;
                             0,//  UINT8 FanTable_PwmLow;
                             0,//  UINT8 FanTable_PwmMed;
                             0,//  UINT8 FanTable_PwmHigh;
                             0,//  UINT8 FanTable_PwmFreq;      //[0 = 25kHz; 1 = 100Hz]
                             0,//  UINT8 FanTable_Polarity;     //[0 = negative; 1 = positive]
                             0,//  UINT8 FanTable_spare;
                             0,//  UINT8  CoreDldoPsmMargin;       //[PSM count 1 ~ 1.8mV]
                             5,//  UINT8  GfxDldoPsmMargin;        //[PSM count 1 ~ 1.8mV]
                             0,//  UINT8  ForceFanPwmEn;           //[1 means use the ForceFanPwm value below]
                             0,//  UINT8  ForceFanPwm;             //[% 0-100]
                             0,//  UINT8  CoreStretchThreshEn;     //[1 means use the CoreStretchThresh value below]
                             0,//  UINT8  CoreStretchThresh;       //[1 = 2.5%]
                             0,//  UINT8  L3StretchThreshEn;       //[1 means use the L3StretchThresh value below]
                             0,//  UINT8  L3StretchThresh;         //[1 = 2.5%]
                             0,//  UINT8  GfxStretchThreshEn;      //[1 means use the GfxStretchThresh value below]
                             0,//  UINT8  GfxStretchThresh;        //[1 = 2.5%]
                             0,//  UINT8  GfxStretchAmountEn;
                             0,//  UINT8  GfxStretchAmount;
                             1,//  UINT8  CoreDldoBypass;          //[1 means bypass]
                             0,//  UINT8  GfxDldoBypass;           //[1 means bypass]
                             0,//  UINT8  XiSeparationEn;          //[1 means use the XiSeparation value below]
                             0,//  UINT8  XiSeparationHigh;        //[0 = async mode; 3 = 2 cycle; 4 = 2.5 cycle; 5 = 3 cycle; 6 = 3.5 cycle; 7 = 4 cycle]
                             0,//  UINT8  XiSeparationLow;         //[0 = async mode; 3 = 2 cycle; 4 = 2.5 cycle; 5 = 3 cycle; 6 = 3.5 cycle; 7 = 4 cycle]
                             0,//  UINT8  AvfsCoeffTable_Override; //[1 = override; 0 = use defaults]
                             0,//  uint8  MP2CLK_PwrDn;
                             0,//  UINT8  spare2;
                             0,//  INT32  VddcrVddVoltageMargin;   //[mV]
                             0,//  INT32  VddcrSocVoltageMargin;   //[mV]
                             0,//  UINT16 FcwSlewFrac_L3FidTotalSteps;
                             0,//  UINT8  FcwSlewFrac_L3FidTotalStepsEn;
                             0,//  UINT8  WaitVidCompDis;          //[0 = use VOTF feedback from VR; 1 = use internal timer]
                             1,//  UINT8  UseCcxFreqCurveFuses;
                             1,//  UINT8  UseGfxFreqCurveFuses;
                             1,//  UINT8  UseCacSiddFuses;
                             0,//  UINT8  ApplyRichtekVrmPsi0Workaround;
                               //CBS debug options [AVFS coeffients - signed values]
                             0,//  INT32 CorePsfFreq2;
                             0,//  INT32 CorePsfFreq;
                             0,//  INT32 CorePsfGfxActive;
                             0,//  INT32 CorePsfTemp;
                             0,//  INT32 CorePsfSidd;
                             0,//  INT32 CorePsfCac;
                             0,//  INT32 CorePsfNumActiveCores;
                             0,//  INT32 CorePsfSigma;
                             0,//  INT32 CorePsfAcBtc;
                             0,//  INT32 L3PsfFreq2;
                             0,//  INT32 L3PsfFreq;
                             0,//  INT32 L3PsfGfxActive;
                             0,//  INT32 L3PsfTemp;
                             0,//  INT32 L3PsfSidd;
                             0,//  INT32 L3PsfCac;
                             0,//  INT32 L3PsfNumActiveCores;
                             0,//  INT32 L3PsfSigma;
                             0,//  INT32 L3PsfAcBtc;
                             0,//  INT32 GfxPsfFreq2;
                             0,//  INT32 GfxPsfFreq;
                             0,//  INT32 GfxPsfGfxActive;
                             0,//  INT32 GfxPsfTemp;
                             0,//  INT32 GfxPsfSidd;
                             0,//  INT32 GfxPsfCac;
                             0,//  INT32 GfxPsfNumActiveCores;
                             0,//  INT32 GfxPsfSigma;
                             0,//  INT32 GfxPsfAcBtc;
                             0,//  UINT32 Telemetry_VddcrVddSlope;
                             0,//  UINT32 Telemetry_VddcrVddOffset;
                             0,//  UINT32 Telemetry_VddcrSocSlope;
                             0,//  UINT32 Telemetry_VddcrSocOffset;
                             // LIVmin Entry voltage
                             0,//  uint8  LivMinEntryVID;
                             {0,0,0}, //  spare3[3]   placeholder for RV2 LIVmin Entry voltage
                             0,//  uint32_t Telemetry_VddcrVddSlope2;
                             0,//  uint32_t Telemetry_VddcrVddSlope3;
                             0,//  uint32_t Telemetry_VddcrVddSlope4;
                             0,//  uint32_t Telemetry_VddcrVddSlope5;
                             0,//  uint32_t MinS0i3SleepTimeInMs;
                             0,//  uint32_t STT_MinLimit; // Power [mWatts]
                             0,//  uint8_t  CalculateIOPhyDataDis;
                             0,//  uint8_t  FmaxTempThreshold;
                             0,//  uint16_t FmaxTempFrequency;
                             {0,0}, //uint8_t  UsbPortsToClearWceWde[2]
                             0,//  uint8_t  minSocVidOffset
                             0,//  uint8_t  AclkDpm0Freq400MHz;
                             {0}, // uint16_t  ForceVddcrVddVoltage //[mV; 0 means no force]
                             {0}, // uint16_t  ForceVddcrSocVoltage //[mV; 0 means no force]
                             {0}, // uint32_t WLAN; //[31:24]Offset,[23:16]PcieBus,[15:8]PcieDevice,[7:0]PcieFunction
                             0, //  uint8_t spare7;          //Reserved for Set_LPCRST
                             0, //  uint8_t SparseControlDisable; //Default=0
                             {0, 0}, //  uint8_t spare8[2];       //placeholder
                             {0,0,0,0,0,0,0,0,0} //  uint32_t  spare9[9];
};


