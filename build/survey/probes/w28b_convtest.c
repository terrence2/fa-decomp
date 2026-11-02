void __thiscall w28b_tc(unsigned char x){}
void __pascal w28b_pas(unsigned char x){}
void __syscall w28b_sys(unsigned char x){}
void w28b_used_ref(unsigned char x){}
void w28b_caller(void){ w28b_used_ref(1); }
extern void __fastcall w28b_extern_fc(unsigned char x);
void w28b_calls_fc(void){ w28b_extern_fc(2); }
