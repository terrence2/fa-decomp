// __strdup @ rva 0xe3cd0 (933072) — FA 48 B = 0x26 code + 10 B cc pad:
//   55 8b ec            push ebp / mov ebp,esp
//   57 8b 7d 08         push edi / mov edi,[ebp+8]      (src -> edi)
//   57 e8 ....          push edi / call _strlen
//   5a                  pop edx                          (1 B cdecl cleanup)
//   40 50               inc eax / push eax               (size + 1)
//   e8 ....             call _malloc
//   5a                  pop edx
//   0b c0               or eax,eax
//   74 09               je +9
//   57 50               push edi / push eax              (strcpy(p, src))
//   e8 ....             call _strcpy
//   5a 5a               pop edx / pop edx
//   5f c9 c3            pop edi / leave / ret
// i.e. p = malloc(strlen(s)+1); if (p) strcpy(p, s); return p; — with FA's
// compiler keeping p in EAX across the strcpy call (strcpy returns dst == p,
// so the fall-through epilog rets p in eax with no 8b c7 reload).
//
// EXACT fit (byte-verify PASS, no --tail-accept; tail = census-proven cc*10).
//
// Raw CL /c /O2 /Gy /G5 output for this body differs in register/epilog
// choices (probe v1 = w24b_strdup_f_o2nopragma.obj, 49 B):
//   prolog 56 57 8b 75 08 (esi AND edi saved, src -> esi), all three
//   arg-cleanup adds as 83 c4 xx, p copied to edi (8b f8/85 ff/8b c7),
//   epilog 5f 5e 5d c3 (extra pop esi, mov esp,ebp instead of leave).
// Eight byte surgeries bring it to FA's shape. The pushes/pops stay
// register-faithful: src lives in edi for us exactly as for FA.
//
// fitobj (winning command):
//   python3 tools/fitobj.py build/survey/probes/w24b_strdup_final.obj 933072 \
//     --map '__strlen_a=_strlen' --map '__malloc_a=_malloc' \
//     --map '__strcpy_a=_strcpy' \
//     --patch '3,5,578b7d08'   \
//     --patch '7,1,57'         \
//     --patch '13,3,5a'        \
//     --patch '21,3,5a'        \
//     --patch '22,6,0bc07409'  \
//     --patch '26,2,5750'      \
//     --patch '33,3,5a5a'      \
//     --patch '35,6,5fc9c3'    \
//     build/survey/probes/w24b_strdup_final_fit.obj
//
#pragma optimize("y", off)

// Patch provenance (each key = the directive's first two fields, state word
// toolchain-diff; deltas are CL-vs-FA codegen deltas on an FA prebuilt-CRT
// chunk that ships without .debug$F):
//   3,5   578b7d08  replace 'push esi; push edi; mov esi,[ebp+8]' with
//                   'push edi; mov edi,[ebp+8]' (FA saves edi only)
//   7,1   57        strlen-arg push esi -> push edi (src now in edi)
//   13,3  5a        83 c4 04 -> pop edx (FA's 1 B cleanup of the strlen arg)
//   21,3  5a        83 c4 04 -> pop edx (malloc arg cleanup)
//   22,6  0bc07409  8b f8 85 ff 74 0a (mov edi,eax/test edi/je+10) ->
//                   0b c0 74 09 (or eax,eax/je+9) — p stays in eax
//   26,2  5750       strcpy arg pushes 'push esi/push edi' -> 'push edi/push
//                   eax' (p=eax, src=edi — byte shape equal to FA's)
//   33,3  5a5a      83 c4 08 -> 5a 5a (strcpy's 8 B cleanup -> pop/pop)
//   35,6  5fc9c3    8b c7 5f 5e 5d c3 -> 5f c9 c3 (drop the 8b c7
//                   eax-reload — FA's epilog trusts the or-eax copy; pop esi
//                   no longer needed; mov esp,ebp+pop ebp -> leave)
// The 74 09 je lands on the single epilog at +35, exactly FA's fallthrough.
extern unsigned int _strlen_a(const char *s);      /* __strlen_a -> _strlen */
extern void *_malloc_a(unsigned int n);            /* __malloc_a -> _malloc */
extern void _strcpy_a(char *d, const char *s);     /* __strcpy_a -> _strcpy */

char *_strdup_q(const char *src)
{
    char *p;
    p = (char *)_malloc_a(_strlen_a(src) + 1);
    if (p != 0)
        _strcpy_a(p, src);
    return p;
}
