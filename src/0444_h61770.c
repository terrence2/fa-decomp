/* probe w45D_61770 (FA 0x461770, 64B): fadeout starter */
extern unsigned long w45D_wgs[];       /* _wingIds (VA 0x5421d0); +0x194 = element 101 */
void __fastcall w45D_sub690(unsigned long, unsigned char *);
long __stdcall RMChangeType(long, long, long);
long __stdcall PlayCobra(long);
long __stdcall DoFadeout(void);

void __cdecl w45D_61770(void)
{
    unsigned char buf[16];
    w45D_sub690(w45D_wgs[101], buf);
    RMChangeType((long)buf, 0, (long)buf);
    PlayCobra((long)buf);
    DoFadeout();
}