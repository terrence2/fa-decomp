// _fwrite @ rva 0xd5810 (55 B, FPO fpo/esp params=4) — CRT fwrite, byte
// identical to _fread except the mid call targets __fwrite_lk:
// lock stream (esi = 4th param), push (esi,eax,ecx,edx) = (handle,buf,
// size,count) shuffled from [esp+0x18/14/10], call, save eax into edi,
// unlock, return edi. Naked asm (shared arg-shuffle register plan).
extern void lockFileX(void);
extern void fwriteLkX(void);
extern void unlockFileX(void);

void __declspec(naked) fwriteQ(void)
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
        call fwriteLkX
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