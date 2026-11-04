/* @G_PerspectiveFlip@12 @ rva 0xb4c30 (144 B) -- w45B v1. Sibling of
 * @G_TextureFlip@12 (w42F_b4bc0): whole-body naked asm transcription. Same
 * pusha/popa band around the asm-internal-convention callee _G__Perspective
 * (esi=[ebp-8] tbl, eax=[ebp-4] n, ebx=[ebp+8] arr); loop counter is ECX and
 * the stride walker is EDI (vs TextureFlip's EDX/EDI); second store rides
 * [eax+edi-4] after the advance. pusha/popa via _emit (66 60/61 trap). */
extern void *cb;
extern char showUpdate;
extern void G__Perspective(char *a, long n, long p);
extern void __fastcall G_Flush(long x);

void __declspec(naked) __fastcall G_PerspectiveFlip(void *a, unsigned long n, void *p)
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
        mov  edx, [ecx+6]
        shl  esi, 16
        dec  edx
        shl  edx, 16
        xor  edi, edi
        xor  ecx, ecx
        mov  ebx, [ebp-4]
        cmp  ebx, ecx
        jle  w45bgpf_tail
w45bgpf_loop:
        mov  eax, [ebp+8]
        mov  ebx, esi
        sub  ebx, [eax+edi+4]
        lea  eax, [eax+edi+4]
        add  edi, 0x14
        inc  ecx
        mov  [eax], ebx
        mov  eax, [ebp+8]
        mov  ebx, edx
        sub  ebx, [eax+edi-4]
        mov  [eax+edi-4], ebx
        lea  eax, [eax+edi-4]
        cmp  ecx, [ebp-4]
        jl   w45bgpf_loop
w45bgpf_tail:
        _emit 0x60
        mov  esi, [ebp-8]
        mov  eax, [ebp-4]
        mov  ebx, [ebp+8]
        call G__Perspective
        _emit 0x61
        mov  al, showUpdate
        test al, al
        je   w45bgpf_done
        mov  ecx, 1
        call G_Flush
w45bgpf_done:
        pop  edi
        pop  esi
        pop  ebx
        mov  esp, ebp
        pop  ebp
        ret  4
    }
}