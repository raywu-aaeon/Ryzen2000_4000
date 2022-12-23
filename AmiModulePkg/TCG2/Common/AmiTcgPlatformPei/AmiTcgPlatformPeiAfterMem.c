//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TcgNext/Common/AmiTcgPlatform/AmiTcgPlatformPeiAfterMem.c 1     10/08/13 12:04p Fredericko $
//
// $Revision: 1 $
//
// $Date: 10/08/13 12:04p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TcgNext/Common/AmiTcgPlatform/AmiTcgPlatformPeiAfterMem.c $
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:	AmiTcgPlatformPeiAfterMem.c
//
// Description:	Function file for AmiTcgPlatformPeiAfterMem
//
//<AMI_FHDR_END>
//*************************************************************************
#include <Efi.h>
#include <Pei.h>
#include <AmiTcg/TcgCommon12.h>
#include <AmiTcg/TCGMisc.h>
#include <Ppi/TcgTcmService.h>
#include <Ppi/TcgService.h>
#include <Ppi/TpmDevice.h>
#include "Ppi/CpuIo.h"
#include "Ppi/LoadFile.h"
#include <AmiTcg/AmiTcgPlatformPei.h>
#include <Ppi/AmiTcgPlatformPpi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#if defined (TCGRomLayout_SUPPORT) && (TCGRomLayout_SUPPORT!=0)
#include <Library/AmiRomLayoutLib.h>
#include <RomLayout.h>
#endif
#include <Library/MemoryAllocationLib.h>
#include <Library/PerformanceLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeCoffLib.h>
// NIST 800-155
#include <Guid/HobList.h>
#include <AmiHobs.h>
#include <Token.h>
#include <AmiTcg/AmiTpmStatusCodes.h>
#include <Guid/AmiTcgGuidIncludes.h>
#include <Library/HobLib.h>
#include <Library/PrintLib.h>
#if defined CORE_COMBINED_VERSION && CORE_COMBINED_VERSION >= 0x50015
#include <Guid/MigratedFvInfo.h>
#endif

#if defined (AmiTrustedFv_Support) && (AmiTrustedFv_Support == 1)
#include <Ppi/AmiFvDigest.h>
#endif
// NIST 800-155

//**********************************************************************
//                  Links
//**********************************************************************
extern MEASURE_CRTM_VERSION_PEI_FUNC_PTR  MEASURE_CRTM_VERSION_PEI_FUNCTION;
MEASURE_CRTM_VERSION_PEI_FUNC_PTR *MeasureCRTMVersionFuncPtr = MEASURE_CRTM_VERSION_PEI_FUNCTION;

extern EFI_GUID gTcgPeiPolicyGuid;
extern EFI_GUID gAmiTcgPlatformPpiAfterMem;
extern EFI_GUID PeiMpFileGuid;
extern EFI_GUID gMpTcmFileGuid;
extern TCM_PC_REGISTERS_PTR      TcmReg;

EFI_GUID gEdkiiMigratedFvInfoGuid = { 0xc1ab12f7, 0x74aa, 0x408d, { 0xa2, 0xf4, 0xc6, 0xce, 0xfd, 0x17, 0x98, 0x71 } };

    
//NIST-155

// ->>>>>>>>>>>>>>>> NIST 800-155
void printbuffer(UINT8 *Buffer, UINTN BufferSize)
{
    UINTN i=0; UINTN j=0;
                
    for(i=0; i<BufferSize; i++){

        if(i%16 == 0){
            DEBUG((DEBUG_INFO,"\n"));
            DEBUG((DEBUG_INFO,"%04x :", j));
            j+=1;
        }
        DEBUG((DEBUG_INFO,"%02x ", Buffer[i]));
    }
    DEBUG((DEBUG_INFO,"\n"));
    
}


#pragma pack(push,1)

typedef struct{

    UINT64   Base;
    UINTN   Size;
}HASHDATA;
#pragma pack(pop)
EFI_STATUS FindAndMeasureFwVols(EFI_PEI_SERVICES **PeiServices);


EFI_STATUS
TcgPeiSimpleExtend(
   PEI_TCG_PPI   *TcgPpi,  
   EFI_PEI_SERVICES **ps,
   IN TPM_PCRINDEX PCRIndex,
   IN TCG_DIGEST   *Digest,
   OUT TCG_DIGEST  *NewPCRValue )
{
    UINT8   *cmd;
    UINT8   *BufferPtr=NULL;
    UINT32   BufferSize=0;
    EFI_STATUS Status;
    UINT8   *ret;

    BufferSize = sizeof (TPM_1_2_CMD_HEADER) + sizeof (PCRIndex) + TPM_SHA1_160_HASH_LEN;
    Status = (*ps)->AllocatePool((CONST EFI_PEI_SERVICES **)ps, BufferSize, (void **)&cmd);
    if(EFI_ERROR(Status))return Status;
    
    Status = (*ps)->AllocatePool((CONST EFI_PEI_SERVICES **)ps, BufferSize, (void **)&ret);
    if(EFI_ERROR(Status))return Status;
    
    (*ps)->SetMem(cmd, BufferSize, 0);
        
    BufferPtr = cmd;
    ((TPM_1_2_CMD_HEADER *)cmd)->Tag       = SwapBytes16( TPM_TAG_RQU_COMMAND );
    ((TPM_1_2_CMD_HEADER *)cmd)->ParamSize = SwapBytes32(BufferSize);
    ((TPM_1_2_CMD_HEADER *)cmd)->Ordinal   = SwapBytes32( TPM_ORD_Extend );
    
    BufferPtr += sizeof(TPM_1_2_CMD_HEADER);
    
    PCRIndex = SwapBytes32(PCRIndex);
    
    (*ps)->CopyMem(BufferPtr, &PCRIndex, sizeof(TPM_PCRINDEX));
    
    BufferPtr+= sizeof(TPM_PCRINDEX);
    
    (*ps)->CopyMem(BufferPtr, Digest->digest, TPM_SHA1_160_HASH_LEN);
    
    //printbuffer(cmd, BufferSize);
    
    Status = TcgPpi->TCGPassThroughToTpm(TcgPpi,
                                ps,
                                BufferSize,
                                cmd,
                                BufferSize,
                                ret);
    
    DEBUG ((DEBUG_INFO, "Status = %r\n", Status));
    //printbuffer(ret, BufferSize);
    
    return Status;
}
    


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   MeasureLogDxeFwVol
//
// Description: Hashes FVMain Volume
//
//
// Input:       IN      EFI_PEI_SERVICES          **PeiServices,
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
MeasureLogDxeFwVol(
    IN  CONST EFI_PEI_SERVICES  **PeiServices,
    IN  FwVolHob                *TpmFwVolHob,
    IN  PEI_TPM_PPI             *TpmPpi,
    IN  PEI_TCG_PPI             *TcgPpi
)
{
    EFI_STATUS                        Status = EFI_SUCCESS;
    SHA1_CTX                          Sha1Ctx;
    PEI_EFI_BLOB_EVENT                *TcgEvent = NULL;
    UINT32                            EventNumber;
    UINT32                            i = 0;
    UINT32                            FwVolHobCount;
    TCG_DIGEST                        Sha1Digest;
    EFI_PHYSICAL_ADDRESS              FvBase;
    UINTN                             FvLength=0;
#if defined CORE_COMBINED_VERSION && CORE_COMBINED_VERSION >= 0x50015
    EFI_PEI_HOB_POINTERS              Hob;
    EDKII_MIGRATED_FV_INFO            *MigratedFvInfo;
    BOOLEAN                           MatchFound=FALSE;
#endif

    DEBUG(( DEBUG_INFO, "[%d] Enter MeasureLogDxeFwVol\n", __LINE__));

    Status = (*PeiServices)->AllocatePool( PeiServices,
                                           sizeof(PEI_EFI_BLOB_EVENT),
                                           (void **)&TcgEvent);
    if (EFI_ERROR (Status))
    {
        return Status;
    }

    FwVolHobCount = TpmFwVolHob->Count;

    DEBUG ((DEBUG_INFO, "FwVolHobCount = %x \n", FwVolHobCount));
    for(i=0; i< FwVolHobCount; i++)
    {
        TcgEvent->Header.PCRIndex      = AMI_PCRi_CRTM_AND_POST_BIOS;
        TcgEvent->Header.EventType     = EV_EFI_PLATFORM_FIRMWARE_BLOB;
        TcgEvent->Header.EventDataSize = sizeof (EFI_PLATFORM_FIRMWARE_BLOB);
        TcgEvent->Event.BlobBase = TpmFwVolHob[i].baseAddress;
        TcgEvent->Event.BlobLength = (UINT64)TpmFwVolHob[i].Size;
        DEBUG(( DEBUG_INFO, "[%d] TpmFwVolHob[i].baseAddress = %x \n", __LINE__, TpmFwVolHob[i].baseAddress));
#if defined CORE_COMBINED_VERSION && CORE_COMBINED_VERSION >= 0x50015
        Hob.Raw  = GetFirstGuidHob (&gEdkiiMigratedFvInfoGuid);
        while (Hob.Raw != NULL) {
            MigratedFvInfo = GET_GUID_HOB_DATA (Hob);
            DEBUG(( DEBUG_INFO, "[%d] MigratedFvInfo->FvNewBase = %x and MigratedFvInfo->FvLength = %x \n",
                    __LINE__, MigratedFvInfo->FvNewBase, MigratedFvInfo->FvLength));
            if ((MigratedFvInfo->FvOrgBase == (UINT32) (UINTN)TpmFwVolHob[i].baseAddress) && 
                                        (MigratedFvInfo->FvLength == (u32)TpmFwVolHob[i].Size)) {
              DEBUG(( DEBUG_INFO, "[%d] Fv match found \n",__LINE__));
              MatchFound = TRUE;
              break;
            }
            Hob.Raw = GET_NEXT_HOB (Hob);
            Hob.Raw = GetNextGuidHob (&gEdkiiMigratedFvInfoGuid, Hob.Raw);
        }
        
        FvBase = MigratedFvInfo->FvNewBase;
        FvLength = MigratedFvInfo->FvLength;
#else
        FvBase  = TpmFwVolHob[i].baseAddress;
        FvLength = TpmFwVolHob[i].Size;
#endif
        
#if defined CORE_COMBINED_VERSION && CORE_COMBINED_VERSION >= 0x50015        
    if(MatchFound == FALSE){
        continue;
    }
        
    MatchFound = FALSE; //reset for next loop
#endif
                
    SHA1Init( &Sha1Ctx );
        
    SHA1Update( &Sha1Ctx,  (unsigned char *)(UINTN)FvBase, FvLength);
        
    SHA1Final(Sha1Digest.digest, &Sha1Ctx);
       
    (*PeiServices)->CopyMem(TcgEvent->Header.Digest.digest, Sha1Digest.digest, TPM_SHA1_160_HASH_LEN);

    TpmPpi->Init(TpmPpi, (EFI_PEI_SERVICES **)PeiServices);

    Status = TcgPeiSimpleExtend(
                  TcgPpi,
                  (EFI_PEI_SERVICES **)PeiServices,
                  TcgEvent->Header.PCRIndex,
                  &TcgEvent->Header.Digest,
                  &Sha1Digest );

    TpmPpi->Close(TpmPpi, (EFI_PEI_SERVICES **)PeiServices);

    if (EFI_ERROR (Status))
    {
        return Status;
    }

    Status = TcgPpi->TCGLogEvent( TcgPpi,
                                  (EFI_PEI_SERVICES **)PeiServices,
                                  (TCG_PCR_EVENT *)TcgEvent,
                                  &EventNumber);
    }
    DEBUG(( DEBUG_INFO, "MeasureLogDxeFwVol - %r\n", Status));

    TpmPeiReportStatusCodeEx(EFI_PROGRESS_CODE, AMI_SPECIFIC_BIOS_FWVOL_MEASURED | EFI_SOFTWARE_PEI_MODULE,
                             0, NULL, &ExtendedDataGuid, &TcgEvent->Event, sizeof (PEI_EFI_BLOB_EVENT));
    TpmPeiReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_BIOS_FWVOL_MEASURED | EFI_SOFTWARE_PEI_MODULE);

    return Status;
}



#if defined (TCGRomLayout_SUPPORT) && (TCGRomLayout_SUPPORT!=0)
// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: GetRomLayout
//
// Description: 
//
// Input:
//  OUT UINT8 **pRomLayout
//  OUT UINTN *Size
//
// Output:      EFI_STATUS
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>
EFI_STATUS GetRomArea(
  IN OUT AMI_ROM_AREA **pRomLayout,
  IN OUT UINTN *Size,
  IN  AMI_ROM_AREA *First
)
{             
  if(pRomLayout == NULL)return EFI_INVALID_PARAMETER;
  if(First == NULL){
      *pRomLayout = AmiGetFirstRomArea();
      if(*pRomLayout == NULL)return EFI_NOT_FOUND;
  }else{
      *pRomLayout = AmiGetNextRomArea(First);
      if(*pRomLayout == NULL)return EFI_NOT_FOUND;
  }
  
  *Size = (*pRomLayout)->Size;
  return EFI_SUCCESS;
}
#endif
  
#ifndef ROM_AREA_TCG_MEASURED
// Platform Firmware Volume that either contains or 
// measures the EFI Boot Services and EFI Run Time Services; (code measured into TPM PCR[0])
#define ROM_AREA_TCG_MEASURED     0x000008000  
#endif

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   InternalPeiBuildHobGuid
//
// Description: Internal abstracted function to create a Hob
//
// Input:       IN  EFI_PEI_SERVICES  **PeiServices,
//              IN  EFI_GUID          *Guid,
//              IN  UINTN             DataLength,
//              OUT VOID              **Hob
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS InternalPeiBuildHobGuid(
    IN EFI_PEI_SERVICES **PeiServices,
    IN EFI_GUID         *Guid,
    IN UINTN            DataLength,
    OUT VOID            **Hob )
{
    EFI_STATUS Status;

    Status = (*PeiServices)->CreateHob(
        (CONST EFI_PEI_SERVICES **)PeiServices,
        EFI_HOB_TYPE_GUID_EXTENSION,
        (UINT16) ( sizeof (EFI_HOB_GUID_TYPE) + DataLength ),
        Hob
        );

    if ( EFI_ERROR( Status ))
    {
        DEBUG((DEBUG_INFO, "Failed to create TCG/TPM Hob Status = %r \n", Status));
        return Status;
    }
    
    DEBUG((DEBUG_INFO, "Hob created \n")); 
    ((EFI_HOB_GUID_TYPE*)(*Hob))->Name = *Guid;

    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ImageRead (
  IN     VOID    *FileHandle,
  IN     UINTN   FileOffset,
  IN OUT UINTN   *ReadSize,
  OUT    VOID    *Buffer
  )
{
  CopyMem (Buffer, (UINT8 *)((UINTN) FileHandle + FileOffset), *ReadSize);
  return EFI_SUCCESS;
}


#if defined (AmiTrustedFv_Support) && (AmiTrustedFv_Support == 1)
EFI_STATUS Tpm12UpdateLogWithVerifiedHash (CONST EFI_PEI_SERVICES  **PeiServices,
                                      AMI_FV_DIGEST_PPI *VerifiedHashDigestPpi,
                                      PEI_TCG_PPI             *TcgPpi)
{
    EFI_STATUS Status = EFI_NOT_FOUND;
    PEI_EFI_BLOB_EVENT              TcgEvent;
    UINT32                          EventNum;
    UINTN                           i = 0;
    
    
    DEBUG(( DEBUG_INFO, "UpdateLogWithVerifiedHash \n"));
    
    if((PeiServices == NULL) || (VerifiedHashDigestPpi == NULL)
            || TcgPpi == NULL ){
        return EFI_INVALID_PARAMETER;
    }
    
    TcgEvent.Header.PCRIndex      = AMI_PCRi_CRTM_AND_POST_BIOS;
    TcgEvent.Header.EventType     = EV_POST_CODE;
    TcgEvent.Header.EventDataSize = sizeof (EFI_TCG_EV_POST_CODE);
#if (AMI_TRUSTED_FV_MODULE_REVISION >= 5)
    for(i=0; i<VerifiedHashDigestPpi->HashElemCnt; i++){
        DEBUG(( DEBUG_INFO, "VerifiedHashDigestPpi->AddrList[%d] = %x \n", i,VerifiedHashDigestPpi->AddrList[i]));
        DEBUG(( DEBUG_INFO, "VerifiedHashDigestPpi->LenList[%d] = %x \n", i,VerifiedHashDigestPpi->LenList[i]));
        TcgEvent.Event.BlobBase = (EFI_PHYSICAL_ADDRESS)VerifiedHashDigestPpi->AddrList[i];
        TcgEvent.Event.BlobLength = (UINT64)VerifiedHashDigestPpi->LenList[i];
        printbuffer((UINT8 *)VerifiedHashDigestPpi->HashList[i],VerifiedHashDigestPpi->HashSize);
        Status = TcgPpi->TCGHashLogExtendEvent(TcgPpi, (EFI_PEI_SERVICES  **)PeiServices, VerifiedHashDigestPpi->FvHash, 
                                            VerifiedHashDigestPpi->HashSize, (TCG_PCR_EVENT *)&TcgEvent, &EventNum );
        if(EFI_ERROR(Status))
            break;
    }
#else
    DEBUG(( DEBUG_INFO, "VerifiedHashDigestPpi->AddrList[0] = %x \n", VerifiedHashDigestPpi->AddrList[0]));
    TcgEvent.Event.BlobBase = (EFI_PHYSICAL_ADDRESS)VerifiedHashDigestPpi->AddrList[0];
    TcgEvent.Event.BlobLength = 0;
    for(i=0; i<VerifiedHashDigestPpi->HashElemCnt; i++){
        DEBUG(( DEBUG_INFO, "VerifiedHashDigestPpi->LenList = %x \n", VerifiedHashDigestPpi->LenList[i]));
        TcgEvent.Event.PostCodeLength += (UINT64)VerifiedHashDigestPpi->LenList[i];
    }
    
    DEBUG(( DEBUG_INFO, "EventData.BlobLength = %x \n", TcgEvent.Event.PostCodeLength));
    printbuffer(VerifiedHashDigestPpi->FvHash,VerifiedHashDigestPpi->HashSize);
    
    Status = TcgPpi->TCGHashLogExtendEvent(TcgPpi, (EFI_PEI_SERVICES  **)PeiServices, VerifiedHashDigestPpi->FvHash, 
                                        VerifiedHashDigestPpi->HashSize, (TCG_PCR_EVENT *)&TcgEvent, &EventNum );

    printbuffer(VerifiedHashDigestPpi->FvHash,VerifiedHashDigestPpi->HashSize);
    DEBUG(( DEBUG_INFO, "UpdateLogWithVerifiedHash - %r\n", Status));
#endif
    return Status;
}

EFI_STATUS
EFIAPI
Tpm12EndOfPeiSignalPpiNotifyCallback (
        IN EFI_PEI_SERVICES           **PeiServices,
        IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
        IN VOID                       *Ppi
)
{
    AMI_FV_DIGEST_PPI               *VerifiedHashDigestPpi = NULL;
    EFI_GUID     gAmiFvDigestPpiguid = AMI_FV_DIGEST_PPI_GUID;
    PEI_TPM_PPI             *TpmPpi         = NULL;         
    PEI_TCG_PPI             *TcgPpi         = NULL;
    EFI_STATUS              Status= EFI_NOT_FOUND;
    
    Status = LocateTcgPpi((EFI_PEI_SERVICES **)PeiServices, &TpmPpi, &TcgPpi);
    if(EFI_ERROR(Status)){
      DEBUG((DEBUG_ERROR, "\n LocateTcgPpi is failed \n"));
      return EFI_NOT_FOUND;
    }
    
    Status = (*PeiServices)->LocatePpi((CONST EFI_PEI_SERVICES  **)PeiServices,
                                    &gAmiFvDigestPpiguid,
                                    0, NULL,
                                    (void **)&VerifiedHashDigestPpi);
    
    if(!EFI_ERROR(Status) && (VerifiedHashDigestPpi != NULL)){
        Status = Tpm12UpdateLogWithVerifiedHash((CONST EFI_PEI_SERVICES  **)PeiServices, VerifiedHashDigestPpi,
                                                TcgPpi);
        return Status;
    }else{
        
        Status = FindAndMeasureFwVols(PeiServices);
        if ( EFI_ERROR( Status ))
        {
            DEBUG((DEBUG_ERROR, "Error: Failure %d %a Status = %r\n", __LINE__, __FUNCTION__, Status));
        }
    }

    return Status;
}


EFI_PEI_NOTIFY_DESCRIPTOR mTpm12EndOfPeiSignalPpiNotifyList[] = {
    {
           (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
            &gEfiEndOfPeiSignalPpiGuid,
            Tpm12EndOfPeiSignalPpiNotifyCallback
    }
};

#endif
   
//*******************************************************************************
//<AMI_PHDR_START>
//
// Procedure:   FindAndMeasureDxeCore
//
// Description: 
//
// Input:      
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//******************************************************************************
EFI_STATUS FindAndMeasureFwVols(EFI_PEI_SERVICES **PeiServices)
{

   EFI_STATUS              Status;
   PEI_TPM_PPI             *TpmPpi         = NULL;         
   PEI_TCG_PPI             *TcgPpi         = NULL;
   TCG_PLATFORM_SETUP_INTERFACE    *TcgPeiPolicy=NULL;
   TCG_CONFIGURATION               ConfigFlags;
#if defined (TCGRomLayout_SUPPORT) && (TCGRomLayout_SUPPORT!=0)
   AMI_ROM_AREA                    *RomArea = NULL;
   UINTN                           RomArea_size;
#endif
   FwVolHob                        *TpmFwVolHob = NULL;
   FwVolHob                        FwVolHobArray[10];
   UINTN                           i=0;
   UINTN                            Count=0;
   EFI_HOB_GUID_TYPE               *VolHob = NULL;

   
   //locate the PeiTree Protocol
    Status = LocateTcgPpi((EFI_PEI_SERVICES **)PeiServices, &TpmPpi, &TcgPpi);
    if(EFI_ERROR(Status)){
      DEBUG((DEBUG_ERROR, "\n LocateTcgPpi is failed \n"));
      return EFI_NOT_FOUND;
    }
   
    //create RomAreaOHob for Measurement of FV in Dxemain
#if defined (TCGRomLayout_SUPPORT) && (TCGRomLayout_SUPPORT!=0)
    Status = GetRomArea(&RomArea,&RomArea_size, NULL);
    if( (!EFI_ERROR(Status))&&(RomArea != NULL) )
    {
        for(i=0; RomArea!=NULL; i++)
        {
#if defined (TCGNIST_03_OR_NEWER) && (TCGNIST_03_OR_NEWER!=0)
            if(((RomArea->Attributes & AMI_ROM_AREA_MEASURED) == AMI_ROM_AREA_MEASURED)||
               ((RomArea->Attributes & AMI_ROM_AREA_FV_ACCESS_ATTRIBUTES) != 0
               &&(RomArea->Attributes & (AMI_ROM_AREA_FV_PEI | AMI_ROM_AREA_VITAL)) != (AMI_ROM_AREA_FV_PEI | AMI_ROM_AREA_VITAL)))
#else
            if(((RomArea->Attributes & ROM_AREA_FV_SIGNED) && (RomArea->Attributes & ROM_AREA_TCG_MEASURED)) ||
                (((RomArea->Attributes & (ROM_AREA_FV_PEI+ROM_AREA_FV_DXE)) &&
                !(RomArea->Attributes & ROM_AREA_VITAL) )) )  // Attributes)
#endif
            {
                
                FwVolHobArray[Count].baseAddress = RomArea->Address;  
                FwVolHobArray[Count].Size        = RomArea->Size;  
               DEBUG ((DEBUG_INFO, "RomArea->Address = %x \n", RomArea->Address));
               DEBUG ((DEBUG_INFO, "RomArea->Size = %x \n",RomArea->Size));
                Count +=1;
            }
            
            GetRomArea(&RomArea,&RomArea_size, RomArea);
        }
    }
    else
    {
        FwVolHobArray[Count].baseAddress = FV_MAIN_BASE;
        FwVolHobArray[Count].Size = FV_MAIN_SIZE;
        Count+=1;
    }
#else
    FwVolHobArray[Count].baseAddress = FV_MAIN_BASE;
    FwVolHobArray[Count].Size = FV_MAIN_SIZE;
    Count+=1;
#endif
    
    Status = InternalPeiBuildHobGuid(PeiServices, &amiFVhoblistguid,
                              (sizeof(FwVolHob)*Count),  (void **)&VolHob);
    if (EFI_ERROR (Status))
    {
        return Status;
    }
    
    Status = (*PeiServices)->LocatePpi(
                    (CONST EFI_PEI_SERVICES **)PeiServices,
                     &gTcgPeiPolicyGuid,
                     0, NULL,
                     (void **)&TcgPeiPolicy);
    
    if(EFI_ERROR(Status)){
        return EFI_NOT_FOUND;  
    }
           
    Status = TcgPeiPolicy->getTcgPeiPolicy(PeiServices, &ConfigFlags);
    if(EFI_ERROR(Status))return Status;
    
    TpmFwVolHob = (FwVolHob*)(VolHob + 1);
    for(i=0; i<Count; i++){
       
       if(i==0){
           TpmFwVolHob->Size = FwVolHobArray[i].Size;
           TpmFwVolHob->baseAddress = FwVolHobArray[i].baseAddress;
           TpmFwVolHob->Count = Count;
           // For TPM 1.2, the Tcg2SpecVersion should be 0
           TpmFwVolHob->Tcg2SpecVersion = 0;
       }else{
           TpmFwVolHob->Size = FwVolHobArray[i].Size;
           TpmFwVolHob->baseAddress = FwVolHobArray[i].baseAddress;
           TpmFwVolHob->Count = 0;
           TpmFwVolHob->Tcg2SpecVersion = 0;
       }
       
       DEBUG ((DEBUG_INFO, "TpmFwVolHob->Size = %x \n", TpmFwVolHob->Size));
       DEBUG ((DEBUG_INFO, "TpmFwVolHob->baseAddress = %x \n",TpmFwVolHob->baseAddress));
       DEBUG ((DEBUG_INFO, "TpmFwVolHob->Tcg2SpecVersion = %x \n",TpmFwVolHob->Tcg2SpecVersion));
       DEBUG ((DEBUG_INFO, "TpmFwVolHob address = %x \n", TpmFwVolHob));
       TpmFwVolHob+=1;
    }
                         
    DEBUG ((DEBUG_INFO, "Calling MeasureLogDxeFwVol \n"));
      
    MeasureLogDxeFwVol(   
            (CONST EFI_PEI_SERVICES **)PeiServices,
            ((FwVolHob*)(VolHob + 1)),
            TpmPpi,
            TcgPpi
            );
  
    return Status;
}



//NIST-155    
    
    
    
    

EFI_STATUS MeasureNISTManifest(
        IN EFI_PEI_SERVICES **ps, 
        IN PEI_TCG_PPI      *tcg );


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   VerifyTcgVariables
//
// Description: Function to check whether we need to reset TCG variables
//
//
// Input:       EFI_PEI_SERVICES **PeiServices
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS VerifyTcgVariables(
    EFI_PEI_SERVICES **PeiServices )
{
    AMI_TCG_PEI_FUNCTION_OVERRIDE_PPI       *VerifyVarOverride;
    EFI_STATUS						Status;

    
    Status = (*PeiServices)->LocatePpi(
                   (CONST EFI_PEI_SERVICES    **)PeiServices,
                    &AmiVerifyTcgVariablesGuid,
                    0, NULL,
                    (void **)&VerifyVarOverride);

    if(!EFI_ERROR(Status)){
        return (VerifyVarOverride->Function(PeiServices));
    }

    return EFI_SUCCESS;
}



TPM_Capabilities_PermanentFlag INTTCGPEI_GETCAP( EFI_PEI_SERVICES **PeiServices );
//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   Set_TPMPhysicalPresence
//
// Description: Sets TPM physical Presence
//
//
// Input:       IN      EFI_PEI_SERVICES          **PeiServices,
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS Set_TPMPhysicalPresence(
    IN EFI_PEI_SERVICES **PeiServices )
{
    EFI_STATUS                      Status;
    TPM_RSP_COMMAND_HDR             RspHdr;
    TPM_Capabilities_PermanentFlag  Cap;

    AMI_TCG_PEI_FUNCTION_OVERRIDE_PPI   *SetPhysicalOverride;
    struct
    {
        TPM_RQU_COMMAND_HDR CmdHdr;
        UINT8               Data[0x4];
    } cmd;

    UINT16        physical_CMD_on = SwapBytes16(TPM_PHYSICAL_PRESENCE_CMD_ENABLE );
    UINT16        physical_on     = SwapBytes16(TPM_PHYSICAL_PRESENCE_PRESENT );
    PEI_TPM_PPI   *TpmPpi         = NULL;         
    PEI_TCG_PPI   *TcgPpi         = NULL;


    Status = (*PeiServices)->LocatePpi(
                    (CONST EFI_PEI_SERVICES    **)PeiServices,
                    &AmiSetPhysicalPresenceGuid,
                    0, NULL,
                    (void **)&SetPhysicalOverride);

    if(!EFI_ERROR(Status)){
        return (SetPhysicalOverride->Function(PeiServices));
    }
    
    if(IsTcmSupportType()){
    	return EFI_SUCCESS;
    }


    cmd.CmdHdr.tag =     SwapBytes16( TPM_TAG_RQU_COMMAND );
    cmd.CmdHdr.paramSize = SwapBytes32((UINT32)( sizeof (cmd.CmdHdr)
                           + sizeof(TPM_PHYSICAL_PRESENCE)));

    cmd.CmdHdr.ordinal = SwapBytes32(TSC_ORD_PhysicalPresence );

    if ( Lock_TPMPhysicalPresence( PeiServices ))
    {
        physical_on = SwapBytes16( TPM_PHYSICAL_PRESENCE_LOCK );
    }else{
		// When TCM plug into the board, we nee to skip the TPM selftest command.
        if( !IsTcmSupportType() )
        {
            Status = ContinueTPMSelfTest( PeiServices );
            if(EFI_ERROR(Status)){
                DEBUG((DEBUG_INFO, "\n ContinueTpmSelftest Status = %r \n", Status));
            }
        }
    }

    Status = LocateTcgPpi(PeiServices, &TpmPpi, &TcgPpi);
    if(EFI_ERROR(Status)){
        DEBUG((DEBUG_INFO, "\n ContinueTpmSelftest Status = %r \n", Status));
    }
    
    if(EFI_ERROR(Status))return EFI_NOT_FOUND;
    Cap = INTTCGPEI_GETCAP(PeiServices);
    if( 1 == Cap.physicalPresenceLifetimeLock )
    {
        Status = TpmPpi->Init( TpmPpi, PeiServices );
        if ( EFI_ERROR( Status ))
        {
            return Status;
        }

        CopyMem( cmd.Data, &physical_on, sizeof(TPM_PHYSICAL_PRESENCE));

        Status =TcgPpi->TCGPassThroughToTpm(
                    TcgPpi,
                    PeiServices,
                    (sizeof (cmd.CmdHdr) + sizeof(TPM_PHYSICAL_PRESENCE)),
                    (UINT8*)&cmd,
                    sizeof (RspHdr),
                    (UINT8*)&RspHdr );
		if (EFI_ERROR (Status))
        {
            DEBUG((DEBUG_INFO,"TCGPassThroughToTpm Status = %r\n", Status));
        }

        Status = TpmPpi->Close( TpmPpi, PeiServices );
        if ( EFI_ERROR( Status ))
        {
            return Status;
        }
        return EFI_SUCCESS;
    }

    Status = TpmPpi->Init( TpmPpi, PeiServices );
    if ( EFI_ERROR( Status ))
    {
        return Status;
    }

    CopyMem( cmd.Data, &physical_CMD_on, sizeof(TPM_PHYSICAL_PRESENCE));

    Status =TcgPpi->TCGPassThroughToTpm(
        TcgPpi,
        PeiServices,
        (sizeof (cmd.CmdHdr) + sizeof(TPM_PHYSICAL_PRESENCE)),
        (UINT8*)&cmd,
        sizeof (RspHdr),
        (UINT8*)&RspHdr );

    CopyMem( cmd.Data, &physical_on, sizeof(TPM_PHYSICAL_PRESENCE));

    Status = TcgPpi->TCGPassThroughToTpm(
        TcgPpi,
        PeiServices,
        (sizeof (cmd.CmdHdr) + sizeof(TPM_PHYSICAL_PRESENCE)),
        (UINT8*)&cmd,
        sizeof (RspHdr),
        (UINT8*)&RspHdr );

    Status = TpmPpi->Close( TpmPpi, PeiServices );
    if ( EFI_ERROR( Status ))
    {
        return Status;
    }

    if ( RspHdr.returnCode != 0 )
    {
        TpmPeiReportStatusCode(EFI_ERROR_CODE|EFI_ERROR_MAJOR, AMI_SPECIFIC_TPM_1_2_PP_LOCK_CMD_SENT | EFI_SOFTWARE_PEI_MODULE);   
        return EFI_DEVICE_ERROR;
    }
    
    if( physical_on == SwapBytes16( TPM_PHYSICAL_PRESENCE_LOCK )){
        TpmPeiReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_1_2_PP_LOCK_CMD_SENT | EFI_SOFTWARE_PEI_MODULE);
    }
    
    return EFI_SUCCESS;
}





//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   Set_TCMPhysicalPresence
//
// Description: Sets TCM physical Presence
//
//
// Input:       IN      EFI_PEI_SERVICES          **PeiServices,
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS Set_TCMPhysicalPresence(
    IN EFI_PEI_SERVICES **PeiServices )
{
    EFI_STATUS               Status;
    TPM_RSP_COMMAND_HDR      RspHdr;
    UINT16  physical_CMD_on = SwapBytes16(TPM_PHYSICAL_PRESENCE_CMD_ENABLE );
    UINT16  physical_on     = SwapBytes16(TPM_PHYSICAL_PRESENCE_PRESENT );
    PEI_TCM_PPI     *TcmPpi = NULL;
    struct
    {
        TPM_RQU_COMMAND_HDR CmdHdr;
        UINT8               Data[0x4];
    } cmd;



    cmd.CmdHdr.tag =     SwapBytes16( TPM_TAG_RQU_COMMAND );
    cmd.CmdHdr.paramSize = SwapBytes32((UINT32)( sizeof (cmd.CmdHdr)
                           + sizeof(TPM_PHYSICAL_PRESENCE)));

    cmd.CmdHdr.ordinal = SwapBytes32(TCM_TSC_ORD_PhysicalPresence );
    

    if ( Lock_TPMPhysicalPresence( PeiServices ))
    {
        physical_on = SwapBytes16( TPM_PHYSICAL_PRESENCE_LOCK );
    }

    Status = LocateTcmPpi(PeiServices, &TcmPpi);
    ASSERT_EFI_ERROR(  Status );

    CopyMem( cmd.Data, &physical_CMD_on, sizeof(TPM_PHYSICAL_PRESENCE));

    Status = TcmPpi->TcmLibPassThrough(
                        TcmReg,
                        (UINT8*)&cmd,
                        (sizeof (cmd.CmdHdr) + sizeof(TPM_PHYSICAL_PRESENCE)),
                        (UINT8*)&RspHdr,
                        sizeof (RspHdr));

    CopyMem( cmd.Data, &physical_on, sizeof(TPM_PHYSICAL_PRESENCE));

    Status = TcmPpi->TcmLibPassThrough(
            TcmReg,
            (UINT8*)&cmd,
            (sizeof (cmd.CmdHdr) + sizeof(TPM_PHYSICAL_PRESENCE)),
            (UINT8*)&RspHdr,
            sizeof (RspHdr));

    if ( RspHdr.returnCode != 0 )
    {
        TpmPeiReportStatusCode(EFI_ERROR_CODE|EFI_ERROR_MAJOR, AMI_SPECIFIC_TPM_1_2_PP_LOCK_CMD_SENT | EFI_SOFTWARE_PEI_MODULE);   
        return EFI_DEVICE_ERROR;
    }
    
    if( physical_on == SwapBytes16( TPM_PHYSICAL_PRESENCE_LOCK )){
        TpmPeiReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_1_2_PP_LOCK_CMD_SENT | EFI_SOFTWARE_PEI_MODULE);
    }
    
    return Status;
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  TcgPeiGetRawImage
//
// Description:    Loads binary from RAW section of main firwmare volume
//
// Input:       IN EFI_PEI_SERVICES **PeiServices
//              IN OUT VOID         **Buffer
//              IN OUT UINT16       *size
//              IN     EFI_GUID     guid
//
// Output:        EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI TcgPeiGetRawImage(
    IN EFI_PEI_SERVICES **PeiServices,
    IN OUT VOID         **Buffer,
    IN OUT UINT16       *size,
    EFI_GUID            guid )
{
    EFI_STATUS                 Status;
    EFI_FIRMWARE_VOLUME_HEADER *pFV;
    UINTN                      FvNum   = 0;
    EFI_FFS_FILE_HEADER        *ppFile = NULL;
    MPDRIVER_LEGHEADER         *Temp;
    BOOLEAN                    Found = FALSE;

    while ( TRUE )
    {
        Status = (*PeiServices)->FfsFindNextVolume( (CONST EFI_PEI_SERVICES **)PeiServices, FvNum, (void **)&pFV );

        if ( EFI_ERROR( Status ))
        {
            return Status;
        }

        ppFile = NULL;

        while ( TRUE )
        {
            Status = (*PeiServices)->FfsFindNextFile( (CONST EFI_PEI_SERVICES **)PeiServices,
            										  EFI_FV_FILETYPE_ALL,
                                                      pFV,
                                                     (void **) &ppFile );

            if ( Status == EFI_NOT_FOUND )
            {
                break;
            }

            if ( CompareMem( &ppFile->Name, &guid, sizeof(EFI_GUID) ) == 0 )
            {
                Found = TRUE;
                break;
            }
        }

        if ( Found )
        {
            break;
        }
        else {
            FvNum++;
        }
    }

    (*PeiServices)->FfsFindSectionData( (CONST EFI_PEI_SERVICES **)PeiServices,
                                        EFI_SECTION_RAW,
                                        ppFile,
                                        Buffer );

    if ( Buffer == NULL )
    {
        return EFI_NOT_FOUND;
    }

    Temp  = ((MPDRIVER_LEGHEADER*)(((UINT8* )ppFile )+sizeof(EFI_FFS_FILE_HEADER)));
    *size = Temp->Size;
    
    Status = (*PeiServices)->AllocatePool((CONST EFI_PEI_SERVICES **)PeiServices, *size,  (void **)Buffer );
    if(EFI_ERROR(Status)) return Status;
    
    (*PeiServices)->CopyMem(*Buffer,( ((UINT8* )ppFile )+sizeof(EFI_FFS_FILE_HEADER) ), *size) ;

    return Status;
}

EFI_STATUS MeasureTCGPcClientSpecID(
    IN EFI_PEI_SERVICES **ps, 
    IN PEI_TCG_PPI      *tcg );

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   MemoryPresentEntry
//
// Description: This function performs TPM MP initialization
//
//
// Input:       IN     EFI_PEI_SERVICES  **PeiServices,
//
// Output:      EFI STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI MemoryPresentEntry(
    IN EFI_PEI_SERVICES **PeiServices )
{
    EFI_STATUS                     Status;
    EFI_HOB_GUID_TYPE              *Hob;
    TCG_LOG_HOB                    *TcgLog;
    PEI_TPM_PPI                    *TpmPpi = NULL;         
    PEI_TCG_PPI                    *TcgPpi = NULL;
    EFI_HOB_GUID_TYPE              *ptrBootMode;
    EFI_BOOT_MODE                  BootMode;

    AMI_TCG_PEI_FUNCTION_OVERRIDE_PPI       *MpOverride;

    Status = (*PeiServices)->LocatePpi(
                                (CONST EFI_PEI_SERVICES    **)PeiServices,
                                &AmiMemoryPresentFunctionOverrideGuid,
                                0, NULL,
                                (void **)&MpOverride);

    if(!EFI_ERROR(Status)){
        return (MpOverride->Function(PeiServices));
    }

    Status = (*PeiServices)->GetBootMode( (CONST EFI_PEI_SERVICES **)PeiServices, &BootMode );
    ASSERT_EFI_ERROR(  Status );
    
 #if (StartupCmd_SelfTest_State == 0)
    Status = SendStartupandSelftest(PeiServices,BootMode);
    if(EFI_ERROR(Status))return Status;  //if startup or selftest fails, treat it as a fatal error; return
 #endif

    if((BootMode == BOOT_ON_S3_RESUME) || (BootMode == BOOT_IN_RECOVERY_MODE)){
        return EFI_SUCCESS;
    }

    Status = TcgPeiBuildHobGuid(
        (CONST EFI_PEI_SERVICES    **) PeiServices,
        &gEfiTcgWakeEventDataHobGuid,
        sizeof (BootMode),
        (void **)&ptrBootMode );

    if(EFI_ERROR(Status)){
        return Status;
    }

    ptrBootMode++;
    (*PeiServices)->CopyMem( ptrBootMode, &BootMode, sizeof (BootMode));

    //even if TPM is deactivated still build hob but
    //don't populate it.
    Status = TcgPeiBuildHobGuid(
         (CONST EFI_PEI_SERVICES **)PeiServices,
        &gEfiPeiTcgLogHobGuid,
        sizeof (*TcgLog) + TCG_LOG_MAX_TABLE_SIZE,
        (void **)&Hob );

    if(EFI_ERROR(Status)){
        return Status;
    }

    TcgLog = (TCG_LOG_HOB*)(Hob + 1);
    (*PeiServices)->SetMem( TcgLog, sizeof (*TcgLog), 0 );
    TcgLog->TableMaxSize = TCG_LOG_MAX_TABLE_SIZE;
    
    Status = LocateTcgPpi(PeiServices, &TpmPpi, &TcgPpi);
    if(EFI_ERROR(Status))return EFI_NOT_FOUND;

    if(!IsTcmSupportType())
    {
#if defined(TcgNistSp800_155_SUPPORT) && (TcgNistSp800_155_SUPPORT == 1)
        Status = MeasureTCGPcClientSpecID(PeiServices, TcgPpi);
        ASSERT_EFI_ERROR( Status );
        Status = MeasureNISTManifest(PeiServices, TcgPpi);
        ASSERT_EFI_ERROR( Status );
#endif
        Status = MeasureCRTMVersionFuncPtr( PeiServices );
        ASSERT_EFI_ERROR(  Status );
        if ( EFI_ERROR( Status ))
        {
            DEBUG((DEBUG_ERROR, "Error: Failure %d %a Status = %r\n", __LINE__, __FUNCTION__, Status));
        }
    }

#if defined (AmiTrustedFv_Support) && (AmiTrustedFv_Support == 1)
    Status = PeiServicesNotifyPpi (&mTpm12EndOfPeiSignalPpiNotifyList[0]);
#else
    Status = FindAndMeasureFwVols(PeiServices);
#endif

    return Status;
}




static AMI_TCG_PLATFORM_PPI_AFTER_MEM  mAmiTcgPlatformPPI = {
    Set_TPMPhysicalPresence,
    MemoryPresentEntry,
    VerifyTcgVariables
};


static EFI_PEI_PPI_DESCRIPTOR mAmiTcgPlatformPPIListAfterMem[] = {
    {
        EFI_PEI_PPI_DESCRIPTOR_PPI
        | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &gAmiTcgPlatformPpiAfterMem,
        &mAmiTcgPlatformPPI
    }
};




//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   AmiTcgPlatformPEI_EntryAfterMem
//
// Description: Installs AMIplatform PPI for initialization in PEI after 
//              memory is installed
//
// Input:        IN EFI_FFS_FILE_HEADER *FfsHeader,
//               IN EFI_PEI_SERVICES    **PeiServices
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:   
//
// Notes:       
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI AmiTcgPlatformPEI_EntryAfterMem(
    IN EFI_PEI_FILE_HANDLE  FileHandle,
    IN CONST EFI_PEI_SERVICES    **PeiServices 
){
    EFI_STATUS Status;

    Status = (*PeiServices)->InstallPpi( PeiServices, mAmiTcgPlatformPPIListAfterMem );
    return Status;
}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
