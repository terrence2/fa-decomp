// _TopCenterDialog @ rva 0x87830 = 555056, 80 B (FA: ecx=[curDialog];
//   movsx eax,(short)[grMode+0xa]; movsx edx,(short)[ecx+0xc]; sub eax,edx;
//   cdq; sub eax,edx; sar eax,1 (floored /2); mov WORD [ecx+8],ax;
//   ecx=[curDialog] again; movsx eax,(short)[grMode+0xc]; movsx edx,
//   (short)[ecx+0xe]; sub eax,edx; mov ecx,3; cdq; idiv ecx; ecx=[curDialog];
//   mov WORD [ecx+0xa],ax; ret).
typedef struct { unsigned char pad[8]; short fx, fy, fw, fh; } D26;
extern void *w26_curDialogP; /* map _w26_curDialogP=?curDialog@@3PAUDIALOG@@A */
extern short w26_grModeWA; /* map _w26_grModeWA=_grMode+0xa */
extern short w26_grModeWB; /* map _w26_grModeWB=_grMode+0xc */

void w26c_TopCenterDialog_q(void)
{
    ((D26 *)w26_curDialogP)->fx = (short)((w26_grModeWA -
        ((D26 *)w26_curDialogP)->fh) / 2);
    ((D26 *)w26_curDialogP)->fy = (short)((w26_grModeWB -
        ((D26 *)w26_curDialogP)->fh) / 3);
}