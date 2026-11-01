// __NLG_Notify @ rva 0xd4966 (19 B, gap chunk — no FPO record) — the NLG
// state store: push ebx/ecx, ebx = __NLG_Destination (OFFSET, identity
// data extern as in __NLG_Notify1), then [ebp+8]->ecx (caller-frame read),
// +0x8=ecx, +0x4=eax, +0xc=ebp. The chunk ENDS with no ret — it falls
// through into the next code page's NLG continuation (this is the +0xa
// target of _NLG_Notify1's eb 0a short-jmp). Naked asm.
extern long _NLG_Destination;

void __declspec(naked) _NLG_Notify(void)
{
    __asm {
        push ebx
        push ecx
        mov  ebx, OFFSET _NLG_Destination
        mov  ecx, [ebp+8]
        mov  [ebx+8], ecx
        mov  [ebx+4], eax
        mov  [ebx+0xc], ebp
    }
}