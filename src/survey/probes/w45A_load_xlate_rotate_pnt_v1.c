/* w45A_load_xlate_rotate_pnt_v1 - rva 0xcab6c load_xlate_rotate_pnt (59 B, no FPO, no ret: falls through) */
/* 4 rel32 callers; body = 16-bit shl-by-cl phases, sub abs word __xv/__zv/__yv, results in bx/bp/cx */
extern char w45a_c2;
extern unsigned short w45a_xv, w45a_zv, w45a_yv;

void __declspec(naked) _load_xlate_rotate_pnt(void)
{
    __asm {
        mov cl, byte ptr w45a_c2
        mov ax, word ptr [esi]
        shl ax, cl
        sub ax, word ptr w45a_xv
        mov bx, ax
        mov ax, word ptr [esi+2]
        shl ax, cl
        sub ax, word ptr w45a_zv
        mov bp, ax
        mov ax, word ptr [esi+4]
        shl ax, cl
        sub ax, word ptr w45a_yv
        mov cx, ax
        add esi, 6
    }
}