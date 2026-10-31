/* WRFogLayerUpdate — pilot decompilation (chunk @ rva 0xb06c0, size 0x50).
 *
 * FA asm:
 *   push esi; mov ecx,0x33; mov esi,[esp+8]; call @Rand@4;
 *   movsx eax,ax; sub eax,0x19;
 *   mov ecx,[esi+0xfe]; add ecx,eax; cmp ecx,0xd9; mov eax,ecx;
 *   mov [esi+0xfe],ecx; jge L;  mov [esi+0xfe],0xd9; pop esi; ret
 *   L: cmp eax,0xeb; jle R; mov [esi+0xfe],0xeb; pop esi; ret
 * FPO: offStart=0xb06c0 cbProcSize=0x50 cdwLocals=0 cbParams=1 flags=06 01
 */
#pragma pack(push, 1)
typedef struct WRFOG { char pad[0xfe]; long fog; } WRFOG;
#pragma pack(pop)

extern long __fastcall Rand(long n);

long WRFogLayerUpdate(WRFOG *p)
{
    long v;
    p->fog = p->fog + (short)Rand(51) - 0x19;
    v = p->fog;
    if (v < 0xd9)
        p->fog = 0xd9;
    else if (v > 0xeb)
        p->fog = 0xeb;
    return v;
}