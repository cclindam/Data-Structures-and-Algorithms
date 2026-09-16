#ifndef DATA_STRUCTURES

#define DATA_STRUCTURES
//Name: Cole Lindaman ASUID: 1238166464

enum COLOR {
	WHITE, 
	GREY, 
	BLACK
}; 

typedef struct TAG_VERTEX{
	int index; 
	COLOR color; 
	double key; 
	int pi; 
	int position; 
}VERTEX; 
//usage: typedef VERTEX *pVERTEXT

typedef struct TAG_NODE{
	int index;  
	int v; 
	double w; 
	TAG_NODE *next; 
}NODE; 
//usage: typedef NODE *pNODE

typedef struct TAG_GRAPH{
	int numberOfVerticies; 
	int numberOfEdges; 
	NODE **TailList; 
	NODE **ADJ; 
}GRAPH; 

typedef VERTEX ELEMENT; 
typedef ELEMENT *pELEMENT; 

typedef struct TAG_HEAP {
	int capacity; //capacity of the heap
	int size; //current size of the heap
	int *H; //array of indices to ANOTHER array
} HEAP; 
//usage: HEAP *pHeap; 

typedef struct TAG_STACK_ELEMENT {
	int pos;  
	double key; 
	int index; 

} STACK_ELEMENT; 

typedef struct TAG_STACK {
	int capacity; 
	int size; 
	int *H; 

} STACK; 



#endif
