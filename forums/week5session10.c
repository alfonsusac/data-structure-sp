#include "util.h"

#define MAX_HEAP_NODES 31

void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

int leftChild(int curr){
    return 2 * curr + 1;
}

int rightChild(int curr){
    return 2 * curr + 2;
}

STRUCT Heap{
    int head[MAX_HEAP_NODES];
    int count;
}Heap;

void heapify_from_end(Heap *heap){
    int curr = heap->count - 1;
    while (heap->head[curr] != heap->head[0]) {
        curr = (curr - 1) / 2;
        int *largest = 0;
        if (heap->head[leftChild(curr)] > heap->head[curr])
            largest = &heap->head[leftChild(curr)];
        if (heap->head[rightChild(curr)] > heap->head[curr])
            largest = &heap->head[rightChild(curr)];
        if (largest != 0)
            swap(largest, &heap->head[curr]);
    }
}

void insert_to_heap(Heap *heap, int input){


    heap->head[heap->count] = input;
    heap->count++;

    if( heap->count > 1 ){
        heapify_from_end(heap);
    }

}

void show_heap_tree(Heap *heap){

    put("                                     "); // 37
    if( heap->head[0] == 0 ) put(" NL");
    else put("%3d", heap->head[0]);
    put("                                     "); // 18 1 18
    put("\n");

    put("                  "); // 18
    for( range(1, 3) ){
        if( heap->head[i] == 0 ) put(" NL");
        else put("%3d", heap->head[i]);
        put("                                     "); // 18 1 18
    } put("\n");

    put("        "); // 8
    for( range(3, 7) ){
        if( heap->head[i] == 0 ) put(" NL");
        else put("%3d", heap->head[i]);
        put("                 "); // 818
    } put("\n");

    put("   "); // 3
    for( range(7, 15) ){
        if( heap->head[i] == 0 ) put(" NL");
        else put("%3d", heap->head[i]);
        put("       "); // 313
    } put("\n");

    for( range(15, 31) ){ // 0
        if( heap->head[i] == 0 ) put(" NL");
        else put("%3d", heap->head[i]);
        put("  "); // 2
    } put("\n");
}

void heapify_all(Heap *heap, int index){
    int largest = index; // largest is root
    if ( heap->head[leftChild(index)] > heap->head[largest] )
        largest = leftChild(index);
    if ( heap->head[rightChild(index)] > heap->head[largest] )
        largest = rightChild(index);
    if( largest != index ){
        swap(&heap->head[largest], &heap->head[index]);
        heapify_all(heap, largest);
    }
}

void delete_root_of_heap(Heap *heap){
    swap(&heap->head[0], &heap->head[heap->count - 1]);

    heap->head[heap->count - 1] = 0;
    heap->count--;

    if( heap->count > 1 ){
        heapify_all(heap,0);
    }
}

void _menu_insert(Heap *heap){
    int input;
    validate(getint("Input your data [1-100]: ", input), between(input, 1, 100));
    insert_to_heap(heap, input);
    getenter("Insert Success");
}

void _menu_view(Heap *heap){
    putl("Only 5 levels shown");
    show_heap_tree(heap);
    getenter(" ");
}

void _menu_pop(Heap *heap){
    if( heap->head[0] == 0 ){
        getenter("There is no data");
    }else{
        delete_root_of_heap(heap);
        getenter("Delete Success");
    }
}

int main(){
    // Initialization
    new_struct(Heap, heap); // horray
    for( range(MAX_HEAP_NODES) ) heap->head[i] = 0;
    heap->count = 0;

    insert_to_heap(heap, 60);
    insert_to_heap(heap, 90);
    insert_to_heap(heap, 32);
    insert_to_heap(heap, 95);
    insert_to_heap(heap, 75);
    insert_to_heap(heap, 76);

    // Execution
    bool running = true;
    while( running ){
        clr();
        putl("MAX HEAP TREE");
        putl("=============");
        putl("1. Insert");
        putl("2. View");
        putl("3. Pop");
        putl("4. Exit");

        int choice = 0;
        getint("Choice: ", choice);

        if( choice == 1 ) _menu_insert(heap);
        else if( choice == 2 ) _menu_view(heap);
        else if( choice == 3 ) _menu_pop(heap);
        else if( choice == 4 ) running = false;

    }

    free(heap);
}