/* ?MOD_Initialize1@@YAJPAUCN_INFO@@J@Z @ rva 0x98d30 (112 B) -- v1.
 * __cdecl C++ fns (add esp,8/4 at call sites); fbc tested 8; else path
 * stores f64 = fbc reusing the pre-branch eax; four per-path epilogues. */
struct CN_INFO {
    char p0[0x64];
    long f64;           /* +0x64 */
    char p1[0x54];      /* 0x68..0xbb */
    long fbc;           /* +0xbc */
};

long MOD_FindModemAndInit(CN_INFO *cn, long b);
long MOD_FindModemAndInitPCMCIA(CN_INFO *cn, long b);
long MOD_InitPortAndModem(CN_INFO *cn, long b);
void serIO(long a);

long MOD_Initialize1X(CN_INFO *cn, long b)
{
    long r;

    if (cn->fbc == 8) {
        r = MOD_FindModemAndInit(cn, b);
        if (r == 2)
            return 2;
        r = MOD_FindModemAndInitPCMCIA(cn, b);
        if (r == 2)
            return 2;
        serIO(0x19);
        return 0;
    }
    cn->f64 = cn->fbc;
    return MOD_InitPortAndModem(cn, b);
}