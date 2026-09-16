#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cfloat>
#include "util.h"
#include "heap.h"
#include "graph.h"
#include "stack.h"
//Name: Cole Lindaman ASUID: 1238166464


typedef struct VERTEX_PATH {
    int source; 
    int destination; 
} PATH; 


void printLength(GRAPH *graph, ELEMENT **V, int source, int destination) {

    if(V[source]->color == WHITE || V[destination]->color == WHITE) {
        printf("There is no path from %d to %d.\n", source, destination); 
        return; 
    }

    printf("The length of the shortest path from %d to %d is:     %.2lf\n", source, destination, V[destination]->key); 
}

void printPath(GRAPH *graph, ELEMENT **V, int source, int destination) {

    if(V[source]->color == WHITE || V[destination]->color == WHITE) { //There might be a situation where the path computed may not connect
        printf("There is no path from %d to %d.\n", source, destination);
        return; 
    }

    STACK *pSTACK = (STACK *) malloc(sizeof(STACK));
    pSTACK->capacity = graph->numberOfVerticies; 
    pSTACK->size = 0; 
    pSTACK->H = (int *) malloc(sizeof(int) * (pSTACK->capacity + 1));


    //needs to check to make sure there is actually a path. 
    int current = destination; 
    while (current != -1) {
        push(V, pSTACK, current);
        current = V[current]->pi; 
    }

    if(pSTACK->size <= 0) {
        fprintf(stderr, "Failed to add elements to stack.\n"); 
        return; 
    }

    printf("The shortest path from %d to %d is:\n", source, destination); 
    ELEMENT *currentVertex; 
    while(pSTACK->size != 1) {
        currentVertex = pop(V, pSTACK);

        printf("[%d:%8.2lf]-->", currentVertex->index, currentVertex->key); 
    }
    currentVertex = pop(V, pSTACK); 
    printf("[%d:%8.2lf].\n", currentVertex->index, currentVertex->key);

    free(pSTACK->H); 
    free(pSTACK); 
}

void singlePair(GRAPH *graph, ELEMENT **V, int source, int destination) {
    Dijkstra_ST(graph, V, source, destination, true); 

}

void singleSource(GRAPH *graph, ELEMENT **V, int source) {
    Dijkstra_ST(graph, V, source, -1, false); 
}

//appends new node into the end of the list. 
void addNodeToGraph(GRAPH* graph, int u, int v, double w) {
    NODE *newNode = (NODE *) malloc(sizeof(NODE));
    newNode->index = u; 
    newNode->v = v; 
    newNode->w = w;  


    if(graph->ADJ[u] == nullptr) {
        graph->ADJ[u] = newNode;
        //graph->TailList[u] = newNode; 
        
    } else {
        NODE *current = graph->ADJ[u]; 
        while(current->next != nullptr) current = current->next; 
        current->next = newNode; 
        /*
        graph->TailList[u]->next = newNode;  
        graph->TailList[u] = newNode; 
        */ 
    }
}

//inserts new node into the beginning of ADJ list
void insertNodeToGraph(GRAPH *graph, int u, int v, double w) {
    NODE *newNode = (NODE *) malloc(sizeof(NODE));
    newNode->index = u; 
    newNode->v = v; 
    newNode->w = w; 

    if (graph->ADJ[u] == nullptr) {
        graph->ADJ[u] = newNode; 
    } else {
        NODE *head = graph->ADJ[u]; 
        newNode->next = head; 
        graph->ADJ[u] = newNode; 
    }
}

int main(int argc, char **argv){
    FILE  *fp1; 
    int    returnV, source, destination, flag; 
    char   Word[100]; 
    bool isDirected; 

   int previousComputedSource = -1, previousComputedDestination = -1; 
     
	//data structures 	
    ELEMENT **V; 
    GRAPH *graph; 

    // Check commandline arguments
    if (argc < 4){
        fprintf(stderr, "Usage: %s <InputFile> <GraphType> <Flag>\n", argv[0]);
        exit(0);
    }
    //is a undirected graph? 
    if(strcmp(argv[2], "UndirectedGraph")==0){
        isDirected = false; 
    } else if(strcmp(argv[2], "DirectedGraph")==0) {
        isDirected = true; 
    } else {
        fprintf(stderr, "Usage: <Graphtype> should be DirectedGraph or UndirectedGraph.\n"); 
        return 1; 
    }
    flag = atoi(argv[3]); 

    fp1   = NULL;
    // open networks0<n>.txt file
    fp1 = fopen(argv[1], "r");
    
    //exit if failed to open networks0<n>.txt file
    if (!fp1){
        fprintf(stderr, "Error: cannot open file %s\n", argv[1]);
        exit(0);
    }

    //initialize graph
    int n, m; 
    fscanf(fp1, "%d %d", &n, &m);
    graph = (GRAPH *) malloc(sizeof(GRAPH));
    graph->numberOfVerticies = n; 
    graph->numberOfEdges = m; 
    graph->ADJ = (NODE **) malloc(sizeof(NODE*) * (n+1));
    graph->TailList = (NODE **) malloc(sizeof(NODE*) * (n+1));

    // initialize ELEMENT ** for Dijkstra_ST
    V = (ELEMENT **) malloc(sizeof(ELEMENT *) * (graph->numberOfVerticies + 1)); 
    for(int vertex = 1; vertex <= graph->numberOfVerticies; vertex++) {
        V[vertex] = (ELEMENT *) malloc(sizeof(ELEMENT));
        V[vertex]->index = vertex;  
    }

    int index, u, v;
    double w; 
    while(fscanf(fp1,"%d %d %d %lf", &index, &u, &v, &w) == 4) {
        if(isDirected && flag == 1) {
            addNodeToGraph(graph, u, v, w); 
        } else if(isDirected && flag == 0) {
            insertNodeToGraph(graph, u, v, w); 
        } else if(!isDirected && flag == 1) {
            addNodeToGraph(graph, u, v, w); 
            addNodeToGraph(graph, v, u, w); 
        } else if(!isDirected && flag == 0){
            insertNodeToGraph(graph, u, v, w);
            insertNodeToGraph(graph, v, u, w); 
        }
    }

    fclose(fp1); 

    // Loop over the instructions

    while (1){
        returnV = nextInstruction(Word, &source, &destination);
        if (returnV == 0){
            fprintf(stderr, "Warning: Invalid instruction: %s, %d, %d\n", Word, source, destination);
            continue;
        }

        if(strcmp(Word, "Stop")==0) {
            //printf("Instruction: Stop\n");

            if(V != nullptr) {
                for(int ii = 0; ii <= graph->numberOfVerticies; ii++) {
                    free(V[ii]); 
                }

                free(V); 
             }

            if(graph != nullptr) {
                for(int ii=0; ii <= graph->numberOfVerticies; ii++) {
                    NODE *current = graph->ADJ[ii]; 
                    while(current != nullptr) {
                        NODE *delNODE = current; 
                        current = current->next; 
                        free(delNODE);
                    }
                }

                free(graph); 
            }

            exit(0);  
        }

        if(strcmp(Word, "PrintADJ")==0) {
            //printf("Instruction: PrintADJ\n");
            PrintADJList(graph); 
            continue;
        }
        
        //SinglePair <source> <destination>
        if(strcmp(Word, "SinglePair")==0) {
            //printf("Instruction: SinglePair\n");

            singlePair(graph, V, source, destination);
            previousComputedSource = source;
            previousComputedDestination = destination; 
            continue;
        }

        //SingleSource <source> 
        if(strcmp(Word, "SingleSource")==0) {
            //printf("Instruction: SingleSource\n");
            singleSource(graph, V, source); 
            previousComputedSource = source; 
            previousComputedDestination = -1;  
            continue;
        }

        //PrintLength <s> <t>
        if(strcmp(Word, "PrintLength")==0) {
            //printf("Instruction: PrintLength\n"); 
            printLength(graph, V, source, destination); 
            continue;
        }

        //PrintPath <s> <t>
        if(strcmp(Word, "PrintPath")==0) {
            //printf("Instruction: PrintPath"); 
            if(source == previousComputedSource) {
                //if SingleSource is used, that means there can be more than 1 destination. 
                if(destination == previousComputedDestination || previousComputedDestination == -1) {
                    printPath(graph, V, source, destination);
                }
                
            } 
            continue;
        }
    return 1;
    }
    
    
    if(V != nullptr) {
        for(int ii = 0; ii < graph->numberOfVerticies; ii++) {
            free(V[ii]); 
        }

        free(V); 
    }

    if(graph != nullptr) {
        for(int ii=1; ii <= graph->numberOfVerticies; ii++) {
            NODE *current = graph->ADJ[ii]; 
            while(current != nullptr) {
                NODE *delNODE = current; 
                current = current->next; 
                free(delNODE);

            }
        }

        free(graph); 
    }
}
