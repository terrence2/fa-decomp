// @SAYRearmMessage@8 @ rva 0x8ca80 (48 B) — fastcall: param2 kept in si
//   (66 8b f2), three reg-arg calls ($FA$_t_48b570 with no arg, wingSay+0x5a8
//   in ecx, then $FA$_t_48cab0(esi, dx=word _curId) with a 16-bit dx load),
//   returns 1 in al (char return).
extern unsigned short curId;
extern char wingSay5a8[];
extern void __fastcall srmInit(void);
extern void __fastcall srmSay(void *p);
extern long __fastcall srmGo(unsigned short a, unsigned short b);
char __fastcall SAYRearmMessage_q(int a, unsigned short b)
{
    srmInit();
    srmSay(wingSay5a8);
    srmGo(b, curId);
    return 1;
}