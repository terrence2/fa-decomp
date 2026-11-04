/* unnamed gap chunk @ rva 0x322b0 (205488, 32 B) — fastcall char white/
 * delimiter test.  Param arrives in cl (FPO params=0 — reg param); chain
 * of cmp cl,imm / je true-label, result in al as char.  Compare order in
 * FA: ' ', \t, \r, \n.  Tail pad 8d 9b 00 00 00 00 (6 B) census filler.
 */
char __fastcall w30e_white(char c)
{
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}