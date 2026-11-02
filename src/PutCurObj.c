// @PutCurObj@0 @ rva 0x61b40 (64 B) — copy the current thing into the chain
// slot. FA: push esi; edx = word[chainStart+0x4] (66 8b 15); push edi;
// esi=&_curThing (be imm w/ reloc); eax = word[_curId] (66 a1);
// ecx=edx>>2; nop; edi=objPtrs[id] (8b 3c 85, sib-85 scale4); rep movsd;
// ecx=edx&3; rep movsb; word[_curId]=0 (66 c7 05); pop edi/esi; ret.
// Explicit rep-movs plan — naked asm.
extern unsigned short objSizeW;   /* ?chainStart@@3GA+0x4 */
extern unsigned short curIdW;     /* _curId */
extern char curThingB[];          /* _curThing */
extern char objPtrsA[];           /* _objPtrs */

__declspec(naked) void __fastcall PutCurObj_q(void)
{
    __asm {
        push esi
        xor edx, edx
        mov dx, word ptr objSizeW
        push edi
        mov esi, offset curThingB
        xor eax, eax
        mov ax, word ptr curIdW
        mov ecx, edx
        shr ecx, 2
        nop
        mov edi, dword ptr objPtrsA[eax*4]
        rep movsd
        mov ecx, edx
        and ecx, 3
        rep movsb
        mov word ptr curIdW, 0
        pop edi
        pop esi
        ret
    }
}
