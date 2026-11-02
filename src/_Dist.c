// 0xc2a7c _Dist@8 @ 0x4c2a7c — v4: naked asm over full FA decode
// (abs via jns/neg per axis, unsigned max via jae+xchg, shr 2 sums,
// stdcall ret 8; trailing 8b c0 pad comes from the census)
void __declspec(naked) __stdcall w28c_dist(long a, long b)
{
    __asm {
        push ebp
        mov ebp, esp
        push ebx
        push esi
        mov ebx, [ebp+8]
        mov esi, [ebp+0xc]
        mov eax, [ebx]
        sub eax, [esi]
        jns L1
        neg eax
L1:
        mov ecx, [ebx+4]
        sub ecx, [esi+4]
        jns L2
        neg ecx
L2:
        mov edx, [ebx+8]
        sub edx, [esi+8]
        jns L3
        neg edx
L3:
        cmp ecx, edx
        jae L4
        xchg edx, ecx
L4:
        cmp eax, ecx
        jae L5
        xchg ecx, eax
L5:
        shr ecx, 2
        add eax, ecx
        shr edx, 2
        add eax, edx
        pop esi
        pop ebx
        pop ebp
        ret 8
    }
}
