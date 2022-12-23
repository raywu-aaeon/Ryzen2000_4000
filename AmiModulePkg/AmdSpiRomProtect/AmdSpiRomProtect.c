//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
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
/** @file AmdSpiRomProtect.c
    This file contains code for AMD SPI ROM Protect entrypoint

**/

//----------------------------------------------------------------------------
// Includes
// Statements that include other files
#include <PiSmm.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/DebugLib.h>

#include <Token.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <AmiSmm.h>
#include <Protocol/SmmCpu.h>

#include <Protocol/SmmBase2.h>

#if CPUIOTRAP_FLAG
#include <AmiCpuPkg/CPU/Include/Protocol/CpuIoTrapProtocol.h> 
#endif

#define SMM_ENTRY_CODE_OFFS 0x400
//----------------------------------------------------------------------------
// Function Externs
VOID AmdSpiRomProtectWriteEnable (VOID);
VOID AmdSpiRomProtectWriteDisable (VOID);
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Local Variables
#if CPUIOTRAP_FLAG
EFI_EVENT  gEvtCpuIoTrap;
EFI_EVENT  gRegCpuIoTrap;
EFI_GUID   gCpuIoTrapDispatchProtocolGuid           = EFI_CPU_IO_TRAP_DISPATCH_PROTOCOL_GUID;
#endif
volatile UINT8  *gSPIBASE = (UINT8*)(UINTN)SPI_BASE_ADDRESS;



#if CPUIOTRAP_FLAG
/**
    CpuIoTrapCallback1 service for if IO 0xCF9 Trap.

        
    @param Event 
    @param Context 
         
    @retval VOID

**/
VOID 
EFIAPI
CpuIoTrapCallback1(
    IN EFI_HANDLE                  DispatchHandle,
    IN EFI_CPU_IO_TRAP_CONTEXT    *DispatchContext
    )
{
    UINT8 TrapValue;

    TrapValue = (UINT8) ((* (UINT32 *) DispatchContext) & 0xFF);
    if ((TrapValue == 0x06) || (TrapValue == 0x04)|| (TrapValue == 0x02))
    {
    AmdSpiRomProtectWriteEnable ();
    IoWrite8(0xCF9,6);
    EFI_DEADLOOP();
    }
    IoWrite8(0xCF9,TrapValue);
}  


/**
    CpuIoTrapCallback2 service for if IO 0x92 Trap.

        
    @param Event 
    @param Context 
         
    @retval VOID

**/
VOID 
EFIAPI
CpuIoTrapCallback2(
    IN EFI_HANDLE                  DispatchHandle,
    IN EFI_CPU_IO_TRAP_CONTEXT    *DispatchContext
    )
{
    UINT8               TrapValue;

    TrapValue = (UINT8) ((* (UINT32 *) DispatchContext) & 0xFF);
    if (TrapValue == 0x01)
    {
        AmdSpiRomProtectWriteEnable ();
        IoWrite8(0xCF9,6);
        EFI_DEADLOOP();
    }
    IoWrite8(0x92,TrapValue);
}    // end CpuIoTrapCallback2

/**
    CpuIoTrapCallback3 service for if IO 0x64 Trap.

        
    @param Event 
    @param Context 
         
    @retval VOID

**/
VOID 
EFIAPI
CpuIoTrapCallback3(
    IN EFI_HANDLE                  DispatchHandle,
    IN EFI_CPU_IO_TRAP_CONTEXT    *DispatchContext
    )
{
    UINT8               TrapValue;

    TrapValue = (UINT8) ((* (UINT32 *) DispatchContext) & 0xFF);
    if (TrapValue == 0xFE)
    {
        AmdSpiRomProtectWriteEnable ();
        IoWrite8(0xCF9,6);
        EFI_DEADLOOP();
    }
    IoWrite8(0x64,TrapValue);
}  // end CpuIoTrapCallback3




VOID
EFIAPI
CpuIoTrapDispatchProtocolCallBack (
    IN EFI_EVENT        Event, 
    IN VOID             *Context
)
{
	    EFI_CPU_IO_TRAP_DISPATCH_PROTOCOL   *gAmdCpuIoTrapProtocol;
	    EFI_CPU_IO_TRAP_REGISTER_CONTEXT    CpuIoTrapContext;
	    EFI_STATUS                          Status;
	    EFI_HANDLE                          Handle;

	    
	    Status = pBS->LocateProtocol ( &gCpuIoTrapDispatchProtocolGuid,
	                                    NULL,
	                                   &gAmdCpuIoTrapProtocol);
	 
	    if (EFI_ERROR(Status)) return;


	        CpuIoTrapContext.Address = 0xcf9;
		    CpuIoTrapContext.Length = 1;
	    	CpuIoTrapContext.Type = WriteCpuIoTrap;
	        Status = gAmdCpuIoTrapProtocol->Register ( gAmdCpuIoTrapProtocol,
	                                                   CpuIoTrapCallback1,
	                                                  &CpuIoTrapContext,
	                                                  &Handle );


	        CpuIoTrapContext.Address = 0x92;
		    CpuIoTrapContext.Length = 1;
	    	CpuIoTrapContext.Type = WriteCpuIoTrap;
	        Status = gAmdCpuIoTrapProtocol->Register ( gAmdCpuIoTrapProtocol,
	                                                   CpuIoTrapCallback2,
	                                                  &CpuIoTrapContext,
	                                                  &Handle );

	        CpuIoTrapContext.Address = 0x64;
		    CpuIoTrapContext.Length = 1;
	    	CpuIoTrapContext.Type = WriteCpuIoTrap;
	        Status = gAmdCpuIoTrapProtocol->Register (gAmdCpuIoTrapProtocol,
	                                                  CpuIoTrapCallback3,
	                                                  &CpuIoTrapContext,
	                                                  &Handle );


	    pBS->CloseEvent(Event);
}

#endif


/**
    This function initializes Child dispatcher in SMM mode

        
    @param ImageHandle Image handle
    @param SystemTable pointer to system table
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
EFIAPI
InSmmFunction(
    IN EFI_HANDLE          ImageHandle,
    IN EFI_SYSTEM_TABLE    *SystemTable
)
{
	 EFI_STATUS  Status = EFI_SUCCESS;
	 
	     Status = InitAmiSmmLib( ImageHandle, SystemTable );
	     if (EFI_ERROR(Status)) return Status;
#if  CPUIOTRAP_FLAG
	     Status = RegisterProtocolCallback ( &gCpuIoTrapDispatchProtocolGuid,
	                                         CpuIoTrapDispatchProtocolCallBack,
	                                         NULL,
	                                         &gEvtCpuIoTrap,
	                                         &gRegCpuIoTrap );
	     CpuIoTrapDispatchProtocolCallBack (gEvtCpuIoTrap, NULL);
#endif	
         DEBUG ((DEBUG_INFO, "AmdSPiRomProtect.c In Smm.\n"));


    return Status;
}

/**
    OFBD ME Firmware Update InSmm Function

        
    @param ImageHandle Image handle
    @param SystemTable pointer to system table
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
EFIAPI 
AmdSpiRomProtectEnteyPoint(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{

    InitAmiLib (ImageHandle, SystemTable);
    return InitSmmHandler (ImageHandle, SystemTable, \
                                    InSmmFunction, NULL);
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
