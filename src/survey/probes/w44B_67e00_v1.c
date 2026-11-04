/* unnamed @ rva 0x67e00 (dec 425472), size 0x60:
 * entry: caller passes RM record ptr in ECX; RMAccess(ecx, 0x810c) returns
 * a string whose first char is a tag; strlen(s+1) copies strlen+1 bytes
 * (the string incl NUL) into unAvailNames + (int)counter*32, bumps the
 * 16-bit counter after the copy.
 */
extern char *unAvailNames;
extern short unAvailPilots;
unsigned long __stdcall RMAccess(int, int);

void __fastcall w44B_rmcopy(int key)
{
    unsigned long r = RMAccess(key, 0x810c);
    char *s = (char *)r + 1;
    int n = strlen(s);
    short c = unAvailPilots;
    char *dst = unAvailNames + (int)c * 32;
    memcpy(dst, s, n + 1);
    unAvailPilots = (short)(c + 1);
}