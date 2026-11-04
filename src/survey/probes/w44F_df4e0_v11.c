/* rva 0xdf4e0 (171 B) _calloc - naked asm (wave-19 wall: cmp [mem],reg both
   sites unreachable from C; src/HeapAllocX.c precedent). FA transcription. */
extern unsigned long heaplimitA;             /* _heaplimitA -> __adbgmsg+0x1074 */
extern unsigned long newmodeA;               /* _newmodeA   -> __adbgmsg+0x1080 */
extern void *crtheapG;                       /* _crtheapG   -> __crtheap */
extern void *heapAllocSubP(unsigned long);   /* _heapAllocSubP -> $FA$_t_4de350 */
extern void __cdecl lockX(unsigned long);    /* _lockX -> __lock */
extern void __cdecl unlockX(unsigned long);  /* _unlockX -> __unlock */
extern unsigned long __cdecl callnewhX(unsigned long);
                                             /* _callnewhX -> __callnewh */
extern void *(__stdcall *heapAllocP)(void *, unsigned long, unsigned long);
                                             /* _heapAllocP -> __imp__HeapAlloc */

__declspec(naked) void *__cdecl calloc(unsigned long num, unsigned long size)
{
    __asm {
        push ebx
        push esi
        mov  esi, [esp+0x10]
        push edi
        imul esi, [esp+0x10]
        push ebp
        cmp  esi, 0xffffffe0
        ja   LroundDone
        test esi, esi
        je   Lround10
        add  esi, 0xf
        and  esi, 0xfffffff0
        jmp  LroundDone
Lround10:
        mov  esi, 0x10
LroundDone:
        mov  ebx, dword ptr [heapAllocP]
        xor  ebp, ebp
Lloop:
        cmp  esi, 0xffffffe0
        ja   Ldone
        cmp  esi, heaplimitA
        ja   Lzcheck
        push 0x9
        call lockX
        add  esp, 4
        mov  eax, esi
        shr  eax, 4
        push eax
        call heapAllocSubP
        add  esp, 4
        mov  ebp, eax
        push 0x9
        call unlockX
        add  esp, 4
        test ebp, ebp
        _emit 0x74
        _emit 0x16
        mov  edi, ebp
        xor  eax, eax
        mov  ecx, esi
        shr  ecx, 2
        rep stosd
        mov  ecx, esi
        and  ecx, 0x3
        rep stosb

Lzcheck:
        test ebp, ebp
        jne  Ldone2
        push esi
        mov  eax, crtheapG
        push 0x8
        push eax
        call ebx
        mov  ebp, eax
Ldone:
        test ebp, ebp
        jne  Ldone2
        cmp  newmodeA, 0
        je   Ldone2
        push esi
        call callnewhX
        add  esp, 4
        test eax, eax
        _emit 0x75
        _emit 0x8c
        xor  eax, eax
        pop  ebp
        pop  edi
        pop  esi
        pop  ebx
        ret
Ldone2:
        mov  eax, ebp
        pop  ebp
        pop  edi
        pop  esi
        pop  ebx
        ret
    }
}