//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//*************************************************************************
// $Header: $
//
// $Revision: $
//
// $Date: $
//*************************************************************************
// Revision History
// ----------------
// $Log:  $
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
#include <Efi.h>
#include "Tpm20CRBLibArm.h"
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Token.h>
#include <AmiTcg/Tpm20.h>
#include <Library/TimerLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/ArmSmcLib.h>

#define CRB_TIMEOUT_A   (750 * 1000)       //microseconds
#define CRB_TIMEOUT_B   (2 * 1000 * 1000)  
#define CRB_TIMEOUT_C   (30 * 1000)
#define CRB_TIMEOUT_D   (200 * 1000)


UINT8 *
EFIAPI
CrbMmioReadBuffer8 (
    IN  UINTN       StartAddress,
    IN  UINTN       Length,
    OUT UINT8      *Buffer
)
{
    UINT8   *ReturnBuffer;

    ASSERT ((Length - 1) <=  (MAX_ADDRESS - StartAddress));
    ASSERT ((Length - 1) <=  (MAX_ADDRESS - (UINTN) Buffer));

    ReturnBuffer = Buffer;

    while (Length-- != 0)
    {
                *(Buffer++) = MmioRead8 (StartAddress++);  
    }

    return ReturnBuffer;
}


UINT32 *
EFIAPI
CrbMmioWriteBuffer8 (
    IN  UINTN        StartAddress,
    IN  UINTN        Length,
    IN  CONST UINT8  *Buffer
)
{
    VOID* ReturnBuffer;

    ASSERT ((Length - 1) <=  (MAX_ADDRESS - StartAddress));
    ASSERT ((Length - 1) <=  (MAX_ADDRESS - (UINTN) Buffer));

    ReturnBuffer = (UINT8 *) Buffer;

    while (Length-- != 0)
    {
        MmioWrite8 (StartAddress++, *(Buffer++)); 
    }

    return ReturnBuffer;
}

BOOLEAN IsPTP()
{
    return 0;
}


UINT8 CrbSupported()
{
    CONTROL_AREA_LAYOUT_PTR ControlAreaPtr = (CONTROL_AREA_LAYOUT_PTR)((UINTN)(CONTROL_AREA_BASE));
    
    DEBUG ((DEBUG_ERROR, "CONTROL_AREA_BASE= %x \n", CONTROL_AREA_BASE));
    DEBUG ((DEBUG_ERROR, "ControlAreaPtr->CommandAddressL = %x \n", ControlAreaPtr->CommandAddressL));
    DEBUG ((DEBUG_ERROR, "ControlAreaPtr->StatusField.Error  = %x \n", ControlAreaPtr->StatusField.Error ));
    
    if(ControlAreaPtr->CommandAddressL == 0 || \
       ControlAreaPtr->CommandAddressL == 0xFFFFFFFF ||
       ControlAreaPtr->StatusField.Error == 1)
        return 0;

    return 1;
}

UINT8 GetCurrentInterfaceType()
{
    DEBUG ((DEBUG_ERROR, "Tpm20crbLibArm Get Current Interface \n"));
    if(CrbSupported())
        return 1;
    else
        return 0;
}



//Make sure the TPM is present before calling this library
//function. Results are not accurate otherwise
UINT8 TisSupported()
{
    UINT16 Cap = *((UINT16 *)(PORT_TPM_IOMEMBASE + 0x30));

    if(IsPTP())
    {

        if(!GetCurrentInterfaceType())return 1;

        Cap = Cap >> 13;

        if(Cap & 0x01)
        {
            return 1;
        }
        return 0;
    }
    return 1;
}


BOOLEAN FIFOSupported()
{
    return 0;
}

BOOLEAN isTpm20CrbPresent()
{
    if(CrbSupported())
    {
        return TRUE;
    }
    return FALSE;
}


/*
BOOLEAN dTPMCrbLocality0Granted(TPM_CRB_ACCESS_REG_PTR dCrbAccessRegPtr)
{
    UINTN       ActiveLocality = 0;
    UINT32     u32TpmlocState = 0;

    u32TpmlocState = dCrbAccessRegPtr->TpmlocState;
    ActiveLocality = u32TpmlocState >> 2;

    if( ((ActiveLocality & 0x7)==0)             &&      // Locality is 0.
            (dCrbAccessRegPtr->TpmlocState & 0x02)  &&      // Locality is assign.
            (dCrbAccessRegPtr->TpmlocState & 0x80))     // TPM is Valid.
    {
        return TRUE;
    }

    return FALSE;
}



EFI_STATUS dTPMCrbSetLocality(TPM_CRB_ACCESS_REG_PTR dCrbAccessRegPtr)
{
    EFI_STATUS  Status = EFI_SUCCESS;
    UINTN       DelayTime = CRB_DELAY_TIMEOUT;
    UINTN       Timeout   = CRB_TIMEOUT_A / CRB_COUNT_TIMEOUT, Count =0;


    while( FALSE == dTPMCrbLocality0Granted(dCrbAccessRegPtr) )
    {
        dCrbAccessRegPtr->TpmlocCtrl = 0x1;
        MicroSecondDelay(DelayTime); //delay 50us
        ++Count;
        if(Count == Timeout)return EFI_DEVICE_ERROR;
    }
    
    return EFI_SUCCESS;
}*/


EFI_STATUS dTPMCrbWaitStrtClr(CONTROL_AREA_LAYOUT_PTR ControlAreaPtr)
{   
    UINTN       DelayTime = CRB_DELAY_TIMEOUT;
    UINTN       Timeout   = 2*1000*10000 / CRB_COUNT_TIMEOUT, Count =0;

    DEBUG ((-1, "dTPMCrbWaitStrtClr:: StartField.Start = %x \n", ControlAreaPtr->StartField.Start));
    while(ControlAreaPtr->StartField.Start != 0x0 &&
            !( ControlAreaPtr->StatusField.Error & 1) )
    {
        if(Count == Timeout) break;
        MicroSecondDelay(DelayTime); //delay 50us
        Count+=1;
    }
    
    if((ControlAreaPtr->StatusField.Error & 1) == 1)
        return EFI_DEVICE_ERROR;

    if(Count == Timeout)return EFI_DEVICE_ERROR;
    return EFI_SUCCESS;
}

UINT8 isTPMIdle(CONTROL_AREA_LAYOUT_PTR ControlAreaPtr)
{
    if((ControlAreaPtr->StatusField.Error & 1) == 1)
    {
        return 0xFF; //FATAL TPM ERROR
    }
    if((ControlAreaPtr->StatusField.TpmIdle & 1) == 1)
    {
        return 1; //idle state
    }
    return 0;
}


EFI_STATUS SetTPMIdle()
{
    UINTN       DelayTime = CRB_DELAY_TIMEOUT;
    UINTN       Timeout   = CRB_TIMEOUT_A / CRB_COUNT_TIMEOUT, Count =0;  //We should be in Timeout_C but 
                                                                          //some TPM's need more time.
    CONTROL_AREA_LAYOUT_PTR ControlAreaPtr =\
                        (CONTROL_AREA_LAYOUT_PTR)(( UINTN ) (CONTROL_AREA_BASE));
    
    if((ControlAreaPtr->StatusField.Error & 1) == 1)
    {
        return 0xFF; //FATAL TPM ERROR
    }
    
    ControlAreaPtr->RequestField.GoIdle = 1;
    while(isTPMIdle(ControlAreaPtr))
    {
        DEBUG ((-1, "SetTPMIdle::isTPMIdle() = %x \n", isTPMIdle(ControlAreaPtr)));
        ControlAreaPtr->RequestField.GoIdle = 1;
        MicroSecondDelay(DelayTime); //delay 50us
        if(Count == Timeout)break;
        Count +=1;
    }
    return EFI_SUCCESS;
}


EFI_STATUS dTPMCrbSetReqReadyState(CONTROL_AREA_LAYOUT_PTR ControlAreaPtr)
{
    UINTN       DelayTime = CRB_DELAY_TIMEOUT;
    UINTN       Timeout   = CRB_TIMEOUT_A / CRB_COUNT_TIMEOUT, Count =0;  //We should be in Timeout_C but 
                                                                          //some TPM's need more time.

    if( (isTPMIdle(ControlAreaPtr)) == 0  )
    {
        return EFI_SUCCESS;
    }

    do
    {
        ControlAreaPtr->RequestField.CmdReady = 0x01;
        MicroSecondDelay(DelayTime); //delay 50us
        if(Count == Timeout)break;
        Count +=1;
    }
    while( (isTPMIdle(ControlAreaPtr)) == 1 );    //wait till ready

    if(Count == Timeout)return EFI_DEVICE_ERROR;
    return EFI_SUCCESS;
}


/*EFI_STATUS dTPMCrbSetReqIdleState(TPM_CRB_ACCESS_REG_PTR dCrbAccessRegPtr)
{
    UINTN       DelayTime = CRB_DELAY_TIMEOUT;
    UINTN       Timeout   = CRB_TIMEOUT_A / CRB_COUNT_TIMEOUT, Count =0; //We should be in Timeout_C but 
                                                                         //some TPM's need more time.
    EFI_STATUS  Status = EFI_SUCCESS;

    // TPM have already in Idle mode
    if( 1 == isTPMIdle(dCrbAccessRegPtr) )
        return EFI_SUCCESS;

    do
    {
        dCrbAccessRegPtr->TpmCrbCtrlReq = 0x2;
        MicroSecondDelay(DelayTime); //delay 100us
        if(Count == Timeout)break;
        Count +=1;
    }
    while( (isTPMIdle(dCrbAccessRegPtr)) == 0 );   //wait till idle

    if(Count == Timeout)return EFI_DEVICE_ERROR;
    return EFI_SUCCESS;
}*/


EFI_STATUS
EFIAPI
CrbSend(
    IN     UINT8      *InputBuffer,
    IN     UINT32     DataLength
)
{
    CONTROL_AREA_LAYOUT_PTR ControlAreaPtr = (CONTROL_AREA_LAYOUT_PTR)(( UINTN ) (CONTROL_AREA_BASE));
    UINTN   CmdBase;
    EFI_STATUS Status;


    if(CrbSupported())
    {
        Status = dTPMCrbSetReqReadyState(ControlAreaPtr);
        if(EFI_ERROR(Status))
        {
            return Status;
        }

        if( ControlAreaPtr->CommandSize == 0 || \
                ControlAreaPtr->CommandAddressL  == 0 ||\
                ControlAreaPtr->ResponseSize == 0 ||
                ControlAreaPtr->ResponseAddressL == 0)
        {
            return EFI_DEVICE_ERROR;
        }

        if(ControlAreaPtr->CommandAddressL !=0)
        {
            CmdBase = (UINTN)(ControlAreaPtr->CommandAddressH << 32 | ControlAreaPtr->CommandAddressL);

            CrbMmioWriteBuffer8(CmdBase, DataLength, InputBuffer);

            Status = dTPMCrbWaitStrtClr(ControlAreaPtr);
            if(EFI_ERROR(Status))return Status;

            ControlAreaPtr->StartField.Start = 1;
            return EFI_SUCCESS;
        }
    }

    return EFI_ABORTED;
}


EFI_STATUS
EFIAPI
CrbReceive(
    OUT     UINT8     *OutBuffer,
    OUT     UINT32    *RespSize
)
{
    CONTROL_AREA_LAYOUT_PTR ControlAreaPtr = (CONTROL_AREA_LAYOUT_PTR)(( UINTN ) (CONTROL_AREA_BASE));
    UINTN RspBase;
    UINT16 Data16;
    UINT32 Data32;
    EFI_STATUS Status;
    DEBUG ((-1, "CrbReceive Entrypoint \n"));
    if(CrbSupported())
    {
         Status = dTPMCrbWaitStrtClr(ControlAreaPtr);

         DEBUG ((-1, "dTPMCrbWaitStrtClr = %r \n", Status));
         
        if(EFI_ERROR(Status))return Status;

        DEBUG ((-1, "ControlAreaPtr->ResponseAddressL = %x \n", ControlAreaPtr->ResponseAddressL));
        DEBUG ((-1, "ControlAreaPtr->ResponseAddressH = %x \n", ControlAreaPtr->ResponseAddressH));
        
        if(ControlAreaPtr->ResponseAddressL !=0)
        {
            RspBase = (UINTN)(ControlAreaPtr->ResponseAddressH << 32 | ControlAreaPtr->ResponseAddressL);

            DEBUG ((-1, "CrbMmioReadBuffer8 reading...."));
            CrbMmioReadBuffer8(RspBase, RESPONSE_HEADER_SIZE, OutBuffer);

            DEBUG ((-1, "..done \n"));
            CopyMem (&Data16, OutBuffer, sizeof (UINT16));

            DEBUG ((-1, "Before SwapBytes16  \n"));
            if(SwapBytes16(Data16) == TPM_ST_RSP_COMMAND)
            {
                return EFI_DEVICE_ERROR;
            }

            DEBUG ((-1, "Before CopyMem2  \n"));
            CopyMem(&Data32, (OutBuffer + 2), sizeof(UINT32));

            DEBUG ((-1, "Before SwapBytes32  \n"));
            *RespSize = SwapBytes32(Data32);

            DEBUG ((-1, "RespSize = %x \n", RespSize));
            
            if(*RespSize > ControlAreaPtr->ResponseSize)
            {
                return EFI_BUFFER_TOO_SMALL;
            }

            if(*RespSize <  sizeof(GENERIC_RESP_HDR))
            {
                return EFI_DEVICE_ERROR;
            }
            
            DEBUG ((-1, "CrbMmioReadBuffer8 final buffer reading...."));

            CrbMmioReadBuffer8(RspBase, *RespSize,  OutBuffer);
            
            DEBUG ((-1, "..done \n"));
            
            return EFI_SUCCESS;
        }
    }

    
    return EFI_ABORTED;
}



EFI_STATUS
EFIAPI
CrbSubmitCmd(
    IN      UINT8     *InputBuffer,
    IN      UINT32     InputBufferSize,
    OUT     UINT8     *OutputBuffer,
    OUT     UINT32    *OutputBufferSize
)
{
    EFI_STATUS Status;
    ARM_SMC_ARGS ArmSmcArgs;

    //CONTROL_AREA_LAYOUT_PTR ControlAreaPtr = (CONTROL_AREA_LAYOUT_PTR)(( UINTN ) (CONTROL_AREA_BASE));

    DEBUG ((-1, "ArmCRB CrbSubmitCmd Entry \n"));
    
    if(InputBuffer == NULL || OutputBuffer == NULL || InputBufferSize == 0)
    {
        DEBUG ((-1, "ArmCRB CrbSubmitCmd EFI_INVALID_PARAMETER \n"));
        return EFI_INVALID_PARAMETER;
    }
    
    DEBUG ((-1, "ArmCRB CrbSubmitCmd CrbSupported = %x  \n", CrbSupported()));
    
    if(CrbSupported())
    {
        Status = CrbSend(InputBuffer, InputBufferSize);
        if (EFI_ERROR (Status))
        {
            DEBUG ((-1, "ArmCRB Send Error = %r \n", Status));
            SetTPMIdle(); //always returns EFI_SUCCESS;
            return Status;
        }
        
        DEBUG ((-1, "ArmCRB Send Status = %r \n", Status));
        //sendsmc
       ArmSmcArgs.Arg0 = SMC_FUNC_ID;
       ArmCallSmc (&ArmSmcArgs);
        

        ///
        /// Receive the response data from TPM
        ///
        Status = CrbReceive(OutputBuffer, OutputBufferSize);
        if (EFI_ERROR (Status))
        {
            DEBUG ((-1, "ArmCRB recv Error = %r \n", Status));
            SetTPMIdle(); //always returns EFI_SUCCESS;
            return Status;
        }
        
        SetTPMIdle(); //always returns EFI_SUCCESS;
        DEBUG ((-1, "ArmCRB recv OK\n"));
        return Status;
     }
    
    DEBUG ((-1, "ArmCRB CrbReceive Status = %r \n", Status));

     return EFI_UNSUPPORTED;
}

