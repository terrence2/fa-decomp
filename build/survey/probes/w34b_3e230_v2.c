/* rva 0x3e230 (254512), 48 B - v2: do-while form to steer FA's
   cmp ecx,edx/jb latch order. eax must be w on every return path. */
void __fastcall w34b_3e2302(unsigned long lo, unsigned long hi,
                            unsigned short w)
{
    unsigned long i;
    for (i = lo; i < hi; i += 0x8c) {
        if (*(unsigned short *)i == w) {
            *(unsigned short *)i = 0;
            return;
        }
    }
}