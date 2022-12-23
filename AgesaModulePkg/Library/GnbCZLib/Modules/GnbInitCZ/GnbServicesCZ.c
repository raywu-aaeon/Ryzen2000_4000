/* $NoKeywords:$ */
/**
 * @file
 *
 * Install of build option: GNB
 *
 * Contains AMD AGESA install macros and test conditions. Output is the
 * defaults tables reflecting the User's build options selection.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Options
 * @e \$Revision: 329865 $   @e \$Date: 2015-10-29 09:59:04 +0800 (Thu, 29 Oct 2015) $
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
 **/

#include "Gnb.h"
#include  "OptionGnb.h"
#include  "SocLogicalId.h"
  #include "GnbPcie.h"
  #include "GnbGfx.h"
  #include  "GnbPcieFamServices.h"
  #include  "GnbFamServices.h"
  #include  "GnbGfxFamServices.h"

//---------------------------------------------------------------------------------------------------
// Service installation
// Export CZ services
//---------------------------------------------------------------------------------------------------
  extern F_PCIEFMGETSBCONFIGINFO                  PcieGetSbConfigInfoCZ;
  extern F_PCIEFMGETCOMPLEXDATALENGTH             PcieGetComplexDataLengthCZ;
  extern F_PCIEFMBUILDCOMPLEXCONFIGURATION        PcieBuildComplexConfigurationCZ;
  extern F_PCIEFMCONFIGUREENGINESLANEALLOCATION   PcieConfigureEnginesLaneAllocationCZ;
  extern F_PCIEFMCHECKPORTPCIDEVICEMAPPING        PcieCheckPortPciDeviceMappingCZ;
  extern F_PCIEFMMAPPORTPCIADDRESS                PcieMapPortPciAddressCZ;
  extern F_PCIEFMCHECKPORTPCIELANECANBEMUXED      PcieCheckPortPcieLaneCanBeMuxedCZ;
  PCIe_FAM_CONFIG_SERVICES GnbPcieConfigProtocolCZ = {
    PcieGetComplexDataLengthCZ,
    PcieBuildComplexConfigurationCZ,
    PcieConfigureEnginesLaneAllocationCZ,
    PcieCheckPortPciDeviceMappingCZ,
    PcieMapPortPciAddressCZ,
    PcieCheckPortPcieLaneCanBeMuxedCZ,
    PcieGetSbConfigInfoCZ
  };
  GNB_SERVICE GnbPcieConfigServicesCZ = {
    GnbPcieFamConfigService,
    AMD_FAMILY_CZ,
    &GnbPcieConfigProtocolCZ,
    NULL
  };

  //-------------------------------------------------------
  extern F_PCIEFMGETCORECONFIGURATIONVALUE        PcieGetCoreConfigurationValueCZ;
  extern F_PCIEFMGETLINKSPEEDCAP                  PcieGetLinkSpeedCapCZ;
  extern F_PCIEFMGETNATIVEPHYLANEBITMAP           PcieGetNativePhyLaneBitmapCZ;
  extern F_PCIEFMSETLINKSPEEDCAP                  PcieSetLinkSpeedCapV4;
  PCIe_FAM_INIT_SERVICES GnbPcieInitProtocolCZ = {
    PcieGetCoreConfigurationValueCZ,
    PcieGetLinkSpeedCapCZ,
    PcieGetNativePhyLaneBitmapCZ,
    PcieSetLinkSpeedCapV4
  };
  GNB_SERVICE GnbPcieInitServicesCZ = {
    GnbPcieFamInitService,
    AMD_FAMILY_CZ,
    &GnbPcieInitProtocolCZ,
    &GnbPcieConfigServicesCZ
  };

  //-------------------------------------------------------
  //  #if IDSOPT_TRACING_ENABLED == TRUE
  extern F_PCIEFMDEBUGGETHOSTREGADDRESSSPACESTRING  PcieDebugGetHostRegAddressSpaceStringCZ;
  extern F_PCIEFMDEBUGGETWRAPPERNAMESTRING          PcieDebugGetWrapperNameStringCZ;
  extern F_PCIEFMDEBUGGETCORECONFIGURATIONSTRING    PcieDebugGetCoreConfigurationStringCZ;

  PCIe_FAM_DEBUG_SERVICES GnbPcieDebugProtocolCZ = {
    PcieDebugGetHostRegAddressSpaceStringCZ,
    PcieDebugGetWrapperNameStringCZ,
    PcieDebugGetCoreConfigurationStringCZ
  };

  GNB_SERVICE GnbPcieDebugServicesCZ = {
    GnbPcieFamDebugService,
    AMD_FAMILY_CZ,
    &GnbPcieDebugProtocolCZ,
    &GnbPcieInitServicesCZ
  };
  //  #endif

  //-------------------------------------------------------
  extern F_GNB_REGISTER_ACCESS  GnbRegisterReadCZ;
  extern F_GNB_REGISTER_ACCESS  GnbRegisterWriteCZ;
  GNB_REGISTER_SERVICE GnbRegisterAccessProtocolCZ = {
    GnbRegisterReadCZ,
    GnbRegisterWriteCZ
  };
  GNB_SERVICE GnbRegisterAccessServicesCZ = {
    GnbRegisterAccessService,
    AMD_FAMILY_CZ,
    &GnbRegisterAccessProtocolCZ,
    &GnbPcieDebugServicesCZ
  };

  //-------------------------------------------------------
  extern F_GNBFMCREATEIVRSENTRY    GnbCreateIvrsEntryCZ;
  extern F_GNBFMCHECKIOMMUPRESENT  GnbCheckIommuPresentCZ;

  GNB_FAM_IOMMU_SERVICES GnbIommuConfigProtocolCZ = {
    GnbCheckIommuPresentCZ,
    GnbCreateIvrsEntryCZ
  };

  GNB_SERVICE GnbIommuConfigServicesCZ = {
    GnbIommuService,
    AMD_FAMILY_CZ,
    &GnbIommuConfigProtocolCZ,
    &GnbRegisterAccessServicesCZ
  };
  //-------------------------------------------------------
  extern F_GFXMAPENGINETODISPLAYPATH GfxMapEngineToDisplayPathCZ;
  extern F_GFXDISABLECONTROLLER      GfxDisableControllerCZ;
  extern F_GFXCALCULATECLOCK         GfxCalculateClockCZ;
  extern F_GFXISVBIOSPOSTED          GfxIsVbiosPostedCZ;
  GFX_FAM_SERVICES GfxFamilyServiceProtocolCZ = {
    GfxMapEngineToDisplayPathCZ,
    GfxDisableControllerCZ,
    GfxCalculateClockCZ,
    GfxIsVbiosPostedCZ
  };
  GNB_SERVICE GfxFamilyServicesCZ = {
    GfxFamService,
    AMD_FAMILY_CZ,
    &GfxFamilyServiceProtocolCZ,
    &GnbIommuConfigServicesCZ
  };

  //-------------------------------------------------------
  extern F_GNBTIMESTAMP GnbTimeStampCZ;
  GNB_FAM_TS_SERVICES GnbFamTsProtocolCZ = {
    GnbTimeStampCZ,
  };
  GNB_SERVICE GnbFamTsServicesCZ = {
    GnbFamTsService,
    AMD_FAMILY_CZ,
    &GnbFamTsProtocolCZ,
    &GfxFamilyServicesCZ
  };

  //-------------------------------------------------------
  extern F_GNBFMALIBGETBASETABLE PcieAlibGetBaseTableCZM;
  GNB_FAM_ALIB_SERVICES AlibProtocolCZ = {
    PcieAlibGetBaseTableCZM
  };
  GNB_SERVICE AlibServicesCZ = {
    GnbFamAlibService,
    AMD_FAMILY_CZ,
    &AlibProtocolCZ,
    &GnbFamTsServicesCZ
  };

  //-------------------------------------------------------
  extern F_GNBFMALIBGETBUILDOPTIONS GnbGetBuildOptionsCZ;
  GNB_FAM_BUILDOPTIONS_POINTERS GnbOptionsProtocolCZ = {
    &GnbGetBuildOptionsCZ
  };
  GNB_SERVICE GnbOptionsServicesCZ = {
    GnbFamBuildOptionPointer,
    AMD_FAMILY_CZ,
    &GnbOptionsProtocolCZ,
    &AlibServicesCZ
  };
//  GNB_SERVICE   *ServiceTableCZ = &GnbOptionsServicesCZ;
  GNB_SERVICE   *ServiceTable = &GnbOptionsServicesCZ;

