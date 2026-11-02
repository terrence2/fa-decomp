// _TransposeMatrix @ rva 0xd21c8 (860616, 64 B) — cdecl void(void*):
//   push eax/ebx/esi / esi=[ebp+8] / word swaps f1<->f3, f2<->f6, f5<->f7 /
//   pop esi/ebx/eax / ret.
void w27c_TransposeMatrix(void *pv)
{
    unsigned short *f = pv;
    unsigned short t;
    t = f[1];
    f[1] = f[3];
    f[3] = t;
    t = f[2];
    f[2] = f[6];
    f[6] = t;
    t = f[5];
    f[5] = f[7];
    f[7] = t;
}
