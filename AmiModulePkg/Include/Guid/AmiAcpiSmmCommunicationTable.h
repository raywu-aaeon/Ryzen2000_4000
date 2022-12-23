//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
  @brief AMI SMM Communication ACPI Table definition
**/

#ifndef __AMI_ACPI_SMM_COMMUNICATION_TABLE__H__
#define __AMI_ACPI_SMM_COMMUNICATION_TABLE__H__

#include <Uefi/UefiAcpiDataTable.h>

#define AMI_ACPI_SMM_COMMUNICATION_TABLE_GUID\
    { 0xbaedb05d, 0xf2ce, 0x485b, { 0xb4, 0x54, 0xc2, 0x51, 0x87, 0xc, 0xde, 0xfc } }

#pragma pack(1)
typedef struct {
    EFI_ACPI_DATA_TABLE UefiAcpiDataTable; // 0x36 bytes
    UINT16 Revision; // offset 0x36
    UINT64 MailboxAddress; // offset 0x38
    UINT32 SwSmiNumber; // offset 0x40
    UINT32 MailboxHeaderSize; // offset 0x44
} AMI_ACPI_SMM_COMMUNICATION_TABLE;
#pragma pack()

extern EFI_GUID gAmiAcpiSmmCommunucationTableGuid;
#endif
