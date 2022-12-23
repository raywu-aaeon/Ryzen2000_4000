/* $NoKeywords:$ */
/**
 * @file
 *
 * APCB.h
 *
 * AGESA PSP Output Block
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (APOB)
 * @e \$Revision$ @e \$Date$
 *
 **/
/*****************************************************************************
*
* Copyright 2008 - 2020 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
*
*/

#ifndef _APOB_CMN_H_
#define _APOB_CMN_H_

//Common structure across programs

/*----------------------------------------------------------------------------
 *   Mixed (DEFINITIONS AND MACROS / TYPEDEFS, STRUCTURES, ENUMS)
 *
 *----------------------------------------------------------------------------
 */

/*-----------------------------------------------------------------------------
 *                         DEFINITIONS AND MACROS
 *
 *-----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                         TYPEDEFS, STRUCTURES, ENUMS
 *
 *----------------------------------------------------------------------------
 */
#define APOB_SIGNATURE        0x424F5041  //!!APOB
/// AMD APOB_HMAC
#define APOB_HMAC_SIZE 32

#define MAX_APOB_ERROR_ENTRIES  64
// APOB Group Definitons
#define APOB_MEM      1
#define APOB_DF       2
#define APOB_CCX      3
#define APOB_GNB      4
#define APOB_FCH      5
#define APOB_PSP      6
#define APOB_GEN      7
#define APOB_SMBIOS   8
#define APOB_FABRIC   9
// APOB Type Definitons
#define APOB_MEM_GENERAL_ERRORS_TYPE   1
#define APOB_MEM_GENERAL_CONFIGURATION_INFO_TYPE   2
#define APOB_GEN_CONFIGURATION_INFO_TYPE   3
#define APOB_GEN_S3_REPLAY_BUFFER_INFO_TYPE   4
#define APOB_MEM_PMU_SMB_TYPE   5
#define APOB_GEN_EVENT_LOG_TYPE   6
#define APOB_MEM_DIMM_SMBUS_INFO_TYPE   7
#define APOB_MEM_SMBIOS_TYPE  8
#define APOB_SYS_MAP_INFO_TYPE   9
#define APOB_MEM_NVDIMM_INFO_TYPE   15
#define APOB_APCB_BOOT_INFO_TYPE    16
#define APOB_MEM_DIMM_SPD_DATA_TYPE     17
#define APOB_MEM_MBIST_RESULT_INFO_TYPE 18
#define APOB_SYS_NPS_INFO_TYPE   19
#define APOB_SYS_SLINK_INFO_TYPE   20
#define APOB_DF_DXIO_PHY_FW_OVERRIDE_INFO_TYPE 21
#define APOB_MEM_PMU_TRAINING_FAILURE_INFO_TYPE 22
#define APOB_ENV_FLAGS_INFO_TYPE 23
#define APOB_MEM_S3_DDR_PHY_REPLAY_PHASE0_BUFFER_INFO_TYPE   30
#define APOB_MEM_S3_DDR_PHY_REPLAY_MAX_ENTRIES               10
// APOB CCX Type Definitons
#define APOB_CCX_LOGICAL_TO_PHYSICAL_MAP_TYPE  1
#define APOB_CCX_EDC_THROTTLE_THRESH_TYPE      2
#define APOB_CCD_LOGICAL_TO_PHYSICAL_MAP_TYPE  3

typedef struct {
  UINT8  ApobHmac[APOB_HMAC_SIZE];                      ///< APOB HMAC for secutity check of each type
} APOB_HMAC;

/// AMD APOB_HEADER Header
typedef struct {
  UINT32   Signature;                 ///< APOB signature
  UINT32   Version;                   ///< Version
  UINT32   Size;                      ///< APOB Size
  UINT32   OffsetOfFirstEntry;        ///< APOB Header Size
} APOB_BASE_HEADER;


/// AMD APOB_HEADER Header
typedef struct {
  UINT32  GroupID;                          ///< Group ID
  UINT32  DataTypeID;                       ///< Data Type ID
  UINT32  InstanceID;                       ///< Instance ID
                                            ///< - Bit 15:0 - SocketID
                                            ///< - Bit  8:0 - DieID
  UINT32  TypeSize;                         ///< Type Size (including header)
  APOB_HMAC ApobTypeHmac;                   ///< Hmac location for type
} APOB_TYPE_HEADER;

///
/// APOB SPD Data for each DIMM.
///
typedef struct _APOB_SPD_STRUCT {
  UINT8  SocketNumber;          ///< Indicates the socket number
  UINT8  ChannelNumber;          ///< Indicates the channel number
  UINT8  DimmNumber;          ///< Indicates the channel number
  UINT8   PageAddress;  ///< Indicates the 256 Byte EE Page the data belongs to
                        //      0 = Lower Page
                        //      1 = Upper Page
  BOOLEAN DimmPresent;   //< Indicates if the DIMM is present
  UINT8  MuxPresent;      ///< SpdMux Present or not. if 1, then yes otherwise no
  UINT8  MuxI2CAddress;      ///< MuxI2cAddress
  UINT8  MuxChannel;         ///< MuxChannel no.
  UINT32 Address;         ///< SMBus address of the DRAM
  UINT32 SerialNumber;   ///< DIMM Serial Number
  UINT32 DeviceWidth:3;         ///< Device Width i.e. x4, x8, x16 and x32
  UINT32 DpprSupported:2;       ///< Dppr Support Present
  UINT32 SpprSupported:1;       ///< Sppd Support Present
  UINT32 Reserved:26;           ///< Reserved for Future Use
  UINT8 Data[512];      ///< Buffer for 256 Bytes of SPD data from DIMM
} APOB_SPD_STRUCT;

#define  EDC_THROTTLE_TYPE_INVALID  0
#define  EDC_THROTTLE_TYPE_L3       1
#define  EDC_THROTTLE_TYPE_CORE     2
#define  EDC_THROTTLE_TYPE_FP       3
#define  MAX_NUMBER_OF_THROTTLERS   3
#define  CCX_NOT_PRESENT (0xFF)

typedef struct {
  UINT32   Type;
  UINT32   OpnValue;
  UINT32   AblProgrammedValue;
} EDC_THROTTLE_THRESHOLD;

/// Event log entry
typedef struct {
  UINT32    EventClass;   ///< The severity of the event, its associated AGESA_STATUS.
  UINT32    EventInfo;        ///< Uniquely identifies the event.
  UINT32    DataA;
  UINT32    DataB;
} APOB_ERROR_LOG;
typedef struct {
  APOB_ERROR_LOG AgesaEvent[MAX_APOB_ERROR_ENTRIES];    ///< The entry itself.
} AGESA_EVENT_STRUCT;
typedef struct {
  APOB_TYPE_HEADER  ApobTypeHeader;    ///< APOB Type Header
  UINT16        Count;           ///< The total number of active entries.
  AGESA_EVENT_STRUCT ApobEventStruct;   ///< The entries.
} EVENT_LOG_STRUCT;
#endif  /* _APOB_CMN_H_ */

