/* w46A TVKey v3 = v2 if/else-if chain + goto fail to force FA's shared far-jump ret0 tail. */
extern unsigned long _stickDevice;
extern unsigned long w46a_coolie;      /* = ?coolieTV@@3JA */
extern volatile unsigned long w46a_ctt;/* = _curThingType+0xba */

unsigned short __stdcall GetKeyFlags(void);
void __stdcall FMSetTV(long a, long b);

unsigned short __fastcall TVKey(unsigned short a, unsigned short b)
{
    if (_stickDevice == 0 && !(GetKeyFlags() & 1))
        goto fail;
    if (GetKeyFlags() & 4)
        goto fail;
    if (w46a_coolie == 0x4b) {
        if (!(w46a_ctt & 0x100)) goto fail;
        FMSetTV(-1, 1);
        return 0;
    } else if (w46a_coolie == 0x4d) {
        if (!(w46a_ctt & 0x100)) goto fail;
        FMSetTV(-1, 2);
        return 0;
    } else if (w46a_coolie == 0x50) {
        if (!(w46a_ctt & 0x80)) goto fail;
        FMSetTV(4, -1);
        return 0;
    } else if (w46a_coolie == 0x48) {
        if (!(w46a_ctt & 0x80)) goto fail;
        FMSetTV(3, -1);
        return 0;
    } else {
        FMSetTV(-1, -1);
    }
fail:
    return 0;
}