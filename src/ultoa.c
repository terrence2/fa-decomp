/* __ultoa @ rva 0xe1fa0 — CRT forwarder; helper at $FA$_t_4e1f10 */
extern unsigned char *__cdecl ultoaHelper(unsigned long a, unsigned char *b,
                                          unsigned long c, int d);

unsigned char *__cdecl ultoa(unsigned long val, unsigned char *str,
                             unsigned long radix)
{
    ultoaHelper(val, str, radix, 0);
    return str;
}