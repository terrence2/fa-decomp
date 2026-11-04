/* 0xc4f9c _BuildSelfModifyCode@0 0x74 — naked _emit transcription */
extern unsigned short w43D_smf;   /* _dvbuf+0x3c0 */
extern unsigned long w43D_dvt;    /* _dvbuf+0x3c2 (table ptr) */
extern unsigned long w43D_dcd;    /* _dvbuf+0x3de (code ptr) */
extern void __fastcall w43D_dnb(unsigned short c);

void __declspec(naked) w43D_bsmcq(void)
{
    __asm {
        _emit 0x53                          ; push ebx
        _emit 0x56                          ; push esi
        _emit 0x57                          ; push edi
        _emit 0x55                          ; push ebp
        cmp word ptr [w43D_smf], 0
        jne L_pop
        mov ebx, OFFSET w43D_dvt
        mov edi, OFFSET w43D_dcd
        _emit 0x33
        _emit 0xC9                          ; xor ecx, ecx
L_head:
        _emit 0x89
        _emit 0x3B                          ; mov [ebx], edi
        _emit 0x83
        _emit 0xC3
        _emit 0x04                          ; add ebx, 4
        or ecx, ecx
        jne L_body2
        _emit 0xC6
        _emit 0x07
        _emit 0x03                          ; mov byte ptr [edi], 3
        _emit 0x47                          ; inc edi
        _emit 0xC6
        _emit 0x07
        _emit 0xFA                          ; 0xfa
        _emit 0x47
        _emit 0xC6
        _emit 0x07
        _emit 0xC3                          ; 0xc3
        _emit 0x47
        _emit 0x41                          ; inc ecx
        jmp L_head
        _emit 0xEB
        _emit 0x32                          ; dead jmp -> flag store
L_body2:
        cmp ecx, 0xff
        jae L_last
        _emit 0x8A
        _emit 0xC1                          ; mov al, cl
        _emit 0x24
        _emit 0xF0                          ; and al, 0xf0
        _emit 0xC0
        _emit 0xE8
        _emit 0x04                          ; shr al, 4
        call w43D_dnb
        _emit 0x8A
        _emit 0xC1
        _emit 0x24
        _emit 0x0F                          ; and al, 0x0f
        call w43D_dnb
        _emit 0xC6
        _emit 0x07
        _emit 0xC3
        _emit 0x47
        _emit 0x41
        jmp L_head
        _emit 0xEB
        _emit 0x0C                          ; dead jmp -> flag store
L_last:
        _emit 0xC6
        _emit 0x07
        _emit 0xA5
        _emit 0x47
        _emit 0xC6
        _emit 0x07
        _emit 0xA5
        _emit 0x47
        _emit 0xC6
        _emit 0x07
        _emit 0xC3
        _emit 0x47
        mov word ptr [w43D_smf], 1
L_pop:
        pop ebp
        pop edi
        pop esi
        pop ebx
        ret
    }
}
