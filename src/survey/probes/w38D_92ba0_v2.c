/* @GetPOV@0 rva 0x92ba0, 144 B (129 code + 15 B deco tail 8d 64 24 00 x2 + 8d a4 24 00 00 00 00, c3 at 0x80).
 * FA: push ebx,esi; mov bl,jok; test; mov bl,funcs; test bl,0x10; push ebx(pov);
 * call _ReadDevice; mov val=eax? no: mov [esi],? — actually val home esi;
 * val = jix[pov*13+0] (delta 0x28 base); val==0xffff -> xor esi; else t=val/100:
 * t<=0x2d b0 48; t<=0x87 b0 4d; t<=0xe1 b0 50; else cmp t,0x13b jle 4b else 48.
 * v2: r has NO initializer — CL then uses eax plan like FA (no esi hoist). */
extern char joysticksInitialized;
extern unsigned long joystickFunctions;
extern unsigned long joystickPOVDevice;
extern unsigned long ReadDevice(unsigned long);
extern long w38d_jixX[];

int __fastcall GetPOV(void)
{
    long val, t, r;

    if (!joysticksInitialized)
        return 0;
    if (!(joystickFunctions & 0x10))
        return 0;
    val = ReadDevice(joystickPOVDevice);
    val = w38d_jixX[joystickPOVDevice * 13];
    if (val == 0xffff)
        return 0;
    t = val / 100;
    if (t <= 0x2d)
        return 0x48;
    if (t <= 0x87)
        return 0x4d;
    if (t <= 0xe1)
        return 0x50;
    r = 0x4b;
    if (t > 0x13b)
        r = 0x48;
    return r;
}