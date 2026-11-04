/* wave 32 batch B: 0x4db260 (unnamed 24 B, __ungetc_lk gate wrapper) */
extern int _ungetc_lk(int c, void *f);

/* FA bytes 0x4db260 (24 B):
   mov eax,[esp+4]; cmp eax,-1; je ret
   mov ecx,[esp+8]; push ecx; push eax; call _ungetc_lk; add esp,8
   ret                                          */
void w32b_ungetc2(int c, void *f)
{
    if (c != -1)
        _ungetc_lk(c, f);
}