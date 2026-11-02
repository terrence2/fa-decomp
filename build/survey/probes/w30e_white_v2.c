/* w30e_white v2 — int return spelling (same fastcall char param chain).
 */
int __fastcall w30e_white2(char c)
{
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}