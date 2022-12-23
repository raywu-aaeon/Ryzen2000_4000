//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file AmiGopPolicy.h
    AmiGopPolicy Header File.

**/

#ifndef _AMI_GOP_POLICY_H_
#define _AMI_GOP_POLICY_H_
#ifdef __cplusplus
extern "C" {
#endif

#define AMI_GOP_POLICY_VARIABLE_GUID \
    {0xc143929c, 0xbf5d, 0x423b, {0x99, 0x9b, 0xf, 0x2d, 0xd2, 0xb6, 0x1f, 0xf7}}

#pragma pack(1)

typedef struct _AMI_GOP_POLICY_SETUP_DATA
{
    UINT8   GopDeviceCount;
    UINT8   GopOutputCount;
} AMI_GOP_POLICY_SETUP_DATA;

#pragma pack()

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
