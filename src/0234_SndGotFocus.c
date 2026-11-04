// ?SndGotFocus@@YAXXZ @ rva 0x35750 (16 B) — clears the byte at
// ?ailActive@@3DA+0x4 (c6 05 store). plain C, probe w12a_05 byte-exact.
extern char sndFocusAil;

void SndGotFocus_q(void)
{
    sndFocusAil = 0;
}
