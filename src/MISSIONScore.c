// @MISSIONScore@4 @ rva 0x846a0 (48 B) — FA asm: a1 [scoreBy] / test eax,eax
// / je / cmp eax,1 / je / cmp eax,2 / je / fallthrough a1 [playerDamage+] /
// ret; case bodies mov [ecx*4+disp] (sib 8d: index=ECX = fastcall param sel),
// out-of-line case blocks reached by je. Plain C switch reproduced CL's
// out-of-line case blocks exactly (probe b17c_missionscore_v2 byte-exact);
// the if-chain equivalent scheduled differently (v3 FAIL). The 8b 04 8d sib
// byte was initially misread as [ebp*4] (index bits 5-3 = 001 = ECX). No
// maps: scoreBy/playerKills/playerKillRatio/playerDamage all identity.
extern long scoreBy;
extern long playerKills[];
extern long playerKillRatio[];
extern long playerDamage[];

int __fastcall MISSIONScore(int sel)
{
    switch (scoreBy) {
    case 0: return playerKills[sel];
    case 1: return playerKillRatio[sel];
    case 2: return playerDamage[sel];
    }
    return 0;
}