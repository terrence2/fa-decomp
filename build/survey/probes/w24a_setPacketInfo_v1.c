void setPacketInfo(void *pk, long a, long b)
{
    *(unsigned char *)pk = (unsigned char)b | 0xFC;
    ((unsigned char *)pk)[3] = (unsigned char)a;
}
