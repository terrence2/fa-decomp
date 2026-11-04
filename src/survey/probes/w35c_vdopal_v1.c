// w35C #2: ?ReadVDOPalette@@YADFPAUVDOHEADER@@QAUT_RGB@@@Z @ rva 0xac180
// (80 B). FA: push esi / xor eax,eax / esi=a2(VDOHEADER*) / push edi /
// cmp word [esi+0x18],ax / edi=-1 / je tail / movsx eax,[esi+0x16] (SHORT
// w16) / ecx=a3(pal) / lea edi,[eax+eax*2] (want=3*w16) / mov ax,[esp+0xc]
// (a1 short n, only ax) / push edi,ecx,eax / call _LibRead / add esp,0xc /
// cmp edi,eax / je tail / mov word ds:?vdoExitCode@@3FA,4 (66 c7 05) /
// tail: cmp word [esi+0x18],0 / jne sete / mov al,1 / ret; sete al / ret.
// probe-own func name + maps (C++-mangled FA chunk).
typedef struct VDOHDRS { unsigned char pad[0x16]; short w16; short w18; } VDOHDR;
typedef struct T_RGBS { unsigned char q[1]; } T_RGBS;

extern long __cdecl LibRead(short idx, void *dst, long len);
extern short vdoExitCodeq;

char __cdecl ReadVDOPaletteq(short n, VDOHDR *h, T_RGBS *pal)
{
    long r = 0;
    long want = -1;

    if (h->w18 != (short)r) {
        want = 3L * (long)h->w16;
        r = LibRead(n, pal, want);
        if (want != r)
            vdoExitCodeq = 4;
    }
    if (h->w18 == 0)
        return 1;
    return (char)(want == r);
}