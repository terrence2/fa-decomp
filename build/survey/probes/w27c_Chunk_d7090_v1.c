// chunk @ rva 0xd7090 (880784, unnamed 15 B) — mov eax,[esp+4] / mov ecx,[eax]
//   / add ecx,4 / mov [eax],ecx / mov eax,[ecx-4] / ret: bump a pointer slot
//   forward one int and return the original value.
int Chunk_d7090_q(int **pp)
{
    int *p = *pp;
    *pp = p + 1;
    return *(int *)p;
}
