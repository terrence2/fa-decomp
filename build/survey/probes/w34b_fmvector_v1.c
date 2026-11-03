/* rva 0x51420 (@FMVector@8), 80 B - fastcall (ushort a, uchar f) clamp:
   f? TH+=a : TH=a; TH<HI ? TH=HI,ret : fall; TH>TLO ? TH=TLO,ret. */
extern short w34b_th;
extern short w34b_thi;
extern short w34b_tlo;

short __fastcall w34b_fmvector(unsigned short a, unsigned char f)
{
    if (f)
        w34b_th = (short)(w34b_th + (short)a);
    else
        w34b_th = (short)a;
    if (w34b_th < w34b_thi)
        return w34b_th = w34b_thi;
    if (w34b_th > w34b_tlo)
        return w34b_th = w34b_tlo;
    return w34b_th;
}