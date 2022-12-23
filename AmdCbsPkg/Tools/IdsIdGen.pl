#;*****************************************************************************
#;
#; Copyright 2012 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
#;
#; AMD is granting You permission to use this software and documentation (if
#; any) (collectively, the "Software") pursuant to the terms and conditions of
#; the Software License Agreement included with the Software. If You do not have
#; a copy of the Software License Agreement, contact Your AMD representative for
#; a copy.
#;
#; You agree that You will not reverse engineer or decompile the Software, in
#; whole or in part, except as allowed by applicable law.
#;
#; WARRANTY DISCLAIMER: THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
#; KIND. AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
#; BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, QUALITY,
#; FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT AND WARRANTIES
#; ARISING FROM CUSTOM OF TRADE OR COURSE OF USAGE WITH RESPECT TO THE SOFTWARE,
#; INCLUDING WITHOUT LIMITATION, THAT THE SOFTWARE WILL RUN UNINTERRUPTED OR
#; ERROR-FREE. THE ENTIRE RISK ASSOCIATED WITH THE USE OF THE SOFTWARE IS
#; ASSUMED BY YOU. Some jurisdictions do not allow the exclusion of implied
#; warranties, so the above exclusion may not apply to You, but only to the
#; extent required by law.
#;
#; LIMITATION OF LIABILITY AND INDEMNIFICATION: TO THE EXTENT NOT PROHIBITED BY
#; APPLICABLE LAW, AMD AND ITS LICENSORS WILL NOT, UNDER ANY CIRCUMSTANCES BE
#; LIABLE TO YOU FOR ANY PUNITIVE, DIRECT, INCIDENTAL, INDIRECT, SPECIAL OR
#; CONSEQUENTIAL DAMAGES ARISING FROM POSSESSION OR USE OF THE SOFTWARE OR
#; OTHERWISE IN CONNECTION WITH ANY PROVISION OF THIS AGREEMENT EVEN IF AMD AND
#; ITS LICENSORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. THIS
#; INCLUDES, WITHOUT LIMITATION, DAMAGES DUE TO LOST OR MISAPPROPRIATED DATA,
#; LOST PROFITS OR CONFIDENTIAL OR OTHER INFORMATION, FOR BUSINESS INTERRUPTION,
#; FOR PERSONAL INJURY, FOR LOSS OF PRIVACY, FOR FAILURE TO MEET ANY DUTY
#; INCLUDING OF GOOD FAITH OR REASONABLE CARE, FOR NEGLIGENCE AND FOR ANY OTHER
#; PECUNIARY OR OTHER LOSS WHTSOEVER. In no event shall AMD's total liability to
#; You for all damages, losses, and causes of action (whether in contract, tort
#; (including negligence) or otherwise) exceed the amount of $50 USD. You agree
#; to defend, indemnify and hold harmless AMD, its subsidiaries and affiliates
#; and their respective licensors, directors, officers, employees, affiliates or
#; agents from and against any and all loss, damage, liability and other
#; expenses (including reasonable attorneys' fees), resulting from Your
#; possession or use of the Software or violation of the terms and conditions of
#; this Agreement.
#;
#; U.S. GOVERNMENT RESTRICTED RIGHTS: Notice to U.S. Government End Users. The
#; Software and related documentation are "commercial items", as that term is
#; defined at 48 C.F.R. Section 2.101, consisting of "commercial computer
#; software" and "commercial computer software documentation", as such terms are
#; used in 48 C.F.R. Section 12.212 and 48 C.F.R. Section 227.7202,
#; respectively. Consistent with 48 C.F.R. Section 12.212 or 48 C.F.R. Sections
#; 227.7202-1 through 227.7202-4, as applicable, the commercial computer
#; software and commercial computer software documentation are being licensed to
#; U.S. Government end users: (a) only as commercial items, and (b) with only
#; those rights as are granted to all other end users pursuant to the terms and
#; conditions set forth in this Agreement. Unpublished rights are reserved under
#; the copyright laws of the United States.
#;
#; EXPORT RESTRICTIONS:  You shall adhere to all applicable U.S. import/export
#; laws and regulations, as well as the import/export control laws and
#; regulations of other countries as applicable. You further agree You will not
#; export, re-export, or transfer, directly or indirectly, any product,
#; technical data, software or source code received from AMD under this license,
#; or the direct product of such technical data or software to any country for
#; which the United States or any other applicable government requires an export
#; license or other governmental approval without first obtaining such licenses
#; or approvals, or in violation of any applicable laws or regulations of the
#; United States or the country where the technical data or software was
#; obtained. You acknowledges the technical data and software received will not,
#; in the absence of authorization from U.S. or local law and regulations as
#; applicable, be used by or exported, re-exported or transferred to: (i) any
#; sanctioned or embargoed country, or to nationals or residents of such
#; countries; (ii) any restricted end-user as identified on any applicable
#; government end-user list; or (iii) any party where the end-use involves
#; nuclear, chemical/biological weapons, rocket systems, or unmanned air
#; vehicles.  For the most current Country Group listings, or for additional
#; information about the EAR or Your obligations under those regulations, please
#; refer to the website of the U.S. Bureau of Industry and Security at
#; http://www.bis.doc.gov/.
#;*****************************************************************************
use Getopt::Long; #Library to parse and interpret arguments
use XML::Simple qw(XMLin XMLout );
use Data::Dumper;
use Encode qw(encode decode);
use CommonGen qw (generateUniFileStr generateHFile generateLableStr generateKeyStr generateVfrFile generateBlankLine
genStrToken genLableToken attachUniStr generateSetDefaultValueFile);
use File::Find;
# use strict;

#Version 1.0.0 09/06/2017
# Initial version

#Version 1.0.1 10/18/2017
# Add support SSP support

#Global variable
my $toolVersion="1.0.1";
my $toolName="IDS Generator Tool";
my $inputPath;
my $idsNvIntIdFile;
my $outputpath;
my $version;
my $formID;
my $help;
my $rootLable='CBS_ROOT';
my $idsIdNum = 0;
my $idsIdNumEnd = 0;
my $idsNvSize = 0;
my $promontorySupport = 1;
my $Program;
my $IdsIdStruct;
my $Id = 0;
my $sortedIdsIdStruct;
# Name Model = "ProgramName_BranchName"
my %supportedProgram = ('ZEPPELIN'=>'ZP','RAVEN'=>'RV', 'STARSHIP'=>'SSP'); #
my $idsFiles;
printf "%s - Version %s\n\n", $toolName, $toolVersion;
print "parse input parameters...\n";
# parse input parameters
parseinput ();

my $year = `date /t`;
$year =~ /(\d{4})/i;
$year = $1;

print "Search *Setup*.xml in $inputPath\n";
find (\&wanted, $inputPath);

foreach $xmlfile (@xmlfiles) {
printf "parse XML files %s\n", $xmlfile;

  my $rootCfgHash = XMLin("$xmlfile", forcearray => qr/ITEM$/);
  # Get Program string, and init related variable
  # $Program = GetProgramStr ($rootCfgHash->{'Name'});
  $Program = GetProgramStr($rootCfgHash->{'Name'});
  if (!exists $supportedProgram{$Program}) {
    print ("Unsupported Program $Program\n");
    die ("Unsupported Program $Program\n");
  }
  $ProgramStr = &GetProgramShortStr($Program);
  print "Creating files "."IdsNvId".$ProgramStr.".h ...\n";
  # 2nd, open files and init file str
  open my $idsNvIdFile, ">".$outputpath."IdsNvId".$ProgramStr.".h" or die "IdsNvId.h";
  print "Creating files"."IdsNvIntId".$ProgramStr.".h ...\n";
  open my $idsNvIntIdFile, ">".$outputpath."IdsNvIntId".$ProgramStr.".h" or die "IdsNvIntId.h";
  $idsFiles->{$Program}->{"External"}=$idsNvIdFile;
  $idsFiles->{$Program}->{"Internal"}=$idsNvIntIdFile;

  # 3rd, copyright
  print "generateFileHeader...\n";
  &generateFileHeader ($idsNvIdFile, $idsNvIntIdFile);
  printf $idsNvIdFile "#ifndef _IDS_NV_ID_%s_H_\n#define _IDS_NV_ID_%s_H_\n\n", $ProgramStr, $ProgramStr;
  printf $idsNvIntIdFile "#ifndef _IDS_NV_INT_ID_%s_H_\n#define _IDS_NV_INT_ID_%s_H_\n\n", $ProgramStr, $ProgramStr;

  &generateCbsFiles ($rootCfgHash->{'ITEM'});
}
# print Dumper($IdsIdStruct);
refineStruct ();
# die;
# 4th, #ifndef

print "\n\nGenerate IDS NV Id definitions...\n";

&OutputIdsId ();


foreach $Program (keys %$idsFiles) {
  $idsNvIdFile = $idsFiles->{$Program}->{'External'};
  $idsNvIntIdFile = $idsFiles->{$Program}->{'Internal'};
  printf $idsNvIdFile "\n#endif //_IDS_NV_ID_%s_H_\n", &GetProgramShortStr($Program);
  printf $idsNvIntIdFile "\n#endif //_IDS_NV_INT_ID_%s_H_\n", &GetProgramShortStr($Program);

  print "\n\nClose files...\n";

  close $idsNvIdFile;
  close $idsNvIntIdFile;
}
print "End\n";
#*----------------------------------------------------------
#*           L O C A L     F U N C T I O N S
#*----------------------------------------------------------
#*
sub GetProgramStr {
    my $_program = shift;
    if ($_program =~ /^([^_]+)_/) {
        return (uc $1);
	}
	return "";
}

sub GetProgramShortStr {
    my $_program = shift;
    ($supportedProgram{$_program} ne undef) or die;
    return $supportedProgram{$_program};
}

sub wanted {
    if (/[ie]Setup.+.xml$/i) {
        print $File::Find::name."\n";
        push @xmlfiles, $File::Find::name;
    }
}
#########################################################
#
# Parse input & init default value
#
# IN      : NULL
# IN      : NULL
#
#########################################################
sub parseinput {
  GetOptions(
      'inputPath=s'   => \$inputPath,
      'outputpath=s'  => \$outputpath,
      'help'          => \$help
  ) or die "Incorrect usage! Try --help for help with usage\n";

  if ($help) {
    &showhelp();
  }

  if ($inputPath eq '') {
    print ("inputPath is Required\n");
    &showhelp();
  } else {
    if (!-e $inputPath) {
      print ("Can't open $inputPath\n");
      &showhelp();       
    }
  }

  if ($outputpath eq '') {
    $outputpath = ".\\";
  }
  $outputpath =~ s/\\/\//g;
  mkdir ($outputpath);
  $outputpath .= '/';
}
#########################################################
#
# Show Help
#
# IN      : NULL
# IN      : NULL
#
#########################################################
sub showhelp {
  printf "%s - Ver %s\n\n", $toolName, $toolVersion;
  print 
  '
  
  USAGE perl IdsIdGen.pl [-i InputPath] [-o outputpath]
    [-i Input XML file] specify the input path, used to search the CBS XML File ([i,e]setup.+.xml)
    [-o outputpath] specify output path e.g -o y:\CBS
  ';
  exit (1);
}

#########################################################
#
# Generate vfr, header, uni files
#
# IN      : CBS database
# IN      : CBS version, it could be internal/external
#
#########################################################
sub generateCbsFiles {
  my $cbsDataBase = shift;




  # generate vfr, header and uni files

  &parseCbs ($cbsDataBase, $rootLable, $cbsDataBase);


}
#########################################################
#
# Get Componet name according to input CBS section name
#
# IN      : Section name
# OUT     : Component name
#
#########################################################
sub GetComponentName {
  my $OptionName = shift;
  my $component;
        # get component
  if (($OptionName =~ /AMD Processor Common Options/ig) || ($OptionName =~ /AMD Processor Debug Options/ig)) {
    $component = 'CPU';
  }
  if (($OptionName =~ /AMD GNB Common Options/ig) || ($OptionName =~ /AMD GNB Debug Options/ig)) {
    $component = 'GNB';
  }
  if (($OptionName =~ /AMD FCH Common Options/ig) || ($OptionName =~ /AMD FCH Debug Options/ig)) {
    $component = 'FCH';
  }
  if (($OptionName =~ /Promontory Common Options/ig) || ($OptionName =~ /Promontory Debug Options/ig)) {
    $component = 'Promontory';
  }
  # SOC 15
  if (($OptionName =~ /Zen Common Options/ig) || ($OptionName =~ /Zen Debug Options/ig)) {
    $component = 'CCX';
  }
  if (($OptionName =~ /DF Common Options/ig) || ($OptionName =~ /DF Debug Options/ig)) {
    $component = 'DF';
  }
  if (($OptionName =~ /UMC Common Options/ig) || ($OptionName =~ /UMC Debug Options/ig)) {
    $component = 'UMC';
  }
  if (($OptionName =~ /NBIO Common Options/ig) || ($OptionName =~ /NBIO Debug Options/ig)
  || ($OptionName =~ /SMU Debug Options/ig)) {
    $component = 'GNB';
  }
  if (($OptionName =~ /FCH Common Options/ig) || ($OptionName =~ /FCH Debug Options/ig)) {
    $component = 'FCH';
  }

  return $component;
}
#########################################################
#
# Parse cbs database and generate vfr, header, uni files
#
# IN      : Pointer to the database want to be parsed
# IN      : CBS version, it could be internal/external
# IN      : parent section
# IN      : root section
#
#########################################################
sub parseCbs {
  my $cbsDataBase = shift;
  my $rootSection = shift;
  my $component = 'NA';


  foreach my $thisOption (@{$cbsDataBase}) {
    if ($thisOption->{'Type'} =~ /^SECTION$/i) {
        # get component
        $component = GetComponentName ($thisOption->{'Name'});
        next if (($component eq 'Promontory') && ($promontorySupport == 0));
        # Ignore the setction with name (Obsolete)
        next if ($thisOption->{'Name'} =~ /\(Obsolete\)\s*$/i);
        $indentNum = $indentNumSaved;
        &parseCbsSection ($thisOption->{'ITEM'},  $thisOption, $rootSection, $component);
    }
  }
}

#########################################################
#
# Parse a cbs SECTION and generate vfr, header, uni files
#
# IN      : Pointer to the database want to be parsed
# IN      : CBS version, it could be internal/external
# IN      : parent section
# IN      : root section
# IN      : component (CPU/GNB/FCH)
#
#########################################################
sub parseCbsSection {
  my $cbsDataBase = shift;
  my $parentSection = shift;
  my $rootSection = shift;
  my $component = shift;
  my $firstOption = 'TRUE';
  my $parentSectionName = $parentSection->{'Name'};
  my $Visibility = $parentSection->{'Visibility'};
  # if (!($Visibility =~ /^External$/i)) {
  #     $Visibility = 'Internal';
  # }
  # 2nd, generate uni, header, vfr files
  foreach my $thisOption (@{$cbsDataBase}) {
    if (ref ($thisOption->{'Variable_name'}) ne 'HASH') {
      #Fix build issue on setup related file generation, replace "\n" with string "\n"
      $thisOption->{'Help_text'} =~ s/\n/\\n/g;

      &generateIdsFiles($component, $Visibility, $thisOption);
    }
  }



  # 6th #endif
#  if (($component eq 'CPU') || ($component eq 'GNB') || ($component eq 'FCH')) {
#    print $vfrFile '  ' x $indentNum."#endif\n\n\n";
#  }

  # 7th, parse sub 'SECTION's
  my $indentNumSaved = $indentNum + 1;
  foreach my $thisOption (@{$cbsDataBase}) {
    if ($thisOption->{'Type'} =~ /^SECTION$/i) {
      $indentNum = $indentNumSaved;
      &parseCbsSection ($thisOption->{'ITEM'}, $thisOption, $rootSection, $component);
    }
  }
}


#########################################################
#
# Generate copyright
#
#########################################################
sub generateFileHeader
{
  my $idsNvIdFile = shift;
  my $idsNvIntIdFile = shift;
  my $copyright = "/*****************************************************************************
 *
 * Copyright 2008 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting You permission to use this software and documentation (if
 * any) (collectively, the \"Software\") pursuant to the terms and conditions of
 * the Software License Agreement included with the Software. If You do not have
 * a copy of the Software License Agreement, contact Your AMD representative for
 * a copy.
 *
 * You agree that You will not reverse engineer or decompile the Software, in
 * whole or in part, except as allowed by applicable law.
 *
 * WARRANTY DISCLAIMER: THE SOFTWARE IS PROVIDED \"AS IS\" WITHOUT WARRANTY OF ANY
 * KIND. AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
 * BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, QUALITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT AND WARRANTIES
 * ARISING FROM CUSTOM OF TRADE OR COURSE OF USAGE WITH RESPECT TO THE SOFTWARE,
 * INCLUDING WITHOUT LIMITATION, THAT THE SOFTWARE WILL RUN UNINTERRUPTED OR
 * ERROR-FREE. THE ENTIRE RISK ASSOCIATED WITH THE USE OF THE SOFTWARE IS
 * ASSUMED BY YOU. Some jurisdictions do not allow the exclusion of implied
 * warranties, so the above exclusion may not apply to You, but only to the
 * extent required by law.
 *
 * LIMITATION OF LIABILITY AND INDEMNIFICATION: TO THE EXTENT NOT PROHIBITED BY
 * APPLICABLE LAW, AMD AND ITS LICENSORS WILL NOT, UNDER ANY CIRCUMSTANCES BE
 * LIABLE TO YOU FOR ANY PUNITIVE, DIRECT, INCIDENTAL, INDIRECT, SPECIAL OR
 * CONSEQUENTIAL DAMAGES ARISING FROM POSSESSION OR USE OF THE SOFTWARE OR
 * OTHERWISE IN CONNECTION WITH ANY PROVISION OF THIS AGREEMENT EVEN IF AMD AND
 * ITS LICENSORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. THIS
 * INCLUDES, WITHOUT LIMITATION, DAMAGES DUE TO LOST OR MISAPPROPRIATED DATA,
 * LOST PROFITS OR CONFIDENTIAL OR OTHER INFORMATION, FOR BUSINESS INTERRUPTION,
 * FOR PERSONAL INJURY, FOR LOSS OF PRIVACY, FOR FAILURE TO MEET ANY DUTY
 * INCLUDING OF GOOD FAITH OR REASONABLE CARE, FOR NEGLIGENCE AND FOR ANY OTHER
 * PECUNIARY OR OTHER LOSS WHTSOEVER. In no event shall AMD's total liability to
 * You for all damages, losses, and causes of action (whether in contract, tort
 * (including negligence) or otherwise) exceed the amount of \$50 USD. You agree
 * to defend, indemnify and hold harmless AMD, its subsidiaries and affiliates
 * and their respective licensors, directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your
 * possession or use of the Software or violation of the terms and conditions of
 * this Agreement.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS: Notice to U.S. Government End Users. The
 * Software and related documentation are \"commercial items\", as that term is
 * defined at 48 C.F.R. Section 2.101, consisting of \"commercial computer
 * software\" and \"commercial computer software documentation\", as such terms are
 * used in 48 C.F.R. Section 12.212 and 48 C.F.R. Section 227.7202,
 * respectively. Consistent with 48 C.F.R. Section 12.212 or 48 C.F.R. Sections
 * 227.7202-1 through 227.7202-4, as applicable, the commercial computer
 * software and commercial computer software documentation are being licensed to
 * U.S. Government end users: (a) only as commercial items, and (b) with only
 * those rights as are granted to all other end users pursuant to the terms and
 * conditions set forth in this Agreement. Unpublished rights are reserved under
 * the copyright laws of the United States.
 *
 * EXPORT RESTRICTIONS:  You shall adhere to all applicable U.S. import/export
 * laws and regulations, as well as the import/export control laws and
 * regulations of other countries as applicable. You further agree You will not
 * export, re-export, or transfer, directly or indirectly, any product,
 * technical data, software or source code received from AMD under this license,
 * or the direct product of such technical data or software to any country for
 * which the United States or any other applicable government requires an export
 * license or other governmental approval without first obtaining such licenses
 * or approvals, or in violation of any applicable laws or regulations of the
 * United States or the country where the technical data or software was
 * obtained. You acknowledges the technical data and software received will not,
 * in the absence of authorization from U.S. or local law and regulations as
 * applicable, be used by or exported, re-exported or transferred to: (i) any
 * sanctioned or embargoed country, or to nationals or residents of such
 * countries; (ii) any restricted end-user as identified on any applicable
 * government end-user list; or (iii) any party where the end-use involves
 * nuclear, chemical/biological weapons, rocket systems, or unmanned air
 * vehicles.  For the most current Country Group listings, or for additional
 * information about the EAR or Your obligations under those regulations, please
 * refer to the website of the U.S. Bureau of Industry and Security at
 * http://www.bis.doc.gov/.
 *
 ***************************************************************************/


";
my $infCopyright = "#;*****************************************************************************
#;
#; Copyright 2008 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
#;
#; AMD is granting You permission to use this software and documentation (if
#; any) (collectively, the \"Software\") pursuant to the terms and conditions of
#; the Software License Agreement included with the Software. If You do not have
#; a copy of the Software License Agreement, contact Your AMD representative for
#; a copy.
#;
#; You agree that You will not reverse engineer or decompile the Software, in
#; whole or in part, except as allowed by applicable law.
#;
#; WARRANTY DISCLAIMER: THE SOFTWARE IS PROVIDED \"AS IS\" WITHOUT WARRANTY OF ANY
#; KIND. AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
#; BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, QUALITY,
#; FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT AND WARRANTIES
#; ARISING FROM CUSTOM OF TRADE OR COURSE OF USAGE WITH RESPECT TO THE SOFTWARE,
#; INCLUDING WITHOUT LIMITATION, THAT THE SOFTWARE WILL RUN UNINTERRUPTED OR
#; ERROR-FREE. THE ENTIRE RISK ASSOCIATED WITH THE USE OF THE SOFTWARE IS
#; ASSUMED BY YOU. Some jurisdictions do not allow the exclusion of implied
#; warranties, so the above exclusion may not apply to You, but only to the
#; extent required by law.
#;
#; LIMITATION OF LIABILITY AND INDEMNIFICATION: TO THE EXTENT NOT PROHIBITED BY
#; APPLICABLE LAW, AMD AND ITS LICENSORS WILL NOT, UNDER ANY CIRCUMSTANCES BE
#; LIABLE TO YOU FOR ANY PUNITIVE, DIRECT, INCIDENTAL, INDIRECT, SPECIAL OR
#; CONSEQUENTIAL DAMAGES ARISING FROM POSSESSION OR USE OF THE SOFTWARE OR
#; OTHERWISE IN CONNECTION WITH ANY PROVISION OF THIS AGREEMENT EVEN IF AMD AND
#; ITS LICENSORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. THIS
#; INCLUDES, WITHOUT LIMITATION, DAMAGES DUE TO LOST OR MISAPPROPRIATED DATA,
#; LOST PROFITS OR CONFIDENTIAL OR OTHER INFORMATION, FOR BUSINESS INTERRUPTION,
#; FOR PERSONAL INJURY, FOR LOSS OF PRIVACY, FOR FAILURE TO MEET ANY DUTY
#; INCLUDING OF GOOD FAITH OR REASONABLE CARE, FOR NEGLIGENCE AND FOR ANY OTHER
#; PECUNIARY OR OTHER LOSS WHTSOEVER. In no event shall AMD's total liability to
#; You for all damages, losses, and causes of action (whether in contract, tort
#; (including negligence) or otherwise) exceed the amount of \$50 USD. You agree
#; to defend, indemnify and hold harmless AMD, its subsidiaries and affiliates
#; and their respective licensors, directors, officers, employees, affiliates or
#; agents from and against any and all loss, damage, liability and other
#; expenses (including reasonable attorneys' fees), resulting from Your
#; possession or use of the Software or violation of the terms and conditions of
#; this Agreement.
#;
#; U.S. GOVERNMENT RESTRICTED RIGHTS: Notice to U.S. Government End Users. The
#; Software and related documentation are \"commercial items\", as that term is
#; defined at 48 C.F.R. Section 2.101, consisting of \"commercial computer
#; software\" and \"commercial computer software documentation\", as such terms are
#; used in 48 C.F.R. Section 12.212 and 48 C.F.R. Section 227.7202,
#; respectively. Consistent with 48 C.F.R. Section 12.212 or 48 C.F.R. Sections
#; 227.7202-1 through 227.7202-4, as applicable, the commercial computer
#; software and commercial computer software documentation are being licensed to
#; U.S. Government end users: (a) only as commercial items, and (b) with only
#; those rights as are granted to all other end users pursuant to the terms and
#; conditions set forth in this Agreement. Unpublished rights are reserved under
#; the copyright laws of the United States.
#;
#; EXPORT RESTRICTIONS:  You shall adhere to all applicable U.S. import/export
#; laws and regulations, as well as the import/export control laws and
#; regulations of other countries as applicable. You further agree You will not
#; export, re-export, or transfer, directly or indirectly, any product,
#; technical data, software or source code received from AMD under this license,
#; or the direct product of such technical data or software to any country for
#; which the United States or any other applicable government requires an export
#; license or other governmental approval without first obtaining such licenses
#; or approvals, or in violation of any applicable laws or regulations of the
#; United States or the country where the technical data or software was
#; obtained. You acknowledges the technical data and software received will not,
#; in the absence of authorization from U.S. or local law and regulations as
#; applicable, be used by or exported, re-exported or transferred to: (i) any
#; sanctioned or embargoed country, or to nationals or residents of such
#; countries; (ii) any restricted end-user as identified on any applicable
#; government end-user list; or (iii) any party where the end-use involves
#; nuclear, chemical/biological weapons, rocket systems, or unmanned air
#; vehicles.  For the most current Country Group listings, or for additional
#; information about the EAR or Your obligations under those regulations, please
#; refer to the website of the U.S. Bureau of Industry and Security at
#; http://www.bis.doc.gov/.
#;*****************************************************************************

";
  my $warningLine = "//This file is auto generated, don't edit it manually\n\n";

  print $idsNvIdFile $copyright.$warningLine;
  print $idsNvIntIdFile $copyright.$warningLine;
}


#########################################################
#
# Convert CBS Variable Name to Base Variable Name used in IDS/APCB Generation
#
#########################################################
sub convertCbsVarNametoBaseVarName
{
  my $cbsVarName = shift;
  my $baseVarName = $cbsVarName;
  $baseVarName =~ s/^Cbs//;
  $baseVarName =~ s/([a-z0-9])([A-Z])/$1_$2/g;
  $baseVarName =~ s/([A-Z]+)([A-Z][a-z0-9]+)/$1_$2/g;
  #Delete the word can't be used in C language
  $baseVarName =~ s/\W//g;
  return uc $baseVarName;
}
#########################################################
#
# Get Variable Type String from CBS XML "DataType"
#
#########################################################
sub GetVarTypeStr 
{
  my $cbsNvType = shift;
  if ($cbsNvType =~ /^\s*Byte\s*$/i) {
    return "UINT8";
  } elsif ($cbsNvType =~ /^\s*Word\s*$/i) {
    return "UINT16";
  }  elsif ($cbsNvType =~ /^\s*Dword\s*$/i) {
    return "UINT32";
  }  elsif ($cbsNvType =~ /^\s*Qword\s*$/i) {
    return "UINT64";
  } 
}

#########################################################
#
# Get AUTO choice according NV value
# Return: (AutoExist, AutoValue)
#
#########################################################
sub GetAutoValue
{
  my $option = shift;
  my $exist = 0;
  my $value;

  if ($option->{'Input_type'} =~ /^Fixed$/i) {
    #Loop the choice to search the AUTO choice
    foreach my $choice (@{$option->{'OPTION_ITEM'}}) {
      if ($choice->{"Name"} =~ /^Auto$/i) {
        $exist = 1;
        $value = $choice->{"Nv_storage"};
        last;
      }
    }
  }
  return ($exist, $value);
}

#########################################################
#
# Generate IDS, APCB related files
#
#########################################################
sub generateIdsFiles
{
  my $component = shift;
  my $Visibility = shift;
  my $thisOption = shift;
  my $_idsNvIdFile;
  my $_idsNvDefFile;

  #Add IDS NV ID
  if ($thisOption->{'Type'} =~ /^OPTION$/i) {

    my $idsIdStr;
    my $idsNvIdStr;
    my $optName;
    my $optHelp;
    my $pcdUsed = 0;
    my $pcdFullToken;
    my $pcdToken;
    my $pcdGetFunc;
    my $pcdSetFunc;
    my $baseName;
    my $pcdFuncOverride = "";


    $idsIdStr = $thisOption->{'Variable_name'};
    $optName = $thisOption->{'Name'};
    $optHelp = $thisOption->{"Help_text"};
    #Trim space at end of line to avoid style issue
    $optName =~ s/\s*$//;
    $optHelp =~ s/\s*$//;
    #Generate IDS NV ID String by convert CBS variable Name
    $baseName = &convertCbsVarNametoBaseVarName ($idsIdStr);
    $idsNvIdStr = "IDSNVID_".$baseName;

    #>>print the line to IdsNvId.h as above below line
    ##define IDSNVID_DBG_GNB_PCIE_LANES_TOPO   (0x018C) //PCIe lanes topology
    # printf $_idsNvIdFile "#define %s   (0x%04X) //%s\n", $idsNvIdStr, $idsIdNum++, $optName;

    $IdsIdStruct->{$idsNvIdStr}->{$Program} = $Visibility;
    $IdsIdStruct->{$idsNvIdStr}->{"Name"} = $optName;
    $IdsIdStruct->{$idsNvIdStr}->{"IdsIdStr"}= $idsNvIdStr;
    if ($IdsIdStruct->{$idsNvIdStr}->{"Id"} eq undef) {
       $IdsIdStruct->{$idsNvIdStr}->{"Id"} = $Id++
    }
  }
}

sub refineStruct {
  foreach $key (keys %$IdsIdStruct) {
    $sortedIdsIdStruct->[$IdsIdStruct->{$key}->{"Id"}] = $IdsIdStruct->{$key};
  }
  # print Dumper ($sortedIdsIdStruct);
}

sub OutputIdsId {
  my $filehandle;
  foreach $idsid (@$sortedIdsIdStruct) {
    # print "x".Dumper $idsid;
    foreach $program (keys %supportedProgram) {
      if ($idsid->{$program} eq 'External') {
        $filehandle = $idsFiles->{$program}->{'External'};
        printf $filehandle "\n#ifndef %s\n", $idsid->{"IdsIdStr"};
        printf $filehandle "  #define %s   (0x%04X) //%s\n", $idsid->{"IdsIdStr"},  $idsid->{"Id"}, $idsid->{"Name"};
        printf $filehandle "#endif\n";
      } elsif ($idsid->{$program} eq 'Internal') {
        $filehandle =  $idsFiles->{$program}->{'Internal'};
        printf  $filehandle "#define %s   (0x%04X) //%s\n", $idsid->{"IdsIdStr"}, $idsid->{"Id"}, $idsid->{"Name"};
      }
    }
  }
}