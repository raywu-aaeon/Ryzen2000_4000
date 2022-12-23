//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file Kbccore.c
    It has function for port 60 read, 60 write, 64 read and 64 write

**/

//---------------------------------------------------------------------------

#include "KbcEmul.h"
#include "Kbc.h"
#if UHCI_EMUL_SUPPORT
#include "KbcUhci.h"
#endif
#if OHCI_EMUL_SUPPORT
#include "KbcOhci.h"
#endif
#if SB_EMUL_SUPPORT
#include "KbcSb.h"
#endif
#if IOTRAP_EMUL_SUPPORT
#include "KbcIoTrap.h"
#endif

//---------------------------------------------------------------------------

BOOLEAN         AcpiEmulationDisable=FALSE;
extern KBC*     gVirtualKBC;
#define SYNC_SMI_BIT  (1 << 0)

/**
    FindSMICpu

    In a Multiprocessor environment, any logical CPU can generate
    the SMI. This function finds the CPU that generates SMI by accessing
    IO 60/64 Ports

    @param       None

    @retval      UINT8

**/

UINT8
FindSMICpu(
    UINT16                      IoPort,
    EFI_SMM_SAVE_STATE_IO_TYPE  IoType
)
{
    UINT8                       CpuIndex;
    EFI_SMM_SAVE_STATE_IO_INFO  IoInfo;
    EFI_STATUS                  Status;

    for (CpuIndex = 0; CpuIndex < gSmst1->NumberOfCpus; CpuIndex++) {

       Status = SmmCpuProtocol->ReadSaveState(
                            SmmCpuProtocol,
                            sizeof(EFI_SMM_SAVE_STATE_IO_INFO),
                            EFI_SMM_SAVE_STATE_REGISTER_IO,
                            CpuIndex,
                            (VOID*)&IoInfo
                            );
       //In a multiprocessor environment, it may return wrong SMI generated CPU index 
       //while accessing 60/64 ports. To avoid that added the below checks.
       if (EFI_ERROR(Status) || IoInfo.IoPort != IoPort || IoInfo.IoType != IoType || \
               IoInfo.IoWidth != EFI_SMM_SAVE_STATE_IO_WIDTH_UINT8) {
           continue;
       }
       return CpuIndex;
    }

    return 0xFF;
}

/**
    getTrapAL

    Get the port 60 or 64 input value from the CPU save reg

    @param       None

    @retval      UINT8

**/

UINT8
GetTrapAL(
    UINT16                      IoPort,
    EFI_SMM_SAVE_STATE_IO_TYPE  IoType
)
{

#if UHCI_EMUL_SUPPORT || SB_EMUL_SUPPORT ||	IOTRAP_EMUL_SUPPORT

    UINT8       CpuIndex;
    UINT8       TrapAl=0xFF;
    
    CpuIndex = FindSMICpu (IoPort, IoType);
    ASSERT (CpuIndex != 0xFF);

    SmmCpuProtocol->ReadSaveState(
                            SmmCpuProtocol,
                            1,
                            EFI_SMM_SAVE_STATE_REGISTER_RAX,
                            CpuIndex,
                            &TrapAl
                            );
    return TrapAl;

#else
    return GetHceInput();
#endif

}

/**
    setTrapAL

    Set the port 60 or 64 output value to the CPU save reg

    @param       data

    @retval      VOID

**/

VOID
SetTrapAL(
    UINT8                       Data,
    UINT16                      IoPort,
    EFI_SMM_SAVE_STATE_IO_TYPE  IoType
)
{

#if UHCI_EMUL_SUPPORT || SB_EMUL_SUPPORT || IOTRAP_EMUL_SUPPORT
    UINT8   CpuIndex;

    CpuIndex = FindSMICpu(IoPort, IoType);
    ASSERT (CpuIndex != 0xFF);

    SmmCpuProtocol->WriteSaveState(
                            SmmCpuProtocol,
                            1,
                            EFI_SMM_SAVE_STATE_REGISTER_RAX,
                            CpuIndex,
                            &Data
                            );
#endif

}

/**
    trap64w

    This function handles the Port64 write command

    @param       None

    @retval      VOID

**/

VOID
trap64w ()
{
    (*gVirtualKBC->kbc_write_command)( gVirtualKBC,GetTrapAL(0x64, EFI_SMM_SAVE_STATE_IO_TYPE_OUTPUT) );
}

/**
    trap60w

    This function handles the Port60 write command

    @param       None

    @retval      VOID

**/

VOID
trap60w ()
{
    (*gVirtualKBC->kbc_write_data)( gVirtualKBC,GetTrapAL(0x60, EFI_SMM_SAVE_STATE_IO_TYPE_OUTPUT) );
}

/**
    trap64r

    This function handles the Port64 Read command

    @param       None

    @retval      VOID

**/

VOID
trap64r ()
{
    SetTrapAL((*gVirtualKBC->kbc_read_status)(gVirtualKBC), 0x64, EFI_SMM_SAVE_STATE_IO_TYPE_INPUT);
}

/**
    trap60r

    This function handles the Port60 Read command

    @param       None

    @retval      VOID

**/

VOID
trap60r ()
{
    SetTrapAL((*gVirtualKBC->kbc_read_data)(gVirtualKBC), 0x60, EFI_SMM_SAVE_STATE_IO_TYPE_INPUT);
}

/**
    SmmGetTrapStatus

    return the port 6064 trap status

    @param       None

    @retval      BOOLEAN

**/

BOOLEAN SmmGetTrapStatus()
{
#if UHCI_EMUL_SUPPORT
    return Uhci_HasTrapStatus();
#endif
#if OHCI_EMUL_SUPPORT
    return Ohci_HasTrapStatus();
#endif
#if SB_EMUL_SUPPORT
    return Sb_HasTrapStatus();
#endif
#if IOTRAP_EMUL_SUPPORT
    return IoTrap_HasTrapStatus();
#endif
    return FALSE;
}

/**
    TrapEnable

    Enable/disable the port6064 tra

    @param       BOOLEAN

    @retval      BOOLEAN

**/

BOOLEAN TrapEnable(BOOLEAN b)
{

    if(AcpiEmulationDisable) {
        return FALSE;
    }

#if UHCI_EMUL_SUPPORT
    return Uhci_TrapEnable(b);
#endif
#if OHCI_EMUL_SUPPORT
    return Ohci_TrapEnable(b);
#endif
#if SB_EMUL_SUPPORT
    return Sb_TrapEnable(b);
#endif    
#if IOTRAP_EMUL_SUPPORT
    return IoTrapEnable(b);
#endif
    return TRUE;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************


