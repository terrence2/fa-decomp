// _GRAPHICUpdate@0 @ rva 0x42400 (48 B) — walks the graphics MODSPEC array in
// 0x66 strides until ?noMixLeft@@3UMODSPEC@@A, thiscalling each entry whose
// +4 word != -1, then UpdateLoopSounds. The thiscall is driven as a fastcall
// extern (mov ecx,esi / call @gfxUpdObj@4); the 16-bit != -1 test needs the
// limit in a reg (mov edi,0xffff / cmp word [esi+4],di) which CL emits even
// for the plain 0xFFFF literal. probe w12a_07 byte-exact.
extern char graphics[];
extern char noMixLeftArr[];
extern void __fastcall gfxUpdObj(long o);
extern long __fastcall UpdateLoopSounds_q(void);

void __stdcall GRAPHICUpdate_q(void)
{
    unsigned long s = (unsigned long)graphics;
    do
    {
        if (*(unsigned short *)(s + 4) != 0xFFFF)
            gfxUpdObj((long)s);
        s += 0x66;
    } while (s < (unsigned long)noMixLeftArr);
    UpdateLoopSounds_q();
}
