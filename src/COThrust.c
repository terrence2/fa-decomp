// @COThrust@4 @ rva 0x77060 (64 B) — CO thrust value with multiplayer halfing:
// B (curThingType+0x153) if arg and B nonzero, else A (curThingType+0x14f);
// halves (sar 1) when numComputers > 1 && (gameMultiPrefs & 0x10) &&
// (_curThing+0x10 byte & 0x80). EXACT as plain C (wave-23 probe): the
// naked-asm header's "CL hoists the gmp dword load into edx" was the
// compiler seeing the value live across the call-free range — folding the
// three guards into a single if-condition with && keeps every byte.
// Maps: _ctA=_curThingType+0x14f, _ctB=_curThingType+0x153,
// _ctFlags10=_curThing+0x10; numComputers/gameMultiPrefs are FA-universe
// symbols (no maps).
extern unsigned long ctA;            /* _curThingType+0x14f */
extern unsigned long ctB;            /* _curThingType+0x153 */
extern long numComputers;
extern unsigned long gameMultiPrefs;
extern unsigned char ctFlags10;      /* _curThing+0x10 */

long __fastcall COThrust_q(unsigned char f)
{
    long v;
    if (f)
    {
        v = ctB;
        if (v == 0)
            v = ctA;
    }
    else
        v = ctA;
    if (numComputers > 1 && (gameMultiPrefs & 0x10) && (ctFlags10 & 0x80))
        v >>= 1;
    return v;
}