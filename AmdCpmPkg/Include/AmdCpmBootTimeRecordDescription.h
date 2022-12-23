/*****************************************************************************
 *
 * Copyright 2012 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 * ***************************************************************************
 */

#ifndef _AMD_CPM_BOOT_TIME_RECORD_DESCRIPTIONS
  #define _AMD_CPM_BOOT_TIME_RECORD_DESCRIPTIONS
  #define BOOT_TIMER_RECORD_RELEASE_VERSION 0x0001000ul
  #define TSC_TIMER_TICK_ENABLE 1   //use TSC Timer tick
  //#define ACPI_TIMER_TICK_ENABLE 0
  #define MAXIMUM_RECORDS 100
  #define MAX_IDS_PERFORMANCE_UNIT_NUM 100
  #define CMOS_BOOT_TIME_STORAGE          0x70
  #define CMOS_BOOT_TIME_S3RESUME_STORAGE 0x78
  #define CMOS_BOOT_TIME_IDS_STORAGE    0x80
  #define CMOS_BOOT_TIME_IDS_S3_STORAGE   0x88
  #define BTR_HIDDEN_End                0

/// Boot Time Record Test Points
  typedef enum {
    AtStartRecording                                              = 0x01, ///< Start Recording
    AtBeforeBootToOS                                              = 0x02, ///< INT19
    AtAsmTransferControl                                          = 0x03, ///< AtAsmTransferControl
    AtInitializeAmdProcessorInitPeim                              = 0x04, ///< AtInitializeAmdProcessorInitPeim
    AtAgesaDxeDriverEntryPoint                                    = 0x05, ///< AtAgesaDxeDriverEntryPoint
    AtDiscoverMemory                                              = 0x06, ///< AtDiscoverMemory
    AtPlatformBdsInit                                             = 0x07, ///< AtPlatformBdsInit
    AtVBIOSInitial                                                = 0x08, ///< AtVBIOSInitial
    AtExitBootServices                                            = 0x09, ///< AtExitBootServices
    BeginCRBPEIInit                                               = 0x10, ///< BeginCRBPEIInit
    EndCRBPEIInit                                                 = 0x11, ///< EndCRBPEIInit
    BeginCpuPeiEntry                                              = 0x12, ///< BeginCpuPeiEntry
    EndCpuPeiEntry                                                = 0x13, ///< EndCpuPeiEntry
    BeginSbInterfaceInit                                          = 0x14, ///< BeginSbInterfaceInit
    EndSbInterfaceInit                                            = 0x15, ///< EndSbInterfaceInit
    BeginAmdSbInterface                                           = 0x16, ///< BeginAmdSbInterface
    EndAmdSbInterface                                             = 0x17, ///< EndAmdSbInterface
    BeginAmdSbPeiInit                                             = 0x18, ///< BeginAmdSbPeiInit
    EndAmdSbPeiInit                                               = 0x19, ///< EndAmdSbPeiInit
    BeginSmBusPei                                                 = 0x1A, ///< BeginSmBusPei
    EndSmBusPei                                                   = 0x1B, ///< EndSmBusPei
    BeginInstallSpdPpiInit                                        = 0x1C, ///< BeginInstallSpdPpiInit
    EndInstallSpdPpiInit                                          = 0x1D, ///< EndInstallSpdPpiInit
    BeginSr5690PeiInit                                            = 0x1E, ///< BeginSr5690PeiInit
    EndSr5690PeiInit                                              = 0x1F, ///< EndSr5690PeiInit
    BeginAodPeiInit                                               = 0x20, ///< BeginAodPeiInit
    EndAodPeiInit                                                 = 0x21, ///< EndAodPeiInit
    DXEIPLStart                                                   = 0xFF, ///< DXEIPLStart
    BeginInitializeAmdProcessorInitPeim                           = 0x700, ///< BeginInitializeAmdProcessorInitPeim
    EndInitializeAmdProcessorInitPeim                             = 0x701, ///< EndInitializeAmdProcessorInitPeim
    BeginAmdCpuInitialize                                         = 0x702, ///< BeginAmdCpuInitialize
    EndAmdCpuInitialize                                           = 0x703, ///< EndAmdCpuInitialize
    BeginAmdInitReset                                             = 0x704, ///< BeginAmdInitReset
    EndAmdInitReset                                               = 0x705, ///< EndAmdInitReset
    BeginAmdInitEarly                                             = 0x706, ///< BeginAmdInitEarly
    EndAmdInitEarly                                               = 0x707, ///< EndAmdInitEarly
    BeginDiscoverMemory                                           = 0x708, ///< BeginDiscoverMemory
    EndDiscoverMemory                                             = 0x709, ///< EndDiscoverMemory
    BeginInitializeMemory                                         = 0x70A, ///< BeginInitializeMemory
    EndInitializeMemory                                           = 0x70B, ///< EndInitializeMemory
    BeginAmdInitPost                                              = 0x70C, ///< BeginAmdInitPost
    EndAmdInitPost                                                = 0x70D, ///< EndAmdInitPost
    BeginBuildHobInfo                                             = 0x70E, ///< BeginBuildHobInfo
    EndBuildHobInfo                                               = 0x70F, ///< EndBuildHobInfo
    BeginInvokeAmdInitResume                                      = 0x710, ///< BeginInvokeAmdInitResume
    EndInvokeAmdInitResume                                        = 0x711, ///< EndInvokeAmdInitResume
    BeginAmdInitResume                                            = 0x712, ///< BeginAmdInitResume
    EndAmdInitResume                                              = 0x713, ///< EndAmdInitResume
    BeginInvokeAmdInitS3LateRestore                               = 0x714, ///< BeginInvokeAmdInitS3LateRestore
    EndInvokeAmdInitS3LateRestore                                 = 0x715, ///< EndInvokeAmdInitS3LateRestore
    BeginAmdS3LateRestore                                         = 0x716, ///< BeginAmdS3LateRestore
    EndAmdS3LateRestore                                           = 0x717, ///< EndAmdS3LateRestore
    BeginAgesaDxeDriverEntryPoint                                 = 0x718, ///< BeginAgesaDxeDriverEntryPoint
    EndAgesaDxeDriverEntryPoint                                   = 0x719, ///< EndAgesaDxeDriverEntryPoint
    BeginAmdCpuCreateProcessorTables                              = 0x71A, ///< BeginAmdCpuCreateProcessorTables
    EndAmdCpuCreateProcessorTables                                = 0x71B, ///< EndAmdCpuCreateProcessorTables
    BeginInvokeAmdInitMid                                         = 0x71C, ///< BeginInvokeAmdInitMid
    EndInvokeAmdInitMid                                           = 0x71D, ///< EndInvokeAmdInitMid
    BeginInvokeAmdInitLate                                        = 0x71E, ///< BeginInvokeAmdInitLate
    EndInvokeAmdInitLate                                          = 0x71F, ///< EndInvokeAmdInitLate
    BeginAgesaS3Save                                              = 0x720, ///< BeginAgesaS3Save
    EndAgesaS3Save                                                = 0x721, ///< EndAgesaS3Save
    BeginRebuildHeap                                              = 0x723, ///< BeginRebuildHeap
    EndRebuildHeap                                                = 0x724, ///< EndRebuildHeap
    BeginAmdInitEnv                                               = 0x725, ///< BeginAmdInitEnv
    EndAmdInitEnv                                                 = 0x726, ///< EndAmdInitEnv
    BeginAmdInitMid                                               = 0x727, ///< BeginAmdInitMid
    EndAmdInitMid                                                 = 0x728, ///< EndAmdInitMid
    BeginAmdInitLate                                              = 0x729, ///< BeginAmdInitLate
    EndAmdInitLate                                                = 0x72A, ///< EndAmdInitLate
    BeginAmdS3Save                                                = 0x72B, ///< BeginAmdS3Save
    EndAmdS3Save                                                  = 0x72C, ///< EndAmdS3Save
    BeginFchPeiInit                                               = 0x730, ///< BeginFchPeiInit
    EndFchPeiInit                                                 = 0x731, ///< EndFchPeiInit
    BeginFchUpdateBootMode                                        = 0x732, ///< BeginFchUpdateBootMode
    EndFchUpdateBootMode                                          = 0x733, ///< EndFchUpdateBootMode
    BeginFchPeiAux                                                = 0x734, ///< BeginFchPeiAux
    EndFchPeiAux                                                  = 0x735, ///< EndFchPeiAux
    BeginLibFchPeiAuxInitialization                               = 0x736, ///< BeginLibFchPeiAuxInitialization
    EndLibFchPeiAuxInitialization                                 = 0x737, ///< EndLibFchPeiAuxInitialization
    BeginFchPeiBootTimer                                          = 0x738, ///< BeginFchPeiBootTimer
    EndFchPeiBootTimer                                            = 0x739, ///< EndFchPeiBootTimer
    BeginFchPeiDisUsbPort                                         = 0x73A, ///< BeginFchPeiDisUsbPort
    EndFchPeiDisUsbPort                                           = 0x73B, ///< EndFchPeiDisUsbPort
    BeginFchPeiAuxGpio                                            = 0x73C, ///< BeginFchPeiAuxGpio
    EndFchPeiAuxGpio                                              = 0x73D, ///< EndFchPeiAuxGpio
    BeginFchPeiGpioRead                                           = 0x73E, ///< BeginFchPeiGpioRead
    EndFchPeiGpioRead                                             = 0x73F, ///< EndFchPeiGpioRead
    BeginFchPeiOscOutClockSel                                     = 0x740, ///< BeginFchPeiOscOutClockSel
    EndFchPeiOscOutClockSel                                       = 0x741, ///< EndFchPeiOscOutClockSel
    BeginFchDxeInit                                               = 0x742, ///< BeginFchDxeInit
    EndFchDxeInit                                                 = 0x743, ///< EndFchDxeInit
    BeginFchDxeAuxInit                                            = 0x744, ///< BeginFchDxeAuxInit
    EndFchDxeAuxInit                                              = 0x745, ///< EndFchDxeAuxInit
    BeginFchDxeAuxGpio                                            = 0x746, ///< BeginFchDxeAuxGpio
    EndFchDxeAuxGpio                                              = 0x747, ///< EndFchDxeAuxGpio
    BeginFchDxeAuxGpioRead                                        = 0x748, ///< BeginFchDxeAuxGpioRead
    EndFchDxeAuxGpioRead                                          = 0x749, ///< EndFchDxeAuxGpioRead
    BeginFchDxeEsataPortSet                                       = 0x74A, ///< BeginFchDxeEsataPortSet
    EndFchDxeEsataPortSet                                         = 0x74B, ///< EndFchDxeEsataPortSet
    BeginFchDxeDisUsbPort                                         = 0x74C, ///<
    EndFchDxeDisUsbPort                                           = 0x74D, ///<
    BeginFchDxeAuxBootTimer                                       = 0x74E, ///<
    EndFchDxeAuxBootTimer                                         = 0x74F, ///<
    BeginAmdGetNumberPirqs                                        = 0x750, ///<
    EndAmdGetNumberPirqs                                          = 0x751, ///<
    BeginAmdGetLocation                                           = 0x752, ///<
    EndAmdGetLocation                                             = 0x753, ///<
    BeginAmdReadPirq                                              = 0x754, ///<
    EndAmdReadPirq                                                = 0x755, ///<
    BeginAmdInstallLegacyInterrupt                                = 0x756, ///<
    EndAmdInstallLegacyInterrupt                                  = 0x757, ///<
    BeginAmdWritePirq                                             = 0x758, ///<
    EndAmdWritePirq                                               = 0x759, ///<
    BeginSmmControlDxePreInit                                     = 0x75A, ///<
    EndSmmControlDxePreInit                                       = 0x75B, ///<
    BeginClearSmi                                                 = 0x75C, ///<
    EndClearSmi                                                   = 0x75D, ///<
    BeginAmdTrigger                                               = 0x75E, ///<
    EndAmdTrigger                                                 = 0x75F, ///<
    BeginAmdGetRegisterInfo                                       = 0x760, ///<
    EndAmdGetRegisterInfo                                         = 0x761, ///<
    BeginVariableVirtualAddressChangeCallBack                     = 0x762, ///<
    EndVariableVirtualAddressChangeCallBack                       = 0x763, ///<
    BeginAmdInstallSmmControl                                     = 0x764, ///<
    EndAmdInstallSmmControl                                       = 0x765, ///<
    BeginOemCustomizeInitReset                                    = 0x200, ///<
    EndOemCustomizeInitReset                                      = 0x201, ///<
    BeginOemCustomizeInitEarly                                    = 0x202, ///<
    EndOemCustomizeInitEarly                                      = 0x203, ///<
    BeginOemCustomizeInitPost                                     = 0x204, ///<
    EndOemCustomizeInitPost                                       = 0x205, ///<
    BeginOemCustomizeInitResume                                   = 0x206, ///<
    EndOemCustomizeInitResume                                     = 0x207, ///<
    BeginOemCustomizeS3LateRestore                                = 0x208, ///<
    EndOemCustomizeS3LateRestore                                  = 0x209, ///<
    BeginOemHookEndInitReset                                      = 0x20A, ///<
    EndOemHookEndInitReset                                        = 0x20B, ///<
    BeginOemHookEndInitEarly                                      = 0x20C, ///<
    EndOemHookEndInitEarly                                        = 0x20D, ///<
    BeginOemHookEndInitPost                                       = 0x20E, ///<
    EndOemHookEndInitPost                                         = 0x20F, ///<
    BeginOemHookEndInitResume                                     = 0x210, ///<
    EndOemHookEndInitResume                                       = 0x211, ///<
    BeginOemHookEndS3LateRestore                                  = 0x212, ///<
    EndOemHookEndS3LateRestore                                    = 0x213, ///<
    BeginOemCustomizeInitEnv                                      = 0x214, ///<
    EndOemCustomizeInitEnv                                        = 0x215, ///<
    BeginOemCustomizeInitMid                                      = 0x216, ///<
    EndOemCustomizeInitMid                                        = 0x217, ///<
    BeginOemCustomizeInitLate                                     = 0x218, ///<
    EndOemCustomizeInitLate                                       = 0x219, ///<
    BeginOemCustomizeS3Save                                       = 0x21A, ///<
    EndOemCustomizeS3Save                                         = 0x21B, ///<
    BeginOemHookEndInitEnv                                        = 0x21C, ///<
    EndOemHookEndInitEnv                                          = 0x21D, ///<
    BeginOemHookEndInitMid                                        = 0x21E, ///<
    EndOemHookEndInitMid                                          = 0x21F, ///<
    BeginOemHookEndInitLate                                       = 0x220, ///<
    EndOemHookEndInitLate                                         = 0x221, ///<
    BeginAgesaReadSpd                                             = 0x222, ///<
    EndAgesaReadSpd                                               = 0x223, ///<
    BeginVBIOSInitial                                             = 0x224, ///<
    EndVBIOSInitial                                               = 0x225, ///<
    BeginOemHookAfterInitReset                                    = 0x226, ///<
    EndOemHookAfterInitReset                                      = 0x227, ///<
    BeginOemHookAfterInitEarly                                    = 0x228, ///<
    EndOemHookAfterInitEarly                                      = 0x229, ///<
    BeginOemHookAfterInitPost                                     = 0x22A, ///<
    EndOemHookAfterInitPost                                       = 0x22B, ///<
    BeginOemHookAfterS3LateRestore                                = 0x22C, ///<
    EndOemHookAfterS3LateRestore                                  = 0x22D, ///<
    BeginOemHookAfterInitEnv                                      = 0x22E, ///<
    EndOemHookAfterInitEnv                                        = 0x22F, ///<
    BeginOemHookAfterInitMid                                      = 0x230, ///<
    EndOemHookAfterInitMid                                        = 0x231, ///<
    BeginOemHookAfterInitLate                                     = 0x232, ///<
    EndOemHookAfterInitLate                                       = 0x233, ///<
    BeginSetVGAMode                                               = 0x234, ///<
    EndSetVGAMode                                                 = 0x235, ///<
    BeginSetVBEMode                                               = 0x236, ///<
    EndSetVBEMode                                                 = 0x237, ///<
    BeginOemAgesaSaveS3Info                                       = 0x238, ///<
    EndOemAgesaSaveS3Info                                         = 0x239, ///<
    BeginOemAgesaGetS3Info                                        = 0x23A, ///<
    EndOemAgesaGetS3Info                                          = 0x23B, ///<
    BeginS3RestoreConfig                                          = 0x300, ///<
    EndS3RestoreConfig                                            = 0x301, ///<
    BeginS3BootScriptTable                                        = 0x302, ///<
    EndS3BootScriptTable                                          = 0x303, ///<
    EndS3WakingVector                                             = 0x304, ///<
    BeginPlatformBdsInit                                          = 0x400, ///<
    EndPlatformBdsInit                                            = 0x401, ///<
    BeginPlatformBdsConnectConsole                                = 0x402, ///<
    EndPlatformBdsConnectConsole                                  = 0x403, ///<
    BeginPlatformBdsForceActiveVga                                = 0x404, ///<
    EndPlatformBdsForceActiveVga                                  = 0x405, ///<
    BeginPlatformBDSConnectCRTerminal                             = 0x406, ///<
    EndPlatformBDSConnectCRTerminal                               = 0x407, ///<
    BeginBdsLibConnectAllDefaultConsoles                          = 0x408, ///<
    EndBdsLibConnectAllDefaultConsoles                            = 0x409, ///<
    BeginBdsLibConnectUsbHID                                      = 0x40A, ///<
    EndBdsLibConnectUsbHID                                        = 0x40B, ///<
    BeginPlatformBdsPolicyBehavior                                = 0x40C, ///<
    EndPlatformBdsPolicyBehavior                                  = 0x40D, ///<
    BeginBdsInitialize                                            = 0x40E, ///<
    EndBdsInitialize                                              = 0x40F, ///<
    BeginLoadDefaultCheck                                         = 0x410, ///<
    EndLoadDefaultCheck                                           = 0x411, ///<
    BeginBdsEntry                                                 = 0x412, ///<
    EndBdsEntry                                                   = 0x413, ///<
    BeginUpdateBootMessage                                        = 0x414, ///<
    EndUpdateBootMessage                                          = 0x415, ///<
    BeginBdsLibLoadDrivers                                        = 0x416, ///<
    EndBdsLibLoadDrivers                                          = 0x417, ///<
    BeginPlatformBdsPolicyBehaviort                               = 0x418, ///<
    EndPlatformBdsPolicyBehaviort                                 = 0x419, ///<
    BeginBdsBootDeviceSelect                                      = 0x41A, ///<
    EndBdsBootDeviceSelect                                        = 0x41B, ///<
    BeginPlatformBdsNoConsoleAction                               = 0x41C, ///<
    EndPlatformBdsNoConsoleAction                                 = 0x41D, ///<
    BeginPlatformBdsBootDisplayDevice                             = 0x41E, ///<
    EndPlatformBdsBootDisplayDevice                               = 0x41F, ///<
    BeginPlatformBdsDiagnostics                                   = 0x420, ///<
    EndPlatformBdsDiagnostics                                     = 0x421, ///<
    BeginBdsLibConnectLegacyRoms                                  = 0x422, ///<
    EndBdsLibConnectLegacyRoms                                    = 0x423, ///<
    BeginPlatformBdsConnectSequence                               = 0x424, ///<
    EndPlatformBdsConnectSequence                                 = 0x425, ///<
    BeginShowAllDevice                                            = 0x426, ///<
    EndShowAllDevice                                              = 0x427, ///<
    BeginBdsLibEnumerateAllBootOption                             = 0x428, ///<
    EndBdsLibEnumerateAllBootOption                               = 0x429, ///<
    BeginEnterSetup                                               = 0x42A, ///<
    EndEnterSetup                                                 = 0x42B, ///<
    BeginPlatformBdsBootSelection                                 = 0x42C, ///<
    EndPlatformBdsBootSelection                                   = 0x42D, ///<
    BeginPlatformBdsPredictBootOption                             = 0x42E, ///<
    EndPlatformBdsPredictBootOption                               = 0x42F, ///<
    BeginHotKeyEvent                                              = 0x430, ///<
    EndHotKeyEvent                                                = 0x431, ///<
    BeginBdsLibOnEndOfBdsBootSelection                            = 0x432, ///<
    EndBdsLibOnEndOfBdsBootSelection                              = 0x433, ///<
    BeginOemHotKeyCallback                                        = 0x434, ///<
    EndOemHotKeyCallback                                          = 0x435, ///<
    BeginPCIEnumeration                                           = 0x436, ///<
    EndPCIEnumeration                                             = 0x437, ///<
    BeginNbPeiInit                                                = 0x438, ///<
    EndNbPeiInit                                                  = 0x439, ///<
    AtAspmOverrideEntryPoint                                      = 0x500, ///<
    BeginPciBusDriverBindingStart                                 = 0x501, ///<
    EndPciBusDriverBindingStart                                   = 0x502, ///<
    BeginBiosVideoDriverBindingStart                              = 0x503, ///<
    EndBiosVideoDriverBindingStart                                = 0x504, ///<
    BeginLpcDriverStart                                           = 0x505, ///<
    EndLpcDriverStart                                             = 0x506, ///<
    BeginIsaBusControllerDriverStart                              = 0x507, ///<
    EndIsaBusControllerDriverStart                                = 0x508, ///<
    BeginBiosKeyboardDriverBindingStart                           = 0x509, ///<
    EndBiosKeyboardDriverBindingStart                             = 0x50A, ///<
    BeginConPlatformTextInDriverBindingStart                      = 0x50B, ///<
    EndConPlatformTextInDriverBindingStart                        = 0x50C, ///<
    BeginConSplitterAbsolutePointerDriverBindingStart             = 0x50D, ///<
    EndConSplitterAbsolutePointerDriverBindingStart               = 0x50E, ///<
    BeginPS2MouseDriverStart                                      = 0x50F, ///<
    EndPS2MouseDriverStart                                        = 0x510, ///<
    BeginGraphicsConsoleControllerDriverStart                     = 0x511, ///<
    EndGraphicsConsoleControllerDriverStart                       = 0x512, ///<
    BeginUsbBusControllerDriverStart                              = 0x513, ///<
    EndUsbBusControllerDriverStart                                = 0X514, ///<
    BeginSataControllerStart                                      = 0x515, ///<
    EndSataControllerStart                                        = 0x516, ///<
    BeginPlatformDriverBindingStart                               = 0x517, ///<
    EndPlatformDriverBindingStart                                 = 0x518, ///<
    BeginDiskIoDriverBindingStart                                 = 0x519, ///<
    EndDiskIoDriverBindingStart                                   = 0x51A, ///<
    BeginPartitionDriverBindingStart                              = 0x51B, ///<
    EndPartitionDriverBindingStart                                = 0x51C, ///<
    BeginFatDriverBindingStart                                    = 0x51D, ///<
    EndFatDriverBindingStart                                      = 0x51E, ///<
    BeginExitBootServices                                         = 0x51F, ///<
    EndExitBootServices                                           = 0x520, ///<
    BeginCoreConnectSingleController                              = 0x600, ///<
    EndCoreConnectSingleController                                = 0x601, ///<
    BeginAmdCpmInitPeimDriver                                     = 0xC00, ///<
    EndAmdCpmInitPeimDriver                                       = 0xC01, ///<
    BeginAmdCpmInitBeforeS3LateRestore                            = 0xC02, ///<
    EndAmdCpmInitBeforeS3LateRestore                              = 0xC03, ///<
    BeginAmdCpmInitDxeDriver                                      = 0xC04, ///<
    EndAmdCpmInitDxeDriver                                        = 0xC05, ///<
    BeginAmdCpmLoadCommonSsdt                                     = 0xC06, ///<
    EndAmdCpmLoadCommonSsdt                                       = 0xC07, ///<
    BeginAmdCpmInitSmmDriver                                      = 0xC08, ///<
    EndAmdCpmInitSmmDriver                                        = 0xC09, ///<
    BeginAmdCpmAcpiThermalFanPeimDriver                           = 0xC10, ///<
    EndAmdCpmAcpiThermalFanPeimDriver                             = 0xC11, ///<
    BeginAmdCpmAcpiThermalFanDxeDriver                            = 0xC12, ///<
    EndAmdCpmAcpiThermalFanDxeDriver                              = 0xC13, ///<
    BeginAmdCpmLoadThermalFanSsdt                                 = 0xC14, ///<
    EndAmdCpmLoadThermalFanSsdt                                   = 0xC15, ///<
    BeginAmdCpmAdaptiveS4PeimDriver                               = 0xC16, ///<
    EndAmdCpmAdaptiveS4PeimDriver                                 = 0xC17, ///<
    BeginAmdCpmAdaptiveS4DxeDriver                                = 0xC18, ///<
    EndAmdCpmAdaptiveS4DxeDriver                                  = 0xC19, ///<
    BeginAmdCpmAdaptiveS4SmmDriver                                = 0xC1A, ///<
    EndAmdCpmAdaptiveS4SmmDriver                                  = 0xC1B, ///<
    BeginAmdCpmDisplayFeaturePeimDriver                           = 0xC1C, ///<
    EndAmdCpmDisplayFeaturePeimDriver                             = 0xC1D, ///<
    BeginAmdCpmDisplayFeatureDxeDriver                            = 0xC1E, ///<
    EndAmdCpmDisplayFeatureDxeDriver                              = 0xC1F, ///<
    BeginAmdCpmDisplayFeatureMidInit                              = 0xC20, ///<
    EndAmdCpmDisplayFeatureMidInit                                = 0xC21, ///<
    BeginAmdCpmDisplayFeatureLateInit                             = 0xC22, ///<
    EndAmdCpmDisplayFeatureLateInit                               = 0xC23, ///<
    BeginAmdCpmDisplayFeatureSmmDriver                            = 0xC24, ///<
    EndAmdCpmDisplayFeatureSmmDriver                              = 0xC25, ///<
    BeginAmdCpmDisplayFeatureRestore                              = 0xC26, ///<
    EndAmdCpmDisplayFeatureRestore                                = 0xC27, ///<
    BeginAmdCpmGpioInitPeimDriver                                 = 0xC28, ///<
    EndAmdCpmGpioInitPeimDriver                                   = 0xC29, ///<
    BeginAmdCpmGpioInitStage1                                     = 0xC2A, ///<
    EndAmdCpmGpioInitStage1                                       = 0xC2B, ///<
    BeginAmdCpmGpioInitStage2                                     = 0xC2C, ///<
    EndAmdCpmGpioInitStage2                                       = 0xC2D, ///<
    BeginAmdCpmSetMemVoltage                                      = 0xC2E, ///<
    EndAmdCpmSetMemVoltage                                        = 0xC2F, ///<
    BeginAmdCpmGpioInitDxeDriver                                  = 0xC30, ///<
    EndAmdCpmGpioInitDxeDriver                                    = 0xC31, ///<
    BeginAmdCpmGpioInitSmmDriver                                  = 0xC32, ///<
    EndAmdCpmGpioInitSmmDriver                                    = 0xC33, ///<
    BeginAmdCpmGpioInitS3Restore                                  = 0xC34, ///<
    EndAmdCpmGpioInitS3Restore                                    = 0xC35, ///<
    BeginAmdCpmPcieInitPeimDriver                                 = 0xC36, ///<
    EndAmdCpmPcieInitPeimDriver                                   = 0xC37, ///<
    BeginAmdCpmPcieReset                                          = 0xC38, ///<
    EndAmdCpmPcieReset                                            = 0xC39, ///<
    BeginAmdCpmPcieInitDxeDriver                                  = 0xC3A, ///<
    EndAmdCpmPcieInitDxeDriver                                    = 0xC3B, ///<
    BeginAmdCpmZeroPowerOddPeimDriver                             = 0xC3C, ///<
    EndAmdCpmZeroPowerOddPeimDriver                               = 0xC3D, ///<
    BeginAmdCpmZeroPowerOddDxeDriver                              = 0xC3E, ///<
    EndAmdCpmZeroPowerOddDxeDriver                                = 0xC3F, ///<
    BeginAmdCpmOemInitPeimDriver                                  = 0xC50, ///<
    EndAmdCpmOemInitPeimDriver                                    = 0xC51, ///<
    BeginAmdCpmOemTableOverride                                   = 0xC60, ///<
    EndAmdCpmOemTableOverride                                     = 0xC61, ///<
  } BOOT_TIME_RECORD_TP_DESCRIPTION;
#endif
