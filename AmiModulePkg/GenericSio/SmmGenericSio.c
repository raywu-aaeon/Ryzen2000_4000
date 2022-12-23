//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file SmmGenericSio.c

    Implementation of the AMI SIO SMM Driver
    to record S# boot script after ReadyToLock event.
**/

#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/IoLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Protocol/AmiSioSmmHandoff.h>
#include <Protocol/AmiBoardInitPolicy.h>
#include <AmiDxeLib.h>
#include <AmiGenericSio.h>

/**
    Default Init Function - FUNC 0. Must present always. 
    It will be called at ready to boot event.
    If device requires some additional Boot script for S3 resume.
        
    @param[in] This                 Pointer to AMI_BOARD_INIT_PROTOCOL instance.
    @param[in] Function             Pointer to each SIO LDs Initialization routine.
    @param[in] ParameterBlock       Initialization Routine Parameters Block.

    @retval EFI_SUCCESS             Initial step sucessfully
    @retval EFI_INVALID_PARAMETER   Not find the initial step or instance is NULL.
**/
EFI_STATUS  EFIAPI Func0(
        AMI_BOARD_INIT_PROTOCOL     *This,
        IN UINTN                    *Function,
        IN OUT AMI_BOARD_INIT_PARAMETER_BLOCK                 *ParameterBlock
)
{
    AMI_BOARD_INIT_PARAMETER_BLOCK  *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
//----------------------


    if((This==NULL) || (*Function != 0) || (ParameterBlock==NULL) || (Args->InitStep != 0)) return EFI_INVALID_PARAMETER;

    Args->Param1=&This->FunctionCount;
    Args->Param2=NULL;
    Args->Param3=NULL;
    Args->Param4=&This->Uid;

    return EFI_SUCCESS;
}
#ifdef __GNUC__
 #pragma GCC diagnostic ignored "-Wmissing-braces"
#endif
#include <GSIODXEINIT.h> 
//======================================================================================
///Global Variables
//======================================================================================
UINTN                           gSmmSpioCnt=0;

AMI_SIO_SMM_HANDOFF_PROTOCOL    *gAmiSioSmmHandoffProtocol=NULL;

SMM_GSIO                        *gSmmSpio;

EFI_HANDLE                      gSmiReadyToBootCommunicateHandle;

//======================================================================================

/**
    Routine to record SIO LD selection into S3 Boot Script.

    @param Dev Pointer to the private SIO LD data structure
    @param SaveState Pointer to EFI_S3_SAVE_STATE_PROTOCOL instance
    
    @retval EFI_SUCCESS if everything good
    @retval EFI_ERROR value if something wrong happends
**/
VOID EFIAPI SmmBootScriptSioDevSelect(SMM_SIO_DEV *Dev, EFI_S3_SMM_SAVE_STATE_PROTOCOL *SaveState){
	
    EFI_STATUS Status;
//---------------------
    //in case of non Standard SIO w/o Device Select Register specified just return
    if((!Dev->Owner->SpioSdlInfo.StdSioDevice) && (Dev->Owner->SpioSdlInfo.DevSelReg == 0)) return;
    
    //BOOT_SCRIPT_S3_IO_WRITE_MACRO(SaveState,
    //        EfiBootScriptWidthUint8,
    //        Dev->Owner->SpioSdlInfo->SioIndex, 1, &Dev->Owner->SpioSdlInfo->DevSelReg);
    SIO_TRACE((TRACE_SIO,"SmmSIO:  Adding IO ( 0x%X <- 0x%X; cnt=1)", Dev->Owner->SpioSdlInfo.SioIndex, Dev->Owner->SpioSdlInfo.DevSelReg));
    Status = SaveState->Write(SaveState, 0x00, EfiBootScriptWidthUint8,
            (UINT64)Dev->Owner->SpioSdlInfo.SioIndex, (UINTN)1, &Dev->Owner->SpioSdlInfo.DevSelReg);
    SIO_TRACE((TRACE_SIO,"Status=%r\n",Status));

    //BOOT_SCRIPT_S3_IO_WRITE_MACRO(SaveState,
    //        EfiBootScriptWidthUint8,
    //        Dev->Owner->SpioSdlInfo->SioData, 1, &Dev->DeviceInfo->Ldn);
    
    SIO_TRACE((TRACE_SIO,"SmmSIO:  Adding IO ( 0x%X <- 0x%X; cnt=1)", Dev->Owner->SpioSdlInfo.SioData, Dev->SdlDeviceInfo.Ldn));
    Status = SaveState->Write(SaveState, 0x00, EfiBootScriptWidthUint8,
            (UINT64)Dev->Owner->SpioSdlInfo.SioData, (UINTN)1, &Dev->SdlDeviceInfo.Ldn);
    SIO_TRACE((TRACE_SIO,"Status=%r\n",Status));
    
}



/**
    This Function Selects SIO Logical device "Dev"
    
    @param Dev Pointer to the private LD Data

    @retval VOID

    @note This function assumes SIO is in Config Mode
**/
VOID EFIAPI SmmDevSelect(SMM_SIO_DEV *Dev){
//----------------
    //in case of non Standard SIO w/o Device Select Register specified just return
    if((!Dev->Owner->SpioSdlInfo.StdSioDevice) && (Dev->Owner->SpioSdlInfo.DevSelReg==0)) return;
    
    //all other case 
    IoWrite8(Dev->Owner->SpioSdlInfo.SioIndex,Dev->Owner->SpioSdlInfo.DevSelReg);
    IoWrite8(Dev->Owner->SpioSdlInfo.SioData, Dev->SdlDeviceInfo.Ldn);
}


/**
    Routine to record SIO transition to/from Config Mode into S3 Boot Script.

    @param Sio Pointer to the private SIO data structure
    @param Get Action Selector
    @param SaveState Pointer to EFI_S3_SAVE_STATE_PROTOCOL instance
    
    @retval EFI_SUCCESS if everything good
    @retval EFI_ERROR value if something wrong happens
**/
VOID EFIAPI SmmBootScriptSioCfgMode(SMM_GSIO *Sio, BOOLEAN Enter, EFI_S3_SMM_SAVE_STATE_PROTOCOL *SmmSaveState)
{
    UINTN               i;
    SIO_SCRIPT_LST2     *sl;
    EFI_STATUS			Status;
//---------------------------------
    if(Enter)sl=Sio->EnterCfgMode;
    else sl=Sio->ExitCfgMode;

    if(sl==NULL) return;

    for (i=0; i<sl->InstrCount; i++){
        switch (sl->OpType){
            case cfNone: 
                break;
            case cfByteSeq:
            {
                SPIO_SCRIPT  *Instr = (SPIO_SCRIPT*) &sl->Instruction[0];
                SPIO_SCRIPT *cmd = &Instr[i];
                UINT16      reg;
            //------------------------
                if(cmd->IdxDat)reg=Sio->SpioSdlInfo.SioIndex;
                else reg=Sio->SpioSdlInfo.SioData;
                
                if (cmd->WrRd) {
                    //BOOT_SCRIPT_S3_IO_WRITE_MACRO(SaveState,
                    //    EfiBootScriptWidthUint8,
                    //    reg, 1, &cmd->Value
                    //);
                    SIO_TRACE((TRACE_SIO,"SmmSIO:  Adding IO ( 0x%X <- 0x%X; cnt=1)",reg,cmd->Value));
                    Status=SmmSaveState->Write(SmmSaveState,0x00,EfiBootScriptWidthUint8,(UINT64)reg,(UINTN)1,&cmd->Value);
                    SIO_TRACE((TRACE_SIO,"Status=%r\n",Status));
                    
                } else {
                    //This waits until SIO provides a specific value.
                    //This unsupported by boot script Io read/writes.

                    //<markw>I know of no SIO that needs this.
                    //If needed, SIO S3 resume must be implemented differently
                    // than the normal boot script.
                    SIO_TRACE((TRACE_SIO,"GSIO: Reading Index/Data SIO registers not supported entering/exit in for S3 resume.\n"));
                    ASSERT_EFI_ERROR(EFI_UNSUPPORTED);
                }
                break;
            }
            case cfRoutine:
            {
                UINTN  *FunctionNo = (UINTN*)&sl->Instruction[0];
                AMI_BOARD_INIT_PARAMETER_BLOCK  Parameters;

                *FunctionNo &= 0xF;
                if(gSioInitProtocolPtr->FunctionCount < *FunctionNo) {
                    return ;
                }
                Parameters.Signature = AMI_SIO_PARAM_SIG;
                Parameters.InitStep = isSioNone;
                Parameters.Param1 = NULL;
                Parameters.Param2 = NULL;
                Parameters.Param3 = SmmSaveState;
                Parameters.Param4 = NULL;
                if(gSioInitProtocolPtr) {
                    SIO_TRACE((TRACE_SIO,"SmmSIO: Calling InitProtocol->Function[%lX](Enter/ExitCfgMode)...", *FunctionNo));
                    Status = gSioInitProtocolPtr->Functions[*FunctionNo](gSioInitProtocolPtr, FunctionNo, &Parameters);
                    SIO_TRACE((TRACE_SIO,"%r\n",Status));
                    ASSERT_EFI_ERROR(Status);
                }
                break;
            }
            default: return;
        }//switch
    }//for
    Sio->InCfgMode=Enter;
    return;
}



/**
    Routine to transit Sio in/from Config Mode.

    @param Sio Pointer to the SIO Private Data
    @param Enter Action Selector
    
    @retval VOID

**/  
VOID EFIAPI SmmSioCfgMode(SMM_GSIO *Sio, BOOLEAN Enter)
{
    UINTN               i;
    SIO_SCRIPT_LST2     *sl;
//---------------------------------
    if(Enter)sl=Sio->EnterCfgMode;
    else sl=Sio->ExitCfgMode;

    if(sl==NULL) return;

    for (i=0; i<sl->InstrCount; i++){
        switch (sl->OpType){
            case cfNone: 
                break;
            case cfByteSeq:
            {
                SPIO_SCRIPT  *Instr = (SPIO_SCRIPT*) &sl->Instruction[0];
                SPIO_SCRIPT *cmd = &Instr[i];
                UINT16      reg;
                UINT8       dat;    
            //------------------------
                if(cmd->IdxDat)reg=Sio->SpioSdlInfo.SioIndex;
                else reg=Sio->SpioSdlInfo.SioData;
                
                if (cmd->WrRd) IoWrite8(reg,cmd->Value);
                else {
                    UINTN c=100000;
                    dat=IoRead8(reg);
                    while( c && dat!=cmd->Value ) {
                        dat=IoRead8(reg);
                        c--;    
                    }
                }
                break;
            }
            case cfRoutine:
            {
                UINTN  *FunctionNo = (UINTN*)&sl->Instruction[0];
                AMI_BOARD_INIT_PARAMETER_BLOCK  Parameters;

                *FunctionNo &= 0xF;
                if(gSioInitProtocolPtr->FunctionCount < *FunctionNo) {
                    return ;
                }
                Parameters.Signature = AMI_SIO_PARAM_SIG;
                Parameters.InitStep = isSioNone;
                Parameters.Param1 = NULL;
                Parameters.Param2 = NULL;
                Parameters.Param3 = NULL;
                Parameters.Param4 = NULL;                
                if(gSioInitProtocolPtr) {

                    gSioInitProtocolPtr->Functions[*FunctionNo](gSioInitProtocolPtr, FunctionNo, &Parameters);
                }
                //BOOT_SCRIPT_S3_DISPATCH_MACRO(SmmSaveState, (VOID*)(gSioInitProtocolPtr->Functions[*FunctionNo]));
                break;
            }

            default: return;
        }//switch
    }//for
    Sio->InCfgMode=Enter;
    return;
}

/**
  SmmLaunchInitRoutine - Invokes initialization routine for SMM
  
  @param[in] Device     Points to the LD Private Data.

  @retval EFI_SUCCESS   runs successfully.
 **/
EFI_STATUS EFIAPI SmmLaunchInitRoutine(SMM_SIO_DEV *Device, EFI_S3_SMM_SAVE_STATE_PROTOCOL  *SmmS3Save){
    AMI_BOARD_INIT_PARAMETER_BLOCK  Parameters;
    UINTN                           InitFunction=Device->SdlDeviceInfo.InitRoutine;
    EFI_STATUS                      Status;
//----------------------- 

    //Check the parameters...
    if((gSioInitProtocolPtr==NULL)||(Device->CompatibleMode)) return EFI_SUCCESS;
    if(Device->SdlDeviceInfo.InitRoutine==0) return EFI_SUCCESS;
    if(gSioInitProtocolPtr->FunctionCount < Device->SdlDeviceInfo.InitRoutine) return EFI_INVALID_PARAMETER;
    
        
    Parameters.Signature    =AMI_SIO_PARAM_SIG;
    Parameters.InitStep     =isAfterSmmBootScript;
    Parameters.Param1       =Device;
    Parameters.Param2       =NULL;
    Parameters.Param3       =SmmS3Save;
    Parameters.Param4       =NULL;

    SIO_TRACE((TRACE_SIO,"\nSmmSIO:  Calling Porting Function ... "));
    Status=gSioInitProtocolPtr->Functions[InitFunction](gSioInitProtocolPtr,&InitFunction, &Parameters);
    SIO_TRACE((TRACE_SIO,"Status=%r\n",Status));
            
    if(EFI_ERROR(Status)){
        if(Status!=EFI_UNSUPPORTED){
            ASSERT_EFI_ERROR(Status);
        } else Status =EFI_SUCCESS;
    }
    return Status;            
        
}

/**
  Smm Ready To Lock event notification handler 
  When triggered it start to record SIO Boot Script.
  
  @param[in] Protocol   Points to the protocol's unique identifier.
  @param[in] Interface  Points to the interface instance.
  @param[in] Handle     The handle on which the interface was installed.

  @retval EFI_SUCCESS   Notification handler runs successfully.
 **/
EFI_STATUS EFIAPI SmmSioRecordBootScript ()
{
    EFI_S3_SMM_SAVE_STATE_PROTOCOL  *s3s;
    EFI_STATUS  Status;
    UINTN       i, j, s, ari;//, cnt1,cnt2;
    UINT8       b,r;
    BOOLEAN     devsel, devact, cfgmod; 
    BOOLEAN     noar=FALSE, nods=FALSE;
    SMM_SIO_DEV *dev;
    SMM_GSIO    *spio;
//----------------------------------
    SIO_TRACE((TRACE_SIO, "SmmSIO: -> [[ SmmCallbackReadyToBoot() Start... ]]\n"));

    Status = gSmst->SmmLocateProtocol(&gEfiS3SmmSaveStateProtocolGuid, NULL, (VOID **)&s3s);
    if (EFI_ERROR(Status)) {
        SIO_TRACE((TRACE_SIO,"SmmSIO: FAIL to locate EfiBootScriptSaveProtocol %r",Status));
        return EFI_UNSUPPORTED;
    }
    
    for(s=0;s<gSmmSpioCnt;s++){  
        cfgmod=FALSE;
        spio=&gSmmSpio[s];
        if(!spio->InCfgMode) SmmSioCfgMode(spio, TRUE);
        spio->SaveState=s3s;

        nods=((spio->SpioSdlInfo.StdSioDevice==0) && (spio->SpioSdlInfo.DevSelReg==0));
        noar=((spio->SpioSdlInfo.StdSioDevice==0) && (spio->SpioSdlInfo.ActivateReg==0));
                
        //first Check if something changed in Global Config regs programming
        for(i=0;  i<spio->GlobalInclRegCount; i++){
            //if we got DevSel register just skip it
            r=spio->GlobalIncludeReg[i];
            
            if(!noar){
                if(r==spio->SpioSdlInfo.ActivateReg) continue;
            }

            if(!nods){
                if(r==spio->SpioSdlInfo.DevSelReg) continue;
            }
            
            //select register
            IoWrite8(spio->SpioSdlInfo.SioIndex,r);
            //read actual data
            b=IoRead8(spio->SpioSdlInfo.SioData);
            //if nothing has changed just skip it
            if(b==spio->GlobalCfgDump[i]) continue; 

            //enter config mode only if we really need it
            if(!cfgmod){
                SmmBootScriptSioCfgMode(spio,TRUE,s3s);
                cfgmod=TRUE;
            }   
            //if this reg was different before the initialization of SIO - record that into boot script
            //BOOT_SCRIPT_S3_IO_WRITE_MACRO(s3s,EfiBootScriptWidthUint8,spio->SpioSdlInfo->SioIndex, 1, &r);
            SIO_TRACE((TRACE_SIO,"SmmSIO:  Adding IO ( 0x%X <- 0x%X; cnt=1)",spio->SpioSdlInfo.SioIndex, r));
            Status=s3s->Write(s3s,0x00,EfiBootScriptWidthUint8,(UINT64)spio->SpioSdlInfo.SioIndex,(UINTN)1,&r);
            SIO_TRACE((TRACE_SIO,"Status=%r\n",Status));
            
            //BOOT_SCRIPT_S3_IO_WRITE_MACRO(s3s,EfiBootScriptWidthUint8,spio->SpioSdlInfo->SioData, 1, &b);
            SIO_TRACE((TRACE_SIO,"SmmSIO:  Adding IO ( 0x%X <- 0x%X; cnt=1)",spio->SpioSdlInfo.SioData, b));
            Status=s3s->Write(s3s,0x00,EfiBootScriptWidthUint8,(UINT64)spio->SpioSdlInfo.SioData, (UINTN)1,&b);
            SIO_TRACE((TRACE_SIO,"Status=%r\n",Status));
        }
        
        //Found out Activate register index in spio->SpioInfo->LocalIncludeReg[] buffer
        //it must be in LocalIncludeReg[] Buffer for standard SIO.
        //Special SIO might not have Activate register so..
        //in case of non Standard SIO w/o Device Activate Register specified 
        //set ActivateRegister Index bigger array count 
        if(noar) ari=spio->LocalInclRegCount;
        else{
            //Device Activate Register must be specified 
            for(ari=0; ari<spio->LocalInclRegCount; ari++){
                    if(spio->LocalIncludeReg[ari]==spio->SpioSdlInfo.ActivateReg)break;
            }
        } 
        
        //Now check Local registers - unique for each device
        for (j=0; j<spio->LdCount; j++) {

        //---------------------
            devsel=FALSE;
            dev=&spio->DeviceList[j];
            
            //found out if device was selected
            if(nods)devsel=TRUE;
            else SmmDevSelect(dev);

            //found out if device was active after PEI phase before DXE SIO Intialization
            if(noar){
                devact=FALSE;
            } else {
                devact=(dev->LocalCfgDump[ari]==spio->SpioSdlInfo.ActivateVal);
            
                //check current device active status
                IoWrite8(spio->SpioSdlInfo.SioIndex,spio->SpioSdlInfo.ActivateReg);
                b=IoRead8(spio->SpioSdlInfo.SioData);                
                //if device is NOT active now and was NOT active before just skip it 
                if( ((b==spio->SpioSdlInfo.DeactivateVal) && (dev->LocalCfgDump[ari]==spio->SpioSdlInfo.DeactivateVal)) || (!dev->StdLogicDev)){
                    //Here unconditionally invoke initialization routine...
                    if(!cfgmod){ //if still not in config mode
                        SmmBootScriptSioCfgMode(spio,TRUE,s3s);
                        cfgmod=TRUE;
                    }
                    if(!devsel){//device has not been selected
                        SmmBootScriptSioDevSelect(dev, s3s);
                        devsel=TRUE;
                    }
                    //This porting function is for nonstandard logical device to write configuration register to bootscript.
                    Status=SmmLaunchInitRoutine(dev, s3s);
                    ASSERT_EFI_ERROR(Status);
                    continue;
                }
        
                //if before and after device was ACTIVE that means - nothing has changed 
                //in Device Active Status. We need not to add this device in boot script
                if((b==spio->SpioSdlInfo.ActivateVal)&&(dev->LocalCfgDump[ari]==spio->SpioSdlInfo.ActivateVal));
                else{
                    //before and after SIO Init Activate register values does not mutch 
                    //we need to enter config mode if not in config mode yet and select the device 
                    if(!cfgmod){ //if still not in config mode
                        SmmBootScriptSioCfgMode(spio,TRUE,s3s);
                        cfgmod=TRUE;
                    }   
                    if(!devsel){//device has not been selected
                        SmmBootScriptSioDevSelect(dev, s3s);
                        devsel=TRUE;
                    }   
                    //Device was Active after PEI phase, but now it is NOT
                    if(devact){
                        //BOOT_SCRIPT_S3_IO_WRITE_MACRO(s3s,EfiBootScriptWidthUint8,spio->SpioSdlInfo->SioIndex, 1, &spio->SpioSdlInfo->ActivateReg);
                        SIO_TRACE((TRACE_SIO,"SmmSIO:  Adding IO ( 0x%X <- 0x%X; cnt=1)",spio->SpioSdlInfo.SioIndex, spio->SpioSdlInfo.ActivateReg));
                        Status=s3s->Write(s3s,0x00,EfiBootScriptWidthUint8,(UINT64)spio->SpioSdlInfo.SioIndex,(UINTN)1,&spio->SpioSdlInfo.ActivateReg);
                        SIO_TRACE((TRACE_SIO,"Status=%r\n",Status));

                        
                        //BOOT_SCRIPT_S3_IO_WRITE_MACRO(s3s,EfiBootScriptWidthUint8,spio->SpioSdlInfo->SioData, 1, &spio->SpioSdlInfo->DeactivateVal);
                        SIO_TRACE((TRACE_SIO,"SmmSIO:  Adding IO ( 0x%X <- 0x%X; cnt=1)", spio->SpioSdlInfo.SioData, spio->SpioSdlInfo.DeactivateVal));
                        Status=s3s->Write(s3s,0x00,EfiBootScriptWidthUint8,(UINT64)spio->SpioSdlInfo.SioData,(UINTN)1,&spio->SpioSdlInfo.DeactivateVal);
                        SIO_TRACE((TRACE_SIO,"Status=%r\n",Status));
                        devact=FALSE; 
                    }
                    if((b==spio->SpioSdlInfo.DeactivateVal) || (!dev->StdLogicDev))continue;
                }
            } 
            
            //if we are here that means - Device is active after DXE initialization 
            //and we must check if something gets changed in Generic register programming
            for(i=0;  i<spio->LocalInclRegCount; i++) {
                r=spio->LocalIncludeReg[i];
                //We took care about activate register erlier   
                if((r==spio->SpioSdlInfo.ActivateReg)||(r==spio->SpioSdlInfo.DevSelReg)) continue;
            
                //select register
                IoWrite8(spio->SpioSdlInfo.SioIndex,r);
                //read actual data
                b=IoRead8(spio->SpioSdlInfo.SioData);
                //if nothing has changed just skip it
                if(b==dev->LocalCfgDump[i]) continue;   

                //enter config mode only if we really need it
                if(!cfgmod){
                    SmmBootScriptSioCfgMode(spio, TRUE, s3s);
                    cfgmod=TRUE;
                }
                //device has not been selected
                if(!devsel){
                    SmmBootScriptSioDevSelect(dev, s3s);
                    devsel=TRUE;
                }
                //Deactivate the device before changing registers 
                if(devact){ 
                    //BOOT_SCRIPT_S3_IO_WRITE_MACRO(s3s,EfiBootScriptWidthUint8,spio->SpioSdlInfo->SioIndex, 1, &spio->SpioSdlInfo->ActivateReg);
                    SIO_TRACE((TRACE_SIO,"SmmSIO:  Adding IO ( 0x%X <- 0x%X; cnt=1)", spio->SpioSdlInfo.SioIndex, spio->SpioSdlInfo.ActivateReg));
                    Status=s3s->Write(s3s,0x00,EfiBootScriptWidthUint8,(UINT64)spio->SpioSdlInfo.SioIndex,(UINTN)1,&spio->SpioSdlInfo.ActivateReg);
                    SIO_TRACE((TRACE_SIO,"Status=%r\n",Status));

                    
                    //BOOT_SCRIPT_S3_IO_WRITE_MACRO(s3s,EfiBootScriptWidthUint8,spio->SpioSdlInfo->SioData, 1, &spio->SpioSdlInfo->DeactivateVal);
                    SIO_TRACE((TRACE_SIO,"SmmSIO:  Adding IO ( 0x%X <- 0x%X; cnt=1)",spio->SpioSdlInfo.SioData,spio->SpioSdlInfo.DeactivateVal));
                    Status=s3s->Write(s3s,0x00,EfiBootScriptWidthUint8,(UINT64)spio->SpioSdlInfo.SioData,(UINTN)1,&spio->SpioSdlInfo.DeactivateVal);
                    SIO_TRACE((TRACE_SIO,"Status=%r\n",Status));
                            
                    devact=FALSE;
                }
                //if this reg was different before the DXE initialization of SIO - record that into boot script
                //BOOT_SCRIPT_S3_IO_WRITE_MACRO(s3s,EfiBootScriptWidthUint8,spio->SpioSdlInfo->SioIndex, 1, &r);
                SIO_TRACE((TRACE_SIO,"SmmSIO:  Adding IO ( 0x%X <- 0x%X; cnt=1)",spio->SpioSdlInfo.SioIndex,r));
                Status=s3s->Write(s3s,0x00,EfiBootScriptWidthUint8,(UINT64)spio->SpioSdlInfo.SioIndex,(UINTN)1,&r);
                SIO_TRACE((TRACE_SIO,"Status=%r\n",Status));

                //BOOT_SCRIPT_S3_IO_WRITE_MACRO(s3s,EfiBootScriptWidthUint8,spio->SpioSdlInfo.SioData, 1, &b);
                SIO_TRACE((TRACE_SIO,"SmmSIO:  Adding IO ( 0x%X <- 0x%X; cnt=1)",spio->SpioSdlInfo.SioData,b));
                Status=s3s->Write(s3s,0x00,EfiBootScriptWidthUint8,(UINT64)spio->SpioSdlInfo.SioData,(UINTN)1,&b);
                SIO_TRACE((TRACE_SIO,"Status=%r\n",Status));

            } //reg dump compare loop

            //if we are here we have checked the device registers 
            if(!devact){ // we must Activate device now if we have deactivated it earlier
                //BOOT_SCRIPT_S3_IO_WRITE_MACRO(s3s,EfiBootScriptWidthUint8,spio->SpioSdlInfo->SioIndex, 1, &spio->SpioSdlInfo->ActivateReg);
                SIO_TRACE((TRACE_SIO,"SmmSIO:  Adding IO ( 0x%X <- 0x%X; cnt=1)",spio->SpioSdlInfo.SioIndex,spio->SpioSdlInfo.ActivateReg));
                s3s->Write(s3s,0x00,EfiBootScriptWidthUint8,(UINT64)spio->SpioSdlInfo.SioIndex,(UINTN)1,&spio->SpioSdlInfo.ActivateReg);
                SIO_TRACE((TRACE_SIO,"Status=%r\n",Status));

                //BOOT_SCRIPT_S3_IO_WRITE_MACRO(s3s,EfiBootScriptWidthUint8,spio->SpioSdlInfo->SioData, 1, &spio->SpioSdlInfo->ActivateVal);
                SIO_TRACE((TRACE_SIO,"SmmSIO:  Adding IO ( 0x%X <- 0x%X; cnt=1)",spio->SpioSdlInfo.SioData,spio->SpioSdlInfo.ActivateVal));
                s3s->Write(s3s,0x00,EfiBootScriptWidthUint8,(UINT64)spio->SpioSdlInfo.SioData,(UINTN)1,&spio->SpioSdlInfo.ActivateVal);
                SIO_TRACE((TRACE_SIO,"Status=%r\n",Status));
            }
            
            //Now if device has programmed some registers mapped through LD Decoded registers
            //we need so save them as well. We will not do this automatically, but call Porting function to do so...
            //SIO_TRACE((TRACE_SIO,"GSIO: InitSioDevice() - Calling InitRoutine(isAfterBootScript)"));
            //This porting function is for standard logical device to write runtime register to bootscript.
            Status=SmmLaunchInitRoutine(dev, s3s);
            ASSERT_EFI_ERROR(Status);
            
            
            //SIO_TRACE((TRACE_SIO," Status=%r\n", Status));
        } //end device loop
        if(cfgmod)SmmBootScriptSioCfgMode(spio, FALSE, s3s);
        SmmSioCfgMode(spio, FALSE);
    }//for s
        
    SIO_TRACE((TRACE_SIO, "SmmSIO: -> [[ CallbackReadyToBoot()  Done!!! ]]\n"));
    return EFI_SUCCESS;
}


/**
    Creates copy of SIO Data in SMRAM.  
    
    @param Pointer to This Driver Image Handle
    @param Pointer to the UEFI Services System Table

    @retval EFI_STATUS
        EFI_SUCCESS      When everything is going on fine!
        EFI_ERROR        Something Wrong!
**/
EFI_STATUS EFIAPI CopySioData(){
   UINTN    i,j,sz;
//----------------    
    gSmmSpio=AllocateZeroPool(sizeof(SMM_GSIO)*gSmmSpioCnt);
    if(gSmmSpio==NULL) return EFI_OUT_OF_RESOURCES;
    
    //Copy All necessary data from gAmiSioSmmHandoffProtocolInstance to gSmmSpio    
    for(i=0;i<gSmmSpioCnt; i++){
        GSIO2    *spio;
    //------------------------
        spio=&gAmiSioSmmHandoffProtocol->SpioData[i];
        gSmmSpio[i].InCfgMode           = spio->InCfgMode;
        gSmmSpio[i].CompatibleData      = spio->CompatibleData;
        CopyMem(&gSmmSpio[i].SpioSdlInfo, spio->SpioSdlInfo, sizeof(AMI_SDL_SIO_CHIP_INFO));

        //get memory for Logical Devices we will copy it here later.
        gSmmSpio[i].LdCount             = spio->LdCount;
        sz=sizeof(SMM_SIO_DEV)*gSmmSpio[i].LdCount;
        
        
        
        gSmmSpio[i].DeviceList          = AllocateZeroPool(sz);
        if(gSmmSpio[i].DeviceList==NULL) return EFI_OUT_OF_RESOURCES;
                
        //Get Memory for Global registers info and dump for S3 Save...         
        gSmmSpio[i].GlobalInclRegCount  = spio->GlobalInclRegCount;
        sz=sizeof(UINT8)*gSmmSpio[i].GlobalInclRegCount;
        gSmmSpio[i].GlobalIncludeReg    = AllocatePool(sz);
        gSmmSpio[i].GlobalCfgDump       = AllocatePool(sz);
        if(gSmmSpio[i].GlobalIncludeReg==NULL || gSmmSpio[i].GlobalCfgDump==NULL) return EFI_OUT_OF_RESOURCES;
        //Copy content..
        CopyMem(gSmmSpio[i].GlobalIncludeReg,spio->GlobalIncludeReg,sz);
        CopyMem(gSmmSpio[i].GlobalCfgDump,spio->GlobalCfgDump,sz);
        
        //Get Memory for Local registers information for S3 Save dump will be stored 
        //in SMM_SIO_DEV.LocalCfgDump at corresponded gSmmSpio[i].DeviceList[j].LocalCfgDump        
        gSmmSpio[i].LocalInclRegCount   = spio->LocalInclRegCount;
        sz=sizeof(UINT8)*gSmmSpio[i].LocalInclRegCount;
        gSmmSpio[i].LocalIncludeReg     = AllocatePool(sz);
        if(gSmmSpio[i].LocalIncludeReg==NULL) return EFI_OUT_OF_RESOURCES;
        //Copy content..
        CopyMem(gSmmSpio[i].LocalIncludeReg,spio->LocalIncludeReg,sz);
        
        //Now Enter\Exit Cffg Mode Script....
        //Enter...
        sz=sizeof(SIO_SCRIPT_LST2)+(sizeof(SPIO_SCRIPT)*spio->EnterCfgMode->InstrCount-1);
        gSmmSpio[i].EnterCfgMode=AllocatePool(sz);
        if(gSmmSpio[i].EnterCfgMode==NULL) return EFI_OUT_OF_RESOURCES;
        //Copy content..
        CopyMem(gSmmSpio[i].EnterCfgMode, spio->EnterCfgMode,sz);

        //Exit...
        sz=sizeof(SIO_SCRIPT_LST2)+(sizeof(SPIO_SCRIPT)*spio->ExitCfgMode->InstrCount-1);
        gSmmSpio[i].ExitCfgMode=AllocatePool(sz);
        if(gSmmSpio[i].ExitCfgMode==NULL) return EFI_OUT_OF_RESOURCES;
        //Copy content..
        CopyMem(gSmmSpio[i].ExitCfgMode, spio->ExitCfgMode,sz);
        
        //Now copy each LD data, memory we have allocated as an array
        for(j=0;j<gSmmSpio[i].LdCount; j++){
            SMM_SIO_DEV *lds;
            SIO_DEV2    *ldd;
        //-----------------------
            ldd=spio->DeviceList[j];
            lds=&gSmmSpio[i].DeviceList[j];
            
            lds->Owner=&gSmmSpio[i];
            
            lds->Assigned           = ldd->Assigned;
            lds->CompatibleMode     = ldd->CompatibleMode;
            lds->Initialized        = ldd->Initialized;
            lds->Started            = ldd->Started;
            
            CopyMem(&lds->SdlDeviceInfo, ldd->DeviceInfo, sizeof(AMI_SDL_LOGICAL_DEV_INFO));
                        
            sz=sizeof(UINT8)*gSmmSpio[i].LocalInclRegCount;
            lds->LocalCfgDump=AllocatePool(sz);
            if(lds->LocalCfgDump==NULL) return EFI_OUT_OF_RESOURCES; 
            
            CopyMem(lds->LocalCfgDump,ldd->LocalCfgDump,sz);
            
            lds->NvData=ldd->NvData;
            lds->VlData=ldd->VlData;
        } //sio device
        
    }//SPIO chip Looop
    
    return EFI_SUCCESS;
}

/**
  Dispatch function for a Software SMI handler.

  @param DispatchHandle     The unique handle assigned to this handler by SmiHandlerRegister().
  @param Context            Points to an optional handler context which was specified when the
                            handler was registered.
  @param CommBuffer         A pointer to a collection of data in memory that will
                            be conveyed from a non-SMM environment into an SMM environment.
  @param CommBufferSize     The size of the CommBuffer.

  @retval EFI_SUCCESS       Command is handled successfully.
**/
EFI_STATUS EFIAPI SmiSioHandler (
  IN EFI_HANDLE                               DispatchHandle,
  IN CONST VOID                               *Context,
  IN OUT VOID                                 *CommBuffer,
  IN OUT UINTN                                *CommBufferSize
  )
{
    EFI_STATUS  Status;
    UINT8       Index;
    UINT8       Counter;
//-------------------    
    for(Index = 0;Index < gSmmSpioCnt;Index ++) {
        for(Counter = 0;Counter < gSmmSpio[Index].LdCount;Counter ++){
            SMM_SIO_DEV *SmmLogicalDevice;
            SmmLogicalDevice = &gSmmSpio[Index].DeviceList[Counter];
            SmmLogicalDevice->StdLogicDev = *((UINT8*)CommBuffer + Counter);
        }
    }  
    Status = SmmSioRecordBootScript();
    if(EFI_ERROR(Status)) {
        SIO_TRACE((TRACE_SIO,"SmmSIO: FAIL to record boot script."));
        return EFI_SUCCESS;
    }

    Status = gSmst->SmiHandlerUnRegister(DispatchHandle);
    ASSERT_EFI_ERROR (Status);
    
    return EFI_SUCCESS;
}




/**
    SMM Driver "entry point" for this module, called by the DXE Core.  
    
    @param Pointer to This Driver Image Handle
    @param Pointer to the UEFI Services System Table

    @retval EFI_STATUS
        EFI_SUCCESS      When everything is going on fine!
        EFI_ERROR        Something Wrong!
**/

EFI_STATUS EFIAPI SmmGenericSioEntryPoint(
	IN EFI_HANDLE		ImageHandle,
	IN EFI_SYSTEM_TABLE	*SystemTable
)
{
    EFI_STATUS      Status;
    EFI_GUID        SmiReadyToBootCommunicateGuid=SMI_READY_TO_BOOT_COMMUNICATE_GUID;
//------------------------
    
    //InitAmiLib(ImageHandle, SystemTable);
    InitAmiSmmLib(ImageHandle, SystemTable);
    //Get SioHandoff protocol instance it must be only one.
    Status=gBS->LocateProtocol(&gAmiSioSmmHandoffProtocolGuid, NULL, (VOID**)&gAmiSioSmmHandoffProtocol);
    if(EFI_ERROR(Status)){
        ASSERT_EFI_ERROR(Status);
        return Status;
    }    
    
    gSmmSpioCnt=gAmiSioSmmHandoffProtocol->SpioCount;    
  
    //No SIO - No Boot Script...
    if(gSmmSpioCnt==0) return EFI_SUCCESS;
    
    //Copy data we are going to need in SMM to SMRAM.
    Status=CopySioData();

    //Only EFI_OUT_OF_RESOURCES error can be found here.
    if(EFI_ERROR(Status)){
        ASSERT_EFI_ERROR(Status);
        return Status;
    }    
    
    //Setup ready to boot event Handler to record SIO Boot Script when triggered...
    
    
    Status = gSmst->SmiHandlerRegister (
            SmiSioHandler,
            &SmiReadyToBootCommunicateGuid,
            &gSmiReadyToBootCommunicateHandle
            );

    ASSERT_EFI_ERROR(Status);
    
    return Status;	
}
