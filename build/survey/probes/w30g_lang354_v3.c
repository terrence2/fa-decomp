// v3: goto tail for the true arm, hoping to keep CL branchy (no sbb select).
short __cdecl w30g_lang354c(int x)
{
    if ((x & 0xffff) == 0x354)
        goto hit;
    return 0;
hit:
    return 0xc04;
}