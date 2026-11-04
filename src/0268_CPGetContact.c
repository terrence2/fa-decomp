// ?CPGetContact@@YGGJ@Z @ rva 0x40be0 (32 B) — FA asm: mov eax,[esp+4]
//   (idx) / 8d 0c c5 00 00 00 00 lea ecx,[idx*8+0] (index-only lea, base=101
//   forces disp32=0) / sub ecx,eax (idx*7) / shl ecx,2 (idx*28) /
//   66 8b 84 89 <_frontRCS+0x10> mov ax,[ecx + ecx*4 + frontRCS+0x10]
//   (idx*28*5 = idx*140 halfword, contact-word at +0x10 of the 140-byte
//   record) / ret 4. frontRCS = the per-plane contact-RCS record array; each
//   contact's word sits at +0x10. CL reproduces the whole strength-reduction
//   chain from plain byte-offset arithmetic (idx*140 in one expression) —
//   the +0x10 lands as CL's own disp addend on the _frontRCS DIR32, so the
//   target VA (0x534050) is identity: NO map line (wave-17 TO rule; probe
//   b19c_cpg_a, diffs confined to the reloc window; tail = census 050pad).
extern char frontRCS[];

unsigned short __stdcall CPGetContact(long idx)
{
    return *(unsigned short *)&frontRCS[0x10 + idx * 140];
}