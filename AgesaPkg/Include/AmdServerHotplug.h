/* $NoKeywords:$ */
/**
 * @file
 *
 * Platform PCIe Complex Definitions
 *
 * Contains AMD AGESA core interface
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Include
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-25 21:00:43 -0600 (Wed, 25 Feb 2015) $
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
 **/


#ifndef _AMD_SERVER_HOTPLUG_H_
#define _AMD_SERVER_HOTPLUG_H_


#ifndef DESCRIPTOR_TERMINATE_LIST
  #define DESCRIPTOR_TERMINATE_LIST           0x80000000ull
#endif


/// PCIe Hot Plug Format
typedef enum {
  HotplugPresenceDetect,                                      ///< Simple Presence Detect
  HotplugExpressModule,                                       ///< PCIe Express Module
  HotplugEnterpriseSsd,                                       ///< Enterprise SSD
  HotplugExpressModuleB,                                      ///< PCIe Express Module B
  MaxHotplugFormat                                            ///< Not valid value, used to verify input
} DXIO_HOTPLUG_TYPE;


// --------------------------------------------------------------------------------------------------
// PCIE_HOTPLUG_MAPPING
// Each MAPPING descriptor contains information that identifies how a given hot-plug slot maps onto the APU device capabilities.
// Depending on whether the port is active, the <slotNum> MAPPING descriptor specifies a mapping to a particular PCIe function/port
// in the socket. Additionally, the MAPPING descriptor also identifies the level of hot-plug capability, as well as the applicability
// of the RESET and GPIO descriptors. The MAPPING descriptor is always valid for an active hot-plug slot.
//

/// PCIe Hotplug Mapping Descriptor
typedef struct  {
  IN      UINT32                    HotPlugFormat          :3;  /**< Hotplug Format
                                                                 *  @li @b 0 - Simple Presence Detect
                                                                 *  @li @b 1 - PCIe Express Module
                                                                 *  @li @b 2 - Enterprise SSD
                                                                 */
  IN      UINT32                    Revision               :1;  ///< GPIO Descriptor revision
  IN      UINT32                    GpioDescriptorValid    :1;  /**< GPIO Descriptor Valid
                                                                 *  @li @b 0 - This descriptor should be ignored
                                                                 *  @li @b 1 - This descriptor is valid
                                                                 */
  IN      UINT32                    ResetDescriptorValid   :1;  /**< Reset Descriptor Valid
                                                                 *  @li @b 0 - Reset is not supported from the I2C subsystem
                                                                 *  @li @b 1 - Reset is supported from the I2C subsystem
                                                                 */
  IN      UINT32                    PortActive             :1;  /**< This bit is essentially a valid marker indicating whether the hot-plug slot is
                                                                 *   implemented in the system and whether the information in the descriptor register
                                                                 *   is valid.
                                                                 *  @li @b 0 - This descriptor should be ignored
                                                                 *  @li @b 1 - This descriptor is valid
                                                                 */
  IN      UINT32                    MasterSlaveAPU         :1;  /**< this bit indicates the APU (Master or Slave die) the PCIe device, that is
                                                                 *   mapped onto the hot-plug slot, resides. Note, the "Master" APU is the APU
                                                                 *   that hosts the I2C subsystem. The "Slave" APU communicates with the "Master"
                                                                 *   APU through a die-to-die communication link (DDCL).
                                                                 *  @li @b 0 - Connected to Master APU
                                                                 *  @li @b 1 - Connected to Slave APU
                                                                 */
  IN      UINT32                    DieNumber              :4;  ///< Indicates the Zeppelin Die number in the system
  IN      UINT32                    PortId                 :3;  ///< Indicates port number on the core
  IN      UINT32                    TileId                 :1;  /**< Indicates the Aperture ID assigned to the PCIe tile on the SMN network.
                                                                 *   This is used by the SMU to route the "SMU Status Transfer" to the correct PCIe tile.
                                                                 *   This can also be seen as the PCIe "core number", that contains PCIe device that is
                                                                 *   mapped onto the hot-plug slot.
                                                                 */
  IN      UINT32                    Rsvd0                  :8;
  IN      UINT32                    AlternateSlotNumber    :6;  /**< When the descriptor is used for an Enterprise SSD form-factor, and the slot
                                                                 *   supports two PCIe links, this field serves as a pointer to the PCIE_HOTPLUG_MAPPING<slotNum>
                                                                 *   descriptor associated with the 'other' PCIe link. The primary descriptor shall point to
                                                                 *   the secondary descriptor, and the secondary descriptor must point to the primary descriptor.
                                                                 *   For a slot that only supports a single PCIe link, the primary descriptor must set this field to zero.
                                                                 */
  IN      UINT32                    PrimarySecondaryLink   :1;  /**< When the descriptor is used for an Enterprise SSD form-factor, this bit specifies whether the
                                                                 *   descriptor is for the primary PCIe device, or the secondary PCIe device associated with the slot.
                                                                 *  @li @b 0 - This is the primary PCIe device
                                                                 *  @li @b 1 - This is the secondary PCIe device
                                                                 */
  IN      UINT32                    Reserved1              :1;  ///< Reserved for future use
} PCIE_HOTPLUG_MAPPING;


// --------------------------------------------------------------------------------------------------
// PCIE_HOTPLUG_FUNCTION Descriptor
// Associated with each MAPPING descriptor (refer to section 5.5.1), a FUNCTION descriptor is provided that indicates where the associated hot-plug functionality
// is mapped within the I2C subsystem. Through the FUNCTION descriptor, the exact pin (or group of pins) on a specific IO byte of a specific I2C GPIO device.
// In addition, where a group of pins is allocated to the hot-plug functionality (based on the "HotPlugFormat" field of the corresponding MAPPING descriptor),
// a bitwise mask is provided to opt-out of specific functional elements of the specified hot-plug behaviour, freeing the associated pin for other potential uses.
//

/// PCIe Hotplug Function Descriptor
typedef struct  {
  IN      UINT32                    I2CGpioBitSelector     :3;  /**< I2C GPIO Bit Select : for a simple presense detect usage model, this field indicates which
                                                                 *   bit of which IO byte is used for the presence detect signal associated with this descriptor.
                                                                 *   For an Enterprise SSD form-factor, bits 0 and 1 must be 0 and bit 2 selects which nibble of the
                                                                 *   IO byte is used for the hot plug signals associated with this descriptor.
                                                                 */
  IN      UINT32                    I2CGpioByteMapping     :3;  /**< I2C GPIO IO Byte Mapping : indicates which IO byte of the I2C GPIO device is used for the
                                                                 *   hot-plug signals associated with this descriptor.
                                                                 */
  IN      UINT32                    I2CGpioDeviceMappingExt :2; /**< I2C GPIO Device Mapping Ext: indicates bits 4:3 of the I2C address for the
                                                                 *   I2C GPIO device that is used to host the hot-plug signals associated with this descriptor.
                                                                 */
  IN      UINT32                    I2CGpioDeviceMapping   :3;  /**< I2C GPIO Device Mapping : indicates the lower three bits of the I2C address for the
                                                                 *   I2C GPIO device that is used to host the hot-plug signals associated with this descriptor.
                                                                 */
  IN      UINT32                    I2CDeviceType          :2;  /**< I2C Device Type : indicates which of three I2C GPIO devices is used to host the hot-plug
                                                                 *   signals associated with this descriptor.
                                                                 *  @li @b 00 - PCA9539 address and register map; in support of legacy hot-plug implementations
                                                                 *  @li @b 01 - PCA9535 address and register map; in support of newer hot-plug implementations
                                                                 *  @li @b 10 - PCA9506 address and register map; in support of high slot-capacity implementations
                                                                 *  @li @b 11 - reserved
                                                                 *   Note, PCA9535 and PCA9506 devices may be intermixed on the I2C interface.
                                                                 *   However, due to common addressing, a combined total of eight devices may be populated.
                                                                 */
  IN      UINT32                    I2CBusSegment          :3;  /**< I2C Bus Segment :  in the context of an I2C subsystem constructed with PCA9545 I2C switches,
                                                                 *   this field specifies the downstream I2C bus segment, on one of two PCA9545 switches, on which
                                                                 *   the target I2C GPIO device is located. However, for I2C topologies that are not constructed
                                                                 *   with any PCA9545 devices, one value is reserved to identify that the I2C GPIO device does
                                                                 *   not reside behind any PCA9454 I2C switch.
                                                                 *  @li @b 000 - PCA9545, address=00, downstream I2C bus=00
                                                                 *  @li @b 001 - PCA9545, address=00, downstream I2C bus=01
                                                                 *  @li @b 010 - PCA9545, address=00, downstream I2C bus=10
                                                                 *  @li @b 011 - PCA9545, address=00, downstream I2C bus=11
                                                                 *  @li @b 100 - PCA9545, address=01, downstream I2C bus=00
                                                                 *  @li @b 101 - PCA9545, address=01, downstream I2C bus=01
                                                                 *  @li @b 110 - PCA9545, address=01, downstream I2C bus=10
                                                                 *  @li @b 111 - no PCA9545; I2C bus directly connected to APU socket
                                                                 */
  IN      UINT32                    FunctionMask           :8;  /**< Function Mask : when the descriptor is used for a multi-bit hot-plug functional format,
                                                                 *   this field can be used to opt-out of specific pin functionality. When an 8bit GPIO group
                                                                 *   is allocated to the hot-plug function, all eight bits of this field are valid. When a
                                                                 *   4bit GPIO group is allocated to the hot-plug function, only the lower four bits of this
                                                                 *   field are valid. When valid, if bitN of this field is set, the sub-element of the hot-plug
                                                                 *   function that is mapped to the Nth IO bit of the byte/nibble is disabled. Once disabled
                                                                 *   via this field, the associated pin is made available for other potential purposes such
                                                                 *   as a RESET or GPIO capability.
                                                                 */
  IN      UINT32                    PortMapping            :5;  ///< Logical Bridge Id for port mapping
  IN      UINT32                    Reserved1              :1;  ///< Reserved for future use
  IN      UINT32                    I2CBusSegmentExt       :2;  /**< I2C Bus Segment Ext : optional upper bits for additional I2C switches
                                                                   *  This field is populated with bits 4:3 of I2CBusSegment (above) if present.
                                                                   *  @li @b 01000 - PCA9545, address=01, downstream I2C bus=11
                                                                   *  @li @b 01001 - PCA9545, address=02, downstream I2C bus=00
                                                                   *  @li @b 01010 - PCA9545, address=02, downstream I2C bus=01
                                                                   *  @li @b 01011 - PCA9545, address=02, downstream I2C bus=10
                                                                   *  @li @b 01100 - PCA9545, address=02, downstream I2C bus=11
                                                                   *  @li @b 01101 - PCA9545, address=03, downstream I2C bus=00
                                                                   *  @li @b 01110 - PCA9545, address=03, downstream I2C bus=01
                                                                   *  @li @b 01111 - PCA9545, address=03, downstream I2C bus=10
                                                                   *  @li @b 10000 - PCA9545, address=03, downstream I2C bus=11
                                                                   */
} PCIE_HOTPLUG_FUNCTION;


// --------------------------------------------------------------------------------------------------
// PCIE_HOTPLUG_RESET Descriptor
// When PCIE_HOTPLUG_MAPPING<slotNum>.ResetDescriptorVld is set to 0, reset  functionality is not tied to the hot-plug slot and must be furnished in
// some other manner. However, when the ResetDescriptorVld bit-field is set to 1, the RESET descriptor for the <slotNum> link specifies the exact pin
// within the hot-plug I2C subsystem onto which the reset functionality is mapped, enabling control of the reset functionality through a BIOS
// accessible API.

/// PCIe Hotplug Reset Descriptor
typedef struct  {
  IN      UINT32                    Reserved0              :3;  ///< Reserved for future use
  IN      UINT32                    I2CGpioByteMapping     :3;  /**< I2C GPIO IO Byte Mapping : indicates which IO byte of the I2C GPIO device is used for the
                                                                 *   hot-plug signals associated with this descriptor.
                                                                 */
  IN      UINT32                    Reserved1              :2;  ///< Reserved for future use
  IN      UINT32                    I2CGpioDeviceMapping   :3;  /**< I2C GPIO Device Mapping : indicates the lower three bits of the I2C address for the
                                                                 *   I2C GPIO device that is used to host the hot-plug signals associated with this descriptor.
                                                                 */
  IN      UINT32                    I2CDeviceType          :2;  /**< I2C Device Type : indicates which of three I2C GPIO devices is used to host the hot-plug
                                                                 *   signals associated with this descriptor.
                                                                 *  @li @b 00 - PCA9539 address and register map; in support of legacy hot-plug implementations
                                                                 *  @li @b 01 - PCA9535 address and register map; in support of newer hot-plug implementations
                                                                 *  @li @b 10 - PCA9506 address and register map; in support of high slot-capacity implementations
                                                                 *  @li @b 11 - reserved
                                                                 *   Note, PCA9535 and PCA9506 devices may be intermixed on the I2C interface.
                                                                 *   However, due to common addressing, a combined total of eight devices may be populated.
                                                                 */
  IN      UINT32                    I2CBusSegment          :3;  /**< I2C Bus Segment :  in the context of an I2C subsystem constructed with PCA9545 I2C switches,
                                                                 *   this field specifies the downstream I2C bus segment, on one of two PCA9545 switches, on which
                                                                 *   the target I2C GPIO device is located. However, for I2C topologies that are not constructed
                                                                 *   with any PCA9545 devices, one value is reserved to identify that the I2C GPIO device does
                                                                 *   not reside behind any PCA9454 I2C switch.
                                                                 *  @li @b 000 - PCA9545, address=00, downstream I2C bus=00
                                                                 *  @li @b 001 - PCA9545, address=00, downstream I2C bus=01
                                                                 *  @li @b 010 - PCA9545, address=00, downstream I2C bus=10
                                                                 *  @li @b 011 - PCA9545, address=00, downstream I2C bus=11
                                                                 *  @li @b 100 - PCA9545, address=01, downstream I2C bus=00
                                                                 *  @li @b 101 - PCA9545, address=01, downstream I2C bus=01
                                                                 *  @li @b 110 - PCA9545, address=01, downstream I2C bus=10
                                                                 *  @li @b 111 - no PCA9545; I2C bus directly connected to APU socket
                                                                 */
  IN      UINT32                    ResetSelect            :8;  /**< Reset Select : this bit-field is used to specify which pin within the selected I2C IO byte
                                                                 *   (identified by the other fields in this descriptor) is used for the reset function associated
                                                                 *   with the <slotNum> PCIe link. Since reset is a singular function, only one bit in this field
                                                                 *   may be set to one. When the Nth bit of this field is set to 1, the Nth bit of the selected I2C
                                                                 *   IO byte serves as the platform reset signal for the associated PCIe link.
                                                                 *   Note, although this descriptor identifies a single bit, this field has been defined in this
                                                                 *   manner so as to be consistent with both the "FunctionMask" field in the FUNCTION descriptor
                                                                 *   and the "GPIOSelect" field in the GPIO descriptor. 
                                                                 */
  IN      UINT32                    Reserved2              :6;  ///< Reserved for future use
  IN      UINT32                    I2CBusSegmentExt       :2;  ///< I2C Bus Segment Ext
} PCIE_HOTPLUG_RESET;


// --------------------------------------------------------------------------------------------------
// SMU_GENERIC_GPIO Descriptor
// In order to provide AMD's customers with flexibility to customize and differentiate their own hot-plug deployments, the hot-plug a facility incorporates
// generalized GPIO extensibility through the SMU-managed I2C subsystem. Through the use of GPIO descriptors, generalized GPIO pins can be allocated within
// the hot-plug I2C subsystem, and are exposed to the platform software through a BIOS accessible API. For each I2C IO bit that is mapped into the generalized
// GPIO facility, the bit is capable of operating as either:
//   - an output, used to drive a platform level signal
//   - an input, used to ascertain platform-specific information
//   - a level-sensitive interrupt input, used to signal platform events to the platform BIOS or other system software
// Within this GPIO facility, the I2C GPIOs can be conceptually tied to the per-slot functionality, or can even be stand-alone GPIO functions for purposes
// unrelated to PCIe hot-plug. The former association is accomplished by setting PCIE_HOTPLUG_MAPPING<slotNum>.GPIODescriptorVld = 1, in which case the
// SMU_GENERIC_GPIO<slotNum> descriptor is used for GPIO functionality associated with the <slotNum> hot-plug slot.
// Otherwise, those SMU_GENERIC_GPIO<descNum> descriptors not allocated to the MAPPING registers can be used for potentially orthogonal purposes.

/// General Purpose GPIO Descriptor
typedef struct  {
  IN      UINT32                    Reserved0              :3;  ///< Reserved for future use
  IN      UINT32                    I2CGpioByteMapping     :3;  /**< I2C GPIO IO Byte Mapping : indicates which IO byte of the I2C GPIO device is used for the
                                                                 *   hot-plug signals associated with this descriptor.
                                                                 */
  IN      UINT32                    Reserved1              :2;  ///< Reserved for future use
  IN      UINT32                    I2CGpioDeviceMapping   :3;  /**< I2C GPIO Device Mapping : indicates the lower three bits of the I2C address for the
                                                                 *   I2C GPIO device that is used to host the hot-plug signals associated with this descriptor.
                                                                 */
  IN      UINT32                    I2CDeviceType          :2;  /**< I2C Device Type : indicates which of three I2C GPIO devices is used to host the hot-plug
                                                                 *   signals associated with this descriptor.
                                                                 *  @li @b 00 - PCA9539 address and register map; in support of legacy hot-plug implementations
                                                                 *  @li @b 01 - PCA9535 address and register map; in support of newer hot-plug implementations
                                                                 *  @li @b 10 - PCA9506 address and register map; in support of high slot-capacity implementations
                                                                 *  @li @b 11 - reserved
                                                                 *   Note, PCA9535 and PCA9506 devices may be intermixed on the I2C interface.
                                                                 *   However, due to common addressing, a combined total of eight devices may be populated.
                                                                 */
  IN      UINT32                    I2CBusSegment          :3;  /**< I2C Bus Segment :  in the context of an I2C subsystem constructed with PCA9545 I2C switches,
                                                                 *   this field specifies the downstream I2C bus segment, on one of two PCA9545 switches, on which
                                                                 *   the target I2C GPIO device is located. However, for I2C topologies that are not constructed
                                                                 *   with any PCA9545 devices, one value is reserved to identify that the I2C GPIO device does
                                                                 *   not reside behind any PCA9454 I2C switch.
                                                                 *  @li @b 000 - PCA9545, address=00, downstream I2C bus=00
                                                                 *  @li @b 001 - PCA9545, address=00, downstream I2C bus=01
                                                                 *  @li @b 010 - PCA9545, address=00, downstream I2C bus=10
                                                                 *  @li @b 011 - PCA9545, address=00, downstream I2C bus=11
                                                                 *  @li @b 100 - PCA9545, address=01, downstream I2C bus=00
                                                                 *  @li @b 101 - PCA9545, address=01, downstream I2C bus=01
                                                                 *  @li @b 110 - PCA9545, address=01, downstream I2C bus=10
                                                                 *  @li @b 111 - no PCA9545; I2C bus directly connected to APU socket
                                                                 */
  IN      UINT32                    GpioSelect             :8;  /**< GPIO Select : this bit-field is used to specify which pin within the selected I2C IO byte
                                                                 *   (identified by the other fields in this descriptor) is used for GPIO functionality. For each
                                                                 *   bit that is set to 1, the corresponding pin on the I2C IO Byte (selected by the remaining
                                                                 *   fields in this descriptor) are assigned to GPIO functionality. Any population of bits, from
                                                                 *   one to eight, can be selected using this field. 
                                                                 */
  IN      UINT32                    GpioInterruptEnable    :8;  /**< GPIO Interrupt Enable : each bit of this field acts as an interrupt enable for the
                                                                 *   corresponding bit in the I2C IO Byte pointed to by this descriptor. When the bit in the
                                                                 *   IO Byte is used as a GPIO, and it used as an input, the corresponding enable bit determines
                                                                 *   whether an SMI/SCI interrupt will be generated in response to a change in the input value.
                                                                 *   When the corresponding mask bit is '1', an SCI/SMI interrupt will be generated as a consequence of
                                                                 *   a change on the I2C GPIO bit. When the corresponding mask bit is '0', no interrupt will be generated.
                                                                 */
} PCIE_HOTPLUG_GPIO;

/// Engine Configuration
typedef struct {
  IN       UINT8                StartLane;                /**< Start Lane ID (in reversed configuration StartLane > EndLane)
                                                           * This value should correspond exactly to the definition the PCIe topology
                                                           */
  IN       UINT8                EndLane;                  /**< End lane ID (in reversed configuration StartLane > EndLane)
                                                           * This value should correspond exactly to the definition the PCIe topology
                                                           */
  IN       UINT8                SocketNumber;             ///< Socket Number of this port
  IN       UINT8                SlotNumber;               ///< Unique identifier for the physical slot number of this port
} HOTPLUG_ENGINE_DATA;


typedef struct {
  UINT32                        Flags;
  HOTPLUG_ENGINE_DATA           Engine;
  PCIE_HOTPLUG_MAPPING          Mapping;
  PCIE_HOTPLUG_FUNCTION         Function;
  PCIE_HOTPLUG_RESET            Reset;
  PCIE_HOTPLUG_GPIO             Gpio;
} HOTPLUG_DESCRIPTOR;


// Macro for statically initializing various structures
#define  HOTPLUG_ENGINE_DATA_INITIALIZER(mStartLane, mEndLane, mSocketNumber, mSlotNumber) {mStartLane, mEndLane, mSocketNumber, mSlotNumber},

#define  PCIE_HOTPLUG_INITIALIZER_MAPPING(mHotPlugFormat, mGpioDescriptorValid, mResetDescriptorValid, mPortActive, mMasterSlaveAPU, mDieNumber, \
                                          mAlternateSlotNumber, mPrimarySecondaryLink) \
                                         {mHotPlugFormat, 1, mGpioDescriptorValid, mResetDescriptorValid, mPortActive, mMasterSlaveAPU, mDieNumber, \
                                          0, 0, 0, mAlternateSlotNumber, mPrimarySecondaryLink, 0},

#define  PCIE_HOTPLUG_INITIALIZER_FUNCTION(mI2CGpioBitSelector, mI2CGpioByteMapping, mAddrExt, mI2CGpioDeviceMapping, mI2CDeviceType, mI2CBusSegment, mFunctionMask) \
                                          {mI2CGpioBitSelector, mI2CGpioByteMapping, mAddrExt, mI2CGpioDeviceMapping, mI2CDeviceType, mI2CBusSegment & 7, mFunctionMask, 0, 0, mI2CBusSegment >> 3},

#define  PCIE_HOTPLUG_INITIALIZER_RESET(mI2CGpioByteMapping, mI2CGpioDeviceMapping, mI2CDeviceType, mI2CBusSegment, mResetSelect) \
                                       {0, mI2CGpioByteMapping, 0, mI2CGpioDeviceMapping, mI2CDeviceType, mI2CBusSegment, mResetSelect, 0, 0},

#define  PCIE_HOTPLUG_INITIALIZER_NO_RESET() {0, 0, 0, 0, 0, 0, 0, 0, 0},

#define  PCIE_HOTPLUG_INITIALIZER_GPIO(mI2CGpioByteMapping, mI2CGpioDeviceMapping, mI2CDeviceType, mI2CBusSegment, mGpioSelect, mGpioInterruptEnable) \
                                      {0, mI2CGpioByteMapping, 0, mI2CGpioDeviceMapping, mI2CDeviceType, mI2CBusSegment, mGpioSelect, mGpioInterruptEnable}

#define  PCIE_HOTPLUG_INITIALIZER_NO_GPIO() {0, 0, 0, 0, 0, 0, 0, 0}

// bitmasks for GPIO pins based on hotplug format

#define PCIE_HOTPLUG_EXPRESSMODULE_PRESENT_    0x01
#define PCIE_HOTPLUG_EXPRESSMODULE_PWRFLT_     0x02
#define PCIE_HOTPLUG_EXPRESSMODULE_ATNSW_      0x04
#define PCIE_HOTPLUG_EXPRESSMODULE_EMILS       0x08
#define PCIE_HOTPLUG_EXPRESSMODULE_PWREN_      0x10
#define PCIE_HOTPLUG_EXPRESSMODULE_ATNLED      0x20
#define PCIE_HOTPLUG_EXPRESSMODULE_PWRLED      0x40
#define PCIE_HOTPLUG_EXPRESSMODULE_EMIL        0x80

#define PCIE_HOTPLUG_EXPRESSMODULE_B_ATNLED    0x01
#define PCIE_HOTPLUG_EXPRESSMODULE_B_PWRLED    0x02
#define PCIE_HOTPLUG_EXPRESSMODULE_B_PWREN_    0x04
#define PCIE_HOTPLUG_EXPRESSMODULE_B_ATNSW_    0x08
#define PCIE_HOTPLUG_EXPRESSMODULE_B_PRESENT_  0x10
#define PCIE_HOTPLUG_EXPRESSMODULE_B_PWRFLT_   0x20
#define PCIE_HOTPLUG_EXPRESSMODULE_B_EMILS     0x40
#define PCIE_HOTPLUG_EXPRESSMODULE_B_EMIL      0x80

#define PCIE_HOTPLUG_EXPRESS_SSD_PRESENT_      0x10
#define PCIE_HOTPLUG_EXPRESS_SSD_IFDET_        0x20
#define PCIE_HOTPLUG_EXPRESS_SSD_DUALEN_       0x40


#endif // _AGESA_H_

