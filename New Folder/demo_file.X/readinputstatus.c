#include "testingdata.h"
unsigned int no_of_bytes1;
unsigned int e1, byte_count1, bit_index1, register_index1, byte_index1, register_status1;
unsigned char byteValue1;

WORD                                        
readinputstatus(BYTE *ModbusTcpTxBuf, WORD *DataRegister, parse1 *parse) //Reads the ON/OFF status of discrete inputs in the slave
{
  *ModbusTcpTxBuf = parse->TransactionID.v[1];
  *(ModbusTcpTxBuf+1) = parse->TransactionID.v[0];

  *(ModbusTcpTxBuf+2) = parse->ProtocolID.v[1];
  *(ModbusTcpTxBuf+3) = parse->ProtocolID.v[0];

  *(ModbusTcpTxBuf+4) = 0X0;
  *(ModbusTcpTxBuf+5) = parse->Length;
  // Output[5] = 0X3 + Output[8];
  *(ModbusTcpTxBuf+6) = parse->UnitID;
  *(ModbusTcpTxBuf+7) = parse->FunctionCode;

  *(ModbusTcpTxBuf+8) = e1;
  e1 = ((parse->StartAddress.v[0] + parse->NumberofRegister.v[0]) + 0x7) / 0x8;
  byte_index1 = 9;
  for (byte_count1 = 0; byte_count1 < e1; byte_count1++)            //Iteration over each byte 
    {
      byteValue1 = 0;
      for (bit_index1 = 0; bit_index1 < 8; bit_index1++)           //iteration over each bit
        {
          register_index1 = byte_count1 * 8 + bit_index1;          //index  of the current bit register
          register_status1 = DataRegister[parse->StartAddress.Val + register_index1]; //status of the register
          byteValue1 |= (register_status1 & 0x01) << bit_index1;
          parse->StartAddress.Val++;
        }
      *(ModbusTcpTxBuf+byte_index1++) = byteValue1;
    }
  
  no_of_bytes1 = 0x9 + *(ModbusTcpTxBuf+8);
  return no_of_bytes1;
}
