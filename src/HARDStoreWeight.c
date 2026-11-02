// @HARDStoreWeight@4 @ rva 0x51f60 (64 B) — FA asm (fastcall, FPO frame):
//   0f b6 01 (movzx eax,byte [ecx])/0f b6 c0 (movzx eax,al)/ff 24 85
//   <tbl 0x451f90> (jmp dword [eax*4+tbl] — inline jump table, 4 absolute
//   dwords 0x451f76/0x451f7a/0x451f86/0x451f86 + 8d 49 00 nop pad; dis.py's
//   "SIB scale-2 flag" was a heuristic misfire on the ff 24 85 form)/
//   case 7: 8b 41 57 (mov eax,[ecx+0x57])/c3; case 8: 33 c0 (xor eax)/
//   8b 51 08 (mov edx,[ecx+8])/66 8b 41 05+0f b7 c0 (movzx ax word [ecx+5])/
//   03 c2 (add eax,edx)/c3; case 9,10: 33 c0/66 8b 41 05/0f b7 c0/c3;
//   default: 33 c0/c3.  Switch on the byte at the HARD record, returning
//   [p+0x57], (word [p+5] + dword [p+8]), word [p+5], or 0.  Plain C exact
//   — CL 4.2 emits the same ff 24 85 inline table with identical case arms
//   (probe build/w4probe/b20b_hard_v1.obj — exact modulo the 4 table-entry
//   dword windows).
long __fastcall HARDStoreWeight(void *p)
{
    switch (*(unsigned char *)p) {
    case 7:
        return *(long *)((char *)p + 0x57);
    case 8:
        return *(unsigned short *)((char *)p + 5) + *(long *)((char *)p + 8);
    case 9:
    case 10:
        return *(unsigned short *)((char *)p + 5);
    default:
        return 0;
    }
}