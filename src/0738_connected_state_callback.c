// ?connected_state_callback@@YAXPAXW4NET_CONNECTED_STATE@@@Z @ rva 0x92040
//   (16 B) — FA asm: 8b 44 24 08 (arg2 = the NET_CONNECTED_STATE value)/
//   a3 <?connected_state_flag@@3W4NET_CONNECTED_STATE@@C> (a3 moffs store)/
//   c3.  Plain C exact (mov eax,[esp+8] then a3 into eax-resident store).
//   Probe build/w4probe/w19_connstate_v1.obj — exact.
extern long connStateFlag;   /* ?connected_state_flag@@3W4NET_CONNECTED_STATE@@C */

void ConnectedStateCb_f(void *p, long st)
{
    connStateFlag = st;
}