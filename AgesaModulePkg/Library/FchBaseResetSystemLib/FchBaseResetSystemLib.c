/* $NoKeywords:$ */
/**
 * @file
 *
 * FCH BaseReset Lib
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

/** @file
  Library to support reset library, inheritted from Agesa Cf9Reset module.

  Copyright (c) 2018, Microsoft Corporation. All rights reserved.<BR>

**/

#include <Uefi.h>
#include "AMD.h"
#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/FchBaseLib.h>
#include <Protocol/Reset.h>
#include <Library/ResetSystemLib.h>
#include <FchRegistersCommon.h>

//
// Reset control register values
//
#define FULLRESET       0x0E
#define HARDRESET       0x06
#define SOFTRESET       0x04
#define HARDSTARTSTATE  0x02
#define SOFTSTARTSTATE  0x00

#define SUS_S3          0x0C00U     // S3
#define SUS_S5          0x1400U     // S4
#define SLP_TYPE        0x1C00U     // MASK
#define SLP_EN          0x2000U     // BIT13

/**
  This function causes a system-wide reset (cold reset), in which
  all circuitry within the system returns to its initial state. This type of reset 
  is asynchronous to system operation and operates without regard to 
  cycle boundaries.

  If this function returns, it means that the system does not support cold reset. 
**/
VOID
EFIAPI
ResetCold (
  VOID
)
{
  UINT8      InitialData; 
  UINT8      OutputData;
  UINT8      PwrRsrCfg;
  BOOLEAN    IsFullHardReset = FALSE;

  DEBUG(( DEBUG_INFO, __FUNCTION__" - enter..\n" ));

  InitialData = HARDSTARTSTATE;
  IsFullHardReset = PcdGetBool (PcdFchFullHardReset);
  if (IsFullHardReset){
    OutputData  = FULLRESET;
  }else{
    OutputData  = HARDRESET;
  }
  IoWrite8 (FCH_IOMAP_REGCD6, 0x10);
  PwrRsrCfg = IoRead8 (FCH_IOMAP_REGCD7);
  PwrRsrCfg = PwrRsrCfg | BIT1;                          //set ToggleAllPwrGoodOnCf9
  IoWrite8 (FCH_IOMAP_REGCD7, PwrRsrCfg);

  IoWrite8 (FCH_IOMAP_REGCF9, InitialData);
  IoWrite8 (FCH_IOMAP_REGCF9, OutputData);

  //
  // Given we should have reset getting here would be bad
  //
  DEBUG(( DEBUG_ERROR, __FUNCTION__" - should never be here!!!\n" ));
  FCH_DEADLOOP();
}

/**
  This function causes a system-wide initialization (warm reset), in which all processors 
  are set to their initial state. Pending cycles are not corrupted.

  If this function returns, it means that the system does not support warm reset.
**/
VOID
EFIAPI
ResetWarm (
  VOID
)
{
  UINT8      InitialData; 
  UINT8      OutputData;
  UINT8      PwrRsrCfg;

  DEBUG(( DEBUG_INFO, __FUNCTION__" - enter..\n" ));

  InitialData = HARDSTARTSTATE;
  OutputData  = HARDRESET;
  IoWrite8 (FCH_IOMAP_REGCD6, 0x10);
  PwrRsrCfg = IoRead8 (FCH_IOMAP_REGCD7);
  PwrRsrCfg = PwrRsrCfg & 0xFD;                          //clear ToggleAllPwrGoodOnCf9
  IoWrite8 (FCH_IOMAP_REGCD7, PwrRsrCfg);

  IoWrite8 (FCH_IOMAP_REGCF9, InitialData);
  IoWrite8 (FCH_IOMAP_REGCF9, OutputData);

  //
  // Given we should have reset getting here would be bad
  //
  DEBUG(( DEBUG_ERROR, __FUNCTION__" - should never be here!!!\n" ));
  FCH_DEADLOOP();
}

/**
  This function causes the system to enter a power state equivalent 
  to the ACPI G2/S5 or G3 states.
  
  If this function returns, it means that the system does not support shutdown reset.
**/
VOID
EFIAPI
ResetShutdown (
  VOID
)
{
  UINT16     AcpiGpeBase;
  UINT16     AcpiPm1StsBase;
  UINT16     AcpiPm1CntBase;
  UINT32     Gpe0Enable;
  UINT16     PmCntl;
  UINT16     PwrSts;

  DEBUG(( DEBUG_INFO, __FUNCTION__" - enter..\n" ));

  // Disable all GPE0 Event
  FchReadPmio (FCH_PMIOA_REG68, AccessWidth16, &AcpiGpeBase);
  AcpiGpeBase += 4; //Get enable base
  Gpe0Enable  = 0;
  IoWrite32 (AcpiGpeBase, Gpe0Enable);

  // Clear Power Button status.
  FchReadPmio (FCH_PMIOA_REG60, AccessWidth16, &AcpiPm1StsBase);
  PwrSts  = BIT8 | BIT15; //Clear WakeStatus with PwrBtnStatus
  IoWrite16 (AcpiPm1StsBase, PwrSts);

  // Transform system into S5 sleep state
  FchReadPmio (FCH_PMIOA_REG62, AccessWidth16, &AcpiPm1CntBase);
  PmCntl  = IoRead16 (AcpiPm1CntBase);
  PmCntl  = (PmCntl & ~SLP_TYPE) | SUS_S5 | SLP_EN;
  IoWrite16 (AcpiPm1CntBase, PmCntl);

  //
  // Given we should have shutdown getting here would be bad
  //
  DEBUG(( DEBUG_ERROR, __FUNCTION__" - should never be here!!!\n" ));
  FCH_DEADLOOP();
}

/**
  This function causes the system to enter S3 and then wake up immediately.
  
  If this function returns, it means that the system does not support S3 feature.
**/
VOID
EFIAPI
EnterS3WithImmediateWake (
  VOID
)
{
  DEBUG(( DEBUG_ERROR, __FUNCTION__" - No S3WithImmediateWake handler found!\n" ));
  ASSERT (FALSE);
}

/**
  This function causes a systemwide reset. The exact type of the reset is
  defined by the EFI_GUID that follows the Null-terminated Unicode string passed
  into ResetData. If the platform does not recognize the EFI_GUID in ResetData
  the platform must pick a supported reset type to perform.The platform may
  optionally log the parameters from any non-normal reset that occurs.

  @param[in]  DataSize   The size, in bytes, of ResetData.
  @param[in]  ResetData  The data buffer starts with a Null-terminated string,
                         followed by the EFI_GUID.
**/
VOID
EFIAPI
ResetPlatformSpecific (
  IN UINTN   DataSize,
  IN VOID    *ResetData
)
{
  DEBUG(( DEBUG_ERROR, __FUNCTION__" - No PlatformSpecific reset handler found!\n" ));
  ASSERT( FALSE );
  ResetCold();
}
