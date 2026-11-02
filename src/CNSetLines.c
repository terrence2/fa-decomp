extern long cnLineA;   /* _buttonBoxes+0x108 */
extern long cnLineB;   /* _buttonBoxes+0x10c */

void CN_SetLines_q(unsigned long a, unsigned long b)
{
    cnLineA = a;
    cnLineB = b;
}
