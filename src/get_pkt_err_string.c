// ?get_pkt_err_string@@YAPADJ@Z @ rva 0xadfd0 (32 B) — err>0 && err<7 ->
//   return pktErrTab[err] (8b 04 85 sib-85 indexed, dis.py elided this
//   mov; objdump cross-checked), else return the default string pointer
//   (b8 imm32 return of the mapped default-string symbol). Both disp32s
//   carry fixups -> symbol refs via maps (_pktErrTab=?,tcp_proto+0x290;
//   _pktErrDflt=?,state_funcs_list+0x9c). Plain C: signed err local,
//   && short-circuit — CL 10.20 emits the sib-85 load and the b8 imm32
//   return naturally from this spell.
extern char *pktErrTab[];
extern char pktErrDflt[];

char *get_pkt_err_string(long err)
{
    if (err > 0 && err < 7)
        return pktErrTab[err];
    return pktErrDflt;
}