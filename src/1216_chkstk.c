/* __chkstk @ rva 0xd4530 (dec 869680), size 0x30 — EXACT, naked-asm escape.
 *
 * No FPO record for this chunk; FA's body is the classic CRT _chkstk
 * probe loop (push ecx / cmp eax,0x1000 / lea ecx,[esp+8] / jb / sub /
 * test [ecx],eax / jae loop / sub ecx,eax / mov eax,esp / test /
 * mov esp,ecx / restore-return). Not C-formable (pure asm, no C prologue
 * allowed); naked asm carrying FA's own instruction sequence verbatim.
 * The C name `_chkstk` decorates to the obj symbol __chkstk = FA's chunk
 * name (identity, no map).
 *
 * fitobj: python3 tools/fitobj.py build/survey/probes/w24a_chkstk_v1.obj 869680 \
 *   build/survey/probes/w24a_chkstk_v1_fit.obj
 * (0 relocs, 0 undefineds; tail = census-proven filler cc.)
 */
void __declspec(naked) _chkstk(void)
{
    __asm {
        push ecx
        cmp eax, 0x1000
        lea ecx, [esp+8]
        jb small
        big:
        sub ecx, 0x1000
        sub eax, 0x1000
        test dword ptr [ecx], eax
        cmp eax, 0x1000
        jae big
        small:
        sub ecx, eax
        mov eax, esp
        test dword ptr [ecx], eax
        mov esp, ecx
        mov ecx, [eax]
        mov eax, [eax+4]
        push eax
        ret
    }
}
