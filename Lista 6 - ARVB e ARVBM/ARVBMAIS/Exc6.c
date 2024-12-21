/*
quantidade de nós folha: int nf(TARVB *a);
*/
#include "TARVBM.c"
int nf(TARVBM *a){
    if (!a) return INT_MIN;
    if (a->folha) return 1;
    int resp=0;
    while (a->filho[0]) a = a->filho[0];
    while (a){
        resp++;
        a=a->prox;
    }
    return resp;
}