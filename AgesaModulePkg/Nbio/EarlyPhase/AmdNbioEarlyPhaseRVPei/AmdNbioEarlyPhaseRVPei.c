/* $NoKeywords:$ */
/**
 * @file
 *
 * AmdNbioEarlyPhaseRVPei Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  AmdNbioEarlyPhaseRVPei
 * @e \$Revision: 312065 $   @e \$Date: 2018-08-10 10:09:05 +0800 (Fri, 10 Aug 2018) $
 *
 */
/*****************************************************************************
 *
 * Copyright 2008 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting You permission to use this software and documentation (if
 * any) (collectively, the "Software") pursuant to the terms and conditions of
 * the Software License Agreement included with the Software. If You do not have
 * a copy of the Software License Agreement, contact Your AMD representative for
 * a copy.
 *
 * You agree that You will not reverse engineer or decompile the Software, in
 * whole or in part, except as allowed by applicable law.
 *
 * WARRANTY DISCLAIMER: THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND. AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
 * BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, QUALITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT AND WARRANTIES
 * ARISING FROM CUSTOM OF TRADE OR COURSE OF USAGE WITH RESPECT TO THE SOFTWARE,
 * INCLUDING WITHOUT LIMITATION, THAT THE SOFTWARE WILL RUN UNINTERRUPTED OR
 * ERROR-FREE. THE ENTIRE RISK ASSOCIATED WITH THE USE OF THE SOFTWARE IS
 * ASSUMED BY YOU. Some jurisdictions do not allow the exclusion of implied
 * warranties, so the above exclusion may not apply to You, but only to the
 * extent required by law.
 *
 * LIMITATION OF LIABILITY AND INDEMNIFICATION: TO THE EXTENT NOT PROHIBITED BY
 * APPLICABLE LAW, AMD AND ITS LICENSORS WILL NOT, UNDER ANY CIRCUMSTANCES BE
 * LIABLE TO YOU FOR ANY PUNITIVE, DIRECT, INCIDENTAL, INDIRECT, SPECIAL OR
 * CONSEQUENTIAL DAMAGES ARISING FROM POSSESSION OR USE OF THE SOFTWARE OR
 * OTHERWISE IN CONNECTION WITH ANY PROVISION OF THIS AGREEMENT EVEN IF AMD AND
 * ITS LICENSORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. THIS
 * INCLUDES, WITHOUT LIMITATION, DAMAGES DUE TO LOST OR MISAPPROPRIATED DATA,
 * LOST PROFITS OR CONFIDENTIAL OR OTHER INFORMATION, FOR BUSINESS INTERRUPTION,
 * FOR PERSONAL INJURY, FOR LOSS OF PRIVACY, FOR FAILURE TO MEET ANY DUTY
 * INCLUDING OF GOOD FAITH OR REASONABLE CARE, FOR NEGLIGENCE AND FOR ANY OTHER
 * PECUNIARY OR OTHER LOSS WHTSOEVER. In no event shall AMD's total liability to
 * You for all damages, losses, and causes of action (whether in contract, tort
 * (including negligence) or otherwise) exceed the amount of $50 USD. You agree
 * to defend, indemnify and hold harmless AMD, its subsidiaries and affiliates
 * and their respective licensors, directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your
 * possession or use of the Software or violation of the terms and conditions of
 * this Agreement.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS: Notice to U.S. Government End Users. The
 * Software and related documentation are "commercial items", as that term is
 * defined at 48 C.F.R. Section 2.101, consisting of "commercial computer
 * software" and "commercial computer software documentation", as such terms are
 * used in 48 C.F.R. Section 12.212 and 48 C.F.R. Section 227.7202,
 * respectively. Consistent with 48 C.F.R. Section 12.212 or 48 C.F.R. Sections
 * 227.7202-1 through 227.7202-4, as applicable, the commercial computer
 * software and commercial computer software documentation are being licensed to
 * U.S. Government end users: (a) only as commercial items, and (b) with only
 * those rights as are granted to all other end users pursuant to the terms and
 * conditions set forth in this Agreement. Unpublished rights are reserved under
 * the copyright laws of the United States.
 *
 * EXPORT RESTRICTIONS:  You shall adhere to all applicable U.S. import/export
 * laws and regulations, as well as the import/export control laws and
 * regulations of other countries as applicable. You further agree You will not
 * export, re-export, or transfer, directly or indirectly, any product,
 * technical data, software or source code received from AMD under this license,
 * or the direct product of such technical data or software to any country for
 * which the United States or any other applicable government requires an export
 * license or other governmental approval without first obtaining such licenses
 * or approvals, or in violation of any applicable laws or regulations of the
 * United States or the country where the technical data or software was
 * obtained. You acknowledges the technical data and software received will not,
 * in the absence of authorization from U.S. or local law and regulations as
 * applicable, be used by or exported, re-exported or transferred to: (i) any
 * sanctioned or embargoed country, or to nationals or residents of such
 * countries; (ii) any restricted end-user as identified on any applicable
 * government end-user list; or (iii) any party where the end-use involves
 * nuclear, chemical/biological weapons, rocket systems, or unmanned air
 * vehicles.  For the most current Country Group listings, or for additional
 * information about the EAR or Your obligations under those regulations, please
 * refer to the website of the U.S. Bureau of Industry and Security at
 * http://www.bis.doc.gov/.
 *******************************************************************************
 */
#include <AMD.h>
#include <Filecode.h>
#include <PiPei.h>
#include <GnbDxio.h>
#include <Library/NbioSmuV10Lib.h>
#include <Library/PcdLib.h>
#include <Library/PciLib.h>
#include <Library/IdsLib.h>

#define FILECODE  NBIO_EARLYPHASE_AMDNBIOEARLYPHASERVPEI_AMDNBIOEARLYPHASERVPEI_FILECODE

/*----------------------------------------------------------------------------------------
 *                         E X T E R N   D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                    P P I   N O T I F Y   D E S C R I P T O R S
 *----------------------------------------------------------------------------------------
 */




/*----------------------------------------------------------------------------------------*/
/**
 * AmdNbioEarlyPhase driver entry point for RV
 *
 *
 *
 * @param[in]  FileHandle  Standard configuration header
 * @param[in]  PeiServices Pointer to EFI_PEI_SERVICES pointer
 * @retval     EFI_STATUS
 */

EFI_STATUS
EFIAPI
AmdNbioEarlyPhaseRVPeiEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  PCI_ADDR      NbioPciAddress;
  UINT32        SmuArg[6];
  UINT32   Value;
  UINTN    PciAddr;

  AGESA_TESTPOINT (TpEarlyEntry, NULL);
  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdNbioEarlyPhaseRVPeiEntry Entry\n");


  NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
  NbioPciAddress.AddressValue = 0;
  if (NbioSmuServiceRequestV10 (NbioPciAddress, 0x51, SmuArg,0)) {  // SMC_MSG_GetOpnSpareFuse
    IDS_HDT_CONSOLE (NB_MISC, "  SmuArg 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n", SmuArg[0], SmuArg[1], SmuArg[2], SmuArg[3], SmuArg[4], SmuArg[5]);
  }

  PcdSet32 (PcdGetRVFamilyOPN, SmuArg[0]);

  SmuArg[0] = SmuArg[0] >> 30;
  IDS_HDT_CONSOLE (NB_MISC, "SmuArg 0x%x\n", SmuArg[0]);
  if (SmuArg[0] == 2 || SmuArg[0] == 3) {
    PcdSetBool (PcdPCIeExactMatchEnable, TRUE);
    IDS_HDT_CONSOLE (MAIN_FLOW, "Enable Exact Match\n");
  }

  PciAddr = MAKE_SBDFO (0, 0, 0, 0, 0xB8);
  PciWrite32 (PciAddr, 0x5D254); // Read FUSE_DATA_149

  PciAddr = MAKE_SBDFO (0, 0, 0, 0, 0xBC);
  Value = PciRead32 (PciAddr);

  Value = (Value >> 17) & 1; // Only need bit17
  PcdSet8S (PcdXgbeDisable, (UINT8) Value);
  IDS_HDT_CONSOLE (MAIN_FLOW, "PcdXgbeDisable = 0x%x\n", Value);

  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdNbioEarlyPhaseRVPeiEntry Exit\n");
  AGESA_TESTPOINT (TpEarlyExit, NULL);
  return EFI_SUCCESS;
}

