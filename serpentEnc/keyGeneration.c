#include "../headers/serpent_functions.h"

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

void KeySchedule(uint subkeysHat[33][4], const uchar *key, uchar *output, uint kBytes)
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
        interkey[i] = ROTL((interkey[i - 8] ^ interkey[i - 5] ^ interkey[i - 3] ^ interkey[i - 1] ^ FRAC ^ (i - 8)), 11);
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
