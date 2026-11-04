// chunk @ rva 0xd7090 (880784, 15 B) — v3: compound *pp += 1 (add ecx,4),
//   return deref at ((int*)*pp)[] - 1 (mov eax,[ecx-4]).
int Chunk_d7090_v3q(int **pp)
{
    int *p = *pp;
    *pp += 1;
    return *((int *)*pp - 1);
}
