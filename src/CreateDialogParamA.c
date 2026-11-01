// _CreateDialogParamA@20 @ rva 0xd34fe (6 B) — USER32 import pass-through thunk.
extern void *impCreateDialogParamA[];
unsigned long __declspec(naked) __stdcall CreateDialogParamA(void *a, void *b, void *c, void *d, void *e)
{
    __asm { jmp dword ptr [impCreateDialogParamA] }
}
