// _MMUWordAt @ rva 0x35e20 (13 B) — identical bytes to _MMWordAt (unsigned
//   dereference is byte-for-byte the same in CL 4.2). Probe d5_mmwa1.
short MMUWordAt_q(char *p, int o)
{
    return *(short *)(p + o);
}
