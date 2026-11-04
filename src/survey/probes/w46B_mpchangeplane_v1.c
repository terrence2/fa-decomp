/* w46B_mpchangeplane_v1 - ?MPChangePlaneType@@YGXGPAD@Z, FA rva 0x712c0 (463552), 112 B, tail 8d642400 (4 B census pad)
 *
 * FA anatomy (stdcall YG, ret 8, FPO esp, locals 4 dwords = char buf[16], cbRegs=2 esi/edi):
 *   sub esp,0x10; mov eax,[numComputers]; cmp eax,1; nop; push esi/edi; je exit
 *   mov edx,1; mov ecx,[arg1 slot]; mov byte [esp+8],0x46;
 *   call @OBJAlias@8 (fastcall: ecx=u16 plane alias, edx=1); mov [esp+9],ax
 *   mov edi,[esp+0x20] (arg2 name); inline strlen: mov ecx,-1; xor eax; repnz scasb;
 *     not ecx (len incl NUL); sub edi,ecx (edi=str); mov eax,ecx; shr ecx,2;
 *     mov esi,edi; lea edi,[esp+0xb] (buf+3); rep movsd; mov ecx,eax;
 *     push 1 | and ecx,3 | push 0x10 | rep movsb  (scheduling: broadcast-arg pushes interleave)
 *   lea ecx,[esp+0x10] (buf); push ecx; push -1; call $FA$_t_46b260 (stdcall (-1,buf,16,1));
 *   xor ecx,ecx; call ?MPFlushAll@@YIXD@Z (fastcall, arg 0);
 *   pop edi/esi; add esp,0x10; ret 8
 */
extern unsigned short __fastcall OBJAlias(unsigned short id, int which);  /* @OBJAlias@8 */
extern void __stdcall MPBroadcast(int dest, char *buf, int size, int prio); /* $FA$_t_46b260 */
extern void __fastcall MPFlushAll(char flags);   /* ?MPFlushAll@@YIXD@Z */
extern long numComputers;                        /* _numComputers */

void __stdcall MPChangePlaneType(unsigned short a, char *name)
{
    char buf[16];
    if (numComputers != 1)
    {
        buf[0] = 0x46;
        *(unsigned short *)(buf + 1) = OBJAlias(a, 1);
        strcpy(buf + 3, name);
        MPBroadcast(-1, buf, 16, 1);
        MPFlushAll(0);
    }
}