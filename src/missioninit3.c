// _MISSIONInit3@0 @ rva 0x7f070 (16 B) — jmp _SAYInit2@0 (identity, no map)
extern void __stdcall SAYInit2(void);

void __stdcall MISSIONInit3(void)
{
    SAYInit2();
}
