// _HARDUnloadAll@0 @ rva 0x52380 (48 B) — unloads ids 0..count-1 through the
// fastcall @HARDUnload@8 with arg2=0. The count byte is read into al BEFORE
// the xor esi (unsigned char local n), the loop reloads it zero-extended
// (xor eax,eax / a0) for the signed jg. Key: i++ as a SEPARATE statement
// after the call (HARDUnload(i,0); i++;) gives FA's 33 d2 / 8b ce / 46 / e8
// order — the post-inc arg form (w12a_10) emits mov ecx first. probe w12a_19.
extern void __fastcall HARDUnload(long id, long zero);
extern unsigned char hardUnloadCnt;

void __stdcall HARDUnloadAll_q(void)
{
    unsigned char n = hardUnloadCnt;
    long i = 0;
    if (n)
    {
        do
        {
            HARDUnload(i, 0);
            i++;
        } while ((long)hardUnloadCnt > i);
    }
}
