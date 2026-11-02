extern char sndEnableQ;
extern unsigned short musicIdU;   /* ?musicId@@3FA */
void __fastcall SoundOff_q(char id);
void DMusicOff_q(void)
{
    if (sndEnableQ) {
        unsigned short id;
        id = musicIdU;
        if (id != 0xffff)
            SoundOff_q((char)id);
        musicIdU = 0xffff;
    }
}
