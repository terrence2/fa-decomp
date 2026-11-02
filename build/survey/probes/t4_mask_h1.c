// t4_mask_h1: hybrid base = the v1 stream (the ONLY prior C shape whose CL
// output matches FA everywhere except one instruction). Expected CL:
//   8d 04 4d dffffffe   lea eax,[ecx*2-2]
//   66 f7 d0            not ax
//   66 25 fe ff         and ax,0xfffe        <- FA has 24 fe (and al,0xfe)
//   66 a3 <moffs>       mov cmdBufPos,ax
//   c3                  ret
// fitobj --patch '10,4,24fe' shrinks it to FA's 19 body bytes; the moffs
// reloc at 14 shifts to 12 automatically.
extern unsigned short cmdBufPos;

void __fastcall MaskEvents_q(int m)
{
    unsigned short s;

    s = m * 2 - 2;
    s = ~s;
    s &= 0xfffe;
    cmdBufPos = s;
}