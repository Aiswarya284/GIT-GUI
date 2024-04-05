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
#define size 12
#define testing

#ifdef testing
#include "testingdata.h"
#endif
void deserialize (void);
void testingfun (void);
#define	ReadHoldingRegister 03
unsigned int c, d, e;
unsigned int o = 1;
unsigned int i;
BYTE Output[12];
BYTE op1[12] = {0x0, 0x1, 0x2, 0x3, 0x0, 0x5, 0x6, 0x3, 0x4, 0x0, 0x5, 0x0, 0x6};

//unsigned int pack[25];

unsigned int a, b, i, length;
unsigned int y;
extern int z1, l, value;
//l=value;
WORD Register[25] = {0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x0009, 0x0008, 0x0007, 0x0007, 0x0006, 0x0005, 0x0004, 0x0003, 0x0002, 0x0001, 0x0025, 0x0035, 0x0036, 0x9957, 0x7890};

typedef struct
{
  WORD_VAL TransactionID;
  WORD_VAL ProtocolID;
  WORD Length;
  BYTE UnitID;
  BYTE FunctionCode;
  WORD_VAL StartAddress;
  WORD_VAL NumberofRegister;
} parse1;

parse1 parse;

main ()
{
  //z1[0] = 110 ;
  //printf ("%d", Output[i]);cc
  deserialize ();

  if (parse.FunctionCode == ReadHoldingRegister)
    {
      Output[0] = parse.TransactionID.v[1];
      Output[1] = parse.TransactionID.v[0];

      Output[2] = parse.ProtocolID.v[1];
      Output[3] = parse.ProtocolID.v[0];

      Output[4] = 0X0;
      Output[5] = parse.Length;
      // Output[5] = 0X3 + Output[8];
      Output[6] = parse.UnitID;
      Output[7] = parse.FunctionCode;
      Output[8] = (char) (parse.NumberofRegister.Val * 2);

      for (a = 0; a < parse.NumberofRegister.Val; a++)
        {
          b = a * 2;

          Output[9 + b] = Register[parse.StartAddress.Val + a] / 0x100;
          Output[10 + b] = Register[parse.StartAddress.Val + a] % 0x100;
        }
    }

  length = sizeof (Output) / sizeof (Output[0]);
  for (i = 0; i < length; i++)
    {
      printf ("%d", Output[i]);
    }
  testingfun ();
  while (1)
    {



    }
}

void
deserialize (void)
{

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

void
testingfun (void)
{
  for (i = 0; i<sizeof (op1); i++)
    {

      if (Output[i] != op1[i])
        {
          o = 9;

        }
      break;
    }
  
  o = 10;
}