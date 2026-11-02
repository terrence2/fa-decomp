// _OBJShutdown@0 @ rva 0x8f420 (64 B) — FA asm (FPO frame): 57 (push edi —
//   ONE prolog push, CL MERGES the two const-size memsets' edi push/pop)/
//   e8 @MMFreePtr@4 (fastcall MMFreePtr(wSayThing))/bf <wingSay+0xe64>/
//   e8 @MMFreePtr@4 (or the second call form)/c7 05 <wingSay+0xe64> 0
//   (hidden store: mov dword [?wingSay@@3PAUSAY@@A+0xe64],0 — zero the
//   say-thing slot)/ then both const-size memsets INLINED as one
//   push edi/mov edi,imm/mov ecx,imm/rep stosd sequence for
//   _objPtrs (0xe10 B) and ?COMMENT_TYPE@@3W4__unnamed@@A+0x150 (0x708 B).
//   Plain C exact — the two memset calls merge their edi prolog/piplogue
//   exactly like InitTmapRemaps (wave 19) (probe
//   build/w4probe/b20b_objsh_v1.obj — exact).
extern void *wSayThing;      /* ?wingSay@@3PAUSAY@@A+0xe64 */
extern char objPtrs[];       /* _objPtrs, 0xe10 B */
extern char cmtZero[];       /* ?COMMENT_TYPE@@3W4__unnamed@@A+0x150, 0x708 B */
extern void *memset(void *, int, unsigned);
extern void __fastcall MMFreePtr(void *p);

void __stdcall OBJShutdown(void)
{
    MMFreePtr(wSayThing);
    wSayThing = 0;
    memset(objPtrs, 0, 0xe10);
    memset(cmtZero, 0, 0x708);
}