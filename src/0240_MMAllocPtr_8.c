// @MMAllocPtr@8 @ rva 0x35aa0 (16 B)
// FA: call @MMAllocHandle@8 (forwards ecx=a, edx=b) / test / jne+3 /
//     xor eax,eax / ret / mov eax,[eax+8] / ret
extern int __fastcall MMAllocHandle(int, int);

int __fastcall MMAllocPtr(int a, int b)
{
    int h = MMAllocHandle(a, b);
    // explicit "test / jne-then / xor-last / ret" shape: the ternary form
    // compiles to test / je-then / mov-first / ret / xor (inverted polarity)
    if (!h)
        return 0;
    return *(int *)((char *)h + 8);
}
