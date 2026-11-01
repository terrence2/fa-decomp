// @APRemoveFromCarrier@0 @ rva 0xbaf00 (48 B incl. 14 B census tail)
//   mov eax, airports+0x3020 (apShipBaseQ)
// head:
//   mov cx, [_curId]
//   cmp [eax], cx
//   je found
//   add eax, 0x18
//   cmp eax, [_overflow_ptr]
//   jb head
//   ret
// found:
//   mov word [eax], 0
//   ret
// Walks the airport array (structs at +0x3020, stride 0x18) and zeroes the
// word of the entry whose id matches _curId; relocs @1/_airports +0x3020,
// @8 _curId, @15 _overflow_ptr (all identity).  w14c_a probe: 34 code bytes
// + 3 relocs byte-exact, incl. 16-bit cx reload at loop head.
extern char airports[];
extern unsigned short curId;
extern char overflow_ptr[];

void __fastcall APRemoveFromCarrier(void)
{
    char *p;
    p = airports + 0x3020;
    for (;;) {
        unsigned short id;
        id = curId;
        if (*(unsigned short *)p == id)
            break;
        p += 0x18;
        if (p < overflow_ptr)
            continue;
        return;
    }
    *(unsigned short *)p = 0;
}
