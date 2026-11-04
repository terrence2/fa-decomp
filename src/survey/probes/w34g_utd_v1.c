/* rva 0xce6f4 (845556), 60 B - VM-dispatch slice (do_use_terrain_detail):
   stores _detail=_terDetail, then dispatches script opcodes through the
   vector table (inbound esi = VM opcode cursor, register-ABI slice) -
   naked asm verbatim (w30b do_sfcal_long recipe). */
extern unsigned short w34g_td;    /* -> _terDetail */
extern unsigned short w34g_det;   /* -> _detail */
extern char w34g_vt[];            /* -> vector_table */

void __declspec(naked) w34g_utd(void)
{
    __asm
    {
        mov ax, w34g_td
        mov w34g_det, ax
lab_entry:
        mov ax, [esi]
        lea esi, [esi+0x2]
        movzx ebx, al
        jmp [w34g_vt + ebx*2]
lab_case:
        mov ax, [esi]
        lea esi, [esi+0x2]
        cmp w34g_det, ax
        jl lab_ret
        mov ax, [esi]
        lea esi, [esi+0x2]
        movzx ebx, al
        jmp [w34g_vt + ebx*2]
lab_ret:
        ret
    }
}