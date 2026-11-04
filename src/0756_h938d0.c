/* w40H 0x938d0 v2 — single-register zero loop (FA keeps one base in eax:
 * mov [eax],0; add eax,4; dec ecx; nop; mov [eax-0x14],0; jne) spelled as
 * *p++ = 0; p[-5] = 0. v1's two-pointer spelling gave CL a 2-reg loop
 * with c7 stores — wrong shape. */
typedef long (*VT0)(long, long, long);

extern long w40hA1;   /* -> $FA$_t_493910 */
extern long w40hA2;   /* -> $FA$_t_493a70 */

void w40h938d0(long obj)
{
	long r, vt, *p, i;

	vt = *(long *)((char *)obj + 4);
	r = (*(VT0 *)vt)(obj, 1, 0x46);
	*(long *)((char *)obj + 0x186) = r;
	*(long *)r = (long)&w40hA1;
	p = (long *)((char *)r + 0x36);
	*(long *)((char *)r + 4) = (long)&w40hA2;
	for (i = 4; i != 0; i--) {
		*p++ = 0;
		p[-5] = 0;
	}
}
