/* $NoKeywords:$ */
/**
 * @file
 *
 * FCH PEI LIBRARY
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project   FCH PEI LIBRARY
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 10:28:05 -0800 (Tue, 09 Dec 2014) $
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
#include "PiPei.h"

#include <Library/FchPeiLib.h>
#define FILECODE UEFI_PEI_FCHPEILIB_FCHPEILIB_FILECODE

#define FCH_IOMAP_REGCD6 0xcd6
#define FCH_IOMAP_REGCD7 0xcd7
/*********************************************************************************
 * Name: LibFchMemRead8
 *
 * Description
 *   Read 8-bit data from memory
 *
 * Input
 *   PeiServices : a pointer to the PEI service table pointer
 *   Address     : Memory address
 *
 * Output
 *   the read data
 *
 *********************************************************************************/
UINT8
LibFchMemRead8 (
  IN CONST EFI_PEI_SERVICES  **PeiServices,
  IN       UINT64            Address
  )
{
  EFI_PEI_CPU_IO_PPI            *CpuIo;
  UINT8                Data;

  CpuIo = (*PeiServices)->CpuIo;
  Data = CpuIo->MemRead8 (
                  PeiServices,
                  CpuIo,
                  Address
                  );
  return (Data);
}


/*********************************************************************************
 * Name: LibFchMemWrite8
 *
 * Description
 *   Read 8-bit data from memory
 *
 * Input
 *   PeiServices : a pointer to the PEI service table pointer
 *   Address     : Memory address
 *
 * Output
 *   the read data
 *
 *********************************************************************************/
VOID
LibFchMemWrite8 (
  IN CONST EFI_PEI_SERVICES  **PeiServices,
  IN       UINT64            Address,
  IN       UINT8             *Value
  )
{
  EFI_PEI_CPU_IO_PPI            *CpuIo;

  CpuIo = (*PeiServices)->CpuIo;
  CpuIo->MemWrite8 (
           PeiServices,
           CpuIo,
           Address,
           *Value
           );
}


VOID
LibFchMemRMW8 (
  IN CONST EFI_PEI_SERVICES  **PeiServices,
  IN       UINT64            Address,
  IN       UINT8             AndMask,
  IN       UINT8             OrMask
  )
{
  EFI_PEI_CPU_IO_PPI   *CpuIo;
  UINT8                Data;

  CpuIo = (*PeiServices)->CpuIo;
  Data = CpuIo->MemRead8 (
                  PeiServices,
                  CpuIo,
                  Address
                  );
  Data &= AndMask;
  Data |= OrMask;
  CpuIo->MemWrite8 (
           PeiServices,
           CpuIo,
           Address,
           Data
           );
}


/*********************************************************************************
 * Name: LibFchPmIoRead8
 *
 * Description
 *   Read 8 bits from the PMIO space using CD6/CD7
 *
 * Input
 *   PeiServices : a pointer to the PEI service table pointer
 *   RegIndex    : the register to read from
 *
 * Output
 *   the read data
 *
 *********************************************************************************/
UINT8
LibFchPmIoRead8 (
  IN CONST EFI_PEI_SERVICES  **PeiServices,
  IN       UINT8             RegIndex
  )
{
  EFI_PEI_CPU_IO_PPI   *CpuIo;
  UINT8                Data;

  // get the CpuIo pointer
  CpuIo = (*PeiServices)->CpuIo;

  // perform the read
  CpuIo->IoWrite8 (
           PeiServices,
           CpuIo,
           FCH_IOMAP_REGCD6,
           RegIndex
           );

  Data = CpuIo->IoRead8 (
                  PeiServices,
                  CpuIo,
                  FCH_IOMAP_REGCD7
                  );

  return (Data);
}


/*********************************************************************************
 * Name: LibFchPmIoRead16
 *
 * Description
 *   Read 16 bits from the PMIO space using CD6/CD7
 *
 * Input
 *   PeiServices : a pointer to the PEI service table pointer
 *   RegIndex    : the register to read from
 *
 * Output
 *   the read data
 *
 *********************************************************************************/
UINT16
LibFchPmIoRead16 (
  IN CONST EFI_PEI_SERVICES  **PeiServices,
  IN       UINT8             RegIndex
  )
{
  UINT16               Data;

  // get the data using two 1 byte read
  Data  = LibFchPmIoRead8 (PeiServices, RegIndex);
  Data |= (LibFchPmIoRead8 (PeiServices, RegIndex + 1) << 8);

  return (Data);
}

/*---------------------------------------------------------------------------------------*/
/**
 * LibFchGetAcpiMmio - Get AGESA FCH ACPIMMIO Address
 *
 * @param[in]      PeiServices   EFI_PEI_SERVICE
 *
 */
UINT32
LibFchGetAcpiMmio (
  IN CONST EFI_PEI_SERVICES  **PeiServices
  )
{
  UINT32      AcpiMmioAddr;

  AcpiMmioAddr = 0xFED80000;
  return (AcpiMmioAddr);
}

/*---------------------------------------------------------------------------------------*/
/**
 * LibFchPciCfgRead - FCH Read PCI Configuration space
 *
 * @param[in]      PeiServices   EFI_PEI_SERVICE
 * @param[in]      Width         PCI Cfg Read lenght
 * @param[in]      Address       PCI Cfg Read Address
 * @param[in]      Value         Return Read value buffer
 *
 */
VOID
LibFchPciCfgRead (
  IN       CONST EFI_PEI_SERVICES         **PeiServices,
  IN       EFI_PEI_PCI_CFG_PPI_WIDTH      Width,
  IN       UINT64                         Address,
  IN OUT   VOID                           *Value
  )
{
  EFI_PEI_PCI_CFG2_PPI            *PciCfg;

  PciCfg = ( EFI_PEI_PCI_CFG2_PPI* ) (*PeiServices)->PciCfg;
  PciCfg->Read (
            PeiServices,
            PciCfg,
            Width,
            Address,
            Value
            );
}

/*---------------------------------------------------------------------------------------*/
/**
 * LibFchPciCfgWrite - FCH Write PCI Configuration space
 *
 * @param[in]      PeiServices   EFI_PEI_SERVICE
 * @param[in]      Width         PCI Cfg Write lenght
 * @param[in]      Address       PCI Cfg Write Address
 * @param[in]      Value         Return Write value buffer
 *
 */
VOID
LibFchPciCfgWrite (
  IN       CONST EFI_PEI_SERVICES   **PeiServices,
  IN       EFI_PEI_PCI_CFG_PPI_WIDTH Width,
  IN       UINT64                   Address,
  IN OUT   VOID                     *Value
  )
{
  EFI_PEI_PCI_CFG2_PPI            *PciCfg;

  PciCfg = ( EFI_PEI_PCI_CFG2_PPI* ) (*PeiServices)->PciCfg;
  PciCfg->Write (
            PeiServices,
            PciCfg,
            Width,
            Address,
            Value
            );
}

/*---------------------------------------------------------------------------------------*/
/**
 * LibFchPciCfgModify - FCH Modify PCI Configuration space
 *
 * @param[in]      PeiServices   EFI_PEI_SERVICE
 * @param[in]      Width         PCI Cfg modify lenght
 * @param[in]      Address       PCI Cfg modify Address
 * @param[in]      SetBits       Set PCI Cfg Register bitmap
 * @param[in]      ClearBits     Clear PCI Cfg Register bitmap
 *
 */
VOID
LibFchPciCfgModify (
  IN CONST EFI_PEI_SERVICES         **PeiServices,
  IN       EFI_PEI_PCI_CFG_PPI_WIDTH Width,
  IN       UINT64                   Address,
  IN       UINTN                    SetBits,
  IN       UINTN                    ClearBits
  )
{
  EFI_PEI_PCI_CFG2_PPI            *PciCfg;

  PciCfg = ( EFI_PEI_PCI_CFG2_PPI* ) (*PeiServices)->PciCfg;
  PciCfg->Modify (
            PeiServices,
            PciCfg,
            Width,
            Address,
            &SetBits,
            &ClearBits
            );
}

