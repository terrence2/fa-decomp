/* w46D MAPDrawBG rva 139310 (0x42202e) v1 */
struct F24_POINT3;
struct WORD_POINT { short x, y; };
extern void __fastcall MAPWorldToScreen(struct F24_POINT3*, struct WORD_POINT*);   /* name-identical */
extern "C" void __fastcall G_SetScaleMax_q(int, int);    /* map: @G_SetScaleMax_q@8=@G_SetScaleMax@8 */
extern "C" int __fastcall MMAccessR_q(void*);            /* map: @MMAccessR_q@4=@MMAccessR@4 */
extern "C" int __fastcall G_Scale_q(int, int, int, int, int);  /* map: @G_Scale_q@20=@G_Scale@20 */
extern "C" void* th;                                     /* _th name-identical */
extern "C" void __cdecl w46d_t114(void);                 /* map: _w46d_t114=$FA$_t_422114 */
extern "C" void __cdecl w46d_t0aa(void);                 /* map: _w46d_t0aa=$FA$_t_4220aa */
extern unsigned long w46d_mfa;                           /* map: _w46d_mfa=?mcFlyAll@@3DA+0x20 */

void __stdcall MAPDrawBG(void)                           /* ?MAPDrawBG@@YGXXZ name-identical */
{
    struct WORD_POINT a, b;
    w46d_t114();
    G_SetScaleMax_q(0x7fff, 0x7fff);
    MAPWorldToScreen((struct F24_POINT3*)((char*)th + 0x61), &a);
    MAPWorldToScreen((struct F24_POINT3*)((char*)th + 0x6d), &b);
    if (*(unsigned char*)(w46d_mfa + 0x11) & 0x10)
        w46d_t0aa();
    G_Scale_q(MMAccessR_q((void*)w46d_mfa), (int)b.x, (int)a.y,
              (int)a.x - (int)b.x + 1, (int)b.y - (int)a.y + 1);
}