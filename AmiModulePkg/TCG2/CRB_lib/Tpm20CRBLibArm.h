//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TcgNext/Libraries/Tpm20CrbLib/Tpm20CRBLib.h 1     10/08/13 11:59a Fredericko $
//
// $Revision: 1 $
//
// $Date: 10/08/13 11:59a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TcgNext/Libraries/Tpm20CrbLib/Tpm20CRBLib.h $
//
// 1     10/08/13 11:59a Fredericko
// Initial Check-In for Tpm-Next module
//
// 2     9/16/13 1:51p Fredericko
//
// 1     7/10/13 5:51p Fredericko
// [TAG]        EIP120969
// [Category]   New Feature
// [Description]    TCG (TPM20)
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
#include <Efi.h>
#include <Token.h>


//Defines ACPI Interface for Control Resource Buffer Access
#define TPM20H2NS(x)        ((((x) << 8) | ((x) >> 8)) & 0xffff)
#define TPM20H2NL(x)        (TPM20H2NS ((x) >> 16) | (TPM20H2NS ((x) & 0xffff) << 16))

#define CONTROL_AREA_REQUEST               0x00
#define CONTROL_AREA_STATUS                 0x04
#define CONTROL_AREA_CANCEL                0x08
#define CONTROL_AREA_START                 0x0C
#define CONTROL_AREA_INT                   0x10
#define CONTROL_AREA_CMD_SZ                0x18
#define CONTROL_AREA_CMD_BASE              0x1C
#define CONTROL_AREA_RSP_SZ                0x24
#define CONTROL_AREA_RSP_BASE              0x28

//Timeouts
#define TIMEOUT_A         500           ///< 500 microseconds
#define TIMEOUT_B         500 * 1000    ///< 10ms (max command processing time in PK-TPM ca. 3ms)
#define TIMEOUT_C         1000 * 1000   ///< 1s
#define TIMEOUT_D         500 * 1000    ///< 500 ms
#define POLLING_PERIOD    140           ///< Poll register every 140 microsecondss

#define CRB_DEVICE_CMD     0x40
#define CRB_DEVICE_STS     0x44

#define TPM20_CRB_IDLE     0x02

#define TPM20_MAX_COMMAND_SIZE     0x0F80
#define StartStatusFieldSet        0x00000001

#define TPM20_CRB_CMD_BASE 0x80
#define TPM20_CRB_RSP_BASE 0x80

#define TPM20_CRBSTATUS_START      0x00000001
#define TPM20_CRB_ALL_CLEAR        0xFFFFFFFF

#define RESPONSE_HEADER_SIZE  12



typedef struct
{
    UINT16 tag;
    UINT32 paramSize;
    UINT32 responseCode;
} CHK_RESPONSE_HEADER;

#pragma pack(1)

typedef struct _CRB_REQUEST_FIELD_
{
    UINT32   CmdReady:1;        //Set by software to indicate that the TPM should prepare to receive the next command
    UINT32   GoIdle:1;          //Set by software to indicate to the TPM that it may go o an idle state
    UINT32   Reserved:30;       //reserved
} CRB_REQUEST_FIELD;

typedef struct _STATUS_FIELD_
{
    UINT32   Error:1;           //Set by TPM in case of unrecoverable error
    UINT32   TpmIdle:1;         //SET by the TPM if in low power state
    UINT32   Reserved:30;       //reserved
} STATUS_FIELD;

typedef struct _CANCEL_FIELD_
{
    UINT32   Cancel:1;           //Set by software to request cancellation of the current command
    UINT32   Reserved:31;       //reserved
} CANCEL_FIELD;

typedef struct _START_FIELD_
{
    UINT32   Start:1;           //Set by software for TPM to start Command processing. Cleared by TPM afterwards
    UINT32   Reserved:31;       //reserved
} START_FIELD;


typedef struct _CONTROL_AREA_LAYOUT_
{
    CRB_REQUEST_FIELD RequestField;
    STATUS_FIELD      StatusField;
    CANCEL_FIELD      CancelField;
    START_FIELD       StartField;
    UINT8             InterruptControl[8];
    UINT32            CommandSize;
    UINT32            CommandAddressL;
    UINT32            CommandAddressH;
    UINT32            ResponseSize;
    UINT32            ResponseAddressL;
    UINT32            ResponseAddressH;
} CONTROL_AREA_LAYOUT;

typedef struct _GENERIC_RESP_HDR_
{
    UINT16 Tag;
    UINT32 RespSize;
    UINT32 RespCode;
} GENERIC_RESP_HDR;

typedef volatile CONTROL_AREA_LAYOUT *CONTROL_AREA_LAYOUT_PTR;
#pragma pack()


EFI_STATUS
EFIAPI
CrbSubmitCmd(
    IN      UINT8     *InputBuffer,
    IN      UINT32     InputBufferSize,
    OUT     UINT8     *OutputBuffer,
    OUT     UINT32    *OutputBufferSize);

BOOLEAN isTpm20CrbPresent();
UINT8   GetCurrentInterfaceType();
BOOLEAN IsPTP();
BOOLEAN CrbSupported();
BOOLEAN FIFOSupported();
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
