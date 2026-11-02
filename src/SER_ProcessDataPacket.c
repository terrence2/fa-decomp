// ?SER_ProcessDataPacket@@YAXAAUSERIAL_PACKET_WRAPPER@@@Z @ rva 0x904f0
// (32 B) — wrapper: mov eax,[esp+4] / push eax (the packet) / push
// &InQueue (abs fixup) / call insertQueue(q, pkt) / c6 05 <Ctrl+0x128>,0
// (elided by dis.py — dis.py c6 05 elision, objdump cross-checked) /
// add esp,8 / ret. FA stores the Ctrl flag byte BETWEEN the call and the
// add esp — try plain C (same compiler; scheduling may match), fall to
// asm if CL emits add-first.
extern char serQData[];
extern char serCtrlFlagQ;

void __cdecl insertQueue(void *q, void *w);

void __cdecl SER_ProcessDataPacket(void *w)
{
    insertQueue(serQData, w);
    serCtrlFlagQ = 0;
}