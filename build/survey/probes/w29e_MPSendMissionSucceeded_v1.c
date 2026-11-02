/* ?MPSendMissionSucceeded@@YGXXZ @ rva 0x6efa0 (48 B) — stdcall void(void):
   if (numComputers != 1) build msg "M"+dword(_missionSucceeded) at the
   local and snd(-1, msg, 5, 1) ($FA$_t_46b260). Store interleave per
   Fort/Side sibling recipe: msg[0]='M' first in source; dword second. */
extern long w29e_nc;           /* =_numComputers */
extern unsigned long w29e_ms;  /* =_missionSucceeded */
extern void __stdcall w29e_snd(long a, unsigned char *b, long c, long d);
                               /* =$FA$_t_46b260 */

void __stdcall MPSendMissionSucceededW(void)
{
    unsigned char msg[8];
    if (w29e_nc != 1) {
        msg[0] = 'M';
        *(unsigned long *)(msg + 1) = w29e_ms;
        w29e_snd(-1, msg, 5, 1);
    }
}