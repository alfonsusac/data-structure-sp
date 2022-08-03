//
// Created by Hanry Ham on 2020-05-24.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define tableSize 29

struct storage
{
    int key;
    int qty;
    char name[25];
    char category[20];
    struct storage *next;
};

struct hashPool
{
    struct storage *head;
    struct storage *tail;
};
struct hashPool hashTable[tableSize];

void init()
{
    for (int i = 0; i < tableSize; i++)
    {
        hashTable[i].head = NULL;
        hashTable[i].tail = NULL;
    }
}

int generateKey(char *name)
{
    int key = 0;
    int len = strlen(name);
    // [10%] (1) INSERT YOUR CODE HERE
    for (size_t i = 0; i < len; i++)
    {
        key += name[i];
    }
    key = key % tableSize;
    return key;
}

struct storage *newNode(char *name, char *category)
{
    struct storage *curr = (struct storage *)malloc(sizeof(struct storage));
    curr->key = generateKey(name);
    curr->qty = 1;
    strcpy(curr->name, name);
    strcpy(curr->category, category);
    curr->next = NULL;
    return curr;
}

struct storage *searchNode(struct storage *node)
{
    struct storage *search = hashTable[node->key].head;
    struct storage *temp = NULL;
    // [10%] (2) INSERT YOUR CODE HERE

    while (search != NULL)
    {
        if (strcmp(search->name,node->name) == 0
        && strcmp(search->category, node->category) == 0)
        {
            temp = search;
        }
        search = search->next;
    }
    return temp;
}

void push(struct storage *node)
{
    // [10%] (3) INSERT YOUR CODE HERE

    struct storage *temp = searchNode(node);

    if (temp)
    {
        temp->qty++;
    }
    else if (hashTable[node->key].head == NULL)
    {
        hashTable[node->key].head = node;
        hashTable[node->key].tail = node;
    }
    else if (hashTable[node->key].head != NULL)
    {
        struct storage *curr = hashTable[node->key].head;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = node;
        hashTable[node->key].tail = node;
    }
}

void printAll()
{
    for (int i = 0; i < tableSize; i++)
    {
        printf("[%2d] : ", i);
        struct storage *curr = hashTable[i].head;
        while (curr != NULL)
        {
            printf("%-10s (%-3d) -> ", curr->name, curr->qty);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

int main()
{
    init();
    push(newNode("Sate Ayam", "Daging"));
    push(newNode("Sate Ayam", "Daging"));
    push(newNode("Gulai Kambing", "Daging"));
    push(newNode("Kangkung", "Sayuran"));
    push(newNode("Sate Ayam", "Daging"));
    push(newNode("Coca Cola", "Minuman"));
    push(newNode("Sate Ayam", "Daging"));
    push(newNode("Coca Cola", "Minuman"));
    push(newNode("Gulai Kambing", "Daging"));
    push(newNode("Sate Kambing", "Daging"));
    push(newNode("Opor Ayam", "Daging"));
    push(newNode("Sate Kambing", "Daging"));
    push(newNode("Sate Kambing", "Daging"));
    printAll();
    return 0;
}
