/* ?MPSetSlowComm@@YGXXZ @ rva 0x6b310 (64 B) — stdcall void(void):
   three guards jump to the slowComm=1 tail; fall-through sets slowComm=0.
   (dis.py elides the two c6 05 [?slowComm@@3DA] stores — read from bytes.) */
struct W29EINFO { unsigned char pad[0x148]; long st; };
extern struct W29EINFO *w29e_mpinfo(void);        /* =?MP_Info@@YAPAUMP_INFO@@XZ */
extern long w29e_ncomp;                           /* =_numComputers */
extern unsigned long w29e_gdp;                    /* =_gameDebugPrefs */
extern char w29e_sc;                              /* =?slowComm@@3DA */

void __stdcall MPSetSlowCommW(void)
{
    if (w29e_mpinfo()->st >= 0x2710 && w29e_ncomp <= 4 &&
        !(w29e_gdp & 0x400))
        w29e_sc = 0;
    else
        w29e_sc = 1;
}