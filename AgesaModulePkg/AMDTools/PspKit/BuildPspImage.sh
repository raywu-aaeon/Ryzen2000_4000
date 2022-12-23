 # *****************************************************************************
 # *
 # * Copyright 2008 - 2015 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 # *
 # * AMD is granting you permission to use this software (the Materials)
 # * pursuant to the terms and conditions of your Software License Agreement
 # * with AMD.  This header does *NOT* give you permission to use the Materials
 # * or any rights under AMD's intellectual property.  Your use of any portion
 # * of these Materials shall constitute your acceptance of those terms and
 # * conditions.  If you do not agree to the terms and conditions of the Software
 # * License Agreement, please do not use any portion of these Materials.
 # *
 # * CONFIDENTIALITY:  The Materials and all other information, identified as
 # * confidential and provided to you by AMD shall be kept confidential in
 # * accordance with the terms and conditions of the Software License Agreement.
 # *
 # * LIMITATION OF LIABILITY: THE MATERIALS AND ANY OTHER RELATED INFORMATION
 # * PROVIDED TO YOU BY AMD ARE PROVIDED "AS IS" WITHOUT ANY EXPRESS OR IMPLIED
 # * WARRANTY OF ANY KIND, INCLUDING BUT NOT LIMITED TO WARRANTIES OF
 # * MERCHANTABILITY, NONINFRINGEMENT, TITLE, FITNESS FOR ANY PARTICULAR PURPOSE,
 # * OR WARRANTIES ARISING FROM CONDUCT, COURSE OF DEALING, OR USAGE OF TRADE.
 # * IN NO EVENT SHALL AMD OR ITS LICENSORS BE LIABLE FOR ANY DAMAGES WHATSOEVER
 # * (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF PROFITS, BUSINESS
 # * INTERRUPTION, OR LOSS OF INFORMATION) ARISING OUT OF AMD'S NEGLIGENCE,
 # * GROSS NEGLIGENCE, THE USE OF OR INABILITY TO USE THE MATERIALS OR ANY OTHER
 # * RELATED INFORMATION PROVIDED TO YOU BY AMD, EVEN IF AMD HAS BEEN ADVISED OF
 # * THE POSSIBILITY OF SUCH DAMAGES.  BECAUSE SOME JURISDICTIONS PROHIBIT THE
 # * EXCLUSION OR LIMITATION OF LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES,
 # * THE ABOVE LIMITATION MAY NOT APPLY TO YOU.
 # *
 # * AMD does not assume any responsibility for any errors which may appear in
 # * the Materials or any other related information provided to you by AMD, or
 # * result from use of the Materials or any related information.
 # *
 # * You agree that you will not reverse engineer or decompile the Materials.
 # *
 # * NO SUPPORT OBLIGATION: AMD is not obligated to furnish, support, or make any
 # * further information, software, technical information, know-how, or show-how
 # * available to you.  Additionally, AMD retains the right to modify the
 # * Materials at any time, without notice, and is not obligated to provide such
 # * modified Materials to you.
 # *
 # * U.S. GOVERNMENT RESTRICTED RIGHTS: The Materials are provided with
 # * "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
 # * subject to the restrictions as set forth in FAR 52.227-14 and
 # * DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
 # * Government constitutes acknowledgement of AMD's proprietary rights in them.
 # *
 # * EXPORT ASSURANCE:  You agree and certify that neither the Materials, nor any
 # * direct product thereof will be exported directly or indirectly, into any
 # * country prohibited by the United States Export Administration Act and the
 # * regulations thereunder, without the required authorization from the U.S.
 # * government nor will be used for any purpose prohibited by the same.
 # *
 # ***************************************************************************

#!/bin/bash
# BuildPspImage InputBiosFile rtmfile PspDirectoryCfg OutputBiosFile KeyMode

#HELP
function HELP {
  echo "Embed PSP contents to Specific BIOS image"
  echo ""
  echo "BuildPspImage.bat rtmfile PspDirectoryCfg OutputBiosFile"
  echo "  Positional parameters:"
  echo "    rtmfile           The Root trunk module of BIOS, commonly it is the"
  echo "                      SEC,PEI combined FV image"
  echo "    PspDirectoryCfg   Config file which describe PSP directory layout,"
  echo "                      and input bios informations"
  echo "    OutputBiosFile    The output bios image after embed the PSP contents"
  echo "    KeyMode           'TK|PK' Specify which key will be used, test key or"
  echo "                      production key"
  exit 1
}

#ERROR
function ERROR {
  echo "**** BuildPspImage.sh: Build PSP Image Fail ****"
  exit 2
}

#Input parameter check
if [ "$5" == "" ]; then
	HELP
fi

#System variable Check
if [ ! $PSPKIT_PATH ]; then
	PSPKIT_PATH=$pwd
fi

if [ ! $PSPKIT_PATH/BuildPspImage.sh ]; then
	echo "!!!PSPKIT_PATH system variable is NOT set correctly!!"
	exit 1
fi

if [ ! $PSP_FW_PATH ]; then
	PSP_FW_PATH=$PWD/AmdPlatformAmurPkg/Psp/Firmware
fi


###START
#BIOS images
InputBiosFile=$1
RTM_FILE=$2
PspDirectoryCfg=$3
FINAL_BIOS=$4

#Related PATH
PSP_DIR_TOOL_PATH=$PSPKIT_PATH/PspDirectoryTool
TEMP_PATH=$PSPKIT_PATH/Temp

#Create Temporary folder, and copy all files to it
rm -rf $TEMP_PATH
mkdir $TEMP_PATH
cp $PSP_DIR_TOOL_PATH/* $TEMP_PATH/
cp $PSP_FW_PATH/*.* $TEMP_PATH/
cp $PSPKIT_PATH/*.* $TEMP_PATH/

#TOOLS
BUILDPSPDIRECTORY=BuildPspDirectory.py
#Binaries
RTM_PRIVATE_KEY=TestRtmPrivateKey.pem
PSP_DIR_FILE=Output/BiosDirHeader.bin
RTM_PSPDIR_COMBINE_FILE=BiosRtmPspCombine.bin
RTM_FILE_SIGNATURE=RTMSignature.bin

pushd $TEMP_PATH

echo ""
echo "[Generate PSP Directory]"
this_command="python $BUILDPSPDIRECTORY bd $InputBiosFile $PspDirectoryCfg"
echo "$this_command"
eval $this_command || ERROR

if [ "$5" != "NOSIGN" ]; then
  echo ""
  echo "[Combine RTM - PSP Directory and sign this using public key]"
  this_command="cat $RTM_FILE $PSP_DIR_FILE > $RTM_PSPDIR_COMBINE_FILE"
  echo "$this_command"
  eval $this_command
  #Sign using Test Key
  if [ "$5" == "TK" ]; then
    echo "Use Test Key to sign $RTM_PSPDIR_COMBINE_FILE"
    openssl dgst -binary -sign $RTM_PRIVATE_KEY -sha256 -sigopt rsa_padding_mode:pss -sigopt rsa_pss_saltlen:-2 -out $RTM_FILE_SIGNATURE $RTM_PSPDIR_COMBINE_FILE
    cat $RTM_FILE_SIGNATURE | perl -0777e 'print scalar reverse <>' > Temp$RTM_FILE_SIGNATURE
    mv Temp$RTM_FILE_SIGNATURE $RTM_FILE_SIGNATURE
  #Sign using Production Key
  elif [ "$5" == "PK" ]; then
    echo "Use Production key to sign $RTM_PSPDIR_COMBINE_FILE"
    java -version || ERROR
    echo "SPCLIENT_PATH:$SPCLIENT_PATH"
    pushd $SPCLIENT_PATH
      rm -rf $RTM_FILE_SIGNATURE
      export sp_function="Sign AM BIOS"
      this_command="./SPClient.sh -in $TEMP_PATH/$RTM_PSPDIR_COMBINE_FILE -out $TEMP_PATH/$RTM_FILE_SIGNATURE"
      echo "$this_command"
      eval $this_command || ERROR
    popd
  else
    echo "Invalid KeyMode"
    HELP
  fi
fi

echo ""
echo "[Finally build the Final BiosImage]"
this_command="python $BUILDPSPDIRECTORY bb $InputBiosFile $PspDirectoryCfg $FINAL_BIOS"
echo "$this_command"
eval $this_command || ERROR
cp Output/$FINAL_BIOS ../
popd

echo ""
echo "PSP contents have been embed to $FINAL_BIOS"
