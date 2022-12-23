//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file
  This file contains PPI definitions that are defined in the CSP Library
*/

#ifndef __CSP_LIB_PPI_H__
#define __CSP_LIB_PPI_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <Pei.h>
/*
//
//============================================================================
//
// Name:        AMI_PEI_PCI_TABLE_INIT_PPI_GUID
//
// Description: 
//  This is the GUID to use to locate the the instance of the
//  AMI_PEI_PCI_TABLE_INIT_PPI
//
// Notes:
//  #define AMI_PEI_PCI_TABLE_INIT_PPI_GUID \
//      { 0x97f91e78, 0xea12, 0x4ea6, 0xb7, 0xb3, 0x7b, 0x6, 0x78, 0xc2, 0x86, 0x73 }
//
//============================================================================
//*/
#define AMI_PEI_PCI_TABLE_INIT_PPI_GUID \
{   0x97f91e78, 0xea12, 0x4ea6, {0xb7, 0xb3, 0x7b, 0x6, 0x78, 0xc2, 0x86, 0x73 }}

GUID_VARIABLE_DECLARATION(gPeiPciTableInitPpiGuid,AMI_PEI_PCI_TABLE_INIT_PPI_GUID);
GUID_VARIABLE_DECLARATION(gAmiPeiPciTableInitPpiGuid,AMI_PEI_PCI_TABLE_INIT_PPI_GUID);

#ifndef GUID_VARIABLE_DEFINITION

typedef struct  _AMI_PEI_PCI_TABLE_INIT_PPI     AMI_PEI_PCI_TABLE_INIT_PPI;

/*
//
//------------------------------------------------------------------
//
// Name:        AMI_PEI_PCI_INIT_TABLE_STRUCT
//
// Fields:      Type    ParameterName    Description
//------------------------------------------------------------------
//  UINT8 bRegIndex - PCI Register to program
//  UINT8 bANDMask - AND mask to apply to data in PCI register
//  UINT8 bORMask - OR mask to apply to data in PCI register after AND mask
//
// Description: 
//  This data structure contains the information that is used to 
//  modify PCI register of a PCI specific device
//  
//
// Notes:   
//  Only can modify a one byte register at a time.  
//  See AMI_PEI_PCI_INIT_TABLE_STRUCT2 to modify lager register
//  at once
//      
//------------------------------------------------------------------
//*/
typedef struct _AMI_PEI_PCI_INIT_TABLE_STRUCT
{
    UINT8       bRegIndex;
    UINT8       bANDMask;
    UINT8       bORMask;
}   AMI_PEI_PCI_INIT_TABLE_STRUCT;

/*
//
//------------------------------------------------------------------
//
// Name:        AMI_PEI_PCI_INIT_TABLE_STRUCT2
//
// Fields:      Type    ParameterName    Description
//------------------------------------------------------------------
//  UINT8 bRegIndex - PCI Register to program
//  UINTN bANDMask - AND mask to apply to data in PCI register
//  UINTN bORMask - OR mask to apply to data in PCI register after AND mask
//
// Description: 
//  This data structure contains the information that is used to 
//  modify PCI register of a PCI specific device
//  
//
// Notes:
//  This Structure is almost the same as AMI_PEI_PCI_INIT_TABLE_STRUCT
//  The difference is in the size of the AND and OR masks. to allow
//  modification of PCI registers larger than one byte
//      
//------------------------------------------------------------------
//*/
typedef struct 
{
    UINT8       bRegIndex;          // register offset to modify
    UINTN       bANDMask;           // specified bits will be cleared
    UINTN       bORMask;            // specified bits will be set
} AMI_PEI_PCI_INIT_TABLE_STRUCT2;

typedef
EFI_STATUS
(EFIAPI * AMI_PEI_PCI_TABLE_INIT_FUNCTION) (
    IN          EFI_PEI_SERVICES                **PeiServices,
    IN          AMI_PEI_PCI_TABLE_INIT_PPI      *This,
    IN          EFI_PEI_PCI_CFG2_PPI             *PciCfg,        // OPTIONAL
    IN          UINT64                          Address,
    IN          AMI_PEI_PCI_INIT_TABLE_STRUCT   PCIInitTable[],
    IN          UINT16                          wSize
    );

// This version allows a table of specified access width up to UINTN
typedef
EFI_STATUS
(EFIAPI * AMI_PEI_PCI_TABLE_INIT_FUNCTION_VARACCESS) (
    IN          EFI_PEI_SERVICES                **PeiServices,
    IN          AMI_PEI_PCI_TABLE_INIT_PPI      *This,
    IN          EFI_PEI_PCI_CFG2_PPI             *PciCfg,        // OPTIONAL
    IN          UINT64                          CfgAddress,
    IN          AMI_PEI_PCI_INIT_TABLE_STRUCT2  *PciInitTable,
    IN          UINT16                          TableEntries,
    IN          EFI_PEI_PCI_CFG_PPI_WIDTH       AccessWidth
);

/*
//
//------------------------------------------------------------------
//
// Name:        AMI_PEI_PCI_TABLE_INIT_PPI
//
// Description: 
//  This data structure is the AMI_PEI_PCI_TABLE_INIT_PPI definition 
//  This provides this PPI to any module that includes the chipset 
//  library.  This provides a mechanism to program a table full of
//  PCI information in one function call
//  
// Fields:      Type    ParameterName    Description
//------------------------------------------------------------------
//  AMI_PEI_PCI_TABLE_INIT_FUNCTION AMIPEIProgramPCITable - PciTableInit
//  AMI_PEI_PCI_TABLE_INIT_FUNCTION_VARACCESS ProgramPciTable - PciTableInit2
//
// Notes:
//  See the function headers for descriptions
//
//------------------------------------------------------------------
//*/
 
struct _AMI_PEI_PCI_TABLE_INIT_PPI
{
    AMI_PEI_PCI_TABLE_INIT_FUNCTION             AMIPEIProgramPCITable;
    AMI_PEI_PCI_TABLE_INIT_FUNCTION_VARACCESS   ProgramPciTable;
};


/****** DO NOT WRITE BELOW THIS LINE *******/
#endif // #ifndef GUID_VARIABLE_DEFINITION
#ifdef __cplusplus
}
#endif

#endif
