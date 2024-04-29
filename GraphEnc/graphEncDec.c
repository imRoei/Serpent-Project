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

char *firstSetCypher(char *string, int a, int b)
{
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
    // fill out the missing characters for the graph format
    if ((block_size - strlen(result) % block_size) != 0)
    {
        result = AutofillString(result, strlen(result), block_size - strlen(result) % block_size);
    }
    printf("\n%s\n", result);
    return result;
}

// make the graph completed with random weights
void makeCompletedGraph(Graph *graph)
{
    int randomNumber;

    for (int i = 1; i < block_size + 1; i++)
    {
        for (int j = 1; j < block_size + 1; j++)
        {
            if (i != j)
            {
                if ((graph->adjacencyMatrix[i][j] == 0 && graph->adjacencyMatrix[j][i] == 0))
                {
                    do
                    {
                        // Generate a random number between 26 and 100 (inclusive)
                        randomNumber = rand() % 75 + 27;               // 26 to 100 inclusive
                    } while (randomNumber < 26 || randomNumber > 100); // Repeat until the number is in the desired range

                    graph->adjacencyMatrix[i][j] = randomNumber;
                    graph->adjacencyMatrix[j][i] = randomNumber;
                }
            }
        }
    }
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
// make undirected graph
void populateGraph(Graph *graph, char *character) // needs some fixing
{

    int weight;
    for (int i = 1; i < block_size + 1; i++)
    {

        weight = character[i % block_size] - character[i - 1];
        if (i < block_size)
        {
            graph->adjacencyMatrix[i][i + 1] = weight;
            graph->adjacencyMatrix[i + 1][i] = weight;
        }
        else
        {
            graph->adjacencyMatrix[1][block_size] = weight;
            graph->adjacencyMatrix[block_size][1] = weight;
        }
    }
}

char calculateFirstSpecial(double key[][keyMatSize])
{
    int firstSpecial = 0;
    for (int i = 0; i < keyMatSize; i++)
    {
        for (int j = 0; j < keyMatSize; j++)
        {
            firstSpecial += key[i][j];
        }
    }
    firstSpecial %= 26;

    return (firstSpecial + 'A');
}

void addSpecialChar(Graph *graph[], double key[][keyMatSize], int blocknumber, char **character)
{
    char firstSpecial = calculateFirstSpecial(key);

    graph[0]->adjacencyMatrix[0][1] = character[0][0] - firstSpecial;
    graph[0]->adjacencyMatrix[1][0] = character[0][0] - firstSpecial;

    for (int i = 1; i < blocknumber; i++)
    {

        graph[i]->adjacencyMatrix[0][1] = character[i][0] - character[i - 1][block_size - 1];
        graph[i]->adjacencyMatrix[1][0] = character[i][0] - character[i - 1][block_size - 1];
    }
}

void multiplyMatrices(double key[][keyMatSize], Graph *gMat)
{
    double result[keyMatSize][keyMatSize];
    for (int i = 0; i < keyMatSize; ++i)
    {
        for (int j = 0; j < keyMatSize; ++j)
        {
            result[i][j] = 0;
            for (int k = 0; k < keyMatSize; ++k)
            {
                result[i][j] += key[i][k] * gMat->adjacencyMatrix[k][j];
            }
        }
    }
    for (int i = 0; i < keyMatSize; ++i)
    {
        for (int j = 0; j < keyMatSize; ++j)
        {
            gMat->adjacencyMatrix[i][j] = result[i][j];
        }
    }
}

Graph **Encryption(double key[][keyMatSize], char *text, int a, int b)
{
    char *EncText = firstSetCypher(text, a, b);
    int blocknumber = strlen(EncText) / block_size;
    if (strlen(EncText) % block_size != 0)
    {
        blocknumber++;
    }
    Graph **GraphBlocks = (Graph **)malloc(sizeof(Graph) * blocknumber);
    char **substrings = (char **)malloc(blocknumber * sizeof(char *));
    substrings = split_string_exact(EncText, substrings, blocknumber);
    for (int i = 0; i < blocknumber; i++)
    {
        GraphBlocks[i] = createGraph(block_size);
        populateGraph(GraphBlocks[i], substrings[i]);
        makeCompletedGraph(GraphBlocks[i]);
    }
    addSpecialChar(GraphBlocks, key, blocknumber, substrings);
    for (size_t i = 0; i < blocknumber; i++)
    {
        multiplyMatrices(key, GraphBlocks[i]);
    }

    return GraphBlocks;
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

char *getEncryptedText(Graph **EncryptedBlocks, char firstSpecial, int textLength)
{
    // Set a fixed seed for any randomness used in the encryption process
    double diff;
    char *encryptedText = (char *)malloc(sizeof(char) * textLength + 1); // +1 for null terminator
    encryptedText[textLength] = '\0';                                    // Ensure null termination

    for (int i = 0; i < textLength / block_size; i++)
    {
        for (int j = 0; j < block_size; j++)
        {
            if (i == 0 && j == 0)
            {
                diff = firstSpecial + EncryptedBlocks[0]->adjacencyMatrix[0][1];
                encryptedText[0] = diff;
            }
            else
            {
                // Assuming you want to use the PREVIOUS character in the SAME block:
                diff = encryptedText[i * block_size + j - 1] + EncryptedBlocks[i]->adjacencyMatrix[j][j + 1];
                encryptedText[i * block_size + j] = diff;
            }
        }
    }
    return encryptedText; // Add return!
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

void Decreyption(double key[][keyMatSize], Graph **EncryptedBlocks, int blocknumber, int a, int b)
{
    double inverseKey[keyMatSize][keyMatSize];
    char special = calculateFirstSpecial(key);
    inverseMatrix(key, inverseKey, keyMatSize);
    printf("\nDecryption");
    for (int i = 0; i < blocknumber; i++)
    {
        multiplyMatrices(inverseKey, EncryptedBlocks[i]);
    }
    int textLength = blocknumber * block_size;
    char *Enctext = strdup(getEncryptedText(EncryptedBlocks, special, textLength));
    printf("Not determinent enc: %s\n", Enctext);
    for (int i = 0; i < textLength; i++)
    {
        Enctext[i] -= 'A';
        if (Enctext[i] >= 14)
        {
            Enctext[i] = Enctext[i] + 26;
        }
        else
        {

            Enctext[i] = (Enctext[i] + 26 * 2);
        }
        Enctext[i] += 25 - 'A';
        int inverse = modularInverse(a, 26);
        Enctext[i] = (inverse * (Enctext[i] - b)) % 26;
    }
    char *Decrypted = (char *)malloc((textLength + 1) * sizeof(char));
    for (int i = 0; i < textLength; i++)
    {
        Decrypted[i] = ((int)Enctext[i]) + 'A' + 26;
    }
    printf("Decrypted: %s", Decrypted);
}
