// headers that have been used in the project
#include <stdio.h>  // for reading from stdin and writing to stdout
#include <stdlib.h> // for managing memory allocation
#include <string.h> //
#include <stdint.h> //
#include <string.h>

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

void Get_Subkeys(const uint32_t *key, uint32_t subkeysHat[33][4])
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
                subkeysHat[i][j] |= ((s >> j) & 0x1) << k;
            }
        }
    }
}

void Key_Schedule(uint32_t subkeysHat[33][4],
                  const unsigned char *key,
                  unsigned char *output,
                  uint32_t nBytes)
{
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
    Get_Subkeys(prekey, subkeysHat);
}

/*
The function is used to encrypt a block of data using the Serpent algorithm.
The input and the output should be 32 bytes long.
the input block is set as constant so no damage will be done to
the original text
*/
void InitialPermutation(const uint32_t *input, uint32_t *output)
{
    // Initialize the output to all zeros
    memset(output, 0, 4 * sizeof(uint32_t)); // Assuming 4 * 32-bit blocks = 128 bits

    for (int i = 0; i < 128; ++i)
    {
        // Calculate the new position of the current bit
        int newPos = (32 * i) % 127;
        // Special case for newPos == 0 as per the pseudo-code logic
        if (i != 0 && newPos == 0)
            newPos = 127;

        // Extract the bit from the input
        int bit = (input[i / 32] >> (i % 32)) & 1;

        // Set the bit in the new position in the output
        output[newPos / 32] |= bit << (newPos % 32);
    }
}

void FinalPermutation(const uint32_t *input, uint32_t *result)
{
    // copy end bits
    result[0] |= ((input[0] >> 0) & 0x1) << 0;
    result[3] |= ((input[3] >> 31) & 0x1) << 31;
    // transform bits
    for (int i = 1; i < 127; ++i)
    {
        uint32_t replacer = ((i * 4) % 127);
        uint32_t currentBlockPosition = i / 32;
        uint32_t currentBlockReplacer = replacer / 32;
        result[currentBlockPosition] |= ((input[currentBlockReplacer] >> (replacer % 32)) & 1) << (i % 32);
    }
}

void LinearTransformation(uint32_t *X)
{
    // Apply the linear transformation to the block X
    X[0] = ROTL(X[0], 13);
    X[2] = ROTL(X[2], 3);
    X[1] = X[1] ^ X[0] ^ X[2];
    X[3] = X[3] ^ X[2] ^ (X[0] << 3);
    X[1] = ROTL(X[1], 1);
    X[3] = ROTL(X[3], 7);
    X[0] = X[0] ^ X[1] ^ X[3];
    X[2] = X[2] ^ X[3] ^ (X[1] << 7);
    X[0] = ROTL(X[0], 5);
    X[2] = ROTL(X[2], 22);
}

void RoundFunction(uint32_t *block, const uint32_t *subkey)
{
    // Substitute using S-boxes and XOR with subkey
    for (int i = 0; i < 4; i++)
    {
        block[i] = applySbox(i, block[i]) ^ subkey[i]; // Assume Sbox() applies the S-box transformation based on round
    }
    LinearTransformation(block); // Apply Linear Transformation
}

// summoning the main function of the algorithm, will include in it all the other functions
// of the algorithm and combine their actions to encrypt the plain text
void serpent_encrypt(const unsigned char *plaintext,
                     const unsigned char *key,
                     unsigned char *output,
                     unsigned int kBytes)
{
    // 33 subkeys * 32bits * 4 blocks
    uint32_t subkeysHat[33][4] = {0};

    // generating the needed keys and expantion to 33 keys from 32
    Key_Schedule(subkeysHat, key, output, kBytes);

    // Initial Permutation
    const uint32_t *charPlainToInt = (const uint32_t *)plaintext;
    // make static allocation in order to avoid dynamic allocation
    uint32_t B[4] = {0};

    InitialPermutation(charPlainToInt, B);

    uint32_t result[4] = {0};
    // Apply 32 rounds of encryption
    for (int round = 0; round < 32; round++)
    {
        for (int j = 0; j < 4; ++j)
        {
            result[j] = B[j] ^ subkeysHat[round][j];
        }
        if (round < 31)
        {
            RoundFunction(result, subkeysHat[round]);
        }
        else
        {
            // the LAST round of the transformation is used to replace by additional key mixing
            result[0] = result[0] ^ subkeysHat[32][0];
            result[1] = result[1] ^ subkeysHat[32][1];
            result[2] = result[2] ^ subkeysHat[32][2];
            result[3] = result[3] ^ subkeysHat[32][3];
        }
    }

    // copy 128 bits to output string
    memcpy(output, result, 16);

    /* FINAL PERMUTATION */
    uint32_t finalResult[4] = {0};
    FinalPermutation(result, finalResult);

    // copy 128 bits to output string
    memcpy(output, finalResult, 16);
}
// IMPORTANT: ONLY CONVERTS A BIG ENDIAN HEX STRING
void hexConvert(const char *s, unsigned char *b)
{
    const char *a = "0123456789abcdef";
    // find
    for (int i = 0; i < 32; i += 2)
    {
        unsigned char e = 0;
        for (int j = 0; j < 16; ++j)
        {
            if (s[i] == a[j])
            {
                e |= j << 4;
                break;
            }
        }
        for (int j = 0; j < 16; ++j)
        {
            if (s[i + 1] == a[j])
            {
                e |= j << 0;
                break;
            }
        }
        b[15 - (i / 2)] = e;
    }
}

void printHex(const unsigned char *s, int bytelength, const char *message)
{
    const char *a = "0123456789abcdef";
    printf("%s\n", message);
    printf("(little endian)\n");
    for (int i = 0; i < bytelength; ++i)
    {
        printf("%c", a[(s[i] >> 0) & 0xF]);
        printf("%c", a[(s[i] >> 4) & 0xF]);
    }
    printf("\n(big endian)\n");
    for (int i = bytelength - 1; i >= 0; --i)
    {
        printf("%c", a[(s[i] >> 4) & 0xF]);
        printf("%c", a[(s[i] >> 0) & 0xF]);
    }
    printf("\n");
}

// main encryption process
// Initialize your block and keys
// Call serpentEncrypt with the block and keys
int main()
{
    // (8 bits * 4) * 4 = 128 bits
    const char *test_string = "softAnus";

    // key in this implementation must be 128bits
    const char *key_string = "bigDick";

    unsigned char *encrypted_string = (unsigned char *)malloc(16 * sizeof(unsigned char));
    unsigned char *decrypted_string = (unsigned char *)malloc(16 * sizeof(unsigned char));

    unsigned char *test_string_hex = (unsigned char *)malloc(16 * sizeof(unsigned char));
    hexConvert(test_string, test_string_hex);
    unsigned char *key_string_hex = (unsigned char *)malloc(16 * sizeof(unsigned char));
    hexConvert(key_string, key_string_hex);

    serpent_encrypt(test_string_hex, key_string_hex, encrypted_string, 16);
    printHex(encrypted_string, 16, "Encrypted Cipher:");
    printf("\n");
    return 0;

    return 0;
}
