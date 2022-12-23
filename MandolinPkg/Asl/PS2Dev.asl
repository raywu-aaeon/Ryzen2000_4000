//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

#include <TokenAsl.h>

Scope (ASL_ECPS2_DEVICE_NAME) {
    Device(PS2K) {
        Name(_HID,"MSFT0001")
        Name(_CID,EISAID("PNP0303"))

        Method(_STA,0) {
            Return (0x0F)
        }

        Name(_CRS,ResourceTemplate() {
            IO(Decode16, 0x60, 0x60, 0, 0x1)    //PS2 resource
            IO(Decode16, 0x64, 0x64, 0, 0x1)
            IRQNoFlags(){1}
        })

        Name(_PRS, ResourceTemplate() {
            StartDependentFn(0, 0) {  
                IO(Decode16, 0x60, 0x60, 0, 0x1)  
                IO(Decode16, 0x64, 0x64, 0, 0x1)
                IRQNoFlags(){1}
            }
        EndDependentFn()
        })

        // Keyboard 2nd Level wake up control method
        Method(_PSW, 1) {
            Store(Arg0, \KBFG)
        }
    }// End of PS2K

    Scope(\){
        Name(\KBFG, 0x01)   //Keyboard wake-up flag default enable
    }
} // End of \_SB.PCI0


//**********************************************************************
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
