/* w46D MPMissionInit2 rva 439856 (0x46b630) v1 */
extern void* __cdecl memset(void*, int, unsigned);
struct ANGLE;
extern void __stdcall MPPrepareForInterp(struct ANGLE*, long);   /* ?MPPrepareForInterp@@YGXPAUANGLE@@J@Z */
extern void __stdcall MPSendPrefs(void);                         /* ?MPSendPrefs@@YGXXZ */
extern "C" unsigned long numComputers;       /* _numComputers */
extern "C" unsigned long thisComputer;       /* _thisComputer */
extern "C" unsigned long gamePrefs;          /* _gamePrefs */
extern "C" unsigned short nextObjId;         /* _nextObjId */
extern long packetTicks[];                   /* ?packetTicks@@3PAJA */
extern long packetTicksAdjust[];             /* ?packetTicksAdjust@@3PAJA */
extern unsigned long w46d_pta2;              /* map: _w46d_pta2=?packetTicksAdjust@@3PAJA+0x20 */
extern "C" void __fastcall GetCurObj_q(unsigned long);   /* map: @GetCurObj_q@4=@GetCurObj@4 */
extern "C" void __cdecl PutCurObj_q(void);               /* map: _PutCurObj_q=@PutCurObj@0 */

void __stdcall MPMissionInit2(void)          /* ?MPMissionInit2@@YGXXZ name-identical */
{
    long* px; unsigned short i;
    if (numComputers == 1)
        return;
    if (!thisComputer)
        MPSendPrefs();
    else
        w46d_pta2 = gamePrefs;
    px = packetTicks + 0x136;
    px[0] = 0;
    px[1] = 0;
    memset((void*)packetTicks, 0, 32);
    memset((void*)packetTicksAdjust, 0, 32);
    i = 1;
    while (nextObjId > i) {
        GetCurObj_q(i++);
        MPPrepareForInterp(0, 0);
        PutCurObj_q();
    }
}