// _MSGHide@0 @ rva 0x18460 (48 B) — FA asm: mov ax,<lastWeaponButton+0xe8>
//   (66 a1) / mov dl,<lastWeaponButton+0x8> / mov byte [..+8],1 / movsx
//   ecx,ax / inc ax (66 40) / mov <..+0xe8>,ax (66 a3 store) / mov byte
//   [ecx + lastWeaponButton + 0x64c8],dl / ret.  Hides the current message:
//   stash the msg-flag byte (+8) into the message ring slot at the ++'d
//   16-bit write cursor (+0xe8, cursor sign-extended as the slot index), and
//   arm the flag.  Naked asm: v1 plain C collapsed to movzx + 66 ff 05
//   mem-inc (CL kept w 32-bit, never re-stored the 16-bit cursor, stored the
//   ring byte as a direct moffs with no index reg) — the 16-bit ax plan with
//   a movsx'd ecx slot index is asm-only (post-dec-counter class, wave 8).
//   The ring store is the bracket-after-symbol form (wave-13 rule): MASM
//   drops literal [ecx + sym + 0x64c8] to a bare moffs store, so the ring
//   base is its own extern with the 0x64c8 addend carried in the map TO.
//   Probe b18_MSGHide_v2.obj — exact modulo fixup dwords.
extern char lastWeaponButton[];
extern char msgRing[];

__declspec(naked) void __stdcall MSGHide(void)
{
    __asm {
        mov ax, word ptr [lastWeaponButton+0xe8]
        mov dl, byte ptr [lastWeaponButton+0x8]
        mov byte ptr [lastWeaponButton+0x8], 1
        movsx ecx, ax
        inc ax
        mov word ptr [lastWeaponButton+0xe8], ax
        mov byte ptr msgRing[ecx], dl
        ret
    }
}