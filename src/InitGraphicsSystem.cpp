/* _InitGraphicsSystem @ 0x794e0 — v1: real C++ class decl -> exact mangles */
extern "C" unsigned long hWndMain;                        /* -> _hWndMain */

class CDirDraw {
public:
    static CDirDraw *m_singleton;
    int Create(void *p);
    int SetCooperativeLevel(unsigned long k);
    void Destroy(void);
    static int CreateSingleton(void);
    static void DeleteSingleton(void);
};

extern "C" int _InitGraphicsSystem_impl(void)
{
    if (!CDirDraw::CreateSingleton())
        return 0;
    if (!CDirDraw::m_singleton->Create((void *)hWndMain))
        { CDirDraw::DeleteSingleton(); return 0; }
    if (CDirDraw::m_singleton->SetCooperativeLevel(0x53))
        return 1;
    CDirDraw::m_singleton->Destroy();
    CDirDraw::DeleteSingleton();
    return 0;
}
