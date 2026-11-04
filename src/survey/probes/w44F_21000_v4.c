/* rva 0x21000 (96 B) - computer-index check (fastcall, x in ecx).
   naked: CL canonicalizes loop-bottom cmp to [mem],reg+3f/jg, keeps the
   second g1 read in ecx, flips tail comparands, and fuses the last return
   into setge - plus interleaves the pops. Transcription is deterministic. */
extern long numComputers;
extern long thisComputer;
extern int __fastcall w44f_fn(int);

__declspec(naked) unsigned char __fastcall w44F_21000(int x)
{
    __asm {
        push esi
        mov  eax, dword ptr [numComputers]
        push edi
        mov  esi, ecx
        cmp  eax, 1
        jne  L1
        mov  al, 1
        pop  edi
        pop  esi
        ret
L1:
        mov  ecx, dword ptr [thisComputer]
        test ecx, ecx
        jne  L2
        mov  edi, 1
        cmp  eax, edi
        jle  L2
Lloop:
        mov  ecx, edi
        inc  edi
        call w44f_fn
        cmp  edi, dword ptr [numComputers]
        jl   Lloop
L2:
        mov  eax, dword ptr [thisComputer]
        test eax, eax
        jle  L3
        mov  ecx, eax
        call w44f_fn
        cmp  eax, esi
        jg   L4
        add  eax, 3
        cmp  eax, esi
        jge  L3
L4:
        xor  al, al
        pop  edi
        pop  esi
        ret
L3:
        mov  al, 1
        pop  edi
        pop  esi
        ret
        _emit 0x05
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
    }
}