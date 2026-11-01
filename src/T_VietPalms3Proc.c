// ?T_VietPalms3Proc@@YAXJ@Z @ rva 0xa5850 (16 B) — cdecl stack-param thunk:
// mov eax,[esp+4]/push eax/call ?T_ForestProc@@YAXJ@Z ($FA$_t_4a4de0)/
// add esp,4/ret. probe w13b_VietPalms1.
extern void forestProcX_(unsigned long a);

void T_VietPalms3Proc(unsigned long a)
{
    forestProcX_(a);
}