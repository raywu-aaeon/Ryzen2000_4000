//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

#include <PiPei.h>
#include <AGESA.h>
#include "Library/IoLib.h"
#include <Library/BaseMemoryLib.h>
#include "Token.h"
#include <Library/DebugLib.h>
#include "Ppi/ReadOnlyVariable2.h"
#include <Library/AmdSocBaseLib.h>
#include <Library/PcdLib.h>
#include <CpuSetupData.h>
#include "Library/CcxPstatesLib.h"
#include <Ppi/AmdSocPcdInitPpi.h>
#include "CcxRegistersZp.h"

EFI_STATUS
EFIAPI
CpuAgesaPcdInitReadyCallback (
  IN  EFI_PEI_SERVICES                **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
  IN  VOID                            *InvokePpi
  );

EFI_PEI_NOTIFY_DESCRIPTOR   CpuAgesaPcdInitReadyNotifyList = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_DISPATCH | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdPcdInitReadyPpiGuid,
  CpuAgesaPcdInitReadyCallback
};


/**
 *  CpuAgesaPcdInitReadyCallback
 *
 *  Description:
 *    This function will set the AGESA PCD according to Cpu setup value.
 *
 *  Parameters:
 *    @param[in]        **PeiServices
 *                      NotifyDesc
 *                      InvokePpi
 *
 *
 *    @retval         VOID
 *
 **/
EFI_STATUS
EFIAPI
CpuAgesaPcdInitReadyCallback (
  IN  EFI_PEI_SERVICES                **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
  IN  VOID                            *InvokePpi
  )
{
    CPU_SETUP_DATA      CpuSetupData;
    SOC_ID_STRUCT       SocId;
    
    GetCpuSetupData((EFI_PEI_SERVICES**)PeiServices, &CpuSetupData, TRUE);

    // Check Hardware Identification
    SocId.SocFamilyID = F15_BR_RAW_ID;
    SocId.PackageType = BR_PKG_AM4;

    if (SocHardwareIdentificationCheck (&SocId))
    {
        // It's family 15h
        PcdSet8S (PcdAmdCpbMode, CpuSetupData.CpbMode);
        PcdSet8S (PcdAmdCStateMode, CpuSetupData.C6Mode);
        if (CpuSetupData.C6Mode == 0)
        {
            PcdSet16S(PcdAmdCStateIoBaseAddress, 0);
        }
    }

    if (CpuSetupData.PNOW_ASL_MODE)
    {
        PcdSetBoolS(PcdAmdAcpiCpuSsdt, TRUE);
    }
    else
    {
        PcdSetBoolS(PcdAmdAcpiCpuSsdt, FALSE);
    }

    return (EFI_SUCCESS);
}


/**
 *  CpuSetAgesaPcdEntry
 *
 *  Description:
 *    This function will notify a callback of gAmdPcdInitReadyPpiGuid.
 *
 *  Parameters:
 *    @param[in]        **PeiServices
 *                      FileHandle
 *
 *
 *    @retval         VOID
 *
 **/
EFI_STATUS
EFIAPI
CpuSetAgesaPcdEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
    EFI_STATUS          Status;

    Status = (**PeiServices).NotifyPpi (PeiServices, &CpuAgesaPcdInitReadyNotifyList);

    return  Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
