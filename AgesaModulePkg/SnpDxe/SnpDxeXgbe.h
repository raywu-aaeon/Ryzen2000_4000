/* $NoKeywords:$ */
/**
 * @file
 *
 * SnpDxeXgbe.h
 *
 * Ethernet Phy Driver DXE-Phase header file.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: FDK
 * @e sub-project: UEFI
 * @e version: $Revision: 298339 $ @e date: $Date: 2014-07-14 16:27:48 -0700 (Mon, 14 Jul 2014) $
 *
 */
/*
 ****************************************************************************
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
#ifndef __SNP_DXE_XGBE_H__
#define __SNP_DXE_XGBE_H__

  #include <Library/IoLib.h>
  #include <AMD.h>

  typedef struct _ENET_DXE_PRIVATE_DATA_ ENET_DXE_PRIVATE_DATA;


#define SERDES_RXTX_CH0_REG3 0x406 << 1
#define SECURITY_4_REG 0x18
#define XPCS_DEV_SEL 0xFF << 2
#define VR_AN_MMD_Interrupt_Mask_Register 0x8001 << 2
#define VR_AN_MMD_Interrupt_Register 0x8002 << 2
#define XGMAC_DMA_CH0_INT_EN 0x3138
#define XGBE_TC_CNT 2
#define AN_MAX_RETR 100

#define MTL_DEBUG_CONTROL   0x1008
#define MTL_DEBUG_STATUS    0x100C
#define MTL_FIFO_DEBUG_DATA 0x1010

#define XGMAC_TX_DMA_MAX_WAIT_MCS 5000
#define TX_DESC_CNT 8
#define XGBE_MAX_QUEUES		16
#define XGMAC_FIFO_UNIT		256

  /* Advertisement control register. */
#define ADVERTISE_SLCT		0x001f	/* Selector bits               */
#define ADVERTISE_CSMA		0x0001	/* Only selector supported     */
#define ADVERTISE_10HALF	0x0020	/* Try for 10mbps half-duplex  */
#define ADVERTISE_1000XFULL	0x0020	/* Try for 1000BASE-X full-duplex */
#define ADVERTISE_10FULL	0x0040	/* Try for 10mbps full-duplex  */
#define ADVERTISE_1000XHALF	0x0040	/* Try for 1000BASE-X half-duplex */
#define ADVERTISE_100HALF	0x0080	/* Try for 100mbps half-duplex */
#define ADVERTISE_1000XPAUSE	0x0080	/* Try for 1000BASE-X pause    */
#define ADVERTISE_100FULL	0x0100	/* Try for 100mbps full-duplex */
#define ADVERTISE_1000XPSE_ASYM	0x0100	/* Try for 1000BASE-X asym pause */
#define ADVERTISE_100BASE4	0x0200	/* Try for 100mbps 4k packets  */
#define ADVERTISE_PAUSE_CAP	0x0400	/* Try for pause               */
#define ADVERTISE_PAUSE_ASYM	0x0800	/* Try for asymetric pause     */
#define ADVERTISE_RESV		0x1000	/* Unused...                   */
#define ADVERTISE_RFAULT	0x2000	/* Say we can detect faults    */
#define ADVERTISE_LPACK		0x4000	/* Ack link partners response  */
#define ADVERTISE_NPAGE		0x8000	/* Next page bit               */
  
#define ADVERTISE_FULL		(ADVERTISE_100FULL | ADVERTISE_10FULL | \
					ADVERTISE_CSMA)
#define ADVERTISE_ALL		(ADVERTISE_10HALF | ADVERTISE_10FULL | \
					ADVERTISE_100HALF | ADVERTISE_100FULL)


/* Media-dependent registers. */
#define MDIO_PMA_10GBT_SWAPPOL	130	/* 10GBASE-T pair swap & polarity */
#define MDIO_PMA_10GBT_TXPWR	131	/* 10GBASE-T TX power control */
#define MDIO_PMA_10GBT_SNR		133	/* 10GBASE-T SNR margin, lane A.
					 				  * Lanes B-D are numbered 134-136. */
#define MDIO_PMA_10GBR_FECABLE	170	/* 10GBASE-R FEC ability */
#define MDIO_PCS_10GBX_STAT1	24	/* 10GBASE-X PCS status 1 */
#define MDIO_PCS_10GBRT_STAT1	32	/* 10GBASE-R/-T PCS status 1 */
#define MDIO_PCS_10GBRT_STAT2	33	/* 10GBASE-R/-T PCS status 2 */
#define MDIO_AN_10GBT_CTRL		32	/* 10GBASE-T auto-negotiation control */
#define MDIO_AN_10GBT_STAT		33	/* 10GBASE-T auto-negotiation status */

#define MDIO_AN_10GBT_CTRL_ADV_NBT_MASK	0x01e0
#define XP_INT_REISSUE_EN		0x0074

#define XGBE_SFP_BASE_VENDOR_NAME		20
#define XGBE_SFP_BASE_VENDOR_NAME_LEN	16
#define XGBE_SFP_BASE_VENDOR_PN			40
#define XGBE_SFP_BASE_VENDOR_PN_LEN		16
#define XGBE_SFP_BASE_VENDOR_REV		56
#define XGBE_SFP_BASE_VENDOR_REV_LEN	4

#define XGBE_BEL_FUSE_VENDOR	"BEL-FUSE        "
#define XGBE_BEL_FUSE_PARTNO	"1GBT-SFP06      "


enum phy_10g_an_mode{
    MV_PCS_BASE_T           = 0x0000,
    MV_PCS_BASE_R           = 0x1000,
    MV_PCS_1000BASEX        = 0x2000,

    MV_PCS_PAIRSWAP         = 0x8182,
    MV_PCS_PAIRSWAP_MASK    = 0x0003,
    MV_PCS_PAIRSWAP_AB      = 0x0002,
    MV_PCS_PAIRSWAP_NONE    = 0x0003,

    /* These registers appear at 0x800X and 0xa00X - the 0xa00X control
    * registers appear to set themselves to the 0x800X when AN is
    * restarted, but status registers appear readable from either.
    */
    MV_AN_CTRL1000          = 0x8000, /* 1000base-T control register */
    MV_AN_STAT1000          = 0x8001, /* 1000base-T status register */

    /* Vendor2 MMD registers */
    MV_V2_TEMP_CTRL         = 0xf08a,
    MV_V2_TEMP_CTRL_MASK    = 0xc000,
    MV_V2_TEMP_CTRL_SAMPLE  = 0x0000,
    MV_V2_TEMP_CTRL_DISABLE = 0xc000,
    MV_V2_MODE_CFG          = 0xf000,
    MV_V2_PORT_CTRL         = 0xf001,
    MV_V2_LED0_CTRL         = 0xf020,
    MV_V2_HOST_KR_TUNE      = 0xf07c,
    MV_V2_HOST_KR_ENABLE    = 0xf084,
    MV_V2_TEMP	            = 0xf08c,
    MV_V2_TEMP_UNKNOWN      = 0x9600, /* unknown function */
};

#define MDIO_MMD_PHYXS      4    /* PHY Extender Sublayer */

  UINTN
  read_mmd_regs (
    UINTN XPCS_BASE, UINTN mmd_regs
  );

  STATIC
  UINT32
  GET_CURR_TX_DESC_INDEX (
    UINT32 *Index
  )
  {
    ASSERT (Index != NULL);

    if (*Index >= TX_DESC_CNT) {
      *Index = 0;
    }

    return *Index;
  }
#define RX_DESC_CNT 8
  STATIC UINT32 GET_CURR_RX_DESC_INDEX (UINT32 *Index)
  {
    ASSERT (Index != NULL);

    if (*Index >= RX_DESC_CNT) {
      *Index = 0;
    }

    return *Index;
  }

  #ifdef ENET_PORT0
  #define PORT_CLK_GATE_EN  0x1F030ul
  #elseif ENET_PORT1
  #define PORT_CLK_GATE_EN  0x1F034ul
  #elseif ENET_PORT2
  #define PORT_CLK_GATE_EN  0x1F038ul
  #else
  #define PORT_CLK_GATE_EN  0x1F03Cul
  #endif

#define MII_BMCR    0x00  /* Basic mode control register */
#define BMCR_RESET    0x8000  /* Reset to default state      */
#define BMCR_PDOWN    0x0800  /* Enable low power state      */
#define BMCR_ANENABLE   0x1000  /* Enable auto negotiation     */
#define BMCR_SPEED1000  0x0040  /* MSB of Speed (1000)         */
#define BMCR_SPEED100   0x2000  /* Select 100Mbps              */
#define MDIO_AN_LP_ABL1 0x0013
#define MDIO_AN_LP_ABL2 0x0014
#define MDIO_AN_LP_ABL3 0x0015
#define MDIO_AN_INTMASK 0x8001
#define MDIO_AN_INT     0x8002
#define AN_INT_CMPLT  0x0001
#define AN_INC_LNK    0x0002
#define AN_PG_RCV     0x0004
#define MDIO_CTRL1    MII_BMCR
#define MDIO_CTRL2    7 /* 10G control 2 */
#define MDIO_CTRL1_RESET    BMCR_RESET
#define MDIO_CTRL1_SPEEDSELEXT    (BMCR_SPEED1000 | BMCR_SPEED100)
#define MDIO_CTRL1_SPEEDSEL   (MDIO_CTRL1_SPEEDSELEXT | 0x003c)
#define MDIO_CTRL1_LPOWER   BMCR_PDOWN
#define MDIO_CTRL1_SPEED10G (MDIO_CTRL1_SPEEDSELEXT | 0x00)
#define MDIO_CTRL1_SPEED1G (MDIO_CTRL1_SPEED10G & ~BMCR_SPEED100)
#define MDIO_AN_CTRL1_ENABLE    BMCR_ANENABLE
#define MDIO_AN_CTRL1_RESTART   0x0200
#define MDIO_MMD_AN   7 /* Auto-Negotiation */
#define MDIO_MMD_VEND2   31 /* Auto-Negotiation */
#define MDIO_MMD_PCS 3 /* Physical Coding Sublayer */
#define MDIO_MMD_PMAPMD   1 /* Physical Medium Attachment */
#define MDIO_PCS_CTRL2_TYPE   0x0003  /* PCS type selection */
#define MDIO_PCS_CTRL2_10GBR    0x0000  /* 10GBASE-R type */
#define MDIO_PCS_CTRL2_10GBX    0x0001  /* 10GBASE-X type */
#define MDIO_PCS_CTRL2_10GBW    0x0010  /* 10GBASE-X type */
#define MDIO_PMA_10GBR_CTRL 0x0096
#define MDIO_PMA_10GBR_STS  0x0097
#define MDIO_PMA_10GBR_LP_CESTS  0x0099 /* 10GBASE-KR LP Coefficient Status Register */
#define MDIO_PMA_10GBR_LD_CESTS  0x009B /* 10GBASE-KR LD (Local Device) Coefficient Status Register */
#define MDIO_PMA_10GBR_CE_RR   0x8000 /* Bit 15 - Receiver Ready in LD and LP Coefficient Status Register */
#define MDIO_PMA_10GBR_CTRL_KRTRAIN_START 0x1
#define MDIO_PMA_10GBR_CTRL_KRTRAIN 0x2
#define MDIO_PMA_10GBR_STS_TR_FAIL  0x0008  /* Bit 3 - KR training failure */
#define MDIO_PMA_10GBR_STS_RCV_STS  0x0001  /* Bit 1 - KR training Receiver Status */
#define MII_ADDR_C45 (1 << 30)
#define PCS_MMD_SELECT 0xff
#define MDIO_PCS_DEV_ID1      0x0002  /* PCS MMD Device Identifier Register 1 */
#define MDIO_PCS_STS1         0x0001  /* PCS MMD Status1 register */
#define PCS_STS1_RLU          0x0004  /* Rx Link Up bit in PCS MMD Status1 register */
#define PMA_MPLLA_CTRL0       0x8071
#define PMA_MPLLA_CTRL2       0x8073
#define PMA_VCO_CAL_LOAD0     0x8092
#define PMA_VCO_CAL_REF0      0x8096
#define PMA_AFE_DFE_EN        0x805D
#define PMA_EQUA_CNTRL4       0x805C
#define PMA_TX_RATE_CNTRL     0x8034
#define PMA_TX_GEN_CNTRL      0x8032
#define PMA_RX_RATE_CNTRL     0x8054
#define PMA_RX_GEN_CNTRL2     0x8052
/* PCS register offsets */
//#define PCS_V1_WINDOW_SELECT    0x03fc
//#define PCS_V2_WINDOW_DEF    0x9060
//#define PCS_V2_WINDOW_SELECT    0x9064

#define PCS_V2_RV_WINDOW_DEF        0x1060
#define PCS_V2_RV_WINDOW_SELECT     0x1064

/* PCS register entry bit positions and sizes */
#define PCS_V2_WINDOW_DEF_OFFSET_INDEX  6
#define PCS_V2_WINDOW_DEF_OFFSET_WIDTH  14
#define PCS_V2_WINDOW_DEF_SIZE_INDEX  2
#define PCS_V2_WINDOW_DEF_SIZE_WIDTH  4


#define MPLLA_MULTIPLIER_1G   32
#define MPLLA_MULTIPLIER_10G  33
#define MPLLA_BANDWIDTH_1G    65
#define VCO_LD_VAL_0_1G       1344
#define VCO_LD_VAL_0_10G_156  1353
#define VCO_REF_LD_0_1G_156   42
#define VCO_REF_LD_0_10G_156  41
#define PMA_AFE_DFE_EN_0_1G   0
#define PMA_AFE_DFE_EN_0_10G  1
#define CONT_ADAPT_0_1G       0
#define CONT_ADAPT_0_10G      1
#define TX0_RATE_1G           0x3
#define TX0_RATE_10G          0x0
#define RX0_RATE_1G           0x3
#define RX0_RATE_10G          0x0
#define TX0_WIDTH_1G          0x1
#define TX0_WIDTH_10G_16BIT   0x2
#define RX0_WIDTH_1G          0x1
#define RX0_WIDTH_10G_16BIT   0x2
#define MPLLA_DIV16P5_CLK_EN  0
#define MPLLA_DIV10P5_CLK_EN  1
#define MPLLA_DIV18P5_CLK_EN  0

/* MAC Control register entry bit positions and sizes */
#define XP_DRIVER_INT_REQ_REQUEST_INDEX    0
#define XP_DRIVER_INT_REQ_REQUEST_WIDTH    1
#define XP_DRIVER_INT_RO_STATUS_INDEX    0
#define XP_DRIVER_INT_RO_STATUS_WIDTH    1
#define XP_DRIVER_SCRATCH_0_COMMAND_INDEX  0
#define XP_DRIVER_SCRATCH_0_COMMAND_WIDTH  8
#define XP_DRIVER_SCRATCH_0_SUB_COMMAND_INDEX  8
#define XP_DRIVER_SCRATCH_0_SUB_COMMAND_WIDTH  8
#define XP_ECC_CNT0_RX_DED_INDEX    24
#define XP_ECC_CNT0_RX_DED_WIDTH    8
#define XP_ECC_CNT0_RX_SEC_INDEX    16
#define XP_ECC_CNT0_RX_SEC_WIDTH    8
#define XP_ECC_CNT0_TX_DED_INDEX    8
#define XP_ECC_CNT0_TX_DED_WIDTH    8
#define XP_ECC_CNT0_TX_SEC_INDEX    0
#define XP_ECC_CNT0_TX_SEC_WIDTH    8
#define XP_ECC_CNT1_DESC_DED_INDEX    8
#define XP_ECC_CNT1_DESC_DED_WIDTH    8
#define XP_ECC_CNT1_DESC_SEC_INDEX    0
#define XP_ECC_CNT1_DESC_SEC_WIDTH    8
#define XP_ECC_IER_DESC_DED_INDEX    0
#define XP_ECC_IER_DESC_DED_WIDTH    1
#define XP_ECC_IER_DESC_SEC_INDEX    1
#define XP_ECC_IER_DESC_SEC_WIDTH    1
#define XP_ECC_IER_RX_DED_INDEX      2
#define XP_ECC_IER_RX_DED_WIDTH      1
#define XP_ECC_IER_RX_SEC_INDEX      3
#define XP_ECC_IER_RX_SEC_WIDTH      1
#define XP_ECC_IER_TX_DED_INDEX      4
#define XP_ECC_IER_TX_DED_WIDTH      1
#define XP_ECC_IER_TX_SEC_INDEX      5
#define XP_ECC_IER_TX_SEC_WIDTH      1
#define XP_ECC_ISR_DESC_DED_INDEX    0
#define XP_ECC_ISR_DESC_DED_WIDTH    1
#define XP_ECC_ISR_DESC_SEC_INDEX    1
#define XP_ECC_ISR_DESC_SEC_WIDTH    1
#define XP_ECC_ISR_RX_DED_INDEX      2
#define XP_ECC_ISR_RX_DED_WIDTH      1
#define XP_ECC_ISR_RX_SEC_INDEX      3
#define XP_ECC_ISR_RX_SEC_WIDTH      1
#define XP_ECC_ISR_TX_DED_INDEX      4
#define XP_ECC_ISR_TX_DED_WIDTH      1
#define XP_ECC_ISR_TX_SEC_INDEX      5
#define XP_ECC_ISR_TX_SEC_WIDTH      1
#define XP_I2C_MUTEX_BUSY_INDEX      31
#define XP_I2C_MUTEX_BUSY_WIDTH      1
#define XP_I2C_MUTEX_ID_INDEX      29
#define XP_I2C_MUTEX_ID_WIDTH      2
#define XP_I2C_MUTEX_ACTIVE_INDEX    0
#define XP_I2C_MUTEX_ACTIVE_WIDTH    1
#define XP_MAC_ADDR_HI_VALID_INDEX    31
#define XP_MAC_ADDR_HI_VALID_WIDTH    1
#define XP_PROP_0_CONN_TYPE_INDEX    28
#define XP_PROP_0_CONN_TYPE_WIDTH    3
#define XP_PROP_0_MDIO_ADDR_INDEX    16
#define XP_PROP_0_MDIO_ADDR_WIDTH    5
#define XP_PROP_0_PORT_ID_INDEX      0
#define XP_PROP_0_PORT_ID_WIDTH      8
#define XP_PROP_0_PORT_MODE_INDEX    8
#define XP_PROP_0_PORT_MODE_WIDTH    4
#define XP_PROP_0_PORT_SPEEDS_INDEX    23
#define XP_PROP_0_PORT_SPEEDS_WIDTH    4
#define XP_PROP_1_MAX_RX_DMA_INDEX    24
#define XP_PROP_1_MAX_RX_DMA_WIDTH    5
#define XP_PROP_1_MAX_RX_QUEUES_INDEX    8
#define XP_PROP_1_MAX_RX_QUEUES_WIDTH    5
#define XP_PROP_1_MAX_TX_DMA_INDEX    16
#define XP_PROP_1_MAX_TX_DMA_WIDTH    5
#define XP_PROP_1_MAX_TX_QUEUES_INDEX    0
#define XP_PROP_1_MAX_TX_QUEUES_WIDTH    5
#define XP_PROP_2_RX_FIFO_SIZE_INDEX    16
#define XP_PROP_2_RX_FIFO_SIZE_WIDTH    16
#define XP_PROP_2_TX_FIFO_SIZE_INDEX    0
#define XP_PROP_2_TX_FIFO_SIZE_WIDTH    16
#define XP_PROP_3_GPIO_MASK_INDEX    28
#define XP_PROP_3_GPIO_MASK_WIDTH    4
#define XP_PROP_3_GPIO_MOD_ABS_INDEX    20
#define XP_PROP_3_GPIO_MOD_ABS_WIDTH    4
#define XP_PROP_3_GPIO_RATE_SELECT_INDEX  16
#define XP_PROP_3_GPIO_RATE_SELECT_WIDTH  4
#define XP_PROP_3_GPIO_RX_LOS_INDEX    24
#define XP_PROP_3_GPIO_RX_LOS_WIDTH    4
#define XP_PROP_3_GPIO_TX_FAULT_INDEX    12
#define XP_PROP_3_GPIO_TX_FAULT_WIDTH    4
#define XP_PROP_3_GPIO_ADDR_INDEX    8
#define XP_PROP_3_GPIO_ADDR_WIDTH    3
#define XP_PROP_3_MDIO_RESET_INDEX    0
#define XP_PROP_3_MDIO_RESET_WIDTH    2
#define XP_PROP_3_MDIO_RESET_I2C_ADDR_INDEX  8
#define XP_PROP_3_MDIO_RESET_I2C_ADDR_WIDTH  3
#define XP_PROP_3_MDIO_RESET_I2C_GPIO_INDEX  12
#define XP_PROP_3_MDIO_RESET_I2C_GPIO_WIDTH  4
#define XP_PROP_3_MDIO_RESET_INT_GPIO_INDEX  4
#define XP_PROP_3_MDIO_RESET_INT_GPIO_WIDTH  2
#define XP_PROP_4_MUX_ADDR_HI_INDEX    8
#define XP_PROP_4_MUX_ADDR_HI_WIDTH    5
#define XP_PROP_4_MUX_ADDR_LO_INDEX    0
#define XP_PROP_4_MUX_ADDR_LO_WIDTH    3
#define XP_PROP_4_MUX_CHAN_INDEX    4
#define XP_PROP_4_MUX_CHAN_WIDTH    3
#define XP_PROP_4_REDRV_ADDR_INDEX    16
#define XP_PROP_4_REDRV_ADDR_WIDTH    7
#define XP_PROP_4_REDRV_IF_INDEX    23
#define XP_PROP_4_REDRV_IF_WIDTH    1
#define XP_PROP_4_REDRV_LANE_INDEX    24
#define XP_PROP_4_REDRV_LANE_WIDTH    3
#define XP_PROP_4_REDRV_MODEL_INDEX    28
#define XP_PROP_4_REDRV_MODEL_WIDTH    3
#define XP_PROP_4_REDRV_PRESENT_INDEX    31
#define XP_PROP_4_REDRV_PRESENT_WIDTH    1

//Define XGBE IC registers
#define XGBE_MAC_CTRL_OFFSET    0x1d000ul
#define XGBE_I2C_CTRL_OFFSET    0x1e000ul
#define IC_CON                  0x0000
#define IC_TAR                  0x0004
#define IC_DATA_CMD             0x0010
#define IC_INTR_STAT            0x002c
#define IC_INTR_MASK            0x0030
#define IC_CLR_INTR             0x0040
#define IC_ENABLE               0x006c
#define IC_TXFLR                0x0074
#define IC_RXFLR                0x0078
#define IC_TX_ABRT_SOURCE       0x0080
#define IC_ENABLE_STATUS        0x009c
#define IC_COMP_PARAM_1         0x00f4
#define IC_ENABLE_ABORT_INDEX      1
#define IC_ENABLE_ABORT_WIDTH      1
#define IC_ENABLE_EN_INDEX      0
#define IC_ENABLE_EN_WIDTH      1

#define IC_TX_ABRT_7B_ADDR_NOACK    0x0001
#define IC_TX_ABRT_ARB_LOST      0x1000


  #define IC_COMP_PARAM_1_MAX_SPEED_MODE_INDEX    2
  #define IC_COMP_PARAM_1_MAX_SPEED_MODE_WIDTH    2
  #define IC_COMP_PARAM_1_RX_BUFFER_DEPTH_INDEX   8
  #define IC_COMP_PARAM_1_RX_BUFFER_DEPTH_WIDTH   8
  #define IC_COMP_PARAM_1_TX_BUFFER_DEPTH_INDEX   16
  #define IC_COMP_PARAM_1_TX_BUFFER_DEPTH_WIDTH   8
  #define IC_CON_MASTER_MODE_INDEX        0
  #define IC_CON_MASTER_MODE_WIDTH        1
  #define IC_CON_RESTART_EN_INDEX         5
  #define IC_CON_RESTART_EN_WIDTH         1
  #define IC_CON_SLAVE_DISABLE_INDEX      6
  #define IC_CON_SLAVE_DISABLE_WIDTH      1
  #define IC_CON_SPEED_INDEX          1
  #define IC_CON_SPEED_WIDTH          2
  #define IC_DATA_CMD_CMD_INDEX           8
  #define IC_DATA_CMD_CMD_WIDTH           1
  #define IC_DATA_CMD_STOP_INDEX          9
  #define IC_DATA_CMD_STOP_WIDTH          1
  #define IC_ENABLE_EN_INDEX          0
  #define IC_ENABLE_EN_WIDTH          1
  #define IC_ENABLE_STATUS_EN_INDEX       0
  #define IC_ENABLE_STATUS_EN_WIDTH       1
  #define IC_INTR_MASK_TX_EMPTY_INDEX     4
  #define IC_INTR_MASK_TX_EMPTY_WIDTH     1
  #define IC_INTR_STAT_RX_FULL_INDEX      2
  #define IC_INTR_STAT_RX_FULL_WIDTH      1
  #define IC_INTR_STAT_STOP_DET_INDEX     9
  #define IC_INTR_STAT_STOP_DET_WIDTH     1
  #define IC_INTR_STAT_TX_ABRT_INDEX      6
  #define IC_INTR_STAT_TX_ABRT_WIDTH      1
  #define IC_INTR_STAT_TX_EMPTY_INDEX     4
  #define IC_INTR_STAT_TX_EMPTY_WIDTH     1

#define IC_RAW_INTR_STAT_RX_FULL_INDEX    2
#define IC_RAW_INTR_STAT_RX_FULL_WIDTH    1
#define IC_RAW_INTR_STAT_STOP_DET_INDEX    9
#define IC_RAW_INTR_STAT_STOP_DET_WIDTH    1
#define IC_RAW_INTR_STAT_TX_ABRT_INDEX    6
#define IC_RAW_INTR_STAT_TX_ABRT_WIDTH    1
#define IC_RAW_INTR_STAT_TX_EMPTY_INDEX    4
#define IC_RAW_INTR_STAT_TX_EMPTY_WIDTH    1

#define XGBE_SFP_ADDRESS      0x50
#define PCA9535_ADDRESS       0x40
#define PCA9555_ADDRESS       0x20
#define XGBE_GPIO_ADDRESS_PCA9555  0x20

//PLATFORM Connectivity
#define ENET_PLAT_PORT_PROPERTY_0  0x1F800ul //20, 40, 60
#define ENET_PLAT_PORT_PROPERTY_1  0x1F804ul //24, 44
#define ENET_PLAT_PORT_PROPERTY_2  0x1F808ul
#define ENET_PLAT_PORT_PROPERTY_3  0x1F80Cul
#define ENET_PLAT_PORT_PROPERTY_4  0x1F810ul
#define ENET_PLAT_PORT_PROPERTY_5  0x1F814ul

#define ENET_PORT_PROPERTY_0  0x1D000ul
#define ENET_PORT_PROPERTY_1  0x1D004ul
#define ENET_PORT_PROPERTY_2  0x1D008ul
#define ENET_PORT_PROPERTY_3  0x1D00Cul
#define ENET_PORT_PROPERTY_4  0x1D010ul
#define ENET_PORT_PROPERTY_5  0x1D014ul
#define PORT_MAC_ADDR_LOW     0x1D020ul
#define PORT_MAC_ADDR_HIGH    0x1D024ul
#define PAD_MUX0              0x1F000ul
#define PAD_MUX1              0x1F004ul
#define MAC_TIMESTAMP_CONTROL 0x00D00ul
#define MAC_SUB_SECOND_INCREMENT 0x00D04ul
#define PORT_I2C_MUTEX        0x1D080ul
#define MC_DRIVER_MB_INT_REQ  0x0060ul
#define MC_DRIVER_MB_INT_RES  0x0064ul
#define MC_DRIVER_MB_S0        0x0068ul
#define MC_DRIVER_MB_S1       0x006cul
#define INT_EN                0x1D078ul

#define PLAT_CONFIG           8
#define MDIO_ID               0
#define SUPP_SPEED            0xB   //bit0=100M, bit1=1G bit2=2.5G bit3=10G
#define CONN_TYPE             0x1
#define MDIO_RESET_TYPE       0x0
#define GPIO_ADD              0x0  //Lower 3 bits of the GPIO expander
#define TX_FAULT_NOT_USED     0
#define TX_FAULT0             0xE   //IO1_6 = 1110b
#define TX_FAULT1             0xA
#define TX_FAULT2             0x6   //IO0_6 = 0110b
#define TX_FAULT3             0x2
#define RS_NOT_USED           0
#define MOD_ABS_NOT_USED      0
#define MOD_ABS0              0xC  //IO1_4 = 1100b
#define MOD_ABS1              0x8
#define MOD_ABS2              0x4
#define MOD_ABS3              0x0
#define RX_LOS_NOT_USED       0
#define RX_LOS0               0xD
#define RX_LOS1               0x9
#define RX_LOS2               0x5
#define RX_LOS3               0x1
#define MUX_LOW_ADD0          0x0
#define MUX_LOW_ADD1          0x1
#define MUX_LOW_ADD2          0x2
#define MUX_LOW_ADD3          0x3
#define RX_LOS_NOT_SUPPORTED    0x8
#define MOD_ABS_NOT_SUPPORTED   0x4
#define RS_NOT_SUPPORTED        0x2
#define TX_FAULT_NOT_SUPPORTED  0x1
//#define PCA9545_ADDRESS_LOWER  0x0 // Only Lower 3 bits address
#define PCA9545_ADDRESS_UPPER   0x1C
#define SFP_DIRECT_CONNECT      0x1F

// MDIO undefined or vendor specific registers
  #ifndef MDIO_PMA_10GBR_PMD_CTRL
  #define MDIO_PMA_10GBR_PMD_CTRL    0x0096
  #endif

  #ifndef MDIO_PMA_10GBR_FECCTRL
  #define MDIO_PMA_10GBR_FECCTRL    0x00ab
  #endif

  #ifndef MDIO_PCS_DIG_CTRL
  #define MDIO_PCS_DIG_CTRL    0x8000
  #endif

  #ifndef MDIO_AN_XNP
  #define MDIO_AN_XNP      0x0016
  #endif

  #ifndef MDIO_AN_LPX
  #define MDIO_AN_LPX      0x0019
  #endif

  #ifndef MDIO_AN_COMP_STAT
  #define MDIO_AN_COMP_STAT    0x0030
  #endif

  #ifndef MDIO_AN_INTMASK
  #define MDIO_AN_INTMASK      0x8001
  #endif

  #ifndef MDIO_AN_INT
  #define MDIO_AN_INT      0x8002
  #endif

  #ifndef MDIO_VEND2_AN_ADVERTISE
  #define MDIO_VEND2_AN_ADVERTISE    0x0004
  #endif

  #ifndef MDIO_VEND2_AN_LP_ABILITY
  #define MDIO_VEND2_AN_LP_ABILITY  0x0005
  #endif

  #ifndef MDIO_VEND2_AN_CTRL
  #define MDIO_VEND2_AN_CTRL    0x8001
  #endif

  #ifndef MDIO_VEND2_AN_STAT
  #define MDIO_VEND2_AN_STAT    0x8002
  #endif

  #ifndef MDIO_CTRL1_SPEED1G
  #define MDIO_CTRL1_SPEED1G    (MDIO_CTRL1_SPEED10G & ~BMCR_SPEED100)
  #endif

  #ifndef MDIO_VEND2_CTRL1_AN_ENABLE
  #define MDIO_VEND2_CTRL1_AN_ENABLE  BIT12
  #endif

  #ifndef MDIO_VEND2_CTRL1_AN_RESTART
  #define MDIO_VEND2_CTRL1_AN_RESTART  BIT9
  #endif

  #ifndef MDIO_VEND2_CTRL1_SS6
  #define MDIO_VEND2_CTRL1_SS6    BIT6
  #endif

  #ifndef MDIO_VEND2_CTRL1_SS13
  #define MDIO_VEND2_CTRL1_SS13    BIT13
  #endif

/* MDIO mask values */
#define XGBE_AN_CL73_INT_CMPLT    BIT0
#define XGBE_AN_CL73_INC_LINK    BIT1
#define XGBE_AN_CL73_PG_RCV    BIT2
#define XGBE_AN_CL73_INT_MASK    0x07

#define XGBE_XNP_MCF_NULL_MESSAGE  0x001
#define XGBE_XNP_ACK_PROCESSED    BIT12
#define XGBE_XNP_MP_FORMATTED    BIT13
#define XGBE_XNP_NP_EXCHANGE    BIT15

#define XGBE_KR_TRAINING_START    BIT0
#define XGBE_KR_TRAINING_ENABLE    BIT1

#define XGBE_PCS_CL37_BP    BIT12
#define XGBE_PCS_EN_VSMMD1    BIT13

#define XGBE_AN_CL37_INT_CMPLT    BIT0
#define XGBE_AN_CL37_INT_MASK    0x01

#define XGBE_AN_CL37_HD_MASK    0x40
#define XGBE_AN_CL37_FD_MASK    0x20

#define XGBE_AN_CL37_PCS_MODE_MASK   0x06
#define XGBE_AN_CL37_PCS_MODE_BASEX  0x00
#define XGBE_AN_CL37_PCS_MODE_SGMII  0x04
#define XGBE_AN_CL37_TX_CONFIG_MASK  0x08
#define XGBE_AN_CL37_MII_CTRL_8BIT   0x0100

/* MAC Control register offsets */
#define XP_PROP_0      0x0000
#define XP_PROP_1      0x0004
#define XP_PROP_2      0x0008
#define XP_PROP_3      0x000c
#define XP_PROP_4      0x0010
#define XP_PROP_5      0x0014
#define XP_MAC_ADDR_LO      0x0020
#define XP_MAC_ADDR_HI      0x0024
#define XP_ECC_ISR      0x0030
#define XP_ECC_IER      0x0034
#define XP_ECC_CNT0      0x003c
#define XP_ECC_CNT1      0x0040
#define XP_DRIVER_INT_REQ    0x0060
#define XP_DRIVER_INT_RO    0x0064
#define XP_DRIVER_SCRATCH_0    0x0068
#define XP_DRIVER_SCRATCH_1    0x006c
#define XP_INT_EN      0x0078
#define XP_I2C_MUTEX      0x0080
#define XP_MDIO_MUTEX      0x0084

/* I2C target addresses */
#define XGBE_SFP_SERIAL_ID_ADDRESS        0x50
#define XGBE_SFP_DIAG_INFO_ADDRESS        0x51
#define XGBE_SFP_PHY_ADDRESS              0x56


#define ethtool_link_ksettings_add_link_mode(ptr, name, mode)		\
	__set_bit(ETHTOOL_LINK_MODE_ ## mode ## _BIT, (ptr)->link_modes.name)
#define upper_32_bits(n) ((UINT32)((UINTN)((UINTN)(n) >> 16) >> 16))
#define lower_32_bits(n) ((UINT32)((UINTN)(n)))

#define DEBUG_DEAD_LOOP            \
  do {                             \
       VOLATILE UINTN __iii;       \
       __iii = 1;                  \
       while (__iii) {};           \
  } while (FALSE)

#define GET_BITS(_var, _index, _width)                    \
    (((_var) >> (_index)) & ((0x1 << (_width)) - 1))

#define SET_BITS(_var, _index, _width, _val)                \
  do {                                    \
    (_var) &= ~(((0x1 << (_width)) - 1) << (_index));       \
    (_var) |= (((_val) & ((0x1 << (_width)) - 1)) << (_index)); \
  } while (0)

#define SET_BIT_FIELD(RC, INDEX, WIDTH, Value)   \
  RC &= ~(((0x1 << WIDTH) - 1) << INDEX); \
  RC |= ((Value & ((0x1 << WIDTH) - 1)) << INDEX)

#define SNP_SET_BIT_FIELD(BITS, Reg, Field, Value) \
  SET_BIT_FIELD (BITS, Reg##_##Field##_##INDEX, Reg##_##Field##_##WIDTH, Value)

#define GET_BIT_FIELD(RC, INDEX, WIDTH) ((RC >> INDEX ) & ((0x1 << WIDTH) - 1))

#define SNP_GET_BIT_FIELD(BITS, Reg, Field) \
  GET_BIT_FIELD (BITS, Reg##_##Field##_##INDEX, Reg##_##Field##_##WIDTH)

// Macros for building, reading or writing register values or bits
// within the register values of XPCS registers.

#define XPCS_IOWRITE32(xpcs_regs, _off, _val) \
  MmioWrite32 (xpcs_regs + (_off), _val)

#define XPCS_IOWRITE16(xpcs_regs, _off, _val) \
  MmioWrite16 (xpcs_regs + (_off), _val)

#define XPCS_IOREAD32(xpcs_regs, _off) \
  MmioRead32 (xpcs_regs + (_off))

#define XPCS_IOREAD16(xpcs_regs, _off) \
  MmioRead16 (xpcs_regs + (_off))

  // Macros for building, reading or writing register values or bits
  // within the register values of IC Control registers.

  #define XI2C_GET_BITS(_var, _prefix, _field)                \
      GET_BITS ((_var),                        \
           _prefix##_##_field##_INDEX,                \
           _prefix##_##_field##_WIDTH)

  #define XI2C_SET_BITS(_var, _prefix, _field, _val)          \
      SET_BITS ((_var),                        \
           _prefix##_##_field##_INDEX,                \
           _prefix##_##_field##_WIDTH, (_val))

  #define XI2C_IOREAD(_pdata, _reg)                   \
        MmioRead32 ((_pdata)->i2c_regs + _reg)

  #define XI2C_IOREAD_BITS(_pdata, _reg, _field)              \
      GET_BITS (XI2C_IOREAD ((_pdata), _reg),               \
           _reg##_##_field##_INDEX,               \
           _reg##_##_field##_WIDTH)

  #define XI2C_IOWRITE(_pdata, _reg, _val)                \
        MmioWrite32 ((_pdata)->i2c_regs + _reg, (_val))

  #define XI2C_IOWRITE_BITS(_pdata, _reg, _field, _val)           \
  do {                                    \
      UINT32 reg_val = XI2C_IOREAD ((_pdata), _reg);          \
      SET_BITS (reg_val,                       \
           _reg##_##_field##_INDEX,               \
           _reg##_##_field##_WIDTH, (_val));          \
      XI2C_IOWRITE ((_pdata), _reg, reg_val);              \
  } while (0)

/* Macros for building, reading or writing register values or bits
 * using MDIO.  Different from above because of the use of standardized
 * *nix include values.  No shifting is performed with the bit
 * operations, everything works on mask values.
 */
#define XMDIO_READ(xpcs_regs, _mmd, _reg)         \
  (read_mmd_regs((xpcs_regs),   \
    MII_ADDR_C45 | (_mmd << 16) | ((_reg) & 0xffff)))

#define XMDIO_READ_BITS(xpcs_regs, _mmd, _reg, _mask)     \
  (XMDIO_READ((xpcs_regs), _mmd, _reg) & _mask)

#define XMDIO_WRITE(xpcs_regs, _mmd, _reg, _val)        \
  (write_mmd_regs((xpcs_regs),    \
    MII_ADDR_C45 | (_mmd << 16) | ((_reg) & 0xffff), (_val)))

#define XMDIO_WRITE_BITS(xpcs_regs, _mmd, _reg, _mask, _val)    \
  do {                  \
    UINTN mmd_val = XMDIO_READ ((xpcs_regs), _mmd, _reg);     \
    mmd_val &= ~_mask;            \
    mmd_val |= (_val);            \
    XMDIO_WRITE ((xpcs_regs), _mmd, _reg, mmd_val);      \
  } while (0)


  typedef enum {
    XGBE_PORT_MODE_RSVD = 0,
    XGBE_PORT_MODE_BACKPLANE,
    XGBE_PORT_MODE_BACKPLANE_2500,
    XGBE_PORT_MODE_1000BASE_T,
    XGBE_PORT_MODE_1000BASE_X,
    XGBE_PORT_MODE_NBASE_T,
    XGBE_PORT_MODE_10GBASE_T,
    XGBE_PORT_MODE_10GBASE_R,
    XGBE_PORT_MODE_SFP,
    XGBE_PORT_MODE_MAX,
  } xgbe_port_mode;

  typedef enum {
    XGBE_CONN_TYPE_NONE = 0,
    XGBE_CONN_TYPE_SFP = 1,
    XGBE_CONN_TYPE_MDIO = 2,
    XGBE_CONN_TYPE_BACKPLANE = 4,
    XGBE_CONN_TYPE_MAX,
  } xgbe_conn_type ;

  /* SFP/SFP+ related definitions */
  typedef enum {
    XGBE_SFP_COMM_DIRECT = 0,
    XGBE_SFP_COMM_PCA9545,
  } xgbe_sfp_comm;

  typedef enum {
    XGBE_SFP_CABLE_UNKNOWN = 0,
    XGBE_SFP_CABLE_ACTIVE,
    XGBE_SFP_CABLE_PASSIVE,
  } xgbe_sfp_cable;

  typedef enum {
    XGBE_SFP_BASE_UNKNOWN = 0,
    XGBE_SFP_BASE_1000_T,
    XGBE_SFP_BASE_1000_SX,
    XGBE_SFP_BASE_1000_LX,
    XGBE_SFP_BASE_1000_CX,
    XGBE_SFP_BASE_10000_SR,
    XGBE_SFP_BASE_10000_LR,
    XGBE_SFP_BASE_10000_LRM,
    XGBE_SFP_BASE_10000_ER,
    XGBE_SFP_BASE_10000_CR,
  } xgbe_sfp_base;

  typedef enum {
    XGBE_SFP_SPEED_UNKNOWN = 0,
    XGBE_SFP_SPEED_100_1000,
    XGBE_SFP_SPEED_1000,
    XGBE_SFP_SPEED_10000,
  } xgbe_sfp_speed;


  /* MDIO PHY reset types */
  enum xgbe_mdio_reset
  {
    XGBE_MDIO_RESET_NONE = 0,
    XGBE_MDIO_RESET_I2C_GPIO,
    XGBE_MDIO_RESET_INT_GPIO,
    XGBE_MDIO_RESET_MAX,
  };

  /* Re-driver related definitions */
  enum xgbe_phy_redrv_if
  {
    XGBE_PHY_REDRV_IF_MDIO = 0,
    XGBE_PHY_REDRV_IF_I2C,
    XGBE_PHY_REDRV_IF_MAX,
  };

  enum xgbe_phy_redrv_model
  {
    XGBE_PHY_REDRV_MODEL_4223 = 0,
    XGBE_PHY_REDRV_MODEL_4227,
    XGBE_PHY_REDRV_MODEL_MAX,
  };

  enum xgbe_phy_redrv_mode
  {
    XGBE_PHY_REDRV_MODE_CX = 5,
    XGBE_PHY_REDRV_MODE_SR = 9,
  };

  enum xgbe_speed
  {
    XGBE_SPEED_1000 = 0,
    XGBE_SPEED_2500,
    XGBE_SPEED_10000,
    XGBE_SPEEDS,
  };

  enum xgbe_an_mode
  {
    XGBE_AN_MODE_CL73 = 0,
    XGBE_AN_MODE_CL73_REDRV,
    XGBE_AN_MODE_CL37,
    XGBE_AN_MODE_CL37_SGMII,
    XGBE_AN_MODE_NONE,
  };

  enum xgbe_an
  {
    XGBE_AN_READY = 0,
    XGBE_AN_PAGE_RECEIVED,
    XGBE_AN_INCOMPAT_LINK,
    XGBE_AN_COMPLETE,
    XGBE_AN_NO_LINK,
    XGBE_AN_ERROR,
  };

  enum xgbe_rx
  {
    XGBE_RX_BPA = 0,
    XGBE_RX_XNP,
    XGBE_RX_COMPLETE,
    XGBE_RX_ERROR,
  };

  enum xgbe_mode
  {
    XGBE_MODE_KX_1000 = 0,
    XGBE_MODE_KX_2500,
    XGBE_MODE_KR,
    XGBE_MODE_X,
    XGBE_MODE_SGMII_100,
    XGBE_MODE_SGMII_1000,
    XGBE_MODE_SFI,
    XGBE_MODE_UNKNOWN,
  };

  enum xgbe_speedset
  {
    XGBE_SPEEDSET_1000_10000 = 0,
    XGBE_SPEEDSET_2500_10000,
  };

  enum xgbe_mdio_mode
  {
    XGBE_MDIO_MODE_NONE = 0,
    XGBE_MDIO_MODE_CL22,
    XGBE_MDIO_MODE_CL45,
  };

  typedef struct {
    UINT8 base[64];
    UINT8 extd[32];
    UINT8 vendor[32];
  } xgbe_sfp_eeprom;

  typedef struct {
    xgbe_port_mode port_mode;
    UINT8 port_id;
    UINTN port_speeds;
    UINTN conn_type;
    enum xgbe_mode cur_mode;
    enum xgbe_mode start_mode;
    UINTN rrc_count;
    UINTN mdio_addr;
    UINTN comm_owned;
	
    // SFP Support
    xgbe_sfp_comm sfp_comm;
    UINTN sfp_mux_address;
    UINTN sfp_mux_channel;
	
    UINTN sfp_gpio_address;
	UINTN sfp_gpio_inputs;
    UINTN sfp_gpio_mask;
    UINTN sfp_gpio_rx_los;
    UINTN sfp_gpio_tx_fault;
    UINTN sfp_gpio_mod_absent;
    UINTN sfp_gpio_rate_select;
	
    UINTN sfp_rx_los;
    UINTN sfp_tx_fault;
    UINTN sfp_mod_absent;
    UINTN sfp_diags;
    UINTN sfp_phy_avail;
    UINTN sfp_cable_len;
    xgbe_sfp_base sfp_base;
    xgbe_sfp_cable sfp_cable;
    xgbe_sfp_speed sfp_speed;
    xgbe_sfp_eeprom sfp_eeprom;
	
    // External PHY support
    enum xgbe_mdio_mode phydev_mode;
    struct mii_bus  *mii;
    struct phy_device  *phydev;
    enum xgbe_mdio_reset  mdio_reset;
    UINTN mdio_reset_addr;
    UINTN mdio_reset_gpio;
	
    //Re-driver support
    UINTN redrv;
    UINTN redrv_if;
    UINTN redrv_addr;
    UINTN redrv_lane;
    UINTN redrv_model;

	/* KR AN support */
	UINTN phy_cdr_notrack;
	UINTN phy_cdr_delay;	
  } XGBE_PHY_DATA;
  
  /// Receive Normal Descriptor
  struct _RX_NORMAL_DESC_ {
    UINT32 RDES0;               ///< Receive Descriptor 0
    UINT32 RDES1;               ///< Receive Descriptor 1
    UINT32 RDES2;               ///< Receive Descriptor 2
    UINT32 RDES3;               ///< Receive Descriptor 3
  };

  typedef struct _RX_NORMAL_DESC_ RX_NORMAL_DESC;

  /// Transmit Normal Descriptor
  struct _TX_NORMAL_DESC_ {
    UINT32 TDES0;                ///< Transmit Descriptor 0
    UINT32 TDES1;                ///< Transmit Descriptor 1
    UINT32 TDES2;                ///< Transmit Descriptor 2
    UINT32 TDES3;                ///< Transmit Descriptor 3
  } ;

  typedef struct _TX_NORMAL_DESC_ TX_NORMAL_DESC;

/* Macros for reading or writing DMA channel registers
 *  Similar to the standard read and write macros except that the
 *  base register value is obtained from the ring
 */
#define XGMAC_DMA_IOREAD32(_channel, _reg)        \
  MmioRead32 ((_channel)->dma_regs + _reg)

#define XGMAC_DMA_IOREAD32_BITS(_channel, _reg, _field)     \
  GET_BIT_FIELD (XGMAC_DMA_IOREAD32 ((_channel), _reg),     \
     _reg##_##_field##_INDEX,       \
     _reg##_##_field##_WIDTH)

#define XGMAC_DMA_IOWRITE32(_channel, _reg, _val)     \
  MmioWrite32 ((_channel)->dma_regs + _reg, (_val))

#define XGMAC_DMA_IOWRITE32_BITS(_channel, _reg, _field, _val)    \
  do {                  \
    UINT32 reg_val = XGMAC_DMA_IOREAD32 ((_channel), _reg);    \
    SET_BIT_FIELD (reg_val,            \
      _reg##_##_field##_INDEX,       \
      _reg##_##_field##_WIDTH, (_val));      \
    XGMAC_DMA_IOWRITE32 ((_channel), _reg, reg_val);     \
  } while (0)

/* Macros for reading or writing MTL queue registers
 *  Similar to the standard read and write macros except that the
 *  base register value is calculated by the queue number
 */
#define XGMAC_MTL_IOREAD32(_pdata, _q, _reg)        \
  MmioRead32 ((_pdata)->xgmac_regs +         \
     MTL_Q_BASE + ((_q) * MTL_Q_INC) + _reg)

#define XGMAC_MTL_IOREAD32_BITS(_pdata, _q, _reg, _field)   \
  GET_BIT_FIELD (XGMAC_MTL_IOREAD32 ((_pdata), (_q), _reg),   \
     _reg##_##_field##_INDEX,       \
     _reg##_##_field##_WIDTH)

#define XGMAC_MTL_IOWRITE32(_pdata, _q, _reg, _val)     \
  MmioWrite32 ((_pdata)->xgmac_regs +      \
              MTL_Q_BASE + ((_q) * MTL_Q_INC) + _reg, (_val))

#define XGMAC_MTL_IOWRITE32_BITS(_pdata, _q, _reg, _field, _val)  \
  do {                  \
    UINT32 reg_val = XGMAC_MTL_IOREAD32 ((_pdata), (_q), _reg);    \
    SET_BIT_FIELD (reg_val,            \
      _reg##_##_field##_INDEX,       \
      _reg##_##_field##_WIDTH, (_val));      \
    XGMAC_MTL_IOWRITE32 ((_pdata), (_q), _reg, reg_val);   \
  } while (0)

/* Macros for reading or writing registers
 *  The ioread macros will get bit fields or full values using the
 *  register definitions formed using the input names
 *
 *  The iowrite macros will set bit fields or full values using the
 *  register definitions formed using the input names
 */
#define XGMAC_IOREAD32(_pdata, _reg)          \
  MmioRead32 ((_pdata)->xgmac_regs + _reg)

#define XGMAC_IOREAD32_BITS(_pdata, _reg, _field)     \
  GET_BIT_FIELD (XGMAC_IOREAD32 ((_pdata), _reg),     \
     _reg##_##_field##_INDEX,       \
     _reg##_##_field##_WIDTH)

#define XGMAC_IOWRITE32(_pdata, _reg, _val)       \
  MmioWrite32 ((_pdata)->xgmac_regs + _reg, (_val))

#define XGMAC_IOWRITE32_BITS(_pdata, _reg, _field, _val)    \
  do {                  \
    UINT32 reg_val = XGMAC_IOREAD32 ((_pdata), _reg);      \
    SET_BIT_FIELD (reg_val,            \
      _reg##_##_field##_INDEX,       \
      _reg##_##_field##_WIDTH, (_val));      \
    XGMAC_IOWRITE32 ((_pdata), _reg, reg_val);     \
  } while (0)

  /* Macros for building, reading or writing register values or bits
 * within the register values of MAC Control registers.
 */
#define XP_GET_BITS(_var, _prefix, _field)      \
  GET_BITS ((_var),      \
     _prefix##_##_field##_INDEX,      \
     _prefix##_##_field##_WIDTH)

#define XP_SET_BITS(_var, _prefix, _field, _val)     \
  SET_BITS ((_var),     \
     _prefix##_##_field##_INDEX,      \
     _prefix##_##_field##_WIDTH, (_val))

#define XP_IOREAD(_pdata, _reg)      \
  MmioRead32 ((_pdata)->xprop_regs + (_reg))

#define XP_IOREAD_BITS(_pdata, _reg, _field)      \
  GET_BITS (XP_IOREAD ((_pdata), (_reg)),      \
     _reg##_##_field##_INDEX,      \
     _reg##_##_field##_WIDTH)

#define XP_IOWRITE(_pdata, _reg, _val)      \
  MmioWrite32 ((_pdata)->xprop_regs + (_reg), (_val) )

#define XP_IOWRITE_BITS(_pdata, _reg, _field, _val)      \
  do {      \
    UINT32 reg_val = XP_IOREAD ((_pdata), (_reg));      \
    SET_BITS (reg_val,      \
       _reg##_##_field##_INDEX,      \
       _reg##_##_field##_WIDTH, (_val));      \
    XP_IOWRITE ((_pdata), (_reg), reg_val);      \
  } while (0)

/* Macros for building, reading or writing register values or bits
 * within the register values of XPCS registers.
 */
#define XPCS_GET_BITS(_var, _prefix, _field)          \
  GET_BITS ((_var),                                  \
    _prefix##_##_field##_INDEX,                  \
    _prefix##_##_field##_WIDTH)

#define XPCS_SET_BITS(_var, _prefix, _field, _val)    \
  SET_BITS ((_var),                                  \
     _prefix##_##_field##_INDEX,                  \
     _prefix##_##_field##_WIDTH, (_val))

// Bit setting and getting macros based on register fields
//   The get macro uses the bit field definitions formed using the input
//   names to extract the current bit field value from within the
//   variable

//   The set macro uses the bit field definitions formed using the input
//   names to set the bit field of the variable to the specified value

#define XGMAC_GET_BITS(_var, _prefix, _field)       \
  GET_BIT_FIELD (_var,             \
     _prefix##_##_field##_INDEX,        \
     _prefix##_##_field##_WIDTH)

#define XGMAC_SET_BITS(_var, _prefix, _field, _val)     \
  SET_BIT_FIELD (_var,             \
     _prefix##_##_field##_INDEX,        \
     _prefix##_##_field##_WIDTH, (_val))

#define XGMAC_MAX_FLOW_CONTROL_QUEUES 8
#define FIFO_SIZE_B(x)      (x)
#define FIFO_SIZE_KB(x)     (x * 1024)

#define min_t(x, y) \
          (((x) > (y))? (y):(x))

#define RX_NORMAL_DESC3_ES_INDEX    15
#define RX_NORMAL_DESC3_ES_WIDTH    1
#define RX_NORMAL_DESC3_ETLT_INDEX    16
#define RX_NORMAL_DESC3_ETLT_WIDTH    4
#define RX_NORMAL_DESC3_INTE_INDEX    30
#define RX_NORMAL_DESC3_INTE_WIDTH    1
#define RX_NORMAL_DESC3_OWN_INDEX   31
#define RX_NORMAL_DESC3_OWN_WIDTH   1
#define RX_NORMAL_DESC3_PL_INDEX    0
#define RX_NORMAL_DESC3_PL_WIDTH    14

#define TX_NORMAL_DESC2_HL_B1L_INDEX    0
#define TX_NORMAL_DESC2_HL_B1L_WIDTH    14
#define TX_NORMAL_DESC2_IC_INDEX    31
#define TX_NORMAL_DESC2_IC_WIDTH    1
#define TX_NORMAL_DESC3_CIC_INDEX   16
#define TX_NORMAL_DESC3_CIC_WIDTH   2
#define TX_NORMAL_DESC3_CPC_INDEX   26
#define TX_NORMAL_DESC3_CPC_WIDTH   2
#define TX_NORMAL_DESC3_CTXT_INDEX    30
#define TX_NORMAL_DESC3_CTXT_WIDTH    1
#define TX_NORMAL_DESC3_FD_INDEX    29
#define TX_NORMAL_DESC3_FD_WIDTH    1
#define TX_NORMAL_DESC3_FL_INDEX    0
#define TX_NORMAL_DESC3_FL_WIDTH    15
#define TX_NORMAL_DESC3_LD_INDEX    28
#define TX_NORMAL_DESC3_LD_WIDTH    1
#define TX_NORMAL_DESC3_OWN_INDEX   31
#define TX_NORMAL_DESC3_OWN_WIDTH   1
#define TX_NORMAL_DESC3_TCPHDRLEN_INDEX   19
#define TX_NORMAL_DESC3_TCPHDRLEN_WIDTH   4
#define TX_NORMAL_DESC3_TCPPL_INDEX   0
#define TX_NORMAL_DESC3_TCPPL_WIDTH   18
#define TX_NORMAL_DESC3_TSE_INDEX   18
#define TX_NORMAL_DESC3_TSE_WIDTH   1

/* Enable or disable autonegotiation.  If this is set to enable,
 * the forced link modes above are completely ignored.
 */
#define AUTONEG_DISABLE   0x00
#define AUTONEG_ENABLE    0x01

/* The forced speed, 10Mb, 100Mb, gigabit, 2.5Gb, 10GbE. */
#define SPEED_10    10
#define SPEED_100   100
#define SPEED_1000    1000
#define SPEED_2500    2500
#define SPEED_10000   10000
#define SPEED_UNKNOWN   -1

/* Helper macros for handling FLOW control in HW */
#define XGMAC_FLOW_CTRL_OFF   0x00
#define XGMAC_FLOW_CTRL_RX    0x01
#define XGMAC_FLOW_CTRL_TX    0x02
#define XGMAC_FLOW_CTRL_TX_RX   (XGMAC_FLOW_CTRL_TX | \
           XGMAC_FLOW_CTRL_RX)

/* TX and RX PBL operations */
#define XGMAC_PBL_1     1
#define XGMAC_PBL_2     2
#define XGMAC_PBL_4     4
#define XGMAC_PBL_8     8
#define XGMAC_PBL_16      16
#define XGMAC_PBL_32      32
#define XGMAC_PBL_64      64  /* 8 x 8 */
#define XGMAC_PBL_128     128 /* 8 x 16 */
#define XGMAC_PBL_256     256 /* 8 x 32 */

/* RX THRESHOLD operations */
#define XGMAC_RX_THRESHOLD_32   0x01
#define XGMAC_RX_THRESHOLD_64   0x00
#define XGMAC_RX_THRESHOLD_96   0x02
#define XGMAC_RX_THRESHOLD_128    0x03

/* TX THRESHOLD operations */
#define XGMAC_TX_THRESHOLD_32   0x01
#define XGMAC_TX_THRESHOLD_64   0x00
#define XGMAC_TX_THRESHOLD_96   0x02
#define XGMAC_TX_THRESHOLD_128    0x03
#define XGMAC_TX_THRESHOLD_192    0x04
#define XGMAC_TX_THRESHOLD_256    0x05
#define XGMAC_TX_THRESHOLD_384    0x06
#define XGMAC_TX_THRESHOLD_512    0x07

/* TX and RX Store and Forward Mode operations */
#define XGMAC_RSF_DISABLE   0x00
#define XGMAC_RSF_ENABLE    0x01
#define XGMAC_TSF_DISABLE   0x00
#define XGMAC_TSF_ENABLE    0x01

#define MAC_HWF0R     0x011c
#define MAC_HWF1R     0x0120
#define MAC_HWF2R     0x0124

#define MAC_HWF0R_ADDMACADRSEL_INDEX  18
#define MAC_HWF0R_ADDMACADRSEL_WIDTH  5
#define MAC_HWF0R_ARPOFFSEL_INDEX 9
#define MAC_HWF0R_ARPOFFSEL_WIDTH 1
#define MAC_HWF0R_EEESEL_INDEX    13
#define MAC_HWF0R_EEESEL_WIDTH    1
#define MAC_HWF0R_GMIISEL_INDEX   1
#define MAC_HWF0R_GMIISEL_WIDTH   1
#define MAC_HWF0R_MGKSEL_INDEX    7
#define MAC_HWF0R_MGKSEL_WIDTH    1
#define MAC_HWF0R_MMCSEL_INDEX    8
#define MAC_HWF0R_MMCSEL_WIDTH    1
#define MAC_HWF0R_RWKSEL_INDEX    6
#define MAC_HWF0R_RWKSEL_WIDTH    1
#define MAC_HWF0R_RXCOESEL_INDEX  16
#define MAC_HWF0R_RXCOESEL_WIDTH  1
#define MAC_HWF0R_SAVLANINS_INDEX 27
#define MAC_HWF0R_SAVLANINS_WIDTH 1
#define MAC_HWF0R_SMASEL_INDEX    5
#define MAC_HWF0R_SMASEL_WIDTH    1
#define MAC_HWF0R_TSSEL_INDEX   12
#define MAC_HWF0R_TSSEL_WIDTH   1
#define MAC_HWF0R_TSSTSSEL_INDEX  25
#define MAC_HWF0R_TSSTSSEL_WIDTH  2
#define MAC_HWF0R_TXCOESEL_INDEX  14
#define MAC_HWF0R_TXCOESEL_WIDTH  1
#define MAC_HWF0R_VLHASH_INDEX    4
#define MAC_HWF0R_VLHASH_WIDTH    1
#define MAC_HWF1R_ADDR64_INDEX    14
#define MAC_HWF1R_ADDR64_WIDTH    2
#define MAC_HWF1R_ADVTHWORD_INDEX 13
#define MAC_HWF1R_ADVTHWORD_WIDTH 1
#define MAC_HWF1R_DBGMEMA_INDEX   19
#define MAC_HWF1R_DBGMEMA_WIDTH   1
#define MAC_HWF1R_DCBEN_INDEX   16
#define MAC_HWF1R_DCBEN_WIDTH   1
#define MAC_HWF1R_HASHTBLSZ_INDEX 24
#define MAC_HWF1R_HASHTBLSZ_WIDTH 3
#define MAC_HWF1R_L3L4FNUM_INDEX  27
#define MAC_HWF1R_L3L4FNUM_WIDTH  4
#define MAC_HWF1R_NUMTC_INDEX    21
#define MAC_HWF1R_NUMTC_WIDTH    3
#define MAC_HWF1R_RSSEN_INDEX   20
#define MAC_HWF1R_RSSEN_WIDTH   1
#define MAC_HWF1R_RXFIFOSIZE_INDEX  0
#define MAC_HWF1R_RXFIFOSIZE_WIDTH  5
#define MAC_HWF1R_SPHEN_INDEX   17
#define MAC_HWF1R_SPHEN_WIDTH   1
#define MAC_HWF1R_TSOEN_INDEX   18
#define MAC_HWF1R_TSOEN_WIDTH   1
#define MAC_HWF1R_TXFIFOSIZE_INDEX  6
#define MAC_HWF1R_TXFIFOSIZE_WIDTH  5
#define MAC_HWF2R_AUXSNAPNUM_INDEX  28
#define MAC_HWF2R_AUXSNAPNUM_WIDTH  3
#define MAC_HWF2R_PPSOUTNUM_INDEX 24
#define MAC_HWF2R_PPSOUTNUM_WIDTH 3
#define MAC_HWF2R_RXCHCNT_INDEX   12
#define MAC_HWF2R_RXCHCNT_WIDTH   4
#define MAC_HWF2R_RXQCNT_INDEX    0
#define MAC_HWF2R_RXQCNT_WIDTH    4
#define MAC_HWF2R_TXCHCNT_INDEX   18
#define MAC_HWF2R_TXCHCNT_WIDTH   4
#define MAC_HWF2R_TXQCNT_INDEX    6
#define MAC_HWF2R_TXQCNT_WIDTH    4
#define MAC_ISR_MMCRXIS_INDEX   9
#define MAC_ISR_MMCRXIS_WIDTH   1
#define MAC_ISR_MMCTXIS_INDEX   10
#define MAC_ISR_MMCTXIS_WIDTH   1
#define MAC_ISR_PMTIS_INDEX   4
#define MAC_ISR_PMTIS_WIDTH   1
#define MAC_MACA1HR_AE_INDEX    31
#define MAC_MACA1HR_AE_WIDTH    1
#define MAC_PFR_HMC_INDEX   2
#define MAC_PFR_HMC_WIDTH   1
#define MAC_PFR_HUC_INDEX   1
#define MAC_PFR_HUC_WIDTH   1
#define MAC_PFR_PM_INDEX    4
#define MAC_PFR_PM_WIDTH    1
#define MAC_PFR_PR_INDEX    0
#define MAC_PFR_PR_WIDTH    1
#define MAC_PMTCSR_MGKPKTEN_INDEX 1
#define MAC_PMTCSR_MGKPKTEN_WIDTH 1
#define MAC_PMTCSR_PWRDWN_INDEX   0
#define MAC_PMTCSR_PWRDWN_WIDTH   1
#define MAC_PMTCSR_RWKFILTRST_INDEX 31
#define MAC_PMTCSR_RWKFILTRST_WIDTH 1
#define MAC_PMTCSR_RWKPKTEN_INDEX 2
#define MAC_PMTCSR_RWKPKTEN_WIDTH 1
#define MAC_Q0TFCR_PT_INDEX   16
#define MAC_Q0TFCR_PT_WIDTH   16
#define MAC_Q0TFCR_TFE_INDEX    1
#define MAC_Q0TFCR_TFE_WIDTH    1
#define MAC_RCR_ACS_INDEX   1
#define MAC_RCR_ACS_WIDTH   1
#define MAC_RCR_CST_INDEX   2
#define MAC_RCR_CST_WIDTH   1
#define MAC_RCR_DCRCC_INDEX   3
#define MAC_RCR_DCRCC_WIDTH   1
#define MAC_RCR_IPC_INDEX   9
#define MAC_RCR_IPC_WIDTH   1
#define MAC_RCR_JE_INDEX    8
#define MAC_RCR_JE_WIDTH    1
#define MAC_RCR_LM_INDEX    10
#define MAC_RCR_LM_WIDTH    1
#define MAC_RCR_RE_INDEX    0
#define MAC_RCR_RE_WIDTH    1
#define MAC_RFCR_RFE_INDEX    0
#define MAC_RFCR_RFE_WIDTH    1
#define MAC_RQC0R_RXQ0EN_INDEX    0
#define MAC_RQC0R_RXQ0EN_WIDTH    2
#define MAC_TCR_SS_INDEX    29
#define MAC_TCR_SS_WIDTH    2
#define MAC_TCR_TE_INDEX    0
#define MAC_TCR_TE_WIDTH    1
#define MAC_VLANTR_DOVLTC_INDEX   20
#define MAC_VLANTR_DOVLTC_WIDTH   1
#define MAC_VLANTR_ERSVLM_INDEX   19
#define MAC_VLANTR_ERSVLM_WIDTH   1
#define MAC_VLANTR_ESVL_INDEX   18
#define MAC_VLANTR_ESVL_WIDTH   1
#define MAC_VLANTR_EVLS_INDEX   21
#define MAC_VLANTR_EVLS_WIDTH   2
#define MAC_VLANTR_EVLRXS_INDEX   24
#define MAC_VLANTR_EVLRXS_WIDTH   1

/* MTL queue register offsets
 *   Multiple queues can be active.  The first queue has registers
 *   that begin at 0x1100.  Each subsequent queue has registers that
 *   are accessed using an offset of 0x80 from the previous queue.
 */
#define MTL_Q_BASE      0x1100
#define MTL_Q_INC     0x80

#define MTL_Q_TQOMR     0x00
#define MTL_Q_TQUR      0x04
#define MTL_Q_TQDR      0x08
#define MTL_Q_TCECR     0x10
#define MTL_Q_TCESR     0x14
#define MTL_Q_TCQWR     0x18
#define MTL_Q_RQOMR     0x40
#define MTL_Q_RQMPOCR     0x44
#define MTL_Q_RQDR      0x4c
#define MTL_Q_IER     0x70
#define MTL_Q_ISR     0x74

/* MTL queue register entry bit positions and sizes */
#define MTL_Q_TCQWR_QW_INDEX    0
#define MTL_Q_TCQWR_QW_WIDTH    21
#define MTL_Q_RQOMR_EFHC_INDEX    7
#define MTL_Q_RQOMR_EFHC_WIDTH    1
#define MTL_Q_RQOMR_RFA_INDEX   8
#define MTL_Q_RQOMR_RFA_WIDTH   3
#define MTL_Q_RQOMR_RFD_INDEX   13
#define MTL_Q_RQOMR_RFD_WIDTH   3
#define MTL_Q_RQOMR_RQS_INDEX   16
#define MTL_Q_RQOMR_RQS_WIDTH   9
#define MTL_Q_RQOMR_RSF_INDEX   5
#define MTL_Q_RQOMR_RSF_WIDTH   1
#define MTL_Q_RQOMR_RTC_INDEX   0
#define MTL_Q_RQOMR_RTC_WIDTH   2
#define MTL_Q_TQOMR_FTQ_INDEX   0
#define MTL_Q_TQOMR_FTQ_WIDTH   1
#define MTL_Q_TQOMR_TQS_INDEX   16
#define MTL_Q_TQOMR_TQS_WIDTH   10
#define MTL_Q_TQOMR_TSF_INDEX   1
#define MTL_Q_TQOMR_TSF_WIDTH   1
#define MTL_Q_TQOMR_TTC_INDEX   4
#define MTL_Q_TQOMR_TTC_WIDTH   3
#define MTL_Q_TQOMR_TXQEN_INDEX   2
#define MTL_Q_TQOMR_TXQEN_WIDTH   2

/* MTL operation mode values */
#define XGMAC_MTL_ETSALG_WRR    0x0
#define XGMAC_MTL_ETSALG_WFQ    0x1
#define XGMAC_MTL_ETSALG_DWRR   0x2
#define XGMAC_MTL_RAA_SP    0x0
#define XGMAC_MTL_RAA_WSP   0x1
#define XGMAC_MTL_TSA_SP    0x00

/* DMA register offsets */
#define DMA_MR        0x3000
#define DMA_SBMR      0x3004
#define DMA_ISR       0x3008
#define DMA_AXIARCR     0x3010
#define DMA_AXIAWCR     0x3018
#define DMA_DSR0      0x3020
#define DMA_DSR1      0x3024
#define DMA_DSR2      0x3028
#define DMA_DSR3      0x302c
#define DMA_DSR4      0x3030

/* DMA register entry bit positions and sizes */
#define DMA_AXIARCR_DRC_INDEX   0
#define DMA_AXIARCR_DRC_WIDTH   4
#define DMA_AXIARCR_DRD_INDEX   4
#define DMA_AXIARCR_DRD_WIDTH   2
#define DMA_AXIARCR_TEC_INDEX   8
#define DMA_AXIARCR_TEC_WIDTH   4
#define DMA_AXIARCR_TED_INDEX   12
#define DMA_AXIARCR_TED_WIDTH   2
#define DMA_AXIARCR_THC_INDEX   16
#define DMA_AXIARCR_THC_WIDTH   4
#define DMA_AXIARCR_THD_INDEX   20
#define DMA_AXIARCR_THD_WIDTH   2
#define DMA_AXIAWCR_DWC_INDEX   0
#define DMA_AXIAWCR_DWC_WIDTH   4
#define DMA_AXIAWCR_DWD_INDEX   4
#define DMA_AXIAWCR_DWD_WIDTH   2
#define DMA_AXIAWCR_RPC_INDEX   8
#define DMA_AXIAWCR_RPC_WIDTH   4
#define DMA_AXIAWCR_RPD_INDEX   12
#define DMA_AXIAWCR_RPD_WIDTH   2
#define DMA_AXIAWCR_RHC_INDEX   16
#define DMA_AXIAWCR_RHC_WIDTH   4
#define DMA_AXIAWCR_RHD_INDEX   20
#define DMA_AXIAWCR_RHD_WIDTH   2
#define DMA_AXIAWCR_TDC_INDEX   24
#define DMA_AXIAWCR_TDC_WIDTH   4
#define DMA_AXIAWCR_TDD_INDEX   28
#define DMA_AXIAWCR_TDD_WIDTH   2
#define DMA_DSR0_RPS_INDEX    8
#define DMA_DSR0_RPS_WIDTH    4
#define DMA_DSR0_TPS_INDEX    12
#define DMA_DSR0_TPS_WIDTH    4
#define DMA_ISR_MACIS_INDEX   17
#define DMA_ISR_MACIS_WIDTH   1
#define DMA_ISR_MTLIS_INDEX   16
#define DMA_ISR_MTLIS_WIDTH   1
#define DMA_MR_SWR_INDEX    0
#define DMA_MR_SWR_WIDTH    1
#define DMA_SBMR_EAME_INDEX   11
#define DMA_SBMR_EAME_WIDTH   1
#define DMA_SBMR_UNDEF_INDEX    0
#define DMA_SBMR_UNDEF_WIDTH    1
#define DMA_SBMR_BLEN_256_INDEX   7
#define DMA_SBMR_BLEN_256_WIDTH   1

#define MAX_DMA_CHANNELS    16

/* Settings when cache enabled */
#define DMA_ARDOMAIN_SETTING_CE    0x2
#define DMA_ARCACHE_SETTING_CE   0xb
#define DMA_AWDOMAIN_SETTING_CE    0x2
#define DMA_AWCACHE_SETTING_CE   0xf
/* Settings when cache disabled */
#define DMA_ARDOMAIN_SETTING_CD    0x0
#define DMA_ARCACHE_SETTING_CD   0x2
#define DMA_AWDOMAIN_SETTING_CD    0x0
#define DMA_AWCACHE_SETTING_CD   0x2


/* MAC register offsets */
#define MAC_TCR       0x0000
#define MAC_RCR       0x0004
#define MAC_PFR       0x0008
#define MAC_WTR       0x000c
#define MAC_HTR0      0x0010
#define MAC_HTR1      0x0014
#define MAC_HTR2      0x0018
#define MAC_HTR3      0x001c
#define MAC_HTR4      0x0020
#define MAC_HTR5      0x0024
#define MAC_HTR6      0x0028
#define MAC_HTR7      0x002c
#define MAC_VLANTR      0x0050
#define MAC_VLANHTR     0x0058
#define MAC_VLANIR      0x0060
#define MAC_IVLANIR     0x0064
#define MAC_RETMR     0x006c
#define MAC_Q0TFCR      0x0070
#define MAC_RFCR      0x0090
#define MAC_RQC0R     0x00a0
#define MAC_RQC1R     0x00a4
#define MAC_RQC2R     0x00a8
#define MAC_RQC3R     0x00ac
#define MAC_ISR       0x00b0
#define MAC_IER       0x00b4
#define MAC_RTSR      0x00b8
#define MAC_PMTCSR      0x00c0
#define MAC_RWKPFR      0x00c4
#define MAC_LPICSR      0x00d0
#define MAC_LPITCR      0x00d4
#define MAC_VR        0x0110
#define MAC_DR        0x0114
#define MAC_HWF0R     0x011c
#define MAC_HWF1R     0x0120
#define MAC_HWF2R     0x0124
#define MAC_GPIOCR      0x0278
#define MAC_GPIOSR      0x027c
#define MAC_MACA0HR     0x0300
#define MAC_MACA0LR     0x0304
#define MAC_MACA1HR     0x0308
#define MAC_MACA1LR     0x030c

#define MAC_QTFCR_INC     4
#define MAC_MACA_INC      4

/* DMA channel register offsets
 *   Multiple channels can be active.  The first channel has registers
 *   that begin at 0x3100.  Each subsequent channel has registers that
 *   are accessed using an offset of 0x80 from the previous channel.
 */
#define DMA_CH_BASE     0x3100
#define DMA_CH_INC      0x80

#define DMA_CH_CR     0x00
#define DMA_CH_TCR      0x04
#define DMA_CH_RCR      0x08
#define DMA_CH_TDLR_HI      0x10
#define DMA_CH_TDLR_LO      0x14
#define DMA_CH_RDLR_HI      0x18
#define DMA_CH_RDLR_LO      0x1c
#define DMA_CH_TDTR_LO      0x24
#define DMA_CH_RDTR_LO      0x2c
#define DMA_CH_TDRLR      0x30
#define DMA_CH_RDRLR      0x34
#define DMA_CH_IER      0x38
#define DMA_CH_RIWT     0x3c
#define DMA_CH_CATDR_LO     0x44
#define DMA_CH_CARDR_LO     0x4c
#define DMA_CH_CATBR_HI     0x50
#define DMA_CH_CATBR_LO     0x54
#define DMA_CH_CARBR_HI     0x58
#define DMA_CH_CARBR_LO     0x5c
#define DMA_CH_SR     0x60

/* DMA channel register entry bit positions and sizes */
#define DMA_CH_CR_PBLX8_INDEX   16
#define DMA_CH_CR_PBLX8_WIDTH   1
#define DMA_CH_IER_AIE_INDEX    15
#define DMA_CH_IER_AIE_WIDTH    1
#define DMA_CH_IER_FBEE_INDEX   12
#define DMA_CH_IER_FBEE_WIDTH   1
#define DMA_CH_IER_NIE_INDEX    16
#define DMA_CH_IER_NIE_WIDTH    1
#define DMA_CH_IER_RBUE_INDEX   7
#define DMA_CH_IER_RBUE_WIDTH   1
#define DMA_CH_IER_RIE_INDEX    6
#define DMA_CH_IER_RIE_WIDTH    1
#define DMA_CH_IER_RSE_INDEX    8
#define DMA_CH_IER_RSE_WIDTH    1
#define DMA_CH_IER_TBUE_INDEX   2
#define DMA_CH_IER_TBUE_WIDTH   1
#define DMA_CH_IER_TIE_INDEX    0
#define DMA_CH_IER_TIE_WIDTH    1
#define DMA_CH_IER_TXSE_INDEX   1
#define DMA_CH_IER_TXSE_WIDTH   1
#define DMA_CH_RCR_PBL_INDEX    16
#define DMA_CH_RCR_PBL_WIDTH    6
#define DMA_CH_RCR_RBSZ_INDEX   1
#define DMA_CH_RCR_RBSZ_WIDTH   14
#define DMA_CH_RCR_SR_INDEX   0
#define DMA_CH_RCR_SR_WIDTH   1
#define DMA_CH_RIWT_RWT_INDEX   0
#define DMA_CH_RIWT_RWT_WIDTH   8
#define DMA_CH_SR_FBE_INDEX   12
#define DMA_CH_SR_FBE_WIDTH   1
#define DMA_CH_SR_RBU_INDEX   7
#define DMA_CH_SR_RBU_WIDTH   1
#define DMA_CH_SR_RI_INDEX    6
#define DMA_CH_SR_RI_WIDTH    1
#define DMA_CH_SR_RPS_INDEX   8
#define DMA_CH_SR_RPS_WIDTH   1
#define DMA_CH_SR_TBU_INDEX   2
#define DMA_CH_SR_TBU_WIDTH   1
#define DMA_CH_SR_TI_INDEX    0
#define DMA_CH_SR_TI_WIDTH    1
#define DMA_CH_SR_TPS_INDEX   1
#define DMA_CH_SR_TPS_WIDTH   1
#define DMA_CH_TCR_OSP_INDEX    4
#define DMA_CH_TCR_OSP_WIDTH    1
#define DMA_CH_TCR_PBL_INDEX    16
#define DMA_CH_TCR_PBL_WIDTH    6
#define DMA_CH_TCR_ST_INDEX   0
#define DMA_CH_TCR_ST_WIDTH   1
#define DMA_CH_TCR_TSE_INDEX    12
#define DMA_CH_TCR_TSE_WIDTH    1

#define RX_NORMAL_DESC3_ES_INDEX    15
#define RX_NORMAL_DESC3_ES_WIDTH    1
#define RX_NORMAL_DESC3_ETLT_INDEX    16
#define RX_NORMAL_DESC3_ETLT_WIDTH    4
#define RX_NORMAL_DESC3_INTE_INDEX    30
#define RX_NORMAL_DESC3_INTE_WIDTH    1
#define RX_NORMAL_DESC3_OWN_INDEX   31
#define RX_NORMAL_DESC3_OWN_WIDTH   1
#define RX_NORMAL_DESC3_PL_INDEX    0
#define RX_NORMAL_DESC3_PL_WIDTH    14

/* MTL register offsets */
#define MTL_OMR       0x1000
#define MTL_FDCR      0x1008
#define MTL_FDSR      0x100c
#define MTL_FDDR      0x1010
#define MTL_ISR       0x1020
#define MTL_RQDCM0R     0x1030
#define MTL_TCPM0R      0x1040
#define MTL_TCPM1R      0x1044
#define MTL_TC_ETSCR    0x10

#define MTL_RQDCM_INC     4
#define MTL_RQDCM_Q_PER_REG   4

/* MTL register entry bit positions and sizes */
#define MTL_OMR_ETSALG_INDEX    5
#define MTL_OMR_ETSALG_WIDTH    2
#define MTL_OMR_RAA_INDEX   2
#define MTL_OMR_RAA_WIDTH   1
#define MTL_TC_ETSCR_TSA_INDEX    0
#define MTL_TC_ETSCR_TSA_WIDTH    2

#define MTL_Q_DISABLED      0x00
#define MTL_Q_ENABLED     0x02

/* MMC register offsets */
#define MMC_CR        0x0800
#define MMC_RISR      0x0804
#define MMC_TISR      0x0808
#define MMC_RIER      0x080c
#define MMC_TIER      0x0810
#define MMC_TXOCTETCOUNT_GB_LO    0x0814
#define MMC_TXOCTETCOUNT_GB_HI    0x0818
#define MMC_TXFRAMECOUNT_GB_LO    0x081c
#define MMC_TXFRAMECOUNT_GB_HI    0x0820
#define MMC_TXBROADCASTFRAMES_G_LO  0x0824
#define MMC_TXBROADCASTFRAMES_G_HI  0x0828
#define MMC_TXMULTICASTFRAMES_G_LO  0x082c
#define MMC_TXMULTICASTFRAMES_G_HI  0x0830
#define MMC_TX64OCTETS_GB_LO    0x0834
#define MMC_TX64OCTETS_GB_HI    0x0838
#define MMC_TX65TO127OCTETS_GB_LO 0x083c
#define MMC_TX65TO127OCTETS_GB_HI 0x0840
#define MMC_TX128TO255OCTETS_GB_LO  0x0844
#define MMC_TX128TO255OCTETS_GB_HI  0x0848
#define MMC_TX256TO511OCTETS_GB_LO  0x084c
#define MMC_TX256TO511OCTETS_GB_HI  0x0850
#define MMC_TX512TO1023OCTETS_GB_LO 0x0854
#define MMC_TX512TO1023OCTETS_GB_HI 0x0858
#define MMC_TX1024TOMAXOCTETS_GB_LO 0x085c
#define MMC_TX1024TOMAXOCTETS_GB_HI 0x0860
#define MMC_TXUNICASTFRAMES_GB_LO 0x0864
#define MMC_TXUNICASTFRAMES_GB_HI 0x0868
#define MMC_TXMULTICASTFRAMES_GB_LO 0x086c
#define MMC_TXMULTICASTFRAMES_GB_HI 0x0870
#define MMC_TXBROADCASTFRAMES_GB_LO 0x0874
#define MMC_TXBROADCASTFRAMES_GB_HI 0x0878
#define MMC_TXUNDERFLOWERROR_LO   0x087c
#define MMC_TXUNDERFLOWERROR_HI   0x0880
#define MMC_TXOCTETCOUNT_G_LO   0x0884
#define MMC_TXOCTETCOUNT_G_HI   0x0888
#define MMC_TXFRAMECOUNT_G_LO   0x088c
#define MMC_TXFRAMECOUNT_G_HI   0x0890
#define MMC_TXPAUSEFRAMES_LO    0x0894
#define MMC_TXPAUSEFRAMES_HI    0x0898
#define MMC_TXVLANFRAMES_G_LO   0x089c
#define MMC_TXVLANFRAMES_G_HI   0x08a0
#define MMC_RXFRAMECOUNT_GB_LO    0x0900
#define MMC_RXFRAMECOUNT_GB_HI    0x0904
#define MMC_RXOCTETCOUNT_GB_LO    0x0908
#define MMC_RXOCTETCOUNT_GB_HI    0x090c
#define MMC_RXOCTETCOUNT_G_LO   0x0910
#define MMC_RXOCTETCOUNT_G_HI   0x0914
#define MMC_RXBROADCASTFRAMES_G_LO  0x0918
#define MMC_RXBROADCASTFRAMES_G_HI  0x091c
#define MMC_RXMULTICASTFRAMES_G_LO  0x0920
#define MMC_RXMULTICASTFRAMES_G_HI  0x0924
#define MMC_RXCRCERROR_LO   0x0928
#define MMC_RXCRCERROR_HI   0x092c
#define MMC_RXRUNTERROR     0x0930
#define MMC_RXJABBERERROR   0x0934
#define MMC_RXUNDERSIZE_G   0x0938
#define MMC_RXOVERSIZE_G    0x093c
#define MMC_RX64OCTETS_GB_LO    0x0940
#define MMC_RX64OCTETS_GB_HI    0x0944
#define MMC_RX65TO127OCTETS_GB_LO 0x0948
#define MMC_RX65TO127OCTETS_GB_HI 0x094c
#define MMC_RX128TO255OCTETS_GB_LO  0x0950
#define MMC_RX128TO255OCTETS_GB_HI  0x0954
#define MMC_RX256TO511OCTETS_GB_LO  0x0958
#define MMC_RX256TO511OCTETS_GB_HI  0x095c
#define MMC_RX512TO1023OCTETS_GB_LO 0x0960
#define MMC_RX512TO1023OCTETS_GB_HI 0x0964
#define MMC_RX1024TOMAXOCTETS_GB_LO 0x0968
#define MMC_RX1024TOMAXOCTETS_GB_HI 0x096c
#define MMC_RXUNICASTFRAMES_G_LO  0x0970
#define MMC_RXUNICASTFRAMES_G_HI  0x0974
#define MMC_RXLENGTHERROR_LO    0x0978
#define MMC_RXLENGTHERROR_HI    0x097c
#define MMC_RXOUTOFRANGETYPE_LO   0x0980
#define MMC_RXOUTOFRANGETYPE_HI   0x0984
#define MMC_RXPAUSEFRAMES_LO    0x0988
#define MMC_RXPAUSEFRAMES_HI    0x098c
#define MMC_RXFIFOOVERFLOW_LO   0x0990
#define MMC_RXFIFOOVERFLOW_HI   0x0994
#define MMC_RXVLANFRAMES_GB_LO    0x0998
#define MMC_RXVLANFRAMES_GB_HI    0x099c
#define MMC_RXWATCHDOGERROR   0x09a0

/* MMC register entry bit positions and sizes */
#define MMC_CR_CR_INDEX       0
#define MMC_CR_CR_WIDTH       1
#define MMC_CR_CSR_INDEX      1
#define MMC_CR_CSR_WIDTH      1
#define MMC_CR_ROR_INDEX      2
#define MMC_CR_ROR_WIDTH      1
#define MMC_CR_MCF_INDEX      3
#define MMC_CR_MCF_WIDTH      1
#define MMC_CR_MCT_INDEX      4
#define MMC_CR_MCT_WIDTH      2
#define MMC_RIER_ALL_INTERRUPTS_INDEX   0
#define MMC_RIER_ALL_INTERRUPTS_WIDTH   23
#define MMC_RISR_RXFRAMECOUNT_GB_INDEX    0
#define MMC_RISR_RXFRAMECOUNT_GB_WIDTH    1
#define MMC_RISR_RXOCTETCOUNT_GB_INDEX    1
#define MMC_RISR_RXOCTETCOUNT_GB_WIDTH    1
#define MMC_RISR_RXOCTETCOUNT_G_INDEX   2
#define MMC_RISR_RXOCTETCOUNT_G_WIDTH   1
#define MMC_RISR_RXBROADCASTFRAMES_G_INDEX  3
#define MMC_RISR_RXBROADCASTFRAMES_G_WIDTH  1
#define MMC_RISR_RXMULTICASTFRAMES_G_INDEX  4
#define MMC_RISR_RXMULTICASTFRAMES_G_WIDTH  1
#define MMC_RISR_RXCRCERROR_INDEX   5
#define MMC_RISR_RXCRCERROR_WIDTH   1
#define MMC_RISR_RXRUNTERROR_INDEX    6
#define MMC_RISR_RXRUNTERROR_WIDTH    1
#define MMC_RISR_RXJABBERERROR_INDEX    7
#define MMC_RISR_RXJABBERERROR_WIDTH    1
#define MMC_RISR_RXUNDERSIZE_G_INDEX    8
#define MMC_RISR_RXUNDERSIZE_G_WIDTH    1
#define MMC_RISR_RXOVERSIZE_G_INDEX   9
#define MMC_RISR_RXOVERSIZE_G_WIDTH   1
#define MMC_RISR_RX64OCTETS_GB_INDEX    10
#define MMC_RISR_RX64OCTETS_GB_WIDTH    1
#define MMC_RISR_RX65TO127OCTETS_GB_INDEX 11
#define MMC_RISR_RX65TO127OCTETS_GB_WIDTH 1
#define MMC_RISR_RX128TO255OCTETS_GB_INDEX  12
#define MMC_RISR_RX128TO255OCTETS_GB_WIDTH  1
#define MMC_RISR_RX256TO511OCTETS_GB_INDEX  13
#define MMC_RISR_RX256TO511OCTETS_GB_WIDTH  1
#define MMC_RISR_RX512TO1023OCTETS_GB_INDEX 14
#define MMC_RISR_RX512TO1023OCTETS_GB_WIDTH 1
#define MMC_RISR_RX1024TOMAXOCTETS_GB_INDEX 15
#define MMC_RISR_RX1024TOMAXOCTETS_GB_WIDTH 1
#define MMC_RISR_RXUNICASTFRAMES_G_INDEX  16
#define MMC_RISR_RXUNICASTFRAMES_G_WIDTH  1
#define MMC_RISR_RXLENGTHERROR_INDEX    17
#define MMC_RISR_RXLENGTHERROR_WIDTH    1
#define MMC_RISR_RXOUTOFRANGETYPE_INDEX   18
#define MMC_RISR_RXOUTOFRANGETYPE_WIDTH   1
#define MMC_RISR_RXPAUSEFRAMES_INDEX    19
#define MMC_RISR_RXPAUSEFRAMES_WIDTH    1
#define MMC_RISR_RXFIFOOVERFLOW_INDEX   20
#define MMC_RISR_RXFIFOOVERFLOW_WIDTH   1
#define MMC_RISR_RXVLANFRAMES_GB_INDEX    21
#define MMC_RISR_RXVLANFRAMES_GB_WIDTH    1
#define MMC_RISR_RXWATCHDOGERROR_INDEX    22
#define MMC_RISR_RXWATCHDOGERROR_WIDTH    1
#define MMC_TIER_ALL_INTERRUPTS_INDEX   0
#define MMC_TIER_ALL_INTERRUPTS_WIDTH   18
#define MMC_TISR_TXOCTETCOUNT_GB_INDEX    0
#define MMC_TISR_TXOCTETCOUNT_GB_WIDTH    1
#define MMC_TISR_TXFRAMECOUNT_GB_INDEX    1
#define MMC_TISR_TXFRAMECOUNT_GB_WIDTH    1
#define MMC_TISR_TXBROADCASTFRAMES_G_INDEX  2
#define MMC_TISR_TXBROADCASTFRAMES_G_WIDTH  1
#define MMC_TISR_TXMULTICASTFRAMES_G_INDEX  3
#define MMC_TISR_TXMULTICASTFRAMES_G_WIDTH  1
#define MMC_TISR_TX64OCTETS_GB_INDEX    4
#define MMC_TISR_TX64OCTETS_GB_WIDTH    1
#define MMC_TISR_TX65TO127OCTETS_GB_INDEX 5
#define MMC_TISR_TX65TO127OCTETS_GB_WIDTH 1
#define MMC_TISR_TX128TO255OCTETS_GB_INDEX  6
#define MMC_TISR_TX128TO255OCTETS_GB_WIDTH  1
#define MMC_TISR_TX256TO511OCTETS_GB_INDEX  7
#define MMC_TISR_TX256TO511OCTETS_GB_WIDTH  1
#define MMC_TISR_TX512TO1023OCTETS_GB_INDEX 8
#define MMC_TISR_TX512TO1023OCTETS_GB_WIDTH 1
#define MMC_TISR_TX1024TOMAXOCTETS_GB_INDEX 9
#define MMC_TISR_TX1024TOMAXOCTETS_GB_WIDTH 1
#define MMC_TISR_TXUNICASTFRAMES_GB_INDEX 10
#define MMC_TISR_TXUNICASTFRAMES_GB_WIDTH 1
#define MMC_TISR_TXMULTICASTFRAMES_GB_INDEX 11
#define MMC_TISR_TXMULTICASTFRAMES_GB_WIDTH 1
#define MMC_TISR_TXBROADCASTFRAMES_GB_INDEX 12
#define MMC_TISR_TXBROADCASTFRAMES_GB_WIDTH 1
#define MMC_TISR_TXUNDERFLOWERROR_INDEX   13
#define MMC_TISR_TXUNDERFLOWERROR_WIDTH   1
#define MMC_TISR_TXOCTETCOUNT_G_INDEX   14
#define MMC_TISR_TXOCTETCOUNT_G_WIDTH   1
#define MMC_TISR_TXFRAMECOUNT_G_INDEX   15
#define MMC_TISR_TXFRAMECOUNT_G_WIDTH   1
#define MMC_TISR_TXPAUSEFRAMES_INDEX    16
#define MMC_TISR_TXPAUSEFRAMES_WIDTH    1
#define MMC_TISR_TXVLANFRAMES_G_INDEX   17
#define MMC_TISR_TXVLANFRAMES_G_WIDTH   1

//struct xgbe_prv_data;


  /// XGMac Hardware Features
  typedef struct _xgmac_hw_features {
    UINT32 version;         ///< version
    // HW Feature Register0
    UINT32 gmii;            ///< 1000 Mbps support
    UINT32 vlhash;          ///< VLAN Hash Filter
    UINT32 sma;             ///< SMA(MDIO) Interface
    UINT32 rwk;             ///< PMT remote wake-up packet
    UINT32 mgk;             ///< PMT magic packet
    UINT32 mmc;             ///< RMON module
    UINT32 aoe;             ///< ARP Offload
    UINT32 ts;              ///< IEEE 1588-2008 Adavanced Timestamp
    UINT32 eee;             ///< Energy Efficient Ethernet
    UINT32 tx_coe;          ///< Tx Checksum Offload
    UINT32 rx_coe;          ///< Rx Checksum Offload
    UINT32 addn_mac;        ///< Additional MAC Addresses
    UINT32 ts_src;          ///< Timestamp Source
    UINT32 sa_vlan_ins;     ///< Source Address or VLAN Insertion

    // HW Feature Register1
    UINT32 rx_fifo_size;    ///< MTL Receive FIFO Size
    UINT32 tx_fifo_size;    ///< MTL Transmit FIFO Size
    UINT32 adv_ts_hi;       ///< Advance Timestamping High Word
    UINT32 dma_width;        ///< DMA width
    UINT32 dcb;             ///< DCB Feature
    UINT32 sph;             ///< Split Header Feature
    UINT32 tso;             ///< TCP Segmentation Offload
    UINT32 dma_debug;       ///< DMA Debug Registers
    UINT32 rss;             ///< Receive Side Scaling
    UINT32 tc_cnt;          ///< Number of Traffic Classes
    UINT32 hash_table_size; ///< Hash Table Size
    UINT32 l3l4_filter_num; ///< Number of L3-L4 Filters

    // HW Feature Register2
    UINT32 rx_q_cnt;        ///< Number of MTL Receive Queues
    UINT32 tx_q_cnt;        ///< Number of MTL Transmit Queues
    UINT32 rx_ch_cnt;       ///< Number of DMA Receive Channels
    UINT32 tx_ch_cnt;       ///< Number of DMA Transmit Channels
    UINT32 pps_out_num;     ///< Number of PPS outputs
    UINT32 aux_snap_num;    ///< Number of Aux snapshot inputs
  } xgmac_hw_features;

  /// XGMac MTL FIFO Size
  typedef enum {
    XGMAC_MTL_FIFO_SIZE_256  = 0x00,   ///< 256 Byte FIFO size
    XGMAC_MTL_FIFO_SIZE_512  = 0x01,   ///< 512 Byte FIFO size
    XGMAC_MTL_FIFO_SIZE_1K   = 0x03,   ///< 1K Byte FIFO size
    XGMAC_MTL_FIFO_SIZE_2K   = 0x07,   ///< 2K Byte FIFO size
    XGMAC_MTL_FIFO_SIZE_4K   = 0x0f,   ///< 4K Byte FIFO size
    XGMAC_MTL_FIFO_SIZE_8K   = 0x1f,   ///< 8K Byte FIFO size
    XGMAC_MTL_FIFO_SIZE_16K  = 0x3f,   ///< 16K Byte FIFO size
    XGMAC_MTL_FIFO_SIZE_32K  = 0x7f,   ///< 32K Byte FIFO size
    XGMAC_MTL_FIFO_SIZE_64K  = 0xff,   ///< 64K Byte FIFO size
    XGMAC_MTL_FIFO_SIZE_128K = 0x1ff,  ///< 128K Byte FIFO size
    XGMAC_MTL_FIFO_SIZE_256K = 0x3ff,  ///< 256K Byte FIFO size
  } xgmac_mtl_fifo_size;

  /// Interface Mode definitions
  typedef enum {
    PHY_INTERFACE_MODE_NA,             ///< PHY Interface Mode Not Applicable
    PHY_INTERFACE_MODE_MII,            ///< PHY Interface Mode MII
    PHY_INTERFACE_MODE_GMII,           ///< PHY Interface Mode GMII
    PHY_INTERFACE_MODE_SGMII,          ///< PHY Interface Mode SGMII
    PHY_INTERFACE_MODE_TBI,            ///< PHY Interface Mode TBI
    PHY_INTERFACE_MODE_REVMII,         ///< PHY Interface Mode REVMII
    PHY_INTERFACE_MODE_RMII,           ///< PHY Interface Mode RMII
    PHY_INTERFACE_MODE_RGMII,          ///< PHY Interface Mode RGII
    PHY_INTERFACE_MODE_RGMII_ID,       ///< PHY Interface Mode RGMII ID
    PHY_INTERFACE_MODE_RGMII_RXID,     ///< PHY Interface Mode RGMII RXID
    PHY_INTERFACE_MODE_RGMII_TXID,     ///< PHY Interface Mode RGMII TXID
    PHY_INTERFACE_MODE_RTBI,           ///< PHY Interface Mode RTBI
    PHY_INTERFACE_MODE_SMII,           ///< PHY Interface Mode SMII
    PHY_INTERFACE_MODE_XGMII,          ///< PHY Interface Mode XGMII
  } phy_interface_t;

  /// AN states
  typedef enum {
    RESTART_AN,         ///< Restart AN
    READ_LP,            ///< Read Link Partner abilities
    KR_TRAIN,           ///< KR training
    WAIT_INT_CMPLT,     ///< Wait INT Complete
    EXIT_AN_RUN         ///< Exit AN
  } AN_NEXT_STEP;


  struct xgbe_phy {
    UINT64 supported;
    UINT64 advertising;
    UINT32 lp_advertising;
    UINTN address;
    UINTN autoneg;
    UINTN speed;
    UINTN duplex;
    UINTN link;
    UINTN pause_autoneg;
    UINTN tx_pause;
    UINTN rx_pause;
  };

/* Structure used to describe the descriptor rings associated with
 * a DMA channel.
 */
  typedef struct _xgmac_prv_data xgmac_prv_data;

  /// XGMAC Channel Structure
  struct _xgmac_channel {
    UINTN dma_regs;                 ///< DMA Base Address

    /* Address of private data area for device */
    xgmac_prv_data *pdata;          ///< XGMac Private Data
  } ____cacheline_aligned;


  typedef struct _xgmac_channel xgmac_channel;


  /// XGMac Private Data
  typedef struct _xgmac_prv_data {
    UINT32 xgmac_regs;                ///< XGMAC Registers
    xgmac_hw_features hw_feat;       ///< XGMAC Hardware Features

    // Rings for Tx/Rx on a DMA channel
    xgmac_channel channel;           ///< XGMAC Channel Structure
    UINT32 tx_ring_count;            ///< Transmit Ring Count
    UINT32 tx_desc_count;            ///< Transmit Descriptor Count
    UINT32 rx_ring_count;            ///< Receive Ring Count
    UINT32 rx_desc_count;            ///< Receive Descriptor Count

    // Tx/Rx common settings
    UINT32 pblx8;                    ///< PBL by 8

    // Tx settings
    UINT32 tx_sf_mode;               ///< Transmit SF Mode
    UINT32 tx_threshold;             ///< Transmit Threshold
    UINT32 tx_pbl;                   ///< Transmit PBL
    UINT32 tx_osp_mode;              ///< Transmit OSP Mode

    // Rx settings
    UINT32 rx_sf_mode;               ///< Receive SF Mode
    UINT32 rx_threshold;             ///< Receive Threshold
    UINT32 rx_pbl;                   ///< Receive PBL

    // Rx coalescing settings
    UINT32 rx_use_riwt;              ///< Receive Use RIWT
    UINT32 rx_riwt;                  ///< Receive RIWT
    UINT32 rx_frames;                ///< Receive Frames

    // Current MTU
    UINT32 mtu;                      ///< MTU
    UINT32 rx_buf_size;              ///< Receive Buffer Size

    // Keeps track of previous options
    UINT32 flow_ctrl;                ///< Flow Control
    UINT32 oldflow_ctrl;             ///< Old Flow Control

    // Keeps track of power mode for API based PMT control
    UINT32 power_down;               ///< Power Down

    //phy_interface_t phy_interface;   ///< PHY Interface Structure
    //INT32 default_autoneg;           ///< Default Auto Negotiate
    //INT32 default_speed;             ///< Default Speed
  } xgmac_prv_data;

  EFI_STATUS
  XpcsSettleSpeed (
    ENET_DXE_PRIVATE_DATA *Private
    );

  EFI_STATUS
  xgbe_phy_start (
    ENET_DXE_PRIVATE_DATA *Private
    );

  EFI_STATUS
  xgbe_phy_stop (
    ENET_DXE_PRIVATE_DATA *Private
    );  

  EFI_STATUS
  xgbe_phy_reset (
    ENET_DXE_PRIVATE_DATA *Private
    );

  EFI_STATUS
  XgbePlatinit (
    ENET_DXE_PRIVATE_DATA *Private
    );

  EFI_STATUS
  xgbe_phy_init (
    ENET_DXE_PRIVATE_DATA *Private
    );

  UINT32
  FindSupportedDevice (
    IN       UINT32 XgmacBase
  );

  VOID
  DetectSfp (
    ENET_DXE_PRIVATE_DATA *Private
  );

 
  EFI_STATUS
  XgbeBaseAddr (
    OUT ENET_DXE_PRIVATE_DATA *Private
  );


  VOID
  XgmacInit (
    IN OUT ENET_DXE_PRIVATE_DATA *Private,
    IN     UINTN XgmacBase
  );
  
  VOID 
  xgbe_switch_mode(
	  ENET_DXE_PRIVATE_DATA *pdata
	  );

 
  VOID 
  xgbe_set_mode(
	ENET_DXE_PRIVATE_DATA *pdata,
	enum xgbe_mode mode
	);

  VOID
  xgmac_get_all_hw_features (
    IN  xgmac_prv_data *pdata
  );

  VOID xgmac_default_config (
    IN  xgmac_prv_data *pdata
  );

  EFI_STATUS
  xgmac_pre_xmit (
    IN  ENET_DXE_PRIVATE_DATA *Private,
    IN  VOID       *Buffer,
    IN  UINTN      BufferSize
  );

  EFI_STATUS
  xgmac_dev_read (
    IN  ENET_DXE_PRIVATE_DATA *Private,
    IN  VOID            *Buffer,
    IN  UINTN           *BufferSize
  );

  VOID
  UpdateLinkStatus (
    IN  ENET_DXE_PRIVATE_DATA *Private
  );

  VOID
  PlatformConInfo (
    IN ENET_DXE_PRIVATE_DATA *Private
  );

  VOID
  UpdateXgbeVersion (
    VOID
  );

  BOOLEAN
  xgbe_an_state_machine(
    IN  ENET_DXE_PRIVATE_DATA *Private
  );
  
  
  VOID XgbeHwinitDelay ( );

  STATIC VOID xgbe_an_disable (ENET_DXE_PRIVATE_DATA *pdata);
  STATIC VOID xgbe_phy_power_off (ENET_DXE_PRIVATE_DATA *pdata);
  VOID xgbe_sfp_mode (ENET_DXE_PRIVATE_DATA *pdata);
  UINTN xgbe_phy_get_comm_ownership ( ENET_DXE_PRIVATE_DATA *pdata );
  VOID xgbe_phy_put_comm_ownership ( ENET_DXE_PRIVATE_DATA *pdata );
  VOID xgmac_pcs_disable_kr_training ( UINTN XpcsBase);
  INT32 set_gmii_speed ( xgmac_prv_data *pdata);
  VOID xgbe_phy_sgmii_1000_mode (ENET_DXE_PRIVATE_DATA *pdata);
  VOID xgbe_phy_set_mode (ENET_DXE_PRIVATE_DATA *pdata,enum xgbe_mode mode);
  VOID xgbe_an37_init (ENET_DXE_PRIVATE_DATA *pdata,UINT32 XpcsBase);
  VOID xgbe_an37_enable_interrupts (UINTN XpcsBase);
  VOID xgbe_an37_set_EN_VSMMD1 (UINTN XpcsBase);
  VOID xgbe_phy_an_mode ( ENET_DXE_PRIVATE_DATA *pdata );
  EFI_STATUS XgbeSfpGetMux (ENET_DXE_PRIVATE_DATA *Private);
  EFI_STATUS XgbeSfpPutMux (ENET_DXE_PRIVATE_DATA *Private);

  UINT32 getBitfield (
  IN UINT32 Value,
  IN UINT32 Lsb,
  IN UINT32 Width
  );
  UINT32 getBitfieldReg32 (
  IN UINT32 Addr,
  IN UINT32 Lsb,
  IN UINT32 Width
  );
  
#endif//__SNP_DXE_XGBE_H__


