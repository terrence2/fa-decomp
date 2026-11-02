// _TransposeMatrix — v3: same body, but fn typed to land the pointer in esi
//   (unsigned short * param) hoping for the ebp frame + push eax shape.
void w27c_TransposeMatrix(unsigned short *f)
{
    unsigned short a, b;
    a = f[3]; b = f[1]; f[1] = a; f[3] = b;
    a = f[6]; b = f[2]; f[2] = a; f[6] = b;
    a = f[7]; b = f[5]; f[5] = a; f[7] = b;
}
