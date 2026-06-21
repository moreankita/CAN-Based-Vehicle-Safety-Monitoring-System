#include"types.h"
void WriteLCD(u8 data);
void CmdLCD(u8 cmd);
void charLCD(u8 ascii);
void InitLCD(void);
void strLCD(s8 *p);
void u32LCD(u32 n);
void s32LCD(s32 n);
void f32LCD(f32 fnum, u8 nDP);
void HexLCD(u32 n);
void OctLCD(u32 n);
void BinLCD(u32 n, u8 nbd);
void BuildCGRAM(u8 *p, u8 nb);

