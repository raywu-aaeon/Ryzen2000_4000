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

/** @file AmiHpetTimer.c
    This file contains code for Template Hpet Timer initialization
    in the DXE stage

*/

// Module specific Includes
#include <PiDxe.h>

#include <Protocol/Cpu.h>
#include <Protocol/Timer.h>

#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/LocalApicLib.h>
#include <Protocol/AmiHpetTimer.h>
#include <Token.h>
#include <AmiLib.h>
#include <Sb.h>
#include <Library/SbCspLib.h>
#include <Library/UefiLib.h>
#include <Library/AmiTimerIntLib.h>

static BOOLEAN HpetMsiEnable = FixedPcdGetBool (AmiPcdHpetMsiEnable);

VOID
EFIAPI
IoApicEnableInterrupt (
  IN UINTN    Irq,
  IN BOOLEAN  Enable
  );

VOID
EFIAPI
IoApicConfigureInterrupt (
  IN UINTN    Irq,
  IN UINTN    Vector,
  IN UINTN    DeliveryMode,
  IN BOOLEAN  LevelTriggered,
  IN BOOLEAN  AssertionLevel
  );

EFI_STATUS
EFIAPI
TimerRegisterHandler (
  IN EFI_TIMER_ARCH_PROTOCOL  *This,
  IN EFI_TIMER_NOTIFY         NotifyFunction
  );

EFI_STATUS
EFIAPI
SetTimerPeriod (
  IN EFI_TIMER_ARCH_PROTOCOL  *This,
  IN UINT64                   TimerPeriod
  );

EFI_STATUS
EFIAPI
GetTimerPeriod (
  IN EFI_TIMER_ARCH_PROTOCOL   *This,
  OUT UINT64                   *TimerPeriod
  );

EFI_STATUS
EFIAPI
GenerateSoftIntr (
  IN EFI_TIMER_ARCH_PROTOCOL  *This
  );
  
//
// The Timer Architectural Protocol that this driver produces.
//
EFI_TIMER_ARCH_PROTOCOL  mTimer = {
    TimerRegisterHandler,
    SetTimerPeriod,
    GetTimerPeriod,
    GenerateSoftIntr
};

//
// The notification function to call on every timer interrupt.
//
EFI_TIMER_NOTIFY  mTimerNotifyFunction = NULL;

//
// The current period of the HPET timer interrupt in 100 ns units.
//
UINT64  mTimerPeriod = 0;

//
// The number of HPET timer ticks required for the current HPET rate specified by mTimerPeriod.
//
UINT64  mTimerCount;

//
// Mask used for counter and comparator calculations to adjust for a 32-bit or 64-bit counter.
//
UINT64  mCounterMask;

//
// The HPET main counter value from the most recent HPET timer interrupt.
//
volatile UINT64  mPreviousMainCounter;

volatile UINT64  mPreviousComparator;

//
// The index of the HPET timer being managed by this driver.
//
UINTN  mTimerIndex;

//
// The I/O APIC IRQ that the HPET Timer is mapped if I/O APIC mode is used.
//
UINT32  mTimerIrq;

//
// Cached state of the HPET General Capabilities register managed by this driver.
// Caching the state reduces the number of times the configuration register is read.
//
HPET_GENERAL_CAPABILITIES_ID_REGISTER  mHpetGeneralCapabilities;

//
// Cached state of the HPET General Configuration register managed by this driver.
// Caching the state reduces the number of times the configuration register is read.
//
HPET_GENERAL_CONFIGURATION_REGISTER  mHpetGeneralConfiguration;

//
// Cached state of the Configuration register for the HPET Timer managed by 
// this driver.  Caching the state reduces the number of times the configuration
// register is read.
//
HPET_TIMER_CONFIGURATION_REGISTER  mTimerConfiguration;

//
// Counts the number of HPET Timer interrupts processed by this driver.
// Only required for debug.
//
volatile UINTN  mNumTicks;

EFI_EVENT gRegisterRestoreEvent;

//
// List of HPET registers that need to save/restore on AMD platform
//
UINT64  mHpet_0x010 = 0;
UINT64  mHpet_0x100 = 0;
UINT64  mHpet_0x108 = 0;
UINT64  mHpet_0x1B0 = 0;
UINT64  mHpet_0x1B8 = 0;


/**
  Read a 64-bit register from the HPET

  @param  Offset  Specifies the offset of the HPET register to read.

  @return  The 64-bit value read from the HPET register specified by Offset.
**/
UINT64
HpetRead (
  IN UINTN  Offset
  )
{
  return MmioRead64 (HPET_BASE_ADDRESS + Offset);
}

/**
  Write a 64-bit HPET register.

  @param  Offset  Specifies the ofsfert of the HPET register to write.
  @param  Value   Specifies the value to write to the HPET register specified by Offset.

  @return  The 64-bit value written to HPET register specified by Offset.
**/
UINT64
HpetWrite (
  IN UINTN   Offset,
  IN UINT64  Value
  )
{
  return MmioWrite64 (HPET_BASE_ADDRESS + Offset, Value);
}

/**
  Enable or disable the main counter in the HPET Timer.

  @param  Enable  If TRUE, then enable the main counter in the HPET Timer.
                  If FALSE, then disable the main counter in the HPET Timer.
**/
VOID
HpetEnable (
  IN BOOLEAN  Enable
  )
{
  mHpetGeneralConfiguration.Bits.MainCounterEnable = Enable ? 1 : 0;  
  HpetWrite (HPET_GENERAL_CONFIGURATION_OFFSET, mHpetGeneralConfiguration.Uint64);
}

/**
  Restore registers value saved in timer interrupt routine.
  
  @param  Event    The instance of EFI_EVENT.
  @param  Context  The parameter passed in.
**/
VOID
EFIAPI
RegisterRestoreCallBack (
  IN  EFI_EVENT  Event,
  IN  VOID       *Context
  )
{
  SaveRestoreRegisters(FALSE);
}

/**
  The interrupt handler for the HPET timer.  This handler clears the HPET interrupt
  and computes the amount of time that has passed since the last HPET timer interrupt.
  If a notification function is registered, then the amount of time since the last
  HPET interrupt is passed to that notification function in 100 ns units.  The HPET
  time is updated to generate another interrupt in the required time period. 

  @param  InterruptType  The type of interrupt that occured.
  @param  SystemContext  A pointer to the system context when the interrupt occured.
**/
VOID
EFIAPI
TimerInterruptHandler (
  IN EFI_EXCEPTION_TYPE   InterruptType,
  IN EFI_SYSTEM_CONTEXT   SystemContext
  )
{
  UINT64                  MainCounter;
  UINT64                  Comparator;
  UINT64                  TimerPeriod;
  UINT64                  Delta;
  EFI_TPL                 CurrentTpl;

  //
  // Count number of ticks
  //
  // unreadVariable warning happened under MARCO "DEBUG_CODE"(\MdePkg\Include\Library\DebugLib.h)
  // cppcheck-suppress unreadVariable
  DEBUG_CODE (mNumTicks++;);

  SaveRestoreRegisters(TRUE);

  //
  // Clear HPET timer interrupt status
  //
  HpetWrite (HPET_GENERAL_INTERRUPT_STATUS_OFFSET, LShiftU64 (HPET_APIC_LEVEL_TRIGGER, mTimerIndex));

  //
  // Local APIC EOI
  //
  SendApicEoi ();

  //
  // Disable HPET timer when adjusting the COMPARATOR value to prevent a missed interrupt
  //
  HpetEnable (FALSE);
  
  //
  // Capture main counter value
  //
  MainCounter = HpetRead (HPET_MAIN_COUNTER_OFFSET);

  //
  // Get the previous comparator counter
  //
  mPreviousComparator = HpetRead (HPET_TIMER_COMPARATOR_OFFSET + mTimerIndex * HPET_TIMER_STRIDE);

  //
  // Set HPET COMPARATOR to the value required for the next timer tick
  //
  Comparator = (mPreviousComparator + mTimerCount) & mCounterMask;

  if ((mPreviousMainCounter < MainCounter) && (mPreviousComparator > Comparator)) {
    //
    // When comparator overflows
    //
    HpetWrite (HPET_TIMER_COMPARATOR_OFFSET + mTimerIndex * HPET_TIMER_STRIDE, Comparator);
  } else if ((mPreviousMainCounter > MainCounter) && (mPreviousComparator < Comparator)) {
    //
    // When main counter overflows
    //
    HpetWrite (HPET_TIMER_COMPARATOR_OFFSET + mTimerIndex * HPET_TIMER_STRIDE, (MainCounter + mTimerCount) & mCounterMask);
  } else {
    //
    // When both main counter and comparator do not overflow or both do overflow
    //
    if (Comparator > MainCounter) {
      HpetWrite (HPET_TIMER_COMPARATOR_OFFSET + mTimerIndex * HPET_TIMER_STRIDE, Comparator);
    } else {
      HpetWrite (HPET_TIMER_COMPARATOR_OFFSET + mTimerIndex * HPET_TIMER_STRIDE, (MainCounter + mTimerCount) & mCounterMask);
    }
  }

  //
  // Enable the HPET counter once the new COMPARATOR value has been set.
  //
  HpetEnable (TRUE);
  
  //
  // Check to see if there is a registered notification function
  //
  if (mTimerNotifyFunction != NULL) {
    //
    // Compute time since last notification in 100 ns units (10 ^ -7) 
    //
    if (MainCounter > mPreviousMainCounter) {
      //
      // Main counter does not overflow
      //
      Delta = MainCounter - mPreviousMainCounter;
    } else {
      //
      // Main counter overflows, first usb, then add
      //
      Delta = (mCounterMask - mPreviousMainCounter) + MainCounter;
    }
    TimerPeriod = DivU64x32 (
                    MultU64x32 (
                      Delta & mCounterMask,
                      mHpetGeneralCapabilities.Bits.CounterClockPeriod
                      ), 
                    100000000
                    );
                    
    //
    // Call registered notification function passing in the time since the last
    // interrupt in 100 ns units.
    //    
    mTimerNotifyFunction (TimerPeriod);
  }
  
  //
  // The user's EVT_TIMER is not within TimerInterruptHandler.
  // If CurrentTpl is greater than TPL_NOTIFY, the user's EVT_TIMER will haven't
  // been executed yet.
  // Signal gRegisterRestoreEvent to restore the register in RegisterRestoreCallBack()
  // after user's event.
  //
  CurrentTpl = EfiGetCurrentTpl();
  if (CurrentTpl > TPL_NOTIFY) {
    gBS->SignalEvent (gRegisterRestoreEvent);
  } else {  
    SaveRestoreRegisters(FALSE);
  }

  //
  // Save main counter value
  //
  mPreviousMainCounter = MainCounter;
}

/**
    This function registers a handler that is called every time the
    timer interrupt fires

    @param This - Pointer to the instance of the 
                  Architectural Protocol
    @param NotifyFunction - The function to call when the interrupt fires

    @retval EFI_SUCCESS new handle registered
    @retval EFI_ALREADY_STARTED if Notify function is already defined

**/
EFI_STATUS
EFIAPI
TimerRegisterHandler (
  IN EFI_TIMER_ARCH_PROTOCOL  *This,
  IN EFI_TIMER_NOTIFY         NotifyFunction
  )
{
  //
  // Check for invalid parameters
  //
  if (NotifyFunction == NULL && mTimerNotifyFunction == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  if (NotifyFunction != NULL && mTimerNotifyFunction != NULL) {
    return EFI_ALREADY_STARTED;
  }

  //
  // Cache the registered notification function
  //
  mTimerNotifyFunction = NotifyFunction;

  return EFI_SUCCESS;
}

/**
    This function will restore HPET related registers as hardware default if TimerPeriod is 0

    @param VOID

    @retval VOID

**/
VOID
RestoreHpetRegisters()
{
    HpetWrite(0x010, mHpet_0x010);
    HpetWrite(0x100, mHpet_0x100);
    HpetWrite(0x108, mHpet_0x108);
    HpetWrite(0x1B0, mHpet_0x1B0);
    HpetWrite(0x1B8, mHpet_0x1B8);
}

/**
    This function sets the timer to create an Interrupt on IRQ0
    every TimerPeriod number of 100ns intervals

    @param This - Pointer to the instance of the Architectural Protocol
    @param TimerPeriod - The number of 100ns intervals to which the timer
                         will be programmed. This value will be rounded up 
                         to the nearest timer interval

    @retval EFI_SUCCESS

**/
EFI_STATUS
EFIAPI
SetTimerPeriod (
  IN EFI_TIMER_ARCH_PROTOCOL  *This,
  IN UINT64                   TimerPeriod
  )
{
  EFI_TPL                        Tpl;
  UINT64                         MainCounter;
  UINT64                         Delta;
  UINT64                         CurrentComparator;
  HPET_TIMER_MSI_ROUTE_REGISTER  HpetTimerMsiRoute;

  //
  // Disable interrupts
  //
  Tpl = gBS->RaiseTPL (TPL_HIGH_LEVEL);

  //
  // Disable HPET timer when adjusting the timer period
  //
  HpetEnable (FALSE);
  
  if (TimerPeriod == 0) {
    if (mTimerPeriod != 0) {
      //
      // Check if there is possibly a pending interrupt
      //
      MainCounter = HpetRead (HPET_MAIN_COUNTER_OFFSET);
      if (MainCounter < mPreviousMainCounter) {
        Delta = (mCounterMask - mPreviousMainCounter) + MainCounter;
      } else { 
        Delta = MainCounter - mPreviousMainCounter;
      }
      if ((Delta & mCounterMask) >= mTimerCount) {
        //
        // Interrupt still happens after disable HPET, wait to be processed
        // Wait until interrupt is processed and comparator is increased
        //
        CurrentComparator = HpetRead (HPET_TIMER_COMPARATOR_OFFSET + mTimerIndex * HPET_TIMER_STRIDE);
        while (CurrentComparator == mPreviousComparator) {
          CurrentComparator = HpetRead (HPET_TIMER_COMPARATOR_OFFSET + mTimerIndex * HPET_TIMER_STRIDE);
          CpuPause();
        }
      }
    }

    //
    // If TimerPeriod is 0, then mask HPET Timer interrupts
    //
    // cppcheck-suppress knownConditionTrueFalse  
    if (mTimerConfiguration.Bits.MsiInterruptCapablity != 0 && HpetMsiEnable) {
      //
      // Disable HPET MSI interrupt generation
      //
      mTimerConfiguration.Bits.MsiInterruptEnable = 0;
    } else {
      //
      // Disable I/O APIC Interrupt
      //
      IoApicEnableInterrupt (mTimerIrq, FALSE);
    }
    
    //
    // Disable HPET timer interrupt 
    //
    mTimerConfiguration.Bits.InterruptEnable = 0;
    HpetWrite (HPET_TIMER_CONFIGURATION_OFFSET + mTimerIndex * HPET_TIMER_STRIDE, mTimerConfiguration.Uint64);
  } else {
    //
    // Convert TimerPeriod to femtoseconds and divide by the number if femtoseconds 
    // per tick of the HPET counter to determine the number of HPET counter ticks
    // in TimerPeriod 100 ns units.
    // 
    mTimerCount = DivU64x32 (
                    MultU64x32 (TimerPeriod, 100000000),
                    mHpetGeneralCapabilities.Bits.CounterClockPeriod
                    );

    //
    // Program the HPET Comparator with the number of ticks till the next interrupt
    //
    MainCounter = HpetRead (HPET_MAIN_COUNTER_OFFSET);
    if (MainCounter > mPreviousMainCounter) {
      Delta = MainCounter - mPreviousMainCounter;
    } else { 
      Delta = (mCounterMask - mPreviousMainCounter) + MainCounter;
    }
    if ((Delta & mCounterMask) >= mTimerCount) {
      HpetWrite (HPET_TIMER_COMPARATOR_OFFSET + mTimerIndex * HPET_TIMER_STRIDE, (MainCounter + 1) & mCounterMask);
    } else {  
      HpetWrite (HPET_TIMER_COMPARATOR_OFFSET + mTimerIndex * HPET_TIMER_STRIDE, (mPreviousMainCounter + mTimerCount) & mCounterMask);
    }
    
    //
    // Enable HPET Timer interrupt generation
    //
    // cppcheck-suppress knownConditionTrueFalse  
    if (mTimerConfiguration.Bits.MsiInterruptCapablity != 0 && HpetMsiEnable) {
      //
      // Program MSI Address and MSI Data values in the selected HPET Timer
      // Program HPET register with APIC ID of current BSP in case BSP has been switched
      //
      HpetTimerMsiRoute.Bits.Address = GetApicMsiAddress ();
      HpetTimerMsiRoute.Bits.Value   = (UINT32)GetApicMsiValue (MASTER_INTERRUPT_BASE + HPET_APIC_INTERRUPT_PIN, LOCAL_APIC_DELIVERY_MODE_LOWEST_PRIORITY, FALSE, FALSE);
      HpetWrite (HPET_TIMER_MSI_ROUTE_OFFSET + mTimerIndex * HPET_TIMER_STRIDE, HpetTimerMsiRoute.Uint64);
      //
      // Enable HPET MSI Interrupt
      //
      mTimerConfiguration.Bits.MsiInterruptEnable = 1;
    } else {
      //
      // Enable timer interrupt through I/O APIC
      // Program IOAPIC register with APIC ID of current BSP in case BSP has been switched
      //
      IoApicConfigureInterrupt (mTimerIrq, MASTER_INTERRUPT_BASE + HPET_APIC_INTERRUPT_PIN, HPET_APIC_DELIVERY_MODE, (HPET_APIC_LEVEL_TRIGGER == 1) ? TRUE : FALSE, (HPET_INTERRUPT_POLARITY == 0) ? TRUE : FALSE);
      IoApicEnableInterrupt (mTimerIrq, TRUE);
    }

    //
    // Enable HPET Interrupt Generation
    //
    mTimerConfiguration.Bits.InterruptEnable = 1;
    HpetWrite (HPET_TIMER_CONFIGURATION_OFFSET + mTimerIndex * HPET_TIMER_STRIDE, mTimerConfiguration.Uint64);
  }
    
  //
  // Save the new timer period
  //
  mTimerPeriod = TimerPeriod;

  //
  // Enable the HPET counter once new timer period has been established
  // The HPET counter should run even if the HPET Timer interrupts are
  // disabled.  This is used to account for time passed while the interrupt
  // is disabled.
  //
  HpetEnable (TRUE);
 
  //
  // Due to AMD BTS utility will check HPET related register under OS.
  // Restore hardware default value for passing the test.
  //
  if (TimerPeriod == 0) RestoreHpetRegisters();

  //
  // Restore interrupts
  //
  gBS->RestoreTPL (Tpl);

  return EFI_SUCCESS;
}

/**
    This function returns the current timer period

    @param This - Pointer to the instance of the Architectural Protocol
    @param TimerPeriod - pointer to a memory location to load the current
                         Timer period into

    @retval EFI_STATUS

**/
EFI_STATUS
EFIAPI
GetTimerPeriod (
  IN EFI_TIMER_ARCH_PROTOCOL   *This,
  OUT UINT64                   *TimerPeriod
  )
{
  if (TimerPeriod == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  *TimerPeriod = mTimerPeriod;

  return EFI_SUCCESS;
}

/**
    This function generates a soft timer interrupt

    @param This - Pointer to the instance of the Architectural Protocol

    @retval  EFI_SUCCESS       The soft timer interrupt was generated.
    @retval  EFI_UNSUPPORTED   The platform does not support the generation of soft
                               timer interrupts.

**/
EFI_STATUS
EFIAPI
GenerateSoftIntr (
  IN EFI_TIMER_ARCH_PROTOCOL  *This
  )
{
  UINT64   MainCounter;
  EFI_TPL  Tpl;
  UINT64   TimerPeriod;
  UINT64   Delta;

  //
  // Disable interrupts
  //  
  Tpl = gBS->RaiseTPL (TPL_HIGH_LEVEL);
  
  //
  // Capture main counter value
  //
  MainCounter = HpetRead (HPET_MAIN_COUNTER_OFFSET);

  //
  // Check to see if there is a registered notification function
  //
  if (mTimerNotifyFunction != NULL) {
    //
    // Compute time since last interrupt in 100 ns units (10 ^ -7) 
    //
    if (MainCounter > mPreviousMainCounter) {
      //
      // Main counter does not overflow
      //
      Delta = MainCounter - mPreviousMainCounter;
    } else {
      //
      // Main counter overflows, first usb, then add
      //
      Delta = (mCounterMask - mPreviousMainCounter) + MainCounter;
    }

    TimerPeriod = DivU64x32 (
                    MultU64x32 (
                      Delta & mCounterMask,
                      mHpetGeneralCapabilities.Bits.CounterClockPeriod
                      ), 
                    100000000
                    );
                    
    //
    // Call registered notification function passing in the time since the last
    // interrupt in 100 ns units.
    //    
    mTimerNotifyFunction (TimerPeriod);
  }

  //
  // Save main counter value
  //
  mPreviousMainCounter = MainCounter;
  
  //
  // Restore interrupts
  //  
  gBS->RestoreTPL (Tpl);
  
  return EFI_SUCCESS;
}

/**
    This function will save HPET related registers

    @param VOID

    @retval VOID

**/
VOID
SaveHpetRegisters()
{
    mHpet_0x010 = HpetRead(0x010);
    mHpet_0x100 = HpetRead(0x100);
    mHpet_0x108 = HpetRead(0x108);
    mHpet_0x1B0 = HpetRead(0x1B0);
    mHpet_0x1B8 = HpetRead(0x1B8);
}

/**
  Initialize the Timer Architectural Protocol driver

  @param  ImageHandle  ImageHandle of the loaded driver
  @param  SystemTable  Pointer to the System Table

  @retval  EFI_SUCCESS           Timer Architectural Protocol created
  @retval  EFI_OUT_OF_RESOURCES  Not enough resources available to initialize driver.
  @retval  EFI_DEVICE_ERROR      A device error occured attempting to initialize the driver.

**/
EFI_STATUS
EFIAPI
AmiHpetTimerInitialize (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                             Status;
  EFI_CPU_ARCH_PROTOCOL                  *Cpu = NULL;
  UINTN                                  TimerIndex;
  UINTN                                  MsiTimerIndex;
  HPET_TIMER_MSI_ROUTE_REGISTER          HpetTimerMsiRoute;
  EFI_HANDLE                             TimerHandle = NULL;

  DEBUG ((DEBUG_INFO, "AmiHpetTimerInitialize() ..\n"));

  //
  // Save Hpet hardware default status
  //
  SaveHpetRegisters();

  //
  // Make sure the Timer Architectural Protocol is not already installed in the system
  //
  ASSERT_PROTOCOL_ALREADY_INSTALLED (NULL, &gEfiTimerArchProtocolGuid);

  //
  // Find the CPU architectural protocol.
  //
  Status = gBS->LocateProtocol (&gEfiCpuArchProtocolGuid, NULL, (VOID **) &Cpu);
  ASSERT_EFI_ERROR (Status);

  //
  // Retrieve HPET Capabilities and Configuration Information
  //  
  mHpetGeneralCapabilities.Uint64  = HpetRead (HPET_GENERAL_CAPABILITIES_ID_OFFSET);
  mHpetGeneralConfiguration.Uint64 = HpetRead (HPET_GENERAL_CONFIGURATION_OFFSET);
 
  //
  // If Revision is not valid, then ASSERT() and unload the driver because the HPET 
  // device is not present.
  //  
  ASSERT (mHpetGeneralCapabilities.Uint64 != 0);
  ASSERT (mHpetGeneralCapabilities.Uint64 != 0xFFFFFFFFFFFFFFFFULL);
  if (mHpetGeneralCapabilities.Uint64 == 0 || mHpetGeneralCapabilities.Uint64 == 0xFFFFFFFFFFFFFFFFULL) {
    DEBUG ((DEBUG_ERROR, "HPET device is not present.  Unload HPET driver.\n"));
    return EFI_DEVICE_ERROR;
  }

  //
  // Force the HPET timer to be disabled while setting everything up
  //
  HpetEnable (FALSE);

  //
  // Dump HPET Configuration Information
  //  
  // unreadVariable warning happened under MARCO "DEBUG_CODE"(\MdePkg\Include\Library\DebugLib.h)
  // cppcheck-suppress unreadVariable
  DEBUG_CODE (
    DEBUG ((DEBUG_INFO, "HPET Base Address = 0x%08x\n", HPET_BASE_ADDRESS));
    DEBUG ((DEBUG_INFO, "  HPET_GENERAL_CAPABILITIES_ID  = 0x%016lx\n", mHpetGeneralCapabilities));
    DEBUG ((DEBUG_INFO, "  HPET_GENERAL_CONFIGURATION    = 0x%016lx\n", mHpetGeneralConfiguration.Uint64));
    DEBUG ((DEBUG_INFO, "  HPET_GENERAL_INTERRUPT_STATUS = 0x%016lx\n", HpetRead (HPET_GENERAL_INTERRUPT_STATUS_OFFSET)));
    DEBUG ((DEBUG_INFO, "  HPET_MAIN_COUNTER             = 0x%016lx\n", HpetRead (HPET_MAIN_COUNTER_OFFSET)));
    DEBUG ((DEBUG_INFO, "  HPET Main Counter Period      = %d (fs)\n", mHpetGeneralCapabilities.Bits.CounterClockPeriod));
    for (TimerIndex = 0; TimerIndex <= mHpetGeneralCapabilities.Bits.NumberOfTimers; TimerIndex++) {
      DEBUG ((DEBUG_INFO, "  HPET_TIMER%d_CONFIGURATION     = 0x%016lx\n", TimerIndex, HpetRead (HPET_TIMER_CONFIGURATION_OFFSET + TimerIndex * HPET_TIMER_STRIDE)));
      DEBUG ((DEBUG_INFO, "  HPET_TIMER%d_COMPARATOR        = 0x%016lx\n", TimerIndex, HpetRead (HPET_TIMER_COMPARATOR_OFFSET    + TimerIndex * HPET_TIMER_STRIDE)));
      DEBUG ((DEBUG_INFO, "  HPET_TIMER%d_MSI_ROUTE         = 0x%016lx\n", TimerIndex, HpetRead (HPET_TIMER_MSI_ROUTE_OFFSET     + TimerIndex * HPET_TIMER_STRIDE)));
    }
  );
  
  //
  // Capture the current HPET main counter value.
  //
  mPreviousMainCounter = HpetRead (HPET_MAIN_COUNTER_OFFSET);
  
  //
  // Determine the interrupt mode to use for the HPET Timer.  
  // Look for MSI first, then unused PIC mode interrupt, then I/O APIC mode interrupt
  //  
  MsiTimerIndex = HPET_INVALID_TIMER_INDEX;
  mTimerIndex   = HPET_INVALID_TIMER_INDEX;
  for (TimerIndex = 0; TimerIndex <= mHpetGeneralCapabilities.Bits.NumberOfTimers; TimerIndex++) {
    //
    // Read the HPET Timer Capabilities and Configuration register
    //
    mTimerConfiguration.Uint64 = HpetRead (HPET_TIMER_CONFIGURATION_OFFSET + TimerIndex * HPET_TIMER_STRIDE);
    
    //
    // Check to see if this HPET Timer supports MSI 
    //
    if (mTimerConfiguration.Bits.MsiInterruptCapablity != 0) {
      //
      // Save the index of the first HPET Timer that supports MSI interrupts
      //
      if (MsiTimerIndex == HPET_INVALID_TIMER_INDEX) {
        MsiTimerIndex = TimerIndex;
      }
    }
    
    //
    // Check to see if this HPET Timer supports I/O APIC interrupts
    //
    if (mTimerConfiguration.Bits.InterruptRouteCapability != 0) {
      //
      // Save the index of the first HPET Timer that supports I/O APIC interrupts
      //
      if (mTimerIndex == HPET_INVALID_TIMER_INDEX) {
        mTimerIndex = TimerIndex;
        mTimerIrq   = (UINT32)LowBitSet32 (mTimerConfiguration.Bits.InterruptRouteCapability);
      }
    }
  }
  // cppcheck-suppress knownConditionTrueFalse  
  if (HpetMsiEnable && MsiTimerIndex != HPET_INVALID_TIMER_INDEX) {
    //
    // Use MSI interrupt if supported
    //
    mTimerIndex  = MsiTimerIndex;

    //
    // Program MSI Address and MSI Data values in the selected HPET Timer
    //
    HpetTimerMsiRoute.Bits.Address = GetApicMsiAddress ();
    HpetTimerMsiRoute.Bits.Value   = (UINT32)GetApicMsiValue (MASTER_INTERRUPT_BASE + HPET_APIC_INTERRUPT_PIN, LOCAL_APIC_DELIVERY_MODE_LOWEST_PRIORITY, FALSE, FALSE);
    HpetWrite (HPET_TIMER_MSI_ROUTE_OFFSET + mTimerIndex * HPET_TIMER_STRIDE, HpetTimerMsiRoute.Uint64);

    //
    // Read the HPET Timer Capabilities and Configuration register and initialize for MSI mode
    //   Clear LevelTriggeredInterrupt to use edge triggered interrupts when in MSI mode
    //
    mTimerConfiguration.Uint64 = HpetRead (HPET_TIMER_CONFIGURATION_OFFSET + mTimerIndex * HPET_TIMER_STRIDE);
    mTimerConfiguration.Bits.LevelTriggeredInterrupt = 0;
  } else {
    //
    // If no HPET timers support MSI or I/O APIC modes, then ASSERT() and unload the driver.
    //
    ASSERT (mTimerIndex != HPET_INVALID_TIMER_INDEX);
    if (mTimerIndex == HPET_INVALID_TIMER_INDEX) {
      DEBUG ((DEBUG_ERROR, "No HPET timers support MSI or I/O APIC mode.  Unload HPET driver.\n"));
      return EFI_DEVICE_ERROR;
    }
    
    //
    // Initialize I/O APIC entry for HPET Timer Interrupt
    //   Fixed Delivery Mode, Level Triggered, Asserted Low
    //
    IoApicConfigureInterrupt (mTimerIrq, MASTER_INTERRUPT_BASE + HPET_APIC_INTERRUPT_PIN, HPET_APIC_DELIVERY_MODE, (HPET_APIC_LEVEL_TRIGGER == 1) ? TRUE : FALSE, (HPET_INTERRUPT_POLARITY == 0) ? TRUE : FALSE);

    //
    // Read the HPET Timer Capabilities and Configuration register and initialize for I/O APIC mode
    //   Clear MsiInterruptCapability to force rest of driver to use I/O APIC mode
    //   Set LevelTriggeredInterrupt to use level triggered interrupts when in I/O APIC mode
    //   Set InterruptRoute field based in mTimerIrq
    //
    mTimerConfiguration.Uint64 = HpetRead (HPET_TIMER_CONFIGURATION_OFFSET + mTimerIndex * HPET_TIMER_STRIDE);
    mTimerConfiguration.Bits.LevelTriggeredInterrupt = HPET_APIC_LEVEL_TRIGGER;
    mTimerConfiguration.Bits.InterruptRoute          = mTimerIrq;
  }

  //
  // Configure the selected HPET Timer with settings common to both MSI mode and I/O APIC mode
  //   Clear InterruptEnable to keep interrupts disabled until full init is complete 
  //   Clear PeriodicInterruptEnable to use one-shot mode 
  //   Configure as a 32-bit counter  
  //
  mTimerConfiguration.Bits.InterruptEnable         = 0;
  mTimerConfiguration.Bits.PeriodicInterruptEnable = 0;
  mTimerConfiguration.Bits.CounterSizeEnable       = 1;
  HpetWrite (HPET_TIMER_CONFIGURATION_OFFSET + mTimerIndex * HPET_TIMER_STRIDE, mTimerConfiguration.Uint64);
  
  //
  // Read the HPET Timer Capabilities and Configuration register back again.
  // CounterSizeEnable will be read back as a 0 if it is a 32-bit only timer
  //
  mTimerConfiguration.Uint64 = HpetRead (HPET_TIMER_CONFIGURATION_OFFSET + mTimerIndex * HPET_TIMER_STRIDE);
  if ((mTimerConfiguration.Bits.CounterSizeEnable == 1) && (sizeof (UINTN) == sizeof (UINT64))) {
    DEBUG ((DEBUG_INFO, "Choose 64-bit HPET timer.\n"));
    //
    // 64-bit BIOS can use 64-bit HPET timer
    //
    mCounterMask = 0xffffffffffffffffULL;
    //
    // Set timer back to 64-bit
    //
    mTimerConfiguration.Bits.CounterSizeEnable = 0;
    HpetWrite (HPET_TIMER_CONFIGURATION_OFFSET + mTimerIndex * HPET_TIMER_STRIDE, mTimerConfiguration.Uint64);
  } else {
    DEBUG ((DEBUG_INFO, "Choose 32-bit HPET timer.\n"));
    mCounterMask = 0x00000000ffffffffULL;
  }

  //
  // Install interrupt handler for selected HPET Timer
  //
  Status = Cpu->RegisterInterruptHandler (Cpu, MASTER_INTERRUPT_BASE + HPET_APIC_INTERRUPT_PIN, TimerInterruptHandler);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Unable to register HPET interrupt with CPU Arch Protocol.  Unload HPET driver.\n"));
    return EFI_DEVICE_ERROR;
  }

  //
  // Force the HPET Timer to be enabled at its default period
  //
  Status = SetTimerPeriod (&mTimer, HPET_DEFAULT_TICK_DURATION);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Unable to set HPET default timer rate.  Unload HPET driver.\n"));
    return EFI_DEVICE_ERROR;
  }

  //
  // Show state of enabled HPET timer
  //
  // unreadVariable warning happened under MARCO "DEBUG_CODE"(\MdePkg\Include\Library\DebugLib.h)
  // cppcheck-suppress knownConditionTrueFalse
  // cppcheck-suppress unreadVariable
  
  DEBUG_CODE (         
    if (mTimerConfiguration.Bits.MsiInterruptCapablity != 0 && HpetMsiEnable) {
      DEBUG ((DEBUG_INFO, "HPET Interrupt Mode MSI\n"));
    } else {
      DEBUG ((DEBUG_INFO, "HPET Interrupt Mode I/O APIC\n"));
      DEBUG ((DEBUG_INFO, "HPET I/O APIC IRQ         = 0x%02x\n",  mTimerIrq));
    }  
    DEBUG ((DEBUG_INFO, "HPET Interrupt Vector     = 0x%02x\n",    MASTER_INTERRUPT_BASE + HPET_APIC_INTERRUPT_PIN));
    DEBUG ((DEBUG_INFO, "HPET Counter Mask         = 0x%016lx\n",  mCounterMask));
    DEBUG ((DEBUG_INFO, "HPET Timer Period         = %d\n",        mTimerPeriod));
    DEBUG ((DEBUG_INFO, "HPET Timer Count          = 0x%016lx\n",  mTimerCount));
    DEBUG ((DEBUG_INFO, "HPET_TIMER%d_CONFIGURATION = 0x%016lx\n", mTimerIndex, HpetRead (HPET_TIMER_CONFIGURATION_OFFSET + mTimerIndex * HPET_TIMER_STRIDE)));
    DEBUG ((DEBUG_INFO, "HPET_TIMER%d_COMPARATOR    = 0x%016lx\n", mTimerIndex, HpetRead (HPET_TIMER_COMPARATOR_OFFSET    + mTimerIndex * HPET_TIMER_STRIDE)));
    DEBUG ((DEBUG_INFO, "HPET_TIMER%d_MSI_ROUTE     = 0x%016lx\n", mTimerIndex, HpetRead (HPET_TIMER_MSI_ROUTE_OFFSET     + mTimerIndex * HPET_TIMER_STRIDE)));

    //
    // Wait for a few timer interrupts to fire before continuing
    // 
    while (mNumTicks < 10);
  );
 
  //
  // Install the Timer Architectural Protocol onto a new handle
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &TimerHandle,
                  &gEfiTimerArchProtocolGuid,
                  &mTimer,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->CreateEvent (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  RegisterRestoreCallBack,
                  NULL,
                  &gRegisterRestoreEvent
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
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
