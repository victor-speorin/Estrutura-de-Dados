/*
 Duas ABBs são SIMILARES se possuem a mesma distribuição de nós (independente
 dos valores nos mesmos). Em uma definição mais formal, duas ABBs são SIMILARES
 se são ambas vazia, ou se suas subárvores esquerdas são similares, e suas subárvores
 direitas também são similares. Implemente a função que verifica se duas árvores são
 similares
*/
#include "TABB.c"
int sim(TABB* a, TABB* b){
    if (!a && !b) return 1;
    if (!a || !b) return 0;
    return ((sim(a->esq,b->esq)) && (sim(a->dir,b->dir)));
}
