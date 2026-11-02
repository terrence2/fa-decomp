/* rva 571200 (0x8b740) 32 B FPO/esp gap chunk
 * 66 8b c1 mov ax,cx; 66 8b 0d <abs _timeCompression>; 66 85 c9; 7e 03;
 * 66 d3 e0 shl ax,cl; c3 -- 16-bit fastcall short form */
extern short w30h_timeCompression;

short __fastcall w30h_timeComp(short a)
{
    short t = w30h_timeCompression;

    if (t > 0)
        a = (short)(a << t);
    return a;
}