/* rva 0xcf386 (848774), 54 B - VM-dispatch slice (do_setcolor_continue):
   movzx inbound ax, call Remap, install flip fn pointers, store word,
   dispatch next opcode (vector_table stride 2). Inbound esi/ax = VM
   register-ABI slice - naked asm (w30b do_sfcal_long recipe). */
extern char w34g_pp[];      /* -> ppolygon */
extern char w34g_flipf[];   /* -> @G_PolygonFlip@8 */
extern char w34g_uflipf[];  /* -> @G_UPolygonFlip@8 */
extern unsigned short w34g_go1;   /* -> gouraudOn+0x1 */
extern void __cdecl w34g_remap(void);    /* -> Remap */
extern char w34g_vt[];      /* -> vector_table */

void __declspec(naked) w34g_setcolc(void)
{
    __asm
    {
        movzx eax, ax
        xor ebx, ebx
        call w34g_remap
        mov DWORD PTR [w34g_pp], OFFSET w34g_flipf
        mov DWORD PTR [w34g_pp + 0x4], OFFSET w34g_uflipf
        mov w34g_go1, ax
lab_next:
        mov ax, [esi]
        lea esi, [esi+0x2]
        movzx ebx, al
        jmp [w34g_vt + ebx*2]
    }
}