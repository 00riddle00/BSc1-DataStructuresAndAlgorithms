/*=============================================================================
 |
 |  Assignment:  Exercise 10
 |
 |       Author:  Tomas Giedraitis
 |  Study group:  VU MIF INFO, 1st group
 |     Contacts:  tomasgiedraitis@gmail.com
 |        Class:  Algorithms and Data Structures
 |         Date:  May 4th, 2017
 |
 |     Language:  GNU C (using gcc on Lenovo Y50-70, OS: Arch Linux x86_64)
 |     Version:   0.0
 |
 +-----------------------------------------------------------------------------
 |
 |  Description:  Represent a Graph by using an Adjacency Matrix method
 |                Implement graph drawing and finding isomorphism between graphs
 |                
 |	    Input:    Command line input by user
 |
 |	    Output:   Prompt messages, validation errors and final results
 |                are displayed one per line to the standard output.
 | Version
 | updates:      Currently this is the intial version
 |
 +===========================================================================*/

#include <stdio.h>
#include <curses.h>
#include <string.h>

#include "dbg.h"
#include "helpers.h"

typedef struct Graph {
    int adj_mat[50][50];
    char name[20];
    char type[20];
    unsigned int vertice_count;
} Graph;

static Graph graphs[10];
static unsigned int size;

void print_dir_graph_vertices(unsigned int index) {

    printf("\n\n----------------------------------\n");
    printf("Printing graph's vertice degrees \"%s\" (%s)\n\n", graphs[index].name, graphs[index].type);

    unsigned int i, j, in_deg, out_deg;
    unsigned int n = graphs[index].vertice_count;

	printf("\n Vertex \t In_Degree \t Out_Degree \t Total_Degree ");

	for (i = 1; i <= n ; i++ ) {
		in_deg = out_deg = 0;
		for ( j = 1 ; j <= n ; j++ ) {
			if ( graphs[index].adj_mat[j][i] == 1 ) {
				in_deg++;
            }
		} 
		for ( j = 1 ; j <= n ; j++ ) {
			if (graphs[index].adj_mat[i][j] == 1 ) {
				out_deg++;
            }
        }
		printf("\n\n %5d\t\t\t%d\t\t%d\t\t%d\n\n",i,in_deg,out_deg,in_deg+out_deg);
	} 
    printf("----------------------------------\n");
	return;
} 

void print_undir_graph_vertices(unsigned int index) {

    unsigned int i, j, deg;
    unsigned int n = graphs[index].vertice_count;

    printf("\n\n----------------------------------\n");
    printf("Printing graph's vertice degrees \"%s\" (%s)\n\n", graphs[index].name, graphs[index].type);

	printf("\n Vertex \t Degree ");

	for ( i = 1 ; i <= n ; i++ ) {
		deg = 0;
		for ( j = 1 ; j <= n ; j++ ) {
			if ( graphs[index].adj_mat[i][j] == 1) {
				deg++;
            }
        }
		printf("\n\n %5d \t\t %d\n\n", i, deg);
	} 
    printf("----------------------------------\n");
} 

void read_graph(unsigned int index) {

	unsigned int i, j;

    graphs[index].vertice_count = get_pos_num("Select how many vertices a graph has > ", 0);

    unsigned int n = graphs[index].vertice_count;

	for ( i = 1 ; i <= n ; i++ ) {
		for ( j = 1 ; j <= n ; j++ ) {
			if ( i == j ) {
				graphs[index].adj_mat[i][j] = 0;
				continue;
			} 
            char prompt[50];
            sprintf(prompt, "\nVertices %d & %d are Adjacent?", i, j);

            if (choice(prompt)) {
				graphs[index].adj_mat[i][j] = 1;
            } else {
				graphs[index].adj_mat[i][j] = 0;
            }
		} 
	} 
} 

void print_adj_matrix(unsigned int index) {

    unsigned int i,j;
    unsigned int n = graphs[index].vertice_count;

    printf("\n\n----------------------------------\n");
    printf("Printing graph's adjacency matrix \"%s\" (%s)\n\n", graphs[index].name, graphs[index].type);

	for ( i = 1 ; i <= n ; i++ ) {
		for ( j = 1 ; j <= n ; j++ ) {
            printf("%d ", graphs[index].adj_mat[i][j]);
        }
        printf("\n");
    }

    printf("----------------------------------\n");
}

int undir_graphs_are_not_isomorphic(unsigned int index1, unsigned int index2) {

    unsigned int i,j;

    Graph g1 = graphs[index1];
    Graph g2 = graphs[index2];

    if (g1.vertice_count != g2.vertice_count) {
        return 1;
    } 

    unsigned int vertices1 = 0;
    unsigned int vertices2 = 0;

    unsigned int n = g1.vertice_count;

	for ( i = 1 ; i <= n ; i++ ) {
		for ( j = 1 ; j <= n ; j++ ) {
            if (g1.adj_mat[i][j]) {
                vertices1++;
            }
        }
    }

    n = g2.vertice_count;

	for ( i = 1 ; i <= n ; i++ ) {
		for ( j = 1 ; j <= n ; j++ ) {
            if (g2.adj_mat[i][j]) {
                vertices2++;
            }
        }
    }

    if (vertices1 != vertices2) {
        return 1;
    }

    // TODO implement finding nonmutually adjacent ses
    // pseudocode: 
    /*
      for each vertex v in G1:
            if( G2.find(v).edges != v.edges):
                     return False;
      */
    
    return 0;
}

int main() {

   int option;

   while (1) {
        printf("\n A Program to represent a Graph by using an Adjacency Matrix method\n");
		printf("\n 1. Directed Graph ");
		printf("\n 2. Un-Directed Graph ");
		printf("\n 3. Exit ");

        option = get_num_interval("\n\n Select a proper option > ", "invalid option", 1, 3);
        Graph graph;
        get_word("Input the name of the graph > ", graph.name);
        graphs[size++] = graph;

		switch(option) {
			case 1:
                strcpy(graphs[size-1].type, "directed");
                read_graph(size-1);
                print_dir_graph_vertices(size-1);
                print_adj_matrix(size-1);
				break;
			case 2: 
                strcpy(graphs[size-1].type, "undirected");
                read_graph(size-1);
                print_undir_graph_vertices(size-1);
                print_adj_matrix(size-1);
				break;
			case 3:
                exit(0);
		} 
	}

   return 0;
} 


