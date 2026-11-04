/* w36C 0x92c30 @ASynchJoystick@0 v3: whole-body naked asm (precedent
 * w34H_e4460/w35B_69eb0).  FA reg plan: newBtn=eax, i=ecx, mask=edx,
 * old=esi, n=edi, dev chain edx/esi/ebx; caps load is a baked-disp
 * [esi+caps+3Ch].  Interleaved prolog per FA bytes:
 * push ebx / a0 joyInit / push esi / test / push edi / je pops.
 * 15 B census tail after ret (8d 64 24 00 x2, 8d a4 24 ...). */
extern char          joyInitX;         /* _joyInitX=?joysticksInitialized@@3DA */
extern unsigned long joystickXDevice;  /* identity */
extern unsigned long joystickFunctions;
extern unsigned long joystickButtons;
extern unsigned long buttonPresses[];
extern char          capG[];           /* _capG=?joystickCaps@@3PAUtagJOYCAPSA@@A */

void __fastcall ReadJoystickButtons(void);

__declspec(naked) void __fastcall ASynchJoystick(void)
{
    __asm {
        push    ebx
        mov     al, byte ptr joyInitX
        push    esi
        test    al, al
        push    edi
        je      Lpops
        mov     eax, dword ptr joystickFunctions
        test    al, 3
        je      Lpops
        call    ReadJoystickButtons
        xor     ecx, ecx
        mov     edx, dword ptr joystickXDevice
        lea     esi, [edx+edx*4]
        lea     ebx, [esi+esi*8]
        lea     esi, [ebx+ebx*8]
        sub     esi, edx
        mov     edi, dword ptr capG[esi+3Ch]
        cmp     edi, ecx
        je      Lstore
        mov     esi, dword ptr joystickButtons
    Lloop:
        mov     edx, 1
        shl     edx, cl
        test    edx, eax
        je      Lnext
        test    edx, esi
        jne     Lnext
        inc     dword ptr buttonPresses[ecx]
    Lnext:
        inc     ecx
        cmp     ecx, edi
        jb      Lloop
    Lstore:
        mov     dword ptr joystickButtons, eax
    Lpops:
        pop     edi
        pop     esi
        pop     ebx
        ret
    }
}