// w35D_bd9d0_v3: nameless 48-B chunk @ 0xbd9d0 (0 params, fpo, cdecl ret).
// v1/v2 emit eax loads/arg-window staging off-by-one vs FA (v1: arg staging
// xor eax inside group 2; v2: group-1 load inside load window 2). v3: pure C
// 13-arg call, no local (v2 shape), hoping CL's push-stream scheduling puts
// the ushort load (arg a4) AFTER the group-1 pushes and groups 0x508770/0/4
// AFTER the load; probe the eax-identity variant too.
extern unsigned char w35d_ct[0x1000];
extern long __stdcall CreateMove(long a1, long a2, long a3, long a4, long a5,
                                 long a6, long a7, long a8, long a9, long a10,
                                 long a11, long a12, long a13);

unsigned long w35d_bd9d0(void)
{
    CreateMove((long)(w35d_ct + 0x38), 0, 4,
               (long)*(unsigned short *)(void *)(w35d_ct + 0xe4), 4, 0, 1, 0,
               1, 0, 8, 0x10, 0x7fff);
    return 0;
}