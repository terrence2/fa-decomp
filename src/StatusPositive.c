// __positive @ rva 0xd94d0 (23 B) — fldz / mov eax,[esp+4] / fcomp qword
//   [eax] / fnstsw ax / test ah,0x41 / mov eax,1 / jne +2 / xor eax,eax /
//   ret. Semantics: return (*p >= 0). Every pure-C formulation probed
//   (d19/d20/d27/d27b/d30/d30b) came out as CL's setne or a hoisted mov
//   ecx,1, so the leaf is inline __asm (probe d36 byte-exact); the
//   compiler epilogue supplies the ret.
void StatusPositive_q(void)
{
    __asm {
        fldz
        mov     eax, dword ptr [esp+4]
        fcomp   qword ptr [eax]
        fnstsw  ax
        test    ah, 41h
        mov     eax, 1
        jne     pos_done
        xor     eax, eax
pos_done:
    }
}
