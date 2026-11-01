// __controlfp @ rva 0xdf690 — mask off bit 0x80000 and forward to __control87
extern int __cdecl control87Fn(int a, int b);
int controlfp_q(int a, int b)
{
    return control87Fn(a, b & 0xfff7ffff);
}
