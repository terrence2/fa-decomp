// ?SoundName@@YIPADF@Z @ rva 0x35760 = 48, 48 B (fastcall short arg -> cx,
//   char* ret; FA: mov al,[soundOn]; test al,al; jne cont; mov eax,sndDef;
//   ret; cont: movsx eax,cx; cmp cx,0x10; lea edx,[eax+eax*4]; lea eax,
//   [eax+edx*4]; jge Lspec; lea eax,[eax*4+MODbase]; ret; Lspec: lea eax,
//   [eax*4+specials]; ret — i<16 -> MOD fallthrough, i>=16 -> specials).
// v2: if (i < 16) first-return orientation.
extern unsigned char w26_soundOn; /* map _w26_soundOn=_soundOn */
extern void *w26_sndDef; /* map _w26_sndDef=$FA$_d_4e7000+0x548 */
extern void *w26_MODp; /* map _w26_MODp=?MOD@@3PAUMODSPEC@@A */
extern void *w26_specialsB; /* map _w26_specialsB=_specials+0xb30 */

char *__fastcall w26c_SoundName_q(short p1)
{
    int i;
    if (!w26_soundOn)
        return (char *)w26_sndDef;
    i = p1;
    if (i < 16)
        return (char *)w26_MODp + i * 84;
    return (char *)w26_specialsB + i * 84;
}