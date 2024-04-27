#include <graphs.h>

// Create a graph with a given number of vertices
Graph *createGraph(int numVertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    // Allocate memory for vertices array
    graph->character = (char *)malloc(numVertices * sizeof(char));

    // Allocate memory for the adjacency matrix
    graph->adjacencyMatrix = (int **)malloc(numVertices * sizeof(int *));
    for (int i = 0; i < numVertices; i++)
    {
        graph->adjacencyMatrix[i] = (int *)malloc(numVertices * sizeof(int));
        for (int j = 0; j < numVertices; j++)
        {
            graph->adjacencyMatrix[i][j] = 0; // Default weight (no edge)
        }
    }

    return graph;
}

// make undirected graph
void populateGraph(Graph *graph, char *block)
{
    int weight;
    for (int i = 0; i < block_size; i++)
    {
        weight = block[(i + 1) % block_size] - block[i] - 'A';
        graph->adjacencyMatrix[i][(i + 1) % block_size] = weight;
        graph->adjacencyMatrix[(i + 1) % block_size][i] = weight;
    }
}

// make the graph completed with random weights
void makeCompletedGraph(Graph *graph)
{
    srand(time(NULL));
    int randomNumber;

    for (int i = 0; i < block_size; i++)
    {
        for (int j = 0; j < block_size; j++)
        {
            if (i != j)
            {
                if ((graph->adjacencyMatrix[i][j] == 0 && graph->adjacencyMatrix[j][i] == 0))
                {

                    do
                    {
                        // Generate a random number between 0 and RAND_MAX
                        randomNumber = rand() % 100 + 26;
                    } while (randomNumber <= 26 || randomNumber >= 100); // Repeat until the number is in the desired range
                }
            }
        }
    }
}
