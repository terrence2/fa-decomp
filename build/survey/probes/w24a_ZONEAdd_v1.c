typedef struct { char b[46]; } ZREC;
extern unsigned char cobraData_x[];

void __stdcall ZONEAdd(void *src)
{
    if (*(short *)(cobraData_x + 0xc1c0) < 6) {
        *(ZREC *)((char *)cobraData_x + 0xc1c8 + 46 * *(short *)(cobraData_x + 0xc1c0))
            = *(ZREC *)src;
        (*(short *)(cobraData_x + 0xc1c0))++;
    }
}
