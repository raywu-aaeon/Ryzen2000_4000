/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Library
 *
 * Contains interface to the AMD AGESA library
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Lib
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
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

/*****************************************************************************
 *
 * This software package can be used to enable the Overclocking of certain
 * AMD processors and its use is subject to the terms and conditions of the
 * AMD Overclocking Waiver. Enabling overclocking through use of the low-level
 * routines included in this package and operating an AMD processor outside of
 * the applicable AMD product specifications will void any AMD warranty and can
 * result in damage to the processor or the system into which the processor has
 * been integrated. The user of this software assumes, and AMD disclaims, all
 * risk, liability, costs and damages relating to or arising from the overclocking
 * of AMD processors.
 *
 ******************************************************************************
 */

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */

#include "Porting.h"
#include <Library/BaseLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/AmdSocBaseLib.h>
#include <Library/AmdPspBaseLibV2.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/AmdPspFlashUpdateLib.h>
#include <Addendum/Apcb/Inc/SSP/APOB.h>
#include <Library/AmdPspApobLib.h>
#include <Library/ApcbLibV3.h>
#include <Addendum/Apcb/Inc/SSP/APCB.h>
#include <Library/ApobCommonServiceLib.h>
#include <Protocol/SmmBase2.h>
#include <Protocol/SmmReadyToBoot.h>
#include <Library/MemRestore.h>
#include <Filecode.h>

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define FILECODE        LIBRARY_APCBLIBV3_APCBLIBV3_FILECODE

#define APCB_SIGNATURE  0x42435041ul

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */
typedef UINT64 (*GET_PCD_ADDRESS_TYPE) ();
typedef VOID (*SET_PCD_ADDRESS_TYPE) (UINT64 Address);

typedef struct {
  APCB_V3_HEADER          *Address;
  UINT32                  Size;
} APCB_ENTRY_INFO;

typedef struct {
  GET_PCD_ADDRESS_TYPE    GetPcd;
  SET_PCD_ADDRESS_TYPE    SetPcd;
} APCB_POST_TIME_SHADOW;

typedef struct {
  APCB_V3_HEADER          *Buffer;
  EFI_GUID                *ProtocolGuid;
} APCB_RUN_TIME_SHADOW;

typedef struct {
  UINT8                   BiosDirEntry;
  UINT8                   BinaryInstance;
  APCB_ENTRY_INFO         ApcbEntryInfo;
  APCB_POST_TIME_SHADOW   PostTimeShadow;
  APCB_RUN_TIME_SHADOW    RunTimeShadow;
} APCB_BINARY_INSTANCE_STORAGE;

typedef struct {
  UINT8                   Purpose;
  UINT8                   PriorityLevel;
} APCB_PURPOSE_TO_PRIORITY_LEVEL;

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
UINT64
GetApcb68ShadowAddress (
  );

UINT64
GetApcb60ConfigShadowAddress (
  );

UINT64
GetApcb60EvtLgShadowAddress (
  );

VOID
SetApcb68ShadowAddress (
  UINT64 Address
  );

VOID
SetApcb60ConfigShadowAddress (
  UINT64 Address
  );

VOID
SetApcb60EvtLgShadowAddress (
  UINT64 Address
  );

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
extern EFI_GUID gSmmApcb68RtShadowAddressProtocolGuid;
extern EFI_GUID gSmmApcb60RtShadowAddressProtocolGuid;
extern UINT8 CurrentPriorityLevel;
extern UINT8 CurrentBiosDirEntry;
extern UINT8 CurrentBinaryInstance;
extern UINT8 CurrentTypeInstance;

/*----------------------------------------------------------------------------------------
 *                          G L O B A L        V A L U E S
 *----------------------------------------------------------------------------------------
 */
BOOLEAN                 mInSmm                                = FALSE;
BOOLEAN                 mAtRuntime                            = FALSE;
BOOLEAN                 mApcbSmmMutexLocked                   = FALSE;
EFI_SMM_SYSTEM_TABLE2   *mSmst                                = NULL;

APCB_PURPOSE_TO_PRIORITY_LEVEL PurposeToPriorityMapping[] = {
  {APCB_TYPE_PURPOSE_HARD_FORCE,      APCB_PRIORITY_LEVEL_HARD_FORCE},
  {APCB_TYPE_PURPOSE_ADMIN,           APCB_PRIORITY_LEVEL_CUSTOM0},
  {APCB_TYPE_PURPOSE_DEBUG,           APCB_PRIORITY_LEVEL_CUSTOM1},
  {APCB_TYPE_PURPOSE_EVENT_LOGGING,   APCB_PRIORITY_LEVEL_EVENT_LOGGING},
  {APCB_TYPE_PURPOSE_NORMAL,          APCB_PRIORITY_LEVEL_CUSTOM2},
  {APCB_TYPE_PURPOSE_DEFAULT,         APCB_PRIORITY_LEVEL_DEFAULT}
};

PRIORITY_INSTANCE_MAPPING PriorityInstanceMapping[] = {
  {APCB_PRIORITY_LEVEL_HARD_FORCE,    BIOS_APCB_INFO_BACKUP,  APCB_BINARY_INSTANCE_HARD_FORCE,    APCB_TYPE_INSTANCE_HARD_FORCE},
  {APCB_PRIORITY_LEVEL_CUSTOM0,       BIOS_APCB_INFO,         APCB_BINARY_INSTANCE_BIOS_CONFIG,   APCB_TYPE_INSTANCE_ADMIN},
  {APCB_PRIORITY_LEVEL_CUSTOM1,       BIOS_APCB_INFO,         APCB_BINARY_INSTANCE_BIOS_CONFIG,   APCB_TYPE_INSTANCE_DEBUG},
  {APCB_PRIORITY_LEVEL_EVENT_LOGGING, BIOS_APCB_INFO,         APCB_BINARY_INSTANCE_EVENT_LOGGING, APCB_TYPE_INSTANCE_EVENT_LOGGING},
  {APCB_PRIORITY_LEVEL_CUSTOM2,       BIOS_APCB_INFO,         APCB_BINARY_INSTANCE_BIOS_CONFIG,   APCB_TYPE_INSTANCE_NORMAL},
  {APCB_PRIORITY_LEVEL_DEFAULT,       BIOS_APCB_INFO_BACKUP,  APCB_BINARY_INSTANCE_DEFAULT,       APCB_TYPE_INSTANCE_DEFAULT}
};

APCB_BINARY_INSTANCE_STORAGE ApcbBinaryInstanceStorage[] = {
  {
    BIOS_APCB_INFO_BACKUP,
    APCB_BINARY_INSTANCE_DEFAULT,
    {
      NULL,
      0
    },
    {
      GetApcb68ShadowAddress,
      SetApcb68ShadowAddress
    },
    {
      NULL,
      &gSmmApcb68RtShadowAddressProtocolGuid,
    }
  },
  {
    BIOS_APCB_INFO,
    APCB_BINARY_INSTANCE_BIOS_CONFIG,
    {
      NULL,
      0
    },
    {
      GetApcb60ConfigShadowAddress,
      SetApcb60ConfigShadowAddress
    },
    {
      NULL,
      &gSmmApcb60RtConfigShadowAddressProtocolGuid
    }
  },
  {
    BIOS_APCB_INFO,
    APCB_BINARY_INSTANCE_EVENT_LOGGING,
    {
      NULL,
      0
    },
    {
      GetApcb60EvtLgShadowAddress,
      SetApcb60EvtLgShadowAddress
    },
    {
      NULL,
      &gSmmApcb60RtEvtLgShadowAddressProtocolGuid
    }
  }
};

/*
 * Function to get the shadow copy address of APCB entry 0x68
*/
UINT64
GetApcb68ShadowAddress (
  )
{
  return PcdGet64 (PcdApcb68ShadowAddress);
}

/*
 * Function to get the shadow copy address of APCB entry 0x68
*/
UINT64
GetApcb60ConfigShadowAddress (
  )
{
  return PcdGet64 (PcdApcb60ConfigShadowAddress);
}

/*
 * Function to get the shadow copy address of APCB entry 0x68
*/
UINT64
GetApcb60EvtLgShadowAddress (
  )
{
  return PcdGet64 (PcdApcb60EvtLgShadowAddress);
}

/*
 * Function to set the shadow copy address of APCB entry 0x68
*/
VOID
SetApcb68ShadowAddress (
  UINT64 Address
  )
{
  PcdSet64 (PcdApcb68ShadowAddress, Address);
}

/*
 * Function to set the shadow copy address of APCB entry 0x68
*/
VOID
SetApcb60ConfigShadowAddress (
  UINT64 Address
  )
{
  PcdSet64 (PcdApcb60ConfigShadowAddress, Address);
}

/*
 * Function to set the shadow copy address of APCB entry 0x68
*/
VOID
SetApcb60EvtLgShadowAddress (
  UINT64 Address
  )
{
  PcdSet64 (PcdApcb60EvtLgShadowAddress, Address);
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function acquires mutex for the subsequent APCB operations
 *
 */
BOOLEAN
ApcbAcquireMutex (
  ) {
  EFI_STATUS                Status;
  EFI_SMM_BASE2_PROTOCOL    *SmmBase2;

  Status = gBS->LocateProtocol (&gEfiSmmBase2ProtocolGuid, NULL, (VOID**) &SmmBase2);
  if (!EFI_ERROR (Status)) {
    SmmBase2->InSmm (SmmBase2, &mInSmm);
  }

  if (!mInSmm) {
    if (!PcdGetBool (PcdApcbMutexLocked)) {
      PcdSetBool (PcdApcbMutexLocked, TRUE);
      IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] APCB DXE Mutex acquired successfully\n");
      return TRUE;
    } else {
      IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] Failed to acquire APCB DXE Mutex\n");
      ASSERT (FALSE);
      return FALSE;
    }
  } else {
    if (!mApcbSmmMutexLocked) {
      mApcbSmmMutexLocked = TRUE;
      IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] APCB SMM Mutex acquired successfully\n");
      return TRUE;
    } else {
      IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] Failed to acquire APCB SMM Mutex\n");
      ASSERT (FALSE);
      return FALSE;
    }
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function releases mutex for the subsequent APCB operations
 *
 */
VOID
ApcbReleaseMutex (
  ) {
  EFI_STATUS                Status;
  EFI_SMM_BASE2_PROTOCOL    *SmmBase2;

  Status = gBS->LocateProtocol (&gEfiSmmBase2ProtocolGuid, NULL, (VOID**) &SmmBase2);
  if (!EFI_ERROR (Status)) {
    SmmBase2->InSmm (SmmBase2, &mInSmm);
  }

  if (!mInSmm) {
    PcdSetBool (PcdApcbMutexLocked, FALSE);
    IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] APCB DXE Mutex released successfully\n");
  } else {
    mApcbSmmMutexLocked = FALSE;
    IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] APCB SMM Mutex released successfully\n");
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function set the target priority level for the subsequent APCB operations
 *
 * @param[in]         PriorityLevel        - APCB Priority Level
 *
 * @retval
 *
 */
VOID
ApcbSetPriorityLevel (
  IN       UINT8         PriorityLevel
  )
{
  UINT8   i;

  for (i = 0; i < sizeof (PriorityInstanceMapping) / sizeof (PRIORITY_INSTANCE_MAPPING); i ++) {
    if (PriorityLevel == PriorityInstanceMapping[i].PriorityLevel) {
      CurrentPriorityLevel  = PriorityLevel;
      CurrentBiosDirEntry   = PriorityInstanceMapping[i].BiosDirEntry;
      CurrentBinaryInstance = PriorityInstanceMapping[i].BinaryInstance;
      CurrentTypeInstance   = PriorityInstanceMapping[i].TypeInstance;
      IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] APCB Priority Level set to %d\n", CurrentPriorityLevel);
      IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] \t\tCurrentBiosDirEntry = 0x%x\n", CurrentBiosDirEntry);
      IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] \t\tCurrentBinaryInstance = 0x%x\n", CurrentBinaryInstance);
      IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] \t\tCurrentTypeInstance = 0x%x\n", CurrentTypeInstance);
      return;
    }
  }
  ASSERT (FALSE);
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function set the purpose for the subsequent APCB operations
 *
 * @param[in]         Purpose        - Purpose of APCB operations
 *
 * @retval
 *
 */
VOID
ApcbSetPurpose (
  IN       UINT8         Purpose
  )
{
  UINT8   i;

  ASSERT (Purpose > APCB_TYPE_PURPOSE_NONE && Purpose < APCB_TYPE_PURPOSE_LIMIT);

  for (i = 0; i < sizeof (PurposeToPriorityMapping) / sizeof (APCB_PURPOSE_TO_PRIORITY_LEVEL); i ++) {
    if (Purpose == PurposeToPriorityMapping[i].Purpose) {
      ApcbSetPriorityLevel (PurposeToPriorityMapping[i].PriorityLevel);
      return;
    }
  }
  ASSERT (FALSE);
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function set the purpose for the subsequent APCB operations
 *
 *
 * @retval  - Purpose
 *
 */
UINT8
ApcbGetPurpose (
  VOID
  )
{
  UINT8   i;

  for (i = 0; i < sizeof (PurposeToPriorityMapping) / sizeof (APCB_PURPOSE_TO_PRIORITY_LEVEL); i ++) {
    if (CurrentPriorityLevel == PurposeToPriorityMapping[i].PriorityLevel) {
      return PurposeToPriorityMapping[i].Purpose;
    }
  }
  ASSERT (FALSE);
  return APCB_TYPE_PURPOSE_NONE;
}

/*
 * Function to get ApcbShadowCopy Address, return NULL if fail
*/
VOID *
GetApcbShadowCopy (
  IN OUT  UINT32  *Size
  )
{
  VOID * ApcbData;
  UINT8 i;
  UINT8 j;

  ASSERT (Size != NULL);

  ApcbData = NULL;
  for (i = 0; i < sizeof (PriorityInstanceMapping) / sizeof (PRIORITY_INSTANCE_MAPPING); i ++) {
    if (CurrentPriorityLevel == PriorityInstanceMapping[i].PriorityLevel) {
      for (j = 0; j < sizeof (ApcbBinaryInstanceStorage) / sizeof (APCB_BINARY_INSTANCE_STORAGE); j ++) {
        if (PriorityInstanceMapping[i].BiosDirEntry == ApcbBinaryInstanceStorage[j].BiosDirEntry &&
            PriorityInstanceMapping[i].BinaryInstance == ApcbBinaryInstanceStorage[j].BinaryInstance) {
          if (mAtRuntime) {
            ApcbData = ApcbBinaryInstanceStorage[j].RunTimeShadow.Buffer;
          } else {
            ApcbData = (VOID *) (UINTN) ApcbBinaryInstanceStorage[j].PostTimeShadow.GetPcd ();
          }
          *Size = ApcbBinaryInstanceStorage[j].ApcbEntryInfo.Size;
          if (0 != *Size && NULL != ApcbData && APCB_SIGNATURE == (*(UINT32 *)ApcbData)) {
            IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] GetApcbShadowCopy for Entry 0x%x, Binary Instance %d, 0x%x:0x%x\n",
                                        ApcbBinaryInstanceStorage[j].BiosDirEntry,
                                        ApcbBinaryInstanceStorage[j].BinaryInstance,
                                        ApcbData,
                                        *Size);
            return ApcbData;
          } else {
            IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] APCB Shadow copy not found\n");
            return NULL;
          }
        }
      }
    }
  }
  IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] APCB Shadow copy not found\n");
  return NULL;
}

/*
 * Function to set ApcbShadowCopy Address
*/
VOID
SetApcbShadowCopy (
  IN      VOID * ApcbShadowAddress
  )
{
  UINT8 i;
  UINT8 j;

  IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] SetApcbShadowCopy %x\n", ApcbShadowAddress);

  ASSERT (NULL != ApcbShadowAddress);

  for (i = 0; i < sizeof (PriorityInstanceMapping) / sizeof (PRIORITY_INSTANCE_MAPPING); i ++) {
    if (CurrentPriorityLevel == PriorityInstanceMapping[i].PriorityLevel) {
      for (j = 0; j < sizeof (ApcbBinaryInstanceStorage) / sizeof (APCB_BINARY_INSTANCE_STORAGE); j ++) {
        if (PriorityInstanceMapping[i].BiosDirEntry == ApcbBinaryInstanceStorage[j].BiosDirEntry &&
            PriorityInstanceMapping[i].BinaryInstance == ApcbBinaryInstanceStorage[j].BinaryInstance) {
          if (mAtRuntime) {
            ApcbBinaryInstanceStorage[j].RunTimeShadow.Buffer = ApcbShadowAddress;
          } else {
            ApcbBinaryInstanceStorage[j].PostTimeShadow.SetPcd ((UINT64) (UINTN) ApcbShadowAddress);
          }
          return;
        }
      }
    }
  }
  ASSERT (FALSE);
}

/*
 * Function to calculate APCB checksum
*/
UINT8
ApcbCalcCheckSum (
  IN       VOID             *ApcbPtr,
  IN       UINT32           Length
  )
{
  UINT8  CheckSum;
  UINT8  *DataPtr;

  ASSERT (NULL != ApcbPtr);

  CheckSum = 0;
  DataPtr = ApcbPtr;
  while (Length --) {
    CheckSum += *(DataPtr ++);
  }
  return CheckSum;
}

/**
 *  Write APCB data to BIOS Directory APCB Entry 0x60
 *
 *
 *  @retval EFI_SUCCESS       The Data save to FLASH successfully
 *
 **/
EFI_STATUS
AmdPspWriteBackApcbShadowCopy (
  VOID
  )
{
  APCB_V3_HEADER                  *ApcbHeader;
  UINT8                           *ApcbData;
  EFI_STATUS                      Status;
  BOOLEAN                         ApcbRecoveryFlag;
  UINT8                           i;

  IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] AmdPspWriteBackApcbShadowCopy Enter\n");

  //
  // Exit service, if recovery flag set
  //
  if (mAtRuntime == FALSE) {
    Status = ApobGetApcbRecoveryFlag (&ApcbRecoveryFlag);
    if (ApcbRecoveryFlag) {
      IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] APCB.RecoveryFlag Set, exit service\n");
      return EFI_UNSUPPORTED;
    }
  }
  //
  // Exit service, if recovery flag set
  //
  if (CheckPspRecoveryFlagV2 () == TRUE) {
    IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] Recovery flag set, exit service\n");
    // ASSERT (FALSE); // Assertion in the debug build
    return EFI_UNSUPPORTED;
  }

  for (i = 0; i < sizeof (ApcbBinaryInstanceStorage) / sizeof (APCB_BINARY_INSTANCE_STORAGE); i ++) {
    if (BIOS_APCB_INFO_BACKUP == ApcbBinaryInstanceStorage[i].BiosDirEntry) {
      //
      // Do NOT write to the read-only entry (Entry 0x68)
      //
      continue;
    }
    if (mAtRuntime) {
      ApcbData = (VOID *)ApcbBinaryInstanceStorage[i].RunTimeShadow.Buffer;
    } else {
      ApcbData = (VOID *) (UINTN) ApcbBinaryInstanceStorage[i].PostTimeShadow.GetPcd ();
    }
    IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] Ready to write APCB shadow copy @ 0x%x back to : Entry 0x%x, Binary Instance %d\n",
                                ApcbData,
                                ApcbBinaryInstanceStorage[i].BiosDirEntry,
                                ApcbBinaryInstanceStorage[i].BinaryInstance
                              );
    ApcbHeader = (APCB_V3_HEADER *) ApcbData;
    if (NULL != ApcbHeader && 0 != ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Size) {
      if (ApcbHeader->SizeOfApcb > ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Size) {
        IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] APCB SPI Entry too small: 0x%x < 0x%x\n",
                                    ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Size,
                                    ApcbHeader->SizeOfApcb
                                  );
      }
      //
      // Compare if any changes
      //
      if (((ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Address)->CheckSumByte != ApcbHeader->CheckSumByte) ||
          ((ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Address)->SizeOfApcb != ApcbHeader->SizeOfApcb) ||
          (CompareMem (ApcbData, (VOID *) (UINTN) ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Address, ApcbHeader->SizeOfApcb))) {

        IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] Data different between APCB shadow & SPI copy at Entry %x, Binary Instance %d\n",
                                   ApcbBinaryInstanceStorage[i].BiosDirEntry,
                                   ApcbBinaryInstanceStorage[i].BinaryInstance
                                   );
        PspUpdateFlash ((UINT32) ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Address, ApcbHeader->SizeOfApcb, ApcbData);

        //
        // APCB Update should trigger memory re-training in the next boot
        //
        IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] Trigger memory re-training in the next boot\n");

        AmdMemRestoreDiscardCurrentMemContext ();
      } else {
        IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] No APCB data update for Entry %x, Binary Instance %d. Bypassing SPI write.\n",
                                   ApcbBinaryInstanceStorage[i].BiosDirEntry,
                                   ApcbBinaryInstanceStorage[i].BinaryInstance
                                  );
      }
    }
  }

  IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] AmdPspWriteBackApcbShadowCopy Exit\n");

  return EFI_SUCCESS;
}

/**
 *
 *  Init mApcbSmmRtShadowCopy
 *
 **/
EFI_STATUS
EFIAPI
ApcbRTBCallBack (
  IN CONST EFI_GUID                       *Protocol,
  IN VOID                                 *Interface,
  IN EFI_HANDLE                           Handle
  )
{
  UINT8         i;

  IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] ApcbRTBCallBack\n");
  for (i = 0; i < sizeof (ApcbBinaryInstanceStorage) / sizeof (APCB_BINARY_INSTANCE_STORAGE); i ++) {
    //
    //Check if mApcbSmmRtShadowCopy already initialized
    //Use APCB signature to do the simple check below
    //
    if (NULL != ApcbBinaryInstanceStorage[i].RunTimeShadow.Buffer &&
        0 != ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Size &&
        APCB_SIGNATURE != (ApcbBinaryInstanceStorage[i].RunTimeShadow.Buffer)->Signature
        ) {
      IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] Copy the Apcb from SPI %x to APCB RT copy %x, size = %x\n",
                                  ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Address,
                                  ApcbBinaryInstanceStorage[i].RunTimeShadow.Buffer,
                                  ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Size
                                );
      //Copy the Apcb from SPI to Shadow Copy
      CopyMem (ApcbBinaryInstanceStorage[i].RunTimeShadow.Buffer,
                (VOID *) (UINTN) ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Address,
                ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Size
              );
    }
  }
  mAtRuntime = TRUE;

  return EFI_SUCCESS;
}
/**
 *
 *  ApcbLibConstructor, initial the shadow copy of APCB data, and save the address to PCD
 *
 **/
EFI_STATUS
EFIAPI
ApcbLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  APCB_V3_HEADER            *ApcbShadowCopy;
  BOOLEAN                   ApcbEntryExist;
  TYPE_ATTRIB               TypeAttrib;
  UINT64                    EntryDest;
  EFI_SMM_BASE2_PROTOCOL    *SmmBase2;
  EFI_STATUS                Status;
  VOID                      *Registration;
  EFI_HANDLE                Handle;
  BOOLEAN                   ApcbRecoveryFlag;
  UINT8                     i;
  UINT8                     ApcbActiveInstance;

  IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] ApcbLibConstructor\n");
  ApcbActiveInstance    = 0;
  ApcbShadowCopy        = NULL;
  mInSmm                = FALSE;

  //
  // Exit if BR program
  //
  if (SocFamilyIdentificationCheck (F15_BR_RAW_ID)) {
    return EFI_SUCCESS;
  }
  //
  // Exit service, if recovery flag set
  //
  ApcbRecoveryFlag = FALSE;
  Status = ApobGetApcbRecoveryFlag (&ApcbRecoveryFlag);
  if (ApcbRecoveryFlag) {
    IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] APCB.RecoveryFlag Set, exit service\n");
    return EFI_SUCCESS;
  }

  //
  // Exit service, if recovery flag set
  //
  if (CheckPspRecoveryFlagV2 () == TRUE) {
    IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] Recovery flag set, exit service\n");
    // ASSERT (FALSE); // Assertion in the debug build
    return EFI_SUCCESS;
  }

  Status = gBS->LocateProtocol (&gEfiSmmBase2ProtocolGuid, NULL, (VOID**) &SmmBase2);
  if (!EFI_ERROR (Status)) {
    SmmBase2->InSmm (SmmBase2, &mInSmm);
  } else {
    IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] gEfiSmmBase2ProtocolGuid Locate Fail\n");
  }

  IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] %a\n", mInSmm ? "InSmm" : "OutSmm");

  //
  // Initialize the APCB purpose to priority mapping
  //
  for (i = 0; i < sizeof (PurposeToPriorityMapping) / sizeof (APCB_PURPOSE_TO_PRIORITY_LEVEL); i ++) {
    switch (PurposeToPriorityMapping[i].Purpose) {
    case APCB_TYPE_PURPOSE_ADMIN:
      PurposeToPriorityMapping[i].PriorityLevel = PcdGet8 (PcdAmdApcbPriorityLevelAdmin);
      break;
    case APCB_TYPE_PURPOSE_DEBUG:
      PurposeToPriorityMapping[i].PriorityLevel = PcdGet8 (PcdAmdApcbPriorityLevelDebug);
      break;
    case APCB_TYPE_PURPOSE_NORMAL:
      PurposeToPriorityMapping[i].PriorityLevel = PcdGet8 (PcdAmdApcbPriorityLevelNormal);
      break;
    default:
      break;
    }
  }

  for (i = 0; i < sizeof (ApcbBinaryInstanceStorage) / sizeof (APCB_BINARY_INSTANCE_STORAGE); i ++) {
    IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] Locating APCB binary Instance 0x%x in Entry 0x%x ...\n",
                                ApcbBinaryInstanceStorage[i].BinaryInstance,
                                ApcbBinaryInstanceStorage[i].BiosDirEntry
                              );
    ApcbEntryExist = BIOSEntryInfo (ApcbBinaryInstanceStorage[i].BiosDirEntry,
                                    ApcbBinaryInstanceStorage[i].BinaryInstance,
                                    &TypeAttrib,
                                    (VOID *)&ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Address,
                                    &ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Size,
                                    &EntryDest
                                    );
    //
    // Check if Posttime APCB shadow already initialized
    //
    ApcbShadowCopy = (APCB_V3_HEADER *) (UINTN) ApcbBinaryInstanceStorage[i].PostTimeShadow.GetPcd ();
    if (ApcbShadowCopy == NULL) {
      if (!ApcbEntryExist) {
        IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] APCB Instance 0x%x does not exist in Entry 0x%x\n",
                                    ApcbBinaryInstanceStorage[i].BinaryInstance,
                                    ApcbBinaryInstanceStorage[i].BiosDirEntry
                                  );
      } else {
        //
        // Shadow Copy haven't init yet
        //
        IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] Allocating PostTime APCB Shadow Copy with 0x%x bytes\n",
                                    ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Size
                                  );
        Status = gBS->AllocatePool (EfiBootServicesData,
                                    ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Size,
                                    (VOID **) &ApcbShadowCopy
                                  );
        ASSERT (ApcbShadowCopy != NULL);
        if (ApcbShadowCopy == NULL) {
          IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] Fail to allocate APCB Shadow Copy\n");
          return EFI_OUT_OF_RESOURCES;
        }
        IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] ALLOCATED[%x:%x]\n",
                                    ApcbShadowCopy,
                                    ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Size
                                  );

        ZeroMem (ApcbShadowCopy, ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Size);
        //
        // Copy the Apcb from SPI to Shadow Copy
        //
        CopyMem (ApcbShadowCopy,
                  (VOID *) (UINTN) ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Address,
                  ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Size
                );
        //
        // Calc the checksum, and report the warning
        //
        if (ApcbCalcCheckSum (ApcbShadowCopy, ApcbShadowCopy->SizeOfApcb) != 0) {
          IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] Warning: APCB Checksum not zero\n");
        }
        ApcbBinaryInstanceStorage[i].PostTimeShadow.SetPcd ((UINT64) (UINTN) ApcbShadowCopy);
      }
    }
  }

  if (!mInSmm) {
    return EFI_SUCCESS;
  }

  //
  // We are now in SMM
  // get SMM table base
  //
  Status = SmmBase2->GetSmstLocation (SmmBase2, &mSmst);
  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] GetSmstLocation Fail\n");
    return Status;
  }

  for (i = 0; i < sizeof (ApcbBinaryInstanceStorage) / sizeof (APCB_BINARY_INSTANCE_STORAGE); i ++) {
    //
    // Check if Post Time APCB shadow already initialized by locate SmmProtocol
    //
    Status = mSmst->SmmLocateProtocol (ApcbBinaryInstanceStorage[i].RunTimeShadow.ProtocolGuid,
                                        NULL,
                                        &ApcbShadowCopy
                                      );
    if (EFI_ERROR (Status) && 0 != ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Size) {
      IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] Allocate RT APCB Shadow Copy for Binary Instance 0x%x Entry 0x%x with 0x%x bytes\n",
                                  ApcbBinaryInstanceStorage[i].BinaryInstance,
                                  ApcbBinaryInstanceStorage[i].BiosDirEntry,
                                  ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Size
                                );
      //
      // Allocate APCB shadow for SMM RT
      //
      Status = mSmst->SmmAllocatePool (EfiRuntimeServicesData,
                                       ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Size,
                                       &ApcbShadowCopy
                                      );
      ASSERT (ApcbShadowCopy != NULL);
      if (ApcbShadowCopy == NULL) {
        IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] APCB Shadow Copy allocate fail\n");
        return Status;
      }
      IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] ALLOCATE[%x:%x]\n",
                                  ApcbShadowCopy,
                                  ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Size
                                );

      ZeroMem (ApcbShadowCopy, ApcbBinaryInstanceStorage[i].ApcbEntryInfo.Size);
      ApcbBinaryInstanceStorage[i].RunTimeShadow.Buffer = ApcbShadowCopy;
      Handle = NULL;
      Status = mSmst->SmmInstallProtocolInterface (
                        &Handle,
                        ApcbBinaryInstanceStorage[i].RunTimeShadow.ProtocolGuid,
                        EFI_NATIVE_INTERFACE,
                        &ApcbBinaryInstanceStorage[i].RunTimeShadow.Buffer
                        );
    }
  }
  //
  // Register SMM Exit boot service callback used init mApcbSmmRtShadowCopy
  //
  mSmst->SmmRegisterProtocolNotify (
           &gEdkiiSmmReadyToBootProtocolGuid,
           ApcbRTBCallBack,
           &Registration
           );

  return EFI_SUCCESS;
}

