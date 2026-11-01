// __ltoa @ rva 0xe1f70 (47 B) — char *_ltoa(long val, char *str, int
// radix): radix->eax and val->edx loaded up front, pre-materialized neg =
// (radix==10 && val<0) as mov ecx,1 / jmp / xor ecx,ecx (true value first,
// zeroed at the shared else label), str re-loaded into esi, then the
// unnamed 4-arg cdecl helper at $FA$_t_4e1f10 with neg/radix/str/val
// pushed right-to-left from the held regs, str returned from esi. Two C
// probes (b18_ltoa_v2/v3: ternary inline in the arg, if/else) both
// reproduce FA's exact instruction ORDER but pin radix/val/neg in
// ecx/eax/edx — CL's reg plan is not steerable, so naked asm.
extern void __cdecl ltoa_helper(long val, char *str, int radix, int neg);

void __declspec(naked) __cdecl _ltoa(void)
{
    __asm {
        mov  eax, dword ptr [esp+0xc]   ; radix (arg3)
        push esi
        mov  edx, dword ptr [esp+8]     ; val (arg1)
        cmp  eax, 10
        jne  Lzero
        test edx, edx
        jge  Lzero
        mov  ecx, 1
        jmp  Lhave
Lzero:
        xor  ecx, ecx
Lhave:
        mov  esi, dword ptr [esp+0xc]   ; str (esp shifted by the esi push)
        push ecx                        ; neg
        push eax                        ; radix
        push esi                        ; str
        push edx                        ; val
        call ltoa_helper
        add  esp, 16
        mov  eax, esi
        pop  esi
        ret
    }
}