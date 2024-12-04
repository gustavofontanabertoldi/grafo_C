#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node* adjLists[MAX_VERTICES];
} Graph;

// Função para criar um novo nó
Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Função para criar um grafo
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

// Função para adicionar arestas
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Função para criar um subgrafo
Graph* createSubgraph(Graph* graph, int* subset, int subsetSize) {
    Graph* subgraph = createGraph(graph->numVertices);

    // Array para verificar se um vértice está no subconjunto
    bool isInSubset[MAX_VERTICES] = {false};
    for (int i = 0; i < subsetSize; i++) {
        isInSubset[subset[i]] = true;
    }

    // Adicionar arestas que conectam vértices no subconjunto
    for (int i = 0; i < subsetSize; i++) {
        int u = subset[i];
        Node* temp = graph->adjLists[u];

        while (temp) {
            int v = temp->vertex;
            if (isInSubset[v]) {
                addEdge(subgraph, u, v);
            }
            temp = temp->next;
        }
    }
    return subgraph;
}

// Função para imprimir um grafo
void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->adjLists[v];
        printf("Vértice %d:", v);
        while (temp) {
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Função principal
int main() {
    int vertices = 6;

    Graph* graph = createGraph(vertices);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 5);

    printf("Grafo original:\n");
    printGraph(graph);

    // Subconjunto de vértices para o subgrafo
    int subset[] = {1, 2, 3, 4};
    int subsetSize = sizeof(subset) / sizeof(subset[0]);

    // Criar subgrafo
    Graph* subgraph = createSubgraph(graph, subset, subsetSize);

    printf("\nSubgrafo:\n");
    printGraph(subgraph);

    return 0;
}
