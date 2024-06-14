/*Done By M.Harish AIML A 231501058*/
#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 100

int minDistance(int dist[], int sptSet[], int vertices) {
    int min = INT_MAX, minIndex;
    for (int v = 0; v < vertices; v++) {
        if (!sptSet[v] && dist[v] < min) {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void printSolution(int dist[], int vertices) {
    printf("Vertex \tDistance from Source\n");
    for (int i = 0; i < vertices; i++) {
        printf("%d \t%d\n", i, dist[i]);
    }
}

void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int src, int vertices) {
    int dist[MAX_VERTICES];
    int sptSet[MAX_VERTICES];
    
    for (int i = 0; i < vertices; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }
    
    dist[src] = 0;
    
    for (int count = 0; count < vertices - 1; count++) {
        int u = minDistance(dist, sptSet, vertices);
        sptSet[u] = 1;
        
        for (int v = 0; v < vertices; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    
    printSolution(dist, vertices);
}

int main() {
    int vertices = 5;
    
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 10, INT_MAX, 30, 100},
        {10, 0, 50, INT_MAX, INT_MAX},
        {INT_MAX, 50, 0, 20, 10},
        {30, INT_MAX, 20, 0, 60},
        {100, INT_MAX, 10, 60, 0}
    };
    
    int source = 0;
    
    dijkstra(graph, source, vertices);
    return 0;
}
/*Done By M.Harish AIML A 231501058*/