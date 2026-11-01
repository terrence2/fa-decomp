// _MMLongAt @ rva 0x35e30 (12 B) — mov eax,[esp+4] / mov ecx,[esp+8] /
//   mov eax,[ecx+eax] / ret. Pure C always emits the SIB with the pointer
//   arg as base ([eax+ecx], i.e. _MMULongAt's form — probed d16/d17/d18/
//   d26), so this leaf is inline __asm (probe d32 exact; the compiler
//   epilogue supplies the ret).
void MMLongAt_q(void)
{
    __asm {
        mov     eax, dword ptr [esp+4]
        mov     ecx, dword ptr [esp+8]
        mov     eax, dword ptr [ecx+eax]
    }
}
