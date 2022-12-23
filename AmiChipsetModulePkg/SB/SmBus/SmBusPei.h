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
/** @file SmBusPei.h
    This file contains PEI SMBUS Driver functions and data structures definition

**/
//*************************************************************************

#ifndef __SMBUS_PEI__H__
#define __SMBUS_PEI__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <Library/SmBusCommon.h>
// consumed PPI
#include <Ppi/Stall.h>
#include <Ppi/Smbus2.h>
#include <Ppi/Smbus.h>

#define MAX_PEI_ARP_DEVICES 8

#pragma pack(1)


/**
    AMI SMBUS driver PEI private data structure

 Fields: Name         Type                        Description
 SmBusPpi             EFI_PEI_SMBUS_PPI           SMBUS PPI structure
 Identifier           EFI_GUID                    SMBUS controller identifier
 SmBusContext         SMBUS_PRIVATE               SMBUS private data structure
 NotifyDesc           EFI_PEI_NOTIFY_DESCRIPTOR   Notify descriptor structure
 SmBusPpiDesc         EFI_PEI_PPI_DESCRIPTOR      PPI descriptor structure

**/
typedef struct _SMBUS2_PEI_PRIVATE
{
    EFI_PEI_SMBUS2_PPI        SmBusPpi;
    EFI_PEI_STALL_PPI         *StallPpi;
    EFI_PEI_SERVICES          **PeiServices;
    SMBUS_PRIVATE             SmBusContext;
    EFI_PEI_NOTIFY_DESCRIPTOR NotifyDesc;
    EFI_PEI_PPI_DESCRIPTOR    SmBusPpiDesc;
} SMBUS2_PEI_PRIVATE;



/**
    AMI SMBUS driver PEI private data structure

 Fields: Name         Type                        Description
 SmBusPpi             EFI_PEI_SMBUS_PPI           SMBUS PPI structure
 Identifier           EFI_GUID                    SMBUS controller identifier
 SmBusContext         SMBUS_PRIVATE               SMBUS private data structure
 NotifyDesc           EFI_PEI_NOTIFY_DESCRIPTOR   Notify descriptor structure
 SmBusPpiDesc         EFI_PEI_PPI_DESCRIPTOR      PPI descriptor structure

**/
typedef struct _SMBUS_PEI_PRIVATE
{
    EFI_PEI_SMBUS_PPI               SmBusPpi;
    EFI_GUID                        Identifier;
    EFI_PEI_STALL_PPI         *StallPpi;
    EFI_PEI_SERVICES          **PeiServices;
    SMBUS_PRIVATE             SmBusContext;
    EFI_PEI_NOTIFY_DESCRIPTOR NotifyDesc;
    EFI_PEI_PPI_DESCRIPTOR    SmBusPpiDesc;
} SMBUS_PEI_PRIVATE;

#pragma pack()

EFI_STATUS
EFIAPI
SmBusPeiEntryPoint (
    IN EFI_PEI_FILE_HANDLE   FileHandle,
    IN CONST EFI_PEI_SERVICES          **PeiServices
    );

EFI_STATUS SmBus2PeiExecute (
    IN CONST EFI_PEI_SMBUS2_PPI     *This,
    IN EFI_SMBUS_DEVICE_ADDRESS SlaveAddress,
    IN EFI_SMBUS_DEVICE_COMMAND Command,
    IN EFI_SMBUS_OPERATION Operation,
    IN BOOLEAN PecCheck,
    IN OUT UINTN *Length,
    IN OUT VOID *Buffer
    );

EFI_STATUS SmBus2PeiArpDevice (
    IN CONST EFI_PEI_SMBUS2_PPI     *This,
    IN BOOLEAN ArpAll,
    IN EFI_SMBUS_UDID *SmbusUdid, OPTIONAL
    IN OUT EFI_SMBUS_DEVICE_ADDRESS *SlaveAddress OPTIONAL
    );

EFI_STATUS SmBus2PeiGetArpMap (
    IN CONST EFI_PEI_SMBUS2_PPI     *This,
    IN OUT UINTN *Length,
    IN OUT EFI_SMBUS_DEVICE_MAP **SmbusDeviceMap
    );

EFI_STATUS SmBus2PeiNotify (
    IN CONST EFI_PEI_SMBUS2_PPI     *This,
    IN EFI_SMBUS_DEVICE_ADDRESS SlaveAddress,
    IN UINTN Data,
    IN EFI_PEI_SMBUS_NOTIFY2_FUNCTION NotifyFunction
    );

EFI_STATUS SmBus2EndOfPeiCallback (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *Ppi
    );

VOID SmBus2PeiWait(
    IN SMBUS_PRIVATE *This,
    IN UINTN Microseconds
    );


EFI_STATUS SmBusPeiExecute (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_SMBUS_PPI            *This,
    IN EFI_SMBUS_DEVICE_ADDRESS SlaveAddress,
    IN EFI_SMBUS_DEVICE_COMMAND Command,
    IN EFI_SMBUS_OPERATION Operation,
    IN BOOLEAN PecCheck,
    IN OUT UINTN *Length,
    IN OUT VOID *Buffer
    );

EFI_STATUS SmBusPeiArpDevice (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_SMBUS_PPI            *This,
    IN BOOLEAN ArpAll,
    IN EFI_SMBUS_UDID *SmbusUdid, OPTIONAL
    IN OUT EFI_SMBUS_DEVICE_ADDRESS *SlaveAddress OPTIONAL
    );

EFI_STATUS SmBusPeiGetArpMap (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_SMBUS_PPI            *This,
    IN OUT UINTN *Length,
    IN OUT EFI_SMBUS_DEVICE_MAP **SmbusDeviceMap
    );

EFI_STATUS SmBusPeiNotify (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_SMBUS_PPI            *This,
    IN EFI_SMBUS_DEVICE_ADDRESS SlaveAddress,
    IN UINTN Data,
    IN EFI_PEI_SMBUS_NOTIFY_FUNCTION NotifyFunction
    );

EFI_STATUS SmBusEndOfPeiCallback (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *Ppi
    );

VOID SmBusPeiWait(
    IN SMBUS_PRIVATE *This,
    IN UINTN Microseconds
    );

VOID SmBusPeiInitialize(
    IN SMBUS_PRIVATE *Context
    );

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
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
