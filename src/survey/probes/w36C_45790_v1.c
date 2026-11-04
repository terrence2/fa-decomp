/* w36C 0x45790 (unnamed, 48 B) v1: whole-body NAKED-ASM.  FA carries
 * C-dead work: dx/di/si loads from [a+0xe/0x10/0x12] whose uses a pure C
 * compiler DCEs, and a dead word cmp [ecx+0xe],dx inside the loop (the
 * jne branches on the LATER dword cmp eax,ecx).  Same wall as the
 * towupper family: FA-only dead loads keep esi/edi/dx alive.  No maps,
 * no externs (reads [esp+4]/[esp+10] args, chain-follows +0x28). */
int __declspec(naked) f_45790X(void)
{
    __asm {
        mov eax, dword ptr [esp+4]
        push esi
        mov dx, word ptr [eax+0eh]
        push edi
        mov di, word ptr [eax+10h]
        mov ecx, dword ptr [eax+28h]
        mov si, word ptr [eax+12h]
        mov eax, dword ptr [esp+10h]
        cmp eax, ecx
        je Lret
    Lloop:
        cmp word ptr [ecx+0eh], dx
        mov ecx, dword ptr [ecx+28h]
        cmp eax, ecx
        jne Lloop
    Lret:
        xor eax, eax
        pop edi
        pop esi
        ret
    }
}