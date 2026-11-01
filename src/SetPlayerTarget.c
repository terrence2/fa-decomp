// SetPlayerTarget @ rva 0x13e30 — decompiled from FA.EXE (probe d224_spt4.c, byte-exact)
extern char curThing[];
extern void __fastcall NPCSetStateTarget(char a, int b);
__declspec(naked) void __fastcall SetPlayerTarget_q(unsigned short p1)
{
    __asm {
        cmp cx, word ptr [curThing + 0xee]
        jz fin
        mov al, byte ptr [curThing + 0xe3]
        mov edx, ecx
        mov ecx, eax
        call NPCSetStateTarget
        mov byte ptr [curThing + 0x11d], 0
        fin: ret
    }
}
