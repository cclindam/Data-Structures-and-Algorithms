#include "heap.h"
#include "data_structures.h"
#include <limits.h> 
#include <float.h> 
//Name: Cole Lindaman ASUID: 1238166464
ELEMENT *min_heap_extract_minimum(ELEMENT **V, HEAP *pHeap) {
	ELEMENT *min = min_heap_minimum(V, pHeap); 
	V[pHeap->H[1]]->position = 0; 
	pHeap->H[1] = pHeap->H[pHeap->size]; 
	V[pHeap->H[1]]->position = 1; 
	pHeap->size--; 
	min_Heapify(V, pHeap, 1); 
	return min; 
}

ELEMENT *min_heap_minimum(ELEMENT **V, HEAP *pHeap) {
	if(pHeap->size < 1) {
		fprintf(stderr, "heap underflow\n");
		return nullptr; //TODO find out what to do when calling min_heap_min when there are no elements in the heap. 
	}

	return V[pHeap->H[1]]; 
} 

void build_min_heap(ELEMENT **V, HEAP *pHeap) {
	int size = pHeap->size; 
	for(int i=size/2; i>=1; i--) {
		min_Heapify(V, pHeap, i); 
	}
}

void min_heap_decrease_key(ELEMENT **V, HEAP *pHeap, int index, double newKey) {
	if(V[index]->position > pHeap->capacity || V[index]->position <= 0) {
		printf("error: there is no such key in heap.\n"); 
		return; 
	}

	if(newKey > V[index]->key) {
		fprintf(stderr, "error: newKey is smaller than current key.\n"); 
		return; 
	} else {
		V[index]->key = newKey; 
		MovingUp(V, pHeap, V[index]->position); 
	}
}

void MovingUp(ELEMENT **V, HEAP *pHEAP, int pos) {
	int parent; 
	int temp; 
	parent = Parent(pos);  
	if(pos > 1 && V[pHEAP->H[pos]]->key < V[pHEAP->H[parent]]->key) {

		temp = pHEAP->H[pos]; 
		pHEAP->H[pos] = pHEAP->H[parent]; 
		pHEAP->H[parent] = temp; 

		V[pHEAP->H[pos]]->position = parent; 
		V[pHEAP->H[parent]]->position = pos;


		MovingUp(V, pHEAP, parent); 


	}
}

void min_heap_insert(ELEMENT **V, HEAP *pHeap, int index) {

	if(V[index]->position != 0) {
		fprintf(stderr, "Error: V[%d] already in the heap.\n", index);  
		return; 
	}

	//increase heap size
	pHeap->size++;

	//get the current key value. 
	double key = V[index]->key;
	//set the key value to infinity and add insert to the end of the heap
	V[index]->key = DBL_MAX; 
	V[index]->position = pHeap->size;
	
	pHeap->H[V[index]->position] = V[index]->index; 

	min_heap_decrease_key(V, pHeap, index, key); 

}

void min_Heapify(ELEMENT **V, HEAP *pHeap, int i) {
	int l = Left(i); 
	int r = Right(i); 
	int size = pHeap->size;
	int smallest; 
	
	if(l <= size && V[pHeap->H[l]]->key < V[pHeap->H[i]]->key) {
		smallest = l;
	} else {
		smallest = i;
	}
	
	if(r <= size && V[pHeap->H[r]]->key < V[pHeap->H[smallest]]->key) {
		smallest = r;
	}
	
	if(smallest != i) {
		int indexTemp = pHeap->H[i]; 
		pHeap->H[i] = pHeap->H[smallest]; 
		pHeap->H[smallest] = indexTemp;

		V[pHeap->H[smallest]]->position = smallest; 
		V[pHeap->H[i]]->position = i;

		min_Heapify(V, pHeap, smallest); 	
				
	} 
}

int Parent(int i) {
	return i / 2; 
} 

int Left(int i) { 
	return 2*i; 
}

int Right(int i) {
	return 2*i + 1; 
}


void print_min_heap(HEAP *pHeap) {
	
	printf("Capacity = %d, size = %d\n", pHeap->capacity, pHeap->size); 
	if(pHeap->size >= 1) {
		for(int i = 1; i <= pHeap->size; i++) {
			printf("H[%d] = %d\n", i, pHeap->H[i]); 		
		}
	}  
	
}

void print_elements(ELEMENT **V, HEAP *pHeap) {
	if(V == nullptr) {
		printf("There has been no elements\n");
		return; 
	}
	
	for(int ii=1; ii <= pHeap->capacity; ii++) {
		printf("%d %lf %d\n", V[ii]->index, V[ii]->key, V[ii]->position); 
	}

}
