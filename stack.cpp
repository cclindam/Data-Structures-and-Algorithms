#include "stack.h"
#include "data_structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void push(ELEMENT **V, STACK *pSTACK, int index) {
    if(pSTACK->size == pSTACK->capacity) {
        printf("Heap is full.\n"); 
        return; 
    }

    pSTACK->H[++pSTACK->size] = V[index]->index; 
    V[index]->position = pSTACK->size; 

}

ELEMENT *pop(ELEMENT **V, STACK *pSTACK) {
    if(pSTACK->size == 0) {
        printf("Stack is empty.\n"); 
        return nullptr; 
    }

    ELEMENT *key = V[pSTACK->H[pSTACK->size]]; 
    V[pSTACK->H[pSTACK->size]]->position = 0; 
    pSTACK->size--; 
    return key; 
}

void peak(ELEMENT **V, STACK *pSTACK) {
    if(pSTACK->size == 0) {
        fprintf(stderr, "Stack is empty.\n"); 
        return; 
    }
    printf("%lf\n", V[pSTACK->H[pSTACK->size]]->key); 
}

/*
int main(int argc, char **argv) {
    double input[11] = {10, 5.0, 6.0, 3.0, 2.0, 1.0, 4.0, 8.0, 9.0, 7.0, 10.0};
    STACK_ELEMENT **V; 
    STACK *pSTACK; 


    int n = (int) input[0];

    pSTACK = (STACK*) malloc(sizeof(STACK));
    pSTACK->capacity = n; 
    pSTACK->size = 0; 
    pSTACK->H = (int*) malloc(sizeof(int) * (n + 1));

    V = (STACK_ELEMENT **) malloc(sizeof(STACK_ELEMENT *) * (n + 1)); 
    for(int ii = 1; ii <= n; ii++) {
        V[ii] = (STACK_ELEMENT *) malloc(sizeof(STACK_ELEMENT));
        V[ii]->index = ii; 
        V[ii]->key = input[ii]; 
        V[ii]->pos = 0;  
    }

    printf("Testing adding odd elements\n");
    for(int ii = 1; ii <= pSTACK->capacity; ii++) {
        if(!(ii % 2 == 0)) {
            printf("Size of stack: %d adding element: %lf\n", pSTACK->size, V[ii]->key);
            push(V, pSTACK, ii);
        }
    }

    printf("Testing adding even elements\n");
    for(int ii = 1; ii <= pSTACK->capacity; ii++) {
        if(ii % 2 == 0) {
            printf("Size of stack: %d adding element: %lf\n", pSTACK->size, V[ii]->key); 
            push(V, pSTACK, ii);
        }
    }

    printf("V:\n"); 
    for(int ii = 1; ii <= n; ii++) {
        printf("\t%d %lf %d\n", V[ii]->index, V[ii]->key, V[ii]->pos);
    }

    printf("Testing removing elements\n");
    while(pSTACK->size > 0) {
        printf("key popped: %lf\n", pop(V, pSTACK)); 
    } 

    printf("V after removing elements:\n"); 
    for(int ii = 1; ii <= n; ii++) {
        printf("\t%d %lf %d\n", V[ii]->index, V[ii]->key, V[ii]->pos);
        free(V[ii]);
    }
    

    free(V);
    free(pSTACK->H); 
    free(pSTACK); 

    printf("Hello World!\n"); 

    return 0; 
}

*/ 