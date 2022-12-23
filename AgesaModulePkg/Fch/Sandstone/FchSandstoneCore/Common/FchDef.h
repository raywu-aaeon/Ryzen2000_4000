/* $NoKeywords:$ */
/**
 * @file
 *
 * FCH routine definition
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: FCH
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 10:28:05 -0800 (Tue, 09 Dec 2014) $
 *
 */
/*
*****************************************************************************
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
#ifndef _FCH_DEF_H_
#define _FCH_DEF_H_

AGESA_STATUS  FchInitReset (IN FCH_RESET_DATA_BLOCK *FchParams);
AGESA_STATUS  FchInitEnv (IN FCH_DATA_BLOCK *FchDataBlock);
AGESA_STATUS  FchInitMid (IN FCH_DATA_BLOCK *FchDataBlock);
AGESA_STATUS  FchInitLate (IN FCH_DATA_BLOCK *FchDataBlock);

UINT32        ReadAlink (IN UINT32 Index, IN AMD_CONFIG_PARAMS *StdHeader);
VOID          WriteAlink (IN UINT32 Index, IN UINT32 Data, IN AMD_CONFIG_PARAMS *StdHeader);
VOID          RwAlink (IN UINT32 Index, IN UINT32 AndMask, IN UINT32 OrMask, IN AMD_CONFIG_PARAMS *StdHeader);
VOID          ReadMem (IN UINT32 Address, IN UINT8 OpFlag, IN VOID *ValuePtr);
VOID          WriteMem (IN UINT32 Address, IN UINT8 OpFlag, IN VOID *ValuePtr);
VOID          RwMem (IN UINT32 Address, IN UINT8 OpFlag, IN UINT32 Mask, IN UINT32 Data);
VOID          ReadPci (IN UINT32 Address, IN UINT8 OpFlag, IN VOID *Value, IN AMD_CONFIG_PARAMS *StdHeader);
VOID          WritePci (IN UINT32 Address, IN UINT8 OpFlag, IN VOID *Value, IN AMD_CONFIG_PARAMS *StdHeader);
VOID          RwPci (IN UINT32 Address, IN UINT8 OpFlag, IN UINT32 Mask, IN UINT32  Data, IN AMD_CONFIG_PARAMS *StdHeader);
VOID          ProgramPciByteTable (IN REG8_MASK* pPciByteTable, IN UINT16 dwTableSize, IN AMD_CONFIG_PARAMS *StdHeader);
VOID          ProgramFchAcpiMmioTbl (IN ACPI_REG_WRITE  *pAcpiTbl, IN AMD_CONFIG_PARAMS *StdHeader);
VOID          ProgramFchSciMapTbl (IN SCI_MAP_CONTROL  *pSciMapTbl, IN FCH_RESET_DATA_BLOCK *FchResetDataBlock);
VOID          ProgramFchGpioTbl (IN GPIO_CONTROL  *pGpioTbl, IN FCH_RESET_DATA_BLOCK *FchResetDataBlock);
VOID          ProgramFchSataPhyTbl (IN SATA_PHY_CONTROL  *pSataPhyTbl, IN FCH_RESET_DATA_BLOCK *FchResetDataBlock);
VOID          GetChipSysMode (IN VOID *Value, IN AMD_CONFIG_PARAMS *StdHeader);
BOOLEAN       IsImcEnabled (IN AMD_CONFIG_PARAMS *StdHeader);
VOID          ReadPmio (IN UINT8 Address, IN UINT8 OpFlag, IN VOID *Value, IN AMD_CONFIG_PARAMS *StdHeader);
VOID          WritePmio (IN UINT8 Address, IN UINT8 OpFlag, IN VOID *Value, IN AMD_CONFIG_PARAMS *StdHeader);
VOID          RwPmio (IN UINT8 Address, IN UINT8 OpFlag, IN UINT32 AndMask, IN UINT32 OrMask, IN AMD_CONFIG_PARAMS *StdHeader);
VOID          ReadPmio2 (IN UINT8 Address, IN UINT8 OpFlag, IN VOID *Value, IN AMD_CONFIG_PARAMS *StdHeader);
VOID          WritePmio2 (IN UINT8 Address, IN UINT8 OpFlag, IN VOID *Value, IN AMD_CONFIG_PARAMS *StdHeader);
VOID          RwPmio2 (IN UINT8 Address, IN UINT8  OpFlag, IN UINT32 AndMask, IN UINT32 OrMask, IN AMD_CONFIG_PARAMS *StdHeader);
VOID          ReadBiosram (IN UINT8 Address, IN UINT8 OpFlag, IN VOID *Value, IN AMD_CONFIG_PARAMS *StdHeader);
VOID          WriteBiosram (IN UINT8 Address, IN UINT8 OpFlag, IN VOID *Value, IN AMD_CONFIG_PARAMS *StdHeader);
VOID          GetFchAcpiMmioBase (OUT UINT32 *AcpiMmioBase, IN AMD_CONFIG_PARAMS *StdHeader);
VOID          GetFchAcpiPmBase (OUT  UINT16 *AcpiPmBase, IN AMD_CONFIG_PARAMS *StdHeader);
UINT8         ReadFchSleepType (IN AMD_CONFIG_PARAMS *StdHeader);
UINT8         ReadFchChipsetRevision (IN AMD_CONFIG_PARAMS *StdHeader);
UINT32        ReadSocType (VOID);
BOOLEAN       CheckZP (VOID);
BOOLEAN       FchCheckRvOpnB4 (VOID);
BOOLEAN       FchCheckPicasso (VOID);
RAVEN2_TYPE   FchCheckRaven2Type(VOID);
BOOLEAN       FchCheckAm4PackageType(VOID);
BOOLEAN       FchCheckFt5PackageType(VOID);

VOID          FchSmnRead (IN UINT32 IohcBus, IN UINT32 SmnAddress, IN UINT32 *Value, IN AMD_CONFIG_PARAMS *StdHeader);
VOID          FchSmnWrite (IN UINT32 IohcBus, IN UINT32 SmnAddress, IN UINT32 *Value, IN AMD_CONFIG_PARAMS *StdHeader);
VOID          FchSmnRW (IN UINT32 IohcBus, IN UINT32 SmnAddress, IN UINT32 AndMask, IN UINT32 OrMask, IN AMD_CONFIG_PARAMS *StdHeader);
VOID          FchSmnRead8 (IN UINT32 IohcBus, IN UINT32 SmnAddress, IN UINT8 *Value8, IN AMD_CONFIG_PARAMS *StdHeader);
VOID          FchSmnWrite8 (IN UINT32 IohcBus, IN UINT32 SmnAddress, IN UINT8 *Value8, IN AMD_CONFIG_PARAMS *StdHeader);
VOID          FchSmnRW8 (IN UINT32 IohcBus, IN UINT32 SmnAddress, IN UINT8 AndMask, IN UINT8 OrMask, IN AMD_CONFIG_PARAMS *StdHeader);

///
/// Fch Ab Routines
///
///  Pei Phase
///
VOID  FchInitResetAb (IN VOID* FchDataPtr);
VOID  FchProgramAbPowerOnReset (IN VOID* FchDataPtr);
///
///  Dxe Phase
///
VOID  FchInitEnvAb (IN VOID* FchDataPtr);
VOID  FchInitEnvAbSpecial (IN VOID* FchDataPtr);
VOID  FchInitMidAb (IN VOID* FchDataPtr);
VOID  FchInitLateAb (IN VOID* FchDataPtr);
///
///  Other Public Routines
///
VOID  FchInitEnvAbLinkInit (IN VOID* FchDataPtr);
VOID  FchAbLateProgram (IN VOID* FchDataPtr);

///
/// Fch Pcie Routines
///
///
///  Dxe Phase
///
VOID  ProgramPcieNativeMode (IN VOID* FchDataPtr);


///
/// Fch HwAcpi Routines
///
///  Pei Phase
///
VOID  FchInitResetHwAcpiP    (IN VOID  *FchDataPtr);
VOID  FchInitResetHwAcpi     (IN VOID  *FchDataPtr);
VOID  ProgramFchHwAcpiResetP (IN VOID  *FchDataPtr);
VOID  FchInitEnableWdt       (IN VOID  *FchDataPtr);
VOID  ProgramResetRtcExt     (IN VOID  *FchDataPtr);
///
///  Dxe Phase
///
VOID  FchInitEnvHwAcpiP                      (IN VOID  *FchDataPtr);
VOID  FchInitEnvHwAcpi                       (IN VOID  *FchDataPtr);
VOID  ProgramEnvPFchAcpiMmio                 (IN VOID *FchDataPtr);
VOID  ProgramFchEnvHwAcpiPciReg              (IN VOID *FchDataPtr);
VOID  ProgramSpecificFchInitEnvAcpiMmio      (IN VOID *FchDataPtr);
VOID  ProgramFchEnvClkCntl                   (IN VOID *FchDataPtr);
VOID  ProgramFchEnvSpreadSpectrum            (IN VOID *FchDataPtr);
VOID  ProgramFchEnvAoacInit                  (IN VOID *FchDataPtr);
VOID  PciIntVwInit                           (IN VOID *FchDataPtr);
VOID  FchInternalDeviceIrqInit               (IN VOID *FchDataPtr);
VOID  FchInitMidHwAcpi      (IN VOID  *FchDataPtr);
VOID  FchInitLateHwAcpi     (IN VOID  *FchDataPtr);

///
///  Other Public Routines
///
VOID HpetInit               (IN VOID  *FchDataPtr);
VOID MtC1eEnable            (IN VOID  *FchDataPtr);
VOID GcpuRelatedSetting     (IN VOID  *FchDataPtr);
VOID StressResetModeLate    (IN VOID  *FchDataPtr);
VOID FchEventInitUsbGpe     (IN VOID  *FchDataPtr);
VOID FchAl2ahbInit          (IN VOID  *FchDataPtr);
VOID FchI2cUartInit         (IN VOID  *FchDataPtr);
VOID FchI2cUartInitLate     (IN VOID  *FchDataPtr);

///
/// Fch SATA Routines
///
///  Pei Phase
///
VOID  FchInitResetSata          (IN VOID  *FchDataPtr);
VOID  FchInitResetSataProgram   (IN UINT32 DieBusNum, IN VOID  *FchDataPtr);
///
///  Dxe Phase
///
VOID  FchInitMidSata                   (IN VOID  *FchDataPtr);
VOID  FchInitEnvSata                   (IN VOID  *FchDataPtr);
VOID  FchInitEnvProgramSata            (IN UINT32 DieBusNum, IN VOID  *FchDataPtr);
VOID  FchInitMidProgramSataRegs        (IN UINT32 DieBusNum, IN VOID  *FchDataPtr);
VOID  FchInitLateProgramSataRegs       (IN UINT32 DieBusNum, IN VOID  *FchDataPtr);

VOID  FchInitEnvSataAhci        (IN UINT32 DieBusNum, IN VOID *FchDataPtr);
VOID  FchInitLateSata           (IN VOID  *FchDataPtr);
VOID  FchInitMidSataAhci        (IN UINT32 DieBusNum, IN VOID  *FchDataPtr);
VOID  FchInitLateSataAhci       (IN UINT32 DieBusNum, IN VOID  *FchDataPtr);
VOID  FchInitEnvSataRaid        (IN UINT32 DieBusNum, IN VOID *FchDataPtr);
VOID  FchInitMidSataRaid        (IN UINT32 DieBusNum, IN VOID  *FchDataPtr);
VOID  FchInitLateSataRaid       (IN UINT32 DieBusNum, IN VOID  *FchDataPtr);

VOID  SataAhciSetDeviceNumMsi     (IN UINT32 DieBusNum, IN VOID  *FchDataPtr);
VOID  SataRaidSetDeviceNumMsi     (IN UINT32 DieBusNum, IN VOID  *FchDataPtr);
VOID  SataSetIrqIntResource (IN VOID  *FchDataPtr, IN AMD_CONFIG_PARAMS *StdHeader);

VOID  SataSetDeviceNumMsi (IN UINT32 DieBusNum, IN VOID  *FchDataPtr);
VOID  FchSataSetDeviceNumMsi (IN UINT32 DieBusNum, IN VOID  *FchDataPtr);
VOID  ShutdownUnconnectedSataPortClock (IN UINT32 DieBusNum, IN VOID *FchDataPtr);
VOID  SataDriveDetection (IN VOID *FchDataPtr, IN UINT32 *Bar5Ptr);
VOID  FchSataDriveDetection (IN VOID *FchDataPtr, IN UINT32 *Bar5Ptr);
VOID  SataBar5RegSet (IN UINT32 DieBusNum, IN  VOID  *FchDataPtr);
VOID  SataSetPortGenMode (IN UINT32 DieBusNum, IN  VOID  *FchDataPtr);
VOID  FchInitEnvSataRaidProgram  (IN VOID  *FchDataPtr);

UINT32 SataGetBusCNumber (IN UINT32 DieBusNum, IN AMD_CONFIG_PARAMS *StdHeader);
UINT32 SataSetBusCTempNumber (IN AMD_CONFIG_PARAMS *StdHeader);
UINT32 SataEnableBusCMmioDecode (IN AMD_CONFIG_PARAMS *StdHeader);
VOID  SataRestoreBusCMmioDecode (IN UINT32 SavedCmdReg, IN AMD_CONFIG_PARAMS *StdHeader);
VOID  SataBar5setting (IN VOID *FchDataPtr, IN UINT32 SataBusNum, IN UINT32 *Bar5Ptr);
VOID  SataEnableWriteAccess (IN UINT32 DieBusNum, IN VOID *FchDataPtr);
VOID  SataDisableWriteAccess (IN UINT32 DieBusNum, IN VOID *FchDataPtr);

VOID  FchSSSataInitPortOffline (IN UINT32 DieBusNum, IN UINT32 PortNum, IN VOID *FchDataPtr);
VOID  FchSSSataInitPortActive  (IN UINT32 DieBusNum, IN UINT32 PortNum, IN VOID *FchDataPtr);
VOID  FchSSSataInitEnableErr (IN UINT32 DieBusNum, IN VOID *FchDataPtr);
VOID  FchSSSataInitEsata (IN UINT32 DieBusNum, IN VOID *FchDataPtr);
VOID  FchSSSataInitDevSlp (IN UINT32 DieBusNum, IN VOID *FchDataPtr);
VOID  FchSSSataInitMpssMap (IN UINT32 DieBusNum, IN VOID *FchDataPtr);
VOID  FchSSSataInitRsmuCtrl (IN UINT32 DieBusNum, IN VOID *FchDataPtr);
VOID  FchSSSataInitCtrlReg (IN UINT32 DieBusNum, IN VOID *FchDataPtr);
VOID  FchSSSataInitMMC (IN UINT32 DieBusNum, IN VOID *FchDataPtr);
VOID  FchSSSataSetPortGenMode (IN UINT32 DieBusNum, IN  VOID  *FchDataPtr);
VOID  FchSSSataShutdownUnconnectedSataPortClock (IN UINT32 DieBusNum, IN VOID *FchDataPtr);
VOID  FchSSSataGpioInitial (IN UINT32 DieBusNum, IN VOID *FchDataPtr);
VOID  FchSSSataAutoShutdownController (IN UINT32 DieBusNum, IN VOID *FchDataPtr);
VOID  FchSSSataDisableSata (IN UINT32 DieBusNum, IN VOID *FchDataPtr);

VOID FchSataD3ColdOverrideDevSlpPad ();
VOID FchSataD3ColdRemoveOverrideDevSlpPad ();
VOID FchSataD3ColdOfflineMode ();
VOID FchSataD3ColdPollingOffline ();
VOID FchSataD3ColdSaveRegisters ();
VOID FchSataD3ColdRestoreRegisters ();
VOID FchSataD3ColdBlockReset ();
VOID FchSataD3ColdUnBlockReset ();
VOID FchSataD3ColdEnable100MClk ();
VOID FchSataD3ColdBlockOOB ();
VOID FchSataD3ColdUnBlockOOB ();
BOOLEAN FchSataD3ColdClockOn ();
BOOLEAN FchSataD3ColdPowerStateOn ();
VOID FchSataD3ColdPowerDown ();
VOID FchSataD3ColdPowerUp ();
///
/// FCH USB Controller Public Function
///
///  Pei Phase
///
VOID  FchInitResetUsb            (IN VOID  *FchDataPtr);
VOID  FchInitResetXhci           (IN VOID  *FchDataPtr);
VOID  FchInitResetXhciProgram    (IN VOID  *FchDataPtr);
///
///  Dxe Phase
///
VOID  FchInitEnvUsb              (IN VOID  *FchDataPtr);
VOID  FchInitMidUsb              (IN VOID  *FchDataPtr);
VOID  FchInitLateUsb             (IN VOID  *FchDataPtr);
VOID  FchInitEnvUsbXhci          (IN VOID  *FchDataPtr);
VOID  FchInitMidUsbXhci          (IN VOID  *FchDataPtr);
VOID  FchInitLateUsbXhci         (IN VOID  *FchDataPtr);
///
///  Other Public Routines
///
VOID FchRVXhci0InitBootProgram    (IN VOID *FchDataPtr);
VOID FchRVXhci0InitS3ExitProgram  (IN VOID *FchDataPtr);
VOID FchRVXhci0InitS3EntryProgram (IN VOID *FchDataPtr);
VOID FchRVXhci1InitBootProgram    (IN VOID *FchDataPtr);
VOID FchRVXhci1InitS3ExitProgram  (IN VOID *FchDataPtr);
VOID FchRVXhci1InitS3EntryProgram (IN VOID *FchDataPtr);
VOID FchRVXhciInitBootProgram    (IN UINT8 Controller, IN VOID *FchDataPtr);
VOID FchRVXhciInitS3ExitProgram  (IN UINT8 Controller, IN VOID *FchDataPtr);
VOID FchRVXhciInitS3EntryProgram (IN UINT8 Controller, IN VOID *FchDataPtr);
VOID FchRVXhciProgramInternalRegStepOne (IN UINT8 Controller, IN VOID *FchDataPtr);
VOID FchRVXhciProgramInternalRegStepTwo (IN UINT8 Controller, IN VOID *FchDataPtr);
VOID FchRVXhciProgramInternalRegStepThree (IN UINT8 Controller, IN VOID *FchDataPtr);
VOID FchRVXhciInitSsid (IN UINT32 DieBusNum, IN UINT32 Ssid);
BOOLEAN FchRVXhci0DisablePort (IN UINT32 USB3DisableMap, IN UINT32 USB2DisableMap);
BOOLEAN FchRVXhci1DisablePort (IN UINT32 USB3DisableMap, IN UINT32 USB2DisableMap);
BOOLEAN FchRV0Xhci0OCmapping (IN UINT8 Port, IN UINT8 OCPin);
BOOLEAN FchRV0Xhci1OCmapping (IN UINT8 Port, IN UINT8 OCPin);
BOOLEAN FchRVXhciSmuService (IN UINT32 RequestId);
BOOLEAN FchRVXhciSmuUsbPowerService (IN UINT32 UsbId );

BOOLEAN
FchRVXhciSmuUsbConfigUpdate (
  IN  UINT32    smn_register,
  IN  UINT32    smn_mask,
  IN  UINT32    smn_data,
  IN  UINT32    smn_group
  );
BOOLEAN FchRVXhciSmuUsbCmdTrap   (IN VOID *FchDataPtr);
VOID FchRVUsb3InitBootProgram    (IN VOID *FchDataPtr);
VOID FchRVUsb3InitS3ExitProgram  (IN VOID *FchDataPtr);
VOID FchRVUsb3InitS3EntryProgram (IN VOID *FchDataPtr);
///
/// Fch Sd Routines
///
VOID  FchInitEnvSd  (IN VOID  *FchDataPtr);
VOID  FchInitMidSd  (IN VOID  *FchDataPtr);
VOID  FchInitLateSd (IN VOID  *FchDataPtr);

///
///  Other Public Routines
///

VOID FchInitEnvSdProgram (IN VOID  *FchDataPtr);

///
/// Fch Spi Routines
///
///  Pei Phase
///
VOID  FchInitResetSpi        (IN VOID  *FchDataPtr);
VOID  FchInitResetLpc        (IN VOID  *FchDataPtr);
VOID  FchInitResetLpcProgram (IN VOID  *FchDataPtr);
///
///  Dxe Phase
///
VOID  FchInitEnvSpi          (IN VOID  *FchDataPtr);
VOID  FchInitMidSpi          (IN VOID  *FchDataPtr);
VOID  FchInitLateSpi         (IN VOID  *FchDataPtr);
VOID  FchInitEnvLpc          (IN VOID  *FchDataPtr);
VOID  FchInitMidLpc          (IN VOID  *FchDataPtr);
VOID  FchInitLateLpc         (IN VOID  *FchDataPtr);
VOID  FchInitEnvLpcProgram   (IN VOID  *FchDataPtr);
///
///  Other Public Routines
///
VOID  FchSpiUnlock       (IN VOID  *FchDataPtr);
VOID  FchSpiLock         (IN VOID  *FchDataPtr);

///
/// Fch ESPI Routines
///
///
VOID  FchInitResetEspi   (IN VOID  *FchDataPtr);
VOID  FchinitSSEspiEnableIo80 (IN  BOOLEAN  Enable);
VOID  FchinitSSEspiEnableKbc6064 (IN BOOLEAN  Enable);
VOID  FchinitSSEspiTimer (IN UINT32 EspiBase);
VOID  FchinitSSEspiIoMux ();
VOID  FchinitSSEspiEc0 (IN VOID  *FchDataPtr);
VOID  FchinitSSEspiIoDecode (IN  VOID  *FchDataPtr);
VOID  FchinitSSEspiMmioDecode (IN  VOID  *FchDataPtr);
UINT32 getESPIBase ();


///
/// Fch eMMC Routines
///
///  Pei Phase
///
VOID  FchInitResetEmmc (IN VOID* FchDataPtr);
///
///  Dxe Phase
///
VOID  FchInitEnvEmmc (IN VOID* FchDataPtr);
VOID  FchInitMidEmmc (IN VOID* FchDataPtr);
VOID  FchInitLateEmmc (IN VOID* FchDataPtr);

///
/// Fch XgbE Routines
///
///  Pei Phase
///

///
///  Dxe Phase
///
VOID  FchInitEnvXGbe (IN VOID* FchDataPtr);

VOID  FchSsXgbePortClockGate (IN UINT32 DieBusNum, IN UINT8 Port);
VOID  FchSsXgbePortPlatformConfig (IN UINT32 DieBusNum, IN UINT8 PortNum, IN UINT32 SystemPort, IN VOID *PortData);
VOID  FchSsXgbePortMacAddress (IN UINT32 DieBusNum, IN UINT8 PortNum, IN VOID *MacData);
VOID  FchSsXgbePortPtpInit (IN UINT32 DieBusNum, IN UINT8 PortNum, IN VOID *PortData);
VOID  FchSsXgbePadEnable (IN UINT32 DieBusNum, IN VOID *XgbeData);
/*--------------------------- Documentation Pages ---------------------------*/
VOID  FchStall (IN UINT32 uSec, IN AMD_CONFIG_PARAMS *StdHeader);
VOID  CimFchStall (IN UINT32 uSec, IN AMD_CONFIG_PARAMS *StdHeader);
VOID  FchPciReset (IN AMD_CONFIG_PARAMS *StdHeader);
VOID  OutPort80 (IN UINT32 pcode, IN AMD_CONFIG_PARAMS *StdHeader);
VOID  OutPort1080 (IN UINT32 pcode, IN AMD_CONFIG_PARAMS *StdHeader);
VOID  GetEfuseStatus (IN VOID* Value, IN AMD_CONFIG_PARAMS *StdHeader);
VOID  TurnOffCG2 (OUT VOID);
VOID  BackUpCG2 (OUT VOID);
VOID  FchCopyMem (IN VOID* pDest, IN VOID* pSource, IN UINTN Length);
VOID* GetRomSigPtr (IN UINTN* RomSigPtr, IN AMD_CONFIG_PARAMS *StdHeader);
VOID  RwXhciIndReg (IN UINT32 Index, IN UINT32 AndMask, IN UINT32 OrMask, IN AMD_CONFIG_PARAMS *StdHeader);
VOID  RwXhci0IndReg (IN UINT32 Index, IN UINT32 AndMask, IN UINT32 OrMask, IN AMD_CONFIG_PARAMS *StdHeader);
VOID  RwXhci1IndReg (IN UINT32 Index, IN UINT32 AndMask, IN UINT32 OrMask, IN AMD_CONFIG_PARAMS *StdHeader);
VOID  ReadXhci0Phy (IN UINT32 Port, IN UINT32 Address, IN UINT32 *Value, IN AMD_CONFIG_PARAMS *StdHeader);
VOID  ReadXhci1Phy (IN UINT32 Port, IN UINT32 Address, IN UINT32 *Value, IN AMD_CONFIG_PARAMS *StdHeader);
VOID  RwSsicIndReg (IN UINT32 Index, IN UINT32 AndMask, IN UINT32 OrMask, IN AMD_CONFIG_PARAMS *StdHeader);
VOID  AcLossControl (IN UINT8 AcLossControlValue);
VOID  FchVgaInit (OUT VOID);
VOID  RecordFchConfigPtr (IN UINT32 FchConfigPtr);
VOID  ValidateFchVariant (IN VOID  *FchDataPtr);
VOID  RecordSmiStatus (IN AMD_CONFIG_PARAMS *StdHeader);
VOID  ClearAllSmiStatus (IN AMD_CONFIG_PARAMS *StdHeader);
BOOLEAN  IsExternalClockMode (IN VOID  *FchDataPtr);
VOID  SbSleepTrapControl (IN BOOLEAN SleepTrap);

AGESA_STATUS
FchSpiTransfer (
  IN       UINT8    PrefixCode,
  IN       UINT8    Opcode,
  IN  OUT  UINT8    *DataPtr,
  IN       UINT8    *AddressPtr,
  IN       UINT8    Length,
  IN       BOOLEAN  WriteFlag,
  IN       BOOLEAN  AddressFlag,
  IN       BOOLEAN  DataFlag,
  IN       BOOLEAN  FinishedFlag
  );

BOOLEAN
FchConfigureSpiDeviceDummyCycle (
  IN       UINT32     DeviceID,
  IN       UINT8      SpiMode
  );

UINT32
FchReadSpiId (
  IN       BOOLEAN    Flag
  );

VOID
FchConfigureSpiControllerDummyCycle (
  );

BOOLEAN
FchPlatformSpiQe (
  IN       VOID     *FchDataPtr
  );

VOID
ProgramPMEDis (
  IN       UINT8     dbBusNo,
  IN       BOOLEAN   PMEDis
  );

VOID
ProgramLpcSdPins (
  IN       BOOLEAN   Sd_en
  );
  
VOID
ProgramLpcEmmcPins (
  IN       BOOLEAN   eMMC_en
  );

VOID
RestoreAmbaEmmc2D0 (
  );

BOOLEAN
AmdSpiSemaphoreControl  (
  SPI_SEMAPHORE_ID SemaphoreId,
  UINTN TimeoutInMicrosecond
  );

VOID
FchEmmcOnRecovery (
  IN        VOID      *FchDataPtr
  );
VOID
ProgramXhciPmeEn (
  IN  VOID          *FchDataPtr
  );
#endif


