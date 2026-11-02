// ?pkt_set_header@@YAXHPAUNET_PKT@@H@Z @ rva 0x5d040 = 380992, 32 B
// (25 code c3 + 0500000000 census tail).  22 rel32 callers — already
// converted C callers map _pkt_set_header=... so keep cdecl 3-arg void.
// FA asm: mov eax,[esp+0xc] (p3) / mov ecx,[esp+8] (p2 pkt) / mov [ecx],ax
// (pkt->w0 = word of p3) / mov eax,[eax*4 + 0x4f2b38]  (=_campaignPlane+0x1c8
// table indexed by p3) / add ax,4 (16-bit) / mov [ecx+2],ax / ret.
// p1 ([esp+4]) is never read (dead param).
extern unsigned char campaignPlane[];

void __cdecl w25c_pktsethdr_q(int a, unsigned short *pkt, int v)
{
    *(unsigned short *)pkt = (unsigned short)v;
    *(unsigned short *)((char *)pkt + 2) =
        (unsigned short)(*(unsigned long *)(campaignPlane + 0x1c8 + v * 4) + 4);
}