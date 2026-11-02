// do_setlight @ rva 0xd0678 (36 B, gap chunk, no FPO) — interp do-handler:
// read word at [esi] -> movsx eax, set ebx = 4 (light slot id), call
// do_collision_info+0x14 core, read next word -> movzx bl, then tail-dispatch
// jmp dword ptr [ebx*2 + vector_table] (base-less sib-5d form; EBX carries
// the zero-extended command word). Ends in the jump — no ret. Naked
// asm escape (register-state protocol: esi data ptr, ebx dispatch cmd).
extern void doSetLgtCore(void);      /* do_collision_info + 0x14 */
extern void *setVT[];                /* vector_table */

void __declspec(naked) do_setlight_q(void)
{
    __asm {
        mov  ax, word ptr [esi]
        lea  esi, [esi+0x2]
        movsx eax, ax
        mov  ebx, 0x4
        call doSetLgtCore
        mov  ax, word ptr [esi]
        lea  esi, [esi+0x2]
        movzx ebx, al
        jmp  dword ptr setVT[ebx*2]
    }
}