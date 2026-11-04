/* _CTDo_move rva 0x64e80, 128 B (126 code + 5 tail 05 00 00 00 00).
 * FA: push ebx,esi,edi,ebp; 5 bare cdecl calls -> si/di/ebp/bx/eax;
 * mov cl,[st+0xec]; test; jne epilogue;
 * 66 8b 0d [st+0xfc] (m=cx); push eax (e5); 66 a1 [st+0x100] (n=ax);
 * push ebx; push eax; cmp ebp,0x7fffffff; sete dl; push ecx,edx,ebp,edi,esi;
 * call _MVRMove@32; mov word [st+0x100],0; mov word [st+0xfc],0;
 * mov eax,1; mov [st+0xf0],al; mov [st+0xf8],al; pops; ret */
extern unsigned short w38d_f00X(void);
extern short w38d_e50X(void);
extern long w38d_f60X(void);
extern short w38d_fc0X(void);
extern long w38d_fa0X(void);
extern void __stdcall MVRMove(short, short, long, char, short, short, short, long);
extern char w38d_stecX, w38d_stf0X, w38d_stf8X;
extern unsigned short w38d_stfcX, w38d_st100X;

void CTDo_move(void)
{
    unsigned short a, m, n;
    short e2, e7, z;
    long e3, e5, one;

    a = w38d_f00X();
    e2 = w38d_e50X();
    e3 = w38d_f60X();
    e7 = w38d_fc0X();
    e5 = w38d_fa0X();
    if (!w38d_stecX) {
        z = (e3 == 0x7fffffff);
        m = w38d_stfcX;
        n = w38d_st100X;
        MVRMove(a, e2, e3, z, m, n, e7, e5);
        w38d_st100X = 0;
        w38d_stfcX = 0;
        one = 1;
        w38d_stf0X = one;
        w38d_stf8X = one;
    }
}