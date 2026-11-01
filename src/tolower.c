// __tolower @ rva 0xd3da0 (8 B) — mov eax,[esp+4] / add eax,0x20 / ret
//   (CRT C ident carries a leading underscore -> doubled obj prefix)
int __cdecl _tolower(int c)
{
    return c + 0x20;
}
