//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file AmiPirqRouterLib.c
    South Bridge Pirq Router Library implementation

*/

#include <Library/AmiPirqRouterLib.h>
#include <AmiChipsetIoLib.h>
#include <Sb.h>

#define MAX_PIRQS        8

UINT8   bMaxPIRQ        = MAX_PIRQS;     // For CSM
UINT8   bRouterBus      = FCH_LPC_BUS    ;// PORTING REQUIRED (Use appropriate Equate)
UINT8   bRouterDevice   = FCH_LPC_DEV    ;// PORTING REQUIRED (Use appropriate Equate)
UINT8   bRouterFunction = FCH_LPC_FUNC    ;// PORTING REQUIRED (Use appropriate Equate)
UINT8   RRegs[MAX_PIRQS]= {0, 1, 2, 3, 4, 5, 6, 7};   // Porting required

// Local variable
static EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL      *gPciRootBridgeIo;

typedef struct{
	UINT8 IrqIndex;
	UINT8 IrqDeviceIndex;
} FCH_IRQ_STRUCT;
FCH_IRQ_STRUCT gSbIrqStruct[] = {
	{0x00,0x13}, // SD IntA#-> INTA# (Refer to reference BIOS -> ASL name : HDAD)
	{0x00,0x17}, // SD IntA#-> INTA# (Refer to reference BIOS -> ASL name : SDCL)

    {0x02,0x30}, // 30h: Dev18 (USB) IntA#-> INTC#
    {0x02,0x34}, // 34h: Dev22 (USB) IntA#-> INTC#
    {0x03,0x41}, // 41h: SATA pciPCI interrupt-> INTD#
};

//----------------------------------------------------------------------------
//  PCI IRQ Routing (Pci_Intr_Index/Pci_Intr_Data)
#define READ_IO8_PIRQ(mIdx) \
                ReadIo8IdxData(PIRQ_IO_INDEX, mIdx)
#define WRITE_IO8_PIRQ(mIdx, mVal) \
                WriteIo8IdxData(PIRQ_IO_INDEX, mIdx, mVal)

/**
    Program the Chipset the IRQ

    @param IrqIndex : IRQ Index
    @param PirqData : Pirq Data

    @retval VOID

**/
VOID
RthChipsetRoutePciIrqSB800Hook(
    IN UINT8                            IrqIndex,
    IN UINT8                            PirqData
    )
{
    UINT8       PirqValue = PirqData & 0x0F;
    UINT32      StartIdx;

    if (IrqIndex < 4) {
        for (StartIdx = 0; StartIdx < \
            (sizeof(gSbIrqStruct)/sizeof(FCH_IRQ_STRUCT)); StartIdx++ )
        {
            if (IrqIndex == gSbIrqStruct[StartIdx].IrqIndex) {
                // For PCI
                WRITE_IO8_PIRQ(gSbIrqStruct[StartIdx].\
                                IrqDeviceIndex, PirqValue);
                // For APIC
                WRITE_IO8_PIRQ((gSbIrqStruct[StartIdx].\
                                IrqDeviceIndex | 0x80), (IrqIndex+16));
            }
        }
    }
}

/**
    This function is clears the routing registers to default values

    @param PciRBIo Root bridge IO protocol pointer

    @retval EFI_STATUS Returned from PCI read call

**/
EFI_STATUS SbGenInitializeRouterRegisters (
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *PciRBIo
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
    UINT8       Idx;
#if defined (HPET_PROTOCOL_SUPPORT) && (HPET_PROTOCOL_SUPPORT == 0)
    for (Idx = 0; Idx < MAX_PIRQS; Idx++)
        WRITE_IO8_PIRQ((RRegs[Idx] | 0x80), Idx+0x10);  
#else
    for (Idx = 0; Idx < MAX_PIRQS; Idx++)
        WRITE_IO8_PIRQ((RRegs[Idx] | 0x80), 0x1F); //Disable the IO APIC,
                                                   //And program it at _PIC method.
#endif  


    gPciRootBridgeIo = PciRBIo;         // Save RB IO value for later use

    return Status;
}

/**
    This function returns the 0 based PIRQ index (PIRQ0, 1 etc)
    based on the PIRQ register number specified in the routing table

    @param PIRQRegister - Register number of the PIR

    @retval PIRQIndex 0 - (MAX_PIRQ -1)
            0xFF if the register is invalid

    @note  Here is the control flow of this function:
              1. If Invalid PirqNumber, return EFI_INVALID_PARAMETER.
              2. Read into *PriqData from PIRQ register for Pirq requested.
              3. Return EFI_SUCCESS.
**/
UINT8 SBGen_GetPIRQIndex (
    UINT8 PIRQRegister
)
{
    UINT8       rrIndx = 0;

    //--- while ((rrIndx < MAX_PIRQS) && (RRegs[rrIndx] != PIRQRegister)) rrIndx++;
    // The router is Index/Data register.(0~3 9~C)
    // Because Microsoft IRQ Routing Table test.
    // We can't let the field "Chipset Reg" == 0.(..\Build\oempir.inc)
    // So I set the field == (1~4 A~D). Actually it is (0~3 9~C).
    while ((rrIndx < MAX_PIRQS) && (RRegs[rrIndx] != (PIRQRegister-1))) rrIndx++;

    if (rrIndx == MAX_PIRQS) return 0xFF;

    return rrIndx;
}

/**
    This function reads the IRQ associated with the PIRQ from
    the chipset register

    @param This Pointer to Legacy interrupt protocol
    @param PirqNumber PIRQ number to read
    @param PirqData IRQ programmed for this PIRQ (BIT7 will be
           set if the PIRQ is not programmed)

    @retval EFI_STATUS
            EFI_SUCCESS On successfully IRQ value return
            EFI_INVALID_PARAMETER   If PirqNumber is greater than max PIRQs

    @note  Here is the control flow of this function:
              1. If Invalid PirqNumber, return EFI_INVALID_PARAMETER.
              2. Read into *PriqData from PIRQ register for PIRQ requested.
              3. Return EFI_SUCCESS.
**/
EFI_STATUS EFIAPI SbGenReadPirq (
    IN EFI_LEGACY_INTERRUPT_PROTOCOL    *This,
    IN UINT8                            PirqNumber,
    OUT UINT8                           *PirqData
)
{
    if (PirqNumber >= MAX_PIRQS) return EFI_INVALID_PARAMETER;

    *PirqData = READ_IO8_PIRQ(RRegs[PirqNumber]);
    if (*PirqData == 0x1F) *PirqData = 0x00;

    return EFI_SUCCESS;
}

/**
    This function writes an IRQ value allocated for the PIRQ by
    programming the chipset register

    @param This - Pointer to Legacy interrupt protocol
    @param PirqNumber - PIRQ number to read
    @param PirqData - IRQ to be programmed

    @retval EFI_STATUS
            EFI_SUCCESS On successfully IRQ value return
            EFI_INVALID_PARAMETER If PirqNumber is greater than
                                  max PIRQs or PirqData is greater
                                  than 15 (MAX IRQ)

    @note  Here is the control flow of this function:
              1. If Invalid PirqNumber, return EFI_INVALID_PARAMETER.
              2. Write PirqData to PIRQ register for PIRQ requested.
              3. Return EFI_SUCCESS.
**/
EFI_STATUS EFIAPI SbGenWritePirq (
    IN EFI_LEGACY_INTERRUPT_PROTOCOL    *This,
    IN UINT8                            PirqNumber,
    IN UINT8                            PirqData
)
{
    UINT8       PirqValue = PirqData & 0x0F;

    if (PirqNumber >= MAX_PIRQS) return EFI_INVALID_PARAMETER;
    if (PirqData > 15) return EFI_INVALID_PARAMETER;

    RthChipsetRoutePciIrqSB800Hook(RRegs[PirqNumber], PirqValue);

    WRITE_IO8_PIRQ(RRegs[PirqNumber], PirqValue);

    //Remove the PCIE IO APIC program, move it to _PIC method.
    //WRITE_IO8_PIRQ((RRegs[PirqNumber] | 0x80), (RRegs[PirqNumber] + 0x10));
#if defined (HPET_PROTOCOL_SUPPORT) && (HPET_PROTOCOL_SUPPORT == 0)
    WRITE_IO8_PIRQ((RRegs[PirqNumber] | 0x80), (RRegs[PirqNumber] + 0x10));   
#endif    

    
    return EFI_SUCCESS;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
