// ?FreeVDOLinkNode@@YAXPAUVDOLinkedList@@@Z @ rva 0xac060 (48 B) — frees
//   node->[0] and node->[4] when non-NULL, then the node itself, via
//   VDOFree (cdecl 1 arg, caller add esp,4). Plain C should reach FA's
//   esi-node/eax-value plan.
extern void __cdecl VDOFree(void *p);

void __cdecl FreeVDOLinkNode(void *node)
{
    void *a = *(void **)node;
    if (a != 0)
        VDOFree(a);
    a = *((void **)node + 1);
    if (a != 0)
        VDOFree(a);
    VDOFree(node);
}