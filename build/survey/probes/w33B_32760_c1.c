/* w33B_32760_c1.c -- ?ScoreOn@@YIXPAXD@Z fastcall setter */
extern void __fastcall w33b_scoreoff(void);
extern unsigned long w33b_scorestart;
extern unsigned long w33b_scoreoffset;
extern unsigned char w33b_scoreishandle;
extern unsigned char w33b_scoreprefix;
extern unsigned char w33b_scoreneedcheck;
extern char w33b_muon;

void __fastcall w33b_scoreon(void *start, char ishandle)
{
    if (w33b_muon)
    {
        w33b_scoreoff();
        w33b_scoreishandle = ishandle;
        w33b_scorestart = (unsigned long)start;
        w33b_scoreoffset = 0;
        w33b_scoreprefix = 0;
        w33b_scoreneedcheck = 0;
    }
}