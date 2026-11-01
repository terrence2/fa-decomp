// _G_FindClose@4 @ rva 0x78df0 (48 B) — stdcall FindClose wrapper:
//   push ebx / push esi / mov esi,[esp+0xc] / test esi,esi / jne L1 /
//   xor al,al / pop esi / pop ebx / ret 4
//   mov eax,[esi] / mov ebx,[__imp__FindClose] / push eax / call ebx /
//   mov bl,al / push esi / call $FA$_t_4d4880 / add esp,4 / mov al,bl /
//   pop esi / pop ebx / ret 4  (tail 8bff census pad)
// The ebx-indirect IAT call (avoids ff 15) and the AL result parked in BL
// across the clean-up call are the G5 shapes C can't reach: naked asm
// (probe w13a_gfindclose exact outside the two reloc dwords).
extern void *impFindCloseIAT;      // __imp__FindClose IAT slot address
extern void GFindCloseClean(void *find);   // $FA$_t_4d4880

__declspec(naked) int __stdcall G_FindClose(void *find)
{
    __asm {
        push ebx
        push esi
        mov esi, [esp+0xc]
        test esi, esi
        jne l1
        xor al, al
        pop esi
        pop ebx
        ret 4
    l1:
        mov eax, [esi]
        mov ebx, [impFindCloseIAT]
        push eax
        call ebx
        mov bl, al
        push esi
        call GFindCloseClean
        add esp, 4
        mov al, bl
        pop esi
        pop ebx
        ret 4
    }
}