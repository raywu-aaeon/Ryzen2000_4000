/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Library
 *
 * Contains interface to the AMD S3 save library
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Lib
 * @e \$Revision: 312770 $   @e \$Date: 2015-02-11 13:24:42 +0800 (Wed, 11 Feb 2015) $
 *
 */
/*
 ******************************************************************************
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
#include <PiDxe.h>
#include <Guid/EventGroup.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/S3BootScriptLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/SmmCommunication.h>
#include <Protocol/DxeSmmReadyToLock.h>
#include "AMD.h"
#include "Library/AmdBaseLib.h"
#include "Library/AmdS3SaveLib.h"
#include "Library/IdsLib.h"
#include "AmdS3SaveLibData.h"
#include "AmdSmmCommunication.h"
#include <Library/PciLib.h>
#include "Filecode.h"
#define FILECODE LIBRARY_AMDS3SAVELIB_S3SAVE_AMDS3SAVELIB_FILECODE

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */
UINT64
STATIC
AmdS3GetDataFromPtr (
  IN       ACCESS_WIDTH AccessWidth,
  IN       VOID         *Data
  );

S3_BOOT_SCRIPT_LIB_WIDTH
STATIC
AmdS3GetAccessWidth (
  IN       ACCESS_WIDTH AccessWidth
  );

AGESA_STATUS
AmdS3SaveCacheScriptData (
  IN      UINT16      OpCode,
  IN      ...
  );
/*----------------------------------------------------------------------------------------
 *                         G L O B A L        D A T A
 *----------------------------------------------------------------------------------------
 */
AMD_S3_LIB_PRIVATE_DATA *mAmdS3LibPrivateData = NULL;
EFI_EVENT                mS3ScriptLockEvent = NULL;
EFI_EVENT                mCloseTableEvent = NULL;
UINT32 mMMIOSize = 0;
UINT64 mMMIOAddress = 0;
/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
AGESA_STATUS
AmdS3IoWrite (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Value,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  AGESA_STATUS  AgesaStatus;

  LibAmdIoWrite (Width, (UINT16) Address, Value, StdHeader);
  AgesaStatus = AmdS3SaveScriptIoWrite (Width, Address, Value);

  return AgesaStatus;
}

AGESA_STATUS
AmdS3IoRMW (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Data,
  IN       VOID          *DataMask,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  AGESA_STATUS  AgesaStatus;

  LibAmdIoRMW (Width, (UINT16) Address, Data, DataMask, StdHeader);
  AgesaStatus = AmdS3SaveScriptIoRMW (Width, Address, Data, DataMask);

  return AgesaStatus;
}

AGESA_STATUS
AmdS3IoPoll (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Data,
  IN       VOID          *DataMask,
  IN       UINT64        Delay,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  AGESA_STATUS  AgesaStatus;

  LibAmdIoPoll (Width, (UINT16) Address, Data, DataMask, Delay, StdHeader);
  AgesaStatus = AmdS3SaveScriptIoPoll (Width, Address, Data, DataMask, Delay);

  return AgesaStatus;
}

AGESA_STATUS
AmdS3MemWrite (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Value,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  AGESA_STATUS  AgesaStatus;

  LibAmdMemWrite (Width, Address, Value, StdHeader);
  AgesaStatus = AmdS3SaveScriptMemWrite (Width, Address, Value);

  return AgesaStatus;
}

AGESA_STATUS
AmdS3MemRMW (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Data,
  IN       VOID          *DataMask,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  AGESA_STATUS  AgesaStatus;

  LibAmdMemRMW (Width, Address, Data, DataMask, StdHeader);
  AgesaStatus = AmdS3SaveScriptMemRMW (Width, Address, Data, DataMask);

  return AgesaStatus;
}

AGESA_STATUS
AmdS3MemPoll (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Data,
  IN       VOID          *DataMask,
  IN       UINT64        Delay,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  AGESA_STATUS  AgesaStatus;

  LibAmdMemPoll (Width, Address, Data, DataMask, Delay, StdHeader);
  AgesaStatus = AmdS3SaveScriptMemPoll (Width, Address, Data, DataMask, Delay);

  return AgesaStatus;
}

AGESA_STATUS
AmdS3PciWrite (
  IN       ACCESS_WIDTH  Width,
  IN       UINTN         PciAddress,
  IN       VOID          *Value,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  AGESA_STATUS  AgesaStatus;

  switch (Width) {
  case AccessWidth8:
  case AccessS3SaveWidth8:
    PciWrite8 (PciAddress, *((UINT8 *) Value));
    break;
  case AccessWidth16:
  case AccessS3SaveWidth16:
    PciWrite16 (PciAddress, *((UINT16 *) Value));
    break;
  case AccessWidth32:
  case AccessS3SaveWidth32:
    PciWrite32 (PciAddress, *((UINT32 *) Value));
    break;
  default:
    IDS_ERROR_TRAP;
  }

  AgesaStatus = AmdS3SaveScriptPciWrite (Width, PciAddress, Value);

  return AgesaStatus;
}

AGESA_STATUS
AmdS3PciRMW (
  IN       ACCESS_WIDTH  Width,
  IN       UINTN         PciAddress,
  IN       VOID          *Data,
  IN       VOID          *DataMask,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT32  TempData;
  UINT32  TempMask;
  AGESA_STATUS  AgesaStatus;

  LibAmdGetDataFromPtr (Width, Data,  DataMask, &TempData, &TempMask);

  switch (Width) {
  case AccessWidth8:
  case AccessS3SaveWidth8:
    PciAndThenOr8 (PciAddress, (UINT8) (~TempMask), (UINT8) TempData);
    break;
  case AccessWidth16:
  case AccessS3SaveWidth16:
    PciAndThenOr16 (PciAddress, (UINT16) (~TempMask), (UINT16) TempData);
    break;
  case AccessWidth32:
  case AccessS3SaveWidth32:
    PciAndThenOr32 (PciAddress, (~TempMask), TempData);
    break;
  default:
    IDS_ERROR_TRAP;
  }

  AgesaStatus = AmdS3SaveScriptPciRMW (Width, PciAddress, Data, DataMask);

  return AgesaStatus;
}

AGESA_STATUS
AmdS3SaveScriptIoWrite (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Value
  )
{
  RETURN_STATUS CalledStatus;
  AGESA_STATUS  AgesaStatus;

  if (mAmdS3LibPrivateData->S3ScriptLock == FALSE) {
    CalledStatus = S3BootScriptSaveIoWrite (AmdS3GetAccessWidth (Width), Address, 1, Value);
    AgesaStatus  = (CalledStatus == RETURN_SUCCESS) ? AGESA_SUCCESS : AGESA_ERROR;
  } else {
    AgesaStatus = AmdS3SaveCacheScriptData (AMD_S3LIB_BOOT_SCRIPT_IO_WRITE_OP,
                                            AmdS3GetAccessWidth (Width),
                                            Address,
                                            AmdS3GetDataFromPtr (Width, Value));
  }
  return AgesaStatus;
}

AGESA_STATUS
AmdS3SaveScriptIoRMW (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Data,
  IN       VOID          *DataMask
  )
{
  UINT64 DataMaskTemp;
  RETURN_STATUS CalledStatus;
  AGESA_STATUS  AgesaStatus;

  DataMaskTemp = AmdS3GetDataFromPtr (Width, DataMask);
  DataMaskTemp = ~DataMaskTemp;

  if (mAmdS3LibPrivateData->S3ScriptLock == FALSE) {
    CalledStatus = S3BootScriptSaveIoReadWrite (AmdS3GetAccessWidth (Width), Address, Data, &DataMaskTemp);
    AgesaStatus  = (CalledStatus == RETURN_SUCCESS) ? AGESA_SUCCESS : AGESA_ERROR;
  } else {
    AgesaStatus = AmdS3SaveCacheScriptData (AMD_S3LIB_BOOT_SCRIPT_IO_RMW_OP,
                                            AmdS3GetAccessWidth (Width),
                                            Address,
                                            AmdS3GetDataFromPtr (Width, Data),
                                            DataMaskTemp);
  }
  return AgesaStatus;
}

AGESA_STATUS
AmdS3SaveScriptIoPoll (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Data,
  IN       VOID          *DataMask,
  IN       UINT64        Delay
  )
{
  RETURN_STATUS CalledStatus;
  AGESA_STATUS  AgesaStatus;

  if (mAmdS3LibPrivateData->S3ScriptLock == FALSE) {
    CalledStatus = S3BootScriptSaveIoPoll (AmdS3GetAccessWidth (Width), Address, Data, DataMask, Delay);
    AgesaStatus  = (CalledStatus == RETURN_SUCCESS) ? AGESA_SUCCESS : AGESA_ERROR;
  } else {
    AgesaStatus = AmdS3SaveCacheScriptData (AMD_S3LIB_BOOT_SCRIPT_IO_POLL_OP,
                                            AmdS3GetAccessWidth (Width), Address,
                                            AmdS3GetDataFromPtr (Width, Data),
                                            AmdS3GetDataFromPtr (Width, DataMask),
                                            Delay);
  }
  return AgesaStatus;
}

AGESA_STATUS
AmdS3SaveScriptMemWrite (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Value
  )
{
  RETURN_STATUS CalledStatus;
  AGESA_STATUS  AgesaStatus;

  if (mAmdS3LibPrivateData->S3ScriptLock == FALSE) {
    CalledStatus = S3BootScriptSaveMemWrite (AmdS3GetAccessWidth (Width), Address, 1, Value);
    AgesaStatus  = (CalledStatus == RETURN_SUCCESS) ? AGESA_SUCCESS : AGESA_ERROR;
  } else {
    AgesaStatus = AmdS3SaveCacheScriptData (AMD_S3LIB_BOOT_SCRIPT_MEM_WRITE_OP,
                                            AmdS3GetAccessWidth (Width),
                                            Address,
                                            AmdS3GetDataFromPtr (Width, Value));
  }

  return AgesaStatus;
}

AGESA_STATUS
AmdS3SaveScriptMemRMW (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Data,
  IN       VOID          *DataMask
  )
{
  UINT64 DataMaskTemp;
  RETURN_STATUS CalledStatus;
  AGESA_STATUS  AgesaStatus;

  DataMaskTemp = AmdS3GetDataFromPtr (Width, DataMask);
  DataMaskTemp = ~DataMaskTemp;
  if (mAmdS3LibPrivateData->S3ScriptLock == FALSE) {
    CalledStatus = S3BootScriptSaveMemReadWrite (AmdS3GetAccessWidth (Width), Address, Data, &DataMaskTemp);
    AgesaStatus  = (CalledStatus == RETURN_SUCCESS) ? AGESA_SUCCESS : AGESA_ERROR;
  } else {
    AgesaStatus = AmdS3SaveCacheScriptData (AMD_S3LIB_BOOT_SCRIPT_MEM_RMW_OP,
                                            AmdS3GetAccessWidth (Width),
                                            Address,
                                            AmdS3GetDataFromPtr (Width, Data),
                                            DataMaskTemp);
  }

  return AgesaStatus;
}

AGESA_STATUS
AmdS3SaveScriptMemPoll (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Data,
  IN       VOID          *DataMask,
  IN       UINT64        Delay
  )
{
  RETURN_STATUS CalledStatus;
  AGESA_STATUS  AgesaStatus;

  UINTN LoopTimes;

  //
  // According to the spec, the interval between 2 polls is 100ns,
  // but the unit of Duration for S3BootScriptSaveMemPoll() is microsecond(1000ns).
  // Duration * 1000ns * LoopTimes = Delay * 100ns
  // Duration will be minimum 1(microsecond) to be minimum deviation,
  // so LoopTimes = Delay / 10.
  //
  LoopTimes = (Delay + 9) / 10;
  if (mAmdS3LibPrivateData->S3ScriptLock == FALSE) {
    CalledStatus = S3BootScriptSaveMemPoll (AmdS3GetAccessWidth (Width), Address, DataMask, Data, 1, LoopTimes);
    AgesaStatus  = (CalledStatus == RETURN_SUCCESS) ? AGESA_SUCCESS : AGESA_ERROR;
  } else {
    AgesaStatus = AmdS3SaveCacheScriptData (AMD_S3LIB_BOOT_SCRIPT_MEM_POLL_OP,
                                            AmdS3GetAccessWidth (Width), Address,
                                            AmdS3GetDataFromPtr (Width, Data),
                                            AmdS3GetDataFromPtr (Width, DataMask),
                                            LoopTimes);
  }

  return AgesaStatus;
}

AGESA_STATUS
AmdS3SaveScriptPciWrite (
  IN       ACCESS_WIDTH  Width,
  IN       UINTN         PciAddress,
  IN       VOID          *Value
  )
{
  UINT64 BootScriptPciAddress;

  //Translate PCI Write to MMIO write due PCILIB can't support PCI register offset above 0xFF
  BootScriptPciAddress = mMMIOAddress + (PciAddress & 0x0FFFFFFF);
  return AmdS3SaveScriptMemWrite (Width, BootScriptPciAddress, Value) ;
}

AGESA_STATUS
AmdS3SaveScriptPciRMW (
  IN       ACCESS_WIDTH  Width,
  IN       UINTN         PciAddress,
  IN       VOID          *Data,
  IN       VOID          *DataMask
  )
{
  UINT64 BootScriptPciAddress;

  //Translate PCI Write to MMIO write due PCILIB can't support PCI register offset above 0xFF
  BootScriptPciAddress = mMMIOAddress + (PciAddress & 0x0FFFFFFF);
  return AmdS3SaveScriptMemRMW (Width, BootScriptPciAddress, Data, DataMask);
}

AGESA_STATUS
AmdS3SaveScriptPciPoll (
  IN       ACCESS_WIDTH  Width,
  IN       UINTN         PciAddress,
  IN       VOID          *Data,
  IN       VOID          *DataMask,
  IN       UINT64        Delay
  )
{

  UINT64 BootScriptPciAddress;

  //Translate PCI Write to MMIO write due PCILIB can't support PCI register offset above 0xFF
  BootScriptPciAddress = mMMIOAddress + (PciAddress & 0x0FFFFFFF);

  return AmdS3SaveScriptMemPoll (Width, BootScriptPciAddress, Data, DataMask, Delay);
}

AGESA_STATUS
AmdS3SaveScriptDispatch (
  IN       VOID          *EntryPoint,
  IN       VOID          *Context
  )
{
  RETURN_STATUS CalledStatus;
  AGESA_STATUS  AgesaStatus;

  if (mAmdS3LibPrivateData->S3ScriptLock == FALSE) {
    CalledStatus = S3BootScriptSaveDispatch2 (EntryPoint, Context);
    AgesaStatus  = (CalledStatus == RETURN_SUCCESS) ? AGESA_SUCCESS : AGESA_ERROR;
  } else {
    AgesaStatus = AmdS3SaveCacheScriptData (AMD_S3LIB_BOOT_SCRIPT_DISPATCH_OP, EntryPoint, Context);
  }
  return AgesaStatus;
}


/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
UINT64
STATIC
AmdS3GetDataFromPtr (
  IN       ACCESS_WIDTH AccessWidth,
  IN       VOID         *Data
  )
{
  UINT64       TempData;

  TempData = 0;
  switch (AccessWidth) {
  case AccessWidth8:
    TempData = (UINT64) (*((UINT8 *) Data));
    break;
  case AccessWidth16:
    TempData = (UINT64) (*((UINT16 *) Data));
    break;
  case AccessWidth32:
    TempData = (UINT64) (*((UINT32 *) Data));
    break;
  case AccessWidth64:
    TempData = (UINT64) (*((UINT64 *) Data));
    break;
  default:
    IDS_ERROR_TRAP;
    break;
  }
  return TempData;
}

S3_BOOT_SCRIPT_LIB_WIDTH
STATIC
AmdS3GetAccessWidth (
  IN       ACCESS_WIDTH AccessWidth
  )
{
  S3_BOOT_SCRIPT_LIB_WIDTH S3BootScriptAccessWidth;

  switch (AccessWidth) {
  case AccessWidth8:
    S3BootScriptAccessWidth = S3BootScriptWidthUint8;
    break;
  case AccessWidth16:
    S3BootScriptAccessWidth = S3BootScriptWidthUint16;
    break;
  case AccessWidth32:
    S3BootScriptAccessWidth = S3BootScriptWidthUint32;
    break;
  case AccessWidth64:
    S3BootScriptAccessWidth = S3BootScriptWidthUint64;
    break;
  default:
    S3BootScriptAccessWidth = S3BootScriptWidthUint8;
    IDS_ERROR_TRAP;
    break;
  }
  return S3BootScriptAccessWidth;
}

VOID
PrepareOpRecord (
  IN       UINT16      OpCode,
  IN       VA_LIST     Marker,
  IN       VOID        *OpDataBuf,
  IN OUT   UINTN       *OpDataLength
  )
{
  ((AMD_S3LIB_BOOT_SCRIPT_COMMON *) OpDataBuf)->OpCode = OpCode;
  switch (OpCode) {
  case AMD_S3LIB_BOOT_SCRIPT_IO_WRITE_OP:
    ((AMD_S3LIB_BOOT_SCRIPT_IO_WRITE *) OpDataBuf)->Width = VA_ARG (Marker, S3_BOOT_SCRIPT_LIB_WIDTH);
    ((AMD_S3LIB_BOOT_SCRIPT_IO_WRITE *) OpDataBuf)->Address = VA_ARG (Marker, UINT64);
    ((AMD_S3LIB_BOOT_SCRIPT_IO_WRITE *) OpDataBuf)->Value = VA_ARG (Marker, UINT64);
    *OpDataLength = sizeof (AMD_S3LIB_BOOT_SCRIPT_IO_WRITE);
    break;
  case AMD_S3LIB_BOOT_SCRIPT_IO_RMW_OP:
    ((AMD_S3LIB_BOOT_SCRIPT_IO_RMW *) OpDataBuf)->Width = VA_ARG (Marker, S3_BOOT_SCRIPT_LIB_WIDTH);
    ((AMD_S3LIB_BOOT_SCRIPT_IO_RMW *) OpDataBuf)->Address = VA_ARG (Marker, UINT64);
    ((AMD_S3LIB_BOOT_SCRIPT_IO_RMW *) OpDataBuf)->Data =  VA_ARG (Marker, UINT64);
    ((AMD_S3LIB_BOOT_SCRIPT_IO_RMW *) OpDataBuf)->DataMask =  VA_ARG (Marker, UINT64);
    *OpDataLength = sizeof (AMD_S3LIB_BOOT_SCRIPT_IO_RMW);
    break;
  case AMD_S3LIB_BOOT_SCRIPT_IO_POLL_OP:
    ((AMD_S3LIB_BOOT_SCRIPT_IO_POLL *) OpDataBuf)->Width = VA_ARG (Marker, S3_BOOT_SCRIPT_LIB_WIDTH);
    ((AMD_S3LIB_BOOT_SCRIPT_IO_POLL *) OpDataBuf)->Address = VA_ARG (Marker, UINT64);
    ((AMD_S3LIB_BOOT_SCRIPT_IO_POLL *) OpDataBuf)->Data =  VA_ARG (Marker, UINT64);
    ((AMD_S3LIB_BOOT_SCRIPT_IO_POLL *) OpDataBuf)->DataMask =  VA_ARG (Marker, UINT64);
    ((AMD_S3LIB_BOOT_SCRIPT_IO_POLL *) OpDataBuf)->Delay =  VA_ARG (Marker, UINT64);
    *OpDataLength = sizeof (AMD_S3LIB_BOOT_SCRIPT_IO_POLL);
    break;
  case AMD_S3LIB_BOOT_SCRIPT_MEM_WRITE_OP:
    ((AMD_S3LIB_BOOT_SCRIPT_MEM_WRITE *) OpDataBuf)->Width = VA_ARG (Marker, S3_BOOT_SCRIPT_LIB_WIDTH);
    ((AMD_S3LIB_BOOT_SCRIPT_MEM_WRITE *) OpDataBuf)->Address = VA_ARG (Marker, UINT64);
    ((AMD_S3LIB_BOOT_SCRIPT_MEM_WRITE *) OpDataBuf)->Value = VA_ARG (Marker, UINT64);
    *OpDataLength = sizeof (AMD_S3LIB_BOOT_SCRIPT_MEM_WRITE);
    break;
  case AMD_S3LIB_BOOT_SCRIPT_MEM_RMW_OP:
    ((AMD_S3LIB_BOOT_SCRIPT_MEM_RMW *) OpDataBuf)->Width = VA_ARG (Marker, S3_BOOT_SCRIPT_LIB_WIDTH);
    ((AMD_S3LIB_BOOT_SCRIPT_MEM_RMW *) OpDataBuf)->Address = VA_ARG (Marker, UINT64);
    ((AMD_S3LIB_BOOT_SCRIPT_MEM_RMW *) OpDataBuf)->Data =  VA_ARG (Marker, UINT64);
    ((AMD_S3LIB_BOOT_SCRIPT_MEM_RMW *) OpDataBuf)->DataMask =  VA_ARG (Marker, UINT64);
    *OpDataLength = sizeof (AMD_S3LIB_BOOT_SCRIPT_MEM_RMW);
    break;
  case AMD_S3LIB_BOOT_SCRIPT_MEM_POLL_OP:
    ((AMD_S3LIB_BOOT_SCRIPT_MEM_POLL *) OpDataBuf)->Width = VA_ARG (Marker, S3_BOOT_SCRIPT_LIB_WIDTH);
    ((AMD_S3LIB_BOOT_SCRIPT_MEM_POLL *) OpDataBuf)->Address = VA_ARG (Marker, UINT64);
    ((AMD_S3LIB_BOOT_SCRIPT_MEM_POLL *) OpDataBuf)->Data =  VA_ARG (Marker, UINT64);
    ((AMD_S3LIB_BOOT_SCRIPT_MEM_POLL *) OpDataBuf)->DataMask =  VA_ARG (Marker, UINT64);
    ((AMD_S3LIB_BOOT_SCRIPT_MEM_POLL *) OpDataBuf)->LoopTimes =  VA_ARG (Marker, UINTN);
    *OpDataLength = sizeof (AMD_S3LIB_BOOT_SCRIPT_MEM_POLL);
    break;
  case AMD_S3LIB_BOOT_SCRIPT_PCI_WRITE_OP:
    ((AMD_S3LIB_BOOT_SCRIPT_PCI_WRITE *) OpDataBuf)->Width = VA_ARG (Marker, S3_BOOT_SCRIPT_LIB_WIDTH);
    ((AMD_S3LIB_BOOT_SCRIPT_PCI_WRITE *) OpDataBuf)->Segment = VA_ARG (Marker, UINT16);
    ((AMD_S3LIB_BOOT_SCRIPT_PCI_WRITE *) OpDataBuf)->Address = VA_ARG (Marker, UINT64);
    ((AMD_S3LIB_BOOT_SCRIPT_PCI_WRITE *) OpDataBuf)->Value = VA_ARG (Marker, UINT64);
    *OpDataLength = sizeof (AMD_S3LIB_BOOT_SCRIPT_PCI_WRITE);
    break;
  case AMD_S3LIB_BOOT_SCRIPT_PCI_RMW_OP:
    ((AMD_S3LIB_BOOT_SCRIPT_PCI_RMW *) OpDataBuf)->Width = VA_ARG (Marker, S3_BOOT_SCRIPT_LIB_WIDTH);
    ((AMD_S3LIB_BOOT_SCRIPT_PCI_RMW *) OpDataBuf)->Segment = VA_ARG (Marker, UINT16);
    ((AMD_S3LIB_BOOT_SCRIPT_PCI_RMW *) OpDataBuf)->Address = VA_ARG (Marker, UINT64);
    ((AMD_S3LIB_BOOT_SCRIPT_PCI_RMW *) OpDataBuf)->Data =  VA_ARG (Marker, UINT64);
    ((AMD_S3LIB_BOOT_SCRIPT_PCI_RMW *) OpDataBuf)->DataMask =  VA_ARG (Marker, UINT64);
    *OpDataLength = sizeof (AMD_S3LIB_BOOT_SCRIPT_PCI_RMW);
    break;
  case AMD_S3LIB_BOOT_SCRIPT_PCI_POLL_OP:
    ((AMD_S3LIB_BOOT_SCRIPT_PCI_POLL *) OpDataBuf)->Width = VA_ARG (Marker, S3_BOOT_SCRIPT_LIB_WIDTH);
    ((AMD_S3LIB_BOOT_SCRIPT_PCI_POLL *) OpDataBuf)->Segment = VA_ARG (Marker, UINT16);
    ((AMD_S3LIB_BOOT_SCRIPT_PCI_POLL *) OpDataBuf)->Address = VA_ARG (Marker, UINT64);
    ((AMD_S3LIB_BOOT_SCRIPT_PCI_POLL *) OpDataBuf)->Data =  VA_ARG (Marker, UINT64);
    ((AMD_S3LIB_BOOT_SCRIPT_PCI_POLL *) OpDataBuf)->DataMask =  VA_ARG (Marker, UINT64);
    ((AMD_S3LIB_BOOT_SCRIPT_PCI_POLL *) OpDataBuf)->Delay =  VA_ARG (Marker, UINT64);
    *OpDataLength = sizeof (AMD_S3LIB_BOOT_SCRIPT_PCI_POLL);
    break;
  case AMD_S3LIB_BOOT_SCRIPT_DISPATCH_OP:
    ((AMD_S3LIB_BOOT_SCRIPT_DISPATCH *) OpDataBuf)->EntryPoint = VA_ARG (Marker, VOID *);
    ((AMD_S3LIB_BOOT_SCRIPT_DISPATCH *) OpDataBuf)->Context = VA_ARG (Marker, VOID *);
    *OpDataLength = sizeof (AMD_S3LIB_BOOT_SCRIPT_DISPATCH);
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}
AGESA_STATUS
ValidateSaveTable (
  )
{
  AMD_S3_LIB_BOOT_SCRIPT_TABLE_HEADER *AmdS3LibTblHdr;

  //Validate the save table
  AmdS3LibTblHdr = (AMD_S3_LIB_BOOT_SCRIPT_TABLE_HEADER *) mAmdS3LibPrivateData->TableBase;
  ASSERT (AmdS3LibTblHdr->Sinature == AMD_S3LIB_BOOT_SCRIPT_TABLE_SIG);
  if (AmdS3LibTblHdr->Sinature != AMD_S3LIB_BOOT_SCRIPT_TABLE_SIG) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "AmdS3Lib table Signature check fail\n");
    return AGESA_ERROR;
  }
  ASSERT (*((UINT32 *) (mAmdS3LibPrivateData->TableBase + AmdS3LibTblHdr->TableLength)) == AMD_S3LIB_TABLE_WATCHER);
  if (*((UINT32 *) (mAmdS3LibPrivateData->TableBase + AmdS3LibTblHdr->TableLength)) != AMD_S3LIB_TABLE_WATCHER) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "AmdS3Lib table boundary check fail\n");
    return AGESA_ERROR;
  }
  return AGESA_SUCCESS;
}

AGESA_STATUS
AmdS3SaveCacheScriptData (
  IN      UINT16      OpCode,
  IN      ...
  )
{
  UINT8     *TableData;
  AMD_S3_LIB_BOOT_SCRIPT_TABLE_HEADER *AmdS3LibTblHdr;
  AMD_S3LIB_BOOT_SCRIPT_DATA OpDataBuf [2];
  UINTN OpDataLength;
  VA_LIST  Marker;

  VA_START (Marker, OpCode);
  AmdS3LibTblHdr = NULL;
  //
  //Cache the Script if EFI S3Script Locked and Amd S3 Table still open
  if ((mAmdS3LibPrivateData->S3ScriptLock == TRUE) &&
      (mAmdS3LibPrivateData->CloseTable == FALSE)) {
    if (mAmdS3LibPrivateData->TableBase == NULL) {
      //S3 table haven't been allocated
      //reserve 4 bytes for data over boundary check
      AmdS3LibTblHdr = AllocateRuntimeZeroPool (AMD_S3LIB_BUFFER_INIT_SIZE + AMD_S3LIB_TABLE_WATCHER_SIZE);
      ASSERT (AmdS3LibTblHdr != NULL);
      if (AmdS3LibTblHdr == NULL) {
        IDS_HDT_CONSOLE (MAIN_FLOW, "AmdS3Lib table allocate fail\n");
        return AGESA_ERROR;
      }
      //Update the private data
      mAmdS3LibPrivateData->TableBase = (UINT8 *) (AmdS3LibTblHdr);
      //Init the Table
      AmdS3LibTblHdr->Sinature = AMD_S3LIB_BOOT_SCRIPT_TABLE_SIG;
      AmdS3LibTblHdr->Version = AMD_S3LIB_BOOT_SCRIPT_TABLE_VER_1;

      AmdS3LibTblHdr->TableLength = AMD_S3LIB_BUFFER_INIT_SIZE;
      AmdS3LibTblHdr->NextDataOffset = OFFSET_OF (AMD_S3_LIB_BOOT_SCRIPT_TABLE_HEADER, Data);
      //Fill the Watcher
      *((UINT32 *)(mAmdS3LibPrivateData->TableBase + AmdS3LibTblHdr->TableLength)) = AMD_S3LIB_TABLE_WATCHER;
    } else {
      AmdS3LibTblHdr = (AMD_S3_LIB_BOOT_SCRIPT_TABLE_HEADER *) mAmdS3LibPrivateData->TableBase;
    }

    if (ValidateSaveTable () != AGESA_SUCCESS) {
      return AGESA_ERROR;
    }
    //Prepare the OP record buffer and get its length according OpCode
    ZeroMem (OpDataBuf, sizeof (OpDataBuf));
    OpDataLength = 0;
    PrepareOpRecord (OpCode, Marker, OpDataBuf, &OpDataLength);

    //Check if the buffer size is enough to hold the new record
    if ((AmdS3LibTblHdr->NextDataOffset + OpDataLength + AMD_S3LIB_TABLE_END_SIZE) > AmdS3LibTblHdr->TableLength ) {
      //Don't have enough space
      //Allocate new space with big size
      TableData = AllocateRuntimeZeroPool (AmdS3LibTblHdr->TableLength + AMD_S3LIB_BUFFER_INC_SIZE + AMD_S3LIB_TABLE_WATCHER_SIZE);
      ASSERT (TableData != NULL);
      if (TableData == NULL) {
        IDS_HDT_CONSOLE (MAIN_FLOW, "AmdS3SaveLib allocate new Pool fail %x\n", (AmdS3LibTblHdr->TableLength + AMD_S3LIB_BUFFER_INC_SIZE + AMD_S3LIB_TABLE_WATCHER_SIZE));
        return AGESA_ERROR;
      }
      //Copy data to new buffer
      CopyMem (TableData, mAmdS3LibPrivateData->TableBase, AmdS3LibTblHdr->TableLength);
      FreePool (mAmdS3LibPrivateData->TableBase);
      //Update global private data
      mAmdS3LibPrivateData->TableBase = TableData;
      //Update Table Header with new size infomation
      AmdS3LibTblHdr = (AMD_S3_LIB_BOOT_SCRIPT_TABLE_HEADER *) TableData;
      AmdS3LibTblHdr->TableLength += AMD_S3LIB_BUFFER_INC_SIZE;
      //Fill the Watcher
      *((UINT32 *)(mAmdS3LibPrivateData->TableBase + AmdS3LibTblHdr->TableLength)) = AMD_S3LIB_TABLE_WATCHER;
    }
    //Copy the OP record to table
    CopyMem (mAmdS3LibPrivateData->TableBase + AmdS3LibTblHdr->NextDataOffset, OpDataBuf, OpDataLength);
    AmdS3LibTblHdr->NextDataOffset += OpDataLength;
  }
  return AGESA_SUCCESS;
}

VOID
AmdS3SaveBootScriptLockCallBack (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  EFI_STATUS Status;
  VOID        *Interface;

  //
  // Try to locate it because EfiCreateProtocolNotifyEvent will trigger it once when registration.
  // Just return if it is not found.
  //
  Status = gBS->LocateProtocol (
                  &gEfiDxeSmmReadyToLockProtocolGuid,
                  NULL,
                  &Interface
                  );
  if (EFI_ERROR (Status)) {
    return ;
  }

  //Make sure the hook ONLY called one time.
  if (Event != NULL) {
    gBS->CloseEvent (Event);
  }
  mAmdS3LibPrivateData->S3ScriptLock = TRUE;
}

VOID
AmdS3SaveCloseTableCallBack (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  EFI_STATUS Status;
  AMD_S3_LIB_BOOT_SCRIPT_TABLE_HEADER *AmdS3LibTblHdr;
  UINT8       *Buffer;
  EFI_SMM_COMMUNICATE_HEADER *SmmCommBuff;
  AMD_SMM_COMMUNICATION_S3SCRIPT  *AmdSmmS3ScriptBuff;
  EFI_SMM_COMMUNICATION_PROTOCOL *SmmCommunication;
  UINTN       SmmCommBufferSize;
  //Make sure the hook ONLY called one time.
  if (Event != NULL) {
    gBS->CloseEvent (Event);
  }

  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdS3SaveCloseTableCallBack\n");
  if (mAmdS3LibPrivateData->TableBase != NULL) {
    if (ValidateSaveTable () != AGESA_SUCCESS) {
      return;
    }
    //Fill the END flag
    AmdS3LibTblHdr = (AMD_S3_LIB_BOOT_SCRIPT_TABLE_HEADER *) mAmdS3LibPrivateData->TableBase;
    *((UINT16 *) (mAmdS3LibPrivateData->TableBase + AmdS3LibTblHdr->NextDataOffset)) = AMD_S3LIB_TABLE_END;

    //Init SMM communication buffer header
    Buffer = (UINT8 *) (UINTN) PcdGet64 (PcdAmdSmmCommunicationAddress);

    ASSERT (Buffer != NULL);
    if (Buffer != NULL) {
      ZeroMem (Buffer, AMD_SMM_COMMUNICATION_S3SCRIPT_BUFFER_SIZE);
      SmmCommBuff = (EFI_SMM_COMMUNICATE_HEADER *) Buffer;
      CopyGuid (&SmmCommBuff->HeaderGuid, &gAmdSmmCommunicationHandleGuid);
      SmmCommBuff->MessageLength = sizeof (AMD_SMM_COMMUNICATION_S3SCRIPT);
      //Init PSP SMM communicate private data
      AmdSmmS3ScriptBuff = (AMD_SMM_COMMUNICATION_S3SCRIPT *) &SmmCommBuff->Data;
      AmdSmmS3ScriptBuff->id = AMD_SMM_COMMUNICATION_ID_S3SCRIPT;
      AmdSmmS3ScriptBuff->PrivateDataAddress = mAmdS3LibPrivateData;

      //Communicate AMD SMM Handle
      SmmCommunication = NULL;
      Status = gBS->LocateProtocol (&gEfiSmmCommunicationProtocolGuid, NULL, (VOID **) &SmmCommunication);
      ASSERT (Status == EFI_SUCCESS);
      if (SmmCommunication == NULL) {
        IDS_HDT_CONSOLE (MAIN_FLOW, "AmdS3SaveLib locate SmmCommunicationProtocol fail \n");
        return;
      }
      //Communicate AMD SMM communication handler to save boot script inside SMM
      SmmCommBufferSize = AMD_SMM_COMMUNICATION_S3SCRIPT_BUFFER_SIZE;
      SmmCommunication->Communicate (SmmCommunication, Buffer, &SmmCommBufferSize);

      //Close Table
      mAmdS3LibPrivateData->CloseTable = TRUE;
      //Free the memory buffer
      FreePool (mAmdS3LibPrivateData->TableBase);
    }
  } else {
    IDS_HDT_CONSOLE (MAIN_FLOW, "mAmdS3LibPrivateData is NULL\n");
  }
}

EFI_STATUS
EFIAPI
AmdS3SaveLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS Status;
  AMD_S3_LIB_PRIVATE_DATA *AmdS3LibPrivateData;
  VOID   *Registration;

  //Locate the global data structure via PCD
  AmdS3LibPrivateData = NULL;
  AmdS3LibPrivateData = (AMD_S3_LIB_PRIVATE_DATA *) (UINTN) PcdGet64 (PcdAmdS3LibPrivateDataAddress);

  ASSERT (GetPciMmioAddress (&mMMIOAddress, &mMMIOSize, NULL) == TRUE);

  if (AmdS3LibPrivateData == NULL) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "AmdS3LibPrivateData allocation\n");
    //Global data structure haven't init yet
    AmdS3LibPrivateData = AllocateRuntimeZeroPool (sizeof (AMD_S3_LIB_PRIVATE_DATA));
    ASSERT (AmdS3LibPrivateData != NULL);
    if (AmdS3LibPrivateData == NULL) {
      IDS_HDT_CONSOLE (MAIN_FLOW, "AmdS3LibPrivateData allocate fail\n");
      return EFI_OUT_OF_RESOURCES;
    }

    AmdS3LibPrivateData->S3ScriptLock = FALSE;
    AmdS3LibPrivateData->CloseTable = FALSE;
    AmdS3LibPrivateData->TableBase = NULL;

    //Set the global data
    PcdSet64 (PcdAmdS3LibPrivateDataAddress, (UINT64) (UINTN) AmdS3LibPrivateData);

    //
    // create event to notify the SMM Lock event
    //
    mS3ScriptLockEvent = EfiCreateProtocolNotifyEvent  (
                          &gEfiDxeSmmReadyToLockProtocolGuid,
                          TPL_CALLBACK,
                          AmdS3SaveBootScriptLockCallBack,
                          NULL,
                          &Registration
                          );
    ASSERT (mS3ScriptLockEvent != NULL);
    if (mS3ScriptLockEvent == NULL) {
      IDS_HDT_CONSOLE (MAIN_FLOW, "AmdS3SaveLib create BootScriptLock Event fail\n");
      return EFI_UNSUPPORTED;
    }

    //Create the hook for ReadyToBoot, ExitBootService will not be called for Non-UEFI system
    /// @todo need to make sure it the last timepoint of AGESA
    Status = gBS->CreateEventEx (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    AmdS3SaveCloseTableCallBack,
                    NULL,
                    &gEfiEventReadyToBootGuid,
                    &mCloseTableEvent
                    );

    ASSERT (Status == EFI_SUCCESS);
    if (EFI_ERROR (Status)) {
      IDS_HDT_CONSOLE (MAIN_FLOW, "AmdS3SaveLib create CloseTable Event fail\n");
      return EFI_UNSUPPORTED;
    }
  }
  //Init Driver scope global value
  mAmdS3LibPrivateData = AmdS3LibPrivateData;

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
AmdS3SaveLibDestructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS Status;

  //
  // Close events
  //
  if (mS3ScriptLockEvent != NULL) {
    Status = gBS->CloseEvent (mS3ScriptLockEvent);
    ASSERT (Status == EFI_SUCCESS);
  }

  if (mCloseTableEvent != NULL) {
    Status = gBS->CloseEvent (mCloseTableEvent);
    ASSERT (Status == EFI_SUCCESS);
  }
  return EFI_SUCCESS;
}

