// _OBJProc @ rva 0x72b30 (48 B) — dialog message-id -> proc-address selector:
//   xor eax,eax / mov al,[esp+4] (zero-extend the uchar id via xor+mov al) /
//   cmp eax,3 / je / cmp eax,4 / je / cmp eax,6 / je / xor eax,eax / ret /
//   case blocks at end: b8 <_OBJEventProc> / b8 <?OBJDamageProc@@...> /
//   b8 <_OBJSayProc> each followed by ret (imm32 abs fixups)
// Plain-C sparse switch with uchar param — the wave-16 uchar-dispatcher
// family, here the cmp-eax-immediate form (probe b18c_OBJProc; if-chain
// instead gives 3c-imm8 byte compares on al and case-inline layout). Taking
// the addresses: b8 imm32 + DIR32 to each proc symbol.
extern void OBJEventProc(char *data);
extern void OBJDamageProc(char *data);
extern void OBJSayProc(char *data);

int __cdecl OBJProc(unsigned char id)
{
    switch (id) {
    case 3: return (int)OBJEventProc;
    case 4: return (int)OBJDamageProc;
    case 6: return (int)OBJSayProc;
    }
    return 0;
}
