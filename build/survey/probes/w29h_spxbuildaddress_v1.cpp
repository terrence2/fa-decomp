// ?spxbuildaddress@@YADPAUNET_PROTOCOL@@PAUCN_INFO@@PAUNET_ADDRESS@@@Z @ 0x953c0 (64 B)
// v1: char-returning cdecl, 3 fn params. w = (char*)p+0xdca materialized for
// the +4 word read (lea eax,[edx+0xdca]; mov ax,[eax+4]); as = (char*)a+8 for
// the [esi+4] word store.
struct NET_PROTOCOL;
struct CN_INFO;
struct NET_ADDRESS;

char spxbuildaddress(struct NET_PROTOCOL *p, struct CN_INFO *c, struct NET_ADDRESS *a)
{
    char *w = (char *)p + 0xdca;
    char *as = (char *)a + 8;
    *(unsigned long *)as = *(unsigned long *)w;
    *(unsigned short *)(as + 4) = *(unsigned short *)(w + 4);
    *(long *)((char *)a + 4) = *(long *)((char *)p + 0xdc6);
    *(unsigned short *)((char *)a + 2) = 0x87ec;
    *(unsigned short *)a = 2;
    return 1;
}