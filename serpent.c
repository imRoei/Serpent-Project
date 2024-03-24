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
typedef unsigned int WORD;
typedef unsigned char BIT;
typedef unsigned char NIBBLE;
typedef WORD BLOCK[4];
typedef uint32_t _128[4];
#define BITS_PER_NIBBLE 4
#define BITS_PER_BLOCK 128
#define BITS_PER_WORD 32
#define WORDS_PER_BLOCK 4
#define NIBBLES_PER_WORD 8

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
        paddedKey[keyLength] = 0x80;
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

    for (int i = 0; i < 33; i++)
    {
        int p = (32 + 3 - i) % 32;
        char s = 0;
        for (int k = 0; k < 32; k++)
        {
            s = SBox[p % 8][((key[8 + 0 + (4 * i)] >> k) & 1) << 0 |
                            ((key[8 + 1 + (4 * i)] >> k) & 1) << 1 |
                            ((key[8 + 2 + (4 * i)] >> k) & 1) << 2 |
                            ((key[8 + 3 + (4 * i)] >> k) & 1) << 3];
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
void InitialPermutation(const uint32_t *input, uint32_t *result)
{
    // Initialize the output to all zeros
    memset(result, 0, 4 * sizeof(uint32_t));

    result[0] |= ((input[0] >> 0) & 0x1) << 0;
    result[3] |= ((input[3] >> 31) & 0x1) << 31;
    // transform bits
    // THIS SHOULD BE CORRECT
    for (int i = 1; i < 127; ++i)
    {
        uint replacer = ((i * 32) % 127);
        uint currentBlockPosition = i / 32;
        uint currentBlockReplacer = replacer / 32;
        result[currentBlockPosition] |= ((input[currentBlockReplacer] >> (replacer % 32)) & 1) << (i % 32);
    }
}
// exact same moves as the final permutation in reverse order.
void InverseInitialPermutation(const uint32_t *input, uint32_t *result)
{
    // copy end bits
    result[0] |= ((input[0] >> 0) & 0x1) << 0;
    result[3] |= ((input[3] >> 31) & 0x1) << 31;
    for (int i = 0; i < 127; ++i)
    {
        uint position = ((32 * i) % 127);
        uint currentBlockPosition = position / 32;
        uint currentBlockReplacer = i / 32;
        result[currentBlockPosition] |= ((input[currentBlockReplacer] >> (i % 32)) & 1) << (position % 32);
    }
}
// last step of the text mixing
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
    printf("%d%d%d%d", result[0], result[1], result[2], result[3]);
}

// exact same moves as the final permutation in reverse order.
void InverseFinalPermutation(const uint32_t *input, uint32_t *result)
{
    // copy end bits
    result[0] |= ((input[0] >> 0) & 0x1) << 0;
    result[3] |= ((input[3] >> 31) & 0x1) << 31;
    for (int i = 0; i < 127; ++i)
    {
        uint32_t position = ((4 * i) % 127);
        uint32_t currentBlockPosition = position / 32;
        uint32_t currentBlockReplacer = i / 32;
        result[currentBlockPosition] |= ((input[currentBlockReplacer] >> (i % 32)) & 1) << (position % 32);
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

void InverseLinearTransformation(uint32_t *X)
{
    // Reverse step 10
    X[2] = ROTL(X[2], 32 - 22); // Rotate right by 10 bits

    // Reverse step 9
    X[0] = ROTL(X[0], 32 - 5); // Rotate right by 27 bits

    // Prepare to reverse steps 7 and 8 by first undoing the effect of these XORs
    uint32_t originalX1 = X[1];
    uint32_t originalX3 = X[3];

    // Reverse step 8 (note that the operation itself is unchanged, just applied differently)
    X[2] ^= X[3] ^ (X[1] << 7);
    // Reverse step 7
    X[0] ^= X[1] ^ X[3];
    // Reverse step 6
    X[3] = ROTL(originalX3, 32 - 7); // Rotate right by 25 bits
    // Reverse step 5
    X[1] = ROTL(originalX1, 32 - 1); // Rotate right by 31 bits
    // Steps 3 and 4 are XOR operations and are their own inverses. We now apply them with the original X[1] and X[3]
    X[3] ^= X[2] ^ (X[0] << 3);
    X[1] ^= X[0] ^ X[2];
    // Reverse step 2
    X[2] = ROTL(X[2], 32 - 3); // Rotate right by 29 bits
    // Reverse step 1
    X[0] = ROTL(X[0], 32 - 13); // Rotate right by 19 bits
}

// Placeholder for applying S-box (to be implemented)
uint32_t applySbox(int round, uint32_t value)
{
    // Apply S-box transformation based on round and input value
    // Placeholder logic, replace with actual S-box application
    return value; // Return unchanged for placeholder
}

// Placeholder for applying inverse S-box (to be implemented)
uint32_t applyInverseSbox(int round, uint32_t value)
{
    // Apply inverse S-box transformation based on round and input value
    // Placeholder logic, replace with actual inverse S-box application
    return value; // Return unchanged for placeholder
}

void RoundFunction(uint32_t *X, const uint32_t *subkey)
{
    for (int i = 0; i < 4; ++i)
    {
        X[i] = applySbox(i, X[i]) ^ subkey[i];
    }
    LinearTransformation(X);
}

void InverseRoundFunction(uint32_t *X, const uint32_t *subkey)
{
    InverseLinearTransformation(X);
    for (int i = 0; i < 4; ++i)
    {
        X[i] = applyInverseSbox(i, X[i]) ^ subkey[i];
    }
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
    uint32_t result[4] = {0};

    InitialPermutation(charPlainToInt, result);

    uint32_t X[4] = {0};
    // Apply 32 rounds of encryption
    for (int round = 0; round < 32; round++)
    {
        for (int j = 0; j < 4; ++j)
        {
            X[j] = result[j] ^ subkeysHat[round][j];
        }
        if (round < 31)
        {
            RoundFunction(X, subkeysHat[round]);
        }
        else
        {
            // the LAST round of the transformation is used to replace by additional key mixing
            result[0] = X[0] ^ subkeysHat[32][0];
            result[1] = X[1] ^ subkeysHat[32][1];
            result[2] = X[2] ^ subkeysHat[32][2];
            result[3] = X[3] ^ subkeysHat[32][3];
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

// reverse and decrypt
void serpent_decrypt(const unsigned char *ciphertext,
                     const unsigned char *key,
                     unsigned char *output,
                     unsigned int kBytes)
{
    uint32_t subkeysHat[33][4] = {0};
    // Generate the subkeys for decryption
    Key_Schedule(subkeysHat, key, output, kBytes);

    // Convert ciphertext to uint32_t array for processing
    const uint *charpToInt = (const uint *)ciphertext;
    uint result[4] = {0};
    InverseFinalPermutation(charpToInt, result);

    /* REVERSE LINEAR TRANSFORMATION */

    // 32 rounds
    uint X[4] = {0};
    for (int i = 31; i >= 0; --i)
    {
        if (i < 31)
        {
            InverseRoundFunction(X, subkeysHat[i]);
        }
        else
        {
            // In the last round, the transformation is replaced by an additional key mixing
            X[0] = result[0] ^ subkeysHat[32][0];
            X[1] = result[1] ^ subkeysHat[32][1];
            X[2] = result[2] ^ subkeysHat[32][2];
            X[3] = result[3] ^ subkeysHat[32][3];
        }
        for (int j = 0; j < 4; ++j)
        {
            X[j] = (SBoxInverse[i % 8][(X[j] >> 0) & 0xF]) << 0 |
                   (SBoxInverse[i % 8][(X[j] >> 4) & 0xF]) << 4 |
                   (SBoxInverse[i % 8][(X[j] >> 8) & 0xF]) << 8 |
                   (SBoxInverse[i % 8][(X[j] >> 12) & 0xF]) << 12 |
                   (SBoxInverse[i % 8][(X[j] >> 16) & 0xF]) << 16 |
                   (SBoxInverse[i % 8][(X[j] >> 20) & 0xF]) << 20 |
                   (SBoxInverse[i % 8][(X[j] >> 24) & 0xF]) << 24 |
                   (SBoxInverse[i % 8][(X[j] >> 28) & 0xF]) << 28;
        }
        for (int j = 0; j < 4; ++j)
        {
            result[j] = X[j] ^ subkeysHat[i][j];
        }
    }

    // Apply the inverse initial permutation to finish the decryption process
    uint32_t finalResult[4] = {0};
    InverseInitialPermutation(result, finalResult);

    // Copy the decrypted block to the output
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
    /*
    // (8 bits * 4) * 4 = 128 bits
    const char *test_string = "hello i am roei";

    // key in this implementation must be 128bits
    const char *key_string = "mykey";

    unsigned char *encrypted_string = (unsigned char *)malloc(16 * sizeof(unsigned char));
    unsigned char *decrypted_string = (unsigned char *)malloc(16 * sizeof(unsigned char));

    unsigned char *test_string_hex = (unsigned char *)malloc(16 * sizeof(unsigned char));
    hexConvert(test_string, test_string_hex);
    unsigned char *key_string_hex = (unsigned char *)malloc(16 * sizeof(unsigned char));
    hexConvert(key_string, key_string_hex);

    serpent_encrypt(test_string_hex, key_string_hex, encrypted_string, 16);
    printHex(encrypted_string, 16, "Encrypted Cipher:");
    printf("\n");

    serpent_decrypt(encrypted_string, key_string_hex, decrypted_string, 16);
    printHex(decrypted_string, 16, "Decrypted Cipher:");
    printf("%s", decrypted_string);*/

    uint32_t testBlock[4] = {0x01234567, 0x89abcdef, 0xfedcba98, 0x76543210};
    uint32_t tempBlock[4];
    uint32_t resultBlock[4];
    // Apply Initial Permutation and its Inverse
    InitialPermutation(testBlock, tempBlock);
    InverseInitialPermutation(tempBlock, resultBlock);
    // Check if resultBlock matches testBlock for Initial Permutation and its Inverse
    printf("Testing Initial Permutation and its Inverse...\n");
    int testPassed = 1; // Assume test passed, and try to disprove it
    for (int i = 0; i < 4; i++)
    {
        if (testBlock[i] != resultBlock[i])
        {
            testPassed = 0; // Test failed if any pair of elements doesn't match
            break;          // No need to check further if any mismatch is found
        }
    }

    if (testPassed)
    {
        printf("Test PASSED: Initial Permutation and its Inverse correctly reverses the block.\n");
    }
    else
    {
        printf("Test FAILED: Initial Permutation and its Inverse did not correctly reverse the block.\n");
        // Optionally print the blocks for debugging
        for (int i = 0; i < 4; i++)
        {
            printf("Original: %08x, Result: %08x\n", testBlock[i], resultBlock[i]);
        }
    }
    /*
    // Reset tempBlock for next test
    memset(tempBlock, 0, sizeof(tempBlock));

    // Apply Final Permutation and its Inverse
    FinalPermutation(testBlock, tempBlock);
    InverseFinalPermutation(tempBlock, resultBlock);

    // Check if resultBlock matches testBlock for Final Permutation and its Inverse
    printf("Testing Final Permutation and its Inverse...\n");
    // [Here you would compare resultBlock to testBlock and print the result]

    // Conclude testing
    printf("Testing completed.\n");
    */
    return 0;
}