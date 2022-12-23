/*****************************************************************************
 *
 * Copyright 2012 - 2020 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 ******************************************************************************
 */

#include <AmdCpmDxe.h>
#include <AmdCpmBaseIo.h>
#include <AmdCpmCpu.h>
#include <AmdCpmFch.h>
#include <AmdCpmTable.h>
  #include <Guid/AmdMemoryInfoHob.h>


AMD_CPM_TABLE_PROTOCOL    *AmdCpmTableProtocolPtr;
AMD_CPM_NV_DATA_PROTOCOL  *AmdCpmNvDataProtocolPtr;
EFI_EVENT                 ReadyToBootEvent;

extern UINT8              AmdCpmSsdtSupport;

EFI_GUID  COMMON_ACPI_DEVICE_GUID = {
  0x5b1e5b38, 0x8ebd, 0x4784, 0x9b, 0x52, 0x38, 0xb2, 0xaa, 0x9b, 0xff, 0x2f
};

VOID
EFIAPI
AmdCpmDxeRegisterKernel (
  IN       VOID                                *This
  );

VOID
EFIAPI
AmdCpmInitLate (
  IN       EFI_EVENT                           Event,
  IN       VOID                                *Context
  );

EFI_STATUS
EFIAPI
AmdCpmAddSsdtTable (
  IN       VOID                                *This,
  IN       VOID                                *EfiGuid,
  IN       UINT64                              *OemTableId,
  IN       AMD_CPM_ADDSSDTCALLBACK_FN          Function,
  IN       VOID                                *Context
  );


/*----------------------------------------------------------------------------------------*/
/**
 * Entry point of the AMD CPM Init DXE driver
 *
 * This function installs AmdCpmTableProtocol, AmdCpmNvDataProtocol and CPM Common SSDT Table
 * and registers CPM common functions at AmdCpmInitDxe.
 *
 * @param[in]     ImageHandle    Pointer to the firmware file system header
 * @param[in]     SystemTable    Pointer to System table
 *
 * @retval        EFI_SUCCESS    Module initialized successfully
 * @retval        EFI_ERROR      Initialization failed (see error for more details)
 */
EFI_STATUS
EFIAPI
AmdCpmInitDxeEntryPoint (
  IN       EFI_HANDLE              ImageHandle,
  IN       EFI_SYSTEM_TABLE        *SystemTable
  )
{
  EFI_STATUS                      Status;
  AMD_CPM_MAIN_TABLE              *MainTablePtr;
  VOID                            *HobList;
  VOID                            *Buffer;
  UINTN                           BufferSize;
  UINT8                           *HobBuffer;
  EFI_HANDLE                      Handle;
  AMD_CPM_NV_DATA_STRUCT          *NvDataPtr;
  AMD_CPM_TABLE_LIST              *TableListPtr;

  DEBUG((DEBUG_INFO, "KER-DXE-%a-Start\n", __FUNCTION__));
  //
  // Initialize Global Variable
  //
  CpmInitializeDriverLib (ImageHandle, SystemTable);

  RECORD_TIME_DXE (BeginAmdCpmInitDxeDriver);

  DEBUG((DEBUG_INFO, "KER-DXE-%a-CpmGetSystemConfigurationTable-gEfiHobListGuid\n", __FUNCTION__));
  Status = CpmGetSystemConfigurationTable (&gEfiHobListGuid, &HobList);
  if (EFI_ERROR (Status)) {
    DEBUG((DEBUG_INFO, "KER-DXE-%a-End-1-Status=%r\n", __FUNCTION__, Status));
    return Status;
  }

  Buffer = NULL;
  BufferSize = 0;
  DEBUG((DEBUG_INFO, "KER-DXE-%a-If_CpmGetHobBuffer-gAmdCpmTableHobGuid\n", __FUNCTION__));
  If_CpmGetHobBuffer (HobList, gAmdCpmTableHobGuid, Buffer, BufferSize, GuidHob) {
    DEBUG((DEBUG_INFO, "KER-DXE-%a-CpmRelocateTableList\n", __FUNCTION__));
    CpmRelocateTableList (Buffer);
    TableListPtr = CpmAdjustTableList (Buffer);

    DEBUG((DEBUG_INFO, "KER-DXE-%a-AllocatePool-EfiACPIMemoryNVS-HobBuffer\n", __FUNCTION__));
    Status = gBS->AllocatePool (
                    EfiACPIMemoryNVS,
                    TableListPtr->Size + AMD_TABLE_ADDITIONAL_BUFFER_SIZE,
                    (VOID**)&HobBuffer
                    );

    DEBUG((DEBUG_INFO, "KER-DXE-%a-CpmCopyTableListToMemory\n", __FUNCTION__));
    CpmCopyTableListToMemory (TableListPtr, HobBuffer);
    ((AMD_CPM_HOB_HEADER*)HobBuffer)->Revision = ((AMD_CPM_HOB_HEADER*)Buffer)->Revision;

    DEBUG((DEBUG_INFO, "KER-DXE-%a-AllocatePool-EfiACPIMemoryNVS-AmdCpmTableProtocolPtr\n", __FUNCTION__));
    Status = gBS->AllocatePool (
                    EfiACPIMemoryNVS,
                    sizeof (AMD_CPM_TABLE_PROTOCOL),
                    (VOID**)&AmdCpmTableProtocolPtr
                    );

    MainTablePtr                          = ((AMD_CPM_HOB_HEADER*)HobBuffer)->MainTablePtr.Pointer;
    AmdCpmTableProtocolPtr->Revision      = ((AMD_CPM_HOB_HEADER*)HobBuffer)->Revision;
    AmdCpmTableProtocolPtr->MainTablePtr  = MainTablePtr;

    DEBUG((DEBUG_INFO, "KER-DXE-%a-AmdCpmDxeRegisterKernel\n", __FUNCTION__));
    AmdCpmDxeRegisterKernel (AmdCpmTableProtocolPtr);
    DEBUG((DEBUG_INFO, "KER-DXE-%a-CpmRegisterBaseIo\n", __FUNCTION__));
    CpmRegisterBaseIo (AmdCpmTableProtocolPtr);
    DEBUG((DEBUG_INFO, "KER-DXE-%a-CpmRegisterCpu\n", __FUNCTION__));
    CpmRegisterCpu (AmdCpmTableProtocolPtr);
    DEBUG((DEBUG_INFO, "KER-DXE-%a-CpmRegisterFch\n", __FUNCTION__));
    CpmRegisterFch (AmdCpmTableProtocolPtr);

    Handle = NULL;
    DEBUG((DEBUG_INFO, "KER-DXE-%a-InstallProtocolInterface-gAmdCpmTableProtocolGuid\n", __FUNCTION__));
    gBS->InstallProtocolInterface (
                    &Handle,
                    &gAmdCpmTableProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    AmdCpmTableProtocolPtr
                    );

    DEBUG((DEBUG_INFO, "KER-DXE-%a-AllocatePool-EfiACPIMemoryNVS-AmdCpmNvDataProtocolPtr\n", __FUNCTION__));
    Status = gBS->AllocatePool (
                    EfiACPIMemoryNVS,
                    sizeof (AMD_CPM_NV_DATA_PROTOCOL),
                    (VOID**)&AmdCpmNvDataProtocolPtr
                    );
    Handle = ImageHandle;
    DEBUG((DEBUG_INFO, "KER-DXE-%a-InstallProtocolInterface-gAmdCpmNvDataProtocolGuid\n", __FUNCTION__));
    Status = gBS->InstallProtocolInterface (
                    &Handle,
                    &gAmdCpmNvDataProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    AmdCpmNvDataProtocolPtr
                    );
    if (EFI_ERROR (Status)) {
      DEBUG((DEBUG_INFO, "KER-DXE-%a-End-2-Status=%r\n", __FUNCTION__, Status));
      return (Status);
    }

    BufferSize = sizeof (AMD_CPM_NV_DATA_STRUCT);

    DEBUG((DEBUG_INFO, "KER-DXE-%a-AllocatePool-EfiACPIMemoryNVS-NvDataPtr\n", __FUNCTION__));
    Status = gBS->AllocatePool (
                    EfiACPIMemoryNVS,
                    BufferSize,
                    (VOID**)&NvDataPtr
                    );
    if (EFI_ERROR (Status)) {
      DEBUG((DEBUG_INFO, "KER-DXE-%a-End-3-Status=%r\n", __FUNCTION__, Status));
      return Status;
    }

    DEBUG((DEBUG_INFO, "KER-DXE-%a-CpmZeroMem\n", __FUNCTION__));
    CpmZeroMem (NvDataPtr, BufferSize);
    NvDataPtr->CpmVersion               = (UINT32)AmdCpmTableProtocolPtr->Revision;
    NvDataPtr->CpmPcieMmioBaseAddr      = MainTablePtr->PcieMemIoBaseAddr;
    NvDataPtr->CpmAcpiMmioBaseAddr      = MainTablePtr->AcpiMemIoBaseAddr;
    NvDataPtr->CpmSbChipId              = AmdCpmTableProtocolPtr->ChipId.Sb;
    NvDataPtr->CpmEcRamGpioBaseOffset   = CFG_CPM_ECRAM_GPIO_OFFSET;
    NvDataPtr->CpmSwSmiPort             = AmdCpmTableProtocolPtr->CommonFunction.GetAcpiSmiCmd (AmdCpmTableProtocolPtr);
    NvDataPtr->CpmSwSmiCmdSetAutoUmaMode  = CFG_CPM_SWSMICMD_SETAUTOUMAMODE;
    NvDataPtr->CpmUmaSize               = 0;
    NvDataPtr->CpmSbStrap               = (UINT8)AmdCpmTableProtocolPtr->CommonFunction.GetStrap (AmdCpmTableProtocolPtr);
    NvDataPtr->CpmMainTable             = (UINT32) (UINT64)AmdCpmTableProtocolPtr->CommonFunction.GetTablePtr (AmdCpmTableProtocolPtr, CPM_SIGNATURE_MAIN_TABLE);
    NvDataPtr->CpmDeviceDetectionTable  = (UINT32) (UINT64)AmdCpmTableProtocolPtr->CommonFunction.GetTablePtr (AmdCpmTableProtocolPtr, CPM_SIGNATURE_GPIO_DEVICE_DETECTION);
    NvDataPtr->CpmDeviceResetTable      = (UINT32) (UINT64)AmdCpmTableProtocolPtr->CommonFunction.GetTablePtr (AmdCpmTableProtocolPtr, CPM_SIGNATURE_GPIO_DEVICE_RESET);
    NvDataPtr->CpmDevicePowerTable      = (UINT32) (UINT64)AmdCpmTableProtocolPtr->CommonFunction.GetTablePtr (AmdCpmTableProtocolPtr, CPM_SIGNATURE_GPIO_DEVICE_POWER);
    NvDataPtr->CpmWirelessButtonTable   = (UINT32) (UINT64)AmdCpmTableProtocolPtr->CommonFunction.GetTablePtr (AmdCpmTableProtocolPtr, CPM_SIGNATURE_WIRELESS_BUTTON);
    NvDataPtr->CpmSaveContextTable      = (UINT32) (UINT64)AmdCpmTableProtocolPtr->CommonFunction.GetTablePtr (AmdCpmTableProtocolPtr, CPM_SIGNATURE_SAVE_CONTEXT);
    NvDataPtr->CpmExpressCardTable      = (UINT32) (UINT64)AmdCpmTableProtocolPtr->CommonFunction.GetTablePtr (AmdCpmTableProtocolPtr, CPM_SIGNATURE_PCIE_EXPRESS_CARD);
    NvDataPtr->CpmDisplayFeatureTable   = (UINT32) (UINT64)AmdCpmTableProtocolPtr->CommonFunction.GetTablePtr (AmdCpmTableProtocolPtr, CPM_SIGNATURE_DISPLAY_FEATURE);
    NvDataPtr->CpmZeroPowerOddTable     = (UINT32) (UINT64)AmdCpmTableProtocolPtr->CommonFunction.GetTablePtr (AmdCpmTableProtocolPtr, CPM_SIGNATURE_ZERO_POWER_ODD);
    NvDataPtr->CpmAcpiThermalFanTable   = (UINT32) (UINT64)AmdCpmTableProtocolPtr->CommonFunction.GetTablePtr (AmdCpmTableProtocolPtr, CPM_SIGNATURE_ACPI_THERMAL_FAN);
    NvDataPtr->CpmAdaptiveS4Table       = (UINT32) (UINT64)AmdCpmTableProtocolPtr->CommonFunction.GetTablePtr (AmdCpmTableProtocolPtr, CPM_SIGNATURE_ADAPTIVE_S4);
    NvDataPtr->CpmPcieClockTable        = (UINT32) (UINT64)AmdCpmTableProtocolPtr->CommonFunction.GetTablePtr (AmdCpmTableProtocolPtr, CPM_SIGNATURE_PCIE_CLOCK);
    NvDataPtr->CpmOtherHotplugCardTable = (UINT32) (UINT64)AmdCpmTableProtocolPtr->CommonFunction.GetTablePtr (AmdCpmTableProtocolPtr, CPM_SIGNATURE_PCIE_OTHER_HOTPLUG_CARD);
    NvDataPtr->CpmCoreTopologyTable     = (UINT32) (UINT64)AmdCpmTableProtocolPtr->CommonFunction.GetTablePtr (AmdCpmTableProtocolPtr, CPM_SIGNATURE_CORE_TOPOLOGY);
    NvDataPtr->CpmUcsiTable             = (UINT32) (UINT64)AmdCpmTableProtocolPtr->CommonFunction.GetTablePtr (AmdCpmTableProtocolPtr, CPM_SIGNATURE_UCSI);
    NvDataPtr->CpmLowPowerEthernetTable = (UINT32) (UINT64)AmdCpmTableProtocolPtr->CommonFunction.GetTablePtr (AmdCpmTableProtocolPtr, CPM_SIGNATURE_PCIE_LOW_POWER_ETHERNET);
    NvDataPtr->CpmWirelessLanRecoveryTable = (UINT32) (UINT64)AmdCpmTableProtocolPtr->CommonFunction.GetTablePtr (AmdCpmTableProtocolPtr, CPM_SIGNATURE_WIRELESS_LAN_RECOVERY);

    AmdCpmNvDataProtocolPtr->NvDataPtr = NvDataPtr;

    DEBUG((DEBUG_INFO, "KER-DXE-%a-If_CpmGetHobBuffer-gAmdMemoryInfoHobGuid\n", __FUNCTION__));
    If_CpmGetHobBuffer (HobList, gAmdMemoryInfoHobGuid, Buffer, BufferSize, GuidHob) {
      AMD_MEMORY_INFO_HOB           *MemInfoHob;
      AMD_MEMORY_RANGE_DESCRIPTOR   *MemRangDesc;
      UINT32                        NumberOfDescriptor;
      UINT32                        Index;
      MemInfoHob = (AMD_MEMORY_INFO_HOB*) Buffer;
      NumberOfDescriptor = MemInfoHob->NumberOfDescriptor;
      MemRangDesc = &MemInfoHob->Ranges[0];
      DEBUG((DEBUG_INFO, "KER-DXE-%a-Get-CpmUmaSize-From-AMD_MEMORY_INFO_HOB\n", __FUNCTION__));
      for (Index = 0; Index <= NumberOfDescriptor; Index++) {
        DEBUG((DEBUG_INFO, "KER-DXE-%a-MemRangDesc[Index=0x%X].Attribute=0x%X\n", __FUNCTION__, Index, MemRangDesc[Index].Attribute));
        DEBUG((DEBUG_INFO, "KER-DXE-%a-MemRangDesc[Index=0x%X].Size=0x%X\n", __FUNCTION__, Index, MemRangDesc[Index].Size));
        if (MemRangDesc[Index].Attribute == AMD_MEMORY_ATTRIBUTE_UMA) {
          NvDataPtr->CpmUmaSize = (UINT32) MemRangDesc[Index].Size >> 20;
          DEBUG((DEBUG_INFO, "KER-DXE-%a-CpmUmaSize=0x%X\n", __FUNCTION__, NvDataPtr->CpmUmaSize));
          break;
        }
      }
    }

    DEBUG((DEBUG_INFO, "KER-DXE-%a-CreateEventEx-gEfiEventReadyToBootGuid-For-AmdCpmInitLate\n", __FUNCTION__));
    Status = gBS->CreateEventEx (
                    CPM_EVENT_NOTIFY_SIGNAL,
                    CPM_TPL_NOTIFY,
                    AmdCpmInitLate,
                    (VOID*)AmdCpmNvDataProtocolPtr,
                    &gEfiEventReadyToBootGuid,
                    &ReadyToBootEvent
                    );
  }

  RECORD_TIME_DXE (EndAmdCpmInitDxeDriver);

  DEBUG((DEBUG_INFO, "KER-DXE-%a-End-4-Status=%r\n", __FUNCTION__, Status));
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Kernal Common function to read the register of Smbus Device.
 *
 * @param[in]     This           Point to Protocol
 * @param[in]     Select         The Smbus number.
 * @param[in]     Address        The address of Smbus device
 * @param[in]     Offset         The Offset of Smbus register
 * @param[in]     Length         The register size in BYTE
 * @param[out]    Value          Data Pointer to save register value
 *
 * @retval        EFI_SUCCESS    SSDT table initialized successfully
 * @retval        EFI_ERROR      Initialization failed
 */
EFI_STATUS
AmdCpmDxeSmbusGetByte (
  IN       VOID                    *This,
  IN       UINT8                   Select,
  IN       UINT8                   Address,
  IN       UINT8                   Offset,
  IN       UINTN                   Length,
     OUT   UINT8                   *Value
  )
{
  EFI_STATUS                      Status;
  EFI_SMBUS_DEVICE_ADDRESS        SmbusSlaveAddress;
  EFI_SMBUS_HC_PROTOCOL           *SmbusController;
  UINTN                           SmbusLength;
  UINTN                           SmbusOffset;

  DEBUG((DEBUG_INFO, "KER-DXE-%a-Start\n", __FUNCTION__));
  Status = gBS->LocateProtocol (
                                &gCpmSmbusProtocolGuid,
                                NULL,
                                (VOID**)&SmbusController
                                );

  if (!EFI_ERROR (Status)) {
    SmbusLength = Length;
    SmbusOffset = Offset;
    SmbusSlaveAddress.SmbusDeviceAddress = Address;

    DEBUG((DEBUG_INFO, "KER-DXE-%a-Execute-EfiSmbusReadByte\n", __FUNCTION__));
    Status = SmbusController->Execute (
                                SmbusController,
                                SmbusSlaveAddress,
                                SmbusOffset,
                                EfiSmbusReadByte,
                                FALSE,
                                &SmbusLength,
                                Value
                                );
  }
  DEBUG((DEBUG_INFO, "KER-DXE-%a-End-Status=%r\n", __FUNCTION__, Status));
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Kernal Common function to set the register of Smbus device.
 *
 * @param[in]     This           Point to Protocol
 * @param[in]     Select         The Smbus number.
 * @param[in]     Address        The address of Smbus device
 * @param[in]     Offset         The Offset of Smbus register
 * @param[in]     Length         The register size in BYTE
 * @param[in]     Value          Data Pointer to register value
 *
 * @retval        EFI_SUCCESS    SSDT table initialized successfully
 * @retval        EFI_ERROR      Initialization failed
 */
EFI_STATUS
AmdCpmDxeSmbusSetByte (
  IN       VOID                    *This,
  IN       UINT8                   Select,
  IN       UINT8                   Address,
  IN       UINT8                   Offset,
  IN       UINTN                   Length,
  IN       UINT8                   *Value
  )
{
  EFI_STATUS                      Status;
  EFI_SMBUS_DEVICE_ADDRESS        SmbusSlaveAddress;
  EFI_SMBUS_HC_PROTOCOL           *SmbusController;
  UINTN                           SmbusLength;
  UINTN                           SmbusOffset;

  DEBUG((DEBUG_INFO, "KER-DXE-%a-Start\n", __FUNCTION__));
  Status = gBS->LocateProtocol (
                                &gCpmSmbusProtocolGuid,
                                NULL,
                                (VOID**)&SmbusController
                                );

  if (!EFI_ERROR (Status)) {
    SmbusLength = Length;
    SmbusOffset = Offset;
    SmbusSlaveAddress.SmbusDeviceAddress = Address;

    DEBUG((DEBUG_INFO, "KER-DXE-%a-Execute-EfiSmbusWriteByte\n", __FUNCTION__));
    Status = SmbusController->Execute (
                                SmbusController,
                                SmbusSlaveAddress,
                                SmbusOffset,
                                EfiSmbusWriteByte,
                                FALSE,
                                &SmbusLength,
                                Value
                                );
  }

  DEBUG((DEBUG_INFO, "KER-DXE-%a-End-Status=%r\n", __FUNCTION__, Status));
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Kernal Common function to read the register of Smbus Device in block mode.
 *
 * @param[in]     This           Point to Protocol
 * @param[in]     Select         The Smbus number.
 * @param[in]     Address        The address of Smbus device
 * @param[in]     Offset         The Offset of Smbus register
 * @param[in]     Length         The register size in BYTE
 * @param[out]    Value          Data Pointer to save register value
 *
 * @retval        EFI_SUCCESS    SSDT table initialized successfully
 * @retval        EFI_ERROR      Initialization failed
 */
EFI_STATUS
AmdCpmDxeSmbusGetBlock (
  IN       VOID                    *This,
  IN       UINT8                   Select,
  IN       UINT8                   Address,
  IN       UINT8                   Offset,
  IN       UINTN                   Length,
     OUT   UINT8                   *Value
  )
{
  EFI_STATUS                      Status;
  EFI_SMBUS_DEVICE_ADDRESS        SmbusSlaveAddress;
  EFI_SMBUS_HC_PROTOCOL           *SmbusController;
  UINTN                           SmbusLength;
  UINTN                           SmbusOffset;

  DEBUG((DEBUG_INFO, "KER-DXE-%a-Start\n", __FUNCTION__));
  Status = gBS->LocateProtocol (
                                &gCpmSmbusProtocolGuid,
                                NULL,
                                (VOID**)&SmbusController
                                );

  if (!EFI_ERROR (Status)) {
    SmbusLength = Length;
    SmbusOffset = Offset;
    SmbusSlaveAddress.SmbusDeviceAddress = Address;

    DEBUG((DEBUG_INFO, "KER-DXE-%a-Execute-EfiSmbusReadBlock\n", __FUNCTION__));
    Status = SmbusController->Execute (
                                SmbusController,
                                SmbusSlaveAddress,
                                SmbusOffset,
                                EfiSmbusReadBlock,
                                FALSE,
                                &SmbusLength,
                                Value
                                );
  }
  DEBUG((DEBUG_INFO, "KER-DXE-%a-End-Status=%r\n", __FUNCTION__, Status));
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Kernal Common function to set the register of Smbus device in block mode.
 *
 * @param[in]     This           Point to Protocol
 * @param[in]     Select         The Smbus number.
 * @param[in]     Address        The address of Smbus device
 * @param[in]     Offset         The Offset of Smbus register
 * @param[in]     Length         The register size in BYTE
 * @param[in]     Value          Data Pointer to register value
 *
 * @retval        EFI_SUCCESS    SSDT table initialized successfully
 * @retval        EFI_ERROR      Initialization failed
 */
EFI_STATUS
AmdCpmDxeSmbusSetBlock (
  IN       VOID                    *This,
  IN       UINT8                   Select,
  IN       UINT8                   Address,
  IN       UINT8                   Offset,
  IN       UINTN                   Length,
  IN       UINT8                   *Value
  )
{
  EFI_STATUS                      Status;
  EFI_SMBUS_DEVICE_ADDRESS        SmbusSlaveAddress;
  EFI_SMBUS_HC_PROTOCOL           *SmbusController;
  UINTN                           SmbusLength;
  UINTN                           SmbusOffset;

  DEBUG((DEBUG_INFO, "KER-DXE-%a-Start\n", __FUNCTION__));
  Status = gBS->LocateProtocol (
                                &gCpmSmbusProtocolGuid,
                                NULL,
                                (VOID**)&SmbusController
                                );

  if (!EFI_ERROR (Status)) {
    SmbusLength = Length;
    SmbusOffset = Offset;
    SmbusSlaveAddress.SmbusDeviceAddress = Address;

    DEBUG((DEBUG_INFO, "KER-DXE-%a-Execute-EfiSmbusWriteBlock\n", __FUNCTION__));
    Status = SmbusController->Execute (
                                SmbusController,
                                SmbusSlaveAddress,
                                SmbusOffset,
                                EfiSmbusWriteBlock,
                                FALSE,
                                &SmbusLength,
                                Value
                                );
  }

  DEBUG((DEBUG_INFO, "KER-DXE-%a-End-Status=%r\n", __FUNCTION__, Status));
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Common kernel function to check ACPI object
 *
 * This function is used to check whether it is an AML Op Region Object in the table.
 *
 * @param[in]     TablePtr       Pointer to the AML table
 *
 * @retval        TRUE           Is AML Op Region Object
 * @retval        FALSE          Is not AML Op Region Object
 */
BOOLEAN
IsAmlOpRegionObject (
  IN       UINT8                               *TablePtr
  )
{
  UINT16 *Operation;
  Operation = (UINT16*) (TablePtr - 2);
  if (*Operation == AML_OPREGION_OP ) {
    return TRUE;
  }

  return FALSE;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback function to update Common SSDT table
 *
 * This function is used to update the base address and size of the region object: CPNV.
 *
 * @param[in]     This           Pointer to Protocol
 * @param[in]     AmlObjPtr      The AML Object Buffer
 * @param[in]     Context        The Parameter Buffer
 *
 * @retval        TRUE           SSDT Table has been updated completely
 * @retval        FALSE          SSDT Table has not been updated completely
 */
BOOLEAN
EFIAPI
AmdCpmCommonSsdtCallBack (
  IN       VOID                                *This,
  IN       VOID                                *AmlObjPtr,
  IN       VOID                                *Context
  )
{
  UINT32                  *RegionAddress;
  UINT32                  *RegionSize;
  UINT32                  *Buffer;
  AMD_CPM_TABLE_PROTOCOL  *TableProtocolPtr;

  TableProtocolPtr = This;
  Buffer = (UINT32*) Context;
  switch (*((UINT32*)AmlObjPtr)) {
  case (CPM_SIGNATURE_32 ('C', 'P', 'N', 'V')):
    if (TableProtocolPtr->CommonFunction.IsAmlOpRegionObject (AmlObjPtr)) {
      DEBUG((DEBUG_INFO, "KER-DXE-%a-UpdateAcpiName-CPNV\n", __FUNCTION__));
      RegionAddress = (UINT32 *) ((UINT8*)AmlObjPtr + 6);
      (* RegionAddress) = *Buffer;
      RegionSize = (UINT32 *) ((UINT8*)AmlObjPtr + 11);
      * RegionSize = *(Buffer + 1);
    }
    break;
  case (CPM_SIGNATURE_32 ('M', 'O', 'E', 'M')):
    if (*(Buffer + 2)) {
      DEBUG((DEBUG_INFO, "KER-DXE-%a-UpdateAcpiName-MOEM\n", __FUNCTION__));
      *((UINT32*)AmlObjPtr) = *(Buffer + 2);
    }
    break;
  case (CPM_SIGNATURE_32 ('M', 'L', 'I', 'B')):
    if (*(Buffer + 3)) {
      DEBUG((DEBUG_INFO, "KER-DXE-%a-UpdateAcpiName-MLIB\n", __FUNCTION__));
      *((UINT32*)AmlObjPtr) = *(Buffer + 3);
    }
    break;
  case (CPM_SIGNATURE_32 ('G', 'P', '1', '8')):
    if (*(Buffer + 4)) {
      DEBUG((DEBUG_INFO, "KER-DXE-%a-UpdateAcpiName-GP18\n", __FUNCTION__));
      *((UINT32*)AmlObjPtr) = *(Buffer + 4);
    }
    break;
  case CPM_SIGNATURE_32 ('M', '2', '8', '5'):     // ASL code: CpmPostCodeBuffer: M285
    if (*(Buffer + 5)) {
      DEBUG((DEBUG_INFO, "KER-DXE-%a-UpdateAcpiName-M285\n", __FUNCTION__));
//    In Function.asi
//      Name (CpmPostCodeBuffer, Buffer (4) {0, 3, 0x80, 0})
//      CreateByteField (CpmPostCodeBuffer, 0, CpmTestPointEnable)  // PcdAgesaTestPointEnable
//      CreateByteField (CpmPostCodeBuffer, 1, CpmTestPointWidth)   // PcdAgesaTestPointWidth
//      CreateWordField (CpmPostCodeBuffer, 2, CpmDebugPort)        // PcdIdsDebugPort
//    In AmdCpmInitDxe.c
//      Buffer[5] = PcdGetBool (PcdAgesaTestPointEnable);
//      Buffer[6] = (UINT32)PcdGet8 (PcdAgesaTestPointWidth);
//      Buffer[7] = (UINT32)PcdGet16 (PcdIdsDebugPort);
        *((UINT8*)AmlObjPtr + 8) = *(UINT8*)(Buffer + 5);
        *((UINT8*)AmlObjPtr + 9) = *(UINT8*)(Buffer + 6);
        *((UINT16*)AmlObjPtr + 5) = *(UINT16*)(Buffer + 7);
        *(Buffer + 5) = 0;
    }
    break;
  }
  return FALSE;
}

/*----------------------------------------------------------------------------------------*/
/**
 * The function to load Common SSDT table.
 *
 * This function gets called each time the EFI_EVENT_SIGNAL_READY_TO_BOOT gets signaled.
 *
 * @param[in]     Event          EFI_EVENT
 * @param[in]     Context        The Parameter Buffer
 *
 */
VOID
EFIAPI
AmdCpmInitLate (
  IN       EFI_EVENT               Event,
  IN       VOID                    *Context
  )
{
  AMD_CPM_NV_DATA_PROTOCOL        *NvDataProtocolPtr;
  EFI_STATUS                      Status;
  UINT32                          Buffer[8];
  STATIC BOOLEAN                  InitlateInvoked = FALSE;

  DEBUG((DEBUG_INFO, "KER-DXE-%a-Start", __FUNCTION__));
  DEBUG((DEBUG_INFO, "-From-AmdCpmInitDxeEntryPoint-CreateEventEx-gEfiEventReadyToBootGuid\n"));
  RECORD_TIME_DXE (BeginAmdCpmLoadCommonSsdt);

  if (!InitlateInvoked) {

    DEBUG((DEBUG_INFO, "KER-DXE-%a-if (!InitlateInvoked)\n", __FUNCTION__));
    NvDataProtocolPtr = (AMD_CPM_NV_DATA_PROTOCOL *)Context;

    ZeroMem (Buffer, sizeof (Buffer));
    Buffer[0] = (UINT32) (UINT64) (NvDataProtocolPtr->NvDataPtr);
    Buffer[1] = (UINT32) (sizeof (AMD_CPM_NV_DATA_STRUCT));
    Buffer[2] = CFG_CPM_ASL_OEM_CALLBACK;
    Buffer[3] = CFG_CPM_ASL_OEM_MLIB;
    Buffer[4] = CFG_AMD_CPM_ASL_GP18_NAME;   // PcdGet32 (PcieGp18AslName)
    if (PcdGetBool (PcdAgesaTestPointEnable)) {
      Buffer[5] = 1;
    }
    Buffer[6] = (UINT32)PcdGet8 (PcdAgesaTestPointWidth);
    Buffer[7] = (UINT32)PcdGet16 (PcdIdsDebugPort);

    DEBUG((DEBUG_INFO, "KER-DXE-%a-AmdCpmAddSsdtTable-AmdCpmCommonSsdtCallBack\n", __FUNCTION__));
    Status = AmdCpmAddSsdtTable (  (VOID*)AmdCpmTableProtocolPtr,
                                &COMMON_ACPI_DEVICE_GUID,
                                NULL,
                                AmdCpmCommonSsdtCallBack,
                                &Buffer[0]
                                );
  }

  InitlateInvoked = TRUE;

  RECORD_TIME_DXE (EndAmdCpmLoadCommonSsdt);

  DEBUG((DEBUG_INFO, "KER-DXE-%a-End\n", __FUNCTION__));
  return;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Kernal Common function to load SSDT table.
 *
 * This function searchs ACPI storage file and finds the matched SSDT table. The table will
 * be updated and registered in ACPI area.
 *
 * @param[in]     This           Point to Protocol
 * @param[in]     EfiGuid        The GUID of ACPI storage file of SSDT table
 * @param[in]     OemTableId     OEM Table Id of SSDT table
 * @param[in]     Function       Callback Function
 * @param[in]     Context        The Parameters for callback function
 *
 * @retval        EFI_SUCCESS    SSDT table initialized successfully
 * @retval        EFI_ERROR      Initialization failed
 */
EFI_STATUS
EFIAPI
AmdCpmAddSsdtTable (
  IN       VOID                                *This,
  IN       VOID                                *EfiGuid,
  IN       UINT64                              *OemTableId,
  IN       AMD_CPM_ADDSSDTCALLBACK_FN          Function,
  IN       VOID                                *Context
  )
{
  CPM_ACPI_SUPPORT_PROTOCOL           *AcpiSupport;
  UINT8                               *AmlObjPtr;
  UINTN                               TableList;
  EFI_STATUS                          Status;
  EFI_GUID                            *EfiGuidPtr;
  EFI_HANDLE                          *HandleBuffer;
  UINTN                               NumberOfHandles;
  UINTN                               Index;
  CPM_FIRMWARE_VOLUME_PROTOCOL        *FwVol;
  UINTN                               Size;
  UINT32                              FvStatus;
  EFI_FV_FILETYPE                     FileType;
  EFI_FV_FILE_ATTRIBUTES              Attributes;
  INTN                                Instance;
  EFI_ACPI_COMMON_HEADER              *CurrentTable;
  UINT64                              TableId;
  UINT8                               IsAmdCpmSsdtSupport;

  DEBUG((DEBUG_INFO, "KER-DXE-%a-Start\n", __FUNCTION__));
  CurrentTable  = NULL;
  TableList     = 0;
  EfiGuidPtr    = (EFI_GUID*) EfiGuid;
  FwVol         = NULL;
  Size          = 0;
  IsAmdCpmSsdtSupport = AmdCpmSsdtSupport;

  switch (((AMD_CPM_TABLE_PROTOCOL*)This)->CommonFunction.GetCpuRevisionId (This)) {
  case CPM_CPU_REVISION_ID_AM:
    IsAmdCpmSsdtSupport = 0;
    break;
  }

  if (!IsAmdCpmSsdtSupport) {
    DEBUG((DEBUG_INFO, "KER-DXE-%a-End-1-EFI_UNSUPPORTED\n", __FUNCTION__));
    return EFI_UNSUPPORTED;
  }

  //
  // Locate protocol.
  // There is little chance we can't find an FV protocol
  //
  DEBUG((DEBUG_INFO, "KER-DXE-%a-LocateHandleBuffer-gCpmFirmwareVolumeProtocolGuid\n", __FUNCTION__));
  Status = gBS->LocateHandleBuffer (
                    ByProtocol,
                    &gCpmFirmwareVolumeProtocolGuid,
                    NULL,
                    &NumberOfHandles,
                    &HandleBuffer
                    );
  if (EFI_ERROR (Status)) {
    DEBUG((DEBUG_INFO, "KER-DXE-%a-End-2-Status=%r\n", __FUNCTION__, Status));
    return Status;
  }

  //
  // Looking for FV with ACPI storage file
  //
  for (Index = 0; Index < NumberOfHandles; Index++) {
    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    DEBUG((DEBUG_INFO, "KER-DXE-%a-HandleProtocol-HandleBuffer[Index=0x%X]\n", __FUNCTION__, Index));
    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gCpmFirmwareVolumeProtocolGuid,
                    (VOID**)&FwVol
                    );
    if (EFI_ERROR (Status)) {
      DEBUG((DEBUG_INFO, "KER-DXE-%a-End-3-Status=%r\n", __FUNCTION__, Status));
      return Status;
    }

    //
    // See if it has the ACPI storage file
    //
    Size     = 0;
    FvStatus = 0;
    DEBUG((DEBUG_INFO, "KER-DXE-%a-HandleProtocol-HandleBuffer[Index=0x%X]-FwVol->ReadFile\n", __FUNCTION__, Index));
    Status = FwVol->ReadFile (
                    FwVol,
                    EfiGuidPtr,
                    NULL,
                    &Size,
                    &FileType,
                    &Attributes,
                    &FvStatus
                    );

    //
    // If we found it, then we are done
    //
    if (Status == EFI_SUCCESS) {
      DEBUG((DEBUG_INFO, "KER-DXE-%a-HandleProtocol-HandleBuffer[Index=0x%X]-if (Status == EFI_SUCCESS)\n", __FUNCTION__, Index));
      break;
    }
  }

  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  //
  // Free any allocated buffers
  //
  DEBUG((DEBUG_INFO, "KER-DXE-%a-gBS->FreePool (HandleBuffer)\n", __FUNCTION__));
  gBS->FreePool (HandleBuffer);

  //
  // Sanity check that we found our data file
  //
  DEBUG((DEBUG_INFO, "KER-DXE-%a-ASSERT (FwVol)\n", __FUNCTION__));
  ASSERT (FwVol);

  //
  // Read tables from the storage file.
  //

  Instance     = 0;
  CurrentTable = NULL;

  while (Status == EFI_SUCCESS) {
    Status = FwVol->ReadSection (
                    FwVol,
                    EfiGuidPtr,
                    EFI_SECTION_RAW,
                    Instance,
                    (VOID**)&CurrentTable,
                    &Size,
                    &FvStatus
                    );

    if (!EFI_ERROR (Status)) {
      TableId = ((EFI_ACPI_DESCRIPTION_HEADER*) CurrentTable)->OemTableId;
      if (*((UINT32 *) CurrentTable) == 'TDSS' && (OemTableId ? TableId == *OemTableId: TRUE)) {
        if (Function) {
          for (AmlObjPtr = (UINT8*) CurrentTable + sizeof (EFI_ACPI_COMMON_HEADER); AmlObjPtr < ((UINT8*) CurrentTable) + Size; AmlObjPtr ++) {
            if ((*Function) (This, AmlObjPtr, Context)) {
              break;
            }
          }
        }
        break;
      }

      //
      // Increment the instance
      //
      Instance++;
      CurrentTable = NULL;
    }
  }

  DEBUG((DEBUG_INFO, "KER-DXE-%a-LocateProtocol-gCpmAcpiSupportGuid\n", __FUNCTION__));
  Status = gBS->LocateProtocol (
                    &gCpmAcpiSupportGuid,
                    NULL,
                    (VOID**)&AcpiSupport
                    );
  if (EFI_ERROR (Status)) {
    DEBUG((DEBUG_INFO, "KER-DXE-%a-End-4-Status=%r\n", __FUNCTION__, Status));
    return Status;
  }

  TableList = 0;

  //
  // Update OemId & OemTableId fields.
  //
  if (CurrentTable) {
    if (((EFI_ACPI_DESCRIPTION_HEADER*) CurrentTable)->OemTableId != PcdGet64 (PcdCpmIgnoreOemTableId)) {
      DEBUG((DEBUG_INFO, "KER-DXE-AmdCpmAddSsdtTable-Overwrite OemTableId\n", ((EFI_ACPI_DESCRIPTION_HEADER*) CurrentTable)->OemTableId));
      ((AMD_CPM_TABLE_PROTOCOL*)This)->CommonFunction.CopyMem (
        (VOID *) &((EFI_ACPI_DESCRIPTION_HEADER*) CurrentTable)->OemId,
        (VOID *) PcdGetPtr (PcdAmdAcpiTableHeaderOemId),
        AsciiStrnLenS (PcdGetPtr (PcdAmdAcpiTableHeaderOemId), 6)
        );

      ((AMD_CPM_TABLE_PROTOCOL*)This)->CommonFunction.CopyMem (
        (VOID *) &((EFI_ACPI_DESCRIPTION_HEADER*) CurrentTable)->OemTableId,
        (VOID *) PcdGetPtr (PcdAmdAcpiTableHeaderOemTableId),
        AsciiStrnLenS (PcdGetPtr (PcdAmdAcpiTableHeaderOemTableId), 8)
        );
    } else {
      DEBUG((DEBUG_INFO, "KER-DXE-AmdCpmAddSsdtTable-Don't overwrite OemTableId 0x%LX\n", ((EFI_ACPI_DESCRIPTION_HEADER*) CurrentTable)->OemTableId));
    }
  }

  DEBUG((DEBUG_INFO, "KER-DXE-%a-CpmSetAcpiTable\n", __FUNCTION__));
  CpmSetAcpiTable (AcpiSupport, CurrentTable, TRUE, AMD_CPM_ACPI_VERSION_SUPPORT, Size, TableList, Status);

  if (CurrentTable) {
    DEBUG((DEBUG_INFO, "KER-DXE-%a-gBS->FreePool (CurrentTable)\n", __FUNCTION__));
    Status = gBS->FreePool (CurrentTable);
  }

  DEBUG((DEBUG_INFO, "KER-DXE-%a-End-5-Status=%r\n", __FUNCTION__, Status));
  return  Status;
}

AGESA_STATUS
AmdCpmGetPostedVbiosImageNull (
  IN      GFX_VBIOS_IMAGE_INFO         *VbiosImageInfo
  )
{
  DEBUG((DEBUG_INFO, "KER-DXE-%a-return-AGESA_UNSUPPORTED\n", __FUNCTION__));
  return AGESA_UNSUPPORTED;
}


/*---------------------------------------------------------------------------------------*/
/**
 * Register Common Kenerl functions at the AmdCpmInitDxe entry point.
 *
 * This function registers CPM common kernel functions in AmdCpmTableProtocol
 * at AmdCpmInitDxe.
 *
 *  @param[in]   This                Pointer to Protocol.
 *
 */
VOID
EFIAPI
AmdCpmDxeRegisterKernel (
  IN       VOID                        *This
  )
{
  AMD_CPM_TABLE_PROTOCOL      *TableProtocolPtr = This;

  DEBUG((DEBUG_INFO, "KER-DXE-%a-Start\n", __FUNCTION__));
  TableProtocolPtr->CommonFunction.GetTablePtr            = CpmGetTablePtr;
  TableProtocolPtr->CommonFunction.GetTablePtr2           = CpmGetTablePtr2;
  TableProtocolPtr->CommonFunction.AddTable               = CpmAddTable;
  TableProtocolPtr->CommonFunction.RemoveTable            = CpmRemoveTable;
  TableProtocolPtr->CommonFunction.AddSsdtTable           = AmdCpmAddSsdtTable;
  TableProtocolPtr->CommonFunction.IsAmlOpRegionObject    = IsAmlOpRegionObject;
  TableProtocolPtr->CommonFunction.RelocateTable          = CpmRelocateTableList;
  TableProtocolPtr->CommonFunction.CopyMem                = CpmCopyMem;
  TableProtocolPtr->CommonFunction.ReadSmbus              = AmdCpmDxeSmbusGetByte;
  TableProtocolPtr->CommonFunction.WriteSmbus             = AmdCpmDxeSmbusSetByte;
  TableProtocolPtr->CommonFunction.ReadSmbusBlock         = AmdCpmDxeSmbusGetBlock;
  TableProtocolPtr->CommonFunction.WriteSmbusBlock        = AmdCpmDxeSmbusSetBlock;
  TableProtocolPtr->DxePublicFunction.GetPostedVbiosImage = AmdCpmGetPostedVbiosImageNull;

  DEBUG((DEBUG_INFO, "KER-DXE-%a-End\n", __FUNCTION__));
  return;
}
