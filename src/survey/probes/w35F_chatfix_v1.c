/* w35F _CHATFixKeyarray@0 @ 0x139b0 — v1
 * FA: a0 <chatEditing>; test al,al; je ret; xor ecx,ecx; ten 88 0d cl-stores
 * to _keyarray+{0x39,0xf,0x48,0x50,0x4b,0x4d,0xc,0xd,0x4a,0x4e}; ret */
extern char w35f_chatEdit;      /* -> ?chatEditing@@3DA */
extern char w35f_ka0, w35f_ka1, w35f_ka2, w35f_ka3, w35f_ka4;
extern char w35f_ka5, w35f_ka6, w35f_ka7, w35f_ka8, w35f_ka9;

void __stdcall w35f_chatfix(void)
{
    if (w35f_chatEdit) {
        char z = 0;
        w35f_ka0 = z;
        w35f_ka1 = z;
        w35f_ka2 = z;
        w35f_ka3 = z;
        w35f_ka4 = z;
        w35f_ka5 = z;
        w35f_ka6 = z;
        w35f_ka7 = z;
        w35f_ka8 = z;
        w35f_ka9 = z;
    }
}
