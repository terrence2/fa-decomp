// _COBv@0 @ rva 0x76d70 (48 B) — FA asm:
//   push esi / mov ecx,6 / push edi / mov esi,OFFSET curThingType+0xca /
//   mov edi,OFFSET packetTicks+0x4e8 / rep movsd /
//   mov ax,[curThing+0x245] / pop edi / mov [packetTicks+0x4ea],ax /
//   pop esi / mov eax,OFFSET packetTicks+0x4e8 / ret
// Copies the current banked thing's 24-byte state block into
// packetTicks+0x4e8 and stores its banked-thing word, returning the
// destination address. Naked-asm escape: the state block is static-address
// (curThing/curThingType/packetTicks with baked addends), a rep movsd
// between them, and eax returns the static address — CL 4.2 cannot emit
// address-of-static returns interleaved with rep movs from C (probe
// b19b_cobv_v1 exact). Map: _packetTicks=?packetTicks@@3PAJA (c++-mangled
// FA global; both 0x4e8/0x4ea addends are baked by MASM).
extern char curThing[];
extern char curThingType[];
extern char packetTicks[];

int __declspec(naked) __stdcall COBv(void)
{
    __asm {
        push esi
        mov ecx, 6
        push edi
        mov esi, OFFSET curThingType + 0xca
        mov edi, OFFSET packetTicks + 0x4e8
        rep movsd
        mov ax, word ptr curThing[0x245]
        pop edi
        mov word ptr packetTicks[0x4ea], ax
        pop esi
        mov eax, OFFSET packetTicks + 0x4e8
        ret
    }
}