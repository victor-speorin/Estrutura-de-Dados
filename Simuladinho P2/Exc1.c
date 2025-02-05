/*
Com base na biblioteca de heap binária implementada em
sala, refaça a função void max_heapfy_k(int *vet, int n, int
ind, int k) para uma heap k-nária em memória principal. Ou
seja, cada nó pode ter no máximo k filhos.
*/
#include "stdio.h"
#include "limits.h"
int pai (int k,int ind){
    if (ind <= 0) return INT_MAX;
    return (ind-1)/k;
}

int filho(int k, int ind, int f){
    return (k*ind) + f;
}

void max_heapfy_k(int *vet, int n, int ind, int k){
    int maior = ind;
    for (int i=1; i <= k; i++){
        int x = filho(k,ind,i);
        if ((x < n) && vet[x] > vet[maior]) maior = x;
    }
    if (maior != ind){
        int tmp = vet[ind];
        vet[ind] = vet[maior];
        vet[maior] = tmp;
        max_heapfy_k(vet,n,maior,k);
    }
}