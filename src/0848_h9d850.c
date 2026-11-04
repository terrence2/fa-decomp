// w26a_9d850 @ rva 0x9d850 (645712, unnamed 16 B orphan) — FA bytes (raw):
//   a0 1b 88 50 00       mov al, ds:0x50881b   (moffs A0 form; _curThing+0xe3)
//   3c 1f                cmp al, 0x1f
//   75 05                jne L0 (short, target = the ret at +0x0e)
//   e9 b2 57 fc ff       jmp _CancelCmdBuf@0   (rel32, ext tail-jmp)
// L0: c3                ret
//   90                   (1 B census pad)
// Gate + tail-jmp into the 0-arg stdcall CancelCmdBuf.
extern char curThing_t[];    /* _curThing (+0xe3 addend baked by array form) */
extern void __stdcall CancelCmdBuf(void);
void w26a_9d850(void)
{
    if ((unsigned char)curThing_t[0xe3] != 0x1f)
        return;
    CancelCmdBuf();
}