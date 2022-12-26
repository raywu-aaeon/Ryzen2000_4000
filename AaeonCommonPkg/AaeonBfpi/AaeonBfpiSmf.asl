#if ASL_WMI_SMF_SUPPORT
  Scope(\_SB.BFPI) {

#if ASL_WMI_HWM_SUPPORT == 0
    //------------------------------------------------------------------------
    // Table:    TFAN
    // Description:  Look up table for standard name of sensors
    //-------------------------------------------------------------------------
    Name(TFAN, Package() {
        ASL_STD_FAN_STRING_LIST
    })
#endif

    //---------------------------------------------------------------------------
    // Name: SMFO
    //
    // Description:  SMF Operation
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
    Method (SMFO, 3){
      If (LEqual(Arg0, 0x0000)) {  // Report capability
        Return(FCRC(Arg1, Arg2))
      }
      If (LEqual(Arg0, 0x0001)) {  // Get FAN mode
        Return(FCGM(Arg1, Arg2))
      }
      If (LEqual(Arg0, 0x0002)) {  // Set FAN mode
        Return(FCSM(Arg1, Arg2))
      }
      If (LEqual(Arg0, 0x0003)) {  // Get control point configuration
        Return(FCGP(Arg1, Arg2))
      }
      If (LEqual(Arg0, 0x0004)) {  // Set control point configuration
        Return(FCSP(Arg1, Arg2))
      }
      Return(ASL_BFPI_INVALID_PARAMETER)
    }

    //---------------------------------------------------------------------------
    // Name: FCRC
    //
    // Description:  SMF FAN Controller report capability
    //   Arg0 : IIA0, Select capability data to return
    //   Arg1 : IIA1, FAN index
    //
    // Output:
    //   According to sub-function.
    //
    //---------------------------------------------------------------------------
    Method (FCRC, 2){
      And (Arg0, 0xFF, Local0) // Input: Interger - Select capability data to return
      And (Arg1, 0x0F, Local1) // FAN index
      Store ("NULL", Local2) // FAN name
      ShiftRight (And(Arg1,0x10), 4, Local5) // FAN index mapping

      If (LEqual(Local0, 0x00)) {  // Report capability in JSON format
        Store (FCRG, \_SB.BFPI.WDBF)
        Return(ASL_BFPI_SUCCESS)
      }
      ElseIf (LEqual(Local0, 0x12)) {  // Supported Smart FAN Bitmap
        Store (0, Local1)  // Bitmap to return
        Store (0, Local3)  // Counter

        If (LEqual(Local5, 0)) {
          // Return in standard mapping
          Store (SizeOf(TFAN), Local4)
          While (LLess(Local3, Local4)) {
            If (LNotEqual(FCRM(DerefOf(Index(TFAN, Local3))), ASL_BFPI_NOT_SUPPORTED)) {
              Or (Local1, ShiftLeft(0x01, Local3), Local1)
            }
            Increment (Local3)
          }
        } Else {
          // Return in flatten mapping
          Store (FCRN, Local4)  // FAN Controller number

          While (LLess(Local3, Local4)) {
            Or (Local1, ShiftLeft(0x01, Local3), Local1)
            Increment (Local3)
          }
        }

        Return(Local1)
      }

      Store (FCIS(Local1, Local5), Local2)

      If (LEqual(Local0, 0x01)) {  // Label for FAN instance selected in Arg1.
        Store (FCRF(Local2), Local2)

        IF(LEqual (Local2, "NULL")) { Return (ASL_BFPI_NOT_SUPPORTED) }
        Store (Local2, \_SB.BFPI.WDBF)

        Return(ASL_BFPI_SUCCESS)
      }
      ElseIf (LEqual(Local0, 0x13)) {  // Return supported mode for FAN instance selected in Arg1.
        Return (FCRM(Local2))
      }
      ElseIf (LEqual(Local0, 0x14)) {  // Return Max. PWM value for FAN instance selected in Arg1.
        Return (FCPW(Local2))
      }
      ElseIf (LEqual(Local0, 0x15)) {  // Return Min. slope unit for FAN instance selected in Arg1.
        Return (FCLP(Local2))
      }
      ElseIf (LEqual(Local0, 0x16)) {  // Return target temperature map. Also put string to data buffer.
        Return (FCTM(Local2, Local5))
      }

      Return(ASL_BFPI_INVALID_PARAMETER)
    }

    //---------------------------------------------------------------------------
    // Name: FCIS
    //
    // Description:  SMF FAN get name string from index. If no proper string found,
    //               this function will try to retrieve a string from data buffer.
    //   Arg0 : SMF index to get.
    //   Arg1 : Index format
    //
    // Output:
    //   String : FAN name string
    //
    //---------------------------------------------------------------------------
    Method (FCIS, 2){
      Store ("NULL", Local0)  // FAN string

      If (LEqual(Arg1, 0)) {
        // Standard mapping, Get name string from standard table
        If (LLess(Arg0, SizeOf(TFAN))) {
          Store (DerefOf(Index(TFAN, Arg0)), Local0)
        }
      } Else {
        // Flatten mapping, Get name string from index
        Store (FCRS(Arg0), Local0)  // Get name string from index
      }

      If (LEqual(Local0, "NULL")) {
        // Not found, use string in WDBF instead.
        Store (ToString (WDBF), Local0)
      }

      Return (Local0)
    }

    //---------------------------------------------------------------------------
    // Name: FCRG
    //
    // Description:  SMF FAN Controller report general capability
    //
    // Output:
    //   According to sub-function.
    //
    //---------------------------------------------------------------------------
    Method (FCRG, 0){
      //Get base prefix
      Store ("{ \"Label\":\"SMF\", \"Instance Number\": ", Local0)
      Store (ONE, Local1)
      Concatenate (Local0, FCRN, Local0)
      Concatenate (Local0, ", \"Instance Data\":[", Local0)

      // Concatenate all supported FAN data
#if ASL_SMF_TYPE_OEM_SUPPORT
      // OEM SMF controlling method can be implemented externally in project level.
      If (LEqual(Local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
      Concatenate (Local0, ASL_OEM_SMF_RL_METHOD, Local0)
#endif
#if ASL_SMF_TYPE_SOC_SUPPORT
      // SoC SMF controlling method should be implemented externally in platform level.
      If (LEqual(Local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
      Concatenate (Local0, \_SB.SFRL, Local0)
#endif
#if ASL_SMF_TYPE_SIO1_SUPPORT
      If (LEqual(Local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
      Concatenate (Local0, \_SB.PCI0.LPCB.SIO1.F1RL, Local0)
#endif
#if ASL_SMF_TYPE_SIO2_SUPPORT
      If (LEqual(Local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
      Concatenate (Local0, \_SB.PCI0.LPCB.SIO2.F2RL, Local0)
#endif
#if ASL_SMF_TYPE_SIO3_SUPPORT
      If (LEqual(Local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
      Concatenate (Local0, \_SB.PCI0.LPCB.SIO3.F3RL, Local0)
#endif
#if ASL_SMF_TYPE_EC1_SUPPORT
      If (LEqual(Local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
      Concatenate (Local0, \_SB.PCI0.LPCB.EC01.E1RL, Local0)
#endif
#if ASL_SMF_TYPE_EC2_SUPPORT
      If (LEqual(Local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
      Concatenate (Local0, \_SB.PCI0.LPCB.EC02.E2RL, Local0)
#endif

      // Append suffix
      Concatenate (Local0, "]}", Local0)

      Return(Local0)
    }

    //---------------------------------------------------------------------------
    // Name: FCRN
    //
    // Description:  FAN Controller return number
    //
    // Output:
    //   Integer - Total number of FAN controller
    //
    //---------------------------------------------------------------------------
    Method (FCRN, 0){
      Store (0, Local0)

      // Concatenate all supported sensor name for requested type
#if ASL_SMF_TYPE_OEM_SUPPORT
      // OEM SMF controlling method can be implemented externally in project level.
      Add (Local0, ASL_OEM_SMF_RN_METHOD, Local0)
#endif
#if ASL_SMF_TYPE_SOC_SUPPORT
      // SoC SMF controlling method should be implemented externally in platform level.
      Add (Local0, \_SB.SFRN, Local0)
#endif
#if ASL_SMF_TYPE_SIO1_SUPPORT
      Add (Local0, \_SB.PCI0.LPCB.SIO1.F1RN, Local0)
#endif
#if ASL_SMF_TYPE_SIO2_SUPPORT
      Add (Local0, \_SB.PCI0.LPCB.SIO2.F2RN, Local0)
#endif
#if ASL_SMF_TYPE_SIO3_SUPPORT
      Add (Local0, \_SB.PCI0.LPCB.SIO3.F3RN, Local0)
#endif
#if ASL_SMF_TYPE_EC1_SUPPORT
      Add (Local0, \_SB.PCI0.LPCB.EC01.E1RN, Local0)
#endif
#if ASL_SMF_TYPE_EC2_SUPPORT
      Add (Local0, \_SB.PCI0.LPCB.EC02.E2RN, Local0)
#endif

      Return(Local0)
    }

    //---------------------------------------------------------------------------
    // Name: FCRS
    //
    // Description:  FAN controller return name string
    //   Arg0 : Index of controller to return name string
    //
    // Output:
    //   String - Name string of specified controller
    //   "NULL" - if not found
    //
    //---------------------------------------------------------------------------
    Method (FCRS, 1){
      Store (Arg0, Local0)  // Index
      Store (0, Local1)  // Supported number
      Store ("NULL", Local2)  // String to return

#if ASL_SMF_TYPE_OEM_SUPPORT
      // OEM controlling method can be implemented externally in project level.
      Store (ASL_OEM_SMF_RN_METHOD, Local1)
      If (LLessEqual(Local0, Local1)) {
        Store (ASL_OEM_SMF_FS_METHOD, Local2)
      } Else {
        Subtract (Local0, Local1, Local0)
      }
#endif
#if ASL_SMF_TYPE_SOC_SUPPORT
      // SoC SMF controlling method should be implemented externally in platform level.
      Store (\_SB.SFRN, Local1)
      If (LLessEqual(Local0, Local1)) {
        Store (\_SB.SFFS(Local0), Local2)
      } Else {
        Subtract (Local0, Local1, Local0)
      }
#endif
#if ASL_SMF_TYPE_SIO1_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO1.F1RN, Local1)
      If (LLessEqual(Local0, Local1)) {
        Store (\_SB.PCI0.LPCB.SIO1.F1FS(Local0), Local2)
      } Else {
        Subtract (Local0, Local1, Local0)
      }
#endif
#if ASL_SMF_TYPE_SIO2_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO2.F2RN, Local1)
      If (LLessEqual(Local0, Local1)) {
        Store (\_SB.PCI0.LPCB.SIO2.F2FS(Local0), Local2)
      } Else {
        Subtract (Local0, Local1, Local0)
      }
#endif
#if ASL_SMF_TYPE_SIO3_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO3.F3RN, Local1)
      If (LLessEqual(Local0, Local1)) {
        Store (\_SB.PCI0.LPCB.SIO3.F3FS(Local0), Local2)
      } Else {
        Subtract (Local0, Local1, Local0)
      }
#endif
#if ASL_SMF_TYPE_EC1_SUPPORT
      Store (\_SB.PCI0.LPCB.EC01.E1RN, Local1)
      If (LLessEqual(Local0, Local1)) {
        Store (\_SB.PCI0.LPCB.EC01.E1FS(Local0), Local2)
      } Else {
        Subtract (Local0, Local1, Local0)
      }
#endif
#if ASL_SMF_TYPE_EC2_SUPPORT
      Store (\_SB.PCI0.LPCB.EC02.E2RN, Local1)
      If (LLessEqual(Local0, Local1)) {
        Store (\_SB.PCI0.LPCB.EC02.E2FS(Local0), Local2)
      } Else {
        Subtract (Local0, Local1, Local0)
      }
#endif

      Return (Local2)
    }

    //---------------------------------------------------------------------------
    // Name: FCTS
    //
    // Description:  FAN controller return name string for target temperature
    //   Arg0 : String - FAN name to return
    //
    // Output:
    //   String - Name string of target temperature for specified controller
    //   "NULL" - if not found
    //
    //---------------------------------------------------------------------------
    Method (FCTS, 1){
      Store ("NULL", Local0)
#if ASL_SMF_TYPE_OEM_SUPPORT
      // OEM SMF controlling method can be implemented externally in project level.
      Store (ASL_OEM_SMF_TS_METHOD, Local0)
      If (LNotEqual(Local0, "NULL")) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SOC_SUPPORT
      // SoC SMF controlling method should be implemented externally in platform level.
      Store (\_SB.SFTS(Arg0), Local0)
      If (LNotEqual(Local0, "NULL")) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO1_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO1.F1TS(Arg0), Local0)
      If (LNotEqual(Local0, "NULL")) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO2_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO2.F2TS(Arg0), Local0)
      If (LNotEqual(Local0, "NULL")) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO3_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO3.F3TS(Arg0), Local0)
      If (LNotEqual(Local0, "NULL")) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_EC1_SUPPORT
      Store (\_SB.PCI0.LPCB.EC01.E1TS(Arg0), Local0)
      If (LNotEqual(Local0, "NULL")) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_EC2_SUPPORT
      Store (\_SB.PCI0.LPCB.EC02.E2TS(Arg0), Local0)
      If (LNotEqual(Local0, "NULL")) { Return (Local0) }
#endif
      Return (Local0)
    }

    //---------------------------------------------------------------------------
    // Name: FCTM
    //
    // Description:  FAN Controller return target Temp.
    //   Arg0 : String - FAN name to get
    //   Arg1 : Integer - Format :
    //     0 - Standard mapping
    //     1 - Flatten mapping
    //
    // Output:
    //   Integer - Temperature mapping value
    //   Data Buffer - String of target Temperature
    //
    //---------------------------------------------------------------------------
    Method (FCTM, 2){
      Store (0, Local0)  // Bitmap to return

      // Get target temperature
      Store (FCTS(Arg0), Local1)  // Temperature string
      If (LEqual(Local1, "NULL")) { Return (Local0) }
      Store (Local1, \_SB.BFPI.WDBF)  // Store to data buffer
      Store (0, Local2)  // Counter

      If (LEqual(Arg1, 0)) {
        // Standart mapping
        Store (SizeOf(TTHM), Local3)

        While (LLess(Local2, Local3)) {
          If (LEqual(Local1, DerefOf(Index(TTHM, Local2)))) {
            Or (Local0, ShiftLeft(0x01, Local2), Local0)
          }
          Increment (Local2)
        }
      } Else {
        // Flatten mapping
        Store (HMSN(0), Local3)

        While (LLess(Local2, Local3)) {
          If (LEqual(Local1, HMSS(0,Local2))) {
            Or (Local0, ShiftLeft(0x01, Local2), Local0)
          }
          Increment (Local2)
        }
      }

      Return(Local0)
    }

    //---------------------------------------------------------------------------
    // Name: FCRM
    //
    // Description:  FAN Controller return supported mode
    //   Arg0 : String - FAN name to get
    //
    // Output:
    //   Integer - Bitmap for supported mode
    //   ASL_BFPI_NOT_SUPPORTED - No matched FAN found
    //
    //---------------------------------------------------------------------------
    Method (FCRM, 1){
      Store (ASL_BFPI_NOT_SUPPORTED, Local0)  // Bitmap to return

#if ASL_SMF_TYPE_OEM_SUPPORT
      // OEM controlling method can be implemented externally in project level.
      Store (ASL_OEM_SMF_RM_METHOD, Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SOC_SUPPORT
      // SoC controlling method should be implemented externally in platform level.
      Store (\_SB.SFRM(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO1_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO1.F1RM(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO2_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO2.F2RM(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO3_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO3.F3RM(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_EC1_SUPPORT
      Store (\_SB.PCI0.LPCB.EC01.E1RM(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_EC2_SUPPORT
      Store (\_SB.PCI0.LPCB.EC02.E2RM(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif

      Return(Local0)
    }

    //---------------------------------------------------------------------------
    // Name: FCPW
    //
    // Description:  FAN Controller return Max. PWM value.
    //   Arg0 : String - FAN name to get
    //
    // Output:
    //   Integer - Max. PWM value supported. Ordinarily 100 or 255.
    //   ASL_BFPI_NOT_SUPPORTED - No matched FAN found
    //
    //---------------------------------------------------------------------------
    Method (FCPW, 1){
      Store (ASL_BFPI_NOT_SUPPORTED, Local0)  // Bitmap to return

#if ASL_SMF_TYPE_OEM_SUPPORT
      // OEM controlling method can be implemented externally in project level.
      Store (ASL_OEM_SMF_PW_METHOD, Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SOC_SUPPORT
      // SoC controlling method should be implemented externally in platform level.
      Store (\_SB.SFPW(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO1_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO1.F1PW(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO2_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO2.F2PW(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO3_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO3.F3PW(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_EC1_SUPPORT
      Store (\_SB.PCI0.LPCB.EC01.E1PW(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_EC2_SUPPORT
      Store (\_SB.PCI0.LPCB.EC02.E2PW(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif

      Return(Local0)
    }

    //---------------------------------------------------------------------------
    // Name: FCLP
    //
    // Description:  FAN Controller return Min. slope unit
    //   Arg0 : String - FAN name to get
    //
    // Output:
    //   Integer - Slope supported by FAN specified by Arg1.
    //     Bit0 : Slop type
    //       0 : Use Bit[7:4] and Bit[3:1] as step value
    //       1 : 2n, Bit[7:4] and Bit[3:1] are ignored.
    //            ex: 1, 2, 4, 8, 16... 2(n)
    //     Bit[3:1] : Digit part of step value
    //       0 : No digit part
    //       1~3: In form of 2-n. Ex: n=1: unit=0.5; n=2: unit=0.25...
    //       Others: reserved
    //     Bit[7:4] : Integer part of step value.
    //     Bit[15:8]: Max. slope value
    //     ASL_BFPI_NOT_SUPPORTED - No matched FAN found or slope-liear mode is not supported
    //
    //---------------------------------------------------------------------------
    Method (FCLP, 1){
      Store (ASL_BFPI_NOT_SUPPORTED, Local0)  // Bitmap to return

#if ASL_SMF_TYPE_OEM_SUPPORT
      // OEM controlling method can be implemented externally in project level.
      Store (ASL_OEM_SMF_LP_METHOD, Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SOC_SUPPORT
      // SoC controlling method should be implemented externally in platform level.
      Store (\_SB.SFLP(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO1_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO1.F1LP(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO2_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO2.F2LP(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO3_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO3.F3LP(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_EC1_SUPPORT
      Store (\_SB.PCI0.LPCB.EC01.E1LP(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_EC2_SUPPORT
      Store (\_SB.PCI0.LPCB.EC02.E2LP(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif

      Return(Local0)
    }

    //---------------------------------------------------------------------------
    // Name: FCRF
    //
    // Description:  SMF FAN Controller report functionality
    //   Arg0 : String - FAN name to get smart FAN functionality
    //
    // Output:
    //   According to sub-function.
    //
    //---------------------------------------------------------------------------
    Method (FCRF, 1){
      Store ("NULL", Local0)
#if ASL_SMF_TYPE_OEM_SUPPORT
      // OEM SMF controlling method can be implemented externally in project level.
      Store (ASL_OEM_SMF_RC_METHOD, Local0)
      If (LNotEqual(Local0, "NULL")) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SOC_SUPPORT
      // SoC SMF controlling method should be implemented externally in platform level.
      Store (\_SB.SFRC(Arg0), Local0)
      If (LNotEqual(Local0, "NULL")) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO1_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO1.F1RC(Arg0), Local0)
      If (LNotEqual(Local0, "NULL")) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO2_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO2.F2RC(Arg0), Local0)
      If (LNotEqual(Local0, "NULL")) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO3_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO3.F3RC(Arg0), Local0)
      If (LNotEqual(Local0, "NULL")) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_EC1_SUPPORT
      Store (\_SB.PCI0.LPCB.EC01.F1RC(Arg0), Local0)
      If (LNotEqual(Local0, "NULL")) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_EC2_SUPPORT
      Store (\_SB.PCI0.LPCB.EC02.E2RC(Arg0), Local0)
      If (LNotEqual(Local0, "NULL")) { Return (Local0) }
#endif
      Return (Local0)
    }

    //---------------------------------------------------------------------------
    // Name: FCGM
    //
    // Description:  SMF FAN control get mode
    //   Arg0 : IIA0, SMF index to get.
    //   Arg1 : IIA1, Basically not used.
    //
    // Output:
    //   Integer :
    //     Bit[3:0]: Fan Mode
    //       0 - Manual mode
    //       1 - Linear mode (Point-Linear mode)
    //       2 - Slope-Linear mode
    //     Bit[7:4]: Reserved Bits
    //     Bit[15:8]: (valid only for manual mode) PWM value for manual mode
    //     BFPI_NOT_SUPPORTED : No matched fan found.
    //
    //---------------------------------------------------------------------------
    Method (FCGM, 2){
      Store ("NULL", Local0)  // FAN string
      And (Arg0, 0xF, Local1) // [3:0] - SMF index to operate
      And (ShiftRight(Arg0,4), 0x1, Local2) // [4] - SMF Index format

      Store (FCIS(Local1, Local2), Local0)

      Return (AFGM(Local0))
    }

    //---------------------------------------------------------------------------
    // Name: AFGM
    //
    // Description:  AAEON FAN control get mode
    //   Arg0 : SMF name to get
    //
    // Output:
    //   Integer :
    //     Bit[3:0]: Fan Mode
    //       0 - Manual mode
    //       1 - Linear mode (Point-Linear mode)
    //       2 - Slope-Linear mode
    //     Bit[7:4]: Reserved Bits
    //     Bit[15:8]: (valid only for manual mode) PWM value for manual mode
    //     BFPI_NOT_SUPPORTED : No matched fan found.
    //
    //---------------------------------------------------------------------------
    Method (AFGM, 1) {
      Store (ASL_BFPI_NOT_SUPPORTED, Local0)
#if ASL_SMF_TYPE_OEM_SUPPORT
      // OEM SMF controlling method can be implemented externally in project level.
      Store (ASL_OEM_SMF_GM_METHOD, Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SOC_SUPPORT
      // SoC SMF controlling method should be implemented externally in platform level.
      Store (\_SB.SFGM(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO1_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO1.F1GM(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO2_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO2.F2GM(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO3_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO3.F3GM(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_EC1_SUPPORT
      Store (\_SB.PCI0.LPCB.EC01.E1GM(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_EC2_SUPPORT
      Store (\_SB.PCI0.LPCB.EC02.E2GM(Arg0), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
      Return (Local0)
    }

    //---------------------------------------------------------------------------
    // Name: FCSM
    //
    // Description:  SMF FAN control set mode
    //   Arg0 : IIA0, SMF index to set.
    //   Arg1 : IIA1, Basically not used.
    //
    // Output:
    //   BFPI_STATUS
    //
    //---------------------------------------------------------------------------
    Method (FCSM, 2){
      Store ("NULL", Local0)  // FAN string
      And (Arg0, 0xF, Local1) // [3:0] - SMF index to operate
      And (ShiftRight(Arg0,4), 0xF, Local2) // [7:4] - SMF mode to set
      And (ShiftRight(Arg0,16), 0xFF, Local3) // [23:16] - SMF Manual PWM to set
      And (ShiftRight(Arg0,8), 0x1, Local4) // [8] - SMF Index format

      Store (FCIS(Local1, Local4), Local0)

      Return (AFSM(Local0, Local2, Local3))
    }

    //---------------------------------------------------------------------------
    // Name: AFSM
    //
    // Description:  AAEON FAN control set mode
    //   Arg0 : SMF name to set
    //   Arg1 : SMF mode to set
    //       0 - Manual mode
    //       1 - Linear mode (Point-Linear mode)
    //       2 - Slope-Linear mode
    //   Arg2 : (valid only for manual mode) PWM value for manual mode
    //
    // Output:
    //   BFPI_STATUS
    //
    //---------------------------------------------------------------------------
    Method (AFSM, 3){
      Store (ASL_BFPI_NOT_SUPPORTED, Local0)
#if ASL_SMF_TYPE_OEM_SUPPORT
      // OEM SMF controlling method can be implemented externally in project level.
      Store (ASL_OEM_SMF_SM_METHOD, Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SOC_SUPPORT
      // SoC SMF controlling method should be implemented externally in platform level.
      Store (\_SB.SFSM(Arg0, Arg1, Arg2), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO1_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO1.F1SM(Arg0, Arg1, Arg2), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO2_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO2.F2SM(Arg0, Arg1, Arg2), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO3_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO3.F3SM(Arg0, Arg1, Arg2), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_EC1_SUPPORT
      Store (\_SB.PCI0.LPCB.EC01.E1SM(Arg0, Arg1, Arg2), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_EC2_SUPPORT
      Store (\_SB.PCI0.LPCB.EC02.E2SM(Arg0, Arg1, Arg2), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
      Return (ASL_BFPI_NOT_SUPPORTED)
    }

    //---------------------------------------------------------------------------
    // Name: FCGP
    //
    // Description:  SMF FAN control get control point configuration
    //   Arg0 : IIA0, SMF index to get.
    //   Arg1 : IIA1, Basically not used.
    //
    // Output:
    //   Same as AFGP
    //
    //---------------------------------------------------------------------------
    Method (FCGP, 2){
      Store ("NULL", Local0)  // FAN string
      And (Arg0, 0xF, Local1) // [3:0] - SMF index to operate
      And (ShiftRight(Arg0,4), 0xF, Local2) // [7:4] - SMF Control point number
      And (ShiftRight(Arg0,8), 0x1, Local3) // [8] - SMF Index format

      Store (FCIS(Local1, Local3), Local0)

      Return (AFGP(Local0, Local2))
    }

    //---------------------------------------------------------------------------
    // Name: AFGP
    //
    // Description:  AAEON FAN control get control point configuration
    //   Arg0 : SMF name to get
    //   Arg1 : control point to get
    //     For Linear mode (Point-Linear mode) -
    //       0 - lowest point
    //       1 - highest point
    //       2 - secondary low point
    //       3 - third low point
    //     ...
    //     For Slope-Linear mode -
    //       0 - lowest point
    //       1 - highest point
    //       2 - Slope
    //       3 - third low point
    //       ...
    //
    // Output:
    //   Integer :
    //     For Temp. point -
    //       Bit[7:0]: DutyCycle coordinate for this pont
    //         0 - 0% duty
    //         X - (X/Max)% duty
    //         Max - 100% duty
    //       Bit[15:8]: Temperature coordinate for this pont
    //     For Slope -
    //       Bit[7:0]: Digit part after point, of slope. in 1/256
    //       Bit[15:8]: Integer part of slope
    //     BFPI_NOT_SUPPORTED: No FAN matches name provided.
    //
    //---------------------------------------------------------------------------
    Method (AFGP, 2) {
      Store (ASL_BFPI_NOT_SUPPORTED, Local0)
#if ASL_SMF_TYPE_OEM_SUPPORT
      // OEM SMF controlling method can be implemented externally in project level.
      Store (ASL_OEM_SMF_GP_METHOD, Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SOC_SUPPORT
      // SoC SMF controlling method should be implemented externally in platform level.
      Store (\_SB.SFGP(Arg0, Arg1), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO1_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO1.F1GP(Arg0, Arg1), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO2_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO2.F2GP(Arg0, Arg1), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO3_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO3.F3GP(Arg0, Arg1), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_EC1_SUPPORT
      Store (\_SB.PCI0.LPCB.EC01.E1GP(Arg0, Arg1), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_EC2_SUPPORT
      Store (\_SB.PCI0.LPCB.EC02.E2GP(Arg0, Arg1), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
      Return (ASL_BFPI_NOT_SUPPORTED)
    }

    //---------------------------------------------------------------------------
    // Name: FCSP
    //
    // Description:  SMF FAN control set control point configuration
    //   Arg0 : IIA0, SMF index to set.
    //   Arg1 : IIA1, Basically not used.
    //
    // Output:
    //   BFPI_STATUS
    //
    //---------------------------------------------------------------------------
    Method (FCSP, 2){
      Store ("NULL", Local0)  // FAN string
      And (Arg0, 0xF, Local1) // [3:0] - SMF index to operate
      And (ShiftRight(Arg0,4), 0xF, Local2) // [7:4] - SMF Control point number
      And (ShiftRight(Arg0,8), 0xFF, Local3) // [15:8] - SMF PWM coordinate or digit part of slope
      And (ShiftRight(Arg0,16), 0xFF, Local4) // [23:16] - SMF Temperature coordinate or integer part of slope
      And (ShiftRight(Arg0,24), 0x01, Local5) // [24] - SMF index format

      Store (FCIS(Local1, Local5), Local0)

      Return (AFSP(Local0, Local2, Local3, Local4))
    }

    //---------------------------------------------------------------------------
    // Name: AFSP
    //
    // Description:  AAEON FAN control set control point configuration
    //   Arg0 : SMF name to set
    //   Arg1 : control point to configre
    //     For Linear mode (Point-Linear mode) -
    //       0 - lowest point
    //       1 - highest point
    //       2 - secondary low point
    //       3 - third low point
    //     ...
    //     For Slope-Linear mode -
    //       0 - lowest point
    //       1 - highest point
    //       2 - Slope
    //       3 - third low point
    //       ...
    //   For points
    //     Arg2 : DutyCycle coordinate for this pont
    //       0 - 0% duty
    //       X - (X/Max)% duty
    //       Max - 100% duty
    //     Arg3 : Temperature coordinate for this pont
    //   For Slope configuration -
    //     Arg2 : Digit part after point, of slope to set. in 1/256
    //     Arg3 : Integer part of slope to set.
    //
    // Output:
    //   BFPI_STATUS
    //
    //---------------------------------------------------------------------------
    Method (AFSP, 4){
      Store (ASL_BFPI_NOT_SUPPORTED, Local0)
#if ASL_SMF_TYPE_OEM_SUPPORT
      // OEM SMF controlling method can be implemented externally in project level.
      Store (ASL_OEM_SMF_SP_METHOD, Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SOC_SUPPORT
      // SoC SMF controlling method should be implemented externally in platform level.
      Store (\_SB.SFSP(Arg0, Arg1, Arg2, Arg3), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO1_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO1.F1SP(Arg0, Arg1, Arg2, Arg3), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO2_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO2.F2SP(Arg0, Arg1, Arg2, Arg3), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_SIO3_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO3.F3SP(Arg0, Arg1, Arg2, Arg3), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_EC1_SUPPORT
      Store (\_SB.PCI0.LPCB.EC01.E1SP(Arg0, Arg1, Arg2, Arg3), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
#if ASL_SMF_TYPE_EC2_SUPPORT
      Store (\_SB.PCI0.LPCB.EC02.E2SP(Arg0, Arg1, Arg2, Arg3), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
#endif
      Return (ASL_BFPI_NOT_SUPPORTED)
    }

  }  // Scope(\_SB.BFPI)
#endif