/* unnamed @ rva 0x24b63 (79 B) — thiscall (ecx = WP* this; 3 locals).
 * WPPos(this, &loc); sub = $FA$_t_424ae3(this) (returns u16 -> movzx);
 * ecx = objPtrs[ax]; $tail call (@w33b_24bb2@8 — next chunk) with edx=loc;
 * test [this+1]&2; if set: cl = [this+3]; if cl!=2 && cl!=3 && al!=0 skip,
 * else [this+1] = 1; ret.
 * Transplant entry — verbatim FA body (thiscall ecx + caller-CX-style reg
 * use; adjacent-chunk calls). */
extern long __stdcall w44hWPPos(long a, long *b);
extern short __fastcall w44h_424ae3(long a);
extern char * __fastcall w44h_24bb2(int a, int b);
extern void **objPtrs;

void w44h_24b63(long t)
{
    long loc[4];
    (void)w44hWPPos(t, loc);
    loc[3] = w44h_424ae3(t);
    loc[1] = (long)objPtrs;
    (void)w44h_24bb2(0, 0);
}
