// @APAddToCarrier@4 @ rva 0xbaea0 (96 B = 83 code + 13 pad 8d9b..+8da4..)
// -- FA asm: fastcall (thing* in ecx; dx is LOCAL scratch reloaded from
// _curId, NOT a param): push esi / mov eax,_airports+0x3020 (24-B carrier
// slots; WORD id at +0, DWORD value at +2) / L: mov dx,ds:_curId /
// cmp [eax],dx / je found / add eax,0x18 / cmp eax,_overflow_ptr / jb L /
// mov esi,_airports+0x3020 / L2: cmp word [esi],0 / je empty / add esi,0x18
// / cmp esi,_overflow_ptr / jb L2 / pop esi / ret.  found: pop esi /
// [eax+2],ecx / ret.  empty (pushedesi IS THE 3RD ARG OF APSetOffset):
// push esi / [esi+2],ecx / push ecx / push 0x508738 (_curThing) /
// call ?APSetOffset@@YGX... (cleans 3) / mov ax,ds:_curId /
// mov [esi],ax / pop esi / ret.  Naked-asm escape (dx/esi register plan).
extern short curId;
extern char airports[];
extern char overflow_ptr[];
extern void* curThing;
extern void apsetoffset();

void __declspec(naked) __fastcall APAddToCarrier(unsigned thing)
{
    __asm {
        push esi
        mov eax, OFFSET airports + 0x3020
    L1:
        mov dx, word ptr curId
        cmp word ptr [eax], dx
        je Lfound
        add eax, 18h
        cmp eax, OFFSET overflow_ptr
        jb L1
        mov esi, OFFSET airports + 0x3020
    L2:
        cmp word ptr [esi], 0
        je Lempty
        add esi, 18h
        cmp esi, OFFSET overflow_ptr
        jb L2
        pop esi
        ret
    Lfound:
        pop esi
        mov dword ptr [eax+2], ecx
        ret
    Lempty:
        push esi
        mov dword ptr [esi+2], ecx
        push ecx
        push OFFSET curThing
        call apsetoffset
        mov ax, word ptr curId
        mov word ptr [esi], ax
        pop esi
        ret
    }
}