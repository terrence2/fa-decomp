// 0xaf530 — v6: naked asm (rotation of CL's volatile-reg plan was
// unsteerable; FA bytes deterministic here)
extern char w28c_clArr[];

void __declspec(naked) __stdcall w28c_WRGetLayer(long key, char *out)
{
    __asm {
        mov ecx, [esp+4]
        push ebx
        sar ecx, 8
        test ecx, ecx
        jge L0
        xor ecx, ecx
L0:
        mov eax, OFFSET w28c_clArr
L1:
        mov edx, [eax+0xa]
        cmp edx, ecx
        jg L2
        mov edx, [eax+0xe]
        cmp edx, ecx
        jge L3
        add eax, 0x160
        jmp L1
L2:
        mov edx, [eax+0xe]
        cmp edx, ecx
        jge L3
        add eax, 0x160
        jmp L1
L3:
        mov edx, [esp+0xc]
        test edx, edx
        je L4
        mov bl, [eax+0x160]
        test bl, 1
        jne Lz
        mov ebx, [eax+0x16a]
        cmp edx, ebx
        jg Lz
        pop ebx
        mov byte ptr [edx], 1
        ret 8
Lz:
        mov byte ptr [edx], 0
        pop ebx
        ret 8
L4:
        pop ebx
        ret 8
    }
}
