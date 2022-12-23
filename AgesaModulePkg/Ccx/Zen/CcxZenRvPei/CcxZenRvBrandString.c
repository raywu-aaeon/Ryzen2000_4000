/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD CCX brand string
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Ccx
 * @e \$Revision$   @e \$Date$
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

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include "AGESA.h"
#include "Filecode.h"
#include "cpuRegisters.h"
#include "Library/PeiServicesTablePointerLib.h"
#include "Ppi/NbioSmuServicesPpi.h"
#include <Library/CcxBaseX86Lib.h>
#include <Library/IdsLib.h>
#include "PiPei.h"

#define FILECODE CCX_ZEN_CCXZENRVPEI_CCXZENRVBRANDSTRING_FILECODE

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */
/// A structure containing brand string
typedef struct {
  CONST CHAR8 *Stringstart;  ///< The literal string
} CPU_F17_ZP_EXCEPTION_BRAND;

/*---------------------------------------------------------------------------------------
 *               T Y P E D E F S,   S T R U C T U R E S,    E N U M S
 *---------------------------------------------------------------------------------------
 */
/// A structure containing brand string
typedef struct {
  CONST CHAR8 *Stringstart;  ///< The literal string
} CPU_F17_EXCEPTION_BRAND;

// This is an example, need to be updated once Processor Revision Guide define brand string exception
// Brand string is always 48 bytes
//CONST CHAR8 ROMDATA str_Exception_0[48] = "AMD PRO A12-8800B R7, 12 Compute Cores 4C+8G";
CONST CHAR8 ROMDATA str_Unprogrammed_Sample[48] = "AMD Unprogrammed Engineering Sample";

CONST CPU_F17_EXCEPTION_BRAND ROMDATA CpuF17ExceptionBrandIdString[] =
{
//  str_Exception_0
  NULL
};

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
BOOLEAN
STATIC
IsException (
     OUT   UINT32                 *ExceptionId,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*---------------------------------------------------------------------------------------*/
/**
* Set the Processor Name String register based on fuses.
*
*  @param[in]   StdHeader           Config handle for library and services.
*
*/
VOID
CcxZenRvSetBrandString (
  IN       AMD_CONFIG_PARAMS  *StdHeader
  )
{
  UINT32                         ExceptionId;
  UINT32                         MsrIndex;
  UINT64                         *MsrNameStringPtrPtr;
  EFI_STATUS                     Status;
  EFI_PEI_SERVICES               **PeiServices;
  PEI_AMD_NBIO_SMU_SERVICES_PPI  *GnbSmuService;
  UINT64                         BrandString[6];

  BrandString[5] = 0;
  MsrNameStringPtrPtr = (UINT64 *) str_Unprogrammed_Sample;
  if (IsException (&ExceptionId, StdHeader)) {
    ASSERT (ExceptionId < ((sizeof (CpuF17ExceptionBrandIdString) / sizeof (CpuF17ExceptionBrandIdString[0])) - 1));
    MsrNameStringPtrPtr = (UINT64 *) CpuF17ExceptionBrandIdString[ExceptionId].Stringstart;
  } else {
    // Normally, we get Name String from the SMU
    IDS_HDT_CONSOLE (CPU_TRACE, "    Set brand string");
    PeiServices = (EFI_PEI_SERVICES **) GetPeiServicesTablePointer ();
    Status = (**PeiServices).LocatePpi (
              PeiServices,
              &gAmdNbioSmuServicesPpiGuid,
              0,
              NULL,
              &GnbSmuService
              );
    if (EFI_ERROR (Status)) {
      IDS_HDT_CONSOLE (CPU_TRACE, "    Can not locate SMU PPI");
    } else if (GnbSmuService->SmuReadBrandString (GnbSmuService, 0, ((sizeof (BrandString)) - 1), (UINT8 *) &BrandString[0]) != EFI_SUCCESS) {
      IDS_HDT_CONSOLE (CPU_TRACE, "    SMU PPI returned an error");
    } else {
      MsrNameStringPtrPtr = &BrandString[0];
    }
  }
  // Put values into name MSRs,  Always write the full 48 bytes
  for (MsrIndex = MSR_CPUID_NAME_STRING0; MsrIndex <= MSR_CPUID_NAME_STRING5; MsrIndex++) {
    AsmWriteMsr64 (MsrIndex, *MsrNameStringPtrPtr);
    MsrNameStringPtrPtr++;
  }
}

/*---------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *---------------------------------------------------------------------------------------
 */

/*---------------------------------------------------------------------------------------*/
/**
* Check if it's an exception
*
* For family 17h, brand string is obtained from D0F0xBC_xD021_108C, but there may be exceptions.
* This function checks if it's an exception.
*
*  @param[out]  ExceptionId         Id of exception
*  @param[in]   StdHeader           Config handle for library and services.
*
*  @retval      TRUE                It's an exception
*  @retval      FALSE               It's NOT an exception
*/
BOOLEAN
STATIC
IsException (
     OUT   UINT32             *ExceptionId,
  IN       AMD_CONFIG_PARAMS  *StdHeader
  )
{
  *ExceptionId = 0xFFFF;
  return FALSE;
}

