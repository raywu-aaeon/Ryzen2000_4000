
#ifndef __MDIO_H__
#define __MDIO_H__

/* Generic MII registers. */
#define MII_BMCR                    0x00    /* Basic mode control register */
#define MII_BMSR                    0x01    /* Basic mode status register  */
#define MII_PHYSID1                 0x02    /* PHYS ID 1                   */
#define MII_PHYSID2                 0x03    /* PHYS ID 2                   */
#define MII_ADVERTISE               0x04    /* Advertisement control reg   */
#define MII_LPA                     0x05    /* Link partner ability reg    */
#define MII_EXPANSION               0x06    /* Expansion register          */
#define MII_CTRL1000                0x09    /* 1000BASE-T control          */
#define MII_STAT1000                0x0a    /* 1000BASE-T status           */
#define MII_MMD_CTRL                0x0d    /* MMD Access Control Register */
#define MII_MMD_DATA                0x0e    /* MMD Access Data Register */
#define MII_ESTATUS                 0x0f    /* Extended Status             */
#define MII_DCOUNTER                0x12    /* Disconnect counter          */
#define MII_FCSCOUNTER              0x13    /* False carrier counter       */
#define MII_NWAYTEST                0x14    /* N-way auto-neg test reg     */
#define MII_RERRCOUNTER             0x15    /* Receive error counter       */
#define MII_SREVISION               0x16    /* Silicon revision            */
#define MII_RESV1                   0x17    /* Reserved...                 */
#define MII_LBRERROR                0x18    /* Lpback, rx, bypass error    */
#define MII_PHYADDR                 0x19    /* PHY address                 */
#define MII_RESV2                   0x1a    /* Reserved...                 */
#define MII_TPISTATUS               0x1b    /* TPI status for 10mbps       */
#define MII_NCONFIG                 0x1c    /* Network interface config    */

/* Basic mode control register. */
#define BMCR_RESV               0x003f  /* Unused...                   */
#define BMCR_SPEED1000          0x0040  /* MSB of Speed (1000)         */
#define BMCR_CTST               0x0080  /* Collision test              */
#define BMCR_FULLDPLX           0x0100  /* Full duplex                 */
#define BMCR_ANRESTART          0x0200  /* Auto negotiation restart    */
#define BMCR_ISOLATE            0x0400  /* Isolate data paths from MII */
#define BMCR_PDOWN              0x0800  /* Enable low power state      */
#define BMCR_ANENABLE           0x1000  /* Enable auto negotiation     */
#define BMCR_SPEED100           0x2000  /* Select 100Mbps              */
#define BMCR_LOOPBACK           0x4000  /* TXD loopback bits           */
#define BMCR_RESET              0x8000  /* Reset to default state      */

#define MII_88E1121_PHY_LED_CTRL    16
#define MII_88E1121_PHY_LED_PAGE    3
#define MII_88E1121_PHY_LED_DEF     0x0030

/* marvell */
#define MII_MARVELL_PHY_PAGE            22
#define MII_MARVELL_COPPER_PAGE         0x00
#define MII_MARVELL_FIBER_PAGE          0x01
#define MII_MARVELL_MSCR_PAGE           0x02
#define MII_MARVELL_LED_PAGE            0x03
#define MII_MARVELL_MISC_TEST_PAGE      0x06
#define MII_MARVELL_WOL_PAGE            0x11

#define MII_88E1510_GEN_CTRL_REG_1              0x14
#define MII_88E1510_GEN_CTRL_REG_1_MODE_MASK    0x7
#define MII_88E1510_GEN_CTRL_REG_1_MODE_SGMII   0x1 /* SGMII to copper */
#define MII_88E1510_GEN_CTRL_REG_1_RESET        0x8000  /* Soft reset */

#define MII_88E1318S_PHY_MSCR1_REG  16
#define MII_88E1318S_PHY_MSCR1_PAD_ODD  0x40;//BIT(6)



/* Basic mode status register. */
#define BMSR_ERCAP              0x0001  /* Ext-reg capability          */
#define BMSR_JCD                0x0002  /* Jabber detected             */
#define BMSR_LSTATUS            0x0004  /* Link status                 */
#define BMSR_ANEGCAPABLE        0x0008  /* Able to do auto-negotiation */
#define BMSR_RFAULT             0x0010  /* Remote fault detected       */
#define BMSR_ANEGCOMPLETE       0x0020  /* Auto-negotiation complete   */
#define BMSR_RESV               0x00c0  /* Unused...                   */
#define BMSR_ESTATEN            0x0100  /* Extended Status in R15      */
#define BMSR_100HALF2           0x0200  /* Can do 100BASE-T2 HDX       */
#define BMSR_100FULL2           0x0400  /* Can do 100BASE-T2 FDX       */
#define BMSR_10HALF             0x0800  /* Can do 10mbps, half-duplex  */
#define BMSR_10FULL             0x1000  /* Can do 10mbps, full-duplex  */
#define BMSR_100HALF            0x2000  /* Can do 100mbps, half-duplex */
#define BMSR_100FULL            0x4000  /* Can do 100mbps, full-duplex */
#define BMSR_100BASE4           0x8000  /* Can do 100mbps, 4k packets  */


/* 1000BASE-T Control register */
#define ADVERTISE_1000FULL          0x0200  /* Advertise 1000BASE-T full duplex */
#define ADVERTISE_1000HALF          0x0100  /* Advertise 1000BASE-T half duplex */

#define SUPPORTED_1000baseT_Half        (1 << 4)
#define SUPPORTED_1000baseT_Full        (1 << 5)

#define ADVERTISED_100baseT_Full        (1 << 3)

#define ADVERTISED_1000baseT_Half       (1 << 4)
#define ADVERTISED_1000baseT_Full       (1 << 5)
#define ADVERTISED_Autoneg              (1 << 6)
#define ADVERTISED_TP                   (1 << 7)
#define ADVERTISED_FIBER                (1 << 10)

#define ADVERTISED_10000baseT_Full      (1 << 12)
#define ADVERTISED_Pause				(1 << 13)
#define ADVERTISED_Asym_Pause			(1 << 14)
#define ADVERTISED_2500baseX_Full       (1 << 15)
#define ADVERTISED_Backplane            (1 << 16)
#define ADVERTISED_1000baseKX_Full      (1 << 17)
#define ADVERTISED_10000baseKR_Full     (1 << 19)
#define ADVERTISED_10000baseR_FEC		(1 << 20)
#define ADVERTISED_10000baseCR_Full     ((UINT64)1 << 38)

#define ADVERTISED_1000baseX_Full       ((UINT64)1 << 41)
#define ADVERTISED_10000baseSR_Full     ((UINT64)1 << 43)
#define ADVERTISED_10000baseLR_Full     ((UINT64)1 << 44)
#define ADVERTISED_10000baseLRM_Full    ((UINT64)1 << 45)
#define ADVERTISED_10000baseER_Full     ((UINT64)1 << 46)





#define ADVERTISED_2500baseT_Full       ((UINT64)1 << 47)




/* MDI or MDI-X status/control - if MDI/MDI_X/AUTO is set then
 * the driver is required to renegotiate link
 */
#define ETH_TP_MDI_INVALID  0x00 /* status: unknown; control: unsupported */
#define ETH_TP_MDI          0x01 /* status: MDI;     control: force MDI */
#define ETH_TP_MDI_X        0x02 /* status: MDI-X;   control: force MDI-X */
#define ETH_TP_MDI_AUTO     0x03 /*                  control: auto-select */


#define CMD_TIMEOUT         100
#define MAC_MDIOSCAR        0x0200
#define MAC_MDIOSCCDR       0x0204
#define MAC_MDIOISR         0x0214
#define MAC_MDIOCL22R       0x0220
#define MAC_GPIOCR          0x0278
#define MAC_GPIOSR          0x027c

#define GET_BITS(_var, _index, _width)                    \
    (((_var) >> (_index)) & ((0x1 << (_width)) - 1))

#define SET_BITS(_var, _index, _width, _val)                \
do {                                    \
    (_var) &= ~(((0x1 << (_width)) - 1) << (_index));        \
    (_var) |= (((_val) & ((0x1 << (_width)) - 1)) << (_index));    \
} while (0)

#define MASKLOW(numBits) ((1 << (numBits)) - 1)
#define SETBITS(reg, IdxHi, IdxLo)        reg = ((reg) | (MASKLOW((IdxHi) - (IdxLo) + 1) << (IdxLo)))
#define CLEARBITS(reg, IdxHi, IdxLo)      reg = ((reg) & (~(MASKLOW((IdxHi) - (IdxLo) + 1) << (IdxLo))))
#define WRITEBITS(reg, IdxHi, IdxLo, val) CLEARBITS(reg, (IdxHi), (IdxLo)); reg = ((reg) | (val << (IdxLo)))
#define READBITS(reg, IdxHi, IdxLo)       ((reg >> (IdxLo)) & (MASKLOW((IdxHi) - (IdxLo) + 1)))
#define SETBIT(reg, Idx)                  reg = (reg | (1 << Idx))
#define CLEARBIT(reg, Idx)                reg = (reg & (~(1 << Idx)))

EFI_STATUS xgbe_set_ext_mii_mode(ENET_DXE_PRIVATE_DATA *pdata, UINT32 port, UINT32 mode);

EFI_STATUS phy_init_hw(ENET_DXE_PRIVATE_DATA *pdata);

EFI_STATUS m88e1510_config_aneg(ENET_DXE_PRIVATE_DATA *pdata);

VOID xgbe_phy_external_phy_quirks(ENET_DXE_PRIVATE_DATA *pdata);

#endif  //__MDIO_H__
