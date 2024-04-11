//unsigned int c, d, e;

//unsigned int pack[25];
//unsigned int y;
//extern int z1, l, value;
//l=value;
#include "GenericTypeDefs_1.h"

#define ReadCoilStatus 01
#define ReadInputStatus 02
#define	ReadHoldingRegister 03
#define ReadInputRegisters 04
#define ForceSingleCoil 05
#define PresetSingleRegister 06
#define ForceMultipleCoils 15
#define PresetMultipleRegisters 16
#define DataRegistersize 25

#define Illegal_Function_Code   0x01u       
#define Illegal_Data_Address    0x02u
#define Illegal_Data_Value      0x03u

typedef struct
{
  WORD_VAL TransactionID;
  WORD_VAL ProtocolID;
  WORD Length;
  BYTE UnitID;
  BYTE FunctionCode;
  WORD_VAL StartAddress;
  WORD_VAL NumberofRegister;
  WORD ByteCount;
  WORD_VAL ForceData ;
} parse1;

typedef struct
{
    BYTE Val;
    BYTE Addr;
  
} WORD_VAL1, WORD_BITS1;

void modbuserror(parse1*parse, BYTE *ModbusTcpTxBuf, unsigned char exceptioncode);



