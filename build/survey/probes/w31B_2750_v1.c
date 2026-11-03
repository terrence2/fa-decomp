/* rva 10064 (0x2750) 32 B FPO/esp gap chunk
 * mov eax,[esp+4]; push eax; mov dword [eax+0x76],0  (zero-imm32 hidden by dis.py!);
 * call $FA$_t_402770; add esp,4; ret  (cdecl, 1 param)
 * store BEFORE the push; call with same eax */
extern void __cdecl w31b_t402770(void *a);

void __cdecl w31b_2750(void *p)
{
    *(long *)((char *)p + 0x76) = 0;
    w31b_t402770(p);
}