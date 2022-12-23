//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
#include <Token.h>
#include "includes.h"
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/PcdLib.h>
#include <CryptLib.h>

//
// Global variables
//
EFI_EVENT     mVirtualAddressChangeEvent = NULL;

// Crypto Memory Manager heap address
static UINT8 *gDstAddress = NULL;
static UINTN  gHeapSize   = 0;

/**
  Return pointer to CRMm Descriptor table

  @param[in]  none
  
  @retval     pointer to CRMm Descriptor table
**/
VOID * GetCRmmPtr()
{
    return gDstAddress;
}

/**
  This is a notification function registered on EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE
  event. It converts a pointer to a new virtual address.
  
  @param  Event        Event whose notification function is being invoked.
  @param  Context      Pointer to the notification function's context

**/
VOID
EFIAPI
RuntimeCryptLibAddressChangeEvent (
  IN  EFI_EVENT        Event,
  IN  VOID             *Context
  )
{
  //
  // Stop Crypto debug traces after switch to Virtual mode
  //
  wpa_set_trace_level(0); 
  //
  // Converts a pointer for runtime memory management to a new virtual address.
  //
  gRT->ConvertPointer(0, (VOID**)&gDstAddress);

//  InitCRmm((VOID*)gDstAddress, gHeapSize);

  return;
}

/**
  This constructor function allocates memory for Crypto Memory manager,
  and sets local EfiTime variable with current EfiTime

  @param  ImageHandle   The firmware allocated handle for the EFI image.
  @param  SystemTable   A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS   The constructor always returns EFI_SUCCESS.

**/
EFI_STATUS
EFIAPI
AmiCryptLibConstructor(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_TIME    EfiTime;

    DEBUG((AmiCryptoPkg_DEBUG_LEVEL,"AmiCryptoLib Constructor\n"));
    //
    // Update Crypto debug traces level
    //
    //wpa_set_trace_level(CRYPTO_trace_level);
    ///////////////////////////////////////////////////////////////////////////////
    //
    // Init Aux Memory Manager
    // Pre-allocates runtime space for possible cryptographic operations
    //
    ///////////////////////////////////////////////////////////////////////////////
    gHeapSize = PcdGet32(AmiPcdCpMaxHeapSize);
    if(gDstAddress == NULL)
        gDstAddress = (UINT8*)AllocateRuntimePool ((UINTN) gHeapSize);
    DEBUG((AmiCryptoPkg_DEBUG_LEVEL,"RT Heap alloc (addr=%X, size=%x)\n", gDstAddress, gHeapSize));
    if(gDstAddress != NULL)
        InitCRmm( (void*)gDstAddress, gHeapSize);
	///////////////////////////////////////////////////////////////////////////////
    //
    // Update local EfiTime variable
    //
    ///////////////////////////////////////////////////////////////////////////////
    gRT->GetTime(&EfiTime, NULL);
    set_crypt_efitime(&EfiTime);

    return EFI_SUCCESS;
}

/**
  The destructor function frees memory allocated by constructor.

  @param  ImageHandle   The firmware allocated handle for the EFI image.
  @param  SystemTable   A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS   The constructor always returns EFI_SUCCESS.

**/
EFI_STATUS
EFIAPI
AmiCryptLibDestructor(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    DEBUG((AmiCryptoPkg_DEBUG_LEVEL,"AmiCryptoLib Destructor\n"));
    if(gDstAddress) {
        InitCRmm( (void*)NULL, 0);
        FreePool ( (void*)gDstAddress);
    }

    return EFI_SUCCESS;
}
//=======================================================================================
/**
  This constructor function installs Notification function 
  on EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE.

  @param  ImageHandle   The firmware allocated handle for the EFI image.
  @param  SystemTable   A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS   The constructor always returns EFI_SUCCESS.

**/
EFI_STATUS
EFIAPI
AmiCryptLibRunConstructor(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    DEBUG((AmiCryptoPkg_DEBUG_LEVEL,"Runtime"));
    AmiCryptLibConstructor(ImageHandle,SystemTable);
    //////////////////////////////////////////////////////////////////////////////
    //
    // Create virtual address change event
    //
    ///////////////////////////////////////////////////////////////////////////////
    gBS->CreateEvent(EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE, TPL_CALLBACK, RuntimeCryptLibAddressChangeEvent, NULL, &mVirtualAddressChangeEvent);

    return EFI_SUCCESS;
}

/**
  The destructor function frees memory allocated by constructor, and closes related events.
  It will ASSERT() if that related operation fails and it will always return EFI_SUCCESS. 

  @param  ImageHandle   The firmware allocated handle for the EFI image.
  @param  SystemTable   A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS   The constructor always returns EFI_SUCCESS.

**/
EFI_STATUS
EFIAPI
AmiCryptLibRunDestructor(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    DEBUG((AmiCryptoPkg_DEBUG_LEVEL,"Runtime"));
    AmiCryptLibDestructor(ImageHandle, SystemTable);

    if (mVirtualAddressChangeEvent) {
        ASSERT (gBS != NULL);
        gBS->CloseEvent (mVirtualAddressChangeEvent);
    }

    return EFI_SUCCESS;
}
