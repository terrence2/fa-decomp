// __fclose_lk @ rva 0xd3f50 (95 B) — int __cdecl _fclose_lk(FILE *f): the
// locked half of fclose (same family as _fclose/_fflush_lk, waves 16/21).
// edi = -1 result holder; flags test (0x83 = _IOREAD|_IOWRIT|_IORW) must be
// the direct mem byte test f6 46 0c (CL emits mov al/test al — w16a
// _fclose lesson); on open: __flush_lk ($FA$_t_4d5f30, r via edi), the
// unknown stream helper parked at $FA$_t_4d82a0, _close([f+0x10]) with
// jge-over mov edi,-1 / jmp exit; free the tmpfname ([f+0x1c]) then clear
// BOTH dwords ([f+0x1c]=0 with the add esp,4 deferred past the store,
// [f+0xc]=0), return edi. Naked asm escape (mem byte test + deferred
// add esp,4 between stores).
extern int __cdecl _flush_lk(void *f);      /* $FA$_t_4d5f30 */
extern int __cdecl fcloseUnk2(void *f);     /* $FA$_t_4d82a0 */
extern int __cdecl _close(int fd);
extern void __cdecl free(void *mem);

int __declspec(naked) __cdecl _fclose_lkQ(void)
{
    __asm {
        push esi
        push edi
        mov  edi, -1
        mov  esi, dword ptr [esp+0xc]
        test byte ptr [esi+0xc], 0x83
        je   common
        push esi
        call _flush_lk
        add  esp, 4
        mov  edi, eax
        push esi
        call fcloseUnk2
        add  esp, 4
        mov  eax, dword ptr [esi+0x10]
        push eax
        call _close
        add  esp, 4
        test eax, eax
        jge  tempName
        mov  edi, -1
        jmp  common
    tempName:
        mov  eax, dword ptr [esi+0x1c]
        test eax, eax
        je   common
        push eax
        call free
        mov  dword ptr [esi+0x1c], 0
        add  esp, 4
    common:
        mov  dword ptr [esi+0xc], 0
        mov  eax, edi
        pop  edi
        pop  esi
        ret
    }
}