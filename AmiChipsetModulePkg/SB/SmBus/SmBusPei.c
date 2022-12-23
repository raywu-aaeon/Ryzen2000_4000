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

//*************************************************************************
/** @file SmBusPei.c
    SMBUS PEI functions implementation

**/
//*************************************************************************

#include "Efi.h"
#include "Pei.h"
#include "Token.h"
#include <AmiPeiLib.h>
#include <AmiLib.h>
#include <Guid/AmiCspHobs.h>
#include <SmBusPei.h>
#include <Ppi/Stall.h>
#include <Ppi/EndOfPeiPhase.h>

extern EFI_GUID SmBusIdentifierGuid;

/**
    SMBUS driver PEI entry point

    @param FfsHeader pointer to file header
    @param PeiServices pointer to PEI services table

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
EFIAPI
SmBusPeiEntryPoint (
    IN EFI_PEI_FILE_HANDLE   FileHandle,
    IN CONST EFI_PEI_SERVICES          **PeiServices
    )
{
    EFI_STATUS Status;
    SMBUS_PEI_PRIVATE *Private;



    {
    SMBUS2_PEI_PRIVATE    *Smbus2Private;

    //===========================================
    // Install the SMBUS PPI2
    //===========================================
    Status = (*PeiServices)->AllocatePool(
                                        PeiServices,
                                        sizeof(SMBUS2_PEI_PRIVATE),
                                        &Smbus2Private);
    if(EFI_ERROR(Status))
        return Status;

    Status = (*PeiServices)->AllocatePool(
                                    PeiServices,
                                    sizeof(EFI_SMBUS_DEVICE_MAP) * MAX_PEI_ARP_DEVICES,
                                    &(Smbus2Private->SmBusContext.ArpDeviceList));
    if(EFI_ERROR(Status))
        return Status;

    //
    // Initialize the structure
    //
    Smbus2Private->SmBusPpi.Execute   = SmBus2PeiExecute;
    Smbus2Private->SmBusPpi.ArpDevice = SmBus2PeiArpDevice;
    Smbus2Private->SmBusPpi.GetArpMap = SmBus2PeiGetArpMap;
    Smbus2Private->SmBusPpi.Notify    = SmBus2PeiNotify;

    Smbus2Private->SmBusPpiDesc.Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
    Smbus2Private->SmBusPpiDesc.Guid  = &gEfiPeiSmbus2PpiGuid;
    Smbus2Private->SmBusPpiDesc.Ppi   = &Smbus2Private->SmBusPpi;

    Smbus2Private->NotifyDesc.Flags = EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
    Smbus2Private->NotifyDesc.Guid = &gEfiEndOfPeiSignalPpiGuid;
    Smbus2Private->NotifyDesc.Notify = SmBus2EndOfPeiCallback;

    Smbus2Private->SmBusContext.ArpDeviceCount = 0;
    Smbus2Private->SmBusContext.MaxDevices = MAX_PEI_ARP_DEVICES;
    Smbus2Private->SmBusContext.SmBusWait = SmBus2PeiWait;
    Smbus2Private->SmBusContext.SmBusBase = SMBUS_BASE_ADDRESS;
    Smbus2Private->SmBusPpi.Identifier = SmBusIdentifierGuid;

    Smbus2Private->PeiServices = PeiServices;
    Status = (**PeiServices).LocatePpi(PeiServices, &gEfiPeiStallPpiGuid, 0, NULL, \
                                        &Smbus2Private->StallPpi);

    if(EFI_ERROR(Status)) return Status;

    SmBusPeiInitialize(&Smbus2Private->SmBusContext);

    Status = (*PeiServices)->NotifyPpi(PeiServices, &Smbus2Private->NotifyDesc);
    if(EFI_ERROR(Status))
        return Status;

    Status = (*PeiServices)->InstallPpi(PeiServices, &Smbus2Private->SmBusPpiDesc);
    if(EFI_ERROR(Status))
        return Status;

    }

    {
    SMBUS2_PEI_PRIVATE    *Smbus2PrivateDash;

    //===========================================
    // Install the SMBUS PPI2
    //===========================================
    Status = (*PeiServices)->AllocatePool(
                                        PeiServices,
                                        sizeof(SMBUS2_PEI_PRIVATE),
                                        &Smbus2PrivateDash);
    if(EFI_ERROR(Status))
        return Status;

    Status = (*PeiServices)->AllocatePool(
                                    PeiServices,
                                    sizeof(EFI_SMBUS_DEVICE_MAP) * MAX_PEI_ARP_DEVICES,
                                    &(Smbus2PrivateDash->SmBusContext.ArpDeviceList));
    if(EFI_ERROR(Status))
        return Status;

    //
    // Initialize the structure
    //
    Smbus2PrivateDash->SmBusPpi.Execute   = SmBus2PeiExecute;
    Smbus2PrivateDash->SmBusPpi.ArpDevice = SmBus2PeiArpDevice;
    Smbus2PrivateDash->SmBusPpi.GetArpMap = SmBus2PeiGetArpMap;
    Smbus2PrivateDash->SmBusPpi.Notify    = SmBus2PeiNotify;

    Smbus2PrivateDash->SmBusPpiDesc.Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
    Smbus2PrivateDash->SmBusPpiDesc.Guid  = &gEfiPeiSmbus2PpiGuid;
    Smbus2PrivateDash->SmBusPpiDesc.Ppi   = &Smbus2PrivateDash->SmBusPpi;

    Smbus2PrivateDash->NotifyDesc.Flags = EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
    Smbus2PrivateDash->NotifyDesc.Guid = &gEfiEndOfPeiSignalPpiGuid;
    Smbus2PrivateDash->NotifyDesc.Notify = SmBus2EndOfPeiCallback;

    Smbus2PrivateDash->SmBusContext.ArpDeviceCount = 0;
    Smbus2PrivateDash->SmBusContext.MaxDevices = MAX_PEI_ARP_DEVICES;
    Smbus2PrivateDash->SmBusContext.SmBusWait = SmBus2PeiWait;
    Smbus2PrivateDash->SmBusContext.SmBusBase = SMBUS1_BASE_ADDRESS;
    Smbus2PrivateDash->SmBusPpi.Identifier = SmBusIdentifierGuid;

    Smbus2PrivateDash->PeiServices = PeiServices;
    Status = (**PeiServices).LocatePpi(PeiServices, &gEfiPeiStallPpiGuid, 0, NULL, \
                                        &Smbus2PrivateDash->StallPpi);

    if(EFI_ERROR(Status)) return Status;

    SmBusPeiInitialize(&Smbus2PrivateDash->SmBusContext);

    Status = (*PeiServices)->NotifyPpi(PeiServices, &Smbus2PrivateDash->NotifyDesc);
    if(EFI_ERROR(Status))
        return Status;

    Status = (*PeiServices)->InstallPpi(PeiServices, &Smbus2PrivateDash->SmBusPpiDesc);
    if(EFI_ERROR(Status))
        return Status;

    }


    Status = (*PeiServices)->AllocatePool(
                                        PeiServices,
                                        sizeof(SMBUS_PEI_PRIVATE),
                                        &Private);
    if(EFI_ERROR(Status))
        return Status;

    Status = (*PeiServices)->AllocatePool(
                                    PeiServices,
                                    sizeof(EFI_SMBUS_DEVICE_MAP) * MAX_PEI_ARP_DEVICES,
                                    &(Private->SmBusContext.ArpDeviceList));
    if(EFI_ERROR(Status))
        return Status;

    Private->SmBusPpi.Execute   = SmBusPeiExecute;
    Private->SmBusPpi.ArpDevice = SmBusPeiArpDevice;
    Private->SmBusPpi.GetArpMap = SmBusPeiGetArpMap;
    Private->SmBusPpi.Notify    = SmBusPeiNotify;

    Private->SmBusPpiDesc.Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
    Private->SmBusPpiDesc.Guid  = &gEfiPeiSmbusPpiGuid;
    Private->SmBusPpiDesc.Ppi   = &Private->SmBusPpi;

    Private->NotifyDesc.Flags = EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
    Private->NotifyDesc.Guid = &gEfiEndOfPeiSignalPpiGuid;
    Private->NotifyDesc.Notify = SmBusEndOfPeiCallback;

    Private->SmBusContext.ArpDeviceCount = 0;
    Private->SmBusContext.MaxDevices = MAX_PEI_ARP_DEVICES;
    Private->SmBusContext.SmBusWait = SmBusPeiWait;
    Private->SmBusContext.SmBusBase = SMBUS_BASE_ADDRESS;
    Private->Identifier = SmBusIdentifierGuid;

    Private->PeiServices = PeiServices;
    Status = (**PeiServices).LocatePpi(PeiServices, &gEfiPeiStallPpiGuid, 0, NULL, \
                                        &Private->StallPpi);

    if(EFI_ERROR(Status)) return Status;

    SmBusPeiInitialize(&Private->SmBusContext);

    Status = (*PeiServices)->NotifyPpi(PeiServices, &Private->NotifyDesc);
    if(EFI_ERROR(Status))
        return Status;
    Status = (*PeiServices)->InstallPpi(PeiServices, &Private->SmBusPpiDesc);
    if(EFI_ERROR(Status))
        return Status;
   {
    Status = (*PeiServices)->AllocatePool(
                                        PeiServices,
                                        sizeof(SMBUS_PEI_PRIVATE),
                                        &Private);
    if(EFI_ERROR(Status))
        return Status;

    Status = (*PeiServices)->AllocatePool(
                                    PeiServices,
                                    sizeof(EFI_SMBUS_DEVICE_MAP) * MAX_PEI_ARP_DEVICES,
                                    &(Private->SmBusContext.ArpDeviceList));
    if(EFI_ERROR(Status))
        return Status;

    Private->SmBusPpi.Execute   = SmBusPeiExecute;
    Private->SmBusPpi.ArpDevice = SmBusPeiArpDevice;
    Private->SmBusPpi.GetArpMap = SmBusPeiGetArpMap;
    Private->SmBusPpi.Notify    = SmBusPeiNotify;

    Private->SmBusPpiDesc.Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
    Private->SmBusPpiDesc.Guid  = &gEfiPeiSmbusPpiGuid;
    Private->SmBusPpiDesc.Ppi   = &Private->SmBusPpi;

    Private->NotifyDesc.Flags = EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
    Private->NotifyDesc.Guid = &gEfiEndOfPeiSignalPpiGuid;
    Private->NotifyDesc.Notify = SmBusEndOfPeiCallback;

    Private->SmBusContext.ArpDeviceCount = 0;
    Private->SmBusContext.MaxDevices = MAX_PEI_ARP_DEVICES;
    Private->SmBusContext.SmBusWait = SmBusPeiWait;
    Private->SmBusContext.SmBusBase = SMBUS1_BASE_ADDRESS;
    Private->Identifier = SmBusIdentifierGuid;

    Private->PeiServices = PeiServices;
    Status = (**PeiServices).LocatePpi(PeiServices, &gEfiPeiStallPpiGuid, 0, NULL, \
                                        &Private->StallPpi);

    if(EFI_ERROR(Status)) return Status;

    SmBusPeiInitialize(&Private->SmBusContext);

    Status = (*PeiServices)->NotifyPpi(PeiServices, &Private->NotifyDesc);
    if(EFI_ERROR(Status))
        return Status;
    Status = (*PeiServices)->InstallPpi(PeiServices, &Private->SmBusPpiDesc);
    if(EFI_ERROR(Status))
        return Status;
    }
    return Status;

}


//----------------------------------------------------------------------------
/**
  Executes an SMBus operation to an SMBus controller. Returns when either
  the command has been executed or an error is encountered in doing the operation.

  @param  This            A pointer to the EFI_PEI_SMBUS2_PPI instance.
  @param  SlaveAddress    The SMBUS hardware address to which the SMBUS device is preassigned or
                          allocated.
  @param  Command         This command is transmitted by the SMBus host controller to the SMBus slave
                          device and the interpretation is SMBus slave device specific.
                          It can mean the offset to a list of functions inside
                          an SMBus slave device. Not all operations or slave devices support
                          this command's registers.
  @param  Operation       Signifies which particular SMBus hardware protocol instance that it
                          will use to execute the SMBus transactions.
                          This SMBus hardware protocol is defined by the System Management Bus (SMBus)
                          Specification and is not related to UEFI.
  @param  PecCheck        Defines if Packet Error Code (PEC) checking is required for this operation.
  @param  Length          Signifies the number of bytes that this operation will do.
                          The maximum number of bytes can be revision specific and operation specific.
                          This parameter will contain the actual number of bytes that are executed
                          for this operation. Not all operations require this argument.
  @param  Buffer          Contains the value of data to execute to the SMBus slave device.
                          Not all operations require this argument.
                          The length of this buffer is identified by Length.


  @retval EFI_SUCCESS           The last data that was returned from the access
                                matched the poll exit criteria.
  @retval EFI_CRC_ERROR         The checksum is not correct (PEC is incorrect)
  @retval EFI_TIMEOUT           Timeout expired before the operation was completed.
                                Timeout is determined by the SMBus host controller device.
  @retval EFI_OUT_OF_RESOURCES  The request could not be completed
                                due to a lack of resources.
  @retval EFI_DEVICE_ERROR      The request was not completed because
                                a failure reflected in the Host Status Register bit.
  @retval EFI_INVALID_PARAMETER Operation is not defined in EFI_SMBUS_OPERATION.
                                Or Length/Buffer is NULL for operations except for EfiSmbusQuickRead and
                                EfiSmbusQuickWrite. Or Length is outside the range of valid values.
  @retval EFI_UNSUPPORTED       The SMBus operation or PEC is not supported.
  @retval EFI_BUFFER_TOO_SMALL  Buffer is not sufficient for this operation.

**/
EFI_STATUS SmBus2PeiExecute (
    IN CONST EFI_PEI_SMBUS2_PPI     *This,
    IN EFI_SMBUS_DEVICE_ADDRESS SlaveAddress,
    IN EFI_SMBUS_DEVICE_COMMAND Command,
    IN EFI_SMBUS_OPERATION Operation,
    IN BOOLEAN PecCheck,
    IN OUT UINTN *Length,
    IN OUT VOID *Buffer
    )
{
    SMBUS2_PEI_PRIVATE *Private = (SMBUS2_PEI_PRIVATE *)This;


    return Execute(
                &(Private->SmBusContext),
                SlaveAddress,
                Command,
                Operation,
                PecCheck,
                Length,
                Buffer);
}

/**
  The ArpDevice() function enumerates the entire bus or enumerates a specific
  device that is identified by SmbusUdid.

  @param  This           A pointer to the EFI_PEI_SMBUS2_PPI instance.
  @param  ArpAll         A Boolean expression that indicates if the host drivers need
                         to enumerate all the devices or enumerate only the device that is identified
                         by SmbusUdid. If ArpAll is TRUE, SmbusUdid and SlaveAddress are optional.
                         If ArpAll is FALSE, ArpDevice will enumerate SmbusUdid and the address
                         will be at SlaveAddress.
  @param  SmbusUdid      The targeted SMBus Unique Device Identifier (UDID).
                         The UDID may not exist for SMBus devices with fixed addresses.
  @param  SlaveAddress   The new SMBus address for the slave device for
                         which the operation is targeted.

  @retval EFI_SUCCESS           The SMBus slave device address was set.
  @retval EFI_INVALID_PARAMETER SlaveAddress is NULL.
  @retval EFI_OUT_OF_RESOURCES  The request could not be completed
                                due to a lack of resources.
  @retval EFI_TIMEOUT           The SMBus slave device did not respond.
  @retval EFI_DEVICE_ERROR      The request was not completed because the transaction failed.
  @retval EFI_UNSUPPORTED       ArpDevice, GetArpMap, and Notify are not implemented by this PEIM.

**/
EFI_STATUS SmBus2PeiArpDevice (
    IN CONST EFI_PEI_SMBUS2_PPI     *This,
    IN BOOLEAN ArpAll,
    IN EFI_SMBUS_UDID *SmbusUdid, OPTIONAL
    IN OUT EFI_SMBUS_DEVICE_ADDRESS *SlaveAddress OPTIONAL
    )
{
    SMBUS2_PEI_PRIVATE *Private = (SMBUS2_PEI_PRIVATE *)This;

    return ArpDevice(
                &(Private->SmBusContext),
                ArpAll,
                SmbusUdid,
                SlaveAddress);
}

/**
  The GetArpMap() function returns the mapping of all the SMBus devices
  that are enumerated by the SMBus host driver.

  @param  This           A pointer to the EFI_PEI_SMBUS2_PPI instance.
  @param  Length         Size of the buffer that contains the SMBus device map.
  @param  SmbusDeviceMap The pointer to the device map as enumerated
                         by the SMBus controller driver.

  @retval EFI_SUCCESS           The device map was returned correctly in the buffer.
  @retval EFI_UNSUPPORTED       ArpDevice, GetArpMap, and Notify are not implemented by this PEIM.

**/
EFI_STATUS SmBus2PeiGetArpMap (
    IN CONST EFI_PEI_SMBUS2_PPI *This,
    IN OUT UINTN *Length,
    IN OUT EFI_SMBUS_DEVICE_MAP **SmbusDeviceMap
    )
{
    SMBUS2_PEI_PRIVATE *Private = (SMBUS2_PEI_PRIVATE *)This;

    return GetArpMap(
                &(Private->SmBusContext),
                Length,
                SmbusDeviceMap);
}

/**
  CallBack function can be registered in EFI_PEI_SMBUS2_PPI_NOTIFY.

  @param  This           A pointer to the EFI_PEI_SMBUS2_PPI instance.
  @param  SlaveAddress   The SMBUS hardware address to which the SMBUS
                         device is preassigned or allocated.
  @param  Data           Data of the SMBus host notify command that
                         the caller wants to be called.

  @retval EFI_SUCCESS           NotifyFunction has been registered.
  @retval EFI_UNSUPPORTED       ArpDevice, GetArpMap, and Notify are not
                                implemented by this PEIM.

**/
EFI_STATUS SmBus2PeiNotify (
    IN CONST EFI_PEI_SMBUS2_PPI       *This,
    IN EFI_SMBUS_DEVICE_ADDRESS SlaveAddress,
    IN UINTN Data,
    IN EFI_PEI_SMBUS_NOTIFY2_FUNCTION NotifyFunction
    )
{
    return EFI_UNSUPPORTED;
}
/**
    This function creates map of devices connected to SMBUS at the end of PEI phase

    @param PeiServices pointer to PEI services table
    @param NotifyDescriptor pointer to notify descriptor
    @param Ppi pointer to notify PPI

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS SmBus2EndOfPeiCallback (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *Ppi
    )
{
    SMBUS2_PEI_PRIVATE *Private = OUTTER(NotifyDescriptor, NotifyDesc, SMBUS2_PEI_PRIVATE);
    UINTN HobSize;
    AMI_CSP_SMBUS_HOB *Hob;
    EFI_STATUS Status;

    HobSize = sizeof(AMI_CSP_SMBUS_HOB) + Private->SmBusContext.ArpDeviceCount * sizeof(EFI_SMBUS_DEVICE_MAP);
    Status = (*PeiServices)->CreateHob(PeiServices, EFI_HOB_TYPE_GUID_EXTENSION, HobSize, &Hob);
    if(!EFI_ERROR(Status))
    {
        Hob->Header.Name = Private->SmBusPpi.Identifier;
        Hob->BoardReservedAddressCount = Private->SmBusContext.BoardReservedAddressCount;
        Hob->BoardReservedAddressList = (UINT32)Private->SmBusContext.BoardReservedAddressList;
        Hob->ArpDeviceCount = Private->SmBusContext.ArpDeviceCount;
        MemCpy(Hob->ArpDeviceList,
               Private->SmBusContext.ArpDeviceList,
               Private->SmBusContext.ArpDeviceCount * sizeof(EFI_SMBUS_DEVICE_MAP));
    }
    return Status;
}

/**
    This function waits given number of microseconds

    @param This 
    @param Microseconds number of microseconds to wait

    @retval VOID

    @note  Porting required

**/
VOID SmBus2PeiWait(
    IN SMBUS_PRIVATE *This,
    IN UINTN Microseconds
    )
{
    SMBUS2_PEI_PRIVATE       *Private = OUTTER(This, SmBusContext, SMBUS2_PEI_PRIVATE);
    Private->StallPpi->Stall(Private->PeiServices, Private->StallPpi, Microseconds);
}


//----------------------------------------------------------------------------
/**
  Executes an SMBus operation to an SMBus controller.

  @param[in]      PeiServices   A pointer to the system PEI Services Table.
  @param[in]      This          A pointer to the EFI_PEI_SMBUS_PPI instance.
  @param[in]      SlaveAddress  The SMBUS hardware address to which the SMBUS
                                device is preassigned or allocated.
  @param[in]      Command       This command is transmitted by the SMBus host
                                controller to the SMBus slave device, and the
                                interpretation is SMBus slave device specific.
  @param[in]      Operation     Signifies which particular SMBus hardware protocol
                                instance to use to execute the SMBus transactions.
  @param[in]      PecCheck      Defines if Packet Error Code (PEC) checking is
                                required for this operation.
  @param[in, out] Length        The number of bytes for this operation.
  @param[in, out] Buffer        Contains the value of data to execute to the SMBus
                                slave device.

  @retval EFI_SUCCESS           The last data that was returned from the access
                                matched the poll exit criteria.
  @retval EFI_CRC_ERROR         The checksum is not correct (PEC is incorrect).
  @retval EFI_TIMEOUT           Timeout expired before the operation was completed.
                                Timeout is determined by the SMBus host controller device.
  @retval EFI_OUT_OF_RESOURCES  The request could not be completed
                                due to a lack of resources.
  @retval EFI_DEVICE_ERROR      The request was not completed because a failure
                                was recorded in the Host Status Register bit.
  @retval EFI_INVALID_PARAMETER The operation is not defined in EFI_SMBUS_OPERATION.
  @retval EFI_INVALID_PARAMETER Length/Buffer is NULL for operations except for
                                EfiSmbusQuickRead and EfiSmbusQuickWrite. Length
                                is outside the range of valid values.
  @retval EFI_UNSUPPORTED       The SMBus operation or PEC is not supported.
  @retval EFI_BUFFER_TOO_SMALL  Buffer is not sufficient for this operation.

**/
EFI_STATUS SmBusPeiExecute (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_SMBUS_PPI        *This,
    IN EFI_SMBUS_DEVICE_ADDRESS SlaveAddress,
    IN EFI_SMBUS_DEVICE_COMMAND Command,
    IN EFI_SMBUS_OPERATION Operation,
    IN BOOLEAN PecCheck,
    IN OUT UINTN *Length,
    IN OUT VOID *Buffer
    )
{
    SMBUS_PEI_PRIVATE *Private = (SMBUS_PEI_PRIVATE *)This;

    return Execute(
                &(Private->SmBusContext),
                SlaveAddress,
                Command,
                Operation,
                PecCheck,
                Length,
                Buffer);
}

/**
  The ArpDevice() function enumerates either the entire bus or a specific
  device identified by SmbusUdid.

  @param[in]      PeiServices   A pointer to the system PEI Services Table.
  @param[in]      This          A pointer to the EFI_PEI_SMBUS_PPI instance.
  @param[in]      ArpAll        A Boolean expression that indicates if the host
                                drivers need to enumerate all the devices or to
                                enumerate only the device that is identified
                                by SmbusUdid. If ArpAll is TRUE, SmbusUdid and
                                SlaveAddress are optional and ignored if entered.
                                If ArpAll is FALSE, ArpDevice will enumerate
                                SmbusUdid, and the address will be at SlaveAddress.
  @param[in]      SmbusUdid     The targeted SMBus Unique Device Identifier (UDID).
                                The UDID may not exist for SMBus devices with fixed
                                addresses.
  @param[in, out] SlaveAddress  The new SMBus address for the slave device for
                                which the operation is targeted.
                                This address may be NULL.

  @retval EFI_SUCCESS           The SMBus slave device address was set.
  @retval EFI_INVALID_PARAMETER SlaveAddress is NULL.
  @retval EFI_OUT_OF_RESOURCES  The request could not be completed
                                due to a lack of resources.
  @retval EFI_TIMEOUT           The SMBus slave device did not respond.
  @retval EFI_DEVICE_ERROR      The request was not completed because the transaction failed.
  @retval EFI_UNSUPPORTED       ArpDevice() is not implemented by this PEIM.
                                This return value is not defined in the Framework Specification.
                                This return value was introduced in the PI Specification.

**/
EFI_STATUS SmBusPeiArpDevice (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_SMBUS_PPI            *This,
    IN BOOLEAN ArpAll,
    IN EFI_SMBUS_UDID *SmbusUdid, OPTIONAL
    IN OUT EFI_SMBUS_DEVICE_ADDRESS *SlaveAddress OPTIONAL
    )
{
    SMBUS_PEI_PRIVATE *Private = (SMBUS_PEI_PRIVATE *)This;

    return ArpDevice(
                &(Private->SmBusContext),
                ArpAll,
                SmbusUdid,
                SlaveAddress);
}

/**
  The GetArpMap() function returns the mapping of all the SMBus devices
  that are enumerated by the SMBus host driver.

  @param[in]      PeiServices    A pointer to the system PEI Services Table.
  @param[in]      This           A pointer to the EFI_PEI_SMBUS_PPI instance.
  @param[in, out] Length         The size of the buffer that contains the SMBus device map.
  @param[in, out] SmbusDeviceMap The pointer to the device map as enumerated
                                 by the SMBus controller driver.

  @retval EFI_SUCCESS       The device map was returned correctly in the buffer.
  @retval EFI_UNSUPPORTED   GetArpMap() are not implemented by this PEIM.
                            This return value was not defined in the Framework Specification.
                            This return value was introduced in the PI Specification.

**/
EFI_STATUS SmBusPeiGetArpMap (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_SMBUS_PPI        *This,
    IN OUT UINTN *Length,
    IN OUT EFI_SMBUS_DEVICE_MAP **SmbusDeviceMap
    )
{
    SMBUS_PEI_PRIVATE *Private = (SMBUS_PEI_PRIVATE *)This;

    return GetArpMap(
                &(Private->SmBusContext),
                Length,
                SmbusDeviceMap);
}

/**
  This function is user-defined, and is called when the SlaveAddress/Data pair happens.

  @param[in]  PeiServices    A pointer to the system PEI Services Table.
  @param[in]  This           A pointer to the EFI_PEI_SMBUS_PPI instance.
  @param[in]  SlaveAddress   The SMBUS hardware address to which the SMBUS
                             device is preassigned or allocated.
  @param[in]  Data           Data of the SMBus host notify command, which denotes that
                             the caller wants to be called.

  @return Status Code returned by callback function.

**/
EFI_STATUS SmBusPeiNotify (
    IN EFI_PEI_SERVICES               **PeiServices,
    IN EFI_PEI_SMBUS_PPI              *This,
    IN EFI_SMBUS_DEVICE_ADDRESS SlaveAddress,
    IN UINTN Data,
    IN EFI_PEI_SMBUS_NOTIFY_FUNCTION NotifyFunction
    )
{
    return EFI_UNSUPPORTED;
}

/**
    This function creates map of devices connected to SMBUS at the end of PEI phase

    @param PeiServices pointer to PEI services table
    @param NotifyDescriptor pointer to notify descriptor
    @param Ppi pointer to notify PPI

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS SmBusEndOfPeiCallback (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *Ppi
    )
{
    SMBUS_PEI_PRIVATE *Private = OUTTER(NotifyDescriptor, NotifyDesc, SMBUS_PEI_PRIVATE);
    UINTN HobSize;
    AMI_CSP_SMBUS_HOB *Hob;
    EFI_STATUS Status;

    HobSize = sizeof(AMI_CSP_SMBUS_HOB) + Private->SmBusContext.ArpDeviceCount * sizeof(EFI_SMBUS_DEVICE_MAP);
    Status = (*PeiServices)->CreateHob(PeiServices, EFI_HOB_TYPE_GUID_EXTENSION, HobSize, &Hob);
    if(!EFI_ERROR(Status))
    {
        Hob->Header.Name = Private->Identifier;
        Hob->BoardReservedAddressCount = Private->SmBusContext.BoardReservedAddressCount;
        Hob->BoardReservedAddressList = (UINT32)Private->SmBusContext.BoardReservedAddressList;
        Hob->ArpDeviceCount = Private->SmBusContext.ArpDeviceCount;
        MemCpy(Hob->ArpDeviceList,
               Private->SmBusContext.ArpDeviceList,
               Private->SmBusContext.ArpDeviceCount * sizeof(EFI_SMBUS_DEVICE_MAP));
    }
    return Status;
}


//**********************************************************************
//                  Porting functions
//**********************************************************************

/**
    This function waits given number of microseconds

               
    @param This Pointer to the SMBus PPI structure
    @param Microseconds number of microseconds to wait

    @retval VOID

    @note  Porting required

**/
VOID SmBusPeiWait(
    IN SMBUS_PRIVATE *This,
    IN UINTN Microseconds
    )
{
    SMBUS_PEI_PRIVATE       *Private = OUTTER(This, SmBusContext, SMBUS_PEI_PRIVATE);
    Private->StallPpi->Stall(Private->PeiServices, Private->StallPpi, Microseconds);
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
