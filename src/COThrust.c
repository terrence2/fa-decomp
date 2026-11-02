// @COThrust@4 @ rva 0x77060 (64 B) — CO thrust value with multiplayer halfing.
// FA: test cl,cl(arg); je -> load A; B=[curThingType+0x153]; if B!=0 skip A
// load (a1 both); numComputers<=1 -> ret (8b 0d/83 f9 01/7e); gameMultiPrefs
// THEN re-loaded into ecx (8b 0d) and byte-tested (f6 c1 10); [curThing+0x10]
// byte +0x80 test (8a 0d/f6 c1 80); sar eax,1; ret. CL 4.2 hoists the gmp
// dword load into edx ahead of the nc cmp and byte-tests dl (f6 c2) —
// unsteerable reg plan, naked asm (CTEval_tgt family).
extern unsigned long ctA;            /* _curThingType+0x14f */
extern unsigned long ctB;            /* _curThingType+0x153 */
extern long numComputers;
extern unsigned long gameMultiPrefs;
extern unsigned char ctFlags10;      /* _curThing+0x10 */

__declspec(naked) long __fastcall COThrust_q(unsigned char f)
{
    __asm {
        test cl, cl
        je l_a
        mov eax, ctB
        test eax, eax
        jne cont
    l_a:
        mov eax, ctA
    cont:
        mov ecx, numComputers
        cmp ecx, 1
        jle ret_l
        mov ecx, gameMultiPrefs
        test cl, 10h
        je ret_l
        mov cl, ctFlags10
        test cl, 80h
        je ret_l
        sar eax, 1
    ret_l:
        ret
    }
}
