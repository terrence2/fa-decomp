/* w44C 128e0 @StringToNumber@4 v1 — fastcall (ECX = string). FA shape: dollar
 * flag in BL (preserved reg), acc in esi, digit in edi (survives iterations:
 * non-digit chars reuse the previous digit), p walks in ebp, base is a stack
 * dword reloaded each iteration (all 4 preserved regs busy; tolower clobbers
 * eax/ecx/edx). Prefix selects base: '$'>0x10+dollar, '%'>1, '^'>0xa+hat.
 * FA quirk kept: digit only assigned for 0-9 / $-hex-letters. */
extern int __cdecl tolower(int);

long __fastcall w44c_stringtonumber(char *p)
{
    long acc, base, digit;
    unsigned char c;
    char dollar = 0, neg = 0, hat = 0;

    c = *p;
    if (c == '$') { dollar = 1; p++; base = 0x10; }
    else if (c == '%') { p++; base = 1; }
    else if (c == '^') { hat = 1; p++; base = 0xa; }
    else base = 0xa;

    acc = 0;
    digit = base;
    while ((c = tolower(*p)) != 0) {
        if (c == '-') { neg = 1; p++; continue; }
        if (c >= '0' && c <= '9')
            digit = c - '0';
        else if (dollar && c >= 'a' && c <= 'f')
            digit = c - 0x57;
        acc = acc * base + digit;
        p++;
    }
    if (neg) acc = -acc;
    if (hat) acc = acc << 8;
    return acc;
}