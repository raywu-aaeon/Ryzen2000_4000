/* $NoKeywords:$ */
/**
 * @file
 *
 * Contains the definition of the SMU11
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: Nbio/SMU
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
#ifndef SMU11_BIOS_IF_H
#define SMU11_BIOS_IF_H

//
// Assume standard IA-32 alignment.
// BugBug: Need to check portability of long long
//
typedef unsigned long long  uint64_t;
typedef long long           int64_t;
typedef unsigned int        uint32_t;
typedef int                 int32_t;
typedef unsigned short      uint16_t;
typedef short               int16_t;
typedef unsigned char       uint8_t;
typedef signed char         int8_t;

// *** IMPORTANT ***
// SMU TEAM: Always increment the interface version if
// any structure is changed in this file
#define SMU11_BIOS_IF_VERSION 2

typedef struct {
  //DEFAULT INFRASTRUCTURE LIMITS
  uint32_t TDP;   //Power [W]
  uint32_t PPT;   //Power [W]
  uint32_t TDC;   //Current [A]
  uint32_t EDC;   //Current [A]
  uint32_t TjMax; //Degrees [C]

  //PLATFORM INFRASTRUCTURE LIMITS
  uint32_t TDP_PlatformLimit; //Power [W]
  uint32_t PPT_PlatformLimit; //Power [W]
  uint32_t TDC_PlatformLimit; //Current [A]
  uint32_t EDC_PlatformLimit; //Current [A]

  //FAN TABLE
  uint8_t FanTable_Override;     //[1 means use the data specified below; 0 means use default fan table]
  uint8_t FanTable_Hysteresis;   //['C]
  uint8_t FanTable_TempLow;      //['C]
  uint8_t FanTable_TempMed;      //['C]
  uint8_t FanTable_TempHigh;     //['C]
  uint8_t FanTable_TempCritical; //['C]
  uint8_t FanTable_PwmLow;       //[PWM 0-100]
  uint8_t FanTable_PwmMed;       //[PWM 0-100]
  uint8_t FanTable_PwmHigh;      //[PWM 0-100]
  uint8_t FanTable_PwmFreq;      //[0 = 25kHz; 1 = 100Hz]
  uint8_t FanTable_Polarity;     //[0 = negative; 1 = positive]
  uint8_t FanTable_spare;

  //CBS debug options
  int32_t CoreDldoPsmMargin;           //[PSM count] [signed]
  int32_t VddcrCpuVoltageMargin;       //[mV] [signed]
  int32_t VddcrSocVoltageMargin;       //[mV] [signed]
  uint8_t CC1Dis;                      //[0 = CC1 enabled; 1 = CC1 disabled]
  uint8_t DeterminismPercentageEn;     //[1 means use the value in DeterminismSlider; 0 means use the default value]
  uint8_t DeterminismPercentage;       //[0 means full non-determinism; 100 means full determinism; range 0-100]
  uint8_t CCX_VdciAsync;               //[0 = predictive mode; 1 = async mode]
  uint8_t APBDIS;                      //[0 = not APBDIS; 1 = APBDIS]
  uint8_t EfficiencyModeEn;            //[0 = don't enable efficiency mode; 1 = enable efficiency mode]
  uint8_t PowerManagementModeOverride; //[0 = use fused MP1_PowerManagementMode; 1 = use PowerManagementMode specified in this table]
  uint8_t PowerManagementMode;         //[0 = Telemetry; 1 = Per Part Calculations; 2 = Force 100% determinism; 3 = Default 100% Determinism; 4 = Default 0% Determinism]
  uint8_t PcieEsmMode[4];              //Per-NBIO_QUADRANT [0 = non-ESM; 1 = ESM]

  //DF CSTATE CONFIG
  uint8_t DfCstateConfigOverride;
  uint8_t DfCstateClkPwrDnEn;
  uint8_t DfCstateSelfRefrEn;
  uint8_t DfCstateGmiPwrDnEn;
  uint8_t DfCstateGopPwrDnEn;
  uint8_t DfCstateSpare[3];

  //xGMI CONFIGURATION
  uint8_t xGMIMaxLinkWidthEn;
  uint8_t xGMIMaxLinkWidth;
  uint8_t xGMIForceLinkWidthEn;
  uint8_t xGMIForceLinkWidth;

  //TELEMETRY CALIBRATION
  uint32_t Telemetry_VddcrCpu_FullScaleCurrent; //[A] [unsigned]
  int32_t  Telemetry_VddcrCpu_Offset;           //[A] [signed]
  uint32_t Telemetry_VddcrSoc_FullScaleCurrent; //[A] [unsigned]
  int32_t  Telemetry_VddcrSoc_Offset;           //[A] [signed]

  //PRECISE AND DIRECT OVERCLOCKING CONFIG
  uint8_t  OC_DISABLE; //1=disable overclocking; 0=allow overclocking
  uint8_t  OC_MINVID;  //[VID] SVI2 VID encoding
  uint16_t OC_FREQMAX; //MHz

  //CCLK FREQUENCY FORCE
  uint16_t ForceCclkFrequency;   //[MHz; 0 means no force]
  uint16_t FmaxOverride;         //[MHz; 0 means no override]
  uint8_t  APBDIS_DfPstate;      //[DfPstate index to set when APBDIS=1]
  uint8_t  spare[3];

  //CPPC DEFAULT SETTINGS (only used when CPPC is not enabled)
  uint8_t  CPPC_Override;                    //Use the 3 values defined below
  uint8_t  CPPC_EnergyPerformancePreference; //Default EPP value to use when CPPC is disabled [0-100]
  uint8_t  CPPC_MaxPerfLimit;                //Default MaxPerfLimit to use when CPPC is disabled [0-100]
  uint8_t  CPPC_MinPerfLimit;                //Default MinPerfLimit to use when CPPC is disabled [0-100]

  //CPPC APICID MAPPING
  uint8_t  LogicalThreadToApicidSize;
  uint8_t  spare4[3];
  uint16_t LogicalThreadToApicid[256]; //256 is the maximum number of threads on a 2P system
} PPTable_t;

typedef struct {
  //PCIe LANE MAPPING [NBIO_QUADRANT][PCIe_CORE][DEVICE]
  uint8_t PCIe_GenSpeed[4][2][8];    //0=NOT_CONNECTED; 1=GEN1; 2=GEN2; 3=GEN3; 4=GEN4; 5=GEN4+(ESM)
  uint8_t PCIe_LaneWidth[4][2][8];   //LANE_WIDTH [0=NOT_CONNECTED; 1=x1; 2=x2; 4=x4; 8=x8; 16=x16]
} PcieLaneMappingTable_t;

// PCIE hotplug structures
#define MAX_HOTPLUG_PCIE_PORTS 96

// NBIO_TODO : Below here there are lots of unmerged hotplug structs. Need to remember to update when we update the hotplug code.
typedef struct {
  uint32_t HotPlugFormat              :   3;
  uint32_t NewStructureFormat         :   1;  // bit indcating the new structure format for backward compatibility.  Should be 0 of version 1
  uint32_t GpioDescriptorValid        :   1;
  uint32_t ResetDescriptorValid       :   1;
  uint32_t PortActive                 :   1;
  uint32_t MasterSlaveAPU             :   1;
  uint32_t DieID                      :   4;
  uint32_t ApertureID                 :  12;
  uint32_t AltSlotNum                 :   6;
  uint32_t SecondaryLink              :   1;
  uint32_t Reserved1                  :   1;
} PcieHotPlugMappingDescriptor_t;

typedef struct {
  uint32_t HotPlugFormat              :   3;
  uint32_t NewStructureFormat         :   1;  // bit indcating the new structure format for backward compatibility.  Should be 1 of version 2
  uint32_t GpioDescriptorValid        :   1;
  uint32_t ResetDescriptorValid       :   1;
  uint32_t PortActive                 :   1;
  uint32_t MasterSlaveAPU             :   1;
  uint32_t DieID                      :   4;
  uint32_t PciePortInstance           :   3;
  uint32_t PcieTileInstance           :   1;
  uint32_t Reserved                   :   8;
  uint32_t AltSlotNum                 :   6;
  uint32_t SecondaryLink              :   1;
  uint32_t Reserved1                  :   1;
} PcieHotPlugMappingDescriptorV2_t;

typedef struct {
  uint32_t i2c_bit_or_nibble_select   :   3;  // bit [2] is used for nibble select and bits [2:0] are used for bit select
  uint32_t i2c_byte_select            :   3;
  uint32_t i2c_device_address_ext     :   2;  // reserved bits [7:6] are used to as high bits to enhance the device address from 3 bits to 5 bits
  uint32_t i2c_device_address         :   3;
  uint32_t i2c_device_type            :   2;
  uint32_t i2c_bus_segment            :   3;
  uint32_t function_mask              :   8;
  uint32_t pcie_port_mapping_offset   :   5;
  uint32_t reserved                   :   1;
  uint32_t i2c_bus_segment_ext        :   2;
} PcieHotPlugFunctionDescriptor_t;

typedef struct {
  uint32_t reserved                   :   3;
  uint32_t i2c_byte_select            :   3;
  uint32_t i2c_device_address_ext     :   2;  // reserved bits [7:6] are used to as high bits to enhance the device address from 3 bits to 5 bits
  uint32_t i2c_device_address         :   3;
  uint32_t i2c_device_type            :   2;
  uint32_t i2c_bus_segment            :   3;
  uint32_t reset_select               :   8;
  uint32_t reserved1                  :   6;
  uint32_t i2c_bus_segment_ext        :   2;
} PcieHotPlugResetDescriptor_t;

typedef struct {
  uint32_t reserved                   :   3;
  uint32_t i2c_byte_select            :   3;
  uint32_t i2c_device_address_ext     :   2;  // reserved bits [7:6] are used to as high bits to enhance the device address from 3 bits to 5 bits
  uint32_t i2c_device_address         :   3;
  uint32_t i2c_device_type            :   2;
  uint32_t i2c_bus_segment            :   3;
  uint32_t gpio_select                :   8;
  uint32_t gpio_interrupt_en          :   8;
} SmuGenericGpioDescriptor_t;

typedef struct {
  PcieHotPlugMappingDescriptorV2_t MappingDescriptor   [64];
  PcieHotPlugFunctionDescriptor_t FunctionDescriptor  [64];
  PcieHotPlugResetDescriptor_t    ResetDescriptor     [64];
  SmuGenericGpioDescriptor_t      GpioDescriptor      [64];
} PcieHotPlugConfigTable_t;

// BIOS-SMU SCI structures
typedef struct {
  uint32_t EventGroupValid            :   1;
  uint32_t EventGroupQueueStatus      :   1;
  uint32_t Reserved_0                 :   5;
  uint32_t EventGroupClass            :   1;
  uint32_t HotPlugSlotOrGpioByte      :   6;
  uint32_t Reserved_1                 :  18;
} GpioIntrStatus_t;

typedef union {
  uint32_t val;
  GpioIntrStatus_t f;
} GpioIntrStatus_u;

typedef struct {
  uint32_t EventGroupServiced         :   1;
  uint32_t ServiceRoutineExit         :   1;
  uint32_t Reserved_0                 :  14;
  uint32_t RearmDelay                 :   8;
  uint32_t Reserved_1                 :   8;
} GpioIntrCommand_t;

typedef union {
  uint32_t val;
  GpioIntrCommand_t f;
} GpioIntrCommand_u;

typedef struct {
  uint32_t version;

  PPTable_t                PPTable;
  PcieHotPlugConfigTable_t PcieHotPlugConfigTable;

} SMU11BiosInterfaceTable_t;

#endif

