/* $NoKeywords:$ */
/**
 * @file
 *
 * PSP TPM related functions Prototype definition
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 */
/*****************************************************************************
 *
 * Copyright 2008 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting You permission to use this software and documentation (if
 * any) (collectively, the "Software") pursuant to the terms and conditions of
 * the Software License Agreement included with the Software. If You do not have
 * a copy of the Software License Agreement, contact Your AMD representative for
 * a copy.
 *
 * You agree that You will not reverse engineer or decompile the Software, in
 * whole or in part, except as allowed by applicable law.
 *
 * WARRANTY DISCLAIMER: THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND. AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
 * BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, QUALITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT AND WARRANTIES
 * ARISING FROM CUSTOM OF TRADE OR COURSE OF USAGE WITH RESPECT TO THE SOFTWARE,
 * INCLUDING WITHOUT LIMITATION, THAT THE SOFTWARE WILL RUN UNINTERRUPTED OR
 * ERROR-FREE. THE ENTIRE RISK ASSOCIATED WITH THE USE OF THE SOFTWARE IS
 * ASSUMED BY YOU. Some jurisdictions do not allow the exclusion of implied
 * warranties, so the above exclusion may not apply to You, but only to the
 * extent required by law.
 *
 * LIMITATION OF LIABILITY AND INDEMNIFICATION: TO THE EXTENT NOT PROHIBITED BY
 * APPLICABLE LAW, AMD AND ITS LICENSORS WILL NOT, UNDER ANY CIRCUMSTANCES BE
 * LIABLE TO YOU FOR ANY PUNITIVE, DIRECT, INCIDENTAL, INDIRECT, SPECIAL OR
 * CONSEQUENTIAL DAMAGES ARISING FROM POSSESSION OR USE OF THE SOFTWARE OR
 * OTHERWISE IN CONNECTION WITH ANY PROVISION OF THIS AGREEMENT EVEN IF AMD AND
 * ITS LICENSORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. THIS
 * INCLUDES, WITHOUT LIMITATION, DAMAGES DUE TO LOST OR MISAPPROPRIATED DATA,
 * LOST PROFITS OR CONFIDENTIAL OR OTHER INFORMATION, FOR BUSINESS INTERRUPTION,
 * FOR PERSONAL INJURY, FOR LOSS OF PRIVACY, FOR FAILURE TO MEET ANY DUTY
 * INCLUDING OF GOOD FAITH OR REASONABLE CARE, FOR NEGLIGENCE AND FOR ANY OTHER
 * PECUNIARY OR OTHER LOSS WHTSOEVER. In no event shall AMD's total liability to
 * You for all damages, losses, and causes of action (whether in contract, tort
 * (including negligence) or otherwise) exceed the amount of $50 USD. You agree
 * to defend, indemnify and hold harmless AMD, its subsidiaries and affiliates
 * and their respective licensors, directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your
 * possession or use of the Software or violation of the terms and conditions of
 * this Agreement.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS: Notice to U.S. Government End Users. The
 * Software and related documentation are "commercial items", as that term is
 * defined at 48 C.F.R. Section 2.101, consisting of "commercial computer
 * software" and "commercial computer software documentation", as such terms are
 * used in 48 C.F.R. Section 12.212 and 48 C.F.R. Section 227.7202,
 * respectively. Consistent with 48 C.F.R. Section 12.212 or 48 C.F.R. Sections
 * 227.7202-1 through 227.7202-4, as applicable, the commercial computer
 * software and commercial computer software documentation are being licensed to
 * U.S. Government end users: (a) only as commercial items, and (b) with only
 * those rights as are granted to all other end users pursuant to the terms and
 * conditions set forth in this Agreement. Unpublished rights are reserved under
 * the copyright laws of the United States.
 *
 * EXPORT RESTRICTIONS:  You shall adhere to all applicable U.S. import/export
 * laws and regulations, as well as the import/export control laws and
 * regulations of other countries as applicable. You further agree You will not
 * export, re-export, or transfer, directly or indirectly, any product,
 * technical data, software or source code received from AMD under this license,
 * or the direct product of such technical data or software to any country for
 * which the United States or any other applicable government requires an export
 * license or other governmental approval without first obtaining such licenses
 * or approvals, or in violation of any applicable laws or regulations of the
 * United States or the country where the technical data or software was
 * obtained. You acknowledges the technical data and software received will not,
 * in the absence of authorization from U.S. or local law and regulations as
 * applicable, be used by or exported, re-exported or transferred to: (i) any
 * sanctioned or embargoed country, or to nationals or residents of such
 * countries; (ii) any restricted end-user as identified on any applicable
 * government end-user list; or (iii) any party where the end-use involves
 * nuclear, chemical/biological weapons, rocket systems, or unmanned air
 * vehicles.  For the most current Country Group listings, or for additional
 * information about the EAR or Your obligations under those regulations, please
 * refer to the website of the U.S. Bureau of Industry and Security at
 * http://www.bis.doc.gov/.
 *******************************************************************************
 **/
#ifndef _PSP_FTPM_LIB_H_
#define _PSP_FTPM_LIB_H_
#include <IndustryStandard/Acpi30.h>

//
/// 1MB @todo check. Also move this to common header file and make it customizable
/// perhaps fed it via build option etc
#define FTPM_COMMAND_BUFFER_SIZE  (16*1024)
#define FTPM_RESPONSE_BUFFER_SIZE (16*1024)

/* SYSTEM_TPM_CONFIG_VAL
 *  Value range for APCB_TOKEN_UID_PSP_SYSTEM_TPM_CONFIG
 */
typedef enum {
  SYSTEM_TPM_CONFIG_DTPM     = 0x00, ///< dTPM
  SYSTEM_TPM_CONFIG_PSP_FTPM = 0x01, ///< PSP FTPM
  SYSTEM_TPM_CONFIG_HSP_FTPM = 0x02, ///< HSP FTPM
  SYSTEM_TPM_CONFIG_NONE     = 0xFF, ///< None of TPM
} SYSTEM_TPM_CONFIG_VAL;

#pragma  pack (push, 1)
/// Define TPM_2_CONTROL_AREA
typedef struct {
    // Interface Identifier
  volatile UINT64                InterfaceIdentifier; ///< Interface Identifier

  // TPM2 Control Area Extension
  volatile UINT32                 Clear;            ///< Clear
  volatile UINT32                 RemainingBytes;   ///< RemainingBytes
  volatile UINT32                 StatusReserved;   ///< StatusReserved
  volatile UINT32                 StatusError;      ///< StatusError
  volatile UINT32                 StatusCancel;     ///< StatusCancel
  volatile UINT32                 StatusStart;      ///< StatusStart
  UINT64                          InterruptControl; ///< InterruptControl
  UINT32                          CommandSize;      ///< CommandSize
  EFI_PHYSICAL_ADDRESS            CommandAddress;   ///< CommandAddress
  UINT32                          ResponseSize;     ///< ResponseSize
  EFI_PHYSICAL_ADDRESS            ResponseAddress;  ///< ResponseAddress
// Memory Absent command/response buffer
  volatile UINT32                 CmdRespHWBuffer;  ///< Cmd/Rsp HW Buffer

} TPM2_CONTROL_AREA;


#pragma  pack (pop)

/**
 *  Set Command,Response buffer registers, Buffer address equal to NULL will skip the setting
 *
 * @param[in]    CommandBuffer              Point to the TPM command buffer
 * @param[in]    CommandSize                Size of the TPM command buffer
 * @param[in]    ResponseBuffer             Point to the TPM response buffer
 * @param[in]    ResponseSize               Size of the TPM response buffer
 *
 * @return       EFI_SUCCESS                Command executed successfully
 * @return       EFI_UNSUPPORTED            Device unsupported
 *
 */
EFI_STATUS
FtpmAssignMemory (
  IN     UINTN                CommandBuffer,
  IN     UINT32               CommandSize,
  IN     UINTN                ResponseBuffer,
  IN     UINT32               ResponseSize
  );

/**
 *  GET TPM related Info
 *
 * @param[in,out] FtpmStatus              Used to hold more detail info (Unused Currently)
 *
 * @return       EFI_SUCCESS              Ftpm function supported
 * @return       EFI_UNSUPPORTED          Ftpm function unsupported
 *
 */
EFI_STATUS
FtpmGetInfo (
  IN OUT UINTN                *FtpmStatus
  );

/**
 *  Send a TPM command
 *
 * @param[in]    CommandBuffer              Point to the TPM command buffer
 * @param[in]    CommandSize                Size of the TPM command buffer
 *
 * @return       EFI_SUCCESS                Command executed successfully
 * @return       EFI_UNSUPPORTED            Device unsupported
 * @return       EFI_TIMEOUT                Command fail due the time out
 * @return       EFI_DEVICE_ERROR           Command fail due the error status set
 * @return       EFI_BUFFER_TOO_SMALL       Response buffer too small to hold the response
 *
 */
EFI_STATUS
FtpmSendCommand (
  IN     VOID                 *CommandBuffer,
  IN     UINT32                CommandSize
  );

/**
 *  Get a TPM command's response
 *
 * @param[in]    ResponseBuffer             Point to the TPM response buffer
 * @param[in]    ResponseSize               Size of the TPM response buffer
 *
 * @return       EFI_SUCCESS                Command executed successfully
 * @return       EFI_UNSUPPORTED            Device unsupported
 * @return       EFI_TIMEOUT                Command fail due the time out
 * @return       EFI_DEVICE_ERROR           Command fail due the error status set
 * @return       EFI_BUFFER_TOO_SMALL       Response buffer too small to hold the response
 *
 */
EFI_STATUS
FtpmGetResponse (
  IN OUT VOID                  *ResponseBuffer,
  IN OUT UINT32                *ResponseSize
  );

/**
 *  Execute a TPM command
 *
 * @param[in]    CommandBuffer              Point to the TPM command buffer
 * @param[in]    CommandSize                Size of the TPM command buffer
 * @param[in]    ResponseBuffer             Point to the TPM response buffer
 * @param[in]    ResponseSize               Size of the TPM response buffer
 *
 * @return       EFI_SUCCESS                Command executed successfully
 * @return       EFI_UNSUPPORTED            Device unsupported
 * @return       EFI_TIMEOUT                Command fail due the time out
 * @return       EFI_DEVICE_ERROR           Command fail due the error status set
 * @return       EFI_BUFFER_TOO_SMALL       Response buffer too small to hold the response
 *
 */
EFI_STATUS
FtpmExecuteCommand (
  IN     VOID                 *CommandBuffer,
  IN     UINT32               CommandSize,
  IN OUT VOID                 *ResponseBuffer,
  IN OUT UINT32               *ResponseSize
  );
#endif //_PSP_FTPM_LIB_H_
