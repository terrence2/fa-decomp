// _VIEWSlew@12 @ rva 0xd510 = 5456, 80 B (stdcall, ret 0xc, fpo, no saves)
// FA asm two symmetric word blocks:
//   blk1: mov ecx,[esp+4] (p2... in call order p1) / mov eax,[esp+8] (p1 word)
//     add ax,[ecx+2] / movsx edx,ax / mov [ecx+2],ax /
//     mov eax,[ecx+0xe]; cmp edx,eax; jl  -> v=MAX  (store ax, fall through)
//     mov eax,[ecx+0x12]; cmp edx,eax; jle -> skip store; else store (INVERTED
//     clamp: "if (v < f_e) v = f_e; else if (v > f_12) v = f_12;")
//   blk2: same shape at +4 / +0xa / +6 with a `ret 0xc` inside (early return
//     when v4 < f_a) and a second `ret 0xc` at the end.
// 5 call sites: push(imm)/push(...)/push(p1) — p1 = 0x53681c base struct,
// p2 = small dword offsets, p3 = 0 or pushed values.
void __stdcall w25c_VIEWSlew_q(char *c, int a1, int a2)
{
    unsigned short v;
    long cmpv;
    v = (unsigned short)(*(unsigned short *)(c + 2) + (unsigned short)a1);
    *(unsigned short *)(c + 2) = v;
    cmpv = (short)v;
    {
        long f_e, f_12;
        if (cmpv < (f_e = *(long *)(c + 0xe)))
        {
            v = (unsigned short)f_e;
            *(unsigned short *)(c + 2) = v;
        }
        else if (cmpv > (f_12 = *(long *)(c + 0x12)))
        {
            v = (unsigned short)f_12;
            *(unsigned short *)(c + 2) = v;
        }
    }
    v = (unsigned short)(*(unsigned short *)(c + 4) + (unsigned short)a2);
    *(unsigned short *)(c + 4) = v;
    cmpv = (short)v;
    {
        long f_a, f_6;
        if (cmpv < (f_a = *(long *)(c + 0xa)))
        {
            v = (unsigned short)f_a;
            *(unsigned short *)(c + 4) = v;
            return;
        }
        if (cmpv > (f_6 = *(long *)(c + 6)))
        {
            v = (unsigned short)f_6;
            *(unsigned short *)(c + 4) = v;
        }
    }
}