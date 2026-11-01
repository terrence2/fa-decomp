// @TIMESetCompression@4 @ rva 0x84db0 (28 B) — fastcall param kept whole in
//   ecx, tested as the low word (66 81 f9) once _numComputers > 1; zeroing is
//   a 16-bit xor (66 33 c9) and the store is a word (66 89 0d). The unsigned
//   short local w is what keeps CL in 16-bit forms (int-a form gives 32-bit
//   xor ecx,ecx, d143, 27 B).
extern long numComputers;
extern unsigned short timeCompression;
void __fastcall TIMESetCompression_q(int a)
{
    unsigned short w = (unsigned short)a;
    if (numComputers > 1)
    {
        if (w != 0x7fff)
            w = 0;
    }
    timeCompression = w;
}
