// _PROJInit@0 @ rva 0xbca40 (112 B; FPO locals 0, frameless; code 96 B +
// 16 B lea pad).  stdcall void.  Zero band: xor ecx,ecx then 16 stores in
// FA order — projLocksOnPlayer is materialized b8/eax indirection ([eax],
// [eax+4], word [eax+8]); _searchLockEndT/_trackLockEndT dwords are 89 0d
// moffs; the dead b8 0x586308 sits between the last searchLock word store
// and the projLockCalcTime word store; trackLockEndT reuses an eax pointer
// for the final word [eax+8].  Word stores: trackLockEndT+0x16/+0x14,
// _lastPlayerProjId, ?projLockCalcTime@@3FA+0x4/@@3FA, searchLockEndT+8,
// trackLockEndT+8.
extern unsigned long w43H_trkD0;   /* =_trackLockEndT */
extern unsigned long w43H_trkD1;   /* =_trackLockEndT+0x4 */
extern unsigned short w43H_tw0;    /* =_trackLockEndT+0x14 */
extern unsigned short w43H_tw1;    /* =_trackLockEndT+0x16 */
extern unsigned short w43H_trkW1;  /* =_trackLockEndT+0x8 */
extern unsigned long w43H_slkD0;   /* =_searchLockEndT */
extern unsigned long w43H_slkD1;   /* =_searchLockEndT+0x4 */
extern unsigned short w43H_slkW1;  /* =_searchLockEndT+0x8 */
extern unsigned long w43H_pjkD0;   /* =_projLocksOnPlayer */
extern unsigned long w43H_pjkD1;   /* =_projLocksOnPlayer+0x4 */
extern unsigned short w43H_pjkW1;  /* =_projLocksOnPlayer+0x8 */
extern unsigned short w43H_lpp;    /* =_lastPlayerProjId */
extern unsigned short w43H_plc;    /* =?projLockCalcTime@@3FA */
extern unsigned short w43H_plc4;   /* =?projLockCalcTime@@3FA+0x4 */

void __stdcall w43H_PROJInit3(void)
{
    unsigned long *p;
    p = (unsigned long *)&w43H_pjkD0;
    w43H_tw1 = 0;
    p[0] = 0;
    w43H_tw0 = 0;
    p[1] = 0;
    w43H_lpp = 0;
    w43H_slkD0 = 0;
    w43H_plc4 = 0;
    w43H_slkD1 = 0;
    *(unsigned short *)((char *)p + 8) = 0;
    w43H_trkD0 = 0;
    w43H_slkW1 = 0;
    p = (unsigned long *)&w43H_slkD0;
    w43H_plc = 0;
    p = (unsigned long *)&w43H_trkD0;
    w43H_trkD1 = 0;
    *(unsigned short *)((char *)p + 8) = 0;
}