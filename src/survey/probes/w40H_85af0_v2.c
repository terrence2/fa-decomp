/* w40H 0x85af0 v2 — 6-B member struct copy to force FA's lea pair
 * (lea eax,[edi+0x36]; lea edx,[esi+8]; dword + word halves), then the
 * dword at +0x32 and the 16-bit byteswap (which v1 already matched:
 * 66 8b c8 8a e9 8a cc). */
struct W40hF { long a; unsigned short b; };
struct W40hD2 { unsigned short w0; unsigned short w2; long d4;
		struct W40hF f8; };
struct W40hS2 { long d32; struct W40hF f4; unsigned short wc; };

void w40h85af0(struct W40hD2 *dst, struct W40hS2 *src)
{
	dst->w0 = 2;
	dst->f8 = src->f4;
	dst->d4 = src->d32;
	dst->w2 = (unsigned short)((src->wc << 8) | (src->wc >> 8));
}
