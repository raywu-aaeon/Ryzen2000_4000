#if ASL_WMI_WDT_SUPPORT
  Scope(\_SB.BFPI) {
    //---------------------------------------------------------------------------
    // Name: WDTO
    //
    // Description:  WDT Operation
    //
    // Input:
    //   Arg0 : Sub-function number
    //   Arg1 : IIA0, Input: IntegerArgument
    //   Arg2 : IIA1, Input: IntegerArgument
    //
    // Output:
    //   According to sub-function.
    //
    //---------------------------------------------------------------------------
    Method (WDTO, 3){
      If (LEqual(Arg0, 0x0000)) {  // Report capability
        Return(WDRC(Arg1, Arg2))
      }
      If (LEqual(Arg0, 0x0001)) {  // Get watchdog timeout value
        Return(WDGT(Arg1, Arg2))
      }
      If (LEqual(Arg0, 0x0002)) {  // Set watchdog timeout value and start/stop watchdog
        Return(WDST(Arg1, Arg2))
      }
      Return(ASL_BFPI_INVALID_PARAMETER)
    }

    //------------------------------------------------------------------------
    // Table:    TWDT
    // Description:  WDT Type look up table
    //
    //-------------------------------------------------------------------------
    Name (TWDT, Package(ASL_WDT_NUMBER) {
        ASL_FIRST_WDT_TYPE
        #ifdef ASL_SECOND_WDT_TYPE
        , ASL_SECOND_WDT_TYPE
        #endif
        // TODO: Porting required if 3rd WDT supported
        //, ASL_THIRD_WDT_TYPE
    })

    //---------------------------------------------------------------------------
    // Name: WDRC
    //
    // Description:  WDT report capability
    //   Arg0 : IIA0, Select capability data to return
    //   Arg1 : IIA1, Basically not used.
    //
    // Output:
    //   According to sub-function.
    //
    //---------------------------------------------------------------------------
    Method (WDRC, 2){
      And (Arg0, 0xFF, Local0) // Input: Interger - Select capability data to return

      If (LEqual(Local0, 0x00)) {  // Report capability in JSON format
        Store (WDTC, WDBF)
        Return (ASL_BFPI_SUCCESS)
      }
      If (LEqual(Local0, 0x10)) {  // Return Max. supported timeout in ms.
        If (LGreater(Arg1, ASL_WDT_NUMBER)) {
          Return (ASL_BFPI_INVALID_PARAMETER)
        }
        Return (AWRC(DerefOf(Index(TWDT, Arg1))))
      }
      If (LEqual(Local0, 0x12)) {  // Supported WatchDog Sensor Bitmap
        Store (0, Local0)  // Counter
        Store (0, Local1)  // Bitmap to return
        While (LLess(Local0, SizeOf(TWDT))) {
          Or (Local1, ShiftLeft(0x01, Local0), Local1)
          Increment (Local0)
        }
        Return (Local1)
      }
      Return(ASL_BFPI_INVALID_PARAMETER)
    }

    //---------------------------------------------------------------------------
    // Name: AWRC
    //
    // Description:  AAEON WDT get timeout value
    //   Arg0 : WDT Type
    //
    // Output:
    //   Interger: Remained timeout value
    //   ASL_BFPI_INVALID_PARAMETER
    //
    //---------------------------------------------------------------------------
    Method (AWRC, 1) {
      #if ASL_WDT_TYPE_OEM_SUPPORT
      // OEM WDT controlling method can be implemented externally in project level.
      If (LEqual (Arg0, ASL_SOURCE_TYPE_OEM)) {
        Return (ASL_OEM_WDT_RC_METHOD)
      }
      #endif
      #if ASL_WDT_TYPE_SOC_SUPPORT
      If (LEqual (Arg0, ASL_SOURCE_TYPE_SOC)) {
        // SoC WDT controlling method should be implemented externally in platform level.
        Return (\_SB.SCRC())
      }
      #endif
      #if ASL_WDT_TYPE_SIO1_SUPPORT
      If (LEqual (Arg0, ASL_SOURCE_TYPE_SIO1)) {
        Return (\_SB.PCI0.LPCB.SIO1.W1RC())
      }
      #endif
      #if ASL_WDT_TYPE_SIO2_SUPPORT
      If (LEqual (Arg0, ASL_SOURCE_TYPE_SIO2)) {
        Return (\_SB.PCI0.LPCB.SIO2.W2RC())
      }
      #endif
      #if ASL_WDT_TYPE_SIO3_SUPPORT
      If (LEqual (Arg0, ASL_SOURCE_TYPE_SIO3)) {
        Return (\_SB.PCI0.LPCB.SIO.W3RC())
      }
      #endif
      #if ASL_WDT_TYPE_EC1_SUPPORT
      If (LEqual (Arg0, ASL_SOURCE_TYPE_EC1)) {
        Return (\_SB.PCI0.LPCB.EC01.E1RC())
      }
      #endif
      #if ASL_WDT_TYPE_EC2_SUPPORT
      If (LEqual (Arg0, ASL_SOURCE_TYPE_EC2)) {
        Return (\_SB.PCI0.LPCB.EC02.E2RC())
      }
      #endif
      Return (ASL_BFPI_NOT_SUPPORTED)
    }

    //---------------------------------------------------------------------------
    // Name: WDGT
    //
    // Description:  WDT get timeout value
    //   Arg0 : IIA0, Basically not used.
    //   Arg1 : IIA1, WDT instance to get
    //
    // Output:
    //   Interger: Remained timeout value
    //   ASL_BFPI_INVALID_PARAMETER
    //
    //---------------------------------------------------------------------------
    Method (WDGT, 2){
      If (LGreater(Arg1, ASL_WDT_NUMBER)) {
        Return (ASL_BFPI_INVALID_PARAMETER)
      }
      Return (AWGT(DerefOf(Index(TWDT, Arg1))))
    }

    //---------------------------------------------------------------------------
    // Name: AWGT
    //
    // Description:  AAEON WDT get timeout value
    //   Arg0 : WDT Type
    //
    // Output:
    //   Interger: Remained timeout value
    //   ASL_BFPI_INVALID_PARAMETER
    //
    //---------------------------------------------------------------------------
    Method (AWGT, 1) {
      #if ASL_WDT_TYPE_OEM_SUPPORT
      // OEM WDT controlling method can be implemented externally in project level.
      If (LEqual (Arg0, ASL_SOURCE_TYPE_OEM)) {
        Return (ASL_OEM_WDT_GT_METHOD)
      }
      #endif
      #if ASL_WDT_TYPE_SOC_SUPPORT
      If (LEqual (Arg0, ASL_SOURCE_TYPE_SOC)) {
        // SoC WDT controlling method should be implemented externally in platform level.
        Return (\_SB.SCGT())
      }
      #endif
      #if ASL_WDT_TYPE_SIO1_SUPPORT
      If (LEqual (Arg0, ASL_SOURCE_TYPE_SIO1)) {
        Return (\_SB.PCI0.LPCB.SIO1.W1GT())
      }
      #endif
      #if ASL_WDT_TYPE_SIO2_SUPPORT
      If (LEqual (Arg0, ASL_SOURCE_TYPE_SIO2)) {
        Return (\_SB.PCI0.LPCB.SIO2.W2GT())
      }
      #endif
      #if ASL_WDT_TYPE_SIO3_SUPPORT
      If (LEqual (Arg0, ASL_SOURCE_TYPE_SIO3)) {
        Return (\_SB.PCI0.LPCB.SIO.W3GT())
      }
      #endif
      #if ASL_WDT_TYPE_EC1_SUPPORT
      If (LEqual (Arg0, ASL_SOURCE_TYPE_EC1)) {
        Return (\_SB.PCI0.LPCB.EC01.E1GT())
      }
      #endif
      #if ASL_WDT_TYPE_EC2_SUPPORT
      If (LEqual (Arg0, ASL_SOURCE_TYPE_EC2)) {
        Return (\_SB.PCI0.LPCB.EC02.E2GT())
      }
      #endif
      Return (ASL_BFPI_NOT_SUPPORTED)
    }

    //---------------------------------------------------------------------------
    // Name: WDST
    //
    // Description:  Set watchdog timeout value and start/stop watchdog
    //   Arg1 : IIA0, timeout value in ms
    //            0: stop watchdog
    //            other: start watchdog with value as timeout
    //   Arg1 : IIA1, WDT instance to set
    //
    // Output:
    //   BFPI_STATUS
    //
    //---------------------------------------------------------------------------
    Method (WDST, 2){
      If (LGreater(Arg1, ASL_WDT_NUMBER)) {
        Return (ASL_BFPI_INVALID_PARAMETER)
      }
      Return (AWST(Arg0, DerefOf(Index(TWDT, Arg1))))
    }

    //---------------------------------------------------------------------------
    // Name: AWST
    //
    // Description:  AAEON Set watchdog timeout value and start/stop watchdog
    //   Arg0 : Timeout value in ms
    //            0: stop watchdog
    //            other: start watchdog with value as timeout
    //   Arg1 : WDT type to set
    //
    // Output:
    //   BFPI_STATUS
    //
    //---------------------------------------------------------------------------
    Method (AWST, 2){
      #if ASL_WDT_TYPE_OEM_SUPPORT
      // OEM WDT controlling method can be implemented externally in project level.
      If (LEqual (Arg1, ASL_SOURCE_TYPE_OEM)) {
        // ASL_OEM_WDT_ST_METHOD should contain (Arg0). EX: \_SB.OWDT.ODST(Arg0)
        Return (ASL_OEM_WDT_ST_METHOD)
      }
      #endif
      #if ASL_WDT_TYPE_SOC_SUPPORT
      If (LEqual (Arg1, ASL_SOURCE_TYPE_SOC)) {
        // SoC WDT controlling method should be implemented externally in platform level.
        Return (\_SB.SCST(Arg0))
      }
      #endif
      #if ASL_WDT_TYPE_SIO1_SUPPORT
      If (LEqual (Arg1, ASL_SOURCE_TYPE_SIO1)) {
        Return (\_SB.PCI0.LPCB.SIO1.W1ST(Arg0))
      }
      #endif
      #if ASL_WDT_TYPE_SIO2_SUPPORT
      If (LEqual (Arg1, ASL_SOURCE_TYPE_SIO2)) {
        Return (\_SB.PCI0.LPCB.SIO2.W2ST(Arg0))
      }
      #endif
      #if ASL_WDT_TYPE_SIO3_SUPPORT
      If (LEqual (Arg1, ASL_SOURCE_TYPE_SIO3)) {
        Return (\_SB.PCI0.LPCB.SIO.W3ST(Arg0))
      }
      #endif
      #if ASL_WDT_TYPE_EC1_SUPPORT
      If (LEqual (Arg1, ASL_SOURCE_TYPE_EC1)) {
        Return (\_SB.PCI0.LPCB.EC01.E1ST(Arg0))
      }
      #endif
      #if ASL_WDT_TYPE_EC2_SUPPORT
      If (LEqual (Arg1, ASL_SOURCE_TYPE_EC2)) {
        Return (\_SB.PCI0.LPCB.EC02.E2ST(Arg0))
      }
      #endif
      Return(ASL_BFPI_NOT_SUPPORTED)
    }

  }  // Scope(\_SB.BFPI)
  #endif