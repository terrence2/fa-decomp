/* _MultDiv32@12 @ rva 0x496c0 (dec 300736), size 0x30 — EXACT, naked-asm escape.
 *
 * Wall (named, 3 probes): CL 4.2 /O2 never emits FA's one-op imul
 * (F7 6D 0C) / one-op idiv (F7 7D 10) pair — every spelling tried
 * (volatile temps, plain `return a*b/c;`, split statements) produced the
 * two-op imul (0F AF) + cdq + FPO frame, a codegen gap in this CL build.
 * FA's full-ebp frame + parent-sourced push ebx/esi/edi + [ebp-4] result
 * spill + ILINK e9+0 self-jmp (content 0) are also not C-formable.
 * The body is FA's own instruction sequence verbatim; the prologue is
 * unreachable by normal C statement placement, hence naked.
 *
 * IDIOM: CL 4.2's inline assembler silently drops `leave` — spell the
 * epilogue's leave as `_emit 0xc9` (3B mov esp,ebp/pop ebp won't fit).
 *
 * fitobj: python3 tools/fitobj.py build/survey/probes/w24a_MultDiv32_v5.obj 300736 \
 *   build/survey/probes/w24a_MultDiv32_v5_fit.obj
 * (0 relocs; tail = census-proven filler cc x12.)
 */
int __declspec(naked) __stdcall MultDiv32(int a, int b, int c)
{
    __asm {
        push ebp
        mov ebp, esp
        sub esp, 4
        push ebx
        push esi
        push edi
        mov eax, [ebp+8]
        imul dword ptr [ebp+0xc]
        idiv dword ptr [ebp+0x10]
        mov [ebp-4], eax
        mov eax, [ebp-4]
        _emit 0xe9
        _emit 0
        _emit 0
        _emit 0
        _emit 0
        pop edi
        pop esi
        pop ebx
        _emit 0xc9
        ret 0xc
    }
}
