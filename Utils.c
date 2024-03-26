#include "serpent_functions.h"

void printHex(const unsigned char *s, int bytelength, const char *message)
{
    const char *a = "0123456789abcdef";
    printf("%s\n", message);
    printf("(big endian)\n");
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
        int flag1 = 1;
        int flag2 = 1;
        unsigned char e = 0;
        for (int j = 0; j < 16, flag1; ++j)
        {
            if (s[i] == a[j])
            {
                e |= j << 4;
                flag1 = 0;
            }
        }
        for (int j = 0; j < 16, flag2; ++j)
        {
            if (s[i + 1] == a[j])
            {
                e |= j << 0;
                flag2 = 0;
            }
        }
        b[15 - (i / 2)] = e;
    }
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

BIT getBit(WORD x[], int p)
{
    /* Return the value of the bit at position 'p' in little-endian word
     array 'x'. */

    return (BIT)((x[p / BITS_PER_WORD] & ((WORD)0x1 << p % BITS_PER_WORD)) >> p % BITS_PER_WORD);
}