/*****************************************************************************
 *
 * Copyright 2015 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting You permission to use this software and documentation (if
 * any) (collectively, the "Software") pursuant to the terms and conditions of
 * the Software License Agreement included with the Software. If You do not have
 * a copy of the Software License Agreement, contact Your AMD representative for
 * a copy.
 *
 * You agree that You will not reverse engineer or decompile the Software, in
 * whole or in part, except as allowed by applicable law.
 *
 * WARRANTY DISCLAIMER: THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND. AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
 * BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, QUALITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT AND WARRANTIES
 * ARISING FROM CUSTOM OF TRADE OR COURSE OF USAGE WITH RESPECT TO THE SOFTWARE,
 * INCLUDING WITHOUT LIMITATION, THAT THE SOFTWARE WILL RUN UNINTERRUPTED OR
 * ERROR-FREE. THE ENTIRE RISK ASSOCIATED WITH THE USE OF THE SOFTWARE IS
 * ASSUMED BY YOU. Some jurisdictions do not allow the exclusion of implied
 * warranties, so the above exclusion may not apply to You, but only to the
 * extent required by law.
 *
 * LIMITATION OF LIABILITY AND INDEMNIFICATION: TO THE EXTENT NOT PROHIBITED BY
 * APPLICABLE LAW, AMD AND ITS LICENSORS WILL NOT, UNDER ANY CIRCUMSTANCES BE
 * LIABLE TO YOU FOR ANY PUNITIVE, DIRECT, INCIDENTAL, INDIRECT, SPECIAL OR
 * CONSEQUENTIAL DAMAGES ARISING FROM POSSESSION OR USE OF THE SOFTWARE OR
 * OTHERWISE IN CONNECTION WITH ANY PROVISION OF THIS AGREEMENT EVEN IF AMD AND
 * ITS LICENSORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. THIS
 * INCLUDES, WITHOUT LIMITATION, DAMAGES DUE TO LOST OR MISAPPROPRIATED DATA,
 * LOST PROFITS OR CONFIDENTIAL OR OTHER INFORMATION, FOR BUSINESS INTERRUPTION,
 * FOR PERSONAL INJURY, FOR LOSS OF PRIVACY, FOR FAILURE TO MEET ANY DUTY
 * INCLUDING OF GOOD FAITH OR REASONABLE CARE, FOR NEGLIGENCE AND FOR ANY OTHER
 * PECUNIARY OR OTHER LOSS WHTSOEVER. In no event shall AMD's total liability to
 * You for all damages, losses, and causes of action (whether in contract, tort
 * (including negligence) or otherwise) exceed the amount of $50 USD. You agree
 * to defend, indemnify and hold harmless AMD, its subsidiaries and affiliates
 * and their respective licensors, directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your
 * possession or use of the Software or violation of the terms and conditions of
 * this Agreement.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS: Notice to U.S. Government End Users. The
 * Software and related documentation are "commercial items", as that term is
 * defined at 48 C.F.R. Section 2.101, consisting of "commercial computer
 * software" and "commercial computer software documentation", as such terms are
 * used in 48 C.F.R. Section 12.212 and 48 C.F.R. Section 227.7202,
 * respectively. Consistent with 48 C.F.R. Section 12.212 or 48 C.F.R. Sections
 * 227.7202-1 through 227.7202-4, as applicable, the commercial computer
 * software and commercial computer software documentation are being licensed to
 * U.S. Government end users: (a) only as commercial items, and (b) with only
 * those rights as are granted to all other end users pursuant to the terms and
 * conditions set forth in this Agreement. Unpublished rights are reserved under
 * the copyright laws of the United States.
 *
 * EXPORT RESTRICTIONS:  You shall adhere to all applicable U.S. import/export
 * laws and regulations, as well as the import/export control laws and
 * regulations of other countries as applicable. You further agree You will not
 * export, re-export, or transfer, directly or indirectly, any product,
 * technical data, software or source code received from AMD under this license,
 * or the direct product of such technical data or software to any country for
 * which the United States or any other applicable government requires an export
 * license or other governmental approval without first obtaining such licenses
 * or approvals, or in violation of any applicable laws or regulations of the
 * United States or the country where the technical data or software was
 * obtained. You acknowledges the technical data and software received will not,
 * in the absence of authorization from U.S. or local law and regulations as
 * applicable, be used by or exported, re-exported or transferred to: (i) any
 * sanctioned or embargoed country, or to nationals or residents of such
 * countries; (ii) any restricted end-user as identified on any applicable
 * government end-user list; or (iii) any party where the end-use involves
 * nuclear, chemical/biological weapons, rocket systems, or unmanned air
 * vehicles.  For the most current Country Group listings, or for additional
 * information about the EAR or Your obligations under those regulations, please
 * refer to the website of the U.S. Bureau of Industry and Security at
 * http://www.bis.doc.gov/.
 ******************************************************************************
 */
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiDriverEntryPoint.h>
//#include <Protocol/AmdBoardIdProtocol.h>
#include "AmdXgbeWorkaround.h"
#include <AMD.h>
#include <Library/AmdBaseLib.h>
#include <Library/PcdLib.h>
#include <Library/PciLib.h>
#include <Protocol/FabricTopologyServices2.h>
#include <Protocol/xGbEI2cMaster.h>
#include <Library/IoLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/S3BootScriptLib.h>
#include <Fch.h>
#include <AmdCpmDxe.h>
#include <DwI2cRegs.h>

extern  EFI_BOOT_SERVICES       *gBS;
#define TEST_PCA9535_CONFIG     1
#define REV_A_BOARD 1
#define PORT_I2C_MUTEX        0x1D080ul

/**
 *---------------------------------------------------------------------------------------
 *
 *  getBitfield
 *
 *  Description:
 *    Read value of bits.
 *
 *  Parameters:
 *    @param[in]      Value       In coming value
 *
 *    @param[in]      *Lsb        Least significant bit to start reading
 *
 *    @param[in]      *Width      How many bits to read
 *
 *    @return         Value       Value after reading bits
 *
 *------------------------------------------------------------------------------------
 **/
STATIC
UINT32
getBitfield (
  IN UINT32 Value,
  IN UINT32 Lsb,
  IN UINT32 Width
  )
{
  UINT32 Mask;
  UINT32 i;

  Mask = 0;
  for (i = 0; i < Width; i++) {
    Mask |= 1 << i;
  }

  Value &= Mask << Lsb;

  return (Value >> Lsb);
}
/**
 *---------------------------------------------------------------------------------------
 *
 *  getBitfieldReg32
 *
 *  Description:
 *    Read value of bits.
 *
 *  Parameters:
 *    @param[in]      Addr       In coming Address
 *
 *    @param[in]      *Lsb        Least significant bit to start reading
 *
 *    @param[in]      *Width      How many bits to read
 *
 *    @return         Value       Value after reading bits
 *
 *------------------------------------------------------------------------------------
 **/
STATIC
UINT32
getBitfieldReg32 (
  IN UINT32 Addr,
  IN UINT32 Lsb,
  IN UINT32 Width
  )
{
  UINT32 Value;

  Value = MmioRead32 (Addr);
  return getBitfield (Value, Lsb, Width);
}

VOID
GetI2cOwnership (
  IN       UINT32 XgmacBase,
  IN       UINT8 MutexId
  )
{
  UINT32 MutexVal = 0;
  UINT32 MutexSet1 = 0;
  MutexVal |= MutexId;
  MutexVal <<= 29;
  MutexVal |= 1;

  if (XgmacBase == 0xFFFFFFFF || XgmacBase == 0) {
    return;
  }

  MmioWrite32 (XgmacBase + PORT_I2C_MUTEX, 0x80000000);
  gBS->Stall (1000);

  while(MmioRead32 (XgmacBase + PORT_I2C_MUTEX)){};

  do {
    MmioWrite32 (XgmacBase + PORT_I2C_MUTEX, MutexVal);
    gBS->Stall (1000);
    MutexSet1 = MmioRead32 (XgmacBase + PORT_I2C_MUTEX);
  } while (MutexSet1 != MutexVal);
}


VOID
PutI2cOwnership (
  IN       UINT32 XgmacBase,
  IN       UINT8 MutexId
  )
{
  if (XgmacBase == 0xFFFFFFFF || XgmacBase == 0) {
    return;
  }

  if (getBitfieldReg32 (XgmacBase + PORT_I2C_MUTEX, 29, 2) == MutexId) {
    MmioWrite32 (XgmacBase + PORT_I2C_MUTEX, 0x80000000);
  }
}

/*********************************************************************************
 * Name: SaveXgbeS3BootScript
 *
 * Description
 *   Save the S3 boot scritp for xgbe
 *
 * Input
 *   BusNumberBase : Base Bus number for XGBE PCI bridge
 *
 * Output
 *   VOID
 *********************************************************************************/
VOID
SaveXgbeS3BootScript(
    UINTN BusNumberBase
  )
{
  UINT64 BootScriptPciAddress;
  UINT16 CommandValue;
  UINT32 AddressValue;

  //
  // Ethernet functions are under the Bridge@ Device 8, function2
  //
  AddressValue = (MAKE_SBDFO (0, BusNumberBase, 0x8, FUNC_2, 0x4));
  CommandValue = PciRead16 (AddressValue);

  //Check for first 3-bits of command register for IO/Memory/Bus Master enable
  if( (CommandValue & 0x7) != 0x7)
  {
    CommandValue = (CommandValue | 0x7);
  }
  //Save the Command Register for the S3 boot script
  BootScriptPciAddress = S3_BOOT_SCRIPT_LIB_PCI_ADDRESS (BusNumberBase, 0x8, FUNC_2, 0x4);
  S3BootScriptSavePciCfgWrite (
    S3BootScriptWidthUint16,
    BootScriptPciAddress,
    1,
    &CommandValue
    );
	
  DEBUG((DEBUG_INFO, "SaveXgbeS3BootScript() exit\n"));
}
/*********************************************************************************
 * Name: XgbeGetBaseAddr
 *
 * Description
 *   Get Base address of XGBE
 *
 * Input
 *   XgbeData : XGBE data to store base address for each XGBE port
 *
 * Output
 *
 *********************************************************************************/
EFI_STATUS
XgbeGetBaseAddr (
  OUT  XGBE_DATA *XgbeData
  )
{
  UINT8 SecBusDie0, i, port;
  UINT8 BusMasterEn;
  UINT32 Value, XgmacBase, Xgmac0_Base, Xgmac1_Base, Xpcs0_Base, Xpcs1_Base;
  UINTN BusNumberBase, SocketNum, DieNum; 
  PCI_ADDR  PciAddress;
  EFI_STATUS Status;
  AMD_FABRIC_TOPOLOGY_SERVICES2_PROTOCOL *FabricTopology;
  
  XgmacBase = 0;
  Xgmac0_Base = 0;
  Xgmac1_Base = 0;
  Xpcs0_Base = 0;
  Xpcs1_Base = 0;
  BusNumberBase = 0;
  SocketNum = 0;
  DieNum = 0;
  BusMasterEn = 0;
  SecBusDie0 = 0;

  DEBUG((DEBUG_INFO, "In XgbeGetBaseAddr\n"));
  //
  // Get Base address for XGMAC and  XPCS
  // Get the Base BUS# first.
  //
  Status = gBS->LocateProtocol (
                &gAmdFabricTopologyServices2ProtocolGuid,
                NULL,
                &FabricTopology
                );

  if (FabricTopology->GetRootBridgeInfo (FabricTopology, SocketNum, DieNum, 0, NULL, &BusNumberBase, NULL, NULL, NULL, NULL) != EFI_SUCCESS) {
    DEBUG ((DEBUG_INFO, "GetRootBridgeInfo returned Status = %r\n", Status));
    Status = EFI_DEVICE_ERROR;
  }

  SaveXgbeS3BootScript(BusNumberBase);

  //
  // Ethernet functions are under the Bridge@ Device 8, function2
  //
  PciAddress.AddressValue = (MAKE_SBDFO (0, BusNumberBase, 0x8, FUNC_2, 0x19));
  SecBusDie0 = PciRead8 (PciAddress.AddressValue);

  DEBUG((DEBUG_INFO, "BusNumberBase = %x, SecBusDie0 = %x\n", BusNumberBase, SecBusDie0));

  //
  // for Raven,
  // Port0 => Bus B, Device 0, Function 1
  // Port1 => Bus B, Device 0, Function 2
  //
  // Port0, Enable Bus master enable bit
  //
  PciAddress.AddressValue = (MAKE_SBDFO (0, SecBusDie0, 0x0, FUNC_1, 0x4));
  BusMasterEn = PciRead8 (PciAddress.AddressValue);
  BusMasterEn |= 0x6;
  PciWrite8 (PciAddress.AddressValue, BusMasterEn);

  //
  // Get the MAC and the PCS base addresses from the config space
  //
  PciAddress.AddressValue = (MAKE_SBDFO (0, SecBusDie0, 0x0, FUNC_1, 0x10));
  Xgmac0_Base = PciRead32 (PciAddress.AddressValue);
  PciAddress.AddressValue = (MAKE_SBDFO (0, SecBusDie0, 0x0, FUNC_1, 0x14));
  Xpcs0_Base = PciRead32 (PciAddress.AddressValue);

  DEBUG((DEBUG_INFO, "Xgmac0_Base = %x, Xpcs0_Base = %x\n", Xgmac0_Base, Xpcs0_Base));

  //
  // Port1, Enable the Bus master enable bit
  //
  PciAddress.AddressValue = (MAKE_SBDFO (0, SecBusDie0, 0x0, FUNC_2, 0x4));
  BusMasterEn = PciRead8 (PciAddress.AddressValue);
  BusMasterEn |= 0x6;
  PciWrite8 (PciAddress.AddressValue, BusMasterEn);

  //
  // Get the MAC and PCS base addresses from the config space
  //
  PciAddress.AddressValue = (MAKE_SBDFO (0, SecBusDie0, 0x0, FUNC_2, 0x10));
  Xgmac1_Base = PciRead32 (PciAddress.AddressValue);
  PciAddress.AddressValue = (MAKE_SBDFO (0, SecBusDie0, 0x0, FUNC_2, 0x14));
  Xpcs1_Base = PciRead32 (PciAddress.AddressValue);

  DEBUG((DEBUG_INFO, "Xgmac1_Base = %x, Xpcs1_Base = %x\n", Xgmac1_Base, Xpcs1_Base));

  XgbeData->Xgmac0BaseAdd = 0;
  XgbeData->Xgmac1BaseAdd = 0;

  //Program for XGBE ECC Interrupt.
  for (port = 0; port < NUMBER_OF_ETH_PORTS; port++){
    if (port == 0) { 
      if(Xgmac0_Base == 0xFFFFFFFF) {
        continue;
      }
      XgmacBase = Xgmac0_Base;
      XgbeData->Xgmac0BaseAdd = Xgmac0_Base;
    }
    if (port == 1) { 
      if(Xgmac1_Base == 0xFFFFFFFF) {
        break;
      }
      XgmacBase = Xgmac1_Base;
      XgbeData->Xgmac1BaseAdd = Xgmac1_Base;
    }

    if (getBitfieldReg32 (XgmacBase + 0x1d030, 0, 6) == 0 ) {
      DEBUG ((EFI_D_ERROR, " ECC already addressed for Port %x \n", port));
      continue;
    }

    MmioWrite32 (XgmacBase + 0x1008, 0x103);
    while (getBitfieldReg32 (XgmacBase + 0x100C, 0, 1) != 0);
    MmioWrite32 (XgmacBase + 0x1010, 0x0);
    //write rx_fifo
    for (i = 0; i <= 3; i++) {
      MmioWrite32 (XgmacBase + 0x1008, 0x380f);
      while (getBitfieldReg32 (XgmacBase + 0x100C, 0, 1) != 0);
    }

    for (i = 0; i <= 3; i++) {
      MmioWrite32 (XgmacBase + 0x1008, 0x80f);
      while (getBitfieldReg32 (XgmacBase + 0x100C, 0, 1) != 0);
    }
    for (i = 0; i <= 3; i++) {
      MmioWrite32 (XgmacBase + 0x1008, 0x180f);
      while (getBitfieldReg32 (XgmacBase + 0x100C, 0, 1) != 0);
    }

    for (i = 0; i <= 3; i++) {
      MmioWrite32 (XgmacBase + 0x1008, 0x340f);
      do {
        Value = MmioRead32 (XgmacBase + 0x100C);
        Value = getBitfieldReg32 (XgmacBase + 0x100C, 0, 1);
      } while (Value != 0);
      Value = MmioRead32 (XgmacBase + 0x1010);
    }

    for (i = 0; i <= 3; i++) {
      MmioWrite32 (XgmacBase + 0x1008, 0x40f);
      while (getBitfieldReg32 (XgmacBase + 0x100C, 0, 1) != 0);
      Value = MmioRead32 (XgmacBase + 0x1010);
    }
    for (i = 0; i <= 3; i++) {
      MmioWrite32 (XgmacBase + 0x1008, 0x140f);
      while (getBitfieldReg32 (XgmacBase + 0x100C, 0, 1) != 0);
      Value = MmioRead32 (XgmacBase + 0x1010);
    }
    MmioWrite32 (XgmacBase + 0x1d030, 0x3f);

  }

  return (Status);
}

/*********************************************************************************
 * Name: XgbeReadEeprom
 *
 * Description
 *   Call to Read XGBE I2Cdevices
 *
 * Input
 *   XgbeBaseAdd:   XGBE Base address.\
 *   SlaveAdd:      Slave Address of I2C
 *   Offset:        Offset to write to
 *   DataLength:    Size of Data to be Read from device.
 *
 * Output
 *   Data read from device
 *
 *********************************************************************************/
UINT16
XgbeReadEeprom(
  UINT32 XgbeBaseAdd,
  UINT8 SlaveAdd,
  UINT8 Offset,
  UINT16 DataLength
  )
{
  XGBE_I2C_MASTER_PROTOCOL  *XgbEI2cMaster;
  UINT8                     PacketBuffer[sizeof(EFI_I2C_REQUEST_PACKET) + sizeof(EFI_I2C_OPERATION)];
  EFI_I2C_REQUEST_PACKET    *RequestPacket;
  EFI_I2C_OPERATION         *Operation;
  EFI_STATUS                Status;
  UINT8                     Data[2];
  UINT16                    Pca9555Data;
  UINT32                    XgmacBaseI2c;

  Status =                  EFI_SUCCESS;
  Pca9555Data =             0;
  Data[0] =                 0;
  Data[1] =                 0;

  //
  // I2C registers for ethernet is mapped to BAR0 @offset 1E000
  //
  XgmacBaseI2c = XgbeBaseAdd + 0x1E000;

  DEBUG((DEBUG_INFO, "XgmacBaseI2c = %x\n", XgmacBaseI2c));
  Status = gBS->LocateProtocol (&gxGbEI2cMasterProtocolGuid, NULL, &XgbEI2cMaster);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "\nXGMAC Workaround: Could not Locate I2C Protocol.\n"));
  }

  XgbEI2cMaster->BaseAddress = XgmacBaseI2c;
  XgbEI2cMaster->I2cInit(XgbEI2cMaster);
  RequestPacket = (EFI_I2C_REQUEST_PACKET*)PacketBuffer;
  Operation   = RequestPacket->Operation;
  RequestPacket->OperationCount = 2;
  Operation[0].Flags            = 0;
  Operation[0].LengthInBytes    = sizeof(UINT8);
  Operation[0].Buffer           = &Offset;
  Operation[1].Flags            = I2C_FLAG_READ;
  Operation[1].LengthInBytes    = DataLength;
  Operation[1].Buffer           = Data;

  Status = XgbEI2cMaster->StartRequest(XgbEI2cMaster, SlaveAdd, RequestPacket, NULL, NULL);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "\nXGMAC: Failed to StartRequest.\n"));
  }
  Pca9555Data = (Data[1] << 8) | Data[0];
  return Pca9555Data;
}

/*********************************************************************************
 * Name: XgbeWriteEeprom
 *
 * Description
 *   Call to write to XGBE I2C devices 

 *
 * Input
 *   XgbeBaseAdd : XGBE Base address.\
 *   SlaveAdd:     Slave Address of I2C
 *   Offset:       Offset to write to
 *   Data:         Data to be written on device.
 *
 * Output
 *
 *********************************************************************************/

EFI_STATUS
XgbeWriteEeprom(
  UINT32 XgbeBaseAdd,
  UINT8 SlaveAdd,
  UINT8 Offset,
  UINT16 Data
  )
{
  XGBE_I2C_MASTER_PROTOCOL  *XgbEI2cMaster;
  EFI_I2C_REQUEST_PACKET    RequestPacket;
  EFI_I2C_OPERATION         *Operation;
  EFI_STATUS                Status;
  UINT8                     Buffer[3];
  UINT32                    XgmacBaseI2c;
  Status =                  EFI_SUCCESS;

  //
  // I2C registers for ethernet is mapped to BAR0 @offset 1E000
  //
  XgmacBaseI2c = XgbeBaseAdd + 0x1E000;
  Status = gBS->LocateProtocol (&gxGbEI2cMasterProtocolGuid, NULL, &XgbEI2cMaster);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "\nXGMAC Workaround: Could not Locate I2C Protocol.\n"));
  }
  XgbEI2cMaster->BaseAddress = XgmacBaseI2c;
  XgbEI2cMaster->I2cInit(XgbEI2cMaster);

  //Prepare write data buffer
  Buffer[0] = Offset;
  Buffer[1] = (UINT8)(Data & 0x00FF); //Low byte
  Buffer[2] = (UINT8)(Data >> 8);     //High byte

  Operation   = RequestPacket.Operation;
  RequestPacket.OperationCount = 1;
  Operation[0].Flags            = 0;
  Operation[0].LengthInBytes    = 3;
  Operation[0].Buffer           = &Buffer[0];

  Status = XgbEI2cMaster->StartRequest(XgbEI2cMaster, SlaveAdd, &RequestPacket, NULL, NULL);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "\nXGMAC: Failed to StartRequest.\n"));
  }

  return Status;
}

/*********************************************************************************
 * Name: XgbeI2cRecovery
 *
 * Description
 *   Recovers the Xgbe I2c when SDA stuck low
 *    *
 * Input
 *   XgbeData : XGBE DATA holds the base address of each XGBE port
 *
 * Output
 *  VOID
 *
 *********************************************************************************/
VOID
XgbeI2cRecovery(
    XGBE_DATA *XgbeData
    )
{
  EFI_STATUS                Status;
  UINT8                     IOMUXx28Value;
  UINT8                     IOMUXx0AValue;
  AMD_CPM_TABLE_PROTOCOL    *CpmTableProtocolPtr;
  UINT8                     GpioValue;
  UINT32                    Count = 0;
  UINT32                    TogCount = 0;
  UINT32                    XgbeBaseAdd = 0;

  DEBUG((EFI_D_ERROR, "XgbeI2cRecovery() Entry\n"));

  Status = gBS->LocateProtocol (  &gAmdCpmTableProtocolGuid,
                                    NULL,
                                    (VOID**)&CpmTableProtocolPtr
                                    );
  if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "CpmTableProtocolPtr LocateProtocol failed:%r\n",Status));
      return;
  }

  // store the IOMUX values; later these values will be restored
  IOMUXx28Value = MmioRead8(FCH_IOMUXx28_AGPIO40_SGPIO_DATAIN_MDIO0_SDA);
  // Enable AGPIO40 and Check GPIO value
  MmioWrite8(FCH_IOMUXx28_AGPIO40_SGPIO_DATAIN_MDIO0_SDA,0);
  GpioValue = CpmTableProtocolPtr->CommonFunction.GetGpio(CpmTableProtocolPtr, FCH_GPIO_REG40 );
  DEBUG((EFI_D_ERROR, "GpioValue :%d\n",GpioValue));
  if( GpioValue == 0 )
  {
    //Program IC_Enable to 0
    if (XgbeData->Xgmac0BaseAdd) {
        XgbeBaseAdd = XgbeData->Xgmac0BaseAdd;
    }else {
        XgbeBaseAdd = XgbeData->Xgmac1BaseAdd;
    }
    DEBUG((EFI_D_ERROR, "XgbeBaseAdd :%x\n",XgbeBaseAdd));
    if(XgbeBaseAdd == NULL)
	{
		MmioWrite8(FCH_IOMUXx28_AGPIO40_SGPIO_DATAIN_MDIO0_SDA,IOMUXx28Value);
        return;
	}
    MmioWrite32(XgbeBaseAdd + DW_IC_ENABLE, 0);

    //Change to GPIO10
    IOMUXx0AValue = MmioRead8(FCH_IOMUXx28_AGPIO10_SGPIO_DATAIN_MDIO0_SDA);
    MmioWrite8(FCH_IOMUXx28_AGPIO10_SGPIO_DATAIN_MDIO0_SDA,0);

    //Toggle the CLK and check SDA
    while( Count <= 10 )
    {
        for(TogCount=0; TogCount<=19; TogCount++)
        {
            CpmTableProtocolPtr->CommonFunction.SetGpio (CpmTableProtocolPtr, FCH_GPIO_REG10, 0);
            gBS->Stall (10);//10us
            CpmTableProtocolPtr->CommonFunction.SetGpio (CpmTableProtocolPtr, FCH_GPIO_REG10, 1);
            gBS->Stall (10);
        }
        GpioValue = CpmTableProtocolPtr->CommonFunction.GetGpio(CpmTableProtocolPtr, FCH_GPIO_REG40 );
        Count++;
        if ( GpioValue == 1 )
            break;
    }

    //Generate a pulse on GPIO40
    CpmTableProtocolPtr->CommonFunction.SetGpio (CpmTableProtocolPtr, FCH_GPIO_REG40, 0);
    gBS->Stall (11);
    CpmTableProtocolPtr->CommonFunction.SetGpio (CpmTableProtocolPtr, FCH_GPIO_REG40, 1);

    MmioWrite8(FCH_IOMUXx28_AGPIO10_SGPIO_DATAIN_MDIO0_SDA,IOMUXx0AValue);
    DEBUG((EFI_D_ERROR, "Restored after cycles:%d,GpioValue:%d\n",Count,GpioValue));
  }

  //Restore IOMUX28
  MmioWrite8(FCH_IOMUXx28_AGPIO40_SGPIO_DATAIN_MDIO0_SDA,IOMUXx28Value);

}
/*********************************************************************************
 * Name: XgbeTxDisableLow
 *
 * Description
 *   Work around to set TX_DISABLE pin to low.
 *
 * Input
 *   XgbeData : XGBE DATA holds the base address of each XGBE port
 *
 * Output
 *   EFI_SUCCESS : Module initialized successfully
 *   EFI_ERROR   : Initialization failed (see error for more details)
 *
 *********************************************************************************/

EFI_STATUS
XgbeTxDisableLow (
  XGBE_DATA *XgbeData
  )
{
  UINT16 Data;
  UINT8 SlaveAdd;
  UINT16 DataSize;
  UINT32 XgbeBaseAdd;
  UINT8 Offset;

  EFI_STATUS Status;
  
  DEBUG ((EFI_D_INFO, "In XgbeTxDisableLow Start \n"));

  XgbeI2cRecovery(XgbeData);
  // Port 0
  Status = EFI_SUCCESS;
  
  if (XgbeData->Xgmac0BaseAdd) {
    SlaveAdd = (UINT8)(PCA9535_ADDRESS + getBitfieldReg32 (XgbeData->Xgmac0BaseAdd + ENET_PORT_PROPERTY_3, 8, 3));
    DEBUG ((EFI_D_ERROR, " PORT 0 PCA9535 SlaveAdd = 0x%x \n", SlaveAdd));
    DataSize = sizeof (UINT16);
    XgbeBaseAdd = XgbeData->Xgmac0BaseAdd;

    Offset = 6;       // PCA9535 Config register offset
    Data = 0;
    Data = XgbeReadEeprom(XgbeBaseAdd, SlaveAdd, Offset, DataSize);
    DEBUG ((EFI_D_ERROR, " PCA9535 Config register read data = %x \n", Data));
    
    // I/O 0_7 to I/O 0_0 (  0 => output and 1 => input)
    // (0111 1111 = 0x7F)
    // I/O 1_7 to I/O 1_0 (0,1,1,1,1,1,1,1) ( 0111 1111 = 0x7F)
    Data &= 0x7F7F; // This statement make sure output set as 0 properly
    Data |= 0x7F7F; // This statement make sure input set as 1 properly
    DEBUG ((EFI_D_ERROR, " PCA9535 Config register before write data = %x \n", Data));
    XgbeWriteEeprom(XgbeBaseAdd, SlaveAdd, Offset, Data);
    
    Data = 0;
    Data = XgbeReadEeprom(XgbeBaseAdd, SlaveAdd, Offset, DataSize);
    DEBUG ((EFI_D_ERROR, " PCA9535 Config register read data = %x \n", Data));  

    Offset = 2;       // PCA9535 output port register. 
    Data = XgbeReadEeprom(XgbeBaseAdd, SlaveAdd, Offset, DataSize);

    // SFP+_XGB1_DISABLE (I/O 0_7) =>  High:Disable the transmitter  Low : Enable the Transmiter
    // SFP+_XGB0_DISABLE (I/O 1_7) =>  High:Disable the transmitter  Low : Enable the Transmiter
    // Input port value is ignored even if we configure any value.
    Data &= 0x0000; 
    
    XgbeWriteEeprom(XgbeBaseAdd, SlaveAdd, Offset, Data);
    
#ifdef TEST_PCA9535_CONFIG   
    Data = 0;
    Data = XgbeReadEeprom(XgbeBaseAdd, SlaveAdd, Offset, DataSize);
    DEBUG ((EFI_D_ERROR, " Xgmac0 PCA9535 Output port register read data = %x \n", Data));
#endif  
  }

  //Port 1
  Status = EFI_SUCCESS;
  if(XgbeData->Xgmac1BaseAdd) {

    if (XgbeData->Xgmac0BaseAdd == 0) { 
      GetI2cOwnership(XgbeData->Xgmac1BaseAdd, 1);
    }

    SlaveAdd = (UINT8)(PCA9535_ADDRESS + getBitfieldReg32 (XgbeData->Xgmac1BaseAdd + ENET_PORT_PROPERTY_3, 8, 3));
    DEBUG ((EFI_D_ERROR, " PORT 1 PCA9535 SlaveAdd = 0x%x \n", SlaveAdd));
    DataSize = sizeof (UINT16);
    XgbeBaseAdd = XgbeData->Xgmac1BaseAdd;

    Offset = 6;       // PCA9535 Config register offset
    Data = XgbeReadEeprom(XgbeBaseAdd, SlaveAdd, Offset, DataSize);
    DEBUG ((EFI_D_ERROR, " PCA9535 Config register read data = %x \n", Data));

    // I/O 0_7 to I/O 0_0 (  0 => output and 1 => input)
    // (0111 1111 = 0x7F)
    // I/O 1_7 to I/O 1_0 (0111 1111 = 0x7F)
    Data &= 0x7F7F; // This statement make sure output set as 0 properly
    Data |= 0x7F7F; // This statement make sure input set as 1 properly
    DEBUG ((EFI_D_ERROR, " PCA9535 Config register before write data = %x \n", Data));
    XgbeWriteEeprom(XgbeBaseAdd, SlaveAdd, Offset, Data);

    Data = 0;
    Data = XgbeReadEeprom(XgbeBaseAdd, SlaveAdd, Offset, DataSize);
    DEBUG ((EFI_D_ERROR, " PCA9535 Config register read data = %x \n", Data));  

    Offset = 2;       // PCA9535 output port register. 
    Data = XgbeReadEeprom(XgbeBaseAdd, SlaveAdd, Offset, DataSize);

    // SFP+_XGB1_DISABLE (I/O 0_7) =>  High:Disable the transmitter  Low : Enable the Transmiter
    // SFP+_XGB0_DISABLE (I/O 1_7) =>  High:Disable the transmitter  Low : Enable the Transmiter
    Data &= 0x0000; 
    XgbeWriteEeprom(XgbeBaseAdd, SlaveAdd, Offset, Data);
    
    #ifdef TEST_PCA9535_CONFIG  
    Data = 0;
    Data = XgbeReadEeprom(XgbeBaseAdd, SlaveAdd, Offset, DataSize);
    DEBUG ((EFI_D_ERROR, " Xgmac1 PCA9535 Output port register read data = %x \n", Data));  
    #endif

    if (XgbeData->Xgmac0BaseAdd == 0) { 
      PutI2cOwnership(XgbeData->Xgmac1BaseAdd, 1);
    }
  }
  DEBUG ((EFI_D_ERROR, "In XgbeTxDisableLow End \n"));
  return Status;
}

/*********************************************************************************
 * Name: AmdXgbeWorkaroundDxeInit
 *
 * Description
 *   Entry point of the AMD XGBE WORK AROUND DXE driver
 *   Perform the required work around needed for XGBE.
 *
 * Input
 *   ImageHandle : EFI Image Handle for the DXE driver
 *   SystemTable : pointer to the EFI system table
 *
 * Output
 *   EFI_SUCCESS : Module initialized successfully
 *   EFI_ERROR   : Initialization failed (see error for more details)
 *
 *********************************************************************************/

EFI_STATUS
EFIAPI
AmdXgbeWorkaroundDxeInit (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS   Status;
  XGBE_DATA   *XgbeData;

  DEBUG ((EFI_D_INFO, "In AmdXgbeWorkaroundDxeInit\n"));

  Status = EFI_SUCCESS;
  if(PcdGet8(PcdXgbeDisable))
    return Status;

  if(PcdGet8 (PcdBoardRevision)== REV_A_BOARD )  {
    DEBUG ((EFI_D_INFO, "Bilby Rev A board:skipping XGBE workaround\n"));
    return (Status);
  }
  XgbeData = AllocateZeroPool (sizeof (XGBE_DATA));
  if (XgbeData == NULL) {
    DEBUG ((EFI_D_ERROR, "Could not allocate XGBE_DATA structures.\n"));
    return EFI_OUT_OF_RESOURCES;
  }


  if(PcdGetBool (PcdXgbeSfp)) {
    Status = XgbeGetBaseAddr (XgbeData);
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "\n XgbeGetBaseAddr failed\n"));
    }
    Status = XgbeTxDisableLow (XgbeData);
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "\n XgbeTxDisableLow failed\n"));
    }
  }
  return (Status);
}
