// _G_InitCircles@0 @ rva 0x69810 (80 B) — push esi; xor esi (i=0);
//   loop: lea eax,[esi*4+&unAvailNames+0x24]; push 1; push esi;
//   mov ds:_pilotsUpdated+0x2d8,eax (a3); mov ax,_grMode+0xc (66 a1);
//   inc esi (i++ scheduled); sar ax,1; movsx ecx,ax; mov ax,_grMode+0xa;
//   push ecx; sar ax,1; movsx ecx,ax; push ecx; call _G_Circle@16;
//   cmp esi,0x14; jl loop; after: mov ds:_pilotsUpdated+0x2d8,0 (c7 05).
extern char w27a_unA24[];      /* ?unAvailNames@@3PADA+0x24 */
extern unsigned int w27a_puX;  /* _pilotsUpdated+0x2d8 */
extern short w27a_grX;         /* _grMode+0xa */
extern short w27a_grY;         /* _grMode+0xc */
extern void __stdcall G_Circle_f(int y2, int x2, int i, int one);
                               /* _G_Circle@16 */
void __stdcall w27a_gic_q(void)
{
    int i;
    for (i = 0; i < 0x14; i++)
    {
        w27a_puX = (unsigned int)(w27a_unA24 + i * 4);
        G_Circle_f(w27a_grX >> 1, w27a_grY >> 1, i, 1);
    }
    w27a_puX = 0;
}