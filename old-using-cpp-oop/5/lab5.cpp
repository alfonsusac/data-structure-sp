#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node1
{
    char name[150];
    Node1 *left, *right;
};

Node1* createNewNode(char *name)
{
    Node1 *newNode = (Node1 *)malloc(sizeof(Node1));
    strcpy(newNode->name, name);
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node1* insert(Node1 *curr, char *name)
{
    if (!curr)
    {
        return createNewNode(name);
    }
    else if (strcmp(name, curr->name) < 0)
    {
        curr->left = insert(curr->left, name);
    }
    else if (strcmp(name, curr->name) > 0)
    {
        curr->right = insert(curr->right, name);
    }
    // same value
    return curr;
}

void preOrder(Node1 *curr)
{
    if(!curr)
        return;

    printf("%s\n", curr->name);
    preOrder(curr->left);
    preOrder(curr->right);
}

void inOrder(Node1 *curr)
{
    if (!curr)
        return;

    inOrder(curr->left);
    printf("%s\n", curr->name);
    inOrder(curr->right);
}

int main()
{
    Node1 *root = NULL;
    root = insert(root, (char *)"Alfon");
    root = insert(root, (char *)"Winston");
    root = insert(root, (char *) "Parama");

    inOrder(root);
    puts("\n\n");
    preOrder(root);
}