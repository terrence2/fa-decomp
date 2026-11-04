/* ?net_add_self@@YAXPADH@Z @ 0xae170 (144 B): register this machine as a
 * network player (char *name, long slot).  v2: signed counter loads (jge),
 * shared eax=1 register reused by the f0 increment (add ecx,eax), pl[8]
 * increment last (a1-load / pop / inc eax / pops / a3-store / pop ebx).
 * prologue: push ebx; mov ecx,0x10; push esi/edi/ebp
 *   MMPushAllocId(0x10);  p = MMAllocPtr(0x91de, 0);  MMPopAllocId();
 *   edx = a2; edi = a1; ecx,-1/eax,0; slot-store [edx*4+0x577eae]; scasb
 *   strcpy inline -> (char*)p+8
 *   mov eax,1; p[0x37]=al; p[0x36]=al; p[0x38]=al; *(ulong*)(p+0x32)=edx
 *   mov ecx,[pl+0]; mov ebp,[pl+4]; add ecx,eax; mov [pl+0],ecx;
 *   cmp ecx,ebp; jge skip; mov [pl+4],ecx
 *   a1 [pl+8]; 5d; 40 inc eax; 5f; 5e; a3 [pl+8]; 5b; c3
 */
extern "C" {
    extern unsigned char player_list[];                     /* 0x577e48 */
    extern unsigned long __fastcall MMPushAllocId(long id);
    extern unsigned long __fastcall MMAllocPtr(unsigned long size, unsigned long a2);
    extern void __fastcall MMPopAllocId(void);
    extern char *strcpy(char *dst, const char *src);
}

void net_add_self(char *a1, long a2)
{
    unsigned char *p;
    unsigned long v;

    MMPushAllocId(0x10);
    p = (unsigned char *)MMAllocPtr(0x91de, 0);
    MMPopAllocId();
    *(unsigned long *)((char *)player_list + 0x66 + 4 * a2) = (unsigned long)p;
    strcpy((char *)p + 8, a1);
    v = 1;
    p[0x37] = (unsigned char)v;
    p[0x36] = (unsigned char)v;
    p[0x38] = (unsigned char)v;
    *(unsigned long *)((char *)p + 0x32) = a2;
    *(long *)player_list = *(long *)player_list + v;
    if (*(long *)player_list < *(long *)(player_list + 4))
        *(long *)(player_list + 4) = *(long *)player_list;
    *(long *)(player_list + 8) = *(long *)(player_list + 8) + 1;
}