// _COTwr@0 @ rva 0x770a0 (48 B) — type gate *(char*)_curThing==4 (a0 + cmp
//   al,4), then @COThrust@4(1) * 100 (shl 2 + two lea [r+r*4]) and the
//   mem-operand idiv f7 3d (cdq + idiv dword [_curThing+0x202]).
extern char curThing[];
extern long __fastcall COThrust(int a);
long __stdcall COTwr_q(void)
{
    if (*(char *)curThing != 4)
        return 0;
    return COThrust(1) * 100 / *(long *)(curThing + 0x202);
}