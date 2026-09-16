#include "list_read.h"
#include "list_write.h"
#include <stdio.h>
#include <stdlib.h>

//Name: Cole Lindaman ASUID: 1238166464



void listRelease(LIST *pLIST){
	if (pLIST->head == nullptr && pLIST->tail == nullptr) {
		return; 
	}

	NODE *current = pLIST->head; 
	while(current->next != nullptr) {
		NODE *delNode = current;
		current = current->next; 
		delNode->next = nullptr; 
		free(delNode); 
	
	}

	pLIST->head = pLIST->tail = nullptr;
        pLIST->length = 0; 	
}


NODE * listInsert(LIST *pLIST, double key){
	NODE *pNODE;
	pNODE = (NODE *) malloc(sizeof(NODE)); 
	pNODE->key = key; 

	if (pLIST->head == nullptr && pLIST->tail == nullptr) {
		pLIST->head = pLIST->tail = pNODE; 
		pLIST->length = 1; 

		return pNODE; 
	}

	NODE *prevHead = pLIST->head; 
	pNODE->next = prevHead; 
	pLIST->head = pNODE; 


	pLIST->length++; 
	return pNODE;
}


NODE * listAppend(LIST *pLIST, double key){
	NODE *pNODE;
	pNODE = (NODE *) malloc(sizeof(NODE));
	pNODE->key = key;

	//if pList length is zero, pNode is head and tail. 
	if (pLIST->head == nullptr && pLIST->tail == nullptr) {
	    	pLIST->head = pLIST->tail = pNODE;
		pLIST->length = 1; 
		return pNODE;  
	}

	NODE *prevTail = pLIST->tail; 
	prevTail->next = pNODE; 
	pLIST->tail = pNODE; 

	pLIST->length++; 
	return pNODE;
}


NODE * listDelete(LIST *pLIST, double key){
    
	if(pLIST->head == nullptr && pLIST->tail == nullptr) {
		fprintf(stdout, "Warning in listDelete: Key %lf not in list not in list\n", key); 	
		return nullptr; 
	}
    
	NODE *delNODE = nullptr; 

    
	if (pLIST->head->key == key) {
		delNODE = pLIST->head; 
		pLIST->head = delNODE->next; 
		pLIST->length--; 
		return delNODE; 
	}

	NODE *current, *prev;
	prev = pLIST->head; 
	current = prev->next; 

	while(current != nullptr) {
		if (current->key == key) {
			delNODE = current; 
			prev->next = delNODE->next; 
			break; 
		}
		prev = current; 
		current = current->next; 
    	} 
    	if(current == nullptr) {
		fprintf(stdout, "Warning in listDelete: Key %lf not in list\n", key); 	
		return nullptr;

	}else if (current == pLIST->tail) {
		pLIST->tail = prev; 
	}
    
	pLIST->length--; 
	return delNODE;
}

void printList(LIST *pLIST) {
    
	NODE *current = pLIST->head;
	printf("[");
	
	while(current->next != nullptr) {
		printf("%.2lf, ", current->key);
        	current = current->next; 	
	}
	printf("%.2lf]\n", current->key);
}

/*
int main() {
	LIST * pList = (LIST *) calloc(1, sizeof(LIST)); 
	pList->length = 0; 
	pList->head = NULL; 
	pList->tail = NULL; 

	for (int ii =0; ii<=10; ++ii) {
		listAppend(pList, (double) ii); 	
	}

	printList(pList); 
	listDelete(pList, 3); 
	printList(pList); 
	listDelete(pList, 3); 
	listDelete(pList, 11); 
	return 0; 
}

*/
