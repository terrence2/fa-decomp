extern char curThing[];
extern void __fastcall SoundOff(short a);
void __stdcall PLANETurnOffGunSound(void)
{
    if (*(short *)(curThing + 0x278) == -1)
        return;
    SoundOff(*(short *)(curThing + 0x278));
    *(unsigned short *)(curThing + 0x278) = (unsigned short)-1;
}
