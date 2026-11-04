/* w43F 0x4e6e0 (48 B): 8 a3 stores from a kept-in-eax staging int (0 x4, 10 x4)
 * to ?InPacket@@3USERIAL_PACKET_WRAPPER@@A+0x17c..+0x198.  Wave-11 a3-from-var
 * recipe: stores from variable assignments, not literals.
 */
extern long w43F_inpa, w43F_inpb, w43F_inpc, w43F_inpd;
extern long w43F_inpe, w43F_inpf, w43F_inpg, w43F_inph;

void w43F_4e6e0(void)
{
    long z;
    z = 0;
    w43F_inpa = z;
    w43F_inpb = z;
    w43F_inpc = z;
    w43F_inpd = z;
    z = 10;
    w43F_inpe = z;
    w43F_inpf = z;
    w43F_inpg = z;
    w43F_inph = z;
}