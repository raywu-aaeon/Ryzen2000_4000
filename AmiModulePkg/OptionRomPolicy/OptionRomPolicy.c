//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file OptionRomPolicy.c
    Option ROM Dispatch Policy Dynamic Setup screen 
    routines and implementation
**/

#include <Token.h>
#include <OptionRomPolicyStrDefs.h>
#include <AmiDxeLib.h>
#include <PciBus.h>
#include <PciHostBridge.h>
#include <PciSetup.h>
#include <Setup.h>
#include "OptionRomPolicyPrivate.h"


///Protocols Used
#include <Protocol/DevicePath.h>
#include <Protocol/PciIo.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/LegacyBiosExt.h>
#include <Protocol/AmiOptionRomPolicy.h>
#include <Protocol/AmiCsmOpromPolicy.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/DevicePath.h>
#include <Protocol/PciIo.h>


///Library used
#include <Library/HiiLib.h>
#include <Library/PrintLib.h>
#include <Library/AmiSdlLib.h>
#include <Library/AmiPciBusLib.h>
#include <Library/AmiHiiUpdateLib.h>
#include <Library/DevicePathLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

///  Global Variable Definitions
BOOLEAN             gCsmSupported = FALSE;

EFI_HII_HANDLE      gRomHiiHandle = NULL;

ROM_POLICY_INFO     gOptRomData;

ROM_POLICY_INFO     *gRomPolicyDataPtr=&gOptRomData;

SETUP_DATA          gSetupData;

CSM_SETUP_DATA      gCsmSetup;  

ROM_SETUP_DATA      *gRomSetupPtr=NULL;

OPROM_PCI_DEV_DATA_LIST    *gOpromPciDevDataList = NULL;

EFI_GUID            RomSetupGuid   = ROM_FORM_SET_GUID;

EFI_GUID            AmiSetupGuid   = SETUP_GUID;

UINT32              gSlotsToShow[]={ROM_SETUP_SLOTS_TO_SHOW};

UINTN               gNumberOfSlotsToShow=sizeof(gSlotsToShow)/sizeof(UINT32);

BOOLEAN             gGopFound=FALSE;

BOOLEAN             gInitRomIfrEntered = FALSE;

UINT32              gEntryVgaIdx=0;

UINT8               gEntryGrop=0;

UINT8               gEntryItem=0;

UINTN               gRomIndex=1000;

UINT32              gCsmCmnAttributes=(EFI_VARIABLE_BOOTSERVICE_ACCESS);

UINT32              gRomCmnAttributes=(EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS);

UINT32              gRomFbAttributes=(EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS);

UINT32              gSetupAttributes=(EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS);

EFI_STATUS 
EFIAPI 
RomBrowserCallback(
    IN  CONST   EFI_HII_CONFIG_ACCESS_PROTOCOL   *This,
    IN  EFI_BROWSER_ACTION                       Action,
    IN  EFI_QUESTION_ID                          KeyValue,
    IN  UINT8                                    Type,
    IN  EFI_IFR_TYPE_VALUE                       *Value,
    OUT EFI_BROWSER_ACTION_REQUEST               *ActionRequest
);

EFI_HII_CONFIG_ACCESS_PROTOCOL CallBack = { NULL, NULL, RomBrowserCallback };

EFI_GUID RomFormsetGuid = ROM_FORM_SET_GUID;

CALLBACK_INFO SetupCallBack[] =
{
    // Last field in every structure will be filled by the Setup
    { &RomFormsetGuid, &CallBack, ROM_FORM_SET_CLASS, 0, 0},
};

EFI_GUID gEfiIfrTianoGuid = EFI_IFR_TIANO_GUID;

AMI_BOARD_INIT_PROTOCOL     *gPciInitProtocol = NULL;

AMI_CSM_OPROM_POLICY_PROTOCOL gAmiCsmOpromPolicy = { NULL, NULL };
AMI_OPROM_POLICY_PROTOCOL gAmiOpromPolicy = { NULL, NULL };

VOID *gCsmOpromPolicyOverrideRegistration;
VOID *gOpromPolicyOverrideRegistration;
VOID *gGopProtocolRegistration;

///Forward declaration
EFI_STRING_ID GetHelpStrId(PCI_DEV_INFO *Dev);
EFI_STRING_ID GetClassStrId(PCI_DEV_INFO *Dev);
EFI_STATUS UpdateItemStrings(ROM_POLICY_CB_DATA *RomItemData);
EFI_STATUS InitRomPolicyData(ROM_POLICY_INFO *RomIfrInfo);
VOID SortData(VOID);
VOID InitDriverVersionString(VOID);
EFI_STATUS GetSetRomData(BOOLEAN Get);
EFI_STATUS GetSetCsmData( UINT8 Get);
UINT8 GetOpRomPolicy(UINT8 PciClass);
VOID CreateRomCbItems(ROM_POLICY_INFO *RomIfrInfo);
VOID InitRomIfr(IN EFI_EVENT Event, IN VOID *Context);
EFI_STATUS CheckRomPolicyVgaStatus(BOOLEAN CallbackMode);
BOOLEAN CheckOBoardAslNameArrayElements(UINT8 *AslName);
EFI_STATUS SetRomPolicyDefaults(BOOLEAN UpdateVar);
VOID RestoreDefaults(VOID);
VOID ClearFailToBootVar(IN EFI_EVENT Event, IN VOID *Context);
EFI_STATUS CollectPciOnboardDevicesDataFromSdl(VOID);
EFI_STATUS CollectPciSlotDevicesDataFromSdl(VOID);
BOOLEAN SearchMatchingSlotinShowList(
    UINTN      SlotShowIndex,
    UINTN      ListSlotDeviceCount
);
EFI_STATUS AppendUnlistedSlotItems(VOID);
EFI_STATUS InitRomDataFromSdl(VOID);

AMI_SDL_PCI_DEV_INFO* 
GetMatchingSdlDevice (
    ROM_POLICY_VAR        *rp, 
    UINTN                 *SdlIdx
);

EFI_STATUS  InitRomDataFromVar(BOOLEAN Extra);
VOID UpdateRomPolicyToUefiWhenCsmUnavailable(EFI_EVENT, VOID*);
VOID UpdateRomPolicyToDefaultUefi(VOID);
VOID OptionRomPolicyLegacyBiosCallback(EFI_EVENT, VOID*);
EFI_STATUS CheckUefiOpRomPolicy(
    IN  AMI_OPROM_POLICY_PROTOCOL *This,
    IN  UINT8                     PciClass
);
EFI_STATUS CheckUefiOpRomPolicyByPciHandle(
    IN  AMI_CSM_OPROM_POLICY_PROTOCOL *This,
    IN  EFI_HANDLE                PciHandle
);
VOID ProcessOpRom(
    IN OPTIONAL AMI_CSM_PLATFORM_POLICY_DATA *OpRomStartEndProtocol
);
VOID CsmOpromPolicyOverrideCallback (EFI_EVENT, VOID*);
VOID OpromPolicyOverrideCallback (EFI_EVENT, VOID*);
VOID* LocateInterfaceFromDevPath(
    EFI_DEVICE_PATH_PROTOCOL    **DevicePath, 
    EFI_GUID                    *ProtocolGuid, 
    EFI_HANDLE                  *HandlePtr
);
VOID GopProtocolCallback (EFI_EVENT,  VOID*);


/**
  Get Option Rom Help Item String ID.
  
  The function generates Help String for the item
  and return it.
  
 @param[in]  Dev    Pointer to a private PCI_DEV_INFO structure

 @return            Help String Id
**/
EFI_STRING_ID 
GetHelpStrId (
  PCI_DEV_INFO  *Dev
  )
{
    EFI_STRING            TempString1;
    EFI_STRING            On = L"X";
    EFI_STRING            Off = L" ";
    EFI_STRING            UefiOprom = Off, LegacyOprom = Off;
    EFI_STRING_ID         StringId = 0;
    UINTN                 Index;
    CHAR16                String1 [MAX_BUFFER_LEN];
    CHAR16                String2 [MAX_BUFFER_LEN];
    AMI_SDL_PCI_DEV_INFO  *DevSdlInfo;

    ZeroMem (String1, sizeof(String1));
    ZeroMem (String2, sizeof(String2));

//------------------
    //if (Dev->AmiSdlPciDevData == NULL) StringId = STRING_TOKEN (STR_ROM_ITEM_HELP_SLOT_DONT); 
    if (Dev->AmiSdlPciDevData->PciDevFlags.Bits.OnBoard) {

        for (Index = 0; Index < Dev->SdlDevCount; Index++) {
            DevSdlInfo = &gSdlPciData->PciDevices[Dev->SdlIdxArray [Index]];
            if (DevSdlInfo->PciDevFlags.Bits.UefiDriverBin) UefiOprom = On; 
            if (DevSdlInfo->PciDevFlags.Bits.StdPciRom) LegacyOprom = On; 
        }

        //If no embedded through SDL ROMs there, try to check Rom Status;
        if (Dev->AmiRomPolicy->RomStatus & AMI_OPTION_ROM_POLICY_UEFI) UefiOprom = On;
        if (Dev->AmiRomPolicy->RomStatus & AMI_OPTION_ROM_POLICY_LEGACY) LegacyOprom = On;

        TempString1 = HiiGetString (gRomHiiHandle, STRING_TOKEN (STR_ROM_ITEM_HELP_ONBOARD), NULL);
        if (TempString1 != NULL) {
            UnicodeSPrint (String1, sizeof (String1), TempString1, UefiOprom, LegacyOprom,
               Dev->DevVenId.VenId, Dev->DevVenId.DevId,
               Dev->RbIo->SegmentNumber, Dev->Address.Addr.Bus,
               Dev->Address.Addr.Device, Dev->Address.Addr.Function);

           StringId = HiiSetString (gRomHiiHandle, 0, String1, NULL);
           FreePool (TempString1);
        }
    } else {
        if (Dev->AmiRomPolicy->RomStatus & AMI_OPTION_ROM_POLICY_UEFI) UefiOprom = On;
        if (Dev->AmiRomPolicy->RomStatus & AMI_OPTION_ROM_POLICY_LEGACY) LegacyOprom = On;

        if(Dev->AmiRomPolicy->RomStatus) {
            if(Dev->AmiRomPolicy->BaseClass!=Dev->Class.BaseClassCode) {
                EFI_STRING TempString2;

                //if this is a bridged device on the slot we should tell customer what it is...
                TempString1 = HiiGetString (gRomHiiHandle, STRING_TOKEN (STR_ROM_ITEM_HELP_SLOT_HAVE), NULL);
                switch (Dev->AmiRomPolicy->BaseClass) {
                case PCI_CL_NETWORK:
                    TempString2 = HiiGetString (gRomHiiHandle,STRING_TOKEN (STR_ROM_HELP_NETWORK_BEHIND), NULL);
                    break;

                case PCI_CL_MASS_STOR:
                    TempString2 = HiiGetString (gRomHiiHandle,STRING_TOKEN (STR_ROM_HELP_STORAGE_BEHIND), NULL);
                    break;

                case PCI_CL_DISPLAY:
                    TempString2 = HiiGetString (gRomHiiHandle,STRING_TOKEN (STR_ROM_HELP_DISPLAY_BEHIND), NULL);
                    break;

                default:
                    TempString2 = HiiGetString (gRomHiiHandle, STRING_TOKEN (STR_ROM_HELP_OTHER_BEHIND), NULL);
                    break;
                }
                if ((TempString1 != NULL) && (TempString2 != NULL)) {
                    UnicodeSPrint (String2, sizeof (String2), TempString1, UefiOprom, LegacyOprom,
                         Dev->DevVenId.VenId, Dev->DevVenId.DevId,
                         Dev->RbIo->SegmentNumber, Dev->Address.Addr.Bus, Dev->Address.Addr.Device, Dev->Address.Addr.Function);
                    UnicodeSPrint (String1, sizeof (String1), L"%s\n%s", TempString2, String2);
                     StringId = HiiSetString (gRomHiiHandle, 0, String1, NULL );
                }
                if (TempString1 != NULL) FreePool (TempString1);
                if (TempString2 != NULL) FreePool (TempString2);
            } else {
                TempString1 = HiiGetString (gRomHiiHandle, STRING_TOKEN (STR_ROM_ITEM_HELP_SLOT_HAVE), NULL);
                if (TempString1 != NULL) {
                    UnicodeSPrint (String1, sizeof (String1), TempString1, UefiOprom, LegacyOprom,
                        Dev->DevVenId.VenId, Dev->DevVenId.DevId,
                        Dev->RbIo->SegmentNumber, Dev->Address.Addr.Bus, Dev->Address.Addr.Device, Dev->Address.Addr.Function);
                    StringId = HiiSetString (gRomHiiHandle, 0, String1, NULL);

                    FreePool (TempString1);
                }
            }
        }
        else StringId = STRING_TOKEN (STR_ROM_ITEM_HELP_SLOT_DONT);
    }

    return StringId;
}

/**
    This is a routine, based on "Dev" Class Code will return corresponded 
    to this Class code string.

    @param[in]  Dev Pointer to the private PCI Device Data
    
    @return     EFI_STRING_ID  Pointer to UNICODE String
    
**/ 

EFI_STRING_ID 
GetClassStrId(
        PCI_DEV_INFO *Dev
)
{
    static EFI_STRING_ID    pciclasslist[]={
            STRING_TOKEN(STR_PCI_CLAS_00_STR),
            STRING_TOKEN(STR_PCI_CLAS_01_STR),
            STRING_TOKEN(STR_PCI_CLAS_02_STR),
            STRING_TOKEN(STR_PCI_CLAS_03_STR),
            STRING_TOKEN(STR_PCI_CLAS_04_STR),
            STRING_TOKEN(STR_PCI_CLAS_05_STR),
            STRING_TOKEN(STR_PCI_CLAS_06_STR),
            STRING_TOKEN(STR_PCI_CLAS_07_STR),
            STRING_TOKEN(STR_PCI_CLAS_08_STR),
            STRING_TOKEN(STR_PCI_CLAS_09_STR),
            STRING_TOKEN(STR_PCI_CLAS_0A_STR),
            STRING_TOKEN(STR_PCI_CLAS_0B_STR),
            STRING_TOKEN(STR_PCI_CLAS_0C_STR),
            STRING_TOKEN(STR_PCI_CLAS_0D_STR),
            STRING_TOKEN(STR_PCI_CLAS_0E_STR),
            STRING_TOKEN(STR_PCI_CLAS_0F_STR),
            STRING_TOKEN(STR_PCI_CLAS_10_STR),
            STRING_TOKEN(STR_PCI_CLAS_11_STR)
    };
    UINTN   idx;
    EFI_STRING_ID   strid;
//------------------
    if(Dev==NULL){
        strid=STR_NOT_PRESENT_STR;
    } else {
        idx=Dev->Class.BaseClassCode;
        strid = (idx <= 0x11) ? pciclasslist[idx] : STRING_TOKEN(STR_PCI_CLAS_UNKNOWN_STR);
    }

    return strid;
}

/**
  This function generates Device Option ROM item title string and Help string.
  
 @param[in,out]  RomItemData   In input, Private Data structure. 
                               On output function fills ROM_POLICY_CB_DATA fields

 @return         Status of operation
**/

EFI_STATUS 
UpdateItemStrings (
  ROM_POLICY_CB_DATA  *RomItemData
  )
{
    EFI_STRING_ID       StringId;
    EFI_STRING          LocationStr, StatusStr, ClassStr;
    CHAR16              DummyString = 0;
    UINTN               Index;
    CHAR16              String [MAX_BUFFER_LEN];
//--------------------------------
    // Create goto title string
    // "On Board  classxxxx" 
    // "Slot #XX  Empty    " 
    // "Slot #XX  classxxxx"
    ZeroMem (String, sizeof (String));
    if (RomItemData->PciSdlInfo->PciDevFlags.Bits.OnBoard && RomItemData->PciDevInfo == NULL) {
       //"On Board  NOT FOUND" 
       LocationStr = HiiGetString (gRomHiiHandle, STRING_TOKEN (STR_ONBOARD_STR), NULL);
       ClassStr = HiiGetString (gRomHiiHandle, STRING_TOKEN (STR_NOT_PRESENT_STR), NULL);

       if ((LocationStr != NULL) && (ClassStr != NULL)){
           UnicodeSPrint (String, sizeof(String) , L"%s %s", LocationStr, ClassStr);
       }

       if (LocationStr != NULL) FreePool (LocationStr);
       if (ClassStr != NULL) FreePool (ClassStr);
    } else {

        if(RomItemData->PciSdlInfo->PciDevFlags.Bits.OnBoard){
            // "On Board  Device    [classxxxx]" 
            LocationStr = HiiGetString(gRomHiiHandle, STRING_TOKEN (STR_ONBOARD_STR), NULL);
            StringId = GetClassStrId (RomItemData->PciDevInfo);
            ClassStr = HiiGetString (gRomHiiHandle, StringId, NULL);

            if(LocationStr == NULL) LocationStr = &DummyString;
            if(ClassStr == NULL)    ClassStr = &DummyString;

    //      StatusStr = HiiGetString (gRomHiiHandle, STRING_TOKEN (STR_DEVICE_STR), NULL);
    //      if (StatusStr == NULL)   StatusStr = &DummyString;
    //      UnicodeSPrint (String, sizeof (String), L"%s  %s [%s]", LocationStr, StatusStr, ClassStr);

            UnicodeSPrint (String, sizeof (String) , L"%s %s", LocationStr, ClassStr);

            if ((LocationStr != NULL) && (LocationStr != (&DummyString))) {
                FreePool (LocationStr);
            }

            if ((ClassStr != NULL) && (ClassStr != (&DummyString))) {
                FreePool (ClassStr);
            }

        } else {
            LocationStr = HiiGetString (gRomHiiHandle, STRING_TOKEN (STR_SLOT_STR), NULL);
            if (LocationStr == NULL) LocationStr = &DummyString;

            if (RomItemData->PciDevInfo == NULL) {
                // "Slot #XX Empty" 
                StatusStr = HiiGetString (gRomHiiHandle, STRING_TOKEN (STR_EMPTY_STR), NULL);

                if (StatusStr == NULL) StatusStr = &DummyString;

      //        ClassStr = HiiGetString (gRomHiiHandle, STRING_TOKEN (STR_NOT_PRESENT_STR), NULL);
      //        if (ClassStr == NULL) ClassStr = &DummyString;

      //        UnicodeSPrint (String, sizeof (String), L"%s #%2d %s [FROM BRG (%s)]", 
      //        locationstr, PciDevGotoData->PciSdlInfo->Slot, statusstr, classstr);

                UnicodeSPrint (String, sizeof (String), L"%s #%2d %s", LocationStr, RomItemData->PciSdlInfo->Slot, StatusStr);

                if((StatusStr != (&DummyString)) && (StatusStr !=NULL)) {
                    FreePool (StatusStr);
                }

            } else {
                // "Slot #XX  Populated [classxxxx]"
                StringId = GetClassStrId (RomItemData->PciDevInfo);
                ClassStr = HiiGetString (gRomHiiHandle,STRING_TOKEN (StringId), NULL);
                if(ClassStr == NULL) ClassStr = &DummyString;

      //        StatusStr = HiiGetString (gRomHiiHandle, STRING_TOKEN (STR_POPULATED_STR), NULL);
      //        if (StatusStr == NULL) StatusStr = &DummyString;
      //        UnicodeSPrint (String, sizeof (String), L"%s #%2d %s [%s]", LocationStr, RomItemData->PciSdlInfo->Slot, StatusStr, ClassStr);

                UnicodeSPrint (String, sizeof(String), L"%s #%2d %s", LocationStr, RomItemData->PciSdlInfo->Slot, ClassStr);

                if ((ClassStr != (&DummyString)) && (ClassStr !=NULL)) {
                    FreePool (ClassStr);
                } 
            }
            if((LocationStr != (&DummyString)) && (LocationStr !=NULL)) {
                FreePool (LocationStr);
            }
        }
    }

    RomItemData->CbPromptStringId = HiiSetString (gRomHiiHandle, 0, String, NULL ); 
    gRomIndex--;
    // Setting Mapping Id
    UnicodeSPrint (String, sizeof (String), L"OROM%03d", gRomIndex);
    HiiSetString (gRomHiiHandle, RomItemData->CbPromptStringId, String, "x-UEFI-AMI");

    if (RomItemData->PciDevInfo == NULL) RomItemData->CbHelpStringId = STRING_TOKEN (STR_ROM_OPTION_HELP);
    else RomItemData->CbHelpStringId = GetHelpStrId (RomItemData->PciDevInfo);

    //Will show all Onboard devices...
    //RomItemData->ShowItem initialized with FALSE th this point
    if (RomItemData->PciSdlInfo->PciDevFlags.Bits.OnBoard) {
        //Unless customer wants to hide it.
        if (RomItemData->PciDevInfo == NULL) {
            if (!ROM_SETUP_HIDE_NOTFOUND_ONBOARD) RomItemData->ShowItem = TRUE; 
        } else {
            if (RomItemData->PciDevInfo->AmiRomPolicy != NULL) {
                if ((RomItemData->PciDevInfo->AmiRomPolicy->RomStatus & (AMI_OPTION_ROM_POLICY_UEFI|AMI_OPTION_ROM_POLICY_LEGACY)) ||
                  ((RomItemData->PciDevInfo->AmiRomPolicy->RomStatus == 0) && (RomItemData->PciDevInfo->AmiRomPolicy->CurrentPolicy == 0))) {
                        RomItemData->ShowItem = TRUE;
                } 
            }
        } 
    } else {
        //and slots in the ROM_SETUP_SLOTS_TO_SHOW list...
        for (Index = 0; Index < gNumberOfSlotsToShow; Index++) {
            if (gSlotsToShow[Index] == RomItemData->PciSdlInfo->Slot) {
                RomItemData->ShowItem = TRUE;

#if (ROM_SETUP_SHOW_EMPTY_SLOTS_TO_CONFIG == 0)
                if (RomItemData->PciDevInfo == NULL) {
                    DEBUG ((DEBUG_VERBOSE,"RomItemData->PciDevInfo=NULL.\n"));
                    RomItemData->ShowItem = FALSE;
                }
#endif
                break;
            }
        }
    }

    if (RomItemData->PciSdlInfo->ParentIndex == ROM_SETUP_HIDE_ITEM_PARENT_IDX) RomItemData->ShowItem = FALSE;

    return EFI_SUCCESS;
}


/**
    Prepares the IFR labels within the Option ROM page for the controls insertion. 

    @param RomIfrInfo Pointer to the private ROM Setup data structure

    @retval EFI_SUCCESS if everything good
    @retval EFI_ERROR value if something wrong happens

    @note  
  This call does not free the memory allocated earlier for SIO_IFR_INFO;
  caller is responsible for freeing any memory before executing this function

**/
EFI_STATUS 
InitRomPolicyData (
    ROM_POLICY_INFO *RomIfrInfo
  )
{
    EFI_STATUS                  Status;
    UINTN                       PciDevHandleCount, Index1, Index2;
    EFI_HANDLE                  *PciDevHandles = NULL;
    EFI_PCI_IO_PROTOCOL         *PciIo;
    PCI_DEV_INFO                *Dev;

    if (gRomSetupPtr->ExtraRomCount){

        DEBUG ((DEBUG_INFO,"OptRomSetup: SetupPtr.ExtraRomCount(0x%X)!= 0 processing;\n", gRomSetupPtr->ExtraRomCount));
        Status = InitRomDataFromVar (TRUE);
        ASSERT_EFI_ERROR (Status);
        if (EFI_ERROR(Status)) return Status;
        SortData ();
        //START: Coverity Issue : UNUSED_VALUE
        SetRomPolicyDefaults (TRUE);
        //END: Coverity Issue : UNUSED_VALUE
    }

    // Create new OpCode Handle
    RomIfrInfo->StartOpCodeHandle = HiiAllocateOpCodeHandle ();
    RomIfrInfo->EndOpCodeHandle = HiiAllocateOpCodeHandle ();

    // Create Hii Extend Label OpCode as the start opcode
    RomIfrInfo->StartLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (
            RomIfrInfo->StartOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));
    RomIfrInfo->StartLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;

    RomIfrInfo->EndLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (
            RomIfrInfo->EndOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));
    RomIfrInfo->EndLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;

    RomIfrInfo->StartLabel->Number = ROM_LIST_LABEL_START;
    RomIfrInfo->EndLabel->Number = ROM_LIST_LABEL_END;

    // Update PCI Dev information
    Status = gBS->LocateHandleBuffer (ByProtocol,
        &gEfiPciIoProtocolGuid, NULL, &PciDevHandleCount, &PciDevHandles);

    ASSERT_EFI_ERROR (Status);

    if (EFI_ERROR(Status)) return Status;

    //Now check devices with Handles if they are Enabled and Active
    for (Index1 = 0; Index1 < RomIfrInfo->RomItemsCount; Index1++){
        AMI_SDL_PCI_DEV_INFO    *SdlPciDev;
        //----------------------------------
        SdlPciDev = (RomIfrInfo->RomPolicyCbData [Index1])->PciSdlInfo;
        //Found Matching SDL Objects...
        for (Index2 = 0; Index2 < PciDevHandleCount; Index2++) {
            Status = gBS->HandleProtocol (PciDevHandles [Index2], &gEfiPciIoProtocolGuid, (VOID**)&PciIo); 
            ASSERT_EFI_ERROR(Status);

            Dev = (PCI_DEV_INFO*)PciIo;
            //Check if we running with AMI driver and can type cast data like that
            if (Dev->Signature != AMI_PCI_SIG) return EFI_NOT_FOUND;

            //Here check if current PciIo instance belongs to the Func0 of the device on the slot...
            //On board devices could have setup for different functions though...
            if (!SdlPciDev->PciDevFlags.Bits.OnBoard && !IsFunc0 (Dev)) continue;

            if (Dev->SdlDevCount == 0) continue;
            if (Dev->SdlDevCount == 1) {
                if (SdlPciDev == Dev->AmiSdlPciDevData) {
                    (RomIfrInfo->RomPolicyCbData [Index1])->PciDevInfo = Dev;
                }
            } else {//Here dev->SdlDevCount>1
                //here if we have more than 1 SDL object matching Device
                UINTN                   Index3;
                UINTN                   RecordIndex;
                AMI_SDL_PCI_DEV_INFO    *TempSdlPciDev;

                for (Index3 = 0; Index3 < Dev->SdlDevCount; Index3++) {
                    RecordIndex = Dev->SdlIdxArray [Index3];
                    Status = AmiSdlFindIndexRecord (RecordIndex, &TempSdlPciDev);
                    if (SdlPciDev == TempSdlPciDev){
                        (RomIfrInfo->RomPolicyCbData [Index1])->PciDevInfo = Dev;
                        break;
                    }
                }
            }

            if (SdlPciDev->ParentIndex == Dev->SdlDevIndex) {
                (RomIfrInfo->RomPolicyCbData [Index1])->ParentBrgInfo = Dev;
            }
        }

        UpdateItemStrings (RomIfrInfo->RomPolicyCbData [Index1]);

    }

    if (PciDevHandles!=NULL) FreePool (PciDevHandles);

    return Status;
}


/**
    This will sort setup device items in Following order:
    First go slots in Ascending order followed by on board devices...

    @param  VOID

    @retval VOID

**/
VOID 
SortData(
        VOID
)
{
    T_ITEM_LIST slt={0,0,NULL};
    T_ITEM_LIST obd={0,0,NULL};
    EFI_STATUS  Status;
    UINTN   i;
    ROM_POLICY_CB_DATA      *cb;
    AMI_SDL_PCI_DEV_INFO    *sd;
    ROM_POLICY_CB_DATA      *tmpcb;
    AMI_SDL_PCI_DEV_INFO    *tmpsd;
    BOOLEAN                 ap;
//------------------------------------
    while(gOptRomData.RomItemsCount){
        cb=gOptRomData.RomPolicyCbData[0];
        sd=cb->PciSdlInfo;

        //Remove item from unsorted array;
        DeleteItemLst((T_ITEM_LIST*)&gOptRomData.InitCount, 0, FALSE);

        if(sd->PciDevFlags.Bits.OnBoard){
            //Add OnBoard device to the separate list, 
            Status = AppendItemLst(&obd, cb);
        } else {

            for(i=0, ap=TRUE; i<slt.ItemCount; i++){
                tmpcb=(ROM_POLICY_CB_DATA*)slt.Items[i];
                tmpsd=tmpcb->PciSdlInfo;
                if(tmpsd->Slot > sd->Slot){
                    Status=InsertItemLst(&slt, cb, i);
                    ap=FALSE;
                    break;
                }
            }//for
            // if Append Flag is set Slot # is the biggest one yet.
            if(ap) Status = AppendItemLst(&slt, cb);
        }
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status)) return;
    } //keep going until unsorted list empty.
    
    //now fill same list we just emptied IfrData->PciDevSetupData[] with sorted data.
    //With Sorted Slot Data....
#if (ROM_SETUP_SHOW_SLOTS_FIRST == 1)
    for(i=0;i<slt.ItemCount; i++) {
        Status=AppendItemLst((T_ITEM_LIST*)&gOptRomData.InitCount, slt.Items[i]);
        ASSERT_EFI_ERROR(Status);
    }
#endif
    //with On Board Devices Data...
    for(i=0;i<obd.ItemCount; i++) {
        Status=AppendItemLst((T_ITEM_LIST*)&gOptRomData.InitCount, obd.Items[i]);
        ASSERT_EFI_ERROR(Status);
    }
    
#if (ROM_SETUP_SHOW_SLOTS_FIRST == 0)   
    for(i=0;i<slt.ItemCount; i++) {
        Status=AppendItemLst((T_ITEM_LIST*)&gOptRomData.InitCount, slt.Items[i]);
        ASSERT_EFI_ERROR(Status);
    }
#endif  
    ClearItemLst(&obd,FALSE);
    ClearItemLst(&slt,FALSE);
}


/**
    This function Updates Driver version string with actual number.
    
    @param VOID

    @retval VOID

**/

VOID 
InitDriverVersionString (
  VOID
  )
{
    CHAR16      String [80];
    CHAR16      DummyString = 0;
    EFI_STRING  DriverVersion;

    DriverVersion = HiiGetString (gRomHiiHandle, STRING_TOKEN (STR_ROM_PCI_DRIVER_VER_PROMPT), NULL);
    if (DriverVersion == NULL) {
        DriverVersion = &DummyString;
    }
    UnicodeSPrint (String, sizeof (String), L"%s%02X.%02d.%02d", DriverVersion, PCI_BUS_MAJOR_VER, PCI_BUS_MINOR_VER, PCI_BUS_REVISION);
    HiiSetString (gRomHiiHandle, STRING_TOKEN (STR_ROM_PCI_DRIVER_VER), String, NULL);
    if((DriverVersion != (&DummyString)) && (DriverVersion != NULL)) {
        FreePool (DriverVersion);
    }
}

/**
    This function is called by Setup browser to perform Setup Form update

    @param This pointer to the instance of 
        ConfigAccess protocol
    @param Action action, that setup browser is performing
    @param KeyValue value of currently processed setup control
    @param Type value type of setup control data
    @param Value pointer to setup control data
    @param ActionRequest pointer where to store requested action

    @retval EFI_SUCCESS flash updated successfully
    @retval EFI_UNSUPPORTED browser action is not supported
 
**/
EFI_STATUS 
EFIAPI 
RomBrowserCallback(
    IN  CONST   EFI_HII_CONFIG_ACCESS_PROTOCOL  *This,
    IN  EFI_BROWSER_ACTION                      Action,
    IN  EFI_QUESTION_ID                         KeyValue,
    IN  UINT8                                   Type,
    IN  EFI_IFR_TYPE_VALUE                      *Value,
    OUT EFI_BROWSER_ACTION_REQUEST              *ActionRequest
)
{
    DEBUG((DEBUG_VERBOSE,"RomSetup: BrowserCallback(Action %x, KeyValue %x, Type %x).\n", Action, KeyValue, Type));

    if (ActionRequest) 
        *ActionRequest = EFI_BROWSER_ACTION_REQUEST_NONE;

    if( (Action == EFI_BROWSER_ACTION_DEFAULT_STANDARD ||
        Action == EFI_BROWSER_ACTION_DEFAULT_MANUFACTURING || 
        Action == EFI_BROWSER_ACTION_DEFAULT_SAFE)){
        if((KeyValue & ROM_GOTO_ID_BASE)!= 0) {
            UINTN               i=(KeyValue & (~ROM_GOTO_ID_BASE));
            ROM_POLICY_CB_DATA  *cb=gOptRomData.RomPolicyCbData[i];

            gRomSetupPtr->PolicyOption[i].Option=AMI_OPTION_ROM_POLICY_UEFI;
            gRomSetupPtr->PolicyOption[i].SdlIdx=(UINT32)cb->SdlIdx;

            if (cb->PciSdlInfo->PciDevFlags.Bits.OnBoard) {
                 // Clear Slot attributes as 0 and Program Asl Name for Onboard devices
                 gRomSetupPtr->PolicyOption[i].SlotNum = 0;
                 gRomSetupPtr->PolicyOption[i].IsSlot = FALSE;
                 MemCpy(&(gRomSetupPtr->PolicyOption[i].AslName), &(cb->PciSdlInfo->AslName), sizeof(cb->PciSdlInfo->AslName));
             } else {
                 //Fill Slot Number
                 gRomSetupPtr->PolicyOption[i].SlotNum =(UINT32)cb->PciSdlInfo->Slot;
                 gRomSetupPtr->PolicyOption[i].IsSlot = TRUE;
             }

            cb->PolicyVarPtr = &gRomSetupPtr->PolicyOption[i];
            Value->u8 = AMI_OPTION_ROM_POLICY_UEFI;
            return EFI_SUCCESS;
        } else {
            return EFI_UNSUPPORTED;
        }

    }

    if(Action == EFI_BROWSER_ACTION_CHANGING){
/*        if((KeyValue & ROM_GOTO_ID_BASE)!= 0) {
            if(gLoadDefaults){
                UINTN               i=(KeyValue & (~ROM_GOTO_ID_BASE));
                ROM_POLICY_CB_DATA  *cb=gOptRomData.RomPolicyCbData[i];     
            //-------------------
                //if(cb->PolicyVarPtr->Option!=Value->u8)cb->PolicyVarPtr->Option=Value->u8;
                Value->u8=AMI_OPTION_ROM_POLICY_UEFI;
                gLoadDefaults=FALSE;
            }
        }
*/
        return EFI_SUCCESS;
    }

    return EFI_UNSUPPORTED;
}

/**

  The function will get CSM group policy information
  and then fill globally defined data structure gCsmSetup
  if parameter passed == true it will create a memory var.
  
 @param[in]     Get            If TRUE it will read data
                               If FALSE it will update NVRAM var.

 @return        Status of operation
**/
EFI_STATUS 
GetSetRomData (
    BOOLEAN     Get
  )
{
    UINTN       Size = sizeof(ROM_SETUP_DATA);
    EFI_STATUS  Status = EFI_SUCCESS;

    if (Get) {
        Status = gRT->GetVariable (
                        L"ROM_CMN",
                        &RomSetupGuid,
                        &gRomCmnAttributes,
                        &Size,
                        gRomSetupPtr
                        );
        if (Status == EFI_NOT_FOUND) {
            DEBUG ((DEBUG_ERROR, " GetSetRomData : Get gRomSetupPtr variable Status - %r\n", Status));
            gRomCmnAttributes = (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS);
        }
        // Nvram incompatibility check
        if ( !EFI_ERROR (Status) && (Size != sizeof(ROM_SETUP_DATA)) ) {
            DEBUG ((DEBUG_ERROR, " GetSetRomData : NV Structure Incompatible \n"));
            DEBUG ((DEBUG_ERROR, " GetSetRomData : Comparison sz %x, sizeof(ROM_SETUP_DATA) %x \n", Size, sizeof (ROM_SETUP_DATA)));
            Status = EFI_BAD_BUFFER_SIZE;
        }
    } else {
        Status = gRT->SetVariable (
                        L"ROM_CMN",
                        &RomSetupGuid,
                        gRomCmnAttributes, 
                        sizeof(ROM_SETUP_DATA),
                        gRomSetupPtr
                        );
    }

    return Status;
}

/**

  The function will get CSM group policy information
  and then fill globally defined data structure gCsmSetup
  if parameter passed == true it will create a memory var.
  
 @param[in]     Get            If TRUE it will read data
                               If FALSE it will update NVRAM var.

 @return        Status of operation
**/
EFI_STATUS 
GetSetCsmData (
    UINT8       Get
  )
{
    UINTN       Size = sizeof (CSM_SETUP_DATA);
    EFI_STATUS  Status = EFI_SUCCESS;

    if (Get) {

        Status = gRT->GetVariable (L"CSM_CMN", &RomSetupGuid, &gCsmCmnAttributes, &Size, &gCsmSetup);

        if (EFI_ERROR(Status)) {
            gCsmSetup.CsmDisplay    = gSetupData.VideoOpRom;
            gCsmSetup.CsmMassSt     = gSetupData.MassStorageOpRom;
            gCsmSetup.CsmNetwork    = gSetupData.PxeOpRom;
            gCsmSetup.CsmOther      = gSetupData.OldOpRom;
            gCsmSetup.CsmPresent    = gCsmSupported;
            gCsmCmnAttributes       = (EFI_VARIABLE_BOOTSERVICE_ACCESS);
            Get = FALSE;
        }
    }

    if (!Get) {
        Status = gRT->SetVariable (L"CSM_CMN", &RomSetupGuid, gCsmCmnAttributes, Size, &gCsmSetup);
    }

    return Status;
}


/**
    This function returns OpROM policy for given PCI class of the device

    @param 
        UINT8 PciClass - class of PCI device to check


    @retval UINT8 policy (0-disable all, 1-disable Legacy, 2-disable UEFI)

**/
UINT8 
GetOpRomPolicy(
    IN UINT8 PciClass
)
{
    EFI_STATUS Status;
    UINT8 Policy = 0xff;

    Status = GetSetCsmData(TRUE);
    ASSERT_EFI_ERROR(Status);

    switch(PciClass) {
        case PCI_CL_NETWORK:
            Policy = gCsmSetup.CsmNetwork;
            break;

        case PCI_CL_MASS_STOR:
            Policy = gCsmSetup.CsmMassSt;
            break;

        case PCI_CL_DISPLAY:
            Policy = gCsmSetup.CsmDisplay;
            break;

        default:
/*
    For PCI devices with PCI class different from Network, Mass Storage or Video
    behavior will be as in previous versions of PciBus driver - UEFI OpROM will
    be executed first or not executed at all
*/
            Policy = gCsmSetup.CsmOther;
            break;
    }
    return Policy;
}


/**
  This function creates and initializes device Option 
  ROM Item private data structure.
  
 @param[in]     RomIfrInfo    Private data of Setup Item to be created

 @retval        VOID
**/

VOID 
CreateRomCbItems(
        ROM_POLICY_INFO *RomIfrInfo
)
{
    UINTN           i;
//    EFI_STATUS        Status;
    EFI_QUESTION_ID cbid;

    for (i=0; i<RomIfrInfo->RomItemsCount; i++) {
        ROM_POLICY_CB_DATA *cb;

        cb=RomIfrInfo->RomPolicyCbData[i];
        if(cb->ShowItem==FALSE) continue;
        //Generate ID based on 0x6000 + AMI SDL Index i structure 
        cbid=ROM_GOTO_ID_BASE+(UINT16)i;

        //Will create a one of items with 3 options [ Disable | Uefi | Legacy ] 
        if(DeviceClassPolicyOverride){
            VOID *OpcodeHandle=HiiAllocateOpCodeHandle();

            //First create one of options...
            //1. 'Disable' Option... ==0
            HiiCreateOneOfOptionOpCode (
                    OpcodeHandle,
                    STRING_TOKEN(STR_DISABLE_STR),
                    0,
                    EFI_IFR_NUMERIC_SIZE_1,
                    AMI_OPTION_ROM_POLICY_DISABLE );
            //2. 'UEFI' option == 1 (Default)
            HiiCreateOneOfOptionOpCode (
                    OpcodeHandle,
                    STRING_TOKEN(STR_UEFI_STR),
                    (EFI_IFR_OPTION_DEFAULT | EFI_IFR_OPTION_DEFAULT_MFG),
                    EFI_IFR_NUMERIC_SIZE_1,
                    AMI_OPTION_ROM_POLICY_UEFI );

            if(gCsmSetup.CsmPresent){
                //3 'Legacy' option = 2 only if CSM is Enabled...
                HiiCreateOneOfOptionOpCode (
                        OpcodeHandle,
                        STRING_TOKEN(STR_LEGACY_STR),
                        0,
                        EFI_IFR_NUMERIC_SIZE_1,
                        AMI_OPTION_ROM_POLICY_LEGACY );
            }

            //4. 'Disable All' option = 4. Disable Oprom as well Drivers
            HiiCreateOneOfOptionOpCode (
                    OpcodeHandle,
                    STRING_TOKEN(STR_DISABLE_ALL_STR),
                    0,
                    EFI_IFR_NUMERIC_SIZE_1,
                    AMI_OPTION_ROM_POLICY_DISABLE_ALL );

            //Now create OneOf OpCode...
            HiiCreateOneOfOpCode (
                    RomIfrInfo->StartOpCodeHandle,      //*OpCodeHandle
                    cbid,                               //QuestionId
                    0xFFF0,     //Varstore Id of ROM_SETUP_DATA "ROM_CMN"
                    (UINT16)(EFI_FIELD_OFFSET(ROM_SETUP_DATA, PolicyOption[i])),//+(sizeof(ROM_POLICY_VAR)*i)),//Offset
                    cb->CbPromptStringId,               //Prompt
                    cb->CbHelpStringId,                 //Help 
                    EFI_IFR_FLAG_RESET_REQUIRED|EFI_IFR_FLAG_CALLBACK,        //QuestionFlags
                    EFI_IFR_NUMERIC_SIZE_1,             //OneOfFlags
                    OpcodeHandle,                       //OptionsOpCodeHandle
                    NULL//defopt                        //*DefaultsOpCodeHandle  OPTIONAL
            );

        } else {
            //Device/Slot ROM Dispatch Check Box...
            HiiCreateCheckBoxOpCode (
            RomIfrInfo->StartOpCodeHandle,
            cbid,
            0xFFF0, //Varstore Id of ROM_SETUP_DATA "ROM_CMN"
            (UINT16)(EFI_FIELD_OFFSET(ROM_SETUP_DATA, PolicyOption[i])),//+(sizeof(ROM_POLICY_VAR)*i)),
            cb->CbPromptStringId,
            cb->CbHelpStringId,
            EFI_IFR_FLAG_RESET_REQUIRED|EFI_IFR_FLAG_CALLBACK,
            1, // "Enable" - the default settings.
            NULL
            );

        }

    }

    HiiUpdateForm (
      gRomHiiHandle,
      &RomFormsetGuid,
      ROM_MAIN_FORM_ID,
      RomIfrInfo->StartOpCodeHandle,
      RomIfrInfo->EndOpCodeHandle
    );
}

/**
    This is Setup Init Event Handler. It is called in call back
    when entering to Setup as well as on ReadytoBoot to Sync data. 

    @param Event Event Handle
    @param Context Pointer to the optional Data buffer
    
    @retval VOID
**/ 
VOID 
InitRomIfr (
    IN EFI_EVENT              Event,
    IN VOID                   *Context
  )
{
    EFI_STATUS                Status;
    EFI_LEGACY_BIOS_PROTOCOL  *LegacyBios;
    BOOLEAN                   RomFb = FALSE;
//------------------------------------
    DEBUG ((DEBUG_INFO, "RomSetup: InitRomIfr"));
    if (!gInitRomIfrEntered) {
        gInitRomIfrEntered = TRUE;
        DEBUG ((DEBUG_INFO, "(Event 0x%X, Context @0x%X) = ", Event, Context));

        Status = GetSetCsmData (FALSE);

        if (EFI_ERROR (Status)) return;

        Status = gBS->LocateProtocol (&gEfiLegacyBiosProtocolGuid, NULL, (VOID **) &LegacyBios);
        if (EFI_ERROR (Status)) gCsmSetup.CsmPresent = 0;
        else gCsmSetup.CsmPresent = 1;

        Status = GetSetRomData (TRUE);

        if (EFI_ERROR(Status)) return;

        Status = InitRomPolicyData (&gOptRomData);

        DEBUG ((DEBUG_INFO, "%r.\n", Status));

        if (EFI_ERROR (Status)) return;

        CreateRomCbItems (&gOptRomData);

        //Reset Failure to boot var. In case Ready to boot event will not be generated 
        //due to setup Save and reset action...
        Status = gRT->SetVariable (L"ROM_FB", &RomSetupGuid, gRomFbAttributes, sizeof (RomFb), &RomFb);
        ASSERT_EFI_ERROR (Status);
    }
    DEBUG ((DEBUG_INFO, "\n"));
}

/**
    Checks and enforces Video option ROM policy exception. 

    @param  Size Size of Option ROM NVRAM var

    @retval EFI_SUCCESS if everything good
    @retval EFI_ERROR value if something wrong happens

**/

EFI_STATUS 
CheckRomPolicyVgaStatus (
    BOOLEAN                       CallbackMode
  )
{
    UINTN                         Index;
    EFI_STATUS                    Status = EFI_SUCCESS;
    EFI_GRAPHICS_OUTPUT_PROTOCOL  *Gop;
    EFI_EVENT                     GopRrotocolEvent;
//--------------------------------------
    //Now check if policy has disabled Video Opt ROM dispatch 
    if (gRomSetupPtr->SupressVga) {
        UINT8       UpdateVar = 0;
    //-----------------    
        DEBUG ((DEBUG_INFO,"OptRomSetup: ChkVga - VGA Settings: VgaIdx=0x%X; Item=%d; Group=%d; cbMode=%d; GopFound=%d;\n", 
                gRomSetupPtr->PriVgaIdx,gRomSetupPtr->PriVgaItemValue,gRomSetupPtr->PriVgaGroupValue,CallbackMode, gGopFound));

        //In case if original UEFI Gop driver does not set legacy VGA attributes...
        //SDL Index of a VGA Device can't be == 0 this is true only for HostBridgeType Device
        //if it ==0 means it has not been initialized.
        if (!CallbackMode) {
            //if (gRomSetupPtr->PriVgaIdx == 0) {
            Status = gBS->LocateProtocol (
                            &gEfiGraphicsOutputProtocolGuid, 
                            NULL, 
                            (VOID **)&Gop
                            );
            if (EFI_ERROR(Status)) {
                Status = RegisterProtocolCallback (
                           &gEfiGraphicsOutputProtocolGuid, 
                           GopProtocolCallback,
                           NULL,
                           &GopRrotocolEvent,
                           &gGopProtocolRegistration
                           );
                ASSERT_EFI_ERROR (Status);
            } else {
                GopProtocolCallback (NULL, NULL);
            }
        }

        //Check if Video Group Policy was disabled... 
        //Check if we need to restore CSM Group Policy on VGA
        if (gSetupData.VideoOpRom == AMI_OPTION_ROM_POLICY_DISABLE) {
            //if(gCsmSetup.CsmPresent) gSetupData.VideoOpRom=AMI_OPTION_ROM_POLICY_LEGACY;
            //else gSetupData.VideoOpRom=AMI_OPTION_ROM_POLICY_UEFI;
            DEBUG ((DEBUG_INFO,"OptRomSetup: ChkVga - Restoring GropMode: from (%d) ",gSetupData.VideoOpRom));
            gSetupData.VideoOpRom = gRomSetupPtr->PriVgaGroupValue;
            UpdateVar |= 1;
            //if still it appears to be disabled...restore defaults...
            if (gSetupData.VideoOpRom == AMI_OPTION_ROM_POLICY_DISABLE) {
                if (gCsmSupported) gSetupData.VideoOpRom = AMI_OPTION_ROM_POLICY_LEGACY;
                else gSetupData.VideoOpRom = AMI_OPTION_ROM_POLICY_UEFI;
            }
            DEBUG ((DEBUG_INFO,"... to (%d).\n",gSetupData.VideoOpRom));
        }
        //Update Group Policy Value
        gRomSetupPtr->PriVgaGroupValue = gSetupData.VideoOpRom;

        //now item policy check
        for (Index = 0; Index < (UINTN)(gRomSetupPtr->OptRomCount+gRomSetupPtr->ExtraRomCount); Index++) {
            ROM_POLICY_VAR  *RomPolicyVar = &gRomSetupPtr->PolicyOption [Index];
        //----------------------
            if (gRomSetupPtr->PriVgaIdx == RomPolicyVar->SdlIdx) {
                if (RomPolicyVar->Option == AMI_OPTION_ROM_POLICY_DISABLE) {
                    DEBUG ((DEBUG_INFO,"OptRomSetup: ChkVga - Restoring ItemMode: from (%d) ", RomPolicyVar->Option));
                    RomPolicyVar->Option = gRomSetupPtr->PriVgaItemValue;
                    UpdateVar |= 2;
                    //if it still disabled restore defaults...
                    if (RomPolicyVar->Option == AMI_OPTION_ROM_POLICY_DISABLE) {
                        if (gCsmSupported) RomPolicyVar->Option = AMI_OPTION_ROM_POLICY_LEGACY;
                        else RomPolicyVar->Option = AMI_OPTION_ROM_POLICY_UEFI;
                        gRomSetupPtr->PriVgaItemValue = RomPolicyVar->Option;
                    }
                    DEBUG ((DEBUG_INFO,"... to (%d).\n", RomPolicyVar->Option));
                }
                //Update Item Value...
                gRomSetupPtr->PriVgaItemValue = RomPolicyVar->Option;
                break;
            }
        }

        //If we have initial ROM_CMN var or VGA device changed we need to update IDX.
        if ((gEntryVgaIdx != gRomSetupPtr->PriVgaIdx) ||
           (gEntryGrop != gRomSetupPtr->PriVgaGroupValue) ||
           (gEntryItem != gRomSetupPtr->PriVgaItemValue) ) {
            UpdateVar |= 2;
        }

        if (UpdateVar) {
            if (UpdateVar&1) {
                Status = gRT->SetVariable (
                                L"Setup",
                                &AmiSetupGuid,
                                gSetupAttributes, 
                                sizeof (SETUP_DATA),
                                &gSetupData
                                );

                DEBUG ((DEBUG_INFO,"OptRomSetup: ChkVga - Updating 'Setup' var Status=%r.\n",Status));
                if (EFI_ERROR(Status)) return Status;
            }

            if (UpdateVar&2) {
                Status=gRT->SetVariable (
                              L"ROM_CMN",
                              &RomSetupGuid,
                              gRomCmnAttributes, 
                              sizeof (ROM_SETUP_DATA),
                              gRomSetupPtr
                              );
                DEBUG ((DEBUG_INFO,"OptRomSetup: ChkVga - Updating 'ROM_CMN' var Status=%r.\n",Status));
                if (EFI_ERROR(Status)) return Status;
            }
        }

        //Need to restart system since GOP gets installed after PCI io and ROM Dispatch.
        //if (UpdateVar && CallbackMode) {
        //    DEBUG ((DEBUG_ERROR,"OptRomSetup: System RESET (VGA Restore); VGA Settings: VgaIdx=%X; Item=%d; Group=%d;\n", 
        //            gRomSetupPtr->PriVgaIdx,gRomSetupPtr->PriVgaItemValue,gRomSetupPtr->PriVgaGroupValue));
        //    gRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
        //}
    }

    return Status;
}


/**
    Checks if Onboard Asl Name array elements is ported with NON zero values

    @param  UINT8 *Name

    @retval TRUE if non zero values exists
            FALSE if all elements are 0

**/

BOOLEAN 
CheckOBoardAslNameArrayElements(
        UINT8 *AslName
)
{
    UINT8 ElementIndex = 0;
    
    for(ElementIndex = 0; ElementIndex < 4; ElementIndex++) {
        if(AslName[ElementIndex] != 0) return TRUE;
    }

    return FALSE;
}

/**
    Checks and enforces System option ROM policy exception. 
    Restores Option ROM Policy safe defaults if system fails to boot

    @param  BOOLEAN UpdateVar 

    @retval EFI_SUCCESS if everything good
    @retval EFI_ERROR value if something wrong happens

**/

EFI_STATUS 
SetRomPolicyDefaults (
    BOOLEAN  UpdateVar
  )
{
    UINTN    Index;
//-------------
    DEBUG ((DEBUG_INFO,"OptRomSetup: SetRomPolicyDefaults ...\n"));

    gOptRomData.RomSetup->OptRomCount   = (UINT16)gOptRomData.RomItemsCount;
    gOptRomData.RomSetup->ExtraRomCount = 0;
    gOptRomData.RomSetup->SupressVga    = DEFAULT_SUPRESS_VGA_VALUE;
    gOptRomData.RomSetup->ResetPolicy   = DEFAULT_RESET_POLICY_VALUE;

    for(Index = 0; Index < gOptRomData.RomItemsCount; Index++) {
        ROM_POLICY_CB_DATA  *cb;
    //------------------
        cb = gOptRomData.RomPolicyCbData [Index];

        //Set UEFI as default for Options to launch enabled option ROM . Later modify option if Legacy.
        gRomSetupPtr->PolicyOption [Index].Option = AMI_OPTION_ROM_POLICY_UEFI;

        // Check Policy Override and Onboard/Embedded Roms for Legacy
        if ((DeviceClassPolicyOverride) && 
           (cb->PciSdlInfo->PciDevFlags.Bits.OnBoard && cb->PciSdlInfo->PciDevFlags.Bits.EmbededRom) &&
           (cb->PciSdlInfo->PciDevFlags.Bits.StdPciRom)) {
            //Set Default for Onboard Legacy if present
            gRomSetupPtr->PolicyOption [Index].Option = AMI_OPTION_ROM_POLICY_LEGACY;
        }

        gRomSetupPtr->PolicyOption [Index].SdlIdx = (UINT32)cb->SdlIdx;

        if (cb->PciSdlInfo->PciDevFlags.Bits.OnBoard) {
            // Clear Slot attributes as 0 and Program Asl Name for Onboard devices
            gRomSetupPtr->PolicyOption[Index].SlotNum = 0;
            gRomSetupPtr->PolicyOption[Index].IsSlot = FALSE;

            if (!CheckOBoardAslNameArrayElements(&cb->PciSdlInfo->AslName [0])) {
                DEBUG((DEBUG_ERROR,"!!!WARNING!!! - OptRomSetup: OnBoard Device ASL Name is not PORTED\n")); 
            }
            MemCpy (&(gRomSetupPtr->PolicyOption [Index].AslName), &(cb->PciSdlInfo->AslName), sizeof (cb->PciSdlInfo->AslName));
        } else {
            //Fill Slot Number
            gRomSetupPtr->PolicyOption [Index].SlotNum = (UINT32)cb->PciSdlInfo->Slot;
            gRomSetupPtr->PolicyOption [Index].IsSlot = TRUE;
        }

        cb->PolicyVarPtr = &gRomSetupPtr->PolicyOption [Index];
    }

    if (UpdateVar) {
        return gRT->SetVariable (
                      L"ROM_CMN",
                      &RomSetupGuid,
                      gRomCmnAttributes, 
                      sizeof (ROM_SETUP_DATA),
                      gRomSetupPtr
                      );
    }
    return EFI_SUCCESS;
}

/**
    Checks and enforces System option ROM policy exception. 
    Restores Option ROM Policy safe defaults if system fails to boot

    @param  VOID

    @retval VOID

**/
VOID 
RestoreDefaults (
    VOID
  )
{
    BOOLEAN     RomFb = FALSE;
    EFI_STATUS  Status;
//-------------------

    DEBUG ((DEBUG_INFO,"OptRomSetup: RestoreDefaults ...\n"));

    //Restore Defaults of OptRom Module
    Status = SetRomPolicyDefaults (TRUE);
    ASSERT_EFI_ERROR (Status);

#if ((defined CSM_SUPPORT) && (CSM_SUPPORT==1))
    //Restore Defaults of CSM at SETUP_DATA var
    if (DeviceClassPolicyOverride && PolicyOverrideMode == AMI_OPT_ITEM_PRIORITY) gSetupData.VideoOpRom = 1;
    else gSetupData.VideoOpRom = DEFAULT_VIDEO_OPROM_POLICY;
    gSetupData.MassStorageOpRom = DEFAULT_MASS_STORAGE_OPROM_POLICY;
    gSetupData.PxeOpRom = DEFAULT_PXE_OPROM_POLICY;
    gSetupData.OldOpRom = AMI_OPTION_ROM_POLICY_UEFI;
    gSetupData.CsmSupport = DEFAULT_CSM_LAUNCH_POLICY;
#else
    if (DEFAULT_VIDEO_OPROM_POLICY == AMI_OPTION_ROM_POLICY_LEGACY) gSetupData.VideoOpRom = AMI_OPTION_ROM_POLICY_UEFI;
    else gSetupData.VideoOpRom = DEFAULT_VIDEO_OPROM_POLICY;
    if(DEFAULT_MASS_STORAGE_OPROM_POLICY == AMI_OPTION_ROM_POLICY_LEGACY) gSetupData.MassStorageOpRom = AMI_OPTION_ROM_POLICY_UEFI;
    else gSetupData.MassStorageOpRom = DEFAULT_MASS_STORAGE_OPROM_POLICY;
    if (DEFAULT_PXE_OPROM_POLICY == AMI_OPTION_ROM_POLICY_LEGACY) gSetupData.PxeOpRom = AMI_OPTION_ROM_POLICY_UEFI;
    else gSetupData.PxeOpRom = DEFAULT_PXE_OPROM_POLICY;
    gSetupData.OldOpRom = AMI_OPTION_ROM_POLICY_UEFI;
    gSetupData.CsmSupport = 0;
    gCsmSupported = FALSE;
#endif
    //reset Fail to Boot var...
    Status= gRT->SetVariable (L"ROM_FB", &RomSetupGuid, gRomFbAttributes, sizeof (RomFb), &RomFb);
    ASSERT_EFI_ERROR (Status);

    Status = gRT->SetVariable (L"Setup", &AmiSetupGuid, gSetupAttributes, sizeof (SETUP_DATA), &gSetupData);
    ASSERT_EFI_ERROR (Status);
}


/**
    Event handler to clear FAIL to Boot variable if system is booting

    @param[in]  Event       Event Handle
    @param[in]  Context     Pointer on some data buffer

    @retval VOID

**/
VOID 
ClearFailToBootVar (
    IN EFI_EVENT Event, 
    IN VOID      *Context
  )
{
    UINT8        RomFbVar = 0;
    EFI_STATUS   Status;
//--------------------------------    
    DEBUG((DEBUG_ERROR,"OptRomSetup: RdyToBoot VGA Settings(Idx=%X; Itm=%d; Gr=%d; GOP=%d); Setting FbVar=0.\n", 
              gRomSetupPtr->PriVgaIdx, gRomSetupPtr->PriVgaItemValue, gRomSetupPtr->PriVgaGroupValue, gGopFound));
    Status = gRT->SetVariable (L"ROM_FB", &RomSetupGuid ,gRomFbAttributes, sizeof (RomFbVar), &RomFbVar);
    ASSERT_EFI_ERROR (Status);

    if (gRomSetupPtr->SupressVga && !gGopFound) {
        Status = CheckRomPolicyVgaStatus (TRUE);
        ASSERT_EFI_ERROR (Status);
    }

    gBS->CloseEvent (Event);
}

/**
    
    Collects all Pci Onboard  Devices Data from Sdl information
    
    @param  VOID
    
    @retval EFI_STATUS

**/
EFI_STATUS 
CollectPciOnboardDevicesDataFromSdl(
    VOID
)
{
    UINTN                       Index = 0;
    AMI_SDL_PCI_DEV_INFO        *SdlDevInfo;
    EFI_STATUS                  Status = EFI_SUCCESS;
    //------    
    
    //Look in SDL DB for PCI Devices with Onboard Flag Set  
    for(Index = 0; Index < gSdlPciData->PciDevCount; Index++){
        SdlDevInfo = &gSdlPciData->PciDevices[Index];
        
        if((SdlDevInfo->PciDevFlags.Bits.PciDevice) && (SdlDevInfo->PciDevFlags.Bits.OnBoard)){
            if(SdlDevInfo->PciDevFlags.Bits.StdPciRom || SdlDevInfo->PciDevFlags.Bits.UefiDriverBin){
                ROM_POLICY_CB_DATA        *ObDevData;
                ObDevData = MallocZ(sizeof(ROM_POLICY_CB_DATA));
                if(ObDevData == NULL) return EFI_OUT_OF_RESOURCES;
                
                ObDevData->PciSdlInfo = SdlDevInfo;
                ObDevData->SdlIdx = Index;
                DEBUG((DEBUG_INFO,"CollectPciOnboardDevicesDataFromSdl: ObDevData->SdlIdx 0x%X \n", ObDevData->SdlIdx ));
                        
                Status = AppendItemLst((T_ITEM_LIST*)&gOpromPciDevDataList->ObInitCount, ObDevData);
            }
        }
    }

    DEBUG((DEBUG_VERBOSE,"CollectPciOnboardDevicesDataFromSdl: gOpromPciDevDataList->ObDevCount  0x%X \n\n", gOpromPciDevDataList->ObDevCount ));
    
    return Status;
}

/**
    
    Collects all Pci Slot  Devices Data from Sdl information
    
    @param  VOID
    
    @retval EFI_STATUS

**/
EFI_STATUS 
CollectPciSlotDevicesDataFromSdl (
    VOID
  )
{
    UINTN                       Index1, Index2;
    AMI_SDL_PCI_DEV_INFO        *SdlDevInfo;
    EFI_STATUS                  Status = EFI_SUCCESS;
    //------    

    //Look in SDL DB for PCI Devices with Slots Flag Set (Not Onboards are all slots) 
    for (Index1 = 0; Index1 < gSdlPciData->PciDevCount; Index1++) {
        SdlDevInfo = &gSdlPciData->PciDevices [Index1];

        if ((SdlDevInfo->PciDevFlags.Bits.PciDevice) && (!SdlDevInfo->PciDevFlags.Bits.OnBoard)) {

            DEBUG ((DEBUG_VERBOSE,"CollectPciSlotDevicesDataFromSdl: SdlDevInfo->Slot 0x%X \n", SdlDevInfo->Slot));
            DEBUG ((DEBUG_VERBOSE,"CollectPciSlotDevicesDataFromSdl: gNumberOfSlotsToShow 0x%X \n", gNumberOfSlotsToShow));
            //Slots should have NON zero slot Numbers
            if (SdlDevInfo->Slot > 0x00) {
                for (Index2 = 0; Index2 < gNumberOfSlotsToShow; Index2++) {

                    DEBUG ((DEBUG_VERBOSE,"CollectPciSlotDevicesDataFromSdl: gSlotsToShow[Index2] 0x%X \n", gSlotsToShow[Index2]));
                    // Loop through & get matching slot numbers from display sdl list
                    if (gSlotsToShow [Index2] == SdlDevInfo->Slot) {
                        //If match Found
                        ROM_POLICY_CB_DATA        *SlotDevData;
                        SlotDevData = AllocateZeroPool (sizeof(ROM_POLICY_CB_DATA));
                        if (SlotDevData == NULL) return EFI_OUT_OF_RESOURCES;

                        SlotDevData->PciSdlInfo = SdlDevInfo;
                        SlotDevData->SdlIdx = Index1;
                        DEBUG ((DEBUG_VERBOSE,"CollectPciSlotDevicesDataFromSdl: SlotDevData->SdlIdx 0x%X \n\n", SlotDevData->SdlIdx));

                        Status = AppendItemLst ((T_ITEM_LIST*)&gOpromPciDevDataList->SlotInitCount, SlotDevData);
                        ASSERT_EFI_ERROR (Status);
                        break;
                    }
                }
            }
        }
    }

    DEBUG ((DEBUG_VERBOSE,"CollectPciSlotDevicesDataFromSdl: gOpromPciDevDataList->SlotDevCount  0x%X \n\n", gOpromPciDevDataList->SlotDevCount));

    return Status;
}

/**

    Search Matching Slot in Show sdl List
    
    @param      UINTN      SlotShowIndex,
                UINTN      ListSlotDeviceCount
    
    @retval BOOLEAN

**/
BOOLEAN 
SearchMatchingSlotinShowList(
    UINTN      SlotShowIndex,
    UINTN      ListSlotDeviceCount
)
{
    UINTN                       sIndex = 0;

    for(sIndex = 0; sIndex < ListSlotDeviceCount; sIndex++) {

        ROM_POLICY_CB_DATA          *ListSlotData = gOpromPciDevDataList->SlotDevData[sIndex];
        AMI_SDL_PCI_DEV_INFO        *ListSlotSdlInfo = ListSlotData->PciSdlInfo;
        
        DEBUG((DEBUG_VERBOSE,"SearchMatchingSlotinShowList ListSlotSdlInfo->Slot 0x%X \n", ListSlotSdlInfo->Slot));
        DEBUG((DEBUG_VERBOSE,"SearchMatchingSlotinShowList gSlotsToShow[nIndex] 0x%X \n", gSlotsToShow[SlotShowIndex] ));
        
        if(gSlotsToShow[SlotShowIndex] == ListSlotSdlInfo->Slot){
            DEBUG((DEBUG_VERBOSE,"SearchMatchingSlotinShowList found matching\n\n"));
            return TRUE; 
        }
    }
        
    return FALSE;
}

/**
    Appends Slot List with dummy SdlDevData for unlisted Slot Sdl Table Items to show in setup 

    @param  VOID
    
    @retval EFI_STATUS

**/
EFI_STATUS 
AppendUnlistedSlotItems (
    VOID
  )
{
    UINTN                       Index;
    EFI_STATUS                  Status = EFI_SUCCESS;
    UINTN                       ListSlotDeviceCount = gOpromPciDevDataList->SlotDevCount;
    //--------------------------------

    DEBUG ((DEBUG_VERBOSE,"AppendUnlistedSlotItems:  gOpromPciDevDataList->SlotDevCount 0x%X, ListSlotDeviceCount 0x%X,gNumberOfSlotsToShow 0x%X  \n", 
                                                    gOpromPciDevDataList->SlotDevCount, ListSlotDeviceCount, gNumberOfSlotsToShow ));

    // If extra slot items present in Sdl display table,  add dummy entry in Slot List
    if (gNumberOfSlotsToShow > (UINT32)(gOpromPciDevDataList->SlotDevCount)) { 

        for (Index = 0; Index < gNumberOfSlotsToShow; Index++) {
            if (!SearchMatchingSlotinShowList (Index, ListSlotDeviceCount)) {

                AMI_SDL_PCI_DEV_INFO    *NewSdlDev;
                ROM_POLICY_CB_DATA      *NewSlotDevData;
                //--------------------------------

                NewSdlDev = AllocateZeroPool (sizeof (AMI_SDL_PCI_DEV_INFO));
                if (NewSdlDev == NULL) return EFI_OUT_OF_RESOURCES;

                DEBUG ((DEBUG_VERBOSE,"AppendUnlistedSlotItems: 111 Index 0x%X, ListSlotDeviceCount 0x%X,gSlotsToShow[nIndex] 0x%X  \n\n",
                    Index, ListSlotDeviceCount, gSlotsToShow[Index]));
                // Create Slot item for missing entries
                NewSdlDev->Slot = (UINT32)gSlotsToShow [Index];

                NewSlotDevData = AllocateZeroPool (sizeof (ROM_POLICY_CB_DATA));
                if(NewSlotDevData == NULL) return EFI_OUT_OF_RESOURCES;

                NewSlotDevData->PciSdlInfo = NewSdlDev; 

                Status = AppendItemLst ((T_ITEM_LIST*)&gOpromPciDevDataList->SlotInitCount, NewSlotDevData);
                ASSERT_EFI_ERROR (Status);
            }
        }
    }

    DEBUG ((DEBUG_VERBOSE,"AppendUnlistedSlotItems: Status 0x%X , Final gOpromPciDevDataList->SlotDevCount  0x%X \n\n", 
        Status, gOpromPciDevDataList->SlotDevCount ));

    return Status;
}


/**
    Initializes Rom Items List from Pci SDL device Data for Valid Onboard and Slots to be displayed 

    @param  VOID
    
    @retval EFI_STATUS

**/
EFI_STATUS 
InitRomDataFromSdl(
        VOID
)
{
    UINTN                   Index = 0;
    EFI_STATUS              Status;
//------    
    Status = CollectPciOnboardDevicesDataFromSdl();
    ASSERT_EFI_ERROR(Status);
    
    Status = CollectPciSlotDevicesDataFromSdl();
    ASSERT_EFI_ERROR(Status);
    
    Status = AppendUnlistedSlotItems();
    ASSERT_EFI_ERROR(Status);
        
    //Update Onboard Items to Rom Items List
    for(Index = 0; Index < gOpromPciDevDataList->ObDevCount; Index++) {
        Status = AppendItemLst((T_ITEM_LIST*)&gOptRomData.InitCount, gOpromPciDevDataList->OnboardDevData[Index]);
        ASSERT_EFI_ERROR(Status);
    }
    
    //Update Onboard Items to Rom Items List
    for(Index = 0; Index < gOpromPciDevDataList->SlotDevCount; Index++) {
        Status = AppendItemLst((T_ITEM_LIST*)&gOptRomData.InitCount, gOpromPciDevDataList->SlotDevData[Index]); 
        ASSERT_EFI_ERROR(Status);
    }
    
    DEBUG((DEBUG_INFO," Total Initial RomItemsCount 0x%X \n", gOptRomData.RomItemsCount));
    
    ClearItemLst((T_ITEM_LIST*)&gOpromPciDevDataList->ObInitCount,FALSE);
    ClearItemLst((T_ITEM_LIST*)&gOpromPciDevDataList->SlotInitCount,FALSE);
    
    return Status;
}


/**
    
    Get Matching Sdl Device Index value from Slot number or Asl Name
    @param  ROM_POLICY_VAR  *rp, 
        UINTN               *SdlIdx
    
    @retval AMI_SDL_PCI_DEV_INFO

**/
AMI_SDL_PCI_DEV_INFO* 
GetMatchingSdlDevice (
  ROM_POLICY_VAR             *rp,
  UINTN                      *SdlIdx
  )
{
    UINT32                   Index;
    AMI_SDL_PCI_DEV_INFO    *SdlDev;

    //Look in SDL DB for PCI Devices with Opt ROMs and Slots  
    for(Index = 0; Index < gSdlPciData->PciDevCount; Index++) {
        SdlDev = &gSdlPciData->PciDevices[Index];

        //DEBUG ((DEBUG_VERBOSE, "gSdlPciData->PciDevCount: %2x \n" , gSdlPciData->PciDevCount));
        //DEBUG ((DEBUG_VERBOSE, "Index: %2x rp->SlotNum: %4d rp->AslName: %a SdlDev->Slot: %4d SdlDev->AslName: %a\n",
               // Index, rp->SlotNum, rp->AslName, SdlDev->Slot, SdlDev->AslName));
        // For Slots, use SlotNum to find Sdl Device
        // For Onboard device, use ASLName
        if  ((rp->SlotNum && (SdlDev->Slot == rp->SlotNum)) || 
             (!rp->SlotNum && !AsciiStrCmp ((CHAR8 *)rp->AslName, (CHAR8 *)SdlDev->AslName)) ) {
            //DEBUG ((DEBUG_VERBOSE, "gSdlPciData->PciDevCount: %2x \n" , Index));
            *SdlIdx = Index;
            return SdlDev;
        }
    }
    return NULL;
}


/**
    Initializes Rom Items List from previously set Variable. 
    Slot list should match slot display list in sdl.
    If matching sdl value is not found, it means slot number is different, 
    if so create a dummy entry.
    
    @param  BOOLEAN Extra
    
    @retval EFI_STATUS

**/
EFI_STATUS  
InitRomDataFromVar(
        BOOLEAN Extra
)
{
    UINTN                   i,j,lim;
    EFI_STATUS              Status;
//--------------    
    
    if(Extra) lim=gRomSetupPtr->ExtraRomCount;
    else lim=gRomSetupPtr->OptRomCount;
    

    DEBUG((DEBUG_INFO,"InitRomDataFromVar : %d lim: %d \n", Extra, lim));

    for(i=0; i<lim; i++){
        ROM_POLICY_VAR          *rp;
        ROM_POLICY_CB_DATA      *cb;
        AMI_SDL_PCI_DEV_INFO    *sdldev;
        UINTN                   SdlIdx=0;
        //----------------
        if(Extra)j=gRomSetupPtr->OptRomCount+i;
        else j=i;

        rp=&gRomSetupPtr->PolicyOption[j];

        cb=MallocZ(sizeof(ROM_POLICY_CB_DATA));
        if(cb==NULL) return EFI_OUT_OF_RESOURCES;

        sdldev = GetMatchingSdlDevice(rp, &SdlIdx);
        DEBUG((DEBUG_VERBOSE,"i: %d j: %d  rp->SlotNum: %x sdldev: %p SdlIdx: %x \n", i, j, rp->SlotNum, sdldev, SdlIdx));
        if (sdldev == NULL) {
            sdldev=MallocZ(sizeof(AMI_SDL_PCI_DEV_INFO));
            if(sdldev==NULL) return EFI_OUT_OF_RESOURCES;
            //Assign Slot number: RomItemsCount is ZERO Based
            sdldev->Slot = rp->SlotNum;
            SdlIdx = 0;
        }

        cb->PciSdlInfo=sdldev;   
        cb->SdlIdx=SdlIdx;

        Status=AppendItemLst((T_ITEM_LIST*)&gOptRomData.InitCount,  cb);
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status)) return Status;
    }

    if(Extra){
        gRomSetupPtr->OptRomCount+=gRomSetupPtr->ExtraRomCount;
        gRomSetupPtr->ExtraRomCount=0;
    }
    DEBUG((DEBUG_INFO,"gOptRomData.OptRomCount: %d after \n", gOptRomData.RomItemsCount));

    return Status;
}

/**
    Updates RomPolicy to Uefi when Csm is unavailable.
    SignalConnectDriversEvent installation notification callback. 
    
    @param Event - event signaled by the BDS upon  SignalConnectDriversEvent
    @param Context - event context, not used

    @retval NONE
**/
VOID 
UpdateRomPolicyToUefiWhenCsmUnavailable (
    IN EFI_EVENT              Event, 
    IN VOID                   *Context
  )
{
    EFI_STATUS                Status = EFI_SUCCESS;
    EFI_LEGACY_BIOS_PROTOCOL  *LegacyBios;

    // We are at SignalConnectDriversEvent. If Legacy Bios Protocol is unavailable 
    // still, assign all policy values to UEFI.
    //
    Status = gBS->LocateProtocol (&gEfiLegacyBiosProtocolGuid, NULL, (VOID **) &LegacyBios);
    if (EFI_ERROR (Status)) {
        UpdateRomPolicyToDefaultUefi ();
    }

    if (Event != NULL) {
           Status = gBS->CloseEvent (Event);
           ASSERT_EFI_ERROR (Status);
    }

    return;
}

/**
    
    Updates all policy values to UEFI
    
    @param  None
    
    @retval NONE

**/
VOID 
UpdateRomPolicyToDefaultUefi(
    VOID
)
{
    UINTN                   RomCountIndex = 0;
    BOOLEAN                 PolicyChanged = FALSE;


    GetSetRomData(TRUE);
    
    DEBUG((DEBUG_VERBOSE,"OptRomPolicy: UpdateRomPolicyToDefaultUefi \n"));
    
    for(RomCountIndex = 0; RomCountIndex < gRomSetupPtr->OptRomCount; RomCountIndex++) {
        if(gRomSetupPtr->PolicyOption[RomCountIndex].Option == AMI_OPTION_ROM_POLICY_LEGACY) {
            gRomSetupPtr->PolicyOption[RomCountIndex].Option = AMI_OPTION_ROM_POLICY_UEFI;
            PolicyChanged = TRUE;
        }       
    }
    
    if(PolicyChanged) {
        GetSetRomData(FALSE);
    }

    return;
}

/**
    LegacyBiosProtocol installation notification callback. 
    
    @param Event - event signaled by the BDS upon LegacyBiosProtocol
    @param Context - event context, not used
    
    @retval NONE

**/
VOID 
OptionRomPolicyLegacyBiosCallback (
    IN EFI_EVENT    Event, 
    IN VOID         *Context
  )
{
    EFI_STATUS      Status;

    gCsmSupported = TRUE;

    if (Event != NULL) {
           Status = gBS->CloseEvent (Event);
           ASSERT_EFI_ERROR (Status);
    }

    return;
}


/**
    This is the standard EFI driver entry point called for CSM Policy module
    initialization

    @param ImageHandle ImageHandle of the loaded driver
    @param SystemTable Pointer to the System Table

    @retval EFI_SUCCESS if everything good
    @retval EFI_ERROR value if something wrong happens

**/
EFI_STATUS 
EFIAPI 
OptionRomPolicyEntryPoint (
    IN EFI_HANDLE             ImageHandle,
    IN EFI_SYSTEM_TABLE       *SystemTable
  )
{
    EFI_STATUS                Status = EFI_SUCCESS;
//    AMI_SDL_PCI_DEV_INFO    *sdldev;
    UINTN                     Size;
    EFI_EVENT                 ClearFbEvent = NULL;
    BOOLEAN                   RomFbVar = FALSE;

    EFI_LEGACY_BIOS_PROTOCOL  *LegacyBios;
    EFI_EVENT                 OptRomPolicyLegacyBiosEvent;
    EFI_EVENT                 OrpBdsConnectDriversEvent;
    VOID                      *OptRomPolicyLegacyBiosRegn;
    VOID                      *OrpConnectDriversRegn;

    //---------------------    

    InitAmiLib (ImageHandle, SystemTable);
    //START: Coverity Issue :CHECKED_RETURN
    Status = AmiSdlInitBoardInfo ();
    if (EFI_ERROR(Status)) return Status;
    //END: Coverity Issue :CHECKED_RETURN
    
    Status = gBS->LocateProtocol (
                           &gEfiLegacyBiosProtocolGuid,
                           NULL,
                           (VOID **) &LegacyBios);
    
    if (!EFI_ERROR(Status)) {
        DEBUG ((DEBUG_VERBOSE,"OptionRomPolicyEntryPoint gEfiLegacyBiosProtocolGuid Present \n"));
        gCsmSupported = TRUE;
    } else {
        DEBUG ((DEBUG_VERBOSE,"OptionRomPolicyEntryPoint gEfiLegacyBiosProtocolGuid NOT Present \n"));
        RegisterProtocolCallback (
                     &gAmiBdsConnectDriversProtocolGuid,
                     UpdateRomPolicyToUefiWhenCsmUnavailable,
                     NULL,
                     &OrpBdsConnectDriversEvent,
                     &OrpConnectDriversRegn);

        RegisterProtocolCallback (
                     &gEfiLegacyBiosProtocolGuid,
                     OptionRomPolicyLegacyBiosCallback,
                     NULL,
                     &OptRomPolicyLegacyBiosEvent,
                     &OptRomPolicyLegacyBiosRegn);
    }

    //Clear Space...
    ZeroMem (&gOptRomData, sizeof (ROM_POLICY_INFO));
    ZeroMem (&gSetupData, sizeof (SETUP_DATA));
    ZeroMem (&gCsmSetup, sizeof (CSM_SETUP_DATA));
    gOptRomData.CsmSetup = &gCsmSetup;

    gOpromPciDevDataList = AllocateZeroPool (sizeof (OPROM_PCI_DEV_DATA_LIST));
    if (gOpromPciDevDataList == NULL) return EFI_OUT_OF_RESOURCES;

    //Get CSM Policy Vars from Common Setup Data...
    Size = sizeof (SETUP_DATA);
    Status = gRT->GetVariable (L"Setup",&AmiSetupGuid, &gSetupAttributes, &Size, &gSetupData);
    if (EFI_ERROR(Status)) {
#if ((defined CSM_SUPPORT) && (CSM_SUPPORT==1))
    //Set Defaults of CSM at SETUP_DATA var
        if (DeviceClassPolicyOverride && PolicyOverrideMode == AMI_OPT_ITEM_PRIORITY) gSetupData.VideoOpRom = 1;
        else gSetupData.VideoOpRom = DEFAULT_VIDEO_OPROM_POLICY;
        gSetupData.MassStorageOpRom = DEFAULT_MASS_STORAGE_OPROM_POLICY;
        gSetupData.PxeOpRom = DEFAULT_PXE_OPROM_POLICY;
        gSetupData.OldOpRom = AMI_OPTION_ROM_POLICY_UEFI;
        gSetupData.CsmSupport = 1;
#else
        if (DEFAULT_VIDEO_OPROM_POLICY == AMI_OPTION_ROM_POLICY_LEGACY) gSetupData.VideoOpRom = AMI_OPTION_ROM_POLICY_UEFI;
        else gSetupData.VideoOpRom = DEFAULT_VIDEO_OPROM_POLICY;
        if (DEFAULT_MASS_STORAGE_OPROM_POLICY == AMI_OPTION_ROM_POLICY_LEGACY) gSetupData.MassStorageOpRom = AMI_OPTION_ROM_POLICY_UEFI;
        else gSetupData.MassStorageOpRom = DEFAULT_MASS_STORAGE_OPROM_POLICY;
        if (DEFAULT_PXE_OPROM_POLICY == AMI_OPTION_ROM_POLICY_LEGACY) gSetupData.PxeOpRom = AMI_OPTION_ROM_POLICY_UEFI;
        else gSetupData.PxeOpRom = DEFAULT_PXE_OPROM_POLICY;
        gSetupData.OldOpRom = AMI_OPTION_ROM_POLICY_UEFI;
        gSetupData.CsmSupport = 0;
        gCsmSupported = FALSE;
#endif
        gSetupAttributes = (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS);
        Status = gRT->SetVariable (L"Setup",&AmiSetupGuid, gSetupAttributes, sizeof (SETUP_DATA), &gSetupData);
        ASSERT_EFI_ERROR (Status);
    }

    //Get policy VAR and allocate space for it.
    Size = sizeof (ROM_SETUP_DATA);//+( sizeof(ROM_POLICY_VAR) * (gOptRomData.RomItemsCount - 1) );
    gRomSetupPtr = AllocateZeroPool (Size);
    if (gRomSetupPtr == NULL) return EFI_OUT_OF_RESOURCES;
    gOptRomData.RomSetup = gRomSetupPtr;

    Status = GetSetRomData (TRUE);
    //VAR does not exist - init is with defaults...
    if (EFI_ERROR(Status)||(!gRomSetupPtr->SdlScanned)) {
        DEBUG ((DEBUG_INFO,"OptRomSetup: OptRomSetupVar Does not exist or uninitialized. Initialize with DEFAULTS...\n"));
        //EFI_DEADLOOP();
        Status = InitRomDataFromSdl();
        ASSERT_EFI_ERROR (Status);
        gRomSetupPtr->SdlScanned = TRUE;
        SortData ();
        Status = SetRomPolicyDefaults (TRUE);
        ASSERT_EFI_ERROR (Status);
        if (EFI_ERROR(Status)) return Status;
    } else {
        if ((!gCsmSupported)||(gSetupData.CsmSupport == 0)) {
            UpdateRomPolicyToDefaultUefi ();
        }
        //Data sorted already in the ROM_VAR so just use it;
        Status = InitRomDataFromVar (FALSE);
        ASSERT_EFI_ERROR (Status);
        if (EFI_ERROR (Status)) return Status;
    }

    //If no PCI devices with Option ROMs .... just exit..
    if (gOptRomData.RomItemsCount == 0 && gRomSetupPtr->ExtraRomCount == 0) return EFI_SUCCESS;

    //Check Data consistency
    if (gRomSetupPtr->OptRomCount != gOptRomData.RomItemsCount) {
        DEBUG((DEBUG_INFO,"OptRomSetup: SetupPtr.OptRomCount(0x%X)!= (0x%X)gOptRomData.RomItemsCount;\n",
                gRomSetupPtr->OptRomCount, gOptRomData.RomItemsCount));
        //EFI_DEADLOOP();
        gRomSetupPtr->SdlScanned = FALSE;
        SortData ();
        Status = SetRomPolicyDefaults (TRUE);
        if (EFI_ERROR (Status)) return Status;
    }

    //Check if PciBusDeriver has added some OptROMs of Onboard device w/o ROM SDL flag
    if (gRomSetupPtr->ExtraRomCount) {
        DEBUG ((DEBUG_INFO,"OptRomSetup: SetupPtr.ExtraRomCount(0x%X)!= 0 Processing;\n", gRomSetupPtr->ExtraRomCount));
        //EFI_DEADLOOP();
        Status = InitRomDataFromVar (TRUE);
        ASSERT_EFI_ERROR (Status);
        if (EFI_ERROR(Status)) return Status;
        SortData ();
        //START: Coverity Issue : UNUSED_VALUE
        SetRomPolicyDefaults (TRUE);
        //END: Coverity Issue : UNUSED_VALUE
    }

    //Print how many devices with setup have been found...
    DEBUG ((DEBUG_INFO,"OptRomSetup: Found 0x%X Objects With Potential Option ROMs... %r.\n",gOptRomData.RomItemsCount, Status));

    //If PCI Device Class Policy not Shown...
    //Make sure all options set to UEFI and user can't disable CSM support.
    //if gSetupData.CsmSupport == 0 means all options already set to ENABLED.
    if (DeviceClassPolicyOverride && gSetupData.CsmSupport && PolicyOverrideMode==AMI_OPT_ITEM_PRIORITY){
        BOOLEAN     UpdateVar = FALSE;
    //----------------------    
        if (gSetupData.VideoOpRom != AMI_OPTION_ROM_POLICY_UEFI){
            gSetupData.VideoOpRom = AMI_OPTION_ROM_POLICY_UEFI;
            UpdateVar = TRUE;
        }

        if (gSetupData.MassStorageOpRom != AMI_OPTION_ROM_POLICY_UEFI){
            gSetupData.MassStorageOpRom = AMI_OPTION_ROM_POLICY_UEFI;
            UpdateVar = TRUE;
        }

        if (gSetupData.PxeOpRom != AMI_OPTION_ROM_POLICY_UEFI){
            gSetupData.PxeOpRom = AMI_OPTION_ROM_POLICY_UEFI;
            UpdateVar = TRUE;
        }

        if (gSetupData.OldOpRom != AMI_OPTION_ROM_POLICY_UEFI){
            gSetupData.OldOpRom = AMI_OPTION_ROM_POLICY_UEFI;
            UpdateVar = TRUE;
        }

        if (UpdateVar) {
            Status = gRT->SetVariable (L"Setup", &AmiSetupGuid, gSetupAttributes, sizeof (SETUP_DATA), &gSetupData);
            ASSERT_EFI_ERROR (Status);
            if (EFI_ERROR(Status)) return Status;
        }
    }

    //Create ROM NVRAM Variables...if they do not exist
    //START: Coverity Issue : UNUSED_VALUE
    GetSetCsmData (TRUE);
    //START: Coverity Issue : UNUSED_VALUE

    //check if MAX_NUMBER_OF_ROM_ITEMS >= gOptRomData.RomItemsCount
    if (MAX_NUMBER_OF_ROM_ITEMS < gOptRomData.RomItemsCount) {
        DEBUG((DEBUG_ERROR,"OptRomSetup: !!!!WARNING!!!!... MAX_NUMBER_OF_ROM_ITEMS < ROM_Items_Found %d < %d.\n",
                MAX_NUMBER_OF_ROM_ITEMS, gOptRomData.RomItemsCount));
        ASSERT_EFI_ERROR (EFI_DEVICE_ERROR);
    }

    //Just to know if VGA device changed at next boot...
    gEntryVgaIdx = gRomSetupPtr->PriVgaIdx;
    gEntryGrop = gRomSetupPtr->PriVgaGroupValue;
    gEntryItem = gRomSetupPtr->PriVgaItemValue;
    DEBUG ((DEBUG_INFO,"OptRomSetup: Entry Settings: VgaIdx=0x%X; Item=%d; Group=%d;\n", 
            gEntryVgaIdx, gEntryGrop, gEntryItem));

    //Get Fail to Boot var....
    if (gRomSetupPtr->ResetPolicy) {
        Size = sizeof (RomFbVar);
        Status = gRT->GetVariable (L"ROM_FB",&RomSetupGuid, &gRomFbAttributes, &Size, &RomFbVar);
        //If var exists and System failed to boot....
        if ((!EFI_ERROR(Status)) && RomFbVar){
            DEBUG ((DEBUG_ERROR,"OptRomSetup: Fail To Boot detected RomFbVar=%d. Loading Defaults\n",RomFbVar)); 

            RestoreDefaults ();
        }
    }

    Status=CheckRomPolicyVgaStatus (FALSE);
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR(Status)) return Status;

    //Load setup page and update strings
    LoadResources (ImageHandle, sizeof (SetupCallBack) / sizeof (CALLBACK_INFO), SetupCallBack, NULL);
    gRomHiiHandle = SetupCallBack[0].HiiHandle;

    InitDriverVersionString ();

    // Register callback on TSE event to update IFR data
    {
        VOID *SetupRegistration;
        static EFI_GUID SetupEnterGuid = AMITSE_SETUP_ENTER_GUID;
        static EFI_EVENT SetupEnterEvent;

        RegisterProtocolCallback (
            &SetupEnterGuid, InitRomIfr,
            NULL, &SetupEnterEvent, &SetupRegistration
        );
    }

    // Create ReadytoBoot to update IFR data
    {
        EFI_EVENT               InitRomRbEvent = NULL;
        Status = CreateReadyToBootEvent (
                                TPL_CALLBACK,
                                InitRomIfr,
                                NULL,
                                &InitRomRbEvent);
        ASSERT_EFI_ERROR (Status);
   }

    //if Customer selected restore defaults when fail to boot...
    if (gRomSetupPtr->ResetPolicy) {

        RomFbVar = ROM_FAIL_TO_BOOT;
        Status=gRT->SetVariable (L"ROM_FB",&RomSetupGuid, gRomFbAttributes, sizeof(RomFbVar), &RomFbVar);
        ASSERT_EFI_ERROR (Status);
        
        // Register the event handling function to Reset Fail To Boot Var.
        Status = CreateReadyToBootEvent (
                            TPL_CALLBACK,
                            ClearFailToBootVar,
                            NULL,
                            &ClearFbEvent);
        ASSERT_EFI_ERROR (Status);
    }

    // Override current CSM option ROM policy protocols.
    //
    // AMI_CSM_OPROM_POLICY_PROTOCOL provides policy access by PciHandle
    // AMI_OPROM_POLICY_PROTOCOL provides policy access by PciClass
    {
        AMI_CSM_OPROM_POLICY_PROTOCOL *AmiCsmOpromPolicy = NULL;
        EFI_EVENT OpromPolicyOverrideEvent;

        Status = gBS->LocateProtocol (
                               &gAmiCsmOpromPolicyProtocolGuid, 
                               NULL, 
                               (VOID **)&AmiCsmOpromPolicy);

        if (EFI_ERROR(Status)) {

            Status = RegisterProtocolCallback (&gAmiCsmOpromPolicyProtocolGuid, 
                            CsmOpromPolicyOverrideCallback, 
                            NULL, 
                            &OpromPolicyOverrideEvent, 
                            &gCsmOpromPolicyOverrideRegistration);
            ASSERT_EFI_ERROR (Status);
        } else {
            CsmOpromPolicyOverrideCallback (NULL, NULL);
        }
    }

    {
        AMI_OPROM_POLICY_PROTOCOL  *AmiOpromPolicy = NULL;
        EFI_EVENT                  OpromPolicyOverrideEvent;

        Status = gBS->LocateProtocol (
                                  &gAmiOpromPolicyProtocolGuid, 
                                  NULL, 
                                  (VOID **)&AmiOpromPolicy);
        if (EFI_ERROR (Status)) {
            Status = RegisterProtocolCallback (&gAmiOpromPolicyProtocolGuid, 
                            OpromPolicyOverrideCallback, 
                            NULL, 
                            &OpromPolicyOverrideEvent, 
                            &gOpromPolicyOverrideRegistration);
            ASSERT_EFI_ERROR (Status);
        } else {
            OpromPolicyOverrideCallback (NULL, NULL);
        }
    }

    return Status;
}

/**
    This function overrides the functionality of
    AMI_OPROM_POLICY_PROTOCOL.CheckUefiOpRomPolicy installed
    by CsmPolicy.
    
    @note Original CsmPolicy functions are stored in gAmiOpromPolicy variable.
    
    @param This - pointer to AMI_OPROM_POLICY_PROTOCOL
    @param PciClass - PCI device class

    @retval EFI_SUCCESS OpROM should be executed
    @retval EFI_UNSUPPORTED OpROM should not be executed
    @retval EFI_NO_MAPPING group policy not available due to policy settings

**/

EFI_STATUS 
CheckUefiOpRomPolicy(
    IN  AMI_OPROM_POLICY_PROTOCOL *This,
    IN  UINT8                     PciClass
)
{
    UINT8   Policy;
    BOOLEAN Result = TRUE;

    Policy = GetOpRomPolicy(PciClass);

    if(Policy == AMI_OPTION_ROM_POLICY_DISABLE || Policy == AMI_OPTION_ROM_POLICY_LEGACY  ) {
        Result = FALSE;
    }
    
    return (Result) ? EFI_SUCCESS : EFI_UNSUPPORTED;
}


/**
    This function overrides the functionality of
    AMI_CSM_OPROM_POLICY_PROTOCOL.CheckUefiOpRomPolicyByPciHandle installed
    by CsmPolicy.
    
    @note Original CsmPolicy functions are stored in gAmiCsmOpromPolicy variable.
         
    @param This - pointer to pointer to AMI_CSM_OPROM_POLICY_PROTOCOL
    @param PciHandle - PCI device handle
          
    @retval EFI_SUCCESS OpROM should be executed
    @retval EFI_UNSUPPORTED OpROM should not be executed

**/
EFI_STATUS 
CheckUefiOpRomPolicyByPciHandle (
    IN  AMI_CSM_OPROM_POLICY_PROTOCOL  *This,
    IN  EFI_HANDLE                     PciHandle
  )
{
    EFI_STATUS Status;
    EFI_PCI_IO_PROTOCOL                *PciIo;
    UINT8                              PciClass;
    AMI_OPTION_ROM_POLICY_PROTOCOL     *OpRomPolicyProt;
    UINT8                              ItemPolicy, GroupPolicy;

    //--------------------
    Status = gBS->HandleProtocol (
                    PciHandle, 
                    &gEfiPciIoProtocolGuid, 
                    (VOID **)&PciIo
                    );

    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) return Status;

    Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint8, 0xB, 1, &PciClass);
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) return Status;

    Status = gBS->HandleProtocol (
                    PciHandle, 
                    &gAmiOptionRomPolicyProtocolGuid, 
                    (VOID **)&OpRomPolicyProt
                    );

    if (EFI_ERROR(Status)) goto business_as_usual;

    //Figure out if Device Class Policy Override option is on...
    if (DeviceClassPolicyOverride) { 
        //Get Item Policy value...
        Status = OpRomPolicyProt->GetOptionRomPolicy (OpRomPolicyProt, &ItemPolicy, NULL);
        ASSERT_EFI_ERROR (Status);
        if (EFI_ERROR (Status)) return Status;
    
        //And Group Policy as well...
        GroupPolicy = GetOpRomPolicy (PciClass);
    
        //Check policy Override mode...
        //In Mode 0 Item Policy has priority over Group Policy
        if (PolicyOverrideMode == AMI_OPT_ITEM_PRIORITY) {
            if (ItemPolicy==AMI_OPTION_ROM_POLICY_UEFI) return EFI_SUCCESS;
            else return EFI_UNSUPPORTED;
        }

        //In Mode 1 Item Policy ONLY used when Group Policy == AMI_OPT_ROM_POLICY_CUSTOM
        if (PolicyOverrideMode == AMI_OPT_GROUP_PRIORITY && GroupPolicy == AMI_OPTION_ROM_POLICY_CUSTOM) {
            //check if group policy was overridden...
            if (ItemPolicy == AMI_OPTION_ROM_POLICY_UEFI) return EFI_SUCCESS;
            else return EFI_UNSUPPORTED;
        }
    }
    //In all other cases business as usual.    
business_as_usual:
    return gAmiCsmOpromPolicy.CheckOpromPolicy (This, PciHandle);
}


/**
    This function will be called before and after installing legacy OpROM
    @note  
          PolicyData is valid when this call is made before Option ROM execution, it
          is NULL when this function is called after Option ROM execution.

    @param  OPTIONAL AMI_CSM_PLATFORM_POLICY_DATA
          
    @retval  VOID    

**/
VOID 
ProcessOpRom (
    IN OPTIONAL AMI_CSM_PLATFORM_POLICY_DATA *OpRomStartEndProtocol
  )
{
    EFI_PCI_IO_PROTOCOL             *PciIo;
    UINT8                           PciClassCode;
    EFI_STATUS                      Status;
    AMI_OPTION_ROM_POLICY_PROTOCOL  *OpRomPolicyProt;
    UINT8                           ItemPolicy,GroupPolicy;

    if (OpRomStartEndProtocol == NULL) goto business_as_usual;

    //check if someone already disabled execution of this OpROM
    if(OpRomStartEndProtocol->PciIo == NULL || OpRomStartEndProtocol->ExecuteThisRom == FALSE)
            return;

    PciIo = OpRomStartEndProtocol->PciIo;
    Status = PciIo->Pci.Read (PciIo, EfiPciIoWidthUint8, 0xB, 1, &PciClassCode);
    if (EFI_ERROR(Status)) 
            return;

//-----------------    
    Status = gBS->HandleProtocol (
                    OpRomStartEndProtocol->PciHandle, 
                    &gAmiOptionRomPolicyProtocolGuid, 
                    (VOID **)&OpRomPolicyProt
                    );

    if (EFI_ERROR (Status)) goto business_as_usual;

    if (DeviceClassPolicyOverride) { 
        //Get Item Policy value...
        Status = OpRomPolicyProt->GetOptionRomPolicy (OpRomPolicyProt, &ItemPolicy, NULL);
        ASSERT_EFI_ERROR (Status);
        if (EFI_ERROR(Status)) return;

        //And Group Policy as well...
        GroupPolicy = GetOpRomPolicy (PciClassCode);

        //Check policy Override mode...
        //In Mode 0 Item Policy has priority over Group Policy
        if (PolicyOverrideMode == AMI_OPT_ITEM_PRIORITY) {
            if (ItemPolicy == AMI_OPTION_ROM_POLICY_LEGACY) {
                OpRomStartEndProtocol->ExecuteThisRom = TRUE;
            } else {
                OpRomStartEndProtocol->ExecuteThisRom = FALSE;
            }
            return;
        }

        //In Mode 1 Item Policy ONLY used when Group Policy == AMI_OPT_ROM_POLICY_CUSTOM
        if (PolicyOverrideMode == AMI_OPT_GROUP_PRIORITY && GroupPolicy == AMI_OPTION_ROM_POLICY_CUSTOM) {
            //check if group policy was overridden...

            if (ItemPolicy == AMI_OPTION_ROM_POLICY_LEGACY ) {
                OpRomStartEndProtocol->ExecuteThisRom = TRUE;
            } else {
                OpRomStartEndProtocol->ExecuteThisRom = FALSE;
            }
            return;
        }
    }
    //In all other cases business as usual.
    business_as_usual:
        gAmiCsmOpromPolicy.ProcessOpRom (OpRomStartEndProtocol);
}


/**
    AMI_CSM_OPROM_POLICY_PROTOCOL installation notification callback. Uninstall the
    AMI_CSM_OPROM_POLICY_PROTOCOL and install a new one.
    
    @note The callback event must be closed prior to the protocol installation to avoid the
    recurrent callbacks.
    
    @param Event - event signaled by the DXE Core upon gAmiCsmOpromPolicyProtocol installation
    @param Context - event context, not used

    @retval  VOID    

**/

VOID
CsmOpromPolicyOverrideCallback (
    EFI_EVENT   Event,
    VOID        *Context
  )
{
    EFI_STATUS Status;
    AMI_CSM_OPROM_POLICY_PROTOCOL *CurrentAmiOpromPolicy = NULL;
    EFI_HANDLE Handle;
    UINTN HandleSize = sizeof (EFI_HANDLE);

    static AMI_CSM_OPROM_POLICY_PROTOCOL NewAmiOpromPolicy = {
        CheckUefiOpRomPolicyByPciHandle,
        ProcessOpRom
    };
    
    Status = gBS->LocateHandle (
                    ByRegisterNotify,
                    NULL,
                    gCsmOpromPolicyOverrideRegistration,
                    &HandleSize,
                    &Handle
                    );

    if (EFI_ERROR(Status))
    {
        Status = gBS->LocateHandle(
                        ByProtocol,
                        &gAmiCsmOpromPolicyProtocolGuid,
                        NULL,
                        &HandleSize,
                        &Handle
                        );
        ASSERT_EFI_ERROR (Status);
    }

    ASSERT_EFI_ERROR (Status);

    Status = gBS->HandleProtocol (
                    Handle, 
                    &gAmiCsmOpromPolicyProtocolGuid, 
                    (VOID **)&CurrentAmiOpromPolicy
                    );
    ASSERT_EFI_ERROR (Status);

    // Save the original CSM policy pointers for future use
    gAmiCsmOpromPolicy.CheckOpromPolicy = CurrentAmiOpromPolicy->CheckOpromPolicy;
    gAmiCsmOpromPolicy.ProcessOpRom = CurrentAmiOpromPolicy->ProcessOpRom;

    if (Event != NULL) {
        Status = gBS->CloseEvent (Event);
        ASSERT_EFI_ERROR (Status);
    }

    Status = gBS->ReinstallProtocolInterface (
                    Handle,
                    &gAmiCsmOpromPolicyProtocolGuid,
                    CurrentAmiOpromPolicy,
                    &NewAmiOpromPolicy
                    );
    ASSERT_EFI_ERROR (Status);
}

/**
    AMI_OPROM_POLICY_PROTOCOL installation notification callback. Uninstall the
    AMI_OPROM_POLICY_PROTOCOL and install a new one.
    
    @note The callback event must be closed prior to the protocol installation to avoid the
    recurrent callbacks.
    
    @param Event - event signaled by the DXE Core upon gAmiOpromPolicyProtocol installation
    @param Context - event context, not used
    
    @retval  VOID    
**/

VOID
OpromPolicyOverrideCallback (
    EFI_EVENT   Event,
    VOID        *Context
  )
{
    EFI_STATUS Status;
    AMI_OPROM_POLICY_PROTOCOL *CurrentAmiOpromPolicy = NULL;
    EFI_HANDLE Handle;
    UINTN HandleSize = sizeof (EFI_HANDLE);

    static AMI_OPROM_POLICY_PROTOCOL NewAmiOpromPolicy = {
        CheckUefiOpRomPolicy,
        (EXECUTE_OPROM_POLICY)ProcessOpRom
    };
    
    Status = gBS->LocateHandle (
                    ByRegisterNotify,
                    NULL,
                    gOpromPolicyOverrideRegistration,
                    &HandleSize,
                    &Handle
                    );
    if (EFI_ERROR (Status)) {
        Status = gBS->LocateHandle(
                        ByProtocol,
                        &gAmiOpromPolicyProtocolGuid,
                        NULL,
                        &HandleSize,
                        &Handle
                        );
        ASSERT_EFI_ERROR (Status);
    }


    Status = gBS->HandleProtocol (
                    Handle, 
                    &gAmiOpromPolicyProtocolGuid, 
                    (VOID **)&CurrentAmiOpromPolicy
                    );

    ASSERT_EFI_ERROR (Status);
    
    // Save the original CSM policy pointers for future use
    gAmiOpromPolicy.CheckUefiOpromPolicy = CurrentAmiOpromPolicy->CheckUefiOpromPolicy;
    gAmiOpromPolicy.ProcessOpRom = CurrentAmiOpromPolicy->ProcessOpRom;

    if (Event != NULL) {
        Status = gBS->CloseEvent (Event);
        ASSERT_EFI_ERROR (Status);
    }

    Status = gBS->ReinstallProtocolInterface (
                    Handle,
                    &gAmiOpromPolicyProtocolGuid,
                    CurrentAmiOpromPolicy,
                    &NewAmiOpromPolicy
                    );
    ASSERT_EFI_ERROR (Status);
}

/**
  Locate Protocol associated with the given device path.
  
  The function calls LocateDevicePath to find the closest handle that supports the protocol
  and then calls HandleProtocol to get protocol interface.
  
 @param[in,out]  DevicePath    In input, device path to match. 
                               On output the pointer is updated by the LocateDevicePath with the address
                               of the first unmatched node in the original device path.
 @param[in]      ProtocolGuid  GUID of the protocol to locate
 @param[out]     HandlePtr     Handle on which ProtocolGuid is installed.

 @return         Interface Pointer
**/
VOID*
LocateInterfaceFromDevPath (
    EFI_DEVICE_PATH_PROTOCOL    **DevicePath, 
    EFI_GUID                    *ProtocolGuid, 
    EFI_HANDLE                  *HandlePtr
  )
{
    VOID                        *Interface;
    EFI_HANDLE                  Handle;
    EFI_DEVICE_PATH_PROTOCOL    *TmpDevicePath = *DevicePath;

    if (EFI_ERROR (gBS->LocateDevicePath (ProtocolGuid, &TmpDevicePath, &Handle)))
        return NULL;
    if (EFI_ERROR(gBS->HandleProtocol (Handle, ProtocolGuid, &Interface))) 
        return NULL;
    *DevicePath = TmpDevicePath;
    if (HandlePtr != NULL) *HandlePtr = Handle;
    return Interface;
}

/**
    EFI_GRAPHICS_OUTPUT_PROTOCOL installation notification callback. It will detect primary 
    Video Device of the system 
    
    @note The callback event must be closed prior to the protocol installation to avoid the
    recurrent callbacks.
    
    @param Event - event signaled by the DXE Core upon gAmiOpromPolicyProtocol installation
    @param Context - event context, not used

    @retval  VOID    

**/
VOID 
GopProtocolCallback (
    EFI_EVENT   Event, 
    VOID        *Context
  )
{
    EFI_STATUS                      Status;
    EFI_DEVICE_PATH_PROTOCOL        *DevPath = NULL;
    EFI_PCI_IO_PROTOCOL             *PciIo = NULL;
    EFI_HANDLE                      GopHandle;
    UINTN                           HandleSize = sizeof (EFI_HANDLE);
    PCI_DEV_INFO                    *dev;
//    UINTN                           i;
//-------------------------------------    

    DEBUG ((DEBUG_INFO,"\nOptRomSetup: GOP Protocol Installed, EVENT=0x%X.\n",Event));

    Status = GetSetRomData (TRUE) ;
    ASSERT_EFI_ERROR (Status);

    Status = gBS->LocateHandle (
                    ByRegisterNotify,
                    NULL,
                    gGopProtocolRegistration,
                    &HandleSize,
                    &GopHandle);
    if (EFI_ERROR(Status)) {
        Status = gBS->LocateHandle (
                        ByProtocol,
                        &gEfiGraphicsOutputProtocolGuid,
                        NULL,
                        &HandleSize,
                        &GopHandle);
        ASSERT_EFI_ERROR (Status);
    }

    Status = gBS->HandleProtocol (
                    GopHandle, 
                    &gEfiDevicePathProtocolGuid, 
                    (VOID **)&DevPath );
    //GOP must have DP installed on it's handle or this is some kind of strange GOP... 
    if (EFI_ERROR(Status)) return;

    PciIo = (EFI_PCI_IO_PROTOCOL*)LocateInterfaceFromDevPath (&DevPath, &gEfiPciIoProtocolGuid, NULL);
    //If No PciIo Protocol mInstance or this is third party PCI_IO .. nothing we can do...
    if (PciIo == NULL || ((PCI_DEV_INFO*)PciIo)->Signature != AMI_PCI_SIG) return;
    //Do some more checking, for GOP it must be an ACPI_ADR_DEVICE_PATH node right after PCI Device Path Node.
    if (!IsDevicePathEnd(NextDevicePathNode(DevPath)) || !(DevPath->Type==ACPI_DEVICE_PATH && DevPath->SubType == ACPI_ADR_DP)) return;

    gGopFound = TRUE;

    dev = (PCI_DEV_INFO*)PciIo;
    if (dev->Signature!=AMI_PCI_SIG) return; //Not AMI PCI Bus Driver...


    //No Sdl Data - possible device behind the bridge...
    if (dev->AmiSdlPciDevData == NULL) {
        while (TRUE) {
           dev = dev->ParentBrg;
           //START: Coverity Issue :REVERSE_INULL
           if (dev == NULL) return;
          //END: Coverity Issue : REVERSE_INULL
           if (dev->AmiSdlPciDevData != NULL) break;
        }
        //must be slot only...
        //START: Coverity Issue :REVERSE_INULL
        if (dev->AmiSdlPciDevData->PciDevFlags.Bits.OnBoard) return;
        //END: Coverity Issue : REVERSE_INULL
    } 

    //try to check if PriVga index match this dev->SdlDevIndex;
    if (gRomSetupPtr->PriVgaIdx != dev->SdlDevIndex || 
            gRomSetupPtr->PriVgaItemValue != dev->AmiRomPolicy->CurrentPolicy ||
            gRomSetupPtr->PriVgaGroupValue != gSetupData.VideoOpRom) {
        gRomSetupPtr->PriVgaIdx = (UINT32)dev->SdlDevIndex;
        gRomSetupPtr->PriVgaItemValue = dev->AmiRomPolicy->CurrentPolicy;
        gRomSetupPtr->PriVgaGroupValue = gSetupData.VideoOpRom;
    }

/*    
    //Now check if policy has disabled Opt rom dispatch 
    //------------------------
    for(i=0; i<gRomSetupPtr->OptRomCount;i++){
        ROM_POLICY_VAR  *rp=&gRomSetupPtr->PolicyOption[i];
    //----------------------
        if(dev->SdlDevIndex==rp->SdlIdx && rp->Option==AMI_OPTION_ROM_POLICY_DISABLE){
            rp->Option=AMI_OPTION_ROM_POLICY_UEFI;
            if(DeviceClassPolicyOverride && gSetupData.CsmSupport){
                rp->Option=AMI_OPTION_ROM_POLICY_LEGACY;
            } 
            gRomSetupPtr->PriVgaItemValue=rp->Option;
            break;
        }
    }
*/
    if (Event != NULL) {
        Status = gBS->CloseEvent(Event);
        ASSERT_EFI_ERROR (Status);
        //if this function was invoked as callback we need to update Vga Status..
        Status = CheckRomPolicyVgaStatus (TRUE);
        ASSERT_EFI_ERROR (Status);
    }

}

