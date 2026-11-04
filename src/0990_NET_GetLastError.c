// ?NET_GetLastError@@YAXPADH@Z @ rva 0xad6f0 (32 B) — void
// NET_GetLastError(char *buf, int n): _strncpy(buf, winsock_error_buf, n).
// eax/ecx param preloads, push (n, &winsock_error_buf, buf) — the 68 imm
// push of the buffer global's address comes from src-array decay
// (w22b: push IMM + abs reloc = array symbol, not pointer deref). __cdecl
// caller-cleans (call / add esp,0xc / ret): plain C.
extern char *strncpy(char *dst, const char *src, unsigned int n);
extern char winsock_error_buf[];

void netGetLastErrorQ(char *buf, int n)
{
    strncpy(buf, winsock_error_buf, n);
}