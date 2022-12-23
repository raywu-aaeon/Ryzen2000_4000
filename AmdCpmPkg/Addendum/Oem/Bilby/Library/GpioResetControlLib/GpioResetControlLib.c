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
 ******************************************************************************
 */
#include <PiPei.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeiServicesTablePointerLib.h>

#include <AMD.h>
#include <Library/OemGpioResetControlLib.h>

#include <Ppi/AmdCpmTablePpi/AmdCpmTablePpi.h>
#include <Ppi/NbioPcieComplexPpi.h>
#include <Fch.h>

/*----------------------------------------------------------------------------------------
 *                         E X T E R N   D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
/*----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------*/
/**
 * Local delay function
 *
 *
 *
 * @param[in]  PeiServices    Pointer to EFI_PEI_SERVICES pointer
 * @param[in]  xus            Microseconds to delay
 *
 */
VOID
STATIC
delay_xus (
  IN  CONST     EFI_PEI_SERVICES   **PeiServices,
  IN  UINT32    xus
  )
{
  EFI_PEI_CPU_IO_PPI  *CpuIo;
  UINTN               uSec;
  UINT8               Data;

  // Issue the reset
  CpuIo = (*PeiServices)->CpuIo;

  //Simplified implementation
  uSec = xus >> 1;
  while (uSec != 0) {
    Data = CpuIo->IoRead8 (
                    PeiServices,
                    CpuIo,
                    (UINT64) 0x80
                    );
    uSec--;
  }
}

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/**
 Gpio reset control.

 @param[in]         FcnData             Function data
 @param[in]         ResetInfo           Reset information

 @retval            EFI_SUCCESS       Function returns successfully
 @retval            EFI_UNSUPPORTED   Function is not supported
*/
EFI_STATUS
AgesaGpioSlotResetControl (
  IN      UINTN                         FcnData,
  IN      GPIO_RESET_INFO               *ResetInfo
  )
{
  EFI_PEI_SERVICES                      **PeiServices;
  AMD_CPM_TABLE_PPI                     *AmdCpmTablePpi;
  EFI_STATUS                            Status;

  DXIO_PORT_DESCRIPTOR                  *UserCfgPortList;
  PEI_AMD_NBIO_PCIE_COMPLEX_PPI         *NbioPcieComplexPpi;
  DXIO_COMPLEX_DESCRIPTOR               *UserConfig;
  UINTN                                 Counter = 0;
  GPIO_RESET_INFO                       GpioResetInfo;

  PeiServices = (EFI_PEI_SERVICES **) GetPeiServicesTablePointer ();
  DEBUG((DEBUG_INFO, "OEM-PEI-AgesaGpioSlotResetControl-Start\n"));

  Status = (*PeiServices)->LocatePpi (
                             PeiServices,
                             &gAmdCpmTablePpiGuid,
                             0,
                             NULL,
                             &AmdCpmTablePpi
                             );
  if (!EFI_ERROR (Status)) {
    DEBUG((DEBUG_INFO, "OEM-PEI-AgesaGpioSlotResetControl-ResetId=%X   ResetControl=%X\n", ResetInfo->ResetId, ResetInfo->ResetControl));
    Status = (*PeiServices)->LocatePpi (PeiServices, &gAmdNbioPcieComplexPpiGuid, 0, NULL, &NbioPcieComplexPpi);

    NbioPcieComplexPpi->PcieGetComplex (NbioPcieComplexPpi, &UserConfig);

    UserCfgPortList = UserConfig->PciePortList;

    while ((UserCfgPortList->Flags & DESCRIPTOR_TERMINATE_LIST) == 0) {
      do {
        UserCfgPortList = UserConfig->PciePortList;
        UserCfgPortList = UserCfgPortList + Counter;
        Counter++;
        DEBUG((DEBUG_INFO, "Counter 0x%x\n", Counter));
      } while (UserCfgPortList->EngineData.EngineType == DxioUnusedEngine);

      GpioResetInfo.ResetId = UserCfgPortList->EngineData.GpioGroupId;
      GpioResetInfo.ResetControl = DeassertSlotReset;

      if (GpioResetInfo.ResetId != 1) {
        AmdCpmTablePpi->PeimPublicFunction.PcieReset ( AmdCpmTablePpi,
                                           (UINT8) GpioResetInfo.ResetId,
                                           (UINT8) GpioResetInfo.ResetControl );
      }
    }
    DEBUG((DEBUG_INFO, "OEM-PEI-AgesaGpioSlotResetControl-End=EFI_SUCCESS\n"));

    AmdCpmTablePpi->CommonFunction.SetGpio(AmdCpmTablePpi, 0x6, 0x0);
    AmdCpmTablePpi->CommonFunction.Stall (AmdCpmTablePpi, 5000);                          // Delay 5ms
    AmdCpmTablePpi->CommonFunction.SetGpio(AmdCpmTablePpi, 0x6, 0x1);

//  DEBUG((DEBUG_INFO, "OEM-PEI-AgesaGpioSlotResetControl-EGPIO26 & EGPIO27 Output high\n"));
//  AmdCpmTablePpi->CommonFunction.SetGpio (AmdCpmTablePpi, 26, 1);                       // EGPIO26 Output high
//  AmdCpmTablePpi->CommonFunction.SetGpio (AmdCpmTablePpi, 27, 1);                       // EGPIO27 Output high

    DEBUG((DEBUG_INFO, "OEM-PEI-AgesaGpioSlotResetControl-End-1-EFI_SUCCESS\n"));
    return EFI_SUCCESS;
  }
  DEBUG((DEBUG_INFO, "OEM-PEI-AgesaGpioSlotResetControl-End-2-EFI_UNSUPPORTED\n"));
  return EFI_UNSUPPORTED;
}

