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

/** @file AmiFchUartDebuggerGpioLib.c
    This file contains code for AmiFchUartDebuggerGpioLib PEIM library.
    The purpose is to override the CPM GPIO to keep UART function PIN for AMI debugger.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
// UDK header
#include <Library/BaseLib.h>
#include <Library/PeiServicesLib.h>

#include <AmdCpmPei.h>
#include <Pei/AmdCpmOemInitPei/AmdCpmOemInitPeim.h>

#include <Token.h>
// AMI Compatibility header


//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------

EFI_STATUS
EFIAPI
FchUartGpioOverrideCallBack (
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
  );

STATIC CONST EFI_PEI_NOTIFY_DESCRIPTOR  gAmdCpmOverrideTableNotifyList =
{
	(EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
	&gAmdCpmOverrideTablePpiGuid,
	FchUartGpioOverrideCallBack,
};

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------


// Function Definition(s)

//---------------------------------------------------------------------------


/**
    This function is called while CPM table override notification.
    Also CRB provides a sample to change GPIO setting depend on BIOS-SETUP.
    The following usage of CPM interface shows how to change original CPM GPIO table.

    @param PeiServices Pointer to PeiServices
    @param NotifyDesc Pointer to NotifyDesc
    @param InvokePpi

    @retval EFI_STATUS EFI_SUCCESS

**/
EFI_STATUS
EFIAPI
FchUartGpioOverrideCallBack (
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
  )
{
	EFI_STATUS					Status;
	UINT32						i;
	AMD_CPM_TABLE_PPI			*CpmTablePpiPtr;
	AMD_CPM_GPIO_INIT_TABLE		*GpioTablePtr;
	AMD_CPM_GPIO_ITEM			GpioOverrideTbl[] = {
			//
			// The original table in the CPM. (AmdCpmPkg\Addendum\Oem\MandolinPco\Pei\AmdCpmOemInitPei\AmdCpmOemTable.c)
			//		ORG : PIN is EGPIO
			//

			//
			//		MOD : PIN is UART0 function pin.  (For SerialRedirection and SerialDebugger both RX/TX pin should be available) (For debug message only TX pin)
			//
	#if (FCH_UART_DEBUG_SELECT == 1)
			GPIO_DEF_V2 (0, 0, 135, GPIO_FUNCTION_0, GPIO_NA, 	GPIO_PU_PD_DIS), // Set to UART0_CTS_L
			GPIO_DEF_V2 (0, 0, 136, GPIO_FUNCTION_0, GPIO_NA,	GPIO_PU_PD_DIS), // UART0_RXD/EGPIO136
			GPIO_DEF_V2 (0, 0, 137, GPIO_FUNCTION_0, GPIO_NA,  	GPIO_PU_PD_DIS), // UART0_RTS_L/EGPIO137 // APU_NFC_DWL_REQ#
			GPIO_DEF_V2 (0, 0, 138, GPIO_FUNCTION_0, GPIO_NA,	GPIO_PU_PD_DIS), // UART0_TXD/EGPIO138 // APU_NFC_WAKE#
			GPIO_DEF_V2 (0, 0, 139, GPIO_FUNCTION_0, GPIO_NA,	GPIO_PU_PD_DIS), // UART0_INTR/AGPIO139 // TPM_PIRQ#
	#endif

			//
			//		MOD : PIN is UART1 function pin.  (For SerialRedirection and SerialDebugger both RX/TX pin should be available) (For debug message only TX pin)
			//
	#if (FCH_UART_DEBUG_SELECT == 2)
			GPIO_DEF_V2 (0, 0, 140, GPIO_FUNCTION_0, GPIO_NA,  	GPIO_PU_PD_DIS), // UART1_CTS_L/UART3_TXD/EGPIO140 // MXM_RESET#
			GPIO_DEF_V2 (0, 0, 141, GPIO_FUNCTION_0, GPIO_NA,  	GPIO_PU_PD_DIS), // UART1_RXD/EGPIO141 // MXM_POWER_ENABLE
			GPIO_DEF_V2 (0, 0, 142, GPIO_FUNCTION_0, GPIO_NA, 	GPIO_PU_PD_DIS), // UART1_RTS_L/UART3_RXD/EGPIO142 // MXM_POWER_ON
			GPIO_DEF_V2 (0, 0, 143, GPIO_FUNCTION_0, GPIO_NA,	GPIO_PU_PD_DIS), // UART1_TXD/EGPIO143 // MXM_POWER_GOOD
			GPIO_DEF_V2 (0, 0, 144, GPIO_FUNCTION_0, GPIO_NA,   GPIO_PU_PD_DIS), // UART1_INTR/AGPIO144 // UART1_INTR
	#endif
	};

	Status = PeiServicesLocatePpi (
				&gAmdCpmTablePpiGuid,
				0,
				NULL,
				&CpmTablePpiPtr
				);
	ASSERT_EFI_ERROR(Status);

	GpioTablePtr = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_GPIO_INIT);
	if (GpioTablePtr) {
		for (i = 0; i < sizeof(GpioOverrideTbl)/sizeof(AMD_CPM_GPIO_ITEM); i++) {
			AMD_CPM_GPIO_ITEM               *TablePtr = GpioTablePtr->GpioList;

			//
			// Override original AMD-CPM table to set the UART function pin.
			//
			while (TablePtr->Pin != 0xFF ) {
				if (TablePtr->Pin == GpioOverrideTbl[i].Pin) {
					TablePtr->Setting.Raw = GpioOverrideTbl[i].Setting.Raw;
					break;
				}
				TablePtr++;
			}

			//
			// Program the UART function pin here as well.
			//
			CpmTablePpiPtr->CommonFunction.SetGpio (CpmTablePpiPtr, GpioOverrideTbl[i].Pin, GpioOverrideTbl[i].Setting.Raw);

		}
	}

	return EFI_SUCCESS;
}


/**
  The constructor function initialize the AmiFchUartDebuggerGpioLib Library

  @retval EFI_SUCCESS   The constructor always returns RETURN_SUCCESS.

**/

EFI_STATUS
EFIAPI
AmiFchUartDebuggerGpioLibConstructor (
  IN       EFI_PEI_FILE_HANDLE       FileHandle,
  IN CONST EFI_PEI_SERVICES          **PeiServices
  )
{
    EFI_STATUS                  Status;

    Status = PeiServicesNotifyPpi(&gAmdCpmOverrideTableNotifyList);

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
