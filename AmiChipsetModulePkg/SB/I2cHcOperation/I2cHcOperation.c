//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file I2cHcOperation.c
    This file contains code for I2c Hc Operation Protocol initialization
    in the DXE stage

*/

// Module specific Includes

#include "I2cHcOperationDxe.h"


I2C_BUS_INSTANCE      *gI2cContext = NULL;


AMI_FCH_I2C_CONTROLLER_INFO gAmiFchI2cControllerList[] = {
    {I2C2_BUS_NUM, I2C2_MMIO_BASE, I2C2_HANDLE_ENABLED},
    {I2C3_BUS_NUM, I2C3_MMIO_BASE, I2C3_HANDLE_ENABLED},
    {I2C4_BUS_NUM, I2C4_MMIO_BASE, I2C4_HANDLE_ENABLED}
};

/**
    This function is the entry point for this DXE. This function
    initializes I2C HC Operation Protocol.

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

    @retval Return Status based on errors that occurred while waiting for
            time to expire.

**/
EFI_STATUS
EFIAPI
InitializeI2cHcOperationEntry (
    IN  EFI_HANDLE            ImageHandle,
    IN  EFI_SYSTEM_TABLE      *SystemTable
    )
{
    UINTN         Index;
    EFI_STATUS    Status;

    gI2cContext = AllocateZeroPool(sizeof(I2C_BUS_INSTANCE) * MAX_I2C_BUS);
    if (gI2cContext == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    for (Index = 0; Index < MAX_I2C_BUS; Index++) {
        if (!gAmiFchI2cControllerList[Index].Enabled) {
            continue;
        }

        //
        // Initializes I2c Context
        //
        gI2cContext[Index].Signature = I2C_PRIVATE_DATA_SIGNATURE;
        gI2cContext[Index].Version   = AMI_I2C_HC_VERSION_1;
        gI2cContext[Index].BusNo     = (UINT8)gAmiFchI2cControllerList[Index].ControllerNum;
        gI2cContext[Index].Handle    = NULL;
        gI2cContext[Index].I2cBase   = gAmiFchI2cControllerList[Index].MmioBase;

        //
        // Initializes I2C location information
        //
        gI2cContext[Index].Location.BaseAddress = gI2cContext[Index].I2cBase;
        // gI2cContext[Index].Location.Capabilities = I2C_HC_CAP_10BIT_ADDR;

        //
        // Initialize the I2C Hc Operation Protocol
        //
        Status = I2cHcOperationProtocolInit (&gI2cContext[Index].I2cHcOpProtocol);
        if (EFI_ERROR(Status)) {
            continue;
        }

        //
        // Install AMI I2C Hc Operation Protocol
        //
        Status = gBS->InstallMultipleProtocolInterfaces (
                        &gI2cContext[Index].Handle,
                        &gAmiI2cHcOperationProtocolGuid,
                        &gI2cContext[Index].I2cHcOpProtocol,
                        NULL);
        ASSERT_EFI_ERROR(Status);
    } // for (Index = 0; Index < MAX_I2C_BUS; Index++)

    return EFI_SUCCESS;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
