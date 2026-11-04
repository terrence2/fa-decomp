// _ChooseScoreInit @ rva 0x41280 (48 B) — FA asm: c7 05 <targetV+0x1c48>,
//   ffffffff (dword -1)/6a 01/68 <_missionName>/e8 _CallMissionProc@8
//   (CallMissionProc(missionName, 1))/a2 <_combatScoreTime+0x4>,al/a2
//   <targetV+0x1c4c>,al/33 c0/66 a3 <targetV+0x1c44>,ax/66 a3
//   <_combatScoreTime>,ax (chained zero materialized in ax)/ret.  Plain C:
//   the two a2 stores re-commit al (char return kept in al); the word
//   zero-pair is the chained-assignment shape cst = tvW = 0.  Probe
//   build/w4probe/b20f_ChooseScoreInit.obj — exact modulo fixup dwords.
extern char missionName[];   /* identity _missionName */
extern long tvA;             /* ?targetV@@3UVIEW_VARS@@A+0x1c48 */
extern char tvC;             /* ?targetV@@3UVIEW_VARS@@A+0x1c4c */
extern short tvW;            /* ?targetV@@3UVIEW_VARS@@A+0x1c44 */
extern char csi4;            /* _combatScoreTime+0x4 */
extern short csiW;           /* _combatScoreTime */

extern char __stdcall CallMissionProc(char *name, int sel);

void ChooseScoreInit_q(void)
{
    char r;
    tvA = -1;
    r = CallMissionProc(missionName, 1);
    csi4 = r;
    tvC = r;
    csiW = tvW = 0;
}