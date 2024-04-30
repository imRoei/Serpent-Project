#include "../headers/graphs.h"

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
