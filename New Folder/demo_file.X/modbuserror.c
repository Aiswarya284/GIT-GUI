#include "testingdata.h"
void modbuserror(parse1 *parse, BYTE *ModbusTcpTxBuf, unsigned char exceptioncode){
    ModbusTcpTxBuf[4]=0X00;
    ModbusTcpTxBuf[5]=0X03;
    ModbusTcpTxBuf[parse->FunctionCode]+=0X80;
    ModbusTcpTxBuf[8]= exceptioncode;
}
