// do_sfcal_long @ rva 0xce658 (44 B, gap chunk, no FPO) — v1 naked asm
// (wave-28 do_ijmp_long recipe: VM dispatch, call/jmp via vector_table[ebx*2])
extern char w30b_vt[];                    /* vector_table */

void __declspec(naked) w30b_sfl(void)
{
    __asm {
        mov eax, [esi]
        lea esi, [esi+4]
        push esi
        add esi, eax
        mov ax, [esi]
        lea esi, [esi+2]
        movzx ebx, al
        call [w30b_vt + ebx*2]
        pop esi
        mov ax, [esi]
        lea esi, [esi+2]
        movzx ebx, al
        jmp [w30b_vt + ebx*2]
    }
}