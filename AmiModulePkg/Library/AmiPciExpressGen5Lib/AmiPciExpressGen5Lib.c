//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985 - 2020, American Megatrends International LLC. *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file AmiPciExpressGen5Lib.c
    Library Class for AMI Pci Express GEN 5 Support Functions.


**/

//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <AmiLib.h>
#include <AcpiRes.h>
#include <Protocol/PciIo.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Library/AmiPciBusLib.h>

//-------------------------------------------------------------------------
// Constants, Macros and Type Definitions
//-------------------------------------------------------------------------


/**
    Function detects if Device PCIe v5.x and up compatible

    @param Device Pointer to device private data structure

    @retval TRUE if Compatible FALSE otherwise.

**/
BOOLEAN Pcie5CheckPcie5Compatible(PCI_DEV_INFO  *Device){
    
    if( Device->PciExpress!=NULL &&
        Device->PciExpress->Pcie2!=NULL &&
        Device->PciExpress->Pcie3!=NULL &&
        Device->PciExpress->Pcie4!=NULL &&
        Device->PciExpress->Pcie5!=NULL &&
        Device->DevSetup.Pcie1Disable == 0 &&
        Device->DevSetup.Pcie2Disable == 0
    )return TRUE;
    else return FALSE;
}



/**
     This function will displays the Content of the PCIE5_EQUALIZATION_STA_REG register.

    @param Device Pointer to device private data structure
    @param EquStatus Pointer to PCI_EXPRESS_REG_PHYSICAL_LAYER_32_0_STATUS structure

    @retval EFI_STATUS Return Status
    @retval EFI_SUCCESS Set successfully.
    @retval EFI_INVALID_PARAMETER the Input parameter is invalid. 

**/
EFI_STATUS Pcie5GetEqualizationStatus(PCI_DEV_INFO *Device, PCI_EXPRESS_REG_PHYSICAL_LAYER_32_0_STATUS *EquStatus){
    EFI_STATUS          Status=EFI_SUCCESS;
	PCI_CFG_ADDR		addr;
//-----------------------------

    //If device don't have GEN 5 Cap Hdr, or link is operating on less than 32.0 GT/s speed - just exit...
    if(!Pcie5CheckPcie5Compatible(Device)) return EFI_SUCCESS;

    //Get PCIE_32_0_STA_OFFSET register to check the Equalization status
    addr.ADDR=Device->Address.ADDR;
    addr.Addr.ExtendedRegister=Device->PciExpress->Pcie5->PhyPcieCapOffs+PCI_EXPRESS_REG_PHYSICAL_LAYER_32_0_STATUS_OFFSET;
    Status=PciCfg32(Device->RbIo, addr, FALSE,&(EquStatus->Uint32));
    ASSERT_EFI_ERROR(Status);

    //Display Content of the PCIE5_EQUALIZATION_STA_REG register.
    DEBUG((DEBUG_VERBOSE," Pcie5 : EQUALIZATION_STA-> [EqCompl=%X|EqP1=%X|EqP2=%X|EqP3=%X|EqReq=%X\n",
        EquStatus->Bits.EqualizationComplete,
        EquStatus->Bits.EqualizationPhase1Success,
        EquStatus->Bits.EqualizationPhase2Success,
        EquStatus->Bits.EqualizationPhase3Success,
        EquStatus->Bits.LinkEqualizationRequest
        ));

    return Status;
}


/**
    This function will Update Speed encoding and 
    display content of LNK_CAP2_REG.
    
    @param Device Pointer to PCI Device Private Data structure. 

    @retval VOID  

**/
VOID Pcie5InitDisplayPcie5Data(PCI_DEV_INFO *Device){
    //Do some additional checks if device has GEN 5 Secondary PCIe Cap Header.
    //At that point if we have discovered Physical Layer 32.0 PCIe Cap HDR Device->PciExpress->Pcie5 must be initialized.
    if(!Pcie5CheckPcie5Compatible(Device)){
        //Update Speed encoding it is defined differently for devices Supporting V5.0 spec.
        Device->PciExpress->Pcie5->MaxLanesCount = (UINT8)Device->PciExpress->LinkCap.MaxLnkWidth;

        //Display content of LNK_CAP2_REG
        DEBUG((DEBUG_VERBOSE,"PCIe5 -> Device is PCIe v5.0 Compliant!!! LNK_CAP2 present!!! \n LNK_CAP2-> [R2=%X|CrossL=%X|SuppLnkSpeedVect=%X|R1=%X]|[RetimerPresDet=%x][TwotimerPresDet=%x]; RcvdModifiedTSData1->[%X] RcvdModifiedTSData2->[%X] TransModifiedTSData1->[%X]; TransModifiedTSData2->[%X]; ControlReg->[%X]; MaxLanes=%X\n",
            Device->PciExpress->Pcie2->LinkCap2.Reserved2,
            Device->PciExpress->Pcie2->LinkCap2.CrossLnk,
            Device->PciExpress->Pcie2->LinkCap2.SuppLnkSpeeds,
            Device->PciExpress->Pcie2->LinkCap2.Reserved1,
            Device->PciExpress->Pcie2->LinkCap2.RetimerPresDet,
            Device->PciExpress->Pcie2->LinkCap2.TwotimerPresDet,
            Device->PciExpress->Pcie5->RcvdModifiedTSData1,
            Device->PciExpress->Pcie5->RcvdModifiedTSData2,
            Device->PciExpress->Pcie5->TransModifiedTSData1,
            Device->PciExpress->Pcie5->TransModifiedTSData2,
            Device->PciExpress->Pcie5->ControlReg,
            Device->PciExpress->Pcie5->MaxLanesCount));
    }
}

/**
    This function will Allocate the memory for Pcie5
    and Getting Content of LaneErrSts and MaxLanesCount
    
    @param Device Pointer to PCI Device Private Data structure.
    @param Pcie3CapOffset offset for Secondary PCIe Ext Capability.

    @retval   EFI_STATUS
        EFI_SUCCESS             When everything is going on fine!
        EFI_DEVICE_ERROR        When driver fails access PCI Bus.
        EFI_INVALID_PARAMETER   When some of the parameters are invalid. 

**/
EFI_STATUS Pcie5AllocateInitPcie5Data(PCI_DEV_INFO *Device, UINT32 Pcie5CapOffset){
    PCI_CFG_ADDR	addr;
    EFI_STATUS      Status;
//---------------------------
    DEBUG((DEBUG_VERBOSE,"PciE5: Found Physical Layer 32.0 PCIe Ext Cap Header @ offset 0x%X\n", Pcie5CapOffset));

    //Allocate Memory
    Device->PciExpress->Pcie5=MallocZ(sizeof(PCIE5_DATA));
    if(Device->PciExpress->Pcie5==NULL) {
        ASSERT_EFI_ERROR(EFI_OUT_OF_RESOURCES);
        return EFI_OUT_OF_RESOURCES;
    }

    Device->PciExpress->Pcie5->PhyPcieCapOffs = (UINT16)Pcie5CapOffset;

    //Get Content of RcvdModifiedTSData1,RcvdModifiedTSData2,TransModifiedTSData1,TransModifiedTSData2 and MaxLanesCount
    addr.ADDR=Device->Address.ADDR;
    addr.Addr.ExtendedRegister=Pcie5CapOffset+PCI_EXPRESS_REG_PHYSICAL_LAYER_32_0_RCVD_MODIFIED_TS_DATA1_OFFSET;

    Status=PciCfg32(Device->RbIo, addr, FALSE,&Device->PciExpress->Pcie5->RcvdModifiedTSData1);
    
    addr.ADDR=Device->Address.ADDR;
    addr.Addr.ExtendedRegister=Pcie5CapOffset+PCI_EXPRESS_REG_PHYSICAL_LAYER_32_0_RCVD_MODIFIED_TS_DATA2_OFFSET;

    Status=PciCfg32(Device->RbIo, addr, FALSE,&Device->PciExpress->Pcie5->RcvdModifiedTSData2);
        
    addr.ADDR=Device->Address.ADDR;
    addr.Addr.ExtendedRegister=Pcie5CapOffset+PCI_EXPRESS_REG_PHYSICAL_LAYER_32_0_TRANS_MODIFIED_TS_DATA1_OFFSET;

    Status=PciCfg32(Device->RbIo, addr, FALSE,&Device->PciExpress->Pcie5->TransModifiedTSData1);
    
    addr.ADDR=Device->Address.ADDR;
    addr.Addr.ExtendedRegister=Pcie5CapOffset+PCI_EXPRESS_REG_PHYSICAL_LAYER_32_0_TRANS_MODIFIED_TS_DATA2_OFFSET;

    Status=PciCfg32(Device->RbIo, addr, FALSE,&Device->PciExpress->Pcie5->TransModifiedTSData2);
    
    addr.ADDR=Device->Address.ADDR;
    addr.Addr.ExtendedRegister=Pcie5CapOffset+PCI_EXPRESS_REG_PHYSICAL_LAYER_32_0_CONTROL_OFFSET;

    Status=PciCfg32(Device->RbIo, addr, FALSE,&Device->PciExpress->Pcie5->ControlReg);

    Pcie5InitDisplayPcie5Data(Device);

    return Status;

}
