//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file HddSecDynamicSetup.c
    HDD Security Setup Routines
    Use this hook to dynamically change HDD Security VFR data.

**/

#include <HddSecDynamicSetup.h>

#if defined(SECURITY_SETUP_ON_SAME_PAGE) && SECURITY_SETUP_ON_SAME_PAGE
EFI_STRING_ID gHddSecSupportedStrIds[HDD_SECURITY_MAX_HDD_COUNT];
EFI_STRING_ID gHddSecEnabledStrIds[HDD_SECURITY_MAX_HDD_COUNT];
EFI_STRING_ID gHddSecLockedStrIds[HDD_SECURITY_MAX_HDD_COUNT];
EFI_STRING_ID gHddSecFrozenStrIds[HDD_SECURITY_MAX_HDD_COUNT];
EFI_STRING_ID gHddSecUserPwdStsStrIds[HDD_SECURITY_MAX_HDD_COUNT];
EFI_STRING_ID gHddSecMasterPwdStsStrIds[HDD_SECURITY_MAX_HDD_COUNT];
#else
EFI_STRING_ID gHddSecSupportedStrIds[1];
EFI_STRING_ID gHddSecEnabledStrIds[1];
EFI_STRING_ID gHddSecLockedStrIds[1];
EFI_STRING_ID gHddSecFrozenStrIds[1];
EFI_STRING_ID gHddSecUserPwdStsStrIds[1];
EFI_STRING_ID gHddSecMasterPwdStsStrIds[1];
#endif

UINTN                                   gHddSecFrozenBaseKey = HDD_SECURITY_DYNAMIC_SETUP_SEC_FROZEN_00;
UINTN                                   gHddSecShowMasterBaseKey = HDD_SECURITY_DYNAMIC_SETUP_SEC_SHOW_MP_00;
UINTN                                   gHddSecUserPasswordBaseKey = HDD_SECURITY_DYNAMIC_SETUP_UP_00;
UINTN                                   gHddSecMasterPasswordBaseKey = HDD_SECURITY_DYNAMIC_SETUP_MP_00;
UINTN                                   gHddSecGotoBaseKey = HDD_SECURITY_DYNAMIC_SETUP_GOTO_00;
EFI_VARSTORE_ID                         gVarstoreId = HDD_SECURITY_DYNAMIC_VARIABLE_ID;
static EFI_GUID                         gHddSecEscOnPwdPromptGuid = AMITSE_ESC_ON_PWD_PROMPT_GUID;

static HDD_SECURITY_CONFIGURATION       *gHddSecurityConfig = NULL;
static EFI_GUID                         gHddSecurityConfigurationGuid = HDD_SECURITY_CONFIGURATION_VARIABLE_GUID;
static HDD_SECURITY_INTERNAL_DATA       *gHddSecurityInternalData = NULL;
static UINT16                           gHddSecurityCount = 0;
static UINT16                           gValidHddSecurityCount;
static UINTN                            gCurrentHddIndex = 0xFFFF;
static EFI_HII_STRING_PROTOCOL          *HiiString = NULL;
static CHAR8                            *SupportedLanguages=NULL;
static EFI_GUID                         gSecurityFormsetGuid = SECURITY_FORM_SET_GUID;
static EFI_HII_HANDLE                   gHiiHandle = NULL;
static EFI_GUID                         gHddSecurityLoadSetupDefaultsGuid = AMI_HDD_SECURITY_LOAD_SETUP_DEFAULTS_GUID;
static EFI_EVENT                        gHddSecurityLoadSetupDefaultsEvent = NULL;
static VOID                             *gHddSecEscNotifyRegistration;
static EFI_EVENT                        gHddSecEscNotifyEvent;
static BOOLEAN                          gHddSecIsEscPressed = FALSE;

#if !(defined (MDE_CPU_IA32) || defined (MDE_CPU_X64))

/**
  Local function defined for the Build except X64, IA32 Architecture
  i.e. GetRandomNumber64() function defined in "RngLib" will be used for X64 and IA32 supported projects.

  if Rand is NULL, then ASSERT().

  @param[out] Rand     Buffer pointer to store the 64-bit random value.

  @retval TRUE         Random number generated successfully.
  @retval FALSE        Failed to generate the random number.

**/
static
BOOLEAN
EFIAPI
HddSecGetRandomNumber64 (
  OUT UINT64                    *Rand
)
{
    if (!Rand) {
       ASSERT(FALSE);
       return FALSE;
    }
    
    *Rand = 0;
    return TRUE;
}
#define GET_RANDOM_NUMBER_64(Arg) HddSecGetRandomNumber64(Arg)
#else
BOOLEAN
EFIAPI
GetRandomNumber64 (
  OUT     UINT64    *Rand
);
#define GET_RANDOM_NUMBER_64(Arg) GetRandomNumber64(Arg)
#endif

#if defined(SETUP_PASSWORD_NON_CASE_SENSITIVE) && SETUP_PASSWORD_NON_CASE_SENSITIVE
/** @internal
    Function to update the given password to non case sensitive

    @param *Password     Pointer to Passsword for data security.
    @param PwdLength     Length of the password.

    @return VOID

    @endinternal
**/
static
VOID
UpdatePasswordToNonCaseSensitive(
        CHAR16 *Password,
        UINTN PwdLength
)
{
    UINTN Idx;
    for ( Idx = 0; Idx < PwdLength; Idx++ ) {
        Password[Idx] = ((Password[Idx]>=L'a')&&(Password[Idx]<=L'z'))?(Password[Idx]+L'A'-L'a'):Password[Idx];
    }
}
#endif

/** @internal
    Locate the Security Protocols and return the information

    @param VOID

    @return UINT16       Count of Valid HDD Security

    @endinternal
**/
static
UINT16
InitHddSecurityInternalDataPtr(
    VOID
)
{
    EFI_STATUS                      Status;
    AMI_HDD_SECURITY_INTERFACE      *Security = NULL;
    UINTN                           i;
    VOID                            *TempPtr;

    Status = gBS->LocateProtocol(
                    &gAmiHddSecurityProtocolGuid,
                    NULL,
                    (VOID**) &Security);

    if ( !EFI_ERROR( Status )) {
        gHddSecurityCount = *((UINT16*)Security->PostHddCount);
        gHddSecurityInternalData = *((HDD_SECURITY_INTERNAL_DATA**)Security->PostHddData);

        gValidHddSecurityCount = gHddSecurityCount;

        for(i=0;i<gHddSecurityCount;i++) {

            if( (gHddSecurityInternalData+i) != NULL ) {
                Status = gBS->HandleProtocol(
                                gHddSecurityInternalData[i].DeviceHandle,
                                &gAmiHddSecurityProtocolGuid,
                                &TempPtr
                                );

                if( EFI_ERROR(Status) ) {
                    TempPtr = 0;
                    gValidHddSecurityCount--;
                }
            }
        }

        return gValidHddSecurityCount;
    }

    return 0;
}

/** @internal
    This function is wrapper function of gRT->GetVariable() with error check.   

    @param *sName          A Null-terminated string that is the name of the vendor's
                             variable.
    @param pGuid           A unique identifier for the vendor.
    @param *pAttributes    If not NULL, a pointer to the memory location to return the
                             attributes bitmask for the variable.
    @param *pDataSize      On input, the size in bytes of the return Data buffer.
                              On output the size of data returned in Data.
    @param **ppData        Pointer to variable's memory location

    @return EFI_SUCCESS            The function completed successfully.
    @return EFI_NOT_FOUND          The variable was not found.
    @return EFI_BUFFER_TOO_SMALL   The DataSize is too small for the result.
    @return EFI_INVALID_PARAMETER  VariableName is NULL.
    @return EFI_INVALID_PARAMETER  VendorGuid is NULL.
    @return EFI_INVALID_PARAMETER  DataSize is NULL.
    @return EFI_INVALID_PARAMETER  The DataSize is not too small and Data is NULL.
    @return EFI_DEVICE_ERROR       The variable could not be retrieved due to a hardware error.
    @return EFI_SECURITY_VIOLATION The variable could not be retrieved due to an authentication failure.

    @endinternal
**/
EFI_STATUS
HddSecGetEfiVariable(
    IN CHAR16 *sName,
    IN EFI_GUID *pGuid,
    OUT UINT32 *pAttributes OPTIONAL,
    IN OUT UINTN *pDataSize,
    OUT VOID **ppData
)
{
    EFI_STATUS Status;
    if (!*ppData) *pDataSize=0;
    Status = gRT->GetVariable(sName, pGuid, pAttributes, pDataSize, *ppData);
    if (!EFI_ERROR(Status)) return Status;
    if (Status==EFI_BUFFER_TOO_SMALL)
    {
        if (*ppData) gBS->FreePool(*ppData);
        
        *ppData = AllocatePool(*pDataSize);
        if (!*ppData) {
            return EFI_OUT_OF_RESOURCES;
        }
        Status = gRT->GetVariable(sName, pGuid, pAttributes, pDataSize, *ppData);
    }
    return Status;
}

/** @internal
    Return the String based on StringId
    
    @param HiiHandle       Handle to HII database
    @param StringId        The string's id, which is unique within PackageList.

    @return EFI_STRING      String is returned based on StringID.
    @return NULL            No String is returned.
    
    @endinternal
**/
EFI_STRING
HddSecHiiGetString (
    IN  EFI_HII_HANDLE  HiiHandle,
    IN  EFI_STRING_ID   StringId
)
{
    EFI_STRING String = NULL;
    UINTN StringSize = 0;
    EFI_STATUS Status;
    CHAR8* PlatformLang = NULL;
    UINTN Size = 0;

    if(HiiString == NULL) {
        Status = gBS->LocateProtocol(&gEfiHiiStringProtocolGuid, NULL, (VOID **) &HiiString);
        if(EFI_ERROR(Status))
            return NULL;
    }

    //language not provided - try platform language
    Status = HddSecGetEfiVariable(L"PlatformLang", &gEfiGlobalVariableGuid, NULL, &Size, (VOID **) &PlatformLang);
    if(!EFI_ERROR(Status)) {
        Status = HiiString->GetString(HiiString, PlatformLang, HiiHandle, StringId, String, &StringSize, NULL);
        if(Status == EFI_BUFFER_TOO_SMALL) {
            Status = gBS->AllocatePool(EfiBootServicesData, StringSize, (VOID**)&String);
            if(!EFI_ERROR(Status))
                Status = HiiString->GetString(HiiString, PlatformLang, HiiHandle, StringId, String, &StringSize, NULL);
        }
        gBS->FreePool(PlatformLang);
    }
    return (EFI_ERROR(Status)) ? NULL : String;
}

/** @internal
    Add/Set the String to HII Database using HiiString Protocol

    @param HiiHandle     Handle to HII database
    @param String        Points to the new null-terminated string.
    @param StringId      On return, contains the new strings id, which is
                          unique within PackageList.

    @return EFI_STRING_ID       String is added to HII Database.
    @return 0                   Error in adding String to HII Database.

    @endinternal
**/
EFI_STRING_ID
HddSecHiiAddStringInternal (
    IN  EFI_HII_HANDLE  HiiHandle,
    IN  CHAR16 *        String,
    IN  EFI_STRING_ID   StringId
)
{
    EFI_STATUS      Status;
    CHAR8*          Languages = NULL;
    UINTN           LangSize = 0;
    CHAR8*          CurrentLanguage;
    BOOLEAN         LastLanguage = FALSE;

    if(HiiString == NULL) {
        Status = gBS->LocateProtocol(&gEfiHiiStringProtocolGuid, NULL, (VOID **) &HiiString);
        if(EFI_ERROR(Status)) {
            return 0;
        }
    }

    if(SupportedLanguages == NULL) {
        Status = HiiString->GetLanguages(HiiString, HiiHandle, Languages, &LangSize);
        if(Status == EFI_BUFFER_TOO_SMALL) {
            Status = gBS->AllocatePool(EfiBootServicesData, LangSize, (VOID**)&Languages);
            if(EFI_ERROR(Status)) {
                //
                //not enough resources to allocate string
                //
                return 0;
            }
            Status = HiiString->GetLanguages(HiiString, HiiHandle, Languages, &LangSize);
            if(EFI_ERROR(Status)) {
                return 0;
            }
        }
        SupportedLanguages=Languages;
    } else {
        Languages=SupportedLanguages;
    }

    while(!LastLanguage) {
        //
        //point CurrentLanguage to start of new language
        //
        CurrentLanguage = Languages;
        while(*Languages != ';' && *Languages != 0)
            Languages++;

        //
        //Last language in language list
        //
        if(*Languages == 0) {
            LastLanguage = TRUE;
            if(StringId == 0) {
                Status = HiiString->NewString(HiiString, HiiHandle, &StringId, CurrentLanguage, NULL, String, NULL);
            } else {
                Status = HiiString->SetString(HiiString, HiiHandle, StringId, CurrentLanguage, String, NULL);
            }
            if(EFI_ERROR(Status)) {
                return 0;
            }
        } else {
            //
            //put null-terminator
            //
            *Languages = 0;
            if(StringId == 0) {
                Status = HiiString->NewString(HiiString, HiiHandle, &StringId, CurrentLanguage, NULL, String, NULL);
            } else {
                Status = HiiString->SetString(HiiString, HiiHandle, StringId, CurrentLanguage, String, NULL);
            }
            *Languages = ';';       //restore original character
            Languages++;
            if(EFI_ERROR(Status)) {
                return 0;
            }
        }
    }
    return StringId;
}

/** @internal
    Add the String to HII Database using HiiString Protocol

    @param HiiHandle      Handle to HII database
    @param String         Points to the new null-terminated string.

    @return EFI_STRING_ID       String is added to HII Database.
    @return 0                   Error in adding String to HII Database.

    @endinternal
**/
EFI_STRING_ID
HddSecHiiAddString (
    IN  EFI_HII_HANDLE  HiiHandle,
    IN  CHAR16 *        String
)
{
    return HddSecHiiAddStringInternal(HiiHandle, String, 0);
}

/** @internal
    Set the String to HII Database using HiiString Protocol

    @param HiiHandle      Handle to HII database
    @param String         Points to the new null-terminated string.
    @param StringId       On return, contains the new strings id, which is
                          unique within PackageList.

    @return EFI_STRING_ID       String is added to HII Database.
    @return 0                   Error in adding String to HII Database.

    @endinternal
**/
EFI_STRING_ID
HddSecHiiSetString (
    IN  EFI_HII_HANDLE  HiiHandle,
    IN  CHAR16 *        String,
    IN  EFI_STRING_ID   StringId
)
{
    return HddSecHiiAddStringInternal(HiiHandle, String, StringId);
}


/** 
    Create EFI_IFR_PASSWORD_OP opcode.

    If OpCodeHandle is NULL, then ASSERT().
    If any reserved bits are set in QuestionFlags, then ASSERT().

    @param[in]  OpCodeHandle          Handle to the buffer of opcodes.
    @param[in]  QuestionId            Question ID
    @param[in]  VarStoreId            Storage ID
    @param[in]  VarOffset             Offset in Storage or String ID of the name (VarName)
                                    for this name/value pair.
    @param[in]  Prompt                String ID for Prompt
    @param[in]  Help                  String ID for Help
    @param[in]  QuestionFlags         Flags in Question Header
    @param[in]  PasswordFlag          Flags for password opcode
    @param[in]  MinSize               String minimum length
    @param[in]  MaxSize               String maximum length
    @param[in]  DefaultsOpCodeHandle  Handle for a buffer of DEFAULT opcodes.  This
                                    is an optional parameter that may be NULL.

    @retval NULL   There is not enough space left in Buffer to add the opcode.
    @retval Other  A pointer to the created opcode.

**/
static
UINT8 *
EFIAPI
HiiCreatePasswordOpCode (
  IN VOID             *OpCodeHandle,
  IN EFI_QUESTION_ID  QuestionId,
  IN EFI_VARSTORE_ID  VarStoreId,
  IN UINT16           VarOffset,
  IN EFI_STRING_ID    Prompt,
  IN EFI_STRING_ID    Help,
  IN UINT8            QuestionFlags,
  //IN UINT8            PasswordFlag,
  IN UINT8            MinSize,
  IN UINT8            MaxSize,
  IN VOID             *DefaultsOpCodeHandle  OPTIONAL
  )
{
  EFI_IFR_PASSWORD  OpCode;
  UINTN           Position;

  ASSERT ((QuestionFlags & (~(EFI_IFR_FLAG_READ_ONLY | EFI_IFR_FLAG_CALLBACK | EFI_IFR_FLAG_RESET_REQUIRED))) == 0);

  ZeroMem (&OpCode, sizeof (OpCode));
  OpCode.Question.Header.Prompt          = Prompt;
  OpCode.Question.Header.Help            = Help;
  OpCode.Question.QuestionId             = QuestionId;
  OpCode.Question.VarStoreId             = VarStoreId;
  OpCode.Question.VarStoreInfo.VarOffset = VarOffset;
  OpCode.Question.Flags                  = QuestionFlags;
  OpCode.MinSize                         = MinSize;
  OpCode.MaxSize                         = MaxSize;
  //OpCode.Flags                           = PasswordFlag;

  if (DefaultsOpCodeHandle == NULL) {
    return InternalHiiCreateOpCodeExtended (OpCodeHandle, &OpCode, EFI_IFR_PASSWORD_OP, sizeof (OpCode), 0, 0);
  }

  Position = InternalHiiOpCodeHandlePosition (OpCodeHandle);
  InternalHiiCreateOpCodeExtended (OpCodeHandle, &OpCode, EFI_IFR_PASSWORD_OP, sizeof (OpCode), 0, 1);
  InternalHiiAppendOpCodes (OpCodeHandle, DefaultsOpCodeHandle);
  HiiCreateEndOpCode (OpCodeHandle);
  return InternalHiiOpCodeHandleBuffer (OpCodeHandle) + Position;
}

/** 
    Create EFI_IFR_SUPPRESS_IF_OP/EFI_IFR_GRAY_OUT_IF_OP opcode with
    TRUE/FALSE condition.

    If OpCodeHandle is NULL, then ASSERT().

    @param[in]  OpCodeHandle          Handle to the buffer of opcodes.
    @param[in]  Value                 Condition value - TRUE/FALSE
    @param[in]  Suppress              1: EFI_IFR_SUPPRESS_IF_OP, 0: EFI_IFR_GRAY_OUT_IF_OP

    @retval NULL   There is not enough space left in Buffer to add the opcode.
    @retval Other  A pointer to the created opcode.

**/
static
UINT8 *
EFIAPI
AmiHiiCreateSuppresGrayVal(
  IN VOID               *OpCodeHandle,
  BOOLEAN               Value,
  BOOLEAN               Suppress    //if TRUE Suppress; False Gray out.
  )
{
    EFI_IFR_OP_HEADER   *Condition;
    EFI_IFR_OP_HEADER   *Header;
    UINT8               *Buffer=NULL;
    UINTN               sz;
//-------------------------------------
    //Allocate buffer for SUPPRESS_IF/GRAY_OUT_IF opcode + EFI_IFR_EQ_ID_VAL for suppress;
    sz=sizeof(EFI_IFR_OP_HEADER)+sizeof(EFI_IFR_OP_HEADER);
    Buffer=AllocateZeroPool(sz);
    if(Buffer==NULL) {
        ASSERT_EFI_ERROR(EFI_OUT_OF_RESOURCES);
        return Buffer;
    }

    //Init Pointers;
    Header=(EFI_IFR_OP_HEADER*)Buffer;
    Condition=(EFI_IFR_OP_HEADER*)(Header+1);

    //Update OpCodes...
    //EFI_IFR_SUPPRESS_IF_OP/EFI_IFR_GRAY_OUT_IF_OP first;
    if(Suppress) Header->OpCode=EFI_IFR_SUPPRESS_IF_OP;
    else Header->OpCode=EFI_IFR_GRAY_OUT_IF_OP;
    Header->Length=sizeof(EFI_IFR_OP_HEADER);
    Header->Scope=1;

    //then goes conditions.
    //First update OpCode Header
    if(Value) Condition->OpCode=EFI_IFR_TRUE_OP;
    else Condition->OpCode=EFI_IFR_FALSE_OP;
    Condition->Scope=0;
    Condition->Length=sizeof(EFI_IFR_OP_HEADER);

    //Here we go...
    return HiiCreateRawOpCodes(OpCodeHandle,Buffer,sz);
}

/** @internal
    This function will dynamically add VFR contents to HDD security BIOS setup page
    using HII library functions.

    @param VOID

    @return VOID

    @endinternal
**/
VOID
HddSecInitDynamicChildFormContents(
        VOID
)
{
    VOID                *StartOpCodeHandle;
    VOID                *EndOpCodeHandle;
    VOID                *YesNoOneOfOptionOpCodeHandle;
    EFI_IFR_GUID_LABEL  *StartLabel;
    EFI_IFR_GUID_LABEL  *EndLabel;
    UINTN               HddIndex;
#if defined(SECURITY_SETUP_ON_SAME_PAGE) && SECURITY_SETUP_ON_SAME_PAGE    
    EFI_STRING          HddName = NULL;
    EFI_STRING_ID       HddNameToken = 0;
    UINTN               TotalHddIndex;
#endif

    StartOpCodeHandle = HiiAllocateOpCodeHandle ();
    EndOpCodeHandle = HiiAllocateOpCodeHandle ();
    YesNoOneOfOptionOpCodeHandle = HiiAllocateOpCodeHandle ();
    
    if((StartOpCodeHandle == NULL) || (EndOpCodeHandle == NULL) || (YesNoOneOfOptionOpCodeHandle == NULL) ) {
        DEBUG((DEBUG_ERROR,"HddSecurity: %a Not enough resources to allocate a new OpCode Handle\n",__FUNCTION__));
        return;
    }
    
    // Create Hii Extended Label OpCode as the start and end opcode
    StartLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (
            StartOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));
    StartLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;

    EndLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (
            EndOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));
    EndLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;

    StartLabel->Number = HDD_SECURITY_DYNAMIC_ITEM_START;
    EndLabel->Number = HDD_SECURITY_DYNAMIC_ITEM_END;


    HiiCreateOneOfOptionOpCode (
            YesNoOneOfOptionOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_YES),
            (EFI_IFR_OPTION_DEFAULT | EFI_IFR_OPTION_DEFAULT_MFG),
            EFI_IFR_NUMERIC_SIZE_1,
            1 );

    HiiCreateOneOfOptionOpCode (
            YesNoOneOfOptionOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_NO),
            0,
            EFI_IFR_NUMERIC_SIZE_1,
            0 );

#if (defined(SECURITY_SETUP_ON_SAME_PAGE) && SECURITY_SETUP_ON_SAME_PAGE) || ALL_HDD_SAME_PW == 0
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_PASSWORD_DESCRIPTION),
            STRING_TOKEN(STR_EMPTY),
            0,0);

    // HDD password description
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_EMPTY),
            STRING_TOKEN(STR_EMPTY),
            0,0);
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_BANNER_ONE),
            STRING_TOKEN(STR_EMPTY),
            0,0);
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_BANNER_TWO),
            STRING_TOKEN(STR_EMPTY),
            0,0);
#if MASTER_PASSWORD_ENABLE
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_BANNER_THREE),
            STRING_TOKEN(STR_EMPTY),
            0,0);
#endif
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_BANNER_FOUR),
            STRING_TOKEN(STR_EMPTY),
            0,0);
#if MASTER_PASSWORD_ENABLE
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_BANNER_FIVE),
            STRING_TOKEN(STR_EMPTY),
            0,0);
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_BANNER_SIX),
            STRING_TOKEN(STR_EMPTY),
            0,0);
#endif
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_BANNER_SEVEN),
            STRING_TOKEN(STR_EMPTY),
            0,0);
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_BANNER_EIGHT),
            STRING_TOKEN(STR_EMPTY),
            0,0);
#if ALL_HDD_SAME_PW
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_BANNER_NINE),
            STRING_TOKEN(STR_EMPTY),
            0,0);
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_BANNER_TEN),
            STRING_TOKEN(STR_EMPTY),
            0,0);
#endif


    //SEPARATOR
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_EMPTY),
            STRING_TOKEN(STR_EMPTY),
            0,0);
#endif

#if defined(SECURITY_SETUP_ON_SAME_PAGE) && SECURITY_SETUP_ON_SAME_PAGE && ALL_HDD_SAME_PW
    AmiHiiCreateSuppresGrayIdVal(StartOpCodeHandle, (EFI_QUESTION_ID)(gHddSecFrozenBaseKey), 1,TRUE);
    HiiCreatePasswordOpCode(
        StartOpCodeHandle,
        (EFI_QUESTION_ID)(gHddSecUserPasswordBaseKey),
        gVarstoreId,
        (UINT16)OFFSET_OF(HDD_SECURITY_CONFIGURATION, HddPassword[0]),
        STRING_TOKEN(STR_HDDSEC_USER_PASSWORD),
        STRING_TOKEN(STR_HDDSEC_USER_PASSWORD_HELP),
        EFI_IFR_FLAG_CALLBACK | EFI_IFR_FLAG_RESET_REQUIRED,
        0,
        32,
        NULL
    );
    //close scope
    AmiHiiTerminateScope(StartOpCodeHandle);
#if defined(DISPLAY_MASTER_PASSWORD) && DISPLAY_MASTER_PASSWORD
    AmiHiiCreateSuppresGrayIdVal(StartOpCodeHandle, (EFI_QUESTION_ID)(gHddSecFrozenBaseKey), 1,TRUE);
    AmiHiiCreateSuppresGrayIdVal(StartOpCodeHandle, (EFI_QUESTION_ID)(gHddSecShowMasterBaseKey), 0,FALSE);
    HiiCreatePasswordOpCode(
        StartOpCodeHandle,
        (EFI_QUESTION_ID)(gHddSecMasterPasswordBaseKey),
        gVarstoreId,
        (UINT16)OFFSET_OF(HDD_SECURITY_CONFIGURATION, HddPassword[1]),
        STRING_TOKEN(STR_HDDSEC_MASTER_PASSWORD),
        STRING_TOKEN(STR_HDDSEC_MASTER_PASSWORD),
        EFI_IFR_FLAG_CALLBACK | EFI_IFR_FLAG_RESET_REQUIRED,
        0,
        32,
        NULL
    );
    //close scope
    AmiHiiTerminateScope(StartOpCodeHandle);
    AmiHiiTerminateScope(StartOpCodeHandle);
#endif
    //SEPARATOR
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_EMPTY),
            STRING_TOKEN(STR_EMPTY),
            0,0);
#endif

    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_PASSWORD_CONFIGURATION),
            STRING_TOKEN(STR_EMPTY),
            0,0);

    //SEPARATOR
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_EMPTY),
            STRING_TOKEN(STR_EMPTY),
            0,0);

#if defined(SECURITY_SETUP_ON_SAME_PAGE) && SECURITY_SETUP_ON_SAME_PAGE
    for(HddIndex = 0, TotalHddIndex=0; (TotalHddIndex < gHddSecurityCount) && (HddIndex < HDD_SECURITY_MAX_HDD_COUNT) \
             && (HddIndex < gValidHddSecurityCount); TotalHddIndex++ ) {

        if( !(gHddSecurityInternalData + TotalHddIndex) ) {
            continue;
        }

        if(gHiiHandle == gHddSecurityInternalData[HddIndex].PostHiiHandle) {
            HddNameToken = gHddSecurityInternalData[HddIndex].PromptToken;
        } else {
            HddName = HddSecHiiGetString(gHddSecurityInternalData[HddIndex].PostHiiHandle, gHddSecurityInternalData[HddIndex].PromptToken);
            HddNameToken = HddSecHiiAddString(gHiiHandle, HddName);
        }

        HiiCreateSubTitleOpCode(StartOpCodeHandle,
                HddNameToken,
                STRING_TOKEN(STR_EMPTY),
                0,0);
#else
        HddIndex = 0;
#endif

    gHddSecSupportedStrIds[HddIndex] = HddSecHiiAddString(gHiiHandle, L"No");
    HiiCreateTextOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_SUPPORTED),
            STRING_TOKEN(STR_EMPTY),
            gHddSecSupportedStrIds[HddIndex]
    );

    gHddSecEnabledStrIds[HddIndex] = HddSecHiiAddString(gHiiHandle, L"No");
    HiiCreateTextOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_ENABLED),
            STRING_TOKEN(STR_EMPTY),
            gHddSecEnabledStrIds[HddIndex]
    );

    gHddSecLockedStrIds[HddIndex] = HddSecHiiAddString(gHiiHandle, L"No");
    HiiCreateTextOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_LOCKED),
            STRING_TOKEN(STR_EMPTY),
            gHddSecLockedStrIds[HddIndex]
    );

    // Suppress by default
    AmiHiiCreateSuppresGrayVal(StartOpCodeHandle, TRUE, TRUE);
    //Now create OneOf OpCode...
    HiiCreateOneOfOpCode (
        StartOpCodeHandle,
        (EFI_QUESTION_ID)(gHddSecFrozenBaseKey + HddIndex),
        gVarstoreId,
        (UINT16)OFFSET_OF(HDD_SECURITY_CONFIGURATION, Frozen[HddIndex]),
        STRING_TOKEN(STR_HDDSEC_FROZEN),
        STRING_TOKEN(STR_EMPTY),
        0,
        EFI_IFR_NUMERIC_SIZE_1,
        YesNoOneOfOptionOpCodeHandle,
        NULL
    );
    //close scope
    AmiHiiTerminateScope(StartOpCodeHandle);

    gHddSecFrozenStrIds[HddIndex] = HddSecHiiAddString(gHiiHandle, L"No");
    HiiCreateTextOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_FROZEN),
            STRING_TOKEN(STR_EMPTY),
            gHddSecFrozenStrIds[HddIndex]
    );

    gHddSecUserPwdStsStrIds[HddIndex] = HddSecHiiAddString(gHiiHandle, L"NOT INSTALLED");
    HiiCreateTextOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_USER_PASSWORD_STS),
            STRING_TOKEN(STR_EMPTY),
            gHddSecUserPwdStsStrIds[HddIndex]
    );

    gHddSecMasterPwdStsStrIds[HddIndex] = HddSecHiiAddString(gHiiHandle, L"NOT INSTALLED");
    HiiCreateTextOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_MASTER_PASSWORD_STS),
            STRING_TOKEN(STR_EMPTY),
            gHddSecMasterPwdStsStrIds[HddIndex]
    );

    // Suppress by default
    AmiHiiCreateSuppresGrayVal(StartOpCodeHandle, TRUE, TRUE);
    //Now create OneOf OpCode...
    HiiCreateOneOfOpCode (
        StartOpCodeHandle,
        (EFI_QUESTION_ID)(gHddSecShowMasterBaseKey + HddIndex),
        gVarstoreId,
        (UINT16)OFFSET_OF(HDD_SECURITY_CONFIGURATION, ShowMaster[HddIndex]),
        STRING_TOKEN(STR_EMPTY),
        STRING_TOKEN(STR_EMPTY),
        0,
        EFI_IFR_NUMERIC_SIZE_1,
        YesNoOneOfOptionOpCodeHandle,
        NULL
    );
    //close scope
    AmiHiiTerminateScope(StartOpCodeHandle);
#if !defined(SECURITY_SETUP_ON_SAME_PAGE) || SECURITY_SETUP_ON_SAME_PAGE == 0
    //SEPARATOR
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_EMPTY),
            STRING_TOKEN(STR_EMPTY),
            0,0);
#endif
#if ALL_HDD_SAME_PW == 0
    AmiHiiCreateSuppresGrayIdVal(StartOpCodeHandle, (EFI_QUESTION_ID)(gHddSecFrozenBaseKey + HddIndex), 1,TRUE);
    HiiCreatePasswordOpCode(
        StartOpCodeHandle,
        (EFI_QUESTION_ID)(gHddSecUserPasswordBaseKey + HddIndex),
        gVarstoreId,
        (UINT16)OFFSET_OF(HDD_SECURITY_CONFIGURATION, HddPassword[0]),
        STRING_TOKEN(STR_HDDSEC_USER_PASSWORD),
        STRING_TOKEN(STR_HDDSEC_USER_PASSWORD_HELP),
        EFI_IFR_FLAG_CALLBACK | EFI_IFR_FLAG_RESET_REQUIRED,
        0,
        32,
        NULL
    );
    //close scope
    AmiHiiTerminateScope(StartOpCodeHandle);

#if defined(DISPLAY_MASTER_PASSWORD) && DISPLAY_MASTER_PASSWORD
    AmiHiiCreateSuppresGrayIdVal(StartOpCodeHandle, (EFI_QUESTION_ID)(gHddSecFrozenBaseKey + HddIndex), 1,TRUE);
    AmiHiiCreateSuppresGrayIdVal(StartOpCodeHandle, (EFI_QUESTION_ID)(gHddSecShowMasterBaseKey + HddIndex), 0,FALSE);
    HiiCreatePasswordOpCode(
        StartOpCodeHandle,
        (EFI_QUESTION_ID)(gHddSecMasterPasswordBaseKey + HddIndex),
        gVarstoreId,
        (UINT16)OFFSET_OF(HDD_SECURITY_CONFIGURATION, HddPassword[1]),
        STRING_TOKEN(STR_HDDSEC_MASTER_PASSWORD),
        STRING_TOKEN(STR_HDDSEC_MASTER_PASSWORD),
        EFI_IFR_FLAG_CALLBACK | EFI_IFR_FLAG_RESET_REQUIRED,
        0,
        32,
        NULL
    );
    //close scope
    AmiHiiTerminateScope(StartOpCodeHandle);
    AmiHiiTerminateScope(StartOpCodeHandle);
#endif
#endif

#if defined(SECURITY_SETUP_ON_SAME_PAGE) && SECURITY_SETUP_ON_SAME_PAGE
        //SEPARATOR
        HiiCreateSubTitleOpCode(StartOpCodeHandle,
                STRING_TOKEN(STR_EMPTY),
                STRING_TOKEN(STR_EMPTY),
                0,0);
        //SEPARATOR
        HiiCreateSubTitleOpCode(StartOpCodeHandle,
                STRING_TOKEN(STR_EMPTY),
                STRING_TOKEN(STR_EMPTY),
                0,0);

        HddIndex++;

    } // end of FOR loop
#endif

    //We are done!!
    HiiUpdateForm (
      gHiiHandle,
      &gSecurityFormsetGuid,
      HDD_SECURITY_DYNAMIC_SETUP_FORM,
      StartOpCodeHandle,
      EndOpCodeHandle
    );


    HiiFreeOpCodeHandle (StartOpCodeHandle);
    HiiFreeOpCodeHandle (EndOpCodeHandle);
    HiiFreeOpCodeHandle (YesNoOneOfOptionOpCodeHandle);


}

/** @internal
    This function will dynamically add VFR contents to HDD security BIOS setup page
    using HII library functions.

    @param VOID

    @return VOID

    @endinternal
**/
VOID
HddSecInitDynamicMainFormContents(
        VOID
)
{
    VOID                *StartOpCodeHandle;
    VOID                *EndOpCodeHandle;
    EFI_IFR_GUID_LABEL  *StartLabel;
    EFI_IFR_GUID_LABEL  *EndLabel;
    UINTN               HddIndex;
#if !(defined SECURITY_SETUP_ON_SAME_PAGE) || SECURITY_SETUP_ON_SAME_PAGE == 0
    EFI_STRING          HddName = NULL;
    EFI_STRING_ID       HddNameToken = 0;
    UINTN               TotalHddIndex;
#endif

    StartOpCodeHandle = HiiAllocateOpCodeHandle ();
    EndOpCodeHandle = HiiAllocateOpCodeHandle ();

    // Create Hii Extended Label OpCode as the start and end opcode
    StartLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (
            StartOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));
    StartLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;

    EndLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (
            EndOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));
    EndLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;

    StartLabel->Number = HDD_SECURITY_DYNAMIC_GOTO_START;
    EndLabel->Number = HDD_SECURITY_DYNAMIC_GOTO_END;

    //SEPARATOR
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_EMPTY),
            STRING_TOKEN(STR_EMPTY),
            0,0);

#if defined(SECURITY_SETUP_ON_SAME_PAGE) && SECURITY_SETUP_ON_SAME_PAGE
    HddIndex = 0;
    // Add goto control
    HiiCreateGotoOpCode (
        StartOpCodeHandle,
        HDD_SECURITY_DYNAMIC_SETUP_FORM,
        STRING_TOKEN(STR_HDDSEC_SECURITY_ALL_HELP),
        STRING_TOKEN(STR_HDDSEC_SECURITY_ALL_HELP),
        EFI_IFR_FLAG_CALLBACK,
        (EFI_QUESTION_ID)(gHddSecGotoBaseKey + HddIndex)
    );
#else
#if ALL_HDD_SAME_PW
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_PASSWORD_DESCRIPTION),
            STRING_TOKEN(STR_EMPTY),
            0,0);

    // HDD password description
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_EMPTY),
            STRING_TOKEN(STR_EMPTY),
            0,0);
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_BANNER_ONE),
            STRING_TOKEN(STR_EMPTY),
            0,0);

    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_BANNER_TWO),
            STRING_TOKEN(STR_EMPTY),
            0,0);
#if MASTER_PASSWORD_ENABLE
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_BANNER_THREE),
            STRING_TOKEN(STR_EMPTY),
            0,0);
#endif
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_BANNER_FOUR),
            STRING_TOKEN(STR_EMPTY),
            0,0);
#if MASTER_PASSWORD_ENABLE
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_BANNER_FIVE),
            STRING_TOKEN(STR_EMPTY),
            0,0);
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_BANNER_SIX),
            STRING_TOKEN(STR_EMPTY),
            0,0);
#endif
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_BANNER_SEVEN),
            STRING_TOKEN(STR_EMPTY),
            0,0);
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_BANNER_EIGHT),
            STRING_TOKEN(STR_EMPTY),
            0,0);
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_BANNER_NINE),
            STRING_TOKEN(STR_EMPTY),
            0,0);
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_BANNER_TEN),
            STRING_TOKEN(STR_EMPTY),
            0,0);

    //SEPARATOR
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_EMPTY),
            STRING_TOKEN(STR_EMPTY),
            0,0);


    AmiHiiCreateSuppresGrayIdVal(StartOpCodeHandle, (EFI_QUESTION_ID)(gHddSecFrozenBaseKey), 1,TRUE);
    HiiCreatePasswordOpCode(
        StartOpCodeHandle,
        (EFI_QUESTION_ID)(gHddSecUserPasswordBaseKey),
        gVarstoreId,
        (UINT16)OFFSET_OF(HDD_SECURITY_CONFIGURATION, HddPassword[0]),
        STRING_TOKEN(STR_HDDSEC_USER_PASSWORD),
        STRING_TOKEN(STR_HDDSEC_USER_PASSWORD_HELP),
        EFI_IFR_FLAG_CALLBACK | EFI_IFR_FLAG_RESET_REQUIRED,
        0,
        32,
        NULL
    );
    //close scope
    AmiHiiTerminateScope(StartOpCodeHandle);

#if defined(DISPLAY_MASTER_PASSWORD) && DISPLAY_MASTER_PASSWORD
    AmiHiiCreateSuppresGrayIdVal(StartOpCodeHandle, (EFI_QUESTION_ID)(gHddSecFrozenBaseKey), 1,TRUE);
    AmiHiiCreateSuppresGrayIdVal(StartOpCodeHandle, (EFI_QUESTION_ID)(gHddSecShowMasterBaseKey), 0,FALSE);
    HiiCreatePasswordOpCode(
        StartOpCodeHandle,
        (EFI_QUESTION_ID)(gHddSecMasterPasswordBaseKey),
        gVarstoreId,
        (UINT16)OFFSET_OF(HDD_SECURITY_CONFIGURATION, HddPassword[1]),
        STRING_TOKEN(STR_HDDSEC_MASTER_PASSWORD),
        STRING_TOKEN(STR_HDDSEC_MASTER_PASSWORD),
        EFI_IFR_FLAG_CALLBACK | EFI_IFR_FLAG_RESET_REQUIRED,
        0,
        32,
        NULL
    );
    //close scope
    AmiHiiTerminateScope(StartOpCodeHandle);
    AmiHiiTerminateScope(StartOpCodeHandle);
#endif

    //SEPARATOR
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_EMPTY),
            STRING_TOKEN(STR_EMPTY),
            0,0);
    //SEPARATOR
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_EMPTY),
            STRING_TOKEN(STR_EMPTY),
            0,0);
#endif

    HiiCreateSubTitleOpCode(StartOpCodeHandle,
            STRING_TOKEN(STR_HDDSEC_SECURITY_CONFIGURATION),
            STRING_TOKEN(STR_EMPTY),
            0,0);

    for(HddIndex = 0, TotalHddIndex=0; (TotalHddIndex < gHddSecurityCount) && (HddIndex < HDD_SECURITY_MAX_HDD_COUNT) \
                 && (HddIndex < gValidHddSecurityCount); TotalHddIndex++ ) {

        if( (gHddSecurityInternalData + TotalHddIndex) == NULL ) {
            continue;
        }

        if(gHiiHandle == gHddSecurityInternalData[HddIndex].PostHiiHandle) {
            HddNameToken = gHddSecurityInternalData[HddIndex].PromptToken;
        } else {
            HddName = HddSecHiiGetString(gHddSecurityInternalData[HddIndex].PostHiiHandle, gHddSecurityInternalData[HddIndex].PromptToken);
            HddNameToken = HddSecHiiAddString(gHiiHandle, HddName);
        }

        // Add goto control
        HiiCreateGotoOpCode (
            StartOpCodeHandle,
            HDD_SECURITY_DYNAMIC_SETUP_FORM,
            HddNameToken,
            STRING_TOKEN(STR_HDDSEC_SECURITY_HELP),
            EFI_IFR_FLAG_CALLBACK,
            (EFI_QUESTION_ID)(gHddSecGotoBaseKey + HddIndex)
        );

        HddIndex++;
    }
#endif

    //We are done!!
    HiiUpdateForm (
      gHiiHandle,
      &gSecurityFormsetGuid,
      SECURITY_MAIN,
      StartOpCodeHandle,
      EndOpCodeHandle
    );

    if (StartOpCodeHandle != NULL)
    {
        HiiFreeOpCodeHandle (StartOpCodeHandle);
        HiiFreeOpCodeHandle (EndOpCodeHandle);
    }

}

/** 
    Notification function for "Load Default" action in BIOS setup. This function
    will re-initialize the HDD security setup data.

    @param  Event                 Event whose notification function is being invoked.
    @param  Context               The pointer to the notification function's context,
                                  which is implementation-dependent.
    @return VOID

**/
static
VOID
EFIAPI
HddSecurityLoadSetupDefaults (
        IN EFI_EVENT Event,
        IN VOID *Context
)
{
    HddSecurityRefreshSetupData(gCurrentHddIndex);
}

/** @internal
    This function initializes HDD Security HiiHandle and IFR contents.

    @param  HiiHandle   Handle to HII database
    @param  Class       Indicates the setup class

    @retval VOID

    @endinternal
**/

VOID
InitHddSecurityDynamicIfrContents (
    EFI_HII_HANDLE  HiiHandle,
    UINT16          Class
)
{
    
    EFI_STATUS    Status;
    UINTN         BufferSize = sizeof(UINTN);
    VOID          *NotifyRegistration;
    EFI_EVENT     NotifyEvent;
    EFI_HANDLE    TseHddNotify;
    EFI_GUID      AmiTseHddNotifyGuid = AMI_TSE_HDD_NOTIFY_GUID;
       
    gHiiHandle = HiiHandle;
    
    Status = gBS->LocateHandle ( ByProtocol,
                                 &AmiTseHddNotifyGuid,
                                 NULL,
                                 &BufferSize,
                                 &TseHddNotify );
       
       if (Status == EFI_SUCCESS) {
       //If HDD post data already initialized then Init Setup Strings here.
           AmiTseHddNotifyInitString (NULL, NULL);        
       } else if (Status == EFI_NOT_FOUND) {
           //Else register notify for AmiTseHddNotifyGuid
           Status = gBS->CreateEvent( EFI_EVENT_NOTIFY_SIGNAL,
                                      TPL_CALLBACK,
                                      AmiTseHddNotifyInitString,
                                      &NotifyRegistration,
                                      &NotifyEvent );
           if(EFI_ERROR(Status)) {
              return;
           }
           
           Status = gBS->RegisterProtocolNotify( &AmiTseHddNotifyGuid,
                                        NotifyEvent,
                                        &NotifyRegistration );
           ASSERT_EFI_ERROR(Status);
       }
}

/** 
    This Event notifies String initialization for HddSecurity for  can be processed
    
    @param  Event                 Event whose notification function is being invoked.
    @param  Context               The pointer to the notification function's context,
                                  which is implementation-dependent.

    @retval VOID

**/

VOID 
EFIAPI
AmiTseHddNotifyInitString(
    IN EFI_EVENT Event, 
    IN VOID *Context
)
{
    EFI_STATUS                Status;
    EFI_STRING                 vname = L"HddSecDynamicSetup";
    EFI_GUID                   vguid = HDD_SECURITY_CONFIGURATION_VARIABLE_GUID;
    UINTN                      vsize =  sizeof(HDD_SECURITY_CONFIGURATION);
    HDD_SECURITY_CONFIGURATION vdata;

    Status = gRT->SetVariable(vname, &vguid,
                              EFI_VARIABLE_BOOTSERVICE_ACCESS,
                              vsize, &vdata);
    ASSERT_EFI_ERROR (Status);

    // Initialize HDD security internal data structure and gHddSecurityCount
    gHddSecurityCount = InitHddSecurityInternalDataPtr( );
    
    DEBUG((DEBUG_VERBOSE,"HddSecurity: Validated Hdd Count = %d\n", gHddSecurityCount));

    if( 0 == gHddSecurityCount) { // No HDD detected
        return;
    }

    HddSecInitDynamicChildFormContents();
    HddSecInitDynamicMainFormContents();

    if(gHddSecurityLoadSetupDefaultsEvent == NULL) {
      Status = gBS->CreateEventEx(
                     EVT_NOTIFY_SIGNAL,
                     TPL_CALLBACK,
                     HddSecurityLoadSetupDefaults,
                     NULL,
                     &gHddSecurityLoadSetupDefaultsGuid,
                     &gHddSecurityLoadSetupDefaultsEvent);
      ASSERT_EFI_ERROR(Status);
    }

}


/** @internal
    Return the Security Status Information

    @param *HddSecurityProtocol    Pointer to AMI_HDD_SECURITY_PROTOCOL
    @param *ReqStatus              Pointer to Mask security status 
    @param Mask                    Flags for security.
    
    @retval TRUE        Security Status Information is valid.
    @retval FALSE       Unable to get security status
    
    @note
        1. Security Status Informations.
          Bit 0 : Security Supported
          Bit 1 : Security Enabled
          Bit 2 : Security Locked
          Bit 3 : Security Frozen
    @endinternal
**/
BOOLEAN
HddSecurityCheckSecurityStatus (
    IN  AMI_HDD_SECURITY_PROTOCOL   *HddSecurityProtocol,
    IN  OUT BOOLEAN                 *ReqStatus,
    IN  UINT16                      Mask
)
{
    UINT16      SecurityStatus = 0;
    EFI_STATUS  Status;

    //get the security status of the device
    Status = HddSecurityProtocol->ReturnSecurityStatus( HddSecurityProtocol, &SecurityStatus );

    if ( EFI_ERROR( Status ))
        return FALSE; // Unable to get security status
    // Mask security status based on supplied mask data
    *ReqStatus = (BOOLEAN)((SecurityStatus & Mask) ? TRUE : FALSE );
    return TRUE;
}

/** @internal
    Updates the password for the current HDD alone.

    @param Index            Number of Hard Disk connected.
    @param *Password        Pointer to Password for security
    @param bCheckUser       Check for user/Master Password: 0/1

    @retval TRUE     Password set.
    @retval FALSE    Error in setting Password.

    @endinternal
**/
BOOLEAN
HddSecurityUpdateHdd (
    UINT32      Index,
    CHAR16      *Password,
    BOOLEAN     bCheckUser
)
{
    AMI_HDD_SECURITY_PROTOCOL   *HddSecurityProtocol = NULL;
    UINT16                      Control              = bCheckUser ? 0 : 1;
    UINT8                       RevisionCode         = 0;
    BOOLEAN                     Locked, Enabled;
    EFI_STATUS                  Status = EFI_UNSUPPORTED;
    UINT8                       Buffer[IDE_PASSWORD_LENGTH + 1];
    #if !SETUP_SAME_SYS_HDD_PW
    UINTN                       ii;
    #endif
    HDD_SECURITY_INTERNAL_DATA  *DataPtr;

#if defined(SETUP_PASSWORD_NON_CASE_SENSITIVE) && SETUP_PASSWORD_NON_CASE_SENSITIVE
    UpdatePasswordToNonCaseSensitive(Password, StrLen(Password));
#endif

    DataPtr = &gHddSecurityInternalData[Index];

    if ( DataPtr == NULL ) {
        return FALSE;
    }
    HddSecurityProtocol = DataPtr->HddSecurityProtocol;

    //get the status of the device
    if ( !(
            HddSecurityCheckSecurityStatus(
                                     HddSecurityProtocol, &Locked,
                                     SECURITY_LOCKED_MASK )
             && HddSecurityCheckSecurityStatus( 
                                     HddSecurityProtocol, &Enabled,
                                     SECURITY_ENABLED_MASK ))) {
        return FALSE;
    }

    if ( !Locked ) {
        if ( Password[0] == 0 ) {
            //empty string is entered -> disable password
            Status = HddSecurityProtocol->SecurityDisablePassword(
                HddSecurityProtocol,
                Control,
                gHddSecurityInternalData[Index].PWD );
        } else {
            //set new password
            ZeroMem (&Buffer, IDE_PASSWORD_LENGTH + 1);
            #if !SETUP_SAME_SYS_HDD_PW

            for ( ii = 0; ii < IDE_PASSWORD_LENGTH + 1; ii++ ) {
                Buffer[ii] = (UINT8)Password[ii];

                if ( Password[ii] == L'\0' ) {
                    break;
                }
            }// end of for
            #else
            CopyMem( Buffer, Password, IDE_PASSWORD_LENGTH + 1 );
            #endif

            Status = HddSecurityProtocol->SecuritySetPassword(
                HddSecurityProtocol,
                Control,
                Buffer,
                RevisionCode );
        }
    }// end if(!Locked)

    if ( EFI_ERROR( Status )) {
        return FALSE;
    }

    return TRUE;
}

/** @internal
    Updates the HDD password for all the HDDs present.

    @param Index            Number of Hard Disk connected.
    @param *Password        Pointer to Password for security
    @param bCheckUser       Check for user/Master Password: 0/1

    @return TRUE     Password set.
    @return FALSE    Error in setting Password.

    @endinternal
**/
BOOLEAN
HddSecurityUpdateAllHdd (
    UINT32      Index,
    CHAR16      *Password,
    BOOLEAN     bCheckUser
)
{
    UINTN       i;
    BOOLEAN     Status = FALSE;
        for ( i = 0; i < gHddSecurityCount; i++ ) {
            Status = HddSecurityUpdateHdd( (UINT32)i, Password, bCheckUser);
        }
    return Status;
}

/** @internal
    Hook function to update the password for the HDDs based
    on the token ALL_HDD_SAME_PW.

    @param Index            Number of Hard Disk connected.
    @param *Password        Pointer to Password for security
    @param bCheckUser       Check for user/Master Password: 0/1

    @return TRUE     Password set.
    @return FALSE    Error in setting Password.

    @endinternal
**/
BOOLEAN
HddSecurityUpdate (
    UINT32      Index,
    CHAR16      *Password,
    BOOLEAN     bCheckUser
)
{
    #if ALL_HDD_SAME_PW
     return HddSecurityUpdateAllHdd( Index, Password, bCheckUser);
    #else
     return HddSecurityUpdateHdd( Index, Password, bCheckUser);
    #endif
}

/** @internal
    Validates the password for the current HDD alone.

    @param *Password        Pointer to Password for security.
    @param *Ptr             
    @param bCheckUser       Check for user/Master Password: 0/1

    @retval EFI_SUCCESS         Password for current HDD is validated successfully.
    @retval EFI_ACCESS_DENIED   Access to unlock Hdd is denied.

    @endinternal
**/
EFI_STATUS
HddSecurityAuthenticateHdd (
    CHAR16  *Password,
    VOID    * Ptr,
    BOOLEAN bCheckUser
)
{
    UINT16            Control = 0;
    EFI_STATUS        Status;
    UINT8             Buffer[IDE_PASSWORD_LENGTH + 1];

    #if !SETUP_SAME_SYS_HDD_PW
    UINTN             i;
    #endif

    HDD_SECURITY_INTERNAL_DATA * DataPtr = (HDD_SECURITY_INTERNAL_DATA*)Ptr;

#if defined(SETUP_PASSWORD_NON_CASE_SENSITIVE) && SETUP_PASSWORD_NON_CASE_SENSITIVE
    UpdatePasswordToNonCaseSensitive(Password, StrLen(Password));
#endif

    ZeroMem (&Buffer, IDE_PASSWORD_LENGTH + 1);

    #if !SETUP_SAME_SYS_HDD_PW

    for ( i = 0; i < IDE_PASSWORD_LENGTH + 1; i++ ) {
        Buffer[i] = (UINT8)Password[i];

        if ( Password[i] == L'\0' ) {
            break;
        }
    }
    #else
    CopyMem( Buffer, Password, IDE_PASSWORD_LENGTH + 1 );
    #endif

    Control = bCheckUser ? 0 : 1;

    Status = (DataPtr->HddSecurityProtocol)->SecurityUnlockPassword(
        DataPtr->HddSecurityProtocol,
        Control,
        Buffer );

    if ( EFI_ERROR( Status )) {
        return EFI_ACCESS_DENIED;
    }

    //save password in case we need to disable it during the setup
    CopyMem( &(DataPtr->PWD), &Buffer, IDE_PASSWORD_LENGTH + 1 );
//    DataPtr->Locked = FALSE;

    if ( !bCheckUser ) {
        DataPtr->LoggedInAsMaster = TRUE;
    }

    return EFI_SUCCESS;
}

/** @internal
    Validates the password for all the HDDs Present.

    @param *Password        Pointer to Password for security
    @param *Ptr             Pointer to Index of HDD
    @param bCheckUser       Check for user/Master Password: 0/1

    @return EFI_SUCCESS      Password validation is success.
    @return EFI_NOT_FOUND    Security internal data is not available for the drives.

    @endinternal
**/
EFI_STATUS
HddSecurityAuthenticateAllHdd (
    CHAR16  *Password,
    VOID    * Ptr,
    BOOLEAN bCheckUser
)
{
    HDD_SECURITY_INTERNAL_DATA *DataPtr;
    UINTN i;
    EFI_STATUS        Status=EFI_NOT_FOUND;

    //For all drives
    DataPtr = gHddSecurityInternalData;

    if(DataPtr == NULL) {
        return EFI_NOT_FOUND;
    }

    for ( i = 0; i < gHddSecurityCount; i++ ) {

        Status = HddSecurityAuthenticateHdd( Password,
                                          DataPtr,
                                          bCheckUser );
        if ( EFI_SUCCESS != Status ) {
            // Unlock failed.
            ReportStatusCode (
                        EFI_ERROR_CODE | EFI_ERROR_MAJOR,
                        DXE_INVALID_IDE_PASSWORD);
        }
        DataPtr++;
    }
    return Status;
}

/** @internal
    Hook function to validate Password for the HDDs based on
    the token ALL_HDD_SAME_PW

    @param *Password        Pointer to Password for security
    @param *Ptr             Pointer to Index of HDD
    @param bCheckUser       Check for user/Master Password: 0/1

    @return EFI_SUCCESS      Password validation is success.
    @return EFI_NOT_FOUND    Security internal data is not available.

    @endinternal
**/
EFI_STATUS
HddSecurityAuthenticate (
    CHAR16  *Password,
    VOID    * Ptr,
    BOOLEAN bCheckUser
)
{
    #if ALL_HDD_SAME_PW
     return HddSecurityAuthenticateAllHdd( Password, Ptr, bCheckUser);
    #else
     return HddSecurityAuthenticateHdd( Password, Ptr, bCheckUser);
    #endif
}

/** @internal
    Initializes the structure HDD_SECURITY_CONFIG for the current
    HDD if the data pointer to the structure HDD_SECURITY_INTERNAL_DATA is
    initialized already.

    @param *TempHddSecurityConfig    Pointer to HDD_SECURITY_CONFIG
    @param  value                    Number of HDD connected.
    
    @return VOID

    @endinternal
**/
VOID
HddSecurityUpdateSetupDataByHddIndex(
    VOID    *TempHddSecurityConfig,
    UINTN   value
)
{
    HDD_SECURITY_INTERNAL_DATA    *DataPtr             = NULL;
    AMI_HDD_SECURITY_PROTOCOL     *HddSecurityProtocol = NULL;
    BOOLEAN                       Status;
    UINT32                        IdePasswordFlags = 0;
    EFI_STATUS                    ReturnStatus;
    HDD_SECURITY_CONFIGURATION           *HddSecurityConfig
        = (HDD_SECURITY_CONFIGURATION*)TempHddSecurityConfig;

    //Set current HDD security page
    DataPtr = (HDD_SECURITY_INTERNAL_DATA*)&gHddSecurityInternalData[value];
#if !defined(SECURITY_SETUP_ON_SAME_PAGE) || SECURITY_SETUP_ON_SAME_PAGE == 0
    value = 0;
#endif

    if ( DataPtr ) {
        HddSecurityProtocol = DataPtr->HddSecurityProtocol;

        HddSecurityCheckSecurityStatus(
            HddSecurityProtocol,
            &Status,
            SECURITY_SUPPORTED_MASK );
        HddSecurityConfig->Supported[value] = Status ? 1 : 0;
        HddSecurityCheckSecurityStatus(
            HddSecurityProtocol,
            &Status,
            SECURITY_ENABLED_MASK );
        HddSecurityConfig->Enabled[value] = Status ? 1 : 0;
        HddSecurityCheckSecurityStatus(
            HddSecurityProtocol,
            &Status,
            SECURITY_LOCKED_MASK );
        HddSecurityConfig->Locked[value] = Status ? 1 : 0;
        HddSecurityCheckSecurityStatus(
            HddSecurityProtocol,
            &Status,
            SECURITY_FROZEN_MASK );
        HddSecurityConfig->Frozen[value] = Status ? 1 : 0;
        ReturnStatus         = HddSecurityProtocol->ReturnIdePasswordFlags(
            HddSecurityProtocol,
            &IdePasswordFlags );

        if ( EFI_ERROR( ReturnStatus )) {
            return;
        }

        HddSecurityConfig->UserPasswordStatus[value]
            = (IdePasswordFlags & 0x00020000) ? 1 : 0;
        HddSecurityConfig->MasterPasswordStatus[value]
            = (IdePasswordFlags & 0x00010000) ? 1 : 0;

        HddSecurityConfig->ShowMaster[value] = 0x0000;

        if ( HddSecurityConfig->Locked[value] &&  HddSecurityConfig->MasterPasswordStatus[value]) {
            HddSecurityConfig->ShowMaster[value] = 0x0001;
        } else if ( (DataPtr->LoggedInAsMaster)) {
            HddSecurityConfig->ShowMaster[value] = 0x0001;
        } else if ( !(HddSecurityConfig->UserPasswordStatus[value])) {
            HddSecurityConfig->ShowMaster[value] = 0x0001;
        }

        HddSecHiiSetString(gHiiHandle, HddSecurityConfig->Supported[value]  ? L"Yes" : L"No", gHddSecSupportedStrIds[value]);
        HddSecHiiSetString(gHiiHandle, HddSecurityConfig->Enabled[value]  ? L"Yes" : L"No", gHddSecEnabledStrIds[value]);
        HddSecHiiSetString(gHiiHandle, HddSecurityConfig->Locked[value]  ? L"Yes" : L"No", gHddSecLockedStrIds[value]);
        HddSecHiiSetString(gHiiHandle, HddSecurityConfig->Frozen[value]  ? L"Yes" : L"No", gHddSecFrozenStrIds[value]);
        HddSecHiiSetString(gHiiHandle, HddSecurityConfig->UserPasswordStatus[value]  ? \
                                                        L"INSTALLED" : L"NOT INSTALLED", gHddSecUserPwdStsStrIds[value]);
        HddSecHiiSetString(gHiiHandle, HddSecurityConfig->MasterPasswordStatus[value]  ? \
                                                        L"INSTALLED" : L"NOT INSTALLED", gHddSecMasterPwdStsStrIds[value]);
    }// end if
    return;
}

/** @internal
    Initializes the structure HDD_SECURITY_CONFIG for all the
    HDDs present if the data pointer to the structure
    HDD_SECURITY_INTERNAL_DATA is initialized already.

    @param *HddSecurityConfig     Pointer to HDD_SECURITY_CONFIG
    @param value                  Number of HDD connected.

    @return VOID

    @endinternal
**/
VOID
HddSecurityUpdateSetupDataForAllHdd(
    VOID    *HddSecurityConfig,
    UINTN   value
)
{
    UINTN i;

    for ( i = 0; i < gHddSecurityCount; i++ ) {
        HddSecurityUpdateSetupDataByHddIndex( HddSecurityConfig, i);
    }
    return;
}

/** @internal
    Hook function to Initialize the structure HDD_SECURITY_CONFIG
    for the HDDs based on the token ALL_HDD_SAME_PW.

    @param *HddSecurityConfig    Pointer to HDD_SECURITY_CONFIG
    @param  value                Number of HDD connected.

    @return VOID

    @endinternal
**/
VOID
HddSecurityUpdateSetupData(
    VOID    *HddSecurityConfig,
    UINTN   value
)
{
    #if ALL_HDD_SAME_PW
    HddSecurityUpdateSetupDataForAllHdd( HddSecurityConfig, value);
    #else
    HddSecurityUpdateSetupDataByHddIndex( HddSecurityConfig, value);
    #endif

}

/** @internal
    Function to update the setup configuration page after HDD password update

    @param HddIndex         Number of Hard Disk connected.

    @return VOID

    @endinternal
**/
VOID
HddSecurityRefreshSetupData (
        UINTN               HddIndex
)
{
    EFI_STATUS          Status;

    // Allocate memory for setup configuration data
    if(NULL == gHddSecurityConfig) {
        Status = gBS->AllocatePool( EfiBootServicesData,
                                    sizeof(HDD_SECURITY_CONFIGURATION),
                                    (VOID**)&gHddSecurityConfig);
        if(EFI_ERROR(Status) || NULL == gHddSecurityConfig) {
            return;
        }
    }

    gValidHddSecurityCount = InitHddSecurityInternalDataPtr( );
    
    if(HddIndex == 0xFFFF) {
        // Update setup data for all HDDs
        HddSecurityUpdateSetupDataForAllHdd( (VOID*)gHddSecurityConfig, HddIndex );
    } else {
        HddSecurityUpdateSetupData( (VOID*)gHddSecurityConfig, HddIndex );
    }

    // Set the new setup configuration data
    Status = gRT->SetVariable(L"HddSecDynamicSetup",
                    &gHddSecurityConfigurationGuid,
                    EFI_VARIABLE_BOOTSERVICE_ACCESS,
                    sizeof(HDD_SECURITY_CONFIGURATION),
                    gHddSecurityConfig);
    
    ASSERT_EFI_ERROR (Status);

    // Refresh browser data
    HiiSetBrowserData (
                &gHddSecurityConfigurationGuid,
                L"HddSecDynamicSetup",
                sizeof (HDD_SECURITY_CONFIGURATION),
                (UINT8 *)gHddSecurityConfig,
                NULL );

}

/**
    Notification function for "Esc pressed" action in BIOS setup.

    @param EFI_EVENT Event - Event to signal
    @param VOID* Context - Event specific context

    @retval VOID

**/
STATIC
VOID 
EFIAPI
NotifyEscPressed(
    IN EFI_EVENT Event, 
    IN VOID *Context
)
{
    gHddSecIsEscPressed = TRUE;
    return;
}

/** @internal
    Fills the password buffer with the random number
    generated using GetRandomNumber64()

    @param  Buffer       Pointer to Password buffer.
    @param  size         Size of the buffer.

    @return VOID
    
    @endinternal
**/
STATIC
VOID
FillRandNoInPwdBuffer(
    UINT64 *Buffer, 
    UINT8  size
)
{
    UINT64     RandNo;
    UINT8      i;
    UINT8      *TempBuffer;
    UINT8      Remainder = size % 8;

    if(Buffer == NULL || size == 0)
        return;
    // Fill the buffer in multiples of eight as
    // we are getting eight byte random number
    for(i= 0; i < (size/8); i++) {
        GET_RANDOM_NUMBER_64(&RandNo);
        *Buffer = RandNo;
        Buffer++;
    }
    // Fill the remaining buffer byte by byte
    if(Remainder) {
        TempBuffer = (UINT8*)Buffer;
        GET_RANDOM_NUMBER_64(&RandNo);
        
        while(Remainder) {
          *TempBuffer = (UINT8)RandNo;
          TempBuffer++;
          RandNo = RShiftU64 (RandNo, 8);
          Remainder--;
        }
    }
    return;
}

/** @internal
    This function handles password operations (check/validate/change/clear)
    for all HDD password fields

    @param HiiHandle           HII handle of formset
    @param Class               class of formset
    @param SubClass            subclass of formset
    @param Key                 Id of setup control

   @retval EFI_UNSUPPORTED     Browser actions not supported.

    @note
    Case1: Check password status
        EFI_SUCCESS      No password
        EFI_NOT_FOUND    Password exists
    Case2: Validate password
        EFI_SUCCESS      Password is correct
        EFI_NOT_READY    Password is wrong
    Case3: Set/Clear password
        EFI_SUCCESS      Operation successful
        EFI_NOT_READY    Operation failed
        
    @endinternal
**/

EFI_STATUS
HddSecurityDynamicSetupPasswordCallback (
    IN EFI_HII_HANDLE       HiiHandle,
    IN UINT16               Class,
    IN UINT16               SubClass,
    IN UINT16               Key
)
{
    EFI_STATUS                  Status;
    CALLBACK_PARAMETERS         *CallbackParameters;
    CHAR16                      PasswordBuffer[IDE_PASSWORD_LENGTH+1];
    CHAR16                      *PasswordBufferPtr = NULL;
    static CHAR16               OldPasswordBuffer[IDE_PASSWORD_LENGTH+1];
    BOOLEAN                     bCheckUser = FALSE;
    BOOLEAN                     IsSecurityEnabled = FALSE;
    static BOOLEAN              IsPasswordValidated = FALSE;
    static BOOLEAN              NoPasswordExistedOnFirstCall = FALSE;
    static UINTN                LastHardDiskNumber = 0xFFFF;
    UINTN                       CurrentHardDiskNumber;
    UINTN                       size;
    VOID                        *DataPtr;

    // Get actual parameter passed by browser
    CallbackParameters = GetCallbackParameters();

    // Check for supported browser actions
    if(!CallbackParameters || ((CallbackParameters->Action != EFI_BROWSER_ACTION_CHANGING) && \
          (CallbackParameters->Action != EFI_BROWSER_ACTION_CHANGED) && (CallbackParameters->Action != EFI_BROWSER_ACTION_DEFAULT_STANDARD))) {
        return EFI_UNSUPPORTED;
    }

    // Always return success here
    if((CallbackParameters->Action == EFI_BROWSER_ACTION_CHANGED) || (CallbackParameters->Action == EFI_BROWSER_ACTION_DEFAULT_STANDARD )) {
        return EFI_SUCCESS;
    }

    // Check which password field was selected
#if (defined(SECURITY_SETUP_ON_SAME_PAGE) && SECURITY_SETUP_ON_SAME_PAGE) || ALL_HDD_SAME_PW
        if(gHddSecUserPasswordBaseKey <= Key && Key < gHddSecUserPasswordBaseKey + HDD_SECURITY_MAX_HDD_COUNT) {
            bCheckUser = TRUE;
            CurrentHardDiskNumber = Key - gHddSecUserPasswordBaseKey;
        } else if (gHddSecMasterPasswordBaseKey <= Key && Key < gHddSecMasterPasswordBaseKey + HDD_SECURITY_MAX_HDD_COUNT) {
            bCheckUser = FALSE;
            CurrentHardDiskNumber = Key - gHddSecMasterPasswordBaseKey;
        } else {
            CurrentHardDiskNumber = 0xFFFF;
            LastHardDiskNumber = 0xFFFF;
        }
#else
        if(gHddSecUserPasswordBaseKey == Key) {
            bCheckUser = TRUE;
            CurrentHardDiskNumber = gCurrentHddIndex;
        } else if (gHddSecMasterPasswordBaseKey == Key) {
            bCheckUser = FALSE;
            CurrentHardDiskNumber = gCurrentHddIndex;
        } else {
            CurrentHardDiskNumber = 0xFFFF;
            LastHardDiskNumber = 0xFFFF;
        }
#endif

    // Not a valid HDD number
    if( CurrentHardDiskNumber == 0xFFFF ) {
        return EFI_NOT_FOUND;
    }

    // Just to make sure that two subsequent calls are for same HDD
    if(LastHardDiskNumber != 0xFFFF && LastHardDiskNumber != CurrentHardDiskNumber) {
        IsPasswordValidated = FALSE;
        LastHardDiskNumber = 0xFFFF;
        NoPasswordExistedOnFirstCall = FALSE;
        ZeroMem((VOID *)OldPasswordBuffer,sizeof(OldPasswordBuffer));
    }

    // Allocate memory for setup data
    if(NULL == gHddSecurityConfig) {
        Status = gBS->AllocatePool( EfiBootServicesData,
                                    sizeof(HDD_SECURITY_CONFIGURATION),
                                    (VOID**)&gHddSecurityConfig);
        if(EFI_ERROR(Status) || NULL == gHddSecurityConfig) {
            return EFI_NOT_FOUND;
        }
    }

    // Get setup/browser data
    size = sizeof(HDD_SECURITY_CONFIGURATION);
    if (!HiiGetBrowserData (
                        &gHddSecurityConfigurationGuid,
                        L"HddSecDynamicSetup",
                        size,
                        (UINT8 *)gHddSecurityConfig )) {
        return EFI_NOT_FOUND;
    }
    
    if (gHddSecEscNotifyEvent == NULL) {
        //register notify for gTseEscOnPwdPromptGuid
        Status = gBS->CreateEvent( EFI_EVENT_NOTIFY_SIGNAL,
                                   TPL_CALLBACK,
                                   NotifyEscPressed,
                                   &gHddSecEscNotifyRegistration,
                                   &gHddSecEscNotifyEvent );
        if(EFI_ERROR(Status)) {
            return Status;
        }
          
        Status = gBS->RegisterProtocolNotify( &gHddSecEscOnPwdPromptGuid,
                                     gHddSecEscNotifyEvent,
                                     &gHddSecEscNotifyRegistration );
        if(EFI_ERROR(Status)) {
            return Status;
        }
    }

#if defined(SECURITY_SETUP_ON_SAME_PAGE) && SECURITY_SETUP_ON_SAME_PAGE
    IsSecurityEnabled = gHddSecurityConfig->Enabled[CurrentHardDiskNumber] ? TRUE : FALSE;
#else
    IsSecurityEnabled = gHddSecurityConfig->Enabled[0] ? TRUE : FALSE;
#endif

    // Get string from HII database using input string token
    if (CallbackParameters->Value->string != 0) {
        size = sizeof(PasswordBuffer);
        PasswordBufferPtr = HddSecHiiGetString (
                                          HiiHandle,
                                          CallbackParameters->Value->string);
        if (PasswordBufferPtr != NULL)
            CopyMem (PasswordBuffer, PasswordBufferPtr, size);
        
        if (EFI_ERROR(Status)) {
            return EFI_NOT_FOUND;
        }
    } else {
        return EFI_NOT_FOUND;
    }

    // Return password status
    if (PasswordBuffer[0] == L'\0' && (IsPasswordValidated == FALSE) && (NoPasswordExistedOnFirstCall == FALSE)) {
        LastHardDiskNumber = CurrentHardDiskNumber;
        // Initializing the OldPasswordBuffer to zeros for handling the callback 
        // when Esc is pressed
        ZeroMem((VOID *)OldPasswordBuffer,sizeof(OldPasswordBuffer));
        // If Esc is pressed reset the flag
        gHddSecIsEscPressed = FALSE;
        if(IsSecurityEnabled == TRUE) {
            NoPasswordExistedOnFirstCall = FALSE;
            return EFI_NOT_FOUND;   // Pre-existing password
        }
        else {
            NoPasswordExistedOnFirstCall = TRUE;
            return EFI_SUCCESS;    // No pre-existing password.
        }
    }
    else if(IsSecurityEnabled == TRUE && IsPasswordValidated == FALSE) { // Validate password
        DataPtr = &gHddSecurityInternalData[CurrentHardDiskNumber];
        Status = HddSecurityAuthenticate( PasswordBuffer, DataPtr, bCheckUser ); //Authenticate it
        if(EFI_ERROR( Status )) {
            // To make sure OldPasswordBuffer is filled with random number before exiting the function.
            FillRandNoInPwdBuffer((VOID *)OldPasswordBuffer,sizeof(OldPasswordBuffer));
            return EFI_NOT_READY;   // Password is wrong.
        }
        else {
            IsPasswordValidated = TRUE; // Set it so that password could be changed/cleared on next call
            StrCpyS (OldPasswordBuffer, sizeof(OldPasswordBuffer) / sizeof(CHAR16), PasswordBuffer); // Save existing HDD password
            return EFI_SUCCESS;    // Password is correct.
        }
    }
    else { // Set new password or clear old one
        // Reset static variables
        IsPasswordValidated = FALSE;
        NoPasswordExistedOnFirstCall = FALSE;
        DataPtr = &gHddSecurityInternalData[CurrentHardDiskNumber];

 
        // If existing password is equals to new password then do nothing
        if ((StrCmp(OldPasswordBuffer,PasswordBuffer) == 0) && gHddSecIsEscPressed) {
            // Make sure Buffer is filled with random number before exiting the function.
            FillRandNoInPwdBuffer((VOID *)OldPasswordBuffer,sizeof(OldPasswordBuffer));
            FillRandNoInPwdBuffer((VOID*)((HDD_SECURITY_INTERNAL_DATA*)DataPtr)->PWD, sizeof(((HDD_SECURITY_INTERNAL_DATA*)DataPtr)->PWD));
            // If Esc is pressed reset the flag
            gHddSecIsEscPressed = FALSE;
            return EFI_SUCCESS;
        }

        FillRandNoInPwdBuffer((VOID *)OldPasswordBuffer,sizeof(OldPasswordBuffer));

        // Set/Clear HDD password
        if(!HddSecurityUpdate( (UINT32)CurrentHardDiskNumber, PasswordBuffer, bCheckUser )) {
            if(bCheckUser) {
                return EFI_NOT_READY; // Not updated
            }
        }
        // After setting pwd fill the buffer with random number
        FillRandNoInPwdBuffer((VOID*)((HDD_SECURITY_INTERNAL_DATA*)DataPtr)->PWD, sizeof(((HDD_SECURITY_INTERNAL_DATA*)DataPtr)->PWD));
        //Update NVRAM and browser data
#if defined(SECURITY_SETUP_ON_SAME_PAGE) && SECURITY_SETUP_ON_SAME_PAGE && ALL_HDD_SAME_PW
        HddSecurityRefreshSetupData(0xFFFF);
#else
        HddSecurityRefreshSetupData(CurrentHardDiskNumber);
#endif
    }
    return EFI_SUCCESS;
}

/** @internal
    This function will update security status of HDDs

    @param HiiHandle           HII handle of formset
    @param Class               class of formset
    @param SubClass            subclass of formset
    @param Key                 Id of setup control

    @retval EFI_SUCCESS        Operation finished
    @retval EFI_UNSUPPORTED    Operation not supported on current event

    @endinternal
**/
EFI_STATUS
HddSecurityDynamicSetupUpdateFormCallback(
        EFI_HII_HANDLE HiiHandle,
        UINT16         Class,
        UINT16         SubClass,
        UINT16         Key
)
{
    CALLBACK_PARAMETERS *CallbackParameters;

    // Get actual parameter passed by browser
    CallbackParameters = GetCallbackParameters();

    // Check for supported browser actions
    if(!CallbackParameters || ((CallbackParameters->Action != EFI_BROWSER_ACTION_CHANGING) 
           && (CallbackParameters->Action != EFI_BROWSER_ACTION_CHANGED) 
           && (CallbackParameters->Action != EFI_BROWSER_ACTION_RETRIEVE)) )
        return EFI_UNSUPPORTED;

    // Always return success here
    if((CallbackParameters->Action == EFI_BROWSER_ACTION_CHANGED)) {
        return EFI_SUCCESS;
    }

    if((CallbackParameters->Action == EFI_BROWSER_ACTION_RETRIEVE)) {
        HddSecurityRefreshSetupData(gCurrentHddIndex);
        return EFI_SUCCESS;
    }

    // Check which HDD was selected
#if defined(SECURITY_SETUP_ON_SAME_PAGE) && SECURITY_SETUP_ON_SAME_PAGE
    gCurrentHddIndex = 0xFFFF;
#else
    if(gHddSecGotoBaseKey <= Key && Key < gHddSecGotoBaseKey + HDD_SECURITY_MAX_HDD_COUNT) {
        gCurrentHddIndex = Key - gHddSecGotoBaseKey;
    } else {
        gCurrentHddIndex = 0xFFFF;
    }
#endif

    //Update NVRAM and browser data
    HddSecurityRefreshSetupData(gCurrentHddIndex);

    return EFI_SUCCESS;
}

