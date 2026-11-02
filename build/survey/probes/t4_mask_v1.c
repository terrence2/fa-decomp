// t4_mask_v1: 32-bit route — compute ~(2m-2) in eax, and eax,~1 (83 e0 fe),
// truncate on store. Records what CL does when the mask is spelled 32-bit
// wide (FA uses 66 f7 d0 not ax + 24 fe and al — same total length, but the
// opcodes can only match if CL keeps the value 16-bit).
extern unsigned short cmdBufPos;

void __fastcall MaskEvents_q(int m)
{
    unsigned int s;

    s = (unsigned int)(m * 2 - 2);
    s = ~s;
    s &= ~1u;
    cmdBufPos = (unsigned short)s;
}