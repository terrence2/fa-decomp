/* w36F 0x7bb30 (64B) v2 — inverted gate polarity: if (cfe != 1) return 0;
 * leaves the false exit inline after a je(+) like FA, ts body at the tail
 */
extern char __stdcall CheckFlightEnvelope(int a, int b);
extern char __stdcall ThrustSupport(void);
extern long w36f_ct1;   /* -> _curThing+0x19b */

char __cdecl w36f_envchk(void)
{
    int mode;
    mode = w36f_ct1 >> 8;
    if (mode < 0) {
        mode = 0;
    } else if (mode > 2) {
        mode = 2;
    }
    if (CheckFlightEnvelope(mode, 0) != 1) {
        return 0;
    }
    return (char)(ThrustSupport() == 0);
}