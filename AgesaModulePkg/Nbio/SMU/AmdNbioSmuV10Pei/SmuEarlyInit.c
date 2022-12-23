/* $NoKeywords:$ */
/**
 * @file
 *
 * SMU Early Initialization Function
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  AmdNbioSmuV10Pei
 * @e \$Revision: 312065 $   @e \$Date: 2015-01-30 04:23:05 -0600 (Fri, 30 Jan 2015) $
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
#include <PiPei.h>
#include <Filecode.h>
#include <GnbDxio.h>
#include <GnbRegistersRV.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/PcdLib.h>
#include <Library/HobLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/NbioHandleLib.h>
#include <Library/GnbRegisterAccZpLib.h>
#include <Library/PcieConfigLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/NbioSmuV10Lib.h>
//#include <PcieComplexDataZP.h>
#include <Ppi/NbioSmuServicesPpi.h>
#include <Ppi/NbioBaseServicesZPPpi.h>
#include <Ppi/AmdCoreTopologyServicesPpi.h>
#include <Ppi/NbioPcieServicesPpi.h>
#include <Guid/GnbNbioBaseZPInfoHob.h>
//<Embedded_Override_Strat>
#include <Library/SmnAccessLib.h>
//#defines for i-temp SOC Model name
#define ITEMP_OPN_V1404I "V1404I"
//<Embedded_Override_End>
#define FILECODE        NBIO_SMU_AMDNBIOSMUV10PEI_SMUEARLYINIT_FILECODE


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


//<Embedded_Override_Start>	
/* -----------------------------------------------------------------------------*/
/**
 *
 *  GetOPNNameString
 *
 *  @param[in]  OPNString     OPNString Pointer
 *
 *  Description:
 *    Gets the OPN part String .
 *
 *  @retval VOID
 *
 */
VOID GetOPNNameString( CHAR8 *OPNString )
{
    UINT32              RegisterData;

    if(OPNString == NULL)
        return;
    
    SmnRegisterRead (0, SMUFUSEx000005A0_ADDRESS, &RegisterData);
    //OPN string is present in the offsets 5-11,12-18,19-25,26-31
    
    OPNString[0] = (RegisterData >> 5)&0x7F;
    OPNString[1] = (RegisterData >> 12)&0x7F;
    OPNString[2] = (RegisterData >> 19)&0x7F;
    OPNString[3] = (RegisterData >> 26)&0x7F;
    
    SmnRegisterRead (0, SMUFUSEx000005A4_ADDRESS, &RegisterData);
    //OPN Contunuity string is present in the offsets 1-7,8-15
    OPNString[4] = (RegisterData >> 1)&0x7F;
    OPNString[5] = (RegisterData >> 8)&0x7F;
    
    IDS_HDT_CONSOLE (MAIN_FLOW, "\nOPN Name String:%c%c%c%c%c%c\n", OPNString[0],OPNString[1],OPNString[2],OPNString[3],OPNString[4],OPNString[5]);

}
//<Embedded_Override_End>
/*----------------------------------------------------------------------------------------*/
/**
 * Smu Early Init
 *
 * This is the main flow of the early initialization of the SMU.
 *
 * @param[in]       Pcie           Pointer to global PCIe configuration
 */
EFI_STATUS
AmdNbioSmuEarlyInit (
  IN       PCIe_PLATFORM_CONFIG            *Pcie
  )
{
  EFI_STATUS                      Status;
  GNB_HANDLE                      *NbioHandle;
  //<Embedded_Override_Start>	
  CHAR8 OPNNameString[10] = {0};
  //<Embedded_Override_End>

  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdNbioSmuEarlyInit Entry\n");

  Status = EFI_SUCCESS;
  NbioHandle = NbioGetHandle (Pcie);
  while (NbioHandle != NULL) {
    // Repeat initialization for each NbioHandle of the platform
    // NbioSmuFirmwareTestV10 (NbioHandle);
    // TBD - Add SMU initialization functions here
//<Embedded_Override_Start>	
    GetOPNNameString(OPNNameString);
    if(AsciiStrCmp(OPNNameString,ITEMP_OPN_V1404I) == 0)
      PcdSet8 (Pcditemp,1);
//<Embedded_Override_End>

    NbioHandle = GnbGetNextHandle (NbioHandle);
  }
  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdNbioSmuEarlyInit Exit\n");
  return Status;
}

