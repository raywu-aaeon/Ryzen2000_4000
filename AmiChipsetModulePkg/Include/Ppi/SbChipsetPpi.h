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
/** @file SbChipsetPpi.h
    This header file contains the PPI definition for the SB.
*/

#ifndef __AMI_SB_CHIPSET_PPI_H__
#define __AMI_SB_CHIPSET_PPI_H__

/**** PORTING REQUIRED ****
  AMI_GPIO_INIT_TABLE_STRUCT is optional for SbChipsetPpi.h.
  Chipset porting owner can change it per your GPIO porting need.
****/
typedef struct _AMI_GPIO_INIT_TABLE_STRUCT  AMI_GPIO_INIT_TABLE_STRUCT;

struct _AMI_GPIO_INIT_TABLE_STRUCT {
    UINT16                      GpioNo;
	union {
		UINT16	GpioCfg;
		  struct {                                                    ///<
		    UINT16                         OwnedByIMC:1;               ///< OwnedByIMC
		    UINT16                         OwnedByHost:1;              ///< OwnedByHost
		    UINT16                         Sticky:1;                   ///< Sticky
		    UINT16                         PullUpB:1;                  ///< PullUpB
		    UINT16                         PullDown:1;                 ///< PullDown
		    UINT16                         GpioOutEnB:1;               ///< GpioOutEnB
		    UINT16                         GpioOut:1;                  ///< GpioOut
		    UINT16                         GpioIn:1;                   ///< GpioIn
		    UINT16                         IoMux:3;                    ///< Multi-function IO pin function select of GPIO
		    UINT16                         Reserved2:4;                ///  reserved
		    UINT16                         isGpio:1;                   ///< is GPIo
		  }                               Gpio;                       ///< Bit mapping for GPIO settin
	};
};

typedef struct _AMD_FCH_AMI_POLICY_PPI {
    AMI_GPIO_INIT_TABLE_STRUCT  *DefaultGpioTbl;
    AMI_PEI_SB_CUSTOM_PPI       *AmiPeiSbCustomPpi;
} AMD_FCH_AMI_POLICY_PPI;

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
