//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
#ifndef _AMI_USB_HC_MEM_RECORD_PROTOCOL_H_
#define _AMI_USB_HC_MEM_RECORD_PROTOCOL_H_

#define AMI_USB_HC_MEM_RECORD_PROTOCOL_GUID \
{0x3279a703, 0xba93, 0x4cbc, {0xad, 0x11, 0x5c, 0x2a, 0x82, 0xc9, 0x4a, 0x80}}

typedef struct _AMI_USB_HC_MEM_RECORD_PROTOCOL {

    EFI_PHYSICAL_ADDRESS        HcMemStart;
    UINTN                       MemTotalPages;

} AMI_USB_HC_MEM_RECORD_PROTOCOL;

#endif
//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
