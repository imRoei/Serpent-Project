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

void InitialPermutation(const uint *input, uint *result)
{
    // copy end bits
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

void InverseInitialPermutation(const uint *input, uint *result)
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

void FinalPermutation(const uint *input, uint *result)
{
    // copy end bits
    result[0] |= ((input[0] >> 0) & 0x1) << 0;
    result[3] |= ((input[3] >> 31) & 0x1) << 31;
    // transform bits
    for (int i = 1; i < 127; ++i)
    {
        uint replacer = ((i * 4) % 127);
        uint currentBlockPosition = i / 32;
        uint currentBlockReplacer = replacer / 32;
        result[currentBlockPosition] |= ((input[currentBlockReplacer] >> (replacer % 32)) & 1) << (i % 32);
    }
}

void InverseFinalPermutation(const uint *input, uint *result)
{
    // copy end bits
    result[0] |= ((input[0] >> 0) & 0x1) << 0;
    result[3] |= ((input[3] >> 31) & 0x1) << 31;
    for (int i = 0; i < 127; ++i)
    {
        uint position = ((4 * i) % 127);
        uint currentBlockPosition = position / 32;
        uint currentBlockReplacer = i / 32;
        result[currentBlockPosition] |= ((input[currentBlockReplacer] >> (i % 32)) & 1) << (position % 32);
    }
}

BIT getBit(WORD x[], int p)
{
    /* Return the value of the bit at position 'p' in little-endian word
     array 'x'. */

    return (BIT)((x[p / BITS_PER_WORD] & ((WORD)0x1 << p % BITS_PER_WORD)) >> p % BITS_PER_WORD);
}

void setBit(uint *x, int p, BIT v)
{
    /* Set the bit at position 'p' of little-endian word array 'x' to 'v'. */

    if (v)
    {
        x[p / BITS_PER_WORD] |= ((WORD)0x1 << p % BITS_PER_WORD);
    }
    else
    {
        x[p / BITS_PER_WORD] &= ~((WORD)0x1 << p % BITS_PER_WORD);
    }
}

void LinearTransformation(uint *X, uint *result, uint subkeysHat[33][4])
{

    for (int i = 0; i < 32; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            X[j] = result[j] ^ subkeysHat[i][j];
        }
        for (int j = 0; j < 4; ++j)
        {
            X[j] = (SBox[i % 8][(X[j] >> 0) & 0xF]) << 0 |
                   (SBox[i % 8][(X[j] >> 4) & 0xF]) << 4 |
                   (SBox[i % 8][(X[j] >> 8) & 0xF]) << 8 |
                   (SBox[i % 8][(X[j] >> 12) & 0xF]) << 12 |
                   (SBox[i % 8][(X[j] >> 16) & 0xF]) << 16 |
                   (SBox[i % 8][(X[j] >> 20) & 0xF]) << 20 |
                   (SBox[i % 8][(X[j] >> 24) & 0xF]) << 24 |
                   (SBox[i % 8][(X[j] >> 28) & 0xF]) << 28;
        }
        if (i < 31)
        {
            for (int a = 0; a < 128; ++a)
            {
                char b = 0;
                int j = 0;
                while (LTTable[a][j] != MARKER)
                {
                    b ^= getBit(X, LTTable[a][j]);
                    ++j;
                }
                setBit(result, a, b);
            }
        }
        else
        {
            // In the last round, the transformation is replaced by an additional key mixing
            result[0] = X[0] ^ subkeysHat[32][0];
            result[1] = X[1] ^ subkeysHat[32][1];
            result[2] = X[2] ^ subkeysHat[32][2];
            result[3] = X[3] ^ subkeysHat[32][3];
        }
    }
}

void InverseLinearTransformation(uint *X, uint *result, uint subkeysHat[33][4])
{
    for (int i = 31; i >= 0; --i)
    {
        if (i < 31)
        {
            for (int a = 0; a < 128; ++a)
            {
                char b = 0;
                int j = 0;
                while (LTTableInverse[a][j] != MARKER)
                {
                    b ^= getBit(result, LTTableInverse[a][j]);
                    ++j;
                }
                setBit(X, a, b);
            }
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
}

void KeyExpention(const uchar *key, uint *keysplit, uint kBytes)
{
    // check if key needs to be padded then
    // split original key into 8 32bit prekeys
    if (kBytes < 32)
    {
        unsigned char tempkey[32] = {0};
        // if shorter than 32 bytes, pad key with 0b1
        ulong kl = kBytes;
        for (int i = 0; i < kl; ++i)
        {
            tempkey[i] = key[i];
        }
        tempkey[kl] = 0b00000001;
        for (int i = 0; i < 8; ++i)
        {
            keysplit[i] = *(((uint *)tempkey) + i);
        }
    }
    else if (kBytes == 32)
    {
        for (int i = 0; i < 8; ++i)
        {
            keysplit[i] = *(((uint *)key) + i);
        }
    }
    else
    {
        printf("Key Length Error\n");
        exit(EXIT_FAILURE);
    }
}

void KeySchedule(uint subkeysHat[33][4],
                 const uchar *key,
                 uchar *output,
                 uint kBytes)
{
    // 33 subkeys * 32bits * 4 blocks
    uint subkeys[33][4] = {0};
    uint keysplit[8] = {0};
    uint interkey[140] = {0};
    // memory precheck
    if (output == NULL)
    {
        fprintf(stderr, "Given output char pointer not initialized/allocated.\n");
        exit(EXIT_FAILURE);
    }
    KeyExpention(key, keysplit, kBytes);
    // load keysplit into interkey
    for (int i = 0; i < 8; ++i)
    {
        interkey[i] = keysplit[i];
    }
    /* GENERATE PREKEYS */
    for (int i = 8; i < 140; ++i)
    {
        interkey[i] = ROTL((interkey[i - 8] ^ interkey[i - 5] ^ interkey[i - 3] ^ interkey[i - 1] ^ phi ^ (i - 8)), 11);
    }
    // generate keys from s-boxes
    // holds keys
    for (int i = 0; i < 33; ++i)
    {
        // descending selector starting at 3
        int currentBox = (32 + 3 - i) % 32;
        char sboxOut = 0;
        for (int j = 0; j < 32; ++j)
        {
            sboxOut = SBox[currentBox % 8][((interkey[8 + 0 + (4 * i)] >> j) & 1) << 0 |
                                           ((interkey[8 + 1 + (4 * i)] >> j) & 1) << 1 |
                                           ((interkey[8 + 2 + (4 * i)] >> j) & 1) << 2 |
                                           ((interkey[8 + 3 + (4 * i)] >> j) & 1) << 3];
            for (int l = 0; l < 4; ++l)
            {
                subkeys[i][l] |= ((sboxOut >> l) & 1) << j;
            }
        }
    }
    // PERMUTATE THE KEYS
    for (int i = 0; i < 33; ++i)
    {
        InitialPermutation(subkeys[i], subkeysHat[i]);
    }
}

void serpent_encrypt_standard(const unsigned char *plaintext,
                              const unsigned char *key,
                              unsigned char *output,
                              unsigned int kBytes)
{

    // 33 subkeys * 32bits * 4 blocks
    uint subkeysHat[33][4] = {0};
    KeySchedule(subkeysHat, key, output, kBytes);

    /* INITIAL PERMUTATION */

    // ignore bit[0] and bit[127]
    // replace bit[1..126] with bit[(i*32)%127]
    const uint *charpToInt = (const uint *)plaintext;
    uint result[4] = {0};
    InitialPermutation(charpToInt, result);

    /* LINEAR TRANSFORMATION */
    uint X[4] = {0};
    LinearTransformation(X, result, subkeysHat);

    /* FINAL PERMUTATION */

    uint finalResult[4] = {0};
    FinalPermutation(result, finalResult);

    // copy 128 bits to output string
    memcpy(output, finalResult, 16);
    while (*output++)
    {
        printf("%c ", *output);
    }
}

// decryption proccess
void serpent_decrypt_standard(const unsigned char *plaintext,
                              const unsigned char *key,
                              unsigned char *output,
                              unsigned int kBytes)
{

    uint subkeysHat[33][4] = {0};

    KeySchedule(subkeysHat, key, output, kBytes);

    /*  Start plaintext processing  */

    /* REVERSE FINAL PERMUTATION */

    // ignore bit[0] and bit[127]
    // replace bit[1..126] with bit[(i*32)%127]
    const uint *charpToInt = (const uint *)plaintext;
    uint result[4] = {0};
    InverseFinalPermutation(charpToInt, result);

    // result == Bi

    /* REVERSE LINEAR TRANSFORMATION */

    // 32 rounds
    uint X[4] = {0};
    InverseLinearTransformation(X, result, subkeysHat);

    /* REVERSE INITIAL PERMUTATION */

    uint finalResult[4] = {0};
    InverseInitialPermutation(result, finalResult);

    // copy 128 bits to output string
    memcpy(output, finalResult, 16);
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
int main(int argc, const char *argv[])
{

    // HEX INPUT
    // (8 bits * 4) * 4 = 128 bits
    const char *test_string = "roei homo";
    // key in this implementation must be 128bits
    const char *key_string = "roei homo meod";
    /*                          ^ = msb                        ^ = lsb */
    unsigned char *encrypted_string = malloc(16 /*bytes*/);
    unsigned char *decrypted_string = malloc(16 /*bytes*/);

    // print original string
    //    print_bits(test_string, "Plaintext");
    //    print_bits(key_string, "Key");

    unsigned char *test_string_hex = malloc(16);
    hexConvert(test_string, test_string_hex);
    unsigned char *key_string_hex = malloc(16);
    hexConvert(key_string, key_string_hex);

    serpent_encrypt_standard(test_string_hex, key_string_hex, encrypted_string, 16);
    printHex(encrypted_string, 16, "Encrypted Cipher:");
    printf("\n");
    serpent_decrypt_standard(encrypted_string, key_string_hex, decrypted_string, 16);
    printHex(decrypted_string, 16, "Decrypted Cipher:");

    return 0;
}