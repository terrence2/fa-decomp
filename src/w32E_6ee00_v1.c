extern char w32e_mns;
extern void w32e_next(void);

void w32e_6ee00_v1(void)
{
    if (!w32e_mns) {
        w32e_mns = 1;
        w32e_next();
    }
}