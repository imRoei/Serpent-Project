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

    for (int i = 0; i < 32; i += 2)
    {
        unsigned char e = 0;

        // Find first hex digit
        for (int j = 0; j < 16; ++j)
        {
            if (s[i] == a[j])
            {
                e |= j << 4;
                j = 16; // Exit the inner loop
            }
        }

        // Find second hex digit
        for (int j = 0; j < 16; ++j)
        {
            if (s[i + 1] == a[j])
            {
                e |= j << 0;
                j = 16; // Exit the inner loop
            }
        }

        b[15 - (i / 2)] = e;
    }
}

char *hex_to_string(const char *hex_string)
{
    // Error handling for invalid input
    if (hex_string == NULL || strlen(hex_string) % 2 != 0)
    {
        return NULL; // Indicate error
    }

    // Calculate the length of the resulting string
    int string_length = strlen(hex_string) / 2;
    char *string = (char *)malloc((string_length + 1) * sizeof(char)); // +1 for the null terminator
    if (string == NULL)
    {
        return NULL; // Indicate memory allocation error
    }

    // Convert hex pairs to characters
    int i = 0, j = 0;
    while (hex_string[i] != '\0')
    {
        char hex_pair[3] = {hex_string[i], hex_string[i + 1], '\0'};
        int byte_value = strtol(hex_pair, NULL, 16); // Convert hex pair to integer
        string[j++] = (char)byte_value;
        i += 2;
    }

    string[j] = '\0'; // Add the null terminator
    return string;
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