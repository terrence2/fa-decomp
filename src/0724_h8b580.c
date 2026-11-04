/* unnamed @ rva 0x8b580 (dec 570752), size 0x50: fastcall struct-arg
 * (ECX = rec); if (rec->[0]) strcat(buf540, rec->a); if (rec->[4]) {
 * if (buf5a0[0]) strcat(buf5a0, fmt ("%s%s" @0x4eca00));
 * strcat(buf5a0, rec->b); }  — all three strcat calls are BAKED rel32
 * in FA (no .reloc entries at the e8 disps; only the push imm32 dwords
 * and the a0 moffs are reloc'd).
 * push-imm targets (reloc'd):
 *   0x54a540 buf = $FA$_d_4e7000+0x63540
 *   0x54a5a0 buf = $FA$_d_4e7000+0x635a0
 *   0x4eca00 fmt = $FA$_d_4e7000+0x5a00
 */
#pragma function(strcat)   /* FA calls real _strcat; /O2 would inline it */
extern char w44B_buf540[];
extern char w44B_buf5a0[];
extern char w44B_fmt[];
extern char *strcat(char *, const char *);

typedef struct { char *a; char *b; } W44Brec;

void __fastcall w44B_8b580(W44Brec *p)
{
    if (p->a)
        strcat(w44B_buf540, p->a);
    if (p->b) {
        if (w44B_buf5a0[0])
            strcat(w44B_buf5a0, w44B_fmt);
        strcat(w44B_buf5a0, p->b);
    }
}