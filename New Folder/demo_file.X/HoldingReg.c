#include "testingdata.h"
unsigned int a, b;
unsigned int bytes;
// ModbusTcpRxBuf
// ModbusTcpTxBuf
/*
 Parametes
 * ModbusPacketParser
 * 
 * 1.DataRegister
 * 2.ModbusTcpRxBuf - QUERY Buffer
 * 3.ModbusTcpTxBuf - Response Buffer
 * 
 * Return
 * No of bytes to send
 * Bit Test
 * 
 * 0000 1000
 * 0001 0000
 * ---------
 * 0000 0000
 * 
 * 0001 1000
 * 0001 0000
 * ---------
 * 0001 0000
 * 
 */




//parse->TransactionID.v[0] = *DataRegister;
//  parse->TransactionID.v[1] = *DataRegister++;

WORD
ReadHoldingRegisters (BYTE *ModbusTcpTxBuf, WORD *DataRegister, parse1 *parse)
{
  
   if((parse->StartAddress.Val > ((int)(DataRegistersize) - 1)) ||
        ((parse->StartAddress.Val - 1 + parse->NumberofRegister.Val) > (int)(DataRegistersize)))
    {
        modbuserror(parse, &ModbusTcpTxBuf[0],Illegal_Data_Address);
        return;
        
    }
  
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

  for (a = 0; a < parse->NumberofRegister.Val; a++)
    {
      b = a * 2;

      ModbusTcpTxBuf[9 + b] = DataRegister[parse->StartAddress.Val + a] / 0x100;
      ModbusTcpTxBuf[10 + b] = DataRegister[parse->StartAddress.Val + a] % 0x100;
    }
  
  bytes = 0x9 + ModbusTcpTxBuf[8];
  return bytes;
  //return &ModbusTcpTxBuf;
}

