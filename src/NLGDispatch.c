/* __NLG_Dispatch @ rva 0xd4979 (pop ecx / pop ebx / ret 4) */
void __declspec(naked) _NLG_Dispatch(void)
{
    __asm {
        pop ecx
        pop ebx
        ret 4
    }
}