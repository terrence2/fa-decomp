/* @G_TextureFlip@12 @ rva 0xb4bc0 (112 B) -- w42F v1. Whole-body naked asm
 * transcription (same recipe as w41F CopyDB15 / w37H attempts that could not
 * close through C: the pusha/popa band and the hand-rolled esi=ecx/eax=edx/
 * ebx=stack-arg call of _G__Texture are asm-only; w37H v10-13 got the prolog
 * band + loop in C but only ever converged with a non-matching asm block).
 * FA body: FP frame (push ebp/sub esp,8), a1 moffs load of _cb + alignment
 * nop, [ebp-4]=edx / [ebp-8]=ecx param spills, top=(cb->w6-1)<<16 /
 * bot=(a->w6-1)<<16 preloads, edx=byte-stride walker (+0x14) with edi counter,
 * then the _emit 60/61 pusha band around the 3-reg call. pusha/popa are
 * emitted via _emit to dodge the 66-prefixed 16-bit pusha trap (wave 18). */
extern void *cb;
extern void G__Texture(char *a, long n, long p);

void __declspec(naked) __fastcall G_TextureFlip(void *a, unsigned long n, void *p)
{
    __asm {
        push ebp
        mov  ebp, esp
        sub  esp, 8
        mov  eax, cb
        nop
        mov  [ebp-4], edx
        push ebx
        push esi
        mov  [ebp-8], ecx
        push edi
        mov  esi, [eax+6]
        dec  esi
        mov  ecx, [ecx+6]
        shl  esi, 16
        dec  ecx
        shl  ecx, 16
        xor  edx, edx
        xor  edi, edi
        mov  ebx, [ebp-4]
        cmp  ebx, edx
        jle  w42fGtf_tail
w42fGtf_loop:
        mov  eax, [ebp+8]
        mov  ebx, esi
        sub  ebx, [eax+edx+4]
        lea  eax, [eax+edx+4]
        add  edx, 0x14
        inc  edi
        mov  [eax], ebx
        mov  eax, [ebp+8]
        mov  ebx, ecx
        sub  ebx, [eax+edx-4]
        mov  [eax+edx-4], ebx
        lea  eax, [eax+edx-4]
        cmp  edi, [ebp-4]
        jl   w42fGtf_loop
w42fGtf_tail:
        _emit 0x60
        mov  esi, [ebp-8]
        mov  eax, [ebp-4]
        mov  ebx, [ebp+8]
        call G__Texture
        _emit 0x61
        pop  edi
        pop  esi
        pop  ebx
        mov  esp, ebp
        pop  ebp
        ret  4
    }
}