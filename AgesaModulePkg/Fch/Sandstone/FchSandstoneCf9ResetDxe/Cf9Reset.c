/* $NoKeywords:$ */
/**
 * @file
 *
 * FCH DXE Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project   FCH DXE Driver
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 10:28:05 -0800 (Tue, 09 Dec 2014) $
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

#include "Cf9Reset.h"
#define FILECODE UEFI_DXE_CF9RESET_CF9RESET_FILECODE


//
// The handle onto which the Reset Architectural Protocol is installed
//
EFI_HANDLE  mResetHandle = NULL;


UINT16
ReadPmio16 (
  IN       UINT8        Index
  )
{
  UINT8    bTemp;

  IoWrite8 (FCH_IOMAP_REGCD6, Index);
  bTemp = IoRead8 (FCH_IOMAP_REGCD7);
  IoWrite8 (FCH_IOMAP_REGCD6, Index + 1);
  return (UINT16) ((IoRead8 (FCH_IOMAP_REGCD7) << 8) + bTemp);
}


VOID
EFIAPI
Cf9ResetSystem (
  IN EFI_RESET_TYPE   ResetType,
  IN EFI_STATUS       ResetStatus,
  IN UINTN            DataSize,
  IN CHAR16           *ResetData OPTIONAL
  )
/*++

Routine Description:

  Reset the system.

Arguments:

    ResetType - warm or cold
    ResetStatus - possible cause of reset
    DataSize - Size of ResetData in bytes
    ResetData - Optional Unicode string
    For details, see efiapi.h

Returns:
  Does not return if the reset takes place.
  EFI_INVALID_PARAMETER   If ResetType is invalid.

--*/
{
  UINT8      InitialData;
  UINT8      OutputData;
  UINT8      PwrRsrCfg;
  UINT16     AcpiGpeBase;
  UINT16     AcpiPm1StsBase;
  UINT16     AcpiPm1CntBase;
  UINT32     Gpe0Enable;
  UINT16     PmCntl;
  UINT16     PwrSts;
  BOOLEAN    IsFullHardReset = FALSE;
  UINT8      SleepIoWriteWidth;

  DEBUG ((DEBUG_INFO, "[FchCf9Reset] ResetSystem invoked:  ResetType = %d\n", ResetType));
  switch (ResetType) {
  //
  // For update resets, the reset data is a null-terminated string followed
  // by a VOID * to the capsule descriptors. Get the pointer and set the
  // capsule variable before we do a warm reset. Per the EFI 1.10 spec, the
  // reset data is only valid if ResetStatus != EFI_SUCCESS.
  //
  case EfiResetWarm:
    InitialData = HARDSTARTSTATE;
    OutputData  = HARDRESET;
    IoWrite8 (FCH_IOMAP_REGCD6, 0x10);
    PwrRsrCfg = IoRead8 (FCH_IOMAP_REGCD7);
    PwrRsrCfg = PwrRsrCfg & 0xFD; //clear ToggleAllPwrGoodOnCf9
    IoWrite8 (FCH_IOMAP_REGCD7, PwrRsrCfg);
    break;

  case EfiResetCold:
    InitialData = HARDSTARTSTATE;
    IsFullHardReset = PcdGetBool (PcdFchFullHardReset);
    if (IsFullHardReset){
      OutputData  = FULLRESET;
    }else{
      OutputData  = HARDRESET;
    }
    IoWrite8 (FCH_IOMAP_REGCD6, 0x10);
    PwrRsrCfg = IoRead8 (FCH_IOMAP_REGCD7);
    PwrRsrCfg = PwrRsrCfg | BIT1; //set ToggleAllPwrGoodOnCf9
    IoWrite8 (FCH_IOMAP_REGCD7, PwrRsrCfg);
    break;

  case EfiResetShutdown:
    // Disable all GPE0 Event
    AcpiGpeBase = ReadPmio16 (FCH_PMIOA_REG68);
    AcpiGpeBase += 4; //Get enable base
    Gpe0Enable  = 0;
    IoWrite32 (AcpiGpeBase, Gpe0Enable);

    // Clear Power Button status.
    AcpiPm1StsBase = ReadPmio16 (FCH_PMIOA_REG60);
    PwrSts  = BIT8 | BIT15; //Clear WakeStatus with PwrBtnStatus
    IoWrite16 (AcpiPm1StsBase, PwrSts);

    // Transform system into S5 sleep state
    AcpiPm1CntBase = ReadPmio16 (FCH_PMIOA_REG62);
    PmCntl  = IoRead16 (AcpiPm1CntBase);
    PmCntl  = (PmCntl & ~SLP_TYPE) | SUS_S5 | SLP_EN;

    SleepIoWriteWidth = PcdGet8 (PcdFchPmCtrlSlpIoWrWidth);
    if (SleepIoWriteWidth == 0x01) { // Byte IO write Width
      IoWrite8 (AcpiPm1CntBase + 1, (UINT8)(PmCntl >> 8));
    } else {
      IoWrite16 (AcpiPm1CntBase, PmCntl);
    }

    return ;

  default:
    return ;
  }

  AcpiPm1CntBase = ReadPmio16 (FCH_PMIOA_REG62);
  PmCntl  = IoRead16 (AcpiPm1CntBase);
  if (PmCntl & BIT0) {
    //FCH_DEADLOOP ();
    // ProgramLpcEmmcPins (FALSE);
  }
  IoWrite8 (FCH_IOMAP_REGCF9, InitialData);
  IoWrite8 (FCH_IOMAP_REGCF9, OutputData);

  //
  // Given we should have reset getting here would be bad
  //
  FCH_DEADLOOP();
}

/********************************************************************************
 * Name: InitializeCf9Reset
 *
 * Description
 *   Cf9ResetDxe Entrypoint
 *
 * Input
 *   ImageHandle : EFI Image Handle for the DXE driver
 *   SystemTable : pointer to the EFI system table
 *
 * Output
 *   EFI_SUCCESS : Module initialized successfully
 *   EFI_ERROR   : Initialization failed (see error for more details)
 *
 *********************************************************************************/
EFI_STATUS
EFIAPI
InitializeCf9Reset (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
/*++

Routine Description:

  Initialize the state information for the Timer Architectural Protocol

Arguments:

  ImageHandle of the loaded driver
  Pointer to the System Table

Returns:

  Status

  EFI_SUCCESS           - thread can be successfully created
  EFI_OUT_OF_RESOURCES  - cannot allocate protocol data structure
  EFI_DEVICE_ERROR      - cannot create the timer service

--*/
{
  EFI_STATUS  Status;
  UINT32      ProtocolPointer;

  //
  // Check if the Reset Architectural Protocol is already installed in the system
  //
  Status = gBS->LocateProtocol (&gEfiResetArchProtocolGuid, NULL, (VOID **) &ProtocolPointer);
  if ( Status != EFI_NOT_FOUND) {
    //Already installed
    return EFI_UNSUPPORTED;
  }

  //
  // Hook the runtime service table
  //
  SystemTable->RuntimeServices->ResetSystem = Cf9ResetSystem;

  //
  // Now install the Reset RT AP on a new handle
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &mResetHandle,
                  &gEfiResetArchProtocolGuid,
                  NULL,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}


