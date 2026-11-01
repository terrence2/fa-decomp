// __heap_init @ rva 0xdc180 (57 B) — FA asm (note chunk name __heap_init
// <- C fn _heap_init):
//   heap = HeapCreate(0,0x1000,0); if (!heap) return 0 /
//   if (!heapHelper()) { HeapDestroy(heap); return 0 } / return 1
//   (i.e. push 0 / push 0x1000 / push 0 / ff 15 HeapCreate / store
//   __crtheap / test / call heapHelper / test / ff 15 HeapDestroy / returns).
// Naked-asm escape: the IAT calls must be ff 15 indirect; a plain C call
// with __declspec(dllimport) reaches ff 15 but then CL pushes ebx in the
// prolog (prolog mismatch) — so use the IAT-pointer-decl form
// (`extern void *impHeapCreate[]` + `call dword ptr [impHeapCreate]`,
// CreateDialogParamA thunk precedent; probe b19b_hinit_v3 exact; v1
// plain-C e8-call FAIL, v2 dllimport ebx-push FAIL). Maps: FROMs are the
// impX externs; heapHelper is the unnamed $FA$_t_4ddff0 helper;
// __crtheap resolves identity.
extern void *impHeapCreate[];
extern void *impHeapDestroy[];
extern void *_crtheap;
extern int __cdecl heapHelper(void);

int __declspec(naked) _heap_init(void)
{
    __asm {
        push 0
        push 0x1000
        push 0
        call dword ptr [impHeapCreate]
        mov dword ptr [_crtheap], eax
        test eax, eax
        jne Lcont
        xor eax, eax
        ret
    Lcont:
        call heapHelper
        test eax, eax
        jne Lok
        mov eax, dword ptr [_crtheap]
        push eax
        call dword ptr [impHeapDestroy]
        xor eax, eax
        ret
    Lok:
        mov eax, 1
        ret
    }
}