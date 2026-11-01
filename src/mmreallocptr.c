// @MMReallocPtr@8 @ rva 0x35c00 (16 B) — same shape via @MMPtrToHandle@4
//   (callee reads ecx only; our edx stays untouched)
extern int __fastcall MMPtrToHandle(int);

int __fastcall MMReallocPtr(int a, int b)
{
    int h = MMPtrToHandle(a);
    // explicit "test / jne-then / xor-last / ret" shape (as MMAllocPtr: the
    // ternary form inverts the jump polarity and reorders the xor)
    if (!h)
        return 0;
    return *(int *)((char *)h + 8);
}
