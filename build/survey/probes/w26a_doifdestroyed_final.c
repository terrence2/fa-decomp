// w26a_doifdestroyed @ rva 0xce684 (846212) do_ifdestroyed (40 B, no FPO).
// Hand-written-asm VM dispatch fragment (mid-function, entered by
// fallthrough from the previous chunk; no ret — control leaves through the
// vector_table jump). FA bytes (raw):
//   66 8b 06             mov ax,[esi]
//   8d 76 02             lea esi,[esi+2]
//   66 83 3d 8c 7c 50 00 00   cmp word ptr ds:0x507c8c, 0   (_destroyed)
//   74 05                je L1            (short)
//   0f bf c0             movsx eax,ax
//   03 f0                add esi,eax
// L1: 66 8b 06           mov ax,[esi]
//   8d 76 02             lea esi,[esi+2]
//   0f b6 d8             movzx ebx,al
//   ff 24 5d 58 3c 51 00 jmp dword ptr ds:[0x513c58 + ebx*2]   (vector_table)
//   2e 8b c0             (3 B trailing fragment, emitted verbatim)
extern char destroyed_t[];     /* _destroyed */
extern char vector_table_t[];  /* vector_table @0x513c58 */
__declspec(naked) void w26a_doifdestroyed(void)
{
    __asm {
        mov ax, word ptr [esi]
        lea esi, [esi+2]
        cmp word ptr [destroyed_t], 0
        je short L1
        movsx eax, ax
        add esi, eax
L1:     mov ax, word ptr [esi]
        lea esi, [esi+2]
        movzx ebx, al
        jmp dword ptr vector_table_t[ebx*2]
        _emit 0x2e
        _emit 0x8b
        _emit 0xc0
    }
}