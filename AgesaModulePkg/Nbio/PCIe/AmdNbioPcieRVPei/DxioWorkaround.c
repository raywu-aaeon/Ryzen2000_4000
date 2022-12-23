/* $NoKeywords:$ */
/**
 * @file
 *
 * GNB early ABL initialization.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 276746 $   @e \$Date: 2014-10-28 12:22:52 -0600 (Mon, 28 Oct 2013) $
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
#include <AMD.h>
#include <Gnb.h>
#include <PiPei.h>
#include <Filecode.h>
#include <CcxRegistersZp.h>
#include <AmdPcieComplex.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/NbioHandleLib.h>
#include <Library/NbioRegisterAccLib.h>
#include <Library/TimerLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PcieConfigLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/GnbMemAccLib.h>
#include <Ppi/NbioPcieComplexPpi.h>


#define FILECODE NBIO_PCIE_AMDNBIOPCIEZPPEI_DXIOWORKAROUND_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

#define CFG_1X16                0
#define CFG_2X8                 1

#define PCIE_MEMORY_WIDTH       CFG_2X8

#define GEN3                    3
#define GEN2                    2

#define PCIE_MEMORY_SPEED       GEN3

// Define optional configuration here
#define DEVICE_HIDE_USB         FALSE
#define DEVICE_HIDE_NTB         TRUE

#define DEVICE_HIDE_NBIF1       FALSE
#define DEVICE_HIDE_SATA_DIE0   FALSE
#define DEVICE_HIDE_SATA_DIE1   FALSE
#define DEVICE_HIDE_AUDIO       FALSE
#define DEVICE_HIDE_XGBE        FALSE

// From pspsmc.h
// SMU Response Codes:
#define PSPSMC_Result_OK                    0x1
#define PSPSMC_Result_Failed                0xFF
#define PSPSMC_Result_UnknownCmd            0xFE
#define PSPSMC_Result_CmdRejectedPrereq     0xFD
#define PSPSMC_Result_CmdRejectedBusy       0xFC


// Message Definitions:
#define PSPSMC_MSG_TestMessage               0x1
#define PSPSMC_MSG_GetSmuVersion             0x2
#define PSPSMC_MSG_GetBiosIfVersion          0x3
#define PSPSMC_MSG_ConfigureWaflLinks        0x4
#define PSPSMC_MSG_QueryReadyDramTraining    0x5
#define PSPSMC_MSG_SetSharedDramAddress      0x6
#define PSPSMC_MSG_ConfigSocRail             0x7
#define PSPSMC_MSG_ChipSetAuthenticated      0x8
#define PSPSMC_MSG_DxioStartScanCapabilities 0x9
#define PSPSMC_MSG_SetVddpCldoBypassModes    0xA
#define PSPSMC_MSG_SetVddmCldoBypassModes    0xB
#define PSPSMC_MSG_SetVddpVoltage            0xC
#define PSPSMC_MSG_SetVddmVoltage            0xD
#define PSPSMC_MSG_CheckSocketCompatibility  0xE
#define PSPSMC_MSG_ConfigPcieMemoryInterface 0xF
#define PSPSMC_MSG_SwitchToStartupDfPstate   0x10

#define PSPSMC_MSG_DxioEarlyInit             0xFF
#define TARGET_BUS                           0x1
#define BUS_ZERO                             0x0
#define DEVICE_ZERO                          0x0
#define DEVICE_THREE                         0x3
#define FUNCTION_ZERO                        0x0
#define FUNCTION_ONE                         0x1
#define FUNCTION_TWO                         0x2

#define SYSHUB_HI_ADDRESS                    0xFFFE

#define TOBAGO_BAR_ADDRESS                   0x10
#define TOBAGO_BAR_VALUE                     PCIE_MEMORY_BASE
#define TOBAGO_MMIO_BASE                     0x80000000UL
#define TOBAGO_MMIO_BAR_ADDRESS              0x24
#define TOBAGO_DOORBELL_BASE                 0x90000000UL
#define TOBAGO_DOORBELL_BAR_ADDRESS          0x18


#define DF_SMN_BASE_ADDR  (0x0001C000ul)
#define MAKE_SMN_ADDR(Fun, Off) (((UINT32) DF_SMN_BASE_ADDR) | (((UINT32)(Fun)) << 10) | ((UINT32)(Off)))

extern UINT32 gEnvFlag;

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */
/// SetVddCldoBypassModes Argument Structure
typedef union {
  struct {                                                              ///<
    UINT32                                    CLDO_E12GA_GMI_Bypass:8 ; ///<
    UINT32                                      CLDO_DDR_GMI_Bypass:8 ; ///<
    UINT32                                     CLDO_WAFL_GMI_Bypass:8 ; ///<
    UINT32                                    CLDO_E12GB_GMI_Bypass:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///< @todo : docmument this
} SetVddpCldoBypassModes_STRUCT;

/// SetVddmCldoBypassModes Argument Structure
typedef union {
  struct {
    UINT32                                        CLDO_VDDM0_Bypass:8 ; ///<
    UINT32                                        CLDO_VDDM1_Bypass:8 ; ///<
    UINT32                                                Reserved1:8 ; ///<
    UINT32                                                Reserved2:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///< @todo : docmument this
} SetVddmCldoBypassModes_STRUCT;

/// ConfigSocRail Argument Structure
typedef union {
  struct {                                                              ///<
    UINT32                                                 DDR_Rate:16; ///<
    UINT32                                           PCIe_Overclock:8 ; ///<
    UINT32                                     Encryption_Overclock:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///< @todo : docmument this
} ConfigSocRail_STRUCT;

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */
VOID PciePortInitialization (
  IN  CONST EFI_PEI_SERVICES   **PeiServices,
  IN        GNB_HANDLE    *GnbHandle,
  IN        UINT8         DeviceWidth
  );

/*----------------------------------------------------------------------------------------*/
/**
 * SMN Register Write
 *
 *
 *
 * @param[in]  GnbHandle      GNB_HANDLE
 * @param[in]  SmnAddress     SMN Register Address
 * @param[in]  RegValue       Value to write to SMN Register
 *
 */
VOID
STATIC
SmnRegisterWrite (
  IN       GNB_HANDLE      *GnbHandle,
  IN       UINT32          SmnAddress,
  IN       UINT32          RegValue
  )
{
  UINT32  Value;

  Value = RegValue;
  NbioRegisterWrite (GnbHandle, TYPE_SMN, SmnAddress, &Value, 0);
}
#define writeSmnReg SmnRegisterWrite

/*----------------------------------------------------------------------------------------*/
/**
 * SMN Register Read
 *
 *
 *
 * @param[in]  GnbHandle      GNB_HANDLE
 * @param[in]  SmnAddress     SMN Register Address
 * @param[in]  RegValue       Pointer to location to store data from SMN Register
 *
 */
VOID
STATIC
SmnRegisterRead  (
  IN       GNB_HANDLE      *GnbHandle,
  IN       UINT32          SmnAddress,
  IN       UINT32          *RegValue
  )
{
  NbioRegisterRead (GnbHandle, TYPE_SMN, SmnAddress, RegValue, 0);
}

/*----------------------------------------------------------------------------------------*/
/**
 * SMN Register Read
 *
 *
 *
 * @param[in]  GnbHandle      GNB_HANDLE
 * @param[in]  SmnAddress     SMN Register Address
 *
 */
UINT32
STATIC
readSmnReg (
  IN       GNB_HANDLE      *GnbHandle,
  IN       UINT32          SmnAddress
  )
{
  UINT32          Value;

  SmnRegisterRead (GnbHandle, SmnAddress, &Value);
  return Value;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Local delay function
 *
 *
 *
 * @param[in]  PeiServices    Pointer to EFI_PEI_SERVICES pointer
 * @param[in]  xus            Microseconds to delay
 *
 */
VOID
STATIC
delay_xus (
  IN  CONST     EFI_PEI_SERVICES   **PeiServices,
  IN  UINT32    xus
  )
{
  EFI_PEI_CPU_IO_PPI  *CpuIo;
  UINTN               uSec;
  UINT8               Data;

  // Issue the reset
  CpuIo = (*PeiServices)->CpuIo;

  //Simplified implementation
  uSec = xus >> 1;
  while (uSec != 0) {
    Data = CpuIo->IoRead8 (
                    PeiServices,
                    CpuIo,
                    (UINT64) 0x80
                    );
    uSec--;
  }
}

#define US_TO_REFCLK(x) x
#define SysTimeDelay(x)   delay_xus(PeiServices, x)


/*----------------------------------------------------------------------------------------*/
/**
 * Register Group Write helper function
 *
 *
 *
 * @param[in]  GnbHandle     GNB_HANDLE
 * @param[in]  BaseRegister  Address of the first register in the group
 * @param[in]  Value         Value to write to all registers in the group
 * @param[in]  RegisterCount Number of register to write
 */
VOID WriteRegisterGroup (
  IN      GNB_HANDLE  *GnbHandle,
  IN      UINT32      BaseRegister,
  IN      UINT32      Value,
  IN      UINT32      RegisterCount
  )
{
  UINT32      Index;

  for (Index = 0; Index < RegisterCount; Index++) {
    SmnRegisterWrite (GnbHandle, BaseRegister + (Index << 17), Value);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Register Group Poll helper function
 *
 *
 *
 * @param[in]  GnbHandle     GNB_HANDLE
 * @param[in]  BaseRegister  Address of the first register in the group
 * @param[in]  Mask          Value to mask the read value with
 * @param[in]  Value         Masked value that exits the while() loop
 * @param[in]  RegisterCount Number of register to write
 */
VOID PollRegisterGroup (
  IN      GNB_HANDLE  *GnbHandle,
  IN      UINT32      BaseRegister,
  IN      UINT32      Mask,
  IN      UINT32      Value,
  IN      UINT32      RegisterCount
  )
{
  UINT32      Index;

  for (Index = 0; Index < RegisterCount; Index++) {
    while ((readSmnReg (GnbHandle, BaseRegister + (Index << 17)) & Mask) != Value ) {};
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * dGPU as base memory initialization
 *
 *
 *
 * @param[in]  PeiServices   Pointer to EFI_PEI_SERVICES pointer
 * @param[in]  GnbHandle     GNB_HANDLE
 */

VOID
KpnpResetWorkaround (
  IN CONST  EFI_PEI_SERVICES   **PeiServices,
  IN        GNB_HANDLE         *GnbHandle
  )
{
  //Step 0: Correct rx_cdr_vco_lowfreq for all 3 speeds
  writeSmnReg (GnbHandle, 0x11A0B618, 0x10DFDFDF);

  writeSmnReg (GnbHandle, 0x11A1E00C, readSmnReg (GnbHandle, 0x11A1E00C) | 0x80000000);
  writeSmnReg (GnbHandle, 0x11A3E00C, readSmnReg (GnbHandle, 0x11A1E00C) | 0x80000000);
  writeSmnReg (GnbHandle, 0x11A5400C, readSmnReg (GnbHandle, 0x11A1400C) | 0x80000000);
  writeSmnReg (GnbHandle, 0x11A7400C, readSmnReg (GnbHandle, 0x11A1400C) | 0x80000000);
  writeSmnReg (GnbHandle, 0x11A9400C, readSmnReg (GnbHandle, 0x11A1400C) | 0x80000000);

  //Step 1: KPMX_CTLR_SELECT_n0 (N/A)
  //Change LinkId according to link configuration
  //Set bit26&25 to b'11
  writeSmnReg (GnbHandle, 0x11A01620, ((readSmnReg (GnbHandle, 0x11A01620) & 0xF9FFFF00) | (0x0 << 25)|0x1)); //Lane0
  writeSmnReg (GnbHandle, 0x11A01624, ((readSmnReg (GnbHandle, 0x11A01624) & 0xF9FFFF00) | (0x0 << 25)|0x1)); //Lane1
  writeSmnReg (GnbHandle, 0x11B21620, ((readSmnReg (GnbHandle, 0x11B21620) & 0xF9FFFF00) | (0x3 << 25)|0x0)); //Lane2 // Sata
  writeSmnReg (GnbHandle, 0x11B21624, ((readSmnReg (GnbHandle, 0x11B21624) & 0xF9FFFF00) | (0x3 << 25)|0x1)); //Lane3 // Sata
  writeSmnReg (GnbHandle, 0x11A41620, ((readSmnReg (GnbHandle, 0x11A41620) & 0xF9FFFF00) | (0x0 << 25)|0x2)); //Lane4
  writeSmnReg (GnbHandle, 0x11A41624, ((readSmnReg (GnbHandle, 0x11A41624) & 0xF9FFFF00) | (0x0 << 25)|0x3)); //Lane5
  writeSmnReg (GnbHandle, 0x11A41628, ((readSmnReg (GnbHandle, 0x11A41628) & 0xF9FFFF00) | (0x0 << 25)|0x4)); //Lane6
  writeSmnReg (GnbHandle, 0x11A4162C, ((readSmnReg (GnbHandle, 0x11A4162C) & 0xF9FFFF00) | (0x0 << 25)|0x5)); //Lane7
  writeSmnReg (GnbHandle, 0x11A61620, ((readSmnReg (GnbHandle, 0x11A61620) & 0xF9FFFF00) | (0x0 << 25)|0x6)); //Lane8
  writeSmnReg (GnbHandle, 0x11A61624, ((readSmnReg (GnbHandle, 0x11A61624) & 0xF9FFFF00) | (0x0 << 25)|0x6)); //Lane9
  writeSmnReg (GnbHandle, 0x11A61628, ((readSmnReg (GnbHandle, 0x11A61628) & 0xF9FFFF00) | (0x0 << 25)|0x6)); //Lane10
  writeSmnReg (GnbHandle, 0x11A6162C, ((readSmnReg (GnbHandle, 0x11A6162C) & 0xF9FFFF00) | (0x0 << 25)|0x6)); //Lane11
  writeSmnReg (GnbHandle, 0x11A81620, ((readSmnReg (GnbHandle, 0x11A81620) & 0xF9FFFF00) | (0x0 << 25)|0x6)); //Lane12
  writeSmnReg (GnbHandle, 0x11A81624, ((readSmnReg (GnbHandle, 0x11A81624) & 0xF9FFFF00) | (0x0 << 25)|0x6)); //Lane13
  writeSmnReg (GnbHandle, 0x11A81628, ((readSmnReg (GnbHandle, 0x11A81628) & 0xF9FFFF00) | (0x0 << 25)|0x6)); //Lane14
  writeSmnReg (GnbHandle, 0x11A8162C, ((readSmnReg (GnbHandle, 0x11A8162C) & 0xF9FFFF00) | (0x0 << 25)|0x6)); //Lane15

  //Step 2: Set Logiclinknumber to enable gang mode, to do: change the llnumber to map topo
  writeSmnReg (GnbHandle, 0x11A0B040, ((readSmnReg (GnbHandle, 0x11A0B040) & 0xFFFFFFF0) | 0x1)); // Lane0
  writeSmnReg (GnbHandle, 0x11A0B044, ((readSmnReg (GnbHandle, 0x11A0B044) & 0xFFFFFFF0) | 0x1)); // Lane1
  writeSmnReg (GnbHandle, 0x11B2B040, ((readSmnReg (GnbHandle, 0x11B2B040) & 0xFFFFFFF0) | 0x0)); // Lane2 //Sata
  writeSmnReg (GnbHandle, 0x11B2B044, ((readSmnReg (GnbHandle, 0x11B2B044) & 0xFFFFFFF0) | 0x1)); // Lane3 //Sata
  writeSmnReg (GnbHandle, 0x11A0B050, ((readSmnReg (GnbHandle, 0x11A0B050) & 0xFFFFFFF0) | 0x2)); // Lane4
  writeSmnReg (GnbHandle, 0x11A0B054, ((readSmnReg (GnbHandle, 0x11A0B054) & 0xFFFFFFF0) | 0x3)); // Lane5
  writeSmnReg (GnbHandle, 0x11A0B058, ((readSmnReg (GnbHandle, 0x11A0B058) & 0xFFFFFFF0) | 0x4)); // Lane6
  writeSmnReg (GnbHandle, 0x11A0B05C, ((readSmnReg (GnbHandle, 0x11A0B05C) & 0xFFFFFFF0) | 0x5)); // Lane7
  writeSmnReg (GnbHandle, 0x11A0B060, ((readSmnReg (GnbHandle, 0x11A0B060) & 0xFFFFFFF0) | 0x6)); // Lane8
  writeSmnReg (GnbHandle, 0x11A0B064, ((readSmnReg (GnbHandle, 0x11A0B064) & 0xFFFFFFF0) | 0x6)); // Lane9
  writeSmnReg (GnbHandle, 0x11A0B068, ((readSmnReg (GnbHandle, 0x11A0B068) & 0xFFFFFFF0) | 0x6)); // Lane10
  writeSmnReg (GnbHandle, 0x11A0B06C, ((readSmnReg (GnbHandle, 0x11A0B06C) & 0xFFFFFFF0) | 0x6)); // Lane11
  writeSmnReg (GnbHandle, 0x11A0B070, ((readSmnReg (GnbHandle, 0x11A0B070) & 0xFFFFFFF0) | 0x6)); // Lane12
  writeSmnReg (GnbHandle, 0x11A0B074, ((readSmnReg (GnbHandle, 0x11A0B074) & 0xFFFFFFF0) | 0x6)); // Lane13
  writeSmnReg (GnbHandle, 0x11A0B078, ((readSmnReg (GnbHandle, 0x11A0B078) & 0xFFFFFFF0) | 0x6)); // Lane14
  writeSmnReg (GnbHandle, 0x11A0B07C, ((readSmnReg (GnbHandle, 0x11A0B07C) & 0xFFFFFFF0) | 0x6)); // Lane15

  //Step 3: de-assert per-lane soft reset
  // KPNP_LANE_SOFT_RESET
  writeSmnReg (GnbHandle, 0x11A01864, 0x0);
  writeSmnReg (GnbHandle, 0x11A21864, 0x0);
  writeSmnReg (GnbHandle, 0x11A41864, 0x0);
  writeSmnReg (GnbHandle, 0x11A61864, 0x0);
  writeSmnReg (GnbHandle, 0x11A81864, 0x0);

  delay_xus (PeiServices, 10000);

   // Poll if ack = 0
  while ( readSmnReg (GnbHandle, 0x11A01838)!= 0 ) {
    readSmnReg (GnbHandle, 0x11A01838);
  }
  while ( readSmnReg (GnbHandle, 0x11A21838)!= 0 ) {
    readSmnReg (GnbHandle, 0x11A21838);
  }
  while ( readSmnReg (GnbHandle, 0x11A41838)!= 0 ) {
    readSmnReg (GnbHandle, 0x11A41838);
  }
  while ( readSmnReg (GnbHandle, 0x11A61838)!= 0 ) {
    readSmnReg (GnbHandle, 0x11A61838);
  }
  while ( readSmnReg (GnbHandle, 0x11A81838)!= 0 ) {
    readSmnReg (GnbHandle, 0x11A81838);
  }

  return;
}

/*----------------------------------------------------------------------------------------*/
/**
 * A0 Parallel Training Workaround
 *
 *
 *
 * @param[in]  PeiServices   Pointer to EFI_PEI_SERVICES pointer
 * @param[in]  GnbHandle     GNB_HANDLE
 */

VOID
A0ParallelTrainingWorkaround (
  IN CONST  EFI_PEI_SERVICES         **PeiServices,
  IN        GNB_HANDLE               *GnbHandle,
  IN OUT    DXIO_COMPLEX_DESCRIPTOR  *PcieTopologyData
  )
{
  BOOLEAN                              EndOfList;
  DXIO_PORT_DESCRIPTOR                *PortPointer;

  PortPointer = PcieTopologyData->PciePortList;
  EndOfList = FALSE;

  do {
      switch (PortPointer->EngineData.EngineType) {
      case DxioPcieEngine:
       if(PortPointer->EngineData.StartLane == 0 && PortPointer->EngineData.EndLane == 1) {
         PortPointer->Port.LinkSpeedCapability = DxioGen2;
       }
        break;
      case DxioSATAEngine:
        break;
      case DxioDPEngine:
        break;
      case DxioEthernetEngine:
        break;
      case DxioGOPEngine:
        break;
      default:
        break;
    }
    if ((PortPointer->Flags & DESCRIPTOR_TERMINATE_LIST) == 0) {
      PortPointer++;
    } else {
      EndOfList = TRUE;
    }
  } while (EndOfList != TRUE);

}


