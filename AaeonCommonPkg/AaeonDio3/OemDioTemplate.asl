Scope(\_SB) {
  Device (ODIO) {
    Name(_HID, "AANT1101")       // Defined in \\Nas5\_Document\UEFI ACPI ID.xlsx
    Name(_UID, "1")
    Name(_DDN, "OEM DIO Controller")

    Method (_STA) {
      Return (0x0B)  // hidden
    }
    //---------------------------------------------------------------------------
    // Name: ODGL
    //
    // Description:  OEM GPIO Get Level
    //   Arg0 : GPIO Number to get level
    //
    // Output:
    //   Interger:
    //   0 - Low level
    //   1 - High level
    //   ASL_BFPI_INVALID_PARAMETER - GPIO number is invalid
    //
    //---------------------------------------------------------------------------
    Method (ODGL, 1) {
        Return (Arg0)
    }

    //---------------------------------------------------------------------------
    // Name: ODSL
    //
    // Description:  OEM GPIO Set Level
    //   Arg0 : GPIO Number to set level
    //   Arg1 : Level to set
    //     0 - Low level
    //     1 - High level
    //
    // Output:
    //   ASL_BFPI_SUCCESS
    //   ASL_BFPI_INVALID_PARAMETER - Either GPIO number or level to set is invalid
    //
    //---------------------------------------------------------------------------
    Method (ODSL, 2){
        Return (Arg0)
    }

    //---------------------------------------------------------------------------
    // Name: ODGD
    //
    // Description:  OEM GPIO Get Direction
    //   Arg0 : GPIO Number to get Direction
    //
    // Output:
    //   Interger:
    //   0 - Output
    //   1 - Input
    //   ASL_BFPI_INVALID_PARAMETER - GPIO number is invalid
    //
    //---------------------------------------------------------------------------
    Method (ODGD, 1) {
        Return (Arg0)
    }

    //---------------------------------------------------------------------------
    // Name: ODSD
    //
    // Description:  OEM GPIO Set Direction
    //   Arg0 : GPIO Number to set Direction
    //   Arg1 : Direction to set
    //     0 - Output
    //     1 - Input
    //
    // Output:
    //   ASL_BFPI_SUCCESS
    //   ASL_BFPI_INVALID_PARAMETER - Either GPIO number or direction to set is invalid
    //
    //---------------------------------------------------------------------------
    Method (ODSD, 2){
        Return (Arg0)
    }
    //---------------------------------------------------------------------------
    // Name: ODGO
    //
    // Description:  OEM GPIO Get Driving
    //   Arg0 : GPIO Number to get Driving
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
    Method (ODGO, 1) {
        Return (Arg0)
    }

    //---------------------------------------------------------------------------
    // Name: ODSO
    //
    // Description:  OEM GPIO Set Driving
    //   Arg0 : GPIO Number to set Driving
    //   Arg1 : Driving to set
    //     0: Open drain
    //     1: Push pull / Internal pull-up 20K
    //     2: Internal pull-up 10K
    //     3: Internal pull-up 5K
    //     4: Internal pull-up 1K
    //
    // Output:
    //   ASL_BFPI_SUCCESS
    //   ASL_BFPI_INVALID_PARAMETER - Either GPIO number or driving to set is invalid
    //
    //---------------------------------------------------------------------------
    Method (ODSO, 2){
        Return (Arg0)
    }
  }
}