import os
import re
import sys
import struct
import binascii
import shutil
import argparse
from operator import itemgetter
import pdb
# pdb.set_trace()
from xml.etree.ElementTree import Element, SubElement, Comment, tostring
from xml.dom import minidom
import types

#Global Variable
#Version 1.0.1  Add Blob Support, Display PSP FW version in Hexadecimal
#Version 1.1.0  Support recovery scheme
#Version 1.1.1  Fix BVM issue with recovery configuration
#Version 1.1.2  Update Secure OS max size, fix max size calculation issue.
#               Show version information at startup
#Version 1.1.3  Fix system always in recovery mode when use max size as the entry size
#               Which bring in V 1.1.2
#Version 1.1.4  Add New type 0x13 for PSP early secure unlock debug image
#               Fix error exit when add a new unknown type
#Version 1.2.0  CZ branch from ML 1.1.4
#               Add New Type 0x10,0x12 (AgesaS3Rsm, SmuFw2)
#Version 1.2.1  Enlarge PSP NVRAM from 0x8000 to 0x10000
#Version 1.2.2  Update PSP entry max size for compressed PSP FW
#               NOTE this version ONLY compatible with PSP FW version >= 0.2.0.17
#Version 1.2.3  Add new type 0x1A PspNvS3
#Version 1.2.4  Enlarge PspTrustlet from 0x16000 to 0x1A000
#Version 1.2.5  Add "RECOVERY_SUPPORT =0" to overridden Recovery flag even two FV blocks declared
#Version 1.2.6  Add new Type for BR SMU FW
#Version 1.2.7  Add new required parameter "-V" for "DP" subcommand
#Version 1.2.8  DP command add support for the BIOS which doesn't include the PSP FV information

#9/6/2016
#Version 1.2.9  Fix entry size not reflect max size when recovery flag set
#		Add entry 0x14 for TPM 1.22 binary

#6/19/2018
#Version 1.2.A  Increase extra 24K to PSP OS Max Size

Version = "1.2.A"
BiosList = []
PspList = []
PspDirectoryHeaderSize = 16
PspDirectoryEntrySize = 16
Args = ''
#0 PSP FV will use one continual region, and all PSP entry will use file size as its entry size
#non-zero PSP FV will divide to two blocks: Fixed & Update-able, and reserve entry's MaxSize for each entry
#1 Two Continual Blocks
#2 Two separate Blocks
PspFvTwoBlockFlag  = 0
#Flag to control max size check when PspFvTwoBlockFlag set to 1
RecoveryFlag = 1

PspDirectoryEntryDict = {
#                         Type: IsFix MaxSize  ShortName    Full description
                          0x0000: [ 1, 576,       'AmdPubKey','AMD public Key', ],
                          0x0001: [ 0, 32 *1024,  'PspBootLoader','PSP Boot Loader firmware'],
                          0x0002: [ 0, 144*1024,  'PspOs','PSP Secure OS firmware'],
                          0x0003: [ 1, 24 *1024,  'PspRecBL','PSP Recovery Boot Loader'],
                          0x0004: [ 1, 64 *1024,  'PspNv','PSP Non Volatile data'],
                          0x0005: [ 1, 832,       'OemPubKey','[OEM] BIOS public key signed with AMD key'],
                          0x0006: [ 0, 0x000000,  'Rtm','BIOS RTM Volume'],
                          0x0007: [ 0, 256,  'RtmSignature','BIOS RTM volume Signature using OEM private key'],
                          0x0008: [ 0, 80 *1024,  'Smu','SMU offchip firmware (ProgramId 0),for CZ program: 0=CZ, 1=BR'],
                          0x0108: [ 0, 80 *1024,  'Smu','SMU offchip firmware (ProgramId 1),for CZ program: 0=CZ, 1=BR'],
                          0x0009: [ 1, 832,       'DbgKey','AMD Secure Debug Key'],
                          0x000A: [ 1, 832,  'OemPspPubkey','PSP Secure OS public key signed with AMD key'],
                          0x000B: [ 1, 0x000000,  'Value','Secure Unlock Enable flag'],
                          0x000C: [ 0, 104 *1024, 'PspTrustlet96','PSP trustlet Binary 0.96'],
                          0x000D: [ 1, 832,  'TrusletKey','truslet key(Signed public portion)'],
                          0x0010: [ 0, 32 *1024,  'AgesaS3Rsm','AGESA S3 Resume'],
                          0x0012: [ 0, 44 *1024,  'SmuFw2','Smu FW 2 (ProgramId 0),for CZ program: 0=CZ, 1=BR'],
                          0x0112: [ 0, 44 *1024,  'SmuFw2','Smu FW 2 (ProgramId 1),for CZ program: 0=CZ, 1=BR'],
                          0x0013: [ 0, 40 *1024,  'PspEsud','PSP early secure unlock debug image'],
                          0x0014: [ 0, 128 *1024,  'PspTrustlet122','PSP trustlet Binary 1.22'],
                          0x001A: [ 0, 12 *1024,  'PspNvS3','PSP Non Volatile data for S3'],
                          0x005F: [ 0, 4  *1024,  'Scs','SCS Binary'],
                          }

PspDirectoryTypeCnt = len (PspDirectoryEntryDict)

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


def prettify(elem):
    """Return a pretty-printed XML string for the Element.
    """
    rough_string = tostring(elem, 'utf-8')
    reparsed = minidom.parseString(rough_string)
    return reparsed.toprettyxml(indent="  ")

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




def ReadTextFile (File):

  if (os.path.exists(File) == False):
    print "\n[Error] :", File, " does not exist"
    return (None)

  try:
    FileHandle = open (File,'r')
  except:
    print "[Error]: Opening ", File
    sys.exit(2)
  lines = FileHandle.readlines()
  FileHandle.close()

  return lines

def ReadBinaryFile (File):

  if (os.path.exists(File) == False):
    print "\n[Error] :", File, " does not exist"
    return (None)

  try:
    FileHandle = open (File,'rb')
  except:
    print "[Error]: Opening ", File
    sys.exit(2)
  lines = FileHandle.read()
  FileHandle.close()

  return lines

def WriteBinaryFile (File, buffer):

  try:
    FileHandle = open (File,'wb')
  except:
    print "[Error]: Opening ", File
    sys.exit(2)
  FileHandle.write(buffer)
  FileHandle.close()

def PatchBinary (OrgBuffer, ModBuffer, Offset, Message):
  print "<%s> content copied between [0x%04x ~ 0x%04x]" % (Message, Offset, Offset + len(ModBuffer))
  if (Offset + len (ModBuffer) > len (OrgBuffer)):
    sys.exit (2)
  buffer = OrgBuffer[0:Offset] + ModBuffer + OrgBuffer[Offset+ len(ModBuffer):]
  return buffer

def PatchBinary2 (biosbuf, entry, inputfilebuf):
  offset = entry['Offset']
  size = entry ['Size']
  print "Content between [0x%08x and 0x%08x] Updated <%s>" % (offset, offset + size - 1, entry['Description'])
  default = '\x00'
  filelen = len (inputfilebuf)
  buffer = biosbuf[0:offset] + inputfilebuf + default * (size - filelen) + biosbuf [offset + size: ]
  return buffer

PspImageEntry = "^\s*PSP_ENTRY\s*TYPE\s*=\s*(\S*)\s*,\s*FILE\s*=\s*(\S+)\s*$"
# Entry with size
PspImageEntryExt = "^\s*PSP_ENTRY\s*TYPE\s*=\s*(\S*)\s*,\s*FILE\s*=\s*(\S+)\s*,\s*Size\s*=\s*(\S*)\s*$"
# Entry with Value
PspImageEntryExt1 = "^\s*PSP_ENTRY\s*TYPE\s*=\s*(\S*)\s*,\s*VALUE\s*=\s*(\S+)\s*$"
# Entry with Address
PspImageEntryExt2 = "^\s*PSP_ENTRY\s*TYPE\s*=\s*(\S*)\s*,\s*FILE\s*=\s*(\S+)\s*,\s*ADDRESS\s*=\s*(\S+)\s*$"

BiosImageEntry = "^\s*BIOS_IMAGE\s*INPUT_FILE\s*=\s*(\S+)\s*,\s*PSP_FV_BASE\s*=\s*(\S*)\s*,\s*PSP_FV_SIZE\s*=\s*(\S*)\s*,\s*RTM_SIZE\s*=\s*(\S*)\s*"
#Support PSP TWO separate FV blocks
BiosImageEntry1 = "^\s*BIOS_IMAGE\s*INPUT_FILE\s*=\s*(\S+)\s*,\s*FIXFV_BASE\s*=\s*(\S*)\s*,\s*FIXFV_SIZE\s*=\s*(\S*)\s*,\s*DYNFV_BASE\s*=\s*(\S*)\s*,\s*DYNFV_SIZE\s*=\s*(\S*)\s*,\s*RTM_SIZE\s*=\s*(\S*)\s*"
#Support PSP TWO FV blocks which  continual
BiosImageEntry2 = "^\s*BIOS_IMAGE\s*INPUT_FILE\s*=\s*(\S+)\s*,\s*PSP_FV_BASE\s*=\s*(\S*)\s*,\s*FIXFV_SIZE\s*=\s*(\S*)\s*,\s*DYNFV_SIZE\s*=\s*(\S*)\s*,\s*RTM_SIZE\s*=\s*(\S*)\s*"
#Recovery FLAG
#RECOVERY_SUPPORT=0
RecoveryFlagReStr = "^\s*RECOVERY_SUPPORT\s*=\s*(\S+)\s*"
RegExBiosEntry  = re.compile (BiosImageEntry,re.IGNORECASE|re.DOTALL)
RegExBiosEntry1  = re.compile (BiosImageEntry1,re.IGNORECASE|re.DOTALL)
RegExBiosEntry2  = re.compile (BiosImageEntry2,re.IGNORECASE|re.DOTALL)

RegExPspEntry   = re.compile (PspImageEntry,re.IGNORECASE|re.DOTALL)
RegExPspEntryExt= re.compile (PspImageEntryExt,re.IGNORECASE|re.DOTALL)
RegExPspEntryExt1= re.compile (PspImageEntryExt1,re.IGNORECASE|re.DOTALL)
RegExPspEntryExt2= re.compile (PspImageEntryExt2,re.IGNORECASE|re.DOTALL)
RegExRecoveryFlag = re.compile (RecoveryFlagReStr,re.IGNORECASE|re.DOTALL)

def ParsePspFile (File):
  global Args
  global PspFvTwoBlockFlag
  global RecoveryFlag
  list = dict()
  PspEntryList=[]
  BiosEntryList =[]
  lines = ReadTextFile(File)
  if (lines == None):
    return None

  # Parse through each line and see if any Recovery Flag overridden

  for line in lines:
    m = RegExRecoveryFlag.findall(line)
    if (m !=[]):
      (RecoveryFlag) =  StrToNum(m[0])

  # Parse through each line and see if Bios entry or Psp entry is defined
  for line in lines:
    #BIOS_IMAGE  INPUT_FILE = LarneMLX64.fd,  PSP_FV_BASE=0x2FE000, PSP_FV_SIZE=0x130000, RTM_SIZE = 0xCB000
    m = RegExBiosEntry.findall(line)
    if (m !=[]):
      # Bios information found. Use it
      (InputFile, PspFvBase, PspFvSize, BiosRtmSize) =  m[0]
      if (os.path.exists(InputFile) == False):
        print "[Error] Bios file\"",InputFile, "\"not found."
        sys.exit (2)
        continue

      BiosSize=os.path.getsize(InputFile)
      PspFvBase=int(PspFvBase,0)
      PspFvSize=int(PspFvSize,0)
      BiosRtmSize=int(BiosRtmSize,0)
      PspFvBase2 = 0
      PspFvSize2 = 0
      BiosEntryList =( (InputFile, BiosSize, PspFvBase, PspFvSize, BiosRtmSize, PspFvBase2, PspFvSize2))
      continue

    #Two separate PSP FV blocks
    #BIOS_IMAGE  INPUT_FILE = LarneMLX64.fd,  FIXFV_BASE=0x200000, FIXFV_SIZE=0x20000, DYNFV_BASE=0x280000, DYNFV_SIZE=0x80000, RTM_SIZE = 0xCB000
    m = RegExBiosEntry1.findall(line)
    if (m !=[]):
      PspFvTwoBlockFlag = 2
      # Bios information found. Use it
      (InputFile, PspFvBase, PspFvSize, PspFvBase2, PspFvSize2, BiosRtmSize) =  m[0]
      if (os.path.exists(InputFile) == False):
        print "[Error] Bios file\"",InputFile, "\"not found."
        sys.exit (2)

      BiosSize=os.path.getsize(InputFile)
      PspFvBase=int(PspFvBase,0)
      PspFvSize=int(PspFvSize,0)
      BiosRtmSize=int(BiosRtmSize,0)
      PspFvBase2=int (PspFvBase2, 0)
      PspFvSize2=int (PspFvSize2,0)
      BiosEntryList =( (InputFile, BiosSize, PspFvBase, PspFvSize, BiosRtmSize, PspFvBase2, PspFvSize2))
      continue

    #Two PSP FV block  continual
    # BIOS_IMAGE  INPUT_FILE = LarneMLX64.fd,  PSP_FV_BASE=0x200000, FIXFV_SIZE=0x20000, DYNFV_SIZE=0x80000, RTM_SIZE = 0xCB000
    m = RegExBiosEntry2.findall(line)
    if (m !=[]):
      #Two PSP FV block found
      PspFvTwoBlockFlag = 1
      # Bios information found. Use it
      (InputFile, PspFvBase, PspFvSize, PspFvSize2, BiosRtmSize) =  m[0]
      if (os.path.exists(InputFile) == False):
        print "[Error] Bios file\"",InputFile, "\"not found."
        sys.exit (2)

      BiosSize=os.path.getsize(InputFile)
      PspFvBase=int(PspFvBase,0)
      PspFvSize=int(PspFvSize,0)
      BiosRtmSize=int(BiosRtmSize,0)
      PspFvBase2=PspFvBase + PspFvSize
      PspFvSize2=int (PspFvSize2,0)
      BiosEntryList =( (InputFile, BiosSize, PspFvBase, PspFvSize, BiosRtmSize, PspFvBase2, PspFvSize2))
      continue

    #PSP Entry with Size
    #PSP_ENTRY TYPE=?, FILE=?, Size = ?
    m = RegExPspEntryExt.findall(line)
    if (m !=[]):
      # PspEntry information found. Use it
      (PspType, PspFile,  Size) =  m[0]
      PspType = int (PspType,0)
      Size = int (Size,0)
      if (Args.subcommand == 'bb') : #Only check the File existance when execute the BD command
        if (os.path.exists(PspFile) == False):
          print "[Error] Psp entity file\"",PspFile, "\"not found."
          sys.exit (2)

      if (PspFvTwoBlockFlag):
        print "Warning Size will be ignored when Specify the two PSP FV region \n \"%s\"" %(line[0:-1])
      #Offset field will filled later, now keep it as 0
      PspEntryList.append([PspFile, PspType, 0, Size])
      continue

    #PSP Entry without Size
    #PSP_ENTRY TYPE=?, FILE=?
    m = RegExPspEntry.findall(line)
    if (m !=[]):
      # PspEntry information found. Use it
      (PspType, PspFile) =  m[0]
      PspType = int (PspType,0)
      if (os.path.exists(PspFile) == False):
        print "[Error] Psp entity file\"",PspFile, "\"not found."
        sys.exit (2)

      Size = os.path.getsize(PspFile)
      if (PspFvTwoBlockFlag and RecoveryFlag):
        if (IsFileExceedMaxSize(PspType, PspFile)):
          print "[Error] %s exceed its MaxSize %x" %(PspFile, getEntryMaxSize(PspType))
          sys.exit (2)
      #Offset field will filled later, now keep it as 0
      PspEntryList.append([PspFile, PspType, 0, Size])

    #PSP Entry with Value
    #PSP_ENTRY TYPE=?, Value=?
    m = RegExPspEntryExt1.findall(line)
    if (m !=[]):
      # PspEntry information found. Use it
      (PspType, Value) =  m[0]
      PspType = int (PspType,0)
      Value = int (Value, 0)
      #Offset field will filled later, now keep it as 0
      PspEntryList.append([PspFile, PspType, Value, 0xFFFFFFFF])

    #PSP Entry with Address
    #PSP_ENTRY TYPE=?, FILE=?, ADDRESS=?
    m = RegExPspEntryExt2.findall(line)
    if (m !=[]):
      # PspEntry information found. Use it
      (PspType, PspFile, Address) =  m[0]
      PspType = int (PspType,0)
      Address = int (Address, 0)
      #Convert to RT MMIO Address
      Address = GetRTOffset (BiosSize, Address)
      if (os.path.exists(PspFile) == False):
        print "[Error] Psp entity file\"",PspFile, "\"not found."
        sys.exit (2)

      Size = os.path.getsize(PspFile)
      if (PspFvTwoBlockFlag and RecoveryFlag):
        if (IsFileExceedMaxSize(PspType, PspFile)):
          print "[Error] %s exceed its MaxSize" %(PspFile, getEntryMaxSize(PspType))
          sys.exit (2)
      PspEntryList.append([PspFile, PspType, Address, Size])

  #if Entry 6 NOT in the list
  #Auto append RTM entry
  Type6Founded = False
  for PspEntry in PspEntryList:
    if (PspEntry[1] == 6):
      Type6Founded = True
  if (Type6Founded == False):
      PspEntryList.append(["AUTO", 0x06, 0x100000000 - BiosRtmSize, BiosRtmSize])
  return (BiosEntryList, PspEntryList)

def IsEntry6Blob (Entry):
  if ('RTOffset' in Entry):
    if ((Entry['Type'] == 6) and (Entry['RTOffset']+Entry['Size'] != 0x100000000)):
      return True
    else:
      return False

def BuildPspDir ():
  PspEntry=""
  global BiosList
  global PspList
  global PspFvTwoBlockFlag
  InputBios, BiosSize, PspFvBase, PspFvSize, BiosRtmSize, PspFvBase2, PspFvSize2 = BiosList

  # Sort PSP entities in terms of offset
  #PspList = sorted (PspList, key=itemgetter(2))

  PspEntryFmt = 'I I Q'
  PspEntrySize = struct.calcsize(PspEntryFmt)
  # Process each PSP entry
  for (PspFile, Type, Location, Size) in PspList:
    Entry = (Type, Size, Location)
    print "PSP_ENTRY 0x%02x 0x%08x 0x%08x" %(Entry[0], Entry[1], Entry[2]),
    if (Size == 0xFFFFFFFF):
      print "(%-8s)" %"Value",
    else:
      print "(%8s)" %"Location",
    print "(%s)" %getEntryName((Entry[0]))
    s = struct.Struct(PspEntryFmt)
    #Pack Type,
    PspEntry += s.pack(*Entry)

  if (PspFvTwoBlockFlag):
#   1       7          8           8        8
# +----+---------+-----------+----------+---------+
# |FLAG|   RSV   | DYN BASE  | DYN SIZE | FixSIZE |
# +----+---------+-----------+----------+---------+
    if ((PspFvBase2 & 0xFFFF) or (PspFvBase2 >= 0xFF0000) or\
        (PspFvSize2 & 0xFFFF) or (PspFvSize2 >= 0x3F0000) or\
        (PspFvBase  & 0xFFFF) or (PspFvBase  >= 0xFF0000) ):
      print "[Warning] PSP FV Entry or Size are NOT match BVM's requirement"
      print "          Both PSP FV Base & Size should 64K aligned, and smaller than 0xFF0000"
    # Set Flag to indicate two Block format
    PspFvSizeFieldValue = 1 << 31
    #Dynamic Base only needed for two separate blocks
    if (PspFvTwoBlockFlag == 2):
      PspFvSizeFieldValue += ((PspFvBase2 >> 16) << 16)
    #Dynamic Block Size
    PspFvSizeFieldValue += ((PspFvSize2 >> 16) << 8)
    #Fix Block Size
    PspFvSizeFieldValue += ((PspFvSize  >> 16) << 0)
  else:
    if (PspFvSize & 0x80000000):
      print "[Error] Invalid PSP FV size"
      sys.exit (2)
    PspFvSizeFieldValue = PspFvSize
  s = struct.Struct('I I')
  values = (len (PspEntry)/PspEntrySize , PspFvSizeFieldValue)
  CrcList = s.pack(*values) + PspEntry

  crc = Fletcher32Crc (CrcList, len (CrcList)/2)
  print "checksum %x" % crc
  values = ("$PSP", crc, len (PspEntry)/PspEntrySize , PspFvSizeFieldValue)
  s = struct.Struct('4s I I I')
  PspHeader = s.pack(*values)
  PspDir = PspHeader+PspEntry
  return PspDir

def OptPspList ():
  """Optimize the order of PSP entry"""
  global PspList
  NewPspList=[]
  OptOrder = [0,1,8,3,5,6,7,2,4]
  for OptType in OptOrder:
    #Search the specific type in the PspList
    for PspEntry in PspList:
      if (PspEntry[1] == OptType):
        NewPspList.append (PspEntry)
  #append  entries which not in the OPT list
  for PspEntry in PspList:
    if (not(PspEntry[1] in OptOrder)):
      NewPspList.append (PspEntry)
  #update PspList
  PspList = NewPspList

def GetOccupiedSize (ActualSize, Alignment):
  """Calculate occupied size considering the alignment"""
  return   (ActualSize + (((Alignment) - ((ActualSize) & ((Alignment) - 1))) & ((Alignment) - 1)))

def CalcPspEntryOffset ():
  global PspFvTwoBlockFlag
  if (PspFvTwoBlockFlag):
    CalcPspEntryOffsetforTwoFv ()
  else:
    CalcPspEntryOffsetforOneFv ()

def CalcPspEntryOffsetforOneFv ():
  """Calculate Offset by each entry except TYPE6 RTM with AUTO flag"""
  global BiosList
  global PspList
  global PspDirectoryHeaderSize
  global PspDirectoryEntrySize
  global PspDirectoryTypeCnt
  #(InputFile, BiosSize, PspFvBase, PspFvSize, BiosRtmSize)
  UsedSize = 0
  #Bios image is 4GB - size of BIOS image
  NextEntryOffset = 0x100000000 - BiosList[1]+ BiosList[2]
  #Calc Psp Directory table size, and make next PSP entry entity on 0x1000 (4K) boundary
  CurEntrySize = GetOccupiedSize((PspDirectoryHeaderSize + PspDirectoryEntrySize * PspDirectoryTypeCnt) , 0x1000)
  UsedSize += CurEntrySize
  NextEntryOffset += CurEntrySize
  #(PspFile, PspType, Offset, Size)
  for PspEntry in PspList:
      #Skip Type 6, RTM file (AUTO)
      #Skip Size with 0xFFFFFFFF, which reserve for value entry
      #Skip Entry which Address filed already filled
      if ((PspEntry[3] != 0xFFFFFFFF) and (PspEntry[2] == 0)):
        if (not((PspEntry[1] == 6) and (PspEntry[0] == "AUTO"))):
          PspEntry[2] = NextEntryOffset
          CurEntrySize = GetOccupiedSize (PspEntry[3], 0x1000)
          UsedSize += CurEntrySize
          NextEntryOffset += CurEntrySize
          if (UsedSize > BiosList [3]):
            print "[Error] Exceed the limit of PSP FV 0x%xBytes\n" %BiosList [3]
            sys.exit (2)
      #print "%s %x %x %d %x\n" %(PspEntry[0], PspEntry[1], PspEntry[2], PspEntry[3], PspEntry[3])
  #show percent of FV usage
  print "PSP FV 0x%x bytes used, 0x%x bytes free [%.2f%% full]" %(UsedSize, (BiosList[3] -  UsedSize), float (UsedSize)/float (BiosList[3]) *100 )

def CalcPspEntryOffsetforTwoFv ():
  """Calculate Offset by each entry except TYPE6 RTM with AUTO flag"""
  global BiosList
  global PspList
  global PspDirectoryHeaderSize
  global PspDirectoryEntrySize
  global PspDirectoryTypeCnt
  #(InputFile, BiosSize, FixFvBase, FixFvSize, BiosRtmSize, DynamicFvBase, DynamicFvSize1)
  BiosSize = BiosList[1]
  EntrySize = 0

  FixFvBase = BiosList[2]
  FixFvSize = BiosList[3]
  FixFvUsedSize = 0

  DynFvBase = BiosList[5]
  DynFvSize = BiosList[6]
  DynFvUsedSize = 0

  #Bios MMIO Address is 4GB - size of BIOS image
  FixFvNextEntryOffset = 0x100000000 - BiosSize + FixFvBase
  DynFvNextEntryOffset = 0x100000000 - BiosSize + DynFvBase
  # FixFvNextEntryOffset = FixFvBase
  # DynFvNextEntryOffset = DynFvBase

  #Calc Psp Directory table size, and make next PSP entry entity on 0x1000 (4K) boundary
  FixFvCurEntrySize = GetOccupiedSize((PspDirectoryHeaderSize + PspDirectoryEntrySize * PspDirectoryTypeCnt) , 0x1000)
  FixFvUsedSize += FixFvCurEntrySize
  FixFvNextEntryOffset += FixFvCurEntrySize

  #(PspFile, PspType, Offset, Size)
  for PspEntry in PspList:
      #Skip Type 6, RTM file (AUTO)
      #Skip Size with 0xFFFFFFFF, which reserve for value entry
      #Skip Entry which Address filed already filled
      if ((PspEntry[3] != 0xFFFFFFFF) and (PspEntry[2] == 0)):
        if (not((PspEntry[1] == 6) and (PspEntry[0] == "AUTO"))):
          #Fix FV Entries
          if (getEntryIsFix (PspEntry[1])):
            PspEntry[2] = FixFvNextEntryOffset
            #Get Entry Size information, Use entry's max size as its size if has been defined
            #Use entry's real size if recovery-flag cleared
            if (getEntryMaxSize (PspEntry[1]) and RecoveryFlag):
              EntrySize = getEntryMaxSize (PspEntry[1])
            else:
              EntrySize = PspEntry[3]
            FixFvCurEntrySize = GetOccupiedSize (EntrySize, 0x1000)
            FixFvUsedSize += FixFvCurEntrySize
            FixFvNextEntryOffset += FixFvCurEntrySize
            print "FIX Type %x Size %x || UsedSize %x Fvsize %x" %(PspEntry[1], FixFvCurEntrySize, FixFvUsedSize, FixFvSize)
            if (FixFvUsedSize > FixFvSize):
              print "[Error] Exceed the limit of FIX PSP FV 0x%xBytes\n" %FixFvSize
              sys.exit (2)
          else:
          #dynamic FV Entries
            PspEntry[2] = DynFvNextEntryOffset
            #Get Entry Size information, Use entry's max size as its size if has been defined
            if (getEntryMaxSize (PspEntry[1]) and RecoveryFlag):
              EntrySize = getEntryMaxSize (PspEntry[1])
            else:
              EntrySize = PspEntry[3]
            DynFvCurEntrySize = GetOccupiedSize (EntrySize, 0x1000)
            DynFvUsedSize += DynFvCurEntrySize
            DynFvNextEntryOffset += DynFvCurEntrySize
            print "DYN Type %x Size %x || UsedSize %x Fvsize %x" %(PspEntry[1], DynFvCurEntrySize, DynFvUsedSize, DynFvSize)
            if (DynFvUsedSize > DynFvSize):
              print "[Error] Exceed the limit of Dynamic PSP FV 0x%xBytes\n" %DynFvSize
              sys.exit (2)
        #Update the size filed in case it has been updated above
        # if (PspEntry[1] != 1):
        PspEntry[3] = EntrySize
      #print "%s %x %x %d %x\n" %(PspEntry[0], PspEntry[1], PspEntry[2], PspEntry[3], PspEntry[3])
  #show percent of FV usage
  print "PSP FIX FV 0x%x bytes used, 0x%x bytes free [%.2f%% full]" %(FixFvUsedSize, (FixFvSize -  FixFvUsedSize), float (FixFvUsedSize)/float (FixFvSize) *100 )
  print "PSP DYN FV 0x%x bytes used, 0x%x bytes free [%.2f%% full]" %(DynFvUsedSize, (DynFvSize -  DynFvUsedSize), float (DynFvUsedSize)/float (DynFvSize) *100 )

def CheckFileExistance (file):
  return os.path.exists(file)

def ParseArg ():
  global Version
  """Parse Input arguments, and return the parsed result"""
  Parser = argparse.ArgumentParser (description='Tool used to Build PSP DirTable & Embed/Dump/Replace PSP entries')
  Parser.add_argument ('--version', action='version', version='BuildPspDirectory %s' %(Version))
  Parser.add_argument ('-o','--outputpath',default="PspDirToolOutput")
  SubParser = Parser.add_subparsers(dest='subcommand',help="Type '<subcommand> -h' for help on a specific subcommand")
  #Build Directory table
  BDParser = SubParser.add_parser ('bd',help='Build Directory table')
  BDParser.add_argument ("CfgFile", help="Specify the config file for build the PSP Directory")
  BDParser.add_argument ("PspDirFile", help="Specify the OUTPUT PSP Directory binary file name")
  #Build Bios image with psp entry file embedded
  BBParser = SubParser.add_parser ('bb',help='Build Bios image with psp entry file embedded')
  BBParser.add_argument ("CfgFile", help="Specify the config file for build the PSP Directory")
  # BBParser.add_argument ("InBiosImage", help="Specify the Input BIOS image file name")
  BBParser.add_argument ("OutBiosImage", help="Specify the OUTPUT BIOS image file name")
  #DumP psp entry of given BIOS image
  DPParser = SubParser.add_parser ('dp',help='DumP psp entry of given BIOS image')
  DPParser.add_argument ("InBiosImage", help="Specify the INPUT BIOS image file name")
  DPParser.add_argument ("-v","--Vector", help="Specify vector number of ROMSIG to look for PSP directory header, 0: for CZ, BR 1: for ST", required=True)
  DPParser.add_argument ("-x","--xml", help="Output the information in XML format to PspDirInfo.xml",action="store_true")
  DPParser.add_argument ("-b","--binary", help="Output  psp binaries to outputpath",action="store_true")
  DPParser.add_argument ("-d","--directory", help="Output PspDirectory.cfg to outputpath",action="store_true")

  args = Parser.parse_args ()
  #Parameter check
  if (args.subcommand == 'bd'):
    if (CheckFileExistance(args.CfgFile) == False):
      print "[Error] CfgFile '%s' doesn't exists" %args.CfgFile
      sys.exit (2)
  # elif (args.subcommand == 'bb'):
  #   if (CheckFileExistance(args.CfgFile) == False):
  #     print "[Error] CfgFile '%s' doesn't exists" %args.CfgFile
  #     sys.exit (2)
  elif (args.subcommand == 'dp'):
    if (CheckFileExistance(args.InBiosImage) == False):
      print "[Error] BiosImage '%s' doesn't exists" %args.BiosImage
      sys.exit (2)
  return args

def getEntryIsFix (entry):
  global PspDirectoryEntryDict
  if entry in PspDirectoryEntryDict:
    return PspDirectoryEntryDict[entry][0]
  else:
    #Treat unknown entry as Unfix entry
    return 0

def getEntryMaxSize (entry):
  global PspDirectoryEntryDict
  if entry in PspDirectoryEntryDict:
    return PspDirectoryEntryDict[entry][1]
  else:
    #0 indicated Unsupported, the caller can use file size as the Max Size
    return 0


def getEntryShortName (entry):
  global PspDirectoryEntryDict
  if entry in PspDirectoryEntryDict:
    return PspDirectoryEntryDict[entry][2]
  else:
    return "unknown"

def getEntryName (entry):
  global PspDirectoryEntryDict
  if entry in PspDirectoryEntryDict:
    return PspDirectoryEntryDict[entry][3]
  else:
    return "Unknown Type"

def IsFileExceedMaxSize (entry, pspfile):
  if getEntryMaxSize(entry):
    return (os.path.getsize(pspfile) > getEntryMaxSize(entry))
  else:
    return 0

def pspBootLoaderInfo (bios, entry):
  pspBLHeaderSize = 0x100
  verOffset = 0x60
  pspBLInfo = {}
  pspBLHeader = bios [entry['Offset']:entry['Offset']+pspBLHeaderSize]
  pspVer = struct.unpack ('L',pspBLHeader[verOffset:verOffset+4])
  verStr ="%02d.%02d.%04X" %(((pspVer[0] & 0xFF000000)>>24), ((pspVer[0] & 0xFF0000) >> 16),(pspVer[0] & 0xFFFF))
  pspBLInfo['Version'] = verStr
  return pspBLInfo


def pspSecureOsInfo (bios, entry):
  pspOSHeaderSize = 0x100
  verOffset = 0x60
  pspOSInfo = {}
  pspOSHeader = bios [entry['Offset']:entry['Offset']+pspOSHeaderSize]
  pspVer = struct.unpack ('L',pspOSHeader[verOffset:verOffset+4])
  verStr ="%02d.%02d.%04X" %(((pspVer[0] & 0xFF000000)>>24), ((pspVer[0] & 0xFF0000) >> 16),(pspVer[0] & 0xFFFF))
  pspOSInfo['Version'] = verStr
  return pspOSInfo

def smuFwInfo (bios, entry):
  smuHeaderSize = 128
  digestOffset = 0
  verOffset = 20
  smuInfo = {}
  smuHeader = bios [entry['Offset']:entry['Offset']+smuHeaderSize]
  smuVer = struct.unpack ('L',smuHeader[verOffset:verOffset+4])
  digest = struct.unpack ('5L',smuHeader[digestOffset:digestOffset+4 * 5])
  digeststr = ",".join (hex(v).rstrip('L') for v in digest)
  verStr ="%04d.%02d.%02d" %(((smuVer[0] & 0xFFFF0000)>>16), ((smuVer[0] & 0xFF00) >> 8),(smuVer[0] & 0xFF))
  # verStr = str ((smuVer[0] & 0xFFFF0000)>>16).lstrip("0x").rstrip('L') + '.'+ str ((smuVer[0] & 0xFF00) >> 8).lstrip("0x") +'.'+ str (smuVer[0] & 0xFF).lstrip("0x")
  smuInfo['Version'] = verStr
  smuInfo['Digest'] = digeststr
  return smuInfo

def getOffsetInBin (romsize, offset):
  return romsize-(0x100000000 - offset)

def GetRTOffset (romsize, offset):
  return 0x100000000 - romsize + offset

def GetPspDirectory (biosfile):
  PspDirectoryInfo = {}
  try:
    FileHandle = open (biosfile,'rb')
  except:
    print "[Error]: Opening ", biosfile
    sys.exit(2)
  #read whole bios to buffer
  FileHandle.seek (0)
  biosSize = os.path.getsize(biosfile)
  PspDirectoryInfo ['bios'] = FileHandle.read (biosSize)
  PspDirectoryInfo ['biosName'] = biosfile
  PspDirectoryInfo ['biosSize'] = biosSize

  FileHandle.seek (0x20000)
  OemSigRaw = FileHandle.read (0x20)
  OemSigArray = struct.unpack ('8L',OemSigRaw)
  #Check OEM signature, ang get Psp Directory offset
  if (OemSigArray[0] == 0x55aa55aa):
    print "Oem Sig Table Found"
  else:
    print "[Error] Can't Found the Oem Sig table"
    sys.exit (2)
  PspDirRTOffset = OemSigArray[4+ StrToNum(Args.Vector)]
  print "Psp Directory Offset 0x%X" %PspDirRTOffset
  #convert to raw binary offset
  PspDirOffSetInBin = getOffsetInBin (biosSize, PspDirRTOffset)
  print "Psp Directory Offset in binary 0x%X" %PspDirOffSetInBin
  PspDirectoryInfo ['PspDirOffset'] = PspDirOffSetInBin

  #Verify PSP Directory blob
  #read Psp Header
  FileHandle.seek (PspDirOffSetInBin)
  PspDirTblRaw = FileHandle.read (16)
  (Signature, Checksum, NumEntries, PspDirSize) = struct.unpack('4L',PspDirTblRaw)
  PspDirectoryInfo ['PspDirSize'] = PspDirSize
  print "Psp Directory FV Size 0x%X" %PspDirSize

  #Check Signature
  if (Signature != 0x50535024):
    print "Psp Directory Table Signature Verify Fail"
    sys.exit(2)
  #Check CRC Checksum


  #Render & build structure
  #Read the whole Dir Table
  EntryInfoArray = []
  for i in range (NumEntries):
    EntryRaw = FileHandle.read (16)
    (Type, Size, Location) = struct.unpack ('LLQ', EntryRaw)
    if (Size != 0xFFFFFFFF):
      print "\t Type [0x%02X] Size [0x%08X] Location [0x%08X ~ 0x%08X] (%s)"  %(Type,Size,Location, Location + Size -1, getEntryName(Type))
      EntryInfo = {'Type':Type,'Size':Size,'RTOffset':Location, 'Description':getEntryName(Type), 'Offset':getOffsetInBin(biosSize, Location)}
    else:
      print "\t Type [0x%02X] VALUE [0x%08X] (%s)"  %(Type, Location, getEntryName(Type))
      #Ignore Value entry
      EntryInfo = {'Type':Type,'Value':Location, 'Description':getEntryName(Type)}

    EntryInfoArray.append (EntryInfo)
  PspDirectoryInfo['Entries'] = EntryInfoArray
  return PspDirectoryInfo

def OutPutPspDirXml (bios,Entries, xmlFileName):
  try:
    FileHandle = open (xmlFileName,'w')
  except:
    print "[Error]: Opening ", xmlFileName
    sys.exit(2)

  root = Element('PspDirectory')
  for entry in Entries:
    _entry = entry.copy()
    #Update RTM name to Blob
    if (IsEntry6Blob (_entry)):
      _entry["Description"] = "SecureBoot Bypass Blob"
      _entry["SubType"] = "Blob"
    #convert all numberic type to string, for tostring function only accept string
    for (k,v) in _entry.iteritems():
      if (type(v) == types.IntType or type(v) == types.LongType):
        _entry[k]=hex(v)
    entryElmt = SubElement (root, 'entry',_entry)
    if (entry['Type'] == 1) or (entry['Type'] == 3):
      SubElement (entryElmt, 'PspBootLoader', pspBootLoaderInfo(bios, entry))
    elif (entry['Type'] == 2):
      SubElement (entryElmt, 'pspSecureOs', pspSecureOsInfo(bios, entry))
    elif (entry['Type'] == 8):
      SubElement (entryElmt, 'SmuFw', smuFwInfo(bios,entry))

  print >>FileHandle, prettify(root)
def GetOutEntryFileName (entry):
  return "Typex%x_%s.bin" %(entry['Type'], getEntryShortName(entry['Type']))

def IsInRegion (offset, regionStart, regionSize):
  if  ((offset >= regionStart) and (offset <= regionStart + regionSize)):
    return 1
  else:
    return 0

def OutPutPspDirCfg (PspDirectoryInfo, cfgFileName):
  PspFvSizeFieldValue = PspDirectoryInfo ['PspDirSize'];
  try:
    FileHandle = open (cfgFileName,'w')
  except:
    print "[Error]: Opening ", cfgFileName
    sys.exit(2)
  #Get RTM entry
  for entry in PspDirectoryInfo['Entries']:
    if (entry['Type'] == 6):
      RtmEntry = entry
  # Set Default to one block
  TwoBlockFlag = 0
  #PspFvSizeFieldValue is invalid, blind set to One FV with 1M size
  if (PspFvSizeFieldValue == 0xFFFFFFFF) or (PspFvSizeFieldValue == 0):
    print >>FileHandle, "BIOS_IMAGE  INPUT_FILE = %s, PSP_FV_BASE=0x%X, PSP_FV_SIZE=0x%X, RTM_SIZE = 0x%X\n"\
     %(PspDirectoryInfo ['biosName'], PspDirectoryInfo ['PspDirOffset'], 0x100000, RtmEntry['Size'] )
  else:
    if (PspFvSizeFieldValue & 0x80000000):
      # Set Two FV flag
      TwoBlockFlag = 1
  #   1       7          8           8        8
  # +----+---------+-----------+----------+---------+
  # |FLAG|   RSV   | DYN BASE  | DYN SIZE | FixSIZE |
  # +----+---------+-----------+----------+---------+
      # Clear Flag field
      PspFvSizeFieldValue &= 0x7FFFFFFF
      # Get Dynamic & Fix FV information
      DynFvBase = ((PspFvSizeFieldValue & 0x00FF0000) >> 16) << 16
      DynFvSize = ((PspFvSizeFieldValue & 0x0000FF00) >> 8) << 16
      FixFvSize = ((PspFvSizeFieldValue & 0x000000FF) >> 0) << 16
      #Separate or Continual
      if (DynFvBase == 0):
        #Continual Blocks Format
        print >>FileHandle, "BIOS_IMAGE  INPUT_FILE = %s, PSP_FV_BASE=0x%X, FIXFV_SIZE=0x%X, DYNFV_SIZE=0x%X, RTM_SIZE = 0x%X\n"\
       %(PspDirectoryInfo ['biosName'], PspDirectoryInfo ['PspDirOffset'],  FixFvSize, DynFvSize, RtmEntry['Size'] )
      else:
        #Separate Blocks Format
        print >>FileHandle, "BIOS_IMAGE  INPUT_FILE = %s, FIXFV_BASE=0x%X, FIXFV_SIZE=0x%X, DYNFV_BASE=0x%X, DYNFV_SIZE=0x%X, RTM_SIZE = 0x%X\n"\
       %(PspDirectoryInfo ['biosName'], PspDirectoryInfo ['PspDirOffset'], FixFvSize, DynFvBase, DynFvSize, RtmEntry['Size'] )
    else:
    #BIOS_IMAGE  INPUT_FILE = Discovery.dbgX64.fd,  PSP_FV_BASE=0x50000, PSP_FV_SIZE=0x130000, RTM_SIZE = 0xCB000
    #RTM_SIZE will incorrect in if select use blob
      print >>FileHandle, "BIOS_IMAGE  INPUT_FILE = %s, PSP_FV_BASE=0x%X, PSP_FV_SIZE=0x%X, RTM_SIZE = 0x%X\n"\
     %(PspDirectoryInfo ['biosName'], PspDirectoryInfo ['PspDirOffset'], PspDirectoryInfo ['PspDirSize'], RtmEntry['Size'] )

  for entry in PspDirectoryInfo['Entries']:
    if ('Value' in entry):
        print >>FileHandle, "PSP_ENTRY TYPE=0x%x, VALUE=0x%x" %(entry ['Type'], entry ['Value'])
    else:
      #Default Output file name
      outputFileName = GetOutEntryFileName (entry)
      #Skip Output RTM Entry
      if (entry['Type'] == 6):
        if (not IsEntry6Blob (entry)):
          continue
      #Use constant name for RTM signature
      if (entry['Type'] == 7):
        outputFileName = "RTMSignature.bin"
      AddressFlag = 0
      # Set Address field required flag, if a entry NOT belong to any FV region
      if (TwoBlockFlag):
        if (DynFvBase == 0):
          if  (not IsInRegion(entry['Offset'], PspDirectoryInfo ['PspDirOffset'], FixFvSize+DynFvSize)):
            AddressFlag = 1
        else:
          if  ((not IsInRegion(entry['Offset'], PspDirectoryInfo ['PspDirOffset'], FixFvSize)) and \
               (not IsInRegion(entry['Offset'], DynFvBase, DynFvSize))):
            AddressFlag = 1
      else:
        if (not IsInRegion(entry['Offset'], PspDirectoryInfo ['PspDirOffset'],  PspDirectoryInfo ['PspDirSize'])):
          AddressFlag = 1
      #PSP_ENTRY FILE=PspNvram.bin,         TYPE=4,  OFFSET = 0x140000, Size = 0x8000
      if (AddressFlag):
        print >>FileHandle, "PSP_ENTRY TYPE=0x%x, FILE=%s, ADDRESS=0x%x" %(entry ['Type'], outputFileName, entry['Offset'])
      else:
        print >>FileHandle, "PSP_ENTRY TYPE=0x%x, FILE=%s" %(entry ['Type'], outputFileName)

def OutPutPspBinaries (bios,Entries):
  for entry in Entries:
    if (not 'Value' in entry):
      if (entry['Type'] == 7):
        #Use constant name for RTM signature
        outputFileName = "RTMSignature.bin"
      else:
        outputFileName = GetOutEntryFileName (entry)

      #slice the binary
      print "Output %s of BIOS [%x:%x]" %(outputFileName, entry['Offset'], entry['Offset'] + entry ['Size'] - 1)
      buffer = bios [entry['Offset']: entry['Offset'] + entry ['Size']]
      WriteBinaryFile (outputFileName, buffer)

def main ():
  global BiosList
  global PspList
  global Args

  print "BuildPspDirectory   Version "+ Version+"\n"
  #Parse arguments
  Args = ParseArg()

  if (Args.subcommand == 'bd' or Args.subcommand == 'bb'):
    print "Build information structure"
    # Find BIOS information and PSPInformation from the inputfile
    (BiosList, PspList) = ParsePspFile (Args.CfgFile)

    if ((BiosList == []) or (PspList == [])):
      return
    #Optimize the order of PspList (Global value)
    OptPspList()

    CalcPspEntryOffset()

    PspDirectory = BuildPspDir ()
    if (Args.subcommand == 'bd'):
      print "Generate PSP Directory binary", Args.PspDirFile
      WriteBinaryFile (Args.PspDirFile, PspDirectory)
      sys.exit(0)
    elif (Args.subcommand == 'bb'):
      print "Build BIOS image"
      InputBios, BiosSize, PspFvBase, PspFvSize, BiosRtmSize, PspFvSize2, PspFvBase2 = BiosList
      #Bios image is 4GB - size of BIOS image
      BiosBase = 0x100000000 - BiosSize
      # Read the Bios file
      BiosBinary = ReadBinaryFile (InputBios)

      #First update the PSPDirectory in the binary image
      BiosBinary = PatchBinary (BiosBinary, PspDirectory, PspFvBase, "PSPDirecory ")

      # Process each PSP entry
      for (PspFile, Type, Location, Size) in PspList:
        # Read PSP File
        if ((PspFile != "AUTO") and (Size != 0xFFFFFFFF)):
          PspBinary = ReadBinaryFile (PspFile)
          if (PspBinary == None):
            print "[Error] Reading %s\n" %PspFile
            sys.exit(2)
          # And patch the output image
          BiosBinary = PatchBinary (BiosBinary, PspBinary, getOffsetInBin(BiosSize,Location), PspFile+" "+hex(Type))
      print "Generate BIOS image [%s]" %Args.OutBiosImage
      WriteBinaryFile (Args.OutBiosImage, BiosBinary)

  elif (Args.subcommand == 'dp' or Args.subcommand == 'rp'):
    print "Dump BIOS Psp Directory from Vector[%s]" %(Args.Vector)
    PspDirectoryInfo = GetPspDirectory (Args.InBiosImage)
    if (Args.subcommand == 'dp'):
      if (Args.binary == True):
        print "Output  psp binaries"
        OutPutPspBinaries (PspDirectoryInfo['bios'],PspDirectoryInfo['Entries'])
      if (Args.xml == True):
        print "Output  PspDirInfo.xml"
        OutPutPspDirXml (PspDirectoryInfo['bios'],PspDirectoryInfo['Entries'], "PspDirInfo.xml")
      if (Args.directory == True):
        print "Output  PspDirectory.cfg"
        OutPutPspDirCfg (PspDirectoryInfo, "PspDirectory.cfg")


if __name__ == "__main__":
  main()

