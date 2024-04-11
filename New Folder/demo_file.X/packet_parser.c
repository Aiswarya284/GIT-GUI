#include "testingdata.h"
unsigned int c2, d2, bytesrx;
unsigned char exceptioncode;
WORD deserialize (parse1 *parse, BYTE *ModbusTcpRxBuf)
{
  parse->TransactionID.v[1] = ModbusTcpRxBuf[0];
  parse->TransactionID.v[0] = ModbusTcpRxBuf[1];
  parse->ProtocolID.v[1] = ModbusTcpRxBuf[2];
  parse->ProtocolID.v[0] = ModbusTcpRxBuf[3];
  parse->Length = ModbusTcpRxBuf[5];
  parse->UnitID = ModbusTcpRxBuf[6];
  parse->FunctionCode = ModbusTcpRxBuf[7];
  parse->StartAddress.v[1] = ModbusTcpRxBuf[8];
  parse->StartAddress.v[0] = ModbusTcpRxBuf[9];
  parse->NumberofRegister.v[1] = ModbusTcpRxBuf[10];
  parse->NumberofRegister.v[0] = ModbusTcpRxBuf[11];

  if (!(parse->FunctionCode == ReadCoilStatus ||
        parse->FunctionCode == ReadInputStatus ||
        parse->FunctionCode == ReadHoldingRegister ||
        parse->FunctionCode == ReadInputRegisters ||
        parse->FunctionCode == ForceSingleCoil ||
        parse->FunctionCode == PresetSingleRegister ||
        parse->FunctionCode == ForceMultipleCoils ||
        parse->FunctionCode == PresetMultipleRegisters
        ))
    {

//      modbuserror(&parse, &ModbusTcpTxBuf,exceptioncode);
      

    }
  

  if (parse->FunctionCode == 15) //force multiple coils
    {
      parse->ByteCount = ModbusTcpRxBuf[12];

      for (c2 = 0; c2 < parse->ByteCount; c2++)
        {
          d2 = c2 * 2;

          parse->ForceData.v[1 + c2] = ModbusTcpRxBuf[13 + d2];
          parse->ForceData.v[0 + c2] = ModbusTcpRxBuf[14 + d2];
        }
    }
  
// if(parse->FunctionCode == ){}
  
  
  bytesrx = 0x6 + parse->Length;
  return bytesrx;
  //  if (parse->FunctionCode == 16){           //Preset multiple register
  //      
  //    }
}

