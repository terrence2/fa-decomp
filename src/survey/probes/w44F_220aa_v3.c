/* rva 0x220aa (106 B) - bitmap-access setup (global strcpy + RM handle).
   naked: CL constant-folds the zero arg (6a 00 pushes vs FA's reg-held
   xor ebx,ebx), CSEs the +0x54 into an early add (FA lea + late add), and
   pushes the RM arg before the movsb. Transcription is deterministic. */
extern long th;
extern unsigned long w44f_res;
extern void __stdcall SetupBitmapAccess(long, long, long);
extern void __fastcall MMPushAllocId(int);
extern long __stdcall RMAccessHandle(char *, unsigned long);
extern void __fastcall MMPopAllocId(void);

__declspec(naked) void w44F_220aa(void)
{
    __asm {
        push ebx
        push esi
        push edi
        xor  ebx, ebx
        push ebx
        push ebx
        push 0x180
        call SetupBitmapAccess
        mov  ecx, 7
        call MMPushAllocId
        mov  edx, dword ptr [th]
        mov  ecx, -1
        sub  eax, eax
        lea  edi, [edx+0x54]
        repne scasb
        not  ecx
        sub  edi, ecx
        mov  eax, ecx
        shr  ecx, 2
        mov  esi, edi
        mov  edi, 0x4ec520
        rep  movsd
        mov  ecx, eax
        push 0x810c
        and  ecx, 3
        add  edx, 0x54
        rep  movsb
        push edx
        call RMAccessHandle
        mov  dword ptr [w44f_res], eax
        call MMPopAllocId
        push ebx
        push ebx
        push ebx
        call SetupBitmapAccess
        pop  edi
        pop  esi
        pop  ebx
        ret
    }
}