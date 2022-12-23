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

/** @file Nb.h
    NorthBridge definitions

**/

#ifndef  _NB_H   //To Avoid this header get compiled twice
#define  _NB_H

#include "Token.h"
#include "Hob.h"

#pragma pack (push, 1)
// DO NOT REMOVE THE DEFINITION OF THIS STRUCTURE. THIS IS USED BY CSM ALSO
/**
//----------------------------------------------------------------------------
// Name: ROOT_BRIDGE_MAPPING_ENTRY
//
// Description:
// This structure is to define root bridge.
//
// Fields: Name             Type                    Description
//----------------------------------------------------------------------------
// Value                   rbUID                    UID of root bridge
// Value                   rbDevFunc                Device/Function of root bridge
//----------------------------------------------------------------------------
**/
typedef	struct ROOT_BRIDGE_MAPPING_TABLE {
    UINT32	rbUID;
    UINT8	rbDevFunc;
} ROOT_BRIDGE_MAPPING_ENTRY;

/**
//----------------------------------------------------------------------------
// Name: NB_MEMORY_LENGTH
//
// Description:
// This structure is to define the memory below/above 4G.
//
// Fields: Name             Type                    Description
//----------------------------------------------------------------------------
// Value                   MemoryLengthBelow4G      TOM below 4G
// Value                   MemoryLengthAbove4G      TOM2 above 4G
//----------------------------------------------------------------------------
**/
typedef struct {
    UINT64  MemoryLengthBelow4G;
    UINT64  MemoryLengthAbove4G;
} NB_MEMORY_LENGTH;
#pragma pack (pop)

#ifndef PCIBUS_VERSION
#define PCIBUS_VERSION ( PCI_BUS_MAJOR_VER * 10000 + \
                         PCI_BUS_MINOR_VER * 100 + \
                         PCI_BUS_REVISION )
#endif 

extern EFI_GUID gNbMemoryLengthGuid;

#define NB_MEMORY_LENGTH_VARIABLE L"NBMemoryLength"

#define NB_PCI_CFG_ADDRESS(bus, dev, func, reg) \
            (UINT64) ((((UINT8)(bus) << 24) + ((UINT8)(dev) << 16) + \
            ((UINT8)(func) << 8) + ((UINT8)(reg))) & 0xffffffff)

// added for getting extended PCI Address
//BUG fixed, previously the reg variable doesnt had a saperate bracket
#define AMD_PCI_CFG_ADDRESS_S3(bus, dev, func, reg) \
    (UINT32)( (UINT64)NB_PCI_CFG_ADDRESS(bus, dev, func, (reg & 0xff)))

//Guid to save TOM
#define AMI_SAVE_TOM_GUID \
    { 0xd692550d, 0x5104, 0x4a61, 0x95, 0xbf, 0x35, 0x6a, 0x49, 0x88, 0xcd, 0x71 }

//Guid to save TOM2
#define AMI_SAVE_TOM2_GUID \
    { 0xa34d5ff1, 0xac12, 0x7809, 0x01, 0x12, 0xfd, 0x6a, 0x49, 0x88, 0xcd, 0xc1 }

#define AMI_UMA_INFO_HOB_GUID \
    {0x561e8d87, 0x42fc, 0x4416, 0xac, 0xd7, 0x54, 0xfb, 0xca, 0xd4, 0x73, 0x5a}

// {43387991-1223-7645-B5BB-AA7675C5C8EF}
#define AMI_MEM_INFO_GUID \
  { 0x43387991, 0x1223, 0x7645, 0xb5, 0xbb, 0xaa, 0x76, 0x75, 0xc5, 0xc8, 0xef }

extern EFI_GUID	gAmiDTomGuid;
extern EFI_GUID gAmiDTom2Guid;
extern EFI_GUID	gAmiUmaInfoHobGuid;
extern EFI_GUID	gAmiMemInfoGuid;

#define TSEG_ALIGN (UINT32)(0xFFFFFFFF - TSEG_SIZE + 1)

extern EFI_GUID gNbAcpiS3VariableGuid;
#define NB_ACPI_S3_VARIABLE     L"NbAcpiS3Variable"
#pragma pack (push, 1)
typedef struct _EFI_PEI_SAVE_TOM2_PPI
{
    UINT64      Base;
    UINT64      Size;
} EFI_PEI_SAVE_TOM2_PPI;

typedef struct {
	EFI_HOB_GUID_TYPE		EfiHobGuidType;
	UINT32					UmaSize;
} UMAINFO_HOB;

typedef struct {
    UINT32      LoMemBase;
    UINT32      LoMemSize;
    UINT64      HiMemBase;
    UINT64      HiMemSize;
    UINT64      UmaBase;
    UINT64      UmaSize;
}AMI_MEM_INFO;
typedef struct _NB_ACPI_S3_VARIABLE_SET {
    //
    // Acpi Related variables
    //
    EFI_PHYSICAL_ADDRESS    AcpiReservedMemoryBase;
    UINT32          AcpiReservedMemorySize;
} NB_ACPI_S3_VARIABLE_SET;
#pragma pack (pop)


/**
//----------------------------------------------------------------------------
// Name: _EFI_PEI_SAVE_TOM_PPI
//
// Description:
// This PPI is published to save the TOM value calculated in memdetect.c.
// The TOM value is restored and used in CpuPeiEntry function to calculate
// SystemMemoryLength.
//
// Fields: Name             Type                    Description
//----------------------------------------------------------------------------
// Value                   UINT64                  Value of TOM
//
//----------------------------------------------------------------------------
**/
#pragma pack (push, 1)
typedef struct _EFI_PEI_SAVE_TOM_PPI
{
    UINT32				    Value;
} EFI_PEI_SAVE_TOM_PPI;
#pragma pack (pop)

// End of Miscellaneous Data Regster Definition
//----------------------------------------------------------------------

//**********************************************************************
// Device 0 Function 0 (Root Complex) Configuration Registers
//**********************************************************************
#define AMD_RC_DEV 0x00 // Root Complex Device
#define AMD_RC_FUN 0x00 // Root Complex Function

//----------------------------------------------------------------------------
// AMD APU PCI Bus/Device/Function/Register Number Macros
//----------------------------------------------------------------------------
#define AMD_BUS0                        0x00        // Bus 0

#define AMD_K8_NODE0_DEV	0x18		// Device Number

#define AMD_K8_BUS_DEV		0x18		// Device Number
#define AMD_K8_BRDG_DEV		0x0A		// PCI secondary bridge

#define DID_AMD_K8_LDT		0x1100		// DID for LDT space
#define DID_AMD_K8_ADDR		0x1101		// DID for Address space
#define DID_AMD_K8_DDRT		0x1102		// DID for DDR and LDT Trace
#define DID_AMD_K8_MISC		0x1103		// DID for Miscellaneous cfg

#define AMD_K8_LDT_FUNC		0			//  LPC Bridge
#define AMD_K8_ADRM_FUNC	1			//  Address map
#define AMD_K8_DDR_FUNC		2			//  DDR Ram configuration
#define AMD_K8_LDTR_FUNC	2			//  Alias for LDT trace
#define AMD_K8_MISC_FUNC	3			//  Misc Config bits

//----------------------------------------------------------------------
//
#define AMD_MCT				(AMD_K8_BUS_DEV  + AMD_K8_LDT_FUNC)
//
//----------------------------------------------------------------------
//   Node numbers expressed as devs 24-31
//
#define NODE0            (24 << 11)
#define NODE1            (25 << 11)
#define NODE2            (26 << 11)
#define NODE3            (27 << 11)
#define NODE4            (28 << 11)
#define NODE5            (29 << 11)
#define NODE6            (30 << 11)
#define NODE7            (31 << 11)

//-----------------------------------------------------------------------
//
//   AMD_K8 Devices 24-31 correlates to LDT nodes 0-7
//
//   Function 0  - LDT configuration.
//
//-----------------------------------------------------------------------

#define AMD_K8_nF0_VID0            0x00            //Vendor ID Register
#define AMD_K8_nF0_VID1            0x01            //Vendor ID Register
#define AMD_K8_nF0_DID0            0x02            //Device ID Register
#define AMD_K8_nF0_DID1            0x03            //Device ID Register
#define AMD_K8_nF0_PCICMD          0x04            //PCI Command Register
#define AMD_K8_nF0_PCISTS          0x06            //PCI Status Register
#define AMD_K8_nF0_RID             0x08            //Revision ID Register
#define AMD_K8_nF0_PROG            0x09            //Program Interface
#define AMD_K8_nF0_SUBC            0x0A            //Sub-Class Code Register
#define AMD_K8_nF0_BCC             0x0B            //Base Class Code Register
#define AMD_K8_nF0_RSVD1           0x0C            //Reserved by AMD
#define AMD_K8_nF0_MLT             0x0D            //Master Latency Timer Register
#define AMD_K8_nF0_HDR             0x0E            //Header Type Register
#define AMD_K8_nF0_RSVD2           0x0F            //Reserved by AMD
#define AMD_K8_nF0_BAR0            0x10            //BAR0 (AGP virtual addr space))
#define AMD_K8_nF0_BAR1            0x14            //BAR1 (GART Mem Mapp Ptr)
#define AMD_K8_nF0_BAR2            0x18            //Aperture PM2 I/O register
#define AMD_K8_nF0_IOBL            0x1C            //I/O Base and Limit      r
#define AMD_K8_nF0_SSVID           0x2C            //SSVENDORID  Dev A:70 Wr
#define AMD_K8_nF0_SSID            0x2E            //SS ID       Dev A:70 Wr
#define AMD_K8_nF0_F0CAP           0x34            //Function 0 Capabilities
#define AMD_K8_nF0_IBCTL           0x3C            //Irq & Bridge Control
//
// Node routing tables
#define AMD_K8_nF0_N0_RT           0x40            //RW Node 0 routing
#define AMD_K8_nF0_N1_RT           0x44            //RW Node 1 routing
#define AMD_K8_nF0_N2_RT           0x48            //RW Node 2 routing
#define AMD_K8_nF0_N3_RT           0x4C            //RW Node 3 routing
#define AMD_K8_nF0_N4_RT           0x50            //RW Node 4 routing
#define AMD_K8_nF0_N5_RT           0x54            //RW Node 5 routing
#define AMD_K8_nF0_N6_RT           0x58            //RW Node 6 routing
#define AMD_K8_nF0_N7_RT           0x5C            //RW Node 7 routing
//
#define AMD_K8_nF0_NODE_ID         0x60            //RW Node ID
#define AMD_K8_nF0_UNIT_ID         0x64            //RW UNIT ID
#define AMD_K8_nF0_LDT_TRAN_CTL    0x68            //RW LDT Trans Ctrl
#define AMD_K8_nF0_LDT_INIT_CTL    0x6C            //RW LDT Init Ctrl
//
#define AMD_K8_nF0_LDT0_CAP        0x80            //RO LDT 0 Capability
#define AMD_K8_nF0_LDT0_CTL        0x84            //RW LDT 0 Control
#define AMD_K8_nF0_LDT0_REV        0x88            //RW LDT 0 Freq/Revision
#define AMD_K8_nF0_LDT0_FEAT       0x8C            //RO LDT 0 Features
#define AMD_K8_nF0_LDT0_BCT        0x90            //RW LDT 0 Buffer Count
#define AMD_K8_nF0_LDT0_BUSN       0x94            //RW LDT 0 Bus Numbers
#define AMD_K8_nF0_LDT0_TYPE       0x98            //RW LDT 0 Type
//
#define AMD_K8_nF0_LDT1_CAP        0xA0            //RO LDT 1 Capability
#define AMD_K8_nF0_LDT1_CTL        0xA4            //RW LDT 1 Control
#define AMD_K8_nF0_LDT1_REV        0xA8            //RW LDT 1 Freq/Revision
#define AMD_K8_nF0_LDT1_FEAT       0xAC            //RO LDT 1 Features
#define AMD_K8_nF0_LDT1_BCT        0xB0            //RW LDT 1 Buffer Count
#define AMD_K8_nF0_LDT1_BUSN       0xB4            //RW LDT 1 Bus Numbers
#define AMD_K8_nF0_LDT1_TYPE       0xB8            //RW LDT 1 Type
//
#define AMD_K8_nF0_LDT2_CAP        0xC0            //RO LDT 2 Capability
#define AMD_K8_nF0_LDT2_CTL        0xC4            //RW LDT 2 Control
#define AMD_K8_nF0_LDT2_REV        0xC8            //RW LDT 2 Freq/Revision
#define AMD_K8_nF0_LDT2_FEAT       0xCC            //RO LDT 2 Features
#define AMD_K8_nF0_LDT2_BCT        0xD0            //RW LDT 2 Buffer Count
#define AMD_K8_nF0_LDT2_BUSN       0xD4            //RW LDT 2 Bus Numbers
#define AMD_K8_nF0_LDT2_TYPE       0xD8            //RW LDT 2 Type

//-----------------------------------------------------------------------
//
//   AMD_K8 Devices 24-31 correlates to LDT nodes 0-7
//
//   Function 1  - Memory, Memory Mapped I/O, PCI IO routing.
//
//-----------------------------------------------------------------------

#define AMD_K8_nF1_VID0            0x00            //Vendor ID Register
#define AMD_K8_nF1_VID1            0x01            //Vendor ID Register
#define AMD_K8_nF1_DID0            0x02            //Device ID Register
#define AMD_K8_nF1_DID1            0x03            //Device ID Register
#define AMD_K8_nF1_PCICMD          0x04            //PCI Command Register
#define AMD_K8_nF1_PCISTS          0x06            //PCI Status Register
#define AMD_K8_nF1_RID             0x08            //Revision ID Register
#define AMD_K8_nF1_PROG            0x09            //Program Interface
#define AMD_K8_nF1_SUBC            0x0A            //Sub-Class Code Register
#define AMD_K8_nF1_BCC             0x0B            //Base Class Code Register
#define AMD_K8_nF1_RSVD1           0x0C            //Reserved by AMD
#define AMD_K8_nF1_MLT             0x0D            //Master Latency Timer Register
#define AMD_K8_nF1_HDR             0x0E            //Header Type Register
#define AMD_K8_nF1_RSVD2           0x0F            //Reserved by AMD
#define AMD_K8_nF1_BAR0            0x10            //BAR0 (AGP virtual addr space))
#define AMD_K8_nF1_BAR1            0x14            //BAR1 (GART Mem Mapp Ptr)
#define AMD_K8_nF1_BAR2            0x18            //Aperture PM2 I/O register
#define AMD_K8_nF1_IOBL            0x1C            //I/O Base and Limit      r
#define AMD_K8_nF1_SSVID           0x2C            //SSVENDORID  Dev A:70 Wr
#define AMD_K8_nF1_SSID            0x2E            //SS ID       Dev A:70 Wr
#define AMD_K8_nF1_F0CAP           0x34            //Function 0 Capabilities
#define AMD_K8_nF1_IBCTL           0x3C            //Irq & Bridge Control
//
#define AMD_K8_nF1_DRAM_B0         0x40            // Dram base and limit
#define AMD_K8_nF1_DRAM_L0         0x44            // define the memory
#define AMD_K8_nF1_DRAM_B1         0x48            // addresses available
#define AMD_K8_nF1_DRAM_L1         0x4C            // on each node.
#define AMD_K8_nF1_DRAM_B2         0x50            //
#define AMD_K8_nF1_DRAM_L2         0x54            //
#define AMD_K8_nF1_DRAM_B3         0x58            //
#define AMD_K8_nF1_DRAM_L3         0x5C            //
#define AMD_K8_nF1_DRAM_B4         0x60            //
#define AMD_K8_nF1_DRAM_L4         0x64            //
#define AMD_K8_nF1_DRAM_B5         0x68            //
#define AMD_K8_nF1_DRAM_L5         0x6C            //
#define AMD_K8_nF1_DRAM_B6         0x70            //
#define AMD_K8_nF1_DRAM_L6         0x74            //
#define AMD_K8_nF1_DRAM_B7         0x78            //
#define AMD_K8_nF1_DRAM_L7         0x7C            //
//
#define AMD_K8_nF1_MMIO_B0         0x80            // MMIO base and limit
#define AMD_K8_nF1_MMIO_L0         0x84            // define the memory
#define AMD_K8_nF1_MMIO_B1         0x88            // mapped IO address
#define AMD_K8_nF1_MMIO_L1         0x8C            // defined for each
#define AMD_K8_nF1_MMIO_B2         0x90            // node.
#define AMD_K8_nF1_MMIO_L2         0x94            //
#define AMD_K8_nF1_MMIO_B3         0x98            //
#define AMD_K8_nF1_MMIO_L3         0x9C            //
#define AMD_K8_nF1_MMIO_B4         0xA0            //
#define AMD_K8_nF1_MMIO_L4         0xA4            //
#define AMD_K8_nF1_MMIO_B5         0xA8            //
#define AMD_K8_nF1_MMIO_L5         0xAC            //
#define AMD_K8_nF1_MMIO_B6         0xB0            //
#define AMD_K8_nF1_MMIO_L6         0xB4            //
#define AMD_K8_nF1_MMIO_B7         0xB8            //
#define AMD_K8_nF1_MMIO_L7         0xBC            //
//
#define AMD_K8_nF1_PCIIO_B0        0xC0            // PCI I/O space
#define AMD_K8_nF1_PCIIO_L0        0xC4            // mapping to LDTs.
#define AMD_K8_nF1_PCIIO_B1        0xC8            //
#define AMD_K8_nF1_PCIIO_L1        0xCC            //
#define AMD_K8_nF1_PCIIO_B2        0xD0            //
#define AMD_K8_nF1_PCIIO_L2        0xD4            //
#define AMD_K8_nF1_PCIIO_B3        0xD8            //
#define AMD_K8_nF1_PCIIO_L3        0xDC            //
//
#define AMD_K8_nF1_CFGBASE0        0xE0            //  Bus mapping
#define AMD_K8_nF1_CFGBASE1        0xE4            //
#define AMD_K8_nF1_CFGBASE2        0xE8            //
#define AMD_K8_nF1_CFGBASE3        0xEC            //

#define AMD_K8_nF1_DRAM_HOLE	   0xF0
#define AMD_K8_nF1_VGA_ENABLE	   0xF4

#define AMD_K8_nF1_DRAM_BASE_SYS_ADDR  0x120   // DRAM Base System Address Register
#define AMD_K8_nF1_DRAM_LIMIT_SYS_ADDR  0x124   // DRAM Limit System Address Register

//-----------------------------------------------------------------------
//
//   AMD_K8 Devices 24-31 correlates to LDT nodes 0-7
//
//   Function 2 - Memory configuration registers
//
//-----------------------------------------------------------------------

#define AMD_K8_nF2_VID0            0x00            //Vendor ID Register
#define AMD_K8_nF2_VID1            0x01            //Vendor ID Register
#define AMD_K8_nF2_DID0            0x02            //Device ID Register
#define AMD_K8_nF2_DID1            0x03            //Device ID Register
#define AMD_K8_nF2_PCICMD          0x04            //PCI Command Register
#define AMD_K8_nF2_PCISTS          0x06            //PCI Status Register
#define AMD_K8_nF2_RID             0x08            //Revision ID Register
#define AMD_K8_nF2_PROG            0x09            //Program Interface
#define AMD_K8_nF2_SUBC            0x0A            //Sub-Class Code Register
#define AMD_K8_nF2_BCC             0x0B            //Base Class Code Register
#define AMD_K8_nF2_RSVD1           0x0C            //Reserved by AMD
#define AMD_K8_nF2_MLT             0x0D            //Master Latency Timer Register
#define AMD_K8_nF2_HDR             0x0E            //Header Type Register
#define AMD_K8_nF2_RSVD2           0x0F            //Reserved by AMD
#define AMD_K8_nF2_BAR0            0x10            //BAR0 (AGP virtual addr space))
#define AMD_K8_nF2_BAR1            0x14            //BAR1 (GART Mem Mapp Ptr)
#define AMD_K8_nF2_BAR2            0x18            //Aperture PM2 I/O register
#define AMD_K8_nF2_IOBL            0x1C            //I/O Base and Limit      r
#define AMD_K8_nF2_SSVID           0x2C            //SSVENDORID  Dev A:70 Wr
#define AMD_K8_nF2_SSID            0x2E            //SS ID       Dev A:70 Wr
#define AMD_K8_nF2_F0CAP           0x34            //Function 0 Capabilities
#define AMD_K8_nF2_IBCTL           0x3C            //Irq & Bridge Control

// Memory Controller
#define AMD_K8_nF2_CS_BASE0        0x40            // Chip Select base 0
#define AMD_K8_nF2_CS_BASE1        0x44            // Chip Select base 1
#define AMD_K8_nF2_CS_BASE2        0x48            // Chip Select base 2
#define AMD_K8_nF2_CS_BASE3        0x4C            // Chip Select base 3
#define AMD_K8_nF2_CS_BASE4        0x50            // Chip Select base 4
#define AMD_K8_nF2_CS_BASE5        0x54            // Chip Select base 5
#define AMD_K8_nF2_CS_BASE6        0x58            // Chip Select base 6
#define AMD_K8_nF2_CS_BASE7        0x5C            // Chip Select base 7
#define AMD_K8_nF2_CS_MASK0        0x60            // Chip Select mask 0
#define AMD_K8_nF2_CS_MASK1        0x64            // Chip Select mask 1
#define AMD_K8_nF2_CS_MASK2        0x68            // Chip Select mask 2
#define AMD_K8_nF2_CS_MASK3        0x6C            // Chip Select mask 3
#define AMD_K8_nF2_CS_MASK4        0x70            // Chip Select mask 4
#define AMD_K8_nF2_CS_MASK5        0x74            // Chip Select mask 5
#define AMD_K8_nF2_CS_MASK6        0x78            // Chip Select mask 6
#define AMD_K8_nF2_CS_MASK7        0x7C            // Chip Select mask 7
//
#define AMD_K8_nF2_BANK_ADRM       0x80            // Bank addressing map
#define AMD_K8_nF2_TIME_LOW        0x88            // DRAM Timing lower
#define AMD_K8_nF2_TIME_UPR        0x8C            // DRAM Timing Upper
#define AMD_K8_nF2_CFG_LOW         0x90            // DRAM Config Lower
#define AMD_K8_nF2_CFG_UPR         0x94            // DRAM Config Upper
#define AMD_K8_nF2_DELAY_LINE      0x98            // DRAM Config Upper

// Time stamping
#define AMD_K8_nF2_TSC_LOW         0xB0            // Time Stamp Lower
#define AMD_K8_nF2_TSC_UPR         0xB4            // Time Stamp Upper

// LDT tracing facility
#define AMD_K8_nF2_TRACE_BASE      0xB8            // Trace buffer base/size
#define AMD_K8_nF2_TRACE_CURR      0xBC            // Current trace location
#define AMD_K8_nF2_TRACE_CTRL      0xC0            // Trace control
#define AMD_K8_nF2_TRACE_START     0xC4            // Trace START
#define AMD_K8_nF2_TRACE_STOP      0xC8            // Trace STOP
#define AMD_K8_nF2_TRACE_CAPT      0xCC            // Trace CAPTURE
#define AMD_K8_nF2_TRIG0_CMDL      0xD0            // Trace COMMAND LOW
#define AMD_K8_nF2_TRIG0_CMDH      0xD4            // Trace COMMAND HIGH
#define AMD_K8_nF2_TRIG0_MSKL      0xD8            // Trace MASK LOW
#define AMD_K8_nF2_TRIG0_MSKH      0xDC            // Trace MASK HIGH

//-----------------------------------------------------------------------
//
//   AMD_K8 Devices 24-31 correlates to LDT nodes 0-7
//
//   Function 3 - Miscellaneous  Control
//
//-----------------------------------------------------------------------

#define AMD_K8_nF3_VID0            0x00            //Vendor ID Register
#define AMD_K8_nF3_VID1            0x01            //Vendor ID Register
#define AMD_K8_nF3_DID0            0x02            //Device ID Register
#define AMD_K8_nF3_DID1            0x03            //Device ID Register
#define AMD_K8_nF3_PCICMD          0x04            //PCI Command Register
#define AMD_K8_nF3_PCISTS          0x06            //PCI Status Register
#define AMD_K8_nF3_RID             0x08            //Revision ID Register
#define AMD_K8_nF3_PROG            0x09            //Program Interface
#define AMD_K8_nF3_SUBC            0x0A            //Sub-Class Code Register
#define AMD_K8_nF3_BCC             0x0B            //Base Class Code Register
#define AMD_K8_nF3_RSVD1           0x0C            //Reserved by AMD
#define AMD_K8_nF3_MLT             0x0D            //Master Latency Timer Register
#define AMD_K8_nF3_HDR             0x0E            //Header Type Register
#define AMD_K8_nF3_RSVD2           0x0F            //Reserved by AMD
#define AMD_K8_nF3_BAR0            0x10            //BAR0 (AGP virtual addr space))
#define AMD_K8_nF3_BAR1            0x14            //BAR1 (GART Mem Mapp Ptr)
#define AMD_K8_nF3_BAR2            0x18            //Aperture PM2 I/O register
#define AMD_K8_nF3_IOBL            0x1C            //I/O Base and Limit      r
#define AMD_K8_nF3_SSVID           0x2C            //SSVENDORID  Dev A:70 Wr
#define AMD_K8_nF3_SSID            0x2E            //SS ID       Dev A:70 Wr
#define AMD_K8_nF3_F0CAP           0x34            //Function 0 Capabilities
#define AMD_K8_nF3_IBCTL           0x3C            //Irq & Bridge Control

// Miscellaneous  Controls
#define AMD_K8_nF3_MCA_NBCTL       0x40            // Machine Check NB control
#define AMD_K8_nF3_MCA_NBCFG       0x44            // Machine Check NB config
#define AMD_K8_nF3_MCA_STATL       0x48            // MC Status Low
#define AMD_K8_nF3_MCA_STATH       0x4C            // MC Status High
#define AMD_K8_nF3_MCA_ADDRL       0x50            // MC Address Low
#define AMD_K8_nF3_MCA_ADDRH       0x54            // MC Address High
#define AMD_K8_nF3_SCRUB_CTL       0x58            // ECC Scrub control
#define AMD_K8_nF3_SCRUB_ADL       0x5C            // DRAM Scrub address low
#define AMD_K8_nF3_SCRUB_ADH       0x60            // DRAM Scrub address high
#define AMD_K8_nF3_HTC_CTRL	   	   0x64		   	   // Hardware Thermal control
#define AMD_K8_nF3_STC_CTRL	   	   0x68		   	   // Hardware Thermal control
#define AMD_K8_nF3_SRI_2_XBAR      0x70            // Buffer count
#define AMD_K8_nF3_XBAR_2_SRI      0x74            // Buffer count
#define AMD_K8_nF3_MCT_2_XBAR      0x78            // Buffer count
#define AMD_K8_nF3_FREE_BCT        0x7C            // Free list count
#define AMD_K8_nF3_PM_CTL_LOW      0x80            // Power Mgmt Control Low
#define AMD_K8_nF3_PM_CTL_HIGH     0x84            // Power Mgmt Control High
#define AMD_K8_nF3_NB_CFG_LOW      0x88            // North Bridge Config Low
#define AMD_K8_nF3_NB_CFG_HIGH     0x8C            // North Bridge Config High
#define AMD_K8_nF3_AGP_APERTURE    0x90            // GART size/enable
#define AMD_K8_nF3_AGP_GART_APB    0x94            // GART Base address
#define AMD_K8_nF3_AGP_GART_TBL    0x98            // GART table base
#define AMD_K8_nF3_AGP_GART_CACHE  0x9C            // GART cache control
#define AMD_K8_nF3_PWR_CTRL_MISC   0xA0            // Power Control Miscellaneous
#define AMD_K8_nF3_SBI_PSTATE_LIMIT_REG  0xC4	   // Side band interface pstate register
#define AMD_K8_nF3_CLK_PWR_LOW     0xD4            // Clock Power Timing Low
#define AMD_K8_nF3_CLK_PWR_HIGH    0xD8            // Clock Power Timing High
#define AMD_K8_nF3_HT_PTR_OPT_REG  0xDC	           // HyperTransport FIFO Read Pointer
#define AMD_K8_nF3_NB_CAP          0xE8            // NORTH BRIDGE capability


#define K8_REV_LOC_FUNC 			2
#define K8_REV_LOC_OFFSET 			0x9C

#define AMD_K8_nF2_DRAM_CTRL_SELECT_LOW  	   0x110   // DRAM Controller Select Low 				
#define AMD_K8_nF2_DRAM_CTRL	  	   0x78		   // DRAM Control Register
#define AMD_K8_nF2_DRAM_INIT	   	   0x7C		   // DRAM Initialization Register 
#define AMD_K8_nF2_DRAM_CTRL_MISC  	   0xA0		   // DRAM Controller Miscellaneous Register 	
#define AMD_K8_nF2_DRAM_MRS            0x84            // DRAM MRS			
#define AMD_K8_nF2_DRAM_CTRL_SELECT_HIGH  	   0x114    //DRAM Controller Select High
#define AMD_K8_nF2_DRAM_CTRL_CONFIG_LOW  	   0x118    //DRAM Controller Config Low 				
#define AMD_K8_nF2_DRAM_CTRL_CONFIG_HIGH  	   0x11C   // DRAM Controller Config High

//NB MSR
#define AMD_DH_NB_CONFIG_MSR	0xC001001F  //NB Config MSR
//#define EnableCf8ExtCfg 1 << 46				//Extended config space Enable Value
#define         EnableCf8ExtCfg         0x0000400000000000   // [46]
#define AMD_K8_nF2_DRAM_ADD_DATA_OFFSET 	0x98
#define AMD_K8_nF2_DRAM_ADD_DATA_PORT	    0x9c
#define	AMD_K8_nF2_DRAM_CTRL_TEMP_THTL  	   0xA4		  // DRAM Controller Miscellaneous Register 				
#define	AMD_K8_nF2_DRAM_CTRL_MISC2  	   0xA8		   // DRAM Controller Miscellaneous Register 2				
#define AMD_K8_nF2_DRAM_XCTRL_CONFIG_LOW  	   0x1B0   // Extended Memory Controller Configuration Low Register

#define DRAM_PHY_CONTROL_ADDL_REG		0x08
//Required DCT1 register declaration in Extended Config Space
#define	AMD_K8_nF2_CFG_UPR_DCT1	AMD_K8_nF2_CFG_UPR + 0x100

#define S3_MEM_TEST_SIZE 0x10
#endif

#define ONE_KB_SIZE         0x400
#define ONE_MB_SIZE 0x100000


//-----------------------------------------------------------------------
//
//   AMD Family 17h Processor Programming Reference(PPR) Data Fabric 7.15.1
//
//   D18F0 Registers 
//
//-----------------------------------------------------------------------


#define AMD_D18_F0_C0   0xC0    //IO Space Base Address
#define AMD_D18_F0_C4   0xC4    //IO Space Limit Address

#define AMD_D18_F0_A0   0xA0    //Configuration Address Maps

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
