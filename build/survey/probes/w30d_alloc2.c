// 0x43f80 (16 B) — v2 naked asm: MMAllocPtr wrapper (edx=0, ecx=arg2)
extern void mmAllocPtr(void);

long __declspec(naked) w30d_alloc2(long a, long b)
{
    __asm {
        xor edx, edx
        mov ecx, [esp+8]
        jmp mmAllocPtr
    }
}