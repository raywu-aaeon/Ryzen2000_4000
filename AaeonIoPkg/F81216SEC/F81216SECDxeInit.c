//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  <F81216SECDxeInit.c>
//
// Description: 1. Port SIO DXE initial table and routine for GenericSio.c
//              2. Define SIO bootscriptable table
//
//<AMI_FHDR_END>
//**********************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <AmiDxeLib.h>
#include <AmiGenericSio.h>
#include "F81216SECDxeIoTable.h"

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: F81216SEC_ClearDevResource
//
// Description:
//  This function will Clear SIO resource
//
// Input:
//  SIO_DEV2* dev
// Output:
//  NONE
//
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
VOID F81216SEC_ClearDevResource(
    IN  SIO_DEV2    *dev
)
{

    IoWrite8(F81216SEC_CONFIG_INDEX, F81216SEC_CONFIG_MODE_ENTER_VALUE);
    IoWrite8(F81216SEC_CONFIG_INDEX, F81216SEC_CONFIG_MODE_ENTER_VALUE);

    IoWrite8(F81216SEC_CONFIG_INDEX, F81216SEC_LDN_SEL_REGISTER);
    IoWrite8(F81216SEC_CONFIG_DATA, dev->DeviceInfo->Ldn);

    IoWrite8(F81216SEC_CONFIG_INDEX, F81216SEC_BASE1_HI_REGISTER);
    IoWrite8(F81216SEC_CONFIG_DATA, 0);
    IoWrite8(F81216SEC_CONFIG_INDEX, F81216SEC_BASE1_LO_REGISTER);
    IoWrite8(F81216SEC_CONFIG_DATA, 0);
    IoWrite8(F81216SEC_CONFIG_INDEX, F81216SEC_IRQ1_REGISTER);
    IoWrite8(F81216SEC_CONFIG_DATA, 0);

    IoWrite8(F81216SEC_CONFIG_INDEX, F81216SEC_CONFIG_MODE_EXIT_VALUE);

    return;

}
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: F81216SEC_COM_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_BOARD_INIT_PROTOCOL         *This - AMI Board Int Protocol.
//  IN  UINTN                           *Function - AMI Sdl SIO Init Routine.
//  IN  OUT VOID                        *ParameterBlock - SIO Component Initialization Routine Parameters Block...
//
// Output:
//  EFI_SUCCESS - Initial step sucessfully
//  EFI_INVALID_PARAMETER - not find the initial step
//
// Modified:  Nothing
//
// Referrals: None
//
// Notes:
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
#if F81216SEC_SERIAL_PORT1_PRESENT | F81216SEC_SERIAL_PORT2_PRESENT|F81216SEC_SERIAL_PORT3_PRESENT | F81216SEC_SERIAL_PORT4_PRESENT
EFI_STATUS F81216SEC_COM_Init(
    IN AMI_BOARD_INIT_PROTOCOL     *This,
    IN UINTN                    *Function,
    IN OUT VOID                 *ParameterBlock
)
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK  *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                   InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL             *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;

    EFI_STATUS                      Status=EFI_SUCCESS;
    SIO_DEV2                        *dev=(SIO_DEV2*)AmiSio;
    UINT8                           rv; //ComMode Register
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
        // Clear Device Resource?
        if((!dev->DeviceInfo->Implemented) || (!dev->NvData.DevEnable)) {
            F81216SEC_ClearDevResource(dev);
        }
        break;

    case isPrsSelect:
        break;

    case isBeforeActivate:
//RayWu, REMOVE 2015/03/06 >>
//        //Only decode UART1/UART2. More others UART port is decode in PEI
//        //Attention! Remove the more com ports to PEI decode.
//        if(dev->DeviceInfo->Uid < 0x02) {
//            //Decode?
//            if(dev->DeviceInfo->Implemented && dev->NvData.DevEnable) {
//                AmiSioLibSetLpcDeviceDecoding(PciIo,dev->VlData.DevBase1, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
//            } else {
//                AmiSioLibSetLpcDeviceDecoding(PciIo,0, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
//            }
//        }
//RayWu, REMOVE 2015/03/06 <<
//        // Program COM RS485/RS232 Mode Registers and  COM Clock Source Registers.
//        if(F81216SEC_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].AndData8 == 0xFF) {
//            rv=F81216SEC_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].OrData8;
//        } else {
//            Status=AmiSio->Access(AmiSio, FALSE, FALSE, F81216SEC_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].Reg8,&rv);
//            ASSERT_EFI_ERROR(Status);
//            rv &= F81216SEC_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].AndData8;
//            rv |= F81216SEC_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].OrData8;
//        }
//        Status=AmiSio->Access(AmiSio,TRUE,FALSE,F81216SEC_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].Reg8,&rv);
//        ASSERT_EFI_ERROR(Status);
//        //Programm Device Mode register here(if NEEDED)use AmiSioProtocol
//        //AMI_TODO: You can program device mode as follow:
//        if(dev->DeviceInfo->Uid == 0x10)    {
//            Status=AmiSio->Access(AmiSio,FALSE,FALSE,0xF1,&rv);
//            ASSERT_EFI_ERROR(Status);
//            if(EFI_ERROR(Status))return Status;
//            //clear Bit4~2 where COM Port mode is:
//            rv &= 0xE3;
//            switch (dev->NvData.DevMode) {
//            case 0:
//                rv |= 0x00;    //Bit4~2 = 000, Disable IR1 function
//                break;
//            case 1:
//                rv |= 0x10;    //Bit4~2 = 100, Enable IR1 function, active pulse is 1.6uS,Full Duplex
//                break;
//            case 2:
//                rv |= 0x14;    //Bit4~2 = 101, Enable IR1 function, active pulse is 1.6uSe,Half Duplex
//                break;
//            case 3:
//                rv |= 0x18;    //Bit4~2 = 110, Enable IR1 function, active pulse is 3/16 bit time,Full Duplex
//                break;
//            case 4:
//                rv |= 0x1C;    //Bit4~2 = 111, Enable IR1 function, active pulse is 3/16 bit time,Half Duplex
//                break;
//
//            default:
//                return EFI_INVALID_PARAMETER;
//            }
//            Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xF1,&rv);
//            ASSERT_EFI_ERROR(Status);
//
//            if (dev->NvData.DevMode > 0) {
//                //Get DSDT.. we have to update it.
//                ACPI_HDR                        *dsdt;
//                EFI_PHYSICAL_ADDRESS            a;
//
//                Status=LibGetDsdt(&a,EFI_ACPI_TABLE_VERSION_ALL);
//                if(EFI_ERROR(Status)) {
//                    SIO_TRACE((TRACE_SIO,"F81216SEC_COM_Init: Fail to Get DSDT - returned %r\n", Status));
//                    ASSERT_EFI_ERROR(Status);
//                } else dsdt=(ACPI_HDR*)a;
//                Status=UpdateAslNameOfDevice(dsdt, dev->DeviceInfo->AslName, "_HID", 0x1005D041);
//                ASSERT_EFI_ERROR(Status);
//                //Checksum
//                dsdt->Checksum = 0;
//                dsdt->Checksum = ChsumTbl((UINT8*)dsdt, dsdt->Length);
//            }
//        }
        //Programm Device to PCI IRQ shanre mode
        if((dev->DeviceInfo->Flags & SIO_SHR_IRQ1) && dev->ResOwner) {
            //Programm ResOwner
            Status=AmiSio->Access((AMI_SIO_PROTOCOL *)dev->ResOwner,FALSE,FALSE,0x70,&rv);
            ASSERT_EFI_ERROR(Status);
            rv &= 0xCF;
            rv |= ((F81216SEC_URIRQ_MODE << 5) | (F81216SEC_URIRQ_SHAR << 4));  //Bit4 = 1: IRQ is ahring with other device
            //Bit5 = 0: PCI IRQ sharing mode
            Status=AmiSio->Access((AMI_SIO_PROTOCOL *)dev->ResOwner,TRUE,FALSE,0x70,&rv);
            ASSERT_EFI_ERROR(Status);
            //Programm Device
            Status=AmiSio->Access(AmiSio,FALSE,FALSE,0x70,&rv);
            ASSERT_EFI_ERROR(Status);
            rv &= 0xCF;
            rv |= ((F81216SEC_URIRQ_MODE << 5) | (F81216SEC_URIRQ_SHAR << 4));  //Bit4 = 1: IRQ is ahring with other device
            //Bit5 = 0: PCI IRQ sharing mode
            Status=AmiSio->Access(AmiSio,TRUE,FALSE,0x70,&rv);
            ASSERT_EFI_ERROR(Status);
        }
        break;

    case isGetModeData:
//        if(dev->DeviceInfo->Uid == 0x10) {
//            //IRDA Has 4 possible modes
//            //Make sure Device Mode Strings are Static VAR!
//            //Otherwise The string will gone after control flow leave this function
//            static CHAR16 IrdaModeStr1[] = L"Standard Serial Port Mode";
//            static CHAR16 IrdaModeStr2[] = L"IrDA Active pulse 1.6 uS,Full Duplex";
//            static CHAR16 IrdaModeStr3[] = L"IrDA Active pulse 1.6 uS,Half Duplex";
//            static CHAR16 IrdaModeStr4[] = L"IrDA Active pulse 3/16 bit time,Full Duplex";
//            static CHAR16 IrdaModeStr5[] = L"IrDA Active pulse 3/16 bit time,Half Duplex";
//            static CHAR16 IrdaModeHelp[] = L"Change the Serial Port mode. Enable, Disable and Configure IR function.";
//            //---------------------------------------------------
//            dev->DevModeCnt=5;
//            //Make room for 2 floppy modes + Help String...
//            dev->DevModeStr=MallocZ(sizeof(CHAR16*)*(dev->DevModeCnt+1));
//            if(dev->DevModeStr==NULL) {
//                Status=EFI_OUT_OF_RESOURCES;
//                ASSERT_EFI_ERROR(Status);
//                return Status;
//            }
//            dev->DevModeStr[0]=&IrdaModeStr1[0];
//            dev->DevModeStr[1]=&IrdaModeStr2[0];
//            dev->DevModeStr[2]=&IrdaModeStr3[0];
//            dev->DevModeStr[3]=&IrdaModeStr4[0];
//            dev->DevModeStr[4]=&IrdaModeStr5[0];
//            dev->DevModeStr[5]=&IrdaModeHelp[0];
//        }
        break;

    case isAfterActivate:
        break;

    case isAfterBootScript:
        break;

#if  AMI_SIO_MINOR_VERSION >= 6     
    case isAfterSmmBootScript:      
        break;
#endif

    default:
        Status=EFI_INVALID_PARAMETER;
    }//switch
    return Status;
}
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

