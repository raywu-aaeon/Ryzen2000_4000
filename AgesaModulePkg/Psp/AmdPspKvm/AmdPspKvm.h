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

#ifndef _AMD_PSP_KVM_H_
#define _AMD_PSP_KVM_H_

#include <FrameworkDxe.h>
#include <IndustryStandard/pci22.h>
#include <Protocol/SimpleTextIn.h>
#include <Protocol/SimpleTextInEx.h>
#include <Protocol/SimplePointer.h>
#include <Protocol/AbsolutePointer.h>
#include <Protocol/PciIo.h>
#include <Protocol/DevicePath.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/TimerLib.h>
#include <Library/PcdLib.h>
#include <Library/HobLib.h>
#include <Library/PciLib.h>
#include <Library/DebugLib.h>


#include <AGESA.h>
#include <Filecode.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdPspBaseLibV2.h>
#include <Library/AmdPspMboxLibV2.h>
#include <Protocol/AmdPspKvmServiceProtocol.h>


#include "AmdPspKvmKeyboard.h"
#include "AmdPspKvmMouse.h"

#define AMD_PSP_KVM_DEV_SIGNATURE       SIGNATURE_32 ('p', 'k', 'v', 'm')

typedef
EFI_STATUS
(EFIAPI *AMD_PSP_KVM_DEV_GET_MMIO_BASE) (
  IN     EFI_HANDLE         *KvmDevHandle,
  IN OUT UINT64             *NetCardMmioBase
  );

typedef
EFI_STATUS
(EFIAPI *AMD_PSP_KVM_DEV_GET_MMIO_SIZE) (
  IN     EFI_HANDLE           *KvmDevHandle,
  IN OUT UINT32               *NetCardMmioSize
  );

typedef
EFI_STATUS
(EFIAPI *AMD_PSP_KVM_REG_FIELD_ACCESS) (
  IN     EFI_HANDLE         *KvmDevHandle,
  OUT    UINT32             *value
  );

typedef struct {
  AMD_PSP_KVM_DEV_GET_MMIO_BASE  GetMmioBase;
  AMD_PSP_KVM_DEV_GET_MMIO_SIZE  GetMmioSize;
  AMD_PSP_KVM_REG_FIELD_ACCESS   ReadKvmRequest;
  AMD_PSP_KVM_REG_FIELD_ACCESS   WriteKvmRequest;
  AMD_PSP_KVM_REG_FIELD_ACCESS   ReadKvmSessionProgress;
  AMD_PSP_KVM_REG_FIELD_ACCESS   WriteKvmSessionProgress;
} KVM_DEV_PROTOCOL;

typedef struct {
  UINT32                                    VendorID;
  UINT32                                    DeviceID;
  KVM_DEV_PROTOCOL                          *KvmDevProtocol;
} KVM_DEV_INFO;

typedef struct {
  UINTN                               Signature;
  KVM_KEYBOARD_CONSOLE_IN_DEV         *AmdPspKvmKbDev;
  KVM_MOUSE_DEV                       *AmdPspKvmMsDev;
  EFI_UNICODE_STRING_TABLE            *ControllerNameTable;
  EFI_HANDLE                          *KvmDevHandle;

  UINT64                              NetCardMmioBase; ///< NetCard PCIE MMIO base
  UINT32                              NetCardMmioSize; ///< NetCard PCIE MMIO base
  UINT32                              KvmRequest;      ///< Kvm Request status
  UINT64                              KvmDmaAddr;      ///< Kvm Dma buffer base
  UINT64                              KvmEntryAddress; ///< Kvm binary entry address
  UINT32                              KvmEntrySize;    ///< Kvm binary size
  KVM_DEV_PROTOCOL                    *KvmDevProtocol;      ///< Kvm Register offset
} AMD_PSP_KVM_DEV;

typedef union {
  struct {
    UINT32  Reserved_23_0:24;       ///< [23:0] Reserved
    UINT32  KvmRequest:1;           ///< [24] KvmRequest
    UINT32  Reserved_27_25:3;       ///< [27:25] Reserved
    UINT32  KvmSessionProgress:1;   ///< [28] KvmSessionProgress
    UINT32  Reserved_31_29:3;       ///< [31:29] Reserved
  } BrcmField; // UINT32
  struct {
    UINT8   KvmRequest:1;           ///< [0] KVMRequest
    UINT8   KvmSessionProgress:1;   ///< [1] KvmSessionProgress
    UINT8   Reserved_7_2:6;         ///< [7:2] KvmRequest
  } RtkField; // UINT8
  UINT32 Value;
} KVM_STATUS_REG;

typedef enum {
  KVM_FIELD_REQUEST,
  KVM_FIELD_SESSION
} KVM_REG_FIELD;

typedef struct {
  UINT32                                    NetCardMmioBaseLo;              ///< NetCard PCIE MMIO base
  UINT32                                    NetCardMmioBaseHi;              ///< NetCard PCIE MMIO base
  UINT32                                    NetCardMmioSize;              ///< NetCard PCIE MMIO base
  UINT32                                    FrameBufferBaseLo;              ///< Frame buffer base
  UINT32                                    FrameBufferBaseHi;              ///< Frame buffer base
  UINT32                                    FrameBufferSize;              ///< Frame buffer size
  UINT32                                    KvmKbBufferAddrLo;            ///< Low 32 Bit of KVM Keyboard Buffer Addr
  UINT32                                    KvmKbBufferAddrHi;            ///< High 32 Bit of KVM Keyboard Buffer Addr
  UINT32                                    KvmKbBufferSize;              ///< KVM Keyboard Buffer Size
  UINT32                                    KvmMsBufferAddrLo;            ///< Low 32 Bit of KVM Mouse Buffer Addr
  UINT32                                    KvmMsBufferAddrHi;            ///< High 32 Bit of KVM Mouse Buffer Addr
  UINT32                                    KvmMsBufferSize;              ///< KVM Mouse Buffer Size
  UINT32                                    KvmNicCoherencyBufferAddrLo;  ///< Low 32 Bit of KVM NicCoherencyBuffer Addr
  UINT32                                    KvmNicCoherencyBufferAddrHi;  ///< High 32 Bit of KVM NicCoherencyBuffer Addr
  UINT32                                    KvmNicCoherencyBufferSize;    ///< KVM NicCoherencyBuffer Size
  UINT32                                    KvmMouseProtocolSelection;    ///< 0: Absolute Pointer Protocol; 1: Simple Pointer Protocol
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION      GModeInfo;                    ///<Graphics mode info
  KVM_IP_INFO                               KvmIpInfo;
} KVM_OS_PARAM;

typedef union {
  struct {
    UINT32  VendorID:16;
    UINT32  DeviceID:16;
  } Field;
  UINT32 VendorDeviceID;
} KVM_DEVID;

#define KVM_BCM_STATUS_REG_OFFSET  0x8
#define KVM_RTK_STATUS_REG_OFFSET  0x0C

#define RTK_REG_WRITE_BASE_INDEX   0x80421100
#define RTK_REG_READ_BASE_INDEX    0x00421100
#define RTK_REG_INDEX_REG_OFFSET   0x74
#define RTK_REG_DATA_REG_OFFSET    0x70

#define AMD_PSP_KVM_DEV_FROM_THIS(a)  CR (a, AMD_PSP_KVM_DEV, AmdPspKvmKbDev, AMD_PSP_KVM_DEV_SIGNATURE)

#define AMD_RV_PSP_VID        0x1022
#define AMD_RV_PSP_DID        0x15DF
#define AMD_PR_PSP_VID        0x1022
#define AMD_PR_PSP_DID        0x1456

#define KVM_UNSUPPORTED       0x0
#define BCM_VID               0x14E4
#define BCM5762_DID           0x1687
#define RTK_VID               0x10EC
#define RTK8168_DID           0x8168
#define BCM_5762_DEVID        0x168714E4ul
#define BCM5762_BAR0_OFFSET   0x10

#define KVM_ENGINE_BINARY_OFFSET (5 * 1024 * 1024)

#define KVM_ABSOLUTE_MOUSE_PROTOCOL  0x0
#define KVM_SIMPLE_MOUSE_PROTOCOL  0x1

// #define ASSERT_EFI_ERROR(x) ASSERT (!EFI_ERROR (x))

#define AMD_PSP_KVM_SERVICE_PROTOCOL_VERSION_1 (0x00000001ul)
#define KVM_BUFFER_ALIGNMENT     0x8000000ul // Must be 128M aligned

extern KB_RING_BUFFER   *mKbRingBuffer;
extern KVM_MOUSE_BUFFER *mMRingBuffer;

EFI_STATUS
EFIAPI
AmdPspKvmDriverSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
EFIAPI
AmdPspKvmDriverStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
EFIAPI
AmdPspKvmDriverStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  );

EFI_STATUS
EFIAPI
AmdPspKvmComponentNameGetDriverName (
  IN  EFI_COMPONENT_NAME_PROTOCOL  *This,
  IN  CHAR8                        *Language,
  OUT CHAR16                       **DriverName
  );


EFI_STATUS
EFIAPI
AmdPspKvmComponentNameGetControllerName (
  IN  EFI_COMPONENT_NAME_PROTOCOL                     *This,
  IN  EFI_HANDLE                                      ControllerHandle,
  IN  EFI_HANDLE                                      ChildHandle        OPTIONAL,
  IN  CHAR8                                           *Language,
  OUT CHAR16                                          **ControllerName
  );

///Get value of KvmRequest through PCI address
EFI_STATUS
AmdPspKvmGetRequestPciAddr (
  IN     PCI_ADDR    PciAddr,
  IN     UINT32                *KvmRequest
  );

///Get value of KvmRequest
EFI_STATUS
AmdPspKvmGetRequest (
  IN     UINT32                *KvmRequest
  );

///Set value of KvmRequest
EFI_STATUS
AmdPspKvmSetRequest (
  IN     UINT32                *KvmRequest
  );

///Get value of KvmSessionProgress
EFI_STATUS
AmdPspKvmGetSessionProgress (
  IN     UINT32                *KvmSessionProgress
  );

///Set value of KvmSessionProgress
EFI_STATUS
AmdPspKvmSetSessionProgress (
  IN     UINT32                *KvmSessionProgress
  );

EFI_STATUS
AmdPspKvmInitiateKvm (
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *ModeInfo,
  IN KVM_IP_INFO                       *KvmIpInfo
  );

EFI_STATUS
AmdPspKvmTerminateKvm (
  VOID
  );

EFI_STATUS
AmdPspKvmRetrieveSmbiosTable (
  IN    UINT8                    KvmEnabled,
  OUT   SMBIOS_TABLE_TYPEA0    **SmbiosTableTypeA0
  );

EFI_STATUS
GetBrcmMmioBase (
  IN     EFI_HANDLE         *KvmDevHandle,
  IN OUT UINT64             *NetCardMmioBase
  );

EFI_STATUS
GetBrcmMmioSize (
  IN     EFI_HANDLE         *KvmDevHandle,
  IN OUT UINT32             *NetCardMmioSize
  );

EFI_STATUS
GetBrcmBaseAddr (
  IN     EFI_HANDLE         *KvmDevHandle,
  IN OUT UINT64             *KvmBaseAddr
  );

EFI_STATUS
ReadBrcmKvmReg (
  IN     EFI_HANDLE         *KvmDevHandle,
  OUT    UINT32             *value
  );

EFI_STATUS
WriteBrcmKvmReg (
  IN     EFI_HANDLE         *KvmDevHandle,
  IN     UINT32             *value
  );

EFI_STATUS
ReadBrcmKvmRequest (
  IN     EFI_HANDLE         *KvmDevHandle,
  OUT    UINT32             *value
  );

EFI_STATUS
WriteBrcmKvmRequest (
  IN     EFI_HANDLE         *KvmDevHandle,
  OUT    UINT32             *value
  );

EFI_STATUS
ReadBrcmKvmSessionProgress (
  IN     EFI_HANDLE         *KvmDevHandle,
  OUT    UINT32             *value
  );

EFI_STATUS
WriteBrcmKvmSessionProgress (
  IN     EFI_HANDLE         *KvmDevHandle,
  OUT    UINT32             *value
  );

EFI_STATUS
GetRtkMmioBase (
  IN     EFI_HANDLE         *KvmDevHandle,
  IN OUT UINT64             *NetCardMmioBase
  );

EFI_STATUS
GetRtkMmioSize (
  IN     EFI_HANDLE         *KvmDevHandle,
  IN OUT UINT32             *NetCardMmioSize
  );

EFI_STATUS
GetRtkBaseAddr (
  IN     EFI_HANDLE         *KvmDevHandle,
  IN OUT UINT64             *KvmBaseAddr
  );

EFI_STATUS
ReadRtkKvmReg (
  IN     EFI_HANDLE         *KvmDevHandle,
  OUT    UINT32             *value
  );

EFI_STATUS
WriteRtkKvmReg (
  IN     EFI_HANDLE         *KvmDevHandle,
  IN     UINT32             *value
  );

EFI_STATUS
ReadRtkKvmRequest (
  IN     EFI_HANDLE         *KvmDevHandle,
  OUT    UINT32             *value
  );

EFI_STATUS
WriteRtkKvmRequest (
  IN     EFI_HANDLE         *KvmDevHandle,
  OUT    UINT32             *value
  );

EFI_STATUS
ReadRtkKvmSessionProgress (
  IN     EFI_HANDLE         *KvmDevHandle,
  OUT    UINT32             *value
  );

EFI_STATUS
WriteRtkKvmSessionProgress (
  IN     EFI_HANDLE         *KvmDevHandle,
  OUT    UINT32             *value
  );

#endif

