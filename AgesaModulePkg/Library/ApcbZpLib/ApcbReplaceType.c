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
#include <Library/BaseLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/ApcbZpLib.h>
#include <Library/AmdSocBaseLib.h>
#include <Library/AmdPspBaseLibV2.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/ApobCommonServiceLib.h>
#include <Filecode.h>

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define FILECODE        LIBRARY_APCBZPLIB_APCBREPLACETYPE_FILECODE

#define APCB_SIGNATURE  0x42435041ul

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                          G L O B A L        V A L U E S
 *----------------------------------------------------------------------------------------
 */
extern UINT8                     mApcbInstance;
extern BOOLEAN                   mAtRuntime;
extern BOOLEAN                   mApcbRecoveryFlag;

UINT8
ApcbCalcCheckSum (
  IN       VOID             *ApcbPtr,
  IN       UINT32           Length
  );

/*
 * Function to update the APCB parameters of a given type
*/
EFI_STATUS
ApcbReplaceType (
  IN       UINT16          GroupId,
  IN       APCB_PARAM_TYPE ApcbParamType,
  IN       UINT16          InstanceId,
  IN       UINT8           *TypeDataStream,
  IN       UINT32          TypeDataSize,
  IN OUT   UINT8           *NewApcb
  )
{
  APCB_HEADER         *ApcbHeader;
  UINT8               *ApcbEnding;
  APCB_GROUP_HEADER   *ApcbGroupHeader;
  APCB_TYPE_HEADER    *ApcbTypeHeader;
  UINT32              OldTypeSize;
  UINT32              PreTypeDataSize;
  UINT8               *PostTypeData;
  UINT64              PostTypeDataSize;
  UINT8               *NewApcbPtr;
  UINT32              *NewSizeOfApcbPtr;
  UINT32              *NewSizeOfGroupPtr;
  UINT32              *NewSizeOfTypePtr;
  UINT32              NewTypeSize;
  UINT8               *OldApcb;
  AMD_CONFIG_PARAMS   StdHeader;

  ASSERT (0 != TypeDataSize);
  IDS_HDT_CONSOLE_PSP_TRACE ("ApcbReplaceType G:%x T:%x I:%x Data:&%x Size:%x NewApcb:%x\n",
                              GroupId, ApcbParamType, InstanceId, TypeDataStream, TypeDataSize, NewApcb);

  //Exit service, if recovery flag set
  if (mAtRuntime == FALSE) {
    if (mApcbRecoveryFlag) {
      IDS_HDT_CONSOLE_PSP_TRACE ("APCB.RecoveryFlag Set, exit service\n");
      return EFI_UNSUPPORTED;
    }
  }
  //Exit service, if recovery flag set
  if (CheckPspRecoveryFlagV2 () == TRUE) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Recovery flag set, exit service\n");
    // ASSERT (FALSE); // Assertion in the debug build
    return EFI_UNSUPPORTED;
  }

  NewTypeSize = TypeDataSize + ((ALIGN_SIZE_OF_TYPE - (TypeDataSize % ALIGN_SIZE_OF_TYPE)) & (ALIGN_SIZE_OF_TYPE - 1));
  OldApcb = GetApcbShadowCopy ();
  ApcbHeader = (APCB_HEADER *) (OldApcb);
  ASSERT (APCB_SIGNATURE == ApcbHeader->Signature);
  ApcbEnding = (UINT8 *) (OldApcb + ApcbHeader->SizeOfApcb - 1);
  ApcbGroupHeader = (APCB_GROUP_HEADER *) (VOID *) ((UINT8 *) ApcbHeader + sizeof (APCB_HEADER));
  ApcbTypeHeader = (APCB_TYPE_HEADER *) (VOID *) ((UINT8 *) ApcbGroupHeader + sizeof (APCB_GROUP_HEADER));
  IDS_HDT_CONSOLE_PSP_TRACE ("\n\t\tOriginal APCB Size: 0x%04X\n", ApcbHeader->SizeOfApcb);
  while ((((UINT8 *) ApcbGroupHeader + sizeof (APCB_GROUP_HEADER) - 1) <= ApcbEnding) &&
          ((UINT8 *) ((EFI_PHYSICAL_ADDRESS) ApcbTypeHeader + ApcbTypeHeader->SizeOfType - 1) <= ApcbEnding)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("\n\t\tCurrent Group: 0x%04X, Current Type: 0x%04X\n", ApcbGroupHeader->GroupId, ApcbTypeHeader->TypeId);
    if (ApcbGroupHeader->GroupId == GroupId) {
      if (ApcbTypeHeader->TypeId == ApcbParamType) {
        if (ApcbTypeHeader->InstanceId == InstanceId) {
          //
          // Found match!
          //
          IDS_HDT_CONSOLE_PSP_TRACE ("\n\t\tFound TypeId: %x,  Total TypeSize: %x\n", ApcbTypeHeader->TypeId, ApcbTypeHeader->SizeOfType);

          NewApcbPtr = NewApcb;
          OldTypeSize = ApcbTypeHeader->SizeOfType + ((ALIGN_SIZE_OF_TYPE - (ApcbTypeHeader->SizeOfType % ALIGN_SIZE_OF_TYPE)) & (ALIGN_SIZE_OF_TYPE - 1)) - sizeof (APCB_TYPE_HEADER);
          //
          // Copy the APCB data prior to the to-be-replaced type to the new APCB Buffer as-is
          //
          PreTypeDataSize = (UINT32) ((UINT8 *)ApcbTypeHeader - (UINT8 *)OldApcb + sizeof (APCB_TYPE_HEADER));
          LibAmdMemCopy (NewApcbPtr, OldApcb, PreTypeDataSize, &StdHeader);
          NewApcbPtr += PreTypeDataSize;

          //
          // Copy the to-be-replaced type to the new APCB Buffer as-is
          //
          LibAmdMemCopy (NewApcbPtr, TypeDataStream, NewTypeSize, &StdHeader);
          NewApcbPtr += NewTypeSize;

          //
          // Adjust size in the headers
          //
          NewSizeOfApcbPtr = &(((APCB_HEADER *)NewApcb)->SizeOfApcb);
          NewSizeOfGroupPtr = (UINT32 *) ((UINTN)&ApcbGroupHeader->SizeOfGroup + (UINTN)NewApcb - (UINTN)OldApcb);
          NewSizeOfTypePtr = (UINT32 *) ((UINTN)&ApcbTypeHeader->SizeOfType + (UINTN)NewApcb - (UINTN)OldApcb);
          if (NewTypeSize >= OldTypeSize) {
            *NewSizeOfApcbPtr += (NewTypeSize - OldTypeSize);
            *NewSizeOfGroupPtr += (NewTypeSize - OldTypeSize);
            *NewSizeOfTypePtr += (NewTypeSize - OldTypeSize);
          } else {
            *NewSizeOfApcbPtr -= (OldTypeSize - NewTypeSize);
            *NewSizeOfGroupPtr -= (OldTypeSize - NewTypeSize);
            *NewSizeOfTypePtr -= (OldTypeSize - NewTypeSize);
          }
          IDS_HDT_CONSOLE_PSP_TRACE ("\n\t\tSize of APCB updated to: 0x%04X\n", *NewSizeOfApcbPtr);
          IDS_HDT_CONSOLE_PSP_TRACE ("\n\t\tSize of Group updated to: 0x%04X\n", *NewSizeOfGroupPtr);
          IDS_HDT_CONSOLE_PSP_TRACE ("\n\t\tSize of Type updated to: 0x%04X\n", *NewSizeOfTypePtr);

          //
          // Copy the APCB data after the to-be-replaced type to the new APCB Buffer as-is
          //
          PostTypeData = (UINT8 *)ApcbTypeHeader + sizeof (APCB_TYPE_HEADER) + OldTypeSize;
          // Check If reach the last type
          if (PostTypeData < ApcbEnding) {
            PostTypeDataSize = ApcbEnding - PostTypeData + 1;
            LibAmdMemCopy (NewApcbPtr, PostTypeData, PostTypeDataSize, &StdHeader);
          }
          //Calc the checksum
          IDS_HDT_CONSOLE_PSP_TRACE ("Calc the checksum\n");
          ((APCB_HEADER *) NewApcb)->CheckSumByte = 0;
          ((APCB_HEADER *) NewApcb)->CheckSumByte = (UINT8) (0x100 - ApcbCalcCheckSum (NewApcb, ((APCB_HEADER *) NewApcb)->SizeOfApcb));
          //Point the shadow copy to new version, and free old version
          FreePool (OldApcb);
          IDS_HDT_CONSOLE_PSP_TRACE ("FREE[%x]\n", OldApcb);

          //Update Shadow Copy public data
          IDS_HDT_CONSOLE_PSP_TRACE ("Update PSP ApcbShadowCopy from %x to %x\n", OldApcb, NewApcb);
          SetApcbShadowCopy (NewApcb);

          return EFI_SUCCESS;
        }
      } else {
        ApcbTypeHeader = (APCB_TYPE_HEADER *) ((EFI_PHYSICAL_ADDRESS) ApcbTypeHeader + ApcbTypeHeader->SizeOfType);
        // Adjust alignment
        ApcbTypeHeader = (APCB_TYPE_HEADER *) ((UINT8 *) ApcbTypeHeader + ((ALIGN_SIZE_OF_TYPE - ((EFI_PHYSICAL_ADDRESS) ApcbTypeHeader) % ALIGN_SIZE_OF_TYPE) & (ALIGN_SIZE_OF_TYPE - 1)));
        if ((UINT8 *) ApcbTypeHeader > (UINT8 *) ((EFI_PHYSICAL_ADDRESS) ApcbGroupHeader + ApcbGroupHeader->SizeOfGroup - 1)) {
          return EFI_NOT_FOUND;
        }
      }
    } else {
      ApcbGroupHeader = (APCB_GROUP_HEADER *) ((EFI_PHYSICAL_ADDRESS) ApcbGroupHeader + ApcbGroupHeader->SizeOfGroup);
      //
      // APCB Type header following APCP Group header should already be 4-bytes aligned, there's no need for
      // extra adjustment on ApcbTypeHeader pointer.
      //
      ApcbTypeHeader = (APCB_TYPE_HEADER *) (VOID *) (ApcbGroupHeader + 1);
    }
  }
  IDS_HDT_CONSOLE_PSP_TRACE ("\n\t\tNo matching type found in APCB.\n");

  return EFI_NOT_FOUND;
}

