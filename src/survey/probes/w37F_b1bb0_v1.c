/* w37F v1 rva 0xb1bb0: 2x b1aa0(o,i) i=1,0; b3f90(o,[o+4],0x50); [o+4]=0; b4000(o) */
extern void __cdecl w37f_b1aa0(void *, int);
extern void __cdecl w37f_83f90(void *, int, int);
extern void __cdecl w37f_84000(void *);

void w37f_b1bb0(void *o)
{
    int i;
    i = 1;
    do {
        w37f_b1aa0(o, i);
    } while (--i >= 0);
    w37f_83f90(o, *(int *)((char *)o + 4), 0x50);
    *(int *)((char *)o + 4) = 0;
    w37f_84000(o);
}