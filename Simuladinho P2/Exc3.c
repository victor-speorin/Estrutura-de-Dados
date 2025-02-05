/*
Dada uma Árvore B+ qualquer, retorne, numa lista, todos os
elementos menores que N. A função tem o seguinte protótipo:
TLSE* mN(TARVBM *a, int N);
*/
#include "TLSE.c"
#include "TARVBM.c"

TLSE* mN(TARVBM *a, int N){
    TLSE *l = NULL;
    while (a->filho[0]) a = a->filho[0];
    while(a){
        for (int i=0;i<a->nchaves;i++){
            if (a->chave[i] < N) l = TLSE_ins_fim(l,a->chave[i]);
            else return l;
        }
        a = a->prox;
    }
    return l;
}