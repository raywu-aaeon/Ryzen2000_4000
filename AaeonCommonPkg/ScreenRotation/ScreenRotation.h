//***********************************************************************
//*                                                                     *
//*                  Copyright (c) 1985-2021, AMI.                      *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

#ifndef __SCREEN_ROTATION_H__
#define __SCREEN_ROTATION_H__

#define SCREEN_ROTATION_GUID \
    {0xef9a6033, 0x6e54, 0x448c, 0xa3, 0x93, 0xee, 0xc4, 0xd6, 0x89, 0xdc, 0x62}
#define EFI_SHELL_PROTOCOL_GUID \
    {0x47C7B223, 0xC42A, 0x11D2, 0x8E, 0x57, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B}
#define EFI_SHELL2_0_FILE_GUID  \
	{ 0x6302d008, 0x7f9b, 0x4f30, 0x87, 0xac, 0x60, 0xc9, 0xfe, 0xf5, 0xda, 0x4e }

#define NORMAL          0
#define RIGHT_ROTATION  1
#define LEFT_ROTATION   2
#define REVERSION       3

typedef struct {
    UINT8  Direction;
} SCREEN_ROTATION_POLICY;

#endif
