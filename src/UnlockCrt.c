/* probe v1: 55 8b 44 24 08 8b ec 8b 0c 85 a8 a0 51 00 51 ff 15 1c a6 58 00 5d c3
   push ebp/mov ebp,esp prolog despite 1 push-use of ebp; lock table indexed
   [imm32+eax*4]; IAT call after push ecx. */
#pragma optimize("y", off)
void (__stdcall *_lcsX)(void *a);   /* map __imp__lcsX@4=__imp__LeaveCriticalSection */
extern void *_locktableX[];         /* map __locktableX=__locktable */
void _unlock_q(int n)
{
    _lcsX(_locktableX[n]);
}
