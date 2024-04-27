#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define KeySize 5
#define blockSize (KeySize - 1)

int gcd(int a, int b)
{
    int temp;
    while (b != 0)
    {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int isGcdOne(int a, int b)
{
    return gcd(a, 26) == 1 ? 1 : 0;
}

// Function to calculate the determinant of a square matrix
int determinant(int mat[KeySize][KeySize])
{
    int det = 0;
    int submat[KeySize - 1][KeySize - 1];

    if (KeySize == 1)
    {
        return mat[0][0];
    }
    else if (KeySize == 2)
    {
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    }
    else
    {
        for (int col = 0; col < KeySize; col++)
        {
            int subi = 0;
            for (int i = 1; i < KeySize; i++)
            {
                int subj = 0;
                for (int j = 0; j < KeySize; j++)
                {
                    if (j == col)
                    {
                        continue;
                    }
                    submat[subi][subj] = mat[i][j];
                    subj++;
                }
                subi++;
            }
            det += (col % 2 == 0 ? 1 : -1) * mat[0][col] * determinant(submat);
        }
    }
    return det;
}

void processString(const char *input, char **output)
{
    int outputSize = 1; // Initial size of the output string
    *output = (char *)malloc(outputSize * sizeof(char));
    if (*output == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    while (*input)
    {
        if (isalpha(*input))
        {
            if (isupper(*input))
            {
                (*output)[outputSize - 1] = *input;
                outputSize++;
                *output = (char *)realloc(*output, outputSize * sizeof(char));
                if (*output == NULL)
                {
                    fprintf(stderr, "Memory reallocation failed\n");
                    exit(1);
                }
            }
            else if (islower(*input))
            {
                (*output)[outputSize - 1] = toupper(*input);
                outputSize++;
                *output = (char *)realloc(*output, outputSize * sizeof(char));
                if (*output == NULL)
                {
                    fprintf(stderr, "Memory reallocation failed\n");
                    exit(1);
                }
            }
        }
        input++;
    }
    (*output)[outputSize - 1] = '\0'; // Add null terminator to end the output string
}

char *firstSetCypher(char *string)
{
    int a, b;
    printf("Enter two numbers between 0 and 26\n");
    scanf("%d%d", &a, &b);
    while (a < 0 || a > 26 || b < 0 || b >= 26 || !isGcdOne(a, b))
    {
        printf("Invalid input - ");
        printf("Enter two numbers between 0 and 26 that their gcd equals 1");
        scanf("%d%d", &a, &b);
    }
    char *x;
    processString(string, &x);
    printf("%s\n", x);
    int x_len = strlen(x);
    char *result;
    // trasform the letters to suit the graph format
    for (size_t i = 0; i < x_len; i++)
    {
        x[i] = (((x[i] - 'A') * a + b) % 26) + 'A';
    }
    result = strdup(x);
    for (size_t i = 0; i < x_len; i++)
    {
        result[i] = (result[i] - 25) % 26 + 'A';
        printf("%c", result[i]);
    }
    return result;
}

int main(int argc, char const *argv[])
{
    firstSetCypher("DECEMBER FIRST");

    return 0;
}
