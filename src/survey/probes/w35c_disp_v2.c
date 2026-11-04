// w35C #5 dispatcher v2: if/else spelling to get FA's je-forward block order
// (FA: test cl,cl / je -> the 0x1b block at chunk end; body straight-line).
extern long w35c_dg1;   /* map _w35c_dg1=_curThing+0x231 */
extern long w35c_dg2;   /* map _w35c_dg2=_curThing+0x34 */
extern void __fastcall EnterState(int st);

void __cdecl Chunk_b9630(void)
{
    char *t = (char *)w35c_dg1;
    if (t[0xe8]) {
        if (w35c_dg2 & 0xffffff00L)
            return;
        EnterState(0x1a);
    } else {
        EnterState(0x1b);
    }
}