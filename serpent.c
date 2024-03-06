// headers that have been used in the project
#include <stdio.h>  // for reading from stdin and writing to stdout
#include <stdlib.h> // for managing memory allocation
#include <string.h> //
#include <stdint.h> //
#include <string.h>
#include <limits.h> // Include for CHAR_BIT
#include "Sbox.h"

// defines
#define ROTL(x, y) (((x) << (y)) | ((x) >> (32 - (y)))) // ROTL Bits Macro
#define FRAC 0x9e3779b9                                 //  fractional part of the golden ratio(make the cipher safer)
#define MAX_KEY_LENGTH 32                               // maximum key length

/*
 key padding is the first part of the cipher and it is done to make sure that the key
 is the correct size match the functions
 return the length of the padded key, always 32 bytes
*/
int Key_Padding(const unsigned char *key, unsigned int keyLength, unsigned char *paddedKey)
{
    // Initialize the padded key buffer
    memset(paddedKey, 0, MAX_KEY_LENGTH);
    // In case the original key length is less than 32 byte
    if (keyLength < MAX_KEY_LENGTH)
    {
        // copy the original key to the padded key
        memcpy(paddedKey, key, keyLength);
        // add the padding byte after the original key
        // 0x80 in hexadecimal represents 1000 0000 in binary, which corresponds to this pattern
        // of the padding
        paddedKey[keyLength] = 0x01;
    }
    else
    {
        // copy the original key to the padded key
        memcpy(paddedKey, key, MAX_KEY_LENGTH);
    }
    return MAX_KEY_LENGTH; // always 32
}

// key schedule is the second part of the cipher and it is done in order to
//  make sure the encryption is more efficient instead of calculating
// the round keys (will be done in all the 32 round and would cost alot more).
void Get_Prekeys(uint32_t *key, uint32_t *prekeys)
{
    // According to the Serpent specification, the first 8 prekeys are directly copied from the padded key
    for (int i = 0; i < 8; ++i)
    {
        prekeys[i] = key[i];
    }

    // Generate the remaining prekeys, using the recursion formula specified by the Serpent algorithm
    for (int i = 8; i < 140; ++i)
    {
        uint32_t temp = ROTL(prekeys[i - 8] ^ prekeys[i - 5] ^ prekeys[i - 3] ^ prekeys[i - 1] ^ FRAC ^ (i - 8), 11);
        prekeys[i] = temp;
    }
}

void Get_Subkeys(uint32_t *key, uint32_t *subkeys[])
{
    uint8_t p, s;

    for (int i = 0; i < 33; i++)
    {
        p = (32 + 3 - i) % 32;
        for (int k = 0; k < 32; k++)
        {
            s = S[p % 8][((key[4 * i + 0] >> k) & 0x1) << 0 |
                         ((key[4 * i + 1] >> k) & 0x1) << 1 |
                         ((key[4 * i + 2] >> k) & 0x1) << 2 |
                         ((key[4 * i + 3] >> k) & 0x1) << 3];
            for (int j = 0; j < 4; j++)
            {
                subkeys[i][j] |= ((s >> j) & 0x1) << k;
            }
        }
    }
}

void Key_Scedule(uint32_t subkeysHat[33][4],
                 const unsigned char *key,
                 unsigned char *output,
                 uint32_t nBytes)
{
    // 33 subkeys * 32bits * 4 blocks
    uint32_t subkeys[33][4] = {0};
    uint32_t prekey[140] = {0};

    // memory precheck
    // the program will not work if the pointer to the ciphered text
    // is NULL
    if (output == NULL)
    {
        fprintf(stderr, "Given output char pointer not initialized/allocated.\n");
        exit(EXIT_FAILURE);
    }

    unsigned char paddedKey[MAX_KEY_LENGTH] = {0}; // Allocate on the stack to avoid manual memory management

    // check if the key padding is needed for this length of key
    if (nBytes != 32)
    {
        Key_Padding(key, nBytes, paddedKey);
    }
    else
    {
        memcpy(paddedKey, key, MAX_KEY_LENGTH);
    }
    // make a casting to a number in order to make mathematical operations
    uint32_t *paddedKeyInt = (uint32_t *)paddedKey;
    Get_Prekeys(paddedKeyInt, prekey);
    Get_Subkeys(prekey, subkeys);
}
