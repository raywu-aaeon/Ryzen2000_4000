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

/** @file SbAmdNvramCriticalSectionLib.c
    Implementation of the AmiCriticalSectionLib library class.

*/
#include <Library/AmiCriticalSectionLib.h>
#include <AmiCspLib.h>
#include <AmiDxeLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/IoLib.h>
#include <Protocol/SmmBase2.h>
#include <Protocol/AmiHpetTimer.h>

extern BOOLEAN NvramSmmIsActive;

typedef struct{
	UINT32 Signature;
	BOOLEAN Busy;
    BOOLEAN SmiState;
    UINT8 IntState[2];
} CRITICAL_SECTION_INTERNAL;

#define CS_SIGNATURE SIGNATURE_32('_','C','S','_')

#define IS_INVALID_CRITICAL_SECTION(Cs) \
  ((Cs) == NULL || ((CRITICAL_SECTION_INTERNAL*)(Cs))->Signature!=CS_SIGNATURE)

static CRITICAL_SECTION_INTERNAL gCriticalSection = {
	CS_SIGNATURE, // UINT32 Signature;
	FALSE, // BOOLEAN Busy;
    FALSE, // BOOLEAN SmiState;
    {0,0} // UINT8 IntState[2];
};

static CRITICAL_SECTION_INTERNAL *gCriticalSectionPtr = NULL;

#if defined (HPET_PROTOCOL_SUPPORT) && (HPET_PROTOCOL_SUPPORT == 1)
static EFI_EVENT                       mRtHpetLibExitBootServiceEvent = NULL;
static EFI_EVENT                       mRtHpetLibVirtualAddressChangeEvent = NULL;
static BOOLEAN                         mInRunTime = FALSE;
static BOOLEAN                         mInSmm = FALSE;
static EFI_SMM_BASE2_PROTOCOL          *mSmmBase2 = NULL;
static EFI_SMM_SYSTEM_TABLE2           *mSmst;
volatile UINT8                         *mHpetBaseAddr = (UINT8*)(UINTN)HPET_BASE_ADDRESS;
HPET_GENERAL_CONFIGURATION_REGISTER    mOrigHpetGeneralConfigRegister;
#endif

#if defined (HPET_PROTOCOL_SUPPORT) && (HPET_PROTOCOL_SUPPORT == 1)
/**
  Enable the main counter in the HPET Timer.

  @param  Enable  If TRUE, then enable the main counter in the HPET Timer.
                  If FALSE, then disable the main counter in the HPET Timer.
**/
VOID HpetTimerEnable (VOID)
{
  HPET_GENERAL_CONFIGURATION_REGISTER  HpetGeneralConfigRegister;

  if (!mInRunTime) {
    HpetGeneralConfigRegister.Uint64 = MmioRead64 ((UINTN)(UINT8 *)(mHpetBaseAddr + HPET_GENERAL_CONFIGURATION_OFFSET));
    if (HpetGeneralConfigRegister.Bits.MainCounterEnable != mOrigHpetGeneralConfigRegister.Bits.MainCounterEnable) {
      HpetGeneralConfigRegister.Uint64 = mOrigHpetGeneralConfigRegister.Uint64;
      MmioWrite64 ((UINTN)(UINT8 *)(mHpetBaseAddr + HPET_GENERAL_CONFIGURATION_OFFSET), HpetGeneralConfigRegister.Uint64);
    }
  }
}

/**
  Disable the main counter in the HPET Timer.

  @param  Enable  If TRUE, then enable the main counter in the HPET Timer.
                  If FALSE, then disable the main counter in the HPET Timer.
**/
VOID HpetTimerDisable (VOID)
{
  HPET_GENERAL_CONFIGURATION_REGISTER  HpetGeneralConfigRegister;

  if (!mInRunTime) {
    HpetGeneralConfigRegister.Uint64 = MmioRead64 ((UINTN)(UINT8 *)(mHpetBaseAddr + HPET_GENERAL_CONFIGURATION_OFFSET));
    mOrigHpetGeneralConfigRegister.Uint64 = HpetGeneralConfigRegister.Uint64;
    if (HpetGeneralConfigRegister.Bits.MainCounterEnable != 0) {
      HpetGeneralConfigRegister.Bits.MainCounterEnable = 0;
      MmioWrite64 ((UINTN)(UINT8 *)(mHpetBaseAddr + HPET_GENERAL_CONFIGURATION_OFFSET), HpetGeneralConfigRegister.Uint64);
    }
  }
}
#endif

/**
 Creates critical section.
 @param CriticalSection
 @retval EFI_OUT_OF_RESOURCES
 @retval EFI_INVALID_PARAMETER
 @retval EFI_SUCCESS
*/
EFI_STATUS CreateCriticalSection(OUT CRITICAL_SECTION *CriticalSection){
	if (gCriticalSectionPtr != NULL) return EFI_OUT_OF_RESOURCES;
	if (CriticalSection == NULL) return EFI_INVALID_PARAMETER;
	gCriticalSection.Busy = FALSE;
	gCriticalSectionPtr = &gCriticalSection;
	*CriticalSection = gCriticalSectionPtr;
	return EFI_SUCCESS;
}

EFI_STATUS DestroyCriticalSection(IN CRITICAL_SECTION CriticalSection){
	if (IS_INVALID_CRITICAL_SECTION(CriticalSection))
		return EFI_INVALID_PARAMETER;
	gCriticalSectionPtr = NULL;
	return EFI_SUCCESS;
}

/**
  This function is called when critical section begins. It disables interupts, 
  and Smi and fills CRITICAL_SECTION structure fields
  @param CriticalSection - pointer to CRITICAL_SECTION structure
*/
EFI_STATUS BeginCriticalSection(IN CRITICAL_SECTION CriticalSection)
{
    CRITICAL_SECTION_INTERNAL TempCs;
	CRITICAL_SECTION_INTERNAL *Cs;
	
	if (IS_INVALID_CRITICAL_SECTION(CriticalSection))
		return EFI_INVALID_PARAMETER;
		
	Cs = (CRITICAL_SECTION_INTERNAL*)CriticalSection;
	if (Cs->Busy) return EFI_ACCESS_DENIED;
	
    TempCs.IntState[0] = IoRead8(0x21);
    TempCs.IntState[1] = IoRead8(0xa1);
    if (!NvramSmmIsActive) {
        TempCs.SmiState = SbLib_GetSmiState();
    }

    IoWrite8(0x21, 0xff);
    IoWrite8(0xa1, 0xff);
    if (!NvramSmmIsActive) {        
        SbLib_SmiDisable();
    }
#if defined (HPET_PROTOCOL_SUPPORT) && (HPET_PROTOCOL_SUPPORT == 1)
    HpetTimerDisable();
#endif

    Cs->Busy = TRUE;

    Cs->IntState[0] = TempCs.IntState[0];
    Cs->IntState[1] = TempCs.IntState[1];
    if (!NvramSmmIsActive) {
        Cs->SmiState = TempCs.SmiState;
    }

	return EFI_SUCCESS;
}

/**
  This function calls when critical section ends. It enable interupts, 
  and Smi and fills CRITICAL_SECTION structure fields
  @param CriticalSection - pointer to CRITICAL_SECTION structure
*/
EFI_STATUS EndCriticalSection(IN CRITICAL_SECTION CriticalSection)
{
    CRITICAL_SECTION_INTERNAL TempCs;
	CRITICAL_SECTION_INTERNAL *Cs;
	
	if (IS_INVALID_CRITICAL_SECTION(CriticalSection))
		return EFI_INVALID_PARAMETER;

	Cs = (CRITICAL_SECTION_INTERNAL*)CriticalSection;
	if (!Cs->Busy) return EFI_NOT_STARTED;
	
    TempCs.IntState[0] = Cs->IntState[0];
    TempCs.IntState[1] = Cs->IntState[1];
    if (!NvramSmmIsActive) {
        TempCs.SmiState = Cs->SmiState;
    }

    Cs->Busy = FALSE;

    if (!NvramSmmIsActive) {
        if (TempCs.SmiState) SbLib_SmiEnable();
    }
#if defined (HPET_PROTOCOL_SUPPORT) && (HPET_PROTOCOL_SUPPORT == 1)
    HpetTimerEnable ();
#endif
    IoWrite8(0x21, TempCs.IntState[0]);
    IoWrite8(0xa1, TempCs.IntState[1]);
	return EFI_SUCCESS;
}

#if defined (HPET_PROTOCOL_SUPPORT) && (HPET_PROTOCOL_SUPPORT == 1)
/**
  This is the Event call back function is triggered in SMM to notify the Library
  the system is entering runtime phase and Update the global variable mInRunTime 
  before Exit Boot Service Event.

  @param[in] Protocol   Points to the protocol's unique identifier
  @param[in] Interface  Points to the interface instance
  @param[in] Handle     The handle on which the interface was installed

  @retval EFI_SUCCESS SmmAtRuntimeCallBack runs successfully
**/
EFI_STATUS EFIAPI HeptLibExitBsSmmCallBack (
  IN CONST EFI_GUID     *Protocol,
  IN VOID               *Interface,
  IN EFI_HANDLE         Handle
  )
{
  if (!mInRunTime) {
    mInRunTime = TRUE;
  }
  return EFI_SUCCESS;
}

/**
  Update the global variable mInRunTime before Exit Boot Service Event.
  
  @param Event   Event of callback
  @param Context Pointer to context of callback
  
  @retval VOID
**/
VOID EFIAPI HeptLibExitBsNotifyEvent(IN EFI_EVENT Event, IN VOID *Context)
{
  if (!mInRunTime) {
    mInRunTime = TRUE;
  }
}

VOID EFIAPI HpetLibVirtualNotifyEvent(IN EFI_EVENT Event, IN VOID *Context)
{
  gRT->ConvertPointer(0, (VOID **)&mHpetBaseAddr);
}
#endif

/**
  The constructor function creates a Exit Boot Service Event to change global variable mInRunTime 
  indicating now in runtime and Set Virtual Address Map Event to convert physical address to virtual addresses.
  
  @param  ImageHandle   The firmware allocated handle for the EFI image.
  @param  SystemTable   A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS   The constructor completed successfully.
  @retval Other value   The constructor did not complete successfully.

**/
EFI_STATUS
EFIAPI
RtSbHpetLibConstructor (
  IN EFI_HANDLE        ImageHandle, 
  IN EFI_SYSTEM_TABLE  *SystemTable
)
{
#if defined (HPET_PROTOCOL_SUPPORT) && (HPET_PROTOCOL_SUPPORT == 1)
  EFI_STATUS         Status;
  VOID               *Registration;
  
  Status = gBS->LocateProtocol( &gEfiSmmBase2ProtocolGuid, NULL, &mSmmBase2 );
  if (!EFI_ERROR(Status)) {          
    mSmmBase2->InSmm (mSmmBase2, &mInSmm); 
    if (mInSmm) {
      //
      // Here is in SMM
      //
      Status = mSmmBase2->GetSmstLocation (mSmmBase2, &mSmst);

      if (!EFI_ERROR(Status)) {
        //
        // Register a callback for exiting boot service
        //
        Registration = NULL;
        Status = mSmst->SmmRegisterProtocolNotify (
                         &gEdkiiSmmExitBootServicesProtocolGuid,
                         HeptLibExitBsSmmCallBack,
                         &Registration
                         );
        return EFI_SUCCESS;
      }
    } 
  }

  Status = gBS->CreateEvent(
                  EVT_SIGNAL_EXIT_BOOT_SERVICES, 
                  TPL_CALLBACK, 
                  HeptLibExitBsNotifyEvent, 
                  NULL,
                  &mRtHpetLibExitBootServiceEvent
                  );
  
  Status = gBS->CreateEvent(
                  EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE, 
                  TPL_CALLBACK, 
                  HpetLibVirtualNotifyEvent, 
                  NULL,
                  &mRtHpetLibVirtualAddressChangeEvent
                  );
#endif
      
  return EFI_SUCCESS;

}

/**
  The destructor function closes Exit Boot Service Event and Set Virtual Address Map Event.
  
  @param  ImageHandle   The firmware allocated handle for the EFI image.
  @param  SystemTable   A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS   The destructor completed successfully.
  @retval Other value   The destructor did not complete successfully.

**/
EFI_STATUS
EFIAPI
RtSbHpetLibDestructor (
    IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable
  )
{
#if defined (HPET_PROTOCOL_SUPPORT) && (HPET_PROTOCOL_SUPPORT == 1)
  if ((!mInSmm) && (gBS != NULL)) {
    gBS->CloseEvent(mRtHpetLibExitBootServiceEvent);
    gBS->CloseEvent(mRtHpetLibVirtualAddressChangeEvent);
  }
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
