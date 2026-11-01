/* @PLANEUpdateJustLanded@8 @ rva 0x9dd60 — naked asm (CL emits a1/0d/a3 for scalar |=) */
/* curThingFlagQ is _curThing+0x16f */
extern char curThingFlagQ[];

void __declspec(naked) __fastcall PLANEUpdateJustLanded(void)
{
    __asm {
        test cl, cl
        jne L1
        test dl, dl
        je L2
        or dword ptr [curThingFlagQ], 04000000h
    L1:
        test dl, dl
        jne L3
    L2:
        and dword ptr [curThingFlagQ], 0fbffffffh
    L3:
        ret
    }
}