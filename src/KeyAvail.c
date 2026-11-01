// _KeyAvail @ rva 0x11350 (48 B) — is a key pending? kbCount (word at
// 0x51de24) gates the zero-return; then cx = kbHeadPtr (0x51de20, zeroed
// first: 33 c9) and eax = kbBuffer[cx] (0x51de28, zeroed first: 33 c0) —
// the xor32+mov16 pair is CL 4.2's ushort-index/ushort-element codegen,
// exact from the first probe (w13c_key1; dis.py elides both 66-movs —
// raw FA bytes checked).
extern unsigned short kbCount;
extern unsigned short kbHeadPtr;
extern unsigned short kbBuffer[];

int __cdecl KeyAvail(void)
{
    unsigned short h;
    if (kbCount == 0)
        return 0;
    h = kbHeadPtr;
    return kbBuffer[h];
}