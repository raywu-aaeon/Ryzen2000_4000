/**
 * @file
 *
 * GNB init tables
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-25 21:00:43 -0600 (Wed, 25 Feb 2015) $
 *
 */
/*
*****************************************************************************
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
*
*/
/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include  <GnbDxio.h>
#include  <Library/GnbCommonLib.h>
#include  <Library/NbioTable.h>
#include  <GnbRegistersRV.h>
#include  <Filecode.h>

#define FILECODE  NBIO_NBIOBASE_AMDNBIOBASERVPEI_NBIOTABLESRV_FILECODE

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
 *           T A B L E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

GNB_TABLE ROMDATA GnbEarlyInitTableRV [] = {
  // IOHC::NB_IOHC_DEBUG0[NB_IOHC_DEBUG_RW]=0x10 - Terminate p2p atomics
  GNB_ENTRY_RMW (
    NB_IOC_DEBUG_TYPE,
    NB_IOC_DEBUG_ADDRESS,
    NBMISC_0004_NB_IOC_DEBUG_RW_MASK,
    (0x10 << NBMISC_0004_NB_IOC_DEBUG_RW_OFFSET)
    ),
  // To enable peer-to-peer operation, set IOHC::IOHC_FEATURE_CNTL[P2P_mode]=1 and PCIE_VDM_CNTL2[VdmP2pMode]=1.
  GNB_ENTRY_RMW (
    IOC_FEATURE_CNTL_TYPE,
    IOC_FEATURE_CNTL_ADDRESS,
    NBMISC_0118_P2P_mode_MASK,
    (0x1 << NBMISC_0118_P2P_mode_OFFSET)
    ),
  GNB_ENTRY_RMW (
    PCIE_VDM_CNTL2_TYPE,
    PCIE_VDM_CNTL2_ADDRESS,
    NBMISC_0230_VdmP2pMode_MASK,
    (0x1 << NBMISC_0230_VdmP2pMode_OFFSET)
    ),
  //IOHC Initialization
  //IOHC::IOHC_SION_S0_CLIENT_REQ_BURSTTARGET_LOWER_n[4:0] = 0808_0808h
  //IOHC::IOHC_SION_S0_CLIENT_REQ_BURSTTARGET_UPPER_n[4:0] = 0808_0808h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client0_Req_BurstTarget_Lower_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client0_Req_BurstTarget_Upper_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client1_Req_BurstTarget_Lower_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client1_Req_BurstTarget_Upper_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client2_Req_BurstTarget_Lower_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client2_Req_BurstTarget_Upper_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client3_Req_BurstTarget_Lower_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client3_Req_BurstTarget_Upper_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client4_Req_BurstTarget_Lower_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client4_Req_BurstTarget_Upper_ADDRESS,
    0x08080808
    ),
  //IOHC::IOHC_SION_S0_CLIENT_REQ_TIMESLOT_LOWER_n[1:0] = 2121_2121h
  //IOHC::IOHC_SION_S0_CLIENT_REQ_TIMESLOT_UPPER_n[1:0] = 2121_2121h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client0_Req_TimeSlot_Lower_ADDRESS,
    0x21212121
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client0_Req_TimeSlot_Upper_ADDRESS,
    0x21212121
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client1_Req_TimeSlot_Lower_ADDRESS,
    0x21212121
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client1_Req_TimeSlot_Upper_ADDRESS,
    0x21212121
    ),
  //IOHC::IOHC_SION_S0_CLIENT_REQ_TIMESLOT_LOWER_n[2] = 8421_8421h
  //IOHC::IOHC_SION_S0_CLIENT_REQ_TIMESLOT_UPPER_n[2] = 8421_8421h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client2_Req_TimeSlot_Lower_ADDRESS,
    0x84218421
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client2_Req_TimeSlot_Upper_ADDRESS,
    0x84218421
    ),
  //IOHC::IOHC_SION_S0_CLIENT_REQ_TIMESLOT_LOWER_n[3] = 8521_8521h
  //IOHC::IOHC_SION_S0_CLIENT_REQ_TIMESLOT_UPPER_n[3] = 8521_8521h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client3_Req_TimeSlot_Lower_ADDRESS,
    0x85218521
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client3_Req_TimeSlot_Upper_ADDRESS,
    0x85218521
    ),
  //IOHC::IOHC_SION_S0_CLIENT_REQ_TIMESLOT_LOWER_n[4] = 0h
  //IOHC::IOHC_SION_S0_CLIENT_REQ_TIMESLOT_UPPER_n[4] = 0h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client4_Req_TimeSlot_Lower_ADDRESS,
    0x00000000
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client4_Req_TimeSlot_Upper_ADDRESS,
    0x00000000
    ),
  //IOHC::IOHC_SION_S1_CLIENT_REQ_BURSTTARGET_LOWER_n[4:0] = 0808_0808h
  //IOHC::IOHC_SION_S1_CLIENT_REQ_BURSTTARGET_UPPER_n[4:0] = 0808_0808h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client0_Req_BurstTarget_Lower_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client0_Req_BurstTarget_Upper_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client1_Req_BurstTarget_Lower_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client1_Req_BurstTarget_Upper_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client2_Req_BurstTarget_Lower_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client2_Req_BurstTarget_Upper_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client3_Req_BurstTarget_Lower_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client3_Req_BurstTarget_Upper_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client4_Req_BurstTarget_Lower_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client4_Req_BurstTarget_Upper_ADDRESS,
    0x08080808
    ),
  //IOHC::IOHC_SION_S1_CLIENT_REQ_TIMESLOT_LOWER_n[0] = 3333_3030h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client0_Req_TimeSlot_Lower_ADDRESS,
    0x33333030
    ),
  //IOHC::IOHC_SION_S1_CLIENT_REQ_TIMESLOT_UPPER_n[0] = 3333_3030h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client0_Req_TimeSlot_Upper_ADDRESS,
    0x33333030
    ),
  //IOHC::IOHC_SION_S1_CLIENT_REQ_TIMESLOT_LOWER_n[4:1] = 0h
  //IOHC::IOHC_SION_S1_CLIENT_REQ_TIMESLOT_UPPER_n[4:1] = 0h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client1_Req_TimeSlot_Lower_ADDRESS,
    0x00000000
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client1_Req_TimeSlot_Upper_ADDRESS,
    0x00000000
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client2_Req_TimeSlot_Lower_ADDRESS,
    0x00000000
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client2_Req_TimeSlot_Upper_ADDRESS,
    0x00000000
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client3_Req_TimeSlot_Lower_ADDRESS,
    0x00000000
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client3_Req_TimeSlot_Upper_ADDRESS,
    0x00000000
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client4_Req_TimeSlot_Lower_ADDRESS,
    0x00000000
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client4_Req_TimeSlot_Upper_ADDRESS,
    0x00000000
    ),
  //IOHC::IOHC_SION_S0_CLIENT_RDRSP_BURSTTARGET_LOWER_n[4:0] = 0202_0202h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client0_RdRsp_BurstTarget_Lower_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client1_RdRsp_BurstTarget_Lower_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client2_RdRsp_BurstTarget_Lower_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client3_RdRsp_BurstTarget_Lower_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client4_RdRsp_BurstTarget_Lower_ADDRESS,
    0x02020202
    ),
  //IOHC::IOHC_SION_S0_CLIENT_RDRSP_BURSTTARGET_UPPER_n[4:0] = 0202_0202h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client0_RdRsp_BurstTarget_Upper_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client1_RdRsp_BurstTarget_Upper_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client2_RdRsp_BurstTarget_Upper_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client3_RdRsp_BurstTarget_Upper_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S0_Client4_RdRsp_BurstTarget_Upper_ADDRESS,
    0x02020202
    ),
  //IOHC::IOHC_SION_S1_CLIENT_RDRSP_BURSTTARGET_LOWER_n[4:0] = 0202_0202h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client0_RdRsp_BurstTarget_Lower_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client1_RdRsp_BurstTarget_Lower_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client2_RdRsp_BurstTarget_Lower_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client3_RdRsp_BurstTarget_Lower_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client4_RdRsp_BurstTarget_Lower_ADDRESS,
    0x02020202
    ),
  //IOHC::IOHC_SION_S1_CLIENT_RDRSP_BURSTTARGET_UPPER_n[4:0] = 0202_0202h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client0_RdRsp_BurstTarget_Upper_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client1_RdRsp_BurstTarget_Upper_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client2_RdRsp_BurstTarget_Upper_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client3_RdRsp_BurstTarget_Upper_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOHC_SION_S1_Client4_RdRsp_BurstTarget_Upper_ADDRESS,
    0x02020202
    ),
  //IOAGR::IOAGR_SION_S0_Client_Req_BurstTarget_Lower_n[3:0] = 0808_0808h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_Req_BurstTarget_Lower_n0_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_Req_BurstTarget_Lower_n1_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_Req_BurstTarget_Lower_n2_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_Req_BurstTarget_Lower_n3_ADDRESS,
    0x08080808
    ),
  //IOAGR::IOAGR_SION_S0_Client_Req_BurstTarget_Upper_n[3:0] = 0808_0808h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_Req_BurstTarget_Upper_n0_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_Req_BurstTarget_Upper_n1_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_Req_BurstTarget_Upper_n2_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_Req_BurstTarget_Upper_n3_ADDRESS,
    0x08080808
    ),
  //IOAGR::IOAGR_SION_S0_Client_Req_TimeSlot_Lower_n[2:0] = 2121_2121h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_Req_TimeSlot_Lower_n0_ADDRESS,
    0x21212121
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_Req_TimeSlot_Lower_n1_ADDRESS,
    0x21212121
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_Req_TimeSlot_Lower_n2_ADDRESS,
    0x21212121
    ),
  //IOAGR::IOAGR_SION_S0_Client_Req_TimeSlot_Upper_n[2:0] = 2121_2121h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_Req_TimeSlot_Upper_n0_ADDRESS,
    0x21212121
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_Req_TimeSlot_Upper_n1_ADDRESS,
    0x21212121
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_Req_TimeSlot_Upper_n2_ADDRESS,
    0x21212121
    ),
  //IOAGR::IOAGR_SION_S0_CLIENT_REQ_TIMESLOT_LOWER_n[3] = 8421_8421h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_Req_TimeSlot_Lower_n3_ADDRESS,
    0x84218421
    ),
  //IOAGR::IOAGR_SION_S0_CLIENT_REQ_TIMESLOT_UPPER_n[3] = 8421_8421h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_Req_TimeSlot_Upper_n3_ADDRESS,
    0x84218421
    ),
  //IOAGR::IOAGR_SION_S1_CLIENT_REQ_BURSTTARGET_LOWER_n[3:0] = 0808_0808h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_Req_BurstTarget_Lower_n0_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_Req_BurstTarget_Lower_n1_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_Req_BurstTarget_Lower_n2_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_Req_BurstTarget_Lower_n3_ADDRESS,
    0x08080808
    ),
  //IOAGR::IOAGR_SION_S1_CLIENT_REQ_BURSTTARGET_UPPER_n[3:0] = 0808_0808h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_Req_BurstTarget_Upper_n0_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_Req_BurstTarget_Upper_n1_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_Req_BurstTarget_Upper_n2_ADDRESS,
    0x08080808
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_Req_BurstTarget_Upper_n3_ADDRESS,
    0x08080808
    ),
  //IOAGR::IOAGR_SION_S1_CLIENT_REQ_TIMESLOT_LOWER_n[3:0] = 0h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_Req_TimeSlot_Lower_n0_ADDRESS,
    0x00000000
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_Req_TimeSlot_Lower_n1_ADDRESS,
    0x00000000
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_Req_TimeSlot_Lower_n2_ADDRESS,
    0x00000000
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_Req_TimeSlot_Lower_n3_ADDRESS,
    0x00000000
    ),
  //IOAGR::IOAGR_SION_S1_CLIENT_REQ_TIMESLOT_UPPER_n[3:0] = 0h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_Req_TimeSlot_Upper_n0_ADDRESS,
    0x00000000
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_Req_TimeSlot_Upper_n1_ADDRESS,
    0x00000000
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_Req_TimeSlot_Upper_n2_ADDRESS,
    0x00000000
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_Req_TimeSlot_Upper_n3_ADDRESS,
    0x00000000
    ),
  //IOAGR::IOAGR_SION_S0_CLIENT_RDRSP_BURSTTARGET_LOWER_n[3:0] = 0202_0202h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_RdRsp_BurstTarget_Lower_n0_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_RdRsp_BurstTarget_Lower_n1_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_RdRsp_BurstTarget_Lower_n2_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_RdRsp_BurstTarget_Lower_n3_ADDRESS,
    0x02020202
    ),
  //IOAGR::IOAGR_SION_S0_CLIENT_RDRSP_BURSTTARGET_UPPER_n[3:0] = 0202_0202h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_RdRsp_BurstTarget_Upper_n0_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_RdRsp_BurstTarget_Upper_n1_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_RdRsp_BurstTarget_Upper_n2_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S0_Client_RdRsp_BurstTarget_Upper_n3_ADDRESS,
    0x02020202
    ),
  //IOAGR::IOAGR_SION_S1_CLIENT_RDRSP_BURSTTARGET_LOWER_n[3:0] = 0202_0202h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_RdRsp_BurstTarget_Lower_n0_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_RdRsp_BurstTarget_Lower_n1_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_RdRsp_BurstTarget_Lower_n2_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_RdRsp_BurstTarget_Lower_n3_ADDRESS,
    0x02020202
    ),
  //IOAGR::IOAGR_SION_S1_CLIENT_RDRSP_BURSTTARGET_UPPER_n[3:0] = 0202_0202h
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_RdRsp_BurstTarget_Upper_n0_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_RdRsp_BurstTarget_Upper_n1_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_RdRsp_BurstTarget_Upper_n2_ADDRESS,
    0x02020202
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    IOAGR_SION_S1_Client_RdRsp_BurstTarget_Upper_n3_ADDRESS,
    0x02020202
    ),
  //IOHC::IOHC_QOS_CONTROL[VC0QoSPriority] = 0h
  //IOHC::IOHC_QOS_CONTROL[VC1QoSPriority] = 0h
  //IOHC::IOHC_QOS_CONTROL[VC2QoSPriority] = 0h
  //IOHC::IOHC_QOS_CONTROL[VC3QoSPriority] = 0h
  //IOHC::IOHC_QOS_CONTROL[VC4QoSPriority] = 0h
  //IOHC::IOHC_QOS_CONTROL[VC5QoSPriority] = 0h
  //IOHC::IOHC_QOS_CONTROL[VC6QoSPriority] = 0h
  //IOHC::IOHC_QOS_CONTROL[VC7QoSPriority] = 0h
  GNB_ENTRY_RMW (
    TYPE_SMN,
    SMN_IOHC_QOS_CONTROL_ADDRESS,
    IOHC_QOS_CONTROL_VC0QoSPriority_MASK |
    IOHC_QOS_CONTROL_VC1QoSPriority_MASK |
    IOHC_QOS_CONTROL_VC2QoSPriority_MASK |
    IOHC_QOS_CONTROL_VC3QoSPriority_MASK |
    IOHC_QOS_CONTROL_VC4QoSPriority_MASK |
    IOHC_QOS_CONTROL_VC5QoSPriority_MASK |
    IOHC_QOS_CONTROL_VC6QoSPriority_MASK |
    IOHC_QOS_CONTROL_VC7QoSPriority_MASK,
    (0x0 << IOHC_QOS_CONTROL_VC0QoSPriority_OFFSET) |
    (0x0 << IOHC_QOS_CONTROL_VC1QoSPriority_OFFSET) |
    (0x0 << IOHC_QOS_CONTROL_VC2QoSPriority_OFFSET) |
    (0x0 << IOHC_QOS_CONTROL_VC3QoSPriority_OFFSET) |
    (0x0 << IOHC_QOS_CONTROL_VC4QoSPriority_OFFSET) |
    (0x0 << IOHC_QOS_CONTROL_VC5QoSPriority_OFFSET) |
    (0x0 << IOHC_QOS_CONTROL_VC6QoSPriority_OFFSET) |
    (0x0 << IOHC_QOS_CONTROL_VC7QoSPriority_OFFSET)
    ),
  //IOHC::USB_QoS_CNTL[UnitID0] = 2Fh
  //IOHC::USB_QoS_CNTL[UnitID0QoSPriority] = 0h
  //IOHC::USB_QoS_CNTL[UnitID0Enable] = 1h
  //IOHC::USB_QoS_CNTL[UnitID1] = 30h
  //IOHC::USB_QoS_CNTL[UnitID1QoSPriority] = 0h
  //IOHC::USB_QoS_CNTL[UnitID1Enable] = 1h
  GNB_ENTRY_RMW (
    TYPE_SMN,
    SMN_USB_QoS_CNTL_ADDRESS,
    USB_QoS_CNTL_UnitID0_MASK |
    USB_QoS_CNTL_UnitID0QoSPriority_MASK |
    USB_QoS_CNTL_UnitID0Enable_MASK |
    USB_QoS_CNTL_UnitID1_MASK |
    USB_QoS_CNTL_UnitID1QoSPriority_MASK |
    USB_QoS_CNTL_UnitID1Enable_MASK,
    (0x2F << USB_QoS_CNTL_UnitID0_OFFSET) |
    (0x0 << USB_QoS_CNTL_UnitID0QoSPriority_OFFSET) |
    (0x1 << USB_QoS_CNTL_UnitID0Enable_OFFSET) |
    (0x30 << USB_QoS_CNTL_UnitID1_OFFSET) |
    (0x0 << USB_QoS_CNTL_UnitID1QoSPriority_OFFSET) |
    (0x1 << USB_QoS_CNTL_UnitID1Enable_OFFSET)
    ),

  //IOAPIC Initialization
  GNB_ENTRY_RMW (
    IOAPIC_BR0_INTERRUPT_ROUTING_TYPE,
    IOAPIC_BR0_INTERRUPT_ROUTING_ADDRESS,
    NBIOAPICCFG_040_Br0_ext_Intr_grp_MASK |
    NBIOAPICCFG_040_Br0_ext_Intr_swz_MASK |
    NBIOAPICCFG_040_Br0_int_Intr_map_MASK,
    (0x0 << NBIOAPICCFG_040_Br0_ext_Intr_grp_OFFSET) |
    (0x0 << NBIOAPICCFG_040_Br0_ext_Intr_swz_OFFSET) |
    (0x10 << NBIOAPICCFG_040_Br0_int_Intr_map_OFFSET)
    ),
  GNB_ENTRY_RMW (
    IOAPIC_BR1_INTERRUPT_ROUTING_TYPE,
    IOAPIC_BR1_INTERRUPT_ROUTING_ADDRESS,
    NBIOAPICCFG_044_Br1_ext_Intr_grp_MASK |
    NBIOAPICCFG_044_Br1_ext_Intr_swz_MASK |
    NBIOAPICCFG_044_Br1_int_Intr_map_MASK,
    (0x1 << NBIOAPICCFG_044_Br1_ext_Intr_grp_OFFSET) |
    (0x0 << NBIOAPICCFG_044_Br1_ext_Intr_swz_OFFSET) |
    (0x11 << NBIOAPICCFG_044_Br1_int_Intr_map_OFFSET)
    ),
  GNB_ENTRY_RMW (
    IOAPIC_BR2_INTERRUPT_ROUTING_TYPE,
    IOAPIC_BR2_INTERRUPT_ROUTING_ADDRESS,
    NBIOAPICCFG_048_Br2_ext_Intr_grp_MASK |
    NBIOAPICCFG_048_Br2_ext_Intr_swz_MASK |
    NBIOAPICCFG_048_Br2_int_Intr_map_MASK,
    (0x2 << NBIOAPICCFG_048_Br2_ext_Intr_grp_OFFSET) |
    (0x0 << NBIOAPICCFG_048_Br2_ext_Intr_swz_OFFSET) |
    (0x12 << NBIOAPICCFG_048_Br2_int_Intr_map_OFFSET)
    ),
  GNB_ENTRY_RMW (
    IOAPIC_BR3_INTERRUPT_ROUTING_TYPE,
    IOAPIC_BR3_INTERRUPT_ROUTING_ADDRESS,
    NBIOAPICCFG_04C_Br3_ext_Intr_grp_MASK |
    NBIOAPICCFG_04C_Br3_ext_Intr_swz_MASK |
    NBIOAPICCFG_04C_Br3_int_Intr_map_MASK,
    (0x3 << NBIOAPICCFG_04C_Br3_ext_Intr_grp_OFFSET) |
    (0x0 << NBIOAPICCFG_04C_Br3_ext_Intr_swz_OFFSET) |
    (0x13 << NBIOAPICCFG_04C_Br3_int_Intr_map_OFFSET)
    ),
  GNB_ENTRY_RMW (
    IOAPIC_BR4_INTERRUPT_ROUTING_TYPE,
    IOAPIC_BR4_INTERRUPT_ROUTING_ADDRESS,
    NBIOAPICCFG_050_Br4_ext_Intr_grp_MASK |
    NBIOAPICCFG_050_Br4_ext_Intr_swz_MASK |
    NBIOAPICCFG_050_Br4_int_Intr_map_MASK,
    (0x4 << NBIOAPICCFG_050_Br4_ext_Intr_grp_OFFSET) |
    (0x0 << NBIOAPICCFG_050_Br4_ext_Intr_swz_OFFSET) |
    (0x10 << NBIOAPICCFG_050_Br4_int_Intr_map_OFFSET)
    ),
  GNB_ENTRY_RMW (
    IOAPIC_BR5_INTERRUPT_ROUTING_TYPE,
    IOAPIC_BR5_INTERRUPT_ROUTING_ADDRESS,
    NBIOAPICCFG_054_Br5_ext_Intr_grp_MASK |
    NBIOAPICCFG_054_Br5_ext_Intr_swz_MASK |
    NBIOAPICCFG_054_Br5_int_Intr_map_MASK,
    (0x5 << NBIOAPICCFG_054_Br5_ext_Intr_grp_OFFSET) |
    (0x0 << NBIOAPICCFG_054_Br5_ext_Intr_swz_OFFSET) |
    (0x11 << NBIOAPICCFG_054_Br5_int_Intr_map_OFFSET)
    ),
  GNB_ENTRY_RMW (
    IOAPIC_BR6_INTERRUPT_ROUTING_TYPE,
    IOAPIC_BR6_INTERRUPT_ROUTING_ADDRESS,
    NBIOAPICCFG_058_Br6_ext_Intr_grp_MASK |
    NBIOAPICCFG_058_Br6_ext_Intr_swz_MASK |
    NBIOAPICCFG_058_Br6_int_Intr_map_MASK,
    (0x6 << NBIOAPICCFG_058_Br6_ext_Intr_grp_OFFSET) |
    (0x0 << NBIOAPICCFG_058_Br6_ext_Intr_swz_OFFSET) |
    (0x12 << NBIOAPICCFG_058_Br6_int_Intr_map_OFFSET)
    ),
  GNB_ENTRY_RMW (
    IOAPIC_BR7_INTERRUPT_ROUTING_TYPE,
    IOAPIC_BR7_INTERRUPT_ROUTING_ADDRESS,
    NBIOAPICCFG_05C_Br7_ext_Intr_grp_MASK |
    NBIOAPICCFG_05C_Br7_ext_Intr_swz_MASK |
    NBIOAPICCFG_05C_Br7_int_Intr_map_MASK,
    (0x7 << NBIOAPICCFG_05C_Br7_ext_Intr_grp_OFFSET) |
    (0x0 << NBIOAPICCFG_05C_Br7_ext_Intr_swz_OFFSET) |
    (0x13 << NBIOAPICCFG_05C_Br7_int_Intr_map_OFFSET)
    ),
  GNB_ENTRY_RMW (
    IOAPIC_BR8_INTERRUPT_ROUTING_TYPE,
    IOAPIC_BR8_INTERRUPT_ROUTING_ADDRESS,
    NBIOAPICCFG_060_Br8_ext_Intr_grp_MASK |
    NBIOAPICCFG_060_Br8_ext_Intr_swz_MASK |
    NBIOAPICCFG_060_Br8_int_Intr_map_MASK,
    (0x7 << NBIOAPICCFG_060_Br8_ext_Intr_grp_OFFSET) |
    (0x2 << NBIOAPICCFG_060_Br8_ext_Intr_swz_OFFSET) |
    (0xC << NBIOAPICCFG_060_Br8_int_Intr_map_OFFSET)
    ),
  GNB_ENTRY_WR (
    NBIFMISC0_INTR_LINE_POLARITY_TYPE,
    NBIFMISC0_INTR_LINE_POLARITY_ADDRESS,
    0x00000000
    ),
  GNB_ENTRY_WR (
    NBIFMISC0_INTR_LINE_ENABLE_TYPE,
    NBIFMISC0_INTR_LINE_ENABLE_ADDRESS,
    0x000001FF
    ),
  //GMI_WRR_WEIGHT
  GNB_ENTRY_RMW (
    TYPE_SMN,
    SMN_0x1013A108,
    SMN_GMI_REQ_REALTIME_WEIGHT_MASK |
    SMN_GMI_REQ_NORM_P_WEIGHT_MASK |
    SMN_GMI_REQ_NORM_NP_WEIGHT_MASK,
    (0x8 << SMN_GMI_REQ_REALTIME_WEIGHT_OFFSET) |
    (0x8 << SMN_GMI_REQ_NORM_P_WEIGHT_OFFSET) |
    (0x8 << SMN_GMI_REQ_NORM_NP_WEIGHT_OFFSET)
    ),
  // To enable dynamic clock gating:. IOHC::IOHC_GLUE_CG_LCLK_CTRL_0[SOFT_OVERRIDE_CLK9~0]=0h
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IOHC_Clock_GATING,
    IOHC_GLUE_CG_LCLK_CTRL_0_TYPE,
    IOHC_GLUE_CG_LCLK_CTRL_0_ADDRESS,
    NBMISC_0088_SOFT_OVERRIDE_CLK9_MASK |
    NBMISC_0088_SOFT_OVERRIDE_CLK8_MASK |
    NBMISC_0088_SOFT_OVERRIDE_CLK7_MASK |
    NBMISC_0088_SOFT_OVERRIDE_CLK6_MASK |
    NBMISC_0088_SOFT_OVERRIDE_CLK5_MASK |
    NBMISC_0088_SOFT_OVERRIDE_CLK4_MASK |
    NBMISC_0088_SOFT_OVERRIDE_CLK3_MASK |
    NBMISC_0088_SOFT_OVERRIDE_CLK2_MASK |
    NBMISC_0088_SOFT_OVERRIDE_CLK1_MASK |
    NBMISC_0088_SOFT_OVERRIDE_CLK0_MASK,
    (0x0 << NBMISC_0088_SOFT_OVERRIDE_CLK9_OFFSET) |
    (0x0 << NBMISC_0088_SOFT_OVERRIDE_CLK8_OFFSET) |
    (0x0 << NBMISC_0088_SOFT_OVERRIDE_CLK7_OFFSET) |
    (0x0 << NBMISC_0088_SOFT_OVERRIDE_CLK6_OFFSET) |
    (0x0 << NBMISC_0088_SOFT_OVERRIDE_CLK5_OFFSET) |
    (0x0 << NBMISC_0088_SOFT_OVERRIDE_CLK4_OFFSET) |
    (0x0 << NBMISC_0088_SOFT_OVERRIDE_CLK3_OFFSET) |
    (0x0 << NBMISC_0088_SOFT_OVERRIDE_CLK2_OFFSET) |
    (0x0 << NBMISC_0088_SOFT_OVERRIDE_CLK1_OFFSET) |
    (0x0 << NBMISC_0088_SOFT_OVERRIDE_CLK0_OFFSET)
    ),
  // To enable dynamic clock gating:. IOHC::IOHC_GLUE_CG_LCLK_CTRL_1[SOFT_OVERRIDE_CLK9~0]=0h
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IOHC_Clock_GATING,
    IOHC_GLUE_CG_LCLK_CTRL_1_TYPE,
    IOHC_GLUE_CG_LCLK_CTRL_1_ADDRESS,
    NBMISC_008C_SOFT_OVERRIDE_CLK9_MASK |
    NBMISC_008C_SOFT_OVERRIDE_CLK8_MASK |
    NBMISC_008C_SOFT_OVERRIDE_CLK7_MASK |
    NBMISC_008C_SOFT_OVERRIDE_CLK6_MASK |
    NBMISC_008C_SOFT_OVERRIDE_CLK5_MASK |
    NBMISC_008C_SOFT_OVERRIDE_CLK4_MASK |
    NBMISC_008C_SOFT_OVERRIDE_CLK3_MASK |
    NBMISC_008C_SOFT_OVERRIDE_CLK2_MASK |
    NBMISC_008C_SOFT_OVERRIDE_CLK1_MASK |
    NBMISC_008C_SOFT_OVERRIDE_CLK0_MASK,
    (0x0 << NBMISC_008C_SOFT_OVERRIDE_CLK9_OFFSET) |
    (0x0 << NBMISC_008C_SOFT_OVERRIDE_CLK8_OFFSET) |
    (0x0 << NBMISC_008C_SOFT_OVERRIDE_CLK7_OFFSET) |
    (0x1 << NBMISC_008C_SOFT_OVERRIDE_CLK6_OFFSET) |
    (0x0 << NBMISC_008C_SOFT_OVERRIDE_CLK5_OFFSET) |
    (0x0 << NBMISC_008C_SOFT_OVERRIDE_CLK4_OFFSET) |
    (0x0 << NBMISC_008C_SOFT_OVERRIDE_CLK3_OFFSET) |
    (0x0 << NBMISC_008C_SOFT_OVERRIDE_CLK2_OFFSET) |
    (0x0 << NBMISC_008C_SOFT_OVERRIDE_CLK1_OFFSET) |
    (0x0 << NBMISC_008C_SOFT_OVERRIDE_CLK0_OFFSET)
    ),
  // To enable dynamic clock gating:. IOAGR::IOAGR_GLUE_CG_LCLK_CTRL_0[[SOFT_OVERRIDE_CLK9~0]=0h
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IOHC_Clock_GATING,
    IOAGR_GLUE_CG_LCLK_CTRL_0_TYPE,
    IOAGR_GLUE_CG_LCLK_CTRL_0_ADDRESS,
    IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK9_MASK |
    IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK8_MASK |
    IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK7_MASK |
    IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK6_MASK |
    IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK5_MASK |
    IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK4_MASK |
    IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK3_MASK |
    IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK2_MASK |
    IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK1_MASK |
    IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK0_MASK,
    (0x0 << IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK9_OFFSET) |
    (0x0 << IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK8_OFFSET) |
    (0x0 << IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK7_OFFSET) |
    (0x0 << IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK6_OFFSET) |
    (0x0 << IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK5_OFFSET) |
    (0x0 << IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK4_OFFSET) |
    (0x0 << IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK3_OFFSET) |
    (0x0 << IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK2_OFFSET) |
    (0x0 << IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK1_OFFSET) |
    (0x0 << IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK0_OFFSET)
    ),
  // To enable dynamic clock gating:. IOAGR::IOAGR_GLUE_CG_LCLK_CTRL_1[[SOFT_OVERRIDE_CLK2~0]=0h
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IOHC_Clock_GATING,
    IOAGR_GLUE_CG_LCLK_CTRL_1_TYPE,
    IOAGR_GLUE_CG_LCLK_CTRL_1_ADDRESS,
    IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK2_MASK |
    IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK1_MASK |
    IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK0_MASK,
    (0x0 << IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK2_OFFSET) |
    (0x0 << IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK1_OFFSET) |
    (0x0 << IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK0_OFFSET)
    ),
  // To enable dynamic clock gating:. IOAGR::IOAGR_GLUE_CG_LCLK_CTRL_1[[SOFT_OVERRIDE_CLK2~0]=0h
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IOHC_Clock_GATING,
    TYPE_SMN,
    IOAPIC_GLUE_CG_LCLK_CTRL_0_ADDRESS,
    IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK1_MASK |
    IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK0_MASK,
    (0x0 << IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK1_OFFSET) |
    (0x0 << IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK0_OFFSET)
    ),
  // To Enable/Disable NBIO Poison Consumption
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_POISON_ACTION_CONTROL,
    POISON_ACTION_CONTROL_TYPE,
    POISON_ACTION_CONTROL_ADDRESS,
    NBRASCFG_0400_IntPoisonAPMLErrEn_MASK |
    NBRASCFG_0400_IntPoisonLinkDisEn_MASK |
    NBRASCFG_0400_IntPoisonSyncFloodEn_MASK |
    NBRASCFG_0400_EgressPoisonLSAPMLErrEn_MASK |
    NBRASCFG_0400_EgressPoisonLSIntrGenSel_MASK |
    NBRASCFG_0400_EgressPoisonLSSyncFloodEn_MASK |
    NBRASCFG_0400_EgressPoisonHSAPMLErrEn_MASK |
    NBRASCFG_0400_EgressPoisonHSIntrGenSel_MASK |
    NBRASCFG_0400_EgressPoisonHSSyncFloodEn_MASK,
    (0x1 << NBRASCFG_0400_IntPoisonAPMLErrEn_OFFSET) |
    (0x1 << NBRASCFG_0400_IntPoisonLinkDisEn_OFFSET) |
    (0x1 << NBRASCFG_0400_IntPoisonSyncFloodEn_OFFSET) |
    (0x0 << NBRASCFG_0400_EgressPoisonLSAPMLErrEn_OFFSET) |
    (0x0 << NBRASCFG_0400_EgressPoisonLSIntrGenSel_OFFSET) |
    (0x0 << NBRASCFG_0400_EgressPoisonLSSyncFloodEn_OFFSET) |
    (0x0 << NBRASCFG_0400_EgressPoisonHSAPMLErrEn_OFFSET) |
    (0x0 << NBRASCFG_0400_EgressPoisonHSIntrGenSel_OFFSET) |
    (0x0 << NBRASCFG_0400_EgressPoisonHSSyncFloodEn_OFFSET)
    ),
  // set SyncFlood_En/LinkDis_En
  GNB_ENTRY_RMW (
    ErrEvent_ACTION_CONTROL_TYPE,
    ErrEvent_ACTION_CONTROL_ADDRESS,
    ErrEvent_ACTION_CONTROL_LinkDis_En_MASK |
    ErrEvent_ACTION_CONTROL_SyncFlood_En_MASK,
    (0x1 << ErrEvent_ACTION_CONTROL_LinkDis_En_OFFSET) |
    (0x1 << ErrEvent_ACTION_CONTROL_SyncFlood_En_OFFSET)
    ),
  GNB_ENTRY_RMW (
    RCC_BIF_STRAP1_TYPE,
    RCC_BIF_STRAP1_ADDRESS,
    RCC_BIF_STRAP1_STRAP_TRUE_PM_STATUS_EN_MASK,
    (0x1 << RCC_BIF_STRAP1_STRAP_TRUE_PM_STATUS_EN_OFFSET)
    ),
  // :0x1013400c  GFX function use 0x1002 Vendor_ID
  GNB_ENTRY_RMW (
    TYPE_SMN,
    RCC_DEV0_EPF0_STRAP3_ADDRESS,
    BIT25,
    (0x0 << 25)
    ),
  // :0x1013420c  AZ function use 0x1002 Vendor_ID
  GNB_ENTRY_RMW (
    TYPE_SMN,
    RCC_DEV0_EPF1_STRAP3_ADDRESS,
    BIT25,
    (0x0 << 25)
    ),
  // RCC_STRAP:RCC_DEV0_EPF5_STRAP13 ACP-SubClass to 0x80
  GNB_ENTRY_RMW (
    TYPE_SMN,
    RCC_DEV0_EPF5_STRAP13_ADDRESS,
    0xFF00, //BIT8~BIT15
    (0x80 << 8)
    ),
  // Set NBIF multi-function enable
  GNB_ENTRY_RMW (
    SMN_0x101235CC_TYPE,
    SMN_0x101235CC_ADDRESS,
    SMN_0x101235CC_STRAP_MULTI_FUNC_EN_MASK,
    (0x1 << SMN_0x101235CC_STRAP_MULTI_FUNC_EN_OFFSET)
    ),
  GNB_ENTRY_RMW (
    SMN_0x101313e4_TYPE,
    SMN_0x101313e4_ADDRESS,
    SMN_0x101313e4_STRAP_MULTI_FUNC_EN_MASK,
    (0x1 << SMN_0x101313e4_STRAP_MULTI_FUNC_EN_OFFSET)
    ),
  //
  // SMN_0x1013100c_STRAP_ATOMIC_EN_DN_DEV0_MASKT
  //
  GNB_ENTRY_RMW (
    SMN_0x1013100c_TYPE,
    SMN_0x1013100c_ADDRESS,
    SMN_0x1013100c_STRAP_ATOMIC_EN_DN_DEV0_MASK,
    (0x1 << SMN_0x1013100c_STRAP_ATOMIC_EN_DN_DEV0_OFFSET)
    ),
  //
  // RCC_DEV0_PORT_STRAP5:STRAP_ATOMIC_64BIT_EN_DN_DEV0
  //
  GNB_ENTRY_RMW (
    SMN_0x10131014_TYPE,
    SMN_0x10131014_ADDRESS,
    SMN_0x10131014_STRAP_ATOMIC_64BIT_EN_DN_DEV0_MASK,
    (0x1 << SMN_0x10131014_STRAP_ATOMIC_64BIT_EN_DN_DEV0_OFFSET)
    ),
  //
  // RCC_DEV0_PORT_STRAP2:F0
  //
  GNB_ENTRY_RMW (
    RCC_BIF_STRAP2_TYPE,
    RCC_BIF_STRAP2_ADDRESS,
    RCC_BIF_STRAP2_MAX_PASID_WIDTH_DEV0_F0_MASK |
    RCC_BIF_STRAP2_ATS_EN_DEV0_F0_MASK |
    RCC_BIF_STRAP2_PAGE_REQ_EN_DEV0_F0_MASK |
    RCC_BIF_STRAP2_PASID_EN_DEV0_F0_MASK |
    RCC_BIF_STRAP2_PASID_EXE_PERMISSION_SUPPORTED_DEV0_F0_MASK |
    RCC_BIF_STRAP2_PASID_PRIV_MODE_SUPPORTED_DEV0_F0_MASK,
    (0x10 << RCC_BIF_STRAP2_MAX_PASID_WIDTH_DEV0_F0_OFFSET) |
    (0x1  << RCC_BIF_STRAP2_ATS_EN_DEV0_F0_OFFSET) |
    (0x1  << RCC_BIF_STRAP2_PAGE_REQ_EN_DEV0_F0_OFFSET) |
    (0x1  << RCC_BIF_STRAP2_PASID_EN_DEV0_F0_OFFSET) |
    (0x1  << RCC_BIF_STRAP2_PASID_EXE_PERMISSION_SUPPORTED_DEV0_F0_OFFSET) |
    (0x1  << RCC_BIF_STRAP2_PASID_PRIV_MODE_SUPPORTED_DEV0_F0_OFFSET)
    ),
  //
  GNB_ENTRY_RMW (
    RCC_DEV0_PORT_STRAP2_TYPE,
    RCC_DEV0_PORT_STRAP2_ADDRESS,
    STRAP_E2E_PREFIX_EN_DEV0_MASK |
    STRAP_EXTENDED_FMT_SUPPORTED_DEV0_MASK,
    (0x1 << STRAP_E2E_PREFIX_EN_DEV0_OFFSET) |
    (0x1 << STRAP_EXTENDED_FMT_SUPPORTED_DEV0_OFFSET)
    ),
  //
  // Enable  resize BAR CAP and LTR
  // RCC_BIF_STRAP2 - STRAP_RESIZE_BAR_EN_DEV0_F0
  //
  GNB_ENTRY_RMW (
    RCC_BIF_STRAP2_TYPE,
    RCC_BIF_STRAP2_ADDRESS,
    RCC_BIF_STRAP2_RESIZE_BAR_EN_DEV0_F0_MASK,
    (0x1 << RCC_BIF_STRAP2_RESIZE_BAR_EN_DEV0_F0_OFFSET)
    ),
  // STRAP_MEM_AP_SIZE_DEV0_F0  11:9  0x0
  GNB_ENTRY_RMW (
    RCC_BIF_STRAP8_TYPE,
    RCC_BIF_STRAP8_ADDRESS,
    RCC_BIF_STRAP8_MEM_AP_SIZE_DEV0_F0_MASK,
    (0x0 << RCC_BIF_STRAP8_MEM_AP_SIZE_DEV0_F0_OFFSET)
    ),
  //
  // Enable LTR
  // RCC_BIF_STRAP2 - STRAP_RESIZE_BAR_EN_DEV0_F0
  //
  GNB_ENTRY_RMW (
    RCC_BIF_STRAP3_TYPE,
    RCC_BIF_STRAP3_ADDRESS,
    RCC_BIF_STRAP3_LTR_EN_DEV0_MASK |
    RCC_BIF_STRAP3_LTR_EN_DN_DEV0_MASK,
    (0x1 << RCC_BIF_STRAP3_LTR_EN_DEV0_OFFSET) |
    (0x1 << RCC_BIF_STRAP3_LTR_EN_DN_DEV0_OFFSET)
    ),
  //
  // Enable PME_TURNOFF_MODE to 1 to involve SMU FW for this msg
  //
  GNB_ENTRY_RMW (
    SMN_BIFC_MISC_CTL_REG_TYPE,
    SMN_BIFC_MISC_CTL_REG_ADDRESS,
    MISC_CNTRL_REG_PME_TURNOFF_MODE_MASK,
    (0x1 << MISC_CNTRL_REG_PME_TURNOFF_MODE_OFFSET)
    ),
  //
  // Set HWINIT_WR_LOCK bit
  //
  GNB_ENTRY_RMW (
    RCC_PCIE_CNTL_TYPE,
    RCC_PCIE_CNTL_ADDRESS,//RCC_PCIE_CNTL_ADDRESS,
    RCC_PCIE_CNTL_HWINIT_WR_LOCK_MASK,
    (0x1 << RCC_PCIE_CNTL_HWINIT_WR_LOCK_OFFSET)
    ),
  GNB_ENTRY_RMW (
    RCC_PCIE_CNTL_TYPE,
    RCC_PCIE_CNTL1_ADDRESS,
    RCC_PCIE_CNTL_HWINIT_WR_LOCK_MASK,
    (0x1 << RCC_PCIE_CNTL_HWINIT_WR_LOCK_OFFSET)
    ),
  //
  // Enable FLR CAP
  //
  GNB_ENTRY_RMW (
    RCC_DEV0_EPF0_STRAP4_TYPE,
    RCC_DEV0_EPF0_STRAP4_ADDRESS,
    RCC_STRAP_FLR_EN_DEV0_F0_MASK,
    (0x1 << RCC_STRAP_FLR_EN_DEV0_F0_OFFSET)
    ),
  GNB_ENTRY_RMW (
    RCC_DEV0_EPF1_STRAP4_TYPE,
    RCC_DEV0_EPF1_STRAP4_ADDRESS,
    RCC_STRAP_FLR_EN_DEV0_F1_MASK,
    (0x1 << RCC_STRAP_FLR_EN_DEV0_F1_OFFSET)
    ),
  // MGCG enable
  GNB_ENTRY_RMW (
    MGCG_CTRL_TYPE,
    NBIF0_MGCG_CTRL_ADDRESS,
    NBIF_MGCG_EN_LCLK_MASK |
    NBIF_MGCG_HYSTERESIS_LCLK_MASK,
    (0x1 << NBIF_MGCG_EN_LCLK_OFFSET) |
    (0x40 << NBIF_MGCG_HYSTERESIS_LCLK_OFFSET)
    ),
  GNB_ENTRY_RMW (
    MGCG_CTRL_TYPE,
    SYSHUBMM0_NGDC_MGCG_CTRL_ADDRESS,
    NBIF_MGCG_EN_LCLK_MASK |
    NBIF_MGCG_HYSTERESIS_LCLK_MASK,
    (0x1 << NBIF_MGCG_EN_LCLK_OFFSET) |
    (0x40 << NBIF_MGCG_HYSTERESIS_LCLK_OFFSET)
    ),
  GNB_ENTRY_RMW (
    MGCG_CTRL_TYPE,
    SYSHUB_MGCG_CTRL_SHUBCLK_ADDRESS,
    NBIF_MGCG_EN_LCLK_MASK |
    NBIF_MGCG_HYSTERESIS_LCLK_MASK,
    (0x1 << NBIF_MGCG_EN_LCLK_OFFSET) |
    (0x40 << NBIF_MGCG_HYSTERESIS_LCLK_OFFSET)
    ),
  //
  //  SST Clock Gating
  //
  GNB_ENTRY_RMW (
    SION_WRAPPER_404_SST0_TYPE,
    SION_WRAPPER_404_SST0_ADDRESS,
    SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK4_MASK,
    (0x1 << SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK4_OFFSET)
    ),
  GNB_ENTRY_RMW (
    SION_WRAPPER_404_SST1_TYPE,
    SION_WRAPPER_404_SST1_ADDRESS,
    SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK4_MASK,
    (0x1 << SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK4_OFFSET)
    ),
  // SST Clock Gating Disable
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_SST_CLOCK_GATING_DISABLED,
    TYPE_SST0,
    SST_CLOCK_CTRL_SST0_ADDRESS,
    SST_CLOCK_CTRL_RXCLKGATEEn_MASK |
    SST_CLOCK_CTRL_TXCLKGATEEn_MASK,
    (0x0 << SST_CLOCK_CTRL_RXCLKGATEEn_OFFSET) |
    (0x0 << SST_CLOCK_CTRL_TXCLKGATEEn_OFFSET)
    ),
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_SST_CLOCK_GATING_DISABLED,
    TYPE_SST1,
    SST_CLOCK_CTRL_SST1_ADDRESS,
    SST_CLOCK_CTRL_RXCLKGATEEn_MASK |
    SST_CLOCK_CTRL_TXCLKGATEEn_MASK,
    (0x0 << SST_CLOCK_CTRL_RXCLKGATEEn_OFFSET) |
    (0x0 << SST_CLOCK_CTRL_TXCLKGATEEn_OFFSET)
    ),
// PCIe Memory Power Deep Sleep in L1
  GNB_ENTRY_RMW (
    PCIE_CONFIG_CNTL2_TYPE,
    PCIE_CONFIG_CNTL2_ADDRESS,
    PCIE_CTRL2_SLV_MEM_DS_EN_MASK |
    PCIE_CTRL2_MST_MEM_DS_EN_MASK |
    PCIE_CTRL2_REPLAY_MEM_DS_EN_MASK,
    (1 << PCIE_CTRL2_SLV_MEM_DS_EN_OFFSET) |
    (1 << PCIE_CTRL2_MST_MEM_DS_EN_OFFSET) |
    (1 << PCIE_CTRL2_REPLAY_MEM_DS_EN_OFFSET)
    ),
  GNB_ENTRY_RMW (
    PCIE_CONFIG_CNTL2_RX_TYPE,
    PCIE_CONFIG_CNTL2_RX_ADDRESS,
    PCIE_CTRL2_RX_SLVCPL_MEM_DS_EN_MASK,
    (1 << PCIE_CTRL2_RX_SLVCPL_MEM_DS_EN_OFFSET)
    ),
// PCIe Memory Power Shut Down in L1
  GNB_ENTRY_RMW (
    PCIE_CONFIG_CNTL2_TYPE,
    PCIE_CONFIG_CNTL2_ADDRESS,
    PCIE_CTRL2_SLV_MEM_SD_EN_MASK |
    PCIE_CTRL2_MST_MEM_SD_EN_MASK |
    PCIE_CTRL2_REPLAY_MEM_SD_EN_MASK,
    (1 << PCIE_CTRL2_SLV_MEM_SD_EN_OFFSET) |
    (1 << PCIE_CTRL2_MST_MEM_SD_EN_OFFSET) |
    (1 << PCIE_CTRL2_REPLAY_MEM_SD_EN_OFFSET)
    ),
  GNB_ENTRY_RMW (
    PCIE_CONFIG_CNTL2_RX_TYPE,
    PCIE_CONFIG_CNTL2_RX_ADDRESS,
    PCIE_CTRL2_RX_SLVCPL_MEM_SD_EN_MASK,
    (1 << PCIE_CTRL2_RX_SLVCPL_MEM_SD_EN_OFFSET)
    ),
// Enable early wakeup for L1 and nBIF by default
  GNB_ENTRY_RMW (
    IOMMU_L1_SDP_CLKREQ_CNTRL_F0_TYPE,
    IOMMU_L1_SDP_CLKREQ_CNTRL_F0_INST1_ADDRESS,
    HW_PG_WAKEUP_EN_DMA_MASK |
    HW_PG_WAKEUP_EN_HOST_MASK,
    (1 << HW_PG_WAKEUP_EN_DMA_OFFSET) |
    (1 << HW_PG_WAKEUP_EN_HOST_OFFSET)
    ),
  GNB_ENTRY_RMW (
    IOMMU_L1_SDP_CLKREQ_CNTRL_F0_TYPE,
    IOMMU_L1_SDP_CLKREQ_CNTRL_F0_INST2_ADDRESS,
    HW_PG_WAKEUP_EN_DMA_MASK |
    HW_PG_WAKEUP_EN_HOST_MASK,
    (1 << HW_PG_WAKEUP_EN_DMA_OFFSET) |
    (1 << HW_PG_WAKEUP_EN_HOST_OFFSET)
    ),
  GNB_ENTRY_RMW (
    IOAGR_SDP_PORT_CTRL_Type,
    IOAGR_SDP_PORT_CTRL_ADDRESS,
    IOAGR_SDP_DMA_ENABLE_EARLY_CLKREQ_MASK |
    IOAGR_SDP_HOST_ENABLE_EARLY_CLKREQ_MASK,
    (1 << IOAGR_SDP_DMA_ENABLE_EARLY_CLKREQ_OFFSET) |
    (1 << IOAGR_SDP_HOST_ENABLE_EARLY_CLKREQ_OFFSET)
    ),
  GNB_ENTRY_RMW (
    SMN_NBIF_CFG_TYPE,
    SMN_NBIF_CFG_Address,
    NBIF_PG_EARLY_WAKEUP_BY_CLIENT_ACTIVE_Mask,
    (1 << NBIF_PG_EARLY_WAKEUP_BY_CLIENT_ACTIVE_OFFSET)
    ),
//
  GNB_ENTRY_RMW (
    TYPE_SST0,
    SST_CLOCK_CTRL_SST0_ADDRESS,
    SST_CLOCK_CTRL_PCTRL_IDLE_TIME_MASK,
    (0xF0 << SST_CLOCK_CTRL_PCTRL_IDLE_TIME_OFFSET)
    ),
  GNB_ENTRY_RMW (
    TYPE_SST1,
    SST_CLOCK_CTRL_SST1_ADDRESS,
    SST_CLOCK_CTRL_PCTRL_IDLE_TIME_MASK,
    (0xF0 << SST_CLOCK_CTRL_PCTRL_IDLE_TIME_OFFSET)
    ),
// for SYSHUB deep sleep sideband. SDMA1 and CCP.
  GNB_ENTRY_RMW (
    SYSHUB_DS_CTRL_SOCCLK_TYPE,
    SYSHUB_DS_CTRL_SOCCLK_ADDRESS,
    HST_CL4_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Mask |
    DMA_CL2_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Mask,
    (0x1 << HST_CL4_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET) |
    (0x1 << DMA_CL2_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET)
    ),
// IOMMU L2 IOMMU_MMIO_CONTROL1_W
  GNB_ENTRY_RMW (
    IOMMU_MMIO_CONTROL1_W_TYPE,
    IOMMU_MMIO_CONTROL1_W_ADDRESS,
    InvIotlbTypeSup_W_Mask,
    (0x1 << InvIotlbTypeSup_W_OFFSET)
    ),
// Nbif B/D/F
  GNB_ENTRY_RMW (
    SMN_RCC_DEV0_PORT_STRAP7_TYPE,
    SMN_RCC_DEV0_PORT_STRAP7_ADDRESS,
    STRAP_RP_BUSNUM_DEV0_Mask |
    STRAP_DN_DEVNUM_DEV0_Mask |
    STRAP_DN_FUNCID_DEV0_Mask,
    (0x0 << STRAP_RP_BUSNUM_DEV0_OFFSET) |
    (0x8 << STRAP_DN_DEVNUM_DEV0_OFFSET) |
    (0x1 << STRAP_DN_FUNCID_DEV0_OFFSET)
    ),
  GNB_ENTRY_RMW (
    SMN_RCC_DEV1_PORT_STRAP7_TYPE,
    SMN_RCC_DEV1_PORT_STRAP7_ADDRESS,
    STRAP_RP_BUSNUM_DEV1_Mask |
    STRAP_DN_DEVNUM_DEV1_Mask |
    STRAP_DN_FUNCID_DEV1_Mask,
    (0x0 << STRAP_RP_BUSNUM_DEV1_OFFSET) |
    (0x8 << STRAP_DN_DEVNUM_DEV1_OFFSET) |
    (0x2 << STRAP_DN_FUNCID_DEV1_OFFSET)
    ),
// NBIF PG MST
  GNB_ENTRY_RMW (
    TYPE_D0F0xBC,
    NBIF_PGMST_CTRL_ADDRESS,
    NBIF_CFG_PG_EN_MASK |
    NBIF_CFG_PG_HYSTERESIS_MASK,
    (0x1 << NBIF_CFG_PG_EN_OFFSET) |
    (0x50 << NBIF_CFG_PG_HYSTERESIS_OFFSET)
    ),
// IOHC CRS
  GNB_ENTRY_RMW (
    IOHC_PCIE_CRS_Count_TYPE,
    IOHC_PCIE_CRS_Count_Address,
    CrsDelayCount_Mask |
    CrsLimitCount_Mask,
    (0x6 << CrsDelayCount_OFFSET) |
    (0x6 << CrsLimitCount_OFFSET)
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    SMN_CGPLLCntrlReg5_ADDRESS,
    0x0
    ),
  GNB_ENTRY_WR (
    TYPE_SMN,
    SMN_CGPLLCntrlReg6_ADDRESS,
    0x0
    ),
// IOHC:POISON_ACTION_CONTROL
  GNB_ENTRY_RMW (
    POISON_ACTION_CONTROL_TYPE,
    POISON_ACTION_CONTROL_ADDRESS,
    NBRASCFG_0400_IntPoisonSyncFloodEn_MASK |
    NBRASCFG_0400_IntPoisonLinkDisEn_MASK |
    NBRASCFG_0400_IntPoisonAPMLErrEn_MASK,
    (0x1 << NBRASCFG_0400_IntPoisonSyncFloodEn_OFFSET) |
    (0x1 << NBRASCFG_0400_IntPoisonLinkDisEn_OFFSET) |
    (0x1 << NBRASCFG_0400_IntPoisonAPMLErrEn_OFFSET)
    ),
  GNB_ENTRY_TERMINATE
};

GNB_TABLE ROMDATA GnbEnvInitTableRV [] = {
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IGFX_DISABLED,
    TYPE_SMN,
    RCC_DEV0_EPF0_STRAP0_ADDRESS,
    STRAP_FUNC_EN_DEV0_F0_MASK,
    (0x0 << STRAP_FUNC_EN_DEV0_F0_OFFSET) // 0
    ),
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IGFX_DISABLED,
    TYPE_SMN,
    DEV0_PORT_STRAP0_ADDRESS,
    STRAP_EPF0_DUMMY_EN_DEV0_MASK,
    (0x1 << STRAP_EPF0_DUMMY_EN_DEV0_OFFSET)
    ),
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IGFX_DISABLED,
    TYPE_SMN,
    RCC_DEV0_EPF1_STRAP0_ADDRESS,
    STRAP_FUNC_EN_DEV0_F1_MASK,
    (0x0 << STRAP_FUNC_EN_DEV0_F1_OFFSET) //0
    ),
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IGFX_DISABLED,
    TYPE_SMN,
    RCC_DEV0_EPF0_STRAP0_ADDRESS,
    STRAP_DEVICE_ID_DEV0_F0_MASK,
    (0x145A << STRAP_DEVICE_ID_DEV0_F0_OFFSET)
    ),
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IGFX_DISABLED,
    TYPE_SMN,
    RCC_DEV0_EPF0_STRAP13_ADDRESS,
    STRAP_CLASS_CODE_PIF_DEV0_F0_MASK |
    STRAP_CLASS_CODE_SUB_DEV0_F0_MASK |
    STRAP_CLASS_CODE_BASE_DEV0_F0_MASK,
    (0x0 << STRAP_CLASS_CODE_PIF_DEV0_F0_OFFSET) |
    (0x0 << STRAP_CLASS_CODE_SUB_DEV0_F0_OFFSET) |
    (0x13 << STRAP_CLASS_CODE_BASE_DEV0_F0_OFFSET)
    ),
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IGFX_DISABLED,
    TYPE_SMN,
    RCC_DEV0_EPF0_STRAP4_ADDRESS,
    RCC_STRAP_INTERRUPT_PIN_DEV0_F0_MASK,
    (0x0 << RCC_STRAP_INTERRUPT_PIN_DEV0_F0_OFFSET)
    ),
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IGFX_DISABLED,
    TYPE_SMN,
    RCC_DEV0_EPF0_STRAP3_ADDRESS,
    STRAP_MSI_EN_DEV0_F0_MASK |
    STRAP_MSIX_EN_DEV0_F0_MASK,
    (0x0 << STRAP_MSI_EN_DEV0_F0_OFFSET) |
    (0x0 << STRAP_MSIX_EN_DEV0_F0_OFFSET)
    ),
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IGFX_DISABLED,
    TYPE_SMN,
    RCC_DEV0_EPF0_STRAP4_ADDRESS,
    RCC_STRAP_PME_SUPPORT_DEV0_F0_MASK,
    (0x0 << RCC_STRAP_PME_SUPPORT_DEV0_F0_OFFSET)
    ),
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IGFX_DISABLED,
    TYPE_SMN,
    RCC_DEV0_EPF0_STRAP3_ADDRESS,
    STRAP_VENDOR_ID_BIT_DEV0_F0_MASK,
    (0x1 << STRAP_VENDOR_ID_BIT_DEV0_F0_OFFSET)
    ),
// FLR disable
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IGFX_DISABLED,
    TYPE_SMN,
    RCC_DEV0_EPF0_STRAP4_ADDRESS,
    RCC_STRAP_FLR_EN_DEV0_F0_MASK,
    (0x0 << RCC_STRAP_FLR_EN_DEV0_F0_OFFSET)
    ),
// LTR disable
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IGFX_DISABLED,
    TYPE_SMN,
    RCC_BIF_STRAP3_ADDRESS,
    RCC_BIF_STRAP3_LTR_EN_DEV0_MASK |
    RCC_BIF_STRAP3_LTR_EN_DN_DEV0_MASK,
    (0x0 << RCC_BIF_STRAP3_LTR_EN_DEV0_OFFSET) |
    (0x0 << RCC_BIF_STRAP3_LTR_EN_DN_DEV0_OFFSET)
    ),
// ATS disable
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IGFX_DISABLED,
    TYPE_SMN,
    RCC_BIF_STRAP2_ADDRESS,
    RCC_BIF_STRAP2_ATS_EN_DEV0_F0_MASK,
    (0x0 << RCC_BIF_STRAP2_ATS_EN_DEV0_F0_OFFSET)
    ),
// PASID disable
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IGFX_DISABLED,
    TYPE_SMN,
    RCC_BIF_STRAP2_ADDRESS,
    RCC_BIF_STRAP2_PASID_EN_DEV0_F0_MASK,
    (0x0 << RCC_BIF_STRAP2_PASID_EN_DEV0_F0_OFFSET)
    ),

// PRI disable
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IGFX_DISABLED,
    TYPE_SMN,
    RCC_BIF_STRAP2_ADDRESS,
    RCC_BIF_STRAP2_PAGE_REQ_EN_DEV0_F0_MASK,
    (0x0 << RCC_BIF_STRAP2_PAGE_REQ_EN_DEV0_F0_OFFSET)
    ),
//resize bar disable
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IGFX_DISABLED,
    TYPE_SMN,
    RCC_BIF_STRAP2_ADDRESS,
    RCC_BIF_STRAP2_RESIZE_BAR_EN_DEV0_F0_MASK,
    (0x0 << RCC_BIF_STRAP2_RESIZE_BAR_EN_DEV0_F0_OFFSET)
    ),
// atomic disable
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IGFX_DISABLED,
    TYPE_SMN,
    RCC_BIF_STRAP3_ADDRESS,
    RCC_BIF_STRAP3_ATOMIC_EN_DN_DEV0_MASK,
    (0x0 << RCC_BIF_STRAP3_ATOMIC_EN_DN_DEV0_OFFSET)
    ),
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IGFX_DISABLED,
    TYPE_SMN,
    SMN_0x10131014_ADDRESS,
    SMN_0x10131014_STRAP_ATOMIC_64BIT_EN_DN_DEV0_MASK,
    (0x0 << SMN_0x10131014_STRAP_ATOMIC_64BIT_EN_DN_DEV0_OFFSET)
    ),
// AER disable
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IGFX_DISABLED,
    TYPE_SMN,
    RCC_BIF_STRAP2_ADDRESS,
    RCC_BIF_STRAP2_AER_EN_DEV0_F0_MASK |
    RCC_BIF_STRAP2_ACS_EN_DEV0_F0_MASK,
    (0x0 << RCC_BIF_STRAP2_AER_EN_DEV0_F0_OFFSET) |
    (0x0 << RCC_BIF_STRAP2_ACS_EN_DEV0_F0_OFFSET)
    ),
  GNB_ENTRY_TERMINATE
};

GNB_TABLE ROMDATA GnbMidInitTableRV [] = {

  GNB_ENTRY_TERMINATE
};

