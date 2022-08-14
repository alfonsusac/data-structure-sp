//
// Created by Hanry Ham on 2020-05-24.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct storage
{
    char name[25];
    char category[20];
};
const int tableSize = 7;
struct storage hashTable[tableSize];

void init()
{
    for (int i = 0; i < tableSize; i++)
    {
        strcpy(hashTable[i].name, "");
        strcpy(hashTable[i].category, "");
    }
}

int generateKey(const char *name)
{
    int key;
    key = name[0] - 'A';
    return key % tableSize;
}

int linearProbing(int key)
{
    // [15%] (1) INSERT YOUR CODE HERE
    int remaining = tableSize;

    while ( hashTable[key % tableSize].name[0] != NULL && remaining != 0)
    {
        key = (key + 1) % tableSize;
        remaining--;
    }
    if (remaining == 0)
    {
        return -1;
    }
    
    return key;
}

void insert(const char *name, const char *category)
{
    // [15%] (2) INSERT YOUR CODE HERE
    int key = linearProbing(generateKey(name));
    if (key != -1)
    {
        strcpy(hashTable[key].name, name);
        strcpy(hashTable[key].category, category);
    }else
    {
        printf("The hashTable is full!\n");
    }
    
    
}

void printAll()
{
    for (int i = 0; i < tableSize; i++)
    {
        printf("[%2d] : ", i);
        if (strcmp(hashTable[i].name, "") != 0)
        {
            printf("%s", hashTable[i].name);
        }
        else
        {
            printf("NULL");
        }
        printf("\n");
    }
}

int main()
{
    init();
    insert("Sate Ayam", "Daging");
    insert("Gulai Kambing", "Daging");
    insert("Kangkung", "Sayuran");
    insert("Coca Cola", "Minuman");
    insert("Sate Kambing", "Daging");
    insert("Opor Ayam", "Daging");
    insert("Sprite", "Minuman");
    insert("Fanta", "Minuman");
    insert("Ayam Kalasan", "Daging");
    printAll();
    return 0;
}
