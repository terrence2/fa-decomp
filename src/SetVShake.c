/* SetVShake - FA rva 0x127f0 (75760) - EXACT probe verdict, tier1_a_r4.json entry 'SetVShake_v2'
 * Form: patch-hybrid
 * Levers: tail-jmp hybrid: drop push esi, a0->f6 05 test-byte, 39->3b, e8->e9 to @G_SetVShake@8
 * Maps: _gamePrefs=?slewRelative@@3DA+0x4, _gpFlags=_mainV+0x1a, _playerId=?wasInAircraftReference@@3DA+0x4, _tgtSelWord=_mainV+0x1c, @G_SetVShakeShim@8=@G_SetVShake@8
 * patch 0: delete 1 B (push esi)
 * patch 0xc: 7 B f6 05 00000000 01 test-byte, DIR32 re-add _gpFlags
 * patch 0x21: -> 3b
 * patch 0x29: 6 B e9 tail, REL32 re-add @G_SetVShakeShim@8
 * Probes: v1,v2
 */
extern unsigned long gamePrefs;
extern unsigned char gpFlags;
extern unsigned short playerId;
extern unsigned short tgtSelWord;
extern void __fastcall G_SetVShakeShim(int a, int b);

void __fastcall SetVShake(int a, int b)
{
    if (gamePrefs & 0x8000000) {
        if (gpFlags & 1) {
            if (playerId) {
                if (playerId == tgtSelWord)
                    G_SetVShakeShim(a, b);
            }
        }
    }
}
