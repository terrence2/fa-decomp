/* rva 0x3e230 (254512), 48 B - fastcall scan of 140-byte stride array
   for WORD == w; clear that word; eax returns w on every path. */
void __fastcall w34b_3e230(unsigned long lo, unsigned long hi,
                           unsigned short w)
{
    unsigned long i;
    for (i = lo; i < hi; i += 0x8c)
        if (*(unsigned short *)i == w) {
            *(unsigned short *)i = 0;
            break;
        }
}