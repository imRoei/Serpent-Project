#include "serpent_functions.h"

// Rearranges the bits of the input block in a specific pattern to prepare it for encryption.
void InitialPermutation(const uint *input, uint *result)
{
    // copy end bits
    result[0] |= ((input[0] >> 0) & 0x1) << 0;
    result[3] |= ((input[3] >> 31) & 0x1) << 31;
    // transform bits
    for (int i = 1; i < 127; ++i)
    {
        uint replacer = ((i * 32) % 127);
        uint currentBlockPosition = i / 32;
        uint currentBlockReplacer = replacer / 32;
        result[currentBlockPosition] |= ((input[currentBlockReplacer] >> (replacer % 32)) & 1) << (i % 32);
    }
}
// Reverses the bit rearrangement performed by InitialPermutation to recover data after decryption.
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

// Performs a final bit rearrangement on the data after encryption.
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
// Reverses the final bit rearrangement to obtain the original data after decryption.
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

// Performs a complex transformation on the data block
// XORs the block with a subkey.
// Applies S-Box substitutions to individual bits.
// Mixes and rearranges bits using a linear transformation table.
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