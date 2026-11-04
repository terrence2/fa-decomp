/* w36E d7e90 = e04c0 twin - wcsnlen shape (unsigned n) */
unsigned long w36e_d7e90(const unsigned short *p, unsigned long n) {
    const unsigned short *s = p;
    unsigned long d;
    if (n != 0) {
        d = n - 1;
        while (*s != 0) {
            s++;
            if (d-- == 0) break;
        }
    }
    if (*s == 0) return (unsigned long)(s - p);
    return n;
}
