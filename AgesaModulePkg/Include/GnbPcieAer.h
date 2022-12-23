/* $NoKeywords:$ */
/**
 * @file
 *
 * PCIe AER definitions.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: NBIO
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-25 21:00:43 -0600 (Wed, 25 Feb 2015) $
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

*
*/

#ifndef _GNB_PCIE_AER_H_
#define _GNB_PCIE_AER_H_

#pragma pack (push, 1)
/// PCIe Correctable Error Mask
typedef union {
  struct {                                                            ///<
    UINT32                  Reserved_5_0 :6;                          ///<
    UINT32                  BadTLPMask :1;                            ///< [6] BadTlpMask
    UINT32                  BadDLLPMask :1;                           ///< [7] BadDllpMask
    UINT32                  ReplayNumberRolloverMask :1;              ///< [8] ReplayNumRolloverMask
    UINT32                  Reserved_11_9 :3;                         ///<
    UINT32                  ReplayTimerTimeoutMask :1;                ///< [12] ReplayTimerTimeoutMask
    UINT32                  AdvisoryNonFatalErrorMask :1;             ///< [13] AdvisoryNonfatalErrMask
    UINT32                  Reserved_31_14 :18;                       ///<
  } Field;                                                            ///<
  UINT32 Value;                                                       ///<
} NBIO_PCIe_AER_CORRECTABLE_MASK;

/// PCIe Unorrectable Error Mask
typedef union {
  struct {                                                            ///<
    UINT32                  Reserved_3_0 :4;                          ///<
    UINT32                  DataLinkProtocolErrorMask :1;             ///< [4] DlpErrMask
    UINT32                  Reserved_11_5 :7;                         ///<
    UINT32                  PoisonedTLPMask :1;                       ///< [12] PsnErrMask
    UINT32                  Reserved_13_13 :1;                        ///<
    UINT32                  CompletionTimeoutMask :1;                 ///< [14] CplTimeoutMask
    UINT32                  CompleterAbortMask :1;                    ///< [15] CplAbortErrMask
    UINT32                  UnexpectedCompletionMask :1;              ///< [16] UnexpCplMask
    UINT32                  Reserved_17_17:1 ;                        ///<
    UINT32                  MalTlpMask:1 ;                            ///< [18] MalTlpMask
    UINT32                  ECRCErrorMask :1;                         ///< [19] EcrcErrMask
    UINT32                  UnsupportedRequestErrorMask :1;           ///< [20] UnsuppReqErrMask
    UINT32                  AcsViolationMask:1 ;                      ///< [21] AcsViolationMask
    UINT32                  Reserved_31_22 :10;                       ///<
  } Field;                                                            ///<
  UINT32 Value;                                                       ///<
} NBIO_PCIe_AER_UNCORRECTABLE_MASK;

/// PCIe Unorrectable Error Severity
typedef union {
  struct {                                                            ///<
    UINT32                  Reserved_3_0 :4;                          ///< [3:0]
    UINT32                  DataLinkProtocolErrorSeverity :1;         ///< [4] DlpErrSeverity
    UINT32                  Reserved_11_5 :7;                         ///< [11:5]
    UINT32                  PoisonedTLPSeverity :1;                   ///< [12] PsnErrSeverity
    UINT32                  Reserved_13_13 :1;                        ///< [13]
    UINT32                  CompletionTimeoutSeverity :1;             ///< [14] CplTimeoutSeverity
    UINT32                  CompleterAbortSeverity :1;                ///< [15] CplAbortErrSeverity
    UINT32                  UnexpectedCompletionSeverity :1;          ///< [16] UnexpCplSeverity
    UINT32                  Reserved_17_17:1 ;                        ///< [17]
    UINT32                  MalTlpSeverity:1 ;                        ///< [18] MalTlpSeverity
    UINT32                  ECRCErrorSeverity :1;                     ///< [19] EcrcErrSeverity
    UINT32                  UnsupportedRequestErrorSeverity :1;       ///< [20] UnsuppReqErrSeverity
    UINT32                  AcsViolationSeverity:1 ;                  ///< [21] AcsViolationSeverity
    UINT32                  Reserved_31_22 :10;                       ///< [31:22]
  } Field;                                                            ///<
  UINT32 Value;                                                       ///<
} NBIO_PCIe_AER_UNCORRECTABLE_SEVERITY;
#pragma pack (pop)

/// PCIe AER Port Configuration
typedef struct {
  UINT8                                PortAerEnable;                 ///< General per-port enable
  UINT8                                PciDev;                        ///< PCI Device Number
  UINT8                                PciFunc;                       ///< PCI Function Number
  NBIO_PCIe_AER_CORRECTABLE_MASK       CorrectableMask;               ///< Per-port mask for correctable errors
  NBIO_PCIe_AER_UNCORRECTABLE_MASK     UncorrectableMask;             ///< Per-port mask for uncorrectable errors
  NBIO_PCIe_AER_UNCORRECTABLE_SEVERITY UncorrectableSeverity;         ///< Per-port severity configuration for uncorrectable errors
} NBIO_PCIe_PORT_AER_CONFIG;

/// PCIe AER Configuration
typedef struct {
  UINT8                      NumberOfPorts;                           ///< The amount of ports of GNB
  NBIO_PCIe_PORT_AER_CONFIG  PortAerConfig[];                         ///< Per-port AER configuration
} AMD_NBIO_PCIe_AER_CONFIG;

#endif

