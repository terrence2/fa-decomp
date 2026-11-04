/* rva 0x5120 (64 B, code 56 + census tail 8): wait for master-next-screen */
extern long thisComputer;
extern volatile long masterNextScreen;
extern unsigned short curScreen;
extern void __stdcall MPReceive(void);
extern void __stdcall MPCheckDisconnect(void);

void w43A_5120(void)
{
    long ms;
    if (thisComputer <= 0) return;
    ms = masterNextScreen;
    while (ms == -1) {
        MPReceive();
        MPCheckDisconnect();
        ms = masterNextScreen;
    }
    masterNextScreen = -1;
    curScreen = (unsigned short)ms;
}
