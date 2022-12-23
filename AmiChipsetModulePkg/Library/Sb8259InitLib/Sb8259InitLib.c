//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
/** @file Sb8259InitLib.c
    This file contains code for South Bridge 8259 init

**/
//**********************************************************************

// Module specific Includes
#include <Uefi.h>
#include <Token.h>
#include <Sb.h>
#include <IndustryStandard/Pci.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#include <Protocol/AmiHpetTimer.h>

// Produced Protocols
#include <Protocol/PciIo.h>
#include <Protocol/Legacy8259.h>

//----------------------------------------------------------------------------
//          Variable Declaration
//----------------------------------------------------------------------------
//8259 PIC defines
#define ICW1            0x11    //Slave exists and ICW4 required.
#define ICW3_M          1<<2    //IRQ 2 connects to slave
#define ICW3_S          2       //IRQ 2 connects to master
#define ICW4            1       //Bit 4 Normal Nested Mode
                                //Bit 3 Non-buffered Mode
                                //Bit 2 Unused with non-buffered mode
                                //Bit 1 Set manual EOI instead of automatic
                                //Bit 0 8086/8088 mode

#define OCW1_M          0xff    //Master Mask
#define OCW1_S          0xff    //Slave Mask

#define EOI_COMMAND     0x20    //EOI Command

//#define INTERRUPTS_TRIGGER_REG    0x4d0   //Trigger for Interrupts (Edge or Level).
//#define INTERRUPTS_EDGE_TRIGGER   0       //Set all interrupts at edge level.

UINT8   gMasterBase, gSlaveBase;
UINT8   gMode = 1;                        //Initially in protected mode. (0 = Real, 1 = 32 bit protected)
UINT16  gIrqMask[2] = {0xffff,0xffff};   //Initially all Real IRQs masked, protected masked
UINT16  gIrqTrigger[2] = {0,0};          //Initially all Real IRQs Edge, protected Edge.

BOOLEAN	gIsHpetApicEn = FALSE;

// Function Prototypes

// Function Definitions
EFI_STATUS
Initialize8259(
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
);

//----------------------------------------------------------------------------
//   USUALLY NO PORTING REQUIRED FOR THE FOLLOWING ROUTINES
//----------------------------------------------------------------------------

#define SB_8259_PROTOCOL_LIB_SUPPORT 	1 // Sync this token if we roll back SbDxe
#if defined SB_8259_PROTOCOL_SUPPORT && SB_8259_PROTOCOL_SUPPORT == 1 && (SB_8259_PROTOCOL_LIB_SUPPORT == 1)
/**
    Program the IRQ Mask and Trigger.

    @param VOID

    @retval VOID

    @note  Here is the control flow of this function:
     1. Program Master IRQ Mask.
     2. Program Slave IRQ Mask.
     3. Program Trigger Level.

**/
VOID ProgramIrqMaskTrigger (
    VOID
)
{
    IoWrite8(0x21, (UINT8)gIrqMask[gMode]);
    IoWrite8(0xa1, (UINT8)(gIrqMask[gMode] >> 8));
    //
    // 4d0 can not be accessed as by IoWrite16, we have to split
    //
    IoWrite8(0x4d0, (UINT8)gIrqTrigger[gMode]);
    IoWrite8(0x4d1, (UINT8)(gIrqTrigger[gMode] >> 8));
}

/**
    Initializes the interrupt controller and program the IRQ
    Master and Slave Vector Base.

    @param This - Pointer to this object
    @param MasterBase - IRQ base for the master 8259 controller
    @param SlaveBase - IRQ base for the slave 8259 controller

    @retval EFI_SUCCESS Interrupt on the interrupt controllers was enabled.

    @note  Here is the control flow of this function:
           1. If Master base is changed, initialize master 8259 setting
              the interrupt offset.
           2. If Slave base is changed, initialize slave 8259 setting
              the interrupt offset.
           3. Return EFI_SUCCESS.
**/
EFI_STATUS SetVectorBase (
    IN EFI_LEGACY_8259_PROTOCOL   *This,
    IN UINT8                      MasterBase,
    IN UINT8                      SlaveBase
)
{
    //
    // 8259 Master
    //
    if (MasterBase != gMasterBase)
    {
        //
        // Start 8259 Master Initialization.
        //
        IoWrite8(LEGACY_8259_CONTROL_REGISTER_MASTER, ICW1);
        //
        // Set Interrupt Offset
        //
        IoWrite8(LEGACY_8259_MASK_REGISTER_MASTER, MasterBase);
        //
        // Set Slave IRQ.
        //
        IoWrite8(LEGACY_8259_MASK_REGISTER_MASTER, ICW3_M);
        //
        // Set 8259 mode. See ICW4 comments with #define.
        //
        IoWrite8(LEGACY_8259_MASK_REGISTER_MASTER, ICW4);
        gMasterBase = MasterBase;
    }
    //
    // 8259 Slave
    //
    if (SlaveBase != gSlaveBase)
    {
        //
        // Start 8259 Slave  Initialization.
        //
        IoWrite8(LEGACY_8259_CONTROL_REGISTER_SLAVE, ICW1);
        //
        // Set Interrupt Offset
        //
        IoWrite8(LEGACY_8259_MASK_REGISTER_SLAVE, SlaveBase);
        //
        // Set Slave IRQ.
        //
        IoWrite8(LEGACY_8259_MASK_REGISTER_SLAVE, ICW3_S);
        //
        // Set 8259 mode. See ICW4 comments with #define.
        //
        IoWrite8(LEGACY_8259_MASK_REGISTER_SLAVE, ICW4);
        gSlaveBase = SlaveBase;
    }

    return EFI_SUCCESS;
}

/**
    Get the Master/Slave IRQ Mask, IRQ Level for Legacy real
    mode and protected mode.

    @param This - Pointer to this object
    @param LegacyMask - Legacy mode interrupt mask
    @param LegacyEdgeLevel - Legacy mode edge/level trigger value
    @param ProtectedMask - Protected mode interrupt mask
    @param ProtectedEdgeLevel - Protected mode edge/level trigger value

    @retval EFI_SUCCESS Returned iRQ mask/level.

    @note  Here is the control flow of this function:
           1. If *LegacyMask not NULL, get legacy Mask.
           2. If *LegacyEdgeLevel not NULL, get legacy Trigger Level.
           3. If *ProtectedMask not NULL, get protected Mask.
           4. If *ProtectedEdgeLevel not NULL, get protected trigger level.
           5. Return EFI_SUCCESS.

**/
EFI_STATUS GetMask (
    IN EFI_LEGACY_8259_PROTOCOL   *This,
    OUT UINT16                    *LegacyMask   OPTIONAL,
    OUT UINT16                    *LegacyEdgeLevel OPTIONAL,
    OUT UINT16                    *ProtectedMask  OPTIONAL,
    OUT UINT16                    *ProtectedEdgeLevel OPTIONAL
)
{
    if (LegacyMask)   *LegacyMask   = gIrqMask[0];
    if (LegacyEdgeLevel) *LegacyEdgeLevel = gIrqTrigger[0];
    if (ProtectedMask)  *ProtectedMask  = gIrqMask[1];
    if (ProtectedEdgeLevel) *ProtectedEdgeLevel = gIrqTrigger[1];

    return EFI_SUCCESS;
}

/**
    Set the Master/Slave IRQ Mask, IRQ Level for Legacy real mode
    and protected mode.

    @param This - Pointer to this object
    @param LegacyMask - Legacy mode interrupt mask
    @param LegacyEdgeLevel - Legacy mode edge/level trigger value
    @param ProtectedMask - Protected mode interrupt mask
    @param ProtectedEdgeLevel - Protected mode edge/level trigger value

    @retval EFI_SUCCESS Set IRQ mask/level.

    @note  Here is the control flow of this function:
           1. If *LegacyMask not NULL, set legacy mask variable.
           2. If *LegacyEdgeLevel not NULL, set legacy Trigger Level variable.
           3. If *ProtectedMask not NULL, set protected mask variable.
           4. If *ProtectedEdgeLevel not NULL, set protected trigger level variable.
           5. Call function to program 8259 with mask/trigger of current mode.
           6. Return EFI_SUCCESS.

**/
EFI_STATUS SetMask (
    IN EFI_LEGACY_8259_PROTOCOL   *This,
    IN UINT16                     *LegacyMask   OPTIONAL,
    IN UINT16                     *LegacyEdgeLevel OPTIONAL,
    IN UINT16                     *ProtectedMask  OPTIONAL,
    IN UINT16                     *ProtectedEdgeLevel OPTIONAL
)
{
    if (LegacyMask)   gIrqMask[0]  = *LegacyMask;
    if (LegacyEdgeLevel) gIrqTrigger[0] = *LegacyEdgeLevel;
    if (ProtectedMask)  gIrqMask[1]  = *ProtectedMask;
    if (ProtectedEdgeLevel) gIrqTrigger[1] = *ProtectedEdgeLevel;

    ProgramIrqMaskTrigger();

    return EFI_SUCCESS;
}

/**
    Sets the interrupt mode operation to legacy or protected.
    New mask and edge/level status can be provided as input

    @param This - Pointer to this object
    @param Mode - Interrupt mode setting
    @param Mask - New interrupt mask for this mode
    @param EdgeLevel - New edge/level trigger value for this mode

    @retval EFI_SUCCESS Set mode was successful

    @note  Here is the control flow of this function:
           1. If invalid mode, return EFI_INVALID_PARAMETER.
           2. If *Mask not NULL, set mode mask variable.
           3. If *EdgeLevel not NULL, set mode trigger level variable.
           4. Call function to program 8259 with mask/trigger of current mode.
           5. Return EFI_SUCCESS.

**/
EFI_STATUS SetMode (
    IN EFI_LEGACY_8259_PROTOCOL   *This,
    IN EFI_8259_MODE              Mode,
    IN UINT16                     *Mask   OPTIONAL,
    IN UINT16                     *EdgeLevel OPTIONAL
)
{
    if (Mode >= Efi8259MaxMode) return EFI_INVALID_PARAMETER;

    gMode = Mode;
    if (Mask) gIrqMask[Mode] = *Mask;
    if (EdgeLevel) gIrqTrigger[Mode] = *EdgeLevel;

    ProgramIrqMaskTrigger();

    return EFI_SUCCESS;
}

/**
    Returns the vector number for the requested IRQ

    @param This - Legacy8259 protocol object
    @param Irq - IRQ number for which vector is needed
    @param Vector - Vector value is returned in this pointer

    @retval EFI_SUCCESS Get IRQ Vector for IRQ.

    @note  Here is the control flow of this function:
           1. If invalid IRQ, return EFI_INVALID_PARAMETER.
           2. If Set *Vector to IRQ base + interrupt offset.
           3. Return EFI_SUCCESS.

**/
EFI_STATUS GetVector (
    IN EFI_LEGACY_8259_PROTOCOL   *This,
    IN EFI_8259_IRQ               Irq,
    OUT UINT8                     *Vector
)
{
    if ((UINT8)Irq >= (UINT8)Efi8259IrqMax) return EFI_INVALID_PARAMETER;
    *Vector = (Irq <= Efi8259Irq7) ? gMasterBase + Irq : gSlaveBase + Irq - 8;

    return EFI_SUCCESS;
}

/**
    Enable the Interrupt controllers to respond in a specific IRQ.

    @param This - Legacy8259 protocol object
    @param Irq - IRQ that has to be enabled
    @param LevelTriggered - Trigger mechanism (level or edge) for this IRQ

    @retval EFI_SUCCESS Interrupt on the interrupt controllers was enabled.
    @retval EFI_INVALID_PARAMETER Interrupt not existent. The 8259 
                                  master/slave supports IRQ 0-15.

    @note  Here is the control flow of this function:
           1. Check if IRQ is valid. If not, return EFI_INVALID_PARAMETER.
           2. Clear interrupt mask bit in variable of current mode.
           3. Set/Clear bit of trigger level variable of current mode.
           4. Program mask/trigger.
           5. Return EFI_SUCCESS.

**/
EFI_STATUS EnableIrq (
    IN EFI_LEGACY_8259_PROTOCOL   *This,
    IN EFI_8259_IRQ               Irq,
    IN BOOLEAN                    LevelTriggered
)
{
    if ((UINT8)Irq > (UINT8)15) return EFI_INVALID_PARAMETER;
    //
    // Clear mask for the IRQ.
    //
    gIrqMask[gMode] &= ~(1 << Irq);
    //
    // Mask IRQ to change.
    //
    gIrqTrigger[gMode] &= ~(1 << Irq);
    //
    // Change IRQ bit, 0 = edge, 1 = level.
    //
    if (LevelTriggered) gIrqTrigger[gMode] |= (1 << Irq);

    ProgramIrqMaskTrigger();
    return EFI_SUCCESS;
}


/**
    Disable the Interrupt controllers to stop responding to
    a specific IRQ.

    @param This - Legacy8259 protocol object
    @param Irq - IRQ that has to be disabled

    @retval EFI_SUCCESS Interrupt on the interrupt controllers was enabled.
    @retval EFI_INVALID_PARAMETER Interrupt not existent. The 8259 
                                  master/slave supports IRQ 0-15.

    @note  Here is the control flow of this function:
           1. Check if IRQ is valid. If not, return EFI_INVALID_PARAMETER.
           2. Set interrupt mask bit in variable of current mode.
           3. Program mask/trigger.
           4. Return EFI_SUCCESS.

**/
EFI_STATUS DisableIrq (
    IN EFI_LEGACY_8259_PROTOCOL   *This,
    IN EFI_8259_IRQ               Irq
)
{
    if ((UINT8)Irq > (UINT8)15) return EFI_INVALID_PARAMETER;
    //
    // Set mask for the Irq.
    //
    gIrqMask[gMode] |= 1 << Irq;

    ProgramIrqMaskTrigger();
    return EFI_SUCCESS;
}

/**
    Get IRQ vector assigned to PCI card.

    @param This - Pointer to this object
    @param PciHandle - PCI handle for this device
    @param Vector - Interrupt vector this device

    @retval EFI_SUCCESS Vector returned.
    @retval EFI_INVALID_PARAMETER Invalid PciHandle.

    @note  Here is the control flow of this function:
           1. Get Handle of PciIo installed on PciHandle.
           2. If PciIo not installed, return EFI_INVALID_DEVICE.
           3. Set *vector to IRQ vector programmed into card.
           4. Return EFI_SUCCESS.

**/
EFI_STATUS GetInterruptLine (
    IN EFI_LEGACY_8259_PROTOCOL   *This,
    IN EFI_HANDLE                 PciHandle,
    OUT UINT8                     *Vector
)
{
    EFI_STATUS    Status;
    EFI_PCI_IO_PROTOCOL  *PciIo;
    UINT8     InterruptLine;

    Status = gBS->HandleProtocol(
                    PciHandle,
                    &gEfiPciIoProtocolGuid,
                    &PciIo
                    );
    if (EFI_ERROR(Status)) return EFI_INVALID_PARAMETER;
    //
    // Read vector from card.
    //
    PciIo->Pci.Read(
            PciIo,
            EfiPciIoWidthUint8,
            PCI_INT_LINE_OFFSET,
            1,
            &InterruptLine
            );

    *Vector = InterruptLine;

    return EFI_SUCCESS;
}

/**
    Send end of interrupt command to interrupt controller(s).

    @param This - Pointer to this object
    @param Irq - IRQ number for this EOI has to be sent

    @retval EFI_SUCCESS EOI command sent to controller(s)
    @retval EFI_INVALID_PARAMETER Interrupt not existent. The 8259 
                                  master/slave supports IRQ 0-15.

    @note  Here is the control flow of this function:
           1. Check if IRQ is valid. If not, return EFI_INVALID_PARAMETER.
           2. If IRQ >= 8, then Send EOI to slave controller.
           3. Send EOI to master controller. (This is for both master/slave IRQs)
           4. Return EFI_SUCCESS.

**/
EFI_STATUS EndOfInterrupt (
    IN EFI_LEGACY_8259_PROTOCOL   *This,
    IN EFI_8259_IRQ               Irq
)
{
    if (Irq > 15) return EFI_INVALID_PARAMETER;
    //
    // If Slave, send EOI to slave first.
    //
    if (Irq >= 8)
    {
        //
        // Send Slave EOI
        //
        IoWrite8(LEGACY_8259_CONTROL_REGISTER_SLAVE, EOI_COMMAND);
    }
    //
    // Send Master EOI
    //
    IoWrite8(LEGACY_8259_CONTROL_REGISTER_MASTER, EOI_COMMAND);

    return EFI_SUCCESS;
}

EFI_LEGACY_8259_PROTOCOL gLegacy8259Protocol =
{
    SetVectorBase,
    GetMask,
    SetMask,
    SetMode,
    GetVector,
    EnableIrq,
    DisableIrq,
    GetInterruptLine,
    EndOfInterrupt
};

/**
    Program the IRQ Mask and Trigger.

    @param ImageHandle  Image handle for this driver
    @param SystemTable  Pointer to the system table

    @retval EFI_STATUS

    @note  Here is the control flow of this function:
           1. Initialize AMI Library.
           2. Install Legacy 8259 Interface. If error, return error.
           3. Initialize the CPU setting vector bases.
           4. Set CPU Mode, mask, and trigger level.
           5. Return EFI_SUCCESS.

**/
EFI_STATUS Initialize8259 (
    IN EFI_HANDLE                 ImageHandle,
    IN EFI_SYSTEM_TABLE           *SystemTable
)
{
    EFI_STATUS    Status;
    UINT16        Mask  = 0xffff;     //Mask all interrupts.
    UINT16        EdgeLevel = 0x00;   //Set all edge.

    SetVectorBase (0, MASTER_INTERRUPT_BASE, SLAVE_INTERRUPT_BASE);
    SetMode (0, Efi8259ProtectedMode, &Mask, &EdgeLevel);

    Status = gBS->InstallMultipleProtocolInterfaces(
                    &ImageHandle,
                    &gEfiLegacy8259ProtocolGuid,
                    &gLegacy8259Protocol,
                    NULL
                    );

    return Status;
}
#endif

/**
    This function is the reset call interface function published
    by the reset

    @param VOID

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
RETURN_STATUS
EFIAPI
Sb8259InitLibConstructor (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
	EFI_STATUS	Status = EFI_SUCCESS;

#if defined SB_8259_PROTOCOL_SUPPORT && SB_8259_PROTOCOL_SUPPORT == 1 && (SB_8259_PROTOCOL_LIB_SUPPORT == 1)
	Status = Initialize8259(ImageHandle, SystemTable);
#endif
	
	return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
