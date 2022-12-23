//*************************************************************************
//*************************************************************************
//**                                                                     **
//**          (C)Copyright 1985-2019, American Megatrends, Inc.          **
//**                                                                     **
//**                         All Rights Reserved.                        **
//**                                                                     **
//**        5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                     **
//**                         Phone: (770)-246-8600                       **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file MpService.h
    This file is an include file used to define the Protocol for the
    DXE Mp Service Protocol.

**/

#ifndef _MP_SERVICES_H_
#define _MP_SERVICES_H_

#ifdef __cplusplus
extern "C" {
#endif

/// Global ID for the EFI_MP_SERVICES_PROTOCOL.
#define EFI_MP_SERVICES_PROTOCOL_GUID \
  { 0x3fdda605, 0xa76e, 0x4f46, 0xad, 0x29, 0x12, 0xf4, 0x53, 0x1b, 0x3d, 0x08 }

//GUID_VARIABLE_DECLARATION(gEfiMpServiceProtocolGuid, EFI_MP_SERVICES_PROTOCOL_GUID);
extern EFI_GUID    gEfiMpServiceProtocolGuid;

typedef struct _EFI_MP_SERVICES_PROTOCOL EFI_MP_SERVICES_PROTOCOL;

#ifndef EFI_AP_PROCEDURE_TYPE_DEFINED
#define EFI_AP_PROCEDURE_TYPE_DEFINED
typedef VOID (*EFI_AP_PROCEDURE) (
	IN VOID	*Buffer
);
#endif

/// Terminator for a list of failed CPUs returned by StartAllAPs().
#define END_OF_CPU_LIST    0xffffffff

/// This bit is used in the StatusFlag field of EFI_PROCESSOR_INFORMATION and 
/// indicates whether the processor is playing the role of BSP. If the bit is 1,
/// then the processor is BSP. Otherwise, it is AP.
#define PROCESSOR_AS_BSP_BIT         0x00000001

/// This bit is used in the StatusFlag field of EFI_PROCESSOR_INFORMATION and 
/// indicates whether the processor is enabled. If the bit is 1, then the 
/// processor is enabled. Otherwise, it is disabled.
#define PROCESSOR_ENABLED_BIT        0x00000002

/// This bit is used in the StatusFlag field of EFI_PROCESSOR_INFORMATION and 
/// indicates whether the processor is healthy. If the bit is 1, then the 
/// processor is healthy. Otherwise, some fault has been detected for the processor.
#define PROCESSOR_HEALTH_STATUS_BIT  0x00000004

#pragma pack (push, 1)
/// Structure that describes the pyhiscal location of a logical CPU.
typedef struct {
  /// Zero-based physical package number that identifies the cartridge of the processor.
  UINT32  Package;
  /// Zero-based physical core number within package of the processor.
  UINT32  Core;
  /// Zero-based logical thread number within core of the processor.
  UINT32  Thread;
} EFI_CPU_PHYSICAL_LOCATION;

/// Structure that describes information about a logical CPU.
typedef struct {
  /// The unique processor ID determined by system hardware.  For IA32 and X64, 
  /// the processor ID is the same as the Local APIC ID. Only the lower 8 bits 
  /// are used, and higher bits are reserved.  For IPF, the lower 16 bits contains
  /// id/eid, and higher bits are reserved.
  ///
  UINT64                     ProcessorId; 
  ///
  /// Flags indicating if the processor is BSP or AP, if the processor is enabled 
  /// or disabled, and if the processor is healthy. Bits 3..31 are reserved and 
  /// must be 0. 
  /// 
  /// <pre>
  /// BSP  ENABLED  HEALTH  Description
  /// ===  =======  ======  ===================================================
  ///  0      0       0     Unhealthy Disabled AP.
  ///  0      0       1     Healthy Disabled AP.
  ///  0      1       0     Unhealthy Enabled AP.
  ///  0      1       1     Healthy Enabled AP.
  ///  1      0       0     Invalid. The BSP can never be in the disabled state.
  ///  1      0       1     Invalid. The BSP can never be in the disabled state.
  ///  1      1       0     Unhealthy Enabled BSP.
  ///  1      1       1     Healthy Enabled BSP.
  /// </pre>
  ///
  UINT32                     StatusFlag;
  ///
  /// The physical location of the processor, including the physical package number
  /// that identifies the cartridge, the physical core number within package, and 
  /// logical thread number within core.
  ///
  EFI_CPU_PHYSICAL_LOCATION  Location;
} EFI_PROCESSOR_INFORMATION;
#pragma pack (pop)

typedef
EFI_STATUS
(EFIAPI *EFI_MP_SERVICES_GET_NUMBER_OF_PROCESSORS)(
  IN  EFI_MP_SERVICES_PROTOCOL  *This,
  OUT UINTN                     *NumberOfProcessors,
  OUT UINTN                     *NumberOfEnabledProcessors
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MP_SERVICES_GET_PROCESSOR_INFO)(
  IN  EFI_MP_SERVICES_PROTOCOL   *This,
  IN  UINTN                      ProcessorNumber,
  OUT EFI_PROCESSOR_INFORMATION  *ProcessorInfoBuffer
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MP_SERVICES_STARTUP_ALL_APS)(
  IN  EFI_MP_SERVICES_PROTOCOL  *This,
  IN  EFI_AP_PROCEDURE          Procedure,
  IN  BOOLEAN                   SingleThread,
  IN  EFI_EVENT                 WaitEvent               OPTIONAL,
  IN  UINTN                     TimeoutInMicroSeconds,
  IN  VOID                      *ProcedureArgument      OPTIONAL,
  OUT UINTN                     **FailedCpuList         OPTIONAL
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MP_SERVICES_STARTUP_THIS_AP)(
  IN  EFI_MP_SERVICES_PROTOCOL  *This,
  IN  EFI_AP_PROCEDURE          Procedure,
  IN  UINTN                     ProcessorNumber,
  IN  EFI_EVENT                 WaitEvent               OPTIONAL,
  IN  UINTN                     TimeoutInMicroseconds,
  IN  VOID                      *ProcedureArgument      OPTIONAL,
  OUT BOOLEAN                   *Finished               OPTIONAL
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MP_SERVICES_SWITCH_BSP)(
  IN EFI_MP_SERVICES_PROTOCOL  *This,
  IN  UINTN                    ProcessorNumber,
  IN  BOOLEAN                  EnableOldBSP
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MP_SERVICES_ENABLEDISABLEAP)(
  IN  EFI_MP_SERVICES_PROTOCOL  *This,
  IN  UINTN                     ProcessorNumber,
  IN  BOOLEAN                   EnableAP,
  IN  UINT32                    *HealthFlag OPTIONAL
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MP_SERVICES_WHOAMI)(
  IN EFI_MP_SERVICES_PROTOCOL  *This,
  OUT UINTN                    *ProcessorNumber
  );

/// When installed, the MP Services Protocol produces a collection of services 
/// that are needed for MP management.
///
/// Before the UEFI event EFI_EVENT_GROUP_READY_TO_BOOT is signaled, the module 
/// that produces this protocol is required to place all APs into an idle state 
/// whenever the APs are disabled or the APs are not executing code as requested 
/// through the StartupAllAPs() or StartupThisAP() services. The idle state of 
/// an AP before the UEFI event EFI_EVENT_GROUP_READY_TO_BOOT is signaled is 
/// implementation dependent.
///
/// After the UEFI event EFI_EVENT_GROUP_READY_TO_BOOT is signaled, all the APs 
/// must be placed in the OS compatible CPU state as defined by the UEFI 
/// Specification. Implementations of this protocol may use the UEFI event 
/// EFI_EVENT_GROUP_READY_TO_BOOT to force APs into the OS compatible state as 
/// defined by the UEFI Specification. Modules that use this protocol must 
/// guarantee that all non-blocking mode requests on all APs have been completed 
/// before the UEFI event EFI_EVENT_GROUP_READY_TO_BOOT is signaled. Since the 
/// order that event notification functions in the same event group are executed 
/// is not deterministic, an event of type EFI_EVENT_GROUP_READY_TO_BOOT cannot 
/// be used to guarantee that APs have completed their non-blocking mode requests.
///
/// When the UEFI event EFI_EVENT_GROUP_READY_TO_BOOT is signaled, the StartAllAPs() 
/// and StartupThisAp() services must no longer support non-blocking mode requests. 
/// The support for SwitchBSP() and EnableDisableAP() may no longer be supported 
/// after this event is signaled. Since UEFI Applications and UEFI OS Loaders 
/// execute after the UEFI event EFI_EVENT_GROUP_READY_TO_BOOT is signaled, these 
/// UEFI images must be aware that the functionality of this protocol may be reduced.
/// 
#pragma pack (push, 1)
struct _EFI_MP_SERVICES_PROTOCOL {
  EFI_MP_SERVICES_GET_NUMBER_OF_PROCESSORS  GetNumberOfProcessors;
  EFI_MP_SERVICES_GET_PROCESSOR_INFO        GetProcessorInfo;
  EFI_MP_SERVICES_STARTUP_ALL_APS           StartupAllAPs;
  EFI_MP_SERVICES_STARTUP_THIS_AP           StartupThisAP;
  EFI_MP_SERVICES_SWITCH_BSP                SwitchBSP;
  EFI_MP_SERVICES_ENABLEDISABLEAP           EnableDisableAP;
  EFI_MP_SERVICES_WHOAMI                    WhoAmI;
};
#pragma pack (pop)

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

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
