/* w37E candidate 0x8c2b0 (unnamed, __fastcall 3-arg: this=ecx, tbl=edx, short n
   on stack, callee-pops ret 4), 53 B code + census pads.
   FA: push esi; mov esi,ecx; mov cx,[esp+8]; cmp cx,1 jle call; test edx,edx
   je rnd; movsx ecx,cx; xor eax,eax; mov al,[edx+1]; cdq; idiv ecx; jmp join;
   rnd: call @Rand@4 (dirty cx!, thunk masks 0xffff -> @Rand32@4); movsx edx,ax;
   join: lea esi,[esi+edx*8]; call: mov ecx,esi; call $FA$_t_48b580; pop esi; ret 4 */
extern short __fastcall w37e_rand(short n);
extern void __fastcall w37e_t48b580(char *p);

void __fastcall w37e_8c2b0(char *s, char *t, short n)
{
    long d;
    if (n > 1) {
        d = t ? (long)(unsigned char)t[1] % n : w37e_rand(n);
        s += d * 8;
    }
    w37e_t48b580(s);
}