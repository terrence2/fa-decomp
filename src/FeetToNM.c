// @FeetToNM@8 @ rva 0x11b70 (23 B) — push esi / test dl,dl / jz skip /
//   add ecx,0xbde00 / skip: mov esi,0x17bc00 / mov eax,ecx / cdq / div esi /
//   pop esi / ret. The unsigned div after cdq is exactly what CL 4.2 emits
//   for `feet / 0x17bc00` on this declaration (probe-verified byte-exact,
//   build/w4probe/w8_feet.obj).
long __fastcall FeetToNM(int feet, unsigned char flag)
{
    if (flag)
        feet += 0xbde00;
    return feet / 0x17bc00;
}
