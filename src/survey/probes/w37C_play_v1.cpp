/* _CTDo_play @ rva 0x64d80 (96 B) -- v1.  buf[16]; Strncpy(buf,
 * (ctpc() & 0xffff) + st+0x46, 0xc) with the 0xc push scheduled before the
 * helper call; then if (!st+0xec && UGetFileSize(buf) != -1) { SingleSound;
 * RMFree; }. */
extern "C" int __cdecl w37c_ctpc(void);         /* $FA$_t_464c90 */
extern "C" void __stdcall w37c_strncpy(char *d, unsigned long s, unsigned long n);
extern "C" long __fastcall UGetFileSize(char *d);
extern "C" void __stdcall RMFree(char *d);
short __stdcall SingleSound(char *d, short a, unsigned char b, short c);

extern unsigned long w37c_std46;                /* _serviceTicks+0x46 */
extern unsigned char w37c_stec;                 /* _serviceTicks+0xec */

extern "C" void w37c_play(void)
{
    char buf[16];

    w37c_strncpy(buf, (w37c_ctpc() & 0xffff) + w37c_std46, 0xc);
    if (!w37c_stec && UGetFileSize(buf) != -1) {
        SingleSound(buf, 255, 255, 0);
        RMFree(buf);
    }
}