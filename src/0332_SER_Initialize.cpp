/* w46D SER_Initialize rva 311616 (0x44c140) v1 */
struct CN_INFO;
extern long __cdecl SER_Initialize1(struct CN_INFO*, long);     /* ?SER_Initialize1@@YAJPAUCN_INFO@@J@Z */
extern long __cdecl SER_Initialize2(struct CN_INFO*, long);     /* ?SER_Initialize2@@YAJPAUCN_INFO@@J@Z */
extern long __cdecl SER_Initialize2_5(struct CN_INFO*, long);   /* ?SER_Initialize2_5@@YAJPAUCN_INFO@@J@Z */
extern long __cdecl SER_Initialize3(struct CN_INFO*, long);     /* ?SER_Initialize3@@YAJPAUCN_INFO@@J@Z */
extern long __cdecl SER_Initialize4(struct CN_INFO*, long);     /* ?SER_Initialize4@@YAJPAUCN_INFO@@J@Z */
extern long __cdecl SER_Initialize5(struct CN_INFO*, long);     /* ?SER_Initialize5@@YAJPAUCN_INFO@@J@Z */
extern void __stdcall w46d_uip(void*);         /* map: _w46d_uip@4=_UnInitializePort@4 */
extern void __cdecl w46d_ssdn(void);           /* map: _w46d_ssdn=?SER_Shutdown@@YAXXZ */
extern unsigned long w46d_sokx;                /* map: _w46d_sokx=?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x234 */

long __cdecl SER_Initialize(struct CN_INFO* p, long a)   /* ?SER_Initialize@@YAJPAUCN_INFO@@J@Z name-identical */
{
    if (SER_Initialize1(p, a) != 2)
        return 0;
    if (SER_Initialize2(p, a) != 2)
        return 0;
    if (SER_Initialize2_5(p, a) != 2) {
        w46d_uip((void*)w46d_sokx);
        return 0;
    }
    if (SER_Initialize3(p, a) != 2) {
        w46d_uip((void*)w46d_sokx);
        return 0;
    }
    if (SER_Initialize4(p, a) != 2) {
        w46d_ssdn();
        return 0;
    }
    if (SER_Initialize5(p, a) != 2) {
        w46d_ssdn();
        return 0;
    }
    return 1;
}