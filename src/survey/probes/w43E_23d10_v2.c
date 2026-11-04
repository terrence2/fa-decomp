/* FA 0x423d10 unnamed (80 B) v2: nested call, no explicit f1()==0 test */
extern unsigned long fcheck[];  /* _desiredMapScale+0x18 (dword value) */
extern short curScreenV;        /* _curScreen (word value) */
extern long w43E_f1(void);      /* $FA$_t_424ae3 */
extern char __fastcall w43E_f2c(long);    /* $FA$_t_423d60 (arg via ecx) */
extern long nComputers;         /* _numComputers */
extern unsigned short playerId; /* _playerId */
extern char __stdcall WNGPart(unsigned short pid, long a, long b); /* _WNGPart@12 */

unsigned char w43E_MZchk(void)
{
    if (fcheck[0] == 0)
        return 0;
    if (curScreenV == 3)
        return 1;
    if (w43E_f2c(w43E_f1()) == 0)
        return 0;
    if (nComputers > 1) {
        if (WNGPart(playerId, 0, 0) == 2)
            return 0;
    }
    return 1;
}