/* $NoKeywords:$ */
/**
 * @file
 *
 * FCH DXE Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project   SMM Control DXE Driver
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 10:28:05 -0800 (Tue, 09 Dec 2014) $
 *
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
 */

#include "SmmControl.h"
#define FILECODE UEFI_DXE_SMMCONTROL_SMMCONTROL_FILECODE


#define MemRead32(x)  MmioRead32(x)
#define MemWrite32(x, y) MmioWrite32(x, y)
#define FCH_SMI_DUMMY_IO_VALUE   0x55

UINT32                           mAcpiMmioBase;
UINT16                           mAcpiPmBase;
UINT8                            mAcpiSmiCmd;
UINT32                           mPspMmioBase;
EFI_PHYSICAL_ADDRESS             mPspMmioBase64;
EFI_PHYSICAL_ADDRESS             mAcpiMmioBase64;
STATIC EFI_SMM_CONTROL2_PROTOCOL mSmmControl;
EFI_EVENT                        mVirtualAddressChangeEvent = NULL;


#define NBMSIC_SMN_BASE                     0x13B10000ul           ///< Define the SMN Base address for NB MISC register
#define NBMSIC_PSP_BASE_ADDR_LO_OFFSET      0x2E0                  ///< Define the offset of PSP_BASE_ADDR_LO in NB MISC block
#define NB_SMN_INDEX_2_PCI_ADDR (MAKE_SBDFO (0, 0, 0, 0, 0xB8))  ///< PCI Addr of NB_SMN_INDEX_2
#define NB_SMN_DATA_2_PCI_ADDR (MAKE_SBDFO (0, 0, 0, 0, 0xBC))  ///< PCI Addr of NB_SMN_DATA_2
#define PSP_BAR_SIZE                        0x100000ul             ///< Size of PSP BAR
#define C2P_REG_OFFSET                      0x10500ul              ///< BIOS to PSP mailbox Register SMN offset
#define BIOS_MUTEX_OFFSET    (23 * 4)       ///< BIOS mutex: BIOS sets this to non-zero requesting the mutex; clears this register when releases the mutex;
#define PSP_MUTEX_OFFSET     (24 * 4)       ///< PSP sets this to non-zero requesting the mutex; clears this register when releases the mutex;
#define MUTEX_TURN_OFFSET    (25 * 4)       ///< Turn registers as it is: BIOS sets this to 1 when requests the mutes; PSP sets it to 0 when PSP requests the mutex

/**
  Return the PspMMIO MMIO location

  @param[in] PspMmioBase Pointer to Psp MMIO address

  @retval BOOLEAN  0: Error, 1 Success
**/
BOOLEAN
GetPspMmioBase (
  IN OUT   UINT32 *PspMmioBase
  )
{
  UINT32    Value32;
  UINTN     PciAddress;
  UINT32    SmnBase;

  *PspMmioBase = 0;

  SmnBase = NBMSIC_SMN_BASE;

  PciAddress = NB_SMN_INDEX_2_PCI_ADDR;
  Value32 = SmnBase + NBMSIC_PSP_BASE_ADDR_LO_OFFSET;
  PciWrite32 (PciAddress, Value32);
  PciAddress = NB_SMN_DATA_2_PCI_ADDR;
  Value32 = PciRead32 (PciAddress);
  //Mask out the lower bits
  Value32 &= 0xFFF00000;

  if (Value32 == 0) {
    return (FALSE);
  }

  *PspMmioBase = Value32;
  return (TRUE);
}

/**
 * Acquire the Mutex for access PSP,X86 co-accessed register
 * Call this routine before access SMIx98 & SMIxA8
 *
 */
VOID
AcquirePspSmiRegMutexV2 (
  VOID
  )
{
  EFI_PHYSICAL_ADDRESS BiosMutex;
  EFI_PHYSICAL_ADDRESS PspMutex;
  EFI_PHYSICAL_ADDRESS Turn;

  if (mPspMmioBase64 != 0) {
    BiosMutex = mPspMmioBase64 + C2P_REG_OFFSET + BIOS_MUTEX_OFFSET;
    PspMutex = mPspMmioBase64 + C2P_REG_OFFSET + PSP_MUTEX_OFFSET;
    Turn = mPspMmioBase64 + C2P_REG_OFFSET + MUTEX_TURN_OFFSET;
    *(volatile UINT32*)(UINTN)(BiosMutex) = 1;
    *(volatile UINT32*)(UINTN)(Turn) = 1;
    //Wait till PSP FW release the mutex
    while ((*(volatile UINT32*)(UINTN)(PspMutex) == 1) && (*(volatile UINT32*)(UINTN)(Turn) == 1)) {
      ;
    }
  }
}
/**
 * Release the Mutex for access PSP,X86 co-accessed register
 * Call this routine after access SMIx98 & SMIxA8
 *
 */
VOID
ReleasePspSmiRegMutexV2 (
  VOID
  )
{
  EFI_PHYSICAL_ADDRESS BiosMutex;

  if (mPspMmioBase64 != 0) {
    BiosMutex = mPspMmioBase64 + C2P_REG_OFFSET + BIOS_MUTEX_OFFSET;
    *(volatile UINT32*)(UINTN)(BiosMutex) = 0;
  }
}

EFI_STATUS
SmmControlDxePreInit (
  IN       EFI_HANDLE              ImageHandle
  )
{
  UINT16              SmmControlData16;
  UINT16              SmmControlMask16;
  UINT32              SmmControlData32;
  UINT8               SmmControlData8;
  UINT8               i;
  EFI_HANDLE          mDriverImageHandle;
  EFI_STATUS          Status;
  UINT64              Length;
  UINT64              Attributes;
  EFI_GCD_MEMORY_SPACE_DESCRIPTOR GcdMemorySpaceDescriptor;

  //
  // Enable ACPI MMIO space
  //
  LibFchIndirectIoRead (EfiPciWidthUint8, FCH_IOMAP_REGCD6, FCH_PMIOA_REG04, &SmmControlData8);
  SmmControlData8 |= BIT1;
  LibFchIndirectIoWrite (EfiPciWidthUint8, FCH_IOMAP_REGCD6, FCH_PMIOA_REG04, &SmmControlData8);

  //
  // Get ACPI MMIO base and AcpiPm1EvtBlk address
  //
  LibFchGetAcpiMmioBase (&mAcpiMmioBase);
  LibFchGetAcpiPmBase (&mAcpiPmBase);
  LibFchIndirectIoRead (EfiPciWidthUint8, FCH_IOMAP_REGCD6, FCH_PMIOA_REG6A, &mAcpiSmiCmd);

  if ((0 == mAcpiMmioBase) || (0 == mAcpiPmBase)) {
    return EFI_LOAD_ERROR;
  }

  mAcpiMmioBase64 = (EFI_PHYSICAL_ADDRESS) mAcpiMmioBase;
  Length = 0x1000;
  mDriverImageHandle = ImageHandle;

  // Attempt to Add and Allocate the memory region for mAcpiMmioBase
  Status = gDS->GetMemorySpaceDescriptor (mAcpiMmioBase, &GcdMemorySpaceDescriptor);
  if (!EFI_ERROR (Status)) {
    if (GcdMemorySpaceDescriptor.GcdMemoryType == EfiGcdMemoryTypeNonExistent) {
      Status = gDS->AddMemorySpace (
                      EfiGcdMemoryTypeMemoryMappedIo,
                      mAcpiMmioBase64,
                      Length,
                      EFI_MEMORY_RUNTIME | EFI_MEMORY_UC
                      );
      if (!EFI_ERROR (Status)) {
        Status = gDS->AllocateMemorySpace (
                        EfiGcdAllocateAddress,
                        EfiGcdMemoryTypeMemoryMappedIo,
                        12,
                        Length,
                        &mAcpiMmioBase64,
                        mDriverImageHandle,
                        NULL
                        );
        if (!EFI_ERROR (Status)) {
          Status = gDS->GetMemorySpaceDescriptor (mAcpiMmioBase64, &GcdMemorySpaceDescriptor);
        }
      }
    }
  }
  // Attempt to set runtime attribute
  if (!EFI_ERROR (Status)) {
    if (GcdMemorySpaceDescriptor.GcdMemoryType == EfiGcdMemoryTypeMemoryMappedIo) {
      Attributes = GcdMemorySpaceDescriptor.Attributes | EFI_MEMORY_RUNTIME | EFI_MEMORY_UC;
      Status = gDS->SetMemorySpaceAttributes (
                      mAcpiMmioBase,
                      Length,
                      Attributes
                      );
    }
  }
  // Failed to Allocate MMIO region as Runtime
  if (EFI_ERROR (Status)) {
    return (EFI_OUT_OF_RESOURCES);
  }

  // Get MMIO address for PSP Base for mutex control
  mPspMmioBase = 0;
  GetPspMmioBase (&mPspMmioBase);
  ASSERT (mPspMmioBase != 0);
  if (0 == mPspMmioBase) {
    return EFI_LOAD_ERROR;
  }
  //mPspMmioBase64 will convert to virtual address when VirtualAddress event triggers
  mPspMmioBase64 = mPspMmioBase;
  Length = PSP_BAR_SIZE;
  // Attempt to Add and Allocate the memory region for mPspMmioBase
  Status = gDS->GetMemorySpaceDescriptor (mPspMmioBase, &GcdMemorySpaceDescriptor);
  if (!EFI_ERROR (Status)) {
    if (GcdMemorySpaceDescriptor.GcdMemoryType == EfiGcdMemoryTypeNonExistent) {
      Status = gDS->AddMemorySpace (
                      EfiGcdMemoryTypeMemoryMappedIo,
                      mPspMmioBase64,
                      Length,
                      EFI_MEMORY_RUNTIME | EFI_MEMORY_UC
                      );
      if (!EFI_ERROR (Status)) {
        Status = gDS->AllocateMemorySpace (
                        EfiGcdAllocateAddress,
                        EfiGcdMemoryTypeMemoryMappedIo,
                        12,
                        Length,
                        &mPspMmioBase64,
                        mDriverImageHandle,
                        NULL
                        );
        if (!EFI_ERROR (Status)) {
          Status = gDS->GetMemorySpaceDescriptor (mPspMmioBase64, &GcdMemorySpaceDescriptor);
        }
      }
    }
  }
  // Attempt to set runtime attribute
  if (!EFI_ERROR (Status)) {
    if (GcdMemorySpaceDescriptor.GcdMemoryType == EfiGcdMemoryTypeMemoryMappedIo) {
      Attributes = GcdMemorySpaceDescriptor.Attributes | EFI_MEMORY_RUNTIME | EFI_MEMORY_UC;
      Status = gDS->SetMemorySpaceAttributes (
                      mPspMmioBase,
                      Length,
                      Attributes
                      );
    }
  }
  // Failed to Allocate MMIO region as Runtime
  if (EFI_ERROR (Status)) {
    return (EFI_OUT_OF_RESOURCES);
  }
  //
  // Clean up all SMI status and enable bits
  //
  // Clear all SmiControl registers
  SmmControlData32 = 0;
  for (i = FCH_SMI_REGA0; i <= FCH_SMI_REGC4; i += 4) {
    LibFchMemWrite (EfiPciWidthUint32, mAcpiMmioBase + SMI_BASE + i, &SmmControlData32);
  }

  // Clear all SmiStatus registers (SmiStatus0-4)
  SmmControlData32 = 0xFFFFFFFF;
  LibFchMemWrite (EfiPciWidthUint32, mAcpiMmioBase + SMI_BASE + FCH_SMI_REG80, &SmmControlData32);
  LibFchMemWrite (EfiPciWidthUint32, mAcpiMmioBase + SMI_BASE + FCH_SMI_REG84, &SmmControlData32);
  LibFchMemWrite (EfiPciWidthUint32, mAcpiMmioBase + SMI_BASE + FCH_SMI_REG88, &SmmControlData32);
  LibFchMemWrite (EfiPciWidthUint32, mAcpiMmioBase + SMI_BASE + FCH_SMI_REG8C, &SmmControlData32);
  LibFchMemWrite (EfiPciWidthUint32, mAcpiMmioBase + SMI_BASE + FCH_SMI_REG90, &SmmControlData32);

  // Clear SciSmiEn and SciSmiSts
  SmmControlData32 = 0xFFFFFFFF;
  LibFchMemWrite (EfiPciWidthUint32, mAcpiMmioBase + SMI_BASE + FCH_SMI_REG10, &SmmControlData32);
  SmmControlData32 = 0;
  LibFchMemWrite (EfiPciWidthUint32, mAcpiMmioBase + SMI_BASE + FCH_SMI_REG14, &SmmControlData32);

  //
  // If SCI is not enabled, clean up all ACPI PM status/enable registers
  //
  LibFchIoRead (EfiPciWidthUint16, mAcpiPmBase + R_FCH_ACPI_PM_CONTROL, &SmmControlData16);
  if (! (SmmControlData16 & BIT0)) {
    // Clear WAKE_EN, RTC_EN, SLPBTN_EN, PWRBTN_EN, GBL_EN and TMR_EN
    SmmControlData16 = 0;
    SmmControlMask16 = (UINT16)~(BIT15 + BIT10 + BIT9 + BIT8 + BIT5 + BIT0);
    LibFchIoRw (EfiPciWidthUint16, mAcpiPmBase + R_FCH_ACPI_PM1_ENABLE, &SmmControlMask16, &SmmControlData16);

    // Clear WAKE_STS, RTC_STS, SLPBTN_STS, PWRBTN_STS, GBL_STS and TMR_STS
    SmmControlData16 = BIT15 + BIT10 + BIT9 + BIT8 + BIT5 + BIT0;
    LibFchIoWrite (EfiPciWidthUint16, mAcpiPmBase + R_FCH_ACPI_PM1_STATUS, &SmmControlData16);

    // Clear SLP_TYPx
    SmmControlData16 = 0;
    SmmControlMask16 = (UINT16)~(BIT12 + BIT11 + BIT10);
    LibFchIoRw (EfiPciWidthUint16, mAcpiPmBase + R_FCH_ACPI_PM_CONTROL, &SmmControlMask16, &SmmControlData16);

    // Clear GPE0 Enable Register
    SmmControlData32 = 0;
    LibFchIoWrite (EfiPciWidthUint32, mAcpiPmBase + R_FCH_ACPI_EVENT_ENABLE, &SmmControlData32);

    // Clear GPE0 Status Register
    SmmControlData32 = 0xFFFFFFFF;
    LibFchIoWrite (EfiPciWidthUint32, mAcpiPmBase + R_FCH_ACPI_EVENT_STATUS, &SmmControlData32);
  }

  //
  // Set the EOS Bit
  // Clear SmiEnB to enable SMI function
  //
  AcquirePspSmiRegMutexV2 ();
  SmmControlData32 = MemRead32 (mAcpiMmioBase64 + SMI_BASE + FCH_SMI_REG98);
  SmmControlData32 |= BIT28;
  SmmControlData32 &= ~BIT31;
  MemWrite32 (mAcpiMmioBase64 + SMI_BASE + FCH_SMI_REG98, SmmControlData32);
  ReleasePspSmiRegMutexV2 ();
  return EFI_SUCCESS;
}


EFI_STATUS
ClearSmi (
  VOID
  )
{
  UINT32              SmmControlData32;

  //
  // Clear SmiCmdPort Status Bit
  //
  SmmControlData32 = BIT11;
  MemWrite32 (mAcpiMmioBase64 + SMI_BASE + FCH_SMI_REG88, SmmControlData32);

  //
  // Set the EOS Bit if it is currently cleared so we can get an SMI otherwise
  // leave the register alone
  //
  AcquirePspSmiRegMutexV2 ();
  SmmControlData32 = MemRead32 (mAcpiMmioBase64 + SMI_BASE + FCH_SMI_REG98);
  if ((SmmControlData32 & BIT28) == 0) {
    SmmControlData32 |= BIT28;
    MemWrite32 (mAcpiMmioBase64 + SMI_BASE + FCH_SMI_REG98, SmmControlData32);
  }
  ReleasePspSmiRegMutexV2 ();

  return EFI_SUCCESS;
}




// Invoke SMI activation from either preboot or runtime environment
EFI_STATUS
EFIAPI
AmdTrigger (
  IN       CONST EFI_SMM_CONTROL2_PROTOCOL                *This,
  IN OUT   UINT8                      *CommandPort        OPTIONAL,
  IN OUT   UINT8                      *DataPort           OPTIONAL,
  IN       BOOLEAN                    Periodic            OPTIONAL,
  IN       UINTN                      ActivationInterval  OPTIONAL
  )
{
  UINT8                bIndex;
  UINT8                bData;
  UINT32               SmmControlData32;
  UINT8                bIrqMask;
  UINT8                bIrqMask1;

  if (Periodic) {
    return EFI_INVALID_PARAMETER;
  }
  if (NULL == CommandPort) {
    bIndex = 0xff;
  } else {
    bIndex = *CommandPort;
  }
  if (NULL == DataPort) {
    bData  = 0xff;
  } else {
    bData  = *DataPort;
  }

  //
  // Enable CmdPort SMI
  //
  SmmControlData32 = MemRead32 (mAcpiMmioBase64 + SMI_BASE + FCH_SMI_REGB0);
  SmmControlData32 &= ~(BIT22 + BIT23);
  SmmControlData32 |= BIT22;
  MemWrite32 (mAcpiMmioBase64 + SMI_BASE + FCH_SMI_REGB0, SmmControlData32);
 
  // Temporal WA-Ensure IRQ0 is masked off when entering software SMI
  bIrqMask = IoRead8 (FCH_8259_MASK_REG_MASTER);
  if ((bIrqMask & BIT0) == 0) {
    bIrqMask1 = bIrqMask | BIT0;
    IoWrite8 (FCH_8259_MASK_REG_MASTER, bIrqMask1);
  }
  //-WA

  // Removing ClearSmi to fix false and missing SMI issue
  //
  // Issue command port SMI
  //
  IoWrite16 (mAcpiSmiCmd, (bData << 8) + bIndex);
  //
  // Removing ClearSmi to fix false and missing SMI issue
  //
  //Port 80-UEFI Shell
 // IoWrite8 (FCH_IOMAP_REG80, FCH_SMI_DUMMY_IO_VALUE);
 //Port 80-UEFI Shell
 

  // WA-Restore IRQ0 mask if needed
  if ((bIrqMask & BIT0) == 0) {
    IoWrite8 (FCH_8259_MASK_REG_MASTER, bIrqMask);
  }
  //-WA
  return EFI_SUCCESS;
}


// Clear any system state that was created in response to the Trigger call
EFI_STATUS
EFIAPI
AmdClear (
  IN       CONST EFI_SMM_CONTROL2_PROTOCOL *This,
  IN       BOOLEAN                         Periodic OPTIONAL
  )
{
  if (Periodic) {
    return EFI_INVALID_PARAMETER;
  }

  return ClearSmi ();
}


//
// FUNCTION NAME.
//      VariableVirtualAddressChangeCallBack - Call back function for Virtual Address Change Event.
//
// FUNCTIONAL DESCRIPTION.
//      This function convert the virtual addreess to support runtime access.
//
// ENTRY PARAMETERS.
//      Event           - virtual Address Change Event.
//      Context         - virtual Address Change call back Context.
//
// EXIT PARAMETERS.
//      None.
//
// WARNINGS.
//      None.
//

VOID
EFIAPI
VariableVirtualAddressChangeCallBack (
  IN EFI_EVENT Event,
  IN VOID *Context
  )
{

  EfiConvertPointer (0, (VOID **) &mAcpiMmioBase64);
  EfiConvertPointer (0, (VOID *) &(mSmmControl.Trigger));
  EfiConvertPointer (0, (VOID *) &(mSmmControl.Clear));
  EfiConvertPointer (0, (VOID **) &mPspMmioBase64);

  return;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Name: AmdInstallSmmControl
 *
 * This DXE driver produces the SMM Control Protocol
 *
 * @param[in]    ImageHandle     Pointer to the image handle
 * @param[in]    SystemTable     Pointer to the EFI system table
 *
 * @retval       EFI_SUCCESS     Driver initialized successfully
 * @retval       EFI_ERROR       Driver initialization failed
 *
 */
/*----------------------------------------------------------------------------------------*/
EFI_STATUS
AmdInstallSmmControl (
  IN       EFI_HANDLE              ImageHandle,
  IN       EFI_SYSTEM_TABLE        *SystemTable
  )
{
  EFI_STATUS                       Status;

  //
  // Initialize EFI library
  //
  Status = SmmControlDxePreInit (ImageHandle);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  VariableVirtualAddressChangeCallBack,
                  NULL,
                  &gEfiEventVirtualAddressChangeGuid,
                  &mVirtualAddressChangeEvent
                  );
  ASSERT_EFI_ERROR (Status);

  mSmmControl.Trigger              = AmdTrigger;
  mSmmControl.Clear                = AmdClear;
  mSmmControl.MinimumTriggerPeriod = 0;

  //
  // Finally install the protocol
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiSmmControl2ProtocolGuid,
                  &mSmmControl,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}


