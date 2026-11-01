// _OBJAlloc@4 @ rva 0x8f460 — bump allocator over the comment-type arena top
// (same anchor 0x54ad78 as OBJStopAdding's cmStopTop); probe w11b_01, byte-exact
extern unsigned long objAllocTopR;
void *__stdcall OBJAlloc_q(int n)
{
    unsigned long t = objAllocTopR;
    objAllocTopR = t + n;
    return (void *)t;
}