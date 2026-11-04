/* w46B_cpresetrwr_v3 - _CPResetRWR@0, FA rva 0x3e2b0 (254640), 144 B, tail 8d9b00000000+8da42400000000 (13-B census pad)
 *
 * FA anatomy (chunk 0x3e2b0..0x3e332, stdcall, cbRegs=2: push ebx; push edi):
 *   0x00 53 33 c0 57        push ebx; xor eax,eax (memset#1 zero reg); push edi
 *   0x04 b9 d6060000        mov ecx,0x6d6 (memset#1 count = 6936 dwords = 0x1b18 B)
 *   0x09 c7 05 <ifmScale+0x3f8> 00000000?? no: 01000000  mov dword [0x533fc8],1  (?ifmScale@@3JA+0x3f8)
 *   0x13 bf <targetV+0xd8>  mov edi,0x5376d8 (?targetV@@3UVIEW_VARS@@A+0xd8)
 *   0x18 33 db              xor ebx,ebx  (z = dedicated zero register for 6 stores)
 *   0x1a f3 ab              rep stosd (memset #1: zero 0x1b18 B @ targetV+0xd8)
 *   0x1c 8b 15 [_currentTicks]  mov edx,[0x549e78]
 *   0x22 89 1d [windowTypes+0x3f4]  [0x5375ec] = ebx (z)
 *   0x28 bf [ifmHandle+0xd4] mov edi,0x535688
 *   0x2d 89 1d [targetV+0x1c38]     [0x539238] = ebx
 *   0x33 8d 82 00050000     lea eax,[edx+0x500]
 *   0x39 b9 d6060000        mov ecx,0x6d6 (memset#2 count)
 *   0x3e 81 c2 00040000     add edx,0x400
 *   0x44 a3 [ifmScale+0x4]                 [0x533bd4] = eax (moffs store)
 *   0x49 33 c0              xor eax,eax (memset#2 zero)
 *   0x4b 89 1d [ifmHandle+0xc4]     [0x535678] = ebx
 *   0x51 88 1d [windowTypes+0x3f0]  byte [0x5375e8] = bl
 *   0x57 f3 ab              rep stosd (memset #2 @ ifmHandle+0xd4)
 *   0x59 66 89 1d [targetV+0xd0]    word [0x5376d0] = bx
 *   0x60 33 c9              xor ecx,ecx (fastcall arg = 0)
 *   0x62 89 1d [targetV+0x1c40]     [0x539240] = edx (ticks+0x400)
 *   0x68 89 1d [goalP+0x18]         [0x533ab8] = ebx
 *   0x6e e8                 call @SetPlayerTarget@4 (0)
 *   0x73 33 c9 / 0x75 e8    call @SetPlayerContact@4 (0)
 *   0x7a 5f / 0x7b 89 1d [ifmHandle+0xc8]=ebx / 0x81 5b / 0x82 c3 (pop edi, pop ebx order)
 *   anchor publics verified in layout syms: ifmScale@0x533bd0, targetV@0x537600,
 *   windowTypes@0x5371f8, ifmHandle@0x5355b4, goalP@0x533aa0, currentTicks@0x549e78.
 */
extern void *memset(void *dst, int val, unsigned len);
extern unsigned char ifmS_[0x400];     /* ?ifmScale@@3JA (reset region) */
extern long currentTicks;              /* _currentTicks */
extern unsigned char windowTypes[0x400];   /* _windowTypes */
extern unsigned char targetV_[0x1c44];     /* ?targetV@@3UVIEW_VARS@@A */
extern unsigned char ifmH_[0x1b40];        /* ?ifmHandle@@3PAUT_HANDLE@@A (interior refs of its block) */
extern short goalP_;                       /* ?goalP@@3FA */
extern long __fastcall SetPlayerTarget(long);
extern long __fastcall SetPlayerContact(long);

void __stdcall CPResetRWR(void)
{
    unsigned long ticks;
    long z;
    z = 0;
    *(long *)(ifmS_ + 0x3f8) = 1;
    memset(targetV_ + 0xd8, 0, 0x1b58);
    ticks = currentTicks;
    *(long *)(windowTypes + 0x3f4) = z;
    *(long *)(targetV_ + 0x1c38) = z;
    *(long *)(ifmS_ + 0x4) = ticks + 0x500;
    *(long *)(ifmH_ + 0xc4) = z;
    *(unsigned char *)(windowTypes + 0x3f0) = (unsigned char)z;
    memset(ifmH_ + 0xd4, 0, 0x1b58);
    *(unsigned short *)(targetV_ + 0xd0) = (unsigned short)z;
    SetPlayerTarget(0);
    *(long *)(targetV_ + 0x1c40) = ticks + 0x400;
    *(long *)((char *)&goalP_ + 0x18) = z;
    SetPlayerContact(0);
    *(long *)(ifmH_ + 0xc8) = z;
}