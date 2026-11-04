/* w36E df830 - in-flag remapper, no relocs */
unsigned long w36e_df830(unsigned short f) {
    unsigned long r = 0;
    if (f & 0x1) r = 0x10;
    if (f & 0x4) r |= 0x8;
    if (f & 0x8) r |= 0x4;
    if (f & 0x10) r |= 0x2;
    if (f & 0x20) r |= 0x1;
    if (f & 0x2) r |= 0x80000;
    return r;
}
