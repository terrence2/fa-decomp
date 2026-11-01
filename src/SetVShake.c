// @SetVShake@8 @ rva 0x127f0 (46 B code + 1 B 90 pad) — byte-identical twin
// of @SetHShake@8 (0x127c0), tail-jmp @G_SetVShake@8 (0x497370).
extern char mainV[];
extern unsigned short playerId;
extern long gamePrefs;
extern void __fastcall G_SetVShake(int a, int b);

void __declspec(naked) __fastcall SetVShake(int a, int b)
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
        jmp  G_SetVShake
L:
        ret
    }
}