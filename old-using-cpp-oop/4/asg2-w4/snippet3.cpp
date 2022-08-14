//
// Created by Hanry Ham on 2020-05-25.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct storage
{
    int qty;
    char name[25];
    char category[20];
    struct storage *left;
    struct storage *right;
};

struct storage *newNode(const char *name, const char *category)
{
    struct storage *curr = (struct storage *)malloc(sizeof(struct storage));
    curr->qty = 1;
    strcpy(curr->name, name);
    strcpy(curr->category, category);
    curr->left = NULL;
    curr->right = NULL;
    return curr;
}

struct storage *insert(struct storage *root, const char *name, const char *category)
{
    // [10%] (1) INSERT YOUR CODE HERE
    if (root == NULL)
    {
        return newNode(name, category);
    }
    if ( strcmp(name, root->name) < 0 )
    {
        root->left = insert(root->left, name, category);
    }
    else if ( strcmp(name, root->name) > 0 )
    {
        root->right = insert(root->right, name, category);
    }else
    {
        root->qty++;
    }
    
    
    
    return root;
}

struct storage *predecessor(struct storage *root)
{
    // [5%] (2) INSERT YOUR CODE HERE
    if (root->left != NULL)
    {
        storage *tmp = root->left;
        while (tmp->right)
            tmp = tmp->right;
        return tmp;
    }
}

struct storage *successor(struct storage *root)
{
    // [5%] (3) INSERT YOUR CODE HERE
    if (root->right != NULL)
    {
        storage *tmp = root->right;
        while (tmp->left)
            tmp = tmp->left;
        return tmp;
    }
}

struct storage *deleteKey(struct storage *root, const char *name)
{
    // [15%] (4) INSERT YOUR CODE HERE
    if (root == NULL)
        return root;
    
    if ( strcmp(name, root->name) < 0 )
    {
        root->left = deleteKey(root->left, name);
    }
    else if ( strcmp(name,root->name) > 0 )
    {
        root->right = deleteKey(root->right, name);
    }
    else
    {
        if ( root->qty > 1 )
        {
            root->qty--;
        }
        else
        {
            if (root->left == NULL)
            {
                storage *temp = root->right;
                free(root);
                return temp;
            }
            else if (root->right == NULL)
            {
                storage *temp = root->left;
                free(root);
                return temp;
            }
            else
            {
                storage *temp = predecessor(root);
                strcpy(root->name, temp->name);
                strcpy(root->category, temp->category);
                root->qty = temp->qty;
                temp->qty = 1;

                root->left = deleteKey(root->left, temp->name);
            }
        }
    }
    return root;
}

void inOrder(struct storage *root)
{
    if (root)
    {
        // [5%] (5) INSERT YOUR CODE HERE
        inOrder(root->left);
        printf("%-10s(%-3d)\n", root->name, root->qty);
        inOrder(root->right);
    }
}

struct storage *freeAll(struct storage *root)
{
    if (root)
    {
        freeAll(root->left);
        freeAll(root->right);
        free(root);
        root = NULL;
    }
    return root;
}

int main()
{
    struct storage *root = NULL;

    root = insert(root, "Sate Ayam", "Daging");
    root = insert(root, "Gulai Kambing", "Daging");
    root = insert(root, "Kangkung", "Sayuran");
    root = insert(root, "Coca Cola", "Minuman");
    root = insert(root, "Sate Kambing", "Daging");
    root = insert(root, "Opor Ayam", "Daging");
    root = insert(root, "Sprite", "Minuman");
    root = insert(root, "Fanta", "Minuman");
    root = insert(root, "Ayam Kalasan", "Daging");
    root = insert(root, "Kangkung", "Sayuran");
    root = insert(root, "Fanta", "Minuman");
    root = insert(root, "Coca Cola", "Minuman");
    root = insert(root, "Opor Ayam", "Daging");

    printf("Predecessor : %s\n", predecessor(root)->name);
    printf("Successor : %s\n", successor(root)->name);

    printf("\nInorder : \n");
    inOrder(root);

    root = deleteKey(root, "Sate Ayam");
    root = deleteKey(root, "Gulai Kambing");
    root = deleteKey(root, "Coca Cola");
    root = deleteKey(root, "Opor Ayam");
    root = deleteKey(root, "Sate Kambing");
    root = deleteKey(root, "Ayam Kalasan");
    printf("\nAfter Del Inorder : \n");
    inOrder(root);

    freeAll(root);
    return 0;
}
