/* ?tcpfactory@@YAXPAUNET_PROTOCOL@@PADH@Z @ rva 0xa8f40 — v2: volatile byte
   zero store first, to stop CL hoisting the word store above it. */
typedef unsigned long ul;

extern ul __cdecl w30b_pfA(ul a);                      /* $FA$_t_4a8fe0 */
extern ul __cdecl w30b_pfB(ul a, ul b);                /* $FA$_t_4a9030 */

void __cdecl w30b_tpf(void *proto, char *host, int port)
{
    ul t;
    ul z = 0;
    ul h;

    *(volatile char *)(host + 10) = (char)z;
    *(unsigned short *)(host + 8) = 0x6ff;
    *(ul *)(host + 4) = z;
    h = *(ul *)((char *)proto + 0x14);
    t = w30b_pfA(h);
    *(ul *)host = w30b_pfB(h, t);
}