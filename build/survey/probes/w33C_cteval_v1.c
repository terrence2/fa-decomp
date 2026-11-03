extern int __stdcall Dist(int a, int b);
extern int cT;     /* -> _curThing+0x11 */
extern int srvT;   /* -> _serviceTicks+0xf4 */

int CTEval_hrzdisttotgt(void)
{
    int *p = &cT;
    int v[3];
    int t;

    v[0] = cT;
    v[2] = p[2];
    v[1] = p[1];
    t = srvT + 0x11;
    v[1] = *(int *)(t + 4);
    return Dist(&v[0], t) >> 8;
}