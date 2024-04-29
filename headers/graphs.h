#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

#define keyMatSize 5
#define block_size (keyMatSize - 1)

// Structure to represent the graph
typedef struct
{
    int numVertices;
    double **adjacencyMatrix;
} Graph;

Graph *createGraph(int numVertices);

void addWeightedEdge(Graph *graph, int src, int dest, int weight, char character);

int gcd(int a, int b);

int isGcdOne(int a, int b);

// Function to calculate the determinant of a square matrix
double determinant(double matrix[][keyMatSize], int n);

void getCofactor(double matrix[][keyMatSize], double temp[][keyMatSize], int p, int q, int n);

void processString(const char *input, char **output);

char *firstSetCypher(char *string, int a, int b);

// make the graph completed with random weights
void makeCompletedGraph(Graph *graph);
// add all values to the undirected graph
void populateGraph(Graph *graph, char *character);

void addSpecialChar(Graph *graph[], double key[][keyMatSize], int blocknumber, char **character);

void PrintGraph(Graph *graph);

Graph **Encryption(double key[][keyMatSize], char *text, int a, int b);

char **split_string_exact(const char *str, char **substrings, int num_substrings);

void multiplyMatrices(double key[][keyMatSize], Graph *gMat);

void inverseKey(double key[][keyMatSize], double negativekey[][keyMatSize]);

char calculateFirstSpecial(double key[][keyMatSize]);

char *getEncryptedText(Graph **EncryptedBlocks, char firstSpecial, int textLength);

void Decreyption(double key[][keyMatSize], Graph **EncryptedBlocks, int blocknumber, int a, int b);
