#include <stdlib.h>

// [0]------[3]
//  | \
//  |  [2]
//  | /
// [1]

typedef struct node{
    int a;
    int b;
    struct node *next;
} node;

node* createNode(int a, int b){
    node *new_node = (node *)malloc(sizeof(node *));
    new_node->next = 0;
    new_node->a = a;
    new_node->b = b;
    return new_node;
}

typedef struct adjacencyList{
    node *head;
    int edge;
} adjacencyList;

adjacencyList* createAdjacencyList(){
    adjacencyList *new_adjacencyList = (adjacencyList *)malloc(sizeof(new_adjacencyList));
    new_adjacencyList->head = 0;
    new_adjacencyList->edge = 0;
}

void insertNode(adjacencyList* list, int a, int b)
{
    node *new_node = createNode(a, b);
    new_node->next = list->head;
    list->head = new_node;
    list->edge++;
}

int main(){

    #define nodeCount 4
    int adjacencyMatrix[nodeCount][nodeCount] = {
        // [0], [1], [2], [3]
        {   0 ,  1 ,  1 ,  1  }, // [0]
        {   1 ,  0 ,  1 ,  0  }, // [1]
        {   1 ,  1 ,  0 ,  0  }, // [2]
        {   1 ,  0 ,  0 ,  0  }  // [3]
    };


    node *head = 0;
    insertNode(&head, 0, 1);
    insertNode(&head, 0, 2);
    insertNode(&head, 0, 3);
    insertNode(&head, 1, 2);

    return 0;
}
