#include "../headers/graphs.h"

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
double determinant(double matrix[][keyMatSize], int n)
{
    /*
      SIZE: Macro defining the size of the square matrix.
            You'll need to replace this with the actual dimension.
    */

    double det = 0.0;

    // Base case: 1x1 matrix
    if (n == 1)
    {
        return matrix[0][0];
    }

    // Temporary array to store cofactors
    double temp[keyMatSize][keyMatSize];

    // Sign multiplier to apply alternating signs
    int sign = 1;

    // Iterate through the first row for cofactor expansion
    for (int i = 0; i < n; i++)
    {
        // Get the minor matrix
        getCofactor(matrix, temp, 0, i, n);

        // Recursively calculate determinant, multiply by element and sign
        det += sign * matrix[0][i] * determinant(temp, n - 1);

        // Alternate the sign for the next element
        sign = -sign;
    }

    return det;
}

// Helper function to get the cofactor matrix
void getCofactor(double matrix[][keyMatSize], double temp[][keyMatSize], int p, int q, int n)
{
    int row = 0, col = 0;

    // Loop to fill the cofactor matrix 'temp'
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != p && j != q)
            {
                temp[row][col++] = matrix[i][j];
                if (col == n - 1)
                {
                    col = 0;
                    row++;
                }
            }
        }
    }
}

// shorten the string to enclude only characters
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

// padding for the missing characters in the graphs
char *AutofillString(char *input, int len, int numfill)
{
    char add = 'A';
    char *output = strdup(input);
    output = (char *)realloc(output, (len + numfill + 1) * sizeof(char));
    for (int i = len; i < len + numfill; i++)
    {
        output[i] = add++;
    }
    output[len + numfill] = '\0';
    return output;
}

char **split_string_exact(const char *str, char **substrings, int num_substrings)
{
    int len = strlen(str);
    int substring_len = len / num_substrings; // Ideal substring length

    for (int i = 0; i < num_substrings; i++)
    {
        substrings[i] = (char *)malloc((substring_len + 1) * sizeof(char));
        if (substrings[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        for (int j = 0; j < substring_len; j++)
        {
            substrings[i][j] = str[i * substring_len + j];
        }
        substrings[i][substring_len] = '\0';
    }

    return substrings;
}

void inverseMatrix(double mat[][keyMatSize], double inv[][keyMatSize], int size)
{
    // Initialize the inverse matrix as the identity matrix
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
                inv[i][j] = 1.0;
            else
                inv[i][j] = 0.0;
        }
    }

    // Perform Gauss-Jordan elimination
    for (int i = 0; i < size; i++)
    {
        double pivot = mat[i][i];

        // Divide row i by the pivot value
        for (int j = 0; j < size; j++)
        {
            mat[i][j] /= pivot;
            inv[i][j] /= pivot;
        }

        // Eliminate other rows
        for (int k = 0; k < size; k++)
        {
            if (k != i)
            {
                double factor = mat[k][i];
                for (int j = 0; j < size; j++)
                {
                    mat[k][j] -= factor * mat[i][j];
                    inv[k][j] -= factor * inv[i][j];
                }
            }
        }
    }
}

int modularInverse(int a, int m)
{
    int t = 0, newt = 1;
    int r = m, newr = a;

    while (newr != 0)
    {
        int quotient = r / newr;
        int temp = t;
        t = newt;
        newt = temp - quotient * newt;
        temp = r;
        r = newr;
        newr = temp - quotient * newr;
    }
    if (r > 1)
        return -1; // a is not invertible
    if (t < 0)
        t += m;
    return t;
}