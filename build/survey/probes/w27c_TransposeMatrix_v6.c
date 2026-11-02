// _TransposeMatrix @ rva 0xd21c8 (64 B) — v6: b (f1) declared first; a (f3)
//   second — CL's reversed-arg eval then loads f3 into ax first like FA.
void w27c_TransposeMatrix6(void *pv)
{
    unsigned short *f = pv;
    unsigned short b, a;
    b = f[1]; a = f[3]; f[1] = a; f[3] = b;
    b = f[2]; a = f[6]; f[2] = a; f[6] = b;
    b = f[5]; a = f[7]; f[5] = a; f[7] = b;
}
