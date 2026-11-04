/* 0x27d0 (80 B) - unnamed: one arg p; c=*(p+0x176); if c[4] and c[0x41 byte
   and fn(p): c[3]=&chunk 0x3020, [p+0x7e]=0, return; else c[3]=&chunk
   0x2d00 falls into the shared [p+0x7e]=0 exit (which the c[4]==0 path
   shares). Function pointers stored with DIR32 fixups. */
extern char __cdecl w43c_fnqq(char *p);      /* $FA$_t_402ed0 */
extern void __fastcall w43c_t30f(void);      /* $FA$_t_403020 */
extern void __fastcall w43c_t2df(void);      /* $FA$_t_402d00 */
void w43c_27d0q(char *p)
{
    long *c = *(long **)(p + 0x176);
    if (c[4]) {
        if (*(char *)(p + 0x41) && w43c_fnqq(p)) {
            c[3] = (long)w43c_t30f;
            *(long *)(p + 0x7e) = 0;
            return;
        }
        c[3] = (long)w43c_t2df;
    }
    *(long *)(p + 0x7e) = 0;
}
