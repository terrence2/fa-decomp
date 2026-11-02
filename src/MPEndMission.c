extern unsigned long numComputers;
extern void __stdcall ChatSend_q(unsigned long a, char *b, unsigned long c, unsigned long d);
extern void __stdcall CHATEndMission(void);

void __stdcall MPEndMission_q(void)
{
    char buf[4];
    if (numComputers != 1) {
        buf[3] = 0x12;
        ChatSend_q(0xffffffff, buf + 3, 1, 1);
        CHATEndMission();
    }
}
