/*
menor elemento da árvore: TARVB* maior(TARVB *a)
*/
#include "TARVB.c"

int menor(TARVB *a){
    while (a->filho[0]) a = a->filho[0];
    return a->chave[0];
}