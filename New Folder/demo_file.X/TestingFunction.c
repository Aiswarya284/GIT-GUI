#include "GenericTypeDefs_1.h"
unsigned int o,i;

void testingfun (BYTE *ModbusTcpTxBuf , BYTE *op1)
{
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
