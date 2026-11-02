/* socket_set_state - FA rva 0xa3140 (667968) - EXACT probe verdict, tier1_a_r2.json entry 'SocketSetState_v1'
 * Form: patch-hybrid
 * Levers: 3 1-byte patches; tail-jmp chunk via alias anchor
 * Maps: @socketSetStateTail@0=$FA$_t_4a31e0
 * patch 0x1: ->44
 * patch 0x5: ->4c
 * patch 0x9: ->41
 * Probes: v1
 */
extern void __fastcall socketSetStateTail(void);

void socket_set_state(void *st, int s)
{
    *(int *)((char *)st + 0x10) = s;
    socketSetStateTail();
}
