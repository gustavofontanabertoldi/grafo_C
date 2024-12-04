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

// Função para verificar se o grafo é bipartido usando BFS
bool isBipartite(Graph* graph) {
    int color[MAX_VERTICES];
    for (int i = 0; i < graph->numVertices; i++)
        color[i] = -1;

    for (int start = 0; start < graph->numVertices; start++) {
        if (color[start] == -1) { // Ainda não visitado
            color[start] = 0;

            int queue[MAX_VERTICES], front = 0, rear = 0;
            queue[rear++] = start;

            while (front < rear) {
                int u = queue[front++];

                Node* temp = graph->adjLists[u];
                while (temp) {
                    int v = temp->vertex;

                    if (color[v] == -1) { // Não colorido
                        color[v] = 1 - color[u];
                        queue[rear++] = v;
                    } else if (color[v] == color[u]) {
                        return false; // Mesmo grupo, não bipartido
                    }
                    temp = temp->next;
                }
            }
        }
    }
    return true;
}

// Função principal
int main() {
    int vertices = 6;

    Graph* graph = createGraph(vertices);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 3);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 4, 5);

    if (isBipartite(graph))
        printf("O grafo é bipartido.\n");
    else
        printf("O grafo não é bipartido.\n");

    return 0;
}
