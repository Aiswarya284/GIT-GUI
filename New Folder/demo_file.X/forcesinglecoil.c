#include "testingdata.h"

WORD forcesinglecoil(WORD_VAL1 COIL, BYTE *ModbusTcpTxBuf, WORD *DataRegister, parse1 *parse){
  
  ModbusTcpTxBuf[0] = parse->TransactionID.v[1];
  ModbusTcpTxBuf[1] = parse->TransactionID.v[0];

  ModbusTcpTxBuf[2] = parse->ProtocolID.v[1];
  ModbusTcpTxBuf[3] = parse->ProtocolID.v[0];

  ModbusTcpTxBuf[4] = 0X0;
  ModbusTcpTxBuf[5] = parse->Length;
  // Output[5] = 0X3 + Output[8];
  ModbusTcpTxBuf[6] = parse->UnitID;
  ModbusTcpTxBuf[7] = parse->FunctionCode;
 
  ModbusTcpTxBuf[8] = parse->StartAddress.v[1];
  ModbusTcpTxBuf[9] = parse->StartAddress.v[0];

  ModbusTcpTxBuf[10] = parse->NumberofRegister.v[1];
  ModbusTcpTxBuf[11] = parse->NumberofRegister.v[0];
  
  COIL.Addr = parse->StartAddress.v[0];
  COIL.Val = parse->NumberofRegister.v[1];

  return 0x6 + ModbusTcpTxBuf[5];
  //return &ModbusTcpTxBuf;
}
