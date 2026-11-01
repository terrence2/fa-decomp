// _GG_VideoModesAvailable@0 @ rva 0x5da70 — fall-off-end with negated guard
//   ("if (!p) return 0; return f();" — probe d63; the direct if(p)-first form
//   swaps the branch polarity, d43).
extern void *m_singleton;
extern long __fastcall CDirDraw_EnumDisplayModes(void *t);

long GG_VideoModesAvailable_q(void)
{
    if (!m_singleton)
        return 0;
    return CDirDraw_EnumDisplayModes(m_singleton);
}
