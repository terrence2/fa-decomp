// _MSGInit@0 @ rva 0x17e00 (48 B) — FA asm: bf <lastWeaponButton+0xf0>/
//   66 c7 46 06 ff ff (stosd-strided dword-pair fill: 0xffff at +6, stride
//   0xd5) looped to lastWeaponButton+0x64c8, then 0xe8/0x8 zero stores.
//   Plain C wins: CL reuses the fill temp exactly as FA does (66 89/3d cmp).
//   Probe build/w4probe/b17_msginit_v1.c — exact modulo fixup dwords.

extern char lastWeaponButton[];

void MSGInit(void) {
    unsigned char *p = (unsigned char *)lastWeaponButton + 0xf0;
    unsigned short fill = 0xffff;
    do {
        *(unsigned short *)(p + 6) = fill;
        p += 0xd5;
    } while (p < (unsigned char *)lastWeaponButton + 0x64c8);
    *(unsigned short *)(lastWeaponButton + 0xe8) = 0;
    *(unsigned char *)(lastWeaponButton + 8) = 0;
}