open (PC, "+<"."AgesaPostCode.h") or die "Fail to open AgesaPostCode.h";
while (<PC>) {
  $line = $_;
  # TpProcMemBeforeMemDataInit,         ///< 01 .. Memory structure initialization (Public interface)
  # $line =~ s/\s*(.+)?,\s+\/\/\/<\s*(.+)?\s*\.\.\s*(.+)?$/  $1 = 0xA1$2, \/\/\/< $3/);
  # TpFchInitResetDispatching                  = 0xAF01, ///< FCH InitReset dispatch point
  # TpUniversalAcpiEntry = 0xA001,               ///< Universal ACPI entry
  # TpProcMemBeforeMemDataInit                 = 0xA101, ///< Memory structure initialization (Public interface)

  if ($line =~ /^\s*(\w+)?\s*=\s*(\w+)?\s*,\s*\/\/\/<\s*(.+)$/) {
    $TpMacro = $1;
    $TpNum = $2;
    $Cmt = $3;
    # printf ("  [%s]\n", $TpMacro);
    $out .= sprintf ("  %-42s = $TpNum, /\/\/\< $Cmt\n", $TpMacro);
  } else {
    $out .= sprintf $line;
  }
}
seek(PC, 0, 0)               or die "can't seek to start of AgesaPostCode.h : $!";
# print $out;
print PC $out or die "can't print to AgesaPostCode.h $!";
truncate(PC,tell(PC))               or die "Truncating: $!";
close PC;