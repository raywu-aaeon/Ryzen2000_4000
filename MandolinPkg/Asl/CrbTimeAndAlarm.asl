//ACDC Timer asl
//DefinitionBlock (
//    "AcDcTimer.aml",         // Output file
//    "SSDT",                  // Signature
//    0x01,                    // SSDT Revision
//    "AMD",                   // OEM ID
//    "ACDC",                  // OEM Table ID
//    0x1                      // OEM Revision
//    )
//{
  Scope(\_SB)
  {
    Device(ACDC){
      Name(_HID, "ACPI000E") //device ID

      Name(_CRS, ResourceTemplate() {
        GpioInt(Edge, ActiveLow, SharedAndWake, PullUp, 3000, "\\_SB.GPIO", ,) {52}
      })
      
      Method(_STA) {
        If (LEqual(\CNSB,0)){
           Return(0x0F)
      	} Else {
           Return(0x00)
      	}
      }
      OperationRegion(IOMX, SystemMemory, 0xFED80D00, 0x100)
      Field(IOMX, AnyAcc, NoLock, Preserve) {
        Offset (0x17),
        IM17, 8,
      }

      OperationRegion(CMOP, SystemMemory, 0xFED81D00, 0x100)
      Field(CMOP, DWordAcc, NoLock, Preserve) {
        Offset (0x00),
        ATVE,  32,//AcTimerValue
        AETP,  32,//AcExpiredTimerPolicy
        ATED,  1,//AcTimerExpired.
        ATWP,  1,//AcTimerWakeup.
        Offset (0x10),
        DTVE,  32,//DcTimerValue
        DETP,  32,//DcExpiredTimerPolicy
        DTED,  1,//DcTimerExpired.
        DTWP,  1,//DcTimerWakeup.
        Offset (0x20),
        BUSY,  1, //Busy
            ,  7, //
        ATEE,  1, //AcTimerEventEn.
        DTEE,  1, //DcTimerEventEn.
      }

      Method(_INI) {
        Store(zero, IM17)
        Store(one, ATEE)
        Store(one, DTEE)
      }

      Method(AINI) {
        Store(zero, IM17)
        Store(one, ATEE)
      }

      Method(DINI) {
        Store(zero, IM17)
        Store(one, DTEE)
      }

      //Method(_GCP) {
      //  Return (0x03) //AC/DC timer is implemented;
      //}

      Method(_STP, 2){
        If(LEqual(Arg0, 0)) {
          Store(Arg1, AETP) //Set AC timer policy
        }
        Else {
          Store(Arg1,DETP) //Set DC timer policy
        }
        Return(0)
      }

      Method(_TIP, 1){
        If(LEqual(Arg0, 1)) {
          Store(DETP, Local0) //Get DC timer policy
        }
        Else {
          Store(AETP, Local0) //Get AC timer policy
        }
        Return (Local0)
      }

      Method(_STV, 2){
        If(LEqual(Arg0, 0)) {
          AINI()
          Store(Arg1, ATVE) //Set AC timer value
        }
        Else {
          DINI()
          Store(Arg1, DTVE) //Set DC timer value
        }
        Return(0)
      }

      Method(_TIV, 1){
        If(LEqual(Arg0, 1)) {
          Store(DTVE, Local0) //Get DC timer value
        }
        Else {
          Store(ATVE, Local0) //Get AC timer value
        }
        Return (Local0)
      }

      Method(_GWS, 1){
        If(LEqual(Arg0, 1)) {
          Store(DTWP, Local0) //Get DC timer wake status
        }
        Else {
          Store(ATWP, Local0) //Get AC timer wake status
        }
        Return (Local0)
      }

      Method(_CWS, 1){
        If(LEqual(Arg0, 0)) {
          Store(1, ATWP) //Clear AC Wake status
        }
        Else {
          Store(1, DTWP) //Clear DC Wake status
        }
        Return(0)
      }
      
      // reference \AmiModulePkg\ACPI\TimeAndAlarm.asl
      Name (TMZN, 2047)  // Timezone - set to 2047 to indicate value not specified. Will be used if no buffer for SMI was found
      Name (DAYL, 0)     // daylight - bit field to indicate daylight adjustment requirement. Will be used if no buffer for SMI was found

      Name (ATBF, 0x10000000) //Adress of communication buffer
      Name (BUFU, 0x0) //Indicator that buffer was allocated and usable.
      
      //Mutex used to synchronize between methods   accessing RTC   
      Mutex(RTCL, 0) 
      
      // Region for SW SMI port
      // OperationRegion (CSMI, SystemIO, SMIP , 0x1) //SMIO
      OperationRegion (ASMI, SystemIO, SMIO , 0x1) 
      Field (ASMI, ByteAcc, NoLock, Preserve) 
      { 
          INQ,8
      } 
      
      
      // Regions for SW SMI data buffer.  Need two, one for byte access, one for nibble access.
      OperationRegion (DSMI, SystemMemory, ATBF, 0x4)
      Field (DSMI, AnyAcc, NoLock, Preserve) 
      { 
          BSTA, 8, 
          BDLY, 8,
          BTZN, 16 
      } 
      
      OperationRegion(VRTC, SystemCMOS, 0, 0x10)
      Field(VRTC, ByteAcc, Lock, Preserve) 
      {

          SEC, 8,
          SECA, 8, 
                
          MIN, 8,
          MINA, 8,
                
          HOR, 8,
          HORA, 8,
                
          DAYW, 8,                
          DAY, 8,
                
          MON, 8,
          YEAR, 8,

          STAA, 8,
          STAB, 8,
          STAC, 8,
          STAD, 8
      }
      
      
      Method (RTWT, 0x00) {
          Acquire(RTCL, 2000)

          // Loop until an update completes (the Update-Ended Flag (UF) is set)
          While( LNotEqual(And(STAC, 0x10), 0x10 )){
              NoOp
          }

          Release(RTCL)
          return (One)
      }
      
      // Get Capability
      // This object is required and provides the OSPM with a bit mask of the device capabilities. The device 
      // can implement the time function inaddition to the wake function. The capabilities bitmask will 
      // indicate to the OSPM what support is implemented. If the platform implements both AC and DC 
      // timers then it is capable of waking up based on the power source

      // Only AC timer here, so it will be the wake source regardless of the power source 
      Method (_GCP, 0x0, NotSerialized)
      {
          Return (0x7) //Get/Set real time features implemented, real time accuracy in seconds and AC/DC timer only;
      }
      
      // Get Real time Method
      // This object is required ifthe capabilities bit 2 is set to 1. The OSPM can use this object to get time. 
      // The return value is a buffer containing the time information
      Method (_GRT, 0x0, Serialized)
      {   
          Name(RBUF, Buffer(16) {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}) //Buffer of 16 bytes - return value

          // Create fields to address different offsets in the buffer
          CreateWordField(RBUF, 0x0, TYAR)
          CreateByteField(RBUF, 0x2, TMON)
          CreateByteField(RBUF, 0x3, TDAY)
          CreateByteField(RBUF, 0x4, THOR)
          CreateByteField(RBUF, 0x5, TMIN)
          CreateByteField(RBUF, 0x6, TSEC)
          CreateByteField(RBUF, 0x7, TVAL)    // Time Valid if 1, not valid if 0
          CreateWordField(RBUF, 0xA, TZN)     // Timezone not supported through rRTC - return value stored in ASL
          CreateByteField(RBUF, 0xC, DYL)     // Daylight not supported through rRTC - emulate in ASL

          if (BUFU) 
          {
              // Read value from NVRAM
              Store (0x01, BSTA)
              Store (ATAA, INQ)
              Sleep (100)

              if( LEqual(BSTA, 0x03 ) ) {
                  Store (BDLY, DAYL)
                  Store (BTZN, TMZN)
              } else {
                  Store(2047, TMZN)
                  Store (0, DAYL)
              }
          }

          RTWT()
        
          FromBCD(YEAR, TYAR)    // Get Year
          FromBCD (MON, TMON)    // Get Month
          FromBCD (DAY, TDAY)    // Get Day
          FromBCD (HOR, THOR)
          FromBCD (MIN, TMIN)
          FromBCD (SEC, TSEC)

	  Store (2047, TMZN)	//ATAD_TimeZone_Issue_Workaround
          Store (TMZN, TZN)
          Store (DAYL, DYL)
                
          // we don't have centry byte
          ADD(TYAR, 2000, TYAR)

          Store (0x1, TVAL) // Data valid
          return (RBUF)
      }

      // Set Real Time
      // This object is required if the capabilities bit 2 is set to 1. The OSPM can use this object to set the 
      // time. The argument is a buffer containingthe time information

      Method (_SRT, 0x1, Serialized)
      {
          CreateWordField(Arg0, 0x0, TYAR)
          CreateByteField(Arg0, 0x2, TMON)
          CreateByteField(Arg0, 0x3, TDAY)
          CreateByteField(Arg0, 0x4, THOR)
          CreateByteField(Arg0, 0x5, TMIN)
          CreateByteField(Arg0, 0x6, TSEC)
          CreateWordField(Arg0, 0xA, TZN)     // Timezone not supported through rRTC - return value stored in ASL
          CreateByteField(Arg0, 0xC, DYL)     // Daylight not supported through rRTC
                
          if (BUFU) 
          {
              // Send Daylight to NVRAM
              Store (0x2, BSTA)
              Store (DYL, BDLY)
              Store (TZN, BTZN)

              Store (ATAA, INQ)
          }

          RTWT()  

          ToBCD(Subtract(TYAR, 2000), YEAR)
          ToBCD (TMON, MON)   // Set month
          ToBCD (TDAY, DAY)   // Set day
          ToBCD (THOR, HOR)   // Set hour
          ToBCD (TMIN, MIN)   // Set minute
          ToBCD (TSEC, SEC)   // Set second

          Store (TZN, TMZN)
          Store (DYL, DAYL)

          If(LEqual(BSTA, 0x3)) // SMI handler set status to OK
          {
              return (0x0) // return success
          }

          return (0xFFFFFFFF) // return error
      }
      
    } // end of ACPI Wake Alarm device object
  }
//}

