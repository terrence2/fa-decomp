// @SAYMsg@4 @ rva 0x8b4b0 = 570544, 112 B (fastcall; FA regs: ebx=flag
//   (unsigned char: xor bl,bl / mov bl,1), esi=obj copy, id re-read per
//   block (mov ax,[ecx+2] then mov ax,[esi+2]); push eax with stale uppers
//   (param read as 16-bit).  Patched window: offset 0xb, opcode byte — FA
//   compares reg-left (66 3b 05, cmp ax,[curId]) while CL 4.2 canonical-
//   ises 16-bit mem/reg compares to mem-left (66 39) regardless of source
//   spelling or operand order (exp e1-e5 all identical); only opcode byte
//   differs, disp32 at 0xc-0xf is the masked reloc — patch is legal
//   (wave-17 sib-45 precedent).
typedef struct { unsigned char pad[2]; unsigned short id; } O26;
extern unsigned short w26_curId2; /* map _w26_curId2=_curId */
extern void __stdcall PushCurObjQ(unsigned short c); /* map _PushCurObjQ@4=_PushCurObj@4 */
extern int __cdecl CallUtilProcQ(unsigned int code, void *o); /* map _CallUtilProcQ=_CallUtilProc */
extern void __cdecl SAYDefaultSayProcQ(void *o); /* map _SAYDefaultSayProcQ=_SAYDefaultSayProc */
extern void __fastcall PopCurObjQ(void); /* map @PopCurObjQ@0=@PopCurObj@0 */

void __fastcall w26c_SAYMsg_q(O26 *o)
{
    unsigned char pushed = 0;
    if (o->id != w26_curId2 && !(o->id >= 0x8003 && o->id <= 0x800b) && o->id != 0) {
        PushCurObjQ(o->id);
        pushed = 1;
    }
    if (!(o->id >= 0x8003 && o->id <= 0x800b) && o->id != 0)
        CallUtilProcQ(6, o);
    else
        SAYDefaultSayProcQ(o);
    if (pushed) PopCurObjQ();
}/* patch 11,1,3b */