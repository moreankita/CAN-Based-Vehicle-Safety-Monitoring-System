#include"types.h"

typedef struct CAN_FRAME
{
	u32 ID;
	struct Bitfield
	{
		u32 RTR:1;
		u32 DLC:4;
	}BFV;
	u32 Data1, Data2;
	//u8 Data[8];

}CANF;

void Init_CAN1(void);
void CAN1_Tx(CANF txF);
void CAN1_Rx(CANF *rxF);
void Init_CAN2(void);
void CAN2_Tx(CANF txF);
void CAN2_Rx(CANF *rxF);


