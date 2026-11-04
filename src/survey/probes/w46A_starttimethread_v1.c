/* rva 0x84fa0 (?StartTimeThread@@YAKPAK@Z 544672). Spin-wait thread: GetCurrentThread/SetThreadPriority/timeGetTime via IAT dwords (offs 13/20/26/103); 16-bit bx countdown, edi palette refresh, shake vectors _hShakeTicks/_vShakeTicks, Sleep(!noTimerSleep). Transplant: 8 DIR32 newsites.. */
int w46a_stt_stub(void) { return 0; }
