// _MaybeCallEventProc@8 @ rva 0x62b40 (64 B) — maybe invoke the object event
// proc. FA: eax=[_curThing+0x1] (a1 moffs dword); test al,1 / je exit (je,
// fallthrough is the body); movsx ecx, word[_curThing+0x58] (0f bf 0d);
// edx = word/word of param1 (66 8b 54 24 04), zero-extended via 25 ffff0000;
// test ecx,eax (85 c1 — MASM encodes test operand1 in the reg field, so the
// source spells it test eax,ecx) / je exit; push [esp+8]; push edx; call
// _CallEventProc@8 (stdcall); ret 8. Exit path clears ONLY al (32 c0).
// CL cannot steer this reg plan — naked asm (ButtonSound_q family).
extern long curFlagQ;       /* _curThing+0x1 */
extern short curEventW;     /* _curThing+0x58 */
extern int __stdcall CallEventProcQ(int a, int b);

__declspec(naked) int __stdcall MaybeCallEventProc(int a, int b)
{
    __asm {
        mov eax, curFlagQ
        test al, 1
        je zero
        movsx ecx, word ptr curEventW
        mov dx, word ptr [esp+4]
        mov eax, edx
        and eax, 0ffffh
        test eax, ecx
        je zero
        mov eax, [esp+8]
        push eax
        push edx
        call CallEventProcQ
        ret 8
    zero:
        xor al, al
        ret 8
    }
}
