// w29b B: ?NetProtocolPresent@@YADJ@Z @ rva 0xacb60 (64 B incl. 5-byte pad)
// void __cdecl (long). FA body:
//   eax = arg; sub esp,4 (1 dword local, read-only [esp+2] = its high word!)
//   if (arg == 1) w = 2; else if (4..5) w = 1; else w = [esp+2] (junk hiword)
//   join: push eax; call $FA$_t_4ae660 (cdecl, word arg); add esp,4
//   test eax,eax; setne cl; mov al,cl  (result dead — void ret)
//   add esp,4 (local free); ret
extern unsigned __cdecl stubnp_a(unsigned short w);

void NetProtocolPresent_q(long proto)
{
    unsigned short junk[2];
    unsigned short w;
    unsigned char flag;
    if (proto == 1)
        w = 2;
    else if (4 <= proto && proto <= 5)
        w = 1;
    else
        w = junk[1];
    flag = stubnp_a(w) != 0;
}