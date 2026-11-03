/* rva 0x3e230 (254512), 48 B - v3: unsigned short return in case FA
   compiled 'return w' (eax=w on every path either way). */
unsigned short __fastcall w34b_3e2303(unsigned long lo, unsigned long hi,
                                      unsigned short w)
{
    unsigned long i;
    for (i = lo; i < hi; i += 0x8c)
        if (*(unsigned short *)i == w) {
            *(unsigned short *)i = 0;
            break;
        }
    return w;
}