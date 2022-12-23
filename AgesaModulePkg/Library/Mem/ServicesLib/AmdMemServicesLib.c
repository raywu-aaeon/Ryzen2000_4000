/* $NoKeywords:$ */
/**
 * @file
 *
 * AmdMemServicesLib.c
 *
 * Sub-engine to extract CAD bus settings from recommended table
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Ps)
 * @e \$Revision: 311790 $ @e \$Date: 2015-01-26 23:03:49 -0600 (Mon, 26 Jan 2015) $
 *
 **/
/*****************************************************************************
*
* Copyright 2008 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
*
* AMD is granting you permission to use this software and documentation (if
* any) (collectively, the "Materials") pursuant to the terms and conditions of
* the Software License Agreement included with the Materials.  If you do not
* have a copy of the Software License Agreement, contact your AMD
* representative for a copy.
*
* You agree that you will not reverse engineer or decompile the Materials, in
* whole or in part, except as allowed by applicable law.
*
* WARRANTY DISCLAIMER:  THE MATERIALS ARE PROVIDED "AS IS" WITHOUT WARRANTY OF
* ANY KIND.  AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY,
* INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT, THAT THE
* MATERIALS WILL RUN UNINTERRUPTED OR ERROR-FREE OR WARRANTIES ARISING FROM
* CUSTOM OF TRADE OR COURSE OF USAGE.  THE ENTIRE RISK ASSOCIATED WITH THE USE
* OF THE MATERIAL IS ASSUMED BY YOU.  Some jurisdictions do not allow the
* exclusion of implied warranties, so the above exclusion may not apply to
* You.
*
* LIMITATION OF LIABILITY AND INDEMNIFICATION:  AMD AND ITS LICENSORS WILL
* NOT, UNDER ANY CIRCUMSTANCES BE LIABLE TO YOU FOR ANY PUNITIVE, DIRECT,
* INCIDENTAL, INDIRECT, SPECIAL OR CONSEQUENTIAL DAMAGES ARISING FROM USE OF
* THE MATERIALS OR THIS AGREEMENT EVEN IF AMD AND ITS LICENSORS HAVE BEEN
* ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  In no event shall AMD's total
* liability to You for all damages, losses, and causes of action (whether in
* contract, tort (including negligence) or otherwise) exceed the amount of
* $100 USD. You agree to defend, indemnify and hold harmless AMD and its
* licensors, and any of their directors, officers, employees, affiliates or
* agents from and against any and all loss, damage, liability and other
* expenses (including reasonable attorneys' fees), resulting from Your use of
* the Materials or violation of the terms and conditions of this Agreement.
*
* U.S. GOVERNMENT RESTRICTED RIGHTS:  The Materials are provided with
* "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
* subject to the restrictions as set forth in FAR 52.227-14 and
* DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
* Government constitutes acknowledgment of AMD's proprietary rights in them.
*
* EXPORT RESTRICTIONS: The Materials may be subject to export restrictions as
* stated in the Software License Agreement.
*******************************************************************************
*
*/
/*
 *----------------------------------------------------------------------------
 *                                MODULES USED
 *
 *----------------------------------------------------------------------------
 */



#include "PiPei.h"
#include "Library/BaseMemoryLib.h"
#include "Library/BaseLib.h"
#include "Ppi/AmdMemPpi.h"
#include "Library/Mem/BaseLib/AmdMemBaseLib.h"
#include "Library/AmdBaseLib.h"
#include "Filecode.h"

#define FILECODE LIBRARY_MEM_SERVICESLIB_AMDMEMSERVICESLIB_FILECODE

/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                           TYPEDEFS AND STRUCTURES
 *
 *----------------------------------------------------------------------------
 */
/*----------------------------------------------------------------------------
 *                        PROTOTYPES OF LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
/**
  Read Service for the Memory Above 4GB

  Parameters:
  PeiServices
    A pointer to the PEI services
  AmountOfMemory
    Return data pointer for the amount of memory

  Status Codes Returned:
  EFI_SUCCESS           - Return value is valid
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
EFI_STATUS
AmdGetMemoryAbove4gbService (
  IN       EFI_PEI_SERVICES  **PeiServices,
     OUT   UINT32            *AmountOfMemory
  )
{
  PEI_MEMORY_FAMILY_SERVICE_PPI *AmdFamilyServicesPtr;
  EFI_STATUS Status;
  Status = (*PeiServices)->LocatePpi (PeiServices,
                                      &gAmdMemoryFamilyServicesPpiGuid,
                                      0,
                                      NULL,
                                      &AmdFamilyServicesPtr);
  if (EFI_SUCCESS != Status) {
    return Status;
  }
  Status = AmdFamilyServicesPtr->AmdGetMemoryAbove4gbFamilyService (PeiServices, AmountOfMemory);
  return EFI_SUCCESS;
}
/**
  Read Service for the Memory Below 4GB

  Parameters:
  PeiServices
    A pointer to the PEI services
  AmountOfMemory
    Return data pointer for the amount of memory

  Status Codes Returned:
  EFI_SUCCESS           - Return value is valid
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
EFI_STATUS
AmdGetMemoryBelow4gbService (
  IN       EFI_PEI_SERVICES  **PeiServices,
     OUT   UINT32            *AmountOfMemory
  )
{
  PEI_MEMORY_FAMILY_SERVICE_PPI *AmdFamilyServicesPtr;
  EFI_STATUS Status;
  Status = (*PeiServices)->LocatePpi (PeiServices,
                                      &gAmdMemoryFamilyServicesPpiGuid,
                                      0,
                                      NULL,
                                      &AmdFamilyServicesPtr);
  if (EFI_SUCCESS != Status) {
    return Status;
  }
  Status = AmdFamilyServicesPtr->AmdGetMemoryBelow4gbFamilyService (PeiServices, AmountOfMemory);
  return EFI_SUCCESS;
}
/**
  Read Service for the memory Below 1TB

  Parameters:
  PeiServices
    A pointer to the PEI services
  AmountOfMemory
    Return data pointer for the amount of memory

  Status Codes Returned:
  EFI_SUCCESS           - Return value is valid
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
EFI_STATUS
AmdGetMemoryBelow1TbService (
  IN       EFI_PEI_SERVICES  **PeiServices,
     OUT   UINT32            *AmountOfMemory
  )
{
  PEI_MEMORY_FAMILY_SERVICE_PPI *AmdFamilyServicesPtr;
  EFI_STATUS Status;
  Status = (*PeiServices)->LocatePpi (PeiServices,
                                      &gAmdMemoryFamilyServicesPpiGuid,
                                      0,
                                      NULL,
                                      &AmdFamilyServicesPtr);
  if (EFI_SUCCESS != Status) {
    return Status;
  }
  Status = AmdFamilyServicesPtr->AmdGetMemoryBelow1TbFamilyService (PeiServices, AmountOfMemory);
  return EFI_SUCCESS;
}
/**
  Read Service for the Bottom of MMIO

  Parameters:
  PeiServices
    A pointer to the PEI services
  AmountOfMemory
    Return data pointer for the amount of memory

  Status Codes Returned:
  EFI_SUCCESS           - Return value is valid
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
EFI_STATUS
AmdGetBottomIoService (
  IN       EFI_PEI_SERVICES  **PeiServices,
     OUT   UINT32            *AmountOfMemory
  )
{
  PEI_MEMORY_FAMILY_SERVICE_PPI *AmdFamilyServicesPtr;
  EFI_STATUS Status;
  Status = (*PeiServices)->LocatePpi (PeiServices,
                                      &gAmdMemoryFamilyServicesPpiGuid,
                                      0,
                                      NULL,
                                      &AmdFamilyServicesPtr);
  if (EFI_SUCCESS != Status) {
    return Status;
  }
  Status = AmdFamilyServicesPtr->AmdGetBottomIo1TbFamilyService (PeiServices, AmountOfMemory);
  return EFI_SUCCESS;
}
/**
  Read Service for the total amount of memory in the system

  Parameters:
  PeiServices
    A pointer to the PEI services
  AmountOfMemory
    Return data pointer for the amount of memory

  Status Codes Returned:
  EFI_SUCCESS           - Return value is valid
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
EFI_STATUS
AmdGetTotalMemorySizeService (
  IN       EFI_PEI_SERVICES  **PeiServices,
     OUT   UINT32            *AmountOfMemory
  )
{
  PEI_MEMORY_FAMILY_SERVICE_PPI *AmdFamilyServicesPtr;
  EFI_STATUS Status;
  Status = (*PeiServices)->LocatePpi (PeiServices,
                                      &gAmdMemoryFamilyServicesPpiGuid,
                                      0,
                                      NULL,
                                      &AmdFamilyServicesPtr);
  if (EFI_SUCCESS != Status) {
    return Status;
  }
  Status = AmdFamilyServicesPtr->AmdGetTotalMemorySize4gbFamilyService (PeiServices, AmountOfMemory);
  return EFI_SUCCESS;
}
/**
  Read Service for the Memory Frequency of a channel

  Parameters:
  PeiServices
    A pointer to the PEI services
    Channel
       A pointer to the channel to read
  Frequency
      Return data pointer for a channel frequency

  Status Codes Returned:
  EFI_SUCCESS           - Return value is valid
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
EFI_STATUS
AmdGetMemoryFrequencyService (
  IN       EFI_PEI_SERVICES  **PeiServices,
     OUT   UINT32            Channel,
     OUT   UINT32            *Frequency
  )
{
  return EFI_SUCCESS;
}
/**
  Read Service for the Memory Frequency of a channel

  Parameters:
  PeiServices
    A pointer to the PEI services
   UmaInfo
      Return data pointer for the UmaInfo

  Status Codes Returned:
  EFI_SUCCESS           - Return value is valid
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
EFI_STATUS
AmdGetUmaInfoService (
  IN       EFI_PEI_SERVICES  **PeiServices,
     OUT   UINT32            *UmaInfo
  )
{
  return EFI_SUCCESS;
}

