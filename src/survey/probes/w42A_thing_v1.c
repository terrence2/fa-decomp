/* w42A_thing_v1.c — FA chunk $FA$_t_426730 rva 0x26730 (VA 0x4026730)
 * fastcall self(ecx): push esi; push edi; lea edi,[ecx+0x12]; mov esi,ecx;
 *   call _COCornerSpeed@0 (target 0x476c00, identity, converted);
 *   66 89 07 [edi]=ax; 80 3d cmp byte[_curThing],4; jne; 66 3d cmp ax,0x54;
 *   jge; 66 c7 07 [edi],0x54; c6 46 14/15; 80 3d curThing again;
 *   66 c7 46 16,0x800; je; 66 c7 46 16,0x100; ba edx,2; mov ecx,esi;
 *   66 c7 46 18,00; call $FA$_t_426785; pop edi; pop esi; ret. No pad.
 * Caller 0x4265c0 still stub -> alias 0=$FA$_t_426730.
 */
extern char curThing[];
extern void __fastcall w42A_slotcopy(void *self, long slot);
extern int __stdcall COCornerSpeed(void);

void __fastcall w42A_thing(char *self)
{
    char *e;
    short v;

    e = self + 0x12;
    v = (short)COCornerSpeed();
    *(short *)e = v;
    if (*(char *)curThing == 4 && v < 0x54)
        *(short *)e = 0x54;
    *(char *)(self + 0x14) = 1;
    *(char *)(self + 0x15) = 0;
    if (*(char *)curThing == 4)
        *(short *)(self + 0x16) = 0x800;
    else
        *(short *)(self + 0x16) = 0x100;
    *(short *)(self + 0x18) = 0;
    w42A_slotcopy(self, 2);
}