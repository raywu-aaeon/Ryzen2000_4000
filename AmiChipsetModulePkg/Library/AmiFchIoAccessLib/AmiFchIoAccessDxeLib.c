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

/** @file AmiFchIoAccessDxeLib.c
    This file contains code for AmiFchIoAccessDxeLib base library.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
// UDK header
#include <PiDxe.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/PciLib.h>
#include <Library/DebugLib.h>
#include <Protocol/S3SaveState.h>

#include <Library/AmiChipsetIoLib.h>
#include <Library/AmiFchIoAccessLib.h>

#include <Token.h>
// AMI Compatibility header


//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------

EFI_STATUS
EFIAPI
AmiFchIoAccessLibConstructor (
  VOID
  );

UINTN
EFIAPI
AmdFchMmioBase (
  IN AMD_FCH_MMIO_TYPE	Type
  );

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------

EFI_GUID    mAmiFchIoAccessEfiS3SaveStateProtocolGuid = EFI_S3_SAVE_STATE_PROTOCOL_GUID;

extern union {
	UINT32	PciAddr;
	struct{
		UINT32	CONST 	DevFunReg : 20;
		UINT32			Bus : 8;
	} Iohc;
}	AmiSmnIndex2,
	AmiSmnData2
	;

//---------------------------------------------------------------------------
// Function Definition(s)
//---------------------------------------------------------------------------

/**
    Sb CspLib Get BootScriptSaveProtocol

    @param VOID

    @retval EFI_BOOT_SCRIPT_SAVE_PROTOCOL return protocol

**/
static
EFI_S3_SAVE_STATE_PROTOCOL*
SbCspLibGetBootScriptSaveProtocol(VOID)
{
    EFI_S3_SAVE_STATE_PROTOCOL static *SbCspLibProtocol = NULL;
    if (SbCspLibProtocol == NULL) {
        EFI_STATUS  Status;

        Status = gBS->LocateProtocol(&mAmiFchIoAccessEfiS3SaveStateProtocolGuid, NULL, &SbCspLibProtocol);
        ASSERT_EFI_ERROR(Status);
    }
    return SbCspLibProtocol;
}

/**
    Write byte to mmio and boot script.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param Data - data for write

    @retval The value written back to the MMIO register.

**/
UINT8
EFIAPI
AmdFchMmioS3Write8 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register,
  IN UINT8		Data
  )
{
	EFI_S3_SAVE_STATE_PROTOCOL     *mBootScriptSave = SbCspLibGetBootScriptSaveProtocol();
	UINTN 							FchMmioBase = AmdFchMmioBase(Type);

	WRITE_MEM8_S3(mBootScriptSave, FchMmioBase + Register, Data);

	return Data;
}

/**
    Write word to mmio and boot script.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param Data - data for write

    @retval The value written back to the MMIO register.

**/
UINT16
EFIAPI
AmdFchMmioS3Write16 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register,
  IN UINT16		Data
  )
{
	EFI_S3_SAVE_STATE_PROTOCOL     *mBootScriptSave = SbCspLibGetBootScriptSaveProtocol();
	UINTN 							FchMmioBase = AmdFchMmioBase(Type);

	WRITE_MEM16_S3(mBootScriptSave, FchMmioBase + Register, Data);

	return Data;
}

/**
    Write double word to mmio and boot script.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param Data - data for write

    @retval The value written back to the MMIO register.

**/
UINT32
EFIAPI
AmdFchMmioS3Write32 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register,
  IN UINT32		Data
  )
{
	EFI_S3_SAVE_STATE_PROTOCOL     *mBootScriptSave = SbCspLibGetBootScriptSaveProtocol();
	UINTN 							FchMmioBase = AmdFchMmioBase(Type);

	WRITE_MEM32_S3(mBootScriptSave, FchMmioBase + Register, Data);

	return Data;
}

/**
    Or byte then write to mmio and boot script.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param OrData - or data

    @retval The value written back to the MMIO register.

**/
UINT8
EFIAPI
AmdFchMmioS3Or8 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register,
  IN UINT8		OrData
  )
{
	EFI_S3_SAVE_STATE_PROTOCOL		*mBootScriptSave = SbCspLibGetBootScriptSaveProtocol();
	UINTN 							FchMmioBase = AmdFchMmioBase(Type);
	UINT8							Data = AmdFchMmioRead8(Type, Register) | OrData;

	WRITE_MEM8_S3(mBootScriptSave, FchMmioBase + Register, Data);

	return Data;
}

/**
    Or word then write to mmio and boot script.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param OrData - or data

    @retval The value written back to the MMIO register.

**/
UINT16
EFIAPI
AmdFchMmioS3Or16 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register,
  IN UINT16		OrData
  )
{
	EFI_S3_SAVE_STATE_PROTOCOL    	*mBootScriptSave = SbCspLibGetBootScriptSaveProtocol();
	UINTN 							FchMmioBase = AmdFchMmioBase(Type);
	UINT16							Data = AmdFchMmioRead16(Type, Register) | OrData;

	WRITE_MEM16_S3(mBootScriptSave, FchMmioBase + Register, Data);

	return Data;
}

/**
    Or double word then write to mmio and boot script.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param OrData - or data

    @retval The value written back to the MMIO register.

**/
UINT32
EFIAPI
AmdFchMmioS3Or32 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register,
  IN UINT32		OrData
  )
{
	EFI_S3_SAVE_STATE_PROTOCOL		*mBootScriptSave = SbCspLibGetBootScriptSaveProtocol();
	UINTN 							FchMmioBase = AmdFchMmioBase(Type);
	UINT32							Data = AmdFchMmioRead32(Type, Register) | OrData;

	WRITE_MEM32_S3(mBootScriptSave, FchMmioBase + Register, Data);

	return Data;
}

/**
    And byte then write to mmio and boot script.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param AndData - and data

    @retval The value written back to the MMIO register.

**/
UINT8
EFIAPI
AmdFchMmioS3And8 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register,
  IN UINT8		AndData
  )
{
	EFI_S3_SAVE_STATE_PROTOCOL		*mBootScriptSave = SbCspLibGetBootScriptSaveProtocol();
	UINTN 							FchMmioBase = AmdFchMmioBase(Type);
	UINT8							Data = AmdFchMmioRead8(Type, Register) & AndData;

	WRITE_MEM8_S3(mBootScriptSave, FchMmioBase + Register, Data);

	return Data;
}

/**
    And word then write to mmio and boot script.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param AndData - and data

    @retval The value written back to the MMIO register.

**/
UINT16
EFIAPI
AmdFchMmioS3And16 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register,
  IN UINT16		AndData
  )
{
	EFI_S3_SAVE_STATE_PROTOCOL		*mBootScriptSave = SbCspLibGetBootScriptSaveProtocol();
	UINTN 							FchMmioBase = AmdFchMmioBase(Type);
	UINT16							Data = AmdFchMmioRead16(Type, Register) & AndData;

	WRITE_MEM16_S3(mBootScriptSave, FchMmioBase + Register, Data);

	return Data;
}

/**
    And double word then write to mmio and boot script.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param AndData - and data

    @retval The value written back to the MMIO register.

**/
UINT32
EFIAPI
AmdFchMmioS3And32 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register,
  IN UINT32		AndData
  )
{
	EFI_S3_SAVE_STATE_PROTOCOL		*mBootScriptSave = SbCspLibGetBootScriptSaveProtocol();
	UINTN 							FchMmioBase = AmdFchMmioBase(Type);
	UINT32							Data = AmdFchMmioRead32(Type, Register) & AndData;

	WRITE_MEM32_S3(mBootScriptSave, FchMmioBase + Register, Data);

	return Data;
}

/**
    And byte then or byte then write to mmio and boot script.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param AndData - and data
    @param OrData - or data

    @retval The value written back to the MMIO register.

**/
UINT8
EFIAPI
AmdFchMmioS3AndThenOr8 (
  IN 	  AMD_FCH_MMIO_TYPE	  		Type,
  IN 	  UINT32					Register,
  IN      UINT8                     AndData,
  IN      UINT8                     OrData
  )
{
	EFI_S3_SAVE_STATE_PROTOCOL		*mBootScriptSave = SbCspLibGetBootScriptSaveProtocol();
	UINTN 							FchMmioBase = AmdFchMmioBase(Type);
	UINT8							Data = (AmdFchMmioRead8(Type, Register) & AndData) | OrData;

	WRITE_MEM8_S3(mBootScriptSave, FchMmioBase + Register, Data);

	return Data;
}

/**
    And word then or word then write to mmio and boot script.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param AndData - and data
    @param OrData - or data

    @retval The value written back to the MMIO register.

**/
UINT16
EFIAPI
AmdFchMmioS3AndThenOr16 (
  IN 	  AMD_FCH_MMIO_TYPE	  		Type,
  IN 	  UINT32					Register,
  IN      UINT16                    AndData,
  IN      UINT16                    OrData
  )
{
	EFI_S3_SAVE_STATE_PROTOCOL		*mBootScriptSave = SbCspLibGetBootScriptSaveProtocol();
	UINTN 							FchMmioBase = AmdFchMmioBase(Type);
	UINT16							Data = (AmdFchMmioRead16(Type, Register) & AndData) | OrData;

	WRITE_MEM16_S3(mBootScriptSave, FchMmioBase + Register, Data);

	return Data;
}

/**
    And double word then or double word then write to mmio and boot script.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param AndData - and data
    @param OrData - or data

    @retval The value written back to the MMIO register.

**/
UINT32
EFIAPI
AmdFchMmioS3AndThenOr32 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register,
  IN UINT32		AndData,
  IN UINT32		OrData
  )
{
	EFI_S3_SAVE_STATE_PROTOCOL		*mBootScriptSave = SbCspLibGetBootScriptSaveProtocol();
	UINTN 							FchMmioBase = AmdFchMmioBase(Type);
	UINT32							Data = (AmdFchMmioRead32(Type, Register) & AndData) | OrData;

	WRITE_MEM32_S3(mBootScriptSave, FchMmioBase + Register, Data);

	return Data;
}

/**
 * SbSmnWriteS3 - Write Value to SMN register,and Save to Boot Script
 *
 * @param[in] IohcBus     - IOHC (Node) bus number
 * @param[in] SmnAddress  - Register address in SMN 32-bit
 *                           memory space
 * @param[in] Value8       - register value
 *
 */

VOID
SbSmnWrite8S3 (
  IN       UINT32              IohcBus,
  IN       UINT32              SmnAddress,
  IN       UINT8               Value
  )
{
	EFI_S3_SAVE_STATE_PROTOCOL     *mBootScriptSave = SbCspLibGetBootScriptSaveProtocol();
	UINT32    					   RegIndex;

	RegIndex = SmnAddress;
	AmiSmnIndex2.Iohc.Bus = IohcBus;
	AmiSmnData2.Iohc.Bus = IohcBus;

	SbSmnWrite8(IohcBus, SmnAddress, Value);

	WRITE_PCI8_S3EX(mBootScriptSave, AmiSmnIndex2.PciAddr, RegIndex);
	WRITE_PCI8_S3EX(mBootScriptSave, AmiSmnData2.PciAddr, Value);
}

/**
 * SbSmnRWS3 - RW SMN register,and Save to boot script
 *
 * @param[in] IohcBus     - IOHC (Node) bus number
 * @param[in] SmnAddress  - Register address in SMN 32-bit
 *                           memory space
 * @param[in] AndMask       -And mask
 * @param[in] OrMask        Or mask
 *
 */

VOID
SbSmnRw8S3 (
  IN       UINT32              IohcBus,
  IN       UINT32              SmnAddress,
  IN       UINT8               AndMask,
  IN       UINT8               OrMask
  )
{
  UINT8    RegValue;

  SbSmnRead8 (IohcBus, SmnAddress, &RegValue);
  RegValue &= AndMask;
  RegValue |= OrMask;
  SbSmnWrite8S3 (IohcBus, SmnAddress, RegValue);
}


/**
 * SbSmnWriteS3 - Write value to SMN register,and Save value to BootScript
 *
 * @param[in] IohcBus     - IOHC (Node) bus number
 * @param[in] SmnAddress  - Register address in SMN 32-bit
 *                           memory space
 * @param[in] Value       -register value
 *
 */

VOID
SbSmnWriteS3 (
  IN       UINT32              IohcBus,
  IN       UINT32              SmnAddress,
  IN       UINT32              Value
  )
{
	EFI_S3_SAVE_STATE_PROTOCOL     *mBootScriptSave = SbCspLibGetBootScriptSaveProtocol();
	UINT32    					   RegIndex;

	RegIndex = SmnAddress;
	AmiSmnIndex2.Iohc.Bus = IohcBus;
	AmiSmnData2.Iohc.Bus = IohcBus;

	SbSmnWrite(IohcBus, SmnAddress, Value);

	WRITE_PCI32_S3EX(mBootScriptSave, AmiSmnIndex2.PciAddr, RegIndex);
	WRITE_PCI32_S3EX(mBootScriptSave, AmiSmnData2.PciAddr, Value);
}

/**
 * SbSmnRWS3 - Read SMN register and Save to BootScript
 *
 * @param[in] IohcBus     - IOHC (Node) bus number
 * @param[in] SmnAddress  - Register address in SMN 32-bit
 *                           memory space
 * @param[in] AndMask       -And mask
 * @param[in] OrMask        Or mask
 *
 */

VOID
SbSmnRwS3 (
  IN       UINT32              IohcBus,
  IN       UINT32              SmnAddress,
  IN       UINT32              AndMask,
  IN       UINT32              OrMask
  )
{
  UINT32    RegValue=0;

  SbSmnRead (IohcBus, SmnAddress, &RegValue);
  RegValue &= AndMask;
  RegValue |= OrMask;
  SbSmnWriteS3 (IohcBus, SmnAddress, RegValue);
}

/**
  The constructor function initialize the AmiFchIoAccessDxeLib Library

  @retval EFI_SUCCESS   The constructor always returns RETURN_SUCCESS.

**/

RETURN_STATUS
EFIAPI
AmiFchIoAccessDxeLibConstructor (
  VOID
  )
{
    EFI_STATUS                  Status = EFI_SUCCESS;

    Status = AmiFchIoAccessLibConstructor();

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
