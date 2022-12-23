//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
/** @file AmiCpmTableConstructorLib.c
    This file contains code for AmiCpmTableConstructor
    merge the AMI GPIO table into AMD CPM-table.

**/
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
// header
#include <Token.h>

#include <AmdCpmPei.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>

#include <Ppi/SbPpi.h>
#include <Ppi/SbChipsetPpi.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)
VOID
AddAmiGpTblToAmdCpmGpTbl (
  IN AMD_CPM_GPIO_ITEM  				*AmdCpmGpioSetingTable,
  IN AMI_GPIO_INIT_TABLE_STRUCT 		*AmiGpioTb,
  IN UINT8						CONST	*IoMuxSelect
  );

VOID
AppendCpmGpioItem (
  IN AMD_CPM_FCH_REVISION_ID FchRevision,
  IN AMD_CPM_GPIO_ITEM *DestTbl,
  IN AMD_CPM_GPIO_ITEM *SourceTbl,
  IN AMI_GPIO_INIT_TABLE_STRUCT *AmiGpioTb
  );

EFI_STATUS
EFIAPI
AmdFchAmiPolicyCallBack (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  );

EFI_STATUS
EFIAPI
CpmGpioWrapOverrideNotifyCallback (
  IN       EFI_PEI_SERVICES             **PeiServices,
  IN       EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN       VOID                         *Ppi
  );

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

static EFI_PEI_NOTIFY_DESCRIPTOR  gAmdFchAmiPolicyPpiNotify =
{
    (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gAmdFchAmiPolicyPpiGuid,
    AmdFchAmiPolicyCallBack
};

static EFI_PEI_NOTIFY_DESCRIPTOR gCpmOemTableOverrideNotify = {
    (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gAmdCpmTablePpiGuid,
    CpmGpioWrapOverrideNotifyCallback
};

UINT8 CONST IoMuxSelectBr[] = {
    // GPIO 0 ~ 152 (S0-domain General Purpose I/O)
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0,   // GPIO 0 ~ 9   (0 ~ 9)
    1, 0, 2, 1, 1, 1, 2, 2, 2, 2,   // GPIO 10 ~ 19 (0xA ~ 0x13)
    2, 1, 1, 2, 1, 1, 1, 0, 0, 0,   // GPIO 20 ~ 29 (0x14 ~ 0x1D)
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1,   // GPIO 30 ~ 39 (0x1E ~ 0x27)
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0,   // GPIO 40 ~ 49 (0x28 ~ 0x31)
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 50 ~ 59 (0x32 ~ 0x3B)
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 60 ~ 69 (0x3C ~ 0x45)
    0, 0, 0, 0, 1, 1, 0, 0, 0, 0,   // GPIO 70 ~ 79 (0x46 ~ 0x4F)
    0, 0, 0, 0, 1, 1, 1, 1, 1, 0,   // GPIO 80 ~ 89
    0, 1, 3, 1, 0, 1, 1, 1, 1, 1,   // GPIO 90 ~ 99
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0,   // GPIO 100 ~ 109
    0, 0, 0, 2, 2, 1, 1, 1, 1, 2,   // GPIO 110 ~ 119
    1, 1, 1, 0, 0, 0, 1, 0, 0, 1,   // GPIO 120 ~ 129
    1, 3, 2, 1, 0, 1, 1, 1, 1, 1,   // GPIO 130 ~ 139
    1, 1, 1, 1, 1, 1, 1, 1, 1,      // GPIO 140 ~ 148
    //  not used    
    1,   // GPIO 149    
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,        // GPIO 150 ~ 159
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 160 ~ 169 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 170 ~ 179 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 180 ~ 189 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 190 ~ 199 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 200 ~ 209 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 210 ~ 219 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 220 ~ 229 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 230 ~ 239 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 240 ~ 249 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0   // GPIO 250 ~ 255
};

UINT8 CONST IoMuxSelectSm[] = {
    // GPIO 0 ~ 152 (S0-domain General Purpose I/O)
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0,   // GPIO 0 ~ 9   (0 ~ 9)
    1, 1, 1, 0, 0, 0, 1, 1, 1, 2,   // GPIO 10 ~ 19 (0xA ~ 0x13)
    2, 2, 2, 0, 1, 0, 1, 1, 1, 1,   // GPIO 20 ~ 29 (0x14 ~ 0x1D)
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 30 ~ 39 (0x1E ~ 0x27)
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0,   // GPIO 40 ~ 49 (0x28 ~ 0x31)
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 50 ~ 59 (0x32 ~ 0x3B)
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 60 ~ 69 (0x3C ~ 0x45)
    0, 0, 0, 0, 2, 2, 0, 0, 0, 0,   // GPIO 70 ~ 79 (0x46 ~ 0x4F)
    0, 0, 0, 0, 1, 1, 1, 2, 2, 2,   // GPIO 80 ~ 89
    2, 1, 3, 0, 0, 1, 1, 1, 1, 1,   // GPIO 90 ~ 99
    1, 0, 0, 0, 2, 2, 2, 2, 2, 2,   // GPIO 100 ~ 109
    0, 0, 0, 2, 2, 1, 1, 0, 1, 2,   // GPIO 110 ~ 119
    0, 0, 1, 0, 0, 0, 0, 0, 0, 1,   // GPIO 120 ~ 129
    1, 3, 2, 1, 0, 2, 1, 2, 1, 1,   // GPIO 130 ~ 139
    2, 1, 2, 1, 1, 1, 1, 2, 2, 1,   // GPIO 140 ~ 149
    1, 1, 1,                        // GPIO 150 ~ 152
    //  not used        
    0, 0, 0, 0, 0, 0, 0,            // GPIO 153 ~ 159
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 160 ~ 169 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 170 ~ 179 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 180 ~ 189 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 190 ~ 199 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 200 ~ 209 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 210 ~ 219 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 220 ~ 229 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 230 ~ 239 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 240 ~ 249 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0   // GPIO 250 ~ 255
};

UINT8 CONST IoMuxSelectRv[] = {
	// 55570-B1 Rev 1.06 - May 18, 2018   PPR for AMD Family 17h Models 11h,18h B1
	// 15.2.16.1  IOMUX Registers
	//0  1  2  3  4  5  6  7  8  9 
	//
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0,   // GPIO 0 ~ 9   (0 ~ 9)
    0, 0, 1, 1, 1, 0, 1, 1, 1, 2,   // GPIO 10 ~ 19 (0xA ~ 0x13)
    2, 2, 2, 3, 1, 0, 1, 0, 0, 1,   // GPIO 20 ~ 29 (0x14 ~ 0x1D)
    2, 2, 2, 0, 0, 0, 0, 0, 0, 0,   // GPIO 30 ~ 39 (0x1E ~ 0x27)
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 40 ~ 49 (0x28 ~ 0x31)
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 50 ~ 59 (0x32 ~ 0x3B)
    0, 0, 0, 0, 0, 0, 0, 1, 0, 0,   // GPIO 60 ~ 69 (0x3C ~ 0x45)
    0, 0, 0, 0, 2, 2, 1, 0, 0, 0,   // GPIO 70 ~ 79 (0x46 ~ 0x4F)
    0, 0, 0, 0, 1, 1, 1, 2, 2, 2,   // GPIO 80 ~ 89
    2, 1, 3, 0, 0, 0, 0, 0, 0, 0,   // GPIO 90 ~ 99
    0, 0, 0, 0, 3, 3, 3, 3, 2, 2,   // GPIO 100 ~ 109
    0, 0, 0, 2, 2, 1, 1, 0, 0, 0,   // GPIO 110 ~ 119
    1, 1, 0, 0, 0, 0, 0, 0, 0, 1,   // GPIO 120 ~ 129
    1, 3, 2, 0, 0, 2, 1, 2, 1, 1,   // GPIO 130 ~ 139
    2, 1, 2, 1, 1,                  // GPIO 140 ~ 144
                   0, 0, 0, 0, 0,   // GPIO 145 ~ 159   not used 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 150 ~ 159
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 160 ~ 169
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 170 ~ 179
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 180 ~ 189
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 190 ~ 199
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 200 ~ 209
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 210 ~ 219
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 220 ~ 229
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 230 ~ 239
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 240 ~ 249
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0    // GPIO 250 ~ 255
};

struct {
	UINT8				FchRevision;
	UINT8		CONST	*IoMuxSelect;
} CONST STATIC FchIoMux[] = {
		{CPM_FCH_REVISION_ID_BR, IoMuxSelectBr},
		{CPM_FCH_REVISION_ID_ZP, IoMuxSelectSm},
		{CPM_FCH_REVISION_ID_RV, IoMuxSelectRv},
		{CPM_FCH_REVISION_ID_RV2, IoMuxSelectRv},
}, SizeOfFchIoMux;

// GUID Definition(s)

// PPI Definition(s)

// PPI that are installed

// PPI that are notified

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

/**
    This function to merge the AMI GPIO table into AMD CPM-table.

    @param PeiServices Pei service.
    @param NotifyDescriptor The descriptor for the notification event.
    @param Ppi Pointer to the PPI in question.


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
EFIAPI
CpmGpioWrapOverrideNotifyCallback (
  IN       EFI_PEI_SERVICES             **PeiServices,
  IN       EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN       VOID                         *Ppi
  )
{
    EFI_STATUS  			Status = EFI_SUCCESS;
    //###AMD_CPM_GPIO_INIT_TABLE	*AmiCpmGpioTbl;
    AMD_CPM_GPIO_INIT_TABLE	*AmdCpmDefaultGpioTbl;
    AMD_CPM_TABLE_PPI       *This = Ppi;
    AMD_FCH_AMI_POLICY_PPI		*FchAmiPolicyPpi;
    AMI_GPIO_INIT_TABLE_STRUCT 	*DefaultGpioTbl, *CustomizeTbl;

    Status = (*PeiServices)->LocatePpi(
                    PeiServices,
                    &gAmdFchAmiPolicyPpiGuid,
                    0,
                    NULL,
                    &FchAmiPolicyPpi);
     DefaultGpioTbl = NULL;
     CustomizeTbl = NULL;
     if (!EFI_ERROR(Status)) {
         if (FchAmiPolicyPpi->AmiPeiSbCustomPpi != NULL) {
              CustomizeTbl = FchAmiPolicyPpi->AmiPeiSbCustomPpi->GpioInit->GpioTable;
              if (FchAmiPolicyPpi->AmiPeiSbCustomPpi->GpioInit->InitDefaultGpioSetting) {
                  DefaultGpioTbl = FchAmiPolicyPpi->DefaultGpioTbl;
              }
         }
     }

    AmdCpmDefaultGpioTbl = This->CommonFunction.GetTablePtr (This, CPM_SIGNATURE_GPIO_INIT);
    //###This->CommonFunction.AddTable(This, OemTbl);
    //###AmiCpmGpioTbl = OemTbl;
    AppendCpmGpioItem(This->ChipId.Sb, AmdCpmDefaultGpioTbl->GpioList, NULL, DefaultGpioTbl);

    // Append AMI's GPIO table into CPM table.
    AppendCpmGpioItem(This->ChipId.Sb, AmdCpmDefaultGpioTbl->GpioList, NULL, CustomizeTbl);

    return Status;
}

/**
    Translate AMI's AMI_GPIO_INIT_TABLE_STRUCT table to AMD_CPM_GPIO_ITEM.


    @param AmdCpmGpioSetingTable Pointer to the PEI Configure table
    @param AmiGpioTb

    @retval VOID

**/
VOID
AddAmiGpTblToAmdCpmGpTbl (
  IN AMD_CPM_GPIO_ITEM  				*AmdCpmGpioSetingTable,
  IN AMI_GPIO_INIT_TABLE_STRUCT 		*AmiGpioTb,
  IN UINT8						CONST	*IoMuxSelect
  )
{

    if (AmiGpioTb->Gpio.isGpio) {
        AmdCpmGpioSetingTable->Setting.Gpio.Out = AmiGpioTb->Gpio.GpioOut;
        AmdCpmGpioSetingTable->Setting.Gpio.OutEnB = AmiGpioTb->Gpio.GpioOutEnB;
        AmdCpmGpioSetingTable->Setting.Gpio.Sticky = AmiGpioTb->Gpio.Sticky;
        AmdCpmGpioSetingTable->Setting.Gpio.PullUp = AmiGpioTb->Gpio.PullUpB;
        AmdCpmGpioSetingTable->Setting.Gpio.PullDown = AmiGpioTb->Gpio.PullDown;
        AmdCpmGpioSetingTable->Setting.Gpio.SetEnB = 0;
        AmdCpmGpioSetingTable->Setting.Gpio.PresetEn = 1;
        AmdCpmGpioSetingTable->Setting.Gpio.IoMuxEn = 1;
        AmdCpmGpioSetingTable->Setting.Gpio.IoMux = IoMuxSelect[AmiGpioTb->GpioNo];

    } else {
        AmdCpmGpioSetingTable->Setting.Gpio.Out = 0;
        AmdCpmGpioSetingTable->Setting.Gpio.OutEnB = 0;
        AmdCpmGpioSetingTable->Setting.Gpio.Sticky = 0;
        AmdCpmGpioSetingTable->Setting.Gpio.PullUp = 0;
        AmdCpmGpioSetingTable->Setting.Gpio.PullDown = 0;
        AmdCpmGpioSetingTable->Setting.Gpio.IoMux = AmiGpioTb->Gpio.IoMux;
        AmdCpmGpioSetingTable->Setting.Gpio.SetEnB = 1;
        AmdCpmGpioSetingTable->Setting.Gpio.PresetEn = 0;

        AmdCpmGpioSetingTable->Setting.Gpio.IoMuxEn = AmiGpioTb->Gpio.IoMux;
    }

    AmdCpmGpioSetingTable->Pin = (UINT8)AmiGpioTb->GpioNo;

    return;
}


/**
    Append AMD_CPM_GPIO_ITEM into the Gpio tables.


    @param DestTbl Pointer to the PEI Configure table
    @param SourceTbl
    @param AmiGpioTb

    @retval VOID

**/
VOID
AppendCpmGpioItem (
  IN AMD_CPM_FCH_REVISION_ID FchRevision,
  IN AMD_CPM_GPIO_ITEM *DestTbl,
  IN AMD_CPM_GPIO_ITEM *SourceTbl,
  IN AMI_GPIO_INIT_TABLE_STRUCT *AmiGpioTb
  )
{
    UINTN	i, EndOfTbl, NextEntry;
    UINTN	CONST TableSize = AMD_GPIO_ITEM_SIZE; // The AMD-CPM define the maximum array by this token.
    UINT8	CONST *IoMux = NULL;

    for (i = 0; i < sizeof(FchIoMux) / sizeof(SizeOfFchIoMux); i++) {
    	if (FchIoMux[i].FchRevision == FchRevision) {
    		IoMux = FchIoMux[i].IoMuxSelect;
    		break;
    	}
    }
    ASSERT(IoMux != NULL);

    for (i = 0; i < TableSize; i++) {
        if (DestTbl[i].Pin == 0xFF) {
            EndOfTbl = i;
            //
            // Append CPM style GPIO table.
            //
            NextEntry = 0;
            if (SourceTbl) {
                while ((EndOfTbl < TableSize) && (SourceTbl[NextEntry].Pin != 0xFF)) {
                    DestTbl[EndOfTbl].Pin = SourceTbl[NextEntry].Pin;
                    DestTbl[EndOfTbl].Setting.Raw = SourceTbl[NextEntry].Setting.Raw;
                    EndOfTbl++;
                    NextEntry++;
                }
                 // if Out of table
                ASSERT(EndOfTbl < TableSize);
                 // fill the end of table
                DestTbl[EndOfTbl].Pin = 0xFF;
            }
            //
            // Append AMI style GPIO to CPM table.
            //
            NextEntry = 0;
            if (AmiGpioTb) {
                while ((EndOfTbl < TableSize) && (AmiGpioTb[NextEntry].GpioCfg != 0xFFFF) && (AmiGpioTb[NextEntry].GpioNo != 0xFFFF)) {
                    AddAmiGpTblToAmdCpmGpTbl(&DestTbl[EndOfTbl], &AmiGpioTb[NextEntry], IoMux);
                    EndOfTbl++;
                    NextEntry++;
                }
                 // if Out of table
                ASSERT(EndOfTbl < TableSize);
                 // fill the end of table
                DestTbl[EndOfTbl].Pin = 0xFF;
            }
            break;
        }
    }
}

/**
    This function configure parameters in the PEI phase for CPM
    and assign NULL for old OemResetProgrammingTablePtr.


    @param PeiServices Pei service.
    @param This Pointer to the AMD_FCH_AMI_POLICY_PPI
    @param OverwriteTable

    @retval VOID

**/
VOID
CpmApplyGpioTable (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN OUT AMD_FCH_AMI_POLICY_PPI *This,
  IN VOID                       *OverwriteTable
  )
{
    EFI_STATUS                      Status = EFI_SUCCESS;

    // We don't consider the parameter which is going to pass to AGESA-FCH. We disable all.
    //    Because user chose CPM for handle GPIO.
    //		and the OverwriteTable is ignored here.
    //This->AmdParameters.OemResetProgrammingTablePtr = NULL;

}

/**
    To notify us the user custom PPI has been update.


    @param PeiServices Pei service.
    @param NotifyDescriptor The descriptor for the notification event.
    @param Ppi Pointer to the PPI in question.


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
EFIAPI
AmdFchAmiPolicyCallBack (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
    EFI_STATUS				Status = EFI_SUCCESS;
    AMD_FCH_AMI_POLICY_PPI	*This = Ppi;

    //This->HookApplyGpioTable = CpmApplyGpioTable;

    return Status;
}

/**
    This function is the entry point for AmiCpmTableConstructor PEIM.
    It initializes the chipset AmiCpmTableConstructor in PEI phase.

    @param FileHandle Pointer to the FFS file header.
    @param PeiServices Pointer to the PEI services table.


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

    @note  .
**/

EFI_STATUS
EFIAPI
AmiCpmTableConstructor (
  IN EFI_PEI_FILE_HANDLE       FileHandle,
  IN CONST EFI_PEI_SERVICES    **PeiServices
  )
{
    EFI_STATUS                  Status = EFI_SUCCESS;

    if (FeaturePcdGet(PcdAmiCpmTableOverride)) {
        // Notify PPI
        // Notify PPI gAmdCpmTablePpiGuid
	 	// GPIO.h, Crb1GpioTable add CPM GPIo table
        Status = (**PeiServices).NotifyPpi (PeiServices, &gCpmOemTableOverrideNotify);
    }

    return Status;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
