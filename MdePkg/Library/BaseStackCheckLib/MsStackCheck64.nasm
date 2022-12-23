;------------------------------------------------------------------------------
; Copyright (c) 2020-2021, American Megatrends International LLC.
;
;------------------------------------------------------------------------------

    DEFAULT REL
    SECTION .text

extern ASM_PFX(__report_gsfailure)
extern ASM_PFX(__security_cookie)
global ASM_PFX(__security_check_cookie)
ASM_PFX(__security_check_cookie):
    cmp     rcx, [ASM_PFX(__security_cookie)]
    ;use jump to preserve offending function return address
    jne     ASM_PFX(__report_gsfailure)
    ret

