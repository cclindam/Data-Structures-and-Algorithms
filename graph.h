#ifndef GRAPH_H
#define GRAPH_H

#include "data_structures.h"


void Dijkstra_ST(GRAPH *graph, ELEMENT **V, int source, int destination, bool singlePair); 
void PrintADJList(GRAPH *); 

#endif