// @SAYMsg@4 @ rva 0x8b4b0 = 570544, 112 B (fastcall 1 arg -> ecx; FA:
//   push ebx; push esi; mov ax,[ecx+2]; esi=ecx; bl=0; cmp ax,[curId] word;
//   je L1; cmp ax,0x8003 jb; cmp ax,0x800b jbe L1; test ax; je L1; push eax;
//   bl=1; call _PushCurObj@4 // L1: mov ax,[esi+2]; same range tests;
//   push esi; push 6; call _CallUtilProc (cdecl 2); add esp,8; jmp L5 /
//   else: push esi; call _SAYDefaultSayProc; add esp,4 // L5: test bl; je;
//   call @PopCurObj@0; pop esi; pop ebx; ret).
typedef struct { unsigned char pad[2]; unsigned short id; } O26;
extern unsigned short w26_curId2; /* map _w26_curId2=_curId */
extern void __stdcall PushCurObjQ(unsigned int c); /* map _PushCurObjQ@4=_PushCurObj@4 */
extern int __cdecl CallUtilProcQ(unsigned int code, void *o); /* map _CallUtilProcQ=_CallUtilProc */
extern void __cdecl SAYDefaultSayProcQ(void *o); /* map _SAYDefaultSayProcQ=_SAYDefaultSayProc */
extern void __fastcall PopCurObjQ(void); /* map @PopCurObjQ@0=@PopCurObj@0 */

void __fastcall w26c_SAYMsg_q(O26 *obj)
{
    unsigned short id = obj->id;
    int pushed = 0;
    if (id != w26_curId2 && !(id >= 0x8003 && id <= 0x800b) && id != 0) {
        PushCurObjQ(id);
        pushed = 1;
    }
    if (!(id >= 0x8003 && id <= 0x800b) && id != 0)
        CallUtilProcQ(6, obj);
    else
        SAYDefaultSayProcQ(obj);
    if (pushed) PopCurObjQ();
}