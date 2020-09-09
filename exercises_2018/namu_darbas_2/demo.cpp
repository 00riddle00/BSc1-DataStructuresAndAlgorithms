
/*=============================================================================
 |
 |  Assignment:   Homework 2
 |
 |       Author:  Tomas Giedraitis
 |  Study group:  VU MIF INFO, 1st group
 |     Contacts:  tomasgiedraitis@gmail.com
 |        Class:  Algorithms and Data Structures
 |         Date:  March 18th, 2018
 |
 |     Language:  GNU C (using gcc on Lenovo Y50-70, OS: Arch Linux x86_64)
 |     Version:   0.0
 |
 +-----------------------------------------------------------------------------
 |
 |  Description:  Implementing containder (ADT) in a form of a tree
 |                
 |
 |	    Input:    Command line input by user
 |
 |	    Output:   Prompt messages, validation errors and final results
 |                are displayed one per line to the standard output.
 |              
 | Version
 | updates:     Currently this is the intial version
 |
 +===========================================================================*/

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

BstNode* GetNewNode(int data) {
    BstNode* newNode = (BstNode*) malloc(sizeof(BstNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}


// tree Insert
BstNode* tInsert(BstNode* root, int data) {
    if (root == NULL) { // empty tree
        root = GetNewNode(data);
    } else if (data <= root->data) {
        root->left = tInsert(root->left,data);
    }
    else {
        root->right = tInsert(root->right,data);
    }
    return root;
}



BstNode* Balance(BstNode* root, int first, int last) {

    if (last < first) {
        return root;
    } else if (last == first) {
        root = tInsert(root, array[first]); 
        return root;
    }

    int half = (last-first) / 2;
    int midIndex = first + half;
    root = tInsert(root, array[midIndex]); 
    root = Balance(root, first, midIndex-1);
    root = Balance(root, midIndex+1, last);

    return root;
}

BstNode* tSearch(BstNode* root, int data) {
    if (root == NULL)  return NULL;
    else if (root->data == data)  return root;
    else if (data <= root->data) return tSearch(root->left, data);
    else return tSearch(root->right, data);
}

int Search(int data) {
    if (tSearch(root, data) != NULL) {
        return 1;
    }
    return 0;
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

BstNode* tFindMin(BstNode* root) {
    if (root == NULL) {
        printf("Error: Tree is empty\n");
        return NULL;
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}




BstNode* FindMinRecursive(BstNode* root) {
    if (root == NULL) {
        printf("Error: Tree is empty\n");
        return NULL;
    } else if (root->left == NULL) {
        return root;
    }
    return FindMinRecursive(root->left);
}


BstNode* tFindMax(BstNode* root) {
    if (root == NULL) {
        printf("Error: Tree is empty\n");
        return NULL;
    }
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}


BstNode* FindMaxRecursive(BstNode* root) {
    if (root == NULL) {
        printf("Error: Tree is empty\n");
        return NULL;
    } else if (root->right == NULL) {
        return root;
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


int IsSubtreeLesser(BstNode *root, int value) {
    if (root == NULL) return 1;
    if (root->data <= value
            && IsSubtreeLesser(root->left, value)
            && IsSubtreeLesser(root->right, value))
        return 1;
    else
        return 0;
}

int IsSubtreeGreater(BstNode *root, int value) {
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
int IsBinarySearchTree1(BstNode* root) {
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
int IsBinarySearchTree2(BstNode* root, int minValue, int maxValue) {
    if (root == NULL) return 1;
    if (root->data > minValue
        && root->data < maxValue
        && IsBinarySearchTree2(root->left, minValue, root->data)
        && IsBinarySearchTree2(root->right, root->data, maxValue))
        return 1;
    else
        return 0;
}


BstNode* tDelete(BstNode* root, int data) {
    if (root == NULL) return root;
    else if(data < root->data) root->left = tDelete(root->left, data);
    else if(data > root->data) root->right = tDelete(root->right, data);
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
            BstNode* temp = (BstNode*)tFindMin(root->right);
            root->data = temp->data;
            root->right = tDelete(root->right, temp->data);
        }
    }
    return root;
}



 /*//TODO make it work*/
//Function to find Inorder Successor in a BST
BstNode* Getsuccessor(BstNode* root,int data) {
    // Search the Node - O(h)
    BstNode* current = tSearch(root,data);
    if(current == NULL) return NULL;
    if(current->right != NULL) {  //Case 1: Node has right subtree
        return tFindMin(current->right); // O(h)
    }
    else {   //Case 2: No right subtree  - O(h)
        BstNode* successor = NULL;
        BstNode* ancestor = root;
        while(ancestor != current) {
            if(current->data < ancestor->data) {
                successor = ancestor; // so far this is the deepest node for which current node is in left
                ancestor = ancestor->left;
            }
            else
                ancestor = ancestor->right;
        }
        return successor;
    }
}
 
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
void Enqueue(BstNode* x) {
	struct Node* temp = 
		(struct Node*)malloc(sizeof(struct Node));
	temp->data=x; 
	temp->next = NULL;
	if(front == NULL && rear == NULL){
		front = rear = temp;
		return;
	}
	rear->next = temp;
	rear = temp;
}

// To Dequeue an integer.
void Dequeue() {
	struct Node* temp = front;
	if(front == NULL) {
		printf("Queue is Empty\n");
		return;
	}
	if(front == rear) {
		front = rear = NULL;
	}
	else {
		front = front->next;
	}
	free(temp);
}

BstNode* Front() {
	if(front == NULL) {
		printf("Queue is empty\n");
		return NULL;
	}
	return front->data;
}

void PrintQueue() {
	struct Node* temp = front;
	while(temp != NULL) {
		printf("%d ",temp->data->data);
		temp = temp->next;
	}
	printf("\n");
}

/*-----------------------/Linked list implementation of queue ---------------------------------*/

/*-----------------------Tree implementation BFS---------------------------------*/

// Function to print Nodes in a binary tree in Level order (BFS)
void LevelOrder(BstNode *root) {
    if(root == NULL) return;
    //queue<Node*> Q;
    //Q.push(root);  
    Enqueue(root);
    //while there is at least one discovered node
	//while(!Q.empty()) {
    while(Front() != NULL) {
		//Node* current = Q.front();
        BstNode* current = Front();
        //Q.pop(); // removing the element at front
        Dequeue();
        printf("%d ", current->data);
        //if(current->left != NULL) Q.push(current->left);
        if(current->left != NULL) Enqueue(current->left);
        //if(current->right != NULL) Q.push(current->right);
        if(current->right != NULL) Enqueue(current->right);
    }
}

/*-----------------------/Tree implementation BFS---------------------------------*/

/*-----------------------UI wrapper---------------------------------*/
void Create() {
    root = NULL; // creating an empty tree
}

void Insert(int data) {
    root = tInsert(root, data);
}


void Delete(int data) {
    while (Search(data) != NULL) {
        root = tDelete(root, data);
    }
}

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


void Print() {
    Inorder(root);
    printf("\n");
}

//clear()
//destroy()

int FindMin() {
    return tFindMin(root)->data;
}

int FindMax() {
    return tFindMax(root)->data;
}

/*-----------------------/UI wrapper---------------------------------*/

int main() {
    Create();

    Insert(1);
    Insert(2);
    Insert(3);
    Insert(4);
    Insert(5);
    Insert(6);
    Insert(7);

    printf("My container:\n");
    Print();

    int res = Search(6);
    printf("Search result is %d\n", res);

    Delete(6);
    printf("My container:\n");
    Print();

    printf("Min elem is: %d\n", FindMin());
    printf("Max elem is: %d\n", FindMax());
    
}
