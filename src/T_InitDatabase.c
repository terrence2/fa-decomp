/* _T_InitDatabase@0 @ rva 0xc20e0 */
extern void __stdcall T_ShutdownDatabase(void);
extern char *dbDynamicLow;
extern char *dbDynamicHigh;
extern unsigned char dbaseLow[];

void __stdcall T_InitDatabase(void)
{
    T_ShutdownDatabase();
    dbDynamicLow = (char *)dbaseLow;
    dbDynamicHigh = (char *)dbaseLow + 0x2710;
}