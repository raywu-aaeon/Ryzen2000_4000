//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file AmiFchIoAccessLib.c
    This file contains code for AmiFchIoAccessLib base library.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
// UDK header
#include <Uefi.h>
#include <Library/AmiFchIoAccessLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/PciLib.h>
#include <Token.h>
// AMI Compatibility header
#include <Sb.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
#define AMI_SMN_INDEX2_BIOS_BASE			0x2D01000	// define for internal use.

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------

EFI_PHYSICAL_ADDRESS 	mInternalFchAcpiMmioBase;

struct {
	AMD_FCH_MMIO_TYPE	Type;
	UINT32				MmioOffset;
	UINT32				SmnOffset;
} CONST FchMmioInfoTbl[] = {
	{AMD_FCH_MMIO, 				0, 							AMI_SMN_INDEX2_BIOS_BASE + 0},
	{AMD_FCH_SMI_MMIO, 			SMI_BASE,					AMI_SMN_INDEX2_BIOS_BASE + SMI_BASE},
	{AMD_FCH_PMIO_MMIO,			PMIO_BASE,					AMI_SMN_INDEX2_BIOS_BASE + PMIO_BASE},
	{AMD_FCH_PMIO2_MMIO,		PMIO2_BASE,					AMI_SMN_INDEX2_BIOS_BASE + PMIO2_BASE},
	{AMD_FCH_ACPI_PM_MMIO,		0x800,						AMI_SMN_INDEX2_BIOS_BASE + 0x800},
	{AMD_FCH_IOMUX_MMIO,		IOMUX_BASE, 				AMI_SMN_INDEX2_BIOS_BASE + IOMUX_BASE},
	{AMD_FCH_MISC_MMIO,			MISC_BASE, 					AMI_SMN_INDEX2_BIOS_BASE + MISC_BASE},
	{AMD_FCH_GPIO_MMIO,			GPIO_BANK0_BASE,			AMI_SMN_INDEX2_BIOS_BASE + GPIO_BANK0_BASE},
	{AMD_FCH_GPIOB0_MMIO,		GPIO_BANK0_BASE,			AMI_SMN_INDEX2_BIOS_BASE + GPIO_BANK0_BASE},
	{AMD_FCH_GPIOB1_MMIO,		GPIO_BANK0_BASE + 0x100,	AMI_SMN_INDEX2_BIOS_BASE + GPIO_BANK0_BASE + 0x100},
	{AMD_FCH_GPIOB2_MMIO,		GPIO_BANK0_BASE + 0x200,	AMI_SMN_INDEX2_BIOS_BASE + GPIO_BANK0_BASE + 0x200},
	{AMD_FCH_MMIO_TYPE_MAX,		-1,							-1}
};

#define IOHC_NB_SMN_INDEX_2_BIOS  0x00B8
#define IOHC_NB_SMN_DATA_2_BIOS   0x00BC
union {
	UINT32	PciAddr;
	struct{
		UINT32	CONST 	DevFunReg : 20;
		UINT32			Bus : 8;
	} Iohc;
}	AmiSmnIndex2 = {PCI_LIB_ADDRESS(0, 0, 0, IOHC_NB_SMN_INDEX_2_BIOS)},
	AmiSmnData2 = {PCI_LIB_ADDRESS(0, 0, 0, IOHC_NB_SMN_DATA_2_BIOS)}
	;

// Function Definition(s)

//---------------------------------------------------------------------------

/**
    Get mmio base by type.

    @param Type - The type of SB mmio.

    @retval UINT32 mmio base

**/
UINTN
EFIAPI
AmdFchMmioBase (
  IN AMD_FCH_MMIO_TYPE	Type
  )
{
	EFI_PHYSICAL_ADDRESS 	MmioBase;

	MmioBase = mInternalFchAcpiMmioBase + FchMmioInfoTbl[Type].MmioOffset;
	return (UINTN)MmioBase;
}

/**
    Read byte from mmio.

    @param Type - The type of SB mmio.
    @param Register - register for read

    @retval UINT8 return value

**/
UINT8
EFIAPI
AmdFchMmioRead8 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register
  )
{
	UINTN 	FchMmioBase = AmdFchMmioBase(Type);

	return MmioRead8(FchMmioBase + Register);
}

/**
    Read word from mmio.

    @param Type - The type of SB mmio.
    @param Register - register for read

    @retval UINT16 return value

**/
UINT16
EFIAPI
AmdFchMmioRead16 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register
  )
{
	UINTN 	FchMmioBase = AmdFchMmioBase(Type);

	return MmioRead16(FchMmioBase + Register);
}

/**
    Read double word from mmio.

    @param Type - The type of SB mmio.
    @param Register - register for read

    @retval UINT32 return value

**/
UINT32
EFIAPI
AmdFchMmioRead32 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register
  )
{
	UINTN 	FchMmioBase = AmdFchMmioBase(Type);

	return MmioRead32(FchMmioBase + Register);
}

/**
    Write byte to mmio.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param Data - data for write

    @retval The value written back to the MMIO register.

**/
UINT8
EFIAPI
AmdFchMmioWrite8 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register,
  IN UINT8		Data
  )
{
	UINTN 	FchMmioBase = AmdFchMmioBase(Type);

	return MmioWrite8(FchMmioBase + Register, Data);
}

/**
    Write word to mmio.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param Data - data for write

    @retval The value written back to the MMIO register.

**/
UINT16
EFIAPI
AmdFchMmioWrite16 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register,
  IN UINT16		Data
  )
{
	UINTN 	FchMmioBase = AmdFchMmioBase(Type);

	return MmioWrite16(FchMmioBase + Register, Data);
}

/**
    Write double word to mmio.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param Data - data for write

    @retval The value written back to the MMIO register.

**/
UINT32
EFIAPI
AmdFchMmioWrite32 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register,
  IN UINT32		Data
  )
{
	UINTN 	FchMmioBase = AmdFchMmioBase(Type);

	return MmioWrite32(FchMmioBase + Register, Data);
}

/**
    Or byte then write to mmio.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param OrData - or data

    @retval The value written back to the MMIO register.

**/
UINT8
EFIAPI
AmdFchMmioOr8 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register,
  IN UINT8		OrData
  )
{
	UINTN 	FchMmioBase = AmdFchMmioBase(Type);

	return MmioOr8(FchMmioBase + Register, OrData);
}

/**
    Or word then write to mmio.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param OrData - or data

    @retval The value written back to the MMIO register.

**/
UINT16
EFIAPI
AmdFchMmioOr16 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register,
  IN UINT16		OrData
  )
{
	UINTN 	FchMmioBase = AmdFchMmioBase(Type);

	return MmioOr16(FchMmioBase + Register, OrData);
}

/**
    Or double word then write to mmio.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param OrData - or data

    @retval The value written back to the MMIO register.

**/
UINT32
EFIAPI
AmdFchMmioOr32 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register,
  IN UINT32		OrData
  )
{
	UINTN 	FchMmioBase = AmdFchMmioBase(Type);

	return MmioOr32(FchMmioBase + Register, OrData);
}

/**
    And byte then write to mmio.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param AndData - and data

    @retval The value written back to the MMIO register.

**/
UINT8
EFIAPI
AmdFchMmioAnd8 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register,
  IN UINT8		AndData
  )
{
	UINTN 	FchMmioBase = AmdFchMmioBase(Type);

	return MmioAnd8(FchMmioBase + Register, AndData);
}

/**
    And word then write to mmio.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param AndData - and data

    @retval The value written back to the MMIO register.

**/
UINT16
EFIAPI
AmdFchMmioAnd16 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register,
  IN UINT16		AndData
  )
{
	UINTN 	FchMmioBase = AmdFchMmioBase(Type);

	return MmioAnd16(FchMmioBase + Register, AndData);
}

/**
    And double word then write to mmio.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param AndData - and data

    @retval The value written back to the MMIO register.

**/
UINT32
EFIAPI
AmdFchMmioAnd32 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register,
  IN UINT32		AndData
  )
{
	UINTN 	FchMmioBase = AmdFchMmioBase(Type);

	return MmioAnd32(FchMmioBase + Register, AndData);
}

/**
    And byte then or byte then write to mmio.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param AndData - and data
    @param OrData - or data

    @retval The value written back to the MMIO register.

**/
UINT8
EFIAPI
AmdFchMmioAndThenOr8 (
  IN 	  AMD_FCH_MMIO_TYPE	  		Type,
  IN 	  UINT32					Register,
  IN      UINT8                     AndData,
  IN      UINT8                     OrData
  )
{
	UINTN 	FchMmioBase = AmdFchMmioBase(Type);

	return MmioAndThenOr8(FchMmioBase + Register, AndData , OrData);
}

/**
    And word then or word then write to mmio.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param AndData - and data
    @param OrData - or data

    @retval The value written back to the MMIO register.

**/
UINT16
EFIAPI
AmdFchMmioAndThenOr16 (
  IN 	  AMD_FCH_MMIO_TYPE	  		Type,
  IN 	  UINT32					Register,
  IN      UINT16                    AndData,
  IN      UINT16                    OrData
  )
{
	UINTN 	FchMmioBase = AmdFchMmioBase(Type);

	return MmioAndThenOr16(FchMmioBase + Register, AndData , OrData);
}

/**
    And double word then or double word then write to mmio.

    @param Type - The type of SB mmio.
    @param Register - register to write
    @param AndData - and data
    @param OrData - or data

    @retval The value written back to the MMIO register.

**/
UINT32
EFIAPI
AmdFchMmioAndThenOr32 (
  IN AMD_FCH_MMIO_TYPE	Type,
  IN UINT32		Register,
  IN UINT32		AndData,
  IN UINT32		OrData
  )
{
	UINTN 	FchMmioBase = AmdFchMmioBase(Type);

	return MmioAndThenOr32(FchMmioBase + Register, AndData, OrData);
}


/**
 * SbSmnRead - Read SMN register
 *
 * @param[in] IohcBus     - IOHC (Node) bus number
 * @param[in] SmnAddress  - Register address in SMN 32-bit
 *                           memory space
 * @param[in] Value       -  register value
 *
 */
VOID
SbSmnRead (
  IN       UINT32              IohcBus,
  IN       UINT32              SmnAddress,
  IN       UINT32              *Value
  )
{
  UINT32    RegIndex;

  RegIndex = SmnAddress;
  AmiSmnIndex2.Iohc.Bus = IohcBus;
  AmiSmnData2.Iohc.Bus = IohcBus;

  PciWrite32 (AmiSmnIndex2.PciAddr, RegIndex);
  *Value = PciRead32 (AmiSmnData2.PciAddr);
}

/**
 * SbSmnWrite - Write value to SMN register
 *
 * @param[in] IohcBus     - IOHC (Node) bus number
 * @param[in] SmnAddress  - Register address in SMN 32-bit
 *                           memory space
 * @param[in] Value       - register value
 *
 */

VOID
SbSmnWrite (
  IN       UINT32              IohcBus,
  IN       UINT32              SmnAddress,
  IN       UINT32              Value
  )
{
  UINT32    RegIndex;

  RegIndex = SmnAddress;
  AmiSmnIndex2.Iohc.Bus = IohcBus;
  AmiSmnData2.Iohc.Bus = IohcBus;

  PciWrite32 (AmiSmnIndex2.PciAddr, RegIndex);
  PciWrite32 (AmiSmnData2.PciAddr, Value);
}

/**
 * SbSmnRW - RW SMN register
 *
 * @param[in] IohcBus     - IOHC (Node) bus number
 * @param[in] SmnAddress  - Register address in SMN 32-bit
 *                           memory space
 * @param[in] AndMask       -And mask
 * @param[in] OrMask        Or mask
 *
 */

VOID
SbSmnRw (
  IN       UINT32              IohcBus,
  IN       UINT32              SmnAddress,
  IN       UINT32              AndMask,
  IN       UINT32              OrMask
  )
{
  UINT32    RegValue;

  SbSmnRead (IohcBus, SmnAddress, &RegValue);
  RegValue &= AndMask;
  RegValue |= OrMask;
  SbSmnWrite (IohcBus, SmnAddress, RegValue);
}

/**
 * SbSmnRead8 - Read SMN register in Byte
 *
 * @param[in] IohcBus     - IOHC (Node) bus number
 * @param[in] SmnAddress  - Register address in SMN 32-bit
 *  	 memory space
 * @param[in] Value8        register value
 *
 */
VOID
SbSmnRead8 (
  IN       UINT32              IohcBus,
  IN       UINT32              SmnAddress,
  IN       UINT8               *Value
  )
{
  UINT32    RegIndex;

  RegIndex = SmnAddress & 0xFFFFFFFC;
  AmiSmnIndex2.Iohc.Bus = IohcBus;
  AmiSmnData2.Iohc.Bus = IohcBus;
  PciWrite32 (AmiSmnIndex2.PciAddr, RegIndex);
  *Value = PciRead8 (AmiSmnData2.PciAddr + (SmnAddress & 0x3));
}

/**
 * SbSmnWrite - Write Value to SMN register
 *
 * @param[in] IohcBus     - IOHC (Node) bus number
 * @param[in] SmnAddress  - Register address in SMN 32-bit
 *                           memory space
 * @param[in] Value8       - register value
 *
 */

VOID
SbSmnWrite8 (
  IN       UINT32              IohcBus,
  IN       UINT32              SmnAddress,
  IN       UINT8               Value
  )
{
  UINT32    RegIndex;

  RegIndex = SmnAddress & 0xFFFFFFFC;
  AmiSmnIndex2.Iohc.Bus = IohcBus;
  AmiSmnData2.Iohc.Bus = IohcBus;

  PciWrite32 (AmiSmnIndex2.PciAddr, RegIndex);

  PciWrite8 (AmiSmnData2.PciAddr + (UINTN)(SmnAddress & 0x3), Value);
}

/**
 * SbSmnRW8 - RW SMN register
 *
 * @param[in] IohcBus     - IOHC (Node) bus number
 * @param[in] SmnAddress  - Register address in SMN 32-bit
 *                           memory space
 * @param[in] AndMask       -And mask
 * @param[in] OrMask        Or mask
 *
 */

VOID
SbSmnRw8 (
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
  SbSmnWrite8 (IohcBus, SmnAddress, RegValue);
}

/**
  The constructor function initialize the AmiFchIoAccessLib Library

  @retval EFI_SUCCESS   The constructor always returns RETURN_SUCCESS.

**/

EFI_STATUS
EFIAPI
AmiFchIoAccessLibConstructor (
  VOID
  )
{
    EFI_STATUS                  Status = EFI_SUCCESS;

    mInternalFchAcpiMmioBase  =  (EFI_PHYSICAL_ADDRESS) PcdGet32(AmiPcdFchAcpiMmioBase);

    // The verification during porting phase.
    // unreadVariable warning happened under MARCO "DEBUG_CODE"(\MdePkg\Include\Library\DebugLib.h)
    // cppcheck-suppress unreadVariable
    DEBUG_CODE (
    	AMD_FCH_MMIO_TYPE 			i;
		for(i = AMD_FCH_MMIO; i < AMD_FCH_MMIO_TYPE_MAX; i++) {
			if (FchMmioInfoTbl[i].Type != i) {
				ASSERT(FchMmioInfoTbl[i].Type == i);
			}
		}
    );

    return Status;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
