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

//*************************************************************************
/** @file Gnb.h
    GNB definitions

**/
//*************************************************************************

#ifndef  _GNB_H   //To Avoid this header get compiled twice
#define  _GNB_H

#include "Token.h"

#define GNB_PCI_CFG_ADDRESS(bus, dev, func, reg) \
            (UINT64) ((((UINT8)(bus) << 24) + ((UINT8)(dev) << 16) + \
            ((UINT8)(func) << 8) + ((UINT8)(reg))) & 0xffffffff)

//----------------------------------------------------------------------------
// AMD APU Host Bridge PCI Bus Number Equates
//----------------------------------------------------------------------------
#define GNB_BUS                 0       // GNB Bus Number
#define IGD_BUS                 0       // Integrated Graphics Device
                                        // Bus Number  

//----------------------------------------------------------------------------
// AMD APU Host Bridge Device Number Equates
//----------------------------------------------------------------------------
#define GNB_DEV                 0x00    // GNB Device Number
#define IGD_DEV                 0x01    // Integrated Graphics Device 
                                        // Device Number

//----------------------------------------------------------------------------
// AMD APU Host Bridge Function Number Equates
//----------------------------------------------------------------------------
#define GNB_FUN                 0x00    // GNB Function Number
#define IGD_FUN                 0x00    // Integrated Graphics Device 
                                        // Function Number
#define IGD_AUDIO_FUN           0x01    // Integrated Graphics HD-AUDIO Device
                                        // Function Number

//**********************************************************************
// Bus 0
//**********************************************************************
#define AMD_BUS0                        0x00        // Bus 0

//**********************************************************************
// Device 0 Function 0 (Root Complex) Configuration Registers
//**********************************************************************
#define AMD_RC_DEV                      0x00        // Root Complex Device
#define AMD_RC_FUN                      0x00        // Root Complex Function

//**********************************************************************
// D0F0 Root Complex Registers Definition
//**********************************************************************
#define AMD_RC_SUB_ID                   0x2C        // D0F0x2C Subsystem and Subvendor ID
#define AMD_RC_CP                       0x34        // D0F0x34 Capabilities Pointer
#define AMD_RC_PCI_CL                   0x4C        // D0F0x4C PCI Control
                                        
#define AMD_RC_MISC_INDEX               0x60        // D0F0x60 Miscellaneous Index
#define AMD_RC_MISC_DATA                0x64        // D0F0x64 Miscellaneous Index Data
//----------------------------------------------------------------------
// Miscellaneous Data Regster Definition
#define AMD_RC_MISC_NB_CL               0x00        // D0F0x64_x00 Northbridge Control
#define AMD_RC_MISC_IOC_LK_CL           0x0B        // D0F0x64_x0B IOC Link Control
#define AMD_RC_MISC_IOC_BR_CL           0x0C        // D0F0x64_x0C IOC Bridge Control
#define AMD_RC_MISC_IOC_ADV_ERROR_CL    0x16        // D0F0x64_x16 IOC Advanced Error Reporting Control
#define AMD_RC_MISC_TOP_MEM_2LOW        0x19        // D0F0x64_x19 Top of Memory 2 Low
#define AMD_RC_MISC_TOP_MEM_2HIGH       0x1A        // D0F0x64_x1A Top of Memory 2 High
#define AMD_RC_MISC_IG_PCI_CL           0x1C        // D0F0x64_x1C Internal Graphics PCI Control 1
#define AMD_RC_MISC_IG_PCI_CL2          0x1D        // D0F0x64_x1D Internal Graphics PCI Control 2
#define AMD_RC_MISC_LCLK_CL0            0x22        // D0F0x64_x22 LCLK Control 0
#define AMD_RC_MISC_LCLK_CL1            0x23        // D0F0x64_x23 LCLK Control 1
#define AMD_RC_MISC_SCLK_CL             0x24        // D0F0x64_x24 SCLK Control
#define AMD_RC_MISC_IOC_FEA_CL          0x46        // D0F0x64_x46 IOC Features Control
#define AMD_RC_MISC_SMU_REQ_PORT        0x4D        // D0F0x64_x4D SMU Request Port
#define AMD_RC_MISC_SMU_READ_DATA       0x4E        // D0F0x64_x4E SMU Read Data
#define AMD_RC_MISC_IOC_PCIE_55         0x55        // D0F0x64_x55 IOC PCIe Device Control
#define AMD_RC_MISC_IOC_PCIE_57         0x57        // D0F0x64_x57 IOC PCIe Device Control
#define AMD_RC_MISC_IOC_PCIE_59         0x59        // D0F0x64_x59 IOC PCIe Device Control
#define AMD_RC_MISC_IOC_PCIE_5B         0x5B        // D0F0x64_x5B IOC PCIe Device Control
#define AMD_RC_MISC_VOL_CL              0x6A        // D0F0x64_x6A Voltage Control
#define AMD_RC_MISC_VOL_STATUS          0x6B        // D0F0x64_x6B Voltage Status
// End of Miscellaneous Data Regster Definition
//----------------------------------------------------------------------

//----------------------------------------------------------------------------
// AMD APU PCI Bus/Device/Function/Register Number Macros
//----------------------------------------------------------------------------
#define GNB_REG(Reg)            GNB_PCI_CFG_ADDRESS(GNB_BUS, GNB_DEV, \
                                                   GNB_FUN, Reg)
//----------------------------------------------------------------------------
// AMD APU PCI Bus/Device/Function Number Macros
//----------------------------------------------------------------------------
//#define GNB_BUS_DEV_FUN         GNB_REG(0)
//#define IGD_BUS_DEV_FUN         IGD_REG(0)

#define GNB_BUS_DEV_FUN                  ((0x0 << 3) + 0)  // Root Complex
#define IGD_BUS_DEV_FUN                  ((0x1 << 3) + 0)  // Internal Graphics
#define IGDHDA_BUS_DEV_FUN               ((0x1 << 3) + 1)  // Audio Controller
#define GNB_PCIEBRIDGEx_BUS_DEV_FUN      ((0x2 << 3) + 0)  // Root Port 1 ~ 5
#define GNB_PCIEBRIDGE1_BUS_DEV_FUN      ((0x2 << 3) + 1)  // Root Port 1
#define GNB_PCIEBRIDGE2_BUS_DEV_FUN      ((0x2 << 3) + 2)  // Root Port 2
#define GNB_PCIEBRIDGE3_BUS_DEV_FUN      ((0x2 << 3) + 3)  // Root Port 3
#define GNB_PCIEBRIDGE4_BUS_DEV_FUN      ((0x2 << 3) + 4)  // Root Port 4
#define GNB_PCIEBRIDGE5_BUS_DEV_FUN      ((0x2 << 3) + 5)  // Root Port 5

#define GNB_PCIEBRIDGFXGEx_BUS_DEV_FUN      ((0x3 << 3) + 0)  // GFX Root Port 1 ~ 5
#define GNB_PCIEBRIDGFXGEx1_BUS_DEV_FUN      ((0x3 << 3) + 1)  // GFXRoot Port 1
#define GNB_PCIEBRIDGFXGEx2_BUS_DEV_FUN      ((0x3 << 3) + 2)  // GFX Root Port 2


#define GNBACG_BUS_DEV_FUN               ((0x9 << 3) + 2)  // Audio Controller

#define IGD_SSID_MIRROR             0x4C
#define GNB_D0F0_SSID_MIRROR        0x50
#define GNB_D0F0_WRAPPER_INDEX      0xE0      // D0 F0 Wrapper Index Register
#define GNB_D0F0_WRAPPER_DATA       0xE4      // D0 F0 Wrapper Data Register
#define GNB_D0F0_WRAPPER_INDEX_SSID 0x1300046 // SSID Wrapper Register of D0 F0

#ifndef VID_AMD
#define	VID_AMD				        0x1022	// AMD Vendor ID
#endif

#ifndef AMD_VGA_VID
#define	AMD_VGA_VID				    0x1002	// AMD VGA Vendor ID
#endif

#define PICASSO_IGD_DID             0x15D8  // Internal GPU (Model 18h)        1002 15D8
#define RAVEN_IGD_DID               0x15DD  // Internal GPU (Models 10h,11h)   1002 15DD


//
// The enum type use to identify which GNB device in the code.
//
typedef enum {
    // All GNB device
    GNB_DEV_PCIEBRIDGEx,
    GNB_DEV_ACG,
    GNB_DEV_DGPU,
    GNB_DEV_DGPU_AUDIO,
    GNB_DEV_MAX,
} GNB_DEV_LIST;

#endif  //_GNB_H

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
