/*****************************************************************************
 *
 * Copyright 2016 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
#ifndef _AMD_NBIO_EARLY_LINK_PPI_H_
#define _AMD_NBIO_EARLY_LINK_PPI_H_

/// EARLY LINK STATUS Structure
typedef struct {
  IN         BOOLEAN      EarlyLinkStatus;      ///< Status of early link training (TRUE == Training Success)
  IN         UINT8        PhysicalRootBridge;   ///< Physical root bridge (NBIO) that the early train link is connected to
  IN         UINT8        LogicalRootBridge;    ///< Logical root bridge (NBIO) that the early train link is connected to
  IN         UINT8        RootPortBus;          ///< Bus number of the root port of the early train link
  IN         UINT8        RootPortDevice;       ///< Device number of the root port of the early train link
  IN         UINT8        RootPortFunction;     ///< Function number of the root port of the early train link
} EARLY_LINK_STATUS;

typedef struct _PEI_AMD_NBIO_EARLY_LINK_PPI PEI_AMD_NBIO_EARLY_LINK_PPI;

//
// PPI prototype
//
/**
  Returns location information about Early Train Link

  EarlyLinkStatus
    A pointer to structure to store the Early Train Link status
**/
typedef
EFI_STATUS
(EFIAPI * AMD_NBIO_EARLY_LINK_CONFIG) (
  OUT EARLY_LINK_STATUS  *EarlyLinkStatus
);


///
/// The Ppi of Early Link services
///
struct _PEI_AMD_NBIO_EARLY_LINK_PPI {
  AMD_NBIO_EARLY_LINK_CONFIG       GetEarlyLinkConfig; ///<
};

extern EFI_GUID gAmdNbioEarlyLinkPpiGuid;
#endif //

