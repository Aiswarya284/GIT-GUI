/* 
 * File:   main.c
 * Author: Vivek
 *
 * Created on 8 April, 2024, 11:03 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "GenericTypeDefs_1.h"
#include "testingdata.h"

//WORD DataRegister[25];


WORD_VAL1 COIL[500];


WORD deserialize (parse1 *parse,BYTE *ModbusTcpRxBuf);
WORD ReadHoldingRegisters(BYTE *ModbusTcpTxBuf, WORD *DataRegister, parse1 *parse);
WORD ReadInputRegister(BYTE *ModbusTcpTxBuf, WORD *DataRegister, parse1 *parse);
WORD presetsingleregister(BYTE *ModbusTcpTxBuf, WORD *DataRegister, parse1 *parse);
WORD forcesinglecoil(WORD_VAL1 *COIL, BYTE *ModbusTcpTxBuf, WORD *DataRegister, parse1 *parse);
WORD readcoilstatus(BYTE *ModbusTcpTxBuf,WORD *DataRegister,parse1 *parse);
WORD readinputstatus(BYTE *ModbusTcpTxBuf, WORD *DataRegister, parse1 *parse);
WORD testingfun (BYTE *ModbusTcpTxBuf , BYTE *op1);
void modbuserror(parse1 *parse,BYTE *ModbusTcpTxBuf, unsigned char exceptioncode);


parse1 parse;
WORD no_of_bytes,ModbusTxLength;
BYTE ModbusTcpTxBuf[25];
BYTE ModbusTcpRxBuf[25] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x03, 0x27, 0x05, 0x00, 0x02, 0x01, 0x03, 0x03};
BYTE op1[15] = {0x0, 0x1, 0x2, 0x3, 0x0, 0x5, 0x6, 0x3, 0x4, 0x0, 0x5, 0x0, 0x6};
WORD DataRegister[26] = {0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x0009, 0x0008, 0x0007, 0x0007, 0x0006, 0x0005, 0x0004, 0x0003, 0x0002, 0x0001, 0x0025, 0x0035, 0x0036, 0x9957, 0x7890};

main ()
{
  ModbusTxLength = deserialize(&parse,&ModbusTcpRxBuf[0]);
  
  switch(parse.FunctionCode){
    
    case ReadHoldingRegister:                      //Reads the binary contents of holding registers (4X references) in the slave
     ModbusTxLength = ReadHoldingRegisters (&ModbusTcpTxBuf[0],&DataRegister[0],&parse);
     break;

    case ReadInputRegisters:                          //Reads the binary contents of input registers (3X references) in the slave.
     ReadInputRegister(&ModbusTcpTxBuf[0],&DataRegister[0],&parse);
     break;
    
    case PresetSingleRegister:
      presetsingleregister(&ModbusTcpTxBuf[0],&DataRegister[0],&parse);
      break;
      
    case ForceSingleCoil:
      forcesinglecoil(&COIL[0], &ModbusTcpTxBuf[0],&DataRegister[0],&parse);
      break;
      
    case ReadCoilStatus:
      readcoilstatus(&ModbusTcpTxBuf[0],&DataRegister[0],&parse);
      break;
    
    case ReadInputStatus:
      readinputstatus(&ModbusTcpTxBuf[0],&DataRegister[0],&parse);
      break;
    
    default:
      modbuserror(&parse,&ModbusTcpTxBuf[0],Illegal_Function_Code);
   
    }
   testingfun(&ModbusTcpTxBuf[0] ,&op1[0]);
}
