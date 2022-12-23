//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

//*************************************************************************
/** @file SbResetLib.c
    This file contains code for SbResetLib.c
    in the DXE stage.

**/
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

// UDK Header
#include <PiDxe.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/PciLib.h>
#include <Library/S3PciLib.h>
#include <AmiChipsetIoLib.h>
#include <Library/RtcLib.h>
#include <Guid/Rtc.h> //### TBD

#include <Library/DebugLib.h>

#include <Token.h>
// AMI Compatibility Header.
#include <AmiCspLib.h> // Optional. should use Mde Library instead.
#include <AmiLib.h>
#include <SbElinks.h>

// Produced Protocols

// Consumed Protocols

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

static BOOLEAN IsFchFullHardReset;
#if HW_REDUCE_ACDCTIMER_SUPPORT
static BOOLEAN IsHwReduceSystem;
#endif
// Macro Definition(s)

// Type Definition(s)
typedef VOID (SB_OEM_S3_WARMRESET_CALLBACK) (VOID);

// Function Prototype(s)
BOOLEAN
SbGetCapsuleFlag (
  );

VOID ShutdownUsbLegacy(VOID);

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)
extern SB_OEM_S3_WARMRESET_CALLBACK \
                                 SB_OEM_S3_WARMRESET_CALLBACK_LIST EndOfList;
SB_OEM_S3_WARMRESET_CALLBACK* SbS3InsteadOfWarmResetCallBackList[] = \
                                 {SB_OEM_S3_WARMRESET_CALLBACK_LIST NULL};

// Function Definition(s)

//---------------------------------------------------------------------------

/**
    This function calls registered callbacks for S3 RTC/Timer
    (WarmBoot) eLink.

    @param VOID

    @retval VOID
**/

VOID SBLib_S3InsteadOfWarmResetCallBack (VOID)
{
    UINTN   i;

    for (i = 0; SbS3InsteadOfWarmResetCallBackList[i] != NULL; i++)
        SbS3InsteadOfWarmResetCallBackList[i]();
}


/**
    This function puts system into ACPI S3 State.
    if token ENABLE_RTC_ONE_SECOND_WAKEUP = 1, then it setups RTC
    1 second alarm as well.

    @param VOID

    @retval None system will enter ACPI S3 State.
**/
UINT32 gSbMMIOBASEADDR = SB_MMIO_BASE;
VOID SBLib_S3InsteadOfWarmReset (VOID)
{
    UINT32      IoData;
    UINT8       Hour, Minute, Second;
    BOOLEAN     inBCD = TRUE;

    //flush caches befor going to S3
//#if (defined x64_BUILD && x64_BUILD == 1)
//        flushcaches();
    DisableCacheInCR0();
//#else
//        _asm wbinvd
//#endif

    // Read RTC Status Register 0xC
    ReadRtcIndex(0xC);

    // determine if RTC is in BCD mode
    if( ReadRtcIndex(0xB) & 0x4 ) // bit 2
        inBCD = FALSE;
    // wait for time update to complete before reading the values
    while( ReadRtcIndex(0xA) & 0x80 ); // while bit 7 is set the
                                                // time update is in progress
    //read current hour, minute, second
    Hour = ReadRtcIndex(0x4);
    Minute = ReadRtcIndex(0x2);
    Second = ReadRtcIndex(0x0);

    //convert second to decimal from BCD and increment by 1
    if(inBCD)
    	BcdToDecimal8(Second);
    Second += 3;

    if(Second > 59){
        Second -= 60;
        if(inBCD)
            Minute = (Minute >> 4) * 10 + (Minute & 0x0F);
        Minute++;
        if(Minute > 59){
            Minute = 0;
            if(inBCD)
                Hour = (Hour >> 4) * 10 + (Hour & 0x0F);
            Hour++;
            // check 24 hour mode/12 hour mode
            if( ReadRtcIndex(0xB) & 0x2 ) {// bit 1 1=24hour else 12 hour
                if(Hour > 23)
                    Hour = 0;
            } else {
                if(Hour > 11)
                    Hour = 0;
            }

            if(inBCD)
                Hour = Hour % 10 + ( (Hour / 10) << 4 ) ;
        }
        if(inBCD)
            Minute = Minute % 10 + ( (Minute / 10) << 4 ) ;
    }

    //convert from decimal to BCD
    if(inBCD)
    	DecimalToBcd8(Second);

    //set the alarm
    WriteRtcIndex(0x5, Hour);
    WriteRtcIndex(0x3, Minute);
    WriteRtcIndex(0x1, Second);
    // don't alarm RTC Date.
    WriteRtcIndex(0xD, ( ReadRtcIndex(0xD) & 0x80));
    //enable the alarm
    WriteRtcIndex(0xB, ( ReadRtcIndex(0xB) | ((UINT8)( 1 << 5 )) ));

// ========== PORTING REQUIRED ===========================================================
//  Current implementation to simulate the Warm Reboot may not be sufficient on some platforms.
//  S3 transition may require additional Chipset/Platform cooding.
//  If needed add any necessary OEM hooks to be able to put the system into S3 at the end of this handler
//========================================================================================

    //set RTC_EN bit in PM1_EN to wake up from the alarm
    IoWrite16(PM_BASE_ADDRESS + 0x02, ( IoRead16(PM_BASE_ADDRESS + 0x02) | (1 << 10) ));
    //modify power management control register to reflect S3
    IoData = IoRead32(PM_BASE_ADDRESS + 0x04);
    //following code is applicable to Intel PCH only.
    IoData &= ~(0x1C00);
#ifndef AMD_PLATFROM_SUPPORT
    //following code is applicable to Intel PCH only.
    IoData |= 0x1400; //Suspend to RAM
    IoWrite32(PM_BASE_ADDRESS + 0x04, IoData );
#else
    *(volatile UINT8*)( gSbMMIOBASEADDR + 0x300+0xbe) |= BIT5; // Set SLP_TYPE to go to sleep ,not trigger smi
    *(volatile UINT8*)( gSbMMIOBASEADDR + 0x300+0x0b) &= ~(BIT0 + BIT1);
    *(volatile UINT8*)( gSbMMIOBASEADDR + 0x300+0x0b) |= BIT0;
    *(volatile UINT8*)( gSbMMIOBASEADDR + 0x200+0xb0) &= ~(BIT2+BIT3);

#if HW_REDUCE_ACDCTIMER_SUPPORT	
    if(IsHwReduceSystem){
        *(volatile UINT32*)( gSbMMIOBASEADDR + 0x1D00+0x08) = 0x03; // clear AC timer status
        *(volatile UINT32*)( gSbMMIOBASEADDR + 0x1D00+0x18) = 0x03; // clear DC timer status
        *(volatile UINT32*)( gSbMMIOBASEADDR + 0x1D00+0x00) = 0x05; // Set 5 s for AC timer.
        *(volatile UINT32*)( gSbMMIOBASEADDR + 0x1D00+0x04) = 0x05; // Set 5 s for DC timer.   
        *(volatile UINT32*)( gSbMMIOBASEADDR + 0x1D00+0x20) |= (BIT8+BIT9); // Enabled Timer to wake up system.     
    }
#endif
    IoData |= 0x00C00; //Write sleep type to PM base, sleep action will be processed by AGESA FchSmmSxDispatcher.c
    IoWrite32(PM_BASE_ADDRESS + 0x04, IoData );

    // Do any specific porting if needed.
    SBLib_S3InsteadOfWarmResetCallBack();
    
    IoWrite8(0x80,0x75);
    //EFI_DEADLOOP(); //Go to AGESA FchSmmSxDispatcher.c

#endif

}




/**

    @param VOID

    @retval VOID

**/
VOID SB_CapsuleShutdown(VOID)
{
    UINT16          Value16;

    // clear the power button  status
    while (READ_MMIO8_SMI(FCH_SMI_REG84 + 2) & BIT03) {
        RW_MMIO8_SMI(FCH_SMI_REG84 + 2, 0, BIT03);
    }

    WRITE_IO8_PMIO (FCH_PMIOA_REG5B, 0x02);

    Value16 = IoRead16(PM_BASE_ADDRESS) | (UINT16)(1 << 8);
    do {
        IoWrite16(PM_BASE_ADDRESS, Value16);
        for (Value16 = 0; Value16 < 0x100; Value16++)
            IoWrite8(0xED, (UINT8)Value16);
        Value16 = IoRead16(PM_BASE_ADDRESS);
    } while (Value16 & 0x100);

    Value16 = IoRead16(PM_BASE_ADDRESS+4) & ~(15 << 10);


    //put to S5
    IoWrite16(PM_BASE_ADDRESS + 4,(UINT16)(Value16 | (13 << 10)));

    IoWrite8(0x80,0x05);

    CpuDeadLoop (); //halt at this,never come here!
}

/**
    do a warm reset

        
    @param ResetType Reset Type

         
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/

EFI_STATUS
EFIAPI
AmdWarmReset (
  IN EFI_RESET_TYPE  ResetType
  )
{
	EFI_STATUS	Status = EFI_NOT_READY; // default is not entering capsule sleep.
    BOOLEAN IsSbShutdownUsbLegacy = FixedPcdGetBool (SbShutdownUsbLegacyPolicy);

    if(SbGetCapsuleFlag()) {
        if (ResetType == EfiResetWarm) {
            if ( IsSbShutdownUsbLegacy ){
                // Shutdown Smm usb legacy
                ShutdownUsbLegacy();
            }
		#if defined(CAPSULE_RESET_MODE) && CAPSULE_RESET_MODE == 1
			WRITE_IO8(RESET_PORT, (SB_RST_CPU + SB_COLD_RESET));
        	EFI_DEADLOOP();
		#else
			SBLib_S3InsteadOfWarmReset();
		#endif
		} else if (ResetType == EfiResetShutdown) {
			SB_CapsuleShutdown();
		}
		Status = EFI_SUCCESS; // Ready to do capsule sleep.
	}

	return Status;
}


/**
    This function proccessed for trap S5 sleep to S3 for windows firmware update

    @param VOID

    @retval VOID

**/
VOID SbWindowsFirmwareUpdatePutS5InsteadReset( 
    IN EFI_RESET_TYPE           ResetType 
)
{
#if defined(CAPSULE_RESET_MODE) && CAPSULE_RESET_MODE == 0	  
	  UINT32 IoData;
	  	if(SbGetCapsuleFlag()) {
			// Go to S5 for OS FW update process 
			if (ResetType == EfiResetWarm) {
		    DEBUG ((DEBUG_INFO, "SbWindowsFirmwareUpdatePutS5InsteadReset put S5 trap  for Capsule\n"));
			IoData = IoRead32(PM_BASE_ADDRESS + 0x04);
			IoData &= ~(0x1C00);
			IoData |= 0x3400; //Write sleep type to PM base, S5 trap
			IoWrite32(PM_BASE_ADDRESS + 0x04, IoData );
			
			IoWrite8(0x80,0x53);// need nerver go to here.
			EFI_DEADLOOP();
			}
		}
#endif	 
 }

/**
    SbRuntimeResetAmdWarmReset

    @param ResetType Type of reset to perform
    @param ResetStatus System status that caused the reset.  if part
        of normal operation then this should be
        EFI_SUCCESS, Otherwise it should reflect the
        state of the system that caused it
    @param DataSize Size in bytes of the data to be logged
    @param ResetData OPTIONAL      Pointer to the data buffer that is to be logged
               
    @retval VOID

**/
VOID
SbRuntimeResetAmdWarmReset (
	    IN EFI_RESET_TYPE           ResetType,
	    IN EFI_STATUS               ResetStatus,
	    IN UINTN                    DataSize,
	    IN VOID                     *ResetData OPTIONAL
 )
{
      EFI_STATUS                      Status = EFI_SUCCESS;
	  SbWindowsFirmwareUpdatePutS5InsteadReset(ResetType);
      Status = AmdWarmReset(ResetType); 
}

/**
    This function saves the input ResetType in "ResetType"
    variable

               
    @param gRT efi runtime service.
    @param ResetType Type of reset to be generated

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS SetResetType(
    IN EFI_RUNTIME_SERVICES *gRT,
    IN EFI_RESET_TYPE       ResetType
)
{
    EFI_STATUS  Status       = EFI_SUCCESS;
    UINTN       DataSize     = sizeof(UINT32);
    EFI_GUID    VariableGuid = AMI_CSP_RESET_GUID;
    UINT32  CurrentResetType = SoftReset;

    // <AAV> use PCD instead.
    Status = gRT->GetVariable(
                 L"CspResetType",
                 &VariableGuid,
                 NULL,
                 &DataSize,
                 &CurrentResetType);
    if (!EFI_ERROR(Status))
    {
        if (CurrentResetType >= (UINT32)ResetType)
            return EFI_SUCCESS;
    }

    CurrentResetType = ResetType;

    Status = gRT->SetVariable(
                 L"CspResetType",
                 &VariableGuid,
                 EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                 DataSize,
                 &CurrentResetType);

    return Status;
}

/**
    Get PcdFchFullHardReset PCD
        
    @param None.
    @retval Return PCD value.


**/
BOOLEAN EFIAPI GetFchFullHardReset()
{
    return IsFchFullHardReset;
}

/**
    Update FchFullHardReset PCD value
        
    @param PCD value.
    @retval none.

**/

VOID EFIAPI UpdateFchFullHardResetValue(BOOLEAN Value)
{
    IsFchFullHardReset = Value;
    
}
#if HW_REDUCE_ACDCTIMER_SUPPORT
/**
    Update FchFullHardReset PCD value
        
    @param PCD value.
    @retval none.

**/

VOID EFIAPI UpdateHwReduceValue(BOOLEAN Value)
{
    IsHwReduceSystem = Value;
    
}
#endif


