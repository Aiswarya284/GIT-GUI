#include "testingdata.h"
#define bitcheck(byte,nbit) ((byte) &   (1<<(nbit)))
unsigned int e, byte_count, h, bit_index, register_index, byte_index, register_status;
unsigned char byteValue;

WORD
readcoilstatus (BYTE *ModbusTcpTxBuf, WORD *DataRegister, parse1 *parse)
{

  ModbusTcpTxBuf[0] = parse->TransactionID.v[1];
  ModbusTcpTxBuf[1] = parse->TransactionID.v[0];

  ModbusTcpTxBuf[2] = parse->ProtocolID.v[1];
  ModbusTcpTxBuf[3] = parse->ProtocolID.v[0];

  ModbusTcpTxBuf[4] = 0X0;
  ModbusTcpTxBuf[5] = parse->Length;
  // Output[5] = 0X3 + Output[8];
  ModbusTcpTxBuf[6] = parse->UnitID;
  ModbusTcpTxBuf[7] = parse->FunctionCode;

  ModbusTcpTxBuf[8] = e;
  e = ((parse->StartAddress.v[0] + parse->NumberofRegister.v[0]) + 0x7) / 0x8;
  byte_index = 9;
  for (byte_count = 0; byte_count < e; byte_count++)            //Iteration over each byte 
    {
      byteValue = 0;
      for (bit_index = 0; bit_index < 8; bit_index++)           //iteration over each bit
        {
          register_index = byte_count * 8 + bit_index;          //index  of the current bit register
          register_status = DataRegister[parse->StartAddress.Val + register_index]; //status of the register
          byteValue |= (register_status & 0x01) << bit_index;
          parse->StartAddress.Val++;
        }
      ModbusTcpTxBuf[byte_index++] = byteValue;
    }

  return 0x9 + ModbusTcpTxBuf[8];
//  return &ModbusTcpTxBuf;

}
