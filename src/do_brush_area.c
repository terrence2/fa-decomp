// w26a_dobrush @ rva 0xd0df7 (850687) do_brush_area (38 B, no FPO).
// Hand-written-asm VM dispatch fragment (mid-function; entered by
// fallthrough; leaves through the vector_table jump). FA bytes (raw):
//   66 8b 06             mov ax,[esi]
//   8d 76 02             lea esi,[esi+2]
//   66 a3 f0 89 51 00    mov moffs16 ds:0x5189f0, ax   (source_vertex_ptr+4)
//   0f b7 c8             movzx ecx,ax
//   bf cc 39 51 00       mov edi, 0x5139cc             (vbuf2)
//   f3 a5                rep movsd
//   66 8b 06             mov ax,[esi]
//   8d 76 02             lea esi,[esi+2]
//   0f b6 d8             movzx ebx,al
//   ff 24 5d 58 3c 51 00 jmp dword ptr ds:[0x513c58 + ebx*2]  (vector_table)
extern char svp_t[];           /* source_vertex_ptr (+4 addend baked) */
extern char vbuf2_t[];         /* vbuf2 */
extern char vector_table_t[];  /* vector_table @0x513c58 */
__declspec(naked) void w26a_dobrush(void)
{
    __asm {
        mov ax, word ptr [esi]
        lea esi, [esi+2]
        mov word ptr [svp_t + 4], ax
        movzx ecx, ax
        mov edi, OFFSET vbuf2_t
        rep movsd
        mov ax, word ptr [esi]
        lea esi, [esi+2]
        movzx ebx, al
        jmp dword ptr vector_table_t[ebx*2]
    }
}