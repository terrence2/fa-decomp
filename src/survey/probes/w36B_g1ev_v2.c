/* w36B v2: ?game_event_handler@@YADIJHPAUsocket_state@@@Z rva 0xadad0 (80 B).
 * v2: switch (ev) instead of the if-chain — CL 4.2 plans the sparse-case
 * switch as the je-case-label chain (FA's shape: cmp eax,1/je; cmp eax,2/
 * je; cmp eax,0x20/je; default mov al,1/ret), while the if-chain produced
 * jne-skip bodies.
 */
extern void gehc1(void *);
extern void nhfw(void *);
extern void sockclose(unsigned int);

char __cdecl w36bGEvent(unsigned int fd, long ev, char c, void *st)
{
    switch (ev) {
    case 1:    gehc1(st); return 1;
    case 2:    nhfw(st); return 1;
    case 0x20: sockclose(fd); return 1;
    default:   return 1;
    }
}