/* @G_Texture@12 @ rva 0xb4b60 (dec 740192), size 0x30 — EXACT, naked-asm escape.
 *
 * Wall (named): FA's chunk has parent-sourced ebx + full-ebp frame around
 * an edi-saved MMAccessW call sandwich — CL cannot be coaxed into the
 * pusha/popa (must be _emit 0x60/0x61) or the odd push layout, so the
 * probe is a naked-asm escape carrying FA's own instruction sequence
 * verbatim (like carefulDiv). _emit 0x60/0x61 = pusha/popa (66 60/61 form
 * is wrong here — trap documented in wave 18).
 *
 * fitobj: python3 tools/fitobj.py build/survey/probes/w24a_G_Texture_v1.obj 740192 \
 *   --map '_MMAccessW=@MMAccessW@4' build/survey/probes/w24a_G_Texture_v1_fit.obj
 * (2 relocs REL32: @MMAccessW@4 mapped; _G__Texture passes through
 * identity to FA's own data chunk name. tail = census-proven filler 8d4900.)
 */
extern void __cdecl MMAccessW(void);
extern void __cdecl G__Texture(void);
void __declspec(naked) __stdcall G_Texture(int eaxp, int edxp, int stackp)
{
    __asm {
        push ebp
        mov ebp, esp
        sub esp, 8
        push ebx
        mov [ebp-4], edx
        push esi
        push edi
        call MMAccessW
        mov [ebp-8], eax
        _emit 0x60
        mov esi, [ebp-8]
        mov eax, [ebp-4]
        mov ebx, [ebp+8]
        call G__Texture
        _emit 0x61
        pop edi
        pop esi
        pop ebx
        mov esp, ebp
        pop ebp
        ret 4
    }
}
