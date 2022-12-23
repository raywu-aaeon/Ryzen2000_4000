/* $NoKeywords:$ */
/**
 * @file
 *
 * Config Fch Spi (Lpc) controller
 *
 * Init Spi (Lpc) Controller features.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: FCH
 * @e \$Revision: 309083 $   @e \$Date: 2014-12-09 09:28:24 -0800 (Tue, 09 Dec 2014) $
 *
 */
/*
*****************************************************************************
*
* Copyright 2008 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
*******************************************************************************
*/
#include "FchPlatform.h"
#define FILECODE PROC_FCH_SANDSTONE_SSSPI_SSSPIENV_FILECODE
#define SPI_BASE 0xFEC10000ul

VOID
FchWriteSpiExtReg (
  IN       UINT8      SpiExtRegIndex,
  IN       UINT8      SpiExtRegData
  );

VOID
FchSetSpiCounter (
  IN       UINT8      TxCounter,
  IN       UINT8      RxCounter
  );

VOID
FchSpiControllerNotBusy (
  );

VOID
FchSpiExecute (
  );

VOID
FchResetFifo (
  );

BOOLEAN
WaitForSpiDeviceWriteEnabled (
  );

BOOLEAN
WaitForSpiDeviceComplete (
  );

VOID
FchSetQualMode (
  IN       UINT32      SpiQualMode,
  IN       AMD_CONFIG_PARAMS         *StdHeader
  );

UINT32
FchReadSpiId (
  IN       BOOLEAN    Flag
  );

BOOLEAN
FchReadSpiQe (
  IN OUT   SPI_DEVICE_PROFILE    *SpiDeviceProfilePtr,
  IN       UINT32     SpiQeRegValue
  );

VOID
FchWriteSpiQe (
  IN OUT   SPI_DEVICE_PROFILE    *SpiDeviceProfilePtr,
  IN       UINT32     SpiQeRegValue
  );

BOOLEAN
FchFindSpiDeviceProfile (
  IN       UINT32     DeviceID,
  IN OUT   SPI_DEVICE_PROFILE    *SpiDeviceProfilePtr
  );


BOOLEAN
FchConfigureSpiDeviceDummyCycle (
  IN       UINT32     DeviceID,
  IN       UINT8      SpiMode
  );

BOOLEAN
AutoSpiModeSpeed (
  IN       VOID     *FchDataPtr
  );

VOID
FchSetSpi (
  IN  VOID     *FchDataPtr
  );

SPI_CONTROLLER_PROFILE SpiControllerProfile[4] = {
  {128, 100, 100, 100, 100},
  {128,  66,  66,  66,  66},
  {128,  33,  33,  33,  33},
  {128,  16,  16,  16,  16},
  };
SPI_DEVICE_PROFILE DefaultSpiDeviceTable[] = {
  //JEDEC_ID,RomSize,SecSize;MaxNormal;MaxFast;MaxDual;MaxQuad;QeReadReg;QeWriteReg;QeRegSize;QeLocation;
  {0x001524C2, 2 << 20, 4096,  33, 108, 150, 300, 0x05, 0x01, 0x1, 0x0040}, //Macronix_MX25L1635D
  {0x001525C2, 2 << 20, 4096,  33, 108, 160, 432, 0x05, 0x01, 0x1, 0x0040}, //Macronix_MX25L1635E
  {0x00165EC2, 4 << 20, 4096,  33, 104, 208, 400, 0x05, 0x01, 0x1, 0x0040}, //Macronix_MX25L3235D
//  {0x003625C2, 4 << 20, 4096,  33, 104, 168, 432, 0x05, 0x01, 0x1, 0x0040}, //Macronix_MX25U3235F
  {0x001720C2, 8 << 20, 4096,  50, 104, 140, 280, 0x05, 0x01, 0x1, 0x0040}, //Macronix_MX25L6436E
  {0x003725C2, 8 << 20, 4096,  33, 104, 168, 432, 0x05, 0x01, 0x1, 0x0040}, //Macronix_MX25U6435F
  {0x003825C2, 16 << 20, 4096,  33, 104, 168, 432, 0x05, 0x01, 0x1, 0x0040}, //Macronix_MX25U12835F
  {0x003925C2, 32 << 20, 4096,  33, 104, 168, 432, 0x05, 0x01, 0x1, 0x0040}, //Macronix_MX25U25645G //PLAT-31651

  {0x0046159D, 4 << 20, 4096,  33, 104, 208, 400, 0x05, 0x01, 0x1, 0x0040}, //PFLASH Pm25LQ032C

  {0x001540EF, 2 << 20, 4096,  33, 104, 208, 416, 0x35, 0x01, 0x2, 0x0200}, //Wnbond_W25Q16CV
  {0x001640EF, 4 << 20, 4096,  33, 104, 208, 320, 0x35, 0x01, 0x2, 0x0200}, //Wnbond_W25Q32BV
  {0x001740EF, 8 << 20, 4096, 104, 104, 208, 416, 0x35, 0x01, 0x2, 0x0200}, //Wnbond_W25Q64
  {0x001760EF, 8 << 20, 4096, 104, 104, 208, 416, 0x35, 0x01, 0x2, 0x0200}, //Wnbond_W25Q64FW
  {0x001860EF, 16<< 20, 4096, 104, 104, 208, 416, 0x35, 0x01, 0x2, 0x0200}, //Wnbond_W25Q128FW

  {0x004326BF, 8 << 20, 4096,  40, 104, 160, 416, 0x35, 0x01, 0x2, 0x0200}, //SST26VF064BA


  {0x001640C8, 4 << 20, 4096,  33, 100, 160, 320, 0x35, 0x01, 0x2, 0x0200}, //GigaDecice GD25Q32BSIGR
  {0x001760C8, 8 << 20, 4096,  100, 100, 160, 320, 0x35, 0x01, 0x2, 0x0200}, //GigaDecice GD25LB64
  {0x001860C8, 16<< 20, 4096,  100, 100, 160, 320, 0x35, 0x01, 0x2, 0x0200}, //GigaDecice GD25LQ128C

  {0x00164037, 4 << 20, 4096,  33, 100, 200, 400, 0x35, 0x01, 0x2, 0x0200}, //AMIC A25LQ32B

  {0x00164001, 4 << 20, 4096,  50, 108, 216, 432, 0x35, 0x01, 0x3, 0x0200}, //S25FL132K
  {0x00174001, 8 << 20, 4096,  50, 108, 216, 432, 0x35, 0x01, 0x3, 0x0200}, //S25FL164K
  {0x00182001, 16<< 20, 4096,  50, 108, 216, 432, 0x35, 0x01, 0x2, 0x0200}, //S25FS128S

  {0x0016BA20, 4 << 20, 4096, 108, 108, 216, 432, 0x00, 0x00, 0x1, 0x0000}, //N25Q032
  {0x0017BA20, 8 << 20, 4096, 108, 108, 216, 432, 0x00, 0x00, 0x1, 0x0000}, //N25Q064
  {0x0016BB20, 4 << 20, 4096, 108, 108, 216, 432, 0x00, 0x00, 0x1, 0x0000}, //N25Q032A11
  {0x0017BB20, 8 << 20, 4096, 108, 108, 216, 432, 0x00, 0x00, 0x1, 0x0000}, //N25Q064A11
  {0x0018BB20, 16 << 20, 4096, 108, 108, 216, 432, 0x00, 0x00, 0x1, 0x0000}, //N25Q064A11

  {0x0017381C, 8 << 20, 4096, 108, 108, 216, 432, 0x00, 0x00, 0x1, 0x0000}, //EN25S64A (2SC)
  {0x00173820, 8 << 20, 4096, 108, 108, 216, 432, 0x00, 0x00, 0x1, 0x0000}, //XM25QU64Aexit

  {0x00000000, 4 << 20, 4096,  33,  33,  33,  33, 0x05, 0x01, 0x1, 0x0040}
};


UINT8 RomSigBuffer[0x100] = {0};

/**
 * FchWriteSpiExtReg - Write SPI Extension Register
 *
 *
 *
 * @param[in] SpiExtRegIndex - Extension Register Index.
 * @param[in] SpiExtRegData - Extension Register Data.
 *
 */
VOID
FchWriteSpiExtReg (
  IN       UINT8      SpiExtRegIndex,
  IN       UINT8      SpiExtRegData
  )
{
  ACPIMMIO8 (SPI_BASE + FCH_SPI_MMIO_REG1E) = SpiExtRegIndex;
  ACPIMMIO8 (SPI_BASE + FCH_SPI_MMIO_REG1F) = SpiExtRegData;
}
/**
 * FchSetSpiCounter - Set SPI RX/TX Counters
 *
 *
 *
 * @param[in] TxCounter - Transfer Counter.
 * @param[in] RxCounter - Receive Counter.
 *
 */
VOID
FchSetSpiCounter (
  IN       UINT8      TxCounter,
  IN       UINT8      RxCounter
  )
{
  FchWriteSpiExtReg (FCH_SPI_MMIO_REG1F_X05_TX_BYTE_COUNT, TxCounter);
  FchWriteSpiExtReg (FCH_SPI_MMIO_REG1F_X06_RX_BYTE_COUNT, RxCounter);
}
/**
 * FchSpiControllerNotBusy - SPI Conroller Not Busy
 *
 *
 *
 *
 */
VOID
FchSpiControllerNotBusy (
  )
{
  UINT32 SpiReg00;
  SpiReg00 = FCH_SPI_BUSY + FCH_SPI_EXEC_OPCODE;
  do {
    SpiReg00 = ACPIMMIO32 (SPI_BASE + FCH_SPI_MMIO_REG00);
  } while ((SpiReg00 & (FCH_SPI_BUSY + FCH_SPI_EXEC_OPCODE)));
}
/**
 * FchSpiExecute - SPI Execute
 *
 *
 *
 *
 */
VOID
FchSpiExecute (
  )
{
  UINT32 SpiReg00;
  SpiReg00 = FCH_SPI_BUSY + FCH_SPI_EXEC_OPCODE;
  ACPIMMIO32 (SPI_BASE + FCH_SPI_MMIO_REG00) |= FCH_SPI_EXEC_OPCODE;
  do {
    SpiReg00 = ACPIMMIO32 (SPI_BASE + FCH_SPI_MMIO_REG00);
  } while ((SpiReg00 & (FCH_SPI_BUSY + FCH_SPI_EXEC_OPCODE)));
}
/**
 * FchResetFifo - Reset SPI FIFO
 *
 *
 *
 *
 */
VOID
FchResetFifo (
  )
{
  ACPIMMIO32 (SPI_BASE + FCH_SPI_MMIO_REG00) |= BIT20;
}
/**
 * WaitForSpiDeviceWriteEnabled -
 *
 *
 *
 *
 */
BOOLEAN
WaitForSpiDeviceWriteEnabled (
  )
{
  UINT8 bStatus;
  bStatus = 0;
  do
  {
    FchSpiTransfer (
      0, //IN       UINT8    PrefixCode,
      0x05,//IN       UINT8    Opcode,
      &bStatus,//IN       OUT UINT8    *DataPtr,
      NULL,//IN       UINT8    *AddressPtr,
      0,//IN       UINT8    Length,
      FALSE,//IN       BOOLEAN  WriteFlag,
      FALSE,//IN       BOOLEAN  AddressFlag,
      TRUE,//IN       BOOLEAN  DataFlag,
      FALSE //IN       BOOLEAN  FinishedFlag
    );
  } while ((bStatus & 2) == 0);
  return TRUE;
}
/**
 * WaitForSpiDeviceComplete -
 *
 *
 *
 *
 */
BOOLEAN
WaitForSpiDeviceComplete (
  )
{
  UINT8 bStatus;
  bStatus = 1;
  do
  {
    FchSpiTransfer (
      0, //IN       UINT8    PrefixCode,
      0x05,//IN       UINT8    Opcode,
      &bStatus,//IN       OUT UINT8    *DataPtr,
      NULL,//IN       UINT8    *AddressPtr,
      0,//IN       UINT8    Length,
      FALSE,//IN       BOOLEAN  WriteFlag,
      FALSE,//IN       BOOLEAN  AddressFlag,
      TRUE,//IN       BOOLEAN  DataFlag,
      FALSE //IN       BOOLEAN  FinishedFlag
    );
  } while (bStatus & 1);
  return TRUE;
}
/**
 * FchSpiTransfer - FCH Spi Transfer
 *
 *
 *
 * @param[in] PrefixCode   - Prefix code.
 * @param[in] Opcode       - Opcode.
 * @param[in] DataPtr      - Data Pointer.
 * @param[in] AddressPtr   - Address Pointer.
 * @param[in] Length       - Read/Write Length.
 * @param[in] WriteFlag    - Write Flag.
 * @param[in] AddressFlag  - Address Flag.
 * @param[in] DataFlag     - Data Flag.
 * @param[in] FinishedFlag - Finished Flag.
 *
 */
//static
AGESA_STATUS
FchSpiTransfer (
  IN       UINT8    PrefixCode,
  IN       UINT8    Opcode,
  IN OUT   UINT8    *DataPtr,
  IN       UINT8    *AddressPtr,
  IN       UINT8    Length,
  IN       BOOLEAN  WriteFlag,
  IN       BOOLEAN  AddressFlag,
  IN       BOOLEAN  DataFlag,
  IN       BOOLEAN  FinishedFlag
  )
{
  UINTN  Addr;
  UINTN  Retry;
  UINTN  i;
  UINTN  index;
  UINT8  WriteCount;
  UINT8  ReadCount;
  //UINT8  Dummy;
  //UINT8  CurrFifoIndex;

  if (!((Opcode == 0x9f) && (!DataFlag))) {
    if (PrefixCode) {
      Retry = 0;
      do {
        ACPIMMIO8 (SPI_BASE + FCH_SPI_MMIO_REG00 + 0) = PrefixCode;
        //ACPIMMIO8(SPI_BASE + FCH_SPI_MMIO_REG00 + 1) = 0;
        FchSetSpiCounter (0, 0);
        ACPIMMIO32 (SPI_BASE + FCH_SPI_MMIO_REG00) |= FCH_SPI_EXEC_OPCODE;
        FchSpiControllerNotBusy ();

        if (FinishedFlag) {
          if (WaitForSpiDeviceWriteEnabled ()) {
            Retry = 0;
          } else {
            Retry ++;
            if (Retry >= FCH_SPI_RETRY_TIMES) {
              return AGESA_ERROR;
            }
          }
        }
      } while (Retry);
    }
    Retry = 0;
    do {
      WriteCount = 0;
      ReadCount = 0;
      //
      // Reset Fifo Ptr
      //
      FchResetFifo ();
      //
      // Check Address Mode
      //
      index = 0;
      Addr = (UINTN) AddressPtr;
      if (AddressFlag) {
        //for (i = 16, Addr = (UINTN) AddressPtr; i >= 0; i -= 8) {
        for (i = 0; i < 3; i ++) {
          //ACPIMMIO8 (SPI_BASE + FCH_SPI_MMIO_REG0C + 0) = (UINT8) ((Addr >> i) & 0xff);
          ACPIMMIO8 (SPI_BASE + FCH_SPI_MMIO_REG80_FIFO + index) = (UINT8) ((Addr >> (16 - i * 8)) & 0xff);
          index ++;
        }
        WriteCount += 3;
      }
      if (DataFlag) {
        //
        // Check Read/Write Mode
        //
        if (WriteFlag) {
          WriteCount += Length + 1;
          for (i = 0; i < (UINTN) (Length + 1); i ++) {
            //ACPIMMIO8 (SPI_BASE + FCH_SPI_MMIO_REG0C + 0) = DataPtr[i];
            ACPIMMIO8 (SPI_BASE + FCH_SPI_MMIO_REG80_FIFO + index) = DataPtr[i];
            index ++;
          }
        } else {
          //
          // Read operation must plus extra 1 byte
          //
          ReadCount += Length + 2;
        }
      }
      ACPIMMIO8 (SPI_BASE + FCH_SPI_MMIO_REG00 + 0) = Opcode;
      //ACPIMMIO8 (SPI_BASE + FCH_SPI_MMIO_REG00 + 1) = (ReadCount << 4) + WriteCount;
      FchSetSpiCounter (WriteCount, ReadCount);
      ACPIMMIO32 (SPI_BASE + FCH_SPI_MMIO_REG00) |= FCH_SPI_EXEC_OPCODE;
      FchSpiControllerNotBusy ();

      if (FinishedFlag) {
        if (WaitForSpiDeviceComplete ()) {
          Retry = 0;
        } else {
          Retry ++;
          if (Retry >= FCH_SPI_RETRY_TIMES) {
            return AGESA_ERROR;
          }
        }
      }
    } while (Retry);
    if (DataFlag && ReadCount) {
      //
      // Reset Fifo Ptr
      //
      FchResetFifo ();
      //while (DataFlag && ReadCount) {
      //  CurrFifoIndex = ACPIMMIO8 (SPI_BASE + FCH_SPI_MMIO_REG4E + 1) & 0x07;
      //  if (CurrFifoIndex != WriteCount) {
      //    Dummy = ACPIMMIO8 (SPI_BASE + FCH_SPI_MMIO_REG0C + 0);
      //  } else break;
      //}
      for (i = 0; i < (UINTN) (Length + 1); i ++) {
        //DataPtr[i] = ACPIMMIO8 (SPI_BASE + FCH_SPI_MMIO_REG0C + 0);
        DataPtr[i] = ACPIMMIO8 (SPI_BASE + FCH_SPI_MMIO_REG80_FIFO + WriteCount + i);
      }
    }
  }
  return AGESA_SUCCESS;
}

/**
 * FchSetQualMode - Set SPI Qual Mode
 *
 *
 *
 * @param[in] SpiQualMode- Spi Qual Mode.
 * @param[in] StdHeader  - Standard Header.
 *
 */
VOID
FchSetQualMode (
  IN       UINT32      SpiQualMode,
  IN       AMD_CONFIG_PARAMS         *StdHeader
  )
{
  UINT32 SpiMode;
//  UINT8  Src;
//  UINT8  *SrcPoint;
//  UINTN  FlashWriteAddress;

//  SrcPoint = (UINT8*)(UINTN)0xff820040ul;
//  Src = *SrcPoint;
//  if ( Src != 0xAA ) {
//      Src = 0xAA;
//      FlashWriteAddress = 0x20040;
//      FchSpiTransfer (
//        0x06, //IN  UINT8    PrefixCode,
//        0x02,//IN  UINT8    Opcode,
//        &Src,//IN  OUT UINT8    *DataPtr,
//        (UINT8 *)FlashWriteAddress,//IN  UINT8    *AddressPtr,
//        0,//IN  UINT8    Length,
//        1,//IN  BOOLEAN  WriteFlag,
//        1,//IN  BOOLEAN  AddressFlag,
//        1,//IN  BOOLEAN  DataFlag,
//        1 //IN  BOOLEAN  FinishedFlag
//      );
//  }

  //<Embedded_Override_Start>
  RwMem (ACPI_MMIO_BASE + GPIO_BASE + FCH_GEVENT_REG09, AccessWidth8, ~(UINT32) BIT3, BIT3);
  //<Embedded_Override_End>
  SpiMode = ACPIMMIO32 (SPI_BASE + FCH_SPI_MMIO_REG00);
  if ((SpiMode & (BIT18 + BIT29 + BIT30)) != ((SpiQualMode & 1) << 18) + ((SpiQualMode & 6) << 28)) {
    RwMem (SPI_BASE + FCH_SPI_MMIO_REG00, AccessWidth32, ~(UINT32) ( BIT18 + BIT29 + BIT30), ((SpiQualMode & 1) << 18) + ((SpiQualMode & 6) << 28));
  }

}



UINT32
FchReadSpiId (
  IN       BOOLEAN    Flag
  )
{
  UINT32 DeviceID;
  UINT8 *DeviceIdPtr;
  DeviceID = 0;
  DeviceIdPtr = (UINT8 *) (((UINTN) (&DeviceID)));
  if (Flag) {
    FchSpiTransfer (
      0, //IN       UINT8    PrefixCode,
      0x9F,//IN       UINT8    Opcode,
      DeviceIdPtr,//IN  OUT   UINT8    *DataPtr,
      (UINT8 *) (NULL),//IN       UINT8    *AddressPtr,
      2,//IN       UINT8    Length,
      FALSE,//IN       BOOLEAN  WriteFlag,
      FALSE,//IN       BOOLEAN  AddressFlag,
      TRUE,//IN       BOOLEAN  DataFlag,
      FALSE //IN       BOOLEAN  FinishedFlag
    );
  } else {
    FchSpiTransfer (
      0, //IN       UINT8    PrefixCode,
      0x9F,//IN       UINT8    Opcode,
      DeviceIdPtr,//IN  OUT   UINT8    *DataPtr,
      (UINT8 *) (NULL),//IN       UINT8    *AddressPtr,
      2,//IN       UINT8    Length,
      FALSE,//IN       BOOLEAN  WriteFlag,
      FALSE,//IN       BOOLEAN  AddressFlag,
      FALSE,//IN       BOOLEAN  DataFlag,
      FALSE //IN       BOOLEAN  FinishedFlag
    );
  }
  return DeviceID;
}

VOID
FchConfigureSpiControllerDummyCycle (
  )
{
  if (FchReadSpiId(TRUE) == 0x00182001) {
    RwMem (SPI_BASE + FCH_SPI_MMIO_REG32, AccessWidth16, ~((UINT32) (0xFF << 8)), ((0xCA) << 8));
  }else if (FchReadSpiId(TRUE) == 0x00185020) {
    // Keep HW default
  }else if (((FchReadSpiId(TRUE) & 0xff)) == 0x20) {
    RwMem (SPI_BASE + FCH_SPI_MMIO_REG32, AccessWidth16, ~((UINT32) (0xFF << 8)), ((0x8A) << 8));
    //RwMem (SPI_BASE + FCH_SPI_MMIO_REG58_Addr32_Ctrl2, AccessWidth16, ~((UINT32) (0xFF << 8)), ((0x8A) << 8));
  }
}

/**
 * FchReadSpiQe - Read SPI Qual Enable
 *
 *
 *
 * @param[in] SpiDeviceProfilePtr - Spi Device Profile Pointer
 * @param[in] SpiQeRegValue   - Spi QuadEnable Register Value
 *
 */
BOOLEAN
FchReadSpiQe (
  IN OUT   SPI_DEVICE_PROFILE    *SpiDeviceProfilePtr,
  IN       UINT32     SpiQeRegValue
  )
{
  UINT32     Value32;
  SpiQeRegValue = 0;
  Value32 = 0;

  FchSpiTransfer (
    0, //IN       UINT8    PrefixCode,
    0x05,//IN       UINT8    Opcode,
    (UINT8 *)(&SpiQeRegValue),//IN  OUT   UINT8    *DataPtr,
    NULL,//IN       UINT8    *AddressPtr,
    0,//IN       UINT8    Length,
    FALSE,//IN       BOOLEAN  WriteFlag,
    FALSE,//IN       BOOLEAN  AddressFlag,
    TRUE,//IN       BOOLEAN  DataFlag,
    FALSE //IN       BOOLEAN  FinishedFlag
  );

  if (SpiDeviceProfilePtr->QeOperateSize > 1) {
    FchSpiTransfer (
      0, //IN       UINT8    PrefixCode,
      0x35,//IN       UINT8    Opcode,
      (UINT8 *)(&Value32),//IN  OUT   UINT8    *DataPtr,
      NULL,//IN       UINT8    *AddressPtr,
      0,//IN       UINT8    Length,
      FALSE,//IN       BOOLEAN  WriteFlag,
      FALSE,//IN       BOOLEAN  AddressFlag,
      TRUE,//IN       BOOLEAN  DataFlag,
      FALSE //IN       BOOLEAN  FinishedFlag
    );
    SpiQeRegValue |= (Value32 << 8);
  }

  if (SpiDeviceProfilePtr->QeOperateSize > 2) {
    FchSpiTransfer (
      0, //IN       UINT8    PrefixCode,
      0x33,//IN       UINT8    Opcode,
      (UINT8 *)(&Value32),//IN  OUT   UINT8    *DataPtr,
      NULL,//IN       UINT8    *AddressPtr,
      0,//IN       UINT8    Length,
      FALSE,//IN       BOOLEAN  WriteFlag,
      FALSE,//IN       BOOLEAN  AddressFlag,
      TRUE,//IN       BOOLEAN  DataFlag,
      FALSE //IN       BOOLEAN  FinishedFlag
    );
    SpiQeRegValue |= (Value32 << 16);
  }

  if (SpiDeviceProfilePtr->QeLocation & SpiQeRegValue) {
    return TRUE;
  }
  SpiQeRegValue |= (UINT32) (SpiDeviceProfilePtr->QeLocation);
  return FALSE;
}
/**
 * FchWriteSpiQe - Write SPI Qual Enable
 *
 *
 *
 * @param[in] SpiDeviceProfilePtr - Spi Device Profile Pointer
 * @param[in] SpiQeRegValue   - Spi QuadEnable Register Value
 *
 */
VOID
FchWriteSpiQe (
  IN OUT   SPI_DEVICE_PROFILE    *SpiDeviceProfilePtr,
  IN       UINT32     SpiQeRegValue
  )
{

  SpiQeRegValue |= SpiDeviceProfilePtr->QeLocation;
  FchSpiTransfer (
    0x06, //IN       UINT8    PrefixCode,
    SpiDeviceProfilePtr->QeWriteRegister,//IN       UINT8    Opcode,
    (UINT8 *)(&SpiQeRegValue),//IN  OUT   UINT8    *DataPtr,
    NULL,//IN       UINT8    *AddressPtr,
    SpiDeviceProfilePtr->QeOperateSize - 1,//IN       UINT8    Length,
    TRUE,//IN       BOOLEAN  WriteFlag,
    FALSE,//IN       BOOLEAN  AddressFlag,
    TRUE,//IN       BOOLEAN  DataFlag,
    TRUE //IN       BOOLEAN  FinishedFlag
  );
}

/**
 * FchFindSpiDeviceProfile - Find SPI Device Profile
 *
 *
 *
 * @param[in] DeviceID   - Device ID
 * @param[in] SpiDeviceProfilePtr - Spi Device Profile Pointer
 *
 */
BOOLEAN
FchFindSpiDeviceProfile (
  IN       UINT32     DeviceID,
  IN OUT   SPI_DEVICE_PROFILE    *SpiDeviceProfilePtr
  )
{
  SPI_DEVICE_PROFILE   *CurrentSpiDeviceProfilePtr;
  UINT32     SpiQeRegValue;
  SpiQeRegValue = 0;
  CurrentSpiDeviceProfilePtr = SpiDeviceProfilePtr;
  do {
    if (CurrentSpiDeviceProfilePtr->JEDEC_ID == DeviceID) {
      SpiDeviceProfilePtr = CurrentSpiDeviceProfilePtr;
      if (SpiDeviceProfilePtr->QeWriteRegister) {
        if (!(FchReadSpiQe (SpiDeviceProfilePtr, SpiQeRegValue))) {
          FchWriteSpiQe (SpiDeviceProfilePtr, SpiQeRegValue);
          if (!(FchReadSpiQe (SpiDeviceProfilePtr, SpiQeRegValue))) {
            return FALSE;
          }
        }
      }
      return TRUE;
    }
    CurrentSpiDeviceProfilePtr++;
  } while (CurrentSpiDeviceProfilePtr->JEDEC_ID != NULL);
  return FALSE;
}

/**
 * FchConfigureSpiDeviceDummyCycle - Configure Spi Device Dummy
 * Cycle
 *
 *
 *
 * @param[in] DeviceID   - Device ID
 * @param[in] SpiMode  - Spi Mode.
 *
 */
BOOLEAN
FchConfigureSpiDeviceDummyCycle (
  IN       UINT32     DeviceID,
  IN       UINT8      SpiMode
  )
{
  UINT16     Mode16;
  UINT16     Value16;
  UINT8      Value8;
  UINT16     DummyValue16;
  UINT16     CurrentDummyValue16;
  UINT16     CurrentMode16;

  Value16 = 0;
  DummyValue16 = 8;
  DeviceID  &= 0xff;

  if ( DeviceID == 0x20 ) {
    FchSpiTransfer (
      0, //IN       UINT8    PrefixCode,
      0xB5,//IN       UINT8    Opcode,
      (UINT8 *)(&Value16),//IN  OUT   UINT8    *DataPtr,
      NULL,//IN       UINT8    *AddressPtr,
      1,//IN       UINT8    Length,
      FALSE,//IN       BOOLEAN  WriteFlag,
      FALSE,//IN       BOOLEAN  AddressFlag,
      TRUE,//IN       BOOLEAN  DataFlag,
      FALSE //IN       BOOLEAN  FinishedFlag
    );
    CurrentDummyValue16 = Value16 >> 12;
    CurrentMode16 = (Value16 >> 9) & 7;

    FchSpiTransfer (
      0, //IN       UINT8    PrefixCode,
      0x85,//IN       UINT8    Opcode,
      (UINT8 *)(&Value8),//IN  OUT   UINT8    *DataPtr,
      NULL,//IN       UINT8    *AddressPtr,
      0,//IN       UINT8    Length,
      FALSE,//IN       BOOLEAN  WriteFlag,
      FALSE,//IN       BOOLEAN  AddressFlag,
      TRUE,//IN       BOOLEAN  DataFlag,
      FALSE //IN       BOOLEAN  FinishedFlag
    );
    CurrentDummyValue16 = Value8 >> 4;

    switch (SpiMode) {
    case FCH_SPI_MODE_QUAL_144:
      DummyValue16 = 10;
      Mode16 = FCH_SPI_DEVICE_MODE_144;
      break;
    case FCH_SPI_MODE_QUAL_114:
      DummyValue16 = 8;
      Mode16 = FCH_SPI_DEVICE_MODE_114;
      Mode16 = 7;
      break;
    case FCH_SPI_MODE_QUAL_122:
      DummyValue16 = 4;
      Mode16 = FCH_SPI_DEVICE_MODE_122;
      break;
    case FCH_SPI_MODE_QUAL_112:
      DummyValue16 = 8;
      Mode16 = FCH_SPI_DEVICE_MODE_112;
      break;
    case FCH_SPI_MODE_FAST:
      DummyValue16 = 8;
      Mode16 = FCH_SPI_DEVICE_MODE_FAST;
      break;
    default:
      DummyValue16 = 15;
      Mode16 = 7;
      break;
    }
    if ((CurrentDummyValue16 != DummyValue16) || (CurrentMode16 != Mode16)) {
      //FCH_DEADLOOP();
      Value16 &= ~ (0x7f << 9);
      Value16 |= (DummyValue16 << 12);
      Value16 |= (Mode16 << 9);
      //FchSpiTransfer (
      //  0x06, //IN       UINT8    PrefixCode,
      //  0xB1,//IN       UINT8    Opcode,
      //  (UINT8 *)(&Value16),//IN  OUT   UINT8    *DataPtr,
      //  NULL,//IN       UINT8    *AddressPtr,
      //  1,//IN       UINT8    Length,
      //  TRUE,//IN       BOOLEAN  WriteFlag,
      //  FALSE,//IN       BOOLEAN  AddressFlag,
      //  TRUE,//IN       BOOLEAN  DataFlag,
      //  TRUE //IN       BOOLEAN  FinishedFlag
      //);

      FchSpiTransfer (
        0, //IN       UINT8    PrefixCode,
        0x85,//IN       UINT8    Opcode,
        (UINT8 *)(&Value8),//IN  OUT   UINT8    *DataPtr,
        NULL,//IN       UINT8    *AddressPtr,
        0,//IN       UINT8    Length,
        FALSE,//IN       BOOLEAN  WriteFlag,
        FALSE,//IN       BOOLEAN  AddressFlag,
        TRUE,//IN       BOOLEAN  DataFlag,
        FALSE //IN       BOOLEAN  FinishedFlag
      );

      Value8 &= ~ (0xf << 4);
      Value8 |= (UINT8) (DummyValue16 << 4);
      FchSpiTransfer (
        0x06, //IN       UINT8    PrefixCode,
        0x81,//IN       UINT8    Opcode,
        (UINT8 *)(&Value8),//IN  OUT   UINT8    *DataPtr,
        NULL,//IN       UINT8    *AddressPtr,
        0,//IN       UINT8    Length,
        TRUE,//IN       BOOLEAN  WriteFlag,
        FALSE,//IN       BOOLEAN  AddressFlag,
        TRUE,//IN       BOOLEAN  DataFlag,
        TRUE //IN       BOOLEAN  FinishedFlag
      );
    }
    return TRUE;
  }
  return FALSE;
}
/**
 * FchPlatformSpiQe - Platform SPI Qual Enable
 *
 *
 *
 * @param[in] FchDataPtr  - FchData Pointer.
 *
 */
BOOLEAN
FchPlatformSpiQe (
  IN       VOID     *FchDataPtr
  )
{
  UINT32 DeviceID;
  SPI_DEVICE_PROFILE        *LocalSpiDeviceProfilePtr;
  FCH_DATA_BLOCK            *LocalCfgPtr;
  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
//  if (LocalCfgPtr->QeEnabled) {
//    return TRUE;
//  }
//  FchReadSpiId (FALSE);
  DeviceID = FchReadSpiId (TRUE);
//  if (LocalCfgPtr->OemSpiDeviceTable != NULL) {
//    LocalSpiDeviceProfilePtr = LocalCfgPtr->OemSpiDeviceTable;
//    if (FchFindSpiDeviceProfile (DeviceID, LocalSpiDeviceProfilePtr)) {
//      return TRUE;
//    }
//  }
  
  LocalSpiDeviceProfilePtr = (SPI_DEVICE_PROFILE *) (&DefaultSpiDeviceTable);
//  FchConfigureSpiDeviceDummyCycle (0, LocalCfgPtr); //dummy once
//  if (FchConfigureSpiDeviceDummyCycle (DeviceID, LocalCfgPtr->Spi.SpiMode)) {
//    return TRUE;
//  }
  if (FchFindSpiDeviceProfile (DeviceID, LocalSpiDeviceProfilePtr)) {
    return TRUE;
  }
  return FALSE;
}

/**
 * AutoSpiModeSpeed - Auto SPI Mode Speed
 *
 *
 *
 * @param[in] FchDataPtr  - FchData Pointer.
 *
 */
BOOLEAN
AutoSpiModeSpeed (
  IN       VOID     *FchDataPtr
  )
{
  UINT32 DeviceID;
  FCH_DATA_BLOCK      *LocalCfgPtr;
  SPI_DEVICE_PROFILE   *CurrentSpiDeviceProfilePtr;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  DeviceID = FchReadSpiId (TRUE);
  CurrentSpiDeviceProfilePtr = (SPI_DEVICE_PROFILE *) (&DefaultSpiDeviceTable);

  do {
    if (CurrentSpiDeviceProfilePtr->JEDEC_ID == DeviceID) {
      LocalCfgPtr->Spi.SpiMode = FCH_SPI_MODE_QUAL_144;
      if (CurrentSpiDeviceProfilePtr->MaxQuadSpeed >= 100 * 4) {
//        LocalCfgPtr->Spi.SpiFastSpeed = FCH_SPI_SPEED_100M;
        LocalCfgPtr->Spi.SpiFastSpeed = FCH_SPI_SPEED_66M;
      } else if (CurrentSpiDeviceProfilePtr->MaxQuadSpeed >= 66 * 4) {
        LocalCfgPtr->Spi.SpiFastSpeed = FCH_SPI_SPEED_66M;
      } else if (CurrentSpiDeviceProfilePtr->MaxQuadSpeed >= 33 * 4) {
        LocalCfgPtr->Spi.SpiFastSpeed = FCH_SPI_SPEED_33M;
      }
//      *(&LocalCfgPtr->Spi.SpiDeviceProfile) = *CurrentSpiDeviceProfilePtr;
      LocalCfgPtr->Spi.SpiDeviceProfile = *CurrentSpiDeviceProfilePtr;
      return TRUE;
    }
    CurrentSpiDeviceProfilePtr++;
  } while (CurrentSpiDeviceProfilePtr->JEDEC_ID != NULL);
  return FALSE;
}


/**
 * FchSetSpi - Config Spi controller before PCI emulation
 *
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchSetSpi (
  IN  VOID     *FchDataPtr
  )
{
  UINT8  SpiMode;
  UINT8  SpiFastSpeed;
  UINT8  QuadDummyCycle;
  UINT8  *SrcPoint;
  UINTN  FlashWriteAddress;
  UINTN  RomBase;
  UINTN  CopyLength;
  UINTN  RomSigStartingAddr;
  UINT16  Value16;
  UINT32 DeviceID;

  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;
  RomBase = 0x100000000 - 0x1000000;
  GetRomSigPtr (&RomSigStartingAddr, StdHeader);
  Value16 = *((UINT16*) (UINTN) (RomSigStartingAddr + 0x43));
  SrcPoint = (UINT8*) (UINTN) (RomSigStartingAddr + 0x43);
  SpiMode = *SrcPoint;
  SrcPoint ++;
  SpiFastSpeed = *SrcPoint;
  SrcPoint ++;
  QuadDummyCycle = *SrcPoint;

  DeviceID = FchReadSpiId (TRUE);
  if ( (DeviceID & 0xff) == 0x20 ) { //Micron, need adjust timing
    QuadDummyCycle = 0x0A; //PLAT-30454 change dummy cycle back to 0x0A from 0x8A to avoid chip changing hang.
  } else if (DeviceID == 0x00182001) { //S25FS128S
    QuadDummyCycle = 0xCA;
  }
  if (*(UINT8*) (UINTN) (&DeviceID) != ACPIMMIO8 (0xFED8060C)) {
    ACPIMMIO8 (0xFED8060C) = *(UINT8*) (UINTN) (&DeviceID);
  }

  if (( 0 ==  LocalCfgPtr->Spi.SpiMode) && ( 0 ==  (LocalCfgPtr->Spi.SpiFastSpeed))) {
    if (AutoSpiModeSpeed (FchDataPtr)) {
      RomBase = (UINTN) ((~ LocalCfgPtr->Spi.SpiDeviceProfile.RomSize) + 1);
    }
  }

  if (( SpiMode !=  LocalCfgPtr->Spi.SpiMode) || ( SpiFastSpeed !=  (LocalCfgPtr->Spi.SpiFastSpeed -1))) {
    if (FchPlatformSpiQe (FchDataPtr)) {
      if ((LocalCfgPtr->Spi.SpiMode == FCH_SPI_MODE_QUAL_144) || (ACPIMMIO8 (0xFED8060C) != 0x20) || (DeviceID == 0x00185020))  {
        SpiMode =  LocalCfgPtr->Spi.SpiMode;
        if (0 !=  (LocalCfgPtr->Spi.SpiFastSpeed)) {
          SpiFastSpeed =  LocalCfgPtr->Spi.SpiFastSpeed -1;
        } else {
          SpiFastSpeed =  0;
        }

        SrcPoint = (UINT8*) (UINTN) RomSigStartingAddr;
        CopyLength = 0x100;
        if (*(SrcPoint) != RomSigBuffer[0]) {
          LibAmdMemCopy (RomSigBuffer,
                    SrcPoint,
                    CopyLength,
                    StdHeader);
        }

        RomSigBuffer [0x43] = SpiMode;
        RomSigBuffer [0x44] = SpiFastSpeed;

        if (Value16 == 0xffff) {
          FlashWriteAddress = RomSigStartingAddr - RomBase + 0x43;
          FchSpiTransfer (
            0x06, //IN  UINT8    PrefixCode,
            0x02,//IN  UINT8    Opcode,
            &SpiMode,//IN  OUT UINT8    *DataPtr,
            (UINT8 *)FlashWriteAddress,//IN  UINT8    *AddressPtr,
            0,//IN  UINT8    Length,
            1,//IN  BOOLEAN  WriteFlag,
            1,//IN  BOOLEAN  AddressFlag,
            1,//IN  BOOLEAN  DataFlag,
            1 //IN  BOOLEAN  FinishedFlag
          );

          FlashWriteAddress ++;
          //SpiFastSpeed = LocalCfgPtr->Spi.SpiFastSpeed -1;
          FchSpiTransfer (
            0x06, //IN  UINT8    PrefixCode,
            0x02,//IN  UINT8    Opcode,
            &SpiFastSpeed,//IN  OUT UINT8    *DataPtr,
            (UINT8 *)FlashWriteAddress,//IN  UINT8    *AddressPtr,
            0,//IN  UINT8    Length,
            1,//IN  BOOLEAN  WriteFlag,
            1,//IN  BOOLEAN  AddressFlag,
            1,//IN  BOOLEAN  DataFlag,
            1 //IN  BOOLEAN  FinishedFlag
          );

          if (((ACPIMMIO8 (0xFED8060C) == 0x20) && (DeviceID != 0x00185020))\
             ||(DeviceID == 0x00182001)) {
            FlashWriteAddress ++;
            FchSpiTransfer (
              0x06, //IN  UINT8    PrefixCode,
              0x02,//IN  UINT8    Opcode,
              &QuadDummyCycle,//IN  OUT UINT8    *DataPtr,
              (UINT8 *)FlashWriteAddress,//IN  UINT8    *AddressPtr,
              0,//IN  UINT8    Length,
              1,//IN  BOOLEAN  WriteFlag,
              1,//IN  BOOLEAN  AddressFlag,
              1,//IN  BOOLEAN  DataFlag,
              1 //IN  BOOLEAN  FinishedFlag
            );
            RwMem (SPI_BASE + FCH_SPI_MMIO_REG32, AccessWidth16, ~((UINT32) (0xFF << 8)), ((QuadDummyCycle) << 8));
          }
          FchSetQualMode (LocalCfgPtr->Spi.SpiMode, StdHeader);
          RwMem (SPI_BASE + FCH_SPI_MMIO_REG22, AccessWidth16, ~((UINT32) (0xF << 8)), ((SpiFastSpeed) << 8));
        }
      }
    }
  }
}

/**
 * FchInitEnvSpi - Config Spi controller before PCI emulation
 *
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchInitEnvSpi (
  IN  VOID     *FchDataPtr
  )
{
  AGESA_TESTPOINT (TpFchInitEnvSpi, NULL);
  FchInitEnvLpc (FchDataPtr);
  FchSetSpi (FchDataPtr);
}

