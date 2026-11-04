/* G_SetVShake - FA rva 0x97370 (619376) - EXACT probe verdict, tier1_a_r3.json entry 'G_SetVShake_v2'
 * Form: patch-hybrid
 * Levers: 2 cmp-direction/mirroring patches; twin of G_SetHShake spelling
 * Maps: _vShakeTicks=_vShakeTicks, _vHzMod=_vHzMod, @G_SetVShake@8=@G_SetVShake@8
 * patch 0x11: 2 B -> ce 7f (cmp ecx,esi / jg)
 * patch 0x19: -> ce
 * Probes: v1-v2
 */
extern long vShakeTicks;
extern long vHzMod;

void __fastcall G_SetVShake(int hz, int amp)
{
    if (vShakeTicks > 0 && vHzMod < hz)
        return;
    if (vShakeTicks > 0 && vHzMod == hz) {
        vShakeTicks |= 0x10;
        return;
    }
    vHzMod = hz;
    vShakeTicks = amp / 4;
}
