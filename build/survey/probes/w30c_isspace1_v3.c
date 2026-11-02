/* 0x1f320 — v3: merged || so all three conditions share the mov al,1 tail */
extern char __fastcall w30c_iscrlf(char c);

char __fastcall w30c_isspace1(char c)
{
    if (c == ' ' || c == '\t' || w30c_iscrlf(c))
        return 1;
    return 0;
}
