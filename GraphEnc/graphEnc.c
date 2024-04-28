#include "graphs.h"

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
void populateGraph(Graph *graph)
{

    int weight;
    for (int i = 1; i < block_size + 1; i++)
    {

        weight = graph->character[i % block_size] - graph->character[i - 1];
        printf("\n%c - %c", graph->character[i % block_size], graph->character[i - 1]);
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

void addSpecialChar(Graph *graph[], double key[][keyMatSize], int blocknumber)
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
    graph[0]->special = firstSpecial + 'A';
    graph[0]->adjacencyMatrix[0][1] = graph[0]->character[0] - graph[0]->special;
    graph[0]->adjacencyMatrix[1][0] = graph[0]->character[0] - graph[0]->special;

    for (int i = 1; i < blocknumber; i++)
    {
        graph[i]->special = graph[i - 1]->character[block_size - 1];
        printf("\n Special: %c-%c", graph[i]->special, graph[i - 1]->character[0]);
        graph[i]->adjacencyMatrix[0][1] = graph[i]->character[0] - graph[i]->special;
        graph[i]->adjacencyMatrix[1][0] = graph[i]->character[0] - graph[i]->special;
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

void Encryption(double key[][keyMatSize], char *text)
{
    char *EncText = firstSetCypher(text);
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
        GraphBlocks[i]->character = substrings[i];
        populateGraph(GraphBlocks[i]);
        makeCompletedGraph(GraphBlocks[i]);
    }
    addSpecialChar(GraphBlocks, key, blocknumber);
    for (int i = 0; i < blocknumber; i++)
    {
        PrintGraph(GraphBlocks[i]);
    }
    for (size_t i = 0; i < blocknumber; i++)
    {
        multiplyMatrices(key, GraphBlocks[i]);
    }
    for (int i = 0; i < blocknumber; i++)
    {
        PrintGraph(GraphBlocks[i]);
    }
}

void negateKey(double key[][keyMatSize], double **negativekey)
{
    negativekey = (char **)malloc(sizeof(char *) * keyMatSize);
    for (int i = 0; i < keyMatSize; i++)
    {
        negativekey[i] = (char *)malloc(sizeof(char) * keyMatSize);
    }

    for (int i = 0; i < keyMatSize; i++)
    {
        for (int j = 0; j < keyMatSize; j++)
        {
            negativekey[i][j] = pow(key[i][j], -1);
        }
    }
}

void Decreyption(double key[][keyMatSize], char *EncryptedTex)
{
    double **negativeKey;
    negateKey(key, negativeKey);
    printf("\nDecreyption");
    for (int i = 0; i < keyMatSize; i++)
    {
        for (int j = 0; j < keyMatSize; j++)
        {
            printf("%lf ", negativeKey[i][j]);
        }
    }
}

int main(int argc, char const *argv[])
{
    srand(time(NULL)); // Seed initialization

    double key[][keyMatSize] = {{1, 1, 2, 5, 3},
                                {4, 8, 9, 12, 6},
                                {5, 18, 21, 10, 3},
                                {63, 38, 7, 29, 24},
                                {0, 25, 75, 4, 33}};

    char *plaintext = "DECEMBERFIRST";
    if (determinant(key, keyMatSize) == 0)
    {
        printf("Key is not secure enough");
    }
    else
    {
        Encryption(key, plaintext);
    }
    Decreyption(key, plaintext);
    return 0;
}
