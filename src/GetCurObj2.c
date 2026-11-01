// _GetCurObj2@4 @ rva 0x61b80 (16 B) — mov ecx,[esp+4] / call @GetCurObj@4 /
//   ret 4 — stdcall wrapper handing the arg to the fastcall GetCurObj.
extern int __fastcall GetCurObj(int a);

int __stdcall GetCurObj2(int a)
{
    return GetCurObj(a);
}