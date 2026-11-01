// @GRPResponseSize@0 @ rva 0x5f250 (48 B) — bit decode of the reply flag
// byte: a1/a1 loads of _curThing+0xe8, byte ops all pinned in AL (a8 test,
// 24 and, 3c cmp) and the sbb borrow tail. C puts the byte in cl and gives
// setb/neg instead of sbb (w12a_12) — naked asm (probe w12a_18 byte-exact).
extern long grpPtr;
__declspec(naked) long __fastcall GRPResponseSize_q(void)
{
    __asm {
        mov eax, grpPtr
        test eax, eax
        jne L1
        mov eax, 100
        ret
    L1:
        mov eax, grpPtr
        mov al, byte ptr [eax]
        test al, 8
        je L2
        mov eax, 1
        ret
    L2:
        and al, 10h
        cmp al, 1
        sbb eax, eax
        and eax, 62h
        add eax, 2
        ret
    }
}
