//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

//*************************************************************************
/** @file I2cHcOperationDxe.h
    This header file contains I2C related structure and
    constant definitions.

*/
//*************************************************************************

#ifndef _I2C_HC_OPERATION_DXE_H_
#define _I2C_HC_OPERATION_DXE_H_
#include <IndustryStandard/Pci.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PciLib.h>
#include <Library/PcdLib.h>
#include <Protocol/AmiI2cHcOperation.h>
#include "AmiFchI2cInfo.h"
#include "Token.h"

//
// Definitions
//
#define I2C_PRIVATE_DATA_SIGNATURE   SIGNATURE_32('p','i','2','c')

//
// History:
// 
#define I2C_PRIVATE_DATA_FROM_THIS(a) \
            CR (a, I2C_BUS_INSTANCE, I2cHcOpProtocol, I2C_PRIVATE_DATA_SIGNATURE)

typedef struct _I2C_BUS_INSTANCE I2C_BUS_INSTANCE;

typedef enum _I2C_BUS {
  I2C0_BUS_NUM = 0,
  I2C1_BUS_NUM,
  I2C2_BUS_NUM,
  I2C3_BUS_NUM,
  I2C4_BUS_NUM,
} I2C_BUS;


#pragma pack(push, 1)
typedef struct _AMI_FCH_I2C_CONTROLLER_INFO {
    UINTN   ControllerNum;
    UINTN   MmioBase;
    BOOLEAN Enabled;
} AMI_FCH_I2C_CONTROLLER_INFO;

//
// Declare a local instance structure for this driver
//
struct _I2C_BUS_INSTANCE {
    UINT32                          Signature;
    UINT32                          Version;
    EFI_HANDLE                      Handle;
    UINTN                           I2cBase;
    AMI_I2C_LOCATION_INFO           Location;
    UINT8                           BusNo;
    AMI_I2C_HC_OPERATION_PROTOCOL   I2cHcOpProtocol;
};
#pragma pack()

EFI_STATUS
I2cHcOperationProtocolInit (
    IN AMI_I2C_HC_OPERATION_PROTOCOL     *I2cHcOperation
    );

#endif

