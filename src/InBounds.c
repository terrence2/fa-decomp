// _InBounds@8 @ rva 0x11b90 (64 B) — point-in-rect test. FA: mov eax,[esp+4]
// / mov edx,[esp+8] / mov ecx,[eax] / sar ecx,0x10 / cmp word [edx],cx (jg
// false) / cmp word [edx+2],cx (jl false) / mov eax,[eax+8] / sar eax,16 /
// cmp word [edx+4],ax (jg false) / cmp word [edx+6],ax (jl false) / mov
// al,1 / ret 8 — false-exit 32 c0 / ret 8.
// EXACT as plain C (wave-23 probe): the || -chain of short compares with the
// two dwords lazily computed as the 3rd/4th compare's operands reproduces
// FA's lazy [eax+8] load, and the single shared `return 0` exit puts FA's
// false-exit at the tail; the sar'd dwords compare as words without any
// movsx by comparing (short)v against the short-typed bounds directly.
// Map-free: bounds come from a {minx,maxx,miny,maxy} short quad (b) and the
// point from two longs (a).
unsigned char __stdcall InBounds(void *a, void *b)
{
    long v = ((long *)a)[0] >> 16;
    if (((short *)b)[0] > (short)v
        || ((short *)b)[1] < (short)v
        || ((short *)b)[2] > (short)(*((long *)a + 2) >> 16)
        || ((short *)b)[3] < (short)(*((long *)a + 2) >> 16))
        return 0;
    return 1;
}