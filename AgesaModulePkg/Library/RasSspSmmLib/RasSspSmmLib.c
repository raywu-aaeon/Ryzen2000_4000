/*
*****************************************************************************
*
* Copyright 2016 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
#include <Filecode.h>
#include <Library/DebugLib.h>
#include <Library/RasSspSmmLib.h>
#include <Library/PciLib.h>
#include "AMD.h"
#include <Library/IdsLib.h>

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define CFG_ADDR_PORT     0xcf8
#define CFG_DATA_PORT     0xcfc
#define FCH_IOMAP_REGCD6  0xcd6
#define FCH_IOMAP_REGCD7  0xcd7

#define FILECODE LIBRARY_RASSSPSMMLIB_RASSSPSMMLIB_FILECODE

/*----------------------------------------------------------------------------------------
 *                           G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */

extern  ADDR_DATA               *gAddrData;

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
VOID
RasSmmMsrWrite (
  IN       RAS_MSR_ACCESS *RasMsrAccess
  );

VOID
RasSmmMsrRead (
  IN OUT   RAS_MSR_ACCESS *RasMsrAccess
  );

VOID
RasSmmMsrTblWrite (
  IN       VOID *MsrTable
  );

VOID
CollectMcaErrorInfo (
  IN OUT   RAS_MCA_ERROR_INFO_V2* RasMcaErrorInfo
  );

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                          T A B L E    D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------*/
/**
 *  LibRasSmmMemRead
 *  Description
 *      SMM Memory Read Access
 *
 * @param[in]       SmmIo           Pointer to SMM CPU IO interface
 * @param[in]       AccessWidth     Access width
 * @param[in]       Address         Memory address
 * @param[out]      Value           Pointer to data buffer
 *
 */
/*----------------------------------------------------------------------------------------*/
VOID
LibRasSmmMemRead (
  IN       EFI_SMM_CPU_IO2_PROTOCOL    *SmmIo,
  IN       EFI_SMM_IO_WIDTH            AccessWidth,
  IN       UINT64                      Address,
     OUT   VOID                        *Value
  )
{
  SmmIo->Mem.Read (
                   SmmIo,
                   AccessWidth,
                   Address,
                   1,
                   Value
                   );
}


/*----------------------------------------------------------------------------------------*/
/**
 *  LibRasSmmIoRead
 *  Description
 *      SMM I/O Read Access
 *
 * @param[in]       SmmIo           Pointer to SMM CPU IO interface
 * @param[in]       AccessWidth     Access width
 * @param[in]       Address         IO address
 * @param[out]      Value           Pointer to data buffer
 *
 */
/*----------------------------------------------------------------------------------------*/
VOID
LibRasSmmIoRead (
  IN       EFI_SMM_CPU_IO2_PROTOCOL    *SmmIo,
  IN       EFI_SMM_IO_WIDTH            AccessWidth,
  IN       UINT16                      Address,
     OUT   VOID                        *Value
  )
{
  SmmIo->Io.Read (
                   SmmIo,
                   AccessWidth,
                   Address,
                   1,
                   Value
                   );
}


/*----------------------------------------------------------------------------------------*/
/**
 *  LibRasSmmIoWrite
 *  Description
 *      SMM I/O Write Access
 *
 * @param[in]       SmmIo           Pointer to SMM CPU IO interface
 * @param[in]       AccessWidth     Access width
 * @param[in]       Address         IO address
 * @param[out]      Value           Pointer to data buffer
 *
 */
/*----------------------------------------------------------------------------------------*/
VOID
LibRasSmmIoWrite (
  IN       EFI_SMM_CPU_IO2_PROTOCOL    *SmmIo,
  IN       EFI_SMM_IO_WIDTH            AccessWidth,
  IN       UINT64                      Address,
  IN       VOID                        *Value
  )
{
  SmmIo->Io.Write (
              SmmIo,
              AccessWidth,
              Address,
              1,
              Value
              );
}

VOID
LibRasSmmPciRead (
  IN       EFI_SMM_CPU_IO2_PROTOCOL    *SmmIo,
  IN       EFI_SMM_IO_WIDTH            AccessWidth,
  IN       UINT32                      PciAddress,
     OUT   VOID                        *Value
  )
{
  UINT32     Address32;

  Address32 = BIT31 + (UINT32) ((PciAddress >> 8) & 0xFFFFFF00) + (PciAddress & 0xFF);
  LibRasSmmIoWrite (SmmIo, SMM_IO_UINT32, CFG_ADDR_PORT, &Address32);
  LibRasSmmIoRead (SmmIo, AccessWidth, CFG_DATA_PORT, Value);
}


VOID
LibRasSmmPmioRead8 (
  IN       EFI_SMM_CPU_IO2_PROTOCOL    *SmmIo,
  IN       UINT8                       Offset,
     OUT   VOID                        *Value
  )
{
  LibRasSmmIoWrite (SmmIo, SMM_IO_UINT8, FCH_IOMAP_REGCD6, &Offset);
  LibRasSmmIoRead (SmmIo, SMM_IO_UINT8, FCH_IOMAP_REGCD7, Value);
}


VOID
LibRasSmmPmioWrite8 (
  IN       EFI_SMM_CPU_IO2_PROTOCOL    *SmmIo,
  IN       UINT8                       Offset,
     OUT   VOID                        *Value
  )
{
  LibRasSmmIoWrite (SmmIo, SMM_IO_UINT8, FCH_IOMAP_REGCD6, &Offset);
  LibRasSmmIoWrite (SmmIo, SMM_IO_UINT8, FCH_IOMAP_REGCD7, Value);
}

/*---------------------------------------------------------------------------------------*/
/**
 * LibRasSmmMsrWrite
 *
 * Sync Givan MSR list to all APs
 *
 * @param[in]  ApMsrSync         MSRs table
 *
 */
VOID
LibRasSmmMsrWrite (
  IN       RAS_MSR_ACCESS *RasMsrAccess,
  IN       UINTN          ProcessorNumber
  )
{
    if (ProcessorNumber > gSmst->NumberOfCpus) {
      return;
    }
    if (ProcessorNumber == 0) {
      RasSmmMsrWrite(RasMsrAccess);
    } else {
      gSmst->SmmStartupThisAp(
            RasSmmMsrWrite,
            ProcessorNumber,
            RasMsrAccess
      );
    }
}

/*---------------------------------------------------------------------------------------*/
/**
 * LibRasSmmMsrRead
 *
 * Sync Givan MSR list to all APs
 *
 * @param[in]  ApMsrSync         MSRs table
 *
 */
VOID
LibRasSmmMsrRead (
  IN       RAS_MSR_ACCESS *RasMsrAccess,
  IN       UINTN          ProcessorNumber
  )
{
    if (ProcessorNumber > gSmst->NumberOfCpus) {
      return;
    }
    if (ProcessorNumber == 0) {
      RasSmmMsrRead (RasMsrAccess);
    } else {
      gSmst->SmmStartupThisAp(
            RasSmmMsrRead,
            ProcessorNumber,
            RasMsrAccess
      );
    }
}

/*---------------------------------------------------------------------------------------*/
/**
 * LibRasSmmMsrTblWrite
 *
 * Write Givan MSR list to all specified core.
 *
 * @param[in]  ApMsrSync         MSRs table
 * @param[in]  ProcessorNumber          Cpu Logic ID
 *
 */
VOID
LibRasSmmMsrTblWrite (
  IN OUT   RAS_BSP_AP_MSR_SYNC *ApMsrSync,
  IN       UINTN               ProcessorNumber
  )
{
    if (ProcessorNumber > gSmst->NumberOfCpus) {
      return;
    }
    if (ProcessorNumber == 0) {
      RasSmmMsrTblWrite(ApMsrSync);
    } else {
      gSmst->SmmStartupThisAp(
            RasSmmMsrTblWrite,
            ProcessorNumber,
            ApMsrSync
      );
    }
}

/*---------------------------------------------------------------------------------------*/
/**
 * LibRasSmmSyncMsr
 *
 * Sync Givan MSR list to all APs
 *
 * @param[in]  ApMsrSync         MSRs table
 *
 */
VOID
LibRasSmmSyncMsr (
  IN OUT   RAS_BSP_AP_MSR_SYNC *ApMsrSync
  )
{
  UINT16      i;

  //
  //Sync all MSR settings with BSP
  //

  for (i = 0; ApMsrSync[i].RegisterAddress != 0; i++) {
    if (ApMsrSync[i].ForceSetting == FALSE) {
      ApMsrSync[i].RegisterValue = AsmReadMsr64 (ApMsrSync[i].RegisterAddress);
    }
  }

  for (i = 1; i < gSmst->NumberOfCpus; i++) {
    gSmst->SmmStartupThisAp (
            RasSmmMsrTblWrite,
            i,
            (VOID *) ApMsrSync
            );
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * LibRasSmmRunFunc
 *
 * execute given MP procedure to BSP/AP
 *
 * @param[in]  RasMpProcedure Ras MP procedure
 * @param[in]  Buffer         Procedure input buffer
 * @param[in]  ProcessorNumber       Logic CPU ID
 *
 */
VOID
LibRasSmmRunFunc (
  IN        EFI_AP_PROCEDURE RasMpProcedure,
  IN        VOID             *Buffer,
  IN        UINTN            ProcessorNumber
  )
{

  if (ProcessorNumber > gSmst->NumberOfCpus) {
    return;
  }

  if (ProcessorNumber == 0) {
    RasMpProcedure(Buffer);
  } else {
       gSmst->SmmStartupThisAp (
               RasMpProcedure,
               ProcessorNumber,
               Buffer
               );
  }
}

VOID
CollectMpMcaErrorInfo (
  IN OUT   RAS_MCA_ERROR_INFO_V2* RasMcaErrorInfo
  )
{

  if (RasMcaErrorInfo->CpuInfo.ProcessorNumber > gSmst->NumberOfCpus) {
      
    return;
  }
  //Program BSP first
  if (RasMcaErrorInfo->CpuInfo.ProcessorNumber == 0) {
    CollectMcaErrorInfo(RasMcaErrorInfo);
  } else {
    gSmst->SmmStartupThisAp(
           CollectMcaErrorInfo,
           RasMcaErrorInfo->CpuInfo.ProcessorNumber,
           (VOID *) RasMcaErrorInfo 
    );
  }

}

/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*---------------------------------------------------------------------------------------*/
/**
 * MSRs Write
 *
 *
 * @param[in]  RasMsrAccess          MSR data write
 *
 */
VOID
RasSmmMsrWrite (
  IN       RAS_MSR_ACCESS *RasMsrAccess
  )
{

  AsmMsrAndThenOr64 (
    RasMsrAccess->RegisterAddress,
    ~RasMsrAccess->RegisterMask,
    (RasMsrAccess->RegisterValue & RasMsrAccess->RegisterMask)
    );
}


/*---------------------------------------------------------------------------------------*/
/**
 * MSRs Read
 *
 *
 * @param[in]  RasMsrAccess          MSR data read
 *
 */
VOID
RasSmmMsrRead (
  IN       RAS_MSR_ACCESS *RasMsrAccess
  )
{
  RasMsrAccess->RegisterValue = AsmReadMsr64 (RasMsrAccess->RegisterAddress);
}

/*---------------------------------------------------------------------------------------*/
/**
 * AP task to sync MSRs with the BSC
 *
 *
 * @param[in]  MsrTable          MSRs table
 *
 */
VOID
RasSmmMsrTblWrite (
  IN       VOID *MsrTable
  )
{
  UINT8   i;

  for (i = 0; ((RAS_BSP_AP_MSR_SYNC *) MsrTable)[i].RegisterAddress != 0; i++) {
    AsmMsrAndThenOr64 (
        ((RAS_BSP_AP_MSR_SYNC *) MsrTable)[i].RegisterAddress,
        ~(((RAS_BSP_AP_MSR_SYNC *) MsrTable)[i].RegisterMask),
        (((RAS_BSP_AP_MSR_SYNC *) MsrTable)[i].RegisterValue &
        ((RAS_BSP_AP_MSR_SYNC *) MsrTable)[i].RegisterMask)
        );
  }
}

VOID
CollectMcaErrorInfo (
  IN OUT   RAS_MCA_ERROR_INFO_V2* RasMcaErrorInfo
  )
{
  UINT32 i;
  UINT8 BankNum;
  UINT64 MsrData;
  MCA_STATUS_MSR McaStatusMsr;
  MCA_IPID_MSR McIpid;

  MsrData = AsmReadMsr64 (MSR_MCG_CAP);            // MCG_CAP
  BankNum = (UINT8)(MsrData & 0xFF);
  RasMcaErrorInfo->McaBankCount = BankNum;

  for (i = 0; i < BankNum; i++) {
     McIpid.Value = AsmReadMsr64 ((MCA_EXTENSION_BASE + (i * 0x10) | MCA_IPID_OFFSET));            // MCA_IPID
    if (McIpid.Field.HardwareID == 0)
	  continue;
    //Find error log
    McaStatusMsr.Value = AsmReadMsr64((MCA_EXTENSION_BASE + (i * 0x10) | MCA_STATUS_OFFSET));
	if (McaStatusMsr.Field.Val) {
      //Collect MSR value
      RasMcaErrorInfo->McaBankErrorInfo[i].McaBankNumber = i;
      RasMcaErrorInfo->McaBankErrorInfo[i].McaStatusMsr.Value = McaStatusMsr.Value;
      RasMcaErrorInfo->McaBankErrorInfo[i].McaAddrMsr.Value = AsmReadMsr64((MCA_EXTENSION_BASE + (i * 0x10) | MCA_ADDR_OFFSET));
      RasMcaErrorInfo->McaBankErrorInfo[i].McaConfigMsr.Value = AsmReadMsr64((MCA_EXTENSION_BASE + (i * 0x10) | MCA_CONFIG_OFFSET));
      RasMcaErrorInfo->McaBankErrorInfo[i].McaIpidMsr.Value = McIpid.Value;
      RasMcaErrorInfo->McaBankErrorInfo[i].McaSyndMsr.Value = AsmReadMsr64((MCA_EXTENSION_BASE + (i * 0x10) | MCA_SYND_OFFSET));
      RasMcaErrorInfo->McaBankErrorInfo[i].McaMisc0Msr.Value = AsmReadMsr64((MCA_EXTENSION_BASE + (i * 0x10) | MCA_MISC0_OFFSET));
        RasMcaErrorInfo->McaBankErrorInfo[i].McaMisc1Msr.Value = AsmReadMsr64((MCA_EXTENSION_BASE + (i * 0x10) | MCA_MISC1_OFFSET));
        RasMcaErrorInfo->McaBankErrorInfo[i].McaDeStatMsr.Value = AsmReadMsr64((MCA_EXTENSION_BASE + (i * 0x10) | MCA_DESTAT_OFFSET));
        RasMcaErrorInfo->McaBankErrorInfo[i].McaDeAddrMsr.Value = AsmReadMsr64((MCA_EXTENSION_BASE + (i * 0x10) | MCA_DEADDR_OFFSET));
      }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 *
 *
 */
UINT64 
pow_ras (
  UINTN   input,
  UINTN   exp
  )
{
  UINT64  value;
  UINTN   i;

  value = 1;

  if (0 == exp) {
  } else {
    for (i = 0; i < exp; i++) {
      value *= input;
    }
  }
  return value;
}

/*------------------------------------------------------------------
 Function: getBits64
 Purpose: A helper function to get abit range from a uint64
 Inputs:
   low bit number
   high bit number
   the data
 Outputs:
   the requested bits, right justified
 *------------------------------------------------------------------*/
UINT64
getBits64 (
  UINT32 lowBit,
  UINT32 highBit,
  UINT64 data
  )
{
  UINT64    mask;
  mask = (((UINT64) 1) << (highBit - lowBit + ((UINT64) 1))) - ((UINT64) 1);
  return (UINT32) ((data >> lowBit) & mask);
}

/*------------------------------------------------------------------
 Function: getBits
 Purpose: A helper function to get abit range from a uint32
 Inputs:
   low bit number
   high bit number
   the data
 Outputs:
   the requested bits, right justified
 *------------------------------------------------------------------*/
UINT32
getBits (
  UINT32 lowBit,
  UINT32 highBit,
  UINT32 data
  )
{
  UINT32 mask;
  mask = (1 << (highBit - lowBit + 1)) - 1;
  return ((data >> lowBit) & mask);
}

/*------------------------------------------------------------------
 Function: getBit
 Purpose: A helper function to get a specific bit from a uint32
 Inputs:
   bit number
   the data
 Outputs:
   the requested bit, right justified
 *------------------------------------------------------------------*/
UINT32
getBit (
  UINT32 bit,
  UINT32 data
  )
{
  return ((data >> bit) & 0x1);
}

/*------------------------------------------------------------------
 Function: getBit64
 Purpose: A helper function to get a specific bit from a uint64
 Inputs:
   bit number
   the data
 Outputs:
   the requested bit, right justified
 *------------------------------------------------------------------*/
UINT32
getBit64 (
  UINT64 bit,
  UINT64 data
  )
{
  return ((data >> bit) & 0x1);
}

/*------------------------------------------------------------------
 Function: getDfReg
 Purpose: Get a DF register
 Inputs: An instanceID (-1 for a broadcast read),
   a nodeID (for the PCIe bus/device),
   and a register address (function in bits 12:10)
 Outputs: The requested register
 *------------------------------------------------------------------*/
UINT32 
getDfReg (
  UINT32 instanceId,
  UINT32 nodeId,
  UINT32 regAddr
  )
{
  UINT32                               RegisterValue;
  PCI_ADDR                             PciAddr;
  FABRIC_IND_CFG_ACCESS_ADDR_REGISTER  FICAA3;

  PciAddr.AddressValue = 0;
  PciAddr.Address.Device = nodeId + 0x18;   // 0x18 = PCIE device number of socket 0 die 0

  FICAA3.Value = 0;   // Variable initiate
  if ((instanceId & 0xFF) != FABRIC_REG_ACC_BC) {
    FICAA3.Field.CfgRegInstAccEn = 1;
  }

  PciAddr.Address.Function = FICAA3_FUNC;
  PciAddr.Address.Register = FICAA3_REG;
  FICAA3.Field.IndCfgAccRegNum = ((UINT32) (regAddr & 0x3ff)) >> 2;
  FICAA3.Field.IndCfgAccFuncNum = ((UINT32) (regAddr >> 10 )) & 7;
  FICAA3.Field.CfgRegInstID = (UINT32) instanceId;
  PciWrite32 (PciAddr.AddressValue, FICAA3.Value);
  //PciExpressWrite32 ((UINTN) PciAddr.AddressValue, FICAA3.Value);

  PciAddr.Address.Function = FICAD3_LO_FUNC;
  PciAddr.Address.Register = FICAD3_LO_REG;
  RegisterValue = PciRead32 (PciAddr.AddressValue);  
  //RegisterValue = PciExpressRead32 ((UINTN) PciAddr.AddressValue);
  return RegisterValue;
}

/*------------------------------------------------------------------
 Function: getDfRegSystemFabricIdMask
 Purpose: Get the DF::SystemFabricIdMask register
 Inputs: An instanceID (CS) and a nodeID (for the PCIe bus/device)
 Outputs: The requested register
 *------------------------------------------------------------------*/
UINT32
getDfRegSystemFabricIdMask (
  UINT32 nodeId
  )
{
  return (getDfReg (BCAST, nodeId, DF_SYSFABIDMASK_ADDR));
}

/*------------------------------------------------------------------
 Function: getDfRegSystemFabricIdMask1
 Purpose: Get the DF::SystemFabricIdMask register
 Inputs: An instanceID (CS) and a nodeID (for the PCIe bus/device)
 Outputs: The requested register
 *------------------------------------------------------------------*/
UINT32
getDfRegSystemFabricIdMask1 (
  UINT32 nodeId
  )
{
  return (getDfReg (BCAST, nodeId, DF_SYSFABIDMASK1_ADDR));
}

/*------------------------------------------------------------------
 Function: determineDfType
 Purpose: Determine if the DF type is DF2 or DF3
 Inputs: None
 Outputs: The DF type as an integer
 *------------------------------------------------------------------*/
UINT32
determineDfType (
  VOID
  )
{
  // In DF2, F1x208 (SystemFabricIdMask) bits 7:0 are reserved and always zero.
  // In DF3, F1x208 buts 9:0 are the Component ID Mask, and bits 7:0 must always be non-zero.
  // We use this to differentiate DF2 and DF3.
  // We can do this on node 0, since there will always be a node 0 and all nodes will be the same.
  if ((getDfRegSystemFabricIdMask (0) & 0xFF) == 0)
    return 2;
  return 3;
}

/*------------------------------------------------------------------
 Function: getDfRegFabricBlkInstanceCnt
 Purpose: Get the DF::FabricBlockInstanceCount register
 Inputs: An instanceID (CS) and a nodeID (for the PCIe bus/device)
 Outputs: The requested register
 *------------------------------------------------------------------*/
UINT32 
getDfRegFabricBlkInstanceCnt (
  UINT32  nodeId
  )
{
  return (getDfReg (BCAST, nodeId, DF_FABBLKINSTCNT_ADDR));
}

/*------------------------------------------------------------------
 Function: getDfRegFabricBlkInstInfo0
 Purpose: Get the DF::FabricBlockInstanceInformation0 register
 Inputs: An instanceID (CS) and a nodeID (for the PCIe bus/device)
 Outputs: The requested register
 *------------------------------------------------------------------*/
UINT32
getDfRegFabricBlkInstInfo0 (
  UINT32 instanceId,
  UINT32 nodeId
  )
{
  return (getDfReg (instanceId, nodeId, DF_FABBLKINFO0_ADDR));
}

/*------------------------------------------------------------------
 Function: getDfRegFabricBlkInstInfo3
 Purpose: Get the DF::FabricBlockInstanceInformation3 register
 Inputs: An instanceID (CS) and a nodeID (for the PCIe bus/device)
 Outputs: The requested register
 *------------------------------------------------------------------*/
UINT32
getDfRegFabricBlkInstInfo3 (
  UINT32 instanceId,
  UINT32 nodeId
  )
{
  return (getDfReg (instanceId, nodeId, DF_FABBLKINFO3_ADDR));
}

/*------------------------------------------------------------------
 Function: getDfRegDramOffset
 Purpose: Get the DF::DramOffset[n] register
 Inputs: An instanceID (CS), a nodeID (for the PCIe bus/device)
   and a register number (1 or 2)
 Outputs: The requested register
 *------------------------------------------------------------------*/
UINT32
getDfRegDramOffset (
  UINT32 instanceId,
  UINT32 nodeId,
  UINT32 regNum
  )
{
  return (getDfReg (instanceId, nodeId, DF_DRAMOFFSET0_ADDR + (4*regNum)));
}

/*------------------------------------------------------------------
 Function: getDfRegDramBase
 Purpose: Get the DF::DramBaseAddress register
 Inputs: An instanceID (CS), a nodeID (for the PCIe bus/device)
   and a register number (0 through 15)
 Outputs: The requested register
 *------------------------------------------------------------------*/
UINT32
getDfRegDramBase (
  UINT32 instanceId,
  UINT32 nodeId,
  UINT32 regNum
  )
{
  return (getDfReg (instanceId, nodeId, DF_DRAMBASE0_ADDR + (8*regNum)));
}

/*------------------------------------------------------------------
 Function: getDfRegDramLimit
 Purpose: Get the DF::DramLimitAddress register
 Inputs: An instanceID (CS), a nodeID (for the PCIe bus/device)
   and a register number (0 through 15)
 Outputs: The requested register
 *------------------------------------------------------------------*/
UINT32
getDfRegDramLimit (
  UINT32 instanceId,
  UINT32 nodeId,
  UINT32 regNum
  )
{
  return (getDfReg (instanceId, nodeId, DF_DRAMLIMIT0_ADDR + (8*regNum)));
}

/*------------------------------------------------------------------
 Function: getDfRegDramHoleCtrl
 Purpose: Get the DF::DramHoleControl register
 Inputs: An instanceID (CS) and a nodeID (for the PCIe bus/device)
 Outputs: The requested register
 *------------------------------------------------------------------*/
UINT32
getDfRegDramHoleCtrl (
  UINT32 instanceId,
  UINT32 nodeId
  )
{
  return (getDfReg (instanceId, nodeId, DF_DRAMHOLECTRL_ADDR));
}

/*------------------------------------------------------------------
 Function: extractIntLvAddrSel
 Purpose: Extract IntLvAddrSel from either DramBaseReg or DramLimitReg
 Inputs: DF2/DF3 mode, the DramBaseReg, and the DramLimitReg
 Outputs: The requested field
 *------------------------------------------------------------------*/
UINT32
extractIntLvAddrSel (
  UINT32 dfType,
  UINT32 dramBaseReg,
  UINT32 dramLimitReg
  )
{
  if (dfType == 2) {
    return( getBits(INTLVADDRSELLO_DF2, INTLVADDRSELHI_DF2, dramBaseReg));
  }
  return( getBits(INTLVADDRSELLO_DF3, INTLVADDRSELHI_DF3, dramBaseReg));
}

/*------------------------------------------------------------------
 Function: extractIntLvNumChan
 Purpose: Extract IntLvNumChan from either DramBaseReg or DramLimitReg
 Inputs: DF2/DF3 mode, the DramBaseReg, and the DramLimitReg
 Outputs: The requested field
 *------------------------------------------------------------------*/
UINT32
extractIntLvNumChan (
  UINT32 dfType,
  UINT32 dramBaseReg,
  UINT32 dramLimitReg
  )
{
  if (dfType == 2) {
    return (getBits (INTLVNUMCHANLO_DF2, INTLVNUMCHANHI_DF2, dramBaseReg));
  }
  return (getBits (INTLVNUMCHANLO_DF3, INTLVNUMCHANHI_DF3, dramBaseReg));
}

/*------------------------------------------------------------------
 Function: extractIntLvNumDies
 Purpose: Extract IntLvNumDies from either DramBaseReg or DramLimitReg
 Inputs: DF2/DF3 mode, the DramBaseReg, and the DramLimitReg
 Outputs: The requested field
 *------------------------------------------------------------------*/
UINT32
extractIntLvNumDies (
  UINT32 dfType,
  UINT32 dramBaseReg,
  UINT32 dramLimitReg
  )
{
  if (dfType == 2) {
    return (getBits (INTLVNUMDIESLO_DF2, INTLVNUMDIESHI_DF2, dramLimitReg));
  }
  return (getBits (INTLVNUMDIESLO_DF3, INTLVNUMDIESHI_DF3, dramBaseReg));
}

/*------------------------------------------------------------------
 Function: extractIntLvNumSkts
 Purpose: Extract IntLvNumSkts from either DramBaseReg or DramLimitReg
 Inputs: DF2/DF3 mode, the DramBaseReg, and the DramLimitReg
 Outputs: The requested field
 *------------------------------------------------------------------*/
UINT32
extractIntLvNumSkts (
  UINT32 dfType,
  UINT32 dramBaseReg,
  UINT32 dramLimitReg
  )
{
  if (dfType == 2) {
    return (getBit (INTLVNUMSKTS_DF2, dramLimitReg));
  }
  return (getBit (INTLVNUMSKTS_DF3, dramBaseReg));
}

/*------------------------------------------------------------------
 Function: extractDstFabricId
 Purpose: Extract DstFabricId from DramLimitReg
 Inputs: DF2/DF3 mode, the DramBaseReg, and the DramLimitReg
 Outputs: The requested field
 *------------------------------------------------------------------*/
UINT32
extractDstFabricId (
  UINT32 dfType,
  UINT32 dramLimitReg
  )
{
  if (dfType == 2) {
    return (getBits (DSTFABRICIDLO_DF2, DSTFABRICIDHI_DF2, dramLimitReg));
  }
  return (getBits (DSTFABRICIDLO_DF3, DSTFABRICIDHI_DF3, dramLimitReg));
}

/*----------------------------------------------------------------------------------------*/
/**
 * Convert socket/die/UMC number to the Nth UMC in the system (the same as Nth channel in the system,
 * since one channel per UMC on ZP)
 * The input parameter umc_chan_num is fixed to 0 on ZP
 *
 * @param[in] pkg_no            Socket ID (0..1)
 * @param[in] mpu_no            Die ID (0..3)
 * @param[in] umc_inst_num      UMC ID (0..1)
 * @param[in] umc_chan_num      always = 0 in ZP
 * @retval                      Nth channel in the system
 *----------------------------------------------------------------------------------------*/
UINTN
convert_to_addr_trans_index (
  UINTN  pkg_no,
  UINTN  mpu_no,
  UINTN  umc_inst_num,
  UINTN  umc_chan_num
  )
{
  UINTN    U_CH;
  UINTN    M_U_CH;

  U_CH = ((CHANNEL_PER_UMC * umc_inst_num) + umc_chan_num);
  M_U_CH = ((CHANNEL_PER_UMC * UMC_PER_DIE) * mpu_no) + U_CH;
  
  return (((CHANNEL_PER_UMC * UMC_PER_DIE * DIE_PER_SOCKET) * pkg_no) + M_U_CH);
}

BOOLEAN
internal_bit_wise_xor (
  UINT32  inp
  )
{
  BOOLEAN   t;
  UINT32    i;

  t = 0;
  for (i = 0; i < 32; i++) {
    t = t ^ ((inp >> i) & 0x1);
  }
  
  return t;
}

UINT32 
smnRegRead (
  UINTN   socket,
  UINTN   die,
  UINTN   umc,
  UINTN   ch,
  UINTN   offset,
  UINTN   BusNumberBase
  )
{
  UINTN   pciAddress;
  UINT32  smnIndex;
  UINT32  value;
  UINT32  umcSmnBase;

  pciAddress = (BusNumberBase << 20) + IOHC_NB_SMN_INDEX_2_BIOS;
  umcSmnBase = ((UINT32) umc) << 20;
  smnIndex = umcSmnBase + 0x50000 + (UINT32)offset;
  PciWrite32 (pciAddress, smnIndex);
  pciAddress = (BusNumberBase << 20) + IOHC_NB_SMN_DATA_2_BIOS;
  value = PciRead32 (pciAddress);
  return value;
}

/*----------------------------------------------------------------------------------------*/
/**
 * this function returns the (number of "1"s in inp)+8. mainly used to count it in CSMask
 *----------------------------------------------------------------------------------------*/
UINT32
popcnt (
  UINT32  inp
  )
{ 
  UINT32    ans=0, i=0;

  for (i = 0; i < 32; i++) {
    if ((inp >> i) & 0x1) {
      ans ++;
    }
  }
  return (ans + 8);
}

UINT32
popcnt64 (
  UINT64  inp
  )
{ 
  UINT32    ans=0, i=0;

  for (i = 0; i < 64; i++) {
    if ((inp >> i) & 0x1) {
      ans ++;
    }
  }
  return (ans + 8);
}

/*----------------------------------------------------------------------------------------*/
/**
 *  
 *----------------------------------------------------------------------------------------*/
VOID
NormalizedToBankAddrMap (
  UINT64  ChannelAddr,
  UINT64 CSMasksec,
  UINT8 *Bank,
  UINT32 *Row,
  UINT16 *Col,
  UINT8 *Rankmul,
  UINT8 numbankbits,
  UINT8 bank4,
  UINT8 bank3,
  UINT8 bank2,
  UINT8 bank1,
  UINT8 bank0,
  UINT8 numrowlobits,
  UINT8 numrowhibits,
  UINT8 numcolbits,
  UINT8 row_lo0,
  UINT8 row_hi0,
  UINT32 COL0REG,
  UINT32 COL1REG,
  UINT8 numcsbits,
  UINT8 rm0,
  UINT8 rm1,
  UINT8 rm2,
  UINT8 invertmsbse,
  UINT8 invertmsbso,
  UINT8 rm0sec,
  UINT8 rm1sec,
  UINT8 rm2sec,
  UINT8 invertmsbsesec,
  UINT8 invertmsbsosec,
  UINT8 SEC,
  UINT8 cs,
  UINT32 addrhashbank0,
  UINT32 addrhashbank1,
  UINT32 addrhashbank2,
  UINT32 addrhashbank3,
  UINT32 addrhashbank4
  )
{
  if(SEC==3) {
    //IDS_HDT_CONSOLE (MAIN_FLOW, "ERROR: SEC value cannot be 3\n");
    DEBUG((EFI_D_ERROR, "ERROR: SEC value cannot be 3\n"));

    ASSERT (FALSE);
  }
     
  //if addrhash is enabled, we can get bank after gettting row and col
  if (((addrhashbank0 & 0x1) == 0) && ((addrhashbank1 & 0x1) == 0) && ((addrhashbank2 & 0x1) == 0) &&
      ((addrhashbank3 & 0x1) == 0) && ((addrhashbank4 & 0x1) == 0)) {
        *Bank = (numbankbits == 3) ? (((ChannelAddr >> (bank0 + 5)) & 0x1) | 
                                (((ChannelAddr >> (bank1 + 5)) & 0x1) << 1) | 
                                (((ChannelAddr >> (bank2 + 5)) & 0x1) << 2)) : 
            (numbankbits == 4) ? (((ChannelAddr >> (bank0 + 5)) & 0x1) | (((ChannelAddr >> (bank1 + 5)) & 0x1) << 1) | 
                                (((ChannelAddr >> (bank2 + 5)) & 0x1) << 2) | (((ChannelAddr >> (bank3 + 5)) & 0x1) << 3)) : 
                                (((ChannelAddr >> (bank0 + 5)) & 0x1) | (((ChannelAddr >> (bank1 + 5)) & 0x1) << 1) | 
                                (((ChannelAddr >> (bank2 + 5)) & 0x1) << 2) | (((ChannelAddr >> (bank3 + 5)) & 0x1) << 3) | 
                                (((ChannelAddr >> (bank4 + 5)) & 0x1) << 4));
  }   // if addr hash is disabled

  if((numcolbits >= 5) && (numcolbits <= 8)) {
    *Col = ( (ChannelAddr >> (((COL0REG >> 0) & 0xF) + 2)) & 0x1 ) | (( (ChannelAddr >> (((COL0REG >> 4) & 0xF) + 2)) & 0x1 ) << 1) |
      (( (ChannelAddr >> (((COL0REG >> 8) & 0xF) + 2)) & 0x1 ) << 2) | (( (ChannelAddr >> (((COL0REG >> 12) & 0xF) + 2)) & 0x1 ) << 3) |
      (( (ChannelAddr >> (((COL0REG >> 16) & 0xF) + 2)) & 0x1 ) << 4) | (( (ChannelAddr >> (((COL0REG >> 20) & 0xF) + 2)) & 0x1 ) << 5) |
      (( (ChannelAddr >> (((COL0REG >> 24) & 0xF) + 2)) & 0x1 ) << 6) | (( (ChannelAddr >> (((COL0REG >> 28) & 0xF) + 2)) & 0x1 ) << 7);
   } else {
     *Col = ( (ChannelAddr >> (((COL0REG >> 0) & 0xF) + 2)) & 0x1 ) | (( (ChannelAddr >> (((COL0REG >> 4) & 0xF) + 2)) & 0x1 ) << 1) |
       (( (ChannelAddr >> (((COL0REG >> 8) & 0xF) + 2)) & 0x1 ) << 2) | (( (ChannelAddr >> (((COL0REG >> 12) & 0xF) + 2)) & 0x1 ) << 3) |
       (( (ChannelAddr >> (((COL0REG >> 16) & 0xF) + 2)) & 0x1 ) << 4) | (( (ChannelAddr >> (((COL0REG >> 20) & 0xF) + 2)) & 0x1 ) << 5) |
       (( (ChannelAddr >> (((COL0REG >> 24) & 0xF) + 2)) & 0x1 ) << 6) | (( (ChannelAddr >> (((COL0REG >> 28) & 0xF) + 2)) & 0x1 ) << 7) |

       ( ((ChannelAddr >> (((COL1REG >> 0) & 0xF) + 8)) & 0x1) << 8 ) | (( (ChannelAddr >> (((COL1REG >> 4) & 0xF) + 8)) & 0x1 ) << 9) |
       (( (ChannelAddr >> (((COL1REG >> 8) & 0xF) + 8)) & 0x1 ) << 10) | (( (ChannelAddr >> (((COL1REG >> 12) & 0xF) + 8)) & 0x1 ) << 11) |
       (( (ChannelAddr >> (((COL1REG >> 16) & 0xF) + 8)) & 0x1 ) << 12) | (( (ChannelAddr >> (((COL1REG >> 20) & 0xF) + 8)) & 0x1 ) << 13) |
       (( (ChannelAddr >> (((COL1REG >> 24) & 0xF) + 8)) & 0x1 ) << 14) | (( (ChannelAddr >> (((COL1REG >> 28) & 0xF) + 8)) & 0x1 ) << 15);
  }
  *Col = *Col & (((UINT16) pow_ras (2, numcolbits)) - 1);

  *Row = (UINT32) (((ChannelAddr >> (row_lo0 + 12)) & ((UINT32) pow_ras (2, numrowlobits) - 1)) |
                   (((ChannelAddr >> (row_hi0 + 24)) & ((UINT32) pow_ras (2, numrowhibits) - 1)) << numrowlobits));

  //We will need to adjust row taking into account the InvertMSBsE/O for that Pr/Sec rank
  //Row =  Row[Msb] ^ InvertMsbE/O of Pri/SEC[1]<<Msb| Row[Msb-1] ^ InvertMsbE/O of Pri/SEC[0]<<Msb-1| Row & (2^(total number of row bits-2)-1)
  if (SEC != 2) {
    if (numrowhibits == 0) {
      *Row = ((((*Row >> (numrowlobits - 1)) & 1) ^ ((cs % 2) ? (SEC ? ((invertmsbsosec >> 1) & 1) : ((invertmsbso >> 1) & 1)) :
                                                     (SEC ? ((invertmsbsesec >> 1) & 1) : ((invertmsbse >> 1) & 1)))) << (numrowlobits - 1)) |
        ((((*Row >> (numrowlobits - 2)) & 1) ^ ((cs % 2) ? (SEC ? ((invertmsbsosec >> 0) & 1) : ((invertmsbso >> 0) & 1)) :
                                                (SEC? ((invertmsbsesec >> 0) & 1) : ((invertmsbse >> 0) & 1)))) << (numrowlobits - 2)) |
        (*Row & (((UINT32) pow_ras (2, numrowlobits - 2)) - 1));
    } else {

      *Row = ((((*Row >> (numrowlobits + numrowhibits - 1)) & 1 ) ^ ((cs % 2) ? (SEC ? ((invertmsbsosec >> 1) & 1) : ((invertmsbso >> 1) & 1)) :
                                                                     (SEC ? ((invertmsbsesec >> 1) & 1) : ((invertmsbse >> 1) & 1)))) << (numrowlobits + numrowhibits - 1)) |
        ((((*Row >> (numrowlobits + numrowhibits - 2)) & 1 ) ^ ((cs % 2) ? (SEC ? ((invertmsbsosec >> 0) & 1) : ((invertmsbso >> 0) & 1)) :
                                                                (SEC ? ((invertmsbsesec >> 0) & 1) : ((invertmsbse >> 0) & 1)))) << (numrowlobits + numrowhibits - 2)) |
        (*Row & (((UINT32) pow_ras (2, numrowlobits + numrowhibits - 2)) - 1));
    }
  }

  //Asymm dimms: here we go
  if (SEC==2) {
    if ((cs % 2) == 1) {
      *Row = ((ChannelAddr >> (row_lo0 + 12)) & ((UINT32) pow_ras (2, (((popcnt64 (CSMasksec) - numcsbits) == 32) ? 15 : ((popcnt64 (CSMasksec) - numcsbits) == 33) ? 16 : 17)) - 1));
    }
  }

  if ((addrhashbank0 & 0x1) || (addrhashbank1 & 0x1) || (addrhashbank2 & 0x1) || (addrhashbank3 & 0x1) || (addrhashbank4 & 0x1)) {
    *Bank = (numbankbits == 3) ? ((ChannelAddr >> (bank0 + 5) & 0x1) | 
                                  ((ChannelAddr >> (bank1 + 5) & 0x1) << 1) | 
                                  ((ChannelAddr >> (bank2 + 5) & 0x1) << 2)) : 
        (numbankbits == 4) ? ((ChannelAddr >> (bank0 + 5) & 0x1) | 
                              ((ChannelAddr >> (bank1 + 5) & 0x1) << 1) | 
                              ((ChannelAddr >> (bank2 + 5) & 0x1) << 2) | 
                              ((ChannelAddr >> (bank3 + 5) & 0x1) << 3) ) : 
                              ((ChannelAddr >> (bank0 + 5) & 0x1) | 
                              ((ChannelAddr >> (bank1 + 5) & 0x1) << 1) | 
                              ((ChannelAddr >> (bank2 + 5) & 0x1) << 2) | 
                              ((ChannelAddr >> (bank3 + 5) & 0x1) << 3) | 
                              ((ChannelAddr >> (bank4 + 5) & 0x1) << 4));

    gAddrData->addrhash[0] = ((internal_bit_wise_xor(*Col & ((addrhashbank0 >> 1) & 0x1fff))) 
                  ^ (internal_bit_wise_xor(*Row & ((addrhashbank0 >> 14) & 0x3ffff)))) & (addrhashbank0 & 1);

    gAddrData->addrhash[1] = ((internal_bit_wise_xor(*Col & ((addrhashbank1 >> 1) & 0x1fff))) 
                  ^ (internal_bit_wise_xor(*Row & ((addrhashbank1 >> 14) & 0x3ffff)))) & (addrhashbank1 & 1);

    gAddrData->addrhash[2] = ((internal_bit_wise_xor(*Col & ((addrhashbank2 >> 1) & 0x1fff))) 
                  ^ (internal_bit_wise_xor(*Row & ((addrhashbank2 >> 14) & 0x3ffff)))) & (addrhashbank2 & 1);

    gAddrData->addrhash[3] = ((internal_bit_wise_xor(*Col & ((addrhashbank3 >> 1) & 0x1fff))) 
                  ^ (internal_bit_wise_xor(*Row & ((addrhashbank3 >> 14) & 0x3ffff)))) & (addrhashbank3 & 1);

    gAddrData->addrhash[4] = ((internal_bit_wise_xor(*Col & ((addrhashbank4 >> 1) & 0x1fff))) 
                  ^ (internal_bit_wise_xor(*Row & ((addrhashbank4 >> 14) & 0x3ffff)))) & (addrhashbank4 & 1);
  
    *Bank = (numbankbits == 3) ? ((((addrhashbank0 & 0x1) == 1) ? (gAddrData->addrhash[0] ^ (*Bank & 0x1)) : (*Bank & 0x1)) | 
                                  ((((addrhashbank1 & 0x1) == 1) ? (gAddrData->addrhash[1] ^ ((*Bank >> 1) & 0x1)) : ((*Bank >> 1) & 0x1)) << 1) | 
                                  ((((addrhashbank2 & 0x1) == 1) ? (gAddrData->addrhash[2] ^ ((*Bank >> 2) & 0x1)) : ((*Bank >> 2) & 0x1)) << 2)) : 
            (numbankbits == 4) ? ((((addrhashbank0 & 0x1) == 1) ? (gAddrData->addrhash[0] ^ (*Bank & 0x1)) : (*Bank & 0x1)) | 
                                  ((((addrhashbank1 & 0x1) == 1) ? (gAddrData->addrhash[1] ^ ((*Bank >> 1) & 0x1)) : ((*Bank >> 1) & 0x1)) << 1) | 
                                  ((((addrhashbank2 & 0x1) == 1) ? (gAddrData->addrhash[2] ^ ((*Bank >> 2) & 0x1)) : ((*Bank >> 2) & 0x1)) << 2) | 
                                  ((((addrhashbank3 & 0x1) == 1) ? (gAddrData->addrhash[3] ^ ((*Bank >> 3) & 0x1)) : ((*Bank >> 3) & 0x1)) << 3)) : 
                                  ((((addrhashbank0 & 0x1) == 1) ? (gAddrData->addrhash[0] ^ (*Bank & 0x1)) : (*Bank & 0x1)) | 
                                  ((((addrhashbank1 & 0x1) == 1) ? (gAddrData->addrhash[1] ^ ((*Bank >> 1) & 0x1)) : ((*Bank >> 1) & 0x1)) << 1) | 
                                  ((((addrhashbank2 & 0x1) == 1) ? (gAddrData->addrhash[2] ^ ((*Bank >> 2) & 0x1)) : ((*Bank >> 2) & 0x1)) << 2) | 
                                  ((((addrhashbank3 & 0x1) == 1) ? (gAddrData->addrhash[3] ^ ((*Bank >> 3) & 0x1)) : ((*Bank >> 3) & 0x1)) << 3) | 
                                  ((((addrhashbank4 & 0x1) == 1) ? (gAddrData->addrhash[4] ^ ((*Bank >> 4) & 0x1)) : ((*Bank >> 4) & 0x1)) << 4));
  }

  if(0 == SEC) {
    if (numcsbits == 0) {
      *Rankmul = 0;

    } else if (numcsbits == 1) {
      *Rankmul = (ChannelAddr >> (rm0 + 12)) & 1;

    } else if (numcsbits == 2) {
      *Rankmul = ((ChannelAddr >> (rm0 + 12)) & 1) | (((ChannelAddr >> (rm1 + 12)) & 1) << 1);

    } else {
      *Rankmul = ((ChannelAddr >> (rm0 + 12)) & 1) | (((ChannelAddr >> (rm1 + 12)) & 1) << 1) | (((ChannelAddr >> (rm2 + 12)) & 1) << 2);
    }
  } else {
    if (numcsbits == 0) {
      *Rankmul = 0;

    } else if (numcsbits == 1) {
      *Rankmul = (ChannelAddr>> (rm0sec + 12)) & 1;

    } else if (numcsbits == 2) {
      *Rankmul = ((ChannelAddr >> (rm0sec + 12)) & 1) | (((ChannelAddr >> (rm1sec + 12)) & 1) << 1);

    } else {
      *Rankmul = ((ChannelAddr >> (rm0sec + 12)) & 1) | (((ChannelAddr >> (rm1sec + 12)) & 1) << 1) | (((ChannelAddr >> (rm2sec + 12)) & 1) << 2);
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Convert normalized address to chip select, row, column, bank, rankmul
 * 
 * ChannelAddr expected to be passed from the caller should be till lsb=0 and only msb=39 is considered
 * no fancy 39:4 version
 * pkg_no: socket number
 * mpu_no: die number 
 *
 *----------------------------------------------------------------------------------------*/
VOID
translate_norm_to_dram_addr (
  UINT64  ChannelAddr,
  UINT8   pkg_no,
  UINT8   mpu_no,
  UINT8   umc_inst_num, 
  UINT8   umc_chan_num,
  UINT8   *cs_num,
  UINT8   *bank,
  UINT32  *row,
  UINT16  *col,
  UINT8   *rankmul
  )
{
  UINT32  CSBase=0, CSMask=0,CSBasesec=0, CSMasksec=0;
  UINT8   Bank=0,Rankmul=0;
  UINT32  Row=0;
  UINT16  Col=0;
  UINT8   SEC = 0;

  UINT64  temp=0; 
  UINT8   cs=0 ;

  BOOLEAN CSEn=0,CSEnsec=0;
  UINT8   Chipselect=0;
  UINT8   noofbank=0, noofrm=0, noofrowlo=0, noofrowhi=0, noofcol=0, bank0=0, bank1=0, bank2=0,bank3=0,bank4=0;
  UINT8   numrowlobits=0, numrowhibits=0, numcolbits=0, numcsbits=0,  numbankbits=0;
  UINT8   row_lo0=0, row_hi0=0, rm0=0, rm1=0,rm2=0, invertmsbse=0, invertmsbso=0;
  UINT8   rm0sec=0, rm1sec=0,rm2sec=0, invertmsbsesec=0, invertmsbsosec=0;
  UINT32  COL0REG=0, COL1REG=0;
  UINT32  addrhashbank0=0,addrhashbank1=0,addrhashbank2=0,addrhashbank3=0,addrhashbank4=0;
  UINTN   channelId;
  UINT32  InputAddr;
  UINT8   rankmul_temp;

  // channelId: channel ID of system
  umc_chan_num = 0;   // umc_chan_num = 0 in SSP
  channelId = convert_to_addr_trans_index(pkg_no, mpu_no, umc_inst_num, umc_chan_num);
  
  //get_highest_possible_addr_bit(pkg_no, mpu_no, umc_inst_num, umc_chan_num);
         
  //read out the addrhash* registers here
  addrhashbank0 = gAddrData->ADDRHASHBANK0 [channelId];
  addrhashbank1 = gAddrData->ADDRHASHBANK1 [channelId];
  addrhashbank2 = gAddrData->ADDRHASHBANK2 [channelId];
  addrhashbank3 = gAddrData->ADDRHASHBANK3 [channelId];
  addrhashbank4 = gAddrData->ADDRHASHBANK4 [channelId];

  for (cs = 0; cs < 4; ++cs) {    // nhu CSBASESEC[][y], retrieve_regs just save register data to [3:0], need to change to cs < 4
    CSBase = gAddrData->CSBASE[channelId][cs] & 0xffffffff; 
    CSMask = gAddrData->CSMASK[channelId][cs >> 1] & 0xffffffff;

    //Secondary decoder stuff for each primary
    CSBasesec = gAddrData->CSBASESEC[channelId][cs] & 0xffffffff;
    CSMasksec = gAddrData->CSMASKSEC[channelId][cs >> 1] & 0xffffffff; 

    // UMC0CHx00000000 [DRAM CS Base Address][31:1]: Base Address[39:9], shift error address right 8 bit to match BaseAddr
    InputAddr = (ChannelAddr >> 8) & 0xffffffff;

	//Read out *RAMCFG*
    temp = gAddrData->CONFIGDIMM[channelId][cs >> 1];
    CSEn = (temp >> (cs & 0x1)) & 1;

    //Secodnary decoder stuff
    //[25:24]  of CONFIGDIMM is the cssec [1:0]
    CSEnsec = (cs & 0x1) ? ((temp >> 25) & 0x1) : ((temp >> 24) & 0x1);

    if ((CSEn && ((InputAddr & ~CSMask) == (CSBase & ~CSMask))) ||
        (CSEnsec && ((InputAddr & ~CSMasksec) == (CSBasesec & ~CSMasksec)))) {

      // Hashing
      // Dealing with cshash..
      Chipselect = 0 ;
      if (gAddrData->ADDRHASHNORMADDR[channelId][0] & 0x1) {
        Chipselect = (internal_bit_wise_xor ((gAddrData->ADDRHASHNORMADDR[channelId][0] >> 1) & (ChannelAddr >> 9))) ^ (cs & 0x1);
      } else {
        Chipselect = cs & 0x1;
      }

      if (gAddrData->ADDRHASHNORMADDR[channelId][1] & 0x1) {
        Chipselect |= ((internal_bit_wise_xor ((gAddrData->ADDRHASHNORMADDR[channelId][1] >> 1) & (ChannelAddr >> 9))) ^ ((cs >> 1) & 0x1)) << 1;
      } else {
        Chipselect |= ((cs >> 1) & 0x1) << 1;
      }

      if(gAddrData->ADDRHASHNORMADDR[channelId][2] & 0x1) {
        Chipselect |= ((internal_bit_wise_xor ((gAddrData->ADDRHASHNORMADDR[channelId][2] >> 1) & (ChannelAddr >> 9))) ^ ((cs >> 2) & 0x1)) << 2;
      } else {
        Chipselect |= ((cs >> 2) & 0x1) << 2;
      }
      // Hashing end

      SEC = (CSEn && ((InputAddr & ~CSMask) == (CSBase & ~CSMask))) ? 0 : 
          (CSEnsec && ((InputAddr & ~CSMasksec) == (CSBasesec & ~CSMasksec)) && CSEn) ? 1 :
          (CSEnsec && ((InputAddr & ~CSMasksec) == (CSBasesec & ~CSMasksec)) && !CSEn)? 2 : 3;
      InputAddr = 0;

      noofbank = (temp >> 4) & 0x3;
      noofrm  = (temp >> 6) & 0x3;
      noofrowlo = (temp >> 8) & 0xf; 
      noofrowhi = (temp >> 12) & 0xf; 
      noofcol = (temp >> 16) & 0xf;

	  // Read out *BANK_SEL*
      temp = gAddrData->BANKSELDIMM[channelId][cs >> 1]; 
	  bank0 = temp & 0xf;
	  bank1 = (temp >> 4) & 0xf;
	  bank2 = (temp >> 8) & 0xf;
	  bank3 = (temp >> 12) & 0xf;
	  bank4 = (temp >> 16) & 0xf;

      break;
    }   //csen inputaddr loop
  }   //cs loop
  
  //IDS_HDT_CONSOLE (MAIN_FLOW, "noofbank = %d, noofrm = %d, noofrwolo = %d, noofrowhi = %d, noofcol = %d\n",
  //                 noofbank, noofrm, noofrowlo, noofrowhi, noofcol)
  DEBUG((EFI_D_ERROR, "noofbank = %d, noofrm = %d, noofrwolo = %d, noofrowhi = %d, noofcol = %d\n", noofbank, noofrm, noofrowlo, noofrowhi, noofcol));

  if (((gAddrData->RANK_ENABLE_PER_UMCCH_ADDR_TRANS[channelId] >> cs) & 0x1) == 0) {
    //IDS_HDT_CONSOLE (MAIN_FLOW, "ERROR: Rank is out of bounds\n");
    DEBUG((EFI_D_ERROR, "ERROR: Rank is out of bounds\n", noofbank, noofrm, noofrowlo, noofrowhi, noofcol));
  }

	//Read out *ROW_SEL*
  temp = gAddrData->ROWSELDIMM[channelId][cs >> 1];
  row_lo0 = (temp >> 0) & 0xf;
  row_hi0 = (temp >> 4) & 0xf;

  //Read out *COL0_SEL*
  COL0REG = gAddrData->COL0SELDIMM[channelId][cs >> 1];

  //Read out *COL1_SEL*
  COL1REG = gAddrData->COL1SELDIMM[channelId][cs >> 1];

  //Read out *RM_SEL*
  temp = gAddrData->RMSELDIMM[channelId][cs >> 1];
  rm0 = (temp >> 0) & 0xf; 
  rm1 = (temp >> 4) & 0xf; 
  rm2 = (temp >> 8) & 0xf;
  invertmsbse = (temp >> 16) & 0x3;
  invertmsbso = (temp >> 18) & 0x3;

  temp = gAddrData->RMSELDIMMSEC[channelId][cs >> 1];
  rm0sec = (temp >> 0) & 0xf; 
  rm1sec = (temp >> 4) & 0xf; 
  rm2sec = (temp >> 8) & 0xf;
  invertmsbsesec = (temp >> 16) & 0x3;
  invertmsbsosec = (temp >> 18) & 0x3;

  numrowlobits = noofrowlo + 10;
  numrowhibits = noofrowhi;
  numcolbits = noofcol + 5;
  numcsbits = noofrm; 
  numbankbits = (noofbank == 2) ? 5 : (noofbank == 1) ? 4 : 3;    // UMC0CHx00000030 [DRAM Address Configuration][21:20]

  //Let us see if we need to swizzle or not
  temp = gAddrData->CTRLREG[channelId][cs >> 1]; 
  //IDS_HDT_CONSOLE (MAIN_FLOW, "RowLoBits = %d, RowHiBits = %d, ColBits = %d, CsBits = %d, BankBits = %d\n",
  //                 numrowlobits, numrowhibits, numcolbits, numcsbits, numbankbits);
  DEBUG((EFI_D_ERROR, "RowLoBits = %d, RowHiBits = %d, ColBits = %d, CsBits = %d, BankBits = %d\n", numrowlobits, numrowhibits, numcolbits, numcsbits, numbankbits));

  NormalizedToBankAddrMap (ChannelAddr, CSMasksec, &Bank, &Row, &Col, &Rankmul, numbankbits, bank4, bank3, bank2, bank1, bank0,
                           numrowlobits, numrowhibits, numcolbits, row_lo0, row_hi0, COL0REG, COL1REG, numcsbits, rm0, rm1, rm2,
                           invertmsbse, invertmsbso, rm0sec, rm1sec, rm2sec, invertmsbsesec, invertmsbsosec, SEC, cs,
                           addrhashbank0, addrhashbank1, addrhashbank2, addrhashbank3, addrhashbank4);
      
  rankmul_temp=0;

  if((gAddrData->ADDRHASHRMADDR[channelId][0] & 1) && (noofrm >= 1)) {
    rankmul_temp = ((internal_bit_wise_xor((gAddrData->ADDRHASHRMADDR[channelId][0] >> 1) & (ChannelAddr >> 9))) ^ (Rankmul & 0x1));
  } else {
    rankmul_temp = Rankmul & 0x1;
  }

  if((gAddrData->ADDRHASHRMADDR[channelId][1] & 0x1) && (noofrm >= 2)) {
    rankmul_temp =  rankmul_temp | (((internal_bit_wise_xor ((gAddrData->ADDRHASHRMADDR[channelId][1] >> 1) & (ChannelAddr >> 9))) ^ ((Rankmul >> 1) & 0x1)) << 1);
  } else {
    rankmul_temp = rankmul_temp |(((Rankmul >> 1) & 0x1) << 1);
  }

  if((gAddrData->ADDRHASHRMADDR[channelId][2] & 0x1) && (noofrm >= 3)) {
    rankmul_temp =  rankmul_temp | (((internal_bit_wise_xor ((gAddrData->ADDRHASHRMADDR[channelId][2] >> 1) & (ChannelAddr >> 9))) ^ ((Rankmul >> 2) & 0x1)) << 2);
  } else {
    rankmul_temp = rankmul_temp | (((Rankmul >> 2) & 0x1) << 2);
  }

  *cs_num = Chipselect;
  *bank = Bank;
  *row = Row;
  *col = Col;
  *rankmul = rankmul_temp;
       
  // Check if the outputs respect the config
  if (Bank >= ((noofbank == 2) ? 32 : ((noofbank == 1) ? 16 : 8))) {
    //IDS_HDT_CONSOLE (MAIN_FLOW, "ERROR: Bank of the Given NormAddr is out of bounds\n");
    DEBUG((EFI_D_ERROR, "ERROR: Bank of the Given NormAddr is out of bounds\n"));
  }

  if (Row >= (UINT32) (pow_ras (2, (noofrowlo + 10 + noofrowhi)))) {
    //IDS_HDT_CONSOLE (MAIN_FLOW, "ERROR: Row of the Given NormAddr is out of bounds\n");
    DEBUG((EFI_D_ERROR, "ERROR: Row of the Given NormAddr is out of bounds\n"));
  }

  if (Col >= (UINT16)(pow_ras (2, (noofcol + 5)))) {
    //IDS_HDT_CONSOLE (MAIN_FLOW, "ERROR: Col of the Given NormAddr is out of bounds\n");
    DEBUG((EFI_D_ERROR, "ERROR: Row of the Given NormAddr is out of bounds\n"));
  }
}

/*------------------------------------------------------------------
 Function: checkDramHit

 Purpose: Lookup a system address in the DRAM address map.

 Parameters (all are input only)
   sysAddr (ulong)
     The address to be converted.
     The user must remove all VMGuard key indices from the system address.
 Returns:
   The destination (CS) fabric ID

 Side Effects:
   None:

 Limitations:
   - Does not support non-power-of-2 channels (not used on ZP)

 *------------------------------------------------------------------*/
UINT32
checkDramHit (
  UINT64  sysAddr
  )
{
  UINT64  dramBaseAddr;
  UINT64  dramLimitAddr;

  UINT32  dramBaseReg;
  UINT32  dramLimitReg;
  UINT32  systemFabricIdReg;
  UINT32  sysAddrLo;
  UINT32  sysAddrHi;
  UINT32  fabricBlockInstanceInformation0Reg;

  UINT32  addrRngVal;
  UINT32  dstFabricId;
  UINT32  ccmInstanceId;
  UINT32  intLvAddrSel;
  UINT32  intLvAddrBit;
  UINT32  intLvNumDies;
  UINT32  intLvNumChan;
  UINT32  firstDieIdBit;
  UINT32  firstSocketIdBit;
  UINT32  csId;
  UINT32  numSocketsInterleaved;
  UINT32  numDieInterleaved=0;
  UINT32  numChanInterleaved=0;
  UINT32  numInterleaveBits=0;
  UINT32  hashEnabled;
  UINT32  socketIdShift;
  UINT32  socketIdMask;
  UINT32  dieIdMask;
  UINT32  dieIdShift;
  UINT32  addrMapNum;
  UINT32  nodeId;
  UINT32  dfType;
  UINT32  numDFInstances;
  UINT32  i;
  UINT32  instanceType;

  nodeId = 0;
  sysAddrLo = (UINT32) sysAddr;
  sysAddrHi = (UINT32) (sysAddr >> 32);

  dfType = determineDfType ();

  // Find a CCM instance ID
  ccmInstanceId = 0xFFFFFFFF;
  numDFInstances = getBits (BLKINSTCOUNTLO, BLKINSTCOUNTHI, getDfRegFabricBlkInstanceCnt (0));
  for (i = 0; i < numDFInstances; i++) {
    fabricBlockInstanceInformation0Reg = getDfRegFabricBlkInstInfo0(0, i);
    // Skip gated blocks (detected because at least one bit must be non-zero in non-gated blocks)
    if (fabricBlockInstanceInformation0Reg == 0) {
      continue;
    }
    instanceType = getBits (INSTANCETYPELO, INSTANCETYPEHI, fabricBlockInstanceInformation0Reg);
    if (instanceType == CCMINSTANCETYPE) {
      ccmInstanceId = i;
      break;
    }
  }
  IDS_HDT_CONSOLE (MAIN_FLOW, "checkDramHit, ccmInstanceId = %d\n", ccmInstanceId);
  //ASSERT (ccmInstanceId >= 0);

  for (addrMapNum=0; addrMapNum < NUM_DRAM_MAPS; addrMapNum++) {
    dramBaseReg = getDfRegDramBase(ccmInstanceId, nodeId, addrMapNum);
    addrRngVal = getBit (ADDRRNGVAL, dramBaseReg);
    if (addrRngVal == 0) {
      continue;
    }
    dramLimitReg = getDfRegDramLimit (ccmInstanceId, nodeId, addrMapNum);
    dramBaseAddr = getBits (DRAMBASEADDRLO, DRAMBASEADDRHI, dramBaseReg);
    dramBaseAddr = dramBaseAddr << 28;

    dramLimitAddr = getBits (DRAMLIMITADDRLO, DRAMLIMITADDRHI, dramLimitReg);
    dramLimitAddr = dramLimitAddr << 28;
    dramLimitAddr |= ((UINT64) 0x0FFFFFFF);

    if ((sysAddr >= dramBaseAddr) && (sysAddr <= dramLimitAddr)) {
      if (dfType == 2) {
        systemFabricIdReg = getDfRegSystemFabricIdMask (nodeId);
        socketIdShift = getBits (SOCKETIDSHIFTLO_DF2, SOCKETIDSHIFTHI_DF2, systemFabricIdReg);
        socketIdMask = getBits (SOCKETIDMASKLO_DF2, SOCKETIDMASKHI_DF2, systemFabricIdReg);
        dieIdShift = getBits (DIEIDSHIFTLO_DF2, DIEIDSHIFTHI_DF2, systemFabricIdReg);
        dieIdMask = getBits (DIEIDMASKLO_DF2, DIEIDMASKHI_DF2, systemFabricIdReg);

      } else {
        systemFabricIdReg = getDfRegSystemFabricIdMask1 (nodeId);
        socketIdShift = getBits (SOCKETIDSHIFTLO_DF3, SOCKETIDSHIFTHI_DF3, systemFabricIdReg);
        socketIdMask = getBits (SOCKETIDMASKLO_DF3, SOCKETIDMASKHI_DF3, systemFabricIdReg);
        dieIdShift = getBits (DIEIDSHIFTLO_DF3, DIEIDSHIFTHI_DF3, systemFabricIdReg);
        dieIdMask = getBits (DIEIDMASKLO_DF3, DIEIDMASKHI_DF3, systemFabricIdReg);
      }
      
      // hit, now figure out the DstFabricId.
      intLvAddrSel = extractIntLvAddrSel (dfType, dramBaseReg, dramLimitReg);
      //assert (getBit(2, intLvAddrSel) == 0);
      intLvAddrBit = (getBit (1, (UINT32) intLvAddrSel) ? (getBit (0, (UINT32) intLvAddrSel) ? 11 : 10) : (getBit (0, (UINT32) intLvAddrSel) ? 9 : 8));

      intLvNumChan = extractIntLvNumChan(dfType, dramBaseReg, dramLimitReg);

      numChanInterleaved = 1;   // For compiler error
      numDieInterleaved = 1;    // For compiler error

      hashEnabled = FALSE;
      switch (intLvNumChan) {
      case 0:
        numChanInterleaved = 1;
        numInterleaveBits = 0;
        break;
      case 1:
        numChanInterleaved = 2;
        numInterleaveBits = 1;
        break;
      case 3:
        numChanInterleaved = 4;
        numInterleaveBits = 2;
        break;
      case 5:
        numChanInterleaved = 8;
        numInterleaveBits = 3;
        break;
      //case 7:
      //  numChanInterleaved = 16;
      //  numInterleaveBits = 4;
      //  break;
      //case 8:
      //  numChanInterleaved = 32;
      //  numInterleaveBits = 1;
      //  hashEnabled = TRUE;
      //  break;
      case 12:
        numChanInterleaved = 2;
        numInterleaveBits = 1;
        hashEnabled = TRUE;
        break;
      case 13:
        numChanInterleaved = 4;
        numInterleaveBits = 2;
        hashEnabled = TRUE;
        break;
      case 14:
        numChanInterleaved = 8;
        numInterleaveBits = 3;
        hashEnabled = TRUE;
        break;
      }

      // If we are using address hashing, the interleave address bit must be 8 or 9.
      ASSERT (!hashEnabled || (intLvAddrSel == 0) || (intLvAddrSel == 1));

      intLvNumDies = extractIntLvNumDies (dfType, dramBaseReg, dramLimitReg);
      //assert (intLvNumDies != 3);
      switch (intLvNumDies) {
        case 0:
          numDieInterleaved = 1;
          break;
        case 1:
          numDieInterleaved = 2;
          numInterleaveBits += 1;
          break;
        case 2:
          numDieInterleaved = 4;
          numInterleaveBits += 2;
          break;
        case 3:
          numDieInterleaved = 8;
          numInterleaveBits += 3;
          break;
        default:
          ASSERT (0);
      }

      numSocketsInterleaved = extractIntLvNumSkts (dfType, dramBaseReg, dramLimitReg) + 1;
      numInterleaveBits += (numSocketsInterleaved - 1);
      //assert (numInterleaveBits <= 4);

      dstFabricId = extractDstFabricId (dfType, dramLimitReg);

      // If we are using the COD hashing functions, socket/die interleaving must be disabled.
      if ((intLvNumChan >= 12) && (intLvNumChan <= 14)) {
        ASSERT (numDieInterleaved == 1);
        ASSERT (numSocketsInterleaved == 1);
      }

      // Calculate the CSID that we take from the address.
      firstDieIdBit = intLvAddrBit;
      if (numChanInterleaved > 1) {
        if (intLvNumChan == 8) {    // 2 channel interleaving
          // CSSelect[0] = XOR of sysAddr{intLvAddrBit, 12, 18, 21, 30}
          dstFabricId += (getBit64 (intLvAddrBit, sysAddr) ^
                          getBit (12, sysAddrLo) ^
                          getBit (18, sysAddrLo) ^
                          getBit (21, sysAddrLo) ^
                          getBit (30, sysAddrLo));
        } else if (intLvNumChan == 12) {    // COD-2 channel interleaving
          // CSSelect[0] = XOR of sysAddr{intLvAddrBit, 14, 18, 23, 32} 
          dstFabricId += (getBit64 (intLvAddrBit, sysAddr) ^
                          getBit (14, sysAddrLo) ^
                          getBit (18, sysAddrLo) ^
                          getBit (23, sysAddrLo) ^
                          getBit (0, sysAddrHi));
        } else if (intLvNumChan == 13) {    // COD-4 channel interleaving
          // CSSelect[0] = XOR of sysAddr{intLvAddrBit, 14, 18, 23, 32} 
          // CSSelect[1] = XOR of sysAddr{12, 16, 21, 30} 
          dstFabricId += (getBit64 (intLvAddrBit, sysAddr) ^
                          getBit (14, sysAddrLo) ^
                          getBit (18, sysAddrLo) ^
                          getBit (23, sysAddrLo) ^
                          getBit (0, sysAddrHi));
          dstFabricId += ((getBit (12, sysAddrLo) ^
                           getBit (16, sysAddrLo) ^
                           getBit (21, sysAddrLo) ^
                           getBit (30, sysAddrLo)) * 2);
        } else if (intLvNumChan == 14) {    // COD-8 channel interleaving
          // CSSelect[0] = XOR of sysAddr{intLvAddrBit, 14, 18, 23, 32} 
          // CSSelect[1] = XOR of sysAddr{12, 16, 21, 30} 
          // CSSelect[2] = XOR of sysAddr{13, 17, 22, 31} 
          dstFabricId += (getBit64 (intLvAddrBit, sysAddr) ^
                          getBit (14, sysAddrLo) ^
                          getBit (18, sysAddrLo) ^
                          getBit (23, sysAddrLo) ^
                          getBit (0, sysAddrHi));
          dstFabricId += ((getBit (12, sysAddrLo) ^
                           getBit (16, sysAddrLo) ^
                           getBit (21, sysAddrLo) ^
                           getBit (30, sysAddrLo)) * 2);
          dstFabricId += ((getBit (13, sysAddrLo) ^
                           getBit (17, sysAddrLo) ^
                           getBit (22, sysAddrLo) ^
                           getBit (31, sysAddrLo)) * 4);
        }
      } else {
        dstFabricId += (UINT32) getBits64 (intLvAddrBit, firstDieIdBit - 1, sysAddr);
      }

      //firstDieIdBit += log2 (numChanInterleaved);
      switch (numChanInterleaved) {
      case 2:
        firstDieIdBit += 1;
        break;
      case 4:
        firstDieIdBit += 2;
        break;
      case 8:
        firstDieIdBit += 3;
        break;
      case 16:
        firstDieIdBit += 4;
        break;
      case 32:
        firstDieIdBit += 5;
        break;
      }

      firstSocketIdBit = firstDieIdBit;
      if (numDieInterleaved > 1) {
        // firstSocketIdBit += log2(numDieInterleaved);
        switch (numDieInterleaved) {
        case 2:
          firstSocketIdBit += 1;
          break;
        case 4:
          firstSocketIdBit += 2;
          break;
        case 8:
          firstSocketIdBit += 3;
          break;
        }
        csId = (UINT32) getBits64 (firstDieIdBit, firstSocketIdBit - 1, sysAddr);
        dstFabricId |= (csId << dieIdShift);
      }
      if (numSocketsInterleaved > 1) {
        csId = (UINT32) getBits64 (firstSocketIdBit, firstSocketIdBit + numSocketsInterleaved - 1, sysAddr);
        dstFabricId |= (csId << socketIdShift);
      }

      return (dstFabricId);
    }
  }
  //assert(0); // missed in address maps.
  return(0);    // nhu-todo, should return error
}

/*------------------------------------------------------------------
 Function: calcSysAddr

 Purpose: Denormalize an address from a memory controller into a
   system address.

 Parameters (all are input only)
   normAddr (ulong)
     The address to be converted
   mySocketNum (uint):
     This socket number within the system where this normalized
     address was found.
     Valid range (on ZP): 0-1
   myDieNum (uint):
     This die number within the socket where this normalized
     address was found.
     Valid range (on ZP): 0-3
   myChannelNum (uint):
     This channel number within the die where this normalized
     address was found.
     Valid range (on ZP): 0-1
 Returns:
   A system address (ulong)

 Side Effects:
   None:

 Limitations:
   - Does not support non-power-of-2 channel interleaving
   - The system address returned will not have any VMGuard key information
   - When the UMC address is being used for system functions
     e.g. PSP private area, CC6 save address); the algorithm will
    give you the system address - which is actually a E820 hole in
    the memory.

 *------------------------------------------------------------------*/
UINT64 
calcSysAddr (
  UINT64  normAddr,
  UINT32  mySocketNum,
  UINT32  myDieNum,
  UINT32  myChannelNum
  )
{
  UINT64  hiAddrOffset;
  UINT64  dramBaseAddr;
  UINT64  dramLimitAddr;
  UINT64  dramHoleBase;
  UINT64  preBaseSysAddr;
  UINT64  sysAddr;
  UINT64  preNormAddr;
  UINT64  deIntLvAddr;
  UINT64  tempAddrA;
  UINT64  tempAddrB;
  UINT64  tempAddrC;
  UINT64  tempAddrD;

  UINT32  systemFabricIdReg;
  UINT32  dramBaseReg;
  UINT32  dramLimitReg;
  UINT32  sysAddrLo;
  UINT32  sysAddrHi;

  UINT32  socketIdShift;
  UINT32  socketIdMask;
  UINT32  dieIdMask;
  UINT32  dieIdShift;
  UINT32  numDFInstances;
  UINT32  nodeId;
  UINT32  csInstanceId;
  UINT32  csFabricId;
  //UINT32  myDieType;
  UINT32  base;
  UINT32  intLvAddrSel;
  UINT32  intLvAddrBit;
  UINT32  intLvNumDies;
  UINT32  intLvNumChan;
  UINT32  numSocketsInterleaved;
  UINT32  numDieInterleaved=0;
  UINT32  numChanInterleaved=0;
  UINT32  numInterleaveBits=0;
  UINT32  firstSocketIdBit;
  UINT32  firstDieIdBit;
  UINT32  csId=0;
  UINT32  csMask;
  UINT32  holeEn;
  UINT32  hiAddrOffsetEn;
  UINT32  addrRngVal;
  UINT32  hashEnabled;
  UINT32  hashedBit=0;
  UINT32  dfType;
  UINT32  splitNormalized;

  ASSERT (mySocketNum <= 2);
  ASSERT (myDieNum <= 4);
  ASSERT (myChannelNum <= 8);

  nodeId = (mySocketNum * 4) + myDieNum;

  // Detect some information about the system
  //myDieType = getBits (MYDIETYPELO, MYDIETYPEHI, getDfRegSystemCfg (nodeId));
  dfType = determineDfType ();
  numDFInstances = getBits (BLKINSTCOUNTLO, BLKINSTCOUNTHI, getDfRegFabricBlkInstanceCnt (nodeId));
  if (dfType == 2) {
    systemFabricIdReg = getDfRegSystemFabricIdMask (nodeId);
    socketIdShift = getBits (SOCKETIDSHIFTLO_DF2, SOCKETIDSHIFTHI_DF2, systemFabricIdReg);
    socketIdMask = getBits (SOCKETIDMASKLO_DF2, SOCKETIDMASKHI_DF2, systemFabricIdReg);
    dieIdShift = getBits (DIEIDSHIFTLO_DF2, DIEIDSHIFTHI_DF2, systemFabricIdReg);
    dieIdMask = getBits (DIEIDMASKLO_DF2, DIEIDMASKHI_DF2, systemFabricIdReg);
  } else {
    systemFabricIdReg = getDfRegSystemFabricIdMask1 (nodeId);
    socketIdShift = getBits(SOCKETIDSHIFTLO_DF3, SOCKETIDSHIFTHI_DF3, systemFabricIdReg);
    socketIdMask = getBits (SOCKETIDMASKLO_DF3, SOCKETIDMASKHI_DF3, systemFabricIdReg);
    dieIdShift = getBits (DIEIDSHIFTLO_DF3, DIEIDSHIFTHI_DF3, systemFabricIdReg);
    dieIdMask = getBits (DIEIDMASKLO_DF3, DIEIDMASKHI_DF3, systemFabricIdReg);
  }

  // Find the matching CS
  // If one was to do this programmatically, it would still require us to have some SOC-specific
  // defines to determine how the CS->UMC is attached). In addition, one would have to be careful
  // of coherent slaves that are gated because they are unused (no memory, not valid on the package, etc).
  // However, on all products, the relationship is one-to-one (CS0 maps to UMC0) and furthermore, CS0 is
  // always starting at instance ID 0 in the fabric. We will use this trick for now.
  csInstanceId = myChannelNum;

  // Once you have the CS instance ID, now get the FabricID:
  csFabricId = getBits(BLOCKFABRICIDLO, BLOCKFABRICIDHI, getDfRegFabricBlkInstInfo3 (csInstanceId, nodeId));
  //IDS_HDT_CONSOLE (MAIN_FLOW, "csInstanceId = %d, csFabricId = %x\n", csInstanceId, csFabricId);

  // Read the CS offset registers and determine whether this
  // address was part of base/limit register 0, 1, or 2.
  // Since base 2 is only used in tri-channel mappings, which the
  // algorithm doesn't implement, this skips that.
  hiAddrOffsetEn = getBit (HIADDROFFSETEN, getDfRegDramOffset (csInstanceId, nodeId, 1));
  hiAddrOffset = getBits (HIADDROFFSETLO, HIADDROFFSETHI, getDfRegDramOffset (csInstanceId, nodeId, 1));
  hiAddrOffset = hiAddrOffset << 28;
  //IDS_HDT_CONSOLE (MAIN_FLOW, "hiAddrOffsetEn[1] = %d, hiAddrOffset[1] = 0x%016lX\n", hiAddrOffsetEn, hiAddrOffset);
  if (hiAddrOffsetEn && (normAddr >= hiAddrOffset)) {
    base = 1;
  } else {
    base = 0;
  }

  // Now set up variables from the CS base/limit registers
  dramBaseReg = getDfRegDramBase (csInstanceId, nodeId, base);
  dramLimitReg = getDfRegDramLimit (csInstanceId, nodeId, base);
  //IDS_HDT_CONSOLE (MAIN_FLOW, "dramBaseReg = 0x%08X, dramLimitReg = 0x%08X\n", dramBaseReg, dramLimitReg);

  addrRngVal = getBit (ADDRRNGVAL, dramBaseReg);
  //ASSERT (addrRngVal == 1);
  if (0 == addrRngVal) {
    sysAddr = 0xffffffffffffffff;   // Return an invalid system address to indicate something wrong
    return (sysAddr);
  }

  if (base == 0) {
    hiAddrOffset = 0;
  } else {
    hiAddrOffset = getBits (HIADDROFFSETLO, HIADDROFFSETHI, getDfRegDramOffset (csInstanceId, nodeId, base));
    hiAddrOffset = hiAddrOffset << 28;
  }
  //IDS_HDT_CONSOLE (MAIN_FLOW, "hiAddrOffset = 0x%016lX\n", hiAddrOffset);

  dramBaseAddr = getBits (DRAMBASEADDRLO, DRAMBASEADDRHI, dramBaseReg);
  dramBaseAddr = dramBaseAddr << 28;
  //IDS_HDT_CONSOLE (MAIN_FLOW, "dramBaseAddr = 0x%016lX\n", dramBaseAddr);

  dramLimitAddr = getBits (DRAMLIMITADDRLO, DRAMLIMITADDRHI, dramLimitReg);
  dramLimitAddr = dramLimitAddr << 28;
  dramLimitAddr |= ((UINT64) 0x0FFFFFFF);
  //IDS_HDT_CONSOLE (MAIN_FLOW, "dramLimitAddr = 0x%016lX\n", dramLimitAddr);

  holeEn = getBit (LGCYMMIOHOLEEN, dramBaseReg);
  dramHoleBase = getBits (DRAMHOLEBASELO, DRAMHOLEBASEHI, getDfRegDramHoleCtrl (csInstanceId, nodeId));
  dramHoleBase = dramHoleBase << 24;
  //IDS_HDT_CONSOLE (MAIN_FLOW, "holeEn = %d, dramHoleBase = 0x%016lX\n", holeEn, dramHoleBase);

  intLvAddrSel = extractIntLvAddrSel (dfType, dramBaseReg, dramLimitReg);
  intLvAddrBit = (getBit (1, intLvAddrSel) ? (getBit (0, intLvAddrSel) ? 11 : 10) : (getBit (0, intLvAddrSel) ? 9 : 8));

  intLvNumChan = extractIntLvNumChan (dfType, dramBaseReg, dramLimitReg);

  hashEnabled = FALSE;
  switch (intLvNumChan) {
  case 0:
    numChanInterleaved = 1;
    numInterleaveBits = 0;
    splitNormalized = FALSE;
    break;
  case 1:
    numChanInterleaved = 2;
    numInterleaveBits = 1;
    splitNormalized = FALSE;
    break;
  case 3:
    numChanInterleaved = 4;
    numInterleaveBits = 2;
    splitNormalized = FALSE;
    break;
  case 5:
    numChanInterleaved = 8;
    numInterleaveBits = 3;
    splitNormalized = FALSE;
    break;
  case 7:
    numChanInterleaved = 16;
    numInterleaveBits = 4;
    splitNormalized = FALSE;
    break;
  case 8:
    numChanInterleaved = 32;
    numInterleaveBits = 1;
    hashEnabled = FALSE;
    splitNormalized = FALSE;
    break;
  case 12:
    numChanInterleaved = 2;
    numInterleaveBits = 1;
    hashEnabled = TRUE;
    splitNormalized = FALSE;
    break;
  case 13:
    numChanInterleaved = 4;
    numInterleaveBits = 2;
    hashEnabled = TRUE;
    splitNormalized = TRUE;
    break;
  case 14:
    numChanInterleaved = 8;
    numInterleaveBits = 3;
    hashEnabled = TRUE;
    splitNormalized = FALSE;
    break;
  default:
    numChanInterleaved = 1;
    numInterleaveBits = 0;
    splitNormalized = FALSE;
    break;
  }

  // If we are using address hashing, the interleave address bit must be 8 or 9.
  ASSERT (!hashEnabled || (intLvAddrSel == 0) || (intLvAddrSel == 1));

  intLvNumDies = extractIntLvNumDies (dfType, dramBaseReg, dramLimitReg);
  switch (intLvNumDies) {
  case 0:
    numDieInterleaved = 1;
    break;
  case 1:
    numDieInterleaved = 2;
    numInterleaveBits += 1;
    break;
  case 2:
    numDieInterleaved = 4;
    numInterleaveBits += 2;
    break;
  case 3:
    numDieInterleaved = 8;
    numInterleaveBits += 3;
    break;
  }

  numSocketsInterleaved = extractIntLvNumSkts (dfType, dramBaseReg, dramLimitReg) + 1;
  numInterleaveBits += (numSocketsInterleaved - 1);
  ASSERT (numInterleaveBits <= 4);

  //IDS_HDT_CONSOLE (MAIN_FLOW, "intLvAddrBit = %d, numSocketsInterleaved = %d, numDieInterleaved = %d, numChanInterleaved = %d, numInterleaveBits = %d, hashEnabled = %d\n",
  //                 intLvAddrBit, numSocketsInterleaved, numDieInterleaved, numChanInterleaved, numInterleaveBits, hashEnabled);

  // Subtract the offset
  preNormAddr = normAddr - hiAddrOffset;
  //IDS_HDT_CONSOLE (MAIN_FLOW, "preNormAddr = 0x%016lX\n", preNormAddr);

  // Account for interleaving bits
  deIntLvAddr = preNormAddr;
  if (numInterleaveBits > 0) {
    // Calculate the CSID that is part of the de-normalized address.
    csId = 0;
    firstDieIdBit = 0;
    if (numChanInterleaved > 1) {
      //firstDieIdBit = log2(numChanInterleaved); // not supporting tri-channel here.
      switch (numChanInterleaved) {
      case 2:
        firstDieIdBit = 1;
        break;
      case 4:
        firstDieIdBit = 2;
        break;
      case 8:
        firstDieIdBit = 3;
        break;
      case 16:
        firstDieIdBit = 4;
        break;
      case 32:
        firstDieIdBit = 5;
        break;
      }
      csMask = (1 << firstDieIdBit) - 1;
      csId = csFabricId & csMask;
    }
    firstSocketIdBit = firstDieIdBit;
    if (numDieInterleaved > 1) {
      //firstSocketIdBit = firstDieIdBit + log2(numDieInterleaved);
      switch (numDieInterleaved) {
      case 2:
        firstSocketIdBit = firstDieIdBit + 1;
        break;
      case 4:
        firstSocketIdBit = firstDieIdBit + 2;
        break;
      case 8:
        firstSocketIdBit = firstDieIdBit + 3;
        break;
      }
      csId |= (((csFabricId & dieIdMask) >> dieIdShift) << firstDieIdBit);
    }
    if (numSocketsInterleaved > 1) {
      csId |= (((csFabricId & socketIdMask) >> socketIdShift) << firstSocketIdBit);
    }
    //IDS_HDT_CONSOLE (MAIN_FLOW, "numDieInterleaved = %d, numChanInterleaved = %d\n", numDieInterleaved, numChanInterleaved);
    //IDS_HDT_CONSOLE (MAIN_FLOW, "csId = 0x%x, firstSocketIdBit = %d, firstDieIdBit = %d\n", csId, firstSocketIdBit, firstDieIdBit);

    // the system address bit consists of:
    //      XXXXXXXXXIIIYYY
    //   or
    //      XXXXXXIIZZZIYYY
    //   where III is the ID for this CS, and XXXXXXZZZYYYYY are the address bits used
    //   in the normalized address.
    //   numInterleaveBits has been calculated to tell us how many "I" bits there are.
    //   intLvAddrBit tells us how many "Y" bits there are (were "I" starts)
    //   The "split" III is only used in the COD modes, where there is one bit I
    //   at intLvAddrBit, and the remaining CS bits are higher up starting at bit 12.
    tempAddrA = getBits64(0, (intLvAddrBit - 1), preNormAddr);
    tempAddrD = 0;
    if (splitNormalized == FALSE) {
      tempAddrB = getBits64 (intLvAddrBit, 63, preNormAddr);
      tempAddrB = tempAddrB << (intLvAddrBit + numInterleaveBits);
      tempAddrC = 0;
      tempAddrD = 0;
    } else {
      tempAddrB = getBits64 (intLvAddrBit, 10, preNormAddr);
      tempAddrB = tempAddrB << (intLvAddrBit + 1);
      tempAddrC = getBits64(11, 63, preNormAddr);
      tempAddrC = tempAddrC << (11 + numInterleaveBits);
    }
    //IDS_HDT_CONSOLE (MAIN_FLOW, "tempAddrA=0x%016lX, tempAddrB=0x%016lX, tempAddrC=0x%016lX, tempAddrD=0x%016lX\n",
    //                 tempAddrA, tempAddrB, tempAddrC, tempAddrD);
    deIntLvAddr = tempAddrA | tempAddrB | tempAddrC | tempAddrD;
  }
  //IDS_HDT_CONSOLE (MAIN_FLOW, "deIntLvAddr = 0x%016lX\n", deIntLvAddr);

  // Add in the base.
  preBaseSysAddr = deIntLvAddr + dramBaseAddr;
  //IDS_HDT_CONSOLE (MAIN_FLOW, "preBaseSysAddr = 0x%016lX\n", preBaseSysAddr);

  // Account for the DRAM hole
  if (holeEn && (preBaseSysAddr >= dramHoleBase)) {
    //IDS_HDT_CONSOLE (MAIN_FLOW, "dramHoleBase = 0x%016lX, adjust = 0x%016lX\n", dramHoleBase, ((((UINT64) 1) << 32) - dramHoleBase));
    sysAddr = preBaseSysAddr + ((((UINT64) 1) << 32) - dramHoleBase);
  } else {
    sysAddr = preBaseSysAddr;
  }
  //IDS_HDT_CONSOLE (MAIN_FLOW, "sysAddr = 0x%016lX\n", sysAddr);

  // Now fill in the interleave bit
  if ((hashEnabled == FALSE) && (numChanInterleaved > 1)) {
    tempAddrA = (csId << intLvAddrBit);
    sysAddr = sysAddr | tempAddrA;
  }

  if (hashEnabled) {
    // Adjust for the hashing (if enabled)
    sysAddrLo = (UINT32) sysAddr;
    sysAddrHi = (UINT32) (sysAddr>>32);
    if (intLvNumChan == 8) {    // 2 channel interleaving
      // CSSelect[0] = XOR of sysAddr{intLvAddrBit, 12, 18, 21, 30}
      hashedBit = (getBit (0, csId) ^
                   getBit (12, sysAddrLo) ^
                   getBit (18, sysAddrLo) ^
                   getBit (21, sysAddrLo) ^
                   getBit (30, sysAddrLo));
    } else if ((intLvNumChan == 12) || (intLvNumChan == 13) || (intLvNumChan == 14)) {    // COD-2, COD-4, COD-8
      // CSSelect[0] = XOR of sysAddr{intLvAddrBit, 14, 18, 23, 32} 
      hashedBit = (getBit (0, csId) ^
                   getBit (14, sysAddrLo) ^
                   getBit (18, sysAddrLo) ^
                   getBit (23, sysAddrLo) ^
                   getBit (0, sysAddrHi));
    }
    sysAddr ^= (((UINT64) hashedBit) << intLvAddrBit);
    //IDS_HDT_CONSOLE (MAIN_FLOW, "hashedBit = %d, sysAddr = 0x%016lX\n", hashedBit, sysAddr);
    //nhu-todo, above if () cover 13, 14 already ???
    if ((intLvNumChan == 13) || (intLvNumChan == 14)) {   // COD-4, COD-8
      // CSSelect[1] = XOR of sysAddr{12, 16, 21, 30} 
      hashedBit = (getBit (1, csId) ^
                   getBit (12, sysAddrLo) ^
                   getBit (16, sysAddrLo) ^
                   getBit (21, sysAddrLo) ^
                   getBit (30, sysAddrLo));
      sysAddr ^= (((UINT64) hashedBit) << 12);
      //IDS_HDT_CONSOLE (MAIN_FLOW, "hashedBit = %d, sysAddr = 0x%016lX\n", hashedBit, sysAddr);
    }

    if (intLvNumChan == 14) {   // COD-8
      // CSSelect[2] = XOR of sysAddr{13, 17, 22, 31} 
      hashedBit = (getBit (2, csId) ^
                   getBit (13, sysAddrLo) ^
                   getBit (17, sysAddrLo) ^
                   getBit (22, sysAddrLo) ^
                   getBit (31, sysAddrLo));
      sysAddr ^= (((UINT64) hashedBit) << 13);
      //IDS_HDT_CONSOLE (MAIN_FLOW, "hashedBit = %d, sysAddr = 0x%016lX\n", hashedBit, sysAddr);
    }
  }

  // Check that you didn't go over the pair limit
  ASSERT (sysAddr <= dramLimitAddr);
  return (sysAddr);
}

/*------------------------------------------------------------------
 Function: calcNormAddr

 Purpose: Normalize a system address into a memory controller
   (normalized) system address.

 Parameters (all are input only)
   sysAddr (ulong)
     The address to be converted.
     The user must remove all VMGuard key indices from the system address.
 Returns:
   A normalized address (ulong)

 Side Effects:
   None:

 Limitations:
   - Does not support non-power-of-2 channels (not used on ZP)

 *------------------------------------------------------------------*/
NORMALIZED_ADDRESS 
calcNormAddr (
  UINT64 sysAddr
  )
{
  UINT64  hiAddrOffset;
  UINT64  dramBaseAddr;
  UINT64  dramLimitAddr;
  UINT64  dramHoleBase;
  UINT64  postHoleSysAddr;
  UINT64  preIntlvSysAddr;
  UINT64  intLvAddr;
  UINT64  tempAddrA;
  UINT64  tempAddrB;
  UINT64  tempAddrC;

  UINT32  systemFabricIdReg;
  UINT32  dramBaseReg;
  UINT32  dramLimitReg;

  UINT32  socketIdShift;
  UINT32  socketIdMask;
  UINT32  dieIdMask;
  UINT32  dieIdShift;
  UINT32  nodeIdShift;
  UINT32  nodeId;
  UINT32  csInstanceId;
  UINT32  csFabricId;
  UINT32  base;
  UINT32  intLvAddrSel;
  UINT32  intLvAddrBit;
  UINT32  intLvNumDies;
  UINT32  intLvNumChan;
  UINT32  numInterleaveBits;
  UINT32  holeEn;
  UINT32  hiAddrOffsetEn;
  UINT32  addrRngVal;
  UINT32  dfType;
  NORMALIZED_ADDRESS    normalizedAddress;
  UINT32  splitNormalized;

  numInterleaveBits = 0;
  nodeId = 0;

  // Detect some information about the system
  dfType = determineDfType ();
  if (dfType == 2) {
    systemFabricIdReg = getDfRegSystemFabricIdMask (0);
    socketIdShift = getBits (SOCKETIDSHIFTLO_DF2, SOCKETIDSHIFTHI_DF2, systemFabricIdReg);
    socketIdMask = getBits (SOCKETIDMASKLO_DF2, SOCKETIDMASKHI_DF2, systemFabricIdReg);
    dieIdShift = getBits (DIEIDSHIFTLO_DF2, DIEIDSHIFTHI_DF2, systemFabricIdReg);
    dieIdMask = getBits (DIEIDMASKLO_DF2, DIEIDMASKHI_DF2, systemFabricIdReg);
    nodeIdShift = dieIdShift;
  } else {
    systemFabricIdReg = getDfRegSystemFabricIdMask1 (0);
    socketIdShift = getBits (SOCKETIDSHIFTLO_DF3, SOCKETIDSHIFTHI_DF3, systemFabricIdReg);
    socketIdMask = getBits (SOCKETIDMASKLO_DF3, SOCKETIDMASKHI_DF3, systemFabricIdReg);
    dieIdShift = getBits (DIEIDSHIFTLO_DF3, DIEIDSHIFTHI_DF3, systemFabricIdReg);
    dieIdMask = getBits (DIEIDMASKLO_DF3, DIEIDMASKHI_DF3, systemFabricIdReg);
    nodeIdShift = getBits (NODEIDSHIFTLO_DF3, NODEIDSHIFTHI_DF3, systemFabricIdReg);
  }

  // Find the channel...
  csFabricId = checkDramHit (sysAddr);
  //IDS_HDT_CONSOLE (MAIN_FLOW, "csFabricId = %08x\n", csFabricId);

  // convert the dstFabricId to a CS instance ID and nodeId.
  if (dfType == 2) {
    nodeId = (((csFabricId & socketIdMask) >> socketIdShift) * 4) +
             ((csFabricId & dieIdMask) >> dieIdShift);
  } else {
    nodeId = csFabricId >> nodeIdShift;
  }
  csInstanceId = csFabricId & ~(socketIdMask | dieIdMask);

  // Check if it hits on DRAM mapping register 0 or 1 in the CS.
  dramBaseReg = getDfRegDramBase (csInstanceId, nodeId, 1);    // Mapping register 1
  dramBaseAddr = getBits (DRAMBASEADDRLO, DRAMBASEADDRHI, dramBaseReg);
  dramBaseAddr = dramBaseAddr << 28;
  addrRngVal = getBit (ADDRRNGVAL, dramBaseReg);
  if (addrRngVal && (sysAddr >= dramBaseAddr)) {
    base = 1;
  } else {
    base = 0;
  }

  // Now set up variables from the CS base/limit registers
  dramBaseReg = getDfRegDramBase (csInstanceId, nodeId, base);
  dramLimitReg = getDfRegDramLimit (csInstanceId, nodeId, base);

  addrRngVal = getBit (ADDRRNGVAL, dramBaseReg);

  dramBaseAddr = getBits (DRAMBASEADDRLO, DRAMBASEADDRHI, dramBaseReg);
  dramBaseAddr = dramBaseAddr << 28;

  dramLimitAddr = getBits (DRAMLIMITADDRLO, DRAMLIMITADDRHI, dramLimitReg);
  dramLimitAddr = dramLimitAddr << 28;
  dramLimitAddr |= ((UINT64) 0x0FFFFFFF);

  holeEn = getBit (LGCYMMIOHOLEEN, dramBaseReg);
  dramHoleBase = getBits (DRAMHOLEBASELO, DRAMHOLEBASEHI, getDfRegDramHoleCtrl (csInstanceId, nodeId));
  dramHoleBase = dramHoleBase << 24;

  intLvAddrSel = extractIntLvAddrSel (dfType, dramBaseReg, dramLimitReg);
  intLvAddrBit = (getBit (1, intLvAddrSel) ? (getBit (0, intLvAddrSel) ? 11 : 10) : (getBit (0, intLvAddrSel) ? 9 : 8));

  intLvNumChan = extractIntLvNumChan (dfType, dramBaseReg, dramLimitReg);
  switch (intLvNumChan) {
  case 0:
    numInterleaveBits = 0;
    break;
  case 1:
  case 8:
  case 12:
    numInterleaveBits = 1;
    break;
  case 3:
  case 13:
    numInterleaveBits = 2;
    break;
  case 5:
  case 14:
    numInterleaveBits = 3;
    break;
  case 7:
    numInterleaveBits = 4;
    break;
  }

  // Check for DF3 only interleaves
  splitNormalized = FALSE;
  if ((intLvNumChan >= 12) && (intLvNumChan <= 14)) {
    // These are not supported on DF2.
    ASSERT (dfType != 2);
    // If we are using address hashing, the interleave address bit must be 8 or 9.
    ASSERT ((intLvAddrSel == 0) || (intLvAddrSel == 1));
    if (numInterleaveBits == 1) {
      splitNormalized = FALSE;
    } else {
      splitNormalized = TRUE;
    }
  }

  intLvNumDies = extractIntLvNumDies (dfType, dramBaseReg, dramLimitReg);
  switch (intLvNumDies) {
  case 0:
    break;
  case 1:
    numInterleaveBits += 1;
    break;
  case 2:
    numInterleaveBits += 2;
    break;
  }

  numInterleaveBits += extractIntLvNumSkts (dfType, dramBaseReg, dramLimitReg);

  // Account for the DRAM hole
  if (holeEn && (sysAddr >= dramHoleBase)) {
    postHoleSysAddr = sysAddr - ((((UINT64) 1) << 32) - dramHoleBase);
  } else {
    postHoleSysAddr = sysAddr;
  }

  // Subtract the base.
  preIntlvSysAddr = postHoleSysAddr - dramBaseAddr;

  // Account for intereleaving bits
  intLvAddr = preIntlvSysAddr;
  if (numInterleaveBits > 0) {
    //      XXXXXXXXXIIIYYY
    //   or
    //      XXXXXXIIZZZIYYY
    //   where III is the ID for this CS, and XXXXXXZZZYYYYY are the address bits used
    //   in the normalized address.
    //   numInterleaveBits has been calculated to tell us how many "I" bits there are.
    //   intLvAddrBit tells us how many "Y" bits there are (were "I" starts)
    //   The "split" III is only used in the COD modes, where there is one bit I
    //   at intLvAddrBit, and the remaining CS bits are higher up starting at bit 12.
    // Pull out the YYY
    tempAddrA = getBits64 (0, (intLvAddrBit -1), preIntlvSysAddr);
    if (splitNormalized == FALSE) {
      // ZZZZ isn't used in this mode.
      tempAddrB = 0;
      // Pull out the XXXX
      tempAddrC = getBits64 ((intLvAddrBit + numInterleaveBits), 63, preIntlvSysAddr);
      tempAddrC = tempAddrC << intLvAddrBit;
    } else {
      // Pull out the ZZZ
      tempAddrB = getBits64 ((intLvAddrBit + 1), 11, preIntlvSysAddr);
      tempAddrB = tempAddrB << intLvAddrBit;
      // Pull out the XXXX
      tempAddrC = getBits64 ((11 + numInterleaveBits), 63, preIntlvSysAddr);
      tempAddrC = tempAddrC << (intLvAddrBit + 1);
    }
    //if (debug) printf ("tempAddrA=0x%016lX, tempAddrB=0x%016lX, tempAddrC=0x%016lX\n",
    //                  tempAddrA, tempAddrB, tempAddrC);
    intLvAddr = tempAddrA | tempAddrB | tempAddrC;
  }

  if (base == 0) {
    hiAddrOffset = 0;
  } else {
    hiAddrOffsetEn = getBit (HIADDROFFSETEN, getDfRegDramOffset (csInstanceId, nodeId, 1));
    hiAddrOffset = getBits (HIADDROFFSETLO, HIADDROFFSETHI, getDfRegDramOffset (csInstanceId, nodeId, 1));
    hiAddrOffset = hiAddrOffset << 28;
  }

  // Add the offset
  normalizedAddress.normalizedAddr = intLvAddr + hiAddrOffset;
  normalizedAddress.normalizedSocketId = (UINT8) ((csFabricId & socketIdMask) >> socketIdShift);
  normalizedAddress.normalizedDieId = (UINT8) ((csFabricId & dieIdMask) >> dieIdShift);
  normalizedAddress.normalizedChannelId = (UINT8) (csFabricId & ~(socketIdMask | dieIdMask));
  normalizedAddress.reserved = 0;

  return (normalizedAddress);
}

UINT64
get_pcie_ccix_address (
  IN UINT64 address,
  IN BOOLEAN ccix_interleave_en,
  IN INT32 ccix_sdp_port_num_insert_sel,
  IN INT32 ccix_port_number,
  IN INT32 ccix_interleaved_addr_sel,
  IN INT32 ccix_interleaved_addr_remove0,
  IN INT32 ccix_interleaved_addr_remove1,
  IN INT32 ccix_if
  )
{
    UINT64 new_address = address;

    if (ccix_sdp_port_num_insert_sel == 0) {
        new_address = ((address & 0xFFFFFFFFFFFFFF00) << 1) | ((ccix_if & 0x1) << 8) | (address & 0xFF);
    } else if (ccix_sdp_port_num_insert_sel == 1) {
        new_address = ((address & 0xFFFFFFFFFFFFFE00) << 1) | ((ccix_if & 0x1) << 9) | (address & 0x1FF);
    } else if (ccix_sdp_port_num_insert_sel == 2) {
        new_address = ((address & 0xFFFFFFFFFFFFFC00) << 1) | ((ccix_if & 0x1) << 10) | (address & 0x3FF);
    } else if (ccix_sdp_port_num_insert_sel == 3) {
        new_address = ((address & 0xFFFFFFFFFFFFF800) << 1) | ((ccix_if & 0x1) << 11) | (address & 0x7FF);
    }
    //IDS_HDT_CONSOLE (MAIN_FLOW, "new_addres=%x", new_address);

    if (ccix_interleave_en) {
        switch (ccix_port_number) {
            case 0: new_address = new_address; //`uvm_error(get_type_name(), $psprintf("CCIX_PORT_NUMBER %d is invalid", m_greybox_monitor.get_ccix_port_number()))
                    break;
            case 1: switch (ccix_interleaved_addr_sel) {
                       case 0:  new_address = (ccix_interleaved_addr_remove0) ? ((new_address & 0xFFFFFFFFFFFFFC00) >> 1) | (new_address & 0x1FF) : new_address; 
                                break;
                       case 1:  new_address = (ccix_interleaved_addr_remove0) ? ((new_address & 0xFFFFFFFFFFFFF800) >> 1) | (new_address & 0x3FF) : new_address;  
                                break;
                       case 2:  new_address = (ccix_interleaved_addr_remove0) ? ((new_address & 0xFFFFFFFFFFFFF000) >> 1) | (new_address & 0x7FF) : new_address;
                                break;
                       case 3:  new_address = (ccix_interleaved_addr_remove0) ? ((new_address & 0xFFFFFFFFFFFFE000) >> 1) | (new_address & 0xFFF) : new_address;
                                break;
                       default: break;
                    }
                    break;
            case 2: //IDS_HDT_CONSOLE (MAIN_FLOW, "Three Ports, for stacked mode only");
                    break;
            case 3: switch (ccix_interleaved_addr_sel) {
                        case 0:  new_address = (ccix_interleaved_addr_remove0 && ccix_interleaved_addr_remove1)  ? ((new_address & 0xFFFFFFFFFFFFF800) >> 2) | (new_address & 0x1FF) :   // {new_address[63:11], new_address[8:0]} :
                                               (ccix_interleaved_addr_remove0 && !ccix_interleaved_addr_remove1) ? ((new_address & 0xFFFFFFFFFFFFFC00) >> 1) | (new_address & 0x1FF) :    // {new_address[63:10], new_address[8:0]} :
                                               (!ccix_interleaved_addr_remove0 && ccix_interleaved_addr_remove1) ? ((new_address & 0xFFFFFFFFFFFFF800) >> 1) | (new_address & 0x3FF) : new_address;   // {new_address[63:11], new_address[9:0]} : new_address;
                                break;
                        case 1:  new_address = (ccix_interleaved_addr_remove0 && ccix_interleaved_addr_remove1)  ? ((new_address & 0xFFFFFFFFFFFFF000) >> 2) | (new_address & 0x3FF) :  //{new_address[63:12], new_address[9:0]} :
                                               (ccix_interleaved_addr_remove0 && !ccix_interleaved_addr_remove1) ? ((new_address & 0xFFFFFFFFFFFFF800) >> 1) | (new_address & 0x3FF) :  //{new_address[63:11], new_address[9:0]} :
                                               (!ccix_interleaved_addr_remove0 && ccix_interleaved_addr_remove1) ? ((new_address & 0xFFFFFFFFFFFFF000) >> 1) | (new_address & 0x7FF) : new_address; //{new_address[63:12], new_address[10:0]} : new_address;
                                break;
                        case 2:  new_address = (ccix_interleaved_addr_remove0 && ccix_interleaved_addr_remove1)  ? ((new_address & 0xFFFFFFFFFFFFE000) >> 2) | (new_address & 0x7FF) :  //{new_address[63:13], new_address[10:0]} :
                                               (ccix_interleaved_addr_remove0 && !ccix_interleaved_addr_remove1) ? ((new_address & 0xFFFFFFFFFFFFF000) >> 1) | (new_address & 0x7FF) :  //{new_address[63:12], new_address[10:0]} :
                                               (!ccix_interleaved_addr_remove0 && ccix_interleaved_addr_remove1) ? ((new_address & 0xFFFFFFFFFFFFE000) >> 1) | (new_address & 0xFFF) : new_address; //{new_address[63:13], new_address[11:0]} : new_address;
                                break;
                        case 3:  new_address = (ccix_interleaved_addr_remove0 && ccix_interleaved_addr_remove1)  ? ((new_address & 0xFFFFFFFFFFFFC000) >> 2) | (new_address & 0xFFF) :  //{new_address[63:14], new_address[11:0]} :
                                               (ccix_interleaved_addr_remove0 && !ccix_interleaved_addr_remove1) ? ((new_address & 0xFFFFFFFFFFFFE000) >> 1) | (new_address & 0xFFF) :  //{new_address[63:13], new_address[11:0]} :
                                               (!ccix_interleaved_addr_remove0 && ccix_interleaved_addr_remove1) ? ((new_address & 0xFFFFFFFFFFFFC000) >> 1) | (new_address & 0x1FFF) : new_address; //{new_address[63:14], new_address[12:0]} : new_address;
                                break;
                        default: //IDS_HDT_CONSOLE (MAIN_FLOW, "SDP_PORT_NUM_INSERT_SEL %d is invalid", ccix_interleaved_addr_sel);
                             ;
                    }
                    break;
            default:  //IDS_HDT_CONSOLE (MAIN_FLOW, "CCIX_PORT_NUMBER %d is invalid", ccix_port_number);
                 ;
        }
    }
    //IDS_HDT_CONSOLE (MAIN_FLOW, "\nReturning new_addres=%x \n", new_address);

    return new_address;
}

