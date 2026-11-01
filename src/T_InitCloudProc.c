// _T_InitCloudProc @ rva 0xa5a00 (16 B) — mov ecx,_cloudAlt+0x14 /
//   jmp $FA$t_4a4db0 — fastcall thunk: same walker, cloud context.
extern unsigned char cloudAlt[];
extern void __fastcall farmProc_(int ctx);

void T_InitCloudProc(void)
{
    farmProc_((int)(cloudAlt + 0x14));
}