/* wave37D MPStatusSet 0x704a0 (80 B) v1 */
extern long w37d_mps[];          /* ?mpStatus@@3PAJA */
extern long w37d_thisComputer;   /* _thisComputer */
extern long w37d_numComputers;   /* _numComputers */
void __stdcall w37d_mppush(long, void*, long, long);   /* $FA$_t_46b260 */
void __fastcall w37d_mpflush(unsigned char);           /* ?MPFlushAll@@YIXD@Z */
void __fastcall MPStatusSet(long s)
{
    char buf[8];
    w37d_mps[w37d_thisComputer] = s;
    if (w37d_numComputers != 1) {
        *(long*)(buf + 1) = s;
        buf[0] = 0x42;
        w37d_mppush(-1L, buf, 5L, 1L);
        w37d_mpflush(1);
    }
}
