// ?Unlock@CDirDrawSurface@@QAEHXZ @ rva 0x777d0 (59 B code + pad) —
// guards [ecx] (m_dds==0) and [esi+0x74] (m_cookie==0) return 0 inline
// (jne 04 over xor/pop/ret copies); arg1=srf, arg2=f2c pushed (f2c
// first), vtable deref call [eax+0x80] (ff 90 — DX virtual th table
// slot +0x80 via the DDSVt fn-ptr table spell); hr==0 arm inline:
// c7 46 74 cookie=0 + b8 01 + return 1, else shared ret0 at the end.
// Field map: +0 m_dds, +0x2c m_f2c, +0x74 m_cookie (pad1 0x44).
typedef long (__stdcall *ddFn)(void *srf, void *arg);
struct DDSVt {
    ddFn d[0x20];
    ddFn unlock;       /* +0x80 */
};

class CDirDrawSurface {
    void *m_dds;      /* +0 */
    char pad0[0x28];
    void *m_f2c;      /* +0x2c */
    char pad1[0x44];
    long m_cookie;    /* +0x74 */
public:
    long Unlock(void);
};

long CDirDrawSurface::Unlock(void)
{
    long hr;

    if (m_dds == 0)
        return 0;
    if (m_cookie == 0)
        return 0;
    hr = ((DDSVt *)*(void **)m_dds)->unlock(m_dds, m_f2c);
    if (hr == 0) {
        m_cookie = 0;
        return 1;
    }
    return 0;
}