// chunk @ rva 0xd7090 (880784, 15 B) — v6: compound *pp += 1 (add ecx,4)
//   + return deref via the saved p local (no pp re-read): mov eax,[ecx-4].
int Chunk_d7090_v6q(int **pp)
{
    int *p = *pp;
    *pp += 1;
    return *(p - 1);
}
