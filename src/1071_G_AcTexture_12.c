/* @G_AcTexture@12 @ rva 0xb4b90 (dec 740240), size 0x30 — EXACT, naked-asm
 * escape. Identical recipe to G_Texture_final.c (same wall: parent-sourced
 * ebx/esi/edi + ebp frame + pusha/popa sandwich around MMAccessW; CL
 * cannot C-form it). Only the inner call target and arg differ.
 *
 * fitobj: python3 tools/fitobj.py build/survey/probes/w24a_G_AcTexture_v1.obj 740240 \
 *   --map '_MMAccessW=@MMAccessW@4' build/survey/probes/w24a_G_AcTexture_v1_fit.obj
 * (2 relocs REL32: @MMAccessW@4 mapped; _G__AC_Texture identity pass-through.
 * tail = census-proven filler 8d4900.)
 */
extern void __cdecl MMAccessW(void);
extern void __cdecl G__AC_Texture(void);
void __declspec(naked) __stdcall G_AcTexture(int eaxp, int edxp, int stackp)
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
        call G__AC_Texture
        _emit 0x61
        pop edi
        pop esi
        pop ebx
        mov esp, ebp
        pop ebp
        ret 4
    }
}
