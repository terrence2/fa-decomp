// _T_ShutdownDatabase @ rva 0xc2100 — xor eax,eax / mov [_dbDynamicHigh],eax
//   / mov [_dbDynamicLow],eax / ret (a3 moffs stores). Same zero-local
//   pattern as wave-4c _COLInit: the zero must live in a local so CL picks
//   the xor/a3 form.
extern long dbDynamicHigh;
extern long dbDynamicLow;

void T_ShutdownDatabase_q(void)
{
    long z = 0;
    dbDynamicHigh = z;
    dbDynamicLow = z;
}
