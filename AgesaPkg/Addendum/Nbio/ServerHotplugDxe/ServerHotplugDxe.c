/* $NoKeywords:$ */
/**
 * @file
 *
 * Platform PCIe Complex Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  AmdNbioSmuV9Pei
 * @e \$Revision: 312065 $   @e \$Date: 2015-01-30 04:23:05 -0600 (Fri, 30 Jan 2015) $
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
#include <PiPei.h>
#include <AmdPcieComplex.h>
#include <AmdServerHotplug.h>
#include <Protocol/NbioHotplugDesc.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Library/HobLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>


/*----------------------------------------------------------------------------------------
 *                         E X T E R N   D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

HOTPLUG_DESCRIPTOR    HotplugDescriptor[] = {
  {
      0,
      HOTPLUG_ENGINE_DATA_INITIALIZER (0,      // Start Lane
                                       3,      // End Lane
                                       0,       // Socket Number
                                       4)       // Slot number
      PCIE_HOTPLUG_INITIALIZER_MAPPING (HotplugPresenceDetect,   //Hotplug Type
                                        0,      // 0 = No Gpio Descriptor
                                        0,      // 0 = No Reset Descriptor
                                        1,      // 1 = Port Active - this is a valid descriptor
                                        0,      // 1 = Master/Slave APU
                                        0,      // 0 = Die number this slot is connected to
                                        0,      // Alternate Slot number
                                        0)      // Primary/secondary for SSD only
      PCIE_HOTPLUG_INITIALIZER_FUNCTION (1,     // Gpio Bit Select
                                         0,     // GPIO Byte Mapping
                                         0,     // GPIO Device Mapping Ext
                                         7,  // GPIO Device Mapping
                                         1,     // Device Type 1 = 9535
                                         0,     // Bus Segment (No 9545 Present)
                                         0)  // Function Mask
      PCIE_HOTPLUG_INITIALIZER_NO_RESET()
      PCIE_HOTPLUG_INITIALIZER_NO_GPIO()
  },
  {
      0,
      HOTPLUG_ENGINE_DATA_INITIALIZER (4,      // Start Lane
                                       7,      // End Lane
                                       0,       // Socket Number
                                       5)       // Slot number
      PCIE_HOTPLUG_INITIALIZER_MAPPING (HotplugPresenceDetect,   //Hotplug Type
                                        0,      // 0 = No Gpio Descriptor
                                        0,      // 0 = No Reset Descriptor
                                        1,      // 1 = Port Active - this is a valid descriptor
                                        0,      // 1 = Master/Slave APU
                                        0,      // 0 = Die number this slot is connected to
                                        0,      // Alternate Slot number
                                        0)      // Primary/secondary for SSD only
      PCIE_HOTPLUG_INITIALIZER_FUNCTION (0,     // Gpio Bit Select
                                         1,     // GPIO Byte Mapping
                                         0,     // GPIO Device Mapping Ext
                                         7,  // GPIO Device Mapping
                                         1,     // Device Type 1 = 9535
                                         0,     // Bus Segment (No 9545 Present)
                                         0)  // Function Mask
      PCIE_HOTPLUG_INITIALIZER_NO_RESET()
      PCIE_HOTPLUG_INITIALIZER_NO_GPIO()
  },
  {
      0,
      HOTPLUG_ENGINE_DATA_INITIALIZER (8,      // Start Lane
                                       11,      // End Lane
                                       0,       // Socket Number
                                       6)       // Slot number
      PCIE_HOTPLUG_INITIALIZER_MAPPING (HotplugPresenceDetect,   //Hotplug Type
                                        0,      // 0 = No Gpio Descriptor
                                        0,      // 0 = No Reset Descriptor
                                        1,      // 1 = Port Active - this is a valid descriptor
                                        0,      // 1 = Master/Slave APU
                                        0,      // 0 = Die number this slot is connected to
                                        0,      // Alternate Slot number
                                        0)      // Primary/secondary for SSD only
      PCIE_HOTPLUG_INITIALIZER_FUNCTION (1,     // Gpio Bit Select
                                         0,     // GPIO Byte Mapping
                                         0,     // GPIO Device Mapping Ext
                                         7,  // GPIO Device Mapping
                                         1,     // Device Type 1 = 9535
                                         2,     // Bus Segment (No 9545 Present)
                                         0)  // Function Mask
      PCIE_HOTPLUG_INITIALIZER_NO_RESET()
      PCIE_HOTPLUG_INITIALIZER_NO_GPIO()
  },
  {
      0,
      HOTPLUG_ENGINE_DATA_INITIALIZER (12,      // Start Lane
                                       15,      // End Lane
                                       0,       // Socket Number
                                       7)       // Slot number
      PCIE_HOTPLUG_INITIALIZER_MAPPING (HotplugPresenceDetect,   //Hotplug Type
                                        0,      // 0 = No Gpio Descriptor
                                        0,      // 0 = No Reset Descriptor
                                        1,      // 1 = Port Active - this is a valid descriptor
                                        0,      // 1 = Master/Slave APU
                                        0,      // 0 = Die number this slot is connected to
                                        0,      // Alternate Slot number
                                        0)      // Primary/secondary for SSD only
      PCIE_HOTPLUG_INITIALIZER_FUNCTION (0,     // Gpio Bit Select
                                         1,     // GPIO Byte Mapping
                                         0,     // GPIO Device Mapping Ext
                                         7,  // GPIO Device Mapping
                                         1,     // Device Type 1 = 9535
                                         2,     // Bus Segment (No 9545 Present)
                                         0)  // Function Mask
      PCIE_HOTPLUG_INITIALIZER_NO_RESET()
      PCIE_HOTPLUG_INITIALIZER_NO_GPIO()
  },
  {
    0,
    HOTPLUG_ENGINE_DATA_INITIALIZER (80, 95, 0, 3)
    PCIE_HOTPLUG_INITIALIZER_MAPPING (HotplugExpressModule, 0, 0, 1, 1, 2, 0, 0)
    PCIE_HOTPLUG_INITIALIZER_FUNCTION (0, 0, 0, 3, 1, 7, 0)
    PCIE_HOTPLUG_INITIALIZER_NO_RESET ()
    PCIE_HOTPLUG_INITIALIZER_NO_GPIO ()
  },
  {
      0,
      HOTPLUG_ENGINE_DATA_INITIALIZER (0,       // Start Lane
                                       3,       // End Lane
                                       1,       // Socket Number
                                       8)       // Slot number
      PCIE_HOTPLUG_INITIALIZER_MAPPING (HotplugEnterpriseSsd,   //Hotplug Type
                                        0,      // 0 = No Gpio Descriptor
                                        0,      // 0 = No Reset Descriptor
                                        1,      // 1 = Port Active - this is a valid descriptor
                                        0,      // 1 = Master/Slave APU
                                        0,      // 0 = Die number this slot is connected to
                                        0,      // Alternate Slot number
                                        0)      // Primary/secondary for SSD only
      PCIE_HOTPLUG_INITIALIZER_FUNCTION (1,     // Gpio Bit Select
                                         0,     // GPIO Byte Mapping
                                         2,     // GPIO Device Mapping Ext
                                         1,     // GPIO Device Mapping
                                         1,     // Device Type 1 = 9535
                                         1,     // Bus Segment (No 9545 Present)
                                         0)     // Function Mask
      PCIE_HOTPLUG_INITIALIZER_NO_RESET()
      PCIE_HOTPLUG_INITIALIZER_NO_GPIO()
  },
  {
      0,
      HOTPLUG_ENGINE_DATA_INITIALIZER (4,       // Start Lane
                                       7,       // End Lane
                                       1,       // Socket Number
                                       9)       // Slot number
      PCIE_HOTPLUG_INITIALIZER_MAPPING (HotplugEnterpriseSsd,   //Hotplug Type
                                        0,      // 0 = No Gpio Descriptor
                                        0,      // 0 = No Reset Descriptor
                                        1,      // 1 = Port Active - this is a valid descriptor
                                        0,      // 1 = Master/Slave APU
                                        0,      // 0 = Die number this slot is connected to
                                        0,      // Alternate Slot number
                                        0)      // Primary/secondary for SSD only
      PCIE_HOTPLUG_INITIALIZER_FUNCTION (1,     // Gpio Bit Select
                                         1,     // GPIO Byte Mapping
                                         2,
                                         1,     // GPIO Device Mapping
                                         1,     // Device Type 1 = 9535
                                         1,     // Bus Segment (No 9545 Present)
                                         0)     // Function Mask
      PCIE_HOTPLUG_INITIALIZER_NO_RESET()
      PCIE_HOTPLUG_INITIALIZER_NO_GPIO()
  },
  {
      0,
      HOTPLUG_ENGINE_DATA_INITIALIZER (8,       // Start Lane
                                       11,      // End Lane
                                       1,       // Socket Number
                                       10)      // Slot number
      PCIE_HOTPLUG_INITIALIZER_MAPPING (HotplugEnterpriseSsd,   //Hotplug Type
                                        0,      // 0 = No Gpio Descriptor
                                        0,      // 0 = No Reset Descriptor
                                        1,      // 1 = Port Active - this is a valid descriptor
                                        0,      // 1 = Master/Slave APU
                                        0,      // 0 = Die number this slot is connected to
                                        0,      // Alternate Slot number
                                        0)      // Primary/secondary for SSD only
      PCIE_HOTPLUG_INITIALIZER_FUNCTION (1,     // Gpio Bit Select
                                         0,     // GPIO Byte Mapping
                                         2,     // GPIO Device Mapping Ext
                                         2,     // GPIO Device Mapping
                                         1,     // Device Type 1 = 9535
                                         1,     // Bus Segment (No 9545 Present)
                                         0)     // Function Mask
      PCIE_HOTPLUG_INITIALIZER_NO_RESET()
      PCIE_HOTPLUG_INITIALIZER_NO_GPIO()
  },
  {
      DESCRIPTOR_TERMINATE_LIST,
      HOTPLUG_ENGINE_DATA_INITIALIZER (12,      // Start Lane
                                       15,      // End Lane
                                       1,       // Socket Number
                                       11)      // Slot number
      PCIE_HOTPLUG_INITIALIZER_MAPPING (HotplugEnterpriseSsd,   //Hotplug Type
                                        0,      // 0 = No Gpio Descriptor
                                        0,      // 0 = No Reset Descriptor
                                        1,      // 1 = Port Active - this is a valid descriptor
                                        0,      // 1 = Master/Slave APU
                                        0,      // 0 = Die number this slot is connected to
                                        0,      // Alternate Slot number
                                        0)      // Primary/secondary for SSD only
      PCIE_HOTPLUG_INITIALIZER_FUNCTION (1,     // Gpio Bit Select
                                         1,     // GPIO Byte Mapping
                                         2,     // GPIO Device Mapping Ext
                                         2,     // GPIO Device Mapping
                                         1,     // Device Type 1 = 9535
                                         1,     // Bus Segment (No 9545 Present)
                                         0)     // Function Mask
      PCIE_HOTPLUG_INITIALIZER_NO_RESET()
      PCIE_HOTPLUG_INITIALIZER_NO_GPIO()
  },
};

STATIC NBIO_HOTPLUG_DESC_PROTOCOL mHotplugDescriptorProtocol = {
  AMD_NBIO_HOTPLUG_DESC_VERSION,  ///< revision
  HotplugDescriptor
};

EFI_STATUS
EFIAPI
HotplugDescEntry (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_HANDLE                       Handle;
  EFI_STATUS                       Status;

  Handle = NULL;
  // Fixup HOTPLUG_DESCRIPTOR here
  Status = gBS->InstallProtocolInterface (
                  &Handle,
                  &gAmdHotplugDescProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mHotplugDescriptorProtocol
                  );

  return Status;
}

