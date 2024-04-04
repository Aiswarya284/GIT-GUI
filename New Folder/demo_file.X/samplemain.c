/* 
 * File:   samplemain.c
 * Author: Vivek
 *
 * Created on 2 April, 2024, 9:20 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GenericTypeDefs_1.h"
#define testing

void deserialize(void);
#define	ReadHoldingRegister 03
unsigned int c,d,e;
BYTE Input[]= {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x03,0x08,0x09,0x09,0x08};
BYTE Output[25];

//unsigned int pack[25];
unsigned int a ,b, i, length;
WORD Register[25] = {0x0000,0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,0x0008,0x0009,0x0009,0x0008,0x0007,0x0007,0x0006,0x0005,0x0004,0x0003,0x0002,0x0001,0x0025,0x0035,0x0036,0x9957,0x7890};

typedef struct {
 WORD_VAL TransactionID;
 WORD_VAL ProtocolID;
 WORD Length;
 BYTE UnitID;
 BYTE FunctionCode;
 WORD_VAL StartAddress;
 WORD_VAL NumberofRegister;
}parse1;

parse1 parse;

main(){
    deserialize();
//    if(parse.FunctionCode == ReadHoldingRegister){
//        Output[7] = parse.FunctionCode ;
//        Output[8] = (char)(parse.NumberofRegister.Val * 2);
//        Output[4] = 0X0;
//        Output[5] = 0X3 + Output[8];
//      
//        for(a = 0;a<parse.NumberofRegister.Val;a++){
//            b = a*2;
//            Output[9+b]= Register[parse.StartAddress+a]/0x100;
//            Output[10+b]= Register[parse.StartAddress+a]%0x100;
//       }       
//    }    
//    length = sizeof(Output)/sizeof(Output[0]);
//    for(i=0;i< length;i++){
//    printf("%d",Output[i]);
//    }  
}
  
void deserialize (void){
      
    parse.TransactionID.v[1] = Input[0];
    parse.TransactionID.v[0] = Input[1];
    
    parse.ProtocolID.v[1] = Input[2];
    parse.ProtocolID.v[0] = Input[3];
    
    parse.Length = Input[5];
    
    parse.UnitID = Input[6];
    
    parse.FunctionCode = Input[7];
    
    parse.StartAddress.v[1] = Input[8];
    parse.StartAddress.v[0] = Input[9];
    
    parse.NumberofRegister.v[1] = Input[10];
    parse.NumberofRegister.v[0] = Input[11];   
}
