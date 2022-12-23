//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file GnbHdaVerbTableLib.h
    This header file define North bridge HDA Verb Table Override  
    function and the necessary structures

*/
#ifndef  _AMI_GNB_HDA_VERB_TABLE_LIB_H   //To Avoid this header get compiled twice
#define  _AMI_GNB_HDA_VERB_TABLE_LIB_H

#pragma pack(push, 1)

//
// The content of AMI_AZALIA_VERB_TABLE_HEADER can be
// changed per your chipset SW design.
//

// HD Audio Codec table list
typedef struct _GNB_CODEC_VERB_TABLE_LIST {
  IN  UINT32           CodecId;             ///<  CodecID - Codec ID
  IN  UINTN            CodecTablePtr;       ///<  CodecTablePtr - Codec table pointer
} GNB_CODEC_VERB_TABLE_LIST;


/// HD Audio Codec table list
typedef struct _GNB_AGESA_CODEC_VERB_TABLE_LIST {
  IN  UINT32           CodecId;             ///<  CodecID - Codec ID
} GNB_AGESA_CODEC_VERB_TABLE_LIST;

VOID*
GnbHdaVerbTableOverride(
);
#pragma pack(pop)



#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
