// _TransposeMatrix — v8: register-hint pair on the 16-bit temps.
void w27c_TransposeMatrix8(void *pv)
{
    unsigned short *f = pv;
    register unsigned short a, b;
    a = f[3]; b = f[1]; f[1] = a; f[3] = b;
    a = f[6]; b = f[2]; f[2] = a; f[6] = b;
    a = f[7]; b = f[5]; f[5] = a; f[7] = b;
}
