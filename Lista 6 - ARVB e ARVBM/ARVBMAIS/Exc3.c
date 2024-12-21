/*
menor elemento da árvore: TARVB* menor(TARVB *a);
*/
#include "TARVBM.c"

int menor(TARVBM *a){
    while (a->filho[0]) a = a->filho[0];
    return a->chave[0];
}
