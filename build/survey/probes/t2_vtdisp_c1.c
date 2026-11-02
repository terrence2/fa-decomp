/* C-wall probe: what CL 4.2 can emit for opcode dispatch from real C.
   (a) fn-ptr array indexed call, (b) switch. Neither can produce FA's
   tail `ff 24 5d <disp32>` (jmp dword ptr [ebx*2 + vector_table],
   256-entry table read at STRIDE 2 — overlapping dword entries) nor any
   indirect JMP at all (CL always emits call, or switch-table jmp with
   scale-4 sib into .rdata). */
extern void t2_h0(void), t2_h1(void), t2_h2(void);
extern void *vector_table[];

void t2_dispatch_fnptr(unsigned char op)
{
    void (*const jt[3])(void) = { t2_h0, t2_h1, t2_h2 };
    jt[op]();
}

void t2_dispatch_switch(unsigned char op)
{
    switch (op) {
    case 0: t2_h0(); break;
    case 1: t2_h1(); break;
    case 2: t2_h2(); break;
    default: break;
    }
}
