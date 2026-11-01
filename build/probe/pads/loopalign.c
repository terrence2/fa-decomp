int f(const char *s) { int n = 0; while (*s) { n++; s++; } return n; }
int g(char *d, const char *s) { while (*s) *d++ = *s++; return 0; }
int h(int a) { int i, x = 0; for (i = 0; i < 100; i++) x ^= a << (i & 7); return x + a; }
int k(int a) { int i, x = a; for (i = 0; i < 3; i++) x = x * 5 + i; return x; }
