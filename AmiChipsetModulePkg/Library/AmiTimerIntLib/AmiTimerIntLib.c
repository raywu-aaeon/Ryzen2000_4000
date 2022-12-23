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

/** @file AmiTimerIntLib.c
    Timer Interrupt Library functions implementation

*/

#include <Token.h>
#include <Sb.h>
#include <Library/AmiTimerIntLib.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Pi/PiMultiPhase.h>
#include <Library/DebugLib.h>
#include <SbDxeInitElink.h>

typedef struct {
    UINT32      Count;
    UINT32      StoreCF8;
    UINT8       StoreCMOS;
    UINT8       StoreExtCMOS;
} TIMER_INT_DATA;

extern SAVE_RESTORE_CALLBACK SAVE_RESTORE_CALLBACK_LIST EndOfList;
SAVE_RESTORE_CALLBACK* SaveRestoreCallbackList[] = { SAVE_RESTORE_CALLBACK_LIST NULL };


/**
    This function calls registered callbacks to save/restore registers
    value in timer interrupt routine

    @param BOOLEAN Save - if TRUE - save registers, FALSE - restore back

    @retval VOID

**/
VOID SaveRestoreRegisters(
    IN BOOLEAN Save
)
{
    UINTN i;
    static volatile TIMER_INT_DATA  TimerIntData[VARIABLE_BUFFER_SIZE] = {0};
    static volatile UINT32          Index = 0;

    if (Save) {
      if (Index >= VARIABLE_BUFFER_SIZE) {
        //
        // Assert while VARIABLE_BUFFER_SIZE is too small
        //
        ASSERT(FALSE);
        //
        // Stop saving while buffer is not enough
        //
        return;
      }
      
      if ((Index != 0) && \
          (IoRead32(0xcf8) == TimerIntData[Index - 1].StoreCF8) && \
          (IoRead8(CMOS_ADDR_PORT) == TimerIntData[Index - 1].StoreCMOS) && \
          (IoRead8(CMOS_IO_EXT_INDEX) == TimerIntData[Index - 1].StoreExtCMOS) && \
          (TimerIntData[Index - 1].Count < 0xFFFFFFFF)) {
        TimerIntData[Index - 1].Count ++;
      } else {
        //
        // Store CF8 (PCI index)
        //
        TimerIntData[Index].StoreCF8 = IoRead32(0xcf8);
        
        /**** Porting Required ****/
        TimerIntData[Index].StoreCMOS = IoRead8(CMOS_ADDR_PORT);
        TimerIntData[Index].StoreExtCMOS = IoRead8(CMOS_IO_EXT_INDEX);
        Index ++;        
      }
    }

    for(i = 0; SaveRestoreCallbackList[i] != NULL; i++) 
        SaveRestoreCallbackList[i](Save);

    if (!Save) {
      Index --;
      /**** Porting Required ****/
      IoWrite8(CMOS_ADDR_PORT, TimerIntData[Index].StoreCMOS);
      IoWrite8(CMOS_IO_EXT_INDEX, TimerIntData[Index].StoreExtCMOS);
      
      //
      // Restore 0xCF8 (PCI index)
      //
      IoWrite32(0xcf8, TimerIntData[Index].StoreCF8);
      
      if (TimerIntData[Index].Count != 0) {
        TimerIntData[Index].Count --;
        Index ++;
      }
    }
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
