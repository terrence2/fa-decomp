/* NetSetFactoryTCP - FA rva 0xacba0 (707488) - EXACT probe verdict, tier1_a_r2.json entry 'NetSetFactoryTCP_v2'
 * Form: plain C
 * Levers: if-arm-first + zero tail
 * Maps: _netFactoryMake=$FA$_t_4ae660
 * Probes: v1,v2
 */
typedef void (__cdecl *F3)(void *a, void *b, int c);
extern void *__cdecl netFactoryMake(int a);

void NetSetFactoryTCP(void *inf)
{
    void *f = netFactoryMake(1);
    if (f) {
        (*(F3 *)((char *)f + 0x66))(f, inf, 0xc);
        return;
    }
    *(void **)inf = 0;
    *(void **)((char *)inf + 4) = 0;
    *(void **)((char *)inf + 8) = 0;
}
