/* w46A InitMusic natural C — FA rva 0x323e0 (205792, 112 B, ?InitMusic@@YIXXZ stdcall void).
 * FA decode: if(!muon(0x4e75f0)) return;
 *   if(_dMusic(0x4efb68)) { scoreStart=0; muon=1; musicId(word 0x5338d0)=0xffff; return; }
 *   AIL_startup(); AIL_set_preference(4,0x78);
 *   if(AIL_midiOutOpen(&musicDriverHandle(0x4efb74),0,-1)) { muon=0; return; }
 *   eax=1; muon=1; ailActive(0x4efb7c)=1; return; */
extern unsigned char w46a_muon;    /* = $FA$_d_4e7000+0x5f0 (0x4e75f0) */
extern unsigned char w46a_dmusic;  /* = _dMusic (0x4efb68) */
extern unsigned long w46a_ss;      /* = ?scoreStart@@3PAXA (0x4efb8c) */
extern unsigned short w46a_mid;    /* = ?musicId@@3FA (0x5338d0) */
extern unsigned char w46a_ailon;   /* = ?ailActive@@3DA (0x4efb7c) */
extern void *w46a_mdh;             /* = ?musicDriverHandle@@3PAU_MDI_DRIVER@@A (0x4efb74) */

void __declspec(dllimport) __stdcall AIL_startup(void);
void __declspec(dllimport) __stdcall AIL_set_preference(long a, long b);
unsigned long __declspec(dllimport) __stdcall AIL_midiOutOpen(void **h, long a, long b);

void __stdcall w46a_InitMusic(void)
{
    unsigned long r;

    if (w46a_muon) {
        if (w46a_dmusic) {
            w46a_ss = 0;
            w46a_muon = 1;
            w46a_mid = 0xffff;
            return;
        }
        AIL_startup();
        AIL_set_preference(4, 0x78);
        r = AIL_midiOutOpen(&w46a_mdh, 0, -1L);
        if (r) {
            w46a_muon = 0;
            return;
        }
        w46a_muon = 1;
        w46a_ailon = 1;
    }
}