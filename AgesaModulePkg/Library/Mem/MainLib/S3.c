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
#include <Library/BaseLib.h>
#include "AGESA.h"
#include "Library/AmdBaseLib.h"
#include "Library/AmdMemBaseV5Lib.h"
#include "Library/IdsLib.h"
#include <Library/PciLib.h>
#include "Ids.h"
#include "mm.h"
#include "mn.h"
#include "S3.h"
#include "Library/AmdMemFeatS3Lib.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_MAINLIB_S3_FILECODE
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
  if (DeviceList != NULL) {
    // Copy device list over to create an entirely new S3 data blob
    LibAmdMemCopy (Storage,
                   DeviceList,
                   (UINTN) DeviceList->RelativeOrMaskOffset,
                   StdHeader);
    SaveDeviceContext (Storage, CallPoint, ActualBufferSize, StdHeader);
  } else {
    // An overwrite to the original S3 data blob (to fill in some special entries at the end of POST)
    SaveDeviceContext (Storage, CallPoint, NULL, StdHeader);
  }
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
  DEVICE_DESCRIPTORS Device;
  UINT16 i;
  UINT64 StartAddress;
  UINT64 EndAddress;
  VOID *OrMask;

  StartAddress = (UINT64) DeviceList;
  Device.CommonDeviceHeader = (DEVICE_DESCRIPTOR *) &DeviceList[1];
  OrMask = (UINT8 *) DeviceList + DeviceList->RelativeOrMaskOffset;

  // Process Pre ESR List
  for (i = 0; i < DeviceList->NumDevices; i++) {
    switch (Device.CommonDeviceHeader->Type) {
    case DEV_TYPE_PCI_PRE_ESR:
      SavePciDevice (StdHeader, Device.PciDevice, CallPoint, &OrMask);
      // Fall through to advance the pointer after saving context
    case DEV_TYPE_PCI:
      Device.PciDevice++;
      break;
    case DEV_TYPE_CPCI_PRE_ESR:
      SaveConditionalPciDevice (StdHeader, Device.CPciDevice, CallPoint, &OrMask);
      // Fall through to advance the pointer after saving context
    case DEV_TYPE_CPCI:
      Device.CPciDevice++;
      break;
    case DEV_TYPE_MSR_PRE_ESR:
      SaveMsrDevice (StdHeader, Device.MsrDevice, CallPoint, (UINT64 **) &OrMask);
      // Fall through to advance the pointer after saving context
    case DEV_TYPE_MSR:
      Device.MsrDevice++;
      break;
    case DEV_TYPE_CMSR_PRE_ESR:
      SaveConditionalMsrDevice (StdHeader, Device.CMsrDevice, CallPoint, (UINT64 **) &OrMask);
      // Fall through to advance the pointer after saving context
    case DEV_TYPE_CMSR:
      Device.CMsrDevice++;
      break;
    }
  }

  Device.CommonDeviceHeader = (DEVICE_DESCRIPTOR *) &DeviceList[1];
  // Process Post ESR List
  for (i = 0; i < DeviceList->NumDevices; i++) {
    switch (Device.CommonDeviceHeader->Type) {
    case DEV_TYPE_PCI:
      SavePciDevice (StdHeader, Device.PciDevice, CallPoint, &OrMask);
      // Fall through to advance the pointer after saving context
    case DEV_TYPE_PCI_PRE_ESR:
      Device.PciDevice++;
      break;
    case DEV_TYPE_CPCI:
      SaveConditionalPciDevice (StdHeader, Device.CPciDevice, CallPoint, &OrMask);
      // Fall through to advance the pointer after saving context
    case DEV_TYPE_CPCI_PRE_ESR:
      Device.CPciDevice++;
      break;
    case DEV_TYPE_MSR:
      SaveMsrDevice (StdHeader, Device.MsrDevice, CallPoint, (UINT64 **) &OrMask);
      // Fall through to advance the pointer after saving context
    case DEV_TYPE_MSR_PRE_ESR:
      Device.MsrDevice++;
      break;
    case DEV_TYPE_CMSR:
      SaveConditionalMsrDevice (StdHeader, Device.CMsrDevice, CallPoint, (UINT64 **) &OrMask);
      // Fall through to advance the pointer after saving context
    case DEV_TYPE_CMSR_PRE_ESR:
      Device.CMsrDevice++;
      break;
    }
  }
  if (ActualBufferSize != NULL) {
    EndAddress = (UINT64) OrMask;
    *ActualBufferSize = (UINT32) (EndAddress - StartAddress);
    DeviceList->BlobSize = *ActualBufferSize;
  }
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
  UINT8   RegSizeInBytes;
  UINT8   SpecialCaseIndex;
  UINT8   *IntermediatePtr;
  UINT8   BootMode;
  UINT16  i;
  UINT32  Socket;
  UINT32  Module;
  UINT32  AndMask;
  ACCESS_WIDTH AccessWidth;
  AGESA_STATUS IgnoredSts;
  PCI_ADDR PciAddress;
  PCI_REGISTER_BLOCK_HEADER *RegisterHdr;

  RegisterHdr = NULL;

  GetSocketModuleOfNode ((UINT32) Device->Node,
                               &Socket,
                               &Module,
                               StdHeader);
  GetPciAddress (StdHeader, Socket, Module, &PciAddress, &IgnoredSts);

  BootMode = 0;
  if (CallPoint == INIT_RESUME) {
    MemFS3GetPciDeviceRegisterList (Device, &RegisterHdr, StdHeader);
  } else if (CallPoint == PSP_INIT_RESUME) {
    MemFS3GetPciDeviceRegisterList (Device, &RegisterHdr, StdHeader);
    BootMode = SAVE_AT_POST_END;
  } else {
    S3GetPciDeviceRegisterList (Device, &RegisterHdr, StdHeader);
  }

  for (i = 0; i < RegisterHdr->NumRegisters; i++) {
    PciAddress.Address.Function = RegisterHdr->RegisterList[i].Function;
    PciAddress.Address.Register = RegisterHdr->RegisterList[i].Offset;
    RegSizeInBytes = RegisterHdr->RegisterList[i].Type.RegisterSize;
    switch (RegSizeInBytes) {
    case 1:
      AndMask = 0xFFFFFFFF & ((UINT8) RegisterHdr->RegisterList[i].AndMask);
      AccessWidth = AccessS3SaveWidth8;
      break;
    case 2:
      AndMask = 0xFFFFFFFF & ((UINT16) RegisterHdr->RegisterList[i].AndMask);
      AccessWidth = AccessS3SaveWidth16;
      break;
    case 3:
      // In this case, we don't need to save a register. We just need to call a special
      // function to do certain things in the save and resume sequence.
      // This should not be used in a non-special case.
      AndMask = 0;
      RegSizeInBytes = 0;
      AccessWidth = AccessWidthNone;
      break;
    default:
      AndMask = RegisterHdr->RegisterList[i].AndMask;
      RegSizeInBytes = 4;
      AccessWidth = AccessS3SaveWidth32;
      break;
    }
    if ((BootMode == 0) || ((BootMode & RegisterHdr->RegisterList[i].BootMode) != 0)) {
      // Do not save the register if not in the right boot mode
      // Pointer to the saved data buffer still needs to be adjusted as all data will be saved finally
      if (RegisterHdr->RegisterList[i].Type.SpecialCaseFlag == 0) {
        ASSERT ((AndMask != 0) && (RegSizeInBytes != 0) && (AccessWidth != 0));

        switch (AccessWidth) {
        case AccessWidth8:
        case AccessS3SaveWidth8:
          *((UINT8 *) *OrMask) = PciRead8 (PciAddress.AddressValue);
          break;
        case AccessWidth16:
        case AccessS3SaveWidth16:
          *((UINT16 *) *OrMask) = PciRead16 (PciAddress.AddressValue);
          break;
        case AccessWidth32:
        case AccessS3SaveWidth32:
          *((UINT32 *) *OrMask) = PciRead32 (PciAddress.AddressValue);
          break;
        default:
          IDS_ERROR_TRAP;
        }
      } else {
        SpecialCaseIndex = RegisterHdr->RegisterList[i].Type.SpecialCaseIndex;
        RegisterHdr->SpecialCases[SpecialCaseIndex].Save (AccessWidth, PciAddress, *OrMask, StdHeader);
      }
      if (AndMask != 0) {
        // If AndMask is 0, then it is a not-care. Don't need to apply it to the OrMask
        **((UINT32 **) OrMask) &= AndMask;
      }
      if ((RegSizeInBytes == 0) && (**((UINT32 **) OrMask) == RESTART_FROM_BEGINNING_LIST)) {
        // Restart from the beginning of the register list
        i = 0xFFFF;
      }
    }
    IntermediatePtr = (UINT8 *) *OrMask;
    *OrMask = &IntermediatePtr[4]; // += RegSizeInBytes;
  }
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
  UINT8   RegSizeInBytes;
  UINT8   SpecialCaseIndex;
  UINT8   *IntermediatePtr;
  UINT8   BootMode;
  UINT16  i;
  UINT32  Socket;
  UINT32  Module;
  UINT32  AndMask;
  ACCESS_WIDTH AccessWidth;
  AGESA_STATUS IgnoredSts;
  PCI_ADDR PciAddress;
  CPCI_REGISTER_BLOCK_HEADER *RegisterHdr;

  RegisterHdr = NULL;

  GetSocketModuleOfNode ((UINT32) Device->Node,
                               &Socket,
                               &Module,
                               StdHeader);
  GetPciAddress (StdHeader, Socket, Module, &PciAddress, &IgnoredSts);

  BootMode = 0;
  if (CallPoint == INIT_RESUME) {
    MemFS3GetCPciDeviceRegisterList (Device, &RegisterHdr, StdHeader);
  } else if (CallPoint == PSP_INIT_RESUME) {
    MemFS3GetCPciDeviceRegisterList (Device, &RegisterHdr, StdHeader);
    BootMode = SAVE_AT_POST_END;
  } else {
    S3GetCPciDeviceRegisterList (Device, &RegisterHdr, StdHeader);
  }

  for (i = 0; i < RegisterHdr->NumRegisters; i++) {
    if (((Device->Mask1 & RegisterHdr->RegisterList[i].Mask1) != 0) &&
        ((Device->Mask2 & RegisterHdr->RegisterList[i].Mask2) != 0)) {
      PciAddress.Address.Function = RegisterHdr->RegisterList[i].Function;
      PciAddress.Address.Register = RegisterHdr->RegisterList[i].Offset;
      RegSizeInBytes = RegisterHdr->RegisterList[i].Type.RegisterSize;
      switch (RegSizeInBytes) {
      case 1:
        AndMask = 0xFFFFFFFF & ((UINT8) RegisterHdr->RegisterList[i].AndMask);
        AccessWidth = AccessS3SaveWidth8;
        break;
      case 2:
        AndMask = 0xFFFFFFFF & ((UINT16) RegisterHdr->RegisterList[i].AndMask);
        AccessWidth = AccessS3SaveWidth16;
        break;
      case 3:
        // In this case, we don't need to save a register. We just need to call a special
        // function to do certain things in the save and resume sequence.
        // This should not be used in a non-special case.
        AndMask = 0;
        RegSizeInBytes = 0;
        AccessWidth = AccessWidthNone;
        break;
      default:
        AndMask = RegisterHdr->RegisterList[i].AndMask;
        RegSizeInBytes = 4;
        AccessWidth = AccessS3SaveWidth32;
        break;
      }

      if ((BootMode == 0) || ((BootMode & RegisterHdr->RegisterList[i].BootMode) != 0)) {
        // Do not save the register if not in the right boot mode
        // Pointer to the saved data buffer still needs to be adjusted as all data will be saved finally
        if (RegisterHdr->RegisterList[i].Type.SpecialCaseFlag == 0) {
          ASSERT ((AndMask != 0) && (RegSizeInBytes != 0) && (AccessWidth != 0));

          switch (AccessWidth) {
          case AccessWidth8:
          case AccessS3SaveWidth8:
            *((UINT8 *) *OrMask) = PciRead8 (PciAddress.AddressValue);
            break;
          case AccessWidth16:
          case AccessS3SaveWidth16:
            *((UINT16 *) *OrMask) = PciRead16 (PciAddress.AddressValue);
            break;
          case AccessWidth32:
          case AccessS3SaveWidth32:
            *((UINT32 *) *OrMask) = PciRead32 (PciAddress.AddressValue);
            break;
          default:
            IDS_ERROR_TRAP;
          }
        } else {
          SpecialCaseIndex = RegisterHdr->RegisterList[i].Type.SpecialCaseIndex;
          RegisterHdr->SpecialCases[SpecialCaseIndex].Save (AccessWidth, PciAddress, *OrMask, StdHeader);
        }
        if (AndMask != 0) {
          // If AndMask is 0, then it is a not-care. Don't need to apply it to the OrMask
          **((UINT32 **) OrMask) &= AndMask;
        }
        if ((RegSizeInBytes == 0) && (**((UINT32 **) OrMask) == RESTART_FROM_BEGINNING_LIST)) {
          // Restart from the beginning of the register list
          i = 0xFFFF;
        }
      }
      IntermediatePtr = (UINT8 *) *OrMask;
      *OrMask = &IntermediatePtr[4]; // += RegSizeInBytes;
    }
  }
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
  UINT8   SpecialCaseIndex;
  UINT8   BootMode;
  UINT16  i;
  MSR_REGISTER_BLOCK_HEADER *RegisterHdr;

  RegisterHdr = NULL;

  BootMode = 0;
  if (CallPoint == INIT_RESUME) {
    MemFS3GetMsrDeviceRegisterList (Device, &RegisterHdr, StdHeader);
  } else if (CallPoint == PSP_INIT_RESUME) {
    MemFS3GetMsrDeviceRegisterList (Device, &RegisterHdr, StdHeader);
    BootMode = SAVE_AT_POST_END;
  } else {
    S3GetMsrDeviceRegisterList (Device, &RegisterHdr, StdHeader);
  }

  for (i = 0; i < RegisterHdr->NumRegisters; i++) {
    if ((BootMode == 0) || ((BootMode & RegisterHdr->RegisterList[i].BootMode) != 0)) {
      // Do not save the register if not in the right boot mode
      // Pointer to the saved data buffer still needs to be adjusted as all data will be saved finally
      if (RegisterHdr->RegisterList[i].Type.SpecialCaseFlag == 0) {
        **OrMask = AsmReadMsr64 (RegisterHdr->RegisterList[i].Address);
      } else {
        SpecialCaseIndex = RegisterHdr->RegisterList[i].Type.SpecialCaseIndex;
        RegisterHdr->SpecialCases[SpecialCaseIndex].Save (RegisterHdr->RegisterList[i].Address, *OrMask, StdHeader);
      }
      if (RegisterHdr->RegisterList[i].AndMask != 0) {
        **OrMask &= RegisterHdr->RegisterList[i].AndMask;
      }
    }
    (*OrMask)++;
  }
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
  UINT8   SpecialCaseIndex;
  UINT8   BootMode;
  UINT16  i;
  CMSR_REGISTER_BLOCK_HEADER *RegisterHdr;

  RegisterHdr = NULL;

  BootMode = 0;
  if (CallPoint == INIT_RESUME) {
    MemFS3GetCMsrDeviceRegisterList (Device, &RegisterHdr, StdHeader);
  } else if (CallPoint == PSP_INIT_RESUME) {
    MemFS3GetCMsrDeviceRegisterList (Device, &RegisterHdr, StdHeader);
    BootMode = SAVE_AT_POST_END;
  } else {
    S3GetCMsrDeviceRegisterList (Device, &RegisterHdr, StdHeader);
  }

  for (i = 0; i < RegisterHdr->NumRegisters; i++) {
    if (((Device->Mask1 & RegisterHdr->RegisterList[i].Mask1) != 0) &&
        ((Device->Mask2 & RegisterHdr->RegisterList[i].Mask2) != 0)) {
      if ((BootMode == 0) || ((BootMode & RegisterHdr->RegisterList[i].BootMode) != 0)) {
      // Do not save the register if not in the right boot mode
      // Pointer to the saved data buffer still needs to be adjusted as all data will be saved finally
        if (RegisterHdr->RegisterList[i].Type.SpecialCaseFlag == 0) {
          **OrMask = AsmReadMsr64 (RegisterHdr->RegisterList[i].Address);
        } else {
          SpecialCaseIndex = RegisterHdr->RegisterList[i].Type.SpecialCaseIndex;
          RegisterHdr->SpecialCases[SpecialCaseIndex].Save (RegisterHdr->RegisterList[i].Address, (UINT64 *) *OrMask, StdHeader);
        }
        if (RegisterHdr->RegisterList[i].AndMask != 0) {
          **OrMask &= RegisterHdr->RegisterList[i].AndMask;
        }
      }
      (*OrMask)++;
    }
  }
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
  UINT32 WorstCaseSize;
  DEVICE_DESCRIPTORS Device;
  UINT16 i;
  REGISTER_BLOCK_HEADERS RegisterHdr;

  RegisterHdr.PciRegisters = NULL;

  WorstCaseSize = DeviceList->RelativeOrMaskOffset;
  Device.CommonDeviceHeader = (DEVICE_DESCRIPTOR *) &DeviceList[1];

  // Process Device List
  for (i = 0; i < DeviceList->NumDevices; i++) {
    switch (Device.CommonDeviceHeader->Type) {
    case DEV_TYPE_PCI_PRE_ESR:
      // PRE_ESR and post ESR take the same amount of space
    case DEV_TYPE_PCI:
      if (CallPoint == INIT_RESUME) {
        MemFS3GetPciDeviceRegisterList (Device.PciDevice, &(RegisterHdr.PciRegisters), StdHeader);
      } else {
        S3GetPciDeviceRegisterList (Device.PciDevice, &(RegisterHdr.PciRegisters), StdHeader);
      }
      WorstCaseSize += (RegisterHdr.PciRegisters->NumRegisters * 4);
      Device.PciDevice++;
      break;
    case DEV_TYPE_CPCI_PRE_ESR:
      // PRE_ESR and post ESR take the same amount of space
    case DEV_TYPE_CPCI:
      if (CallPoint == INIT_RESUME) {
        MemFS3GetCPciDeviceRegisterList (Device.CPciDevice, &(RegisterHdr.CPciRegisters), StdHeader);
      } else {
        S3GetCPciDeviceRegisterList (Device.CPciDevice, &(RegisterHdr.CPciRegisters), StdHeader);
      }
      WorstCaseSize += (RegisterHdr.CPciRegisters->NumRegisters * 4);
      Device.CPciDevice++;
      break;
    case DEV_TYPE_MSR_PRE_ESR:
      // PRE_ESR and post ESR take the same amount of space
    case DEV_TYPE_MSR:
      if (CallPoint == INIT_RESUME) {
        MemFS3GetMsrDeviceRegisterList (Device.MsrDevice, &(RegisterHdr.MsrRegisters), StdHeader);
      } else {
        S3GetMsrDeviceRegisterList (Device.MsrDevice, &(RegisterHdr.MsrRegisters), StdHeader);
      }
      WorstCaseSize += (RegisterHdr.MsrRegisters->NumRegisters * 8);
      Device.MsrDevice++;
      break;
    case DEV_TYPE_CMSR_PRE_ESR:
      // PRE_ESR and post ESR take the same amount of space
    case DEV_TYPE_CMSR:
      if (CallPoint == INIT_RESUME) {
        MemFS3GetCMsrDeviceRegisterList (Device.CMsrDevice, &(RegisterHdr.CMsrRegisters), StdHeader);
      } else {
        S3GetCMsrDeviceRegisterList (Device.CMsrDevice, &(RegisterHdr.CMsrRegisters), StdHeader);
      }
      WorstCaseSize += (RegisterHdr.CMsrRegisters->NumRegisters * 8);
      Device.CMsrDevice++;
      break;
    default:
      ASSERT (FALSE);
    }
  }

  return (WorstCaseSize);
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
  DEVICE_DESCRIPTORS Device;
  UINT16 i;
  DEVICE_BLOCK_HEADER *DeviceList;

  DeviceList = (DEVICE_BLOCK_HEADER *) Storage;
  Device.CommonDeviceHeader = (DEVICE_DESCRIPTOR *) &DeviceList[1];
  *OrMaskPtr = (UINT8 *) DeviceList + DeviceList->RelativeOrMaskOffset;

  // Process Pre ESR List
  for (i = 0; i < DeviceList->NumDevices; i++) {
    switch (Device.CommonDeviceHeader->Type) {
    case DEV_TYPE_PCI_PRE_ESR:
      RestorePciDevice (StdHeader, Device.PciDevice, CallPoint, OrMaskPtr);
      // Fall through to advance the pointer after restoring context
    case DEV_TYPE_PCI:
      Device.PciDevice++;
      break;
    case DEV_TYPE_CPCI_PRE_ESR:
      RestoreConditionalPciDevice (StdHeader, Device.CPciDevice, CallPoint, OrMaskPtr);
      // Fall through to advance the pointer after restoring context
    case DEV_TYPE_CPCI:
      Device.CPciDevice++;
      break;
    case DEV_TYPE_MSR_PRE_ESR:
      RestoreMsrDevice (StdHeader, Device.MsrDevice, CallPoint, (UINT64 **) OrMaskPtr);
      // Fall through to advance the pointer after restoring context
    case DEV_TYPE_MSR:
      Device.MsrDevice++;
      break;
    case DEV_TYPE_CMSR_PRE_ESR:
      RestoreConditionalMsrDevice (StdHeader, Device.CMsrDevice, CallPoint, (UINT64 **) OrMaskPtr);
      // Fall through to advance the pointer after restoring context
    case DEV_TYPE_CMSR:
      Device.CMsrDevice++;
      break;
    }
  }
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
  DEVICE_DESCRIPTORS Device;
  UINT16 i;
  DEVICE_BLOCK_HEADER *DeviceList;

  DeviceList = (DEVICE_BLOCK_HEADER *) Storage;
  Device.CommonDeviceHeader = (DEVICE_DESCRIPTOR *) &DeviceList[1];

  // Process Pre ESR List
  for (i = 0; i < DeviceList->NumDevices; i++) {
    switch (Device.CommonDeviceHeader->Type) {
    case DEV_TYPE_PCI:
      RestorePciDevice (StdHeader, Device.PciDevice, CallPoint, &OrMaskPtr);
      // Fall through to advance the pointer after restoring context
    case DEV_TYPE_PCI_PRE_ESR:
      Device.PciDevice++;
      break;
    case DEV_TYPE_CPCI:
      RestoreConditionalPciDevice (StdHeader, Device.CPciDevice, CallPoint, &OrMaskPtr);
      // Fall through to advance the pointer after restoring context
    case DEV_TYPE_CPCI_PRE_ESR:
      Device.CPciDevice++;
      break;
    case DEV_TYPE_MSR:
      RestoreMsrDevice (StdHeader, Device.MsrDevice, CallPoint, (UINT64 **) &OrMaskPtr);
      // Fall through to advance the pointer after restoring context
    case DEV_TYPE_MSR_PRE_ESR:
      Device.MsrDevice++;
      break;
    case DEV_TYPE_CMSR:
      RestoreConditionalMsrDevice (StdHeader, Device.CMsrDevice, CallPoint, (UINT64 **) &OrMaskPtr);
      // Fall through to advance the pointer after restoring context
    case DEV_TYPE_CMSR_PRE_ESR:
      Device.CMsrDevice++;
      break;
    }
  }
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
  UINT8   RegSizeInBytes;
  UINT8   SpecialCaseIndex;
  UINT8   *IntermediatePtr;
  UINT8   BootMode;
  UINT16  i;
  UINT32  Socket;
  UINT32  Module;
  UINT32  AndMask;
  UINT32  RegValueRead;
  UINT32  RegValueWrite;
  ACCESS_WIDTH AccessWidth;
  AGESA_STATUS IgnoredSts;
  PCI_ADDR PciAddress;
  PCI_REGISTER_BLOCK_HEADER *RegisterHdr;

  RegisterHdr = NULL;

  RegValueRead = 0;
  GetSocketModuleOfNode ((UINT32) Device->Node,
                               &Socket,
                               &Module,
                               StdHeader);
  GetPciAddress (StdHeader, Socket, Module, &PciAddress, &IgnoredSts);

  if (CallPoint == INIT_RESUME) {
    MemFS3GetPciDeviceRegisterList (Device, &RegisterHdr, StdHeader);
  } else {
    S3GetPciDeviceRegisterList (Device, &RegisterHdr, StdHeader);
  }

  BootMode = S3_RESUME_MODE;
  if (StdHeader->Func == AMD_INIT_POST) {
    BootMode = RESTORE_TRAINING_MODE | CAPSULE_REBOOT_MODE;
  }

  for (i = 0; i < RegisterHdr->NumRegisters; i++) {
    PciAddress.Address.Function = RegisterHdr->RegisterList[i].Function;
    PciAddress.Address.Register = RegisterHdr->RegisterList[i].Offset;
    RegSizeInBytes = RegisterHdr->RegisterList[i].Type.RegisterSize;
    switch (RegSizeInBytes) {
    case 1:
      AndMask = 0xFFFFFFFF & ((UINT8) RegisterHdr->RegisterList[i].AndMask);
      RegValueWrite = **(UINT8 **)OrMask;
      AccessWidth = AccessS3SaveWidth8;
      break;
    case 2:
      AndMask = 0xFFFFFFFF & ((UINT16) RegisterHdr->RegisterList[i].AndMask);
      RegValueWrite = **(UINT16 **)OrMask;
      AccessWidth = AccessS3SaveWidth16;
      break;
    case 3:
      // In this case, we don't need to restore a register. We just need to call a special
      // function to do certain things in the save and resume sequence.
      // This should not be used in a non-special case.
      AndMask = 0;
      RegValueWrite = 0;
      RegSizeInBytes = 0;
      AccessWidth = AccessWidthNone;
      break;
    default:
      AndMask = RegisterHdr->RegisterList[i].AndMask;
      RegSizeInBytes = 4;
      RegValueWrite = **(UINT32 **)OrMask;
      AccessWidth = AccessS3SaveWidth32;
      break;
    }
    if ((RegisterHdr->RegisterList[i].BootMode == 0) || ((BootMode & RegisterHdr->RegisterList[i].BootMode) != 0)) {
      // Do not restore the register if not in the right boot mode
      // Pointer to the saved data buffer still needs to be adjusted as data will be saved regardless of boot mode
      if (RegisterHdr->RegisterList[i].Type.SpecialCaseFlag == 0) {
        ASSERT ((AndMask != 0) && (RegSizeInBytes != 0) && (AccessWidth != 0));
        if (AndMask != (UINT32) ((1 << (RegSizeInBytes * 8)) - 1) && AndMask != 0xFFFFFFFF) {
          // Spare the read if all bits need to be restored
          switch (AccessWidth) {
          case AccessWidth8:
          case AccessS3SaveWidth8:
            RegValueRead = PciRead8 (PciAddress.AddressValue);
            break;
          case AccessWidth16:
          case AccessS3SaveWidth16:
            RegValueRead = PciRead16 (PciAddress.AddressValue);
            break;
          case AccessWidth32:
          case AccessS3SaveWidth32:
            RegValueRead = PciRead32 (PciAddress.AddressValue);
            break;
          default:
            IDS_ERROR_TRAP;
          }

          RegValueWrite |= RegValueRead & (~AndMask);
        }

        switch (AccessWidth) {
        case AccessWidth8:
        case AccessS3SaveWidth8:
          PciWrite8 (PciAddress.AddressValue, *((UINT8 *) &RegValueWrite));
          break;
        case AccessWidth16:
        case AccessS3SaveWidth16:
          PciWrite16 (PciAddress.AddressValue, *((UINT16 *) &RegValueWrite));
          break;
        case AccessWidth32:
        case AccessS3SaveWidth32:
          PciWrite32 (PciAddress.AddressValue, *((UINT32 *) &RegValueWrite));
          break;
        default:
          IDS_ERROR_TRAP;
        }
      } else {
        SpecialCaseIndex = RegisterHdr->RegisterList[i].Type.SpecialCaseIndex;
        if (AndMask != 0) {
          if (AndMask != (UINT32) ((1 << (RegSizeInBytes * 8)) - 1) && AndMask != 0xFFFFFFFF) {
            // Spare the read if all bits need to be restored
            RegisterHdr->SpecialCases[SpecialCaseIndex].Save (AccessWidth,
                                                 PciAddress,
                                                 &RegValueRead,
                                                 StdHeader);
            RegValueWrite |= RegValueRead & (~AndMask);
          }
        }
        RegisterHdr->SpecialCases[SpecialCaseIndex].Restore (AccessWidth,
                                               PciAddress,
                                               &RegValueWrite,
                                               StdHeader);
      }
      IDS_OPTION_HOOK (IDS_AFTER_RESTORING_PCI_REG, RegisterHdr, StdHeader);
    }
    IntermediatePtr = (UINT8 *) *OrMask;
    *OrMask = &IntermediatePtr[4]; // += RegSizeInBytes;
    if ((RegSizeInBytes == 0) && (RegValueWrite == RESTART_FROM_BEGINNING_LIST)) {
      // Restart from the beginning of the register list
      i = 0xFFFF;
    }
  }
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
  UINT8   RegSizeInBytes;
  UINT8   SpecialCaseIndex;
  UINT8   *IntermediatePtr;
  UINT8   BootMode;
  UINT16  i;
  UINT32  Socket;
  UINT32  Module;
  UINT32  RegValueRead;
  UINT32  RegValueWrite;
  UINT32  AndMask;
  ACCESS_WIDTH AccessWidth;
  AGESA_STATUS IgnoredSts;
  PCI_ADDR PciAddress;
  CPCI_REGISTER_BLOCK_HEADER *RegisterHdr;

  RegisterHdr = NULL;

  RegValueRead = 0;
  GetSocketModuleOfNode ((UINT32) Device->Node,
                               &Socket,
                               &Module,
                               StdHeader);
  GetPciAddress (StdHeader, Socket, Module, &PciAddress, &IgnoredSts);

  if (CallPoint == INIT_RESUME) {
    MemFS3GetCPciDeviceRegisterList (Device, &RegisterHdr, StdHeader);
  } else {
    S3GetCPciDeviceRegisterList (Device, &RegisterHdr, StdHeader);
  }

  BootMode = S3_RESUME_MODE;
  if (StdHeader->Func == AMD_INIT_POST) {
    BootMode = RESTORE_TRAINING_MODE | CAPSULE_REBOOT_MODE;
  }

  for (i = 0; i < RegisterHdr->NumRegisters; i++) {
    if (((Device->Mask1 & RegisterHdr->RegisterList[i].Mask1) != 0) &&
        ((Device->Mask2 & RegisterHdr->RegisterList[i].Mask2) != 0)) {
      PciAddress.Address.Function = RegisterHdr->RegisterList[i].Function;
      PciAddress.Address.Register = RegisterHdr->RegisterList[i].Offset;
      RegSizeInBytes = RegisterHdr->RegisterList[i].Type.RegisterSize;
      switch (RegSizeInBytes) {
      case 1:
        AndMask = 0xFFFFFFFF & ((UINT8) RegisterHdr->RegisterList[i].AndMask);
        RegValueWrite = **(UINT8 **)OrMask;
        AccessWidth = AccessS3SaveWidth8;
        break;
      case 2:
        AndMask = 0xFFFFFFFF & ((UINT16) RegisterHdr->RegisterList[i].AndMask);
        RegValueWrite = **(UINT16 **)OrMask;
        AccessWidth = AccessS3SaveWidth16;
        break;
      case 3:
        // In this case, we don't need to restore a register. We just need to call a special
        //  function to do certain things in the save and resume sequence.
        // This should not be used in a non-special case.
        AndMask = 0;
        RegValueWrite = 0;
        RegSizeInBytes = 0;
        AccessWidth = AccessWidthNone;
        break;
      default:
        AndMask = RegisterHdr->RegisterList[i].AndMask;
        RegSizeInBytes = 4;
        RegValueWrite = **(UINT32 **)OrMask;
        AccessWidth = AccessS3SaveWidth32;
        break;
      }
      if ((RegisterHdr->RegisterList[i].BootMode == 0) || ((BootMode & RegisterHdr->RegisterList[i].BootMode) != 0)) {
        // Do not restore the register if not in the right boot mode
        // Pointer to the saved data buffer still needs to be adjusted as data will be saved regardless of boot mode
        if (RegisterHdr->RegisterList[i].Type.SpecialCaseFlag == 0) {
          if (AndMask != (UINT32) ((1 << (RegSizeInBytes * 8)) - 1) && AndMask != 0xFFFFFFFF) {
            // Spare the read if all bits need to be restored
            switch (AccessWidth) {
            case AccessWidth8:
            case AccessS3SaveWidth8:
              RegValueRead = PciRead8 (PciAddress.AddressValue);
              break;
            case AccessWidth16:
            case AccessS3SaveWidth16:
              RegValueRead = PciRead16 (PciAddress.AddressValue);
              break;
            case AccessWidth32:
            case AccessS3SaveWidth32:
              RegValueRead = PciRead32 (PciAddress.AddressValue);
              break;
            default:
              IDS_ERROR_TRAP;
            }

            RegValueWrite |= RegValueRead & (~AndMask);
          }

          switch (AccessWidth) {
          case AccessWidth8:
          case AccessS3SaveWidth8:
            PciWrite8 (PciAddress.AddressValue, *((UINT8 *) &RegValueWrite));
            break;
          case AccessWidth16:
          case AccessS3SaveWidth16:
            PciWrite16 (PciAddress.AddressValue, *((UINT16 *) &RegValueWrite));
            break;
          case AccessWidth32:
          case AccessS3SaveWidth32:
            PciWrite32 (PciAddress.AddressValue, *((UINT32 *) &RegValueWrite));
            break;
          default:
            IDS_ERROR_TRAP;
          }
        } else {
          SpecialCaseIndex = RegisterHdr->RegisterList[i].Type.SpecialCaseIndex;
          if (AndMask != 0) {
            if (AndMask != (UINT32) ((1 << (RegSizeInBytes * 8)) - 1) && AndMask != 0xFFFFFFFF) {
              // Spare the read if all bits need to be restored
              RegisterHdr->SpecialCases[SpecialCaseIndex].Save (AccessWidth,
                                                 PciAddress,
                                                 &RegValueRead,
                                                 StdHeader);
              RegValueWrite |= RegValueRead & (~AndMask);
            }
          }
          IDS_SKIP_HOOK (IDS_BYPASS_S3_REGISTERS, &PciAddress, StdHeader) {
            RegisterHdr->SpecialCases[SpecialCaseIndex].Restore (AccessWidth,
                                                   PciAddress,
                                                   &RegValueWrite,
                                                   StdHeader);
          }
        }
        IDS_OPTION_HOOK (IDS_AFTER_RESTORING_PCI_REG, RegisterHdr, StdHeader);
      }
      IntermediatePtr = (UINT8 *) *OrMask;
      *OrMask = &IntermediatePtr[4];
      if ((RegSizeInBytes == 0) && (RegValueWrite == RESTART_FROM_BEGINNING_LIST)) {
        // Restart from the beginning of the register list
        i = 0xFFFF;
      }
    }
  }
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
  UINT8   SpecialCaseIndex;
  UINT8   BootMode;
  UINT16  i;
  UINT64  RegValueRead;
  UINT64  RegValueWrite;
  MSR_REGISTER_BLOCK_HEADER *RegisterHdr;

  RegisterHdr = NULL;

  if (CallPoint == INIT_RESUME) {
    MemFS3GetMsrDeviceRegisterList (Device, &RegisterHdr, StdHeader);
  } else {
    S3GetMsrDeviceRegisterList (Device, &RegisterHdr, StdHeader);
  }

  BootMode = S3_RESUME_MODE;
  if (StdHeader->Func == AMD_INIT_POST) {
    BootMode = RESTORE_TRAINING_MODE | CAPSULE_REBOOT_MODE;
  }

  for (i = 0; i < RegisterHdr->NumRegisters; i++) {
    if ((RegisterHdr->RegisterList[i].BootMode == 0) || ((BootMode & RegisterHdr->RegisterList[i].BootMode) != 0)) {
      // Do not restore the register if not in the right boot mode
      // Pointer to the saved data buffer still needs to be adjusted as data will be saved regardless of boot mode
      RegValueWrite = **OrMask;
      if (RegisterHdr->RegisterList[i].Type.SpecialCaseFlag == 0) {
        if ((RegisterHdr->RegisterList[i].AndMask + 1) != 0) {
          // Spare the read if all bits need to be restored
          RegValueRead = AsmReadMsr64 (RegisterHdr->RegisterList[i].Address);
          RegValueWrite |= RegValueRead & (~RegisterHdr->RegisterList[i].AndMask);
        }
        AsmWriteMsr64 (RegisterHdr->RegisterList[i].Address, RegValueWrite);
      } else {
        SpecialCaseIndex = RegisterHdr->RegisterList[i].Type.SpecialCaseIndex;
        if ((RegisterHdr->RegisterList[i].AndMask + 1) != 0) {
          // Spare the read if all bits need to be restored
          RegisterHdr->SpecialCases[SpecialCaseIndex].Save (RegisterHdr->RegisterList[i].Address,
                                                               &RegValueRead,
                                                               StdHeader);
          RegValueWrite |= RegValueRead & (~RegisterHdr->RegisterList[i].AndMask);
        }
        RegisterHdr->SpecialCases[SpecialCaseIndex].Restore (RegisterHdr->RegisterList[i].Address,
                                                             &RegValueWrite,
                                                             StdHeader);
      }
    }
    (*OrMask)++;
  }
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
  UINT8   SpecialCaseIndex;
  UINT8   BootMode;
  UINT16  i;
  UINT64  RegValueRead;
  UINT64  RegValueWrite;
  CMSR_REGISTER_BLOCK_HEADER *RegisterHdr;

  RegisterHdr = NULL;

  if (CallPoint == INIT_RESUME) {
    MemFS3GetCMsrDeviceRegisterList (Device, &RegisterHdr, StdHeader);
  } else {
    S3GetCMsrDeviceRegisterList (Device, &RegisterHdr, StdHeader);
  }

  BootMode = S3_RESUME_MODE;
  if (StdHeader->Func == AMD_INIT_POST) {
    BootMode = RESTORE_TRAINING_MODE | CAPSULE_REBOOT_MODE;
  }

  for (i = 0; i < RegisterHdr->NumRegisters; i++) {
    if (((Device->Mask1 & RegisterHdr->RegisterList[i].Mask1) != 0) &&
        ((Device->Mask2 & RegisterHdr->RegisterList[i].Mask2) != 0)) {
      if ((RegisterHdr->RegisterList[i].BootMode == 0) || ((BootMode & RegisterHdr->RegisterList[i].BootMode) != 0)) {
        // Do not restore the register if not in the right boot mode
        // Pointer to the saved data buffer still needs to be adjusted as data will be saved regardless of boot mode
        RegValueWrite = **OrMask;
        if (RegisterHdr->RegisterList[i].Type.SpecialCaseFlag == 0) {
          if ((RegisterHdr->RegisterList[i].AndMask + 1) != 0) {
          // Spare the read if all bits need to be restored
            RegValueRead = AsmReadMsr64 (RegisterHdr->RegisterList[i].Address);
            RegValueWrite |= RegValueRead & (~RegisterHdr->RegisterList[i].AndMask);
          }
          AsmWriteMsr64 (RegisterHdr->RegisterList[i].Address, RegValueWrite);
        } else {
          SpecialCaseIndex = RegisterHdr->RegisterList[i].Type.SpecialCaseIndex;
          if ((RegisterHdr->RegisterList[i].AndMask + 1) != 0) {
          // Spare the read if all bits need to be restored
            RegisterHdr->SpecialCases[SpecialCaseIndex].Save (RegisterHdr->RegisterList[i].Address,
                                                               &RegValueRead,
                                                               StdHeader);
            RegValueWrite |= RegValueRead & (~RegisterHdr->RegisterList[i].AndMask);
          }
          RegisterHdr->SpecialCases[SpecialCaseIndex].Restore (RegisterHdr->RegisterList[i].Address,
                                                               &RegValueWrite,
                                                               StdHeader);
        }
      }
      (*OrMask)++;
    }
  }
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
  *NonMemoryRelatedDeviceList = NULL;
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
  *RegisterHdr = NULL;
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
  *RegisterHdr = NULL;
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
  *RegisterHdr = NULL;
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
  *RegisterHdr = NULL;
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
  S3DataBlock->Signature = 0x52545341;
  S3DataBlock->Version = 0x0000;
  S3DataBlock->VolatileStorage = NULL;
  S3DataBlock->VolatileStorageSize = 0x00000000;
  S3DataBlock->Flags = 0x00000000;
  S3DataBlock->NvStorage = NULL;
  S3DataBlock->NvStorageSize = 0x00000000;
}

