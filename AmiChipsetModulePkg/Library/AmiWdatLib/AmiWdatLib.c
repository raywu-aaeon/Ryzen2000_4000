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

/** @file AmiWdatLib.c
    Library Class for Wdat routines.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#include <AmiDxeLib.h>
#include <Wdat2/Wdat.h>
#include <Token.h>
#include <Library/AmiWdatLib.h>
#include <IndustryStandard/Acpi.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)
#define REBOOT_REG      0x0  /// **PORTING IS REQUIRED**
//#define WDT_BASE_ADDRESS    0xFEB00000


///WDAT Header
///                 {WatchdogHeaderLength, PciSegment, PciBusNumber, PciDeviceNumber, PciFuncitonNumber, Reserved1[3], TimerPeriod, MaximumCount, MinimumCount, WatchdogFlags, Reserved2[3], NumberWactchdogInstructionEntries};
WDAT_HDR	WdatHdr = {0, SB_WDAT_PCI_SEG, SB_WDAT_PCI_BUS, SB_WDAT_PCI_DEV, SB_WDAT_PCI_FUN, 0,0,0, SB_WDAT_TIMER_PERIOD, SB_WDAT_MAX_COUNT, SB_WDAT_MIN_COUNT, SB_WDAT_FLAG, 0,0,0, 0};

/// Watchdog Action Instruction Table
///      {WatchdogAction                    ,InstructionFlags                       ,Reserved1  ,RegisterRegion.AddrSpcID,RegisterRegion.RegBitWidth,RegisterRegion.RegBitOffs,RegisterRegion.AccessSize,RegisterRegion.Address, Value, Mask };
/// WatchdogAction: Please refer to Watchdog Actions (WDA) Value defined in Wdat.h.
/// InstructionFlags: Please refer to Watchdog Instruction(WDI) Flags Value defined in Wdat.h.
/// RegisterRegion.AddrSpcID: Please refer to Generic Address Space Address IDs defined in Acpi50.h.
/// Note: PORTING IS REQUIRED for NewActionTable.
/// Sample for Watchdog Action Instruction Table
WDAT_INST_ENTRY NewActionTable[] = {
         //### Template ###{WDA_RESET                         ,WDI_WRITE_VALUE|WDI_PRESERVE_REGISTER      ,0    ,EFI_ACPI_5_0_SYSTEM_IO     ,8    ,0    ,1    ,PM_BASE_ADDRESS + 0x57   ,BIT7   ,BIT7 },
         //### Template ###{WDA_QUERY_CURRENT_COUNTDOWN_PERIOD,WDI_READ_COUNTDOWN                         ,0    ,EFI_ACPI_5_0_SYSTEM_IO     ,16   ,0    ,2    ,PM_BASE_ADDRESS + 0x54   ,0x0    ,0x3ff},
         //### Template ###{WDA_QUERY_COUNTDOWN_PERIOD        ,WDI_READ_COUNTDOWN                         ,0    ,EFI_ACPI_5_0_SYSTEM_IO     ,16   ,0    ,2    ,PM_BASE_ADDRESS + 0x54   ,0x0    ,0x3ff},
         //### Template ###{WDA_SET_COUNTDOWN_PERIOD          ,WDI_WRITE_COUNTDOWN|WDI_PRESERVE_REGISTER  ,0    ,EFI_ACPI_5_0_SYSTEM_IO     ,16   ,0    ,2    ,PM_BASE_ADDRESS + 0x54   ,0x0    ,0x3ff},
         //### Template ###{WDA_QUERY_RUNNING_STATE           ,WDI_READ_VALUE                             ,0    ,EFI_ACPI_5_0_SYSTEM_IO     ,8    ,0    ,1    ,PM_BASE_ADDRESS + 0x55   ,0xe0   ,0xe0 },
         //### Template ###{WDA_SET_RUNNING_STATE             ,WDI_WRITE_VALUE|WDI_PRESERVE_REGISTER      ,0    ,EFI_ACPI_5_0_SYSTEM_IO     ,8    ,0    ,1    ,PM_BASE_ADDRESS + 0x55   ,0xe0   ,0xe0 },
         //### Template ###{WDA_QUERY_STOPPED_STATE           ,WDI_READ_VALUE                             ,0    ,EFI_ACPI_5_0_SYSTEM_IO     ,8    ,0    ,1    ,PM_BASE_ADDRESS + 0x55   ,0x0    ,0xe0 },
         //### Template ###{WDA_SET_STOPPED_STATE             ,WDI_WRITE_VALUE|WDI_PRESERVE_REGISTER      ,0    ,EFI_ACPI_5_0_SYSTEM_IO     ,8    ,0    ,1    ,PM_BASE_ADDRESS + 0x55   ,0x0    ,0xe0 },
         //### Template ###{WDA_QUERY_REBOOT                  ,WDI_READ_VALUE                             ,0    ,EFI_ACPI_5_0_SYSTEM_MEMORY ,32   ,0    ,3    ,REBOOT_REG   ,0x0    ,0x2},
         //### Template ###{WDA_SET_REBOOT                    ,WDI_WRITE_VALUE|WDI_PRESERVE_REGISTER      ,0    ,EFI_ACPI_5_0_SYSTEM_MEMORY ,32   ,0    ,3    ,REBOOT_REG   ,0x0    ,0x2},
         //### Template ###{WDA_QUERY_SHUTDOWN                ,WDI_READ_VALUE                             ,0    ,EFI_ACPI_5_0_SYSTEM_IO     ,16   ,0    ,2    ,0x40A   ,0x10   ,0x30},
         //### Template ###{WDA_SET_SHUTDOWN                  ,WDI_WRITE_VALUE|WDI_PRESERVE_REGISTER      ,0    ,EFI_ACPI_5_0_SYSTEM_IO     ,16   ,0    ,2    ,0x40A   ,0x10   ,0x30},
         //### Template ###{WDA_QUERY_WATCHDOG_STATUS         ,WDI_READ_VALUE                             ,0    ,EFI_ACPI_5_0_SYSTEM_IO     ,8    ,0    ,1    ,PM_BASE_ADDRESS + 0x56   ,BIT7   ,BIT7},
         //### Template ###{WDA_SET_WATCHDOG_STATUS           ,WDI_WRITE_VALUE|WDI_PRESERVE_REGISTER      ,0    ,EFI_ACPI_5_0_SYSTEM_IO     ,8    ,0    ,1    ,PM_BASE_ADDRESS + 0x56   ,BIT7   ,BIT7}};
		///
		///	RVA9
		/// The following table from WDAP1 label 04 of AMD module part. check later
		/// RVA9
		///
//                       WatchdogAction,                          InstructionFlags, Reserved1,   AddrSpcID, RegBitWidth, RegBitOffs, AccessSize,            Address, Value,   Mask};
	    {                         WDA_RESET,     WDI_WRITE_VALUE|WDI_PRESERVE_REGISTER,         0, EFI_ACPI_5_0_SYSTEM_MEMORY,          32,          0,          3,   WDT_BASE_ADDRESS,  0x80,   0x80}, //RestartCount
	    {WDA_QUERY_CURRENT_COUNTDOWN_PERIOD,                        WDI_READ_COUNTDOWN,         0, EFI_ACPI_5_0_SYSTEM_MEMORY,          32,          0,          3, WDT_BASE_ADDRESS+4,  0x00, 0xFFFF}, //QCurCountPer
	    {          WDA_SET_COUNTDOWN_PERIOD, WDI_WRITE_COUNTDOWN|WDI_PRESERVE_REGISTER,         0, EFI_ACPI_5_0_SYSTEM_MEMORY,          32,          0,          3, WDT_BASE_ADDRESS+4,  0X00, 0xFFFF}, //SetCountPer
	    {           WDA_QUERY_RUNNING_STATE,                            WDI_READ_VALUE,         0, EFI_ACPI_5_0_SYSTEM_MEMORY,          32,          0,          3,   WDT_BASE_ADDRESS,  0x01,   0x01}, //QRunState
	    {             WDA_SET_RUNNING_STATE,     WDI_WRITE_VALUE|WDI_PRESERVE_REGISTER,         0, EFI_ACPI_5_0_SYSTEM_MEMORY,          32,          0,          3,   WDT_BASE_ADDRESS,  0x01,   0x01}, //SetRunState
	    {           WDA_QUERY_STOPPED_STATE,                            WDI_READ_VALUE,         0, EFI_ACPI_5_0_SYSTEM_MEMORY,          32,          0,          3,   WDT_BASE_ADDRESS,  0x00,   0x01}, //QStopState
	    {             WDA_SET_STOPPED_STATE,     WDI_WRITE_VALUE|WDI_PRESERVE_REGISTER,         0, EFI_ACPI_5_0_SYSTEM_MEMORY,          32,          0,          3,   WDT_BASE_ADDRESS,  0x00,   0x01}, //SetStopState
	    {                  WDA_QUERY_REBOOT,                            WDI_READ_VALUE,         0, EFI_ACPI_5_0_SYSTEM_MEMORY,          32,          0,          3,   WDT_BASE_ADDRESS,  0x00,   0x04}, //QReboot
	    {                    WDA_SET_REBOOT,     WDI_WRITE_VALUE|WDI_PRESERVE_REGISTER,         0, EFI_ACPI_5_0_SYSTEM_MEMORY,          32,          0,          3,   WDT_BASE_ADDRESS,  0x00,   0x04}, //SetReboot
	    {                WDA_QUERY_SHUTDOWN,                            WDI_READ_VALUE,         0, EFI_ACPI_5_0_SYSTEM_MEMORY,          32,          0,          3,   WDT_BASE_ADDRESS,  0x04,   0x04}, //QSchutdown
	    {                  WDA_SET_SHUTDOWN,     WDI_WRITE_VALUE|WDI_PRESERVE_REGISTER,         0, EFI_ACPI_5_0_SYSTEM_MEMORY,          32,          0,          3,   WDT_BASE_ADDRESS,  0x04,   0x04}, //SetSchutdown
	//###    {         WDA_QUERY_WATCHDOG_STATUS,                           WDI_WRITE_VALUE,         0,  EFI_ACPI_5_0_SYSTEM_IO,           8,          0,          1, BIOSRAM_INDEX_PORT,  0xEF,   0xFF}, //QWdtStatus0
	    {         WDA_QUERY_WATCHDOG_STATUS,                            WDI_READ_VALUE,         0,  EFI_ACPI_5_0_SYSTEM_MEMORY,           32,          0,          3,  WDT_BASE_ADDRESS,  0x02,   0x02}, //QWdtStatus1
	    {           WDA_SET_WATCHDOG_STATUS,     WDI_WRITE_VALUE|WDI_PRESERVE_REGISTER,         0,  EFI_ACPI_5_0_SYSTEM_MEMORY,           32,          0,          3, WDT_BASE_ADDRESS,  0x02,   0x02}, //SetWdtStatus0
	//###    {           WDA_SET_WATCHDOG_STATUS,     WDI_WRITE_VALUE|WDI_PRESERVE_REGISTER,         0,  EFI_ACPI_5_0_SYSTEM_IO,           8,          0,          1,  BIOSRAM_DATA_PORT,  0x00,   0x01}  //SetWdtStatus1
};

///--------------------------------------------------------------------------

/**
    Create ActionTable, retrieve data and ActionTableLen
    
    @retval ActionTable A pointer to ActionTable data.  
    
**/
WDAT_INST_ENTRY*
CreateActionTableAndRetrieveIt(
		OUT UINT32			*ActionTableLen)
{
	EFI_STATUS	Status;
	WDAT_INST_ENTRY	*ActionTable;

	*ActionTableLen = sizeof(NewActionTable) / sizeof(WDAT_INST_ENTRY);
	
	Status = pBS->AllocatePool(EfiBootServicesData, sizeof(NewActionTable), &ActionTable);
	ASSERT(Status == EFI_SUCCESS);
	
	MemCpy(ActionTable, NewActionTable, sizeof(NewActionTable));
	
	return ActionTable;
}

/**
    Override the default Wdat Header and Action instruction table
    
    @retval EFI_SUCCESS Always returns EFI_SUCCESS.  
    
**/
EFI_STATUS
WdatHeaderAndActionTableOverride(
		IN WDA_TABLE 		*pWdatTable,
		IN WDAT_INST_ENTRY	*ActionTable,
		IN UINT32			*ActionTableLen)
{
	UINT64		WdatInstTableLen;
	UINT8		*ActInsEtnry = (UINT8*)pWdatTable + sizeof(EFI_ACPI_DESCRIPTION_HEADER) + sizeof(WDAT_HDR);
	
	WdatInstTableLen = *ActionTableLen * sizeof(WDAT_INST_ENTRY);
	WdatHdr.WatchdogHeaderLength = sizeof(WDAT_HDR);
	WdatHdr.NumberWactchdogInstructionEntries = *ActionTableLen;
	MemCpy(&pWdatTable->WatchdogHeader, &WdatHdr, sizeof(WDAT_HDR));
	MemCpy(ActInsEtnry, ActionTable,(UINTN)WdatInstTableLen);

	return EFI_SUCCESS;
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
