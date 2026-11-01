// _GetKeyFlags @ rva 0x11380 (16 B) — xor eax,eax / mov al,[_keyFlags] / ret
extern unsigned char keyFlags[];

long __cdecl GetKeyFlags(void)
{
    return *(unsigned char *)keyFlags;
}
