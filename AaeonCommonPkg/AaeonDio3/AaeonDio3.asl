#ifndef ASL_BFPI_SUCCESS
    #define ASL_BFPI_SUCCESS 0
#endif
#ifndef ASL_BFPI_NOT_SUPPORTED
    #define ASL_BFPI_NOT_SUPPORTED 0xFFFFFFFF
#endif
#ifndef ASL_BFPI_INVALID_PARAMETER
    #define ASL_BFPI_INVALID_PARAMETER 0xFFFFFFFE
#endif

Scope(\_SB) {
  Device(ADIO) {
    Name(_HID, "AANT1100")       // Defined in \\Nas5\_Document\UEFI ACPI ID.xlsx
    Name(_UID, "1")
    Name(_DDN, "AAEON DIO Controller")

    OperationRegion(WDCB, SystemMemory, 0xFFFF0000, 0x800)  // BFPI DIO Capability Buffer. Address will be updated in AaeonDioDxe2.c
    Field(WDCB, AnyAcc, NoLock, Preserve)
    {
      DCBA, 32,    //Offset 0   // DIO Capability Buffer Address
      INTA, 1,     //Offset 4   // Interrupt enabled
      Offset (8),
      DINC, 128,   //Offset 8   // DIO Input Capability for pin 1~128
      DOPC, 128,   //Offset 24  // DIO Output Capability for pin 1~128
      DDRC, 128,   //Offset 40  // DIO Driving Capability for pin 1~128
      DITC, 128,   //Offset 56  // DIO Interrupt Capability for pin 1~128
      DIC1, 32,    //Offset 72  // 1st DIO Source IC
      DMP1, 1024,  //Offset 76  // 1st DIO GPIO mapping
      DIC2, 32,    //Offset 204 // 2nd DIO Source IC
      DMP2, 1024   //Offset 208 // 2nd DIO GPIO mapping
      // TODO: Porting may be required if 3rd DIO controller is supported.
      #if defined(THIRD_DIO_NUMBER) && (THIRD_DIO_NUMBER > 0)
      DIC3, 32,    //Offset 336 // 3rd DIO Source IC
      DMP3, 1024   //Offset 340 // 3rd DIO GPIO mapping
      #endif
    }

    Method (_STA) {
        If (LEqual (INTA, 1)) { 
          Return (0x0F)  // When enabled, device should be shown and installed with driver.
        } Else { 
          Return (0x0B)  // When disabled, device should be hidden.
        }
    }

    //===========================================================================
    //---------------------------------------------------------------------------
    // Name: DIOO
    //
    // Description:  DIO Operation
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
    Method (DIOO, 3){
      If (LEqual(Arg0, 0x0000)) {  // Report capability
        Return(DGRC(Arg1, Arg2))
      }
      If (LEqual(Arg0, 0x0001)) {  // Get Digital I/O Level
        Return(DGGL(Arg1, Arg2))
      }
      If (LEqual(Arg0, 0x0002)) {  // Set Digital I/O Level
        Return(DGSL(Arg1, Arg2))
      }
      If (LEqual(Arg0, 0x0003)) {  // Get Digital I/O Direction
        Return(DGGD(Arg1, Arg2))
      }
      If (LEqual(Arg0, 0x0004)) {  // Set Digital I/O Direction
        Return(DGSD(Arg1, Arg2))
      }
      If (LEqual(Arg0, 0x0005)) {  // Get Digital I/O Driving
        Return(DGGO(Arg1, Arg2))
      }
      If (LEqual(Arg0, 0x0006)) {  // Set Digital I/O Driving
        Return(DGSO(Arg1, Arg2))
      }
      Return(ASL_BFPI_INVALID_PARAMETER)
    }

    //---------------------------------------------------------------------------
    // Name: DGRC
    //
    // Description:  Digital I/O report capability
    //   Arg0 : IIA0, Select capability data to return
    //   Arg1 : IIA1, Basically not used.
    //
    // Output:
    //   According to sub-function.
    //
    //---------------------------------------------------------------------------
    Method (DGRC, 2){
      Name(BUFF, Buffer(16) {0x0})

      And (Arg0, 0xFF, Local0) // Input: Interger - Select capability data to return
      ShiftRight (And(Arg0,0xF0000), 16, Local1) // Input: Interger - Select which bank of data to return

      #if ASL_AAEON_BFPI_SUPPORT
      If (LEqual(Local0, 0x00)) {  // Report capability in JSON format
        Store (DIOC, \_SB.BFPI.WDBF)
        Return (ASL_BFPI_SUCCESS)
      }
      #endif
      If (LEqual(Local0, 0x01)) {  // Return DIO Capability Buffer Address
        Return (DCBA)
      }
      If (LEqual(Local0, 0x10)) {  // Supported DIO pin number
        Return (ASL_DIO_TOTAL_NUMBER)
      }
      If (LEqual(Local0, 0x11)) {  // Supported GPIO Input Bit Map
        // DINC
        Store (DINC, BUFF)
        CreateDWordField (BUFF, Multiply (Local1, 4), GIBM)
        Return (GIBM)
      }
      If (LEqual(Local0, 0x12)) {  // Supported GPIO Output Bit Map
        // DOPC
        Store (DOPC, BUFF)
        CreateDWordField (BUFF, Multiply (Local1, 4), GOBM)
        Return (GOBM)
      }
      If (LEqual(Local0, 0x13)) {  // Supported GPIO Driving Bit Map
        // DDRC
        Store (DDRC, BUFF)
        CreateDWordField (BUFF, Multiply (Local1, 4), GDBM)
        Return (GDBM)
      }
      If (LEqual(Local0, 0x14)) {  // Supported GPIO Interrupt Bit Map
        // DITC
        Store (DITC, BUFF)
        CreateDWordField (BUFF, Multiply (Local1, 4), GTBM)
        Return (GTBM)
      }
      Return(ASL_BFPI_INVALID_PARAMETER)
    }

    //---------------------------------------------------------------------------
    // Name: DGPI
    //
    // Description:  Digital I/O Get Pin Information
    //   Arg0 : IIA0, Pin number to get
    //
    // Output:
    //   Buffer:
    //   Offset 0 - DIO Chip Type
    //   Offset 1 - DIO Pin map
    //   ASL_BFPI_INVALID_PARAMETER
    //
    //---------------------------------------------------------------------------
    Method (DGPI, 1) {
      Name (BUFF, Buffer(32) {0x0})
      Name (RBUF, Buffer(2) {0x0})
      If (LLessEqual(Arg0, ASL_DIO_END_NUMBER)) {
        Store (DIC1, Local0)
        Store (DMP1, BUFF)
        Store (Arg0, Local2)
      }
      ElseIf (LLessEqual(Arg0, ASL_SECOND_DIO_END_NUMBER)) {
        Store (DIC2, Local0)
        Store (DMP2, BUFF)
        Subtract(Arg0, Add(ASL_DIO_END_NUMBER,1), Local2)
      }
      // TODO: Porting may required if there is 3rd DIO controller
      #if defined(THIRD_DIO_NUMBER) && (THIRD_DIO_NUMBER > 0)
      ElseIf (LLessEqual(Arg0, ASL_3rd_DIO_END_NUMBER)) {
        Subtract(Arg0, Add(ASL_SECOND_DIO_END_NUMBER,1), Local2)
        Store (DIC3, Local0)
        Store (DMP3, BUFF)
      }
      #endif
      Else {
        Return (Buffer(2){0xFF})
      }
      Store (DerefOf (Index (BUFF, Local2)), Local1)
      Store (Local0, Index (RBUF, 0))
      Store (Local1, Index (RBUF, 1))
      Return (RBUF)
    }

    //===========================================================================
    //---------------------------------------------------------------------------
    // Name: DGGL
    //
    // Description:  Digital I/O Get Level
    //   Arg0 : IIA0, Pin number to get
    //   Arg1 : IIA1, Basically not used.
    //
    // Output:
    //   Interger:
    //   0 - Low level
    //   1 - High level
    //   ASL_BFPI_INVALID_PARAMETER - GPIO number is invalid
    //
    //---------------------------------------------------------------------------
    Method (DGGL, 2){
      If (LGreaterEqual(Arg0, ASL_DIO_TOTAL_NUMBER)) { Return(ASL_BFPI_INVALID_PARAMETER) }
      Name (BUFF, Buffer(2) {0x0})
      Store (DGPI(Arg0), BUFF)

      // Buff 0 : DIO Chip type
      // Buff 1 : DIO Pin map
      Store (DerefOf (Index (BUFF, 0)), Local0)
      Store (DerefOf (Index (BUFF, 1)), Local1)
      Return(AGGL(Local0, Local1))
    }

    //---------------------------------------------------------------------------
    // Name: AGGL
    //
    // Description:  AAEON GPIO Get Level
    //   Arg0 : GPIO Chip Type
    //   Arg1 : GPIO Number to get level
    //
    // Output:
    //   Interger:
    //   0 - Low level
    //   1 - High level
    //   ASL_BFPI_INVALID_PARAMETER
    //
    //---------------------------------------------------------------------------
    Method (AGGL, 2) {
      #if ASL_DIO_TYPE_OEM_SUPPORT
      // OEM GPIO controlling method can be implemented externally in project level.
      If (LEqual (Arg0, ASL_DIO_TYPE_OEM)) {
        // ASL_OEM_DIO_GL_METHOD should contain (Arg1). EX: \_SB.ODIO.ODGL(Arg1)
        Return (ASL_OEM_DIO_GL_METHOD)
      }
      #endif
      #if ASL_DIO_TYPE_SOC_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SOC)) {
        // SoC GPIO controlling method should be implemented externally in platform level.
        Return (\_SB.SCGL(Arg1))
      }
      #endif
      #if ASL_DIO_TYPE_SIO1_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SIO1)) {
        Return (\_SB.PCI0.LPCB.SIO1.D1GL(Arg1))
      }
      #endif
      #if ASL_DIO_TYPE_SIO2_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SIO2)) {
        Return (\_SB.PCI0.LPCB.SIO2.D2GL(Arg1))
      }
      #endif
      #if ASL_DIO_TYPE_SIO3_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SIO3)) {
        Return (\_SB.PCI0.LPCB.SIO.D3GL(Arg1))
      }
      #endif
      #if ASL_DIO_TYPE_EC1_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_EC1)) {
        Return (\_SB.PCI0.LPCB.EC01.E1GL(Arg1))
      }
      #endif
      #if ASL_DIO_TYPE_EC2_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_EC2)) {
        Return (\_SB.PCI0.LPCB.EC02.E2GL(Arg1))
      }
      #endif
      #if ASL_DIO_TYPE_SMBUS_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SMBUS)) {
        Return (\_SB.SMGL(Arg1))
      }
      #endif
      Return (ASL_BFPI_INVALID_PARAMETER)
    }

    //---------------------------------------------------------------------------
    // Name: DGSL
    //
    // Description:  Digital I/O Set Level
    //   Arg0 : IIA0,
    //            [7:0] - Pin number to Set
    //            [15:8] - Level to set
    //              0 - Low level
    //              1 - High level
    //   Arg1 : IIA1, Basically not used.
    //
    // Output:
    //   ASL_BFPI_SUCCESS
    //   ASL_BFPI_INVALID_PARAMETER - Either GPIO number or level to set is invalid
    //
    //---------------------------------------------------------------------------
    Method (DGSL, 2){
      And (Arg0, 0xFFFF, Local0) // [15:0] - Pin number to Set
      ShiftRight (And(Arg0,0x1FFFF), 16, Local2) // [16] - Level to set
      If (LGreaterEqual(Local0, ASL_DIO_TOTAL_NUMBER)) { Return(ASL_BFPI_INVALID_PARAMETER) }
      If (LGreater(Local2,1)) { Return(ASL_BFPI_INVALID_PARAMETER) }

      Name (BUFF, Buffer(2) {0x0})
      Store (DGPI(Local0), BUFF)

      // Buff 0 : DIO Chip type
      // Buff 1 : DIO Pin map
      Store (DerefOf (Index (BUFF, 0)), Local0)
      Store (DerefOf (Index (BUFF, 1)), Local1)
      Return(AGSL(Local0, Local1, Local2))
    }

    //---------------------------------------------------------------------------
    // Name: AGSL
    //
    // Description:  AAEON GPIO Set Level
    //   Arg0 : GPIO Chip Type
    //   Arg1 : GPIO Number to set level
    //   Arg2 : Level to set
    //     0 - Low level
    //     1 - High level
    //
    // Output:
    //   BFPI_STATUS
    //
    //---------------------------------------------------------------------------
    Method (AGSL, 3){
      #if ASL_DIO_TYPE_OEM_SUPPORT
      // OEM GPIO controlling method can be implemented externally in project level.
      If (LEqual (Arg0, ASL_DIO_TYPE_OEM)) {
        // ASL_OEM_DIO_SL_METHOD should contain (Arg1, Arg2). EX: \_SB.ODIO.ODSL(Arg1, Arg2)
        Return (ASL_OEM_DIO_SL_METHOD)
      }
      #endif
      #if ASL_DIO_TYPE_SOC_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SOC)) {
        // SoC GPIO controlling method should be implemented externally in platform level.
        Return (\_SB.SCSL(Arg1, Arg2))
      }
      #endif
      #if ASL_DIO_TYPE_SIO1_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SIO1)) {
        Return (\_SB.PCI0.LPCB.SIO1.D1SL(Arg1, Arg2))
      }
      #endif
      #if ASL_DIO_TYPE_SIO2_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SIO2)) {
        Return (\_SB.PCI0.LPCB.SIO2.D2SL(Arg1, Arg2))
      }
      #endif
      #if ASL_DIO_TYPE_SIO3_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SIO3)) {
        Return (\_SB.PCI0.LPCB.SIO.D3SL(Arg1, Arg2))
      }
      #endif
      #if ASL_DIO_TYPE_EC1_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_EC1)) {
        Return (\_SB.PCI0.LPCB.EC01.E1SL(Arg1, Arg2))
      }
      #endif
      #if ASL_DIO_TYPE_EC2_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_EC2)) {
        Return (\_SB.PCI0.LPCB.EC02.E2SL(Arg1, Arg2))
      }
      #endif
      #if ASL_DIO_TYPE_SMBUS_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SMBUS)) {
        Return (\_SB.SMSL(Arg1, Arg2))
      }
      #endif
      Return(ASL_BFPI_INVALID_PARAMETER)
    }

    //===========================================================================
    //---------------------------------------------------------------------------
    // Name: DGGD
    //
    // Description:  Digital I/O Get Direction
    //   Arg0 : IIA0, Pin number to get
    //   Arg1 : IIA1, Basically not used.
    //
    // Output:
    //   Interger:
    //   0 - Output
    //   1 - Input
    //   ASL_BFPI_INVALID_PARAMETER - GPIO number is invalid
    //
    //---------------------------------------------------------------------------
    Method (DGGD, 2){
      If (LGreaterEqual(Arg0, ASL_DIO_TOTAL_NUMBER)) { Return(ASL_BFPI_INVALID_PARAMETER) }
      Name (BUFF, Buffer(2) {0x0})
      Store (DGPI(Arg0), BUFF)

      // Buff 0 : DIO Chip type
      // Buff 1 : DIO Pin map
      Store (DerefOf (Index (BUFF, 0)), Local0)
      Store (DerefOf (Index (BUFF, 1)), Local1)
      Return(AGGD(Local0, Local1))
    }

    //---------------------------------------------------------------------------
    // Name: AGGD
    //
    // Description:  AAEON GPIO Get Direction
    //   Arg0 : GPIO Chip Type
    //   Arg1 : GPIO Number to get Direction
    //
    // Output:
    //   Interger:
    //   0 - Output
    //   1 - Input
    //   ASL_BFPI_INVALID_PARAMETER
    //
    //---------------------------------------------------------------------------
    Method (AGGD, 2) {
      #if ASL_DIO_TYPE_OEM_SUPPORT
      // OEM GPIO controlling method can be implemented externally in project level.
      If (LEqual (Arg0, ASL_DIO_TYPE_OEM)) {
        // ASL_OEM_DIO_GD_METHOD should contain (Arg1). EX: \_SB.ODIO.ODGD(Arg1)
        Return (ASL_OEM_DIO_GD_METHOD)
      }
      #endif
      #if ASL_DIO_TYPE_SOC_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SOC)) {
        // SoC GPIO controlling method should be implemented externally in platform level.
        Return (\_SB.SCGD(Arg1))
      }
      #endif
      #if ASL_DIO_TYPE_SIO1_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SIO1)) {
        Return (\_SB.PCI0.LPCB.SIO1.D1GD(Arg1))
      }
      #endif
      #if ASL_DIO_TYPE_SIO2_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SIO2)) {
        Return (\_SB.PCI0.LPCB.SIO2.D2GD(Arg1))
      }
      #endif
      #if ASL_DIO_TYPE_SIO3_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SIO3)) {
        Return (\_SB.PCI0.LPCB.SIO.D3GD(Arg1))
      }
      #endif
      #if ASL_DIO_TYPE_EC1_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_EC1)) {
        Return (\_SB.PCI0.LPCB.EC01.E1GD(Arg1))
      }
      #endif
      #if ASL_DIO_TYPE_EC2_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_EC2)) {
        Return (\_SB.PCI0.LPCB.EC02.E2GD(Arg1))
      }
      #endif
      #if ASL_DIO_TYPE_SMBUS_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SMBUS)) {
        Return (\_SB.SMGD(Arg1))
      }
      #endif
      Return (ASL_BFPI_INVALID_PARAMETER)
    }

    //---------------------------------------------------------------------------
    // Name: DGSD
    //
    // Description:  Digital I/O Set Direction
    //   Arg0 : IIA0,
    //            [7:0] - Pin number to Set
    //            [15:8] - Direction to set
    //              0 - Output
    //              1 - Input
    //   Arg1 : IIA1, Basically not used.
    //
    // Output:
    //   ASL_BFPI_SUCCESS
    //   ASL_BFPI_INVALID_PARAMETER - Either GPIO number or direction to set is invalid
    //
    //---------------------------------------------------------------------------
    Method (DGSD, 2){
      And (Arg0, 0xFFFF, Local0) // [15:0] - Pin number to Set
      ShiftRight (And(Arg0,0x1FFFF), 16, Local2) // [16] - Direction to set
      If (LGreaterEqual(Local0, ASL_DIO_TOTAL_NUMBER)) { Return(ASL_BFPI_INVALID_PARAMETER) }
      If (LGreater(Local2,1)) { Return(ASL_BFPI_INVALID_PARAMETER) }

      Name (BUFF, Buffer(2) {0x0})
      Store (DGPI(Local0), BUFF)

      // Buff 0 : DIO Chip type
      // Buff 1 : DIO Pin map
      Store (DerefOf (Index (BUFF, 0)), Local0)
      Store (DerefOf (Index (BUFF, 1)), Local1)
      Return(AGSD(Local0, Local1, Local2))
    }

    //---------------------------------------------------------------------------
    // Name: AGSD
    //
    // Description:  AAEON GPIO Set Direction
    //   Arg0 : GPIO Chip Type
    //   Arg1 : GPIO Number to set Direction
    //   Arg2 : Direction to set
    //     0 - Output
    //     1 - Input
    //
    // Output:
    //   BFPI_STATUS
    //
    //---------------------------------------------------------------------------
    Method (AGSD, 3){
      #if ASL_DIO_TYPE_OEM_SUPPORT
      // OEM GPIO controlling method can be implemented externally in project level.
      If (LEqual (Arg0, ASL_DIO_TYPE_OEM)) {
        // ASL_OEM_DIO_SD_METHOD should contain (Arg1, Arg2). EX: \_SB.ODIO.ODSD(Arg1, Arg2)
        Return (ASL_OEM_DIO_SD_METHOD)
      }
      #endif
      #if ASL_DIO_TYPE_SOC_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SOC)) {
        // SoC GPIO controlling method should be implemented externally in platform level.
        Return (\_SB.SCSD(Arg1, Arg2))
      }
      #endif
      #if ASL_DIO_TYPE_SIO1_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SIO1)) {
        Return (\_SB.PCI0.LPCB.SIO1.D1SD(Arg1, Arg2))
      }
      #endif
      #if ASL_DIO_TYPE_SIO2_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SIO2)) {
        Return (\_SB.PCI0.LPCB.SIO2.D2SD(Arg1, Arg2))
      }
      #endif
      #if ASL_DIO_TYPE_SIO3_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SIO3)) {
        Return (\_SB.PCI0.LPCB.SIO.D3SD(Arg1, Arg2))
      }
      #endif
      #if ASL_DIO_TYPE_EC1_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_EC1)) {
        Return (\_SB.PCI0.LPCB.EC01.E1SD(Arg1, Arg2))
      }
      #endif
      #if ASL_DIO_TYPE_EC2_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_EC2)) {
        Return (\_SB.PCI0.LPCB.EC02.E2SD(Arg1, Arg2))
      }
      #endif
      #if ASL_DIO_TYPE_SMBUS_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SMBUS)) {
        Return (\_SB.SMSD(Arg1, Arg2))
      }
      #endif
      Return(ASL_BFPI_INVALID_PARAMETER)
    }

    //===========================================================================
    //---------------------------------------------------------------------------
    // Name: DGGO
    //
    // Description:  Digital I/O Get Driving
    //   Arg0 : IIA0, Pin number to get
    //   Arg1 : IIA1, Basically not used.
    //
    // Output:
    //   Interger:
    //     0: Open drain
    //     1: Push pull / Internal pull-up 20K
    //     2: Internal pull-up 10K
    //     3: Internal pull-up 5K
    //     4: Internal pull-up 1K
    //   ASL_BFPI_INVALID_PARAMETER - GPIO number is invalid
    //
    //---------------------------------------------------------------------------
    Method (DGGO, 2){
      If (LGreaterEqual(Arg0, ASL_DIO_TOTAL_NUMBER)) { Return(ASL_BFPI_INVALID_PARAMETER) }
      Name (BUFF, Buffer(2) {0x0})
      Store (DGPI(Arg0), BUFF)

      // Buff 0 : DIO Chip type
      // Buff 1 : DIO Pin map
      Store (DerefOf (Index (BUFF, 0)), Local0)
      Store (DerefOf (Index (BUFF, 1)), Local1)
      Return(AGGO(Local0, Local1))
    }

    //---------------------------------------------------------------------------
    // Name: AGGO
    //
    // Description:  AAEON GPIO Get Driving
    //   Arg0 : GPIO Chip Type
    //   Arg1 : GPIO Number to get Driving
    //
    // Output:
    //   Interger:
    //     0: Open drain
    //     1: Push pull / Internal pull-up 20K
    //     2: Internal pull-up 10K
    //     3: Internal pull-up 5K
    //     4: Internal pull-up 1K
    //   ASL_BFPI_INVALID_PARAMETER
    //
    //---------------------------------------------------------------------------
    Method (AGGO, 2) {
      #if ASL_DIO_TYPE_OEM_SUPPORT
      // OEM GPIO controlling method can be implemented externally in project level.
      If (LEqual (Arg0, ASL_DIO_TYPE_OEM)) {
        // ASL_OEM_DIO_GO_METHOD should contain (Arg1). EX: \_SB.ODIO.ODGO(Arg1)
        Return (ASL_OEM_DIO_GO_METHOD)
      }
      #endif
      #if ASL_DIO_TYPE_SOC_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SOC)) {
        // SoC GPIO controlling method should be implemented externally in platform level.
        Return (\_SB.SCGO(Arg1))
      }
      #endif
      #if ASL_DIO_TYPE_SIO1_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SIO1)) {
        Return (\_SB.PCI0.LPCB.SIO1.D1GO(Arg1))
      }
      #endif
      #if ASL_DIO_TYPE_SIO2_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SIO2)) {
        Return (\_SB.PCI0.LPCB.SIO2.D2GO(Arg1))
      }
      #endif
      #if ASL_DIO_TYPE_SIO3_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SIO3)) {
        Return (\_SB.PCI0.LPCB.SIO.D3GO(Arg1))
      }
      #endif
      #if ASL_DIO_TYPE_EC1_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_EC1)) {
        Return (\_SB.PCI0.LPCB.EC01.E1GO(Arg1))
      }
      #endif
      #if ASL_DIO_TYPE_EC2_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_EC2)) {
        Return (\_SB.PCI0.LPCB.EC02.E2GO(Arg1))
      }
      #endif
      #if ASL_DIO_TYPE_SMBUS_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SMBUS)) {
        Return (\_SB.SMGO(Arg1))
      }
      #endif
      Return (ASL_BFPI_INVALID_PARAMETER)
    }

    //---------------------------------------------------------------------------
    // Name: DGSO
    //
    // Description:  Digital I/O Set Driving
    //   Arg0 : IIA0,
    //            [7:0] - Pin number to Set
    //            [20:16] - Driving to set
    //              0: Open drain
    //              1: Push pull / Internal pull-up 20K
    //              2: Internal pull-up 10K
    //              3: Internal pull-up 5K
    //              4: Internal pull-up 1K
    //   Arg1 : IIA1, Basically not used.
    //
    // Output:
    //   ASL_BFPI_SUCCESS
    //   ASL_BFPI_INVALID_PARAMETER - Either GPIO number or driving to set is invalid
    //
    // Note:
    //   If the hardware implementation of GPIO does not support selected
    //   driving level, next lower level is selected. (1K > 2K ... > 20K)
    //
    //---------------------------------------------------------------------------
    Method (DGSO, 2){
      And (Arg0, 0xFFFF, Local0) // [15:0] - Pin number to Set
      And (ShiftRight(Arg0, 16), 0xF, Local2) // [20:16] - Driving to set
      If (LGreaterEqual(Local0, ASL_DIO_TOTAL_NUMBER)) { Return(ASL_BFPI_INVALID_PARAMETER) }

      Name (BUFF, Buffer(2) {0x0})
      Store (DGPI(Local0), BUFF)

      // Buff 0 : DIO Chip type
      // Buff 1 : DIO Pin map
      Store (DerefOf (Index (BUFF, 0)), Local0)
      Store (DerefOf (Index (BUFF, 1)), Local1)
      Return(AGSO(Local0, Local1, Local2))
    }

    //---------------------------------------------------------------------------
    // Name: AGSO
    //
    // Description:  AAEON GPIO Set Driving
    //   Arg0 : GPIO Chip Type
    //   Arg1 : GPIO Number to set Driving
    //   Arg2 : Driving to set
    //     0: Open drain
    //     1: Push pull / Internal pull-up 20K
    //     2: Internal pull-up 10K
    //     3: Internal pull-up 5K
    //     4: Internal pull-up 1K
    //
    // Output:
    //   BFPI_STATUS
    //
    //---------------------------------------------------------------------------
    Method (AGSO, 3){
      #if ASL_DIO_TYPE_OEM_SUPPORT
      // OEM GPIO controlling method can be implemented externally in project level.
      If (LEqual (Arg0, ASL_DIO_TYPE_OEM)) {
        // ASL_OEM_DIO_SO_METHOD should contain (Arg1, Arg2). EX: \_SB.ODIO.ODSO(Arg1, Arg2)
        Return (ASL_OEM_DIO_SO_METHOD)
      }
      #endif
      #if ASL_DIO_TYPE_SOC_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SOC)) {
        // SoC GPIO controlling method should be implemented externally in platform level.
        Return (\_SB.SCSO(Arg1, Arg2))
      }
      #endif
      #if ASL_DIO_TYPE_SIO1_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SIO1)) {
        Return (\_SB.PCI0.LPCB.SIO1.D1SO(Arg1, Arg2))
      }
      #endif
      #if ASL_DIO_TYPE_SIO2_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SIO2)) {
        Return (\_SB.PCI0.LPCB.SIO2.D2SO(Arg1, Arg2))
      }
      #endif
      #if ASL_DIO_TYPE_SIO3_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SIO3)) {
        Return (\_SB.PCI0.LPCB.SIO.D3SO(Arg1, Arg2))
      }
      #endif
      #if ASL_DIO_TYPE_EC1_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_EC1)) {
        Return (\_SB.PCI0.LPCB.EC01.E1SO(Arg1, Arg2))
      }
      #endif
      #if ASL_DIO_TYPE_EC2_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_EC2)) {
        Return (\_SB.PCI0.LPCB.EC02.E2SO(Arg1, Arg2))
      }
      #endif
      #if ASL_DIO_TYPE_SMBUS_SUPPORT
      If (LEqual (Arg0, ASL_DIO_TYPE_SMBUS)) {
        Return (\_SB.SMSO(Arg1, Arg2))
      }
      #endif
      Return(ASL_BFPI_INVALID_PARAMETER)
    }
  }
}  // Scope(\_SB)