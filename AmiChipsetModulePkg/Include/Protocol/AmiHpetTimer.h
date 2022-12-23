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

/** @file AmiHpetTimer.h
    This file contains HPET Timer data structures 
    definitions

*/
#ifndef __AMI_HPET_TIMER__H__
#define __AMI_HPET_TIMER__H__
#ifdef __cplusplus
extern "C" {
#endif

//
// Definition for Local APIC registers and related values
//
#define LOCAL_APIC_DELIVERY_MODE_FIXED           0
#define LOCAL_APIC_DELIVERY_MODE_LOWEST_PRIORITY 1
#define LOCAL_APIC_DELIVERY_MODE_SMI             2
#define LOCAL_APIC_DELIVERY_MODE_NMI             4
#define LOCAL_APIC_DELIVERY_MODE_INIT            5
#define LOCAL_APIC_DELIVERY_MODE_STARTUP         6
#define LOCAL_APIC_DELIVERY_MODE_EXTINT          7

//
// I/O APIC Register Offsets
//
#define IOAPIC_INDEX_OFFSET  0x00
#define IOAPIC_DATA_OFFSET   0x10

//
// I/O APIC Indirect Register Indexes
//
#define IO_APIC_IDENTIFICATION_REGISTER_INDEX  0x00
#define IO_APIC_VERSION_REGISTER_INDEX         0x01
#define IO_APIC_REDIRECTION_TABLE_ENTRY_INDEX  0x10

//
// I/O APIC Interrupt Deliver Modes
//
#define IO_APIC_DELIVERY_MODE_FIXED            0
#define IO_APIC_DELIVERY_MODE_LOWEST_PRIORITY  1
#define IO_APIC_DELIVERY_MODE_SMI              2
#define IO_APIC_DELIVERY_MODE_NMI              4
#define IO_APIC_DELIVERY_MODE_INIT             5
#define IO_APIC_DELIVERY_MODE_EXTINT           7

//
// HPET General Register Offsets
//
#define HPET_GENERAL_CAPABILITIES_ID_OFFSET     0x000
#define HPET_GENERAL_CONFIGURATION_OFFSET       0x010
#define HPET_GENERAL_INTERRUPT_STATUS_OFFSET    0x020

//
// HPET Timer Register Offsets
//
#define HPET_MAIN_COUNTER_OFFSET                0x0F0
#define HPET_TIMER_CONFIGURATION_OFFSET         0x100
#define HPET_TIMER_COMPARATOR_OFFSET            0x108
#define HPET_TIMER_MSI_ROUTE_OFFSET             0x110

//
// Stride between sets of HPET Timer Registers
//
#define HPET_TIMER_STRIDE                       0x020

//
// Define value for an invalid HPET Timer index.
//
#define HPET_INVALID_TIMER_INDEX                0xFF

#pragma pack(1)

typedef union {
  struct {
    UINT32  Reserved0:24;
    UINT32  Identification:4;
    UINT32  Reserved1:4;
  } Bits;
  UINT32  Uint32;
} IO_APIC_IDENTIFICATION_REGISTER;

typedef union {
  struct {
    UINT32  Version:8;
    UINT32  Reserved0:8;
    UINT32  MaximumRedirectionEntry:8;
    UINT32  Reserved1:8;
  } Bits;
  UINT32  Uint32;
} IO_APIC_VERSION_REGISTER;

typedef union {
  struct {
    UINT32  Vector:          8;
    UINT32  DeliveryMode:    3;
    UINT32  DestinationMode: 1;
    UINT32  DeliveryStatus:  1;
    UINT32  Polarity:        1;
    UINT32  RemoteIRR:       1;
    UINT32  TriggerMode:     1;
    UINT32  Mask:            1;
    UINT32  Reserved0:       15;
    UINT32  Reserved1:       24;
    UINT32  DestinationID:   8;
  } Bits;
  struct {
    UINT32  Low;
    UINT32  High;
  } Uint32;
  UINT64  Uint64;
} IO_APIC_REDIRECTION_TABLE_ENTRY;

// HPET General Capabilities and ID Register
typedef union {
  struct {
    UINT32  Revision:8;
    UINT32  NumberOfTimers:5;
    UINT32  CounterSize:1;
    UINT32  Reserved0:1;
    UINT32  LegacyRoute:1;
    UINT32  VendorId:16;
    UINT32  CounterClockPeriod:32;
  } Bits;
  UINT64  Uint64;
} HPET_GENERAL_CAPABILITIES_ID_REGISTER;

// HPET General Configuration Register
typedef union {
  struct {
    UINT32  MainCounterEnable:1;
    UINT32  LegacyRouteEnable:1;
    UINT32  Reserved0:30;
    UINT32  Reserved1:32;
  } Bits;
  UINT64  Uint64;
} HPET_GENERAL_CONFIGURATION_REGISTER;

// HPET Timer Configuration Register
typedef union {
  struct {
    UINT32  Reserved0:1;
    UINT32  LevelTriggeredInterrupt:1;
    UINT32  InterruptEnable:1;
    UINT32  PeriodicInterruptEnable:1;
    UINT32  PeriodicInterruptCapablity:1;
    UINT32  CounterSizeCapablity:1;
    UINT32  ValueSetEnable:1;
    UINT32  Reserved1:1;
    UINT32  CounterSizeEnable:1;
    UINT32  InterruptRoute:5;
    UINT32  MsiInterruptEnable:1;
    UINT32  MsiInterruptCapablity:1;
    UINT32  Reserved2:16;
    UINT32  InterruptRouteCapability;
  } Bits;
  UINT64  Uint64;
} HPET_TIMER_CONFIGURATION_REGISTER;

// HPET Timer MSI Route Register
typedef union {
  struct {
    UINT32  Value:32;
    UINT32  Address:32;
  } Bits;
  UINT64  Uint64;
} HPET_TIMER_MSI_ROUTE_REGISTER;

#pragma pack()

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

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
