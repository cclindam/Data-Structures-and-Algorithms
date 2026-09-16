#ifndef HEAP_H
#define HEAP_H 
#include "data_structures.h"
#include <stdlib.h> 
#include <stdio.h> 

	//heap helper functions
	int Parent(int i); 
	int Left(int i); 
	int Right(int i); 

	//heap function
	void min_Heapify(ELEMENT **, HEAP*, int i);
	void build_min_heap(ELEMENT **, HEAP*); 
	void min_heap_decrease_key(ELEMENT **, HEAP*, int oldKey, double newKey); 
	void min_heap_insert(ELEMENT**, HEAP*, int index); 
	void MovingUp(ELEMENT **V, HEAP *pHEAP, int pos);
	ELEMENT* min_heap_minimum(ELEMENT**, HEAP*); 
	ELEMENT* min_heap_extract_minimum(ELEMENT**, HEAP*); 
 

	//print functions
	void print_min_heap(HEAP*);
	void print_elements(ELEMENT **, HEAP *); 

#endif 
