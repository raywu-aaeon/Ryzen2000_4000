/*++

   Copyright (c) 2005 Intel Corporation. All rights reserved
   This software and associated documentation (if any) is furnished
   under a license and may only be used or copied in accordance
   with the terms of the license. Except as permitted by such
   license, no part of this software or documentation may be
   reproduced, stored in a retrieval system, or transmitted in any
   form or by any means without the express written consent of
   Intel Corporation.


   Module Name:

   TpmPei.h

   Abstract:

   PEI driver for TPM devices

   --*/
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TcgNext/Common/TcgPei/TisPei.c 1     10/08/13 12:02p Fredericko $
//
// $Revision: 1 $
//
// $Date: 10/08/13 12:02p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TcgNext/Common/TcgPei/TisPei.c $
//
// 1     10/08/13 12:02p Fredericko
// Initial Check-In for Tpm-Next module
//
// 1     7/10/13 5:51p Fredericko
// [TAG]        EIP120969
// [Category]   New Feature
// [Description]    TCG (TPM20)
//
// 17    4/01/11 11:13a Fredericko
//
// 16    4/01/11 10:52a Fredericko
// Changes for TPM support in Legacy IO mode. Some TPMs do not allow init
// function to be called more than once during legacy mode.
//
// 15    3/31/11 4:49p Fredericko
// Changes for TCG_LEGACY support
//
// 14    3/29/11 12:57p Fredericko
//
// 13    3/28/11 2:06p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
//
// 12    5/19/10 5:44p Fredericko
// Included File Header
// Included File Revision History
// Code Beautification
// EIP 37653
//
//*************************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  TpmPei.c
//
// Description:
//  Abstracted functions for Tpm ppis' are defined here
//
//<AMI_FHDR_END>
//*************************************************************************
#include <Efi.h>
#include <AmiTcg/TcgTpm12.h>
#include <AmiTcg/TpmLib.h>
#include <Token.h>
#include <AmiTcg/TcgCommon12.h>
#include "Ppi/TcgService.h"
#include "Ppi/TpmDevice.h"
#include <Library/DebugLib.h>
#include <Guid/AmiTcgGuidIncludes.h>

extern EFI_GUID gTcgPeiPolicyGuid;

#define _CR( Record, TYPE,\
             Field )((TYPE*) ((CHAR8*) (Record) - (CHAR8*) &(((TYPE*) 0)->Field)))

#define INTEL_VID 0x8086
#define TCG_VID_OFFSET 0x0F00

BOOLEAN iTPMVerifyMeStatus( );

#define TPM_PEI_PRIVATE_DATA_FROM_THIS( This )  \
    _CR( This, TPM_PEI_PRIVATE_DATA, TpmPpi )

typedef struct _TPM_PEI_PRIVATE_DATA
{
    PEI_TPM_PPI          TpmPpi;
    EFI_PHYSICAL_ADDRESS BaseAddr;
} TPM_PEI_PRIVATE_DATA;


EFI_STATUS
EFIAPI TpmPeiInit(
    IN PEI_TPM_PPI      *This,
    IN EFI_PEI_SERVICES **PeiServices )
{
    TPM_PEI_PRIVATE_DATA *Private;

    Private = TPM_PEI_PRIVATE_DATA_FROM_THIS( This );
    return TisRequestLocality(
               (TPM_1_2_REGISTERS_PTR)( UINTN ) Private->BaseAddr);
}

EFI_STATUS
EFIAPI TpmPeiClose(
    IN PEI_TPM_PPI      *This,
    IN EFI_PEI_SERVICES **PeiServices )
{
    TPM_PEI_PRIVATE_DATA *Private;

    Private = TPM_PEI_PRIVATE_DATA_FROM_THIS( This );
    return TisReleaseLocality(
               (TPM_1_2_REGISTERS_PTR)( UINTN ) Private->BaseAddr);
}

EFI_STATUS
EFIAPI TpmPeiGetStatusInfo(
    IN PEI_TPM_PPI      *This,
    IN EFI_PEI_SERVICES **PeiServices )
{
    return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI TpmPeiTransmit(
    IN PEI_TPM_PPI             *This,
    IN EFI_PEI_SERVICES        **PeiServices,
    IN UINTN                   NoInputBuffers,
    IN TPM_TRANSMIT_BUFFER     *InputBuffers,
    IN UINTN                   NoOutputBuffers,
    IN OUT TPM_TRANSMIT_BUFFER *OutputBuffers )
{
    TPM_PEI_PRIVATE_DATA  *Private;
    TPM_1_2_REGISTERS_PTR TpmReg;

    Private = TPM_PEI_PRIVATE_DATA_FROM_THIS( This );
    TpmReg  = (TPM_1_2_REGISTERS_PTR)( UINTN ) Private->BaseAddr;
    return TpmLibPassThrough(
               TpmReg,
               NoInputBuffers,
               InputBuffers,
               NoOutputBuffers,
               OutputBuffers
           );
}

static TPM_PEI_PRIVATE_DATA   mTpmPrivate =
{
    {
        TpmPeiInit,
        TpmPeiClose,
        TpmPeiGetStatusInfo,
        TpmPeiTransmit
    },
    TPM_BASE_ADDRESS
};

static EFI_PEI_PPI_DESCRIPTOR mPpiList[] =
{
        { 
    EFI_PEI_PPI_DESCRIPTOR_PPI
    | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gPeiTpmPpiGuid,
    &mTpmPrivate.TpmPpi
        }
};


EFI_STATUS
EFIAPI TpmPeiEntry(
    IN EFI_PEI_FILE_HANDLE  FileHandle,
    IN CONST EFI_PEI_SERVICES    **PeiServices )
{
    EFI_STATUS Status = EFI_SUCCESS;
    BOOLEAN    Temp = TRUE;
    TCG_PLATFORM_SETUP_INTERFACE   *TcgPeiPolicy = NULL;
    TCG_CONFIGURATION              ConfigFlags;
    BOOLEAN     CrbSupport=0;


    Status = (*PeiServices)->LocatePpi(
                 PeiServices,
                 &gTcgPeiPolicyGuid,
                 0, NULL,
                 (void **)&TcgPeiPolicy);

    if(EFI_ERROR(Status) || TcgPeiPolicy == NULL )return Status;

    DEBUG((DEBUG_INFO, "before getTcgPeiPolicy\n"));
    Status = TcgPeiPolicy->getTcgPeiPolicy( (EFI_PEI_SERVICES    **)PeiServices, &ConfigFlags);

    if(ConfigFlags.DeviceType == 0)
    {
        (*PeiServices)->InstallPpi( PeiServices, mPpiList );
    }
    else
    {
        CrbSupport = isTpm20CrbPresent();
        DEBUG((DEBUG_INFO, "CrbSupport = %x \n", CrbSupport));
        if(!CrbSupport)
        {
            (*PeiServices)->InstallPpi( PeiServices, mPpiList );
        }
        else
        {
            return EFI_NOT_FOUND;
        }
    }

    DEBUG((DEBUG_INFO, "TpmDevice Ppi Installed\n"));
    DEBUG((DEBUG_INFO, "TpmPeientry ConfigFlags.DeviceType = %x\n", ConfigFlags.DeviceType));

    if ( Temp )
    {
#if defined (INTEL_ARCHITECTURE_SUPPORT_TCG) &&  (INTEL_ARCHITECTURE_SUPPORT_TCG == 1)
        Status = IsTpmPresent((TPM_1_2_REGISTERS_PTR)(
                                  UINTN ) mTpmPrivate.BaseAddr );

        DEBUG((DEBUG_INFO, "IsTpmPresent results = %r\n", Status));
        DEBUG((DEBUG_INFO, "IsTpmPresent base = %x\n",  mTpmPrivate.BaseAddr));
        DEBUG((DEBUG_INFO, "IsTpmPresent Access reg = %x\n", *(UINT8 *)(UINTN) mTpmPrivate.BaseAddr));
#else
        Status = EFI_NOT_FOUND;
#endif
        if ( EFI_ERROR( Status ))
        {
            return EFI_NOT_FOUND;
        }
    }

    return Status;
}
