//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file BotPeim.h
    This file belongs to "Framework".
    This file is modified by AMI to include copyright message,
    appropriate header and integration code.

**/

//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//

/**
BOT Transportation implementation.

Copyright (c) 2006, Intel Corporation. All rights reserved.<BR>
  
This program and the accompanying materials
are licensed and made available under the terms and conditions
of the BSD License which accompanies this distribution.  The
full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/


#ifndef _PEI_BOT_PEIM_H
#define _PEI_BOT_PEIM_H

#define STATIC  static

#include "Atapi.h"

#pragma pack(1)

//
//Bulk Only device protocol
//
typedef struct
{
    UINT32 CbwSignature;
    UINT32 CbwTag;
    UINT32 CbwDataTransferLength;
    UINT8  CbwFlags;
    UINT8  CbwLUN;
    UINT8  CbwCBLength;
    UINT8  CbwCB[16];
} CBW;

typedef struct
{
    UINT32 CswSignature;
    UINT32 CswTag;
    UINT32 CswDataResidue;
    UINT8  CswStatus;
    UINT8  Filler[18];
} CSW;

#pragma pack()

//
// Status code, see Usb Bot device spec
//
#define CSWSIG  0x53425355
#define CBWSIG  0x43425355

EFI_STATUS
PeiUsbInquiry (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_BOT_DEVICE   *PeiBotDevice );

EFI_STATUS
PeiUsbTestUnitReady (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_BOT_DEVICE   *PeiBotDevice );

EFI_STATUS
PeiUsbRequestSense (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_BOT_DEVICE   *PeiBotDevice,
    IN UINT8            *SenseKeyBuffer );

EFI_STATUS
PeiUsbReadCapacity (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_BOT_DEVICE   *PeiBotDevice );

EFI_STATUS
PeiUsbReadFormattedCapacity (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_BOT_DEVICE   *PeiBotDevice );

EFI_STATUS
PeiUsbRead10 (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_BOT_DEVICE   *PeiBotDevice,
    IN VOID             *Buffer,
    IN EFI_PEI_LBA      Lba,
    IN UINTN            NumberOfBlocks );

BOOLEAN
IsNoMedia (
    IN REQUEST_SENSE_DATA *SenseData,
    IN UINTN              SenseCounts );

BOOLEAN
IsMediaError (
    IN REQUEST_SENSE_DATA *SenseData,
    IN UINTN              SenseCounts );

BOOLEAN
IsMediaChange (
    IN REQUEST_SENSE_DATA *SenseData,
    IN UINTN              SenseCounts );

#endif

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
