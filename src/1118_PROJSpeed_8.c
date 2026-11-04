// _PROJSpeed@8 @ rva 0xbd4c0 (80 B) — int __stdcall PROJSpeed(char *obj,
// int val): v = (u8)[obj+0x115] * (val >> 8) / 100, then clamp:
// v = max(v, (short)[obj+0xfb]); v = max(v, (short)[obj+0x67]);
// v = min(v, (short)[obj+0x6b]). FA schedules the [obj+0xfb] movsx load
// ahead of the cdq/idiv pair (ebx = 100 divisor materialized early, ecx
// held with m1 across the divide, arg2 preloaded into ecx before esi).
// Plain-C probe — register plan may need an asm escape.
int __stdcall PROJSpeedQ(char *obj, int val)
{
    int v;
    unsigned char b;
    b = *(unsigned char *)(obj + 0x115);
    v = (int)b * (val >> 8) / 100;
    {
        short m = *(short *)(obj + 0xfb);
        if (m > v)
            v = m;
    }
    {
        short m = *(short *)(obj + 0x67);
        if (m > v)
            v = m;
    }
    {
        short m = *(short *)(obj + 0x6b);
        if (m < v)
            v = m;
    }
    return v;
}