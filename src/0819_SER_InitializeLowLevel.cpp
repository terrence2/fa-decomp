// w36A_98690_v1: ?SER_InitializeLowLevel@@YAXXZ @ 0x98690 (80 B, fx 6,
// tail 8x lea esp,[esp] census). Pure C++ 4.2: three InitializeQueue
// calls with the serial globals. Compiled as .cpp so every callee and
// data global mangles to FA's exact C++ publics (wave-33E recipe) —
// caller-cleaned cdecl (add esp,0xc per call), J = long, arrays decay
// (PAU mangle), queues by reference (AAU mangle).

struct SERIAL_QUEUE { char pad[24]; };
struct USERIAL_QUEUE { char pad[24]; };
struct USERIAL_PACKET_WRAPPER { char pad[24]; };

extern USERIAL_QUEUE InQueue;
extern USERIAL_QUEUE OutQueue;
extern USERIAL_QUEUE HistoryQueue;
extern USERIAL_PACKET_WRAPPER InQueuePackets[];
extern USERIAL_PACKET_WRAPPER OutQueuePackets[];
extern USERIAL_PACKET_WRAPPER HistoryQueuePackets[];

void SER_InitializeControlStruct(void);
void InitializeQueue(struct SERIAL_QUEUE &q, struct USERIAL_PACKET_WRAPPER *w, long n);

void SER_InitializeLowLevel(void)
{
    SER_InitializeControlStruct();
    InitializeQueue((struct SERIAL_QUEUE &)InQueue, InQueuePackets, 0x400);
    InitializeQueue((struct SERIAL_QUEUE &)OutQueue, OutQueuePackets, 0x40);
    InitializeQueue((struct SERIAL_QUEUE &)HistoryQueue, HistoryQueuePackets, 0x100);
}