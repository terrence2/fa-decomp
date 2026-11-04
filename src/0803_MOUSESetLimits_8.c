// _MOUSESetLimits@8 @ rva 0x97d20 (32 B) — 16-bit param pair (66 8b loads)
//   stored 0x48/0x4a into _mouseButtonPresses: first is FA's 66 a3 moffs
//   store from AX, second 66 89 0d from CX.
extern char mouseButtonPresses[];
void __stdcall MOUSESetLimits_q(unsigned short x, unsigned short y)
{
    *(unsigned short *)(mouseButtonPresses + 0x48) = x;
    *(unsigned short *)(mouseButtonPresses + 0x4a) = y;
}