// _ShutdownGraphicsSystem @ rva 0x79540 — m_singleton guarded thiscall
//   Destroy, then a ZERO-ARG tail call to the static DeleteSingleton (probe
//   d80; passing the singleton as an argument makes CL reload it — d55).
extern void *m_singleton;
extern void __fastcall CDirDraw_Destroy(void *t);
extern void __fastcall CDirDraw_DeleteSingleton(void);

void ShutdownGraphicsSystem_q(void)
{
    if (m_singleton) {
        CDirDraw_Destroy(m_singleton);
        CDirDraw_DeleteSingleton();
    }
}
