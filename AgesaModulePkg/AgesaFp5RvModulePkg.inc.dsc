#;*****************************************************************************
#;
#; Copyright 2008 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
#;
#; AMD is granting You permission to use this software and documentation (if
#; any) (collectively, the "Software") pursuant to the terms and conditions of
#; the Software License Agreement included with the Software. If You do not have
#; a copy of the Software License Agreement, contact Your AMD representative for
#; a copy.
#;
#; You agree that You will not reverse engineer or decompile the Software, in
#; whole or in part, except as allowed by applicable law.
#;
#; WARRANTY DISCLAIMER: THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
#; KIND. AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
#; BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, QUALITY,
#; FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT AND WARRANTIES
#; ARISING FROM CUSTOM OF TRADE OR COURSE OF USAGE WITH RESPECT TO THE SOFTWARE,
#; INCLUDING WITHOUT LIMITATION, THAT THE SOFTWARE WILL RUN UNINTERRUPTED OR
#; ERROR-FREE. THE ENTIRE RISK ASSOCIATED WITH THE USE OF THE SOFTWARE IS
#; ASSUMED BY YOU. Some jurisdictions do not allow the exclusion of implied
#; warranties, so the above exclusion may not apply to You, but only to the
#; extent required by law.
#;
#; LIMITATION OF LIABILITY AND INDEMNIFICATION: TO THE EXTENT NOT PROHIBITED BY
#; APPLICABLE LAW, AMD AND ITS LICENSORS WILL NOT, UNDER ANY CIRCUMSTANCES BE
#; LIABLE TO YOU FOR ANY PUNITIVE, DIRECT, INCIDENTAL, INDIRECT, SPECIAL OR
#; CONSEQUENTIAL DAMAGES ARISING FROM POSSESSION OR USE OF THE SOFTWARE OR
#; OTHERWISE IN CONNECTION WITH ANY PROVISION OF THIS AGREEMENT EVEN IF AMD AND
#; ITS LICENSORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. THIS
#; INCLUDES, WITHOUT LIMITATION, DAMAGES DUE TO LOST OR MISAPPROPRIATED DATA,
#; LOST PROFITS OR CONFIDENTIAL OR OTHER INFORMATION, FOR BUSINESS INTERRUPTION,
#; FOR PERSONAL INJURY, FOR LOSS OF PRIVACY, FOR FAILURE TO MEET ANY DUTY
#; INCLUDING OF GOOD FAITH OR REASONABLE CARE, FOR NEGLIGENCE AND FOR ANY OTHER
#; PECUNIARY OR OTHER LOSS WHTSOEVER. In no event shall AMD's total liability to
#; You for all damages, losses, and causes of action (whether in contract, tort
#; (including negligence) or otherwise) exceed the amount of $50 USD. You agree
#; to defend, indemnify and hold harmless AMD, its subsidiaries and affiliates
#; and their respective licensors, directors, officers, employees, affiliates or
#; agents from and against any and all loss, damage, liability and other
#; expenses (including reasonable attorneys' fees), resulting from Your
#; possession or use of the Software or violation of the terms and conditions of
#; this Agreement.
#;
#; U.S. GOVERNMENT RESTRICTED RIGHTS: Notice to U.S. Government End Users. The
#; Software and related documentation are "commercial items", as that term is
#; defined at 48 C.F.R. Section 2.101, consisting of "commercial computer
#; software" and "commercial computer software documentation", as such terms are
#; used in 48 C.F.R. Section 12.212 and 48 C.F.R. Section 227.7202,
#; respectively. Consistent with 48 C.F.R. Section 12.212 or 48 C.F.R. Sections
#; 227.7202-1 through 227.7202-4, as applicable, the commercial computer
#; software and commercial computer software documentation are being licensed to
#; U.S. Government end users: (a) only as commercial items, and (b) with only
#; those rights as are granted to all other end users pursuant to the terms and
#; conditions set forth in this Agreement. Unpublished rights are reserved under
#; the copyright laws of the United States.
#;
#; EXPORT RESTRICTIONS:  You shall adhere to all applicable U.S. import/export
#; laws and regulations, as well as the import/export control laws and
#; regulations of other countries as applicable. You further agree You will not
#; export, re-export, or transfer, directly or indirectly, any product,
#; technical data, software or source code received from AMD under this license,
#; or the direct product of such technical data or software to any country for
#; which the United States or any other applicable government requires an export
#; license or other governmental approval without first obtaining such licenses
#; or approvals, or in violation of any applicable laws or regulations of the
#; United States or the country where the technical data or software was
#; obtained. You acknowledges the technical data and software received will not,
#; in the absence of authorization from U.S. or local law and regulations as
#; applicable, be used by or exported, re-exported or transferred to: (i) any
#; sanctioned or embargoed country, or to nationals or residents of such
#; countries; (ii) any restricted end-user as identified on any applicable
#; government end-user list; or (iii) any party where the end-use involves
#; nuclear, chemical/biological weapons, rocket systems, or unmanned air
#; vehicles.  For the most current Country Group listings, or for additional
#; information about the EAR or Your obligations under those regulations, please
#; refer to the website of the U.S. Bureau of Industry and Security at
#; http://www.bis.doc.gov/.
#;*****************************************************************************


[LibraryClasses.Common.PEIM]
  AmdS3SaveLib|AgesaModulePkg/Library/AmdS3SaveLib/WOS3Save/AmdWOS3SaveLib.inf
  AmdHeapLib|AgesaModulePkg/Library/AmdHeapPeiLib/AmdHeapPeiLib.inf
  FabricResourceSizeForEachRbLib|AgesaModulePkg/Library/PeiFabricResourceSizeForEachRbLib/PeiFabricResourceSizeForEachRbLib.inf
  FabricResourceReportToGcdLib|AgesaModulePkg/Library/FabricResourceReportToGcdNullLib/FabricResourceReportToGcdNullLib.inf
  CcxSetMmioCfgBaseLib|AgesaModulePkg/Library/CcxSetMmioCfgBaseLib/CcxSetMmioCfgBaseLib.inf
  IdsLib|AgesaModulePkg/Library/IdsPeiLib/IdsPeiLib.inf
  FchPeiLibV9|AgesaModulePkg/Library/FchPeiLib/FchPeiLib.inf
  FchSandstonePeiLib|AgesaModulePkg/Fch/Sandstone/FchSandstoneCore/FchSandstoneLibPei.inf
  FchInitHookLibPei|AgesaModulePkg/Library/FchInitHookLib/FchInitHookLibPei.inf
  GnbHeapLib|AgesaModulePkg/Library/GnbHeapPeiLib/GnbHeapPeiLib.inf
  AmdPspCommonLib|AgesaModulePkg/Library/AmdPspCommonLibPei/AmdPspCommonLibPei.inf
  ApobCommonServiceLib|AgesaModulePkg/Library/ApobCommonServiceLibPei/ApobCommonServiceLibPei.inf
  PeiSocLogicalIdServicesLib|AgesaModulePkg/Library/PeiSocLogicalIdServicesLib/PeiSocLogicalIdServicesLib.inf
  AmdTableSmnLib|AgesaModulePkg/Library/AmdTableLib/Pei/AmdTableSmnPeiLib.inf
  AmdCapsuleLib|AgesaModulePkg/Library/AmdCapsuleLibPei/AmdCapsuleLibPei.inf
  PeiSocBistLoggingLib|AgesaModulePkg/Library/PeiSocBistLoggingLib/PeiSocBistLoggingLib.inf

  ## MEM Libs
  AmdMemBaseLib|AgesaModulePkg/Library/Mem/BaseLib/AmdMemBaseLib.inf

  AmdMemSmbiosV2Lib|AgesaModulePkg/Library/MemSmbiosV2RvLib/MemSmbiosV2Lib.inf
  AmdCalloutLib|AgesaModulePkg/Library/AmdCalloutLib/AmdCalloutLib.inf

  ## IDS LIB
  AmdIdsHookLib|AgesaModulePkg/Library/AmdIdsHookLibPei/AmdIdsHookLib.inf
  CcxZenRvIdsHookLibPei|AgesaModulePkg/Library/CcxZenRvIdsHookLib/Pei/CcxZenRvIdsHookLibPei.inf
  FabricIdsHookRvLibPei|AgesaModulePkg/Library/FabricIdsHookRvLib/Pei/FabricIdsHookRvLibPei.inf

  ## FCH I2C Lib
  Mp2I2cLibPei|AgesaModulePkg/Fch/Sandstone/FchSandstoneI2cPei/Mp2I2cLibPei.inf

[LibraryClasses.Common.DXE_DRIVER]
  AmdS3SaveLib|AgesaModulePkg/Library/AmdS3SaveLib/S3Save/AmdS3SaveLib.inf
  IdsLib|AgesaModulePkg/Library/IdsDxeLib/IdsDxeLib.inf
  FabricResourceSizeForEachRbLib|AgesaModulePkg/Library/DxeFabricResourceSizeForEachRbLib/DxeFabricResourceSizeForEachRbLib.inf
  AmdHeapLib|AgesaModulePkg/Library/AmdHeapDxeLib/AmdHeapDxeLib.inf
  GnbHeapLib|AgesaModulePkg/Library/GnbHeapDxeLib/GnbHeapDxeLib.inf
  AmdPspCommonLib|AgesaModulePkg/Library/AmdPspCommonLibDxe/AmdPspCommonLibDxe.inf
  ApobCommonServiceLib|AgesaModulePkg/Library/ApobCommonServiceLibDxe/ApobCommonServiceLibDxe.inf
  AmdPspFlashAccLib|AgesaModulePkg/Library/AmdPspFlashAccLibDxe/AmdPspFlashAccLibDxe.inf
  AmdPspFlashUpdateLib|AgesaModulePkg/Library/AmdPspFlashUpdateLib/AmdPspFlashUpdateLib.inf
  ApcbRvLib|AgesaModulePkg/Library/ApcbRvLib/ApcbLib.inf
#  ApcbSspLib|AgesaModulePkg/Library/ApcbSspLib/ApcbLib.inf                                                             <SSP|MTS>
  DxeSocLogicalIdServicesLib|AgesaModulePkg/Library/DxeSocLogicalIdServicesLib/DxeSocLogicalIdServicesLib.inf
  AmdTableSmnLib|AgesaModulePkg/Library/AmdTableLib/Dxe/AmdTableSmnDxeLib.inf
  AmdCapsuleLib|AgesaModulePkg/Library/AmdCapsuleLibDxe/AmdCapsuleLibDxe.inf
  CcxMpServicesLib|AgesaModulePkg/Library/CcxMpServicesDxeLib/CcxMpServicesDxeLib.inf
  CcxSmmAccess2Lib|AgesaModulePkg/Library/DxeCcxSmmAccess2Lib/DxeCcxSmmAccess2Lib.inf

  ## IDS LIB
  AmdIdsHookLib|AgesaModulePkg/Library/AmdIdsHookLibDxe/AmdIdsHookLib.inf
  CcxZenRvIdsHookLibDxe|AgesaModulePkg/Library/CcxZenRvIdsHookLib/Dxe/CcxZenRvIdsHookLibDxe.inf
  FabricIdsHookRvLibDxe|AgesaModulePkg/Library/FabricIdsHookRvLib/Dxe/FabricIdsHookRvLibDxe.inf

[LibraryClasses.Common.DXE_SMM_DRIVER]
  AmdHeapLib|AgesaModulePkg/Library/AmdHeapDxeLib/AmdHeapDxeLib.inf
  AmdS3SaveLib|AgesaModulePkg/Library/AmdS3SaveLib/S3Save/AmdS3SaveLib.inf
  FabricResourceSizeForEachRbLib|AgesaModulePkg/Library/DxeFabricResourceSizeForEachRbLib/DxeFabricResourceSizeForEachRbLib.inf
#@todo add specifiic SMM Lib instance, DXE Lib is depend on gBS service exisitance
  IdsLib|AgesaModulePkg/Library/IdsNonUefiLib/IdsNonUefiLib.inf
  AmdIdsHookLib|AgesaModulePkg/Library/AmdIdsHookLibDxe/AmdIdsHookLib.inf
  AmdPspCommonLib|AgesaModulePkg/Library/AmdPspCommonLibDxe/AmdPspCommonLibDxe.inf
  ApobCommonServiceLib|AgesaModulePkg/Library/ApobCommonServiceLibDxe/ApobCommonServiceLibDxe.inf
  AmdPspFlashUpdateLib|AgesaModulePkg/Library/AmdPspFlashUpdateLib/AmdPspFlashUpdateLib.inf
  CcxZenRvIdsHookLibSmm|AgesaModulePkg/Library/CcxZenRvIdsHookLib/Smm/CcxZenRvIdsHookLibSmm.inf
  ApcbRvLib|AgesaModulePkg/Library/ApcbRvLib/ApcbLib.inf
#  ApcbSspLib|AgesaModulePkg/Library/ApcbSspLib/ApcbLib.inf                                                             <SSP|MTS>
  AmdCapsuleLib|AgesaModulePkg/Library/AmdCapsuleLibDxe/AmdCapsuleLibDxe.inf
  AmdTableSmnLib|AgesaModulePkg/Library/AmdTableLib/Dxe/AmdTableSmnDxeLib.inf
  CcxMpServicesLib|AgesaModulePkg/Library/CcxMpServicesSmmLib/CcxMpServicesSmmLib.inf
  RasRvSmmLib|AgesaModulePkg/Library/RasRvSmmLib/RasRvSmmLib.inf

[LibraryClasses.common.PEI_CORE]
  AmdHeapLib|AgesaModulePkg/Library/AmdHeapPeiLib/AmdHeapPeiLib.inf
  AmdTableSmnLib|AgesaModulePkg/Library/AmdTableLib/Pei/AmdTableSmnPeiLib.inf

[LibraryClasses]
  #
  # Agesa specific common libraries
  #
  AmdBaseLib|AgesaModulePkg/Library/AmdBaseLib/AmdBaseLib.inf
  FabricResourceSizeForEachRbLib|AgesaModulePkg/Library/DxeFabricResourceSizeForEachRbLib/DxeFabricResourceSizeForEachRbLib.inf
  FabricResourceReportToGcdLib|AgesaModulePkg/Library/FabricResourceReportToGcdLib/FabricResourceReportToGcdLib.inf
  AmdIdsDebugPrintLib|AgesaModulePkg/Library/AmdIdsDebugPrintLib/AmdIdsDebugPrintLib.inf
  AmdIdsHookLib|AgesaModulePkg/Library/AmdIdsHookLibNull/AmdIdsHookLibNull.inf
  AmdIdsHookExtLib|AgesaModulePkg/Library/AmdIdsExtLibNull/AmdIdsHookExtLibNull.inf
  IdsLib|AgesaModulePkg/Library/IdsNonUefiLib/IdsNonUefiLib.inf
  IdsMiscLib|AgesaModulePkg/Library/IdsMiscLib/IdsMiscLib.inf
  AmdHeapLib|AgesaModulePkg/Library/AmdHeapLibNull/AmdHeapLibNull.inf

  AmdSocBaseLib|AgesaModulePkg/Library/AmdSocBaseLib/AmdSocBaseLib.inf
  AmdErrorLogLib|AgesaModulePkg/Library/AmdErrorLogLib/AmdErrorLogLib.inf
  AmdTableLib|AgesaModulePkg/Library/AmdTableLib/AmdTableLib.inf
  SocCmnIdsHookRvLibPei|AgesaModulePkg/Library/SocCmnIdsHookRvLib/Pei/SocCmnIdsHookRvLibPei.inf
  SocCmnIdsHookRvLibDxe|AgesaModulePkg/Library/SocCmnIdsHookRvLib/Dxe/SocCmnIdsHookRvLibDxe.inf
  BaseCoreLogicalIdLib|AgesaModulePkg/Library/BaseCoreLogicalIdX86Lib/BaseCoreLogicalIdX86Lib.inf
  AmdS3SaveLib|AgesaModulePkg/Library/AmdS3SaveLib/WOS3Save/AmdWOS3SaveLib.inf

  ## PSP Libs
  AmdPspMboxLibV1|AgesaModulePkg/Library/AmdPspMboxLibV1/AmdPspMboxLibV1.inf
  AmdPspBaseLibV1|AgesaModulePkg/Library/AmdPspBaseLibV1/AmdPspBaseLibV1.inf
  AmdPspBaseLibV2|AgesaModulePkg/Library/AmdPspBaseLibV2/AmdPspBaseLibV2.inf
  AmdPspMboxLibV2|AgesaModulePkg/Library/AmdPspMboxLibV2/AmdPspMboxLibV2.inf
  AmdPspApobLib|AgesaModulePkg/Library/AmdPspApobLib/AmdPspApobLib.inf
  AmdPspFtpmLib|AgesaModulePkg/Library/AmdPspFtpmLib/AmdPspFtpmLib.inf
  AmdPspFlashAccLib|AgesaModulePkg/Library/AmdPspFlashAccLibNull/AmdPspFlashAccLibNull.inf
  PspIdsHookLibDxe|AgesaModulePkg/Library/PspIdsHookLib/Dxe/PspIdsHookLibDxe.inf
  ApobZpRvLib|AgesaModulePkg/Library/ApobZpRvLib/ApobZpRvLib.inf
  ApobZpMcmLib|AgesaModulePkg/Library/ApobZpMcmLib/ApobZpMcmLib.inf
  ApobSspLib|AgesaModulePkg/Library/ApobSspLib/ApobSspLib.inf
  ApobDummyLib|AgesaModulePkg/Library/ApobDummyLib/ApobDummyLib.inf

  ## CCX Lib
  CcxBaseX86Lib|AgesaModulePkg/Library/CcxBaseX86Lib/CcxBaseX86Lib.inf
  CcxBistLib|AgesaModulePkg/Library/CcxBistLib/CcxBistLib.inf
  CcxPspLib|AgesaModulePkg/Library/CcxPspLib/CcxPspLib.inf
  CcxHaltLib|AgesaModulePkg/Library/CcxHaltLib/CcxHaltLib.inf
  CcxMicrocodePatchLib|AgesaModulePkg/Library/CcxMicrocodePatchLib/CcxMicrocodePatchLib.inf
  CcxRolesLib|AgesaModulePkg/Library/CcxRolesX86Lib/CcxRolesX86Lib.inf
  CcxPstatesLib|AgesaModulePkg/Library/CcxPstatesZenZpLib/CcxPstatesZenZpLib.inf
  CcxStallLib|AgesaModulePkg/Library/CcxStallZenLib/CcxStallZenLib.inf
  DxeCcxBaseX86ServicesLib|AgesaModulePkg/Library/DxeCcxBaseX86ServicesLib/DxeCcxBaseX86ServicesLib.inf

  ## DF Lib
  FabricPstatesLib|AgesaModulePkg/Library/FabricPstatesZpLib/FabricPstatesZpLib.inf
  BaseFabricTopologyLib|AgesaModulePkg/Library/BaseFabricTopologyZpLib/BaseFabricTopologyZpLib.inf
  PeiFabricTopologyServices2Lib|AgesaModulePkg/Library/PeiFabricTopologyServices2Lib/PeiFabricTopologyServices2Lib.inf
  DxeFabricTopologyServices2Lib|AgesaModulePkg/Library/DxeFabricTopologyServices2Lib/DxeFabricTopologyServices2Lib.inf
  SmmFabricTopologyServices2Lib|AgesaModulePkg/Library/SmmFabricTopologyServices2Lib/SmmFabricTopologyServices2Lib.inf
  FabricRegisterAccLib|AgesaModulePkg/Library/FabricRegisterAccSoc15Lib/FabricRegisterAccSoc15Lib.inf

  FabricResourceManagerLib|AgesaModulePkg/Library/FabricResourceManagerDf1Lib/FabricResourceManager1Lib.inf
  PeiFabricResourceManagerServicesLib|AgesaModulePkg/Library/PeiFabricResourceManagerServicesLib/PeiFabricResourceManagerServicesLib.inf
  DxeFabricResourceManagerServicesLib|AgesaModulePkg/Library/DxeFabricResourceManagerServicesLib/DxeFabricResourceManagerServicesLib.inf

  ## MEM Lib
  AmdMemBaseLib|AgesaModulePkg/Library/Mem/BaseLib/AmdMemBaseLib.inf
  MemRestoreLib|AgesaModulePkg/Library/MemRestoreLib/MemRestoreLib.inf

  ## Gnb Lib
  GnbCommonLib|AgesaModulePkg/Library/GnbCommonLib/GnbCommonLib.inf
  GnbMemAccLib|AgesaModulePkg/Library/GnbMemAccLib/GnbMemAccLib.inf
  GnbIoAccLib|AgesaModulePkg/Library/GnbIoAccLib/GnbIoAccLib.inf
  GnbPciAccLib|AgesaModulePkg/Library/GnbPciAccLib/GnbPciAccLib.inf
  GnbCpuAccLib|AgesaModulePkg/Library/GnbCpuAccLib/GnbCpuAccLib.inf
  GnbPciLib|AgesaModulePkg/Library/GnbPciLib/GnbPciLib.inf
  GnbLib|AgesaModulePkg/Library/GnbLib/GnbLib.inf
  NbioHandleLib|AgesaModulePkg/Library/NbioHandleLib/NbioHandleLib.inf
  NbioIommuIvrsLib|AgesaModulePkg/Library/NbioIommuIvrsLib/NbioIommuIvrsLib.inf
  PcieConfigLib|AgesaModulePkg/Library/PcieConfigLib/PcieConfigLib.inf
  GnbSSocketLib|AgesaModulePkg/Library/GnbSSocketLib/GnbSSocketLib.inf
  GnbRegisterAccZpLib|AgesaModulePkg/Library/GnbRegisterAccZpLib/GnbRegisterAccZpLib.inf
  NbioRegisterAccLib|AgesaModulePkg/Library/NbioRegisterAccLib/NbioRegisterAcc.inf
  NbioSmuV9Lib|AgesaModulePkg/Library/NbioSmuV9Lib/NbioSmuV9Lib.inf
  NbioSmuV10Lib|AgesaModulePkg/Library/NbioSmuV10Lib/NbioSmuV10Lib.inf
  NbioIdsHookRVLib|AgesaModulePkg/Library/NbioIdsHookRVLib/NbioIdsHookRVLib.inf
  DxioLibV1|AgesaModulePkg/Library/DxioLibV1/DxioLibV1.inf
  PcieMiscCommLib|AgesaModulePkg/Library/PcieMiscCommLib/PcieMiscCommLib.inf
  NbioAzaliaLib|AgesaModulePkg/Library/NbioAzaliaLib/NbioAzaliaLib.inf
  SmnAccessLib|AgesaModulePkg/Library/SmnAccessLib/SmnAccessLib.inf

  ## Fch Lib
  FchBaseLib|AgesaModulePkg/Library/FchBaseLib/FchBaseLib.inf
  BaseResetSystemLib|AgesaModulePkg/Library/FchBaseResetSystemLib/FchBaseResetSystemLib.inf
  FchDxeLibV9|AgesaModulePkg/Library/FchDxeLib/FchDxeLib.inf
  FchSmmLibV9|AgesaModulePkg/Library/FchSmmLib/FchSmmLib.inf
  FchSandstoneDxeLib|AgesaModulePkg/Fch/Sandstone/FchSandstoneCore/FchSandstoneLibDxe.inf
  FchInitHookLibDxe|AgesaModulePkg/Library/FchInitHookLib/FchInitHookLibDxe.inf
  FchIdsHookLib|AgesaModulePkg/Library/FchIdsHookLib/FchIdsHookLib.inf
  Mp2I2cLibDxe|AgesaModulePkg/Fch/Sandstone/FchSandstoneI2cDxe/Mp2I2cLibDxe.inf
  ## Ras Lib
  RasRvBaseLib|AgesaModulePkg/Library/RasRvBaseLib/RasRvBaseLib.inf

[Components.IA32]
  AgesaModulePkg/Debug/AmdIdsDebugPrintPei/AmdIdsDebugPrintPei.inf

  ##PSP Drivers
  AgesaModulePkg/Psp/AmdPspPeiV2/AmdPspPeiV2.inf
  AgesaModulePkg/Psp/AmdPspFtpmPei/AmdPspFtpmPei.inf
  AgesaModulePkg/Psp/ApobDrv/ApobZpRvPei/ApobZpRvPei.inf

  AgesaModulePkg/Ccx/Zen/CcxZenRvPei/AmdCcxZenRvPei.inf {
    <LibraryClasses>
    CcxResetTablesLib|AgesaModulePkg/Library/CcxResetTablesRvLib/CcxResetTablesRvLib.inf
    IdsLib|AgesaModulePkg/Library/IdsNonUefiLib/IdsNonUefiLib.inf
    BaseSocLogicalIdXlatLib|AgesaModulePkg/Library/BaseSocLogicalIdXlatRvDieLib/BaseSocLogicalIdXlatRvDieLib.inf
    CcxResetTablesLib|AgesaModulePkg/Library/CcxResetTablesRvLib/CcxResetTablesRvLib.inf
  }
  AgesaModulePkg/Fabric/RV/FabricRvPei/AmdFabricRvPei.inf {
    <LibraryClasses>
    IdsLib|AgesaModulePkg/Library/IdsNonUefiLib/IdsNonUefiLib.inf
    BaseFabricTopologyLib|AgesaModulePkg/Library/BaseFabricTopologyZpLib/BaseFabricTopologyZpLib.inf
    FabricRegisterAccLib|AgesaModulePkg/Library/FabricRegisterAccSoc15Lib/FabricRegisterAccSoc15Lib.inf
    FabricResourceManagerLib|AgesaModulePkg/Library/FabricResourceManagerDf1Lib/FabricResourceManager1Lib.inf
  }
  AgesaModulePkg/Nbio/SMU/AmdNbioSmuV10Pei/AmdNbioSmuV10Pei.inf
  AgesaModulePkg/Nbio/PCIe/AmdNbioPcieRVPei/AmdNbioPcieRVPei.inf {
    <LibraryClasses>
    FabricResourceManagerLib|AgesaModulePkg/Library/FabricResourceManagerDf1Lib/FabricResourceManager1Lib.inf
  }
  AgesaModulePkg/Nbio/NbioBase/AmdNbioBaseRVPei/AmdNbioBaseRVPei.inf
  AgesaModulePkg/Nbio/GFX/AmdNbioGfxRVPei/AmdNbioGfxRVPei.inf
  AgesaModulePkg/Nbio/IOMMU/AmdNbioIOMMUZPPei/AmdNbioIOMMUZPPei.inf {
    <LibraryClasses>
    FabricResourceManagerLib|AgesaModulePkg/Library/FabricResourceManagerDf1Lib/FabricResourceManager1Lib.inf
  }

  AgesaModulePkg/Fch/Sandstone/FchSandstonePei/FchPei.inf
  AgesaModulePkg/Fch/Sandstone/FchSandstoneSmbusPei/Smbus.inf
  AgesaModulePkg/Mem/AmdMemAm4ZpPei/AmdMemAm4ZpPei.inf
  AgesaModulePkg/Soc/AmdSocFp5RvPei/AmdSocFp5RvPei.inf {
    <LibraryClasses>
    FabricResourceInitLib|AgesaModulePkg/Library/FabricResourceManagerDf1Lib/FabricResourceInit1Lib.inf
    FabricResourceManagerLib|AgesaModulePkg/Library/FabricResourceManagerDf1Lib/FabricResourceManager1Lib.inf
    FabricRegisterAccLib|AgesaModulePkg/Library/FabricRegisterAccSoc15Lib/FabricRegisterAccSoc15Lib.inf
    BaseFabricTopologyLib|AgesaModulePkg/Library/BaseFabricTopologyZpLib/BaseFabricTopologyZpLib.inf
    BaseSocketLogicalIdLib|AgesaModulePkg/Library/BaseSocketLogicalIdRvDieLib/BaseSocketLogicalIdRvDieLib.inf
    BaseSocLogicalIdXlatLib|AgesaModulePkg/Library/BaseSocLogicalIdXlatRvDieLib/BaseSocLogicalIdXlatRvDieLib.inf
    PeiSocBistLib|AgesaModulePkg/Library/PeiSocBistRvLib/PeiSocBistRvLib.inf
  }
  AgesaModulePkg/Mem/AmdMemChanXLatZpPei/MemChanXLatZpPei.inf
  AgesaModulePkg/Mem/AmdMemSmbiosV2RvPei/MemSmbiosV2Pei.inf {
    <LibraryClasses>
    AmdMemSmbiosV2Lib|AgesaModulePkg/Library/MemSmbiosV2RvLib/MemSmbiosV2Lib.inf
  }
  AgesaModulePkg/Mem/AmdMemRestorePei/MemRestorePei.inf
  AgesaModulePkg/ErrorLog/AmdErrorLogPei/AmdErrorLogPei.inf
  AgesaModulePkg/Nbio/EarlyPhase/AmdNbioEarlyPhaseRVPei/AmdNbioEarlyPhaseRVPei.inf
  AgesaModulePkg/Mem/AmdMemoryHobInfoPeimRv/AmdMemoryHobInfoPeim.inf
  AgesaModulePkg/Universal/Version/AmdVersionPei/AmdVersionPei.inf

[Components.X64]
  AgesaModulePkg/Debug/AmdIdsDebugPrintDxe/AmdIdsDebugPrintDxe.inf
  AgesaModulePkg/Mem/AmdMemAm4Dxe/AmdMemAm4Dxe.inf
  AgesaModulePkg/Mem/AmdMemSmbiosV2Dxe/AmdMemSmbiosV2Dxe.inf
  AgesaModulePkg/Mem/AmdMemRestoreDxe/MemRestoreDxe.inf
  AgesaModulePkg/Psp/ApcbDrv/ApcbRvDxe/ApcbRvDxe.inf{
    <LibraryClasses>
    ApcbRvLib|AgesaModulePkg/Library/ApcbRvLib/ApcbLib.inf
  }
  AgesaModulePkg/Psp/ApcbDrv/ApcbRvSmm/ApcbRvSmm.inf{
    <LibraryClasses>
    ApcbRvLib|AgesaModulePkg/Library/ApcbRvLib/ApcbLib.inf
  }

#  AgesaModulePkg/Psp/ApcbDrv/ApcbSspDxe/ApcbSspDxe.inf{
#    <LibraryClasses>
#    ApcbSspLib|AgesaModulePkg/Library/ApcbSspLib/ApcbLib.inf
#  }                                                                                                                    <SSP|MTS>
#  AgesaModulePkg/Psp/ApcbDrv/ApcbSspSmm/ApcbSspSmm.inf{
#    <LibraryClasses>
#    ApcbSspLib|AgesaModulePkg/Library/ApcbSspLib/ApcbLib.inf
#  }                                                                                                                    <SSP|MTS>
  AgesaModulePkg/Psp/AmdPspDxeV2Rv/AmdPspDxeV2.inf

  AgesaModulePkg/Psp/AmdPspP2CmboxV2/AmdPspP2CmboxV2.inf

  AgesaModulePkg/Psp/AmdPspSmmV2/AmdPspSmmV2.inf

  AgesaModulePkg/Psp/AmdPspFtpmDxe/AmdPspFtpmDxe.inf
  AgesaModulePkg/Psp/AmdHstiV2/AmdHstiV2.inf

  AgesaModulePkg/Psp/ApobDrv/ApobZpRvDxe/ApobZpRvDxe.inf

  AgesaModulePkg/Ccx/Zen/CcxZenRvDxe/AmdCcxZenRvDxe.inf {
    <LibraryClasses>
    IdsLib|AgesaModulePkg/Library/IdsNonUefiLib/IdsNonUefiLib.inf
    CcxResetTablesLib|AgesaModulePkg/Library/CcxResetTablesRvLib/CcxResetTablesRvLib.inf
    BaseSocLogicalIdXlatLib|AgesaModulePkg/Library/BaseSocLogicalIdXlatRvDieLib/BaseSocLogicalIdXlatRvDieLib.inf
    CcxIdsCustomPstatesLib|AgesaModulePkg/Library/CcxIdsCustomPstateZenLib/CcxIdsCustomPstatesZenLib.inf
    CcxSetMcaLib|AgesaModulePkg/Library/CcxSetMcaRvLib/CcxSetMcaRvLib.inf
    CcxResetTablesLib|AgesaModulePkg/Library/CcxResetTablesRvLib/CcxResetTablesRvLib.inf
    CcxSmbiosLib|AgesaModulePkg/Library/CcxSmbiosZenRvLib/CcxSmbiosZenRvLib.inf
  }
  AgesaModulePkg/Ccx/Zen/CcxZenRvSmm/AmdCcxZenRvSmm.inf {
    <LibraryClasses>
    BaseSocLogicalIdXlatLib|AgesaModulePkg/Library/BaseSocLogicalIdXlatRvDieLib/BaseSocLogicalIdXlatRvDieLib.inf
    CcxSetMcaLib|AgesaModulePkg/Library/CcxSetMcaRvLib/CcxSetMcaRvLib.inf
  }
  AgesaModulePkg/Fabric/RV/FabricRvDxe/AmdFabricRvDxe.inf {
    <LibraryClasses>
    IdsLib|AgesaModulePkg/Library/IdsNonUefiLib/IdsNonUefiLib.inf
    FabricResourceManagerLib|AgesaModulePkg/Library/FabricResourceManagerDf1Lib/FabricResourceManager1Lib.inf
    BaseSocLogicalIdXlatLib|AgesaModulePkg/Library/BaseSocLogicalIdXlatRvDieLib/BaseSocLogicalIdXlatRvDieLib.inf
    FabricRegisterAccLib|AgesaModulePkg/Library/FabricRegisterAccSoc15Lib/FabricRegisterAccSoc15Lib.inf
    BaseFabricTopologyLib|AgesaModulePkg/Library/BaseFabricTopologyZpLib/BaseFabricTopologyZpLib.inf
  }
  AgesaModulePkg/Fabric/RV/FabricRvSmm/AmdFabricRvSmm.inf {
    <LibraryClasses>
    AmdS3SaveLib|AgesaModulePkg/Library/AmdS3SaveLib/WOS3Save/AmdWOS3SaveLib.inf
  }
  AgesaModulePkg/Soc/AmdSocFp5RvDxe/AmdSocFp5RvDxe.inf {
    <LibraryClasses>
    AmdS3SaveLib|AgesaModulePkg/Library/AmdS3SaveLib/WOS3Save/AmdWOS3SaveLib.inf
    BaseSocketLogicalIdLib|AgesaModulePkg/Library/BaseSocketLogicalIdRvDieLib/BaseSocketLogicalIdRvDieLib.inf
    BaseSocLogicalIdXlatLib|AgesaModulePkg/Library/BaseSocLogicalIdXlatRvDieLib/BaseSocLogicalIdXlatRvDieLib.inf
    FabricRegisterAccLib|AgesaModulePkg/Library/FabricRegisterAccSoc15Lib/FabricRegisterAccSoc15Lib.inf
    BaseFabricTopologyLib|AgesaModulePkg/Library/BaseFabricTopologyZpLib/BaseFabricTopologyZpLib.inf
    AmdIdsHookExtLib|AgesaModulePkg/Library/AmdIdsExtLibNull/AmdIdsHookExtLibNull.inf
  }
  AgesaModulePkg/ErrorLog/AmdErrorLogDxe/AmdErrorLogDxe.inf

  ## Gnb Dxe Drivers
  AgesaModulePkg/Nbio/NbioBase/AmdNbioBaseRVDxe/AmdNbioBaseRVDxe.inf {
    <LibraryClasses>
    FabricResourceManagerLib|AgesaModulePkg/Library/FabricResourceManagerDf1Lib/FabricResourceManager1Lib.inf
    FabricRegisterAccLib|AgesaModulePkg/Library/FabricRegisterAccSoc15Lib/FabricRegisterAccSoc15Lib.inf
    BaseFabricTopologyLib|AgesaModulePkg/Library/BaseFabricTopologyZpLib/BaseFabricTopologyZpLib.inf
  }
  AgesaModulePkg/Nbio/SMU/AmdNbioSmuV10Dxe/AmdNbioSmuV10Dxe.inf
  AgesaModulePkg/Nbio/PCIe/AmdNbioPcieRVDxe/AmdNbioPcieRVDxe.inf
  AgesaModulePkg/Nbio/IOMMU/AmdNbioIOMMURVDxe/AmdNbioIOMMURVDxe.inf {
    <LibraryClasses>
    FabricResourceManagerLib|AgesaModulePkg/Library/FabricResourceManagerDf1Lib/FabricResourceManager1Lib.inf
  }
  AgesaModulePkg/Nbio/GFX/AmdNbioGfxRVDxe/AmdNbioGfxRVDxe.inf
  AgesaModulePkg/Nbio/NbioALib/AmdNbioAlibRVDxe/AmdNbioAlibRVDxe.inf

  ## Fch Dxe Drivers
  AgesaModulePkg/Fch/Sandstone/FchSandstoneDxe/FchDxe.inf
  AgesaModulePkg/Fch/Sandstone/FchSandstoneSmm/FchSmm.inf
  AgesaModulePkg/Fch/Sandstone/FchSandstoneSmbusDxe/SmbusLight.inf
  AgesaModulePkg/Fch/Sandstone/FchSandstoneCf9ResetDxe/Cf9Reset.inf
  AgesaModulePkg/Fch/Sandstone/FchSandstoneLegacyInterruptDxe/LegacyInterrupt.inf
  AgesaModulePkg/Fch/Sandstone/FchSandstoneSmmControlDxe/SmmControl.inf
  AgesaModulePkg/Fch/Sandstone/FchSandstoneSmmDispatcher/FchSmmDispatcher.inf
  AgesaModulePkg/Fch/Sandstone/FchSandstoneComplement/FchSSSataD3Cold/FchSSSataD3ColdSmm.inf

  # Universal
  AgesaModulePkg/Universal/Smbios/AmdSmbiosDxe.inf
  AgesaModulePkg/Universal/Acpi/AmdAcpiDxe.inf
  AgesaModulePkg/Universal/AmdSmmCommunication/AmdSmmCommunication.inf
  AgesaModulePkg/Universal/Version/AmdVersionDxe/AmdVersionDxe.inf

  ## Ras Dxe Drivers
  AgesaModulePkg/Ras/AmdRasRvApeiDxe/AmdRasRvApeiDxe.inf
  AgesaModulePkg/Ras/AmdRasRvDxe/AmdRasRvDxe.inf
  AgesaModulePkg/Ras/AmdRasRvSmm/AmdRasRvSmm.inf

[PcdsFixedAtBuild]
  # AMD AGESA PI Name & Version string
  gEfiAmdAgesaModulePkgTokenSpaceGuid.PcdAmdPackageString|"AGESA!V9\0EmbeddedR2KPI-FP5_1.0.0.0"

[PcdsDynamicDefault]
  # Gnb Gbs Override
  gEfiAmdAgesaModulePkgTokenSpaceGuid.PcdIommuL1ClockGatingEnable|TRUE
  gEfiAmdAgesaModulePkgTokenSpaceGuid.PcdIommuL2ClockGatingEnable|TRUE
  gEfiAmdAgesaModulePkgTokenSpaceGuid.PcdIOHCClkGatingSupport|TRUE
  gEfiAmdAgesaModulePkgTokenSpaceGuid.PcdCfgSstunlClkGating|TRUE

  # CCX and Fabric Default
  gEfiAmdAgesaPkgTokenSpaceGuid.PcdAmdCStateMode|1
  gEfiAmdAgesaPkgTokenSpaceGuid.PcdAmdAcpiC3Ctrl|0x00
  
  # RAS Feature Control
  gEfiAmdAgesaPkgTokenSpaceGuid.PcdNbioDeferredErrThreshEn|TRUE
  gEfiAmdAgesaPkgTokenSpaceGuid.PcdNbioDeferredErrThreshCount|0x00
