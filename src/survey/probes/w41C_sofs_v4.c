// v4 = v3b (q/long i/long h) with FA's init order: i=0 before q.
extern void __stdcall RMChangeType(int a, char *b, char *c);
extern void *__stdcall w41C_RMSeqAccess(char *b, int n);
extern char defaultChatSoundName[];
extern long w41C_modBase;
extern void __fastcall SoundOff(int i);

void __cdecl SEQsndoff(int p)
{
    char buf[16];
    char *q;
    long i;
    long h;

    RMChangeType(p, defaultChatSoundName + 0x14, buf);
    h = (long)w41C_RMSeqAccess(buf, 0x104);
    if (h == 0)
        return;
    i = 0;
    q = (char *)&w41C_modBase;
    do {
        if (*(long *)q == h)
            SoundOff((int)i);
        q += 0x54;
        i++;
    } while (q < (char *)&w41C_modBase + 0x540);
}