// ?SER_ExNamesTimeout@@YAXXZ @ rva 0x4b840 = 309312, 64 B (cdecl void; two
//   state checks, EACH reloading the state global (volatile); MOD_Shutdown
//   + serIO(0x1a); SER_Shutdown + serIO(0x1b)).
extern volatile int w26_mpInfoState6c; /* map _w26_mpInfoState6c=?mpInfo@@3UMP_INFO@@C+0x16c */
extern void __cdecl MOD_ShutdownQ(void); /* map _MOD_ShutdownQ=?MOD_Shutdown@@YAXXZ */
extern void __cdecl serIOQ(long n); /* map _serIOQ=?serIO@@YAXJ@Z */
extern void __cdecl SER_ShutdownQ(void); /* map _SER_ShutdownQ=?SER_Shutdown@@YAXXZ */

void __cdecl w26c_SER_ExNamesTimeout_q(void)
{
    if (w26_mpInfoState6c == 2) {
        MOD_ShutdownQ();
        serIOQ(0x1a);
    }
    if (w26_mpInfoState6c == 3) {
        SER_ShutdownQ();
        serIOQ(0x1b);
    }
}