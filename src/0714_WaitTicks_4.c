/* @WaitTicks@4 @ rva 0x85b5a (dec 547674), size 0x29 — EXACT, C + 7 patches.
 *
 * C recipe: void __fastcall tail-call with a volatile local t.
 *   - CL tail-merges a plain void __fastcall tail call (call becomes jmp)
 *     — the volatile t slot defeats the merge and recovers FA's sub esp,8
 *     + reload shape.
 *   - Un-C-formable leftovers, all patched (provenance "toolchain-diff"):
 *     FA's full-ebp prologue (push ebp/mov ebp,esp = ILINK parent-sourced
 *     frame, CL keeps FPO form); the callee-saved pushes; FA's param d
 *     spilled at entry to [ebp-8] (CL keeps d in ecx, computing
 *     add ecx,eax vs FA's add eax,[ebp-8]); the [ebp-4]/[ebp-8] slot
 *     addressing of the volatile t slot; and FA's 5-byte e9+0 self-jmp
 *     between the call and the epilogue (content 0, literal — REL32 to
 *     field+4, no .reloc entry).
 *
 * Source (w24a_WaitTicks_v3.c):
 *   extern int __fastcall WaitUntil(unsigned long t);
 *   extern unsigned long timerTicks;
 *   void __fastcall WaitTicks(volatile int d)
 *   {
 *       volatile int t = timerTicks + d;
 *       WaitUntil(t);
 *   }
 *
 * patch provenance (all: toolchain-diff — FA ILINK frame / spill / self-jmp
 * artifacts not formable by CL 4.2 C):
 *   patch 0x0 (prologue): toolchain-diff — insert push ebp/mov ebp,esp (ILINK
 *     parent frame; CL stays FPO)
 *   patch 0x6 (frame): toolchain-diff — insert push ebx/esi/edi + mov
 *     [ebp-8],ecx d-spill (param spill CL never emits)
 *   patch 0x11 (add): toolchain-diff — add eax,[ebp-8] form (CL emits
 *     add ecx,eax register add)
 *   patch 0x14/0x17 (t slot): toolchain-diff — ebp-relative [ebp-4] slots
 *     (CL's [esp+4])
 *   patch 0x1f (tail jle... e9): toolchain-diff — insert FA's e9+0 self-jmp
 *     after the call (ILINK artifact, literal content 0)
 *   patch 0x24 (epilogue): toolchain-diff — pop edi/esi/ebx + leave + ret
 *     (CL's bare ret)
 *
 * fitobj: python3 tools/fitobj.py build/survey/probes/w24a_WaitTicks_v3.obj 547674 \
 *   --patch '0,0,558bec' --patch '6,0,535657894df8' --patch '17,2,0345f8' \
 *   --patch '20,4,8945fc' --patch '23,4,8b4dfc' --patch '31,3,e900000000' \
 *   --patch '36,1,5f5e5bc9c3' --map '@WaitUntil@4=?WaitUntil@@YIXK@Z' \
 *   build/survey/probes/w24a_WaitTicks_v3_fit.obj
 * (2 relocs auto-shifted to FA's sites 0xd (abs _timerTicks) and 0x1b
 * (rel call); code = full chunk extent 0x29, no tail.)
 */
extern int __fastcall WaitUntil(unsigned long t);
extern unsigned long timerTicks;
void __fastcall WaitTicks(volatile int d)
{
    volatile int t = timerTicks + d;
    WaitUntil(t);
}
