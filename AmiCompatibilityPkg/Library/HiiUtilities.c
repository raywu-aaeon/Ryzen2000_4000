//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


//**********************************************************************
// $Header: $
//
// $Revision: $
//
// $Date: $
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: HiiUtilities.c
//
// Description: 
//  Contains generic EFI library functions for HII access.
//
//<AMI_FHDR_END>
//*************************************************************************
#include <AmiDxeLib.h>

#include <Protocol/LoadedImage.h>
#include <Protocol/HiiDatabase.h>
#include <Protocol/HiiConfigAccess.h>
#include <Protocol/HiiConfigRouting.h>
#include <Protocol/HiiPackageList.h>
#include <Protocol/HiiString.h>
#include <Library/PrintLib.h>
#include <Protocol/HiiDatabase.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DevicePathLib.h>
#include <Library/BaseMemoryLib.h>

typedef struct _NAME_PATTERN
{
    UINTN Length;
    CHAR16 *Tag;
} NAME_PATTERN;

typedef struct _PACKAGE_LIST_RECORD {
    DLINK		 Link;
	UINT32		 Signature;
	EFI_GUID	 Guid;
    EFI_HANDLE	 DriverHandle;
	DLIST		 PackageList;
	DLIST		 FontList;
	DLIST		 LanguageList;
	DBE_DATABASE StringDb;
} PACKAGE_LIST_RECORD;

typedef struct _PACKAGE_LINK {
	DLINK					Link;
	EFI_HII_PACKAGE_HEADER  Package;
} PACKAGE_LINK;

LIST_ENTRY gPrivateCallbackList;

typedef struct _PRIVATE_CALLBACK_INFO {
    LIST_ENTRY              Link;
    EFI_HII_CONFIG_ACCESS_PROTOCOL *HiiAccessProtocol;   ///< Instance of the HiiAccessProtocol that is produced by this module
    EFI_HANDLE CallbackHandle;                          ///< Handle that the HiiAccessProtocol is installed upon
    EFI_HII_HANDLE HiiHandle;                           ///< HiiHandle returned when NewPack is called when installing the String Database
    EFI_GUID FormGuid;                                  ///< GUID of the formset produced by this module;
} PRIVATE_CALLBACK_INFO;

extern const char *DefaultLanguageCode;

const NAME_PATTERN GuidPattern   = { 10, L"GUID=" };
const NAME_PATTERN NamePattern   = { 10, L"NAME=" };
const NAME_PATTERN PathPattern   = { 10, L"PATH=" };
const NAME_PATTERN AltCfgPattern = { 14, L"ALTCFG=" };
const NAME_PATTERN OffsetPattern = { 14, L"OFFSET=" };
const NAME_PATTERN WidthPattern  = { 12, L"WIDTH=" };
const NAME_PATTERN ValuePattern  = { 12, L"VALUE=" };

// ===========================
// In Aptio4, these are externals defined in the AmiProtocolLib.
// In AptioV, there is no AmiProtocolLib.
// We could've listed these in AmiDxeLib.inf, but may break the
// build of some of the Aptio4 modules due to multiple defined symbols.
static EFI_GUID gLocalHiiUtilitiesProtocolGuid = HII_UTILITIES_PROTOCOL_GUID;
static EFI_GUID gLocalEfiHiiConfigAccessProtocolGuid = EFI_HII_CONFIG_ACCESS_PROTOCOL_GUID;
static EFI_GUID gLocalEfiHiiConfigRoutingProtocolGuid = EFI_HII_CONFIG_ROUTING_PROTOCOL_GUID;
static EFI_GUID gLocalEfiDevicePathProtocolGuid = EFI_DEVICE_PATH_PROTOCOL_GUID;
static EFI_GUID gLocalEfiHiiStringProtocolGuid = EFI_HII_STRING_PROTOCOL_GUID;
static EFI_GUID gLocalEfiFormBrowser2ProtocolGuid = EFI_FORM_BROWSER2_PROTOCOL_GUID;
static EFI_GUID gLocalEfiHiiPackageListProtocolGuid = EFI_HII_PACKAGE_LIST_PROTOCOL_GUID;
static EFI_GUID gLocalEfiHiiDatabaseProtocolGuid = EFI_HII_DATABASE_PROTOCOL_GUID;

static EFI_HII_DATABASE_PROTOCOL *gHiiDatabase=NULL;
static EFI_HII_STRING_PROTOCOL *HiiString=NULL;
static EFI_FORM_BROWSER2_PROTOCOL  *FormBrowser = NULL;
static EFI_HII_CONFIG_ROUTING_PROTOCOL *HiiConfigRouting = NULL;
static CHAR16 DummyConfigHeader[] = L"GUID=00000000000000000000000000000000&NAME=0000&PATH=00&";

// *************************** Service functions (not for public use) **********************
CHAR8 *HiiLibGetPlatformLanguageInternal(BOOLEAN Refresh){
	static EFI_GUID EfiVariableGuid = EFI_GLOBAL_VARIABLE;
	static CHAR8 *PlatformLang = NULL;	
    
    if (PlatformLang==NULL || Refresh){
    	UINTN Size = 0;
    	if (PlatformLang==(CHAR8*)DefaultLanguageCode) PlatformLang = NULL;
        if (EFI_ERROR(GetEfiVariable(
            L"PlatformLang", &EfiVariableGuid, NULL, &Size, (VOID **)&PlatformLang
        ))) PlatformLang = (CHAR8*)DefaultLanguageCode;
    }    
    return PlatformLang;
}

BOOLEAN CheckIfHexDigit(CHAR16 Char)
{
    if(Char < 0x30 || Char > 0x66)
        return FALSE;

    if(Char > 0x39 && Char < 0x41)
        return FALSE;

    if(Char > 0x46 && Char < 0x61)
        return FALSE;

    return TRUE;
}

UINT8 HexValue(CHAR8 Char)
{
    if(Char >= 0x30 && Char <= 0x39)        //symbols 0...9
        return Char - 0x30;

    if(Char >= 0x41 && Char <= 0x46)        //symbols A...F
        return Char - 0x37;

    return Char - 0x57;                     //symbols a...f
}

static BOOLEAN CheckPattern(CHAR16 *String, const NAME_PATTERN *Pattern)
{
    if(MemCmp(String, Pattern->Tag, Pattern->Length))
        return FALSE;
    else
        return TRUE;
}

VOID StringToChar16(
    IN CHAR16 *String,
    IN OUT UINTN  *Size,
    OUT CHAR16 *Block
)
{
    UINTN i, j;

    i = 0;
    j = 0;

    while( CheckIfHexDigit(String[i]) && CheckIfHexDigit(String[i + 1]) && 
           CheckIfHexDigit(String[i + 2]) && CheckIfHexDigit(String[i + 3]) &&
           j < *Size - 1 )
    {
        Block[j]  = HexValue((UINT8)String[i]) & 0x000f;
        Block[j] <<= 4;
        Block[j] |= HexValue((UINT8)String[i + 1]);
        Block[j] <<= 4;
        Block[j] |= HexValue((UINT8)String[i + 2]);
        Block[j] <<= 4;
        Block[j] |= HexValue((UINT8)String[i + 3]);

        i += 4;
        j++;
    }
    *Size = j;      //number of words processed
    Block[j] = 0;   //put null-terminator
}

static UINT32 StrSize16(CHAR16 *String)
{
	UINT32 Size = 2;
	while(*String++)
		Size += 2;
	return Size;
}

VOID StringToBlock(
    IN CHAR16 *String,
    IN UINTN StringSize,
    OUT UINT8 *Block)
{
    UINT8 LowNibble, HiNibble;
    UINTN i, j;

    j = 0;

    for(i = 0; i < StringSize; i += 2)
    {
        if(i == StringSize - 1) {   //odd number need to fill with zeroes
            HiNibble = 0;
            LowNibble = HexValue((UINT8)String[i]);
        } else {
            HiNibble = HexValue((UINT8)String[i]);
            LowNibble = HexValue((UINT8)String[i + 1]);
        }
        Block[j] = (HiNibble << 4) | LowNibble;
        j++;
    }
}

static EFI_STATUS ExtractDevicePath(CHAR16 *ConfigString, UINT8 **DevicePath, UINTN *DpLength)
{
    EFI_STATUS Status;
    UINTN Length = 0;
    UINTN i = 5;        //set pointer to skip first four symbols "PATH="

    while(CheckIfHexDigit(ConfigString[i]))      //determine device path length in characters
    {
        Length++;
        i++;
    }

    Status = pBS->AllocatePool(
                            EfiBootServicesData, 
        					(Length / 2), 
					        (VOID**)DevicePath);
	if (EFI_ERROR(Status))
		return Status;

    StringToBlock(&ConfigString[5], Length, *DevicePath);
    *DpLength = Length / 2;

    return EFI_SUCCESS;
}

static BOOLEAN CheckDevicePath(
    IN UINT8 *DevicePath,
    IN UINTN DpLength)
{
    EFI_DEVICE_PATH_PROTOCOL* TempDp;

    TempDp = (EFI_DEVICE_PATH_PROTOCOL*)DevicePath;
    
    if (DevicePath == NULL)
        return FALSE;
        
    // Valid device path must have at least one node
    if (DpLength < 4)
        return FALSE;
    
    // Valid device path protocol cannot be longer than binary data
    if (*(UINT16*)TempDp->Length > DpLength)
        return FALSE;
        
    // Valide device path types
    if (TempDp->Type != HARDWARE_DEVICE_PATH    &&
        TempDp->Type != ACPI_DEVICE_PATH        &&
        TempDp->Type != MESSAGING_DEVICE_PATH   &&
        TempDp->Type != MEDIA_DEVICE_PATH       &&
        TempDp->Type != BBS_DEVICE_PATH         &&
        TempDp->Type != END_DEVICE_PATH_TYPE)
    {
        return FALSE;
    }

    return TRUE;
}

static EFI_STATUS FindDeviceHandle(
    IN CHAR16 *ConfigString,
    OUT EFI_HANDLE *Handle)
{
    UINTN i = 0;
    UINTN DpLength;
    UINT8 *DevicePath = NULL;
    EFI_DEVICE_PATH_PROTOCOL* TempDp;
    EFI_STATUS Status;

//scan config string to find PATH pattern
    do
    {
        while((ConfigString[i] != L'&') && (ConfigString[i] != 0))
            i++;

        if(ConfigString[i] == 0)
            return EFI_NOT_FOUND;

        i++;            //shift pointer to next symbol
        if(CheckPattern(&ConfigString[i], &PathPattern))
            break;
    } while(1);

//if we get here, we have pointer set on PATH pattern
    Status = ExtractDevicePath(&ConfigString[i], &DevicePath, &DpLength);
    if(EFI_ERROR(Status))
        return Status;
        
    if (CheckDevicePath(DevicePath, DpLength)) {
        TempDp = (EFI_DEVICE_PATH_PROTOCOL*)DevicePath;
        Status = pBS->LocateDevicePath (
                          &gLocalEfiDevicePathProtocolGuid,
                          (EFI_DEVICE_PATH_PROTOCOL**)&TempDp,
                          Handle
                          );
    } else {
        Status = EFI_NOT_FOUND;
    }
    
    pBS->FreePool(DevicePath);

    return Status;
}

static VOID StripValuePattern(
    IN OUT EFI_STRING String,
    IN UINTN          Size
)
{
    EFI_STATUS Status;
    EFI_STRING NewString;
    UINTN i = 0;
    UINTN j = 0;

    Status = pBS->AllocatePool(EfiBootServicesData, Size, (VOID**)&NewString);
    if( EFI_ERROR(Status) )
        return;
    while(String[i] != 0) {
        if(String[i] == L'&') {
            if(CheckPattern(&String[i + 1], &ValuePattern)) {
                i++;
                while((String[i] != L'&') && (String[i] != 0))
                    i++;
                if(String[i] == 0)
                    break;
            }
        }

        NewString[j++] = String[i++];
    }

    NewString[j] = 0;
    MemCpy(String, NewString, (j + 1) * 2);
    pBS->FreePool(NewString);
}

/**
  Converts all hex string characters in range ['A'..'F'] to ['a'..'f'] for
  hex digits that appear between a '=' and a '&' in a config string.

  If ConfigString is NULL, then ASSERT().

  @param[in] ConfigString  Pointer to a Null-terminated Unicode string.

  @return  Pointer to the Null-terminated Unicode result string.

**/
EFI_STRING
EFIAPI
InternalLowerConfigString (
  IN EFI_STRING  ConfigString
  )
{
  EFI_STRING  String;
  BOOLEAN     Lower;

  ASSERT (ConfigString != NULL);

  //
  // Convert all hex digits in range [A-F] in the configuration header to [a-f]
  //
  for (String = ConfigString, Lower = FALSE; *String != L'\0'; String++) {
    if (*String == L'=') {
      Lower = TRUE;
    } else if (*String == L'&') {
      Lower = FALSE;
    } else if (Lower && *String >= L'A' && *String <= L'F') {
      *String = (CHAR16) (*String - L'A' + L'a');
    }
  }

  return ConfigString;
}

/**
  Allocates and returns a Null-terminated Unicode <ConfigHdr> string using routing
  information that includes a GUID, an optional Unicode string name, and a device
  path.  The string returned is allocated with AllocatePool().  The caller is
  responsible for freeing the allocated string with FreePool().

  The format of a <ConfigHdr> is as follows:

    GUID=<HexCh>32&NAME=<Char>NameLength&PATH=<HexChar>DevicePathSize<Null>

  @param[in]  Guid          Pointer to an EFI_GUID that is the routing information
                            GUID.  Each of the 16 bytes in Guid is converted to
                            a 2 Unicode character hexadecimal string.  This is
                            an optional parameter that may be NULL.
  @param[in]  Name          Pointer to a Null-terminated Unicode string that is
                            the routing information NAME.  This is an optional
                            parameter that may be NULL.  Each 16-bit Unicode
                            character in Name is converted to a 4 character Unicode
                            hexadecimal string.
  @param[in]  DriverHandle  The driver handle which supports a Device Path Protocol
                            that is the routing information PATH.  Each byte of
                            the Device Path associated with DriverHandle is converted
                            to a 2 Unicode character hexadecimal string.

  @retval NULL   DriverHandle does not support the Device Path Protocol.
  @retval Other  A pointer to the Null-terminate Unicode <ConfigHdr> string

**/
EFI_STRING
EFIAPI
InternalHiiConstructConfigHdr (
  IN CONST EFI_GUID  *Guid,  OPTIONAL
  IN CONST CHAR16    *Name,  OPTIONAL
  IN EFI_HANDLE      DriverHandle
  )
{
  UINTN                     NameLength;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  UINTN                     DevicePathSize;
  CHAR16                    *String;
  CHAR16                    *ReturnString;
  UINTN                     Index;
  UINT8                     *Buffer;
  UINTN                     MaxLen;

  //
  // Compute the length of Name in Unicode characters.
  // If Name is NULL, then the length is 0.
  //
  NameLength = 0;
  if (Name != NULL) {
    NameLength = StrLen (Name);
  }

  DevicePath = NULL;
  DevicePathSize = 0;
  //
  // Retrieve DevicePath Protocol associated with DriverHandle
  //
  if (DriverHandle != NULL) {
    DevicePath = DevicePathFromHandle (DriverHandle);
    if (DevicePath == NULL) {
      return NULL;
    }
    //
    // Compute the size of the device path in bytes
    //
    DevicePathSize = GetDevicePathSize (DevicePath);
  }

  //
  // GUID=<HexCh>32&NAME=<Char>NameLength&PATH=<HexChar>DevicePathSize <Null>
  // | 5 | sizeof (EFI_GUID) * 2 | 6 | NameStrLen*4 | 6 | DevicePathSize * 2 | 1 |
  //
  MaxLen = 5 + sizeof (EFI_GUID) * 2 + 6 + NameLength * 4 + 6 + DevicePathSize * 2 + 1;
  String = AllocateZeroPool (MaxLen * sizeof (CHAR16));
  if (String == NULL) {
    return NULL;
  }

  //
  // Start with L"GUID="
  //
  StrCpyS (String, MaxLen, L"GUID=");
  ReturnString = String;
  String += StrLen (String);

  if (Guid != NULL) {
    //
    // Append Guid converted to <HexCh>32
    //
    for (Index = 0, Buffer = (UINT8 *)Guid; Index < sizeof (EFI_GUID); Index++) {
      UnicodeValueToStringS (
        String,
        MaxLen * sizeof (CHAR16) - ((UINTN)String - (UINTN)ReturnString),
        PREFIX_ZERO | RADIX_HEX,
        *(Buffer++),
        2
        );
      String += StrnLenS (String, MaxLen - ((UINTN)String - (UINTN)ReturnString) / sizeof (CHAR16));
    }
  }

  //
  // Append L"&NAME="
  //
  StrCatS (ReturnString, MaxLen, L"&NAME=");
  String += StrLen (String);

  if (Name != NULL) {
    //
    // Append Name converted to <Char>NameLength
    //
    for (; *Name != L'\0'; Name++) {
      UnicodeValueToStringS (
        String,
        sizeof (CHAR16) * MaxLen - ((UINTN)String - (UINTN)ReturnString),
        PREFIX_ZERO | RADIX_HEX,
        *Name,
        4
        );
      String += StrnLenS (String, MaxLen - ((UINTN)String - (UINTN)ReturnString) / sizeof (CHAR16));
    }
  }

  //
  // Append L"&PATH="
  //
  StrCatS (ReturnString, MaxLen, L"&PATH=");
  String += StrLen (String);

  //
  // Append the device path associated with DriverHandle converted to <HexChar>DevicePathSize
  //
  for (Index = 0, Buffer = (UINT8 *)DevicePath; Index < DevicePathSize; Index++) {
    UnicodeValueToStringS (
      String,
      sizeof (CHAR16) * MaxLen - ((UINTN)String - (UINTN)ReturnString),
      PREFIX_ZERO | RADIX_HEX,
      *(Buffer++),
      2
      );
    String += StrnLenS (String, MaxLen - ((UINTN)String - (UINTN)ReturnString) / sizeof (CHAR16));
  }

  //
  // Null terminate the Unicode string
  //
  *String = L'\0';

  //
  // Convert all hex digits in range [A-F] in the configuration header to [a-f]
  //
  return InternalLowerConfigString (ReturnString);
}

/**
 * Retrieves the array of all the HII Handles
 * The caller is responsible for freeing the array with FreePool().
 * 
 * 
 * @param ConfigRouting  Instance of the ConfigRouting Protocol 
 * @param DriverHandle Handle in which DevicePath protocol and HiiConfigAccessProtocol has been installed.
 *                     Also this DriverHandle will be used in NewPackageList().
 * @param IfrVarStore Pointer has Buffer Varstore information.
 * @param Response     Pointer to a newly created string that contains the requested information
 * @param Progress    Pointer that contains the progress of parsing the Request string
 *  
 * @retval NULL   The array of HII Handles could not be retrieved
 * @retval Other  A pointer to the NULL terminated array of HII Handles
 */
EFI_HII_HANDLE *
EFIAPI
InternalHiiGetHiiHandles (
VOID
  )
{
  EFI_STATUS      Status;
  UINTN           HandleBufferLength;
  EFI_HII_HANDLE  TempHiiHandleBuffer;
  EFI_HII_HANDLE  *HiiHandleBuffer;
  //
  // Retrieve the size required for the buffer of all HII handles.
  //
  HandleBufferLength = 0;
  Status = gHiiDatabase->ListPackageLists (
                           gHiiDatabase,
                           EFI_HII_PACKAGE_TYPE_ALL,
                           NULL,
                           &HandleBufferLength,
                           &TempHiiHandleBuffer
                           );
  
  if (Status != EFI_BUFFER_TOO_SMALL) {
    return NULL;
  }

  //
  // Allocate the array of HII handles to hold all the HII Handles and a NULL terminator
  //
  HiiHandleBuffer = AllocateZeroPool (HandleBufferLength + sizeof (EFI_HII_HANDLE));
  if (HiiHandleBuffer == NULL) {
    return NULL;
  }

  //
  // Retrieve the array of HII Handles in the HII Database
  //
  Status = gHiiDatabase->ListPackageLists (
                           gHiiDatabase,
                           EFI_HII_PACKAGE_TYPE_ALL,
                           NULL,
                           &HandleBufferLength,
                           HiiHandleBuffer
                           );
  if (EFI_ERROR (Status)) {
    //
    // Free the buffer and return NULL if the HII handles can not be retrieved.
    //
    FreePool (HiiHandleBuffer);
    return NULL;
  }

    return HiiHandleBuffer;
}
/**
 * Frames the <ConfigHdr> and <ConfigRequest> by using valid GUID, Unicode string name, and DriverHandle.
 * Returns the Response string in the format <ConfigResp> by using the framed <ConfigRequest>.
 * 
 * 
 * @param ConfigRouting  Instance of the ConfigRouting Protocol 
 * @param DriverHandle Handle in which DevicePath protocol and HiiConfigAccessProtocol has been installed.
 *                     Also this DriverHandle will be used in NewPackageList().
 * @param IfrVarStore Pointer has Buffer Varstore information.
 * @param Response     Pointer to a newly created string that contains the requested information
 * @param Progress    Pointer that contains the progress of parsing the Request string
 *  
 * @return EFI_STATUS
 * @retval EFI_NOT_FOUND Mostly Variables may not found for the input IfrVarStore.
 * @retval EFI_SUCCESS   Response pointer returns a <ConfigResp>  for a
 *                       valid EFI_IFR_FORM_SET.
 */
EFI_STATUS
InternalFrameConfigHdrAndReturnResponse (
    EFI_HII_CONFIG_ROUTING_PROTOCOL *ConfigRouting,
    EFI_HANDLE DriverHandle,
    EFI_IFR_VARSTORE  *IfrVarStore,
    EFI_STRING *Response,
    EFI_STRING *Progress
){
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_STRING VarStoreName = NULL;
    EFI_STRING ConfigRequestHdr = NULL;
    EFI_STRING ConfigRequest = NULL;
    UINTN      NameSize;
    UINT8      *VarData = NULL;
    UINTN      BufferSize = 0;
    EFI_GUID   Guid;
    
    NameSize = AsciiStrSize ((CHAR8 *)IfrVarStore->Name);
    VarStoreName = (EFI_STRING)AllocateZeroPool (NameSize * sizeof (CHAR16));
    
    if (VarStoreName == NULL) {
        Status = EFI_OUT_OF_RESOURCES;
        goto Done;
    }

    AsciiStrToUnicodeStrS ((CHAR8 *) IfrVarStore->Name, VarStoreName, NameSize);

    CopyMem( &Guid, &IfrVarStore->Guid, sizeof(EFI_GUID));

    ConfigRequestHdr = InternalHiiConstructConfigHdr (&Guid, VarStoreName, DriverHandle);

    //
    // Request has no request element, construct full request string.
    // Allocate and fill a buffer large enough to hold the <ConfigHdr> template
    // followed by "&OFFSET=0&WIDTH=WWWWWWWWWWWWWWWW" followed by a Null-terminator
    // to get <ConfigRequest>
    BufferSize = (StrLen (ConfigRequestHdr) + 32 + 1) * sizeof (CHAR16);
    
    ConfigRequest = AllocateZeroPool(BufferSize);
    if (ConfigRequest == NULL) {
        *Progress = NULL;
        Status =  EFI_OUT_OF_RESOURCES;
        goto Done;
    }
    
    UnicodeSPrint (ConfigRequest, BufferSize, L"%s&OFFSET=0&WIDTH=%016LX", ConfigRequestHdr, IfrVarStore->Size);
    
    BufferSize = 0;
    Status = pRS->GetVariable (VarStoreName, &Guid, NULL, &BufferSize, NULL);
    
    if (Status != EFI_BUFFER_TOO_SMALL) {
        goto Done;
    }
    
    VarData = AllocateZeroPool (BufferSize);
    ASSERT (VarData != NULL);
    Status = pRS->GetVariable (VarStoreName, &Guid, NULL, &BufferSize, VarData);
    if (EFI_ERROR (Status)) {
        goto Done;
    }
    
    Status = ConfigRouting->BlockToConfig(ConfigRouting, ConfigRequest, VarData, IfrVarStore->Size, Response, Progress);
    
    if (EFI_ERROR (Status)) {
        goto Done;
    }
    
Done:
    if (VarStoreName != NULL) {
        FreePool (VarStoreName);
    }
    
    if (VarData != NULL) {
        FreePool (VarData);
    }
    
    if (ConfigRequestHdr != NULL) {
        FreePool (ConfigRequestHdr);
    }
    
    if (ConfigRequest != NULL) {
        FreePool (ConfigRequest);
    }
    return Status;
}

/**
 * Validates all the Hii Handles available in Hii Database to match the input HiiHandle. Once match is found,
 * then validates all the Formsets obtained from the HiiPackagelist to find the exact Formset which has identical
 * FormSetGuid. By using all the valid EFI_IFR_VARSTORE under the matched formset, Request is framed in <ConfigRequest>
 * format and returns a Results string for the framed Request.
 *
 * @param HiiHandle  Instance of HiiHandle which is obtained as output from NewPackageList() 
 * @param DriverHandle Handle in which DevicePath protocol and HiiConfigAccessProtocol has been installed.
 *                     Also this DriverHandle will be used to add a package in Packagelist using NewPackageList().
 * @param FormSetGuid Guid to match the expected EFI_IFR_FORM_SET opcode.
 * @param Results     Pointer to a newly created string that contains the requested information
 * @param Progress    Pointer that contains the progress of parsing the Request string
 *  
 * @return EFI_STATUS
 * @retval EFI_NOT_FOUND There is no valid EFI_IFR_VARSTORE available.
 * @retval EFI_SUCCESS   Results pointer consists at-least one <ConfigResp> or  <MultiConfigResp> obtained from all
 *                       the valid EFI_IFR_FORM_SET found under matched FormSet.
 */

EFI_STATUS
InternalExtractConfigProcessNullRequest(    
  EFI_HII_HANDLE HiiHandle,
  EFI_HANDLE     DriverHandle,
  EFI_GUID       FormSetGuid,
  EFI_STRING     *Results,
  EFI_STRING     *Progress
) 
{
    EFI_STATUS  Status;
    EFI_HII_CONFIG_ROUTING_PROTOCOL *ConfigRouting = NULL;
    UINTN                        PackageListSize;
    EFI_HII_PACKAGE_LIST_HEADER  *HiiPackageList;
    UINT32                       PackageListLength;
    UINT32                       Offset;
    UINT32                       Offset2;
    UINT8                        *Package;
    UINT8                        *OpCodeData;
    UINTN                        MaxSize = 0;
    EFI_STRING                   TempResult1 = NULL;
    EFI_STRING                   TempResult2 = NULL;
    EFI_HII_HANDLE               *HiiHandleBuffer = NULL;
    EFI_HANDLE                   TempDriverHandle;
    UINT32                       Index;
    BOOLEAN                      HiiHandleFound = FALSE;
    BOOLEAN                      FormSetFound = FALSE;
    
    // Locate the HiiDatabase Protocol
    Status = pBS->LocateProtocol(&gLocalEfiHiiDatabaseProtocolGuid, NULL, (VOID**)&gHiiDatabase);
    if(EFI_ERROR(Status))
        return Status;
    
    Status = pBS->LocateProtocol(&gLocalEfiHiiConfigRoutingProtocolGuid, NULL, (VOID**)&ConfigRouting);
    if(EFI_ERROR(Status))
        return Status;
    
    HiiHandleBuffer = InternalHiiGetHiiHandles ();
    if (HiiHandleBuffer == NULL) {
        return EFI_NOT_FOUND;
    }
    
    // Check complete HII Database to match the Input HiiHandle and DriverHandle 
    for (Index = 0; HiiHandleBuffer[Index] != NULL; Index ++) {
        gHiiDatabase->GetPackageListHandle (gHiiDatabase, HiiHandleBuffer[Index], &TempDriverHandle);
        if ((TempDriverHandle == DriverHandle) && (HiiHandleBuffer[Index] == HiiHandle) ){
            HiiHandleFound = TRUE;
            break;
        }
    }
    
    pBS->FreePool(HiiHandleBuffer);
    
    if(!HiiHandleFound) {
        return EFI_NOT_FOUND;
    }

    PackageListSize = 0;
    HiiPackageList = NULL;
    Status = gHiiDatabase->ExportPackageLists (gHiiDatabase, HiiHandle, &PackageListSize, HiiPackageList);

    if (EFI_ERROR (Status) && (Status != EFI_BUFFER_TOO_SMALL)) {
        return Status;
    }
    
    Status = pBS->AllocatePool(EfiBootServicesData, PackageListSize, (VOID**)&HiiPackageList);
    if (HiiPackageList == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    Status = gHiiDatabase->ExportPackageLists (gHiiDatabase, HiiHandle, &PackageListSize, HiiPackageList);
    ASSERT_EFI_ERROR (Status);
    
    Offset = sizeof (EFI_HII_PACKAGE_LIST_HEADER);
    PackageListLength = ReadUnaligned32 (&HiiPackageList->PackageLength);

    while (Offset < PackageListLength) {
        
        // Exit the while() when Expected Formset is Found.
        if (FormSetFound) {
            break;
        }
        
        Package = ((UINT8 *) HiiPackageList) + Offset;
        Offset += ((EFI_HII_PACKAGE_HEADER*)Package)->Length;

        if (((EFI_HII_PACKAGE_HEADER*)Package)->Type != EFI_HII_PACKAGE_FORMS) {
            continue;
        }
      
        Offset2 = sizeof (EFI_HII_PACKAGE_HEADER);
        while (Offset2 < ((EFI_HII_PACKAGE_HEADER*)Package)->Length) {
            OpCodeData = Package + Offset2;
            Offset2 += ((EFI_IFR_OP_HEADER *) OpCodeData)->Length;
            
            if (((EFI_IFR_OP_HEADER *) OpCodeData)->OpCode != EFI_IFR_FORM_SET_OP) {
                continue;
            }
              
            // Check to verify the FormSetGuid.
            if (guidcmp(&((EFI_IFR_FORM_SET*) OpCodeData)->Guid,&FormSetGuid) == 0){
                FormSetFound = TRUE;
                break;
            }
        }
    }
    
    *Results = NULL;
    *Progress = NULL;
    
    // Return if Expected FormSet is not found
    if (!FormSetFound) {
        if (HiiPackageList) {
            pBS->FreePool (HiiPackageList);
        }
        return EFI_NOT_FOUND;
    }
    
    do  {
        OpCodeData += ((EFI_IFR_OP_HEADER *) OpCodeData)->Length;
        if (((EFI_IFR_OP_HEADER *) OpCodeData)->OpCode == EFI_IFR_VARSTORE_OP){
            
            // Frame the ConfigHeader for the obtained EFI_IFR_VARSTORE and
            // Returns the Config response.
            Status = InternalFrameConfigHdrAndReturnResponse (
                        ConfigRouting,
                        DriverHandle,
                        (EFI_IFR_VARSTORE*) OpCodeData,
                        &TempResult1,
                        Progress
            );
            
            if (!EFI_ERROR(Status) &&(TempResult1 != NULL)) {
                if (*Results == NULL) {
                    *Results = TempResult1;
                } else {
                    
                    // MaxSize will have total number of Bytes.
                    // Adding 4 to append "&" and frame the <MultiConfigResp>.
                    MaxSize = StrSize(*Results) + StrSize(TempResult1) + 4;
                    TempResult2 = AllocateZeroPool (MaxSize);
                    
                    if (TempResult2 == NULL) {
                        return EFI_OUT_OF_RESOURCES;
                    }
                    
                    // (Maxsize / 2) gives the total number of Unicode Characters
                    StrCatS (TempResult2,(MaxSize / 2),*Results);
                    StrCatS (TempResult2,(MaxSize / 2),L"&");
                    StrCatS (TempResult2,(MaxSize / 2),TempResult1);
                    
                    // Free the previously allocated memory.
                    pBS->FreePool (*Results);
                    pBS->FreePool (TempResult1);
                    TempResult1 = NULL;
                    
                    // Update the Results with newly allocated memory.
                    *Results = TempResult2;
                    *Progress = TempResult2;
                }
            }
        }
    }while(((EFI_IFR_OP_HEADER *) OpCodeData)->OpCode != EFI_IFR_END_OP);
    
    if (HiiPackageList) {
        pBS->FreePool (HiiPackageList);
    }
    
    // if *Results is NULL then not even single <ConfigResp> is framed.
    // other words, there is no valid EFI_IFR_VARSTORE.
    if (*Results == NULL) {
        return EFI_NOT_FOUND;
    }
    
    return EFI_SUCCESS;
}


static EFI_STATUS EFIAPI HiiAccessExtractConfig(
    IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
    IN CONST EFI_STRING Request,
    OUT EFI_STRING *Progress,
    OUT EFI_STRING *Results
)
{
    EFI_STATUS  Status;
    UINTN       Length;
    EFI_GUID    Guid;
    CHAR16      Name[80];
    CHAR16      *Pointer = Request;
    UINT8       *Var = NULL;
    EFI_HII_CONFIG_ROUTING_PROTOCOL *ConfigRouting;
    CHAR16      *ErrorMarker;
    PRIVATE_CALLBACK_INFO *PrivateCallbackInfo = NULL;
    LIST_ENTRY *Link;
    BOOLEAN MatchFound = FALSE;
    
    if(Request == NULL) {
        if (IsListEmpty(&gPrivateCallbackList)) {
            return EFI_NOT_FOUND;
        }
        
        for (Link = gPrivateCallbackList.ForwardLink; Link != &gPrivateCallbackList; Link = Link->ForwardLink) {
            PrivateCallbackInfo = BASE_CR(Link, PRIVATE_CALLBACK_INFO, Link );
            
            if (PrivateCallbackInfo->HiiAccessProtocol == This) {
                MatchFound = TRUE;
            }
        }
        if (!MatchFound) {
            return EFI_NOT_FOUND;
        }
        Status = InternalExtractConfigProcessNullRequest (
                PrivateCallbackInfo->HiiHandle,
                PrivateCallbackInfo->CallbackHandle,
                PrivateCallbackInfo->FormGuid,
                Results,
                Progress
        );
        if (EFI_ERROR(Status)){
            return EFI_NOT_FOUND;
        }
        return Status;
    }

    Status = pBS->LocateProtocol(&gLocalEfiHiiConfigRoutingProtocolGuid, NULL, (VOID **)&ConfigRouting);
    if(EFI_ERROR(Status))
        return Status;

//check syntax for guid
    if(!CheckPattern(Request, &GuidPattern)) {
        *Progress = Request;
        return EFI_INVALID_PARAMETER;
    }
//extract guid
    ErrorMarker = Pointer;
    Pointer += 5;       //skip "GUID=" pattern
    Length = 32;        //length of guid in symbols
    StringToBlock(Pointer, Length, (UINT8 *)&Guid);
    Pointer += Length;
    if(*Pointer != L'&') {
        TRACE((DEBUG_ERROR, "HII Extract Config: Guid extraction failed\n"));
        *Progress = ErrorMarker;
        return EFI_INVALID_PARAMETER;
    }

//check syntax for name
    if(!CheckPattern(Pointer + 1, &NamePattern)) {
        *Progress = Pointer;
        return EFI_INVALID_PARAMETER;
    }
//extract name
    ErrorMarker = Pointer;
    Pointer += 6;       //skip '&NAME=' pattern
    Length = 80;
    StringToChar16(Pointer, &Length, Name);
    Pointer += (Length * 4);
    if(*Pointer != L'&') {
        TRACE((DEBUG_ERROR, "HII Extract Config: Name extraction failed\n"));
        *Progress = ErrorMarker;
        return EFI_INVALID_PARAMETER;
    }

//get variable by name and guid from nvram

    Length = 0;
    Status = GetEfiVariable(Name, &Guid, NULL, &Length, (VOID**)&Var);
    if(EFI_ERROR(Status)) {
        *Progress = Request;
        return Status;
    }

//find start of OFFSET/WIDTH/VALUE block
    Pointer++;      //skip '&'
    while((*Pointer != L'&') && (*Pointer != 0))    //skip PATH
            Pointer++;

    if(*Pointer == 0) {                     //OFFSET/WIDTH blocks are missed
        UINTN TempSize; 
        CHAR16 *TempString;
        CHAR16 *TempString2;

        TempSize = (StrLen(L"&OFFSET=0&WIDTH=") + sizeof(Length) + 1) * sizeof(CHAR16);
        TempString = MallocZ(TempSize);
        if(TempString == NULL)
            return EFI_OUT_OF_RESOURCES;

        UnicodeSPrint(TempString, TempSize, L"&OFFSET=0&WIDTH=%x", Length);

        TempSize += StrSize(Request);
        TempString2 = MallocZ(TempSize);
        if(TempString2 == NULL)
            return EFI_OUT_OF_RESOURCES;

        Status = StrCatS(TempString2, TempSize, Request);
        if (!EFI_ERROR(Status))
        {
            Status = StrCatS(TempString2, TempSize, TempString);
        }
        
        if (EFI_ERROR(Status))
        {
            pBS->FreePool(TempString);
            pBS->FreePool(TempString2);
            return EFI_OUT_OF_RESOURCES;
        }
        
        Status = ConfigRouting->BlockToConfig(ConfigRouting, TempString2, Var, Length, Results, Progress);
        *Progress = Request + StrLen(Request); //set Progress to end of ConfigHdr
        pBS->FreePool(TempString);
        pBS->FreePool(TempString2);
    } else {                                        //OFFSET/WIDTH block found, let's check if it's correct
        if(!CheckPattern(Pointer + 1, &OffsetPattern)) {
            *Progress = Pointer;
            return EFI_INVALID_PARAMETER;
        }
        Status = ConfigRouting->BlockToConfig(ConfigRouting, Request, Var, Length, Results, Progress);
    }
        
    pBS->FreePool(Var);

    return Status;
}

static EFI_STATUS EFIAPI HiiAccessRouteConfig(
    IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
    IN CONST EFI_STRING Configuration,
    OUT EFI_STRING *Progress
)
{
    EFI_STATUS  Status;
    UINTN       Length;
    UINTN       VarSize;
    EFI_GUID    Guid;
    CHAR16      Name[80];
    CHAR16      *Pointer = Configuration;
    UINT8       *Var = NULL;
    EFI_HII_CONFIG_ROUTING_PROTOCOL *ConfigRouting;
    EFI_HANDLE  Handle;
    UINT32      Attributes;

    if(Configuration == NULL || Progress == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }
    
    *Progress = Configuration;
    
    Status = pBS->LocateProtocol(&gLocalEfiHiiConfigRoutingProtocolGuid, NULL, (VOID**)&ConfigRouting);
    if(EFI_ERROR(Status))
        return Status;

//check syntax for guid
    if(!CheckPattern(Configuration, &GuidPattern))
    {
        *Progress = Configuration;
        return EFI_INVALID_PARAMETER;
    }

//check proper device path
    Status = FindDeviceHandle(Configuration, &Handle);
    if(EFI_ERROR(Status))
        return EFI_NOT_FOUND;

//extract guid
    Pointer += 5;       //skip "GUID=" pattern
    Length = 32;        //length of guid in bytes
    StringToBlock(Pointer, Length, (UINT8 *)&Guid);
    Pointer += Length;
    if(*Pointer != L'&')
    {
        TRACE((DEBUG_ERROR, "HII Route Config: Guid extraction failed\n"));
        *Progress = Pointer;
        return EFI_INVALID_PARAMETER;
    }

//check syntax for name
    if(!CheckPattern(Pointer + 1, &NamePattern))
    {
        *Progress = Pointer;
        return EFI_INVALID_PARAMETER;
    }
//extract name
    Pointer += 6;       //skip '&NAME=' pattern
    Length = 80;
    StringToChar16(Pointer, &Length, Name);
    Pointer += (Length * 4);
    if(*Pointer != L'&')
    {
        TRACE((DEBUG_ERROR, "HII Route Config: Name extraction failed\n"));
        *Progress = Pointer;
        return EFI_INVALID_PARAMETER;
    }

//get variable by name and guid from nvram

    Length = 0;
    Status = GetEfiVariable(Name, &Guid, &Attributes, &Length, (VOID**)&Var);
    if(EFI_ERROR(Status))   //requested variable not found
    {
        if(Var != NULL)
            pBS->FreePool(Var);
        
        Var = NULL;
        Length = 0;
#if (defined(RT_ACCESS_SUPPORT_IN_HPKTOOL) && (RT_ACCESS_SUPPORT_IN_HPKTOOL == 1))
        {
            Attributes = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS;
        }
#else
        {
            Attributes = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS;
        }
#endif
    }
    VarSize = Length;

    Status = ConfigRouting->ConfigToBlock(ConfigRouting, Configuration, Var, &Length, Progress);
    while(Status == EFI_DEVICE_ERROR || (Status == EFI_INVALID_PARAMETER && Var == NULL)) //block not large enough
    {
        if(Var != NULL)
            pBS->FreePool(Var);

        Status = pBS->AllocatePool(EfiBootServicesData, Length, (VOID**)&Var);
        if(EFI_ERROR(Status))
            return Status;

        VarSize = Length;
        Status = ConfigRouting->ConfigToBlock(ConfigRouting, Configuration, Var, &Length, Progress);
    }

    if(EFI_ERROR(Status))
        return Status;

    pRS->SetVariable(Name, &Guid, Attributes, VarSize, Var);

    pBS->FreePool(Var);

    return EFI_SUCCESS;
}

static EFI_STATUS EFIAPI HiiAccessFormCallback(
    IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
    IN EFI_BROWSER_ACTION Action,
    IN EFI_QUESTION_ID QuestionId,
    IN UINT8 Type,
    IN EFI_IFR_TYPE_VALUE *Value,
    OUT EFI_BROWSER_ACTION_REQUEST *ActionRequest
)
{
    return EFI_UNSUPPORTED;
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: SetCallback
//
// Description:
//  EFI_STATUS SetCallback(EFI_HII_IFR_PACK *pIfr,
// UINTN NumberOfCallbacks, CALLBACK_INFO *CallbackInfo,
// CALLBACK_INFO **CallBackFound)
//
// Input:
//
// Output:
//
// Modified:
//
// Referrals:
// 
// Notes:	
//          
//<AMI_PHDR_END>
//*************************************************************************
EFI_STATUS SetCallback(
    EFI_LOADED_IMAGE_PROTOCOL *Image,
	EFI_IFR_FORM_SET *FormSet, UINTN NumberOfCallbacks,
	CALLBACK_INFO *CallbackInfo, CALLBACK_INFO **CallBackFound,
    EFI_HANDLE *CallbackHandle 
)
{
	UINTN i;
	EFI_STATUS Status;
    EFI_HANDLE Handle=NULL;
    EFI_DEVICE_PATH_PROTOCOL *pPath, *pPath2;
    CALLBACK_INFO *CallbackInfoPtr;

    static EFI_HII_CONFIG_ACCESS_PROTOCOL DefaultConfigAccess = {
        HiiAccessExtractConfig, HiiAccessRouteConfig, HiiAccessFormCallback
    };
    static CALLBACK_INFO DefaultCallbackInfo = {
	    NULL,&DefaultConfigAccess, 0, 0, NULL
    };
    static VENDOR_DEVICE_PATH FormSetDevicePathNode = {
        {
            MEDIA_DEVICE_PATH, MEDIA_VENDOR_DP,
            {sizeof(VENDOR_DEVICE_PATH), 0}
        },
        {0}
    };

	for(  i=0
        ;    i<NumberOfCallbacks
          && (      CallbackInfo[i].pGuid == NULL
                ||  guidcmp(&FormSet->Guid,CallbackInfo[i].pGuid) != 0
             )
        ; i++
    );
    if (i==NumberOfCallbacks){
        CallbackInfoPtr = &DefaultCallbackInfo;
    }else{
        CallbackInfoPtr = &CallbackInfo[i];
        if (CallbackInfoPtr->pFormCallback == NULL){
            CallbackInfoPtr->pFormCallback = &DefaultConfigAccess;  
        }else{
            if (CallbackInfoPtr->pFormCallback->ExtractConfig==NULL)
                CallbackInfoPtr->pFormCallback->ExtractConfig = 
                    HiiAccessExtractConfig;
            if (CallbackInfoPtr->pFormCallback->RouteConfig==NULL)
                CallbackInfoPtr->pFormCallback->RouteConfig = 
                    HiiAccessRouteConfig;
            if (CallbackInfoPtr->pFormCallback->Callback==NULL)
                CallbackInfoPtr->pFormCallback->Callback = 
                    HiiAccessFormCallback;
        }
    }
            Status=pBS->HandleProtocol(Image->DeviceHandle, &guidDevicePath, (VOID**)&pPath);
            if (EFI_ERROR(Status)) pPath=NULL;
            pPath = DPAddNode(pPath, Image->FilePath);
            FormSetDevicePathNode.Guid = FormSet->Guid;
            pPath2 = DPAddNode(pPath, &FormSetDevicePathNode.Header);
            pBS->FreePool(pPath);
            Status = pBS->InstallMultipleProtocolInterfaces(
                &Handle, 
                &guidDevicePath, pPath2,
                &gLocalEfiHiiConfigAccessProtocolGuid, CallbackInfoPtr->pFormCallback,
                NULL
            );
			if (EFI_ERROR(Status)) return Status;
    if (CallbackHandle) *CallbackHandle=Handle;
    if (CallBackFound){
        *CallBackFound=  (CallbackInfoPtr == &DefaultCallbackInfo) 
                       ? NULL 
                       : CallbackInfoPtr;
    }
	return EFI_SUCCESS;
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: HiiLibPublishPackages
//
// Description: Publishes submitted array of HII packages into HII database.
//
// Input:
//  IN VOID *PackagePointers - array of pointers to the HII packages
//  IN UINTN NumberOfPackages - number of pointers in the PackagePointers array
//  IN EFI_GUID *PackageGuid - package list GUID
//  IN EFI_HANDLE DriverHandle OPTIONAL - Handle to associate with the package list
//  OUT EFI_HII_HANDLE *HiiHandle - HII handle of the package list
//
// Output:
//  EFI_STATUS
//            
//<AMI_PHDR_END>
//*************************************************************************
EFI_STATUS HiiLibPublishPackages(
    IN VOID *PackagePointers, IN UINTN NumberOfPackages, 
    IN EFI_GUID *PackageGuid, IN EFI_HANDLE DriverHandle OPTIONAL,
    OUT EFI_HII_HANDLE *HiiHandle
){
	EFI_STATUS Status;
    EFI_HII_PACKAGE_LIST_HEADER *PackageList;
    UINTN i;
    UINT32 PackageLength; 
    UINT8 *PackagePtr;
    EFI_HII_PACKAGE_HEADER **Packages = PackagePointers;
    if (NumberOfPackages==0) return EFI_SUCCESS;
    if (   !gHiiDatabase 
        && EFI_ERROR(Status=pBS->LocateProtocol(
                        &gLocalEfiHiiDatabaseProtocolGuid, NULL, (VOID**)&gHiiDatabase
           ))
    ) return Status;
    //calculate the package list length
    PackageLength =   sizeof(EFI_HII_PACKAGE_LIST_HEADER) 
                    + sizeof(EFI_HII_PACKAGE_HEADER); //package list terminator
    for(i=0; i<NumberOfPackages; i++){
        PackageLength += Packages[i]->Length;
    }
    PackageList = Malloc(PackageLength);
    if(PackageList==NULL) return EFI_OUT_OF_RESOURCES;
    PackageList->PackageListGuid = *PackageGuid;
    PackageList->PackageLength = PackageLength;

    PackagePtr = (UINT8*)(PackageList+1);
    for(  i=0; i<NumberOfPackages; i++){
        pBS->CopyMem(PackagePtr, Packages[i], Packages[i]->Length);
        PackagePtr += Packages[i]->Length;
    }
    ((EFI_HII_PACKAGE_HEADER *)PackagePtr)->Length = sizeof(EFI_HII_PACKAGE_HEADER);
    ((EFI_HII_PACKAGE_HEADER *)PackagePtr)->Type = EFI_HII_PACKAGE_END;

    Status = gHiiDatabase->NewPackageList(
            gHiiDatabase, PackageList, DriverHandle, HiiHandle
    );
    pBS->FreePool(PackageList);
    return Status;
}

/**
  Returns a pointer to an allocated buffer that contains the best matching language 
  from a set of supported languages.  
  
  This function works with RFC 4646 language codes. The language 
  code returned is allocated using AllocatePool().  The caller is responsible for 
  freeing the allocated buffer using FreePool().  This function supports a variable
  argument list that allows the caller to pass in a prioritized list of language 
  codes to test against all the language codes in SupportedLanguages 

  @param[in]  SupportedLanguages  A pointer to a Null-terminated ASCII string that
                                  contains a set of semicolon separated RFC 4646 language codes.
  @param[in]  ...                 A variable argument list that contains pointers to 
                                  Null-terminated ASCII strings that contain one or more
                                  RFC 4646 language codes.
                                  The first language code from each of these language
                                  code lists is used to determine if it is an exact or
                                  close match to any of the language codes in 
                                  SupportedLanguages.  The matching algorithm from RFC 4647
                                  is used to determine if a close match is present.  If 
                                  an exact or close match is found, then the matching
                                  language code from SupportedLanguages is returned.  If
                                  no matches are found, then the next variable argument
                                  parameter is evaluated.  The variable argument list 
                                  is terminated by a NULL.

  @retval NULL   The best matching language could not be found in SupportedLanguages.
  @retval NULL   There are not enough resources available to return the best matching 
                 language.
  @retval Other  A pointer to a Null-terminated ASCII string that is the best matching 
                 language in SupportedLanguages.
**/
static CHAR8* EFIAPI FindBestLanguage (CHAR8 *SupportedLanguages,  ... ) {
#define IsEndOfLanguage(Lang) (*(Lang) == 0 || *(Lang) == ';')
    VA_LIST Args;
    CHAR8 *Language, *BestMatchStart = NULL, *BestMatchEnd = NULL, *Supported, *Lang;
    UINTN Length;
	
	if (SupportedLanguages == NULL) return NULL;
    VA_START (Args, SupportedLanguages);
    while ((Language = VA_ARG (Args, CHAR8 *)) != NULL) {
		Supported = SupportedLanguages;
		BestMatchStart = NULL;
		do{
			BOOLEAN PartialMatch = FALSE;
			CHAR8 *SupportedStart, *BestMatch;			
			BestMatch = Language;
			SupportedStart = Supported;
			for(  Lang = Language
				; !IsEndOfLanguage(Lang)
				; Lang++, Supported++
			){
				if (*Lang =='-') PartialMatch = TRUE;
				if  (*Lang != *Supported || IsEndOfLanguage(Supported)) break;
			}
			while(!IsEndOfLanguage(Supported)) Supported++;
			if ((PartialMatch || IsEndOfLanguage(Lang))&& BestMatch-Language < Lang-Language){
				BestMatch = Lang;
				BestMatchStart = SupportedStart;
				BestMatchEnd = Supported;
			}
			if (*Supported==';') Supported++;
		}while (*Supported != 0 && !IsEndOfLanguage(Lang));
		if (BestMatchStart != NULL) break;
	}
    VA_END (Args);
	// No matches were found 
	if ((BestMatchStart == NULL) || (BestMatchEnd == NULL)) return NULL;
	Length = BestMatchEnd - BestMatchStart;
    Language = Malloc (Length + 1);
    if (Language == NULL)  return NULL;
    MemCpy (Language, BestMatchStart, Length);
	Language[Length]=0;
    return Language;
}

static CHAR8* GetSupportedLanguages (IN EFI_HII_HANDLE   HiiHandle) {
    EFI_STATUS  Status;
    CHAR8 *SupportedLanguages = NULL;
	UINTN Size = 0;
    
    // Retrieve list of supported languages
	if (HiiHandle == NULL) return NULL;
    if (   !HiiString
        && EFI_ERROR(pBS->LocateProtocol(&gLocalEfiHiiStringProtocolGuid, NULL, (VOID**)&HiiString))
    ) return NULL;
	
    Status = HiiString->GetLanguages(HiiString, HiiHandle, SupportedLanguages, &Size);
    if (Status != EFI_BUFFER_TOO_SMALL) return NULL;
    SupportedLanguages = Malloc(Size);
    Status = HiiString->GetLanguages(HiiString, HiiHandle, SupportedLanguages, &Size);
	if (EFI_ERROR(Status)){
		pBS->FreePool(SupportedLanguages);
		return NULL;
	}
	return SupportedLanguages;
}

static EFI_STATUS GetAnyLanguageString(
	CHAR8 *SupportedLanguages, EFI_HII_STRING_PROTOCOL *LocalHiiString,
	IN EFI_HII_HANDLE HiiHandle, IN STRING_REF StringId, 
	IN OUT UINTN *StringSize, OUT EFI_STRING String
){
	EFI_STATUS Status = EFI_INVALID_PARAMETER; // if the Supported languages is empty, this will ensure an error is reported
	CHAR8 *LangStart, *LangEnd;
	//Find string representation by trying all the supported languages
	
	//Iterate over languages in the SupportedLanguages list
	for(LangStart = SupportedLanguages; *LangStart!=0; ){
		CHAR8 Char;
		//Find the end of a language code
		for(LangEnd = LangStart; *LangEnd!=';'&& *LangEnd!=0; LangEnd++);
		//Terminate current language with 0 to call GetString
		Char = *LangEnd; // save the original char
		*LangEnd = 0;
		Status = LocalHiiString->GetString(
			LocalHiiString, LangStart, HiiHandle,
			StringId, String, StringSize, NULL
		);
		if (Status!=EFI_INVALID_LANGUAGE) break;
		if (Char==0) break;
		LangStart = LangEnd + 1; // continue with the next language
	}
	return Status;
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: HiiLibGetString
//
// Description: Reads string from the HII database in current language.
//
// Input:
//  IN EFI_HII_HANDLE HiiHandle - Package list handle
//  IN EFI_STRING_ID StringId - ID of the string to read
//  IN OUT UINTN *StringSize - On entry, points to the size of the buffer pointed to by String, 
//      in bytes. On return, points to the length of the string, in bytes.
//  OUT EFI_STRING String - Points to the output null-terminated string.
//
// Output:
//   EFI_STATUS
//          
//<AMI_PHDR_END>
//*************************************************************************
EFI_STATUS HiiLibGetString(
	IN EFI_HII_HANDLE HiiHandle, IN STRING_REF StringId, 
	IN OUT UINTN *StringSize, OUT EFI_STRING String
){
    EFI_STATUS Status;
	CHAR8 *SupportedLanguages, *BestLanguage;
	CHAR8 *PlatformLang;
    
    if (   !HiiString 
        && EFI_ERROR(pBS->LocateProtocol(&gLocalEfiHiiStringProtocolGuid, NULL, (VOID**)&HiiString))
    ) return EFI_NOT_FOUND;
    PlatformLang = HiiLibGetPlatformLanguageInternal(TRUE);
	SupportedLanguages = GetSupportedLanguages (HiiHandle);
	if (SupportedLanguages == NULL) return EFI_NOT_FOUND;
	// Find the best supported language.
    // If the string representation is not defined for a PlatformLang, default language or English,
    // use the first supported language.
	BestLanguage = FindBestLanguage(
		SupportedLanguages, 
		PlatformLang, 
		(CHAR8*)DefaultLanguageCode, LANGUAGE_CODE_ENGLISH, 
		SupportedLanguages,
		NULL
	);
	if (BestLanguage == NULL){
		pBS->FreePool(SupportedLanguages);
		return EFI_NOT_FOUND;
	}

    Status = HiiString->GetString(
        HiiString, BestLanguage, HiiHandle,StringId, String, StringSize, NULL
    );
	pBS->FreePool(BestLanguage);
    // If the string representation for the PlatformLang is not defined,
    // try all the languages supported by the package.
    // If still no luck, try English
    if (Status==EFI_INVALID_LANGUAGE)
		Status = GetAnyLanguageString(
			SupportedLanguages,HiiString,
			HiiHandle,StringId,StringSize,String
		);
	pBS->FreePool(SupportedLanguages);
    return Status;
}

EFI_STATUS HiiLibGetStringEx(
	IN EFI_HII_HANDLE HiiHandle, IN STRING_REF StringId, IN CHAR8 *Language,
	IN OUT UINTN *StringSize, OUT EFI_STRING String
){
    EFI_STATUS Status;
	CHAR8 *SupportedLanguages, *BestLanguage;
	CHAR8 *PlatformLang;
    
    if (   !HiiString 
        && EFI_ERROR(pBS->LocateProtocol(&gLocalEfiHiiStringProtocolGuid, NULL, (VOID**)&HiiString))
    ) return EFI_NOT_FOUND;
    PlatformLang = HiiLibGetPlatformLanguageInternal(FALSE);
	SupportedLanguages = GetSupportedLanguages (HiiHandle);
	if (SupportedLanguages == NULL) return EFI_NOT_FOUND;
	// Find the best supported language.
    // If the string representation is not defined for a PlatformLang, default language or English,
    // use the first supported language.
	BestLanguage = FindBestLanguage(
		SupportedLanguages, 
		Language, PlatformLang, 
		(CHAR8*)DefaultLanguageCode, LANGUAGE_CODE_ENGLISH,
		SupportedLanguages,
		NULL
	);
	if (BestLanguage == NULL){
		pBS->FreePool(SupportedLanguages);
		return EFI_NOT_FOUND;
	}

    Status = HiiString->GetString(
        HiiString, BestLanguage, HiiHandle,StringId, String, StringSize, NULL
    );
	pBS->FreePool(BestLanguage);
    // If the string representation for the PlatformLang is not defined,
    // try all the languages supported by the package.
    // If still no luck, try English
    if (Status==EFI_INVALID_LANGUAGE)
		Status = GetAnyLanguageString(
			SupportedLanguages,HiiString,
			HiiHandle,StringId,StringSize,String
		);
	pBS->FreePool(SupportedLanguages);
    return Status;
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: HiiLibSetString
//
// Description: Updates string in the HII database in all languages supported by the package list.
//
// Input:
//  IN EFI_HII_HANDLE HiiHandle - Package list handle
//  IN EFI_STRING_ID StringId - ID of the string to udpate
//  IN EFI_STRING String - Points to the new null-terminated string.
//
// Output:
//   EFI_STATUS
//          
//<AMI_PHDR_END>
//*************************************************************************
EFI_STATUS HiiLibSetString(
	IN EFI_HII_HANDLE HiiHandle, IN STRING_REF StringId, IN EFI_STRING String
){
	CHAR8 *LanguageList = NULL;
	UINTN Size = 0;
    EFI_STATUS Status;

    if (   !HiiString 
        && EFI_ERROR(pBS->LocateProtocol(&gLocalEfiHiiStringProtocolGuid, NULL, (VOID**)&HiiString))
    ) return EFI_NOT_FOUND;

    Status = HiiString->GetLanguages(HiiString, HiiHandle, LanguageList, &Size);
    if (Status!=EFI_BUFFER_TOO_SMALL) return Status;
    LanguageList = Malloc(Size);
    Status = HiiString->GetLanguages(HiiString, HiiHandle, LanguageList, &Size);
    if (!EFI_ERROR(Status)){
        CHAR8 *CurrentLang, *EndOfCurrentLang;
        EndOfCurrentLang = LanguageList;
        while(EndOfCurrentLang < LanguageList+Size){
            CHAR8 OriginalChar;
            CurrentLang = EndOfCurrentLang;
            while(*EndOfCurrentLang!=';'&&*EndOfCurrentLang!=0) EndOfCurrentLang++;
            OriginalChar = *EndOfCurrentLang;
            *EndOfCurrentLang = 0;
            Status = HiiString->SetString(
                HiiString, HiiHandle, StringId, CurrentLang, String, NULL
            );
            if (EFI_ERROR(Status)) break;
            *EndOfCurrentLang = OriginalChar;
            EndOfCurrentLang++;
        }
    }
    pBS->FreePool(LanguageList);
    return Status;
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: HiiLibGetBrowserData
//
// Description: Retrieves uncommitted state data from the HII browser.
//  Only works in UEFI 2.1 mode.
//
// Input:
//   IN OUT UINTN *BufferSize - A pointer to the size of the buffer associated with Buffer. 
//     On input, the size in bytes of Buffer. On output, the size of data returned in Buffer.
//   OUT VOID *Buffer - A data returned from an IFR browser. 
//   IN CONST EFI_GUID *VarStoreGuid OPTIONAL - An optional field to indicate the target variable GUID name to use.
//   IN CONST CHAR16 *VarStoreName  OPTIONAL  - An optional field to indicate the target variable name.
//
// Output:
//   EFI_STATUS
//          
//<AMI_PHDR_END>
//*************************************************************************
EFI_STATUS HiiLibGetBrowserData(
    IN OUT UINTN *BufferSize, OUT VOID *Buffer, 
    IN CONST EFI_GUID *VarStoreGuid OPTIONAL,
    IN CONST CHAR16 *VarStoreName  OPTIONAL
){
    UINTN StringDataSize = 0;
    CHAR16 *StringData = NULL;
	CHAR16 *ConfigResp;
	UINTN ConfigRespSize;
    EFI_STATUS Status;
    EFI_STRING Progress;

    if (   !FormBrowser 
        && EFI_ERROR(pBS->LocateProtocol(&gLocalEfiFormBrowser2ProtocolGuid, NULL, (VOID**)&FormBrowser))
    ) return EFI_NOT_FOUND;
    if (   !HiiConfigRouting 
        && EFI_ERROR(pBS->LocateProtocol(&gLocalEfiHiiConfigRoutingProtocolGuid, NULL, (VOID**)&HiiConfigRouting))
    ) return EFI_NOT_FOUND;

    Status = FormBrowser->BrowserCallback(
        FormBrowser, &StringDataSize, StringData, TRUE, 
        VarStoreGuid, VarStoreName
    );
    if (Status!=EFI_BUFFER_TOO_SMALL) return Status;
	// We'll need to construct a proper <ConfigResp> string by 
	// appending dummy <ConfigHdr> at the beginning of a string returned by BrowserCallback.
	// This is required because
	// BrowserCallback returns string without <ConfigHdr>
	// and ConfigToBlock expects sring with <ConfigHdr>.
	
	// <DataSize> + <Dummy ConfigHdr Size> - <Terminating zero>
	ConfigRespSize = StringDataSize + sizeof(DummyConfigHeader)-sizeof(CHAR16);
    ConfigResp = Malloc(ConfigRespSize);
    StringData = ConfigResp + UnicodeSPrint( ConfigResp, ConfigRespSize, L"%s",DummyConfigHeader);
    Status = FormBrowser->BrowserCallback(
        FormBrowser, &StringDataSize, StringData, TRUE, 
        VarStoreGuid, VarStoreName
    );
    if (!EFI_ERROR(Status)){
        StringDataSize = *BufferSize;       //preserve passed buffer size value, as 
                                            //ConfigToBlock may change it as per UEFI 2.1 spec
                                            //it will contain index of last updated byte
        Status = HiiConfigRouting->ConfigToBlock(
            HiiConfigRouting, ConfigResp, Buffer, BufferSize, &Progress
        );
        *BufferSize = StringDataSize;       //restore original value
    }
    pBS->FreePool(ConfigResp);
    return Status;
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: HiiLibSetBrowserData
//
// Description: Updates uncommitted state data of the HII browser.
//  Only works in UEFI 2.1 mode.
//
// Input:
//   IN UINTN BufferSize - Size of the buffer associated with Buffer. 
//   IN VOID *Buffer - A data to send to an IFR browser. 
//   IN CONST EFI_GUID *VarStoreGuid OPTIONAL - An optional field to indicate the target variable GUID name to use.
//   IN CONST CHAR16 *VarStoreName  OPTIONAL  - An optional field to indicate the target variable name.
//
// Output:
//   EFI_STATUS
//          
//<AMI_PHDR_END>
//*************************************************************************
EFI_STATUS HiiLibSetBrowserData(
    IN UINTN BufferSize, IN VOID *Buffer, 
    IN CONST EFI_GUID *VarStoreGuid, OPTIONAL 
    IN CONST CHAR16 *VarStoreName  OPTIONAL
){
    UINTN StringDataSize = 0;
    CHAR16 *StringData = NULL;
    EFI_STATUS Status;
    EFI_STRING Config;
    EFI_STRING Progress;
	CHAR16 *ConfigResp;
	UINTN ConfigRespSize;
	
    if (   !FormBrowser 
        && EFI_ERROR(pBS->LocateProtocol(&gLocalEfiFormBrowser2ProtocolGuid, NULL, (VOID**)&FormBrowser))
    ) return EFI_NOT_FOUND;
    if (   !HiiConfigRouting 
        && EFI_ERROR(pBS->LocateProtocol(&gLocalEfiHiiConfigRoutingProtocolGuid, NULL, (VOID**)&HiiConfigRouting))
    ) return EFI_NOT_FOUND;

    Status = FormBrowser->BrowserCallback(
        FormBrowser, &StringDataSize, StringData, TRUE, 
        VarStoreGuid, VarStoreName
    );
    if (Status!=EFI_BUFFER_TOO_SMALL) return Status;
	// We'll need to construct a proper <ConfigResp> string by 
	// appending dummy <ConfigHdr> at the beginning of a string returned by BrowserCallback.
	// This is required because
	// BrowserCallback returns string without <ConfigHdr>
	// and BlockToConfig expects sring with <ConfigHdr>.
	
	// <DataSize> + <Dummy ConfigHdr Size> - <Terminating zero>
	ConfigRespSize = StringDataSize + sizeof(DummyConfigHeader)-sizeof(CHAR16);
    ConfigResp = Malloc(ConfigRespSize);
    StringData = ConfigResp + UnicodeSPrint(ConfigResp, ConfigRespSize, L"%s",DummyConfigHeader);
    Status = FormBrowser->BrowserCallback(
        FormBrowser, &StringDataSize, StringData, TRUE, 
        VarStoreGuid, VarStoreName
    );
    if (EFI_ERROR(Status)){
		pBS->FreePool(ConfigResp);
        return Status;
	}

//we have StringData in format &OFFSET=XXXX&WIDTH=XXXX&VALUE=XXXX&OFFSET=...
//in order for function BlockToConfig to work we need to modify StringData as follows:
//&OFFSET=XXXX&WIDTH=XXXX&OFFSET=... (i.e. remove all &VALUE=XXX patterns)

    StripValuePattern(ConfigResp, ConfigRespSize);

    Status = HiiConfigRouting->BlockToConfig(
        HiiConfigRouting, ConfigResp, Buffer, BufferSize,
        &Config, &Progress
    );
    if(!EFI_ERROR(Status)) {
        StringDataSize = StrSize16(Config);
        Status = FormBrowser->BrowserCallback(
            FormBrowser, &StringDataSize, Config, FALSE, 
            VarStoreGuid, VarStoreName
        );
        pBS->FreePool(Config);
    }

    pBS->FreePool(ConfigResp);
    return Status;
}


HII_UTILITIES_PROTOCOL *GetHiiUtilitiesInterface(){
    static HII_UTILITIES_PROTOCOL *HiiUtilities = NULL;
    if (   HiiUtilities == NULL
        && EFI_ERROR(pBS->LocateProtocol(
                        &gLocalHiiUtilitiesProtocolGuid, NULL, (VOID**)&HiiUtilities
           ))
    //if LocateProtocol has failed, HiiUtilities is undefined.
    //set it to NULL.
    ) HiiUtilities = NULL; 
    return HiiUtilities;
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: LoadStrings
//
// Description:
//  EFI_STATUS LoadStrings(EFI_HANDLE ImageHandle,
// EFI_HII_HANDLE *pHiiHandle) - loads HII string packages associated with 
// the specified image and publishes them to the HII database
//
// Input:
//  EFI_HANDLE ImageHandle - Image Handle
//  EFI_HII_HANDLE *pHiiHandle - HII package list handle
//
// Output:
//   EFI_STATUS
//
//<AMI_PHDR_END>
//*************************************************************************
EFI_STATUS LoadStrings(
	EFI_HANDLE ImageHandle, EFI_HII_HANDLE *pHiiHandle
)
{
    EFI_STATUS                      Status;
    EFI_HII_PACKAGE_LIST_HEADER     *PackageList;
    EFI_HII_DATABASE_PROTOCOL       *LocalHiiDatabase;
    
    //
    // Retrieve HII package list from ImageHandle
    //
    Status = pBS->OpenProtocol (
        ImageHandle,
        &gLocalEfiHiiPackageListProtocolGuid,
        (VOID **) &PackageList,
        ImageHandle,
        NULL,
        EFI_OPEN_PROTOCOL_GET_PROTOCOL
    );
    if (EFI_ERROR (Status)) {
    	TRACE((DEBUG_ERROR,"gEfiHiiPackageListProtocolGuid protocol is not found\n"));
        return Status;
    }
  
    Status = pBS->LocateProtocol (
        &gLocalEfiHiiDatabaseProtocolGuid,
        NULL,
        (VOID**)&LocalHiiDatabase
    );
    if (EFI_ERROR (Status)) {
    	TRACE((DEBUG_ERROR,"gEfiHiiDatabaseProtocolGuid protocol is not found\n"));
        return Status;
    }
    
    //
    // Publish HII package list to HII Database.
    //
    Status = LocalHiiDatabase->NewPackageList (
        LocalHiiDatabase,
        PackageList,
        NULL,
        pHiiHandle
    );
    TRACE((DEBUG_ERROR,"NewPackageList status: %r\n",Status));
    return Status;
}

//*************************************************************************
//<AMI_PHDR_START>
//
// Name: LoadResources
//
// Description:
//  EFI_STATUS LoadResources(EFI_HANDLE ImageHandle,
// UINTN NumberOfCallbacks, CALLBACK_INFO *pCallBack,
// INIT_HII_PACK InitFunction) - loads HII packages associated with 
// the specified image and publishes them to the HII database
//
// Input:
//  IN EFI_HANDLE ImageHandle - Image Handle
//  IN UINTN NumberOfCallbacks - Number of the structures in the pCallBack array
//	IN OUT CALLBACK_INFO *pCallBack - Array of IFR package descriptors.
//  IN INIT_HII_PACK InitFunction - initialization function to be launched once resources are published.
//
// Output:
//   EFI_STATUS
//          
//<AMI_PHDR_END>
//*************************************************************************
EFI_STATUS LoadResources(
	EFI_HANDLE ImageHandle, UINTN NumberOfCallbacks,
	CALLBACK_INFO *pCallBack, INIT_HII_PACK InitFunction
)
{
    EFI_STATUS                      Status;
    EFI_HII_PACKAGE_LIST_HEADER     *PackageList;
    EFI_HII_DATABASE_PROTOCOL       *LocalHiiDatabase;
    EFI_LOADED_IMAGE_PROTOCOL       *Image;
    EFI_HII_HANDLE                  mHiiHandle;
    static EFI_GUID gLocalEfiLoadedImageProtocolGuid = EFI_LOADED_IMAGE_PROTOCOL_GUID;
    static BOOLEAN DlistInitDone = FALSE;
    PRIVATE_CALLBACK_INFO *PrivateCallbackInfo = NULL;
    EFI_IFR_FORM_SET *FormSet = NULL;
    
    if (EFI_ERROR(Status=pBS->HandleProtocol(ImageHandle, &gLocalEfiLoadedImageProtocolGuid, (VOID**)&Image))) return Status;
    
    //
    // Retrieve HII package list from ImageHandle
    //
    Status = pBS->OpenProtocol (
        ImageHandle,
        &gLocalEfiHiiPackageListProtocolGuid,
        (VOID **) &PackageList,
        ImageHandle,
        NULL,
        EFI_OPEN_PROTOCOL_GET_PROTOCOL
    );
    if (EFI_ERROR (Status)) {
        return Status;
    }
  
    Status = pBS->LocateProtocol (
        &gLocalEfiHiiDatabaseProtocolGuid,
        NULL,
        (VOID**)&LocalHiiDatabase
    );
    if (EFI_ERROR (Status)) {
        return Status;
    }
  
    //for(i=0; i<NumberOfIfrPackages; i++)
    {
        EFI_HANDLE CallbackHandle = NULL;
        EFI_HII_PACKAGE_HEADER *IfrPackagePtr;
        CALLBACK_INFO *pCallBackFound = NULL;

        for (IfrPackagePtr = (EFI_HII_PACKAGE_HEADER*)(PackageList+1);
             IfrPackagePtr < (EFI_HII_PACKAGE_HEADER*)((UINT8*)PackageList+PackageList->PackageLength);
             IfrPackagePtr = (EFI_HII_PACKAGE_HEADER*)((UINT8*)IfrPackagePtr+IfrPackagePtr->Length))
        {
            if (IfrPackagePtr->Type == EFI_HII_PACKAGE_FORMS) {
                break;
            }
        }
        FormSet = (EFI_IFR_FORM_SET*)(IfrPackagePtr+1);
        Status = SetCallback(
                        Image, 
                        FormSet,
                        NumberOfCallbacks,
                        pCallBack,
                        &pCallBackFound,
                        &CallbackHandle
                        );
        
        if (!EFI_ERROR(Status)) {
            
            if (!DlistInitDone) {
                InitializeListHead(&gPrivateCallbackList);
                DlistInitDone = TRUE;
            }
            
            //
            // Publish HII package list to HII Database.
            //
            Status = LocalHiiDatabase->NewPackageList (
                LocalHiiDatabase,
                PackageList,
                CallbackHandle,
                &mHiiHandle
            );
            
            if (EFI_ERROR (Status)) {
                return Status;
            }
            
            Status = pBS->AllocatePool(
                            EfiBootServicesData, 
                            sizeof(PRIVATE_CALLBACK_INFO), 
                            (VOID**)&PrivateCallbackInfo);
            if(!EFI_ERROR(Status)) {
                PrivateCallbackInfo->HiiAccessProtocol = pCallBackFound->pFormCallback;
                PrivateCallbackInfo->CallbackHandle = CallbackHandle;
                PrivateCallbackInfo->HiiHandle = mHiiHandle;
                pBS->CopyMem (&PrivateCallbackInfo->FormGuid,&FormSet->Guid,sizeof(EFI_GUID));
                InsertTailList(&gPrivateCallbackList,&PrivateCallbackInfo->Link);
            }
            if (pCallBackFound) pCallBackFound->HiiHandle = mHiiHandle;
            if (InitFunction) InitFunction(mHiiHandle, pCallBackFound);
            pCallBackFound = NULL;
        }
    }
  return EFI_SUCCESS;
}

