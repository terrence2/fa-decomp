/* wave37D COLTerrainBlocking 0x2e010 (80 B) v1 - full-body asm (dx reg-arg to _Collision@56) */
extern unsigned char w37d_thType;    /* _curThing+0x9 */
extern unsigned short w37d_curIdW;   /* _curId */
extern char w37d_ct11;               /* _curThing+0x11 */
extern char w37d_curb;               /* _curThing+0x0 */
extern long __stdcall w37d_col14(long, long, long, long, long, long, long, long,
                                  long, long, long, long, long, long);  /* _Collision@56 */
int __fastcall COLTerrainBlocking(int t)
{
    __asm {
        sub esp, 10h
        lea eax, [esp+4]
        push 0
        lea edx, [esp+6]
        push 0
        push 0
        push 0
        push eax
        add ecx, 11h
        push edx
        mov al, BYTE PTR w37d_thType
        push 201h
        push 0
        mov dx, WORD PTR w37d_curIdW
        push 0
        push ecx
        push OFFSET w37d_ct11
        push eax
        push OFFSET w37d_curb
        push edx
        call w37d_col14
        cmp WORD PTR [esp+2], 0FFFFh
        sete cl
        mov al, cl
        add esp, 10h
    }
}
