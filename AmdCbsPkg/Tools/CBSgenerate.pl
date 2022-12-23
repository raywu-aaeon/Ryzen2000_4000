#;*****************************************************************************
#;
#; Copyright 2008 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
#;******************************************************************************
use Getopt::Long; #Library to parse and interpret arguments
use XML::Simple qw(XMLin XMLout );
use Data::Dumper;
use Encode qw(encode decode);
use CommonGen qw (generateUniFileStr generateHFile generateLableStr generateKeyStr generateVfrFile generateBlankLine
genStrToken genLableToken attachUniStr generateSetDefaultValueFile);
use strict;

#Version 2.1.13 11/13/2019
# Fix hex value bug

#Version 2.1.12 02/27/2019
# Show/Hide Bixby CBS options

#Version 2.1.11 11/27/2018
# Add Renoir support

#Version 2.1.10 10/12/2018
# Change APCB bool algorithm from auto detected to force by keyword in Apcb_structure attribute
# Warning message "APCB BOOL type is suggested" when a option match AUTO detect algorithm

#Version 2.1.F 10/02/2018
# Enchancement for PLAT-37287: [CBS] generate KEY ID based on variable name

#Version 2.1.E 09/25/2018
# Enchancement for PLAT-37038 [CBS] modify PCD only if this option is active
# Fix for PLAT-36847 [Jenkins] RomeEthanolxMasterCi #1745 build failure due bixby.dec is not included in generated inf file

#Version 2.1.D 07/04/2018
# Fix some items is not generated in ApcbSetDataXX.c
# Stop for 3 seconds if warning occurs

#Version 2.1.C 06/22/2018
#Add support for APCB V3

#Version 2.1.B 04/18/2018
#Generate APCB default non-auto value in ApcbAutoGenXX.h if '--apcbfile' is not specified

#Version 2.1.A 03/07/2018
# When generate .uni, only keep the last word for the options whose name have '_Legal_Disclaimer_'
#   for example 'CustomPstate_Legal_Disclaimer_Accept' would be 'Accept'
#               'CustomPstate_Legal_Disclaimer_Decline' would be 'Decline'

#Version 2.1.9 01/05/2018
# Fix include internal IDS header file in external file

#Version 2.1.8 12/28/2017
# If '--apcbfile' is not specified:
#   * Not generate ApcbAutoGenXX.h
#   * Not generate APCB token name automatically, instead always use the attribute 'Apcb_structure'

#Version 2.1.7 12/18/2017
# Create initial AmdCbsVariable.h if not specified variable-file in the parameter

#Version 2.1.6 11/30/2017
# Fix the issue which append the "Rsv_XXX" unexpectedly

#Version 2.1.5 11/22/2017
# Add new function to keep generated CBS variable.h structure order.

#Version 2.1.4 11/16/2017
# Update the generated AmdCbsVariable.h
#   1. Add Header, including Guid, and NewRecordOffset
#   2. Reserved addtion 1K for option growth

#Version 2.1.3 10/18/2017
# Add SSP support

#Version 2.1.2 09/06/2017
# Remove IDS NV ID headerfile generation, the function has been move to IdsIdGen.pl

#Version 2.1.1 12/19/2016
# Remove the RV inf reference from autogen inf file

#Version 2.1.0 11/09/2016
# Correct the APCB AutoGen header file name for RV

#Version 2.0.F 10/08/2016
# Ignore non-ascii string from input XML file

#Version 2.0.E 8/31/2016
# Remove $CodeBase, from this version, we will not support different IBV.

#Version 2.0.D 8/18/2016
# Support 'text' type options and new field 'Goto Section', this is for legal disclaimer.

#Version 2.0.C 4/07/2016
# Fix RE pattern issue of word, Dword, Qword

#Version 2.0.B 3/18/2016
# Fix Attrib error in setIdsNv

#Version 2.0.A 3/15/2016
# Change support for setApcbData file generation
# Seperate the APCB token in CMN/DBG

#Version 2.0.9 3/10/2016
# Add support for setApcbData file generation
# Seperate the APCB token in EXT/INT

#Version 2.0.8 3/7/2016
# Support PCD Datatype overriden
# Support new RE Rule for Pcd filed (PackagePcdTokenSpaceGuid.PcdToken(BOOL|UINT8|UINT16|UINT32|UINT64))
# Add Cbs Pcd Inf file generation

#Version 2.0.7 3/4/2016
# New rule of splitting CbsVariable name into token definitions isolated with underscores
# ABCDExxxx => ABCD_EXXX

#Version 2.0.6 3/3/2016
# Split two capital letters in the APCB token name with an underscore

#Version 2.0.5 3/3/2016
# Split a number and a capital letter in the APCB token name with an underscore

#Version 2.0.4 2/23/2016
# Ignore the section with "(Obsolete)" at the end of the string
# Replace the change line to string "\n" in help string

#Version 2.0.3 2/23/2016
# Add support for APCB file generation

#Version 2.0.2 2/22/2016
# Add support for PCD related files

#Version 2.0.1 2/14/2016
# Seperate IDS Internal/external files
# Add Program string to IDS files
# Allocate ID for ZP IDS

#Version 2.0.0 1/27/2016
# Add support for IDS Files: Nvid, NvDef, IdsNvTable, Idssample

#Global variable
my $toolVersion="2.1.13";
my $toolName="CBS Generator";
my $indentNum;
my $hFile;
my $lableFile;
my $uniFile;
my $uniFileStr;
my $vfrFile;
my $setDefaultValueFile;
my $inputFile;
my $inputApcbFile;
my $gbsFile;
my $idsNvDefFile;
my $idsNvIntDefFile;
my $idsSampleFile;
my $cbsIdsNvFile;
my $cbsSetPcdCFile;
my $cbsSetPcdInfFile;
my $apcbAutoGenFile;
my $apcbSetDataFile;
my $inputVariableFile;
my $gOriCbsVariable;
my $gOriCbsVariableLastIndex;
my $gOriCbsVariableRsvdSize;
my $gOriCbsVariableStructUniqueValue;
my $gCurCbsVariable;
my $gFinalCbsVariable = {};
my @gFinalVariable;
my $gFinalCbsVariableStructUniqueValue;
my $gNewAddedVariableSize =0;
my $outputpath;
my $version;
my $formID;
my $help;
my $rootLable='CBS_ROOT';
my $lableStartID;
my $lableIDOutput;
my $keyIDOutput;
my %uniExistHash;
my %keyIDExistHash;
my $gbsSetting;
my $bcomboFlag;
my $packFlag;
my $promontorySupport = 0;
my $bixbySupport = 1;
my $idsIdNum = 0;
my $idsIdNumEnd = 0;
my $idsNvSize = 0;
my $IDS_NV_RECORD_U8_SIZE = 4;
my $IDS_NV_RECORD_U16_SIZE = 5;
my $IDS_NV_RECORD_U32_SIZE = 7;
my $IDS_NV_RECORD_U64_SIZE = 11;
my $IDS_ID_START_ZP = 0x0000;
my $IDS_ID_END_ZP = 0x0FFF;
my $IDS_ID_START_RV = 0x1000;
my $IDS_ID_END_RV = 0x1FFF;
my $IDS_ID_START_RN = 0x2000;
my $IDS_ID_END_RN = 0x2FFF;

my $gVarChoiceDict;
#ZP Zeppelin
my $Program;
#APCB use only
my $gApcbDb = {};
#APCB Token Macros
my $gApcbV2TokenValueStr;
#APCB Default Attributes & Values
my $gApcbV2ExtAttribStr;
my $gApcbV2IntAttribStr;
my $gApcbV2ExtValueStr;
my $gApcbV2IntValueStr;
#For Set APCB File>>>
my $gApcbExtAttribSetStr;
my $gApcbIntAttribSetStr;

my $gApcbExtValueSetStr;
my $gApcbIntValueSetStr;
my $cbsApcbPortingFile;

#switch for APCB V3
my $gApcbVer = 0;
#APCB V3
my $gApcbV3TokenValueStr;
my $gApcbV3ExtBoolStr;
my $gApcbV3ExtU8Str;
my $gApcbV3ExtU16Str;
my $gApcbV3ExtU32Str;
my $gApcbV3IntBoolStr;
my $gApcbV3IntU8Str;
my $gApcbV3IntU16Str;
my $gApcbV3IntU32Str;
my $gApcbV3TokenSetStr;
#CbsIdsNv {ID, Offset} Arrays.
my $gCbsIdsNvU8  = "STATIC IDS_NV_RECORD mIdsNv8[] = {";
my $gCbsIdsNvU16 = "STATIC IDS_NV_RECORD mIdsNv16[] = {";
my $gCbsIdsNvU32 = "STATIC IDS_NV_RECORD mIdsNv32[] = {";
my $gCbsIdsNvU64 = "STATIC IDS_NV_RECORD mIdsNv64[] = {";
#Debug verbose control
my $gDbgVerbose=0;
my $gWarningStopFlag = 0;

printf "%s - Version %s\n\n", $toolName, $toolVersion;
print "parse input parameters...\n";
# parse input parameters
parseinput ();

my $year = `date /t`;
$year =~ /(\d{4})/i;
$year = $1;

print "parse XML file...\n";
my $inputFileStr;
{
  print "Open $inputFile in binary mode, and replace non-ascii value\n";
  open  my $BinFileHdr,"<$inputFile" or die"Can't open $inputFile\n";
  binmode $BinFileHdr;
  local $/ = \1;
  my $NonAsciiDetected = 0;
  while (my $byte = <$BinFileHdr>) {
    if (ord($byte) >= 0x80) {
      $NonAsciiDetected = 1;
    } else {
      $inputFileStr .= $byte;
    }
  }
  # WA for exe file generate, Remove "0D" from input string to avoid unexpected "0D" output
  $inputFileStr =~ s/\r//g;
  if ($NonAsciiDetected) {
    print "\n[Warning] NonAsciiDetected, character has been removed\n";
    # $gWarningStopFlag = 1;
  }
}

my $rootCfgHash = XMLin("$inputFileStr", forcearray => qr/ITEM$/);
if ($gbsFile ne '') {
  $gbsSetting = XMLin ("$gbsFile",forcearray => ['Option']);
  &updateDefaultValue ($rootCfgHash->{'ITEM'});
}
# Build Variable Name and Choices Dict for further use
# It can be used to check if Active_condition or Display_condition matches
  # open  DP1,">DP1.txt" or die"Can't open $inputFile\n";

  # print DP1 Dumper($rootCfgHash->{'ITEM'});
# &BuildVarChoiceDict ($rootCfgHash->{'ITEM'});
  # open  DP2,">DP2.txt" or die"Can't open $inputFile\n";

# print DP2 Dumper $gVarChoiceDict;
# die;
# Get Program string, and init related variable
$Program = GetProgramStr ($rootCfgHash->{'Name'});
if ($Program eq 'ZP') {
  $idsIdNum = $IDS_ID_START_ZP;
  $idsIdNumEnd = $IDS_ID_END_ZP;
} elsif ($Program eq 'RV') {
  $idsIdNum = $IDS_ID_START_RV;
  $idsIdNumEnd = $IDS_ID_END_RV;
} elsif ($Program eq 'RN') {
  $idsIdNum = $IDS_ID_START_RN;
  $idsIdNumEnd = $IDS_ID_END_RN;
}
&InitApcbSetting ();

# Check the valida
# 1st, initilize $lableStartID, $lableIDOutput, $keyIDOutput, %uniExistHash, %keyIDExistHash
if ($formID ne '') {
  $lableStartID = $formID;
} else {
  $lableStartID = 0x7000;
}
$lableIDOutput = '';
$keyIDOutput = '';
%uniExistHash = '';
%keyIDExistHash = '';

my $gNewCbsVariableStructUniqueValue = int (rand (0xFFFF)) << 16 | int (rand (0xFFFF));

# collect current CBS variable structure order before generate the new file
if ($inputVariableFile ne '') {
  &collectCbsVariableInfo ($inputVariableFile);
}

print "Creating files...\n";
# 2nd, open files and init file str
open $hFile, ">".$outputpath."AmdCbsVariable.h" or die "Can't create the AmdCbsVariable.h";
open $lableFile, ">".$outputpath."AmdCbsFormID.h" or die "Can't create the AmdCbsFormID.h";
open $uniFile, ">".$outputpath."AmdCbsStrings.uni" or die "Can't create the AmdCbsStrings.uni";
open $vfrFile, ">".$outputpath."AmdCbsForm.vfr" or die "Can't create the AmdCbsForm.vfr";
open $setDefaultValueFile, ">".$outputpath."AmdCbsDefault.c" or die "AmdCbsDefault.c";
open $idsNvDefFile, ">".$outputpath."IdsNvDef".$Program.".h" or die "IdsNvDef.h";
open $idsNvIntDefFile, ">".$outputpath."IdsNvIntDef".$Program.".h" or die "IdsNvIntDef.h";
open $idsSampleFile, ">".$outputpath."IdsSample".$Program.".c" or die "IdsSample.c";
open $cbsIdsNvFile, ">".$outputpath."CbsIdsNv".$Program.".c" or die "CbsIdsNv.c";
open $cbsSetPcdCFile, ">".$outputpath."CbsSetAgesaPcdLib".$Program.".c" or die "CbsSetAgesaPcdLib.c";
open $cbsSetPcdInfFile, ">".$outputpath."CbsSetAgesaPcdLib".$Program.".inf" or die "CbsSetAgesaPcdLib.inf";
open $apcbAutoGenFile, ">".$outputpath."ApcbAutoGen".$Program.".h" or die "ApcbAutoGen.h";
open $apcbSetDataFile, ">".$outputpath."ApcbSetData".$Program.".c" or die "ApcbSetData.c";
$uniFileStr = "\x{FEFF}/=#\n";


# 3rd, copyright
&generateFileHeader;

# 4th, #ifndef
print $hFile "#ifndef _AMD_CBS_VARIABLE_H_\n#define _AMD_CBS_VARIABLE_H_\n\n";
print $hFile "#pragma pack(push,";
print $hFile $packFlag;
print $hFile ")\n\n";

print $hFile "typedef struct _CBS_VARIABLE_HEADER\n";
print $hFile "{\n";
print $hFile "  UINT32 CbsVariableStructUniqueValue;                                 ///< Will be different if CBS varialbe structure changes\n";
print $hFile "  UINT32 NewRecordOffset;                                         ///< Record the offset of reserved region start, which also the offset of the new record\n";
print $hFile "  UINT8  Reserved[24];                                            ///< Reserved for future use\n";
print $hFile "} CBS_VARIABLE_HEADER;\n";
print $hFile "\n\ntypedef struct _CBS_CONFIG {\n";
print $hFile "  CBS_VARIABLE_HEADER  Header;                                    ///< Variable header\n";


print $lableFile "#ifndef _AMD_CBS_FORM_ID_H_\n#define _AMD_CBS_FORM_ID_H_\n\n";
print $lableFile "  #define CBS_CONFIGURATION_VARSTORE_ID                                           0x5000\n";

printf $idsNvDefFile "#ifndef _IDS_NV_DEF_%s_H_\n#define _IDS_NV_DEF_%s_H_\n\n", $Program, $Program;
printf $idsNvIntDefFile "#ifndef _IDS_NV_INT_DEF_%s_H_\n#define _IDS_NV_INT_DEF_%s_H_\n\n", $Program, $Program;
printf $apcbAutoGenFile "#ifndef _APCB_AUTOGEN_%s_H_\n#define _APCB_AUTOGEN_%s_H_\n\n", $Program, $Program;
print "Generating files...\n";
# 5th, .vfr .h .uni
$indentNum = 1;
&generateCbsFiles ($rootCfgHash->{'ITEM'}, $version);
  # open  DP1,">ori.txt" or die"Can't open $inputFile\n";

  # print DP1 Dumper($gOriCbsVariable);

  # open   DP2,">cur.txt" or die"Can't open $inputFile\n";
  # print DP2 Dumper($gCurCbsVariable);
# Merge original CBS variable structure and current CBS variable structure, and keep the order as original one
# do the print After merge done
if ($inputVariableFile ne '') {
  &mergeCbsVariables ();
}

# 6th, output $lableIDOutput and $keyIDOutput to file
print $lableFile "$lableIDOutput$keyIDOutput";
# print Dumper($gApcbDb);
if ($gApcbVer == 2) {
  concatenateApcbStrV2 ();
} elsif ($gApcbVer == 3) {
  concatenateApcbStrV3 ();
}

# 7th, #endif
if ($inputVariableFile eq '') {
  printf $hFile "\n  UINT8         Reserved[1024];                                   ///< Reserved for option growth\n";
  $gFinalCbsVariableStructUniqueValue = $gNewCbsVariableStructUniqueValue;
} else {
  printf $hFile "\n  UINT8         Reserved[%d];                                   ///< Reserved for option growth\n", $gOriCbsVariableRsvdSize - $gNewAddedVariableSize;
}

print $hFile "} CBS_CONFIG;\n\n";

printf $hFile "\n///CbsVariableStructUniqueValue 0x%x \n\n", $gFinalCbsVariableStructUniqueValue;
print $hFile "#pragma pack(pop)\n\n";
print $hFile "\n#endif // _AMD_CBS_VARIABLE_H_\n";
print $lableFile "\n#endif // _AMD_CBS_FORM_ID_H_\n";
printf $idsNvDefFile "\n#endif //_IDS_NV_DEF_%s_H_\n", $Program;
printf $idsNvIntDefFile "\n#endif //_IDS_NV_INT_DEF_%s_H_\n", $Program;
printf $apcbAutoGenFile "\n#endif //_APCB_AUTOGEN_%s_H_\n", $Program;
printf $setDefaultValueFile "  Setup_Config->Header.CbsVariableStructUniqueValue = 0x%x;\n
}\n", $gFinalCbsVariableStructUniqueValue;

# 8th, output $uniFileStr to final file handler in UTF-16 encoding
syswrite $uniFile, encode("UTF-16LE", $uniFileStr);

print "Close files...\n";
if ($gWarningStopFlag) {
  sleep (3);
}
# 9th, close files
close $hFile;
close $lableFile;
close $uniFile;
close $vfrFile;
close $setDefaultValueFile;
close $idsNvDefFile;
close $idsNvIntDefFile;
close $idsSampleFile;
close $cbsIdsNvFile;
close $cbsSetPcdCFile;
close $cbsSetPcdInfFile;
close $apcbAutoGenFile;
close $apcbSetDataFile;
print "End\n";
#*----------------------------------------------------------
#*           L O C A L     F U N C T I O N S
#*----------------------------------------------------------
#*
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
      'inputfile=s'   => \$inputFile,
      'outputpath=s'  => \$outputpath,
      'version=s'     => \$version,
      'formID=s'      => \$formID,
      'settingfile=s' => \$gbsFile,
      'bcomboFlag=s'  => \$bcomboFlag,
      'packFlag=s'  => \$packFlag,
      'tPromontorySupport=s' => \$promontorySupport,
      'x=s' => \$bixbySupport,
      'apcbfile=s' => \$inputApcbFile,
      'variable-file=s' => \$inputVariableFile,
      'verbose'       => \$gDbgVerbose,
      'help'          => \$help
  ) or die "Incorrect usage! Try --help for help with usage\n";

  if ($help) {
    &showhelp();
  }

  if ($inputFile eq '') {
    print ("inputFile is Required\n");
    &showhelp();
  }

  if ($version eq '') {
    $version = 'external';
  }

  if ($outputpath eq '') {
    $outputpath = ".\\";
  }

  if ($bcomboFlag eq '') {
    $bcomboFlag = 'disable';
  }

  if ($packFlag eq '') {
    $packFlag = '1';
  }

  if ($promontorySupport eq "1") {
    print "Promontory CBS is generated in this project.\n"
  }elsif ($promontorySupport ne "0"){
    print "Promontory Support should be 0 or 1.\n"
	&showhelp();
  }

  if ($bixbySupport eq "1") {
    print "Bixby CBS is generated in this project.\n"
  }elsif ($bixbySupport ne "0"){
    print "Bixby Support should be 0 or 1.\n"
	&showhelp();
  }

  if ($inputVariableFile eq '') {
    print "--variable-file parameters is not specified, the structure order will not be kept which base on original AmdCbsVariable.h\n" ;
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

  USAGE perl CBSgenerate.pl [-i Input XML file] [-v version] [-o outputpath] [--variable-file cbs variable headerfile]
    [-i Input XML file] specify the input XML file
    [-v Internal|external] specify output file version
        internal  only generate internal files
        external  only generate external files
    [-o outputpath] specify output path e.g -o y:\CBS
    [--variable-file cbs variable headerfile] specify the cbs variable headerfile used keep CBS structure order
  ';
  exit (1);
}
sub DbgPrint {
  if ($gDbgVerbose) {
    printf @_;
  }
}
#########################################################
#
# Get Program Str
#
# IN      : Name filed of XML root
#
#########################################################
sub GetProgramStr {
  my $ProgramStr = shift;
  if ($ProgramStr =~ /^Zeppelin_/i) {
    return 'ZP';
  }
  if ($ProgramStr =~ /^Raven_/i) {
    return 'RV';
  }
  if ($ProgramStr =~ /^Starship_/i) {
    return 'SSP';
  }
  if ($ProgramStr =~ /^Renoir_/i) {
    return 'RN';
  }
}
#########################################################
#
# update default value
#
# IN      : CBS database
#
#########################################################
sub updateDefaultValue {
  my $cbsDataBase = shift;

  foreach my $thisOption (@{$cbsDataBase}) {
    if ($thisOption->{'Type'} =~ /^SECTION$/i) {
      &updateDefaultValue ($thisOption->{'ITEM'});
    } elsif ($thisOption->{'Type'} =~ /^OPTION$/i) {
      if (ref ($thisOption->{'Variable_name'}) ne 'HASH') {
        # update default value according to CBS setting
        foreach my $thisGbsSetting (@{$gbsSetting->{'Option'}}) {
          if ($thisOption->{'Variable_name'} eq $thisGbsSetting->{'VariableName'}) {
            $thisOption->{'BIOS_Default'} = $thisGbsSetting->{'Default'};
          }
        }
      }
    }
  }
}
#########################################################
#
# Build CBS Hash, Variable Name as the key
#
# IN      : CBS database
#
#########################################################
sub BuildVarChoiceDict {
  my $cbsDataBase = shift;
  my $varName;
  my $optName;
  foreach my $thisOption (@{$cbsDataBase}) {
    if ($thisOption->{'Type'} =~ /^SECTION$/i) {
      &BuildVarChoiceDict ($thisOption->{'ITEM'});
    } elsif ($thisOption->{'Type'} =~ /^OPTION$/i) {
      if (ref ($thisOption->{'Variable_name'}) ne 'HASH') {
        # printf "[%s]->(", $thisOption->{'Variable_name'};
        if ((ref ($thisOption->{"OPTION_ITEM"}->[0]->{'Name'}) ne 'HASH')) {
          $varName = $thisOption->{"Variable_name"};
          $varName =~ s/(^\s+|\s+$)//g;
          $gVarChoiceDict->{$varName}->{"BIOS_Default"} = $thisOption->{"BIOS_Default"};
          foreach my $choice (@{$thisOption->{'OPTION_ITEM'}}) {
            $optName = $choice->{"Name"};
            $optName =~ s/(^\s+|\s+$)//g;
            $gVarChoiceDict->{$varName}->{"Choices"}->{$optName} = $choice->{"Nv_storage"};
            # printf "%s->%s,", $choice->{"Name"}, $choice->{"Nv_storage"}
          }
          # printf (")\n");
        }
      }
    }
  }
}

sub InitApcbSetting {
  if (($Program eq "ZP") || ($Program eq "RV")) {
    $gApcbVer = 2;
  } elsif (($Program eq "SSP")) {
    $gApcbVer = 3;
  } elsif (($Program eq "RN")) {
    $gApcbVer = 3;
  } else {
    print ("[Warning] APCB program setting is not initilized\n");
    $gWarningStopFlag = 1;
  }
}

sub collectCbsVariableInfo {
  my $_cbsvariablefile = shift;
  my $_size;
  my $_vairableName;
  my $_index = 0;
  my $_comments = '';
  my $CbsStructBegin = 0;
  open CBS_VARIABLE, "<".$_cbsvariablefile or die "Can't open the $_cbsvariablefile";

  while (<CBS_VARIABLE>) {
    # Parse start from typedef struct _CBS_CONFIG {
    if (/^\s*typedef struct _CBS_CONFIG {\s*$/) {
      $CbsStructBegin = 1;
    }

    if ($CbsStructBegin) {
      # Parse CBS variable stops
      if (/^\s*UINT8\s+Reserved\[(\d+)\]/) {
        $gOriCbsVariableRsvdSize = $1;
        printf "[%d] Bytes reserved in the original variable.h\n", $1;
        $CbsStructBegin = 0;
      }
      if ((/^\s*UINT(\d+)?.+\s+(.+)?;\s*\/\/\/<\s(.+)?\s*$/) && $CbsStructBegin) {
        $_size = $1;
        $_vairableName = $2;
        $_comments = $3;
        # Filter out the rsv words e.g. CbsCmnNbioPPTCtl_RsvDeleted_RsvXXX
        $_vairableName =~ s/(.+)?_Rsv.+/$1/;
        $gOriCbsVariable->{$_vairableName}->{'size'} = $_size + 0; #Convert string to number
        $gOriCbsVariable->{$_vairableName}->{'index'} = $_index++;
        $gOriCbsVariable->{$_vairableName}->{'comments'} = $_comments;
        $gOriCbsVariable->{$_vairableName}->{'name'} = $_vairableName;
      }
    }
# ///CbsVariableStructUniqueValue 0x830b593d
# Get the Unique Value from vairable.h
    if (/^\s*\/\/\/CbsVariableStructUniqueValue\s+0x(.+)?\s*$/) {
      $gOriCbsVariableStructUniqueValue = hex($1);
      printf ("CbsVariableStructUniqueValue in Original Variable 0x%x\n", $gOriCbsVariableStructUniqueValue);
    }
  }
  $gOriCbsVariableLastIndex = $_index;
}

sub addCbsVariable
{
  # my $hFile = shift;
  my $thisOption = shift;
  my $_offset = 0;
  if ($thisOption->{'Type'} =~ /^OPTION$/i) {
    if ($thisOption->{'Nv_type'} =~ /^Byte$/i) {
      $gCurCbsVariable->{$thisOption->{'Variable_name'}}->{'name'} = $thisOption->{'Variable_name'};
      $gCurCbsVariable->{$thisOption->{'Variable_name'}}->{'index'} = 0xFFFF;
      $gCurCbsVariable->{$thisOption->{'Variable_name'}}->{'size'} = 8;
      # $gCurCbsVariable->{$thisOption->{'Variable_name'}}->{'comments'} = sprintf "%s Offset 0x%06X", $thisOption->{'Name'}, $_offset;
      $gCurCbsVariable->{$thisOption->{'Variable_name'}}->{'comments'} =  $thisOption->{'Name'};
      $_offset += 1;
      # printf $hFile "  UINT8         %-50s///< $thisOption->{'Name'}\n", $thisOption->{'Variable_name'}.';';
    } elsif ($thisOption->{'Nv_type'} =~ /^Word$/i) {
      # printf $hFile "  UINT16        %-50s///< $thisOption->{'Name'}\n", $thisOption->{'Variable_name'}.';';
      $gCurCbsVariable->{$thisOption->{'Variable_name'}}->{'name'} = $thisOption->{'Variable_name'};
      $gCurCbsVariable->{$thisOption->{'Variable_name'}}->{'index'} = 0xFFFF;
      $gCurCbsVariable->{$thisOption->{'Variable_name'}}->{'size'} = 16;
      # $gCurCbsVariable->{$thisOption->{'Variable_name'}}->{'comments'} =  sprintf "%s Offset 0x%06X", $thisOption->{'Name'}, $_offset;
      $gCurCbsVariable->{$thisOption->{'Variable_name'}}->{'comments'} =   $thisOption->{'Name'};
      $_offset += 2;
    } elsif ($thisOption->{'Nv_type'} =~ /^DWord$/i) {
      # printf $hFile "  UINT32        %-50s///< $thisOption->{'Name'}\n", $thisOption->{'Variable_name'}.';';
      $gCurCbsVariable->{$thisOption->{'Variable_name'}}->{'name'} = $thisOption->{'Variable_name'};
      $gCurCbsVariable->{$thisOption->{'Variable_name'}}->{'index'} = 0xFFFF;
      $gCurCbsVariable->{$thisOption->{'Variable_name'}}->{'size'} = 32;
      # $gCurCbsVariable->{$thisOption->{'Variable_name'}}->{'comments'} =  sprintf "%s Offset 0x%06X", $thisOption->{'Name'}, $_offset;
      $gCurCbsVariable->{$thisOption->{'Variable_name'}}->{'comments'} =   $thisOption->{'Name'};
      $_offset += 4;
    } elsif ($thisOption->{'Nv_type'} =~ /^QWord$/i) {
      # printf $hFile "  UINT64        %-50s///< $thisOption->{'Name'}\n", $thisOption->{'Variable_name'}.';';
      $gCurCbsVariable->{$thisOption->{'Variable_name'}}->{'name'} = $thisOption->{'Variable_name'};
      $gCurCbsVariable->{$thisOption->{'Variable_name'}}->{'index'} = 0xFFFF;
      $gCurCbsVariable->{$thisOption->{'Variable_name'}}->{'size'} = 64;
      # $gCurCbsVariable->{$thisOption->{'Variable_name'}}->{'comments'} =  sprintf "%s Offset 0x%06X", $thisOption->{'Name'}, $_offset;
      $gCurCbsVariable->{$thisOption->{'Variable_name'}}->{'comments'} =   $thisOption->{'Name'};
      $_offset += 8;
    }
  }
}

sub mergeCbsVariables
{
  my $_cbsVariableName;
  my $_updatedCbsVariable;
  my $_updatedCbsVariableName;
  my $_lastIndex = $gOriCbsVariableLastIndex;

  # set the final variable to original 1st
  $gFinalCbsVariable = {%$gOriCbsVariable};

  open  DP1,">ori.txt" or die"Can't open $inputFile\n";
  print DP1 Dumper(%$gFinalCbsVariable);
  open  DP3,">Cur.txt" or die"Can't open $inputFile\n";
  print DP3 Dumper(%$gCurCbsVariable);
  foreach $_cbsVariableName (keys %{$gFinalCbsVariable}) {
    #if the variable is not exist in current Variable, means it has been delete in new version XML,  marked previous name as reserved
    if (!(exists $gCurCbsVariable->{$_cbsVariableName})) {
      $_updatedCbsVariable = $gFinalCbsVariable->{$_cbsVariableName};
      printf "\"%s\" variable deleted\n", $gFinalCbsVariable->{$_cbsVariableName}->{'name'};

      $_updatedCbsVariableName = $gFinalCbsVariable->{$_cbsVariableName}->{'name'}."_RsvDeleted";
      $_updatedCbsVariable->{'name'} = $_updatedCbsVariableName;
      delete $gFinalCbsVariable->{$_cbsVariableName};
      $gFinalCbsVariable->{$_updatedCbsVariableName} = {%$_updatedCbsVariable};
    } elsif ($gCurCbsVariable->{$_cbsVariableName}->{'size'} ne $gFinalCbsVariable->{$_cbsVariableName}->{'size'}) {
      # Size different
      # or If variable size has been changed, make the original as size changed "RsvSizeF8T16"
      $_updatedCbsVariable = $gFinalCbsVariable->{$_cbsVariableName};
      printf "\"%s\" variable Size change From %d To %d\n", $gFinalCbsVariable->{$_cbsVariableName}->{'name'}, $gFinalCbsVariable->{$_cbsVariableName}->{'size'}, $gCurCbsVariable->{$_cbsVariableName}->{'size'};;
      $_updatedCbsVariableName = sprintf "%s_RsvSizeF%dTo%d",$gFinalCbsVariable->{$_cbsVariableName}->{'name'}, $gFinalCbsVariable->{$_cbsVariableName}->{'size'}, $gCurCbsVariable->{$_cbsVariableName}->{'size'};
      $_updatedCbsVariable->{'name'} = $_updatedCbsVariableName;
      delete $gFinalCbsVariable->{$_cbsVariableName};
      $gFinalCbsVariable->{$_updatedCbsVariableName} = {%$_updatedCbsVariable};
    }
  }
  # open   DP3,">Final.txt" or die"Can't open $inputFile\n";
  # print DP3 Dumper(%$gFinalCbsVariable);
  # die;
  # Loop current variable to find new variables, note the variable size chagned item already changed its name in previous step
  foreach $_cbsVariableName (keys %$gCurCbsVariable) {
    if (!(exists $gFinalCbsVariable->{$_cbsVariableName})) {
      # New items fill it at the tail
      $gFinalCbsVariable->{$_cbsVariableName} = $gCurCbsVariable->{$_cbsVariableName};
      # Update its index
      $gFinalCbsVariable->{$_cbsVariableName}->{'index'} = $_lastIndex++;
      $gNewAddedVariableSize += $gFinalCbsVariable->{$_cbsVariableName}->{'size'}/8;
      printf "New item: \"%s\"  Size: %d bytes\n", $gFinalCbsVariable->{$_cbsVariableName}->{'name'}, $gFinalCbsVariable->{$_cbsVariableName}->{'size'}/8;
    }
  }
  if ($gNewAddedVariableSize) {
    printf "Variable Structure changes, [%d] Bytes new added in the variable.h\n", $gNewAddedVariableSize;
    printf "StructUniqueValue update to 0x%x\n", $gNewCbsVariableStructUniqueValue;
    $gFinalCbsVariableStructUniqueValue = $gNewCbsVariableStructUniqueValue;
    if ($gOriCbsVariableRsvdSize < $gNewAddedVariableSize) {
      printf ("Exceed the limit of reserved region\n");
      exit (1);
    }
  } else {
    print "No Variable Structure changes\n";
    $gFinalCbsVariableStructUniqueValue = $gOriCbsVariableStructUniqueValue;
  }
#   print  Dumper($gFinalCbsVariable);
  # die;
  # foreach $_cbsVariableName (keys %$gOriCbsVariable) {
  #   $OriVairiable[$gOriCbsVariable->{$_cbsVariableName}->{'index'}] = $gOriCbsVariable->{$_cbsVariableName};
  # }
  # open  KEY,">keys.txt" or die"Can't open $inputFile\n";
  # print KEY Dumper($gFinalCbsVariable);

  foreach $_cbsVariableName (keys %$gFinalCbsVariable) {
    $gFinalVariable[$gFinalCbsVariable->{$_cbsVariableName}->{'index'}] = $gFinalCbsVariable->{$_cbsVariableName};
  }
  foreach my $_cbsVariable (@gFinalVariable) {
      printf $hFile "  UINT%-2s        %-50s///< %s\n", $_cbsVariable->{'size'}, $_cbsVariable->{'name'}.';', $_cbsVariable->{'comments'};
  }
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
  my $cbsVersion = shift;

  # code base special hook
  &VfrHookBeforeGen ();
  # support combo CBS
  my $comboOption = &comboCbsHook ($cbsDataBase);
  # Build Variable Name and Choices Dict for further use
  # It can be used to check if Active_condition or Display_condition matches
  &BuildVarChoiceDict ($cbsDataBase);
  open  DP1,">DP1.txt" or die"Can't open $inputFile\n";

  print DP1 Dumper($cbsDataBase);
  # uni file should have a blank string and 'AMD CBS' string
  my $strBlank = genStrToken ('BLANK');
  my $strRootSection = genStrToken($rootLable)."_SECTION";
  my $strRootSectionHelp = genStrToken($rootLable)."_SECTION_HELP";
  $strBlank = sprintf "#string %-70s  #language en-US    \"%s\"\n", $strBlank, '';
  $strRootSection = sprintf "#string %-70s  #language en-US    \"%s\"\n", $strRootSection, 'AMD CBS';
  $strRootSectionHelp = sprintf "#string %-70s  #language en-US    \"%s\"\n", $strRootSectionHelp, 'AMD CBS Setup Page';
  attachUniStr (\$uniFileStr, "#langdef en-US \"English\"\n\n");
  attachUniStr (\$uniFileStr, $strBlank);
  attachUniStr (\$uniFileStr, $strRootSection);
  attachUniStr (\$uniFileStr, $strRootSectionHelp);

  # form ID .h file should have SETUP_CBS_ROOT_LABLE
  my $lableToken = genLableToken ($rootLable);
  $lableIDOutput = sprintf "// Section ID\n  #define %-70s  0x%X\n", $lableToken, $lableStartID;

  $lableStartID++;

  # generate vfr, header and uni files

  &parseCbs ($cbsDataBase, $cbsVersion, $rootLable, $cbsDataBase);

  &VfrHookAfterGen ();
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
  #BIXBY
  if (($OptionName =~ /BIXBY Common Options/ig) || ($OptionName =~ /BIXBY Debug Options/ig)) {
    $component = 'BIXBY';
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
  my $cbsVersion = shift;
  my $parentSection = shift;
  my $rootSection = shift;
  my $component = 'NA';

  # 1st, 'form', 'formid, 'title' and 'subtitle'
  print $vfrFile '  ' x $indentNum."//\n".'  ' x $indentNum."// form - $parentSection\n".'  ' x $indentNum."//\n";
  print $vfrFile '  ' x $indentNum."form\n\n";
  $indentNum++;
  my $lableToken = genLableToken ($parentSection);
  my $StrToken = genStrToken ($parentSection);
  $StrToken = $StrToken.'_SECTION';
  print $vfrFile '  ' x $indentNum."formid        = $lableToken,\n\n";
  print $vfrFile '  ' x $indentNum."title         = STRING_TOKEN \($StrToken\);\n\n";
  print $vfrFile '  ' x $indentNum."subtitle text = STRING_TOKEN \($StrToken\);\n";
  $StrToken = genStrToken ('BLANK');
  print $vfrFile '  ' x $indentNum."subtitle text = STRING_TOKEN \($StrToken\);\n\n";

  # 2nd, generate uni, vfr files for the first level of 'SECTION'
  foreach my $thisOption (@{$cbsDataBase}) {
    if ($thisOption->{'Type'} =~ /^SECTION$/i) {
      if ((($cbsVersion =~ /^external$/i) && ($thisOption->{'Visibility'} =~ /^External$/i)) ||
          ($cbsVersion =~ /^internal$/i)) {
        # get component
        $component = GetComponentName ($thisOption->{'Name'});
        next if (($component eq 'Promontory') && ($promontorySupport == 0));
        next if (($component eq 'BIXBY') && ($bixbySupport == 0));
        # Ignore the setction with name (Obsolete)
        next if ($thisOption->{'Name'} =~ /\(Obsolete\)\s*$/i);
        &generateLableStr(\$lableStartID, \$lableIDOutput, $thisOption);
        &generateUniFileStr(\$uniFileStr, $thisOption, \%uniExistHash);
        &generateVfrFile($vfrFile, $thisOption, $indentNum, $rootSection, \%keyIDExistHash, \$lableStartID, \$keyIDOutput, $component);
      }
    }
    if ($thisOption->{'Type'} =~ /^OPTION$/i) {
        # Fix Combo CBS issue
        $component = GetComponentName ($thisOption->{'Name'});
        next if (($component eq 'Promontory') && ($promontorySupport == 0));
        next if (($component eq 'BIXBY') && ($bixbySupport == 0));
        &generateLableStr(\$lableStartID, \$lableIDOutput, $thisOption);
        &generateUniFileStr(\$uniFileStr, $thisOption, \%uniExistHash);
        &generateVfrFile($vfrFile, $thisOption, $indentNum, $rootSection, \%keyIDExistHash, \$lableStartID, \$keyIDOutput, $component);
        &generateKeyStr(\$lableStartID, \$keyIDOutput, $thisOption);
        if ($inputVariableFile eq '') {
          # Generate to file directly
          &generateHFile($hFile, $thisOption);
        } else {
          # Collect the information for further process
          &addCbsVariable($thisOption);
        }
        &generateSetDefaultValueFile ($setDefaultValueFile, $thisOption);
    }

  }

  # 3rd, 'endform;'
  $indentNum--;
  print $vfrFile '  ' x $indentNum."endform;\n\n\n";

  # 4th, determine if we will generate vfr, header and uni files by checking the first level SECTION's visibility
  my $indentNumSaved = $indentNum + 1;
  foreach my $thisOption (@{$cbsDataBase}) {
    if ($thisOption->{'Type'} =~ /^SECTION$/i) {
      if ((($cbsVersion =~ /^external$/i) && ($thisOption->{'Visibility'} =~ /^External$/i)) ||
          ($cbsVersion =~ /^internal$/i)) {
        # get component
        $component = GetComponentName ($thisOption->{'Name'});
        next if (($component eq 'Promontory') && ($promontorySupport == 0));
        next if (($component eq 'BIXBY') && ($bixbySupport == 0));
        # Ignore the setction with name (Obsolete)
        next if ($thisOption->{'Name'} =~ /\(Obsolete\)\s*$/i);
        $indentNum = $indentNumSaved;
        &parseCbsSection ($thisOption->{'ITEM'}, $cbsVersion, $thisOption, $rootSection, $component);
      }
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
  my $cbsVersion = shift;
  my $parentSection = shift;
  my $rootSection = shift;
  my $component = shift;
  my $firstOption = 'TRUE';
  my $parentSectionName = $parentSection->{'Name'};
  my $Visibility = $parentSection->{'Visibility'};

  # 0, #define AMD_PROCESSOR/GNB/FCH
#  if ($component eq 'CPU') {
#    print $vfrFile '  ' x $indentNum."#ifdef AMD_CBS_CPU_SUPPORT\n";
#  }
#  if ($component eq 'GNB') {
#    print $vfrFile '  ' x $indentNum."#ifdef AMD_CBS_GNB_SUPPORT\n";
#  }
#  if ($component eq 'FCH') {
#    print $vfrFile '  ' x $indentNum."#ifdef AMD_CBS_FCH_SUPPORT\n";
#  }

  if ($component eq 'Promontory') {
    if ($promontorySupport) {
      print $vfrFile '  ' x $indentNum."#ifdef PROMONTORY_SUPPORT\n";
    }
  }
  
  if ($component eq 'BIXBY') {
    if ($bixbySupport) {
      # print $vfrFile '  ' x $indentNum."#ifdef BIXBY_SUPPORT\n";
    }
  }

  # 1st, 'form', 'formid, 'title' and 'subtitle'
  print $vfrFile '  ' x $indentNum."//\n".'  ' x $indentNum."// form - $parentSectionName\n".'  ' x $indentNum."//\n";
  print $vfrFile '  ' x $indentNum."form\n\n";
  $indentNum++;
  my $lableToken = genLableToken ($parentSectionName);
  my $StrToken = genStrToken ($parentSectionName);
  $StrToken = $StrToken.'_SECTION';
  print $vfrFile '  ' x $indentNum."formid        = $lableToken,\n\n";
  print $vfrFile '  ' x $indentNum."title         = STRING_TOKEN \($StrToken\);\n\n";
  print $vfrFile '  ' x $indentNum."subtitle text = STRING_TOKEN \($StrToken\);\n";
  $StrToken = genStrToken ('BLANK');
  print $vfrFile '  ' x $indentNum."subtitle text = STRING_TOKEN \($StrToken\);\n\n";

  # 2nd, generate uni, header, vfr files
  foreach my $thisOption (@{$cbsDataBase}) {
    if (ref ($thisOption->{'Variable_name'}) ne 'HASH') {
      # add a blank line after all 'SECTION's
      if (($thisOption->{'Type'} =~ /^OPTION$/i) && ($firstOption eq 'TRUE')) {
        if ($thisOption != ${$cbsDataBase}[0]) {
          generateBlankLine ($vfrFile, $indentNum);
        }
        $firstOption = 'FALSE';
      }
      #Fix build issue on setup related file generation, replace "\n" with string "\n"
      $thisOption->{'Help_text'} =~ s/\n/\\n/g;

      &generateLableStr(\$lableStartID, \$lableIDOutput, $thisOption);
      &generateKeyStr(\$lableStartID, \$keyIDOutput, $thisOption);
      &generateUniFileStr(\$uniFileStr, $thisOption, \%uniExistHash);
      if ($inputVariableFile eq '') {
        # Generate to file directly
        &generateHFile($hFile, $thisOption);
      } else {
        # Collect the information for further process
        &addCbsVariable($thisOption);
      }
      &generateIdsFiles($component, $Visibility, $thisOption);

      &generateVfrFile($vfrFile, $thisOption, $indentNum, $rootSection, \%keyIDExistHash, \$lableStartID, \$keyIDOutput, $component);
      &generateSetDefaultValueFile ($setDefaultValueFile, $thisOption);
    }
  }

  # 5th, 'endform;'
  $indentNum--;
  print $vfrFile '  ' x $indentNum."endform;\n";

  # 6th #endif
#  if (($component eq 'CPU') || ($component eq 'GNB') || ($component eq 'FCH')) {
#    print $vfrFile '  ' x $indentNum."#endif\n\n\n";
#  }

  if (($component eq 'Promontory') && $promontorySupport) {
    print $vfrFile '  ' x $indentNum."#endif\n\n\n";
  }
  
  if (($component eq 'BIXBY') && $bixbySupport) {
    # print $vfrFile '  ' x $indentNum."#endif\n\n\n";
  }

  # 7th, parse sub 'SECTION's
  my $indentNumSaved = $indentNum + 1;
  foreach my $thisOption (@{$cbsDataBase}) {
    if ($thisOption->{'Type'} =~ /^SECTION$/i) {
      $indentNum = $indentNumSaved;
      &parseCbsSection ($thisOption->{'ITEM'}, $cbsVersion, $thisOption, $rootSection, $component);
    }
  }
}

#########################################################
#
# codebase special hook before auto generation
#
#########################################################
sub VfrHookBeforeGen {
  my $strRootSection = genStrToken($rootLable)."_SECTION";
  my $strRootSectionHelp = genStrToken($rootLable)."_SECTION_HELP";
  my $strBlank = genStrToken ('BLANK');
  my $VfrHook =  "#include <Guid\/HiiPlatformSetupFormset.h>
#include \"AmdCbsFormID.h\"
#include \<Guid\/AmdCbsConfig.h\>
#include \"AmdCbsVariable.h\"

formset
  guid      = FORMSET_ID_GUID_AMD_CBS,
  title     = STRING_TOKEN($strRootSection),
  help      = STRING_TOKEN($strRootSectionHelp),
  classguid = EFI_HII_PLATFORM_SETUP_FORMSET_GUID,

";
###
# common
###
print $setDefaultValueFile "#include \"AmdCbsVariable.h\"

VOID
CbsWriteDefalutValue (
  IN UINT8 *IfrData
  )
{
  CBS_CONFIG *Setup_Config;

  Setup_Config = (CBS_CONFIG *)IfrData;
  Setup_Config->Header.NewRecordOffset = OFFSET_OF (CBS_CONFIG, Reserved);
";
###
# common, CBS IDS NV
###
my $idsNvFileName = "IdsNvId".$Program.".h";
print $cbsIdsNvFile "#include \"AmdCbsVariable.h\"
#include \"$idsNvFileName\"\n";

if ($version =~ /^internal$/i) {
  my $idsIntNvFileName = "IdsNvIntId".$Program.".h";
  print $cbsIdsNvFile "#include \"$idsIntNvFileName\"\n";
}

print $cbsIdsNvFile "#include \"IdsNvTable.h\"

UINT32 GetIdsNvRecordsSize ();

#pragma pack(1)
typedef struct {
  IDS_NV_ID     Id;
  UINT16        Offset;
} IDS_NV_RECORD;
#pragma pack()

#ifndef OFFSET_OF
  #define OFFSET_OF(type, member) ((UINT8) &(((type*)0)->member))
#endif

";
print $cbsSetPcdCFile "#include <Base.h>
#include <Library/DebugLib.h>
#include \"AmdCbsVariable.h\"
#include <Library/PcdLib.h>

VOID
CbsSetAgesaPcds (
  IN       VOID *CbsVariable
  )
{
  CBS_CONFIG *Setup_Config;

  if (CbsVariable == NULL) {
    ASSERT (FALSE);
    return;
  }
  Setup_Config = (CBS_CONFIG *) CbsVariable;
";
my $cbsSetPcdInfSourceFile = "CbsSetAgesaPcdLib".$Program.".c";
my $cbsSetPcdInfFamDecFile;
if ($Program eq 'ZP') {
  $cbsSetPcdInfFamDecFile = "AgesaModulePkg/Fch/Taishan/FchTaishan.dec";
} elsif ($Program eq 'RV') {
  $cbsSetPcdInfFamDecFile = "AgesaModulePkg/Fch/Sandstone/FchSandstone.dec";
} elsif ($Program eq 'RN') {
  $cbsSetPcdInfFamDecFile = "AgesaModulePkg/Fch/Sandstone/FchSandstone.dec";
} elsif ($Program eq 'SSP') {
  $cbsSetPcdInfFamDecFile = "AgesaModulePkg/Fch/Huashan/FchHuashan.dec\n  AgesaModulePkg/Fch/Bixby/Bixby.dec";
}
print $cbsSetPcdInfFile
"
[Defines]
  INF_VERSION                    = 0x00010005
  BASE_NAME                      = CbsSetAgesaPcdLib
  FILE_GUID                      = CFBC986E-808D-42A7-B7B7-55D13A626802
  MODULE_TYPE                    = BASE
  VERSION_STRING                 = 1.0
  LIBRARY_CLASS                  = CbsSetAgesaPcdLib

[sources.common]
  $cbsSetPcdInfSourceFile

[Packages]
  MdePkg/MdePkg.dec
  MdeModulePkg/MdeModulePkg.dec
  AmdCbsPkg/AmdCbsPkg.dec
  AgesaPkg/AgesaPkg.dec
  AgesaModulePkg/AgesaCommonModulePkg.dec
  AgesaModulePkg/AgesaModuleCcxPkg.dec
  AgesaModulePkg/AgesaModuleDfPkg.dec
  AgesaModulePkg/AgesaModuleFchPkg.dec
  AgesaModulePkg/AgesaModuleMemPkg.dec
  AgesaModulePkg/AgesaModuleNbioPkg.dec
  AgesaModulePkg/AgesaModulePspPkg.dec
  $cbsSetPcdInfFamDecFile

[LibraryClasses]
  PcdLib
  DebugLib

[DEPEX]
  TRUE

[Pcd]
";

  # update VFR file
  printf $vfrFile $VfrHook;
  printf $vfrFile "  varstore CBS_CONFIG,                        // This is the data structure type
    varid = CBS_CONFIGURATION_VARSTORE_ID,    // Optional VarStore ID
    name  = AmdSetup,                         // Define referenced name in vfr
    guid  = CBS_SYSTEM_CONFIGURATION_GUID;    // GUID of this buffer storage\n";

}

#########################################################
#
# codebase special hook after auto generation
#
#########################################################
sub VfrHookAfterGen {
$gCbsIdsNvU8  = $gCbsIdsNvU8."\n  //End\n  {0xFFFF, 0}};\n\n";
$gCbsIdsNvU16 = $gCbsIdsNvU16."\n  //End\n  {0xFFFF, 0}};\n\n";
$gCbsIdsNvU32 = $gCbsIdsNvU32."\n  //End\n  {0xFFFF, 0}};\n\n";
$gCbsIdsNvU64 = $gCbsIdsNvU64."\n  //End\n  {0xFFFF, 0}};\n\n";
printf $cbsIdsNvFile $gCbsIdsNvU8;
printf $cbsIdsNvFile $gCbsIdsNvU16;
printf $cbsIdsNvFile $gCbsIdsNvU32;
printf $cbsIdsNvFile $gCbsIdsNvU64;

#Add size of the end flag
$idsNvSize += $IDS_NV_RECORD_U64_SIZE;
print $cbsIdsNvFile "
BOOLEAN
PrepareIdsNvTable (
  IN       VOID *CbsVariable,
  IN OUT   VOID *IdsNvTable,
  IN OUT   UINT32 *IdsNvTableSize
  )
{
  IDS_NV_TABLE_HEADER *IdsNvTblHdr;
  UINT8               *IdsNvRecord;
  UINTN               Setup_Config;
  IDS_NV_RECORD       *IdsNv;

  //Check if IdsNvTableSize size satisfied
  if ((*IdsNvTableSize) <  sizeof (IDS_NV_TABLE_HEADER) + GetIdsNvRecordsSize () ) {
    *IdsNvTableSize = sizeof (IDS_NV_TABLE_HEADER) + GetIdsNvRecordsSize ();
    return FALSE;
  }

  Setup_Config = (UINTN) CbsVariable;

  //Fill the IDS_NV_TABLE_HEADER
  IdsNvTblHdr = IdsNvTable;
  IdsNvTblHdr->Signature = IDS_NV_TABLE_SIGNATURE; //\$INV
  IdsNvTblHdr->Revision = IDS_NV_TABLE_REV_1; //0x00000001ul

  //Fill the IDS_NV_RECORD
  IdsNvRecord = &(((IDS_NV_TABLE *)IdsNvTable)->NvRecords);

  IdsNv = mIdsNv8;
  while (IdsNv->Id != 0xFFFF) {
    ((IDS_NV_RECORD_U8 *) IdsNvRecord)->Id = IdsNv->Id;
    ((IDS_NV_RECORD_U8 *) IdsNvRecord)->Attrib.size = IDS_NV_ATTRIB_SIZE_BYTE;
    ((IDS_NV_RECORD_U8 *) IdsNvRecord)->Value = *(UINT8*)(Setup_Config+IdsNv->Offset);
    IdsNvRecord += sizeof (IDS_NV_RECORD_U8);
    IdsNv++;
  }

  IdsNv = mIdsNv16;
  while (IdsNv->Id != 0xFFFF) {
    ((IDS_NV_RECORD_U16 *) IdsNvRecord)->Id = IdsNv->Id;
    ((IDS_NV_RECORD_U16 *) IdsNvRecord)->Attrib.size = IDS_NV_ATTRIB_SIZE_WORD;
    ((IDS_NV_RECORD_U16 *) IdsNvRecord)->Value = *(UINT16*)(Setup_Config+IdsNv->Offset);
    IdsNvRecord += sizeof (IDS_NV_RECORD_U16);
    IdsNv++;
  }

  IdsNv = mIdsNv32;
  while (IdsNv->Id != 0xFFFF) {
    ((IDS_NV_RECORD_U32 *) IdsNvRecord)->Id = IdsNv->Id;
    ((IDS_NV_RECORD_U32 *) IdsNvRecord)->Attrib.size = IDS_NV_ATTRIB_SIZE_DWORD;
    ((IDS_NV_RECORD_U32 *) IdsNvRecord)->Value = *(UINT32*)(Setup_Config+IdsNv->Offset);
    IdsNvRecord += sizeof (IDS_NV_RECORD_U32);
    IdsNv++;
  }

  IdsNv = mIdsNv64;
  while (IdsNv->Id != 0xFFFF) {
    ((IDS_NV_RECORD_U64 *) IdsNvRecord)->Id = IdsNv->Id;
    ((IDS_NV_RECORD_U64 *) IdsNvRecord)->Attrib.size = IDS_NV_ATTRIB_SIZE_QWORD;
    ((IDS_NV_RECORD_U64 *) IdsNvRecord)->Value = *(UINT64*)(Setup_Config+IdsNv->Offset);
    IdsNvRecord += sizeof (IDS_NV_RECORD_U64);
    IdsNv++;
  }

  //Fill the end of IDS_NV_RECORD
  ((IDS_NV_RECORD_CMN *) IdsNvRecord)->Id = IDS_NV_ID_END;

  return TRUE;
}

#define IDS_NV_RECORDS_SIZE ($idsNvSize)

UINT32
GetIdsNvRecordsSize (
  )
{
  return IDS_NV_RECORDS_SIZE;
}";
print $cbsSetPcdCFile "\n}\n";

die if ($idsIdNum > $idsIdNumEnd);

printf $vfrFile "endformset;";
}

#########################################################
#
# Generate copyright
#
#########################################################
sub generateFileHeader
{
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
  my $infWarningLine = "#This file is auto generated, don't edit it manually\n\n";
  print $hFile $copyright;
  print $lableFile $copyright;
  print $vfrFile $copyright;
  print $setDefaultValueFile $copyright;
  print $idsNvDefFile $copyright.$warningLine;
  print $idsNvIntDefFile $copyright.$warningLine;
  print $idsSampleFile $copyright.$warningLine;
  print $cbsIdsNvFile $copyright.$warningLine;
  print $cbsSetPcdCFile $copyright.$warningLine;
  print $cbsSetPcdInfFile $infCopyright, $infWarningLine;
  print $apcbAutoGenFile $copyright.$warningLine;
  print $apcbSetDataFile $copyright.$warningLine;
  $copyright =~ s/(\n).+?/$1\/\//g;
  $copyright =~ s/\/\*/\/\/\*/;
  &attachUniStr (\$uniFileStr ,$copyright);
}

#########################################################
#
# support combo CBS
#
#########################################################
sub comboCbsHook
{
  my $cbsDataBase = shift;

  if ($bcomboFlag =~ /enable/i) {
    my $combo = {};
    $combo->{"Type"} = 'OPTION';
    $combo->{"Input_type"} = 'Customed';
    $combo->{"Name"} = 'Combo CBS';
    $combo->{"Variable_name"} = 'CbsComboFlag';
    $combo->{"BIOS_Default"} = '254';
    $combo->{"Display_condition"} = "CbsComboFlag = 255";
    $combo->{"Active_condition"} = {};
    $combo->{"Nv_type"} = 'Byte';
    #$combo->{"Key_function"} = {};    // used for callback function
    $combo->{"Help_text"} = {};
    $combo->{"OPTION_ITEM"}->[0]->{'Nv_storage'} = '0x00-0xff';
    $combo->{"OPTION_ITEM"}->[0]->{'Name'} = 'User Input';
    push (@{$cbsDataBase}, $combo);
  }
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
# Get APCB VALUE Macro String from CBS XML "DataType"
#
#########################################################
sub GetApcbValMacro
{
  my $cbsNvType = shift;

  if ($cbsNvType =~ /^\s*Byte\s*$/i) {
    return "BSU08";
  } elsif ($cbsNvType =~ /^\s*Word\s*$/i) {
    return "BSU16";
  }  elsif ($cbsNvType =~ /^\s*Dword\s*$/i) {
    return "BSU32";
  }  elsif ($cbsNvType =~ /^\s*Qword\s*$/i) {
    return "BSU64";
  }
}
#########################################################
#
# Init APCB Database from input acpbfile
#
#########################################################
sub initApcbDbV2
{
  my $currentSection = "NULL";
  my $token;
  #check if user specified the input acpbfile via command line parameter
  #die if not
  if ($inputApcbFile eq undef) {
    print "[warning] APCB Attributes is identified in the XML, but \"--apcbfile\" parameter is not specified in the CMD line\n" ;
    $gWarningStopFlag = 1;
    return;
  }

  open APCBINPUT, "<".$inputApcbFile or die "Can't open the $inputApcbFile";

  while (<APCBINPUT>) {
    if (/^\s*#define\s+APCB_TOKEN_CBS_CMN_BEGIN/) {
      $currentSection = "CMN";
    } elsif (/^\s*#define\s+APCB_TOKEN_CBS_CMN_END/) {
      $currentSection = "NULL";
    } elsif (/^\s*#define\s+APCB_TOKEN_CBS_DBG_BEGIN/) {
      $currentSection = "DBG";
    } elsif (/^\s*#define\s+APCB_TOKEN_CBS_DBG_END/) {
      $currentSection = "NULL";
    } elsif (($currentSection ne "NULL") && (/^\s*#define\s+APCB_TOKEN_CBS_/)){
      $_ =~ /^\s*#define\s+(.+)?\s+.+$/;
      $token = $1;
      push @{$gApcbDb->{$currentSection}}, $token;
    }
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
# Evaluate the display condition for a option
# Return: (AutoExist, AutoValue)
#
#########################################################
sub EvaluateDisplayConditionDefault
{
  my $thisOption = shift;
  my @a1;
  my @a2;
  my $andResult = 1;
  my $orResult = 0;
  my $result;
  # Check if Display condition exist
  if ((ref ($thisOption->{'Display_condition'}) ne 'HASH') && ($thisOption->{'Display_condition'} =~ /\w+/)) {
    # A,B | C,D,E =>
    # (A && B) || (C && D && E)
    DbgPrint ("\n==Display_condition: %s==\n", $thisOption->{'Display_condition'});
    my @a1 = split (/\|/, $thisOption->{'Display_condition'});
    # Now @a contains contions (A && B) , (C && D && E)
    # Evaluate until whole array been traverse, or one contion return TRUE
    foreach my $b1 (@a1) {
      $b1 =~ s/(^\s+|\s+$)//g;
      DbgPrint ($b1."|| \n");
      # Exclude CbsComboFlag
      # $b1 =~ s/CbsComboFlag=.+[,]?//gi;
      my @a2 = split (/\,/, $b1);
      foreach my $b2 (@a2) {
        #Evaluate each condition
        $andResult = 1;
        if ($b2 =~ /^\s*(.+)\s*=\s*(.+)?\s*$/) {
          my $variable = $1;
          my $option = $2;
          $variable =~ s/(^\s+|\s+$)//g;
          $option =~ s/(^\s+|\s+$)//g;
          $result = 0;
          DbgPrint ("\tV[%s]:O[%s]\n", $variable, $option);
          # Search in gVarChoiceDict
          # 'Display_condition' => 'CbsCpuPstCustomP0=Custom',
          if (exists $gVarChoiceDict->{$variable}) {
            # If it is user input type
            if ((scalar keys %{$gVarChoiceDict->{$variable}->{"Choices"}} eq 1) &&
                (exists $gVarChoiceDict->{$variable}->{"Choices"}->{'User Input'})) {
              # It is user input type
              if ($option eq $gVarChoiceDict->{$variable}->{"BIOS_Default"}) {
                $result = 1;
                DbgPrint (" TRUE &&\n");
              } else {
                DbgPrint (" FALSE &&\n");
              }
            } else {
              if (exists $gVarChoiceDict->{$variable}->{"Choices"}->{$option}) {
                # Check if contion matches
                DbgPrint ("OpValue %x <> Dft:%x", $gVarChoiceDict->{$variable}->{"Choices"}->{$option}, $gVarChoiceDict->{$variable}->{"BIOS_Default"});
                if ($gVarChoiceDict->{$variable}->{"Choices"}->{$option} eq $gVarChoiceDict->{$variable}->{"BIOS_Default"}) {
                  $result = 1;
                  DbgPrint (" TRUE &&\n");
                } else {
                  DbgPrint (" FALSE &&\n");
                }
              } else {
                DbgPrint ("[Warning] Display_condition %s choice (%s) not found\n", $thisOption->{'Display_condition'}, $option);
                $gWarningStopFlag = 1;
              }
            }
          } else {
            DbgPrint ("[Warning] Display_condition %s variable (%s) not found\n", $thisOption->{'Display_condition'}, $variable);
            $gWarningStopFlag = 1;
          }
        } else {
          DbgPrint ("[Warning] Display_condition Unrecognized format  %s\n", $thisOption->{'Display_condition'});
          $gWarningStopFlag = 1;
        }
        $andResult &= $result;
        if ($andResult == 0) {
          last;
        }
      }
      $orResult |= $andResult;
      if ($orResult == 1) {
        DbgPrint ("Final: >>>>> TRUE <<<<<<<\n");
        return 1;
      }
    }
    return 0;
    DbgPrint ("Final: >>>>> FALSE <<<<<<<\n");
  } else {
    return 1;
  }
}

sub GetDisplayConditionCode {
  my $thisOption = shift;
  my @a1;
  my @a2;
  my $i;
  my $j;
  my $returnCode;

  # Check if Display condition exist
  if ((ref ($thisOption->{'Display_condition'}) ne 'HASH') && ($thisOption->{'Display_condition'} =~ /\w+/)) {
    # A,B | C,D,E =>
    # (A && B) || (C && D && E)
    # DbgPrint ("\n==Display_condition: %s==\n", $thisOption->{'Display_condition'});
    my @a1 = split (/\|/, $thisOption->{'Display_condition'});
    # Now @a contains contions (A && B) , (C && D && E)
    # Evaluate until whole array been traverse, or one contion return TRUE
    foreach my $b1 (@a1) {
      $b1 =~ s/(^\s+|\s+$)//g;
      # DbgPrint $b1, "|| \n";
      # Exclude CbsComboFlag
      # $b1 =~ s/CbsComboFlag=.+[,]?//gi;
      my @a2 = split (/\,/, $b1);
      if (scalar @a1 > 1) {
        $returnCode .= "(";
      }
      $i = 0;
      foreach my $b2 (@a2) {
        #Evaluate each condition
        if ($b2 =~ /^\s*(.+)\s*=\s*(.+)?\s*$/) {
          my $variable = $1;
          my $option = $2;
          $variable =~ s/(^\s+|\s+$)//g;
          $option =~ s/(^\s+|\s+$)//g;
          # Search in gVarChoiceDict
          # 'Display_condition' => 'CbsCpuPstCustomP0=Custom',
          if (exists $gVarChoiceDict->{$variable}) {
            # If it is user input type
            if ((scalar keys %{$gVarChoiceDict->{$variable}->{"Choices"}} eq 1) &&
                (exists $gVarChoiceDict->{$variable}->{"Choices"}->{'User Input'})) {
              # It is user input type
              $returnCode .= sprintf "(Setup_Config->%s == 0x%x)", $variable, $option;
            } else {
              if (exists $gVarChoiceDict->{$variable}->{"Choices"}->{$option}) {
                # Check if contion matches
				my $num = $gVarChoiceDict->{$variable}->{"Choices"}->{$option};
				if($num =~ /^0x/){
					$num = hex($num);
				}
                $returnCode .= sprintf "(Setup_Config->%s == 0x%x)", $variable, $num;
              } else {
                printf ("[Error] Display_condition %s choice (%s) not found\n", $thisOption->{'Display_condition'}, $option);
                exit (2);
              }
            }
          } else {
            printf ("[Error] Display_condition %s variable (%s) not found\n", $thisOption->{'Display_condition'}, $variable);
            exit (2);
          }
        } else {
          printf ("[Error] Display_condition Unrecognized format  %s\n", $thisOption->{'Display_condition'});
          exit (2);
        }
        $i++;
        # Not last one
        if ($i != scalar @a2) {
          $returnCode .= " && ";
        }
      }
      $j++;
      if (scalar @a1 > 1) {
        $returnCode .= ")";
        # Not last one
        if ($j != scalar @a1) {
          $returnCode .= " ||";
        }
      }
    }
    return $returnCode;
  } else {
    return undef;
  }

}
sub FillApcbV2SetStrs
{
  my $thisOption = shift;
  my $apcbTokenStr = shift;
  my $AttribSetStr = shift;
  my $ValueSetStr = shift;

  (my $autoExist, my $autoValue) = GetAutoValue ($thisOption);
  my $VarTypeStr = GetVarTypeStr ($thisOption->{"Nv_type"});
  my $VarName = $thisOption->{'Variable_name'};
  $$AttribSetStr .= "\n  //".$thisOption->{"Name"}."\n";
  $$ValueSetStr .= "\n  //".$thisOption->{"Name"}."\n";

  if ($autoExist) {
    #Attrib
    $$AttribSetStr .= sprintf
"  if (Setup_Config->%s != %s) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = %s;
      ApcbParaAttrib->Size = (sizeof (%s) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }
", $VarName, $autoValue, $apcbTokenStr, $VarTypeStr;

    #Value
    $$ValueSetStr .= sprintf
"  if (Setup_Config->%s != %s) {
    if (ApcbParaValue != NULL) {
      * ((%s *) ApcbParaValue) = Setup_Config->%s;
      ApcbParaValue += sizeof (%s);
    }
    _Size += sizeof (%s);
  }
", $VarName, $autoValue, $VarTypeStr, $VarName,  $VarTypeStr, $VarTypeStr;
  } else {
    #Attrib
    $$AttribSetStr .= sprintf
"  if (ApcbParaAttrib != NULL) {
    ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
    ApcbParaAttrib->Token = %s;
    ApcbParaAttrib->Size = (sizeof (%s) -1);
    ApcbParaAttrib++;
  }
  _Size += sizeof (APCB_PARAM_ATTRIBUTE);
", $apcbTokenStr, $VarTypeStr;

    #Value
    $$ValueSetStr .= sprintf
"  if (ApcbParaValue != NULL) {
    * ((%s *) ApcbParaValue) = Setup_Config->%s;
    ApcbParaValue += sizeof (%s);
  }
  _Size += sizeof (%s);
", $VarTypeStr, $VarName,  $VarTypeStr, $VarTypeStr;
  }
}

sub IsApcbBoolOption {
  my $option = shift;
  my %BoolOptionPattern = (
    uc join ("-", sort ("Enable", "Disable", "Auto")) => 1,
    uc join ("-", sort ("Enabled", "Disable", "Auto")) => 1,
    uc join ("-", sort ("Enable", "Disabled", "Auto")) => 1,
    uc join ("-", sort ("Enabled", "Disabled", "Auto")) => 1,
    uc join ("-", sort ("True", "False", "Auto")) => 1,
    uc join ("-", sort ("Enable", "Auto")) => 1,
    uc join ("-", sort ("Enabled", "Auto")) => 1,
    uc join ("-", sort ("Disable", "Auto")) => 1,
    uc join ("-", sort ("Disabled", "Auto")) => 1,
    uc join ("-", sort ("Enable", "Disable")) => 1,
    uc join ("-", sort ("Enabled", "Disabled")) => 1,
    uc join ("-", sort ("Enabled", "Disable")) => 1,
    uc join ("-", sort ("Enable", "Disabled")) => 1,
  );
  # print Dumper %BoolOptionPattern;
  # print "====\n";
  if ($option->{'Input_type'} =~ /^Fixed$/i) {
    # Should only have 3 elements
    if (scalar @{$option->{'OPTION_ITEM'}} <= 3) {
      # Compose the options arrary, used to check again the pattern
      my @a;
      foreach my $choice (@{$option->{'OPTION_ITEM'}}) {
        push @a, $choice->{"Name"};
      }
      # print uc join ("-", sort @a);
      if (exists $BoolOptionPattern{uc join ("-", sort @a)}) {
        # Pattern matchs
        # Now check if Non-Auto option is range of (0,1)
        #Loop the choice to search the AUTO choice
        foreach my $choice (@{$option->{'OPTION_ITEM'}}) {
          if ($choice->{"Name"} !~ /^Auto$/i) {
            if ($choice->{"Nv_storage"} > 1)  {
              # printf ("[Warning] <%s-%s-0x%x> Non Boolean value found for the APCB BOOL type\n", $option->{"Name"}, $choice->{"Name"}, $choice->{"Nv_storage"});
              # $gWarningStopFlag = 1;
              return 0;
            }
          }
        }
        return 1;
      }
    }
  }
  return 0;
}
sub getChoiceName
{
  my $thisOption = shift;
  my $choiceVal = shift;
  my $choices=$gVarChoiceDict->{$thisOption->{'Variable_name'}}->{"Choices"};

  if (exists $gVarChoiceDict->{$thisOption->{'Variable_name'}}) {
    foreach my $choice (keys %{$choices}) {
      if ($choices->{$choice} eq $choiceVal) {
        return $choice;
      }
    }
  }
  return $choiceVal;
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
  my $_idsNvDefFile;

  if ($Visibility =~ /^External$/i) {
    $_idsNvDefFile = $idsNvDefFile;
  } else {
    $_idsNvDefFile = $idsNvIntDefFile;
  }
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
    my $apcbTokenStr = '';
    #check if PCD filed has been set
    if (ref ($thisOption->{'PCD'}) ne 'HASH') {
      $pcdUsed = 1;
      #Use Overriden format
      if ($thisOption->{'PCD'} =~ /^\s*(.+)?\s*\((.+)\)$/) {
        $pcdFullToken = $1;
        #set PCD func name according to CBS Nv_type
        if ($2 =~ /BOOL/i) {
          $pcdGetFunc = "PcdGetBool";
          $pcdSetFunc = "PcdSetBool";
        } elsif ($2 =~ /UINT8/i) {
          $pcdGetFunc = "PcdGet8";
          $pcdSetFunc = "PcdSet8";
        } elsif ($2 =~ /UINT16/i) {
          $pcdGetFunc = "PcdGet16";
          $pcdSetFunc = "PcdSet16";
        }  elsif ($2 =~ /UINT32/i) {
          $pcdGetFunc = "PcdGet32";
          $pcdSetFunc = "PcdSet32";
        }  elsif ($2 =~ /UINT64/i) {
          $pcdGetFunc = "PcdGet64";
          $pcdSetFunc = "PcdSet64";
        } else {
          print ("Unsupported PCD Data Overriden type found @ $pcdToken $2");
          exit (2);
        }
      } else {
        $pcdFullToken = $thisOption->{'PCD'};
        #set PCD func name according to CBS Nv_type
        if ($thisOption->{"Nv_type"} =~ /^\s*Byte\s*$/i) {
          $pcdGetFunc = "PcdGet8";
          $pcdSetFunc = "PcdSet8";
        } elsif ($thisOption->{"Nv_type"} =~ /^\s*Word\s*$/i) {
          $pcdGetFunc = "PcdGet16";
          $pcdSetFunc = "PcdSet16";
        }  elsif ($thisOption->{"Nv_type"} =~ /^\s*Dword\s*$/i) {
          $pcdGetFunc = "PcdGet32";
          $pcdSetFunc = "PcdSet32";
        }  elsif ($thisOption->{"Nv_type"} =~ /^\s*Qword\s*$/i) {
          $pcdGetFunc = "PcdGet64";
          $pcdSetFunc = "PcdSet64";
        }
      }
      #Check the format of pcdFullToken, and get the PcdTokenName
      if ($pcdFullToken =~ /^\s*(.+)?\.(.+)\s*$/) {
        $pcdToken = $2;
      } else {
        print "PCD Token format error @ \"$pcdFullToken\", please use \"PkgTokenSpaceGuid.PcdName\" to declare a PCDtoken\n\n";
        exit (2);
      }
    }

    $idsIdStr = $thisOption->{'Variable_name'};
    $optName = $thisOption->{'Name'};
    $optHelp = $thisOption->{"Help_text"};
    #Trim space at end of line to avoid style issue
    $optName =~ s/\s*$//;
    $optHelp =~ s/\s*$//;
    #Generate IDS NV ID String by convert CBS variable Name
    $baseName = &convertCbsVarNametoBaseVarName ($idsIdStr);
    $idsNvIdStr = "IDSNVID_".$baseName;


    #>>print the lines of Option definition to IdsNvDef.h
    my $idsOptStr = "IDSOPT_" . $baseName;
    printf $_idsNvDefFile "///%s\n", $optName;
    if (ref ($thisOption->{"Help_text"}) ne 'HASH') {
      printf $_idsNvDefFile "///%s\n", $optHelp;
    }

    if ($thisOption->{'Input_type'} =~ /^Fixed$/i) {
      #if option type is option, generate the lins as below
      # ///DRAM prefetches triggered from CPU requests
      # ///Enable or disable DRAM prefetches Prefetch triggered by CPU requests.
      # typedef enum {
      #   IDSOPT_CMN_PREFETCH_PREF_CPU_DIS_0 = 0,///<0
      #   IDSOPT_CMN_PREFETCH_PREF_CPU_DIS_1 = 1,///<1
      #   IDSOPT_CMN_PREFETCH_PREF_CPU_DIS_AUTO = 3,///<Auto
      # } IDSOPT_CMN_PREFETCH_PREF_CPU_DIS;

     #if option type is option, generate the lins as below for sample file
      # //DRAM prefetches triggered from CPU requests
      # IDS_NV_READ_SKIP (IDSNVID_CMN_CPU_GEN_WA05, &IdsNvValue) {
      #   switch (IdsNvValue) {
      #   case IDSOPT_CMN_CPU_GEN_WA05_1:
      #     break;
      #   case IDSOPT_CMN_CPU_GEN_WA05_0:
      #     break;
      #   case IDSOPT_CMN_CPU_GEN_WA05_AUTO:
      #     break;
      #   default:
      #     ASSERT (FALSE);
      #     break;
      #   }
      # }
      # //DRAM prefetches triggered from CPU requests
      # PcdGet (PcdToken) {
      #   switch (IdsNvValue) {
      #   case IDSOPT_CMN_CPU_GEN_WA05_1:
      #     break;
      #   case IDSOPT_CMN_CPU_GEN_WA05_0:
      #     break;
      #   case IDSOPT_CMN_CPU_GEN_WA05_AUTO:
      #     break;
      #   default:
      #     ASSERT (FALSE);
      #     break;
      #   }
      # }
      print $_idsNvDefFile "typedef enum {\n";
      printf $idsSampleFile "//%s\n", $thisOption->{'Name'};

      printf $idsSampleFile "IDS_NV_READ_SKIP (%s, &IdsNvValue) {\n  switch (IdsNvValue) {\n", $idsNvIdStr;
      if ($pcdUsed) {
        printf $idsSampleFile "  switch (%s (%s)) {\n", $pcdGetFunc, $pcdToken;
      }
      foreach my $choice (@{$thisOption->{'OPTION_ITEM'}}) {
        my $idsOptChoiceStr = $idsOptStr."_".uc $choice->{"Name"};
        #Delete the word can't be used in C language
        $idsOptChoiceStr =~ s/\W//g;
        printf $_idsNvDefFile "  %s = %s,///<%s\n", $idsOptChoiceStr, $choice->{"Nv_storage"}, $choice->{"Name"};
        printf $idsSampleFile "  case %s:\n    break;\n", $idsOptChoiceStr;
      }
      printf $_idsNvDefFile "} %s;\n\n", $idsOptStr;
      print $idsSampleFile
"  default:
    ASSERT (FALSE);
    break;
  }
}\n
";
    } elsif ($thisOption->{'Input_type'} =~ /^Customed$/i) {
      #if option type is numberic, generate the lins as below
      # ///Exception Vector
      # ///Specifies an exception vector
      # #define IDSOPT_DBG_CPU_EXCP_VEC_MIN 0 ///< Min of Exception Vector
      # #define IDSOPT_DBG_CPU_EXCP_VEC_MAX 0xff ///< Max of Exception Vector
     #if option type is numberic, generate the lins as below for sample file
      # //DRAM prefetches triggered from CPU requests
      # IDS_NV_READ_SKIP (IDSNVID_CMN_CPU_GEN_WA05, &IdsNvValue) {
      #   ASSERT (IdsNvValue <= MAX);
      #   ASSERT (IdsNvValue >= MIN);
      # }
      $thisOption->{'OPTION_ITEM'}->[0]->{'Nv_storage'} =~ /(\w+)-(\w+)/;
      my $optMinValStr = $1;
      my $optMaxValStr = $2;
      printf  $_idsNvDefFile "#define %s_MIN %s ///< Min of %s\n", $idsOptStr, $optMinValStr, $optName;
      printf  $_idsNvDefFile "#define %s_MAX %s ///< Max of %s\n\n", $idsOptStr, $optMaxValStr, $optName;
      printf $idsSampleFile "IDS_NV_READ_SKIP (%s, &IdsNvValue) {\n", $idsNvIdStr;
      printf $idsSampleFile "  ASSERT (IdsNvValue <= %s_MAX);\n  ASSERT (IdsNvValue >= %s_MIN);\n}\n\n", $idsOptStr, $idsOptStr;
    }
  #<<
  #>>print the lines to $cbsIdsNv

    if ($thisOption->{"Nv_type"} =~ /^Byte$/i) {
    # //RedirectForReturnDis
    # {IDSNVID_CMN_CPU_GEN_W_A05, OFFSET_OF(CBS_CONFIG,CbsCmnCpuGenWA05)},
    #it is byte type NV generate codes like aboved
      $gCbsIdsNvU8   = $gCbsIdsNvU8.sprintf("\n  //%s\n  {%s, OFFSET_OF(CBS_CONFIG,%s)},", $thisOption->{'Name'}, $idsNvIdStr, $thisOption->{'Variable_name'});
      $idsNvSize += $IDS_NV_RECORD_U8_SIZE;
    } elsif ($thisOption->{"Nv_type"} =~ /^Word$/i) {
      #it is word type NV generate codes like aboved
      $gCbsIdsNvU16 = $gCbsIdsNvU16.sprintf("\n  //%s\n  {%s, OFFSET_OF(CBS_CONFIG,%s)},", $thisOption->{'Name'}, $idsNvIdStr, $thisOption->{'Variable_name'});
      $idsNvSize += $IDS_NV_RECORD_U16_SIZE;
    } elsif ($thisOption->{"Nv_type"} =~ /^Dword$/i) {
      #it is word type NV generate codes like aboved
      $gCbsIdsNvU32 = $gCbsIdsNvU32.sprintf("\n  //%s\n  {%s, OFFSET_OF(CBS_CONFIG,%s)},", $thisOption->{'Name'}, $idsNvIdStr, $thisOption->{'Variable_name'});
      $idsNvSize += $IDS_NV_RECORD_U32_SIZE;
    } elsif ($thisOption->{"Nv_type"} =~ /^Qword$/i) {
      #it is word type NV generate codes like aboved
      $gCbsIdsNvU64 = $gCbsIdsNvU64.sprintf("\n  //%s\n  {%s, OFFSET_OF(CBS_CONFIG,%s)},", $thisOption->{'Name'}, $idsNvIdStr, $thisOption->{'Variable_name'});
      $idsNvSize += $IDS_NV_RECORD_U64_SIZE;
    }
    #>>print the lines to $cbsSetPcd
    if ($pcdUsed) {
      printf $cbsSetPcdInfFile "  %s\n",$pcdFullToken;
      my $DisplayConditionCode;
      my $indent = 1;
      $DisplayConditionCode = &GetDisplayConditionCode ($thisOption);
      if (defined $DisplayConditionCode) {
       printf $cbsSetPcdCFile "  //Check Display Condition %s\n  if (%s) {\n", $thisOption->{"Display_condition"},$DisplayConditionCode;
       $indent++;
      }
      #check Auto option if exist
      (my $autoExist, my $autoValue) = GetAutoValue ($thisOption);
      if ($autoExist) {
        # if (Setup_Config->CbsDbgCpuGenDowncoreCtrl != 0x0F) {}
        printf $cbsSetPcdCFile '  'x$indent."if (Setup_Config->%s != %s) {\n",  $thisOption->{'Variable_name'}, $autoValue;
        printf $cbsSetPcdCFile '  'x$indent."  %s (%s, Setup_Config->%s);\n", $pcdSetFunc, $pcdToken,  $thisOption->{'Variable_name'};
        printf $cbsSetPcdCFile '  'x$indent."}\n";
      } else {
        printf $cbsSetPcdCFile '  'x$indent."%s (%s, Setup_Config->%s);\n", $pcdSetFunc, $pcdToken,  $thisOption->{'Variable_name'};
      }
      if (defined $DisplayConditionCode) {
        printf $cbsSetPcdCFile "  }\n\n";
      } else {
        printf $cbsSetPcdCFile "\n";
      }
    }
    #Generate APCB related
    if ($gApcbVer == 2) {
      if ($thisOption->{'APCB'}) {
        if ($thisOption->{'Apcb_structure'}) {
          # printf ("[Warning] %s Apcb_structure attribute ignored for APCB V2\n", $thisOption->{"Name"});
              # $gWarningStopFlag = 1;
        }
        #init ApcbDb, if not initialied, and create APCB CBS ID
        if (scalar keys %{$gApcbDb} == 0) {
          initApcbDbV2 ();
        }
        $apcbTokenStr = "APCB_TOKEN_CBS_". uc &convertCbsVarNametoBaseVarName ($thisOption->{'Variable_name'});
        #Generate Token
        if ($Visibility =~ /^External$/i) {
          #check the existence, insert to the tail if not
          if (!($apcbTokenStr ~~ @{$gApcbDb->{"CMN"}})) {
            push @{$gApcbDb->{"CMN"}}, $apcbTokenStr;
          }
        } else {
          #check the existence, insert to the tail if not
          if (!($apcbTokenStr ~~ @{$gApcbDb->{"DBG"}})) {
            push @{$gApcbDb->{"DBG"}}, $apcbTokenStr;
          }
        }
        #Generate build time Attrib & Value
        #check if default value is Auto
        (my $autoExist, my $autoValue) = GetAutoValue ($thisOption);
        if ((!$autoExist) || (($autoExist) && ($thisOption->{'BIOS_Default'} ne $autoValue))) {
          my $apcbTokenValueStr = $apcbTokenStr."_VALUE";
          $gApcbV2TokenValueStr .= sprintf ("#define %s %s  //Value for %s\n",$apcbTokenValueStr, $thisOption->{'BIOS_Default'}, $thisOption->{'Name'});
          if ($Visibility =~ /^External$/i) {
            $gApcbV2ExtAttribStr .= sprintf ("{APCB_TIME_POINT_ANY, %s, sizeof (%s) - 1, 0}, \\\n", $apcbTokenStr, &GetVarTypeStr ($thisOption->{"Nv_type"}));
            $gApcbV2ExtValueStr .= sprintf ("  %s (%s), \\\n", &GetApcbValMacro ($thisOption->{"Nv_type"}), $apcbTokenValueStr);
          } else {
            $gApcbV2IntAttribStr .= sprintf ("{APCB_TIME_POINT_ANY, %s, sizeof (%s) - 1, 0}, \\\n", $apcbTokenStr, GetVarTypeStr ($thisOption->{"Nv_type"}));
            $gApcbV2IntValueStr .= sprintf ("  %s (%s), \\\n", &GetApcbValMacro ($thisOption->{"Nv_type"}), $apcbTokenValueStr);
          }
        }
        #Generate Post time Attrib & Value
        if ($Visibility =~ /^External$/i) {
          FillApcbV2SetStrs ($thisOption, $apcbTokenStr, \$gApcbExtAttribSetStr, \$gApcbExtValueSetStr);
        } else {
          FillApcbV2SetStrs ($thisOption, $apcbTokenStr, \$gApcbIntAttribSetStr, \$gApcbIntValueSetStr);
        }
      }
    } elsif ($gApcbVer == 3) {
      my $apcbSetTokenRoutine;
      my $OverrideDataType;
      if ($thisOption->{'Apcb_structure'}) {
        if ($thisOption->{'APCB'}) {
          # printf ("[Warning] <%s> APCB ATTR ignored for APCB V3\n", $thisOption->{"Name"});
              # $gWarningStopFlag = 1;
        }
        if (ref ($thisOption->{'Apcb_structure'}) ne 'HASH') {
          # printf "=>%s<=\n", $thisOption->{'Apcb_structure'};
          # Check if use Overriden format in APCB Structure, "APCB_STR(BOOL)"
          if ($thisOption->{'Apcb_structure'} =~ /^\s*(.+)?\s*\((.+)\)$/) {
            $apcbTokenStr = $1;
            $OverrideDataType = uc $2;
            if ($OverrideDataType !~ /(BOOL|BYTE|WORD|DWORD)/) {
              printf ("[Warning] Invalid APCB override data type %s,Ignored, only support BOOL|BYTE|WORD|DWORD \n", $OverrideDataType);
              $OverrideDataType = undef;
            }
          } else {
            $apcbTokenStr = $thisOption->{'Apcb_structure'};
          }

          my $NvDataType;
          if ($OverrideDataType eq undef) {
            $NvDataType = $thisOption->{'Nv_type'};
          } else {
            $NvDataType = $OverrideDataType;
          }
          # Generate the build time value if the option Display is true, and itself value is non-auto
          my $displayCondition = &EvaluateDisplayConditionDefault ($thisOption);
          (my $autoExist, my $autoValue) = GetAutoValue ($thisOption);
          my $genApcbAutoGenCondition = ((!$autoExist) || (($autoExist) && ($thisOption->{'BIOS_Default'} ne $autoValue)));
          my $apcbTokenValueStr = $apcbTokenStr."_VALUE";
          $displayCondition && ($gApcbV3TokenValueStr .= sprintf ("#define %s %s  // %s\n",$apcbTokenValueStr, $thisOption->{'BIOS_Default'}, &getChoiceName($thisOption, $thisOption->{'BIOS_Default'})));

          if ($Visibility =~ /^External$/i) {
            if ($NvDataType =~ /^Bool$/i) {
              # $genApcbAutoGenCondition && $displayCondition && ($gApcbV3ExtBoolStr .= sprintf ("//%s=%s\n{%s, %s, {0,0,0}}, \\\n", $apcbTokenStr, &getChoiceName($thisOption, $thisOption->{'BIOS_Default'}), $apcbTokenStr, $thisOption->{'BIOS_Default'}));
              $genApcbAutoGenCondition && $displayCondition && ($gApcbV3ExtBoolStr .= sprintf ("APCB_TOKEN_BOOL (%s, %s), \\\n", $apcbTokenStr, $apcbTokenValueStr));
              $apcbSetTokenRoutine = "ApcbSetTokenBool";
            } elsif ($NvDataType =~ /^Byte$/i) {
              # $genApcbAutoGenCondition && $displayCondition && ($gApcbV3ExtU8Str .= sprintf ("//%s=%s\n{%s, %s, {0,0,0}}, \\\n", $apcbTokenStr, &getChoiceName($thisOption, $thisOption->{'BIOS_Default'}), $apcbTokenStr, $thisOption->{'BIOS_Default'}));
              $genApcbAutoGenCondition && $displayCondition && ($gApcbV3ExtU8Str .= sprintf ("APCB_TOKEN_U8 (%s, %s), \\\n", $apcbTokenStr, $apcbTokenValueStr));
              $apcbSetTokenRoutine = "ApcbSetToken8";
              if (&IsApcbBoolOption ($thisOption)) {
                # Provide warning message, suggest change to use BOOL type
                printf ("[Warning]APCB BOOL type is suggested (%s.%s)\n", $thisOption->{'Name'},$apcbTokenStr); #when a option match AUTO detected
              }
            } elsif ($NvDataType =~ /^Word$/i) {
              # $genApcbAutoGenCondition && $displayCondition && ($gApcbV3ExtU16Str .= sprintf ("//%s=%s\n{%s, %s, {0,0}}, \\\n", $apcbTokenStr, &getChoiceName($thisOption, $thisOption->{'BIOS_Default'}), $apcbTokenStr, $thisOption->{'BIOS_Default'}));
              $genApcbAutoGenCondition && $displayCondition && ($gApcbV3ExtU16Str .= sprintf ("APCB_TOKEN_U16 (%s, %s), \\\n", $apcbTokenStr, $apcbTokenValueStr));
              $apcbSetTokenRoutine = "ApcbSetToken16";
            } elsif ($NvDataType =~ /^DWord$/i) {
              # $genApcbAutoGenCondition && $displayCondition && ($gApcbV3ExtU32Str .= sprintf ("//%s=%s\n{%s, %s}, \\\n", $apcbTokenStr, &getChoiceName($thisOption, $thisOption->{'BIOS_Default'}), $apcbTokenStr, $thisOption->{'BIOS_Default'}));
              $genApcbAutoGenCondition && $displayCondition && ($gApcbV3ExtU32Str .= sprintf ("APCB_TOKEN_U32 (%s, %s), \\\n", $apcbTokenStr, $apcbTokenValueStr));
              $apcbSetTokenRoutine = "ApcbSetToken32";
            } else {
              printf ("[Warning] \"%s\" Unsupported APCB data type %s\n", $thisOption->{"Name"},$NvDataType);
              $gWarningStopFlag = 1;
            }
          } else {
            if ($NvDataType =~ /^Bool$/i) {
              # $genApcbAutoGenCondition && $displayCondition && ($gApcbV3ExtBoolStr .= sprintf ("//%s=%s\n{%s, %s, {0,0,0}}, \\\n", $apcbTokenStr, &getChoiceName($thisOption, $thisOption->{'BIOS_Default'}), $apcbTokenStr, $thisOption->{'BIOS_Default'}));
              $genApcbAutoGenCondition && $displayCondition && ($gApcbV3IntBoolStr .= sprintf ("APCB_TOKEN_BOOL (%s, %s), \\\n", $apcbTokenStr, $apcbTokenValueStr));
              $apcbSetTokenRoutine = "ApcbSetTokenBool";
            } elsif ($NvDataType =~ /^Byte$/i) {
              # $genApcbAutoGenCondition && $displayCondition && ($gApcbV3ExtU8Str .= sprintf ("//%s=%s\n{%s, %s, {0,0,0}}, \\\n", $apcbTokenStr, &getChoiceName($thisOption, $thisOption->{'BIOS_Default'}), $apcbTokenStr, $thisOption->{'BIOS_Default'}));
              $genApcbAutoGenCondition && $displayCondition && ($gApcbV3IntU8Str .= sprintf ("APCB_TOKEN_U8 (%s, %s), \\\n", $apcbTokenStr, $apcbTokenValueStr));
              $apcbSetTokenRoutine = "ApcbSetToken8";
              if (&IsApcbBoolOption ($thisOption)) {
                # Provide warning message, suggest change to use BOOL type
                printf ("[Warning] APCB BOOL type is suggested (%s.%s)\n", $thisOption->{'Name'},$apcbTokenStr);
              }
            } elsif ($NvDataType =~ /^Word$/i) {
              # $genApcbAutoGenCondition && $displayCondition && ($gApcbV3IntU16Str .= sprintf ("//%s=%s\n{%s, %s, {0,0}}, \\\n", $apcbTokenStr, &getChoiceName($thisOption, $thisOption->{'BIOS_Default'}), $apcbTokenStr, $thisOption->{'BIOS_Default'}));
              $genApcbAutoGenCondition && $displayCondition && ($gApcbV3IntU16Str .= sprintf ("APCB_TOKEN_U16 (%s, %s), \\\n", $apcbTokenStr, $apcbTokenValueStr));
              $apcbSetTokenRoutine = "ApcbSetToken16";
            } elsif ($NvDataType =~ /^DWord$/i) {
              # $genApcbAutoGenCondition && $displayCondition && ($gApcbV3IntU32Str .= sprintf ("//%s=%s\n{%s, %s}, \\\n", $apcbTokenStr, &getChoiceName($thisOption, $thisOption->{'BIOS_Default'}), $apcbTokenStr, $thisOption->{'BIOS_Default'}));
              $genApcbAutoGenCondition && $displayCondition && ($gApcbV3IntU32Str .= sprintf ("APCB_TOKEN_U32 (%s, %s), \\\n", $apcbTokenStr, $apcbTokenValueStr));
              $apcbSetTokenRoutine = "ApcbSetToken32";
            } else {
              print ("[Warning] \"%s\" Unsupported APCB data type %s\n", $thisOption->{"Name"},$NvDataType);
              $gWarningStopFlag = 1;
            }
          }
          # printf "\t>%s<\n",   $apcbSetTokenRoutine;

          #Generate Post time code for APCB token set
          if (defined $apcbSetTokenRoutine) {
            my $DisplayConditionCode;
            my $indent;
            $DisplayConditionCode = &GetDisplayConditionCode ($thisOption);
            if (defined $DisplayConditionCode) {
             $gApcbV3TokenSetStr .= sprintf ("  //Check Display Condition %s\n  if (%s) {\n", $thisOption->{"Display_condition"},$DisplayConditionCode);
             $indent++;
            }
            (my $autoExist, my $autoValue) = GetAutoValue ($thisOption);
            if ($autoExist) {
             $gApcbV3TokenSetStr .= '  'x$indent.sprintf ("  //Check if select Auto\n");
             $gApcbV3TokenSetStr .= '  'x$indent.sprintf ("  if (Setup_Config->%s != %s) {\n",$thisOption->{'Variable_name'}, $autoValue);
             $gApcbV3TokenSetStr .= '  'x$indent.sprintf ("    %s (ApcbProtocol, APCB_TYPE_PURPOSE_DEBUG, %s, Setup_Config->%s);\n",$apcbSetTokenRoutine, $apcbTokenStr, $thisOption->{'Variable_name'});
             $gApcbV3TokenSetStr .= '  'x$indent.sprintf "  }\n";
            } else {
             $gApcbV3TokenSetStr .= '  'x$indent.sprintf "  %s (ApcbProtocol, APCB_TYPE_PURPOSE_DEBUG, %s, Setup_Config->%s);  //User Input\n",  $apcbSetTokenRoutine, $apcbTokenStr, $thisOption->{'Variable_name'};
            }
            if (defined $DisplayConditionCode) {
             $gApcbV3TokenSetStr .= "  }\n";
            }
            $gApcbV3TokenSetStr .= "\n";
          }
        }
      }
    }
  }
}

sub genApcbV2SetDataFile
{
  my $ExtIntStr = shift;
  my $AttribSetStr = shift;
  my $ValueSetStr = shift;

# Ext Type Attrib #####
  printf $apcbSetDataFile
"
VOID
Prepare%sTypeAttrib (
  UINT32 *Size,
  APCB_PARAM_ATTRIBUTE *ApcbParaAttrib,
  VOID *CbsVariable
  )
{
  CBS_CONFIG *Setup_Config;
  UINT32     _Size;

  if (CbsVariable == NULL) {
    ASSERT (FALSE);
    return;
  }

  if (Size == NULL) {
    ASSERT (FALSE);
    return;
  }

  _Size = 0;
  Setup_Config = (CBS_CONFIG *) CbsVariable;

".$$AttribSetStr.
"
  //End
  if (ApcbParaAttrib != NULL) {
    ApcbParaAttrib->TimePoint = 0;
    ApcbParaAttrib->Token = APCB_TOKEN_CBS_DBG_LIMIT;
    ApcbParaAttrib->Size = 0;
    ApcbParaAttrib->Reserved = 0;
  }

  _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  *Size = _Size;
}

VOID
Prepare%sTypeValue (
  UINT32 *Size,
  UINT8 *ApcbParaValue,
  VOID *CbsVariable
  )
{
  CBS_CONFIG *Setup_Config;
  UINT32     _Size;

  if (CbsVariable == NULL) {
    ASSERT (FALSE);
    return;
  }

  if (Size == NULL) {
    ASSERT (FALSE);
    return;
  }

  _Size = 0;
  Setup_Config = (CBS_CONFIG *) CbsVariable;
".$$ValueSetStr.
"
  //End
  *Size = _Size;
}

", $ExtIntStr, $ExtIntStr;
}
#########################################################
#
# Concatenate APCB string and output to APCB file
#
#########################################################
sub genApcbTokens
{
  my $component = shift;
  my $i = 0;
  print $apcbAutoGenFile
"
//
// CBS $component APCB Tokens
//
";
  printf $apcbAutoGenFile
"#ifndef APCB_TOKEN_CBS_%s_BEGIN
  #define APCB_TOKEN_CBS_%s_BEGIN 0x%04X
#endif\n
", $component, $component, $i++;


  foreach (@{$gApcbDb->{$component}}) {
    printf $apcbAutoGenFile
"#ifndef $_
  #define %s 0x%04X
#endif\n
", $_, $i++;
  }

  printf $apcbAutoGenFile
"#ifndef APCB_TOKEN_CBS_%s_END
  #define APCB_TOKEN_CBS_%s_END 0x%04X
#endif\n
", $component, $component, $i++;

  die "Exceed the limit of APCB token space" if ($i >= 0x1FFF);

  printf $apcbAutoGenFile
"#ifndef APCB_TOKEN_CBS_%s_LIMIT
  #define APCB_TOKEN_CBS_%s_LIMIT 0x1FFF
#endif\n
", $component, $component;
}

sub concatenateApcbStrV2
{
  if ($inputApcbFile ne '') {
    # Only generate Apcb token if ApcbFile
    genApcbTokens("CMN");
    genApcbTokens("DBG");
  }

########## APCB Token Value Definition #######
  print $apcbAutoGenFile "
//
// APCB Token Value Definition
//
";
  print $apcbAutoGenFile $gApcbV2TokenValueStr;

########## APCB Data Definition #######
  print $apcbAutoGenFile "
//
// CBS CMN Token Attributes Data
//
";
  if (defined $gApcbV2ExtAttribStr) {
    print $apcbAutoGenFile "#define APCB_CBS_CMN_DEF_ATRIBS_AUTOGEN \\\n".$gApcbV2ExtAttribStr;
  } else {
    print $apcbAutoGenFile "#define APCB_CBS_CMN_DEF_ATRIBS_AUTOGEN\n";
  }

  print $apcbAutoGenFile "
//
// CBS CMN Value
//
";
  if (defined $gApcbV2ExtValueStr) {
    print $apcbAutoGenFile "#define APCB_CBS_CMN_DEF_VALUES_AUTOGEN \\\n".$gApcbV2ExtValueStr;
  } else {
    print $apcbAutoGenFile "#define APCB_CBS_CMN_DEF_VALUES_AUTOGEN\n";
  }

  print $apcbAutoGenFile "
//
// CBS DBG Token Attributes Data
//
";
  if (defined $gApcbV2IntAttribStr) {
    print $apcbAutoGenFile "#define APCB_CBS_DBG_DEF_ATRIBS_AUTOGEN \\\n".$gApcbV2IntAttribStr;
  } else {
    print $apcbAutoGenFile "#define APCB_CBS_DBG_DEF_ATRIBS_AUTOGEN\n";
  }

  print $apcbAutoGenFile "
//
// CBS DBG Value
//
";
  if (defined $gApcbV2IntValueStr) {
    print $apcbAutoGenFile "#define APCB_CBS_DBG_DEF_VALUE_AUTOGEN \\\n".$gApcbV2IntValueStr;
  } else {
    print $apcbAutoGenFile "#define APCB_CBS_DBG_DEF_VALUE_AUTOGEN\n";
  }
########## APCB Set Data File concatenate #######
if ($Program eq 'ZP') {
  $cbsApcbPortingFile = "#include <Porting.h>";
} elsif ($Program eq 'RV') {
  $cbsApcbPortingFile = "#include <Porting.h>";
}
  print $apcbSetDataFile
"
#include <Base.h>
#include <Library/DebugLib.h>
#include <AmdCbsVariable.h>
".$cbsApcbPortingFile."
#include <Addendum/Apcb/Inc/".GetProgramStr ($rootCfgHash->{'Name'})."/APCB.h>
";
  printf $apcbSetDataFile "#include <ApcbAutoGen%s.h>\n", $Program;

  genApcbV2SetDataFile ("Cmn", \$gApcbExtAttribSetStr, \$gApcbExtValueSetStr);
  genApcbV2SetDataFile ("Dbg", \$gApcbIntAttribSetStr, \$gApcbIntValueSetStr);

}


sub concatenateApcbStrV3
{
# set Empty Macro
  if ((defined $gApcbV3ExtBoolStr) || (defined $gApcbV3IntBoolStr)) {
    print $apcbAutoGenFile "#define APCB_TOKEN_BOOL_AUTOGEN_EMPTY 0\n";
  } else {
    print $apcbAutoGenFile "#define APCB_TOKEN_BOOL_AUTOGEN_EMPTY 1\n";
  }

  if ((defined $gApcbV3ExtU8Str) || (defined $gApcbV3IntU8Str)) {
    print $apcbAutoGenFile "#define APCB_TOKEN_U8_AUTOGEN_EMPTY 0\n";
  } else {
    print $apcbAutoGenFile "#define APCB_TOKEN_U8_AUTOGEN_EMPTY 1\n";
  }

  if ((defined $gApcbV3ExtU16Str) || (defined $gApcbV3IntU16Str)) {
    print $apcbAutoGenFile "#define APCB_TOKEN_U16_AUTOGEN_EMPTY 0\n";
  } else {
    print $apcbAutoGenFile "#define APCB_TOKEN_U16_AUTOGEN_EMPTY 1\n";
  }

  if ((defined $gApcbV3ExtU32Str) || (defined $gApcbV3IntU32Str)) {
    print $apcbAutoGenFile "#define APCB_TOKEN_U32_AUTOGEN_EMPTY 0\n";
  } else {
    print $apcbAutoGenFile "#define APCB_TOKEN_U32_AUTOGEN_EMPTY 1\n";
  }
# ########## APCB Token Value Definition #######
  print $apcbAutoGenFile "
//
// APCB Token Value Definition
//
";
  print $apcbAutoGenFile $gApcbV3TokenValueStr;


########## APCB Data Definition #######
  print $apcbAutoGenFile "
//
// APCB TOKEN COMMON BOOL DATA
//
";
  if (defined $gApcbV3ExtBoolStr) {
    print $apcbAutoGenFile "#define APCB_CMN_TOKEN_BOOL_AUTOGEN \\\n".$gApcbV3ExtBoolStr;
  } else {
    print $apcbAutoGenFile "#define APCB_CMN_TOKEN_BOOL_AUTOGEN\n";
  }

  print $apcbAutoGenFile "
//
// APCB TOKEN COMMON UINT8 DATA
//
";
  if (defined $gApcbV3ExtU8Str) {
    print $apcbAutoGenFile "#define APCB_CMN_TOKEN_U8_AUTOGEN \\\n".$gApcbV3ExtU8Str;
  } else {
    print $apcbAutoGenFile "#define APCB_CMN_TOKEN_U8_AUTOGEN\n";
  }

  print $apcbAutoGenFile "
//
// APCB TOKEN COMMON UINT16 DATA
//
";
  if (defined $gApcbV3ExtU16Str) {
    print $apcbAutoGenFile "#define APCB_CMN_TOKEN_U16_AUTOGEN \\\n".$gApcbV3ExtU16Str;
  } else {
    print $apcbAutoGenFile "#define APCB_CMN_TOKEN_U16_AUTOGEN\n";
  }

  print $apcbAutoGenFile "
//
// APCB TOKEN COMMON UINT32 DATA
//
";
  if (defined $gApcbV3ExtU32Str) {
    print $apcbAutoGenFile "#define APCB_CMN_TOKEN_U32_AUTOGEN \\\n".$gApcbV3ExtU32Str;
  } else {
    print $apcbAutoGenFile "#define APCB_CMN_TOKEN_U32_AUTOGEN\n";
  }

  print $apcbAutoGenFile "
//
// APCB TOKEN DBG BOOL DATA
//
";
  if (defined $gApcbV3IntBoolStr) {
    print $apcbAutoGenFile "#define APCB_DBG_TOKEN_BOOL_AUTOGEN \\\n".$gApcbV3IntBoolStr;
  } else {
    print $apcbAutoGenFile "#define APCB_DBG_TOKEN_BOOL_AUTOGEN\n";
  }

  print $apcbAutoGenFile "
//
// APCB TOKEN DBG UINT8 DATA
//
";
  if (defined $gApcbV3IntU8Str) {
    print $apcbAutoGenFile "#define APCB_DBG_TOKEN_U8_AUTOGEN \\\n".$gApcbV3IntU8Str;
  } else {
    print $apcbAutoGenFile "#define APCB_DBG_TOKEN_U8_AUTOGEN\n";
  }

  print $apcbAutoGenFile "
//
// APCB TOKEN DBG UINT16 DATA
//
";
  if (defined $gApcbV3IntU16Str) {
    print $apcbAutoGenFile "#define APCB_DBG_TOKEN_U16_AUTOGEN \\\n".$gApcbV3IntU16Str;
  } else {
    print $apcbAutoGenFile "#define APCB_DBG_TOKEN_U16_AUTOGEN\n";
  }

  print $apcbAutoGenFile "
//
// APCB TOKEN DBG UINT32 DATA
//
";
  if (defined $gApcbV3IntU32Str) {
    print $apcbAutoGenFile "#define APCB_DBG_TOKEN_U32_AUTOGEN \\\n".$gApcbV3IntU32Str;
  } else {
    print $apcbAutoGenFile "#define APCB_DBG_TOKEN_U32_AUTOGEN\n";
  }

########## APCB Set Data File concatenate #######
  print $apcbSetDataFile
"
#include <Uefi.h>
#include <Base.h>
#include <Library/DebugLib.h>
#include <AmdCbsVariable.h>
#include <Porting.h>
#include <Protocol/AmdApcbProtocol.h>
#include <Addendum/Apcb/Inc/".$Program."/APCB.h>
";
  # printf $apcbSetDataFile "#include <ApcbAutoGen%s.h>\n", $Program;

if ($version =~ /^internal$/i) {
  printf $apcbSetDataFile
"
#include <Addendum/Apcb/Inc/".GetProgramStr ($rootCfgHash->{'Name'})."/Internal/ApcbV3TokenUidInternal.h>
";
}
  printf $apcbSetDataFile
"
EFI_STATUS
UpdateCbsApcbTokens (
  VOID *CbsVariable,
  AMD_APCB_SERVICE_PROTOCOL *ApcbProtocol
  )
{
  EFI_STATUS                            Status;
  CBS_CONFIG                            *Setup_Config;
  FP_GET_TOKEN_BOOL                     ApcbGetTokenBool;                 ///< Get an APCB BOOL token
  FP_SET_TOKEN_BOOL                     ApcbSetTokenBool;                 ///< Set an APCB BOOL token
  FP_GET_TOKEN_8                        ApcbGetToken8;                    ///< Get an APCB UINT8 token
  FP_SET_TOKEN_8                        ApcbSetToken8;                    ///< Set an APCB UINT8 token
  FP_GET_TOKEN_16                       ApcbGetToken16;                   ///< Get an APCB UINT16 token
  FP_SET_TOKEN_16                       ApcbSetToken16;                   ///< Set an APCB UINT16 token
  FP_GET_TOKEN_32                       ApcbGetToken32;                   ///< Get an APCB UINT32 token
  FP_SET_TOKEN_32                       ApcbSetToken32;                   ///< Set an APCB UINT32 token

  if (CbsVariable == NULL) {
    ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  }

  if (ApcbProtocol == NULL) {
    ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  }

  Status = ApcbProtocol->ApcbAcquireMutex (ApcbProtocol);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ApcbGetTokenBool = ApcbProtocol->ApcbGetTokenBool;                 ///< Get an APCB BOOL token
  ApcbSetTokenBool = ApcbProtocol->ApcbSetTokenBool;                 ///< Set an APCB BOOL token
  ApcbGetToken8 = ApcbProtocol->ApcbGetToken8;                    ///< Get an APCB UINT8 token
  ApcbSetToken8 = ApcbProtocol->ApcbSetToken8;                    ///< Set an APCB UINT8 token
  ApcbGetToken16 = ApcbProtocol->ApcbGetToken16;                   ///< Get an APCB UINT16 token
  ApcbSetToken16 = ApcbProtocol->ApcbSetToken16;                   ///< Set an APCB UINT16 token
  ApcbGetToken32 = ApcbProtocol->ApcbGetToken32;                   ///< Get an APCB UINT32 token
  ApcbSetToken32 = ApcbProtocol->ApcbSetToken32;                   ///< Set an APCB UINT32 token
  //Clear all token setting
  ApcbProtocol->ApcbPurgeAllTokens (ApcbProtocol, APCB_TYPE_PURPOSE_DEBUG);

  Setup_Config = (CBS_CONFIG *) CbsVariable;

".$gApcbV3TokenSetStr.
"
  //Write back updated data to SPI
  ApcbProtocol->ApcbFlushData (ApcbProtocol);
  ApcbProtocol->ApcbReleaseMutex (ApcbProtocol);
  return EFI_SUCCESS;
}";
}
