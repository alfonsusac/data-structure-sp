#include "util.h"
#define MAX 255

int parent[MAX] = {-1};

STRUCT Edge{
    int src, dest;
}Edge;

STRUCT Graph{
    int vertices;
    int edges;
    Edge *edge;
}Graph;

Graph *createGraph(int vertices_count, int edges_count){
    new_struct(Graph, new_graph);
    new_graph->vertices = vertices_count;
    new_graph->edges = edges_count;
    new_graph->edge = memalloc(Edge);
    return new_graph;
}

void createSet( int vertexCount){
    for( range(vertexCount) ){
        parent[i] = i;
    }
}

int findParent( int vertex){
    if( parent[vertex] == vertex )
        return vertex;
    return findParent(parent[vertex]);
}

void join( int vertA, int vertB){
    int parent_vertA = findParent(vertA);
    int parent_vertB = findParent(vertB);
    parent[parent_vertA] = parent_vertB;
}

bool isSameSet( int vertA, int vertB){
    if( findParent(vertA) == findParent(vertB) ){
        return true;
    }
    return false;
}

bool joinGraph(Graph *graph){
    for( range(graph->edges) ){
        int parent_source = findParent(graph->edge[i].src);
        int parent_dest = findParent(graph->edge[i].dest);

        printf("%d %d\n", parent_source, parent_dest);
        if( parent_source == parent_dest ){
            return true;
        }
        parent[parent_source] = parent_dest;   
    }
    return false;
}

bool isCyclic(Graph *graph){
    createSet(graph->vertices);
    return joinGraph(graph);
}

int main(){
    Graph *graph = createGraph(4, 4);
    graph->edge[0] = (Edge){0, 2};  
    graph->edge[0] = (Edge){2, 1};  
    graph->edge[0] = (Edge){1, 3};  
    graph->edge[0] = (Edge){0, 1};  

    if( isCyclic(graph) ){
        puts("Cyclic!");
    }else{
        puts("Not cyclic!");
    }

    for( range(4) ){
        printf("%d ", parent[i]);
    }

    return 0;
}