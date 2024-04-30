#include "../headers/serpent_functions.h"

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

void hexstr_to_binary(const char *hexstr, uint8_t **binary, size_t *length)
{
    *length = strlen(hexstr) / 2; // Two hex chars represent one byte
    *binary = malloc(*length);
    if (!*binary)
    {
        *length = 0;
        return;
    }

    for (size_t i = 0; i < *length; i++)
    {
        sscanf(hexstr + (i * 2), "%2hhx", &(*binary)[i]);
    }
}

char *binary_to_hexstr(const uint8_t *binary, size_t length)
{
    char *hexstr = (char *)malloc(2 * length + 1); // Each byte takes two hex characters + null terminator
    if (!hexstr)
        return NULL;

    for (size_t i = 0; i < length; i++)
    {
        sprintf(hexstr + (i * 2), "%02x", binary[i]);
    }

    hexstr[2 * length] = '\0'; // Null-terminate the string
    return hexstr;
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