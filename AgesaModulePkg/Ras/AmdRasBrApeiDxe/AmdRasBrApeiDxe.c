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

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include "PiDxe.h"
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/RasBrBaseLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Protocol/AcpiTable.h>
#include <Protocol/AcpiSystemDescriptionTable.h>
#include <Protocol/AmdRasApeiProtocol.h>
#include "AmdRasBrApeiDxe.h"
#include <Library/DebugLib.h>

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define FILECODE RAS_AMDRASBRAPEIDXE_AMDRASBRAPEIDXE_FILECODE


/*----------------------------------------------------------------------------------------
 *                           G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
EFI_STATUS
AddBertErrorRecord (
  IN UINT8       *ErrorRecord,
  IN UINT32      RecordLen,
  IN UINT8       ErrorType,
  IN UINT8       SeverityType
  );

EFI_STATUS
AddHestErrorRecord (
  IN UINT8       *ErrorRecord,
  IN UINT32      RecordLen
  );

EFI_STATUS
AmdMcaErrorAddrTranslate (
  IN       NORMALIZED_ADDRESS *NormalizedAddress,
  OUT      UINT64             *SystemMemoryAddress,
  OUT      DIMM_INFO          *DimmInfo
  );

EFI_STATUS
AmdTranslateSysAddrToCS (
  IN       UINT64             *SystemMemoryAddress,
  OUT      NORMALIZED_ADDRESS *NormalizedAddress,
  OUT      DIMM_INFO          *DimmInfo
  );

EFI_STATUS
AmdSearchMcaError (
  IN OUT   RAS_MCA_ERROR_INFO* RasMcaErrorInfo
  );

VOID
CollectMcaErrorInfo (
  IN OUT   RAS_MCA_ERROR_INFO* RasMcaErrorInfo
  );

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
extern  EFI_BOOT_SERVICES       *gBS;

/*----------------------------------------------------------------------------------------
 *                          T A B L E    D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */


/*---------------------------------------------------------------------------------------*/
/**
 * MCA_ADDR Address Translate
 *
 * Translate UMC local address into specific memory DIMM information and system address
 * 
 *
 * @param[in]   NormalizedAddress      UMC memory address Information
 * @param[out]  SystemMemoryAddress    System Address
 * @param[out]  DimmInfo               DIMM information
 *
 */

EFI_STATUS
AmdMcaErrorAddrTranslate (
  IN       NORMALIZED_ADDRESS *NormalizedAddress,
  OUT      UINT64             *SystemMemoryAddress,
  OUT      DIMM_INFO          *DimmInfo
)
{
  BOOLEAN         CSFound;

  CSFound         = FALSE;

  // NormalizedAddress->normalizedSocketId = 0;

  PlatformTranslateCsAddrToSys (  NormalizedAddress->normalizedAddr,
                                  NormalizedAddress->normalizedDieId,
                                  NormalizedAddress->normalizedChannelId,
                                  &CSFound,
                                  SystemMemoryAddress,
                                  &DimmInfo->ChipSelect,
                                  &DimmInfo->Bank,
                                  &DimmInfo->Row,
                                  &DimmInfo->Column
                                );

  return EFI_SUCCESS;
}

/*---------------------------------------------------------------------------------------*/
/**
 * System Address Translate
 *
 * Translate system address into specific memory DIMM information and normalized address
 * information
 *
 * @param[in]   SystemMemoryAddress    System Address
 * @param[out]  NormalizedAddress      UMC memory address Information
 * @param[out]  DimmInfo               DIMM information
 *
 */

EFI_STATUS
AmdTranslateSysAddrToCS (
  IN       UINT64             *SystemMemoryAddress,
  OUT      NORMALIZED_ADDRESS *NormalizedAddress,
  OUT      DIMM_INFO          *DimmInfo
)
{
  BOOLEAN         CSFound;

  CSFound         = FALSE;

  NormalizedAddress->normalizedSocketId = 0;

  PlatformTranslateSysAddrToCS (  *SystemMemoryAddress,
                                  &CSFound,
                                  &NormalizedAddress->normalizedAddr,
                                  &NormalizedAddress->normalizedDieId,
                                  &NormalizedAddress->normalizedChannelId,
                                  &DimmInfo->ChipSelect,
                                  &DimmInfo->Bank,
                                  &DimmInfo->Row,
                                  &DimmInfo->Column
                                );

  return EFI_SUCCESS;
}

EFI_STATUS
AmdSearchMcaError (
  IN OUT   RAS_MCA_ERROR_INFO* RasMcaErrorInfo
  )
{
  return EFI_UNSUPPORTED;
}


/*********************************************************************************
 * Name: AmdRasBrApeiDxeInit
 *
 * Description
 *   Entry point of the AMD BR RAS APEI DXE driver
 *   Install all the supported protocol
 *
 * Input
 *   ImageHandle : EFI Image Handle for the DXE driver
 *   SystemTable : pointer to the EFI system table
 *
 * Output
 *   EFI_SUCCESS : Module initialized successfully
 *   EFI_ERROR   : Initialization failed (see error for more details)
 *
 *********************************************************************************/
EFI_STATUS
EFIAPI
AmdRasBrApeiDxeInit (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS            Status = EFI_SUCCESS;
  EFI_HANDLE            Handle = NULL;
  AMD_RAS_APEI_PROTOCOL *AmdRasApeiProtocol;

  // Allocate Memory for the the AMD_RAS_APEI_PROTOCOL protocol.
  Status = gBS->AllocatePool (
                              EfiBootServicesData,              // IN EFI_MEMORY_TYPE PoolType
                              sizeof (AMD_RAS_APEI_PROTOCOL),   // IN UINTN Size
                              &AmdRasApeiProtocol               // OUT VOID **Buffer
                              );
  if (EFI_ERROR (Status)) {
    ASSERT_EFI_ERROR (Status);
    return Status;    // Error detected while trying to locate pool
  }

  // Initialize function pointers to protocol interfaces
  AmdRasApeiProtocol->McaErrorAddrTranslate = &AmdMcaErrorAddrTranslate;
  AmdRasApeiProtocol->TranslateSysAddrToCS = &AmdTranslateSysAddrToCS;
  AmdRasApeiProtocol->AddBootErrorRecordEntry = &AddBertErrorRecord;
  AmdRasApeiProtocol->AddHestErrorSourceEntry = &AddHestErrorRecord;
  AmdRasApeiProtocol->SearchMcaError = &AmdSearchMcaError;

  Status = gBS->InstallProtocolInterface (
                                          &Handle,                  // IN OUT EFI_HANDLE
                                          &gAmdRasApeiProtocolGuid, // IN EFI_GUID
                                          EFI_NATIVE_INTERFACE,     // IN EFI_INITERFACE_TYPE
                                          AmdRasApeiProtocol        // IN VOID* Interface
                                          );
  if (EFI_ERROR (Status)) {
    ASSERT_EFI_ERROR (Status);
    return EFI_PROTOCOL_ERROR;
  }
  return (Status);
}

/**
 *---------------------------------------------------------------------------------------
 *
 *  AddBertErrorRecord
 *
 *  Description:
 *     Adds a new Boot Error Record Entry to the APEI Boot Error Record Table (BERT).
 *
 *  Parameters:
 *    @param[in]     *ErrorRecord
 *    @param[in]     RecordLen
 *    @param[in]     ErrorType
 *    @param[in]     SeverityType
 *
 *    @retval         EFI_SUCCESS   Error record has been added to BERT table
 *                    EFI_UNSUPPORTED ErrorType passed in is unsupported
 *                    EFI_OUT_OF_RESOURCES  Could not allocate memory
 *                    EFI_VOLUME_FULL   cannot add one more error record
 *
 *---------------------------------------------------------------------------------------
 **/
EFI_STATUS
AddBertErrorRecord (
  IN UINT8  *ErrorRecord,
  IN UINT32 RecordLen,
  IN UINT8  ErrorType,
  IN UINT8  SeverityType
  )
{
  return EFI_UNSUPPORTED;
}

/**
 *---------------------------------------------------------------------------------------
 *
 *  AddHestErrorRecord
 *
 *  Description:
 *     Adds a new Hardware Error Source Record Entry to the APEI Hardware Error Source Table (HEST).
 *
 *  Parameters:
 *    @param[in]     *ErrorRecord
 *    @param[in]     RecordLen
 *
 *    @retval         EFI_SUCCESS  Error record has been added to BERT table
 *                    EFI_UNSUPPORTED  ErrorType passed in is unsupported
 *                    EFI_OUT_OF_RESOURCES  Could not allocate memory
 *                    EFI_VOLUME_FULL  Cannot add one more error record
 *
 *---------------------------------------------------------------------------------------
 **/
EFI_STATUS
AddHestErrorRecord (
  IN UINT8  *ErrorRecord,
  IN UINT32 RecordLen
  )
{
  return EFI_UNSUPPORTED;
}


VOID
CollectMcaErrorInfo (
  IN OUT   RAS_MCA_ERROR_INFO* RasMcaErrorInfo
  )
{
}


