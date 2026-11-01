// @SetHShake@8 @ rva 0x127c0 (46 B code + 1 B 90 pad) — fastcall pass-through
// gate, tail-jmp @G_SetHShake@8 with ecx/edx args untouched:
//   mov eax,[_gamePrefs] / test eax,0x8000000 / je ret
//   test byte ptr [_mainV+0x1a],1 / je ret
//   mov ax,[_playerId] / test ax,ax / je ret
//   cmp ax,[_mainV+0x1c] / jne ret
//   jmp @G_SetHShake@8 / ret.
// Naked asm (tail with fastcall args already in ecx/edx is not reachable
// from a C call — CL would reload params).  _gamePrefs/_playerId/_mainV are
// FA.SMS identities (probes w16c_6/w16c_7 exact; MASM gives a1, a9 imm32
// test, 66 a1, f6 05 mem-byte test and 66 3b 05 mem-first cmp).
extern char mainV[];
extern unsigned short playerId;
extern long gamePrefs;
extern void __fastcall G_SetHShake(int a, int b);

void __declspec(naked) __fastcall SetHShake(int a, int b)
{
    __asm {
        mov  eax, gamePrefs
        test eax, 08000000h
        je   L
        test byte ptr [mainV+1Ah], 1
        je   L
        mov  ax, word ptr playerId
        test ax, ax
        je   L
        cmp  ax, word ptr [mainV+1Ch]
        jne  L
        jmp  G_SetHShake
L:
        ret
    }
}