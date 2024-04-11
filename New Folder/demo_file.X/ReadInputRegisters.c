#include "testingdata.h"
unsigned int c, d;
WORD ReadInputRegister(BYTE *ModbusTcpTxBuf, WORD *DataRegister, parse1 *parse){
  
  ModbusTcpTxBuf[0] = parse->TransactionID.v[1];
  ModbusTcpTxBuf[1] = parse->TransactionID.v[0];

  ModbusTcpTxBuf[2] = parse->ProtocolID.v[1];
  ModbusTcpTxBuf[3] = parse->ProtocolID.v[0];

  ModbusTcpTxBuf[4] = 0X0;
  ModbusTcpTxBuf[5] = parse->Length;
  // Output[5] = 0X3 + Output[8];
  ModbusTcpTxBuf[6] = parse->UnitID;
  ModbusTcpTxBuf[7] = parse->FunctionCode;
  ModbusTcpTxBuf[8] = (char)(parse->NumberofRegister.Val * 2);

  for (c = 0; c < parse->NumberofRegister.Val; c++)
    {
      d = c * 2;

      ModbusTcpTxBuf[9 + d] = DataRegister[parse->StartAddress.Val + c] / 0x100;
      ModbusTcpTxBuf[10 + d] = DataRegister[parse->StartAddress.Val + c] % 0x100;
    }
 
  return 0x9 + ModbusTcpTxBuf[8];
  //return &ModbusTcpTxBuf;
}
