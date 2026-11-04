/* _GRPWingman@4 @ 0x5e9f0 (80 B)  FA layout (raw bytes):
   sub esp,4; lea eax,[esp]; push 0/push eax/push ecx; call @GRPPart@12;
   cmp al,1; je +7; [xor ax,ax; add esp,4; ret]; mov eax,[esp];
   mov cl,[_groupSizes+eax]; cmp cl,2; jae +7; [xor ax,ax; add esp,4; ret];
   mov eax,[esp]; add esp,4; shl eax,2; mov ax,[_groupIds+0x2+eax*4]; ret.
   Early-return shape: each `if (c) return 0;` -> test-je-continues, ret0
   epilogue at the fall-through. Success word = low word of dword-array elem
   out[0]*4 (shl 2 + SIB *4), read as 16-bit. */
extern unsigned char __stdcall GRPPart_q(unsigned long a, unsigned long *out, unsigned long z);
extern unsigned char grpSizesB[];   /* -> _groupSizes */
extern unsigned long grpDwBase[];   /* -> _groupIds+0x2 */

unsigned short __fastcall GRPWingman_q(unsigned long a)
{
    unsigned long out[1];
    if (GRPPart_q(a, out, 0) != 1)
        return 0;
    if (grpSizesB[out[0]] < 2)
        return 0;
    return *(unsigned short *)(&grpDwBase[out[0] * 4]);
}