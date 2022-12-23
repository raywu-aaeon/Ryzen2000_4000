/* $NoKeywords:$ */
/**
 * @file
 *
 * NbioTopMemRV - Set top of memory for NBIO
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  AmdNbioBaseRVPei
 * @e \$Revision: 312065 $   @e \$Date: 2015-01-30 04:23:05 -0600 (Fri, 30 Jan 2015) $
 *
 */
/*****************************************************************************
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
#include <AMD.h>
#include <PiPei.h>
#include <Filecode.h>
#include <GnbRegistersRV.h>
//#include <GnbDxio.h>
#include <Guid/GnbPcieInfoHob.h>
#include <Guid/AmdMemoryInfoHob.h>
#include <Library/BaseLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/HobLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/NbioRegisterAccLib.h>
#include <Library/NbioHandleLib.h>
#include <Ppi/NbioPcieServicesPpi.h>
#include <Ppi/AmdMemoryInfoHobPpi.h>


#define FILECODE  NBIO_NBIOBASE_AMDNBIOBASERVPEI_NBIOTOPMEMRV_FILECODE

/*----------------------------------------------------------------------------------------
 *                         E X T E R N   D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define SYSTEM_IA32_MAX_LINEAR_ADDRESS                         0xFFFFFFFF

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                    P P I   N O T I F Y   D E S C R I P T O R S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------*/
/**
 * Memory config complete callback
 * This function should use the information from memory config to initialize NBIO top of memory
 *
 *
 *
 * @param[in]  PeiServices        EFI_PEI_SERVICES pointer
 * @param[in]  NotifyDescriptor   EFI_PEI_NOTIFY_DESCRIPTOR pointer
 * @param[in]  Ppi                VOID pointer to the PPI that generated this callback
 * @retval     EFI_STATUS
 */

EFI_STATUS
EFIAPI
MemoryConfigDoneCallbackPpi (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  EFI_STATUS                      Status;
  GNB_HANDLE                      *GnbHandle;
  AMD_CONFIG_PARAMS               *StdHeader;
  EFI_PEI_HOB_POINTERS            Hob;
  AMD_MEMORY_INFO_HOB             *AmdMemoryInfoHob;
  UINT32                          Index;
  AMD_MEMORY_RANGE_DESCRIPTOR     *Range;
  PCIe_PLATFORM_CONFIG            *Pcie;
  PEI_AMD_NBIO_PCIE_SERVICES_PPI  *PcieServicesPpi;
  GNB_PCIE_INFORMATION_DATA_HOB   *PciePlatformConfigHob;
  UINT64                          MsrData;
  UINT64                          GnbTom2;
  UINT64                          GnbTom3;
  D0F0_090_STRUCT                 D0F0_090;
  NBMISC_0064_STRUCT              NBMISC_0064;
  NBMISC_0068_STRUCT              NBMISC_0068;
  NBMISC_0138_STRUCT              NBMISC_0138;
  UINT32                          MaxTOM;
  NB_MMIOBASE_STRUCT              NB_MMIOBASE;
  NB_MMIOLIMIT_STRUCT             NB_MMIOLIMIT;

  AGESA_TESTPOINT (TpMemoryConfigDoneCallbackPpiEntry, NULL);
  GnbHandle = NULL;
  StdHeader = NULL;
  MaxTOM = 0;
  // Need topology structure to get GnbHandle
  Status = (*PeiServices)->LocatePpi (
                             PeiServices,
                             &gAmdNbioPcieServicesPpiGuid,
                             0,
                             NULL,
                             (VOID **)&PcieServicesPpi
                             );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  PcieServicesPpi->PcieGetTopology (PcieServicesPpi, &PciePlatformConfigHob);
  Pcie = &(PciePlatformConfigHob->PciePlatformConfigHob);
  GnbHandle = NbioGetHandle (Pcie);

  // Read TOP_OF_DRAM registers
  NbioRegisterRead (GnbHandle, NB_TOP_OF_DRAM_SLOT1_TYPE, NB_TOP_OF_DRAM_SLOT1_ADDRESS, &D0F0_090.Value, 0);
  NbioRegisterRead (GnbHandle, NB_LOWER_TOP_OF_DRAM2_TYPE, NB_LOWER_TOP_OF_DRAM2_ADDRESS, &NBMISC_0064.Value, 0);
  NbioRegisterRead (GnbHandle, NB_UPPER_TOP_OF_DRAM2_TYPE, NB_UPPER_TOP_OF_DRAM2_ADDRESS, &NBMISC_0068.Value, 0);

  // In IOHC, program TOM3_ENABLE=1 and TOM3_LIMIT to 0x3FFFFFF in IOHCMISC0x00000138 (NB_TOP_OF_DRAM3).
  // This will force IOHC to see the full encrypted address space as part of the DRAM range.
  // Setting this should get IOMMU to start up.
  NBMISC_0138.Field.TOM3_LIMIT = 0x3FFFFFF;
  NBMISC_0138.Field.TOM3_ENABLE = 1;
  // Set MMIOBase and MMIOLimit to cover any MMIO that exists between 1TB and 128TB-1.
  // For example, if this entire range was MMIO (ie. System had 256GB of DRAM) set MMIOBase=0x100_0000 in
  // IOHCMISC0x0000005C (NB_MMIOBASE) and MMIOLimit=0x7FFF_FFFF in IOHCMISC0x00000060 (NB_MMIOLIMIT).
  // This should allow IOHC to see this range as a non-DRAM range and do proper p2p decoding again.
  NB_MMIOBASE.Value = 0x01000000;
  NB_MMIOLIMIT.Value = 0x7FFFFFFF;

  // Locate AMD_MEMORY_INFO_HOB
  AmdMemoryInfoHob = NULL;
  Status = PeiServicesGetHobList (&Hob.Raw);
  while (!END_OF_HOB_LIST (Hob)) {
    if (Hob.Header->HobType == EFI_HOB_TYPE_GUID_EXTENSION &&
        CompareGuid ( &Hob.Guid->Name, &gAmdMemoryInfoHobGuid)) {
      AmdMemoryInfoHob = (AMD_MEMORY_INFO_HOB *) (Hob.Raw +
                          sizeof (EFI_HOB_GENERIC_HEADER) +
                          sizeof (EFI_GUID));
      Status = EFI_SUCCESS;
      break;
    }
    Hob.Raw = GET_NEXT_HOB (Hob);
  }

  //Read memory size below 4G from MSR C001_001A
  MsrData = AsmReadMsr64 (TOP_MEM);

  if (AmdMemoryInfoHob != NULL) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "AMD_MEMORY_INFO_HOB at 0x%x\n", AmdMemoryInfoHob);
    IDS_HDT_CONSOLE (MAIN_FLOW, "  Version: 0x%x\n", AmdMemoryInfoHob->Version);
    IDS_HDT_CONSOLE (MAIN_FLOW, "  NumberOfDescriptor: 0x%x\n", AmdMemoryInfoHob->NumberOfDescriptor);
    for (Index = 0; Index < AmdMemoryInfoHob->NumberOfDescriptor; Index++) {
      Range = (AMD_MEMORY_RANGE_DESCRIPTOR*)&AmdMemoryInfoHob->Ranges[Index];
      IDS_HDT_CONSOLE (MAIN_FLOW, "  Range: %d\n", Index);
      IDS_HDT_CONSOLE (MAIN_FLOW, "    Base: 0x%x\n", Range->Base);
      IDS_HDT_CONSOLE (MAIN_FLOW, "    Size: 0x%x\n", Range->Size);
      IDS_HDT_CONSOLE (MAIN_FLOW, "    Attribute: 0x%x\n", Range->Attribute);
      if ((Range->Attribute != AMD_MEMORY_ATTRIBUTE_MMIO) && (Range->Base < SYSTEM_IA32_MAX_LINEAR_ADDRESS)) {
        if (MaxTOM < (Range->Base + Range->Size)) {
          MaxTOM =(UINT32)(Range->Base + Range->Size);
        }
      }
    }
    D0F0_090.Field.TOP_OF_DRAM = ((UINT32)MaxTOM & 0xFF800000) >> 23;     //Keep bits 31:23
  } else {
    // AMD_MEMORY_INFO_HOB was not located - use MSR register as temporary workaround
    IDS_HDT_CONSOLE (MAIN_FLOW, "AmdMemoryInfoHob NOT FOUND!!\n");
    //Write to NB register 0x90
    D0F0_090.Field.TOP_OF_DRAM = ((UINT32)MsrData & 0xFF800000) >> 23;     //Keep bits 31:23
  }

  IDS_HDT_CONSOLE (MAIN_FLOW, "Hob:TOP_MEM is 0x%x D0F0_090[31:23,TOP_OF_DRAM] is 0x%x\n", MaxTOM, D0F0_090.Field.TOP_OF_DRAM);
  IDS_HDT_CONSOLE (MAIN_FLOW, "MSR:TOP_MEM is 0x%x [31:23,TOP_OF_DRAM] is 0x%x\n", (UINT32) MsrData, ((UINT32)MsrData & 0xFF800000) >> 23);

  ///@todo - temporary solution until memory HOB contains TOM information
  GnbTom2 = 0;
  GnbTom3 = 0;
  MsrData = AsmReadMsr64 (SYS_CFG);
  if ((MsrData & BIT21) != 0) {
    //If SYS_CFG(MtrrTom2En) then configure GNB TOM2 and TOM3
    //Read memory size above 4G from TOP_MEM2 (MSR C001_001D)
    MsrData = AsmReadMsr64 (TOP_MEM2);
    IDS_HDT_CONSOLE (GNB_TRACE, "MSR TOP_MEM2[63:32] is 0x%08x\n", RShiftU64 (MsrData, 32));
    IDS_HDT_CONSOLE (GNB_TRACE, "MSR TOP_MEM2[31:0] is 0x%08x\n", MsrData);
    if ((MsrData & (UINT64)0x0000FFFFFFC00000) > ((UINT64)0x0000010000000000)) {
      // If TOP_MEM2 is above 1TB, enable GNB TOM2 and TOM3
      // Set TOM2 for below 1TB limit
      GnbTom2 = 0x000000FD00000000;
      // TOM3 is INCLUSIVE, so set it to TOM - 1 using bits 47:22
      GnbTom3 = (MsrData - 1) & (UINT64)0x0000FFFFFFC00000;
    } else {
      // If TOP_MEM2 is below 1TB, set TOM2 using bits 39:22
      GnbTom2 = MsrData & (UINT64)0x000000FFFFC00000;       //Keep bits 39:22
      // If TOP_MEM2 is below 1TB, disable GNB TOM3
      GnbTom3 = 0;
    }
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbSetTomRV setting GnbTom2 to 0x%x\n", GnbTom2);
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbSetTomRV setting GnbTom3 to 0x%x\n", GnbTom3);
  if (GnbTom2 != 0) {
    // Write memory size[39:32] to indirect register 1A[7:0]
    NBMISC_0068.Field.UPPER_TOM2 = (UINT32) (RShiftU64 (GnbTom2, 32) & 0xFF);
    // Write memory size[31:23] to indirect register 19[31:23] and enable memory through bit 0
    NBMISC_0064.Field.LOWER_TOM2 = ((UINT32)GnbTom2 & 0xFF800000) >> 23;
    NBMISC_0064.Field.ENABLE = 1;
  }

  if (GnbTom3 != 0) {
    // Above 1TB addressing TOM3 if MSR TOM is above 1TB
    // Write memory size[47:16] to NB_MMIOBASE[31:0]
    NB_MMIOBASE.Value = (UINT32) RShiftU64 (GnbTom3, 16);
    // Set TOM2 to all 1's
    NBMISC_0068.Field.UPPER_TOM2 = 0x1FF;
    NBMISC_0064.Field.LOWER_TOM2 = 0x1FF;
    NBMISC_0064.Field.ENABLE = 1;

  }
    // Write TOP_OF_DRAM registers
  NbioRegisterWrite (GnbHandle, NB_TOP_OF_DRAM_SLOT1_TYPE, NB_TOP_OF_DRAM_SLOT1_ADDRESS, &D0F0_090.Value, 0);
  NbioRegisterWrite (GnbHandle, NB_LOWER_TOP_OF_DRAM2_TYPE, NB_LOWER_TOP_OF_DRAM2_ADDRESS, &NBMISC_0064.Value, 0);
  NbioRegisterWrite (GnbHandle, NB_UPPER_TOP_OF_DRAM2_TYPE, NB_UPPER_TOP_OF_DRAM2_ADDRESS, &NBMISC_0068.Value, 0);
  NbioRegisterWrite (GnbHandle, NB_TOP_OF_DRAM3_TYPE, NB_TOP_OF_DRAM3_ADDRESS, &NBMISC_0138.Value, 0);
  NbioRegisterWrite (GnbHandle, NB_MMIOBASE_TYPE, NB_MMIOBASE_ADDRESS, &NB_MMIOBASE.Value, 0);
  NbioRegisterWrite (GnbHandle, NB_MMIOLIMIT_TYPE, NB_MMIOLIMIT_ADDRESS, &NB_MMIOLIMIT.Value, 0);
  NbioRegisterRMW (GnbHandle,
                   NB_PCI_CTRL_TYPE,
                   NB_PCI_CTRL_ADDRESS,
                   (UINT32) ~(NB_PCI_CTRL_MMIOEnable_MASK),
                   (1 << NB_PCI_CTRL_MMIOEnable_OFFSET),
                   0
                   );

  AGESA_TESTPOINT (TpMemoryConfigDoneCallbackPpiExit, NULL);
  return EFI_SUCCESS;
}




