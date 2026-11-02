// ?spxbuildaddress@@YADPAUNET_PROTOCOL@@PAUCN_INFO@@PAUNET_ADDRESS@@@Z @ 0x953c0
// v3: like v2 but w= (address-only) first, load v from w; r=1 mid-body.
struct NET_PROTOCOL;
struct CN_INFO;
struct NET_ADDRESS;

char spxbuildaddress(struct NET_PROTOCOL *p, struct CN_INFO *c, struct NET_ADDRESS *a)
{
    char r;
    char *w = (char *)c + 0xdca;
    unsigned long v = *(unsigned long *)w;
    char *as = (char *)a + 8;
    *(unsigned long *)as = v;
    *(unsigned short *)(as + 4) = *(unsigned short *)(w + 4);
    r = 1;
    *(long *)((char *)a + 4) = *(long *)((char *)c + 0xdc6);
    *(unsigned short *)((char *)a + 2) = 0x87ec;
    *(unsigned short *)a = 2;
    return r;
}