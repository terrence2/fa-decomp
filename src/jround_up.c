// ?jround_up@@YAJJJ@Z @ rva 0x74f40 (32 B) — FA asm: mov ecx,[esp+4] / push esi
//   / mov esi,[esp+0ch] / lea ecx,[esi+ecx*1-1] / mov eax,ecx / cdq / idiv esi /
//   sub ecx,edx / pop esi / mov eax,ecx / ret. Rounds a up to the next multiple
//   of b: ((a+b-1)/b)*b computed as t - t%b. Naked-asm escape: 4 plain-C
//   spellings (a+b-1, b+a-1, (b-1)+a, single-expression) all load a into eax
//   and emit the fused lea with sib 0x30 ([esi+eax*1]); FA keeps a in ecx so
//   the lea reads sib 0x0e ([esi+ecx*1]) — jdiv_round_up's zero-fill sibling
//   needs no escape, this one does. MASM spelling [esi+ecx*1-1] yields sib 0e.
long __declspec(naked) jround_up(long a, long b)
{
    __asm {
        mov ecx, [esp+4]
        push esi
        mov esi, [esp+0ch]
        lea ecx, [esi+ecx*1-1]
        mov eax, ecx
        cdq
        idiv esi
        sub ecx, edx
        pop esi
        mov eax, ecx
        ret
    }
}