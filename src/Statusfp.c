// __statusfp @ rva 0xdf610 (22 B) — sub esp,4 / fstsw [esp+2] / mov eax,
//   [esp+2] / push eax / call $FA$_t_4df830 / add esp,8 / ret. Inline asm;
//   the callee is an unnamed gap chunk (probe d23 exact modulo rel32).
extern int sfpHelper(int w);

void Statusfp_q(void)
{
    __asm {
        sub     esp, 4
        fstsw   [esp+2]
        mov     eax, [esp+2]
        push    eax
        call    sfpHelper
        add     esp, 8
    }
}
