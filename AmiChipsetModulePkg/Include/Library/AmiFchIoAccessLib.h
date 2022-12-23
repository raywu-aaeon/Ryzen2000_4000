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
//<AMI_FHDR_START>
//
// Name:        AmiFchIoAccessLib.h
//
// Description: This header file contains the AmiFchIoAccessLib.h definition.
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef _AMICHIPSETMODULEPKG_INCLUDE_LIBRARY_AMIFCHIOACCESSLIB_H_
#define _AMICHIPSETMODULEPKG_INCLUDE_LIBRARY_AMIFCHIOACCESSLIB_H_

typedef enum {
	AMD_FCH_MMIO = 0,
	AMD_FCH_SMI_MMIO,
	AMD_FCH_PMIO_MMIO,
	AMD_FCH_PMIO2_MMIO,
	AMD_FCH_ACPI_PM_MMIO,
	AMD_FCH_IOMUX_MMIO,
	AMD_FCH_MISC_MMIO,
	AMD_FCH_GPIO_MMIO,
	AMD_FCH_GPIOB0_MMIO,
	AMD_FCH_GPIOB1_MMIO,
	AMD_FCH_GPIOB2_MMIO,
	AMD_FCH_MMIO_TYPE_MAX
} AMD_FCH_MMIO_TYPE;



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
  );

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
  );

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
  );

/**
    Write bite to mmio.

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );


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
  );


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
  );

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
  );

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
  );

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
  IN       UINT8               *Value8
  );

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
  IN       UINT8               Value8
  );

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
  );



/*******************************************************************************************************
 *
 * 		The following library for boot script
 *
 */

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

#pragma pack(1)



#pragma pack()

#endif /* _AMICHIPSETMODULEPKG_INCLUDE_LIBRARY_AMIFCHIOACCESSLIB_H_ */

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
