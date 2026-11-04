/* _GetGround@0 @ rva 0x79df0 (80 B) -- stdcall void(void), frameless.
 * onTheGround = (char)OnTheGround(); push 1 (arg6);
 * T_Info(word[curId], curThing, curThing+0x11, &groundAngle, &groundSea, 1)
 * with FA's junk push ecx (entry-ecx garbage -- FA itself does it) and the
 * interleave; then groundY = *(long*)...; groundPitch = PAToF24(word
 * [groundAngle+2]) called with NO pushed arg (FA quirk, callee @4).
 * Whole-body naked-asm. */
extern void __stdcall OnTheGround(void);
extern void __stdcall T_Info(unsigned long, unsigned long, unsigned long,
                             unsigned long, unsigned long, unsigned long);
extern unsigned long __fastcall PAToF24(unsigned long);
extern char curThing[];
extern char onTheGround;
extern long groundSea;
extern long curId;
extern long groundAngle;
extern long groundY;
extern long groundPitch;

void __declspec(naked) __stdcall GetGround(void)
{
    __asm {
        call OnTheGround
        push 1
        mov BYTE PTR [onTheGround], al
        mov ax, WORD PTR [curThing + 1Dh]
        push OFFSET groundSea
        mov cx, WORD PTR [curId]
        push OFFSET groundAngle
        mov WORD PTR [groundAngle], ax
        push OFFSET curThing + 11h
        push OFFSET curThing
        push ecx
        call T_Info
        mov cx, WORD PTR [groundAngle + 2]
        mov DWORD PTR [groundY], eax
        call PAToF24
        mov DWORD PTR [groundPitch], eax
        ret
    }
}