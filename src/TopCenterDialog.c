// _TopCenterDialog @ rva 0x87830 = 555056, 80 B (FA: eax=(short)[grMode+0xa]
//   (WA); edx=(short)[d+0xc] (fw); cdq/sub/sar /2; store [d+8]; then eax=
//   (short)[grMode+0xc] (WB); edx=(short)[d+0xe] (fh); idiv 3; [d+0xa].
//   v2: swap the field uses so stmt1 reads +0xc and stmt2 reads +0xe).
typedef struct { unsigned char pad[8]; short fx, fy, fw, fh; } D26;
extern void *w26_curDialogP; /* map _w26_curDialogP=?curDialog@@3PAUDIALOG@@A */
extern short w26_grModeWA; /* map _w26_grModeWA=_grMode+0xa */
extern short w26_grModeWB; /* map _w26_grModeWB=_grMode+0xc */

void w26c_TopCenterDialog_q(void)
{
    ((D26 *)w26_curDialogP)->fx = (short)((w26_grModeWA -
        ((D26 *)w26_curDialogP)->fw) / 2);
    ((D26 *)w26_curDialogP)->fy = (short)((w26_grModeWB -
        ((D26 *)w26_curDialogP)->fh) / 3);
}