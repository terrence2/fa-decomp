// @G_Flush@4 @ rva 0x96550 (16 B) — jmp @GG_Flush@4
extern void __fastcall GG_Flush(int);

void __fastcall G_Flush(int a)
{
    GG_Flush(a);
}
