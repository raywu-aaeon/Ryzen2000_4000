//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

    //LPC PCI Config Space Region
    OperationRegion(LPCS, PCI_Config, 0x00, 0x100)
    Field(LPCS, AnyAcc, NoLock, Preserve) 
      {
        offset (0xA4),
        IMCP, 16,       //IMC Port
      }

    //Operation Region for EC index/data
    OperationRegion(ECIO, SystemIO, And(IMCP, 0xFFFE), 0x2)	
    Field(ECIO, ByteAcc, NoLock, Preserve)
      {
        INDX, 8, 
        DATA, 8
      }
	    
    //EC logical device register space
    IndexField(INDX, DATA, ByteAcc, NoLock, Preserve)	
      {
        Offset(0x7), 
        LDNM, 8, 
        Offset(0x30), 
        ACT, 1,
        Offset(0x60), 
        IOBH, 8, 
        IOBL, 8, 
        Offset(0x70), 
        INT, 4, 
      }

    //Method to enter config mode and select the corresponding logical device
    Method(CFG, 1)
      {
        Store(0x5A, INDX)
        Store(0x5A, INDX)
        Store(Arg0, LDNM)
	  	}

    //Method to exit config mode
    Method(XCFG)
      {
        Store(0xA5, INDX)
      }

    Mutex(ECMU, 0x0)

    //Method to return status of any logical device in EC
    Method(STA, 1)
      {
        Store(0x00, Local0)

        Acquire(ECMU, 0x5000)

        CFG(Arg0)
        If(ACT)
          {
            Store(0x0F, Local0)
          }
        If (LEqual(INDX, 0xFF)) 
          {
            Store(0x00, Local0)      		
          }
        XCFG()
	    
        Release(ECMU)

        Return(Local0)
      }
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************