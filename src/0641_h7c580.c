// $FA$_t_47c580 @ rva 0x7c580 (64 B) — fastcall (i in ecx): lazily build
// buttonBoxes[i] via RMAccessHandle, then register the box index in
// fmtText.  eax=bb[i]; if 0: push 0x8000 / eax=fb[i+1] (sib [esi*4+
// fmtReduceButtonH+0x4]) / push eax / call RMAccessHandle (args (fb, 0x8000))
// / store bb[i] = result.  Then textNum a1 moffs; ecx=x*17 (shl 4 + add);
// fmtText[15 + textNum*17] = i (sib [ecx*4+fmtText+0x3c]).  Tail
// 8d 64 24 00.
extern int __stdcall RMAccessHandle(int a, int b);
extern long w43b_bb[];      /* map _w43b_bb=_buttonBoxes+0xc8 */
extern long w43b_fb[];      /* map _w43b_fb=_fmtReduceButtonH+0x4 */
extern long w43b_ft[];      /* map _w43b_ft=_fmtText+0x3c */
extern long textNum;

void __fastcall w43b_prep(long i)
{
    if (w43b_bb[i] == 0)
        w43b_bb[i] = RMAccessHandle(w43b_fb[i + 1], 0x8000);
    w43b_ft[textNum * 17 + 15] = i;
}