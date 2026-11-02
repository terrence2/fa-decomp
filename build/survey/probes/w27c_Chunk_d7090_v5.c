// chunk @ rva 0xd7090 (880784, 15 B) — v5: *pp = *pp + 1 spelled as
//   (*pp)++ reassignment ... plain add attempt.
int Chunk_d7090_v5q(int **pp)
{
    *pp = (int *)((char *)*pp + 4);
    return *(int *)((char *)*pp - 4);
}
