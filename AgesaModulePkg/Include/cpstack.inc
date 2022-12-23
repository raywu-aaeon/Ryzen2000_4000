;*****************************************************************************
; AMD Generic Encapsulated Software Architecture
;
;  Workfile: cpstack.inc    $Revision$    $Date$
;
; Description: Code to setup and break down stack
;
;*****************************************************************************
;
; Copyright (C) 2008-2022 Advanced Micro Devices, Inc. All rights reserved.
;
;******************************************************************************

;============================================================================
;
; Define a  macro that allow the OEM to specify supported solutions in the
; cache-as-ram code. This will reduce the size of the assembled file.
; The macro will convert solutions into supported families.
;
;============================================================================

    .XLIST
    INCLUDE earlycpusupport.inc
    INCLUDE cpstackhooks.inc
    .LIST
    .586P
    .mmx

;======================================================================
; AMD_ENABLE_STACK_PRIVATE:  Setup a stack
;
;   In:
;       EBX  = Return address (preserved)
;
;   Out:
;       SS:ESP - Our new private stack location
;
;       EAX = AGESA_STATUS
;       EDX = Return status code if EAX contains a return code of higher
;             severity than AGESA_SUCCESS
;       ECX = Stack size in bytes
;
;   Requirements:
;       * This routine presently is limited to a max of 64 processor cores
;   Preserved:
;       ebx ebp
;   Destroyed:
;       eax, ecx, edx, edi, esi, ds, es, ss, esp
;       mmx0, mmx1, mmx5
;   Input Parameter:
;       STACK_AT_TOP
;              Indicate stack is on the top of cache as RAM.
;       STACK_AT_BOTTOM (default)
;              Indicate stack is at the bottom of cache as RAM.
;
;       BspStackSize (default: STACK_SIZE_64K)
;              could be STACK_SIZE_64K, STACK_SIZE_128K, STACK_SIZE_192K, STACK_SIZE_256K
;              N O T E: BspStackSize must be the same as the one in PspPlatformDriver.c (RESUME_BSP_STACK_SIZE)
;
;   Description:
; Fixed MTRR address allocation to cores:
; The BSP gets 64K of stack, Core0 of each node gets 16K of stack, all other cores get 4K.
; There is a max of 1 BSP, 7 core0s and 56 other cores.
; Although each core has it's own cache storage, they share the address space. Each core must
; be assigned a private and unique address space for its stack. To support legacy systems,
; the stack needs to be within the legacy address space (1st 1Meg). Room must also be reserved
; for the other legacy elements (Interrupt vectors, BIOS ROM, video buffer, etc.)
;
; 80000h                                        40000h                                      00000h
;     +----------+----------+----------+----------+----------+----------+----------+----------+
; 64K |          |          |          |          |          |          |          |          |  64K  ea
;  ea +----------+----------+----------+----------+----------+----------+----------+----------+
;     |                             MTRR 0000_0250 MTRRfix64K_00000                           |
;     +----------+----------+----------+----------+----------+----------+----------+----------+
;     |    3     |    2     |    1     |    0     |     0    |          |          |          | <-node
;     |  15..1   |  15..1   |  15..1   |  15..1   |     0    |          |          |          | <-core
;     +----------+----------+----------+----------+----------+----------+----------+----------+
;
; C0000h                       B0000h                      A0000h                      90000h                      80000h
;     +------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+
;16K  |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
; ea  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+
;     |              MTRR 0259 MTRRfix16K_A0000               |             MTRR 0258 MTRRfix16K_80000                |
;     +------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+
;     | > Dis|play B|uffer |   <  |      |      |      |      |      |      |      |      |      |   3  |   2  |   1  | <-node
;     | >   T| e  m |p o r |a r y |  B u |f f e |r   A |r e a<|      |      |      |      |      |   0  |   0  |   0  | <-core
;     +------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+
;
; E0000h                                            D0000h                                         C0000h
;     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
; 4K  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  4K  ea
;  ea +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
;     |  026B MTRRfix4K_D8000 | 026A MTRRfix4K_D0000  | 0269 MTRRfix4K_C8000  | 0268 MTRRfix4K_C0000  |
;     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
;     |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | >| V| I| D| E| O|  |B |I |O |S |  |A |r |e |a<|
;     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
;
; 100000h                                           F0000h                                          E0000h
;     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
;     |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  4K  ea
;     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
;     |  026F MTRRfix4K_F8000 | 026E MTRRfix4K_F0000  | 026D MTRRfix4K_E8000  | 026C MTRRfix4K_E0000  |
;     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
;     | >|MA|IN| B|IO|S |RA|NG|E |  |  |  |  |  |  |< | >|EX|TE|ND|ED| B|IO|S |ZO|NE|  |  |  |  |  |< |
;     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
;======================================================================
AMD_ENABLE_STACK_PRIVATE MACRO StackPosition, BspStackSize, BspStackAddr
  local AmdEnableStackExit
  local GoToVarMtrr

  IF ((BspStackSize NE STACK_SIZE_64K) AND (BspStackSize NE STACK_SIZE_128K) AND (BspStackSize NE STACK_SIZE_192K) AND (BspStackSize NE STACK_SIZE_256K) AND (BspStackSize NE STACK_SIZE_1M))
      jmp $ ; We only support 64K, 128K, 192K, 256K, 1M please check input parameter
  ENDIF

    ;   Note that SS:ESP will be default stack.  Note that this stack
    ;   routine will not be used after memory has been initialized.  Because
    ;   of its limited lifetime, it will not conflict with typical PCI devices.
    movd    mm0, ebx                    ; Put return address in a safe place
    movd    mm1, ebp                    ; Save some other user registers

    ; get node id and core id of current executing core
    GET_NODE_ID_CORE_ID                 ; Sets ESI[15,8]= Node#; ESI[7,0]= core# (relative to node)
    ; Note: ESI[31:24] are used for flags:  Unrecognized Family,  Is_Primary core,  Stack already established

    ; If Stack Base is located under 1M, limit it to the first 640K
    mov ebp, BspStackAddr
    .if (ebp < 0100000h)
      .if (ebp >= 0A0000h)
        mov edx, CPU_EVENT_STACK_BASE_OUT_OF_BOUNDS
        mov eax, AGESA_FATAL
        jmp AmdEnableStackExit
      .endif
    .endif

    ; STACK_SIZE_1M is not valid for systems where DRAM is not yet available at this timepoint.
    bt esi, FLAG_DRAM_AVAILABLE
    .if (!carry?)
      .if (BspStackSize EQ STACK_SIZE_1M)
        mov edx, CPU_EVENT_STACK_SIZE_INVALID
        mov eax, AGESA_FATAL
        jmp AmdEnableStackExit
      .endif
    .endif

    ; If we detected an unknown processor family or core combination, return AGESA_FATAL.
    .if (esi & (1 SHL FLAG_UNKNOWN_FAMILY))
      mov edx, CPU_EVENT_UNKNOWN_PROCESSOR_FAMILY
      mov eax, AGESA_FATAL
      jmp AmdEnableStackExit
    .elseif (esi & (1 SHL FLAG_CORE_NOT_IDENTIFIED))
      mov edx, CPU_EVENT_CORE_NOT_IDENTIFIED
      mov eax, AGESA_FATAL
      jmp AmdEnableStackExit
    .endif

    ; determine if stack is already enabled. We are using the DefType MSR for this determination.
    ; It is =0 after reset; CAR setup sets it to enable the MTRRs
    mov     eax, cr0                    ; Is cache enabled? (CD or NW bit set)
    CR0_MASK    TEXTEQU %((1 SHL CR0_CD) OR (1 SHL CR0_NW))
    .if (!(eax & CR0_MASK))
        mov     ecx, AMD_MTRR_DEFTYPE   ; MSR:0000_02FF
        _RDMSR                          ; Are either of the default types enabled? (MTRR_DEF_TYPE_EN + MTRR_DEF_TYPE_FIX_EN)
        MSR_MASK    TEXTEQU %((1 SHL MTRR_DEF_TYPE_EN)+(1 SHL MTRR_DEF_TYPE_FIX_EN))
        .if (eax & MSR_MASK)
            bts     esi, FLAG_STACK_REENTRY     ; indicate stack has already been initialized
        .endif
    .endif

    AMD_ENABLE_STACK_FAMILY_HOOK

    ; Init CPU MSRs for our init routines
    mov     ecx, MTRR_SYS_CFG           ; SYS_CFG
    _RDMSR
    bts     eax, MTRR_FIX_DRAM_MOD_EN   ; Turn on modification enable bit
    _WRMSR

    mov     eax, esi
    bt      eax, FLAG_STACK_REENTRY     ; Is this a 2nd entry?
    .if (!carry?)                       ;   On a re-entry, do not clear MTRRs or reset TOM; just reset the stack SS:ESP
        bt      eax, FLAG_IS_PRIMARY    ;   Is this core the primary in a compute unit?
        .if (carry?)                    ;     Families using shared groups do not need to clear the MTRRs since that is done at power-on reset
            ;  Note: Relying on MSRs to be cleared to 0's at reset for families w/shared cores
            ; Clear all variable and Fixed MTRRs for non-shared cores
            mov     ecx, AMD_MTRR_VARIABLE_BASE0
            xor     eax, eax
            xor     edx, edx
            .while (cl != 10h)                  ; Variable MTRRphysBase[n] and MTRRphysMask[n]
                _WRMSR
                inc     cl
            .endw
            mov     cx, AMD_MTRR_FIX64k_00000   ; MSR:0000_0250
            _WRMSR
            mov     cx, AMD_MTRR_FIX16k_80000   ; MSR:0000_0258
            _WRMSR
            mov     cx, AMD_MTRR_FIX16k_A0000   ; MSR:0000_0259
            _WRMSR
            mov     cx, AMD_MTRR_FIX4k_C0000    ; Fixed 4Ks: MTRRfix4K_C0000 to MTRRfix4K_F8000
            .while (cl != 70h)
                _WRMSR
                inc     cl
            .endw

        .endif                          ;   End Is_Primary
    .endif                              ; End Stack_ReEntry

    ; Clear IORRs (C001_0016-19) and TOM2(C001_001D) for all cores
    xor     eax, eax
    xor     edx, edx
    mov     ecx, IORR_BASE              ; MSR:C001_0016 - 0019
    .while (cl != 1Ah)
        _WRMSR
        inc     cl
    .endw

    ; setup MTTRs for stacks
    ;   A speculative read can be generated by a speculative fetch mis-aligned in a code zone
    ;    or due to a data zone being interpreted as code. When a speculative read occurs outside a
    ;    controlled region (intentionally used by software), it could cause an unwanted cache eviction.
    ;   To prevent speculative reads from causing an eviction, the unused cache ranges are set
    ;    to UC type. Only the actively used regions (stack, heap) are reflected in the MTRRs.
    ;    Note: some core stack regions will share an MTRR since the control granularity is much
    ;    larger than the allocated stack zone. The allocation algorithm must account for this 'extra'
    ;    space covered by the MTRR when parseling out cache space for the various uses. In some cases
    ;    this could reduce the amount of EXE cache available to a core. see cpuCacheInit.c
    ;
    ; Outcome of this block is that:   (Note the MTRR map at the top of the file)
    ;   ebp - start address of stack block
    ;   ebx - [31:16] - MTRR MSR address
    ;       - [15:8]  - slot# in MTRR register
    ;       - [7:0]   - block size in #4K blocks
    ; review: ESI[31:24]=Flags; SI[15,8]= Node#; SI[7,0]= core# (relative to node)
    ;
    mov     eax, esi                    ; Load Flags, node, core
    .if (al == 0)                       ; Is a core 0?
        .if (ah == 0)                   ; Is Node 0? (BSP)
            bt esi, FLAG_DRAM_AVAILABLE
            .if (carry?)              
              ; a) For stack located under 1M, use Fixed MTRRs
              .if (ebp < 0100000h)
                ; a.i) Use Fixed 0250h and possibly 0258h
                .if (ebp < 080000h)
                  ; Calculate starting block #
                  mov ecx, ebp
                  and ecx, 0F0000h
                  shr ecx, 16

                  ; Calculate # of 64K blocks to fill
                  mov bl, (BspStackSize / 10000h)
                  mov ch, bl

                  ; Calculate end block #
                  add ch, cl

                  ; bl = Number of 64K blocks
                  ; cl = Start block #
                  ; ch = End block #
                  .if (cl < 4)
                    .if (ch <= 4)
                      ;
                      ; a.i.i) if Start Block and End Block are within the lower 32 bits of MTRR
                      ;
                      mov edi, WB_DRAM_TYPE
                      .while (bl > 1)
                        shl edi, 8
                        or edi, WB_DRAM_TYPE
                        dec bl
                      .endw
                      shl cl, 3
                      shl edi, cl

                      mov ecx, AMD_MTRR_FIX64k_00000
                      _RDMSR
                      or eax, edi
                      _WRMSR
                    .else
                      ;
                      ; a.i.ii) if Start Block and End Block spans upper and lower bits of MTRR
                      ;
                      ; bh = number of blocks that needs to be set in the lower 32 bits
                      mov bh, 4
                      sub bh, cl

                      ; Store number of remaining blocks to be set in upper 32 bits in ecx [24:16]
                      ror ecx, 16
                      mov cl, bl
                      sub cl, bh
                      rol ecx, 16

                      mov edi, WB_DRAM_TYPE
                      .while (bh > 1)
                        shl edi, 8
                        or edi, WB_DRAM_TYPE
                        dec bh
                      .endw

                      ; transfer number of blocks to bs set in the upper 32 bits to ebx
                      mov ebx, ecx

                      ; move to the correct Start block position
                      shl cl, 3
                      shl edi, cl

                      mov ecx, AMD_MTRR_FIX64k_00000
                      _RDMSR
                      or eax, edi

                      mov edi, WB_DRAM_TYPE
                      ; Retrieve number of remaining blocks to be set in the upper 32 bits of MTRR
                      ror ebx, 16
                      .while (bl > 1)
                        shl edi, 8
                        or edi, WB_DRAM_TYPE
                        dec bl
                      .endw
                      or edx, edi
                      _WRMSR
                    .endif
                  .else
                    .if (ch <= 8)
                      ;
                      ; a.i.iii) if Start Block and End Block are within the upper 32 bits of MTRR
                      ;
                      sub cl, 4

                      mov edi, WB_DRAM_TYPE
                      .while (bl > 1)
                        shl edi, 8
                        or edi, WB_DRAM_TYPE
                        dec bl
                      .endw

                      shl cl, 3
                      shl edi, cl

                      mov ecx, AMD_MTRR_FIX64k_00000
                      _RDMSR
                      or edx, edi
                      _WRMSR
                    .else
                      ;
                      ; a.i.iv) if Start Block and End Block spans multiple MTRRs
                      ;
                      ; bh = Number of blocks that need to be set in MSR0000_0250
                      mov bh, 8
                      sub bh, cl

                      ; Store number of remaining blocks to be set in MSR0000_0258 in ebx[24:16]
                      mov al, bl
                      sub al, bh
                      ror ebx, 16
                      mov bx, ax
                      rol ebx, 16

                      mov edi, WB_DRAM_TYPE
                      .while (bh > 1)
                        shl edi, 8
                        or edi, WB_DRAM_TYPE
                        dec bh
                      .endw

                      shl cl, 3
                      shl edi, cl

                      ; Since the max size for stack under 1M is 256K, if the start block and end block
                      ; spans multiple MTRRs, then only upper bits of MSR250 needs to be set
                      mov ecx, AMD_MTRR_FIX64k_00000
                      _RDMSR
                      or edx, edi
                      _WRMSR

                      ; Retrieve number of blocks to be set in MSR0000_0258
                      ror ebx, 16
                      ; bl = Number of 16K blocks to be set in the lower 32 bits of MSR0000_0258
                      shl bl, 2
                      mov bh, bl
                      ; bh = Number of 16K blocks to be set in the upper 32 bits of MSR0000_0258
                      sub bh, 4

                      mov edi, WB_DRAM_TYPE
                      .if (bl > 4)
                        mov bl, 4
                      .endif

                      .while (bl > 1)
                        shl edi, 8
                        or edi, WB_DRAM_TYPE
                        dec bl
                      .endw

                      mov ecx, AMD_MTRR_FIX16k_80000
                      _RDMSR
                      or eax, edi

                      .if (bh == 0)
                        xor edi, edi
                      .else
                        mov edi, WB_DRAM_TYPE
                        ; If number of slots exceeds 4, ignore the remaining since we are limiting stack within 640K
                        .if (bh > 4)
                          mov bh, 4
                        .endif
                      .endif
                      .while (bh > 1)
                        shl edi, 8
                        or edi, WB_DRAM_TYPE
                        dec bh
                      .endw

                      or edx, edi
                      _WRMSR

                    .endif
                  .endif
                .else
                  ; a.ii) Use Fixed 258h

                  ; Calculate start block #
                  mov ecx, ebp
                  and ecx, 01F000h
                  shr ecx, 14

                  ; Calculate # of 16K blocks to fill
                  mov bl, (BspStackSize / 4000h)
                  mov ch, bl

                  ; Calculate end block #
                  add ch, cl

                  ; bl = Number of 16K blocks
                  ; cl = Start block #
                  ; ch = End block #
                  .if (cl < 4)
                    .if (ch <= 4)
                      ;
                      ; a.ii.i) if Start Block and End Block are within the lower 32 bits of MTRR
                      ;
                      mov edi, WB_DRAM_TYPE
                      .while (bl > 1)
                        shl edi, 8
                        or edi, WB_DRAM_TYPE
                        dec bl
                      .endw

                      mov ecx, AMD_MTRR_FIX16k_80000
                      _RDMSR
                      or eax, edi
                      _WRMSR
                    .else
                      ;
                      ; a.ii.ii) if Start Block and End Block spans both the upper and lower 32 bits of the MTRR
                      ;
                      ; bh = number of blocks to be set in the lower 32 bits
                      mov bh, 4
                      sub bh, cl

                      ; store number of remaining blocks to be set in the upper 32 bits in ecx[26:16]
                      ror ecx, 16
                      mov cl, bl
                      sub cl, bh
                      rol ecx, 16

                      mov edi, WB_DRAM_TYPE
                      .while (bh > 1)
                        shl edi, 8
                        or edi, WB_DRAM_TYPE
                        dec bh
                      .endw

                      shl cl, 3
                      shl edi, cl

                      ; transfer number of blocks to bs set in the upper 32 bits to ebx
                      mov ebx, ecx

                      mov ecx, AMD_MTRR_FIX16k_80000
                      _RDMSR
                      or eax, edi

                      mov edi, WB_DRAM_TYPE
                      ; Retrieve number of remaning blocks to be set in the upper 32 bits
                      ror ebx, 16
                      .while (bl > 1)
                        shl edi, 8
                        or edi, WB_DRAM_TYPE
                        dec bl
                      .endw

                      or edx, edi
                      _WRMSR

                    .endif
                  .else
                    ;
                    ; a.ii.iii) if Start Block and End Block are within the upper 32 bits of the MTRR
                    ;
                    mov edi, WB_DRAM_TYPE
                    .while (bl > 1)
                      shl edi, 8
                      or edi, WB_DRAM_TYPE
                      dec bl
                    .endw

                    mov ecx, AMD_MTRR_FIX16k_80000
                    _RDMSR
                    or edx, edi
                    _WRMSR
                  .endif
                .endif

                ; Set ebx with the correct value for later use
                mov ebx, (BspStackSize / 1000h)
                jmp GoToVarMtrr
              .else
                ; b. If stack is located above 1M, use variable MTRRs
                mov ebx, (BspStackSize / 1000h)
                jmp GoToVarMtrr
              .endif
            .else
              ; Is BSP, assigning stack as specified by BspStackSize
              mov     ebx, ((AMD_MTRR_FIX64k_00000 SHL 16) + (BSP_CACHE_TYPE_POSITION SHL 8) + (BspStackSize  / 1000h))
              mov     ebp, BSP_STACK_BASE_ADDR
            .endif
        .else   ; node 1 to 7, core0
            ; Is a Core0 of secondary node, assign 16K stacks
            mov     bx, AMD_MTRR_FIX16k_80000
            shl     ebx, 16             ;
            dec     ah                  ; index from 0
            mov     bh, ah              ; Node# is used as slot#
            mov     bl, (CORE0_STACK_SIZE / 1000h)
            mov     al, ah              ; Base = (Node# * Size);
            mul     bl                  ;
            movzx   eax, ax             ;
            shl     eax, 12             ; Expand back to full byte count (* 4K)
            add     eax, CORE0_STACK_BASE_ADDR
            mov     ebp, eax
        .endif
    .else    ;core 1 thru core 15
        ; Is core 1-15 of any node, assign 4K stacks
        mov     al, 16                  ; CoreIndex = ( (Node# * 16) ...
        mul     ah                      ;
        mov     bx, si                  ;
        dec     bl                      ; account for core 0 on P1, etc
        add     al, bl                  ;         ...  + Core#);

        mov     bx, AMD_MTRR_FIX64k_00000
        shl     ebx, 16                 ;
        mov     bh, al                  ; Slot# = (CoreIndex / 16) + 4;
        shr     bh, 4                   ;
        add     bh, (BspStackSize / 10000h + BSP_CACHE_TYPE_POSITION)
        mov     bl, (CORE1_STACK_SIZE / 1000h)

        mul     bl                      ; Base = ( (CoreIndex * Size) ...
        movzx   eax, ax                 ;
        shl     eax, 12                 ; Expand back to full byte count (* 4K)
        add     eax, (BSP_STACK_BASE_ADDR + BspStackSize) ;     ...   + Base_Addr);
        mov     ebp, eax
    .endif

    ; Now set the MTRR. Add this to already existing settings (don't clear any MTRR)
    ; Set lower 32 bits of MTRR
    mov     edi, WB_DRAM_TYPE           ; Load Cache type in 1st slot
    mov     cl, bl                      ; block size in #64K blocks
    shr     cl, 4
    .if (cl > 4)
        jmp $                           ; We do NOT support size larger than 256K
    .endif
    .while (cl > 1)
        shl edi, 8
        or  edi, WB_DRAM_TYPE
        dec cl
    .endw
    mov     cl, bh                      ; ShiftCount =  ((slot#   ...
    .if (cl > 3)
        mov edi, 0
    .else
        shl cl,  3                      ;   ...  * 8);
        shl edi, cl                     ; Cache type is now in correct position
    .endif
    ror     ebx, 16                     ; Get the MTRR address
    movzx   ecx, bx                     ;
    rol     ebx, 16                     ; Put slot# & size back in BX
    _RDMSR                              ; Read-modify-write the MSR
    or      eax, edi                    ;

    ; Set upper 32 bits of MTRR
    mov     cl, bl
    add     cl, 0Fh
    shr     cl, 4
    dec     cl
    add     cl, bh
    mov     ch, cl
    .if (cl >= 4)
        .if (bh >= 4)
            mov cl, bh
        .else
            mov cl, 4
        .endif
        sub ch, cl
        sub cl,  4
        mov edi, WB_DRAM_TYPE
        .while (ch >= 1)
           shl edi, 8
           or  edi, WB_DRAM_TYPE
           dec ch
        .endw
        shl cl, 3
        shl edi, cl
    .else
        mov edi, 0
    .endif
    ror     ebx, 16                     ; Get the MTRR address
    movzx   ecx, bx                     ;
    rol     ebx, 16                     ; Put slot# & size back in BX
    or      edx, edi                    ;
    _WRMSR                              ;

GoToVarMtrr:
    bt      esi, FLAG_IS_PRIMARY        ; Is this a primary core?
    .if (carry?)
        bt      esi, FLAG_DRAM_AVAILABLE ; Is system DRAM initialized?
        .if (carry?)
            mov    ecx, TOP_MEM         ; Read the top of memory below 4GB
            _RDMSR
            mov    edi, eax             ; EDI = top of memory below 4GB
            xor    esp, esp             ; Initialize DRAM base address to 0
            mov    ecx, AMD_MTRR_VARIABLE_BASE0 ; Start with VarMtrr0
            .while ((edi != 0) && (ecx < AMD_MTRR_VARIABLE_BASE6)) ; Loop until all set bits are accounted for or we run out of mtrrs
                mov    eax, esp         ; EAX = region base
                mov    al, MTRR_TYPE_WB ; WB type
                xor    edx, edx         ; Only describing below 4GB
                _WRMSR                  ; Apply var mtrr base
                inc    cx               ; Set ECX to var mtrr limit register
                bsr    edx, edi         ; Find MSb
                btr    edi, edx         ; Mark it as accounted for
                xor    eax, eax         ; EAX = 0
                bts    eax, edx         ; EAX = region size
                mov    edx, esp         ; EDX = current region base
                add    edx, eax         ; EDX = next region base
                mov    esp, edx         ; ESP = next region base
                neg    eax              ; EAX = lower 32 bits of the mask required for this region's size
                bts    eax, VMTRR_VALID ; Set the valid bit
                mov    edx, edi         ; Save EDI to EDX
                movd   edi, mm5         ; Load pointer to Family Info Struc
                bswap  ecx              ; Save MTRR address to ECX[31:16]
                mov    cl, [edi].CPU_FAMILY_INFO.SIZE_ADDRESS_BUS ; CL = number of address bits for this family
                mov    edi, edx         ; Restore EDI
                xor    edx, edx         ; EDX = 0
                .if (cl < 64)
                    sub    cl, 32       ; CL = number of valid address bits between [63:32]
                    inc    dx           ; EDX = 1
                    shl    edx, cl      ;
                .endif
                dec    edx              ; EDX = Upper half of the address mask for this family
                xor    cl, cl           ; Restore CL
                bswap  ecx              ; Restore ECX
                _WRMSR                  ; Enable the var mtrr
                inc    cx               ; Point to next var mtrr base
            .endw
        .endif
    .endif

    ; Enable MTRR defaults as UC type
    mov     ecx, AMD_MTRR_DEFTYPE       ; MSR:0000_02FF
    _RDMSR                              ; Read-modify-write the MSR
    bts     eax, MTRR_DEF_TYPE_EN       ; MtrrDefTypeEn
    bts     eax, MTRR_DEF_TYPE_FIX_EN   ; MtrrDefTypeFixEn
    _WRMSR

    ; Close the modification window on the Fixed MTRRs
    mov     ecx, MTRR_SYS_CFG           ; MSR:0C001_0010
    _RDMSR
    bts     eax, MTRR_FIX_DRAM_EN       ; MtrrFixDramEn
    bts     eax, MTRR_VAR_DRAM_EN       ; variable MTRR enable bit
    btr     eax, MTRR_FIX_DRAM_MOD_EN   ; Turn off modification enable bit
    _WRMSR

    ; Enable caching in CR0
    mov     eax, CR0                    ; Enable WT/WB cache
    btr     eax, CR0_PG                 ; Make sure paging is disabled
    btr     eax, CR0_CD                 ; Clear CR0 NW and CD
    btr     eax, CR0_NW
    mov     CR0, eax

    ; Use the Stack Base & size to calculate SS and ESP values
    ; review:
    ;       esi[31:24]=Flags; esi[15,8]= Node#; esi[7,0]= core# (relative to node)
    ;       ebp - start address of stack block
    ;       ebx - [31:16] - MTRR MSR address
    ;           - [15:8]  - slot# in MTRR register
    ;           - [7:0]   - block size in #4K blocks
    ;
    mov     esp, ebp                    ; Initialize the stack pointer
    mov     edi, esp                    ; Copy the stack start to edi
    bt      esi, FLAG_DRAM_AVAILABLE

    .if (!carry?)
      movzx   bx, bl
      movzx   ebx, bx                     ; Clear upper ebx, don't need MSR addr anymore
    .endif
    shl     ebx, 12                     ; Make size full byte count (* 4K)
    IFNB <StackPosition>
        IF (StackPosition EQ STACK_AT_BOTTOM)
            mov ax, si
            .if (al == 0)               ; Only BSC needs to cut its CAR in half for PEI RAM
                shr   ebx, 1            ; If stack is at the bottom of CAR, divide size by 2
            .endif
        ENDIF
    ENDIF
    add     esp, ebx                    ; Set the Stack Pointer as full linear address
    sub     esp, 4
    ;
    ; review:
    ;       esi[31:24]=Flags; esi[15,8]= Node#; esi[7,0]= core# (relative to node)
    ;       edi - 32b start address of stack block
    ;       ebx - size of stack block
    ;       esp - 32b linear stack pointer
    ;

    ; Determine mode for SS base;
    mov     ecx, CR0                    ; Check for 32-bit protect mode
    bt      ecx, CR0_PE                 ;
    .if (!carry?)                       ; PE=0 means real mode
        mov     cx, cs                  ;
        .if (cx >= 0D000h)              ; If CS >= D000, it's a real mode segment. PM selector would be 08-> 1000
            ; alter SS:ESP for 16b Real Mode:
            mov     eax, edi            ;
            shr     eax, 4              ;   Create a Real Mode segment for ss, ds, es
            mov     ss, ax              ;
            mov     ds, ax              ;
            mov     es, ax              ;
            shl     eax, 4              ;
            sub     edi, eax            ;   Adjust the clearing pointer for Seg:Offset mode
            mov     esp, ebx            ;   Make SP an offset from SS
            sub     esp, 4              ;
        .endif                          ; endif
    ; else
    ;   Default is to use Protected 32b Mode
    .endif
    IFNB <StackPosition>
        IF (StackPosition EQ STACK_AT_BOTTOM)
            mov ax, si
            .if (al == 0)
                shl   ebx, 1            ; restore the size of CAR
            .endif
        ENDIF
    ENDIF
    ;
    ; Clear The Stack
    ;   Now that we have set the location and the MTRRs, initialize the cache by
    ;   reading then writing to zero all of the stack area.
    ; review:
    ;       ss  - Stack base
    ;       esp - stack pointer
    ;       ebx - size of stack block
    ;       esi[31:24]=Flags; esi[15,8]= Node#; esi[7,0]= core# (relative to node)
    ;       edi -  address of start of stack block
    ;
    shr     ebx, 2                      ;
    mov     ecx, ebx                      ; set cx for size count of DWORDS

    ; Check our flags - Don't clear an existing stack
    .if ( !(esi & (1 SHL FLAG_STACK_REENTRY)) )
        cld
        mov     esi, edi
        rep     lods DWORD PTR [esi]    ; Pre-load the range
        xor     eax, eax
        mov     ecx, ebx
        mov     esi, edi                ; Preserve base for push on stack
        rep     stos DWORD PTR [edi]    ; Clear the range
        mov     DWORD PTR [esp], 0ABCDDCBAh ; Put marker in top stack dword
        shl     ebx, 2                  ; Put stack size and base
        push    ebx                     ;  in top of stack
        push    esi

        mov     ecx, ebx                ; Return size of stack in bytes
        mov     eax, AGESA_SUCCESS      ; eax = AGESA_SUCCESS : no error return code
    .else
        movzx   ecx, cx
        shl     ecx, 2                  ; Return size of stack, in bytes
        mov     edx, CPU_EVENT_STACK_REENTRY
        mov     eax, AGESA_WARNING      ; eax = AGESA_WARNING (Stack has already been set up)
    .endif

AmdEnableStackExit:
    movd        ebx, mm0                ; Restore return address
    movd        ebp, mm1
ENDM

;======================================================================
; AMD_DISABLE_STACK_PRIVATE:  Destroy the stack inside the cache. This routine
;                             should only be executed on the BSP
;
;   In:
;       none
;
;   Out:
;       EAX = AGESA_SUCCESS
;
;   Preserved:
;       ebx
;   Destroyed:
;       eax, ecx, edx, esp, mmx5
;======================================================================
AMD_DISABLE_STACK_PRIVATE MACRO

    mov     esp, ebx                    ; Save return address

    ; get node/core/flags of current executing core
    GET_NODE_ID_CORE_ID                 ; Sets ESI[15,8]= Node#; ESI[7,0]= core# (relative to node)

    ; Turn on modification enable bit
    mov     ecx, MTRR_SYS_CFG           ; MSR:C001_0010
    _RDMSR
    bts     eax, MTRR_FIX_DRAM_MOD_EN   ; Enable modifications
    _WRMSR

    ; Set lower 640K MTRRs for Write-Back memory caching
    mov     ecx, AMD_MTRR_FIX64k_00000
    mov     eax, 1E1E1E1Eh
    mov     edx, eax
    _WRMSR                              ; 0 - 512K = WB Mem
    mov     ecx, AMD_MTRR_FIX16k_80000
    _WRMSR                              ; 512K - 640K = WB Mem

    ; Turn off modification enable bit
    mov     ecx, MTRR_SYS_CFG           ; MSR:C001_0010
    _RDMSR
    btr     eax, MTRR_FIX_DRAM_MOD_EN   ; Disable modification
    _WRMSR

    AMD_DISABLE_STACK_FAMILY_HOOK       ; Re-Enable 'normal' cache operations

    mov     ebx, esp                    ; restore return address (ebx)
    xor     eax, eax

ENDM

