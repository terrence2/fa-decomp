int __declspec(naked) QuickDist(int *a, int *b)
{
    __asm {
        push ebp
        mov ebp, esp
        push ebx
        push esi
        mov ebx, [ebp + 8]
        mov esi, [ebp + 0xc]
        mov eax, [ebx]
        sub eax, [esi]
        jns quickdist_abs0
        neg eax
quickdist_abs0:
        mov ecx, [ebx + 4]
        sub ecx, [esi + 4]
        jns quickdist_abs1
        neg ecx
quickdist_abs1:
        mov edx, [ebx + 8]
        sub edx, [esi + 8]
        jns quickdist_abs2
        neg edx
quickdist_abs2:
        add eax, ecx
        add eax, edx
        pop esi
        pop ebx
        pop ebp
        ret 8
    }
}