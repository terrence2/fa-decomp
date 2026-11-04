// _AngleOffNose@4 @ rva 0x11880 (112 B) -- naked-asm escape: FA's lea
// args [esp]/[esp+2] interleaved arg setup, 16-bit cx/dx reg carries and
// the sub-cx-moffs reads are not reproducible from CL's C scheduler.
extern int __stdcall Angles(void*, void*, short*, short*);
extern int __fastcall Abs(short);
extern char curThing[];

int __declspec(naked) __stdcall AngleOffNose(void* p)
{
    __asm {
        mov edx, [esp+4]
        sub esp, 4
        lea eax, [esp]
        lea ecx, [esp+2]
        push eax
        push ecx
        push edx
        push OFFSET curThing + 11h
        call Angles
        mov cx, word ptr [esp+2]
        sub cx, word ptr [curThing+1Dh]
        call Abs
        mov cx, word ptr [esp]
        sub cx, word ptr [curThing+1Fh]
        mov word ptr [esp+2], ax
        call Abs
        mov cx, ax
        mov dx, word ptr [esp+2]
        mov word ptr [esp], ax
        cmp cx, dx
        jg L1
        mov cx, dx
    L1:
        mov ax, cx
        add esp, 4
        ret 4
    }
}