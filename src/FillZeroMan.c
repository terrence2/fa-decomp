// __FillZeroMan @ rva 0xdfa30 (16 B) — mov ecx,[esp+4] / xor eax,eax /
//   mov [ecx],eax / mov [ecx+4],eax / mov [ecx+8],eax / ret — zero the first
//   12 bytes of a man record.
//
// Codegen note: the probe matrix (build/w4probe q1..q4) shows CL 4.2 always
// allocates an esp-frame pointer param to eax and the constant zero to ecx —
// the exact reverse of FA's ecx=param / eax=zero. Same instructions, register
// roles swapped; repaired by the entry's patch (no relocs inside the span).
void __cdecl _FillZeroMan(void *m)
{
    long z = 0;
    *(long *)m = z;
    *(long *)((char *)m + 4) = z;
    *(long *)((char *)m + 8) = z;
}