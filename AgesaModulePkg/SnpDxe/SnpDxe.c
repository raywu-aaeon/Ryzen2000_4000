/* $NoKeywords:$ */
/**
 * @file
 *
 * SnpDxe.c
 *
 * Contains Ethernet Driver for the DXE phase.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: FDK
 * @e sub-project: UEFI
 * @e version: $Revision: 300489 $ @e date: $Date: 2014-08-08 14:36:46 -0700 (Fri, 08 Aug 2014) $
 *
 */
/*****************************************************************************
 *
 * Copyright 2013 - 2018 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting you permission to use this software (the Materials)
 * pursuant to the terms and conditions of your Software License Agreement
 * with AMD.  This header does *NOT* give you permission to use the Materials
 * or any rights under AMD's intellectual property.  Your use of any portion
 * of these Materials shall constitute your acceptance of those terms and
 * conditions.  If you do not agree to the terms and conditions of the Software
 * License Agreement, please do not use any portion of these Materials.
 *
 * CONFIDENTIALITY:  The Materials and all other information, identified as
 * confidential and provided to you by AMD shall be kept confidential in
 * accordance with the terms and conditions of the Software License Agreement.
 *
 * LIMITATION OF LIABILITY: THE MATERIALS AND ANY OTHER RELATED INFORMATION
 * PROVIDED TO YOU BY AMD ARE PROVIDED "AS IS" WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTY OF ANY KIND, INCLUDING BUT NOT LIMITED TO WARRANTIES OF
 * MERCHANTABILITY, NONINFRINGEMENT, TITLE, FITNESS FOR ANY PARTICULAR PURPOSE,
 * OR WARRANTIES ARISING FROM CONDUCT, COURSE OF DEALING, OR USAGE OF TRADE.
 * IN NO EVENT SHALL AMD OR ITS LICENSORS BE LIABLE FOR ANY DAMAGES WHATSOEVER
 * (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF PROFITS, BUSINESS
 * INTERRUPTION, OR LOSS OF INFORMATION) ARISING OUT OF AMD'S NEGLIGENCE,
 * GROSS NEGLIGENCE, THE USE OF OR INABILITY TO USE THE MATERIALS OR ANY OTHER
 * RELATED INFORMATION PROVIDED TO YOU BY AMD, EVEN IF AMD HAS BEEN ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGES.  BECAUSE SOME JURISDICTIONS PROHIBIT THE
 * EXCLUSION OR LIMITATION OF LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES,
 * THE ABOVE LIMITATION MAY NOT APPLY TO YOU.
 *
 * AMD does not assume any responsibility for any errors which may appear in
 * the Materials or any other related information provided to you by AMD, or
 * result from use of the Materials or any related information.
 *
 * You agree that you will not reverse engineer or decompile the Materials.
 *
 * NO SUPPORT OBLIGATION: AMD is not obligated to furnish, support, or make any
 * further information, software, technical information, know-how, or show-how
 * available to you.  Additionally, AMD retains the right to modify the
 * Materials at any time, without notice, and is not obligated to provide such
 * modified Materials to you.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS: The Materials are provided with
 * "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
 * subject to the restrictions as set forth in FAR 52.227-14 and
 * DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
 * Government constitutes acknowledgement of AMD's proprietary rights in them.
 *
 * EXPORT ASSURANCE:  You agree and certify that neither the Materials, nor any
 * direct product thereof will be exported directly or indirectly, into any
 * country prohibited by the United States Export Administration Act and the
 * regulations thereunder, without the required authorization from the U.S.
 * government nor will be used for any purpose prohibited by the same.
 ******************************************************************************
 */
#include "SnpDxe.h"
#include <AMD.h>
#include <Library/AmdBaseLib.h>
#include <Library/PcdLib.h>
#include <Guid/EventLegacyBios.h>

extern  EFI_DEVICE_PATH_PROTOCOL        *PciDevicePath;
ENET_DXE_PRIVATE_DATA *gPrivate;
EFI_HANDLE              gControllerHandle;
UINT8 					TxCount;

#define INT_EN                0x1D078ul
extern
UINT32
clearBitfield (
  IN UINT32 Value,
  IN UINT32 Lsb,
  IN UINT32 Width
  );

extern
VOID
setBitfieldReg32 (
  IN UINT32 Addr,
  IN UINT32 Lsb,
  IN UINT32 Width,
  IN UINT32 FieldValue
  );


#if MAC_ADDRESS_DEBUG
STATIC
CHAR8
CharToUpper (
  IN       CHAR8 Char
  )
{
  if (Char >= 'a' && Char <= 'z') {
    return (CHAR8) (Char - ('a' - 'A'));
  }

  return Char;
}


EFI_STATUS
STATIC
HexCharToUint (
  IN       CHAR8 Char,
     OUT   UINT8 *Out
  )
{
  if (Char >= '0' && (Char <= '9')) {
    *Out = (UINT8) (Char - '0');
  } else if (Char >= 'a' && (Char <= 'f')) {
    *Out = (UINT8) (10 + CharToUpper (Char) - 'A');
  } else if (Char >= 'A' && (Char <= 'F')) {
    *Out = (UINT8) (10 + Char - 'A');
  } else {
    return EFI_INVALID_PARAMETER;
  }

  return EFI_SUCCESS;
}
#endif


EFI_STATUS
STATIC
EthSetMacAddrFromPcd (
  IN       UINTN XgmacBase,
  OUT      UINT8 *Addr
  )
{
  UINT64 Index;
  UINT64 Mask;
  UINT64 PcdMacAddr;
  UINT32 Value;

  Value = MmioRead16 (XgmacBase + PORT_MAC_ADDR_HIGH);
  PcdMacAddr = Value;
  PcdMacAddr <<= 32;
  Value = MmioRead32 (XgmacBase + PORT_MAC_ADDR_LOW);
  PcdMacAddr |= Value;
  Mask = 0xFF;
  for (Index = 0; Index < ENET_ADDR_LEN; Index++) {
    Addr[Index] = (UINT8) ((PcdMacAddr & (Mask << (8 * Index))) >> (8 * Index));
  }

  DEBUG ((
    EFI_D_ERROR,
    "SNP MAC Address : %02X:%02X:%02X:%02X:%02X:%02X\n",
    Addr[0], Addr[1], Addr[2], Addr[3], Addr[4], Addr[5]
    ));

  return EFI_SUCCESS;
}

#if MAC_ADDRESS_DEBUG

EFI_STATUS
STATIC
EthSetMacAddrFromToken (
  OUT UINT8 *Addr
  )
{
#define MAC_ADDR_DIGIT_NUM 12

  EFI_STATUS StatusHigh = EFI_NOT_FOUND;
  EFI_STATUS StatusLow = EFI_NOT_FOUND;
  UINT8 Temp[2];
  UINT8 Index;
  CHAR8 MacAddressStr[MAC_ADDR_DIGIT_NUM];

#ifdef ENET_PORT0
#ifndef MAC_ADDRESS0_STR
  DEBUG ((EFI_D_ERROR, "\n*** Error: MAC address not set. ***\n"));
  return EFI_NOT_FOUND;
#endif

  if (AsciiStrLen (MAC_ADDRESS0_STR) != MAC_ADDR_DIGIT_NUM) {
    DEBUG ((EFI_D_ERROR, "\n*** Error: Invalid MAC address length. ***\n"));
    return EFI_INVALID_PARAMETER;
  }

  AsciiStrnCpy (MacAddressStr, MAC_ADDRESS0_STR, MAC_ADDR_DIGIT_NUM);
#else
#ifndef MAC_ADDRESS1_STR
  DEBUG ((EFI_D_ERROR, "\n*** Error: MAC address not set. ***\n"));
  return EFI_NOT_FOUND;
#endif

  if (AsciiStrLen (MAC_ADDRESS1_STR) != MAC_ADDR_DIGIT_NUM) {
    DEBUG ((EFI_D_ERROR, "\n*** Error: Invalid MAC address length. ***\n"));
    return EFI_INVALID_PARAMETER;
  }

  AsciiStrnCpy (MacAddressStr, MAC_ADDRESS1_STR, MAC_ADDR_DIGIT_NUM);
#endif

  for (Index = 0; Index < MAC_ADDR_DIGIT_NUM; Index += 2) {
    StatusHigh = HexCharToUint (MacAddressStr[Index], &Temp[0]);
    StatusLow = HexCharToUint (MacAddressStr[Index + 1], &Temp[1]);

    if (EFI_ERROR (StatusHigh) || EFI_ERROR (StatusLow)) {
      DEBUG ((EFI_D_ERROR, "\n*** Error: Invalid MAC address range. ***\n"));
      return EFI_UNSUPPORTED;
    }

    Addr[Index >> 1] = (Temp[0] << 4) | Temp[1];
  }

  return EFI_SUCCESS;
}
#endif


EFI_STATUS
STATIC
EFIAPI
EthStart (
  IN       EFI_SIMPLE_NETWORK_PROTOCOL *This
  )
{
  ENET_DXE_PRIVATE_DATA *Private = NULL;
  EFI_STATUS  Status;
  EFI_TPL     OldTpl;

  if (This == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Private = ENET_DXE_PRIVATE_DATA_FROM_SNP_THIS (This);

  OldTpl = gBS->RaiseTPL (TPL_CALLBACK);

  DEBUG ((EFI_D_ERROR, "EthStart Private->Mode.State = %x \n", Private->Mode.State)); 

  switch (Private->Mode.State) {
  case EfiSimpleNetworkStopped:
    Status = ImplementStart (Private);
    if (!EFI_ERROR (Status)) {
      Private->Mode.MCastFilterCount = 0;
    }
    break;

  case EfiSimpleNetworkStarted:
  case EfiSimpleNetworkInitialized:
    Status = EFI_ALREADY_STARTED;
    break;

  default:
    Status = EFI_DEVICE_ERROR;
    break;
  }

  gBS->RestoreTPL (OldTpl);
  return Status;
}

EFI_STATUS
//STATIC
EFIAPI
EthStop (
  IN EFI_SIMPLE_NETWORK_PROTOCOL *This
  )
{
  ENET_DXE_PRIVATE_DATA *Private = NULL;
  EFI_TPL     OldTpl;
  EFI_STATUS  Status;

  if (This == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Private = ENET_DXE_PRIVATE_DATA_FROM_SNP_THIS (This);

  OldTpl = gBS->RaiseTPL (TPL_CALLBACK);

  DEBUG ((EFI_D_ERROR, "EthStop Private->Mode.State = %x \n" , Private->Mode.State));

  switch (Private->Mode.State) {
  case EfiSimpleNetworkStarted:
    Status = ImplementStop (Private);
    break;

  case EfiSimpleNetworkStopped:
    Status = EFI_NOT_STARTED;
    break;

  default:
    Status = EFI_DEVICE_ERROR;
    break;
  }

  gBS->RestoreTPL (OldTpl);
  return Status;
}

EFI_STATUS
STATIC
EFIAPI
EthInitialize (
  IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
  IN UINTN ExtraRxBufferSize OPTIONAL,
  IN UINTN ExtraTxBufferSize OPTIONAL
  )
{
  EFI_STATUS  EfiStatus;
  ENET_DXE_PRIVATE_DATA *Private = NULL;

  EFI_TPL     OldTpl;
  
  if (This == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Private = ENET_DXE_PRIVATE_DATA_FROM_SNP_THIS (This);
  if (Private == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  OldTpl = gBS->RaiseTPL (TPL_CALLBACK);

  DEBUG ((EFI_D_ERROR, "EthInitialize Private->Mode.State = %x \n" , Private->Mode.State));

  switch (Private->Mode.State) {
  case EfiSimpleNetworkStarted:
    Private->Mode.MCastFilterCount      = 0;
    Private->Mode.ReceiveFilterSetting  = 0;
    ZeroMem (Private->Mode.MCastFilter, sizeof (Private->Mode.MCastFilter));
    CopyMem (
              &Private->Mode.CurrentAddress,
              &Private->Mode.PermanentAddress,
              sizeof (EFI_MAC_ADDRESS)
            );
    EfiStatus = ImplementInit (Private);
    break;

  case EfiSimpleNetworkStopped:
    EfiStatus = EFI_NOT_STARTED;
    break;

  default:
    EfiStatus = EFI_DEVICE_ERROR;
    break;
  }

  gBS->RestoreTPL (OldTpl);
  return EfiStatus;
}


EFI_STATUS
STATIC
EFIAPI
EthReset (
  IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
  IN BOOLEAN ExtendedVerification
  )
{
  ENET_DXE_PRIVATE_DATA *Private = NULL;
  EFI_TPL     OldTpl;
  EFI_STATUS  Status;

  
  DEBUG ((EFI_D_ERROR, "EthReset \n"));

  //
  // Resolve Warning 4 unreferenced parameter problem
  //
  ExtendedVerification = 0;
  DEBUG ((EFI_D_WARN, "ExtendedVerification = %d is not implemented!\n", ExtendedVerification));

  if (This == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Private = ENET_DXE_PRIVATE_DATA_FROM_SNP_THIS (This);

  OldTpl = gBS->RaiseTPL (TPL_CALLBACK);

  switch (Private->Mode.State) {
  case EfiSimpleNetworkInitialized:
    Status = ImplementReset (Private);
    break;

  case EfiSimpleNetworkStopped:
    Status = EFI_NOT_STARTED;
    break;

  default:
    Status = EFI_DEVICE_ERROR;
    break;
  }

  gBS->RestoreTPL (OldTpl);
  return Status;
}

EFI_STATUS
STATIC
EFIAPI
EthShutdown (
  IN EFI_SIMPLE_NETWORK_PROTOCOL *This
  )
{
  ENET_DXE_PRIVATE_DATA *Private = NULL;
  EFI_STATUS  Status;
  EFI_TPL     OldTpl;

  //
  // Get pointer to SNP driver instance for *This.
  //
  if (This == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Private = ENET_DXE_PRIVATE_DATA_FROM_SNP_THIS (This);

  OldTpl = gBS->RaiseTPL (TPL_CALLBACK);

  DEBUG ((EFI_D_ERROR, "EthShutdown Private->Mode.State = %x \n" , Private->Mode.State));

  //
  // Return error if the SNP is not initialized.
  //
  switch (Private->Mode.State) {
  case EfiSimpleNetworkInitialized:
    Status                              = ImplementShutdown (Private);
    Private->Mode.State                 = EfiSimpleNetworkStarted;
    Private->Mode.ReceiveFilterSetting  = 0;
    Private->Mode.MCastFilterCount      = 0;
    Private->Mode.ReceiveFilterSetting  = 0;
    ZeroMem (Private->Mode.MCastFilter, sizeof Private->Mode.MCastFilter);
    CopyMem (
              &Private->Mode.CurrentAddress,
              &Private->Mode.PermanentAddress,
              sizeof (EFI_MAC_ADDRESS)
            );
    break;

  case EfiSimpleNetworkStopped:
    Status = EFI_NOT_STARTED;
    break;

  default:
    Status = EFI_DEVICE_ERROR;
    break;
  }

  gBS->RestoreTPL (OldTpl);
  return Status;
}

EFI_STATUS
STATIC
EFIAPI
EthReceiveFilters (
  IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
  IN UINT32 Enable,
  IN UINT32 Disable,
  IN BOOLEAN ResetMCastFilter,
  IN UINTN MCastFilterCnt OPTIONAL,
  IN EFI_MAC_ADDRESS *MCastFilter OPTIONAL
  )
{
  ENET_DXE_PRIVATE_DATA *Private = NULL;
  EFI_STATUS  Status;
  EFI_TPL     OldTpl;

  if (This == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Private = ENET_DXE_PRIVATE_DATA_FROM_SNP_THIS (This);

  OldTpl = gBS->RaiseTPL (TPL_CALLBACK);

  DEBUG ((EFI_D_ERROR, "EthReceiveFilters Private->Mode.State = %x \n" , Private->Mode.State));

  switch (Private->Mode.State) {
  case EfiSimpleNetworkInitialized:
    break;

  case EfiSimpleNetworkStopped:
    Status = EFI_NOT_STARTED;
    gBS->RestoreTPL (OldTpl);
    return Status;

  default:
    Status = EFI_DEVICE_ERROR;
    gBS->RestoreTPL (OldTpl);
    return Status;
  }
  //
  // check if we are asked to enable or disable something that the UNDI
  // does not even support!
  //
  if (((Enable &~Private->Mode.ReceiveFilterMask) != 0) ||
      ((Disable &~Private->Mode.ReceiveFilterMask) != 0)) {
    Status = EFI_INVALID_PARAMETER;
    gBS->RestoreTPL (OldTpl);
    return Status;
  }

  if (ResetMCastFilter) {
    Disable |= EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST & Private->Mode.ReceiveFilterMask;
    MCastFilterCnt = 0;
    MCastFilter    = NULL;
  } else {
    if (MCastFilterCnt != 0) {
      if ((MCastFilterCnt > Private->Mode.MaxMCastFilterCount) ||
          (MCastFilter == NULL)) {
        Status = EFI_INVALID_PARAMETER;
        gBS->RestoreTPL (OldTpl);
        return Status;
      }
    }
  }

  if (Enable == 0 && Disable == 0 && !ResetMCastFilter && MCastFilterCnt == 0) {
    Status = EFI_SUCCESS;
    gBS->RestoreTPL (OldTpl);
    return Status;
  }

  if ((Enable & EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST) != 0 && MCastFilterCnt == 0) {
    Status = EFI_INVALID_PARAMETER;
    gBS->RestoreTPL (OldTpl);
    return Status;
  }

  if ((Enable != 0) || (MCastFilterCnt != 0)) {
    Status = ImplementRecvFilterEnable (Private);

    if (EFI_ERROR (Status)) {
      gBS->RestoreTPL (OldTpl);
      return Status;
    }
  }

  if ((Disable != 0) || ResetMCastFilter) {
    Status = ImplementRecvFilterDisable (Private);
    if (EFI_ERROR (Status)) {
      gBS->RestoreTPL (OldTpl);
      return Status;
    }
  }

  Status = ImplementRecvFilterRead (Private);
  gBS->RestoreTPL (OldTpl);
  return Status;
}

EFI_STATUS
STATIC
EFIAPI
EthStationAddress (
  IN       EFI_SIMPLE_NETWORK_PROTOCOL *This,
  IN       BOOLEAN Reset,
  IN       EFI_MAC_ADDRESS *New OPTIONAL
  )
{
  ENET_DXE_PRIVATE_DATA *Private = NULL;
  EFI_STATUS  Status;
  EFI_TPL     OldTpl;

  DEBUG ((EFI_D_ERROR, "EthStationAddress  \n"));

  //
  // Check for invalid parameter combinations.
  //
  if ((This == NULL) ||
      (!Reset && (New == NULL))) {
    return EFI_INVALID_PARAMETER;
  }

  Private = ENET_DXE_PRIVATE_DATA_FROM_SNP_THIS (This);

  OldTpl = gBS->RaiseTPL (TPL_CALLBACK);

  //
  // Return error if the SNP is not initialized.
  //
  switch (Private->Mode.State) {
  case EfiSimpleNetworkInitialized:
    if (Reset) {
      Status = ImplementSetStnAddr (Private, NULL);
    } else {
      Status = ImplementSetStnAddr (Private, New);
    }
    break;

  case EfiSimpleNetworkStopped:
    Status = EFI_NOT_STARTED;
    break;

  default:
    Status = EFI_DEVICE_ERROR;
    break;
  }

  gBS->RestoreTPL (OldTpl);
  return Status;
}

EFI_STATUS
STATIC
EFIAPI
EthStatistics (
  IN       EFI_SIMPLE_NETWORK_PROTOCOL *This,
  IN       BOOLEAN Reset,
  IN OUT   UINTN *StatisticsSize OPTIONAL,
  IN OUT   EFI_NETWORK_STATISTICS *StatisticsTable OPTIONAL
  )
{
  ENET_DXE_PRIVATE_DATA *Private = NULL;
  EFI_TPL           OldTpl;
  EFI_STATUS        Status;

  DEBUG ((EFI_D_ERROR, "EthStatistics \n"));

  //
  // Get pointer to SNP driver instance for *This.
  //
  if (This == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Private = ENET_DXE_PRIVATE_DATA_FROM_SNP_THIS (This);

  OldTpl = gBS->RaiseTPL (TPL_CALLBACK);

  //
  // Return error if the SNP is not initialized.
  //
  switch (Private->Mode.State) {
  case EfiSimpleNetworkInitialized:
    //
    // if we are not resetting the counters, we have to have a valid stat table
    // with >0 size. if no reset, no table and no size, return success.
    //
    if (!Reset && StatisticsSize == NULL) {
      Status = (StatisticsTable != NULL) ? EFI_INVALID_PARAMETER : EFI_SUCCESS;
    } else if (Reset) {
      Status = EFI_SUCCESS;
    } else if (StatisticsTable == NULL) {
      *StatisticsSize = sizeof (EFI_NETWORK_STATISTICS);
      Status = EFI_BUFFER_TOO_SMALL;
    } else {
      Status = ImplementStatistics (Private);
    }
    break;

  case EfiSimpleNetworkStopped:
    Status = EFI_NOT_STARTED;
    break;

  default:
    Status = EFI_DEVICE_ERROR;
    break;
  }

  gBS->RestoreTPL (OldTpl);
  return Status;
}

EFI_STATUS
STATIC
EFIAPI
EthMCastIpToMac (
  IN       EFI_SIMPLE_NETWORK_PROTOCOL *This,
  IN       BOOLEAN IPv6,
  IN       EFI_IP_ADDRESS *IP,
     OUT   EFI_MAC_ADDRESS *MAC
  )
{
  ENET_DXE_PRIVATE_DATA *Private = NULL;
  EFI_TPL     OldTpl;
  EFI_STATUS  Status;

  DEBUG ((EFI_D_ERROR, "EthMCastIpToMac  \n"));

  //
  // Get pointer to SNP driver instance for *this.
  //
  if (This == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (IP == NULL || MAC == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Private = ENET_DXE_PRIVATE_DATA_FROM_SNP_THIS (This);

  OldTpl = gBS->RaiseTPL (TPL_CALLBACK);

  switch (Private->Mode.State) {
  case EfiSimpleNetworkInitialized:
    Status = ImplementIp2Mac (Private, IPv6, IP, MAC);
    break;

  case EfiSimpleNetworkStopped:
    Status = EFI_NOT_STARTED;
    break;

  default:
    Status = EFI_DEVICE_ERROR;
    break;
  }

  gBS->RestoreTPL (OldTpl);
  return Status;
}

EFI_STATUS
STATIC
EFIAPI
EthNvData (
  IN       EFI_SIMPLE_NETWORK_PROTOCOL *This,
  IN       BOOLEAN ReadWrite,
  IN       UINTN Offset,
  IN       UINTN BufferSize,
  IN OUT   VOID *Buffer
  )
{
  ENET_DXE_PRIVATE_DATA *Private = NULL;
  EFI_TPL     OldTpl;
  EFI_STATUS  Status;

  DEBUG ((EFI_D_ERROR, "EthNvData  \n"));

  //
  // Get pointer to SNP driver instance for *this.
  //
  if (This == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Private = ENET_DXE_PRIVATE_DATA_FROM_SNP_THIS (This);

  OldTpl = gBS->RaiseTPL (TPL_CALLBACK);

  //
  // Return error if the SNP is not initialized.
  //
  switch (Private->Mode.State) {
  case EfiSimpleNetworkInitialized:
      //
    // Return error if non-volatile memory variables are not valid.
    //
    if (Private->Mode.NvRamSize == 0 || Private->Mode.NvRamAccessSize == 0) {
      Status = EFI_UNSUPPORTED;
      // Check for invalid parameter combinations.
    } else if ((BufferSize == 0) ||
          (Buffer == NULL) ||
          (Offset >= Private->Mode.NvRamSize) ||
          (Offset + BufferSize > Private->Mode.NvRamSize) ||
          (BufferSize % Private->Mode.NvRamAccessSize != 0) ||
          (Offset % Private->Mode.NvRamAccessSize != 0)
        ) {
      Status = EFI_INVALID_PARAMETER;
      // check the implementation flags of undi if we can write the nvdata!
    } else if (!ReadWrite) {
      Status = EFI_UNSUPPORTED;
    } else {
      Status = ImplementNvDataRead (Private, Offset, BufferSize, Buffer);
    }
    break;

  case EfiSimpleNetworkStopped:
    Status = EFI_NOT_STARTED;
    break;

  default:
    Status = EFI_DEVICE_ERROR;
    break;
  }

  gBS->RestoreTPL (OldTpl);
  return Status;
}

EFI_STATUS
STATIC
EFIAPI
EthGetStatus (
  IN       EFI_SIMPLE_NETWORK_PROTOCOL *This,
     OUT   UINT32 *InterruptStatus OPTIONAL,
     OUT   VOID **TxBuf OPTIONAL
  )
{
  ENET_DXE_PRIVATE_DATA *Private = NULL;
  EFI_TPL     OldTpl;
  EFI_STATUS  Status;

  if (This == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (InterruptStatus == NULL && TxBuf == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Private = ENET_DXE_PRIVATE_DATA_FROM_SNP_THIS (This);
  if (Private == NULL) {
    return EFI_DEVICE_ERROR;
  }

  OldTpl = gBS->RaiseTPL (TPL_CALLBACK);

  DEBUG ((EFI_D_ERROR, "EthGetStatus Private->Mode.State = %x \n" , Private->Mode.State));

  switch (Private->Mode.State) {
  case EfiSimpleNetworkInitialized:
    Status = ImplementGetStatus (Private, InterruptStatus, TxBuf);
    break;

  case EfiSimpleNetworkStopped:
    Status = EFI_NOT_STARTED;
    break;

  default:
    Status = EFI_DEVICE_ERROR;
    break;
  }

  gBS->RestoreTPL (OldTpl);
  return Status;
}

EFI_STATUS
STATIC
EFIAPI
EthTransmit (
  IN       EFI_SIMPLE_NETWORK_PROTOCOL *This,
  IN       UINTN HeaderSize,
  IN       UINTN BufferSize,
  IN       VOID *Buffer,
  IN       EFI_MAC_ADDRESS *SrcAddr OPTIONAL,
  IN       EFI_MAC_ADDRESS *DestAddr OPTIONAL,
  IN       UINT16 *Protocol OPTIONAL
  )
{
  ENET_DXE_PRIVATE_DATA *Private = NULL;
  EFI_STATUS  Status;
  EFI_TPL     OldTpl;

  if (This == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Private = ENET_DXE_PRIVATE_DATA_FROM_SNP_THIS (This);
  if (Private == NULL) {
    return EFI_DEVICE_ERROR;
  }

  OldTpl = gBS->RaiseTPL (TPL_CALLBACK);

  DEBUG ((EFI_D_ERROR, "EthTransmit Private->Mode.State = %x \n" , Private->Mode.State));

  switch (Private->Mode.State) {
  case EfiSimpleNetworkInitialized:
    break;

  case EfiSimpleNetworkStopped:
    Status = EFI_NOT_STARTED;
    gBS->RestoreTPL (OldTpl);
    return Status;

  default:
    Status = EFI_DEVICE_ERROR;
    gBS->RestoreTPL (OldTpl);
    return Status;
  }

  if (Buffer == NULL) {
    Status = EFI_INVALID_PARAMETER;
    gBS->RestoreTPL (OldTpl);
    return Status;
  }

  if (BufferSize < Private->Mode.MediaHeaderSize) {
    Status = EFI_BUFFER_TOO_SMALL;
    gBS->RestoreTPL (OldTpl);
    return Status;
  }

  //
  // if the HeaderSize is non-zero, we need to fill up the header and for that
  // we need the destination address and the protocol
  //
  if (HeaderSize != 0) {
    if (HeaderSize != Private->Mode.MediaHeaderSize || DestAddr == 0 || Protocol == 0) {
      Status = EFI_INVALID_PARAMETER;
      gBS->RestoreTPL (OldTpl);
      return Status;
    }

    Status = ImplementFillHeader (
                            Private,
                            Buffer,
                            HeaderSize,
                            (UINT8 *) Buffer + HeaderSize,
                            BufferSize - HeaderSize,
                            DestAddr,
                            SrcAddr,
                            Protocol
                            );

    if (EFI_ERROR (Status)) {
      gBS->RestoreTPL (OldTpl);
      return Status;
    }
  }

  Status = ImplementTransmit (Private, Buffer, BufferSize);
  // If packet sent, put buffer pointer into recycling list, which will be used by GetStatus
  // to determine if transfer complete. Actual buffer recycle will be done on upper level.
  if (EFI_SUCCESS == Status) {
    ((PXE_DB_GET_STATUS*)(Private->Db))->TxBuffer[TxCount++] = (UINTN) (UINT8 *) Buffer;
  }

  gBS->RestoreTPL (OldTpl);
  return Status;
}

EFI_STATUS
STATIC
EFIAPI
EthReceive (
  IN       EFI_SIMPLE_NETWORK_PROTOCOL *This,
     OUT   UINTN *HeaderSize OPTIONAL,
  IN OUT   UINTN *BufferSize,
     OUT   VOID *Buffer,
     OUT   EFI_MAC_ADDRESS *SrcAddr OPTIONAL,
     OUT   EFI_MAC_ADDRESS *DestAddr OPTIONAL,
     OUT   UINT16 *Protocol OPTIONAL
  )
{
  ENET_DXE_PRIVATE_DATA *Private = NULL;
  EFI_TPL     OldTpl;
  EFI_STATUS  Status;

  if (This == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Private = ENET_DXE_PRIVATE_DATA_FROM_SNP_THIS (This);
  if (Private == NULL) {
    return EFI_DEVICE_ERROR;
  }

  OldTpl = gBS->RaiseTPL (TPL_CALLBACK);

  switch (Private->Mode.State) {
  case EfiSimpleNetworkInitialized:
    if ((BufferSize == NULL) || (Buffer == NULL)) {
      Status = EFI_INVALID_PARAMETER;
	  DEBUG ((EFI_D_ERROR, "EthReceive  EFI_INVALID_PARAMETER \n" ));
    } else if (Private->Mode.ReceiveFilterSetting == 0) {
      DEBUG ((EFI_D_ERROR, "EthReceive  ReceiveFilterSetting EFI_DEVICE_ERROR \n" ));
      Status = EFI_DEVICE_ERROR;
    } else {
      Status = ImplementReceive (
                       Private,
                       Buffer,
                       BufferSize,
                       HeaderSize,
                       SrcAddr,
                       DestAddr,
                       Protocol
                       );
    }
    break;

  case EfiSimpleNetworkStopped:
    Status = EFI_NOT_STARTED;
    break;

  default:
    Status = EFI_DEVICE_ERROR;
    break;
  }

  gBS->RestoreTPL (OldTpl);
  return Status;
}

VOID
EnetDmaFreeBuffer (
  OUT ENET_DMA_BUFFER *DMA
  )
{
  if (DMA == NULL) {
    return;
  }
  if (DMA->DeviceAddress) {
    gBS->FreePages (DMA->DeviceAddress,
                    EFI_SIZE_TO_PAGES (DMA->BufferSize));
  }
}

EFI_STATUS
EnetDmaAllocBuffer (
  IN       UINTN BufferSize,
     OUT   ENET_DMA_BUFFER *DMA
  )
{
  EFI_STATUS Status = EFI_NOT_READY;

  DEBUG ((EFI_D_ERROR, "EnetDmaAllocBuffer  \n"));

  if ((DMA == NULL) || (BufferSize == 0)) {
    return EFI_INVALID_PARAMETER;
  }

  DMA->BufferSize = BufferSize;

  Status = gBS->AllocatePages (
    AllocateAnyPages,
    EfiBootServicesData,
    EFI_SIZE_TO_PAGES (BufferSize),
    (EFI_PHYSICAL_ADDRESS*)&DMA->DeviceAddress
    );

  DMA->HostAddress = (VOID *) (UINTN)DMA->DeviceAddress;
  DMA->Mapping = 0;
  SetMem ((VOID *) (UINTN)DMA->DeviceAddress, DMA->BufferSize, 0);

  return EFI_SUCCESS;
}

EFI_STATUS
STATIC
PrivateDataInit (
  OUT ENET_DXE_PRIVATE_DATA *Private
  )
{
  UINTN BufferSize;
  UINT32 Index;
  EFI_STATUS Status = EFI_NOT_READY;

  if (Private == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  SetMem (Private, sizeof (ENET_DXE_PRIVATE_DATA), 0);
  //
  //  Set SnpDxe's function pointer
  //
  Private->Signature    = ENET_DRIVER_SIGNATURE;
  Private->DeviceHandle = NULL;
  Private->Snp.Revision = EFI_SIMPLE_NETWORK_PROTOCOL_REVISION;
  Private->Snp.Start                 = EthStart;
  Private->Snp.Stop                  = EthStop;
  Private->Snp.Initialize            = EthInitialize;
  Private->Snp.Reset                 = EthReset;
  Private->Snp.Shutdown              = EthShutdown;
  Private->Snp.ReceiveFilters        = EthReceiveFilters;
  Private->Snp.StationAddress        = EthStationAddress;
  Private->Snp.Statistics            = EthStatistics;
  Private->Snp.MCastIpToMac          = EthMCastIpToMac;
  Private->Snp.NvData                = EthNvData;
  Private->Snp.GetStatus             = EthGetStatus;
  Private->Snp.Transmit              = EthTransmit;
  Private->Snp.Receive               = EthReceive;
  Private->Snp.WaitForPacket         = NULL;
  Private->Snp.Mode                  = NULL;
  //
  //  Initialize simple network protocol mode structure
  //
  Private->Mode.State                = EfiSimpleNetworkStopped;
  Private->Mode.HwAddressSize        = ENET_ADDR_LEN;
  Private->Mode.MediaHeaderSize      = sizeof (ENET_HEADER);
  Private->Mode.MaxPacketSize        = ENET_MAX_PACKET_SIZE;
  Private->Mode.NvRamSize            = ENET_NVRAM_SIZE;
  Private->Mode.NvRamAccessSize      = ENET_NVRAM_ACCESS_SIZE;
  Private->Mode.ReceiveFilterMask =
    EFI_SIMPLE_NETWORK_RECEIVE_UNICAST                 |
    EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST               |
    EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST               |
    EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS             |
    EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS_MULTICAST;
  Private->Mode.ReceiveFilterSetting =
    EFI_SIMPLE_NETWORK_RECEIVE_UNICAST                 |
    EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST;
  Private->Mode.MaxMCastFilterCount = MAX_MCAST_FILTER_CNT;
  Private->Mode.MCastFilterCount = 0;
  SetMem (Private->Mode.MCastFilter,       sizeof (Private->Mode.MCastFilter),      0);
  SetMem (&Private->Mode.CurrentAddress,   sizeof (Private->Mode.CurrentAddress),   0);
  SetMem (&Private->Mode.BroadcastAddress, sizeof (Private->Mode.BroadcastAddress), 0);
  SetMem (&Private->Mode.PermanentAddress, sizeof (Private->Mode.PermanentAddress), 0);
  Private->Mode.IfType                = ENET_IFTYPE;
  Private->Mode.MacAddressChangeable  = FALSE;
  Private->Mode.MultipleTxSupported   = FALSE;
  Private->Mode.MediaPresentSupported = TRUE;
  Private->Mode.MediaPresent          = FALSE;
  Private->Snp.Mode                   = &Private->Mode;
  Private->DevicePath.EthDevicePath.Header.Type      = MESSAGING_DEVICE_PATH;
  Private->DevicePath.EthDevicePath.Header.SubType   = MSG_MAC_ADDR_DP;
  Private->DevicePath.EthDevicePath.Header.Length[0] = sizeof (MAC_ADDR_DEVICE_PATH);
  Private->DevicePath.EthDevicePath.Header.Length[1] = 0;
  Private->DevicePath.EthDevicePath.IfType    = ENET_IFTYPE;
  Private->DevicePath.EndDevicePath.Type      = END_DEVICE_PATH_TYPE;
  Private->DevicePath.EndDevicePath.SubType   = END_ENTIRE_DEVICE_PATH_SUBTYPE;
  Private->DevicePath.EndDevicePath.Length[0] = sizeof (EFI_DEVICE_PATH_PROTOCOL);
  Private->DevicePath.EndDevicePath.Length[1] = 0;
  //Program Base address for XPCS and XGBE for each port
  Status = XgbeBaseAddr (Private);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  
  XgbePlatinit (Private);
  
  xgbe_phy_init (Private);
  
  XgbePlatinit (Private);

  Status = EthSetMacAddrFromPcd (Private->xgmac_pdata.xgmac_regs, Private->DevicePath.EthDevicePath.MacAddress.Addr);

  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }
  SetMem (
    Private->Mode.BroadcastAddress.Addr,
    sizeof (Private->Mode.BroadcastAddress.Addr),
    0xFF
    );

  CopyMem (
    Private->Mode.CurrentAddress.Addr,
    Private->DevicePath.EthDevicePath.MacAddress.Addr,
    sizeof (Private->DevicePath.EthDevicePath.MacAddress.Addr)
    );

  CopyMem (
    Private->Mode.PermanentAddress.Addr,
    Private->Mode.CurrentAddress.Addr,
    sizeof (Private->Mode.CurrentAddress.Addr)
    );

  // Allocate for DB struct
  Private->Db = NULL;
  Status = gBS->AllocatePool (EfiBootServicesData, 2048, (VOID*)&(Private->Db));
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_NET, "\nCould not allocate DB structures.\n"));
    ASSERT_EFI_ERROR (Status);
    return Status;
  }
  ZeroMem(Private->Db,2048);

  // Allocate for tx/rx desc
  Private->desc_tx_index = 0;
  DEBUG ((EFI_D_ERROR, "desc_tx_index : 0x%lx\n", &Private->desc_tx_index));
  Private->desc_rx_index = 0;
  DEBUG ((EFI_D_ERROR, "desc_rx_index : 0x%lx\n", &Private->desc_rx_index));
  BufferSize = (sizeof (TX_NORMAL_DESC) * TX_DESC_CNT);

  Status = EnetDmaAllocBuffer (BufferSize, &Private->desc_tx_dma);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Private->desc_tx = (VOID *) (UINTN) Private->desc_tx_dma.DeviceAddress;
  DEBUG ((EFI_D_ERROR, "desc_tx : 0x%lx\n", Private->desc_tx));

  BufferSize = (sizeof (RX_NORMAL_DESC) * RX_DESC_CNT);
  Status = EnetDmaAllocBuffer (BufferSize, &Private->desc_rx_dma);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Private->desc_rx = (VOID *) (UINTN) Private->desc_rx_dma.DeviceAddress;
  DEBUG ((EFI_D_ERROR, "desc_rx : 0x%lx\n", Private->desc_rx));

  BufferSize = ENET_MAX_PACKET_SIZE;
  for (Index = 0; Index < TX_DESC_CNT; Index++) {
    Status = EnetDmaAllocBuffer (BufferSize, &Private->pkt_tx_dma[Index]);
    if (EFI_ERROR (Status)) {
      return Status;
    }
    //DEBUG ((EFI_D_ERROR, "pkt%02d_tx : 0x%lx\n", Index, Private->pkt_tx_dma[Index].DeviceAddress));
  }

  BufferSize = ENET_MAX_PACKET_SIZE;
  for (Index = 0; Index < RX_DESC_CNT; Index++) {
    Status = EnetDmaAllocBuffer (BufferSize, &Private->pkt_rx_dma[Index]);
    if (EFI_ERROR (Status)) {
      return Status;
    }
    //DEBUG ((EFI_D_ERROR, "pkt%02d_rx : 0x%lx\n", Index, Private->pkt_rx_dma[Index].DeviceAddress));
  }

  xgmac_get_all_hw_features (&Private->xgmac_pdata);
  xgmac_default_config (&Private->xgmac_pdata);
  Private->xgmac_pdata.channel.pdata = &Private->xgmac_pdata;
  Private->xgmac_pdata.channel.dma_regs =
  Private->xgmac_pdata.xgmac_regs + DMA_CH_BASE; // + (DMA_CH_INC * i)
  Private->xgmac_pdata.rx_riwt = 0x3A;//4b;
  Private->xgmac_pdata.rx_frames = 0x10;
  Private->xgmac_pdata.rx_buf_size = ENET_MAX_PACKET_SIZE;

  return EFI_SUCCESS;
}

VOID
EFIAPI
SWResetXGMAC (
  IN       EFI_EVENT Event,
  IN       VOID *Context
  )
{
  ENET_DXE_PRIVATE_DATA *Private;
  UINT32 CheckValue;
  UINT32 XgmacBase;
    
  Private  = (ENET_DXE_PRIVATE_DATA *)Context;
  XgmacBase = Private->xgmac_pdata.xgmac_regs;
  
  DEBUG ((EFI_D_ERROR, "PXEDEBUG : SWResetXGMAC entry\n"));
  
  // Bit0 SWR - Software Reset
  //XGMAC_IOWRITE32 (&Private->xgmac_pdata, DMA_MR, 0x1);
  setBitfieldReg32 (XgmacBase + INT_EN, 0, 20, 0x000000);
  
  // S/W Reset
  MmioWrite32 (XgmacBase + 0x00003000, 0x00000001);
  while (1) {
  // wait for done
    CheckValue = getBitfieldReg32 ((UINT32)XgmacBase + 0x00003000, 0, 1);
    if (CheckValue == 0x0) {
      break;
    }
    gBS->Stall (1000);
  }

  DEBUG ((EFI_D_ERROR, "PXEDEBUG : SWResetXGMAC exit\n"));
}


EFI_STATUS
EFIAPI
AmdXgbeInit (
  VOID
        )
{
  EFI_EVENT              SnpExitBootServicesEvent;
  EFI_STATUS Status;
  ENET_DXE_PRIVATE_DATA *Private;
  MAC_ADDR_DEVICE_PATH MacNode;
  EFI_EVENT                   LegacyBootEvent;

  LegacyBootEvent          = NULL;
  SnpExitBootServicesEvent = NULL;
  Status = EFI_SUCCESS;

  Private = AllocateZeroPool (sizeof (ENET_DXE_PRIVATE_DATA));
  if (Private == NULL) {
    DEBUG ((EFI_D_ERROR, "Could not allocate ENET_DXE_PRIVATE_DATA structures.\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  Status = PrivateDataInit (Private);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "AmdEnet Private Data inital failure\r\n"));
    FreePool (Private);
    Private = NULL;
    return Status;
  }

  CopyMem (&MacNode, &Private->DevicePath, sizeof (MAC_ADDR_DEVICE_PATH));
  Private->FullDevicePath = AppendDevicePathNode (PciDevicePath, &MacNode.Header);

  gPrivate = Private;
  Private->DeviceHandle = NULL;

  Status = gBS->InstallMultipleProtocolInterfaces (
    &Private->DeviceHandle,
    &gEfiDevicePathProtocolGuid,
    Private->FullDevicePath,
    &gEfiSimpleNetworkProtocolGuid,
    &Private->Snp,
    NULL
    );

  Status = gBS->CreateEventEx (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    SWResetXGMAC,
                    Private,
                    &gEfiEventExitBootServicesGuid,
                    &SnpExitBootServicesEvent
                    );

  ASSERT_EFI_ERROR (Status);

  Status = gBS->CreateEventEx (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    SWResetXGMAC,
                    Private,
                    &gEfiEventLegacyBootGuid,
                    &LegacyBootEvent
                    );

  ASSERT_EFI_ERROR (Status);

  return Status;
}

