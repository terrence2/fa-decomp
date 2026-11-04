// @Alive@4 @ rva 472848 (0x73710, 64 B) — plain C.  Decisive levers: field
//   reads as cast derefs off the ecx pointer; the dword at +1 kept live in a
//   local so both masks test it in AL/AH (test al,1 reuse then test ah,0x20
//   shape); word test at +0xe reads as 66 83 79 0e 00 via the ushort-cast
//   form; uchar tests emit the 3c imm cmp pair.  Guard order matters: dword
//   bit 0, word at +0xe, dword bit 0x2000, then the ==2/==4 gate at +0xe3.
//   Probe build/survey/probes/p_w23_Alive_v1.obj EXACT (w23_r2.json).
char __fastcall Alive_q(char *e)
{
    unsigned long d = *(unsigned long *)(e + 1);
    if ((d & 1) == 0)
        return 0;
    if (*(unsigned short *)(e + 0xe) == 0)
        return 0;
    if (d & 0x2000)
        return 0;
    if (*(unsigned char *)e == 2 || *(unsigned char *)e == 4) {
        if (*(unsigned char *)(e + 0xe3) == 0)
            return 0;
    }
    return 1;
}