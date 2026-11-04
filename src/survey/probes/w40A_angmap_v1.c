/* w40A_angmap_v1 — unnamed 0xe0a0 (80 B): piecewise 16-bit angle-to-pitch map */
int sub_e0a0(short arg)
{
    if (arg >= 0x3552)
        return (0x3ffc - arg) * 256 / 0xaaa;
    if (arg <= (short)0xcaae)
        return (arg + 0x3ffc) * 256 / 0xaaa;
    return 0x100;
}