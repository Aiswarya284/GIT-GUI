/* 
 * File:   newmain1.c
 * Author: Vivek
 *
 * Created on 4 April, 2024, 4:33 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GenericTypeDefs_1.h"

void deserialize(void);
#define ReadHoldingRegister 03
unsigned int a, b, i, length;
BYTE Input[] = {0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0003, 0x0008, 0x0009, 0x0009, 0x0008};
BYTE Output[25];
WORD Register[25] = {0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x0009, 0x0008, 0x0007, 0x0007, 0x0006, 0x0005, 0x0004, 0x0003, 0x0002, 0x0001, 0x0025, 0x0035, 0x0036, 0x9957, 0x7890};

typedef struct {
    WORD_VAL TransactionID;
    WORD_VAL ProtocolID;
    WORD Length;
    BYTE UnitID;
    BYTE FunctionCode;
    WORD_VAL StartAddress;
    WORD_VAL NumberofRegister;
} parse1;

parse1 parse;

int main() {
    deserialize();
    if (parse.FunctionCode == ReadHoldingRegister) {
        Output[7] = parse.FunctionCode;
        Output[8] = (char)(parse.NumberofRegister.Val * 2);
        Output[4] = 0x0;
        Output[5] = 0x3 + (Output[8] * 2); // Corrected calculation for Output[5]

        for (a = 0; a < parse.NumberofRegister.Val; a++) {
            b = a * 2;
            Output[9 + b] = Register[parse.StartAddress.Val + a] >> 8; // High byte
            Output[10 + b] = Register[parse.StartAddress.Val + a] & 0xFF; // Low byte
        }
    }
    return 0;
}

void deserialize(void) {
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

