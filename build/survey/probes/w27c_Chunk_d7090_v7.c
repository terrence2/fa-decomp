// chunk @ rva 0xd7090 (880784, 15 B) — v7: the chunk's true semantics are
//   "bump slot, return the previous value": post-increment spelling.
int Chunk_d7090_v7q(int **pp)
{
    return (*pp)++;
}
