/*
verifique se uma TAB é um TABB
*/
#include "TAB.c"

int ver_TABB(TAB* a){
    if (!a) return 1;
    if ((a->esq) && (a->esq->info > a->info)) return 0;
    if ((a->dir) && (a->dir->info < a->info)) return 0;
    return (ver_TABB(a->esq) && ver_TABB(a->dir));
}

int main(){
    TAB *a = NULL;
    int x;
    printf("quantos elementos tem sua arvore? ");
    scanf("%d",&x);
    int *vet = (int*) malloc(sizeof (int)*x);
    for (int i=0;i<x;i++){
        printf("\tinsira o %d elemento: ", i+1);
        scanf("%d", &vet[i]);
    }
    a = vet2ab(vet,x);
    printf("sua arvore eh: ");
    TAB_imp_ident(a);
    printf("\n");
    x = ver_TABB(a);
    if (x) printf("TABB");
    else printf("nao");
    free(vet);
    TAB_libera(a);
    return 0;
}