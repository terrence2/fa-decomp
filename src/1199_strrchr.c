/* _strrchr @ rva 0xd39b0 (dec 866736), size 0x30 — EXACT, naked-asm escape.
 *
 * Wall (named): the body is the CRT strrchr rep-scasb shape (FA's
 * compiler emitted the intrinsic as straight-line asm incl. repnz scasb
 * + std/cld) — spellable only as naked asm; the C intrinsic path does not
 * reach these exact bytes. CL 4.2's inline assembler silently drops
 * `leave` (wave-21 idiom), so the epilogue's c9 is spelled _emit 0xc9.
 * CL 4.2 reserves the intrinsic name strrchr, so the probe spells the
 * definition strrchr_probe (C2059 otherwise); the naked obj defines no
 * callable name itself and fitobj stamps the FA chunk name _strrchr (0
 * relocs, 0 undefineds), so the spelling is unused at link time.
 *
 * fitobj: python3 tools/fitobj.py build/survey/probes/w24a_strrchr_v3.obj 866736 \
 *   build/survey/probes/w24a_strrchr_v3_fit.obj
 * (0 relocs, 0 undefineds; tail = census-proven filler cc x9.)
 */
__declspec(naked) char *__cdecl strrchr_probe(const char *s, int ch)
{
    __asm {
        push ebp
        mov ebp, esp
        push edi
        mov edi, [ebp+8]
        xor eax, eax
        or ecx, -1
        repnz scasb
        inc ecx
        neg ecx
        dec edi
        mov al, [ebp+0xc]
        std
        repnz scasb
        inc edi
        cmp byte ptr [edi], al
        je found
        xor eax, eax
        jmp skipover
        found:
        mov eax, edi
        skipover:
        cld
        pop edi
        _emit 0xc9
        ret
    }
}
