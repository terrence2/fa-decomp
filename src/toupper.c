// __toupper @ rva 0xd43c0 (8 B) — mov eax,[esp+4] / sub eax,0x20 / ret
int __cdecl _toupper(int c)
{
    return c - 0x20;
}
