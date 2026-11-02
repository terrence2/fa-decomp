// ?DMusicOff@@YIXXZ @ rva 0x32700 (48 B) — FA asm: a0 [sndEnable 0x4e75f0]/
//   test al,al/74 je/66 8b 0d [musicId]/66 83 f9 ff (cmp cx,-1)/74 je/
//   e8 ?SoundOff@@YIXF@Z (call, cl arg)/66 c7 05 [musicId],0xffff/ret.
extern char sndEnableQ;      /* $FA$_d_4e7000+0x5f0 */
extern short musicId;        /* ?musicId@@3FA */

void __fastcall SoundOff_q(char id);   /* ?SoundOff@@YIXF@Z */

void DMusicOff_q(void)
{
    if (sndEnableQ) {
        if (musicId != (unsigned short)-1)
            SoundOff_q((char)musicId);
        musicId = -1;
    }
}