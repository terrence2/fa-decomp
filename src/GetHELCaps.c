// ?GetHELCaps@CDirDraw@@QAEPBU_DDCAPS@@XZ @ rva 0x1dd20 (32 B) —
// branchless mask ternary: mov eax,[ecx+0x27c]; cmp eax,1; mov eax,0;
// adc eax,-1 (CF from the unsigned x<1 cmp); and eax,ecx (mask & this);
// ret. All three natural C forms (ternary, ?:, if==0) fold to the same
// mov0/adc/and (w14a_ghc1..3 identical); kept the explicit-ternary one.
struct _DDCAPS;

struct _DDCAPS * __fastcall GetHELCaps(void *t)
{
    unsigned long x;

    x = *(unsigned long *)((char *)t + 0x27c);
    return (struct _DDCAPS *)((x < 1 ? 0 : -1) & (unsigned long)t);
}