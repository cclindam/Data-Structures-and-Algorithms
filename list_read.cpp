#include "list_read.h"
#include <stdio.h>
#include <stdlib.h>

void listPrint(FILE *stream, LIST *pLIST){
    NODE *pNODE;

    if (!pLIST){
        fprintf(stderr, "Error in listPrint: NULL list\n");
        exit (0);
    }else{
        fprintf(stream, "Length=%d\n", pLIST->length);
        pNODE = pLIST->head;
        while (pNODE){
            fprintf(stream, "%lf\n", pNODE->key);
            pNODE = pNODE->next;
        }
    }
}


NODE * listSearch(LIST *pLIST, double query){
    NODE *pNODE;

    if (pLIST == NULL){
        fprintf(stderr, "Error in listSearch: NULL list\n");
        exit (0);
    }

    pNODE = pLIST->head;
    while (pNODE){
        if (pNODE->key == query){
            return pNODE;
        }
        pNODE = pNODE->next;
    }
    return pNODE;
}


double listMax(LIST *pLIST){
    double max;
    NODE *pNODE;

    if (pLIST == NULL){
        fprintf(stderr, "Error in listMax: NULL list\n");
        exit(0);
    }else if (pLIST->head == NULL){
        fprintf(stderr, "Error in listMax: Empty list\n");
        exit(0);
    }else{
        pNODE = pLIST->head;
        max   = pNODE->key;
        while (pNODE){
            if (pNODE->key > max) max = pNODE->key;
            pNODE = pNODE->next;
        }
    }
    return max;
}


double listMin(LIST *pLIST){
    double min;
    NODE *pNODE;

    if (pLIST == NULL){
        fprintf(stderr, "Error in listMin: NULL list\n");
        exit(0);
    }else if (pLIST->head == NULL){
        fprintf(stderr, "Error in listMin: Empty list\n");
        exit(0);
    }else{
        pNODE = pLIST->head;
        min   = pNODE->key;
        while (pNODE){
            if (pNODE->key < min) min = pNODE->key;
            pNODE = pNODE->next;
        }
    }
    return min;
}


double listSum(LIST *pLIST){
    double sum;
    NODE *pNODE;

    if (pLIST == NULL){
        fprintf(stderr, "Error in listSum: NULL list\n");
        exit(0);
    }else if (pLIST->head == NULL){
        fprintf(stderr, "Error in listSum: Empty list\n");
        exit(0);
    }else{
        sum   = 0;
        pNODE = pLIST->head;
        while (pNODE){
            sum = sum + pNODE->key;
            pNODE = pNODE->next;
        }
    }
    return sum;
}


