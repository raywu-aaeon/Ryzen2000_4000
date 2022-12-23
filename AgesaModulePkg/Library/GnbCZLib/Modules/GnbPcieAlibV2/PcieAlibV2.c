/* $NoKeywords:$ */
/**
 * @file
 *
 * PCIe ALIB
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
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
#include  "Library/AmdHeapLib.h"
#include  "GnbFamServices.h"
#include  "GnbPcie.h"
#include  "GnbPcieFamServices.h"
#include  "GnbCommonLib.h"
#include  "GnbPcieConfig.h"
#include  "GnbPcieInitLib.h"
#include  "OptionGnb.h"
#include  "PcieAlibV2.h"
#include  "GnbFuseTable.h"
#include  <cpuRegisters.h>
#include  "PiDxe.h"
#include  <Protocol/AcpiTable.h>
#include  <Library/UefiBootServicesTableLib.h>
#include  <Library/BaseLib.h>

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBPCIEALIBV2_PCIEALIBV2_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

extern  GNB_BUILD_OPTIONS ROMDATA GnbBuildOptions;


/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */


AGESA_STATUS
PcieAlibUpdateGnbData (
  IN OUT   VOID                  *SsdtBuffer,
  IN       AMD_CONFIG_PARAMS     *StdHeader
  );

VOID
STATIC
PcieAlibUpdatePciePortDataCallback (
  IN       PCIe_ENGINE_CONFIG     *Engine,
  IN OUT   VOID                   *Buffer,
  IN       PCIe_PLATFORM_CONFIG   *Pcie
  );


AGESA_STATUS
PcieAlibBuildAcpiTableV2 (
  IN       AMD_CONFIG_PARAMS      *StdHeader,
     OUT   VOID                   **AlibSsdtPtr
  );

AGESA_STATUS
PcieAlibUpdateVoltageData (
  IN OUT   VOID                  *DataBuffer,
  IN       AMD_CONFIG_PARAMS     *StdHeader
  );

AGESA_STATUS
PcieAlibUpdatePcieData (
  IN OUT   VOID                  *DataBuffer,
  IN       AMD_CONFIG_PARAMS     *StdHeader
  );


/*----------------------------------------------------------------------------------------*/
/**
 * Create ACPI ALIB SSDT table
 *
 *
 *
 * @param[in] StdHeader           Standard configuration header
 * @retval    AGESA_STATUS
 */

AGESA_STATUS
PcieAlibV2Feature (
  IN       AMD_CONFIG_PARAMS    *StdHeader
  )
{
  AMD_LATE_PARAMS *LateParamsPtr;
  LateParamsPtr = (AMD_LATE_PARAMS*) StdHeader;
  return PcieAlibBuildAcpiTableV2 (StdHeader, &LateParamsPtr->AcpiAlib);
}

/*----------------------------------------------------------------------------------------*/
/**
 * Checksum Acpi Table
 *
 *
 *
 * @param[in] Table               Acpi Table
 * @param[in] StdHeader           Standard configuration header
 * @retval    AGESA_STATUS
 */

VOID
PcieAlibChecksumAcpiTable (
  IN OUT   ACPI_TABLE_HEADER *Table,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT8  *BuffTempPtr;
  UINT8  Checksum;
  UINT32 BufferOffset;

  Table->Checksum = 0;
  Checksum = 0;
  BuffTempPtr = (UINT8 *) Table;
  for (BufferOffset = 0; BufferOffset < Table->TableLength; BufferOffset++) {
    Checksum = Checksum - *(BuffTempPtr + BufferOffset);
  }

  Table->Checksum = Checksum;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Build ALIB ACPI table
 *
 *
 *
 * @param[in]     StdHeader       Standard Configuration Header
 * @param[in,out] AlibSsdtPtr     Pointer to pointer to ALIB SSDT table
 * @retval        AGESA_SUCCESS
 * @retval        AGESA_ERROR
 */

AGESA_STATUS
PcieAlibBuildAcpiTableV2 (
  IN       AMD_CONFIG_PARAMS    *StdHeader,
     OUT   VOID                 **AlibSsdtPtr
  )
{
  AGESA_STATUS            Status;
  AGESA_STATUS            AgesaStatus;
  VOID                    *AlibSsdtBuffer;
  VOID                    *AlibSsdtTable;
  UINTN                   AlibSsdtlength;
  UINT32                  AmlObjName;
  VOID                    *AmlObjPtr;
  EFI_ACPI_TABLE_PROTOCOL *AcpiTable;
  UINTN                   TableHandle;

  TableHandle = 0;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieAlibBuildAcpiTableV2 Enter\n");
  AgesaStatus = AGESA_SUCCESS;
  AlibSsdtTable = GnbFmAlibGetBaseTable (StdHeader);
  AlibSsdtlength = ((ACPI_TABLE_HEADER*) AlibSsdtTable)->TableLength;
  if (*AlibSsdtPtr == NULL) {
    AlibSsdtBuffer = GnbAllocateHeapBuffer (
                       AMD_ACPI_ALIB_BUFFER_HANDLE,
                       AlibSsdtlength,
                       StdHeader
                       );
    ASSERT (AlibSsdtBuffer != NULL);
    if (AlibSsdtBuffer == NULL) {
      return  AGESA_ERROR;
    }
    *AlibSsdtPtr = AlibSsdtBuffer;
  } else {
    AlibSsdtBuffer = *AlibSsdtPtr;
  }
  // Check length of port data
  ASSERT (sizeof (_ALIB_PORT_DATA) <= 20);
  // Check length of global data
  ASSERT (sizeof (_ALIB_GLOBAL_DATA) <= 32);
  // Copy template to buffer
  LibAmdMemCopy (AlibSsdtBuffer, AlibSsdtTable, AlibSsdtlength, StdHeader);
  // Update table OEM fields.
  LibAmdMemCopy (
    (VOID *) &((ACPI_TABLE_HEADER*) AlibSsdtBuffer)->OemId,
    (VOID *) &GnbBuildOptions.OemIdString,
    sizeof (GnbBuildOptions.OemIdString),
    StdHeader);
  LibAmdMemCopy (
    (VOID *) &((ACPI_TABLE_HEADER*) AlibSsdtBuffer)->OemTableId,
    (VOID *) &GnbBuildOptions.OemTableIdString,
    sizeof (GnbBuildOptions.OemTableIdString),
    StdHeader);
  //
  // Update register base base
  //
  PcieAlibUpdateGnbData (AlibSsdtBuffer, StdHeader);
  //
  // Update transfer block
  //
  AmlObjName = STRING_TO_UINT32 ('A', 'D', 'A', 'T');
  AmlObjPtr = GnbLibFind (AlibSsdtBuffer, AlibSsdtlength, (UINT8*) &AmlObjName, sizeof (AmlObjName));
  if (AmlObjPtr != NULL) {
    AmlObjPtr = (UINT8 *) AmlObjPtr + 10;
  }
  // Dispatch function from table
  Status = PcieAlibUpdateVoltageData (AmlObjPtr, StdHeader);
  Status = PcieAlibUpdatePcieData (AmlObjPtr, StdHeader);

  AGESA_STATUS_UPDATE (Status, AgesaStatus);
  if (AgesaStatus != AGESA_SUCCESS) {
    //Shrink table length to size of the header
    ((ACPI_TABLE_HEADER*) AlibSsdtBuffer)->TableLength = sizeof (ACPI_TABLE_HEADER);
  }
  PcieAlibChecksumAcpiTable ((ACPI_TABLE_HEADER*) AlibSsdtBuffer, StdHeader);
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieAlibBuildAcpiTableV2 Exit [0x%x]\n", AgesaStatus);

  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **)&AcpiTable);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = AcpiTable->InstallAcpiTable (AcpiTable, AlibSsdtBuffer, ((ACPI_TABLE_HEADER*) AlibSsdtBuffer)->TableLength, &TableHandle);

  return AgesaStatus;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Update MMIO info
 *
 *
 *
 *
 * @param[in] SsdtBuffer          Pointer to SSDT table
 * @param[in] StdHeader           Standard configuration header
 */

AGESA_STATUS
PcieAlibUpdateGnbData (
  IN OUT   VOID                  *SsdtBuffer,
  IN       AMD_CONFIG_PARAMS     *StdHeader
  )
{
  UINT64        LocalMsrRegister;
  UINT32        AmlObjName;
  VOID          *AmlObjPtr;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieAlibUpdateGnbData Enter\n");
  //
  //  Locate Base address variable
  //
  AmlObjName = STRING_TO_UINT32 ('A', 'G', 'R', 'B');
  AmlObjPtr = GnbLibFind (
                SsdtBuffer,
                ((ACPI_TABLE_HEADER*) SsdtBuffer)->TableLength,
                (UINT8*) &AmlObjName,
                sizeof (AmlObjName)
                );
  // ASSERT (AmlObjPtr != NULL);
  if (AmlObjPtr == NULL) {
    return AGESA_ERROR;
  }
  //
  //  Update PCIe MMIO base
  //
  LocalMsrRegister = AsmReadMsr64 (MSR_MMIO_Cfg_Base);
  if ((LocalMsrRegister & BIT0) != 0 && (LocalMsrRegister & 0xFFFFFFFF00000000) == 0) {
    *(UINT32*)((UINT8*) AmlObjPtr + 5) = (UINT32) (LocalMsrRegister & 0xFFFFF00000);
  } else {
    ASSERT (FALSE);
    return AGESA_ERROR;
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieAlibUpdateGnbData Exit\n");
  return AGESA_SUCCESS;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Update MMIO info
 *
 *
 *
 *
 * @param[in] DataBuffer          Pointer to data buffer
 * @param[in] StdHeader           Standard configuration header
 */

AGESA_STATUS
PcieAlibUpdateVoltageData (
  IN OUT   VOID                  *DataBuffer,
  IN       AMD_CONFIG_PARAMS     *StdHeader
  )
{
  PP_FUSE_ARRAY_V2   *PpFuseArray;
  AGESA_STATUS    Status;
  ALIB_DATA       *AlibData;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieAlibUpdateVoltageData Enter\n");
  Status = AGESA_SUCCESS;
  ASSERT (DataBuffer != NULL);
  AlibData = (ALIB_DATA *) DataBuffer;
  //
  //  Locate Fuse table
  //
  PpFuseArray = GnbLocateHeapBuffer (AMD_PP_FUSE_TABLE_HANDLE, StdHeader);
  ASSERT (PpFuseArray != NULL);
  if (PpFuseArray != NULL) {
    //
    //  Update GEN1 Vid
    //
    AlibData->Data.Data.PcieVidGen1 = PpFuseArray->VddNbVid[0];
    IDS_HDT_CONSOLE (GNB_TRACE, "  PcieVidGen1 = %x\n", AlibData->Data.Data.PcieVidGen1);
    //
    //  Update GEN2 Vid
    //
    AlibData->Data.Data.PcieVidGen2 = PpFuseArray->VddNbVid[PpFuseArray->PcieGen2Vid];
    IDS_HDT_CONSOLE (GNB_TRACE, "  PcieVidGen2 = %x\n", AlibData->Data.Data.PcieVidGen2);
    //
    //  Update GEN3 Vid
    //
    AlibData->Data.Data.PcieVidGen3 = PpFuseArray->VddNbVid[PpFuseArray->PcieGen3Vid];
    IDS_HDT_CONSOLE (GNB_TRACE, "  PcieVidGen3 = %x\n", AlibData->Data.Data.PcieVidGen3);
    //
    //  Update DPM Mask
    //
    AlibData->Data.Data.DpmMask = (PpFuseArray->PerfFlag + 1);
    IDS_HDT_CONSOLE (GNB_TRACE, "  DpmMask = %02x\n", AlibData->Data.Data.DpmMask);
    //
    //  Update Boost data
    //
    AlibData->Data.Data.NumBoostStates = (PpFuseArray->NumBoostStates);
    IDS_HDT_CONSOLE (GNB_TRACE, "  NumBoost = %02x\n", AlibData->Data.Data.NumBoostStates);
  } else {
    Status = AGESA_ERROR;
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieAlibUpdateVoltageData Exit\n");
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Update PCIe info
 *
 *
 *
 *
 * @param[in] DataBuffer          Ponter to data buffer
 * @param[in] StdHeader           Standard configuration header
 */

AGESA_STATUS
PcieAlibUpdatePcieData (
  IN OUT   VOID                  *DataBuffer,
  IN       AMD_CONFIG_PARAMS     *StdHeader
  )
{
  PCIe_PLATFORM_CONFIG       *Pcie;
  AGESA_STATUS               Status;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieAlibUpdatePcieData Enter\n");
  ASSERT (DataBuffer != NULL);
  Status = AGESA_SUCCESS;

  //
  //  Locate PCIe platform config
  //
  if (PcieLocateConfigurationData (StdHeader, &Pcie) == AGESA_SUCCESS) {
    //
    // Update policy data
    //
    ((ALIB_DATA *) DataBuffer)->Data.Data.PsppPolicy = Pcie->PsppPolicy;
    IDS_HDT_CONSOLE (GNB_TRACE, "  PsppPolicy = %x\n", Pcie->PsppPolicy);
    //
    // Update data for each port
    //
    PcieConfigRunProcForAllEngines (
      DESCRIPTOR_PCIE_ENGINE,
      PcieAlibUpdatePciePortDataCallback,
      DataBuffer,
      Pcie
      );
  } else {
    ASSERT (FALSE);
    Status = AGESA_FATAL;
  }

  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback to update PCIe port data
 *
 *
 *
 *
 * @param[in]       Engine          Pointer to engine config descriptor
 * @param[in, out]  Buffer          Not used
 * @param[in]       Pcie            Pointer to global PCIe configuration
 *
 */

VOID
STATIC
PcieAlibUpdatePciePortDataCallback (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  _ALIB_PORT_DATA *PortData;

  PortData = &((ALIB_DATA *) Buffer)->PortData[Engine->Type.Port.PcieBridgeId].PortData;

  if (PcieConfigIsEngineAllocated (Engine) && (Engine->Type.Port.PortData.LinkHotplug != HotplugDisabled || PcieConfigCheckPortStatus (Engine, INIT_STATUS_PCIE_TRAINING_SUCCESS))) {
    //
    // Various speed capability
    //
    IDS_HDT_CONSOLE (GNB_TRACE, "  Engine->Type.Port.PcieBridgeId = %x\n", Engine->Type.Port.PcieBridgeId);
    PortData->PciePortMaxSpeed = (UINT8) PcieFmGetLinkSpeedCap (PCIE_PORT_GEN_CAP_MAX, Engine);
    PortData->PciePortCurSpeed = (UINT8) PcieFmGetLinkSpeedCap (PCIE_PORT_GEN_CAP_BOOT, Engine);
    PortData->PciePortDcSpeed = PcieGen1;
    PortData->PciePortAcSpeed = PortData->PciePortMaxSpeed;
    if (Pcie->PsppPolicy == PsppBalanceLow) {
      PortData->PciePortAcSpeed = PcieGen1;
    }
    if (PcieConfigIsSbPcieEngine (Engine)) {
      PortData->PcieSbPort = 0x1;
      PortData->PciePortAcSpeed = PortData->PciePortMaxSpeed;
    }
    if (Engine->Type.Port.PortData.MiscControls.LinkSafeMode != 0) {
      PortData->PcieLinkSafeMode = 0x1;
      PortData->PcieLocalOverrideSpeed = Engine->Type.Port.PortData.MiscControls.LinkSafeMode;
    }
    IDS_HDT_CONSOLE (GNB_TRACE, "  PortData->PciePortMaxSpeed = %x\n", PortData->PciePortMaxSpeed);
    IDS_HDT_CONSOLE (GNB_TRACE, "  PortData->PciePortCurSpeed = %x\n", PortData->PciePortCurSpeed);
    IDS_HDT_CONSOLE (GNB_TRACE, "  PortData->PciePortDcSpeed = %x\n", PortData->PciePortDcSpeed);
    IDS_HDT_CONSOLE (GNB_TRACE, "  PortData->PciePortAcSpeed = %x\n", PortData->PciePortAcSpeed);

    //
    // various port capability
    //
    PortData->StartPhyLane = (UINT8) Engine->EngineData.StartLane;
    PortData->EndPhyLane = (UINT8) Engine->EngineData.EndLane;
    PortData->StartCoreLane = (UINT8) Engine->Type.Port.StartCoreLane;
    PortData->EndCoreLane = (UINT8) Engine->Type.Port.EndCoreLane;
    PortData->PortId = Engine->Type.Port.PortId;
    PortData->LinkHotplug = Engine->Type.Port.PortData.LinkHotplug;
    PortData->PciDev = (UINT8) Engine->Type.Port.Address.Address.Device;
    PortData->PciFun = (UINT8) Engine->Type.Port.Address.Address.Function;
    IDS_HDT_CONSOLE (GNB_TRACE, "  PortData->StartPhyLane = %x\n", PortData->StartPhyLane);
    IDS_HDT_CONSOLE (GNB_TRACE, "  PortData->EndPhyLane = %x\n", PortData->EndPhyLane);
    IDS_HDT_CONSOLE (GNB_TRACE, "  PortData->StartCoreLane = %x\n", PortData->StartCoreLane);
    IDS_HDT_CONSOLE (GNB_TRACE, "  PortData->EndCoreLane = %x\n", PortData->EndCoreLane);
    IDS_HDT_CONSOLE (GNB_TRACE, "  PortData->PortId = %x\n", PortData->PortId);
    IDS_HDT_CONSOLE (GNB_TRACE, "  PortData->LinkHotplug = %x\n", PortData->LinkHotplug);
    IDS_HDT_CONSOLE (GNB_TRACE, "  PortData->PciDev = %x\n", PortData->PciDev);
    IDS_HDT_CONSOLE (GNB_TRACE, "  PortData->PciFun = %x\n", PortData->PciFun);

  } else {
    PortData->PciePortMaxSpeed = PcieGen1;
    PortData->PciePortCurSpeed = PcieGen1;
    PortData->PciePortDcSpeed  = PcieGen1;
    PortData->PciePortAcSpeed  = PcieGen1;
    PortData->PcieLocalOverrideSpeed = PcieGen1;
    IDS_HDT_CONSOLE (GNB_TRACE, "  Engine->Type.Port.PcieBridgeId = %x not allocated or non-hotplug\n", Engine->Type.Port.PcieBridgeId);

  }
}


