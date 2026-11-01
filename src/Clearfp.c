// __clearfp @ rva 0xdf630 (23 B) — as __statusfp but fnstsw (no wait) and
//   fnclex before the push (probe d24 exact modulo rel32).
extern int cfpHelper(int w);

void Clearfp_q(void)
{
    __asm {
        sub     esp, 4
        fnstsw  [esp+2]
        fnclex
        mov     eax, [esp+2]
        push    eax
        call    cfpHelper
        add     esp, 8
    }
}
