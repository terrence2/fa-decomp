// _TransposeMatrix @ rva 0xd21c8 (64 B) — v2: two named locals, load order
//   matching FA (ax-then-bx), stores low-first.
void w27c_TransposeMatrix(void *pv)
{
    unsigned short *f = pv;
    unsigned short a, b;
    a = f[3]; b = f[1]; f[1] = a; f[3] = b;
    a = f[6]; b = f[2]; f[2] = a; f[6] = b;
    a = f[7]; b = f[5]; f[5] = a; f[7] = b;
}
