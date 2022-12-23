/* $NoKeywords:$ */
/**
 * @file
 *
 * Provide family specifical data that RAS needs.
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  CCX
 * @e \$Revision$   @e \$Date$
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
#include <Library/BaseLib.h>
#include "AGESA.h"
#include "Filecode.h"
#include "Library/AmdBaseLib.h"
#include "Library/UefiBootServicesTableLib.h"
#include "Protocol/AmdAcpiRasServicesProtocol.h"


#define FILECODE CCX_ZEN_CCXZENZPDXE_CCXZENZPACPIRAS_FILECODE



/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

EFI_STATUS
EFIAPI
CcxZenZpGetMcBankInfo (
  IN       AMD_CCX_ACPI_RAS_SERVICES_PROTOCOL         *This,
     OUT   AMD_MC_INIT_DATA                          **McBankInfo
  );

/*----------------------------------------------------------------------------------------
 *                           G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */
STATIC AMD_CCX_ACPI_RAS_SERVICES_PROTOCOL   mZenZpRasServicesProtocol = {
  1,
  CcxZenZpGetMcBankInfo
};


STATIC AMD_MC_BANK_INIT_DATA ROMDATA mZenZpMcBankInitData[] = {
  {0xFFFFFFFFFFFFFFFF,0xC0002000,0xC0002001,0xC0002002,0xC0002003},      //Bank 0
  {0xFFFFFFFFFFFFFFFF,0xC0002010,0xC0002011,0xC0002012,0xC0002013},      //Bank 1
  {0xFFFFFFFFFFFFFFFF,0xC0002020,0xC0002021,0xC0002022,0xC0002023},      //Bank 2
  {0xFFFFFFFFFFFFFFFF,0xC0002030,0xC0002031,0xC0002032,0xC0002033},      //Bank 3
  {0x0000000000000000,0xC0002040,0xC0002041,0xC0002042,0xC0002043},      //Bank 4 unused
  {0xFFFFFFFFFFFFFFFF,0xC0002050,0xC0002051,0xC0002052,0xC0002053},      //Bank 5
  {0xFFFFFFFFFFFFFFFF,0xC0002060,0xC0002061,0xC0002062,0xC0002063},      //Bank 6
  {0xFFFFFFFFFFFFFFFF,0xC0002070,0xC0002071,0xC0002072,0xC0002073},      //Bank 7
  {0xFFFFFFFFFFFFFFFF,0xC0002080,0xC0002081,0xC0002082,0xC0002083},      //Bank 8
  {0xFFFFFFFFFFFFFFFF,0xC0002090,0xC0002091,0xC0002092,0xC0002093},      //Bank 9
  {0xFFFFFFFFFFFFFFFF,0xC00020A0,0xC00020A1,0xC00020A2,0xC00020A3},      //Bank 10
  {0xFFFFFFFFFFFFFFFF,0xC00020B0,0xC00020B1,0xC00020B2,0xC00020B3},      //Bank 11
  {0xFFFFFFFFFFFFFFFF,0xC00020C0,0xC00020C1,0xC00020C2,0xC00020C3},      //Bank 12
  {0xFFFFFFFFFFFFFFFF,0xC00020D0,0xC00020D1,0xC00020D2,0xC00020D3},      //Bank 13
  {0xFFFFFFFFFFFFFFFF,0xC00020E0,0xC00020E1,0xC00020E2,0xC00020E3},      //Bank 14
  {0xFFFFFFFFFFFFFFFF,0xC00020F0,0xC00020F1,0xC00020F2,0xC00020F3},      //Bank 15
  {0xFFFFFFFFFFFFFFFF,0xC0002100,0xC0002101,0xC0002102,0xC0002103},      //Bank 16
  {0xFFFFFFFFFFFFFFFF,0xC0002110,0xC0002111,0xC0002112,0xC0002113},      //Bank 17
  {0xFFFFFFFFFFFFFFFF,0xC0002120,0xC0002121,0xC0002122,0xC0002123},      //Bank 18
  {0xFFFFFFFFFFFFFFFF,0xC0002130,0xC0002131,0xC0002132,0xC0002133},      //Bank 19
  {0xFFFFFFFFFFFFFFFF,0xC0002140,0xC0002141,0xC0002142,0xC0002143},      //Bank 20
  {0xFFFFFFFFFFFFFFFF,0xC0002150,0xC0002151,0xC0002152,0xC0002153},      //Bank 21
  {0xFFFFFFFFFFFFFFFF,0xC0002160,0xC0002161,0xC0002162,0xC0002163},      //Bank 22
};

STATIC AMD_MC_INIT_DATA ROMDATA mZenZpMcaInitData = {
  0x0000000000000000,       // AmdGlobCapInitData
  0x000000000001FFEF,       // AmdGlobCtrlInitData
  0x00,                     // AmdMcbClrStatusOnInit
  0x02,                     // AmdMcbStatusDataFormat
  0x00,                     // Reserved
  (sizeof (mZenZpMcBankInitData) / sizeof (mZenZpMcBankInitData[0])), // McBankNum
  &mZenZpMcBankInitData[0]   // Pointer to Initial data of MC Bank
};


/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */



/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                          AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL
 *----------------------------------------------------------------------------------------
 */


EFI_STATUS
EFIAPI
CcxZenZpRasServicesProtocolInstall (
  IN       EFI_HANDLE        ImageHandle,
  IN       EFI_SYSTEM_TABLE  *SystemTable
  )
{
  // Install ACPI RAS services protocol
  return gBS->InstallProtocolInterface (
                &ImageHandle,
                &gAmdCcxAcpiRasServicesProtocolGuid,
                EFI_NATIVE_INTERFACE,
                &mZenZpRasServicesProtocol
                );
}

/**
 *---------------------------------------------------------------------------------------
 *
 *  CcxZenZpGetMcBankInfo
 *
 *  Description:
 *    This function provides MC bank init data.
 *
 *  Parameters:
 *    @param[in]  This                                 A pointer to the AMD_CCX_ACPI_RAS_SERVICES_PROTOCOL instance.
 *    @param[out] McBankInfo                           Contains MC bank init data
 *
 *    @retval     AGESA_STATUS
 *
 *---------------------------------------------------------------------------------------
 **/
EFI_STATUS
EFIAPI
CcxZenZpGetMcBankInfo (
  IN       AMD_CCX_ACPI_RAS_SERVICES_PROTOCOL         *This,
     OUT   AMD_MC_INIT_DATA                          **McBankInfo
  )
{
  *McBankInfo = &mZenZpMcaInitData;

  return EFI_SUCCESS;
}



