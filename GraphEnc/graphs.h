#include <stdio.h>

#include <stdlib.h>

#define block_size 4

#define INF 9999 // Infinity value for unconnected vertices

// Structure to represent the graph
typedef struct
{
    int numVertices;
    char *character;
    int **adjacencyMatrix;
} Graph;

Graph *createGraph(int numVertices);

void addWeightedEdge(Graph *graph, int src, int dest, int weight, char character);