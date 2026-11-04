// w35D_ce6ac_v8: do_no_overlap @ rva 0xce6ac — v6 with the three 16-B
// spelled movzx/movsx widened to the 32-B register forms FA actually encodes
// (0f b6 d8 = movzx ebx,al — NO 66; 0f bf c8 = movsx ecx,ax), and the two
// jumps spelled as FA's sib-45 indexed form ff 24 5d (jmp [vt_tab + ebx*2])
// instead of v6's ff 25 moffs (1 B short each). Cancellation: -3 (66s) -2
// (moffs shorts) = FA's 72 B exactly, zero patches.
extern unsigned char w35d_no_overlap;
extern unsigned char w35d_detail;
extern unsigned long w35d_vector_table;

void __declspec(naked) do_no_overlap(void)
{
    __asm {
        L1:
        mov ax, word ptr [esi]
        lea esi, [esi+2]
        mov word ptr [w35d_no_overlap], ax
        mov ax, word ptr [esi]
        lea esi, [esi+2]
        movzx ebx, al
        jmp dword ptr [w35d_vector_table + ebx*2]
        mov ax, word ptr [esi]
        lea esi, [esi+2]
        movsx ecx, ax
        mov ax, word ptr [esi]
        lea esi, [esi+2]
        cmp word ptr [w35d_detail], ax
        jae L4
        add esi, ecx
        L4:
        mov ax, word ptr [esi]
        lea esi, [esi+2]
        movzx ebx, al
        jmp dword ptr [w35d_vector_table + ebx*2]
        mov eax, eax
    }
}