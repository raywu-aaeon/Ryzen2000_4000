CALCWr      MACRO   r:REQ, w:REQ
    xor     r, [w - 14*4]
    xor     r, [w - 8*4]
    xor     r, [w - 3*4]
    rol     r, 1
    mov     [w], r
            ENDM

CALCW       MACRO   r:REQ, w:REQ
    mov     r, [w - 16*4]
    CALCWr  r, w
            ENDM

S_ABC       MACRO   A, B, C, K:REQ
    ror     B, 2                        ; B >>>= 2
    mov     C, B                        ; C <- B >>> 2
    mov     B, A                        ; B <- A
    rol     A, 5                        ; A <<<= 5
    add     A, eax                      ; A += F(B, C, D) + E
    pop     eax                         ; eax <- Wi
    add     A, K                        ; A += K
    add     A, eax                      ; A += Wi
            ENDM

SHA1_R1     MACRO   A, B, C, D, E, K:REQ; F = BC + ~BD
    mov     eax, B                      ; eax <- B
    push    C
    not     eax                         ; eax <- ~B
    and     C, B                        ; C <- BC
    and     eax, D                      ; eax <- ~BD
    or      eax, C                      ; eax <- F(B, C, D)
    add     eax, E                      ; eax <- F(B, C, D) + E
    mov     E, D                        ; E <- D
    pop     D                           ; D <- C
    S_ABC   A, B, C, K
    CALCWr  eax, esp + 15*4
            ENDM

SHA1_R2     MACRO   A, B, C, D, E, K:REQ; F = B^C^D
    SHA1_R4 A, B, C, D, E, K
    CALCWr  eax, esp + 15*4
            ENDM

SHA1_R3     MACRO   A, B, C, D, E, K:REQ; F = B(C + D) + CD
    mov     eax, C                      ; eax <- C
    push    C
    or      eax, D                      ; eax <- C + D
    and     C, D                        ; C <- CD
    and     eax, B                      ; eax <- B(C + D)
    or      eax, C                      ; eax <- F(B, C, D)
    add     eax, E                      ; eax <- F(B, C, D) + E
    mov     E, D                        ; E <- D
    pop     D                           ; D <- C
    S_ABC   A, B, C, K
    CALCWr  eax, esp + 15*4
            ENDM

SHA1_R4     MACRO   A, B, C, D, E, K:REQ; F = B^C^D
    mov     eax, B
    xor     eax, C
    xor     eax, D                      ; eax <- F(B, C, D)
    add     eax, E                      ; eax += E
    mov     E, D                        ; E <- D
    mov     D, C                        ; D <- C
    S_ABC   A, B, C, K
            ENDM

SHA1RND     MACRO   SHA1_R, K:REQ
    or      ecx, 20
@@:
    SHA1_R  ebx, edx, esi, edi, ebp, K
    loop    @B
            ENDM

_Sha1Transform@8   PROC    USES    ebp ebx esi edi
    mov     esi, [esp + 24]             ; esi <- addr of M
    add     esp, -80*4
    mov     ecx, 10h
    lea     edi, [esp + ecx*4]
@@:
    mov     eax, [esi + ecx*4 - 4]
    bswap   eax
    mov     [esp + ecx*4 - 4], eax
    loop    @B
    mov     eax, [esp + 80*4 + 20]      ; eax <- addr of States
    mov     ebx, [eax]                  ; ebx <- S[0]
    mov     edx, [eax + 4]              ; edx <- S[1]
    mov     esi, [eax + 8]              ; esi <- S[2]
    mov     edi, [eax + 12]             ; edi <- S[3]
    mov     ebp, [eax + 16]             ; ebp <- S[4]
    SHA1RND SHA1_R1, 5a827999h
    SHA1RND SHA1_R2, 6ed9eba1h
    SHA1RND SHA1_R3, 8f1bbcdch
    CALCW   eax, esp + 16*4
    or      ecx, 3
@@:
    CALCW   eax, esp + 16*4 + ecx*4
    loop    @B
    SHA1RND SHA1_R4, 0ca62c1d6h
    mov     eax, [esp + 20]             ; eax <- addr of States
    add     [eax], ebx
    add     [eax + 4], edx
    add     [eax + 8], esi
    add     [eax + 12], edi
    add     [eax + 16], ebp
    ret     8
_Sha1Transform@8   ENDP

