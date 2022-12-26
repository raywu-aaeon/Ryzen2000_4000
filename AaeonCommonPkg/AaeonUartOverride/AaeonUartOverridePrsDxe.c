//----------------------------------------------------------------------
//Include Files
//----------------------------------------------------------------------
#include <AmiDxeLib.h>
#include <GenericSio.h>
#include <Library/AmiSdlLib.h>
#include <token.h>
#include <Library/AmiSioDxeLib.h>
// Produced Protocols

// Consumed Protocols

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

///==================================================================================
///Global Variables
///==================================================================================
///UART IRQ Mask tells which interrupts we can use for UART devices
UINT16      gUartIrqMsk=0;
//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//Selects Resources by Priority settings.
//UINT8 *num number of descriptors in Dependency list;
/**
    This Function selects Possible Resource Settings List by Priority settings
    
    @param DfLst Pointer to the Possible Resource Settings Lists Collection 
    @param cmp Resource List Compatibility level 
    @param prf Resource List preference level 

    @retval Pointer to the Possible Resource Settings List

    @note See ACPI Spec DependentFn macro
**/
T_ITEM_LIST* EFIAPI GetPriResources(T_ITEM_LIST *DfLst, UINT8 cmp, UINT8 prf){
    UINTN               i;
    ASLRF_S_HDR         *ResHdr;
    EFI_ASL_DepFn       *DepFn;        
//-------------------------------------
    for(i=0; i<DfLst->ItemCount; i++){
        DepFn=DfLst->Items[i];
        ResHdr=(ASLRF_S_HDR*)DepFn->DepFn;
        if(ResHdr->Length==1) {    
            if(((ASLR_StartDependentFn*)DepFn->DepFn)->_PRI._CMP==cmp || 
                ((ASLR_StartDependentFn*)DepFn->DepFn)->_PRI._PRF==prf)
                return &DepFn->DepRes;
        }
    } 
    return NULL; 
}
//----------------------------------------------------------------------------
//
// Procedure:   GetIrqResource
//
// Description: This function is getting IRQ resource for target UART
//
// Input:       T_ITEM_LIST *ResLst - Resource list from target UART
//              
// Output:      None
//
// Notes:       
//----------------------------------------------------------------------------
ASLR_IRQ* EFIAPI GetIrqResource(T_ITEM_LIST *ResLst)
{
    UINTN               i;
    ASLR_IRQ            *IrqHdr;
    ASLRF_S_HDR         *ResHdr;

    for(i = 0; i< ResLst->ItemCount; i++){
        ResHdr = (ASLRF_S_HDR*)ResLst->Items[i];
        if (ResHdr->Type==ASLV_SMALL_RES && ResHdr->Name == ASLV_RT_IRQ)
        {
            TRACE((-1,"Get IRQ resource from %dst item in resource list", i));
            IrqHdr = (ASLR_IRQ*)ResHdr;
            return IrqHdr;
        }
    }

    TRACE((-1,"Get IRQ resource Failed"));
    return NULL;
}
//----------------------------------------------------------------------------
//
// Procedure:   ShareIrqOverride
//
// Description: This function is finding the IRQ owner then set the first 
//              IRQ sharing UART as owner and the other one as customer
//
// Input:       ASLR_IRQ - IRQ header for target UART
//              AMI_SDL_LOGICAL_DEV_INFO - logic device info for target UART
//              
// Output:      None
//
// Notes:       
//----------------------------------------------------------------------------
VOID EFIAPI ShareIrqOverride(ASLR_IRQ *IrqHdr, AMI_SDL_LOGICAL_DEV_INFO *LdSdlInfo)
{
    TRACE((-1,"gUartIrqMsk = %X; IrqHdr->_INT = %x", gUartIrqMsk, IrqHdr->_INT));

    //
    // Checking and setting the LDEVICE Flags of UART for dynamic IRQ sharing 
    // 
    if(gUartIrqMsk & IrqHdr->_INT)
    {
        if(LdSdlInfo->Flags == SIO_SHR_IRQ1)
        {                    
            //IRQ already has an owner so target UART is IRQ customer
            TRACE((-1,"IRQ->Customer;\n"));
        }
        else
        {
            //IRQ sharing UART should set to SIO_SHR_IRQ1
            TRACE((-1,"IRQ sharing UART should set to SIO_SHR_IRQ1, assign IRQ->Customer;\n"));
            LdSdlInfo->Flags = SIO_SHR_IRQ1;
        }
    }
    else
    {
        //IRQ doesn't has an owner, set gUartIrqMsk for recording IRQ was used
        gUartIrqMsk |= IrqHdr->_INT;
        if(LdSdlInfo->Flags == SIO_SHR_IRQ1)
        {
            //First IRQ sharing UART should set to SIO_SHR_NONE
            TRACE((-1,"First IRQ sharing UART should set to SIO_SHR_NONE, assign IRQ->Owner;\n"));
            LdSdlInfo->Flags = SIO_SHR_NONE;
        }
        else
        {
            //Target UART is IRQ owner
            TRACE((-1,"IRQ->Owner;\n"));
        }
    } 
}
//----------------------------------------------------------------------------
//
// Procedure:   AaeonUartOverridePrsInit
//
// Description: This function is getting all UART resource and setting the 
//              LEDVICE Flags for dynamic IRQ sharing
//
// Input:       EFI_HANDLE
//              EFI_SYSTEM_TABLE
//              
// Output:      EFI_STATUS
//
// Notes:       
//----------------------------------------------------------------------------
EFI_STATUS
EFIAPI
AaeonUartOverridePrsInit (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS                  Status = EFI_NOT_FOUND;
    UINTN                       i, j;
    AMI_SDL_SIO_CHIP_INFO       *SioChipSdlInfo;
    SIO_DEV2                    *Siodev;
    ASLR_IRQ                    *IrqHdr;
    T_ITEM_LIST                 *DevLst,*ResLst;

    InitAmiLib(ImageHandle, SystemTable);

    Status = AmiSdlInitBoardInfo();
    SioChipSdlInfo=&gSdlSioData->SioDev[0];
    gUartIrqMsk = 0;

    TRACE((-1,"AaeonUartOverridePrsInit: Get %d SIO Chip.\n", gSdlSioData->SioCount));
    for(j=0; j<gSdlSioData->SioCount; j++)
    {
        AMI_SDL_LOGICAL_DEV_INFO    *LdSdlInfo;
        TRACE((-1,"AaeonUartOverridePrsInit: Get %d LD on SIO Chip %d.\n", SioChipSdlInfo->LogicalDevCount, gSdlSioData->SioCount));
        //--------------------------------
        for(i=0; i<SioChipSdlInfo->LogicalDevCount; i++)
        {
            LdSdlInfo = &SioChipSdlInfo->LogicalDev[i];
            if(LdSdlInfo->Type == dsUART && LdSdlInfo->Flags != SIO_NO_RES)
            {
                TRACE((-1,"SIO_LD[%d]; AslName[%s]; Implemented = %d; FLAGS = %X.\n", i, LdSdlInfo->AslName, LdSdlInfo->Implemented, LdSdlInfo->Flags));

                Siodev = MallocZ(sizeof(SIO_DEV2));
                if(Siodev == NULL)
                {
                    Status = EFI_OUT_OF_RESOURCES;
                    ASSERT_EFI_ERROR(Status);
                    return Status;
                }
                //Get _PRS
                Siodev->DeviceInfo = LdSdlInfo;
                Status = SioDxeLibGetPrsFromAml(Siodev, NULL ,i);

                //Get priority resources
                DevLst = &Siodev->PRS;
                ResLst = GetPriResources(DevLst,0,0);

                //Get IRQ resource from priority resources
                IrqHdr = GetIrqResource(ResLst);

                //Set LDEVICE Flags of UART for dynamic IRQ sharing
                ShareIrqOverride(IrqHdr, LdSdlInfo);
            }
        }
        //Advance to the next SIO CHIP in Multiple Sio case.
        SioChipSdlInfo = (AMI_SDL_SIO_CHIP_INFO*)(LdSdlInfo + 1);
    }

    return Status;
}