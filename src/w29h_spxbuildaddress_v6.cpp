// ?spxbuildaddress@@YADPAUNET_PROTOCOL@@PAUCN_INFO@@PAUNET_ADDRESS@@@Z @ 0x953c0
// (611264, 64 B: 62 code + 8bff census tail) — 6 patches, no maps (no
// globals; args are stack params at FA's slots: EDX = arg2 CN_INFO*,
// EDI = arg3 NET_ADDRESS*, arg1 untouched).
//
// Real C shape: r=1 (mov al,1) mid-body before the [edx+0xdc6] load store
// pair; the a+8 copy pointer is rematerialized as lea esi,[edi+8] for the
// +4 word store, and w=(char*)c+0xdca remats as lea eax,[edx+0xdca] for the
// w+4 word read. fitobj (EXACT, 0 relocs -> byte-verify = full proof):
// python3 tools/fitobj.py build/survey/probes/w29h_spxbuildaddress_v6.obj 0x953c0 \
//   --patch "0,6,8b542408565790" --patch "0xc,1,8a" --patch "0x12,1,82" \
//   --patch "0x1b,1,77" --patch "0x23,1,46" \
//   --patch "0x25,25,b0018b92c60d000089570466c74702ec8766c70702005f5ec3" \
//   build/survey/probes/w29h_spxbuildaddress_v6_fit.obj
struct NET_PROTOCOL;
struct CN_INFO;
struct NET_ADDRESS;

char spxbuildaddress(struct NET_PROTOCOL *p, struct CN_INFO *c, struct NET_ADDRESS *a)
{
    char r;
    char *w = (char *)c + 0xdca;
    char *as = (char *)a + 8;
    *(unsigned long *)as = *(unsigned long *)w;
    *(unsigned short *)(as + 4) = *(unsigned short *)(w + 4);
    r = 1;
    *(long *)((char *)a + 4) = *(long *)((char *)c + 0xdc6);
    *(unsigned short *)((char *)a + 2) = 0x87ec;
    *(unsigned short *)a = 2;
    return r;
}