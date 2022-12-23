;------------------------------------------------------------------------------
;
;
; Module Name:
;
;   SpiFlashAsm.nasm
;
; Abstract:
;
;   SpiFlash function
;
; Notes:
;
;------------------------------------------------------------------------------

    DEFAULT REL
    SECTION .text

;------------------------------------------------------------------------------
; VOID *
; EFIAPI
; SpiFlashAsmMfence (
;   VOID
;   );
;------------------------------------------------------------------------------
global ASM_PFX(SpiFlashAsmMfence)
ASM_PFX(SpiFlashAsmMfence):
    mfence
    ret