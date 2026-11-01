/* do_start_asm @ rva 0xd0604 (push esi / ret; FA tail 8b c0 is filler) */
void __declspec(naked) do_start(void)
{
    __asm {
        push esi
        ret
    }
}