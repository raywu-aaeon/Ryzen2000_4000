/* $NoKeywords:$ */
/**
 * @file
 *
 * Nbio PCIe AER Protocol prototype definition
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Nbio
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-25 21:00:43 -0600 (Wed, 25 Feb 2015) $
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

#ifndef _NBIO_PCIE_AER_PROTOCOL_H_
#define _NBIO_PCIE_AER_PROTOCOL_H_


// TODO : Potentially remove these defines if they are not used, and leave them to the architecture
// specific GNB PPR defines. Otherwise they are duplicates...
/// PCIe Correctable Error Mask
typedef union {
  struct {                                                            ///<
    UINT32                  BadTLPMask :1;                            ///<
    UINT32                  BadDLLPMask :1;                           ///<
    UINT32                  ReplayNumberRolloverMask :1;              ///<
    UINT32                  ReplayTimerTimeoutMask :1;                ///<
    UINT32                  AdvisoryNonFatalErrorMask :1;             ///<
  } Field;                                                            ///<
  UINT32 Value;                                                       ///<
} PCIe_AER_CORRECTABLE_MASK;

/// PCIe Unorrectable Error Mask
typedef union {
  struct {                                                            ///<
    UINT32                  DataLinkProtocolErrorMask :1;             ///<
    UINT32                  PoisonedTLPMask :1;                       ///<
    UINT32                  CompletionTimeoutMask :1;                 ///<
    UINT32                  CompleterAbortMask :1;                    ///<
    UINT32                  UnexpectedCompletionMask :1;              ///<
    UINT32                  MalTlpMask:1 ;                            ///<
    UINT32                  ECRCErrorMask :1;                         ///<
    UINT32                  UnsupportedRequestErrorMask :1;           ///<
    UINT32                  AcsViolationMask:1 ;                      ///<
  } Field;                                                            ///<
  UINT32 Value;                                                       ///<
} PCIe_AER_UNCORRECTABLE_MASK;

/// PCIe Unorrectable Error Severity
typedef union {
  struct {                                                            ///<
    UINT32                  DataLinkProtocolErrorSeverity :1;         ///<
    UINT32                  PoisonedTLPSeverity :1;                   ///<
    UINT32                  CompletionTimeoutSeverity :1;             ///<
    UINT32                  CompleterAbortSeverity :1;                ///<
    UINT32                  UnexpectedCompletionSeverity :1;          ///<
    UINT32                  MalTlpSeverity:1 ;                        ///<
    UINT32                  ECRCErrorSeverity :1;                     ///<
    UINT32                  UnsupportedRequestErrorSeverity :1;       ///<
    UINT32                  AcsViolationSeverity:1 ;                  ///<
  } Field;                                                            ///<
  UINT32 Value;                                                       ///<
} PCIe_AER_UNCORRECTABLE_SEVERITY;

/// PCIe AER Port Configuration
typedef struct {
  UINT8                           AerEnable;                          ///< General per-port enable, 0=disable 1=enable
  UINT8                           PciBus;                             ///< PCI Bus Number
  UINT8                           PciDev;                             ///< PCI Device Number
  UINT8                           PciFunc;                            ///< PCI Function Number
  PCIe_AER_CORRECTABLE_MASK       CorrectableMask;                    ///< Per-port mask for correctable errors
  PCIe_AER_UNCORRECTABLE_MASK     UncorrectableMask;                  ///< Per-port mask for uncorrectable errors
  PCIe_AER_UNCORRECTABLE_SEVERITY UncorrectableSeverity;              ///< Per-port severity configuration for uncorrectable errors
} PCIe_PORT_AER_CONFIG;

///
/// Forward declaration for the AMD_NBIO_PCIE_AER_PROTOCOL
///
typedef struct _AMD_NBIO_PCIE_AER_PROTOCOL AMD_NBIO_PCIE_AER_PROTOCOL;


//
// Protocol Definitions
//
/**
  Enable or disable Advanced Error Reporting feature
  This
    A pointer to the AMD_NBIO_PCIE_AER_PROTOCOL instance.
  PcieAerSetting
    A pointer to store the address of the PCIe port AER config structure
**/
typedef
EFI_STATUS
(EFIAPI * AMD_NBIO_PCIE_AER_FEATURE) (
  IN  AMD_NBIO_PCIE_AER_PROTOCOL  *This,
  IN  PCIe_PORT_AER_CONFIG        *PcieAerSetting
);

///
/// The Dxe of PCIE AER Services
///
struct _AMD_NBIO_PCIE_AER_PROTOCOL {
  AMD_NBIO_PCIE_AER_FEATURE     SetPcieAerFeature; ///<
};

extern EFI_GUID gAmdNbioPcieAerProtocolGuid;

#endif

