// @WriteCmdBufProcptr@4 @ rva 0x62e60 (27 B) — spills the fastcall param into a
//   stack local AFTER pushing arg 3 (mov [esp+4],ecx), then fastcalls
//   WriteCmdBuf(1, &tmp, 4); CL schedules lea edx,&tmp before the push exactly
//   like FA (probe d125).
extern void __fastcall WriteCmdBuf(int a, int *b, int c);
void __fastcall WriteCmdBufProcptr_q(int p)
{
    int tmp = p;
    WriteCmdBuf(1, &tmp, 4);
}
