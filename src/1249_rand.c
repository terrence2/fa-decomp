// _rand @ rva 0xd5c30 — holdrand = holdrand*239613 + 2531011 over __getptd()
//   thread state (+0x14), return >>16 & 0x7fff. CL 4.2's decomposition of
//   *239613 differs from FA's 5*/25/+1/*9/«8/-1/*4+1 chain for every
//   source form -- inline __asm (probe d92 exact).
extern int __getptd(void);

int _rand_q(void)
{
    __asm {
        call __getptd
        mov  ecx, dword ptr [eax+0x14]
        mov  edx, ecx
        lea  ecx, [ecx+ecx*4]
        lea  ecx, [ecx+ecx*4]
        add  ecx, edx
        lea  ecx, [edx+ecx*8]
        shl  ecx, 8
        sub  ecx, edx
        lea  ecx, [edx+ecx*4+0x269EC3]
        mov  dword ptr [eax+0x14], ecx
        mov  eax, ecx
        and  eax, 0x7fff0000
        shr  eax, 16
    }
}
