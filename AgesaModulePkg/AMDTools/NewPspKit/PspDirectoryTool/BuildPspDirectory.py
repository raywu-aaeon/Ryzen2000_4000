 # *****************************************************************************
 # *
 # * Copyright 2008 - 2018 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 # ******************************************************************************
import os
import sys
#Module Data Packing
import struct
#Module for arguments parsing
import argparse
#Module for logging, 
import logging
from pprint import pprint
#Module for XML parsing
import xml.etree.ElementTree as ET
from xml.etree.ElementTree import Element, SubElement, Comment, tostring
from xml.dom import minidom
import types
import pdb
import traceback
# pdb.set_trace()

Version = "3.1.1D"
#Version 3.1.1D  09/27/2018
  #Update to offset in EFS and PSP Directory

#Version 3.1.1C  09/26/2018
  #Fix instance disappeared when tool generate PspDirectory.xml for multiple instance Point entry

#Version 3.1.1B  09/05/2018
  #Add support EFS address 0x120000

#Version 3.1.1A  08/17/2018
  #Fix "dp" command doesn't support BIOS rom with subprogram in PSP DIR type, which bring in by version 3.1.19

#Version 3.1.19  07/25/2018
  #Add support for RomId

#Version 3.1.18  06/26/2018
  #Add dump function for MTS and RV2

#Version 3.1.17  05/22/2018
  #Fix SMU version display issue on SSP

#Version 3.1.16  05/21/2018
  #Fix output nonexistent HeaderBase in SSP 2Lv PSP Dir configuration.

#Version 3.1.15  04/08/2018
  # Support Devel SMU version display

#Version 3.1.14  04/02/2018
  # Fix dp -P SSP fail in parameter check
  # Add new attribute "HeaderBase" in PSP_DIR, BIOS_DIR.
  # When "HeaderBase" specified, the tool will put the directory header to address "HeaderBase" point to.
  # All IMAGE_ENTRY will be put to the region where "BASE" and "Size" speicified.
  #
  # If only "Base" specified, the tool will put the directory header at "Base", and IMAGE_ENTRYs follow by

#Version 3.1.13  03/01/2018
  # Add SSP combo suppport

#Version 3.1.12  02/26/2018
  # Update help description for entry 0xB

#Version 3.1.11  02/12/2018
  # Add 'SubProgam' support to BIOS DIR

#Version 3.1.10  01/18/2018
  # *Fix dump function abnormal exit when over 10 instances

#Version 3.1.09  11/14/2017
  # *Add Version rendering for KVM engine

#Version 3.1.08  10/24/2017
  # *Support subprogram filed in PSP Directory

#Version 3.1.07  07/26/2017
  # *Add Multiple ROMSIG Address support

#Version 3.1.06  07/26/2017
  # *Fix TR SMU version display issue 

#Version 3.1.05  06/15/2017
  # *Add new FW entry type

#Version 3.1.05  06/15/2017
  # *Add new FW entry type

#Version 3.1.04  04/01/2017
  # *Add version display for SMU2

#Version 3.1.03  03/31/2017
  # *Update PSP tool to accommodate with SMU version field change

#Version 3.1.02  11/14/2016
  # * HVB related changes for PSP init recovery (two BIOS signature)

#Version 3.1.01  10/24/2016
  # * Add combo DIR support to DP command (-P new required parameter added)

#Version 3.1.00  09/09/2016
  # * Add Recovery two level DIR support

#Version 3.0.09  08/23/2016
  # * Add entry 0x25 to 0x28

#Version 3.0.08  07/12/2016
  # * Add definition for CoreMCEData, correct modfiable bit for some entries

#Version 3.0.07  06/21/2016
  # * Add Support for PSP Combo header generation

#Version 3.0.06  05/06/2016
  # * Correct the SMU, PSP version
  # * Add version display for ABL & Ucode patch
  # * Add Entry ID for Ucode patch 0x66
  
#Version 3.0.05  3/31/2016
  # * Add support to specify the instance id of BIOS directory image
  # * Change default alignment from 0x1000 to 0x100
  # * Add new tag SpiBlockSize to specify the SPI block size used for modifiable entry
  # * Add New entry 0x38, 0x64, 0x65

#Version 3.0.04  12/17/2015
  # * Update binary identification sequence, check ROMSIG 1st

#Version 3.0.03  11/09/2015
  # * Support dump PSP SPI image

#Version 3.0.02  09/16/2015
  # * Update PSP entry definition according to PSP BIOS Guide ver 1.03

#Version 3.0.01  08/24/2015
  # * Add Secure gasket binary (0x24)

#Version 3.0.00  05/05/2015
  # * ZP initial support

#Version 2.1.12  03/16/2015
  # * Update PSP directory definition

#Version 2.1.11  03/06/2015
  # * Add Compress Flag support for BIOS directory

#Version 2.1.10  01/19/2015
  # * Change the order & method of parsing input binary for "dp" command to
  #   Fix Can't support eMMC image which "$BHD" BIOS header not locate at offset 0.

#Version 2.1.9  11/24/2014
  # * Output "Resetimage.bin" for type 62 with reset flag set

#Version 2.1.8  9/09/2014
  # * Update 'dp' command for only output image entry
  # * Fix 'dp' command display minus APOB entry address
  # * Fix 'bb', 'bd' command shown incorrect end address for a PSP entry
  # * Add check for PSP, BIOS DIR region address overlap in 'bb', 'bd' command

#Version 2.1.7  8/28/2014
 # * Mask high 4 BITS of PSP FW version
 # * Update DP -X output file format
  #   . Separate Entry Node to IMAGE_ENTRY, VALUE_ENTRY, POINT_ENTRY for both BIOS & PSP Directory
  #   . Remove Sub node of PSP BL/OS, SMU, Add new general Node Detail for BVM to present the detail column 

#Version 2.1.6  8/19/2014
 # * Add USB FW type

#Version 2.1.5  6/6/2014
 # * Update APOB, SMU2 Entry type
 # * Always fill APOB Source as zero

#Version 2.1.4
 # * Fix "DP" unexpected error exit when there is no Entry 0x11 in PSP DIR

#Version 2.1.3
 # * Add New Type 0x12, 0x61

#Version 2.1.2
 # * EMMC/UFS support 
 #         with AddressMode attribute in the Root tag added
 #         support exact eMMC type image
 # * Update BIOS Image Signature to "$BHD"
 # * Display tool's version at startup

#Version 2.1.1:
 # * Update Entry id: PspAgesaRsm 0x11->0x10; BiosDirInfo 0x12->0x11
 # * Fix RTMSignature.bin has been missed for dp -b
 # * Add output binary file name to "dp -x"

#Version 2.1.0:
 # * Add TypeAttrib tag support
 # * Update Entry id
 # * Add "dp" support to BIOS directory    

#Version 2.0.0: XML version configure file

#Static Value
ROMSIG_SIG_OFFSET = 0
ROMSIG_PSPDIR_OFFSET = 5
ROMSIG_BIOSDIR_OFFSET = 6
SECOND_GEN_EFS_OFFSET = 9
PSP_COMBO_SIGNATURE = 0x50535032 #2PSP
PSP_DIR_SIGNATURE = 0x50535024 #$PSP
PSP_LEVEL2_DIR_SIGNATURE = 0x324C5024 #$PL2
BIOS_DIR_SIGNATURE = 0x44484224 #$BHD
BIOS_LEVEL2_DIR_SIGNATURE = 0x324C4224 #$BL2
#Global Variable
DEBUG = 1
gAlignment= 0x100
DirHeaderSize = 0x400   #Always reserve 0x400 for Dir Header 
OutputPath='/'
AddressMode = 0
ProgramStr = 'None'
PSP_ENTRY_TYPE_LEVEL2_DIR = 0x40
BIOS_ENTRY_TYPE_LEVEL2_DIR = 0x70
gXorBit24 = 0
PspDirectoryEntryName = {
#                         Type:   DIR, Entry Type    ShortName    Full description  Modifiable 
                          0x00: ['PSP' ,'IMAGE_ENTRY','AmdPubKey','AMD public Key', 0],
                          0x01: ['PSP' ,'IMAGE_ENTRY','PspBootLoader','PSP Boot Loader firmware', 0],
                          0x02: ['PSP' ,'IMAGE_ENTRY','PspOs','PSP Secure OS firmware', 0],
                          0x03: ['PSP' ,'IMAGE_ENTRY','PspRecBL','PSP Recovery Boot Loader', 0],
                          0x04: ['PSP' ,'IMAGE_ENTRY','PspNv','PSP Non Volatile data', 1],
                          0x05: ['BIOS','IMAGE_ENTRY','OemPubKey','[OEM] BIOS public key signed with AMD key', 0],
                          0x06: ['BIOS','POINT_ENTRY','Rtm','BIOS RTM Volume', 0],
                          0x07: ['BIOS','IMAGE_ENTRY','RtmSignature','BIOS RTM volume Signature using OEM private key', 0],
                          0x08: ['PSP' ,'IMAGE_ENTRY','Smu','SMU offchip firmware', 0],
                          0x09: ['PSP' ,'IMAGE_ENTRY','DbgKey','AMD Secure Debug Key', 0],
                          0x0A: ['PSP' ,'IMAGE_ENTRY','OemAblKey','OEM ABL public key signed with AMD key', 0],
                          0x0B: ['PSP' ,'VALUE_ENTRY','Value','Secure Unlock Enable flag', 0],
                          0x0C: ['PSP' ,'IMAGE_ENTRY','PspTrustlet','PSP trustlet Binary', 0],
                          0x0D: ['PSP' ,'IMAGE_ENTRY','TrusletKey','truslet key(Signed public portion)', 0],
                          0x12: ['PSP' ,'IMAGE_ENTRY','Smu2','SMU offchip firmware 2', 0],
                          0x13: ['PSP' ,'IMAGE_ENTRY','PspEarlyUnlock','PSP early secure unlock debug image', 0],
                          0x20: ['PSP' ,'IMAGE_ENTRY','HwIpCfg', 'HW IP configuration file', 0],
                          0x21: ['PSP' ,'IMAGE_ENTRY','ikek', 'Wrapped iKEK', 0],
                          0x22: ['PSP' ,'IMAGE_ENTRY','PspTokenUnlockData', 'PSP token unlock data', 1],
                          0x23: ['PSP' ,'IMAGE_ENTRY','PspDiagBL', 'Entry to load PSP Diag BL on non-secure part via fuse', 0],
                          0x24: ['PSP' ,'IMAGE_ENTRY','SecureGasket', 'Secure Gasket', 0],
                          0x25: ['PSP' ,'IMAGE_ENTRY','Mp2Fw', 'MP2 FW', 0],
                          0x26: ['PSP' ,'IMAGE_ENTRY','Mp2Fw2', 'Reserved for MP2 FW part2', 0],
                          0x27: ['PSP' ,'IMAGE_ENTRY','UserModeUnitTest', 'User mode unit tests binary', 0],
                          0x28: ['PSP' ,'IMAGE_ENTRY','PspSystemDriver', 'PSP Entry points to system driver in SPI space', 0],
                          0x29: ['PSP' ,'IMAGE_ENTRY','Kvm', 'Location field pointing to KVM image', 0],
                          0x2A: ['PSP' ,'IMAGE_ENTRY','Mp5Fw', 'Location field pointing to MP5 FW', 0],
                          0x30: ['PSP' ,'IMAGE_ENTRY','PspAgesaBL0', 'PSP AGESA Binary 0', 0],
                          0x31: ['PSP' ,'IMAGE_ENTRY','PspAgesaBL1', 'PSP AGESA Binary 1', 0],
                          0x32: ['PSP' ,'IMAGE_ENTRY','PspAgesaBL2', 'PSP AGESA Binary 2', 0],
                          0x33: ['PSP' ,'IMAGE_ENTRY','PspAgesaBL3', 'PSP AGESA Binary 3', 0],
                          0x34: ['PSP' ,'IMAGE_ENTRY','PspAgesaBL4', 'PSP AGESA Binary 4', 0],
                          0x35: ['PSP' ,'IMAGE_ENTRY','PspAgesaBL5', 'PSP AGESA Binary 5', 0],
                          0x36: ['PSP' ,'IMAGE_ENTRY','PspAgesaBL6', 'PSP AGESA Binary 6', 0],
                          0x37: ['PSP' ,'IMAGE_ENTRY','PspAgesaBL7', 'PSP AGESA Binary 7', 0],
                          0x38: ['PSP' ,'IMAGE_ENTRY','SevData', 'SEV Data', 1],
                          0x39: ['PSP' ,'IMAGE_ENTRY','SevCode', 'Trusted application implementing SEV functionality', 0],
                          0x3A: ['PSP' ,'IMAGE_ENTRY','WhiteList', 'Processor serial number white list binary', 0],
                          0x40: ['PSP' ,'POINT_ENTRY','PspDirLv2', 'Point to PSP level 2 directory', 0],
                          0x5F: ['PSP' ,'IMAGE_ENTRY','Scs','SCS Binary', 0],
                          0x60: ['BIOS','IMAGE_ENTRY','Apcb','Agesa PSP Customization Block', 1],
                          0x61: ['BIOS','POINT_ENTRY','Apob','Agesa PSP Output Block', 0],
                          0x62: ['BIOS','POINT_ENTRY','BiosFirmware','Bios firmware', 0],
                          0x63: ['BIOS','IMAGE_ENTRY','ApobNv','APOB NV Copy', 1],
                          0x64: ['BIOS','IMAGE_ENTRY','PmuCode','Instruction portion of PMU firmware', 0],
                          0x65: ['BIOS','IMAGE_ENTRY','PmuData','Data portion of PMU firmware', 0],
                          0x66: ['BIOS','IMAGE_ENTRY','UCodePatch','Microcode Patch', 0],
                          0x67: ['BIOS','IMAGE_ENTRY','CoreMceData','core machine check exception data', 1],
                          0x68: ['BIOS','IMAGE_ENTRY','ApcbRec','Location field points to the backup copy of APCB data', 1],
                          0x69: ['BIOS','IMAGE_ENTRY','EarlyVgaImage','Location field pointing to the interpreter binary that displays the video image', 0],
                          0x6A: ['BIOS','IMAGE_ENTRY','Mp2Cfg','Location field pointing to the MP2 FW configuration file', 0],
                          0x70: ['BIOS','POINT_ENTRY','BIOSDirLv2', 'Point to BIOS level 2 directory', 0],
                                 }

ProgramTable = {
  'ZP': {"AndMask":0xFFFF0000,"PSPID": 0xBC090000, "BIOSDIR_OFFSET": 6, "SECOND_GEN_EFS": 1},
  'RV': {"AndMask":0xFFFF0000,"PSPID": 0xBC0A0000, "BIOSDIR_OFFSET": 7, "SECOND_GEN_EFS": 1},
  'SSP': {"AndMask":0xFFFF0000,"PSPID": 0xBC0B0000, "BIOSDIR_OFFSET": 8, "SECOND_GEN_EFS": 0},
  'ARD': {"AndMask":0xFFFF0000,"PSPID": 0xBC0C0000, "BIOSDIR_OFFSET": 7, "SECOND_GEN_EFS": 1},
}

RomSigAddrTable = [
  0x00FA0000, #  --> 512KB base
  0x00F20000, #  --> 1MB base
  0x00E20000, #  --> 2MB base
  0x00C20000, #  --> 4MB base
  0x00820000, #  --> 8MB base
  0x00020000, #  --> 16MB base
  0x00120000, #  --> Special Base
]

#Set log level to debug, internal debug only
log = logging.getLogger();
FORMAT = '%(message)s'  #message ONLY
if (DEBUG):
  logging.basicConfig(format= FORMAT,stream=sys.stderr,level=logging.DEBUG)
else:
  #Set log level to debug, internal debug only
  logging.basicConfig(format= FORMAT,stream=sys.stderr,level=logging.INFO)

#Utility routines
def StrToNum (Str):
  if (Str != None):
    if type(Str) is str:
      if (Str.endswith ('L')):
        Str = Str.rstrip ('L')
      num = int(Str, 0)
      return num
    elif type(Str) is int:
      return Str
    else:
      print "unexpected Data Type ", type(Str)
      FatalErrorExit ()

def CheckFileExistance (file):
  return os.path.exists(file)

def IsImageEntry (Entry):
  if (Entry['Entry'] == 'IMAGE_ENTRY'):
    return True
  return False

def IsValueEntry (Entry):
  if (Entry['Entry'] == 'VALUE_ENTRY'):
    return True
  return False

def IsPointEntry (Entry):
  if (Entry['Entry'] == 'POINT_ENTRY'):
    return True
  return False

def IsResetImageEntry (Entry):
  if ((Entry['Entry'] == 'POINT_ENTRY') and
      (Entry['Type'] == 0x62)  and
      (Entry['ResetImage'] == 1)) :
    return True
  return False

def FatalErrorExit ():
  log.info (traceback.extract_stack())
  log.info ("ERORR Exit\n")
  sys.exit (2)

def prettify(elem):
    """Return a pretty-printed XML string for the Element.
    """
    rough_string = tostring(elem, 'utf-8')
    reparsed = minidom.parseString(rough_string)
    return reparsed.toprettyxml(indent="  ")

def GetOccupiedSize (ActualSize, Alignment):
  """Calculate occupied size considering the alignment"""
  return   (ActualSize + (((Alignment) - ((ActualSize) & ((Alignment) - 1))) & ((Alignment) - 1)))

def AlignAddress (Address, Alignment):
  """Calculate occupied size considering the alignment"""
  return   (Address + (((Alignment) - ((Address) & ((Alignment) - 1))) & ((Alignment) - 1)))


def getEntryType (DirectoryInfo, EntryInfo):
  global PspDirectoryEntryName
  if EntryInfo["Type"] in PspDirectoryEntryName:
    #Check if inside of Current DIR region if not set to "POINT_ENTRY"
    if (DirectoryInfo["BaseOffset"] != 0):
      BaseOffset = DirectoryInfo["BaseOffset"]
    else :
      BaseOffset = DirectoryInfo["DirOffset"]

    if ((EntryInfo["Address"] >= BaseOffset) and (EntryInfo["Address"] < BaseOffset + DirectoryInfo["DirSize"])): 
      EntryType = PspDirectoryEntryName[EntryInfo["Type"]][1]
    else:
      EntryType = "POINT_ENTRY"
  else:
    EntryType = "UNKNOWN_ENTRY"
  return EntryType

def getEntryShortName (Type):
  global PspDirectoryEntryName
  if Type in PspDirectoryEntryName:
    return PspDirectoryEntryName[Type][2]
  else:
    return "unknown"

def getEntryName (Type):
  global PspDirectoryEntryName
  if Type in PspDirectoryEntryName:
    return PspDirectoryEntryName[Type][3]
  else:
    return "Unknown Type"

def IsEntryModifiable (Type):
  global PspDirectoryEntryName
  if Type in PspDirectoryEntryName:
    return PspDirectoryEntryName[Type][4]
  else:
    return 0

def GetOutEntryFileBaseName (entry, DirStr, Level):
  if (IsImageEntry (entry)):
    if ((entry['Type'] == 7) and (Level == 1)):
    #Use constant name for RTM signature
      return "RTMSignature"
    elif ((entry['Type'] == 7) and (Level == 2)):
    #Use constant name for RTM signature
      return "RTMSignatureL1L2"
    else:
      if 'Type16' in entry:
        return "%sL%x_Typex%x_%s" %(DirStr, Level, entry['Type16'], getEntryShortName(entry['Type']))
      else:
        return "%sL%x_Typex%x_%s" %(DirStr, Level, entry['Type'], getEntryShortName(entry['Type']))
  elif (IsResetImageEntry (entry)):
      return "ResetImage"
  else:
    return "Unsupported"

def GetOutEntryFileName (entry, DirStr, Level):
  if (IsImageEntry (entry)):
    if ((entry['Type'] == 7) and (Level == 1)):
    #Use constant name for RTM signature
      return "RTMSignature.bin"
    elif ((entry['Type'] == 7) and (Level == 2)):
    #Use constant name for RTM signature
      return "RTMSignatureL1L2.bin"
    else:
      if 'Type16' in entry:
        return "%sL%x_Typex%x_%s.bin" %(DirStr, Level, entry['Type16'], getEntryShortName(entry['Type']))
      else:
        return "%sL%x_Typex%x_%s.bin" %(DirStr, Level, entry['Type'], getEntryShortName(entry['Type']))
  elif (IsResetImageEntry (entry)):
      return "ResetImage.bin"
  else:
    return "Unsupported"

def Fletcher32Crc (data, words):
  sum1 = 0xffff
  sum2 = 0xffff
  tlen = 0
  i = 0

  while (words):
    tlen = 359
    if (words < 359):
      tlen = words
    words -=tlen

    while tlen:
      s = struct.Struct('H')
      val = s.unpack(data [i: i+2])[0]
      #print "%x"%(val),
      i +=2
      sum1 += val
      sum2 += sum1
      tlen -=1

    sum1 = (sum1 & 0xffff) + (sum1 >> 16)
    sum2 = (sum2 & 0xffff) + (sum2 >> 16)

  sum1 = (sum1 & 0xffff) + (sum1 >> 16)
  sum2 = (sum2 & 0xffff) + (sum2 >> 16)
  return (sum2 << 16 | sum1)

def WriteBinaryFile (File, buffer):
  global OutputPath
  try:
    FileHandle = open (OutputPath + File,'wb')
  except:
    print "Error: Opening ", OutputPath + File
    FatalErrorExit ()
  FileHandle.write(buffer)
  FileHandle.close()


def ReadBinaryFile (File):

  if (os.path.exists(File) == False):
    print "\nError :", File, " does not exist"
    return (None)

  try:
    FileHandle = open (File,'rb')
  except:
    print "Error: Opening ", File
    FatalErrorExit ()
  lines = FileHandle.read()
  FileHandle.close()
  return lines

def getOffsetInBin (romsize, offset):
  '''
    romsize equal zero indicate it is a relative address, no need to do the translation
  '''
  if ((gXorBit24 == 1) and (offset & 0xF0000000)):
    log.info ("Incorrect configuration, EFS at top 16M, where offset still using legacy Pysical MMIO address")
    FatalErrorExit ()
  if (romsize):
    if (romsize > 0x1000000):
      # Physical Address can only be used on pre SSP program, force set romsize to 16M
      romsize = 0x1000000
    #Use 0xFFFFFFFF + 1 instead of 0x100000000 to avoid long number which will leading "L" trailing when print out
    return romsize-(0xFFFFFFFF - offset + 1)
  else:
    return offset

def getMmioAddress (romsize, offset):
  #Use 0xFFFFFFFF + 1 instead of 0x100000000 to avoid long number which will leading "L" trailing when print out
  # MMIO address can only be used for legacy program, and only support upper to 16M SPI
  if (romsize >0x1000000):
    romsize = 0x1000000
  return 0xFFFFFFFF - romsize + offset + 1

def getRelativeAddress (romsize, mmioAddr):
  #Use 0xFFFFFFFF + 1 instead of 0x100000000 to avoid long number which will leading "L" trailing when print out
  #return 0, 
  #if mmioAddr is not in given romsize MMIO region
  if (mmioAddr < getMmioAddress (romsize, 0)):
    return 0
  else:
    return mmioAddr - getMmioAddress (romsize, 0);

def AddrXorBit24 (address, xorbit):
  return (address ^ (xorbit << 24))

def AddrGlobalXorBit24 (address):
  global gXorBit24
  if (address != None):
    return (address ^ (gXorBit24 << 24))
  else:
    return None

def PatchBinary (OrgBuffer, ModBuffer, Offset, Message):
  Offset = AddrGlobalXorBit24 (Offset)
  log.info ("<%s> content copied between [0x%04x ~ 0x%04x]" , Message, Offset, Offset + len(ModBuffer) -1)
  if (Offset + len (ModBuffer) > len (OrgBuffer)):
    log.info ("ERROR: Size error in PatchBinary")
    FatalErrorExit ()
  buffer = OrgBuffer[0:Offset] + ModBuffer + OrgBuffer[Offset+ len(ModBuffer):]
  return buffer

def StringlizeDict (Dict):
  for (k,v) in Dict.iteritems():
    if (type(v) == types.IntType or type(v) == types.LongType):
      Dict[k]=hex(v)
  return Dict

#Functional routines
def ParseArg ():
  global Version
  global ProgramStr
  global ProgramTable
  """Parse Input arguments, and return the parsed result"""
  Parser = argparse.ArgumentParser (description='Tool used to Build PSP DirTable & Embed/Dump PSP entries')
  Parser.add_argument ('--version', action='version', version='BuildPspDirectory %s' %(Version))
  Parser.add_argument ('-o','--outputpath',default="Output")
  SubParser = Parser.add_subparsers(dest='subcommand',help="Type '<subcommand> -h' for help on a specific subcommand")
  #Build Directory table
  BDParser = SubParser.add_parser ('bd',help='Build Directory table header only')
  BDParser.add_argument ("InBiosImage", help="Specify the INPUT BIOS image file name")
  BDParser.add_argument ("CfgFile", help="Specify the configure file for build the PSP Directory")
  #Build Bios image with psp entry file embedded
  BBParser = SubParser.add_parser ('bb',help='Build Bios image with psp entry file embedded')
  BBParser.add_argument ("InBiosImage", help="Specify the INPUT BIOS image file name")
  BBParser.add_argument ("CfgFile", help="Specify the config file for build the PSP Directory")
  BBParser.add_argument ("OutBiosImage", help="Specify the OUTPUT BIOS image file name")
  #DumP psp entry of given BIOS image
  DPParser = SubParser.add_parser ('dp',help='DumP psp entry of given BIOS image')
  DPParser.add_argument ("InBiosImage", help="Specify the INPUT BIOS image file name")
  DPParser.add_argument ("-p", "--program", help="Specify the program name, Valid choices: %s" %ProgramTable.keys(), required=True)
  DPParser.add_argument ("-x","--xml", help="Output the information in XML format to PspDirInfo.xml",action="store_true")
  DPParser.add_argument ("-b","--binary", help="Output  psp binaries to outputpath",action="store_true")
  DPParser.add_argument ("-d","--directory", help="Output PspDirectory.cfg to outputpath",action="store_true")

  args = Parser.parse_args ()
  #Parameter check
  if (args.subcommand == 'bd' or args.subcommand == 'bb'):
    if (CheckFileExistance(args.CfgFile) == False):
      log.info ("[Error] Can't Open CfgFile '%s'", args.CfgFile)
      FatalErrorExit ()
      #To be Done: Check PSP Directory Format
      #if (CheckCfgFileFormat(args.CfgFile) == False):
        # print "[Error] CfgFile '%s' doesn't exists" %args.CfgFile
        # FatalErrorExit ()

  if (args.subcommand == 'dp' or args.subcommand == 'bd' or args.subcommand == 'bb'):
    if (CheckFileExistance(args.InBiosImage) == False):
      log.info ("[Error] Can't Open BiosImage '%s'", args.InBiosImage)
      FatalErrorExit ()
# Validate Program string
  if (args.subcommand == 'dp'):
    ValidProgram = False
    for program in ProgramTable.keys():
      if (args.program.upper() != program):
        ValidProgram = True
        break
    if (ValidProgram == False):
      log.info ("[Error] Not a valid program string, only %s are supported", ProgramTable.keys())
      FatalErrorExit ()
    ProgramStr = args.program.upper ()
  return args

def ValidatePspDirAttrib (PspDirAttrib):
  # The valid attributes for PSP Dir tag can be like below:
  # *Note* the attributes are case sensitive
  # 1) None       |Used when only generate the directory header with "bd" command
  # 2) Base       |Used for fix address format, which all address need explicit defined, include where to embed the Directory Header.
  # 3) Base, Size |Used for dynamic address format, user reserve a region for hold all PSP entries include the header
  if (((PspDirAttrib['Base'] == None) and  (PspDirAttrib['Size'] != None))):
    return False

  if (((PspDirAttrib['Base'] == None) and  (PspDirAttrib['HeaderBase'] != None))):
    log.info ("ERROR: Don't support specify HeaderBase only, Base need be declared")
    return False

  if (PspDirAttrib['HeaderBase'] != None):
    if ((StrToNum(PspDirAttrib['HeaderBase']) % 0x1000) != 0):
      log.info ("ERROR: HeaderBase must be 0x1000 aligned")
      return False
    if (StrToNum(PspDirAttrib['HeaderBase']) > 0x4000000):
      log.info ("ERROR: Exceed Max HeaderBase 0x4000000")
      return False

  if (PspDirAttrib['Size'] != None):
    if ((StrToNum(PspDirAttrib['Size']) % 0x1000) != 0):
      log.info ("ERROR: Dir Size must be 0x1000 aligned")
      return False
    if (StrToNum(PspDirAttrib['Size']) > 0x400000):
      log.info ("ERROR: Exceed Max Dir Size 0x400000")
      return False

  if (PspDirAttrib['SpiBlockSize'] != None):
    if ((StrToNum(PspDirAttrib['SpiBlockSize']) % 0x1000) != 0):
      log.info ("ERROR: SpiBlockSize must be 0x1000 aligned")
      return False
    if (StrToNum(PspDirAttrib['SpiBlockSize']) > 0x10000):
      log.info ("ERROR: Exceed Max SpiBlockSize 0x10000")
      return False
  return True

def ValidateBiosDirAttrib (BiosDirAttrib):
  # The valid attributes for PSP Dir tag can be like below:
  # *Note* the attributes are case sensitive
  # 1) None       |Used when only generate the directory header with "bd" command
  # 2) Address    |Used for fix address format, which all address need explicit defined, include where to embed the Directory Header.
  # 3) Base, Size |Used for dynamic address format, user reserve a region for hold all PSP entries include the header
  if (((BiosDirAttrib['Base'] == None) and  (BiosDirAttrib['Size'] != None))):
    return False

  if (((BiosDirAttrib['Base'] == None) and  (BiosDirAttrib['HeaderBase'] != None))):
    log.info ("ERROR: Don't support specify HeaderBase only, Base need be declared")
    return False

  if (BiosDirAttrib['Size'] != None):
    if ((StrToNum(BiosDirAttrib['Size']) % 0x1000) != 0):
      log.info ("ERROR: Dir Size must be 0x1000 aligned")
      return False
    if (StrToNum(BiosDirAttrib['Size']) > 0x400000):
      log.info ("ERROR: Exceed Max Dir Size 0x400000")
      return False

  if (BiosDirAttrib['SpiBlockSize'] != None):
    if ((StrToNum(BiosDirAttrib['SpiBlockSize']) % 0x1000) != 0):
      log.info ("ERROR: SpiBlockSize must be 0x1000 aligned")
      return False
    if (StrToNum(BiosDirAttrib['SpiBlockSize']) > 0x10000):
      log.info ("ERROR: Exceed Max SpiBlockSize 0x10000")
      return False
  return True

def ValidateComboDirAttrib (ComboDirAttrib):
  if (((ComboDirAttrib['Base'] == None) or  (ComboDirAttrib['LookUpMode'] == None))):
    log.info ("ERROR: Base and LookUpMode need be explicit defined in COMBO_DIR tag")
    return False
  if (StrToNum(ComboDirAttrib['LookUpMode']) > 1):
    log.info ("Invalid value for LookUpMode, should be 0 or 1")


def ValidatePspEntry (PspEntry):
  #Below items will be checked
  #entry: should be one of three: IMAGE_ENTRY;VALUE_ENTRY;POINT_ENTRY
  if (not (IsImageEntry (PspEntry) or IsValueEntry(PspEntry) or IsPointEntry (PspEntry))):
    return False
  #Type should be explicit defined
  if (PspEntry['Type'] == None):
    log.info ("ERROR: Type haven't been explicit defined")
    return False
  #"File" need be defined for Image entry:
  if (IsImageEntry (PspEntry)):
    if (PspEntry['File'] == None):
      log.info ("ERROR: File haven't been explicit defined for IMAGE_ENTRY")
      return False
  #"Value" need be defined for Value entry
  if (IsValueEntry (PspEntry)):
    if (PspEntry['Value'] == None):
      log.info ("ERROR: Value haven't been explicit defined for VALUE_ENTRY")
      return False
  #"Address" "Size" need be defined for Point entry
  if (IsPointEntry(PspEntry)):
    if ((PspEntry['Address'] == None) or (PspEntry['Size'] == None)):
      log.info ("ERROR: Address or Size haven't been explicit defined for VALUE_ENTRY")
      return False

  if (PspEntry['RomId'] != None):
    if (StrToNum(PspEntry['RomId']) > 4):
      log.info ("ERROR: Exceed RomId valid range [0-3]\n")
      return False
  return True

def ValidateBiosEntry (BiosEntry):
  #Below items will be checked
  #entry: should be one of three: IMAGE_ENTRY;VALUE_ENTRY;POINT_ENTRY
  if (not (IsImageEntry (BiosEntry) or IsValueEntry(BiosEntry) or IsPointEntry (BiosEntry))):
    return False
  #Type should be explicit defined
  if (BiosEntry['Type'] == None):
    log.info ("ERROR: Type haven't been explicit defined")
    return False
  #"File" need be defined for Image entry:
  if (IsImageEntry (BiosEntry)):
    if (BiosEntry['File'] == None):
      return False
  #"Value" need be defined for Value entry
  if (IsValueEntry (BiosEntry)):
    if (BiosEntry['Value'] == None):
      return False
  #"Address" "Size" need be defined for Point entry
  if (IsPointEntry(BiosEntry)):
    if ((BiosEntry['Address'] == None) or (BiosEntry['Size'] == None)):
      return False
  if (BiosEntry['Type'] > 0xFF):
      log.info ("ERROR: Type exceed limit 0xFF")
      return False

  if (BiosEntry['RegionType'] > 0xFF):
      log.info ("ERROR: RegionType exceed limit 0xFF")
      return False

  if (BiosEntry['ResetImage'] > 0x1):
      log.info ("ERROR: BiosResetImage exceed limit 0x1")
      return False

  if (BiosEntry['Copy'] > 0x1):
      log.info ("ERROR: Copy exceed limit 0x1")
      return False

  if (BiosEntry['ReadOnly'] > 0x1):
      log.info ("ERROR: ReadOnly exceed limit 0x1")
      return False

  if (BiosEntry['Compressed'] > 0x1):
      log.info ("ERROR: Compressed exceed limit 0x1")
      return False

  if (BiosEntry['Instance'] > 0xF):
      log.info ("ERROR: Instance exceed limit 0xF")
      return False

  if (BiosEntry['SubProgram'] > 0x7):
      log.info ("ERROR: SubProgram exceed limit 0x7")
      return False

  if (BiosEntry['RomId'] > 4):
    log.info ("ERROR: Exceed RomId valid range [0-3]\n")
    return False
  return True

def ValidateComboEntry (ComboEntry):
  #Below items will be checked
  #Below attribute should be explicit defined
  if (ComboEntry['IdSelect'] == None):
    log.info ("ERROR: IdSelect haven't been explicit defined")
    return False
  if (ComboEntry['Id'] == None):
    log.info ("ERROR: Id haven't been explicit defined")
    return False
  if (ComboEntry['Address'] == None):
    log.info ("ERROR: Address haven't been explicit defined")
    return False
  if (ComboEntry['IdSelect'] >0x1):
    log.info ("ERROR: Invalid value for IdSelect, should be either 0 or 1")
    return False
  return True

def BuildPspEntries (PspDir):
  PspEntries = []
  for entry in PspDir:
    log.debug ("Psp Entry %s->%s",entry.tag, entry.attrib)
    PspEntry = {}
    # Initial default value
    PspEntry['Type'] = None
    PspEntry['File'] = None
    PspEntry['Address'] = None
    PspEntry['Size'] = None
    PspEntry['Entry'] = None
    PspEntry['Value'] = None
    PspEntry['Recovery'] = 0
    PspEntry['RomId'] = 0
    #Update the attribute get from XML
    PspEntry.update (entry.attrib)
    PspEntry['Entry'] = entry.tag
    #Transfer all numeric field
    PspEntry['Type'] = StrToNum(PspEntry['Type'] )
    PspEntry['Address'] = StrToNum(PspEntry['Address'])
    PspEntry['Size'] = StrToNum(PspEntry['Size'])
    PspEntry['Value'] = StrToNum(PspEntry['Value'])
    PspEntry['Recovery'] = StrToNum(PspEntry['Recovery'])
    PspEntry['RomId'] = StrToNum (PspEntry['RomId'])
    log.debug ("PspEntry %s", PspEntry)
    if (ValidatePspEntry (PspEntry) == False):
      log.info ("ERROR: Unrecognized Attribute/Tag found in %s->%s", entry.tag, entry.attrib)
      FatalErrorExit ()
    PspEntries.append(PspEntry)
  return PspEntries


def BuildBiosEntries (BiosDir):
  BiosEntries = []
  for entry in BiosDir:
    BiosEntry = {}
    log.debug ("%s->%s",entry.tag, entry.attrib)
    # Initial default value
    BiosEntry['Type'] = None
    BiosEntry['File'] = None
    BiosEntry['Address'] = None
    BiosEntry['Size'] = None
    BiosEntry['Entry'] = None
    BiosEntry['Destination'] = '0xFFFFFFFFFFFFFFFF'
    BiosEntry['Instance'] = 0
    BiosEntry['SubProgram'] = 0
    BiosEntry['RomId'] = 0
    #Set all attributes default to 0
    BiosEntry['RegionType'] = 0
    BiosEntry['ResetImage'] = 0
    BiosEntry['Copy'] = 0
    BiosEntry['ReadOnly'] = 0
    BiosEntry['Compressed'] = 0
    BiosEntry['Recovery'] = 0
    #Update the attribute get from XML
    BiosEntry.update (entry.attrib)
    BiosEntry['Entry'] = entry.tag
    #Transfer all numeric field
    BiosEntry['Type'] = StrToNum(BiosEntry['Type'] )
    BiosEntry['Address'] = StrToNum(BiosEntry['Address'])
    BiosEntry['Size'] = StrToNum(BiosEntry['Size'])
    BiosEntry['Destination'] = StrToNum(BiosEntry['Destination'])
    BiosEntry['Instance'] = StrToNum(BiosEntry['Instance'])
    BiosEntry['Recovery'] = StrToNum(BiosEntry['Recovery'])
    BiosEntry['SubProgram'] = StrToNum (BiosEntry['SubProgram'])
    BiosEntry['RomId'] = StrToNum (BiosEntry['RomId'])

    for typeAttrib in entry:
      log.debug ("%s->%s",typeAttrib.tag, typeAttrib.attrib)
      #Update the attribute get from XML
      BiosEntry.update (typeAttrib.attrib)
      #Transfer all numeric field
      BiosEntry['RegionType'] = StrToNum(BiosEntry['RegionType'] )
      BiosEntry['ResetImage'] = StrToNum(BiosEntry['ResetImage'])
      BiosEntry['Copy'] = StrToNum(BiosEntry['Copy'])
      BiosEntry['ReadOnly'] = StrToNum(BiosEntry['ReadOnly'])
      BiosEntry['Compressed'] = StrToNum(BiosEntry['Compressed'])
    log.debug ("BiosEntry %s", BiosEntry)
    if (ValidateBiosEntry (BiosEntry) == False):
      log.info ("ERROR: Unrecognized Attribute/Tag found in %s->%s", entry.tag, entry.attrib)
      FatalErrorExit ()
    BiosEntries.append(BiosEntry)
  return BiosEntries

def BuildComboEntries (ComboDir):
  ComboEntries = []
  for entry in ComboDir:
    log.debug ("Combo Entry %s->%s",entry.tag, entry.attrib)
    ComboEntry = {}
    # Initial default value
    ComboEntry['IdSelect'] = None
    ComboEntry['Id'] = None
    ComboEntry['Address'] = None
    #Update the attribute get from XML
    ComboEntry.update (entry.attrib)
    #Transfer all numeric field
    ComboEntry['IdSelect'] = StrToNum(ComboEntry['IdSelect'] )
    ComboEntry['Id'] = StrToNum(ComboEntry['Id'])
    ComboEntry['Address'] = StrToNum(ComboEntry['Address'])
    log.debug ("ComboEntry %s", ComboEntry)
    if (ValidateComboEntry (ComboEntry) == False):
      log.info ("ERROR: Unrecognized Attribute/Tag found in %s->%s", entry.tag, entry.attrib)
      FatalErrorExit ()
    ComboEntries.append(ComboEntry)
  return ComboEntries

def ParseCfgFile (CfgFile):
  global AddressMode
  global DirHeaderSize
  global gXorBit24
  # To support multiple PSP Dir
  PspDicts = []
  BiosDicts = []

  ComboDict = {}
  try:
    tree = ET.parse (CfgFile)
  except:
    log.info ("ERROR: Parse the %s fail, please check file's format", CfgFile)
    FatalErrorExit ()
  root = tree.getroot ()
  # Get Address mode, if have been defined, or else use the default value
  if 'AddressMode' in root.attrib:
    log.info ("AddressMode explicit defined as %s", root.attrib['AddressMode'])

    AddressMode = StrToNum (root.attrib['AddressMode'])
    # Validate AddressMode Value
    if (not ((AddressMode == 0) or (AddressMode == 1))):
      log.info ("ERROR: Invalid AddressMode: 0 SPI(Default, if no explicit defined) 1: eMMC/UFS")
      FatalErrorExit ()
  if 'XorBit24' in root.attrib:
    log.info ("XorBit24 explicit defined as %s", root.attrib['XorBit24'])
    gXorBit24 = StrToNum (root.attrib['XorBit24'])

  for Dir in root:
    print Dir.tag
    #PSP DIR
    if (Dir.tag == 'PSP_DIR'):
      PspDict = {}
      #Init default value
      PspDict['Base'] = None
      PspDict['HeaderBase'] = None
      PspDict['Size'] = None
      PspDict['SpiBlockSize'] = None
      #Default Level 1 
      PspDict['Level'] = 1
      #Update the attribute get from XML
      PspDict.update (Dir.attrib)
      #Checking Attribute Keyword (Case sensitive)
      if (ValidatePspDirAttrib (PspDict) == False):
        log.info ("ERROR: Unrecognized Attribute found in %s", Dir.attrib)
        FatalErrorExit ()
      # log.debug ("PspDict: %s",PspDict)
      #Build PSP Entries
      PspDict['Entries'] = BuildPspEntries (Dir)
      #Transfer all numeric field
      PspDict['Base'] = StrToNum (PspDict['Base'])
      PspDict['HeaderBase'] = StrToNum (PspDict['HeaderBase'])
      PspDict['Size'] = StrToNum (PspDict['Size'])
      PspDict['SpiBlockSize'] = StrToNum (PspDict['SpiBlockSize'])
      PspDict['Level'] = StrToNum (PspDict['Level'])
      log.debug ("PspDict: %s", PspDict)
      PspDicts.append (PspDict)
    elif (Dir.tag == 'BIOS_DIR'):
      #BIOS DIR
      BiosDict = {}
      #Init default value
      BiosDict['Base'] = None
      BiosDict['HeaderBase'] = None
      BiosDict['Size'] = None
      BiosDict['SpiBlockSize'] = None
      #Default Level 1 
      BiosDict['Level'] = 1
      #Update the attribute get from XML
      BiosDict.update (Dir.attrib)
      #Checking Attribute Keyword (Case sensitive)
      if (ValidateBiosDirAttrib (BiosDict) == False):
        log.info ("ERROR: Unrecognized Attribute found in %s", Dir.attrib)
      #Build PSP Entries
      BiosDict['Entries'] = BuildBiosEntries (Dir)
      #Transfer all numeric field
      BiosDict['Base'] = StrToNum (BiosDict['Base'])
      BiosDict['HeaderBase'] = StrToNum (BiosDict['HeaderBase'])
      BiosDict['Size'] = StrToNum (BiosDict['Size'])
      BiosDict['SpiBlockSize'] = StrToNum (BiosDict['SpiBlockSize'])
      BiosDict['Level'] = StrToNum (BiosDict['Level'])
      log.debug ("BiosDict: %s", BiosDict)
      BiosDicts.append (BiosDict)
    elif (Dir.tag == 'COMBO_DIR'):
      #BIOS DIR
      #Init default value
      ComboDict['Base'] = None
      ComboDict['LookUpMode'] = None
      #Update the attribute get from XML
      ComboDict.update (Dir.attrib)
      #Checking Attribute Keyword (Case sensitive)
      #use BIOS Dir rule to validate
      if (ValidateComboDirAttrib (ComboDict) == False):
        log.info ("ERROR: Unrecognized Attribute found in %s", Dir.attrib)
      #Build Combo Entries
      ComboDict['Entries'] = BuildComboEntries (Dir)
      #Transfer all numeric field
      ComboDict['Base'] = StrToNum (ComboDict['Base'])
      ComboDict['LookUpMode'] = StrToNum (ComboDict['LookUpMode'])
      log.debug ("ComboDict: %s", ComboDict)
    else:
      log.info ("ERROR: Unrecognized Tag (%s) found in %s", Dir.tag, CfgFile)
      FatalErrorExit ()
  #Check DIR region overlap
  #Make a generic DIR array with base size information
  DirList = []
  if (len(BiosDicts) != 0):
    for BiosDict in BiosDicts:
      if ((BiosDict['Base'] != None) and (BiosDict['Size'] != None)):
        DirElmt = {}
        DirElmt ['Base'] = BiosDict ['Base']
        DirElmt ['Size'] = BiosDict ['Size']
        DirList.append (DirElmt)

  if (len(BiosDicts) != 0):
    for BiosDict in BiosDicts:
      if (BiosDict['HeaderBase'] != None):
        DirElmt = {}
        DirElmt ['Base'] = BiosDict ['HeaderBase']
        DirElmt ['Size'] = DirHeaderSize
        DirList.append (DirElmt)

  if (len(PspDicts) != 0):
    for PspDict in PspDicts:
      if ((PspDict['Base'] != None) and (PspDict['Size'] != None)):
        DirElmt = {}
        DirElmt ['Base'] = PspDict ['Base']
        DirElmt ['Size'] = PspDict ['Size']
        DirList.append (DirElmt)

  if (len(PspDicts) != 0):
    for PspDict in PspDicts:
      if (PspDict['HeaderBase'] != None):
        DirElmt = {}
        DirElmt ['Base'] = PspDict ['HeaderBase']
        DirElmt ['Size'] = DirHeaderSize
        DirList.append (DirElmt)

  for i in range (len (DirList)):
    for j in range (len (DirList)):
      #exclude Current index
      if (i != j):
        CurDirStart = DirList[i]['Base']
        CurDirEnd = DirList[i]['Base']+DirList[i]['Size'] - 1;
        OtherDirStart = DirList[j]['Base']
        OtherDirEnd = DirList[j]['Base']+DirList[j]['Size'] - 1;
        if (not((CurDirEnd < OtherDirStart) or (OtherDirEnd < CurDirStart))):
          log.info ("\nERROR: DIR [%x~%x] and DIR [%x~%x] region overlapped, please check PSP_DIR & BIOS_DIR \"Base\" & \"Size\" definition\n", CurDirStart, CurDirEnd, OtherDirStart, OtherDirEnd)
          FatalErrorExit ()

  return (PspDicts, BiosDicts, ComboDict)

def OptPspEntryOrder (PspDict):
# To be Done Optimize PSP entry Order
  return PspDict

def CalcEntryOffset (BiosSize, Directory):
  global DirHeaderSize
  global gAlignment
  Alignment = 0
  # Calculate the Entry offset for dynamic format configure file
  # Which Base and Size have been explicit define in the DIR Node(PSP_DIR or BIOS_DIR)
  if ((Directory['Base'] != None) and (Directory['Size'] != None)):
    #PSP Entry Start Address
    if (Directory['HeaderBase'] != None):
      BaseOffset = AlignAddress (Directory['Base'], gAlignment)
      EntryOffset = BaseOffset
    else:
      BaseOffset = AlignAddress (Directory['Base'] + DirHeaderSize, gAlignment)
      EntryOffset = BaseOffset
    #Validate all entries:
    for Entry in Directory['Entries']:
      #Image Entry should not have Address attribute
      if (IsImageEntry(Entry)):
        log.debug (Entry)
        if (Entry['Address'] != None ):
          log.info ("ERROR: Entry should not have Address attribute as the 'Base' & 'Size' have been defined in parameter node")
          FatalErrorExit ()
        if (Entry['Size'] == None):
          if (CheckFileExistance (Entry['File']) == False):
            log.info ("ERROR: Can't open %s", Entry['File'])
            FatalErrorExit ()
          #If Size has been specified it will override the actual file size
          EntrySize = os.path.getsize(Entry['File'])
          Entry['Size'] = EntrySize
        #Worker functions>>
        #Check if this entry is modifiable & SpiBlockSize is defined, using SpiBlockSize as Alignment, else using default Alignment
        if ((IsEntryModifiable (Entry['Type'])) and (Directory['SpiBlockSize'] != None)):
          Alignment = Directory['SpiBlockSize']
        else:
          Alignment = gAlignment
        #log.info("Before Align %x", EntryOffset)
        EntryOffset = AlignAddress (EntryOffset, Alignment)
        if (EntryOffset + Entry['Size'] > (BaseOffset + Directory['Size'])):
          log.info ("[Error] Exceed the limit of Dir Size 0x%xBytes\n", Directory['Size'])
          FatalErrorExit()
        #Record to structure
        Entry['Address'] = EntryOffset
        #Update to Next Entry offset
        EntryOffset += Entry['Size']
        #log.info("Type 0x%x Base %x Size %x", Entry['Type'], Entry['Address'], Entry['Size'])
    # Result
    UsedSize = EntryOffset - BaseOffset
    log.info("PSP FV 0x%x bytes used, 0x%x bytes free [%.2f%% full]" ,UsedSize, (Directory['Size'] -  UsedSize), float (UsedSize)/float (Directory['Size']) *100 )
  return Directory

def DumpPspDict (BiosSize, PspDict):
  for Entry in PspDict['Entries']:
    if (IsImageEntry(Entry) or IsPointEntry(Entry)):
      log.info ("%s 0x%02X 0x%08x 0x%08x 0x%08x(R) (%s)", Entry['Entry'], Entry['Type'], Entry['Size'], Entry['Address'], Entry['Address'], getEntryName(Entry['Type']))
    elif (IsValueEntry(Entry)):
      log.info ("%s 0x%02X 0x%08x (%s)", Entry['Entry'], Entry['Type'], Entry['Value'], getEntryName(Entry['Type']))

def DumpBiosDict (BiosSize, BiosDict):
  for Entry in BiosDict['Entries']:
    if (IsImageEntry(Entry) or IsPointEntry(Entry)):
      log.info ("%s Type[%02X] RegionType[%02X] Reset[%01x] Copy[%01x] RO[%01x] ZIP[%01x] 0x%08x 0x%08x 0x%08x(R) 0x%x (%s)",Entry['Entry'], Entry['Type'],Entry['RegionType'],Entry['ResetImage'],Entry['Copy'],Entry['ReadOnly'], Entry['Compressed'], Entry['Size'], Entry['Address'],  Entry['Address'], Entry['Destination'], getEntryName(Entry['Type']))
    elif (IsValueEntry(Entry)):
      log.info ("%s 0x%02X 0x%08x (%s)", Entry['Entry'], Entry['Type'], Entry['Value'], getEntryName(Entry['Type']))

def BuildPspDir (BiosSize, PspDict):
  global AddressMode
  PspEntry=""
  PspEntryFmt = 'I I Q'
  PspEntrySize = struct.calcsize(PspEntryFmt)
  # Process each PSP entry
  for Entry in PspDict['Entries']:
    # typedef struct {
    #   UINT32 Type:8 ;          ///< Type of PSP Directory entry
    #   UINT32 SubProgram:8;       ///< Specify the SubProgram
    #   UINT32 RomId:2;            ///< Specify the ROM ID
    #   UINT32 Reserved:20;        ///< Reserved
    # } PSP_DIRECTORY_ENTRY_TYPE;
    TypeAttrib = (Entry['Type'] + (Entry['RomId'] << 16))
    if (IsImageEntry(Entry) or IsPointEntry(Entry)):
      if (AddressMode == 0) :
        EntryData = (TypeAttrib, Entry['Size'], getMmioAddress (BiosSize, Entry['Address']))
      elif (AddressMode == 1):
        EntryData = (TypeAttrib, Entry['Size'], Entry['Address'])
    elif (IsValueEntry(Entry)):
      # Size field always be 0xFFFFFFFF for Value 
      EntryData = (Entry['Type'], 0xFFFFFFFF, Entry['Value'])
    s = struct.Struct(PspEntryFmt)
    #Pack Type
    PspEntry += s.pack(*EntryData)

  s = struct.Struct('I I')

  if (PspDict['Base'] != None and PspDict['Size'] != None):
    # Put PspDict['Size'] to the reserved field for Binary level replacement usage
    # [0:9] Directory Size in 4K bytes, Max:1K * 4K = 4M
    # [10:13] SpiBlockSize, Max: 16 * 4K = 64K
    # [14:28] Base, [26:12] of Base address, Max support to 64M address
    Rsvd =  ((PspDict['Size'] >> 12) << 0)
    if (PspDict['SpiBlockSize'] != None):
      Rsvd +=  ((PspDict['SpiBlockSize'] >> 12) << 10)
    if (PspDict['HeaderBase'] != None):
      Rsvd += ((PspDict['Base'] >> 12) << 14)
  else:
    Rsvd =  0
  values = (len (PspEntry)/PspEntrySize , Rsvd)
  CrcList = s.pack(*values) + PspEntry
  crc = Fletcher32Crc (CrcList, len (CrcList)/2)
  if (PspDict["Level"] == 1):
    Signature = "$PSP"
  elif (PspDict["Level"] == 2):
    Signature = "$PL2"
  else:
    log.info ("Unsupported Level detected.")
    FatalErrorExit ()
    
  values = (Signature, crc, len (PspEntry)/PspEntrySize , Rsvd)
  s = struct.Struct('4s I I I')
  PspHeader = s.pack(*values)
  PspDir = PspHeader+PspEntry
  return PspDir

def BuildBiosDir (BiosSize, BiosDict):
  BiosEntry=""
  BiosEntryFmt = 'I I Q Q'
  BiosEntrySize = struct.calcsize(BiosEntryFmt)
  MmioAddress = 0
  # Process each PSP entry
  for Entry in BiosDict['Entries']:
    if (IsImageEntry(Entry) or IsPointEntry(Entry)):
      # typedef struct {
      #   UINT32 Type : 8 ;          ///< Type of BIOS entry
      #   UINT32 RegionType : 8;     ///< 0 Normal memory, 1 TA1 memory, 2 TA2 memor
      #   UINT32 BiosResetImage: 1;  ///< Set for SEC or EL3 fw, which will be authenticate by PSP FW known as HVB
      #   UINT32 Copy: 1;            ///< Copy: 1- copy BIOS image image from source to destination 0- Set region attribute based on <ReadOnly, Source, size> attributes
      #   UINT32 ReadOnly : 1;       ///< 1: Set region to read-only (applicable for ARM- TA1/TA2) 0: Set region to read/write
      #   UINT32 Compressed : 1;     ///< 1: Compresed
      #   UINT32 Instance : 4;       ///< Specify the Instance of an entry
      #   UINT32 SubProgram : 3;       ///< Specify the SubProgram
      #   UINT32 RomId:2;           ///< Specify the RomId
      #   UINT32 Reserved : 3;      ///< Reserve for future use
      # } TYPE_ATTRIB;
      TypeAttrib = (Entry['Type'] + (Entry['RegionType'] << 8) + (Entry['ResetImage'] << 16)\
                   + (Entry['Copy'] << 17) + (Entry['ReadOnly'] <<18) + (Entry['Compressed'] <<19) + (Entry['Instance'] <<20) + (Entry['SubProgram'] << 24) + (Entry['RomId'] << 27))
      if (AddressMode == 0) :
        # Always Set Source to 0 for APOB entry
        if (Entry['Type'] == 0x61):
          MmioAddress = 0
        else:
          MmioAddress = getMmioAddress (BiosSize, Entry['Address'])
        EntryData = (TypeAttrib, Entry['Size'], MmioAddress, Entry['Destination'])
      elif (AddressMode == 1):
        EntryData = (TypeAttrib, Entry['Size'], Entry['Address'], Entry['Destination'])
    elif (IsValueEntry(Entry)):
      # Size field always be 0xFFFFFFFF for Value 
      EntryData = (Entry['Type'], 0xFFFFFFFF, Entry['Value'], Entry['Destination'])
    s = struct.Struct(BiosEntryFmt)
    #Pack Type
    BiosEntry += s.pack(*EntryData)

  s = struct.Struct('I I')
  if (BiosDict['Base'] != None and BiosDict['Size'] != None):
    # Put BiosDict['Size'] to the reserved field for Binary level replacement usage
    # [0:9] Directory Size in 4K bytes, Max:1K * 4K = 4M
    # [10:13] SpiBlockSize, Max: 16 * 4K = 64K
    # [14:28] Base, [26:12] of Base address, Max support to 64M address
    Rsvd =  ((BiosDict['Size'] >> 12) << 0)
    if (BiosDict['SpiBlockSize'] != None):
      Rsvd +=  ((BiosDict['SpiBlockSize'] >> 12) << 10)
    if (BiosDict['HeaderBase'] != None):
      Rsvd += ((BiosDict['Base'] >> 12) << 14)
  else:
    Rsvd =  0
  values = (len (BiosEntry)/BiosEntrySize , Rsvd)
  CrcList = s.pack(*values) + BiosEntry
  crc = Fletcher32Crc (CrcList, len (CrcList)/2)
  if (BiosDict["Level"] == 1):
    Signature = "$BHD"
  elif (BiosDict["Level"] == 2):
    Signature = "$BL2"
  else:
    log.info ("Unsupport Level detected.")
    FatalErrorExit ()
  values = (Signature, crc, len (BiosEntry)/BiosEntrySize , Rsvd)
  s = struct.Struct('4s I I I')
  BiosHeader = s.pack(*values)
  BiosDir = BiosHeader+BiosEntry
  return BiosDir

def BuildComboDir (BiosSize, ComboDict):
  global AddressMode
  ComboEntry=""
  ComboEntryFmt = 'I I Q'
  ComboEntrySize = struct.calcsize(ComboEntryFmt)
  # Process each Combo entry
  for Entry in ComboDict['Entries']:
    if (AddressMode == 0) :
      EntryData = (Entry['IdSelect'], Entry['Id'], getMmioAddress (BiosSize, Entry['Address']))
    elif (AddressMode == 1):
      EntryData = (Entry['IdSelect'], Entry['Id'], Entry['Address'])
    s = struct.Struct(ComboEntryFmt)
    #Pack Type
    ComboEntry += s.pack(*EntryData)

  s = struct.Struct('I I 4I')
  LookUpMode =  ComboDict['LookUpMode']
  values = (len (ComboEntry)/ComboEntrySize , LookUpMode, 0, 0, 0, 0)
  CrcList = s.pack(*values) + ComboEntry
  crc = Fletcher32Crc (CrcList, len (CrcList)/2)
  values = ("2PSP", crc, len (ComboEntry)/ComboEntrySize , LookUpMode, 0, 0, 0, 0)
  s = struct.Struct('4s I I I 4I')
  ComboHeader = s.pack(*values)
  ComboDir = ComboHeader+ComboEntry
  return ComboDir

def GetBiosTypeAttribs (TypeAttrib):
  Type = (TypeAttrib & 0xFF) >> 0
  RegionType = (TypeAttrib & 0xFF00) >> 8
  Reset = (TypeAttrib & 0x10000) >> 16
  Copy = (TypeAttrib & 0x20000) >> 17
  ReadOnly = (TypeAttrib & 0x40000) >> 18
  Compressed = (TypeAttrib & 0x80000) >> 19
  Instance = (TypeAttrib & 0xF00000) >> 20
  SubProgram = (TypeAttrib & 0x7000000) >> 24
  RomId = (TypeAttrib & 0x18000000) >> 27
  return (Type, RegionType, Reset, Copy, ReadOnly, Compressed, Instance, SubProgram, RomId)

def ParsePspDirBin (FileHandle, BinarySize, PspDirOffSetInBin, Level, PspDirectoryInfos):
  BiosDirOffset = 0
  BiosDirRawSize = 0
  #Verify PSP Directory blob
  #read Psp Header
  PspDirectoryInfo = {}
  PspDirectoryInfos.append (PspDirectoryInfo)
  FileHandle.seek (AddrGlobalXorBit24 (PspDirOffSetInBin))
  PspDirTblRaw = FileHandle.read (16)
  (Signature, Checksum, NumEntries, Rsvd) = struct.unpack('4L',PspDirTblRaw)
  # [0:9] Directory Size in 4K bytes, Max:1K * 4K = 4M
  # [10:13] SpiBlockSize, Max: 16 * 4K = 64K
  # [14:28] Base, [26:12] of Base address, Max support to 64M address
  PspDirSize = ((Rsvd & 0x3FF) >> 0) << 12
  SpiBlockSize = ((Rsvd & 0x3C00) >> 10) << 12
  BaseOffset = ((Rsvd & 0x1FFFC000) >> 14) << 12
  PspDirectoryInfo ['DirSize'] = PspDirSize
  PspDirectoryInfo ['DirOffset'] = PspDirOffSetInBin
  PspDirectoryInfo ['SpiBlockSize'] = SpiBlockSize
  PspDirectoryInfo ['BaseOffset'] = BaseOffset
  PspDirectoryInfo ['Level'] = Level
  
  log.info ("Psp Directory Header Offset 0x%x Base offset 0x%x FV Size 0x%X SpiBlockSize 0x%X" ,PspDirOffSetInBin, BaseOffset, PspDirSize, SpiBlockSize)

  #Check Signature
  if ((Signature != PSP_DIR_SIGNATURE) and (Signature != PSP_LEVEL2_DIR_SIGNATURE)):
    log.info ("Psp Directory Table Signature Verify Fail")
    FatalErrorExit ()
  #To be Done Check CRC Checksum

  #Render & build structure
  #Read the whole Dir Table
  EntryInfoArray = []
  PreAddressMode  = 0xFFFF  #Init value
  for i in range (NumEntries):
    EntryRaw = FileHandle.read (16)
    (TypeAttrib, Size, Location) = struct.unpack ('LLQ', EntryRaw)
    Type = (TypeAttrib & 0xFF) >> 0
    Type16 = TypeAttrib & 0xFFFF
    RomId = (TypeAttrib & 0x30000) >> 16

    if (Size != 0xFFFFFFFF):
      # Type16 specify the 1st 16 bits of Type filed, while Type only specify the lowest 8bits of Type field
      log.info ("Type16 [0x%X] Type [0x%02X] RomId[0x%01X] Size [0x%08X] Location [0x%08X ~ 0x%08X] (%s)",  Type16, Type, RomId, Size,Location, Location + Size -1, getEntryName(Type))
      if (Location & 0xF0000000):
        PspDirEntryAddress = getOffsetInBin(BinarySize, Location)
        PspDirEntryAddressMode = 0
      else:
        PspDirEntryAddress = Location
        PspDirEntryAddressMode = 1
      #Verify if addressmode is aligned between  
      if ((PreAddressMode != 0xFFFF) and (PreAddressMode != PspDirEntryAddressMode)):
        log.info ("Error: Address mode is not aligned between Entries\n")
        FatalErrorExit ()
      PreAddressMode = PspDirEntryAddressMode

      EntryInfo = {'Type16':Type16,'Type':Type, 'RomId':RomId,'Size':Size,'RTOffset':Location, 'Description':getEntryName(Type & 0xFF), 'Address':PspDirEntryAddress, 'XorAddr':AddrGlobalXorBit24 (PspDirEntryAddress)}
      #Update the Description filed with subprogram information, if upper bits of Type filed is non-zero
      if (EntryInfo['Type16'] & 0xFF00):
        EntryInfo['Description'] = EntryInfo['Description'] + " (RV2,PiR,CF)"
      # Check if it the entry point 2nd level DIR
      if (EntryInfo['Type'] == PSP_ENTRY_TYPE_LEVEL2_DIR):
        log.info ("2nd PSP DIR found\n")
        #It is the entry point level 2 directory
        ParsePspDirBin (FileHandle, BinarySize, EntryInfo["Address"], 2, PspDirectoryInfos)
      EntryInfo['Entry'] = getEntryType(PspDirectoryInfo, EntryInfo)
      # Found a unknown type, set it to IMAGE_ENTRY to allow replace the unknown type
      if (EntryInfo['Entry'] == "UNKNOWN_ENTRY"):
        EntryInfo['Entry'] = "IMAGE_ENTRY"
      #Only given File attribute for IMAGE_ENTRY
      if (GetOutEntryFileName (EntryInfo, "PspDir", Level) != "Unsupported"):
        EntryInfo ['File'] = GetOutEntryFileName (EntryInfo, "PspDir", Level)
    else:
      log.info ("Type [0x%02X] VALUE [0x%08X] (%s)",  Type, Location, getEntryName(Type))
      #Ignore Size in Value entry
      EntryInfo = {'Type':Type,'Entry':'VALUE_ENTRY','Value':Location, 'Description':getEntryName(Type)}
    EntryInfoArray.append (EntryInfo)
  PspDirectoryInfo ['AddressMode'] = PspDirEntryAddressMode
  PspDirectoryInfo['Entries'] = EntryInfoArray


def ParseBiosDirBin (FileHandle, BinarySize, BiosDirOffset, Level, BiosDirectoryInfos):
  '''
      Build BIOS Dir structure
  '''
  BiosFwId = 0
  BiosDirectoryInfo = {}
  BiosDirectoryInfos.append (BiosDirectoryInfo)
  FileHandle.seek (AddrGlobalXorBit24 (BiosDirOffset))
  BiosDirTblRaw = FileHandle.read (16)
  (Signature, Checksum, NumEntries, Rsvd) = struct.unpack('4L',BiosDirTblRaw)
  # [0:9] Directory Size in 4K bytes, Max:1K * 4K = 4M
  # [10:13] SpiBlockSize, Max: 16 * 4K = 64K
  # [14:28] Base, [26:12] of Base address, Max support to 64M address
  BiosDirSize = ((Rsvd & 0x3FF) >> 0) << 12
  SpiBlockSize = ((Rsvd & 0x3C00) >> 10) << 12
  BaseOffset = ((Rsvd & 0x1FFFC000) >> 14) << 12
  BiosDirectoryInfo ['DirOffset'] = BiosDirOffset  
  BiosDirectoryInfo ['DirSize'] = BiosDirSize
  BiosDirectoryInfo ['SpiBlockSize'] = SpiBlockSize
  BiosDirectoryInfo ['BaseOffset'] = BaseOffset
  BiosDirectoryInfo ['Level'] = Level
  log.info ("BIOS Directory Header Offset 0x%x Base offset 0x%x Size 0x%X SpiBlockSize 0x%X" ,BiosDirOffset, BaseOffset, BiosDirSize, SpiBlockSize)
  #Check Signature
  if ((Signature != BIOS_DIR_SIGNATURE) and (Signature != BIOS_LEVEL2_DIR_SIGNATURE)):
    log.info ("BIOS Directory Table Signature Verify Fail")
    FatalErrorExit ()

  EntryInfoArray = []
  PreAddressMode  = 0xFFFF  #Init value
  FileNameDict = {}
  FileName = ''
  for i in range (NumEntries):
    EntryRaw = FileHandle.read (24)
    (TypeAttrib, Size, Location, Destination) = struct.unpack ('LLQQ', EntryRaw)
    if (Size != 0xFFFFFFFF):
      (Type, RegionType, ResetImage, Copy, ReadOnly, Compressed, Instance, SubProgram, RomId)= GetBiosTypeAttribs (TypeAttrib)
      log.info ("Type[%02X] RomId[%02X] SubProgram[%02x] Instance[%02X] RegionType[%02X] Reset[%01x] Copy[%01x] RO[%01x] ZIP[%01x]\n>>Size [0x%08X] Source [0x%08X ~ 0x%08X] Dest[0x%08x] (%s)",\
      Type, RomId, SubProgram, Instance, RegionType, ResetImage, Copy, ReadOnly, Compressed,\
      Size, Location, Location + Size -1, Destination, getEntryName(Type))

      if (Location & 0xF0000000):
        BiosDirEntryAddress = getOffsetInBin(BinarySize, Location)
        BiosDirEntryAddressMode = 0
      elif (Location == 0):
        # Ignore mode check for APOB
        BiosDirEntryAddressMode = PreAddressMode
      else:
        BiosDirEntryAddress = Location
        BiosDirEntryAddressMode = 1
      

      #Verify if addressmode is aligned between  
      if ((PreAddressMode != 0xFFFF) and (PreAddressMode != BiosDirEntryAddressMode)):
        log.info ("Error: Address mode is not aligned between Entries\n")
        FatalErrorExit ()
      PreAddressMode = BiosDirEntryAddressMode

      EntryInfo = {'Type':Type, 'RomId':RomId, 'SubProgram':SubProgram, 'Instance':Instance, 'RegionType':RegionType, 'ResetImage':ResetImage, 'Copy': Copy, 'ReadOnly': ReadOnly, 'Compressed':Compressed, \
      'Size':Size,'RTOffset':Location, 'Description':getEntryName(Type), \
      'Address':BiosDirEntryAddress, 'Destination':Destination, 'XorAddr': AddrGlobalXorBit24 (BiosDirEntryAddress)}
      EntryInfo['Entry'] = getEntryType(BiosDirectoryInfo, EntryInfo);
      # Check if it the entry point 2nd level DIR
      if (EntryInfo['Type'] == BIOS_ENTRY_TYPE_LEVEL2_DIR):
        log.info ("2nd BIOS DIR found\n")
        #It is the entry point level 2 directory
        ParseBiosDirBin (FileHandle, BinarySize, EntryInfo["Address"], 2, BiosDirectoryInfos)
      # Found a unknown type, set it to IMAGE_ENTRY to allow replace the unknown type
      if (EntryInfo['Entry'] == "UNKNOWN_ENTRY"):
        EntryInfo['Entry'] = "IMAGE_ENTRY"
      #Only given File attribute for IMAGE_ENTRY
      if (GetOutEntryFileBaseName (EntryInfo, "BiosDir", Level) != "Unsupported"):
        FileName = GetOutEntryFileBaseName (EntryInfo, "BiosDir", Level)
        #Check if duplicated file name
        if (FileName in FileNameDict):
          FileIndex = FileNameDict[FileName]
          FileNameDict[FileName] += 1
          FileName += ("_" + "%d"%FileIndex)
        else:
          FileNameDict[FileName] = 1
        #add file surfix
        EntryInfo ['File'] = FileName + ".bin"
        
      #Always return physical address for APOB, and should be ZERO
      if (EntryInfo['Type'] == 0x61):
        EntryInfo['Address'] = getOffsetInBin(0, Location)
    else:
      log.info ("Type [0x%02X] VALUE [0x%08X] (%s)",  Type, Location, getEntryName(Type))
      #Ignore size,Destination in Value entry
      EntryInfo = {'Type':Type, 'Entry':'VALUE_ENTRY','Value':Location, 'Description':getEntryName(Type)}

    EntryInfoArray.append (EntryInfo)
  BiosDirectoryInfo ['AddressMode'] = BiosDirEntryAddressMode
  BiosDirectoryInfo['Entries'] = EntryInfoArray

def GetPspDirectory (BinaryFile):
  global AddressMode
  global ProgramTable
  global ProgramStr
  global gXorBit24
  PspDirectoryInfos = []
  BiosDirectoryInfos = []
  BinaryInfo = {}
  try:
    FileHandle = open (BinaryFile,'rb')
  except:
    log.info ("Error: Opening ", BinaryFile)
    FatalErrorExit ()
  #read whole binary to buffer
  FileHandle.seek (0)
  BinarySize = os.path.getsize(BinaryFile)
  BinaryInfo ['Binary'] = FileHandle.read (BinarySize)
  BinaryInfo ['BinaryName'] = BinaryFile
  BinaryInfo ['BinarySize'] = BinarySize

  ######################################
  # 1st try the Traditional ROMSIG way
  ######################################
  # Check Signature
  # log.info ("2 try the Traditional ROMSIG way")

  #
  gXorBit24 = 0
  for i in range(2):
    # Try upper 16M if can't find in low 16M
    if (i == 1):
      gXorBit24 = 1
    for RomSigOffset in RomSigAddrTable:
      RomSigOffset = AddrGlobalXorBit24 (RomSigOffset)
      if (RomSigOffset > BinarySize):
        continue
      log.info ("Check ROMSIG @ 0x%X" ,RomSigOffset)
      FileHandle.seek (RomSigOffset)
      OemSigRaw = FileHandle.read (0x30)
      OemSigArray = struct.unpack ('12L',OemSigRaw)
      #Check OEM signature, ang get Psp Directory offset
      if (OemSigArray[ROMSIG_SIG_OFFSET] == 0x55aa55aa):
        log.info ("Oem Sig Table Found")
        # if the EFI gen match the program
        if BinarySize > 0x1000000:
          if ((OemSigArray[SECOND_GEN_EFS_OFFSET] & 0x1) != ProgramTable[ProgramStr]["SECOND_GEN_EFS"] ):
            log.info ("SECOND_GEN_EFS %x not match %x continue search", (OemSigArray[SECOND_GEN_EFS_OFFSET] & 0x1) , ProgramTable[ProgramStr]["SECOND_GEN_EFS"])
            continue
        PspDirOffset = OemSigArray[ROMSIG_PSPDIR_OFFSET]
        log.info ("Psp Directory Offset 0x%X" ,PspDirOffset)
        #convert to raw binary offset
        PspDirAddressMode = 1
        if (PspDirOffset & 0xF0000000):
          # Check if Pysical MMIO address or binary offset
          PspDirOffset = getOffsetInBin (BinarySize, PspDirOffset)
          PspDirAddressMode = 0
        else:
          PspDirOffset = PspDirOffset

        log.info ("Psp Directory Offset in binary 0x%X" ,PspDirOffset)
        FileHandle.seek (AddrGlobalXorBit24 (PspDirOffset))
        PspDirTblRaw = FileHandle.read (16)
        (Signature, Checksum, NumEntries, PspDirSize) = struct.unpack('4L',PspDirTblRaw)
        if (Signature == PSP_DIR_SIGNATURE):
          log.info ("PSP Directory Found")
          #We found a Valid PSP Directory Header through ROM SIG
          ParsePspDirBin (FileHandle, BinarySize, PspDirOffset, 1, PspDirectoryInfos)
          BiosDirOffset = OemSigArray[ProgramTable[ProgramStr]["BIOSDIR_OFFSET"]]
          if (BiosDirOffset != 0):
            log.info ("BIOS Directory Offset found at ROMSIG[%x]0x%X" ,ProgramTable[ProgramStr]["BIOSDIR_OFFSET"], BiosDirOffset)
            BiosDirAddressMode = 1
            #convert to raw binary offset
            if (BiosDirOffset & 0xF0000000):
              # Check if Pysical MMIO address or binary offset
              BiosDirOffset = getOffsetInBin (BinarySize, BiosDirOffset)
              BiosDirAddressMode = 0
            else:
              BiosDirOffset =  BiosDirOffset

            ParseBiosDirBin (FileHandle, BinarySize, BiosDirOffset, 1, BiosDirectoryInfos)
            #######################################################
            # Verify to make sure all element use same addressmode
            #######################################################
            PreEntryAddressMode = 0xFFFF
            for PspDirectoryInfo in PspDirectoryInfos:
              PspDirEntryAddressMode = PspDirectoryInfo['AddressMode']
              if ((PreEntryAddressMode != 0xFFFF) and (PreEntryAddressMode != PspDirEntryAddressMode)):
                log.info ("Error: Address mode is not aligned between PSP Directories\n")
                FatalErrorExit ()
              PreEntryAddressMode = PspDirectoryInfo['AddressMode']

            PreEntryAddressMode = 0xFFFF                
            for BiosDirectoryInfo in BiosDirectoryInfos:
              BiosDirEntryAddressMode = BiosDirectoryInfo['AddressMode']
              if ((PreEntryAddressMode != 0xFFFF) and (PreEntryAddressMode != BiosDirEntryAddressMode)):
                log.info ("Error: Address mode is not aligned between Bios Directories\n")
                FatalErrorExit ()
              PreEntryAddressMode = BiosDirectoryInfo['AddressMode']

            if ((PspDirAddressMode == BiosDirAddressMode) and (BiosDirAddressMode == PspDirEntryAddressMode) and (PspDirEntryAddressMode == BiosDirEntryAddressMode)):
              AddressMode = PspDirAddressMode
            else:
              log.info ("Error: Address mode is not aligned between EFS/ROMSIG & Bios Directories\n")
              FatalErrorExit ()
          return (BinaryInfo, PspDirectoryInfos, BiosDirectoryInfos)
        elif (Signature == PSP_COMBO_SIGNATURE):
          log.info ("PSP Combo Directory Found")
          #loop the PSP Combo Directory to found entry for specific program
          FileHandle.seek (AddrGlobalXorBit24 (PspDirOffset))
          PspDirTblRaw = FileHandle.read (16)
          (Signature, Checksum, NumEntries, LookUpMode) = struct.unpack('4L',PspDirTblRaw)
          #Ignore 16 bytes reserved
          FileHandle.read (16)
          for i in range (NumEntries):
            EntryRaw = FileHandle.read (16)
            (IdSelect, Id, PspDirOffset) = struct.unpack ('LLQ', EntryRaw)
            #convert to raw binary offset
            PspDirAddressMode = 1
            if (PspDirOffset & 0xF0000000):
              # Check if Pysical MMIO address or binary offset
              PspDirOffset = getOffsetInBin (BinarySize, PspDirOffset)
              PspDirAddressMode = 0
            else:
              PspDirOffset = PspDirOffset
  
            #Check if match the input program
            if ((ProgramTable[ProgramStr]["PSPID"] & ProgramTable[ProgramStr]["AndMask"]) == (Id & ProgramTable[ProgramStr]["AndMask"])):
              EntryFound = 1
              break

          if (EntryFound):
            log.info ("PSP Directory for %s Found @ %x", ProgramStr, PspDirOffset)
            ParsePspDirBin (FileHandle, BinarySize, PspDirOffset, 1, PspDirectoryInfos)
            BiosDirOffset = OemSigArray[ProgramTable[ProgramStr]["BIOSDIR_OFFSET"]]
            if (BiosDirOffset != 0):
              log.info ("BIOS Directory Offset found at ROMSIG[%x]0x%X" ,ProgramTable[ProgramStr]["BIOSDIR_OFFSET"], BiosDirOffset)
              BiosDirAddressMode = 1
              #convert to raw binary offset
              if (BiosDirOffset & 0xF0000000):
                # Check if Pysical MMIO address or binary offset
                BiosDirOffset = getOffsetInBin (BinarySize, BiosDirOffset)
                BiosDirAddressMode = 0
              else:
                BiosDirOffset = BiosDirOffset

              ParseBiosDirBin (FileHandle, BinarySize, BiosDirOffset, 1, BiosDirectoryInfos)

              #######################################################
              # Verify to make sure all element use same addressmode
              #######################################################
              PreEntryAddressMode = 0xFFFF
              for PspDirectoryInfo in PspDirectoryInfos:
                PspDirEntryAddressMode = PspDirectoryInfo['AddressMode']
                if ((PreEntryAddressMode != 0xFFFF) and (PreEntryAddressMode != PspDirEntryAddressMode)):
                  log.info ("Error: Address mode is not aligned between PSP Directories\n")
                  FatalErrorExit ()
                PreEntryAddressMode = PspDirectoryInfo['AddressMode']

              PreEntryAddressMode = 0xFFFF                
              for BiosDirectoryInfo in BiosDirectoryInfos:
                BiosDirEntryAddressMode = BiosDirectoryInfo['AddressMode']
                if ((PreEntryAddressMode != 0xFFFF) and (PreEntryAddressMode != BiosDirEntryAddressMode)):
                  log.info ("Error: Address mode is not aligned between Bios Directories\n")
                  FatalErrorExit ()
                PreEntryAddressMode = BiosDirectoryInfo['AddressMode']

              if ((PspDirAddressMode == BiosDirAddressMode) and (BiosDirAddressMode == PspDirEntryAddressMode) and (PspDirEntryAddressMode == BiosDirEntryAddressMode)):
                AddressMode = PspDirAddressMode
              else:
                log.info ("Error: Address mode is not aligned between EFS_PSP_Dir %x,EFS_BIOS_Dir %x,PSP Directories %x, BIOS Directories %x\n", PspDirAddressMode, BiosDirAddressMode, PspDirEntryAddressMode, BiosDirEntryAddressMode)
                FatalErrorExit ()
            return (BinaryInfo, PspDirectoryInfos, BiosDirectoryInfos)

    # else:
    #   #When we go here, it is neither a PSP eMMC image nor a SPI image
    #   #Will try to search the "$BHD" signature with 0x100 boundary 
    #   ######################################
    #   # Last check if eMMC BIOS Image $BHD
    #   ######################################
    #   log.info ("3 Check if eMMC BIOS Image")
    #   FileHandle.seek (0x0)
    #   while True:
    #     Buf = FileHandle.read (0x100)
    #     if len(Buf) == 0:
    #       #End of file
    #       break;
    #     (Signature,) = struct.unpack ('L',Buf[:4])
    #     if (Signature == 0x44484224):
    #       #compare to "$BHD"
    #       log.info ("eMMC BIOS Image identified")
    #       AddressMode = 1
    #       BiosDirOffset = FileHandle.tell () - 0x100
    #       (BiosDirectoryInfo) = ParseBiosDirBin (FileHandle, 0, BiosDirOffset)
    #       return (BinaryInfo, PspDirectoryInfo, BiosDirectoryInfo)

    #   print "Unrecognized Binary\n"
      # FatalErrorExit ()
  # # Check BIOS SPI Image layout Or PSP SPI image layout
  # ######################################
  # # 2nd check if  PSP Image  # $PSP
  # ######################################
  FileHandle.seek (0)
  PspDirTblRaw = FileHandle.read (16)
  (Signature, Checksum, NumEntries, PspDirSize) = struct.unpack('4L',PspDirTblRaw)
  log.info ("2 check if PSP Image")  
  if (Signature == PSP_DIR_SIGNATURE):
    # Parse PSP DIR Header
    # Binary Size set 0, implies it is eMMC image, no need to do the address translation
    log.info ("PSP Image identified")
    AddressMode = 1
    ParsePspDirBin (FileHandle, 0, 0, 1, PspDirectoryInfos)
    return (BinaryInfo, PspDirectoryInfos, BiosDirectoryInfos)

def OutPutPspBinaries (bios,Entries):
  for Entry in Entries:
    if (GetOutEntryFileBaseName (Entry, "PspDir", 0) != "Unsupported"):
      outputFileName = Entry['File']
      #slice the binary
      print "Output %s of BIOS [%x:%x]" %(outputFileName, Entry['XorAddr'], Entry['XorAddr'] + Entry ['Size'] - 1)
      buffer = bios [Entry['XorAddr']: Entry['XorAddr'] + Entry ['Size']]
      WriteBinaryFile (outputFileName, buffer)

def OutPutBiosBinaries (bios,Entries):
  for Entry in Entries:
    if (GetOutEntryFileBaseName (Entry, "BiosDir", 0) != "Unsupported"):
      outputFileName =  Entry['File']
      #slice the binary
      print "Output %s of BIOS [%x:%x]" %(outputFileName, Entry['XorAddr'], Entry['XorAddr'] + Entry ['Size'] - 1)
      buffer = bios [Entry['XorAddr']: Entry['XorAddr'] + Entry ['Size']]
      WriteBinaryFile (outputFileName, buffer)

def pspBootLoaderInfo (bios, entry):
  pspBLHeaderSize = 0x100
  verOffset = 0x60
  pspBLInfo = {}
  pspBLHeader = bios [entry['XorAddr']:entry['XorAddr']+pspBLHeaderSize]
  pspVer = struct.unpack ('L',pspBLHeader[verOffset:verOffset+4])
  verStr ="%X.%X.%X.%X" %(((pspVer[0] & 0xFF000000)>>24), ((pspVer[0] & 0xFF0000) >> 16),((pspVer[0] & 0xFF00) >> 8), ((pspVer[0] & 0xFF) >> 0))
  pspBLInfo['Version'] = verStr
  return pspBLInfo


def pspSecureOsInfo (bios, entry):
  pspOSHeaderSize = 0x100
  verOffset = 0x60
  pspOSInfo = {}
  pspOSHeader = bios [entry['XorAddr']:entry['XorAddr']+pspOSHeaderSize]
  pspVer = struct.unpack ('L',pspOSHeader[verOffset:verOffset+4])
  verStr ="%X.%X.%X.%X" %(((pspVer[0] & 0xFF000000)>>24), ((pspVer[0] & 0xFF0000) >> 16),((pspVer[0] & 0xFF00) >> 8), ((pspVer[0] & 0xFF) >> 0))
  pspOSInfo['Version'] = verStr
  return pspOSInfo

def KvmInfo (bios, entry):
  KvmHeaderSize = 0x100
  verOffset = 0x60
  KvmInfo = {}
  KvmHeader = bios [entry['XorAddr']:entry['XorAddr']+KvmHeaderSize]
  KvmVer = struct.unpack ('L',KvmHeader[verOffset:verOffset+4])
  verStr ="%d.%d.%d" %(((KvmVer[0] & 0xFF) >> 0), ((KvmVer[0] & 0xFF00) >> 8), ((KvmVer[0] & 0xFFFF0000) >> 16), )
  KvmInfo['Version'] = verStr
  return KvmInfo

def smuFwInfo (bios, entry):
  SmuHeaderSize = 0x100
  verOffset = 0x0
  SmuInfo = {}
  SmuHeader = bios [entry['XorAddr']:entry['XorAddr']+SmuHeaderSize]
  SmuBin_00 = struct.unpack ('L',SmuHeader[0x60:0x60+4])
  # Check if it is old SMU version format, ZP, PR
  if ((SmuBin_00[0x0] & 0x00FF0000) == 0x190000) or ((SmuBin_00[0x0] & 0x00FF0000) == 0x2B0000):
    verOffset = 0x60

  SmuVer = struct.unpack ('L',SmuHeader[verOffset:verOffset+4])
  # Check the format x.x.x.x or X.X.X
  if (SmuVer[0] & 0xFF000000):
    # format x.x.x.x
    verStr ="%d.%d.%d.%d" %(((SmuVer[0] & 0xFF000000)>>24), ((SmuVer[0] & 0x00FF0000)>>16), ((SmuVer[0] & 0xFF00) >> 8),((SmuVer[0] & 0x00FF) >> 0))
  else:
    # format x.x.x
    verStr ="%d.%d.%d" %(((SmuVer[0] & 0xFFFF0000)>>16), ((SmuVer[0] & 0xFF00) >> 8),((SmuVer[0] & 0x00FF) >> 0))
  SmuInfo['Version'] = verStr
  return SmuInfo

def ucodeInfo (bios, entry):
  HeaderSize = 0x30
  ucodeInfo = {}
  ucodeHeader = bios [entry['XorAddr']:entry['XorAddr']+HeaderSize]
  DateCode = struct.unpack ('L',ucodeHeader[0:4])
  PatchId = struct.unpack ('L',ucodeHeader[4:8])
  ProcessorRevisionID = struct.unpack ('H',ucodeHeader[24:26])
  ucodeInfo['DateCode'] = "%x/%x/%x" %(((DateCode[0] & 0xFF000000) >> 24),((DateCode[0] & 0xFF0000) >> 16), ((DateCode[0] & 0xFFFF) >> 0))
  ucodeInfo['PatchId'] = "%x" %(PatchId[0])
  ucodeInfo['EquivalentProcessorRevisionID'] = "%x" %(ProcessorRevisionID[0])
  return ucodeInfo

def ablInfo (bios, entry):
  ablHeaderSize = 0x100
  verOffset = 0x60
  ablInfo = {}
  ablHeader = bios [entry['XorAddr']:entry['XorAddr']+ablHeaderSize]
  ablVer = struct.unpack ('L',ablHeader[verOffset:verOffset+4])
  verStr ="%08x" %(ablVer[0])
  ablInfo['Version'] = verStr
  return ablInfo

def OutPutPspDirInfoXml (BinaryInfo, PspDirectoryInfos, BiosDirectoryInfos, xmlFileName):
  try:
    FileHandle = open (xmlFileName,'w')
  except:
    print "Error: Opening ", xmlFileName
    FatalErrorExit ()
  root = Element('Dirs')
  
  if (len (PspDirectoryInfos) != 0):
    for PspDirectoryInfo in PspDirectoryInfos:
      DirDict = {}
      DirDict ['Level'] = PspDirectoryInfo ['Level']
      DirDict = StringlizeDict (DirDict)
      PspDirElmt = SubElement(root, 'PspDirectory', DirDict)
      for entry in PspDirectoryInfo['Entries']:
        _entry = entry.copy()
        # Change _entry['Type'] value to ['Type16'], to void BVM change
        if 'Type16' in _entry:
          _entry['Type'] = entry['Type16']
        #convert all numberic type to string, for tostring function only accept string
        _entry = StringlizeDict (_entry)
        #Override the default if it has been defined
        if (entry['Type'] in PspDirectoryEntryName):
            EntryType = entry['Entry']
        #Get Entry type from PspDirectoryEntryName
        #                          Type:   DIR, Entry Type    ShortName    Full description
        #                            0x00: ['PSP' ,'IMAGE_ENTRY','AmdPubKey','AMD public Key', ],
        entryElmt = SubElement (PspDirElmt, EntryType, _entry)
        if (entry['Type'] == 1) or (entry['Type'] == 3):
          SubElement (entryElmt, 'Detail', pspBootLoaderInfo(BinaryInfo['Binary'], entry))
        elif (entry['Type'] == 2):
          SubElement (entryElmt, 'Detail', pspSecureOsInfo(BinaryInfo['Binary'], entry))
        elif (entry['Type'] == 8) or (entry['Type'] == 0x12):
          SubElement (entryElmt, 'Detail', smuFwInfo(BinaryInfo['Binary'], entry))
        elif ((entry['Type'] >= 0x30) and (entry['Type'] <= 0x37)):
          SubElement (entryElmt, 'Detail', ablInfo(BinaryInfo['Binary'], entry))
        elif (entry['Type'] == 0x29):
          SubElement (entryElmt, 'Detail', KvmInfo(BinaryInfo['Binary'], entry))          
        elif (entry['Type'] == 0xb):
          SubElement (entryElmt, 'Detail', {"Help":'''BIT0:PSP Secure Debug Control Flag (0-Disabled, 1-Enabled);\
           BIT4:Enable applying of Security Policy to unsecure ASIC;\
           BIT28:MP0 DPM Enable
           BIT29:Skip MP2 FW loading. 0: Load MP2 FW normally 1: Skip MP2 FW Loading'''})

  if (len (BiosDirectoryInfos) != 0):
    for BiosDirectoryInfo in BiosDirectoryInfos:
      DirDict = {}
      DirDict ['Level'] = BiosDirectoryInfo ['Level']
      DirDict = StringlizeDict (DirDict)
      BiosDirElmt = SubElement(root, 'BiosDirectory',DirDict)
      for entry in BiosDirectoryInfo['Entries']:
        _entry = entry.copy()
        #convert all numberic type to string, for tostring function only accept string
        _entry = StringlizeDict (_entry)
        #Override the default if it has been defined
        if (entry['Type'] in PspDirectoryEntryName):
            EntryType = entry['Entry']
        entryElmt = SubElement (BiosDirElmt, EntryType, _entry)
        if (entry['Type'] == 0x66):
          SubElement (entryElmt, 'Detail', ucodeInfo(BinaryInfo['Binary'], entry))

  print >>FileHandle, prettify(root)

def OutPutBiosDirectoryXml (root, BiosDirectoryInfo):
  DirDict = {}
  if (BiosDirectoryInfo ['BaseOffset'] != 0):
    DirDict ['HeaderBase'] = BiosDirectoryInfo ['DirOffset']
    DirDict ['Base'] = BiosDirectoryInfo ['BaseOffset']
  else:
    DirDict ['Base'] = BiosDirectoryInfo ['DirOffset']

  if (BiosDirectoryInfo ['DirSize'] != 0):
    DirDict ['Size'] = BiosDirectoryInfo ['DirSize']
  if (BiosDirectoryInfo ['SpiBlockSize'] != 0):
    DirDict ['SpiBlockSize'] = BiosDirectoryInfo ['SpiBlockSize']
  DirDict ['Level'] = BiosDirectoryInfo ['Level']
  DirDict = StringlizeDict (DirDict)
  DirElmt = SubElement (root, 'BIOS_DIR', DirDict)
  for entry in BiosDirectoryInfo['Entries']:
    EntryDict = {}
    if (IsValueEntry (entry)):
      EntryDict = dict ((k, entry[k]) for k in ['Type', 'Value'])
      EntryDict = StringlizeDict (EntryDict)
      SubElement (DirElmt, 'VALUE_ENTRY', EntryDict)
    elif (IsImageEntry(entry)):
      EntryDict['File'] = OutputPath + entry['File']
      EntryDict['Type'] = entry ['Type']
      #Prepare for the 'Size' & 'Address'
      #fill the Size, Address attributes when Dir Size is 0, which means
      #User disable the auto allocation function
      if (BiosDirectoryInfo ['DirSize'] == 0):
        EntryDict['Size'] = entry ['Size']
        EntryDict['Address'] = entry ['Address']
      #Prepare for the 'Destination'
      if (entry['Destination'] != 0xFFFFFFFFFFFFFFFF):
        EntryDict['Destination'] = entry ['Destination']
      #Fill the instance, if instance is not 0
      if (entry['Instance'] != 0):
        EntryDict['Instance'] = entry ['Instance']
      #Fill the SubProgram, if SubProgram is not 0
      if (entry['SubProgram'] != 0):
        EntryDict['SubProgram'] = entry ['SubProgram']
      #Fill the RomId, if RomId is not 0
      if (entry['RomId'] != 0):
        EntryDict['RomId'] = entry ['RomId']

      EntryDict = StringlizeDict (EntryDict)
      EntryElmt = SubElement (DirElmt, 'IMAGE_ENTRY', EntryDict)

      #Prepare for the TypeAttrib tag, if any below attributes in non-zero
      if (not ((entry['RegionType'] == 0) and\
          (entry['ResetImage'] == 0) and\
          (entry['Copy'] == 0) and\
          (entry['ReadOnly'] == 0) and\
          (entry['Compressed'] == 0))):
        AttribsDict = {}
        AttribsDict = dict ((k, entry[k]) for k in ['RegionType', 'ResetImage', 'Copy', 'ReadOnly', 'Compressed'])
        AttribsDict = StringlizeDict (AttribsDict)
        SubElement (EntryElmt, 'TypeAttrib', AttribsDict)

    elif (IsPointEntry (entry)):
      EntryDict['Type'] = entry ['Type']
      EntryDict['Size'] = entry ['Size']
      EntryDict['Address'] = entry ['Address']  
      #Prepare for the 'Destination'
      if (entry['Destination'] != 0xFFFFFFFFFFFFFFFF):
        EntryDict['Destination'] = entry ['Destination']
      #Fill the instance, if instance is not 0
      if (entry['Instance'] != 0):
        EntryDict['Instance'] = entry ['Instance']
      #Fill the SubProgram, if SubProgram is not 0
      if (entry['SubProgram'] != 0):
        EntryDict['SubProgram'] = entry ['SubProgram']
      #Fill the RomId, if RomId is not 0
      if (entry['RomId'] != 0):
        EntryDict['RomId'] = entry ['RomId']

      EntryDict = StringlizeDict (EntryDict)
      EntryElmt = SubElement (DirElmt, 'POINT_ENTRY', EntryDict)

      #Prepare for the TypeAttrib tag, if any below attributes in non-zero
      if (not ((entry['RegionType'] == 0) and\
          (entry['ResetImage'] == 0) and\
          (entry['Copy'] == 0) and\
          (entry['ReadOnly'] == 0) and\
          (entry['Compressed'] == 0))):
        AttribsDict = {}
        AttribsDict = dict ((k, entry[k]) for k in ['RegionType', 'ResetImage', 'Copy', 'ReadOnly', 'Compressed'])
        AttribsDict = StringlizeDict (AttribsDict)
        SubElement (EntryElmt, 'TypeAttrib', AttribsDict)
    else:
      log.info ("Unrecognized entry Type")
      # FatalErrorExit ()
  
def OutPutPspDirectoryXml (PspDirectoryInfos, BiosDirectoryInfos, cfgFileName):
  global AddressMode
  global gXorBit24
  try:
    FileHandle = open (cfgFileName,'w')
  except:
    print "Error: Opening ", cfgFileName
    sys.exit(2)
  RootDict = {}
  if (AddressMode):
    RootDict['AddressMode'] = AddressMode
  if (gXorBit24):
    RootDict['XorBit24'] = gXorBit24
  RootDict = StringlizeDict (RootDict)
  root = Element('DIRS', RootDict)
  if (len (PspDirectoryInfos) != 0):
    for PspDirectoryInfo in PspDirectoryInfos:
      DirDict = {}
      # DirDict ['Base'] = PspDirectoryInfo ['PspDirOffset']
      if (PspDirectoryInfo ['BaseOffset'] != 0):
        DirDict ['HeaderBase'] = PspDirectoryInfo ['DirOffset']
        DirDict ['Base'] = PspDirectoryInfo ['BaseOffset']
      else:
        DirDict ['Base'] = PspDirectoryInfo ['DirOffset']

      if (PspDirectoryInfo ['DirSize'] != 0):
        DirDict ['Size'] = PspDirectoryInfo ['DirSize']
      if (PspDirectoryInfo ['SpiBlockSize'] != 0):
        DirDict ['SpiBlockSize'] = PspDirectoryInfo ['SpiBlockSize']
      DirDict ['Level'] = PspDirectoryInfo ['Level']
      DirDict = StringlizeDict (DirDict)
      DirElmt = SubElement (root, 'PSP_DIR', DirDict)
      for entry in PspDirectoryInfo['Entries']:
        EntryDict = {}
        if (IsValueEntry (entry)):
          EntryDict = dict ((k, entry[k]) for k in ['Type', 'Value'])
          EntryDict = StringlizeDict (EntryDict)
          SubElement (DirElmt, 'VALUE_ENTRY', EntryDict)
        elif (IsImageEntry (entry)):
          # Dynamic Address
          # EntryInfo = {'Type':Type,'Size':Size,'RTOffset':Location, 'Description':getEntryName(Type), 'Address':getOffsetInBin(biosSize, Location)}
          if (entry['RomId'] != 0):
            EntryDict['RomId'] = entry['RomId']
          EntryDict['File'] = OutputPath +  entry['File']
          if (PspDirectoryInfo ['DirSize'] != 0):
            EntryDict['Type'] = entry['Type16']
          else:
            EntryDict['Type'] = entry ['Type16']
            EntryDict['Size'] = entry ['Size']
            EntryDict['Address'] = entry ['Address']  
          EntryDict = StringlizeDict (EntryDict)
          SubElement (DirElmt, 'IMAGE_ENTRY', EntryDict)
        elif (IsPointEntry (entry)):
          if (entry['RomId'] != 0):
            EntryDict['RomId'] = entry['RomId']
          EntryDict['Type'] = entry ['Type16']
          EntryDict['Size'] = entry ['Size']
          EntryDict['Address'] = entry ['Address']  
          # EntryDict.update = {(k, entry[k]) for k in ['Type', 'Size', 'Address']}
          EntryDict = StringlizeDict (EntryDict)
          SubElement (DirElmt, 'POINT_ENTRY', EntryDict)
        else:
          log.info ("Unrecognized entry Type")
          # FatalErrorExit ()

  if (len (BiosDirectoryInfos) != 0):
    for BiosDirectoryInfo in BiosDirectoryInfos:
      OutPutBiosDirectoryXml (root, BiosDirectoryInfo)

  print >>FileHandle, prettify(root)

def main ():
  global OutputPath
  log.info ("%s","Parse Input Parameters:")
  Args = ParseArg()
  log.debug ("Args: %s",Args)
  OutputPath = Args.outputpath+"/"
  print "BuildPspDirectory   Version "+ Version+"\n"
  #Always create output folder except dp command with no additional parameters
  if not (Args.subcommand == 'dp' and
          Args.binary != True and
          Args.xml != True and 
          Args.directory != True):
    if not os.path.exists(OutputPath):
            os.makedirs(OutputPath)
  if (Args.subcommand == 'bd' or Args.subcommand == 'bb'):
    BiosSize=os.path.getsize(Args.InBiosImage)
    log.info ("Parse Configure File: %s\n", Args.CfgFile)
    (PspDicts, BiosDicts, ComboDict) = ParseCfgFile (Args.CfgFile)
    if (len(PspDicts) != 0):
      # Traverse PspDicts array
      for PspDict in PspDicts:
        log.info ("Optimize PSP Entry Order\n")
        PspDict = OptPspEntryOrder (PspDict)

        log.info ("Calculate PSP Entry Address\n")
        PspDict = CalcEntryOffset(BiosSize, PspDict)
        DumpPspDict (BiosSize, PspDict)
        log.info ("Prepare for PspDirecotry Header Data")
        PspDict ["PspDirHeader"] = BuildPspDir (BiosSize, PspDict)

    if (len(BiosDicts) != 0):
      # Traverse PspDicts array
      for BiosDict in BiosDicts:
        log.info ("Calculate BIOS Entry Address\n")    
        BiosDict = CalcEntryOffset (BiosSize, BiosDict)
        DumpBiosDict (BiosSize, BiosDict)

        log.info ("Prepare for BiosDirecotry Header Data")
        BiosDict ["BiosDirHeader"] = BuildBiosDir (BiosSize, BiosDict)

    if (len(ComboDict) != 0):
      log.info ("Prepare for ComboDict Header Data")
      ComboDirHeader = BuildComboDir (BiosSize, ComboDict)

    if (Args.subcommand == 'bd'):
      if (len(PspDicts) != 0):
        for PspDict in PspDicts:
          log.info ("Write the data to file %s%s", OutputPath, "PspDirHeaderL"+str (PspDict["Level"])+".bin")
          WriteBinaryFile ("PspDirHeaderL"+str (PspDict["Level"])+".bin", PspDict["PspDirHeader"])
      if (len(BiosDicts) != 0):
        for BiosDict in BiosDicts:
          log.info ("Write the data to file %s%s", OutputPath, "BiosDirHeaderL"+ str (BiosDict["Level"]) +".bin")
          # Only write the Level 1 Header
          WriteBinaryFile ("BiosDirHeaderL"+ str (BiosDict["Level"]) +".bin", BiosDict["BiosDirHeader"])

    elif (Args.subcommand == 'bb'):
      log.info ("Patch BIOS Image")
      # Read the BIOS file
      BiosBinary = ReadBinaryFile (Args.InBiosImage)
      #First update the PSPDirectory in the binary image
      if (len(PspDicts) != 0):
        for PspDict in PspDicts:
          if (PspDict['Base'] == None):
            log.info ("Error: Base attribute haven't been defined in PSP_DIR tag")
            FatalErrorExit()
          if (PspDict['HeaderBase'] != None):
            BiosBinary = PatchBinary (BiosBinary, PspDict["PspDirHeader"], PspDict['HeaderBase'], "PSPDirecory ")
          else:
            BiosBinary = PatchBinary (BiosBinary, PspDict["PspDirHeader"], PspDict['Base'], "PSPDirecory ")
          # Process each PSP entry
          for Entry in PspDict['Entries']:
            if (IsImageEntry(Entry)):
              PspBinary = ReadBinaryFile (Entry['File'])
              if (PspBinary == None):
                log.info ("Error Reading %s\n", Entry['File'])
                FatalErrorExit()
              # And patch the output image
              BiosBinary = PatchBinary (BiosBinary, PspBinary, Entry['Address'], Entry['File']+" "+hex(Entry['Type']))

      #Second update the BiosDirectory in the binary image
      if (len(BiosDicts) != 0):
        for BiosDict in BiosDicts:
          if (BiosDict['Base'] == None):
            log.info ("Error: Base attribute haven't been defined in BIOS_DIR tag")
            FatalErrorExit()
          if (BiosDict['HeaderBase'] != None):
            BiosBinary = PatchBinary (BiosBinary, BiosDict["BiosDirHeader"], BiosDict['HeaderBase'], "BIOSDirecory ")
          else:
            BiosBinary = PatchBinary (BiosBinary, BiosDict["BiosDirHeader"], BiosDict['Base'], "BIOSDirecory ")
          # Process each BIOS entry
          for Entry in BiosDict['Entries']:
            if (IsImageEntry(Entry)):
              PspBinary = ReadBinaryFile (Entry['File'])
              if (PspBinary == None):
                log.info ("Error Reading %s\n", Entry['File'])
                FatalErrorExit()
              # And patch the output image
              BiosBinary = PatchBinary (BiosBinary, PspBinary, Entry['Address'], Entry['File']+" "+hex(Entry['Type']))

      #update Combo Header in the binary image
      if (len(ComboDict) != 0):
        if (ComboDict['Base'] == None):
          log.info ("Error: Base attribute haven't been defined in ComboDict tag")
          FatalErrorExit()
        BiosBinary = PatchBinary (BiosBinary, ComboDirHeader, ComboDict['Base'], "COMBODirecory ")

      log.info ("Generate BIOS image [%s]" ,OutputPath + Args.OutBiosImage)
      WriteBinaryFile (Args.OutBiosImage, BiosBinary)
  elif (Args.subcommand == 'dp'):
    log.info ("Dump BIOS Psp DirectoryOut for %s" %(Args.program))
    (BinaryInfo, PspDirectoryInfos, BiosDirectoryInfos) = GetPspDirectory (Args.InBiosImage)
    if ((len (PspDirectoryInfos) == 0) and (len (BiosDirectoryInfos) == 0)):
      print "Error: Result of GetPspDirectory is invalid"
      FatalErrorExit ()
    if (Args.binary == True):
      print "Output  PSP binaries" 
      if (len (PspDirectoryInfos) != 0):
        for PspDirectoryInfo in PspDirectoryInfos:
          OutPutPspBinaries (BinaryInfo['Binary'],PspDirectoryInfo['Entries'])

      print "Output  BIOS binaries"
      if (len (BiosDirectoryInfos) != 0):
        for BiosDirectoryInfo in BiosDirectoryInfos:
          OutPutBiosBinaries (BinaryInfo['Binary'],BiosDirectoryInfo['Entries'])
    if (Args.xml == True):
      print "Output  PspDirInfo.xml"
      OutPutPspDirInfoXml (BinaryInfo, PspDirectoryInfos, BiosDirectoryInfos, OutputPath + "PspDirInfo.xml")
    if (Args.directory == True):
      print "Output  PspDirectory.xml"
      OutPutPspDirectoryXml (PspDirectoryInfos, BiosDirectoryInfos, OutputPath + "PspDirectory.xml")
if __name__ == "__main__":
  main()