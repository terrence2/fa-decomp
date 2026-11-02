// 0xcf4b0 do_ijmp_long (52 B, gap chunk) — v1 naked asm
extern char w28c_vTable[];

void __declspec(naked) w28c_ijmpLong(void)
{
    __asm {
        mov eax, [esi]
        lea esi, [esi+4]
        add esi, eax
        mov ax, [esi]
        lea esi, [esi+2]
        movzx ebx, al
        jmp [w28c_vTable + ebx*2]
        nop
        mov ax, [esi]
        lea esi, [esi+2]
        movsx ebx, ax
        mov esi, [ebx]
        mov ax, [esi]
        lea esi, [esi+2]
        movzx ebx, al
        jmp [w28c_vTable + ebx*2]
        nop
    }
}
