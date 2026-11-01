// _AIL_resume_sequence@4 @ rva 0xd3594 (6 B) — AIL_resume_sequence (Miles AIL) sound import pass-through thunk.
extern void *impAIL_resume_sequence[];
unsigned long __declspec(naked) __stdcall AIL_resume_sequence(void *a0)
{
    __asm { jmp dword ptr [impAIL_resume_sequence] }
}
