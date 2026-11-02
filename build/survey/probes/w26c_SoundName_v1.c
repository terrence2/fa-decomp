// ?SoundName@@YIPADF@Z @ rva 0x35760 = 218976, 48 B (fastcall 1 short arg ->
// cx, returns char*; FA: mov al,[soundOn]; test al; jne L; mov eax,imm32
// (bss gap anchor+0x548); ret // L: movsx eax,cx; cmp cx,0x10; lea edx,
// [eax+eax*4]; lea eax,[eax+edx*4]; jge L2; lea eax,[eax*4+MOD]; ret;
// L2: lea eax,[eax*4+specials+0xb30]; ret) — i*84 computed as 5i,21i,84i.
extern unsigned char w26_soundOn; /* map _w26_soundOn=_soundOn */
extern unsigned char w26_sndDef[]; /* map _w26_sndDef=$FA$_d_4e7000+0x548 */
extern unsigned char w26_MODp[]; /* map _w26_MODp=?MOD@@3PAUMODSPEC@@A */
extern unsigned char w26_specials[]; /* map _w26_specials=_specials+0xb30 */

char *__fastcall w26c_SoundName_q(short p1)
{
    if (!w26_soundOn) return (char *)w26_sndDef;
    {
        int i = p1;
        if ((short)p1 >= 16)
            return (char *)w26_specials + i * 84;
        return (char *)w26_MODp + i * 84;
    }
}