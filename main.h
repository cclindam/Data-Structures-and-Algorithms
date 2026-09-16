#ifndef MAIN_H
#define MAIN_H
#include "data_structures.h"

//Name: Cole Lindaman ASUID: 1238166464
void initHeap(ELEMENT **, HEAP*); 
void printLength(GRAPH *graph, ELEMENT **V, int source, int destination);
void singlePair(GRAPH *graph, ELEMENT **V, int source, int destination);
void singleSource(GRAPH *graph, ELEMENT **V, int source); 

#endif