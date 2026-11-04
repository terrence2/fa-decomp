/* 0xd2848 @GRExec@4 (64 B): naked inline-asm escape — 16-bit word
 * pushes/pops of xv/yv/zv + dispatch through vector_table[ebx] (16-bit
 * stack-ABI wall). Single inline-asm retry; all refs carry relocations. */
extern unsigned short xv;     /* 0x518662 */
extern unsigned short yv;     /* 0x518664 */
extern unsigned short zv;     /* 0x518666 */
extern void *vector_table;    /* 0x513c58 */

__declspec(naked) void __stdcall w38a_grexec(int a)
{
    (void)a;
    __asm {
        pushad
        push word ptr [xv]
        push word ptr [yv]
        push word ptr [zv]
        mov esi, ecx
        mov ax, word ptr [esi]
        lea esi, [esi+0x2]
        movzx ebx, al
        call dword ptr [vector_table + ebx*2]
        pop word ptr [zv]
        pop word ptr [yv]
        pop word ptr [xv]
        popad
        ret
    }
}
