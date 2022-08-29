#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Bikin Heap

struct Node {
    char name[100];
    Node *left, *right;
};

int max(int a, int b){
    return a > b ? a : b;
}

int getHeight(Node *root){
    if(root == NULL) return 0;
    return 1 + max(getHeight(root->left), getHeight(root->right));
}

int getBalanceFactor(Node *root){
    return getHeight(root->left) - getHeight(root->right);
}



int main(){

    return 0;
}