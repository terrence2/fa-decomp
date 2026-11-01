// do_start_interp @ rva 0xd05f0 (20 B) — FA asm:
//   pop esi / mov ax,[esi] / lea esi,[esi+2] / movzx ebx,al /
//   jmp dword [vector_table+ebx*2]
// (Same shape as do_nop, wave-W15/17 vector-dispatch family.) Reads the
// instruction opcode byte from the top-of-stack stream pointer, advances
// it, and jumps through the 256-entry opcode table. Naked-asm escape: the
// pop esi (the cdecl return-addr slot IS the stream pointer — no C can
// pop its own return address) + sib 0x5d jmp dword (scale-2 ebx index,
// base-less) — `jmp dword ptr vector_table[ebx*2]` (probe
// b19b_sinterp_v1 exact). Map: _vector_table=vector_table (FA chunk name
// is the bare spelling).
extern void *vector_table[];

void __declspec(naked) do_start_interp(void)
{
    __asm {
        pop esi
        mov ax, word ptr [esi]
        lea esi, [esi+2]
        movzx ebx, al
        jmp dword ptr vector_table[ebx*2]
    }
}