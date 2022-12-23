//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file
  Module that supports the IBVs level of responsibility related to the 
  HSTI (Hardware Security Test Interface) Specification.  
  
  This will provide the OEM/ODM the ability to find out information about
  the firmware's security state. and return that information.
**/


#include <AmiHsti.h>
#include <AmiHstiElinks.h>
// Handle for string resources that are part of the module
EFI_HII_HANDLE HiiHandle=0;

#if defined (HSTI_REVISION) && (HSTI_REVISION == 0)
CHAR16 ImplementationId[] = L"AMI AptioV v1.0";
#elif defined (HSTI_REVISION) && (HSTI_REVISION == 1)
CHAR16 ImplementationId[] = L"AMI AptioV v2.0";
#endif

typedef VOID (EFIAPI AMI_IBV_HSTI_SECURITY_TEST)( VOID );

extern AMI_IBV_HSTI_SECURITY_TEST HSTI_TEST_LIST EndOfHstiTestList;
AMI_IBV_HSTI_SECURITY_TEST *HstiTestList[] = {HSTI_TEST_LIST NULL};




CHAR8 ENGLISH_LANG[] = "en-US";

/**
  This function adds the error string that corresponds to the test failure that was reported.  The string gets added at the end of the HSTI table
  
 @param BitNum
 @param ErrorNum
 @param Token
 
 @return EFI_STATUS
 @retval EFI_SUCCESS - the functionproperly add the string to the table
 */
EFI_STATUS ReportError( 
        UINT32 BitNum,
        UINT16 ErrorNum,
        STRING_REF Token)
{
    CHAR8 *Language = NULL;
    CHAR16 *ErrorString = NULL;
    CHAR16 *NewString = NULL;
    BOOLEAN DoNotFreeLang = FALSE;
    UINTN StringSize;

    DEBUG((DEBUG_VERBOSE, "AMI HSTI get language and String, then append string to the table.\n\r"));

    // Get current language.  This is to support multi languages. if the translations are prov1ded
    Language = GetVariable(L"PlatformLang", &gEfiGlobalVariableGuid);
    if (Language == NULL)
    {
        DoNotFreeLang = TRUE;
        Language = ENGLISH_LANG; // use english if PlatformLang variable is not installed
    }
    // gets the string from the local Hii Database
    ErrorString = HiiGetString(HiiHandle, Token, Language);
    if (ErrorString != NULL)
    {
        StringSize = StrLen(ErrorString);
        NewString = AllocatePool((StringSize + 10)*2);
        UnicodeSPrint(NewString, ((StringSize + 10) *2), ErrorString, BitNum, ErrorNum);
        DEBUG((DEBUG_VERBOSE, "...%S\n\r", NewString));    
        
        //Use the MdePkg to Append the error string to the end of the table
        HstiLibAppendErrorString (PLATFORM_SECURITY_ROLE_PLATFORM_IBV, ImplementationId, NewString);
    }
    
    // free memory
    if (!DoNotFreeLang)
        gBS->FreePool(Language);
    if (ErrorString)
        gBS->FreePool(ErrorString);
    if (NewString)
        gBS->FreePool(NewString);

    return EFI_SUCCESS;
}

/**
 This function runs all the tests and reports the data so that the HSTI table can be updated.
 
 A return value of FALSE means that we have passed that test.  TRUE indicates an error.
 
 @param VOID
 @return VOID
 */
VOID RunTests(VOID)
{
    UINTN Idx;
  
    
    for (Idx=0; HstiTestList[Idx]; Idx++) 
    {
            HstiTestList[Idx]();
    }
    
}



/**
 This function is the callback for HSTI to run the tests and log the results
 
 @return EFI_STATUS
 @retval EFI_SUCCESS
 @retval EFI_OUT_OF_RESOURCES
 */
VOID AmiHsti_PerformTestsAndPublish(IN EFI_EVENT Event, IN VOID *Context)
{
	DEBUG((DEBUG_VERBOSE, "AMI HSTI Callback.\n\r"));

	gBS->CloseEvent(Event);

	// Determine what test need to be run and execute them and store the information.
    RunTests();
}



EFI_STATUS EFIAPI HstiEntryPoint(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status;
    EFI_EVENT Event = NULL;
    ADAPTER_INFO_PLATFORM_SECURITY *AipTable;
    UINTN Size;
    CHAR16 *String;
    UINT8 *ImplementedArray;
    UINT32 Index;
    UINT32 NumSecurityBytes;
    UINT64 ImplementationBitMap;

    // create a Hii Database for the Error strings and load them into the database
    InitAmiLib(ImageHandle, SystemTable);
    // Load the strings for use when creating the Error strings
    Status = LoadStrings(ImageHandle, &HiiHandle);
    if (EFI_ERROR(Status))
        ASSERT(Status == EFI_SUCCESS);

    // Create the IBV AIP table for later use
    NumSecurityBytes = PcdGet32(AmiPcdHstiNumSecurityBytes);
    // Test that makes sure that this value to something other than 0
    ASSERT (NumSecurityBytes != 0 );

#if defined (HSTI_REVISION) && (HSTI_REVISION == 0)
    // size of structure, the size of the 3 different arrays, and then an empty null terminated string
    Size = sizeof(ADAPTER_INFO_PLATFORM_SECURITY) + (3*NumSecurityBytes ) + sizeof(CHAR16);
#elif defined (HSTI_REVISION) && (HSTI_REVISION == 1)
    // size of structure, the size of the 2 different arrays, the size of the Windows Bitmap, and then an empty null terminated string
    Size = sizeof(ADAPTER_INFO_PLATFORM_SECURITY) + (2 * NumSecurityBytes ) + (4 * sizeof(UINT32)) + sizeof(CHAR16);
#endif
    // generate IBV version of the table and then start testing what is
    // defined by the IBV Bitmaps.  Make sure initial Array is all zeros
    AipTable = AllocateZeroPool(Size);
    if (AipTable == NULL)
        return EFI_OUT_OF_RESOURCES;
    
//#if defined (HSTI_REVISION) && (HSTI_REVISION == 0)
//    AipTable->Version = PLATFORM_SECURITY_VERSION_VNEXTCS3;
//#elif defined (HSTI_REVISION) && (HSTI_REVISION == 1)
    AipTable->Version = PLATFORM_SECURITY_VERSION_VNEXTCS;
//#endif
    AipTable->Role = PLATFORM_SECURITY_ROLE_PLATFORM_IBV;
    
    Status = StrnCpyS(AipTable->ImplementationID, sizeof(AipTable->ImplementationID), ImplementationId, StrLen(ImplementationId));
    if (EFI_ERROR(Status))
    {
        DEBUG((DEBUG_ERROR, "AMI HSTI: Implementation ID String too long\n\r"));
        ASSERT(StrLen(ImplementationId) > sizeof(AipTable->ImplementationID));
    }
    // length of each Array.  not total length of all the arrays
    AipTable->SecurityFeaturesSize = NumSecurityBytes;

#if defined (HSTI_REVISION) && (HSTI_REVISION == 0)
    // pointer to the Implemented Array
    ImplementedArray = (UINT8 *)((UINTN)AipTable + sizeof(ADAPTER_INFO_PLATFORM_SECURITY) + NumSecurityBytes );
    // skip over the Implemented and Verified arrays
    String = (CHAR16 *)(ImplementedArray + 2*NumSecurityBytes);  // pointer to the Error Strings
#elif defined (HSTI_REVISION) && (HSTI_REVISION == 1)
    // pointer to the Implemented Array
    ImplementedArray = (UINT8 *)((UINTN)AipTable + sizeof(ADAPTER_INFO_PLATFORM_SECURITY));
    // skip over the Implemented and Verified arrays and the Windows bitmap array
    String = (CHAR16 *)(ImplementedArray + 2*NumSecurityBytes + (4 * sizeof(UINT32)) );  // pointer to the Error Strings
#endif
    // get the PCD that defines the Bitmap of Implemented Tests for the IBV
    ImplementationBitMap = PcdGet64(AmiPcdHstiImplementedTestBitmap);
    
    // Test that makes sure that the Chipset Porting Engineer has
    //  set this value to something other than 0
    ASSERT (ImplementationBitMap != 0 );
    
    // Determine what test need to be run and set the appropriate bits .
    for (Index = 0; Index < NumSecurityBytes; Index++)
    {
        // copies byte by byte from implementation bitmap to Implementation Array
        ImplementedArray[Index] = (UINT8)(ImplementationBitMap >> (8*Index));
    }

    // Set the String to a NULL character
    *String = 0;

    // Initial publishing of the table
    DEBUG((DEBUG_VERBOSE, "AMI HSTI - Publish default Table with only implemented bits set.\n\r"));
    Status = HstiLibSetTable(AipTable, Size);

    // Create Callback for running tests.
    Status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL, TPL_CALLBACK, AmiHsti_PerformTestsAndPublish, NULL, &Event);
    if(!EFI_ERROR(Status))
        Status = gBS->CreateEventEx (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    AmiHsti_PerformTestsAndPublish,
                    NULL,
                    &gEfiEventReadyToBootGuid,
                    &Event
                    );
    return Status;
}
