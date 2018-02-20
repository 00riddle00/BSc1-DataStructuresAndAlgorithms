// Binary Search Tree 
// Simple implementation
// - GetNewNode
// - Insert
// - Search
// - FindMin
// - FindMax
// - FinHeight

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

int FindMin(BstNode* root) {
    if (root == NULL) {
        printf("Error: Tree is empty\n");
        return -1;
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root->data;
}

int FindMinRecursive(BstNode* root) {
    if (root == NULL) {
        printf("Error: Tree is empty\n");
        return -1;
    } else if (root->left == NULL) {
        return root->data;
    }
    return FindMinRecursive(root->left);
}

int FindMax(BstNode* root) {
    if (root == NULL) {
        printf("Error: Tree is empty\n");
        return -1;
    }
    while (root->right != NULL) {
        root = root->right;
    }
    return root->data;
}

int FindMaxRecursive(BstNode* root) {
    if (root == NULL) {
        printf("Error: Tree is empty\n");
        return -1;
    } else if (root->right == NULL) {
        return root->data;
    }
    return FindMaxRecursive(root->right);
}

// A recursive function to find tree heights.
// We get the height of the bigger subtree, and then 
// add 1. Adding 1 means counting the edge from the 
// starting node (root node) to the root node of the subtree.
int FindHeight(BstNode* root) {
    if (root == NULL) {
        // we return -1 to make the total height equal to 0
        // since we are adding 1 afterwards, but if there is no 
        // subtree, hence there is no edge between the root and 
        // the root of the subtree
        return -1; 
    }
    return fmax(FindHeight(root->left),FindHeight(root->right))+1;
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


    // Number to be searched
    int number;
    number = 20;

    if ( Search(root,number) == 1) printf("Found\n");
    else printf("Not Found\n");
    
    printf("Min elem is: %d\n", FindMin(root));
    printf("Max elem is: %d\n", FindMax(root));

    printf("Using recursion, Min elem is: %d\n", FindMinRecursive(root));
    printf("Using recursion, Max elem is: %d\n", FindMaxRecursive(root));

    printf("Height of the tree is: %d\n", FindHeight(root));
}

