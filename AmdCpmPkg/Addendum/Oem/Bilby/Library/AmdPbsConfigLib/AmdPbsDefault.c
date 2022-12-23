/*****************************************************************************
 *
 * Copyright 2015 - 2020 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting you permission to use this software (the Materials)
 * pursuant to the terms and conditions of your Software License Agreement
 * with AMD.  This header does *NOT* give you permission to use the Materials
 * or any rights under AMD's intellectual property.  Your use of any portion
 * of these Materials shall constitute your acceptance of those terms and
 * conditions.  If you do not agree to the terms and conditions of the Software
 * License Agreement, please do not use any portion of these Materials.
 *
 * CONFIDENTIALITY:  The Materials and all other information, identified as
 * confidential and provided to you by AMD shall be kept confidential in
 * accordance with the terms and conditions of the Software License Agreement.
 *
 * LIMITATION OF LIABILITY: THE MATERIALS AND ANY OTHER RELATED INFORMATION
 * PROVIDED TO YOU BY AMD ARE PROVIDED "AS IS" WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTY OF ANY KIND, INCLUDING BUT NOT LIMITED TO WARRANTIES OF
 * MERCHANTABILITY, NONINFRINGEMENT, TITLE, FITNESS FOR ANY PARTICULAR PURPOSE,
 * OR WARRANTIES ARISING FROM CONDUCT, COURSE OF DEALING, OR USAGE OF TRADE.
 * IN NO EVENT SHALL AMD OR ITS LICENSORS BE LIABLE FOR ANY DAMAGES WHATSOEVER
 * (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF PROFITS, BUSINESS
 * INTERRUPTION, OR LOSS OF INFORMATION) ARISING OUT OF AMD'S NEGLIGENCE,
 * GROSS NEGLIGENCE, THE USE OF OR INABILITY TO USE THE MATERIALS OR ANY OTHER
 * RELATED INFORMATION PROVIDED TO YOU BY AMD, EVEN IF AMD HAS BEEN ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGES.  BECAUSE SOME JURISDICTIONS PROHIBIT THE
 * EXCLUSION OR LIMITATION OF LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES,
 * THE ABOVE LIMITATION MAY NOT APPLY TO YOU.
 *
 * AMD does not assume any responsibility for any errors which may appear in
 * the Materials or any other related information provided to you by AMD, or
 * result from use of the Materials or any related information.
 *
 * You agree that you will not reverse engineer or decompile the Materials.
 *
 * NO SUPPORT OBLIGATION: AMD is not obligated to furnish, support, or make any
 * further information, software, technical information, know-how, or show-how
 * available to you.  Additionally, AMD retains the right to modify the
 * Materials at any time, without notice, and is not obligated to provide such
 * modified Materials to you.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS: The Materials are provided with
 * "RESTRICTED" RIGHTS. Use, duplication, or disclosure by the Government is
 * subject to the restrictions as set forth in FAR 52.227-14 and
 * DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
 * Government constitutes acknowledgement of AMD's proprietary rights in them.
 *
 * EXPORT ASSURANCE:  You agree and certify that neither the Materials, nor any
 * direct product thereof will be exported directly or indirectly, into any
 * country prohibited by the United States Export Administration Act and the
 * regulations thereunder, without the required authorization from the U.S.
 * government nor will be used for any purpose prohibited by the same.
 ******************************************************************************
 */

#include <PiPei.h>
#include <Uefi.h>
#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Dxe/AmdPbsSetupDxe/AmdPbsConfig.h>
#include <Library/PcdLib.h>

EFI_STATUS
EFIAPI
LoadAmdPbsDefault (
  OUT AMD_PBS_SETUP_OPTION        *AmdPbsConfiguration
  )
{

    AmdPbsConfiguration->PlatformId                                    = ((PcdGet16 (OriginalPlatformId) & BIT2)>>2);
    AmdPbsConfiguration->CurrentId                                     = ((PcdGet16 (CurrentPlatformId) < 0x0008) ? 0 : 1);
    AmdPbsConfiguration->AmdCpmUsedPbsSize                             = AMD_CPM_USED_PBS_SIZE;
    AmdPbsConfiguration->StallForUnlock                                = 0;
    AmdPbsConfiguration->HdtBreakPointBoot                             = 0;
    AmdPbsConfiguration->HdtBreakPointS3                               = 0;
    AmdPbsConfiguration->SpecialVgaFeature                             = 0;
    AmdPbsConfiguration->DgpuAudio                                     = 0;
    AmdPbsConfiguration->PrimaryVideoAdaptor                           = 1;
    AmdPbsConfiguration->SataPort0HddPowerEn                           = 1;
    AmdPbsConfiguration->SataPort1OddPowerEn                           = 1;
    AmdPbsConfiguration->SataPortSsdPowerEn                            = 1;
    AmdPbsConfiguration->EvalAutoDetection                             = 0;
    AmdPbsConfiguration->SdPowerControl                                = 1;
    AmdPbsConfiguration->FchSdConfig                                   = 0;
    AmdPbsConfiguration->MITTWITTControl                               = 2;
    AmdPbsConfiguration->UnusedGppClkOff                               = 0;
    AmdPbsConfiguration->ClockRequest2                                 = 1;
    AmdPbsConfiguration->ClockRequest3                                 = 1;
    AmdPbsConfiguration->ClockRequest4                                 = 0;
    AmdPbsConfiguration->ClockRequest5                                 = 0;
    AmdPbsConfiguration->ClockRequest6                                 = 0;
    AmdPbsConfiguration->KbcSupport                                    = 1;
    AmdPbsConfiguration->XgbePortPhySwitch                             = 1;
    AmdPbsConfiguration->XgbePortSpeedSwitch                           = 3;
    AmdPbsConfiguration->VDDP                                          = 0;
    AmdPbsConfiguration->AmdPspKvmMouseProtocol                        = 3;
    AmdPbsConfiguration->AmdBlinkLed                                   = 1;
    AmdPbsConfiguration->DisplaySelect1                                = 1;
    AmdPbsConfiguration->DisplaySelect2                                = 1;
    AmdPbsConfiguration->PxeBoot                                       = 0;
    AmdPbsConfiguration->XgbeVsPcieXn                                  = 0;
    return EFI_SUCCESS;
}