// Binary Search Tree Traversal
// - Preorder
// - Inorder
// - Postorder

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

int Search(BstNode* root, int data) {
    if (root == NULL)  return 0;
    else if (root->data == data)  return 1;
    else if (data <= root->data) return Search(root->left, data);
    else return Search(root->right, data);
}

void Preorder(BstNode *root) {
    if (root == NULL) return;

    printf("%d ", root->data);
    Preorder(root->left);
    Preorder(root->right);
}

void Inorder(BstNode *root) {
    if (root == NULL) return;

    Inorder(root->left);
    printf("%d ", root->data);
    Inorder(root->right);
}

void Postorder(BstNode *root) {
    if (root == NULL) return;

    Postorder(root->left);
    Postorder(root->right);
    printf("%d ", root->data);
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
    Inorder(root);
    printf("\n");
    Postorder(root);
    printf("\n");
}

