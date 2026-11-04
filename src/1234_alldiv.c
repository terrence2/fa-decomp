/* w45F __alldiv @ 0x4d4c90 (176 B, gap chunk, CRT asm via CL macro-asm era)
 * — v1 husk for full-body transplant: no .reloc'd dwords (the only control
 * flow is an internal eb-rel8 @0x57); signed 64/64 division with 3-neg
 * sign handling, shift-normalized unsigned core, mul-based remainder fixup
 * (dec esi on over/under), sbb carry on the negated result.
 * C ident _alldiv emits __alldiv — identity with the FA public. */
void _alldiv(void)
{
    return;
}