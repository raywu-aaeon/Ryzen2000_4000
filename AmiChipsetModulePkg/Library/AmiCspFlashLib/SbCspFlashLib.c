//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file SbCspFlashLib.c
    South Bridge Chipset Flash Library implementation

*/

#include <Library/BaseLib.h>

#include <Token.h>
#include <Sb.h>
#include <Library/AmiFchIoAccessLib.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------

// GUID Definition(s)

// Protocol/Ppi Definition(s)

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

//Generic Flash part porting hooks

/**
    This function is invoked to do any chipset specific operations 
    that are necessary when enabling the Flash Part for writing

    @param VOID

    @retval VOID

**/
VOID ChipsetFlashDeviceWriteEnable(
    VOID
)
{
    //### RVA9 ###if SB900_EC_SUPPORT
    //### RVA9 ##    //SBLib_PrepareEcForBiosFlashing();
    //### RVA9 ##    SBLib_PutImcToSleep();
    //### RVA9 ###endif
}

/**
    This function is invoked to do any chipset specific operations 
    that are necessary when disabling the Flash Part for writing

    @param VOID

    @retval VOID

**/
VOID ChipsetFlashDeviceWriteDisable(
    VOID
)
{

    //### RVA9 ####if SB900_EC_SUPPORT
    //### RVA9 ###//    SBLib_RestoreEcAfterBiosFlashing();
    //### RVA9 ###    SBLib_WakeUpImc();
    //### RVA9 ####endif
}

#if BIOS_LOCK_ENABLE
/**
    The procedure re-enable the BIOS Write Enable bit before
    Write/Erase procedures if BIOS_LOCK_ENABLE is set. 

    @param SwSmiNum - A S/W SMI number, this value must be 0x20.
    @param Buffer   - A 64bit buffer uses for communicating between
                      caller and this routine.

    @retval VOID

**/

VOID BiosLockEnableSmiFlashHook (
    IN UINT8            SwSmiNum,
    IN OUT UINT64       Buffer
)
{
    if (SwSmiNum != 0x20) return;

/**** PORTING REQUIRED ****
    // Clear BIOSWR_STS
    IoWrite16(PM_BASE_ADDRESS + 0x64, 0x100);
    // Clear TCO_STS
    IoWrite32(PM_BASE_ADDRESS + 0x34, BIT13);
****/

}    
#endif

/**
    This function checks if TopSwap (A16, A17, A18 address lines
    inversion) is on
              
    @param VOID

    @retval TRUE TopSwap is ON
    @retval FALSE TopSwap is OFF

    @note  Intel Chipsets are porting required
**/
BOOLEAN IsTopSwapOn( VOID )
{
  return FALSE;
/*

  volatile UINT8* Address8;

  Address8 = (UINT8 *)(SB_RCBA + SB_BACKED_UP_CONTROL_REGISTER);

  return ((*Address8) & 1) ? TRUE : FALSE;
*/
}

/**
    This function sets TopSwap (A16, A17, A18 address lines 
    inversion) to ON or OFF.

    @param BOOLEAN On - if TRUE, set TopSwap to ON, if FALSE - set to OFF

    @retval VOID

    @note  Intel Chipsets are porting required
**/
VOID  SetTopSwap(
    IN BOOLEAN      On )
{
/*
  volatile UINT8* Address8;

  Address8 = (UINT8 *)(SB_RCBA + SB_BACKED_UP_CONTROL_REGISTER);

  if (On) {
    *Address8 |= 1;
  } else {
    *Address8 &= 0xFE;
  }
*/
}

/**
    Read SPI Descriptor

    @param  SectionSelect     Data written to Flash Descriptor Section Select bits
    @param  SectionIndex      Data written to Flash Descriptor Section Index bits
    @param  *SectionData      Pointer to Flash Descriptor Section Data

    @retval EFI_UNSUPPORTED   This function is not supported
    @retval EFI_SUCCESS       Success to read SPI Descriptor
    @retval EFI_DEVICE_ERROR  Failed to read SPI Descriptor
    @retval EFI_NOT_FOUND     Invalid Flash Valid Signature

**/
EFI_STATUS ReadSpiDescriptor (
    IN UINT8                SectionSelect,
    IN UINT8                SectionIndex,
    OUT UINT32              *SectionData
)
{
/**** PORTING REQUIRED ****
    // Please check the datasheet of the chipset for the register to know
    // how to read SPI Descriptor region.
    // If Descriptor region is not supported by the chip, please return EFI_UNSUPPORTED.

    //
    // Check if it is valid to use hardware sequencing regs
    //
    if ((MmioRead16 (SB_RCBA + SPI_BASE_ADDRESS + R_SB_SPI_HSFS) & B_SB_SPI_HSFS_FDV) == B_SB_SPI_HSFS_FDV) {
      //
      // Check Flash Valid Signature
      //
      MmioAndThenOr32 (
        SB_RCBA + SPI_BASE_ADDRESS + R_SB_SPI_FDOC,
        (UINT32) (~(B_SB_SPI_FDOC_FDSS_MASK | B_SB_SPI_FDOC_FDSI_MASK)),
        (UINT32) (V_SB_SPI_FDOC_FDSS_FSDM | R_SB_SPI_FDBAR_FLVALSIG)
        );
      if ((MmioRead32 (SB_RCBA + SPI_BASE_ADDRESS + R_SB_SPI_FDOD)) == SPI_FDBAR_FLVALSIG) {
        MmioAndThenOr32 (
          SB_RCBA + SPI_BASE_ADDRESS + R_SB_SPI_FDOC,
          (UINT32) (~(B_SB_SPI_FDOC_FDSS_MASK | B_SB_SPI_FDOC_FDSI_MASK)),
          ((UINT32)SectionSelect << 12) | ((UINT32)SectionIndex << 2)
          );
        *SectionData = MmioRead32 (SB_RCBA + SPI_BASE_ADDRESS + R_SB_SPI_FDOD);
        return EFI_SUCCESS;
      } else {
        return EFI_NOT_FOUND;
      }
    } else {
      return EFI_DEVICE_ERROR;
    }
**** PORTING REQUIRED ****/
	// AMD SPI controller didn't provide SPI Descriptor and just return EFI_UNSUPPORTED for this routine.
	// 	RVA9 : Check Sandstone-FCH later.
    return EFI_UNSUPPORTED;
}

/**
    Get the SPI region base, based on the enum type.
        
    @param RegionType - Region type to query for the base address
    @param LimitAddress - This address is left shifted by 12 bits to 
                          represent bits 26:12 for the Region 'n' Limit.
    @param BaseAddress - This address is left shifted by 12 bits to 
                         represent bits 26:12 for the Region 'n' Base.

    @retval EFI_SUCCESS - Read success
            EFI_INVALID_PARAMETER - Invalid region type given

**/
/*
EFI_STATUS
EFIAPI
GetSpiRegionAddresses (
  IN   AMI_PCH_SPI_REGION_TYPE  RegionType,
  OUT  UINT32                   *LimitAddress,
  OUT  UINT32                   *BaseAddress
  )
{
    BOOLEAN               AdjustRange;
    UINTN                 RegionTypeReg;
    UINT32                ReadValue;
    UINT32                RegionRangeBase;

    if (!((RegionType >= AmiUndefinedType) && (RegionType <= AmiTxeType))) {
      return EFI_INVALID_PARAMETER;
    }

    AdjustRange = FALSE;

    if (RegionType == AmiUndefinedType) {
      return EFI_SUCCESS;
    } else if (RegionType == AmiDescriptorType) {
      RegionTypeReg = R_SB_SPI_FREG0_FLASHD;
    } else if (RegionType == AmiBiosType) {
      AdjustRange = TRUE;
      RegionTypeReg = R_SB_SPI_FREG1_BIOS;
    } else if (RegionType == AmiTxeType) {
      RegionTypeReg = R_SB_SPI_FREG2_SEC;
    }

    ReadValue = MmioRead32 (SPI_BASE_ADDRESS + RegionTypeReg);
    RegionRangeBase  = (ReadValue & B_SB_SPI_FREGX_BASE_MASK) << 12;

    if (AdjustRange == TRUE) {
      *LimitAddress += RegionRangeBase;
      *BaseAddress  += RegionRangeBase;
    } else {
      *LimitAddress = (ReadValue & B_SB_SPI_FREGX_LIMIT_MASK) >> 4;
      *BaseAddress  = RegionRangeBase;
    }
    
    return EFI_SUCCESS;
}
*/

/**
    Get total Flash ROM size by reading SPI Descriptor.
        
    @param VOID

    @return Flash ROM Size

**/
/*
UINT32 GetTotalFlashRomSize ( VOID )
{
    UINT32  TotalRomSize = 0;
    UINT32  CtrlData;
    UINT8   NumSpi = 0;

    //
    // Select to Flash Map 0 Register to get the number of flash Component
    //
    CtrlData = MmioRead32((SPI_BASE_ADDRESS + R_SB_SPI_FDOC));
    CtrlData &= (UINT32)(~(B_SB_SPI_FDOC_FDSS_MASK | B_SB_SPI_FDOC_FDSI_MASK));
    CtrlData |= (UINT32)(V_SB_SPI_FDOC_FDSS_FSDM | R_SB_SPI_FDBAR_FLASH_MAP0);
    MmioWrite32((SPI_BASE_ADDRESS + R_SB_SPI_FDOC), CtrlData);

    switch ( MmioRead16 (SPI_BASE_ADDRESS + R_SB_SPI_FDOD) & B_SB_SPI_FDBAR_NC ) {
        case V_SB_SPI_FDBAR_NC_1:
            NumSpi = 1;
            break;
        case V_SB_SPI_FDBAR_NC_2:
            NumSpi = 2;
            break;
        default:
            break;
    }

    if (NumSpi == 0) return TotalRomSize;

    //
    // Select to Flash Components Register to get the Component 1 Density
    //
    CtrlData = MmioRead32((SPI_BASE_ADDRESS + R_SB_SPI_FDOC));
    CtrlData &= (UINT32)(~(B_SB_SPI_FDOC_FDSS_MASK | B_SB_SPI_FDOC_FDSI_MASK));
    CtrlData |= (UINT32)(V_SB_SPI_FDOC_FDSS_COMP | R_SB_SPI_FCBA_FLCOMP);
    MmioWrite32((SPI_BASE_ADDRESS + R_SB_SPI_FDOC), CtrlData);

    //
    //  Get Component 1 Density
    //
    switch ( (UINT8) MmioRead32 (SPI_BASE_ADDRESS + R_SB_SPI_FDOD) & B_SB_SPI_FLCOMP_COMP1_MASK ) {
        case V_SB_SPI_FLCOMP_COMP1_512KB:
            TotalRomSize += (UINT32) (512 << KBShift);
            break;
        case V_SB_SPI_FLCOMP_COMP1_1MB:
            TotalRomSize += (UINT32) (1 << MBShift);
            break;
        case V_SB_SPI_FLCOMP_COMP1_2MB:
            TotalRomSize += (UINT32) (2 << MBShift);
            break;
        case V_SB_SPI_FLCOMP_COMP1_4MB:
            TotalRomSize += (UINT32) (4 << MBShift);
            break;
        case V_SB_SPI_FLCOMP_COMP1_8MB:
            TotalRomSize += (UINT32) (8 << MBShift);
            break;
        case V_SB_SPI_FLCOMP_COMP1_16MB:
            TotalRomSize += (UINT32) (16 << MBShift);
            break;
        default:
            break;
    } // end of switch

    //
    // Get Component 2 Density
    //
    if (NumSpi == 2) {
        switch ( (UINT8) MmioRead32 (SPI_BASE_ADDRESS + R_SB_SPI_FDOD) & B_SB_SPI_FLCOMP_COMP2_MASK ) {
            case V_SB_SPI_FLCOMP_COMP2_512KB:
                TotalRomSize += (UINT32) (512 << KBShift);
                break;
            case V_SB_SPI_FLCOMP_COMP2_1MB:
                TotalRomSize += (UINT32) (1 << MBShift);
                break;
            case V_SB_SPI_FLCOMP_COMP2_2MB:
                TotalRomSize += (UINT32) (2 << MBShift);
                break;
            case V_SB_SPI_FLCOMP_COMP2_4MB:
                TotalRomSize += (UINT32) (4 << MBShift);
                break;
            case V_SB_SPI_FLCOMP_COMP2_8MB:
                TotalRomSize += (UINT32) (8 << MBShift);
                break;
            case V_SB_SPI_FLCOMP_COMP2_16MB:
                TotalRomSize += (UINT32) (16 << MBShift);
                break;
            default:
                break;
        } // end of switch
    }// end of if

    return TotalRomSize;
}
*/

/**
    This routine provides H/W read/write-protection of the BIOS region.
    If chipset supports "SPI Flash Protected Range Registers", then program
    them to protect BIOS region in SPI Flash.
        
    @param VOID

    @retval EFI_STATUS
            EFI_SUCCESS - Set successfully.
            EFI_INVALID_PARAMETER - The parameter of input is invalid
            EFI_UNSUPPORTED - Chipset or H/W is not supported.

    Note:   Porting required

**/
EFI_STATUS SbFlashProtectedRange ( VOID )
{
    return EFI_UNSUPPORTED;
/*
    AMI_SPI_PROTECTED_RANGE_CONIFG  SpiProtectedRange[] = { SPI_PROTECTED_RANGE_0,
                                                            SPI_PROTECTED_RANGE_1,
                                                            SPI_PROTECTED_RANGE_2,
                                                            SPI_PROTECTED_RANGE_3,
                                                            SPI_PROTECTED_RANGE_4 };
    AMI_PCH_SPI_REGION_TYPE         AmiSpiRegionType;
    BOOLEAN                         WriteProtectionEnable;
    BOOLEAN                         ReadProtectionEnable;
    UINT32                          ProtectedRangeBase;
    UINT32                          ProtectedRangeLimit;
    UINT32                          RegIndex;
    UINT32                          TotalRomSize;
    volatile UINT32                 Value32;

    //
    // Get Total ROM size first
    //
    TotalRomSize = GetTotalFlashRomSize();

    if (TotalRomSize == 0) return EFI_INVALID_PARAMETER;

    //
    // Program Protected Range Registers per SPI_PROTECTED_RANGE_X tokens
    //
    for (RegIndex = 0; RegIndex < 5; RegIndex++) {
      AmiSpiRegionType      = SpiProtectedRange[RegIndex].AmiPchSpiRegionType;
      WriteProtectionEnable = SpiProtectedRange[RegIndex].WriteProtectionEnable;
      ReadProtectionEnable  = SpiProtectedRange[RegIndex].ReadProtectionEnable;
      ProtectedRangeBase    = SpiProtectedRange[RegIndex].ProtectedRangeBase;
      ProtectedRangeLimit   = SpiProtectedRange[RegIndex].ProtectedRangeBase + SpiProtectedRange[RegIndex].ProtectedRangeLength - 1;
      
      if ((WriteProtectionEnable == 0) && (ReadProtectionEnable == 0)) continue;
      
      //
      // Get RangeBase and RangeLimit per SpiRegion
      //
      GetSpiRegionAddresses (AmiSpiRegionType, &ProtectedRangeBase, &ProtectedRangeLimit);
      //
      // Exceed the address of protected range base.
      //
      if (ProtectedRangeBase >= TotalRomSize) continue;
      //
      // Exceed the address of protected range limit.
      //
      if (ProtectedRangeLimit >= TotalRomSize) continue;

      Value32 = *(UINT32 *)(SPI_BASE_ADDRESS + R_SB_SPI_PR0 + (RegIndex * 4));
      if (Value32 == 0) {
        Value32 = (ProtectedRangeBase & 0x1FFF000) >> 12;
        Value32 += ((ProtectedRangeLimit & 0x1FFF000) << 4);
        if (ReadProtectionEnable) Value32 |= B_SB_SPI_PRx_RPE;
        if (WriteProtectionEnable) Value32 |= B_SB_SPI_PRx_WPE;
        *(UINT32 *)(SPI_BASE_ADDRESS + R_SB_SPI_PR0 + (RegIndex * 4)) = Value32;
      } // if register is not use yet
    } // for loop

    return EFI_SUCCESS;
*/    
}

UINT8   gPowerState=0;
/**
    Disable Power Button SMI when AFU.

    @param VOID

    @retval VOID

    @retval VOID

**/
VOID ChipsetDisablePowerButton(VOID)
{
    // Disable PWR Button SMI
    UINT8 Data;

    Data = AmdFchMmioRead8(AMD_FCH_SMI_MMIO, FCH_SMI_REGAC);
    gPowerState = Data & (BIT6+BIT7);

    Data &= ~(BIT6+BIT7); // Disable PBtn
    AmdFchMmioWrite8(AMD_FCH_SMI_MMIO, FCH_SMI_REGAC,Data); ;

}
/**
    Re-Enable PowerButton after flash BIOS

    @param VOID

    @retval VOID

    @retval VOID

**/
VOID ChipsetEnablePowerButton (VOID)
{
    UINT8 Data;

    //Clear the Power button status
    while (AmdFchMmioRead8(AMD_FCH_SMI_MMIO, FCH_SMI_REG84 + 2) & BIT3)
    {
        AmdFchMmioAndThenOr8(AMD_FCH_SMI_MMIO, FCH_SMI_REG84 + 2, ~0, BIT3);
    }

    Data = AmdFchMmioRead8(AMD_FCH_SMI_MMIO, FCH_SMI_REGAC);
    Data |= gPowerState; // Enable PBtn
    AmdFchMmioWrite8(AMD_FCH_SMI_MMIO, FCH_SMI_REGAC, Data); ;
}


//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
