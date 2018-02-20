// Binary Search Tree 
// - Check if a given BINARY tree is a binary search tree or not
// TODO check BST with inorder traversal

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node* GetNewNode(int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* Insert(Node* root, int data) {
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

void Preorder(Node *root) {
    if (root == NULL) return;

    printf("%d ", root->data);
    Preorder(root->left);
    Preorder(root->right);
}

void Inorder(Node *root) {
    if (root == NULL) return;

    Inorder(root->left);
    printf("%d ", root->data);
    Inorder(root->right);
}


int IsSubtreeLesser(Node *root, int value) {
    if (root == NULL) return 1;
    if (root->data <= value
            && IsSubtreeLesser(root->left, value)
            && IsSubtreeLesser(root->right, value))
        return 1;
    else
        return 0;
}

int IsSubtreeGreater(Node *root, int value) {
    if (root == NULL) return 1;
    if (root->data > value
            && IsSubtreeGreater(root->left, value)
            && IsSubtreeGreater(root->right, value))
        return 1;
    else
        return 0;
}


// Implementation 1
// FindMax/FindMin functions can be used instead of IsSubtreeLesser/IsSubtreeGreater
// Time complexity: O(n^2)
int IsBinarySearchTree1(Node* root) {
    if (root == NULL) return 1;
    if (IsSubtreeLesser(root->left, root->data)
        && IsSubtreeGreater(root->right, root->data)
        && IsBinarySearchTree1(root->left)
        && IsBinarySearchTree1(root->right))
        return 1;
    else
        return 0;
}

// Implementation 2
// Using the range of values (every node is checked only once)
// Time complexity: O(n)
int IsBinarySearchTree2(Node* root, int minValue, int maxValue) {
    if (root == NULL) return 1;
    if (root->data > minValue
        && root->data < maxValue
        && IsBinarySearchTree2(root->left, minValue, root->data)
        && IsBinarySearchTree2(root->right, root->data, maxValue))
        return 1;
    else
        return 0;
}





int main() {
    Node* root = NULL; // creating an empty tree

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

    /*int res = IsBinarySearchTree1(root);*/
    int res = IsBinarySearchTree2(root, INT_MIN, INT_MAX);
    printf("res: %d\n", res);

    root->right->data = 11;

    Preorder(root);
    printf("\n");

    /*res = IsBinarySearchTree1(root);*/
    res = IsBinarySearchTree2(root, INT_MIN, INT_MAX);
    printf("res: %d\n", res);

}

