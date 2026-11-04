/* w46D MusicVolume rva 206448 (0x432670) v2: operand setup hoisted before store */
extern short volDMusic;                     /* ?volDMusic@@3FA name-identical */
extern unsigned short musicVolume;          /* ?musicVolume@@3GA name-identical */
extern "C" unsigned char dMusic;            /* _dMusic */
extern "C" unsigned short curScreen;        /* _curScreen */
extern unsigned char w46d_sflag;            /* map: _w46d_sflag=_IID_IDirectDrawClipper+0x2350 */
struct _MDI_DRIVER;
extern struct _MDI_DRIVER* musicDriverHandle;   /* ?musicDriverHandle@@3PAU_MDI_DRIVER@@A */
extern "C" __declspec(dllimport) void __stdcall w46d_lck(void);        /* map: __imp__w46d_lck@0=__imp__AIL_lock@0 */
extern "C" __declspec(dllimport) void __stdcall w46d_smv(void*, long); /* map: __imp__w46d_smv@8=__imp__AIL_set_XMIDI_master_volume@8 */
extern void (__stdcall *w46d_ulk9)(void);                              /* map: _w46d_ulk9=__imp__AIL_unlock@0 */

void __fastcall MusicVolume(unsigned short vol)     /* ?MusicVolume@@YIXG@Z name-identical */
{
    int mvi;
    if (w46d_sflag) {
        mvi = ((int)vol << 7) / 100;
        musicVolume = vol;
        if (dMusic || curScreen != 16) {
            if (vol > 100)
                vol = 100;
            volDMusic = (((int)vol << 8) - vol) / 100;
        } else {
            w46d_lck();
            w46d_smv(musicDriverHandle, mvi);
            (*w46d_ulk9)();
            return;
        }
    }
}