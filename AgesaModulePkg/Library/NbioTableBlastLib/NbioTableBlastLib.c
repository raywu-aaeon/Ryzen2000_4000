/* $NoKeywords:$ */
/**
 * @file
 *
 * Service procedure to access PCI config space registers
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
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
*
*/

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include <Library/BaseLib.h>
#include <AGESA.h>
#include <Library/IdsLib.h>
#include <Library/AmdBaseLib.h>
#include <Gnb.h>
#include <Library/GnbPcieConfigLib.h>
#include <Library/GnbLib.h>
#include <Library/NbioTableBlastLib.h>
#include <Library/SmnAccessLib.h>
#include <Library/PcdLib.h>
#include <Library/PcieConfigLib.h>
#include <GnbRegistersSSP.h>
#include <Filecode.h>

#define FILECODE LIBRARY_NBIOTABLEBLASTLIB_NBIOTABLEBLASTLIB_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------*/
/**
 * Supporting function for register read modify write in NBIO space
 *
 * @param[in] GnbHandle                 Gnb handle
 * @param[in] Data                      Data pointer
 * @param[in] Flags                     Flags
 */

VOID
STATIC
GnbProcessTableRegisterRmwNbioSpace (
  IN      GNB_HANDLE                     *GnbHandle,
  IN      GNB_RMW_BLOCK                  *Data,
  IN      UINT32                         Flags
  )
{
  UINT64  Value;
  Value = 0;
  SmnRegisterRead (
    GnbHandle->Address.Address.Bus,
    NBIO_SPACE(GnbHandle, Data->Address),
    &Value
    );
  Value = (Value & (~ (UINT64) Data->AndMask)) | Data->OrMask;
  SmnRegisterWrite (
    GnbHandle->Address.Address.Bus,
    NBIO_SPACE(GnbHandle, Data->Address),
    &Value,
    Flags
    );
}

/*----------------------------------------------------------------------------------------*/
/**
 * Supporting function for register read modify write in wrapper space
 *
 * @param[in] GnbHandle                 Gnb handle
 * @param[in] Wrapper                   Pcie wrapper
 * @param[in] Data                      Data pointer
 * @param[in] Flags                     Flags
 */

VOID
STATIC
GnbProcessTableRegisterRmwWrapperSpace (
  IN      GNB_HANDLE                     *GnbHandle,
  IN      PCIe_WRAPPER_CONFIG            *Wrapper,
  IN      GNB_RMW_BLOCK                  *Data,
  IN      UINT32                         Flags
  )
{
  UINT64  Value;
  Value = 0;
  SmnRegisterRead (
    GnbHandle->Address.Address.Bus,
    WRAP_SPACE(GnbHandle, Wrapper, Data->Address),
    &Value
    );
  Value = (Value & (~ (UINT64) Data->AndMask)) | Data->OrMask;
  SmnRegisterWrite (
    GnbHandle->Address.Address.Bus,
    WRAP_SPACE(GnbHandle, Wrapper, Data->Address),
    &Value,
    Flags
    );
}

/*----------------------------------------------------------------------------------------*/
/**
 * Supporting function for register read modify write in pcie port space
 *
 * @param[in] GnbHandle                 Gnb handle
 * @param[in] Wrapper                   Pcie wrapper
 * @param[in] PcieEngine                Pcie port
 * @param[in] Data                      Data pointer
 * @param[in] Flags                     Flags
 */

VOID
STATIC
GnbProcessTableRegisterRmwPortSpace (
  IN      GNB_HANDLE                     *GnbHandle,
  IN      PCIe_WRAPPER_CONFIG            *Wrapper,
  IN      PCIe_ENGINE_CONFIG             *PcieEngine,
  IN      GNB_RMW_BLOCK                  *Data,
  IN      UINT32                         Flags
  )
{
  UINT64  Value;
  Value = 0;
  SmnRegisterRead (
    GnbHandle->Address.Address.Bus,
    PORT_SPACE(GnbHandle, Wrapper, PcieEngine->Type.Port.PortId % 8, Data->Address),
    &Value
    );
  Value = (Value & (~ (UINT64) Data->AndMask)) | Data->OrMask;
  SmnRegisterWrite (
    GnbHandle->Address.Address.Bus,
    PORT_SPACE(GnbHandle, Wrapper, PcieEngine->Type.Port.PortId % 8, Data->Address),
    &Value,
    Flags
    );
}

/*----------------------------------------------------------------------------------------*/
/**
 * Determine what type of PCD is associated with a token, and then retrieve that value
 *
 * @param[in] Token    PCD Token Value
 *
 * @retval             The PCD value
 *
 */
UINT32
DeterminePcdValue (
  UINT32      Token
  )
{
  PCD_INFO                         PcdInfoData;

  LibPcdGetInfo(Token, &PcdInfoData);

  IDS_HDT_CONSOLE(NB_MISC, "%a : Getting PCD value of %s\n", __FUNCTION__, PcdInfoData.PcdName);

  switch (PcdInfoData.PcdType) {
  case PCD_TYPE_8:
    return LibPcdGet8(Token);
  case PCD_TYPE_16:
    return LibPcdGet16(Token);
  case PCD_TYPE_32:
    return LibPcdGet32(Token);
  case PCD_TYPE_BOOL:
    return LibPcdGetBool(Token);
  default:
    IDS_HDT_CONSOLE (NB_MISC, "%a : PCD Type not supported\n", __FUNCTION__);
    ASSERT(FALSE);
    return 0;
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Take care of all NBIO_TYPE entries.
 *
 * @param[in] EntryPointer    Pointer to beginning byte of entry
 * @param[in] GnbHandle       Gnb handle
 * @param[in] Table           Table pointer
 * @param[in] Property        Property
 */
UINTN
NbioTypeHandler(
 IN  UINT8       *EntryPointer,
 IN  GNB_HANDLE  *GnbHandle,
 IN  UINT32      WriteAccFlags,
 IN  UINT32      Property

  )
{
  UINTN                            EntrySize;
  GNB_TABLE_ENTRY_PCD_RMW          *PcdRmwEntry;
  GNB_TABLE_ENTRY_PCD_WR           *PcdWrEntry;
  BOOLEAN                          BlastedEntry;

  EntrySize = 0;
  BlastedEntry = FALSE;

  switch (*EntryPointer) {
  case GnbEntryWr:
    SmnRegisterWrite (
      GnbHandle->Address.Address.Bus,
      NBIO_SPACE(GnbHandle, ((GNB_TABLE_ENTRY_WR*) EntryPointer)->Address),
      &((GNB_TABLE_ENTRY_WR*) EntryPointer)->Value,
      WriteAccFlags
      );
    EntrySize = sizeof (GNB_TABLE_ENTRY_WR);
    break;
  case GnbEntryRmw:
    GnbProcessTableRegisterRmwNbioSpace (
      GnbHandle,
      &((GNB_TABLE_ENTRY_RMW *) EntryPointer)->Data,
      WriteAccFlags
      );
    EntrySize = sizeof (GNB_TABLE_ENTRY_RMW);
    break;
  case GnbEntryPcdWr:
    PcdWrEntry = (GNB_TABLE_ENTRY_PCD_WR *)EntryPointer;
    IDS_HDT_CONSOLE(NB_MISC, "  Read GNB_ENTRY_PCD_WR. Token value %x , PCD Operation Type %d\n", PcdWrEntry->Token, PcdWrEntry->PcdType);
    if ((PcdWrEntry->PcdType == TableBlastWriteIfValEqual) && (DeterminePcdValue(PcdWrEntry->Token) == PcdWrEntry->CompareValue)) {
      SmnRegisterWrite (
        GnbHandle->Address.Address.Bus,
        NBIO_SPACE(GnbHandle, (PcdWrEntry->Address)),
        &(PcdWrEntry->Value),
        WriteAccFlags
        );
      BlastedEntry = TRUE;
    }
    if ((PcdWrEntry->PcdType == TableBlastWriteIfValNotEqual) && (DeterminePcdValue(PcdWrEntry->Token) != PcdWrEntry->CompareValue)) {
      SmnRegisterWrite (
        GnbHandle->Address.Address.Bus,
        NBIO_SPACE(GnbHandle, (PcdWrEntry->Address)),
        &(PcdWrEntry->Value),
        WriteAccFlags
        );
      BlastedEntry = TRUE;
    }
    if ((PcdWrEntry->PcdType == TableBlastWriteValue)) {
      PcdWrEntry->Value = DeterminePcdValue(PcdWrEntry->Token);
      SmnRegisterWrite (
        GnbHandle->Address.Address.Bus,
        NBIO_SPACE(GnbHandle, (PcdWrEntry->Address)),
        &(PcdWrEntry->Value),
        WriteAccFlags
        );
      BlastedEntry = TRUE;
    }
    if (BlastedEntry) {
      IDS_HDT_CONSOLE (NB_MISC, "Blasted PCD WR entry.\n");
    }
    EntrySize = sizeof(GNB_TABLE_ENTRY_PCD_WR);
    break;
  case GnbEntryPcdRmw:
    PcdRmwEntry = (GNB_TABLE_ENTRY_PCD_RMW *)EntryPointer;
    IDS_HDT_CONSOLE(NB_MISC, "  Read GNB_ENTRY_PCD_RMW. Token value %x , PCD Operation Type %d\n", PcdRmwEntry->Token, PcdRmwEntry->PcdType);
    if ((PcdRmwEntry->PcdType == TableBlastWriteIfValEqual) && (DeterminePcdValue(PcdRmwEntry->Token) == PcdRmwEntry->CompareValue)) {
      GnbProcessTableRegisterRmwNbioSpace (
        GnbHandle,
        &(PcdRmwEntry->Data),
        WriteAccFlags
        );
      BlastedEntry = TRUE;
    }
    if ((PcdRmwEntry->PcdType == TableBlastWriteIfValNotEqual) && (DeterminePcdValue(PcdRmwEntry->Token) != PcdRmwEntry->CompareValue)) {
      GnbProcessTableRegisterRmwNbioSpace (
        GnbHandle,
        &(PcdRmwEntry->Data),
        WriteAccFlags
        );
      BlastedEntry = TRUE;
    }
    if (BlastedEntry) {
      IDS_HDT_CONSOLE (NB_MISC, "Blasted PCD RMW entry.\n");
    }
    /// Check for an invalid PCD RMW Instruction(s) to prevent
    /// developer mistakes
    ASSERT(PcdRmwEntry->PcdType != TableBlastWriteValue);
    EntrySize = sizeof(GNB_TABLE_ENTRY_PCD_RMW);
    break;
  case GnbEntryPropertyRmw:
    if ((Property & ((GNB_TABLE_ENTRY_PROPERTY_RMW *) EntryPointer)->Property) != 0) {
      GnbProcessTableRegisterRmwNbioSpace (
        GnbHandle,
        &((GNB_TABLE_ENTRY_PROPERTY_RMW *) EntryPointer)->Data,
        WriteAccFlags
        );
    }
    EntrySize = sizeof (GNB_TABLE_ENTRY_PROPERTY_RMW);
    break;
  default:
    IDS_HDT_CONSOLE (NB_MISC, "  ERROR!!! Register table parse\n");
    ASSERT (FALSE);
    return 0;
  }

  return EntrySize;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Take care of all ALL_WRAP_TYPE entries.
 *
 * @param[in] EntryPointer    Pointer to beginning byte of entry
 * @param[in] GnbHandle       Gnb handle
 * @param[in] Table           Table pointer
 * @param[in] Property        Property
 */
UINTN
WrapperTypeHandler(
 IN  UINT8       *EntryPointer,
 IN  GNB_HANDLE  *GnbHandle,
 IN  UINT32      WriteAccFlags,
 IN  UINT32      Property

  )
{
  UINTN                            EntrySize;
  PCIe_WRAPPER_CONFIG              *PcieWrapper;
  GNB_TABLE_ENTRY_PCD_RMW          *PcdRmwEntry;
  GNB_TABLE_ENTRY_PCD_WR           *PcdWrEntry;
  BOOLEAN                          BlastedEntry;

  EntrySize = 0;
  BlastedEntry = FALSE;
  PcieWrapper = PcieConfigGetChildWrapper (GnbHandle);
  //
  // Perform this action to all enabled pcie wrappers
  //
  while ((PcieWrapper != NULL) && (PcieWrapper->WrapId < 2)) {
    switch (*EntryPointer) {
    case GnbEntryWr:
      SmnRegisterWrite (
        GnbHandle->Address.Address.Bus,
        WRAP_SPACE(GnbHandle, PcieWrapper, ((GNB_TABLE_ENTRY_WR*) EntryPointer)->Address),
        &((GNB_TABLE_ENTRY_WR*) EntryPointer)->Value,
        WriteAccFlags
        );
      EntrySize = sizeof (GNB_TABLE_ENTRY_WR);
      break;
    case GnbEntryRmw:
      GnbProcessTableRegisterRmwWrapperSpace (
        GnbHandle,
        PcieWrapper,
        &((GNB_TABLE_ENTRY_RMW *) EntryPointer)->Data,
        WriteAccFlags
        );
      EntrySize = sizeof (GNB_TABLE_ENTRY_RMW);
      break;
    case GnbEntryPcdWr:
      PcdWrEntry = (GNB_TABLE_ENTRY_PCD_WR *)EntryPointer;
      IDS_HDT_CONSOLE(NB_MISC, "  Read GNB_ENTRY_PCD_WR. Token value %x , PCD Operation Type %d\n", PcdWrEntry->Token, PcdWrEntry->PcdType);
      if ((PcdWrEntry->PcdType == TableBlastWriteIfValEqual) && (DeterminePcdValue(PcdWrEntry->Token) == PcdWrEntry->CompareValue)) {
        SmnRegisterWrite (
          GnbHandle->Address.Address.Bus,
          WRAP_SPACE(GnbHandle, PcieWrapper, (PcdWrEntry->Address)),
          &(PcdWrEntry->Value),
          WriteAccFlags
          );
        BlastedEntry = TRUE;
      }
      if ((PcdWrEntry->PcdType == TableBlastWriteIfValNotEqual) && (DeterminePcdValue(PcdWrEntry->Token) != PcdWrEntry->CompareValue)) {
        SmnRegisterWrite (
          GnbHandle->Address.Address.Bus,
          WRAP_SPACE(GnbHandle, PcieWrapper, (PcdWrEntry->Address)),
          &(PcdWrEntry->Value),
          WriteAccFlags
          );
        BlastedEntry = TRUE;
      }
      if ((PcdWrEntry->PcdType == TableBlastWriteValue)) {
        PcdWrEntry->Value = DeterminePcdValue(PcdWrEntry->Token);
        SmnRegisterWrite (
          GnbHandle->Address.Address.Bus,
          WRAP_SPACE(GnbHandle, PcieWrapper, (PcdWrEntry->Address)),
          &(PcdWrEntry->Value),
          WriteAccFlags
          );
        BlastedEntry = TRUE;
      }
      if (BlastedEntry) {
        IDS_HDT_CONSOLE (NB_MISC, "Blasted PCD WR entry.\n");
      }
      EntrySize = sizeof(GNB_TABLE_ENTRY_PCD_WR);
      break;
    case GnbEntryPcdRmw:
      PcdRmwEntry = (GNB_TABLE_ENTRY_PCD_RMW *)EntryPointer;
      IDS_HDT_CONSOLE(NB_MISC, "  Read GNB_ENTRY_PCD_RMW. Token value %x , PCD Operation Type %d\n", PcdRmwEntry->Token, PcdRmwEntry->PcdType);
      if ((PcdRmwEntry->PcdType == TableBlastWriteIfValEqual) && (DeterminePcdValue(PcdRmwEntry->Token) == PcdRmwEntry->CompareValue)) {
        GnbProcessTableRegisterRmwWrapperSpace (
          GnbHandle,
          PcieWrapper,
          &(PcdRmwEntry->Data),
          WriteAccFlags
          );
        BlastedEntry = TRUE;
      }
      if ((PcdRmwEntry->PcdType == TableBlastWriteIfValNotEqual) && (DeterminePcdValue(PcdRmwEntry->Token) != PcdRmwEntry->CompareValue)) {
        GnbProcessTableRegisterRmwWrapperSpace (
          GnbHandle,
          PcieWrapper,
          &(PcdRmwEntry->Data),
          WriteAccFlags
          );
        BlastedEntry = TRUE;
      }
      if (BlastedEntry) {
        IDS_HDT_CONSOLE (NB_MISC, "Blasted PCD RMW entry.\n");
      }
      /// Check for an invalid PCD RMW Instruction(s) to prevent
      /// developer mistakes.
      ASSERT(PcdRmwEntry->PcdType != TableBlastWriteValue);
      EntrySize = sizeof(GNB_TABLE_ENTRY_PCD_RMW);
      break;
    case GnbEntryPropertyRmw:
      if ((Property & ((GNB_TABLE_ENTRY_PROPERTY_RMW *) EntryPointer)->Property) != 0) {
        GnbProcessTableRegisterRmwWrapperSpace (
          GnbHandle,
          PcieWrapper,
          &((GNB_TABLE_ENTRY_PROPERTY_RMW *) EntryPointer)->Data,
          WriteAccFlags
          );
      }
      EntrySize = sizeof (GNB_TABLE_ENTRY_PROPERTY_RMW);
      break;
    default:
      IDS_HDT_CONSOLE (NB_MISC, "  ERROR!!! Register table parse\n");
      ASSERT (FALSE);
      return 0;
    }
    PcieWrapper = PcieLibGetNextDescriptor (PcieWrapper);
  }

  return EntrySize;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Take care of all ALL_PORT_TYPE entries.
 *
 * @param[in] EntryPointer    Pointer to beginning byte of entry
 * @param[in] GnbHandle       Gnb handle
 * @param[in] Table           Table pointer
 * @param[in] Property        Property
 */
UINTN
PortTypeHandler(
 IN  UINT8       *EntryPointer,
 IN  GNB_HANDLE  *GnbHandle,
 IN  UINT32      WriteAccFlags,
 IN  UINT32      Property

  )
{
  UINTN                            EntrySize;
  PCIe_WRAPPER_CONFIG              *PcieWrapper;
  PCIe_ENGINE_CONFIG               *PcieEngine;
  GNB_TABLE_ENTRY_PCD_RMW          *PcdRmwEntry;
  GNB_TABLE_ENTRY_PCD_WR           *PcdWrEntry;
  BOOLEAN                          BlastedEntry;

  EntrySize = 0;
  BlastedEntry = FALSE;
  PcieWrapper = PcieConfigGetChildWrapper (GnbHandle);
  //
  // Perform this action to all enabled pcie wrappers
  //
  while (PcieWrapper != NULL) {
    PcieEngine = PcieConfigGetChildEngine (PcieWrapper);
    while (PcieEngine != NULL) {
      if (PcieLibIsEngineAllocated (PcieEngine)) {
        switch (*EntryPointer) {
        case GnbEntryWr:
          SmnRegisterWrite (
            GnbHandle->Address.Address.Bus,
            PORT_SPACE(GnbHandle, PcieWrapper, PcieEngine->Type.Port.PortId % 8, ((GNB_TABLE_ENTRY_WR*) EntryPointer)->Address),
            &((GNB_TABLE_ENTRY_WR*) EntryPointer)->Value,
            WriteAccFlags
            );
          EntrySize = sizeof (GNB_TABLE_ENTRY_WR);
          break;
        case GnbEntryRmw:
          GnbProcessTableRegisterRmwPortSpace (
            GnbHandle,
            PcieWrapper,
            PcieEngine,
            &((GNB_TABLE_ENTRY_RMW *) EntryPointer)->Data,
            WriteAccFlags
            );
          EntrySize = sizeof (GNB_TABLE_ENTRY_RMW);
          break;
        case GnbEntryPcdWr:
          PcdWrEntry = (GNB_TABLE_ENTRY_PCD_WR *)EntryPointer;
          IDS_HDT_CONSOLE(NB_MISC, "  Read GNB_ENTRY_PCD_WR. Token value %x , PCD Operation Type %d\n", PcdWrEntry->Token, PcdWrEntry->PcdType);
          if ((PcdWrEntry->PcdType == TableBlastWriteIfValEqual) && (DeterminePcdValue(PcdWrEntry->Token) == PcdWrEntry->CompareValue)) {
            SmnRegisterWrite (
              GnbHandle->Address.Address.Bus,
              PORT_SPACE(GnbHandle, PcieWrapper, PcieEngine->Type.Port.PortId % 8, (PcdWrEntry->Address)),
              &(PcdWrEntry->Value),
              WriteAccFlags
              );
            BlastedEntry = TRUE;
          }
          if ((PcdWrEntry->PcdType == TableBlastWriteIfValNotEqual) && (DeterminePcdValue(PcdWrEntry->Token) != PcdWrEntry->CompareValue)) {
            SmnRegisterWrite (
              GnbHandle->Address.Address.Bus,
              PORT_SPACE(GnbHandle, PcieWrapper, PcieEngine->Type.Port.PortId % 8, (PcdWrEntry->Address)),
              &(PcdWrEntry->Value),
              WriteAccFlags
              );
            BlastedEntry = TRUE;
          }
          if ((PcdWrEntry->PcdType == TableBlastWriteValue)) {
            PcdWrEntry->Value = DeterminePcdValue(PcdWrEntry->Token);
            SmnRegisterWrite (
              GnbHandle->Address.Address.Bus,
              PORT_SPACE(GnbHandle, PcieWrapper, PcieEngine->Type.Port.PortId % 8, (PcdWrEntry->Address)),
              &(PcdWrEntry->Value),
              WriteAccFlags
              );
            BlastedEntry = TRUE;
          }
          if (BlastedEntry) {
            IDS_HDT_CONSOLE (NB_MISC, "Blasted PCD WR entry.\n");
          }
          EntrySize = sizeof(GNB_TABLE_ENTRY_PCD_WR);
          break;
        case GnbEntryPcdRmw:
          PcdRmwEntry = (GNB_TABLE_ENTRY_PCD_RMW *)EntryPointer;
          IDS_HDT_CONSOLE(NB_MISC, "  Read GNB_ENTRY_PCD_RMW. Token value %x , PCD Operation Type %d\n", PcdRmwEntry->Token, PcdRmwEntry->PcdType);
          if ((PcdRmwEntry->PcdType == TableBlastWriteIfValEqual) && (DeterminePcdValue(PcdRmwEntry->Token) == PcdRmwEntry->CompareValue)) {
            GnbProcessTableRegisterRmwPortSpace (
              GnbHandle,
              PcieWrapper,
              PcieEngine,
              &(PcdRmwEntry->Data),
              WriteAccFlags
              );
            BlastedEntry = TRUE;
          }
          if ((PcdRmwEntry->PcdType == TableBlastWriteIfValNotEqual) && (DeterminePcdValue(PcdRmwEntry->Token) != PcdRmwEntry->CompareValue)) {
            GnbProcessTableRegisterRmwPortSpace (
              GnbHandle,
              PcieWrapper,
              PcieEngine,
              &(PcdRmwEntry->Data),
              WriteAccFlags
              );
            BlastedEntry = TRUE;
          }
          if (BlastedEntry) {
            IDS_HDT_CONSOLE (NB_MISC, "Blasted PCD RMW entry.\n");
          }
          /// Check for an invalid PCD RMW Instruction(s) to prevent
          /// developer mistakes.
          ASSERT(PcdRmwEntry->PcdType != TableBlastWriteValue);
          EntrySize = sizeof(GNB_TABLE_ENTRY_PCD_RMW);
          break;
        case GnbEntryPropertyRmw:
          if ((Property & ((GNB_TABLE_ENTRY_PROPERTY_RMW *) EntryPointer)->Property) != 0) {
            GnbProcessTableRegisterRmwPortSpace (
              GnbHandle,
              PcieWrapper,
              PcieEngine,
              &((GNB_TABLE_ENTRY_PROPERTY_RMW *) EntryPointer)->Data,
              WriteAccFlags
              );
          }
          EntrySize = sizeof (GNB_TABLE_ENTRY_PROPERTY_RMW);
          break;
        default:
          IDS_HDT_CONSOLE (NB_MISC, "  ERROR!!! Register table parse\n");
          ASSERT (FALSE);
          return 0;
        }
      }
      PcieEngine = PcieLibGetNextDescriptor (PcieEngine);
    }
    PcieWrapper = PcieLibGetNextDescriptor (PcieWrapper);
  }

  return EntrySize;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Process table
 *
 * @param[in] GnbHandle       Gnb handle
 * @param[in] Table           Table pointer
 * @param[in] Property        Property
 * @param[in] Flags           Flags
 * @param[in] StdHeader       Standard configuration header
 */

AGESA_STATUS
GnbBlastTable (
  IN      GNB_HANDLE            *GnbHandle,
  IN      GNB_TABLE             *Table,
  IN      UINT32                Property,
  IN      UINT32                Flags,
  IN      AMD_CONFIG_PARAMS     *StdHeader
  )
{
  UINT8     *EntryPointer;
  UINT32    WriteAccFlags;
  UINTN     EntrySize;

  IDS_HDT_CONSOLE (GNB_TRACE, "%a Enter\n", __FUNCTION__);
  IDS_HDT_CONSOLE (GNB_TRACE, " Property - 0x%08x\n", Property);

  EntryPointer = (UINT8 *) Table;
  WriteAccFlags = 0;
  EntrySize = 0;

  if ((Flags & NBIO_TABLE_FLAGS_FORCE_S3_SAVE) != 0) {
    WriteAccFlags |= GNB_REG_ACC_FLAG_S3SAVE;
  }

  while (*EntryPointer != GnbEntryTerminate) {

    ///
    /// Actions to execute per NBIO
    ///
    if (EntryPointer[1] == ALL_NBIO_TYPE || EntryPointer[1] == ONE_ADDR_TYPE) {
      EntrySize = NbioTypeHandler(
                    EntryPointer,
                    GnbHandle,
                    WriteAccFlags,
                    Property
                    );
    }
    if (EntryPointer[1] == ALL_WRAP_TYPE) {
      EntrySize = WrapperTypeHandler(
                    EntryPointer,
                    GnbHandle,
                    WriteAccFlags,
                    Property
                    );
    }
    if (EntryPointer[1] == ALL_PORT_TYPE) {
      EntrySize = PortTypeHandler(
                    EntryPointer,
                    GnbHandle,
                    WriteAccFlags,
                    Property
                    );
    }

    ///
    /// Make sure table entry was processed. An incorrect type ID
    /// means the table is malformed
    ///
    if (EntryPointer[1] > ALL_PORT_TYPE) {
      IDS_HDT_CONSOLE (GNB_TRACE, "%a : Received unknown type %d\n", __FUNCTION__, EntryPointer[1]);
      ASSERT(FALSE);
    }

    EntryPointer = EntryPointer + EntrySize;
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "%a Exit\n", __FUNCTION__);
  return AGESA_SUCCESS;
}



