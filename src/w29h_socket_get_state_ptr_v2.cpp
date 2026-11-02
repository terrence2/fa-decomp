// ?socket_get_state_ptr@@YAPAUsocket_state@@I@Z @ 0xa30c0 (667840, 64 B:
// 52 code + 0500000000+8da42400000000 census tail) — EXACT, NO maps, NO
// patches. Pure CL C++ 4.2: decl matching FA's decor (struct socket_state
// = 0x32-byte record with long at +0xc, byte at +0x18; struct
// SOCKET_STATE_LIST with count at 0 and entries at +0x424) reproduces
// every byte incl. the xor ebx,ebx zero cache and cmp [eax+0x18],bl.
// The only steer: the probe body must increment i BEFORE the pointer
// advance (v1's `for(...;i++)` latch emitted add eax,0x32; inc edx —
// FA has inc edx; add eax,0x32).
//
// fitobj (EXACT):
// python3 tools/fitobj.py build/survey/probes/w29h_socket_get_state_ptr_v2.obj 0xa30c0 \
//   build/survey/probes/w29h_socket_get_state_ptr_v2_fit.obj
// (reloc ?socket_list@@3USOCKET_STATE_LIST@@A resolves as-is: CL bakes
// +0x424 into the mov eax imm and 0 into the two cmp disps.)
struct socket_state {
    unsigned char s0[0xc];
    long s0c;
    unsigned char s10[8];
    unsigned char s18;
    unsigned char pad[0x32 - 0x19];
};

struct SOCKET_STATE_LIST {
    long count;
    unsigned char pad[0x420];
    struct socket_state ss[2];
};

extern struct SOCKET_STATE_LIST socket_list;

struct socket_state *socket_get_state_ptr(unsigned int id)
{
    struct socket_state *e = &socket_list.ss[0];
    long i;
    for (i = 0; i < socket_list.count; ) {
        if (e->s18) {
            if (e->s0c == id)
                return e;
        }
        i = i + 1;
        e = (struct socket_state *)((char *)e + 0x32);
    }
    return 0;
}