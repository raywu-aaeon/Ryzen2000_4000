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

/** @file AmiI2cHcOperation.h
    This file contains Ami I2C HC Operation Protocol data structures 
    definitions
*/

#ifndef _AMI_I2C_HC_OPERATION_H_
#define _AMI_I2C_HC_OPERATION_H_

#include <Pi/PiI2c.h>

// {61984EAE-5D17-458B-9292-7C7D0CBD0903}
#define AMI_I2C_HC_OPERATION_PROTOCOL_GUID \
  { \
    0x61984eae, 0x5d17, 0x458b, 0x92, 0x92, 0x7c, 0x7d, 0xc, 0xbd, 0x9, 0x3 \
  }

#define AMI_I2C_HC_VERSION_1  0x00000001

typedef struct _AMI_I2C_HC_OPERATION_PROTOCOL  AMI_I2C_HC_OPERATION_PROTOCOL;

typedef
enum{
  MasterMode = 0,
  SlaveMode
}I2C_ACTIVE_MODE;

//
//  Frequency of I2C Host
//
#define I2C_HC_100KHZ  (100 * 1000)
#define I2C_HC_400KHZ  (400 * 1000)
#define I2C_HC_1MHZ    (1000 * 1000)
#define I2C_HC_3_4MHZ  (3400 * 1000)

/**** PORTING REQUIRED ****
//
// I2C Bus/Dev/Func #
//
#define PCI_DEVICE_NUMBER_I2C0      22
#define PCI_DEVICE_NUMBER_I2C1      23
#define PCI_FUNCTION_NUMBER_I2C0    0
#define PCI_FUNCTION_NUMBER_I2C1    1
#define PCI_FUNCTION_NUMBER_I2C2    2
#define PCI_FUNCTION_NUMBER_I2C3    3
#define PCI_FUNCTION_NUMBER_I2C4    0
#define PCI_FUNCTION_NUMBER_I2C5    1
#define PCI_FUNCTION_NUMBER_I2C6    2
#define PCI_FUNCTION_NUMBER_I2C7    3
**** PORTING REQUIRED ****/

//
// Capabilities for I2C HC
//
#define I2C_HC_CAP_10BIT_ADDR   BIT0
#define I2C_HC_CAP_SWITCH_MODE  BIT1

typedef union {
  UINTN                     Capabilities;
  UINTN                     BaseAddress;
} AMI_I2C_LOCATION_INFO;

/**

  Get where the current host controller

  @param[in]   This                  I2C Host Controller
  @param[out]  Info                  Get the host info

  @retval EFI_SUCCESS
  @retval EFI_INVALID_PARAMETER      Info was NULL  

**/
typedef
EFI_STATUS
(EFIAPI *I2C_HC_GET_INFO)(
  IN  CONST AMI_I2C_HC_OPERATION_PROTOCOL   *This,
  OUT       AMI_I2C_LOCATION_INFO           *Info
  );

/**

  Access the I2C bus

  @param[in]      This                  I2C Host Controller
  @param[in]      SlaveAddress          Device slave address
  @param[in]      RequestPacket         read/write packages
  @param[in]      Event                 triggered Event after executed RequestPacket
  @param[out]     I2cStatus             Optional buffer to receive the I2C transaction
                                        completion status

  @retval EFI_SUCCESS
  @retval EFI_DEVICE_ERROR      I2C bus not exist
  @retval EFI_TIMEOUT           Device is no acknowledge

**/
typedef
EFI_STATUS
(EFIAPI *I2C_HC_REQUEST)(
  IN  CONST AMI_I2C_HC_OPERATION_PROTOCOL  *This,
  IN        UINTN                          SlaveAddress,
  IN        EFI_I2C_REQUEST_PACKET         *RequestPacket,
  IN        EFI_EVENT                      Event      OPTIONAL,
  OUT       EFI_STATUS                     *I2cStatus OPTIONAL
  );

/**

  Get the I2C Bus Configuration of Frequency

  @param[in]   This                  I2C Host Controller
  @param[out]  Freq                  Current I2C bus Freq
  
  @retval EFI_SUCCESS                The I2C bus frequency was returned
                                     successfully.
  @retval EFI_INVALID_PARAMETER      Freq was NULL


**/
typedef
EFI_STATUS
(EFIAPI *I2C_HC_GET_CONFIGURATION) (
  IN  CONST AMI_I2C_HC_OPERATION_PROTOCOL   *This,
  OUT       UINTN                           *Freq
  );

/**

  Set the I2C Bus Configuration of Frequency, default value is 100KHz

  @param[in]   This                  I2C Host Controller
  @param[in]   Freq                  I2C bus Freq
  
  @retval EFI_SUCCESS
  @retval EFI_NO_MAPPING             wrong frequence

**/
typedef
EFI_STATUS
(EFIAPI *I2C_HC_SET_CONFIGURATION) (
  IN  CONST AMI_I2C_HC_OPERATION_PROTOCOL   *This,
  IN        UINTN                           Freq
  );

/**

  Reset I2C Host

  @param[in]  This                  I2C Host Controller
  @param[in]  Slave                 I2C Slave Addr
  
  @retval EFI_SUCCESS

**/
typedef
EFI_STATUS
(EFIAPI *I2C_HC_RESET) (
  IN  CONST AMI_I2C_HC_OPERATION_PROTOCOL   *This,
  IN  UINTN                                 Slave
  );

/**

  Switch I2C host controller to Slave/Master mode

  @param[in]  This                  I2C Host Controller
  @param[out] Mode                  Switch the I2C to Slave/Master mode
  
  @retval EFI_SUCCESS
  @retval EFI_UNSUPPORTED           Doesn't support this function

**/
typedef
EFI_STATUS
(EFIAPI *I2C_HC_SWITCH_MODE) (
  IN  CONST AMI_I2C_HC_OPERATION_PROTOCOL   *This,
  IN  OUT I2C_ACTIVE_MODE                   Mode
  );

#pragma pack(1)

struct _AMI_I2C_HC_OPERATION_PROTOCOL {
  UINT32                            Version;
  I2C_HC_GET_INFO                   GetInfo;
  I2C_HC_GET_CONFIGURATION          GetConfiguration;
  I2C_HC_SET_CONFIGURATION          SetConfiguration;
  I2C_HC_REQUEST                    StartRequest;
  I2C_HC_RESET                      Reset;
  I2C_HC_SWITCH_MODE                Switch;
};

#pragma pack()

extern EFI_GUID gAmiI2cHcOperationProtocolGuid;

#endif

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
