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

/** @file AmiFchInitHookDxeLib.c
    This file contains code for AmiFchInitHookDxeLib.c
    in the DXE stage.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

// UDK Header
#include <PiDxe.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/S3SaveState.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/S3BootScriptLib.h>
#include <Library/PciLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>

// AMI Header
#include <Token.h>
#include <SbElinks.h>
#include <Sb.h>

// Produced Protocols

// Consumed Protocols

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)
typedef struct {
    UINT64                  Address;
    EFI_BOOT_SCRIPT_WIDTH   Width;
    UINT32					TempData;
} BOOT_SCRIPT_PCI_REGISTER_SAVE;

typedef
EFI_STATUS
(SB_UPDATE_FCH_PCDS_FUNC)(
  IN  BOOLEAN	IsPei
  );

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	static	*gPciRootBridgeIo = NULL;
EFI_S3_SAVE_STATE_PROTOCOL     	static	*gBootScriptSave = NULL;

extern SB_UPDATE_FCH_PCDS_FUNC SB_FCH_PCD_INIT_LIST EndOfList;
SB_UPDATE_FCH_PCDS_FUNC* FchPcdUpdateList[] = { SB_FCH_PCD_INIT_LIST NULL };

// Function Definition(s)

//---------------------------------------------------------------------------

/**
    This function is the FCH Hook for FchPlatformOemDxeInit.

    @param FchData FCH parameter

    @retval EFI_STATUS EFI_SUCCESS

    @note  .
**/

EFI_STATUS
EFIAPI
AmiFchInitHookConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS      Status = EFI_SUCCESS;
    CHAR16			CONST *FchTypeStr = (CHAR16*)PcdGetPtr(AmiPcdSbFchTypeString);
    UINTN			Buffer,i;
    UINT8           SwSmi;
	UINT32          SetBits, MaskBits;
	UINT64          Address;
	struct {
    	CHAR16*					CONST FchTypeStr;
		UINT64                  CONST Address;
		EFI_BOOT_SCRIPT_WIDTH   CONST Width;
		UINT32					TempData;
	} gPciRegScriptTbl[] = {
		//
		// To save sufficient script of registers for AMD-FCH reference code S3 path.
		//		S3 PATH :
		//		==> Save the SW-SMI of AMD-FCH boot script in Dxe.
		//			==> Restore SW-SMI script in PEI while S3 wake.
		//				==> Issue SW-SMI to call AMD-FCH S3 routine.
		//
		// Most AMD-FCH has used SMN access instead Pci resource access we can skip resource dependency.
		// But some AMD-FCH code require resource that assigned by PciBus Driver. We have to porting the following table.
		//
		{L"Sandstone", 		S3_BOOT_SCRIPT_LIB_PCI_ADDRESS(0, 0x8, 0x2, 0x18), EfiBootScriptWidthUint32, (((FIXED_SATA_BUS_SANDSTONE<<8)+FIXED_SATA_BUS_SANDSTONE)<<8)}, // restore Bus Num. Required by SataGetBusCNumber.
		{L"Taishan", 		S3_BOOT_SCRIPT_LIB_PCI_ADDRESS(0, 0x8, 0x1, 0x18), EfiBootScriptWidthUint32, (((FIXED_SATA_BUS_SANDSTONE<<8)+FIXED_SATA_BUS_SANDSTONE)<<8)}, // restore Bus Num. Required by SataGetBusCNumber.
		//{L"Kern", 			S3_BOOT_SCRIPT_LIB_PCI_ADDRESS(0, 0x11, 0x0, 0x24), EfiBootScriptWidthUint32, TEMP_SATA_BAR5_ADDRESS},
		{NULL, 0, 0, 0}
	};

	for (i = 0; FchPcdUpdateList[i] != NULL; i++) {

		Status = FchPcdUpdateList[i](FALSE);

	}

	//
	// Clear SmiCmdPort Status Bit
	//
	SetBits = BIT11;
	MaskBits = -1;
	Address = ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG88;

	S3BootScriptSaveMemReadWrite (
	  EfiBootScriptWidthUint32,
	  Address,
	  &SetBits,
	  &MaskBits
	  );
	//
	// Enable CmdPort SMI
	//
	SetBits = BIT22;
	MaskBits = ~(BIT23 + BIT22);
	Address = ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REGB0;

	S3BootScriptSaveMemReadWrite (
	  EfiBootScriptWidthUint32,
	  Address,
	  &SetBits,
	  &MaskBits
	  );
	//
	// Clear SmiEnB to enable SMI function
	//
	SetBits = 0;
	MaskBits = ~BIT31;
	Address = ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG98;

	S3BootScriptSaveMemReadWrite (
	  EfiBootScriptWidthUint32,
	  Address,
	  &SetBits,
	  &MaskBits
	  );

	//
	// Set the EOS Bit
	//
	SetBits = BIT28;
	MaskBits = -1;
	Address = ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG98;

	S3BootScriptSaveMemReadWrite (
	  EfiBootScriptWidthUint32,
	  Address,
	  &SetBits,
	  &MaskBits
	  );

	// issue the Fch S3 resume.
	SwSmi = SB_BEFORE_PCI_RESTORE_SWSMI; // AVA9 : use PCD directly later.
	S3BootScriptSaveIoWrite (
	  EfiBootScriptWidthUint8,
	  SW_SMI_IO_ADDRESS,
	  1,
	  &SwSmi
	  );

    //
    // Save script to program temp resource.
    //
	if(PcdGetBool (PcdSataControllerAutoShutdown) == FALSE){
      i = 0;
      while(gPciRegScriptTbl[i].FchTypeStr != NULL) {
    	  if (StrCmp(gPciRegScriptTbl[i].FchTypeStr, FchTypeStr) == 0) {
			  Buffer = gPciRegScriptTbl[i].TempData;

			  S3BootScriptSavePciCfgWrite (
		  	    gPciRegScriptTbl[i].Width,
			    gPciRegScriptTbl[i].Address,
			    1,
			    &Buffer
			    );
    	  }

		i++;
      }
	}
    // issue the Fch S3 resume.
    SwSmi = SB_AFTER_PCI_RESTORE_SWSMI; // AVA9 : use PCD directly later.

	S3BootScriptSaveIoWrite (
	  EfiBootScriptWidthUint8,
	  SW_SMI_IO_ADDRESS,
	  1,
	  &SwSmi
	  );

    return Status;
}


//
// The AmdCpmPkg done something porting about FCH-IMC in the FchInitHook library for CRB.
// We provide dummy FchInitHook here if it is not required by OEM and user disable it.
//
#if (defined(AmdCpmPkg_FchInitHookDxeLib_SUPPORT) && (AmdCpmPkg_FchInitHookDxeLib_SUPPORT == 0)) || !defined(AmdCpmPkg_FchInitHookDxeLib_SUPPORT)
/**
    This function is the FCH Hook for FchPlatformImcDxeInit.

    @param FchImcData FCH parameter

    @retval EFI_STATUS EFI_SUCCESS

    @note  .
**/

EFI_STATUS
EFIAPI
FchPlatformImcDxeInit (
  IN      VOID                          *FchImcData
  )
{
	return EFI_SUCCESS;
}

/**
    This function is the FCH Hook for FchPlatformPTDxeInit.

    @param FchPTData FCH parameter

    @retval EFI_STATUS EFI_SUCCESS

    @note  .
**/

EFI_STATUS
EFIAPI
FchPlatformPTDxeInit (
  IN      VOID                          *FchPTData
  )
{
	return EFI_SUCCESS;
}


/**
    This function is the FCH Hook for FchPlatformOemDxeInit.

    @param FchData FCH parameter

    @retval EFI_STATUS EFI_SUCCESS

    @note  .
**/

EFI_STATUS
EFIAPI
FchPlatformOemDxeInit (
  IN      VOID                          *FchData
  )
{
  return EFI_SUCCESS;
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
