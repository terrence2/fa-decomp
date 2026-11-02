// w26a_77a60 @ rva 0x77a60 (490592, unnamed 16 B orphan) — FA bytes (raw):
//   e9 0b 00 00 00       jmp $FA$_t_477a70 (rel32 -> unnamed chunk @0x77a70)
//   8d 64 24 00 / 8d a4 24 00 00 00 00   (11 B census pad)
// 0-arg-void tail-jmp into a gap-chunk anchor (wave-21 --alias/map recipe).
extern void gap477a70(void);   /* $FA$_t_477a70 */
void w26a_77a60(void)
{
    gap477a70();
}