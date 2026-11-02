// 0x1dff0 = 122864, unnamed gap, 16 B (12 code + 8d642400 pad)
// FA asm: push esi / mov esi,ecx / call ?ddECS@CDirDraw@@SAXXZ (cdecl static)
// / mov eax,esi / pop esi / ret  — thiscall-shaped: reads the incoming ECX,
// calls the void(void) helper, returns the original ECX.  C cannot read the
// incoming ecx -> naked asm escape.
extern void DDECS_c(void);
/* map _DDECS_c=?ddECS@CDirDraw@@SAXXZ */

__declspec(naked) void * __fastcall w25c_ddECSGet_q(void)
{
    __asm {
        push esi
        mov esi, ecx
        call DDECS_c
        mov eax, esi
        pop esi
        ret
    }
}