/* do_collision_info @ rva 0xd0608 (112 B, gap chunk, no FPO) -- the interp
 * do-handler CORE: fragments shared by do_setlight/do_setcoarse et al.
 *   entry 0x00: esi cursor walk: read uword [esi], esi+=2, movzx ebx,al,
 *     then tail dispatch jmp dword ptr [ebp*4 + vector_table] (sib-5d; the
 *     caller's ebp carries the table word index).
 *   core 0x14 (called by do_setlight as do_collision_info+0x14): merge the
 *     per-effect mask: eax &= ebx (clamped mask staged in ebx), retain only
 *     bits allowed in _effectsAllowed, clear the disallowed bits in _effects
 *     (not ebx; effects stored via a3 moffs), then ret.
 *   entry 0x2e: collision-info fetch: ax = [esi], esi += 2; if ax==2 answer
 *     depends on _nightHazing (byte flag): zero -> eax=-1... (FA byte test at
 *     0x3e: cmp byte,0 / je / xor eax,eax / jmp); nonzero tail -> or ax,ax
 *     zero-eax else eax=-1; call core 0x14 with ebx=0x10 slot mask.
 *   entry 0x5d: same cursor walk + movzx ebx,al + jmp [ebp*4+vector_table].
 * Whole-body transplant: husk documents the register-state protocol
 * (esi = interp data cursor, ebp = vector_table row, ebx = cmd/width);
 * FA bytes are authoritative and CL 4.2 could not reproduce the sib-5d
 * jump-table dispatches (VM-dispatch wall). */
long do_collision_info(long cmd);
long do_collision_info(long cmd) { return 0; }