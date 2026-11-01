// ?_query_new_handler@@YAP6AHI@ZXZ @ rva 0xdf5c0 — return the new-handler ref
typedef int (__cdecl *PNH_q)(int, unsigned);
extern PNH_q newHandlerRef;
PNH_q query_new_handler_q(void)
{
    return newHandlerRef;
}
