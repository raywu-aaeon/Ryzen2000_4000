/* $NoKeywords:$ */
/**
 * @file
 *
 * JedecNvdimmDsm.c
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
 ******************************************************************************
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

/** @file JedecNvdimmDsm.c
    JedecNvdimmDsm Driver Implementation

**/

//---------------------------------------------------------------------------

#include "JedecNvdimm.h"
#include "JedecNvdimmDsm.h"
#include <Library/BaseMemoryLib.h>
#include <Library/BaseLib.h>
#include <Library/HobLib.h>

//---------------------------------------------------------------------------

extern DSM_ACPI_SMM_DATA   *pDsmAcpiSmmData;
extern EFI_GUID gAmdNvdimmSpdInfoHobGuid;
extern EFI_STATUS StartTimeout(IN SMM_TIMEOUT *Timeout, IN UINTN Time);
extern EFI_STATUS HasItTimedOut(IN SMM_TIMEOUT *Timeout);
extern EFI_STATUS ReadNvdimm (UINT8 Socket, UINT8 Channel, UINT8 Dimm, UINT8 Page, UINT8 Register, UINT8 *Data, BOOLEAN IsSpd);
extern EFI_STATUS WriteNvdimm (UINT8 Socket, UINT8 Channel, UINT8 Dimm, UINT8 Page, UINT8 Register, UINT8 *Data, BOOLEAN IsSpd);

#define DSM_DEBUG_PRINT 0

#if DSM_DEBUG_PRINT
#define DSM_DEBUG(Arguments) DEBUG(Arguments)
#else
#define DSM_DEBUG(Arguments)
#endif

//
// Platform specific settings
//
UINT8 gDsmErrorInjectionEnable;

#if 0
/**
    Clear the Memory.

    @param Buffer
    @param Size

    @retval VOID
**/
VOID 
ZeroMem (
    IN  VOID    *Buffer,
    IN  UINTN   Size
)
{
    UINT8 *Ptr;

    Ptr = Buffer;
    while ( Size-- )
    {
        *(Ptr++) = 0;
    }
}
#endif
/**
    Set NVDIMM event notifications

    @param  TotalNvdimm
    
    @retval  Status
    
**/

EFI_STATUS
SetEventNotifications (
    IN  UINT16 TotalNvdimm
    )
{
    EFI_STATUS          Status = EFI_SUCCESS;
    VOID                *HobAddr;
    NVDIMM_SPD_INFO     *NvdimmSpdInfo;
    UINTN               i;
    UINT8               Data;
    UINT8               EventNotifications = 0;
    
    HobAddr = GetFirstGuidHob (&gAmdNvdimmSpdInfoHobGuid);
    if (HobAddr == NULL) {
        DEBUG ((EFI_D_ERROR, "gAmdNvdimmSpdInfoHobGuid hob not found!\n"));
        return EFI_UNSUPPORTED;
    }
    NvdimmSpdInfo = (NVDIMM_SPD_INFO *) GET_GUID_HOB_DATA (HobAddr);
    
    for (i = 0; i < TotalNvdimm; i++) {
        // Find out what events are supported
        ReadNvdimm(NvdimmSpdInfo[i].Socket, NvdimmSpdInfo[i].Channel, NvdimmSpdInfo[i].Dimm, 0, PAGE0_EVENT_NOTIFICATION_SUPPORT, &Data, FALSE);
        DEBUG ((EFI_D_ERROR, "Event Notifications Supported: S[%d] C[%d] D[%d] = 0x%X\n", NvdimmSpdInfo[i].Socket, NvdimmSpdInfo[i].Channel, NvdimmSpdInfo[i].Dimm, Data));
        if (Data & BIT0) EventNotifications |= BIT0;     // Persistency notification
        if (Data & BIT1) EventNotifications |= BIT1;     // Warning threshold notification
        if (Data & BIT2) EventNotifications |= BIT2;     // Voltage regulator failed notification
        
        // Clear SET_EVENT_NOTIFICATION_CMD
        Data = 0;
        WriteNvdimm(NvdimmSpdInfo[i].Socket, NvdimmSpdInfo[i].Channel, NvdimmSpdInfo[i].Dimm, 0, PAGE0_SET_EVENT_NOTIFICATION_CMD, &Data, FALSE);
        
        // Deassert the EVENT_N pin in case previous event occured
        Data = BIT2;
        WriteNvdimm(NvdimmSpdInfo[i].Socket, NvdimmSpdInfo[i].Channel, NvdimmSpdInfo[i].Dimm, 0, PAGE0_NVDIMM_MGT_CMD1, &Data, FALSE);
        
        // Set Event Notifcations that are supported
        WriteNvdimm(NvdimmSpdInfo[i].Socket, NvdimmSpdInfo[i].Channel, NvdimmSpdInfo[i].Dimm, 0, PAGE0_SET_EVENT_NOTIFICATION_CMD, &EventNotifications, FALSE);
        DEBUG ((EFI_D_ERROR, "Set Event Notifications: S[%d] C[%d] D[%d] = 0x%X\n", NvdimmSpdInfo[i].Socket, NvdimmSpdInfo[i].Channel, NvdimmSpdInfo[i].Dimm, EventNotifications));
    }
    
    return Status;
}

/**
    Abort Running Operation

    @param  Socket
    @param  Channel
    @param  Dimm
    
**/

VOID
AbortRunningOperation (
    IN  UINT8   Socket,
    IN  UINT8   Channel,
    IN  UINT8   Dimm
    )
{
    EFI_STATUS  Status = EFI_SUCCESS;
    UINT8       Data;
    SMM_TIMEOUT SmmTimeout;
    UINTN       TimeoutUs;  // Timeout value in microseconds
    
    DSM_DEBUG ((EFI_D_ERROR, "DSM: AbortRunningOperation Entry\n"));
    
    // Abort the running operation
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_ABORT_CMD_TIMEOUT, &Data, FALSE);
    TimeoutUs = Data;
    TimeoutUs *= 1000;                  // Convert milliseconds to microseconds
    
    Data = BIT4;                        // ABORT_CURRENT_OP
    WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_FUNC_CMD0, &Data, FALSE);
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
    if (!(Data & BIT5)) {
        // ABORT in progress bit not set, try again
        Data = BIT4;
        WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_FUNC_CMD0, &Data, FALSE);
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        if (!(Data & BIT5)) {
            // Unable to start operation on second try
            return;
        }
    }
    
    StartTimeout(&SmmTimeout, TimeoutUs);
    
    // Wait for ABORT in progress bit to be clear.
    do {
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        Status = HasItTimedOut(&SmmTimeout);
    } while((Data & BIT5) && !EFI_ERROR(Status));
}

/**
    Erase NVM Image (Function Index 19)

    @param  Socket
    @param  Channel
    @param  Dimm

    @retval  DsmStatus

**/

UINT32
EraseNvmImage (
    IN  UINT8   Socket,
    IN  UINT8   Channel,
    IN  UINT8   Dimm
    )
{
    EFI_STATUS  Status = EFI_SUCCESS;
    UINT8       Data;
    SMM_TIMEOUT SmmTimeout;
    UINTN       TimeoutUs;  // Timeout value in microseconds
    UINT32      DsmStatus = DSM_SUCCESS;
    
    DSM_DEBUG ((EFI_D_ERROR, "DSM: EraseNvmImage Entry\n"));
    
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_ERASE_TIMEOUT0, &Data, FALSE);
    TimeoutUs = Data;
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_ERASE_TIMEOUT1, &Data, FALSE);
    TimeoutUs |= ((Data & 0x7F) << 8);
    if (Data & BIT7) TimeoutUs *= 1000000;  // Convert seconds to microseconds
    else TimeoutUs *= 1000;                 // Convert milliseconds to microseconds
    StartTimeout(&SmmTimeout, TimeoutUs);
    
    // Wait for Controller NOT busy
    do {
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        Status = HasItTimedOut(&SmmTimeout);
    } while((Data & BIT0) && !EFI_ERROR(Status));
    
    // Set CL_ERASE_STAT to clear restore status register
    Data = BIT4;
    WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_MGT_CMD0, &Data, FALSE);
    
    // START_ERASE
    Data = BIT3;
    WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_FUNC_CMD0, &Data, FALSE);
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
    if (!(Data & BIT4)) {
        // ERASE in progress bit not set, try again
        Data = BIT3;
        WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_FUNC_CMD0, &Data, FALSE);
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        if (!(Data & BIT4)) {
            // Unable to start operation on second try
            return DSM_FUNCTION_ERROR_CODE;
        }
    }
    
    // Wait for ERASE in progress bit to be clear
    do {
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        Status = HasItTimedOut(&SmmTimeout);
    } while((Data & BIT4) && !EFI_ERROR(Status));
    
    // Check for timeout
    if (EFI_ERROR(Status)) {
        AbortRunningOperation(Socket, Channel, Dimm);
        DsmStatus = ((1 << 16) | DSM_FUNCTION_ERROR_CODE);   // 1: The operation timed out.
    }
    return DsmStatus;
}

/**
    Arm NVDIMM-N (Function Index 20)

    @param  Socket
    @param  Channel
    @param  Dimm

    @retval  DsmStatus

**/

UINT32
ArmNvdimm (
    IN  UINT8   Socket,
    IN  UINT8   Channel,
    IN  UINT8   Dimm
    )
{
    EFI_STATUS  Status = EFI_SUCCESS;
    UINT8       Data;
    SMM_TIMEOUT SmmTimeout;
    UINTN       TimeoutUs;  // Timeout value in microseconds
    UINT32      DsmStatus = DSM_SUCCESS;
    
    DSM_DEBUG ((EFI_D_ERROR, "DSM: ArmNvdimm Entry\n"));
    
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_ARM_TIMEOUT0, &Data, FALSE);
    TimeoutUs = Data;
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_ARM_TIMEOUT1, &Data, FALSE);
    TimeoutUs |= ((Data & 0x7F) << 8);
    if (Data & BIT7) TimeoutUs *= 1000000;  // Convert seconds to microseconds
    else TimeoutUs *= 1000;                 // Convert milliseconds to microseconds
    StartTimeout(&SmmTimeout, TimeoutUs);
    
    // Wait for Controller NOT busy
    do {
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        Status = HasItTimedOut(&SmmTimeout);
    } while((Data & BIT0) && !EFI_ERROR(Status));
    
    // Set CL_ARM_STAT to clear arm status register
    Data = BIT5;
    WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_MGT_CMD0, &Data, FALSE);
    
    // ARM_CMD: Set the appropriate bits to reflect the save triggers to be enabled
    Data = BIT0;
    WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_ARM_CMD, &Data, FALSE);
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
    if (!(Data & BIT6)) {
        // ARM in progress bit not set, try again
        Data = BIT0;
        WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_FUNC_CMD0, &Data, FALSE);
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        if (!(Data & BIT6)) {
            // Unable to start operation on second try
            return DSM_FUNCTION_ERROR_CODE;
        }
    }
    
    // Wait for ARM in progress bit to be clear
    do {
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        Status = HasItTimedOut(&SmmTimeout);
    } while((Data & BIT6) && !EFI_ERROR(Status));
    
    // Check for timeout
    if (EFI_ERROR(Status)) {
        AbortRunningOperation(Socket, Channel, Dimm);
        DsmStatus = ((1 << 16) | DSM_FUNCTION_ERROR_CODE);   // 1: The operation timed out.
    }
    return DsmStatus;
}

/**
    Reset to Factory Defaults (Function Index 21)

    @param  Socket
    @param  Channel
    @param  Dimm

    @retval  DsmStatus

**/

UINT32
ResetToFactoryDefaults (
    IN  UINT8   Socket,
    IN  UINT8   Channel,
    IN  UINT8   Dimm
    )
{
    EFI_STATUS  Status = EFI_SUCCESS;
    UINT8       Data;
    SMM_TIMEOUT SmmTimeout;
    UINTN       TimeoutUs;  // Timeout value in microseconds
    UINT32      DsmStatus = DSM_SUCCESS;
    
    DSM_DEBUG ((EFI_D_ERROR, "DSM: ResetToFactoryDefaults Entry\n"));
    
    TimeoutUs = 0xFFFFFFF;  // TODO: What should this timeout be?
    StartTimeout(&SmmTimeout, TimeoutUs);
    
    // Wait for Controller NOT busy
    do {
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        Status = HasItTimedOut(&SmmTimeout);
    } while((Data & BIT0) && !EFI_ERROR(Status));
    
    // Set CL_FACTORY_DEFAULT_STAT to clear factory default status register
    Data = BIT0;
    WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_MGT_CMD1, &Data, FALSE);
    
    // START_FACTORY_DEFAULT Operation
    Data = BIT0;
    WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_FUNC_CMD0, &Data, FALSE);
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
    if (!(Data & BIT1)) {
        // FACTORY_DEFAULT in progress bit not set, try again
        Data = BIT0;
        WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_FUNC_CMD0, &Data, FALSE);
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        if (!(Data & BIT1)) {
            // Unable to start operation on second try
            return DSM_FUNCTION_ERROR_CODE;
        }
    }
    
    // Wait for FACTORY_DEFAULT in progress bit to be clear
    do {
        DEBUG ((EFI_D_ERROR, "."));
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        Status = HasItTimedOut(&SmmTimeout);
    } while((Data & BIT1) && !EFI_ERROR(Status));
    
    DEBUG ((EFI_D_ERROR, "\n"));
    
    // Check for timeout
    if (EFI_ERROR(Status)) {
        AbortRunningOperation(Socket, Channel, Dimm);
        DsmStatus = ((1 << 16) | DSM_FUNCTION_ERROR_CODE);   // 1: The operation timed out.
    }
    return DsmStatus;
}

/**
    Start Firmware Update (Function Index 22)

    @param  Socket
    @param  Channel
    @param  Dimm
    @param  FirmwareSlot

    @retval  DsmStatus

**/

UINT32
StartFirmwareUpdate (
    IN  UINT8   Socket,
    IN  UINT8   Channel,
    IN  UINT8   Dimm,
    IN  UINT8   FirmwareSlot
    )
{
    EFI_STATUS  Status = EFI_SUCCESS;
    UINT8       Data;
    SMM_TIMEOUT SmmTimeout;
    UINTN       TimeoutUs;  // Timeout value in microseconds
    UINT32      DsmStatus = DSM_SUCCESS;
    
    DSM_DEBUG ((EFI_D_ERROR, "DSM: StartFirmwareUpdate Entry\n"));
    
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_TIMEOUT0, &Data, FALSE);
    TimeoutUs = Data;
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_TIMEOUT1, &Data, FALSE);
    TimeoutUs |= ((Data & 0x7F) << 8);
    if (Data & BIT7) TimeoutUs *= 1000000;  // Convert seconds to microseconds
    else TimeoutUs *= 1000;                 // Convert milliseconds to microseconds
    
    // Check if already in firmware update mode
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_STATUS, &Data, FALSE);
    if (Data & BIT2) {
        DsmStatus = ((1 << 16) | DSM_FUNCTION_ERROR_CODE);   // 1: There is a firmware update operation currently in progress.
        return DsmStatus;
    }
    
    // Set firmware image slot from input
    ReadNvdimm(Socket, Channel, Dimm, 3, PAGE3_FW_SLOT_INFO, &Data, FALSE);
    Data &= 0xF0;
    Data |= (FirmwareSlot & 0x0F);
    WriteNvdimm(Socket, Channel, Dimm, 3, PAGE3_FW_SLOT_INFO, &Data, FALSE);
    
    StartTimeout(&SmmTimeout, TimeoutUs);
    
    // Wait for Controller NOT busy
    do {
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        Status = HasItTimedOut(&SmmTimeout);
    } while((Data & BIT0) && !EFI_ERROR(Status));
    
    // Set CL_FIRMWARE_OPS_STAT to clear firmware ops status register
    Data = BIT1;
    WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_MGT_CMD1, &Data, FALSE);
    
    // Enable firmware update mode
    Data = BIT0;
    WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_CMD, &Data, FALSE);
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
    if (!(Data & BIT7)) {
        // FIRMWARE_OPS in progress bit not set, try again
        Data = BIT0;
        WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_CMD, &Data, FALSE);
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        if (!(Data & BIT7)) {
            // Unable to start operation on second try
            return DSM_FUNCTION_ERROR_CODE;
        }
    }
    
    // Wait for FIRMWARE_OPS in progress bit to be clear
    do {
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        Status = HasItTimedOut(&SmmTimeout);
    } while((Data & BIT7) && !EFI_ERROR(Status));
    
    // Check for timeout
    if (EFI_ERROR(Status)) {
        AbortRunningOperation(Socket, Channel, Dimm);
        DsmStatus = DSM_FUNCTION_ERROR_CODE;   // The operation timed out
    }
    return DsmStatus;
}

/**
    CRC Algorithm

    @param  *ptr
    @param  count

    @retval  crc

**/

int Crc16 (
    char    *ptr,
    int     count
    )
{
    int crc, i;
    crc = 0;
    while (--count >= 0) {
        crc = crc ^ (int)*ptr++ << 8;
        for (i = 0; i < 8; ++i) {
            if (crc & 0x8000) {
                crc = crc << 1 ^ 0x1021;
            } else {
                crc = crc << 1;
            }
        }
    }
    return (crc & 0xFFFF);
}

/**
    Send Firmware Update Data (Function Index 23)

    @param  Socket
    @param  Channel
    @param  Dimm

    @retval  DsmStatus

**/

UINT32
SendFirmwareUpdateData (
    IN  UINT8   Socket,
    IN  UINT8   Channel,
    IN  UINT8   Dimm
    )
{
    EFI_STATUS  Status = EFI_SUCCESS;
    UINT8       Data;
    SMM_TIMEOUT SmmTimeout;
    UINTN       TimeoutUs;  // Timeout value in microseconds
    UINT32      DsmStatus = DSM_SUCCESS;
    UINT8       i;
    UINT16      Checksum;
    UINT16      FwRegionCrc;
    
    DSM_DEBUG ((EFI_D_ERROR, "DSM: SendFirmwareUpdateData Entry\n"));
    
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_TIMEOUT0, &Data, FALSE);
    TimeoutUs = Data;
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_TIMEOUT1, &Data, FALSE);
    TimeoutUs |= ((Data & 0x7F) << 8);
    if (Data & BIT7) TimeoutUs *= 1000000;  // Convert seconds to microseconds
    else TimeoutUs *= 1000;                 // Convert milliseconds to microseconds
    StartTimeout(&SmmTimeout, TimeoutUs);
    
    // Check if in firmware update mode
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_STATUS, &Data, FALSE);
    if ((Data & BIT2) == 0) {
        DsmStatus = ((1 << 16) | DSM_FUNCTION_ERROR_CODE);   // 1: There is no firmware update operation in progress.
        return DsmStatus;
    }
    
    // Validate region length
    if (((FIRMWARE_UPDATE_DATA *)pDsmAcpiSmmData->InputData)->RegionLength > FIRMWARE_DATA_LENGTH) {
        DsmStatus = ((2 << 16) | DSM_FUNCTION_ERROR_CODE);   // 2: Invalid region size.
        return DsmStatus;
    }
    
    // Set CL_FIRMWARE_OPS_STAT to clear firmware ops status register
    Data = BIT1;
    WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_MGT_CMD1, &Data, FALSE);
    
    // Clear firmware data region
    Data = BIT1;
    WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_CMD, &Data, FALSE);
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
    if (!(Data & BIT7)) {
        // FIRMWARE_OPS in progress bit not set, try again
        Data = BIT1;
        WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_CMD, &Data, FALSE);
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        if (!(Data & BIT7)) {
            // Unable to start operation on second try
            AbortRunningOperation(Socket, Channel, Dimm);
            DsmStatus = ((5 << 16) | DSM_FUNCTION_ERROR_CODE);   // 5: The firmware commit operation failed.
            return DsmStatus;
        }
    }
    
    // Wait for FIRMWARE_OPS in progress bit to be clear
    do {
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        Status = HasItTimedOut(&SmmTimeout);
    } while((Data & BIT7) && !EFI_ERROR(Status));
    
    // Check for timeout
    if (EFI_ERROR(Status)) {
        AbortRunningOperation(Socket, Channel, Dimm);
        DsmStatus = ((4 << 16) | DSM_FUNCTION_ERROR_CODE);   // 4: Operation timed out.
        return DsmStatus;
    }
    
    // Write TYPED_BLOCK_DATA register with value 0x1 (firmware image data)
    Data = 0x1;
    WriteNvdimm(Socket, Channel, Dimm, 3, PAGE3_TYPED_BLOCK_DATA, &Data, FALSE);
    
    // Write BLOCK_ID, REGION_ID0 and REGION_ID1 registers
    Data = (((FIRMWARE_UPDATE_DATA *)pDsmAcpiSmmData->InputData)->RegionId & 0xFF);
    WriteNvdimm(Socket, Channel, Dimm, 3, PAGE3_REGION_ID0, &Data, FALSE);
    Data = ((((FIRMWARE_UPDATE_DATA *)pDsmAcpiSmmData->InputData)->RegionId >> 8) & 0xFF);
    WriteNvdimm(Socket, Channel, Dimm, 3, PAGE3_REGION_ID1, &Data, FALSE);
    Data = ((FIRMWARE_UPDATE_DATA *)pDsmAcpiSmmData->InputData)->BlockId;
    WriteNvdimm(Socket, Channel, Dimm, 3, PAGE3_BLOCK_ID, &Data, FALSE);
    
    // Write firmware data
    for (i = 0; i < ((FIRMWARE_UPDATE_DATA *)pDsmAcpiSmmData->InputData)->RegionLength; i++) {
        Data = ((FIRMWARE_UPDATE_DATA *)pDsmAcpiSmmData->InputData)->FirmwareData[i];
        WriteNvdimm(Socket, Channel, Dimm, 3, PAGE3_TYPED_BLOCK_DATA_BYTE0 + i, &Data, FALSE);
    }
    
    // Calculate the checksum for the firmware data region transferred
    Checksum = (UINT16)Crc16(((FIRMWARE_UPDATE_DATA *)pDsmAcpiSmmData->InputData)->FirmwareData,
                             ((FIRMWARE_UPDATE_DATA *)pDsmAcpiSmmData->InputData)->RegionLength);
    
    // Set CL_FIRMWARE_OPS_STAT to clear firmware ops status register
    Data = BIT1;
    WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_MGT_CMD1, &Data, FALSE);
    
    StartTimeout(&SmmTimeout, TimeoutUs);
    
    // Generate firmware data region checksum
    Data = BIT2;
    WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_CMD, &Data, FALSE);
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
    if (!(Data & BIT7)) {
        // FIRMWARE_OPS in progress bit not set, try again
        Data = BIT2;
        WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_CMD, &Data, FALSE);
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        if (!(Data & BIT7)) {
            // Unable to start operation on second try
            AbortRunningOperation(Socket, Channel, Dimm);
            DsmStatus = ((5 << 16) | DSM_FUNCTION_ERROR_CODE);   // 5: The firmware commit operation failed.
            return DsmStatus;
        }
    }
    
    // Wait for FIRMWARE_OPS in progress bit to be clear
    do {
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        Status = HasItTimedOut(&SmmTimeout);
    } while((Data & BIT7) && !EFI_ERROR(Status));
    
    // Check for timeout
    if (EFI_ERROR(Status)) {
        AbortRunningOperation(Socket, Channel, Dimm);
        DsmStatus = ((4 << 16) | DSM_FUNCTION_ERROR_CODE);   // 4: Operation timed out.
        return DsmStatus;
    }
    
    // Validate CRC
    ReadNvdimm(Socket, Channel, Dimm, 3, PAGE3_FW_REGION_CRC0, &Data, FALSE);
    FwRegionCrc = Data;
    ReadNvdimm(Socket, Channel, Dimm, 3, PAGE3_FW_REGION_CRC1, &Data, FALSE);
    FwRegionCrc |= ((Data & 0xFF) << 8);
    if (FwRegionCrc != Checksum) {
        DsmStatus = ((3 << 16) | DSM_FUNCTION_ERROR_CODE);   // 3: Transfer failed due to data corruption.
    }
    
    // Set CL_FIRMWARE_OPS_STAT to clear firmware ops status register
    Data = BIT1;
    WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_MGT_CMD1, &Data, FALSE);
    
    StartTimeout(&SmmTimeout, TimeoutUs);
    
    // Commit firmware data region
    Data = BIT3;
    WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_CMD, &Data, FALSE);
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
    if (!(Data & BIT7)) {
        // FIRMWARE_OPS in progress bit not set, try again
        Data = BIT3;
        WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_CMD, &Data, FALSE);
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        if (!(Data & BIT7)) {
            // Unable to start operation on second try
            AbortRunningOperation(Socket, Channel, Dimm);
            DsmStatus = ((5 << 16) | DSM_FUNCTION_ERROR_CODE);   // 5: The firmware commit operation failed.
            return DsmStatus;
        }
    }
    
    // Wait for FIRMWARE_OPS in progress bit to be clear
    do {
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        Status = HasItTimedOut(&SmmTimeout);
    } while((Data & BIT7) && !EFI_ERROR(Status));
    
    // Check for timeout
    if (EFI_ERROR(Status)) {
        AbortRunningOperation(Socket, Channel, Dimm);
        DsmStatus = ((4 << 16) | DSM_FUNCTION_ERROR_CODE);   // 4: Operation timed out.
        return DsmStatus;
    }
    
    return DsmStatus;
}

/**
    Finish Firmware Update (Function Index 24)

    @param  Socket
    @param  Channel
    @param  Dimm

    @retval  DsmStatus

**/

UINT32
FinishFirmwareUpdate (
    IN  UINT8   Socket,
    IN  UINT8   Channel,
    IN  UINT8   Dimm
    )
{
    EFI_STATUS  Status = EFI_SUCCESS;
    UINT8       Data;
    SMM_TIMEOUT SmmTimeout;
    UINTN       TimeoutUs;  // Timeout value in microseconds
    UINT32      DsmStatus = DSM_SUCCESS;
    
    DSM_DEBUG ((EFI_D_ERROR, "DSM: FinishFirmwareUpdate Entry\n"));
    
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_TIMEOUT0, &Data, FALSE);
    TimeoutUs = Data;
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_TIMEOUT1, &Data, FALSE);
    TimeoutUs |= ((Data & 0x7F) << 8);
    if (Data & BIT7) TimeoutUs *= 1000000;  // Convert seconds to microseconds
    else TimeoutUs *= 1000;                 // Convert milliseconds to microseconds
    StartTimeout(&SmmTimeout, TimeoutUs);
    
    // Check if in firmware update mode
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_STATUS, &Data, FALSE);
    if ((Data & BIT2) == 0) {
        DsmStatus = ((1 << 16) | DSM_FUNCTION_ERROR_CODE);   // 1: There is no firmware update operation in progress.
        return DsmStatus;
    }
    
    // Set CL_FIRMWARE_OPS_STAT to clear firmware ops status register
    Data = BIT1;
    WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_MGT_CMD1, &Data, FALSE);
    
    // Validate firmware image
    Data = BIT5;
    WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_CMD, &Data, FALSE);
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
    if (!(Data & BIT7)) {
        // FIRMWARE_OPS in progress bit not set, try again
        Data = BIT5;
        WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_CMD, &Data, FALSE);
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        if (!(Data & BIT7)) {
            // Unable to start operation on second try
            AbortRunningOperation(Socket, Channel, Dimm);
            DsmStatus = DSM_FUNCTION_ERROR_CODE;
            return DsmStatus;
        }
    }
    
    // Wait for FIRMWARE_OPS in progress bit to be clear
    do {
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        Status = HasItTimedOut(&SmmTimeout);
    } while((Data & BIT7) && !EFI_ERROR(Status));
    
    // Check for timeout
    if (EFI_ERROR(Status)) {
        AbortRunningOperation(Socket, Channel, Dimm);
        DsmStatus = DSM_FUNCTION_ERROR_CODE;   // Operation timed out
        return DsmStatus;
    }
    
    // Check if FIRMWARE_OPS operation failed, indicating invalid firmware image
    ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_STATUS, &Data, FALSE);
    if (Data & BIT1) {
        DsmStatus = ((2 << 16) | DSM_FUNCTION_ERROR_CODE);   // 2: Invalid firmware image.
        return DsmStatus;
    }
    
    StartTimeout(&SmmTimeout, TimeoutUs);
    
    // Set CL_FIRMWARE_OPS_STAT to clear firmware ops status register
    Data = BIT1;
    WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_MGT_CMD1, &Data, FALSE);
    
    // Writes FIRMWARE_OPS_CMD register with the value 0x0 to disable firmware update mode
    Data = 0x0;
    WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_CMD, &Data, FALSE);
    
    // Wait for FIRMWARE_OPS in progress bit to be clear
    do {
        ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVDIMM_CMD_STATUS0, &Data, FALSE);
        Status = HasItTimedOut(&SmmTimeout);
    } while((Data & BIT7) && !EFI_ERROR(Status));
    
    // Check for timeout
    if (EFI_ERROR(Status)) {
        AbortRunningOperation(Socket, Channel, Dimm);
        DsmStatus = DSM_FUNCTION_ERROR_CODE;   // Operation timed out
        return DsmStatus;
    }
    return DsmStatus;
}

/**
    Handle SWSMI generated from OS DSM command

    @param  DispatchHandle,
    @param  *DispatchContext OPTIONAL,
    @param  *CommBuffer OPTIONAL,
    @param  *CommBufferSize OPTIONAL
  
    @retval  EFI_STATUS

**/

EFI_STATUS
EFIAPI
ExecuteDsmCommand (
    IN  EFI_HANDLE      DispatchHandle,
    IN  CONST   VOID    *DispatchContext OPTIONAL,
    IN  OUT     VOID    *CommBuffer OPTIONAL,
    IN  OUT     UINTN   *CommBufferSize OPTIONAL
    )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    UINT32                      DsmStatus = DSM_SUCCESS;
    UINT8                       Socket;
    UINT8                       Channel;
    UINT8                       Dimm;
    UINT8                       Data;
    UINT8                       Page, Offset;
    UINT8                       i;
    
    Socket = (UINT8)((pDsmAcpiSmmData->NfitDeviceHandle >> 12) & 0xF);
    Channel = (UINT8)((pDsmAcpiSmmData->NfitDeviceHandle >> 4) & 0xF);
    Dimm = (UINT8)(pDsmAcpiSmmData->NfitDeviceHandle & 0xF);
    
    DEBUG ((EFI_D_ERROR, "ExecuteDsmCommand (Function Index %d): Socket %d, Channel %d, Dimm %d\n", pDsmAcpiSmmData->FunctionIndex, Socket, Channel, Dimm));
    
    switch (pDsmAcpiSmmData->FunctionIndex) {
    
        // Get NVDIMM-N Identification (Function Index 1)
        case 1:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Get NVDIMM-N Identification (Function Index 1)\n"));
            ZeroMem(pDsmAcpiSmmData->OutputData, sizeof(NVDIMM_N_IDENTIFICATION));  // Init OutputData to 0
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_SPECREV, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->SpecificationRevision = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_SPECREV (0x%X) = 0x%X\n", PAGE0_SPECREV, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_STD_NUM_PAGES, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->NumberOfStandardPages = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_STD_NUM_PAGES (0x%X) = 0x%X\n", PAGE0_STD_NUM_PAGES, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_VENDOR_START_PAGES, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->FirstVendorPage = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_VENDOR_START_PAGES (0x%X) = 0x%X\n", PAGE0_VENDOR_START_PAGES, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_VENDOR_NUM_PAGES, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->NumberOfVendorPages = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_VENDOR_NUM_PAGES (0x%X) = 0x%X\n", PAGE0_VENDOR_NUM_PAGES, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_HWREV, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->HardwareRevision.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_HWREV (0x%X) = 0x%X\n", PAGE0_HWREV, Data));
            ReadNvdimm(Socket, Channel, Dimm, 3, PAGE3_FW_SLOT_INFO, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->CurrentFirmwareSlot = (Data >> 4) & 0xF;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE3_FW_SLOT_INFO (0x%X) = 0x%X\n", PAGE3_FW_SLOT_INFO, (Data >> 4) & 0xF));
            if (((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->CurrentFirmwareSlot == 0) {
                ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_SLOT0_FWREV0, &Data, FALSE);
                ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->FirmwareRevision.Byte0 = Data;
                DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_SLOT0_FWREV0 (0x%X) = 0x%X\n", PAGE0_SLOT0_FWREV0, Data));
                ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_SLOT0_FWREV1, &Data, FALSE);
                ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->FirmwareRevision.Byte1 = Data;
                DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_SLOT0_FWREV1 (0x%X) = 0x%X\n", PAGE0_SLOT0_FWREV1, Data));
            }
            else {
                ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_SLOT1_FWREV0, &Data, FALSE);
                ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->FirmwareRevision.Byte0 = Data;
                DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_SLOT1_FWREV0 (0x%X) = 0x%X\n", PAGE0_SLOT1_FWREV0, Data));
                ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_SLOT1_FWREV1, &Data, FALSE);
                ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->FirmwareRevision.Byte1 = Data;
                DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_SLOT1_FWREV1 (0x%X) = 0x%X\n", PAGE0_SLOT1_FWREV1, Data));
            }
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->FirmwareSlotCount = 2;    // For JEDEC-compliant devices, this field shall be 2.
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_CAPABILITIES, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->Capabilities = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_CAPABILITIES (0x%X) = 0x%X\n", PAGE0_CAPABILITIES, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_CSAVE_TRIGGER_SUPPORT, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->SupportedBackupTriggers = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_CSAVE_TRIGGER_SUPPORT (0x%X) = 0x%X\n", PAGE0_CSAVE_TRIGGER_SUPPORT, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_HOST_MAX_OPERATION_RETRY, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->MaximumOperationRetryCount = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_HOST_MAX_OPERATION_RETRY (0x%X) = 0x%X\n", PAGE0_HOST_MAX_OPERATION_RETRY, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_EVENT_NOTIFICATION_SUPPORT, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->SupportedNotificationEvents = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_EVENT_NOTIFICATION_SUPPORT (0x%X) = 0x%X\n", PAGE0_EVENT_NOTIFICATION_SUPPORT, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_CSAVE_TIMEOUT0, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->SaveOperationTimeout.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_CSAVE_TIMEOUT0 (0x%X) = 0x%X\n", PAGE0_CSAVE_TIMEOUT0, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_CSAVE_TIMEOUT1, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->SaveOperationTimeout.Byte1 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_CSAVE_TIMEOUT1 (0x%X) = 0x%X\n", PAGE0_CSAVE_TIMEOUT1, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_RESTORE_TIMEOUT0, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->RestoreOperationTimeout.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_RESTORE_TIMEOUT0 (0x%X) = 0x%X\n", PAGE0_RESTORE_TIMEOUT0, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_RESTORE_TIMEOUT1, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->RestoreOperationTimeout.Byte1 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_RESTORE_TIMEOUT1 (0x%X) = 0x%X\n", PAGE0_RESTORE_TIMEOUT1, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_ERASE_TIMEOUT0, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->EraseOperationTimeout.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_ERASE_TIMEOUT0 (0x%X) = 0x%X\n", PAGE0_ERASE_TIMEOUT0, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_ERASE_TIMEOUT1, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->EraseOperationTimeout.Byte1 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_ERASE_TIMEOUT1 (0x%X) = 0x%X\n", PAGE0_ERASE_TIMEOUT1, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_ARM_TIMEOUT0, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->ArmOperationTimeout.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_ARM_TIMEOUT0 (0x%X) = 0x%X\n", PAGE0_ARM_TIMEOUT0, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_ARM_TIMEOUT1, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->ArmOperationTimeout.Byte1 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_ARM_TIMEOUT1 (0x%X) = 0x%X\n", PAGE0_ARM_TIMEOUT1, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_TIMEOUT0, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->FirmwareOperationsTimeout.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_FIRMWARE_OPS_TIMEOUT0 (0x%X) = 0x%X\n", PAGE0_FIRMWARE_OPS_TIMEOUT0, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_FIRMWARE_OPS_TIMEOUT1, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->FirmwareOperationsTimeout.Byte1 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_FIRMWARE_OPS_TIMEOUT1 (0x%X) = 0x%X\n", PAGE0_FIRMWARE_OPS_TIMEOUT1, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_ABORT_CMD_TIMEOUT, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->AbortOperationTimeout.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_ABORT_CMD_TIMEOUT (0x%X) = 0x%X\n", PAGE0_ABORT_CMD_TIMEOUT, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_MIN_OPERATING_TEMP, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->MinimumOperatingTemperature = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_MIN_OPERATING_TEMP (0x%X) = 0x%X\n", PAGE0_MIN_OPERATING_TEMP, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_MAX_OPERATING_TEMP, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->MaximumOperationTemperature = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_MAX_OPERATING_TEMP (0x%X) = 0x%X\n", PAGE0_MAX_OPERATING_TEMP, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_REGION_BLOCK_SIZE, &Data, FALSE);
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->RegionBlockSize = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_REGION_BLOCK_SIZE (0x%X) = 0x%X\n", PAGE0_REGION_BLOCK_SIZE, Data));
            ((NVDIMM_N_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->Status = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(NVDIMM_N_IDENTIFICATION);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;
        
        // Get Save Operation Requirements (Function Index 2)
        case 2:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Get Save Operation Requirements (Function Index 2)\n"));
            ZeroMem(pDsmAcpiSmmData->OutputData, sizeof(SAVE_OPERATION_REQUIREMENTS));  // Init OutputData to 0
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_CSAVE_POWER_REQ0, &Data, FALSE);
            ((SAVE_OPERATION_REQUIREMENTS *)pDsmAcpiSmmData->OutputData)->AveragePowerRequirement.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_CSAVE_POWER_REQ0 (0x%X) = 0x%X\n", PAGE0_CSAVE_POWER_REQ0, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_CSAVE_POWER_REQ1, &Data, FALSE);
            ((SAVE_OPERATION_REQUIREMENTS *)pDsmAcpiSmmData->OutputData)->AveragePowerRequirement.Byte1 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_CSAVE_POWER_REQ1 (0x%X) = 0x%X\n", PAGE0_CSAVE_POWER_REQ1, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_CSAVE_IDLE_POWER_REQ0, &Data, FALSE);
            ((SAVE_OPERATION_REQUIREMENTS *)pDsmAcpiSmmData->OutputData)->IdlePowerRequirement.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_CSAVE_IDLE_POWER_REQ0 (0x%X) = 0x%X\n", PAGE0_CSAVE_IDLE_POWER_REQ0, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_CSAVE_IDLE_POWER_REQ1, &Data, FALSE);
            ((SAVE_OPERATION_REQUIREMENTS *)pDsmAcpiSmmData->OutputData)->IdlePowerRequirement.Byte1 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_CSAVE_IDLE_POWER_REQ1 (0x%X) = 0x%X\n", PAGE0_CSAVE_IDLE_POWER_REQ1, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_CSAVE_MIN_VOLT_REQ0, &Data, FALSE);
            ((SAVE_OPERATION_REQUIREMENTS *)pDsmAcpiSmmData->OutputData)->MinimumVoltageRequirement.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_CSAVE_MIN_VOLT_REQ0 (0x%X) = 0x%X\n", PAGE0_CSAVE_MIN_VOLT_REQ0, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_CSAVE_MIN_VOLT_REQ1, &Data, FALSE);
            ((SAVE_OPERATION_REQUIREMENTS *)pDsmAcpiSmmData->OutputData)->MinimumVoltageRequirement.Byte1 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_CSAVE_MIN_VOLT_REQ1 (0x%X) = 0x%X\n", PAGE0_CSAVE_MIN_VOLT_REQ1, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_CSAVE_MAX_VOLT_REQ0, &Data, FALSE);
            ((SAVE_OPERATION_REQUIREMENTS *)pDsmAcpiSmmData->OutputData)->MaximumVoltageRequirement.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_CSAVE_MAX_VOLT_REQ0 (0x%X) = 0x%X\n", PAGE0_CSAVE_MAX_VOLT_REQ0, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_CSAVE_MAX_VOLT_REQ1, &Data, FALSE);
            ((SAVE_OPERATION_REQUIREMENTS *)pDsmAcpiSmmData->OutputData)->MaximumVoltageRequirement.Byte1 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_CSAVE_MAX_VOLT_REQ1 (0x%X) = 0x%X\n", PAGE0_CSAVE_MAX_VOLT_REQ1, Data));
            ((SAVE_OPERATION_REQUIREMENTS *)pDsmAcpiSmmData->OutputData)->Status = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(SAVE_OPERATION_REQUIREMENTS);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;

        // Get Energy Source Identification (Function Index 3)
        case 3:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Get Energy Source Identification (Function Index 3)\n"));
            ZeroMem(pDsmAcpiSmmData->OutputData, sizeof(ENERGY_SOURCE_IDENTIFICATION));  // Init OutputData to 0
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_ENERGY_SOURCE_POLICY, &Data, FALSE);
            ((ENERGY_SOURCE_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->EnergySourcePolicy = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_ENERGY_SOURCE_POLICY (0x%X) = 0x%X\n", PAGE0_ENERGY_SOURCE_POLICY, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_SET_ES_POLICY_STATUS, &Data, FALSE);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_SET_ES_POLICY_STATUS (0x%X) = 0x%X\n", PAGE0_SET_ES_POLICY_STATUS, Data));
            if (Data & BIT2) {
                ReadNvdimm(Socket, Channel, Dimm, 1, PAGE1_ES_HWREV, &Data, FALSE);
                ((ENERGY_SOURCE_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->DeviceManagedEsIdentification.EsHardwareRevision.Byte0 = Data;
                DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE1_ES_HWREV (0x%X) = 0x%X\n", PAGE1_ES_HWREV, Data));
                ReadNvdimm(Socket, Channel, Dimm, 1, PAGE1_ES_FWREV0, &Data, FALSE);
                ((ENERGY_SOURCE_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->DeviceManagedEsIdentification.EsFirmwareRevision.Byte0 = Data;
                DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE1_ES_FWREV0 (0x%X) = 0x%X\n", PAGE1_ES_FWREV0, Data));
                ReadNvdimm(Socket, Channel, Dimm, 1, PAGE1_ES_FWREV1, &Data, FALSE);
                ((ENERGY_SOURCE_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->DeviceManagedEsIdentification.EsFirmwareRevision.Byte1 = Data;
                DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE1_ES_FWREV1 (0x%X) = 0x%X\n", PAGE1_ES_FWREV1, Data));
                ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_AUTO_ES_HEALTH_FREQUENCY, &Data, FALSE);
                ((ENERGY_SOURCE_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->DeviceManagedEsIdentification.EsHealthCheckFrequency = Data;
                DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_AUTO_ES_HEALTH_FREQUENCY (0x%X) = 0x%X\n", PAGE0_AUTO_ES_HEALTH_FREQUENCY, Data));
                ReadNvdimm(Socket, Channel, Dimm, 1, PAGE1_ES_CHARGE_TIMEOUT0, &Data, FALSE);
                ((ENERGY_SOURCE_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->DeviceManagedEsIdentification.EsChargeTimeout.Byte0 = Data;
                DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE1_ES_CHARGE_TIMEOUT0 (0x%X) = 0x%X\n", PAGE1_ES_CHARGE_TIMEOUT0, Data));
                ReadNvdimm(Socket, Channel, Dimm, 1, PAGE1_ES_CHARGE_TIMEOUT1, &Data, FALSE);
                ((ENERGY_SOURCE_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->DeviceManagedEsIdentification.EsChargeTimeout.Byte1 = Data;
                DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE1_ES_CHARGE_TIMEOUT1 (0x%X) = 0x%X\n", PAGE1_ES_CHARGE_TIMEOUT1, Data));
                ReadNvdimm(Socket, Channel, Dimm, 1, PAGE1_MIN_ES_OPERATING_TEMP, &Data, FALSE);
                ((ENERGY_SOURCE_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->DeviceManagedEsIdentification.EsMinimumOperatingTemperature = Data;
                DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE1_MIN_ES_OPERATING_TEMP (0x%X) = 0x%X\n", PAGE1_MIN_ES_OPERATING_TEMP, Data));
                ReadNvdimm(Socket, Channel, Dimm, 1, PAGE1_MAX_ES_OPERATING_TEMP, &Data, FALSE);
                ((ENERGY_SOURCE_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->DeviceManagedEsIdentification.EsMaximumOperatingTemperature = Data;
                DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE1_MAX_ES_OPERATING_TEMP (0x%X) = 0x%X\n", PAGE1_MAX_ES_OPERATING_TEMP, Data));
                ReadNvdimm(Socket, Channel, Dimm, 1, PAGE1_ES_ATTRIBUTES, &Data, FALSE);
                ((ENERGY_SOURCE_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->DeviceManagedEsIdentification.EsAttributes = Data;
                DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE1_ES_ATTRIBUTES (0x%X) = 0x%X\n", PAGE1_ES_ATTRIBUTES, Data));
                ReadNvdimm(Socket, Channel, Dimm, 1, PAGE1_ES_TECH, &Data, FALSE);
                ((ENERGY_SOURCE_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->DeviceManagedEsIdentification.EsTechnology = Data;
                DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE1_ES_TECH (0x%X) = 0x%X\n", PAGE1_ES_TECH, Data));
            }
            else if (Data & BIT3) {
                ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_AUTO_ES_HEALTH_FREQUENCY, &Data, FALSE);
                ((ENERGY_SOURCE_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->HostManagedEsIdentification.EsHealthCheckFrequency = Data;
                DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_AUTO_ES_HEALTH_FREQUENCY (0x%X) = 0x%X\n", PAGE0_AUTO_ES_HEALTH_FREQUENCY, Data));
                ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_HOST_MANAGED_ES_ATTRIBUTES, &Data, FALSE);
                ((ENERGY_SOURCE_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->HostManagedEsIdentification.EsAttributes = Data;
                DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE2_HOST_MANAGED_ES_ATTRIBUTES (0x%X) = 0x%X\n", PAGE2_HOST_MANAGED_ES_ATTRIBUTES, Data));
                ReadNvdimm(Socket, Channel, Dimm, 1, PAGE1_ES_TECH, &Data, FALSE);
                ((ENERGY_SOURCE_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->HostManagedEsIdentification.EsTechnology = Data;
                DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE1_ES_TECH (0x%X) = 0x%X\n", PAGE1_ES_TECH, Data));
            }
            ((ENERGY_SOURCE_IDENTIFICATION *)pDsmAcpiSmmData->OutputData)->Status = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(ENERGY_SOURCE_IDENTIFICATION);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;
      
        //  Get Last Backup Information (Function Index 4)
        case 4:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Get Last Backup Information (Function Index 4)\n"));
            ZeroMem(pDsmAcpiSmmData->OutputData, sizeof(LAST_BACKUP_INFORMATION));  // Init OutputData to 0
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_CSAVE_INFO0, &Data, FALSE);
            ((LAST_BACKUP_INFORMATION *)pDsmAcpiSmmData->OutputData)->TriggerInformation.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_CSAVE_INFO0 (0x%X) = 0x%X\n", PAGE0_CSAVE_INFO0, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_CSAVE_FAIL_INFO0, &Data, FALSE);
            ((LAST_BACKUP_INFORMATION *)pDsmAcpiSmmData->OutputData)->SaveFailureInformation.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_CSAVE_FAIL_INFO0 (0x%X) = 0x%X\n", PAGE0_CSAVE_FAIL_INFO0, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_CSAVE_FAIL_INFO1, &Data, FALSE);
            ((LAST_BACKUP_INFORMATION *)pDsmAcpiSmmData->OutputData)->SaveFailureInformation.Byte1 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_CSAVE_FAIL_INFO1 (0x%X) = 0x%X\n", PAGE0_CSAVE_FAIL_INFO1, Data));
            ((LAST_BACKUP_INFORMATION *)pDsmAcpiSmmData->OutputData)->Status = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(LAST_BACKUP_INFORMATION);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;
      
        // Get NVM Thresholds (Function Index 5)
        case 5:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Get NVM Thresholds (Function Index 5)\n"));
            ZeroMem(pDsmAcpiSmmData->OutputData, sizeof(NVM_THRESHOLDS));  // Init OutputData to 0
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVM_LIFETIME_WARNING_THRESHOLD, &Data, FALSE);
            ((NVM_THRESHOLDS *)pDsmAcpiSmmData->OutputData)->NvmLifetimePercentageWarningThreshold = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_NVM_LIFETIME_WARNING_THRESHOLD (0x%X) = 0x%X\n", PAGE0_NVM_LIFETIME_WARNING_THRESHOLD, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVM_LIFETIME_ERROR_THRESHOLD, &Data, FALSE);
            ((NVM_THRESHOLDS *)pDsmAcpiSmmData->OutputData)->NvmLifetimePercentageErrorThreshold = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_NVM_LIFETIME_ERROR_THRESHOLD (0x%X) = 0x%X\n", PAGE0_NVM_LIFETIME_ERROR_THRESHOLD, Data));
            ((NVM_THRESHOLDS *)pDsmAcpiSmmData->OutputData)->Status = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(NVM_THRESHOLDS);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;

        // Set NVM Lifetime Percentage Warning Threshold (Function Index 6)
        case 6:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Set NVM Lifetime Percentage Warning Threshold (Function Index 6)\n"));
            DSM_DEBUG ((EFI_D_ERROR, "DSM: NvmLifetimePercentageWarningThreshold = 0x%X\n", ((NVM_LIFETIME_PERCENTAGE_WARNING_THRESHOLD *)pDsmAcpiSmmData->InputData)->NvmLifetimePercentageWarningThreshold));
            if((pDsmAcpiSmmData->InputDataSize != sizeof(NVM_LIFETIME_PERCENTAGE_WARNING_THRESHOLD)) ||
               (((NVM_LIFETIME_PERCENTAGE_WARNING_THRESHOLD *)pDsmAcpiSmmData->InputData)->NvmLifetimePercentageWarningThreshold > 100)) {
                DsmStatus = DSM_INVALID_INPUT_PARAMETERS;
            }
            else {
                Data = ((NVM_LIFETIME_PERCENTAGE_WARNING_THRESHOLD *)pDsmAcpiSmmData->InputData)->NvmLifetimePercentageWarningThreshold;
                WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVM_LIFETIME_WARNING_THRESHOLD, &Data, FALSE);
            }
            ((UINT32 *)pDsmAcpiSmmData->OutputData)[0] = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(UINT32);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;

        //  Get Energy Source Thresholds (Function Index 7)
        case 7:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Get Energy Source Thresholds (Function Index 7)\n"));
            ZeroMem(pDsmAcpiSmmData->OutputData, sizeof(ENERGY_SOURCE_THRESHOLDS));  // Init OutputData to 0
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_ES_LIFETIME_WARNING_THRESHOLD, &Data, FALSE);
            ((ENERGY_SOURCE_THRESHOLDS *)pDsmAcpiSmmData->OutputData)->EsLifetimePercentageWarningThreshold = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_ES_LIFETIME_WARNING_THRESHOLD (0x%X) = 0x%X\n", PAGE0_ES_LIFETIME_WARNING_THRESHOLD, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_ES_LIFETIME_ERROR_THRESHOLD, &Data, FALSE);
            ((ENERGY_SOURCE_THRESHOLDS *)pDsmAcpiSmmData->OutputData)->EsLifetimePercentageErrorThreshold = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_ES_LIFETIME_ERROR_THRESHOLD (0x%X) = 0x%X\n", PAGE0_ES_LIFETIME_ERROR_THRESHOLD, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_ES_TEMP_WARNING_THRESHOLD, &Data, FALSE);
            ((ENERGY_SOURCE_THRESHOLDS *)pDsmAcpiSmmData->OutputData)->EsTemperatureWarningThreshold = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_ES_TEMP_WARNING_THRESHOLD (0x%X) = 0x%X\n", PAGE0_ES_TEMP_WARNING_THRESHOLD, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_ES_TEMP_ERROR_THRESHOLD, &Data, FALSE);
            ((ENERGY_SOURCE_THRESHOLDS *)pDsmAcpiSmmData->OutputData)->EsTemperatureErrorThreshold = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_ES_TEMP_ERROR_THRESHOLD (0x%X) = 0x%X\n", PAGE0_ES_TEMP_ERROR_THRESHOLD, Data));
            ((ENERGY_SOURCE_THRESHOLDS *)pDsmAcpiSmmData->OutputData)->Status = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(ENERGY_SOURCE_THRESHOLDS);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;

        // Set Energy Source Lifetime Warning Threshold (Function Index 8)
        case 8:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Set Energy Source Lifetime Warning Threshold (Function Index 8)\n"));
            DSM_DEBUG ((EFI_D_ERROR, "DSM: EsLifetimePercentageWarningThreshold = 0x%X\n", ((ENERGY_SOURCE_LIFETIME_WARNING_THRESHOLD *)pDsmAcpiSmmData->InputData)->EsLifetimePercentageWarningThreshold));
            if((pDsmAcpiSmmData->InputDataSize != sizeof(ENERGY_SOURCE_LIFETIME_WARNING_THRESHOLD)) ||
               (((ENERGY_SOURCE_LIFETIME_WARNING_THRESHOLD *)pDsmAcpiSmmData->InputData)->EsLifetimePercentageWarningThreshold > 100)) {
                DsmStatus = DSM_INVALID_INPUT_PARAMETERS;
            }
            else {
                Data = ((ENERGY_SOURCE_LIFETIME_WARNING_THRESHOLD *)pDsmAcpiSmmData->InputData)->EsLifetimePercentageWarningThreshold;
                WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_ES_LIFETIME_WARNING_THRESHOLD, &Data, FALSE);
            }
            ((UINT32 *)pDsmAcpiSmmData->OutputData)[0] = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(UINT32);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;

        // Set Energy Source Temperature Warning Threshold (Function Index 9)
        case 9:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Set Energy Source Temperature Warning Threshold (Function Index 9)\n"));
            DSM_DEBUG ((EFI_D_ERROR, "DSM: EsLifetimeTemperatureWarningThreshold = 0x%X\n", ((ENERGY_SOURCE_TEMPERATURE_WARNING_THRESHOLD *)pDsmAcpiSmmData->InputData)->EsLifetimeTemperatureWarningThreshold));
            if(pDsmAcpiSmmData->InputDataSize != sizeof(ENERGY_SOURCE_TEMPERATURE_WARNING_THRESHOLD)) {
                DsmStatus = DSM_INVALID_INPUT_PARAMETERS;
            }
            else {
                Data = ((ENERGY_SOURCE_TEMPERATURE_WARNING_THRESHOLD *)pDsmAcpiSmmData->InputData)->EsLifetimeTemperatureWarningThreshold;
                WriteNvdimm(Socket, Channel, Dimm, 0, PAGE0_ES_TEMP_WARNING_THRESHOLD, &Data, FALSE);
            }
            ((UINT32 *)pDsmAcpiSmmData->OutputData)[0] = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(UINT32);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;

        // Get Critical Health Info (Function Index 10)
        case 10:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Get Critical Health Info (Function Index 10)\n"));
            ZeroMem(pDsmAcpiSmmData->OutputData, sizeof(CRITICAL_HEALTH_INFO));  // Init OutputData to 0
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_MODULE_HEALTH, &Data, FALSE);
            ((CRITICAL_HEALTH_INFO *)pDsmAcpiSmmData->OutputData)->CriticalHealthInfo = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_MODULE_HEALTH (0x%X) = 0x%X\n", PAGE0_MODULE_HEALTH, Data));
            ((CRITICAL_HEALTH_INFO *)pDsmAcpiSmmData->OutputData)->Status = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(CRITICAL_HEALTH_INFO);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;

        // Get NVDIMM-N Health Info (Function Index 11)
        case 11:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Get NVDIMM-N Health Info (Function Index 11)\n"));
            ZeroMem(pDsmAcpiSmmData->OutputData, sizeof(NVDIMM_N_HEALTH_INFO));  // Init OutputData to 0
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_MODULE_HEALTH_STATUS0, &Data, FALSE);
            ((NVDIMM_N_HEALTH_INFO *)pDsmAcpiSmmData->OutputData)->ModuleHealth.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_MODULE_HEALTH_STATUS0 (0x%X) = 0x%X\n", PAGE0_MODULE_HEALTH_STATUS0, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_MODULE_HEALTH_STATUS1, &Data, FALSE);
            ((NVDIMM_N_HEALTH_INFO *)pDsmAcpiSmmData->OutputData)->ModuleHealth.Byte1 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_MODULE_HEALTH_STATUS1 (0x%X) = 0x%X\n", PAGE0_MODULE_HEALTH_STATUS1, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, 0xE, &Data, TRUE);     // Byte 14 (0x00E): Module Thermal Sensor
            ((NVDIMM_N_HEALTH_INFO *)pDsmAcpiSmmData->OutputData)->ModuleCurrentTemperature = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Module Thermal Sensor (0xE) = 0x%X\n", Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_ERROR_THRESHOLD_STATUS, &Data, FALSE);
            ((NVDIMM_N_HEALTH_INFO *)pDsmAcpiSmmData->OutputData)->ErrorThresholdStatus = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_ERROR_THRESHOLD_STATUS (0x%X) = 0x%X\n", PAGE0_ERROR_THRESHOLD_STATUS, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_WARNING_THRESHOLD_STATUS, &Data, FALSE);
            ((NVDIMM_N_HEALTH_INFO *)pDsmAcpiSmmData->OutputData)->WarningThresholdStatus = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_WARNING_THRESHOLD_STATUS (0x%X) = 0x%X\n", PAGE0_WARNING_THRESHOLD_STATUS, Data));
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_NVM_LIFETIME, &Data, FALSE);
            ((NVDIMM_N_HEALTH_INFO *)pDsmAcpiSmmData->OutputData)->NvmLifetime = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_NVM_LIFETIME (0x%X) = 0x%X\n", PAGE0_NVM_LIFETIME, Data));
            ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_DRAM_ECC_ERROR_COUNT, &Data, FALSE);
            ((NVDIMM_N_HEALTH_INFO *)pDsmAcpiSmmData->OutputData)->CountofDramUncorrectableEccErrors = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE2_DRAM_ECC_ERROR_COUNT (0x%X) = 0x%X\n", PAGE2_DRAM_ECC_ERROR_COUNT, Data));
            ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_DRAM_THRESHOLD_ECC_COUNT, &Data, FALSE);
            ((NVDIMM_N_HEALTH_INFO *)pDsmAcpiSmmData->OutputData)->CountofDramCorrectableEccErrorAboveThresholdEvents = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE2_DRAM_THRESHOLD_ECC_COUNT (0x%X) = 0x%X\n", PAGE2_DRAM_THRESHOLD_ECC_COUNT, Data));
            ((NVDIMM_N_HEALTH_INFO *)pDsmAcpiSmmData->OutputData)->Status = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(NVDIMM_N_HEALTH_INFO);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;

        // Get Energy Source Health Info (Function Index 12)
        case 12:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Get Energy Source Health Info (Function Index 12)\n"));
            ZeroMem(pDsmAcpiSmmData->OutputData, sizeof(ENERGY_SOURCE_HEALTH_INFO));  // Init OutputData to 0
            ReadNvdimm(Socket, Channel, Dimm, 1, PAGE1_ES_LIFETIME, &Data, FALSE);
            ((ENERGY_SOURCE_HEALTH_INFO *)pDsmAcpiSmmData->OutputData)->EsLifetimePercentage = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE1_ES_LIFETIME (0x%X) = 0x%X\n", PAGE1_ES_LIFETIME, Data));
            ReadNvdimm(Socket, Channel, Dimm, 1, PAGE1_ES_TEMP0, &Data, FALSE);
            ((ENERGY_SOURCE_HEALTH_INFO *)pDsmAcpiSmmData->OutputData)->EsCurrentTemperature.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE1_ES_TEMP0 (0x%X) = 0x%X\n", PAGE1_ES_TEMP0, Data));
            ReadNvdimm(Socket, Channel, Dimm, 1, PAGE1_ES_TEMP1, &Data, FALSE);
            ((ENERGY_SOURCE_HEALTH_INFO *)pDsmAcpiSmmData->OutputData)->EsCurrentTemperature.Byte1 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE1_ES_TEMP1 (0x%X) = 0x%X\n", PAGE1_ES_TEMP1, Data));
            ReadNvdimm(Socket, Channel, Dimm, 1, PAGE1_ES_RUNTIME0, &Data, FALSE);
            ((ENERGY_SOURCE_HEALTH_INFO *)pDsmAcpiSmmData->OutputData)->TotalRuntime.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE1_ES_RUNTIME0 (0x%X) = 0x%X\n", PAGE1_ES_RUNTIME0, Data));
            ReadNvdimm(Socket, Channel, Dimm, 1, PAGE1_ES_RUNTIME1, &Data, FALSE);
            ((ENERGY_SOURCE_HEALTH_INFO *)pDsmAcpiSmmData->OutputData)->TotalRuntime.Byte1 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE1_ES_RUNTIME1 (0x%X) = 0x%X\n", PAGE1_ES_RUNTIME1, Data));
            ((ENERGY_SOURCE_HEALTH_INFO *)pDsmAcpiSmmData->OutputData)->Status = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(ENERGY_SOURCE_HEALTH_INFO);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;

        // Get Operational Statistics (Function Index 13)
        case 13:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Get Operational Statistics (Function Index 13)\n"));
            ZeroMem(pDsmAcpiSmmData->OutputData, sizeof(OPERATIONAL_STATISTICS));  // Init OutputData to 0
            ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_LAST_SAVE_DURATION0, &Data, FALSE);
            ((OPERATIONAL_STATISTICS *)pDsmAcpiSmmData->OutputData)->DurationOfLastSaveOperation.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE2_LAST_SAVE_DURATION0 (0x%X) = 0x%X\n", PAGE2_LAST_SAVE_DURATION0, Data));
            ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_LAST_SAVE_DURATION1, &Data, FALSE);
            ((OPERATIONAL_STATISTICS *)pDsmAcpiSmmData->OutputData)->DurationOfLastSaveOperation.Byte1 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE2_LAST_SAVE_DURATION1 (0x%X) = 0x%X\n", PAGE2_LAST_SAVE_DURATION1, Data));
            ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_LAST_RESTORE_DURATION0, &Data, FALSE);
            ((OPERATIONAL_STATISTICS *)pDsmAcpiSmmData->OutputData)->DurationOfLastRestoreOperation.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE2_LAST_RESTORE_DURATION0 (0x%X) = 0x%X\n", PAGE2_LAST_RESTORE_DURATION0, Data));
            ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_LAST_RESTORE_DURATION1, &Data, FALSE);
            ((OPERATIONAL_STATISTICS *)pDsmAcpiSmmData->OutputData)->DurationOfLastRestoreOperation.Byte1 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE2_LAST_RESTORE_DURATION1 (0x%X) = 0x%X\n", PAGE2_LAST_RESTORE_DURATION1, Data));
            ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_LAST_ERASE_DURATION0, &Data, FALSE);
            ((OPERATIONAL_STATISTICS *)pDsmAcpiSmmData->OutputData)->DurationOfLastEraseOperation.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE2_LAST_ERASE_DURATION0 (0x%X) = 0x%X\n", PAGE2_LAST_ERASE_DURATION0, Data));
            ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_LAST_ERASE_DURATION1, &Data, FALSE);
            ((OPERATIONAL_STATISTICS *)pDsmAcpiSmmData->OutputData)->DurationOfLastEraseOperation.Byte1 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE2_LAST_ERASE_DURATION1 (0x%X) = 0x%X\n", PAGE2_LAST_ERASE_DURATION1, Data));
            ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_NUM_SAVE_OPS_COUNT0, &Data, FALSE);
            ((OPERATIONAL_STATISTICS *)pDsmAcpiSmmData->OutputData)->NumberOfSaveOperationsCompleted.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE2_NUM_SAVE_OPS_COUNT0 (0x%X) = 0x%X\n", PAGE2_NUM_SAVE_OPS_COUNT0, Data));
            ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_NUM_SAVE_OPS_COUNT1, &Data, FALSE);
            ((OPERATIONAL_STATISTICS *)pDsmAcpiSmmData->OutputData)->NumberOfSaveOperationsCompleted.Byte1 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE2_NUM_SAVE_OPS_COUNT1 (0x%X) = 0x%X\n", PAGE2_NUM_SAVE_OPS_COUNT1, Data));
            ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_NUM_RESTORE_OPS_COUNT0, &Data, FALSE);
            ((OPERATIONAL_STATISTICS *)pDsmAcpiSmmData->OutputData)->NumberOfRestoreOperationsCompleted.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE2_NUM_RESTORE_OPS_COUNT0 (0x%X) = 0x%X\n", PAGE2_NUM_RESTORE_OPS_COUNT0, Data));
            ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_NUM_RESTORE_OPS_COUNT1, &Data, FALSE);
            ((OPERATIONAL_STATISTICS *)pDsmAcpiSmmData->OutputData)->NumberOfRestoreOperationsCompleted.Byte1 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE2_NUM_RESTORE_OPS_COUNT1 (0x%X) = 0x%X\n", PAGE2_NUM_RESTORE_OPS_COUNT1, Data));
            ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_NUM_ERASE_OPS_COUNT0, &Data, FALSE);
            ((OPERATIONAL_STATISTICS *)pDsmAcpiSmmData->OutputData)->NumberOfEraseOperationsCompleted.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE2_NUM_ERASE_OPS_COUNT0 (0x%X) = 0x%X\n", PAGE2_NUM_ERASE_OPS_COUNT0, Data));
            ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_NUM_ERASE_OPS_COUNT1, &Data, FALSE);
            ((OPERATIONAL_STATISTICS *)pDsmAcpiSmmData->OutputData)->NumberOfEraseOperationsCompleted.Byte1 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE2_NUM_ERASE_OPS_COUNT1 (0x%X) = 0x%X\n", PAGE2_NUM_ERASE_OPS_COUNT1, Data));
            ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_NUM_MODULE_POWER_CYCLES0, &Data, FALSE);
            ((OPERATIONAL_STATISTICS *)pDsmAcpiSmmData->OutputData)->NumberOfModulePowerCycles.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE2_NUM_MODULE_POWER_CYCLES0 (0x%X) = 0x%X\n", PAGE2_NUM_MODULE_POWER_CYCLES0, Data));
            ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_NUM_MODULE_POWER_CYCLES1, &Data, FALSE);
            ((OPERATIONAL_STATISTICS *)pDsmAcpiSmmData->OutputData)->NumberOfModulePowerCycles.Byte1 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE2_NUM_MODULE_POWER_CYCLES1 (0x%X) = 0x%X\n", PAGE2_NUM_MODULE_POWER_CYCLES1, Data));
            ((OPERATIONAL_STATISTICS *)pDsmAcpiSmmData->OutputData)->Status = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(OPERATIONAL_STATISTICS);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;

        // Get Vendor Log Page Size (Function Index 14)
        case 14:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Get Vendor Log Page Size (Function Index 14)\n"));
            ZeroMem(pDsmAcpiSmmData->OutputData, sizeof(VENDOR_LOG_PAGE_SIZE));  // Init OutputData to 0
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_VENDOR_LOG_PAGE_SIZE, &Data, FALSE);
            ((VENDOR_LOG_PAGE_SIZE *)pDsmAcpiSmmData->OutputData)->VendorLogPageSize = (UINT32)Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_VENDOR_LOG_PAGE_SIZE (0x%X) = 0x%X\n", PAGE0_VENDOR_LOG_PAGE_SIZE, Data));
            ((VENDOR_LOG_PAGE_SIZE *)pDsmAcpiSmmData->OutputData)->Status = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(VENDOR_LOG_PAGE_SIZE);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;

        // Get Vendor Log Page (Function Index 15)
        case 15:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Get Vendor Log Page (Function Index 15)\n"));
            ZeroMem(pDsmAcpiSmmData->OutputData, sizeof(VENDOR_LOG_PAGE));  // Init OutputData to 0
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_VENDOR_LOG_PAGE_SIZE, &Data, FALSE);    // Call Get Vendor Log Page Size (Function Index 14) to obtain.
            ((VENDOR_LOG_PAGE *)pDsmAcpiSmmData->OutputData)->VendorLogPage = (UINT32)Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_VENDOR_LOG_PAGE_SIZE (0x%X) = 0x%X\n", PAGE0_VENDOR_LOG_PAGE_SIZE, Data));
            ((VENDOR_LOG_PAGE *)pDsmAcpiSmmData->OutputData)->Status = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(VENDOR_LOG_PAGE);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;

        // Query Error Injection Status (Function Index 16)
        case 16:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Query Error Injection Status (Function Index 16)\n"));
            ZeroMem(pDsmAcpiSmmData->OutputData, sizeof(ERROR_INJECTION_STATUS));  // Init OutputData to 0
            ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_CAPABILITIES, &Data, FALSE);
            if (!(Data & BIT2)) gDsmErrorInjectionEnable = 0;   // Disable error injection if it's not supported
            ((ERROR_INJECTION_STATUS *)pDsmAcpiSmmData->OutputData)->ErrorInjectionEnabled = gDsmErrorInjectionEnable;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: ErrorInjectionEnabled = 0x%X\n", gDsmErrorInjectionEnable));
            ((ERROR_INJECTION_STATUS *)pDsmAcpiSmmData->OutputData)->Status = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(ERROR_INJECTION_STATUS);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;

        // Inject Error (Function Index 17)
        case 17:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Inject Error (Function Index 17)\n"));
            if(pDsmAcpiSmmData->InputDataSize != sizeof(INJECT_ERROR)) {
                DsmStatus = DSM_INVALID_INPUT_PARAMETERS;
            }
            else if (gDsmErrorInjectionEnable == 0) {
                DsmStatus = ((1 << 16) | DSM_FUNCTION_ERROR_CODE);   // 1: Error injection is disabled
            }
            else {
                Data = ((INJECT_ERROR *)pDsmAcpiSmmData->InputData)->InjectOperationFailures.Byte0;
                WriteNvdimm(Socket, Channel, Dimm, 2, PAGE2_INJECT_OPS_FAILURES, &Data, FALSE);
                //  If INJECT_BAD_BLOCKS is 1 (bit 7 of Byte 0), this is INJECT_BAD_BLOCK_CAP (2, 0x67). Otherwise, it shall be 0.
                if (Data & BIT7) {
                    Data = ((INJECT_ERROR *)pDsmAcpiSmmData->InputData)->InjectOperationFailures.Byte1;
                    WriteNvdimm(Socket, Channel, Dimm, 2, PAGE2_INJECT_BAD_BLOCK_CAP, &Data, FALSE);
                }
                Data = ((INJECT_ERROR *)pDsmAcpiSmmData->InputData)->InjectEnergySourceFailures;
                WriteNvdimm(Socket, Channel, Dimm, 2, PAGE2_INJECT_ES_FAILURES, &Data, FALSE);
                Data = ((INJECT_ERROR *)pDsmAcpiSmmData->InputData)->InjectFirmwareUpdateFailures;
                WriteNvdimm(Socket, Channel, Dimm, 2, PAGE2_INJECT_FW_FAILURES, &Data, FALSE);
            }
            ((UINT32 *)pDsmAcpiSmmData->OutputData)[0] = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(UINT32);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;

        // Get Injected Errors (Function Index 18)
        case 18:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Get Injected Errors (Function Index 18)\n"));
            ZeroMem(pDsmAcpiSmmData->OutputData, sizeof(INJECTED_ERRORS));  // Init OutputData to 0
            ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_INJECT_OPS_FAILURES, &Data, FALSE);
            ((INJECTED_ERRORS *)pDsmAcpiSmmData->OutputData)->OperationFailuresInjected.Byte0 = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE2_INJECT_OPS_FAILURES (0x%X) = 0x%X\n", PAGE2_INJECT_OPS_FAILURES, Data));
            // If INJECT_BAD_BLOCKS is '1' (bit 7 of Byte 0), this is *INJECT_BAD_BLOCK_CAP (2, 0x67). Otherwise, this shall be 0.
            if (Data & BIT7) {
                ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_INJECT_BAD_BLOCK_CAP, &Data, FALSE);
                ((INJECTED_ERRORS *)pDsmAcpiSmmData->OutputData)->OperationFailuresInjected.Byte1 = Data;
                DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE2_INJECT_BAD_BLOCK_CAP (0x%X) = 0x%X\n", PAGE2_INJECT_BAD_BLOCK_CAP, Data));
            }
            else {
                ((INJECTED_ERRORS *)pDsmAcpiSmmData->OutputData)->OperationFailuresInjected.Byte1 = 0;
            }
            ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_INJECT_ES_FAILURES, &Data, FALSE);
            ((INJECTED_ERRORS *)pDsmAcpiSmmData->OutputData)->EnergySourceFailuresInjected = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE2_INJECT_ES_FAILURES (0x%X) = 0x%X\n", PAGE2_INJECT_ES_FAILURES, Data));
            ReadNvdimm(Socket, Channel, Dimm, 2, PAGE2_INJECT_FW_FAILURES, &Data, FALSE);
            ((INJECTED_ERRORS *)pDsmAcpiSmmData->OutputData)->FirmwareUpdateFailuresInjected = Data;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE2_INJECT_FW_FAILURES (0x%X) = 0x%X\n", PAGE2_INJECT_FW_FAILURES, Data));
            ((INJECTED_ERRORS *)pDsmAcpiSmmData->OutputData)->Status = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(INJECTED_ERRORS);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;

        // Erase NVM Image (Function Index 19)
        case 19:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Erase NVM Image (Function Index 19)\n"));
            DsmStatus = EraseNvmImage(Socket, Channel, Dimm);
            ((UINT32 *)pDsmAcpiSmmData->OutputData)[0] = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(UINT32);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;

        // Arm NVDIMM-N (Function Index 20)
        case 20:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Arm NVDIMM-N (Function Index 20)\n"));
            DsmStatus = ArmNvdimm(Socket, Channel, Dimm);
            ((UINT32 *)pDsmAcpiSmmData->OutputData)[0] = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(UINT32);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;

        // Reset to Factory Defaults (Function Index 21)
        case 21:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Reset to Factory Defaults (Function Index 21)\n"));
            DsmStatus = ResetToFactoryDefaults(Socket, Channel, Dimm);
            ((UINT32 *)pDsmAcpiSmmData->OutputData)[0] = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(UINT32);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;

        //  Start Firmware Update (Function Index 22)
        case 22:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Start Firmware Update (Function Index 22)\n"));
            Data = ((START_FIRMWARE_UPDATE *)pDsmAcpiSmmData->InputData)->FirmwareSlot;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: FirmwareSlot = 0x%X\n", Data));
            DsmStatus = StartFirmwareUpdate(Socket, Channel, Dimm, Data);
            ((UINT32 *)pDsmAcpiSmmData->OutputData)[0] = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(UINT32);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;

        //  Send Firmware Update Data (Function Index 23)
        case 23:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Send Firmware Update Data (Function Index 23)\n"));
            DsmStatus = SendFirmwareUpdateData(Socket, Channel, Dimm);
            ((UINT32 *)pDsmAcpiSmmData->OutputData)[0] = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(UINT32);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;

        // Finish Firmware Update (Function Index 24)
        case 24:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Finish Firmware Update (Function Index 24)\n"));
            DsmStatus = FinishFirmwareUpdate(Socket, Channel, Dimm);
            ((UINT32 *)pDsmAcpiSmmData->OutputData)[0] = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(UINT32);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;

        // Select Firmware Image Slot (Function Index 25)
        case 25:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Select Firmware Image Slot (Function Index 25)\n"));
            Data = ((SELECT_FIRMWARE_IMAGE_SLOT *)pDsmAcpiSmmData->InputData)->FirmwareSlot;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: FirmwareSlot = 0x%X\n", Data));
            if (Data > 1) {
                DsmStatus = ((1 << 16) | DSM_FUNCTION_ERROR_CODE);   // 1: Invalid slot number.
            }
            else {
                WriteNvdimm(Socket, Channel, Dimm, 3, PAGE3_FW_SLOT_INFO, &Data, FALSE);
            }
            ((UINT32 *)pDsmAcpiSmmData->OutputData)[0] = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(UINT32);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;
        
        // Get Firmware Info (Function Index 26)
        case 26:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Get Firmware Info (Function Index 26)\n"));
            ZeroMem(pDsmAcpiSmmData->OutputData, sizeof(FIRMWARE_INFO));  // Init OutputData to 0
            Data = ((GET_FIRMWARE_IMAGE_SLOT *)pDsmAcpiSmmData->InputData)->FirmwareSlot;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: FirmwareSlot = 0x%X\n", Data));
            WriteNvdimm(Socket, Channel, Dimm, 3, PAGE3_FW_SLOT_INFO, &Data, FALSE);
            if (Data == 0) {
                ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_SLOT0_FWREV0, &Data, FALSE);
                ((FIRMWARE_INFO *)pDsmAcpiSmmData->OutputData)->Version.Byte0 = Data;
                DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_SLOT0_FWREV0 (0x%X) = 0x%X\n", PAGE0_SLOT0_FWREV0, Data));
                ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_SLOT0_FWREV1, &Data, FALSE);
                ((FIRMWARE_INFO *)pDsmAcpiSmmData->OutputData)->Version.Byte1 = Data;
                DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_SLOT0_FWREV1 (0x%X) = 0x%X\n", PAGE0_SLOT0_FWREV1, Data));
            }
            else {
                ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_SLOT1_FWREV0, &Data, FALSE);
                ((FIRMWARE_INFO *)pDsmAcpiSmmData->OutputData)->Version.Byte0 = Data;
                DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_SLOT1_FWREV0 (0x%X) = 0x%X\n", PAGE0_SLOT1_FWREV0, Data));
                ReadNvdimm(Socket, Channel, Dimm, 0, PAGE0_SLOT1_FWREV1, &Data, FALSE);
                ((FIRMWARE_INFO *)pDsmAcpiSmmData->OutputData)->Version.Byte1 = Data;
                DSM_DEBUG ((EFI_D_ERROR, "DSM: PAGE0_SLOT1_FWREV1 (0x%X) = 0x%X\n", PAGE0_SLOT1_FWREV1, Data));
            }
            ((FIRMWARE_INFO *)pDsmAcpiSmmData->OutputData)->Status = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(FIRMWARE_INFO);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;
        
        // I2C Read (Function Index 27)
        case 27:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: I2C Read (Function Index 27)\n"));
            ZeroMem(pDsmAcpiSmmData->OutputData, sizeof(I2C_READ_OUTPUT));  // Init OutputData to 0
            Page = ((I2C_READ_INPUT *)pDsmAcpiSmmData->InputData)->Page;
            Offset = ((I2C_READ_INPUT *)pDsmAcpiSmmData->InputData)->Offset;
            if (Page > 3) {
                DsmStatus = ((1 << 16) | DSM_FUNCTION_ERROR_CODE);   // 1: Invalid page.
            }
            else {
                ReadNvdimm(Socket, Channel, Dimm, Page, Offset, &Data, FALSE);
                ((I2C_READ_OUTPUT *)pDsmAcpiSmmData->OutputData)->Data = Data;
            }
            ((I2C_READ_OUTPUT *)pDsmAcpiSmmData->OutputData)->Status = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(I2C_READ_OUTPUT);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;
        
        // I2C Write (Function Index 28)
        case 28:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: I2C Write (Function Index 28)\n"));
            Page = ((I2C_WRITE *)pDsmAcpiSmmData->InputData)->Page;
            Offset = ((I2C_WRITE *)pDsmAcpiSmmData->InputData)->Offset;
            Data = ((I2C_WRITE *)pDsmAcpiSmmData->InputData)->Data;
            if (Page > 3) {
                DsmStatus = ((1 << 16) | DSM_FUNCTION_ERROR_CODE);   // 1: Invalid page.
            }
            else {
                WriteNvdimm(Socket, Channel, Dimm, Page, Offset, &Data, FALSE);
            }
            ((UINT32 *)pDsmAcpiSmmData->OutputData)[0] = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(UINT32);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;
        
        //  Read Typed Data (Function Index 29)
        case 29:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Read Typed Data (Function Index 29)\n"));
            ZeroMem(pDsmAcpiSmmData->OutputData, sizeof(READ_TYPED_DATA_OUTPUT));  // Init OutputData to 0
            Data = ((READ_TYPED_DATA_INPUT *)pDsmAcpiSmmData->InputData)->DataType;
            if ((Data == 1) || (Data == 2) || ((Data >= 201) && (Data <= 255))) {
                WriteNvdimm(Socket, Channel, Dimm, 3, PAGE3_TYPED_BLOCK_DATA, &Data, FALSE);
                Data = (((READ_TYPED_DATA_INPUT *)pDsmAcpiSmmData->InputData)->RegionId & 0xFF);
                WriteNvdimm(Socket, Channel, Dimm, 3, PAGE3_REGION_ID0, &Data, FALSE);
                Data = ((((READ_TYPED_DATA_INPUT *)pDsmAcpiSmmData->InputData)->RegionId >> 8) & 0xFF);
                WriteNvdimm(Socket, Channel, Dimm, 3, PAGE3_REGION_ID1, &Data, FALSE);
                Data = ((READ_TYPED_DATA_INPUT *)pDsmAcpiSmmData->InputData)->BlockId;
                WriteNvdimm(Socket, Channel, Dimm, 3, PAGE3_BLOCK_ID, &Data, FALSE);
                for (i = 0; i < READ_TYPED_DATA_LENGTH; i++) {
                    ReadNvdimm(Socket, Channel, Dimm, 3, PAGE3_TYPED_BLOCK_DATA_BYTE0 + i, &Data, FALSE);
                    ((READ_TYPED_DATA_OUTPUT *)pDsmAcpiSmmData->OutputData)->Data[i] = Data;
                }
            }
            else {
                DsmStatus = ((1 << 16) | DSM_FUNCTION_ERROR_CODE);   // 1: Invalid data type.
            }
            ((READ_TYPED_DATA_OUTPUT *)pDsmAcpiSmmData->OutputData)->Status = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(READ_TYPED_DATA_OUTPUT);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;
        
        // Write Typed Data (Function Index 30)
        case 30:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Write Typed Data (Function Index 30)\n"));
            Data = ((WRITE_TYPED_DATA *)pDsmAcpiSmmData->InputData)->DataType;
            if ((Data == 1) || (Data == 2) || ((Data >= 201) && (Data <= 255))) {
                WriteNvdimm(Socket, Channel, Dimm, 3, PAGE3_TYPED_BLOCK_DATA, &Data, FALSE);
                Data = (((WRITE_TYPED_DATA *)pDsmAcpiSmmData->InputData)->RegionId & 0xFF);
                WriteNvdimm(Socket, Channel, Dimm, 3, PAGE3_REGION_ID0, &Data, FALSE);
                Data = ((((WRITE_TYPED_DATA *)pDsmAcpiSmmData->InputData)->RegionId >> 8) & 0xFF);
                WriteNvdimm(Socket, Channel, Dimm, 3, PAGE3_REGION_ID1, &Data, FALSE);
                Data = ((WRITE_TYPED_DATA *)pDsmAcpiSmmData->InputData)->BlockId;
                WriteNvdimm(Socket, Channel, Dimm, 3, PAGE3_BLOCK_ID, &Data, FALSE);
                for (i = 0; i < READ_TYPED_DATA_LENGTH; i++) {
                    Data = ((WRITE_TYPED_DATA *)pDsmAcpiSmmData->InputData)->Data[i];
                    WriteNvdimm(Socket, Channel, Dimm, 3, PAGE3_TYPED_BLOCK_DATA_BYTE0 + i, &Data, FALSE);
                }
            }
            else {
                DsmStatus = ((1 << 16) | DSM_FUNCTION_ERROR_CODE);   // 1: Invalid data type.
            }
            ((UINT32 *)pDsmAcpiSmmData->OutputData)[0] = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(UINT32);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;
        
        //  Set Memory Error Counters (Function Index 31)
        case 31:
            DSM_DEBUG ((EFI_D_ERROR, "\nDSM: Set Memory Error Counters (Function Index 31)\n"));
            Data = ((SET_MEMORY_ERROR_COUNTERS *)pDsmAcpiSmmData->InputData)->CountOfDramUncorrectableEccErrors;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: CountOfDramUncorrectableEccErrors = 0x%X\n", Data));
            WriteNvdimm(Socket, Channel, Dimm, 2, PAGE2_DRAM_ECC_ERROR_COUNT, &Data, FALSE);
            Data = ((SET_MEMORY_ERROR_COUNTERS *)pDsmAcpiSmmData->InputData)->CountOfDramCorrectableEccErrorAboveThresholdEvents;
            DSM_DEBUG ((EFI_D_ERROR, "DSM: CountOfDramCorrectableEccErrorAboveThresholdEvents = 0x%X\n", Data));
            WriteNvdimm(Socket, Channel, Dimm, 2, PAGE2_DRAM_THRESHOLD_ECC_COUNT, &Data, FALSE);
            ((UINT32 *)pDsmAcpiSmmData->OutputData)[0] = DsmStatus;
            pDsmAcpiSmmData->OutputDataSize = sizeof(UINT32);
            DSM_DEBUG ((EFI_D_ERROR, "DSM: Status = 0x%d\n", DsmStatus));
            break;

        default:
            ((UINT32 *)pDsmAcpiSmmData->OutputData)[0] = DSM_NOT_SUPPORTED;
            pDsmAcpiSmmData->OutputDataSize = sizeof(UINT32);
            break;
      
    }
    
    return Status;
}

/**
    InstallDsmSmiHandler installs the SMI handler for DSM exectuion from OS

    @retval   EFI_SUCCESS

**/

EFI_STATUS
InstallDsmSmiHandler (
    )
{
    EFI_STATUS                      Status;
    EFI_SMM_BASE2_PROTOCOL          *SmmBase2;
    EFI_SMM_SYSTEM_TABLE2           *Smst2;
    EFI_HANDLE                      SwHandle = NULL;
    EFI_SMM_SW_DISPATCH2_PROTOCOL   *SwDispatch = NULL;
    EFI_SMM_SW_REGISTER_CONTEXT     SwContext;
    
    DEBUG ((EFI_D_ERROR, "InstallDsmSmiHandler Entry\n"));
    
    Status = gBS->LocateProtocol(&gEfiSmmBase2ProtocolGuid, NULL, &SmmBase2);
    if (EFI_ERROR(Status)) {
        return EFI_SUCCESS;
    }

    Status = SmmBase2->GetSmstLocation (SmmBase2, &Smst2);
    if (EFI_ERROR(Status)) {
        return EFI_SUCCESS;
    }

    Status = Smst2->SmmLocateProtocol(&gEfiSmmSwDispatch2ProtocolGuid,
                                      NULL,
                                      &SwDispatch);
    if (EFI_ERROR(Status)) {
        return EFI_SUCCESS;
    }
    
    //
    // Initialize platform specific settings
    //
    gDsmErrorInjectionEnable = 1;   // Enable error injection

    SwContext.SwSmiInputValue = 0xEB;
    Status = SwDispatch->Register (SwDispatch,
                                   ExecuteDsmCommand,
                                   &SwContext,
                                   &SwHandle);
    if (EFI_ERROR (Status)) {
        return Status;
    }
    
    DEBUG ((EFI_D_ERROR, "InstallDsmSmiHandler Exit\n"));
    
    return Status;
}


