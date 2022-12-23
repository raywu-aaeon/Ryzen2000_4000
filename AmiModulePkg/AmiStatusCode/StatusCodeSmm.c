//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file StatusCodeSmm.c

	SMM StausCode Functions 
**/
//**********************************************************************
#include "StatusCodeInt.h"
#include <AmiDxeLib.h>
#include <Protocol/SmmReportStatusCodeHandler.h>
#include <Protocol/SmmStatusCode.h>
#include <Library/SmmServicesTableLib.h>
#include <Protocol/AmiDebugService.h>
#include <Token.h>
#include <Library/PrintLib.h>

#define SMM_CALLBACK_NUMBER 10

AMI_STATUS_CODE_BUFFER *StausCodeBuffer;
UINT16 StringMaxSize = 2048;
UINT8 *String = NULL;
UINT16 NestedDebug = 0;
UINT16 NestedAssert = 0;

INIT_FUNCTION* InitPartsList[] = {NULL};

extern STRING_FUNCTION SMM_STRING_LIST EndOfStringList;
STRING_FUNCTION* StringList[] = {SMM_STRING_LIST NULL};

extern SIMPLE_FUNCTION SMM_SIMPLE_LIST EndOfSimpleList;
SIMPLE_FUNCTION* SimpleList[] = {SMM_SIMPLE_LIST NULL};

extern MISC_FUNCTION SMM_MISC_LIST EndOfMiscList;
MISC_FUNCTION* MiscList[] = {SMM_MISC_LIST NULL};

extern CHECKPOINT_FUNCTION SMM_CHECKPOINT_LIST EndOfCheckpointList;
CHECKPOINT_FUNCTION* CheckpointList[] = {SMM_CHECKPOINT_LIST NULL};

extern DEBUG_SERVICE_PRINT_FUNCTION SMM_DEBUG_PRINT_LIST EndOfDebugPrintList;
DEBUG_SERVICE_PRINT_FUNCTION* DebugServicePrintList[] = {SMM_DEBUG_PRINT_LIST NULL};

extern DEBUG_SERVICE_ASSERT_FUNCTION SMM_DEBUG_ASSERT_LIST EndOfDebugAssertList;
DEBUG_SERVICE_ASSERT_FUNCTION* DebugServiceAssertList[] = {SMM_DEBUG_ASSERT_LIST NULL};

extern DEBUG_SERVICE_PRINT_GATE_FUNCTION SMM_DEBUG_SERVICE_PRINT_GATE;
DEBUG_SERVICE_PRINT_GATE_FUNCTION* DebugServicePrintGate = SMM_DEBUG_SERVICE_PRINT_GATE;

extern DEBUG_SERVICE_ASSERT_GATE_FUNCTION SMM_DEBUG_SERVICE_ASSERT_GATE;
DEBUG_SERVICE_ASSERT_GATE_FUNCTION* DebugServiceAssertGate = SMM_DEBUG_SERVICE_ASSERT_GATE;

#define ERROR_ACTION(Value,Action) Action

extern ERROR_CODE_ACTION SMM_ERROR_CODE_ACTIONS EndOfActionList;

#undef ERROR_ACTION
#define ERROR_ACTION(Value,Action) {Value,&Action}

ERROR_CODE_ACTION_MAP ErrorCodeActions[] =
{
    SMM_ERROR_CODE_ACTIONS
    {0,0}
};

UINT16 RouterRecurciveStatus = 0;
typedef struct {
    UINT32 RegisteredSmmEntries;
    EFI_SMM_RSC_HANDLER_CALLBACK  RscSmmHandlerCallback[SMM_CALLBACK_NUMBER];
} SMM_ROUTER_STRUCT;


SMM_ROUTER_STRUCT SmmRouterCallbackStr;

#if DETAILED_ERROR_MESSAGES
// To reduce ROM footprint of the status code module we are only including the most common errors here. 
ERROR_MESSAGE ErrorMessage[] = {
//Reported by the PEIM or DXE driver which detected the error
    { GENERIC_MEMORY_CORRECTABLE_ERROR, "Correctable memory error"},
    { GENERIC_MEMORY_UNCORRECTABLE_ERROR, "Uncorrectable memory error"},

//Reported by the PEIM or DXE driver which detected the error
    { GENERIC_CPU_THERMAL_ERROR, "CPU thermal error"},
    { GENERIC_CPU_LOW_VOLTAGE, "CPU low voltage"},
    { GENERIC_CPU_HIGH_VOLTAGE, "CPU high voltage"},
    { GENERIC_CPU_CORRECTABLE_ERROR, "Correctable CPU ECC error"},
    { GENERIC_CPU_UNCORRECTABLE_ERROR, "Uncorrectable CPU ECC error"},
    {0, NULL}
};

BOOLEAN PrintDetailedErrorMessage(IN EFI_STATUS_CODE_VALUE Value, OUT UINT8 *Str){
    UINT32 i;
    for(i=0; ErrorMessage[i].ErrorValue!=0; i++){
        if (ErrorMessage[i].ErrorValue == Value){
            AsciiSPrint(
                (CHAR8*)Str, StringMaxSize,
                "ERROR: %a\n", ErrorMessage[i].ErrorString
            );
            return TRUE;
        }
    }
    return FALSE;    
}
#endif

/**
    Remove a previously registered callback function from the notification list.

         
    @param Callback A pointer to a function that 
        that is to be unregistered.
      
    @retval 
        EFI_SUCCESS           Function was successfully unregistered.
        EFI_INVALID_PARAMETER The callback function was NULL.
        EFI_NOT_FOUND         The callback function was not found to be unregistered. 
**/
EFI_STATUS
EFIAPI
SmmUnregister (
  IN EFI_SMM_RSC_HANDLER_CALLBACK Callback
  )
{
    UINT32                        i;

    if (Callback == NULL) return EFI_INVALID_PARAMETER;

    for (i = 0; i != SmmRouterCallbackStr.RegisteredSmmEntries; i++) 
    {
        if (SmmRouterCallbackStr.RscSmmHandlerCallback[i] == Callback) 
        {
            SmmRouterCallbackStr.RscSmmHandlerCallback[i] = NULL;
            return EFI_SUCCESS; //Function Unregistered 
        }
    }

    return EFI_NOT_FOUND;
}

/**
    When this function is called the function pointer is added to an 
    internal list and any future calls to ReportStatusCode() will be
    forwarded to the Callback function.

         
    @param Callback A pointer to a function that 
        is called when a call to ReportStatusCode() occurs.
      
    @retval 
        EFI_SUCCESS           Function was successfully registered.
        EFI_INVALID_PARAMETER The callback function was NULL.
        EFI_OUT_OF_RESOURCES  The internal buffer ran out of space. No more functions 
        can be registered.
        EFI_ALREADY_STARTED   The function was already registered. It can't be 
        registered again.   
**/
EFI_STATUS
EFIAPI
SmmRegister (
  IN EFI_SMM_RSC_HANDLER_CALLBACK Callback
  )
{
    UINT32                        i=0, FreeEntry = (UINT32)-1;

    if (Callback == NULL) 
        return EFI_INVALID_PARAMETER;
    if (SmmRouterCallbackStr.RegisteredSmmEntries != 0)
    {
        for (i = 0; i != SmmRouterCallbackStr.RegisteredSmmEntries; i++) 
        {
            if (SmmRouterCallbackStr.RscSmmHandlerCallback[i] == Callback)
                return EFI_ALREADY_STARTED; //Function already registered 
            if (SmmRouterCallbackStr.RscSmmHandlerCallback[i] == NULL)
                FreeEntry = i; 
        }
        if (FreeEntry == -1) //No Unregistered entries
        {
            if (SmmRouterCallbackStr.RegisteredSmmEntries == SMM_CALLBACK_NUMBER - 1)
                return EFI_OUT_OF_RESOURCES; // And all entries are taken already - exit
            FreeEntry = i;
            SmmRouterCallbackStr.RegisteredSmmEntries++;
        }
    }
    else 
    {
        SmmRouterCallbackStr.RegisteredSmmEntries++;
        FreeEntry = 0;
    }
    SmmRouterCallbackStr.RscSmmHandlerCallback[FreeEntry] = Callback;

    return EFI_SUCCESS;
}

EFI_SMM_RSC_HANDLER_PROTOCOL  SmmRscHandlerProtocol = {
    SmmRegister,
    SmmUnregister
    };


/**
    Pass all parameters to Registered Statuse Code Routers.

        
    @param Type the type and severity of the error that occurred
    @param Value the Class, subclass and Operation that caused the error
    @param Instance 
    @param CallerId OPTIONAL - The GUID of the caller function
    @param Data OPTIONAL - the extended data field that contains additional info

    @retval EFI_STATUS

**/

EFI_STATUS ReportSmmRouter (
    IN EFI_STATUS_CODE_TYPE     Type,
    IN EFI_STATUS_CODE_VALUE    Value,
    IN UINT32                   Instance,
    IN  CONST EFI_GUID                 *CallerId  OPTIONAL,
    IN EFI_STATUS_CODE_DATA     *Data      OPTIONAL
    )
{

    UINT32                        i;
 
    if ((SmmRouterCallbackStr.RegisteredSmmEntries == 0) || (InterlockedCompareExchange16 (&RouterRecurciveStatus, 0, 1) == 1)) 
        return EFI_ACCESS_DENIED;
    for (i = 0; i != SmmRouterCallbackStr.RegisteredSmmEntries; i++) 
    {
        if (SmmRouterCallbackStr.RscSmmHandlerCallback[i] == NULL) 
            continue;//Unregistered function
        else
            SmmRouterCallbackStr.RscSmmHandlerCallback[i] (Type, Value, Instance, (EFI_GUID*)CallerId, Data);
    }
    // Restore the Recursive status of report

    InterlockedCompareExchange16 (&RouterRecurciveStatus, 1, 0);
    return EFI_SUCCESS;
}
EFI_STATUS ReportRouterHelper (
	IN VOID 					*PeiServices,
    IN EFI_STATUS_CODE_TYPE     Type,
    IN EFI_STATUS_CODE_VALUE    Value,
    IN UINT32                   Instance,
    IN EFI_GUID                 *CallerId  OPTIONAL,
    IN EFI_STATUS_CODE_DATA     *Data      OPTIONAL
    )
{
	return ReportSmmRouter(Type, Value, Instance, CallerId, Data); 
}
/**
    SMM Status Code Reporting function.
    A wrapper around phase independent ReportStatucCode
    function defined in StatusCodeCommon.c.

        
    @param This 
        Points to this instance of the EFI_SMM_STATUS_CODE_PROTOCOL.
    @param Value the Class, subclass and Operation that caused the error
    @param Instance Instance - Instance
        *CallerId OPTIONAL - The GUID of the caller function
        *Data OPTIONAL - the extended data field that contains additional info

    @retval EFI_STATUS

**/
EFI_STATUS EFIAPI SmmReportStatusCode (
    IN CONST EFI_SMM_STATUS_CODE_PROTOCOL *This, IN EFI_STATUS_CODE_TYPE Type,
    IN EFI_STATUS_CODE_VALUE Value,
    IN UINT32 Instance, IN CONST EFI_GUID *CallerId OPTIONAL,
    IN EFI_STATUS_CODE_DATA *Data OPTIONAL
)
{   
    EFI_STATUS Status;

    ReportSmmRouter (Type, Value, Instance, CallerId, Data);

    Status = AmiReportStatusCode( NULL, Type, Value, Instance, (EFI_GUID*)CallerId, Data, String);

    return Status;
}

// ******************** AmiDebugService implementation ****************
VOID EFIAPI DebugPrintHelper(
    UINTN ErrorLevel, CONST CHAR8 *Format, VA_LIST VaListMarker
)
{
    if (NestedAssert == 1 || InterlockedCompareExchange16 (&NestedDebug, 0, 1) == 1)
        return;
    AmiDebugServiceDebugPrintHelper(NULL,String,ErrorLevel,Format,VaListMarker);
    InterlockedCompareExchange16 (&NestedDebug, 1, 0);
}

VOID EFIAPI DebugAssertHelper(
    CONST CHAR8  *FileName, UINTN LineNumber, CONST CHAR8  *Description
)
{
    if (InterlockedCompareExchange16 (&NestedAssert, 0, 1) == 1)
        return;
    AmiDebugServiceDebugAssertHelper(NULL,String,FileName,LineNumber,Description);
    InterlockedCompareExchange16 (&NestedAssert, 1, 0);
}

static AMI_DEBUG_SERVICE_PROTOCOL AmiDebugServiceProtocol;

VOID AmiSmmDebugServiceInitialization()
{
    EFI_HANDLE  Handle=NULL;
    
    AmiDebugServiceProtocol.Debug = DebugPrintHelper;
    AmiDebugServiceProtocol.DebugAssert = DebugAssertHelper;
#ifdef AMI_DEBUG_SERVICE_PROTOCOL_REVISION
    AmiDebugServiceProtocol.Revision = 0x10000;
#endif
    gSmst->SmmInstallProtocolInterface(&Handle, &gAmiSmmDebugServiceProtocolGuid, EFI_NATIVE_INTERFACE, &AmiDebugServiceProtocol);
}
// ******************** End of AmiDebugService implementation *********

EFI_SMM_STATUS_CODE_PROTOCOL SmmStatusCode = {SmmReportStatusCode};

EFI_STATUS 
EFIAPI 
SmmInitStatusCode(
    IN EFI_HANDLE         ImageHandle,
    IN EFI_SYSTEM_TABLE   *SystemTable
)
{
    EFI_STATUS          Status;
    EFI_HANDLE  	SmmHandle = NULL;

    InitAmiLib(ImageHandle,SystemTable);
    // install debug service protocol
    Status = gSmst->SmmAllocatePool (EfiRuntimeServicesData, sizeof (AMI_STATUS_CODE_BUFFER), (VOID**) &StausCodeBuffer);
        ASSERT_EFI_ERROR (Status);
        if (EFI_ERROR(Status)) return Status;

        pBS->SetMem(StausCodeBuffer,sizeof (AMI_STATUS_CODE_BUFFER), 0);
        StausCodeBuffer->Header.HeaderSize = (UINT16) sizeof (EFI_STATUS_CODE_DATA);
        StausCodeBuffer->Header.Size = sizeof (AMI_STATUS_CODE_BUFFER) - sizeof (EFI_STATUS_CODE_DATA);
        
        CopyGuid (&StausCodeBuffer->Header.Type, &gEfiStatusCodeDataTypeDebugGuid);
        String = (UINT8*)&(StausCodeBuffer->String[0]);
        
    AmiSmmDebugServiceInitialization();
    SmmRouterCallbackStr.RegisteredSmmEntries = 0;

 
    Status = gSmst->SmmInstallProtocolInterface(
                    &SmmHandle,
                    &gEfiSmmRscHandlerProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &SmmRscHandlerProtocol
                    );
    //ASSERT_EFI_ERROR (Status);


    Status = gSmst->SmmInstallProtocolInterface(
                 &SmmHandle,
                 &gEfiSmmStatusCodeProtocolGuid,
                 EFI_NATIVE_INTERFACE, &SmmStatusCode
    );


    return Status;
}

/**
    Error Code Action.
    Attempts to perform a system reset. If reset fails, returns.

        
    @param PeiServices not used
    @param Value Value of the error code that triggered the action.

         
    @retval VOID

**/
VOID ResetOrResume(
    IN VOID *PeiServices, IN EFI_STATUS_CODE_VALUE Value
)
{
    pRS->ResetSystem(EfiResetCold,0,0,NULL);
}


