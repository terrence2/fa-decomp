/* 0x1f320 — v1: isspace-ish test; ' '/'\t' inline, CR/LF via 0x1f2d0 helper */
extern char __fastcall w30c_iscrlf(char c);

char __fastcall w30c_isspace1(char c)
{
    if (c == ' ' || c == '\t')
        return 1;
    return w30c_iscrlf(c) != 0 ? 1 : 0;
}