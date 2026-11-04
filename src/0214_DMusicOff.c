// ?DMusicOff@@YIXXZ @ rva 0x32700 (206592 DEC; off 203520) (48 B) — EXACT
// winner (probe w24c_DMusicOff_v2.c). Pure CL C, NO patches. 0x25 body +
// census tail 8d642400 + 8da42400000000 (11 B).
//
// FA asm: a0 [sndEnable = $FA$_d_4e7000+0x5f0] / test al,al / 74 je / 66 8b 0d
// [musicId] / 66 83 f9 ff (16-bit cmp cx,-1) / 74 je / e8 ?SoundOff@@YIXF@Z
// (fastcall, char arg in cl — stale uppers ride) / 66 c7 05 [musicId],ffff /
// c3.
//
// C recipe:
//   - `if (musicId != -1)` with `extern short musicId` (plain, no cast)
//     emits the native 16-bit compare 66 8b 0d + 66 83 f9 ff. A
//     (unsigned short)-1 cast or unsigned mirror externs emit
//     movsx/32-bit-cmp forms instead (v1 lesson).
//   - sndEnable is a byte inside a data coin: extern char sndEnableQ mapped
//     to $FA$_d_4e7000+0x5f0 (identity addend on a text-segment data page).
//   - SoundOff_q(char) fastcall: @4 mangle despite the 1-byte param;
//     callee pops nothing -> FA's c3 ret comes free.
//   - musicId = -1 as signed short store emits 66 c7 05 0000+ffff.
//
// Maps (obj FROM -> FA name):
//   _sndEnableQ=$FA$_d_4e7000+0x5f0
//   _musicId=?musicId@@3FA
//   @SoundOff_q@4=?SoundOff@@YIXF@Z
//   (_DMusicOff_q=?DMusicOff@@YIXXZ — needed because the C function name is
//   DMusicOff_q, not the FA chunk name; fitobj redefines the MAIN symbol but
//   the recursive-ish self reference here is via the extern declaration —
//   actually the extern self-call map is harmless/unused.)
//
// Fit line:
//   python3 tools/fitobj.py build/survey/probes/w24c_DMusicOff_v2.obj 206592 \
//     build/survey/probes/w24c_DMusicOff_v2_fit.obj \
//     --map '_sndEnableQ=$FA$_d_4e7000+0x5f0' --map '_musicId=?musicId@@3FA' \
//     --map '@SoundOff_q@4=?SoundOff@@YIXF@Z' --map '_DMusicOff_q=?DMusicOff@@YIXXZ'
extern char sndEnableQ;      /* $FA$_d_4e7000+0x5f0 */
extern short musicId;        /* ?musicId@@3FA */
void __fastcall SoundOff_q(char id);   /* ?SoundOff@@YIXF@Z */

void DMusicOff_q(void)
{
    if (sndEnableQ) {
        if (musicId != -1)
            SoundOff_q((char)musicId);
        musicId = -1;
    }
}