// chunk @ rva 0xd7090 (880784, 15 B) — v4: no p var: *pp += 1; then deref
//   ((int *)*pp) - 1.
int Chunk_d7090_v4q(int **pp)
{
    *pp += 1;
    return *((int *)*pp - 1);
}
