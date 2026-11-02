// t4_zero_v4: clean C hybrid base (non-volatile — the volatile lever had no
// byte effect, wall family 1). Expected CL stream (30 B = p_IsZeroMan_v1):
//   33 c0                xor eax,eax
//   8b 4c 24 04          mov ecx,[esp+4]
//   8b 11 85 d2          mov edx,[ecx]/test edx,edx   <- FA: 83 39 00 (3 B)
//   75 0f                jne fail
//   83 c1 04 40          add ecx,4/inc eax
//   83 f8 03             cmp eax,3
//   7c f1                jl loop                      <- FA: 7c f2 (1 B disp)
//   b8 01 00 00 00 c3    mov eax,1/ret
//   33 c0 c3             xor eax,eax/ret
// Patches: '6,4,833900' then '18,2,7cf2'.
int IsZeroMan_zr(long *p)
{
    int i;

    for (i = 0; i < 3; i++)
        if (p[i])
            return 0;
    return 1;
}