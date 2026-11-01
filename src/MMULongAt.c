// _MMULongAt @ rva 0x35e40 (12 B) — mov ecx,[esp+8] / mov eax,[esp+4] /
//   mov eax,[eax+ecx] / ret: *(long *)(p + o) with a scale-1 pointer add
//   (void *). Probe d3_mmla1 byte-exact.
long MMULongAt_q(int p, int o)
{
    return *(long *)(p + o);
}
