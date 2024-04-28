#include "graphs.h"

// Create a graph with a given number of vertices
Graph *createGraph(int numVertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = ++numVertices;
    graph->special = '\0';
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

void PrintGraph(Graph *graph)
{
    printf("\n");
    for (int i = 0; i < graph->numVertices; i++)
    {
        printf("%c ", graph->character[i]);
    }
    printf("\n");
    for (int i = 0; i < graph->numVertices; i++)
    {
        for (int j = 0; j < graph->numVertices; j++)
        {
            printf("%d ", graph->adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}