/* $NoKeywords:$ */
/**
 * @file
 *
 * ACPI S3 Support routines
 *
 * Contains routines needed for supporting resume from the ACPI S3 sleep state.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Interface
 * @e \$Revision: 319661 $   @e \$Date: 2015-05-31 18:47:12 +0800 (Sun, 31 May 2015) $
 *
 */
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
 */


/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include "AGESA.h"
#include "Library/AmdBaseLib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "mm.h"
#include "mn.h"
#include "S3.h"
#include "Library/AmdMemFeatS3Lib.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_NULL_MAINLIBNULL_S3_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
VOID
SaveDeviceContext (
  IN       DEVICE_BLOCK_HEADER *DeviceList,
  IN       CALL_POINTS         CallPoint,
     OUT   UINT32              *ActualBufferSize,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  );

VOID
SavePciDevice (
  IN       AMD_CONFIG_PARAMS     *StdHeader,
  IN       PCI_DEVICE_DESCRIPTOR *Device,
  IN       CALL_POINTS           CallPoint,
  IN OUT   VOID                  **OrMask
  );

VOID
SaveConditionalPciDevice (
  IN       AMD_CONFIG_PARAMS                 *StdHeader,
  IN       CONDITIONAL_PCI_DEVICE_DESCRIPTOR *Device,
  IN       CALL_POINTS                       CallPoint,
  IN OUT   VOID                              **OrMask
  );

VOID
SaveMsrDevice (
  IN       AMD_CONFIG_PARAMS     *StdHeader,
  IN       MSR_DEVICE_DESCRIPTOR *Device,
  IN       CALL_POINTS           CallPoint,
  IN OUT   UINT64                **OrMask
  );

VOID
SaveConditionalMsrDevice (
  IN       AMD_CONFIG_PARAMS                 *StdHeader,
  IN       CONDITIONAL_MSR_DEVICE_DESCRIPTOR *Device,
  IN       CALL_POINTS                       CallPoint,
  IN OUT   UINT64                            **OrMask
  );

VOID
RestorePciDevice (
  IN       AMD_CONFIG_PARAMS     *StdHeader,
  IN       PCI_DEVICE_DESCRIPTOR *Device,
  IN       CALL_POINTS           CallPoint,
  IN OUT   VOID                  **OrMask
  );

VOID
RestoreConditionalPciDevice (
  IN       AMD_CONFIG_PARAMS                 *StdHeader,
  IN       CONDITIONAL_PCI_DEVICE_DESCRIPTOR *Device,
  IN       CALL_POINTS                       CallPoint,
  IN OUT   VOID                              **OrMask
  );

VOID
RestoreMsrDevice (
  IN       AMD_CONFIG_PARAMS     *StdHeader,
  IN       MSR_DEVICE_DESCRIPTOR *Device,
  IN       CALL_POINTS           CallPoint,
  IN OUT   UINT64                **OrMask
  );

VOID
RestoreConditionalMsrDevice (
  IN       AMD_CONFIG_PARAMS                 *StdHeader,
  IN       CONDITIONAL_MSR_DEVICE_DESCRIPTOR *Device,
  IN       CALL_POINTS                       CallPoint,
  IN OUT   UINT64                            **OrMask
  );

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*---------------------------------------------------------------------------------------*/
/**
 * Saves all devices in the given device list.
 *
 * This traverses the entire device list twice.  In the first pass, we save
 * all devices identified as Pre ESR.  In the second pass, we save devices
 * marked as post ESR.
 *
 * @param[in]     DeviceList        Beginning of the device list to save.
 * @param[in]     Storage           Beginning of the context buffer.
 * @param[in]     CallPoint         Indicates whether this is AMD_INIT_RESUME or
 *                                  AMD_S3LATE_RESTORE.
 * @param[out]    ActualBufferSize  Actual size used in saving the device list.
 * @param[in]     StdHeader         AMD standard header config param.
 *
 */
VOID
SaveDeviceListContext (
  IN       DEVICE_BLOCK_HEADER *DeviceList,
  IN       VOID                *Storage,
  IN       CALL_POINTS         CallPoint,
     OUT   UINT32              *ActualBufferSize,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
}

/*---------------------------------------------------------------------------------------*/
/**
 * Saves all devices in the given device list.
 *
 * This traverses the entire device list twice.  In the first pass, we save
 * all devices identified as Pre ESR.  In the second pass, we save devices
 * marked as post ESR.
 *
 * @param[in,out] DeviceList        Beginning of the device list to save.
 * @param[in]     CallPoint         Indicates whether this is AMD_INIT_RESUME or
 *                                  AMD_S3LATE_RESTORE.
 * @param[out]    ActualBufferSize  Actual size used in saving the device list.
 * @param[in]     StdHeader         AMD standard header config param.
 *
 */
VOID
SaveDeviceContext (
  IN       DEVICE_BLOCK_HEADER *DeviceList,
  IN       CALL_POINTS         CallPoint,
     OUT   UINT32              *ActualBufferSize,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{

}

/*---------------------------------------------------------------------------------------*/
/**
 * Saves the context of a PCI device.
 *
 * This traverses the provided register list saving PCI registers.
 *
 * @param[in]     StdHeader      AMD standard header config param.
 * @param[in]     Device         PCI device to restore.
 * @param[in]     CallPoint      Indicates whether this is AMD_INIT_RESUME or
 *                               AMD_S3LATE_RESTORE.
 * @param[in,out] OrMask         Current buffer pointer of raw register values.
 *
 */
VOID
SavePciDevice (
  IN       AMD_CONFIG_PARAMS     *StdHeader,
  IN       PCI_DEVICE_DESCRIPTOR *Device,
  IN       CALL_POINTS           CallPoint,
  IN OUT   VOID                  **OrMask
  )
{

}

/*---------------------------------------------------------------------------------------*/
/**
 * Saves the context of a 'conditional' PCI device.
 *
 * This traverses the provided register list saving PCI registers when appropriate.
 *
 * @param[in]     StdHeader      AMD standard header config param.
 * @param[in]     Device         'conditional' PCI device to restore.
 * @param[in]     CallPoint      Indicates whether this is AMD_INIT_RESUME or
 *                               AMD_S3LATE_RESTORE.
 * @param[in,out] OrMask         Current buffer pointer of raw register values.
 *
 */
VOID
SaveConditionalPciDevice (
  IN       AMD_CONFIG_PARAMS                 *StdHeader,
  IN       CONDITIONAL_PCI_DEVICE_DESCRIPTOR *Device,
  IN       CALL_POINTS                       CallPoint,
  IN OUT   VOID                              **OrMask
  )
{

}

/*---------------------------------------------------------------------------------------*/
/**
 * Saves the context of an MSR device.
 *
 * This traverses the provided register list saving MSRs.
 *
 * @param[in]     StdHeader      AMD standard header config param.
 * @param[in]     Device         MSR device to restore.
 * @param[in]     CallPoint      Indicates whether this is AMD_INIT_RESUME or
 *                               AMD_S3LATE_RESTORE.
 * @param[in,out] OrMask         Current buffer pointer of raw register values.
 *
 */
VOID
SaveMsrDevice (
  IN       AMD_CONFIG_PARAMS     *StdHeader,
  IN       MSR_DEVICE_DESCRIPTOR *Device,
  IN       CALL_POINTS           CallPoint,
  IN OUT   UINT64                **OrMask
  )
{

}

/*---------------------------------------------------------------------------------------*/
/**
 * Saves the context of a 'conditional' MSR device.
 *
 * This traverses the provided register list saving MSRs when appropriate.
 *
 * @param[in]     StdHeader      AMD standard header config param.
 * @param[in]     Device         'conditional' MSR device to restore.
 * @param[in]     CallPoint      Indicates whether this is AMD_INIT_RESUME or
 *                               AMD_S3LATE_RESTORE.
 * @param[in,out] OrMask         Current buffer pointer of raw register values.
 *
 */
VOID
SaveConditionalMsrDevice (
  IN       AMD_CONFIG_PARAMS                 *StdHeader,
  IN       CONDITIONAL_MSR_DEVICE_DESCRIPTOR *Device,
  IN       CALL_POINTS                       CallPoint,
  IN OUT   UINT64                            **OrMask
  )
{

}

/*---------------------------------------------------------------------------------------*/
/**
 * Determines the maximum amount of space required to store all raw register
 * values for the given device list.
 *
 * This traverses the entire device list, and calculates the worst case size
 * of each device in the device list.
 *
 * @param[in]     DeviceList     Beginning of the device list.
 * @param[in]     CallPoint      Indicates whether this is AMD_INIT_RESUME or
 *                               AMD_S3LATE_RESTORE.
 * @param[in]     StdHeader      AMD standard header config param.
 *
 * @retval        Size in bytes required for storing all registers.
 */
UINT32
GetWorstCaseContextSize (
  IN       DEVICE_BLOCK_HEADER *DeviceList,
  IN       CALL_POINTS         CallPoint,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  return (0);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Restores all devices marked as 'before exiting self-refresh.'
 *
 * This traverses the entire device list, restoring all devices identified
 * as Pre ESR.
 *
 * @param[in,out] OrMaskPtr      Current buffer pointer of raw register values.
 * @param[in]     Storage        Beginning of the device list.
 * @param[in]     CallPoint      Indicates whether this is AMD_INIT_RESUME or
 *                               AMD_S3LATE_RESTORE.
 * @param[in]     StdHeader      AMD standard header config param.
 *
 */
VOID
RestorePreESRContext (
     OUT   VOID              **OrMaskPtr,
  IN       VOID              *Storage,
  IN       CALL_POINTS       CallPoint,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{

}

/*---------------------------------------------------------------------------------------*/
/**
 * Restores all devices marked as 'after exiting self-refresh.'
 *
 * This traverses the entire device list, restoring all devices identified
 * as Post ESR.
 *
 * @param[in]     OrMaskPtr      Current buffer pointer of raw register values.
 * @param[in]     Storage        Beginning of the device list.
 * @param[in]     CallPoint      Indicates whether this is AMD_INIT_RESUME or
 *                               AMD_S3LATE_RESTORE.
 * @param[in]     StdHeader      AMD standard header config param.
 *
 */
VOID
RestorePostESRContext (
  IN       VOID              *OrMaskPtr,
  IN       VOID              *Storage,
  IN       CALL_POINTS       CallPoint,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{

}

/*---------------------------------------------------------------------------------------*/
/**
 * Restores the context of a PCI device.
 *
 * This traverses the provided register list restoring PCI registers.
 *
 * @param[in]     StdHeader      AMD standard header config param.
 * @param[in]     Device         'conditional' PCI device to restore.
 * @param[in]     CallPoint      Indicates whether this is AMD_INIT_RESUME or
 *                               AMD_S3LATE_RESTORE.
 * @param[in,out] OrMask         Current buffer pointer of raw register values.
 *
 */
VOID
RestorePciDevice (
  IN       AMD_CONFIG_PARAMS     *StdHeader,
  IN       PCI_DEVICE_DESCRIPTOR *Device,
  IN       CALL_POINTS           CallPoint,
  IN OUT   VOID                  **OrMask
  )
{

}

/*---------------------------------------------------------------------------------------*/
/**
 * Restores the context of a 'conditional' PCI device.
 *
 * This traverses the provided register list restoring PCI registers when appropriate.
 *
 * @param[in]     StdHeader      AMD standard header config param.
 * @param[in]     Device         'conditional' PCI device to restore.
 * @param[in]     CallPoint      Indicates whether this is AMD_INIT_RESUME or
 *                               AMD_S3LATE_RESTORE.
 * @param[in,out] OrMask         Current buffer pointer of raw register values.
 *
 */
VOID
RestoreConditionalPciDevice (
  IN       AMD_CONFIG_PARAMS                 *StdHeader,
  IN       CONDITIONAL_PCI_DEVICE_DESCRIPTOR *Device,
  IN       CALL_POINTS                       CallPoint,
  IN OUT   VOID                              **OrMask
  )
{

}

/*---------------------------------------------------------------------------------------*/
/**
 * Restores the context of an MSR device.
 *
 * This traverses the provided register list restoring MSRs.
 *
 * @param[in]     StdHeader      AMD standard header config param.
 * @param[in]     Device         MSR device to restore.
 * @param[in]     CallPoint      Indicates whether this is AMD_INIT_RESUME or
 *                               AMD_S3LATE_RESTORE.
 * @param[in,out] OrMask         Current buffer pointer of raw register values.
 *
 */
VOID
RestoreMsrDevice (
  IN       AMD_CONFIG_PARAMS     *StdHeader,
  IN       MSR_DEVICE_DESCRIPTOR *Device,
  IN       CALL_POINTS           CallPoint,
  IN OUT   UINT64                **OrMask
  )
{

}

/*---------------------------------------------------------------------------------------*/
/**
 * Restores the context of a 'conditional' MSR device.
 *
 * This traverses the provided register list restoring MSRs when appropriate.
 *
 * @param[in]     StdHeader      AMD standard header config param.
 * @param[in]     Device         'conditional' MSR device to restore.
 * @param[in]     CallPoint      Indicates whether this is AMD_INIT_RESUME or
 *                               AMD_S3LATE_RESTORE.
 * @param[in,out] OrMask         Current buffer pointer of raw register values.
 *
 */
VOID
RestoreConditionalMsrDevice (
  IN       AMD_CONFIG_PARAMS                 *StdHeader,
  IN       CONDITIONAL_MSR_DEVICE_DESCRIPTOR *Device,
  IN       CALL_POINTS                       CallPoint,
  IN OUT   UINT64                            **OrMask
  )
{

}

/*---------------------------------------------------------------------------------------*/
/**
 * Unique device ID to PCI register list translator.
 *
 * This translates the given device header in storage to the appropriate list
 * of registers in the AGESA image.
 *
 * @param[out]   NonMemoryRelatedDeviceList  List of devices to save and restore
 *                                           during S3LateRestore.
 * @param[in]    StdHeader                   AMD standard header config param.
 *
 */
VOID
GetNonMemoryRelatedDeviceList (
     OUT   DEVICE_BLOCK_HEADER **NonMemoryRelatedDeviceList,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{

}

/*---------------------------------------------------------------------------------------*/
/**
 * Unique device ID to PCI register list translator.
 *
 * This translates the given device header in storage to the appropriate list
 * of registers in the AGESA image.
 *
 * @param[in]     Device         Device header containing the unique ID.
 * @param[out]    RegisterHdr    Output PCI register list pointer.
 * @param[in]     StdHeader      AMD standard header config param.
 *
 * @retval        AGESA_SUCCESS  Always succeeds.
 */
AGESA_STATUS
S3GetPciDeviceRegisterList (
  IN       PCI_DEVICE_DESCRIPTOR     *Device,
     OUT   PCI_REGISTER_BLOCK_HEADER **RegisterHdr,
  IN       AMD_CONFIG_PARAMS         *StdHeader
  )
{
  return AGESA_SUCCESS;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Unique device ID to 'conditional' PCI register list translator.
 *
 * This translates the given device header in storage to the appropriate list
 * of registers in the AGESA image.
 *
 * @param[in]     Device         Device header containing the unique ID.
 * @param[out]    RegisterHdr    Output 'conditional' PCI register list pointer.
 * @param[in]     StdHeader      AMD standard header config param.
 *
 * @retval        AGESA_SUCCESS  Always succeeds.
 */
AGESA_STATUS
S3GetCPciDeviceRegisterList (
  IN       CONDITIONAL_PCI_DEVICE_DESCRIPTOR *Device,
     OUT   CPCI_REGISTER_BLOCK_HEADER        **RegisterHdr,
  IN       AMD_CONFIG_PARAMS                 *StdHeader
  )
{
  return AGESA_SUCCESS;
}


/*---------------------------------------------------------------------------------------*/
/**
 * Unique device ID to MSR register list translator.
 *
 * This translates the given device header in storage to the appropriate list
 * of registers in the AGESA image.
 *
 * @param[in]     Device         Device header containing the unique ID.
 * @param[out]    RegisterHdr    Output MSR register list pointer.
 * @param[in]     StdHeader      AMD standard header config param.
 *
 * @retval        AGESA_SUCCESS  Always succeeds.
 */
AGESA_STATUS
S3GetMsrDeviceRegisterList (
  IN       MSR_DEVICE_DESCRIPTOR     *Device,
     OUT   MSR_REGISTER_BLOCK_HEADER **RegisterHdr,
  IN       AMD_CONFIG_PARAMS         *StdHeader
  )
{
  return AGESA_SUCCESS;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Unique device ID to 'conditional' MSR register list translator.
 *
 * This translates the given device header in storage to the appropriate list
 * of registers in the AGESA image.
 *
 * @param[in]     Device         Device header containing the unique ID.
 * @param[out]    RegisterHdr    Output 'conditional' MSR register list pointer.
 * @param[in]     StdHeader      AMD standard header config param.
 *
 * @retval        AGESA_SUCCESS  Always succeeds.
 */
AGESA_STATUS
S3GetCMsrDeviceRegisterList (
  IN       CONDITIONAL_MSR_DEVICE_DESCRIPTOR *Device,
     OUT   CMSR_REGISTER_BLOCK_HEADER        **RegisterHdr,
  IN       AMD_CONFIG_PARAMS                 *StdHeader
  )
{
  return AGESA_SUCCESS;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Constructor for the S3_DATA_BLOCK structure.
 *
 * This routine initializes failsafe values for the S3_DATA_BLOCK structure
 * to be used by the AMD_INIT_RESUME, AMD_INIT_RTB, and AMD_S3LATE_RESTORE
 * entry points.
 *
 * @param[in,out] S3DataBlock       Required input parameter for the AMD_INIT_RESUME,
 *                               AMD_INIT_RTB, and AMD_S3LATE_RESTORE entry points.
 *
 */
VOID
S3DataBlockInitializer (
     OUT   S3_DATA_BLOCK *S3DataBlock
  )
{

}

