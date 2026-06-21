#include"types.h"

#ifndef _DS18B20_H_

#define _DS18B20_H_


/**DS18B20 FUNCTION DECLARATION**/

u8 ResetDS18b20(void);

u8 ReadBit(void);

void WriteBit(u8);

u8 ReadByte(void);

void WriteByte(u8);

int ReadTemp(void);


#endif

