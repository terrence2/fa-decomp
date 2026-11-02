// _DialogUpdateString @ rva 0x87780 (64 B) — cdecl, 3 params: ushort id,
// char* s, unsigned long w. FA: push esi/edi; si=[esp+0xc](id); ecx=esi;
// call @DialogGetPtr@4 (fastcall, ushort formal -> no movzx); edi=eax;
// push 0; eax=[esp+0x14](=p2 s: esp is E-12 after push 0); push eax;
// push esi; call _DialogSetString@12 (stdcall, cleans 12 -> esp back to
// E-8); ax=[esp+0x14](=p3 w: E-8+0x14=E+0xc, 16-bit view); push edi (arg
// for DialogDraw pre-staged); [edi+0x18]=ax; [edi+0x1c]=0x3e8;
// call ?DialogDraw@@YGXPAX@Z; pop edi/esi; ret.
extern void *__fastcall DialogGetPtr(unsigned short id);   /* @DialogGetPtr@4 identity */
extern void __stdcall DialogSetString(unsigned short id, char *s, int z);   /* _DialogSetString@12 identity */
extern void __stdcall DialogDraw(char *d);   /* -> ?DialogDraw@@YGXPAX@Z */

void __cdecl DialogUpdateString(unsigned short id, char *s, unsigned short w)
{
    void *d;

    d = DialogGetPtr(id);
    DialogSetString(id, s, 0);
    *(unsigned short *)((char *)d + 0x18) = (unsigned short)w;
    *(unsigned short *)((char *)d + 0x1c) = 0x3e8;
    DialogDraw(d);
}