/* w36E e4d70 - bounded wchar scan returning idx+1 capped at n */
int w36e_e4d70(const unsigned short *p, int n) {
    const unsigned short *s = p;
    int d = n;
    if (n != 0) {
        while (*s != 0) {
            s++;
            if (--d == 0) break;
        }
    }
    if (d != 0) {
        if (*s == 0) return (int)(s - p) + 1;
    }
    return n;
}
