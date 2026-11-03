// __msize @ rva 0xe4700 (102 B, fpo/esp, 2 locals, ebx+esi) -- CRT heap
// size: lock(9); 3-arg query call to the still-stub $FA$_t_4de2a0 with
// (p, &local0, &local1) where both locals are lea'd BEFORE the stack
// cleanup of the lock call; returned block-type byte *0x10, else the
// HeapSize(__crtheap, 0, p) fallback.  CL's C route interleaves the
// arg-setup with the call-cleanup the FA way only by hand -> naked-asm
// escape.  HeapSize is an IAT call (ff 15), __crtheap an a1 moffs.
extern void lock(int);
extern void unlock(int);
extern int hpq1(void*, int*, int*);      /* $FA$_t_4de2a0 */
extern char crtheap[];
extern void* impHeapSize[];

int __declspec(naked) _msize(void* p)
{
    __asm {
        sub esp, 8
        push ebx
        push esi
        push 9
        call lock
        lea eax, [esp+10h]
        lea ecx, [esp+0Ch]
        mov esi, [esp+18h]
        add esp, 4
        push eax
        push ecx
        push esi
        call hpq1
        add esp, 0Ch
        test eax, eax
        je Lheap
        xor ebx, ebx
        push 9
        mov bl, byte ptr [eax]
        call unlock
        shl ebx, 4
        add esp, 4
        mov eax, ebx
        pop esi
        pop ebx
        add esp, 8
        ret
    Lheap:
        push 9
        call unlock
        add esp, 4
        mov eax, dword ptr [crtheap]
        push esi
        push 0
        push eax
        call dword ptr [impHeapSize]
        mov ebx, eax
        pop esi
        mov eax, ebx
        pop ebx
        add esp, 8
        ret
    }
}