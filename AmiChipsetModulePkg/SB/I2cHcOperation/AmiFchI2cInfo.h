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

/** @file AmiFchI2cInfo.h
    This file contains Ami I2C data structures definitions.
**/

#ifndef _AMIFCHI2CINFO_H_
#define _AMIFCHI2CINFO_H_

#define BIT(offset)                         1 << (offset)
#define MicroSecondDelay(cnt)               gBS->Stall(cnt);

//
// MMI/O Register Definitions
//
#define I2C2_MMIO_BASE                      0xFEDC4000
#define I2C3_MMIO_BASE                      0xFEDC5000
#define I2C4_MMIO_BASE                      0xFEDC6000   //slave for usb power delivery

//
// FIFO write workaround value.
//
#define FIFO_WRITE_DELAY                    2

#define  R_IC_CON                           0x00        // I2C Control
#define    B_IC_SLAVE_DISABLE               BIT(6)
#define    B_IC_RESTART_EN                  BIT(5)
#define    B_IC_10BITADDR_MASTER            BIT(4)
#define    B_IC_10BITADDR_SLAVE             BIT(3)
#define    V_IC_SPEED_STANDARD              0x02
#define    V_IC_SPEED_FAST                  0x04
#define    V_IC_SPEED_HIGH                  0x06
#define    B_IC_MASTER_MODE                 BIT(0)
// #define   IC_TAR_10BITADDR_MASTER  BIT12

#define  R_IC_TAR                           0x04        // I2C Target Address
#define  R_IC_SAR                           0x08        // I2C Slave Address
#define  R_IC_HS_MADDR                      0x0C        // I2C HS MasterMode Code Address
#define  R_IC_DATA_CMD                      0x10        // I2C Rx/Tx Data Buffer and Command
#define  B_READ_CMD                         BIT8        // 1 = read, 0 = write
#define  B_CMD_STOP                         BIT9        // 1 = STOP
#define  B_CMD_RESTART                      BIT10       // 1 = IC_RESTART_EN

#define  V_WRITE_CMD_MASK                   0xFF

#define  R_IC_SS_SCL_HCNT                   0x14        // Standard Speed I2C Clock SCL High Count
#define  R_IC_SS_SCL_LCNT                   0x18        // Standard Speed I2C Clock SCL Low Count
#define  R_IC_FS_SCL_HCNT                   0x1C        // Full Speed I2C Clock SCL High Count
#define  R_IC_FS_SCL_LCNT                   0x20        // Full Speed I2C Clock SCL Low Count
#define  R_IC_HS_SCL_HCNT                   0x24        // High Speed I2C Clock SCL High Count
#define  R_IC_HS_SCL_LCNT                   0x28        // High Speed I2C Clock SCL Low Count
#define  R_IC_INTR_STAT                     0x2C        // I2C Inetrrupt Status
#define  R_IC_INTR_MASK                     0x30        // I2C Interrupt Mask
#define    I2C_INTR_GEN_CALL                BIT11       // General call received
#define    I2C_INTR_START_DET               BIT10
#define    I2C_INTR_STOP_DET                BIT9
#define    I2C_INTR_ACTIVITY                BIT8
#define    I2C_INTR_TX_ABRT                 BIT6        // Set on NACK
#define    I2C_INTR_TX_EMPTY                BIT4
#define    I2C_INTR_TX_OVER                 BIT3
#define    I2C_INTR_RX_FULL                 BIT2        // Data bytes in RX FIFO over threshold
#define    I2C_INTR_RX_OVER                 BIT1
#define    I2C_INTR_RX_UNDER                BIT0

#define  R_IC_RAW_INTR_STAT                 0x34        // I2C Raw Interrupt Status
#define  R_IC_RX_TL                         0x38        // I2C Receive FIFO Threshold
#define  R_IC_TX_TL                         0x3C        // I2C Transmit FIFO Threshold
#define  R_IC_CLR_INTR                      0x40        // Clear Combined and Individual Interrupts
#define  R_IC_CLR_RX_UNDER                  0x44        // Clear RX_UNDER Interrupt
#define  R_IC_CLR_RX_OVER                   0x48        // Clear RX_OVERinterrupt
#define  R_IC_CLR_TX_OVER                   0x4C        // Clear TX_OVER interrupt
#define  R_IC_CLR_RD_REQ                    0x50        // Clear RD_REQ interrupt
#define  R_IC_CLR_TX_ABRT                   0x54        // Clear TX_ABRT interrupt
#define  R_IC_CLR_RX_DONE                   0x58        // Clear RX_DONE interrupt
#define  R_IC_CLR_ACTIVITY                  0x5C        // Clear ACTIVITY interrupt
#define  R_IC_CLR_STOP_DET                  0x60        // Clear STOP_DET interrupt
#define  R_IC_CLR_START_DET                 0x64        // Clear START_DET interrupt
#define  R_IC_CLR_GEN_CALL                  0x68        // Clear GEN_CALL interrupt
#define  R_IC_ENABLE                        0x6C        // I2C Enable
#define  R_IC_STATUS                        0x70        // I2C Status
#define    STAT_SLV_ACTIVITY                BIT6
#define    STAT_MST_ACTIVITY                BIT5        // Master FSM Activity Status
#define    STAT_RFF                         BIT(4)      // RX FIFO is completely full
#define    STAT_RFNE                        BIT(3)      // RX FIFO is not empty
#define    STAT_TFE                         BIT(2)      // TX FIFO is completely empty
#define    STAT_TFNF                        BIT(1)      // TX FIFO is not full

#define  R_IC_TXFLR                         0x74        // Transmit FIFO Level Register
#define  R_IC_RXFLR                         0x78        // Receive FIFO Level Register
#define  R_IC_SDA_HOLD                      0x7C        // SDA Hold Time Length
#define  R_IC_TX_ABRT_SOURCE                0x80        // I2C Transmit Abort Status Register
#define  R_IC_SLV_DATA_NACK_ONLY            0x84        // Generate SLV_DATA_NACK Register
#define  R_IC_DMA_CR                        0x88        // DMA Control Register
#define  R_IC_DMA_TDLR                      0x8C        // DMA Transmit Data Level
#define  R_IC_DMA_RDLR                      0x90        // DMA Receive Data Level
#define  R_IC_SDA_SETUP                     0x94        // I2C SDA Setup Register
#define  R_IC_ACK_GENERAL_CALL              0x98        // I2C ACK General Call Register
#define  R_IC_ENABLE_STATUS                 0x9C        // I2C Enable Status Register
#define  R_IC_COMP_PARAM                    0xF4        // Component Parameter Register
#define  R_IC_COMP_VERSION                  0xF8        // Component Version ID
#define  R_IC_COMP_TYPE                     0xFC        // Component Type

#define  R_IC_CLK_GATE                      0xC0        // Clock Gate
#define  R_IC_CLK_PARAMS                    0x800       // Clock Parameters
#define  R_IC_RESETS                        0x804       // Reset Register


EFI_STATUS
EFIAPI
I2cBusFrequencySet(
    IN  UINTN MmioBase,
    IN  UINTN BusClockHertz,
    IN OUT UINT16 *IcMode
    );


EFI_STATUS
EFIAPI
I2CInit(
    IN UINTN  MmioBase,
    IN UINT16 SlaveAddress
    );


EFI_STATUS
EFIAPI
I2cWriteRead(
    UINTN  MmioBase,
    UINT8  SlaveAddress,
    UINTN  WLength,
    UINT8  *Write_Buffer,
    UINTN  RLength,
    UINT8  *Read_Buffer
    );


#endif  //_AMIFCHI2CINFO_H_

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
