extern char sndEnableQ;
extern short musicId;
void __fastcall SoundOff_q(char id);
void DMusicOff_q(void)
{
    if (sndEnableQ) {
        if (musicId != -1)
            SoundOff_q((char)musicId);
        musicId = -1;
    }
}
