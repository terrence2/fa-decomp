// _MaxSpeed@8 @ rva 0x76c20 (80 B) — dispatches on [obj] type byte.
// FA: ecx=byte[eax(arg2)]; 5 -> return movsx word[p1+0x243]; 7 -> tail call
// $FA$_t_476c70(ecx=[p1+0x15], push [p1+0x109], push [p1+0x10a]);
// else movsx word[eax+0x6b]. dis.py ELIDED the case-5 movsx (0f bf 80 43 02).
// Push order at callee: [esp+4]=[p1+0x109], [esp+8]=[p1+0x10a]. naked asm.
extern int __stdcall tMaxSpeedTailQ(int a, int b, int c);

__declspec(naked) int __stdcall MaxSpeed(int p1, int p2)
{
    __asm {
        xor ecx, ecx
        mov eax, [esp+8]
        mov cl, [eax]
        cmp ecx, 5
        je l5
        cmp ecx, 7
        je l7
        movsx eax, word ptr [eax+6bh]
        ret 8
    l5:
        mov eax, [esp+4]
        movsx eax, word ptr [eax+243h]
        ret 8
    l7:
        movsx edx, word ptr [eax+6bh]
        xor ecx, ecx
        mov cl, [eax+10ah]
        push ecx
        xor ecx, ecx
        mov cl, [eax+109h]
        mov eax, [esp+8]
        push ecx
        mov ecx, [eax+15h]
        call tMaxSpeedTailQ
        ret 8
    }
}
