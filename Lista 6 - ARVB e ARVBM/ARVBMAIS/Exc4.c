/*
função que, dadas duas árvores deste tipo, testa se estas árvores são iguais. A
função retorna um se elas são iguais e zero, caso contrário. A função deve
obedecer ao seguinte protótipo: int igual (TARVB* a1, TARVB* a2);
*/
#include "TARVBM.c"
int igual (TARVBM* a1, TARVBM* a2){
    if (!a1 || !a2) return 0;
    while (a1->filho[0]) a1 = a1->filho[0];
    while (a2->filho[0]) a2 = a2->filho[0];
    while (a1 && a2){
        if (a1->nchaves != a2->nchaves) return 0;
        for (int i=0;i<a1->nchaves;i++){
            if (a1->chave[i]!=a2->chave[i]) return 0;
        }
        a1=a1->prox;
        a2=a2->prox;
    }
    return 1;
}