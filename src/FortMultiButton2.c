// @FortMultiButton2@8 @ rva 0x4c520 — same two [ecx*4+disp32],edx stores into
//   ?InPacket@@3USERIAL_PACKET_WRAPPER@@A at +0x150 and +0x38 (probe v11).
extern long inPacketArr_x[];
extern long inPacketArr2_x[];

void __fastcall FortMultiButton2(int i, int v)
{
    inPacketArr_x[i] = v;
    inPacketArr2_x[i] = v;
}
