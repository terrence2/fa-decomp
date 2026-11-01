// _InBounds@8 @ rva 0x11b90 (64 B) — FA asm: mov eax,[esp+4] / mov
//   edx,[esp+8] / mov ecx,[eax] / sar ecx,0x10 / cmp word [edx],cx (jg
//   false) / cmp word [edx+2],cx (jl false) / mov eax,[eax+8] / sar eax,16 /
//   cmp word [edx+4],ax (jg false) / cmp word [edx+6],ax (jl false) / mov
//   al,1 / ret 8 — false-exit 32 c0 / ret 8.
//   Naked asm: FA compares the sar'd dwords as WORDS against [mem],cx
//   (66 39 / 66 3b mem-vs-reg16); every plain-C form CL tried for
//   (short)field vs *(short*)q loads the word into a register with movsx and
//   reverses the cmp operand order (wave-9 lvalue-vs-lvalue rule).  Bounds
//   come from a {minx,maxx,miny,maxy} short quad; point from two longs
//   >>16 (sar = signed floor-shift of the fixed-point coords).
__declspec(naked) unsigned char __stdcall InBounds(void *a, void *b)
{
    __asm {
        mov eax, [esp+0x4]
        mov edx, [esp+0x8]
        mov ecx, [eax]
        sar ecx, 0x10
        cmp word ptr [edx], cx
        jg Lout
        cmp word ptr [edx+2], cx
        jl Lout
        mov eax, [eax+8]
        sar eax, 0x10
        cmp word ptr [edx+4], ax
        jg Lout
        cmp word ptr [edx+6], ax
        jl Lout
        mov al, 1
        ret 8
    Lout:
        xor al, al
        ret 8
    }
}