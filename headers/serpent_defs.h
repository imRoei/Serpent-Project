#ifndef MY_DEFINES_H
#define MY_DEFINES_H

// defines file inorder to avoid compiler warnings and to reduce the number of
// lines that are written in every file

// includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <string.h>

// defines
#define ROTL(x, y) (((x) << (y)) | ((x) >> (32 - (y)))) // ROTL Bits Macro
#define FRAC 0x9e3779b9                                 //  fractional part of the golden ratio(make the cipher safer)
#define MAX_KEY_LENGTH 32                               // maximum key length
#define BITS_PER_NIBBLE 4
#define BITS_PER_BLOCK 128
#define BITS_PER_WORD 32
#define WORDS_PER_BLOCK 4
#define NIBBLES_PER_WORD 8
#define MARKER 0xff

typedef unsigned int WORD;
typedef unsigned char BIT;
typedef unsigned char NIBBLE;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned char uchar;
typedef WORD BLOCK[WORDS_PER_BLOCK];
typedef uint _128[4];

extern uint SBox[32][16];
extern uint SBoxInverse[32][16];
extern uint LTTable[128][8];
extern uint LTTableInverse[128][8];

#endif