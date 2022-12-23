/*****************************************************************************
 *
 * Copyright 2012 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 ******************************************************************************
 */

#ifndef _AMD_CPM_FUNCTION_H_
#define _AMD_CPM_FUNCTION_H_

typedef UINT8 (EFIAPI *AMD_CPM_IOREAD8_FN) (
  IN       UINT16                      Port
  );

typedef UINT16 (EFIAPI *AMD_CPM_IOREAD16_FN) (
  IN       UINT16                      Port
  );

typedef UINT32 (EFIAPI *AMD_CPM_IOREAD32_FN) (
  IN       UINT16                      Port
  );

typedef void (EFIAPI *AMD_CPM_IOWRITE8_FN) (
  IN       UINT16                      Port,
  IN       UINT8                       Value
  );

typedef void (EFIAPI *AMD_CPM_IOWRITE16_FN) (
  IN       UINT16                      Port,
  IN       UINT16                      Value
  );

typedef void (EFIAPI *AMD_CPM_IOWRITE32_FN) (
  IN       UINT16                      Port,
  IN       UINT32                      Value
  );

typedef UINT8 (EFIAPI *AMD_CPM_MMIOREAD8_FN) (
  IN       UINTN                       Address
  );

typedef UINT16 (EFIAPI *AMD_CPM_MMIOREAD16_FN) (
  IN       UINTN                       Address
  );

typedef UINT32 (EFIAPI *AMD_CPM_MMIOREAD32_FN) (
  IN       UINTN                       Address
  );

typedef UINT64 (EFIAPI *AMD_CPM_MMIOREAD64_FN) (
  IN       UINTN                       Address
  );

typedef UINT8 (EFIAPI *AMD_CPM_MMIOWRITE8_FN) (
  IN       UINTN                       Address,
  IN       UINT8                       Value
  );

typedef UINT16 (EFIAPI *AMD_CPM_MMIOWRITE16_FN) (
  IN       UINTN                       Address,
  IN       UINT16                      Value
  );

typedef UINT32 (EFIAPI *AMD_CPM_MMIOWRITE32_FN) (
  IN       UINTN                       Address,
  IN       UINT32                      Value
  );

typedef UINT64 (EFIAPI *AMD_CPM_MMIOWRITE64_FN) (
  IN       UINTN                       Address,
  IN       UINT64                      Value
  );

typedef UINT8 (EFIAPI *AMD_CPM_MMIOOR8_FN) (
  IN       UINTN                       Address,
  IN       UINT8                       OrData
  );

typedef UINT16 (EFIAPI *AMD_CPM_MMIOOR16_FN) (
  IN       UINTN                       Address,
  IN       UINT16                      OrData
  );

typedef UINT32 (EFIAPI *AMD_CPM_MMIOOR32_FN) (
  IN       UINTN                       Address,
  IN       UINT32                      OrData
  );

typedef UINT64 (EFIAPI *AMD_CPM_MMIOOR64_FN) (
  IN       UINTN                       Address,
  IN       UINT64                      OrData
  );

typedef UINT8 (EFIAPI *AMD_CPM_MMIOAND8_FN) (
  IN       UINTN                       Address,
  IN       UINT8                       AndData
  );

typedef UINT16 (EFIAPI *AMD_CPM_MMIOAND16_FN) (
  IN       UINTN                       Address,
  IN       UINT16                      AndData
  );

typedef UINT32 (EFIAPI *AMD_CPM_MMIOAND32_FN) (
  IN       UINTN                       Address,
  IN       UINT32                      AndData
  );

typedef UINT64 (EFIAPI *AMD_CPM_MMIOAND64_FN) (
  IN       UINTN                       Address,
  IN       UINT64                      AndData
  );

typedef UINT8 (EFIAPI *AMD_CPM_MMIOANDTHENOR8_FN) (
  IN       UINTN                       Address,
  IN       UINT8                       AndData,
  IN       UINT8                       OrData
  );

typedef UINT16 (EFIAPI *AMD_CPM_MMIOANDTHENOR16_FN) (
  IN       UINTN                       Address,
  IN       UINT16                      AndData,
  IN       UINT16                      OrData
  );

typedef UINT32 (EFIAPI *AMD_CPM_MMIOANDTHENOR32_FN) (
  IN       UINTN                       Address,
  IN       UINT32                      AndData,
  IN       UINT32                      OrData
  );

typedef UINT64 (EFIAPI *AMD_CPM_MMIOANDTHENOR64_FN) (
  IN       UINTN                       Address,
  IN       UINT64                      AndData,
  IN       UINT64                      OrData
  );

typedef UINT64 (EFIAPI *AMD_CPM_MSRREAD_FN) (
  IN       UINT32                      Index
  );

typedef UINT64 (EFIAPI *AMD_CPM_MSRWRITE_FN) (
  IN       UINT32                      Index,
  IN       UINT64                      Value
  );

typedef UINT64 (EFIAPI *AMD_CPM_READTSC_FN) (
  );

typedef UINT8 (EFIAPI *AMD_CPM_BITSCANFORWARD_FN) (
  IN       UINT32                      Value
  );

typedef UINT8 (EFIAPI *AMD_CPM_BITSCANREVERSE_FN) (
  IN       UINT32                      Value
  );

typedef VOID (EFIAPI* AMD_CPM_CPUIDRAWREAD_FN) (
  IN       UINT32                      CpuidFcnAddress,
     OUT   CPUID_DATA                  *Value
  );

typedef VOID (EFIAPI* AMD_CPM_CPUIDREAD_FN) (
  IN       VOID                        *This,
     OUT   UINT32                      *CpuidFamilyModelStepping,
     OUT   UINT32                      *PkgType
  );

typedef void (EFIAPI *AMD_CPM_POSTCODE_FN) (
  IN       UINT32                      PostCode
  );

typedef void (EFIAPI *AMD_CPM_STALL_FN) (
  IN       VOID                        *This,
  IN       UINT32                      Microseconds
  );

typedef UINT8 (EFIAPI *AMD_CPM_GETGPIO_FN) (
  IN       VOID                        *This,
  IN       UINT16                      Pin
  );

typedef void (EFIAPI *AMD_CPM_SETGPIO_FN) (
  IN       VOID                        *This,
  IN       UINT16                      Pin,
  IN       UINT16                      Value
  );

typedef UINT8 (EFIAPI *AMD_CPM_GETRTC_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Index
  );

typedef void (EFIAPI *AMD_CPM_SETRTC_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Index,
  IN       UINT8                       Value
  );

typedef UINT8 (EFIAPI *AMD_CPM_GETACPI_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Index
  );

typedef void (EFIAPI *AMD_CPM_SETACPI_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Index,
  IN       UINT8                       Value
  );

typedef UINT8 (EFIAPI *AMD_CPM_GETGEVENT_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Pin
  );

typedef void (EFIAPI *AMD_CPM_SETGEVENT_FN) (
  IN       VOID                        *This,
  IN       UINT16                      Pin,
  IN       UINT16                      Value
  );

typedef void (EFIAPI *AMD_CPM_SETSMICONTROL_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Pin,
  IN       UINT16                      Value
  );

typedef void (EFIAPI *AMD_CPM_SETGEVENTSCITRIG_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Pin,
  IN       UINT8                       Value
  );

typedef void (EFIAPI *AMD_CPM_SETGEVENTSCI_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Pin
  );

typedef UINT32 (EFIAPI *AMD_CPM_GETSTRAP_FN) (
  IN       VOID                        *This
  );

typedef void (EFIAPI *AMD_CPM_SETCLKREQ_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Socket,
  IN       UINT8                       Die,
  IN       UINT8                       Bridge,
  IN       UINT8                       Miscid,
  IN       UINT8                       ClkId,
  IN       UINT8                       ClkReq
  );

typedef UINT8 (EFIAPI *AMD_CPM_GETCLKREQ_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Socket,
  IN       UINT8                       Die,
  IN       UINT8                       Bridge,
  IN       UINT8                       Miscid,
  IN       UINT8                       ClkId
  );

typedef void (EFIAPI *AMD_CPM_SETFANON_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Fan
  );

typedef void (EFIAPI *AMD_CPM_SETPROCHOT_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Enable,
  IN       UINT8                       Fan,
  IN       UINT8                       Freq
  );

typedef UINT32 (EFIAPI *AMD_CPM_GETSBTSIADDR_FN) (
  IN       VOID                        *This
  );

typedef EFI_STATUS (EFIAPI *AMD_CPM_SMBUSREAD_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Select,
  IN       UINT8                       Address,
  IN       UINT8                       Offset,
  IN       UINTN                       Length,
     OUT   UINT8                       *Value
  );

typedef EFI_STATUS (EFIAPI *AMD_CPM_SMBUSWRITE_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Select,
  IN       UINT8                       Address,
  IN       UINT8                       Offset,
  IN       UINTN                       Length,
  IN       UINT8                       *Value
  );

typedef void* (EFIAPI *AMD_CPM_GETTABLEPTR_FN) (
  IN       VOID                        *This,
  IN       UINT32                      TableId
  );

typedef void* (EFIAPI *AMD_CPM_ADDTABLE_FN) (
  IN       VOID                        *This,
  IN       VOID                        *TablePtr
  );

typedef void* (EFIAPI *AMD_CPM_REMOVETABLE_FN) (
  IN       VOID                        *This,
  IN       VOID                        *TablePtr
  );

typedef void (EFIAPI *AMD_CPM_SETMEMVOLTAGE_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Voltage
  );

typedef void (EFIAPI *AMD_CPM_SETVDDPVDDRVOLTAGE_FN) (
  IN       VOID                        *This,
  IN       VDDP_VDDR_VOLTAGE           Voltage
  );

typedef BOOLEAN (EFIAPI *AMD_CPM_ADDSSDTCALLBACK_FN) (
  IN       VOID                        *This,
  IN       VOID                        *AcpiTablePtr,
  IN       VOID                        *Context
  );

typedef EFI_STATUS (EFIAPI *AMD_CPM_ADDSSDTTABLE_FN) (
  IN       VOID                        *This,
  IN       VOID                        *EfiGuid,
  IN       UINT64                      *OemTableId,
  IN       AMD_CPM_ADDSSDTCALLBACK_FN  Function,
  IN       VOID                        *Context
  );

typedef BOOLEAN (EFIAPI *AMD_CPM_ISAMLOPREGIONOBJECT_FN) (
  IN       UINT8                       *TablePtr
  );

typedef UINT8 (EFIAPI *AMD_CPM_CHECKPCIEDEVICE_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Socket,
  IN       UINT8                       Die,
  IN       UINT8                       Bridge,
  IN       UINT8                       Device,
  IN       UINT8                       Function
  );

typedef BOOLEAN (EFIAPI *AMD_CPM_CHECKPCIEVGA_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Socket,
  IN       UINT8                       Die,
  IN       UINT8                       Bridge,
  IN       UINT8                       Device,
  IN       UINT8                       Function
  );

typedef void (EFIAPI *AMD_CPM_PCIERESET_FN) (
  IN       VOID                        *This,
  IN       UINT8                       ResetId,
  IN       UINT8                       ResetControl
  );

typedef void (EFIAPI *AMD_CPM_RESETDEVICE_FN) (
  IN       VOID                        *This,
  IN       UINT8                       DeviceId,
  IN       UINT8                       Mode
  );

typedef UINT8 (EFIAPI *AMD_CPM_PCIREAD8_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Bus,
  IN       UINT8                       Device,
  IN       UINT8                       Function,
  IN       UINT16                      Offset
  );

typedef UINT16 (EFIAPI *AMD_CPM_PCIREAD16_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Bus,
  IN       UINT8                       Device,
  IN       UINT8                       Function,
  IN       UINT16                      Offset
  );

typedef UINT32 (EFIAPI *AMD_CPM_PCIREAD32_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Bus,
  IN       UINT8                       Device,
  IN       UINT8                       Function,
  IN       UINT16                      Offset
  );

typedef void (EFIAPI *AMD_CPM_PCIWRITE8_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Bus,
  IN       UINT8                       Device,
  IN       UINT8                       Function,
  IN       UINT16                      Offset,
  IN       UINT8                       Data
  );

typedef void (EFIAPI *AMD_CPM_PCIWRITE16_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Bus,
  IN       UINT8                       Device,
  IN       UINT8                       Function,
  IN       UINT16                      Offset,
  IN       UINT16                      Data
  );

typedef void (EFIAPI *AMD_CPM_PCIWRITE32_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Bus,
  IN       UINT8                       Device,
  IN       UINT8                       Function,
  IN       UINT16                      Offset,
  IN       UINT32                      Data
  );

typedef void (EFIAPI *AMD_CPM_PCIAND8_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Bus,
  IN       UINT8                       Device,
  IN       UINT8                       Function,
  IN       UINT16                      Offset,
  IN       UINT8                       AndData
  );

typedef void (EFIAPI *AMD_CPM_PCIAND16_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Bus,
  IN       UINT8                       Device,
  IN       UINT8                       Function,
  IN       UINT16                      Offset,
  IN       UINT16                      AndData
  );

typedef void (EFIAPI *AMD_CPM_PCIAND32_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Bus,
  IN       UINT8                       Device,
  IN       UINT8                       Function,
  IN       UINT16                      Offset,
  IN       UINT32                      AndData
  );

typedef void (EFIAPI *AMD_CPM_PCIOR8_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Bus,
  IN       UINT8                       Device,
  IN       UINT8                       Function,
  IN       UINT16                      Offset,
  IN       UINT8                       OrData
  );

typedef void (EFIAPI *AMD_CPM_PCIOR16_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Bus,
  IN       UINT8                       Device,
  IN       UINT8                       Function,
  IN       UINT16                      Offset,
  IN       UINT16                      OrData
  );

typedef void (EFIAPI *AMD_CPM_PCIOR32_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Bus,
  IN       UINT8                       Device,
  IN       UINT8                       Function,
  IN       UINT16                      Offset,
  IN       UINT32                      OrData
  );

typedef void (EFIAPI *AMD_CPM_PCIANDTHENOR8_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Bus,
  IN       UINT8                       Device,
  IN       UINT8                       Function,
  IN       UINT16                      Offset,
  IN       UINT8                       AndData,
  IN       UINT8                       OrData
  );

typedef void (EFIAPI *AMD_CPM_PCIANDTHENOR16_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Bus,
  IN       UINT8                       Device,
  IN       UINT8                       Function,
  IN       UINT16                      Offset,
  IN       UINT16                      AndData,
  IN       UINT16                      OrData
  );

typedef void (EFIAPI *AMD_CPM_PCIANDTHENOR32_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Bus,
  IN       UINT8                       Device,
  IN       UINT8                       Function,
  IN       UINT16                      Offset,
  IN       UINT32                      AndData,
  IN       UINT32                      OrData
  );

typedef UINT8 (EFIAPI *AMD_CPM_SMNREAD8_FN) (
  IN       VOID                        *This,
  IN       UINT16                      Socket,
  IN       UINT16                      Die,
  IN       UINT16                      Bridge,
  IN       UINT32                      SmnAddr,
  IN       UINT32                      Offset
  );

typedef UINT16 (EFIAPI *AMD_CPM_SMNREAD16_FN) (
  IN       VOID                        *This,
  IN       UINT16                      Socket,
  IN       UINT16                      Die,
  IN       UINT16                      Bridge,
  IN       UINT32                      SmnAddr,
  IN       UINT32                      Offset
  );

typedef UINT32 (EFIAPI *AMD_CPM_SMNREAD32_FN) (
  IN       VOID                        *This,
  IN       UINT16                      Socket,
  IN       UINT16                      Die,
  IN       UINT16                      Bridge,
  IN       UINT32                      SmnAddr,
  IN       UINT32                      Offset
  );

typedef void (EFIAPI *AMD_CPM_SMNWRITE8_FN) (
  IN       VOID                        *This,
  IN       UINT16                      Socket,
  IN       UINT16                      Die,
  IN       UINT16                      Bridge,
  IN       UINT32                      SmnAddr,
  IN       UINT32                      Offset,
  IN       UINT8                       Data
  );

typedef void (EFIAPI *AMD_CPM_SMNWRITE16_FN) (
  IN       VOID                        *This,
  IN       UINT16                      Socket,
  IN       UINT16                      Die,
  IN       UINT16                      Bridge,
  IN       UINT32                      SmnAddr,
  IN       UINT32                      Offset,
  IN       UINT16                      Data
  );

typedef void (EFIAPI *AMD_CPM_SMNWRITE32_FN) (
  IN       VOID                        *This,
  IN       UINT16                      Socket,
  IN       UINT16                      Die,
  IN       UINT16                      Bridge,
  IN       UINT32                      SmnAddr,
  IN       UINT32                      Offset,
  IN       UINT32                      Data
  );

typedef void (EFIAPI *AMD_CPM_SMNAND8_FN) (
  IN       VOID                        *This,
  IN       UINT16                      Socket,
  IN       UINT16                      Die,
  IN       UINT16                      Bridge,
  IN       UINT32                      SmnAddr,
  IN       UINT32                      Offset,
  IN       UINT8                       AndData
  );

typedef void (EFIAPI *AMD_CPM_SMNAND16_FN) (
  IN       VOID                        *This,
  IN       UINT16                      Socket,
  IN       UINT16                      Die,
  IN       UINT16                      Bridge,
  IN       UINT32                      SmnAddr,
  IN       UINT32                      Offset,
  IN       UINT16                      AndData
  );

typedef void (EFIAPI *AMD_CPM_SMNAND32_FN) (
  IN       VOID                        *This,
  IN       UINT16                      Socket,
  IN       UINT16                      Die,
  IN       UINT16                      Bridge,
  IN       UINT32                      SmnAddr,
  IN       UINT32                      Offset,
  IN       UINT32                      AndData
  );

typedef void (EFIAPI *AMD_CPM_SMNOR8_FN) (
  IN       VOID                        *This,
  IN       UINT16                      Socket,
  IN       UINT16                      Die,
  IN       UINT16                      Bridge,
  IN       UINT32                      SmnAddr,
  IN       UINT32                      Offset,
  IN       UINT8                       OrData
  );

typedef void (EFIAPI *AMD_CPM_SMNOR16_FN) (
  IN       VOID                        *This,
  IN       UINT16                      Socket,
  IN       UINT16                      Die,
  IN       UINT16                      Bridge,
  IN       UINT32                      SmnAddr,
  IN       UINT32                      Offset,
  IN       UINT16                      OrData
  );

typedef void (EFIAPI *AMD_CPM_SMNOR32_FN) (
  IN       VOID                        *This,
  IN       UINT16                      Socket,
  IN       UINT16                      Die,
  IN       UINT16                      Bridge,
  IN       UINT32                      SmnAddr,
  IN       UINT32                      Offset,
  IN       UINT32                      OrData
  );

typedef void (EFIAPI *AMD_CPM_SMNANDTHENOR8_FN) (
  IN       VOID                        *This,
  IN       UINT16                      Socket,
  IN       UINT16                      Die,
  IN       UINT16                      Bridge,
  IN       UINT32                      SmnAddr,
  IN       UINT32                      Offset,
  IN       UINT8                       AndData,
  IN       UINT8                       OrData
  );

typedef void (EFIAPI *AMD_CPM_SMNANDTHENOR16_FN) (
  IN       VOID                        *This,
  IN       UINT16                      Socket,
  IN       UINT16                      Die,
  IN       UINT16                      Bridge,
  IN       UINT32                      SmnAddr,
  IN       UINT32                      Offset,
  IN       UINT16                      AndData,
  IN       UINT16                      OrData
  );

typedef void (EFIAPI *AMD_CPM_SMNANDTHENOR32_FN) (
  IN       VOID                        *This,
  IN       UINT16                      Socket,
  IN       UINT16                      Die,
  IN       UINT16                      Bridge,
  IN       UINT32                      SmnAddr,
  IN       UINT32                      Offset,
  IN       UINT32                      AndData,
  IN       UINT32                      OrData
  );

typedef UINT8 (EFIAPI *AMD_CPM_GETSATAMODE_FN) (
  IN       VOID                        *This
  );

typedef BOOLEAN (EFIAPI *AMD_CPM_DETECTDEVICE_FN) (
  IN       VOID                        *This,
  IN       UINT8                       DeviceId,
     OUT   UINT8                       *Status
  );

typedef BOOLEAN (EFIAPI *AMD_CPM_ISFCHDEVICE_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Device,
  IN       UINT8                       Function
  );

typedef BOOLEAN (EFIAPI *AMD_CPM_ISTHERMALSUPPORT_FN) (
  IN       VOID                        *This
  );

typedef VOID (EFIAPI *AMD_CPM_RELOCATETABLE_FN) (
  IN OUT   VOID                        *TablePtr
  );

typedef VOID (EFIAPI *AMD_CPM_COPYMEM_FN) (
  IN OUT   VOID                        *destination,
  IN       VOID                        *source,
  IN       UINTN                       size
  );

typedef UINT8 (EFIAPI *AMD_CPM_GETSCIMAP_FN) (
  IN       VOID                        *This,
  IN       UINT8                       GeventPin
  );

typedef UINT32 (EFIAPI *AMD_CPM_GETPCIEASLNAME_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Device,
  IN       UINT8                       Function
  );

typedef UINT32 (EFIAPI *AMD_CPM_GETFCHPCIEASLNAME_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Device,
  IN       UINT8                       Function
  );

typedef UINT32 (EFIAPI *AMD_CPM_GETPTBRDEVADDR_FN) (
  IN       VOID                        *This
  );

typedef EFI_STATUS (EFIAPI *AMD_CPM_KBCREAD_FN) (
  IN       UINT16                      BaseAddr,
  IN       UINT8                       Command,
  IN       UINT8                       *Data,
     OUT   UINT8                       *Value
  );

typedef EFI_STATUS (EFIAPI *AMD_CPM_KBCWRITE_FN) (
  IN       UINT16                      BaseAddr,
  IN       UINT8                       Command,
  IN       UINT8                       *Data
  );

typedef UINT8 (EFIAPI *AMD_CPM_GETCPUREVISIONID_FN) (
  IN       VOID                        *This
  );

typedef UINT8 (EFIAPI *AMD_CPM_GETBOOTMODE_FN) (
  );

typedef BOOLEAN (EFIAPI *AMD_CPM_ISRTCWAKEUP_FN) (
  IN       VOID                        *This
  );

typedef VOID (EFIAPI *AMD_CPM_LOADPREINITTABLE_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Stage
  );

typedef AGESA_STATUS (EFIAPI *AMD_CPM_GETPOSTEDVBIOSIMAGE_FN) (
  IN      GFX_VBIOS_IMAGE_INFO         *VbiosImageInfo
  );

typedef VOID (EFIAPI *AMD_CPM_SETSAVECONTEXT_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Offset,
  IN       UINT8                       Data
  );

typedef UINT8 (EFIAPI *AMD_CPM_GETSAVECONTEXT_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Offset
  );

typedef UINT16 (EFIAPI *AMD_CPM_GETACPISMICMD_FN) (
  IN       VOID                        *This
  );

typedef VOID (EFIAPI *AMD_CPM_POWERONDEVICE_FN) (
  IN       VOID                        *This,
  IN       UINT8                       DeviceId,
  IN       UINT8                       State
  );

typedef UINT8 (EFIAPI *AMD_CPM_GETDEVICECONFIG_FN) (
  IN       VOID                        *This,
  IN       UINT8                       DeviceId
  );

typedef UINT32 (EFIAPI *AMD_CPM_GETPCIEENDPOINTDEVICEID_FN) (
  IN       VOID                        *This,
  IN       UINT8                       Device,
  IN       UINT8                       Function
  );

typedef UINT8 (EFIAPI *AMD_CPM_GETMULTIDIEBUSNUMBER_FN) (
  IN       VOID                        *This,
  IN       UINT16                      Socket,
  IN       UINT16                      Die,
  IN       UINT16                      Bridge
  );

typedef UINT32 (EFIAPI *AMD_CPM_EVENTASLNAMECONVERTER_FN) (
  IN       UINT8                       EventPin
  );

/// PT GPIO function
typedef EFI_STATUS (EFIAPI *PTInitialGpioPei) (
  IN       EFI_PEI_SERVICES            **PeiServices,
  IN       VOID                        *PTGpioPtr
  );

/// Write GPIO function
typedef EFI_STATUS (EFIAPI *PTWriteGpioPei) (
  IN       EFI_PEI_SERVICES            **PeiServices,
  IN       UINT8                       Pin,
  IN       UINT8                       Value
  );

/// Read GPIO function
typedef EFI_STATUS (EFIAPI *PTReadGpioPei) (
  IN       EFI_PEI_SERVICES            **PeiServices,
  IN       UINT8                       Pin,
  OUT      UINT8                       Value
  );

typedef EFI_STATUS (EFIAPI *AMD_CPM_ECRAMWRITE_FN) (
  IN       UINT16                      BaseAddr,
  IN       UINT8                       Command,
  IN       UINT8                       *Offset,
  IN       UINT8                       *Data
  );
/// Common Functions for CPM Drivers

typedef struct _AMD_CPM_COMMON_FUNCTION {
  AMD_CPM_IOREAD8_FN                  IoRead8;              ///< Read IO byte
  AMD_CPM_IOREAD16_FN                 IoRead16;             ///< Read IO word
  AMD_CPM_IOREAD32_FN                 IoRead32;             ///< Read IO dword
  AMD_CPM_IOWRITE8_FN                 IoWrite8;             ///< Write IO byte
  AMD_CPM_IOWRITE16_FN                IoWrite16;            ///< Write IO word
  AMD_CPM_IOWRITE32_FN                IoWrite32;            ///< Write IO dword
  AMD_CPM_MMIOREAD8_FN                MmioRead8;            ///< Read memory/MMIO byte
  AMD_CPM_MMIOREAD16_FN               MmioRead16;           ///< Read memory/MMIO word
  AMD_CPM_MMIOREAD32_FN               MmioRead32;           ///< Read memory/MMIO dword
  AMD_CPM_MMIOREAD64_FN               MmioRead64;           ///< Read memory/MMIO qword
  AMD_CPM_MMIOWRITE8_FN               MmioWrite8;           ///< Write memory/MMIO byte
  AMD_CPM_MMIOWRITE16_FN              MmioWrite16;          ///< Write memory/MMIO word
  AMD_CPM_MMIOWRITE32_FN              MmioWrite32;          ///< Write memory/MMIO dword
  AMD_CPM_MMIOWRITE64_FN              MmioWrite64;          ///< Write memory/MMIO qword
  AMD_CPM_MMIOAND8_FN                 MmioAnd8;             ///< Read memory/MMIO byte, perform a bitwise AND
                                                            ///<   and write the result back to memory/MMIO
  AMD_CPM_MMIOAND16_FN                MmioAnd16;            ///< Read memory/MMIO word, perform a bitwise AND
                                                            ///<   and write the result back to memory/MMIO
  AMD_CPM_MMIOAND32_FN                MmioAnd32;            ///< Read memory/MMIO dword, perform a bitwise AND
                                                            ///<   and write the result back to memory/MMIO
  AMD_CPM_MMIOAND64_FN                MmioAnd64;            ///< Read memory/MMIO qword, perform a bitwise AND
                                                            ///<   and write the result back to memory/MMIO
  AMD_CPM_MMIOOR8_FN                  MmioOr8;              ///< Read memory/MMIO byte, perform a bitwise OR
                                                            ///<   and write the result back to memory/MMIO
  AMD_CPM_MMIOOR16_FN                 MmioOr16;             ///< Read memory/MMIO word, perform a bitwise OR
                                                            ///<   and write the result back to memory/MMIO
  AMD_CPM_MMIOOR32_FN                 MmioOr32;             ///< Read memory/MMIO dword, perform a bitwise OR
                                                            ///<   and write the result back to memory/MMIO
  AMD_CPM_MMIOOR64_FN                 MmioOr64;             ///< Read memory/MMIO qword, perform a bitwise OR
                                                            ///<   and write the result back to memory/MMIO
  AMD_CPM_MMIOANDTHENOR8_FN           MmioAndThenOr8;       ///< Read memory/MMIO byte, perform a bitwise AND
                                                            ///<   followed by a bitwise inclusive OR, and writes
                                                            ///<   the result back to memory/MMIO
  AMD_CPM_MMIOANDTHENOR16_FN          MmioAndThenOr16;      ///< Read memory/MMIO word, perform a bitwise AND
                                                            ///<   followed by a bitwise inclusive OR, and writes
                                                            ///<   the result back to memory/MMIO
  AMD_CPM_MMIOANDTHENOR32_FN          MmioAndThenOr32;      ///< Read memory/MMIO dword, perform a bitwise AND
                                                            ///<   followed by a bitwise inclusive OR, and writes
                                                            ///<   the result back to memory/MMIO
  AMD_CPM_MMIOANDTHENOR64_FN          MmioAndThenOr64;      ///< Read memory/MMIO qword, perform a bitwise AND
                                                            ///<   followed by a bitwise inclusive OR, and writes
                                                            ///<   the result back to memory/MMIO
  AMD_CPM_MSRREAD_FN                  MsrRead;              ///< Read MSR register
  AMD_CPM_MSRWRITE_FN                 MsrWrite;             ///< Write MSR register
  AMD_CPM_PCIREAD8_FN                 PciRead8;             ///< Read PCI register byte
  AMD_CPM_PCIREAD16_FN                PciRead16;            ///< Read PCI register word
  AMD_CPM_PCIREAD32_FN                PciRead32;            ///< Read PCI register dword
  AMD_CPM_PCIWRITE8_FN                PciWrite8;            ///< Write PCI register byte
  AMD_CPM_PCIWRITE16_FN               PciWrite16;           ///< Write PCI register word
  AMD_CPM_PCIWRITE32_FN               PciWrite32;           ///< Write PCI register dword
  AMD_CPM_PCIAND8_FN                  PciAnd8;              ///< Read PCI register byte, perform a bitwise AND
                                                            ///<   and write the result back to PCI register
  AMD_CPM_PCIAND16_FN                 PciAnd16;             ///< Read PCI register word, perform a bitwise AND
                                                            ///<   and write the result back to PCI register
  AMD_CPM_PCIAND32_FN                 PciAnd32;             ///< Read PCI register dword, perform a bitwise AND
                                                            ///<   and write the result back to PCI register
  AMD_CPM_PCIOR8_FN                   PciOr8;               ///< Read PCI register byte, perform a bitwise OR
                                                            ///<   and write the result back to PCI register
  AMD_CPM_PCIOR16_FN                  PciOr16;              ///< Read PCI register word, perform a bitwise AND
                                                            ///<   and write the result back to PCI register
  AMD_CPM_PCIOR32_FN                  PciOr32;              ///< Read PCI register dword, perform a bitwise AND
                                                            ///<   and write the result back to PCI register
  AMD_CPM_PCIANDTHENOR8_FN            PciAndThenOr8;        ///< Read PCI register byte, perform a bitwise AND
                                                            ///<   followed by a bitwise inclusive OR, and writes
                                                            ///<   the result back to the PCI register
  AMD_CPM_PCIANDTHENOR16_FN           PciAndThenOr16;       ///< Read PCI register word, perform a bitwise AND
                                                            ///<   followed by a bitwise inclusive OR, and writes
                                                            ///<   the result back to the PCI register
  AMD_CPM_PCIANDTHENOR32_FN           PciAndThenOr32;       ///< Read PCI register dword, perform a bitwise AND
                                                            ///<   followed by a bitwise inclusive OR, and writes
                                                            ///<   the result back to the PCI register
  AMD_CPM_SMNREAD8_FN                 SmnRead8;             ///< Read SMN register dword
  AMD_CPM_SMNREAD16_FN                SmnRead16;            ///< Read SMN register dword
  AMD_CPM_SMNREAD32_FN                SmnRead32;            ///< Read SMN register dword
  AMD_CPM_SMNWRITE8_FN                SmnWrite8;            ///< Write SMN register dword
  AMD_CPM_SMNWRITE16_FN               SmnWrite16;           ///< Write SMN register dword
  AMD_CPM_SMNWRITE32_FN               SmnWrite32;           ///< Write SMN register dword
  AMD_CPM_SMNAND8_FN                  SmnAnd8;              ///< Read SMN register byte, perform a bitwise AND
                                                            ///<   and write the result back to SMN register
  AMD_CPM_SMNAND16_FN                 SmnAnd16;             ///< Read SMN register byte, perform a bitwise AND
                                                            ///<   and write the result back to SMN register
  AMD_CPM_SMNAND32_FN                 SmnAnd32;             ///< Read SMN register byte, perform a bitwise AND
                                                            ///<   and write the result back to SMN register
  AMD_CPM_SMNOR8_FN                   SmnOr8;               ///< Read SMN register byte, perform a bitwise OR
                                                            ///<   and write the result back to SMN register
  AMD_CPM_SMNOR16_FN                  SmnOr16;              ///< Read SMN register byte, perform a bitwise OR
                                                            ///<   and write the result back to SMN register
  AMD_CPM_SMNOR32_FN                  SmnOr32;              ///< Read SMN register byte, perform a bitwise OR
                                                            ///<   and write the result back to SMN register
  AMD_CPM_SMNANDTHENOR8_FN            SmnAndThenOr8;        ///< Read SMN register byte, perform a bitwise AND
                                                            ///<   followed by a bitwise inclusive OR, and writes
                                                            ///<   the result back to the SMN register
  AMD_CPM_SMNANDTHENOR16_FN           SmnAndThenOr16;       ///< Read SMN register byte, perform a bitwise AND
                                                            ///<   followed by a bitwise inclusive OR, and writes
                                                            ///<   the result back to the SMN register
  AMD_CPM_SMNANDTHENOR32_FN           SmnAndThenOr32;       ///< Read SMN register byte, perform a bitwise AND
                                                            ///<   followed by a bitwise inclusive OR, and writes
                                                            ///<   the result back to the SMN register
  AMD_CPM_READTSC_FN                  ReadTsc;              ///< Read TSC
  AMD_CPM_BITSCANFORWARD_FN           BitScanForward;       ///< Find the most right hand side non-zero bit.
  AMD_CPM_BITSCANREVERSE_FN           BitScanReverse;       ///< Find the most left hand side non-zero bit.
  AMD_CPM_CPUIDRAWREAD_FN             CpuidRawRead;         ///< Read CPUID Raw Data
  AMD_CPM_CPUIDREAD_FN                CpuidRead;            ///< Read CPUID
  AMD_CPM_POSTCODE_FN                 PostCode;             ///< Output a post code
  AMD_CPM_CHECKPCIEDEVICE_FN          CheckPcieDevice;      ///< Check whether PCI space exists
  AMD_CPM_CHECKPCIEVGA_FN             CheckPcieVga;         ///< Check whether PCIE VGA device exists
  AMD_CPM_DETECTDEVICE_FN             DetectDevice;         ///< Detect whether the device exists
  AMD_CPM_POWERONDEVICE_FN            PowerOnDevice;        ///< Power on/off device
  AMD_CPM_GETDEVICECONFIG_FN          GetDeviceConfig;      ///< Get the config of device
  AMD_CPM_GETPCIEENDPOINTDEVICEID_FN  GetPcieEndPointDeviceID;  ///< Check whether PCI space exists
  AMD_CPM_GETMULTIDIEBUSNUMBER_FN     GetMultiDieBusNumber; ///< Get Multi-Die Bus Number from AMD_CPM_CORE_TOPOLOGY_TABLE
  AMD_CPM_EVENTASLNAMECONVERTER_FN    EventAslNameConverter;///< Convert Event pin number to Asl name

  AMD_CPM_KBCREAD_FN                  KbcRead;              ///< Read Kbc Register
  AMD_CPM_KBCWRITE_FN                 KbcWrite;             ///< Write Kbc Register

  AMD_CPM_GETRTC_FN                   GetRtc;               ///< Read RTC register
  AMD_CPM_SETRTC_FN                   SetRtc;               ///< Write RTC register
  AMD_CPM_GETACPI_FN                  GetAcpi;              ///< Read ACPI register
  AMD_CPM_SETACPI_FN                  SetAcpi;              ///< Write ACPI register
  AMD_CPM_GETGPIO_FN                  GetGpio;              ///< Get GPIO pin status: 0: Low. 1: High
  AMD_CPM_SETGPIO_FN                  SetGpio;              ///< Set GPIO and IO Mux register
  AMD_CPM_GETGEVENT_FN                GetGevent;            ///< Get GEVENT pin status: 0: Low. 1: High
  AMD_CPM_SETGEVENT_FN                SetGevent;            ///< Set GEVENT register
  AMD_CPM_SETSMICONTROL_FN            SetSmiControl;        ///< Set GEVENT SMI Control Register
  AMD_CPM_SETGEVENTSCITRIG_FN         SetGeventSciTrig;     ///< Set SCI trigger method of GEVENT pin
  AMD_CPM_SETGEVENTSCI_FN             SetGeventSci;         ///< Trigger a GEVENT SCI interrupt
  AMD_CPM_GETSTRAP_FN                 GetStrap;             ///< Get FCH strap status
                                                            ///<   BIT0: IMC
                                                            ///<   BIT1: FCH Internal Clock
                                                            ///<   BIT2: S5+
  AMD_CPM_SETCLKREQ_FN                SetClkReq;            ///< Set FCH ClkReq register
  AMD_CPM_GETCLKREQ_FN                GetClkReq;            ///< Get FCH ClkReq register
  AMD_CPM_STALL_FN                    Stall;                ///< Delay in the unit of 1us
  AMD_CPM_SETFANON_FN                 SetFanOn;             ///< Force FCH FANOUT pin to ON
  AMD_CPM_SETPROCHOT_FN               SetProchot;           ///< Set FCH FANOUT register to emulate PROCHOT
  AMD_CPM_GETSATAMODE_FN              GetSataMode;          ///< Get current mode of SATA controller
  AMD_CPM_ISFCHDEVICE_FN              IsFchDevice;          ///< Is a FCH embedded device
  AMD_CPM_GETSCIMAP_FN                GetSciMap;            ///< Get SciMap value of GEVENT pin

  AMD_CPM_GETCPUREVISIONID_FN         GetCpuRevisionId;     ///< Get CPU revision ID
  AMD_CPM_GETSBTSIADDR_FN             GetSbTsiAddr;         ///< Get the address of SB-TSI register
  AMD_CPM_ISTHERMALSUPPORT_FN         IsThermalSupport;     ///< Is thermal function supported in current CPU or APU
  AMD_CPM_GETPCIEASLNAME_FN           GetPcieAslName;       ///< Get ASL name of PCIE brdige
  AMD_CPM_GETFCHPCIEASLNAME_FN        GetFchPcieAslName;    ///< Get ASL name of Fch PCIE brdige
  AMD_CPM_GETPTBRDEVADDR_FN           GetPtBrDevAddr;       ///< Get Promontory Pcie Bridge Device/Function Address
  AMD_CPM_GETBOOTMODE_FN              GetBootMode;          ///< Get Boot Mode: 0 - S0. 1 - S1. 3 - S3. 4 - S4. 5 - S5
  AMD_CPM_ISRTCWAKEUP_FN              IsRtcWakeup;          ///< Is RTC Wakeup

  AMD_CPM_GETTABLEPTR_FN              GetTablePtr;          ///< Get CPM Table Pointer
  AMD_CPM_GETTABLEPTR_FN              GetTablePtr2;         ///< Get CPM Table Pointer. The table can be re-writable
  AMD_CPM_ADDTABLE_FN                 AddTable;             ///< Add a table in Hob table list
  AMD_CPM_REMOVETABLE_FN              RemoveTable;          ///< Remove a table from Gob table list
  AMD_CPM_SMBUSREAD_FN                ReadSmbus;            ///< Read from a device on SMBUS
  AMD_CPM_SMBUSWRITE_FN               WriteSmbus;           ///< Write to a device on SMBUS
  AMD_CPM_SMBUSREAD_FN                ReadSmbusBlock;       ///< Read from a device on SMBUS in block mode
  AMD_CPM_SMBUSWRITE_FN               WriteSmbusBlock;      ///< Write to a device on SMBUS in block mode
  AMD_CPM_RESETDEVICE_FN              ResetDevice;          ///< Toggle reset pin of a device
  AMD_CPM_RELOCATETABLE_FN            RelocateTable;        ///< Adjust the pointers of CPM table in Hob
  AMD_CPM_COPYMEM_FN                  CopyMem;              ///< Copy a memory block
  AMD_CPM_LOADPREINITTABLE_FN         LoadPreInitTable;     ///< Load AMD_CPM_PRE_INIT_TABLE

  AMD_CPM_ADDSSDTTABLE_FN             AddSsdtTable;         ///< Register one SSDT table
  AMD_CPM_ISAMLOPREGIONOBJECT_FN      IsAmlOpRegionObject;  ///< Is AML Op Region Object

  AMD_CPM_SETSAVECONTEXT_FN           SetSaveContext;       ///< Write the data to Save Context Area
  AMD_CPM_GETSAVECONTEXT_FN           GetSaveContext;       ///< Read the data from Save Context Area
  AMD_CPM_GETACPISMICMD_FN            GetAcpiSmiCmd;        ///< Get ACPI SMI Command Base Register
  AMD_CPM_ECRAMWRITE_FN               EcRamWrite;           ///< Write EC RAM register

} AMD_CPM_COMMON_FUNCTION;

/// CPM Public Functions for platform PEI Driver to use

typedef struct _AMD_CPM_PEIM_PUBLIC_FUNCTION {
  AMD_CPM_SETMEMVOLTAGE_FN            SetMemVoltage;            ///< Set memory voltage
  AMD_CPM_SETVDDPVDDRVOLTAGE_FN       SetVddpVddrVoltage;       ///< Set VDDP/VDDR voltage
  AMD_CPM_PCIERESET_FN                PcieReset;                ///< Toggle PCIE reset pin
  PCIe_COMPLEX_DESCRIPTOR             *PcieComplexDescriptorPtr;///< The pointer of PCIE complex descriptor
  DXIO_COMPLEX_DESCRIPTOR             *DxioComplexDescriptorPtr;///< The pointer of DXIO complex descriptor
} AMD_CPM_PEIM_PUBLIC_FUNCTION;

/// CPM Public Functions for platform DXE Driver to use

typedef struct _AMD_CPM_DXE_PUBLIC_FUNCTION {
  AMD_CPM_GETPOSTEDVBIOSIMAGE_FN      GetPostedVbiosImage;      ///< Get posted VBIOS image
} AMD_CPM_DXE_PUBLIC_FUNCTION;

#endif
