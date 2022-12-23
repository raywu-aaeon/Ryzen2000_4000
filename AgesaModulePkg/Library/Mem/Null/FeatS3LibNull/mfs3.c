/* $NoKeywords:$ */
/**
 * @file
 *
 * mfs3.c
 *
 * Main S3 resume memory Entrypoint file
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/FEAT/S3)
 * @e \$Revision: 309090 $ @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 *
 **/
/*****************************************************************************
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

/*
 *----------------------------------------------------------------------------
 *                                MODULES USED
 *
 *----------------------------------------------------------------------------
 */



#include "AGESA.h"
#include "Library/AmdBaseLib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "cpuRegisters.h"
#include "OptionMemory.h"
#include "mm.h"
#include "mn.h"
#include "S3.h"
#include "Library/AmdMemFeatS3Lib.h"
#include "Library/AmdHeapLib.h"
#include "Filecode.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEM_NULL_FEATS3LIBNULL_MFS3_FILECODE


extern MEM_NB_SUPPORT memNBInstalled[];

/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                           TYPEDEFS AND STRUCTURES
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                        PROTOTYPES OF LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function is the main memory entry point for the S3 resume sequence
 *      Requirements:
 *
 *      Run-Time Requirements:
 *      1. Complete Hypertransport Bus Configuration
 *      4. BSP in Big Real Mode
 *      5. Stack available
 *
 *      @param[in]  *StdHeader - Config handle for library and services
 *
 *      @return     AGESA_STATUS
 *                          - AGESA_ALERT
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 *                          - AGESA_WARNING
 */
AGESA_STATUS
AmdMemS3Resume (
  IN   AMD_CONFIG_PARAMS *StdHeader
  )
{
  return AGESA_SUCCESS;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function deallocates heap space allocated in memory S3 resume.
 *
 *      @param[in]  *StdHeader - Config handle for library and services
 *
 *      @return     AGESA_STATUS
 *                          - AGESA_ALERT
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 *                          - AGESA_WARNING
 */
AGESA_STATUS
MemS3Deallocate (
  IN   AMD_CONFIG_PARAMS *StdHeader
  )
{
  return AGESA_SUCCESS;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function is the entrance to get device list for memory registers.
 *
 *      @param[in, out]  **DeviceBlockHdrPtr - Pointer to the memory containing the
 *                                             device descriptor list
 *      @param[in]       *StdHeader - Config handle for library and services
 *      @return          AGESA_STATUS
 *                          - AGESA_ALERT
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 *                          - AGESA_WARNING
 */
AGESA_STATUS
MemFS3GetDeviceList (
  IN OUT   DEVICE_BLOCK_HEADER **DeviceBlockHdrPtr,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  return AGESA_SUCCESS;
}


/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function initialize the northbridge block and apply for heap space
 *      before any function call is made to memory component during S3 resume.
 *
 *      @param[in]       *StdHeader - Config handle for library and services
 *      @return          AGESA_STATUS
 *                          - AGESA_ALERT
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 *                          - AGESA_WARNING
 */
AGESA_STATUS
MemS3ResumeInitNB (
  IN   AMD_CONFIG_PARAMS *StdHeader
  )
{
  return AGESA_SUCCESS;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function returns the PCI device register list according to the register
 *      list ID.
 *
 *      @param[in]       *Device - pointer to the PCI_DEVICE_DESCRIPTOR
 *      @param[out]      **RegisterHdr - pointer to the address of the register list
 *      @param[in]       *StdHeader - Config handle for library and services
 *
 *      @return          AGESA_STATUS
 *                          - AGESA_ALERT
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 *                          - AGESA_WARNING
 */
AGESA_STATUS
MemFS3GetPciDeviceRegisterList (
  IN       PCI_DEVICE_DESCRIPTOR     *Device,
     OUT   PCI_REGISTER_BLOCK_HEADER **RegisterHdr,
  IN       AMD_CONFIG_PARAMS         *StdHeader
  )
{
  return AGESA_SUCCESS;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function returns the conditional PCI device register list according
 *      to the register list ID.
 *
 *      @param[in]       *Device - pointer to the CONDITIONAL_PCI_DEVICE_DESCRIPTOR
 *      @param[out]      **RegisterHdr - pointer to the address of the register list
 *      @param[in]       *StdHeader - Config handle for library and services
 *
 *      @return          AGESA_STATUS
 *                          - AGESA_ALERT
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 *                          - AGESA_WARNING
 */
AGESA_STATUS
MemFS3GetCPciDeviceRegisterList (
  IN       CONDITIONAL_PCI_DEVICE_DESCRIPTOR *Device,
     OUT   CPCI_REGISTER_BLOCK_HEADER        **RegisterHdr,
  IN       AMD_CONFIG_PARAMS                 *StdHeader
  )
{
  return AGESA_SUCCESS;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function returns the MSR device register list according to the register
 *      list ID.
 *
 *      @param[in]       *Device - pointer to the MSR_DEVICE_DESCRIPTOR
 *      @param[out]      **RegisterHdr - pointer to the address of the register list
 *      @param[in]       *StdHeader - Config handle for library and services
 *
 *      @return          AGESA_STATUS
 *                          - AGESA_ALERT
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 *                          - AGESA_WARNING
 */
AGESA_STATUS
MemFS3GetMsrDeviceRegisterList (
  IN       MSR_DEVICE_DESCRIPTOR     *Device,
     OUT   MSR_REGISTER_BLOCK_HEADER **RegisterHdr,
  IN       AMD_CONFIG_PARAMS         *StdHeader
  )
{
  return AGESA_SUCCESS;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function returns the conditional MSR device register list according
 *      to the register list ID.
 *
 *      @param[in]       *Device - pointer to the CONDITIONAL_PCI_DEVICE_DESCRIPTOR
 *      @param[out]      **RegisterHdr - pointer to the address of the register list
 *      @param[in]       *StdHeader - Config handle for library and services
 *
 *      @return          AGESA_STATUS
 *                          - AGESA_ALERT
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 *                          - AGESA_WARNING
 */
AGESA_STATUS
MemFS3GetCMsrDeviceRegisterList (
  IN       CONDITIONAL_MSR_DEVICE_DESCRIPTOR     *Device,
     OUT   CMSR_REGISTER_BLOCK_HEADER            **RegisterHdr,
  IN       AMD_CONFIG_PARAMS                     *StdHeader
  )
{
  return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function initialize needed data structures for S3 resume.
 *
 *      @param[in, out]  **S3NBPtr - Pointer to the pointer of northbridge block.
 *      @param[in, out]  *MemPtr - Pointer to MEM_DATA_STRUCT.
 *      @param[in, out]  *mmData - Pointer to MEM_MAIN_DATA_BLOCK.
 *      @param[in]       *StdHeader - Config handle for library and services.
 *
 *      @return          AGESA_STATUS
 *                          - AGESA_ALERT
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 *                          - AGESA_WARNING
 */
AGESA_STATUS
MemS3InitNB (
  IN OUT   S3_MEM_NB_BLOCK **S3NBPtr,
  IN OUT   MEM_DATA_STRUCT **MemPtr,
  IN OUT   MEM_MAIN_DATA_BLOCK *mmData,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  return AGESA_SUCCESS;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function determines if the PSP is present
 *
 *      @param[in]       *StdHeader - Config handle for library and services.
 *
 *      @return          AGESA_STATUS
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 */
AGESA_STATUS
AmdMemDoResume (
  IN   AMD_CONFIG_PARAMS *StdHeader
  )
{
  return AGESA_SUCCESS;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function determines if the revision S3 data blob matches the S3 engine
 *
 *      @param[in]       Storage    - Beginning of the device list.
 *      @param[in]       *StdHeader - Config handle for library and services.
 *
 *      @return          AGESA_STATUS
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 */
AGESA_STATUS
AmdMemS3DatablobRevMatch (
  IN   VOID              *Storage,
  IN   AMD_CONFIG_PARAMS *StdHeader
  )
{
  return AGESA_SUCCESS;
}

