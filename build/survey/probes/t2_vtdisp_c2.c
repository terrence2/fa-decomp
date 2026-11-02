/* 40-case switch: document the ONLY jumptable form CL 4.2 emits from C
   (scale-4 sib `ff 24 .` into its own .rdata table) vs FA's handler tail
   `ff 24 5d <disp32>` (index ebx, scale 2, base-less disp32 = the
   vector_table global). Scale/index/stride/table-location are all
   compiler-fixed; no C type spelling changes them. */
extern void t2_h0(void);
void t2_dispatch_big(unsigned char op){
    switch(op){
    case 0: t2_h0(); break;
    case 1: t2_h0(); break;
    case 2: t2_h0(); break;
    case 3: t2_h0(); break;
    case 4: t2_h0(); break;
    case 5: t2_h0(); break;
    case 6: t2_h0(); break;
    case 7: t2_h0(); break;
    case 8: t2_h0(); break;
    case 9: t2_h0(); break;
    case 10: t2_h0(); break;
    case 11: t2_h0(); break;
    case 12: t2_h0(); break;
    case 13: t2_h0(); break;
    case 14: t2_h0(); break;
    case 15: t2_h0(); break;
    case 16: t2_h0(); break;
    case 17: t2_h0(); break;
    case 18: t2_h0(); break;
    case 19: t2_h0(); break;
    case 20: t2_h0(); break;
    case 21: t2_h0(); break;
    case 22: t2_h0(); break;
    case 23: t2_h0(); break;
    case 24: t2_h0(); break;
    case 25: t2_h0(); break;
    case 26: t2_h0(); break;
    case 27: t2_h0(); break;
    case 28: t2_h0(); break;
    case 29: t2_h0(); break;
    case 30: t2_h0(); break;
    case 31: t2_h0(); break;
    case 32: t2_h0(); break;
    case 33: t2_h0(); break;
    case 34: t2_h0(); break;
    case 35: t2_h0(); break;
    case 36: t2_h0(); break;
    case 37: t2_h0(); break;
    case 38: t2_h0(); break;
    case 39: t2_h0(); break;
    }
}
