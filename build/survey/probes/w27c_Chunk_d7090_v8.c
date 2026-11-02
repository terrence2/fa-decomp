// chunk @ rva 0xd7090 (880784, 15 B) — v8: bump-and-return-previous via
//   (*pp += 1) - 1 (add then deref the decremented new pointer).
int Chunk_d7090_v8q(int **pp)
{
    return (*pp += 1) - 1;
}
