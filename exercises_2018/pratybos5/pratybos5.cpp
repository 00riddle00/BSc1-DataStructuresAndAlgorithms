
/*=============================================================================
 |
 |  Assignment:   Exercise 5
 |
 |       Author:  Tomas Giedraitis
 |  Study group:  VU MIF INFO, 1st group
 |     Contacts:  tomasgiedraitis@gmail.com
 |        Class:  Algorithms and Data Structures
 |         Date:  March 6th, 2018
 |
 |     Language:  GNU C (using gcc on Lenovo Y50-70, OS: Arch Linux x86_64)
 |     Version:   0.0
 |
 +-----------------------------------------------------------------------------
 |
 |  Description:  Implementing BST with balance function 
 |                
 |
 |	    Input:    Command line input by user
 |
 |	    Output:   Prompt messages, validation errors and final results
 |                are displayed one per line to the standard output.
 |              
 |
 | Version
 | updates:     Currently this is the intial version
 |
 +===========================================================================*/

// Binary Search Tree Traversal
// - Preorder
// - Inorder
// - Postorder

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//#define TIMES 2000000000
#define TIMES 200000000

clock_t begin;
clock_t end;

double clocks;
double time_spent;

// global variable used for balancing tree
// TODO move it inside functions or as a struct member
int array[10];
int size = 0;

typedef struct BstNode {
    int data;
    struct BstNode *left;
    struct BstNode *right;
} BstNode;

BstNode* GetNewNode(int data) {
    BstNode* newNode = (BstNode*) malloc(sizeof(BstNode));
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


BstNode* Balance(BstNode* root, int first, int last) {

    if (last < first) {
        return root;
    } else if (last == first) {
        root = Insert(root, array[first]); 
        return root;
    }

    int half = (last-first) / 2;
    int midIndex = first + half;
    root = Insert(root, array[midIndex]); 
    root = Balance(root, first, midIndex-1);
    root = Balance(root, midIndex+1, last);

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


void InorderFill(BstNode *root) {
    if (root == NULL) return;

    InorderFill(root->left);
    array[size++] = root->data;
    InorderFill(root->right);
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

    root = Insert(root, 1);
    root = Insert(root, 2);
    root = Insert(root, 3);
    root = Insert(root, 4);
    root = Insert(root, 5);
    root = Insert(root, 6);
    root = Insert(root, 7);

    /* the resulting tree:
     *
                  1
                   \
                    2
                     \
                      3
                       \
                        4
                         \
                          5
                           \
                            6
                             \
                              7

    */

    printf("Printing preorder (unbalanced):\n");
    Preorder(root);
    printf("\n\n");


    printf("Repetition times: %d\n", TIMES);

    // Test assignment time

    begin = clock();
    int res;

    for (int i = 0; i < TIMES; ++i) {
        res = i;
    }

    end = clock();

    clocks = (double)(end - begin);
    time_spent = clocks / CLOCKS_PER_SEC;
    clock_t assignment = time_spent;

    printf("Assignment time: %f clocks, %f seconds\n", clocks, time_spent);

    // Test BST search (unbalanced)

    begin = clock();

    int found;

    for (int i = 0; i < TIMES; ++i) {
        found = Search(root, 6);
    }
    end = clock();

    clocks = (double)(end - begin);
    time_spent = clocks / CLOCKS_PER_SEC - assignment;

    printf("\nTest search (not balanced): %f seconds\n", time_spent);

    /* Balance BST  */
    // Fill array (global var) with BST elements listed inorder
    InorderFill(root);

    // clear the BST before balancing
    root = NULL;

    root = Balance(root, 0, size-1);
    
    /* the resulting (balanced) tree:

                 4
               /  \
             2      6
           /  \   /  \
         1     3 5    7
    */


    printf("\n");
    printf("Printing preorder (balanced):\n");
    Preorder(root);
    printf("\n\n");

    // Test BST search (balanced)
    begin = clock();

    for (int i = 0; i < TIMES; ++i) {
        found = Search(root, 6);
    }
    end = clock();

    clocks = (double)(end - begin);
    time_spent = clocks / CLOCKS_PER_SEC - assignment;

    printf("Test search (balanced): %f seconds\n", time_spent);

}
