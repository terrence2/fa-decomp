/* chunk ?UCONFIG_load_EA_CFG@@YGPAUCONFIG@@XZ @ rva 0xaecf0
 * (dec 716016, 80 B) — void* __stdcall(void):
 *   h = LoadFile(state_funcs_list+0x104, &buf, 0, 0);   (_LoadFile@16)
 *   if (!h) return 0;
 *   p = MMAccessR(h);                                    (@MMAccessR@4)
 *   if (p->f0 == 0x28 && buf == 0x157) return p;
 *   MMFreeHandle(h);                                     (@MMFreeHandle@4)
 *   return 0;
 * FA: buf local spilled (sub esp,4; lea eax,[esp] before esi push);
 * h held in esi; second test jumps to shared epilogue on true.
 */
struct W31G_CFG { unsigned long f0; };
extern char w31g_sfl;                       /* ?state_funcs_list@@3PAU__unnamed@@A+0x104 */
extern long __stdcall w31g_lf(char *, void **, int, int);
extern void *__fastcall w31g_mar(long);
extern void __fastcall w31g_mfr(long);

void *__stdcall w31g_ucfg(void)
{
    void *buf;
    long h;
    struct W31G_CFG *p;
    h = w31g_lf((char *)&w31g_sfl, &buf, 0, 0);
    if (h == 0)
        return 0;
    p = w31g_mar(h);
    if (p->f0 == 0x28 && buf == (void *)0x157)
        return p;
    w31g_mfr(h);
    return 0;
}
