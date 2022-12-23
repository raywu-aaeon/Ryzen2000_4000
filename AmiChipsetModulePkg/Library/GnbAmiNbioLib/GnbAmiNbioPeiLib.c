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

/** @file GnbAmiNbioPeiLib.c
    This file contains code for GnbAmiNbioPeiLib initialization in the PEI stage.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
// UDK header
#include <PiPei.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include "AGESA.h"
//AMI Generic Porting starts
#include "Token.h"
#include "Gnb.h"
#include <Library/GnbPolicy.h>
#include <Ppi/GnbPpi.h>
#include <Library/GnbHdaVerbTableLib.h>
#include <Library/AmdSocBaseLib.h>
//### RVA9 : Family15 only ####include <Dxe/AmdPbsSetupDxe/AmdPbsConfig.h>
//### RVA9 : Family15 only ####include <Library/AmdPbsConfigLib/AmdPbsConfigLib.h>


//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)
SOC_ID_STRUCT gFchSocIdTbl[] = {
    {F17_RV_RAW_ID, RV_FP5}
};

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// PPI Definition(s)

// PPI that are installed

// PPI that are notified

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

/**
    This function is the entry point for GnbAmiNbioPeiLib PEIM.
    It initializes the chipset GnbAmiNbioPeiLib in PEI phase.

    @param FileHandle Pointer to the FFS file header.
    @param PeiServices Pointer to the PEI services table.

    @retval EFI_STATUS EFI_SUCCESS

    @note  .
**/

VOID 
GnbAmiNbioPeiHdAudioPcdSet (
  IN CONST EFI_PEI_SERVICES    **PeiServices
  )
{
    EFI_STATUS           Status = EFI_SUCCESS;
    GNB_CODEC_VERB_TABLE_LIST  *VerbTbl;
    GNB_AGESA_CODEC_VERB_TABLE_LIST *VerbTableList=NULL;
    GNB_AGESA_CODEC_VERB_TABLE_LIST  *VerbTablePcdSet=NULL;
    GNB_AGESA_CODEC_VERB_TABLE_LIST  *CreateVerbTable=NULL;
    UINT32               Size = 0;
    UINT32               Length =0;
    UINT32               i=0;

    VerbTbl = (GNB_CODEC_VERB_TABLE_LIST*)GnbHdaVerbTableOverride ();

    //Check the total length
    for(i=0;VerbTbl[i].CodecId != 0xFFFFFFFF;i++){
        Length++;
        VerbTableList = (GNB_AGESA_CODEC_VERB_TABLE_LIST*)VerbTbl[i].CodecTablePtr;
        while (VerbTableList->CodecId != 0xFFFFFFFF) {
              VerbTableList++;
              Length++;
        }
         Length++;
    }
    
    //add end flag " UINT32(0xFFFFFFFF), UINT64(0x0FFFFFFFF)" length 
    Length =Length+2;
    
    Size = Length*sizeof(UINT32);
    
    Status = (*PeiServices)->AllocatePool(PeiServices,Size, &VerbTablePcdSet); //allocate a length  buffer
    ASSERT_EFI_ERROR(Status);

    CreateVerbTable = VerbTablePcdSet;

    //Convert the Verb table as Agesa V9 format
    for(i=0;VerbTbl[i].CodecId != 0xFFFFFFFF;i++){
        CreateVerbTable->CodecId = VerbTbl[i].CodecId;
        CreateVerbTable++;
        VerbTableList = (GNB_AGESA_CODEC_VERB_TABLE_LIST*)VerbTbl[i].CodecTablePtr;
        while (VerbTableList->CodecId != 0xFFFFFFFF) {
            CreateVerbTable->CodecId =VerbTableList->CodecId;
            VerbTableList++;
            CreateVerbTable++;
        }
        CreateVerbTable->CodecId = 0xFFFFFFFF;
        CreateVerbTable++;
    }

    //End Table ,add end flag with value :" UINT32(0xFFFFFFFF), UINT64(0x0FFFFFFFF)"
    CreateVerbTable->CodecId = 0xFFFFFFFF;
    CreateVerbTable++;
    CreateVerbTable->CodecId = 0xFFFFFFFF;
    
    PcdSet32S (PcdCfgAzaliaCodecVerbTable, (UINT32)VerbTablePcdSet);
    DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "VerbTbl=%x ,Size=%x,PCDget =%x\n",VerbTbl,Size,PcdGet32(PcdCfgAzaliaCodecVerbTable)));
}


    
EFI_STATUS
EFIAPI
GnbAmiNbioPeiConstructor (
  IN EFI_PEI_FILE_HANDLE       FileHandle,
  IN CONST EFI_PEI_SERVICES    **PeiServices
  )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    GNB_SETUP_DATA              GnbSetupData;
    UINTN                       i;

    GetGnbSetupData((VOID*)PeiServices, &GnbSetupData, TRUE);
    
    //## depends on AMD-CBS
    //if (GnbSetupData.PsppPolicy != GNB_SD_AUTO) PcdSet8S(PcdPsppPolicy, GnbSetupData.PsppPolicy);//|0x00|UINT8|0x0003F501

    //Use SDL VerbTable  OEM_HDA_VERB_TABLE
    #if GNB_HDA_VERBTABLE
        GnbAmiNbioPeiHdAudioPcdSet(PeiServices);
    #endif //GNB_HDA_VERBTABLE


    // Summit, UMA default off
    //####PcdSet8S (PcdAmdMemCfgUmaMode, UMA_NONE); //### Default DEC is auto.
        
    for (i = 0; i < sizeof(gFchSocIdTbl)/sizeof(SOC_ID_STRUCT); i++) {
    	if (SocHardwareIdentificationCheck (&gFchSocIdTbl[i])) {
//### RVA9 : Family15 only ###        GNB_SETUP_DATA                  GnbSetupData;
//### RVA9 : Family15 only ###        AMD_PBS_SETUP_OPTION            AmdPbsSetup;
//### RVA9 : Family15 only ###        MEM_PARAMETER_STRUCT            *MemPtr = NULL;
//### RVA9 : Family15 only ###
//### RVA9 : Family15 only ###        GetGnbSetupData((VOID*)PeiServices, &GnbSetupData, TRUE);
//### RVA9 : Family15 only ###
//### RVA9 : Family15 only ###        PcdSet8S (PcdCfgGnbHdAudio,  GnbSetupData.GnbHdAudio);
//### RVA9 : Family15 only ###
//### RVA9 : Family15 only ###        Status = GetAmdPbsConfiguration(&AmdPbsSetup);
//### RVA9 : Family15 only ###        if (!EFI_ERROR(Status)) {
//### RVA9 : Family15 only ###            if (AmdPbsSetup.SpecialVgaFeature == 0) {
//### RVA9 : Family15 only ###                if (AmdPbsSetup.PrimaryVideoAdaptor == 1) {
//### RVA9 : Family15 only ###
//### RVA9 : Family15 only ###                    if (GnbSetupData.UmaFrameBufferSize != GNB_SD_AUTO) {
//### RVA9 : Family15 only ###                        PcdSet8S (PcdAmdMemCfgUmaMode, UMA_SPECIFIED); ////Forced
//### RVA9 : Family15 only ###                        PcdSet32S (PcdAmdMemCfgUmaSize, GnbSetupData.UmaFrameBufferSize << 9);
//### RVA9 : Family15 only ###                    }
//### RVA9 : Family15 only ###
//### RVA9 : Family15 only ###                } else if (AmdPbsSetup.PrimaryVideoAdaptor == 2) {
//### RVA9 : Family15 only ###                    PcdSet8S (PcdAmdMemCfgUmaMode, UMA_NONE); ////Forced
//### RVA9 : Family15 only ###                }
//### RVA9 : Family15 only ###            }
//### RVA9 : Family15 only ###        }
            break;
    	}
    }

    
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
