// 0xaf530 ___WRGetLayer@@YA?AUWRAPPER@@PAU@@@Z @ 0x4af530 — v7: naked asm,
// loop restructured so first jg jumps straight to the add (v6 duplicated
// the second check); failure paths reuse one pop (je -> post-store-0 pop)
extern char w28c_clArr[];

void __declspec(naked) w28c_WRGetLayer(int *p, int *r)
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
L2:
        add eax, 0x160
        jmp L1
L3:
        mov edx, [esp+0xc]
        test edx, edx
        je Zpop
        mov bl, [eax+0x160]
        test bl, 1
        jne Z0
        mov ebx, [eax+0x16a]
        cmp ebx, ecx
        jg Z0
        pop ebx
        mov byte ptr [edx], 1
        ret 8
Z0:
        mov byte ptr [edx], 0
Zpop:
        pop ebx
        ret 8
    }
}