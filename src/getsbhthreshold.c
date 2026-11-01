// __get_sbh_threshold @ rva 0xddfc0 (6 B, FPO cbProlog=0)
// FA asm: a1 1c bd 51 00  mov eax,ds:0x51bd1c (= __adbgmsg+0x1074)
//         c3
extern unsigned char _adbgmsg[];

int __cdecl _get_sbh_threshold(void)
{
    return *(const int *)(_adbgmsg + 0x1074);
}