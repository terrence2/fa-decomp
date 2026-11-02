// 0x6a6a0 ?SetupCobra@@YAGPAUGlobalData@@@Z — v2 (goto layout)
// FA shape: IC-fail jne -> the shared "mov ax,[esi+0xae]; pop; ret"
// epilogue at the END; IV-fail jne -> the shared CleanCobra block;
// IA-fail jne +5 past the inline "return 0"; CleanVideo falls through
// into CleanCobra. Expressed with gotos to place the shared blocks last.
struct W29GD { char pad[0xae]; short f0ae; };
extern short __cdecl w29a_InitCobra(struct W29GD *);    /* $FA$_t_469fd0 */
extern short __cdecl w29a_InitVideo(struct W29GD *);    /* $FA$_t_46a2e0 */
extern short __cdecl w29a_InitAudio(struct W29GD *);    /* $FA$_t_46a680 */
extern short __cdecl w29a_CleanVideo(struct W29GD *);   /* $FA$_t_46a670 */
extern short __cdecl w29a_CleanCobra(struct W29GD *);   /* $FA$_t_46a2b0 */

short __cdecl w29a_SetupCobra(struct W29GD *g)
{
    short r;
    r = w29a_InitCobra(g);
    if (r != 0)
        goto Lfailret;
    r = w29a_InitVideo(g);
    if (r != 0)
        goto Lclean;
    r = w29a_InitAudio(g);
    if (r == 0)
        return 0;
    w29a_CleanVideo(g);
Lclean:
    w29a_CleanCobra(g);
Lfailret:
    return g->f0ae;
}