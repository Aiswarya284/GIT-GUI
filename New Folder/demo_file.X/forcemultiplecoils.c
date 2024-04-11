#include "testingdata.h"
unsigned int coil_byte_index,coil_byte_count, coil_byte_count,coil_byteValue,coil_bit_index,coil_register_index, coil_register_status;
WORD
forcemultiplecoils (WORD_VAL1 *COIL, BYTE *ModbusTcpTxBuf, WORD *DataRegister, parse1 *parse)
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

  ModbusTcpTxBuf[8] = parse->StartAddress.v[1];
  ModbusTcpTxBuf[9] = parse->StartAddress.v[0];

  ModbusTcpTxBuf[10] = parse->NumberofRegister.v[1];
  ModbusTcpTxBuf[11] = parse->NumberofRegister.v[0];
  
  coil_byte_index = 12;
  for (coil_byte_count = 0; coil_byte_count < parse->ByteCount ; coil_byte_count++)            //Iteration over each byte 
    {
      coil_byteValue = 0;
      for (coil_bit_index = 0; coil_bit_index < 8; coil_bit_index++)           //iteration over each bit
        {
          coil_register_index = coil_byte_count * 8 + coil_bit_index;          //index  of the current bit register
          coil_register_status = parse->ForceData.v[parse->StartAddress.Val + coil_register_index]; //status of the register
          coil_byteValue = (coil_register_status & 0x01) << coil_bit_index;
          parse->StartAddress.Val++;
          ModbusTcpTxBuf[coil_byte_index++] = coil_byteValue;
        }
    }

  //coil_count = (parse->StartAddress.v[0] + parse->NumberofRegister.v[0]);

  //for(i=0 ; i < parse->NumberofRegister.Val; i++){
  //   parse->ForceData.byte
  //COIL[parse->StartAddress.Val +i];
  //}
  //*COIL.Addr = parse->StartAddress.v[0];
  //*COIL.Val = parse->NumberofRegister.v[1];  
} 
