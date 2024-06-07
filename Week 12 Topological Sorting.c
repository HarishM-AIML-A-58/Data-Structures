#include <stdio.h>
#include <malloc.h>

struct node {
    int vertex;
    struct node* next;
};

struct Graph {
    int numVertices;
    struct node** adjLists;
    int* visited;
};

struct node* createNode(int v) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = (struct node**)malloc(vertices * sizeof(struct node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

void topologicalSortUtil(int v, struct Graph* graph, int* stack, int* stackIndex) {
    graph->visited[v] = 1;

    struct node* adjList = graph->adjLists[v];
    struct node* temp = adjList;

    while (temp != NULL) {
        int connectedVertex = temp->vertex;
        if (!graph->visited[connectedVertex]) {
            topologicalSortUtil(connectedVertex, graph, stack, stackIndex);
        }
        temp = temp->next;
    }

    stack[(*stackIndex)++] = v;
}

void topologicalSort(struct Graph* graph) {
    int* stack = (int*)malloc(graph->numVertices * sizeof(int));
    int stackIndex = 0;

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->visited[i] == 0) {
            topologicalSortUtil(i, graph, stack, &stackIndex);
        }
    }

    for (int i = stackIndex - 1; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
    free(stack);
}

int main() {
    struct Graph* graph = createGraph(6);
    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    printf("Topological Sort: ");
    topologicalSort(graph);
    printf("\n");

    return 0;
}
