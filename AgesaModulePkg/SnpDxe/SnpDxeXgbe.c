/* $NoKeywords:$ */
/**
 * @file
 *
 * SnpDxeXgbe.c
 *
 * Contains Ethernet Phy Driver for the DXE phase.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: FDK
 * @e sub-project: UEFI
 * @e version: $Revision: 300489 $ @e date: $Date: 2014-08-08 14:36:46 -0700 (Fri, 08 Aug 2014) $
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
#include "SnpDxe.h"
#include "SnpDxeXgbe.h"
#include "mdio.h"
#include <AMD.h>
#include <Library/AmdBaseLib.h>
#include <Library/PcdLib.h>
#include <Library/PciLib.h>
#include <Protocol/FabricTopologyServices2.h>
#include <Protocol/Pca9535aProtocol.h>
#include <Protocol/Pca9545aProtocol.h>
//#include <Protocol/Sff8472Protocol.h>
#include <Protocol/xGbEI2cMaster.h>
//#include "Library/GnbCZLib/Module/GnpCommonLib/GnbLibPciAcc.h"

extern XGBE_PLATFORM_DATA  mXgbeData;
extern  EFI_BOOT_SERVICES       *gBS;

VOID STATIC xgbe_an73_restart (  UINT32 XpcsBase  );
VOID xgbe_an73_set (  UINT32 XpcsBase,  BOOLEAN enable,  BOOLEAN restart  );
VOID xgbe_an37_restart (  UINT32 XpcsBase  );
VOID STATIC xgbe_phy_rrc (   ENET_DXE_PRIVATE_DATA *pdata   );
VOID xgbe_an73_clear_interrupts (  UINTN XpcsBase  );
VOID xgbe_an_restart (   ENET_DXE_PRIVATE_DATA *pdata);
VOID xgbe_phy_power_off (   ENET_DXE_PRIVATE_DATA *pdata  );
UINTN STATIC xgbe_phy_mdio_reset (   ENET_DXE_PRIVATE_DATA *pdata   );
VOID STATIC xgbe_an_clear_interrupts (   ENET_DXE_PRIVATE_DATA *pdata   );
VOID STATIC xgbe_an73_disable_kr_training ( UINTN XpcsBase );


#define XGBE_PHY_PORT_SPEED_100      BIT0
#define XGBE_PHY_PORT_SPEED_1000     BIT1
#define XGBE_PHY_PORT_SPEED_2500     BIT2
#define XGBE_PHY_PORT_SPEED_10000    BIT3

STATIC UINT8 mCurrLanSpeed = 1;
STATIC UINT8 mLan0Speed = 0;
STATIC UINT8 mLan1Speed = 0;
STATIC UINT8 mLan2Speed = 0;
STATIC UINT8 mLan3Speed = 0;
UINTN OldIntVal = 0;
EFI_EVENT LinkStsTimerEvent = NULL;
/* SFP EEPROM Base ID values relative to an offset of 0 */
#define XGBE_SFP_BASE_ID              0
#define XGBE_SFP_ID_SFP               0x03

#define XGBE_SFP_BASE_EXT_ID          1
#define XGBE_SFP_EXT_ID_SFP           0x04

#define XGBE_SFP_BASE_10GBE_CC          3
#define XGBE_SFP_BASE_10GBE_CC_SR       BIT4
#define XGBE_SFP_BASE_10GBE_CC_LR       BIT5
#define XGBE_SFP_BASE_10GBE_CC_LRM      BIT6
#define XGBE_SFP_BASE_10GBE_CC_ER       BIT7

#define XGBE_SFP_BASE_1GBE_CC           6
#define XGBE_SFP_BASE_1GBE_CC_SX        BIT0
#define XGBE_SFP_BASE_1GBE_CC_LX        BIT1
#define XGBE_SFP_BASE_1GBE_CC_CX        BIT2
#define XGBE_SFP_BASE_1GBE_CC_T         BIT3

#define XGBE_SFP_BASE_CABLE             8
#define XGBE_SFP_BASE_CABLE_PASSIVE     BIT2
#define XGBE_SFP_BASE_CABLE_ACTIVE      BIT3
#define XGBE_SFP_BASE_BR                12
#define XGBE_SFP_BASE_BR_1GBE_MIN       0x0a
#define XGBE_SFP_BASE_BR_1GBE_MAX       0x0d
#define XGBE_SFP_BASE_BR_10GBE_MIN      0x64
#define XGBE_SFP_BASE_BR_10GBE_MAX      0x68

#define XGBE_SFP_BASE_CC                63

/* SFP Serial ID Extended ID values relative to an offset of 64 */
#define XGBE_SFP_BASE_VENDOR_SN			4
#define XGBE_SFP_BASE_VENDOR_SN_LEN		16

#define XGBE_SFP_EXTD_OPT1			        1
#define XGBE_SFP_EXTD_OPT1_RX_LOS		    BIT1
#define XGBE_SFP_EXTD_OPT1_TX_FAULT		    BIT3
#define XGBE_SFP_EXTD_OPT1_TX_DISABLE		BIT4
#define XGBE_SFP_EXTD_OPT1_RATE_SELECT		BIT5

#define XGBE_SFP_EXTD_DIAG			        28
#define XGBE_SFP_EXTD_DIAG_ADDR_CHANGE		BIT2

#define XGBE_SFP_EXTD_SFF_8472			    30

#define XGBE_SFP_EXTD_CC			        31

/* SFP sideband signal indicators */
#define XGBE_GPIO_NO_TX_FAULT		        BIT0
#define XGBE_GPIO_NO_RATE_SELECT	        BIT1
#define XGBE_GPIO_NO_MOD_ABSENT		        BIT2
#define XGBE_GPIO_NO_RX_LOS		            BIT3

/* Rate-change complete wait/retry count */
#define XGBE_RATECHANGE_COUNT           500

#define XGBE_MUTEX_RELEASE              0x80000000ul
#define XGBE_SFP_DIRECT                 7

#define XGBE_PHY_REDRV_MODE_REG         0x12b0
#define XGBE_ABORT_COUNT                500
#define XGBE_DISABLE_COUNT              1000
#define XGBE_INTR_RX_FULL               BIT2 //BIT(IC_RAW_INTR_STAT_RX_FULL_INDEX)
#define XGBE_INTR_TX_EMPTY              BIT4 //BIT(IC_RAW_INTR_STAT_TX_EMPTY_INDEX)
#define XGBE_INTR_TX_ABRT               BIT6 //BIT(IC_RAW_INTR_STAT_TX_ABRT_INDEX)
#define XGBE_INTR_STOP_DET              BIT9 //BIT(IC_RAW_INTR_STAT_STOP_DET_INDEX)
#define XGBE_DEFAULT_INT_MASK    (XGBE_INTR_RX_FULL  | \
                        XGBE_INTR_TX_EMPTY |  \
                        XGBE_INTR_TX_ABRT  |  \
                        XGBE_INTR_STOP_DET)
#define XGBE_SFP_BASE_CU_CABLE_LEN     18
#define DUPLE X_HALF                   0x00
#define DUPLEX_FULL                    0x01
#define DUPLEX_UNKNOWN                 0xff
#define MDIO_AN_ADVERTISE              16

#define XGBE_PMA_CDR_TRACK_EN_MASK	0x01
#define XGBE_PMA_CDR_TRACK_EN_OFF	0x00
#define XGBE_PMA_CDR_TRACK_EN_ON	0x01

#ifndef MDIO_VEND2_PMA_CDR_CONTROL
#define MDIO_VEND2_PMA_CDR_CONTROL	0x8056
#endif


/* CDR delay values for KR support (in usec) */
#define XGBE_CDR_DELAY_INIT		10000
#define XGBE_CDR_DELAY_INC		10000
#define XGBE_CDR_DELAY_MAX		100000

/*

B2 R1000 is creating timing issues with RJ45. We see this issue only with few PXe servers.
We see it works with stability with 100000 value.  We did not see much stable with 10000 and 20000 . 
Autoneg is completing without delay but transsation is not happening. 
We did not find any register from XGBE side to know weather xgmac is ready.
Ideally after AUTO neg we are good to start transfer packets. But almost altime issuee with R1000 and only 
first time with V1000. To consider all corner cases we included this delay for all chipsets.
*/
#define XGBE_DELAY_SILICON_LIMIT	    100000       /* 0.1 sec */

/* RRC frequency during link status check */
#define XGBE_RRC_FREQUENCY		10


/* Generic MDIO registers. */
#define MDIO_CTRL1		MII_BMCR
#define MDIO_STAT1		MII_BMSR
#define MDIO_DEVID1		MII_PHYSID1
#define MDIO_DEVID2		MII_PHYSID2
#define MDIO_SPEED		4	/* Speed ability */
#define MDIO_DEVS1		5	/* Devices in package */
#define MDIO_DEVS2		6
#define MDIO_CTRL2		7	/* 10G control 2 */
#define MDIO_STAT2		8	/* 10G status 2 */
#define MDIO_PMA_TXDIS		9	/* 10G PMA/PMD transmit disable */
#define MDIO_PMA_RXDET		10	/* 10G PMA/PMD receive signal detect */
#define MDIO_PMA_EXTABLE	11	/* 10G PMA/PMD extended ability */
#define MDIO_PKGID1		14	/* Package identifier */
#define MDIO_PKGID2		15
#define MDIO_AN_ADVERTISE	16	/* AN advertising (base page) */
#define MDIO_AN_LPA		19	/* AN LP abilities (base page) */
#define MDIO_PCS_EEE_ABLE	20	/* EEE Capability register */
#define MDIO_PCS_EEE_WK_ERR	22	/* EEE wake error counter */
#define MDIO_PHYXS_LNSTAT	24	/* PHY XGXS lane state */
#define MDIO_AN_EEE_ADV		60	/* EEE advertisement */
#define MDIO_AN_EEE_LPABLE	61	/* EEE link partner ability */

/* PMA 10GBASE-T TX power register. */
#define MDIO_PMA_10GBT_TXPWR_SHORT	0x0001	/* Short-reach mode */

/* PMA 10GBASE-T SNR registers. */
/* Value is SNR margin in dB, clamped to range [-127, 127], plus 0x8000. */
#define MDIO_PMA_10GBT_SNR_BIAS		0x8000
#define MDIO_PMA_10GBT_SNR_MAX		127

/* PMA 10GBASE-R FEC ability register. */
#define MDIO_PMA_10GBR_FECABLE_ABLE	0x0001	/* FEC ability */
#define MDIO_PMA_10GBR_FECABLE_ERRABLE	0x0002	/* FEC error indic. ability */

/* PCS 10GBASE-R/-T status register 1. */
#define MDIO_PCS_10GBRT_STAT1_BLKLK	0x0001	/* Block lock attained */

/* PCS 10GBASE-R/-T status register 2. */
#define MDIO_PCS_10GBRT_STAT2_ERR	0x00ff
#define MDIO_PCS_10GBRT_STAT2_BER	0x3f00

/* AN 10GBASE-T control register. */
#define MDIO_AN_10GBT_CTRL_ADV10G	0x1000	/* Advertise 10GBASE-T */

/* AN 10GBASE-T status register. */
#define MDIO_AN_10GBT_STAT_LPTRR	0x0200	/* LP training reset req. */
#define MDIO_AN_10GBT_STAT_LPLTABLE	0x0400	/* LP loop timing ability */
#define MDIO_AN_10GBT_STAT_LP10G	0x0800	/* LP is 10GBT capable */
#define MDIO_AN_10GBT_STAT_REMOK	0x1000	/* Remote OK */
#define MDIO_AN_10GBT_STAT_LOCOK	0x2000	/* Local OK */
#define MDIO_AN_10GBT_STAT_MS		0x4000	/* Master/slave config */
#define MDIO_AN_10GBT_STAT_MSFLT	0x8000	/* Master/slave config fault */

/* Auto-negotiation */
#define XGBE_AN_MS_TIMEOUT		500
#define XGBE_LINK_TIMEOUT		10



VOID xgbe_phy_set_mode (ENET_DXE_PRIVATE_DATA *pdata, enum xgbe_mode mode);
VOID STATIC xgbe_an73_disable (ENET_DXE_PRIVATE_DATA *pdata);
VOID STATIC xgbe_an37_disable (ENET_DXE_PRIVATE_DATA *pdata);
VOID STATIC xgbe_an37_set ( UINT32 XpcsBase, BOOLEAN enable, BOOLEAN restart);

VOID
STATIC
write_mmd_regs (
  IN       UINTN XpcsBase,
  IN       UINTN mmd_reg,
  IN       UINTN mmd_data
  );

EFI_STATUS
XgbeI2cCall (
 ENET_DXE_PRIVATE_DATA *Private
 );


UINT32
clearBitfield (
  IN UINT32 Value,
  IN UINT32 Lsb,
  IN UINT32 Width
  )
{
  UINT32 ClearMask;
  UINTN i;

  ClearMask = 0;
  for (i = 0; i < Width; i++) {
    ClearMask |= 1 << i;
  }
  return Value & ~(ClearMask << Lsb);
}

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

VOID
STATIC
setBitfieldReg (
  IN UINT32 Base,
  IN UINT32 Reg,
  IN UINT32 Lsb,
  IN UINT32 Width,
  IN UINT32 FieldValue
  )
{
  UINT32 Value;
  UINT32 RetryCount;
  UINT32 Index;
  UINT32 VerifyValue;
  UINT32 Addr;

  Addr = Base + ( Reg * 4 );
  RetryCount = 1000;
  Value = MmioRead16 (Addr);
  Value = clearBitfield (Value, Lsb, Width);
  Value |= FieldValue << Lsb;
  MmioWrite16 (Addr, (UINT16)Value);

  for (Index = 0; Index < RetryCount; Index++) {
    VerifyValue = MmioRead16 (Addr);
    if (VerifyValue == Value) {
      break;
    }

    MmioWrite16 (Addr, (UINT16)Value);
    gBS->Stall (1000);
  }
}

VOID
setBitfieldReg32 (
  IN UINT32 Addr,
  IN UINT32 Lsb,
  IN UINT32 Width,
  IN UINT32 FieldValue
  )
{
  UINT32 Value;
  UINT32 RetryCount;
  UINT32 Index;
  UINT32 VerifyValue;

  RetryCount = 1000;
  Value = MmioRead32 (Addr);
  Value = clearBitfield (Value, Lsb, Width);
  Value |= FieldValue << Lsb;
  MmioWrite32 (Addr, Value);

  for (Index = 0; Index < RetryCount; Index++) {
    VerifyValue = MmioRead32 (Addr);
    if (VerifyValue == Value) {
      break;
    }

    MmioWrite32 (Addr, Value);
    gBS->Stall (1000);
  }
}

UINT32
STATIC
getBitfieldReg (
  IN UINT32 Base,
  IN UINT32 Reg,
  IN UINT32 Lsb,
  IN UINT32 Width
  )
{
  UINT32 Value;
  UINT32 Addr;
  Addr = Base + Reg;
  Value = MmioRead16 (Addr);
  return getBitfield (Value, Lsb, Width);
}

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

VOID XgbeHwinitDelay ( )
{
	gBS->Stall (XGBE_DELAY_SILICON_LIMIT);
}

enum xgbe_mode xgbe_phy_get_basex_mode(XGBE_PHY_DATA *phy_data, UINTN speed)
{
	switch (speed) {
	case SPEED_1000:
		return XGBE_MODE_X;
	case SPEED_10000:
		return XGBE_MODE_KR;
	default:
		return XGBE_MODE_UNKNOWN;
	}
}

enum xgbe_mode xgbe_phy_get_baset_mode(XGBE_PHY_DATA *phy_data,  UINTN speed)
{
	switch (speed) {
	case SPEED_100:
		return XGBE_MODE_SGMII_100;
	case SPEED_1000:
		return XGBE_MODE_SGMII_1000;
	case SPEED_2500:
		return XGBE_MODE_KX_2500;
	case SPEED_10000:
		return XGBE_MODE_KR;
	default:
		return XGBE_MODE_UNKNOWN;
	}
}

// SFP 1G is not functional for SGMII_1000 mode. Lets use MODE_X For SFG 1G default
enum xgbe_mode xgbe_phy_get_sfp_mode(XGBE_PHY_DATA *phy_data, UINTN speed)
{
    switch (speed) {
    case SPEED_100:
        return XGBE_MODE_SGMII_100;
    case SPEED_1000:
        if (phy_data->sfp_base == XGBE_SFP_BASE_1000_T)
            return  XGBE_MODE_SGMII_1000;
        else
            return XGBE_MODE_X;
    case SPEED_10000:
    case SPEED_UNKNOWN:
        return XGBE_MODE_SFI;
    default:
        return XGBE_MODE_UNKNOWN;
    }
}

enum xgbe_mode xgbe_phy_get_bp_2500_mode(UINTN speed)
{
	switch (speed) {
	case SPEED_2500:
		return XGBE_MODE_KX_2500;
	default:
		return XGBE_MODE_UNKNOWN;
	}
}

enum xgbe_mode xgbe_phy_get_bp_mode(UINTN speed)
{
	switch (speed) {
	case SPEED_1000:
		return XGBE_MODE_KX_1000;
	case SPEED_10000:
		return XGBE_MODE_KR;
	default:
		return XGBE_MODE_UNKNOWN;
	}
}

enum xgbe_mode xgbe_phy_get_mode(ENET_DXE_PRIVATE_DATA *pdata, UINTN speed)
{
	XGBE_PHY_DATA *phy_data = pdata->phy_data;

	switch (phy_data->port_mode) {
	case XGBE_PORT_MODE_BACKPLANE:
		return xgbe_phy_get_bp_mode(speed);
	case XGBE_PORT_MODE_BACKPLANE_2500:
		return xgbe_phy_get_bp_2500_mode(speed);
	case XGBE_PORT_MODE_1000BASE_T:
	case XGBE_PORT_MODE_NBASE_T:
	case XGBE_PORT_MODE_10GBASE_T:
		return xgbe_phy_get_baset_mode(phy_data, speed);
	case XGBE_PORT_MODE_1000BASE_X:
	case XGBE_PORT_MODE_10GBASE_R:
		return xgbe_phy_get_basex_mode(phy_data, speed);
	case XGBE_PORT_MODE_SFP:
		return xgbe_phy_get_sfp_mode(phy_data, speed);
	default:
		return XGBE_MODE_UNKNOWN;
	}
}



BOOLEAN xgbe_phy_check_mode(ENET_DXE_PRIVATE_DATA *pdata,
        enum xgbe_mode mode, UINT64 advert)
{
   DEBUG ((EFI_D_ERROR, " xgbe_phy_check_mode  pdata->phy.autoneg = %x \n", pdata->phy.autoneg));
   DEBUG ((EFI_D_ERROR, " xgbe_phy_check_mode  advert = %lx  pdata->phy.supported = %lx \n", advert , pdata->phy.supported));
   DEBUG ((EFI_D_ERROR, " xgbe_phy_check_mode  pdata->phy.speed = %x \n", pdata->phy.speed));
   if (pdata->phy.autoneg == AUTONEG_ENABLE) {
       if(pdata->phy.supported  & advert)
           return TRUE;
       else
           return FALSE;
   } else {
       enum xgbe_mode cur_mode;

       cur_mode = xgbe_phy_get_mode(pdata, pdata->phy.speed);
       if (cur_mode == mode)
           return TRUE;
   }
   
   return FALSE;
}

BOOLEAN xgbe_phy_use_basex_mode(ENET_DXE_PRIVATE_DATA *pdata,
				    enum xgbe_mode mode)
{

	switch (mode) {
	case XGBE_MODE_X:
		return xgbe_phy_check_mode(pdata, mode, ADVERTISED_1000baseX_Full);
	case XGBE_MODE_KR:
		return xgbe_phy_check_mode(pdata, mode, ADVERTISED_10000baseKR_Full);
	default:
		return FALSE;
	}
}

BOOLEAN xgbe_phy_use_baset_mode(ENET_DXE_PRIVATE_DATA *pdata,
				    enum xgbe_mode mode)
{

	switch (mode) {
	case XGBE_MODE_SGMII_100:
		return xgbe_phy_check_mode(pdata, mode, ADVERTISED_100baseT_Full);
	case XGBE_MODE_SGMII_1000:
		return xgbe_phy_check_mode(pdata, mode, ADVERTISED_1000baseT_Full);
	case XGBE_MODE_KX_2500:
		return xgbe_phy_check_mode(pdata, mode,  ADVERTISED_2500baseT_Full);
	case XGBE_MODE_KR:
		return xgbe_phy_check_mode(pdata, mode, ADVERTISED_10000baseT_Full);
	default:
		return FALSE;
	}
}

BOOLEAN xgbe_phy_use_sfp_mode(ENET_DXE_PRIVATE_DATA *pdata,
				  enum xgbe_mode mode)
{
	XGBE_PHY_DATA *phy_data = pdata->phy_data;

	if (phy_data->sfp_mod_absent)
		return FALSE;

	DEBUG ((EFI_D_ERROR, " xgbe_phy_use_sfp_mode  phy_data->sfp_base = %x \n", phy_data->sfp_base));

	switch (mode) {
	case XGBE_MODE_X:
		if (phy_data->sfp_base == XGBE_SFP_BASE_1000_T)
			return FALSE;
		return xgbe_phy_check_mode(pdata, mode, ADVERTISED_1000baseX_Full);
	case XGBE_MODE_SGMII_100:
		if (phy_data->sfp_base != XGBE_SFP_BASE_1000_T)
			return FALSE;
		return xgbe_phy_check_mode(pdata, mode, ADVERTISED_100baseT_Full);
	case XGBE_MODE_SGMII_1000:
		if (phy_data->sfp_base != XGBE_SFP_BASE_1000_T)
			return FALSE;
		return xgbe_phy_check_mode(pdata, mode, ADVERTISED_1000baseT_Full);
	case XGBE_MODE_SFI:
		return xgbe_phy_check_mode(pdata, mode, ADVERTISED_10000baseSR_Full  || ADVERTISED_10000baseLR_Full  ||
					   							ADVERTISED_10000baseLRM_Full ||  ADVERTISED_10000baseER_Full  ||
					   							ADVERTISED_10000baseCR_Full
					   				);
	default:
		return FALSE;
	}
}

BOOLEAN xgbe_phy_use_bp_2500_mode(ENET_DXE_PRIVATE_DATA *pdata,
				      enum xgbe_mode mode)
{

	switch (mode) {
	case XGBE_MODE_KX_2500:
		return xgbe_phy_check_mode(pdata, mode, ADVERTISED_2500baseX_Full);
	default:
		return FALSE;
	}
}

BOOLEAN xgbe_phy_use_bp_mode(ENET_DXE_PRIVATE_DATA *pdata, enum xgbe_mode mode)
{
	switch (mode) {
	case XGBE_MODE_KX_1000:
		return xgbe_phy_check_mode(pdata, mode, ADVERTISED_1000baseKX_Full);
	case XGBE_MODE_KR:
		return xgbe_phy_check_mode(pdata, mode, ADVERTISED_10000baseKR_Full);
	default:
		return FALSE;
	}
}




BOOLEAN xgbe_phy_use_mode(ENET_DXE_PRIVATE_DATA *pdata, enum xgbe_mode mode)
{
	XGBE_PHY_DATA *phy_data = pdata->phy_data;

	DEBUG ((EFI_D_ERROR, " xgbe_phy_use_mode  phy_data->port_mode = %x \n", phy_data->port_mode));

	switch (phy_data->port_mode) {
	case XGBE_PORT_MODE_BACKPLANE:
		return xgbe_phy_use_bp_mode(pdata, mode);
	case XGBE_PORT_MODE_BACKPLANE_2500:
		return xgbe_phy_use_bp_2500_mode(pdata, mode);
	case XGBE_PORT_MODE_1000BASE_T:
	case XGBE_PORT_MODE_NBASE_T:
	case XGBE_PORT_MODE_10GBASE_T:
		return xgbe_phy_use_baset_mode(pdata, mode);
	case XGBE_PORT_MODE_1000BASE_X:
	case XGBE_PORT_MODE_10GBASE_R:
		return xgbe_phy_use_basex_mode(pdata, mode);
	case XGBE_PORT_MODE_SFP:
		return xgbe_phy_use_sfp_mode(pdata, mode);
	default:
		return FALSE;
	}
}

/*

to make use of the auto-negotiation (AN) phy hooks
to improve the ability to successfully complete Clause 73 AN when running
at 10gbps.  Hardware can sometimes have issues with CDR lock when the
AN DME page exchange is being performed.

The AN and KR training hooks are used as follows:
- The pre AN hook is used to disable CDR tracking in the PHY so that the
  DME page exchange can be successfully and consistently completed.
- The post KR training hook is used to re-enable the CDR tracking so that
  KR training can successfully complete.
- The post AN hook is used to check for an unsuccessful AN which will
  increase a CDR tracking enablement delay (up to a maximum value).

  https://lore.kernel.org/patchwork/patch/897575/

*/

VOID xgbe_phy_cdr_track(
	ENET_DXE_PRIVATE_DATA *pdata
	)
{
	XGBE_PHY_DATA *phy_data = pdata->phy_data;
	UINTN XpcsBase = pdata->xpcs_regs;

	if (!pdata->debugfs_an_cdr_workaround)
		return;

	if (!phy_data->phy_cdr_notrack)
		return;

	DEBUG ((EFI_D_ERROR, " xgbe_phy_cdr_track  \n"));

	gBS->Stall (phy_data->phy_cdr_delay + 500);

	XMDIO_WRITE_BITS(XpcsBase, MDIO_MMD_PMAPMD, MDIO_VEND2_PMA_CDR_CONTROL,
			 XGBE_PMA_CDR_TRACK_EN_MASK,
			 XGBE_PMA_CDR_TRACK_EN_ON);

	phy_data->phy_cdr_notrack = 0;
}

VOID xgbe_phy_cdr_notrack(
	ENET_DXE_PRIVATE_DATA *pdata
	)
{
	XGBE_PHY_DATA *phy_data = pdata->phy_data;
	UINTN XpcsBase = pdata->xpcs_regs;

	if (!pdata->debugfs_an_cdr_workaround)
		return;

#if 1
     //  10G_WORKING case
	if (phy_data->phy_cdr_notrack)
		return;
#else
	if (!phy_data->phy_cdr_notrack)
		return;
#endif

	DEBUG ((EFI_D_ERROR, " xgbe_phy_cdr_notrack  \n"));

	XMDIO_WRITE_BITS(XpcsBase, MDIO_MMD_PMAPMD, MDIO_VEND2_PMA_CDR_CONTROL,
			 XGBE_PMA_CDR_TRACK_EN_MASK,
			 XGBE_PMA_CDR_TRACK_EN_OFF);


	xgbe_phy_rrc(pdata);

	phy_data->phy_cdr_notrack = 1;
}

VOID xgbe_phy_kr_training_post(
	ENET_DXE_PRIVATE_DATA *pdata
	)
{
	if (!pdata->debugfs_an_cdr_track_early)
		xgbe_phy_cdr_track(pdata);
}

VOID xgbe_phy_kr_training_pre(
	ENET_DXE_PRIVATE_DATA *pdata
	)
{
	if (pdata->debugfs_an_cdr_track_early)
		xgbe_phy_cdr_track(pdata);
}

VOID xgbe_phy_an_post(
	ENET_DXE_PRIVATE_DATA *pdata
	)
{
	XGBE_PHY_DATA *phy_data = pdata->phy_data;

	switch (pdata->an_mode) {
	case XGBE_AN_MODE_CL73:
	case XGBE_AN_MODE_CL73_REDRV:
		if (phy_data->cur_mode != XGBE_MODE_KR)
			break;

		xgbe_phy_cdr_track(pdata);

		switch (pdata->an_result) {
		case XGBE_AN_READY:
		case XGBE_AN_COMPLETE:
			break;
		default:
			if (phy_data->phy_cdr_delay < XGBE_CDR_DELAY_MAX)
				phy_data->phy_cdr_delay += XGBE_CDR_DELAY_INC;
			else
				phy_data->phy_cdr_delay = XGBE_CDR_DELAY_INIT;
			break;
		}
		break;
	default:
		break;
	}
}

VOID xgbe_phy_an_pre(
	ENET_DXE_PRIVATE_DATA *pdata
	)
{
	XGBE_PHY_DATA *phy_data = pdata->phy_data;

	switch (pdata->an_mode) {
	case XGBE_AN_MODE_CL73:
	case XGBE_AN_MODE_CL73_REDRV:
		if (phy_data->cur_mode != XGBE_MODE_KR)
			break;
		xgbe_phy_cdr_notrack(pdata);
		break;
	default:
		break;
	}
}

enum xgbe_an xgbe_an73_tx_training(
	ENET_DXE_PRIVATE_DATA *pdata,
	enum xgbe_rx *state
	)
{
	XGBE_PHY_DATA *phy_data = pdata->phy_data;
	UINTN XpcsBase = pdata->xpcs_regs;
	UINTN ad_reg, lp_reg, reg;

	DEBUG ((EFI_D_ERROR, " xgbe_an73_tx_training  state = %x \n", *state));

	*state = XGBE_RX_COMPLETE;

	/* If we're not in KR mode then we're done */
	if (phy_data->cur_mode != XGBE_MODE_KR)
		return XGBE_AN_PAGE_RECEIVED;

	/* Enable/Disable FEC */
	ad_reg = XMDIO_READ(XpcsBase, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 2);
	lp_reg = XMDIO_READ(XpcsBase, MDIO_MMD_AN, MDIO_AN_LPA + 2);

	reg = XMDIO_READ(XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_FECCTRL);
	DEBUG ((EFI_D_ERROR, "MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_FECCTRL reg = %x \n", reg ));
	reg &= ~(MDIO_PMA_10GBR_FECABLE_ABLE | MDIO_PMA_10GBR_FECABLE_ERRABLE);
	if ((ad_reg & 0xc000) && (lp_reg & 0xc000))
		reg |= pdata->fec_ability;

	XMDIO_WRITE(XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_FECCTRL, reg);
	DEBUG ((EFI_D_ERROR, "MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_FECCTRL reg = %x \n", reg ));

	gBS->Stall (100);

	/* Start KR training */
	xgbe_phy_kr_training_pre(pdata);

	reg = XMDIO_READ(XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_PMD_CTRL);
	DEBUG ((EFI_D_ERROR, "KR MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_PMD_CTRL reg = %x \n", reg ));
	reg |= XGBE_KR_TRAINING_ENABLE;
	reg |= XGBE_KR_TRAINING_START;
	XMDIO_WRITE(XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_PMD_CTRL, reg);

	XMDIO_WRITE(XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_PMD_CTRL, reg); //check again
	reg = XMDIO_READ(XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_PMD_CTRL);
	DEBUG ((EFI_D_ERROR, "KR training initiated reg = %x \n", reg ));

#if 0
	UINTN count = 100;
    //while(count)
	{
		UINTN   RegVal;
		gBS->Stall (100);  //check againa
		// test if training is complete
		RegVal = XMDIO_READ (XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_STS);
		DEBUG ((EFI_D_ERROR, "KR training Status RegVal = %x \n", RegVal ));
		if (RegVal & MDIO_PMA_10GBR_STS_TR_FAIL) {
			DEBUG ((EFI_D_ERROR, "KR training Failed RegVal = %x \n", RegVal ));
		}
		if (RegVal & MDIO_PMA_10GBR_STS_RCV_STS) {
			// now check LD and LP Receiver Ready ( from KR Coefficient Status reg )
			if ((MDIO_PMA_10GBR_CE_RR & XMDIO_READ (XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_LP_CESTS)) &&
			  (MDIO_PMA_10GBR_CE_RR & XMDIO_READ (XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_LD_CESTS))) {
			  	DEBUG ((EFI_D_ERROR, "KR training Success RegVal = %x \n", RegVal ));
			}
		}
		count--;
	}
#endif

	xgbe_phy_kr_training_post(pdata);


	return XGBE_AN_PAGE_RECEIVED;
}

enum xgbe_an xgbe_an73_tx_xnp(
	ENET_DXE_PRIVATE_DATA *pdata,
	enum xgbe_rx *state
	)
{
	UINTN XpcsBase = pdata->xpcs_regs;
	UINTN msg;

	DEBUG ((EFI_D_ERROR, " xgbe_an73_tx_xnp  state = %x \n", *state));

	*state = XGBE_RX_XNP;

	msg = XGBE_XNP_MCF_NULL_MESSAGE;
	msg |= XGBE_XNP_MP_FORMATTED;

	XMDIO_WRITE(XpcsBase, MDIO_MMD_AN, MDIO_AN_XNP + 2, 0);
	XMDIO_WRITE(XpcsBase, MDIO_MMD_AN, MDIO_AN_XNP + 1, 0);
	XMDIO_WRITE(XpcsBase, MDIO_MMD_AN, MDIO_AN_XNP, msg);

	return XGBE_AN_PAGE_RECEIVED;
}

enum xgbe_an xgbe_an73_rx_bpa(
	ENET_DXE_PRIVATE_DATA *pdata,
	enum xgbe_rx *state
	)
{
	XGBE_PHY_DATA *phy_data = pdata->phy_data;
	UINTN XpcsBase = pdata->xpcs_regs;
	UINTN link_support;
	UINTN reg, ad_reg, lp_reg;

	DEBUG ((EFI_D_ERROR, " xgbe_an73_rx_bpa  state = %x \n", *state));

	/* Read Base Ability register 2 first */
	reg = XMDIO_READ(XpcsBase, MDIO_MMD_AN, MDIO_AN_LPA + 1);

	/* Check for a supported mode, otherwise restart in a different one */
	if (phy_data->cur_mode != XGBE_MODE_KR)
		link_support =  0x20;
	else
		link_support =  0x80;

	DEBUG ((EFI_D_ERROR, " xgbe_an73_rx_bpa  link_support = %x  reg = %x \n", link_support , reg ));

	if (!(reg & link_support))
		return XGBE_AN_INCOMPAT_LINK;

	/* Check Extended Next Page support */
	ad_reg = XMDIO_READ(XpcsBase, MDIO_MMD_AN, MDIO_AN_ADVERTISE);
	lp_reg = XMDIO_READ(XpcsBase, MDIO_MMD_AN, MDIO_AN_LPA);

	return ((ad_reg & XGBE_XNP_NP_EXCHANGE) ||
		(lp_reg & XGBE_XNP_NP_EXCHANGE))
	       ? xgbe_an73_tx_xnp(pdata, state)
	       : xgbe_an73_tx_training(pdata, state);
}

enum xgbe_an xgbe_an73_rx_xnp(
	ENET_DXE_PRIVATE_DATA *pdata,
	enum xgbe_rx *state
	)
{
	UINTN XpcsBase = pdata->xpcs_regs;
	UINTN ad_reg, lp_reg;

	DEBUG ((EFI_D_ERROR, " xgbe_an73_rx_xnp  state = %x \n", *state));

	/* Check Extended Next Page support */
	ad_reg = XMDIO_READ(XpcsBase, MDIO_MMD_AN, MDIO_AN_XNP);
	lp_reg = XMDIO_READ(XpcsBase, MDIO_MMD_AN, MDIO_AN_LPX);

	return ((ad_reg & XGBE_XNP_NP_EXCHANGE) ||
		(lp_reg & XGBE_XNP_NP_EXCHANGE))
	       ? xgbe_an73_tx_xnp(pdata, state)
	       : xgbe_an73_tx_training(pdata, state);
}

enum xgbe_an xgbe_an73_page_received(
	ENET_DXE_PRIVATE_DATA *pdata
	)
{
	XGBE_PHY_DATA *phy_data = pdata->phy_data;
	enum xgbe_rx *state;
	enum xgbe_an ret;

	DEBUG ((EFI_D_ERROR, " xgbe_an73_page_received phy_data->cur_mode = %x  \n", phy_data->cur_mode));

	if (phy_data->cur_mode != XGBE_MODE_KR)
		state =  &pdata->kx_state;
	else
		state =  &pdata->kr_state;

	switch (*state) {
	case XGBE_RX_BPA:
		ret = xgbe_an73_rx_bpa(pdata, state);
		break;

	case XGBE_RX_XNP:
		ret = xgbe_an73_rx_xnp(pdata, state);
		break;

	default:
		ret = XGBE_AN_ERROR;
	}

	return ret;
}

enum xgbe_mode xgbe_phy_cur_mode(
	ENET_DXE_PRIVATE_DATA *pdata
	)
{
	XGBE_PHY_DATA *phy_data = pdata->phy_data;

	return phy_data->cur_mode;
}


enum xgbe_mode xgbe_phy_switch_bp_mode(
	ENET_DXE_PRIVATE_DATA *pdata
	)
{
	/* If we are in KR switch to KX, and vice-versa */
	switch (xgbe_phy_cur_mode(pdata)) {
	case XGBE_MODE_KX_1000:
		return XGBE_MODE_KR;
	case XGBE_MODE_KR:
	default:
		return XGBE_MODE_KX_1000;
	}
}

UINT32 xgbe_set_speed(
	ENET_DXE_PRIVATE_DATA *pdata,
	UINT32 speed)
{
	UINT32 ss;
	xgmac_prv_data *xgmac_pdata = &pdata->xgmac_pdata;

	switch (speed) {
	case SPEED_1000:
		ss = 0x03;
		break;
	case SPEED_2500:
		ss = 0x02;
		break;
	case SPEED_10000:
		ss = 0x00;
		break;
	default:
		ss = 0x03;
		break;
	}

	if (XGMAC_IOREAD32_BITS(xgmac_pdata, MAC_TCR, SS) != ss)
		XGMAC_IOWRITE32_BITS(xgmac_pdata, MAC_TCR, SS, ss);

	return 0;
}


enum xgbe_mode xgbe_phy_switch_mode(
	ENET_DXE_PRIVATE_DATA *pdata
	)
{
	XGBE_PHY_DATA *phy_data = pdata->phy_data;

	switch (phy_data->port_mode) {
	case XGBE_PORT_MODE_BACKPLANE:
		return xgbe_phy_switch_bp_mode(pdata);

	case XGBE_PORT_MODE_BACKPLANE_2500:
		return XGBE_MODE_UNKNOWN;

	case XGBE_PORT_MODE_1000BASE_T:
	case XGBE_PORT_MODE_NBASE_T:
	case XGBE_PORT_MODE_10GBASE_T:
		return XGBE_MODE_UNKNOWN;

	case XGBE_PORT_MODE_1000BASE_X:
	case XGBE_PORT_MODE_10GBASE_R:
	case XGBE_PORT_MODE_SFP:
		/* No switching, so just return current mode */
		return xgbe_phy_cur_mode(pdata);
	default:
		return XGBE_MODE_UNKNOWN;
	}
}

VOID xgbe_kr_mode(
	ENET_DXE_PRIVATE_DATA *pdata
	)
{
   DEBUG ((EFI_D_ERROR, "xgbe_kr_mode \n"));
	/* Set MAC to 10G speed */
	xgbe_set_speed(pdata, SPEED_10000);

	/* Call PHY implementation support to complete rate change */
	xgbe_phy_set_mode(pdata, XGBE_MODE_KR);

	mCurrLanSpeed = 10;
}

VOID xgbe_kx_2500_mode(
	ENET_DXE_PRIVATE_DATA *pdata
	)
{
	/* Set MAC to 2.5G speed */
	xgbe_set_speed(pdata, SPEED_2500);

	/* Call PHY implementation support to complete rate change */
	xgbe_phy_set_mode(pdata, XGBE_MODE_KX_2500);

	mCurrLanSpeed = 2;
}

VOID xgbe_kx_1000_mode(
	ENET_DXE_PRIVATE_DATA *pdata
	)
{
	DEBUG ((EFI_D_ERROR, "xgbe_kx_1000_mode \n"));
	/* Set MAC to 1G speed */
	xgbe_set_speed(pdata, SPEED_1000);

	/* Call PHY implementation support to complete rate change */
	xgbe_phy_set_mode(pdata, XGBE_MODE_KX_1000);

	mCurrLanSpeed = 1;
}

VOID xgbe_sfp_mode(
	ENET_DXE_PRIVATE_DATA *pdata
	)
{
	/* If a KR re-driver is present, change to KR mode instead */
	//if (pdata->kr_redrv)
	//		xgbe_kr_mode(pdata);

	/* Set MAC to 10G speed */
	xgbe_set_speed(pdata, SPEED_10000);

	/* Call PHY implementation support to complete rate change */
	xgbe_phy_set_mode(pdata, XGBE_MODE_SFI);

	mCurrLanSpeed = 10;
}

VOID xgbe_x_mode(
	ENET_DXE_PRIVATE_DATA *pdata
	)
{
    UINT32 XpcsBase = pdata->xpcs_regs;

    // Disable KR training
    xgbe_an73_disable_kr_training (XpcsBase);

	/* Set MAC to 1G speed */
	xgbe_set_speed(pdata, SPEED_1000);

	/* Call PHY implementation support to complete rate change */
	xgbe_phy_set_mode(pdata, XGBE_MODE_X);

	mCurrLanSpeed = 1;
}


VOID xgbe_sgmii_1000_mode(
	ENET_DXE_PRIVATE_DATA *pdata
	)
{
    UINT32 XpcsBase = pdata->xpcs_regs;

	/* Disable KR training */
    xgmac_pcs_disable_kr_training(XpcsBase);

	/* Set MAC to 1G speed */
	xgbe_set_speed(pdata, SPEED_1000);

	/* Call PHY implementation support to complete rate change */
	xgbe_phy_set_mode(pdata, XGBE_MODE_SGMII_1000);

	mCurrLanSpeed = 1;
}



VOID xgbe_sgmii_100_mode(
        ENET_DXE_PRIVATE_DATA *pdata
        )
{    
    UINT32 XpcsBase = pdata->xpcs_regs;

    /* Disable KR training */
    xgmac_pcs_disable_kr_training(XpcsBase);
  
    /* Set MAC to 1G speed */
    xgbe_set_speed(pdata, SPEED_1000);

    /* Call PHY implementation support to complete rate change */
    xgbe_phy_set_mode(pdata, XGBE_MODE_SGMII_100);

    mCurrLanSpeed = 1;
}


VOID xgbe_set_mode(
	ENET_DXE_PRIVATE_DATA *pdata,
	enum xgbe_mode mode
	)
{
	switch (mode) {
	case XGBE_MODE_KX_1000:
		xgbe_kx_1000_mode(pdata);
		break;
	case XGBE_MODE_KX_2500:
		xgbe_kx_2500_mode(pdata);
		break;
	case XGBE_MODE_KR:
		xgbe_kr_mode(pdata);
		break;
	case XGBE_MODE_SGMII_100:
		xgbe_sgmii_100_mode(pdata);
		break;
	case XGBE_MODE_SGMII_1000:
		xgbe_sgmii_1000_mode(pdata);
		break;
	case XGBE_MODE_X:
		xgbe_x_mode(pdata);
		break;
	case XGBE_MODE_SFI:
		xgbe_sfp_mode(pdata);
		break;
	case XGBE_MODE_UNKNOWN:
		break;
	default:
		DEBUG ((EFI_D_ERROR, "invalid operation mode requested (%u)\n", mode));
	}
}

VOID xgbe_switch_mode(
	ENET_DXE_PRIVATE_DATA *pdata
	)
{
	xgbe_set_mode(pdata, xgbe_phy_switch_mode(pdata));
}

enum xgbe_an xgbe_an73_incompat_link(
	ENET_DXE_PRIVATE_DATA *pdata
	)
{
	XGBE_PHY_DATA *phy_data = pdata->phy_data;

	/* Be sure we aren't looping trying to negotiate */
	if (phy_data->cur_mode == XGBE_MODE_KR) {
		pdata->kr_state = XGBE_RX_ERROR;

		//switching from kr mode to kx mode is giving imcompatable link first time
		// 2nd time onwords getting proper AN COMPLETE event
		pdata->mode_switch = 0;

		if (pdata->kx_state != XGBE_RX_BPA)
			return XGBE_AN_NO_LINK;
	} else {
		pdata->kx_state = XGBE_RX_ERROR;

		if(pdata->mode_switch == 2) //alow 2 times to run KX mode .
			pdata->mode_switch = 0;
		else
			pdata->mode_switch++;

		if (pdata->kr_state != XGBE_RX_BPA)
			return XGBE_AN_NO_LINK;
	}

    //In case of 10G Speed selection no need to switch to 1G
	if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000){   
    	if(pdata->mode_switch == 0 || phy_data->cur_mode == XGBE_MODE_KR){

		xgbe_an_disable(pdata);

		xgbe_switch_mode(pdata);
    	}
	}

	return XGBE_AN_INCOMPAT_LINK;
}



VOID
xgbe_an37_clear_interrupts (
  UINTN XpcsBase
  )
{
  UINTN reg;

  reg = XMDIO_READ (XpcsBase, MDIO_MMD_VEND2, MDIO_VEND2_AN_STAT);
  reg &= ~XGBE_AN_CL37_INT_MASK;
  XMDIO_WRITE (XpcsBase, MDIO_MMD_VEND2, MDIO_VEND2_AN_STAT, reg);
}

VOID
xgbe_an37_set_EN_VSMMD1 (
  UINTN XpcsBase
  )
{
  UINTN reg;
  DEBUG ((EFI_D_ERROR, "xgbe_an37_set_EN_VSMMD1\n" ));

  reg = XMDIO_READ (XpcsBase, MDIO_MMD_PCS, MDIO_PCS_DIG_CTRL);
  if( !(reg & XGBE_PCS_EN_VSMMD1)){
	  reg |= XGBE_PCS_EN_VSMMD1;
	  XMDIO_WRITE (XpcsBase, MDIO_MMD_PCS, MDIO_PCS_DIG_CTRL, reg);
  }
}

VOID
xgbe_an37_disable_interrupts (
  UINTN XpcsBase
  )
{
  UINTN reg;
  DEBUG ((EFI_D_ERROR, "xgbe_an37_disable_interrupts\n" ));
  reg = XMDIO_READ (XpcsBase, MDIO_MMD_VEND2, MDIO_VEND2_AN_CTRL);
  reg &= ~XGBE_AN_CL37_INT_MASK;
  XMDIO_WRITE (XpcsBase, MDIO_MMD_VEND2, MDIO_VEND2_AN_CTRL, reg);
  reg = XMDIO_READ (XpcsBase, MDIO_MMD_PCS, MDIO_PCS_DIG_CTRL);
  reg &= ~XGBE_PCS_CL37_BP;
  XMDIO_WRITE (XpcsBase, MDIO_MMD_PCS, MDIO_PCS_DIG_CTRL, reg);
}

VOID
xgbe_an37_enable_interrupts (
  UINTN XpcsBase
  )
{
  UINTN reg;

  reg = XMDIO_READ (XpcsBase, MDIO_MMD_PCS, MDIO_PCS_DIG_CTRL);
  reg |= XGBE_PCS_CL37_BP;
  XMDIO_WRITE ( XpcsBase, MDIO_MMD_PCS, MDIO_PCS_DIG_CTRL, reg);
  reg = XMDIO_READ (XpcsBase, MDIO_MMD_VEND2, MDIO_VEND2_AN_CTRL);
  reg |= XGBE_AN_CL37_INT_MASK;
  XMDIO_WRITE (XpcsBase, MDIO_MMD_VEND2, MDIO_VEND2_AN_CTRL, reg);
}

VOID
xgbe_an73_clear_interrupts (
  UINTN XpcsBase
  )
{
  XMDIO_WRITE (XpcsBase, MDIO_MMD_AN, MDIO_AN_INT, 0);
}

VOID
xgbe_an73_disable_interrupts (
  UINTN XpcsBase
  )
{
  DEBUG ((EFI_D_ERROR, "xgbe_an73_disable_interrupts\n" ));
  XMDIO_WRITE (XpcsBase, MDIO_MMD_AN, MDIO_AN_INTMASK, 0);
}

VOID
xgbe_an73_enable_interrupts (
  UINTN XpcsBase
  )
{
  DEBUG ((EFI_D_ERROR, "xgbe_an73_enable_interrupts\n" ));
  XMDIO_WRITE (XpcsBase, MDIO_MMD_AN, MDIO_AN_INTMASK, XGBE_AN_CL73_INT_MASK);
}

VOID
xgbe_an_disable_interrupts (
	ENET_DXE_PRIVATE_DATA *pdata,
	UINT32 XpcsBase
	)
{
	  switch (pdata->an_mode) {
	  case XGBE_AN_MODE_CL73:
	  case XGBE_AN_MODE_CL73_REDRV:
		  xgbe_an73_disable_interrupts(XpcsBase);
		  break;
	  case XGBE_AN_MODE_CL37:
	  case XGBE_AN_MODE_CL37_SGMII:
		  xgbe_an37_disable_interrupts(XpcsBase);
		  break;
	  default:
		  break;
	  }
}

VOID
xgbe_an_enable_interrupts (
	ENET_DXE_PRIVATE_DATA *pdata,
	UINT32 XpcsBase
	)
{
	  switch (pdata->an_mode) {
	  case XGBE_AN_MODE_CL73:
	  case XGBE_AN_MODE_CL73_REDRV:
		  xgbe_an73_enable_interrupts(XpcsBase);
		  break;
	  case XGBE_AN_MODE_CL37:
	  case XGBE_AN_MODE_CL37_SGMII:
		  xgbe_an37_enable_interrupts(XpcsBase);
		  break;
	  default:
		  break;
	  }
}

VOID
STATIC
xgbe_an_clear_interrupts (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  UINTN XpcsBase;
  XpcsBase = pdata->xpcs_regs;
  DEBUG ((EFI_D_ERROR, "xgbe_an_clear_interrupts\n"));

  switch (pdata->an_mode) {
  case XGBE_AN_MODE_CL73:
  case XGBE_AN_MODE_CL73_REDRV:
	  xgbe_an73_clear_interrupts (XpcsBase);
	  break;
  case XGBE_AN_MODE_CL37:
  case XGBE_AN_MODE_CL37_SGMII:
	  xgbe_an37_clear_interrupts (XpcsBase);
	  break;
  default:
	  break;
  }
}

EFI_STATUS
XgbePlatinit (
  ENET_DXE_PRIVATE_DATA *Private
  )
{
  UINT32 XgmacBase;
  XgmacBase = Private->xgmac_pdata.xgmac_regs;
  setBitfieldReg32 (XgmacBase + INT_EN, 0, 20, 0x1FFFFF);
  return EFI_SUCCESS;
}


BOOLEAN
CheckPortEnabled (
  IN       UINT32 XgmacBase
  )
{
  UINT32 ConnType;
  ConnType = getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_0, 28, 3 ); // Check Connection Type
  if (ConnType == 0) {
    return FALSE;
  }
  ConnType = getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_0, 23, 4 ); // Check Speed Type
  if (ConnType == 0) {
    return FALSE;
  }
  return TRUE;
}

BOOLEAN
XgbePhyModeMismatch (
  XGBE_PHY_DATA *phy_data
  )
{
  switch (phy_data->port_mode) {
  case XGBE_PORT_MODE_BACKPLANE:
    if ((phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000) ||
        (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_10000)) {
      return FALSE;
    }
    break;

  case XGBE_PORT_MODE_BACKPLANE_2500:
    if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_2500) {
      return FALSE;
    }
    break;

  case XGBE_PORT_MODE_1000BASE_T:
    if ((phy_data->port_speeds & XGBE_PHY_PORT_SPEED_100) ||
        (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000)) {
      return FALSE;
    }
    break;

  case XGBE_PORT_MODE_1000BASE_X:
    if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000) {
      return FALSE;
    }
    break;

  case XGBE_PORT_MODE_NBASE_T:
    if ((phy_data->port_speeds & XGBE_PHY_PORT_SPEED_100) ||
        (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000) ||
        (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_2500)) {
      return FALSE;
    }
    break;

  case XGBE_PORT_MODE_10GBASE_T:
    if ((phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000) ||
        (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_10000)) {
      return FALSE;
    }
    break;
  case XGBE_PORT_MODE_10GBASE_R:
    if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_10000) {
      return FALSE;
    }
    break;

  case XGBE_PORT_MODE_SFP:
    if ((phy_data->port_speeds & XGBE_PHY_PORT_SPEED_100) ||
        (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000) ||
        (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_10000)) {
          DEBUG ((EFI_D_ERROR, "XGBE_PORT_MODE_SFP returning FALSE \n"));
      return FALSE;
    }

    break;
  default:
    break;
  }
  return TRUE;
}

EFI_STATUS
xgbe_phy_mdio_reset_setup (
  XGBE_PHY_DATA *phy_data,
  IN       UINT32 XgmacBase
  )
{

  if (phy_data->conn_type != XGBE_CONN_TYPE_MDIO) {
    DEBUG ((EFI_D_ERROR, "Not XGBE_CONN_TYPE_MDIO so get out of here....\n"));
    return 0;
  }
  phy_data->mdio_reset = getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_3, 0, 2 );
  switch (phy_data->mdio_reset) {
  case XGBE_MDIO_RESET_NONE:
  case XGBE_MDIO_RESET_I2C_GPIO:
  case XGBE_MDIO_RESET_INT_GPIO:
    break;
  default:
    DEBUG ((EFI_D_ERROR, "unsupported MDIO reset\n"));
    return 1;
  }

  if (phy_data->mdio_reset == XGBE_MDIO_RESET_I2C_GPIO) {
    phy_data->mdio_reset_addr = XGBE_GPIO_ADDRESS_PCA9555 + (getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_3, 8, 3 ));
    phy_data->mdio_reset_gpio = getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_3, 12, 4 );
  } else if (phy_data->mdio_reset == XGBE_MDIO_RESET_INT_GPIO) {
    phy_data->mdio_reset_gpio = getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_3, 4, 2 );
  }
  return EFI_SUCCESS;
}
BOOLEAN
xgbe_phy_redrv_error (
  XGBE_PHY_DATA *phy_data,
  IN       UINT32 XgmacBase
  )
{
  if (!phy_data->redrv) {
    return FALSE;
  }
  if (phy_data->redrv_if >= XGBE_PHY_REDRV_IF_MAX) {
    return TRUE;
  }

  switch (phy_data->redrv_model) {
  case XGBE_PHY_REDRV_MODEL_4223:
    if (phy_data->redrv_lane > 3) {
      return TRUE;
    }
    break;
  case XGBE_PHY_REDRV_MODEL_4227:
    if (phy_data->redrv_lane > 1) {
      return TRUE;
    }
  break;
  default:
    return TRUE;
  }
  return FALSE;
}

VOID
xgbe_phy_sfp_setup (
  ENET_DXE_PRIVATE_DATA *Private,
  XGBE_PHY_DATA *phy_data
  )
{
  UINT32 MuxAddrHi;
  UINT32 MuxAddrLo;
  UINT32 XgmacBase;
  XgmacBase = Private->xgmac_pdata.xgmac_regs;

  MuxAddrLo = getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_4, 0, 3);  //PCA9545 Low Address
  MuxAddrHi = getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_4, 8, 5);  //PCA9545 Upper Address
  if (MuxAddrLo != 0x7) {
    phy_data->sfp_comm = XGBE_SFP_COMM_PCA9545;
    phy_data->sfp_mux_address = (MuxAddrHi << 2) + MuxAddrLo;
    phy_data->sfp_mux_channel = getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_4, 4, 3);
    DEBUG ((EFI_D_ERROR, "SFP: mux_address = %x.\n", phy_data->sfp_mux_address));
    DEBUG ((EFI_D_ERROR, "SFP: sfp_mux_channel = %u\n", phy_data->sfp_mux_channel));
  }
  //SET GPIOS
  phy_data->sfp_gpio_address = PCA9555_ADDRESS + getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_3, 8, 3);  //GPIO_ADDR
  phy_data->sfp_gpio_tx_fault = getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_3, 12, 4);    //GPIO_TX_FAULT
  phy_data->sfp_gpio_rate_select = getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_3, 16, 4); //GPIO_RATE_SELECT
  phy_data->sfp_gpio_mod_absent = getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_3, 20, 4);  //GPIO_MOD_ABS
  phy_data->sfp_gpio_rx_los = getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_3, 24, 4);      //GPIO_RX_LOS
  phy_data->sfp_gpio_mask = getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_3, 28, 4);        //GPIO_MASK

  DEBUG ((EFI_D_ERROR, "sfp_gpio_address = %0x\n", phy_data->sfp_gpio_address));
  DEBUG ((EFI_D_ERROR, "gpio_mask = %0x\n", phy_data->sfp_gpio_mask));
  DEBUG ((EFI_D_ERROR, "gpio_rx_los = %0x\n", phy_data->sfp_gpio_rx_los));
  DEBUG ((EFI_D_ERROR, "sfp_gpio_tx_fault = %0x\n", phy_data->sfp_gpio_tx_fault));
  DEBUG ((EFI_D_ERROR, "gpio_mod_absent = %0x\n", phy_data->sfp_gpio_mod_absent));
  DEBUG ((EFI_D_ERROR, "gpio_rate_select = %0x\n", phy_data->sfp_gpio_rate_select));
}

VOID
STATIC
xgbe_phy_an_sfp_mode (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  XGBE_PHY_DATA *phy_data = pdata->phy_data;
  switch (phy_data->sfp_base) {
  case XGBE_SFP_BASE_1000_T:
    pdata->an_mode = XGBE_AN_MODE_CL37_SGMII;
 	break; 
  case XGBE_SFP_BASE_1000_SX:
  case XGBE_SFP_BASE_1000_LX:
  case XGBE_SFP_BASE_1000_CX:
    pdata->an_mode = XGBE_AN_MODE_CL37;
 	break;
  default:
    pdata->an_mode = XGBE_AN_MODE_NONE;
  }

  DEBUG ((EFI_D_ERROR, "pdata->an_mode  = %0x\n", pdata->an_mode));
}

VOID
xgbe_phy_an_mode (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  XGBE_PHY_DATA *phy_data = pdata->phy_data;

  // A KR re-driver will always require CL73 AN
  if (phy_data->redrv) {
    pdata->an_mode = XGBE_AN_MODE_CL73_REDRV;
  }
  switch (phy_data->port_mode) {
  case XGBE_PORT_MODE_BACKPLANE:
    pdata->an_mode = XGBE_AN_MODE_CL73;
 	break;
  case XGBE_PORT_MODE_BACKPLANE_2500:
    pdata->an_mode = XGBE_AN_MODE_NONE;
	break;
  case XGBE_PORT_MODE_1000BASE_T:
    pdata->an_mode = XGBE_AN_MODE_CL37_SGMII;
	break;
  case XGBE_PORT_MODE_1000BASE_X:
    pdata->an_mode = XGBE_AN_MODE_CL37;
	break;
  case XGBE_PORT_MODE_NBASE_T:
    pdata->an_mode = XGBE_AN_MODE_CL37_SGMII;
	break;
  case XGBE_PORT_MODE_10GBASE_T:
    pdata->an_mode = XGBE_AN_MODE_CL73;
	break;
  case XGBE_PORT_MODE_10GBASE_R:
    pdata->an_mode = XGBE_AN_MODE_NONE;
	break;
  case XGBE_PORT_MODE_SFP:
    xgbe_phy_an_sfp_mode (pdata);
	break;
  default:
    pdata->an_mode = XGBE_AN_MODE_NONE;
	break;
  }

  DEBUG ((EFI_D_ERROR, "pdata->an_mode  = %0x  phy_data->port_mode = %0x \n", pdata->an_mode , phy_data->port_mode));
}

EFI_STATUS xgbe_phy_reset(ENET_DXE_PRIVATE_DATA *Private)
{
	enum xgbe_mode cur_mode;
	XGBE_PHY_DATA *phy_data = Private->phy_data;
	UINTN ret ;

	/* Reset by power cycling the PHY */
	cur_mode = phy_data->cur_mode;

	xgbe_phy_power_off (Private);
	xgbe_phy_set_mode(Private,cur_mode);

	if (!phy_data->phydev)
		return 0;

	/* Reset the external PHY */
	ret = xgbe_phy_mdio_reset(Private);
	if (ret)
		return ret;

	//return phy_init_hw(phy_data->phydev);

   return EFI_SUCCESS;
}

EFI_STATUS xgbe_phy_stop(ENET_DXE_PRIVATE_DATA *Private)
{
	/* Reset CDR support */
	xgbe_phy_cdr_track(Private);

	xgbe_an_disable (Private);
	xgbe_an_clear_interrupts (Private);

	xgbe_phy_power_off (Private);

   return EFI_SUCCESS;
}


EFI_STATUS  xgbe_phy_an_advertising (ENET_DXE_PRIVATE_DATA *Private)
{
    XGBE_PHY_DATA *phy_data = Private->phy_data;

	if(Private->fec_ability & MDIO_PMA_10GBR_FECABLE_ABLE){
		Private->phy.supported |=   ADVERTISED_10000baseR_FEC;
	}

	DEBUG ((EFI_D_ERROR, "Checking Mode port_mode = %0x Private->fec_ability = %x \n", phy_data->port_mode , Private->fec_ability));

    Private->phy.supported &= ~ADVERTISED_1000baseKX_Full;
	Private->phy.supported &= ~ADVERTISED_10000baseKR_Full;

	switch (phy_data->port_mode) {
	case XGBE_PORT_MODE_BACKPLANE:;
		  Private->phy.supported |=   ADVERTISED_10000baseKR_Full | ADVERTISED_1000baseKX_Full;
		break;
	case XGBE_PORT_MODE_BACKPLANE_2500:
		Private->phy.supported |= ADVERTISED_1000baseKX_Full;
	  break;
	case XGBE_PORT_MODE_1000BASE_T:
	case XGBE_PORT_MODE_1000BASE_X:
	case XGBE_PORT_MODE_NBASE_T:
		Private->phy.supported |= ADVERTISED_1000baseKX_Full;
	  break;
	case XGBE_PORT_MODE_10GBASE_T:
	  if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_10000) {
		  Private->phy.supported |= ADVERTISED_10000baseKR_Full;
	  }else{
		  Private->phy.supported |= ADVERTISED_1000baseKX_Full;
	  }
	  break;

	case XGBE_PORT_MODE_10GBASE_R:
	  Private->phy.supported |= ADVERTISED_10000baseKR_Full;
	  break;

	case XGBE_PORT_MODE_SFP:
		switch (phy_data->sfp_base) {
			case XGBE_SFP_BASE_1000_T:
			case XGBE_SFP_BASE_1000_SX:
			case XGBE_SFP_BASE_1000_LX:
			case XGBE_SFP_BASE_1000_CX:
				Private->phy.supported |= ADVERTISED_1000baseKX_Full;
			break;

			default:
				Private->phy.supported |= ADVERTISED_10000baseKR_Full;
			break;
		}
	  break;
	default:
	  Private->phy.supported |= ADVERTISED_10000baseKR_Full;
	  break;
	}

    return EFI_SUCCESS;
}



EFI_STATUS
xgbe_phy_init (
  ENET_DXE_PRIVATE_DATA *Private
  )
{
  XGBE_PHY_DATA *phy_data;
  UINT32 XgmacBase;
  UINT32 XpcsBase = Private->xpcs_regs;

  XgmacBase = Private->xgmac_pdata.xgmac_regs;
  phy_data = AllocateZeroPool (sizeof (XGBE_PHY_DATA));
  if (phy_data == NULL) {
    DEBUG ((EFI_D_ERROR, "Could not allocate xgbe_phy_data structures.\n"));
    return EFI_OUT_OF_RESOURCES;
  }
  if (CheckPortEnabled (XgmacBase) == FALSE) {
    DEBUG ((EFI_D_ERROR, "XMAC: Port is disabled XgmacBase = %x \n", XgmacBase));
    return EFI_UNSUPPORTED;
  }
  phy_data->port_id = (UINT8)getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_0, 0, 8);      //Port Number
  phy_data->port_mode = getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_0, 8, 4);           //Platform Config
  phy_data->mdio_addr = getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_0, 16, 5);          //MDIO_ID
  phy_data->port_speeds = getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_0, 23, 4);        // Port Speed
  phy_data->conn_type = getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_0, 28, 3);          //Connection Type
  if (phy_data->conn_type == 0) {
    setBitfieldReg32 (XgmacBase + PORT_CLK_GATE_EN, 1, 1, 0x1);                              //Disabled port, Gate clock
    DEBUG ((EFI_D_ERROR, "XgmacBase disabled with address %0x \n", XgmacBase));
    return EFI_NOT_FOUND;
  }

  phy_data->redrv = getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_4, 31, 1);
  phy_data->redrv_if = getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_4, 23, 1);
  phy_data->redrv_addr = getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_4, 16, 7);
  phy_data->redrv_lane = getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_4, 24, 3);
  phy_data->redrv_model = getBitfieldReg32 (XgmacBase + ENET_PORT_PROPERTY_4, 28, 3);

  Private->xprop_regs = Private->xgmac_pdata.xgmac_regs + XGBE_MAC_CTRL_OFFSET;
  Private->xi2c_regs = Private->xgmac_pdata.xgmac_regs + XGBE_I2C_CTRL_OFFSET;

  DEBUG ((EFI_D_ERROR, "Private->xprop_regs = %x \n", Private->xprop_regs));
  DEBUG ((EFI_D_ERROR, "***PhySetup port_id = %0x \n",  phy_data->port_id ));
  DEBUG ((EFI_D_ERROR, "***PhySetup port_mode = %0x \n",  phy_data->port_mode ));
  DEBUG ((EFI_D_ERROR, "***PhySetup mdio_addr = %0x \n",  phy_data->mdio_addr ));
  DEBUG ((EFI_D_ERROR, "***PhySetup port_speeds = %0x \n",  phy_data->port_speeds ));
  DEBUG ((EFI_D_ERROR, "***PhySetup conn_type = %0x \n",  phy_data->conn_type ));
  DEBUG ((EFI_D_ERROR, "***PhySetup  phy_data->redrv Present = %0x \n",   phy_data->redrv ));
  DEBUG ((EFI_D_ERROR, "***PhySetup  redrv_if = %0x \n",   phy_data->redrv_if ));
  DEBUG ((EFI_D_ERROR, "***PhySetup  redrv_addr = %0x \n",   phy_data->redrv_addr ));
  DEBUG ((EFI_D_ERROR, "***PhySetup  redrv_lane = %0x \n",   phy_data->redrv_lane ));
  DEBUG ((EFI_D_ERROR, "***PhySetup  redrv_model = %0x \n",   phy_data->redrv_model ));

  if (XgbePhyModeMismatch (phy_data)) {
    DEBUG ((EFI_D_ERROR, "phy mode / speed mismatch.\n"));
    return EFI_DEVICE_ERROR;
  }

  if (xgbe_phy_redrv_error (phy_data, XgmacBase)) {
    DEBUG ((EFI_D_ERROR, "XGBE: phy re-driver settings error\n"));
    return EFI_DEVICE_ERROR;
  }
  DEBUG ((EFI_D_ERROR, "xgbe_phy_redrv_error Complete\n"));

  xgbe_phy_mdio_reset_setup (phy_data, XgmacBase);

  Private->kr_redrv = phy_data->redrv;

  //   Indicate current mode is unknown
  phy_data->cur_mode = XGBE_MODE_UNKNOWN;

  //   Initialize supported features
  Private->fec_ability = XMDIO_READ(XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_FECCTRL);

  Private->fec_ability &= ( MDIO_PMA_10GBR_FECABLE_ABLE | MDIO_PMA_10GBR_FECABLE_ERRABLE);

  DEBUG ((EFI_D_ERROR, "Checking Mode port_mode = %0x Private->fec_ability = %x \n", phy_data->port_mode , Private->fec_ability));
  switch (phy_data->port_mode) {
  // Backplane support
  case XGBE_PORT_MODE_BACKPLANE:
      if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000) {
        //phy_data->start_mode = XGBE_MODE_KX_1000;
		Private->phy.supported |=  ADVERTISED_1000baseKX_Full;
      }
      if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_10000) {
        //phy_data->start_mode = XGBE_MODE_KR;
		Private->phy.supported |=   ADVERTISED_10000baseKR_Full ;

		if(Private->fec_ability & MDIO_PMA_10GBR_FECABLE_ABLE){
			Private->phy.supported |=   ADVERTISED_10000baseR_FEC;
		}
      }
      phy_data->phydev_mode = XGBE_MDIO_MODE_NONE;
	  Private->phy.supported |=   ADVERTISED_Pause |  ADVERTISED_Asym_Pause |  ADVERTISED_Backplane | ADVERTISED_Autoneg;
      break;
  case XGBE_PORT_MODE_BACKPLANE_2500:
    //phy_data->start_mode = XGBE_MODE_KX_2500;
	Private->phy.supported |=   ADVERTISED_Pause |  ADVERTISED_Asym_Pause |  ADVERTISED_Backplane | ADVERTISED_2500baseX_Full;
    phy_data->phydev_mode = XGBE_MDIO_MODE_NONE;
    break;

   // MDIO 1GBase-T support
  case XGBE_PORT_MODE_1000BASE_T:
  	Private->phy.supported |=   ADVERTISED_Pause |  ADVERTISED_Asym_Pause |  ADVERTISED_Autoneg | ADVERTISED_TP;
    if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_100) {
        //phy_data->start_mode = XGBE_MODE_SGMII_100;
		Private->phy.supported |= ADVERTISED_100baseT_Full;
    }
    if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000) {
        //phy_data->start_mode = XGBE_MODE_SGMII_1000;
		Private->phy.supported |= ADVERTISED_1000baseT_Full;
    }
    phy_data->phydev_mode = XGBE_MDIO_MODE_CL22;
    break;

  // MDIO Base-X support
  case XGBE_PORT_MODE_1000BASE_X:
  	Private->phy.supported |=   ADVERTISED_Pause |  ADVERTISED_Asym_Pause | ADVERTISED_Autoneg | ADVERTISED_FIBER;
    //phy_data->start_mode = XGBE_MODE_X;
    Private->phy.supported  |= ADVERTISED_1000baseX_Full;
    Private->phy.supported  |= ADVERTISED_1000baseKX_Full;

	phy_data->phydev_mode = XGBE_MDIO_MODE_CL22;
    break;

  // MDIO NBase-T support
  case XGBE_PORT_MODE_NBASE_T:
  	Private->phy.supported |=   ADVERTISED_Pause | ADVERTISED_Asym_Pause |  ADVERTISED_Autoneg | ADVERTISED_TP;
    if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_100) {
      //phy_data->start_mode = XGBE_MODE_SGMII_100;
	  Private->phy.supported |= ADVERTISED_100baseT_Full;
    }
    if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000) {
      //phy_data->start_mode = XGBE_MODE_SGMII_1000;
	  Private->phy.supported |= ADVERTISED_1000baseT_Full;
    }
    if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_2500) {
      //phy_data->start_mode = XGBE_MODE_KX_2500;
	  Private->phy.supported |= ADVERTISED_2500baseT_Full;
	  Private->phy.supported |= ADVERTISED_1000baseKX_Full;
    }
    phy_data->phydev_mode = XGBE_MDIO_MODE_CL45;
    break;

  // 10GBase-T support
  case XGBE_PORT_MODE_10GBASE_T:
  	Private->phy.supported |=   ADVERTISED_Pause | ADVERTISED_Asym_Pause | ADVERTISED_Autoneg | ADVERTISED_TP;
    if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_100) {
      //phy_data->start_mode = XGBE_MODE_SGMII_100;
	  Private->phy.supported |= ADVERTISED_100baseT_Full;
    }
    if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000) {
      //phy_data->start_mode = XGBE_MODE_SGMII_1000;
	  Private->phy.supported |= ADVERTISED_1000baseT_Full;
    }
    if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_10000) {
      //phy_data->start_mode = XGBE_MODE_KR;
	  Private->phy.supported |= ADVERTISED_1000baseT_Full;
    }
    phy_data->phydev_mode = XGBE_MDIO_MODE_CL45;
    break;

  // 10GBase-R support
  case XGBE_PORT_MODE_10GBASE_R:
  	Private->phy.supported |=   ADVERTISED_Pause | ADVERTISED_Asym_Pause | ADVERTISED_Autoneg | ADVERTISED_FIBER;
	//Private->phy.supported |= ADVERTISED_10000baseSR_Full | ADVERTISED_1000baseLR_Full | ADVERTISED_1000baseLRM_Full |ADVERTISED_1000baseER_Full;
    Private->phy.supported |= ADVERTISED_10000baseKR_Full;
	if(Private->fec_ability & MDIO_PMA_10GBR_FECABLE_ABLE){
		Private->phy.supported |=   ADVERTISED_10000baseR_FEC;
	}
	//phy_data->start_mode = XGBE_MODE_SFI;
    phy_data->phydev_mode = XGBE_MDIO_MODE_NONE;
    break;

  // SFP support
  case XGBE_PORT_MODE_SFP:
  	Private->phy.supported |=   ADVERTISED_Pause | ADVERTISED_Asym_Pause | ADVERTISED_Autoneg | ADVERTISED_FIBER | ADVERTISED_TP;
#if 0
	if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_100) {
      DEBUG ((EFI_D_ERROR, "XGBE_PHY_PORT_SPEED_100\n"));
      phy_data->start_mode = XGBE_MODE_SGMII_100;
    }
    if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000) {
      phy_data->start_mode = XGBE_MODE_SGMII_1000;
      DEBUG ((EFI_D_ERROR, "XGBE_MODE_SGMII_1000\n"));
    }
    if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_10000) {
      phy_data->start_mode = XGBE_MODE_SFI;
      DEBUG ((EFI_D_ERROR, "XGBE_MODE_SFI\n"));
    }
#endif
    phy_data->phydev_mode = XGBE_MDIO_MODE_CL22;
	xgbe_phy_sfp_setup (Private, phy_data);
    break;
  default:
    return EFI_UNSUPPORTED;
  }

  DEBUG ((EFI_D_ERROR, "Private->phy.supported = %x  phy_data->phydev_mode = %x \n" , Private->phy.supported , phy_data->phydev_mode));

  //for External PHY
  if ((phy_data->conn_type & XGBE_CONN_TYPE_MDIO) && (phy_data->phydev_mode != XGBE_MDIO_MODE_NONE)) {
    xgbe_set_ext_mii_mode(Private,(UINT32)phy_data->port_id,(UINT32)phy_data->phydev_mode);
  }

  if (phy_data->redrv && !phy_data->redrv_if) {
    DEBUG ((EFI_D_ERROR, "*****ERRRRR Port for External PHY\n"));
  }

  phy_data->phy_cdr_delay = XGBE_CDR_DELAY_INIT;
  Private->debugfs_an_cdr_workaround = 1;
  Private->phy.pause_autoneg = 1;
  Private->phy.tx_pause = 1;
  Private->phy.rx_pause = 1;
  Private->irq_reissue_support = 1;

  Private->phy.supported &= ~ADVERTISED_Pause;
  Private->phy.supported &= ~ADVERTISED_Asym_Pause;

  if(Private->phy.rx_pause)
  {
  	Private->phy.supported |=   ADVERTISED_Pause | ADVERTISED_Asym_Pause;
  }
  if(Private->phy.tx_pause)
  {
  	if(Private->phy.supported & ADVERTISED_Asym_Pause)
  		Private->phy.supported &= ~ADVERTISED_Asym_Pause;
  	else
  		Private->phy.supported |=  ADVERTISED_Asym_Pause;
  }

  if (Private->phy.supported & ADVERTISED_Autoneg) {
		Private->phy.autoneg = (UINTN)AUTONEG_ENABLE;
		Private->phy.speed = (UINTN)SPEED_UNKNOWN;
		Private->phy.duplex = (UINTN)DUPLEX_UNKNOWN;
   } else {
		Private->phy.autoneg = (UINTN) AUTONEG_DISABLE;
		Private->phy.speed = (UINTN)SPEED_UNKNOWN ;
		Private->phy.duplex = (UINTN)DUPLEX_FULL;
   }

  DEBUG ((EFI_D_ERROR, "Private->phy.supported = %x  phy_data->phydev_mode = %x \n" , Private->phy.supported , phy_data->phydev_mode));

  // Start in highest supported mode
  Private->phy_data = phy_data;

  return EFI_SUCCESS;
}

#if 1
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
  MmioWrite32 (XgmacBase + PORT_I2C_MUTEX, 0x80000000);
  gBS->Stall (1000);

  while(MmioRead32 (XgmacBase + PORT_I2C_MUTEX)){};

  do {
    MmioWrite32 (XgmacBase + PORT_I2C_MUTEX, MutexVal);
    gBS->Stall (1000);
    MutexSet1 = MmioRead32 (XgmacBase + PORT_I2C_MUTEX);
  } while (MutexSet1 != MutexVal);
}

#else
VOID
GetI2cOwnership (
  IN       UINT32 XgmacBase,
  IN       UINT8 MutexId
  )
{
	/*
		BIOS is silgle threaded and I2C is internal to XGBE IP .
		2 Xgbes can not use I2C's at same time. So I2C ownership is
		not required for PXE Boot. In case of driver it is multi threaded
		and both will run at same time. Hence OS needs I2C ownership but
		BIOS do not need it
	*/

}
#endif

VOID
PutI2cOwnership (
  IN       UINT32 XgmacBase,
  IN       UINT8 MutexId
  )
{
  if (getBitfieldReg32 (XgmacBase + PORT_I2C_MUTEX, 29, 2) == MutexId) {
    MmioWrite32 (XgmacBase + PORT_I2C_MUTEX, 0x80000000);
  }
}

BOOLEAN xgbe_phy_check_sfp_rx_los(XGBE_PHY_DATA *phy_data)
{
	UINT8 *sfp_extd = phy_data->sfp_eeprom.extd;

	if (!(sfp_extd[XGBE_SFP_EXTD_OPT1] & XGBE_SFP_EXTD_OPT1_RX_LOS))
		return FALSE;

	if (phy_data->sfp_gpio_mask & XGBE_GPIO_NO_RX_LOS)
		return FALSE;

	if (phy_data->sfp_gpio_inputs & (UINTN)((UINTN)1 << phy_data->sfp_gpio_rx_los))
		return TRUE;

	return FALSE;
}

BOOLEAN xgbe_phy_check_sfp_tx_fault(XGBE_PHY_DATA *phy_data)
{
	UINT8 *sfp_extd = phy_data->sfp_eeprom.extd;

	if (!(sfp_extd[XGBE_SFP_EXTD_OPT1] & XGBE_SFP_EXTD_OPT1_TX_FAULT))
		return FALSE;

	if (phy_data->sfp_gpio_mask & XGBE_GPIO_NO_TX_FAULT)
		return FALSE;

	if (phy_data->sfp_gpio_inputs & (UINTN)((UINTN)1 << phy_data->sfp_gpio_tx_fault))
		return TRUE;

	return FALSE;
}

BOOLEAN xgbe_phy_check_sfp_mod_absent(XGBE_PHY_DATA *phy_data)
{
    DEBUG ((EFI_D_ERROR, "1 << phy_data->sfp_gpio_mod_absent = %x  phy_data->sfp_gpio_inputs = %x  phy_data->sfp_gpio_mask = %x \n", (1 << phy_data->sfp_gpio_mod_absent), phy_data->sfp_gpio_inputs , phy_data->sfp_gpio_mask));

	if (phy_data->sfp_gpio_mask & XGBE_GPIO_NO_MOD_ABSENT)
		return FALSE;

	if (phy_data->sfp_gpio_inputs & (UINTN)((UINTN)1 << phy_data->sfp_gpio_mod_absent))
		return TRUE;

	return FALSE;
}


EFI_STATUS
XgbeSfpSignal (                      //    Pca9555
  ENET_DXE_PRIVATE_DATA *Private
  )
{
  XGBE_PHY_DATA *phy_data = Private->phy_data;
  XGBE_I2C_MASTER_PROTOCOL  *XgbEI2cMaster;
  UINT8                     PacketBuffer[sizeof (EFI_I2C_REQUEST_PACKET) + sizeof (EFI_I2C_OPERATION)];
  EFI_I2C_REQUEST_PACKET    *RequestPacket;
  EFI_I2C_OPERATION         *Operation;
  EFI_STATUS                Status;
  UINT8                     Offset;
  UINT8                     Data[2];
  UINT16                    Pca9555Data;
  UINT32                    XgmacBaseI2c;
  UINTN                     SlaveAdd;
  Status =                  EFI_SUCCESS;
  Pca9555Data =             0;
  Data[0] =                 0;
  Data[1] =                 0;
  Offset = 0;
  SlaveAdd = phy_data->sfp_gpio_address;
  phy_data->sfp_rx_los = 0;
  phy_data->sfp_tx_fault = 0;
  phy_data->sfp_mod_absent  = 1;
  XgmacBaseI2c = Private->xgmac_pdata.xgmac_regs + 0x1E000;

  Status = gBS->LocateProtocol (&gxGbEI2cMasterProtocolGuid, NULL, &XgbEI2cMaster);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "\nXGMAC XgbeSfpSignal: Could not Locate Protocol.\n"));
    return Status;
  }

  XgbEI2cMaster->BaseAddress = XgmacBaseI2c;
  XgbEI2cMaster->I2cInit (XgbEI2cMaster);
  RequestPacket = (EFI_I2C_REQUEST_PACKET*)PacketBuffer;
  Operation   = RequestPacket->Operation;
  RequestPacket->OperationCount = 2;
  Operation[0].Flags            = 0;
  Operation[0].LengthInBytes    = sizeof (UINT8);
  Operation[0].Buffer           = &Offset;
  Operation[1].Flags            = I2C_FLAG_READ;
  Operation[1].LengthInBytes    = sizeof (UINT16);
  Operation[1].Buffer           = Data;

  Status = XgbEI2cMaster->StartRequest (XgbEI2cMaster, SlaveAdd, RequestPacket, NULL, NULL);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "\nXGMAC: Failed to StartRequest.\n"));
    gBS->Stall (100);
    return Status;
  }

  phy_data->sfp_gpio_inputs = (Data[1] << 8) | Data[0];

  phy_data->sfp_mod_absent = xgbe_phy_check_sfp_mod_absent(Private->phy_data);

  DEBUG ((EFI_D_ERROR, "PCA9535 Data received phy_data->sfp_gpio_inputs = %x phy_data->sfp_mod_absent = %x \n", phy_data->sfp_gpio_inputs , phy_data->sfp_mod_absent));

  gBS->Stall (100);
  return Status;
}

EFI_STATUS
XgbeSfpPutMux (
  ENET_DXE_PRIVATE_DATA *Private
  )
{
  XGBE_PHY_DATA *phy_data = Private->phy_data;
  XGBE_I2C_MASTER_PROTOCOL  *XgbEI2cMaster;
  UINT8                     PacketBuffer[sizeof (EFI_I2C_REQUEST_PACKET) + sizeof (EFI_I2C_OPERATION)];
  EFI_I2C_REQUEST_PACKET    *RequestPacket;
  EFI_I2C_OPERATION         *Operation;
  UINT8                     Mux_Channel;
  UINTN                     SlaveAdd;
  UINT32                    XgmacBaseI2c;
  EFI_STATUS                Status;

  Status = EFI_SUCCESS;
  Mux_Channel = 0;
  SlaveAdd = phy_data->sfp_mux_address;
  Status = gBS->LocateProtocol (&gxGbEI2cMasterProtocolGuid, NULL, &XgbEI2cMaster);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "\nXGMAC: Could not Locate gxGbEI2cMasterProtocolGuid\n"));
    gBS->Stall (100);
    return Status;
  }
  XgmacBaseI2c = Private->xgmac_pdata.xgmac_regs + 0x1E000;
  //SET Base address
  XgbEI2cMaster->BaseAddress = XgmacBaseI2c;
  XgbEI2cMaster->I2cInit (XgbEI2cMaster);

  RequestPacket = (EFI_I2C_REQUEST_PACKET*)PacketBuffer;
  Operation   = RequestPacket->Operation;
  RequestPacket->OperationCount = 1;
  Operation[0].Flags            = 0;
  Operation[0].LengthInBytes    = sizeof (UINT8);
  Operation[0].Buffer           = &Mux_Channel;

  Status = XgbEI2cMaster->StartRequest (XgbEI2cMaster, SlaveAdd, RequestPacket, NULL, NULL);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "\nXGMAC: Failed to StartRequest for MUX.\n"));
    return Status;
  }
  DEBUG ((EFI_D_ERROR, "\nXGMAC: Success to StartRequest for MUX turned OFF.\n"));
  return Status;
}

EFI_STATUS
XgbeSfpGetMux (
  ENET_DXE_PRIVATE_DATA *Private
  )
{
  XGBE_PHY_DATA *phy_data = Private->phy_data;
  XGBE_I2C_MASTER_PROTOCOL  *XgbEI2cMaster;
  UINT8                     PacketBuffer[sizeof (EFI_I2C_REQUEST_PACKET) + sizeof (EFI_I2C_OPERATION)];
  EFI_I2C_REQUEST_PACKET    *RequestPacket;
  EFI_I2C_OPERATION         *Operation;
  UINT8                     Mux_Channel;
  UINTN                     SlaveAdd;
  UINT32                    XgmacBaseI2c;
  EFI_STATUS                Status;

  Status = EFI_SUCCESS;
  Mux_Channel = 1 << phy_data->sfp_mux_channel;
  SlaveAdd = phy_data->sfp_mux_address;
  DEBUG ((EFI_D_ERROR, "XGMAC: Mux SlaveAdd = %0x , Mux_Channel = %0x\n", SlaveAdd, Mux_Channel));

  Status = gBS->LocateProtocol (&gxGbEI2cMasterProtocolGuid, NULL, &XgbEI2cMaster);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "\nXGMAC: Could not Locate gxGbEI2cMasterProtocolGuid\n"));
    gBS->Stall (100);
    return Status;
  }
  XgmacBaseI2c = Private->xgmac_pdata.xgmac_regs + 0x1E000;
  //SET Base address
  XgbEI2cMaster->BaseAddress = XgmacBaseI2c;
  XgbEI2cMaster->I2cInit (XgbEI2cMaster);

  RequestPacket = (EFI_I2C_REQUEST_PACKET*)PacketBuffer;
  Operation   = RequestPacket->Operation;
  RequestPacket->OperationCount = 1;
  Operation[0].Flags            = 0;
  Operation[0].LengthInBytes    = sizeof (UINT8);
  Operation[0].Buffer           = &Mux_Channel;

  Status = XgbEI2cMaster->StartRequest (XgbEI2cMaster, SlaveAdd, RequestPacket, NULL, NULL);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "\nXGMAC: Failed to StartRequest for MUX.\n"));
    return Status;
  }
  return Status;
}

EFI_STATUS
XgbeSfpReadPhyAddr (
  ENET_DXE_PRIVATE_DATA *Private,
  UINT8                     baseAddr
  )
{
  XGBE_I2C_MASTER_PROTOCOL  *XgbEI2cMaster;
  UINT8                     PacketBuffer[sizeof (EFI_I2C_REQUEST_PACKET) + sizeof (EFI_I2C_OPERATION)];
  EFI_I2C_REQUEST_PACKET    *RequestPacket;
  EFI_I2C_OPERATION         *Operation;
  EFI_STATUS                Status;
  UINT8                     Offset;
  UINT8                     Data[2];
  UINT32                    XgmacBaseI2c;
  UINTN SlaveAdd;

  DEBUG ((EFI_D_ERROR, " XgbeSfpReadPhyAddr\n"));

  Status = EFI_SUCCESS;
  Offset = baseAddr;

  Status = XgbeSfpGetMux (Private);
  ASSERT (Status == EFI_SUCCESS);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  DEBUG ((EFI_D_ERROR, "Prepare to Start XgbeSfpReadPhyAddr\n"));
  SlaveAdd = XGBE_SFP_PHY_ADDRESS;
  XgmacBaseI2c = Private->xgmac_pdata.xgmac_regs + 0x1E000;

  Status = gBS->LocateProtocol (&gxGbEI2cMasterProtocolGuid, NULL, &XgbEI2cMaster);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "\nXGMAC Workaround: Could not Locate gxGbEI2cMasterProtocolGuid.\n"));
    gBS->Stall (100);
  }
  XgbEI2cMaster->BaseAddress = XgmacBaseI2c;
  XgbEI2cMaster->I2cInit (XgbEI2cMaster);
  RequestPacket = (EFI_I2C_REQUEST_PACKET*)PacketBuffer;
  Operation   = RequestPacket->Operation;
  RequestPacket->OperationCount = 2;
  Operation[0].Flags            = 0;
  Operation[0].LengthInBytes    = sizeof (UINT8);
  Operation[0].Buffer           = &Offset;
  Operation[1].Flags            = I2C_FLAG_READ;
  Operation[1].LengthInBytes    = sizeof (Data);
  Operation[1].Buffer           = Data;

  XgbeSfpPutMux (Private);

  if((Data[1] << 8) | Data[0])
  	return EFI_SUCCESS;
  else return EFI_DEVICE_ERROR;
}


EFI_STATUS
XgbeSfpReadEeprom (
  ENET_DXE_PRIVATE_DATA *Private
  )
{
  XGBE_PHY_DATA *phy_data = Private->phy_data;
  xgbe_sfp_eeprom sfp_eeprom ;
  XGBE_I2C_MASTER_PROTOCOL  *XgbEI2cMaster;
  UINT8                     PacketBuffer[sizeof (EFI_I2C_REQUEST_PACKET) + sizeof (EFI_I2C_OPERATION)];
  EFI_I2C_REQUEST_PACKET    *RequestPacket;
  EFI_I2C_OPERATION         *Operation;
  EFI_STATUS                Status;
  UINT8                     Offset;
  UINT32                    XgmacBaseI2c;
  UINTN SlaveAdd;
  UINT8 i = 0;
  UINT8 num_div = 0;

  Status = EFI_SUCCESS;
  Offset = 0;

  Status = XgbeSfpGetMux (Private);
  ASSERT (Status == EFI_SUCCESS);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  DEBUG ((EFI_D_ERROR, "Prepare to Start Reading Eeprom XgbeSfpReadEeprom\n"));
  DEBUG ((EFI_D_ERROR, "Private->xgmac_pdata.xgmac_regs =  %x\n" , Private->xgmac_pdata.xgmac_regs));
  SlaveAdd = 0x50;
  XgmacBaseI2c = Private->xgmac_pdata.xgmac_regs + 0x1E000;

  Status = gBS->LocateProtocol (&gxGbEI2cMasterProtocolGuid, NULL, &XgbEI2cMaster);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "\nXGMAC Workaround: Could not Locate gxGbEI2cMasterProtocolGuid.\n"));
    gBS->Stall (100);
  }
  DEBUG ((EFI_D_ERROR, "sizeof (sfp_eeprom) = %d \n",sizeof (sfp_eeprom) ));

  //RxFifoDepth is 16 and sfp_eeprom is 128. To macth size same as RxFifoDepth lets keep division same as that.
  num_div = 8;

  XgbEI2cMaster->BaseAddress = XgmacBaseI2c;
  XgbEI2cMaster->I2cInit (XgbEI2cMaster);
  RequestPacket = (EFI_I2C_REQUEST_PACKET*)PacketBuffer;
  Operation   = RequestPacket->Operation;
  RequestPacket->OperationCount = 2;
  Operation[0].Flags            = 0;
  Operation[0].LengthInBytes    = sizeof (UINT8);
  Operation[0].Buffer           = &Offset;
  Operation[1].Flags            = I2C_FLAG_READ;
  Operation[1].LengthInBytes    = sizeof (sfp_eeprom)/num_div;
  Operation[1].Buffer           = (UINT8*)&sfp_eeprom;

  for(i = 0 ; i < num_div ; i++){
	  Offset = (i * (sizeof (sfp_eeprom)/num_div));
	  Operation[1].Buffer           = (UINT8*)&sfp_eeprom + (i * (sizeof (sfp_eeprom)/num_div));
	  Status = XgbEI2cMaster->StartRequest (XgbEI2cMaster, SlaveAdd, RequestPacket, NULL, NULL);
	  gBS->Stall (100);
  }

  CopyMem (&phy_data->sfp_eeprom, &sfp_eeprom, sizeof (sfp_eeprom));

  XgbeSfpPutMux (Private);
  return Status;
}
BOOLEAN
xgbe_phy_sfp_verify_eeprom (
  UINT8 cc_in,
  UINT8 *buf,
  UINTN len
  )
{
  UINT8 cc;
  for (cc = 0; len; buf++, len--) {
    cc += *buf;
  }
  return (cc == cc_in) ? TRUE : FALSE;
}

BOOLEAN
XgbeSfpBitRate (
  xgbe_sfp_eeprom *sfp_eeprom,
  xgbe_sfp_speed sfp_speed
  )
{
  UINT8 *sfp_base;
  UINT8  min;
  UINT8  max;

  sfp_base = sfp_eeprom->base;

  switch (sfp_speed) {
  case XGBE_SFP_SPEED_1000:
    min = XGBE_SFP_BASE_BR_1GBE_MIN;
    max = XGBE_SFP_BASE_BR_1GBE_MAX;
    break;
  case XGBE_SFP_SPEED_10000:
    min = XGBE_SFP_BASE_BR_10GBE_MIN;
    max = XGBE_SFP_BASE_BR_10GBE_MAX;
    break;
  default:
    return FALSE;
  }
return ((sfp_base[XGBE_SFP_BASE_BR] >= min) &&
    (sfp_base[XGBE_SFP_BASE_BR] <= max));
}

EFI_STATUS
XgbeSfpParseEeprom (
  ENET_DXE_PRIVATE_DATA *Private
  )
{
  XGBE_PHY_DATA *phy_data = Private->phy_data;
  xgbe_sfp_eeprom *sfp_eeprom = &phy_data->sfp_eeprom;
  UINT8 *sfp_base;

  phy_data->sfp_base = XGBE_SFP_BASE_UNKNOWN;
  phy_data->sfp_cable = XGBE_SFP_CABLE_UNKNOWN;
  phy_data->sfp_speed = XGBE_SFP_SPEED_UNKNOWN;

  sfp_base = sfp_eeprom->base;
  DEBUG ((EFI_D_ERROR, "sfp_base[XGBE_SFP_BASE_CABLE] =%x \n", sfp_base[XGBE_SFP_BASE_CABLE]));
  DEBUG ((EFI_D_ERROR, "sfp_base[XGBE_SFP_BASE_CU_CABLE_LEN]; =%x \n", sfp_base[XGBE_SFP_BASE_CU_CABLE_LEN]));
  DEBUG ((EFI_D_ERROR, "sfp_base[XGBE_SFP_BASE_10GBE_CC]; =%x \n", sfp_base[XGBE_SFP_BASE_10GBE_CC]));
  DEBUG ((EFI_D_ERROR, "sfp_base[XGBE_SFP_BASE_1GBE_CC]; =%x \n", sfp_base[XGBE_SFP_BASE_1GBE_CC]));

  if (sfp_base[XGBE_SFP_BASE_ID] != XGBE_SFP_ID_SFP) {
    return EFI_UNSUPPORTED;
  }
  if (sfp_base[XGBE_SFP_BASE_EXT_ID] != XGBE_SFP_EXT_ID_SFP) {
    return EFI_UNSUPPORTED;
  }

  /* Update transceiver signals (eeprom extd/options) */
  phy_data->sfp_tx_fault = xgbe_phy_check_sfp_tx_fault(phy_data);
  phy_data->sfp_rx_los = xgbe_phy_check_sfp_rx_los(phy_data);

  if (sfp_base[XGBE_SFP_BASE_CABLE] & XGBE_SFP_BASE_CABLE_PASSIVE) {
    phy_data->sfp_cable = XGBE_SFP_CABLE_PASSIVE;
    phy_data->sfp_cable_len = sfp_base[XGBE_SFP_BASE_CU_CABLE_LEN];
  }
  else
    phy_data->sfp_cable = XGBE_SFP_CABLE_ACTIVE;

  /* Determine the type of SFP */
  if (sfp_base[XGBE_SFP_BASE_10GBE_CC] & XGBE_SFP_BASE_10GBE_CC_SR) {
    phy_data->sfp_base = XGBE_SFP_BASE_10000_SR;
  } else if (sfp_base[XGBE_SFP_BASE_10GBE_CC] & XGBE_SFP_BASE_10GBE_CC_LR) {
    phy_data->sfp_base = XGBE_SFP_BASE_10000_LR;
  } else if (sfp_base[XGBE_SFP_BASE_10GBE_CC] & XGBE_SFP_BASE_10GBE_CC_LRM) {
    phy_data->sfp_base = XGBE_SFP_BASE_10000_LRM;
  } else if (sfp_base[XGBE_SFP_BASE_10GBE_CC] & XGBE_SFP_BASE_10GBE_CC_ER) {
    phy_data->sfp_base = XGBE_SFP_BASE_10000_ER;
  } else if (sfp_base[XGBE_SFP_BASE_1GBE_CC] & XGBE_SFP_BASE_1GBE_CC_SX) {
    phy_data->sfp_base = XGBE_SFP_BASE_1000_SX;
  } else if (sfp_base[XGBE_SFP_BASE_1GBE_CC] & XGBE_SFP_BASE_1GBE_CC_LX) {
    phy_data->sfp_base = XGBE_SFP_BASE_1000_LX;
  } else if (sfp_base[XGBE_SFP_BASE_1GBE_CC] & XGBE_SFP_BASE_1GBE_CC_T) {
    phy_data->sfp_base = XGBE_SFP_BASE_1000_T;
	// SFP 1G is not functional for SGMII_1000 mode. Lets use MODE_X For SFG 1G default
    //phy_data->sfp_base = XGBE_SFP_BASE_1000_CX;  //support only CX for 1000_T also
  } else if (sfp_base[XGBE_SFP_BASE_1GBE_CC] & XGBE_SFP_BASE_1GBE_CC_CX) {
    phy_data->sfp_base = XGBE_SFP_BASE_1000_CX;
  } else if ((phy_data->sfp_cable == XGBE_SFP_CABLE_PASSIVE) &&
   XgbeSfpBitRate (sfp_eeprom, XGBE_SFP_SPEED_10000)) {
    phy_data->sfp_base = XGBE_SFP_BASE_10000_CR;
  }

  switch (phy_data->sfp_base) {
  case XGBE_SFP_BASE_1000_T:
    phy_data->sfp_speed = XGBE_SFP_SPEED_100_1000;
    break;
  case XGBE_SFP_BASE_1000_SX:
  case XGBE_SFP_BASE_1000_LX:
  case XGBE_SFP_BASE_1000_CX:
    phy_data->sfp_speed = XGBE_SFP_SPEED_1000;
    break;
  case XGBE_SFP_BASE_10000_SR:
  case XGBE_SFP_BASE_10000_LR:
  case XGBE_SFP_BASE_10000_LRM:
  case XGBE_SFP_BASE_10000_ER:
  case XGBE_SFP_BASE_10000_CR:
    phy_data->sfp_speed = XGBE_SFP_SPEED_10000;
    break;
  default:
    break;
  }
  DEBUG ((EFI_D_ERROR, "phy_data->sfp_speed  =%x  phy_data->sfp_base = %x \n", phy_data->sfp_speed , phy_data->sfp_base));
  return EFI_SUCCESS;
}

VOID
STATIC
xgbe_phy_sfp_phy_settings (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  XGBE_PHY_DATA *phy_data = pdata->phy_data;

  pdata->phy.supported = 0;

  if (phy_data->sfp_mod_absent) {
    pdata->phy.speed = (UINTN)SPEED_UNKNOWN;
    pdata->phy.duplex = (UINTN)DUPLEX_UNKNOWN;
    pdata->phy.autoneg = (UINTN)AUTONEG_ENABLE;
	pdata->phy.pause_autoneg = (UINTN)AUTONEG_ENABLE;
	pdata->phy.supported |=   ADVERTISED_Pause | ADVERTISED_Asym_Pause | ADVERTISED_Autoneg | ADVERTISED_FIBER | ADVERTISED_TP;
  }
  switch (phy_data->sfp_base) {
  case XGBE_SFP_BASE_1000_T:
  case XGBE_SFP_BASE_1000_SX:
  case XGBE_SFP_BASE_1000_LX:
  case XGBE_SFP_BASE_1000_CX:
    pdata->phy.speed = (UINTN)SPEED_1000;
    pdata->phy.duplex = (UINTN)DUPLEX_UNKNOWN;
    pdata->phy.autoneg = (UINTN)AUTONEG_ENABLE;
    pdata->phy.pause_autoneg = (UINTN)AUTONEG_ENABLE;
	pdata->phy.supported |=   ADVERTISED_Pause | ADVERTISED_Asym_Pause | ADVERTISED_Autoneg;
	if (phy_data->sfp_base == XGBE_SFP_BASE_1000_T) {
		if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_100){
			pdata->phy.supported |=   ADVERTISED_100baseT_Full ;
		}
		if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000)
			pdata->phy.supported |= ADVERTISED_1000baseT_Full;
	} else {
		if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000)
			pdata->phy.supported |= ADVERTISED_1000baseX_Full ;
	}
	// SFP 1G is not functional for SGMII_1000 mode. Lets use MODE_X For SFG 1G default
	pdata->phy.supported |= ADVERTISED_1000baseX_Full ;
    break;
  case XGBE_SFP_BASE_10000_SR:
  case XGBE_SFP_BASE_10000_LR:
  case XGBE_SFP_BASE_10000_LRM:
  case XGBE_SFP_BASE_10000_ER:
  case XGBE_SFP_BASE_10000_CR:
    pdata->phy.speed = (UINTN)SPEED_10000;
    pdata->phy.duplex = (UINTN)DUPLEX_FULL;
    pdata->phy.autoneg = (UINTN)AUTONEG_DISABLE;
	pdata->phy.pause_autoneg = (UINTN)AUTONEG_DISABLE;
	if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_10000){
		switch (phy_data->sfp_base) {
		case XGBE_SFP_BASE_10000_SR:
			pdata->phy.supported |= ADVERTISED_10000baseSR_Full;
			break;
		case XGBE_SFP_BASE_10000_LR:
			pdata->phy.supported |= ADVERTISED_10000baseLR_Full;
			break;
		case XGBE_SFP_BASE_10000_LRM:
			pdata->phy.supported |= ADVERTISED_10000baseLRM_Full;
			break;
		case XGBE_SFP_BASE_10000_ER:
			pdata->phy.supported |= ADVERTISED_10000baseER_Full;
			break;
		case XGBE_SFP_BASE_10000_CR:
			pdata->phy.supported |= ADVERTISED_10000baseCR_Full;
			break;
		default:
			break;
		}
	}
    break;
  default:
   	pdata->phy.speed = (UINTN)SPEED_UNKNOWN;
	pdata->phy.duplex = (UINTN)DUPLEX_UNKNOWN;
	pdata->phy.autoneg = (UINTN)AUTONEG_DISABLE;
	pdata->phy.pause_autoneg = (UINTN)AUTONEG_DISABLE;
	break;
  }

	switch (phy_data->sfp_base) {
		case XGBE_SFP_BASE_1000_T:
		case XGBE_SFP_BASE_1000_CX:
		case XGBE_SFP_BASE_10000_CR:
			pdata->phy.supported |= ADVERTISED_TP;
			break;
		default:
			pdata->phy.supported |= ADVERTISED_FIBER;
			break;
	}

}

VOID
xgbe_phy_sfp_external_phy (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  XGBE_PHY_DATA *phy_data = pdata->phy_data;
  EFI_STATUS Status;

  phy_data->sfp_phy_avail = 0;

  if (phy_data->sfp_base != XGBE_SFP_BASE_1000_T) {
    return;
  }

  /* Check access to the PHY by reading CTRL1 */
  Status = XgbeSfpReadPhyAddr(pdata, MII_BMCR);
	if (Status != EFI_SUCCESS)
		return;

  phy_data->sfp_phy_avail = 1;

}

EFI_STATUS
XgbeDetectSfp (
  IN  ENET_DXE_PRIVATE_DATA *Private
  )
{
  XGBE_PHY_DATA *phy_data = Private->phy_data;
  UINT32 XgmacBase;
  UINT8 PortNum;
  EFI_STATUS Status;
  Status = EFI_SUCCESS;
  PortNum = phy_data->port_id;
  phy_data->sfp_rx_los = 0;
  phy_data->sfp_tx_fault = 0;
  phy_data->sfp_mod_absent = 1;
  phy_data->sfp_diags = 0;
  phy_data->sfp_base = XGBE_SFP_BASE_UNKNOWN;
  phy_data->sfp_cable = XGBE_SFP_CABLE_UNKNOWN;
  phy_data->sfp_speed = XGBE_SFP_SPEED_UNKNOWN;
  SetMem (&phy_data->sfp_eeprom, sizeof (phy_data->sfp_eeprom), 0);

  XgmacBase = Private->xgmac_pdata.xgmac_regs;
  GetI2cOwnership (XgmacBase, PortNum);

  Status = XgbeSfpSignal (Private);
  if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "\nXGMAC: Failed SFP.\n"));
      PutI2cOwnership (XgmacBase, PortNum);
      return EFI_NOT_FOUND;
  }
  if (phy_data->sfp_mod_absent) {
      DEBUG ((EFI_D_ERROR, "\nXGMAC: SFP Module Absent, phy_data->sfp_mod_absent = %0x\n", phy_data->sfp_mod_absent));
      PutI2cOwnership (XgmacBase, PortNum);
      return EFI_NOT_FOUND;
  }

  Status = XgbeSfpReadEeprom (Private);
  if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "\nXGMAC: Failed XgbeSfpReadEeprom.\n"));
      PutI2cOwnership (XgmacBase, PortNum);
      return EFI_NOT_FOUND;
  }

  Status =  XgbeSfpParseEeprom (Private);

  xgbe_phy_sfp_external_phy (Private);
  xgbe_phy_sfp_phy_settings (Private);
  if(phy_data->sfp_phy_avail){
    xgbe_phy_external_phy_quirks(Private);
  }else if (phy_data->sfp_base == XGBE_SFP_BASE_1000_T){
    Status = EFI_NOT_FOUND;
  }
  PutI2cOwnership (XgmacBase, PortNum);
  return Status;
}

EFI_STATUS
xgbe_phy_start (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
    XGBE_PHY_DATA *phy_data = pdata->phy_data;
    EFI_STATUS    Status;
    DEBUG ((EFI_D_ERROR, "xgbe_phy_start phy_data->port_mode: %x \n", phy_data->port_mode));
    XgbeHwinitDelay();
    switch (phy_data->port_mode) {
        case XGBE_PORT_MODE_BACKPLANE:
        case XGBE_PORT_MODE_BACKPLANE_2500:
            Status = phy_init_hw(pdata);
            if (EFI_ERROR (Status)) {
                DEBUG ((EFI_D_ERROR, "PHY INIT FW Failed \n"));
                return EFI_NOT_FOUND;
            }
            break;
        case XGBE_PORT_MODE_1000BASE_T:
            DEBUG ((EFI_D_ERROR, "Case forPHY INIT FW \n"));
            Status = phy_init_hw(pdata);
            if (EFI_ERROR (Status)) {
                DEBUG ((EFI_D_ERROR, "PHY INIT FW Failed \n"));
                return EFI_NOT_FOUND;
            }
            break;
        case XGBE_PORT_MODE_1000BASE_X:
        case XGBE_PORT_MODE_NBASE_T:
        case XGBE_PORT_MODE_10GBASE_T:
        case XGBE_PORT_MODE_10GBASE_R:
            DEBUG ((EFI_D_ERROR, "PXE Boot EFI_UNSUPPORTED \n"));
            return EFI_UNSUPPORTED;
        case XGBE_PORT_MODE_SFP:
            DEBUG ((EFI_D_ERROR, "Case for XgbeDetectSfp \n"));
            Status = XgbeDetectSfp (pdata);
            if (EFI_ERROR (Status)) {
                DEBUG ((EFI_D_ERROR, "XgbeDetectSfp SFP NOT FOUND \n"));
                return EFI_NOT_FOUND;
            }
            break;
        default:
            return EFI_UNSUPPORTED;
    }

    DEBUG ((EFI_D_ERROR, "pdata->phy.autoneg = %x  pdata->phy.speed = %x   pdata->phy.duplex = %x \n" , pdata->phy.autoneg , pdata->phy.speed , pdata->phy.duplex));
    DEBUG ((EFI_D_ERROR, "Private->phy.supported = %x  phy_data->phydev_mode = %x \n" , pdata->phy.supported , phy_data->phydev_mode));


    /* Set initial mode - call the mode setting routines
    * directly to insure we are properly configured
    */
    if (xgbe_phy_use_mode(pdata, XGBE_MODE_KR)) {
        xgbe_kr_mode(pdata);
    } else if (xgbe_phy_use_mode(pdata, XGBE_MODE_KX_2500)) {
        xgbe_kx_2500_mode(pdata);
    } else if (xgbe_phy_use_mode(pdata, XGBE_MODE_KX_1000)) {
        xgbe_kx_1000_mode(pdata);
    } else if (xgbe_phy_use_mode(pdata, XGBE_MODE_SFI)) {
        xgbe_sfp_mode(pdata);
    } else if (xgbe_phy_use_mode(pdata, XGBE_MODE_X)) {
        xgbe_x_mode(pdata);
    } else if (xgbe_phy_use_mode(pdata, XGBE_MODE_SGMII_1000)) {
        xgbe_sgmii_1000_mode(pdata);
    } else if (xgbe_phy_use_mode(pdata, XGBE_MODE_SGMII_100)) {
        xgbe_sgmii_100_mode(pdata);
    }

    xgbe_phy_an_mode (pdata);

    xgbe_phy_cdr_track(pdata);

    XgbeHwinitDelay();
    return EFI_SUCCESS;
}

/*********************************************************************************
 * Name: XgbeReadEeprom
 *
 * Description
 *   Call to Read XGBE I2C devices
 *
 * Input
 *   XgbeBaseAdd:   XGBE Base address.\
 *   SlaveAdd:      Slave Address of IC
 *   Offset:        Offset to write to
 *   DataLength:    Size of Data to be Read from device.
 *
 * Output
 *   Data read from device
 *
 *********************************************************************************/
UINT16
XgbeReadEeprom (
  UINT32 XgbeBaseAdd,
  UINT8 SlaveAdd,
  UINT8 Offset,
  UINT16 DataLength
  )
{
  XGBE_I2C_MASTER_PROTOCOL  *XgbEI2cMaster;
  UINT8                     PacketBuffer[sizeof (EFI_I2C_REQUEST_PACKET) + sizeof (EFI_I2C_OPERATION)];
  EFI_I2C_REQUEST_PACKET    *RequestPacket;
  EFI_I2C_OPERATION         *Operation;
  EFI_STATUS                Status;
//  UINT8                     Offset;
  UINT8                     Data[2];
  UINT16                    Pca9555Data;
  UINT32                    XgmacBaseI2c;

  Status =                  EFI_SUCCESS;
  Pca9555Data =             0;
  Data[0] =                 0;
  Data[1] =                 0;

  XgmacBaseI2c = XgbeBaseAdd + 0x1E000;
  Status = gBS->LocateProtocol (&gxGbEI2cMasterProtocolGuid, NULL, &XgbEI2cMaster);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "\nXGMAC Workaround: Could not Locate IC Protocol.\n"));
    gBS->Stall (100);
  }

  XgbEI2cMaster->BaseAddress = XgmacBaseI2c;
  XgbEI2cMaster->I2cInit (XgbEI2cMaster);
  RequestPacket = (EFI_I2C_REQUEST_PACKET*)PacketBuffer;
  Operation   = RequestPacket->Operation;
  RequestPacket->OperationCount = 2;
  Operation[0].Flags            = 0;
  Operation[0].LengthInBytes    = sizeof (UINT8);
  Operation[0].Buffer           = &Offset;
  Operation[1].Flags            = I2C_FLAG_READ;
  Operation[1].LengthInBytes    = DataLength;
  Operation[1].Buffer           = Data;

  Status = XgbEI2cMaster->StartRequest (XgbEI2cMaster, SlaveAdd, RequestPacket, NULL, NULL);
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
 *   Call to write to XGBE IC devices

 *
 * Input
 *   XgbeBaseAdd : XGBE Base address.\
 *   SlaveAdd:     Slave Address of IC
 *   Offset:       Offset to write to
 *   Data:         Data to be written on device.
 *
 * Output
 *
 *********************************************************************************/

VOID
XgbeWriteEeprom (
  UINT32 XgbeBaseAdd,
  UINT8 SlaveAdd,
  UINT8 Offset,
  UINT16 Data
  )
{
  XGBE_I2C_MASTER_PROTOCOL  *XgbEI2cMaster;
  UINT8                     PacketBuffer[sizeof (EFI_I2C_REQUEST_PACKET) + sizeof (EFI_I2C_OPERATION)];
  EFI_I2C_REQUEST_PACKET    *RequestPacket;
  EFI_I2C_OPERATION         *Operation;
  EFI_STATUS                Status;
  UINT8                     Buffer[3];
  UINT32                    XgmacBaseI2c;
  Status =                  EFI_SUCCESS;
  XgmacBaseI2c = XgbeBaseAdd + 0x1E000;
  Status = gBS->LocateProtocol (&gxGbEI2cMasterProtocolGuid, NULL, &XgbEI2cMaster);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "\nXGMAC Workaround: Could not Locate IC Protocol.\n"));
    gBS->Stall (100);
  }
  XgbEI2cMaster->BaseAddress = XgmacBaseI2c;
  XgbEI2cMaster->I2cInit (XgbEI2cMaster);

  //Prepare write data buffer
  Buffer[0] = Offset;
  Buffer[1] = (UINT8)(Data & 0x00FF); //Low byte
  Buffer[2] = (UINT8)(Data >> 8);     //High byte

  RequestPacket = (EFI_I2C_REQUEST_PACKET*)PacketBuffer;
  Operation   = RequestPacket->Operation;
  RequestPacket->OperationCount = 1;
  Operation[0].Flags            = 0;
  Operation[0].LengthInBytes    = 3;
  Operation[0].Buffer           = &Buffer[0];

  Status = XgbEI2cMaster->StartRequest (XgbEI2cMaster, SlaveAdd, RequestPacket, NULL, NULL);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "\nXGMAC: Failed to StartRequest.\n"));
  }
}

EFI_STATUS
XgbeBaseAddr (
        OUT ENET_DXE_PRIVATE_DATA *Private
  )
{
  PCI_ADDR  PciAddress;
  AMD_FABRIC_TOPOLOGY_SERVICES2_PROTOCOL *FabricTopology;
  EFI_STATUS   Status;
  UINTN     BusNumberBase;
  UINTN     SocketNum;
  UINTN     DieNum;
  UINT16    BusMasterEn;
  UINT8     SecBusDie0;
  UINT8     SecBusDie1;
  UINT32    Xgmac0_Base;
  UINT32    Xgmac1_Base;
  UINT32    Xgmac2_Base;
  UINT32    Xgmac3_Base;
  UINT32    Xpcs0_Base;
  UINT32    Xpcs1_Base;
  UINT32    Xpcs2_Base;
  UINT32    Xpcs3_Base;
  UINT32    XgmacBase;
  UINT8     i;
  UINT8     port;
  UINT32    Value;
#if 0
  UINT16    DataSize;
  UINT16    Data;
  UINT8     SlaveAdd;
  UINT32    XgbeBaseAdd;
  UINT8     Offset;
#endif


  XgmacBase = 0;
  Xgmac0_Base = 0;
  Xgmac1_Base = 0;
  Xgmac2_Base = 0;
  Xgmac3_Base = 0;
  Xpcs0_Base = 0;
  Xpcs1_Base = 0;
  Xpcs2_Base = 0;
  Xpcs3_Base = 0;
  BusNumberBase = 0;
  SocketNum = 0;
  DieNum = 0;
  BusMasterEn = 0;
  SecBusDie0 = 0;
  SecBusDie1 = 0;
  Status = EFI_SUCCESS;

  //Get Base address for XGMAC and  XPCS
  // Port 0, 1, 2, & 3 are on Socket 0, Die0
  //Get the Base BUS# first.
  Status = gBS->LocateProtocol (
                &gAmdFabricTopologyServices2ProtocolGuid,
                NULL,
                &FabricTopology
                );

  if (FabricTopology->GetRootBridgeInfo (FabricTopology, SocketNum, DieNum, 0, NULL, &BusNumberBase, NULL, NULL, NULL, NULL) != EFI_SUCCESS) {
    Status = EFI_DEVICE_ERROR;
  }
  DEBUG ((EFI_D_ERROR, "BusNumberBase: %x \n", BusNumberBase));

  PciAddress.AddressValue = (MAKE_SBDFO (0, BusNumberBase, 0x8, FUNC_2, 0x19));
  DEBUG ((EFI_D_ERROR, "PciAddress.AddressValue: %x \n", PciAddress.AddressValue));
  SecBusDie0 = PciRead8 (PciAddress.AddressValue);

  //Port 0
  PciAddress.AddressValue = (MAKE_SBDFO (0, SecBusDie0, 0x0, FUNC_1, 0x4));
  BusMasterEn = PciRead16 (PciAddress.AddressValue);
  BusMasterEn |= 0x6;
  PciWrite32 (PciAddress.AddressValue, *((UINT32 *) &BusMasterEn));

  PciAddress.AddressValue = (MAKE_SBDFO (0, SecBusDie0, 0x0, FUNC_1, 0x10));
  Xgmac0_Base = PciRead32 (PciAddress.AddressValue);

  PciAddress.AddressValue = (MAKE_SBDFO (0, SecBusDie0, 0x0, FUNC_1, 0x14));
  Xpcs0_Base = PciRead32 (PciAddress.AddressValue);
  DEBUG ((EFI_D_ERROR, "Xgmac0_Base: %x \n", Xgmac0_Base));
  DEBUG ((EFI_D_ERROR, "Xpcs0_Base: %x \n", Xpcs0_Base));

  //port 1
  PciAddress.AddressValue = (MAKE_SBDFO (0, SecBusDie0, 0x0, FUNC_2, 0x4));
  BusMasterEn = PciRead16 (PciAddress.AddressValue);
  BusMasterEn |= 0x6;
  PciWrite16 (PciAddress.AddressValue, BusMasterEn);

  PciAddress.AddressValue = (MAKE_SBDFO (0, SecBusDie0, 0x0, FUNC_2, 0x10));
  Xgmac1_Base = PciRead32 (PciAddress.AddressValue);
  PciAddress.AddressValue = (MAKE_SBDFO (0, SecBusDie0, 0x0, FUNC_2, 0x14));
  Xpcs1_Base = PciRead32 (PciAddress.AddressValue);

  DEBUG ((EFI_D_ERROR, "Xgmac1_Base: %x \n", Xgmac1_Base));
  DEBUG ((EFI_D_ERROR, "Xpcs1_Base: %x \n", Xpcs1_Base));

  //assign addresses for each port. Change for port 0 only
  if (mXgbeData.XgbeBusFunc == 0x0001) {
    Private->xgmac_pdata.xgmac_regs = Xgmac0_Base;
    Private->xpcs_regs = Xpcs0_Base;
    DEBUG ((EFI_D_ERROR, "XGmac = %x \n Xpcs = %x \n", Private->xgmac_pdata.xgmac_regs, Private->xpcs_regs ));
  } else if (mXgbeData.XgbeBusFunc == 0x0002) {
    Private->xgmac_pdata.xgmac_regs = Xgmac1_Base;
    Private->xpcs_regs = Xpcs1_Base;
    DEBUG ((EFI_D_ERROR, "XGmac1 = %x \n Xpcs1 = %x \n", Private->xgmac_pdata.xgmac_regs, Private->xpcs_regs ));
  }
  Private->XgmacBus = SecBusDie0;
  DEBUG ((EFI_D_ERROR, "XGmac = %x \n Xpcs = %x \n Bus = %x \n", Private->xgmac_pdata.xgmac_regs, Private->xpcs_regs, Private->XgmacBus ));
  Private->i2c_regs = Private->XgmacBus + XGBE_I2C_CTRL_OFFSET;

   //Program for XGBE ECC Interrupt.
  for (port = 0; port < 2; port++) {
    if (port == 0) {
      if(Xgmac0_Base == 0xFFFFFFFF)
        continue;
      XgmacBase = Xgmac0_Base;
    }
    if (port == 1) {
      if(Xgmac1_Base == 0xFFFFFFFF)
        break;
      XgmacBase = Xgmac1_Base;
    }

	if (getBitfieldReg32 (XgmacBase + 0x1d030, 0, 6) == 0 ) {
      DEBUG ((EFI_D_ERROR, " ECC already addressed for Port %x \n", port));
      continue;
    }
    DEBUG ((EFI_D_ERROR, "XGmac Start ECC programming  \n" ));
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

#if 0 // this code is already taken care by BIOS driver.
  SlaveAdd = (UINT8)(PCA9555_ADDRESS + getBitfieldReg32 (Private->xgmac_pdata.xgmac_regs+ENET_PORT_PROPERTY_3, 8, 3));  //GPIO_ADDR
  DataSize = sizeof (UINT16);
  XgbeBaseAdd = Xgmac0_Base;
  Offset = (UINT8)6;
  Data = XgbeReadEeprom (XgbeBaseAdd, SlaveAdd, Offset, DataSize);
  DEBUG ((EFI_D_ERROR, "Device23 Data before = %x \n", Data ));
  // I/O 0_7 to I/O 0_0 (  0 => output and 1 => input)
  // (0111 1111 = 0x7F)
  // I/O 1_7 to I/O 1_0 (0,1,1,1,1,1,1,1) ( 0111 1111 = 0x7F)
  Data &= 0x7F7F; // This statement make sure output set as 0 properly
  Data |= 0x7F7F; // This statement make sure input set as 1 properly
  XgbeWriteEeprom (XgbeBaseAdd, SlaveAdd, Offset, Data);
  Data = (UINT16)0;
  Data = XgbeReadEeprom (XgbeBaseAdd, SlaveAdd, Offset, DataSize);
  DEBUG ((EFI_D_ERROR, "Device23 Data after = %x \n", Data ));

  Offset = (UINT8)2;
  Data = XgbeReadEeprom (XgbeBaseAdd, SlaveAdd, Offset, DataSize);
  // SFP+_XGB1_DISABLE (I/O 0_7) =>  High:Disable the transmitter  Low : Enable the Transmiter
  // SFP+_XGB0_DISABLE (I/O 1_7) =>  High:Disable the transmitter  Low : Enable the Transmiter
  // Input port value is ignored even if we configure any value.
  Data &= 0x0000;
  XgbeWriteEeprom (XgbeBaseAdd, SlaveAdd, Offset, Data);

  Data = (UINT16)0;
  Data = XgbeReadEeprom (XgbeBaseAdd, SlaveAdd, Offset, DataSize);
  DEBUG ((EFI_D_ERROR, "Device23 Data after 2 = %x \n", Data ));
#endif
  return Status;
}

VOID
STATIC
xgbe_phy_start_ratechange (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  UINT32 XgmacBase;
  XgmacBase = pdata->xgmac_pdata.xgmac_regs;

  if (!getBitfieldReg32 (XgmacBase + 0x1d064, 0, 1)) {
    DEBUG ((EFI_D_ERROR, "firmware mailbox GOOD for ratechange command \n"));
    return;
  }
  DEBUG ((EFI_D_ERROR, "firmware mailbox not ready for command \n"));
}

VOID
STATIC
xgbe_phy_complete_ratechange (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  UINTN wait;
  UINT32 XgmacBase;
  XgmacBase = pdata->xgmac_pdata.xgmac_regs;

  //Wait for command to complete
  wait = XGBE_RATECHANGE_COUNT;
  while (wait--) {
    if (!getBitfieldReg32 (XgmacBase + 0x1d064, 0, 1)) {
      DEBUG ((EFI_D_ERROR, "rate Change Successfull \n"));
      return;
    }
    gBS->Stall (100);
  }
  DEBUG ((EFI_D_ERROR, "firmware mailbox command did not complete \n"));
}

VOID
xgbe_phy_power_off (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  XGBE_PHY_DATA *phy_data = pdata->phy_data;
  UINT32 XgmacBase;
  XgmacBase = pdata->xgmac_pdata.xgmac_regs;
  pdata->xprop_regs = pdata->xgmac_pdata.xgmac_regs + XGBE_MAC_CTRL_OFFSET;
  pdata->xi2c_regs = pdata->xgmac_pdata.xgmac_regs + XGBE_I2C_CTRL_OFFSET;
  DEBUG ((EFI_D_ERROR, "xgbe_phy_power_off start \n"));
  xgbe_phy_start_ratechange (pdata);

  // Call FW to make the change
  MmioWrite32 (XgmacBase + 0x1d068, 0);   //scratch 0
  MmioWrite32 (XgmacBase + 0x1d06c, 0);
  MmioWrite32 (XgmacBase + 0x1d060, 1);

  xgbe_phy_complete_ratechange (pdata);
  phy_data->cur_mode = XGBE_MODE_UNKNOWN;
  DEBUG ((EFI_D_ERROR, "phy powered off\n"));
}

UINTN
xgbe_phy_get_comm_ownership (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  UINT32  mutex_id;
  UINTN MutexMdio;
  UINTN MutexI2c;
  XGBE_PHY_DATA *phy_data = pdata->phy_data;
  DEBUG ((EFI_D_ERROR, "xgbe_phy_get_comm_ownership\n"));
  if (phy_data->comm_owned) {
    return 0;
  }
  // Clear the mutexes
  XP_IOWRITE (pdata, XP_I2C_MUTEX, XGBE_MUTEX_RELEASE);
  XP_IOWRITE (pdata, XP_MDIO_MUTEX, XGBE_MUTEX_RELEASE);

  mutex_id = 0;
  XP_SET_BITS (mutex_id, XP_I2C_MUTEX, ID, phy_data->port_id);
  XP_SET_BITS (mutex_id, XP_I2C_MUTEX, ACTIVE, 1);

  do {
    MutexI2c = XP_IOREAD (pdata, XP_I2C_MUTEX);
    MutexMdio = XP_IOREAD (pdata, XP_MDIO_MUTEX);
    gBS->Stall (100);
  } while (MutexMdio || MutexI2c);

  if ((MutexMdio == 0) && (MutexI2c == 0)) {
    // Obtain the mutex
    DEBUG ((EFI_D_ERROR, "Recieved the hardware mutexes\n"));
    XP_IOWRITE (pdata, XP_I2C_MUTEX, mutex_id);
    XP_IOWRITE (pdata, XP_MDIO_MUTEX, mutex_id);
    phy_data->comm_owned = 1;
    return 0;
  }
  DEBUG ((EFI_D_ERROR, "unable to obtain hardware mutexes\n"));
  return 1;
}

VOID
xgbe_phy_put_comm_ownership (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  XGBE_PHY_DATA *phy_data = pdata->phy_data;
  phy_data->comm_owned = 0;
//  mutex_unlock (&xgbe_phy_comm_lock);
}

UINTN
STATIC
xgbe_i2c_abort (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  UINTN wait;
  wait = XGBE_ABORT_COUNT;
  // Must be enabled to recognize the abort request
  XI2C_IOWRITE_BITS (pdata, IC_ENABLE, EN, 1);
  // Issue the abort
  XI2C_IOWRITE_BITS (pdata, IC_ENABLE, ABORT, 1);
  while (wait--) {
    if (!XI2C_IOREAD_BITS (pdata, IC_ENABLE, ABORT)) {
      return 0;
    }
    gBS->Stall (100);
  }
  return 1;
}

UINTN
STATIC
xgbe_i2c_set_enable (
  ENET_DXE_PRIVATE_DATA *pdata,
  BOOLEAN enable
  )
{

  UINTN    wait;
  UINTN    mode;
  wait = XGBE_DISABLE_COUNT;
  mode = enable ? 1 : 0;

  while (wait--) {
    XI2C_IOWRITE_BITS (pdata, IC_ENABLE, EN, mode);
    if (XI2C_IOREAD_BITS (pdata, IC_ENABLE_STATUS, EN) == mode) {
      return 0;
    }
    gBS->Stall (100);
  }

  return 1;
}

UINTN
STATIC
xgbe_i2c_disable (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  UINTN ret;
  ret = xgbe_i2c_set_enable (pdata, FALSE);
  if (ret) {
    // Disable failed, try an abort
    ret = xgbe_i2c_abort (pdata);
    if (ret) {
      return ret;
    }
       // Abort succeeded, try to disable again */
    ret = xgbe_i2c_set_enable (pdata, FALSE);
  }
  return ret;
}

VOID
STATIC
xgbe_i2c_set_target (
  ENET_DXE_PRIVATE_DATA *pdata, UINTN addr
  )
{
  XI2C_IOWRITE (pdata, IC_TAR,(UINT32) addr);
}

VOID
STATIC
xgbe_i2c_clear_all_interrupts (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  XI2C_IOREAD (pdata, IC_CLR_INTR);
}

VOID
STATIC
xgbe_i2c_disable_interrupts (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  XI2C_IOWRITE (pdata, IC_INTR_MASK, 0);
}

VOID
STATIC
xgbe_i2c_enable_interrupts (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  XI2C_IOWRITE (pdata, IC_INTR_MASK, XGBE_DEFAULT_INT_MASK);
}

UINTN
STATIC
xgbe_i2c_enable (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  return xgbe_i2c_set_enable (pdata, TRUE);
}

EFI_STATUS
xgbe_phy_redrv_write (
  ENET_DXE_PRIVATE_DATA *pdata,
  UINTN reg,
  UINTN val
  )
{
  //XGBE_PHY_DATA *phy_data = pdata->phy_data;
  XGBE_I2C_MASTER_PROTOCOL  *XgbEI2cMaster;
  UINT8                     PacketBuffer[sizeof (EFI_I2C_REQUEST_PACKET) + sizeof (EFI_I2C_OPERATION)];
  EFI_I2C_REQUEST_PACKET    *RequestPacket;
  EFI_I2C_OPERATION         *Operation;
  EFI_STATUS                Status;
  UINTN                     SlaveAdd;
  UINT16                    redrv_val;
  UINT8                     redrv_data[5];
  UINT8                     csum;
  UINT8                     i;
  UINT32                    XgmacBaseI2c;
  Status = EFI_SUCCESS;
  SlaveAdd = 0x40; //phy_data->redrv_addr;  //0x40

  for (i = 0; i < 5; i++) {
    redrv_data[i] = 0;
  }
  XgmacBaseI2c = pdata->xgmac_pdata.xgmac_regs + 0x1E000;
  Status = gBS->LocateProtocol (&gxGbEI2cMasterProtocolGuid, NULL, &XgbEI2cMaster);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "\nXGMAC Workaround: Could not Locate gxGbEI2cMasterProtocolGuid\n"));
    gBS->Stall (100);
  }
  XgbEI2cMaster->BaseAddress = XgmacBaseI2c;
  XgbEI2cMaster->I2cInit (XgbEI2cMaster);

  // High byte of register contains read/write indicator
  redrv_data[0] = ((reg >> 8) & 0xff) << 1;
  redrv_data[1] = reg & 0xff;
  redrv_val = *(UINT16 *)&redrv_data[2];
  redrv_data[3] = (UINT8) val;
//  redrv_data[3] = 0x9;

  //Calculate 1 byte checksum
  csum = 0;
  for (i = 0; i < 4; i++) {
    csum += redrv_data[i];
    if (redrv_data[i] > csum) {
      csum++;
    }
  }
  redrv_data[4] = ~csum;
  RequestPacket = (EFI_I2C_REQUEST_PACKET*)PacketBuffer;
  Operation   = RequestPacket->Operation;

  RequestPacket->OperationCount = 2;
  Operation[0].Flags            = 0;
  Operation[0].LengthInBytes    = sizeof (redrv_data);
  Operation[0].Buffer           = redrv_data;
  Operation[1].Flags            = I2C_FLAG_READ;
  Operation[1].LengthInBytes    = sizeof (UINT8);
  Operation[1].Buffer           = redrv_data;

  Status = XgbEI2cMaster->StartRequest (XgbEI2cMaster, SlaveAdd, RequestPacket, NULL, NULL);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "\nXGMAC: Failed to StartRequest.\n"));
  }
  if (redrv_data[0] != 0xff) {
    DEBUG ((EFI_D_ERROR, "XGMAC: Redriver write checksum error\n"));
  }
  DEBUG ((EFI_D_ERROR, "XGMAC: redrv_data  = %0x \n", redrv_data[0]));
  return Status;
}

VOID
xgbe_phy_set_redrv_mode_i2c (
  ENET_DXE_PRIVATE_DATA *pdata,
  enum xgbe_phy_redrv_mode mode
  )
{
  XGBE_PHY_DATA *phy_data = pdata->phy_data;
  UINTN redrv_reg;
  EFI_STATUS                Status;
  Status;

  // Calculate the register to write
  redrv_reg = XGBE_PHY_REDRV_MODE_REG + (phy_data->redrv_lane * 0x1000);
  Status = xgbe_phy_redrv_write (pdata, redrv_reg, mode);
}

VOID
STATIC
xgbe_phy_set_redrv_mode (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  XGBE_PHY_DATA *phy_data = pdata->phy_data;
  enum xgbe_phy_redrv_mode mode;
  UINTN ret;
  DEBUG ((EFI_D_ERROR, "xgbe_phy_set_redrv_mode \n"));
  if (!phy_data->redrv) {
    DEBUG ((EFI_D_ERROR, "Redriver not present.\n"));
    return;
  }
  mode = XGBE_PHY_REDRV_MODE_CX;
  if ((phy_data->port_mode == XGBE_PORT_MODE_SFP) &&
        (phy_data->sfp_base != XGBE_SFP_BASE_1000_CX) &&
        (phy_data->sfp_base != XGBE_SFP_BASE_10000_CR)) {
    mode = XGBE_PHY_REDRV_MODE_SR;
    DEBUG ((EFI_D_ERROR, "Setting Redrv Mode set to XGBE_PHY_REDRV_MODE_SR\n"));
  }
  ret = xgbe_phy_get_comm_ownership (pdata);
  if (ret) {
    DEBUG ((EFI_D_ERROR, "Setting Redrv Mode ERROR1 Returning back\n"));
    return;
  }

  if (phy_data->redrv_if) {
    xgbe_phy_set_redrv_mode_i2c (pdata, mode);
  }
// Gearbox  else
// Gearbox  xgbe_phy_set_redrv_mode_mdio(pdata, mode);

//Gearbox xgbe_phy_put_comm_ownership(pdata);
  phy_data->comm_owned = 0;
}

UINTN xgbe_set_gpio(ENET_DXE_PRIVATE_DATA *pdata, UINT32 gpio)
{
	UINT32 XgmacBase;
	UINT32 Mdioreg = 0;

	XgmacBase = pdata->xgmac_pdata.xgmac_regs;

	if (gpio > 15)
		return 0;

	Mdioreg = MmioRead32 (XgmacBase + MAC_GPIOSR);
	Mdioreg |= (1 << (gpio + 16));
	MmioWrite32 (XgmacBase + MAC_GPIOSR, Mdioreg);
	return 1;
}

UINTN  xgbe_clr_gpio(ENET_DXE_PRIVATE_DATA *pdata, UINT32 gpio)
{
	UINT32 XgmacBase;
	UINT32 Mdioreg = 0;

	XgmacBase = pdata->xgmac_pdata.xgmac_regs;

	if (gpio > 15)
		return 0;

	Mdioreg = MmioRead32 (XgmacBase + MAC_GPIOSR);
	Mdioreg &= ~(1 << (gpio + 16));
	MmioWrite32 (XgmacBase + MAC_GPIOSR, Mdioreg);

	return 1;
}


UINTN xgbe_phy_int_mdio_reset(ENET_DXE_PRIVATE_DATA *pdata){

	XGBE_PHY_DATA *phy_data = pdata->phy_data;
	UINTN ret;

	ret = xgbe_set_gpio(pdata, (UINT32)phy_data->mdio_reset_gpio);
	if (!ret)
		return ret;

	ret = xgbe_clr_gpio(pdata, (UINT32)phy_data->mdio_reset_gpio);
	return ret;
}

UINTN
STATIC
xgbe_phy_mdio_reset (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  XGBE_PHY_DATA *phy_data = pdata->phy_data;
  UINTN ret;
  DEBUG ((EFI_D_ERROR, "xgbe_phy_mdio_reset  \n"));
 if (phy_data->conn_type != XGBE_CONN_TYPE_MDIO)
 	return 0;
  ret = xgbe_phy_get_comm_ownership (pdata);
  if (ret) {
    return ret;
  }

 #if 0   //SKIP GEAR BOX for now.
//gearbox stuff
  if (phy_data->mdio_reset == XGBE_MDIO_RESET_I2C_GPIO) {
   ret = xgbe_phy_i2c_mdio_reset (pdata);
  } else if (phy_data->mdio_reset == XGBE_MDIO_RESET_INT_GPIO) {
   ret = xgbe_phy_int_mdio_reset (pdata);
  }
#endif
  xgbe_phy_put_comm_ownership (pdata);
  return ret;
}
VOID
STATIC
xgbe_phy_sfp_mode (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  XGBE_PHY_DATA *phy_data = pdata->phy_data;
  UINT32 s0;
  UINT32 XgmacBase;
  XgmacBase = pdata->xgmac_pdata.xgmac_regs;

  xgbe_phy_set_redrv_mode (pdata);
  xgbe_phy_start_ratechange (pdata);

  // 10G/SFI
  s0 = 0;
  XP_SET_BITS (s0, XP_DRIVER_SCRATCH_0, COMMAND, 3);
  if (phy_data->sfp_cable != XGBE_SFP_CABLE_PASSIVE) {
    XP_SET_BITS (s0, XP_DRIVER_SCRATCH_0, SUB_COMMAND, 0);
  } else {
    if (phy_data->sfp_cable_len <= 1) {
      XP_SET_BITS (s0, XP_DRIVER_SCRATCH_0, SUB_COMMAND, 1);
    } else if (phy_data->sfp_cable_len <= 3) {
        XP_SET_BITS (s0, XP_DRIVER_SCRATCH_0, SUB_COMMAND, 2);
    } else if (phy_data->sfp_cable_len <= 5) {
        XP_SET_BITS (s0, XP_DRIVER_SCRATCH_0, SUB_COMMAND, 3);
    } else
      XP_SET_BITS (s0, XP_DRIVER_SCRATCH_0, SUB_COMMAND, 3);
    }
  // Call FW to make the change. XP_IOWRITE does not work. Later.
  MmioWrite32 (XgmacBase + 0x1d068, s0);   //scratch 0
  MmioWrite32 (XgmacBase + 0x1d06c, 0);
  MmioWrite32 (XgmacBase + 0x1d060, 1);
  xgbe_phy_complete_ratechange (pdata);
  phy_data->cur_mode = XGBE_MODE_SFI;
  DEBUG ((EFI_D_ERROR, "10GbE SFI mode set  s0 = %x \n" , s0));
}

VOID
STATIC
xgbe_phy_x_mode (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  XGBE_PHY_DATA *phy_data = pdata->phy_data;
  UINT16 s0;
  UINT32 XgmacBase;
  XgmacBase = pdata->xgmac_pdata.xgmac_regs;
  DEBUG ((EFI_D_ERROR, "xgbe_phy_x_mode\n"));
  xgbe_phy_set_redrv_mode (pdata);

  xgbe_phy_start_ratechange (pdata);
  s0 = 0x0301;
  MmioWrite32 (XgmacBase + 0x1d068, s0);   //scratch 0
  MmioWrite32 (XgmacBase + 0x1d06c, 0);
  MmioWrite32 (XgmacBase + 0x1d060, 1);
  xgbe_phy_complete_ratechange (pdata);

  phy_data->cur_mode = XGBE_MODE_X;
  DEBUG ((EFI_D_ERROR, "1GbE X mode set\n"));
}
VOID
xgbe_phy_sgmii_1000_mode (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  XGBE_PHY_DATA *phy_data = pdata->phy_data;
  UINT16 s0;
  UINT32 XgmacBase;
  XgmacBase = pdata->xgmac_pdata.xgmac_regs;
  DEBUG ((EFI_D_ERROR, "xgbe_phy_sgmii_1000_mode\n"));

  xgbe_phy_set_redrv_mode (pdata);
  xgbe_phy_start_ratechange (pdata);
// 1G/SGMII
  s0 = 0x0201;
  MmioWrite32 (XgmacBase + 0x1d068, s0);
  MmioWrite32 (XgmacBase + 0x1d06c, 0);
  MmioWrite32 (XgmacBase + 0x1d060, 1);

  xgbe_phy_complete_ratechange (pdata);
  phy_data->cur_mode = XGBE_MODE_SGMII_1000;
  DEBUG ((EFI_D_ERROR, "1GbE SGMII mode set\n"));
}

VOID
xgbe_phy_sgmii_100_mode (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  XGBE_PHY_DATA *phy_data = pdata->phy_data;
  UINT32 s0;
  UINT32 XgmacBase;
  XgmacBase = pdata->xgmac_pdata.xgmac_regs;

  DEBUG ((EFI_D_ERROR, "xgbe_phy_sgmii_100_mode\n"));
  xgbe_phy_set_redrv_mode (pdata);
  xgbe_phy_start_ratechange (pdata);

  s0 = 0x0101;
  MmioWrite32 (XgmacBase + 0x1d068, s0);
  MmioWrite32 (XgmacBase + 0x1d06c, 0);
  MmioWrite32 (XgmacBase + 0x1d060, 1);


// 1G/SGMII
// s0 = 0;
// XP_SET_BITS(s0, XP_DRIVER_SCRATCH_0, COMMAND, 1);
// XP_SET_BITS(s0, XP_DRIVER_SCRATCH_0, SUB_COMMAND, 1);

// Call FW to make the change
// XP_IOWRITE(pdata, XP_DRIVER_SCRATCH_0, s0);
// XP_IOWRITE(pdata, XP_DRIVER_SCRATCH_1, 0);
// XP_IOWRITE_BITS(pdata, XP_DRIVER_INT_REQ, REQUEST, 1);

  xgbe_phy_complete_ratechange (pdata);
  phy_data->cur_mode = XGBE_MODE_SGMII_100;
  DEBUG ((EFI_D_ERROR, "100MbE SGMII mode set\n"));
}

VOID
STATIC
xgbe_phy_kx_1000_mode (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  XGBE_PHY_DATA *phy_data = pdata->phy_data;
  UINT32 s0;
  UINT32 XgmacBase;
  XgmacBase = pdata->xgmac_pdata.xgmac_regs;
  DEBUG ((EFI_D_ERROR, "xgbe_phy_kx_1000_mode\n"));

  pdata->xprop_regs = pdata->xgmac_pdata.xgmac_regs + XGBE_MAC_CTRL_OFFSET;
  pdata->xi2c_regs = pdata->xgmac_pdata.xgmac_regs + XGBE_I2C_CTRL_OFFSET;
  DEBUG ((EFI_D_ERROR, "pdata->xprop_regs = %x \n", pdata->xprop_regs));

  xgbe_phy_set_redrv_mode (pdata);
  xgbe_phy_start_ratechange (pdata);

// 1G/KX
  s0 = 0x0301;
  MmioWrite32 (XgmacBase + 0x1d068, s0);
  MmioWrite32 (XgmacBase + 0x1d06c, 0);
  MmioWrite32 (XgmacBase + 0x1d060, 1);

 //  s0 = 0;
  //XP_SET_BITS(s0, XP_DRIVER_SCRATCH_0, COMMAND, 1);
 // XP_SET_BITS(s0, XP_DRIVER_SCRATCH_0, SUB_COMMAND, 3);

// Call FW to make the change
//  XP_IOWRITE(pdata, XP_DRIVER_SCRATCH_0, s0);
//  XP_IOWRITE(pdata, XP_DRIVER_SCRATCH_1, 0);
//  XP_IOWRITE_BITS(pdata, XP_DRIVER_INT_REQ, REQUEST, 1);

  xgbe_phy_complete_ratechange (pdata);
  phy_data->cur_mode = XGBE_MODE_KX_1000;
  DEBUG ((EFI_D_ERROR, "1GbE KX mode set\n"));
}

VOID
STATIC
xgbe_phy_kx_2500_mode (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  UINT32 s0;
  XGBE_PHY_DATA *phy_data = pdata->phy_data;
  UINT32 XgmacBase;
  XgmacBase = pdata->xgmac_pdata.xgmac_regs;
  DEBUG ((EFI_D_ERROR, "xgbe_phy_kx_2500_mode\n"));

  pdata->xprop_regs = pdata->xgmac_pdata.xgmac_regs + XGBE_MAC_CTRL_OFFSET;
  pdata->xi2c_regs = pdata->xgmac_pdata.xgmac_regs + XGBE_I2C_CTRL_OFFSET;
  DEBUG ((EFI_D_ERROR, "pdata->xprop_regs = %x \n", pdata->xprop_regs));

  xgbe_phy_set_redrv_mode (pdata);
  xgbe_phy_start_ratechange (pdata);

// 2.5G/KX
  s0 = 0x0002;
  MmioWrite32 (XgmacBase + 0x1d068, s0);
  MmioWrite32 (XgmacBase + 0x1d06c, 0);
  MmioWrite32 (XgmacBase + 0x1d060, 1);


//s0 = 0;
// XP_SET_BITS (s0, XP_DRIVER_SCRATCH_0, COMMAND, 2);
// XP_SET_BITS (s0, XP_DRIVER_SCRATCH_0, SUB_COMMAND, 0);
// Call FW to make the change
//  XP_IOWRITE (pdata, XP_DRIVER_SCRATCH_0, s0);
//  XP_IOWRITE (pdata, XP_DRIVER_SCRATCH_1, 0);
//  XP_IOWRITE_BITS (pdata, XP_DRIVER_INT_REQ, REQUEST, 1);

  xgbe_phy_complete_ratechange (pdata);
  phy_data->cur_mode = XGBE_MODE_KX_2500;
  DEBUG ((EFI_D_ERROR, "2.5GbE KX mode set\n"));
}

VOID
STATIC
xgbe_phy_kr_mode (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  UINT32 s0;
  XGBE_PHY_DATA *phy_data = pdata->phy_data;
  UINT32 XgmacBase;
  XgmacBase = pdata->xgmac_pdata.xgmac_regs;
  DEBUG ((EFI_D_ERROR, "xgbe_phy_kr_mode\n"));

  pdata->xprop_regs = pdata->xgmac_pdata.xgmac_regs + XGBE_MAC_CTRL_OFFSET;
  pdata->xi2c_regs = pdata->xgmac_pdata.xgmac_regs + XGBE_I2C_CTRL_OFFSET;
  //DEBUG ((EFI_D_ERROR, "pdata->xprop_regs = %x \n", pdata->xprop_regs));

  xgbe_phy_set_redrv_mode (pdata);
  xgbe_phy_start_ratechange (pdata);

  // 10G/KR
  s0 = 0x0004;
  MmioWrite32 (XgmacBase + 0x1d068, s0);
  MmioWrite32 (XgmacBase + 0x1d06c, 0);
  MmioWrite32 (XgmacBase + 0x1d060, 1);

  xgbe_phy_complete_ratechange (pdata);
  phy_data->cur_mode = XGBE_MODE_KR;
  DEBUG ((EFI_D_ERROR, "10GbE KR mode set\n"));
}


VOID  xgbe_phy_set_mode(ENET_DXE_PRIVATE_DATA *pdata, enum xgbe_mode mode)
{
	switch (mode) {
	case XGBE_MODE_KX_1000:
		xgbe_phy_kx_1000_mode(pdata);
		break;
	case XGBE_MODE_KX_2500:
		xgbe_phy_kx_2500_mode(pdata);
		break;
	case XGBE_MODE_KR:
		xgbe_phy_kr_mode(pdata);
		break;
	case XGBE_MODE_SGMII_100:
		xgbe_phy_sgmii_100_mode(pdata);
		break;
	case XGBE_MODE_SGMII_1000:
		xgbe_phy_sgmii_1000_mode(pdata);
		break;
	case XGBE_MODE_X:
		xgbe_phy_x_mode(pdata);
		break;
	case XGBE_MODE_SFI:
		xgbe_phy_sfp_mode(pdata);
		break;
	default:
		break;
	}
}

VOID
STATIC
xgbe_phy_rrc (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  UINT32 s0;
  UINT32 XgmacBase;
  XgmacBase = pdata->xgmac_pdata.xgmac_regs;
  xgbe_phy_start_ratechange (pdata);

//  if (!XP_IOREAD_BITS (pdata, XP_DRIVER_INT_RO, STATUS))
//  return;
//  DEBUG ((EFI_D_ERROR, "firmware mailbox not ready for command \n"));

// Receiver Reset Cycle
  s0 = 0x0005;
  MmioWrite32 (XgmacBase + 0x1d068, s0);
  MmioWrite32 (XgmacBase + 0x1d06c, 0);
  MmioWrite32 (XgmacBase + 0x1d060, 1);

  xgbe_phy_complete_ratechange (pdata);
  DEBUG ((EFI_D_ERROR, "receiver reset complete\n"));
}

UINTN
read_mmd_regs (
  IN       UINTN XpcsBase,
  IN       UINTN mmd_reg
  )
{

  UINTN mmd_address;
  UINTN mmd_data;
  UINTN XpcsWin;
  UINTN XpcsWinSize;
  UINTN XpcsWinMask;
  UINTN reg;
  UINTN index;
  UINTN offset;

  reg = XPCS_IOREAD32 (XpcsBase, PCS_V2_RV_WINDOW_DEF);
  XpcsWin = GET_BITS(reg, 6, 14);
  XpcsWin <<= 6;
  XpcsWinSize = GET_BITS(reg, 2, 4);
  XpcsWinSize = 1ULL << (XpcsWinSize + 7);
  XpcsWinMask = XpcsWinSize - 1;

  if (mmd_reg & MII_ADDR_C45) {
    mmd_address = mmd_reg & ~MII_ADDR_C45;
  } else
    mmd_address = (MDIO_MMD_PCS << 16) | (mmd_reg & 0xffff);

//The PCS registers are accessed using mmio. The underlying
// management interface uses indirect addressing to access the MMD
// register sets. This requires accessing of the PCS register in two
// phases, an address phase and a data phase.

//The mmio interface is based on 16-bit offsets and values. All
//register offsets must therefore be adjusted by left shifting the
//offset 1 bit and reading 16 bits of data.

  mmd_address <<= 1;
  index = mmd_address & ~XpcsWinMask;
  offset = XpcsWin + (mmd_address & XpcsWinMask);
  XPCS_IOWRITE32 (XpcsBase, PCS_V2_RV_WINDOW_SELECT, (UINT32)index);
  mmd_data = XPCS_IOREAD16 (XpcsBase, offset);
  return mmd_data;
}

VOID
STATIC
write_mmd_regs (
  IN       UINTN XpcsBase,
  IN       UINTN mmd_reg,
  IN       UINTN mmd_data
  )
{
  UINTN mmd_address;
  UINTN XpcsWin;
  UINTN XpcsWinSize;
  UINTN XpcsWinMask;
  UINTN reg;
  UINTN index;
  UINTN offset;

  reg = XPCS_IOREAD32 (XpcsBase, PCS_V2_RV_WINDOW_DEF);
  XpcsWin = GET_BITS(reg, 6, 14);
  XpcsWin <<= 6;
  XpcsWinSize = GET_BITS (reg, 2, 4);
  XpcsWinSize = 1ULL << (XpcsWinSize + 7);
  XpcsWinMask = XpcsWinSize - 1;

  if (mmd_reg & MII_ADDR_C45) {
  mmd_address = mmd_reg & ~MII_ADDR_C45;
  } else mmd_address = (MDIO_MMD_PCS << 16) | (mmd_reg & 0xffff);

  mmd_address <<= 1;
  index = mmd_address & ~XpcsWinMask;
  offset = XpcsWin + (mmd_address & XpcsWinMask);

  XPCS_IOWRITE32 (XpcsBase, PCS_V2_RV_WINDOW_SELECT, (UINT32)index);
  XPCS_IOWRITE16 (XpcsBase, offset, (UINT16)mmd_data);
}


VOID
STATIC
xgmac_pcs_enable_kr_training (
  IN  UINTN XpcsBase
  )
{
  // Enable KR training
  UINTN reg;
  UINTN count;
  reg = XMDIO_READ (XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_CTRL);
  reg |= MDIO_PMA_10GBR_CTRL_KRTRAIN;
  XMDIO_WRITE (XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_CTRL, reg);
  count = 50;
  do {
    gBS->Stall (100);
    reg = XMDIO_READ (XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_CTRL);
  } while  ((reg & MDIO_PMA_10GBR_CTRL) && --count);
  reg = XMDIO_READ (XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_CTRL);
}

VOID
xgmac_pcs_disable_kr_training (
  IN       UINTN XpcsBase
  )
{
  UINTN reg;
    // Disable KR training
  reg = XMDIO_READ (XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_CTRL);
  reg &= ~MDIO_PMA_10GBR_CTRL_KRTRAIN;
  XMDIO_WRITE (XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_CTRL, reg);
  gBS->Stall (100);
}

VOID
STATIC
xgmac_restart_kr_training (
  IN  UINTN XpcsBase
  )
{
  UINTN reg;
  // set adapter_reset

  reg = XMDIO_READ (XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_CTRL);
  reg |= MDIO_PMA_10GBR_CTRL_KRTRAIN_START;
  XMDIO_WRITE (XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_CTRL, reg);
  gBS->Stall (100);

//  XMDIO_WRITE_BITS (XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_CTRL,
//       MDIO_PMA_10GBR_CTRL_KRTRAIN_START, MDIO_PMA_10GBR_CTRL_KRTRAIN_START);
  // release adapter_reset

}

VOID
STATIC
xgmac_pcs_power_cycle (
  IN       UINTN XpcsBase
  )
{
  UINTN reg;
  reg = XMDIO_READ (XpcsBase, MDIO_MMD_PCS, MDIO_CTRL1);
  reg |= MDIO_CTRL1_LPOWER;
  XMDIO_WRITE (XpcsBase, MDIO_MMD_PCS, MDIO_CTRL1, reg);
  gBS->Stall (100);
  reg = XMDIO_READ (XpcsBase, MDIO_MMD_PCS, MDIO_CTRL1);
  reg &= 0xF7FF;
  XMDIO_WRITE (XpcsBase, MDIO_MMD_PCS, MDIO_CTRL1, reg);
}

VOID
STATIC
xgmac_start_ratechange (
  IN  UINT32 XgmacBase
  )
{
  UINT32 reg;
  do {
    reg = getBitfieldReg32 (XgmacBase + MC_DRIVER_MB_INT_RES, 0, 1);
  } while (reg != 0);
}

VOID
STATIC
xgmac_pcs_gmii_10_speed (
  IN       UINT32 XpcsBase,
  IN       UINT32 XgmacBase
  )
{

  xgmac_start_ratechange (XgmacBase);
  MmioWrite32 (XgmacBase + MC_DRIVER_MB_S0, 0x1);
  MmioWrite32 (XgmacBase + MC_DRIVER_MB_S1, 0x0);
  setBitfieldReg32 (XgmacBase + MC_DRIVER_MB_INT_REQ, 0, 1, 1);
  xgmac_start_ratechange (XgmacBase);
}

VOID
STATIC
xgmac_pcs_gmii_100_speed (
  IN       UINT32 XpcsBase,
  IN       UINT32 XgmacBase

  )
{
  xgmac_start_ratechange (XgmacBase);
  MmioWrite32 (XgmacBase + MC_DRIVER_MB_S0, 0x1);
  MmioWrite32 (XgmacBase + MC_DRIVER_MB_S1, 0x1);
  setBitfieldReg32 (XgmacBase + MC_DRIVER_MB_INT_REQ, 0, 1, 1);
  xgmac_start_ratechange (XgmacBase);
}

VOID
STATIC
xgmac_pcs_gmii_speed (
  IN       UINT32 XpcsBase,
  IN       UINT32 XgmacBase

  )
{

  xgmac_start_ratechange (XgmacBase);
  MmioWrite32 (XgmacBase + MC_DRIVER_MB_S0, 0x1);
  MmioWrite32 (XgmacBase + MC_DRIVER_MB_S1, 0x2);
  setBitfieldReg32 (XgmacBase + MC_DRIVER_MB_INT_REQ, 0, 1, 1);
  xgmac_start_ratechange (XgmacBase);

 // XGMAC_IOWRITE32 (pdata, MC_DRIVER_MB_S0, 1);
 // XGMAC_IOWRITE32 (pdata, MC_DRIVER_MB_S1, 0);

}

VOID
STATIC
xgmac_pcs_gmii_1GKR_speed (
  IN       UINT32 XpcsBase,
  IN       UINT32 XgmacBase

  )
{

  xgmac_start_ratechange (XgmacBase);
  MmioWrite32 (XgmacBase + MC_DRIVER_MB_S0, 0x1);
  MmioWrite32 (XgmacBase + MC_DRIVER_MB_S1, 0x3);
  setBitfieldReg32 (XgmacBase + MC_DRIVER_MB_INT_REQ, 0, 1, 1);
  xgmac_start_ratechange (XgmacBase);
}

VOID
STATIC
xgmac_pcs_gmii_2500_speed (
  IN       UINT32 XpcsBase,
  IN       UINT32 XgmacBase

  )
{
//  xgmac_pcs_gmii_speed (XpcsBase, XgmacBase);
  xgmac_start_ratechange (XgmacBase);
  MmioWrite32 (XgmacBase + MC_DRIVER_MB_S0, 2);
  MmioWrite32 (XgmacBase + MC_DRIVER_MB_S1, 0);
  setBitfieldReg32 (XgmacBase + MC_DRIVER_MB_INT_REQ, 0, 1, 1);
  xgmac_start_ratechange (XgmacBase);

}

VOID
STATIC
xgbe_pcs_xgmii_speed (
  IN       UINT32 XpcsBase,
  IN       UINT32 XgmacBase
  )
{
  xgmac_pcs_enable_kr_training (XpcsBase);
  xgmac_start_ratechange (XgmacBase);
  MmioWrite32 (XgmacBase + MC_DRIVER_MB_S0, 3);
  MmioWrite32 (XgmacBase + MC_DRIVER_MB_S1, 0);
  setBitfieldReg32 (XgmacBase + MC_DRIVER_MB_INT_REQ, 0, 1, 1);
  xgmac_start_ratechange (XgmacBase);
  DEBUG ((EFI_D_ERROR, "X--xgbe_pcs_xgmii_speed\n"));
}

VOID
STATIC
xgbe_pcs_xgmii_kr_speed (
  IN       UINT32 XpcsBase,
  IN       UINT32 XgmacBase
  )
{
  xgmac_pcs_enable_kr_training (XpcsBase);
  xgmac_start_ratechange (XgmacBase);
  MmioWrite32 (XgmacBase + MC_DRIVER_MB_S0, 4);
  MmioWrite32 (XgmacBase + MC_DRIVER_MB_S1, 0);
  setBitfieldReg32 (XgmacBase + MC_DRIVER_MB_INT_REQ, 0, 1, 1);
  xgmac_start_ratechange (XgmacBase);
  DEBUG ((EFI_D_ERROR, "X--xgbe_pcs_xgmii_speed\n"));
}


EFI_STATUS
xgbe_test_kr_train_sts (
  IN  UINTN XpcsBase
  )
{
  UINTN   RegVal;
  // test if training is complete
  RegVal = XMDIO_READ (XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_STS);
  if (RegVal & MDIO_PMA_10GBR_STS_TR_FAIL) {
    return EFI_DEVICE_ERROR;
  }
  if (RegVal & MDIO_PMA_10GBR_STS_RCV_STS) {
    // now check LD and LP Receiver Ready ( from KR Coefficient Status reg )
    if ((MDIO_PMA_10GBR_CE_RR & XMDIO_READ (XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_LP_CESTS)) &&
      (MDIO_PMA_10GBR_CE_RR & XMDIO_READ (XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_LD_CESTS))) {
      return EFI_SUCCESS;
    }
  }
  return EFI_NOT_READY;
}

EFI_STATUS
xgbe_check_kr_train (
  IN  UINTN XpcsBase
  )
{
  UINTN reg;
  EFI_STATUS  Status;
  // Check KR TR enabled
  reg = XMDIO_READ (XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_CTRL);
  if ((reg & MDIO_PMA_10GBR_CTRL_KRTRAIN) != MDIO_PMA_10GBR_CTRL_KRTRAIN) {
    DEBUG ((EFI_D_ERROR, "::KR training was disabled, enabling it\n"));
    reg = XMDIO_READ (XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_CTRL);
    reg |= MDIO_PMA_10GBR_CTRL_KRTRAIN;
    XMDIO_WRITE (XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_CTRL, reg);
  }
  Status = xgbe_test_kr_train_sts (XpcsBase);
  return Status;
}

BOOLEAN
IsLpPresent (
  IN  ENET_DXE_PRIVATE_DATA *Private
  )
{
  UINTN AnIntReg;
  UINTN AnLp2;
  UINTN WaitCount;
  UINTN XpcsBase;
  XpcsBase = Private->xpcs_regs;

  switch (Private->an_mode) {
  case XGBE_AN_MODE_CL73:
  case XGBE_AN_MODE_CL73_REDRV:
	    xgbe_an73_clear_interrupts(XpcsBase);
        xgbe_an73_restart((UINT32)XpcsBase);
	  break;
  case XGBE_AN_MODE_CL37:
  case XGBE_AN_MODE_CL37_SGMII:
		xgbe_an37_clear_interrupts(XpcsBase);
        xgbe_an37_restart((UINT32)XpcsBase);
	  break;
  default:
	  break;
  }

  // Wait for interrupt - PG_RCV
  WaitCount = 0;
  while (WaitCount < 10000) {
  // 1000 mS
    AnIntReg = XMDIO_READ (XpcsBase,  MDIO_MMD_AN, MDIO_AN_INT );

    if (AnIntReg & AN_INC_LNK) {
      return FALSE;
    }
    if (AnIntReg & AN_PG_RCV) {
      // Clear PG_RCV
      XMDIO_WRITE (XpcsBase, MDIO_MMD_AN, MDIO_AN_INT, (AnIntReg & ~AN_PG_RCV));
      gBS->Stall (100);
      XMDIO_WRITE (XpcsBase, MDIO_MMD_AN, MDIO_AN_INT, (AnIntReg & ~AN_PG_RCV));

      // Verify LP
      AnLp2 = XMDIO_READ (XpcsBase, MDIO_MMD_AN, MDIO_AN_LP_ABL2);
      if (AnLp2 & 0xA0)  return TRUE;
      if (AnLp2 & 0x20) {
        return TRUE;
      }
    }
    gBS->Stall (100);
    WaitCount++;
  } // end of wait for INT

  return  FALSE;
}


VOID
EFIAPI
LinkStsTimerEventHandler (
  IN EFI_EVENT    Timer,
  IN VOID         *Context
  )
{
  UINTN RegVal;
  UINTN XpcsBase;
  UINT32 XgmacBase;
  UINTN  an_int ,  an_status;
  ENET_DXE_PRIVATE_DATA *Private;
  Private =  (ENET_DXE_PRIVATE_DATA*)Context;
  XpcsBase = Private->xpcs_regs;
  XgmacBase = Private->xgmac_pdata.xgmac_regs;

  // Stop timer for period of executing this handler
  if ( LinkStsTimerEvent != NULL) {
    gBS->SetTimer (LinkStsTimerEvent, TimerCancel, 0);
  }

  DEBUG ((EFI_D_ERROR, "LinkStsTimerEventHandler \n"));

  switch (Private->an_mode) {
  case XGBE_AN_MODE_CL73:
  case XGBE_AN_MODE_CL73_REDRV:
	    // This part originally for 1GB int, which happens after AN
  		an_int = XMDIO_READ (XpcsBase,  MDIO_MMD_AN, MDIO_AN_INT );
  		if (an_int) {
    		/* Clear the interrupt(s) that fired and process them */
			RegVal &= ~an_int;
    		XMDIO_WRITE (XpcsBase, MDIO_MMD_AN, MDIO_AN_INT, RegVal);
			gBS->Stall (100);
			XMDIO_WRITE (XpcsBase, MDIO_MMD_AN, MDIO_AN_INT, RegVal);    		
  		}
	  break;
  case XGBE_AN_MODE_CL37:
  case XGBE_AN_MODE_CL37_SGMII:
	    // This part originally for 1GB int, which happens after AN
  		RegVal = XMDIO_READ (XpcsBase,  MDIO_MMD_VEND2, MDIO_VEND2_AN_STAT );
        an_int = RegVal & XGBE_AN_CL37_INT_MASK;
        an_status = RegVal & ~XGBE_AN_CL37_INT_MASK;
  		if (an_int) {
    		/* Clear the interrupt(s) that fired and process them */
			RegVal &= ~XGBE_AN_CL37_INT_MASK;
    		XMDIO_WRITE (XpcsBase, MDIO_MMD_VEND2, MDIO_VEND2_AN_STAT, RegVal);
			gBS->Stall (100);
			XMDIO_WRITE (XpcsBase, MDIO_MMD_VEND2, MDIO_VEND2_AN_STAT, RegVal);    		
  		}

	  break;
  default:
	  break;
  }

  // Check link status
  UpdateLinkStatus (Private);
  if (!Private->Mode.MediaPresent) {
    DEBUG ((EFI_D_ERROR, "MediaPresent FAIL   \n"));
    // Check if LP present
    if (IsLpPresent (Private)) {
      xgbe_an_state_machine (Private);
    }
  }

  // Restart timer at the end of event handler
  if ( LinkStsTimerEvent != NULL) {
    gBS->SetTimer (
                    LinkStsTimerEvent,
                    TimerPeriodic,
                    500 * 10000U    // 500 * (100nS * 10000) mS
                    );
  }

  xgbe_an_enable_interrupts(Private , (UINT32)XpcsBase);
}

VOID
StartTmr (
  IN  ENET_DXE_PRIVATE_DATA *Private
  )
{

  gBS->CreateEvent (
                    EVT_TIMER | EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    LinkStsTimerEventHandler,
                    (VOID*)Private,
                    &LinkStsTimerEvent
                    );

  if ( LinkStsTimerEvent != NULL) {
    gBS->SetTimer (
                   LinkStsTimerEvent,
                   TimerPeriodic,
                   500 * 10000U    // 500 * (100nS * 10000) mS
                   );
  }

  OldIntVal = 0;
}

VOID
STATIC
xgbe_an73_init (
  ENET_DXE_PRIVATE_DATA *pdata,
  UINT32 XpcsBase
  )
{

  UINTN reg;

  xgbe_phy_an_advertising(pdata);

  //Currently Forcing for CL73
  DEBUG ((EFI_D_ERROR, "xgbe_an73_init \n"));

  //  Set up Advertisement register 3 first
  reg = XMDIO_READ (XpcsBase, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 2);
  //DEBUG ((EFI_D_ERROR, "AN Register 3 BEFORE Programming= %04X \n", reg));

  if (pdata->phy.supported & ADVERTISED_10000baseR_FEC)
	reg |= 0xc000;
  else
  	reg &= ~0xc000;
  XMDIO_WRITE (XpcsBase, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 2, reg);

  gBS->Stall (100);

  DEBUG ((EFI_D_ERROR, "AN Register 3 BEFORE Programming= %04X \n", reg));
  reg = XMDIO_READ (XpcsBase, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 2);
  DEBUG ((EFI_D_ERROR, "AN Register 3 AFTER Programming= %04X \n", reg));



  // Set up Advertisement register 2 next
  reg = XMDIO_READ (XpcsBase, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 1 );
  //DEBUG ((EFI_D_ERROR, "AN Register 2 BEFORE Programming= %04X \n", reg));
  if (pdata->phy.supported  & ADVERTISED_10000baseKR_Full)
   	reg |= 0x80;
  else
  	reg &= ~0x80;

  if ((pdata->phy.supported & ADVERTISED_1000baseKX_Full) ||(pdata->phy.supported & ADVERTISED_2500baseX_Full))
  	reg |= 0x20;
  else
  	reg &= ~0x20;

  XMDIO_WRITE (XpcsBase, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 1, reg);
  gBS->Stall (100);
  DEBUG ((EFI_D_ERROR, "AN Register 2 BEFORE Programming= %04X \n", reg));
  reg = XMDIO_READ (XpcsBase, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 1 );
  DEBUG ((EFI_D_ERROR, "AN Register 2 AFTER Programming= %04X \n", reg));



  //  Set up Advertisement register 1 last
  reg = XMDIO_READ (XpcsBase, MDIO_MMD_AN, MDIO_AN_ADVERTISE);
  //DEBUG ((EFI_D_ERROR, "AN Register 1 BEFORE Programming= %04x \n", reg));
  if (pdata->phy.supported & ADVERTISED_Pause)
      reg |= 0x400;
  else
  	reg &= ~0x400;
  if (pdata->phy.supported & ADVERTISED_Asym_Pause)
  	reg |= 0x800;
  else
  	reg &= ~0x800;

  // We don't intend to perform XNP
  reg &= ~XGBE_XNP_NP_EXCHANGE;
  XMDIO_WRITE (XpcsBase, MDIO_MMD_AN, MDIO_AN_ADVERTISE, reg);
  gBS->Stall (100);


  DEBUG ((EFI_D_ERROR, "AN Register 1 BEFORE Programming= %04x \n", reg));
  reg = XMDIO_READ (XpcsBase, MDIO_MMD_AN, MDIO_AN_ADVERTISE);
  DEBUG ((EFI_D_ERROR, "AN Register 1 AFTER Programming= %04x \n", reg));


  DEBUG ((EFI_D_ERROR, "CL73 AN initialized \n"));
}
VOID
xgbe_an37_init (
  ENET_DXE_PRIVATE_DATA *pdata,
  UINT32 XpcsBase
  )
{
  UINTN reg;

  xgbe_phy_an_advertising(pdata);

  //Currently Forcing for CL73
  DEBUG ((EFI_D_ERROR, "xgbe_an37_init  pdata->an_mode = %0 x \n", pdata->an_mode));

  // Set up Advertisement register
  reg = XMDIO_READ (XpcsBase, MDIO_MMD_VEND2, MDIO_VEND2_AN_ADVERTISE);
  reg |= 0x100;
  reg &= ~0x80;

  // Full duplex, but not half
  reg |= XGBE_AN_CL37_FD_MASK;
  reg &= ~XGBE_AN_CL37_HD_MASK;
  XMDIO_WRITE (XpcsBase, MDIO_MMD_VEND2, MDIO_VEND2_AN_ADVERTISE, reg);

  // Set up the Control register
  reg = XMDIO_READ (XpcsBase, MDIO_MMD_VEND2, MDIO_VEND2_AN_CTRL);
  reg &= ~XGBE_AN_CL37_TX_CONFIG_MASK;
  reg &= ~XGBE_AN_CL37_PCS_MODE_MASK;

  switch (pdata->an_mode) {
	case XGBE_AN_MODE_CL37:
		reg |= XGBE_AN_CL37_PCS_MODE_BASEX;
		break;
	case XGBE_AN_MODE_CL37_SGMII:
		reg |= XGBE_AN_CL37_PCS_MODE_SGMII;
		break;
	default:
		break;
  }

  reg |= XGBE_AN_CL37_MII_CTRL_8BIT;

  XMDIO_WRITE (XpcsBase, MDIO_MMD_VEND2, MDIO_VEND2_AN_CTRL, reg);
  DEBUG ((EFI_D_ERROR, " CL37 initialized\n"));
}

VOID
xgbe_an_init (
  ENET_DXE_PRIVATE_DATA *pdata,
  UINT32 XpcsBase
  )
{
	xgbe_phy_an_mode(pdata);

	switch (pdata->an_mode) {
	case XGBE_AN_MODE_CL73:
	case XGBE_AN_MODE_CL73_REDRV:
		xgbe_an73_init(pdata , XpcsBase);
		break;
	case XGBE_AN_MODE_CL37:
	case XGBE_AN_MODE_CL37_SGMII:
		xgbe_an37_init(pdata , XpcsBase);
		break;
	default:
		break;
	}
}
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

VOID xgbe_an73_debug_registers(
	IN  ENET_DXE_PRIVATE_DATA *Private
)
{
	UINT32 XpcsBase = Private->xpcs_regs;

	UINT32 an_debug_regs[] = {
		0x8002, 0x8001, 0x8010, 0x0000, 0x0001, 0x0001, 0x0010, 0x0011,
		0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x0019,
		0x001a, 0x001b, 0x0030, 0x003c, 0x003d,
	};
	UINT32 pma_debug_regs[] = {
		0x00ab,
	};
	UINTN i, reg;

    DEBUG ((EFI_D_ERROR, "MMD - AN\n"));
	for (i = 0; i < ARRAY_SIZE(an_debug_regs); i++) {
		reg = XMDIO_READ(XpcsBase, MDIO_MMD_AN, an_debug_regs[i]);
		DEBUG ((EFI_D_ERROR, "   %x :   %x  \n", an_debug_regs[i], reg));
	}

	DEBUG ((EFI_D_ERROR, "MMD - PMA\n"));
	for (i = 0; i < ARRAY_SIZE(pma_debug_regs); i++) {
		reg = XMDIO_READ(XpcsBase, MDIO_MMD_PMAPMD, pma_debug_regs[i]);
		DEBUG ((EFI_D_ERROR, "   %x :   %x  \n", pma_debug_regs[i], reg));
	}
}


AN_NEXT_STEP
run_an_step (
  IN  ENET_DXE_PRIVATE_DATA *Private,
  IN       UINT32 XpcsBase,
  IN       UINT32 XgmacBase
  )
{
  UINTN WaitCount;
  UINTN RegVal;
  UINTN AnIntReg;
  XGBE_PHY_DATA *phy_data = Private->phy_data;

  DEBUG ((EFI_D_ERROR, " Private->an_mode = %d phy_data->cur_mode = %x \n" , Private->an_mode, phy_data->cur_mode));

  //if redriver is present, use an73 clause
  if (phy_data->redrv || Private->an_mode == XGBE_AN_MODE_CL73 ) {
  	enum xgbe_an cur_state = Private->an_state;
	
	xgbe_an37_disable (Private);
    xgbe_an_disable (Private);	
    xgbe_an73_clear_interrupts(XpcsBase);
	
    xgbe_an_init (Private, XpcsBase);
    xgbe_an_restart (Private);

	Private->an_result = XGBE_AN_READY;
	Private->an_state = XGBE_AN_READY;
	Private->kr_state = XGBE_RX_BPA;
	Private->kx_state = XGBE_RX_BPA;	

    XgbeHwinitDelay();
	DEBUG ((EFI_D_ERROR, "Start of run_an_step  \n"));
	//xgbe_an73_debug_registers(Private);

    WaitCount = 0;
    while (WaitCount < 10000) {

	  AnIntReg = XMDIO_READ (XpcsBase,  MDIO_MMD_AN, MDIO_AN_INT );
		
	  if( AnIntReg == 0){
		gBS->Stall (1000);
		WaitCount ++;
		/* Reissue interrupt if status is not clear */
		if (Private->irq_reissue_support)
			XP_IOWRITE(Private, XP_INT_REISSUE_EN, 1 << 3);
		
		continue;
	  }else{	  
	  		DEBUG ((EFI_D_ERROR, "AnIntReg = %x\n", AnIntReg));

			//xgbe_an73_disable_interrupts(XpcsBase);
			
			XMDIO_WRITE(XpcsBase, MDIO_MMD_AN, MDIO_AN_INT, ~AnIntReg);
			DEBUG ((EFI_D_ERROR, "After reset AnIntReg = %x\n", XMDIO_READ (XpcsBase,  MDIO_MMD_AN, MDIO_AN_INT )));
	  }
	  
next_int:

		if (AnIntReg & XGBE_AN_CL73_PG_RCV) {
			Private->an_state = XGBE_AN_PAGE_RECEIVED;
			DEBUG ((EFI_D_ERROR, "XGBE_AN_CL73_PG_RCV \n"));			
			AnIntReg &= ~XGBE_AN_CL73_PG_RCV;
			
		} else if (AnIntReg & XGBE_AN_CL73_INC_LINK) {
			DEBUG ((EFI_D_ERROR, "XGBE_AN_INCOMPAT_LINK \n"));
			Private->an_state = XGBE_AN_INCOMPAT_LINK;
			AnIntReg &= ~XGBE_AN_CL73_INC_LINK;
			
		} else if (AnIntReg & XGBE_AN_CL73_INT_CMPLT) {
			DEBUG ((EFI_D_ERROR, "XGBE_AN_COMPLETE \n"));		
			Private->an_state = XGBE_AN_COMPLETE;
			AnIntReg &= ~XGBE_AN_CL73_INT_CMPLT;
			AnIntReg &= ~XGBE_AN_CL73_INC_LINK;
						
		} else {
			Private->an_state = XGBE_AN_ERROR;
			DEBUG ((EFI_D_ERROR, "XGBE_AN_ERROR \n"));			
		}		

again:		
		cur_state = Private->an_state;

        XgbeHwinitDelay();		
		switch (Private->an_state) {
		case XGBE_AN_READY:
			Private->an_supported = 0;
			if(Private->an_result == XGBE_AN_COMPLETE) {
				XgbeHwinitDelay();
				return EXIT_AN_RUN;
			}
			break;

		case XGBE_AN_PAGE_RECEIVED:			
			Private->an_state = xgbe_an73_page_received(Private);
			Private->an_supported++;
			break;

		case XGBE_AN_INCOMPAT_LINK:
			Private->an_supported = 0;
			Private->parallel_detect = 0;
			Private->an_state = xgbe_an73_incompat_link(Private);
            if(Private->an_state == XGBE_AN_INCOMPAT_LINK){
				XgbeHwinitDelay();
				return RESTART_AN;
			}
				
			break;
			
		case XGBE_AN_COMPLETE:
			if(Private->an_supported == 0 && phy_data->cur_mode == XGBE_MODE_KR){
				Private->an_supported = 0;
				Private->parallel_detect = 0;
				Private->an_state = xgbe_an73_incompat_link(Private);
				if(Private->an_state == XGBE_AN_INCOMPAT_LINK){
					XgbeHwinitDelay();
					return RESTART_AN;
				}	
				break;
			}
			
            XgbeHwinitDelay();
			Private->parallel_detect = Private->an_supported ? 0 : 1;
			if(Private->parallel_detect )
				DEBUG ((EFI_D_ERROR, " Parallel detection successful\n"));
			else
				DEBUG ((EFI_D_ERROR, " Auto negotiation successful\n"));
			break;

		case XGBE_AN_NO_LINK:
			DEBUG ((EFI_D_ERROR, " XGBE_AN_NO_LINK\n"));
			break;
			
		default:
			Private->an_state = XGBE_AN_ERROR;
		}

		if (Private->an_state == XGBE_AN_NO_LINK) {
			AnIntReg = 0;
			xgbe_an73_clear_interrupts(XpcsBase);
			DEBUG ((EFI_D_ERROR, " XGBE_AN_NO_LINK\n"));
		} else if (Private->an_state == XGBE_AN_ERROR) {
			DEBUG ((EFI_D_ERROR, "error during auto-negotiation, state=%u\n", cur_state));
			AnIntReg = 0;
			xgbe_an73_clear_interrupts(XpcsBase);
			DEBUG ((EFI_D_ERROR, " XGBE_AN_ERROR\n"));
		}

		if (Private->an_state >= XGBE_AN_COMPLETE) {
			Private->an_result = Private->an_state;
			Private->an_state = XGBE_AN_READY;
			Private->kr_state = XGBE_RX_BPA;
			Private->kx_state = XGBE_RX_BPA;

			xgbe_phy_an_post(Private);
			xgbe_an73_enable_interrupts(XpcsBase);

			gBS->Stall (100);
		}


		if (cur_state != Private->an_state)
			goto again;

		if (AnIntReg)
			goto next_int;

	  	xgbe_an73_enable_interrupts(XpcsBase);	  
      	gBS->Stall (100);
      	WaitCount++;
    } 
  } else if (!phy_data->redrv) {
    xgbe_an37_disable (Private);
	xgbe_an73_disable (Private);
	xgbe_an73_clear_interrupts (XpcsBase);
    // Clear interrupt(s)
    RegVal = XMDIO_READ (XpcsBase, MDIO_MMD_VEND2, MDIO_VEND2_AN_STAT);
    RegVal &= ~XGBE_AN_CL37_INT_MASK;
    XMDIO_WRITE (XpcsBase, MDIO_MMD_VEND2, MDIO_VEND2_AN_STAT, RegVal);
    DEBUG ((EFI_D_ERROR, " Program AN registers\n"));
    xgbe_an37_init (Private, XpcsBase);
    //Eable Interrupt
    xgbe_an37_enable_interrupts (XpcsBase);
    // Restart AN
    xgbe_an37_set (XpcsBase, TRUE, TRUE);
    gBS->Stall (100);

    // Wait for interrupt
    WaitCount = 0;
    while (WaitCount < 1000) {
      gBS->Stall (100);
      RegVal = XMDIO_READ (XpcsBase, MDIO_MMD_VEND2, MDIO_VEND2_AN_STAT);
      DEBUG ((EFI_D_ERROR, " Auto Negotiation started, RegVal = %x\n", RegVal));
      if (RegVal & XGBE_AN_CL37_INT_MASK) {
        //Clear interrupt
        RegVal &= ~XGBE_AN_CL37_INT_MASK;
        XMDIO_WRITE (XpcsBase, MDIO_MMD_VEND2, MDIO_VEND2_AN_STAT, RegVal);
        DEBUG ((EFI_D_ERROR, "The set interrupt cleared \n"));
        return READ_LP;
      }
      gBS->Stall (100);
      WaitCount++;
    } // end of wait for INT
 }
  return RESTART_AN;
}

AN_NEXT_STEP
read_lp_step (
  IN  UINTN XpcsBase,
  IN  ENET_DXE_PRIVATE_DATA *Private
  )
{
  UINTN AnLp2;
  UINTN AnIntReg;
  XGBE_PHY_DATA *phy_data = Private->phy_data;

  if (phy_data->redrv) {
  	
    AnLp2 = XMDIO_READ (XpcsBase, MDIO_MMD_AN, MDIO_AN_LP_ABL2);
	if(AnLp2 & 0x80)
	{
		DEBUG ((EFI_D_ERROR, ":: LP supports 10G d\n"));
	}else if(AnLp2 & 0x20){
		DEBUG ((EFI_D_ERROR, ":: LP supports 1G d\n"));
	}
    if (AnLp2 & 0x80) {
      // LP supports KR - 10GB
      switch ( mCurrLanSpeed) {
      case 10:
        break;

      case 1:
		xgbe_switch_mode(Private);
        return RESTART_AN;             // and restart AN

      case 2:
        if (AnLp2 & 0x20) {
          return WAIT_INT_CMPLT;
        }
      return EXIT_AN_RUN;

      default:
        DEBUG ((EFI_D_ERROR, "::Unsupported LP speed\n"));
        return EXIT_AN_RUN;
      }
      // Check for Fault
      AnIntReg = XMDIO_READ (XpcsBase,  MDIO_MMD_AN, MDIO_AN_INT );
      if (AnIntReg & (AN_INC_LNK | AN_INT_CMPLT)) {
        return RESTART_AN;
      }
      return KR_TRAIN;

    } else if (AnLp2 & 0x20) {
    // LP supports KX - 1GB
      switch (mCurrLanSpeed) {
      case  1:
      case  2:
        break;

      case  10:
		xgbe_switch_mode(Private);
        return RESTART_AN;

      default:
        DEBUG ((EFI_D_ERROR, "::Unsupported LP speed\n"));
        return EXIT_AN_RUN;
      }
      return WAIT_INT_CMPLT;
    } else {
    // unsupported
      DEBUG ((EFI_D_ERROR, "::Unsupported LP speed\n"));
      return EXIT_AN_RUN;
    }
  } else if (!phy_data->redrv) {
    switch (mCurrLanSpeed) {
    case  1:
    case  2:
      break;

    case  10:
      xgbe_switch_mode(Private);
      return RESTART_AN;

    default:
      DEBUG ((EFI_D_ERROR, "::Unsupported LP speed\n"));
      return EXIT_AN_RUN;
    }
    return WAIT_INT_CMPLT;
  }
  return EXIT_AN_RUN;
}

AN_NEXT_STEP
kr_train_step (
  IN  UINTN XpcsBase
  )
{
  UINTN AnIntReg;
  AnIntReg = XMDIO_READ (XpcsBase,  MDIO_MMD_AN, MDIO_AN_INT );
  DEBUG ((EFI_D_ERROR, "::kr_train_step AnIntReg = %x \n" , AnIntReg));
  if (AnIntReg & AN_PG_RCV) {
    XMDIO_WRITE (XpcsBase, MDIO_MMD_AN, MDIO_AN_INT, (AnIntReg & ~AN_PG_RCV));
    gBS->Stall (100);
    XMDIO_WRITE (XpcsBase, MDIO_MMD_AN, MDIO_AN_INT, (AnIntReg & ~AN_PG_RCV));
  }

  if (EFI_DEVICE_ERROR == xgbe_check_kr_train (XpcsBase)) {
  	DEBUG ((EFI_D_ERROR, "::kr_train_step RESTART_AN returning \n"));
    return RESTART_AN;
  }
  AnIntReg = XMDIO_READ (XpcsBase, MDIO_MMD_AN, MDIO_AN_INT );
  if (AnIntReg & AN_INC_LNK) {
  	DEBUG ((EFI_D_ERROR, "::kr_train_step RESTART_AN returning \n"));
    return RESTART_AN;
  }
  DEBUG ((EFI_D_ERROR, "::kr_train_step WAIT_INT_CMPLT returning \n"));
  return WAIT_INT_CMPLT;
}

AN_NEXT_STEP
wait_int_cmplt_step (
  IN  ENET_DXE_PRIVATE_DATA *Private,
  IN  UINTN XpcsBase
  )
{
  UINTN WaitCount;
  UINTN AnIntReg;
  XGBE_PHY_DATA *phy_data = Private->phy_data;
  // Wait for INT_CMPLT
  WaitCount = 0;
  DEBUG ((EFI_D_ERROR, "::wait_int_cmplt_step \n"));
  if (phy_data->redrv) {
    while (WaitCount < 10000) {
    // 1000 mS
      AnIntReg = XMDIO_READ (XpcsBase,  MDIO_MMD_AN, MDIO_AN_INT );
      if (AnIntReg & AN_PG_RCV) {
        XMDIO_WRITE (XpcsBase, MDIO_MMD_AN, MDIO_AN_INT, (AnIntReg & ~AN_PG_RCV));
        gBS->Stall (100);
        XMDIO_WRITE (XpcsBase, MDIO_MMD_AN, MDIO_AN_INT, (AnIntReg & ~AN_PG_RCV));
      }
      AnIntReg = XMDIO_READ (XpcsBase,  MDIO_MMD_AN, MDIO_AN_INT );
      if (AnIntReg & AN_INC_LNK) {
        return RESTART_AN;
      }
      if (AnIntReg & AN_INT_CMPLT) {
      // Clear INT_CMPLT
        XMDIO_WRITE (XpcsBase, MDIO_MMD_AN, MDIO_AN_INT, (AnIntReg & ~AN_INT_CMPLT));
        gBS->Stall (100);
        XMDIO_WRITE (XpcsBase, MDIO_MMD_AN, MDIO_AN_INT, (AnIntReg & ~AN_INT_CMPLT));
        return EXIT_AN_RUN;
      }
      gBS->Stall (100);
      WaitCount++;
    }
  } else if (!phy_data->redrv) {
    xgbe_an37_set ((UINT32)XpcsBase, TRUE, TRUE);
    gBS->Stall (100);
    WaitCount = 0;
    while (WaitCount < 10000) {
      AnIntReg = XMDIO_READ (XpcsBase, MDIO_MMD_VEND2, MDIO_VEND2_AN_STAT );
      if (AnIntReg & AN_INT_CMPLT) {
        // Clear INT_CMPLT
        XMDIO_WRITE (XpcsBase, MDIO_MMD_VEND2, MDIO_VEND2_AN_STAT, (AnIntReg & ~AN_INT_CMPLT));
        gBS->Stall (100);
        XMDIO_WRITE (XpcsBase, MDIO_MMD_VEND2, MDIO_VEND2_AN_STAT, (AnIntReg & ~AN_INT_CMPLT));
        return EXIT_AN_RUN;
      }
      gBS->Stall (100);
      WaitCount++;
    }
  }
  // if we are here - no INT_CMPLT received
  return RESTART_AN;
}

BOOLEAN
xgbe_an_state_machine (
  IN  ENET_DXE_PRIVATE_DATA *Private
  )
{
  UINT32 XpcsBase;
  UINT32 XgmacBase;
  UINTN AnCycleCount;
  UINTN RegVal;
  UINTN WaitCount = 0;
  AN_NEXT_STEP NextStep;
  XGBE_PHY_DATA *phy_data = Private->phy_data;  	  
  XpcsBase = Private->xpcs_regs;
  XgmacBase = Private->xgmac_pdata.xgmac_regs;

  if (Private->phy.autoneg != AUTONEG_ENABLE && phy_data->cur_mode == XGBE_MODE_SFI) {

	/* Disable auto-negotiation */
	xgbe_an73_disable(Private);
	xgbe_an37_disable(Private);

	gBS->Stall (1000);

	while(WaitCount < 1000) {	
		
		// Get and display Link status from PCS register
		RegVal = XMDIO_READ (XpcsBase, MDIO_MMD_PCS, MDIO_PCS_STS1);			

		if ((RegVal & PCS_STS1_RLU) != 0) {
			DEBUG ((EFI_D_ERROR, "::LINK SPEED : %d  PCS LINK STS - ", mCurrLanSpeed));
			DEBUG ((EFI_D_ERROR, "UP\n"));
			DEBUG ((EFI_D_ERROR, "STS1 RegVal : %x ", RegVal));
			//StartTmr (Private);
			return  TRUE;
		} else {
			//DEBUG ((EFI_D_ERROR, "::LINK SPEED : %d  PCS LINK STS - ", mCurrLanSpeed));
			//DEBUG ((EFI_D_ERROR, "autoneg DISABLED DOWN\n"));
		}
		
		gBS->Stall (500);
		WaitCount++;
	}	
	DEBUG ((EFI_D_ERROR, "::LINK SPEED : %d  PCS LINK STS - ", mCurrLanSpeed));
	DEBUG ((EFI_D_ERROR, "DOWN\n"));
	DEBUG ((EFI_D_ERROR, "Returning from xgbe_an_state_machine\n"));
	return  FALSE;
  	
  }

  for (AnCycleCount = 0; AnCycleCount < AN_MAX_RETR; AnCycleCount++) {
      	
    NextStep = run_an_step (Private, XpcsBase, XgmacBase);
    if ( NextStep == RESTART_AN ) {
      continue;
    }
	UpdateLinkStatus (Private);
    if(Private->Mode.MediaPresent ==  FALSE)
        continue;
	if(NextStep ==  READ_LP)
    	NextStep = read_lp_step (XpcsBase, Private);
    if ( NextStep == EXIT_AN_RUN ) {
      break;
    }
    if ( NextStep == RESTART_AN ) {
      continue;
    }
    if ( NextStep == KR_TRAIN ) {
      NextStep = kr_train_step (XpcsBase);
      if ( NextStep == RESTART_AN ) {
        continue;
      }
    }
	if ( NextStep != EXIT_AN_RUN ){
    	NextStep = wait_int_cmplt_step (Private, XpcsBase);
	}
    if ( NextStep == EXIT_AN_RUN ) {
      break;
    }
  }

  DEBUG ((EFI_D_ERROR, "::LINK SPEED : %d  PCS LINK STS - ", mCurrLanSpeed));
  // Get and display Link status from PCS register

  RegVal = XMDIO_READ (XpcsBase, MDIO_MMD_PCS, MDIO_PCS_STS1);
  gBS->Stall (1000);
  RegVal = XMDIO_READ (XpcsBase, MDIO_MMD_PCS, MDIO_PCS_STS1);

  if ((RegVal & PCS_STS1_RLU) != 0) {
    DEBUG ((EFI_D_ERROR, "UP\n"));
	DEBUG ((EFI_D_ERROR, "STS1 RegVal : %x ", RegVal));
  	//StartTmr (Private);
	return  TRUE;
  } else {
    DEBUG ((EFI_D_ERROR, "DOWN\n"));
	DEBUG ((EFI_D_ERROR, "Returning from xgbe_an_state_machine\n"));
	return  FALSE;
  }
}

VOID
xgbe_an73_set (
  UINT32 XpcsBase,
  BOOLEAN enable,
  BOOLEAN restart
  )
{
  UINTN reg;
  DEBUG ((EFI_D_ERROR, "xgbe_an73_set\n" ));
  
  /* Disable KR training for now */
  reg = XMDIO_READ(XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_PMD_CTRL);
  reg &= ~XGBE_KR_TRAINING_ENABLE;
  XMDIO_WRITE(XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_PMD_CTRL, reg);

  
  reg = XMDIO_READ (XpcsBase, MDIO_MMD_AN, MDIO_CTRL1);
  reg &= ~MDIO_AN_CTRL1_ENABLE;

  if (enable) {
    reg |= MDIO_AN_CTRL1_ENABLE;
  }
  if (restart) {
    reg |= MDIO_AN_CTRL1_RESTART;
  }
  XMDIO_WRITE (XpcsBase, MDIO_MMD_AN, MDIO_CTRL1, reg);
}

VOID
xgbe_an37_set (
  UINT32 XpcsBase,
  BOOLEAN enable,
  BOOLEAN restart
  )
{
  UINTN reg;
  DEBUG ((EFI_D_ERROR, "xgbe_an37_set\n" ));
  reg = XMDIO_READ (XpcsBase, MDIO_MMD_VEND2, MDIO_CTRL1);
  reg &= ~MDIO_VEND2_CTRL1_AN_ENABLE;

  if (enable) {
    reg |= MDIO_VEND2_CTRL1_AN_ENABLE;
    DEBUG ((EFI_D_ERROR, "xgbe_an37 set\n" ));
  }
  if (restart) {
    DEBUG ((EFI_D_ERROR, "xgbe_an37 Restart\n" ));
    reg |= MDIO_VEND2_CTRL1_AN_RESTART;
  }
  XMDIO_WRITE (XpcsBase, MDIO_MMD_VEND2, MDIO_CTRL1, reg);
}

VOID
xgbe_an_set (
  ENET_DXE_PRIVATE_DATA *pdata,
  UINT32 XpcsBase,
  BOOLEAN enable,
  BOOLEAN restart
  )
{
  switch (pdata->an_mode) {
  case XGBE_AN_MODE_CL73:
  case XGBE_AN_MODE_CL73_REDRV:
	  xgbe_an73_set(XpcsBase , enable , restart);
	  break;
  case XGBE_AN_MODE_CL37:
  case XGBE_AN_MODE_CL37_SGMII:
	  xgbe_an37_set(XpcsBase , enable , restart);
	  break;
  default:
	  break;
  }
}

VOID
STATIC
xgbe_an73_disable (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  UINT32 XpcsBase;
  DEBUG ((EFI_D_ERROR, "xgbe_an73_disable\n" ));
  XpcsBase = pdata->xpcs_regs;
  xgbe_an73_set (XpcsBase, FALSE, FALSE);
  xgbe_an73_disable_interrupts (XpcsBase);
  DEBUG ((EFI_D_ERROR, "CL73 AN disabled\n" ));

}


VOID
STATIC
xgbe_an37_disable (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  UINTN XpcsBase;
  DEBUG ((EFI_D_ERROR, "xgbe_an37_disable\n" ));
  XpcsBase = pdata->xpcs_regs;
  xgbe_an37_set ((UINT32)XpcsBase, FALSE, FALSE);
  xgbe_an37_disable_interrupts (XpcsBase);
  DEBUG ((EFI_D_ERROR, "CL37 AN disabled\n" ));
}

VOID
STATIC
xgbe_an_disable (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  DEBUG ((EFI_D_ERROR, "xgbe_an_disable\n" ));

  xgbe_phy_an_post(pdata);
  
  switch (pdata->an_mode) {
  case XGBE_AN_MODE_CL73:
  case XGBE_AN_MODE_CL73_REDRV:
	  xgbe_an73_disable(pdata);
	  break;
  case XGBE_AN_MODE_CL37:
  case XGBE_AN_MODE_CL37_SGMII:
	  xgbe_an37_disable(pdata);
	  break;
  default:
	  break;
  }
}


VOID xgmac_get_all_hw_features (
  IN  xgmac_prv_data *pdata
  )
{
  UINT32  mac_hfr0;
  UINT32  mac_hfr1;
  UINT32  mac_hfr2;
  xgmac_hw_features *hw_feat = &pdata->hw_feat;

  mac_hfr0 = XGMAC_IOREAD32 (pdata, MAC_HWF0R);
  mac_hfr1 = XGMAC_IOREAD32 (pdata, MAC_HWF1R);
  mac_hfr2 = XGMAC_IOREAD32 (pdata, MAC_HWF2R);
  SetMem (hw_feat, sizeof (pdata->hw_feat), 0);
  hw_feat->version = XGMAC_IOREAD32 (pdata, MAC_VR);

  // Hardware feature register 0
  hw_feat->gmii        = XGMAC_GET_BITS (mac_hfr0, MAC_HWF0R, GMIISEL);
  hw_feat->vlhash      = XGMAC_GET_BITS (mac_hfr0, MAC_HWF0R, VLHASH);
  hw_feat->sma         = XGMAC_GET_BITS (mac_hfr0, MAC_HWF0R, SMASEL);
  hw_feat->rwk         = XGMAC_GET_BITS (mac_hfr0, MAC_HWF0R, RWKSEL);
  hw_feat->mgk         = XGMAC_GET_BITS (mac_hfr0, MAC_HWF0R, MGKSEL);
  hw_feat->mmc         = XGMAC_GET_BITS (mac_hfr0, MAC_HWF0R, MMCSEL);
  hw_feat->aoe         = XGMAC_GET_BITS (mac_hfr0, MAC_HWF0R, ARPOFFSEL);
  hw_feat->ts          = XGMAC_GET_BITS (mac_hfr0, MAC_HWF0R, TSSEL);
  hw_feat->eee         = XGMAC_GET_BITS (mac_hfr0, MAC_HWF0R, EEESEL);
  hw_feat->tx_coe      = XGMAC_GET_BITS (mac_hfr0, MAC_HWF0R, TXCOESEL);
  hw_feat->rx_coe      = XGMAC_GET_BITS (mac_hfr0, MAC_HWF0R, RXCOESEL);
  hw_feat->addn_mac    = XGMAC_GET_BITS (mac_hfr0, MAC_HWF0R,
                            ADDMACADRSEL);
  hw_feat->ts_src      = XGMAC_GET_BITS (mac_hfr0, MAC_HWF0R, TSSTSSEL);
  hw_feat->sa_vlan_ins = XGMAC_GET_BITS (mac_hfr0, MAC_HWF0R, SAVLANINS);

  // Hardware feature register 1
  hw_feat->rx_fifo_size  = XGMAC_GET_BITS (mac_hfr1, MAC_HWF1R,
                            RXFIFOSIZE);
  hw_feat->tx_fifo_size  = XGMAC_GET_BITS (mac_hfr1, MAC_HWF1R,
                             TXFIFOSIZE);
  hw_feat->adv_ts_hi     = XGMAC_GET_BITS (mac_hfr1, MAC_HWF1R, ADVTHWORD);
  hw_feat->dma_width     = XGMAC_GET_BITS (mac_hfr1, MAC_HWF1R, ADDR64);
  hw_feat->dcb           = XGMAC_GET_BITS (mac_hfr1, MAC_HWF1R, DCBEN);
  hw_feat->sph           = XGMAC_GET_BITS (mac_hfr1, MAC_HWF1R, SPHEN);
  hw_feat->tso           = XGMAC_GET_BITS (mac_hfr1, MAC_HWF1R, TSOEN);
  hw_feat->dma_debug     = XGMAC_GET_BITS (mac_hfr1, MAC_HWF1R, DBGMEMA);
  hw_feat->rss           = XGMAC_GET_BITS (mac_hfr1, MAC_HWF1R, RSSEN);
  hw_feat->tc_cnt        = XGMAC_GET_BITS (mac_hfr1, MAC_HWF1R, NUMTC);
  hw_feat->hash_table_size = XGMAC_GET_BITS (mac_hfr1, MAC_HWF1R,
                               HASHTBLSZ);
  hw_feat->l3l4_filter_num = XGMAC_GET_BITS (mac_hfr1, MAC_HWF1R,
                              L3L4FNUM);

  // Hardware feature register 2
  hw_feat->rx_q_cnt     = XGMAC_GET_BITS (mac_hfr2, MAC_HWF2R, RXQCNT);
  hw_feat->tx_q_cnt     = XGMAC_GET_BITS (mac_hfr2, MAC_HWF2R, TXQCNT);
  hw_feat->rx_ch_cnt    = XGMAC_GET_BITS (mac_hfr2, MAC_HWF2R, RXCHCNT);
  hw_feat->tx_ch_cnt    = XGMAC_GET_BITS (mac_hfr2, MAC_HWF2R, TXCHCNT);
  hw_feat->pps_out_num  = XGMAC_GET_BITS (mac_hfr2, MAC_HWF2R, PPSOUTNUM);
  hw_feat->aux_snap_num = XGMAC_GET_BITS (mac_hfr2, MAC_HWF2R, AUXSNAPNUM);

  //Translate the Hash Table size into actual number */
  switch (hw_feat->hash_table_size) {
    case 0:
      break;
    case 1:
      hw_feat->hash_table_size = 64;
      break;
    case 2:
      hw_feat->hash_table_size = 128;
      break;
    case 3:
      hw_feat->hash_table_size = 256;
      break;
  }

  // Translate the address width setting into actual number
  switch (hw_feat->dma_width) {
    case 0:
      hw_feat->dma_width = 32;
      break;
    case 1:
      hw_feat->dma_width = 40;
      break;
    case 2:
    hw_feat->dma_width = 48;
    break;
    default:
      hw_feat->dma_width = 32;
  }

  //The Queue, Channel and TC counts are zero based so increment them
  // to get the actual number

  hw_feat->rx_q_cnt++;
  hw_feat->tx_q_cnt++;
  hw_feat->rx_ch_cnt++;
  hw_feat->tx_ch_cnt++;
  hw_feat->tc_cnt++;

  // Translate the fifo sizes into actual numbers
  hw_feat->rx_fifo_size = 1 << (hw_feat->rx_fifo_size + 7);
  hw_feat->tx_fifo_size = 1 << (hw_feat->tx_fifo_size + 7);
}

VOID
xgmac_default_config (
  IN       xgmac_prv_data *pdata
  )
{
  pdata->pblx8 = 1;
  pdata->tx_sf_mode = XGMAC_TSF_ENABLE;
  pdata->tx_threshold = XGMAC_TX_THRESHOLD_64;
  pdata->tx_pbl = XGMAC_PBL_16;
  pdata->tx_osp_mode = 1;
  pdata->rx_sf_mode = XGMAC_RSF_DISABLE;
  pdata->rx_threshold = XGMAC_RX_THRESHOLD_64;
  pdata->rx_pbl = XGMAC_PBL_16;
  pdata->flow_ctrl = XGMAC_FLOW_CTRL_TX_RX;
  pdata->oldflow_ctrl = XGMAC_FLOW_CTRL_TX_RX;
  pdata->power_down = 0;
  
}

UINT32
STATIC
flush_tx_queues (
  IN  xgmac_prv_data *pdata
  )
{
  UINT32  i;
  UINT32  count;
   DEBUG ((EFI_D_ERROR, "-->flush_tx_queues\n"));

  for (i = 0; i < pdata->hw_feat.tx_q_cnt; i++) {
    XGMAC_MTL_IOWRITE32_BITS (pdata, i, MTL_Q_TQOMR, FTQ, 0x1);
  }
  // Poll Until Poll Condition
  for (i = 0; i < pdata->hw_feat.tx_q_cnt; i++) {
    count = 2000;
    while (count-- && XGMAC_MTL_IOREAD32_BITS (pdata, i,
                MTL_Q_TQOMR, FTQ))
      gBS->Stall (1000);

    if (!count) {
      return (UINT32) - 1;
    }
  }
   DEBUG ((EFI_D_ERROR, "X--flush_tx_queues\n"));
  return 0;
}

VOID
STATIC
config_dma_bus (
  IN       xgmac_prv_data *pdata
  )
{
  // Set enhanced addressing mode
  XGMAC_IOWRITE32_BITS (pdata, DMA_SBMR, EAME, 0x1);
  // Set the System Bus mode
  XGMAC_IOWRITE32_BITS (pdata, DMA_SBMR, UNDEF, 0x1);
  XGMAC_IOWRITE32_BITS (pdata, DMA_SBMR, BLEN_256, 0x1);
}

VOID
STATIC
config_dma_cache (
  IN  xgmac_prv_data *pdata
  )
{
  UINT32  arcache;
  UINT32  awcache;

  arcache = 0;
  XGMAC_SET_BITS (arcache, DMA_AXIARCR, DRC, DMA_ARCACHE_SETTING_CE);
  XGMAC_SET_BITS (arcache, DMA_AXIARCR, DRD, DMA_ARDOMAIN_SETTING_CE);
  XGMAC_SET_BITS (arcache, DMA_AXIARCR, TEC, DMA_ARCACHE_SETTING_CE);
  XGMAC_SET_BITS (arcache, DMA_AXIARCR, TED, DMA_ARDOMAIN_SETTING_CE);
  XGMAC_SET_BITS (arcache, DMA_AXIARCR, THC, DMA_ARCACHE_SETTING_CE);
  XGMAC_SET_BITS (arcache, DMA_AXIARCR, THD, DMA_ARDOMAIN_SETTING_CE);

  XGMAC_IOWRITE32 (pdata, DMA_AXIARCR, arcache);

  awcache = 0;
  XGMAC_SET_BITS (awcache, DMA_AXIAWCR, DWC, DMA_AWCACHE_SETTING_CE);
  XGMAC_SET_BITS (awcache, DMA_AXIAWCR, DWD, DMA_AWDOMAIN_SETTING_CE);
  XGMAC_SET_BITS (awcache, DMA_AXIAWCR, RPC, DMA_AWCACHE_SETTING_CE);
  XGMAC_SET_BITS (awcache, DMA_AXIAWCR, RPD, DMA_AWDOMAIN_SETTING_CE);
  XGMAC_SET_BITS (awcache, DMA_AXIAWCR, RHC, DMA_AWCACHE_SETTING_CE);
  XGMAC_SET_BITS (awcache, DMA_AXIAWCR, RHD, DMA_AWDOMAIN_SETTING_CE);
  XGMAC_SET_BITS (awcache, DMA_AXIAWCR, TDC, DMA_AWCACHE_SETTING_CE);
  XGMAC_SET_BITS (awcache, DMA_AXIAWCR, TDD, DMA_AWDOMAIN_SETTING_CE);

  XGMAC_IOWRITE32 (pdata, DMA_AXIAWCR, awcache);
}

INT32
STATIC
set_promiscuous_mode (
  IN  xgmac_prv_data *pdata,
  IN  UINT32 enable
  )
{
  UINT32 val;

  val = enable ? 1 : 0;
  if (XGMAC_IOREAD32_BITS (pdata, MAC_PFR, PR) == val) {
    return 0;
  }

  XGMAC_IOWRITE32_BITS (pdata, MAC_PFR, PR, val);
  return 0;
}

INT32
STATIC
set_all_multicast_mode (
  IN       xgmac_prv_data *pdata,
  IN       UINT32 enable
  )
{
  UINT32 val;
  val = enable ? 1 : 0;
  if (XGMAC_IOREAD32_BITS (pdata, MAC_PFR, PM) == val) {
    return 0;
  }
  XGMAC_IOWRITE32_BITS (pdata, MAC_PFR, PM, val);
  return 0;
}

INT32
STATIC
set_addn_mac_addrs (
  IN       ENET_DXE_PRIVATE_DATA *Private,
  IN       UINT32 am_mode
  )
{
  xgmac_prv_data *pdata;
  UINT32 mac_reg;
  UINT32 mac_addr_hi;
  UINT32 mac_addr_lo;
  UINT32 mac_addr_tmp;
  UINT8 *mac_addr;
  UINT32 i;

  pdata = &Private->xgmac_pdata;
  XGMAC_IOWRITE32_BITS (pdata, MAC_PFR, HUC, 0);
  XGMAC_IOWRITE32_BITS (pdata, MAC_PFR, HMC, 0);

  i = 0;
  mac_addr_tmp = 0;
  mac_reg = MAC_MACA1HR;

  if (!am_mode) {
    mac_addr_lo = mac_addr_hi = 0;
    mac_addr = (UINT8 *)&mac_addr_lo;
    mac_addr_tmp = Private->DevicePath.EthDevicePath.MacAddress.Addr[0];
    SET_BIT_FIELD (mac_addr_tmp, 0, 1, 1);
    mac_addr[0] = (UINT8)mac_addr_tmp;
    mac_addr[1] = Private->DevicePath.EthDevicePath.MacAddress.Addr[1];
    mac_addr[2] = Private->DevicePath.EthDevicePath.MacAddress.Addr[2];
    mac_addr[3] = Private->DevicePath.EthDevicePath.MacAddress.Addr[3];
    mac_addr = (UINT8 *)&mac_addr_hi;
    mac_addr[0] = Private->DevicePath.EthDevicePath.MacAddress.Addr[4];
    mac_addr[1] = Private->DevicePath.EthDevicePath.MacAddress.Addr[5];

    XGMAC_SET_BITS (mac_addr_hi, MAC_MACA1HR, AE, 1);

    XGMAC_IOWRITE32 (pdata, mac_reg, mac_addr_hi);
    mac_reg += MAC_MACA_INC;
    XGMAC_IOWRITE32 (pdata, mac_reg, mac_addr_lo);
    mac_reg += MAC_MACA_INC;
  } else {
    mac_addr_lo = mac_addr_hi = 0;
    mac_addr = (UINT8 *)&mac_addr_lo;
    mac_addr_tmp = Private->DevicePath.EthDevicePath.MacAddress.Addr[0];
    SET_BIT_FIELD (mac_addr_tmp, 0, 1, 0);
    mac_addr[0] = (UINT8)mac_addr_tmp;
    mac_addr[1] = Private->DevicePath.EthDevicePath.MacAddress.Addr[1];
    mac_addr[2] = Private->DevicePath.EthDevicePath.MacAddress.Addr[2];
    mac_addr[3] = Private->DevicePath.EthDevicePath.MacAddress.Addr[3];
    mac_addr = (UINT8 *)&mac_addr_hi;
    mac_addr[0] = Private->DevicePath.EthDevicePath.MacAddress.Addr[4];
    mac_addr[1] = Private->DevicePath.EthDevicePath.MacAddress.Addr[5];

    XGMAC_SET_BITS (mac_addr_hi, MAC_MACA1HR, AE, 1);
    XGMAC_IOWRITE32 (pdata, mac_reg, mac_addr_hi);
    mac_reg += MAC_MACA_INC;
    XGMAC_IOWRITE32 (pdata, mac_reg, mac_addr_lo);
    mac_reg += MAC_MACA_INC;
  }
  // Clear remaining additional MAC address entries
  for (; i < pdata->hw_feat.addn_mac; i++) {
    XGMAC_IOWRITE32 (pdata, mac_reg, 0);
    mac_reg += MAC_MACA_INC;
    XGMAC_IOWRITE32 (pdata, mac_reg, 0);
    mac_reg += MAC_MACA_INC;
  }
  return 0;
}

VOID
STATIC
xgmac_set_rx_mode (
  IN       ENET_DXE_PRIVATE_DATA *Private
  )
{
  UINT32 pr_mode;
  UINT32 am_mode;

  pr_mode = 1;
  am_mode = 1;

  DEBUG ((EFI_D_ERROR, "-->xgmac_set_rx_mode\n"));

  set_promiscuous_mode (&Private->xgmac_pdata, pr_mode);
  set_all_multicast_mode (&Private->xgmac_pdata, am_mode);
  if (!pr_mode) {
    set_addn_mac_addrs (Private, am_mode);
  }
  DEBUG ((EFI_D_ERROR, "X--xgmac_set_rx_mode\n"));
}

INT32
STATIC
config_osp_mode (
  IN       xgmac_prv_data *pdata
  )
{
  xgmac_channel *channel;

  channel = &pdata->channel;
  XGMAC_DMA_IOWRITE32_BITS (channel, DMA_CH_TCR, OSP, pdata->tx_osp_mode);
  return 0;
}

INT32
STATIC
config_pblx8 (
  IN       xgmac_prv_data *pdata
  )
{
  xgmac_channel *channel;

  channel = &pdata->channel;
  XGMAC_DMA_IOWRITE32_BITS (channel, DMA_CH_CR, PBLX8, pdata->pblx8);

  return 0;
}

INT32
STATIC
config_tx_pbl_val (
  IN       xgmac_prv_data *pdata
  )
{
  xgmac_channel *channel;

  channel = &pdata->channel;
  XGMAC_DMA_IOWRITE32_BITS (channel, DMA_CH_TCR, PBL, pdata->tx_pbl);

  return 0;
}

INT32
STATIC
config_rx_pbl_val (
  IN       xgmac_prv_data *pdata
  )
{
  xgmac_channel *channel;

  channel = &pdata->channel;
  XGMAC_DMA_IOWRITE32_BITS (channel, DMA_CH_RCR, PBL, pdata->rx_pbl);

  return 0;
}

INT32
STATIC
config_rx_coalesce (
  IN      xgmac_prv_data *pdata
  )
{
  xgmac_channel *channel;
  pdata->rx_use_riwt = (pdata->rx_riwt || pdata->rx_frames) ? 1 : 0;
  channel = &pdata->channel;
  XGMAC_DMA_IOWRITE32_BITS (channel, DMA_CH_RIWT, RWT, pdata->rx_riwt);
  return 0;
}

VOID
STATIC
config_rx_buffer_size (
  IN       xgmac_prv_data *pdata
  )
{
  xgmac_channel *channel;
  channel = &pdata->channel;
  XGMAC_DMA_IOWRITE32_BITS (channel, DMA_CH_RCR, RBSZ, pdata->rx_buf_size);
}

VOID
STATIC
config_tso_mode (
  IN       xgmac_prv_data *pdata
  )
{
  xgmac_channel *channel;
  channel = &pdata->channel;
  XGMAC_DMA_IOWRITE32_BITS (channel, DMA_CH_TCR, TSE, 1);
}

VOID
STATIC
tx_desc_init (
  IN       ENET_DXE_PRIVATE_DATA *Private
  )
{
  xgmac_channel *channel;
  UINT32 i;
  UINT32 Index;  

  channel = &Private->xgmac_pdata.channel;

  // Initialize all descriptors
  for (i = 1; i <= RX_DESC_CNT; i++) {
	  /* Reset the Tx descriptor
	   *   Set buffer 1 (lo) address to zero
	   *   Set buffer 1 (hi) address to zero
	   *   Reset all other control bits (IC, TTSE, B2L & B1L)
	   *   Reset all other control bits (OWN, CTXT, FD, LD, CPC, CIC, etc)
	   */
	  Index = (i - 1);
	  Private->desc_tx[Index].TDES0 = 0;
	  Private->desc_tx[Index].TDES1 = 0;
	  Private->desc_tx[Index].TDES2 = 0;
	  Private->desc_tx[Index].TDES3 = 0;
  }

  // Make sure everything is written to the descriptor(s) before
  // telling the device about them
  //
  Private->desc_tx_index = 0;   // Init descriptor index

  // Update the total no of Tx descriptors count
  XGMAC_DMA_IOWRITE32 (channel, DMA_CH_TDRLR, TX_DESC_CNT - 1);

  // Update the starting address of desc chain/ring
  XGMAC_DMA_IOWRITE32 (channel, DMA_CH_TDLR_HI,
          upper_32_bits (Private->desc_tx));
  XGMAC_DMA_IOWRITE32 (channel, DMA_CH_TDLR_LO,
          lower_32_bits (Private->desc_tx));
}

VOID
STATIC
rx_desc_init (
  IN       ENET_DXE_PRIVATE_DATA *Private
  )
{
  xgmac_channel *channel;
  UINT32 rx_coalesce;
  UINT32 rx_frames;
  UINT32 i;
  UINT32 Index;

  channel = &Private->xgmac_pdata.channel;

  rx_coalesce = channel->pdata->rx_use_riwt;
  rx_frames = channel->pdata->rx_frames;

  // Initialize all descriptors
  for (i = 1; i <= RX_DESC_CNT; i++) {
    // Initialize Rx descriptor
    //   Set buffer 1 (lo) address to dma address (lo)
    //   Set buffer 1 (hi) address to dma address (hi)
    //   Set buffer 2 (lo) address to zero
    //   Set buffer 2 (hi) address to zero and set control
    //   bits OWN and INTE as appropriate
    //
    Index = (i - 1);
    Private->desc_rx[Index].RDES0 = lower_32_bits (Private->pkt_rx_dma[Index].DeviceAddress);
    Private->desc_rx[Index].RDES1 = upper_32_bits (Private->pkt_rx_dma[Index].DeviceAddress);
    Private->desc_rx[Index].RDES2 = 0;
    Private->desc_rx[Index].RDES3 = 0;
    XGMAC_SET_BITS (Private->desc_rx[Index].RDES3, RX_NORMAL_DESC3, OWN, 0x1);
    XGMAC_SET_BITS (Private->desc_rx[Index].RDES3, RX_NORMAL_DESC3, INTE, 0x1);
    //rdata->interrupt = 1;
    Private->desc_rx_interrupt[Index] = TRUE;
    if (rx_coalesce && (!rx_frames || (i % rx_frames))) {
      // Clear interrupt on completion bit
      XGMAC_SET_BITS (Private->desc_rx[Index].RDES3, RX_NORMAL_DESC3, INTE, 0);
      //rdata->interrupt = 0;
      Private->desc_rx_interrupt[Index] = FALSE;
    }
  }

  // Make sure everything is written to the descriptors before
  // telling the device about them
  //

  Private->desc_rx_index = 0;   // Init descriptor index

  // Update the total no of Rx descriptors count
  XGMAC_DMA_IOWRITE32 (channel, DMA_CH_RDRLR, RX_DESC_CNT - 1);

  // Update the starting address of desc chain/ring
  XGMAC_DMA_IOWRITE32 (channel, DMA_CH_RDLR_HI,
          upper_32_bits (Private->desc_rx));
  XGMAC_DMA_IOWRITE32 (channel, DMA_CH_RDLR_LO,
          lower_32_bits (Private->desc_rx));

  // Update the Rx Descriptor Tail Pointer
  XGMAC_DMA_IOWRITE32 (channel, DMA_CH_RDTR_LO,
          lower_32_bits (&Private->desc_rx[RX_DESC_CNT - 1]));
}

VOID
STATIC
enable_dma_interrupts (
  IN  xgmac_prv_data *pdata
  )
{
  xgmac_channel *channel;
  UINT32 dma_ch_isr;
  UINT32 dma_ch_ier;

  channel = &pdata->channel;
  // Clear all the interrupts which are set
  dma_ch_isr = XGMAC_DMA_IOREAD32 (channel, DMA_CH_SR);
  XGMAC_DMA_IOWRITE32 (channel, DMA_CH_SR, dma_ch_isr);

  // Clear all interrupt enable bits
  dma_ch_ier = 0;

  // Enable following interrupts
  //   NIE  - Normal Interrupt Summary Enable
  //   AIE  - Abnormal Interrupt Summary Enable
  //   FBEE - Fatal Bus Error Enable
  //
  XGMAC_SET_BITS (dma_ch_ier, DMA_CH_IER, NIE, 1);
  XGMAC_SET_BITS (dma_ch_ier, DMA_CH_IER, AIE, 1);
  XGMAC_SET_BITS (dma_ch_ier, DMA_CH_IER, FBEE, 1);

  // Enable the following Tx interrupts
  //   TBUE - Transmit Buffer Unavailable Enable
  //   TXSE - Transmit Stopped Enable
  //   TIE  - Transmit Interrupt Enable (unless polling)
  //
  //XGMAC_SET_BITS (dma_ch_ier, DMA_CH_IER, TBUE, 1);
  //XGMAC_SET_BITS (dma_ch_ier, DMA_CH_IER, TXSE, 1);
  XGMAC_SET_BITS (dma_ch_ier, DMA_CH_IER, TIE, 1);

  // Enable following Rx interrupts
  //   RSE  - Receive Stoppped Enable
  //   RBUE - Receive Buffer Unavailable Enable
  //   RIE  - Receive Interrupt Enable
  //
  //XGMAC_SET_BITS (dma_ch_ier, DMA_CH_IER, RSE, 1);
  XGMAC_SET_BITS (dma_ch_ier, DMA_CH_IER, RBUE, 1);
  XGMAC_SET_BITS (dma_ch_ier, DMA_CH_IER, RIE, 1);

  XGMAC_DMA_IOWRITE32 (channel, DMA_CH_IER, dma_ch_ier);
}

VOID
STATIC
config_mtl_mode (
  IN  xgmac_prv_data *pdata
  )
{
  UINT32 i;

  // Set Tx to weighted round robin scheduling algorithm
  XGMAC_IOWRITE32_BITS (pdata, MTL_OMR, ETSALG, XGMAC_MTL_ETSALG_WRR);

  // Set Tx traffic classes to strict priority algorithm
  for (i = 0; i < XGBE_TC_CNT; i++) {
    XGMAC_MTL_IOWRITE32_BITS (pdata, i, MTL_TC_ETSCR, TSA, XGMAC_MTL_TSA_SP);
  }

  // Set Rx to strict priority algorithm
  XGMAC_IOWRITE32_BITS (pdata, MTL_OMR, RAA, XGMAC_MTL_RAA_SP);
}

VOID
STATIC
config_rx_queue_mapping (
  IN  xgmac_prv_data *pdata
  )
{
  UINT32 i;
  UINT32 reg;
  UINT32 reg_val;
  UINT32 q_count;

  q_count = pdata->hw_feat.rx_q_cnt;
  // Select dynamic mapping of MTL Rx queue to DMA Rx channel
  reg = MTL_RQDCM0R;
  reg_val = 0;
  for (i = 0; i < q_count;) {
    reg_val |= (0x80 << ((i++ % MTL_RQDCM_Q_PER_REG) << 3));

    if ((i % MTL_RQDCM_Q_PER_REG) && (i != q_count)) {
      continue;
    }

    XGMAC_IOWRITE32 (pdata, reg, reg_val);

    reg += MTL_RQDCM_INC;
    reg_val = 0;
  }

}

INT32
STATIC
config_tsf_mode (
  IN       xgmac_prv_data *pdata,
  IN       UINT32 val
  )
{
  UINT32 i;

  for (i = 0; i < pdata->hw_feat.tx_q_cnt; i++) {
    XGMAC_MTL_IOWRITE32_BITS (pdata, i, MTL_Q_TQOMR, TSF, val);
  }

  return 0;
}

INT32
STATIC
config_rsf_mode (
  IN       xgmac_prv_data *pdata,
  IN       UINT32 val
  )
{
  UINT32 i;

  for (i = 0; i < pdata->hw_feat.rx_q_cnt; i++) {
    XGMAC_MTL_IOWRITE32_BITS (pdata, i, MTL_Q_RQOMR, RSF, val);
  }

  return 0;
}

INT32
STATIC
config_tx_threshold (
  IN       xgmac_prv_data *pdata,
  IN       UINT32 val
  )
{
  UINT32 i;

  for (i = 0; i < pdata->hw_feat.tx_q_cnt; i++) {
    XGMAC_MTL_IOWRITE32_BITS (pdata, i, MTL_Q_TQOMR, TTC, val);
  }

  return 0;
}

INT32
STATIC
config_rx_threshold (
  IN       xgmac_prv_data *pdata,
  IN       UINT32 val
  )
{
  UINT32 i;

  for (i = 0; i < pdata->hw_feat.rx_q_cnt; i++) {
    XGMAC_MTL_IOWRITE32_BITS (pdata, i, MTL_Q_RQOMR, RTC, val);
  }

  return 0;
}


VOID
STATIC
config_tx_fifo_size (
  IN       xgmac_prv_data *pdata
  )
{
  UINT32 fifo_size;
  UINT32 i;

  if (pdata->hw_feat.tx_q_cnt != 0) {
    fifo_size = pdata->hw_feat.tx_fifo_size / pdata->hw_feat.tx_q_cnt / 256;
  } else {
    fifo_size = 0;
  }
  if (fifo_size >= 1) {
    fifo_size -= 1;
  }

  for (i = 0; i < pdata->hw_feat.tx_q_cnt; i++) {
    XGMAC_MTL_IOWRITE32_BITS (pdata, i, MTL_Q_TQOMR, TQS, fifo_size);
  }

  DEBUG ((EFI_D_ERROR, "%d Tx queues, %d byte fifo per queue\n",
          pdata->hw_feat.tx_q_cnt, ((fifo_size + 1) * 256)));
}

VOID
STATIC
config_rx_fifo_size (
  IN       xgmac_prv_data *pdata
  )
{
  UINT32 fifo_size;
  UINT32 i;

  if (pdata->hw_feat.rx_q_cnt != 0) {
    fifo_size = pdata->hw_feat.rx_fifo_size / pdata->hw_feat.rx_q_cnt / 256;
  } else {
    fifo_size = 0;
  }
  if (fifo_size >= 1) {
    fifo_size -= 1;
  }

  for (i = 0; i < pdata->hw_feat.rx_q_cnt; i++) {
    XGMAC_MTL_IOWRITE32_BITS (pdata, i, MTL_Q_RQOMR, RQS, fifo_size);
  }

  DEBUG ((EFI_D_ERROR, "%d Rx queues, %d byte fifo per queue\n",
          pdata->hw_feat.rx_q_cnt, ((fifo_size + 1) * 256)));
}

VOID
STATIC
config_flow_control_threshold (
  IN       xgmac_prv_data *pdata
  )
{
  UINT32 i;

  for (i = 0; i < pdata->hw_feat.rx_q_cnt; i++) {
    // Activate flow control when less than 4k left in fifo
    XGMAC_MTL_IOWRITE32_BITS (pdata, i, MTL_Q_RQOMR, RFA, 2);

    // De-activate flow control when more than 6k left in fifo
    XGMAC_MTL_IOWRITE32_BITS (pdata, i, MTL_Q_RQOMR, RFD, 4);
  }
}

VOID
STATIC
enable_mtl_interrupts (
  IN       xgmac_prv_data *pdata
  )
{
  UINT32 mtl_q_isr;
  UINT32 q_count;
  UINT32 i;

  q_count = MAX (pdata->hw_feat.tx_q_cnt, pdata->hw_feat.rx_q_cnt);
  for (i = 0; i < q_count; i++) {
    // Clear all the interrupts which are set
    mtl_q_isr = XGMAC_MTL_IOREAD32 (pdata, i, MTL_Q_ISR);
    XGMAC_MTL_IOWRITE32 (pdata, i, MTL_Q_ISR, mtl_q_isr);

    // No MTL interrupts to be enabled
    XGMAC_MTL_IOWRITE32 (pdata, i, MTL_Q_ISR, 0);
  }
}

VOID
STATIC
config_mac_address (
  IN       ENET_DXE_PRIVATE_DATA *Private
  )
{
  UINT32 mac_hi;
  UINT32 mac_lo;
  xgmac_prv_data *pdata;

  pdata = &Private->xgmac_pdata;
  mac_hi = mac_lo = 0;
  mac_hi |= (Private->DevicePath.EthDevicePath.MacAddress.Addr[5] << 8);
  mac_hi |= (Private->DevicePath.EthDevicePath.MacAddress.Addr[4] << 0);
  mac_lo |= (Private->DevicePath.EthDevicePath.MacAddress.Addr[3] << 24);
  mac_lo |= (Private->DevicePath.EthDevicePath.MacAddress.Addr[2] << 16);
  mac_lo |= (Private->DevicePath.EthDevicePath.MacAddress.Addr[1] << 8);
  mac_lo |= (Private->DevicePath.EthDevicePath.MacAddress.Addr[0] << 0);

  XGMAC_IOWRITE32 (pdata, MAC_MACA0HR, mac_hi);
  XGMAC_IOWRITE32 (pdata, MAC_MACA0LR, mac_lo);
}

VOID
STATIC
config_jumbo_enable (
  IN       xgmac_prv_data *pdata
  )
{
  UINT32 val;

  //val = (pdata->netdev->mtu > XGMAC_STD_PACKET_MTU) ? 1 : 0;
  val = 0;

  XGMAC_IOWRITE32_BITS (pdata, MAC_RCR, JE, val);
}

INT32
STATIC
disable_tx_flow_ctrl (
  IN       xgmac_prv_data *pdata
  )
{
  UINT32 max_q_count;
  UINT32 q_count;
  UINT32 reg;
  UINT32 reg_val;
  UINT32 i;
//  UINT32 z;

  // Clear MTL flow control
  for (i = 0; i < pdata->hw_feat.rx_q_cnt; i++) {
    XGMAC_MTL_IOWRITE32_BITS (pdata, i, MTL_Q_RQOMR, EFHC, 0);
  }

  // Clear MAC flow control
  max_q_count = XGMAC_MAX_FLOW_CONTROL_QUEUES;
  q_count = min_t (pdata->hw_feat.rx_q_cnt, max_q_count);
  reg = MAC_Q0TFCR;
  for (i = 0; i < q_count; i++) {
    reg_val = XGMAC_IOREAD32 (pdata, reg);
    XGMAC_SET_BITS (reg_val, MAC_Q0TFCR, TFE, 0);
    XGMAC_IOWRITE32 (pdata, reg, reg_val);

    reg += MAC_QTFCR_INC;
  }

  return 0;
}

INT32
STATIC
enable_tx_flow_ctrl (
  IN       xgmac_prv_data *pdata
  )
{
  UINT32 max_q_count;
  UINT32 q_count;
  UINT32 reg;
  UINT32 reg_val;
  UINT32 i;

  // Set MTL flow control
  for (i = 0; i < pdata->hw_feat.rx_q_cnt; i++) {
    XGMAC_MTL_IOWRITE32_BITS (pdata, i, MTL_Q_RQOMR, EFHC, 1);
  }

  // Set MAC flow control
  max_q_count = XGMAC_MAX_FLOW_CONTROL_QUEUES;
  q_count = min_t (pdata->hw_feat.rx_q_cnt, max_q_count);
  reg = MAC_Q0TFCR;
  for (i = 0; i < q_count; i++) {
    reg_val = XGMAC_IOREAD32 (pdata, reg);

    // Enable transmit flow control
    XGMAC_SET_BITS (reg_val, MAC_Q0TFCR, TFE, 1);
    // Set pause time
    XGMAC_SET_BITS (reg_val, MAC_Q0TFCR, PT, 0xffff);

    XGMAC_IOWRITE32 (pdata, reg, reg_val);

    reg += MAC_QTFCR_INC;
  }

  return 0;
}

INT32
STATIC
disable_rx_flow_ctrl (
  IN       xgmac_prv_data *pdata
  )
{
  XGMAC_IOWRITE32_BITS (pdata, MAC_RFCR, RFE, 0);

  return 0;
}

INT32
STATIC
enable_rx_flow_ctrl (
  IN       xgmac_prv_data *pdata
  )
{
  XGMAC_IOWRITE32_BITS (pdata, MAC_RFCR, RFE, 1);

  return 0;
}

VOID
STATIC
config_flow_control (
  IN       xgmac_prv_data *pdata
  )
{
  if (pdata->flow_ctrl & XGMAC_FLOW_CTRL_TX) {
    enable_tx_flow_ctrl (pdata);
  } else {
    disable_tx_flow_ctrl (pdata);
  }

  if (pdata->flow_ctrl & XGMAC_FLOW_CTRL_RX) {
    enable_rx_flow_ctrl (pdata);
  } else {
    disable_rx_flow_ctrl (pdata);
  }
}

INT32
STATIC
disable_rx_csum (
  IN       xgmac_prv_data *pdata
  )
{
  XGMAC_IOWRITE32_BITS (pdata, MAC_RCR, IPC, 0);

  return 0;
}

INT32
STATIC
enable_rx_csum (
  IN       xgmac_prv_data *pdata
  )
{
  XGMAC_IOWRITE32_BITS (pdata, MAC_RCR, IPC, 0x1);

  return 0;
}

VOID
STATIC
config_checksum_offload (
  IN       xgmac_prv_data *pdata
  )
{
  if (TRUE) {
    enable_rx_csum (pdata);
  } else {
    disable_rx_csum (pdata);
  }
}

VOID
STATIC
config_mmc (
  IN       xgmac_prv_data *pdata
  )
{
  // Set counters to reset on read
  XGMAC_IOWRITE32_BITS (pdata, MMC_CR, ROR, 1);

  // Reset the counters
  XGMAC_IOWRITE32_BITS (pdata, MMC_CR, CR, 1);
}

INT32
STATIC
xgbe_enable_rx_vlan_stripping (
  IN       xgmac_prv_data *pdata
  )
{
  // Put the VLAN tag in the Rx descriptor
  XGMAC_IOWRITE32_BITS (pdata, MAC_VLANTR, EVLRXS, 1);

  // Don't check the VLAN type
  XGMAC_IOWRITE32_BITS (pdata, MAC_VLANTR, DOVLTC, 1);

  // Check only C-TAG (0x8100) packets
  XGMAC_IOWRITE32_BITS (pdata, MAC_VLANTR, ERSVLM, 0);

  // Don't consider an S-TAG (0x88A8) packet as a VLAN packet
  XGMAC_IOWRITE32_BITS (pdata, MAC_VLANTR, ESVL, 0);

  // Enable VLAN tag stripping
  XGMAC_IOWRITE32_BITS (pdata, MAC_VLANTR, EVLS, 0x3);

  return 0;
}

INT32
STATIC
xgbe_disable_rx_vlan_stripping (
  IN       xgmac_prv_data *pdata
  )
{
  XGMAC_IOWRITE32_BITS (pdata, MAC_VLANTR, EVLS, 0);

  return 0;
}

VOID
STATIC
config_vlan_support (
  IN       xgmac_prv_data *pdata
  )
{
  if (FALSE) {
    xgbe_enable_rx_vlan_stripping (pdata);
  } else {
    xgbe_disable_rx_vlan_stripping (pdata);
  }
}

VOID
STATIC
enable_mac_interrupts (
  IN       xgmac_prv_data *pdata
  )
{
  // No MAC interrupts to be enabled
  XGMAC_IOWRITE32 (pdata, MAC_IER, 0);

  // Enable all counter interrupts
  XGMAC_IOWRITE32_BITS (pdata, MMC_RIER, ALL_INTERRUPTS, 0xff);
  XGMAC_IOWRITE32_BITS (pdata, MMC_TIER, ALL_INTERRUPTS, 0xff);
}

VOID
STATIC
enable_tx (
  IN       xgmac_prv_data *pdata
  )
{
  xgmac_channel *channel;
  UINT32 i;

  // Enable each Tx DMA channel
  channel = &pdata->channel;
  XGMAC_DMA_IOWRITE32_BITS (channel, DMA_CH_TCR, ST, 1);

  // Enable each Tx queue
  for (i = 0; i < pdata->hw_feat.tx_q_cnt; i++) {
    XGMAC_MTL_IOWRITE32_BITS (pdata, i, MTL_Q_TQOMR, TXQEN,
           MTL_Q_ENABLED);
  }

  // Enable MAC Tx
  XGMAC_IOWRITE32_BITS (pdata, MAC_TCR, TE, 1);
}

VOID
STATIC
disable_tx (
  IN       xgmac_prv_data *pdata
  )
{
  xgmac_channel *channel;
  UINT32 i;

  // Disable MAC Tx
  XGMAC_IOWRITE32_BITS (pdata, MAC_TCR, TE, 0);

  // Disable each Tx queue
  for (i = 0; i < pdata->hw_feat.tx_q_cnt; i++) {
    XGMAC_MTL_IOWRITE32_BITS (pdata, i, MTL_Q_TQOMR, TXQEN, 0);
  }

  // Disable each Tx DMA channel
  channel = &pdata->channel;
  XGMAC_DMA_IOWRITE32_BITS (channel, DMA_CH_TCR, ST, 0);

}

VOID
STATIC
enable_rx (
  IN       xgmac_prv_data *pdata
  )
{
  xgmac_channel *channel;
  UINT32 reg_val;
  UINT32 i;

  // Enable each Rx DMA channel
  channel = &pdata->channel;
  XGMAC_DMA_IOWRITE32_BITS (channel, DMA_CH_RCR, SR, 1);

  // Enable each Rx queue
  reg_val = 0;
  for (i = 0; i < pdata->hw_feat.rx_q_cnt; i++) {
    reg_val |= (0x02 << (i << 1));
  }
  XGMAC_IOWRITE32 (pdata, MAC_RQC0R, reg_val);

  // Enable MAC Rx
  XGMAC_IOWRITE32_BITS (pdata, MAC_RCR, DCRCC, 0x1);
  XGMAC_IOWRITE32_BITS (pdata, MAC_RCR, CST, 0x1);
  XGMAC_IOWRITE32_BITS (pdata, MAC_RCR, ACS, 0x1);
  XGMAC_IOWRITE32_BITS (pdata, MAC_RCR, RE, 0x1);
}

VOID
STATIC
disable_rx (
  IN       xgmac_prv_data *pdata
  )
{
  xgmac_channel *channel;

  // Disable MAC Rx
  XGMAC_IOWRITE32_BITS (pdata, MAC_RCR, DCRCC, 0);
  XGMAC_IOWRITE32_BITS (pdata, MAC_RCR, CST, 0);
  XGMAC_IOWRITE32_BITS (pdata, MAC_RCR, ACS, 0);
  XGMAC_IOWRITE32_BITS (pdata, MAC_RCR, RE, 0);

  // Disable each Rx queue
  XGMAC_IOWRITE32 (pdata, MAC_RQC0R, 0);

  // Disable each Rx DMA channel
  channel = &pdata->channel;
  XGMAC_DMA_IOWRITE32_BITS (channel, DMA_CH_RCR, SR, 0);

  // Poll to be sure the channels have stopped?
  //while (count--) {
  //  dma_sr0 = XGMAC_IOREAD32_BITS(pdata, DMA_DSR0, RPS);
  //  if (dma_sr0 == 3 || dma_sr0 == 4)
  //    break;
  //  mdelay(1);
  //}
}

INT32
set_gmii_speed (
  IN       xgmac_prv_data *pdata
  )
{
  UINT32 reg;
  UINT32 XgmacBase;
  XgmacBase = pdata->xgmac_regs;

  XGMAC_IOWRITE32_BITS (pdata, MAC_TCR, SS, 0x3);
  reg = XGMAC_IOREAD32 (pdata, MAC_TCR);
  DEBUG ((EFI_D_ERROR, "gmii_speed set to %x\n", reg));
  return 0;
}

INT32
STATIC
set_gmii_2500_speed (
  IN       xgmac_prv_data *pdata
  )
{
  XGMAC_IOWRITE32_BITS (pdata, MAC_TCR, SS, 0x2);

  return 0;
}

INT32
STATIC
set_xgmii_speed (
  IN       xgmac_prv_data *pdata
  )
{
  XGMAC_IOWRITE32_BITS (pdata, MAC_TCR, SS, 0);
  return 0;
}

VOID
STATIC
rx_desc_reset (
     OUT   ENET_DXE_PRIVATE_DATA *Private,
  IN       UINT32 CurrIndex
  )
{
  // Reset the Rx descriptor
  //   Set buffer 1 (lo) address to dma address (lo)
  //   Set buffer 1 (hi) address to dma address (hi)
  //   Set buffer 2 (lo) address to zero
  //   Set buffer 2 (hi) address to zero and set control bits
  //     OWN and INTE
  //
  //EnetDmaFreeBuffer (&Private->pkt_rx_dma[CurrIndex]);
  //EFI_STATUS Status = EnetDmaAllocBuffer (ENET_MAX_PACKET_SIZE, &Private->pkt_rx_dma[CurrIndex]);
  //ASSERT_EFI_ERROR (Status);
  Private->desc_rx[CurrIndex].RDES0 = lower_32_bits (Private->pkt_rx_dma[CurrIndex].DeviceAddress);
  Private->desc_rx[CurrIndex].RDES1 = upper_32_bits (Private->pkt_rx_dma[CurrIndex].DeviceAddress);
  Private->desc_rx[CurrIndex].RDES2 = 0;

  Private->desc_rx[CurrIndex].RDES3 = 0;
  if (Private->desc_rx_interrupt[CurrIndex] == TRUE) {
    XGMAC_SET_BITS (Private->desc_rx[CurrIndex].RDES3, RX_NORMAL_DESC3, INTE, 1);
  }

  // Since the Rx DMA engine is likely running, make sure everything
  // is written to the descriptor(s) before setting the OWN bit
  // for the descriptor
  //

  XGMAC_SET_BITS (Private->desc_rx[CurrIndex].RDES3, RX_NORMAL_DESC3, OWN, 1);

}

EFI_STATUS
xgmac_dev_read (
  IN       ENET_DXE_PRIVATE_DATA *Private,
  IN       VOID            *Buffer,
  IN       UINTN           *BufferSize
  )
{
  EFI_STATUS Status = EFI_NOT_READY;
  UINTN   BuffSize;
//  UINTN   BuSize;
  xgmac_channel *channel;
  UINT32  CurrIndex;
  UINT32  own;
  UINT32  err_summary;
//   UINT32 XgmacBase;
  gBS->Stall (10);
  BuffSize = *BufferSize;
  channel = &Private->xgmac_pdata.channel;
  CurrIndex = GET_CURR_RX_DESC_INDEX (&Private->desc_rx_index);

  // Check for data availability
  own = XGMAC_GET_BITS (Private->desc_rx[CurrIndex].RDES3, RX_NORMAL_DESC3, OWN);
  if (own == 0) {
    DEBUG ((EFI_D_ERROR, "own = %x \n", own));
    // Check whether it is good packet or bad packet
    err_summary = XGMAC_GET_BITS (Private->desc_rx[CurrIndex].RDES3, RX_NORMAL_DESC3, ES);
    if (err_summary == 0) {
      // Get the packet length
      *BufferSize = XGMAC_GET_BITS (Private->desc_rx[CurrIndex].RDES3, RX_NORMAL_DESC3, PL);
      if ((*BufferSize != 0) && (*BufferSize <= BuffSize)) {
        CopyMem (Buffer, (VOID *) (UINTN) Private->pkt_rx_dma[CurrIndex].DeviceAddress, *BufferSize);
        Status = EFI_SUCCESS;
      } else if (*BufferSize > BuffSize) {
      	DEBUG ((EFI_D_ERROR, "EFI_BUFFER_TOO_SMALL Error\n"));
        return EFI_BUFFER_TOO_SMALL;
      } else {
        DEBUG ((EFI_D_ERROR, "EFI_NOT_READY Error 1n"));
        Status = EFI_NOT_READY;
      }
    } else {
      //
      //UINT32 err_type;
      //err_type = XGMAC_GET_BITS(Private->desc_rx[CurrIndex].RDES3, RX_NORMAL_DESC3, ETLT);
      //DEBUG ((
      //  EFI_D_ERROR, "\nBad packet, error type is 0x%X, size is 0x%X\n",
      //  err_type,
      //  XGMAC_GET_BITS(Private->desc_rx[CurrIndex].RDES3, RX_NORMAL_DESC3, PL)
      //  ));
      //
      Status = EFI_NOT_READY;
	  DEBUG ((EFI_D_ERROR, "EFI_NOT_READY Error 2\n"));
    }
    gBS->Stall (100);
    rx_desc_reset (Private, CurrIndex);
    // Update the Rx Tail Pointer Register with address of
    // descriptors from which data is read
    XGMAC_DMA_IOWRITE32 (channel, DMA_CH_RDTR_LO,
      lower_32_bits (&Private->desc_rx[CurrIndex]));
    Private->desc_rx_index++;
  }

  return Status;
}

VOID
STATIC
tx_desc_reset (
     OUT   ENET_DXE_PRIVATE_DATA *Private,
  IN       UINT32 CurrIndex
  )
{
  // Reset the Tx descriptor
  //   Set buffer 1 (lo) address to zero
  //   Set buffer 1 (hi) address to zero
  //   Reset all other control bits (IC, TTSE, B2L & B1L)
  //   Reset all other control bits (OWN, CTXT, FD, LD, CPC, CIC, etc)
  //
  Private->desc_tx[CurrIndex].TDES0 = 0;
  Private->desc_tx[CurrIndex].TDES1 = 0;
  Private->desc_tx[CurrIndex].TDES2 = 0;
  Private->desc_tx[CurrIndex].TDES3 = 0;
}

EFI_STATUS
xgmac_pre_xmit (
  IN       ENET_DXE_PRIVATE_DATA *Private,
  IN       VOID       *Buffer,
  IN       UINTN      BufferSize
  )
{
  xgmac_channel *channel;
  UINT32 csum;
  UINT32 CurrIndex;
  UINT32 StartIndex;
  UINT32 DmaOwnBit;
  UINTN count;
  EFI_STATUS Status = EFI_SUCCESS;

  channel = &Private->xgmac_pdata.channel;
  csum = 1;
  CurrIndex = GET_CURR_TX_DESC_INDEX (&Private->desc_tx_index);
  StartIndex = CurrIndex;
  DmaOwnBit = 1;

  // Update buffer address (for TSO this is the header)
  CopyMem ((VOID *) (UINTN) Private->pkt_tx_dma[CurrIndex].DeviceAddress, Buffer, BufferSize);
  Private->desc_tx[CurrIndex].TDES0 =
    lower_32_bits (Private->pkt_tx_dma[CurrIndex].DeviceAddress);
  Private->desc_tx[CurrIndex].TDES1 =
    upper_32_bits (Private->pkt_tx_dma[CurrIndex].DeviceAddress);

  // Update the buffer length
  XGMAC_SET_BITS (Private->desc_tx[CurrIndex].TDES2, TX_NORMAL_DESC2, HL_B1L,
           BufferSize);

  // Mark it as First Descriptor
  XGMAC_SET_BITS (Private->desc_tx[CurrIndex].TDES3, TX_NORMAL_DESC3, FD, 1);

  // Mark it as a NORMAL descriptor
  XGMAC_SET_BITS (Private->desc_tx[CurrIndex].TDES3, TX_NORMAL_DESC3, CTXT, 0);

  // Set OWN bit if not the first descriptor
  if (GET_CURR_TX_DESC_INDEX (&Private->desc_tx_index) != StartIndex) {
    XGMAC_SET_BITS (Private->desc_tx[CurrIndex].TDES3, TX_NORMAL_DESC3, OWN, 0x1);
  }

  // Enable CRC and Pad Insertion
  XGMAC_SET_BITS (Private->desc_tx[CurrIndex].TDES3, TX_NORMAL_DESC3, CPC, 0);

  // Enable HW CSUM
  if (csum) {
    XGMAC_SET_BITS (Private->desc_tx[CurrIndex].TDES3, TX_NORMAL_DESC3, CIC, 0x3);
  }

  // Set the total length to be transmitted
  XGMAC_SET_BITS (Private->desc_tx[CurrIndex].TDES3, TX_NORMAL_DESC3, FL,
                 BufferSize);

  // Set LAST bit for the last descriptor
  XGMAC_SET_BITS (Private->desc_tx[CurrIndex].TDES3, TX_NORMAL_DESC3, LD, 0x1);

  // Set Interrupt on Completion bit for the last descriptor
  XGMAC_SET_BITS (Private->desc_tx[CurrIndex].TDES3, TX_NORMAL_DESC2, IC, 0x1);

  // In case the Tx DMA engine is running, make sure everything
  // is written to the descriptor(s) before setting the OWN bit
  // for the first descriptor
  //

  // Set OWN bit for the first descriptor
  XGMAC_SET_BITS (Private->desc_tx[CurrIndex].TDES3, TX_NORMAL_DESC3, OWN, 0x1);


  // Issue a poll command to Tx DMA by writing address
  // of next immediate free descriptor
  Private->desc_tx_index++;
  CurrIndex = GET_CURR_TX_DESC_INDEX (&Private->desc_tx_index);
  XGMAC_DMA_IOWRITE32 (channel, DMA_CH_TDTR_LO,
          lower_32_bits (&Private->desc_tx[CurrIndex]));

  // make sure it had been sent, wait maximum 5mS
  for (count = 0; count < XGMAC_TX_DMA_MAX_WAIT_MCS / 2; count++) {
    DmaOwnBit = SNP_GET_BIT_FIELD (Private->desc_tx[StartIndex].TDES3, TX_NORMAL_DESC3, OWN);
    if (DmaOwnBit == 0) {
      break;
    }
    gBS->Stall (2);
  }

  if (DmaOwnBit == 1) {
    Status = EFI_DEVICE_ERROR;
	DEBUG ((EFI_D_ERROR, "xgmac_pre_xmit EFI_DEVICE_ERROR\n"));
  }

  tx_desc_reset (Private, StartIndex);
  return Status;
}

VOID
XgmacInit (
  IN OUT   ENET_DXE_PRIVATE_DATA *Private,
  IN       UINTN XgmacBase
  )
{
  UINT32 CheckValue;
  // S/W Reset
  XgbeHwinitDelay();
  MmioWrite32 (XgmacBase + 0x00003000, 0x00000001);
  while (1) {
  // wait for done
    CheckValue = getBitfieldReg32 ((UINT32) XgmacBase + 0x00003000, 0, 1);
    if (CheckValue == 0x0) {
      break;
    }
    gBS->Stall (1000);
  }

  // Flush Tx queues
  if (flush_tx_queues (&Private->xgmac_pdata)) {
    DEBUG ((EFI_D_ERROR, "Exiting out of flush_tx_queues\n"));
    return;
  }

  //
  // Initialize DMA related features
  //
  DEBUG ((EFI_D_ERROR, "Initialize DMA related features\n"));
  config_dma_bus (&Private->xgmac_pdata); 
  config_dma_cache (&Private->xgmac_pdata);  
  config_osp_mode (&Private->xgmac_pdata);  
  config_pblx8 (&Private->xgmac_pdata);
  config_tx_pbl_val (&Private->xgmac_pdata);
  config_rx_pbl_val (&Private->xgmac_pdata);  
  config_rx_coalesce (&Private->xgmac_pdata);
  config_rx_buffer_size (&Private->xgmac_pdata);
  config_tso_mode (&Private->xgmac_pdata);  
  tx_desc_init (Private);
  rx_desc_init (Private);
  enable_dma_interrupts (&Private->xgmac_pdata);

  //
  // Initialize MTL related features
  //
  config_mtl_mode (&Private->xgmac_pdata);
  config_rx_queue_mapping (&Private->xgmac_pdata);
  //  Program the priorities mapped to the Selected Traffic Classes
  //  in MTL_TC_Prty_Map0-3 registers
  //  Program the Transmit Selection Algorithm (TSA) in MTL_TC[n]_ETS_Control
  //  register for all the Selected Traffic Classes (n=0, 1, , Max selected
  //  number of TCs - 1)
  config_tsf_mode (&Private->xgmac_pdata, Private->xgmac_pdata.tx_sf_mode);
  config_rsf_mode (&Private->xgmac_pdata, Private->xgmac_pdata.rx_sf_mode);
  config_tx_threshold (&Private->xgmac_pdata, Private->xgmac_pdata.tx_threshold);
  config_rx_threshold (&Private->xgmac_pdata, Private->xgmac_pdata.rx_threshold);
  config_tx_fifo_size (&Private->xgmac_pdata);
  config_rx_fifo_size (&Private->xgmac_pdata);
  config_flow_control_threshold (&Private->xgmac_pdata);
  //  Queue to Traffic Class Mapping (Q2TCMAP)
  //  Error Packet and undersized good Packet forwarding enable (FEP and FUP)
  enable_mtl_interrupts (&Private->xgmac_pdata);

  // Transmit Class Weight
  XGMAC_IOWRITE32_BITS (&Private->xgmac_pdata, MTL_Q_TCQWR, QW, 0x10);

  //
  // Initialize MAC related features
  //
  xgmac_set_rx_mode (Private);
  config_mac_address (Private);
  config_jumbo_enable (&Private->xgmac_pdata);
  config_flow_control (&Private->xgmac_pdata);
  config_checksum_offload (&Private->xgmac_pdata);
  config_vlan_support (&Private->xgmac_pdata);
  config_mmc (&Private->xgmac_pdata);
  enable_mac_interrupts (&Private->xgmac_pdata);

  // Enable Tx/Rx
  enable_tx (&Private->xgmac_pdata);
  enable_rx (&Private->xgmac_pdata);
  gBS->Stall (50000);
}


VOID
UpdateLinkStatus (
  IN       ENET_DXE_PRIVATE_DATA *Private
  )
{
  XGBE_PHY_DATA *phy_data = Private->phy_data;
  UINTN Reg32;

  Reg32 = XMDIO_READ (Private->xpcs_regs, MDIO_MMD_PCS, MDIO_PCS_STS1);
  // Read again as bits in register can be latched
  Reg32 = XMDIO_READ (Private->xpcs_regs, MDIO_MMD_PCS, MDIO_PCS_STS1);

  Private->Mode.MediaPresent = ((Reg32 & PCS_STS1_RLU) == PCS_STS1_RLU)?TRUE:FALSE;
  if ( Private->Mode.MediaPresent == FALSE ) {
    DEBUG ((EFI_D_ERROR, "MediaPresent FAIL   \n"));
    // No link, attempt a receiver reset cycle
    if (phy_data->rrc_count++) {
      phy_data->rrc_count = 0;
      xgbe_phy_rrc (Private);
    }
  }
}


VOID
STATIC
xgbe_an73_disable_kr_training (
  UINTN XpcsBase
  )
{
  UINTN reg;
  DEBUG ((EFI_D_ERROR, "xgbe_an73_disable_kr_training\n"));
  reg = XMDIO_READ (XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_PMD_CTRL);

  reg &= ~XGBE_KR_TRAINING_ENABLE;
  XMDIO_WRITE (XpcsBase, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_PMD_CTRL, reg);
}

VOID
xgbe_an73_restart (
  UINT32 XpcsBase
  )
{
  DEBUG ((EFI_D_ERROR, "xgbe_an73_restart\n"));
  xgbe_an73_enable_interrupts (XpcsBase);
  xgbe_an73_set (XpcsBase, TRUE, TRUE);
  DEBUG ((EFI_D_ERROR, "CL73 AN enabled / restarted\n"));
}

  
VOID
xgbe_an37_restart (
  UINT32 XpcsBase
  )
{
  xgbe_an37_enable_interrupts (XpcsBase);
  xgbe_an37_set (XpcsBase, TRUE, TRUE);
  DEBUG ((EFI_D_ERROR, "CL37 AN enabled / restarted\n"));
}

VOID
xgbe_an_restart (
  ENET_DXE_PRIVATE_DATA *pdata
  )
{
  UINT32 XpcsBase = pdata->xpcs_regs;

  xgbe_phy_an_pre(pdata);

  switch (pdata->an_mode) {
  case XGBE_AN_MODE_CL73:
  case XGBE_AN_MODE_CL73_REDRV:
	    xgbe_an73_restart (XpcsBase);
	  break;
  case XGBE_AN_MODE_CL37:
  case XGBE_AN_MODE_CL37_SGMII:
	    xgbe_an37_restart (XpcsBase);
	  break;
  default:
	  break;
  }
}

