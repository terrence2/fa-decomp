/* ?SER_Write@@YAJJPAEJ@Z @ 0x4b3d0 (144 B): serial write into packet queue.
 * long SER_Write(long a, unsigned char *data, long len)   [cdecl C++]
 *   sent = 0;                                 [33 f6]
 *   while (len > 0) {                         [test ebx,ebx; jle → done]
 *     if (!Ctrl.flag129) return -1;           [a0 byte test @ ?Ctrl+0x12d → -1]
 *     space = 0x14 - OutPacket.used;          [bd 14 / a1 used / 2b e8]
 *     if (space >= len) space = len;          [cmp space,len; jl skip; mov space,ebx]
 *     if (space > 0) {                        [85 ed; jle]
 *         memmove(&OutPacket.bufOut[used], data, space);
 *             [push space; mov eax,[used]; push data; add eax,0x5404c4(&OutPacket+0x1c);
 *              push eax; call memmove; add esp,0xc]
 *         data += space; sent += space; len -= space; OutPacket.used += space;
 *             [03 fd; 03 f5; 2b dd; 01 2d 5404bc]
 *     }
 *     if (len > 0 && !SER_Flush(a, 0)) break; [mov eax,[esp+0x14](arg1); push 0; push eax;
 *                                              call ?SER_Flush@@YADJD@@Z; test al; jne loop]
 *     break;                                   [after jne falls through]
 *   }
 *   return Ctrl.flag129 ? sent : -1;          [recheck flag; esi=-1 if cleared]
 *   OutPacket = ?OutPacket@@3USERIAL_PACKET_WRAPPER@@A @ 0x5404a8;
 *     used = dword at +0x14 (0x5404bc); buffer at +0x1c (0x5404c4)
 *   Ctrl = ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A @ 0x5680e8; flag byte at +0x12d
 */
extern struct { unsigned char pad0[0x14]; long used; long pad1; unsigned char bufOut[1024]; } OutPacket;
extern struct { unsigned char pad0[0x12d]; unsigned char flag129; } Ctrl;
extern void *memmove(void *dst, const void *src, long n);
extern char SER_Flush(long a, char b);

long SER_Write(long a, unsigned char *data, long len)
{
    long sent;
    long space;

    sent = 0;
    while (len > 0) {
        if (!Ctrl.flag129)
            return -1;
        space = 0x14 - OutPacket.used;
        if (space >= len)
            space = len;
        if (space > 0) {
            memmove(OutPacket.bufOut + OutPacket.used, data, space);
            data += space;
            sent += space;
            len -= space;
            OutPacket.used += space;
        }
        if (len > 0) {
            if (SER_Flush(a, 0))
                continue;
        }
        break;
    }
    return Ctrl.flag129 ? sent : -1;
}