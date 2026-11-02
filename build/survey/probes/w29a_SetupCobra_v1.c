// 0x6a6a0 ?SetupCobra@@YAGPAUGlobalData@@@Z (80 B) — v1
// short __cdecl(GlobalData *): all three init failures return g->[0xae]
// (the mov ax,[esi+0xae] block is the shared epilogue; CleanVideo's
// failure path falls through CleanCobra into it).
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
        return g->f0ae;
    r = w29a_InitVideo(g);
    if (r != 0)
    {
        w29a_CleanCobra(g);
        return g->f0ae;
    }
    r = w29a_InitAudio(g);
    if (r != 0)
    {
        w29a_CleanVideo(g);
        w29a_CleanCobra(g);
        return g->f0ae;
    }
    return 0;
}