// chunk @ rva 0xd4880 (870528, unnamed 14 B) — mov eax,[esp+4] / push eax /
//   call _free / add esp,4 / ret: cdecl void free() wrapper.
extern void __cdecl free(void *mem);
void Chunk_d4880_q(void *mem)
{
    free(mem);
}
