// 0x1e000 = 122880, unnamed gap, 16 B (5 code + 11 pad) — pure e9 jmp to
// ?ddLCS@CDirDraw@@SAXXZ (static void(void), 13 refs from CDirDraw methods).
// Bare-jmp pass-through: try plain C tail-call first.
extern void DDLCS_c(void);
/* map _DDLCS_c=?ddLCS@CDirDraw@@SAXXZ */

void __stdcall w25c_fwdddLCS_q(void)
{
    DDLCS_c();
}