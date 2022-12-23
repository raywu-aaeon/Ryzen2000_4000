//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file SmmHddSecurity.h
    This file contains the Includes, Definitions, typedefs,
    Variable and External Declarations, Structure and
    function prototypes needed for the IDESMM Component

**/

#ifndef _HDD_SECURITY_SMM_H_
#define _HDD_SECURITY_SMM_H_

#include <Token.h>
#include <HddSecurityCommon.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/LockBoxLib.h>
#include <Library/PciLib.h>
#include <Library/TimerLib.h>
#include <Library/AmiBufferValidationLib.h>
#include <Library/S3BootScriptLib.h>
#include <Library/SmmConfidentialMemLib.h>
#include <Library/IoLib.h>
#include <Protocol/SmmBase2.h>
#include <Protocol/SmmSwDispatch2.h>
#if (defined(AHCI_SUPPORT) && (AHCI_SUPPORT == 1))
#ifndef DLINK
typedef struct _AMI_LINK DLINK;
typedef struct _AMI_LIST DLIST;
#endif
#include <Protocol/AhciSmmProtocol.h>
#include <AhciController.h>
#endif
#if (defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0))
#include <Nvme/NvmeController.h>
#include <Protocol/AmiNvmeController.h>
#include <Protocol/AmiNvmePassThru.h>
#endif

#define COMMAND_LIST_SIZE_PORT                      0x800

#ifndef DMA_ATAPI_COMMAND_COMPLETE_TIMEOUT
#define DMA_ATAPI_COMMAND_COMPLETE_TIMEOUT          30000           // 30Sec
#endif

#ifndef S3_BUSY_CLEAR_TIMEOUT
#define S3_BUSY_CLEAR_TIMEOUT                       30000           // 30Sec
#endif

#ifndef BUSY_CLEAR_TIMEOUT
#define BUSY_CLEAR_TIMEOUT                          1000            // 1Sec
#endif

#ifndef DRDY_TIMEOUT
#define DRDY_TIMEOUT                                1000            // 1Sec
#endif

#ifndef DRQ_TIMEOUT
#define DRQ_TIMEOUT                                 10              // 10msec
#endif

#ifndef HBA_CAP
#define HBA_CAP                                     0x0000
#endif

#ifndef HBA_CAP_NP_MASK
#define HBA_CAP_NP_MASK                             0x1F
#endif

#ifndef HBA_PORTS_START
#define HBA_PORTS_START                             0x0100
#endif

#ifndef HBA_PORTS_REG_WIDTH
#define HBA_PORTS_REG_WIDTH                         0x0080
#endif

#define AHCI_BAR                                    0x24
#define PCI_SCC                                     0x000A        // Sub Class Code Register
#endif  


