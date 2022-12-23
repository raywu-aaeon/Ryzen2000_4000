/* $NoKeywords:$ */
/**
 * @file
 *
 * JedecNvdimm.c
 *
 * 
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  JedecNvdimm
 * @e \$Revision$   @e \$Date$
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

/** @file JedecNvdimm.c
    JedecNvdimm Driver Implementation

**/

//---------------------------------------------------------------------------

#include "JedecNvdimm.h"
#include "JedecNvdimmDsm.h"
#include "IndustryStandard/Acpi.h"
#include "Protocol/AcpiSystemDescriptionTable.h"
#include <Protocol/SmmBase2.h>

//---------------------------------------------------------------------------

extern EFI_STATUS GenerateJedecNvdimmAcpi();
extern EFI_STATUS InstallDsmSmiHandler();
extern EFI_STATUS SetEventNotifications (UINT16 TotalNvdimm);
extern EFI_STATUS JedecNvdimmSmbusInit();
extern EFI_STATUS ReadNvdimm (UINT8 Socket, UINT8 Channel, UINT8 Dimm, UINT8 Page, UINT8 Register, UINT8 *Data, BOOLEAN IsSpd);
extern EFI_STATUS WriteNvdimm (UINT8 Socket, UINT8 Channel, UINT8 Dimm, UINT8 Page, UINT8 Register, UINT8 *Data, BOOLEAN IsSpd);
extern UINT32 ResetToFactoryDefaults (UINT8 Socket, UINT8 Channel, UINT8 Dimm);

EFI_SMM_SYSTEM_TABLE2   *gSmst;
DSM_ACPI_SMM_DATA       *pDsmAcpiSmmData;
EFI_GUID                gJedecNvdimmSmmProtocolGuid = JEDEC_NVDIMM_SMM_PROTOCOL_GUID;

JEDEC_NVDIMM_SMM_PROTOCOL JedecNvdimmSmmProtocol = {
    ReadMemoryErrorCounters,
    SetMemoryErrorCounters,
    IncrementMemErrorCounters,
    PerformNvdimmPurge
};

/**
 * gNvdimmBitMap
 * 
+---------+-----------------------------------------------+-----------------------------------------------+
| Socket  |                      S1                       |                      S0                       |
+---------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
| Channel |  C7 |  C6 |  C5 |  C4 |  C3 |  C2 |  C1 |  C0 |  C7 |  C6 |  C5 |  C4 |  C3 |  C2 |  C1 |  C0 |
+---------+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
| Dimm    |D1|D0|D1|D0|D1|D0|D1|D0|D1|D0|D1|D0|D1|D0|D1|D0|D1|D0|D1|D0|D1|D0|D1|D0|D1|D0|D1|D0|D1|D0|D1|D0|
+---------+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
| Bit     |31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16|15|14|13|12|11|10|09|08|07|06|05|04|03|02|01|00|
+---------+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
**/

UINT32 gNvdimmBitMap;

//======================================================
//  ACPI Tables header structure  for IA32
//======================================================
typedef struct _ACPI_HDR {
    UINT32      Signature;
    UINT32      Length;
    UINT8       Revision;
    UINT8       Checksum;
    UINT8       OemId[6]; 
    UINT8       OemTblId[8];
    UINT32      OemRev;
    UINT32      CreatorId;
    UINT32      CreatorRev;
} ACPI_HDR;

/**
  Initialize timeout for a specified amount of time in uS.
 
   @param Timeout - Pointer to structure, data modified by function.
   @param Time - Timeout value in uS. 
   @param Status - Status returned by function.

   @return EFI_STATUS
   @retval  EFI_SUCCESS - Always return success.
*/

EFI_STATUS 
StartTimeout(
    IN SMM_TIMEOUT *Timeout, 
    IN UINTN        Time
    )
{
    UINT64  TicksNeeded;
    UINT64  EndValue;
    
    // There are 3.58 ticks per uS.
    TicksNeeded = (Time * 358) / 100;
    
    // Read ACPI Timer
    Timeout->OldTimerValue = IoRead32(PM_TMR_BLK_ADDRESS);
    EndValue = TicksNeeded + Timeout->OldTimerValue;
    
    // Calculate Overflow and EndValue from FullEndValue,
    // based on number of bits in ACPI Timer
    Timeout->OverFlow = (UINT32)(EndValue >> NUM_BITS_IN_ACPI_TIMER);
    Timeout->EndValue = ((UINT32)EndValue) & (UINT32)(((UINT64)1 << NUM_BITS_IN_ACPI_TIMER) - 1);
    
    return EFI_SUCCESS;
}

/**
  Checks if timeout has expired.
 
   @param Timeout - Pointer to structure, data modified by function.
   @param Status - Status returned by function.

   @return EFI_STATUS
   @retval  EFI_SUCCESS - Timer not expired.
   @retval  EFI_TIMEOUT - Timer expired.
*/

EFI_STATUS
HasItTimedOut(
    IN SMM_TIMEOUT *Timeout
    )
{
    UINTN TimerValue;

    // Read ACPI Timer
    TimerValue = IoRead32(PM_TMR_BLK_ADDRESS);

    if (Timeout->OverFlow > 0) {
        // See if the current timer value is less than the previous value.
        // If it is, then the timer had wrapped around.
        if (TimerValue < Timeout->OldTimerValue) {
            --Timeout->OverFlow;
        }
        
        // Update OldTimerValue
        Timeout->OldTimerValue = TimerValue;
        return EFI_SUCCESS;
    }
    
    // See if the current timer value is less than the previous value.
    // If it is, then we are done.
    if (TimerValue < Timeout->OldTimerValue) return EFI_TIMEOUT;
    
    // If we passed the EndValue, we are done.
    if (TimerValue >= Timeout->EndValue) return EFI_TIMEOUT;
    
    // Update OldTimerValue
    Timeout->OldTimerValue = TimerValue;
    
    return EFI_SUCCESS;
}

/**
    This routine delays for specified number of micro seconds

    @param Usec      Amount of delay (count in 1 microsec)

    @retval VOID

**/

VOID 
FixedDelay(
    IN UINTN  Usec                           
    )
{
    UINTN   Counter, i;
    UINT32  Data32, PrevData;

    // There are 3.58 ticks per Usec
    Counter = (Usec * 358) / 100;

    //
    // Call WaitForTick for Counter + 1 ticks to try to guarantee Counter tick
    // periods, thus attempting to ensure Microseconds of stall time.
    //
    if (Counter != 0) {

        PrevData = IoRead32(PM_BASE_ADDRESS + 8);
        for (i = 0; i < Counter; ) {
            Data32 = IoRead32(PM_BASE_ADDRESS + 8);    
            if (Data32 < PrevData) {        // Reset if there is a overlap
                PrevData = Data32;
                continue;
            }
            i += (Data32 - PrevData);        
            PrevData = Data32;
        }
    }
    return;
}

/**
  Reads the DRAM_ECC_ERROR_COUNT (0x80) and DRAM_THRESHOLD_ECC_COUNT (0x81)
  NVDIMM registers

  @param  This                  JEDEC_NVDIMM_SMM_PROTOCOL instance
  @param  Socket                Socket # of NVDIMM
  @param  Channel               Channel # of NVDIMM
  @param  Dimm                  Dimm # of NVDIMM
  @param  DramEccErrorCount     Number of uncorrectable ECC errors detected
  @param  DramThresholdEccCount Number of correctable ECC threshold exceeded events

  @retval EFI_STATUS

**/

EFI_STATUS
EFIAPI
ReadMemoryErrorCounters (
    IN CONST JEDEC_NVDIMM_SMM_PROTOCOL  *This,
    IN UINT8                            Socket,
    IN UINT8                            Channel,
    IN UINT8                            Dimm,
    OUT UINT8                           *DramEccErrorCount,
    OUT UINT8                           *DramThresholdEccCount
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
    UINT8       Data;
    
    Status = ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_DRAM_ECC_ERROR_COUNT, &Data, FALSE);
    *DramEccErrorCount = Data;
    Status = ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_DRAM_THRESHOLD_ECC_COUNT, &Data, FALSE);
    *DramThresholdEccCount = Data;
    
    return Status;
}

/**
  Sets the DRAM_ECC_ERROR_COUNT (0x80) and DRAM_THRESHOLD_ECC_COUNT (0x81)
  NVDIMM registers

  @param  This                  JEDEC_NVDIMM_SMM_PROTOCOL instance
  @param  Socket                Socket # of NVDIMM
  @param  Channel               Channel # of NVDIMM
  @param  Dimm                  Dimm # of NVDIMM
  @param  DramEccErrorCount     Number of uncorrectable ECC errors
  @param  DramThresholdEccCount Number of correctable ECC threshold exceeded events

  @retval EFI_STATUS

**/

EFI_STATUS
EFIAPI
SetMemoryErrorCounters (
    IN CONST JEDEC_NVDIMM_SMM_PROTOCOL  *This,
    IN UINT8                            Socket,
    IN UINT8                            Channel,
    IN UINT8                            Dimm,
    IN UINT8                            DramEccErrorCount,
    IN UINT8                            DramThresholdEccCount
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
    
    Status = WriteNvdimm(Socket, Channel, Dimm, 2, PAGE2_DRAM_ECC_ERROR_COUNT, &DramEccErrorCount, FALSE);
    Status = WriteNvdimm(Socket, Channel, Dimm, 2, PAGE2_DRAM_THRESHOLD_ECC_COUNT, &DramThresholdEccCount, FALSE);

    return Status;
}

/**
  Increments the DRAM_ECC_ERROR_COUNT (0x80) and DRAM_THRESHOLD_ECC_COUNT (0x81)
  NVDIMM registers

  @param  This                      JEDEC_NVDIMM_SMM_PROTOCOL instance
  @param  Socket                    Socket # of NVDIMM
  @param  Channel                   Channel # of NVDIMM
  @param  Dimm                      Dimm # of NVDIMM
  @param  IncDramEccErrorCount      Increment the number of uncorrectable ECC errors detected
  @param  IncDramThresholdEccCount  Increment the number of correctable ECC threshold exceeded events

  @retval EFI_SUCCESS or EFI_UNSUPPORTED

**/

EFI_STATUS
EFIAPI
IncrementMemErrorCounters (
    IN CONST JEDEC_NVDIMM_SMM_PROTOCOL  *This,
    IN UINT8                            Socket,
    IN UINT8                            Channel,
    IN UINT8                            Dimm,
    IN BOOLEAN                          IncDramEccErrorCount,
    IN BOOLEAN                          IncDramThresholdEccCount
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
    UINT8       Data;
    
    if (IncDramEccErrorCount) {
        Status = ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_DRAM_ECC_ERROR_COUNT, &Data, FALSE);
        if (Data < 255) {
            Data += 1;
            Status = WriteNvdimm(Socket, Channel, Dimm, 2, PAGE2_DRAM_ECC_ERROR_COUNT, &Data, FALSE);
            DEBUG ((EFI_D_ERROR, "IncrementMemErrorCounters: New DramEccErrorCount = %d\n", Data));
        }
        else {
            DEBUG ((EFI_D_ERROR, "IncrementMemErrorCounters ERROR: DramEccErrorCount at max 255\n"));
            return EFI_UNSUPPORTED;
        }
    }
    
    if (IncDramThresholdEccCount) {
        Status = ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_DRAM_THRESHOLD_ECC_COUNT, &Data, FALSE);
        if (Data < 255) {
            Data += 1;
            Status = WriteNvdimm(Socket, Channel, Dimm, 2, PAGE2_DRAM_THRESHOLD_ECC_COUNT, &Data, FALSE);
            DEBUG ((EFI_D_ERROR, "IncrementMemErrorCounters: New DramThresholdEccCount = %d\n", Data));
        }
        else {
            DEBUG ((EFI_D_ERROR, "IncrementMemErrorCounters ERROR: DramThresholdEccCount at max 255\n"));
            return EFI_UNSUPPORTED;
        }
    }
    
    return Status;
}

/**
  Executes the JEDEC Restore Factory Defaults function

  @param  This                  JEDEC_NVDIMM_SMM_PROTOCOL instance
  @param  Socket                Socket # of NVDIMM
  @param  Channel               Channel # of NVDIMM
  @param  Dimm                  Dimm # of NVDIMM

  @retval EFI_SUCCESS or EFI_TIMEOUT or EFI_DEVICE_ERROR

**/

EFI_STATUS
EFIAPI
PerformNvdimmPurge (
    IN CONST JEDEC_NVDIMM_SMM_PROTOCOL  *This,
    IN UINT8                            Socket,
    IN UINT8                            Channel,
    IN UINT8                            Dimm
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
    UINT32      DsmStatus;
    UINT8       Data;
    
    DsmStatus = ResetToFactoryDefaults(Socket, Channel, Dimm);
    Status = ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_FACTORY_DEFAULT_STATUS0, &Data, FALSE);
    
    if (DsmStatus == ((1 << 16) | DSM_FUNCTION_ERROR_CODE)) {
        DEBUG ((EFI_D_ERROR, "PerformNvdimmPurge ERROR: Factory Default operation timed out\n"));
        return EFI_TIMEOUT;
    }
    else if (DsmStatus == DSM_FUNCTION_ERROR_CODE) {
        DEBUG ((EFI_D_ERROR, "PerformNvdimmPurge ERROR: Unable to start Factory Default operation\n"));
        return EFI_DEVICE_ERROR;
    }
    else if (Data & BIT1) {
        DEBUG ((EFI_D_ERROR, "PerformNvdimmPurge ERROR: Factory Default operation failed\n"));
        return EFI_DEVICE_ERROR;
    }

    DEBUG ((EFI_D_ERROR, "PerformNvdimmPurge SUCCESS!\n"));
    return Status;
}

/**
    JedecNvdimm Driver Entry Point

    @param    ImageHandle
    @param    *SystemTable

    @retval   EFI_SUCCESS or EFI_NOT_FOUND

**/

EFI_STATUS
EFIAPI
JedecNvdimmEntryPoint (
    IN  EFI_HANDLE              ImageHandle,
    IN  EFI_SYSTEM_TABLE        *SystemTable
)
{
    EFI_STATUS              Status;
    EFI_SMM_BASE2_PROTOCOL  *SmmBase2;
    EFI_PHYSICAL_ADDRESS    DsmAcpiSmmDataAddress;
    EFI_ACPI_SDT_PROTOCOL   *AcpiSdtProtocol;
    UINTN                   AcpiTblIndex;
    EFI_ACPI_SDT_HEADER     *AcpiTbl = NULL;
    EFI_ACPI_TABLE_VERSION  Version;
    UINTN                   AcpiHandle;
    EFI_PHYSICAL_ADDRESS    Dsdt;
    EFI_PHYSICAL_ADDRESS    XDsdt;
    EFI_PHYSICAL_ADDRESS    DsdtAddr=0;
    UINT32                  DsdtSize;
    UINT8                   *CurrentPtr;
    UINT32                  *CurrentSig;
    UINT16                  TotalNvdimm;
    EFI_HANDLE              Handle = NULL;

    DEBUG ((EFI_D_ERROR, "JedecNvdimm Entry\n"));
    
    Status = gBS->LocateProtocol (&gEfiSmmBase2ProtocolGuid, NULL, (VOID**)&SmmBase2);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    Status = SmmBase2->GetSmstLocation (SmmBase2, &gSmst);
    if (EFI_ERROR (Status)) {
        return EFI_UNSUPPORTED;
    }
    
    // Initialize NVDIMM bitmap
    gNvdimmBitMap = 0;
    
    //
    // Initial Smbus variables
    //
    Status = JedecNvdimmSmbusInit ();
    ASSERT_EFI_ERROR (Status);
    
    //
    // Allocate ACPI to SMM data buffer
    //
    DsmAcpiSmmDataAddress = 0xFFFFFFFF;
    Status = gBS->AllocatePages (
                AllocateMaxAddress,
                EfiACPIMemoryNVS,
                EFI_SIZE_TO_PAGES (sizeof(DSM_ACPI_SMM_DATA)),
                &DsmAcpiSmmDataAddress);
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "Unable to allocate ACPI NVS memory!\n"));
        return Status;
    }
    
    pDsmAcpiSmmData = (DSM_ACPI_SMM_DATA *)DsmAcpiSmmDataAddress;
    gBS->SetMem (pDsmAcpiSmmData, sizeof(DSM_ACPI_SMM_DATA), 0);
    
    //
    // Update ACPI buffer address to point to pDsmAcpiSmmData
    //
    Dsdt = 0;
    XDsdt = 0;

    Status = gBS->LocateProtocol (&gEfiAcpiSdtProtocolGuid, NULL, &AcpiSdtProtocol);
    if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, "LocateProtocol EFI_ACPI_SDT_PROTOCOL_GUID failure, return status %x\n", Status));
        return EFI_NOT_AVAILABLE_YET;
    }
    
    for (AcpiTblIndex = 0; ; AcpiTblIndex++) {
        Status = AcpiSdtProtocol->GetAcpiTable (AcpiTblIndex, &AcpiTbl, &Version, &AcpiHandle);

        if (AcpiTbl->Signature == EFI_ACPI_6_0_FIXED_ACPI_DESCRIPTION_TABLE_SIGNATURE) {    // ('F', 'A', 'C', 'P')
            if (Version == EFI_ACPI_TABLE_VERSION_1_0B) {
                Dsdt = (EFI_PHYSICAL_ADDRESS) (((EFI_ACPI_6_0_FIXED_ACPI_DESCRIPTION_TABLE *) AcpiTbl)->Dsdt);
                DEBUG ((EFI_D_ERROR, "DSDT pointer = %08lX\n", Dsdt));
            }

            if ((Version & EFI_ACPI_TABLE_VERSION_X) != 0) {
                Dsdt = (EFI_PHYSICAL_ADDRESS) (((EFI_ACPI_6_0_FIXED_ACPI_DESCRIPTION_TABLE *) AcpiTbl)->Dsdt);
                XDsdt = (EFI_PHYSICAL_ADDRESS) (((EFI_ACPI_6_0_FIXED_ACPI_DESCRIPTION_TABLE *) AcpiTbl)->XDsdt);
                DEBUG ((EFI_D_ERROR, "DSDT pointer = %08lX, X_DSDT pointer = %08lX\n", Dsdt, XDsdt));
            }
        }

        gBS->FreePool((VOID *) AcpiTbl);    // GetAcpiTable allocates pool, need to free it here

        if (Dsdt || XDsdt) {
            break;
        }
    }

    if ((Dsdt != 0) && (XDsdt == 0)) {
        DsdtAddr = Dsdt;
        Status = EFI_SUCCESS;
    } else if ((Dsdt == 0) && (XDsdt != 0)) {
        DsdtAddr = XDsdt;
        Status = EFI_SUCCESS;
    } else {
        DEBUG ((EFI_D_ERROR, "Both DSDT & X_DSDT pointer are not NULL, invalid\n"));
        ASSERT (FALSE);
    }
    
    DsdtSize = ((ACPI_HDR *) DsdtAddr)->Length;
    CurrentPtr = (UINT8 *) DsdtAddr;
    
    // Search for ('N', 'V', 'D', 'M')
    Status = EFI_NOT_FOUND;
    while ((UINTN) CurrentPtr < ((UINTN) DsdtAddr + (UINTN) DsdtSize)) {
        CurrentSig = (UINT32 *) CurrentPtr;
        if (*CurrentSig == SIGNATURE_32 ('N', 'V', 'D', 'M')) {
            *(UINT32 *)CurrentPtr = (UINT32)(UINTN)pDsmAcpiSmmData;
            Status = EFI_SUCCESS;
            break;
        }
        CurrentPtr++;
    }
    ASSERT_EFI_ERROR (Status);

    //
    // Create NFIT tables
    //
    Status = GenerateJedecNvdimmAcpi(&TotalNvdimm);
    pDsmAcpiSmmData->NvdimmBitMap = gNvdimmBitMap;
    ASSERT_EFI_ERROR (Status);
    if (TotalNvdimm == 0) {
        DEBUG ((EFI_D_ERROR, "No NVDIMMs found, JedecNvdimm Exit\n"));
        return EFI_SUCCESS;
    }
    
    //
    // Install DSM SMI handler
    //
    Status = InstallDsmSmiHandler();
    ASSERT_EFI_ERROR (Status);
    
    //
    // Set NVDIMM event notifications
    //
    Status = SetEventNotifications(TotalNvdimm);
    ASSERT_EFI_ERROR (Status);
    
    //
    // Install JEDEC NVDIMM SMM Protocol
    //
    Status = gSmst->SmmInstallProtocolInterface (
                    &Handle,
                    &gJedecNvdimmSmmProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &JedecNvdimmSmmProtocol
                    );
    ASSERT_EFI_ERROR (Status);
    
    DEBUG ((EFI_D_ERROR, "JedecNvdimm Exit\n"));
    
    return Status;
}


