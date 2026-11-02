// ?SoundName@@YIPADF@Z @ rva 0x35760 = 218976, 48 B (fastcall short arg ->
//   cx, char* ret; FA: mov al,[soundOn]; test al,al; jne cont; mov eax,
//   sndDef; ret; cont: movsx eax,cx; cmp cx,0x10; lea edx,[eax+eax*4];
//   lea eax,[eax+edx*4]; jge Lspec; lea eax,[eax*4+MODbase]; ret; Lspec:
//   lea eax,[eax*4+specials]; ret; mov edi,edi pad).
// v3 (EXACT recipe): __fastcall char* fn taking short p1 directly (no
//   int hop, no local) and comparing p1 < (short)16 — CL delivers the
//   param in CX with movsx eax,cx + 16-bit cmp cx,0x10 signed jge, and
//   the array externs fold the bases into the final lea's disp32.
extern unsigned char w26_soundOn; /* map _w26_soundOn=_soundOn */
extern unsigned char w26_sndDef[]; /* map _w26_sndDef=$FA$_d_4e7000+0x548 */
extern unsigned char w26_MODp[]; /* map _w26_MODp=?MOD@@3PAUMODSPEC@@A */
extern unsigned char w26_specials[]; /* map _w26_specials=_specials+0xb30 */

char *__fastcall w26c_SoundName_q(short p1)
{
    if (!w26_soundOn)
        return (char *)w26_sndDef;
    if (p1 < (short)16)
        return (char *)&w26_MODp[p1 * 84];
    return (char *)&w26_specials[p1 * 84];
}