/* ?MPWaitEveryoneStatus@@YGDJDDD@Z (rva 0x709c0, 96 B): single-poll query
 * of the per-computer MP status table (?mpStatus@@3PAJA, indexed by the
 * current _thisComputer id).
 *   - one client: answer "ready" immediately;
 *   - otherwise run the per-computer status probe (unnamed chunk at
 *     rva 0x70a20, reads a1..a4, answers in al) and on failure defer to
 *     ?MPStatusSet@@YIXJ@Z with the current computer's mpStatus entry;
 *   - on success record arg1 as the new mpStatus entry.
 * FA scheduler artifact kept by the transplant: arg3 is pushed as a whole
 * dword whose high bytes are stale from the preceding _thisComputer load
 * (8a 44 24 18 = mov al,[esp+0x18], no extension); the probe only reads
 * the low byte.
 */
extern long numComputers;   /* _numComputers */
extern long thisComputer;   /* _thisComputer */
extern long *mpStatus;      /* ?mpStatus@@3PAJA */
extern long FA_t_470a20(long a1, long a2, long a3, long a4);
extern void __fastcall MPStatusSet(long ctx);

int __stdcall MPWaitEveryoneStatus(long a1, char a2, char a3, char a4)
{
    char ok;
    if (numComputers == 1)
        return 1;
    ok = (char)FA_t_470a20(a1, a2, a3, a4);
    if (!ok) {
        MPStatusSet(mpStatus[thisComputer]);
        return 0;
    }
    mpStatus[thisComputer] = a1;
    return 1;
}