// _OBJNextAliasForMulti@0 @ rva 0x8f930 — post-decrement the alias counter; CL
//   folds any C form to mem-dec (66 ff 0d), FA needs the 16-bit reg copies
//   (probes d150-d171 fold, d186 asm exact)
extern char commentType[];
void __declspec(naked) __stdcall OBJNextAliasForMulti_q(void)
{
    __asm
    {
        mov cx, word ptr [commentType + 0x864]
        mov ax, cx
        dec cx
        mov word ptr [commentType + 0x864], cx
        ret
    }
}
