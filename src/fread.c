// _fread @ rva 0xd5680 (55 B, FPO fpo/esp params=4) — CRT fread: lock
// the stream (esi = 4th param, moved down before the call), re-shuffle
// the remaining (buf,size,count) args onto the stack in FA's esi/eax/ecx/
// edx order, call __fread_lk, save result in edi, unlock, return edi.
// Naked asm: the exact lock/unlock + arg-shuffle register plan with esi
// held across the calls is asm-only.
extern void lockFileX(void);
extern void freadLkX(void);
extern void unlockFileX(void);

void __declspec(naked) freadQ(void)
{
    __asm {
        push esi
        push edi
        mov  esi, dword ptr [esp+0x18]
        push esi
        call lockFileX
        mov  eax, dword ptr [esp+0x18]
        mov  ecx, dword ptr [esp+0x14]
        mov  edx, dword ptr [esp+0x10]
        add  esp, 4
        push esi
        push eax
        push ecx
        push edx
        call freadLkX
        add  esp, 16
        mov  edi, eax
        push esi
        call unlockFileX
        add  esp, 4
        mov  eax, edi
        pop  edi
        pop  esi
        ret
    }
}