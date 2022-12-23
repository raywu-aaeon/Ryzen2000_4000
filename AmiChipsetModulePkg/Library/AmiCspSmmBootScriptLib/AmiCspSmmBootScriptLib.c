//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file AmiCspSmmBootScriptLib.c
    This file contains code for AmiCspSmmBootScriptLib base library.
    To construct this library. First thing is for EDKII boot script.
    We don't want to change other C file who use the original macro that
    AmiChipsetIoLib provided and we also provide the method to access boot script
    in SMM after SMM-LOCK.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
// UDK header
#include <PiDxe.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/S3BootScriptLib.h>
#include <Protocol/S3SaveState.h>
#include <Protocol/DxeSmmReadyToLock.h>
#include <Protocol/SmmCommunication.h>
#include <Guid/EventGroup.h>

#include <Token.h>
// AMI Compatibility header


//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

#define CSP_DECONSTRUCT_SMM_COMMUNICATION_OPCODE	0xAA77

// Type Definition(s)

// Function Prototype(s)
EFI_STATUS
EFIAPI
CspSaveBootScriptToSmm (
  IN CONST EFI_S3_SAVE_STATE_PROTOCOL      *This,
  IN       UINTN                           OpCode,
  ...
  );

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)
EFI_SMM_COMMUNICATION_PROTOCOL 	*gSmmCommunicationProtocol = NULL;
BOOLEAN							gIsSwitchToSmm = FALSE;

EFI_S3_SAVE_STATE_PROTOCOL CspBootScriptWrapper = {
    CspSaveBootScriptToSmm,	// EFI_S3_SAVE_STATE_WRITE   Write;
    NULL,	// EFI_S3_SAVE_STATE_INSERT  Insert;
    NULL,	// EFI_S3_SAVE_STATE_LABEL   Label;
    NULL,	// EFI_S3_SAVE_STATE_COMPARE Compare;
};

UINT8						*gCommunicateBuffer = NULL;
UINT8                       *gBooScriptBuffer = NULL;//edbx Allocate a runtimer buffer before end of dxe for SMM page protection
UINT8                       *gRegBuffer = NULL;//edbx Allocate a runtimer buffer before end of dxe for SMM page protection
UINTN			CONST		gMessageLength = sizeof(VA_LIST);
UINTN						gCommunicateBufferSize = (OFFSET_OF (EFI_SMM_COMMUNICATE_HEADER, Data)) + sizeof(VA_LIST); // Header size (without data) + data size

// GUID Definition(s)
EFI_GUID gAmiCspInternalSmmCommunicationGuid = { 0x28932a0f, 0x3784, 0x4791, { 0xb3, 0x35, 0x33, 0x43, 0x49, 0xaf, 0xca, 0x1c } };
EFI_GUID gAmiCspInternalSmmLockGuid = { 0xb2e3155f, 0x9d2c, 0x4c5b, { 0xb5, 0x7c, 0x87, 0x7e, 0x4b, 0xfd, 0xc6, 0x83 } };


// PPI Definition(s)

// PPI that are installed

// PPI that are notified

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

#ifdef _AUTOGENH_C2F569F8_3668_4171_8BC1_ADD2A0538D88 // only for AmiCspSmmBootScriptSmmLib

#include <PiSmm.h>
#include <Library/SmmServicesTableLib.h>
#include <Protocol/SmmReadyToLock.h>
#include <AmiDxeLib.h>

EFI_S3_SAVE_STATE_PROTOCOL *S3SaveState; // AMI S3BootScriptLib--SmmS3BootScriptLibS3SmmSaveStateProtocol.c

/**
    A smm child dispatcher for smm communication.

    @param SmmImageHandle SMM image handle
    @param CommunicationBuffer pointer to optional communication buffer
    @param SourceSize pointer to size of communication buffer


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
AmiCspSmmBootScriptDispatcher (
  IN EFI_HANDLE           DispatchHandle,
  IN CONST VOID           *DispatchContext OPTIONAL,
  IN OUT VOID             *CommBuffer OPTIONAL,
  IN OUT UINTN            *CommBufferSize OPTIONAL
  )
{
    EFI_STATUS	Status;
    UINT16		OpCode;
    VA_LIST		Marker;

    S3_BOOT_SCRIPT_LIB_WIDTH Width;
    UINT64                Address;
    UINT64                Delay;

    UINTN                 Count;
    UINT8                 *Buffer;

    UINT8                 *Data;
    UINT8                 *DataMask;

    VA_COPY(Marker, *((VA_LIST*)CommBuffer));


    OpCode 		= VA_ARG(Marker, UINT16);
    Width       = VA_ARG (Marker, S3_BOOT_SCRIPT_LIB_WIDTH);
    Address     = VA_ARG (Marker, UINT64);

    switch (OpCode) {
        case EFI_BOOT_SCRIPT_IO_WRITE_OPCODE:
        case EFI_BOOT_SCRIPT_MEM_WRITE_OPCODE:
        case EFI_BOOT_SCRIPT_PCI_CONFIG_WRITE_OPCODE:
            Count       = VA_ARG (Marker, UINTN);
            Buffer      = VA_ARG (Marker, UINT8 *);
        break;

        case EFI_BOOT_SCRIPT_IO_READ_WRITE_OPCODE:
        case EFI_BOOT_SCRIPT_MEM_READ_WRITE_OPCODE:
        case EFI_BOOT_SCRIPT_PCI_CONFIG_READ_WRITE_OPCODE:
            Data        = VA_ARG (Marker, UINT8 *);
            DataMask    = VA_ARG (Marker, UINT8 *);
        break;
        case EFI_BOOT_SCRIPT_MEM_POLL_OPCODE:                              
          Data     = VA_ARG (Marker, VOID *);                                    
          DataMask = VA_ARG (Marker, VOID *);                                    
          Delay    = (UINTN)VA_ARG (Marker, UINT64);   
        break;
        
    }

    switch (OpCode) {
        case EFI_BOOT_SCRIPT_IO_WRITE_OPCODE:
            Status = BOOT_SCRIPT_S3_IO_WRITE_MACRO(
                        S3SaveState,
                        Width,
                        Address,
                        Count,
                        Buffer
                        );
        break;

        case EFI_BOOT_SCRIPT_IO_READ_WRITE_OPCODE:
            Status = BOOT_SCRIPT_S3_IO_READ_WRITE_MACRO(
                        S3SaveState,
                        Width,
                        Address,
                        Data,
                        DataMask
                        );
        break;

        case EFI_BOOT_SCRIPT_MEM_WRITE_OPCODE:
            Status = BOOT_SCRIPT_S3_MEM_WRITE_MACRO(
                        S3SaveState,
                        Width,
                        Address,
                        Count,
                        Buffer
                        );
        break;

        case EFI_BOOT_SCRIPT_MEM_READ_WRITE_OPCODE:
            Status = BOOT_SCRIPT_S3_MEM_READ_WRITE_MACRO(
                        S3SaveState,
                        Width,
                        Address,
                        Data,
                        DataMask
                        );
        break;

        case EFI_BOOT_SCRIPT_PCI_CONFIG_WRITE_OPCODE:
            Status = BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                        S3SaveState,
                        Width,
                        Address,
                        Count,
                        Buffer
                        );
        break;

        case EFI_BOOT_SCRIPT_PCI_CONFIG_READ_WRITE_OPCODE:
            Status = BOOT_SCRIPT_S3_PCI_CONFIG_READ_WRITE_MACRO (
                        S3SaveState,
                        Width,
                        Address,
                        Data,
                        DataMask
                        );
        break;

        case EFI_BOOT_SCRIPT_MEM_POLL_OPCODE:
                          
            Status = BOOT_SCRIPT_S3_MEM_POLL2_MACRO (
                        S3SaveState,
                        Width,
                        Address,
                        DataMask,
                        Data,
                        Delay
                        );
        break;   
        case EFI_BOOT_SCRIPT_SMBUS_EXECUTE_OPCODE:
        case EFI_BOOT_SCRIPT_STALL_OPCODE:
        case EFI_BOOT_SCRIPT_DISPATCH_OPCODE:
        case EFI_BOOT_SCRIPT_DISPATCH_2_OPCODE:
        case EFI_BOOT_SCRIPT_INFORMATION_OPCODE:

        case EFI_BOOT_SCRIPT_PCI_CONFIG2_WRITE_OPCODE:
        case EFI_BOOT_SCRIPT_PCI_CONFIG2_READ_WRITE_OPCODE:
        case EFI_BOOT_SCRIPT_IO_POLL_OPCODE:
        case EFI_BOOT_SCRIPT_PCI_CONFIG_POLL_OPCODE:
        case EFI_BOOT_SCRIPT_PCI_CONFIG2_POLL_OPCODE:
            // TBD
            Status = EFI_UNSUPPORTED;
        break;

        default:
            Status = EFI_UNSUPPORTED;
        break;
    }

    VA_END (Marker);

    if (OpCode == CSP_DECONSTRUCT_SMM_COMMUNICATION_OPCODE && DispatchHandle != NULL) {
    	Status = gSmst->SmiHandlerUnRegister(DispatchHandle);
    }

	DEBUG((DEBUG_INFO|DEBUG_CHIPSET,"AmiCspSmmBootScriptDispatcher OpCode %x Status %r >>\n",OpCode ,Status));

    return Status;
}

/**


    @param Protocol
    @param Interface
    @param Handle


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
CspSmmReadyToLockCallBack (
  IN CONST EFI_GUID  *Protocol,
  IN VOID            *Interface,
  IN EFI_HANDLE      Handle
  )
{
    EFI_STATUS      Status;
    EFI_HANDLE		iHandle = NULL;

//  if (iHandle == NULL) {
        //
        // Because of some module is using TPL_NOTIFY for ReadyToBoot.
        // we have to use our signal guid instead of gEfiDxeSmmReadyToLockProtocolGuid.
        //    otherwise the callback will be entered after them.
        //
        Status = gBS->InstallProtocolInterface(
                          &iHandle,
                          &gAmiCspInternalSmmLockGuid,
                          EFI_NATIVE_INTERFACE,
                          NULL
                          );
        DEBUG((DEBUG_INFO|DEBUG_CHIPSET,"CspSmmReadyToLockCallBack(%r) gIsSwitchToSmm=%x %x \n",Status,gIsSwitchToSmm,iHandle));
//    }

    return Status;
}

/**
    To construct this library in SMM driver. First thing is for EDKII boot script.
    We don't want to change other C file who use the original macro that
    AmiChipsetIoLib provided and we also provide the method to access boot script
    in SMM after SMM-LOCK.

    @retval EFI_SUCCESS   The constructor always returns RETURN_SUCCESS.

**/

EFI_STATUS
EFIAPI
AmiCspSmmBootScriptSmmLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS      Status;
    EFI_HANDLE  	DispatchHandle = NULL;
    VOID			*CspSmmReadyToLockCallBackReg = NULL;

    Status = gSmst->SmiHandlerRegister(AmiCspSmmBootScriptDispatcher, &gAmiCspInternalSmmCommunicationGuid, &DispatchHandle);
    ASSERT_EFI_ERROR(Status);
    Status = gSmst->SmmRegisterProtocolNotify(&gEfiSmmReadyToLockProtocolGuid, CspSmmReadyToLockCallBack, &CspSmmReadyToLockCallBackReg);
    ASSERT_EFI_ERROR(Status);

    return Status;
}

#else

/**
  This is the Event call back function to notify the Library the system is entering
  run time phase.

  @param  Event   Pointer to this event
  @param  Context Event handler private data
 **/
VOID
EFIAPI
CspSwitchBootScriptCallBack (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
    EFI_STATUS				Status = EFI_SUCCESS;

    if (gIsSwitchToSmm == FALSE) {
    	UINTN					*Dummy;

		Status = gBS->LocateProtocol (&gAmiCspInternalSmmLockGuid, NULL, (VOID **) &Dummy);
		if (!EFI_ERROR(Status)) {

			Status = gBS->LocateProtocol (&gEfiSmmCommunicationProtocolGuid, NULL, (VOID **) &gSmmCommunicationProtocol);
			if (!EFI_ERROR(Status)) {
				gIsSwitchToSmm = TRUE;
			}
		}
		if (Event != NULL && gIsSwitchToSmm) gBS->CloseEvent(Event);
    }

	DEBUG((DEBUG_INFO|DEBUG_CHIPSET,"CspSwitchBootScriptCallBack(%r) gIsSwitchToSmm=%x Event=%x \n",Status,gIsSwitchToSmm,Event));
}

/**
  This is the Event call back function to notify the Library the system is entering
  run time phase.

  @param  Event   Pointer to this event
  @param  Context Event handler private data
 **/
VOID
EFIAPI
CspReadyToBootCallBack (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
    EFI_STATUS              Status;

	// deconstruct
	gIsSwitchToSmm = FALSE;

	Status = CspSaveBootScriptToSmm(NULL, CSP_DECONSTRUCT_SMM_COMMUNICATION_OPCODE);

	DEBUG((DEBUG_INFO|DEBUG_CHIPSET,"CspReadyToBootCallBack(%r)Event(%x)\n",Status,Event));

	if (Event != NULL) gBS->CloseEvent(Event);
}

/**
  Check if SMM lock

  @retval TRUE           	SMM is locked.
  @retval FALSE           	SMM is not locked.

**/

BOOLEAN
EFIAPI
CspIsSwitchBootScriptToSmm (
  )
{
    static BOOLEAN	isReady = FALSE;
    EFI_STATUS		Status = EFI_SUCCESS;
    EFI_EVENT		ReadyToLockEvent = NULL;
    EFI_EVENT		ReadyToBootEvent = NULL;

    if (!isReady) {
        VOID		*ReadyToLockReg;

        //
        // Because of some module is using TPL_NOTIFY for ReadyToBoot.
        // we have to use our signal guid instead of gEfiDxeSmmReadyToLockProtocolGuid.
        //    otherwise the callback will be entered after them.
        //
        ReadyToLockEvent = EfiCreateProtocolNotifyEvent  (
        					  &gAmiCspInternalSmmLockGuid, // &gEfiDxeSmmReadyToLockProtocolGuid,
                              TPL_NOTIFY,
                              CspSwitchBootScriptCallBack,
                              NULL,
                              &ReadyToLockReg
                              );
        //####ASSERT (ReadyToLockEvent != NULL); if no smm-lock just leave don't need construct.
        if (ReadyToLockEvent != NULL) {
        	CspSwitchBootScriptCallBack(NULL, NULL);
        }

        // To deconstruct smm communication call.
		Status = gBS->CreateEventEx (
						EVT_NOTIFY_SIGNAL,
						TPL_CALLBACK,
						//###TPL_APPLICATION, // RVA9 : It will never be de-constructed by TPL_APPLICATION. It is unsecured. GnbDxe should change the boot script save behavior.
						CspReadyToBootCallBack,
						NULL,
						&gEfiEventReadyToBootGuid,
						&ReadyToBootEvent
						);
        isReady = TRUE;
        DEBUG((DEBUG_INFO|DEBUG_CHIPSET,"CspIsSwitchBootScriptToSmm(%r) gIsSwitchToSmm=%x RTL<%x> RTB<%x> \n",Status,gIsSwitchToSmm,ReadyToLockEvent,ReadyToBootEvent));
    }

    return gIsSwitchToSmm;
}

/**
    It uses EFI_SMM_COMMUNICATION_PROTOCOL API to transfer data from Non-SMM
    mode to SMM mode.

    @param Buffer - Pointer to data to be transfered
    @param Length - Size of the data
    @param Guid  - Pointer to GUID identifier for the data

    @retval EFI_STATUS

**/
EFI_STATUS
CspBootScriptSmmCommunicate (
    IN  EFI_GUID 	*Guid,
    IN  VOID    	*Buffer
  )
{
    EFI_SMM_COMMUNICATE_HEADER     *SmmCommunicateHeader;
    EFI_STATUS                     Status = EFI_SUCCESS;

    DEBUG((DEBUG_INFO|DEBUG_CHIPSET,"CspBootScriptSmmCommunicate %g\n",Guid));

    if ( Buffer == NULL || gMessageLength == 0 || Guid == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    // Copy SMM Communicate Header Here
    SmmCommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *)gCommunicateBuffer;

    // Copy data GUID
    gBS->CopyMem( &SmmCommunicateHeader->HeaderGuid, Guid, sizeof( EFI_GUID ) );

    // Updated data length
    SmmCommunicateHeader->MessageLength  = gMessageLength;

    // Copy Data Here
    gBS->CopyMem( &SmmCommunicateHeader->Data, Buffer, gMessageLength );

    if (gSmmCommunicationProtocol != NULL) {
        // Send data to SMM using protocol API
        Status = gSmmCommunicationProtocol->Communicate (gSmmCommunicationProtocol, gCommunicateBuffer, &gCommunicateBufferSize);
        //###ASSERT_EFI_ERROR(Status); // comment for unregister call.
    }

    DEBUG((DEBUG_INFO|DEBUG_CHIPSET,"CspBootScriptSmmCommunicate %r\n",Status));

    return Status;
}

/**
  Redirect S3 boot script to SMM.

  @param  This                  A pointer to the EFI_S3_SAVE_STATE_PROTOCOL instance.
  @param  OpCode                The operation code (opcode) number.
  @param  ...                   Argument list that is specific to each opcode.

  @retval EFI_SUCCESS           The operation succeeded. A record was added into the
                                specified script table.
  @retval EFI_INVALID_PARAMETER The parameter is illegal or the given boot script is not supported.
                                If the opcode is unknow or not supported because of the PCD
                                Feature Flags.
  @retval EFI_OUT_OF_RESOURCES  There is insufficient memory to store the boot script.

**/
EFI_STATUS
EFIAPI
CspSaveBootScriptToSmm (
  IN CONST EFI_S3_SAVE_STATE_PROTOCOL      *This,
  IN       UINTN                           OpCode,
  ...
  )
{
    EFI_STATUS  Status;
    VA_LIST		Marker;
    UINT16                      TempOpCode;
    S3_BOOT_SCRIPT_LIB_WIDTH    Width;
    UINT64                      Address;
    UINTN                       Count;
    UINT8                       *Buffer;
    UINT64                      Delay;
    UINT8                       *Data;
    UINT8                       *DataMask;
    UINT8                       *OpData;
    //edbx<

    DEBUG((DEBUG_INFO|DEBUG_CHIPSET,"CspSaveBootScriptToSmm[OpCode]=%x\n",OpCode));
//edbx>Allocate a runtimer buffer before end of dxe for SMM page protection
    if (gBooScriptBuffer != NULL)
    {

        //DEBUG((DEBUG_INFO|DEBUG_CHIPSET,"OpCode %x\n",&OpCode));

        OpData = (UINT8*)gBooScriptBuffer;
        //DEBUG((DEBUG_INFO|DEBUG_CHIPSET,"OpData %x\n",OpData));
        Marker = (VA_LIST)&OpCode; //###VA_START (Marker, This);

        TempOpCode  = VA_ARG(Marker, UINT16);
        //DEBUG((DEBUG_INFO,"After VA_ARG TempOpCode = %x\n", TempOpCode));
        CopyMem(OpData, &TempOpCode, sizeof(UINT16));
        OpData += 8;
        //DEBUG((DEBUG_INFO|DEBUG_CHIPSET,"OpData %x\n",OpData));

        Width       = VA_ARG (Marker, S3_BOOT_SCRIPT_LIB_WIDTH);
        //DEBUG((DEBUG_INFO,"After VA_ARG Width = %x\n", Width));
        CopyMem(OpData, &Width, sizeof(S3_BOOT_SCRIPT_LIB_WIDTH));
        OpData += 8;
        //DEBUG((DEBUG_INFO|DEBUG_CHIPSET,"OpData %x\n",OpData));

        Address     = VA_ARG (Marker, UINT64);
        CopyMem(OpData, &Address, sizeof(UINT64));
        OpData += 8;
        //DEBUG((DEBUG_INFO,"After VA_ARG Address = %x\n", Address));
        //DEBUG((DEBUG_INFO|DEBUG_CHIPSET,"OpData %x\n",OpData));

        switch (TempOpCode) {
            case EFI_BOOT_SCRIPT_IO_WRITE_OPCODE:
            case EFI_BOOT_SCRIPT_MEM_WRITE_OPCODE:
            case EFI_BOOT_SCRIPT_PCI_CONFIG_WRITE_OPCODE:
                Count       = VA_ARG (Marker, UINTN);
                CopyMem(OpData, &Count, sizeof(UINTN));
                OpData += 8;
                //DEBUG((DEBUG_INFO,"After VA_ARG Count = %x\n", Count));
                //DEBUG((DEBUG_INFO|DEBUG_CHIPSET,"OpData %x\n",OpData));

                Buffer      = VA_ARG (Marker, UINT8 *);
                //DEBUG((DEBUG_INFO,"After VA_ARG Buffer = %x\n", Buffer));
                //DEBUG((DEBUG_INFO,"After VA_ARG Buffer content = %x\n", *(UINT32*)Buffer));
                CopyMem(gRegBuffer, Buffer, sizeof(UINT8 *));
                CopyMem(OpData, &gRegBuffer, 8);

            break;

            case EFI_BOOT_SCRIPT_IO_READ_WRITE_OPCODE:
            case EFI_BOOT_SCRIPT_MEM_READ_WRITE_OPCODE:
            case EFI_BOOT_SCRIPT_PCI_CONFIG_READ_WRITE_OPCODE:
                Data        = VA_ARG (Marker, UINT8 *);
                DataMask    = VA_ARG (Marker, UINT8 *);
            break;
            case EFI_BOOT_SCRIPT_MEM_POLL_OPCODE:
              Data     = VA_ARG (Marker, VOID *);
              DataMask = VA_ARG (Marker, VOID *);
              Delay    = (UINTN)VA_ARG (Marker, UINT64);
            break;

        }


        Marker = (VA_LIST)gBooScriptBuffer; //###VA_START (Marker, This);
    }
//  Marker = (VA_LIST)&OpCode; //###VA_START (Marker, This);
//edbx<

    Status = CspBootScriptSmmCommunicate(&gAmiCspInternalSmmCommunicationGuid, &Marker);
    VA_END (Marker);

    DEBUG((DEBUG_INFO|DEBUG_CHIPSET,"CspSaveBootScriptToSmm %r\n",Status));

    return Status;
}

/**
  Return a wrapper function.

  @retval EFI_S3_SAVE_STATE_PROTOCOL           A wrapper.

**/

EFI_S3_SAVE_STATE_PROTOCOL*
EFIAPI
CspGetBootScriptWrapper (
  )
{
    return &CspBootScriptWrapper;
}

/**
    To construct this library. First thing is for EDKII boot script.
    We don't want to change other C file who use the original macro that
    AmiChipsetIoLib provided and we also provide the method to access boot script
    in SMM after SMM-LOCK.

    @retval EFI_SUCCESS   The constructor always returns RETURN_SUCCESS.

**/

EFI_STATUS
EFIAPI
AmiCspSmmBootScriptLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS                  Status;

    //###mReadyToLockEvent = EfiCreateProtocolNotifyEvent  (
    //###                      &gEfiDxeSmmReadyToLockProtocolGuid,
    //###                      TPL_CALLBACK,
    //###                      CspSwitchBootScriptCallBack,
    //###                      NULL,
    //###                      &Registration
    //###                      );
    //###ASSERT (mReadyToLockEvent != NULL); if no smm-lock just leave don't need construct.

    //
    // WSMT required. change the communicate buffer to EfiRuntimeServicesData
    //

    // Allocate memory for Communication Buffer.
    // AllocateRuntimeZeroPool
    Status = gBS->AllocatePool( EfiRuntimeServicesData,
                                gCommunicateBufferSize,
                                (VOID**)&gCommunicateBuffer );
    if ( EFI_ERROR( Status )) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }
    //edbx> Allocate a runtimer buffer before end of dxe for SMM page protection
    if (gBooScriptBuffer == NULL)
        {
            Status = gBS->AllocatePool( EfiRuntimeServicesData,
                                    100,
                                    (VOID**)&gBooScriptBuffer );
            ASSERT_EFI_ERROR(Status);
            ZeroMem(gBooScriptBuffer, 100);
            Status = gBS->AllocatePool( EfiRuntimeServicesData,
                                    8,
                                    (VOID**)&gRegBuffer );
            ASSERT_EFI_ERROR(Status);
            ZeroMem(gRegBuffer, 8);
        }
        DEBUG((DEBUG_INFO|DEBUG_CHIPSET,"gBooScriptBuffer %x\n",gBooScriptBuffer));
        DEBUG((DEBUG_INFO|DEBUG_CHIPSET,"gRegBuffer %x\n",gRegBuffer));
    //edbx<
    //### TBD ###// Free memory allocated for Communication Buffer.
    //### TBD ###gBS->FreePool(gCommunicateBuffer);

    return Status;
}

#endif


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
