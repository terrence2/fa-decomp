#pragma pack(push,1)
typedef struct { unsigned char op; int v; } PKT;
#pragma pack(pop)

extern int numComputers;
extern int thisComputer;
extern void __stdcall mpSend(int a, void *b, int c, int d);
extern void __fastcall MPFlushAll(char c);

void __fastcall MPShellSendScreen(int p1)
{
    PKT pkt;

    if (numComputers != 1 && thisComputer <= 0) {
        pkt.op = 0x37;
        pkt.v = p1;
        mpSend(0xffffffff, &pkt, 5, 1);
        MPFlushAll(1);
    }
}