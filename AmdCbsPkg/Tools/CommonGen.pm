#;*****************************************************************************
#;
#; Copyright 2012 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
#;
#; AMD is granting you permission to use this software and documentation (if
#; any) (collectively, the "Materials") pursuant to the terms and conditions of
#; the Software License Agreement included with the Materials.  If you do not
#; have a copy of the Software License Agreement, contact your AMD
#; representative for a copy.
#; 
#; You agree that you will not reverse engineer or decompile the Materials, in
#; whole or in part, except as allowed by applicable law.
#; 
#; WARRANTY DISCLAIMER:  THE MATERIALS ARE PROVIDED "AS IS" WITHOUT WARRANTY OF
#; ANY KIND.  AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY,
#; INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY,
#; FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT, THAT THE
#; MATERIALS WILL RUN UNINTERRUPTED OR ERROR-FREE OR WARRANTIES ARISING FROM
#; CUSTOM OF TRADE OR COURSE OF USAGE.  THE ENTIRE RISK ASSOCIATED WITH THE USE
#; OF THE MATERIAL IS ASSUMED BY YOU.  Some jurisdictions do not allow the
#; exclusion of implied warranties, so the above exclusion may not apply to
#; You.
#; 
#; LIMITATION OF LIABILITY AND INDEMNIFICATION:  AMD AND ITS LICENSORS WILL
#; NOT, UNDER ANY CIRCUMSTANCES BE LIABLE TO YOU FOR ANY PUNITIVE, DIRECT,
#; INCIDENTAL, INDIRECT, SPECIAL OR CONSEQUENTIAL DAMAGES ARISING FROM USE OF
#; THE MATERIALS OR THIS AGREEMENT EVEN IF AMD AND ITS LICENSORS HAVE BEEN
#; ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  In no event shall AMD's total
#; liability to You for all damages, losses, and causes of action (whether in
#; contract, tort (including negligence) or otherwise) exceed the amount of
#; $100 USD. You agree to defend, indemnify and hold harmless AMD and its
#; licensors, and any of their directors, officers, employees, affiliates or
#; agents from and against any and all loss, damage, liability and other
#; expenses (including reasonable attorneys' fees), resulting from Your use of
#; the Materials or violation of the terms and conditions of this Agreement.
#; 
#; U.S. GOVERNMENT RESTRICTED RIGHTS:  The Materials are provided with
#; "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
#; subject to the restrictions as set forth in FAR 52.227-14 and
#; DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
#; Government constitutes acknowledgment of AMD's proprietary rights in them.
#; 
#; EXPORT RESTRICTIONS: The Materials may be subject to export restrictions as
#; stated in the Software License Agreement.
#;*****************************************************************************
package CommonGen;
use strict;
use vars qw ($VERSION $XS_VERSION @ISA @EXPORT @EXPORT_OK $AUTOLOAD);
require Exporter;
require AutoLoader;

@ISA = qw (Exporter AutoLoader);
@EXPORT = qw ();
@EXPORT_OK = qw ( generateUniFileStr
                  generateHFile
                  generateLableStr
                  generateKeyStr
                  generateVfrFile
                  generateBlankLine
                  genStrToken
                  attachUniStr
                  genLableToken
                  generateSetDefaultValueFile
 );

#*----------------------------------------------------------
#*                  D E F I N E S
#*----------------------------------------------------------
#*
my $strPrefix = 'AMD_CBS_STR_';         # Prefix string
my $vfrStructName = 'AMD_SYSTEM_CONFIGURATION';  # Struct name

#*----------------------------------------------------------
#*           E X P O R T E D     F U N C T I O N S
#*----------------------------------------------------------
#*

#########################################################
#
# Generate UNI files
#
# IN      : UNI file handle
# IN      : Pointer to a CBS section or option
# IN      : a hash to store exist UNI string
#
#########################################################
sub generateUniFileStr
{
  my $uniFileStr = shift;
  my $thisOption = shift;
  my $uniExistHash = shift;

  my $optionNameToken;
  my $optionNameStr;
  my $optionHelpToken;
  my $optionHelpStr;
  my $sectionNameToken;

  if ($thisOption->{'Type'} =~ /^SECTION$/i) {
    # This is a section
    $sectionNameToken = &genStrToken($thisOption->{'Name'});
    $sectionNameToken = $sectionNameToken.'_SECTION';
    &outputStr($uniFileStr, $sectionNameToken, $thisOption->{'Name'}, $uniExistHash);
  } elsif ($thisOption->{'Type'} =~ /^OPTION$/i) {
    # This is an option

    #
    # Name string
    #

    # for 'Text' type, we want to show text which is in 'Additional_information'
    if ($thisOption->{'Input_type'} =~ /^Text$/i) {
      $optionNameToken = &genStrToken($thisOption->{'Name'});
      $optionNameStr = $thisOption->{'Additional_information'};
      &outputStr($uniFileStr, $optionNameToken, $optionNameStr, $uniExistHash);
    } else {
      $optionNameToken = &genStrToken($thisOption->{'Name'});
      $optionNameStr = $thisOption->{'Name'};
      $optionNameStr =~s/GRA\d/GRA/g;
      &outputStr($uniFileStr, $optionNameToken, $optionNameStr, $uniExistHash);
    }

    #
    # Help string
    #
    $optionHelpToken = "$optionNameToken".'_HELP';
    if (ref($thisOption->{'Help_text'}) eq 'HASH') {
      $optionHelpStr = 'No help string';
    } else {
      if ($thisOption->{'Help_text'} ne '') {
        $optionHelpStr = $thisOption->{'Help_text'};
        $optionHelpStr =~ s/GRA\d/GRA/g;
      } else {
        $optionHelpStr = 'No help string';
      }
    }

    &outputStr($uniFileStr, $optionHelpToken, $optionHelpStr, $uniExistHash);

    #
    # Option item string
    #
    if ($thisOption->{'Input_type'} =~ /^Fixed$/i) {
      foreach my $choice (@{$thisOption->{'OPTION_ITEM'}}) {
        my $optionItemToken = &genStrToken($choice->{'Name'});
        &outputStr($uniFileStr, $optionItemToken, $choice->{'Name'}, $uniExistHash);
      }
    }
  }
}

#########################################################
#
# Generate Header files
#
# IN      : Header file handle
# IN      : Pointer to a CBS section or option
#
#########################################################
sub generateHFile
{
  my $hFile = shift;
  my $thisOption = shift;

  if ($thisOption->{'Type'} =~ /^OPTION$/i) {
    if ($thisOption->{'Nv_type'} =~ /^Byte$/i) {
      printf $hFile "  UINT8         %-50s///< $thisOption->{'Name'}\n", $thisOption->{'Variable_name'}.';';
    } elsif ($thisOption->{'Nv_type'} =~ /^Word$/i) {
      printf $hFile "  UINT16        %-50s///< $thisOption->{'Name'}\n", $thisOption->{'Variable_name'}.';';
    } elsif ($thisOption->{'Nv_type'} =~ /^DWord$/i) {
      printf $hFile "  UINT32        %-50s///< $thisOption->{'Name'}\n", $thisOption->{'Variable_name'}.';';
    } elsif ($thisOption->{'Nv_type'} =~ /^QWord$/i) {
      printf $hFile "  UINT64        %-50s///< $thisOption->{'Name'}\n", $thisOption->{'Variable_name'}.';';
    }
  }
}

#########################################################
#
# Generate Lable string
#
# IN      : FORM start ID for CBS
# IN      : FORM ID will be output to .h file for CBS
# IN      : Pointer to a CBS section or option
#
#########################################################
sub generateLableStr
{
  my $lableStartID = shift;
  my $lableIDOutput = shift;
  my $thisOption = shift;

  if ($thisOption->{'Type'} =~ /^SECTION$/i) {
    if ($$lableIDOutput eq '') {
      $$lableIDOutput .= "// Section ID\n";
    }
    my $lableToken = genLableToken ($thisOption->{'Name'});
    $$lableIDOutput .= sprintf "  #define %-70s  0x%X\n", $lableToken, $$lableStartID;
    $$lableStartID++;
  }
}

#########################################################
#
# Generate KEY string
#
# IN      : FORM start ID for CBS
# IN      : FORM ID will be output to .h file for CBS
# IN      : Pointer to a CBS section or option
#
#########################################################
sub generateKeyStr
{
  my $lableStartID = shift;
  my $keyIDOutput = shift;
  my $thisOption = shift;

  if (($thisOption->{'Type'} =~ /^OPTION$/i) && ($thisOption->{'Key_function'} != 0)) {
    if ($$keyIDOutput eq '') {
      $$keyIDOutput .= "\n// KEY function ID\n";
    }
    my $keyToken = genKeyToken ($thisOption->{'Variable_name'});
    $$keyIDOutput .= sprintf "  #define %-70s  0x%X  //%s\n", $keyToken, $$lableStartID, $thisOption->{'Variable_name'};
    $$lableStartID++;
  }
}

#########################################################
#
# Generate VFR files
#
# IN      : VFR file handle
# IN      : Pointer to a CBS section or option
# IN      : Indent number
# IN      : code base
# IN      : Pointer to the CBS root section
# IN      : a hash to store exist KEY ID
# IN      : FORM start ID for CBS
# IN      : FORM ID will be output to .h file for CBS
# IN      : component (CPU/GNB/FCH)
#
#########################################################
sub generateVfrFile
{
  my $vfrFile = shift;
  my $thisOption = shift;
  my $indentNum = shift;
  my $rootSection = shift;
  my $keyIDExistHash = shift;
  my $lableStartID = shift;
  my $keyIDOutput = shift;
  my $component = shift;

  $vfrStructName = 'CBS_CONFIG';

  if ($thisOption->{'Type'} =~ /^SECTION$/i) {
    # This is a section
    generateVfrSection ($vfrFile, $thisOption, $indentNum, $rootSection, $component);
  } elsif ($thisOption->{'Type'} =~ /^OPTION$/i) {
    # This is an option
    # check if we need split 'Display_condition' and have multi instance
    my $multiInstance = checkForMultiInstance ($thisOption);
    if ($multiInstance eq 'FALSE') {
      # common options
      generateVfrCommonOpt ($vfrFile, $thisOption, $indentNum, $rootSection, $keyIDExistHash);
    } else {
      # split 'Display_condition'
      my @displayConditon = split (/\|/, $thisOption->{'Display_condition'});
      foreach my $disConditon (@displayConditon) {
        $thisOption->{'Display_condition'} = $disConditon;
        $thisOption->{'Display_condition'} =~ s/\s*$//g;
        generateVfrCommonOpt ($vfrFile, $thisOption, $indentNum, $rootSection, $keyIDExistHash);
      }
    }
  }
}

#########################################################
#
# Generate string token
#   adding prefix = 'AMD_CBS_STR_'
#   replace `~!@$%^&*()-=+[]{}\/,<>?| white space with _
#   replace . with DOT
#   replace # with POUND
# IN      : name string
#
# RETURN  : a string token used for UNI file
#
#########################################################
sub genStrToken
{
  my $str = shift;
  $str = $strPrefix.uc($str);
  $str = updateStr ($str);
  return $str;
}

#########################################################
#
# Attach the str to Uni str
# IN      : ref of UNI string
# IN      : string been attached
#
# RETURN  : NULL
#
#########################################################
sub attachUniStr
{
  my $unistr = shift;
  my $str = shift;
  $$unistr .= $str;
}

#########################################################
#
# Generate lable token
#   adding prefix = 'SETUP_'
#   adding suffix = '_LABLE'
#   replace `~!@$%^&*()-=+[]{}\/,<>?| white space with _
#   replace . with DOT
#   replace # with POUND
# IN      : name string
#
# RETURN  : a lable used for 'goto'
#
#########################################################
sub genLableToken
{
  my $lable = shift;
  $lable = 'SETUP_'.uc($lable).'_LABLE';
  $lable = updateStr ($lable);
  return $lable;
}

#########################################################
#
# Generate Key token
#   adding prefix = 'KEY_'
#   adding suffix = '_LABLE'
#   replace `~!@$%^&*()-=+[]{}\/,<>?| white space with _
#   replace . with DOT
#   replace # with POUND
# IN      : name string
#
# RETURN  : a lable used for 'goto'
#
#########################################################
sub genKeyToken
{
  my $lable = shift;
  $lable =~ s/([A-Z][a-z])/_$1/g;
  $lable =~ s/([a-z])([A-Z])/$1_$2/g;
  $lable =~ s/SMU/SMU_/ig;
  $lable = 'KEY_'.uc($lable);
  $lable = updateStr ($lable);
  return $lable;
}

#########################################################
#
# Generate a blank line in VFR file
#
# IN      : VFR file handle
# IN      : Indent number
# IN      : code base
#
#########################################################
sub generateBlankLine
{
  my $vfrFile = shift;
  my $indentNum = shift;

  my $StrToken = genStrToken ('BLANK');

  print $vfrFile '  ' x $indentNum."text\n";
  print $vfrFile '  ' x ($indentNum+1)."help        = STRING_TOKEN \($StrToken\),\n";
  print $vfrFile '  ' x ($indentNum+1)."text        = STRING_TOKEN \($StrToken\);\n";

  print $vfrFile "\n";
}
#*----------------------------------------------------------
#*           L O C A L     F U N C T I O N S
#*----------------------------------------------------------
#*

#########################################################
#
# Generate Section for VFR files
#
# IN      : VFR file handle
# IN      : Pointer to a CBS section or option
# IN      : Indent number
# IN      : code base
# IN      : Pointer to the CBS root section
# IN      : component (CPU/GNB/FCH)
#
#########################################################
sub generateVfrSection
{
  my $vfrFile = shift;
  my $thisOption = shift;
  my $indentNum = shift;
  my $rootSection = shift;
  my $component = shift;

  my $displayCondition;
  my $grayoutCondition;
  my $space;
  my $lableToken;
  my $strToken;

  # 0, #define AMD_PROCESSOR/GNB/FCH
#  if (($thisOption->{'Name'} =~ /AMD Processor Debug Options/i) || ($thisOption->{'Name'} =~ /AMD Processor Common Options/i)) {
#    print $vfrFile '  ' x $indentNum."#ifdef AMD_CBS_CPU_SUPPORT\n";
#  }
#  if (($thisOption->{'Name'} =~ /AMD GNB Debug Options/i) || ($thisOption->{'Name'} =~ /AMD GNB Common Options/i)) {
#    print $vfrFile '  ' x $indentNum."#ifdef AMD_CBS_GNB_SUPPORT\n";
#  }
#  if (($thisOption->{'Name'} =~ /AMD FCH Debug Options/i) || ($thisOption->{'Name'} =~ /AMD FCH Common Options/i)) {
#    print $vfrFile '  ' x $indentNum."#ifdef AMD_CBS_FCH_SUPPORT\n";
#  }

  if (($thisOption->{'Name'} =~ /Promontory Debug Options/i) || ($thisOption->{'Name'} =~ /Promontory Common Options/i)) {
    print $vfrFile '  ' x $indentNum."#ifdef PROMONTORY_SUPPORT\n";
  }

  # 1st, generate suppressif and grayoutif
  if ((ref ($thisOption->{'Display_condition'}) ne 'HASH') || (ref ($thisOption->{'Active_condition'}) ne 'HASH')) {
    # 1.1 comments
    if (ref ($thisOption->{'Display_condition'}) ne 'HASH') {
      printf $vfrFile '  ' x $indentNum."// Display Condition: $thisOption->{'Display_condition'}\n";
    }
    if (ref ($thisOption->{'Active_condition'}) ne 'HASH') {
      printf $vfrFile '  ' x $indentNum."// Active Condition: $thisOption->{'Active_condition'}\n";
    }
    # 1.2 suppressif
    if (ref ($thisOption->{'Display_condition'}) ne 'HASH') {
      $displayCondition = findNegativeConditions ($thisOption->{'Display_condition'}, $rootSection);
      $space = '  ' x $indentNum.'      ';
      $displayCondition =~ s/\tOR /$space  OR /g;
      $displayCondition =~ s/\tAND /$space AND /g;
      printf $vfrFile '  ' x $indentNum."suppressif $displayCondition;\n";
    }
    # 1.3 grayoutif
    if (ref ($thisOption->{'Active_condition'}) ne 'HASH') {
      $grayoutCondition = findNegativeConditions ($thisOption->{'Active_condition'}, $rootSection);
      $space = '  ' x $indentNum.'     ';
      $grayoutCondition =~ s/\tOR /$space  OR /g;
      $grayoutCondition =~ s/\tAND /$space AND /g;
      printf $vfrFile '  ' x $indentNum."grayoutif $grayoutCondition;\n";
    }
    # 1.4 $indentNum++
    $indentNum++;
  }

  # 2nd, generate form
  $lableToken = genLableToken ($thisOption->{'Name'});
  $strToken = &genStrToken($thisOption->{'Name'});
  $strToken = $strToken.'_SECTION';
  # Normally we always goto low level section
  # but sometimes we want to goto up level section
  # This is for legal disclaimer
  if (exists $thisOption->{'GoTo_Section'}) {
    if (ref ($thisOption->{'GoTo_Section'}) ne 'HASH') {
      my $GotoSection = genLableToken ($thisOption->{'GoTo_Section'});
      printf $vfrFile '  ' x $indentNum."goto $GotoSection,\n";
    } else {
      printf $vfrFile '  ' x $indentNum."goto $lableToken,\n";
    }
  } else {
    printf $vfrFile '  ' x $indentNum."goto $lableToken,\n";
  }
  printf $vfrFile '  ' x ($indentNum+1)."prompt      = STRING_TOKEN \($strToken\),\n";
  printf $vfrFile '  ' x ($indentNum+1)."help        = STRING_TOKEN \($strToken\);\n";

  # 3rd, endif
  if ((ref ($thisOption->{'Display_condition'}) ne 'HASH') || (ref ($thisOption->{'Active_condition'}) ne 'HASH')) {
    $indentNum--;
    printf $vfrFile '  ' x $indentNum."endif;\n";
    if ((ref ($thisOption->{'Display_condition'}) ne 'HASH') && (ref ($thisOption->{'Active_condition'}) ne 'HASH')) {
      printf $vfrFile '  ' x $indentNum."endif;\n";
    }
  }

  # 4th #endif
#  if (($thisOption->{'Name'} =~ /AMD Processor Debug Options/i) || ($thisOption->{'Name'} =~ /AMD Processor Common Options/i) ||
#      ($thisOption->{'Name'} =~ /AMD GNB Debug Options/i) || ($thisOption->{'Name'} =~ /AMD GNB Common Options/i) ||
#      ($thisOption->{'Name'} =~ /AMD FCH Debug Options/i) || ($thisOption->{'Name'} =~ /AMD FCH Common Options/i)) {
#    print $vfrFile '  ' x $indentNum."#endif\n";
#  }
  if (($thisOption->{'Name'} =~ /Promontory Debug Options/i) || ($thisOption->{'Name'} =~ /Promontory Common Options/i)) {
    print $vfrFile '  ' x $indentNum."#endif\n";
  }
  printf $vfrFile "\n";
}

#########################################################
#
# Check if we need split 'Display_condition' and have multi instance
#
# IN      : Pointer to a CBS section or option
# OUT     : TRUE  --- we need have multi instance for this option
#           FALSE --- one instance for this option is enough
#
#########################################################
sub checkForMultiInstance
{
  my $thisOption = shift;
  my $multiInstance = 'FALSE';

  # (A&B&C) | (A&!B)
  if ($thisOption->{'Display_condition'} =~ /\|/g) {
    my @displayConditon = split (/\|/, $thisOption->{'Display_condition'});
    foreach (@displayConditon) {
      my @temp = split (/\,/, $_);
      if (scalar @temp > 2) {
        $multiInstance = 'TRUE';
      }
    }
  }

  return $multiInstance;
}

#########################################################
#
# Generate common options for VFR files
#
# IN      : VFR file handle
# IN      : Pointer to a CBS section or option
# IN      : Indent number
# IN      : code base
# IN      : Pointer to the CBS root section
# IN      : a hash to store exist KEY ID
#
#########################################################
sub generateVfrCommonOpt
{
  my $vfrFile = shift;
  my $thisOption = shift;
  my $indentNum = shift;
  my $rootSection = shift;
  my $keyIDExistHash = shift;

  my $optionNameToken;
  my $optionHelpToken;
  my $defaultValue;
  my $keyFunction;
  my $keyLable;
  my $choice;
  my $displayCondition;
  my $grayoutCondition;
  my $space;
  my $Backslash = '';
  my $FlagForKeyFunction;

  # 1st, generate suppressif and grayoutif
  if ((ref ($thisOption->{'Display_condition'}) ne 'HASH') || (ref ($thisOption->{'Active_condition'}) ne 'HASH')) {
    # 1.1 comments
    if (ref ($thisOption->{'Display_condition'}) ne 'HASH') {
      printf $vfrFile '  ' x $indentNum."// Display Condition: $thisOption->{'Display_condition'}\n";
    }
    if (ref ($thisOption->{'Active_condition'}) ne 'HASH') {
      printf $vfrFile '  ' x $indentNum."// Active Condition: $thisOption->{'Active_condition'}\n";
    }
    # 1.2 suppressif
    if (ref ($thisOption->{'Display_condition'}) ne 'HASH') {
      $displayCondition = findNegativeConditions ($thisOption->{'Display_condition'}, $rootSection);
      $space = '  ' x $indentNum.'      ';
      $displayCondition =~ s/\tOR /$space  OR /g;
      $displayCondition =~ s/\tAND /$space AND /g;
      printf $vfrFile '  ' x $indentNum."suppressif $displayCondition;\n";
    }
    # 1.3 grayoutif
    if (ref ($thisOption->{'Active_condition'}) ne 'HASH') {
      $grayoutCondition = findNegativeConditions ($thisOption->{'Active_condition'}, $rootSection);
      $space = '  ' x $indentNum.'     ';
      $grayoutCondition =~ s/\tOR /$space  OR /g;
      $grayoutCondition =~ s/\tAND /$space AND /g;
      printf $vfrFile '  ' x $indentNum."grayoutif $grayoutCondition;\n";
    }
    # 1.4 $indentNum++
    $indentNum++;
  }

  # 2nd, generate oneof, numeric
  $optionNameToken = &genStrToken($thisOption->{'Name'});
  $optionHelpToken = "$optionNameToken".'_HELP';
  printf $vfrFile '  ' x $indentNum."// $thisOption->{'Name'}$Backslash\n";
  if (ref ($thisOption->{'Help_text'}) ne 'HASH') {
    if ($thisOption->{'Help_text'} ne $thisOption->{'Name'}) {
      printf $vfrFile '  ' x $indentNum."// $thisOption->{'Help_text'}$Backslash\n";
    }
  } else {
    printf $vfrFile '  ' x $indentNum."// No help string$Backslash\n";
  }

  if ($thisOption->{'Input_type'} =~ /^Fixed$/i) {
    # Fixed Options
    printf $vfrFile '  ' x $indentNum."oneof$Backslash\n";
    printf $vfrFile '  ' x ($indentNum+1)."varid       = $vfrStructName.%s,$Backslash\n", $thisOption->{'Variable_name'};
    #   questionid = KEY_XXXX,
    if ($thisOption->{'Key_function'} != 0) {
      $keyLable = genKeyToken ($thisOption->{'Variable_name'});
      printf $vfrFile '  ' x ($indentNum+1)."questionid  = $keyLable,$Backslash\n";
    }
    printf $vfrFile '  ' x ($indentNum+1)."prompt      = STRING_TOKEN (%s),$Backslash\n", $optionNameToken;
    printf $vfrFile '  ' x ($indentNum+1)."help        = STRING_TOKEN (%s),$Backslash\n", $optionHelpToken;
    #   flags = INTERACTIVE,
    if ($thisOption->{'Key_function'} != 0) {
      $keyLable = genKeyToken ($thisOption->{'Variable_name'});
    }

    my $first = 1;
    foreach $choice (@{$thisOption->{'OPTION_ITEM'}}) {
      # get DEFAULT flag
      $defaultValue = '0 | RESET_REQUIRED';
      if ($thisOption->{'BIOS_Default'} =~ /^$choice->{'Nv_storage'}$/i) {
        $defaultValue = 'DEFAULT | RESET_REQUIRED';
      }
      # get INTERACTIVE flag
      if ($thisOption->{'Key_function'} == 0) {
        $keyFunction = '';
      } else {
        $keyFunction = ' | INTERACTIVE';
      }
      my $optionItemToken = &genStrToken($choice->{'Name'});
      if ($thisOption->{'Key_function'} != 0) {
        printf $vfrFile '  ' x ($indentNum+1)."option text = STRING_TOKEN %-30s value = %-5s flags = %-10s\n", '('.$optionItemToken.'),', $choice->{'Nv_storage'}.',', $defaultValue.$keyFunction.';';
      } else {
        printf $vfrFile '  ' x ($indentNum+1)."option text = STRING_TOKEN %-30s value = %-5s flags = %s\n", '('.$optionItemToken.'),', $choice->{'Nv_storage'}.',', $defaultValue.';';
      }
    }
    printf $vfrFile '  ' x $indentNum."endoneof;\n";
  } elsif ($thisOption->{'Input_type'} =~ /^Customed$/i) {
    # Customed Options
    printf $vfrFile '  ' x $indentNum."numeric$Backslash\n";
    printf $vfrFile '  ' x ($indentNum+1)."varid       = $vfrStructName.%s,$Backslash\n", $thisOption->{'Variable_name'};
    #   questionid = KEY_XXXX,
    if ($thisOption->{'Key_function'} != 0) {
      $FlagForKeyFunction = ' | INTERACTIVE';
      $keyLable = genKeyToken ($thisOption->{'Variable_name'});
      printf $vfrFile '  ' x ($indentNum+1)."questionid  = $keyLable,$Backslash\n";
    }
    printf $vfrFile '  ' x ($indentNum+1)."prompt      = STRING_TOKEN (%s),$Backslash\n", $optionNameToken;
    printf $vfrFile '  ' x ($indentNum+1)."help        = STRING_TOKEN (%s),$Backslash\n", $optionHelpToken;

    if (ref ($thisOption->{'Additional_information'}) eq 'HASH') {
      printf $vfrFile '  ' x ($indentNum+1)."flags       = DISPLAY_UINT_HEX | RESET_REQUIRED$FlagForKeyFunction,$Backslash\n";
    } elsif ($thisOption->{'Additional_information'} !~ /DECIMAL_INPUT\s*=\s*TRUE/ig) {
      printf $vfrFile '  ' x ($indentNum+1)."flags       = DISPLAY_UINT_HEX | RESET_REQUIRED$FlagForKeyFunction,$Backslash\n";
    } else {
      printf $vfrFile '  ' x ($indentNum+1)."flags       = RESET_REQUIRED$FlagForKeyFunction,$Backslash\n";
    }

    $thisOption->{'OPTION_ITEM'}->[0]->{'Nv_storage'} =~ /(\w+)-(\w+)/;
    printf $vfrFile '  ' x ($indentNum+1)."minimum     = %s,$Backslash\n",$1;
    printf $vfrFile '  ' x ($indentNum+1)."maximum     = %s,$Backslash\n",$2;
    printf $vfrFile '  ' x ($indentNum+1)."step        = 0,$Backslash\n";
    printf $vfrFile '  ' x ($indentNum+1)."default     = %s,$Backslash\n", $thisOption->{'BIOS_Default'};
    printf $vfrFile '  ' x $indentNum."endnumeric;\n";
  } elsif ($thisOption->{'Input_type'} =~ /^Text$/i) {
    if (ref ($thisOption->{'Additional_information'}) ne 'HASH') {
      printf $vfrFile '  ' x $indentNum."text\n";
      printf $vfrFile '  ' x ($indentNum+1)."help        = STRING_TOKEN (%s),$Backslash\n", $optionHelpToken;
      printf $vfrFile '  ' x ($indentNum+1)."text        = STRING_TOKEN (%s);\n", $optionNameToken;
    }
  }


  # 3rd, endif
  if ((ref ($thisOption->{'Display_condition'}) ne 'HASH') || (ref ($thisOption->{'Active_condition'}) ne 'HASH')) {
    $indentNum--;
    printf $vfrFile '  ' x $indentNum."endif;$Backslash\n";
    if ((ref ($thisOption->{'Display_condition'}) ne 'HASH') && (ref ($thisOption->{'Active_condition'}) ne 'HASH')) {
      printf $vfrFile '  ' x $indentNum."endif;$Backslash\n";
    }
  }
  printf $vfrFile "\n";
}

#########################################################
#
# Update string
#   replace `~!@$%^&*()-=+[]{}\/,<>?| white space with _
#   replace . with DOT
#   replace # with POUND
# IN OUT  : string
#
#########################################################
sub updateStr
{
  my $str = shift;
  $str =~ s/[`~!@\s\$\%\'\^&\*\(\)\[\]\{\}\-=+\\|\;:",\<>\/\?]+/_/g;
  $str =~ s/\.+/_DOT_/g;
  $str =~ s/#+/_POUND_/g;
  $str =~ s/_{2,}/_/g;
  $str =~ s/_*$//;
  $str =~ s/GRA\d*/GRA/g;
  return $str;
}

#########################################################
#
# Output string to UNI file str.
# IN      : UNI file string
# IN      : String token
# IN      : String
# IN      : a hash to store exist UNI string
#
#########################################################
sub outputStr
{
  my $uniFilestr = shift;
  my $str1 = shift;
  my $str2 = shift;
  my $uniExistHash = shift;

  if (exists $uniExistHash->{"$str1"}) {
    $uniExistHash->{"$str1"} += 1;
  } else {
    $uniExistHash->{"$str1"} = 1;
    $str2 =~ s/"/'/g;
    if ($str2 =~ /_Legal_Disclaimer_(\w+)$/i) {
      $str2 = $1;
    }
    attachUniStr($uniFilestr, sprintf "#string %-70s  #language en-US    \"%s\"\n", $str1, $str2);
  }
}

#########################################################
#
# Generate NV value of a given variable
#
# IN      : variable name
# IN      : NV value name
# IN      : CBS section
#
# RETURN  : NV value
#########################################################
sub getNvValue
{
  my $variableName = shift;
  my $nvValueName = shift;
  my $cbsSection = shift;
  my $nvValue = 'Not found';

  # remove tailing space.
  $variableName =~ s/\s*$//g;
  $nvValueName =~ s/\s*$//g;

  foreach my $thisOption (@{$cbsSection}) {
    if ($thisOption->{'Type'} =~ /^SECTION$/i) {
        $nvValue = getNvValue ($variableName, $nvValueName, $thisOption->{'ITEM'});
        if ($nvValue ne 'Not found') {
          return $nvValue;
        }
    } elsif ($thisOption->{'Type'} =~ /^OPTION$/i) {
      if ($thisOption->{'Variable_name'} =~ /^$variableName$/i) {
        if ($thisOption->{'Input_type'} =~ /^Fixed$/i) {
          foreach my $choice (@{$thisOption->{'OPTION_ITEM'}}) {
            if ($choice->{'Name'} =~ /^$nvValueName$/i) {
              $nvValue = $choice->{'Nv_storage'};
              return $nvValue;
            }
          }
        } elsif ($thisOption->{'Input_type'} =~ /^Customed$/i) {
          $nvValue = $nvValueName;
        }
      }
    }
  }
  return $nvValue;
}

#########################################################
#
# return a group of strings in the form of
# "<VariableName>=<NvValue>"
# IN      : Target option to be processed
# IN      : ptr to the option groups
#
#########################################################
sub findNegativeConditions
{
  my $displayCondition = shift;
  my $sectionName = shift;
  my $parentConditionsString;
  my $vfrCondition = "";
  my @vfrConditions = ();
  my $parentOptionFound = 0;
  my $parentOptionChoiceFound = 0;
  my $nvValue;

  # remove preceding space
  $displayCondition =~ s/^\s*//g;

  # Collect all the parent conditions in @parentConditions
  if (defined $displayCondition && $displayCondition ne "") {
    $parentConditionsString = $displayCondition;
  }

  # parse the complementary parent conditions
  if ($parentConditionsString !~ /\|/) {
    my @oredParentConditionStrings = split (/\s*\,\s*/, $parentConditionsString);
    @vfrConditions = &parseNegativeCondition (\@oredParentConditionStrings, $sectionName);
    $vfrCondition = join ("\n\tOR ", @vfrConditions);
  } elsif ($parentConditionsString !~ /,/) {
    my @andedParentConditionStrings = split (/\s*\|\s*/, $parentConditionsString);
    @vfrConditions = &parseNegativeCondition (\@andedParentConditionStrings, $sectionName);
    $vfrCondition = join ("\n\tAND ", @vfrConditions);
  } else {
    my @vfrAndedConditions = ();
    my @vfrOredConditions = ();
    my @andedParentConditionStrings0 = ();
    my @andedParentConditionStrings1 = ();
    $parentConditionsString = &formatAsABorAC ($parentConditionsString);
    my @oredParentConditionStrings = split (/\s*\|\s*/, $parentConditionsString);
    foreach my $oredParentConditionStrings (@oredParentConditionStrings) {
      $oredParentConditionStrings =~ s/\(|\)//g;
      my @andedParentConditionStrings = split (/\s*\,\s*/, $oredParentConditionStrings);
      if (scalar @andedParentConditionStrings == 2) {
        @andedParentConditionStrings1 = ($andedParentConditionStrings[1]);
        @vfrAndedConditions = (@vfrAndedConditions, &parseNegativeCondition (\@andedParentConditionStrings1, $sectionName));
        $vfrCondition = join ("\n\tAND ", @vfrAndedConditions);
        if (!defined $andedParentConditionStrings0[0]) {
          @andedParentConditionStrings0 = ($andedParentConditionStrings[0]);
        } elsif ($andedParentConditionStrings0[0] ne $andedParentConditionStrings[0]) {
          # The first condition must be common
          die ("[ERROR1] Incorrect format of parent condition string\n\t\t".$parentConditionsString."\n");
        }
      } else {
        die ("[ERROR2] Incorrect format of parent condition string\n\t\t".$parentConditionsString."\n");
      }
    }
    @vfrOredConditions = (&parseNegativeCondition (\@andedParentConditionStrings0, $sectionName));
    $vfrCondition = join ("\n\tOR ", @vfrOredConditions, $vfrCondition);
  }

  return $vfrCondition;
}

sub parseNegativeCondition
{
  my $pConditions = shift;
  my $sectionName = shift;
  my $vfrCondition = "";
  my @vfrConditions = ();
  my $nvValue;

  foreach my $condition (@$pConditions) {
    # loop for all components
    if ($condition =~ /\s*=\s*/) {
      (my $variableName, my $choiceName) = split (/\s*=\s*/, $condition);
      # match target with all the options
      $nvValue = &getNvValue ($variableName, $choiceName, $sectionName);
      push (@vfrConditions, sprintf "NOT ideqval $vfrStructName.%s == $nvValue", $variableName);
    } else {
      die ("[ERROR3] Incorrect format of parent condition string\n\t\t".$condition."\n");
    }
  }

  return @vfrConditions;
}

sub formatAsABorAC
{
    my $parentConditionString = shift;
    my $option = shift;
    my $numOredConditions = 0;
    my %numConditions = ();
    my $commonCondition = "";
    my $formattedCondition = "";

    my @oredParentConditionStrings = split (/\s*\|\s*/, $parentConditionString);
    foreach my $oredParentConditionString (@oredParentConditionStrings) {
        $numOredConditions ++;
        my @andedParentConditions = split (/\s*,\s*/, $oredParentConditionString);
        foreach my $condition (@andedParentConditions) {
            # count the repeats of each condition
            $condition =~ s/\s*=\s*/=/;
            if (defined $numConditions{$condition}) {
                $numConditions{$condition} ++;
            } else {
                $numConditions{$condition} = 1;
            }
        }
    }
    # find the common condition
    foreach my $condition (keys %numConditions) {
        if ($numConditions{$condition} == $numOredConditions) {
            $commonCondition = $condition;
            last;
        }
    }
    if ($commonCondition =~ /^\s*$/) {
        &logError ("[ERROR] No common condition found\n\t\t".$option->{"Name"}." : ".$parentConditionString."\n");
    }
    # format the parent condition
    foreach my $oredParentConditionString (@oredParentConditionStrings) {
        my @andedParentConditions = split (/\s*,\s*/, $oredParentConditionString);
        if ($andedParentConditions[0] eq $commonCondition) {
            $formattedCondition .= $commonCondition.",".$andedParentConditions[1];
        } else {
            $formattedCondition .= $commonCondition.",".$andedParentConditions[0];
        }
        $formattedCondition .= "|";
    }

    $formattedCondition =~ s/\|$//;

    return $formattedCondition;
}


#*----------------------------------------------------------
#*           D E V     F U N C T I O N S
#*----------------------------------------------------------
#*

#########################################################
#
# set default value
# IN      : set default value file handle
# IN      : Pointer to a CBS section or option
#
#########################################################
sub generateSetDefaultValueFile
{
  my $setDefaultValueFile = shift;
  my $thisOption = shift;
  my $temp;

  if ($thisOption->{'Type'} =~ /^OPTION$/i) {
    $temp = '  Setup_Config->'.$thisOption->{'Variable_name'}.' = '.$thisOption->{'BIOS_Default'}.';';
    $temp = sprintf "%-70s  // $thisOption->{'Name'}\n", $temp;
    printf $setDefaultValueFile $temp;
  }
}
1;
