#include "graph.h"
#include "heap.h"
#include "data_structures.h"
#include <stdio.h> 
#include <stdlib.h>
#include <limits.h> 
#include <float.h>

#include <set> 


void PrintADJList(GRAPH *graph) {
     
    for(int vertex=1; vertex<=graph->numberOfVerticies; vertex++) {
        NODE *current = graph->ADJ[vertex];
        printf("ADJ[%d]:", vertex);
        
        while(current != nullptr) {
            printf("-->[%d %d: %4.2lf]", vertex, current->v, current->w); 
            current = current->next; 
        }
        printf("\n");
    }
}

void Dijkstra_ST(GRAPH *graph, ELEMENT **V, int source, int destination, bool singlePair) {
    bool *visted = (bool *) calloc(graph->numberOfVerticies + 1, sizeof(bool)); 
    for (int vertex=1; vertex <= graph->numberOfVerticies; vertex++) {
        V[vertex]->index = vertex; 
        V[vertex]->key = DBL_MAX; 
        V[vertex]->pi = -1; 
        V[vertex]->color = WHITE; 
        V[vertex]->position = 0; 
    }

    V[source]->key = 0; 
    V[source]->color = GREY; 

    //initialize heap, add source vertex to heap. 
    HEAP *pHEAP = (HEAP *) malloc(sizeof(HEAP));
    pHEAP->capacity = graph->numberOfVerticies; 
    pHEAP->size = 0; 
    pHEAP->H = (int *) malloc(sizeof(int) * (graph->numberOfVerticies + 1));  
    min_heap_insert(V, pHEAP, source);

    ELEMENT *u, *v; 
    while(pHEAP->size > 0) {
        
        u = min_heap_extract_minimum(V, pHEAP); 
        u->color = BLACK;

        //printf("Popped off element: vertex: %d, position in heap: %d, previous vertex: %d, weight: %.2lf\n", u->index, u->position, u->pi, u->key); 
        if(u->index == destination && singlePair) return;

        NODE *currentNode = graph->ADJ[u->index];

        while(currentNode != nullptr) {
            v = V[currentNode->v];

            if(v->color == WHITE) { 
                v->color = GREY; 
                v->pi = u->index; 
                v->key = currentNode->w + u->key; 
                if(visted[v->index] == false) {
                    visted[v->index] = true;
                } else {
                    printf("*** ERROR *** duplicate found: %d\n", v->index);
                    return; 
                }
                min_heap_insert(V, pHEAP, v->index); 

            } else if(v->color == GREY) {

                if( v->key > (u->key + currentNode->w)) {
                    //relax; 
                    double newKey; 
                    newKey = (u->key + currentNode->w); 
                    v->pi = u->index; 
                    //call decreaseKey
                    min_heap_decrease_key(V, pHEAP, v->index, newKey); //probably wrong, I need to decrease key in the min_heap
                }
                
            }

            currentNode = currentNode->next; 
        }
    }

    free(pHEAP->H); 
    free(pHEAP); 
}
/*
int main(int argc, char ** argv) {

    if(argc < 2) {
        printf("INVALID USAGE: ./graphTest <file>\n"); 
        return 1; 
    }

    FILE *fp1; 

    fp1 = fopen(argv[1], "r");
    if(!fp1) {
        printf("Failed to open file.\n"); 
        return 1; 
    } 

    ELEMENT **V; 
    HEAP *pHEAP; 
    STACK *pSTACK; 
    GRAPH *graph; 
    //n = number of edges, m = number of vertices
    int n, m; 

    fscanf(fp1, "%d %d", &n, &m); 
    printf("Read in first two: n=%d, m=%d\n", n, m); 

    graph = (GRAPH *) malloc(sizeof(GRAPH));
    graph->numberOfVerticies = n; 
    graph->numberOfEdges = m; 
    graph->ADJ = (NODE **) malloc(sizeof(NODE*) * (n+1));
    graph->TailList = (NODE **) malloc(sizeof(NODE*) * (n+1));

    V = (ELEMENT **) malloc(sizeof(ELEMENT *) * (n+1));
    for(int vertex = 1; vertex <= n; vertex++) {
        V[vertex] = (ELEMENT *) malloc(sizeof(ELEMENT)); 
        V[vertex]->index = vertex; 
        V[vertex]->key = DBL_MAX; 
        V[vertex]->position = 0; 
        V[vertex]->color = WHITE; 
    }


    int index, u, v;
    double w; 
    while(fscanf(fp1,"%d %d %d %lf", &index, &u, &v, &w) == 4) {
        
        NODE *newNode = (NODE *) malloc(sizeof(NODE));
        newNode->index = index; 
        newNode->u = u;
        newNode->v = v; 
        newNode->w = w;  
        if(graph->ADJ[u] == nullptr) {
            graph->ADJ[u] = newNode;
            graph->TailList[u] = newNode; 
            
        } else {
            graph->TailList[u]->next = newNode;  
            graph->TailList[u] = newNode; 
        }
    }

    printf("\n"); 

    PrintADJList(graph); 
    for(int ii = 0; ii <= graph->numberOfVerticies; ii++) {
        if(graph->ADJ[ii] != nullptr) {
            NODE *current = graph->ADJ[ii]; 
            while(current == nullptr) {
                NODE *delNode = current; 
                current = current->next; 

                free(delNode); 
            } 
        }

        if(graph->TailList[ii] != nullptr) {
            //printf("This probably won't get called since we clear it in the ADJ list.\n"); 
            NODE *current = graph->ADJ[ii]; 
            free(current); 
        }
    }
    //free(V); 
    for(int ii=0; ii <= graph->numberOfVerticies; ii++) {
        //ELEMENT *delNode = V[ii]; 
        free(V[ii]); 

    }
    free(graph); 
    free(V); 
    
    fclose(fp1); 

    return 0; 
}

*/ 

