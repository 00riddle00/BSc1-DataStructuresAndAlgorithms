// Binary Search Tree 
// - Delete a Node

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct BstNode {
    int data;
    struct BstNode *left;
    struct BstNode *right;
} BstNode;

BstNode* GetNewNode(int data) {
    BstNode* newNode = malloc(sizeof(BstNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}


BstNode* Insert(BstNode* root, int data) {
    if (root == NULL) { // empty tree
        root = GetNewNode(data);
    } else if (data <= root->data) {
        root->left = Insert(root->left,data);
    }
    else {
        root->right = Insert(root->right,data);
    }
    return root;
}

BstNode* FindMin(BstNode* root) {
    if (root == NULL) {
        printf("Error: Tree is empty\n");
        return NULL;
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

void Preorder(BstNode *root) {
    if (root == NULL) return;

    printf("%d ", root->data);
    Preorder(root->left);
    Preorder(root->right);
}

BstNode* Delete(BstNode* root, int data) {
    if (root == NULL) return root;
    else if(data < root->data) root->left = Delete(root->left, data);
    else if(data > root->data) root->right = Delete(root->right, data);
    else { // Wohoo... I found you, Get ready to be deleted

        // Case 1: No child
        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        }
        // Case 2: One child
        else if (root->left == NULL) {
            BstNode* temp = root;
            root = root->right;
            free(temp);
        }
        else if (root->right == NULL) {
            BstNode* temp = root;
            root = root->left;
            free(temp);
        }
        // Case 3: 2 children
        else {
            BstNode* temp = FindMin(root->right);
            root->data = temp->data;
            root->right = Delete(root->right, temp->data);
        }
    }
    return root;
}

int main() {
    BstNode* root = NULL; // creating an empty tree
    root = Insert(root, 15);
    root = Insert(root, 10);
    root = Insert(root, 20);
    root = Insert(root, 25);
    root = Insert(root, 8);
    root = Insert(root, 12);

    /* the resulting tree:
                15
               /  \
            10     20
           /  \      \
         8    12      25
    */

    Preorder(root);
    printf("\n");

    root = Delete(root, 12);

    Preorder(root);
    printf("\n");
}

