// chunk @ rva 0xd7090 (880784, 15 B) — v2: final deref = one element before
//   the new pointer (FA: mov [eax],ecx / mov eax,[ecx-4]).
int Chunk_d7090_v2q(int **pp)
{
    int *p = *pp;
    *pp = p + 1;
    return *(p - 1);
}
