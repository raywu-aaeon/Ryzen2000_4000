/* $NoKeywords:$ */
/**
 * @file
 *
 * JedecNvdimmDsm.h
 * 
 * 
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  JedecNvdimm
 * @e \$Revision$   @e \$Date$
 *
 */
/*
 ******************************************************************************
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
 */

/** @file JedecNvdimmDsm.h
    Header file for JedecNvdimmDsm Driver

**/

#ifndef _JEDEC_NVDIMM_DSM_H_
#define _JEDEC_NVDIMM_DSM_H_

#define FIRMWARE_DATA_LENGTH    32
#define READ_TYPED_DATA_LENGTH  32

// DSM Method Output
#define DSM_SUCCESS                     0
#define DSM_NOT_SUPPORTED               1
#define DSM_INVALID_INPUT_PARAMETERS    2
#define DSM_I2C_COMMUNICATION_ERROR     3
#define DSM_FUNCTION_ERROR_CODE         4
#define DSM_VENDOR_ERROR_CODE           5

//
// Page 0 Registers
//
#define PAGE0_OPEN_PAGE                         0x00
#define PAGE0_STD_NUM_PAGES                     0x01
#define PAGE0_VENDOR_START_PAGES                0x02
#define PAGE0_VENDOR_NUM_PAGES                  0x03
#define PAGE0_HWREV                             0x04
#define PAGE0_SPECREV                           0x06
#define PAGE0_SLOT0_FWREV0                      0x07
#define PAGE0_SLOT0_FWREV1                      0x08
#define PAGE0_SLOT1_FWREV0                      0x09
#define PAGE0_SLOT1_FWREV1                      0x0A
#define PAGE0_CAPABILITIES                      0x10
#define PAGE0_ENERGY_SOURCE_POLICY              0x14
#define PAGE0_HOST_MAX_OPERATION_RETRY          0x15
#define PAGE0_CSAVE_TRIGGER_SUPPORT             0x16
#define PAGE0_EVENT_NOTIFICATION_SUPPORT        0x17
#define PAGE0_CSAVE_TIMEOUT0                    0x18
#define PAGE0_CSAVE_TIMEOUT1                    0x19
#define PAGE0_PAGE_SWITCH_LATENCY0              0x1A
#define PAGE0_PAGE_SWITCH_LATENCY1              0x1B
#define PAGE0_RESTORE_TIMEOUT0                  0x1C
#define PAGE0_RESTORE_TIMEOUT1                  0x1D
#define PAGE0_ERASE_TIMEOUT0                    0x1E
#define PAGE0_ERASE_TIMEOUT1                    0x1F
#define PAGE0_ARM_TIMEOUT0                      0x20
#define PAGE0_ARM_TIMEOUT1                      0x21
#define PAGE0_FIRMWARE_OPS_TIMEOUT0             0x22
#define PAGE0_FIRMWARE_OPS_TIMEOUT1             0x23
#define PAGE0_ABORT_CMD_TIMEOUT                 0x24
#define PAGE0_MIN_OPERATING_TEMP                0x25
#define PAGE0_MAX_OPERATING_TEMP                0x26
#define PAGE0_MAX_RUNTIME_POWER0                0x27
#define PAGE0_MAX_RUNTIME_POWER1                0x28
#define PAGE0_CSAVE_POWER_REQ0                  0x29
#define PAGE0_CSAVE_POWER_REQ1                  0x2A
#define PAGE0_CSAVE_IDLE_POWER_REQ0             0x2B
#define PAGE0_CSAVE_IDLE_POWER_REQ1             0x2C
#define PAGE0_CSAVE_MIN_VOLT_REQ0               0x2D
#define PAGE0_CSAVE_MIN_VOLT_REQ1               0x2E
#define PAGE0_CSAVE_MAX_VOLT_REQ0               0x2F
#define PAGE0_CSAVE_MAX_VOLT_REQ1               0x30
#define PAGE0_VENDOR_LOG_PAGE_SIZE              0x31
#define PAGE0_REGION_BLOCK_SIZE                 0x32
#define PAGE0_NVDIMM_MGT_CMD0                   0x40
#define PAGE0_NVDIMM_MGT_CMD1                   0x41
#define PAGE0_NVDIMM_FUNC_CMD0                  0x43
#define PAGE0_ARM_CMD                           0x45
#define PAGE0_SET_EVENT_NOTIFICATION_CMD        0x47
#define PAGE0_SET_ES_POLICY_CMD                 0x49
#define PAGE0_FIRMWARE_OPS_CMD                  0x4A
#define PAGE0_NVDIMM_READY                      0x60
#define PAGE0_NVDIMM_CMD_STATUS0                0x61
#define PAGE0_SAVE_STATUS0                      0x64
#define PAGE0_RESTORE_STATUS0                   0x66
#define PAGE0_ERASE_STATUS0                     0x68
#define PAGE0_ARM_STATUS0                       0x6A
#define PAGE0_FACTORY_DEFAULT_STATUS0           0x6C
#define PAGE0_SET_EVENT_NOTIFICATION_STATUS0    0x6E
#define PAGE0_SET_ES_POLICY_STATUS              0x70
#define PAGE0_FIRMWARE_OPS_STATUS               0x71
#define PAGE0_CSAVE_INFO0                       0x80
#define PAGE0_CSAVE_FAIL_INFO0                  0x84
#define PAGE0_CSAVE_FAIL_INFO1                  0x85
#define PAGE0_NVM_LIFETIME_ERROR_THRESHOLD      0x90
#define PAGE0_ES_LIFETIME_ERROR_THRESHOLD       0x91
#define PAGE0_ES_TEMP_ERROR_THRESHOLD           0x92
#define PAGE0_NVM_LIFETIME_WARNING_THRESHOLD    0x98
#define PAGE0_ES_LIFETIME_WARNING_THRESHOLD     0x99
#define PAGE0_ES_TEMP_WARNING_THRESHOLD         0x9A
#define PAGE0_MODULE_HEALTH                     0xA0
#define PAGE0_MODULE_HEALTH_STATUS0             0xA1
#define PAGE0_MODULE_HEALTH_STATUS1             0xA2
#define PAGE0_ERROR_THRESHOLD_STATUS            0xA5
#define PAGE0_WARNING_THRESHOLD_STATUS          0xA7
#define PAGE0_AUTO_ES_HEALTH_FREQUENCY          0xA9
#define PAGE0_MODULE_OPS_CONFIG                 0xAA
#define PAGE0_NVM_LIFETIME                      0xC0

//
// Page 1 Registers
//
#define PAGE1_OPEN_PAGE             0x00
#define PAGE1_ES_HWREV              0x04
#define PAGE1_ES_FWREV0             0x06
#define PAGE1_ES_FWREV1             0x07
#define PAGE1_ES_CHARGE_TIMEOUT0    0x10
#define PAGE1_ES_CHARGE_TIMEOUT1    0x11
#define PAGE1_MIN_ES_OPERATING_TEMP 0x12
#define PAGE1_MAX_ES_OPERATING_TEMP 0x13
#define PAGE1_ES_ATTRIBUTES         0x14
#define PAGE1_ES_TECH               0x15
#define PAGE1_ES_FUNC_CMD0          0x30
#define PAGE1_ES_CMD_STATUS0        0x50
#define PAGE1_ES_LIFETIME           0x70
#define PAGE1_ES_TEMP0              0x71
#define PAGE1_ES_TEMP1              0x72
#define PAGE1_ES_RUNTIME0           0x73
#define PAGE1_ES_RUNTIME1           0x74

//
// Page 2 Registers
//
#define PAGE2_OPEN_PAGE                     0x00
#define PAGE2_LAST_SAVE_DURATION0           0x04
#define PAGE2_LAST_SAVE_DURATION1           0x05
#define PAGE2_LAST_RESTORE_DURATION0        0x06
#define PAGE2_LAST_RESTORE_DURATION1        0x07
#define PAGE2_LAST_ERASE_DURATION0          0x08
#define PAGE2_LAST_ERASE_DURATION1          0x09
#define PAGE2_NUM_SAVE_OPS_COUNT0           0x0A
#define PAGE2_NUM_SAVE_OPS_COUNT1           0x0B
#define PAGE2_NUM_RESTORE_OPS_COUNT0        0x0C
#define PAGE2_NUM_RESTORE_OPS_COUNT1        0x0D
#define PAGE2_NUM_ERASE_OPS_COUNT0          0x0E
#define PAGE2_NUM_ERASE_OPS_COUNT1          0x0F
#define PAGE2_NUM_MODULE_POWER_CYCLES0      0x10
#define PAGE2_NUM_MODULE_POWER_CYCLES1      0x11
#define PAGE2_INJECT_OPS_FAILURES           0x60
#define PAGE2_INJECT_ES_FAILURES            0x64
#define PAGE2_INJECT_FW_FAILURES            0x65
#define PAGE2_INJECT_BAD_BLOCK_CAP          0x67
#define PAGE2_DRAM_ECC_ERROR_COUNT          0x80
#define PAGE2_DRAM_THRESHOLD_ECC_COUNT      0x81
#define PAGE2_HOST_MANAGED_ES_ATTRIBUTES    0x82

//
// Page 3 Registers
//
#define PAGE3_OPEN_PAGE                 0x00
#define PAGE3_TYPED_BLOCK_DATA          0x04
#define PAGE3_REGION_ID0                0x05
#define PAGE3_REGION_ID1                0x06
#define PAGE3_BLOCK_ID                  0x07
#define PAGE3_FW_REGION_CRC0            0x40
#define PAGE3_FW_REGION_CRC1            0x41
#define PAGE3_FW_SLOT_INFO              0x42
#define PAGE3_TYPED_BLOCK_DATA_BYTE0    0x80
#define PAGE3_TYPED_BLOCK_DATA_BYTE1    0x81
#define PAGE3_TYPED_BLOCK_DATA_BYTE2    0x82
#define PAGE3_TYPED_BLOCK_DATA_BYTE3    0x83
#define PAGE3_TYPED_BLOCK_DATA_BYTE4    0x84
#define PAGE3_TYPED_BLOCK_DATA_BYTE5    0x85
#define PAGE3_TYPED_BLOCK_DATA_BYTE6    0x86
#define PAGE3_TYPED_BLOCK_DATA_BYTE7    0x87
#define PAGE3_TYPED_BLOCK_DATA_BYTE8    0x88
#define PAGE3_TYPED_BLOCK_DATA_BYTE9    0x89
#define PAGE3_TYPED_BLOCK_DATA_BYTE10   0x8A
#define PAGE3_TYPED_BLOCK_DATA_BYTE11   0x8B
#define PAGE3_TYPED_BLOCK_DATA_BYTE12   0x8C
#define PAGE3_TYPED_BLOCK_DATA_BYTE13   0x8D
#define PAGE3_TYPED_BLOCK_DATA_BYTE14   0x8E
#define PAGE3_TYPED_BLOCK_DATA_BYTE15   0x8F
#define PAGE3_TYPED_BLOCK_DATA_BYTE16   0x90
#define PAGE3_TYPED_BLOCK_DATA_BYTE17   0x91
#define PAGE3_TYPED_BLOCK_DATA_BYTE18   0x92
#define PAGE3_TYPED_BLOCK_DATA_BYTE19   0x93
#define PAGE3_TYPED_BLOCK_DATA_BYTE20   0x94
#define PAGE3_TYPED_BLOCK_DATA_BYTE21   0x95
#define PAGE3_TYPED_BLOCK_DATA_BYTE22   0x96
#define PAGE3_TYPED_BLOCK_DATA_BYTE23   0x97
#define PAGE3_TYPED_BLOCK_DATA_BYTE24   0x98
#define PAGE3_TYPED_BLOCK_DATA_BYTE25   0x99
#define PAGE3_TYPED_BLOCK_DATA_BYTE26   0x9A
#define PAGE3_TYPED_BLOCK_DATA_BYTE27   0x9B
#define PAGE3_TYPED_BLOCK_DATA_BYTE28   0x9C
#define PAGE3_TYPED_BLOCK_DATA_BYTE29   0x9D
#define PAGE3_TYPED_BLOCK_DATA_BYTE30   0x9E
#define PAGE3_TYPED_BLOCK_DATA_BYTE31   0x9F
#define PAGE3_TYPED_BLOCK_DATA_OFFSET   0xE0

#pragma pack (1)

//
// Get NVDIMM-N Identification (Function Index 1)
//
typedef struct _HARDWARE_REVISION {
    UINT8   Byte0;
    UINT8   Reserved0;
    UINT8   Reserved1;
    UINT8   Reserved2;
} HARDWARE_REVISION;

typedef struct _FIRMWARE_REVISION {
    UINT8   Byte0;
    UINT8   Byte1;
} FIRMWARE_REVISION;

typedef struct _SAVE_OPERATION_TIMEOUT {
    UINT8   Byte0;
    UINT8   Byte1;
    UINT8   Reserved0;
    UINT8   Reserved1;
} SAVE_OPERATION_TIMEOUT;

typedef struct _RESTORE_OPERATION_TIMEOUT {
    UINT8   Byte0;
    UINT8   Byte1;
    UINT8   Reserved0;
    UINT8   Reserved1;
} RESTORE_OPERATION_TIMEOUT;

typedef struct _ERASE_OPERATION_TIMEOUT {
    UINT8   Byte0;
    UINT8   Byte1;
    UINT8   Reserved0;
    UINT8   Reserved1;
} ERASE_OPERATION_TIMEOUT;

typedef struct _ARM_OPERATION_TIMEOUT {
    UINT8   Byte0;
    UINT8   Byte1;
    UINT8   Reserved0;
    UINT8   Reserved1;
} ARM_OPERATION_TIMEOUT;

typedef struct _FIRMWARE_OPERATIONS_TIMEOUT {
    UINT8   Byte0;
    UINT8   Byte1;
    UINT8   Reserved0;
    UINT8   Reserved1;
} FIRMWARE_OPERATIONS_TIMEOUT;

typedef struct _ABORT_OPERATION_TIMEOUT {
    UINT8   Byte0;
    UINT8   Reserved0;
    UINT8   Reserved1;
    UINT8   Reserved2;
} ABORT_OPERATION_TIMEOUT;

typedef struct _NVDIMM_N_IDENTIFICATION {
    UINT32                      Status;
    UINT8                       SpecificationRevision;
    UINT8                       NumberOfStandardPages;
    UINT8                       FirstVendorPage;
    UINT8                       NumberOfVendorPages;
    HARDWARE_REVISION           HardwareRevision;
    FIRMWARE_REVISION           FirmwareRevision;
    UINT8                       CurrentFirmwareSlot;
    UINT8                       FirmwareSlotCount;
    UINT8                       Capabilities;
    UINT8                       SupportedBackupTriggers;
    UINT8                       MaximumOperationRetryCount;
    UINT8                       SupportedNotificationEvents;
    SAVE_OPERATION_TIMEOUT      SaveOperationTimeout;
    RESTORE_OPERATION_TIMEOUT   RestoreOperationTimeout;
    ERASE_OPERATION_TIMEOUT     EraseOperationTimeout;
    ARM_OPERATION_TIMEOUT       ArmOperationTimeout;
    FIRMWARE_OPERATIONS_TIMEOUT FirmwareOperationsTimeout;
    ABORT_OPERATION_TIMEOUT     AbortOperationTimeout;
    UINT8                       MinimumOperatingTemperature;
    UINT8                       MaximumOperationTemperature;
    UINT32                      RegionBlockSize;
} NVDIMM_N_IDENTIFICATION;

//
// Get Save Operation Requirements (Function Index 2)
//
typedef struct _AVERAGE_POWER_REQUIREMENT {
    UINT8   Byte0;
    UINT8   Byte1;
} AVERAGE_POWER_REQUIREMENT;

typedef struct _IDLE_POWER_REQUIREMENT {
    UINT8   Byte0;
    UINT8   Byte1;
} IDLE_POWER_REQUIREMENT;

typedef struct _MINIMUM_VOLTAGE_REQUIREMENT {
    UINT8   Byte0;
    UINT8   Byte1;
} MINIMUM_VOLTAGE_REQUIREMENT;

typedef struct _MAXIMUM_VOLTAGE_REQUIREMENT {
    UINT8   Byte0;
    UINT8   Byte1;
} MAXIMUM_VOLTAGE_REQUIREMENT;

typedef struct _SAVE_OPERATION_REQUIREMENTS {
    UINT32  Status;
    AVERAGE_POWER_REQUIREMENT   AveragePowerRequirement;
    IDLE_POWER_REQUIREMENT      IdlePowerRequirement;
    MINIMUM_VOLTAGE_REQUIREMENT MinimumVoltageRequirement;
    MAXIMUM_VOLTAGE_REQUIREMENT MaximumVoltageRequirement;
} SAVE_OPERATION_REQUIREMENTS;

//
// Get Energy Source Identification (Function Index 3)
//
typedef struct _ES_HARDWARE_REVISION {
    UINT8   Byte0;
    UINT8   Reserved0;
} ES_HARDWARE_REVISION;

typedef struct _ES_FIRMWARE_REVISION {
    UINT8   Byte0;
    UINT8   Byte1;
} ES_FIRMWARE_REVISION;

typedef struct _ES_CHARGE_TIMEOUT {
    UINT8   Byte0;
    UINT8   Byte1;
} ES_CHARGE_TIMEOUT;

typedef struct _DEVICE_MANAGED_ES_IDENTIFICATION {
    ES_HARDWARE_REVISION    EsHardwareRevision;
    ES_FIRMWARE_REVISION    EsFirmwareRevision;
    UINT8                   EsHealthCheckFrequency;
    ES_CHARGE_TIMEOUT       EsChargeTimeout;
    UINT8                   EsMinimumOperatingTemperature;
    UINT8                   EsMaximumOperatingTemperature;
    UINT8                   EsAttributes;
    UINT8                   EsTechnology;
} DEVICE_MANAGED_ES_IDENTIFICATION;

typedef struct _HOST_MANAGED_ES_IDENTIFICATION {
    UINT8   EsHealthCheckFrequency;
    UINT8   EsAttributes;
    UINT8   EsTechnology;
} HOST_MANAGED_ES_IDENTIFICATION;

typedef struct _ENERGY_SOURCE_IDENTIFICATION {
    UINT32                              Status;
    UINT8                               EnergySourcePolicy;
    DEVICE_MANAGED_ES_IDENTIFICATION    DeviceManagedEsIdentification;
    HOST_MANAGED_ES_IDENTIFICATION      HostManagedEsIdentification;
} ENERGY_SOURCE_IDENTIFICATION;

//
// Get Last Backup Information (Function Index 4)
//
typedef struct _TRIGGER_INFORMATION {
    UINT8   Byte0;
    UINT8   Reserved0;
    UINT8   Reserved1;
    UINT8   Reserved2;
} TRIGGER_INFORMATION;

typedef struct _SAVE_FAILURE_INFORMATION {
    UINT8   Byte0;
    UINT8   Byte1;
    UINT8   Reserved0;
    UINT8   Reserved1;
} SAVE_FAILURE_INFORMATION;

typedef struct _LAST_BACKUP_INFORMATION {
    UINT32                      Status;
    TRIGGER_INFORMATION         TriggerInformation;
    SAVE_FAILURE_INFORMATION    SaveFailureInformation;
} LAST_BACKUP_INFORMATION;

//
// Get NVM Thresholds (Function Index 5)
//
typedef struct _NVM_THRESHOLDS {
    UINT32  Status;
    UINT8   NvmLifetimePercentageWarningThreshold;
    UINT8   NvmLifetimePercentageErrorThreshold;
} NVM_THRESHOLDS;

//
// Set NVM Lifetime Percentage Warning Threshold (Function Index 6)
//
typedef struct _NVM_LIFETIME_PERCENTAGE_WARNING_THRESHOLD {
    UINT8   NvmLifetimePercentageWarningThreshold;
} NVM_LIFETIME_PERCENTAGE_WARNING_THRESHOLD;

//
// Get Energy Source Thresholds (Function Index 7)
//
typedef struct _ENERGY_SOURCE_THRESHOLDS {
    UINT32  Status;
    UINT8   EsLifetimePercentageWarningThreshold;
    UINT8   EsLifetimePercentageErrorThreshold;
    UINT8   EsTemperatureWarningThreshold;
    UINT8   EsTemperatureErrorThreshold;
} ENERGY_SOURCE_THRESHOLDS;

//
// Set Energy Source Lifetime Warning Threshold (Function Index 8)
//
typedef struct _ENERGY_SOURCE_LIFETIME_WARNING_THRESHOLD {
    UINT8   EsLifetimePercentageWarningThreshold;
} ENERGY_SOURCE_LIFETIME_WARNING_THRESHOLD;

//
// Set Energy Source Temperature Warning Threshold (Function Index 9)
//
typedef struct _ENERGY_SOURCE_TEMPERATURE_WARNING_THRESHOLD {
    UINT8   EsLifetimeTemperatureWarningThreshold;
} ENERGY_SOURCE_TEMPERATURE_WARNING_THRESHOLD;

//
// Get Critical Health Info (Function Index 10)
//
typedef struct _CRITICAL_HEALTH_INFO {
    UINT32  Status;
    UINT8   CriticalHealthInfo;
} CRITICAL_HEALTH_INFO;

//
// Get NVDIMM-N Health Info (Function Index 11) 
//
typedef struct _MODULE_HEALTH {
    UINT8   Byte0;
    UINT8   Byte1;
} MODULE_HEALTH;

typedef struct _NVDIMM_N_HEALTH_INFO {
    UINT32          Status;
    MODULE_HEALTH   ModuleHealth;
    UINT16          ModuleCurrentTemperature;
    UINT8           ErrorThresholdStatus;
    UINT8           WarningThresholdStatus;
    UINT8           NvmLifetime;
    UINT8           CountofDramUncorrectableEccErrors;
    UINT8           CountofDramCorrectableEccErrorAboveThresholdEvents;
} NVDIMM_N_HEALTH_INFO;

//
// Get Energy Source Health Info (Function Index 12)
//
typedef struct _ES_CURRENT_TEMPERATURE {
    UINT8   Byte0;
    UINT8   Byte1;
} ES_CURRENT_TEMPERATURE;

typedef struct _TOTAL_RUNTIME {
    UINT8   Byte0;
    UINT8   Byte1;
    UINT8   Reserved0;
    UINT8   Reserved1;
} TOTAL_RUNTIME;

typedef struct _ENERGY_SOURCE_HEALTH_INFO {
    UINT32                  Status;
    UINT8                   EsLifetimePercentage;
    ES_CURRENT_TEMPERATURE  EsCurrentTemperature;
    TOTAL_RUNTIME           TotalRuntime;
} ENERGY_SOURCE_HEALTH_INFO;

//
// Get Operational Statistics (Function Index 13)
//
typedef struct _DURATION_OF_LAST_SAVE_OPERATION {
    UINT8   Byte0;
    UINT8   Byte1;
    UINT8   Reserved0;
    UINT8   Reserved1;
} DURATION_OF_LAST_SAVE_OPERATION;

typedef struct _DURATION_OF_LAST_RESTORE_OPERATION {
    UINT8   Byte0;
    UINT8   Byte1;
    UINT8   Reserved0;
    UINT8   Reserved1;
} DURATION_OF_LAST_RESTORE_OPERATION;

typedef struct _DURATION_OF_LAST_ERASE_OPERATION {
    UINT8   Byte0;
    UINT8   Byte1;
    UINT8   Reserved0;
    UINT8   Reserved1;
} DURATION_OF_LAST_ERASE_OPERATION;

typedef struct _NUMBER_OF_SAVE_OPERATIONS_COMPLETED {
    UINT8   Byte0;
    UINT8   Byte1;
    UINT8   Reserved0;
    UINT8   Reserved1;
} NUMBER_OF_SAVE_OPERATIONS_COMPLETED;

typedef struct _NUMBER_OF_RESTORE_OPERATIONS_COMPLETED {
    UINT8   Byte0;
    UINT8   Byte1;
    UINT8   Reserved0;
    UINT8   Reserved1;
} NUMBER_OF_RESTORE_OPERATIONS_COMPLETED;

typedef struct _NUMBER_OF_ERASE_OPERATIONS_COMPLETED {
    UINT8   Byte0;
    UINT8   Byte1;
    UINT8   Reserved0;
    UINT8   Reserved1;
} NUMBER_OF_ERASE_OPERATIONS_COMPLETED;

typedef struct _NUMBER_OF_MODULE_POWER_CYCLES {
    UINT8   Byte0;
    UINT8   Byte1;
    UINT8   Reserved0;
    UINT8   Reserved1;
} NUMBER_OF_MODULE_POWER_CYCLES;

typedef struct _OPERATIONAL_STATISTICS {
    UINT32                                  Status;
    DURATION_OF_LAST_SAVE_OPERATION         DurationOfLastSaveOperation;
    DURATION_OF_LAST_RESTORE_OPERATION      DurationOfLastRestoreOperation;
    DURATION_OF_LAST_ERASE_OPERATION        DurationOfLastEraseOperation;
    NUMBER_OF_SAVE_OPERATIONS_COMPLETED     NumberOfSaveOperationsCompleted;
    NUMBER_OF_RESTORE_OPERATIONS_COMPLETED  NumberOfRestoreOperationsCompleted;
    NUMBER_OF_ERASE_OPERATIONS_COMPLETED    NumberOfEraseOperationsCompleted;
    NUMBER_OF_MODULE_POWER_CYCLES           NumberOfModulePowerCycles;
} OPERATIONAL_STATISTICS;

//
// Get Vendor Log Page Size (Function Index 14)
//
typedef struct _VENDOR_LOG_PAGE_SIZE {
    UINT32  Status;
    UINT32  VendorLogPageSize;
} VENDOR_LOG_PAGE_SIZE;

//
// Get Vendor Log Page (Function Index 15)
//
typedef struct _VENDOR_LOG_PAGE {
    UINT32  Status;
    UINT32  VendorLogPage;
} VENDOR_LOG_PAGE;

//
// Query Error Injection Status (Function Index 16)
//
typedef struct _ERROR_INJECTION_STATUS {
    UINT32  Status;
    UINT8   ErrorInjectionEnabled;
} ERROR_INJECTION_STATUS;

//
// Inject Error (Function Index 17)
//
typedef struct _INJECT_OPERATION_FAILURES {
    UINT8   Byte0;
    UINT8   Byte1;
} INJECT_OPERATION_FAILURES;

typedef struct _INJECT_ERROR {
    INJECT_OPERATION_FAILURES   InjectOperationFailures;
    UINT8                       InjectEnergySourceFailures;
    UINT8                       InjectFirmwareUpdateFailures;
} INJECT_ERROR;

//
// Get Injected Errors (Function Index 18)
//
typedef struct _OPERATION_FAILURES_INJECTED {
    UINT8   Byte0;
    UINT8   Byte1;
} OPERATION_FAILURES_INJECTED;

typedef struct _INJECTED_ERRORS {
    UINT32                      Status;
    OPERATION_FAILURES_INJECTED OperationFailuresInjected;
    UINT8                       EnergySourceFailuresInjected;
    UINT8                       FirmwareUpdateFailuresInjected;
} INJECTED_ERRORS;

//
// Erase NVM Image (Function Index 19)
//

//
// Arm NVDIMM-N (Function Index 20)
//

//
// Reset to Factory Defaults (Function Index 21)
//

//
// Start Firmware Update (Function Index 22)
//
typedef struct _START_FIRMWARE_UPDATE {
    UINT8   FirmwareSlot;
} START_FIRMWARE_UPDATE;

//
// Send Firmware Update Data (Function Index 23)
//
typedef struct _FIRMWARE_UPDATE_DATA {
    UINT32  RegionLength;
    UINT16  RegionId;
    UINT8   BlockId;
    UINT8   FirmwareData[FIRMWARE_DATA_LENGTH];
} FIRMWARE_UPDATE_DATA;

//
// Finish Firmware Update (Function Index 24)
//

//
// Select Firmware Image Slot (Function Index 25)
//
typedef struct _SELECT_FIRMWARE_IMAGE_SLOT {
    UINT8   FirmwareSlot;
} SELECT_FIRMWARE_IMAGE_SLOT;

//
// Get Firmware Info (Function Index 26)
//
typedef struct _GET_FIRMWARE_IMAGE_SLOT {
    UINT8   FirmwareSlot;
} GET_FIRMWARE_IMAGE_SLOT;

typedef struct _FIRMWARE_INFO_VERSION {
    UINT8   Byte0;
    UINT8   Byte1;
} FIRMWARE_INFO_VERSION;

typedef struct _FIRMWARE_INFO {
    UINT32                  Status;
    FIRMWARE_INFO_VERSION   Version;
} FIRMWARE_INFO;

//
// I2C Read (Function Index 27)
//
typedef struct _I2C_READ_INPUT {
    UINT8   Page;
    UINT8   Offset;
} I2C_READ_INPUT;

typedef struct _I2C_READ_OUTPUT {
    UINT32  Status;
    UINT8   Data;
} I2C_READ_OUTPUT;

//
// I2C Write (Function Index 28)
//
typedef struct _I2C_WRITE {
    UINT8   Page;
    UINT8   Offset;
    UINT8   Data;
} I2C_WRITE;

//
// Read Typed Data (Function Index 29)
//
typedef struct _READ_TYPED_DATA_INPUT {
    UINT8   DataType;
    UINT16  RegionId;
    UINT8   BlockId;
} READ_TYPED_DATA_INPUT;

typedef struct _READ_TYPED_DATA_OUTPUT {
    UINT32  Status;
    UINT8   Data[READ_TYPED_DATA_LENGTH];
} READ_TYPED_DATA_OUTPUT;

//
// Write Typed Data (Function Index 30)
//
typedef struct _WRITE_TYPED_DATA {
    UINT8   DataType;
    UINT16  RegionId;
    UINT8   BlockId;
    UINT8   Data[READ_TYPED_DATA_LENGTH];
} WRITE_TYPED_DATA;

//
// Set Memory Error Counters (Function Index 31)
//
typedef struct _SET_MEMORY_ERROR_COUNTERS {
    UINT8   CountOfDramUncorrectableEccErrors;
    UINT8   CountOfDramCorrectableEccErrorAboveThresholdEvents;
} SET_MEMORY_ERROR_COUNTERS;

#pragma pack ()

#endif  // JEDEC_NVDIMM_DSM_H



