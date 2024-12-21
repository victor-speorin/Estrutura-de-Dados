#include "TAB.c"

TAB *ret_pares(TAB *a){
    if (!a) return a;
    if ((a->info%2)==0){
        int x;
        a = retira_folha(a,&x);
        if(a){
            a->info = x;
            return ret_pares(a);
        }
        else{return NULL;}
    }
    a->esq= ret_pares(a->esq);
    a->dir= ret_pares(a->dir);
    return a;
}

int main(){
    int x, n;
    printf("Insira a quantidade de valores da arvore:\n");
    scanf("%d", &n);
    int* vet = (int*) malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        scanf("%d", &x);
        vet[i] = x;
    }

    TAB *a = vet2ab(vet, n);
    printf("Sua arvore original\n");
    TAB_imp_ident(a);
    a = ret_pares(a);
    printf("Sua arvore modificada:\n");
    TAB_imp_ident(a);
    TAB_libera(a);
    return 0;
}