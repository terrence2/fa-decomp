// _SendMessageA@16 @ rva 0xd3474 (6 B) — USER32 import pass-through thunk.
extern void *impSendMessageA[];
unsigned long __declspec(naked) __stdcall SendMessageA(void *a, void *b, void *c, void *d)
{
    __asm { jmp dword ptr [impSendMessageA] }
}
