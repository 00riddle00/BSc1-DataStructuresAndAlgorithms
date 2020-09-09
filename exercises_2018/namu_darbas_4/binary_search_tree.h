#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

// Binary Search Tree 
// Simple implementation
// - GetNewNode
// - Insert
// - Search
// - FindMin
// - FindMax
// - FinHeight
// -Delete a Node

// Binary Search Tree Traversal
// - Preorder
// - Inorder
// - Postorder

// Binary Search Tree 
// - Check if a given BINARY tree is a binary search tree or not
// TODO check BST with inorder traversal
//
// TODO add DFS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>
// Useful debugging macros
#include "dbg.h"


/*-----------------------------BST implementation ---------------------------------*/

// global variable used for balancing tree
// TODO move it inside functions or as a struct member
int array[10];
int size = 0;

typedef struct BstNode {
    int data;
    struct BstNode *left;
    struct BstNode *right;
} BstNode;

BstNode* root; // root struct

BstNode* GetNewNode(int data);

// tree Insert
BstNode* tInsert(BstNode* root, int data);

BstNode* Balance(BstNode* root, int first, int last);

BstNode* tSearch(BstNode* root, int data);

int Search(int data);

void Preorder(BstNode *root);

void InorderFill(BstNode *root);

void Inorder(BstNode *root);

void Postorder(BstNode *root);

BstNode* tFindMin(BstNode* root);

BstNode* FindMinRecursive(BstNode* root);

BstNode* tFindMax(BstNode* root);

BstNode* FindMaxRecursive(BstNode* root);

// A recursive function to find tree heights.
// We get the height of the bigger subtree, and then 
// add 1. Adding 1 means counting the edge from the 
// starting node (root node) to the root node of the subtree.
int FindHeight(BstNode* root);

int IsSubtreeLesser(BstNode *root, int value);

int IsSubtreeGreater(BstNode *root, int value);

// Implementation 1
// FindMax/FindMin functions can be used instead of IsSubtreeLesser/IsSubtreeGreater
// Time complexity: O(n^2)
int IsBinarySearchTree1(BstNode* root);

// Implementation 2
// Using the range of values (every node is checked only once)
// Time complexity: O(n)
int IsBinarySearchTree2(BstNode* root, int minValue, int maxValue);

BstNode* tDelete(BstNode* root, int data);

 /*//TODO make it work*/
//Function to find Inorder Successor in a BST
BstNode* Getsuccessor(BstNode* root,int data);
 
/*----------------------------/BST implementation ---------------------------------*/

/*-----------------------------Linked list implementation of queue ---------------------------------*/

struct Node {
    BstNode* data;
	struct Node* next;
};
// Two glboal variables to store address of front and rear nodes. 
struct Node* front = NULL;
struct Node* rear = NULL;

// To Enqueue an BSTNode
void Enqueue(BstNode* x);

// To Dequeue an integer.
void Dequeue();

BstNode* Front();

void PrintQueue();

/*-----------------------/Linked list implementation of queue ---------------------------------*/

/*-----------------------Tree implementation BFS---------------------------------*/

// Function to print Nodes in a binary tree in Level order (BFS)
void LevelOrder(BstNode *root);
/*-----------------------/Tree implementation BFS---------------------------------*/

/*-----------------------UI wrapper---------------------------------*/
void Create();

void Insert(int data);

void Delete(int data);

/*DeletePos*/
//DeleteFirst
//DeleteLast

//get(pos)
//getFirst()
//getLast()
//get(val)

//getSize()
//getMaxSize()

//edit(old, new)
//next(current)
//prev(current)


void Print();

//clear()
//destroy()

int FindMin();

int FindMax();

#endif

