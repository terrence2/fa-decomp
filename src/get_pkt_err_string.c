// ?get_pkt_err_string@@YAPADJ@Z @ rva 0xadfd0 (32 B) — err>0 && err<7 ->
//   return char* errFuncTab[err] (sib-85 indexed moffs [eax*4+disp32];
//   dis.py elided this mov — objdump cross-checked); else return the
//   default string ptr at 0x508094. Both disp32s carry fixups -> symbol
//   refs via maps (_pktErrTab=?, _pktErrDflt=?). asm escape: FA's
//   [eax*4+tab] sib-85 load and the b8 imm return (LEA would be 8d 05)
//   pinned via MASM.
extern char pktErrTab[];
extern char pktErrDflt[];

__declspec(naked) char *get_pkt_err_string(void)
{
    __asm {
        mov     eax, dword ptr [esp+4]
        test    eax, eax
        jle     Ld
        cmp     eax, 7
        jge     Ld
        mov     eax, dword ptr pktErrTab[eax*4]
        ret
Ld:
        mov     eax, offset pktErrDflt
        ret
    }
}