extern char sndEnableQ;
extern unsigned short musicIdU;   /* ?musicId@@3FA */
void __fastcall SoundOff_q(char id);
void DMusicOff_q(void)
{
    if (sndEnableQ) {
        if (musicIdU != 0xffff)
            SoundOff_q((char)musicIdU);
        musicIdU = 0xffff;
    }
}
