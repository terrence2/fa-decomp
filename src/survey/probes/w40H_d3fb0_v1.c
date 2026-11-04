/* w40H 0xd3fb0 (58 B, 3 params, FPO): CRT lock wrapper.
 * h = $FA$_t_4d84f0(); if (!h) return 0; r = $FA$_t_4d82e0(p1,p2,p3,h);
 * __unlock_file(h); return r.  __unlock_file = wave-39 converted 0xd7270. */
extern long w40hLockAq(void);
extern long w40hInAq(long a, long b, long c, long h);
extern void unlock_fileX(long h);

long w40hD3fb0(long p1, long p2, long p3)
{
	long h, r;

	h = w40hLockAq();
	if (h == 0)
		return 0;
	r = w40hInAq(p1, p2, p3, h);
	unlock_fileX(h);
	return r;
}
