/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD HSTI DXE Driver Header file
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision: 312065 $   @e \$Date: 2015-01-30 18:23:05 +0800 (Fri, 30 Jan 2015) $
 *
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
 */
#define  HSTI_AMD_FEATUERS_SIZE_IN_BYTES        (MAX_HSTI_AMD_FEATURE_BYTE_INDEX + 1)
#define  HSTI_AMD_ERROR_STRING_SIZE             0x100



#define MAX_HSTI_AMD_FEATURE_BYTE_INDEX                             HSTI_AMD_FEATURE_BYTE_INDEX_5

//Security Feature bitmap
//Security Feature Byte Index 0
#define HSTI_AMD_FEATURE_BYTE_INDEX_0                               0     ///< Byte index 0
#define HSTI_AMD_CRYPTO_STRENGTH                                    BIT0  ///< Do you use RSA 2048 and SHA256 only (or similar crypto strength)

///2. Firmware Code must be present in protected storage
///Security Feature Byte Index 1
#define HSTI_AMD_FEATURE_BYTE_INDEX_1                               1     ///< Byte index 1
#define HSTI_AMD_FWCODE_PROTECT_PROTECT_SPI                         BIT0  ///< Do you protect spiflash?
#define HSTI_AMD_FWCODE_PROTECT_SIGNED_FW_CHECK                     BIT2  ///< Do you support Signed Firmware Check Firmware that is installed by OEM is either readonly or protected by secure firmware update process

///3. Secure firmware update process
///Security Feature Byte Index 2
#define HSTI_AMD_FEATURE_BYTE_INDEX_2                               2     ///< Byte index 2
#define HSTI_AMD_SECURE_FW_UPDATE_DFT_TESTKEY                       BIT0  ///< Is secure firmware update process on by default with test keys?  (RECOMMENDED)
#define HSTI_AMD_SECURE_FW_UPDATE_CHECK_TESTKEY_IN_PRODUCTION       BIT1  ///< Do you check if test keys are used in production?
#define HSTI_AMD_SECURE_FW_UPDATE_ROLLBACK_CHECK                    BIT2  ///< Do you allow rollback to insecure firmware  version? If yes then what is the protection mechanism? Do you clear TPM when rollback happens?


///4.Do you have backdoors to override SecureBoot
///Security Feature Byte Index 3
#define HSTI_AMD_FEATURE_BYTE_INDEX_3                               3     ///< Byte index 3
#define HSTI_AMD_SECUREBOOT_BACKDOOR_INLINE_PROMPT_CHECK            BIT0  ///< a. Does your system support inline prompting to bypass Secureboot? If yes then is it disabled while SecureBoot is enabled
#define HSTI_AMD_SECUREBOOT_BACKDOOR_MANUFACTURE_CHECK              BIT1  ///< b. Do  you  have  manufacturing  backdoors?  Do  you  check  for  them  to  be  disabled  while SecureBoot is enabled and always disabled in production system?

///Security Feature Byte Index 4
#define HSTI_AMD_FEATURE_BYTE_INDEX_4                               4     ///< Byte index 4
#define HSTI_AMD_FEATURE_PSP_SECURE_EN                              BIT0  ///< Fuse SecureEnable to ensure silicon level secure
#define HSTI_AMD_FEATURE_PSP_PLATFORM_SECURE_BOOT_EN                BIT1  ///< Boot Integrity Support
#define HSTI_AMD_FEATURE_PSP_DEBUG_LOCK_ON                          BIT2  ///< Protection against external hardware debugger
///Compatibility Support Modules (CSM)
///Security Feature Byte Index 5
#define HSTI_AMD_FEATURE_BYTE_INDEX_5                               5     ///< Byte index 5
#define HSTI_AMD_CSM_DISABLE_IF_SECUREBOOT_EN                       BIT0  ///< b.  Do you check blocking of loading CSM when SecureBoot is enabled
#define HSTI_AMD_CSM_DISABLE_ON_CS_SYSTEM                           BIT1  ///< c.  [CS]Do you check if CSM is not present on CS systems permanently
