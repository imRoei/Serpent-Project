#include "../headers/graphs.h"

// Create a graph with a given number of vertices
Graph *createGraph(int numVertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = ++numVertices;
    // Allocate memory for the adjacency matrix
    graph->adjacencyMatrix = (double **)malloc(numVertices * sizeof(double *));
    for (int i = 0; i < numVertices; i++)
    {
        graph->adjacencyMatrix[i] = (double *)malloc(numVertices * sizeof(double));
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
        for (int j = 0; j < graph->numVertices; j++)
        {
            printf("%f ", graph->adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}