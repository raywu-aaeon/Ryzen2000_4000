/* $NoKeywords:$ */
/**
 * @file
 *
 * mdio.c
 *
 * Contains Ethernet Driver for the DXE phase.
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
#include <Protocol/xGbEI2cMaster.h>

#define SWAPENDIAN_16(x)            (UINT16)((((x) & 0xFF00) >> 8) | (((x) & 0x00FF) << 8))

EFI_STATUS xgbe_phy_i2c_mii_write(ENET_DXE_PRIVATE_DATA *Private, UINT32 reg, UINT32 val);
INT32 xgbe_phy_i2c_mii_read(ENET_DXE_PRIVATE_DATA *Private, UINT32 reg);
INT32 xgbe_read_ext_mii_regs(ENET_DXE_PRIVATE_DATA *pdata, UINT32 addr,	UINT32 reg);

EFI_STATUS xgbe_write_ext_mii_regs(ENET_DXE_PRIVATE_DATA *pdata, UINT32 addr,
        UINT32 reg, UINT32 val) {

    UINT32 XgmacBase;
    UINT32 mdio_sca, mdio_sccd;
    UINT32 Mdioreg = 0;
    UINT32 Count = CMD_TIMEOUT;

    XgmacBase = pdata->xgmac_pdata.xgmac_regs;

    mdio_sca = 0;
    SET_BITS(mdio_sca, 0, 21, reg);
    SET_BITS(mdio_sca, 21, 5, addr);
    MmioWrite32(XgmacBase + MAC_MDIOSCAR, mdio_sca);

    mdio_sccd = 0;
    SET_BITS(mdio_sccd, 0, 16, val);
    SET_BITS(mdio_sccd, 16, 2, 1);
    SET_BITS(mdio_sccd, 22, 1, 1);
    MmioWrite32(XgmacBase + MAC_MDIOSCCDR, mdio_sccd);

    while (Count--) {
        Mdioreg = MmioRead32(XgmacBase + MAC_MDIOISR);
        if (Mdioreg & BIT12) {
            //Adapter->mdio_complete = FALSE;
            break;
        }
        gBS->Stall(1000); //1 milli seconds
        }

    if (!Count) {
        return EFI_NOT_FOUND;
    }
    return EFI_SUCCESS;
}

EFI_STATUS phy_write_mmd(ENET_DXE_PRIVATE_DATA *pdata, UINT32 addr, UINT32 reg, UINT32 val) {
    UINT32 ret;
    EFI_STATUS   Status = EFI_SUCCESS;

    ret = (UINT32) xgbe_phy_get_comm_ownership(pdata);
    if (ret) {
        DEBUG((EFI_D_ERROR, "phy_write xgbe_phy_get_comm_ownership failed\n"));
        return EFI_NOT_FOUND;
    }

    Status = xgbe_write_ext_mii_regs(pdata, addr, reg, val);

    if (EFI_ERROR (Status)) {
        DEBUG((EFI_D_ERROR, "phy_write xgbe_write_ext_mii_regs failed\n"));
        return EFI_NOT_FOUND;
    }

    xgbe_phy_put_comm_ownership(pdata);

    return Status;
}

EFI_STATUS xgbe_phy_i2c_mii_write(ENET_DXE_PRIVATE_DATA *Private, UINT32 reg, UINT32 val)
{
    XGBE_I2C_MASTER_PROTOCOL  *XgbEI2cMaster;
    UINT8                     PacketBuffer[sizeof (EFI_I2C_REQUEST_PACKET) + sizeof (EFI_I2C_OPERATION)];
    EFI_I2C_REQUEST_PACKET    *RequestPacket;
    EFI_I2C_OPERATION         *Operation;
    EFI_STATUS                Status = EFI_SUCCESS;
    UINT8                     Data[3];
    UINT32                    XgmacBaseI2c;
    UINTN                     SlaveAdd =  XGBE_SFP_PHY_ADDRESS;

    Status = XgbeSfpGetMux (Private);
    ASSERT (Status == EFI_SUCCESS);
    if (EFI_ERROR (Status)) {
        return EFI_NOT_FOUND;
    }

    DEBUG ((EFI_D_ERROR, "Prepare to Start xgbe_phy_i2c_mii_write \n"));
    XgmacBaseI2c = Private->xgmac_pdata.xgmac_regs + 0x1E000;

    Status = gBS->LocateProtocol (&gxGbEI2cMasterProtocolGuid, NULL, &XgbEI2cMaster);
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "\nXGMAC Workaround: Could not Locate gxGbEI2cMasterProtocolGuid.\n"));
        gBS->Stall (100);
    }

    Data[0] = (UINT8)(reg & 0xff);
    Data[1] = (UINT8)(val >> 8 ) & 0xff; //higher byte
    Data[2] = (UINT8)val & 0xff ;        // lower byte

    DEBUG ((EFI_D_ERROR, "xgbe_phy_i2c_mii_write Data[1] = %x  Data[2] = %x \n" , Data[1] , Data[2] ));

    XgbEI2cMaster->BaseAddress = XgmacBaseI2c;
    XgbEI2cMaster->I2cInit (XgbEI2cMaster);
    RequestPacket = (EFI_I2C_REQUEST_PACKET*)PacketBuffer;
    Operation   = RequestPacket->Operation;
    RequestPacket->OperationCount = 1;
    Operation[0].Flags            =  0 ; //I2C_FLAG_WRITE;
    Operation[0].LengthInBytes    = sizeof (Data);
    Operation[0].Buffer           = Data;

    Status = XgbEI2cMaster->StartRequest (XgbEI2cMaster, SlaveAdd, RequestPacket, NULL, NULL);
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "\nXGMAC: Failed to StartRequest.\n"));
        gBS->Stall (100);
        return EFI_NOT_FOUND;
    }

    XgbeSfpPutMux (Private);  

    return EFI_SUCCESS;
}


INT32 xgbe_phy_i2c_mii_read(ENET_DXE_PRIVATE_DATA *Private, UINT32 reg)
{
    XGBE_I2C_MASTER_PROTOCOL  *XgbEI2cMaster;
    UINT8                     PacketBuffer[sizeof (EFI_I2C_REQUEST_PACKET) + sizeof (EFI_I2C_OPERATION)];
    EFI_I2C_REQUEST_PACKET    *RequestPacket;
    EFI_I2C_OPERATION         *Operation;
    EFI_STATUS                Status = EFI_SUCCESS;
    UINT8                     Offset = (UINT8)reg;
    UINT8                     Data[2];
    UINT32                    XgmacBaseI2c;
    UINTN                     SlaveAdd =  XGBE_SFP_PHY_ADDRESS;
    INT32                    read_value = 0;

    Status = XgbeSfpGetMux (Private);
    ASSERT (Status == EFI_SUCCESS);
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "Prepare to Start xgbe_phy_i2c_mii_read fail \n"));
        return -1;
    }

    //DEBUG ((EFI_D_ERROR, "Prepare to Start xgbe_phy_i2c_mii_read \n"));
    XgmacBaseI2c = Private->xgmac_pdata.xgmac_regs + 0x1E000;

    Status = gBS->LocateProtocol (&gxGbEI2cMasterProtocolGuid, NULL, &XgbEI2cMaster);
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "\nXGMAC Workaround: Could not Locate gxGbEI2cMasterProtocolGuid.\n"));
        gBS->Stall (100);
        return -1;
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

    Status = XgbEI2cMaster->StartRequest (XgbEI2cMaster, SlaveAdd, RequestPacket, NULL, NULL);
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "\nXGMAC: Failed to StartRequest.\n"));
        gBS->Stall (100);
        return -1;
    }

  XgbeSfpPutMux (Private);

  read_value = (((UINT16)Data[0] ) << 8 ) & 0xFF00;
  read_value |= Data[1] & 0xFF ;  
  DEBUG ((EFI_D_ERROR, "End  xgbe_phy_i2c_mii_read  = %x \n" , read_value)); 

  return read_value;
}


EFI_STATUS xgbe_phy_mii_write(ENET_DXE_PRIVATE_DATA *pdata, UINT32 addr , UINT32 reg, UINT32 val)
{
    XGBE_PHY_DATA *phy_data = pdata->phy_data;
    EFI_STATUS    Status;

    if (phy_data->conn_type == XGBE_CONN_TYPE_SFP)
        Status = xgbe_phy_i2c_mii_write(pdata, reg, val);
    else 
        Status = xgbe_write_ext_mii_regs(pdata, addr, reg, val);

    return Status;
}

UINT32 xgbe_phy_mii_read(ENET_DXE_PRIVATE_DATA *pdata, UINT32 addr, UINT32 reg)
{
    XGBE_PHY_DATA *phy_data = pdata->phy_data;
    UINT32 reg_read_val;

    if (phy_data->conn_type == XGBE_CONN_TYPE_SFP)
        reg_read_val = xgbe_phy_i2c_mii_read(pdata, reg);
    else 
        reg_read_val = xgbe_read_ext_mii_regs(pdata, addr, reg);
    
    return reg_read_val;
}

EFI_STATUS phy_write(ENET_DXE_PRIVATE_DATA *pdata, UINT32 reg, UINT32 val) {
    UINT32 ret;
    UINT32 addr;
    EFI_STATUS    Status;
    XGBE_PHY_DATA *phy_data = pdata->phy_data;	
  
    addr = phy_data->port_id;

    DEBUG((EFI_D_ERROR, "phy_write entry reg= %x RegVal= %x\n", reg, val));

    ret = (UINT32) xgbe_phy_get_comm_ownership(pdata);
    if (ret) {
        DEBUG((EFI_D_ERROR, "phy_write xgbe_phy_get_comm_ownership failed\n"));
        return EFI_UNSUPPORTED;
    }

    Status = xgbe_phy_mii_write(pdata, addr, reg, val);

    if (EFI_ERROR (Status)) {
        DEBUG((EFI_D_ERROR, "phy_write xgbe_write_ext_mii_regs failed\n"));
        return EFI_UNSUPPORTED;
    }

    xgbe_phy_put_comm_ownership(pdata);

    return Status;
}

INT32 xgbe_read_ext_mii_regs(ENET_DXE_PRIVATE_DATA *pdata, UINT32 addr, UINT32 reg) {

    UINT32 XgmacBase;
    UINT32 mdio_sca, mdio_sccd;
    INT32 Mdioreg = 0;
    UINT32 Count = CMD_TIMEOUT;

    XgmacBase = pdata->xgmac_pdata.xgmac_regs;

    mdio_sca = 0;
    SET_BITS(mdio_sca, 0, 21, reg);
    SET_BITS(mdio_sca, 21, 5, addr);
    MmioWrite32(XgmacBase + MAC_MDIOSCAR, mdio_sca);

    mdio_sccd = 0;
    SET_BITS(mdio_sccd, 16, 2, 3);
    SET_BITS(mdio_sccd, 22, 1, 1);
    MmioWrite32(XgmacBase + MAC_MDIOSCCDR, mdio_sccd);

    while (Count--) {
        Mdioreg = MmioRead32(XgmacBase + MAC_MDIOISR);
        if (Mdioreg & BIT12) {
            //Adapter->mdio_complete = FALSE;
            break;
        }
        gBS->Stall(1000); //1 milli seconds
        }

    if (!Count) {
        DEBUG((EFI_D_ERROR,"%a:line(%d), Count=%x\n", __FUNCTION__, __LINE__, Count));
        return -1;
    }

    Mdioreg = MmioRead32(XgmacBase + MAC_MDIOSCCDR);

    Mdioreg = GET_BITS(Mdioreg, 0, 16);
    DEBUG((EFI_D_ERROR,"%a:line(%d), returnVal Mdioreg=%x\n", __FUNCTION__, __LINE__, Mdioreg));

    return Mdioreg;

}

INT32 phy_read_mmd(ENET_DXE_PRIVATE_DATA *pdata, UINT32 addr, UINT32 reg) {
    INT32 RegVal;
    UINTN ret;

    ret =  xgbe_phy_get_comm_ownership(pdata);
    if (ret) {
        DEBUG((EFI_D_ERROR, "phy_read_mmd xgbe_phy_get_comm_ownership failed\n"));
        return -1;
    }

    RegVal = xgbe_read_ext_mii_regs(pdata, addr, reg);

    xgbe_phy_put_comm_ownership(pdata);

    DEBUG((EFI_D_ERROR, "phy_read_mmd exit reg= %x RegVal= %x\n", reg, RegVal));

    return RegVal;
}

INT32 phy_read(ENET_DXE_PRIVATE_DATA *pdata, UINT32 reg) {
    INT32 RegVal;
    UINT32 addr;
    UINTN ret;

    XGBE_PHY_DATA *phy_data = pdata->phy_data;
  
    addr = phy_data->port_id;

    DEBUG((EFI_D_ERROR, "phy_read entry reg= %x\n", reg));

    ret = xgbe_phy_get_comm_ownership(pdata);
    if (ret) {
        DEBUG((EFI_D_ERROR, "phy_read xgbe_phy_get_comm_ownership failed\n"));
        return -1;
    }

    RegVal = xgbe_phy_mii_read(pdata, addr, reg);

    xgbe_phy_put_comm_ownership(pdata);

    DEBUG((EFI_D_ERROR, "phy_read exit reg= %x RegVal= %x\n", reg, RegVal));

    return RegVal;
}

EFI_STATUS xgbe_set_ext_mii_mode(ENET_DXE_PRIVATE_DATA *pdata, UINT32 port,
        UINT32 mode) {

    UINT32 XgmacBase;
    UINT32 Mdioreg = 0;

    DEBUG((EFI_D_ERROR, "xgbe_set_ext_mii_mode port= %x mode=%x\n", port, mode));

    XgmacBase = pdata->xgmac_pdata.xgmac_regs;
    Mdioreg = MmioRead32(XgmacBase + MAC_MDIOCL22R);
    Mdioreg |= (1 << port);
    MmioWrite32(XgmacBase + MAC_MDIOCL22R, Mdioreg);

    return EFI_SUCCESS;
}

EFI_STATUS phy_poll_reset(ENET_DXE_PRIVATE_DATA *pdata) {

    /* Poll until the reset bit clears (50ms per retry == 0.6 sec) */
    UINT8 retries = 12;
    INT32 RegVal;

    DEBUG((EFI_D_ERROR, "phy_poll_reset entry\n"));

    do {
        gBS->Stall(50000); //50 milli seconds

        RegVal = phy_read(pdata, MII_BMCR);
        if (RegVal < 0) {
            DEBUG((EFI_D_ERROR, "phy_poll_reset error exit 1\n"));
            return 1;
        }
    } while ((RegVal & BMCR_RESET) && --retries);

    if (RegVal & BMCR_RESET) {
        DEBUG((EFI_D_ERROR, "phy_poll_reset error exit 2\n"));
        return 1;
    }

    /* Some chips (smsc911x) may still need up to another 1ms after the
     *  * BMCR_RESET bit is cleared before they are usable.
     *  */
    gBS->Stall(1000); //1 milli second
    DEBUG((EFI_D_ERROR, "phy_poll_reset exit\n"));

    return EFI_SUCCESS;
}

EFI_STATUS genphy_soft_reset(ENET_DXE_PRIVATE_DATA *pdata) {

    EFI_STATUS Status;
    XGBE_PHY_DATA *phy_data = pdata->phy_data;

    DEBUG((EFI_D_ERROR, "genphy_soft_reset entry\n"));

    xgbe_set_ext_mii_mode(pdata, (UINT32) phy_data->port_id,
            (UINT32) phy_data->phydev_mode);

    Status = phy_write(pdata, MII_BMCR, BMCR_RESET);
    if (EFI_ERROR(Status)) {
        DEBUG((EFI_D_ERROR, "phy_write  genphy_soft_reset failed\n"));
        return Status;
    }

    Status = phy_poll_reset(pdata);

    DEBUG((EFI_D_ERROR, "genphy_soft_reset exit\n"));

    return Status;
}

EFI_STATUS marvell_set_page(ENET_DXE_PRIVATE_DATA *pdata, UINT32 page) {
    EFI_STATUS Status;
    Status = phy_write(pdata, MII_MARVELL_PHY_PAGE, (UINT16) page);
    return Status;
}

INT32 marvell_get_page(ENET_DXE_PRIVATE_DATA *pdata) {

    INT32 page;
    page = phy_read(pdata, MII_MARVELL_PHY_PAGE);
    return page;
}

EFI_STATUS marvell_get_set_page(ENET_DXE_PRIVATE_DATA *pdata, UINT32 page) {

	EFI_STATUS Status;
	INT32 oldpage = marvell_get_page(pdata);

	if (oldpage < 0) {
		return 1;
	}

	if (page != (UINT32) oldpage) {
		Status = marvell_set_page(pdata, page);
		return Status;
	}

	return 0;
}

EFI_STATUS m88e1121_config_init(ENET_DXE_PRIVATE_DATA *pdata) {

    EFI_STATUS Status;
    INT32 oldpage, page;

    DEBUG((EFI_D_ERROR, "m88e1121_config_init entry\n"));

    //Status = marvell_get_set_page(pdata, MII_MARVELL_LED_PAGE);
    //if (EFI_ERROR (Status)){
    //	DEBUG ((EFI_D_ERROR, "marvell_get_set_page failed\n"));
    //	return Status;
    //}
    page = MII_MARVELL_LED_PAGE;
    oldpage = marvell_get_page(pdata);

    if (oldpage < 0) {
        return 1;

    }

    if (page != oldpage) {
        Status = marvell_set_page(pdata, (UINT32) page);
    }

    /* Default PHY LED config: LED[0] .. Link, LED[1] .. Activity */
    Status = phy_write(pdata, MII_88E1121_PHY_LED_CTRL,
            MII_88E1121_PHY_LED_DEF);
    if (EFI_ERROR(Status)) {
        DEBUG((EFI_D_ERROR, "phy_write [Default PHY LED config: LED[0] .. Link, LED[1] .. Activity] failed\n"));
        return Status;
    }

    Status = marvell_set_page(pdata, oldpage);

    DEBUG((EFI_D_ERROR, "m88e1121_config_init exit\n"));

    return Status;
}

EFI_STATUS m88e1510_config_init(ENET_DXE_PRIVATE_DATA *pdata) {
	EFI_STATUS Status;
	UINT32 RegVal;

	DEBUG((EFI_D_ERROR, "m88e1510_config_init entry\n"));

	/* Select page 18 */
	Status = marvell_set_page(pdata, 18);
	if (EFI_ERROR(Status)) {
		DEBUG((EFI_D_ERROR, "marvell_set_page 18 failed\n"));
		return Status;
	}

	/* In reg 20, write MODE[2:0] = 0x1 (SGMII to Copper) */
	RegVal = phy_read(pdata, MII_88E1510_GEN_CTRL_REG_1);
	RegVal &= ~MII_88E1510_GEN_CTRL_REG_1_MODE_MASK;
	RegVal |= MII_88E1510_GEN_CTRL_REG_1_MODE_SGMII;
	Status = phy_write(pdata, MII_88E1510_GEN_CTRL_REG_1, (UINT16) RegVal);
	if (EFI_ERROR(Status)) {
		DEBUG((EFI_D_ERROR, "phy_write [In reg 20, write MODE[2:0] = 0x1] failed\n"));
		return Status;
	}

	/* PHY reset is necessary after changing MODE[2:0] */
	RegVal |= MII_88E1510_GEN_CTRL_REG_1_RESET;
	Status = phy_write(pdata, MII_88E1510_GEN_CTRL_REG_1, (UINT16) RegVal);
	if (EFI_ERROR(Status)) {
		DEBUG((EFI_D_ERROR, "phy_write [PHY reset is necessary after changing MODE[2:0]] failed\n"));
		return Status;
	}

	/* Reset page selection */
	Status = marvell_set_page(pdata, MII_MARVELL_COPPER_PAGE);
	if (EFI_ERROR(Status)) {
		DEBUG((EFI_D_ERROR, "marvell_set_page MII_MARVELL_COPPER_PAGE failed\n"));
		return Status;
	}

	Status = m88e1121_config_init(pdata);
	if (EFI_ERROR(Status)) {
		DEBUG((EFI_D_ERROR, "marvell_set_page m88e1121_config_init failed\n"));
	}
	DEBUG((EFI_D_ERROR, "m88e1510_config_init exit\n"));

	return Status;

}

/* Some PHYs within the Alaska family like 88x3310 has problems with the
 * KR Auto-negotiation. marvell datasheet for 88x3310 section 6.2.11 says that
 * KR auto-negotitaion can be enabled to adapt to the incoming SERDES by writing
 * to autoneg registers and the PMA/PMD registers
 */
static int mv3310_amd_quirk(ENET_DXE_PRIVATE_DATA *phydev)
{
    int reg = 0, count = 0;
    UINTN version, subversion;
    UINT32 XgmacBase;

    XgmacBase =	phydev->xgmac_pdata.xgmac_regs;

    version = phy_read_mmd(phydev, MDIO_MMD_PMAPMD, 0xC011);
    subversion = phy_read_mmd(phydev, MDIO_MMD_PMAPMD, 0xC012);
    DEBUG((EFI_D_INFO, "%a:line(%d) Marvell FW Version: %x.%x \n", __FUNCTION__, __LINE__, version, subversion));

    if (subversion != 0x400) {
        DEBUG((EFI_D_INFO, "%a:line(%d) Not a default Marvell FW Version: %x.%x \n", __FUNCTION__, __LINE__, version, subversion));
        return -1;
    }

    reg = phy_read_mmd(phydev, MDIO_MMD_PHYXS, MV_V2_HOST_KR_ENABLE);
    reg |= 0x8000;
    phy_write_mmd(phydev, MDIO_MMD_PHYXS, MV_V2_HOST_KR_ENABLE, reg);

    reg = phy_read_mmd(phydev, MDIO_MMD_PHYXS, MV_V2_HOST_KR_TUNE);
    reg = (reg & ~0x8000) | 0x4000;
    phy_write_mmd(phydev, MDIO_MMD_PHYXS, MV_V2_HOST_KR_TUNE, reg);

    if ((reg & BIT8) && (reg & BIT11)) {
        reg = phy_read_mmd(phydev, MDIO_MMD_AN, MV_PCS_BASE_R);
        /* disable BASE-R */
        phy_write_mmd(phydev, MDIO_MMD_AN, MV_PCS_BASE_R, reg);
    } else {
        reg = phy_read_mmd(phydev, MDIO_MMD_AN, MV_PCS_BASE_R);
        /* enable BASE-R for KR initiation */
        reg |= 0x1000;
        phy_write_mmd(phydev, MDIO_MMD_AN, MV_PCS_BASE_R, reg);
    }

    /* down the port if no link */
    reg = phy_read_mmd(phydev, MDIO_MMD_VEND2, MV_V2_MODE_CFG);
    reg &= 0xFFF7;
    phy_write_mmd(phydev, MDIO_MMD_VEND2, MV_V2_MODE_CFG, reg);

    /* reset port to effect above change */
    reg = phy_read_mmd(phydev, MDIO_MMD_VEND2, MV_V2_PORT_CTRL);

    reg |= 0x8000;
    phy_write_mmd(phydev, MDIO_MMD_VEND2, MV_V2_PORT_CTRL, reg);

    /* wait till reset complete */
    count = 50;

    do {
        //msleep(10);
        gBS->Stall (10000);//10 milli seconds
        reg = phy_read_mmd(phydev, MDIO_MMD_VEND2, MV_V2_PORT_CTRL);
    } while ((reg & 0x8000) && --count);

    if (reg & 0x8000) {
        DEBUG((EFI_D_ERROR,"%a: Port Reset taking long time\n",__FUNCTION__));
        return -1;
    }

    /* LED0 Amber light On-Off settings [1:0]=01 */
    reg = phy_read_mmd(phydev, MDIO_MMD_VEND2, MV_V2_LED0_CTRL);

    if ((reg & 0x3) != 0x1) {
        reg &= 0xFFFC;
        reg |= 0x1;
        phy_write_mmd(phydev, MDIO_MMD_VEND2, MV_V2_LED0_CTRL, reg);
    }

    DEBUG((EFI_D_INFO, "%a: quirk applied\n",__FUNCTION__));
    return EFI_SUCCESS;
}

EFI_STATUS phy_init_hw(ENET_DXE_PRIVATE_DATA *pdata) {
    EFI_STATUS Status;
    DEBUG((EFI_D_ERROR, "phy_init_hw entry\n"));

    // Status = genphy_soft_reset(pdata);
    // if (EFI_ERROR(Status)) {
    // 	DEBUG((EFI_D_ERROR, "genphy_soft_reset failed\n"));
    // 	return Status;
    // }

    //Status = m88e1510_config_init(pdata);
    // if (EFI_ERROR(Status)) {
    // 	DEBUG((EFI_D_ERROR, "m88e1510_config_init failed\n"));
    // }

    Status = mv3310_amd_quirk(pdata);
    if (EFI_ERROR(Status)) {
        DEBUG((EFI_D_ERROR, "mv3310_amd_quirk failed\n"));
    }

    DEBUG((EFI_D_ERROR, "phy_init_hw exit\n"));

    return EFI_SUCCESS;
}

UINT32 ethtool_adv_to_mii_ctrl1000_t(UINT32 ethadv)
{
    UINT32 result = 0;

    if (ethadv & ADVERTISED_1000baseT_Half)
        result |= ADVERTISE_1000HALF;
    if (ethadv & ADVERTISED_1000baseT_Full)
        result |= ADVERTISE_1000FULL;

    return result;
}


INT32 genphy_config_advert(ENET_DXE_PRIVATE_DATA *pdata){

    UINT32 advertise;
    INT32 oldadv, adv, bmsr;
    INT32 changed = 0;
    EFI_STATUS Status;  

    DEBUG((EFI_D_ERROR, "genphy_config_advert\n"));

    /* Only allow advertising what this PHY supports */
    pdata->phy.advertising = pdata->phy.supported;
    
    advertise = (UINT32)pdata->phy.advertising;

    /* Setup standard advertisement */
    adv = phy_read(pdata, MII_ADVERTISE);
    if (adv < 0){
        return 1;
    }

    //oldadv = adv;
    //adv &= ~(ADVERTISE_ALL | ADVERTISE_100BASE4 | ADVERTISE_PAUSE_CAP |
    //     ADVERTISE_PAUSE_ASYM);
    //adv |= 0; //ethtool_adv_to_mii_adv_t(advertise);

    //if (adv != oldadv)
    //{
    //    Status = phy_write(pdata, MII_ADVERTISE, (u16)adv);
    //    if (EFI_ERROR(Status)) {
    //        DEBUG((EFI_D_ERROR, "phy_write MII_ADVERTISE failed\n"));
    //        return Status;
    //    }
    //    changed = 1;
    //}

    bmsr = phy_read(pdata, MII_BMSR);
    if (bmsr < 0){
        return 1;
    }

    /* Per 802.3-2008, Section 22.2.4.2.16 Extended status all
     * 1000Mbits/sec capable PHYs shall have the BMSR_ESTATEN bit set to a
     * logical 1.
     */
    if (!(bmsr & BMSR_ESTATEN)){
        return changed;
    }

    /* Configure gigabit if it's supported */
    adv = phy_read(pdata, MII_CTRL1000);
    if (adv < 0){
        return adv;
    }

    oldadv = adv;
    adv &= ~(ADVERTISE_1000FULL | ADVERTISE_1000HALF);

    if (pdata->phy.supported & (SUPPORTED_1000baseT_Half |
                 SUPPORTED_1000baseT_Full)) {
        adv |= ethtool_adv_to_mii_ctrl1000_t(advertise);
    }

    if (adv != oldadv)
            changed = 1;

    Status = phy_write(pdata, MII_CTRL1000, (UINT16)adv);
    if (EFI_ERROR(Status)) {
        DEBUG((EFI_D_ERROR, "phy_write MII_CTRL1000 failed\n"));
        return 0;
    }

    return changed;
}


EFI_STATUS genphy_restart_aneg(ENET_DXE_PRIVATE_DATA *pdata){

    EFI_STATUS Status;  
    XGBE_PHY_DATA *phy_data = pdata->phy_data;
    INT32 ctl;
    
    DEBUG((EFI_D_ERROR, "genphy_restart_aneg entry\n"));
    
    ctl = phy_read(pdata, MII_PHYSID1);
            if (ctl < 0){
                return 1;
            }
    DEBUG((EFI_D_ERROR, "genphy_restart_aneg MII_PHYSID1 %x\n",ctl));
    
    ctl = phy_read(pdata, MII_PHYSID2);
            if (ctl < 0){
                return 1;
            }
    DEBUG((EFI_D_ERROR, "genphy_restart_aneg MII_PHYSID2 %x\n",ctl));

    
    ctl = phy_read(pdata, MII_BMCR);
        if (ctl < 0){
            return 1;
        }
        
    ctl |= BMCR_ANENABLE | BMCR_ANRESTART;

    /* Don't isolate the PHY if we're negotiating */
    ctl &= ~BMCR_ISOLATE;

    Status = phy_write(pdata, MII_BMCR, (UINT16)ctl);
    if (EFI_ERROR(Status)) {
        DEBUG((EFI_D_ERROR, "phy_write MII_BMCR failed\n"));
        return Status;
    }
    
    xgbe_set_ext_mii_mode(pdata,(UINT32)phy_data->port_id,(UINT32)phy_data->phydev_mode);

    return EFI_SUCCESS;
}

EFI_STATUS genphy_config_aneg(ENET_DXE_PRIVATE_DATA *pdata){

    INT32 result,changed;
    EFI_STATUS Status = EFI_SUCCESS; 

    DEBUG((EFI_D_ERROR, "genphy_config_aneg\n"));	
      
    changed = 1; //genphy_config_eee_advert(phydev);

    //if (AUTONEG_ENABLE != phydev->autoneg)
    //{
    //    result = genphy_setup_forced(phydev);
    //    RT_TRACE(COMP_INIT,DBG_TRACE,("[%s %d] result:%d portId:%d\n",__FUNCTION__,__LINE__,result,Adapter->port_id));
    //    return result;
    //}

    result = genphy_config_advert(pdata);
    if (result < 0) /* error */
    {
        return 1;
    }

    changed |= result;
    if (changed == 0)
    {
        /* Advertisement hasn't changed, but maybe aneg was never on to
         * begin with?  Or maybe phy was isolated?
         */
        INT32 ctl = phy_read(pdata, MII_BMCR);
        if (ctl < 0)
        {
            return Status;
        }

        if (!(ctl & BMCR_ANENABLE) || (ctl & BMCR_ISOLATE)){
            result = 1; /* do restart aneg */
        }
    }

    /* Only restart aneg if we are advertising something different
     * than we were before.
     */
    if (changed > 0){
        Status = genphy_restart_aneg(pdata);
    }

    return Status;
}


EFI_STATUS m88e1121_config_aneg(ENET_DXE_PRIVATE_DATA *pdata) {

	EFI_STATUS Status;

	DEBUG((EFI_D_ERROR, "m88e1121_config_aneg\n"));	

    //if (phy_interface_is_rgmii(phydev)) {
    //    err = m88e1121_config_aneg_rgmii_delays(phydev);
    //    if (err)
    //        return err;
    //}
    
	Status = genphy_soft_reset(pdata);
	if (EFI_ERROR(Status)) {
		DEBUG((EFI_D_ERROR, "genphy_soft_reset failed\n"));
		return Status;
	}
	
	//err = marvell_set_polarity(phydev, phydev->mdix_ctrl);
    //if (err < 0)
    //{
    //    RT_TRACE(COMP_INIT, DBG_TRACE,("[%s %d] marvell_set_polarity failed portId:%d\n",__FUNCTION__,__LINE__,Adapter->port_id));
    //    return err;
    //}

	Status = genphy_config_aneg(pdata);

	return Status;
}

EFI_STATUS m88e1318_config_aneg(ENET_DXE_PRIVATE_DATA *pdata ){
	EFI_STATUS Status;
	INT32 oldpage, page, mscr;
	page = MII_MARVELL_MSCR_PAGE;
	DEBUG((EFI_D_ERROR, "m88e1318_config_aneg\n"));	
	
	oldpage = marvell_get_page(pdata);
	if (oldpage < 0 ){
		return 1;
	}

	if (page != oldpage ){
	 Status = marvell_set_page(pdata, page);
		//return Status;
	}
	mscr = phy_read(pdata, MII_88E1318S_PHY_MSCR1_REG);
	mscr |= MII_88E1318S_PHY_MSCR1_PAD_ODD;
	Status = phy_write(pdata, MII_88E1318S_PHY_MSCR1_REG, (UINT16 )mscr);
	if (EFI_ERROR(Status)){
		DEBUG ((EFI_D_ERROR, "phy_write [MII_88E1318S_PHY_MSCR1_REG] failed\n"));
		return Status;
	}

	Status = marvell_set_page(pdata, oldpage);
	if (EFI_ERROR(Status) ){
		DEBUG ((EFI_D_ERROR, "marvell_set_page oldpage failed\n"));
		return Status;
	}

	Status = m88e1121_config_aneg(pdata);
	if (EFI_ERROR(Status) ){
		DEBUG ((EFI_D_ERROR, "m88e1121_config_aneg failed\n"));
	}
	
	mscr = phy_read(pdata, MII_PHYSID1);
            if (mscr < 0){
                return 1;
            }
    DEBUG((EFI_D_ERROR, "m88e1318_config_aneg MII_PHYSID1 %x\n",mscr));
    
    mscr = phy_read(pdata, MII_PHYSID2);
            if (mscr < 0){
                return 1;
            }
    DEBUG((EFI_D_ERROR, "m88e1318_config_aneg MII_PHYSID2 %x\n",mscr));        
	return Status;
}

EFI_STATUS m88e1510_config_aneg(ENET_DXE_PRIVATE_DATA *pdata){ 

	EFI_STATUS Status;
    UINT32 XpcsBase;
  
    XpcsBase = pdata->xpcs_regs;

	DEBUG((EFI_D_ERROR, "m88e1510_config_aneg\n"));		
      
	Status = marvell_set_page(pdata, MII_MARVELL_COPPER_PAGE);
	if (EFI_ERROR (Status) ){
		DEBUG((EFI_D_ERROR, "marvell_set_page MII_MARVELL_COPPER_PAGE failed\n"));
		goto error;
	}
	/* Configure the copper link first */
	Status = m88e1318_config_aneg(pdata);
	if (EFI_ERROR (Status) ){
		DEBUG ((EFI_D_ERROR, "m88e1318_config_aneg failed\n"));
		goto error;
	}

	///* Then the fiber link */
	//Status = marvell_set_page(pdata, MII_MARVELL_FIBER_PAGE);
	//if (EFI_ERROR (Status)){
	//	DEBUG ((EFI_D_ERROR, "marvell_set_page MII_MARVELL_COPPER_PAGE failed\n"));
	//	goto error;
	//}
	//	

	//err = marvell_config_aneg_fiber(phydev);
	//if (err < 0)
	//{
	//	RT_TRACE(COMP_INIT, DBG_ERROR,("[%s %d] Set fiber link failed portId:%d \n",__FUNCTION__,__LINE__,Adapter->port_id));
	//	goto error;
	//}

	//Status = marvell_set_page(pdata, MII_MARVELL_COPPER_PAGE);
	//return Status;

    //xgbe_an37_set_EN_VSMMD1(XpcsBase);	
error:
 	marvell_set_page(pdata, MII_MARVELL_COPPER_PAGE);
	return Status;
}

/**

  Memory compare

  @param  Destination           Target address.
  @param  Source                Orignal address.
  @param  Length                Data length

**/
STATIC
UINTN
Memcmp (
  IN VOID   *Destination,
  IN VOID   *Source,
  IN UINT8  Length
  )
{
  UINT8 *Destination8;
  UINT8 *Source8;

  Destination8 = Destination;
  Source8 = Source;
  while (Length--) {
    if (*(Destination8++) != *(Source8++)) {
     return 1;
    }
  }
  return 0;
}

BOOLEAN
xgbe_phy_finisar_phy_quirks(
        ENET_DXE_PRIVATE_DATA *pdata,
        UINT32 phy_id
        )
{
    XGBE_PHY_DATA *phy_data = pdata->phy_data;

    DEBUG ((EFI_D_ERROR, "Finisar PHY quirk - start \n"));

    if (phy_data->port_mode != XGBE_PORT_MODE_SFP)
        return FALSE;

    if ((phy_id & 0xfffffff0) != 0x01ff0cc0)
        return FALSE;

    DEBUG ((EFI_D_ERROR, "Finiser FUSE PHY quirk Finiser FUSE MATCH \n"));

    /* Enable Base-T AN */
    phy_write(pdata, 0x16, 0x0001);
    phy_write(pdata, 0x00, 0x9140);
    phy_write(pdata, 0x16, 0x0000);

    /* Enable SGMII at 100Base-T/1000Base-T Full Duplex */
    phy_write(pdata, 0x1b, 0x9084);
    phy_write(pdata, 0x09, 0x0e00);
    phy_write(pdata, 0x00, 0x8140);
    phy_write(pdata, 0x04, 0x0d01);
    phy_write(pdata, 0x00, 0x9140);

    DEBUG ((EFI_D_ERROR, "Finisar PHY quirk in place\n"));

    return TRUE;
}


BOOLEAN 
xgbe_phy_belfuse_phy_quirks(
        ENET_DXE_PRIVATE_DATA *pdata,
        UINT32 phy_id
        )
{
    XGBE_PHY_DATA *phy_data = pdata->phy_data;
    xgbe_sfp_eeprom *sfp_eeprom = &phy_data->sfp_eeprom;
    int reg;
    EFI_STATUS Status;

    if (phy_data->port_mode != XGBE_PORT_MODE_SFP)
        return FALSE;

    DEBUG ((EFI_D_ERROR, "BEL FUSE PHY quirk - start \n"));

    if (Memcmp(&sfp_eeprom->base[XGBE_SFP_BASE_VENDOR_NAME],
            XGBE_BEL_FUSE_VENDOR, XGBE_SFP_BASE_VENDOR_NAME_LEN))
        return FALSE;

    if (Memcmp(&sfp_eeprom->base[XGBE_SFP_BASE_VENDOR_PN],
            XGBE_BEL_FUSE_PARTNO, XGBE_SFP_BASE_VENDOR_PN_LEN))
        return FALSE;

    if ((phy_id & 0xfffffff0) != 0x03625d10)
        return FALSE;

    DEBUG ((EFI_D_ERROR, "BEL FUSE PHY quirk BEL FUSE MATCH \n"));

    /* Disable RGMII mode */
    Status = phy_write(pdata, 0x18, 0x7007);
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "Disable RGMII mode Phy write failed \n"));
        return FALSE;
    }
    reg = phy_read(pdata, 0x18);
    Status = phy_write(pdata, 0x18, reg & ~0x0080);
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "Disable RGMII mode Phy write failed \n"));
        return FALSE;
    }

    /* Enable fiber register bank */
    Status = phy_write(pdata, 0x1c, 0x7c00);
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "Enable fiber register bank Phy write failed \n"));
        return FALSE;
    }
    reg = phy_read(pdata, 0x1c);
    reg &= 0x03ff;
    reg &= ~0x0001;
    Status = phy_write(pdata, 0x1c, 0x8000 | 0x7c00 | reg | 0x0001);
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "Enable fiber register bank Phy write failed \n"));
        return FALSE;
    }
    
    /* Power down SerDes */
    reg = phy_read(pdata, 0x00);
    Status = phy_write(pdata, 0x00, reg | 0x00800);
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "Power down SerDes Phy write failed \n"));
        return FALSE;
    }

    /* Configure SGMII-to-Copper mode */
    Status = phy_write(pdata, 0x1c, 0x7c00);
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "Configure SGMII-to-Copper mode Phy write failed \n"));
        return FALSE;
    }
    reg = phy_read(pdata, 0x1c);
    reg &= 0x03ff;
    reg &= ~0x0006;
    Status = phy_write(pdata, 0x1c, 0x8000 | 0x7c00 | reg | 0x0004);
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "Power down SerDes Phy write failed \n"));
        return FALSE;
    }

    /* Power up SerDes */
    reg = phy_read(pdata, 0x00);
    Status = phy_write(pdata, 0x00, reg & ~0x00800);
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "Power up SerDes Phy write failed \n"));
        return FALSE;
    }

    /* Enable copper register bank */
    Status = phy_write(pdata, 0x1c, 0x7c00);
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "Enable copper register bank Phy write failed \n"));
        return FALSE;
    }
    reg = phy_read(pdata, 0x1c);
    reg &= 0x03ff;
    reg &= ~0x0001;
    Status = phy_write(pdata, 0x1c, 0x8000 | 0x7c00 | reg);
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "Enable copper register bank Phy write failed \n"));
        return FALSE;
    }

    /* Power up SerDes */
    reg = phy_read(pdata, 0x00);
    Status = phy_write(pdata, 0x00, reg & ~0x00800);
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "Enable copper register bank Phy write failed \n"));
        return FALSE;
    }

    DEBUG ((EFI_D_ERROR, "BelFuse PHY quirk in place\n"));

    return TRUE;
}

UINT32 
get_phy_id(
        ENET_DXE_PRIVATE_DATA *pdata
        )
{ 
    int reg;
    UINT32 phy_id;
    reg = phy_read(pdata, MII_PHYSID1);
    phy_id = reg << 16;

    reg = phy_read(pdata, MII_PHYSID2);
    phy_id |= reg;

    return phy_id;
}


/* Linux driver has this code to support BEL and FINSER Fuses stability.
Bit for PXE as of now this code is not helping. In future we may need 
to experiment calling this code depending on the issues we are facing.
As we laready implemented  this code for PXE , We are keeping this code 
in this file for future use if needed*/

VOID 
xgbe_phy_external_phy_quirks(
        ENET_DXE_PRIVATE_DATA *pdata
        )
{ 
    UINT32 phy_id = get_phy_id(pdata);

    DEBUG ((EFI_D_ERROR, "xgbe_phy_external_phy_quirks - phy_id = %x  \n", phy_id));

    if (xgbe_phy_belfuse_phy_quirks(pdata , phy_id))
        return;

    if (xgbe_phy_finisar_phy_quirks(pdata , phy_id))
        return;
}



