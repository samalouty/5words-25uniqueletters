#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 6579
#define MAX_WORD_LENGTH 6

typedef struct {
    char word[MAX_WORD_LENGTH];
    int uniqueLetters;
} Node;

int graph[MAX_WORDS][MAX_WORDS];
Node nodes[MAX_WORDS];
int maxCliqueSize = 0;
char maxClique[5][MAX_WORD_LENGTH];

void addEdge(int u, int v) {
    graph[u][v] = 1;
    graph[v][u] = 1;
}

void removeEdge(int u, int v) {
    graph[u][v] = 0;
    graph[v][u] = 0;
}

void printClique() {
    printf("Word combinations with 25 unique letters:\n");
    for (int i = 0; i < maxCliqueSize; i++) {
        printf("%s\n", maxClique[i]);
    }
}

void bronKerbosch(int* R, int RSize, int* P, int PSize, int* X, int XSize) {
    if (PSize == 0 && XSize == 0 && RSize == 5) {
        if (RSize > maxCliqueSize) {
            maxCliqueSize = RSize;
            memcpy(maxClique, nodes, sizeof(maxClique));
        }
        return;
    }

    int* PuX = (int*)malloc((PSize + XSize) * sizeof(int));
    memcpy(PuX, P, PSize * sizeof(int));
    memcpy(PuX + PSize, X, XSize * sizeof(int));

    for (int i = 0; i < PSize; i++) {
        int v = PuX[i];
        if (RSize + 1 + PSize <= maxCliqueSize) {
            return;
        }
        if (RSize + 1 + i + 1 >= maxCliqueSize) {
            int* newR = (int*)malloc((RSize + 1) * sizeof(int));
            memcpy(newR, R, RSize * sizeof(int));
            newR[RSize] = v;

            int newPSize = 0;
            int* newP = (int*)malloc(PSize * sizeof(int));
            for (int j = i + 1; j < PSize; j++) {
                int u = PuX[j];
                if (graph[v][u] == 1) {
                    newP[newPSize] = u;
                    newPSize++;
                }
            }

            int newXSize = 0;
            int* newX = (int*)malloc(XSize * sizeof(int));
            for (int j = 0; j < XSize; j++) {
                int u = X[j];
                if (graph[v][u] == 1) {
                    newX[newXSize] = u;
                    newXSize++;
                }
            }

            bronKerbosch(newR, RSize + 1, newP, newPSize, newX, newXSize);

            free(newR);
            free(newP);
            free(newX);
        }

        PSize--;
        X[XSize] = v;
        XSize++;
    }

    free(PuX);
}

int main() {
    FILE* inputFile = fopen("binaryRep.txt", "r");

    int nodeCount = 0;
    while (fscanf(inputFile, "%d", &nodes[nodeCount].uniqueLetters) != EOF) {
        fscanf(inputFile, "%s", nodes[nodeCount].word);
        nodeCount++;
    }

    fclose(inputFile);

    // Build the graph
    for (int i = 0; i < nodeCount; i++) {
        for (int j = i + 1; j < nodeCount; j++) {
            int uniqueLettersI = nodes[i].uniqueLetters;
            int uniqueLettersJ = nodes[j].uniqueLetters;
            if ((uniqueLettersI & uniqueLettersJ) == 0) {
                addEdge(i, j);
            }
        }
    }

    int* R = (int*)malloc(nodeCount * sizeof(int));
    int* P = (int*)malloc(nodeCount * sizeof(int));
    int* X = (int*)malloc(nodeCount * sizeof(int));

    for (int i = 0; i < nodeCount; i++) {
        P[i] = i;
    }

    bronKerbosch(NULL, 0, P, nodeCount, X, 0);

    if (maxCliqueSize == 5) {
        printClique();
    } else {
        printf("Unable to find 5 word combinations with 25 unique letters.\n");
    }

    free(R);
    free(P);
    free(X);

    return 0;
}
