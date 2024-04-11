#include "GenericTypeDefs_1.h"
unsigned int o,i,m;

void testingfun (BYTE *ModbusTcpTxBuf,BYTE *op1, BYTE *ModbusTcpRxBuf,WORD *DataRegister)
{
  op1[0] = ModbusTcpRxBuf[0];
  op1[1] = ModbusTcpRxBuf[1];
  op1[2] = ModbusTcpRxBuf[2];
  op1[3] = ModbusTcpRxBuf[3];
  op1[4] = ModbusTcpRxBuf[4];
  op1[5] = ModbusTcpRxBuf[5];
  op1[6] = ModbusTcpRxBuf[6];
  op1[7] = ModbusTcpRxBuf[7];
  op1[8] = (char)(ModbusTcpRxBuf[11]*2);
  m = ModbusTcpRxBuf[9];
  
  
  
  for (o = 0; o <ModbusTcpRxBuf[11]; o++)
    {
      i = o * 2;

      op1[9 + i] = DataRegister[m + o] / 0x100;
      op1[10 + i] = DataRegister[m + o] % 0x100;
    }
  
  
  for (i = 0; i<sizeof (op1); i++)
    {
      if (ModbusTcpTxBuf[i] != op1[i])
        {
          o = 9;

        }
      break;
    }

  o = 10;
}
