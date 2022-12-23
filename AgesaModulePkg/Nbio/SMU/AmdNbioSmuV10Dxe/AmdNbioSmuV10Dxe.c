/* $NoKeywords:$ */
/**
 * @file
 *
 * AmdNbioSmuV10Dxe Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  AmdNbioSmuV10Dxe
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
#include <PiDxe.h>
#include <Filecode.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/AmdNbioPcieServicesProtocol.h>
#include <Protocol/AmdCcxProtocol.h>
#include <Protocol/SocLogicalIdProtocol.h>
#include <Protocol/AmdNbioServicesProtocol.h>
#include <Protocol/PciEnumerationComplete.h>
#include <GnbDxio.h>
#include <Guid/GnbPcieInfoHob.h>
#include <GnbRegistersRV.h>
#include <Library/GnbRegisterAccZpLib.h>
#include <Library/NbioHandleLib.h>
#include <Library/PcieConfigLib.h>
#include <IdsHookId.h>
#include <Library/AmdIdsHookLib.h>
#include <Guid/HobList.h>
#include <Library/HobLib.h>
#include <Library/UefiLib.h>
#include <Library/NbioHandleLib.h>
#include <Library/NbioSmuV10Lib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/NbioRegisterAccLib.h>
#include <Library/SmnAccessLib.h>
#include <AmdNbioSmuV10Dxe.h>
#include <smu10_bios_if.h>
#include <smu10.h>
#include <Smu10FeaturesEnable.h>
#include <Library/BaseMemoryLib.h>
#include <Library/GnbPciAccLib.h>
#include <CcxRegistersRV.h>
#include <Protocol/MpService.h>
#include "AcBtc.h"
#include <Library/GnbPciLib.h>


#define GNB_MB_TO_PAGE(a) ((a) * (SIZE_1MB / EFI_PAGE_SIZE))
#define FILECODE        NBIO_SMU_AMDNBIOSMUV10DXE_AMDNBIOSMUV10DXE_FILECODE
#define MAX_CAC_WEIGHT_NUM  21
#define MaxBitNumber        31

/*----------------------------------------------------------------------------------------
 *                         E X T E R N   D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */

extern PPTable_t PPTableDefault;

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define SMUFUSEx000005B8                              0x5D5B8
#define SMUFUSEx000005BC                              0x5D5BC

#define YM2700C4T4MFB_configID                        1582
#define YM2500C4T4MFB_configID                        1587
#define PCICFG_SPACE_Master_CLASS_CODE_OFFSET         0x0B
#define PCICFG_SPACE_SUB_CLASS_CODE_OFFSET            0x0A

//<Embedded_Override_Start>    
//#defines for NPU part names and wattage
#define NPU_OPN_V1500B "V1500B"
#define NPU_OPN_V1780B "V1780B"
#define R2K_OPN_R2312 "R2312 "

#define SYSTEM_CONFIG_TDP_12W 1
#define SYSTEM_CONFIG_TDP_15W 2
#define SYSTEM_CONFIG_TDP_25W 3
#define SYSTEM_CONFIG_TDP_35W 7
#define SYSTEM_CONFIG_TDP_45W 8
#define SYSTEM_CONFIG_TDP_54W 9
#define SYSTEM_CONFIG_TDP_6W 11
#define SYSTEM_CONFIG_TDP_6W_EMBEDDED 111
#define SYSTEM_CONFIG_TDP_10W 12
#define SYSTEM_CONFIG_TDP_8W 13

//Defining Default TDP for the OPNs
#define POWER_LIMIT_15W 15 
#define POWER_LIMIT_45W 45
#define POWER_LIMIT_6W 6
#define POWER_LIMIT_8W 8

// RV1 OPN 
#define RV1_SINGLE_SOURCE  0
#define RV1_B4_DUAL_SOURCE  2
//<Embedded_Override_End>

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */


AMD_CORE_TOPOLOGY_SERVICES_PROTOCOL mAmdCoreTopologyServicesProtocol = {
  SmuV10GetCoreTopologyOnDie,
  SmuV10LaunchThread
};

DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL mDxeAmdNbioSmuServicesProtocol = {
  DXE_AMD_NBIO_SMU_SERVICES_DXE_REVISION,
  AmdSmuReadFuseByName,
  AmdSmuReadFuseByNumber,
  AmdSmuServiceRequest,
  AmdSmuRegisterRead,
  AmdSmuRegisterWrite,
  AmdSmuRegisterRMW,
  AmdSmuReadBrandString,
  AmdSmuReadCacWeights,
  AmdSmuReadThrottleThresholds
};

DXE_AMD_NBIO_SMU_INIT_COMPLETE_PROTOCOL mDxeAmdNbioSmuInitCompleteProtocol = {
  AMD_NBIO_SERVICES_PROTOCOL_REVISION
};

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
/**
 *---------------------------------------------------------------------------------------
 *  CallbackSmuInitDxeDone
 *
 *  Description:
 *     notification event handler after gEfiMpServiceProtocolGuid ready
 *  Parameters:
 *    @param[in]     Event      Event whose notification function is being invoked.
 *    @param[in]     *Context   Pointer to the notification function's context.
 *
 *---------------------------------------------------------------------------------------
 **/
VOID
EFIAPI
CallbackSmuInitDxeDone (
  IN      EFI_EVENT  Event,
  IN      VOID       *Context
  )
{
  EFI_STATUS                Status;
  EFI_MP_SERVICES_PROTOCOL  *MpService;
  EFI_HANDLE                Handle;

  IDS_HDT_CONSOLE (MAIN_FLOW, "CallbackSmuInitDxeDone notify\n");
  Handle = NULL;
  Status = gBS->LocateProtocol (
                  &gEfiMpServiceProtocolGuid,
                  NULL,
                  &MpService
                  );
  if (!EFI_ERROR (Status)) {
    Status = gBS->InstallProtocolInterface (
                          &Handle,
                          &gAmdNbioSmuInitCompleteProtocolGuid,
                          EFI_NATIVE_INTERFACE,
                          &mDxeAmdNbioSmuInitCompleteProtocol
                          );
    IDS_HDT_CONSOLE (MAIN_FLOW, "Publish DXE_AMD_NBIO_SMU_INIT_COMPLETE_PROTOCOL(0x%x)\n", Status);
    gBS->CloseEvent (Event);
  }
}

/**
 *---------------------------------------------------------------------------------------
 *  SelectUlvVidOffsetRequired
 *
 *  Description:
 *     notification event handler after gAmdCcxDxeInitCompleteProtocolGuid ready
 *  Parameters:
 *    @param[in]     NbioHandle Pointer to GNB_HANDLE
 *
 * @retval 0         The OPN_ConfigId requires an offset of 0x00
 * @retval 1         The OPN_ConfigId requires an offset of 0x0E
 * @retval 2         The OPN_ConfigId requires an offset of 0x08
 *
 *---------------------------------------------------------------------------------------
 **/

UINT8
SelectUlvVidOffsetRequired (
  IN         GNB_HANDLE  *NbioHandle
  )
{
  BOOLEAN   ReturnValue;
  UINT32    Value0;
  UINT32    Value1;
  UINT16    OPN_ConfigId;

  ReturnValue = 0;
  NbioRegisterRead (NbioHandle, TYPE_SMN, SMUFUSEx000005B8, &Value0, 0);
  NbioRegisterRead (NbioHandle, TYPE_SMN, SMUFUSEx000005BC, &Value1, 0);
  OPN_ConfigId = (UINT16) ((Value0 >> 27) | (((Value1 & 0x7FF) << 5)));
  if (OPN_ConfigId == YM2700C4T4MFB_configID) {
    ReturnValue = 1;
  } else if (OPN_ConfigId == YM2500C4T4MFB_configID) {
    ReturnValue = 2;
  }
  return ReturnValue;
}

/**
 *---------------------------------------------------------------------------------------
 *  CallbackAfterCCxDxeDone
 *
 *  Description:
 *     notification event handler after gAmdCcxDxeInitCompleteProtocolGuid ready
 *  Parameters:
 *    @param[in]     Event      Event whose notification function is being invoked.
 *    @param[in]     *Context   Pointer to the notification function's context.
 *
 *---------------------------------------------------------------------------------------
 **/
VOID
EFIAPI
CallbackAfterCcxDxeDone (
  IN      EFI_EVENT  Event,
  IN      VOID       *Context
  )
{
  EFI_STATUS                           Status;
  PCIe_PLATFORM_CONFIG                 *PcieFromHob;
  PCIe_PLATFORM_CONFIG                 *Pcie;
  GNB_HANDLE                           *NbioHandle;
  UINT32                               SmuArg[6];
  DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL   *NbioSmuServiceProtocol;
  DXE_AMD_CCX_INIT_COMPLETE_PROTOCOL   *CcxDxeInitCompleteProtocol;
  VOID                                 *Registration;
  UINTN                                BitFlag;
  UINT32                               PackageType;
  UINT32                               Value;
  
  IDS_HDT_CONSOLE (MAIN_FLOW, "CallbackAfterCcxDxeDone First notify\n");
  PcieFromHob = NULL;
  BitFlag = 0;
  //
  // Add more check to locate protocol after got event, because
  // the library will signal this event immediately once it is register
  // just in case it is already installed.
  //
  Status = gBS->LocateProtocol (
                  &gAmdCcxDxeInitCompleteProtocolGuid,
                  NULL,
                  &CcxDxeInitCompleteProtocol
                  );
  if (EFI_ERROR (Status)) {
    return;
  }

  IDS_HDT_CONSOLE (MAIN_FLOW, "CallbackAfterCcxDxeDone Start\n");

  SmuDxeInitialize (&PcieFromHob);
  Pcie = PcieFromHob;

  Status = gBS->LocateProtocol (
                  &gAmdNbioSmuServicesProtocolGuid,
                  NULL,
                  &NbioSmuServiceProtocol
                  );
  IDS_HDT_CONSOLE (MAIN_FLOW, "Status = 0x%x\n", Status);

  NbioHandle = NbioGetHandle (Pcie);
  while (NbioHandle != NULL) {

    switch (SelectUlvVidOffsetRequired (NbioHandle)) {
      case 1:
        PcdSet32 (PcdUlvVidOffset, 0x0E);
        PcdSetBool (PcdUlvVidCtrl, TRUE);
      break;
      case 2:
        PcdSet32 (PcdUlvVidOffset, 0x08);
        PcdSetBool (PcdUlvVidCtrl, TRUE);
      break;
      default:
      break;
    }

    IDS_HDT_CONSOLE (MAIN_FLOW, "PcdUlvVidCtrl = 0%x\n", PcdGetBool (PcdUlvVidCtrl));
    IDS_HDT_CONSOLE (MAIN_FLOW, "PcdUlvVidOffset = 0%x\n", PcdGet32 (PcdUlvVidOffset));

    if (PcdGetBool (PcdUlvVidCtrl) == TRUE) {
      NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
      SmuArg[0] = PcdGet32 (PcdUlvVidOffset);
      IDS_HDT_CONSOLE (MAIN_FLOW, "UlvVidOffset = 0%x\n", SmuArg[0]);
      Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetUlvVidOffset, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
    }

    //
    //  Step24. BIOS call BIOSSMC_MSG_EnableAllSmuFeatures with a bitmask indicating which SMU features to enable.
    //          Masks are allocated in export/smu10.h. Each mask bit should be linked to a CBS option to enable/Disable it.
    //
    NbioSmuServiceCommonInitArgumentsV10 (SmuArg);

    //
    // Update PcdSmuFeatureControlDefines value from CBS.
    //
    SmuArg[0] = PcdGet32 (PcdSmuFeatureControlDefines);
    SmuArg[1] = PcdGet32 (PcdSmuFeatureControlDefinesExt);
    if ((PcdGet8 (PcdAcBtc)) || (PcdGet8 (PcdDcBtc))) {
      // Do not enable CC6 if we are going to run Ac or Dc BTC
      BitFlag = (FEATURE_CORE_CSTATES_BIT > MaxBitNumber) ? 1 : 0;
      if (SmuArg[BitFlag] & (1 << (FEATURE_CORE_CSTATES_BIT % 32))) {
        SmuArg[BitFlag] &= ~((UINT32) (1 << (FEATURE_CORE_CSTATES_BIT % 32)));
      }
    }
    if (PcdGet8 (PcdCfgIgpuContorl) == 0) {
      // Disable GFX DPM if we are going to disable iGPU
      if (SmuArg[0] & (1 << (FEATURE_GFX_DPM_BIT % 32))) {
        SmuArg[0] &= ~((UINT32) (1 << (FEATURE_GFX_DPM_BIT % 32)));
      }
    }

    IDS_HDT_CONSOLE (MAIN_FLOW, "SmuFeatureControlDefines = 0x%x, SmuFeatureControlDefinesExt = 0x%x\n", SmuArg[0], SmuArg[1]);
    Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_EnableSmuFeatures, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
    IDS_HDT_CONSOLE (MAIN_FLOW, "Status = 0x%x\n", Status);
    //<Embedded_Override_Start>
    NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
    SmuArg[0] = 90;
    Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle),SMC_MSG_SetApmlHighTempThreshold, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
    if (EFI_ERROR (Status)) {
        IDS_HDT_CONSOLE (MAIN_FLOW, "ALERT_L: Setting a value to SB-TSI High Temperature(SBTSIx07) register Status:%r\n", Status);
    }
  
    //
    // Update 10Gbe status
    //
    IDS_HDT_CONSOLE (MAIN_FLOW, "Enable Xgbe Clk\n");
    NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
    SmuArg[0]=1;
    Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetGbeStatus, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);

    Value = PcdGet32 (PcdGetRVFamilyOPN);
    IDS_HDT_CONSOLE (MAIN_FLOW, "PcdGetRVFamilyOPN Value = 0x%x\n", Value);
    //If it's not NPU Power UP/DOWN graphics accordingly.
    if ( !(Value & BIT16) ) { 
    //<Embedded_Override_End>
	  // PowerUp Gfx
	  IDS_HDT_CONSOLE (MAIN_FLOW, "Enable Power Up Gfx\n");
	  NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
      Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_PowerUpGfx, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);

	  if (PcdGet8 (PcdCfgIgpuContorl) == 0) {
	    IDS_HDT_CONSOLE (MAIN_FLOW, "Power Down Gfx if iGPU is Disabled\n");
        NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
		Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_PowerDownGfx, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
	  }
    //<Embedded_Override_Start>
    }
    //<Embedded_Override_End>
    NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
    PackageType = LibAmdGetPackageType ((AMD_CONFIG_PARAMS *) NULL);
    if ((1 << RV_SOCKET_AM4) == PackageType) {
      SmuArg[0] = VDDOFF_VID_AM4;
    } else {
      SmuArg[0] = VDDOFF_VID_FP5;
    }

    IDS_HDT_CONSOLE (MAIN_FLOW, "PcdVddOffVidCtrl = 0%x\n", PcdGetBool (PcdVddOffVidCtrl));
    IDS_HDT_CONSOLE (MAIN_FLOW, "PcdVddOffVid = 0%x\n", PcdGet32 (PcdVddOffVid));

    if (PcdGetBool (PcdVddOffVidCtrl) == TRUE) {
      if (PcdGet32 (PcdVddOffVid) >= 1550) {
       SmuArg[0] = 0;
       } else {
         SmuArg[0] = ((1550 - PcdGet32 (PcdVddOffVid)) * 160) / 1000;
      }
    }
    IDS_HDT_CONSOLE (MAIN_FLOW, "VddOffVid = 0%x\n", SmuArg[0]);
    Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetVddOffVid, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);

    if ((1 << RV_SOCKET_AM4) == PackageType) {
      // PPT Limit
      NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
      SmuArg[0] = PcdGet32 (PcdMocPPTLimit);
      if (SmuArg[0] != 0) {
        Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetFastPPTLimit, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
        Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetSlowPPTLimit, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
      }
      // TDC Limit
      NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
      SmuArg[0] = PcdGet32 (PcdMocTDCLimit);
      if (SmuArg[0] != 0) {
        Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetVrmCurrentLimit, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
      }
      NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
      SmuArg[0] = PcdGet32 (PcdMocSocTDCLimit);
      if (SmuArg[0] != 0) {
        Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetVrmSocCurrentLimit, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
      }
      // EDC Limit
      NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
      SmuArg[0] = PcdGet32 (PcdMocEDCLimit);
      if (SmuArg[0] != 0) {
        Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetVrmMaximumCurrentLimit, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
      }
      NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
      SmuArg[0] = PcdGet32 (PcdMocSocEDCLimit);
      if (SmuArg[0] != 0) {
        Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetVrmSocMaximumCurrentLimit, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
      }

      if (PcdGetBool (PcdOcDisable)) {
        NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
        SmuArg[0] = 1;
        Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_OC_Disable, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
      } else {
        NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
        SmuArg[0] = (UINT32) PcdGet16 (PcdOcVoltageMax);
        if (SmuArg[0] != 0) {
          Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_OC_VoltageMax, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
        }
        NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
        SmuArg[0] = (UINT32) PcdGet16 (PcdOcFrequencyMax);
        if (SmuArg[0] != 0) {
          Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_OC_FrequencyMax, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
        }
      }
    }
    //
    //  Enable SMC_MSG_EnableCC6Filter
    //
    NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
    Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_EnableCC6Filter, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);

    if (PcdGet8 (PcdCfgPeApmEnable)) {
      if (PcdGet32 (PcdSetSlowPPTLimitApuOnly)) {
        NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
        SmuArg[0] = PcdGet32 (PcdSetSlowPPTLimitApuOnly);  // Input mW
        Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetSlowPPTLimitApuOnly, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
      }
    }

    NbioHandle = GnbGetNextHandle (NbioHandle);
  }

  //
  //  If AC BTC is enabled, runs the AC BTC flow.
  //
  IDS_HDT_CONSOLE (MAIN_FLOW, "AcBtc \n");
  if ((PcdGet8 (PcdAcBtc)) || (PcdGet8 (PcdDcBtc))) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "Notify AcBtc \n");
    EfiCreateProtocolNotifyEvent (&gEfiMpServiceProtocolGuid, TPL_CALLBACK, CallbackAcBtc, NULL, &Registration);
  }

  EfiCreateProtocolNotifyEvent (&gEfiMpServiceProtocolGuid, TPL_CALLBACK, CallbackSmuInitDxeDone, NULL, &Registration);
  //
  // Close event, so it will not be invoked again.
  //
  gBS->CloseEvent (Event);

//  ServerHotplugInitV10Dxe (Pcie);

  IDS_HDT_CONSOLE (MAIN_FLOW, "CallbackAfterCcxDxeDone End\n");
}


/**
 * This service retrieves information about the layout of the cores on the given die.
 *
 * @param[in]  This                           A pointer to the
 *                                            AMD_CORE_TOPOLOGY_SERVICES_PROTOCOL instance.
 * @param[in]  Socket                         Zero-based socket number to check.
 * @param[in]  Die                            The target die's identifier within Socket.
 * @param[out] NumberOfComplexes              Pointer to the number of enabled complexes on
 *                                            the given socket / die.
 * @param[out] NumberOfCores                  Pointer to the number of enabled cores per
 *                                            complex on the given socket / die.
 * @param[out] NumberOfThreads                Pointer to the number of enabled threads per
 *                                            core on the given socket / die.
 *
 * @retval EFI_SUCCESS                        The core topology information was successfully retrieved.
 * @retval EFI_INVALID_PARAMETER              Socket is non-existent.
 * @retval EFI_INVALID_PARAMETER              Die is non-existent.
 * @retval EFI_INVALID_PARAMETER              All output parameter pointers are NULL.
 *
 **/
EFI_STATUS
SmuV10GetCoreTopologyOnDie (
  IN       AMD_CORE_TOPOLOGY_SERVICES_PROTOCOL   *This,
  IN       UINTN                                 Socket,
  IN       UINTN                                 Die,
     OUT   UINTN                                 *NumberOfComplexes,
     OUT   UINTN                                 *NumberOfCores,
     OUT   UINTN                                 *NumberOfThreads
  )
{
  DXE_AMD_NBIO_PCIE_SERVICES_PROTOCOL *PcieServicesProtocol;
  PCIe_PLATFORM_CONFIG                *Pcie;
  EFI_STATUS                          Status;
  GNB_HANDLE                          *GnbHandle;
  AMD_CONFIG_PARAMS                   *StdHeader;
  GNB_PCIE_INFORMATION_DATA_HOB       *PciePlatformConfigHobData;
  PWR_01C_STRUCT                      ThreadConfiguration;

  IDS_HDT_CONSOLE (MAIN_FLOW, "SmuV10GetCoreTopologyOnDie Entry\n");
  GnbHandle = NULL;
  StdHeader = NULL;
  // Need topology structure
  Status = gBS->LocateProtocol (
                  &gAmdNbioPcieServicesProtocolGuid,
                  NULL,
                  &PcieServicesProtocol
                  );

//  ASSERT (Status == EFI_SUCCESS);
  if (Status == EFI_SUCCESS) {
    PcieServicesProtocol->PcieGetTopology (PcieServicesProtocol, (UINT32 **) &PciePlatformConfigHobData);
    Pcie = &(PciePlatformConfigHobData->PciePlatformConfigHob);

    GnbHandle = NbioGetHandle (Pcie);
    while (GnbHandle != NULL) {
      //Find GnbHandle for this Socket/Die
      if ((Socket == GnbHandle->SocketId) && (Die == GnbHandle->DieNumber))  {
        break;
      }
      GnbHandle = GnbGetNextHandle (GnbHandle);
    }
//    ASSERT (GnbHandle != NULL);
    if (GnbHandle != NULL) {
      Status = GnbRegisterReadZP (GnbHandle,
                                  THREAD_CONFIGURATION_TYPE,
                                  THREAD_CONFIGURATION_ADDRESS,
                                  &ThreadConfiguration,
                                  0,
                                  StdHeader);
      *NumberOfComplexes = ThreadConfiguration.Field.ComplexCount + 1;
      *NumberOfCores = ThreadConfiguration.Field.CoreCount + 1;
      *NumberOfThreads = (ThreadConfiguration.Field.SMTMode == 0) ? 2 : 1;
    } else {
      Status = EFI_INVALID_PARAMETER;
    }
  }

  IDS_HDT_CONSOLE (MAIN_FLOW, "SmuV10GetCoreTopologyOnDie Exit\n");
  return Status;
}

/**
 * This service will start a core to fetch its first instructions from the reset
 * vector.  This service may only be called from the BSP.
 *
 * @param[in]  This                           A pointer to the
 *                                            AMD_CORE_TOPOLOGY_SERVICES_PROTOCOL instance.
 * @param[in]  Socket                         Zero-based socket number of the target thread.
 * @param[in]  Die                            Zero-based die number within Socket of the target thread.
 * @param[in]  LogicalComplex                 Zero-based logical complex number of the target thread.
 * @param[in]  LogicalThread                  Zero-based logical thread number of the target thread.
 *
 * @retval EFI_SUCCESS                        The thread was successfully launched.
 * @retval EFI_DEVICE_ERROR                   The thread has already been launched.
 * @retval EFI_INVALID_PARAMETER              Socket is non-existent.
 * @retval EFI_INVALID_PARAMETER              Die is non-existent.
 * @retval EFI_INVALID_PARAMETER              LogicalComplex is non-existent.
 * @retval EFI_INVALID_PARAMETER              LogicalThread is non-existent.
 *
 **/
EFI_STATUS
SmuV10LaunchThread (
  IN       AMD_CORE_TOPOLOGY_SERVICES_PROTOCOL   *This,
  IN       UINTN                                 Socket,
  IN       UINTN                                 Die,
  IN       UINTN                                 LogicalComplex,
  IN       UINTN                                 LogicalThread
  )
{
  DXE_AMD_NBIO_PCIE_SERVICES_PROTOCOL *PcieServicesProtocol;
  PCIe_PLATFORM_CONFIG                *Pcie;
  EFI_STATUS                          Status;
  GNB_HANDLE                          *GnbHandle;
  AMD_CONFIG_PARAMS                   *StdHeader;
  GNB_PCIE_INFORMATION_DATA_HOB       *PciePlatformConfigHobData;
  PWR_018_STRUCT                      ThreadEnable;
  PWR_01C_STRUCT                      ThreadConfiguration;
  UINTN                               NumberOfThreads;
  UINTN                               NumberOfCores;
  UINTN                               NumberOfLogicalThreads;
  UINT32                              SmuArg[6];

  IDS_HDT_CONSOLE (MAIN_FLOW, "SmuV10LaunchThread Entry\n");
  GnbHandle = NULL;
  StdHeader = NULL;
  // Need topology structure
  Status = gBS->LocateProtocol (
                  &gAmdNbioPcieServicesProtocolGuid,
                  NULL,
                  &PcieServicesProtocol
                  );

//  ASSERT (Status == EFI_SUCCESS);
  if (Status == EFI_SUCCESS) {
    PcieServicesProtocol->PcieGetTopology (PcieServicesProtocol, (UINT32 **) &PciePlatformConfigHobData);
    Pcie = &(PciePlatformConfigHobData->PciePlatformConfigHob);
    GnbHandle = NbioGetHandle (Pcie);
    while (GnbHandle != NULL) {
      //Find GnbHandle for this Socket/Die
      if ((Socket == GnbHandle->SocketId) && (Die == GnbHandle->DieNumber)) {
        break;
      }
      GnbHandle = GnbGetNextHandle (GnbHandle);
    }
//    ASSERT (GnbHandle != NULL);
    if (GnbHandle != NULL) {
      Status = GnbRegisterReadZP (GnbHandle,
                                  THREAD_ENABLE_TYPE,
                                  THREAD_ENABLE_ADDRESS,
                                  &ThreadEnable,
                                  0,
                                  StdHeader);
      Status = GnbRegisterReadZP (GnbHandle,
                                  THREAD_CONFIGURATION_TYPE,
                                  THREAD_CONFIGURATION_ADDRESS,
                                  &ThreadConfiguration,
                                  0,
                                  StdHeader);
      NumberOfThreads = (ThreadConfiguration.Field.SMTMode == 0) ? 2 : 1;
      NumberOfCores = ThreadConfiguration.Field.CoreCount + 1;
      NumberOfLogicalThreads = NumberOfCores * NumberOfThreads;
      if ((LogicalComplex <= ThreadConfiguration.Field.ComplexCount) && (LogicalThread < NumberOfLogicalThreads)) {
        if ((ThreadEnable.Field.ThreadEn & (1 << (LogicalThread + (8 * LogicalComplex)))) == 0) {
          ThreadEnable.Field.ThreadEn |= 1 << (LogicalThread + (8 * LogicalComplex));
          Status = GnbRegisterWriteZP (GnbHandle,
                                       THREAD_ENABLE_TYPE,
                                       THREAD_ENABLE_ADDRESS,
                                       &ThreadEnable,
                                       0,
                                       StdHeader);
          NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
          SmuArg[0] = 0xAA55AA55;
          Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (GnbHandle), SMC_MSG_TestMessage, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
        } else {
          Status = EFI_DEVICE_ERROR;
        }
      } else {
        Status = EFI_INVALID_PARAMETER;
      }
    } else {
      Status = EFI_INVALID_PARAMETER;
    }
  }
  IDS_HDT_CONSOLE (MAIN_FLOW, "SmuV10LaunchThread Exit\n");
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 *   Reads a fuse value based on an enumerated list of fuse "names"
 *
 *
 * @param[in]   This               A pointer to the DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL instance.
 * @param[in]   FuseName           The "name" of the fuse from an enumerated list of fuses supported by this function
 * @param[out]  FuseValue          Pointer to the value of the fuse
 *
 * @retval      EFI_SUCCESS
 *
 */
EFI_STATUS
EFIAPI
AmdSmuReadFuseByName (
  IN       DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *This,
  IN       UINT32                              InstanceId,
  IN       UINTN                               FuseName,
  IN OUT   UINTN                               *BufferSize,
     OUT   UINT8                               *FuseValue
  )
{
  /// If we ever need the DXE version of this code we may want to
  /// pull the PEI version of this function into a BASE library
  return EFI_UNSUPPORTED;
}

/*----------------------------------------------------------------------------------------*/
/**
 *   Reads a fuse value based on chain, start bit, and size
 *
 *
 * @param[in]   This               A pointer to the DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL instance.
 * @param[in]   FuseChain          The chain number of the fuse to read
 * @param[in]   FuseStartBit       The starting bit within the specified fuse chain of the fuse to read
 * @param[in]   FuseSize           The bitfield width of the fuse to read
 * @param[out]  FuseValue          Pointer to the value of the fuse
 *
 * @retval      EFI_SUCCESS
 *
 */
EFI_STATUS
EFIAPI
AmdSmuReadFuseByNumber (
  IN       DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *This,
  IN       UINT32                              FuseChain,
  IN       UINT32                              FuseStartBit,
  IN       UINT32                              FuseSize,
     OUT   UINT32                              *FuseValue
  )
{
  return EFI_UNSUPPORTED;
}

/*----------------------------------------------------------------------------------------*/
/**
 *   Executes a specific SMU service and returns the results
 *
 *
 * @param[in]   This               A pointer to the DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL instance.
 * @param[in]   InstanceId         The unique identifier of the NBIO instance associated with this socket/die
 * @param[in]   ServiceRequest     The service request identifier
 * @param[in]   InputParameters    Pointer to an array of service request arguments (for CZ, UINT32[6])
 * @param[out]  ReturnValues       Pointer to an array of service request response values (UINT32[6])
 *
 * @retval      EFI_SUCCESS
 *
 */
EFI_STATUS
AmdSmuServiceRequest (
  IN       DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *This,
  IN       UINT32                              InstanceId,
  IN       UINT32                              ServiceRequest,
  IN       UINT32                              *InputParameters,
     OUT   UINT32                              *ReturnValues
  )
{
  GNB_HANDLE                      *GnbHandle;
  EFI_STATUS                      Status;
  UINT32                          SmuArg[6];
  UINT32                          SmuResult;

  IDS_HDT_CONSOLE (MAIN_FLOW, "SmuServiceRequest Dxe Entry\n");
  Status = SmuGetGnbHandle (InstanceId, &GnbHandle);
  if (Status == EFI_SUCCESS) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "GnbHandle Found\n");
    LibAmdMemCopy (SmuArg, InputParameters, 24, (AMD_CONFIG_PARAMS *) NULL);
    SmuResult = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (GnbHandle), ServiceRequest, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
    if (SmuResult == 1) {
      LibAmdMemCopy (ReturnValues, SmuArg, 24, (AMD_CONFIG_PARAMS *) NULL);
    } else {
      Status = EFI_INVALID_PARAMETER;
      IDS_HDT_CONSOLE (MAIN_FLOW, "InstandId not found!!\n");
      ASSERT (FALSE);       // Unsupported SMU service request
    }
  }
    IDS_HDT_CONSOLE (MAIN_FLOW, "SmuServiceRequest Exit Status = %d\n", Status);

  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 *   Reads a 32-bit register from SMU register space
 *
 *
 * @param[in]  This               A pointer to the DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL instance.
 * @param[in]  InstanceId         The unique identifier of the NBIO instance associated with this socket/die
 * @param[in]  RegisterIndex      The index of the register to be read
 * @param[in]  RegisterValue      Pointer to a UINT32 holding the value to write to the register
 *
 */
EFI_STATUS
AmdSmuRegisterRead (
  IN       DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *This,
  IN       UINT32                              InstanceId,
  IN       UINT32                              RegisterIndex,
     OUT   UINT32                              *RegisterValue
  )
{
  GNB_HANDLE                      *GnbHandle;
  EFI_STATUS                      Status;

  Status = SmuGetGnbHandle (InstanceId, &GnbHandle);
  if (Status == EFI_SUCCESS) {
    Status = NbioRegisterRead (GnbHandle, TYPE_SMN, RegisterIndex, RegisterValue, 0);
  }
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Writes a 32-bit register in SMU register space
 *
 *
 *
 * @param[in]  This               A pointer to the DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL instance.
 * @param[in]  InstanceId         The unique identifier of the NBIO instance associated with this socket/die
 * @param[in]  RegisterIndex      The index of the register to be read
 * @param[in]  RegisterValue      Pointer to a UINT32 holding the value to write to the register
 *
 */
EFI_STATUS
AmdSmuRegisterWrite (
  IN       DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *This,
  IN       UINT32                              InstanceId,
  IN       UINT32                              RegisterIndex,
  IN       UINT32                              *RegisterValue
  )
{
  GNB_HANDLE                      *GnbHandle;
  EFI_STATUS                      Status;

  Status = SmuGetGnbHandle (InstanceId, &GnbHandle);
  if (Status == EFI_SUCCESS) {
    Status = NbioRegisterWrite (GnbHandle, TYPE_SMN, RegisterIndex, RegisterValue, GNB_REG_ACC_FLAG_S3SAVE);
  }
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Read/Modify/Write a 32-bit register from SMU register space
 *
 *
 *
 * @param[in]  This               A pointer to the DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL instance.
 * @param[in]  InstanceId         The unique identifier of the NBIO instance associated with this socket/die
 * @param[in]  RegisterIndex      The index of the register to be read
 * @param[in]  RegisterANDValue   UINT32 holding the value to be "ANDed" with the data read from the register (i.e. mask of data that will not be modified)
 * @param[in]  RegisterORValue    UINT32 holding the value to be "ORed" with the data read from the register (i.e. data bits to be "set" by this function)
 *
 */
EFI_STATUS
AmdSmuRegisterRMW (
  IN       DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *This,
  IN       UINT32                              InstanceId,
  IN       UINT32                              RegisterIndex,
  IN       UINT32                              RegisterANDValue,
  IN       UINT32                              RegisterORValue
  )
{
  GNB_HANDLE                      *GnbHandle;
  EFI_STATUS                      Status;
  UINT32                          RegisterValue;

  Status = SmuGetGnbHandle (InstanceId, &GnbHandle);
  if (Status == EFI_SUCCESS) {
    Status = NbioRegisterRead (GnbHandle, TYPE_SMN, RegisterIndex, &RegisterValue, 0);
    RegisterValue = (RegisterValue & RegisterANDValue) | RegisterORValue;
    Status = NbioRegisterWrite (GnbHandle, TYPE_SMN, RegisterIndex, &RegisterValue, GNB_REG_ACC_FLAG_S3SAVE);
  }
  return Status;
}

/*----------------------------------------------------------------------------------------
/**
 * Returns the brand string read from SMN space.
 *
 * @param[in]  This               A pointer to the DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL instance.
 * @param[in]  InstanceId         The unique identifier of the NBIO instance associated with this socket/die
 * @param[in]  BrandStringLength  Number of characters to be read.  This value does NOT have to be a multiple of 4.
                                  NBIO driver code will be responsible for alignment, endianness, and string length.
 * @param[in]  BrandString        Pointer to a CHAR array to store the brand string.
 *
**/
EFI_STATUS
AmdSmuReadBrandString (
  IN       DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *This,
  IN       UINT32                              InstanceId,
  IN       UINT32                              BrandStringLength,
     OUT   UINT8                               *BrandString
  )
{
  GNB_HANDLE                      *GnbHandle;
  EFI_STATUS                      Status;
  UINT32                          SmuArg[6];
  UINT32                          SmuResult;
  UINT8                           *StringPtr;
  UINT32                          StringCount;
  UINT32                          ByteCount;
  UINT32                          Iteration;

  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdSmuReadBrandString Entry\n");
  Status = SmuGetGnbHandle (InstanceId, &GnbHandle);
  if (Status == EFI_SUCCESS) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "GnbHandle Found\n");
    StringCount = BrandStringLength;
    StringPtr = BrandString;
    Iteration = 0;
    while (StringCount != 0) {
      NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
      SmuArg[0] = Iteration++;
      SmuResult = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (GnbHandle), BIOSSMC_MSG_GetNameString, SmuArg, 0);
      if (SmuResult == 1) {
        ByteCount = (StringCount < 4) ? StringCount : 4;
        LibAmdMemCopy (StringPtr, SmuArg, StringCount, (AMD_CONFIG_PARAMS *) NULL);
        StringPtr += ByteCount;
        StringCount -= ByteCount;
      } else {
        Status = EFI_INVALID_PARAMETER;
        IDS_HDT_CONSOLE (MAIN_FLOW, "SmuRequestFail!!\n");
        break;
      }
    }
  }
  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdSmuReadBrandString Exit Status = %d\n", Status);
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Returns the CAC weights read from SMU
 *
 * @param[in]  This                    A pointer to the PEI_AMD_NBIO_SMU_SERVICES_PPI instance.
 * @param[in]  MaxNumWeights           The number of values to read from the SMU (defines the maximum size of ApmWeights return data buffer)
 * @param[Out] ApmWeights              Pointer to return data buffer
 *
 * @retval     EFI_SUCCESS             ApmWeights contains the CaC weights read from SMU
 * @retval     EFI_INVALID_PARAMETER   One of the input parameters was invalid
 *                                     InstanceId did not reference a valid NBIO instance
 * @retval     EFI_BUFFER_TOO_SMALL    The number of weights available exceeds MaxNumWeights
 * @retval     EFI_UNSUPPORTED         This function is not supported by this version of the driver
 */
EFI_STATUS
AmdSmuReadCacWeights (
  IN       DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *This,
  IN       UINT32                              MaxNumWeights,
     OUT   UINT64                              *ApmWeights
  )
{
  EFI_STATUS                           Status;
  PCIe_PLATFORM_CONFIG                 *Pcie;
  PCIe_PLATFORM_CONFIG                 *PcieFromHob;
  GNB_HANDLE                           *NbioHandle;
  GNB_HANDLE                           *GnbHandle;
  UINT8                                WeightIndex;
  UINT32                               SmuArg[6];
  UINT32                               RxSmuMessageResponse[6];
  UINT32                               SmuResult;
  UINT64                               CacWeights[MAX_CAC_WEIGHT_NUM];

  IDS_HDT_CONSOLE (MAIN_FLOW, "Smu Cac Entry\n");

  PcieFromHob = NULL;
  LibAmdMemFill ((VOID*)CacWeights, 0x00, MAX_CAC_WEIGHT_NUM * (sizeof (UINT64)), NULL);
  SmuDxeInitialize (&PcieFromHob);
  Pcie = PcieFromHob;
  NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
  NbioHandle = NbioGetHandle (Pcie);
  Status = SmuGetGnbHandle (0, &GnbHandle);

  for (WeightIndex = 0; WeightIndex < MaxNumWeights; WeightIndex++) {

    NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
    SmuArg[0] = WeightIndex;

    SmuResult = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (GnbHandle), SMC_MSG_ReadCoreCacWeightRegister, SmuArg, 0);

    if (SmuResult == 1) {
      LibAmdMemCopy (RxSmuMessageResponse, SmuArg, 24, (AMD_CONFIG_PARAMS *) NULL);
      CacWeights[WeightIndex] = RxSmuMessageResponse[0];
      IDS_HDT_CONSOLE (MAIN_FLOW, "CacWeightsOrg[%d] = %x\n", WeightIndex, CacWeights[0]);
      IDS_HDT_CONSOLE (MAIN_FLOW, "RxSmuMessageResponse[0] = %x\n", RxSmuMessageResponse[0]);
      IDS_HDT_CONSOLE (MAIN_FLOW, "RxSmuMessageResponse[1] = %x\n", RxSmuMessageResponse[1]);
      CacWeights[WeightIndex] = (CacWeights[WeightIndex] << 32) | RxSmuMessageResponse[1];
      IDS_HDT_CONSOLE (MAIN_FLOW, "CacWeights[%d] = %llx\n", WeightIndex, CacWeights[WeightIndex]);
      LibAmdMemCopy (ApmWeights, CacWeights, MaxNumWeights * 8, (AMD_CONFIG_PARAMS *) NULL);
      IDS_HDT_CONSOLE (MAIN_FLOW, "ApmWeights[0] = %llx\n", ApmWeights[0]);
    } else {
      Status = EFI_INVALID_PARAMETER;
      IDS_HDT_CONSOLE (MAIN_FLOW, "InstandId not found!!\n");
      ASSERT (FALSE);       // Unsupported SMU service request
    }
  }
  IDS_HDT_CONSOLE (MAIN_FLOW, "mCacWeightsMod[%d] = %llx\n", WeightIndex, CacWeights[WeightIndex]);

  IDS_HDT_CONSOLE (MAIN_FLOW, "Smu Cac Exit Status = %d\n", Status);
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Returns the throttle thresholds read from SMU
 *
 * @param[in]  This              A pointer to the DXE_AMD_NBIO_SMU_SERVICES_PPI instance.
 * @param[Out] Thresholds        Pointer to return data buffer
 *
 * @retval     EFI_SUCCESS       ApmWeights contains the throttle thresholds read from SMU
 * @retval     EFI_UNSUPPORTED   This function is not supported by this version of the driver
 */
EFI_STATUS
AmdSmuReadThrottleThresholds (
  IN       DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *This,
     OUT   UINT32                              *Thresholds
  )
{
  return EFI_UNSUPPORTED;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Reads a fuse value based on an enumerated list of fuse "names"
 *
 *
 *
 * @param[in]  InstanceId              The unique identifier of the NBIO instance associated with this socket/die
 * @param[out] MyHandle                Pointer to GNB_HANDLE* to return GNB_HANDLE of this InstanceId
 *
 * @retval     EFI_SUCCESS             The fuse was located and the FuseValue returned is valid
 * @retval     EFI_INVALID_PARAMETER   InstanceId did not reference a valid NBIO instance
 */
EFI_STATUS
SmuGetGnbHandle (
  IN       UINT32                         InstanceId,
     OUT   GNB_HANDLE                     **MyHandle
  )
{
  EFI_STATUS                           Status;
  GNB_PCIE_INFORMATION_DATA_HOB        *GnbPcieInformationDataHob;
  PCIe_PLATFORM_CONFIG                 *Pcie;
  BOOLEAN                              InstanceFound;
  GNB_HANDLE                           *GnbHandle;

  //
  // Get information data from HOB.
  //
  Status = EfiGetSystemConfigurationTable (&gEfiHobListGuid, &GnbPcieInformationDataHob);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  GnbPcieInformationDataHob = GetNextGuidHob (&gGnbPcieHobInfoGuid, GnbPcieInformationDataHob);
  if (GnbPcieInformationDataHob == NULL) {
    return EFI_NOT_FOUND;
  }
  Pcie = &(GnbPcieInformationDataHob->PciePlatformConfigHob);
  GnbHandle = NbioGetHandle (Pcie);

  InstanceFound = FALSE;
  Status = EFI_INVALID_PARAMETER;
  while ((InstanceFound == FALSE) && (GnbHandle != NULL)) {
    if (GnbHandle->InstanceId == InstanceId) {
      InstanceFound = TRUE;
      Status = EFI_SUCCESS;
      IDS_HDT_CONSOLE (MAIN_FLOW, "InstanceId found!!\n");
    } else {
      GnbHandle = GnbGetNextHandle (GnbHandle);
    }
  }
  *MyHandle = GnbHandle;

  return Status;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Initilaize data for SMU Dxe phase.
 *
 *
 *
 * @param[out]  Pcie                    Get Pcie data from hob.
 *
 * @retval     EFI_SUCCESS
 */
EFI_STATUS
SmuDxeInitialize (
  OUT PCIe_PLATFORM_CONFIG           **Pcie
  )
{
  EFI_STATUS                           Status;
  GNB_PCIE_INFORMATION_DATA_HOB        *GnbPcieInformationDataHob;

  // Correcting Pcie information from Hob

  //
  // Get information data from HOB.
  //
  Status = EfiGetSystemConfigurationTable (&gEfiHobListGuid, &GnbPcieInformationDataHob);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  GnbPcieInformationDataHob = GetNextGuidHob (&gGnbPcieHobInfoGuid, GnbPcieInformationDataHob);
  if (GnbPcieInformationDataHob == NULL) {
    return EFI_NOT_FOUND;
  }
  *Pcie = &(GnbPcieInformationDataHob->PciePlatformConfigHob);

  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Dump Smu Feature Control.
 *
 *
 *
 * @param[out]  Pcie                    Get Pcie data from hob.
 *
 */
VOID
DumpSmuFeatureControl (
  IN       UINT32                         EnableFeatures,
  IN       UINT32                         EnableFeaturesExt
  )
{
  IDS_HDT_CONSOLE (GNB_TRACE, "Smu Feature Control(0x%x):\n", EnableFeatures);
  IDS_HDT_CONSOLE (GNB_TRACE, "Smu FeaturesExt Control(0x%x):\n", EnableFeaturesExt);
}

/*----------------------------------------------------------------------------------------*/
/**
 * Dump Fan Policy.
 *
 *
 *
 * @param[in]  PPTable
 *
 */
VOID
DumpFanPolicyTable (
  IN       PPTable_t          *PPTable
  )
{
  IDS_HDT_CONSOLE (GNB_TRACE, "Fan Policy:\n");
  IDS_HDT_CONSOLE (GNB_TRACE, "  ForceFanPwmEn = %d\n", PPTable->ForceFanPwmEn);
  IDS_HDT_CONSOLE (GNB_TRACE, "  ForceFanPwm = %d\n", PPTable->ForceFanPwm);
  IDS_HDT_CONSOLE (GNB_TRACE, "  FanTable_Override = %d\n", PPTable->FanTable_Override);
  IDS_HDT_CONSOLE (GNB_TRACE, "  FanTable_TempLow = %d\n", PPTable->FanTable_TempLow);
  IDS_HDT_CONSOLE (GNB_TRACE, "  FanTable_TempMed = %d\n", PPTable->FanTable_TempMed);
  IDS_HDT_CONSOLE (GNB_TRACE, "  FanTable_TempHigh = %d\n", PPTable->FanTable_TempHigh);
  IDS_HDT_CONSOLE (GNB_TRACE, "  FanTable_TempCritical = %d\n", PPTable->FanTable_TempCritical);
  IDS_HDT_CONSOLE (GNB_TRACE, "  FanTable_PwmLow = %d\n", PPTable->FanTable_PwmLow);
  IDS_HDT_CONSOLE (GNB_TRACE, "  FanTable_PwmMed = %d\n", PPTable->FanTable_PwmMed);
  IDS_HDT_CONSOLE (GNB_TRACE, "  FanTable_PwmHigh = %d\n", PPTable->FanTable_PwmHigh);
  IDS_HDT_CONSOLE (GNB_TRACE, "  FanTable_Hysteresis = %d\n", PPTable->FanTable_Hysteresis);
  IDS_HDT_CONSOLE (GNB_TRACE, "  FanTable_PwmFreq = %d\n", PPTable->FanTable_PwmFreq);
  IDS_HDT_CONSOLE (GNB_TRACE, "  FanTable_Polarity = %d\n", PPTable->FanTable_Polarity);
}
//<Embedded_Override_Start>
/*----------------------------------------------------------------------------------------*/
/**
 * 0 = RV1 single source
 * 1 = RV2 single source
 * 2 = RV1  B4 Dual source
 * 3 = RV2 dual source
 * 
 * FALSE - Rv2
 * TRUE - Rv
 */
BOOLEAN
CheckRvOpn (
  )
{
  UINT32  TempData32;

  TempData32 = (PcdGet32 (PcdGetRVFamilyOPN) >> 30) & 0x3;

  if ((TempData32 == RV1_SINGLE_SOURCE) || (TempData32 == RV1_B4_DUAL_SOURCE)) {
    return TRUE;
  } 
  return FALSE;
}
//<Embedded_Override_End>
/*---------------------------------------------------------------------------------------*/
/**
 * Check RV OPN number
 *
 * @retval    TRUE    This is RV B4 part
 *            FALSE   This is not RV B4 part
 *
 */
BOOLEAN
CheckRvOpnB4 (
  )
{
  UINT32              RegisterData;
  UINT32              TempData32;

  SmnRegisterRead (0, SMUFUSEx000005C0_ADDRESS, &RegisterData);
  TempData32 = (RegisterData >> 30) & 0x3;
  if (TempData32 == 2) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "RV1 B4 \n");
    return TRUE;
  } else if (TempData32 == 3) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "RV2 B4 \n");
    PcdSetBool (PcdPciePhyClkCntrlEnable, 0);  // RV2 B4 workaround.
    return TRUE;
  }

  // OPN = ZM2300C4T2OFB
  SmnRegisterRead (0, SMUFUSEx0000059C_ADDRESS, &RegisterData);
  if (((RegisterData >> 16) & 0xFFFF) == 0xA6DA) {
    SmnRegisterRead (0, SMUFUSEx000005A0_ADDRESS, &RegisterData);
    if (RegisterData  == 0x0D83066C) {
      SmnRegisterRead (0, SMUFUSEx000005A4_ADDRESS, &RegisterData);
      if (RegisterData  == 0xD3D95469) {
        SmnRegisterRead (0, SMUFUSEx000005A8_ADDRESS, &RegisterData);
        if ((RegisterData & 0x7FF) == 0x428) {
          IDS_HDT_CONSOLE (MAIN_FLOW, "Special RV1 B4\n");
          return TRUE;
        }
      }
    }
  }

  return FALSE;
}
/*---------------------------------------------------------------------------------------*/
/**
 * Check RV CPU Revision
 *
 * @retval    3    This is RV R3 part
 *            5    This is RV R5 part
 *            7    This is RV R7 part
 *            FALSE   This is not RV part
 *
 */
UINT8
CheckRvCpuRevision (
  )
{
  CPUID_DATA             CpuId;

  // Silicon behavior
  AsmCpuid (
    0x80000002,
    &(CpuId.EAX_Reg),
    &(CpuId.EBX_Reg),
    &(CpuId.ECX_Reg),
    &(CpuId.EDX_Reg)
    );

  //Check CPU string is "Ryzen 7 "
  if((CpuId.ECX_Reg == 0x2037206E) && (CpuId.EBX_Reg == 0x657A7952)){
    return 7;
  }

  //Check CPU string is "Ryzen 5 "
  if((CpuId.ECX_Reg == 0x2035206E) && (CpuId.EBX_Reg == 0x657A7952)){
    return 5;

  }
  //Check CPU string is "Ryzen 3 "
  if((CpuId.ECX_Reg == 0x2033206E) && (CpuId.EBX_Reg == 0x657A7952)){
    return 3;
  }

  return FALSE;

}
/**
 *---------------------------------------------------------------------------------------
 *  CallbackAfterSmuInitComplete
 *
 *  Description:
 *     notification event handler after gAmdNbioSmuInitCompleteProtocolGuid ready
 *  Parameters:
 *    @param[in]     Event      Event whose notification function is being invoked.
 *    @param[in]     *Context   Pointer to the notification function's context.
 *
 *---------------------------------------------------------------------------------------
 **/
VOID
EFIAPI
CallbackAfterSmuInitComplete (
  IN      EFI_EVENT  Event,
  IN      VOID       *Context
  )
{
  EFI_STATUS                              Status;
  PCIe_PLATFORM_CONFIG                    *PcieFromHob;
  PCIe_PLATFORM_CONFIG                    *Pcie;
  GNB_HANDLE                              *NbioHandle;
  UINT32                                  SmuArg[6];
  DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL      *NbioSmuServiceProtocol;
  DXE_AMD_NBIO_SMU_INIT_COMPLETE_PROTOCOL *NbioSmuInitCompleteProtocol;

  Status = gBS->LocateProtocol (
                  &gAmdNbioSmuInitCompleteProtocolGuid,
                  NULL,
                  &NbioSmuInitCompleteProtocol
                  );
  if (EFI_ERROR (Status)) {
    return;
  }

  PcieFromHob = NULL;
  SmuDxeInitialize (&PcieFromHob);
  Pcie = PcieFromHob;

  Status = gBS->LocateProtocol (
                  &gAmdNbioSmuServicesProtocolGuid,
                  NULL,
                  &NbioSmuServiceProtocol
                  );
  if (!EFI_ERROR (Status)) {
    NbioHandle = NbioGetHandle (Pcie);
    while (NbioHandle != NULL) {
      NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
      SmuArg[0] = (UINT32) PcdGet8 (PcdMocGfxCoreVid);
      SmuArg[0] =  (SmuArg[0] << 16) | PcdGet16(PcdMocGfxClockFrequency);
      if (SmuArg[0] != 0) {
        Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetGfxclkOverdriveByFreqVid, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
      }

    if (PcdGet16 (PcdSoftMaxCclk) != 0) {
      NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
      SmuArg[0] = PcdGet16 (PcdSoftMaxCclk);
      SmuArg[0] |= 0xFFFF0000;
      Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetSoftMaxCCLK, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
    }
    if (PcdGet16 (PcdSoftMinCclk) != 0) {
      NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
      SmuArg[0] = PcdGet16 (PcdSoftMinCclk);
      SmuArg[0] |= 0xFFFF0000;
      Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetSoftMinCCLK, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
    }

      NbioHandle = GnbGetNextHandle (NbioHandle);
    }
  }

  //
  // Close event, so it will not be invoked again.
  //
  gBS->CloseEvent (Event);
}

/**
 *---------------------------------------------------------------------------------------
 *  SetSmuFeaturePolicy
 *
 *  Description:
 *     To decide the final SMU feature bit
 *  Parameters:
 *    @param[in]     LogicalId     To decide what CPU Family it is.
 *    @param[in]     PackageType   To decide what CPU Socket it is.
 *
 *---------------------------------------------------------------------------------------
 **/
VOID
EFIAPI
SetSmuFeaturePolicy (
  IN       SOC_LOGICAL_ID              LogicalId,
  IN       UINT32                      PackageType
  )
{
  BOOLEAN                              IsPCO;
  BOOLEAN                              IsRv2;
  //<Embedded_Override_Start>
  BOOLEAN                              IsRv1;
  UINT32                               RegisterData;
  UINT32                               Value;
  
  IsRv2 = FALSE;
  IsPCO = FALSE;
  IsRv1 = FALSE;
  
  // Read OPN_SPARE 
  SmnRegisterRead (0, SMUFUSEx000005C0_ADDRESS, &RegisterData);
  IDS_HDT_CONSOLE (MAIN_FLOW, "OPN_SPARE: %x \n", RegisterData);

  // Get 30 & 31 Bits value of OPN_SPARE 
  Value = (RegisterData >> 30) & 0x3;
  IDS_HDT_CONSOLE (MAIN_FLOW, "Value: %x \n", Value);
  

  // The function CheckRvOpnB4 () will specify whether B4 OPN or not.
  // It will not identify its RV2 or RV1 part.So, removed the function call. 
  
  IDS_HDT_CONSOLE (MAIN_FLOW, "Family: %x \n", LogicalId.Family);
  
  // Note: The below logic applicable for embedded platforms 
  if ((LogicalId.Family & AMD_FAMILY_RV) != 0) {
    // Check whether RV OPN
    IsRv1 = TRUE;
    IDS_HDT_CONSOLE (MAIN_FLOW, "RV1 Source \n");
  }else if ((LogicalId.Family & AMD_FAMILY_RV2) != 0) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "RV2 Single Source \n");
    PcdSetBool (PcdPciePhyClkCntrlEnable, 0);  // RV2 single source workaround.
    IsRv2 = TRUE;
  } else if (((LogicalId.Family & AMD_FAMILY_PIC) != 0)) { // ( PCO OPN_SPARE - 00xxxxx / Dual Source RV2 OPN_SPARE - 11xxxxx )
    if (Value == 0x3) {
    PcdSetBool (PcdPciePhyClkCntrlEnable, 0);
      IDS_HDT_CONSOLE (MAIN_FLOW, "( PCO ) RV2 Dual Source \n");
    } else if (Value == 0x0) {
      IDS_HDT_CONSOLE (MAIN_FLOW, " Pure PCO\n");
    }
    IsPCO = TRUE;
  }
  //<Embedded_Override_End>
  IDS_HDT_CONSOLE (MAIN_FLOW, "IsRv2 = %d\n", IsRv2);
  IDS_HDT_CONSOLE (MAIN_FLOW, "PackageType = %d\n", PackageType);

  if ((1 << RV_SOCKET_AM4) == PackageType) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "Setting PcdSmuFeatureControlDefines to 0x%x : 0x%x\n", (UINT32) AM4_SMU_FEATURES_ENABLE_EXT_DEFAULT, (UINT32) AM4_SMU_FEATURES_ENABLE_DEFAULT);
    PcdSet32 (PcdSmuFeatureControlDefines, (UINT32) AM4_SMU_FEATURES_ENABLE_DEFAULT);
    PcdSet32 (PcdSmuFeatureControlDefinesExt, (UINT32) AM4_SMU_FEATURES_ENABLE_EXT_DEFAULT);
    if (PcdGet8 (PcdAmdPowerSupplyIdleControl) == 0x01) {
      PcdSet32 (PcdSmuFeatureControlDefinesExt, PcdGet32 (PcdSmuFeatureControlDefinesExt) | (UINT32) (1 << (FEATURE_CPUOFF_BIT % 32)));
    } else {
      PcdSet32 (PcdSmuFeatureControlDefinesExt, PcdGet32 (PcdSmuFeatureControlDefinesExt) & ~((UINT32) (1 << (FEATURE_CPUOFF_BIT % 32))));
    }
    //<Embedded_Override_Start>
  } else if(IsRv1) { 
    //<Embedded_Override_End>
    IDS_HDT_CONSOLE (MAIN_FLOW, "Setting PcdSmuFeatureControlDefines to 0x%x : 0x%x\n", (UINT32) SMU_FEATURES_ENABLE_EXT_DEFAULT, (UINT32) SMU_FEATURES_ENABLE_DEFAULT);
    PcdSet32 (PcdSmuFeatureControlDefines, (UINT32) SMU_FEATURES_ENABLE_DEFAULT);
    PcdSet32 (PcdSmuFeatureControlDefinesExt, (UINT32) SMU_FEATURES_ENABLE_EXT_DEFAULT);
    //<Embedded_Override_Start>
    //Disable the STAPM
    PcdSet32 (PcdSmuFeatureControlDefinesExt, PcdGet32 (PcdSmuFeatureControlDefinesExt) & ~((UINT32) (1 << (FEATURE_STAPM_BIT % 32))));
    IDS_HDT_CONSOLE (MAIN_FLOW, "Embedded RV1: STAPM disable\n");
    //<Embedded_Override_End>
  }
  //
  // RV2 table
  //
  if (IsRv2 == TRUE) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "Setting RV2 PcdSmuFeatureControlDefines to 0x%x : 0x%x\n", (UINT32) RV2_SMU_FEATURES_ENABLE_EXT_DEFAULT, (UINT32) RV2_SMU_FEATURES_ENABLE_DEFAULT);
    PcdSet32 (PcdSmuFeatureControlDefines, (UINT32) RV2_SMU_FEATURES_ENABLE_DEFAULT);
    PcdSet32 (PcdSmuFeatureControlDefinesExt, (UINT32) RV2_SMU_FEATURES_ENABLE_EXT_DEFAULT);
    if (PcdGet8 (PcdS0i2Enable) == 0x1) {
      PcdSet32 (PcdSmuFeatureControlDefines, PcdGet32 (PcdSmuFeatureControlDefines) | (UINT32) (1 << (FEATURE_S0i2_BIT)));
    } else {
      PcdSet32 (PcdSmuFeatureControlDefines, PcdGet32 (PcdSmuFeatureControlDefines) & ~((UINT32) (1 << (FEATURE_S0i2_BIT))));
    }

    if (PcdGet8 (PcdS0i3Enable) == 0x1) {
      PcdSet32 (PcdSmuFeatureControlDefinesExt, PcdGet32 (PcdSmuFeatureControlDefinesExt) | (UINT32) (1 << (FEATURE_S0i3_EN_BIT % 32)));
    } else {
      PcdSet32 (PcdSmuFeatureControlDefinesExt, PcdGet32 (PcdSmuFeatureControlDefinesExt) & ~((UINT32) (1 << (FEATURE_S0i3_EN_BIT % 32))));
    }

    //<Embedded_Override_Start>
    //Disable the STAPM
    PcdSet32 (PcdSmuFeatureControlDefinesExt, PcdGet32 (PcdSmuFeatureControlDefinesExt) & ~((UINT32) (1 << (FEATURE_STAPM_BIT % 32))));
    IDS_HDT_CONSOLE (MAIN_FLOW, "Embedded RV2: STAPM disable\n");
    //Disable FEATURE_DS_SHUBCLK_BIT
    PcdSet32 (PcdSmuFeatureControlDefines, PcdGet32 (PcdSmuFeatureControlDefines) & ~((UINT32) (1 << ( FEATURE_DS_SHUBCLK_BIT % 32))));
    IDS_HDT_CONSOLE (MAIN_FLOW, "Embedded RV2: FEATURE_DS_SHUBCLK_BIT disable\n");
    //<Embedded_Override_End>
  }
  //
  // PCO table
  //
  if (IsPCO == TRUE) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "Setting PCO PcdSmuFeatureControlDefines to 0x%x : 0x%x\n", (UINT32) PCO_SMU_FEATURES_ENABLE_EXT_DEFAULT, (UINT32) PCO_SMU_FEATURES_ENABLE_DEFAULT);
    PcdSet32 (PcdSmuFeatureControlDefines, (UINT32) PCO_SMU_FEATURES_ENABLE_DEFAULT);
    PcdSet32 (PcdSmuFeatureControlDefinesExt, (UINT32) PCO_SMU_FEATURES_ENABLE_EXT_DEFAULT);

    //  For PCO, be able control S0i2/S0i3 from platform BIOS.
    if (PcdGet8 (PcdS0i2Enable) == 0x1) {
      PcdSet32 (PcdSmuFeatureControlDefines, PcdGet32 (PcdSmuFeatureControlDefines) | (UINT32) (1 << (FEATURE_S0i2_BIT)));
    } else {
      PcdSet32 (PcdSmuFeatureControlDefines, PcdGet32 (PcdSmuFeatureControlDefines) & ~((UINT32) (1 << (FEATURE_S0i2_BIT))));
    }

    if (PcdGet8 (PcdS0i3Enable) == 0x1) {
      PcdSet32 (PcdSmuFeatureControlDefinesExt, PcdGet32 (PcdSmuFeatureControlDefinesExt) | (UINT32) (1 << (FEATURE_S0i3_EN_BIT % 32)));
    } else {
      PcdSet32 (PcdSmuFeatureControlDefinesExt, PcdGet32 (PcdSmuFeatureControlDefinesExt) & ~((UINT32) (1 << (FEATURE_S0i3_EN_BIT % 32))));
    }

    //<Embedded_Override_Start>
    //Disable the STAPM
    PcdSet32 (PcdSmuFeatureControlDefinesExt, PcdGet32 (PcdSmuFeatureControlDefinesExt) & ~((UINT32) (1 << (FEATURE_STAPM_BIT % 32))));
    IDS_HDT_CONSOLE (MAIN_FLOW, "Embedded PCO: STAPM disable\n");

    //Disable FEATURE_DS_SHUBCLK_BIT
    PcdSet32 (PcdSmuFeatureControlDefines, PcdGet32 (PcdSmuFeatureControlDefines) & ~((UINT32) (1 << ( FEATURE_DS_SHUBCLK_BIT % 32))));
    IDS_HDT_CONSOLE (MAIN_FLOW, "Embedded PCO: FEATURE_DS_SHUBCLK_BIT disable\n");
    //<Embedded_Override_End>
  }

}


/**
 *---------------------------------------------------------------------------------------
 *  CallbackAfterPCIeEnumerateComplete
 *
 *  Description:
 *     notification event handler after gAmdPCIeEnumerateProtocolGuid ready
 *  Parameters:
 *    @param[in]     Event      Event whose notification function is being invoked.
 *    @param[in]     *Context   Pointer to the notification function's context.
 *
 *---------------------------------------------------------------------------------------
 **/
VOID
EFIAPI
CallbackAfterPCIeEnumerateComplete (
  IN      EFI_EVENT  Event,
  IN      VOID       *Context
  )
{
  EFI_STATUS                              Status;
  PCIe_PLATFORM_CONFIG                    *PcieFromHob;
  PCIe_PLATFORM_CONFIG                    *Pcie;
  GNB_HANDLE                              *NbioHandle;
  UINT32                                  SmuArg[6];
  DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL      *NbioSmuServiceProtocol;
  VOID                                    *Interface;
  UINT16     Bus, Dev, Fun;
  UINT8      ClassCodeData;
  UINT8      SubClassCodeData;
  UINT8      SecondaryBusNumber;
  UINT8      NumberOfDevice;
  BOOLEAN    IsNvme = FALSE;

  Bus = 0;
  Dev = 0;
  Fun = 0;
  ClassCodeData = 0;
  SubClassCodeData = 0;
  SecondaryBusNumber = 0;
  NumberOfDevice = 0;
  IDS_HDT_CONSOLE (MAIN_FLOW, "CallbackAfterPCIeEnumerateComplete First notify\n");

  Status = gBS->LocateProtocol (
                  &gEfiPciEnumerationCompleteProtocolGuid,
                  NULL,
                  (VOID **)&Interface
                  );
  if (EFI_ERROR (Status)) {
    return;
  }
  IDS_HDT_CONSOLE (MAIN_FLOW, "Callback AfterPCIeEnumerateComplete Entry\n");

  PcieFromHob = NULL;
  SmuDxeInitialize (&PcieFromHob);
  Pcie = PcieFromHob;

  Status = gBS->LocateProtocol (
                  &gAmdNbioSmuServicesProtocolGuid,
                  NULL,
                  &NbioSmuServiceProtocol
                  );
  if (!EFI_ERROR (Status)) {
    NbioHandle = NbioGetHandle (Pcie);
    while (NbioHandle != NULL) {
      NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
      //
      // To check where is Deivce Bus,
      //
      for (Fun =1; Fun <= 7; Fun++) {
        Bus = 0;
        Dev = 1;

        GnbLibPciRead(
           MAKE_SBDFO (0, Bus, Dev, Fun, 0) | PCICFG_SPACE_SECONDARY_BUS_OFFSET,
           AccessWidth8,
           &SecondaryBusNumber,
           NULL
           );
        IDS_HDT_CONSOLE (NB_MISC, "SecondaryBusNumber 0x%x \n", SecondaryBusNumber);

        GnbLibPciRead(
           MAKE_SBDFO (0, SecondaryBusNumber, 0, 0, 0) | PCICFG_SPACE_Master_CLASS_CODE_OFFSET,
           AccessWidth8,
           &ClassCodeData,
           NULL
           );
        IDS_HDT_CONSOLE (NB_MISC, "ClassCodeData 0x%x \n", ClassCodeData);

        GnbLibPciRead(
            MAKE_SBDFO (0, SecondaryBusNumber, 0, 0, 0) | PCICFG_SPACE_SUB_CLASS_CODE_OFFSET,
            AccessWidth8,
            &SubClassCodeData,
            NULL
            );
        IDS_HDT_CONSOLE (NB_MISC, "SubClassCodeData 0x%x \n", SubClassCodeData);

        IsNvme = FALSE;
        // To check NVME device class code
        if (ClassCodeData == 0x1) {
          // To check device sub-class code
          if (SubClassCodeData == 0x8) {
            if (NumberOfDevice <= 5) {
              NumberOfDevice++;
              SmuArg[NumberOfDevice] = SecondaryBusNumber | (ClassCodeData << 16);
              IsNvme = TRUE;
            }
          }
        }

        // To check XHCI device class code
        if(IsNvme == FALSE) {
          if (ClassCodeData == 0xC) {
            // To check device sub-class code
            if (SubClassCodeData == 0x3) {
              if (NumberOfDevice <= 5) {
                NumberOfDevice++;
                SmuArg[NumberOfDevice] = SecondaryBusNumber | (ClassCodeData << 16);
              }
            }
          }
        }
      }

      SmuArg[0] = NumberOfDevice;
      IDS_HDT_CONSOLE (NB_MISC, "  SmuArg 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n", SmuArg[0], SmuArg[1], SmuArg[2], SmuArg[3], SmuArg[4], SmuArg[5]);
      Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetExternalPcieBuses, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);  //0x52

      if (PcdGetBool (PcdS0i3SetGenericPeRstEnable)) {
        NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
        SmuArg[0] = PcdGet32 (PcdS0i3SetGenericPeRstGpio0);
        SmuArg[1] = PcdGet32 (PcdS0i3SetGenericPeRstGpio1);
        IDS_HDT_CONSOLE (NB_MISC, "  SmuArg 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n", SmuArg[0], SmuArg[1], SmuArg[2], SmuArg[3], SmuArg[4], SmuArg[5]);
        Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetGenericPeRstGpioAddrOffset, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);  //0x56
      }
      NbioHandle = GnbGetNextHandle (NbioHandle);
    }
  }
  IDS_HDT_CONSOLE (MAIN_FLOW, "Callback AfterPCIeEnumerateComplete Exit\n");

  //
  // Close event, so it will not be invoked again.
  //
  gBS->CloseEvent (Event);
}


/**
 *---------------------------------------------------------------------------------------
 *  CallbackforS0i3Feature
 *
 *  Description:
 *     To setting register for S0i3 feature
 *
 *---------------------------------------------------------------------------------------
 **/
VOID
EFIAPI
CallbackforS0i3Feature (
  )
{


  GNB_HANDLE                           *NbioHandle;
  PCIe_PLATFORM_CONFIG                 *Pcie;
  PCIe_PLATFORM_CONFIG                 *PcieFromHob;
  UINT32                               IGPU_DID;

  IDS_HDT_CONSOLE (MAIN_FLOW, "CallbackforS0i3Feature Entry \n");
  IGPU_DID  = (UINT16) PcdGet32 (PcdGetRVFamilyOPN);
  PcieFromHob = NULL;


  SmuDxeInitialize (&PcieFromHob);
  Pcie = PcieFromHob;

  NbioHandle = NbioGetHandle (Pcie);
  while (NbioHandle != NULL) {
    if(IGPU_DID == 0x15D8) {
      IDS_HDT_CONSOLE (MAIN_FLOW, "CPU: PCO\n");
      NbioRegisterRMW (NbioHandle,
                       TYPE_SMN,
                       RCC_DEV1_EPF0_STRAP4_ADDRESS,
                       (UINT32) ~(RCC_STRAP_PME_SUPPORT_DEV1_F0_MASK),
                       0 << RCC_STRAP_PME_SUPPORT_DEV1_F0_OFFSET,
                       1);
      if (PcdGetBool (PcdIommuL1ClockGatingEnable)) {
        // S0i3 WA -- waiting for Driver update
        // IOMMU L1 clock gating
        // IOAGR
        NbioRegisterRMW (NbioHandle,
                         L1_CLKCNTRL_0_AGR_TYPE,
                         L1_CLKCNTRL_0_AGR_ADDRESS,
                         (UINT32) ~(IOMMUL1IOAGR_0CC_L1_CPSLV_CLKGATE_EN_MASK),
                         (0x0 << IOMMUL1IOAGR_0CC_L1_CPSLV_CLKGATE_EN_OFFSET),
                         1);
        // PCIE0
        NbioRegisterRMW (NbioHandle,
                         L1_CLKCNTRL_0_PCIE0_TYPE,
                         L1_CLKCNTRL_0_PCIE0_ADDRESS,
                         (UINT32) ~(IOMMUL1PCIE0_0CC_L1_CPSLV_CLKGATE_EN_MASK),
                         (0x0 << IOMMUL1PCIE0_0CC_L1_CPSLV_CLKGATE_EN_OFFSET),
                         1);
       }
    }
    NbioHandle = GnbGetNextHandle (NbioHandle);
  }

  IDS_HDT_CONSOLE (MAIN_FLOW, "CallbackforS0i3Feature Exit \n");
}
/* -----------------------------------------------------------------------------*/
/**
 *
 *  AmdNbioSmuV10DxeEntry
 *
 *  @param[in]  ImageHandle     EFI Image Handle for the DXE driver
 *  @param[in]  SystemTable     Pointer to the EFI system table
 *
 *  Description:
 *    SMUV10 Driver Entry.
 *
 *  @retval EFI_STATUS
 *
 */
EFI_STATUS
EFIAPI
AmdNbioSmuV10DxeEntry (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                           Status;
  EFI_HANDLE                           Handle;
  UINT32                               SmuArg[6];
  UINT32                               DramBufferSize;
  EFI_PHYSICAL_ADDRESS                 SmuDramBufferAddress;
  EFI_PHYSICAL_ADDRESS                 SetAgmLogDramAddress;
  PPTable_t                            *PPTable;
  GNB_HANDLE                           *NbioHandle;
  PCIe_PLATFORM_CONFIG                 *Pcie;
  PCIe_PLATFORM_CONFIG                 *PcieFromHob;
  VOID                                 *Registration;
  UINT32                               PackageType;
  UINT32                               Value32Upper;
  UINT32                               Value32Lower;
  CPUID_DATA                           CpuId;
  UINT8                                RvCpuRevision;
  AMD_SOC_LOGICAL_ID_PROTOCOL          *SocLogicalId;
  SOC_LOGICAL_ID                       LogicalId;
//<Embedded_Override_Start>  
  UINT32                               SmuArgs[6];
  DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL   *NbioSmuServiceProtocolPtr;
  UINT32 PowerLimit = 0;
  CHAR8 OPNNameString[10] = {0};
//<Embedded_Override_End>

  AGESA_TESTPOINT (TpNbioSmuV10DxeEntry, NULL);
  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdNbioSmuV10DxeEntry Entry\n");

  PcieFromHob = NULL;
  Handle = NULL;
  SetAgmLogDramAddress = 0xffffffff;
  RvCpuRevision = 0;

  Status = gBS->LocateProtocol (&gAmdSocLogicalIdProtocolGuid, NULL, (VOID **) &SocLogicalId);
  ASSERT (!EFI_ERROR (Status));
  SocLogicalId->GetLogicalIdOnCurrentCore (SocLogicalId, &LogicalId);
  PackageType = LibAmdGetPackageType ((AMD_CONFIG_PARAMS *) NULL);

  //
  // Assign SMU feature policy
  //
  SetSmuFeaturePolicy (LogicalId, PackageType);

  //
  // Allocate DRAM to PPtable, System Topology
  //
  Status = gBS->AllocatePool (
                  EfiRuntimeServicesData,
                  sizeof (PPTable_t),
                  &PPTable
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //Zero Pool
  gBS->SetMem (PPTable, sizeof (PPTable_t), 0);
  ////// Copy default setting to Pptable
  gBS->CopyMem (PPTable, &PPTableDefault, sizeof (PPTable_t));
  PPTable->Version= SMU10_BIOS_IF_VERSION;
  PPTable->SYSTEM_CONFIG = PcdGet8 (PcdCfgSystemConfiguration);
  PPTable->Telemetry_VddcrVddSlope = PcdGet32 (PcdTelemetry_VddcrVddfull_Scale_Current);
  PPTable->Telemetry_VddcrVddSlope2 = PcdGet32 (PcdTelemetryVddcrVddfullScale2Current);
  PPTable->Telemetry_VddcrVddSlope3 = PcdGet32 (PcdTelemetryVddcrVddfullScale3Current);
  PPTable->Telemetry_VddcrVddSlope4 = PcdGet32 (PcdTelemetryVddcrVddfullScale4Current);
  PPTable->Telemetry_VddcrVddSlope5 = PcdGet32 (PcdTelemetryVddcrVddfullScale5Current);
  PPTable->Telemetry_VddcrVddOffset = PcdGet32 (PcdTelemetry_VddcrVddOffset);
  PPTable->Telemetry_VddcrSocSlope = PcdGet32 (PcdTelemetry_VddcrSocfull_Scale_Current);
  PPTable->Telemetry_VddcrSocOffset = PcdGet32 (PcdTelemetry_VddcrSocOffset);
  PPTable->AA_MODE_EN = (UINT32) PcdGet8 (PcdCfgPeApmEnable);
  PPTable->FAST_PPT_LIMIT = PcdGet32 (PcdFastPptLimit);
  PPTable->SLOW_PPT_LIMIT = PcdGet32 (PcdSlowPptLimit);
  PPTable->SLOW_PPT_TIME_CONSTANT = PcdGet32 (PcdSlowPptTimeConstant);
  PPTable->PSI0_CURRENT_LIMIT = PcdGet32 (PcdVrmLowPowerThreshold);
  PPTable->PSI0_SOC_CURRENT_LIMIT = PcdGet32 (PcdVrmSocLowPowerThreshold);
  PPTable->THERMCTL_LIMIT = PcdGet32 (PcdCfgThermCtlValue);
  PPTable->VRM_MAXIMUM_CURRENT_LIMIT = PcdGet32 (PcdVrmMaximumCurrentLimit);
  PPTable->VRM_SOC_MAXIMUM_CURRENT_LIMIT = PcdGet32 (PcdVrmSocMaximumCurrentLimit);
  PPTable->SUSTAINED_POWER_LIMIT = PcdGet32 (PcdSustainedPowerLimit);
  PPTable->STAPM_TIME_CONSTANT = PcdGet32 (PcdStapmTimeConstant);
  PPTable->PROCHOT_L_DEASSERTION_RAMP_TIME = PcdGet32 (PcdProchotlDeassertionRampTime);
  PPTable->VRM_CURRENT_LIMIT = PcdGet32 (PcdVrmCurrentLimit);
  PPTable->VRM_SOC_CURRENT_LIMIT = PcdGet32 (PcdVrmSocCurrentLimit);
  PPTable->VddcrSocVoltageMargin = PcdGet32 (PcdVddcrSocVoltageMargin);
  PPTable->VddcrVddVoltageMargin = PcdGet32 (PcdVddcrVddVoltageMargin);
  PPTable->SbTsiAlertComparatorModeEn = PcdGetBool (PcdSbTsiAlertComparatorModeEn);
  PPTable->CoreDldoBypass = PcdGet8 (PcdCoreDldoBypass);
  PPTable->minSocVidOffset = PcdGet8 (PcdminSocVidOffset);
  PPTable->AclkDpm0Freq400MHz = PcdGet8 (PcdAclkDpm0Freq400MHz);
  PPTable->itemp = PcdGet8 (Pcditemp);
  PPTable->WLAN = PcdGet32 (PcdWLANS0i3SaveRestore);

  //<Embedded_Override_Start>
  if ((LogicalId.Family & AMD_FAMILY_RV2) != 0) {
    //This is to enable USB workaround fix for RV2 SMU
    PPTable->SparseControlDisable = PcdGet8 (PcdSparseControlDisable);
  }else {
    PPTable->Field.EmbeddedPlatformEn = 1; // This field is to avoid syncflood failure when run in warmreset
    IDS_HDT_CONSOLE (MAIN_FLOW, "PCO:EmbeddedPlatformEn \n");
  }
  //<Embedded_Override_End>

  // Set A0 AC Droop Coefficients on RV1 A0
  if ((LogicalId.Family & AMD_FAMILY_RV) != 0) {
    if ((LogicalId.Revision & AMD_REV_F17_RV_A0) != 0) {
      PPTable->AvfsCoeffTable_Override = 1;
      PPTable->CorePsfFreq2 = 0xFD558106; //-2.666F
      PPTable->CorePsfFreq = 0x145CAC08;  //20.362F
      PPTable->CorePsfSigma = 0x1795810;  // 1.474F
      PPTable->GfxPsfFreq2 = 0xF321CAC1;  // -12.87F
      PPTable->GfxPsfFreq = 0x276872B0;   // 39.408F
      PPTable->GfxPsfSigma = 0xFDBE76C9;  //-2.256F
      IDS_HDT_CONSOLE (MAIN_FLOW, "A0 Setting \n", LogicalId.Revision);
    }
  }
  Status = gBS->InstallProtocolInterface (
                  &Handle,
                  &gAmdNbioSmuServicesProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mDxeAmdNbioSmuServicesProtocol
                  );

  Status = gBS->InstallProtocolInterface (
                  &Handle,
                  &gAmdCoreTopologyServicesProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mAmdCoreTopologyServicesProtocol
                  );

  //
  //<Embedded_Override_Start> 
  //

  // Read Tctl from SMU message
  Status = gBS->LocateProtocol (
               &gAmdNbioSmuServicesProtocolGuid,
               NULL,
               (VOID **)&NbioSmuServiceProtocolPtr
               );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  SmuArgs[0] = 0;
  SmuArgs[1] = 0;
  SmuArgs[2] = 0;
  SmuArgs[3] = 0;
  SmuArgs[4] = 0;
  SmuArgs[5] = 0;

  NbioSmuServiceProtocolPtr->AmdSmuServiceRequest (NbioSmuServiceProtocolPtr, 0, SMC_MSG_GetSustainedPowerAndThmLimit, SmuArgs, SmuArgs);
  PowerLimit = ((SmuArgs[0] & 0x00FF0000) >> 16);
  IDS_HDT_CONSOLE (MAIN_FLOW, "SystemConfiguration PCD:%d,PowerLimit:%dW\n",PcdGet8 (PcdCfgSystemConfiguration),PowerLimit);

  if (!(PcdGet32 (PcdSmuFeatureControlDefinesExt) & ((UINT32) (1 << (FEATURE_STAPM_BIT % 32)))))
  {
    //Get the OPN name string and if it's NPU Update the Sustained Power Limit values accordingly
    GetOPNNameString(OPNNameString);
  
    if (!AsciiStrCmp(OPNNameString, NPU_OPN_V1500B)) {
      if(PcdGet8 (PcdEnableV1500BExtPptLimit ) &&
         (PcdGet8 (PcdCfgSystemConfiguration) == SYSTEM_CONFIG_TDP_25W) ) {
        //Update the Config to 25W
        PPTable->SUSTAINED_POWER_LIMIT = 25000;
		PcdSet8 (PcdCfgSystemConfiguration, (UINT8) SYSTEM_CONFIG_TDP_25W);//Set Embedded 25W
        PPTable->SLOW_PPT_LIMIT = 25000;
        PPTable->FAST_PPT_LIMIT = 30000;
        IDS_HDT_CONSOLE (MAIN_FLOW, "25W NPU OPN\n");
      } else {
        PPTable->SUSTAINED_POWER_LIMIT = 16000;//Assign 16W for V1500B NPU OPN
        PcdSet8 (PcdCfgSystemConfiguration, (UINT8) SYSTEM_CONFIG_TDP_15W);//Set Embedded 15W
        PPTable->SLOW_PPT_LIMIT = 16000;
        PPTable->FAST_PPT_LIMIT = 16000;
        IDS_HDT_CONSOLE (MAIN_FLOW, "16W NPU OPN\n");
      }
      
    } else {
      switch (PowerLimit) {
        case POWER_LIMIT_15W:
          switch (PcdGet8 (PcdCfgSystemConfiguration)) {
            case SYSTEM_CONFIG_TDP_12W: //12W
              PowerLimit = 12;
              break;
            case SYSTEM_CONFIG_TDP_15W: //15W
              PowerLimit = 15;
              break;
            case SYSTEM_CONFIG_TDP_25W: //25W
              PowerLimit = 25;
              break;
            default:
              //R2312 OPN maximum supported system configuration is 25W
              if (!AsciiStrCmp(OPNNameString, R2K_OPN_R2312)) {
                PowerLimit = 25;
                PcdSet8 (PcdCfgSystemConfiguration, (UINT8)SYSTEM_CONFIG_TDP_25W);//Set Embedded 25W
                IDS_HDT_CONSOLE (MAIN_FLOW, "Configured to 25W \n");
              }else{
                PowerLimit = 35;
                PcdSet8 (PcdCfgSystemConfiguration, (UINT8)SYSTEM_CONFIG_TDP_35W);//Set Embedded 35W
                IDS_HDT_CONSOLE (MAIN_FLOW, "Configured to 35W \n");
              }
              break;
          }
          break;
        case POWER_LIMIT_45W:
          switch (PcdGet8 (PcdCfgSystemConfiguration)) {
            case SYSTEM_CONFIG_TDP_35W: //35W
              PowerLimit = 35;
              break;
            case SYSTEM_CONFIG_TDP_45W: //45W
              PowerLimit = 45;
              break;
            case SYSTEM_CONFIG_TDP_54W: //54W
              PowerLimit = 54;
              break;
            default:
              PowerLimit = 54;
              PcdSet8 (PcdCfgSystemConfiguration, (UINT8) SYSTEM_CONFIG_TDP_54W);//Set Embedded 54W
              break;
          }
          break;
        case POWER_LIMIT_8W:
          switch (PcdGet8 (PcdCfgSystemConfiguration)) {
            case SYSTEM_CONFIG_TDP_8W: //8W
              PowerLimit = 8;
              break;
            case SYSTEM_CONFIG_TDP_10W: //10W
              PowerLimit = 10;
              break;
            default:
              PowerLimit = 10;
              PcdSet8 (PcdCfgSystemConfiguration, (UINT8) SYSTEM_CONFIG_TDP_10W);//Set Embedded 10W
              break;
          }
          break;
        case POWER_LIMIT_6W:
          PowerLimit = 6;
          PcdSet8 (PcdCfgSystemConfiguration, (UINT8) SYSTEM_CONFIG_TDP_6W);//Set Embedded 6W
          break;
      }

      if ((PowerLimit == POWER_LIMIT_6W) && (PPTable->SYSTEM_CONFIG != SYSTEM_CONFIG_TDP_6W_EMBEDDED)) {
        /*
         * This change is only for R1102G 6W sillicon where 6W SDP is default system configuration
         * and on selection of "6W Embedded" from user in BIOS setup, 6W Embedded sysconfig will be used.
         * requirement for 6W SDP system confirguration:
         * 1) set FEATURE_STAPM_BIT
         * 2) Enabled STAPM_BOOST_OVERRIDE and STAPM_BOOST.
         * 3) sPPT = 7800 and fPPT = 12000      (12000 is default in SMU for 6W OPN, so not touching it)
         * 4) SUSTAINED_POWER_LIMIT = 6000      (6000 is default in SMU for 6W OPN, so not touching it)
         * 5) STAPM_TIME_CONSTANT = 2500 sec    (2500 sec is default in SMU for 6W OPN, so not touching it)
        */
        //Enable STAPM only for R1102G sample.
        PcdSet32(PcdSmuFeatureControlDefinesExt, PcdGet32(PcdSmuFeatureControlDefinesExt) | ((UINT32) (1 << (FEATURE_STAPM_BIT % 32))));
        PPTable->STAPM_BOOST_OVERRIDE = 1;
        PPTable->STAPM_BOOST = 1;
        //PPTable->SYSTEM_TEMPERATURE_TRACKING = 1;
      } else {
        //
        //Update the SLOW_PPT_LIMIT as same as TDP value & FAST_PPT_LIMIT as 1.2*TDP
        //
        PPTable->SLOW_PPT_LIMIT = PowerLimit * 1000;
        PPTable->FAST_PPT_LIMIT = PowerLimit * 1200;
      }
    } //end else
    IDS_HDT_CONSOLE (MAIN_FLOW, "SLOW_PPT_LIMIT = %d FAST_PPT_LIMIT:%d\n",PPTable->SLOW_PPT_LIMIT, PPTable->FAST_PPT_LIMIT);
  }
  
  //Assign the Updated PCD value to PPTable
  PPTable->SYSTEM_CONFIG = PcdGet8 (PcdCfgSystemConfiguration);
  //<Embedded_Override_End>  
  SmuDxeInitialize (&PcieFromHob);
  Pcie = PcieFromHob;
  NbioHandle = NbioGetHandle (Pcie);

  //<Embedded_Override_Start>
  if ((LogicalId.Family & AMD_FAMILY_RV) != 0) {
    // Silicon behavior
    IDS_HDT_CONSOLE (MAIN_FLOW, "RV Source \n");
    AsmCpuid (
        0x80000003,
        &(CpuId.EAX_Reg),
        &(CpuId.EBX_Reg),
        &(CpuId.ECX_Reg),
        &(CpuId.EDX_Reg)
        );
    IDS_HDT_CONSOLE (MAIN_FLOW, "CPU Name String = 0x%x\n", CpuId.EAX_Reg);
    if (!(CpuId.EAX_Reg == 0x30334D31 ||
        CpuId.EAX_Reg == 0x30334D32 ||
        CpuId.EAX_Reg == 0x39314D32)) {
      if (CpuId.EAX_Reg == 0x33334D32 || CpuId.EAX_Reg == 0x30324D32) {
        Status = NbioRegisterRead (NbioHandle, TYPE_SMN, 0x5D5B8, &Value32Upper, 0);
        Value32Upper = Value32Upper & 0xF8000000;
        Status = NbioRegisterRead (NbioHandle, TYPE_SMN, 0x5D5BC, &Value32Lower, 0);
        Value32Lower = (Value32Lower & 0x7FF);
        Value32Upper = (Value32Upper >> 27);
        Value32Upper = Value32Upper | (Value32Lower << 5);
        PcdSet8 (PcdDcBtc , FALSE);

        if (Value32Upper == 0x59E || Value32Upper == 0x5C8) {    //1438 , 1483
          PPTable->UseCcxFreqCurveFuses = 1;
          PPTable->UseGfxFreqCurveFuses = 1;
          PPTable->UseCacSiddFuses = 1;
        }
      } else {
        PPTable->UseCcxFreqCurveFuses = 1;
        PPTable->UseGfxFreqCurveFuses = 1;
        PPTable->UseCacSiddFuses = 1;
      }
    }

    if ((1 << RV_SOCKET_AM4) == PackageType) {
      // Workaround DLDO bypass for RV AM4
      PPTable->UseCcxFreqCurveFuses = 0;
      PPTable->UseGfxFreqCurveFuses = 0;
      PPTable->UseCacSiddFuses = 0;
      if ((LogicalId.Revision & AMD_REV_F17_RV_B0) != 0) {
        PPTable->UseCcxFreqCurveFuses = 1;
        PPTable->UseGfxFreqCurveFuses = 1;
        PPTable->UseCacSiddFuses = 1;
      }
    }
  } else if ((LogicalId.Family & AMD_FAMILY_RV2) != 0) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "RV2 Single Source \n");
    PPTable->UseCcxFreqCurveFuses = 1;
    PPTable->UseGfxFreqCurveFuses = 1;
    PPTable->UseCacSiddFuses = 1;
  } else if ((LogicalId.Family & AMD_FAMILY_PIC) != 0) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "Pure PCO / ( PCO ) RV2 Dual Source \n");
    PPTable->UseCcxFreqCurveFuses = 1;
    PPTable->UseGfxFreqCurveFuses = 1;
    PPTable->UseCacSiddFuses = 1;
  }
  //<Embedded_Override_End>
  IDS_HOOK (IDS_HOOK_NBIO_SMUV10_INIT, NULL, (VOID*) PPTable);
  IDS_HOOK (IDS_HOOK_NBIO_SMUV10_INIT_CMN, NULL, (VOID*) PPTable);

  DumpSmuFeatureControl (PcdGet32 (PcdSmuFeatureControlDefines), PcdGet32 (PcdSmuFeatureControlDefinesExt));

  //BLDCFG/CBS fan table
  PPTable->ForceFanPwmEn = PcdGet8 (PcdForceFanPwmEn);
  if (PPTable->ForceFanPwmEn != 0 ) {
    PPTable->ForceFanPwm = PcdGet8 (PcdForceFanPwm);
  }

  PPTable->FanTable_Override = PcdGet8 (PcdFanTableOverride);  //Fan Table Control Options
  if (PPTable->FanTable_Override != 0) {
    PPTable->FanTable_TempLow = PcdGet8 (PcdFanTableTempLow);
    PPTable->FanTable_TempMed = PcdGet8 (PcdFanTableTempMed);
    PPTable->FanTable_TempHigh = PcdGet8 (PcdFanTableTempHigh);
    PPTable->FanTable_TempCritical = PcdGet8 (PcdFanTableTempCritical);
    PPTable->FanTable_PwmLow = PcdGet8 (PcdFanTablePwmLow);
    PPTable->FanTable_PwmMed = PcdGet8 (PcdFanTablePwmMed);
    PPTable->FanTable_PwmHigh = PcdGet8 (PcdFanTablePwmHigh);
    PPTable->FanTable_Hysteresis = PcdGet8 (PcdFanTableHysteresis);
    PPTable->FanTable_PwmFreq = PcdGet8 (PcdFanTablePwmFreq);
    PPTable->FanTable_Polarity = PcdGet8 (PcdFanTablePolarity);
  }

  RvCpuRevision = CheckRvCpuRevision();

  switch (RvCpuRevision) {
    case 3:
    if (PcdGet32 (PcdR3VddcrVddVoltageMargin) != 0) {
      PPTable->VddcrVddVoltageMargin = PcdGet32 (PcdR3VddcrVddVoltageMargin);
    }
    break;
    case 5:
    if (PcdGet32 (PcdR5VddcrVddVoltageMargin) != 0) {
      PPTable->VddcrVddVoltageMargin = PcdGet32 (PcdR5VddcrVddVoltageMargin);
    }
    break;
    case 7:
    if (PcdGet32 (PcdR7VddcrVddVoltageMargin) != 0) {
      PPTable->VddcrVddVoltageMargin = PcdGet32 (PcdR7VddcrVddVoltageMargin);
    }
    break;
    default:
    break;
  }

  // To decide apply Vrm Psi workaround
  PPTable->ApplyRichtekVrmPsi0Workaround = PcdGetBool (PcdRichtekVrmPsi0Workaround);
  // MS s0i3
  PPTable->MinS0i3SleepTimeInMs = PcdGet32 (PcdMinS0i3SleepTimeMs);
  // STT_MinLimit
  PPTable->STT_MinLimit = PcdGet32 (PcdSttMinLimit);

  PPTable->UsbPortsToClearWceWde[0] = PcdGet8 (PcdUsbPortsToClearWceWde0);
  PPTable->UsbPortsToClearWceWde[1] = PcdGet8 (PcdUsbPortsToClearWceWde1);
  PPTable->WaitVidCompDis = PcdGet8 (PcdWaitVidCompDis);
  PPTable->Voltage_SlewRate = PcdGet8 (PcdVoltageSlewRate);

  if (PcdGetBool (PcdCfgPCIePHYPowerGating)) {
    PPTable->CalculateIOPhyDataDis = 1;
  } else {
    PPTable->CalculateIOPhyDataDis = 0;
  }
  // dump Fan policy table
  DumpFanPolicyTable (PPTable);

  IDS_HDT_CONSOLE (MAIN_FLOW, "GfxStretchThreshEn = 0x%x\n", PPTable->GfxStretchThreshEn);
  IDS_HDT_CONSOLE (MAIN_FLOW, "GfxStretchThresh = 0x%x\n", PPTable->GfxStretchThresh);
  IDS_HDT_CONSOLE (MAIN_FLOW, "GfxStretchAmountEn = 0x%x\n", PPTable->GfxStretchAmountEn);
  IDS_HDT_CONSOLE (MAIN_FLOW, "GfxStretchAmount = 0x%x\n", PPTable->GfxStretchAmount);

  IDS_HDT_CONSOLE (MAIN_FLOW, "CoreStretchThreshEn = 0x%x\n", PPTable->CoreStretchThreshEn);
  IDS_HDT_CONSOLE (MAIN_FLOW, "CoreStretchThresh = 0x%x\n", PPTable->CoreStretchThresh);
  IDS_HDT_CONSOLE (MAIN_FLOW, "L3StretchThreshEn = 0x%x\n", PPTable->L3StretchThreshEn);
  IDS_HDT_CONSOLE (MAIN_FLOW, "L3StretchThresh = 0x%x\n", PPTable->L3StretchThresh);
  IDS_HDT_CONSOLE (MAIN_FLOW, "CoreDldoBypass = 0x%x\n", PPTable->CoreDldoBypass);
  IDS_HDT_CONSOLE (MAIN_FLOW, "GfxDldoBypass = 0x%x\n", PPTable->GfxDldoBypass);
  IDS_HDT_CONSOLE (MAIN_FLOW, "CoreDldoPsmMargin = 0x%x\n", PPTable->CoreDldoPsmMargin);
  IDS_HDT_CONSOLE (MAIN_FLOW, "GfxDldoPsmMargin = 0x%x\n", PPTable->GfxDldoPsmMargin);
  IDS_HDT_CONSOLE (MAIN_FLOW, "VddcrVddVoltageMargin = 0x%x\n", PPTable->VddcrVddVoltageMargin);
  IDS_HDT_CONSOLE (MAIN_FLOW, "VddcrSocVoltageMargin = 0x%x\n", PPTable->VddcrSocVoltageMargin);
  IDS_HDT_CONSOLE (MAIN_FLOW, "SYSTEM_CONFIG = 0x%x\n", PPTable->SYSTEM_CONFIG);
  IDS_HDT_CONSOLE (MAIN_FLOW, "Telemetry_VddcrVddSlope = 0x%x\n", PPTable->Telemetry_VddcrVddSlope);
  IDS_HDT_CONSOLE (MAIN_FLOW, "Telemetry_VddcrVddSlope2 = 0x%x\n", PPTable->Telemetry_VddcrVddSlope2);
  IDS_HDT_CONSOLE (MAIN_FLOW, "Telemetry_VddcrVddSlope3 = 0x%x\n", PPTable->Telemetry_VddcrVddSlope3);
  IDS_HDT_CONSOLE (MAIN_FLOW, "Telemetry_VddcrVddSlope4 = 0x%x\n", PPTable->Telemetry_VddcrVddSlope4);
  IDS_HDT_CONSOLE (MAIN_FLOW, "Telemetry_VddcrVddSlope5 = 0x%x\n", PPTable->Telemetry_VddcrVddSlope5);
  IDS_HDT_CONSOLE (MAIN_FLOW, "Telemetry_VddcrVddOffset = 0x%x\n", PPTable->Telemetry_VddcrVddOffset);
  IDS_HDT_CONSOLE (MAIN_FLOW, "Telemetry_VddcrSocSlope = 0x%x\n", PPTable->Telemetry_VddcrSocSlope);
  IDS_HDT_CONSOLE (MAIN_FLOW, "Telemetry_VddcrSocOffset = 0x%x\n", PPTable->Telemetry_VddcrSocOffset);
  IDS_HDT_CONSOLE (MAIN_FLOW, "FastPptLimit = 0x%x\n", PPTable->FAST_PPT_LIMIT);
  IDS_HDT_CONSOLE (MAIN_FLOW, "SlowPptLimit = 0x%x\n", PPTable->SLOW_PPT_LIMIT);
  IDS_HDT_CONSOLE (MAIN_FLOW, "SlowPptTimeConstant = 0x%x\n", PPTable->SLOW_PPT_TIME_CONSTANT);
  IDS_HDT_CONSOLE (MAIN_FLOW, "Thermal Control Limit = 0x%x\n", PPTable->THERMCTL_LIMIT);
  IDS_HDT_CONSOLE (MAIN_FLOW, "VRM_MAXIMUM_CURRENT_LIMIT = 0x%x\n", PPTable->VRM_MAXIMUM_CURRENT_LIMIT);
  IDS_HDT_CONSOLE (MAIN_FLOW, "VRM_SOC_MAXIMUM_CURRENT_LIMIT = 0x%x\n", PPTable->VRM_SOC_MAXIMUM_CURRENT_LIMIT);
  IDS_HDT_CONSOLE (MAIN_FLOW, "SUSTAINED_POWER_LIMIT = 0x%x\n", PPTable->SUSTAINED_POWER_LIMIT);
  IDS_HDT_CONSOLE (MAIN_FLOW, "STAPM_TIME_CONSTANT = 0x%x\n", PPTable->STAPM_TIME_CONSTANT);
  IDS_HDT_CONSOLE (MAIN_FLOW, "STAPM_BOOST = 0x%x\n", PPTable->STAPM_BOOST);
  IDS_HDT_CONSOLE (MAIN_FLOW, "STAPM_BOOST_OVERRIDE = 0x%x\n", PPTable->STAPM_BOOST_OVERRIDE);
  IDS_HDT_CONSOLE (MAIN_FLOW, "FEATURE_STAPM_BIT = 0x%x\n", PcdGet32 (PcdSmuFeatureControlDefinesExt) & ((UINT32) (1 << (FEATURE_STAPM_BIT % 32))));  
  IDS_HDT_CONSOLE (MAIN_FLOW, "PROCHOT_L_DEASSERTION_RAMP_TIME = 0x%x\n", PPTable->PROCHOT_L_DEASSERTION_RAMP_TIME);

  IDS_HDT_CONSOLE (MAIN_FLOW, "VRM_CURRENT_LIMIT = 0x%x\n", PPTable->VRM_CURRENT_LIMIT);
  IDS_HDT_CONSOLE (MAIN_FLOW, "VRM_SOC_CURRENT_LIMIT = 0x%x\n", PPTable->VRM_SOC_CURRENT_LIMIT);
  IDS_HDT_CONSOLE (MAIN_FLOW, "CalculateIOPhyDataDis = 0x%x\n", PPTable->CalculateIOPhyDataDis);
  IDS_HDT_CONSOLE (MAIN_FLOW, "FmaxTempThreshold = 0x%x\n", PPTable->FmaxTempThreshold);
  IDS_HDT_CONSOLE (MAIN_FLOW, "FmaxTempFrequency = 0x%x\n", PPTable->FmaxTempFrequency);

  IDS_HDT_CONSOLE (MAIN_FLOW, "PPTable->UseCcxFreqCurveFuses = 0x%x\n", PPTable->UseCcxFreqCurveFuses);
  IDS_HDT_CONSOLE (MAIN_FLOW, "PPTable->UseGfxFreqCurveFuses = 0x%x\n", PPTable->UseGfxFreqCurveFuses);
  IDS_HDT_CONSOLE (MAIN_FLOW, "PPTable->UseCacSiddFuses = 0x%x\n", PPTable->UseCacSiddFuses);
  IDS_HDT_CONSOLE (MAIN_FLOW, "PPTable->CoreDldoBypass = 0x%x\n", PPTable->CoreDldoBypass);

  IDS_HDT_CONSOLE (MAIN_FLOW, "PPTable->minSocVidOffset = 0x%x\n", PPTable->minSocVidOffset);
  IDS_HDT_CONSOLE (MAIN_FLOW, "PPTable->AclkDpm0Freq400MHz = 0x%x\n", PPTable->AclkDpm0Freq400MHz);
  IDS_HDT_CONSOLE (MAIN_FLOW, "PPTable->itemp = 0x%x\n", PPTable->itemp);
  IDS_HDT_CONSOLE (MAIN_FLOW, "PPTable->WLAN = 0x%x\n", PPTable->WLAN);
  IDS_HDT_CONSOLE (MAIN_FLOW, "PPTable->WaitVidCompDis = 0x%x\n", PPTable->WaitVidCompDis);
  IDS_HDT_CONSOLE (MAIN_FLOW, "PPTable->Voltage_SlewRate = 0x%x\n", PPTable->Voltage_SlewRate);
  IDS_HDT_CONSOLE (MAIN_FLOW, "PPTable->SparseControlDisable = 0x%x\n", PPTable->SparseControlDisable);


  NbioSmuServiceCommonInitArgumentsV10 (SmuArg);

  while (NbioHandle != NULL) {
    //
    //  Check SMU firmware revision.
    //
    IDS_HDT_CONSOLE (GNB_TRACE, "SMU Version Start\n");
    NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
    SmuArg[0] = SMU10_BIOS_IF_VERSION;
    Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_GetBiosIfVersion, SmuArg, 0);
    IDS_HDT_CONSOLE (NB_MISC, "  SmuArg 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n", SmuArg[0], SmuArg[1], SmuArg[2], SmuArg[3], SmuArg[4], SmuArg[5]);
    IDS_HDT_CONSOLE (GNB_TRACE, "SMU Version End\n");

    //
    //  Step15. Allocate DRAM space for the PPTable Structure.
    //
    NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
    SmuArg[0] = (UINT32) ((EFI_PHYSICAL_ADDRESS) PPTable & 0xFFFFFFFF);
    Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetBiosDramAddrLow, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
    if (EFI_ERROR (Status)) {
      return EFI_INVALID_PARAMETER;
    }

    SmuArg[0] = (UINT32) RShiftU64 ((EFI_PHYSICAL_ADDRESS) PPTable, 32);
    Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetBiosDramAddrHigh, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
    if (EFI_ERROR (Status)) {
      return EFI_INVALID_PARAMETER;
    }

    //
    //  Step16. Call SMC_MSG_TransferTableDram2Smu to ask SMU to read in the PP Table, SMU reply when the DRAM read is complete.
    //
    NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
    SmuArg[0] = TABLE_PPTABLE; //Input Argument should be 0;
    Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_TransferTableDram2Smu, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
    if (EFI_ERROR (Status)) {
      return EFI_INVALID_PARAMETER;
    }

    //
    //  Step20. Allocate 4KB DRAM, Call Message BIOSSMC_MSG_SetAgmLogDramAddress with 64 bit address
    //
    Status = gBS->AllocatePages (
                    AllocateMaxAddress,
                    EfiACPIMemoryNVS,
                    1,
                    &SetAgmLogDramAddress
                    );
    IDS_HDT_CONSOLE (MAIN_FLOW, "SetAgmLogDramAddress = 0x%x\n", SetAgmLogDramAddress);
    IDS_HDT_CONSOLE (MAIN_FLOW, "Status = 0x%x\n", Status);

    ZeroMem ((VOID *) (UINTN) SetAgmLogDramAddress, (1 * EFI_PAGE_SIZE));

    NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
    SmuArg[0] = (UINT32)SetAgmLogDramAddress;
    Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetToolsDramAddrLow, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
    if (EFI_ERROR (Status)) {
      return EFI_INVALID_PARAMETER;
    }

    NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
    SmuArg[0] = (UINT32) RShiftU64 ((UINT64)SetAgmLogDramAddress, 32);
    Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetToolsDramAddrHigh, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
    if (EFI_ERROR (Status)) {
      return EFI_INVALID_PARAMETER;
    }

    //
    //  Step22. if CBS options SmuAllocateDramBuffer is non-zero, allocate unsecure DRAM based on the size in Byte defined in the CBS options.
    //          Call message BIOSSMC_MSG_SetDramBufferAddress to pass in the 64 bit address (use 2 message argument)
    //
    DramBufferSize = PcdGet32 (PcdSmuAllocateDramBufferSize);

    if (DramBufferSize != 0) {
      Status = gBS->AllocatePages (
                      AllocateAnyPages,
                      EfiACPIMemoryNVS,
                      GNB_MB_TO_PAGE (DramBufferSize),
                      &SmuDramBufferAddress
                      );
      IDS_HDT_CONSOLE (MAIN_FLOW, "Status = 0x%x\n", Status);

      ZeroMem ((VOID *) SmuDramBufferAddress, DramBufferSize * SIZE_1MB);

      IDS_HDT_CONSOLE (MAIN_FLOW, "SmuDramBufferAddress = 0x%x\n", SmuDramBufferAddress);

      if (!EFI_ERROR (Status)) {
        NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
        SmuArg[0] = (UINT32) ((UINT64)SmuDramBufferAddress);
        IDS_HDT_CONSOLE (MAIN_FLOW, "SmuDramBufferAddressLow = 0x%x\n", SmuArg[0]);
        Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_DramLogSetDramAddrLow, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
        if (EFI_ERROR (Status)) {
          return EFI_INVALID_PARAMETER;
        }

        NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
        SmuArg[0] = (UINT32) RShiftU64 ((UINT64)SmuDramBufferAddress, 32);
        IDS_HDT_CONSOLE (MAIN_FLOW, "SmuDramBufferAddressHigh = 0x%x\n", SmuArg[0]);
        Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_DramLogSetDramAddrHigh, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
        if (EFI_ERROR (Status)) {
          return EFI_INVALID_PARAMETER;
        }

        NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
        SmuArg[0] = DramBufferSize * SIZE_1MB;
        Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_DramLogSetDramSize, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
        if (EFI_ERROR (Status)) {
          return EFI_INVALID_PARAMETER;
        }
      }
    }

    if (PcdGet32 (PcdCfgThermCtlLimit) != 0) {
      NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
      SmuArg[0] = PcdGet32 (PcdCfgThermCtlLimit);
      Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetTctlMax, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
      if (EFI_ERROR (Status)) {
        return EFI_INVALID_PARAMETER;
      }
    }
    if (PcdGet32 (PcdVminFrequency) != 0) {
      NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
      SmuArg[0] = PcdGet32 (PcdVminFrequency);
      Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetVminFrequency, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
      if (EFI_ERROR (Status)) {
        return EFI_INVALID_PARAMETER;
      }
    }

    if (PcdGet32 (PcdFMaxFrequency) != 0) {
      NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
      SmuArg[0] = PcdGet32 (PcdFMaxFrequency);
      Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetFrequencyMax, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
      if (EFI_ERROR (Status)) {
        return EFI_INVALID_PARAMETER;
      }
    }

    if (PcdGet32 (PcdEnableSmuPostCodeLevel) != 0) {
      NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
      SmuArg[0] = PcdGet32 (PcdEnableSmuPostCodeLevel);
      Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_EnablePostCode, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
      if (EFI_ERROR (Status)) {
        return EFI_INVALID_PARAMETER;
      }
    }

    NbioHandle = GnbGetNextHandle (NbioHandle);
  }

  EfiCreateProtocolNotifyEvent (&gAmdCcxDxeInitCompleteProtocolGuid, TPL_CALLBACK, CallbackAfterCcxDxeDone, NULL, &Registration);
  EfiCreateProtocolNotifyEvent (&gAmdNbioSmuInitCompleteProtocolGuid, TPL_CALLBACK, CallbackAfterSmuInitComplete, NULL, &Registration);

  if (PcdGet8 (PcdS0i3Enable) == 0x1) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "S0i3 Enable\n");
    CallbackforS0i3Feature ();
    EfiCreateProtocolNotifyEvent (&gEfiPciEnumerationCompleteProtocolGuid, TPL_CALLBACK, CallbackAfterPCIeEnumerateComplete, NULL, &Registration);
  }

  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdNbioSmuV10DxeEntry Exit\n");
  AGESA_TESTPOINT (TpNbioSmuV10DxeExit, NULL);

  return EFI_SUCCESS;
}


