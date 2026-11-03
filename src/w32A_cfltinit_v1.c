// 0xd4a20 __cfltcvt_init (56 B) — v1: table init, 4 c7 05 imm stores +
// CSE'd eax copy of __cfltcvt into slots 0 and 5 (spelled last-in-source)
extern void *w32a_tab[6];            /* -> __cfltcvt_tab */
extern void __cdecl w32a_cropzeros(void);   /* -> __cropzeros */
extern void __cdecl w32a_fassign(void);    /* -> __fassign */
extern void __cdecl w32a_forcdecpt(void);  /* -> __forcdecpt */
extern void __cdecl w32a_positive(void);   /* -> __positive */
extern void __cdecl w32a_cfltcvt(void);    /* -> __cfltcvt */

void __cdecl w32a_cfltinit(void)
{
    w32a_tab[1] = (void *)w32a_cropzeros;
    w32a_tab[2] = (void *)w32a_fassign;
    w32a_tab[3] = (void *)w32a_forcdecpt;
    w32a_tab[4] = (void *)w32a_positive;
    w32a_tab[0] = (void *)w32a_cfltcvt;
    w32a_tab[5] = (void *)w32a_cfltcvt;
}