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

/** @file SbRun.c
    This file contains code for SouthBridge runtime
    protocol

*/

// Module specific Includes
#include <Uefi.h>
#include "Token.h"
#include <AmiDxeLib.h>
#include <Library/AmiChipsetRuntimeServiceLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Guid/Rtc.h>

// Produced Protocols
#include <Protocol/Metronome.h>
#include <Protocol/RealTimeClock.h>
#include <AmiCspLib.h>
#include <Library/PcdLib.h>
#include <Protocol/Reset.h>

#include <Guid/AmiResetSystemEvent.h>

//----------------------------------------------------------------------------
//          Variable Declaration
//----------------------------------------------------------------------------
EFI_EVENT gAmiSystemResetEvent;
static BOOLEAN gExitBs = FALSE;

// Function Prototypes
EFI_STATUS
WaitForTick (
    IN  EFI_METRONOME_ARCH_PROTOCOL     *This,
    IN  UINT32                          TickNumber
);

// Architectural Protocol Definitions
EFI_METRONOME_ARCH_PROTOCOL mMetronomeProtocol = {
    WaitForTick,
    //
    // The period of platform's known time source in 100 ns units. This value on any
    // platform must not exceed 200 us. The value in this field is a constant that must not be
    // modified after the Metronome architectural protocol is installed. All consumers must
    // treat this as a read-only field.
    // 1 = 100ns/100ns
    //
    TICK_PERIOD
};

// Function Definitions

//----------------------------------------------------------------------------
//   USUALLY NO PORTING REQUIRED FOR THE FOLLOWING ROUTINES
//----------------------------------------------------------------------------

/**
    This function calculates the time needed to delay and then
    calls a library function to delay that amount of time

    @param This Pointer to the instance of
        the Metronome Arch Protocol
    @param TickNumber Number of ticks needed based off of tick period
        defined in Protocol Definiton

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/

EFI_STATUS
WaitForTick (
    IN  EFI_METRONOME_ARCH_PROTOCOL     *This,
    IN  UINT32                          TickNumber
    )
{
    EFI_STATUS          Status;
    UINT32              TotalTime;

    // Manipulate TickNumber into a valid value for the library function call
    // the Current Resolution is 10us.
    // The Library uses Microseconds to count delayed time.
    TotalTime = (TickNumber * This->TickPeriod) / 10;

    // Make Library Function call here
    Status = CountTime( TotalTime, PcdGet16 (AmiPcdAcpiIoPortBaseAddress) );

    return Status;
}

/**
    This function is the interface for the reset function.

    @param ResetType - Type of reset to perform
    @param ResetStatus - System status that caused the reset.  if part
                         of normal operation then this should be
                         EFI_SUCCESS, Otherwise it should reflect the
                         state of the system that caused it
    @param DataSize - Size in bytes of the data to be logged
    @param ResetData - Pointer to the data buffer that is to be logged

    @retval None, Even though it should never get that far

**/
EFI_STATUS
AmiChipsetRuntimeResetSystem (
    IN EFI_RESET_TYPE   ResetType,
    IN EFI_STATUS       ResetStatus,
    IN UINTN            DataSize,
    IN CHAR16           *ResetData OPTIONAL
    )
{
    EFI_STATUS              Status;
    EFI_TPL                 OldTpl;

    if (!gExitBs) {
      //
      // Signal AmiResetSystem Event
      //
      gBS->SignalEvent(gAmiSystemResetEvent);
      
      OldTpl = gBS->RaiseTPL(TPL_HIGH_LEVEL);
      if (OldTpl > TPL_APPLICATION) {
        gBS->RestoreTPL(TPL_APPLICATION);
        gBS->RaiseTPL(OldTpl);
      } else {
        gBS->RestoreTPL(OldTpl);
      }	

      gBS->CloseEvent(gAmiSystemResetEvent);
    }

    Status = AmiChipsetResetSystem (ResetType, ResetStatus, DataSize, ResetData);

    // This should not get here
    return Status;
}

/**
    Submit runtime services both SMM and runtime.

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

              
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
SbRuntimeServiceInit (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
    gRT->ResetSystem    = AmiChipsetRuntimeResetSystem;
    gRT->GetTime        = AmiChipsetGetTime;
    gRT->SetTime        = AmiChipsetSetTime;
    gRT->GetWakeupTime  = AmiChipsetGetWakeupTime;
    gRT->SetWakeupTime  = AmiChipsetSetWakeupTime;

    return EFI_SUCCESS;
}

/**
    A dummy function.

    @param Event   Event of callback
    @param Context Pointer to context of callback

    @retval VOID

**/
VOID SbRunDummyFunction (
    IN EFI_EVENT  Event,
    IN VOID       *Context
    )
{
}

/**
    Update the global variable ExitBs before exiting boot services.

    @param Event   Event of callback
    @param Context Pointer to context of callback

    @retval VOID

**/

VOID SbExitBs (
    IN EFI_EVENT  Event,
    IN VOID       *Context
    )
{
    gExitBs = TRUE;
}

/**
    This function is the entry point for this DXE. This function
    installs the runtime services related to SB

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
EFIAPI
SbRuntimeInitEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{

    EFI_STATUS      Status = EFI_SUCCESS;
    EFI_HANDLE      Handle = NULL;
    EFI_EVENT       ExitBsEvent;

    InitAmiRuntimeLib(ImageHandle, SystemTable, NULL, NULL);
    PROGRESS_CODE(DXE_SBRUN_INIT);

    // CspLib PM Specific function to check and Report
    // CMOS Battary and Power Supply Power loss/failure
    CspLibCheckPowerLoss();

    Status = SbRuntimeServiceInit(ImageHandle, SystemTable);
    ASSERT_EFI_ERROR(Status);

    Status = gBS->InstallProtocolInterface (
                    &ImageHandle, \
                    &gEfiMetronomeArchProtocolGuid, \
                    EFI_NATIVE_INTERFACE, \
                    &mMetronomeProtocol
                    );
    ASSERT_EFI_ERROR(Status);

    Status = gBS->InstallProtocolInterface (
                                    &Handle,
                                    &gEfiResetArchProtocolGuid,
                                    EFI_NATIVE_INTERFACE,
                                    NULL);
    ASSERT_EFI_ERROR(Status);
    //
    // Create the event for AmiResetSystem
    //
    Status = gBS->CreateEventEx(
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    SbRunDummyFunction,
                    NULL,
                    &gAmiResetSystemEventGuid,
                    &gAmiSystemResetEvent
                    );
    //
    // Do not signal AmiResetSystem Event while it is failed
    // to create the event for AmiResetSystem.
    //
    if (EFI_ERROR (Status)) {
      gExitBs = TRUE;
    }
    //
    // Update the global variable ExitBs before exiting boot services.
    //
    Status = gBS->CreateEvent(
                    EVT_SIGNAL_EXIT_BOOT_SERVICES,
                    TPL_CALLBACK,
                    SbExitBs,
                    NULL,
                    &ExitBsEvent
                    );
    //
    // Do not signal AmiResetSystem Event while it is failed
    // to update the global variable ExitBs.
    //
    if (EFI_ERROR (Status)) {
      gExitBs = TRUE;
    }
    //
    // Read "Register C - Flag Register" to clear "Alarm Flag"
    //
    ReadCmos(RTC_REG_C_INDEX);
    //
    // This protocol is to notify core that the Runtime Table has been
    // updated, so it can update the runtime table CRC.
    //
    Handle = NULL;
    return gBS->InstallMultipleProtocolInterfaces (
                  &Handle, \
                  &gEfiRealTimeClockArchProtocolGuid, \
                  NULL, \
                  NULL
                  );
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
